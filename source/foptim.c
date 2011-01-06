#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "batcomp.h" 
#include "foptim.h"
#include "sr.h"
#include "C:\usr\NIK\WORK\UTIL\CUTILS\filecopy.h"
#include "C:\usr\NIK\work\edit\edit.h"

char *strdup(const char *s);

#define END_OF_LIST -1

label_detail_t *labels = NULL;
int code_lines;
int max_labels = 0;
int num_labels = 0;
int label_incr = 50;
char remove_rems = 0;
char remove_blanks = 0;
/* char **ca; */

#ifndef STANDALONE

extern FILE *ofp;
static code_list_t *clptr;
static char *codeptr;

int list_line_count (code_list_t *cl)
{
   int res = 0;
   char *cp = NULL;

   while (cl != NULL)
   {
      cp = cl->code;
      while (*cp != NULL)
      {
         if (*cp == '\n')
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
   if (c != NULL)
      codeptr++;
   if (c == NULL)
   {
      if (clptr->next != NULL)
      {
         clptr = clptr->next;
         codeptr = clptr->code;
         c = *(codeptr);
         if (c != NULL)
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
   filecopy (argv [argc - 1],"bgo.bat");
   if (F_optimize () == 0)
   {
      fprintf (stderr, "optimize failed\n");
      if (system ("copy bgo.bat bco.tmp > nul") != 0)
         perror ("opt fail");
      if (system ("echo rem BAD FILE > bgo.bat") != 0)
         perror ("opt fail");
      if (system ("echo goto "DUD_FILE_LABEL" >> bgo.bat") != 0)
         perror ("opt fail");
      if (system ("type bco.tmp >> bgo.bat") != 0)
         perror ("opt fail");
      if (system ("echo :"DUD_FILE_LABEL">>bgo.bat") != 0)
         perror ("opt fail");
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

char F_get_labels ()
{
   int i;
   char text [TEXTLEN];
   char *lab_beg, result = 0;
   FILE *tmp = NULL, *optofp = NULL;
   char line [TEXTLEN] = "";
   /* char *lptr = line; */

   tmp = fopen (TMPFNAM, "wt");
   if (tmp == NULL)
   {
      perror ("F_reref");
      return 1;
   }
   optofp = fopen ("bgo.bat", "r+t");
   if (optofp == NULL)
   {
      perror ("F_reref");
      return 1;
   }

   /* printf ("get_labels\n");  */

   sprintf (text, "%%"RET_LABEL"%%");
   install_def (text);
   for (i = 0; i < sr_call_count && result == 0; i++)
   {
      sprintf (text, END_SR_PFX"%i", i);
      result = install_ref (text);
   }
   if (line == NULL)
   {
      perror ("F_get_labels");
      return 1;
   }
   while (fgets (line, TEXTLEN, optofp) != NULL)
   {
      if (is_label (line))
      {
         lab_beg = strchr (line, ':');
         lab_beg++;
         sscanf (lab_beg, "%s", text);
         result = install_def (text); 
      }
      else if (is_branch (line))
      {
         lab_beg = strstr (line, "goto");
         lab_beg += 4;
         sscanf (lab_beg, "%s", text);
         result = install_ref (text);
      }
   }
   fclose (tmp);
   fclose (optofp);
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

int F_remove_blanks (void)
{
   FILE *tmp = NULL, *oofp = NULL;
   char line [TEXTLEN];

   unlink (TMPFNAM);
   tmp = fopen (TMPFNAM, "wt");
   if (tmp == NULL)
   {
      perror ("F_reref");
      return -1;
   }
   oofp = fopen ("bgo.bat", "rt");
   if (oofp == NULL)
   {
      perror ("F_reref");
      return -1;
   }
   while (fgets (line, TEXTLEN, oofp) != NULL)
   {
      if (!is_blank (line))
         fprintf (tmp, "%s", line);
   }
   fclose (tmp);
   fclose (oofp);
   return filecopy (TMPFNAM, "bgo.bat");
}

int F_line_count (char *fname)
{
   FILE *tmp = NULL;
   char line [TEXTLEN];
   int result = 0;

   tmp = fopen (fname, "rt");
   if (tmp == NULL)
   {
      perror ("line_count");
      return -1;
   }
   while (fgets (line, TEXTLEN, tmp) != NULL)
      result++;
   fclose (tmp);
   return result;
}


int F_remove_rems (void)
{
   FILE *tmp = NULL, *oofp = NULL;
   char line [TEXTLEN];

   unlink (TMPFNAM);
   tmp = fopen (TMPFNAM, "wt");
   if (tmp == NULL)
   {
      perror ("F_remove_rems");
      return -1;
   }
   oofp = fopen ("bgo.bat", "rt");
   if (oofp == NULL)
   {
      perror ("F_remove_rems");
      return -1;
   }
   while (fgets (line, TEXTLEN, oofp) != NULL)
   {
      if (!is_rem (line))
         fprintf (tmp, "%s", line);
   }
   fclose (tmp);
   fclose (oofp);
   return filecopy (TMPFNAM, "bgo.bat");
}

char next_peep(char peep [PEEPSZ][TEXTLEN], int *end_of_file_head)
{
   char line [TEXTLEN];
   FILE *oofp = NULL;
   int lc = 0;

   oofp = fopen ("bgo.bat", "rt");
   if (oofp == NULL)
   {
      perror ("next_peep");
      return -1;
   }
   while ((fgets (line, TEXTLEN, oofp) != NULL) && lc < *end_of_file_head)
   {
      lc++;
   }
   *end_of_file_head = lc;
   if (fgets (line, TEXTLEN, oofp) != NULL)
   {
      perror ("next_peep");
      fclose (oofp);
      return 0;
   }
   else
   {
      strcpy (peep[0], peep[1]);
      strcpy (peep[1], peep[2]);
      strcpy (peep[2],line);
   }
   fclose (oofp);
   return 1;
}

char F_optimize ()
{
   int i, valid_lines = ROWS;
   int changed = 1;
   FILE *oofp = NULL; 
   int lcount = 0;
   /* char line [TEXTLEN]; */
   int page = 1;
   char re_read = 0; /* does the file have to be read inti buf from scratch */

   /* fprintf (stderr, "optimize      ");   */
   code_lines = F_line_count ("bgo.bat");
   oofp = fopen ("bgo.bat", "rt");
   strcpy (edit_file_name, "bgo.bat");
   if (oofp == NULL)
   {
      perror ("F_optimize");
      return -1;
   }
   if (F_get_labels () != 0)
   {
      fprintf (stderr, "get_labels failed\n");
      return 1;
   }
   if (remove_blanks)
   {
      code_lines = F_remove_blanks ();
      if (code_lines == -1)
      {
         fprintf (stderr, "remove_blanks failed\n");
         return 1;
      }
   }
   if (remove_rems)
   {
      code_lines = F_remove_rems ();
      if (code_lines == -1)
      {
         fprintf (stderr, "remove_rems failed\n");
         return 1;
      }
   }
   while (changed || re_read)
   {
      changed = 0;
      re_read = 0;
      for (page = 1;
           (valid_lines = goto_page (page, oofp)) > 0 && !re_read;
           page++)
      {
         for (i = 0; 
              i < min(ROWS, valid_lines) && !re_read; 
              i++) 
         {
            fprintf (stderr, "optimize %4i/%4i p. %2d pass %2d  \r", i, \
                                     min(ROWS, valid_lines) , page, lcount); 
            if (is_uncond_br (buf [i]) && i + 1 < min(ROWS, valid_lines))
            {
               changed += dead_code (i, valid_lines, page);
               changed += redund_goto (i);
            }
            else if (is_cond_br (buf [i]) && is_uncond_br (buf [i + 1]) \
                                            && i + 2 < min(ROWS, valid_lines))
               changed += jump_over_jump (i);
            else if (is_label (buf [i]) && i + 1 < min(ROWS, valid_lines))
            {
               /* eliminate duplicate labels and jumps to jumps */
               re_read = lablabjmpjmp (i);
            }
         }
         if (changed && !re_read)
         {
            write_file (page, valid_lines, oofp);
            re_read = 1;
         }

      }

      if (remove_blanks)
      {
         code_lines = F_remove_blanks ();
         if (code_lines == -1)
         {
            fprintf (stderr, "remove_blanks failed\n");
            return 1;
         }
      }
         
      for (i = 0; i < num_labels; i++)
      {
         if ((labels [i]).refd == 0)
            changed += F_del_unrefd_labs (labels[i].label);
      }

      if (changed)
      {
         num_labels = 0;
         if (F_get_labels () != 0)
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
      /* fclose (oofp); */
   }
   return 0;
}

char F_del_unrefd_labs (char *name)
{
   char result = 0;
   FILE *tmp = NULL, *oofp = NULL;
   char line [TEXTLEN], text [TEXTLEN];

   /* printf ("F_del_unrefd_labs\n");  */
   unlink (TMPFNAM);
   tmp = fopen (TMPFNAM, "wt");
   if (tmp == NULL)
   {
      perror ("F_unrefd_labs");
      return 0;
   }
   oofp = fopen ("bgo.bat", "rt");
   if (oofp == NULL)
   {
      perror ("F_unrefd_labs");
      return 0;
   }
   sprintf (text, ":%s", name);
   while (fgets (line, TEXTLEN, oofp) != NULL)
   {
      if (strstr (line, text) != NULL && is_label (line))
         result = 1;
      else
         fprintf (tmp, "%s", line);
   }
   fclose (tmp);
   fclose (oofp);
   code_lines = filecopy (TMPFNAM,"bgo.bat");
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
           && (isspace (c) || c == NULL)
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
      while (isspace (*str) && *str != NULL)
         str++;
      if (*str != '%')
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
   if (*str == NULL)
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
   if (is_branch (str) && (find_word (str, "if") != NULL))
      return 1;
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

void F_del_line (int line_no)
{
   int i;
   FILE *tmp = NULL, *oofp = NULL;
   char line [TEXTLEN];

   unlink (TMPFNAM);
   tmp = fopen (TMPFNAM, "wt");
   if (tmp == NULL)
   {
      perror ("F_del_line");
      return;
   }
   oofp = fopen ("bgo.bat", "rt");
   if (oofp == NULL)
   {
      perror ("F_del_line");
      return;
   }

   /* printf ("F_del_line\n");  */
   for (i = 0; i < line_no-1; i++)
      fprintf (tmp, "%s", fgets (line, TEXTLEN, oofp));
   fgets (line, TEXTLEN, oofp);
   while (fgets (line, TEXTLEN, oofp) != NULL)
      fprintf (tmp, "%s", line);
   fclose (tmp);
   fclose (oofp);
   code_lines = filecopy (TMPFNAM,"bgo.bat");
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

char negate (char *str)
{
   char text [TEXTLEN];
   char *lp;

   /* printf ("negate\n");  */
   if ((lp = strstr (str, "not")) == NULL)
   {
      lp = strstr (str, "if");
      lp += 2;
      /* *(lp - 1) = NULL; */
      sprintf (text, "%s%s", "if not", lp);
   }
   else
   { 
      lp+=3;
      sprintf (text, "%s%s", "if", lp);
   }
   /* *str = (char *) realloc (*str, sizeof (char) * (strlen (text) + 1)); */
   if (*str == NULL)
      return 1;
   strcpy (str, text);
   return 0;
}

char F_reref_labs (char *newlab, char *oldlab)
{
   int i;
   char *lp;
   /* char text [TEXTLEN]; */
   FILE *tmp = NULL, *oofp = NULL;
   char line [TEXTLEN];

   /* change references to oldlab to references to newlab */

   /* printf ("F_reref_labs\n");  */
   unlink (TMPFNAM);
   tmp = fopen (TMPFNAM, "wt");
   if (tmp == NULL)
   {
      perror ("F_reref");
      return 1;
   }
   oofp = fopen ("bgo.bat", "rt");
   if (oofp == NULL)
   {
      perror ("F_reref");
      return 1;
   }
   if (newlab == NULL || oldlab == NULL)
      return 1;
   while (fgets (line, TEXTLEN, oofp) != NULL)
   {
      if ((lp = find_word (line, oldlab)) != NULL && is_branch (line))
      {
         *lp = NULL;
         fprintf (tmp, "%s%s\n", line, newlab);
      }
      else
         fprintf (tmp, "%s", line);
   }
   if ((i = find_label (newlab)) != -1)
      (labels [i]).refd = 1;
   if ((i = find_label (oldlab)) != -1)
      (labels [i]).refd = 0;
   fclose (tmp);
   fclose (oofp);
   filecopy (TMPFNAM, "bgo.bat"); 
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
   if (strstr (lab, END_SR_PFX) == NULL)
      return 0;
   return 1;
}

char dead_code (int i, int valid_lines, int page)
{
   /* dead code elimination */
   char result = 0;

   while (!is_label (buf [i+1]) && i + 1 < min(ROWS, valid_lines))
   {
      fprintf (stderr, "%i/%i p. %d   \r", i, min(ROWS, valid_lines), page); 
      if (i+1<min(ROWS, valid_lines))
      {
         buf [i+1][0] = NULL;
         i++;
         result = 1;
      }
      else
         break;
   }
   return result;
}

char redund_goto (int i)
{
   /* redundant goto ? */
   char lab1 [TEXTLEN], lab2 [TEXTLEN], result = 0;;

   strcpy (lab1, get_label_ref (buf [i]));
   strcpy (lab2, get_label_def (buf [i+1]));
   if (strcmp (lab1, lab2) == 0)
   {
      buf [i][0] = NULL;
      result = 1;
   }
   return result;
}

char jump_over_jump (int i)
{  /* eliminate jumps over jumps */
   char lab1 [TEXTLEN], lab2 [TEXTLEN], lab3 [TEXTLEN];
   char *lp, newline [TEXTLEN];
   char result = 0;

   if (is_label (buf [i+2]))
   {
      strcpy (lab1, get_label_ref (buf [i]));
      strcpy (lab2, get_label_ref (buf [i+1]));
      strcpy (lab3, get_label_def (buf [i+2]));
      if (strcmp (lab1, lab3) == 0)
      {

         lp = strstr (buf [i], "goto");
         *lp = NULL;
         if (negate (buf [i]) != 0)
         {
            fprintf (stderr, "negate failed\n");
            return 1;
         }
         sprintf (newline, "%s%s", buf [i], buf [i+1]);
         strcpy (buf[i], newline);
         buf [i + 1][0] = NULL;
         result = 1;
      }
   }
   return result;
}

char lablabjmpjmp (int i)
{
   char lab1 [TEXTLEN] = "", lab2 [TEXTLEN] = "", result = 0;

   strcpy (lab1, get_label_def (buf [i]));
   if (is_label (buf [i+1]))
   {
      /* eliminate duplicate labels */
      strcpy (lab2, get_label_def (buf [i+1])); 
   }
   else if (is_uncond_br (buf [i+1]))
   {
      /* jump to jump */
      strcpy (lab2, get_label_ref (buf [i+1])); 
   }
   if (lab1[0] != NULL &&  lab2[0] != NULL)
      if (!(is_esr (lab1) || is_esr (lab2)))
      {
         if (F_reref_labs (lab2, lab1) != 0)
            return 1;
         result = 1;
      }
   return result;
}