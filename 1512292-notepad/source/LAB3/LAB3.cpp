// LAB3.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "LAB3.h"
#include <Windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <iostream>
#include <fstream>
#include <locale>
#include <codecvt>
#include <io.h>
#include <fcntl.h>
#include "Commdlg.h"
#include <sstream>
#include <codecvt>
#include <Richedit.h>


#define MAX_LOADSTRING 100
using namespace std;
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "ComCtl32.lib")
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
string readFile(char* path);
void WriteNotepad(char* path);
// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
int enCodingChoise;
HWND MyNotepad;
LPCSTR TEXT;
//
UINT_PTR CALLBACK OFNHookProc(
	_In_ HWND   hdlg,
	_In_ UINT   uiMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
);
BOOL OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct);
void OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify);
void OnPaint(HWND hWnd);
void OnDestroy(HWND hwnd);
void GetSize(HWND hwnd, int &height, int &weight);
void OnSize(HWND hWnd, UINT state, int cx, int cy);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB3, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB3));

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

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB3));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB3);
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

	HWND hWnd = CreateWindowW(szWindowClass, L"1512292 - Notepad", WS_OVERLAPPEDWINDOW,
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
	switch (message) {
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hWnd, WM_SIZE, OnSize);
		HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
void OnSize(HWND hWnd,UINT state, int cx,int cy)
{
		int h, w;
		GetSize(hWnd, h, w);
		MoveWindow(MyNotepad, 0, 0, w, h, TRUE);
		
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


string OpenFileW(HWND hWnd) {
	const int BUFFER_SIZE = 260;
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

	if (GetOpenFileName(&ofn) == TRUE) {
		int i = 0;
		while (i <= ofn.lStructSize - 1) {
			filename[i] = ofn.lpstrFile[i];
			i++;
		}
		filename[ofn.lStructSize] = NULL;

		string content = readFile(filename);
		return content;
	}
	else {
		//MessageBox(hWnd, L"You haven't chosen any file!", L"Cannot open", MB_OK);
		return "";
	}
	return "";
}

void SaveFileW(HWND hWnd) {
	const int BUFFER_SIZE = 260;
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
	//ofn.lpfnHook = OFNHookProc;
	if (GetSaveFileName(&ofn) == TRUE) {
		int i = 0;
		while (i <= ofn.lStructSize - 1) {
			filename[i] = ofn.lpstrFile[i];
			i++;
		}
		filename[ofn.lStructSize] = NULL;
		WriteNotepad(filename);
		HANDLE hf = CreateFile(ofn.lpstrFile,
			GENERIC_READ,
			0,
			(LPSECURITY_ATTRIBUTES)NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			(HANDLE)NULL);
	}

}

void WriteNotepad(char* path) {
	int size = GetWindowTextLength(MyNotepad);
	wchar_t *content = new wchar_t(size + 1);
	WCHAR *buf = new WCHAR(size + 1);
	GetWindowText(MyNotepad, buf, size + 1);
	string a;
	content = buf;
	for (int i = 0; i < size; i++) {
		a.push_back(content[i]);
	}
	ofstream ifs(path, ios::binary);
	ifs << a;
	ifs.close();
	if (!buf)
		delete[] buf;
	if (!content)
		delete[] content;
}

BOOL OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
	RECT main;
	GetWindowRect(hWnd, &main);
	INITCOMMONCONTROLSEX icc;
	icc.dwSize = sizeof(icc);
	icc.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&icc);
	MyNotepad = CreateWindowEx(0, MSFTEDIT_CLASS, L"",
		WS_VISIBLE | WS_CHILD | WS_VSCROLL | WS_HSCROLL |
		ES_MULTILINE | ES_LEFT | ES_NOHIDESEL | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
		0, 0, main.right - main.left - 18, main.bottom - main.top - 60,
		hWnd, NULL, hInst, NULL);
	if (!MyNotepad)
		FatalAppExitA(0, "Couldn't create your rich text box!");
	return true;
}

void GetSize(HWND hwnd, int &height, int &weight)
{
	RECT rect;
	if (GetWindowRect(hwnd, &rect))
	{
		height = rect.bottom - rect.top-60;
		weight = rect.right - rect.left-18;
	}
}

void OnCommand(HWND hWnd, int ID, HWND hwndCtl, UINT codeNotify)
{
	HMENU hmenu = GetMenu(hWnd);
	switch (ID)
	{
	case IDM_ABOUT:
		DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
		break;
	case ID_FILE_OPEN: {
		//tạo MyNotepad
		string result = OpenFileW(hWnd);
		wstring wide;
		using convert_typeX = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_typeX, wchar_t> utfconv;
		wide = utfconv.from_bytes(result);
		int i = wide.size();
		while (i > 0) {
			if (wide[i] == 52480) {
				wide[i] = NULL;
				break;
			}
			i--;
		}
		SetWindowText(MyNotepad, (LPCWSTR)wide.c_str());
		break;
	}
	case ID_FILE_SAVE:
		SaveFileW(hWnd);
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case IDM_EXIT:
		DestroyWindow(hWnd);
		break;
	case ID_COPY:
		SendMessage(MyNotepad, WM_COPY, 0, 0);
		break;
	case ID_CUT:
		SendMessage(MyNotepad, WM_CUT, 0, 0);
		break;
	case ID_PASTE:
		SendMessage(MyNotepad, WM_PASTE, 0, 0);
		break;
	}
}

void OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);
	// TODO: Add any drawing code that uses hdc here...
	EndPaint(hWnd, &ps);
}

void OnDestroy(HWND hWnd) 
{
	if (EN_CHANGE)
	{
		int _ID = MessageBox(hWnd, L"Bạn có muốn lưu hay không", L"", MB_OKCANCEL);
		if (_ID == IDOK)
		{
			SaveFileW(hWnd);
			InvalidateRect(hWnd, NULL, TRUE);
		}
	}
}

string readFile(char* path)
{
	ifstream ifs;
	ifs.open((const char*)path, ios::in | ios::binary);
	stringstream ss;
	string result;
	int encoding = 0;

	if (!ifs.is_open()) {
		// Unable to read file
		result.clear();
		return NULL;
	}
	else if (ifs.eof()) {
		result.clear();
	}
	ifs.seekg(0);
	ss << ifs.rdbuf() << "";
	result = ss.str();
	ifs.close();
	return result;
}