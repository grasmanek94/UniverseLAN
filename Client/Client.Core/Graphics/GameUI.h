#pragma once

class GameUI
{
private:
	bool m_bInitialized;

	bool m_bDrawDebugInfo;
	bool m_bTestWorldToScreen;

	ID3D11Device *m_pD3D11Device;
	ID3D11DeviceContext *m_pD3D11DeviceContext;

	IFW1Factory *m_pFW1Factory;
	IFW1FontWrapper *m_pDefaultFontWrapper;

	struct
	{
		bool bInitialized;
		bool bEnabled;

		Gwen::Renderer::DirectX11 *pRenderer;
		Gwen::Skin::TexturedBase *pSkin;
		Gwen::Controls::Canvas *pCanvas;
		Gwen::Input::Windows *pInput;

		UnitTest *pUnitTest;

		void Clear()
		{
			bInitialized = false;
			bEnabled = false;

			pRenderer = NULL;
			pSkin = NULL;
			pCanvas = NULL;
			pInput = NULL;

			pUnitTest = NULL;
		}
	} m_Gwen;

	ChatWindow *m_pChatWindow;

public:
	GameUI(ID3D11Device *pD3D11Device, ID3D11DeviceContext *pD3D11DeviceContext);
	~GameUI();

	inline bool IsInitialized() { return m_bInitialized; }
	inline bool IsDrawingDebugInfoEnabled() { return m_bDrawDebugInfo; }

	inline ID3D11Device * GetD3D11Device() { return m_pD3D11Device; }
	inline ID3D11DeviceContext * GetD3D11DeviceContext() { return m_pD3D11DeviceContext; }

	inline IFW1Factory * GetFW1Factory() { return m_pFW1Factory; }
	inline IFW1FontWrapper * GetDefaultFontWrapper() { return m_pDefaultFontWrapper; }

	inline ChatWindow * GetChatWindow() { return m_pChatWindow; }

	void Initialize();
	void Shutdown();

	void Draw();
	bool MsgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	void ToggleDrawingDebugInfo() { m_bDrawDebugInfo ^= 1; }
	void DisableDrawingDebugInfo() { m_bDrawDebugInfo = false; }

	void ToggleTestWorldToScreen() { m_bTestWorldToScreen ^= 1; }
	void DisableWorldToScreenTest() { m_bTestWorldToScreen = false; }

	void DrawDebugInfo();
	void TestWorldToScreen();
};
