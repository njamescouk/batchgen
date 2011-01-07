@echo off
rem this file has been generated by batchgen and may be overwritten
rem command line: batchgen -orb compile.bg
rem date 2011-0-8 16:05:44

@goto main
rem sub routine
:usage

echo usage %0 [options]
echo .
echo options
echo     -d     include debugging code for lexer and parser
echo     -h     help

rem end sub routine
goto :eof

rem sub routine
:getopts
rem while
:WH0
if not "%1" == "" goto WB0
goto EW0
:WB0
if "%1" == "-d" goto IF1
goto LS1
:IF1
 set BGCOMP_DEBUG=True

goto EI1
rem else
:LS1
if "%1" == "-h" goto IF0
goto LS0
:IF0
set BGCOMP_HELP=True

goto EI0
rem else
:LS0
set BGCOMP_ILLEGAL_OPT=True
rem endif
:EI0
rem endif
:EI1
 shift 
goto WH0
rem endwhile
:EW0
rem end sub routine
goto :eof

rem sub routine
:finalise

set BGCOMP_DEBUG=
set BGCOMP_HELP=
set BGCOMP_ILLEGAL_OPT=
set CC_FLAGS=
set BGCOMP_SOURCE_FILES=
set CC=

rem end sub routine
goto :eof

rem sub routine
:initialise

rem set BGCOMP_DEBUG=<anything> gets a debug build
set BGCOMP_DEBUG=
set BGCOMP_HELP=
set BGCOMP_ILLEGAL_OPT=
set CC_FLAGS=
set BGCOMP_SOURCE_FILES=batchgen.c bkpatch.c fileread.c lex.yy.c optim.c sr.c stacks.c y.tab.c

rem edit these to suit
set CC=c:\bin\MinGW\bin\g++.exe

rem end sub routine
goto :eof

:main
call :initialise
call :getopts
if "%BGCOMP_HELP%" == "True" goto IF4
goto ORF0
:ORF0
if "%BGCOMP_ILLEGAL_OPT%" == "True" goto IF4
goto LS4
:IF4
call :usage
goto batch_end

goto EI4
rem else
:LS4
if "%BGCOMP_DEBUG%" == "" goto IF2
goto LS2
:IF2

       call doLexYacc
       set CC_FLAGS=-D WIN32 -D NDEBUG -D _CONSOLE -obatchgen.exe
       set YYDEBUG=
       

goto EI2
rem else
:LS2

       call doLexYacc -d
       set CC_FLAGS=-D WIN32 -D _CONSOLE -D DEBUG -D YYDEBUG  -obatchgen_debug.exe
       set YYDEBUG=1
       
rem endif
:EI2

    pushd I:\usr\NIK\dev\batchgen\source

    markupgrammar -f batchgen.y > ..\doc\batchgen.y.html
    markupgrammar -f batchgen.y -d > ..\doc\batchgen.y.dot
    markupgrammar -f ..\source\batchgen.y -x > ..\doc\batchgen.y.docbook.xml

    @echo on
    %CC% %CC_FLAGS% %BGCOMP_SOURCE_FILES%
    @echo off

    del *.obj > nul
    
    pushd I:\usr\NIK\dev\batchgen\doc
    dot -O -Tpng batchgen.y.dot
    popd
    
if "%BGCOMP_DEBUG%" == "" goto IF3
goto LS3
:IF3

       move batchgen.exe ..\bin
       

goto EI3
rem else
:LS3

       move batchgen.exe ..\bin\batchgen_debug.exe
       
rem endif
:EI3
rem endif
:EI4
 popd 
call :finalise
:batch_end
