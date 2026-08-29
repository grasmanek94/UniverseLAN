@ECHO OFF

cd /d "%~dp0"
cd ../Source/Version

set "_COUNT="

for /f "delims=" %%a in ('git rev-list HEAD --count 2^>nul') do set "_COUNT=%%a"

if not defined _COUNT (
    if defined UNIVERSELAN_FORCE_BUILD_NUMBER (
        set "_COUNT=%UNIVERSELAN_FORCE_BUILD_NUMBER%"
        echo WARNING: Unable to obtain build number from git, using UNIVERSELAN_FORCE_BUILD_NUMBER=%_COUNT%
    ) else (
        set "_COUNT=0"
        echo WARNING: Unable to obtain build number from git, using build number 0
    )
)

echo #define BUILD_VERSION %_COUNT% > auto_version_check.h

fc /b auto_version.h auto_version_check.h > nul
if errorlevel 1 (
    echo Updating version...
    copy /b Version.cxx +,, > nul
    echo touched version.cxx ...
    del auto_version.h
    move auto_version_check.h auto_version.h
    echo Updated version to %_COUNT%
    cd /d %~dp0
) else (
    del auto_version_check.h
    echo Version doesn't need updating
)

ver > nul
type nul > nul