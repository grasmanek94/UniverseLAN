cd "%~dp0"
rd /S /Q bin
rd /S /Q cmake-x64
rd /S /Q cmake-x86
rd /S /Q release-packages

mkdir bin
mkdir cmake-x64
mkdir cmake-x86
mkdir release-packages

cmake -A x64 -B cmake-x64
cmake -A Win32 -B cmake-x86

cmake --build cmake-x64 --config Release
cmake --build cmake-x86 --config Release

powershell -File ".\package-release.ps1"
