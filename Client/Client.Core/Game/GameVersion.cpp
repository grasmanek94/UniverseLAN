#include "Main.h"

bool GameVersion::bChecked = false;
GameVersionId GameVersion::storedGameVersion = VER_UNK;

std::list<GameVersionId> GameVersion::supportedVersions =
{
	VER_1_0_350_1_STEAM,

	VER_1_0_678_1_STEAM,
	VER_1_0_678_1_NOSTEAM,
	
	VER_1_0_757_4_STEAM,
	VER_1_0_757_4_NOSTEAM,

	VER_1_0_791_2_STEAM,
	VER_1_0_791_2_NOSTEAM,
};

GameVersionId GameVersion::Get()
{
	if(bChecked)
	{
		return storedGameVersion;
	}

	uintptr_t pGameBase = (uintptr_t)GetModuleHandle(nullptr);
	GameVersionId gameVersion = VER_UNK;

	DWORD v0 = *(DWORD *)(pGameBase + 0x870000);

	if(v0 <= 0x57085889)
	{
		if(v0 == 0x57085889) { return VER_1_0_505_2_STEAM; }
		if(v0 > 0x158B4800)
		{
			if(v0 == 0x158B48FF) { return VER_1_0_757_4_STEAM; }
			if(v0 == 0x28C48348) { return VER_1_0_505_2_NOSTEAM; }
			if(v0 == 0x36CB0305) { return VER_1_0_678_1_STEAM; }
			if(v0 == 0x48FFF41E) { return VER_1_0_617_1_NOSTEAM; }
			if(v0 == 0x4DE2E800) { return VER_1_0_573_1_STEAM; }
		}
		else
		{
			if(v0 == 0x158B4800) { return VER_1_0_791_2_NOSTEAM; }
			if(v0 > 0x137978C)
			{
				if(v0 == 0xF000001) { return VER_1_0_463_1_STEAM; }
				if(v0 == 0x100FF360) { return VER_1_0_372_2_NOSTEAM; }
			}
			else
			{
				if(v0 == 0x137978C) { return VER_1_0_757_4_NOSTEAM; }
				if(v0 == 1) { return VER_1_0_350_2_NOSTEAM; }
				if(v0 == 0x1ECB9) { return VER_1_0_372_2_STEAM; }
				if(v0 == 0xA29410) { return VER_1_0_335_2_NOSTEAM; }
			}
		}

		return VER_UNK;
	}

	if(v0 > 0xB95A0589)
	{
		if(v0 == 0xC4834800) { return VER_1_0_393_4_NOSTEAM; }
		if(v0 == 0xC86E0F66) { return VER_1_0_463_1_NOSTEAM; }
		if(v0 == 0xE8012024) { return VER_1_0_335_2_STEAM; }
		if(v0 == 0xE80C75D2) { return VER_1_0_757_2_NOSTEAM; }
		if(v0 == 0xF4397715) { return VER_1_0_617_1_STEAM; }
		return VER_UNK;
	}

	if(v0 == 0xB95A0589) { return VER_1_0_678_1_NOSTEAM; }

	if(v0 > 0x8B48C88B)
	{
		if(v0 == 0x8B48FF79) { return VER_1_0_393_2_NOSTEAM; }
		if(v0 == 0xB86AE800) { return VER_1_0_791_2_STEAM; }
		return VER_UNK;
	}

	if(v0 == 0x8B48C88B) { return VER_1_0_757_2_STEAM; }
	if(v0 == 0x7D2205FF) { return VER_1_0_350_1_STEAM; }
	if(v0 == 0x8948C88B) { return VER_1_0_573_1_NOSTEAM; }

	if(v0 != 0x89605189)
	{
		return VER_UNK;
	}

	gameVersion = VER_1_0_393_4_STEAM;

	if(*(DWORD *)(pGameBase + 0x1433B08) == 0x245C8948)
	{
		gameVersion = VER_1_0_393_2_STEAM;
	}

	return gameVersion;
}

bool GameVersion::IsSupported(GameVersionId gameVersion)
{
	return (std::find(supportedVersions.begin(), supportedVersions.end(), gameVersion) != supportedVersions.end());
}

bool GameVersion::IsSupported()
{
	return (bChecked ? IsSupported(storedGameVersion) : false);
}

void GameVersion::Check()
{
	if(!bChecked)
	{
		storedGameVersion = Get();

		bChecked = true;
	}
}
