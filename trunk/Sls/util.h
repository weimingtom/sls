#ifndef UTIL_H_
#define UTIL_H_

#define countof(x) (sizeof(x) / sizeof((x)[0]))
#define atow(strA, strW, lenW) MultiByteToWideChar(CP_ACP, 0, strA, -1, strW, lenW)
void printLog(LPCSTR lpszFormat, ...);
void printLog(LPCWSTR lpszFormat, ...);
#define printlog printLog
HBITMAP GXLoadFile(LPCTSTR lpszBitmapName);
CString &GetAppPath();
CString &GetImagePath();
HBITMAP GetImageHandle(CString &img);
#endif