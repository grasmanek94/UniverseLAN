#pragma once

class ChatWindowEntrySection
{
private:
	ID3D11DeviceContext *m_pD3D11DeviceContext;
	IFW1FontWrapper *m_pFW1FontWrapper;

	std::wstring m_wstrText;
	unsigned long m_ulColor;
	float m_fCachedWidth;
	unsigned int m_uiCachedLength;

public:
	ChatWindowEntrySection(ID3D11DeviceContext *pD3D11DeviceContext, IFW1FontWrapper *pFW1FontWrapper, std::wstring wstrText, unsigned long ulColor);

	std::wstring GetText() { return m_wstrText; }
	void SetText(std::wstring wstrText) { m_wstrText = wstrText; }

	float GetWidth();

	unsigned long GetColor() { return m_ulColor; }
	void SetColor(unsigned long ulColor) { m_ulColor = ulColor; }

	void Draw(float fX, float fY, bool bShadow = true);
};
