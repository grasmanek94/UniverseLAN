#pragma once

static signed char hex_to_dec(signed char ch);
uint8_t * hex_to_bin(const char *str);
uint32_t hex_to_color(const char *str, int len);
uint32_t hex_to_color_w(const wchar_t *wstr, int len, uint32_t retThisColorIfFuncFails);
