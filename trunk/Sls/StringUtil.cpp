#include "stdafx.h"
#include "StringUtil.h"
BOOL CStringUtil::MByteToWChar(LPCSTR lpcszStr, LPWSTR lpwszStr, DWORD dwSize)
{
	// Get the required size of the buffer that receives the Unicode 
	// string. 
	DWORD dwMinSize; 
	dwMinSize = MultiByteToWideChar(CP_UTF8, 0, lpcszStr, -1, NULL, 0); 
	
	if(dwSize < dwMinSize) 
	{ 
		return FALSE; 
	} 
	// Convert headers from ASCII to Unicode. 
	MultiByteToWideChar(CP_UTF8, 0, lpcszStr, -1, lpwszStr, dwMinSize);  
	return TRUE;
}
BOOL CStringUtil::MByteToWCharExt(LPCSTR lpcszStr, LPWSTR &lpwszStr)
{
	// Get the required size of the buffer that receives the Unicode 
	// string. 
	int size=MultiByteToWideChar(CP_UTF8,0,lpcszStr,-1,NULL,0);
	lpwszStr =new wchar_t[size+1];
	if(!MultiByteToWideChar(CP_UTF8,0,lpcszStr,-1,lpwszStr,size))
	{
		return FALSE;
	}
	return TRUE;
}
BOOL CStringUtil::WCharToMByte(LPCWSTR lpcwszStr, LPSTR lpszStr, DWORD dwSize)
{
	DWORD dwMinSize; 
	dwMinSize = WideCharToMultiByte(CP_OEMCP, NULL, lpcwszStr, -1, NULL, 0, NULL, FALSE); 
	if(dwSize < dwMinSize) 
	{ 
		return FALSE; 
	} 
	WideCharToMultiByte(CP_OEMCP, NULL, lpcwszStr, -1, lpszStr, dwSize, NULL, FALSE); 
	return TRUE;
}