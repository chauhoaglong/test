// 1512292Paint.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "1512292Paint.h"
#include <Windowsx.h>
#include <Windows.h>
#include <Objbase.h>
#include "RibbonFramework.h"
#include "RibbonIDs.h"
#include "CommandHandler.h"
#include "Application.h"
#pragma comment(lib, "Ole32.lib")
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
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
    LoadStringW(hInstance, IDC_1512292PAINT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_1512292PAINT));

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
    return (int) msg.wParam;
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

	wcex.style			= 0 | CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_1512292PAINT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_1512292PAINT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
	readFile("zyx.txt");
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW| WS_CLIPCHILDREN,
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

GdiplusStartupInput gdiplusStartupInput;
ULONG_PTR           gdiplusToken;
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
	//	HMENU menu = GetMenu(hWnd);
	//	CheckMenuItem(menu, IDM_LINE, MF_CHECKED);
	//	drawStyle = 1;
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
			temp = SHAPE::create(drawStyle, isShift);
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
		temp = SHAPE::create(drawStyle, isShift);
		temp->Set(startX, startY, nowX, nowY);
		InvalidateRect(hWnd, NULL, FALSE);
	}
	break;

	case WM_KEYUP:
	{
		int shi = GetKeyState(VK_SHIFT);
		if (!(shi & 0x8000))
			isShift = 0;
		temp = SHAPE::create(drawStyle, isShift);
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
		temp = SHAPE::create(drawStyle, isShift);
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
		// Parse the menu selections:
		//if (CCommandHandler::key == 6)
		//{
		//	ZeroMemory(&ofn, sizeof(ofn));
		////	ZeroMemory(&filename, sizeof(filename));
		//	ofn.lStructSize = sizeof(ofn);
		//	ofn.hwndOwner = hWnd;
		//	ofn.nMaxFile = BUFFER_SIZE;
		//	// Chú ý chuỗi bên dưới double zero terminated!
		//	ofn.lpstrFilter = L"Text document (*.txt) \0*.txt\0All files (*.*)\0*.*\0";

		//	ofn.nFilterIndex = 1; // Text | *.txt
		//	ofn.lpstrInitialDir = NULL;
		//	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
		//	if (GetOpenFileName(&ofn) == TRUE)
		//	{
		//		MessageBox(hWnd, ofn.lpstrFile, L"", MB_OK);
		//	}
		//	else MessageBox(hWnd, L"Lỗi", L"", MB_OK);
		//}
		//if (CCommandHandler::key == 5)
		//{
		//	ZeroMemory(&ofn, sizeof(ofn));
		//	//	ZeroMemory(&filename, sizeof(filename));
		//	ofn.lStructSize = sizeof(ofn);
		//	ofn.hwndOwner = hWnd;
		//	ofn.nMaxFile = BUFFER_SIZE;
		//	// Chú ý chuỗi bên dưới double zero terminated!
		//	ofn.lpstrFilter = L"Text document (*.txt) \0*.txt\0All files (*.*)\0*.*\0";

		//	ofn.nFilterIndex = 1; // Text | *.txt
		//	ofn.lpstrInitialDir = NULL;
		//	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
		//	if (GetSaveFileName(&ofn) == TRUE)
		//	{
		//		MessageBox(hWnd, ofn.lpstrFile, L"", MB_OK);
		//	}
		//	else MessageBox(hWnd, L"Lỗi", L"", MB_OK);
		//}
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
		/*case IDM_ELIPSE:
			CheckMenuItem(menu, IDM_ELIPSE, MF_CHECKED);
			CheckMenuItem(menu, IDM_LINE, MF_DISABLED);
			CheckMenuItem(menu, IDM_RECTANGLE, MF_DISABLED);
			drawStyle = 3;
			break;
		case IDM_LINE:
			CheckMenuItem(menu, IDM_LINE, MF_CHECKED);
			CheckMenuItem(menu, IDM_RECTANGLE, MF_DISABLED);
			CheckMenuItem(menu, IDM_ELIPSE, MF_DISABLED);
			drawStyle = 1;
			break;
		case IDM_RECTANGLE:
			CheckMenuItem(menu, IDM_RECTANGLE, MF_CHECKED);
			CheckMenuItem(menu, IDM_LINE, MF_DISABLED);
			CheckMenuItem(menu, IDM_ELIPSE, MF_DISABLED);
			drawStyle = 2;
			break;*/
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
		writeFile("zyx.txt");
		GdiplusShutdown(gdiplusToken);
//		DestroyFramework();
        PostQuitMessage(0);
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

void SaveFileW(HWND hWnd)
{
	//const int BUFFER_SIZE = 260;
	OPENFILENAME ofn;
	char filename[BUFFER_SIZE];
	ZeroMemory(&ofn, sizeof(ofn));
	ZeroMemory(&filename, sizeof(filename));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWnd;
	ofn.nMaxFile = BUFFER_SIZE;
	// Chú ý chuỗi bên dưới double zero terminated!
	ofn.lpstrFilter = L"Text document (*.txt) \0*.txt\0All files (*.*)\0*.*\0";

	ofn.nFilterIndex = 1; // Text | *.txt
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER | OFN_ENABLEHOOK | OFN_ENABLESIZING;
	ofn.hInstance = hInst;
	ofn.lpstrFile = (LPWSTR)filename;
	if (GetSaveFileName(&ofn) == TRUE) 
	{
		int i = 0;
		while (i <= ofn.lStructSize - 1) 
		{
			filename[i] = ofn.lpstrFile[i];
			i++;
		}
		filename[ofn.lStructSize] = NULL;
		writeFile(filename);
		HANDLE hf = CreateFile(ofn.lpstrFile,GENERIC_READ,0,(LPSECURITY_ATTRIBUTES)NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,(HANDLE)NULL);
	}

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

void OpenFileW(HWND hWnd)
{
//	const int BUFFER_SIZE = 260;
	OPENFILENAME ofn;
	char filename[BUFFER_SIZE];
	ZeroMemory(&ofn, sizeof(ofn));
	ZeroMemory(&filename, sizeof(filename));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWnd;
	ofn.nMaxFile = BUFFER_SIZE;
	// Chú ý chuỗi bên dưới double zero terminated!
	ofn.lpstrFilter = L"Text document (*.txt) \0*.txt\0All files (*.*)\0*.*\0";
	ofn.nFilterIndex = 1; // Text | *.txt
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	ofn.hInstance = hInst;
	ofn.lpstrFile = (LPWSTR)filename;

	if (GetOpenFileName(&ofn) == TRUE) 
	{
		int i = 0;
		while (i <= ofn.lStructSize - 1) {
			filename[i] = ofn.lpstrFile[i];
			i++;
		}
		filename[ofn.lStructSize] = NULL;
		readFile(filename);
	}
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
			temp = SHAPE::create(type);
			if (temp)
			{
				temp->getData(f);
				list.push_back(temp);
			}
		}
	}
	f.close();
}