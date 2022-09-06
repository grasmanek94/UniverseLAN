#pragma once

#define MAX_PLAYER_NAME				32 // temporary

#define MAX_MESSAGE_LENGTH			384
#define MAX_LINE_LENGTH				MAX_MESSAGE_LENGTH / 2
#define MAX_MESSAGES				100

#define CHAT_COLOR_TEXT				0xffffffff
#define CHAT_COLOR_INFO				0xffffffff
#define CHAT_COLOR_DEBUG			0xffffffff

enum eChatMessageType
{
	CHAT_TYPE_NONE = 0,
	CHAT_TYPE_CHAT,
	CHAT_TYPE_INFO,
	CHAT_TYPE_DEBUG
};

class ChatWindow
{
private:
	ID3D11DeviceContext *m_pD3D11DeviceContext;
	IFW1FontWrapper *m_pFW1FontWrapper;

	bool m_bEnabled;
	int m_iPageSize;
	int m_iCurrentPage;
	std::list <ChatWindowEntry> m_ChatWindowEntries;
	int m_lCmdWindowY;

	void AddDefaultEntry(std::wstring wstrText, unsigned long ulTextColor);
	void AddChatMessageEntry(std::wstring wstrNickname, std::wstring wstrMessage, unsigned long ulNickColor, unsigned long ulMessageColor);

public:
	ChatWindow(ID3D11DeviceContext *pD3D11DeviceContext, IFW1FontWrapper *pFW1FontWrapper);
	~ChatWindow();

	void Draw();

	void AddChatMessageA(char *pszNickname, unsigned long ulNickColor, char *pszMessage);
	void AddChatMessageW(wchar_t *pwszNickname, unsigned long ulNickColor, wchar_t *pwszMessage);

	void AddInfoMessageA(char *pszFormat, ...);
	void AddInfoMessageW(wchar_t *pwszFormat, ...);

	void AddDebugMessageA(char *pszFormat, ...);
	void AddDebugMessageW(wchar_t *pwszFormat, ...);

	void AddClientMessageA(unsigned long ulColor, char *pszMessage);
	void AddClientMessageW(unsigned long ulColor, wchar_t *pwszMessage);

	bool IsEnabled() { return m_bEnabled; }
	void SetEnabled(bool bEnabled) { m_bEnabled = bEnabled; }

	void PageUp();
	void PageDown();

	void Toggle() { m_bEnabled ^= 1; };
	void Clear();

	int GetPageSize() { return m_iPageSize; };
	void SetPageSize(int iPageSize) { m_iPageSize = iPageSize; }

	int GetCmdWindowY() { return m_lCmdWindowY; };
};
