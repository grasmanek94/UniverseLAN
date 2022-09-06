#include "Main.h"

ChatWindow::ChatWindow(ID3D11DeviceContext *pD3D11DeviceContext, IFW1FontWrapper *pFW1FontWrapper)
{
	m_bEnabled = true;

	m_iPageSize = 10;
	m_iCurrentPage = 1;

	m_pD3D11DeviceContext = pD3D11DeviceContext;
	m_pFW1FontWrapper = pFW1FontWrapper;

	Clear();
}

ChatWindow::~ChatWindow()
{
	Clear();
}

void ChatWindow::PageUp()
{
	if(!m_bEnabled)
		return;

    m_iCurrentPage++;

	if(m_iCurrentPage > MAX_MESSAGES / m_iPageSize)
		m_iCurrentPage = MAX_MESSAGES / m_iPageSize;
}

void ChatWindow::PageDown()
{
	if(!m_bEnabled)
		return;

    m_iCurrentPage--;

	if(m_iCurrentPage < 1)
		m_iCurrentPage = 1;
}

void ChatWindow::Draw()
{
	int x = 0;
	int iMessageAt;

	float pos[2] = { 20.0f, /*17.0f*/ 20.0f };

	iMessageAt = (m_iCurrentPage * m_iPageSize) - 1;

	if(m_bEnabled)
	{
		while(x != m_iPageSize)
		{
			if(static_cast<int>(m_ChatWindowEntries.size()) > iMessageAt)
			{
				std::list<ChatWindowEntry>::iterator it = m_ChatWindowEntries.begin();
				std::advance(it, iMessageAt);

				(*it).Draw(pos[0], pos[1], true);
			}

			pos[0] = 20.0f;
			pos[1] += 17.0f; // 18.0f;

			iMessageAt--;

			x++;
		}

		m_lCmdWindowY = (int)pos[1] + 10 + 1;
	}
}

void ChatWindow::AddChatMessageA(char *pszNickname, unsigned long ulNickColor, char *pszMessage)
{
	wchar_t
		wcNickname[MAX_PLAYER_NAME + 1],
		wcMessage[MAX_LINE_LENGTH + 1];

	size_t length;

	mbstowcs_s(&length, wcNickname, pszNickname, MAX_PLAYER_NAME);
	mbstowcs_s(&length, wcMessage, pszMessage, MAX_LINE_LENGTH);

	std::wstring
		wstrNick(wcNickname),
		wstrMessage(wcMessage);

	wstrNick.push_back(L':');
	wstrNick.push_back(L' ');

	AddChatMessageEntry(wstrNick, wstrMessage, ulNickColor, CHAT_COLOR_TEXT);
}

void ChatWindow::AddChatMessageW(wchar_t *pwszNickname, unsigned long ulNickColor, wchar_t *pwszMessage)
{
	std::wstring
		wstrNick(pwszNickname),
		wstrMessage(pwszMessage);

	wstrNick.push_back(L':');
	wstrNick.push_back(L' ');

	AddChatMessageEntry(wstrNick, wstrMessage, ulNickColor, CHAT_COLOR_TEXT);
}

void ChatWindow::AddInfoMessageA(char *pszFormat, ...)
{
	char tmp_buf[512];
	memset(tmp_buf, 0, 512);

	va_list args;
	va_start(args, pszFormat);
	vsprintf_s(tmp_buf, 512, pszFormat, args);
	va_end(args);

	wchar_t wcText[MAX_LINE_LENGTH + 1];
	size_t length;

	mbstowcs_s(&length, wcText, tmp_buf, MAX_LINE_LENGTH);

	AddDefaultEntry(std::wstring(wcText), CHAT_COLOR_INFO);
}

void ChatWindow::AddInfoMessageW(wchar_t *pwszFormat, ...)
{
	wchar_t tmp_buf[512];
	memset(tmp_buf, 0, 512 * sizeof(wchar_t));

	va_list args;
	va_start(args, pwszFormat);
	vswprintf_s(tmp_buf, 512, pwszFormat, args);
	va_end(args);

	AddDefaultEntry(std::wstring(tmp_buf), CHAT_COLOR_INFO);
}

void ChatWindow::AddDebugMessageA(char *pszFormat, ...)
{
	char tmp_buf[512];
	memset(tmp_buf, 0, 512);

	va_list args;
	va_start(args, pszFormat);
	vsprintf_s(tmp_buf, 512, pszFormat, args);
	va_end(args);

	wchar_t wcText[MAX_LINE_LENGTH + 1];
	size_t length;

	mbstowcs_s(&length, wcText, tmp_buf, MAX_LINE_LENGTH);

	AddDefaultEntry(std::wstring(wcText), CHAT_COLOR_DEBUG);

	OutputDebugStringA(tmp_buf);
}

void ChatWindow::AddDebugMessageW(wchar_t *pwszFormat, ...)
{
	wchar_t tmp_buf[512];
	memset(tmp_buf, 0, 512 * sizeof(wchar_t));

	va_list args;
	va_start(args, pwszFormat);
	vswprintf_s(tmp_buf, 512, pwszFormat, args);
	va_end(args);

	AddDefaultEntry(std::wstring(tmp_buf), CHAT_COLOR_DEBUG);
	OutputDebugStringW(tmp_buf);
}

void ChatWindow::AddClientMessageA(unsigned long ulColor, char *pszMessage)
{
	ulColor = (ulColor >> 8) | 0xFF000000; // convert to ARGB

	wchar_t wszMessage[MAX_LINE_LENGTH + 1];
	size_t length;

	mbstowcs_s(&length, wszMessage, pszMessage, MAX_MESSAGE_LENGTH);

	AddDefaultEntry(std::wstring(wszMessage), ulColor);
}

void ChatWindow::AddClientMessageW(unsigned long ulColor, wchar_t *pwszMessage)
{
	ulColor = (ulColor >> 8) | 0xFF000000; // convert to ARGB

	AddDefaultEntry(std::wstring(pwszMessage), ulColor);
}

void ChatWindow::AddDefaultEntry(std::wstring wstrText, unsigned long ulTextColor)
{
	ChatWindowEntry defaultEntry(m_pD3D11DeviceContext, m_pFW1FontWrapper);
	defaultEntry.Format(wstrText, ulTextColor, true);

	m_ChatWindowEntries.push_front(defaultEntry);

	if(m_ChatWindowEntries.size() > MAX_MESSAGES)
	{
		m_ChatWindowEntries.pop_back();
	}
}

void ChatWindow::AddChatMessageEntry(std::wstring wstrNick, std::wstring wstrMessage, unsigned long ulNickColor, unsigned long ulMessageColor)
{
	ChatWindowEntry chatMessageEntry(m_pD3D11DeviceContext, m_pFW1FontWrapper);
	chatMessageEntry.FormatWithNickname(wstrNick, wstrMessage, ulNickColor, ulMessageColor, false);

	m_ChatWindowEntries.push_front(chatMessageEntry);

	if(m_ChatWindowEntries.size() > MAX_MESSAGES)
	{
		m_ChatWindowEntries.pop_back();
	}
}

void ChatWindow::Clear()
{
	m_ChatWindowEntries.clear();
}
