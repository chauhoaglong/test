#pragma once
#include <Windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <fstream>
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

class SHAPE
{
public:
	static SHAPE* create(int type, bool isShift);
	static SHAPE* create(int type);
	virtual void Set(int, int, int, int) = 0;
	virtual void Draw(HDC) = 0;
	virtual SHAPE* Clone() = 0;
	virtual int getType() = 0;
	virtual string toString() = 0;
	virtual void getData(ifstream &f) = 0;
};

class LINE :public SHAPE
{
private:
	int xStart;
	int yStart;
	int xEnd;
	int yEnd;
public:
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

class RECTANGLE:public SHAPE
{
private:
	int x;
	int y;
	int width;
	int height;
public:
	void Set(int startX, int startY, int endX, int endY)
	{
		x = min(startX,endX);
		y = min(startY,endY);
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

class ELLIPSE :public SHAPE
{
private:
	int x;
	int y;
	int width;
	int height;
public:
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

class SQUARE :public SHAPE
{
private:
	int x;
	int y;
	int edge;
public:
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

class CIRCLE :public SHAPE
{
private:
	int x;
	int y;
	int diameter;
public:
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

class Factory
{
public:

	SHAPE* create(int type, bool isShift)
	{
		if (type == 1) return new LINE;
		if (type == 2)
		{
			if (isShift) return new SQUARE;
			else return new RECTANGLE;
		}
		if (type == 3)
		{
			if (isShift) return new CIRCLE;
			else return new ELLIPSE;
		}
		return NULL;
	}
};

SHAPE* SHAPE::create(int type, bool isShift)
{
	if (type == 1) return new LINE;
	if (type == 2)
	{
		if (isShift) return new SQUARE;
		else return new RECTANGLE;
	}
	if (type == 3)
	{
		if (isShift) return new CIRCLE;
		else return new ELLIPSE;
	}
	return NULL;
}

SHAPE* SHAPE::create(int type)
{
	if (type == 1) return new LINE;
	if (type == 2) return new RECTANGLE;
	if (type == 3) return new ELLIPSE;
	if (type == 4) return new SQUARE;
	if (type == 5) return new CIRCLE;
	return NULL;
}