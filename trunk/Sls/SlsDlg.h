// SlsDlg.h : header file
//

#if !defined(AFX_SLSDLG_H__78F77400_D8A1_4A7F_83B9_CA297EFA6584__INCLUDED_)
#define AFX_SLSDLG_H__78F77400_D8A1_4A7F_83B9_CA297EFA6584__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSlsDlg dialog
#include <OXBackgroundPainter.h>
#include <OXDIB.h>
#include "OXBitmapButton.h"

class CSlsDlg : public CDialog
{
// Construction
public:
	CSlsDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSlsDlg)
	enum { IDD = IDD_SLS_DIALOG };
	CStatic	m_RightPanel;
	COXBitmapButton	m_WifiBtn;
	COXBitmapButton	m_VideoBtn;
	COXBitmapButton	m_PlayBtn;
	COXBitmapButton	m_PictureBtn;
	COXBitmapButton	m_PhotoBtn;
	COXBitmapButton	m_CloseBtn;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSlsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	void InitPage();
	void InitButtonRect(int bitmapWidth, int bitmapHeight);
	// Generated message map functions
	//{{AFX_MSG(CSlsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	COXBackgroundPainterOrganizer m_backPainterOrganizer;
	COXBackgroundPainterOrganizer m_RightbackPainterOrganizer;
	COXDIB *m_backgroup;
	COXDIB *m_rightbackgroup;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SLSDLG_H__78F77400_D8A1_4A7F_83B9_CA297EFA6584__INCLUDED_)
