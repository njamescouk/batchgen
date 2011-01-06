#include <stdio.h>
#include <stdlib.h>
#include "batchgen.h"
#include "stacks.h"

#define STACK_INCR 50

int w_stk_ptr = 0,
    s_stk_ptr = 0;

int in_while = 0, in_switch = 0;

code_list_t **while_stack = NULL,
            **switch_stack = NULL;

int s_stk_sz = 0,
    w_stk_sz = 0;

char *what_are_we_in_stk = NULL;
int wawi_stk_sz = 0;
int wawi_stk_ptr = 0;
enum {WHILE = 1, SWITCH};

void stack_init (void)
{
   what_are_we_in_stk = more_chars ();
   wawi_push (0);
   if ((while_stack = more_whiles ()) == NULL)
   {
      perror ("no more whiles");
      return;
   }
   switch_stack = more_switches ();
   wpush (NULL);
   in_while--; 
   wawi_stk_ptr--;
   spush (NULL);
   in_switch--;
   wawi_stk_ptr--;
}

void wpush (code_list_t *item)
{
   if (w_stk_ptr > w_stk_sz - 5)
      more_whiles ();
   *(while_stack + w_stk_ptr) = item;
   w_stk_ptr++;
   in_while++;
   wawi_push (WHILE);
}

void spush (code_list_t *item)
{
   if (s_stk_ptr > s_stk_sz - 5)
      more_switches ();
   *(switch_stack + s_stk_ptr) = item;
   s_stk_ptr++;
   in_switch++;
   wawi_push (SWITCH);
}


void wawi_push (char item)
{
   if (wawi_stk_ptr > wawi_stk_sz - 5)
      more_chars ();
   *(what_are_we_in_stk + wawi_stk_ptr) = item;
   wawi_stk_ptr++;
}

code_list_t **more_whiles (void)
{
   w_stk_sz += STACK_INCR;
   return (code_list_t **)realloc (while_stack,\
                                w_stk_sz * sizeof (code_list_t *));
}

code_list_t **more_switches (void)
{
   s_stk_sz += STACK_INCR;
   return (code_list_t **)realloc (switch_stack,\
                                s_stk_sz * sizeof (code_list_t *));
}

char *more_chars (void)
{
   wawi_stk_sz += STACK_INCR;
   return (char *)realloc (what_are_we_in_stk,\
                                wawi_stk_sz * sizeof (char));
}

code_list_t *wpop (void)
{
   if (w_stk_ptr < 0)
      return NULL;
   w_stk_ptr--;
   in_while--;
   wawi_pop ();
   return *(while_stack + w_stk_ptr);
}

code_list_t *spop (void)
{
   if (s_stk_ptr < 0)
      return NULL;
   s_stk_ptr--;
   in_switch--;
   wawi_pop ();
   return *(switch_stack + s_stk_ptr);
}

char *wawi_pop (void)
{
   if (wawi_stk_ptr < 0)
      return NULL;
   wawi_stk_ptr--;
   return (what_are_we_in_stk + wawi_stk_ptr);
}

code_list_t *to_ws (void)
{
   if (w_stk_ptr < 0)
      return NULL;
   return *(while_stack + w_stk_ptr - 1);
}

code_list_t *to_ss (void)
{
   if (s_stk_ptr < 0)
      return NULL;
   return *(switch_stack + s_stk_ptr - 1);
}

char to_wawi_stk (void)
{
   if (wawi_stk_ptr < 0)
      return 0;
   return *(what_are_we_in_stk + wawi_stk_ptr - 1);
}


code_list_t *top_cur_stk (void)
{
   if (to_wawi_stk () == WHILE)
      return to_ws ();
   else if (to_wawi_stk () == SWITCH)
      return to_ss ();
   else
      return NULL;
}

int inwhile (void)
{
   return in_while;
}

int inswitch (void)
{
   return in_switch;
}
