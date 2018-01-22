// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the DLL_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// DLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif


#pragma once
#include <Windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <fstream>
#include "CShape.h"
#pragma comment (lib,"Gdiplus.lib")
using namespace Gdiplus;
using namespace std;
#define lineWidth 2
#define lineColor Color(255, 0, 0, 0)
#define BUFFER_SIZE 260

string ITOA(int x)
{
	if (x)
	{
		string res = "";
		while (x)
		{
			res = (char)(x % 10 + 48) + res;
			x /= 10;
		}
		return res;
	}
	return "0";
}

class DLL_API LINE :public SHAPE
{
private:
	int xStart;
	int yStart;
	int xEnd;
	int yEnd;
public:
	LINE(int startX, int startY, int endX, int endY)
	{
		xStart = startX;
		yStart = startY;
		xEnd = endX;
		yEnd = endY;
	}
	LINE()
	{
	}

	void Set(int startX, int startY, int endX, int endY)
	{
		xStart = startX;
		yStart = startY;
		xEnd = endX;
		yEnd = endY;
	}
	void Draw(HDC hdc)
	{
		Graphics* graphics = new Graphics(hdc);
		Pen* pen = new Pen(lineColor, lineWidth);
		graphics->DrawLine(pen, xStart, yStart, xEnd, yEnd);
		delete pen;
		delete graphics;
	}
	LINE* Clone()
	{
		return new LINE;
	}
	int getType()
	{
		return 1;
	}
	string toString()
	{
		string res = "1 ";
		res = res + ITOA(xStart) + " ";
		res = res + ITOA(yStart) + " ";
		res = res + ITOA(xEnd) + " ";
		res = res + ITOA(yEnd) + "\n";
		return res;
	}
	void getData(ifstream &f)
	{
		f >> xStart >> yStart >> xEnd >> yEnd;
	}
};

class DLL_API RECTANGLE :public SHAPE
{
private:
	int x;
	int y;
	int width;
	int height;
public:
	RECTANGLE(int startX, int startY, int endX, int endY)
	{
		x = min(startX, endX);
		y = min(startY, endY);
		width = abs(startX - endX);
		height = abs(startY - endY);
	}
	RECTANGLE()
	{}
	void Set(int startX, int startY, int endX, int endY)
	{
		x = min(startX, endX);
		y = min(startY, endY);
		width = abs(startX - endX);
		height = abs(startY - endY);
	}
	void Draw(HDC hdc)
	{
		Graphics* graphics = new Graphics(hdc);
		Pen* pen = new Pen(lineColor, lineWidth);
		graphics->DrawRectangle(pen, x, y, width, height);
		delete pen;
		delete graphics;
	}
	RECTANGLE* Clone()
	{
		return new RECTANGLE;
	}
	int getType()
	{
		return 2;
	}
	string toString()
	{
		string res = "2 ";
		res = res + ITOA(x) + " ";
		res = res + ITOA(y) + " ";
		res = res + ITOA(height) + " ";
		res = res + ITOA(width) + "\n";
		return res;
	}
	void getData(ifstream &f)
	{
		f >> x >> y >> height >> width;
	}
};

class DLL_API ELLIPSE :public SHAPE
{
private:
	int x;
	int y;
	int width;
	int height;
public:
	ELLIPSE()
	{}
	ELLIPSE(int startX, int startY, int endX, int endY)
	{
		x = min(startX, endX);
		y = min(startY, endY);
		width = abs(startX - endX);
		height = abs(startY - endY);
	}

	void Set(int startX, int startY, int endX, int endY)
	{
		x = min(startX, endX);
		y = min(startY, endY);
		width = abs(startX - endX);
		height = abs(startY - endY);
	}
	void Draw(HDC hdc)
	{
		Graphics* graphics = new Graphics(hdc);
		Pen* pen = new Pen(lineColor, lineWidth);
		graphics->DrawEllipse(pen, x, y, width, height);
		delete pen;
		delete graphics;
	}
	ELLIPSE* Clone()
	{
		return new ELLIPSE;
	}
	int getType()
	{
		return 3;
	}
	string toString()
	{
		string res = "3 ";
		res = res + ITOA(x) + " ";
		res = res + ITOA(y) + " ";
		res = res + ITOA(height) + " ";
		res = res + ITOA(width) + "\n";
		return res;
	}
	void getData(ifstream &f)
	{
		f >> x >> y >> height >> width;
	}
};

class DLL_API SQUARE :public SHAPE
{
private:
	int x;
	int y;
	int edge;
public:
	SQUARE() {}
	SQUARE(int startX, int startY, int endX, int endY)
	{
		x = min(startX, endX);
		y = min(startY, endY);
		edge = max(abs(startX - endX), abs(startY - endY));
	}

	void Set(int startX, int startY, int endX, int endY)
	{
		x = min(startX, endX);
		y = min(startY, endY);
		edge = max(abs(startX - endX), abs(startY - endY));
	}
	void Draw(HDC hdc)
	{
		Graphics* graphics = new Graphics(hdc);
		Pen* pen = new Pen(lineColor, lineWidth);
		graphics->DrawRectangle(pen, x, y, edge, edge);
		delete pen;
		delete graphics;
	}
	SQUARE* Clone()
	{
		return new SQUARE;
	}
	int getType()
	{
		return 4;
	}
	string toString()
	{
		string res = "4 ";
		res = res + ITOA(x) + " ";
		res = res + ITOA(y) + " ";
		res = res + ITOA(edge) + "\n";
		return res;
	}
	void getData(ifstream &f)
	{
		f >> x >> y >> edge;
	}
};

class DLL_API CIRCLE :public SHAPE
{
private:
	int x;
	int y;
	int diameter;
public:
	CIRCLE()
	{}
	CIRCLE(int startX, int startY, int endX, int endY)
	{
		x = min(startX, endX);
		y = min(startY, endY);
		diameter = max(abs(startX - endX), abs(startY - endY));
	}
	void Set(int startX, int startY, int endX, int endY)
	{
		x = min(startX, endX);
		y = min(startY, endY);
		diameter = max(abs(startX - endX), abs(startY - endY));
	}
	void Draw(HDC hdc)
	{
		Graphics* graphics = new Graphics(hdc);
		Pen* pen = new Pen(lineColor, lineWidth);
		graphics->DrawEllipse(pen, x, y, diameter, diameter);
		delete pen;
		delete graphics;
	}
	CIRCLE* Clone()
	{
		return new CIRCLE;
	}
	int getType()
	{
		return 5;
	}
	string toString()
	{
		string res = "5 ";
		res = res + ITOA(x) + " ";
		res = res + ITOA(y) + " ";
		res = res + ITOA(diameter) + "\n";
		return res;
	}
	void getData(ifstream &f)
	{
		f >> x >> y >> diameter;
	}
};

extern "C" __declspec(dllexport) LINE* __cdecl CreateLine()
{
	return new LINE;
}

extern "C" __declspec(dllexport) RECTANGLE* __cdecl CreateRectangle()
{
	return new RECTANGLE;
}

extern "C" __declspec(dllexport) ELLIPSE* __cdecl CreateEllipse()
{
	return new ELLIPSE();
}

extern "C" __declspec(dllexport) SQUARE* __cdecl CreateSquare()
{
	return new SQUARE;
}

extern "C" __declspec(dllexport) CIRCLE* __cdecl CreateCircle()
{
	return new CIRCLE;
}
