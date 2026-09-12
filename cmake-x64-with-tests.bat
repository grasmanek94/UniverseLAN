rd /S /Q cmake-x64
mkdir cmake-x64
cmake -A x64 -B cmake-x64 -D BUILD_ALL_TESTS=1
pause
