#include "Main.h"

bool GamePatches::InstallPatches()
{
	if(!RevealFullMap(true)) { OutputDebugString(L"[V+ | Core] Failed to install reveal full map patch."); return false; }
	if(!UseMultiplayerUI()) { OutputDebugString(L"[V+ | Core] Failed to install use multiplayer UI patch."); return false; }
	if(!DisableWeaponAndRadioWheelEffect()) { OutputDebugString(L"[V+ | Core] Failed to install disable weapon and radio wheel effect patch."); return false; }
	return true;
}

bool GamePatches::SkipIntro()
{
	static auto rockstarLogos = GameUtility::FindPattern("platform:/movies/rockstar_logos", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");

	if(!rockstarLogos)
	{
		return false;
	}

	memset((void *)rockstarLogos, 0, 32);
	return true;
}

bool GamePatches::RevealFullMap(bool bToggle)
{
	static auto checkMultiplayerDrawMapFrame = GameUtility::FindPattern("\x40\x8A\x35\x00\x00\x00\x00\x84\xC0\x74\x05\x45\x84\xFF", "xxx????xxxxxxx");
	static unsigned char original[7] = { 0 };

	if(!checkMultiplayerDrawMapFrame)
	{
		return false;
	}

	static bool bInitialized = false;

	if(!bInitialized)
	{
		bInitialized = true;

		VirtualProtect((void*)checkMultiplayerDrawMapFrame, 7, PAGE_EXECUTE_READWRITE, nullptr);
		memcpy(&original, (void*)checkMultiplayerDrawMapFrame, 7);
	}

	if(bToggle)
	{
		memset((void*)checkMultiplayerDrawMapFrame, 0x90, 7); // NOP

		// always draw full map
		*(unsigned short *)checkMultiplayerDrawMapFrame = 0xB640; // mov sil, 
		*(unsigned char *)(checkMultiplayerDrawMapFrame + 2) = 1; // 1 (mov sil, 1)
	}
	else
	{
		memcpy((void*)checkMultiplayerDrawMapFrame, &original, 7);
	}

	return true;
}

bool GamePatches::UseMultiplayerUI()
{
	static auto location350 = GameUtility::FindPattern("\x40\x53\x48\x83\xEC\x30\x8B\x0D\x00\x00\x00\x00\x65\x48\x8B\x04\x25\x58\x00\x00\x00\xBA\xB4\x00\x00\x00\x48\x8B\x04\xC8\xF6\x04\x02\x01", "xxxxxxxx????xxxxxxxxxxxxxxxxxxxxx");
	static auto location678 = GameUtility::FindPattern("\x40\x53\x48\x83\xEC\x30\x8B\x0D\x00\x00\x00\x00\x65\x48\x8B\x04\x25\x58\x00\x00\x00\xBA\xB4\x00\x00\x00\x48\x8B\x04\xC8\xB3\x01", "xxxxxxxx????xxxxxxxxxxxxxxxxxxx");

	if(location350 != 0)
	{
		DWORD
			dwProtect1 = NULL,
			dwProtect2 = NULL;

		VirtualProtect((LPVOID)(location350 + 0x24), 7, PAGE_EXECUTE_READWRITE, &dwProtect1);

		if(*(uint8_t *)(location350 + 0x24) != 0x8A || *(uint8_t *)(location350 + 0x24 + 1) != 0x1D)
		{
			VirtualProtect((LPVOID)(location350 + 0x24), 7, dwProtect1, &dwProtect2);
			return false;
		}

		*(unsigned short *)(location350 + 0x24) = 0x01B3; // mov bl, 1
		VirtualProtect((LPVOID)(location350 + 0x24), 7, dwProtect1, &dwProtect2);

		VirtualProtect((LPVOID)(location350 + 0x26), 5, PAGE_EXECUTE_READWRITE, &dwProtect1);
		*(unsigned int *)(location350 + 0x26) = 0x90909090; // nop (4x)
		VirtualProtect((LPVOID)(location350 + 0x26), 5, dwProtect1, &dwProtect2);

		VirtualProtect((LPVOID)(location350 + 0x30), 3, PAGE_EXECUTE_READWRITE, &dwProtect1);
		*(unsigned short *)(location350 + 0x30) = 0x9090; // nop (2x)
		VirtualProtect((LPVOID)(location350 + 0x30), 3, dwProtect1, &dwProtect2);

		return true;
	}

	if(location678 != 0)
	{
		DWORD
			dwProtect1 = NULL,
			dwProtect2 = NULL;

		// always set multiplayer ui
		VirtualProtect((LPVOID)(location678 + 0x35), 2, PAGE_EXECUTE_READWRITE, &dwProtect1);
		*(unsigned char *)(location678 + 0x35) = 0xEB; // jmp instead of jnz
		VirtualProtect((LPVOID)(location678 + 0x35), 2, dwProtect1, &dwProtect2);

		// update it in every frame
		VirtualProtect((LPVOID)(location678 + 0x3F), 3, PAGE_EXECUTE_READWRITE, &dwProtect1);
		*(unsigned char *)(location678 + 0x3F) = 0x90;
		*(unsigned char *)(location678 + 0x40) = 0x90;
		VirtualProtect((LPVOID)(location678 + 0x3F), 3, dwProtect1, &dwProtect2);

		return true;
	}

	return false;
}

bool GamePatches::DisableWeaponAndRadioWheelEffect()
{
	static auto location = GameUtility::FindPattern("\x48\x89\x5C\x24\x08\x57\x48\x83\xEC\x20\x33\xC0\x8B\xFA\x48\x8B\xD9\x83\xFA\x01\x75\x00\x38\x05\x00\x00\x00\x00\x0F\x45\xF8", "xxxxxxxxxxxxxxxxxxxxx?xx????xxx");

	if(!location)
	{
		return false;
	}

	DWORD
		dwProtect1 = NULL,
		dwProtect2 = NULL;

	VirtualProtect((LPVOID)location, 6, PAGE_EXECUTE_READWRITE, &dwProtect1);
	*(unsigned short *)location = 0xC031; // xor eax, eax
	*(unsigned short *)(location + 2) = 0x01B0; // mov al, 1
	*(unsigned char *)(location + 4) = 0xC3; // ret
	VirtualProtect((LPVOID)location, 6, dwProtect1, &dwProtect2);
	return true;
}
