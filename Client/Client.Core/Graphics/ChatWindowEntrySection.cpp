#include "Main.h"

ChatWindowEntrySection::ChatWindowEntrySection(ID3D11DeviceContext *pD3D11DeviceContext, IFW1FontWrapper *pFW1FontWrapper, std::wstring wstrText, unsigned long ulColor)
{
	m_pD3D11DeviceContext = pD3D11DeviceContext;
	m_pFW1FontWrapper = pFW1FontWrapper;

	SetText(wstrText);
	SetColor(ulColor);

	m_fCachedWidth = -1.0f;
	m_uiCachedLength = 0;
}

float ChatWindowEntrySection::GetWidth()
{
	if(m_fCachedWidth < 0.0f || m_wstrText.length() != m_uiCachedLength)
    {
		FW1_RECTF layoutRect = { 0.0f, 0.0f, 8192.0f, 8192.0f };
		FW1_RECTF rect = m_pFW1FontWrapper->MeasureString(m_wstrText.c_str(), L"Tahoma", 14.0f, &layoutRect, FW1_RESTORESTATE);

		m_fCachedWidth = rect.Right - rect.Left;
        m_uiCachedLength = (unsigned int)m_wstrText.length();
    }

    return m_fCachedWidth;
}

void ChatWindowEntrySection::Draw(float fX, float fY, bool bShadow)
{
	if(!m_pD3D11DeviceContext || !m_pFW1FontWrapper)
		return;

	unsigned int ulABGRColor = (m_ulColor & 0xFF000000) | ((m_ulColor & 0x00FF0000) >> 16) | (m_ulColor & 0x0000FF00) | ((m_ulColor & 0x000000FF) << 16);

	if(bShadow)
	{
		m_pFW1FontWrapper->DrawString(m_pD3D11DeviceContext, m_wstrText.c_str(), 14.0f, fX + 1, fY + 1, 0xff000000, FW1_RESTORESTATE);
	}

	m_pFW1FontWrapper->DrawString(m_pD3D11DeviceContext, m_wstrText.c_str(), 14.0f, fX, fY, ulABGRColor, FW1_RESTORESTATE);
}
