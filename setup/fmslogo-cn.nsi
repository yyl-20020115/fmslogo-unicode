;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Filename    : fmslogo.nsi
; Description : The NSIS installer script that builds the FMSLogo's installer.
;
; Localization Instructions: 
; 
;   1) If there are no place-holders for your language, then open a feature
;   request on the FMSLogo project asking someone to add the place-holders.
;
;   2) Once the place-holders exist, Search the file for the NOT_YET_LOCALIZED
;   markers, which will be next to the strings that should be localized.
;   Localize the bit within the double-quotes that corresponds to your language.
;
;   After you translate the string, delete the NOT_YET_LOCALIZED marker.
; 
;   Note that the some characters with the strings must be escaped with a 
;   dollar-sign ($).
;
;     dollar-sign      -> $$ 
;     carriage-return  -> $\r 
;     newline          -> $\n
;     tab              -> $\t
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

!include MUI2.nsh
!include LogicLib.nsh
!include x64.nsh

; Compiler Flags
SetCompressor /SOLID lzma

; The name of the installer
Name "FMSLogo"
!define FMSLOGO_OUTPUT_FILE "FMSLogoUnicode-中文版安装程序.exe"

; The file to write
OutFile "${FMSLOGO_OUTPUT_FILE}"

!define FMSLOGO_EXE_PATH "Release\"

; Modern UI Options
!define MUI_HEADERIMAGE
!define MUI_HEADERIMAGE_BITMAP   "fmslogo-header-icon.bmp"
!define MUI_HEADERIMAGE_UNBITMAP "fmslogo-header-uninstall-icon.bmp"
!define MUI_ICON                 "..\fmslogo.ico"
!define MUI_UNICON               "${NSISDIR}\Contrib\Graphics\Icons\win-uninstall.ico"
!define MUI_CUSTOMFUNCTION_GUIINIT   PreInstallSteps
!define MUI_CUSTOMFUNCTION_UNGUIINIT un.PreInstallSteps

; Add a Vista manifest for UAC that requests admin rights, if available.
RequestExecutionLevel highest


; The default installation directory
InstallDir "$PROGRAMFILES\FMSLogoUnicode"

; Registry key to check for directory 
; (so if you install again, it will overwrite the old one automatically)
InstallDirRegKey HKLM "Software\FMSLogoUnicode" "Install_Dir"

!define /date COPYRIGHT_YEAR "%Y"
VIAddVersionKey "ProductName"     "FMSLogoUnicode"
VIAddVersionKey "ProductVersion"  "${FMSLOGO_VERSION}"
VIAddVersionKey "FileDescription" "FMSLogo installer"
VIAddVersionKey "LegalCopyright"  "Copyright (C) ${COPYRIGHT_YEAR} by David Costanzo"
VIAddVersionKey "CompanyName"     "David Costanzo"
VIAddVersionKey "FileVersion"     "${FMSLOGO_VERSION}"

;VIProductVersion ${FMSLOGO_MAJOR_VERSION}.${FMSLOGO_MINOR_VERSION}.${FMSLOGO_MICRO_VERSION}.0
VIProductVersion 7.3.0.0

Var StartMenuFolder

;--------------------------------

; Pages

!insertmacro MUI_PAGE_LICENSE "..\License.txt"
!insertmacro MUI_PAGE_COMPONENTS
!insertmacro MUI_PAGE_DIRECTORY

!define MUI_STARTMENUPAGE_DEFAULTFOLDER      "FMSLogoUnicode"          ; default start menu folder
!define MUI_STARTMENUPAGE_REGISTRY_ROOT      SHELL_CONTEXT      ; where to store the custom start menu folder
!define MUI_STARTMENUPAGE_REGISTRY_KEY       "Software\FMSLogoUnicode"
!define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "StartMenuFolder"
!insertmacro MUI_PAGE_STARTMENU Application $StartMenuFolder

!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH
  
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES
!insertmacro MUI_UNPAGE_FINISH

; variables
var previousinstalldir ; full path to the uninstaller

; Languages
;!insertmacro MUI_LANGUAGE "English"  ; the default language
!insertmacro MUI_LANGUAGE "SimpChinese"
!define MUI_LANGDLL_ALLLANGUAGES ; don't filter language to system code page

; The description of the main installation component
;LangString FMSLogoDescription ${LANG_ENGLISH}     "Install the FMSLogo programming environment."
LangString FMSLogoDescription ${LANG_SIMPCHINESE} "安装FMSLogo编程环境." 

; The label for the "desktop shortcut" checkbox.
;LangString DesktopShortcut ${LANG_ENGLISH}     "Desktop Shortcut"
LangString DesktopShortcut ${LANG_SIMPCHINESE} "桌面快捷方式"

; The description of the desktop shortcut to FMSLogo
;LangString DesktopShortcutDescription ${LANG_ENGLISH}     "Put a shortcut to FMSLogo on the desktop."
LangString DesktopShortcutDescription ${LANG_SIMPCHINESE} "在桌面放置FMSLogo快捷方式." 

; The label for the "screen saver" checkbox.
;LangString ScreenSaver ${LANG_ENGLISH}     "Screen Saver"
LangString ScreenSaver ${LANG_SIMPCHINESE} "屏保" 

; The description of the screensaver component.
;LangString ScreenSaverDescription ${LANG_ENGLISH}     "Install a screensaver that can run FMSLogo programs.$\n$\nYou must be an administrator to do this."
LangString ScreenSaverDescription ${LANG_SIMPCHINESE} "您必须拥有Administrator权限$\n$\n才能安装能运行FMSLogo程序的屏保."

; An error message to show when attempting to install FMSLogo when it is already running.
;LangString AlreadyRunningCannotInstallMessage ${LANG_ENGLISH}     "Either the installer or FMSLogo is currently running.$\nThis installation cannot continue."
LangString AlreadyRunningCannotInstallMessage ${LANG_SIMPCHINESE} "本安装程序或者FMSLogo正在运行.$\n安装程序不能继续." 

; A notification message when installing FMSLogo when another version is already installed.
; This tells the user that the old installation will be uninstalled.
;LangString MustUninstallBeforeInstallingMessage ${LANG_ENGLISH}     "The existing copy of FMSLogo must be uninstalled to continue.$\nDo you want to uninstall it?$\n$\n(Selecting $\"No$\" will abort the installation)"
LangString MustUninstallBeforeInstallingMessage ${LANG_SIMPCHINESE} "已有FMSLogo必须先删除.$\n您确定要删除吗?$\n$\n(选择No终止安装)"

; An error message to show when attempting to *uninstall* FMSLogo when it is running.
;LangString AlreadyRunningCannotUninstallMessage ${LANG_ENGLISH}     "Either the installer or FMSLogo is currently running.$\nThis uninstallation cannot continue."
LangString AlreadyRunningCannotUninstallMessage ${LANG_SIMPCHINESE} "本安装程序或者FMSLogo正在运行.$\n卸载程序不能继续."

; An error message to show when the uninstaller cannot find the installation.
;LangString CannotFindInstallationMessage ${LANG_ENGLISH}     "Either FMSLogo has already been deleted or you do not have permission to uninstall it.$\nEither way, this uninstallation cannot continue."
LangString CannotFindInstallationMessage ${LANG_SIMPCHINESE} "FMSLogo已删除或者您不具备删除权限.$\n删除不能继续." 


!include FileFunc.nsh
!insertmacro GetParameters
!insertmacro GetOptions

;
; InstallLanguageFile - build_path filename_stem filename_extension
;   Used to install a language-specific file to a well-known location.
;   The filename must be of the form:
;
;        <stem>-<LCID>.<extension>
;
;   and will be installed as:
;
;        <stem>.<extension>
;
;   All of the files with the LCID are packed into the installer, but
;   only the file that corresponds to the selected language is unpacked.
;
; Example Usage:
;  
;    !insertmacro InstallLanguageFile ..\ startup .logoscript
;
; This packs ..\startup-1031.logoscript, ..\startup-1033.logoscript, etc.
; into the installer, and unpacks the correct file as startup.logoscript.
;
!macro InstallLanguageFile.PerLanguage language_id build_path filename_stem filename_extension
  StrCmp $LANGUAGE ${language_id} 0 +2
     File /oname=${filename_stem}${filename_extension} ${build_path}${filename_stem}${filename_extension}
!macroend

!macro InstallLanguageFile build_path filename_stem filename_extension
;  !insertmacro InstallLanguageFile.PerLanguage ${LANG_ENGLISH}     ${build_path} ${filename_stem} ${filename_extension}
  !insertmacro InstallLanguageFile.PerLanguage ${LANG_SIMPCHINESE} ${build_path} ${filename_stem} ${filename_extension}
!macroend


; Because we are using solid compression, files that are required before
; the actual installation should be stored first in the data block.
; This makes the installer start faster as it eliminates the
; "unpacking data xx%" dialog box.
!insertmacro MUI_RESERVEFILE_LANGDLL
;ReserveFile "${NSISDIR}\Plugins\UserInfo.dll"

;--------------------------------

; The stuff to install
Section "FMSLogo" FMSLogoSectionId

  SectionIn RO ; read-only (always checked)

  ;
  ; Set output path to the installation directory.
  ;
  SetOutPath $INSTDIR

  ;
  ; Put files there
  ;
  !insertmacro InstallLanguageFile ..\                 startup   .logoscript
  !insertmacro InstallLanguageFile ..\${FMSLOGO_EXE_PATH}\ FMSLogoUnicode   .exe
  !insertmacro InstallLanguageFile ..\manual\              logohelp  .chm

  File "..\README.TXT"
  File "..\LICENSE.TXT"
  File "..\turtle.bmp"
  File /r "..\${FMSLOGO_EXE_PATH}\logolib"
  File /r "..\examples"

  ;
  ; Write the uninstall keys for Windows
  ;

  ; Write the installation path into the registry
  WriteRegStr SHELL_CONTEXT "Software\FMSLogoUnicode" "Install_Dir" "$INSTDIR"

  WriteRegStr   SHELL_CONTEXT "Software\Microsoft\Windows\CurrentVersion\Uninstall\FMSLogoUnicode" "DisplayName" "FMSLogoUnicode"
  WriteRegStr   SHELL_CONTEXT "Software\Microsoft\Windows\CurrentVersion\Uninstall\FMSLogoUnicode" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteRegDWORD SHELL_CONTEXT "Software\Microsoft\Windows\CurrentVersion\Uninstall\FMSLogoUnicode" "NoModify" 1
  WriteRegDWORD SHELL_CONTEXT "Software\Microsoft\Windows\CurrentVersion\Uninstall\FMSLogoUnicode" "NoRepair" 1

  WriteUninstaller "uninstall.exe"

  ;
  ; create a file association for .lgo
  ;
  WriteRegStr SHELL_CONTEXT "software\classes\.lgo"  ""             "Logo program"
  WriteRegStr SHELL_CONTEXT "software\classes\.lgo"  "Logo program" "Logo program"
  WriteRegStr SHELL_CONTEXT "software\classes\Logo program\shell"              ""  "open"
  WriteRegStr SHELL_CONTEXT "software\classes\Logo program\DefaultIcon"        "" '$INSTDIR\fmslogounicode.exe,0'
  WriteRegStr SHELL_CONTEXT "software\classes\Logo program\shell\open\command" "" '$INSTDIR\fmslogounicode.exe -L%1'

  ;
  ; Create Start Menu shortcuts (if requested)
  ;
  !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
    CreateDirectory "$SMPROGRAMS\$StartMenuFolder"
    CreateShortCut "$SMPROGRAMS\$StartMenuFolder\Uninstall.lnk"        "$INSTDIR\uninstall.exe"       "" "$INSTDIR\uninstall.exe" 0
    CreateShortCut "$SMPROGRAMS\$StartMenuFolder\FMSLogo Unicode.lnk"          "$INSTDIR\fmslogounicode.exe"         "" "$INSTDIR\fmslogounicode.exe" 0
    CreateShortCut "$SMPROGRAMS\$StartMenuFolder\Examples.lnk"         "$INSTDIR\examples"            "" "$INSTDIR\examples" 0
    CreateShortCut "$SMPROGRAMS\$StartMenuFolder\Examples (index).lnk" "$INSTDIR\examples\index.html" "" "$INSTDIR\examples\index.html" 0
  !insertmacro MUI_STARTMENU_WRITE_END

SectionEnd


Section $(DesktopShortcut) DesktopShortcutSectionId
  CreateShortCut "$DESKTOP\FMSLogo Unicode.lnk" "$INSTDIR\fmslogounicode.exe" "" "$INSTDIR\fmslogounicode.exe" 0 
SectionEnd


Section /o $(ScreenSaver) ScreenSaverSectionId

  SectionIn RO ; read-only (only enabled for admins)

  ; Install the screen saver to the system directory.
  SetOutPath $SYSDIR
  !insertmacro InstallLanguageFile ..\screensaver\ fmslogo .scr
SectionEnd


Function .onInit

  ; First, read the language from the command-line
  ;${GetParameters} $R0
  ;ClearErrors
  ;${GetOptions} $R0 /LCID= $LANGUAGE
  ;${Switch} $LANGUAGE
  ;  ${Case} ${LANG_ENGLISH}
  ;  ${Case} ${LANG_SIMPCHINESE}
  ;      goto SetupUser
  ;${EndSwitch}

  ; Either no language was passed on the command-line or
  ; one whose LCID isn't supported was given.
  ; Launch the language picker (from modern UI), defaulting to English
  ;Push ${LANG_ENGLISH}
  ;Pop $LANGUAGE
  ;!insertmacro MUI_LANGDLL_DISPLAY

SetupUser:
  ; Assume non-privileged user until we know they are an administrator
  SetShellVarContext current
  StrLen $2 "$PROFILE\FMSLogoUnicode"
  StrCpy $INSTDIR "$PROFILE\FMSLogoUnicode" $2 0

  ClearErrors
  UserInfo::GetName
  IfErrors SetupUser.Win9x
  Pop $0
  UserInfo::GetAccountType
  Pop $1

  ${Switch} $1
    ${Case} "Admin"
    ${Case} "Power"
SetupUser.Win9x:
      ; This user can install software as an administrator
      SetShellVarContext all
      StrLen $2       "$PROGRAMFILES\FMSLogoUnicode"
      StrCpy $INSTDIR "$PROGRAMFILES\FMSLogoUnicode" $2 0

      ; We can write to the system directory, so enable the screen saver
      SectionGetFlags ${ScreenSaverSectionId} $3
      IntOp $3 $3 & ~${SF_RO}      ; enable the screensaver component
      IntOp $3 $3 | ${SF_SELECTED} ; select it by default
      SectionSetFlags ${ScreenSaverSectionId} $3
  ${EndSwitch}

FunctionEnd

; Create a second initialization function that executes after the
; language has been chosen.  This is invoked after ${LANGUAGE} is
; fixed, so it can use the $() macros for reading strings from the
; language tables.  (If this were done in onInit, we'd have to use
; flow control on the $LANGUAGE variable to accomplish this.)
Function PreInstallSteps

  ;
  ; Abort if another instance of the installer is running
  ; 
  System::Call 'kernel32::CreateMutexA(i 0, i 0, t "LogoUnicodeForWindowsMutex") i .r1 ?e'
  Pop $R0 
  StrCmp $R0 0 checkifinstalled

  ; Silent installs should abort without a dialog box
  IfSilent Abort

  ; Notify the user that the install cannot continue.
  MessageBox MB_OK|MB_ICONEXCLAMATION $(AlreadyRunningCannotInstallMessage)
  Abort

checkifinstalled:

  ;
  ; If FMSLogo is already installed, either uninstall it or abort. 
  ;

  ; If this is a silent install, assume that the user wants it
  ; to succeed (uninstall the previous instance of logo).
  IfSilent uninstall

  ; Infer the path of any previous FMSLogo installation by looking for its uninstaller
  ReadRegStr $0 SHELL_CONTEXT "Software\Microsoft\Windows\CurrentVersion\Uninstall\FMSLogoUnicode" "UninstallString"

  ; If no uninstaller was found, then we're done
  StrCmp $0 "" end 0

  ; Extract the file path from the full path to the uninstaller.
  ; hack: assumes the string is quoted and ends in `\uninstall.exe"'.
  StrCpy $previousinstalldir $0 -15 1
  IfFileExists "$previousinstalldir\*.*" 0 end

  ; Notify the user that the install cannot continue until the existing FMSLogo is uninstalled
  MessageBox MB_YESNO $(MustUninstallBeforeInstallingMessage) IDYES uninstall IDNO abort

abort:
    Abort

uninstall:
  ;
  ; uninstall the old version of Logo.
  ; The code below must be able to remove all traces from any previous installed
  ; version.  Therefore it removes relics that no longer exist.
  ;
  
  ; Remove registry keys
  ; Note that we retain the registry key that has the preferences so that upgrading
  ; to a newer version doesn't cause any data loss.
  DeleteRegKey SHELL_CONTEXT "Software\Microsoft\Windows\CurrentVersion\Uninstall\FMSLogoUnicode"

  ; Remove files and uninstaller
  Delete $previousinstalldir\FMSLogoUnicode.exe
  ;Delete $previousinstalldir\fmslogo-${LANG_ENGLISH}.exe
  ;Delete $previousinstalldir\fmslogo-${LANG_SIMPCHINESE}.exe

  Delete $previousinstalldir\startup.logoscript
  ;Delete $previousinstalldir\startup-${LANG_ENGLISH}.logoscript
  ;Delete $previousinstalldir\startup-${LANG_SIMPCHINESE}.logoscript

  Delete $previousinstalldir\logohelp.chm
  ;Delete $previousinstalldir\logohelp-${LANG_ENGLISH}.chm
  ;Delete $previousinstalldir\logohelp-${LANG_SIMPCHINESE}.chm

  Delete $SYSDIR\fmslogo.scr
  ;Delete $previousinstalldir\fmslogo-${LANG_ENGLISH}.scr
  ;Delete $previousinstalldir\fmslogo-${LANG_SIMPCHINESE}.scr

  ; For FMSLogo 6.27.0, Windows applied a compatibility shim that disabled
  ; file system redirection, resulting in FMSLogo.scr, the screen saver
  ; binary, being written to the real system32 directory, instead of
  ; to syswow64, like most 32-bit programs.  In FMSLogo 6.28.0 or later,
  ; Windows no longer does this.  In order to be able to clean up for
  ; for 6.27.0, we must disable file system redirection, then re-delete
  ; the screensaver.
  ${If} ${RunningX64}
    ${DisableX64FSRedirection}
    Delete $SYSDIR\fmslogo.scr
    ${EnableX64FSRedirection}
  ${EndIf}

  Delete $previousinstalldir\logo.hlp
  Delete $previousinstalldir\logo.gid
  Delete $previousinstalldir\logo.fts

  Delete $previousinstalldir\mcistrwh.hlp
  Delete $previousinstalldir\mcistrwh.gid
  Delete $previousinstalldir\mcistrwh.fts

  Delete $previousinstalldir\README.TXT
  Delete $previousinstalldir\FMSLOGO.TXT
  Delete $previousinstalldir\license.txt
  Delete $previousinstalldir\turtle.bmp

  Delete $previousinstalldir\uninstall.exe

  ; Remove shortcuts, if any.
  ; Note that if no start menu is configured in the registry, as is the
  ; case with version prior to 7.0, then the default folder of FMSLogo
  ; will be used, which is where versions prior to 7.0 stored their
  ; start menu shortcuts.
  !insertmacro MUI_STARTMENU_GETFOLDER Application $StartMenuFolder
  RMDir  /r "$SMPROGRAMS\$StartMenuFolder"
  Delete    "$DESKTOP\FMSLogo Unicode.lnk"

  ; Remove directories used
  RMDir /r "$previousinstalldir\logolib"
  RMDir /r "$previousinstalldir\examples"
  RMDir "$previousinstalldir"

  ; remove the file association for .LGO
  DeleteRegValue SHELL_CONTEXT "software\classes\.lgo" "Logo program"
  DeleteRegKey   SHELL_CONTEXT "software\classes\Logo program"

end:

FunctionEnd



;--------------------------------
; Uninstaller

Function un.onInit

  ; Assume non-privileged user until we know they are an administrator
  SetShellVarContext current

  ClearErrors
  UserInfo::GetName
  IfErrors SetupUser.Win9x
  Pop $0
  UserInfo::GetAccountType
  Pop $1

  ${Switch} $1
    ${Case} "Admin"
    ${Case} "Power"
SetupUser.Win9x:
      ; This user is an administrator
      SetShellVarContext all
  ${EndSwitch}

FunctionEnd

Function un.PreInstallSteps

  System::Call 'kernel32::CreateMutexA(i 0, i 0, t "LogoUnicodeForWindowsMutex") i .r1 ?e'
  Pop $R0
  StrCmp $R0 0 CheckIfInstallExists

  ; Notify the user that the uninstall cannot continue.
  MessageBox MB_OK|MB_ICONEXCLAMATION $(AlreadyRunningCannotUninstallMessage)
  Abort

CheckIfInstallExists:

  ReadRegStr $1 SHELL_CONTEXT "Software\Microsoft\Windows\CurrentVersion\Uninstall\FMSLogoUnicode" "UninstallString"
  StrCpy $INSTDIR $1 -15 1 ; hack: assumes the string is quoted and ends in `\uninstall.exe"'.

  ; Confirm that FMSLogo exists where we think it does
  StrCmp $INSTDIR "" CheckIfInstallExists.ShowError 0
  IfFileExists "$INSTDIR\*.*" CheckIfInstallExists.Done CheckIfInstallExists.ShowError

CheckIfInstallExists.ShowError:
  ; Notify the user that FMSLogo does not exist where we think it does.
  MessageBox MB_OK|MB_ICONEXCLAMATION $(CannotFindInstallationMessage)
  Abort

CheckIfInstallExists.Done:

FunctionEnd


Section "Uninstall"
  ; Remove files and uninstaller
  Delete $INSTDIR\FMSLogoUnicode.exe
  Delete $INSTDIR\startup.logoscript
  Delete $INSTDIR\logohelp.chm
  Delete $SYSDIR\fmslogo.scr

  Delete $INSTDIR\README.TXT
  Delete $INSTDIR\LICENSE.TXT
  Delete $INSTDIR\turtle.bmp

  Delete $INSTDIR\uninstall.exe

  ; Remove shortcuts, if any
  !insertmacro MUI_STARTMENU_GETFOLDER Application $StartMenuFolder
  RMDir  /r "$SMPROGRAMS\$StartMenuFolder"
  Delete    "$DESKTOP\FMSLogo Unicode.lnk"

  ; Remove directories used
  RMDir /r "$INSTDIR\logolib"
  RMDir /r "$INSTDIR\examples"
  RMDir "$INSTDIR"

  ; remove the file association
  DeleteRegValue SHELL_CONTEXT "software\classes\.lgo" "Logo program"
  DeleteRegKey   SHELL_CONTEXT "software\classes\Logo program"

  ; Remove registry keys
  DeleteRegKey SHELL_CONTEXT "Software\Microsoft\Windows\CurrentVersion\Uninstall\FMSLogoUnicode"
  DeleteRegKey SHELL_CONTEXT "Software\FMSLogoUnicode"

SectionEnd

!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
  !insertmacro MUI_DESCRIPTION_TEXT ${DesktopShortcutSectionId} $(DesktopShortcutDescription)
  !insertmacro MUI_DESCRIPTION_TEXT ${ScreenSaverSectionId}     $(ScreenSaverDescription)
  !insertmacro MUI_DESCRIPTION_TEXT ${FMSLogoSectionId}         $(FMSLogoDescription)
!insertmacro MUI_FUNCTION_DESCRIPTION_END
