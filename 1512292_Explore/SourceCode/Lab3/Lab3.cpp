// Lab3.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Lab3.h"
#include "CDrive.h"
#include <Shlwapi.h>

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
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
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
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hWnd, WM_NOTIFY, OnNotify);
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}

BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct) {
	g_Drive = new CDrive;
	g_Drive->GetSystemDrives();

	RECT Client;  
	InitCommonControls();
	GetClientRect(hwnd, &Client);

	//treeview
	gtv = CreateWindowEx(0,	WC_TREEVIEW,TEXT("Tree View"),
		WS_VISIBLE | WS_CHILD | WS_BORDER | TVS_HASLINES|TVS_HASBUTTONS|TVS_EX_AUTOHSCROLL,
		0,	0,	Client.right/3,	Client.bottom,	hwnd,
		(HMENU)IDC_TREEVIEW,	g_hInst	,NULL);

	TV_INSERTSTRUCT tvInsert;
	tvInsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;

	//Desktop
	tvInsert.hParent = NULL;
	tvInsert.hInsertAfter = TVI_ROOT;
	tvInsert.item.iImage = IDI_DESKTOP;
	tvInsert.item.iSelectedImage = IDI_DESKTOP;
	tvInsert.item.pszText = _T("This PC");
	tvInsert.item.lParam = (LPARAM)_T("This PC");
	hDesktop = TreeView_InsertItem(gtv, &tvInsert);

	//listview
	glv = CreateWindowEx(0, WC_LISTVIEW, _T("List View"),
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_TABSTOP |WS_BORDER|LVS_REPORT,
		Client.right/3, 0,Client.right*2/3, Client.bottom, hwnd, (HMENU)IDC_LISTVIEW, g_hInst, NULL);

	LVCOLUMN lvCol;

	lvCol.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvCol.fmt = LVCFMT_LEFT;

	lvCol.cx = 180;
	lvCol.pszText = _T("Tên");
	ListView_InsertColumn(glv, 0, &lvCol);

	lvCol.fmt = LVCFMT_LEFT | LVCF_WIDTH;
	lvCol.cx = 130;
	lvCol.pszText = _T("Kích thước");
	ListView_InsertColumn(glv, 1, &lvCol);

	lvCol.fmt = LVCFMT_RIGHT;
	lvCol.pszText = _T("Loại");
	ListView_InsertColumn(glv, 2, &lvCol);

	lvCol.pszText = _T("Ngày chỉnh sửa");
	ListView_InsertColumn(glv, 3, &lvCol);

	return true;
}

void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify) {
	switch (id)
	{
	case IDM_EXIT:
		DestroyWindow(hwnd);
		break;
	}
}

LRESULT OnNotify(HWND hwnd, int idFrom, NMHDR *pnm)
{
	if (!g_bStarted) 
	{
		LPNMTREEVIEW lpnmTree = (LPNMTREEVIEW)pnm;

		switch (pnm->code)
		{
		case TVN_ITEMEXPANDING:
		{
			tree = (LPNMTREEVIEW)pnm;
			LoadChild(tree->itemNew.hItem, path);
			break;
		}
		case TVN_SELCHANGED:
			TVITEMEX tv;
			tv.mask = TVIF_PARAM;
			tv.hItem = TreeView_GetNextItem(gtv, NULL, TVGN_CARET);
			TreeView_GetItem(gtv, &tv);
			path = (LPCWSTR)tv.lParam;
			ListView_DeleteAllItems(glv);
			if (!StrCmp(path, _T("This PC")))
			{
				LV_ITEM lv;
				lv.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
				lv.iItem = 0;
				lv.iSubItem = 0;
				lv.pszText = _T("My Computer");
				lv.iImage = IDI_MYCOMPUTER;
				lv.lParam = (LPARAM)_T("MyComputer");
				ListView_InsertItem(glv, &lv);

				TV_INSERTSTRUCT tvInsert;
				tvInsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;
				//My Computer
				tvInsert.hParent = hDesktop;
				tvInsert.hInsertAfter = TVI_LAST;
				tvInsert.item.iImage = IDI_MYCOMPUTER;
				tvInsert.item.iSelectedImage = IDI_MYCOMPUTER;
				tvInsert.item.pszText = _T("My Computer");
				tvInsert.item.lParam = (LPARAM)_T("MyComputer");
				hMyComputer = TreeView_InsertItem(gtv, &tvInsert);
				//Các ổ đĩa
				tvInsert.hParent = hMyComputer;
				for (int i = 0; i < g_Drive->GetCount(); ++i)
				{
					tvInsert.hParent = hMyComputer;
					tvInsert.item.pszText = g_Drive->GetDisplayName(i);
					tvInsert.item.lParam = (LPARAM)g_Drive->GetDriveName(i);
					HTREEITEM hDrive = TreeView_InsertItem(gtv, &tvInsert);
					if ((g_Drive->GetIconIndex(i) == IDI_HDD) || (g_Drive->GetIconIndex(i) == IDI_USB))
					{
						tvInsert.hParent = hDrive; 
						tvInsert.item.pszText = _T("");
						tvInsert.item.lParam = (LPARAM)_T("");
						TreeView_InsertItem(gtv, &tvInsert);
					}
				}
			}
			else if (!StrCmp(path, _T("MyComputer")))
			{
				LV_ITEM lv;
				for (int i = 0; i < g_Drive->GetCount(); ++i)
				{
					lv.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
					lv.iItem = i;
					lv.iImage = g_Drive->GetIconIndex(i);

					lv.iSubItem = 0;
					lv.pszText = g_Drive->GetDisplayName(i);
					lv.lParam = (LPARAM)g_Drive->GetDriveName(i);
					ListView_InsertItem(glv, &lv);

					lv.mask = LVIF_TEXT;

					lv.iSubItem = 1;
					lv.pszText = g_Drive->GetType(i);
					ListView_SetItem(glv, &lv);

					lv.iSubItem = 2;
					if (g_Drive->GetIconIndex(i) != IDI_FLOPPY && g_Drive->GetIconIndex(i) != IDI_CD)
						lv.pszText = g_Drive->GetSizeStr(i);
					else
						lv.pszText = NULL;
					ListView_SetItem(glv, &lv);

					lv.iSubItem = 3;
					if (g_Drive->GetIconIndex(i) != IDI_FLOPPY && g_Drive->GetIconIndex(i) != IDI_CD)
						lv.pszText = g_Drive->GetFreeSizeStr(i);
					else
						lv.pszText = NULL;
					ListView_SetItem(glv, &lv);
				}
			}
			else
			{
				//listview
				TCHAR buffer[10240];
				StrCpy(buffer, path);

				if (wcslen(path) == 3)
					StrCat(buffer, _T("*"));
				else
					StrCat(buffer, _T("\\*"));

				WIN32_FIND_DATA fd;
				HANDLE hFile;
				BOOL bFound = true;
				LV_ITEM lv;

				TCHAR * folderPath;
				int nItemCount = 0;

				hFile = FindFirstFileW(buffer, &fd);
				bFound = TRUE;

					bFound = (hFile != INVALID_HANDLE_VALUE);
				while (bFound)
				{
					if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
						((fd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) != FILE_ATTRIBUTE_HIDDEN) &&
						(StrCmp(fd.cFileName, _T(".")) != 0) && (StrCmp(fd.cFileName, _T("..")) != 0))
					{
						folderPath = new TCHAR[wcslen(path) + wcslen(fd.cFileName) + 2];
						StrCpy(folderPath, path);

						if (wcslen(path) != 3)
							StrCat(folderPath, _T("\\"));

						StrCat(folderPath, fd.cFileName);

						lv.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
						lv.iItem = nItemCount;
						lv.iSubItem = 0;
						lv.pszText = fd.cFileName;
						lv.lParam = (LPARAM)folderPath;
						lv.iImage = IDI_FOLDER;
						ListView_InsertItem(glv, &lv);
						ListView_SetItemText(glv, nItemCount, 2, _T("Thư mục"));
						ListView_SetItemText(glv, nItemCount, 3, GetDateModified(fd.ftLastWriteTime));
						++nItemCount;
					}
					bFound = FindNextFileW(hFile, &fd);
				}

				int folderCount = nItemCount;
				TCHAR *filePath;
				int fileSizeCount = 0;
				int fileCount = 0;

				hFile = FindFirstFileW(buffer, &fd);
				bFound = TRUE;

				if (hFile == INVALID_HANDLE_VALUE)
					bFound = FALSE;

				while (bFound)
				{
					if (((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != FILE_ATTRIBUTE_DIRECTORY) &&
						((fd.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) != FILE_ATTRIBUTE_SYSTEM) &&
						((fd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) != FILE_ATTRIBUTE_HIDDEN))
					{
						filePath = new TCHAR[wcslen(path) + wcslen(fd.cFileName) + 2];
						StrCpy(filePath, path);

						if (wcslen(path) != 3)
							StrCat(filePath, _T("\\"));

						StrCat(filePath, fd.cFileName);

						lv.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
						lv.iItem = nItemCount;
						lv.iSubItem = 0;
						lv.pszText = fd.cFileName;
						lv.lParam = (LPARAM)filePath;

						ListView_InsertItem(glv, &lv);
						ListView_SetItemText(glv, nItemCount, 1,(CConverter::Convert(fd.nFileSizeLow)));
						fileSizeCount += fd.nFileSizeLow;
						ListView_SetItemText(glv, nItemCount, 2, GetType(fd));
						ListView_SetItemText(glv, nItemCount, 3, GetDateModified(fd.ftLastWriteTime));
						++nItemCount;
						++fileCount;
					}
					bFound = FindNextFileW(hFile, &fd);
				}
				
			}

		}
		return 0;
	}
}

void OnDestroy(HWND hwnd)
{
	PostQuitMessage(0);
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

void LoadChild(HTREEITEM &hParent, LPCWSTR path)
{
	TCHAR buffer[MAX_PATH_LEN];
	StrCpy(buffer, path);

	StrCat(buffer, _T("\\*"));

	TV_INSERTSTRUCT tvInsert;
	tvInsert.hParent = hParent;
	tvInsert.hInsertAfter = TVI_LAST;
	tvInsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;
	tvInsert.item.iImage = IDI_FOLDER;
	tvInsert.item.iSelectedImage = IDI_FOLDER_SELECTED;

	WIN32_FIND_DATA fd;
	HANDLE hFile = FindFirstFileW(buffer, &fd);
	BOOL bFound = 1;

	if (hFile == INVALID_HANDLE_VALUE)
		bFound = FALSE;

	TCHAR * folderPath;
	while (bFound)
	{
		if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			&& ((fd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) != FILE_ATTRIBUTE_HIDDEN)
			&& ((fd.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) != FILE_ATTRIBUTE_SYSTEM)
			&& (StrCmp(fd.cFileName, _T(".")) != 0) && (StrCmp(fd.cFileName, _T("..")) != 0))
		{
			tvInsert.item.pszText = fd.cFileName;
			folderPath = new TCHAR[wcslen(path) + wcslen(fd.cFileName) + 2];

			StrCpy(folderPath, path);
			if (wcslen(path) != 3)
				StrCat(folderPath, _T("\\"));
			StrCat(folderPath, fd.cFileName);

			tvInsert.item.lParam = (LPARAM)folderPath;
			HTREEITEM hItem = TreeView_InsertItem(gtv, &tvInsert);
			PreLoad(hItem);
		}
		bFound = FindNextFileW(hFile, &fd);
	}//while
}

void PreLoad(HTREEITEM hItem)
{
	TCHAR buffer[MAX_PATH_LEN];
	TVITEMEX tv;
	tv.mask = TVIF_PARAM;
	tv.hItem = hItem;
	TreeView_GetItem(gtv, &tv);
	StrCpy(buffer, (LPCWSTR)tv.lParam);

	if (wcslen(buffer) == 3) //Nếu quét các ổ đĩa
	{
		if (StrStr(buffer, _T("A:")) || StrStr(buffer, _T("B:"))) //Đĩa mềm hổng làm 
			return;
	}
	else
		StrCat(buffer, _T("\\"));

	StrCat(buffer, _T("*"));

	WIN32_FIND_DATA fd;
	HANDLE hFile = FindFirstFileW(buffer, &fd);

	if (hFile == INVALID_HANDLE_VALUE)
		return;

	BOOL bFound = true;

	//Trong khi còn tìm thấy file hay thư mục
	while (bFound)
	{
		if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			&& (StrCmp(fd.cFileName, _T(".")) != 0) && (StrCmp(fd.cFileName, _T("..")) != 0))
		{
			TV_INSERTSTRUCT tvInsert;
			tvInsert.hParent = hItem;
			tvInsert.hInsertAfter = TVI_LAST;
			tvInsert.item.mask = TVIF_TEXT | TVIF_PARAM;
			tvInsert.item.pszText = NULL;
			tvInsert.item.lParam = (LPARAM)_T("PreLoad");
			TreeView_InsertItem(gtv, &tvInsert);
			bFound = FALSE;
		}
		else
			bFound = FindNextFileW(hFile, &fd);
	}//while
}

LPWSTR GetDateModified(const FILETIME &ftLastWrite)
{

	//Chuyển đổi sang local time
	SYSTEMTIME stUTC, stLocal;
	FileTimeToSystemTime(&ftLastWrite, &stUTC);
	SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);

	TCHAR *buffer = new TCHAR[50];
	wsprintf(buffer, _T("%02d/%02d/%04d %02d:%02d %s"),
		stLocal.wDay, stLocal.wMonth, stLocal.wYear,
		(stLocal.wHour>12) ? (stLocal.wHour / 12) : (stLocal.wHour),
		stLocal.wMinute,
		(stLocal.wHour>12) ? (_T("Chiều")) : (_T("Sáng")));

	return buffer;
}

LPWSTR GetType(const WIN32_FIND_DATA &fd)
{
	int nDotPos = StrRStrI(fd.cFileName, NULL, _T(".")) - fd.cFileName;
	int len = wcslen(fd.cFileName);

	if (nDotPos < 0 || nDotPos >= len) //Nếu không tìm thấy
		return _T("Không biết");

	TCHAR *szExtension = new TCHAR[len - nDotPos + 1];
	int i;

	for (i = nDotPos; i < len; ++i)
		szExtension[i - nDotPos] = fd.cFileName[i];
	szExtension[i - nDotPos] = NULL; //Kí tự kết thúc chuỗi

	if (!StrCmpI(szExtension, _T(".htm")) || !StrCmpI(szExtension, _T(".html")))
	{
		return _T("Web page");
	}
	TCHAR pszOut[256];
	HKEY hKey;
	DWORD dwType = REG_SZ;
	DWORD dwSize = 256;

	//Kiếm handle của extension tương ứng trong registry
	if (RegOpenKeyEx(HKEY_CLASSES_ROOT, szExtension, 0, KEY_READ, &hKey) != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
		return _T("Không biết");
	}

	if (RegQueryValueEx(hKey, NULL, NULL, &dwType, (PBYTE)pszOut, &dwSize) != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
		return _T("Không biết");
	}
	RegCloseKey(hKey);

	//Kiếm mô tả về thông tin của extension thông qua handle của key tương ứng trong registry
	TCHAR *pszPath = new TCHAR[1000];
	dwSize = 1000;
	if (RegOpenKeyEx(HKEY_CLASSES_ROOT, pszOut, 0, KEY_READ, &hKey) != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
		return _T("Không biết");
	}

	if (RegQueryValueEx(hKey, NULL, NULL, &dwType, (PBYTE)pszPath, &dwSize) != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
		return _T("Không biết");
	}
	RegCloseKey(hKey);

	return pszPath;
}


