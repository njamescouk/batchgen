#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "batchgen.h"
#include "bkpatch.h"

#pragma warning( disable : 4996 )

goto_list_t *makelist (code_list_t *goto_node)
{
   /* return a pointer to a new goto_list pointing at the code
      of the goto node. 
   */
   goto_list_t *result;

   result = (goto_list_t *) calloc (1, sizeof (goto_list_t));
   if (result == NULL)
   {
      perror ("unable to allocate memory in makelist()");
      return NULL;
   }
   result->labelptr = &(goto_node->code);
   result->next = NULL;
   return result;
}

goto_list_t *merge (goto_list_t *l1, goto_list_t *l2)
{
   goto_list_t *head = l1;

   if (l1 == NULL)
      return l2;
   while (l1->next != NULL)
      l1 = l1->next;
   l1->next = l2;
   return head;
}

void backpatch (goto_list_t *goto_list, int label)
{
   char *textptr = NULL,
        text [80];

   sprintf (text, "%04d\n", label);
   textptr = (char *)calloc (strlen (text) + 1, sizeof (char));
   if (textptr == NULL)
   {
      perror ("unable to allocate memory in backpatch");
      return;
   }
   strcpy (textptr, text);
   while (goto_list != NULL)
   {
      *(goto_list->labelptr) = textptr;
      goto_list = goto_list->next;
   }
}

void backpatch_str (goto_list_t *goto_list, char *label)
{
   char *textptr = NULL;

   textptr = (char *)calloc (strlen (label) + 1, sizeof (char));
   if (textptr == NULL)
   {
      perror ("unable to allocate memory in backpatch");
      return;
   }
   strcpy (textptr, label);
   while (goto_list != NULL)
   {
      *(goto_list->labelptr) = textptr;
      goto_list = goto_list->next;
   }
}
