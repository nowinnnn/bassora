; Instalator BASSORA (Inno Setup 6).
; Budowanie:  ISCC.exe /DAppVersion=0.4.0 installer\BASSORA.iss     (po zbudowaniu projektu w konfiguracji Release)
; GitHub Actions robi to automatycznie - patrz .github/workflows/release.yml

#ifndef AppVersion
  #define AppVersion "0.4.0"
#endif
#ifndef BuildDir
  #define BuildDir "..\build\BASSORA_artefacts\Release"
#endif

#define Vst3Path BuildDir + "\VST3\BASSORA.vst3"

[Setup]
AppId={{8F2C1E6A-5B7D-4F43-9E0B-BA5500A00001}
AppName=BASSORA
AppVersion={#AppVersion}
AppVerName=BASSORA {#AppVersion}
AppPublisher=BASSORA Audio
DefaultDirName={autopf}\BASSORA
DefaultGroupName=BASSORA
DisableProgramGroupPage=yes
OutputDir=..\dist
OutputBaseFilename=BASSORA-Setup-{#AppVersion}
SetupIconFile=bassora.ico
WizardImageFile=wizard.bmp
WizardSmallImageFile=wizard_small.bmp
WizardStyle=modern
Compression=lzma2/max
SolidCompression=yes
ArchitecturesAllowed=x64compatible
ArchitecturesInstallIn64BitMode=x64compatible
PrivilegesRequired=admin
UninstallDisplayName=BASSORA {#AppVersion}
UninstallDisplayIcon={app}\BASSORA.exe

[Types]
Name: "full";    Description: "Full installation (VST3 + Standalone)"
Name: "plugin";  Description: "VST3 plugin only"
Name: "custom";  Description: "Custom installation"; Flags: iscustom

[Components]
Name: "vst3";       Description: "BASSORA VST3 plugin";          Types: full plugin custom; Flags: fixed
Name: "standalone"; Description: "BASSORA Standalone application"; Types: full custom

[Files]
; VST3 - JUCE na Windows tworzy pakiet (folder) BASSORA.vst3; obsługujemy też wariant pojedynczego pliku
#if DirExists(Vst3Path)
Source: "{#Vst3Path}\*"; DestDir: "{commoncf64}\VST3\BASSORA.vst3"; Flags: ignoreversion recursesubdirs createallsubdirs; Components: vst3
#else
Source: "{#Vst3Path}"; DestDir: "{commoncf64}\VST3"; Flags: ignoreversion; Components: vst3
#endif
Source: "{#BuildDir}\Standalone\BASSORA.exe"; DestDir: "{app}"; Flags: ignoreversion; Components: standalone

[Icons]
Name: "{autoprograms}\BASSORA"; Filename: "{app}\BASSORA.exe"; Components: standalone

[Run]
Filename: "{app}\BASSORA.exe"; Description: "Launch BASSORA Standalone"; Flags: nowait postinstall skipifsilent; Components: standalone

[Messages]
FinishedLabel=BASSORA has been installed.%n%nThe VST3 plugin is in the shared VST3 folder - rescan plugins in your DAW to see it. Your own presets are stored per user in the AppData\Roaming\BASSORA\Presets folder and are kept when you uninstall.
