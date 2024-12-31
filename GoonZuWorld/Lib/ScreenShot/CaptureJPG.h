
//=============================================================================
//
//	CaptureJPG.h
//
//	Copyright 2003 Goonzu
//
//=============================================================================

#ifndef __CAPTUREJPG_H__
#define __CAPTUREJPG_H__

#define MAX_CAPTUREJPG_WINDOW	100

class CaptureJPG
{
private:
	HDC		m_hMemDC,m_hScrDC;
	HBITMAP m_hOldBitmap;
	HBITMAP	m_hBitmap;   // ������ ũ���� ��Ʈ��
	HWND	m_hWnd;
	RECT	m_ScRT;

	int		m_ScreenWidth;		// Primary Screen ũ��
	int		m_ScreenHeight;		// Primary Screen ũ��

	int		m_WindowWidth;
	int		m_WindowHeight;


	void	*m_lpImageData;		// Image DATA

	TCHAR	m_WorkPath[MAX_PATH];	// ������ ������ Working Folder
	TCHAR	m_FileName[MAX_PATH];	// ����� File �̸� 
	TCHAR	m_FullPath[MAX_PATH];	// ����� File�� FullPath �̸� 
public:
	//RECT	m_RT[MAX_CAPTUREJPG_WINDOW];
	//int		m_RTCount;
	RECT	m_WindowRect;
public:
	CaptureJPG(HWND hWnd = NULL);
	~CaptureJPG();

	void	CaptureToJPG(TCHAR *Path=NULL);	// PRIMARY SCREEEN�� �ش� ��ο� JPG ���Ϸ� �����Ѵ�.
	TCHAR   *GetFileName();
	HWND	GetWindowHandle()	{return m_hWnd;	};

private:
	BOOL	InitCapture();					// Capture�� ������ ����ϱ� ���ؼ� �̸� �ʱ�ȭ �صд�.
	BOOL	CloseCapture();					// �������� �����Ѵ�.
	BOOL	SaveAsJPEG();					// �����Ȱ����� JPG���Ϸ� �����Ѵ�.
	void	CollectWindows();
	void	MakeFullPathName(TCHAR *Path);	// ����� FullPathName�� �����Ѵ�.
};


#endif