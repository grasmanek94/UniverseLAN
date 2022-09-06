#include "Main.h"
#include <winsock2.h>

static const char * (*g_origGetText) (void *theText, uint32_t hash);

static std::mutex g_textMutex;
static std::unordered_map<uint32_t, std::string> g_textMap;

int __stdcall HookedConnect(SOCKET s, sockaddr *name, int namelen) { return SOCKET_ERROR; }
int __stdcall HookedRecv(SOCKET s, char *buf, int len, int flags) { return SOCKET_ERROR; }
int __stdcall HookedRecvFrom(SOCKET s, char *buf, int len, int flags, sockaddr *from, int *fromlen) { return SOCKET_ERROR; }
int __stdcall HookedSend(SOCKET s, char *buf, int len, int flags) { return SOCKET_ERROR; }
int __stdcall HookedSendTo(SOCKET s, char *buf, int len, int flags, sockaddr *to, int tolen) { return SOCKET_ERROR; }
hostent * __stdcall HookedGetHostByName(char *name) { return NULL; }
int __stdcall HookedGetHostName(char *name, int namelen) { return SOCKET_ERROR; }

static const char* GetText(void* theText, uint32_t hash)
{
	{
		std::unique_lock<std::mutex> lock(g_textMutex);

		auto it = g_textMap.find(hash);

		if (it != g_textMap.end())
		{
			return it->second.c_str();
		}
	}

	return g_origGetText(theText, hash);
}

void AddCustomText(const char *key, const char *value)
{
	std::unique_lock<std::mutex> lock(g_textMutex);
	g_textMap[SharedUtility::HashString(key)] = value;
}

uint64_t __fastcall GetPoolSize(uint64_t a1, uint32_t a2, int32_t a3)
{
	uint32_t v2 = a2;
	uint16_t v4 = *(uint16_t*)(a1 + 16);
	int32_t v5 = a3;
	uint32_t v6 = a2;
	uint64_t v7 = 0;

	if(v4)
	{
		v2 = (unsigned int)(v2 % v4);
		v7 = *(uint64_t*)(*(uint64_t*)(a1 + 8) + 8 * v2);

		if(v7)
		{
			bool skip_condition = false;

			while(*(DWORD*)v7 != v6)
			{
				v7 = *(uint64_t*)(v7 + 8);

				if(!v7)
				{
					skip_condition = true;
					break;
				}
			}

			if(!skip_condition)
			{
				if(*(uint32_t*)(v7 + 4) != -1)
					v5 = *(uint32_t*)(v7 + 4);
			}
		}
	}

	if(0 > v5)
	{
		v5 = 0;
	}

	if(v6 == 0x1182232C)
	{
		if(256 > v5)
		{
			v5 = 256;
		}

		LOG_PRINT("[V+ | Core] Pool 1 extended!");
		return v5;
	}

	if(v6 == 0x7311A8D7)
	{
		if(3072 > v5)
		{
			v5 = 3072;
		}

		LOG_PRINT("[V+ | Core] Pool 2 extended!");
		return v5;
	}

	if(v6 == 0xEF7129CB)
	{
		if(3072 > v5)
		{
			v5 = 3072;
		}

		LOG_PRINT("[V+ | Core] Pool 3 extended!");
		return v5;
	}

	if(v6 == 0x3EEA2DA9)
	{
		if(3072 > v5)
		{
			v5 = 3072;
		}

		LOG_PRINT("[V+ | Core] Pool 4 extended!");
		return v5;
	}

	if(v6 == 0x8DA12117)
	{
		if(512 > v5)
		{
			v5 = 512;
		}

		LOG_PRINT("[V+ | Core] Ped pool extended!");
		return v5;
	}

	if(v6 == 0x74B31BE3)
	{
		if(1024 > v5)
		{
			v5 = 1024;
		}

		LOG_PRINT("[V+ | Core] Vehicle pool extended!");
		return v5;
	}

	return v5;
}

bool GameHooks::InstallHooks()
{
	hook::iat("ws2_32.dll", HookedConnect, 4);
	hook::iat("ws2_32.dll", HookedRecv, 16);
	hook::iat("ws2_32.dll", HookedRecvFrom, 17);
	hook::iat("ws2_32.dll", HookedSend, 19);
	hook::iat("ws2_32.dll", HookedSendTo, 20);
	hook::iat("ws2_32.dll", HookedGetHostByName, 52);
	hook::iat("ws2_32.dll", HookedGetHostName, 57);

	g_textMap[0x748C6374] = "Loading V+";
	g_textMap[0xABB00DEB] = "V+";

	void* getTextPtr = hook::pattern("48 8B CB 8B D0 E8 ? ? ? ? 48 85 C0 0F 95 C0").count(1).get(0).get<void>(5);
	hook::set_call(&g_origGetText, getTextPtr);
	hook::call(getTextPtr, GetText);

	hook::call(hook::pattern("48 85 C0 75 34 8B 0D").count(1).get(0).get<void>(-5), GetText);

	void* getPoolSizeLocation = hook::pattern("40 53 48 83 EC 20 48 8B 1D ? ? ? ? BA 20 4F BC 76 41 B8 01 00 00 00 48 8B CB E8 ? ? ? ? 8B C8").count(1).get(0).get<void>(28);
	uint64_t getPoolSizeAddr = (uint64_t)getPoolSizeLocation + *(uint32_t*)getPoolSizeLocation + 4;

	*(uint16_t*)getPoolSizeAddr = 0xB848u;
	*(uint64_t*)(getPoolSizeAddr + 2) = (uint64_t)GetPoolSize;
	*(uint16_t*)(getPoolSizeAddr + 10) = 0xC350u;
	return true;
}
