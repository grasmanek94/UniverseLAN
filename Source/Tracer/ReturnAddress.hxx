#pragma once

#if defined(_MSC_VER)

#include <intrin.h>

// defines _ReturnAddress()

#elif defined(__GNUC__) || defined(__clang__)

#define _ReturnAddress() \
    __builtin_extract_return_addr(__builtin_return_address(0))

#else

#define _ReturnAddress() nullptr

#endif
