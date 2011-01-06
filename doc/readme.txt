It's not my fault
=================
This software contains known and unknown bugs: use it at your
own risk.

All trade marks acknowledged


Introduction
============

One of the failings of DOS/command.com/cmd.exe is that the only 
logical operator is "not". The other big failing is that it can't
add up. batchgen is an attempt to bring boolean logic to DOS.

You need to be quite happy writing batch files before using
batchgen, it doesn't quite write them for you. Additionally, 
experience of a high level procedural language will make 
it easier for you to use the power that batchgen gives you.

The big idea is that we use batchgen to do all the flow of
control transformations, whilst we enclose normal DOS commands
[# rem like this #]. batchgen turns the flow of control statements 
into legal DOS commands, and copies text enclosed in [##] 
verbatim. (this can lead to problems, see Bugs, below).

If we have the following as input:
if (%1==%2 && ! %3==%4 || exist %5)
   [#
     rem this will be copied verbatim
     @echo it's true
   #]

batchgen's output is:
@goto main
:main
if "%1" == "%2" goto AT0
goto ORF1
:AT0
if "%3" == "%4" goto ORF1
goto IF0
:ORF1
if exist %5 goto IF0
goto EI0
:IF0

     rem this will be copied verbatim
     @echo it's true
   
rem endif
:EI0
:batch_end

if we ask for optimization we get:
if not "%1" == "%2" goto ORF1
if not "%3" == "%4" goto IF0
:ORF1
if not exist %5 goto EI0
:IF0
     @echo it's true
:EI0

If you ask me, that's pretty slick, and it saves a lot of 
unecessary thinking.

batchgen is a run of the mill lex/yacc parser. The lexemes are
defined in batchgen.l, the grammar and it's associated semantic 
actions are defined in batchgen.y.

The parser does not parse DOS commands.



Using
=====

batchgen [-o[r|b] [filename]
In the absence of a filename, batchgen will read input from
the command line, terminated with ctrl-z if you're using the
keyboard. 
   batchgen filename is equivalent to 
   batchgen < filename is equivalent to 
   type filename | batchgen
   and all three of these command lines will work.

   batchgen file1 file2 .. is equivalent to
   batchgen file1 
   there are no warnings or errors

The options are as follows:
   -o   optimizes but leaves lines beginning with rem and blank
        lines
   -or  optimizes as for -o and also removes rems
   -ob  optimizes as for -o and also removes blank lines
   -orb = -obr is full on optimization
   
   -h   prints a usage string

Output is to bc.bat in the current directory. If you've asked
for optimization, your output is in bc.bat. The optimized
output is in bco.bat.

If optimization fails (see Bugs, below) bco.bat is written, 
with code that makes it return immediately wrapped round it, 
so as not to execute potentially damaging instructions. 
(see it's not my fault, above).


Language reference
==================
The syntax is pretty much C like. Does that help you?

The compiler is looking for a statement_list

A statement_list is a sequence of statements

A statement may be:
 a function_definition, or
 a function_call, or
 a jump_statement, or
 a while_statement, or
 a selection_statement, or
 a compound_statement, or
 a dos_command

A function_definition looks like: 
    fdef identifier()
    {
        statement_list
    }

Functions do not take parameters, nor do they 
return values.

It is an error for a function definition to 
contain a function call, ie functions cannot
be nested, owing to the extremely crude 
return mechanism.

A function_call looks like 
    function_identifier()

Functions must have been defined before they can
be called.


A jump_statement is 
    break; or 
    return; or 
    return primary_expression;

break may only be used inside a while or switch
statement.

return; may be used in a function, in which case 
control goes back to the main program, or in the 
main program, in which case control returns to the 
operating system.

return primary_expression; (eg return 42;) is a bit 
of a bodge; a program called el is invoked, which 
returns it's argument as an int. Control is then 
given to the operating system. The errorlevel when
the batch file terminates is thus set to, for 
example, 42. This requires that the program 
el.com or el.exe be available to your batch file.

A while_statement looks like:
   while ( boolean_expression )
       statement

statement may be a compound statement, so the 
while_statement would look like:
   while ( boolean_expression )
   {
       statement_list
   }

This while is the same as everybody else's, 
statement (or the statement list) is executed 
for as long as boolean_expression is true.

A selection_statement is 
   either if ( boolean_expression ) statement 
   or     if ( boolean_expression ) statement else statement
   or     switch ( primary_expression ) statement

if evaluates boolean_expression. If it is true, statement is executed.
if..else evaluates boolean_expression. If it is true, the first 
statement is executed, if false the statement following the 
else is executed. As before, statement may be a compound 
statement, ie a statement_list enclosed in curly brackets.

switch is more complicated than it appears from the grammar.
The sensible way to use switch is along these lines:

   switch(%1)
   {
       case 1: [#do something#]
       case 2: {
                  if (%DEBUG% == TRUE)
                      [#do something else#]
               }
       ...
       default: [#give in#]
   }

There are other legal ways of writing switches. 
They are a bad idea.

The statements in the example above are labelled statements 
which look like:
   case primary_expression : statement
   default : statement

A labelled_statement, according to the grammar, may take
the place of any statement. However, there is some special
case finangling in the semantic actions for case and 
default which ensures they are only legal inside a switch 
statement.

Finally, a statement may be any amount of text enclosed by
[# and #]. This text is copied verbatim to the output batch 
file. It is therefore a good idea to make this legal DOS 
commands. batchgen does not parse this text.

The logical expressions that are evaluated are built up 
from primary_expressions and logical operators. These are 
defined in batchgen.l. The intention here is to make sure 
that our output is something like legal DOS, we want to 
exclude characters like <,> and |.

A primary expression is 
  text, or an
  environmental variable, or a
  parameter, or a
  number, or
  any concatenation of the above, or
  empty

number is a sequence of decimal digits

parameter is a dos positional parameter

text is a string starting with a letter, digit, backslash, 
dot or dash; followed by zero or more letter, digit, 
backslash, dot, dash, dollar sign, underscore or asterisk.

environmental variable is text surounded by percent signs.

An empty primary expression is denoted by two double quotes.

primary_expressions are built up into dos_logical_expressions, 
that is expressions which have a boolean value. These are:

exist primary_expression
primary_expression == primary_expression
primary_expression != primary_expression
errorlevel >= primary_expression
errorlevel < primary_expression
which are are ok for all versions of the OS.

the next two will compile but the OS may not support the
compilers output pre windows NT:
errorlevel == primary_expression
errorlevel != primary_expression


boolean_expressions may grouped like so: (boolean_expression) 
and negated like so: !boolean_expression.

Finally we can also form new boolean expressions using and (&&) and 
or (||), for instance 
  this == %that% || %1 != stop && !exist lock
is a valid boolean_expression which may be used as the test in an 
if or while statement.


Building
========
You need:
   * a C++ compiler (C will do for ver 1.1)
   * lex and yacc - binaries at 
     http://www.monmouth.com/~wstreett/lex-yacc/lex-yacc.html
     I sent hom an email but the ISP said his mailbox was full.
     Of what? I can imagine only too well.


There are no make files.

This program is so small by modern standards as to not require
a make file, we can just build everything. In addition we get a 
version explosion whilst trying to sort out the different 
command lines for different compilers using different makes. 
Stir in the make whitespace/tab bug and I start losing the 
will to live.
Ant is an alternative, I did have a brief look at it, but it
seems like overkill in this case.

Consequently I wrote vc_make.bat (derived from vc_make.bc), 
which will do a VC++ build all.

There are VC++ project and workspace files should they be 
any use to you. These will need copying to the source directory.

running yacc on batchgen.y gives the following error
state <n> contains 1 shift/reduce conflict.
This is the if-else ambiguity, we accept yacc's default 
resolution.


Bugs
====
The optimizer cannot do agressive optimization without removing 
comments and blank lines.

The contents of input and output files are held in main memory, 
consequently you could run out of memory.

Trailing space on environmental variables. This can be a real pain. 
[# set VAR=99 #]
when translated and executed by the OS will give VAR the value "99 ".
You will be saying something like
if "VAR"=="99"   do something
and your program won't do something, it will do nothing. This is
because VAR has the value "99 ", not "99".

I suspect the grammar could be tidied up. I'm 
not particularly expert at grammars, this is 
basically a hack of the C grammar.

A dos_delim may be nested (eg [#  [# #]). The scanner is meant 
to catch this, but it doesn't and I don't know why.

Strings aren't really handled very well. In particular spaces 
aren't allowed, which could be a problem now that file names 
can contain spaces.

error messages could be a lot more informative

test cases are all legal input

UNICODE ? would probably need to recompile lex and yacc for starters.

Line length is limited to 500 char (that's old style ASCII char = 
bytes(that's new style 8 bit bytes)) 

errorlevel. Oh dear. This is currently a hack which may or may 
not work. If you are pre windows NT you need (I think) to stick 
to errorlevel >= primary_expression and errorlevel < primary_expression.
I have also put in productions for errorlevel == primary_expression and 
errorlevel != primary_expression. These are ok for NT and can be 
extended to the complete set of comparison operators, along with 
numeric comparisons, and case (in)sensitive string comparisons. 
Try help if from the command line to get the party line from Microsoft. 
I will probably redo the compiler so it writes code that takes 
advantage of these new features. One day all this will be unecessary 
as cmd.exe will be a proper shell.


<Your bug here>


Acknowledgments
===============

This program is pretty much lifted from Compilers: Principles, 
Techniques and Tools by Aho, Sethi and Ullman, 
pub Addison Wesley 1986

Comments
========
The VC++ project should be ok, you will need lex and yacc and 
will have to do project->settings in VC++ for batchgen.y and 
batchgen.l to point the compiler in the right direction.

The binaries are in bin, some test cases in test, best of luck - NJ.

