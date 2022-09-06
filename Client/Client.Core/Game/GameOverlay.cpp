#include "Main.h"

bool GameOverlay::bInitialized = false;
GameUI * GameOverlay::pGameUI = NULL;

DXGISwapChainPresent GameOverlay::pRealPresent = NULL;
uintptr_t GameOverlay::hkSwapChainVFTable[64];

EngineWorldToScreen_t GameOverlay::EngineWorldToScreen = NULL;

HRESULT __stdcall GameOverlay::HookedPresent(IDXGISwapChain *pSwapChain, UINT SyncInterval, UINT Flags)
{
    if(!bInitialized)
    {
		ID3D11Device *pD3D11Device = NULL;
		ID3D11DeviceContext *pD3D11DeviceContext = NULL;

        pSwapChain->GetDevice(__uuidof(pD3D11Device), (void**)&pD3D11Device);
        pD3D11Device->GetImmediateContext(&pD3D11DeviceContext);

		if(pGameUI == NULL)
		{
			pGameUI = new GameUI(pD3D11Device, pD3D11DeviceContext);
			pGameUI->Initialize();
		}

        bInitialized = true;
    }

	if(pGameUI != NULL && pGameUI->IsInitialized())
	{
		pGameUI->Draw();
	}

    return pRealPresent(pSwapChain, SyncInterval, Flags);
}

bool GameOverlay::Setup()
{
	auto location = GameUtility::FindPattern("\x80\x7E\x10\x00\x48\x8B\x0D\x00\x00\x00\x00\x48\x8D\x94\x24\xA0\x00\x00\x00\x0F\x94\x05", "xxxxxxx????xxxxxxxxxxx");

	while(!location)
	{
		location = GameUtility::FindPattern("\x80\x7E\x10\x00\x48\x8B\x0D\x00\x00\x00\x00\x48\x8D\x94\x24\xA0\x00\x00\x00\x0F\x94\x05", "xxxxxxx????xxxxxxxxxxx");

		Sleep(50);
	}

	bool
		bHookedSwapChain = false,
		bFoundEngineWorldToScreen = false;

	if(location != 0)
	{
		uintptr_t ppDXGISwapChain = (uintptr_t)((location + 7) + *(unsigned int *)(location + 7) + 4);

		if(ppDXGISwapChain == NULL)
		{
			return false;
		}

		IDXGISwapChain *pSwapChain = *(IDXGISwapChain **)(ppDXGISwapChain);

		if(pSwapChain != NULL)
		{
			uintptr_t realSwapChainVFTable = *(uintptr_t *)(pSwapChain);
			DWORD dwProt1 = NULL, dwProt2 = NULL;

			VirtualProtect((LPVOID)(realSwapChainVFTable), 512, PAGE_EXECUTE_READWRITE, &dwProt1);
			memcpy(&hkSwapChainVFTable, (const void *)(realSwapChainVFTable), 512);
			VirtualProtect((LPVOID)(realSwapChainVFTable), 512, dwProt1, &dwProt2);

			pRealPresent = (DXGISwapChainPresent)hkSwapChainVFTable[8];
			hkSwapChainVFTable[8] = (uintptr_t)HookedPresent;

			VirtualProtect((LPVOID)(pSwapChain), 4, PAGE_EXECUTE_READWRITE, &dwProt1);
			*(uintptr_t *)(pSwapChain) = (uintptr_t)&hkSwapChainVFTable;
			VirtualProtect((LPVOID)(pSwapChain), 4, dwProt1, &dwProt2);
		}

		bHookedSwapChain = true;
	}

	location = GameUtility::FindPattern("\x48\x89\x5C\x24\x00\x55\x56\x57\x48\x83\xEC\x70\x65\x4C\x8B\x0C\x25", "xxxx?xxxxxxxxxxxx");

	while(!location)
	{
		location = GameUtility::FindPattern("\x48\x89\x5C\x24\x00\x55\x56\x57\x48\x83\xEC\x70\x65\x4C\x8B\x0C\x25", "xxxx?xxxxxxxxxxxx");

		Sleep(50);
	}

	if(location != 0)
	{
		EngineWorldToScreen = (EngineWorldToScreen_t)location;

		bFoundEngineWorldToScreen = true;
	}

	return (bHookedSwapChain && bFoundEngineWorldToScreen);
}

void GameOverlay::Shutdown()
{
	if(pGameUI != NULL)
	{
		delete pGameUI;
		pGameUI = NULL;
	}
}

bool GameOverlay::WorldToScreen(const Vector3 &worldPosition, Vector2 &screenPosition)
{
	if(!pGameUI || !pGameUI->GetD3D11Device() || !pGameUI->GetD3D11DeviceContext())
	{
		return false;
	}

	float
		fRelativeScreenPositionX = 0.0f,
		fRelativeScreenPositionY = 0.0f;

	if(!EngineWorldToScreen(worldPosition, &fRelativeScreenPositionX, &fRelativeScreenPositionY))
	{
		return false;
	}

	UINT numViewports = 1;
	D3D11_VIEWPORT vp;

	pGameUI->GetD3D11DeviceContext()->RSGetViewports(&numViewports, &vp);

	screenPosition.x = vp.Width * fRelativeScreenPositionX;
	screenPosition.y = vp.Height * fRelativeScreenPositionY;
	return true;
}
