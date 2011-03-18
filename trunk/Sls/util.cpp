#include "stdafx.h"
#include <afxdllx.h>
#include <GdiPlus.h>
#include "uitl.h"

HBITMAP GXLoadFile(LPCTSTR lpszBitmapName)
{
	WCHAR szBuff[MAX_PATH];
	memset(szBuff, 0, MAX_PATH*sizeof(WCHAR));
	atow(lpszBitmapName, szBuff, MAX_PATH);
	Gdiplus::Bitmap *pImg = new Gdiplus::Bitmap(szBuff);
	if(!pImg)
	{
		printlog("Load %s failed!\n", lpszBitmapName);
		return NULL;
	}
	
	HBITMAP hBMP = NULL;
	Gdiplus::Color cr(255, 0, 255);
	pImg->GetHBITMAP(cr, &hBMP);
	
	HBITMAP hRet = (HBITMAP)CopyImage(hBMP, IMAGE_BITMAP, 0, 0, LR_COPYDELETEORG);
	delete pImg;
	
	return hRet;
}

 void printLog(LPCSTR lpszFormat, ...)
{
	va_list args;
	va_start(args, lpszFormat);
	
	int nBuf;
	char szBuffer[1024];
	nBuf = vsprintf(szBuffer, lpszFormat, args);
	// was there an error? was the expanded string too long?
	ASSERT(nBuf >= 0);
	OutputDebugString(szBuffer);
	va_end(args);
}

 void printLog(LPCWSTR lpszFormat, ...)
{	
	va_list args;
	va_start(args, lpszFormat);
	int nBuf;
	WCHAR szBuffer[1024];
	
	nBuf = _vsnwprintf(szBuffer, countof(szBuffer), lpszFormat, args);
	
	// was there an error? was the expanded string too long?
	ASSERT(nBuf >= 0);
	OutputDebugStringW(szBuffer);
	va_end(args);
}