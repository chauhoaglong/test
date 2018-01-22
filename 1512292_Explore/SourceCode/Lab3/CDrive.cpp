#include "stdafx.h"
#include "CDrive.h"

#include "CConverter.h"
#include "CDrive.h"

//Dùng để sử dụng hàm StrCpy, StrNCat
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

#define BUFFER_LEN 105 //Để chữa chuỗi tối đa 26 x 4 + 1 kí tự (Ví dụ "A:\")

//Các chỉ số icon là vị trí trong Imagelist của Treeview, trích xuất ra từ Shell32.dll
#define IDI_FLOPPY 4
#define IDI_USB 5
#define IDI_HDD 6
#define IDI_CD  7 

CDrive::CDrive()
{
	m_pszDrive = NULL;
	m_pszVolName = NULL;
	m_pszDisplayName = NULL;
	m_nIconIndex = NULL;
	m_nCount = 0;
}

CDrive::~CDrive()
{
	for (int i = 0; i < m_nCount; ++i)
	{
		delete[] m_pszDrive[i];
		delete[] m_pszVolName[i];
		delete[] m_pszDisplayName[i];
	}

	delete[] m_pszDrive;
	delete[] m_pszVolName;
	delete[] m_pszDisplayName;
	delete[] m_nIconIndex;
	m_nCount = 0;
}

/*****************************************************************************************/
TCHAR* CDrive::GetDriveName(const int &i)
{
	return m_pszDrive[i];
}

TCHAR* CDrive::GetVolName(const int &i)
{
	return m_pszVolName[i];
}

TCHAR* CDrive::GetDisplayName(const int &i)
{
	return m_pszDisplayName[i];
}

int CDrive::GetCount()
{
	return m_nCount;
}

int CDrive::GetIconIndex(const int &i)
{
	return m_nIconIndex[i];
}
/*****************************************************************************************/

void CDrive::GetSystemDrives()
{
	TCHAR buffer[BUFFER_LEN];
	int i;

	GetLogicalDriveStrings(BUFFER_LEN, buffer);

	//Đếm số lượng ổ đĩa 
	for (i = 0; !((buffer[i] == 0) && (buffer[i + 1] == 0)); ++i)
		if (buffer[i] == 0)
			++m_nCount;
	++m_nCount;

	//Cấp phát bộ nhớ để chứa chuỗi tương ứng
	m_pszDrive = new TCHAR*[m_nCount];
	m_pszVolName = new TCHAR*[m_nCount];
	m_pszDisplayName = new TCHAR*[m_nCount];
	m_nIconIndex = new int[m_nCount];

	for (i = 0; i < m_nCount; ++i)
	{
		m_pszDrive[i] = new TCHAR[4];
		m_pszVolName[i] = new TCHAR[30];
		m_pszDisplayName[i] = new TCHAR[35];
	}

	int j, k;
	i = 0;

	//Lấy từng kí tự ổ đĩa
	for (j = 0; j< m_nCount; ++j)
	{
		k = 0;
		while (buffer[i] != 0)
			m_pszDrive[j][k++] = buffer[i++];
		m_pszDrive[j][k] = 0; //Kết thúc chuỗi
		++i;
	}

	//Lấy volume cho từng ổ đĩa, kết hợp luôn với việc lấy tên hiển thị ứng với từng ổ
	int nType;

	for (i = 0; i < m_nCount; ++i)
	{
		nType = GetDriveType(m_pszDrive[i]);
		StrCpy(buffer, _T(""));

		if ((nType == DRIVE_FIXED) || ((i > 1) && (nType == DRIVE_REMOVABLE)))//Nếu là ổ cứng hay USB
		{
			if (nType == DRIVE_FIXED)
				m_nIconIndex[i] = IDI_HDD;
			else
				m_nIconIndex[i] = IDI_USB;

			GetVolumeInformation(m_pszDrive[i], buffer, BUFFER_LEN, NULL, NULL, NULL, NULL, 0);
			StrCpy(m_pszVolName[i], buffer);
		}
		else
			if (nType == DRIVE_CDROM)
			{
				GetVolumeInformation(m_pszDrive[i], buffer, BUFFER_LEN, NULL, NULL, NULL, NULL, 0);
				if (wcslen(buffer) == 0)
					StrCpy(m_pszVolName[i], _T("CD Rom"));
				else
					StrCpy(m_pszVolName[i], buffer);
				m_nIconIndex[i] = IDI_CD;
			}
			else
				if (((i == 0) || (i == 1)) && (nType == DRIVE_REMOVABLE)) //Nếu là ổ mềm
				{
					StrCpy(m_pszVolName[i], _T("3½ Floppy"));
					m_nIconIndex[i] = IDI_FLOPPY;
				}

		if (wcslen(m_pszVolName[i]) == 0) //Hổng có label T_T
			StrCpy(m_pszDisplayName[i], _T("Local Disk"));
		else
			StrCpy(m_pszDisplayName[i], m_pszVolName[i]);

		//Thêm vào phần sau hai dấu mở ngoặc. Ví dụ: (C:) như ta thường thấy WinXp (C:)
		StrCat(m_pszDisplayName[i], _T(" ("));
		StrNCat(m_pszDisplayName[i], m_pszDrive[i], 3);
		StrCat(m_pszDisplayName[i], _T(")"));
	}
}
/*****************************************************************************************/

LPWSTR CDrive::GetType(const int &i)
{
	switch (GetIconIndex(i))
	{
	case IDI_FLOPPY:
		return _T("3½ Floppy");
		break;
	case IDI_CD:
		return _T("CD Rom");
		break;
	case IDI_HDD:
		return _T("Local Disk");
		break;
	}

	//Còn lại chắc chắn là USB
	return _T("Removable Disk");
}
/*****************************************************************************************/

__int64 CDrive::GetSize(const int &i)
{
	__int64 nSize;
	GetDiskFreeSpaceEx(GetDriveName(i), NULL, (PULARGE_INTEGER)&nSize, NULL);

	return nSize;
}

LPWSTR CDrive::GetSizeStr(const int &i)
{
	return  CConverter::Convert(GetSize(i));
}

__int64 CDrive::GetFreeSize(const int &i)
{
	__int64 nFreeSpace;
	GetDiskFreeSpaceEx(GetDriveName(i), NULL, NULL, (PULARGE_INTEGER)&nFreeSpace);

	return nFreeSpace;
}

LPWSTR CDrive::GetFreeSizeStr(const int &i)
{
	return  CConverter::Convert(GetFreeSize(i));
}
