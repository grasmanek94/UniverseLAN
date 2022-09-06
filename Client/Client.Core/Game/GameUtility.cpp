#include <windows.h>
#include <Psapi.h>

#pragma comment(lib, "psapi.lib")

#include "GameUtility.h"

bool GameUtility::CompareMemory(const unsigned char *pData, const unsigned char *bMask, const char *sMask)
{
	for(; *sMask; ++sMask, ++pData, ++bMask)
		if(*sMask == 'x' && *pData != *bMask)
			return false;

	return *sMask == NULL;
}

intptr_t GameUtility::FindPattern(const char *bMask, const char *sMask)
{
	static intptr_t pGameBase = (intptr_t)GetModuleHandle(nullptr);
	static DWORD pGameSize = 0;

	if(!pGameSize)
	{
		MODULEINFO info;
		GetModuleInformation(GetCurrentProcess(), (HMODULE)pGameBase, &info, sizeof(MODULEINFO));
		pGameSize = info.SizeOfImage;
	}

	for(DWORD i = 0; i < pGameSize; i++)
	{
		if(CompareMemory((unsigned char *)(pGameBase + i), (unsigned char *)bMask, sMask))
			return pGameBase + i;
	}

	return 0;
}

bool GameUtility::IsIntroMovieStringAvailable()
{
	return (GameUtility::FindPattern("platform:/movies/rockstar_logos", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx") != 0);
}
