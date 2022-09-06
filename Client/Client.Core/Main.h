#pragma once

//#include <SDKDDKVer.h>

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

#include <Psapi.h>
#pragma comment(lib, "psapi.lib")

//http://stackoverflow.com/questions/16224273/warnings-using-vs2012-and-directx-june-2010
#pragma warning( push )
#pragma warning( disable : 4005 )
#include <d3d11.h>
#include <D3DX10Math.h>
#include "FW1FontWrapper.h"
#pragma warning( pop )

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <map>
#include <set>
#include <mutex>

#include "SharedUtility.h"

#include "Utility/Hooking/Hooking.h"
#include "Utility/RAGE/pgCollection.h"
#include "Utility/Utility.h"

#include "Gwen/Gwen.h"
#include "Gwen/Skins/Simple.h"
#include "Gwen/Skins/TexturedBase.h"
#include "Gwen/UnitTest/UnitTest.h"
#include "Gwen/Input/Windows.h"
#include "Gwen/Renderers/DirectX11.h"

#include "Game/Input/InputHook.h"

#include "Game/GameUtility.h"
#include "Game/GameStateWatcher.h"
#include "Game/GameAddresses.h"
#include "Game/GamePatches.h"
#include "Game/GameOverlay.h"
#include "Game/GameStartupManager.h"
#include "Game/GameVersion.h"
#include "Game/GameHooks.h"

#include "Game/Scripting/NativeTranslationTables.h"
#include "Game/Scripting/ScriptThread.h"
#include "Game/Scripting/ScriptEngine.h"
#include "Game/Scripting/NativeInvoker.h"

#include "Game/Scripting/TestThread.h"

#include "Graphics/ChatWindowEntrySection.h"
#include "Graphics/ChatWindowEntry.h"
#include "Graphics/ChatWindow.h"
#include "Graphics/GameUI.h"

#include "Game/PedBoneTags.h"
#include "Game/Tasks.h"

#define LOG_PRINT SharedUtility::TemporaryLogFunction
#define LOG_DEBUG SharedUtility::TemporaryLogFunction
#define LOG_WARNING SharedUtility::TemporaryLogFunction
#define LOG_ERROR SharedUtility::TemporaryLogFunction

#include "ClientCore.h"
