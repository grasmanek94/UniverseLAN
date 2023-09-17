#pragma once

#ifdef _WIN32
#include <concurrent_queue.h>
#else
#include <tbb/concurrent_queue.h>

namespace Concurrency = tbb;
namespace concurrency = Concurrency;
#endif
