%{
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <io.h>
#include <string.h>
#include "batchgen.h"
#include "bkpatch.h"
#include "stacks.h"
#include "sr.h"
/* #include "optim.h" */

#pragma warning( disable : 4996 )

#define YYSTACKSIZE 5000
extern char *yytext;

int lineno = 1;
int newlabel = 0;
int newcaselabel = 0;
int newwhilelabel = 0;
int newswitchlabel = 0;
int newiflabel = 0;
int newcondlabel = 0;
int new_sr_return = 0;

%}

%union
{
   code_list_t *code_node;
   expr_t *expr_node;
   int integer;
} 

%token LEXERROR
%token FDEF
%token identifier
%token func_id
%token en_var
%token param
%token ERRORLEVEL
%token GE
%token EXIST
%token EQ
%token NE
%token number
%token empty
%token dos_command
%token CASE
%token DEFAULT
%token IF
%token SWITCH
%token WHILE
%token BREAK
%token RETURN
%token ELSE
%token LOG_OR
%token LOG_AND

%type <code_node> statement
%type <code_node> statement_list
%type <code_node> selection_statement
%type <code_node> while_statement
%type <code_node> jump_statement
%type <code_node> compound_statement
%type <code_node> labelled_statement
%type <code_node> function_call
%type <code_node> function_definition
%type <expr_node> dos_expression
%type <expr_node> primary_expression
%type <expr_node> dos_logical_expression
%type <expr_node> identifier
%type <expr_node> en_var
%type <expr_node> param
%type <expr_node> number
%type <expr_node> empty
%type <expr_node> logical_AND_expression
%type <expr_node> unary_expression
%type <integer> function_identifier

%%

batch_file
   : statement_list
   {
      /*
         code pointed to by $1.code.
         append batchend label for
         return statements
      */
      code_list_t *end = new_code_node (),
                  *begin = new_code_node ();

      add_string (begin, ":main\n");
      add_string (end, ":"END_LABEL"\n");
      cl = code_join (3, begin, $1, end);
      return yynerrs;
   }
   ;
    
statement
   : dos_command
   {
      /*
          dos_command
          batch file statements, copy yytext to $$.code
       */

       $$ = new_code_node ();
       add_string ($$, yytext);
       $$->next = new_code_node ();
       add_string ($$->next, "\n");
   }
   | compound_statement
   | selection_statement
   | while_statement
   | labelled_statement
   | jump_statement
   | function_definition
   {
     /* function definition reduced */
     $$ = new_code_node ();
     add_string ($$, "");
   }
   | function_call
   {
      /* function_call reduced */
      $$ = $1;
   }
   | error {fprintf (stderr, "error near line %d\n", lineno);
            if (yydebug)
               printf ("error near line %d\n", lineno);
           }
   ;

function_definition
   : FDEF identifier
   {
      $2 = new_expr ();
      add_text ($2, yytext);
   }
   '(' ')'
   {
      /* function definition: fdef identifier () ... */

      char errstr [] = "error: cannot define function "
                               "from within function at line %d\n";

      if (in_sr)
      {
         yyerror ("");
         yyerrok;
         if (yydebug)
            printf (errstr, lineno);
         fprintf (stderr, errstr, lineno);
         in_sr--;
         return 1; 
      }
      in_sr++;
      install_func ($2->expr_code->code);
   }
   compound_statement
   {
      /* function definition: ... {}; */
      /* deal with function definition code */
   
      if (add_srcode ($2->expr_code->code, $7) != 0)
         in_sr--;
      else
      {
         fprintf (stderr, "error adding sub routine code at line %i\n", \
                                                     lineno);
         return 1;
      }
   
   }
   ;

function_call
   : function_identifier '(' ')'
   {  
      /* function call
         form code call :SR_PFX<sr_no>
      */
      char label [80],
           code [TEXTLEN];
      char errstr [] = "error: cannot call function "
                               "from within function at line %d\n";
      char *func_name = find_func ($1);
      if (func_name == 0)
      {
         yyerror("function not found");
         yyerrok;
         if (yydebug)
            printf (errstr, lineno);
         fprintf (stderr, errstr, lineno);
         return 1; 
      }

      if (in_sr)
      {
         yyerror ("");
         yyerrok;
         if (yydebug)
            printf (errstr, lineno);
         fprintf (stderr, errstr, lineno);
         in_sr--;
         return 1; 
      }

      sprintf (code, "call :%s\n", func_name);

      $$ = new_code_node ();
      add_string ($$, code);
      sr_call_count++;
   }
   ;

labelled_statement
   : CASE primary_expression ':' statement
   {
      code_list_t *sw_code = to_ss (),
                  *label_def = new_code_node ();
      int label_no = newcaselabel++;
      char label [TEXTLEN], text [TEXTLEN];
       
      /*
         case: check we are in a switch
         forms code: rem case
                     if not <switch_code> == <primary_expr> goto <label>
                     statement
                     rem end case
                     :<label>
                     
      */
      sprintf (label, END_CASE_PFX"%d", label_no);
      if (inswitch ())
      {
         $$ = new_code_node ();
         sprintf (text, "rem case\nif not \"%s\" == \"%s\" goto %s\n",\
                              sw_code->code, $2->expr_code->code, label);
         add_string ($$, text);
         sprintf (text, "rem end case\n:%s\n", label);
         add_string (label_def, text);
         code_join (3, $$, $4, label_def);
      }
      else
      {
         fprintf (stderr, "case outside switch statement at line %d\n",lineno); 
         return 1;
      }
    }

   | DEFAULT ':' statement
   {
      /*
          default: check we are in a switch
          store code in switch.next
       */
      code_list_t *sw_code = to_ss ();

      if (inswitch ())
      {
         if (sw_code == NULL)
         {
            fprintf (stderr, "switch code does not exist at line %i\n", lineno);
            return 1;
         }
         sw_code->next = $3;
      }
      else
      {
         fprintf (stderr, "default outside switch statement at line %d\n",\
                                                          lineno); 
         return 1;
      }
    }
   ;
               
compound_statement
   : '{' statement_list '}'
   {
      /*
         compound statement
         code is in statement list
      */
      $$ = $2;
   }
   | '{' '}'
   {
      /* insert rem statement */
      $$ = new_code_node ();
      add_string ($$, "rem\n");
    }
    ;

statement_list
    : statement
    {
       /*
          statement
          code is in statement
       */
       $$ = $1;
    }
    | statement_list statement
    {
       /*
          statement_list statement
          append code for statement to statement list code
       */
       $$ = $1;
       code_join (2, $$, $2);
     }
     ;

selection_statement
   :
   IF '(' dos_expression ')' statement
   {
      /*
         IF ( expr ) stmt
            
         get 2 new labels for true + false exits of if
         backpatch true label into dos expr true list
         false label into dos expr false list

         join code as follows:-
         dos_expr -> ['L_', truelabel] -> stmt.code ->
         ['L_', falselabel]

         $$ points to dos_expr.code

         forms code: dos_expr_code
                     :<true_label>
                     statement
                     rem endif
                     :<false_label>
      */

      int label_no = newiflabel++;
      code_list_t *trueList = new_code_node (),
                  *falseList = new_code_node ();
      char text [TEXTLEN],
           true_label [80],
           false_label [80];

      sprintf (true_label, IF_PFX"%i\n", label_no);
      sprintf (false_label, ENDIF_PFX"%i\n", label_no);

      backpatch_str ($3->truelist, true_label);
      backpatch_str ($3->falselist, false_label);

      if (trueList != NULL && falseList != NULL)
      {
         sprintf (text, ":%s", true_label);
         add_string (trueList, text);
         sprintf (text, "rem endif\n:%s", false_label);
         add_string (falseList, text);
         code_join(4,$3->expr_code,trueList,$5,falseList);
         $$ = $3->expr_code;
      }
      else
      {
         perror ("cannot allocate memory");
         return 1;
      }
   }
   | IF '(' dos_expression ')' statement ELSE statement
   {
      /*
         IF ( expr ) stmt else stmt
                            
         get 3 labels, true, false and end.
         backpatch true into dos_expr.truelist, false into
         dos_expr.falselist.

         join code as follows:-
         dos_expr -> ['L_', true] -> $5.code ->
         ['goto', end] -> [':L_', false] -> $7.code ->
         [':L_', end]

         $$ points to this list

         forms code: dos_expr_code
                     :<true_label>
                     statement
                     goto <end_label>
                     rem else
                     :<false_label>
                     statement
                     rem endif
                     :<end_label>
         */
         int label_no = newiflabel++;
         code_list_t *trueList = new_code_node (),
                     *falseList = new_code_node (),
                     *end = new_code_node ();
         char text [TEXTLEN],
              true_label [80],
              false_label [80],
              end_label [80];

         sprintf (true_label, IF_PFX"%i\n", label_no);
         sprintf (false_label, ELSE_PFX"%i\n", label_no);
         sprintf (end_label, ENDIF_PFX"%i\n", label_no);

         backpatch_str ($3->truelist, true_label);
         backpatch_str ($3->falselist, false_label);


         if (trueList != NULL && falseList != NULL && end != NULL)
         {
            sprintf (text, ":%s", true_label);
            add_string (trueList, text);
            sprintf (text, "\ngoto %srem else\n:%s", end_label, false_label);
            add_string (falseList, text);
            sprintf (text, "rem endif\n:%s", end_label);
            add_string (end, text);
            code_join (6, $3->expr_code, trueList, $5, falseList, $7, end);
            $$ = $3->expr_code;
         }
         else
         {
            perror ("cannot allocate memory");
            return 1;
         }
      }
      | SWITCH '(' primary_expression
      {
         /* stack first half of test code */

         code_list_t *sw_code = new_code_node ();

         add_string (sw_code, $3->expr_code->code);
         spush (sw_code);
      }

      ')' statement

      {
         /* switch:
         form code: rem switch
                    statement
                    rem default
                    default code (if any)
                    rem end default
                    :<label>

         */
         code_list_t *breaks = to_ss (),
                     *labeldef = new_code_node (),
                     *remsw = new_code_node (),
                     *remdef = new_code_node (),
                     *remedef = new_code_node (),
                     *default_code = spop ();
         int label_no = newlabel++;
         char text [TEXTLEN],
                label [80];
           
           default_code = default_code->next;

           sprintf (label, END_SWITCH_PFX"%i\n", label_no);

           backpatch_str (breaks->gotos, label);
           sprintf (text, ":%s", label);
           add_string (labeldef, text);
           sprintf (text, "rem switch\n");
           add_string (remsw, text);
           sprintf (text, "rem default\n");
           add_string (remdef, text);
           sprintf (text, "rem end default\n");
           add_string (remedef, text);
           $$ = code_join (6, remsw, $6, remdef, default_code, remedef, labeldef);
        }
      ;

            
while_statement
   : WHILE
   {
      /*
         push a code node onto wstack and flag the fact
         that we are in a while.
      */
      code_list_t *breaks = new_code_node ();

      breaks->gotos = makelist (breaks);
      /* use this to backpatch breaks in whiles & switches */ 
      wpush (breaks);
   }
           
   '(' dos_expression ')' statement
   {
      /*
         get 3 labels, true, false + begin
         backpatch true into dos_expr.truelist, false into
         dos_expr.falselist
         backpatch false into statement.nextlist.
         join code as follows:-
           [':L_', begin]->dos_expr.code->[':L_', true]->
           $5.code->['goto ', begin]->[':L_', false]
         $$ points to this list
         backpatch breaks

         form code: rem while
                    :<begin_label>
                    dos_expr
                    :<true_label>
                    statement
                    goto <begin_label>
                    rem endwhile
                    :<false_label>

      */

      int label_no = newwhilelabel++;
      code_list_t *trueList = new_code_node (),
                  *falseList = new_code_node (),
                  *begin = new_code_node (),
                  *breaks = to_ws ();
      char text [TEXTLEN],
           begin_label [80],
           true_label [80],
           false_label [80];

      sprintf (begin_label, WHILE_PFX"%i\n", label_no);
      sprintf (true_label, WHILE_BODY_PFX"%i\n", label_no);
      sprintf (false_label, ENDWHILE_PFX"%i\n", label_no);

      backpatch_str ($4->truelist, true_label);
      backpatch_str ($4->falselist, false_label);
      backpatch_str (breaks->gotos, false_label);

      if (trueList != NULL && falseList != NULL && begin != NULL)
      {
         sprintf (text, "rem while\n:%s", begin_label);
         add_string (begin, text);
         sprintf (text, ":%s", true_label);
         add_string (trueList, text);
         sprintf (text, "goto %srem endwhile\n:%s", begin_label, false_label);
         add_string (falseList, text);
         $$ = code_join (5, begin, $4->expr_code, trueList, $6, falseList);
         wpop ();
      }
      else
      {
         perror ("cannot allocate memory");
         return 1;
      }
   } 
   ;

           
jump_statement
   : BREAK ';'
   {
      /*
         break: check we are in a while or a switch. if so find out which one
         and merge it and the label code. join code
 
         form code: rem break
                   goto <label> (to be backpatched - either endwh|endsw)
      */
      code_list_t *false_exit = top_cur_stk (),
                 *label = new_code_node ();

      if (inwhile () || inswitch ())
      {
         $$ = new_code_node ();
         label->gotos = makelist (label);
         false_exit->gotos = merge (false_exit->gotos, label->gotos);
         add_string ($$, "rem break\ngoto ");
         code_join (2, $$, label);
      }
      else
      {
         fprintf (stderr,"break outside while or switch at line %d\n",lineno);
         return 1;
      }
   }
   | RETURN ';'
   {
      $$ = new_code_node ();
      if (in_sr)
         add_string ($$, "goto :eof\n");
      else
         add_string ($$, "goto batch_end\n");
   }
   | RETURN primary_expression ';'
   {
      char text [TEXTLEN];
                                 
      $$ = new_code_node ();
      sprintf (text, "exit /b %s\n", $2->expr_code->code);
      add_string ($$, text);
   }
   ;
               
dos_expression
   : logical_AND_expression
   {
      $$ = $1;
   }
   | dos_expression LOG_OR logical_AND_expression
   {
      /*
         logical or
                       
         get a label for false exit.
         backpatch false into $1.falselist
         merge $1.truelist with $3.truelist & point $$.truelist
         at this list, $$.falselist = $3.falselist

         form code: dos_expr
                    :<falselabel>
                    log_and
      */

      int label_no = newcondlabel++;
      char false_label [80];
      code_list_t *label_def = new_code_node ();
      char text [TEXTLEN];

      sprintf (false_label, OR_FALSE_PFX"%i\n", label_no);

      sprintf (text, ":%s", false_label);
      add_string (label_def, text);
      backpatch_str ($1->falselist, false_label);
      $$ = new_expr ();
      $$->truelist = merge ($1->truelist, $3->truelist);
      $$->falselist = $3->falselist;
      $$->expr_code = code_join \
                         (3, $1->expr_code, label_def, $3->expr_code);
   }
   ;
               
logical_AND_expression
   : unary_expression
   {
      $$ = $1;
   }
   | logical_AND_expression LOG_AND unary_expression
   {
      /*
         logical and
         
         get a label for true exit and backpatch it into $1.truelist.
         $$.truelist = merge ($1.truelist, $3.truelist)
         $$.falselist = $3.falselist

         form code: log_and
                    :<true_label>
                    unary_expr
      */
                            
      int label_no = newcondlabel++;
      char true_label [80];
      code_list_t *label_def = new_code_node ();
      char text [TEXTLEN] ;
        
      sprintf (true_label, AND_TRUE_PFX"%i\n", label_no);
      sprintf (text, ":%s", true_label);
      add_string (label_def, text);
      backpatch_str ($1->truelist, true_label);
      $$ = new_expr ();
      $$->falselist = merge ($1->falselist, $3->falselist);
      $$->truelist = $3->truelist;
      $$->expr_code = code_join (3, $1->expr_code, label_def, $3->expr_code);
   }
   ;

unary_expression
   : dos_logical_expression
   {
      $$ = $1;
   }
   | '(' dos_expression ')'
   {
      $$ = $2;
   }
   | '!' unary_expression
   {
      /* not unary_expr */
      $$ = new_expr ();
      $$->truelist = $2->falselist;
      $$->falselist = $2->truelist;
      $$->expr_code = $2->expr_code;
   }
   ;
   
dos_logical_expression
   : ERRORLEVEL GE primary_expression
   {
      char text [TEXTLEN] ;

      $$ = new_expr ();
      sprintf (text, "if errorlevel %s goto ", $3->expr_code->code);
      if (make_expr_code (text, $$) == NULL)
         return 1;
   } 
   | ERRORLEVEL '<' primary_expression
   {
      char text [TEXTLEN] ;

      $$ = new_expr ();
      sprintf (text, "if not errorlevel %s goto ", $3->expr_code->code);
      if (make_expr_code (text, $$) == NULL)
         return 1;
   } 

   | ERRORLEVEL EQ primary_expression
   {
      char text [TEXTLEN] ;

      $$ = new_expr ();
      sprintf (text, "if errorlevel = %s goto ", $3->expr_code->code);
      if (make_expr_code (text, $$) == NULL)
         return 1;
   } 

   | ERRORLEVEL NE primary_expression
   {
      char text [TEXTLEN] ;

      $$ = new_expr ();
      sprintf (text, "if not errorlevel = %s goto ", $3->expr_code->code);
      if (make_expr_code (text, $$) == NULL)
         return 1;
   } 

   | EXIST primary_expression
   {
      char text [TEXTLEN] ;

      $$ = new_expr ();
      sprintf (text, "if exist %s goto ", $2->expr_code->code);
      if (make_expr_code (text, $$) == NULL)
         return 1;
   }
   | primary_expression EQ primary_expression
   {
      char text [TEXTLEN] ;

      $$ = new_expr ();
      sprintf (text, "if \"%s\" == \"%s\" goto ", \
                               $1->expr_code->code, $3->expr_code->code);
      if (make_expr_code (text, $$) == NULL)
         return 1;
   }
   | primary_expression NE primary_expression
   {
      char text [TEXTLEN] ;

      $$ = new_expr ();
      sprintf (text, "if not \"%s\" == \"%s\" goto ", \
                               $1->expr_code->code, $3->expr_code->code);
      if (make_expr_code (text, $$) == NULL)
         return 1;
   }
   ;

primary_expression
   : identifier
   {
      /* identifier */
      $$ = new_expr ();
      add_text ($$, yytext);

   }
   | primary_expression identifier
   {
        expr_t *id = new_expr();

      /* primary_expression identifier */
        if (id != NULL)
            add_text (id, yytext);
      if (concat_text ($1, id) == 0)
         $$ = $1;
      else
         return 1;
   }
   | en_var
   {
      /* environmental variable */
      $$ = new_expr ();
      add_text ($$, yytext);
   }
   | primary_expression en_var
   {
        expr_t *ev = new_expr();

        /* primary_expression en_var */
        if (ev != NULL)
            add_text (ev, yytext);
        else
            return 1;
        if (concat_text ($1, ev) == 0)
            $$ = $1;
        else
            return 1;
    }
    | param
    {
        /* parameter */
        $$ = new_expr ();
        add_text ($$, yytext);
    }
    | primary_expression param
    {
        expr_t *par = new_expr();

      /* primary_expression param */
        if (par != NULL)
            add_text (par, yytext);
        else
            return 1;
        if (concat_text ($1, par) == 0)
            $$ = $1;
        else
            return 1;
    }
    | number
    {
        /* number */
        $$ = new_expr ();
        add_text ($$, yytext);
    }
   | primary_expression number
    {
        expr_t *num = new_expr();

        /* primary_expression number */
        if (num != NULL)
            add_text (num, yytext);
        else
            return 1;
        if (concat_text ($1, num) == 0)
         $$ = $1;
      else
         return 1;
   }
   | empty
   {
      $$ = new_expr ();
      add_text ($$, "");
   }
   ;

function_identifier
   : func_id
   {
      $$ = is_func (yytext);
   }

%%

int yyerror (char *s)
{
   fprintf (stderr, "%s\n", s);
   return 0;
}

code_list_t *new_code_node (void)
{
   return (code_list_t *)calloc (1, sizeof (code_list_t));
}

expr_t *new_expr (void)
{
   return (expr_t *)calloc (1, sizeof (expr_t));
}

char add_string (code_list_t *node, char *string)
{
   node->code = (char *)realloc (node->code, \
                                        (strlen(string)+1)*sizeof(char));
   if (node->code == NULL)
      return 1;
   strcpy (node->code, string);
   return 0;
}

char add_text (expr_t *node, char *string)
{
   node->expr_code = new_code_node ();
   if (node->expr_code == NULL)
      return 1;
   if (add_string (node->expr_code, string) != 0)
      return 2;
   return 0;
}

char concat_text (expr_t *n1, expr_t *n2)
{
   /* append code in n2 to code in n1 */
   char text [TEXTLEN];
   char result = 0;

   if (strlen (n1->expr_code->code) + \
                                   strlen (n2->expr_code->code) < TEXTLEN)
   {
      strcpy (text, n1->expr_code->code);
      strcat (text, n2->expr_code->code);
      add_text (n1, text);
   }
   else
   {
      fprintf (stderr, "text too long in concat_text\n");
      result = 1;
   }
   return result;
}

code_list_t *code_join (int n, ...)
{
   va_list argptr;
   code_list_t *curlist;
   code_list_t *result;
   
   va_start (argptr, n);
   if (n <= 1)
      return NULL;
   result = curlist = va_arg (argptr, code_list_t *);
   while (n - 1)
   {
      while (curlist->next != NULL)
         curlist = curlist->next;
      curlist->next = va_arg (argptr, code_list_t *);
      n--;
   }
   va_end (argptr);
   return result;
}

void emit (code_list_t *c1, FILE *fp)
{
   while (c1 != NULL)
   {
      fprintf (fp, "%s", c1->code);
      c1 = c1->next;
   }
}

code_list_t *make_expr_code (char *text, expr_t *expr)
{
   /*
      called on reduction by dos_logical_expr
      forms code: if <dle> goto <true>
                  goto <false>

   */
   code_list_t *trueList = new_code_node ();
   code_list_t *falseList = new_code_node ();
   code_list_t *gto = new_code_node ();

   if (trueList != NULL && falseList != NULL && gto != NULL)
   {
      if (add_text (expr, text) != 0)
      {
         perror ("unable to make expr code");
         return NULL;
      }
      if (add_string (gto, "goto ") != 0)
      {
         perror ("unable to make expr code");
         return NULL;
      }
      code_join (4, expr->expr_code, trueList, gto, falseList);
      expr->truelist = makelist (trueList);
      expr->falselist = makelist (falseList);
      return expr->expr_code;
   }
   else
   {
      perror ("memory allocation failed");
      return NULL;
   }
}  

                         
#ifdef YACC_DEBUG
void main (void)
{
   int c;
   
   while (c = yyparse ())
      printf ("\nyyparse returns int %d =  char %c\n\n", c, c);
}
#endif
