# Microsoft Developer Studio Project File - Name="FrontServer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=FrontServer - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "FrontServer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "FrontServer.mak" CFG="FrontServer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "FrontServer - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "FrontServer - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Server/FrontServer", BDBAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "FrontServer - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x412 /d "NDEBUG"
# ADD RSC /l 0x412 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 /out:"C:\FrontServer\FrontServer.exe"

!ELSEIF  "$(CFG)" == "FrontServer - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x412 /d "_DEBUG"
# ADD RSC /l 0x412 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /out:"C:\FrontServer\FrontServer.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "FrontServer - Win32 Release"
# Name "FrontServer - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AuthProcess.cpp
# End Source File
# Begin Source File

SOURCE=.\FrontClientProtocol.cpp
# End Source File
# Begin Source File

SOURCE=.\FrontGameProtocol.cpp
# End Source File
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# Begin Source File

SOURCE=.\WorldList.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\AuthServer\AuthMsg.h
# End Source File
# Begin Source File

SOURCE=.\AuthProcess.h
# End Source File
# Begin Source File

SOURCE=.\FrontClientProtocol.h
# End Source File
# Begin Source File

SOURCE=.\FrontGameProtocol.h
# End Source File
# Begin Source File

SOURCE=.\FrontMsg.h
# End Source File
# Begin Source File

SOURCE=.\FrontServer.h
# End Source File
# Begin Source File

SOURCE=.\WorldList.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "ITZNetLib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\NetworkLib\itznetlib\itzbase.h
# End Source File
# Begin Source File

SOURCE=..\..\NetworkLib\itznetlib\ITZEncrypt.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NetworkLib\itznetlib\ITZEncrypt.h
# End Source File
# Begin Source File

SOURCE=..\..\NetworkLib\itznetlib\ITZList.h
# End Source File
# Begin Source File

SOURCE=..\..\NetworkLib\itznetlib\ITZListen.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NetworkLib\itznetlib\ITZListen.h
# End Source File
# Begin Source File

SOURCE=..\..\NetworkLib\itznetlib\ITZNetIOCP.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NetworkLib\itznetlib\ITZNetIOCP.h
# End Source File
# Begin Source File

SOURCE=..\..\NetworkLib\itznetlib\ITZNetwork.h
# End Source File
# Begin Source File

SOURCE=..\..\NetworkLib\itznetlib\ITZNetworkThread.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NetworkLib\itznetlib\ITZNetworkThread.h
# End Source File
# Begin Source File

SOURCE=..\..\NetworkLib\itznetlib\ITZObject.h
# End Source File
# Begin Source File

SOURCE=..\..\NetworkLib\itznetlib\ITZPerson.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NetworkLib\itznetlib\ITZPerson.h
# End Source File
# Begin Source File

SOURCE=..\..\NetworkLib\itznetlib\ITZQList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NetworkLib\itznetlib\ITZQList.h
# End Source File
# Begin Source File

SOURCE=..\..\NetworkLib\itznetlib\ITZQueue.h
# End Source File
# Begin Source File

SOURCE=..\..\NetworkLib\itznetlib\ITZRecvBuffer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NetworkLib\itznetlib\ITZRecvBuffer.h
# End Source File
# Begin Source File

SOURCE=..\..\NetworkLib\itznetlib\ITZSendBuffer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NetworkLib\itznetlib\ITZSendBuffer.h
# End Source File
# Begin Source File

SOURCE=..\..\NetworkLib\itznetlib\ITZServer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NetworkLib\itznetlib\ITZServer.h
# End Source File
# Begin Source File

SOURCE=..\..\NetworkLib\itznetlib\ITZSession.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NetworkLib\itznetlib\ITZSession.h
# End Source File
# Begin Source File

SOURCE=..\..\NetworkLib\itznetlib\ITZSessionFactory.h
# End Source File
# Begin Source File

SOURCE=..\..\NetworkLib\itznetlib\ITZSessionManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NetworkLib\itznetlib\ITZSessionManager.h
# End Source File
# Begin Source File

SOURCE=..\..\NetworkLib\itznetlib\ITZWinApp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\NetworkLib\itznetlib\ITZWinApp.h
# End Source File
# End Group
# Begin Group "AgentProcess"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AgentProcess.cpp
# End Source File
# Begin Source File

SOURCE=.\AgentProcess.h
# End Source File
# Begin Source File

SOURCE=..\..\AdminSystem\MasterServer\MasterMsg.h
# End Source File
# End Group
# End Target
# End Project
