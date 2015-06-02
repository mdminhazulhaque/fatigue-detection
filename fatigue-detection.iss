; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "somewhereinblog Deesktop Notifier"
#define MyAppVersion "1.0"
#define MyAppPublisher "MD Minhazul Haque"
#define MyAppURL "http://www.somewhereinblog.net/blog/mhs92"
#define MyAppExeName "somewhereinblog-desktop-notifier.exe"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{579D6004-CA51-47F8-BA0E-32E85A9565BC}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\{#MyAppName}
DefaultGroupName=somewhereinblog Deesktop Notifier
AllowNoIcons=yes
LicenseFile=C:\Users\mmhs\Desktop\win32\LICENSE.txt
OutputDir=C:\Users\mmhs\Desktop
OutputBaseFilename=sdn-installer
SetupIconFile=C:\Users\mmhs\Desktop\installer.ico
Compression=lzma
SolidCompression=yes

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked; OnlyBelowVersion: 0,6.1

[Files]
Source: "C:\Users\mmhs\Desktop\win32\somewhereinblog-desktop-notifier.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\mmhs\Desktop\win32\libgcc_s_dw2-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\mmhs\Desktop\win32\mingwm10.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\mmhs\Desktop\win32\QtCore4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\mmhs\Desktop\win32\QtGui4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\mmhs\Desktop\win32\QtNetwork4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\mmhs\Desktop\win32\QtXml4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\mmhs\Desktop\win32\LICENSE.txt"; DestDir: "{app}"; Flags: ignoreversion

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: quicklaunchicon

[Registry]
Root: HKCU; Subkey: "Software\mdminhazulhaque\somewhereinblog.net"; Flags: uninsdeletekey

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, "&", "&&")}}"; Flags: nowait postinstall skipifsilent
