#pragma once
#include "resource.h"
#include <windowsX.h>
#include <Commctrl.h>
#include <Shellapi.h>
#include <stdio.h>
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <fstream>
#include <ctime>
#include <Strsafe.h>
#include "CList.h"
#include "CListView.h"
#include "CNote.h"
#include "CTags.h"
#include "HOOK.h"


#define MAX_LOADSTRING 100
#pragma comment(lib, "ComCtl32.lib")
#pragma comment(lib,"Gdiplus.lib")
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
using namespace Gdiplus;

// Global Variables:
HINSTANCE			hInst;                                // current instance
WCHAR				szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR				szWindowClass[MAX_LOADSTRING];            // the main window class name
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);

GUID				myGUID;
UINT				const WMAPP_NOTIFYCALLBACK = WM_APP + 1;
UINT				const WMAPP_HIDEFLYOUT = WM_APP + 2;

HWND				gbANnote, gbANtag, edbANtag, edbANnote, btANsave, btANcancel;
HWND				txtVShead, txtVSsum, txtVSno, txtVStag[16], txtVSper[16];
HWND				edbTNnote, txtTNcaps, txtTNdate, txtTNtoday;
HWND				edbVNnote, txtVNcaps, txtVNdate, btVNsave, btVNcancel;
CListView			*lvTag, *lvNote, *lvTime;
CTags*				tagsNow;
CNote*				noteNow;
CListTags			listTags;
CListNote			listNotes;
Color				color[20] = { Color(0,0,127),		Color(0,0,255),		Color(0,127,0),		Color(0,127,127),
Color(0,255,0),		Color(0,255,255),	Color(127,0,0),		Color(127,0,127),
Color(127,0,255),	Color(127,127,0),	Color(127,127,127),	Color(127,127,255),
Color(255,0,0),		Color(255,0,127),	Color(255,127,255),	Color(255,255,0) };
int					x[2] = { 550,700 };
int					y[10] = { 80,120,160,200,240,280,320,360,400,440 };
int					xp[2] = { 500,650 };
int					yp[10] = { 60,100,140,180,220,260,300,340,380,420 };


WCHAR				buff[512];
int					len;
bool				VIEWSTATITISTICS = 0, VIEWNOTES = 0, ADDNOTE = 0, TIMENOTE = 0;
int*				percent;

GdiplusStartupInput gdiplusStartupInput;
ULONG_PTR           gdiplusToken;

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    AddNote(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	ViewNote(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	ViewStatitistics(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	TimeNote(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	ViewNote(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

BOOL				OnCreate(HWND, LPCREATESTRUCT);
LRESULT				OnNotifiViewNote(HWND, int, NMHDR*);
LRESULT				OnNotifiTimeNote(HWND, int, NMHDR *);
void				OnCommand(HWND, int, HWND, UINT);
void				OnCommandViewNote(HWND, int, HWND, UINT);
void				OnDestroy(HWND);

BOOL				AddNotificationIcon(HWND);
BOOL				DeleteNotificationIcon();
void				ShowContextMenu(HWND, POINT);

bool				checkTagsBuff(WCHAR* str);
std::vector<WCHAR*> stringCat(WCHAR* str);
void				add(WCHAR*, WCHAR*, WCHAR*);
void				WriteFile();
void				ReadFile();
void				drawPie(HDC, int, int, int, float, float, Color);
void				getPercent();
int					getSumNote();
WCHAR*				getToday();