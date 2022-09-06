#pragma once

class GamePatches
{
public:
	static bool InstallPatches();

public:
	static bool SkipIntro();

private:
	static bool RevealFullMap(bool bToggle);
	static bool UseMultiplayerUI();
	static bool DisableWeaponAndRadioWheelEffect();
};
