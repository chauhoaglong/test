// QuickNote.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "QuickNote.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_QUICKNOTE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_QUICKNOTE));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_QUICKNOTE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_QUICKNOTE);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (flagHOOK&&!ADDNOTE)
	{
		ADDNOTE = 1;
		flagHOOK = 0;
		LoadLibrary(L"Riched20.dll");
		DialogBox(hInst, MAKEINTRESOURCE(IDD_QUICKNOTE_DIALOG), hWnd, AddNote);
		ADDNOTE = 0;
	}

	ShowWindow(hWnd, SW_HIDE);
    switch (message)
    {
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
	case WMAPP_NOTIFYCALLBACK:
	{
		switch (LOWORD(lParam))
		{
		case WM_CONTEXTMENU:
		{
			POINT const pt = { LOWORD(wParam), HIWORD(wParam) };
			ShowContextMenu(hWnd, pt);
		}
		break;
		}
	}
	break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

INT_PTR CALLBACK AddNote(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	WCHAR *tags_buffer = new WCHAR[512];
	WCHAR *note_buffer = new WCHAR[512];
	WCHAR *date_buffer = new WCHAR[20];
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		SetWindowText(hDlg, L"Add Note");
		LOGFONT lf;

		GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
		HFONT hFont = CreateFont(lf.lfHeight, lf.lfWidth,
			lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
			lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
			lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
			lf.lfPitchAndFamily, TEXT("Segoe UI"));

		gbANnote = CreateWindowEx(0, L"BUTTON", L"Note", BS_GROUPBOX | WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON
			, 30, 100, 410, 145, hDlg, NULL, hInst, NULL);
		SetWindowFont(gbANnote, hFont, 0);

		gbANtag = CreateWindowEx(0, L"BUTTON", L"Tag", BS_GROUPBOX | WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON
			, 30, 20, 410, 75, hDlg, NULL, hInst, NULL);
		SetWindowFont(gbANtag, hFont, 0);

		edbANtag = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER |
			ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | WS_TABSTOP
			, 50, 40, 370, 40, hDlg, (HMENU)IDS_RETAGS, hInst, NULL);
		SetWindowFont(edbANtag, hFont, 0);

		edbANnote = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER |
			ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | WS_TABSTOP
			, 50, 125, 370, 100, hDlg, (HMENU)IDC_RENOTE, hInst, NULL);
		SetWindowFont(edbANnote, hFont, 0);

		btANsave = CreateWindowEx(0, WC_BUTTON, L"Save", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
			290, 255, 80, 20, hDlg, (HMENU)ID_SAVE, NULL, NULL);
		SetWindowFont(btANsave, hFont, 0);

		btANcancel = CreateWindowEx(0, WC_BUTTON, L"Cancel", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
			380, 255, 80, 20, hDlg, (HMENU)IDCANCEL, NULL, NULL);
		SetWindowFont(btANcancel, hFont, 0);

		HICON hIcon = (HICON)LoadImage(hInst, MAKEINTRESOURCE(IDI_QUICKNOTE), IMAGE_ICON,
			GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), 0);
		if (hIcon) SendMessage(hDlg, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
	}
	return TRUE;
	break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		case ID_SAVE:
			GetDlgItemText(hDlg, IDS_RETAGS, tags_buffer, 512);
			GetDlgItemText(hDlg, IDC_RENOTE, note_buffer, 512);
			GetDlgItemText(hDlg, IDC_DATETIMEPICKER1, date_buffer, 20);

			int lenNote = GetWindowTextLength(edbANnote);
			int lenTag = GetWindowTextLength(edbANtag);

			if (checkTagsBuff(tags_buffer) && lenNote && lenTag)
			{
				add(tags_buffer, note_buffer, date_buffer);
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
			else MessageBox(0, L"Tag's syntax error!\nPlease re-enter!", L"Error!", 0);
			if (!tags_buffer) delete tags_buffer;
			if (!note_buffer) delete note_buffer;
		}
	}
	break;
	}
	
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK ViewStatitistics(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		SetWindowTextW(hDlg, L"View Statitistics");
		LOGFONT lf;

		GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
		HFONT hFont = CreateFont(lf.lfHeight*1.1, lf.lfWidth*1.1,
			lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
			lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
			lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
			lf.lfPitchAndFamily, TEXT("Segoe UI"));

		HICON hIcon = (HICON)LoadImage(hInst, MAKEINTRESOURCE(IDI_QUICKNOTE),
			IMAGE_ICON, GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), 0);
		if (hIcon)  SendMessage(hDlg, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);

		txtVShead = CreateWindowEx(0, L"STATIC", L"EXPLICATION",
			WS_CHILD | WS_VISIBLE, 590, 30, 100, 30,
			hDlg, NULL, NULL, NULL);
		SetWindowFont(txtVShead, hFont, 0);
		ShowWindow(txtVShead, SW_HIDE);

		txtVSno = CreateWindowEx(0, L"STATIC", L"NO NOTE IS SAVED",
			WS_CHILD | WS_VISIBLE, 550, 220, 200, 30,
			hDlg, NULL, NULL, NULL);
		SetWindowFont(txtVSno, hFont, 0);
		ShowWindow(txtVSno, SW_HIDE);

		txtVSsum = CreateWindowEx(0, L"STATIC", L"",
			WS_CHILD | WS_VISIBLE, 225, 220, 60, 30,
			hDlg, NULL, NULL, NULL);
		SetWindowFont(txtVSsum, hFont, 0);

		for (int i = 0; i < 16; i++)
		{
			txtVStag[i] = CreateWindowEx(0, L"STATIC", L"",
				WS_CHILD | WS_VISIBLE, x[i % 2], y[i / 2], 80, 30,
				hDlg, NULL, NULL, NULL);
			txtVSper[i] = CreateWindowEx(0, L"STATIC", L"",
				WS_CHILD | WS_VISIBLE, x[i % 2] + 50, y[i / 2], 30, 30,
				hDlg, NULL, NULL, NULL);
			SetWindowFont(txtVStag[i], hFont, 0);
			SetWindowFont(txtVSper[i], hFont, 0);
			ShowWindow(txtVStag[i], SW_HIDE);
			ShowWindow(txtVSper[i], SW_HIDE);
		}
	}

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC            hdc;
		hdc = BeginPaint(hDlg, &ps);

		if (getSumNote())
		{
			listTags.sort();
			getPercent();
			ShowWindow(txtVShead, SW_SHOW); 
			ShowWindow(txtVSno, SW_HIDE);
			float angle = 0;
			int i = 0;
			for (; i < listTags.size() && i < 15; i++)
			{
				drawPie(hdc, xp[i % 2], yp[i / 2], 70, -90, 30, color[i]);
				drawPie(hdc, 70, 50, 350, angle, 3.6*percent[i], color[i]);
				angle += 3.6*percent[i];
				ShowWindow(txtVStag[i], SW_SHOW);
				ShowWindow(txtVSper[i], SW_SHOW);
				SetWindowTextW(txtVStag[i], listTags.at(i)->getTag());
				WCHAR tmp[10];
				wsprintf(tmp, L"%d%%", percent[i]);
				SetWindowTextW(txtVSper[i], tmp);
			}

			if (i == 15)
			{
				drawPie(hdc, xp[15 % 2], yp[15 / 2], 70, -90, 30, color[15]);
				drawPie(hdc, 70, 50, 350, angle, 360 - angle, color[15]);
				ShowWindow(txtVStag[15], SW_SHOW);
				ShowWindow(txtVSper[15], SW_SHOW);
				if (listTags.size() > 16)
					SetWindowTextW(txtVStag[15], L"Other");
				else SetWindowTextW(txtVStag[15], listNotes.at(15)->getNote());
				int per = 0;
				for (int i = 15; i < listTags.size(); i++)
					per += percent[i];
				WCHAR tmp[10];
				wsprintf(tmp, L"%d%%", per);
				SetWindowTextW(txtVSper[15], tmp);
			}
		}
		else
		{
			drawPie(hdc, 70, 50, 350, 0, 360, Color(255, 255, 255));
			ShowWindow(txtVSno, SW_SHOW);
		}
		Graphics *gp = new Graphics(hdc);
		Pen *p = new Pen(Color(0, 0, 0), 1);

		gp->DrawRectangle(p, 480, 20, 300, 400);
		gp->DrawRectangle(p, 20, 20, 450, 400);

		delete p;
		delete gp;
		drawPie(hdc, 190, 170, 110, 0, 360, Color(240, 240, 240));
		WCHAR txt[10];
		swprintf_s(txt, L"SUM = %d", getSumNote());
		SetWindowTextW(txtVSsum, txt);
		EndPaint(hDlg, &ps);
	}
	break;
	case WM_DESTROY:
		EndDialog(hDlg, LOWORD(wParam));
		return (INT_PTR)TRUE;
	break;

	default:
		return DefWindowProc(hDlg, message, wParam, lParam);
	}

	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK TimeNote(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);

	switch (message)
	{
		HANDLE_MSG(hDlg, WM_NOTIFY, OnNotifiTimeNote);
	case WM_INITDIALOG:
	{
		SetWindowTextW(hDlg, L"Time Note");

		LOGFONT lf;

		GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
		HFONT hFont = CreateFont(lf.lfHeight, lf.lfWidth,
			lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
			lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
			lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
			lf.lfPitchAndFamily, TEXT("Segoe UI"));

		HICON hIcon = (HICON)LoadImage(hInst, MAKEINTRESOURCE(IDI_QUICKNOTE),
			IMAGE_ICON, GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), 0);
		if (hIcon)  SendMessage(hDlg, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);

		lvTime = new CListView;
		lvTime->Create(hDlg, hInst, 400, 300, 30, 30);
		lvTime->InitListTimeNote();
		if (listNotes.size())
		{
			listNotes.Sort();
			lvTime->LoadListTime(listNotes.get());
		}

		edbTNnote = CreateWindowEx(0, L"EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_BORDER | ES_LEFT |
			ES_MULTILINE | ES_AUTOVSCROLL | WS_TABSTOP,
			30, 400, 425, 60, hDlg, (HMENU)IDD_VIEWNOTE, NULL, NULL);
		SetWindowFont(edbTNnote, hFont, 0);

		txtTNcaps = CreateWindowEx(0, L"STATIC", L"Content of note: ", WS_CHILD | WS_VISIBLE,
			30, 370, 100, 30, hDlg, NULL, NULL, NULL);
		SetWindowFont(txtTNcaps, hFont, 0);

		txtTNcaps = CreateWindowEx(0, L"STATIC", L"Today: ", WS_CHILD | WS_VISIBLE,
			30, 340, 60, 30, hDlg, NULL, NULL, NULL);
		SetWindowFont(txtTNcaps, hFont, 0);

		txtTNtoday = CreateWindowEx(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE,
			90, 340, 100, 30, hDlg, NULL, NULL, NULL);
		SetWindowFont(txtTNtoday, hFont, 0);
		SetWindowTextW(txtTNtoday, getToday());

		txtTNcaps = CreateWindowEx(0, L"STATIC", L"Date: ", WS_CHILD | WS_VISIBLE,
			300, 370, 50, 30, hDlg, NULL, NULL, NULL);
		SetWindowFont(txtTNcaps, hFont, 0);

		txtTNdate = CreateWindowEx(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE,
			350, 370, 100, 30, hDlg, NULL, NULL, NULL);
		SetWindowFont(txtTNdate, hFont, 0);
	}
		break;
	case WM_DESTROY:
	{
		EndDialog(hDlg, LOWORD(wParam));
		return (INT_PTR)TRUE;
	}
		break;

	default:
		return DefWindowProc(hDlg, message, wParam, lParam);
	}

	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK ViewNote(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);

	switch (message)
	{
		HANDLE_MSG(hDlg, WM_NOTIFY, OnNotifiViewNote);
		HANDLE_MSG(hDlg, WM_COMMAND, OnCommandViewNote);
	case WM_INITDIALOG:
	{
		SetWindowText(hDlg, L"View Note");

		HICON hIcon = (HICON)LoadImage(hInst, MAKEINTRESOURCE(IDI_QUICKNOTE),
			IMAGE_ICON, GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), 0);
		if (hIcon)  SendMessage(hDlg, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);

		LOGFONT lf;

		GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
		HFONT hFont = CreateFont(lf.lfHeight, lf.lfWidth, lf.lfEscapement, lf.lfOrientation, lf.lfWeight, lf.lfItalic,
			lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet, lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
			lf.lfPitchAndFamily, TEXT("Segoe UI"));

		lvTag = new CListView;
		lvTag->Create(hDlg, hInst, 160, 220, 30, 30);
		lvTag->DeleteAll();
		lvTag->InitListTagsCols();

		lvNote = new CListView;
		lvNote->Create(hDlg, hInst, 450, 220, 190, 30);
		lvNote->DeleteAll();
		lvNote->InitListNotesCols();

		lvTag->LoadListTags(listTags.getList());

		edbVNnote = CreateWindowEx(0, L"EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_BORDER | ES_LEFT |
			ES_MULTILINE | ES_AUTOVSCROLL | WS_TABSTOP,
			30, 300, 625, 60, hDlg, (HMENU)IDD_VIEWNOTE, NULL, NULL);
		SetWindowFont(edbVNnote, hFont, 0);

		txtVNcaps = CreateWindowEx(0, L"STATIC", L"Content of note: ", WS_CHILD | WS_VISIBLE,
			30, 270, 100, 30, hDlg, NULL, NULL, NULL);
		SetWindowFont(txtVNcaps, hFont, 0);

		txtVNcaps = CreateWindowEx(0, L"STATIC", L"Date: ", WS_CHILD | WS_VISIBLE,
			500, 270, 50, 30, hDlg, NULL, NULL, NULL);
		SetWindowFont(txtVNcaps, hFont, 0);

		txtVNdate = CreateWindowEx(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE,
			550, 270, 100, 30, hDlg, NULL, NULL, NULL);
		SetWindowFont(txtVNdate, hFont, 0);

		btVNsave = CreateWindowEx(0, WC_BUTTON, L"Save", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
			550, 370, 80, 20, hDlg, (HMENU)IDC_SAVECHANGE, NULL, NULL);
		SetWindowFont(btVNsave, hFont, 0);
	}
		break;
	case WM_DESTROY:
	{
		EndDialog(hDlg, LOWORD(wParam));
		return (INT_PTR)TRUE;
	}
	break;
	default:
		return DefWindowProc(hDlg, message, wParam, lParam);
	}

	return (INT_PTR)FALSE;
}

BOOL AddNotificationIcon(HWND hwnd)
{
	NOTIFYICONDATA nid = { sizeof(nid) };
	nid.hWnd = hwnd;
	nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE | NIF_SHOWTIP | NIF_GUID;

	CoCreateGuid(&myGUID);
	nid.guidItem = myGUID;

	nid.uCallbackMessage = WMAPP_NOTIFYCALLBACK;
	LoadIconMetric(hInst, MAKEINTRESOURCE(IDI_QUICKNOTE), LIM_SMALL, &nid.hIcon);
	LoadString(hInst, IDS_TOOLTIP, nid.szTip, ARRAYSIZE(nid.szTip));
	Shell_NotifyIcon(NIM_ADD, &nid);

	nid.uVersion = NOTIFYICON_VERSION_4;
	return Shell_NotifyIcon(NIM_SETVERSION, &nid);
}

BOOL DeleteNotificationIcon()
{
	NOTIFYICONDATA nid = { sizeof(nid) };
	nid.uFlags = NIF_GUID;
	nid.guidItem = myGUID;
	return Shell_NotifyIcon(NIM_DELETE, &nid);
}

void ShowContextMenu(HWND hwnd, POINT pt)
{
	HMENU hMenu = LoadMenu(hInst, MAKEINTRESOURCE(IDC_MENUQN));
	if (hMenu)
	{
		HMENU hSubMenu = GetSubMenu(hMenu, 0);
		if (hSubMenu)
		{
			SetForegroundWindow(hwnd);

			UINT uFlags = TPM_RIGHTBUTTON;
			if (GetSystemMetrics(SM_MENUDROPALIGNMENT) != 0)
				uFlags |= TPM_RIGHTALIGN;
			else
				uFlags |= TPM_LEFTALIGN;
			TrackPopupMenuEx(hSubMenu, uFlags, pt.x, pt.y, hwnd, NULL);
		}
		DestroyMenu(hMenu);
	}
}

BOOL OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
	INITCOMMONCONTROLSEX icc;
	icc.dwSize = sizeof(icc);
	icc.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&icc);

	ReadFile();
	InstallQuickNoteHook(hWnd);
	AddNotificationIcon(hWnd);
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	return true;
}

LRESULT OnNotifiViewNote(HWND hWnd, int id, NMHDR *pnm)
{
	int Index;
	switch (pnm->code)
	{
	case TVN_ITEMEXPANDING:
		break;

	case TVN_SELCHANGED:
		lvTag->DeleteAll();
		lvTag->LoadListTags(listTags.getList());
		break;

	case NM_CLICK:
		if (pnm->hwndFrom == lvTag->getHandle())
		{
			Index = ListView_GetSelectionMark(lvTag->getHandle());
			if (Index == -1) break;
			tagsNow = listTags.getList().at(Index);
			lvNote->LoadListNotes(tagsNow->getListNote());
		}
		if (pnm->hwndFrom == lvNote->getHandle())
		{
			Index = ListView_GetSelectionMark(lvNote->getHandle());
			if (Index == -1) break;
			noteNow = tagsNow->getListNote().at(Index);
			SetWindowText(edbVNnote, noteNow->getNote());
			SetWindowText(txtVNdate, noteNow->getDate());
		}
		break;
	}
	return 0;
}

LRESULT OnNotifiTimeNote(HWND hWnd, int id, NMHDR *pnm)
{
	int Index;
	switch (pnm->code)
	{
	case TVN_ITEMEXPANDING:
		break;

	case TVN_SELCHANGED:
		lvTime->DeleteAll();
		listNotes.Sort();
		lvTime->LoadListTime(listNotes.get());
		break;

	case NM_CLICK:
		if (pnm->hwndFrom == lvTime->getHandle())
		{
			Index = ListView_GetSelectionMark(lvTime->getHandle());
			if (Index == -1) break;
			noteNow = listNotes.at(Index);
			SetWindowTextW(edbTNnote, noteNow->getNote());
			SetWindowTextW(txtTNdate, noteNow->getDate());
		}
		break;
	}
	return 0;
}

void OnCommand(HWND hWnd, int ID, HWND hwndCtl, UINT codeNotify)
{
	switch (ID)
	{
	case ID__ADDNOTE:
		if (!ADDNOTE)
		{
			VIEWNOTES = 0;
			VIEWSTATITISTICS = 0;
			LoadLibrary(L"Riched20.dll");
			DialogBox(hInst, MAKEINTRESOURCE(IDD_QUICKNOTE_DIALOG), hWnd, AddNote);
		}
		break;
	case ID__VIEWSTATITISTICS:
		if (!VIEWSTATITISTICS)
		{
			VIEWNOTES = 0;
			ADDNOTE = 0;
			LoadLibrary(L"Riched20.dll");
			DialogBox(hInst, MAKEINTRESOURCE(IDD_VIEWSTATITISTICS), hWnd, ViewStatitistics);
		}
		break;
	case ID__VIEWNOTES:
		if (!VIEWNOTES)
		{
			ADDNOTE = 0;
			VIEWSTATITISTICS = 0;
			LoadLibrary(L"Riched20.dll");
			DialogBox(hInst, MAKEINTRESOURCE(IDD_VIEWNOTE), hWnd, ViewNote);
		}
		break;
	case ID__TIMENOTE:
		if (!TIMENOTE)
		{
			ADDNOTE = 0;
			VIEWSTATITISTICS = 0;
			LoadLibrary(L"Riched20.dll");
			DialogBox(hInst, MAKEINTRESOURCE(IDD_TIMENOTE), hWnd, TimeNote);
		}
		break;
	case ID_EXIT:
		int res = MessageBox(0, L"Do you want to exit?", L"Notification!", MB_OKCANCEL);
		if (res == IDOK) SendMessage(hWnd, WM_DESTROY, 0, 0);
		break;
	}
}

void OnCommandViewNote(HWND hWnd, int ID, HWND hwndCtl, UINT codeNotify)
{
	switch (ID)
	{
	case IDC_SAVECHANGE:
		len = GetWindowTextLength(edbVNnote);
		GetWindowText(edbVNnote, buff, len);
		buff[len] = '\0';
		noteNow->setNote(len + 1, buff);

		InvalidateRect(hWnd, NULL, FALSE);
		lvTag->LoadListTags(listTags.getList());
		lvNote->LoadListNotes(tagsNow->getListNote());
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	}
}

void OnDestroy(HWND hWnd)
{
	RemoveQuickNoteHook(hWnd);
	DestroyWindow(hWnd);
	DeleteNotificationIcon();
	GdiplusShutdown(gdiplusToken);
	WriteFile();
	PostQuitMessage(0);
}

bool checkTagsBuff(WCHAR* str)
{
	for (int i = 0; i < lstrlen(str); i++)
	{
		if (str[i] == ','&& str[i + 1] != ' ') return 0;
	}
	return 1;
}

std::vector<WCHAR*> stringCat(WCHAR* str)
{
	std::vector<WCHAR*> res;
	int head = 0;
	int len = wcslen(str);
	for (int i = 0; i <= len; i++)
	{
		if (str[i] == ',' || str[i] == '\0')
		{
			res.push_back(str + head);
			str[i] = '\0';
			head = i + 2;
		}
	}
	return res;
}

void add(WCHAR* tags, WCHAR* note, WCHAR* date)
{
	std::vector<WCHAR*> listTagsBuff = stringCat(tags);
	CNote* Note = new CNote(note, date);
	std::vector<CTags*> tagsOfNote;
	for (int i = 0; i < listTagsBuff.size(); i++)
	{
		CTags* Tags = listTags.search(listTagsBuff[i]);
		if (Tags) Tags->pushNote(Note);
		else
		{
			Tags = listTags.push(listTagsBuff[i]);
			Tags->pushNote(Note);
		}
		tagsOfNote.push_back(Tags);
	}
	Note->setListTags(tagsOfNote);
	listNotes.push(Note);
}

void WriteFile()
{
	FILE* data, *size;
	data = fopen("data", "wb");
	size = fopen("size", "wt");

	fprintf(size, "%d\n", listNotes.size());

	for (int i = 0; i < listNotes.size(); i++)
	{
		int sizeNote = sizeof(listNotes.at(i)->getNote());
		int sizeTags = sizeof(listNotes.at(i)->getTagsBuff());
		int sizeDate = sizeof(listNotes.at(i)->getDate());

		int lenNote = wcslen(listNotes.at(i)->getNote());
		int lenTags = wcslen(listNotes.at(i)->getTagsBuff());
		int lenDate = wcslen(listNotes.at(i)->getDate());

		fprintf(size, "%d %d %d\n", lenNote, lenTags, lenDate);
		fwrite(listNotes.at(i)->getNote(), lenNote, sizeNote, data);
		fwrite(listNotes.at(i)->getTagsBuff(), lenTags, sizeTags, data);
		fwrite(listNotes.at(i)->getDate(), lenDate, sizeDate, data);
	}
	fclose(data);
	fclose(size);
}

void ReadFile()
{
	FILE* data, *size;
	data = fopen("data", "rb");
	size = fopen("size", "rt");

	if (!data || !size) return;

	int count;
	WCHAR tags[512], note[512], date[20];
	int lenTags, lenNote, lenDate;

	fscanf(size, "%d", &count);
	for (int i = 0; i < count; i++)
	{
		fscanf(size, "%d %d %d", &lenNote, &lenTags, &lenDate);
		fread(&note, lenNote, sizeof(WCHAR*), data);
		fread(&tags, lenTags, sizeof(WCHAR*), data);
		fread(&date, lenDate, sizeof(WCHAR*), data);
		add(tags, note, date);
	}
	fclose(size);
	fclose(data);
}

void drawPie(HDC hdc, int X, int Y, int R, float start, float angle, Color color)
{
	Graphics *graphics = new Graphics(hdc);
	Brush *brush = new SolidBrush(color);
	graphics->FillPie(brush, X, Y, R, R, (REAL)(start - 90), (REAL)angle);
	delete graphics;
	delete brush;
}

int getSumNote()
{
	int sum = 0;
	for (int i = 0; i < listTags.getList().size(); i++)
		sum += listTags.at(i)->count();
	return sum;
}

void getPercent()
{
	int countTag = listTags.getList().size();
	int sum = getSumNote();
	percent = new int[countTag];
	for (int i = 0; i < countTag; i++)
		percent[i] = listTags.at(i)->count() * 100 / sum;
	int sumPercent = 0;
	for (int i = 0; i < countTag; i++)
		sumPercent += percent[i];
	int valid = 100 - sumPercent;
	int i = 0;
	while (valid)
	{
		percent[i]++;
		i++;
		valid--;
	}
}

WCHAR* getToday()
{
	WCHAR* res = new WCHAR[10];
	time_t t = time(0);   // get time now
	struct tm * now = localtime(&t);
	swprintf(res, L"%d/%d/%d", now->tm_mon + 1, now->tm_mday, now->tm_year + 1900);
	return res;
}
