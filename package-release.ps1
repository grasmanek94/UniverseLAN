$ErrorActionPreference = 'Stop'

if ((Get-Command "7z.exe" -ErrorAction SilentlyContinue) -eq $null)
{
    throw "7z.exe not found!"
}

if (git status --porcelain | Where-Object { $_ -match '^\?\?' })
{
    throw "Untracked files detected!"
}

if (git status --porcelain | Where-Object { $_ -notmatch '^\?\?' })
{
    throw "Uncommitted changes detected!"
}

Write-Host "Packaging releases..."

if (-not (Test-Path ".\bin" -PathType Container))
{
    throw "Missing .\bin directory."
}

$versionFile = ".\Source\Version\auto_version.h"
$build_number = $null

if (Test-Path $versionFile)
{
    $firstLine = Get-Content $versionFile -TotalCount 1

    if ($firstLine -match '#define\s+BUILD_VERSION\s+(\d+)')
    {
        $build_number = $matches[1]
        Write-Host "Build number from auto_version.h: $build_number"
    }
}

if (-not $build_number)
{
    $build_number = git rev-list HEAD --count

    if (-not $build_number)
    {
        throw "Unable to determine build number."
    }

    Write-Host "Build number from git history: $build_number"
}

$subdirs = Get-ChildItem -Directory .\bin\
$package_folder = "Release"
$output_folder = "release-packages"
$prefix = "UniverseLAN"

$packageCount = 0

foreach ($version in $subdirs)
{
    if ($version.Name -in @("Debug", "Release"))
    {
        continue
    }

    $version_release_dir = ".\bin\$($version.Name)\$package_folder"

    if (-not (Test-Path $version_release_dir -PathType Container))
    {
        throw "Missing release directory: $version_release_dir"
    }

    $exists_x86 = Test-Path "$version_release_dir\UniverseLANServer.exe" -PathType Leaf
    $exists_x64 = Test-Path "$version_release_dir\UniverseLANServer64.exe" -PathType Leaf

    $ext = ''

    if ($exists_x86 -and $exists_x64)
    {
        $ext = "x64_x86"
    }
    elseif ($exists_x86)
    {
        $ext = "x86"
    }
    elseif ($exists_x64)
    {
        $ext = "x64"
    }

    if (-not $ext)
    {
        throw "No expected binaries found in $version_release_dir"
    }

    if (-not (Test-Path ".\$output_folder"))
    {
        Write-Host "Creating .\$output_folder"
        New-Item -Path ".\$output_folder" -ItemType Directory -Force | Out-Null
    }

    $resulting_filename = "$prefix-$($version.Name)-Build-$build_number-$ext.zip"
    $sourcePath = "$version_release_dir\*"
    $destinationPath = ".\$output_folder\$resulting_filename"

    Write-Host "Archiving '$version_release_dir\' into '$destinationPath'"

    & "7z.exe" a -tzip "$destinationPath" "$sourcePath" -mx=9 -y

    if ($LASTEXITCODE -ne 0)
    {
        throw "7-Zip failed with exit code $LASTEXITCODE."
    }

    if (-not (Test-Path $destinationPath -PathType Leaf))
    {
        throw "Archive was not created: $destinationPath"
    }

    $packageCount++
    Write-Host "Done"
}

if ($packageCount -eq 0)
{
    throw "No release packages were produced."
}

Write-Host "Successfully produced $packageCount package(s)."