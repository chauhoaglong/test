#pragma once

#include "resource.h"
#include "ListView.h"
#include "Expense.h"
#include <gdiplus.h>
#include <fstream>
#include <vector>
#include <Windows.h>
#include <wchar.h>
#pragma comment (lib,"Gdiplus.lib")
using namespace Gdiplus;
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

HWND hwndheader;
HWND hwnd;
HWND hwndbutton;
HWND typeBox;
TCHAR* typeChoose[6] = { L"Ăn uống",L"Di chuyển",L"Nhà cửa ", L"Xe cộ" ,L"Nhu yếu phẩm",L"Dịch vụ" };
HWND txtDetail;
HWND txtFee;
HWND txtSum;
HWND txtPercent[6];
ListView *g_ListView;
std::vector<Expense> List;
bool clickDetail = 0;
bool clickFee = 0;
int State;
long sum;
long money[6];
float percent[6];
GdiplusStartupInput gdiplusStartupInput;
ULONG_PTR           gdiplusToken;
Color color[6] = { Color(255,255,0,0),Color(255,0,255,0),Color(255,255,255,0),Color(255,0,0,255),Color(255,255,0,255),Color(255,0,255,255) };
std::vector<std::vector<Expense>> state;
//int choose[2] = {IDC_DETAILBOX,IDC_FEEBOX};
//bool tabUp = 0, enterUp = 0;
//int box = 0;
bool ReadFile();
void WriteFile();
long getSum();
void getPercent();
void drawPie(HDC hdc,int X, int Y, int R, float start, float angle, Color color);   // hướng 12h start =0;