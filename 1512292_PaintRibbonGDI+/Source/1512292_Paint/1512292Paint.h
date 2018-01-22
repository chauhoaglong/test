#pragma once

#include "resource.h"
#include "Header.h"
#include <vector>
#include <Commdlg.h>
#include <commctrl.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int drawStyle = 1;  //1-line, 2-rect, 3-elipse
bool isShift = 0;
bool isDrawing = 0;
int startX;
int startY;
int endX;
int endY;
int nowX;
int nowY;
RECT rect;
WCHAR buff[256];
HDC hdc;
SHAPE* temp;
vector<SHAPE*> list;
bool initSucces;
OPENFILENAME ofn;
void SaveFileW(HWND hWnd);
void writeFile(char* path);
void OpenFileW(HWND hWnd);
void readFile(char* path);