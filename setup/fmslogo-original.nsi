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

; The file to write
OutFile "${FMSLOGO_OUTPUT_FILE}"


; Modern UI Options
!define MUI_HEADERIMAGE
!define MUI_HEADERIMAGE_BITMAP   "fmslogo-header-icon.bmp"
!define MUI_HEADERIMAGE_UNBITMAP "fmslogo-header-uninstall-icon.bmp"
!define MUI_ICON                 "..\src\fmslogo.ico"
!define MUI_UNICON               "${NSISDIR}\Contrib\Graphics\Icons\win-uninstall.ico"
!define MUI_CUSTOMFUNCTION_GUIINIT   PreInstallSteps
!define MUI_CUSTOMFUNCTION_UNGUIINIT un.PreInstallSteps

; Add a Vista manifest for UAC that requests admin rights, if available.
RequestExecutionLevel highest


; The default installation directory
InstallDir "$PROGRAMFILES\FMSLogo"

; Registry key to check for directory 
; (so if you install again, it will overwrite the old one automatically)
InstallDirRegKey HKLM "Software\FMSLogo" "Install_Dir"

!define /date COPYRIGHT_YEAR "%Y"
VIAddVersionKey "ProductName"     "FMSLogo"
VIAddVersionKey "ProductVersion"  "${FMSLOGO_VERSION}"
VIAddVersionKey "FileDescription" "FMSLogo installer"
VIAddVersionKey "LegalCopyright"  "Copyright (C) ${COPYRIGHT_YEAR} by David Costanzo"
VIAddVersionKey "CompanyName"     "David Costanzo"
VIAddVersionKey "FileVersion"     "${FMSLOGO_VERSION}"

VIProductVersion ${FMSLOGO_MAJOR_VERSION}.${FMSLOGO_MINOR_VERSION}.${FMSLOGO_MICRO_VERSION}.0

Var StartMenuFolder

;--------------------------------

; Pages

!insertmacro MUI_PAGE_LICENSE "..\src\License.txt"
!insertmacro MUI_PAGE_COMPONENTS
!insertmacro MUI_PAGE_DIRECTORY

!define MUI_STARTMENUPAGE_DEFAULTFOLDER      "FMSLogo"          ; default start menu folder
!define MUI_STARTMENUPAGE_REGISTRY_ROOT      SHELL_CONTEXT      ; where to store the custom start menu folder
!define MUI_STARTMENUPAGE_REGISTRY_KEY       "Software\FMSLogo"
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
!insertmacro MUI_LANGUAGE "English"  ; the default language
!insertmacro MUI_LANGUAGE "German"
!insertmacro MUI_LANGUAGE "Italian"
!insertmacro MUI_LANGUAGE "Spanish"
!insertmacro MUI_LANGUAGE "French"
!insertmacro MUI_LANGUAGE "Greek"
!insertmacro MUI_LANGUAGE "Portuguese"
!insertmacro MUI_LANGUAGE "Russian"
!insertmacro MUI_LANGUAGE "Croatian"
!insertmacro MUI_LANGUAGE "Polish"
!insertmacro MUI_LANGUAGE "SimpChinese"
!define MUI_LANGDLL_ALLLANGUAGES ; don't filter language to system code page

; The description of the main installation component
LangString FMSLogoDescription ${LANG_ENGLISH}     "Install the FMSLogo programming environment."
LangString FMSLogoDescription ${LANG_GERMAN}      "Install the FMSLogo programming environment." ; NOT_YET_LOCALIZED
LangString FMSLogoDescription ${LANG_SPANISH}     "Instale el entorno de programación FMSLogo."
LangString FMSLogoDescription ${LANG_ITALIAN}     "Installa l'ambiente di programmazione FMSLogo."
LangString FMSLogoDescription ${LANG_PORTUGUESE}  "Install the FMSLogo programming environment." ; NOT_YET_LOCALIZED
LangString FMSLogoDescription ${LANG_FRENCH}      "Install the FMSLogo programming environment." ; NOT_YET_LOCALIZED
LangString FMSLogoDescription ${LANG_GREEK}       "Install the FMSLogo programming environment." ; NOT_YET_LOCALIZED
LangString FMSLogoDescription ${LANG_RUSSIAN}     "Install the FMSLogo programming environment." ; NOT_YET_LOCALIZED
LangString FMSLogoDescription ${LANG_CROATIAN}    "Install the FMSLogo programming environment." ; NOT_YET_LOCALIZED
LangString FMSLogoDescription ${LANG_POLISH}      "Instalacja œrodowiska programistycznego FMSLogo."
LangString FMSLogoDescription ${LANG_SIMPCHINESE} "°²×°FMSLogo±à³Ì»·¾³." 

; The label for the "desktop shortcut" checkbox.
LangString DesktopShortcut ${LANG_ENGLISH}     "Desktop Shortcut"
LangString DesktopShortcut ${LANG_GERMAN}      "Desktop Shortcut" ; NOT_YET_LOCALIZED
LangString DesktopShortcut ${LANG_SPANISH}     "Acceso directo del escritorio"
LangString DesktopShortcut ${LANG_ITALIAN}     "Collegamento sul Desktop"
LangString DesktopShortcut ${LANG_PORTUGUESE}  "Atalho no Desktop"
LangString DesktopShortcut ${LANG_FRENCH}      "Raccourci Bureau" 
LangString DesktopShortcut ${LANG_GREEK}       "Óõíôüìåõóç ÅðéöÜíåéáò Åñãáóßáò"
LangString DesktopShortcut ${LANG_RUSSIAN}     "ßðëûê ðàáî÷åãî ñòîëà" 
LangString DesktopShortcut ${LANG_CROATIAN}    "Preèac na Radnu površinu"
LangString DesktopShortcut ${LANG_POLISH}      "Skrót na pulpicie"
LangString DesktopShortcut ${LANG_SIMPCHINESE} "×ÀÃæ¿ì½Ý·½Ê½"

; The description of the desktop shortcut to FMSLogo
LangString DesktopShortcutDescription ${LANG_ENGLISH}     "Put a shortcut to FMSLogo on the desktop."
LangString DesktopShortcutDescription ${LANG_GERMAN}      "Put a shortcut to FMSLogo on the desktop." ; NOT_YET_LOCALIZED
LangString DesktopShortcutDescription ${LANG_SPANISH}     "Ponga un acceso directo a FMSLogo sobre el escritorio."
LangString DesktopShortcutDescription ${LANG_ITALIAN}     "Aggiungi un collegamento a FMSLogo sul Desktop."
LangString DesktopShortcutDescription ${LANG_PORTUGUESE}  "Put a shortcut to FMSLogo on the desktop." ; NOT_YET_LOCALIZED
LangString DesktopShortcutDescription ${LANG_FRENCH}      "Put a shortcut to FMSLogo on the desktop." ; NOT_YET_LOCALIZED
LangString DesktopShortcutDescription ${LANG_GREEK}       "Put a shortcut to FMSLogo on the desktop." ; NOT_YET_LOCALIZED
LangString DesktopShortcutDescription ${LANG_RUSSIAN}     "Put a shortcut to FMSLogo on the desktop." ; NOT_YET_LOCALIZED
LangString DesktopShortcutDescription ${LANG_CROATIAN}    "Put a shortcut to FMSLogo on the desktop." ; NOT_YET_LOCALIZED
LangString DesktopShortcutDescription ${LANG_POLISH}      "Umieœæ skrót do FMSLogo na pulpicie."
LangString DesktopShortcutDescription ${LANG_SIMPCHINESE} "ÔÚ×ÀÃæ·ÅÖÃFMSLogo¿ì½Ý·½Ê½." 

; The label for the "screen saver" checkbox.
LangString ScreenSaver ${LANG_ENGLISH}     "Screen Saver"
LangString ScreenSaver ${LANG_GERMAN}      "Screen Saver" ; NOT_YET_LOCALIZED
LangString ScreenSaver ${LANG_SPANISH}     "Salvapantallas"
LangString ScreenSaver ${LANG_ITALIAN}     "Salvaschermo"
LangString ScreenSaver ${LANG_PORTUGUESE}  "Screen Saver" ; NOT_YET_LOCALIZED
LangString ScreenSaver ${LANG_FRENCH}      "Screen Saver" ; NOT_YET_LOCALIZED
LangString ScreenSaver ${LANG_GREEK}       "Screen Saver" ; NOT_YET_LOCALIZED
LangString ScreenSaver ${LANG_RUSSIAN}     "Screen Saver" ; NOT_YET_LOCALIZED
LangString ScreenSaver ${LANG_CROATIAN}    "Screen Saver" ; NOT_YET_LOCALIZED
LangString ScreenSaver ${LANG_POLISH}      "Wygaszacz ekranu"
LangString ScreenSaver ${LANG_SIMPCHINESE} "ÆÁ±£" 

; The description of the screensaver component.
LangString ScreenSaverDescription ${LANG_ENGLISH}     "Install a screensaver that can run FMSLogo programs.$\n$\nYou must be an administrator to do this."
LangString ScreenSaverDescription ${LANG_GERMAN}      "Install a screensaver that can run FMSLogo programs.$\n$\nYou must be an administrator to do this." ; NOT_YET_LOCALIZED
LangString ScreenSaverDescription ${LANG_SPANISH}     "Instale un salvapantallas que puede ejecutar programas de FMSLogo.$\n$\nDebe ser un administrador para hacerlo."
LangString ScreenSaverDescription ${LANG_ITALIAN}     "Installa un salvaschermo che può eseguire programmi FMSLogo.$\n$\nDevi avere diritti di amministratore per farlo."
LangString ScreenSaverDescription ${LANG_PORTUGUESE}  "Install a screensaver that can run FMSLogo programs.$\n$\nYou must be an administrator to do this." ; NOT_YET_LOCALIZED
LangString ScreenSaverDescription ${LANG_FRENCH}      "Install a screensaver that can run FMSLogo programs.$\n$\nYou must be an administrator to do this." ; NOT_YET_LOCALIZED
LangString ScreenSaverDescription ${LANG_GREEK}       "Install a screensaver that can run FMSLogo programs.$\n$\nYou must be an administrator to do this." ; NOT_YET_LOCALIZED
LangString ScreenSaverDescription ${LANG_RUSSIAN}     "Install a screensaver that can run FMSLogo programs.$\n$\nYou must be an administrator to do this." ; NOT_YET_LOCALIZED
LangString ScreenSaverDescription ${LANG_CROATIAN}    "Install a screensaver that can run FMSLogo programs.$\n$\nYou must be an administrator to do this." ; NOT_YET_LOCALIZED
LangString ScreenSaverDescription ${LANG_POLISH}      "Zainstaluj wygaszacz ekranu korzystaj¹cy z programów FMSLogo.$\n$\nAby tego dokonaæ musisz mieæ uprawnienia administratora."
LangString ScreenSaverDescription ${LANG_SIMPCHINESE} "Äú±ØÐëÓµÓÐAdministratorÈ¨ÏÞ$\n$\n²ÅÄÜ°²×°ÄÜÔËÐÐFMSLogo³ÌÐòµÄÆÁ±£."

; An error message to show when attempting to install FMSLogo when it is already running.
LangString AlreadyRunningCannotInstallMessage ${LANG_ENGLISH}     "Either the installer or FMSLogo is currently running.$\nThis installation cannot continue."
LangString AlreadyRunningCannotInstallMessage ${LANG_GERMAN}      "Either the installer or FMSLogo is currently running.$\nThis installation cannot continue." ; NOT_YET_LOCALIZED     
LangString AlreadyRunningCannotInstallMessage ${LANG_SPANISH}     "O el instalador o FMSLogo ya está ejecutandose.$\nEsta instalación no puede continuar."
LangString AlreadyRunningCannotInstallMessage ${LANG_ITALIAN}     "L'installatore o FMSLogo sono già in esecuzione.$\nL'installazione non può continuare."
LangString AlreadyRunningCannotInstallMessage ${LANG_PORTUGUESE}  "O instalador ou o FMSLogo está rodando.$\nEssa instalação não poderá prosseguir."
LangString AlreadyRunningCannotInstallMessage ${LANG_FRENCH}      "L'installateur ou bien FMSLogo est en cours d'exécution.$\nL'installation ne peut continuer." 
LangString AlreadyRunningCannotInstallMessage ${LANG_GREEK}       "Ï åãêáôáóôÜôçò Þ ç FMSLogo åêôåëåßôáé Þäç.$\nÁõôÞ ç åãêáôÜóôáóç äå ìðïñåß íá óõíå÷éóôåß."
LangString AlreadyRunningCannotInstallMessage ${LANG_RUSSIAN}     "Èëè èíñòàëëÿòîð èëè FMSLogo â íàñòîÿùåå âðåìÿ çàïóùåíû.$\nÓñòàíîâêà íå ìîæåò áûòü ïðîäîëæåíà." 
LangString AlreadyRunningCannotInstallMessage ${LANG_CROATIAN}    "Trenutno je pokrenut ili instalacijski program ili FMSLogo.$\nOva se instalacija ne može nastaviti."
LangString AlreadyRunningCannotInstallMessage ${LANG_POLISH}      "Instalator albo program FMSLogo jest uruchomiony.$\nInstalacja nie mo¿e byæ kontynuowana."
LangString AlreadyRunningCannotInstallMessage ${LANG_SIMPCHINESE} "±¾°²×°³ÌÐò»òÕßFMSLogoÕýÔÚÔËÐÐ.$\n°²×°³ÌÐò²»ÄÜ¼ÌÐø." 

; A notification message when installing FMSLogo when another version is already installed.
; This tells the user that the old installation will be uninstalled.
LangString MustUninstallBeforeInstallingMessage ${LANG_ENGLISH}     "The existing copy of FMSLogo must be uninstalled to continue.$\nDo you want to uninstall it?$\n$\n(Selecting $\"No$\" will abort the installation)"
LangString MustUninstallBeforeInstallingMessage ${LANG_GERMAN}      "The existing copy of FMSLogo must be uninstalled to continue.$\nDo you want to uninstall it?$\n$\n(Selecting No will abort the installation)" ; NOT_YET_LOCALIZED
LangString MustUninstallBeforeInstallingMessage ${LANG_SPANISH}     "La copia existente de FMSLogo debe ser desinstalado antes de continuar.$\n¿Quiere desinstalarlo?$\n$\n(Si selecciona No, se abortará la instalación)"
LangString MustUninstallBeforeInstallingMessage ${LANG_ITALIAN}     "La versione attualmente installata di FMSLogo deve essere disinstallata prima di procedere.$\nVuoi procedere con la disinstallazione?$\n$\n(Selezionando No verrà interrotta l'installazione)"
LangString MustUninstallBeforeInstallingMessage ${LANG_PORTUGUESE}  "Já existe uma cópia do FMSLogo e precisa ser desinstalada para prosseguir.$\nDeseja desinstalá-la?$\n$\n(Escolher Não cessará a instalação)"
LangString MustUninstallBeforeInstallingMessage ${LANG_FRENCH}      "La version existante de FMSLogo doit être désinstallée pour continuer.$\nVoulez-vous la désinstaller?$\n$\n(Choisir Non terminera l'installation)"
LangString MustUninstallBeforeInstallingMessage ${LANG_GREEK}       "Ôï õðÜñ÷ïí áíôßãñáöï ôçò FMSLogo ðñÝðåé íá áðåãêáôáóôáèåß ðñéí óõíå÷éóôåß áõôÞ ç åãêáôÜóôáóç.$\nÈÝëåôå íá ôï åãêáôáóôÞóåôå;$\n$\n(ÅðéëÝãïíôáò ¼÷é ç åãêáôÜóôáóç èá êëåßóåé.)"
LangString MustUninstallBeforeInstallingMessage ${LANG_RUSSIAN}     "Ñóùåñòâóþùàÿ êîïèÿ FMSLogo äîëæíà áûòü óäàëåíà, ÷òîáû ïðîäîëæèòü.$\nÂû õîòèòå óäàëèòü åå?$\n$\n(Âûáîð Íåò ïðåðâåò óñòàíîâêó)"
LangString MustUninstallBeforeInstallingMessage ${LANG_CROATIAN}    "Postojeæa se verzija programa FMSLogo mora deinstalirati ako želiš nastaviti.$\nŽeliš li je deinstalirati?$\n$\n(Ako odabereš $\"Ne$\", instalacija æe se prekinuti)"
LangString MustUninstallBeforeInstallingMessage ${LANG_POLISH}      "Najpierw nale¿y usun¹æ zainstalowan¹ kopiê programu FSMLogo.$\nCzy usun¹æ?$\n$\n(Wybór $\"Nie$\", przerwie instalacjê)"
LangString MustUninstallBeforeInstallingMessage ${LANG_SIMPCHINESE} "ÒÑÓÐFMSLogo±ØÐëÏÈÉ¾³ý.$\nÄúÈ·¶¨ÒªÉ¾³ýÂð?$\n$\n(Ñ¡ÔñNoÖÕÖ¹°²×°)"

; An error message to show when attempting to *uninstall* FMSLogo when it is running.
LangString AlreadyRunningCannotUninstallMessage ${LANG_ENGLISH}     "Either the installer or FMSLogo is currently running.$\nThis uninstallation cannot continue."
LangString AlreadyRunningCannotUninstallMessage ${LANG_GERMAN}      "Either the installer or FMSLogo is currently running.$\nThis uninstallation cannot continue." ; NOT_YET_LOCALIZED
LangString AlreadyRunningCannotUninstallMessage ${LANG_SPANISH}     "O el instalador o FMSLogo ya está ejecutandose.$\nEsta desinstalación no puede continuar."
LangString AlreadyRunningCannotUninstallMessage ${LANG_ITALIAN}     "L'installatore o FMSLogo sono già in esecuzione.$\nL'installazione non può continuare."
LangString AlreadyRunningCannotUninstallMessage ${LANG_PORTUGUESE}  "O instalador ou o FMSLogo está rodando.$\n$\nEssa desinstalação não poderá prosseguir." ; NOT_YET_LOCALIZED
LangString AlreadyRunningCannotUninstallMessage ${LANG_FRENCH}      "L'installateur ou bien FMSLogo est encours d'exécution.$\nLa désinstallation ne peut continuer."
LangString AlreadyRunningCannotUninstallMessage ${LANG_GREEK}       "Ï åãêáôáóôÜôçò Þ ç FMSLogo åêôåëåßôáé Þäç.$\nÁõôÞ ç áðåãêáôÜóôáóç äå ìðïñåß íá óõíå÷éóôåß."
LangString AlreadyRunningCannotUninstallMessage ${LANG_RUSSIAN}     "Èëè èíñòàëëÿòîð èëè FMSLogo â íàñòîÿùåå âðåìÿ çàïóùåíû.$\níÓäàëåíèå íå ìîæåò áûòü ïðîäîëæåíî."
LangString AlreadyRunningCannotUninstallMessage ${LANG_CROATIAN}    "Trenutno je pokrenut ili instalacijski program ili FMSLogo.$\nOva se deinstalacija ne može nastaviti."
LangString AlreadyRunningCannotUninstallMessage ${LANG_POLISH}      "Instalator albo program FSMLogo jest ju¿ uruchomiony.$\nDeinstalacja nie mo¿e byæ kontynuowana."
LangString AlreadyRunningCannotUninstallMessage ${LANG_SIMPCHINESE} "±¾°²×°³ÌÐò»òÕßFMSLogoÕýÔÚÔËÐÐ.$\nÐ¶ÔØ³ÌÐò²»ÄÜ¼ÌÐø."

; An error message to show when the uninstaller cannot find the installation.
LangString CannotFindInstallationMessage ${LANG_ENGLISH}     "Either FMSLogo has already been deleted or you do not have permission to uninstall it.$\nEither way, this uninstallation cannot continue."
LangString CannotFindInstallationMessage ${LANG_GERMAN}      "Either FMSLogo has already been deleted or you do not have permission to uninstall it.$\nEither way, this uninstallation cannot continue." ; NOT_YET_LOCALIZED
LangString CannotFindInstallationMessage ${LANG_SPANISH}     "O FMSLogo ya ha sido borrado o no tiene permiso para desinstalarlo.$\nDe cualquier manera, esta desinstalación no puede continuar."
LangString CannotFindInstallationMessage ${LANG_ITALIAN}     "FMSLogo è stato già disinstallato oppure non hai i permessi per disinstallarlo.$\nIn entrambi i casi la disinstallazione non può continuare."
LangString CannotFindInstallationMessage ${LANG_PORTUGUESE}  "Ou o FMSLogo já foi deletado ou você não possui permissão para desinstalá-lo.$\nEm ambos os casos, essa desinstalação não poderá continuar." 
LangString CannotFindInstallationMessage ${LANG_FRENCH}      "FMSLogo a déjà été supprimé ou vous n'avez pas la permission de le désinstaller.$\nLa désinstallation ne peut continuer." 
LangString CannotFindInstallationMessage ${LANG_GREEK}       "Either FMSLogo has already been deleted or you do not have permission to uninstall it.$\nEither way, this uninstallation cannot continue." ; NOT_YET_LOCALIZED
LangString CannotFindInstallationMessage ${LANG_RUSSIAN}     "Èëè FMSLogo áûë óæå óäàëåí, èëè Âû íå èìååòå ïðàâ óäàëÿòü åå.$\nÂ ëþáîì ñëó÷àå, óäàëåíèå íå ìîæåò áûòü ïðîäîëæåíî." 
LangString CannotFindInstallationMessage ${LANG_CROATIAN}    "Ili je FMSLogo veæ izbrisan ili nemaš dopuštenje da ga deinstaliraš.$\nU svakom sluèaju, ova se deinstalacija ne može nastaviti."
LangString CannotFindInstallationMessage ${LANG_POLISH}      "Program FSMLogo zosta³ ju¿ usuniêty albo nie masz wystarczaj¹cych uprawnieñ.$\nDeinstalacja nie mo¿e byæ kontynuowana."
LangString CannotFindInstallationMessage ${LANG_SIMPCHINESE} "FMSLogoÒÑÉ¾³ý»òÕßÄú²»¾ß±¸É¾³ýÈ¨ÏÞ.$\nÉ¾³ý²»ÄÜ¼ÌÐø." 


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
;    !insertmacro InstallLanguageFile ..\src\ startup .logoscript
;
; This packs ..\src\startup-1031.logoscript, ..\src\startup-1033.logoscript, etc.
; into the installer, and unpacks the correct file as startup.logoscript.
;
!macro InstallLanguageFile.PerLanguage language_id build_path filename_stem filename_extension
  StrCmp $LANGUAGE ${language_id} 0 +2
     File /oname=${filename_stem}${filename_extension} ${build_path}${filename_stem}-${language_id}${filename_extension}
!macroend

!macro InstallLanguageFile build_path filename_stem filename_extension
  !insertmacro InstallLanguageFile.PerLanguage ${LANG_ENGLISH}     ${build_path} ${filename_stem} ${filename_extension}
  !insertmacro InstallLanguageFile.PerLanguage ${LANG_GERMAN}      ${build_path} ${filename_stem} ${filename_extension}
  !insertmacro InstallLanguageFile.PerLanguage ${LANG_SPANISH}     ${build_path} ${filename_stem} ${filename_extension}
  !insertmacro InstallLanguageFile.PerLanguage ${LANG_ITALIAN}     ${build_path} ${filename_stem} ${filename_extension}
  !insertmacro InstallLanguageFile.PerLanguage ${LANG_PORTUGUESE}  ${build_path} ${filename_stem} ${filename_extension}
  !insertmacro InstallLanguageFile.PerLanguage ${LANG_FRENCH}      ${build_path} ${filename_stem} ${filename_extension}
  !insertmacro InstallLanguageFile.PerLanguage ${LANG_GREEK}       ${build_path} ${filename_stem} ${filename_extension}
  !insertmacro InstallLanguageFile.PerLanguage ${LANG_RUSSIAN}     ${build_path} ${filename_stem} ${filename_extension}
  !insertmacro InstallLanguageFile.PerLanguage ${LANG_CROATIAN}    ${build_path} ${filename_stem} ${filename_extension}
  !insertmacro InstallLanguageFile.PerLanguage ${LANG_POLISH}      ${build_path} ${filename_stem} ${filename_extension}
  !insertmacro InstallLanguageFile.PerLanguage ${LANG_SIMPCHINESE} ${build_path} ${filename_stem} ${filename_extension}
!macroend


; Because we are using solid compression, files that are required before
; the actual installation should be stored first in the data block.
; This makes the installer start faster as it eliminates the
; "unpacking data xx%" dialog box.
!insertmacro MUI_RESERVEFILE_LANGDLL
ReserveFile "${NSISDIR}\Plugins\UserInfo.dll"

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
  !insertmacro InstallLanguageFile ..\src\                 startup   .logoscript
  !insertmacro InstallLanguageFile ..\${FMSLOGO_EXE_PATH}\ fmslogo   .exe
  !insertmacro InstallLanguageFile ..\manual\              logohelp  .chm

  File "..\src\README.TXT"
  File "..\src\LICENSE.TXT"
  File "..\src\turtle.bmp"
  File /r "..\src\logolib"
  File /r "..\src\examples"

  ;
  ; Write the uninstall keys for Windows
  ;

  ; Write the installation path into the registry
  WriteRegStr SHELL_CONTEXT "Software\FMSLogo" "Install_Dir" "$INSTDIR"

  WriteRegStr   SHELL_CONTEXT "Software\Microsoft\Windows\CurrentVersion\Uninstall\FMSLogo" "DisplayName" "FMSLogo"
  WriteRegStr   SHELL_CONTEXT "Software\Microsoft\Windows\CurrentVersion\Uninstall\FMSLogo" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteRegDWORD SHELL_CONTEXT "Software\Microsoft\Windows\CurrentVersion\Uninstall\FMSLogo" "NoModify" 1
  WriteRegDWORD SHELL_CONTEXT "Software\Microsoft\Windows\CurrentVersion\Uninstall\FMSLogo" "NoRepair" 1

  WriteUninstaller "uninstall.exe"

  ;
  ; create a file association for .lgo
  ;
  WriteRegStr SHELL_CONTEXT "software\classes\.lgo"  ""             "Logo program"
  WriteRegStr SHELL_CONTEXT "software\classes\.lgo"  "Logo program" "Logo program"
  WriteRegStr SHELL_CONTEXT "software\classes\Logo program\shell"              ""  "open"
  WriteRegStr SHELL_CONTEXT "software\classes\Logo program\DefaultIcon"        "" '$INSTDIR\fmslogo.exe,0'
  WriteRegStr SHELL_CONTEXT "software\classes\Logo program\shell\open\command" "" '$INSTDIR\fmslogo.exe -L%1'

  ;
  ; Create Start Menu shortcuts (if requested)
  ;
  !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
    CreateDirectory "$SMPROGRAMS\$StartMenuFolder"
    CreateShortCut "$SMPROGRAMS\$StartMenuFolder\Uninstall.lnk"        "$INSTDIR\uninstall.exe"       "" "$INSTDIR\uninstall.exe" 0
    CreateShortCut "$SMPROGRAMS\$StartMenuFolder\FMSLogo.lnk"          "$INSTDIR\fmslogo.exe"         "" "$INSTDIR\fmslogo.exe" 0
    CreateShortCut "$SMPROGRAMS\$StartMenuFolder\Examples.lnk"         "$INSTDIR\examples"            "" "$INSTDIR\examples" 0
    CreateShortCut "$SMPROGRAMS\$StartMenuFolder\Examples (index).lnk" "$INSTDIR\examples\index.html" "" "$INSTDIR\examples\index.html" 0
  !insertmacro MUI_STARTMENU_WRITE_END

SectionEnd


Section $(DesktopShortcut) DesktopShortcutSectionId
  CreateShortCut "$DESKTOP\FMSLogo.lnk" "$INSTDIR\fmslogo.exe" "" "$INSTDIR\fmslogo.exe" 0 
SectionEnd


Section /o $(ScreenSaver) ScreenSaverSectionId

  SectionIn RO ; read-only (only enabled for admins)

  ; Install the screen saver to the system directory.
  SetOutPath $SYSDIR
  !insertmacro InstallLanguageFile ..\screensaver\ fmslogo .scr
SectionEnd


Function .onInit

  ; First, read the language from the command-line
  ${GetParameters} $R0
  ClearErrors
  ${GetOptions} $R0 /LCID= $LANGUAGE
  ${Switch} $LANGUAGE
    ${Case} ${LANG_ENGLISH}
    ${Case} ${LANG_GERMAN}
    ${Case} ${LANG_SPANISH}
    ${Case} ${LANG_ITALIAN}
    ${Case} ${LANG_PORTUGUESE}
    ${Case} ${LANG_FRENCH}
    ${Case} ${LANG_GREEK}
    ${Case} ${LANG_RUSSIAN}
    ${Case} ${LANG_CROATIAN}
    ${Case} ${LANG_POLISH}
    ${Case} ${LANG_SIMPCHINESE}
        goto SetupUser
  ${EndSwitch}

  ; Either no language was passed on the command-line or
  ; one whose LCID isn't supported was given.
  ; Launch the language picker (from modern UI), defaulting to English
  Push ${LANG_ENGLISH}
  Pop $LANGUAGE
  !insertmacro MUI_LANGDLL_DISPLAY

SetupUser:
  ; Assume non-privileged user until we know they are an administrator
  SetShellVarContext current
  StrLen $2 "$PROFILE\FMSLogo"
  StrCpy $INSTDIR "$PROFILE\FMSLogo" $2 0

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
      StrLen $2       "$PROGRAMFILES\FMSLogo"
      StrCpy $INSTDIR "$PROGRAMFILES\FMSLogo" $2 0

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
  System::Call 'kernel32::CreateMutexA(i 0, i 0, t "LogoForWindowsMutex") i .r1 ?e'
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
  ReadRegStr $0 SHELL_CONTEXT "Software\Microsoft\Windows\CurrentVersion\Uninstall\FMSLogo" "UninstallString"

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
  DeleteRegKey SHELL_CONTEXT "Software\Microsoft\Windows\CurrentVersion\Uninstall\FMSLogo"

  ; Remove files and uninstaller
  Delete $previousinstalldir\fmslogo.exe
  Delete $previousinstalldir\fmslogo-${LANG_ENGLISH}.exe
  Delete $previousinstalldir\fmslogo-${LANG_GERMAN}.exe
  Delete $previousinstalldir\fmslogo-${LANG_SPANISH}.exe
  Delete $previousinstalldir\fmslogo-${LANG_ITALIAN}.exe
  Delete $previousinstalldir\fmslogo-${LANG_PORTUGUESE}.exe
  Delete $previousinstalldir\fmslogo-${LANG_GREEK}.exe
  Delete $previousinstalldir\fmslogo-${LANG_FRENCH}.exe
  Delete $previousinstalldir\fmslogo-${LANG_RUSSIAN}.exe
  Delete $previousinstalldir\fmslogo-${LANG_CROATIAN}.exe
  Delete $previousinstalldir\fmslogo-${LANG_POLISH}.exe
  Delete $previousinstalldir\fmslogo-${LANG_SIMPCHINESE}.exe

  Delete $previousinstalldir\startup.logoscript
  Delete $previousinstalldir\startup-${LANG_ENGLISH}.logoscript
  Delete $previousinstalldir\startup-${LANG_GERMAN}.logoscript
  Delete $previousinstalldir\startup-${LANG_SPANISH}.logoscript
  Delete $previousinstalldir\startup-${LANG_ITALIAN}.logoscript
  Delete $previousinstalldir\startup-${LANG_PORTUGUESE}.logoscript
  Delete $previousinstalldir\startup-${LANG_GREEK}.logoscript
  Delete $previousinstalldir\startup-${LANG_FRENCH}.logoscript
  Delete $previousinstalldir\startup-${LANG_RUSSIAN}.logoscript
  Delete $previousinstalldir\startup-${LANG_CROATIAN}.logoscript
  Delete $previousinstalldir\startup-${LANG_POLISH}.logoscript
  Delete $previousinstalldir\startup-${LANG_SIMPCHINESE}.logoscript

  Delete $previousinstalldir\logohelp.chm
  Delete $previousinstalldir\logohelp-${LANG_ENGLISH}.chm
  Delete $previousinstalldir\logohelp-${LANG_GERMAN}.chm
  Delete $previousinstalldir\logohelp-${LANG_SPANISH}.chm
  Delete $previousinstalldir\logohelp-${LANG_ITALIAN}.chm
  Delete $previousinstalldir\logohelp-${LANG_PORTUGUESE}.chm
  Delete $previousinstalldir\logohelp-${LANG_GREEK}.chm
  Delete $previousinstalldir\logohelp-${LANG_FRENCH}.chm
  Delete $previousinstalldir\logohelp-${LANG_RUSSIAN}.chm
  Delete $previousinstalldir\logohelp-${LANG_CROATIAN}.chm
  Delete $previousinstalldir\logohelp-${LANG_POLISH}.chm
  Delete $previousinstalldir\logohelp-${LANG_SIMPCHINESE}.chm

  Delete $SYSDIR\fmslogo.scr
  Delete $previousinstalldir\fmslogo-${LANG_ENGLISH}.scr
  Delete $previousinstalldir\fmslogo-${LANG_GERMAN}.scr
  Delete $previousinstalldir\fmslogo-${LANG_SPANISH}.scr
  Delete $previousinstalldir\fmslogo-${LANG_ITALIAN}.scr
  Delete $previousinstalldir\fmslogo-${LANG_PORTUGUESE}.scr
  Delete $previousinstalldir\fmslogo-${LANG_GREEK}.scr
  Delete $previousinstalldir\fmslogo-${LANG_FRENCH}.scr
  Delete $previousinstalldir\fmslogo-${LANG_RUSSIAN}.scr
  Delete $previousinstalldir\fmslogo-${LANG_CROATIAN}.scr
  Delete $previousinstalldir\fmslogo-${LANG_POLISH}.scr
  Delete $previousinstalldir\fmslogo-${LANG_SIMPCHINESE}.scr

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
  Delete    "$DESKTOP\FMSLogo.lnk"

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

  System::Call 'kernel32::CreateMutexA(i 0, i 0, t "LogoForWindowsMutex") i .r1 ?e'
  Pop $R0
  StrCmp $R0 0 CheckIfInstallExists

  ; Notify the user that the uninstall cannot continue.
  MessageBox MB_OK|MB_ICONEXCLAMATION $(AlreadyRunningCannotUninstallMessage)
  Abort

CheckIfInstallExists:

  ReadRegStr $1 SHELL_CONTEXT "Software\Microsoft\Windows\CurrentVersion\Uninstall\FMSLogo" "UninstallString"
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
  Delete $INSTDIR\fmslogo.exe
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
  Delete    "$DESKTOP\FMSLogo.lnk"

  ; Remove directories used
  RMDir /r "$INSTDIR\logolib"
  RMDir /r "$INSTDIR\examples"
  RMDir "$INSTDIR"

  ; remove the file association
  DeleteRegValue SHELL_CONTEXT "software\classes\.lgo" "Logo program"
  DeleteRegKey   SHELL_CONTEXT "software\classes\Logo program"

  ; Remove registry keys
  DeleteRegKey SHELL_CONTEXT "Software\Microsoft\Windows\CurrentVersion\Uninstall\FMSLogo"
  DeleteRegKey SHELL_CONTEXT "Software\FMSLogo"

SectionEnd

!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
  !insertmacro MUI_DESCRIPTION_TEXT ${DesktopShortcutSectionId} $(DesktopShortcutDescription)
  !insertmacro MUI_DESCRIPTION_TEXT ${ScreenSaverSectionId}     $(ScreenSaverDescription)
  !insertmacro MUI_DESCRIPTION_TEXT ${FMSLogoSectionId}         $(FMSLogoDescription)
!insertmacro MUI_FUNCTION_DESCRIPTION_END
