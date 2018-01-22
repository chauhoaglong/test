#pragma once
#include "stdafx.h"
#include "CNote.h"
#include "CTags.h"
#include <vector>

void WCHARto3int(WCHAR* str, int &date, int &mounth, int &year)
{
	std::vector<WCHAR*> list;
	int len = wcslen(str);
	WCHAR* tmp = new WCHAR[len + 1];
	wcscpy(tmp, str);
	tmp[len] = '\0';
	int head = 0;
	for (int i = 0; i <= len; i++)
		if (tmp[i] == '/' || tmp[i] == '\0')
		{
			tmp[i] = '\0';
			list.push_back(tmp + head);
			head = i + 1;
		}
	if (wcslen(list[0]) == 0) mounth = 0;
	else 	mounth = _wtoi(list[0]);
	if (wcslen(list[1]) == 0) date = 0;
	else	date = _wtoi(list[1]);
	if (wcslen(list[2]) == 0) year = 0;
	year = _wtoi(list[2]);
}

int compareDate(WCHAR* date1, WCHAR* date2)
{
	int d1, d2, m1, m2, y1, y2;
	WCHARto3int(date1, d1, m1, y1);
	WCHARto3int(date2, d2, m2, y2);

	if (y1 != y2) return (y1 - y2) / abs(y1 - y2);
	else if (m1 != m2) return (m1 - m2) / abs(m1 - m2);
	else if (d1 != d2) return (d1 - d2) / abs(d1 - d2);
	return 0;
}

class CListTags
{
private:
	std::vector<CTags*> list;
public:
	std::vector<CTags*> getList()
	{
		return list;
	}
	CTags* push(WCHAR* tag)
	{
		WCHAR* temp = _wcslwr(tag);
		list.push_back(new CTags(temp));
		return list[list.size() - 1];
	}

	CTags* search(WCHAR* tag)
	{
		WCHAR* temp = _wcslwr(tag);
		CTags* find = NULL;
		for (int i = 0; i < list.size(); i++)
			if (list[i]->isCheckTag(tag))
			{
				find = list[i];
				break;
			}
		return find;
	}

	int count()
	{
		return list.size();
	}

	CTags* at(int x)
	{
		return list.at(x);
	}

	void sort()
	{
		for (int i = 0; i < list.size() - 1; i++)
			for (int j = i + 1; j < list.size(); j++)
				if (list[i]->count() < list[j]->count())
				{
					CTags* tmp = list[i];
					list[i] = list[j];
					list[j] = tmp;
				}
	}

	int size()
	{
		return list.size();
	}


};

class CListNote
{
private:
	std::vector<CNote*> list;
public:
	void push(CNote* note)
	{
		list.push_back(note);
	}

	int size()
	{
		return list.size();
	}

	CNote* at(int i)
	{
		return list.at(i);
	}

	void Sort()
	{
		for (int i = 0; i < list.size() - 1; i++)
			for (int j = i + 1; j < list.size(); j++)
				if (compareDate(list[i]->getDate(), list[j]->getDate()) < 0)
				{
					CNote* tmp = list[i];
					list[i] = list[j];
					list[j] = tmp;
				}
	}

	std::vector<CNote*> get()
	{
		return list;
	}
};