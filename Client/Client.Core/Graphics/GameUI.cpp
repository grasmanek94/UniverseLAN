#include "Main.h"

GameUI::GameUI(ID3D11Device *pD3D11Device, ID3D11DeviceContext *pD3D11DeviceContext)
{
	m_bInitialized = false;

	m_bDrawDebugInfo = false;
	m_bTestWorldToScreen = false;

	m_pD3D11Device = pD3D11Device;
	m_pD3D11DeviceContext = pD3D11DeviceContext;

	m_pFW1Factory = NULL;
	m_pDefaultFontWrapper = NULL;

	m_Gwen.Clear();

	m_pChatWindow = NULL;
}

GameUI::~GameUI()
{
	Shutdown();
}

void GameUI::Initialize()
{
	FW1CreateFactory(FW1_VERSION, &m_pFW1Factory);
	m_pFW1Factory->CreateFontWrapper(m_pD3D11Device, L"Tahoma", &m_pDefaultFontWrapper);

	HWND windowHandle = FindWindow(L"grcWindow", NULL);

	m_Gwen.pRenderer = new Gwen::Renderer::DirectX11(m_pD3D11Device);
	m_Gwen.pSkin = new Gwen::Skin::TexturedBase(m_Gwen.pRenderer);
	m_Gwen.pSkin->Init("v-plus\\skin.png");

	RECT FrameBounds;
	GetClientRect(windowHandle, &FrameBounds);

	m_Gwen.pCanvas = new Gwen::Controls::Canvas(m_Gwen.pSkin);
	m_Gwen.pCanvas->SetSize(FrameBounds.right, FrameBounds.bottom);
	m_Gwen.pCanvas->SetDrawBackground(false);

	m_Gwen.pUnitTest = new UnitTest(m_Gwen.pCanvas);
	m_Gwen.pUnitTest->SetPos(10, 10);

	m_Gwen.pInput = new Gwen::Input::Windows;
	m_Gwen.pInput->Initialize(m_Gwen.pCanvas);

	m_Gwen.bInitialized = true;
	m_Gwen.bEnabled = false;

	m_pChatWindow = new ChatWindow(m_pD3D11DeviceContext, m_pDefaultFontWrapper);

	m_bInitialized = true;
}

void GameUI::Shutdown()
{
	if(m_pChatWindow != NULL)
	{
		delete m_pChatWindow;
		m_pChatWindow = NULL;
	}

	if(m_pDefaultFontWrapper != NULL)
	{
		m_pDefaultFontWrapper->Release();
		m_pDefaultFontWrapper = NULL;
	}

	if(m_pFW1Factory != NULL)
	{
		m_pFW1Factory->Release();
		m_pFW1Factory = NULL;
	}

	m_bInitialized = false;
}

void GameUI::Draw()
{
	if(m_Gwen.bInitialized && m_Gwen.bEnabled)
	{
		if(m_Gwen.pCanvas != NULL)
		{
			m_Gwen.pCanvas->RenderCanvas();
		}
	}

	if(m_bDrawDebugInfo)
	{
		DrawDebugInfo();
	}
	else
	{
		if(m_pChatWindow != NULL)
		{
			m_pChatWindow->Draw();
		}
	}

	if(m_bTestWorldToScreen)
	{
		TestWorldToScreen();
	}
}

bool GameUI::MsgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if(m_Gwen.bInitialized)
	{
		if(uMsg == WM_KEYUP && wParam == VK_F2)
		{
			m_Gwen.bEnabled ^= 1;

			if(GameAddresses::pMouseInputEnabled != NULL)
			{
				if(*(GameAddresses::pMouseInputEnabled) != !m_Gwen.bEnabled)
				{
					*(GameAddresses::pMouseInputEnabled) = !m_Gwen.bEnabled;
				}
			}

			if(GameAddresses::pKeyboardInputEnabled != NULL)
			{
				if(*(GameAddresses::pKeyboardInputEnabled) != !m_Gwen.bEnabled)
				{
					*(GameAddresses::pKeyboardInputEnabled) = !m_Gwen.bEnabled;
				}
			}
		}

		if(m_Gwen.bEnabled)
		{
			MSG msg;

			msg.hwnd = hwnd;
			msg.message = uMsg;
			msg.wParam = wParam;
			msg.lParam = lParam;

			if(m_Gwen.pInput->ProcessMessage(msg))
			{
				return false;
			}
		}
	}
	
	if(uMsg == WM_KEYUP)
	{
		switch(wParam)
		{
			case VK_F3:
			{
				ToggleDrawingDebugInfo();
				break;
			}

			case VK_F5:
			{
				ToggleTestWorldToScreen();
				break;
			}

			default:
			{
				break;
			}
		}
	}

	return true;
}

void GameUI::DrawDebugInfo()
{
	wchar_t wszGameStateString[128];
	swprintf_s(wszGameStateString, 128, L"Game state: %d", GameStateWatcher::GetGameState());

	m_pDefaultFontWrapper->DrawString(m_pD3D11DeviceContext, wszGameStateString, 18.0f, 22.0f, 20.0f, 0xff000000, FW1_RESTORESTATE);
	m_pDefaultFontWrapper->DrawString(m_pD3D11DeviceContext, wszGameStateString, 18.0f, 20.0f, 18.0f, 0xffffffff, FW1_RESTORESTATE);

	if(GameStateWatcher::GetGameState() == GameStatePlaying && GameAddresses::ppPedFactory != NULL)
	{
		uint64_t pPedFactory = *(uint64_t *)(GameAddresses::ppPedFactory);

		if(pPedFactory != NULL)
		{
			uint64_t pLocalPlayerPed = *(uint64_t *)(pPedFactory + 8);

			if(pLocalPlayerPed != NULL)
			{
				wchar_t wszPositionString[128];
				swprintf_s(wszPositionString, 128, L"Position: %.2f, %.2f, %.2f",
					*(float *)(pLocalPlayerPed + 0x90), *(float *)(pLocalPlayerPed + 0x94), *(float *)(pLocalPlayerPed + 0x98));

				m_pDefaultFontWrapper->DrawString(m_pD3D11DeviceContext, wszPositionString, 18.0f, 22.0f, 42.0f, 0xff000000, FW1_RESTORESTATE);
				m_pDefaultFontWrapper->DrawString(m_pD3D11DeviceContext, wszPositionString, 18.0f, 20.0f, 40.0f, 0xffffffff, FW1_RESTORESTATE);
			}
		}
	}

	drawTaskList(m_pD3D11DeviceContext, m_pDefaultFontWrapper);
}

void GameUI::TestWorldToScreen()
{
	if(GameStateWatcher::GetGameState() == GameStatePlaying && GameAddresses::ppPedFactory != NULL)
	{
		uint64_t pPedFactory = *(uint64_t *)(GameAddresses::ppPedFactory);

		if(pPedFactory != NULL)
		{
			uint64_t pLocalPlayerPed = *(uint64_t *)(pPedFactory + 8);

			if(pLocalPlayerPed != NULL)
			{
				struct
				{
					Vector3 world;
					Vector2 screen;
				} position;

				typedef void*(__fastcall* GetPedRootBonePositionFromMask_t)(uint64_t pPlayerPed, D3DXVECTOR4& vBonePos, WORD dwMask);
				GetPedRootBonePositionFromMask_t GetPedRootBonePositionFromMask = GetPedRootBonePositionFromMask_t(GameAddresses::getPedRootBonePosition);

				typedef void*(__fastcall* GetPedBonePositionFromMask_t)(uint64_t pPlayerPed, D3DXVECTOR4& vBonePos, WORD dwMask);
				GetPedBonePositionFromMask_t GetPedBonePositionFromMask = GetPedBonePositionFromMask_t(GameAddresses::getPedBonePosition);

				D3DXVECTOR4 head_position;
				GetPedRootBonePositionFromMask(pLocalPlayerPed, head_position, ROOTBONETAG_HEAD);

				//position.world = Vector3(*(float *)(pLocalPlayerPed + 0x90), *(float *)(pLocalPlayerPed + 0x94), *(float *)(pLocalPlayerPed + 0x98));

				position.world = Vector3(head_position.x, head_position.y, head_position.z + 0.375f);
				position.screen = Vector2(0.0f, 0.0f);

				GameOverlay::WorldToScreen(position.world, position.screen);

				if(m_pD3D11DeviceContext != NULL && m_pDefaultFontWrapper != NULL)
				{
					FW1_RECTF layoutRect = { 0.0f, 0.0f, 8192.0f, 8192.0f };
					FW1_RECTF rect = m_pDefaultFontWrapper->MeasureString(L"Player", L"Tahoma", 14.0f, &layoutRect, FW1_RESTORESTATE);

					float
						text_width = rect.Right - rect.Left,
						text_height = rect.Top - rect.Bottom;

					m_pDefaultFontWrapper->DrawString(m_pD3D11DeviceContext, L"Player", 12.0f, position.screen.x - (text_width / 2), position.screen.y - (text_height / 2), 0xffffffff, FW1_RESTORESTATE);
				}
			}
		}
	}
}
