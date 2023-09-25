rd /S /Q cmake-x64
mkdir cmake-x64
cmake -A x64 -B cmake-x64 -D BUILD_TEST_CASES=1 -D LIMIT_VERSIONS="1.144.1"
pause