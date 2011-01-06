# Microsoft Developer Studio Generated NMAKE File, Based on batchgen.dsp
!IF "$(CFG)" == ""
CFG=batchgen - Win32 Debug
!MESSAGE No configuration specified. Defaulting to batchgen - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "batchgen - Win32 Release" && "$(CFG)" != "batchgen - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "batchgen.mak" CFG="batchgen - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "batchgen - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "batchgen - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "batchgen - Win32 Release"

OUTDIR=.\..\bin
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\..\bin
# End Custom Macros

ALL : ".\y.tab.h" ".\y.tab.c" ".\lexyy.c" "$(OUTDIR)\batchgen.exe"


CLEAN :
	-@erase "$(INTDIR)\batchgen.obj"
	-@erase "$(INTDIR)\bkpatch.obj"
	-@erase "$(INTDIR)\fileread.obj"
	-@erase "$(INTDIR)\lex.yy.obj"
	-@erase "$(INTDIR)\optim.obj"
	-@erase "$(INTDIR)\sr.obj"
	-@erase "$(INTDIR)\stacks.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\y.tab.obj"
	-@erase "$(OUTDIR)\batchgen.exe"
	-@erase "lexyy.c"
	-@erase "y.tab.c"
	-@erase "y.tab.h"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /ML /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\batchgen.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\batchgen.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\batchgen.pdb" /machine:I386 /out:"$(OUTDIR)\batchgen.exe" 
LINK32_OBJS= \
	"$(INTDIR)\batchgen.obj" \
	"$(INTDIR)\bkpatch.obj" \
	"$(INTDIR)\fileread.obj" \
	"$(INTDIR)\lex.yy.obj" \
	"$(INTDIR)\optim.obj" \
	"$(INTDIR)\sr.obj" \
	"$(INTDIR)\stacks.obj" \
	"$(INTDIR)\y.tab.obj"

"$(OUTDIR)\batchgen.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "batchgen - Win32 Debug"

OUTDIR=.\..\bin
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\..\bin
# End Custom Macros

ALL : ".\y.tab.h" ".\y.tab.c" ".\lexyy.c" "$(OUTDIR)\batchgen_debug.exe" "$(OUTDIR)\batchgen.bsc"


CLEAN :
	-@erase "$(INTDIR)\batchgen.obj"
	-@erase "$(INTDIR)\batchgen.sbr"
	-@erase "$(INTDIR)\bkpatch.obj"
	-@erase "$(INTDIR)\bkpatch.sbr"
	-@erase "$(INTDIR)\fileread.obj"
	-@erase "$(INTDIR)\fileread.sbr"
	-@erase "$(INTDIR)\lex.yy.obj"
	-@erase "$(INTDIR)\lex.yy.sbr"
	-@erase "$(INTDIR)\optim.obj"
	-@erase "$(INTDIR)\optim.sbr"
	-@erase "$(INTDIR)\sr.obj"
	-@erase "$(INTDIR)\sr.sbr"
	-@erase "$(INTDIR)\stacks.obj"
	-@erase "$(INTDIR)\stacks.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\y.tab.obj"
	-@erase "$(INTDIR)\y.tab.sbr"
	-@erase "$(OUTDIR)\batchgen.bsc"
	-@erase "$(OUTDIR)\batchgen_debug.exe"
	-@erase "$(OUTDIR)\batchgen_debug.ilk"
	-@erase "$(OUTDIR)\batchgen_debug.pdb"
	-@erase "lexyy.c"
	-@erase "y.tab.c"
	-@erase "y.tab.h"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /MLd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\batchgen.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\batchgen.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\batchgen.sbr" \
	"$(INTDIR)\bkpatch.sbr" \
	"$(INTDIR)\fileread.sbr" \
	"$(INTDIR)\lex.yy.sbr" \
	"$(INTDIR)\optim.sbr" \
	"$(INTDIR)\sr.sbr" \
	"$(INTDIR)\stacks.sbr" \
	"$(INTDIR)\y.tab.sbr"

"$(OUTDIR)\batchgen.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\batchgen_debug.pdb" /debug /machine:I386 /out:"$(OUTDIR)\batchgen_debug.exe" 
LINK32_OBJS= \
	"$(INTDIR)\batchgen.obj" \
	"$(INTDIR)\bkpatch.obj" \
	"$(INTDIR)\fileread.obj" \
	"$(INTDIR)\lex.yy.obj" \
	"$(INTDIR)\optim.obj" \
	"$(INTDIR)\sr.obj" \
	"$(INTDIR)\stacks.obj" \
	"$(INTDIR)\y.tab.obj"

"$(OUTDIR)\batchgen_debug.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("batchgen.dep")
!INCLUDE "batchgen.dep"
!ELSE 
!MESSAGE Warning: cannot find "batchgen.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "batchgen - Win32 Release" || "$(CFG)" == "batchgen - Win32 Debug"
SOURCE=..\source\batchgen.c

!IF  "$(CFG)" == "batchgen - Win32 Release"


"$(INTDIR)\batchgen.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "batchgen - Win32 Debug"


"$(INTDIR)\batchgen.obj"	"$(INTDIR)\batchgen.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\source\bkpatch.c

!IF  "$(CFG)" == "batchgen - Win32 Release"


"$(INTDIR)\bkpatch.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "batchgen - Win32 Debug"


"$(INTDIR)\bkpatch.obj"	"$(INTDIR)\bkpatch.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\source\fileread.c

!IF  "$(CFG)" == "batchgen - Win32 Release"


"$(INTDIR)\fileread.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "batchgen - Win32 Debug"


"$(INTDIR)\fileread.obj"	"$(INTDIR)\fileread.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\source\lex.yy.c

!IF  "$(CFG)" == "batchgen - Win32 Release"


"$(INTDIR)\lex.yy.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "batchgen - Win32 Debug"


"$(INTDIR)\lex.yy.obj"	"$(INTDIR)\lex.yy.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\source\optim.c

!IF  "$(CFG)" == "batchgen - Win32 Release"


"$(INTDIR)\optim.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "batchgen - Win32 Debug"


"$(INTDIR)\optim.obj"	"$(INTDIR)\optim.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\source\sr.c

!IF  "$(CFG)" == "batchgen - Win32 Release"


"$(INTDIR)\sr.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "batchgen - Win32 Debug"


"$(INTDIR)\sr.obj"	"$(INTDIR)\sr.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\source\stacks.c

!IF  "$(CFG)" == "batchgen - Win32 Release"


"$(INTDIR)\stacks.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "batchgen - Win32 Debug"


"$(INTDIR)\stacks.obj"	"$(INTDIR)\stacks.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\source\y.tab.c

!IF  "$(CFG)" == "batchgen - Win32 Release"


"$(INTDIR)\y.tab.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "batchgen - Win32 Debug"


"$(INTDIR)\y.tab.obj"	"$(INTDIR)\y.tab.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\source\batchgen.l

!IF  "$(CFG)" == "batchgen - Win32 Release"

InputPath=..\source\batchgen.l

".\lexyy.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	cd ..\source 
	C:\bin\flex batchgen.l 
<< 
	

!ELSEIF  "$(CFG)" == "batchgen - Win32 Debug"

InputPath=..\source\batchgen.l

".\lexyy.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	cd ..\source 
	C:\bin\flex -d batchgen.l 
<< 
	

!ENDIF 

SOURCE=..\source\batchgen.y

!IF  "$(CFG)" == "batchgen - Win32 Release"

InputPath=..\source\batchgen.y

".\y.tab.c"	".\y.tab.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	cd ..\source 
	C:\bin\yacc -vd batchgen.y
<< 
	

!ELSEIF  "$(CFG)" == "batchgen - Win32 Debug"

InputPath=..\source\batchgen.y

".\y.tab.c"	".\y.tab.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	cd ..\source 
	C:\bin\yacc -vdt batchgen.y
<< 
	

!ENDIF 


!ENDIF 

