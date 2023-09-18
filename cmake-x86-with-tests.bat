rd /S /Q cmake-x86
mkdir cmake-x86
cmake -A Win32 -B cmake-x86 -D BUILD_TEST_CASES=1
pause