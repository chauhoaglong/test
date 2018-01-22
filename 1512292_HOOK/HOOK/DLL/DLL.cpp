// DLL.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "DLL.h"

HHOOK hHook = NULL;
HINSTANCE hinstLib;
bool check = 0;

LRESULT CALLBACK KeyBoardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (wParam == WM_KEYUP && (GetAsyncKeyState(VK_SPACE) & 0x8000))
	{
		check = 1 - check;
		SwapMouseButton(check);
		return TRUE;
	}

	return CallNextHookEx(hHook, nCode, wParam, lParam);
}


DLL_API void InstallHookProc(HWND hWnd)
{
	if (hHook != NULL) return;

	hHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)KeyBoardProc, hinstLib, 0);
	if (hHook)
		MessageBox(hWnd, L"Setup hook successfully", L"Result", MB_OK);
	else
		MessageBox(hWnd, L"Setup hook fail", L"Result", MB_OK);
}

DLL_API void RemoveHookProc(HWND hWnd)
{
	if (hHook == NULL) return;
	UnhookWindowsHookEx(hHook);
	hHook = NULL;
	SwapMouseButton(0);
	MessageBox(hWnd, L"Remove hook successfully", L"Result", MB_OK);
}