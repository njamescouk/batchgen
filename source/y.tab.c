#ifndef lint
static char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define yyclearin (yychar=(-1))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING (yyerrflag!=0)
#define YYPREFIX "yy"
#line 2 "batchgen.y"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <io.h>
#include <string.h>
#include "batchgen.h"
#include "bkpatch.h"
#include "stacks.h"
/* #include "sr.h"
#include "optim.h" */

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

#line 28 "batchgen.y"
typedef union
{
   code_list_t *code_node;
   expr_t *expr_node;
   int integer;
} YYSTYPE;
#line 44 "y.tab.c"
#define LEXERROR 257
#define FDEF 258
#define identifier 259
#define en_var 260
#define param 261
#define ERRORLEVEL 262
#define GE 263
#define EXIST 264
#define EQ 265
#define NE 266
#define number 267
#define empty 268
#define dos_command 269
#define CASE 270
#define DEFAULT 271
#define IF 272
#define SWITCH 273
#define WHILE 274
#define BREAK 275
#define RETURN 276
#define ELSE 277
#define LOG_OR 278
#define LOG_AND 279
#define YYERRCODE 256
short yylhs[] = {                                        -1,
    0,    1,    1,    1,    1,    1,    1,    1,    7,    7,
    6,    6,    2,    2,    3,    3,   13,    3,   14,    4,
    5,    5,    5,    8,    8,   11,   11,   12,   12,   12,
   10,   10,   10,   10,   10,   10,   10,    9,    9,    9,
    9,    9,    9,    9,    9,    9,
};
short yylen[] = {                                         2,
    1,    1,    1,    1,    1,    1,    1,    1,    4,    3,
    3,    2,    1,    2,    5,    7,    0,    6,    0,    6,
    2,    2,    3,    1,    3,    1,    3,    1,    3,    2,
    3,    3,    3,    3,    2,    3,    3,    1,    2,    1,
    2,    1,    2,    1,    2,    1,
};
short yydefred[] = {                                      0,
    8,    2,    0,    0,    0,    0,   19,    0,    0,    0,
    0,   13,    0,    4,    5,    7,    3,    6,   38,   40,
   42,   44,   46,    0,    0,    0,    0,    0,   21,   22,
    0,   12,    0,   14,   39,   41,   43,   45,    0,   10,
    0,    0,    0,    0,    0,    0,   28,    0,   26,    0,
    0,   23,   11,    9,    0,    0,    0,    0,    0,    0,
   30,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   29,    0,    0,    0,    0,   27,    0,    0,
    0,   18,   20,   16,
};
short yydgoto[] = {                                      11,
   12,   13,   14,   15,   16,   17,   18,   45,   46,   47,
   48,   49,   67,   28,
};
short yysindex[] = {                                    -87,
    0,    0, -226,  -45,  -20,  -16,    0,  -30,  -56, -116,
    0,    0,  -87,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  -53,  -87,   -1, -226,  -15,    0,    0,
  -40,    0,  -95,    0,    0,    0,    0,    0,  -87,    0,
  -34, -226,   -1,   -1,  -27, -213,    0, -241,    0, -210,
   -1,    0,    0,    0, -226, -226, -226, -226, -210,  -26,
    0,   -1,  -87, -226, -226,   -1,    2,  -25, -210, -210,
 -210, -210,    0, -241, -237, -210, -210,    0,  -87,  -87,
  -87,    0,    0,    0,
};
short yyrindex[] = {                                      0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   56,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  -24,    0,   17,
    0,    0,    0,    0,    0,    0,    0,    0,  -41,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  -39,  -37,
  -35,  -33,    0,  -23,    1,  -31,  -29,    0,    0,    0,
    0,    0,    0,    0,
};
short yygindex[] = {                                      0,
   -2,   49,    0,    0,    0,    0,    0,   12,   18,    0,
    3,  -22,    0,    0,
};
#define YYTABLESIZE 277
short yytable[] = {                                      35,
   15,   31,   30,   33,   39,   34,   10,   32,   32,   36,
   34,   37,   25,   63,   73,   80,   24,   25,   52,   26,
   24,   61,   40,   27,   51,   58,   31,   10,   29,   53,
   34,   44,   19,   20,   21,   10,   54,   66,   43,   81,
   22,   23,   79,   78,   50,   35,   36,   37,   35,   36,
   37,   64,   65,   38,   60,    1,   38,   17,   33,   59,
   75,    0,   68,    0,   74,    0,    0,    0,    0,    0,
    0,    0,   69,   70,   71,   72,   82,   83,   84,    0,
    0,   76,   77,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   15,    0,   15,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    1,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    2,    3,    4,    5,    6,    7,    8,    9,
    1,    0,    0,    0,    0,    0,    0,    0,    1,    0,
    0,    0,    0,    2,    3,    4,    5,    6,    7,    8,
    9,    2,    3,    4,    5,    6,    7,    8,    9,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   19,   20,   21,   35,   36,   37,    0,    0,
   22,   23,    0,   38,    0,    0,    0,    0,   35,   36,
   37,    0,    0,    0,    0,    0,   38,    0,   55,    0,
   56,   57,    0,    0,    0,    0,   35,   35,   31,   31,
   33,   33,   34,   34,   32,   32,   36,   36,   37,   37,
   62,   62,   62,   24,   25,    0,   15,   19,   20,   21,
   41,    0,   42,    0,    0,   22,   23,    0,    0,   15,
   15,   15,   15,   15,   15,   15,   15,
};
short yycheck[] = {                                      41,
    0,   41,   59,   41,   58,   41,  123,   41,  125,   41,
   13,   41,   58,   41,   41,   41,   41,   41,   59,   40,
    3,   44,   25,   40,   40,   60,    9,  123,   59,  125,
   33,   33,  259,  260,  261,  123,   39,  279,   40,  277,
  267,  268,   41,   66,   27,  259,  260,  261,  259,  260,
  261,  265,  266,  267,   43,    0,  267,   41,   10,   42,
   63,   -1,   51,   -1,   62,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   55,   56,   57,   58,   79,   80,   81,   -1,
   -1,   64,   65,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  123,   -1,  125,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  256,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  269,  270,  271,  272,  273,  274,  275,  276,
  256,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  256,   -1,
   -1,   -1,   -1,  269,  270,  271,  272,  273,  274,  275,
  276,  269,  270,  271,  272,  273,  274,  275,  276,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  259,  260,  261,  259,  260,  261,   -1,   -1,
  267,  268,   -1,  267,   -1,   -1,   -1,   -1,  259,  260,
  261,   -1,   -1,   -1,   -1,   -1,  267,   -1,  263,   -1,
  265,  266,   -1,   -1,   -1,   -1,  278,  279,  278,  279,
  278,  279,  278,  279,  278,  279,  278,  279,  278,  279,
  278,  278,  278,  278,  278,   -1,  256,  259,  260,  261,
  262,   -1,  264,   -1,   -1,  267,  268,   -1,   -1,  269,
  270,  271,  272,  273,  274,  275,  276,
};
#define YYFINAL 11
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 279
#if YYDEBUG
char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"'!'",0,0,0,0,0,0,"'('","')'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"':'","';'","'<'",
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'{'",0,"'}'",0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"LEXERROR","FDEF","identifier","en_var","param","ERRORLEVEL","GE","EXIST","EQ",
"NE","number","empty","dos_command","CASE","DEFAULT","IF","SWITCH","WHILE",
"BREAK","RETURN","ELSE","LOG_OR","LOG_AND",
};
char *yyrule[] = {
"$accept : batch_file",
"batch_file : statement_list",
"statement : dos_command",
"statement : compound_statement",
"statement : selection_statement",
"statement : while_statement",
"statement : labelled_statement",
"statement : jump_statement",
"statement : error",
"labelled_statement : CASE primary_expression ':' statement",
"labelled_statement : DEFAULT ':' statement",
"compound_statement : '{' statement_list '}'",
"compound_statement : '{' '}'",
"statement_list : statement",
"statement_list : statement_list statement",
"selection_statement : IF '(' dos_expression ')' statement",
"selection_statement : IF '(' dos_expression ')' statement ELSE statement",
"$$1 :",
"selection_statement : SWITCH '(' primary_expression $$1 ')' statement",
"$$2 :",
"while_statement : WHILE $$2 '(' dos_expression ')' statement",
"jump_statement : BREAK ';'",
"jump_statement : RETURN ';'",
"jump_statement : RETURN primary_expression ';'",
"dos_expression : logical_AND_expression",
"dos_expression : dos_expression LOG_OR logical_AND_expression",
"logical_AND_expression : unary_expression",
"logical_AND_expression : logical_AND_expression LOG_AND unary_expression",
"unary_expression : dos_logical_expression",
"unary_expression : '(' dos_expression ')'",
"unary_expression : '!' unary_expression",
"dos_logical_expression : ERRORLEVEL GE primary_expression",
"dos_logical_expression : ERRORLEVEL '<' primary_expression",
"dos_logical_expression : ERRORLEVEL EQ primary_expression",
"dos_logical_expression : ERRORLEVEL NE primary_expression",
"dos_logical_expression : EXIST primary_expression",
"dos_logical_expression : primary_expression EQ primary_expression",
"dos_logical_expression : primary_expression NE primary_expression",
"primary_expression : identifier",
"primary_expression : primary_expression identifier",
"primary_expression : en_var",
"primary_expression : primary_expression en_var",
"primary_expression : param",
"primary_expression : primary_expression param",
"primary_expression : number",
"primary_expression : primary_expression number",
"primary_expression : empty",
};
#endif
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH 500
#endif
#endif
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short yyss[YYSTACKSIZE];
YYSTYPE yyvs[YYSTACKSIZE];
#define yystacksize YYSTACKSIZE
#line 758 "batchgen.y"

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
   code_list_t *true = new_code_node (),
               *false = new_code_node (),
               *gto = new_code_node ();

   if (true != NULL && false != NULL && gto != NULL)
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
      code_join (4, expr->expr_code, true, gto, false);
      expr->truelist = makelist (true);
      expr->falselist = makelist (false);
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
#line 410 "y.tab.c"
#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
int
yyparse()
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register char *yys;
    extern char *getenv();

    if (yys = getenv("YYDEBUG"))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if (yyn = yydefred[yystate]) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yyss + yystacksize - 1)
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;
#ifdef lint
    goto yynewerror;
#endif
yynewerror:
    yyerror("syntax error");
#ifdef lint
    goto yyerrlab;
#endif
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yyss + yystacksize - 1)
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
    switch (yyn)
    {
case 1:
#line 81 "batchgen.y"
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
      cl = code_join (3, begin, yyvsp[0].code_node, end);
      return yynerrs;
   }
break;
case 2:
#line 99 "batchgen.y"
{
      /*
          dos_command
          batch file statements, copy yytext to $$.code
       */

       yyval.code_node = new_code_node ();
       add_string (yyval.code_node, yytext);
       yyval.code_node->next = new_code_node ();
       add_string (yyval.code_node->next, "\n");
   }
break;
case 8:
#line 115 "batchgen.y"
{fprintf (stderr, "error near line %d\n", lineno);
            if (yydebug)
               printf ("error near line %d\n", lineno);
           }
break;
case 9:
#line 123 "batchgen.y"
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
         yyval.code_node = new_code_node ();
         sprintf (text, "rem case\nif not \"%s\" == \"%s\" goto %s\n",\
                              sw_code->code, yyvsp[-2].expr_node->expr_code->code, label);
         add_string (yyval.code_node, text);
         sprintf (text, "rem end case\n:%s\n", label);
         add_string (label_def, text);
         code_join (3, yyval.code_node, yyvsp[0].code_node, label_def);
      }
      else
      {
         fprintf (stderr, "case outside switch statement at line %d\n",lineno); 
         return 1;
      }
    }
break;
case 10:
#line 157 "batchgen.y"
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
         sw_code->next = yyvsp[0].code_node;
      }
      else
      {
         fprintf (stderr, "default outside switch statement at line %d\n",\
                                                          lineno); 
         return 1;
      }
    }
break;
case 11:
#line 184 "batchgen.y"
{
      /*
         compound statement
         code is in statement list
      */
      yyval.code_node = yyvsp[-1].code_node;
   }
break;
case 12:
#line 192 "batchgen.y"
{
      /* insert rem statement */
      yyval.code_node = new_code_node ();
      add_string (yyval.code_node, "rem\n");
    }
break;
case 13:
#line 201 "batchgen.y"
{
       /*
          statement
          code is in statement
       */
       yyval.code_node = yyvsp[0].code_node;
    }
break;
case 14:
#line 209 "batchgen.y"
{
       /*
          statement_list statement
          append code for statement to statement list code
       */
       yyval.code_node = yyvsp[-1].code_node;
       code_join (2, yyval.code_node, yyvsp[0].code_node);
     }
break;
case 15:
#line 223 "batchgen.y"
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
      code_list_t *true = new_code_node (),
                  *false = new_code_node ();
      char text [TEXTLEN],
           true_label [80],
           false_label [80];

      sprintf (true_label, IF_PFX"%i\n", label_no);
      sprintf (false_label, ENDIF_PFX"%i\n", label_no);

      backpatch_str (yyvsp[-2].expr_node->truelist, true_label);
      backpatch_str (yyvsp[-2].expr_node->falselist, false_label);

      if (true != NULL && false != NULL)
      {
         sprintf (text, ":%s", true_label);
         add_string (true, text);
         sprintf (text, "rem endif\n:%s", false_label);
         add_string (false, text);
         code_join(4,yyvsp[-2].expr_node->expr_code,true,yyvsp[0].code_node,false);
         yyval.code_node = yyvsp[-2].expr_node->expr_code;
      }
      else
      {
         perror ("cannot allocate memory");
         return 1;
      }
   }
break;
case 16:
#line 274 "batchgen.y"
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
         code_list_t *true = new_code_node (),
                     *false = new_code_node (),
                     *end = new_code_node ();
         char text [TEXTLEN],
              true_label [80],
              false_label [80],
              end_label [80];

         sprintf (true_label, IF_PFX"%i\n", label_no);
         sprintf (false_label, ELSE_PFX"%i\n", label_no);
         sprintf (end_label, ENDIF_PFX"%i\n", label_no);

         backpatch_str (yyvsp[-4].expr_node->truelist, true_label);
         backpatch_str (yyvsp[-4].expr_node->falselist, false_label);


         if (true != NULL && false != NULL && end != NULL)
         {
            sprintf (text, ":%s", true_label);
            add_string (true, text);
            sprintf (text, "\ngoto %srem else\n:%s", end_label, false_label);
            add_string (false, text);
            sprintf (text, "rem endif\n:%s", end_label);
            add_string (end, text);
            code_join (6, yyvsp[-4].expr_node->expr_code, true, yyvsp[-2].code_node, false, yyvsp[0].code_node, end);
            yyval.code_node = yyvsp[-4].expr_node->expr_code;
         }
         else
         {
            perror ("cannot allocate memory");
            return 1;
         }
      }
break;
case 17:
#line 335 "batchgen.y"
{
         /* stack first half of test code */

         code_list_t *sw_code = new_code_node ();

         add_string (sw_code, yyvsp[0].expr_node->expr_code->code);
         spush (sw_code);
      }
break;
case 18:
#line 346 "batchgen.y"
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
           yyval.code_node = code_join (6, remsw, yyvsp[0].code_node, remdef, default_code, remedef, labeldef);
        }
break;
case 19:
#line 386 "batchgen.y"
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
break;
case 20:
#line 399 "batchgen.y"
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
      code_list_t *true = new_code_node (),
                  *false = new_code_node (),
                  *begin = new_code_node (),
                  *breaks = to_ws ();
      char text [TEXTLEN],
           begin_label [80],
           true_label [80],
           false_label [80];

      sprintf (begin_label, WHILE_PFX"%i\n", label_no);
      sprintf (true_label, WHILE_BODY_PFX"%i\n", label_no);
      sprintf (false_label, ENDWHILE_PFX"%i\n", label_no);

      backpatch_str (yyvsp[-2].expr_node->truelist, true_label);
      backpatch_str (yyvsp[-2].expr_node->falselist, false_label);
      backpatch_str (breaks->gotos, false_label);

      if (true != NULL && false != NULL && begin != NULL)
      {
         sprintf (text, "rem while\n:%s", begin_label);
         add_string (begin, text);
         sprintf (text, ":%s", true_label);
         add_string (true, text);
         sprintf (text, "goto %srem endwhile\n:%s", begin_label, false_label);
         add_string (false, text);
         yyval.code_node = code_join (5, begin, yyvsp[-2].expr_node->expr_code, true, yyvsp[0].code_node, false);
         wpop ();
      }
      else
      {
         perror ("cannot allocate memory");
         return 1;
      }
   }
break;
case 21:
#line 462 "batchgen.y"
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
         yyval.code_node = new_code_node ();
         label->gotos = makelist (label);
         false_exit->gotos = merge (false_exit->gotos, label->gotos);
         add_string (yyval.code_node, "rem break\ngoto ");
         code_join (2, yyval.code_node, label);
      }
      else
      {
         fprintf (stderr,"break outside while or switch at line %d\n",lineno);
         return 1;
      }
   }
break;
case 22:
#line 488 "batchgen.y"
{
      yyval.code_node = new_code_node ();
	  /*
      if (in_sr)
         add_string ($$, "goto %"RET_LABEL"%\n");
      else
	  */
         add_string (yyval.code_node, "goto batch_end\n");
   }
break;
case 23:
#line 498 "batchgen.y"
{
      char text [TEXTLEN];
                                 
      yyval.code_node = new_code_node ();
      sprintf (text, "exit /b %s\n", yyvsp[-1].expr_node->expr_code->code);
      add_string (yyval.code_node, text);
   }
break;
case 24:
#line 509 "batchgen.y"
{
      yyval.expr_node = yyvsp[0].expr_node;
   }
break;
case 25:
#line 513 "batchgen.y"
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
      backpatch_str (yyvsp[-2].expr_node->falselist, false_label);
      yyval.expr_node = new_expr ();
      yyval.expr_node->truelist = merge (yyvsp[-2].expr_node->truelist, yyvsp[0].expr_node->truelist);
      yyval.expr_node->falselist = yyvsp[0].expr_node->falselist;
      yyval.expr_node->expr_code = code_join \
                         (3, yyvsp[-2].expr_node->expr_code, label_def, yyvsp[0].expr_node->expr_code);
   }
break;
case 26:
#line 547 "batchgen.y"
{
      yyval.expr_node = yyvsp[0].expr_node;
   }
break;
case 27:
#line 551 "batchgen.y"
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
      backpatch_str (yyvsp[-2].expr_node->truelist, true_label);
      yyval.expr_node = new_expr ();
      yyval.expr_node->falselist = merge (yyvsp[-2].expr_node->falselist, yyvsp[0].expr_node->falselist);
      yyval.expr_node->truelist = yyvsp[0].expr_node->truelist;
      yyval.expr_node->expr_code = code_join (3, yyvsp[-2].expr_node->expr_code, label_def, yyvsp[0].expr_node->expr_code);
   }
break;
case 28:
#line 582 "batchgen.y"
{
      yyval.expr_node = yyvsp[0].expr_node;
   }
break;
case 29:
#line 586 "batchgen.y"
{
      yyval.expr_node = yyvsp[-1].expr_node;
   }
break;
case 30:
#line 590 "batchgen.y"
{
      /* not unary_expr */
      yyval.expr_node = new_expr ();
      yyval.expr_node->truelist = yyvsp[0].expr_node->falselist;
      yyval.expr_node->falselist = yyvsp[0].expr_node->truelist;
      yyval.expr_node->expr_code = yyvsp[0].expr_node->expr_code;
   }
break;
case 31:
#line 601 "batchgen.y"
{
      char text [TEXTLEN] ;

      yyval.expr_node = new_expr ();
      sprintf (text, "if errorlevel %s goto ", yyvsp[0].expr_node->expr_code->code);
      if (make_expr_code (text, yyval.expr_node) == NULL)
         return 1;
   }
break;
case 32:
#line 610 "batchgen.y"
{
      char text [TEXTLEN] ;

      yyval.expr_node = new_expr ();
      sprintf (text, "if not errorlevel %s goto ", yyvsp[0].expr_node->expr_code->code);
      if (make_expr_code (text, yyval.expr_node) == NULL)
         return 1;
   }
break;
case 33:
#line 620 "batchgen.y"
{
      char text [TEXTLEN] ;

      yyval.expr_node = new_expr ();
      sprintf (text, "if errorlevel = %s goto ", yyvsp[0].expr_node->expr_code->code);
      if (make_expr_code (text, yyval.expr_node) == NULL)
         return 1;
   }
break;
case 34:
#line 630 "batchgen.y"
{
      char text [TEXTLEN] ;

      yyval.expr_node = new_expr ();
      sprintf (text, "if not errorlevel = %s goto ", yyvsp[0].expr_node->expr_code->code);
      if (make_expr_code (text, yyval.expr_node) == NULL)
         return 1;
   }
break;
case 35:
#line 640 "batchgen.y"
{
      char text [TEXTLEN] ;

      yyval.expr_node = new_expr ();
      sprintf (text, "if exist %s goto ", yyvsp[0].expr_node->expr_code->code);
      if (make_expr_code (text, yyval.expr_node) == NULL)
         return 1;
   }
break;
case 36:
#line 649 "batchgen.y"
{
      char text [TEXTLEN] ;

      yyval.expr_node = new_expr ();
      sprintf (text, "if \"%s\" == \"%s\" goto ", \
                               yyvsp[-2].expr_node->expr_code->code, yyvsp[0].expr_node->expr_code->code);
      if (make_expr_code (text, yyval.expr_node) == NULL)
         return 1;
   }
break;
case 37:
#line 659 "batchgen.y"
{
      char text [TEXTLEN] ;

      yyval.expr_node = new_expr ();
      sprintf (text, "if not \"%s\" == \"%s\" goto ", \
                               yyvsp[-2].expr_node->expr_code->code, yyvsp[0].expr_node->expr_code->code);
      if (make_expr_code (text, yyval.expr_node) == NULL)
         return 1;
   }
break;
case 38:
#line 672 "batchgen.y"
{
      /* identifier */
      yyval.expr_node = new_expr ();
      add_text (yyval.expr_node, yytext);

   }
break;
case 39:
#line 679 "batchgen.y"
{
        expr_t *id = new_expr();

      /* primary_expression identifier */
        if (id != NULL)
            add_text (id, yytext);
      if (concat_text (yyvsp[-1].expr_node, id) == 0)
         yyval.expr_node = yyvsp[-1].expr_node;
      else
         return 1;
   }
break;
case 40:
#line 691 "batchgen.y"
{
      /* environmental variable */
      yyval.expr_node = new_expr ();
      add_text (yyval.expr_node, yytext);
   }
break;
case 41:
#line 697 "batchgen.y"
{
        expr_t *ev = new_expr();

        /* primary_expression en_var */
        if (ev != NULL)
            add_text (ev, yytext);
        else
            return 1;
        if (concat_text (yyvsp[-1].expr_node, ev) == 0)
            yyval.expr_node = yyvsp[-1].expr_node;
        else
            return 1;
    }
break;
case 42:
#line 711 "batchgen.y"
{
        /* parameter */
        yyval.expr_node = new_expr ();
        add_text (yyval.expr_node, yytext);
    }
break;
case 43:
#line 717 "batchgen.y"
{
        expr_t *par = new_expr();

      /* primary_expression param */
        if (par != NULL)
            add_text (par, yytext);
        else
            return 1;
        if (concat_text (yyvsp[-1].expr_node, par) == 0)
            yyval.expr_node = yyvsp[-1].expr_node;
        else
            return 1;
    }
break;
case 44:
#line 731 "batchgen.y"
{
        /* number */
        yyval.expr_node = new_expr ();
        add_text (yyval.expr_node, yytext);
    }
break;
case 45:
#line 737 "batchgen.y"
{
        expr_t *num = new_expr();

        /* primary_expression number */
        if (num != NULL)
            add_text (num, yytext);
        else
            return 1;
        if (concat_text (yyvsp[-1].expr_node, num) == 0)
         yyval.expr_node = yyvsp[-1].expr_node;
      else
         return 1;
   }
break;
case 46:
#line 751 "batchgen.y"
{
      yyval.expr_node = new_expr ();
      add_text (yyval.expr_node, "");
   }
break;
#line 1255 "y.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yyss + yystacksize - 1)
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    return (1);
yyaccept:
    return (0);
}
