#pragma once
#include "stdafx.h"
#include <tchar.h>
#include <Shellapi.h>
#include <shlobj.h>
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")
class Expense {
private:
	TCHAR *type;
	TCHAR *detail;
	TCHAR *fee;
public:
	Expense()
	{
		type = NULL;
		detail = NULL;
		fee = NULL;
	}
	~Expense()
	{
		if (!type) delete[]type;
		if (!detail) delete[]detail;
		if (!fee) delete[]fee;
	}
	TCHAR* getType()
	{
		return type;
	}
	TCHAR* getDetail()
	{
		return detail;
	}
	TCHAR* getFee()
	{
		return fee;
	}
	void set(TCHAR* t_type, int sizeType, TCHAR* t_detail, int sizeDetail,TCHAR* t_fee,int sizeFee)
	{
		type = new TCHAR[sizeType + 1];
		detail = new TCHAR[sizeDetail + 1];
		fee = new TCHAR[sizeFee + 1];

		swprintf(type, sizeType, L"%s", t_type);
		swprintf(detail, sizeDetail, L"%s", t_detail);
		swprintf(fee, sizeFee, L"%s", t_fee);

		type[sizeType] = NULL;
		detail[sizeDetail] = NULL;
		fee[sizeFee] = NULL;
	}
};