#pragma once
#include "stdafx.h"
#include <stdio.h>

HWND hWndwin;
HHOOK hHook = NULL;
HINSTANCE hinstLib;
bool flagHOOK = 0;
LRESULT CALLBACK HookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (wParam == WM_KEYUP
		&& (GetAsyncKeyState(VK_SPACE) & 0x8000)
		&& (GetAsyncKeyState(VK_CONTROL) & 0x8000 && !flagHOOK))
	{
		flagHOOK = 1;
		return TRUE;
	}
	return CallNextHookEx(hHook, nCode, wParam, lParam);
}

void InstallQuickNoteHook(HWND hWnd)
{
	hWndwin = hWnd;
	if (hHook != NULL) return;
	hHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)HookProc, hinstLib, 0);
}

void RemoveQuickNoteHook(HWND hWnd)
{
	if (hHook == NULL) return;
	UnhookWindowsHookEx(hHook);
	hHook = NULL;
}
