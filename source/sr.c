#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "batchgen.h"

#pragma warning( disable : 4996 )

int sr_no = 0;
int num_sr = 0;
char in_sr = 0;
int sr_call_count = 0;
code_list_t **srcode = NULL;
char **srnames = NULL;

char is_func (char *sought)
{
   char i;

   for (i = 0; i < num_sr; i++)
      if (strcmp (srnames [i], sought) == 0)
         return i;
   return -1;
}

char *find_func (int func_number)
{
   if (func_number < 0 || func_number > num_sr)
       return 0;

   return srnames[func_number];
}

void install_func (char *name)
{
   srnames = (char **) realloc (srnames, (num_sr + 1) * sizeof (char *));
   srnames [num_sr] = (char *) calloc (strlen (name) + 1, sizeof (char));
   strcpy (srnames [num_sr], name);
   num_sr++;
}

char add_srcode (char *name, code_list_t *code)
{
   /* form code rem sub routine
                :<name>
                sr code stmts  (in code)
                rem end sub routine
                goto :eof
   */
   int sr_no = is_func (name);
   static int sr_alloced = 0;
   code_list_t *labelled_code = new_code_node ();
   char beginlabel [80],
        *endlabel = beginlabel;

   sprintf (beginlabel, "rem sub routine\n:%s\n", name);
   add_string (labelled_code, beginlabel);
   code = code_join (2, labelled_code, code);
   labelled_code = new_code_node ();
   sprintf (endlabel, "rem end sub routine\ngoto :eof\n\n");
   add_string (labelled_code, endlabel);
   code = code_join (2, code, labelled_code);
   if (sr_no != -1)
   {
      if (sr_no >= sr_alloced)
      {
         srcode = (code_list_t **) realloc (srcode, \
                              (num_sr + 1) * sizeof (code_list_t *));
         sr_alloced++;
      }
      srcode [sr_no] = code;
      return 1;
   }
   return 0;
}
