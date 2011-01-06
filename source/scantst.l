%{
	
#include "y_tab.h"

%}

space [ \t\n]
ws    {space}+
letter [a-zA-Z]
digit [0-9]
number {digit}+
identifier {letter}({letter}|_|{digit})*

%%

{ws}   { }

"&&" {return LOG_AND;}
"==" {return EQ;}
"!=" {return NE;}
">=" {return GE;}
"%"{identifier}"%"  {return en_var;}
"%"{digit}    {return param;}
errorlevel  {return ERRORLEVEL;}
ERRORLEVEL  {return ERRORLEVEL;}
exist       {return EXIST;}
EXIST       {return EXIST;}
{number} {return number;}
{identifier} {return identifier;}
[^ \t\n] {return yytext [0];}

%%


int yywrap (void)
{
   return 1;
}   

#ifdef DEBUG
void main (void)
{
   int c;
   
  	while (c = yylex ())
      printf ("\nyylex returns int %d = char %c\n\n", c, c);
}
#endif
