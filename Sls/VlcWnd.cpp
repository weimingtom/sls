#include "StdAfx.h"
#include "VlcWnd.h"
#include "resource.h"
#include "util.h"
#include <GdiPlus.h>


#define WS_EX_LAYERED           0x00080000
#define AC_SRC_ALPHA            0x01
CVlcWnd::CVlcWnd()
{
	m_hVlcWnd = CreateDialogParam(::AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDD_CHILD), iParentWnd->GetSafeHwnd(), VlcWndProc, (LPARAM)this);
	if(!iPlayPath.IsEmpty())
	{
		int vlc_argc = 0;
		char *vlc_argv[100];
		vlc_argv[vlc_argc++] = "--ignore-config";
		vlc_argv[vlc_argc++] = "--rtsp-caching=30";
		vlc_argv[vlc_argc++] = "--no-video-title-show";
		m_pVlcInst = libvlc_new(vlc_argc, vlc_argv);		
		m_pVlcMedia = libvlc_media_new_location(m_pVlcInst, iPlayPath);
		m_pVlcMediaPlayer = libvlc_media_player_new_from_media(m_pVlcMedia);
		libvlc_media_player_set_hwnd(m_pVlcMediaPlayer, m_hVlcWnd);
		m_fZoom = 1.0;
		libvlc_video_set_scale(m_pVlcMediaPlayer, m_fZoom);
	}
}

CVlcWnd::~CVlcWnd()
{
	
}

void CVlcWnd::SetParentWnd(CWnd *aParentWnd)
{
	iParentWnd=aParentWnd;
}
void CVlcWnd::SetPlayPath(CString aPath)
{
	iPlayPath=aPath;
}
void CVlcWnd::Play()
{
	if(m_pVlcMediaPlayer)
	{
		if(!libvlc_media_player_is_playing(m_pVlcMediaPlayer))
		{
			libvlc_media_player_play(m_pVlcMediaPlayer);
		}
	}
}
void CVlcWnd::Stop()
{
	if(m_pVlcMediaPlayer)
	{
		if(libvlc_media_player_is_playing(m_pVlcMediaPlayer))
		{
			libvlc_media_player_stop(m_pVlcMediaPlayer);
		}
	}
}



VOID CVlcWnd::Show(BOOL bShow)
{

}

// Function name	: ZoomIn
// Description	    : 
// Return type		: BOOL 
BOOL CVlcWnd::ZoomIn()
{
	if(!m_pVlcMediaPlayer)
		return FALSE;
	
	printlog("%s(%d):'ZoomIn : %.1f'\n", __FILE__, __LINE__, m_fZoom);
	m_fZoom += 0.1;
	if(m_fZoom > 8.0)
		return FALSE;
	
	libvlc_video_set_scale(m_pVlcMediaPlayer, m_fZoom);
	return TRUE;
}

// Function name	: ZoomOut
// Description	    : 
// Return type		: BOOL 
BOOL CVlcWnd::ZoomOut()
{
	if(!m_pVlcMediaPlayer)
		return FALSE;
	
	// 	m_fZoom = libvlc_video_get_scale(m_pVlcMediaPlayer);
	m_fZoom -= 0.1;
	if(m_fZoom <= 0.1)
		return FALSE;
	libvlc_video_set_scale(m_pVlcMediaPlayer, m_fZoom);
	return TRUE;
}

// Function name	: ZoomNormal
// Description	    : 
// Return type		: BOOL 
BOOL CVlcWnd::ZoomNormal()
{
	if(!m_pVlcMediaPlayer)
		return FALSE;
	
	m_fZoom = 1.0;
	libvlc_video_set_scale(m_pVlcMediaPlayer, m_fZoom);
	return TRUE;
}

// Function name	: Capture
// Description	    : 
// Return type		: BOOL 
// Argument         : LPTSTR szPath
BOOL CVlcWnd::Capture(LPTSTR szPath)
{
	if(!m_pVlcMediaPlayer)
		return FALSE;
	
	//libvlc_video_take_snapshot(p_media_player, 0, szSaveFile, 720, 480);
	INT w = libvlc_video_get_width(m_pVlcMediaPlayer);
	INT h = libvlc_video_get_height(m_pVlcMediaPlayer);
	
	if(S_OK == libvlc_video_take_snapshot(m_pVlcMediaPlayer,0, szPath, w, h))
		return TRUE;
	
	return FALSE;
}

// Function name	: Record
// Description	    : ¼��
// Return type		: BOOL 
// Argument         : LPTSTR szPath
BOOL CVlcWnd::Record(LPTSTR szPath)
{
	if(m_bRecording)
	{
		if(m_pVlcMediaPlayer2)
		{
			libvlc_media_player_stop(m_pVlcMediaPlayer2);
			libvlc_media_player_release(m_pVlcMediaPlayer2);
			m_pVlcMediaPlayer2 = NULL;
		}
		if(m_pVlcMedia2)
		{
			libvlc_media_release(m_pVlcMedia2);
			m_pVlcMedia2 = NULL;
		}
		if(m_pVlcInst2)
		{
			libvlc_release(m_pVlcInst2);
			m_pVlcInst2 = NULL;
		}
		
		m_bRecording = FALSE;
		
		m_bFlash = FALSE;
		UpdateDisplay(100);
		KillTimer(m_hOSDWnd, 1001);
		return m_bRecording;
	}
	
	int vlc_argc = 0;
	char *vlc_argv[100];
	vlc_argv[vlc_argc++] = "--ignore-config";
	vlc_argv[vlc_argc++] = "--rtsp-caching=90";
	vlc_argv[vlc_argc++] = "--no-video-title-show";
	
	TCHAR szName[MAX_PATH];
	wsprintf(szName, _T("--sout=#standard{access=file,mux=asf,dst=\"%s\"}"), szPath);
	vlc_argv[vlc_argc++] = szName;
	
	m_pVlcInst2 = libvlc_new(vlc_argc, vlc_argv);
	m_pVlcMedia2 = libvlc_media_new_location(m_pVlcInst2, iPlayPath);
	m_pVlcMediaPlayer2 = libvlc_media_player_new_from_media(m_pVlcMedia2);
	libvlc_media_player_play(m_pVlcMediaPlayer2);
	
	SetTimer(m_hOSDWnd, 1001, 1000, NULL);
	m_bRecording = TRUE;
	return m_bRecording;
}

VOID CVlcWnd::DrawOSD(LPVOID pGraph)
{

}
//�ڿ�ʼ��Ⱦ͸������ǰ,����׼������
VOID CVlcWnd::InitOSD()
{
	m_hOSDWnd = CreateDialogParam(::AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDD_POPUP), iParentWnd->GetSafeHwnd(), OsdWndProc, (LPARAM)this);
	HINSTANCE	hFuncInst;
	
	//��dll�г�ȡһ��δ������win32 api
	hFuncInst	= LoadLibrary(_T("User32.DLL")); 
	if(hFuncInst) 
		UpdateLayeredWindow=(MYFUNC)GetProcAddress(hFuncInst, "UpdateLayeredWindow");
	
	//���ô�����ʽ, ʹ���ڲ�������Ϣ(WM_PAINT����)
	DWORD dwExStyle;
	dwExStyle = GetWindowLong( m_hOSDWnd, GWL_EXSTYLE );
	SetWindowLong(m_hOSDWnd, GWL_EXSTYLE, dwExStyle|WS_EX_TRANSPARENT|WS_EX_LAYERED);
	m_Blend.BlendOp				= AC_SRC_OVER ;		
	m_Blend.BlendFlags			= 0;		
	m_Blend.AlphaFormat			= AC_SRC_ALPHA;
	m_Blend.SourceConstantAlpha	= 255;
	
	::SetWindowPos(m_hOSDWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOACTIVATE);   
	/*
	HINSTANCE hInst = ::AfxGetApp()->m_hInstance;
	HRSRC hRsrc = ::FindResource (hInst, MAKEINTRESOURCE(IDR_PNG1), "PNG"); // type
	if (!hRsrc)
	{
		printlog(_T("%s(%d) : error %d:\n"),__FILE__, __LINE__, GetLastError());
		return;
	}
	
	// load resource into memory
	DWORD len		= SizeofResource(hInst, hRsrc);
	BYTE* lpRsrc	= (BYTE*)::LoadResource(hInst, hRsrc);
	if ( !lpRsrc )
		return;
	
	// Allocate global memory on which to create stream
	HGLOBAL		m_hMem	= GlobalAlloc(GMEM_FIXED, len);
	BYTE*		pmem	= (BYTE*)GlobalLock(m_hMem);
	IStream*	pstm	= 0;
	
	memcpy(pmem, lpRsrc, len);
	CreateStreamOnHGlobal(m_hMem, FALSE, &pstm);
	
	// load from stream
	m_pImg = Gdiplus::Image::FromStream(pstm);
	if(!m_pImg)
	{
		printlog(_T("%s(%d) : error %d:\n"), __FILE__, __LINE__, GetLastError());
		return;
	}
	
	// free/release stuff
	GlobalUnlock(m_hMem);
	pstm->Release();
	FreeResource(lpRsrc);*/
}
//������ʾ͸������
VOID CVlcWnd::UpdateDisplay(int Transparent)
{
	//�����ڴ��豸���漰Bitmap
	int nMemBitmapW = 48;
	int nMemBitmapH = 48;
	
	HDC hdcDlgDC	= GetDC(m_hOSDWnd);					//�öԻ������DC
	HDC hdcMemory	= CreateCompatibleDC( hdcDlgDC ) ;	//����һ�����ݵ��ڴ�DC
	HBITMAP hMemBitMap	= CreateCompatibleBitmap(hdcDlgDC, nMemBitmapW, nMemBitmapH);
	SelectObject( hdcMemory, hMemBitMap );
	
	//����͸����
	if(Transparent < 0 || Transparent > 100)	
		Transparent = 100;	//Ĭ����ȫ��͸��
	m_Blend.SourceConstantAlpha = (int)( Transparent * 2.55);//1~255
	
	//��ʼ��Ⱦ
	float fScalePicFactor = 0.5;
	
	//ʹ��GDI+ ���ڴ�DC�ϻ�ͼ
	Gdiplus::Graphics graph(hdcMemory);
	
	if(m_bFlash)
	{
		DrawOSD(&graph);
		m_bFlash = FALSE;
	}
	else
	{
		m_bFlash = TRUE;
	}
	
	//���յĴ�������Ļ��λ��,����С
	SIZE sizeWindow ={ nMemBitmapW, nMemBitmapH } ;	//ȷ�� sizeWindow < m_hdcMemory�Ĵ�С
	
	// :ָ��ԴDC(hdcMemory)�����Ͻ�
	CRect rc;
	iParentWnd->GetWindowRect(&rc);
	POINT ptSrc = {0, 0};
	POINT ptDst = {rc.left - 64, rc.top + 16 };
	UpdateLayeredWindow(m_hOSDWnd, 
		hdcDlgDC,				//�öԻ����DC
		&ptDst, &sizeWindow,	//�öԻ����λ�ü���С
		hdcMemory, &ptSrc,		//�ڴ�DC
		0, &m_Blend,2 );
	
	//������Դ
	graph.ReleaseHDC(hdcMemory);//����Щ���ص��ͷ���Դ�Ƴ�ȥ,���ܻ�õ�.
	::ReleaseDC(m_hOSDWnd,hdcDlgDC);
	
	DeleteObject( hMemBitMap );
	DeleteDC( hdcMemory );
}

BOOL CALLBACK CVlcWnd::VlcWndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	if(uMsg == WM_INITDIALOG)
	{
		CVlcWnd* pThis = (CVlcWnd*)lParam;
		pThis->m_hVlcWnd = hWnd;
		SetWindowLong(hWnd, GWL_USERDATA, lParam);
	}
	
	CVlcWnd* pThis = (CVlcWnd*)GetWindowLong(hWnd, GWL_USERDATA);
	if(pThis)
		return pThis->OnVlcWndMsg(uMsg,wParam,lParam);
	return 0;
	
}

BOOL CVlcWnd::OnVlcWndMsg(UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_ERASEBKGND:
		break;
	case WM_LBUTTONDOWN:
		//return OnLButtonDown(CPoint(LOWORD(lParam), HIWORD(lParam)));
	case WM_MOUSEMOVE:
		//return OnMouseMove(CPoint(LOWORD(lParam), HIWORD(lParam)));
	case WM_LBUTTONUP:
		//return OnLButtonUp(CPoint(LOWORD(lParam), HIWORD(lParam)));
	case WM_DESTROY:
		return 0;
	}
	return 0;
}

BOOL CALLBACK CVlcWnd::OsdWndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	if(uMsg == WM_INITDIALOG)
	{
		CVlcWnd* pThis = (CVlcWnd*)lParam;
		pThis->m_hOSDWnd = hWnd;
		SetWindowLong(hWnd, GWL_USERDATA, lParam);
	}
	
	CVlcWnd* pThis = (CVlcWnd*)GetWindowLong(hWnd, GWL_USERDATA);
	if(pThis)
		return pThis->OnOsdWndMsg(uMsg,wParam,lParam);
	return 0;	
}

BOOL CVlcWnd::OnOsdWndMsg(UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_INITDIALOG:
		{
			CRect rc;
			iParentWnd->GetWindowRect(&rc);
			CRect rcOsd;
			rcOsd.left = rc.left  - 64;
			rcOsd.top = rc.top  + 16;
			rcOsd.right = rcOsd.left + 0;
			rcOsd.bottom = rcOsd.top + 0;
			MoveWindow(m_hOSDWnd, rcOsd.left, rcOsd.top, rcOsd.Width(), rcOsd.Height(), FALSE);
			m_bFlash = TRUE;		
		}
		return TRUE;
	case WM_TIMER:
		UpdateDisplay(60);
		return 0;
	}
	return 0;
}
