# This installs two files, app.exe and logo.ico, creates a start menu shortcut, builds an uninstaller, and
# adds uninstall information to the registry for Add/Remove Programs
 
# To get started, put this script into a folder with the two files (app.exe, logo.ico, and license.rtf -
# You'll have to create these yourself) and run makensis on it
 
# If you change the names "app.exe", "logo.ico", or "license.rtf" you should do a search and replace - they
# show up in a few places.
# All the other settings can be tweaked by editing the !defines at the top of this script
!include "MUI2.nsh"
!define APPNAME "NuttyPutters"
!define COMPANYNAME "NuttyPutters"
!define DESCRIPTION "NuttyPutters"
# These three must be integers
!define VERSIONMAJOR 1
!define VERSIONMINOR 1
!define VERSIONBUILD 1

# This is the size (in kB) of all the files copied into "Program Files"
!define INSTALLSIZE 7233
 
RequestExecutionLevel admin ;Require admin rights on NT6+ (When UAC is turned on)
 
InstallDir "${DESKTOP}\${COMPANYNAME}\${APPNAME}"
 
# rtf or txt file - remember if it is txt, it must be in the DOS text format (\r\n)
#LicenseData "license.rtf"
# This will be in the installer/uninstaller's title bar
Name "${COMPANYNAME} - ${APPNAME}"
outFile "NuttyPuttersx64.exe"
 
!include LogicLib.nsh
 
# Just three pages - license agreement, install location, and installation
page directory
Page instfiles
 
!macro VerifyUserIsAdmin
UserInfo::GetAccountType
pop $0
${If} $0 != "admin" ;Require admin rights on NT4+
        messageBox mb_iconstop "Administrator rights required!"
        setErrorLevel 740 ;ERROR_ELEVATION_REQUIRED
        quit
${EndIf}
!macroend
 
function .onInit
	setShellVarContext all
	!insertmacro VerifyUserIsAdmin
functionEnd
 
section "install"
	# Files for the install directory - to build the installer, these should be in the same directory as the install script (this file)
	setOutPath $INSTDIR
	# Release folder contents
	file "x64\Release\*.*"
	# All dlls required
	file "NuttyPutters\*.dll"
	# All images required in install dir
	file "NuttyPutters\*.jpg" 
	file "NuttyPutters\*.png"
	# Save files
	file "NuttyPutters\*.csv"
	# Object files
	file "NuttyPutters\*.obj"
	# Shaders
	file  "NuttyPutters\*.frag"
	file  "NuttyPutters\*.vert"
	# Readme
	file "NuttyPutters\README.txt"
	
	# SETUP folder structure
	# create the folder
	createDirectory "$INSTDIR\audio\"
	# set the out dir for following file copy commands
	SetOutPath "$INSTDIR\audio\"
	# copy files in this folder to before set outdir
	file /r "NuttyPutters\audio\"
	
	createDirectory "$INSTDIR\controller\"
	SetOutPath "$INSTDIR\controller\"
	file /r "NuttyPutters\controller\"
	
	createDirectory "$INSTDIR\input"
	SetOutPath "$INSTDIR\input\"
	file /r "NuttyPutters\input\"
	
	createDirectory "$INSTDIR\Mainmenu\"
	SetOutPath "$INSTDIR\Mainmenu\"
	file /r "NuttyPutters\Mainmenu\"
	
	createDirectory "$INSTDIR\options\"
	SetOutPath "$INSTDIR\options\"
	file /r "NuttyPutters\options\"
	
	createDirectory "$INSTDIR\pause\"
	SetOutPath "$INSTDIR\pause\"
	file /r "NuttyPutters\pause\"
	
	createDirectory "$INSTDIR\pause\"
	SetOutPath "$INSTDIR\pause\"
	file /r "NuttyPutters\pause\"
	
	createDirectory "$INSTDIR\savesImages\"
	SetOutPath "$INSTDIR\savesImages\"
	file /r "NuttyPutters\savesImages\"
	
	createDirectory "$INSTDIR\skyboxes\"
	SetOutPath "$INSTDIR\skyboxes\"
	file /r "NuttyPutters\skyboxes\"


	
    #file /r "x64\Debug\*.*"
	#file /r "NuttyPutters\x64\Debug\*.*"
	# Uninstaller - See function un.onInit and section "uninstall" for configuration
	writeUninstaller "$INSTDIR\NuttyPuttersx64Uninstall.exe"
 
	# Start Menu
	createDirectory "$SMPROGRAMS\${COMPANYNAME}"
	createShortCut "$SMPROGRAMS\${COMPANYNAME}\${APPNAME}.lnk" "$INSTDIR\app.exe" "" "$INSTDIR\logo.ico"
 
	# Registry information for add/remove programs
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "DisplayName" "${COMPANYNAME} - ${APPNAME} - ${DESCRIPTION}"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "UninstallString" "$\"$INSTDIR\uninstall.exe$\""
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "QuietUninstallString" "$\"$INSTDIR\uninstall.exe$\" /S"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "InstallLocation" "$\"$INSTDIR$\""
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "DisplayIcon" "$\"$INSTDIR\logo.ico$\""
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "Publisher" "$\"${COMPANYNAME}$\""
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "HelpLink" "$\"${HELPURL}$\""
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "URLUpdateInfo" "$\"${UPDATEURL}$\""
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "URLInfoAbout" "$\"${ABOUTURL}$\""
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "DisplayVersion" "$\"${VERSIONMAJOR}.${VERSIONMINOR}.${VERSIONBUILD}$\""
	WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "VersionMajor" ${VERSIONMAJOR}
	WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "VersionMinor" ${VERSIONMINOR}
	# There is no option for modifying or repairing the install
	WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "NoModify" 1
	WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "NoRepair" 1
	# Set the INSTALLSIZE constant (!defined at the top of this script) so Add/Remove Programs can accurately report the size
	WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "EstimatedSize" ${INSTALLSIZE}
sectionEnd
 
# Uninstaller
 
function un.onInit
	SetShellVarContext all
 
	#Verify the uninstaller - last chance to back out
	MessageBox MB_OKCANCEL "Permanantly remove ${APPNAME}?" IDOK next
		Abort
	next:
	!insertmacro VerifyUserIsAdmin
functionEnd
 
section "uninstall"
 
	# Remove Start Menu launcher
	delete "$SMPROGRAMS\${COMPANYNAME}\${APPNAME}.lnk"
	# Try to remove the Start Menu folder - this will only happen if it is empty
	rmDir "$SMPROGRAMS\${COMPANYNAME}"
 
	# Remove files from folders
	delete $INSTDIR\audio\*.*
	delete $INSTDIR\controller\*.*
	delete $INSTDIR\input\*.*
	delete $INSTDIR\Mainmenu\*.*
	delete $INSTDIR\options\*.*
	delete $INSTDIR\pause\*.*
	delete $INSTDIR\savesImages\*.*
	delete $INSTDIR\skyboxes\*.*
	# Remove files from install dir
    delete $INSTDIR\*.*
	# Always delete uninstaller as the delete last action
	delete $INSTDIR\NuttyPuttersUninstall.exe
	# Clean up empty folders
	rmDir $INSTDIR\audio
	rmDir $INSTDIR\controller
	rmDir $INSTDIR\input
	rmDir $INSTDIR\Mainmenu
	rmDir $INSTDIR\options 
	rmDir $INSTDIR\pause 
	rmDir $INSTDIR\savesImages
	rmDir $INSTDIR\skyboxes
	
	
	# Try to remove the install directory - this will only happen if it is empty
	rmDir $INSTDIR
 
	# Remove uninstaller information from the registry
	DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}"
sectionEnd