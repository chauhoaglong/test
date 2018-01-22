#pragma once
#ifndef CDRIVE_H
#define CDRIVE_H

#include <windows.h>
#include <tchar.h>
#include <Shlwapi.h>
#define KB 1
#define MB 2
#define GB 3
#define TB 4
#define RADIX 10
class CDrive
{
private:
	TCHAR **m_pszDrive;
	TCHAR **m_pszVolName;
	TCHAR **m_pszDisplayName; //Kết hợp giữa pszDrive và pszVolName
	int *m_nIconIndex;
	int m_nCount;

public:
	CDrive();
	~CDrive();

	TCHAR* GetDriveName(const int &i);
	TCHAR* GetVolName(const int &i);
	TCHAR* GetDisplayName(const int &i);
	int GetCount();
	int GetIconIndex(const int &i);

	void GetSystemDrives();

	LPWSTR GetType(const int &i);
	__int64 GetSize(const int &i);
	LPWSTR GetSizeStr(const int &i);
	__int64 GetFreeSize(const int &i);
	LPWSTR GetFreeSizeStr(const int &i);
};

#endif

