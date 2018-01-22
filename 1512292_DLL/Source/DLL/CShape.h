#pragma once
#include <Windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <fstream>
#pragma comment (lib,"Gdiplus.lib")
using namespace Gdiplus;
using namespace std;
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
