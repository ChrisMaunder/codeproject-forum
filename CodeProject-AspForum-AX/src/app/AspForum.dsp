# Microsoft Developer Studio Project File - Name="AspForum" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=AspForum - Win32 KETO _ Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "AspForum.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "AspForum.mak" CFG="AspForum - Win32 KETO _ Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "AspForum - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "AspForum - Win32 Unicode Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "AspForum - Win32 Release MinSize" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "AspForum - Win32 Release MinDependency" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "AspForum - Win32 Unicode Release MinSize" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "AspForum - Win32 Unicode Release MinDependency" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "AspForum - Win32 KETO _ Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "AspForum - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\bin"
# PROP Intermediate_Dir "..\..\bin\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "_MBCS" /D "LOGGING" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# Begin Custom Build - Die Registrierung wird durchgeführt
TargetPath=\Dokumente und Einstellungen\Uwe\Eigene Dateien\Projekte\AspForum\bin\AspForum.dll
InputPath=\Dokumente und Einstellungen\Uwe\Eigene Dateien\Projekte\AspForum\bin\AspForum.dll
SOURCE="$(InputPath)"

"\\KRONOS\daten\inetpub\controls\aspforum.dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(TargetPath)" \\KRONOS\daten\inetpub\controls\aspforum.dll 
	d: 
	cd D:\Inetpub\controls 
	call D:\Inetpub\controls\aspforum_register.bat 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "AspForum - Win32 Unicode Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugU"
# PROP BASE Intermediate_Dir "DebugU"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\bin"
# PROP Intermediate_Dir "..\..\bin\DebugU"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "_UNICODE" /D "LOGGING" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# Begin Custom Build - Die Registrierung wird durchgeführt
TargetPath=\Dokumente und Einstellungen\Uwe\Eigene Dateien\Projekte\AspForum\bin\AspForum.dll
InputPath=\Dokumente und Einstellungen\Uwe\Eigene Dateien\Projekte\AspForum\bin\AspForum.dll
SOURCE="$(InputPath)"

"\\KRONOS\daten\inetpub\controls\aspforum.dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	copy "$(TargetPath)" \\KRONOS\daten\inetpub\controls\aspforum.dll 
	d: 
	cd D:\Inetpub\controls 
	call D:\Inetpub\controls\aspforum_register.bat 
	goto end 
	:NOTNT 
	echo Warnung : Unicode DLL kann unter Windows 95 nicht registriert werden 
	:end 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "AspForum - Win32 Release MinSize"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMinSize"
# PROP BASE Intermediate_Dir "ReleaseMinSize"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\bin"
# PROP Intermediate_Dir "..\..\bin\ReleaseMinSize"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O1 /D "NDEBUG" /D "_MBCS" /D "_ATL_DLL" /D "LOGGING" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# Begin Custom Build - Die Registrierung wird durchgeführt
TargetPath=\Dokumente und Einstellungen\Uwe\Eigene Dateien\Projekte\AspForum\bin\AspForum.dll
InputPath=\Dokumente und Einstellungen\Uwe\Eigene Dateien\Projekte\AspForum\bin\AspForum.dll
SOURCE="$(InputPath)"

"\\KRONOS\daten\inetpub\controls\aspforum.dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(TargetPath)" \\KRONOS\daten\inetpub\controls\aspforum.dll 
	d: 
	cd D:\Inetpub\controls 
	call D:\Inetpub\controls\aspforum_register.bat 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "AspForum - Win32 Release MinDependency"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMinDependency"
# PROP BASE Intermediate_Dir "ReleaseMinDependency"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\bin"
# PROP Intermediate_Dir "..\..\bin\ReleaseMinDependency"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O1 /D "NDEBUG" /D "_MBCS" /D "_ATL_STATIC_REGISTRY" /D "LOGGING" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# Begin Custom Build - Die Registrierung wird durchgeführt
TargetPath=\Dokumente und Einstellungen\Uwe\Eigene Dateien\Projekte\AspForum\bin\AspForum.dll
InputPath=\Dokumente und Einstellungen\Uwe\Eigene Dateien\Projekte\AspForum\bin\AspForum.dll
SOURCE="$(InputPath)"

"\\KRONOS\daten\inetpub\controls\aspforum.dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(TargetPath)" \\KRONOS\daten\inetpub\controls\aspforum.dll 
	d: 
	cd D:\Inetpub\controls 
	call D:\Inetpub\controls\aspforum_register.bat 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "AspForum - Win32 Unicode Release MinSize"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseUMinSize"
# PROP BASE Intermediate_Dir "ReleaseUMinSize"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\bin"
# PROP Intermediate_Dir "..\..\bin\ReleaseUMinSize"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O1 /D "NDEBUG" /D "_UNICODE" /D "_ATL_DLL" /D "LOGGING" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# Begin Custom Build - Die Registrierung wird durchgeführt
TargetPath=\Dokumente und Einstellungen\Uwe\Eigene Dateien\Projekte\AspForum\bin\AspForum.dll
InputPath=\Dokumente und Einstellungen\Uwe\Eigene Dateien\Projekte\AspForum\bin\AspForum.dll
SOURCE="$(InputPath)"

"\\KRONOS\daten\inetpub\controls\aspforum.dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	copy "$(TargetPath)" \\KRONOS\daten\inetpub\controls\aspforum.dll 
	d: 
	cd D:\Inetpub\controls 
	call D:\Inetpub\controls\aspforum_register.bat 
	goto end 
	:NOTNT 
	echo Warnung : Unicode DLL kann unter Windows 95 nicht registriert werden 
	:end 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "AspForum - Win32 Unicode Release MinDependency"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseUMinDependency"
# PROP BASE Intermediate_Dir "ReleaseUMinDependency"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\bin"
# PROP Intermediate_Dir "..\..\bin\ReleaseUMinDependency"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O1 /D "NDEBUG" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "LOGGING" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# Begin Custom Build - Die Registrierung wird durchgeführt
TargetPath=\Dokumente und Einstellungen\Uwe\Eigene Dateien\Projekte\AspForum\bin\AspForum.dll
InputPath=\Dokumente und Einstellungen\Uwe\Eigene Dateien\Projekte\AspForum\bin\AspForum.dll
SOURCE="$(InputPath)"

"\\KRONOS\daten\inetpub\controls\aspforum.dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	copy "$(TargetPath)" \\KRONOS\daten\inetpub\controls\aspforum.dll 
	d: 
	cd D:\Inetpub\controls 
	call D:\Inetpub\controls\aspforum_register.bat 
	goto end 
	:NOTNT 
	echo Warnung : Unicode DLL kann unter Windows 95 nicht registriert werden 
	:end 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "AspForum - Win32 KETO _ Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "AspForum___Win32_KETO___Debug"
# PROP BASE Intermediate_Dir "AspForum___Win32_KETO___Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\bin\AspForum___Win32_KETO___Debug"
# PROP Intermediate_Dir "..\..\bin\AspForum___Win32_KETO___Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "_MBCS" /D "LOGGING" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "_MBCS" /D "LOGGING" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# Begin Custom Build - Die Registrierung wird durchgeführt
TargetPath=\Dokumente und Einstellungen\Uwe\Eigene Dateien\Projekte\AspForum\bin\AspForum___Win32_KETO___Debug\AspForum.dll
InputPath=\Dokumente und Einstellungen\Uwe\Eigene Dateien\Projekte\AspForum\bin\AspForum___Win32_KETO___Debug\AspForum.dll
SOURCE="$(InputPath)"

"C:\Dokumente und Einstellungen\Uwe\Eigene Dateien\Projekte\AspForum\bin\AspForum.dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(TargetPath)" "C:\Dokumente und Einstellungen\Uwe\Eigene Dateien\Projekte\AspForum\bin\AspForum.dll" 
	regsvr32 /s /c "C:\Dokumente und Einstellungen\Uwe\Eigene Dateien\Projekte\AspForum\bin\AspForum.dll" 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "AspForum - Win32 Debug"
# Name "AspForum - Win32 Unicode Debug"
# Name "AspForum - Win32 Release MinSize"
# Name "AspForum - Win32 Release MinDependency"
# Name "AspForum - Win32 Unicode Release MinSize"
# Name "AspForum - Win32 Unicode Release MinDependency"
# Name "AspForum - Win32 KETO _ Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AspForum.cpp
# End Source File
# Begin Source File

SOURCE=.\AspForum.def
# End Source File
# Begin Source File

SOURCE=.\AspForum.idl
# ADD MTL /tlb ".\AspForum.tlb" /h "AspForum.h" /iid "AspForum_i.c" /Oicf
# End Source File
# Begin Source File

SOURCE=.\AspForum.rc
# End Source File
# Begin Source File

SOURCE=..\common\common.cpp
# End Source File
# Begin Source File

SOURCE=.\dlldatax.c
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\common\Error.cpp
# End Source File
# Begin Source File

SOURCE=.\Forum2.cpp
# End Source File
# Begin Source File

SOURCE=..\foreign\hightime.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\common\Logging.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\common\tree.cpp
# End Source File
# Begin Source File

SOURCE=..\common\Xept.cpp
# End Source File
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\common\common.h
# End Source File
# Begin Source File

SOURCE=.\dlldatax.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\common\Error.h
# End Source File
# Begin Source File

SOURCE=.\Forum2.h
# End Source File
# Begin Source File

SOURCE=..\foreign\hightime.h
# End Source File
# Begin Source File

SOURCE=..\foreign\hightime.inl
# End Source File
# Begin Source File

SOURCE=..\common\Logging.h
# End Source File
# Begin Source File

SOURCE=..\common\MemoryEx.h
# End Source File
# Begin Source File

SOURCE=..\common\MemoryEx.inl
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\common\tree.h
# End Source File
# Begin Source File

SOURCE=..\common\Xept.h
# End Source File
# End Group
# Begin Group "Ressourcendateien"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Forum2.rgs
# End Source File
# End Group
# End Target
# End Project
