// 1512292QuanLiChiTieu.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "1512292QuanLiChiTieu.h"

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
    LoadStringW(hInstance, IDC_MAIN, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MAIN));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAIN));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MAIN);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_MAIN));

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

   SetWindowText(hWnd, L"Quản lí chi tiêu");

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   if (ReadFile()) 
   {
	   g_ListView->LoadListView(List);
	   sum = getSum();
		TCHAR buff[50];
	   _itow_s(getSum(), buff, 10);
		SetWindowText(txtSum,buff);
	   InvalidateRect(hWnd, NULL, TRUE);
   }

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
    switch (message)
    {
	case WM_CREATE:
		{
			LOGFONT lf;
			GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
			HFONT hFont = CreateFont(lf.lfHeight, lf.lfWidth,
				lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
				lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
				lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
				lf.lfPitchAndFamily, lf.lfFaceName);

			HFONT hFont1 = CreateFont(80, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET,
				OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
				DEFAULT_PITCH | FF_DONTCARE, TEXT("Segoe UI Historic"));
			HFONT hFont2 = CreateFont(30, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET,
				OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
				DEFAULT_PITCH | FF_DONTCARE, TEXT("Segoe UI"));

			hwndheader = CreateWindowEx(0, L"STATIC", L"QUẢN LÍ CHI TIÊU", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_CENTER | SS_CENTERIMAGE, 
				0, 0, 1024, 50, hWnd, NULL, hInst, NULL);
			SendMessage(hwndheader, WM_SETFONT, WPARAM(hFont2), TRUE);

			HICON hIconA = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICONADD));
			hwndbutton = CreateWindowEx(0, L"BUTTON", L"", BS_ICON | WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | SS_CENTERIMAGE|SSF_DONTPRETTYPATH,
				70, 145, 40, 40, hWnd, (HMENU)IDC_BUTTONADD, hInst, NULL);
			SendMessage(hwndbutton, BM_SETIMAGE,
				(WPARAM)IMAGE_ICON, (LPARAM)hIconA);

			HICON hIconC = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICONCLOSE));
			hwnd = CreateWindowEx(0, L"BUTTON", L"", BS_ICON | WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | SS_CENTERIMAGE,
				970, 0, 40, 40, hWnd, (HMENU)IDC_BUTTONCLOSE, hInst, NULL);
			SendMessage(hwnd, BM_SETIMAGE,
				(WPARAM)IMAGE_ICON, (LPARAM)hIconC);

			HICON hIconR = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICONRESET));
			hwndbutton = CreateWindowEx(0, L"BUTTON", L"", BS_ICON | WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | SS_CENTERIMAGE,
				370, 145, 40, 40, hWnd, (HMENU)IDC_BUTTONRESET, hInst, NULL);
			SendMessage(hwndbutton, BM_SETIMAGE,
				(WPARAM)IMAGE_ICON, (LPARAM)hIconR);

			HICON hIconB = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICONBACK));
			hwndbutton = CreateWindowEx(0, L"BUTTON", L"", BS_ICON | WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | SS_CENTERIMAGE,
				170, 145, 40, 40, hWnd, (HMENU)IDC_BUTTONBACK, hInst, NULL);
			SendMessage(hwndbutton, BM_SETIMAGE,
				(WPARAM)IMAGE_ICON, (LPARAM)hIconB);

			HICON hIconP = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICONPREV));
			hwndbutton = CreateWindowEx(0, L"BUTTON", L"", BS_ICON | WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | SS_CENTERIMAGE,
				270, 145, 40, 40, hWnd, (HMENU)IDC_BUTTONPREV, hInst, NULL);
			SendMessage(hwndbutton, BM_SETIMAGE,
				(WPARAM)IMAGE_ICON, (LPARAM)hIconP);

			hwnd = CreateWindowEx(0, L"STATIC", L"Loại chi tiêu", 
				WS_CHILD | WS_VISIBLE | SS_LEFT | SS_CENTER | SS_CENTERIMAGE, 
				40, 95, 100, 20, hWnd, NULL, hInst, NULL);
			SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

			hwnd = CreateWindowEx(0, L"STATIC", L"Chi tiết", 
				WS_CHILD | WS_VISIBLE | SS_LEFT | SS_CENTER | SS_CENTERIMAGE, 
				190, 95, 100, 20, hWnd, NULL, hInst, NULL);
			SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

			hwnd = CreateWindowEx(0, L"STATIC", L"Hao phí", 
				WS_CHILD | WS_VISIBLE | SS_LEFT | SS_CENTER | SS_CENTERIMAGE, 
				340, 95, 100, 20, hWnd, NULL, hInst, NULL);
			SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

			hwnd = CreateWindowEx(0, L"BUTTON", L"Chi Tiêu", 
				BS_GROUPBOX | WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 
				20, 70, 440, 125, hWnd, NULL, hInst, NULL);
			SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

			hwnd = CreateWindowEx(0, L"BUTTON", L"Danh sách chi tiêu", 
				BS_GROUPBOX | WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 
				20, 205, 440, 242, hWnd, NULL, hInst, NULL);
			SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

			hwnd = CreateWindowEx(0, L"BUTTON", L"Biểu đồ", 
				BS_GROUPBOX | WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 
				495, 70, 495, 262, hWnd, NULL, hInst, NULL);
			SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

			hwnd = CreateWindowEx(0, L"BUTTON", L"Tổng chi tiêu (VND)", 
				BS_GROUPBOX | WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 
				495, 340, 495, 117, hWnd, NULL, hInst, NULL);
			SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

			for (int i = 0; i < 6; i++)
			{
				hwnd = CreateWindowEx(0, L"STATIC", typeChoose[i],
					WS_CHILD | WS_VISIBLE | SS_LEFT | SS_CENTERIMAGE,
					590, 90 + 40 * i, 80, 20, hWnd, NULL, hInst, NULL);
				SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

				txtPercent[i] = CreateWindowEx(0, L"EDIT", L"",
					WS_CHILD | WS_VISIBLE | SS_RIGHT | WS_DISABLED,
					670, 90 + 40 * i, 40, 20, hWnd, NULL, hInst, NULL);
				SendMessage(txtPercent[i], WM_SETFONT, WPARAM(hFont), TRUE);
			}
	
			typeBox = CreateWindowEx(0, L"COMBOBOX",L"Loại", CBS_DROPDOWNLIST | WS_CHILD | WS_VISIBLE, 
				 40, 120, 100, 120, hWnd, NULL, hInst, NULL);
			SendMessage(typeBox, WM_SETFONT, WPARAM(hFont), TRUE);
			for (int i = 0; i < 6; ++i)
			{
				// Add string to combobox.
				SendMessage(typeBox, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)typeChoose[i]);
			}
	//		SendMessage(typeBox, CB_SETCURSEL, NULL, (LPARAM)0);
	//		SendMessage(typeBox, CB_ERRSPACE, NULL, (LPARAM)0);

			txtDetail = CreateWindowEx(0, L"EDIT", L"Chi tiết chi tiêu",
				CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | SS_CENTER | WS_BORDER,
				190, 120, 100, 20, hWnd,(HMENU)IDC_DETAILBOX, hInst, NULL);
			SendMessage(txtDetail, WM_SETFONT, WPARAM(hFont), TRUE);

			txtFee = CreateWindowEx(0, L"EDIT", L"Số tiền chi tiêu",
				WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | SS_RIGHT | WS_BORDER,
				340, 120, 100, 20, hWnd, (HMENU)IDC_FEEBOX, hInst, NULL);
			SendMessage(txtFee, WM_SETFONT, WPARAM(hFont), TRUE);

			txtSum = CreateWindowEx(0, L"EDIT", L"0", 
				WS_CHILD | WS_VISIBLE | SS_RIGHT | WS_DISABLED, 
				518, 362, 452, 80, hWnd, NULL, hInst, NULL);
			SendMessage(txtSum, WM_SETFONT, WPARAM(hFont1), TRUE);

			g_ListView = new ListView;
			g_ListView->Create(hWnd, hInst, 400, 210, 40, 230);
			g_ListView->DeleteAll();
			g_ListView->Init3Cols();
			state.push_back(List);
			State = state.size() - 1;
			GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
			return true;
		}
		break;
    case WM_COMMAND:
        {
			TCHAR* bufferType = NULL;
			TCHAR* bufferDetail = NULL;
			TCHAR* bufferFee = NULL;
			TCHAR* bufferSum = NULL;

            int wmId = LOWORD(wParam);
            // Parse the menu selections:
			if (HIWORD(wParam) == EN_SETFOCUS && LOWORD(wParam) == IDC_DETAILBOX)
			{
				clickDetail = 1;
				SetWindowText(txtDetail, 0);
			}
			if (HIWORD(wParam) == EN_SETFOCUS && LOWORD(wParam) == IDC_FEEBOX)
			{
				clickFee = 1;
				SetWindowText(txtFee, 0);
			}
            switch (wmId)
            {
            case IDM_ABOUT:
				{
					DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
				}
                break;
            case IDM_EXIT:
				{
					WriteFile();
					DestroyWindow(hWnd);
				}
                break;
			case IDC_BUTTONRESET:
				{
					if (State != 0 || State != state.size() - 1)
					{
						while (State != state.size() - 1)
						{
							state.pop_back();
						}
					}
					g_ListView->DeleteAll();
					List.clear();
					state.push_back(List);
					State = state.size() - 1;
					InvalidateRect(hWnd, NULL, TRUE);
					SetWindowText(txtSum, L"0");
					SetWindowText(txtDetail, L"Chi tiết chi tiêu");
					SetWindowText(txtFee, L"Số tiền chi tiêu");
				}
				break;
			case IDC_BUTTONCLOSE:
				{
					WriteFile();
					PostQuitMessage(0);
				}
				break;
			case IDC_BUTTONADD:
				{
					int sizeType = GetWindowTextLength(typeBox);
					int sizeDetail = GetWindowTextLength(txtDetail);
					int sizeFee = GetWindowTextLength(txtFee);

					bufferType = new TCHAR[sizeType + 1];
					bufferDetail = new TCHAR[sizeDetail + 1];
					bufferFee = new TCHAR[sizeFee + 1];

					GetWindowText(typeBox, bufferType, sizeType + 1);
					GetWindowText(txtDetail, bufferDetail, sizeDetail + 1);
					GetWindowText(txtFee, bufferFee, sizeFee + 1);

					bool error = 0;
					if (sizeType <= 0 && (sizeDetail <= 0 || !clickDetail)&&(sizeFee <= 0 || !clickFee))
					{
						error = 1;
						MessageBox(0, L"Bạn phải nhập dữ liệu!", L"Lỗi!", 0);
						break;
					}
					if (sizeType <= 0)
					{
						error = 1;
						MessageBox(0, L"Bạn phải chọn loại chi tiêu!", L"Lỗi!", 0);
						break;
					}
					if (sizeDetail <= 0 ||!clickDetail)
					{
						error = 1;
						MessageBox(0, L"Bạn phải nhập chi tiết chi tiêu!", L"Lỗi!", 0);
						break;
					}
					if (sizeFee <= 0 || !clickFee)
					{
						error = 1;
						MessageBox(0, L"Bạn phải nhập hao phí chi tiêu!", L"Lỗi!", 0);
						break;
					}
					else for (int i = 0; i < sizeFee; i++)
						{
							if (bufferFee[i] < 48 || bufferFee[i] > 57) 
							{
								error = 1;
								MessageBox(0, L"Hao phí phải là con số (Không có ký tự đặc biệt)!", L"Lỗi!", 0);
								break;
							}
						}
					if (!error)
					{
						clickDetail = 0;
						clickFee = 0;
						Expense data;
						data.set(bufferType, sizeType + 1, bufferDetail, sizeDetail + 1, bufferFee, sizeFee + 1);
						if (State != 0 && State != (state.size() - 1))
						{
							while (State != (state.size() - 1))
							{
								state.pop_back();
							}
						}
						List.push_back(data);
						g_ListView->LoadListView(List);
						sum = getSum();
						TCHAR buff[50];
						_itow_s(getSum(), buff, 10);
						SetWindowText(txtSum, buff);
						SetWindowText(txtDetail, L"Chi tiết chi tiêu");
						SetWindowText(txtFee, L"Số tiền chi tiêu");
						state.push_back(List);
						State = state.size() - 1;
					//	SendMessage(typeBox, CB_ERRSPACE, NULL, (LPARAM)0);
						InvalidateRect(hWnd, NULL, FALSE);
					}
				}
				break;
			case IDC_BUTTONBACK:
				{
					if (State > 0)
					{
						List = state[State - 1];
						State--;
						g_ListView->LoadListView(List);
						sum = getSum();
						TCHAR buff[50];
						_itow_s(getSum(), buff, 10);
						SetWindowText(txtSum, buff);
						InvalidateRect(hWnd, NULL, FALSE);
					}
				}
				break;
			case IDC_BUTTONPREV:
				{
					if (State < (state.size()-1))
					{
						List = state[State + 1];
						State++;
						g_ListView->LoadListView(List);
						sum = getSum();
						TCHAR buff[50];
						_itow_s(getSum(), buff, 10);
						SetWindowText(txtSum, buff);
						InvalidateRect(hWnd, NULL, FALSE);
					}
				}
				break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
			if (bufferType) delete[]bufferType;
			if (bufferDetail) delete[]bufferDetail;
			if (bufferFee) delete[]bufferFee;
			if (bufferSum) delete[]bufferSum;
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
			float angle = 0;
			getPercent();
			for (int i = 0; i < 6; i++)
			{
				drawPie(hdc, 460, 60 + 40 * i, 100, 90, -30, color[i]);
				drawPie(hdc, 750, 100, 200, angle, 3.6*money[i], color[i]);
				TCHAR *buff = new TCHAR[10];
				swprintf(buff,6, L"%d %%", money[i]);

				SetWindowText(txtPercent[i], buff);
				angle += 3.6*money[i];
			}
			getPercent();

            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
		{
			PostQuitMessage(0);
			WriteFile();
			GdiplusShutdown(gdiplusToken);
		}
        break;
	case WM_CTLCOLORSTATIC:
		if ((HWND)lParam == hwndheader)
		{
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetDCBrushColor((HDC)wParam, RGB(255,0 , 0));	//Set a Solid color
			SetBkColor((HDC)wParam, RGB(255, 0, 0));
			return (LRESULT)GetStockObject(DC_BRUSH); //And use it to paint the rest part of the windows
		}
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
bool ReadFile() 
{
	FILE* fData;
	fopen_s(&fData, "Data", "rb");
	FILE* fSize;
	fopen_s(&fSize, "size", "rt");

	if (fData != NULL && fSize != NULL) 
	{
		while ((!feof(fData)) && (!feof(fSize))) 
		{
			int sizeType = 0, sizeDetail = 0, sizeFee = 0;
			fscanf_s(fSize, "%d", &sizeType);
			fscanf_s(fSize, "%d", &sizeDetail);
			fscanf_s(fSize, "%d", &sizeFee);

			if(sizeType)
			{
				Expense data;
				WCHAR *buffType = new WCHAR[sizeType + 1];
				WCHAR *buffDetail = new WCHAR[sizeDetail + 1];
				WCHAR *buffFee = new WCHAR[sizeFee + 1];

				fread(buffType, sizeof(WCHAR), sizeType, fData);
				fread(buffDetail, sizeof(WCHAR), sizeDetail, fData);
				fread(buffFee, sizeof(WCHAR), sizeFee, fData);

				buffType[sizeType + 1] = NULL;
				buffDetail[sizeDetail + 1] = NULL;
				buffFee[sizeFee+1] = NULL;

				data.set(buffType, sizeType + 1, buffDetail, sizeDetail + 1, buffFee, sizeFee + 1);
				List.push_back(data);
			}
		}
	}
	else 
	{
		return false;
	}
	fclose(fData);
	fclose(fSize);
	return true;
}
void WriteFile()
{
	FILE* fData;
	fopen_s(&fData, "Data", "wb");
	FILE* fSize;
	fopen_s(&fSize, "Size", "wt");
	fseek(fData, 0, SEEK_END);
	fseek(fSize, 0, SEEK_END);
	for (int i = 0; i < List.size(); i++) 
	{
		//ghi kích thước chuỗi
		int sizeType = _tcslen(List[i].getType());
		int sizeDetail = _tcslen(List[i].getDetail());
		int sizeFee = _tcslen(List[i].getFee());
		fprintf(fSize, "%d %d %d ", sizeType, sizeDetail, sizeFee);

		//Ghi chuỗi
		fwrite(List[i].getType(), sizeof(WCHAR), sizeType, fData);
		fwrite(List[i].getDetail(), sizeof(WCHAR), sizeDetail, fData);
		fwrite(List[i].getFee(), sizeof(WCHAR), sizeFee, fData);
	}
	fclose(fData);
	fclose(fSize);
}
long getSum()
{
	TCHAR buff[50];
	
	int result = 0;
	for (int i = 0; i < List.size(); i++) 
	{
		result += _wtoi(List[i].getFee());
	}
	return result;
}
void getPercent()
{
	for (int i = 0; i < 6; i++)
	{
		money[i] = 0;
	}
	for (int i = 0; i < List.size(); i++) 
	{
		for (int j = 0; j < 6; j++)
		{
			if (_tcscmp(List[i].getType(), typeChoose[j]) == 0)
			{
				money[j] += _wtoi(List[i].getFee());
				break;
			}
		}
	}
	int SumFee = 0;
	for (int i = 0; i < 6; i++)
	{
		SumFee += money[i];
	}
	if (SumFee)
	{
		for (int i = 0; i < 6; i++)
		{
			money[i] = money[i] * 100 / SumFee;
		}
		SumFee = 0;
		for (int i = 0; i < 6; i++)
		{
			SumFee += money[i];
		}
		if (SumFee < 100)
		{
			int invalid = 100 - SumFee;
			while (invalid)
			{
				for (int i = 0; i < 6; i++)
				{
					if (invalid&&money[i])
					{
						invalid--;
						money[i]++;
					}
				}
			}
		}
	}
}
void drawPie(HDC hdc, int X, int Y, int R, float start, float angle, Color color)
{
	Graphics *graphics = new Graphics(hdc);
	Brush *brush = new SolidBrush(color);
	graphics->FillPie(brush, X, Y, R, R, (REAL)(start - 90), (REAL)angle);
	delete graphics;
	delete brush;
}