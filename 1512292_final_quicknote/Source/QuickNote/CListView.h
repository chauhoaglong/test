#pragma once
#include "stdafx.h"
#include <shlobj.h>
#include <shlwapi.h>
#include "CTags.h"
#include "CNote.h"
#include <wchar.h>
#include <vector>
#pragma comment(lib, "shlwapi.lib")

WCHAR* toWCHAR(int x)
{
	char y[10];
	_itoa(x, y, 10);
	WCHAR *z = new WCHAR[10];
	mbstowcs(z, y, 10);
	return z;
}

WCHAR* to50(WCHAR* str)
{
	WCHAR* res = new WCHAR[51];
	for (int i = 0; i < 51; i++)
		res[i] = str[i];
	res[50] = '\0';
	return res;
}

class CListView
{
public:
	HINSTANCE	m_hInst;
	HWND		m_hParent;
	HWND		m_hListView;

public:
	CListView()
	{
		m_hInst = NULL;
		m_hParent = NULL;
		m_hListView = NULL;
	}

	~CListView()
	{
		DestroyWindow(m_hListView);
	}

	void Create(HWND hWnd, HINSTANCE hInst, int iWidth, int iHeight, int ix, int iy)
	{
		InitCommonControls();

		m_hInst = hInst;
		m_hParent = hWnd;
		m_hListView = CreateWindowEx(WS_EX_CLIENTEDGE, WC_LISTVIEW, _T("List View"),
			WS_CHILD | WS_VISIBLE | WS_TABSTOP | LVS_ICON | LVS_REPORT | LVS_EDITLABELS
			| LVS_SHOWSELALWAYS | LVS_EX_BORDERSELECT | WS_VSCROLL,
			ix, iy, iWidth, iHeight, hWnd, (HMENU)hWnd, hInst, NULL);

	}

	void InitListTagsCols()
	{
		LVCOLUMN lvCol_Tag;
		lvCol_Tag.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
		lvCol_Tag.fmt = LVCFMT_LEFT;
		lvCol_Tag.cx = 85;
		lvCol_Tag.pszText = _T("Tags");
		ListView_InsertColumn(m_hListView, 0, &lvCol_Tag);

		lvCol_Tag.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
		lvCol_Tag.fmt = LVCFMT_RIGHT;
		lvCol_Tag.cx = 50;
		lvCol_Tag.pszText = _T("Times");
		ListView_InsertColumn(m_hListView, 1, &lvCol_Tag);
	}

	void InitListNotesCols()
	{
		LVCOLUMN lvCol_Note;
		lvCol_Note.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
		lvCol_Note.fmt = LVCFMT_LEFT;
		lvCol_Note.cx = 410;
		lvCol_Note.pszText = _T("Notes");
		ListView_InsertColumn(m_hListView, 0, &lvCol_Note);
	}

	void InitListTimeNote()
	{
		LVCOLUMN lvCol_Tag;
		lvCol_Tag.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
		lvCol_Tag.fmt = LVCFMT_LEFT;
		lvCol_Tag.cx = 280;
		lvCol_Tag.pszText = _T("Note");
		ListView_InsertColumn(m_hListView, 0, &lvCol_Tag);

		lvCol_Tag.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
		lvCol_Tag.fmt = LVCFMT_RIGHT;
		lvCol_Tag.cx = 80;
		lvCol_Tag.pszText = _T("Date");
		ListView_InsertColumn(m_hListView, 1, &lvCol_Tag);
	}

	void LoadListTags(std::vector <CTags*> List)
	{
		DeleteAll();
		LV_ITEM lv;
		for (int i = 0; i < List.size(); i++)
		{
			lv.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
			lv.iItem = i;
			lv.iImage = 0;
			lv.iSubItem = 0;
			lv.pszText = List.at(i)->getTag();
			lv.lParam = (LPARAM)0;
			ListView_InsertItem(m_hListView, &lv);

			lv.mask = LVIF_TEXT;
			lv.iSubItem = 1;
			lv.pszText = toWCHAR(List.at(i)->count());
			ListView_SetItem(m_hListView, &lv);
		}
	}

	void LoadListTime(std::vector <CNote*> List)
	{
		DeleteAll();
		LV_ITEM lv;
		for (int i = 0; i < List.size(); i++)
		{
			lv.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
			lv.iItem = i;
			lv.iImage = 0;
			lv.iSubItem = 0;
			lv.pszText = to50(List.at(i)->getNote());
			lv.lParam = (LPARAM)0;
			ListView_InsertItem(m_hListView, &lv);

			lv.mask = LVIF_TEXT;
			lv.iSubItem = 1;
			lv.pszText = List.at(i)->getDate();
			ListView_SetItem(m_hListView, &lv);
		}
	}

	void LoadListNotes(std::vector <CNote*> ListA)
	{
		DeleteAll();
		LV_ITEM lv;
		for (int i = 0; i < ListA.size(); i++)
		{
			lv.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM | LVCFMT_WRAP;
			lv.iItem = i;
			lv.iSubItem = 0;
			lv.pszText = to50(ListA.at(i)->getNote());
			ListView_InsertItem(m_hListView, &lv);
		}
	}

	HWND getHandle()
	{
		return m_hListView;
	}

	LPWSTR getItem(int iItem)
	{
		LVITEM lv;
		lv.mask = LVIF_PARAM;
		lv.iItem = iItem;
		lv.iSubItem = 0;
		ListView_GetItem(m_hListView, &lv);
		return lv.pszText;
	}

	void DeleteAll()
	{
		ListView_DeleteAllItems(m_hListView);
	}
};
