if(git status --porcelain |Where {$_ -match '^\?\?'}){
    echo "Untracked files detected!"
    pause
    exit
} 
elseif(git status --porcelain |Where {$_ -notmatch '^\?\?'}) {
    echo "Uncommited changes detected!"
    pause
    exit
}
else {
    echo "Packaging releases..."
}

$subdirs = Get-ChildItem -Directory .\bin\
$build_number = $(git rev-list HEAD --count)
$package_folder = "Release"
$output_folder = "release-packages"
$prefix = "UniverseLAN"

echo "Build number: $build_number"

foreach ($version in $subdirs)
{
    if($version.Name -ne "Debug" -and $version.Name -ne "Release")
    {
        $version_release_dir = ".\bin\" + $version.Name + "\$package_folder"

        $exists_x86 = Test-Path -Path "$version_release_dir\UniverseLANServer.exe" -PathType Leaf
        $exists_x64 = Test-Path -Path "$version_release_dir\UniverseLANServer64.exe" -PathType Leaf

        $ext = ''
        if($exists_x86 -and $exists_x64) {
            $ext =  "x64_x86"
        } elseif($exists_x86) {
            $ext = "x86"
        } elseif($exists_x64) {
            $ext = "x64"
        }

        if($ext) {
            $resulting_filename =  "$prefix-$version-Build-$build_number-$ext.zip"

            if(-not(Test-Path ".\$output_folder"))
            {
                echo "Creating .\$output_folder"
                New-Item -Path ".\$output_folder" -ItemType Directory -Force > $null
                echo "Done"
            }

            echo "Archiving '$version_release_dir\' into '.\$output_folder\$resulting_filename'"
            Compress-Archive -Path "$version_release_dir\*" -DestinationPath ".\$output_folder\$resulting_filename"
            echo "Done"
        }
    }
}

pause
