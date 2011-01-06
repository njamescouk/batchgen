@echo off
rem 
rem this file has been generated by batchgen and may be overwritten
rem command line: batchgen -orb compile.bg
rem date 2011-0-7 08:11:27

@goto main

:initialise

rem set DEBUG=<anything> gets a debug build
set DLY_DEBUG=
set DLY_HELP=
set DLY_TERMINATE=
set DLY_LEX_FILE=..\source\batchgen.l
set DLY_GRAMMAR_FILE=..\source\batchgen.y

rem edit these to suit
set DLY_FLEX="C:\Program Files (x86)\GnuWin32\bin\flex.exe"
set DLY_YACC="C:\Program Files (x86)\GnuWin32\bin\yacc.exe"
goto :eof


:getopts
rem while
:WH0
if "%1" == "" goto EW0
:WB0
if "%1" == "-d" set DLY_DEBUG=True
if "%1" == "-h" set DLY_HELP=True
shift 
goto WH0
rem endwhile
:EW0

goto :eof


:usage
echo usage %0 [options]

echo options
echo     -d     include debugging code for lexer and parser
echo     -h     this screen
set DLY_TERMINATE=yes

goto :eof

:main

call :initialise
call :getopts %*

if "%DLY_HELP%" == "True" call :usage
if "%DLY_TERMINATE%"=="yes" goto batch_end

if "%DLY_DEBUG%" == "" goto IF2
goto LS2
:IF2

       set DLY_LEX_FLAGS= -d
       set DLY_YACC_FLAGS= -tdv
       set YYDEBUG=
 
goto EI2
rem else
:LS2

       set DLY_LEX_FLAGS=-d
       set DLY_YACC_FLAGS=-ldv
       set YYDEBUG=1
       
rem endif
:EI2

@echo on

%DLY_YACC% %DLY_YACC_FLAGS% %DLY_GRAMMAR_FILE%
%DLY_FLEX% %DLY_LEX_FLAGS% %DLY_LEX_FILE%

@echo off

move y.output ..\doc\y.output > nul
move lex.yy.* ..\source > nul
move y.tab.* ..\source > nul

set DLY_DEBUG=
set DLY_HELP=
set DLY_LEX_FLAGS=
set DLY_YACC_FLAGS=
set DLY_LEX_FILE=
set DLY_GRAMMAR_FILE=
set DLY_FLEX=
set DLY_YACC=
set DLY_TERMINATE=

:batch_end