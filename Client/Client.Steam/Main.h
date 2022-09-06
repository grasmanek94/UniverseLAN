#pragma once

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

#include <udis86.h>

#define LOG_PRINT SharedUtility::TemporaryLogFunction
#define LOG_DEBUG SharedUtility::TemporaryLogFunction
#define LOG_WARNING SharedUtility::TemporaryLogFunction
#define LOG_ERROR SharedUtility::TemporaryLogFunction

#include "InterfaceMapperBase.h"
#include "InterfaceMapper.h"
#include "ClientEngineMapper.h"
#include "IClientEngine.h"
#include "SafeClientEngine.h"
#include "ISteamClient.h"
#include "SteamLoader.h"
#include "SteamComponentAPI.h"
#include "SteamComponent.h"
