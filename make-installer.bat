@echo off
rem Lokalne budowanie instalatora:  make-installer.bat [wersja]
rem Wymaga: CMake, Visual Studio 2022 (C++), Inno Setup 6 (https://jrsoftware.org/isdl.php)
setlocal
set VERSION=%1
if "%VERSION%"=="" set VERSION=0.4.0

cmake -B build -DBASSORA_COPY_AFTER_BUILD=OFF -DBASSORA_VERSION=%VERSION% || exit /b 1
cmake --build build --config Release --parallel || exit /b 1

set ISCC="%ProgramFiles(x86)%\Inno Setup 6\ISCC.exe"
if not exist %ISCC% goto noinno
%ISCC% /DAppVersion=%VERSION% installer\BASSORA.iss || exit /b 1
echo.
echo Gotowe: dist\BASSORA-Setup-%VERSION%.exe
exit /b 0

:noinno
echo Nie znaleziono Inno Setup 6. Zainstaluj z https://jrsoftware.org/isdl.php i uruchom ponownie.
exit /b 1
