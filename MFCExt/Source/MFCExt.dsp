# Microsoft Developer Studio Project File - Name="MFCExt" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=MFCExt - Win32 Release
!MESSAGE Dies ist kein g�ltiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und f�hren Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "MFCExt.mak".
!MESSAGE 
!MESSAGE Sie k�nnen beim Ausf�hren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "MFCExt.mak" CFG="MFCExt - Win32 Release"
!MESSAGE 
!MESSAGE F�r die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "MFCExt - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MFCExt - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "MFCExt"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MFCExt - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../output/Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /Zi /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 Shlwapi.lib version.lib /nologo /subsystem:windows /dll /debug /debugtype:both /machine:I386 /def:".\MFCExt.def" /implib:"../Lib/MFCExt.lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "MFCExt - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../../output/Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 Shlwapi.lib version.lib /nologo /subsystem:windows /dll /debug /machine:I386 /def:".\MFCExtD.def" /out:"../../output/Debug/MFCExtD.dll" /implib:"../Lib/MFCExtD.lib" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "MFCExt - Win32 Release"
# Name "MFCExt - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CollectionException.cpp
# End Source File
# Begin Source File

SOURCE=.\ComboColorPicker.cpp
# End Source File
# Begin Source File

SOURCE=.\ExtAfx.cpp
# End Source File
# Begin Source File

SOURCE=.\FileDialogEx.cpp
# End Source File
# Begin Source File

SOURCE=.\FileVersionInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderSelect.cpp
# End Source File
# Begin Source File

SOURCE=.\FormatEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\IniFile.cpp
# End Source File
# Begin Source File

SOURCE=.\MFCExt.cpp
# End Source File
# Begin Source File

SOURCE=.\MFCExt.def
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\MFCExt.rc
# End Source File
# Begin Source File

SOURCE=.\MFCExtD.def
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\MRUCombo.cpp
# End Source File
# Begin Source File

SOURCE=.\MRUStringList.cpp
# End Source File
# Begin Source File

SOURCE=.\PathTool.cpp
# End Source File
# Begin Source File

SOURCE=.\SingleInstanceWinApp.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\UniqueStringList.cpp
# End Source File
# Begin Source File

SOURCE=.\WildCard.cpp
# End Source File
# Begin Source File

SOURCE=.\WorkerThread.cpp
# End Source File
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AutoBuildCount.h
# End Source File
# Begin Source File

SOURCE=.\CollectionException.h
# End Source File
# Begin Source File

SOURCE=.\ComboColorPicker.h
# End Source File
# Begin Source File

SOURCE=.\ComHelpers.h
# End Source File
# Begin Source File

SOURCE=.\DoubleBuffer.h
# End Source File
# Begin Source File

SOURCE=..\Include\ExtAfx.h
# End Source File
# Begin Source File

SOURCE=..\Include\ExtApp.h
# End Source File
# Begin Source File

SOURCE=..\Include\ExtCollection.h
# End Source File
# Begin Source File

SOURCE=..\Include\ExtCOM.h
# End Source File
# Begin Source File

SOURCE=..\Include\ExtControls.h
# End Source File
# Begin Source File

SOURCE=..\Include\ExtDebug.h
# End Source File
# Begin Source File

SOURCE=..\Include\ExtDialog.h
# End Source File
# Begin Source File

SOURCE=..\Include\ExtException.h
# End Source File
# Begin Source File

SOURCE=..\Include\ExtTools.h
# End Source File
# Begin Source File

SOURCE=.\FileDialogEx.h
# End Source File
# Begin Source File

SOURCE=.\FileVersionInfo.h
# End Source File
# Begin Source File

SOURCE=.\FolderSelect.h
# End Source File
# Begin Source File

SOURCE=.\FormatEdit.h
# End Source File
# Begin Source File

SOURCE=.\IniFile.h
# End Source File
# Begin Source File

SOURCE=.\MRUCombo.h
# End Source File
# Begin Source File

SOURCE=.\MRUList.h
# End Source File
# Begin Source File

SOURCE=.\MRUStringList.h
# End Source File
# Begin Source File

SOURCE=.\PathTool.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SingleInstanceWinApp.h
# End Source File
# Begin Source File

SOURCE=.\SortArray.h
# End Source File
# Begin Source File

SOURCE=.\SortList.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\UniqueStringList.h
# End Source File
# Begin Source File

SOURCE=.\WildCard.h
# End Source File
# Begin Source File

SOURCE=.\WorkerThread.h
# End Source File
# End Group
# Begin Group "Ressourcendateien"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\MFCExt.rc2
# End Source File
# End Group
# End Target
# End Project
