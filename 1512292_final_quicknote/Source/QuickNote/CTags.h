#pragma once
#include "stdafx.h"
#include <vector>

class CNote;

class CTags
{
private:
	WCHAR* str_tag;
	std::vector<CNote*> listNote;
public:


	CTags(WCHAR* str)
	{
		str_tag = new WCHAR[wcslen(str) + 1];
		lstrcpy(str_tag, str);
		str_tag[wcslen(str)] = NULL;
		listNote.clear();
	}

	~CTags()
	{
		if (!str_tag)
			delete str_tag;
	}

	WCHAR* getTag()
	{
		return str_tag;
	}

	void setTag(int siz, WCHAR* str)
	{
		str_tag = new WCHAR[wcslen(str) + 1];
		lstrcpy(str_tag, str);
		str_tag[wcslen(str)] = NULL;
	}

	bool isCheckTag(WCHAR* had)
	{
		return (lstrcmp(had, str_tag) == 0);
	}

	void pushNote(CNote* note)
	{
		listNote.push_back(note);
	}

	std::vector<CNote*> getListNote()
	{
		return listNote;
	}

	int count()
	{
		return listNote.size();
	}

	int getSize()
	{
		return wcslen(str_tag);
	}
};
