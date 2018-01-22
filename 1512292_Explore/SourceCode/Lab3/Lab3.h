#pragma once

#include "resource.h"
#include "CDrive.h"
#include <CommCtrl.h>
#include <Shlwapi.h>
#include "CConverter.h"
#include <WindowsX.h> //Dùng để ánh xạ các message vào các hàm xử lí tương ứng
#include <Dbt.h> //Chứa các hằng số sự kiện của thông điệp WM_DEVICECHANGE
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "ComCtl32.lib")

void OnDestroy(HWND hwnd);
BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
LRESULT OnNotify(HWND hwnd, int idFrom, NMHDR *pnm);

#define IDI_FOLDER 0
#define IDI_FOLDER_SELECTED 1
#define IDI_DESKTOP 2
#define IDI_MYCOMPUTER 3

#define IDI_FLOPPY 4
#define IDI_USB 5
#define IDI_HDD 6
#define IDI_CD  7 
#define MAX_PATH_LEN 10000
#define KB 1
#define MB 2
#define GB 3
#define TB 4
#define RADIX 10

HWND gtv;
HWND glv;
HTREEITEM hfol;
LPNMTREEVIEW tree;
HINSTANCE g_hInst;
HWND g_hWnd;
//CLIst * g_List;
CDrive * g_Drive;
long i_width;
long i_height;
BOOL g_bStarted = FALSE;
HTREEITEM hDesktop;
HTREEITEM hMyComputer;
void LoadFileAndFolder(LPCWSTR path, HWND);
//LPWSTR Convert(INT64 nSize);
LPCWSTR path;
void LoadChild(HTREEITEM &hParent, LPCWSTR path);
void PreLoad(HTREEITEM hItem);
LPWSTR GetDateModified(const FILETIME &ftLastWrite);
LPWSTR GetSize(const WIN32_FIND_DATA &fd);
LPWSTR GetType(const WIN32_FIND_DATA &fd);

