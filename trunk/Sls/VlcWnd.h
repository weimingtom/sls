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
	typedef BOOL (WINAPI *MYFUNC)(HWND,HDC,POINT*,SIZE*,HDC,POINT*,COLORREF,BLENDFUNCTION*,DWORD);//�ú�����windows��һ��δ����API
	
	//�ú�����windows��һ��δ����API
	MYFUNC UpdateLayeredWindow;
	
	//������Ϣ�ַ�������
	BOOL OnVlcWndMsg(UINT uMsg,WPARAM wParam,LPARAM lParam);
	BOOL OnOsdWndMsg(UINT uMsg,WPARAM wParam,LPARAM lParam);
	
    //���ڵĻص�����
	static BOOL CALLBACK VlcWndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
	static BOOL CALLBACK OsdWndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);

	
	CString iPlayPath;
	
public:
	VOID DrawOSD(LPVOID pGraph);
	//�ڿ�ʼ��Ⱦ͸������ǰ,����׼������
	VOID InitOSD();
	//������ʾ͸������
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
	// Description	    : ¼��
	// Return type		: BOOL 
	// Argument         : LPTSTR szPath
	virtual BOOL Record(LPTSTR szPath);

	void SetParentWnd(CWnd *aParentWnd);
	void SetPlayPath(CString aPath);
	void Play();
	void Stop();

};
#endif