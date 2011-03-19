#ifndef VLC_WND_H_
#define VLC_WND_H_
#include <vlc/vlc.h>
class CVlcWnd
{
public:
	CVlcWnd();
	virtual ~CVlcWnd();
private:
	libvlc_instance_t *m_pVlcInst;
	libvlc_media_player_t *m_pVlcMediaPlayer;
	libvlc_media_t *m_pVlcMedia;
	
	libvlc_instance_t *m_pVlcInst2;
	libvlc_media_player_t *m_pVlcMediaPlayer2;
	libvlc_media_t *m_pVlcMedia2;
	CWnd *iParentWnd;
	HWND m_hVlcWnd;
	HWND m_hOSDWnd;
	BOOL m_bFlash;
	BOOL m_bRecording;
	float m_fZoom;
	BLENDFUNCTION m_Blend;
	typedef BOOL (WINAPI *MYFUNC)(HWND,HDC,POINT*,SIZE*,HDC,POINT*,COLORREF,BLENDFUNCTION*,DWORD);//该函数是windows的一个未公开API
	
	//该函数是windows的一个未公开API
	MYFUNC UpdateLayeredWindow;
	
	//窗口消息分发处理函数
	BOOL OnVlcWndMsg(UINT uMsg,WPARAM wParam,LPARAM lParam);
	BOOL OnOsdWndMsg(UINT uMsg,WPARAM wParam,LPARAM lParam);
	
    //窗口的回调函数
	static BOOL CALLBACK VlcWndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
	static BOOL CALLBACK OsdWndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);

	
	CString iPlayPath;
	
public:
	VOID DrawOSD(LPVOID pGraph);
	//在开始渲染透明窗口前,做好准备工作
	VOID InitOSD();
	//更新显示透明窗口
	VOID UpdateDisplay(int Transparent=100);
	virtual VOID Show(BOOL bShow);
	
	// Function name	: ZoomIn
	// Description	    : 
	// Return type		: BOOL 
	virtual BOOL ZoomIn();
	
	// Function name	: ZoomOut
	// Description	    : 
	// Return type		: BOOL 
	virtual BOOL ZoomOut();
	
	// Function name	: ZoomNormal
	// Description	    : 
	// Return type		: BOOL 
	virtual BOOL ZoomNormal();
	
	// Function name	: Capture
	// Description	    : 
	// Return type		: BOOL 
	// Argument         : LPTSTR szPath
	virtual BOOL Capture(LPTSTR szPath);
	
	// Function name	: Record
	// Description	    : 录像
	// Return type		: BOOL 
	// Argument         : LPTSTR szPath
	virtual BOOL Record(LPTSTR szPath);

	void SetParentWnd(CWnd *aParentWnd);
	void SetPlayPath(CString aPath);
	void Play();
	void Stop();

};
#endif