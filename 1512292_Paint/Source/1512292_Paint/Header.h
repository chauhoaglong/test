#pragma once
#include <Windows.h>
class SHAPE
{
public:
	static SHAPE* create(int type, bool isShift);
	virtual void Set(int, int, int, int) = 0;
	virtual void Draw(HDC) = 0;
	virtual SHAPE* Clone() = 0;
	virtual int getType() = 0;
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
		HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

		SelectObject(hdc, hPen);

		MoveToEx(hdc, xStart, yStart, NULL);
		LineTo(hdc, xEnd, yEnd);
	}
	LINE* Clone()
	{
		return new LINE;
	}
	int getType()
	{
		return 1;
	}
};

class RECTANGLE:public SHAPE
{
private:
	int xTopLeft;
	int yTopLeft;
	int xBotRight;
	int yBotRight;
public:
	void Set(int topLeftX, int topLeftY, int botRightX, int botRightY)
	{
		xTopLeft = topLeftX;
		yTopLeft = topLeftY;
		xBotRight = botRightX;
		yBotRight = botRightY;
	}
	void Draw(HDC hdc)
	{
		HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		SelectObject(hdc, hPen);
		Rectangle(hdc, xTopLeft, yTopLeft, xBotRight, yBotRight);
		DeleteObject(hPen);
	}
	RECTANGLE* Clone()
	{
		return new RECTANGLE;
	}
	int getType()
	{
		return 2;
	}
};

class ELLIPSE :public SHAPE
{
private:
	int xTopLeft;
	int yTopLeft;
	int xBotRight;
	int yBotRight;
public:
	void Set(int topLeftX, int topLeftY, int botRightX, int botRightY)
	{
		xTopLeft = topLeftX;
		yTopLeft = topLeftY;
		xBotRight = botRightX;
		yBotRight = botRightY;
	}
	void Draw(HDC hdc)
	{
		HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		SelectObject(hdc, hPen);
		Ellipse(hdc, xTopLeft, yTopLeft, xBotRight, yBotRight);
		DeleteObject(hPen);
	}
	ELLIPSE* Clone()
	{
		return new ELLIPSE;
	}
	int getType()
	{
		return 3;
	}
};

class SQUARE :public SHAPE
{
private:
	int x;
	int y;
	int edge;
public:
	void Set(int topLeftX, int topLeftY, int botRightX, int botRightY)
	{
		x = min(topLeftX, botRightX);
		y = min(topLeftY, botRightY);
		edge = max(abs(topLeftX - botRightX), abs(topLeftY - botRightY));
	}
	void Draw(HDC hdc)
	{
		HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		SelectObject(hdc, hPen);
		Rectangle(hdc, x, y, x + edge, y + edge);
		DeleteObject(hPen);
	}
	SQUARE* Clone()
	{
		return new SQUARE;
	}
	int getType()
	{
		return 4;
	}
};

class CIRCLE :public SHAPE
{
private:
	int x;
	int y;
	int edge;
public:
	void Set(int topLeftX, int topLeftY, int botRightX, int botRightY)
	{
		x = min(topLeftX, botRightX);
		y = min(topLeftY, botRightY);
		edge = max(abs(topLeftX - botRightX), abs(topLeftY - botRightY));
	}
	void Draw(HDC hdc)
	{
		HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		SelectObject(hdc, hPen);
		Ellipse(hdc, x, y, x + edge, y + edge);
		DeleteObject(hPen);
	}
	CIRCLE* Clone()
	{
		return new CIRCLE;
	}
	int getType()
	{
		return 5;
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