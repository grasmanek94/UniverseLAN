#pragma once

#ifdef _WIN32
#ifdef _MSC_VER
#include <concurrent_queue.h>
#else
#warning Using Unsupported and very simple Concurrent Queue implementation
#include "ConcurrentQueueUnsupported.hxx"
#endif
#else
#include <tbb/concurrent_queue.h>

namespace Concurrency = tbb;
#endif
