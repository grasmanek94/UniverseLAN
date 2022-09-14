@ECHO OFF
cd /d "%~dp0"
cd ../Common/Version
copy /b Version.cxx +,,
echo touched version.cxx ...
for /f "delims=" %%a in ('git rev-list HEAD --count') do set _COUNT=%%a
echo #define BUILD_VERSION %_COUNT% > auto_version.h
echo Updated version to %_COUNT%
cd /d %~dp0
REM exit 0
