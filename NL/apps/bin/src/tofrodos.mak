# Microsoft Developer Studio Generated NMAKE File, Based on tofrodos.dsp
!IF "$(CFG)" == ""
CFG=tofrodos - Win32 Debug
!MESSAGE No configuration specified. Defaulting to tofrodos - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "tofrodos - Win32 Release" && "$(CFG)" != "tofrodos - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "tofrodos.mak" CFG="tofrodos - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "tofrodos - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "tofrodos - Win32 Debug" (based on "Win32 (x86) Console Application")
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

!IF  "$(CFG)" == "tofrodos - Win32 Release"

OUTDIR=.\bin
INTDIR=.\bin
# Begin Custom Macros
OutDir=.\bin
# End Custom Macros

ALL : "$(OUTDIR)\fromdos.exe"


CLEAN :
	-@erase "$(INTDIR)\getopt.obj"
	-@erase "$(INTDIR)\init.obj"
	-@erase "$(INTDIR)\tofrodos.obj"
	-@erase "$(INTDIR)\utility.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\fromdos.exe"
	-@erase "$(OUTDIR)\fromdos.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W4 /WX /GX /Zi /O2 /I "lib" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\tofrodos.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib setargv.obj /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\fromdos.pdb" /debug /machine:I386 /out:"$(OUTDIR)\fromdos.exe" /opt:ref /opt:icf 
LINK32_OBJS= \
	"$(INTDIR)\getopt.obj" \
	"$(INTDIR)\init.obj" \
	"$(INTDIR)\tofrodos.obj" \
	"$(INTDIR)\utility.obj"

"$(OUTDIR)\fromdos.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "tofrodos - Win32 Debug"

OUTDIR=.\bin
INTDIR=.\bin
# Begin Custom Macros
OutDir=.\bin
# End Custom Macros

ALL : "$(OUTDIR)\fromdos.exe"


CLEAN :
	-@erase "$(INTDIR)\getopt.obj"
	-@erase "$(INTDIR)\init.obj"
	-@erase "$(INTDIR)\tofrodos.obj"
	-@erase "$(INTDIR)\utility.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\fromdos.exe"
	-@erase "$(OUTDIR)\fromdos.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W4 /WX /Gm /GX /Zi /Od /I "lib" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\tofrodos.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib setargv.obj /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\fromdos.pdb" /debug /machine:I386 /out:"$(OUTDIR)\fromdos.exe" 
LINK32_OBJS= \
	"$(INTDIR)\getopt.obj" \
	"$(INTDIR)\init.obj" \
	"$(INTDIR)\tofrodos.obj" \
	"$(INTDIR)\utility.obj"

"$(OUTDIR)\fromdos.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("tofrodos.dep")
!INCLUDE "tofrodos.dep"
!ELSE 
!MESSAGE Warning: cannot find "tofrodos.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "tofrodos - Win32 Release" || "$(CFG)" == "tofrodos - Win32 Debug"
SOURCE=.\Lib\getopt.c

"$(INTDIR)\getopt.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\init.c

"$(INTDIR)\init.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\tofrodos.c

"$(INTDIR)\tofrodos.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\utility.c

"$(INTDIR)\utility.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

