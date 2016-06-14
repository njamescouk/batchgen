% Batchgen
% Nick James
% 2016-06-05

<div class="article">
Introduction
============

batchgen is a program to generate dos batch files from a higher level
language, making it easier to use boolean logic in batch files.

One of the failings of DOS/command.com/cmd.exe is that the only logical
operator is "not". The other big failing is that it can't add up.
batchgen is an attempt to bring boolean logic to DOS. You need to be
quite happy writing batch files before using batchgen, it doesn't quite
write them for you. If you have experience of C life will be easier.

The big idea is that we use batchgen to do all the flow of control
transformations, whilst we enclose normal DOS commands [\# rem like this
\#]. batchgen turns the flow of control statements into legal DOS
commands, and copies text enclosed in [\#\#] verbatim. 
(this can lead to problems, see [Bugs](#bugs), below).

If we have the following as input:

<pre class = "programlisting">
!!PP sed "s/^/    /" eg1.bg
</pre>

batchgen's output is:

<pre class = "programlisting">
!!PP batchgen eg1.bg & sed "s/^/    /" bg.bat
</pre>

If you ask me, that's pretty slick, and it saves a lot of unecessary
thinking. 

batchgen is a run of the mill lex/yacc parser. The lexemes are
defined in [batchgen.l](../source/batchgen.l), the grammar and it's
associated semantic actions are defined in
[batchgen.y](../source/batchgen.y). The parser does not parse DOS
commands.

Usage
=====

    batchgen [filename] 

In the absence of a filename, batchgen
will read input from the command line, terminated with ctrl-z if you're
using the keyboard.

`batchgen filename` is equivalent to `batchgen < filename`
 is equivalent to `type filename | batchgen` and all three of these
command lines will work. 

`batchgen file1 file2` .. is equivalent to
`batchgen file1`. There are no warnings or errors.

Options
-------

The options are as follows:

-   -h prints a usage string

Output
------

Output is to `bg.bat` in the current directory.

Batchgen language
=================

The syntax is pretty much C like.

Version 3 handles functions by generating code that uses the call :label
syntax, see
[this](http://technet.microsoft.com/en-us/library/bb490873.aspx). There
are no changes in the grammar, but the generated code won't work unles
you're on XP or later.

break may only be used inside a while or switch statement. return;
returns control to the operating system. return primary\_expression; (eg
return 42;) is rewritten as exit /b primary\_expression, see
[this](http://technet.microsoft.com/en-us/library/bb490902.aspx). The
errorlevel when the batch file terminates is thus set to, for example,
42.

case and default are only legal inside a switch statement, despite the
grammar.

Blocks of dos code to be passed through are enclosed by [\# and \#].
This text is copied verbatim to the output batch file and should,
therefore, be legal DOS commands. batchgen does not parse this text.

Reserved words
--------------

if case else fdef switch default while return break || && == != \>= ""
errorlevel ERRORLEVEL exist EXIST

Batchgen grammar
----------------

<pre class = "programlisting">
!!PPmarkupgrammar -f ..\source\batchgen.y
</pre>

The non terminals identifier, en\_var and param are defined as follows:

-   identifier
    ({letter}|{digit}|\\\\|\\.|\\-)([a-zA-Z\$\\.\\\\\_\\\*:]|{digit})\*
    - this should boil down to a dos directory name

-   en\_var - is an identifier surrounded by %%

-   param - is a parameter prefixed by %

Building
========

You need:

-   a C++ compiler

-   lex and yacc binaries

compile.bat (in bin) will compile from the command line. Using MinGW
produces a buggy program, you're better off using Visual Studio Express
2010 (free) and the batchgen.sln file (in vce2010).

The VC project doesn't run lex and yacc: bin\\doLexYacc.bat calls lex
and yacc (I use the [GnuWin32](http://gnuwin32.sourceforge.net/) ones).
Running yacc on batchgen.y gives the following error:

     state contains 1 shift/reduce conflict.

This is the if-else ambiguity, we accept yacc's default resolution.

There are some test files in tests, these should all generate and
optimize without error.

Bugs
====

-   The contents of input and output files are held in main memory,
    consequently you could run out of memory.

-   Trailing space on environmental variables. This can be a real pain.

        [# set VAR=99 #]

    when translated and executed by the OS will give VAR the value "99
    ". You will be saying something like

        if "VAR"=="99" do something

    and your program won't do something, it will do nothing. This is
    because VAR has the value "99 ", not "99".

-   It's not written in C++. Some of the code is pretty nasty in
    retrospect (2011) but it more or less works.

-   function parameters not supported. This doesn't stop you defining a
    function that uses parameters, but you will have to call it using
    something like [\# call func arg1 arg2 \#] rather than func(arg2,
    arg2).

-   UTF-8 files with a byte order mark cause batchgen to fail with the
    helpful 'syntax error on line 1' message. UTF-8 files that are
    ANSI-in-disguise are ok; I suspect multibyte characters will make
    batchgen fall over.

See also
========

[quick reference](quickref.txt)

[gotchas](gotchas.txt)

[grammar diagram](batchgen.y.dot.jpeg)

Acknowledgments
===============

This program is pretty much lifted from Compilers: Principles,
Techniques and Tools by Aho, Sethi and Ullman, pub Addison Wesley 1986.

The grammar is pretty much lifted from C.

Colophon
========

Produced with

!!PPsed "s/^/    /;/pp readme.md.pp/q;d" makeDoc.bat
</div>