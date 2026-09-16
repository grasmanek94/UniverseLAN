rd /S /Q cmake-x86
mkdir cmake-x86
cmake -A Win32 -B cmake-x86 -D BUILD_ALL_TESTS=0 -D BUILD_INTERCEPTOR=1 -D LIMIT_VERSIONS="1.100.2"
pause
