#pragma once

class Vector2;
class Vector3;

class GameUI;

typedef HRESULT (__stdcall *DXGISwapChainPresent) (IDXGISwapChain *pSwapChain, UINT SyncInterval, UINT Flags); 
typedef bool (__fastcall *EngineWorldToScreen_t)(Vector3 worldPos, float *pRelativeScreenPositionX, float *pRelativeScreenPositionY);

class GameOverlay
{
private:
	static bool bInitialized;
	static GameUI *pGameUI;

	static DXGISwapChainPresent pRealPresent;
	static uintptr_t hkSwapChainVFTable[64];

	static EngineWorldToScreen_t EngineWorldToScreen;

	static HRESULT __stdcall HookedPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);

public:
	static bool IsInitialized() { return bInitialized; }
	static GameUI * GetGameUI() { return pGameUI; }

	static bool Setup();
	static void Shutdown();

	static bool WorldToScreen(const Vector3 &worldPosition, Vector2 &screenPosition);
};
