// 1512292Paint.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "1512292_Paint.h"
#include <Windowsx.h>
#include <Windows.h>
#include <Objbase.h>
#include "RibbonFramework.h"
#include "RibbonIDs.h"
#include "CommandHandler.h"
#include "Application.h"
#pragma comment(lib, "Ole32.lib")


// Global Variables:
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	HRESULT hr = CoInitialize(NULL);
	if (FALSE(hr))
	{
		return FALSE;
	}
	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_MY1512292_PAINT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY1512292_PAINT));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	CoUninitialize();
	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = 0 | CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY1512292_PAINT));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MY1512292_PAINT);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	LoadLibrary(TEXT("Msftedit.dll"));
	hInst = hInstance; // Store instance handle in our global variable
	
	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (CCommandHandler::key == 4)
	{
		message = WM_DESTROY;
	}
	if (CCommandHandler::key == 5 || CCommandHandler::key == 6)
	{
		message = WM_COMMAND;
	}
	switch (message)
	{
	case WM_CREATE:
	{
		initSucces = InitializeFramework(hWnd);
		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
		DLL = LoadLibrary(L"DLL.dll");
		if (!DLL)
		{
			MessageBox(hWnd, L"Không kết nối được DLL.dll", L"Lỗi", 0);
			SendMessage(hWnd, WM_DESTROY, 0, 0);
		}
		else
		{
			dll_line = (DLL_LINE)GetProcAddress(DLL, "CreateLine");
			dll_circle = (DLL_CIRCLE)GetProcAddress(DLL, "CreateCircle");
			dll_ellipse = (DLL_ELLIPSE)GetProcAddress(DLL, "CreateEllipse");
			dll_rectangle = (DLL_RECTANGLE)GetProcAddress(DLL, "CreateRectangle");
			dll_square = (DLL_SQUARE)GetProcAddress(DLL, "CreateSquare");
			if (!dll_line || !dll_circle || !dll_ellipse || !dll_rectangle || !dll_square)
			{
				MessageBox(hWnd, L"Không lấy được địa chỉ hàm", L"Lỗi", 0);
				FreeLibrary(DLL);
				SendMessage(hWnd, WM_DESTROY, 0, 0);
			}
			else
			{
				prototype.clear();
				prototype.push_back(dll_line());
				prototype.push_back(dll_line());
				prototype.push_back(dll_rectangle());
				prototype.push_back(dll_square());
				prototype.push_back(dll_ellipse());
				prototype.push_back(dll_circle());
				readFile("zyx.txt");
			}
		}
	}
	break;

	case WM_MOUSEMOVE:
	{
		nowX = GET_X_LPARAM(lParam);
		nowY = GET_Y_LPARAM(lParam);
		if (CCommandHandler::key == 1 || CCommandHandler::key == 2 || CCommandHandler::key == 3)
		{
			drawStyle = CCommandHandler::key;
		}
		if (isDrawing)
		{
			temp = (prototype[(drawStyle - 1) * 2 + isShift]->Clone());
			temp->Set(startX, startY, nowX, nowY);
			InvalidateRect(hWnd, NULL, FALSE);
		}
		WCHAR buffer[200];
		wsprintf(buffer, L"1512292Paint %d %d", nowX, nowY);
		SetWindowText(hWnd, buffer);
	}
	break;

	case WM_KEYDOWN:
	{
		int shi = GetKeyState(VK_SHIFT);
		if (shi & 0x8000)
			isShift = 1;
		temp = (prototype[(drawStyle - 1) * 2 + isShift]->Clone());
		temp->Set(startX, startY, nowX, nowY);
		InvalidateRect(hWnd, NULL, FALSE);
	}
	break;

	case WM_KEYUP:
	{
		int shi = GetKeyState(VK_SHIFT);
		if (!(shi & 0x8000))
			isShift = 0;
		temp = (prototype[(drawStyle - 1) * 2 + isShift]->Clone());
		temp->Set(startX, startY, nowX, nowY);
		InvalidateRect(hWnd, NULL, FALSE);
	}
	break;

	case WM_LBUTTONDOWN:
	{
		startX = GET_X_LPARAM(lParam);
		startY = GET_Y_LPARAM(lParam);

		if (!isDrawing)
		{
			isDrawing = TRUE;
		}
	}
	break;

	case WM_LBUTTONUP:
	{
		endX = GET_X_LPARAM(lParam);
		endY = GET_Y_LPARAM(lParam);
		temp = (prototype[(drawStyle - 1) * 2 + isShift]->Clone());
		if (temp)
		{
			temp->Set(startX, startY, endX, endY);
			list.push_back(temp);
		}
		isDrawing = FALSE;
	}
	break;

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		HMENU menu = GetMenu(hWnd);
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			GdiplusShutdown(gdiplusToken);
			writeFile("zyx.txt");
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		RECT rect;
		GetClientRect(hWnd, &rect);
		HDC memDC;
		memDC = CreateCompatibleDC(hdc);
		HBITMAP bitmap, oBitmap;
		bitmap = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
		oBitmap = (HBITMAP)SelectObject(memDC, bitmap);
		FillRect(memDC, &rect, HBRUSH(GetBkColor(memDC)));
		for (int i = 0; i < list.size(); i++)
		{
			list[i]->Draw(memDC);
		}

		if (isDrawing) {
			temp->Draw(memDC);
			delete temp;
		}
		BitBlt(hdc, 0, 0, rect.right, rect.bottom, memDC, 0, 0, SRCCOPY);
		SelectObject(memDC, oBitmap);
		DeleteDC(memDC);
		DeleteObject(bitmap);
		EndPaint(hWnd, &ps);
	}
	break;

	case WM_DESTROY:
	{
		writeFile("zyx.txt");
		GdiplusShutdown(gdiplusToken);
		//		DestroyFramework();
		PostQuitMessage(0);
	}
	break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void writeFile(char* path)
{
	ofstream f(path);
	f << list.size() << endl;
	for (int i = 0; i < list.size(); i++)
	{
		f << list[i]->toString();
	}
	f.close();
}

void readFile(char* path)
{
	ifstream f(path);
	SHAPE* temp;
	int count;
	int type;
	if (f)
	{
		list.clear();
		f >> count;
		for (int i = 0; i < count; i++)
		{
			f >> type;
			temp = prototype[type]->Clone();
			if (temp)
			{
				temp->getData(f);
				list.push_back(temp);
			}
		}
	}
	f.close();
}