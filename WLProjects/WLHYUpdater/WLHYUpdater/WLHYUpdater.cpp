// WLHYUpdater.cpp : 定义控制台应用程序的入口点。
//
#include "afx.h"
#include "stdafx.h"
#include <iostream>
#include <UrlMon.h>
#pragma comment(lib, "urlmon.lib")
using namespace std;

int main()
{
	/*char * CURRENT = new char[MAX_PATH];
	GetCurrentDirectory(MAX_PATH,)*/
	//::WinExec("mkdir C:\\", SW_NORMAL);
	//=========================================================================================
	// [UPDATE]
	// hyurl=XXXXX
	// reportport=XXXX
	//-----------------------------------------------------------------------------------------
	HRESULT hr = URLDownloadToFile(0, _T("http://8.8.8.8/download/A_Priceboard_tool.exe"),
		_T("C:\\hyupdate.exe"), 0, NULL);
	if (hr == S_OK)
	{
		cout << "Success Downloading FileURL" << endl;
	}
	else
	{	
		cout << "#Error While Downloading FileURL!" << endl;
		return -1;
	}
	//-----------------------------------------------------------------------------------------
	
	
	char * FileUrl = new char[MAX_PATH];
	char * reportport = new char[MAX_PATH];
	GetPrivateProfileStringW(_T("UPDATE"), _T("hyurl"), _T(""), (LPWSTR)FileUrl, MAX_PATH, _T("C:\\hyupdate.ini"));
	GetPrivateProfileStringW(_T("UPDATE"), _T("reportport"), _T(""), (LPWSTR)reportport, MAX_PATH, _T("C:\\hyupdate.ini"));

	if (FileUrl == "" || reportport == "")
	{
		cout << "Exception!" << endl;
	}

	HRESULT hr2 = URLDownloadToFileW(0, (LPCWSTR)FileUrl,     //.GetString()
		_T("C:\\HyUpdateBag.exe "), 0, NULL);
	if (hr2 == S_OK)
	{
		cout << "Success Downloading FileURL2" << endl;
	}
	else
	{
		cout << "#Error While Downloading FileURL2!" << endl;
		return -1;
	}






	//=========================================================================================

	::WinExec("TASKKILL /IM hystart.exe /F", SW_HIDE);
	::WinExec("TASKKILL /IM shop.exe /F", SW_HIDE);
	::WinExec("TASKKILL /IM pos.exe /F", SW_HIDE);
	::WinExec("TASKKILL /IM pos_device.exe /F", SW_HIDE);


	BOOL mvresault = MoveFileW(_T("C:\\mdcas\\posdb"), _T("C:\\posdbbackup"));
	if (mvresault == 0)
	{
		cout << "#Error While Back Up Datas!" << endl;
		//return -1;
	}
	else
	{
		

	}
	WinExec("C:\\HyUpdateBag.exe", SW_NORMAL);


    return 0;
}

