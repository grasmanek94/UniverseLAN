#include "Main.h"

ChatWindowEntry::ChatWindowEntry(ID3D11DeviceContext *pD3D11DeviceContext, IFW1FontWrapper *pFW1FontWrapper)
{
	m_pD3D11DeviceContext = pD3D11DeviceContext;
	m_pFW1FontWrapper = pFW1FontWrapper;

	m_Sections.clear();
}

ChatWindowEntry::~ChatWindowEntry()
{
	m_Sections.clear();
}

float ChatWindowEntry::GetWidth()
{
    float fWidth = 0.0f;
    std::vector<ChatWindowEntrySection>::iterator it;

    for(it = m_Sections.begin(); it != m_Sections.end(); it++)
    {
        fWidth += (*it).GetWidth();
    }

    return fWidth;
}

void ChatWindowEntry::Format(std::wstring wstrText, unsigned long ulColor, bool bEnableColorEmbedding)
{
	m_Sections.clear();

	HandleColorEmbeddedText(wstrText, ulColor, bEnableColorEmbedding);
}

void ChatWindowEntry::FormatWithNickname(std::wstring wstrNickname, std::wstring wstrMessage, unsigned long ulNicknameColor, unsigned long ulMessageColor, bool bEnableColorEmbedding)
{
	ChatWindowEntrySection nicknameSection(m_pD3D11DeviceContext, m_pFW1FontWrapper, wstrNickname, ulNicknameColor);

	m_Sections.clear();
	m_Sections.push_back(nicknameSection);

	HandleColorEmbeddedText(wstrMessage, ulMessageColor, bEnableColorEmbedding);
}

void ChatWindowEntry::Draw(float fX, float fY, bool bShadow)
{
	float fCurrentX = fX;
	std::vector<ChatWindowEntrySection>::iterator it = m_Sections.begin();

    for(; it != m_Sections.end(); it++)
    {
        (*it).Draw(fCurrentX, fY, bShadow);

        fCurrentX += (*it).GetWidth();
    }
}

void ChatWindowEntry::HandleColorEmbeddedText(std::wstring wstrColorEmbeddedText, unsigned long ulDefaultColor, bool bEnableColorEmbedding)
{
	size_t lengthOfString = wstrColorEmbeddedText.length();
	const wchar_t *wcColorEmbeddedText = wstrColorEmbeddedText.c_str();
	unsigned long ulCurrentColor = ulDefaultColor;
	std::wstring wstrSectionText;

	wstrSectionText.clear();

	size_t i = 0, j = 0;

	for(i = 0; i < lengthOfString; i++)
	{
		if(lengthOfString >= 8 && (wcColorEmbeddedText[i] == L'[' && wcColorEmbeddedText[i + 7] == L']'))
		{
			bool bValid = true;

			for(size_t k = 0; k < 6; k++)
			{
				wchar_t wchar = wcColorEmbeddedText[(i + k) + 1];

				if((wchar < L'0' || wchar > L'9') && (wchar < L'A' || wchar > L'F') && (wchar < L'a' || wchar > L'f'))
				{
					bValid = false;
					break;
				}
			}

			if(bValid)
			{
				ChatWindowEntrySection section(m_pD3D11DeviceContext, m_pFW1FontWrapper, wstrSectionText, ulCurrentColor);
				m_Sections.push_back(section);

				wstrSectionText.clear();

				if(bEnableColorEmbedding)
				{
					ulCurrentColor = hex_to_color_w(&wcColorEmbeddedText[i + 1], 6, ulCurrentColor);
				}

				i += 7;
				continue;
			}
		}

		wstrSectionText.push_back(wcColorEmbeddedText[i]);
		j++;
	}

	ChatWindowEntrySection section(m_pD3D11DeviceContext, m_pFW1FontWrapper, wstrSectionText, ulCurrentColor);
	m_Sections.push_back(section);
}
