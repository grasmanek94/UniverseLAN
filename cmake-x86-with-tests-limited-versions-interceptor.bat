rd /S /Q cmake-x86
mkdir cmake-x86
cmake -A Win32 -B cmake-x86 -D BUILD_TEST_CASES=1 -D BUILD_INTERCEPTOR=1 -D LIMIT_VERSIONS="1.148.3,1.139.2"
pause