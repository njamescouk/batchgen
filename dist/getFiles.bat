@echo off

pushd ..\bin
call compile.bat
popd

pushd ..\doc
call makeDoc.bat
popd

if not exist bin     md  bin
if not exist doc     md  doc
if not exist source  md  source
if not exist test    md  test
if not exist vce2010 md  vce2010


copy ..\vce2010\batchgen.sln vce2010
copy ..\vce2010\vce2010.vcxproj vce2010
copy ..\vce2010\vce2010.vcxproj.filters vce2010
copy ..\vce2010\vce2010.vcxproj.user vce2010

copy ..\test\*.bg test
copy ..\test\testAll.bat test

copy ..\doc\batchgen.doxy doc
copy ..\doc\batchgen_readme.html doc
copy ..\doc\gotchas.txt doc
copy ..\doc\license.html doc
copy ..\doc\quickref.txt doc

copy ..\bin\batchgen.exe bin
copy ..\bin\compile.bat bin

copy ..\source\*.* source
