#pragma once

#include "resource.h"
#include "Shape.h"
#include <vector>
#include <Commdlg.h>
#include <commctrl.h>
#include <iostream>
#include <fstream>
#include <string>
HINSTANCE hInst;
HINSTANCE DLL;
#define MAX_LOADSTRING 100// current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

												// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void writeFile(char* path);
void readFile(char* path);
using namespace std;
typedef SHAPE* (__cdecl *DLL_LINE)();
typedef SHAPE* (__cdecl *DLL_RECTANGLE)();
typedef SHAPE* (__cdecl *DLL_CIRCLE)();
typedef SHAPE* (__cdecl *DLL_SQUARE)();
typedef SHAPE* (__cdecl *DLL_ELLIPSE)();

GdiplusStartupInput gdiplusStartupInput;
ULONG_PTR           gdiplusToken;
int drawStyle = 1;  //1-line, 2-rect, 3-elipse
bool isShift = 0, isDrawing = 0;
int startX, startY, endX, endY, nowX, nowY;
RECT rect;
WCHAR buff[256];
HDC hdc;
SHAPE* temp;
vector<SHAPE*> list;
bool initSucces;
DLL_LINE dll_line;
DLL_CIRCLE dll_circle;
DLL_ELLIPSE dll_ellipse;
DLL_RECTANGLE dll_rectangle;
DLL_SQUARE dll_square;
vector<SHAPE*> prototype;