@echo off
setlocal

REM Use conservative defaults when BUILD_JOBS is not provided.
if not defined BUILD_JOBS (
    set "BUILD_JOBS=4"
    set "EXTRA_CONFIG_PARAM=-DEXPERIMENTAL_FAST_BUILD=1"
    echo Limiting parallel jobs and enabling Unity/Amalgamation build
)

echo Using %BUILD_JOBS% build jobs

pushd "%~dp0" || exit /b 1

rd /S /Q "bin" 2>nul
rd /S /Q "cmake-x64" 2>nul
rd /S /Q "cmake-x86" 2>nul
rd /S /Q "release-packages" 2>nul

mkdir "bin" || exit /b 1
mkdir "cmake-x64" || exit /b 1
mkdir "cmake-x86" || exit /b 1
mkdir "release-packages" || exit /b 1

cmake -A x64 -B "cmake-x64" %EXTRA_CONFIG_PARAM%
if errorlevel 1 exit /b 1

cmake -A Win32 -B "cmake-x86" %EXTRA_CONFIG_PARAM%
if errorlevel 1 exit /b 1

cmake --build "cmake-x64" --config Release -j %BUILD_JOBS%
if errorlevel 1 exit /b 1

cmake --build "cmake-x86" --config Release -j %BUILD_JOBS%
if errorlevel 1 exit /b 1

powershell.exe -NoProfile -File ".\package-release.ps1"
if errorlevel 1 exit /b 1

popd
exit /b 0