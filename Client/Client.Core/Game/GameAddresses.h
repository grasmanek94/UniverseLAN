#pragma once

class GameAddresses
{
public:
	static uint64_t ppPedFactory;
	static char *pGameKeyArray;
	static uint64_t scriptHandleToPed;
	static uint32_t pedIntelligenceOffset;
	static uint8_t *pMouseInputEnabled;
	static uint8_t *pKeyboardInputEnabled;
	static uint64_t getPedRootBonePosition;
	static uint64_t getPedBonePosition;

public:
	static bool FindAddresses();
};
