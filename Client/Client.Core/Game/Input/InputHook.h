#pragma once

namespace InputHook
{
	static LRESULT APIENTRY WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	bool Initialize();
	void Remove();
}
