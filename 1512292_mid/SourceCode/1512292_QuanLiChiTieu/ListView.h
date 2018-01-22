#pragma once
#include "stdafx.h"
#include <tchar.h>
#include <Shellapi.h>
#include <shlobj.h>
#include <shlwapi.h>
#include "Expense.h"
#include <iostream>
#include <vector>
using namespace std;
#pragma comment(lib, "shlwapi.lib")
class ListView {
public:
	HINSTANCE	m_hInst;
	HWND		m_hParent;
	HWND		m_hListView;
public:
public:
	ListView() 
	{
		m_hInst = NULL;
		m_hParent = NULL;
		m_hListView = NULL;
	}
	~ListView() 
	{
		DestroyWindow(m_hListView);
	}

	void Create(HWND hWnd, HINSTANCE hInst, int iWidth, int iHeight, int ix, int iy) 
	{
		//InitCommonControls();

		m_hInst = hInst;
		m_hParent = hWnd;
		m_hListView = CreateWindowEx(WS_EX_CLIENTEDGE, WC_LISTVIEW, _T("List View"),
			WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_TABSTOP | LVS_ICON | LVS_REPORT | LVS_EDITLABELS | LVS_SHOWSELALWAYS,
			ix, iy, iWidth, iHeight, hWnd, (HMENU)hWnd, hInst, NULL);
	}

	void Init3Cols() 
	{
		//Name
		LVCOLUMN lvCol_Name;
		lvCol_Name.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
		lvCol_Name.fmt = LVCFMT_LEFT;
		lvCol_Name.cx = 100;
		lvCol_Name.pszText = _T("Loại");
		ListView_InsertColumn(m_hListView, 0, &lvCol_Name);
		//TYpe
		LVCOLUMN lvCol_Type;
		lvCol_Type.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
		lvCol_Type.fmt = LVCFMT_LEFT | LVCF_WIDTH;
		lvCol_Type.cx = 150;
		lvCol_Type.pszText = _T("Chi tiết");
		ListView_InsertColumn(m_hListView, 1, &lvCol_Type);
		//Size
		LVCOLUMN lvCol_Size;
		lvCol_Size.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH,
		lvCol_Size.fmt = LVCFMT_RIGHT;
		lvCol_Size.cx = 130;
		lvCol_Size.pszText = _T("Hao phí");
		ListView_InsertColumn(m_hListView, 2, &lvCol_Size);
	}

	void LoadListView(vector <Expense> List) 
	{
		DeleteAll();
		LV_ITEM lv;
		for (int i = 0; i < List.size(); i++) {
			lv.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
			lv.iItem = i;
			lv.iImage = 0;
			lv.lParam = (LPARAM)0;

			lv.iSubItem = 0;
			lv.pszText = List[i].getType();
			ListView_InsertItem(m_hListView, &lv);

			lv.mask = LVIF_TEXT;
			lv.iSubItem = 1;
			lv.pszText = List[i].getDetail();
			ListView_SetItem(m_hListView, &lv);

			lv.iSubItem = 2;
			lv.pszText = List[i].getFee();
			ListView_SetItem(m_hListView, &lv);
		}
	}

	void DeleteAll()
	{
		ListView_DeleteAllItems(m_hListView);
	}
};