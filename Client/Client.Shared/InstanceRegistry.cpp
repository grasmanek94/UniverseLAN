/*
 * This file is part of the CitizenFX project - http://citizen.re/
 *
 * See LICENSE and MENTIONS in the root of the source tree for information
 * regarding licensing.
 */

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <wchar.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <process.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <map>
#include <set>
#include <mutex>
#include <sstream>
#include <thread>
#include <atomic>
#include <codecvt>
#include <locale>

#include "SharedUtility.h"
#include "Utility/Hooking/Hooking.h"

#include "fwRef.h"
#include "InstanceRegistry.h"

// global registry for use by client-only modules
CORE_EXPORT InstanceRegistry g_instanceRegistry;