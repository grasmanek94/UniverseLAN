rd /S /Q cmake-x86
mkdir cmake-x86
cmake -A Win32 -B cmake-x86 -D LIMIT_VERSIONS="1.148.3,1.139.2"
pause