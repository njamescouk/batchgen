%{
#define YY_USE_PROTOS

#include <stdlib.h>

#ifndef __TURBOC__
#include <malloc.h>
#endif

#include <string.h>
#include "batchgen.h"
#include "y.tab.h"
#include "sr.h"

#ifdef LEX_DEBUG
int lineno = 0;
#else
extern int lineno;
#endif

%}

%x dos_cmd
space [ \t]
ws    {space}+
letter [a-zA-Z]
digit [0-9]
number {digit}+
dot \.
double_dot \.\.
identifier ({letter}|{digit}|\\|\.|\-)([a-zA-Z$\.\\_\*:]|{digit})*
dos_delim \[#
dos_end_delim #\]

%%
{ws}   { }
\n   {lineno++;}
<*>{dos_end_delim} {   BEGIN (INITIAL); }
{dos_delim} { BEGIN (dos_cmd); }
<dos_cmd>(\n|.)*  {
	       char *yyptr, *nlptr;

	       yyptr = yytext;
          if ((yyptr = strstr (yyptr, "#]")) != NULL)
          {
             yyless (yyleng - strlen (yyptr));
             /* yyptr = yytext; */
             nlptr = yytext;
             while (nlptr - yytext < yyleng)
             {
                if (*nlptr == '\n'&& *nlptr != 0)
                   lineno++;
                nlptr++;
             }
             BEGIN (INITIAL);
          }
          else
          {
              return LEXERROR;
          }

          nlptr = yytext;
          while ((nlptr = strchr (yyptr, '\n')) != NULL)
          {
             lineno++;
             nlptr++;
          }
          return dos_command;
       }

if   {return IF;}
case {return CASE;}
else {return ELSE;}
switch {return SWITCH;}
default {return DEFAULT;}
while {return WHILE;}
return {return RETURN;}
break  {return BREAK;}
fdef {return FDEF;}
"||" {return LOG_OR;}
"&&" {return LOG_AND;}
"==" {return EQ;}
"!=" {return NE;}
">=" {return GE;}
"%"{digit}    {return param;}
"%"{identifier}"%"  {return en_var;}
\"\" { return empty; }
errorlevel  {return ERRORLEVEL;}
ERRORLEVEL  {return ERRORLEVEL;}
exist       {return EXIST;}
EXIST       {return EXIST;}
{number} {return number;}
{identifier} {
#ifndef LEX_DEBUG
                if (is_func (yytext) != -1)
                   return func_id;
#endif
                return identifier;
             }
[^ \t\n] {return yytext [0];}


%%


int yywrap (void)
{
   return 1;
}   

#ifdef LEX_DEBUG
void main (void)
{
   int c;
   
  	while (c = yylex ())
      printf ("\nyylex returns int %d = char %c\n\n", c, c);
}
#endif
