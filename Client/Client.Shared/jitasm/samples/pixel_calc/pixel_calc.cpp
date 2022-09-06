// Copyright (c) 2009, Hikaru Inoue, Akihiro Yamasaki,
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//    * Redistributions of source code must retain the above copyright
//      notice, this list of conditions and the following disclaimer.
//    * Redistributions in binary form must reproduce the above
//      copyright notice, this list of conditions and the following
//      disclaimer in the documentation and/or other materials provided
//      with the distribution.
//    * The names of the contributors may not be used to endorse or promote
//      products derived from this software without specific prior written
//      permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// Pixel Calc sample

#include <stdio.h>
#include <windows.h>
#include <gdiplus.h>
#include "pixel_calc_jit.h"

#define IDM_LOAD_SOURCE1	100
#define IDM_LOAD_SOURCE2	101
#define IDM_EXIT			105
#define IDC_EXPRESSION		110
#define IDC_RENDER			111

using namespace Gdiplus;

HINSTANCE g_hInstance;
Bitmap *g_imgSource1;
Bitmap *g_imgSource2;
Bitmap *g_imgResult;

/**
 * Show Open file dialog and load image
 */
void LoadSourceImage(HWND hWnd, Bitmap **ppBitmap)
{
	WCHAR szFile[MAX_PATH];
	szFile[0] = L'\0';

	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFilter = L"Bitmap files (*.bmp;*.jpg;*.png;*.tif;*.gif)\0*.bmp;*.jpg;*.png;*.tif;*.gif\0All files (*.*)\0*.*\0\0";
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile) / sizeof(WCHAR);
	ofn.Flags = OFN_FILEMUSTEXIST;
	if (GetOpenFileName(&ofn))
	{
		delete *ppBitmap;
		*ppBitmap = NULL;

		*ppBitmap = Bitmap::FromFile(szFile);
	}
}

void UpdateResultImage(HWND hWnd, BOOL bRecreateResultBuffer)
{
	UINT width = -1;
	UINT height = -1;

	if (bRecreateResultBuffer)
	{
		if (g_imgSource1) {
			width = g_imgSource1->GetWidth();
			height = g_imgSource1->GetHeight();
		}
		if (g_imgSource2) {
			width = min(width, g_imgSource2->GetWidth());
			height = min(height, g_imgSource2->GetHeight());
		}

		Bitmap *img = new Bitmap(width, height, PixelFormat32bppARGB);
		if (!img)
			return;

		delete g_imgResult;
		g_imgResult = img;
	}

	if (!g_imgResult)
		return;

	WCHAR szExpr[1024];
	if (!GetDlgItemText(hWnd, IDC_EXPRESSION, szExpr, sizeof(szExpr) / sizeof(WCHAR)))
		return;

	width = g_imgResult->GetWidth();
	height = g_imgResult->GetHeight();
	if (width == 0 || height == 0)
		return;

	if (!g_imgSource1)
		g_imgSource1 = new Bitmap(width, height, PixelFormat32bppARGB);

	if (!g_imgSource2)
		g_imgSource2 = new Bitmap(width, height, PixelFormat32bppARGB);

	Rect rcLock(0, 0, width, height);

	BitmapData src1BmpData;
	ZeroMemory(&src1BmpData, sizeof(BitmapData));
	if (g_imgSource1)
		g_imgSource1->LockBits(&rcLock, ImageLockModeWrite, PixelFormat32bppARGB, &src1BmpData);

	BitmapData src2BmpData;
	ZeroMemory(&src2BmpData, sizeof(BitmapData));
	if (g_imgSource2)
		g_imgSource2->LockBits(&rcLock, ImageLockModeWrite, PixelFormat32bppARGB, &src2BmpData);

	BitmapData dstBmpData;
	ZeroMemory(&dstBmpData, sizeof(BitmapData));
	g_imgResult->LockBits(&rcLock, ImageLockModeWrite, PixelFormat32bppARGB, &dstBmpData);

	LARGE_INTEGER start, end;
	::QueryPerformanceCounter(&start);

	bool res = RenderJIT(szExpr, dstBmpData.Scan0, dstBmpData.Stride, src1BmpData.Scan0, src1BmpData.Stride, src2BmpData.Scan0, src2BmpData.Stride, width, height);

	::QueryPerformanceCounter(&end);

	g_imgResult->UnlockBits(&dstBmpData);
	if (g_imgSource2) g_imgSource2->UnlockBits(&dstBmpData);
	if (g_imgSource1) g_imgSource1->UnlockBits(&dstBmpData);

	LARGE_INTEGER freq;
	::QueryPerformanceFrequency(&freq);

	WCHAR szTitle[128];
	if (res)
		swprintf(szTitle, 128, L"Pixel Calc - Render time %f ms", (double)(end.QuadPart - start.QuadPart) / (double)freq.QuadPart * 1000.0);
	else
		swprintf(szTitle, 128, L"Pixel Calc - Invalid expression!", (double)(end.QuadPart - start.QuadPart) / (double)freq.QuadPart * 1000.0);
	SetWindowText(hWnd, szTitle);

	RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
}

/*
 * Window procedure
 */
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"src1 + src2", WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE, 2, 2, 100, 24, hWnd, (HMENU)IDC_EXPRESSION, g_hInstance, NULL);
		break;

	case WM_SIZE:
		SetWindowPos(GetDlgItem(hWnd, IDC_EXPRESSION), NULL, 2, 2, LOWORD(lParam) - 4, 24, SWP_NOZORDER);
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDM_LOAD_SOURCE1:
			LoadSourceImage(hWnd, &g_imgSource1);
			UpdateResultImage(hWnd, TRUE);
			break;

		case IDM_LOAD_SOURCE2:
			LoadSourceImage(hWnd, &g_imgSource2);
			UpdateResultImage(hWnd, TRUE);
			break;

		case IDC_RENDER:
			UpdateResultImage(hWnd, FALSE);
			break;

		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;

	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			Graphics g(hdc);
			if (g_imgResult)
				g.DrawImage(g_imgResult, 0.0f, 30.0f);
			EndPaint(hWnd, &ps);
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	g_hInstance = hInstance;

	// Initialize GDI+.
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= NULL;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= L"PIXEL_CALC";
	wcex.hIconSm		= NULL;
	RegisterClassEx(&wcex);

	HMENU hMenu = CreateMenu();
	if (hMenu)
	{
		HMENU hFileMenu = CreateMenu();
		InsertMenu(hFileMenu, -1, MF_BYPOSITION | MF_STRING, IDM_LOAD_SOURCE1, L"Load source 1");
		InsertMenu(hFileMenu, -1, MF_BYPOSITION | MF_STRING, IDM_LOAD_SOURCE2, L"Load source 2");
		InsertMenu(hFileMenu, -1, MF_BYPOSITION | MF_STRING, IDM_EXIT, L"&Exit");
		InsertMenu(hMenu, -1, MF_BYPOSITION | MF_STRING | MF_POPUP, (UINT_PTR)hFileMenu, L"&File");
		InsertMenu(hMenu, -1, MF_BYPOSITION | MF_STRING, IDC_RENDER, L"&Render");
	}

	HWND hWnd = CreateWindow(L"PIXEL_CALC", L"Pixel Calc", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, hMenu, hInstance, NULL);
	if (hWnd)
	{
		ShowWindow(hWnd, nCmdShow);
		UpdateWindow(hWnd);

		// Message Loop
		MSG msg;
		while (GetMessage(&msg, NULL, 0, 0))
		{
			if (msg.message == WM_KEYDOWN && msg.wParam == VK_RETURN)
				PostMessage(hWnd, WM_COMMAND, MAKEWPARAM(IDC_RENDER, 0), 0);

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	delete g_imgSource1;
	delete g_imgSource2;
	delete g_imgResult;
	GdiplusShutdown(gdiplusToken);

	return 0;
}
