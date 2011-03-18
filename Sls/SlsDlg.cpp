// SlsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Sls.h"
#include "SlsDlg.h"
#include "util.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSlsDlg dialog

CSlsDlg::CSlsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSlsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSlsDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSlsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSlsDlg)
	DDX_Control(pDX, IDC_BUTTON_WIFI, m_WifiBtn);
	DDX_Control(pDX, IDC_BUTTON_VIDEO, m_VideoBtn);
	DDX_Control(pDX, IDC_BUTTON_PLAY, m_PlayBtn);
	DDX_Control(pDX, IDC_BUTTON_PICTURE, m_PictureBtn);
	DDX_Control(pDX, IDC_BUTTON_PHOTO, m_PhotoBtn);
	DDX_Control(pDX, IDC_BUTTON_CLOSE, m_CloseBtn);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSlsDlg, CDialog)
	//{{AFX_MSG_MAP(CSlsDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSlsDlg message handlers

BOOL CSlsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	m_backgroup = new COXDIB;
	HBITMAP hBitmap;
	hBitmap=GXLoadFile("c:\\background.png");
	HDIB hImg=m_backgroup->BitmapToDIB(hBitmap);
	m_backPainterOrganizer.Attach(this,m_backgroup);

	m_rightbackgroup = new COXDIB;
	HBITMAP hBitmap2;
	hBitmap2=GXLoadFile("c:\\background.png");
	//HDIB hImg2= m_rightbackgroup->BitmapToDIB(hBitmap2);
	//m_RightbackPainterOrganizer.Attach(&m_WifiBtn,m_rightbackgroup);
	m_WifiBtn.SetBitmap(hBitmap2);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSlsDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSlsDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
