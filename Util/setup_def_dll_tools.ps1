Invoke-WebRequest "https://github.com/grasmanek94/UniverseLAN/files/15138422/tools-binaries.zip" -OutFile "tools-binaries.zip"
Expand-Archive "tools-binaries.zip" -DestinationPath "."
Remove-Item "tools-binaries.zip"