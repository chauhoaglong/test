#pragma once
#include "stdafx.h"
#include <vector>
#include <tchar.h>
#include "CTags.h"
class CTags;

class CNote
{
private:
	WCHAR* strNote;
	WCHAR* strDate;
	std::vector<CTags*> listTags;

public:
	CNote(WCHAR* note, WCHAR* date)
	{
		strNote = new WCHAR[wcslen(note) + 1];
		lstrcpy(strNote, note);
		strNote[wcslen(note)] = NULL;
		strDate = new WCHAR[wcslen(date) + 1];
		lstrcpy(strDate, date);
		strDate[wcslen(date)] = NULL;
		listTags.clear();
	}

	~CNote()
	{
		if (!strNote) delete strNote;
		if (!strDate) delete strDate;
	}

	WCHAR* getNote()
	{
		return strNote;
	}

	WCHAR* getDate() {
		return strDate;
	}

	void setNote(int len, WCHAR* note)
	{
		strNote = new WCHAR[wcslen(note) + 1];
		lstrcpy(strNote, note);
		strNote[wcslen(note)] = NULL;
	}

	std::vector<CTags*> getListTags()
	{
		return listTags;
	}

	void setListTags(std::vector<CTags*> list)
	{
		listTags = list;
	}

	WCHAR* getTagsBuff()
	{
		WCHAR* buff = new WCHAR[512];
		memset(buff, 0, 512);
		for (int i = 0; i < listTags.size(); i++)
		{
			wcscat(buff, listTags.at(i)->getTag());
			if (i != (listTags.size() - 1))
				wcscat(buff, L", ");
		}
		return buff;
	}
};