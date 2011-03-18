#ifndef STRINGUTIL_H
#define STRINGUTIL_H

class CStringUtil
{
public:
	static BOOL MByteToWChar(LPCSTR lpcszStr, LPWSTR lpwszStr, DWORD dwSize);
	static BOOL MByteToWCharExt(LPCSTR lpcszStr, LPWSTR &lpwszStr);
	static BOOL WCharToMByte(LPCWSTR lpcwszStr, LPSTR lpszStr, DWORD dwSize);
};
#endif