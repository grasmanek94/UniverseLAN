#include "Main.h"

static signed char hex_to_dec(signed char ch)
{
	if(ch >= '0' && ch <= '9')
		return ch - '0';

	if(ch >= 'A' && ch <= 'F')
		return ch - 'A' + 10;

	if(ch >= 'a' && ch <= 'f')
		return ch - 'A' + 10;

	return -1;
}

uint8_t * hex_to_bin(const char *str)
{
	int	len = (int)strlen(str);
	uint8_t *buf, *sbuf;

	if(len == 0 || len % 2 != 0)
		return NULL;

	sbuf = buf = (uint8_t *)malloc(len / 2);

	while(*str)
	{
		signed char bh = hex_to_dec(*str++);
		signed char bl = hex_to_dec(*str++);

		if(bl == -1 || bh == -1)
		{
			free(sbuf);
			return NULL;
		}

		*buf++ = (uint8_t)(bl | (bh << 4));
	}

	return sbuf;
}

uint32_t hex_to_color(const char *str, int len)
{
	char buf[12];
	strncpy_s(buf, str, len);
	uint32_t color = 0x00;
	byte *colorByteSet = (byte*)&color;
	int stri = 0;

	for(int i = sizeof(color) - 1; i >= 0; i--)
	{
		if(i == 3 && len == 6)
			colorByteSet[3] = 0xFF;

		else
		{
			signed char bh = hex_to_dec(buf[stri++]);
			signed char bl = hex_to_dec(buf[stri++]);

			if(bh != -1 && bl != -1)
				colorByteSet[i] = bl | (bh << 4);
		}
	}
	return color;
}

uint32_t hex_to_color_w(const wchar_t *wstr, int len, uint32_t retThisColorIfFuncFails)
{
	char *buf = (char *)malloc(len * sizeof(char));
	bool invalid = false;

	if(!buf)
		return retThisColorIfFuncFails;

	for(int i = 0; i < len; i++)
	{
		wchar_t ch = wstr[i];

		if(ch >= L'0' && ch <= L'9')
		{
			buf[i] = ('0') + (ch - L'0');
		}

		else if(ch >= L'A' && ch <= L'F')
		{
			buf[i] = ('A') + (ch - L'A');
		}

		else if ( ch >= L'a' && ch <= L'f' )
		{
			buf[i] = ('a') + (ch - L'a');
		}
		else
			invalid = true;
	}

	if(invalid)
		return retThisColorIfFuncFails;

	uint32_t result = hex_to_color(buf, len);
	
	if(buf != NULL)
	{
		free(buf);
		buf = NULL;
	}

	return result;
}
