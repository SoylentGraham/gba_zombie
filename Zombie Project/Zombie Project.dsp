# Microsoft Developer Studio Project File - Name="Zombie Project" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=Zombie Project - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Zombie Project.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Zombie Project.mak" CFG="Zombie Project - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Zombie Project - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "Zombie Project - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "Zombie Project - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Cmd_Line "NMAKE /f "Zombie Project.mak""
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "Zombie Project.exe"
# PROP BASE Bsc_Name "Zombie Project.bsc"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Cmd_Line "NMAKE /f "Zombie Project.mak""
# PROP Rebuild_Opt "/a"
# PROP Target_File "Zombie Project.exe"
# PROP Bsc_Name "Zombie Project.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "Zombie Project - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Cmd_Line "NMAKE /f "Zombie Project.mak""
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "Zombie Project.exe"
# PROP BASE Bsc_Name "Zombie Project.bsc"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Cmd_Line "../make.cmd"
# PROP Rebuild_Opt "/a"
# PROP Target_File "Zombie Project.exe"
# PROP Bsc_Name ""
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "Zombie Project - Win32 Release"
# Name "Zombie Project - Win32 Debug"

!IF  "$(CFG)" == "Zombie Project - Win32 Release"

!ELSEIF  "$(CFG)" == "Zombie Project - Win32 Debug"

!ENDIF 

# Begin Group "c Core"

# PROP Default_Filter ""
# Begin Group "h Core"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\core\animated_sprite.h
# End Source File
# Begin Source File

SOURCE=..\core\bg_handle.h
# End Source File
# Begin Source File

SOURCE=..\core\collisions.h
# End Source File
# Begin Source File

SOURCE=..\core\core.h
# End Source File
# Begin Source File

SOURCE=..\core\dma.h
# End Source File
# Begin Source File

SOURCE=..\core\font.h
# End Source File
# Begin Source File

SOURCE=..\core\gba.h
# End Source File
# Begin Source File

SOURCE=..\core\keypad.h
# End Source File
# Begin Source File

SOURCE=..\core\math.h
# End Source File
# Begin Source File

SOURCE=..\core\sprites.h
# End Source File
# Begin Source File

SOURCE=..\core\tile_alloc.h
# End Source File
# Begin Source File

SOURCE=..\core\tiles.h
# End Source File
# Begin Source File

SOURCE=..\core\types.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\core\animated_sprite.c
# End Source File
# Begin Source File

SOURCE=..\core\bg_handle.c
# End Source File
# Begin Source File

SOURCE=..\core\collisions.c
# End Source File
# Begin Source File

SOURCE=..\core\core.c
# End Source File
# Begin Source File

SOURCE=..\core\dma.c
# End Source File
# Begin Source File

SOURCE=..\core\font.c
# End Source File
# Begin Source File

SOURCE=..\core\math.c
# End Source File
# Begin Source File

SOURCE=..\core\sprites.c
# End Source File
# Begin Source File

SOURCE=..\core\tile_alloc.c
# End Source File
# Begin Source File

SOURCE=..\core\tiles.c
# End Source File
# End Group
# Begin Group "c Game"

# PROP Default_Filter ""
# Begin Group "h Game"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\game\camera.h
# End Source File
# Begin Source File

SOURCE=..\game\game.h
# End Source File
# Begin Source File

SOURCE=..\game\main.h
# End Source File
# Begin Source File

SOURCE=..\game\maps.h
# End Source File
# Begin Source File

SOURCE=..\game\player.h
# End Source File
# Begin Source File

SOURCE=..\game\tile_sets.h
# End Source File
# Begin Source File

SOURCE=..\game\torch.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\game\camera.c
# End Source File
# Begin Source File

SOURCE=..\game\game.c
# End Source File
# Begin Source File

SOURCE=..\game\main.c
# End Source File
# Begin Source File

SOURCE=..\game\maps.c
# End Source File
# Begin Source File

SOURCE=..\game\player.c
# End Source File
# Begin Source File

SOURCE=..\game\tile_sets.c
# End Source File
# Begin Source File

SOURCE=..\game\torch.c
# End Source File
# End Group
# Begin Group "Media"

# PROP Default_Filter ""
# Begin Group "c gfx"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\media\gfx\blank.c
# End Source File
# Begin Source File

SOURCE=..\media\gfx\font.c
# End Source File
# Begin Source File

SOURCE=..\media\gfx\generic_mask.c
# End Source File
# Begin Source File

SOURCE=..\media\gfx\palette.c
# End Source File
# Begin Source File

SOURCE=..\media\gfx\torch_beam.c
# End Source File
# Begin Source File

SOURCE=..\media\gfx\u8_masks.c
# End Source File
# Begin Source File

SOURCE=..\media\gfx\walls_green.c
# End Source File
# End Group
# Begin Group "c maps"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\media\map\map_level_1.c
# End Source File
# Begin Source File

SOURCE=..\media\map\torch_beam_map.c
# End Source File
# End Group
# Begin Source File

SOURCE=..\media\map\map_data.h
# End Source File
# Begin Source File

SOURCE=..\media\gfx\media.h
# End Source File
# End Group
# End Target
# End Project
