#pragma once

#include "resource.h"
#include "Header.h"
#include <vector>

using namespace std;

int drawStyle = 0;  //1-line, 2-rect, 3-elipse
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

