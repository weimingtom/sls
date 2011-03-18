// Sls.h : main header file for the SLS application
//

#if !defined(AFX_SLS_H__6AC737A1_C261_416F_B86E_8FB278F623FE__INCLUDED_)
#define AFX_SLS_H__6AC737A1_C261_416F_B86E_8FB278F623FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSlsApp:
// See Sls.cpp for the implementation of this class
//

class CSlsApp : public CWinApp
{
public:
	CSlsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSlsApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSlsApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	private:
		ULONG_PTR m_gdiplusToken;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SLS_H__6AC737A1_C261_416F_B86E_8FB278F623FE__INCLUDED_)
