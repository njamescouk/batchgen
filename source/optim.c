#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "batchgen.h" 
#include "optim.h"
/* #include "sr.h" */

// char *strdup(const char *s);

#pragma warning( disable : 4996 )

#define END_OF_LIST -1

label_detail_t *labels = NULL;
int code_lines;
int max_labels = 0;
int num_labels = 0;
int label_incr = 50;
char remove_rems = 0;
char remove_blanks = 0;

#ifndef STANDALONE

extern FILE *ofp;
static code_list_t *clptr;
static char *codeptr;

char **copy_lines (code_list_t *code)
{
    /* copy code into array of pointer to char and return pointer to base of
       array
    */
   char **result;
   char text [TEXTLEN];
   int textptr = 0;
   int lines = 0;
   /* int num_code_nodes = 0; */
   char c, done = 0;

   /* printf ("copy_lines\n"); */
   clptr = code;
   codeptr = clptr->code;
   /* num_code_nodes =  */
   cn_count (code);
   code_lines = lines = list_line_count (code);
   code_lines++;
   result = (char **) calloc (lines + 1, sizeof (char *));
   lines = 0;
   while (!done)
   {
      /* codeptr = clptr->code; */
      textptr = 0;
      while ((c = next_char ()) != '\n' && c != END_OF_LIST)
      {
         if (c == 0)
            break;
         text [textptr] = c;
         textptr++;
         if (textptr > TEXTLEN)
         {
            fprintf (stderr, "line too long\n");
            return NULL;
         }
      }
      text [textptr] = 0;
      result [lines] = strdup (text);
      /*
      result [lines] = (char *) calloc (strlen (text) + 1, sizeof (char));
      strcpy (result [lines], text);
      */

      lines++;
      if (c == END_OF_LIST)
         done = 1;
   }

   code_lines = lines;
   return result;
}

int list_line_count (code_list_t *cl)
{
   int res = 0;
   char *cp = NULL;

   while (cl != NULL)
   {
      cp = cl->code;
      while (*cp != 0)
      {
         if (*cp == '\n' || cp == 0)
            res++;
         cp++;
      }
      cl = cl->next;
   }
   return res;
}

char next_char (void)
{
   char c;

   /* printf ("next_char\n"); */
   c = *(codeptr);
   if (c != 0)
      codeptr++;
   if (c == 0)
   {
      if (clptr->next != NULL)
      {
         clptr = clptr->next;
         codeptr = clptr->code;
         c = *(codeptr);
         if (c != 0)
            codeptr++;
      }
      else
         return END_OF_LIST;
   }
   return c;
}

#else

#include "fileread.h"

int count_sr (char **ca);
void get_opts (int argc, char*argv []);

int sr_call_count = 0;

char main (int argc, char *argv [])
{
   char **ca = NULL;
   FILE *fp = NULL, *ofp = NULL;

   if (argc == 1)
   {
      printf ("usage: %s [-r] [-b] filename\n", argv[0]);
      return 1;
   }
   get_opts (argc, argv);
   fp =  fopen (argv [argc - 1], "rt");
   if (fp != NULL)
   {
      code_lines = line_count (fp);
      rewind (fp);
      ca = file_read (fp);
      sr_call_count = count_sr (ca);
      if (optimize (ca) == 0)
      {
         ofp = fopen ("bgo.bat", "wt");
         if (ofp != NULL)
         {
            print_ca (ca, ofp);
            fclose (ofp);
            return 0;
         }
         else
            perror ("optimize, cannot open output file");
      }
   }
   return 1;
}

void get_opts (int argc, char*argv [])
{
   int i;

   for (i = 0; i < argc; i++)
   {
      if (argv [i][0] == '-')
      {
         int j;

         for (j = 1; argv [i][j] != NULL; j++) 
         {
            switch (argv[i][j])
            {
               case 'r': remove_rems = 1;
                         break;
               case 'b': remove_blanks = 1;
                         break;
            }
         }
      }
   }
}

int count_sr (char **ca)
{
   int res = 0, i;

   /* printf ("count_sr\n"); */
   for (i = 0; i < code_lines; i++)
      if (strstr (ca[i], "goto "SR_PFX) != NULL)
         res++;
   return res;
}

#endif

char get_labels (char **ca)
{
   int i;
   char text [TEXTLEN];
   char *lab_beg, result = 0;

   /* printf ("get_labels\n");  */

   /*
   sprintf (text, "%%"RET_LABEL"%%");
   install_def (text);
   for (i = 0; i < sr_call_count && result == 0; i++)
   {
      sprintf (text, END_SR_PFX"%i", i);
      result = install_ref (text);
      *//*
      sprintf (text, SR_PFX"%i", i);
      install_ref (text);
      *//*
   }*/
   
   result = install_def(":eof");

   for (i = 0; i < code_lines && result == 0; i++)
   {
      if (is_label (ca [i]))
      {
         lab_beg = strchr (ca [i], ':');
         lab_beg++;
         sscanf (lab_beg, "%s", text);
         result = install_def (text); 
      }
      else if (is_branch (ca [i]))
      {
         lab_beg = strstr (ca [i], "goto");
         lab_beg += 4;
         sscanf (lab_beg, "%s", text);
         result = install_ref (text);
      }
      else if (is_call (ca [i]))
      {
         lab_beg = strstr (ca [i], "call");
         lab_beg += 4;
         
         sscanf (lab_beg, "%s", text);
         if (text != 0 && text[0] == ':' && strlen(text) > 1)
             result = install_ref (&text[1]);
         else
             result = 0; // was a call to another batch file, not call :label
      }
   }
   return result;
}

char install_def (char *str)
{
   int ln, i;
   label_detail_t *labptr;

   /* printf ("install_def\n");  */
   ln = find_label (str); 
   if (ln == -1)
   {
      if (num_labels >= max_labels)
      {
         labels = (label_detail_t *) \
                   realloc (labels, \
                     sizeof (label_detail_t) * (max_labels + label_incr));
         if (labels == NULL)
            return 1;
         for (i = max_labels; i < max_labels + label_incr; i++)
         {
            labels [i].label = NULL;
            labels [i].refd = 0;
            labels [i].defd = 0;
         }
         max_labels += label_incr;
      }
      labptr = labels + num_labels;
      labptr->label = (char *)realloc (labptr->label, 
                                      (strlen (str) + 1) * sizeof (char));
      strcpy (labptr->label, str);
      labptr->defd = 1;
      labptr->refd = 0;
      num_labels++;
   }
   else if (ln > num_labels - 1)
   {
      fprintf (stderr, "bad label no\n");
      return 1;
   }
   else
      (labels + ln)->defd = 1;
   return 0;
}

char install_ref (char *str)
{
   int ln, i;
   label_detail_t *labptr;

   /* printf ("install_ref\n");  */
   ln = find_label (str); 
   if (ln == -1)
   {
      if (num_labels >= max_labels)
      {
         labels = (label_detail_t *) \
                   realloc (labels, \
                     sizeof (label_detail_t) * (max_labels + label_incr));
         if (labels == NULL)
         {
            perror ("install_ref");
            return 1;
         }
         for (i = max_labels; i < max_labels + label_incr; i++)
         {
            labels [i].label = NULL;
            labels [i].refd = 0;
            labels [i].defd = 0;
         }
         max_labels += label_incr;
      }
      labptr = labels + num_labels;
      labptr->label = (char *)realloc (labptr->label, \
                                        (strlen (str) + 1) * sizeof (char));
      strcpy (labptr->label, str);
      labptr->defd = 0;
      labptr->refd = 1;
      num_labels++;
   }
   else if (ln > num_labels - 1)
   {
      fprintf (stderr, "bad label no\n");
      return 1;
   }
   else
      (labels + ln)->refd = 1;
   return 0;
}

int find_label (char *str)
{
   int result;

   /* printf ("find_label\n");  */
   for (result = 0; result < num_labels; result++)
   {
      if (strcmp (str, labels [result].label) == 0)
         return result;
   }
   return -1;
}

char optimize (char **ca)
{
   int i;
   int changed = 1;
   int lcount = 0;

   if (get_labels (ca) != 0)
   {
      fprintf (stderr, "get_labels failed\n");
      return 1;
   }

   if (remove_blanks)
   {
      for (i = 0; i < code_lines; i++)
      {
         if (is_blank (ca [i]))
         {
            del_line (ca, i);
            /*i--;*/
         }
      }
   }

   if (remove_rems)
   {
      for (i = 0; i < code_lines; i++)
      {
         if (is_rem (ca [i]))
         {
            del_line (ca, i);
            i--;
         }
      }
   }

   while (changed)
   {
      changed = 0;
      // for each line in ca
      for (i = 0; i < code_lines && !changed; i++)
         changed += optimize_line(ca, i);

      for (i = 0; i < num_labels; i++)
      {
         if ((labels [i]).refd == 0)
            changed += del_unrefd_labs (labels[i].label, ca);
      }

      if (changed)
      {
         num_labels = 0;
         if (get_labels (ca) != 0)
         {
            fprintf (stderr, "get_labels failed\n");
            return 1;
         }
         if (check_labels () != 1)
         {
            fprintf (stderr, "optimize failed at pass %i\n", lcount);
            return 1;
         }
      }
      lcount++;
      /*
      sprintf (tempfile, "opt%i.bat", lcount);
      tmpfp = fopen (tempfile, "wt");
      print_ca (ca, tmpfp);
      fclose (tmpfp);
      */
   }
   return 0;
}

// return as soon as something has changed in 
// attempt to get rid of bugs
char optimize_line (char **ca, int line)
{
    if (remove_blanks)
        if (is_blank (ca [line]))
        {
           del_line (ca, line);
           return 1;
        }

    if ((line + 1) < code_lines && is_uncond_br (ca [line]))
    {
        /* 
            we've got a goto followed by a line.
            delete the following line, unless
            it is a label, as it can 
            never be executed
        */
        char lab1 [TEXTLEN], lab2 [TEXTLEN];
        /* dead code elimination */

        if ((line + 1) < code_lines && !is_label (ca [line+1]))
        {
           del_line (ca, line + 1);
           return 1;
        }

        /* redundant goto ? */
        strcpy (lab1, get_label_ref (ca [line]));
        strcpy (lab2, get_label_def (ca [line+1]));
        if (strcmp (lab1, lab2) == 0)
        {
           del_line (ca, line);
           return 1;
        }
    }
    else if ((line + 2) < code_lines && is_cond_br (ca [line]) 
                                        && is_uncond_br (ca [line + 1]))
    {  
        /* eliminate jumps over jumps */
        if (is_label (ca [line+2]))
        {
           char lab1 [TEXTLEN], lab2 [TEXTLEN], lab3 [TEXTLEN];

           strcpy (lab1, get_label_ref (ca [line]));
           strcpy (lab2, get_label_ref (ca [line+1]));
           strcpy (lab3, get_label_def (ca [line+2]));
           if (strcmp (lab1, lab3) == 0)
           {
              char *lp, newline [TEXTLEN];

              lp = strstr (ca [line], "goto");
              *lp = 0;
              if (negate (& ca [line]) != 0)
              {
                 fprintf (stderr, "negate failed\n");
                 return 1;
              }
              sprintf (newline, "%s%s", ca [line], ca [line+1]);
              ca [line] = (char *)realloc (ca [line], \
                                (strlen (newline) + 1) * sizeof (char));
              if (ca [line] == NULL)
              {
                 fprintf (stderr, "realloc failed in elim j over j\n");
                 return 1;
              }
              strcpy (ca[line], newline);
              del_line (ca, line + 1);
              return 1;
           }
        }
    }
    else if ((line + 2) < code_lines && is_cond_br (ca [line])
                   && is_label (ca [line + 2]) && !is_cond_br (ca[line+1]))
    {
        /* one line if */
        char lab1 [TEXTLEN], lab2 [TEXTLEN];

        strcpy (lab2, get_label_def (ca [line+2])); 
        strcpy (lab1, get_label_ref (ca [line]));
        if (strcmp (lab1, lab2) == 0)
        {
           char *lp, newline [TEXTLEN];

           lp = strstr (ca [line], "goto");
           *lp = 0;
           if (negate (& ca [line]) != 0)
           {
              fprintf (stderr, "negate failed\n");
              return 1;
           }
           sprintf (newline, "%s%s", ca [line], ca [line+1]);
           ca [line] = (char *)realloc (ca [line], \
                             (strlen (newline) + 1) * sizeof (char));
           if (ca [line] == NULL)
           {
              fprintf (stderr, "realloc failed in one line if\n");
              return 1;
           }
           strcpy (ca[line], newline);
           del_line (ca, line + 1);
             return 1;
        }
    }
    else if ((line + 1) < code_lines && is_label (ca [line]))
    {
        if (is_label (ca [line+1]))
        {
           /* eliminate duplicate labels */

           char lab1 [TEXTLEN], lab2 [TEXTLEN];

           strcpy (lab2, get_label_def (ca [line+1])); 
           strcpy (lab1, get_label_def (ca [line]));
           if (!(is_esr (lab1) || is_esr (lab2)))
           {
              if (reref_labs (ca, lab1, lab2) != 0)
                 return 1;
           }
        }
        else if (is_uncond_br (ca [line+1]))
        {
           /* jump to jump */

           char lab1 [TEXTLEN], lab2 [TEXTLEN];

           strcpy (lab2, get_label_ref (ca [line+1])); 
           strcpy (lab1, get_label_def (ca [line]));
           if (!(is_esr (lab1) || is_esr (lab2)))
           {
              if (reref_labs (ca, lab2, lab1) != 0)
                 return 1;
           }
        }            
    }
    return 0;
}

char del_unrefd_labs (char *name, char **ca)
{
   int i;
   char result = 0;
   char text [TEXTLEN];

   /* printf ("del_unrefd_labs\n");  
   if (strstr(name, "batch_end") != NULL)
       return 0;
    */

   sprintf (text, ":%s", name);
   for (i = 0; i < code_lines; i++)
   {
      if (find_word (ca [i], text) != NULL && is_label (ca [i]))
      {
         del_line (ca, i);
         result = 1;
      }
   }

   return result;
}

void print_ca (char **ca, FILE *fp)
{
    int i;

   /* printf ("print_ca\n"); */
   for (i = 0; i < code_lines; i++)
   {
      if (ca [i] != NULL)                 
        fprintf (fp, "%s\n", ca [i]);
   }   
}

char *find_word (char *str, char *word)
{
   /* is word in string: return NULL or ptr to word in str */
   char *lp, c, done = 0;

   /* printf ("find_word\n");  */
   if (*str == '@')
      str++;
   while (!done)
   {
      lp = strstr (str, word);
      if (lp == NULL)
         return NULL;
      c = *(lp + strlen (word));
      if (
           (lp == str || isspace (*(lp - 1)))
           && (isspace (c) || c == 0)
         )
         /* return 1; */
         return lp;
      else if (lp != NULL)
      {
         str = lp+1;
         continue;
      }
      else
         done = 1;
   }
   return NULL;
}

char is_branch (char *str)
{
   /* printf ("is_branch\n");  */
   if ((str = find_word (str, "goto")) != NULL)
   {
      str += 4;
      while (isspace (*str) && *str != 0)
         str++;
      if (*str != '%') /* exclude %_ret_label% */ /* why? can't remember. irrelevant now anyhow */
         return 1;
   }
   return 0;
}

char is_call (char *str)
{
   /* printf ("is_call\n");  */
   if ((str = find_word (str, "call")) != NULL)
   {
      return 1;
   }

   return 0;
}

char is_rem (char *str)
{
   /* printf ("is_rem\n");  */
   while (isspace (*str))
      str++;
   if (strstr (str, "rem") == str)
      return 1;
   return 0;
}

char is_blank (char *str)
{
   /* printf ("is_blank\n");  */
   while (isspace (*str))
      str++;
   if (*str == 0)
      return 1;
   return 0;
}

char is_uncond_br (char *str)
{
   /* printf ("is_uncond_br\n"); */
   if (is_branch (str) && (find_word (str, "if") == NULL))
      return 1;
   return 0;
}

char is_cond_br (char *str)
{
   /* printf ("is_cond_br\n"); */
   /* if (is_branch (str) && (find_word (str, "if") != NULL)) */
   /* if 1st word is if it's a conditional branch */
   /*
   while (isspace (*str))
      str++;
   if (str == find_word (str, "if"))
      return 1;
   */
   /* if 1st word is if and there's a goto 
      it's a conditional branch */
   if (is_branch (str))
   {
       while (isspace (*str))
          str++;
       if (str == find_word (str, "if"))
          return 1;
   }
   return 0;
}

char is_label (char *str)
{
   /* printf ("is_label\n");  */
   while (isspace (*str))
      str++;
   if (*str == ':')
      return 1;
   return 0;
}

void del_line (char **ca, int line_no)
{
   int i = 0;

   /* printf ("del_line\n");  */
   /* free (ca [line_no]); */
   /* if (strstr(ca[line_no], ":batch_end") != NULL)
       return; */

   for (i = line_no; i < code_lines; i++)
      ca [i] = ca [i+1];
   code_lines--;
}

char *get_label_def (char *str)
{
   static char label [TEXTLEN];
   char *lp;

   /* printf ("get_label_def\n");  */
   lp = strchr (str, ':');
   lp++;
   sscanf (lp, "%s", label);
   return &label [0];
}

char *get_label_ref (char *str)
{
   static char label [TEXTLEN];
   char *lp;

   /* printf ("get_label_ref\n");  */
   lp = strstr (str, "goto");
   lp+=4;
   sscanf (lp, "%s", label);
   return &label [0];
}

char negate (char **str)
{
   char text [TEXTLEN];
   char *lp;

   /* printf ("negate\n");  */
   if ((lp = strstr (*str, "not")) == NULL)
   {
      lp = strstr (*str, "if");
      lp += 2;
      /* *(lp - 1) = NULL; */
      sprintf (text, "%s%s", "if not", lp);
   }
   else
   { 
      lp+=3;
      sprintf (text, "%s%s", "if", lp);
   }
   *str = (char *) realloc (*str, sizeof (char) * (strlen (text) + 1));
   if (*str == NULL)
      return 1;
   strcpy (*str, text);
   return 0;
}

char reref_labs (char **ca, char *newlab, char *oldlab)
{
   int i;
   char *lp;
   char text [TEXTLEN];

   /* change references to oldlab to references to newlab */

   /* printf ("reref_labs\n");  */
   if (newlab == NULL || oldlab == NULL)
      return 1;
   for (i = 0; i < code_lines; i++)
   {
      if ((lp = find_word (ca[i], oldlab)) != NULL && is_branch (ca [i]))
      {
         *lp = 0;
         sprintf (text, "%s%s", ca [i], newlab);
         ca [i] = (char *)realloc (ca [i], \
                                      sizeof (char) * (strlen (text) + 1));
         if (ca [i] == NULL)
         {
            fprintf (stderr, "reref failed\n");
            return 1;
         }
         strcpy (ca [i], text);
      }
   }
   if ((i = find_label (newlab)) != -1)
      (labels [i]).refd = 1;
   if ((i = find_label (oldlab)) != -1)
      (labels [i]).refd = 0;
   return 0;
}

char check_labels (void)
{
   int i;
   char result = 1;

   for (i = 0; i < max_labels; i++)
   {
      if (labels[i].refd == 1 && labels[i].defd == 0)
      {
         fprintf (stderr, "label %s referenced but not defined\n", labels[i].label);
         result = 0;
      }
   }
   return result;
}

int cn_count (code_list_t *code)
{
   int result = 0;

   while (code != NULL)
   {
      result++;
      code = code->next;
   }

   return result;
}

char is_esr (char *lab)
{
   if (strcmp(lab, ":eof") == 0)
       return 1;

   if (strstr (lab, END_SR_PFX) == NULL)
      return 0;

   return 1;
}
