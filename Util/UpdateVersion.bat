@ECHO OFF
cd /d "%~dp0"
cd ../Common/Version

for /f "delims=" %%a in ('git rev-list HEAD --count') do set _COUNT=%%a
echo #define BUILD_VERSION %_COUNT% > auto_version_check.h

fc /b auto_version.h auto_version_check.h > nul
if errorlevel 1 (
    echo Updating version...
    copy /b Version.cxx +,,
    echo touched version.cxx ...
    del auto_version.h
    move auto_version_check.h auto_version.h
    echo Updated version to %_COUNT%
    cd /d %~dp0
REM exit 0
) else (
    del auto_version_check.h
    echo Version doesn't need updating
)

ver > nul
type nul>nul
