rd /S /Q cmake-x64
mkdir cmake-x64
cmake -A x64 -B cmake-x64 -D BUILD_INTERCEPTOR=1
pause