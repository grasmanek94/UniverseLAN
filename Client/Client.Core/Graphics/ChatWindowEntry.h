#pragma once

class ChatWindowEntry
{
private:
	ID3D11DeviceContext *m_pD3D11DeviceContext;
	IFW1FontWrapper *m_pFW1FontWrapper;

	std::vector <ChatWindowEntrySection> m_Sections;

public:
	ChatWindowEntry(ID3D11DeviceContext *pD3D11DeviceContext, IFW1FontWrapper *pFW1FontWrapper);
	~ChatWindowEntry();

	float GetWidth();

	void Format(std::wstring wstrText, unsigned long ulColor, bool bEnableColorEmbedding = true);
	void FormatWithNickname(std::wstring wstrNickname, std::wstring wstrMessage, unsigned long ulNicknameColor, unsigned long ulMessageColor, bool bEnableColorEmbedding = false);

	void Draw(float fX, float fY, bool bShadow = true);

private:
	void HandleColorEmbeddedText(std::wstring wstrColorEmbeddedText, unsigned long ulDefaultColor, bool bEnableColorEmbedding);
};
