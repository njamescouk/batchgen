@echo off
rem this file has been generated by batchgen and may be overwritten
rem command line: ..\bin\batchgen.exe -orb whsw.bg
rem date 2011-0-8 22:55:34

@echo off
:WH1
if not "%1" == "bert" goto EW1
@echo w1
if "%2" == "1" @echo sw1 c1
if not "%2" == "2" goto EW0
@echo sw1 c2
:WH0
if not "%2" == "2" goto EW0
@echo w2
if "%3" == "3" @echo sw3 c3
shift
goto WH0
:EW0
    shift
goto WH1
:EW1