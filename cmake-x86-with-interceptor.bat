rd /S /Q cmake-x86
mkdir cmake-x86
cmake -A Win32 -B cmake-x86 -D BUILD_INTERCEPTOR=1
pause