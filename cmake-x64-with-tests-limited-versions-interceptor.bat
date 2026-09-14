rd /S /Q cmake-x64
mkdir cmake-x64
cmake -A x64 -B cmake-x64 -D BUILD_ALL_TESTS=0 -D BUILD_INTERCEPTOR=1 -D LIMIT_VERSIONS="1.100.2"
pause
