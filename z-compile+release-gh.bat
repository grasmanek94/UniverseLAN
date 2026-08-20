@echo off

REM We're in Github Actions most likely if this is not set
if "%BUILD_JOBS%"=="" (
  set BUILD_JOBS=4
  set EXTRA_CONFIG_PARAM=-DEXPERIMENTAL_FAST_BUILD=1
  echo Limiting to %BUILD_JOBS% parallel jobs and Unity/Amalgamation build
)

echo Using %BUILD_JOBS% build jobs

cd "%~dp0"
rd /S /Q bin
rd /S /Q cmake-x64
rd /S /Q cmake-x86
rd /S /Q release-packages

mkdir bin
mkdir cmake-x64
mkdir cmake-x86
mkdir release-packages

cmake -A x64 -B cmake-x64 %EXTRA_CONFIG_PARAM% -D LIMIT_VERSIONS="1.148.3,1.139.2"
cmake -A Win32 -B cmake-x86 %EXTRA_CONFIG_PARAM% -D LIMIT_VERSIONS="1.148.3,1.139.2"

cmake --build cmake-x64 --config Release -j %BUILD_JOBS%
cmake --build cmake-x86 --config Release -j %BUILD_JOBS%

powershell -File ".\package-release.ps1"
