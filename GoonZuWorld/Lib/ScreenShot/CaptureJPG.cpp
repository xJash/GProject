
//=============================================================================
//
//	CaptureJPG.cpp
//
//	Copyright 2003 Goonzu
//
//=============================================================================

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/timeb.h>
#include <time.h>
#include "ijl.h"
#include "CaptureJPG.h"
#include "Client.h"

BOOL CALLBACK FindGoonzuWindowsProc(HWND hwnd,LPARAM lParam);
//=============================================================================
//  @Name   CaptureJPG()
//! @author jaycee				
//! @date   2004-3-13
//! @return X
//! @brief  Class ������ 
//=============================================================================
CaptureJPG::CaptureJPG(HWND hWnd)
{
	m_hWnd			= hWnd;

	m_ScreenWidth	= GetSystemMetrics(SM_CXSCREEN);
	m_ScreenHeight	= GetSystemMetrics(SM_CYSCREEN);
	m_hOldBitmap = NULL;
	m_hBitmap = NULL;
	m_lpImageData	= NULL;
}

//=============================================================================
//  @Name   ~CaptureJPG()
//! @author jaycee				
//! @date   2004-3-13
//! @brief  Class �Ҹ���
//=============================================================================
CaptureJPG::~CaptureJPG()
{
	//CloseCapture();
}
//=============================================================================
//  @Name   InitCapture()
//! @author jaycee				
//! @date   2004-3-13
//! @brief  �������� �ʱ�ȭ�ϰ� �����Ѵ�.
//=============================================================================
BOOL CaptureJPG::InitCapture()
{

	//EnumWindows(FindGoonzuWindowsProc, (LPARAM)this);	// ������ ������ ����
	
	GetClientRect(GetWindowHandle(), &m_WindowRect);


	//if(m_WindowRect.right > m_ScreenWidth) m_WindowRect.right = m_ScreenWidth;
	//if(m_WindowRect.bottom > m_ScreenHeight) m_WindowRect.bottom = m_ScreenHeight;
	//if(m_WindowRect.top < 0) m_WindowRect.top = 0;
	//if(m_WindowRect.left < 0 ) m_WindowRect.left = 0;

	m_WindowHeight = m_WindowRect.bottom - m_WindowRect.top;
	m_WindowWidth = m_WindowRect.right - m_WindowRect.left;

	memset(m_WorkPath,	0, sizeof(m_WorkPath));
	memset(m_FileName,	0, sizeof(m_FileName));
	memset(m_FullPath,	0, sizeof(m_FullPath));

	return TRUE;
}

//=============================================================================
//  @Name   CloseCapture()
//! @author jaycee				
//! @date   2004-3-13
//! @brief  �������� �����Ѵ�.
//=============================================================================
BOOL CaptureJPG::CloseCapture()
{
	/*
	if(m_lpImageData != NULL) delete []m_lpImageData; 
	m_lpImageData = NULL;

	
	*/
	return TRUE;
}

//=============================================================================
//  @Name   GetFileName()
//! @author jaycee				
//! @date   2004-3-13
//! @brief  �������� ����� �����̸��� ���´�.
//=============================================================================
TCHAR *CaptureJPG::GetFileName()
{
	return m_FullPath;
}

//=============================================================================
//  @Name   CaptureToJPG()
//! @author jaycee				
//! @date   2004-3-13
//! @param  ������ ���α׷��� Instance 
//! @param  Path ����� JPG������ ��� 
//! @brief  �ش� ��η� Primary Screen�� JPG�� ������ �Ѵ�.
//=============================================================================
void CaptureJPG::CaptureToJPG(TCHAR *Path)	//[�����մ�] 2005-12-7
{
	BOOL rval = FALSE;
	int startX = 0,  startY = 0;

	if(InitCapture()==FALSE) return;	// �ʱ�ȭ


	cltClient *pclclient = (cltClient *)pclClient;	// Ŭ���̾�Ʈ ������ ��



	if(GP.LockSurface(pclclient->lpBackScreen)==TRUE)
	{
		pclclient->lpBackScreen->GetDC(&m_hScrDC);
		

		m_hMemDC		= CreateCompatibleDC(m_hScrDC);			//ȭ���� ��� ���� MemDC
		m_hBitmap = CreateCompatibleBitmap(m_hScrDC, m_WindowWidth, m_WindowHeight); // ������ ũ�� ��Ʈ��

		m_hOldBitmap=(HBITMAP)SelectObject(m_hMemDC,m_hBitmap);
		
		
		startX = MAP_TILE_XSIZE + pclclient->GetScreenRX();
		startY = MAP_TILE_YSIZE + pclclient->GetScreenRY();
		rval = BitBlt(m_hMemDC,0,0, m_WindowWidth, m_WindowHeight,m_hScrDC,startX,startY,SRCCOPY);	
			//,m_WindowRect.left,m_WindowRect.top,SRCCOPY);	

		// �޸� ��Ʈ���� �����ϰ� 
		
		//ȭ���� �޸� ��Ʈ������ �����Ѵ�.
		//CollectWindows();
			
		if(!rval) return;

		// fill .bmp - structures
		BITMAPINFO bmInfo;
		bmInfo.bmiHeader.biSize			= sizeof(BITMAPINFOHEADER);
		bmInfo.bmiHeader.biWidth		= m_WindowWidth;
		bmInfo.bmiHeader.biHeight		= m_WindowHeight;
		bmInfo.bmiHeader.biPlanes		= 1;
		bmInfo.bmiHeader.biBitCount		= 24;
		bmInfo.bmiHeader.biCompression	= BI_RGB;
		bmInfo.bmiHeader.biSizeImage	= 0;
		bmInfo.bmiHeader.biXPelsPerMeter= 0;
		bmInfo.bmiHeader.biYPelsPerMeter= 0;
		bmInfo.bmiHeader.biClrUsed		= 0;
		bmInfo.bmiHeader.biClrImportant = 0;

		SelectObject(m_hMemDC,m_hOldBitmap);
		
		//�޸� �Ҵ�
		m_lpImageData = GlobalAlloc(GMEM_FIXED,m_WindowWidth * m_WindowHeight * 3 + bmInfo.bmiHeader.biSize);
		

		// copy bitmap data into memory
		GetDIBits(m_hMemDC, m_hBitmap, 0, m_WindowHeight, m_lpImageData, &bmInfo, DIB_RGB_COLORS);
		

		// Make Full Path Name
		MakeFullPathName(Path);
		// Savt as to JPG
			
		SaveAsJPEG();

		//�޸� ����
		GlobalFree(m_lpImageData);

		pclclient->lpBackScreen->ReleaseDC(m_hScrDC);
		GP.UnlockSurface(pclclient->lpBackScreen);
	}

	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);
	DeleteDC(m_hScrDC);

}

//=============================================================================
//  @Name   SaveAsJPEG()
//! @author jaycee				
//! @date   2004-3-13
//! @return JPG ������ ��������
//! @brief  JPG ���Ϸ� �ش� Image�� �����Ѵ�.
//=============================================================================
BOOL CaptureJPG::SaveAsJPEG()
{
	JPEG_CORE_PROPERTIES image;
	ZeroMemory( &image, sizeof( JPEG_CORE_PROPERTIES ) );


	if( ijlInit( &image ) != IJL_OK )
	{
		return FALSE;
	}

	// Setup DIB
	image.DIBWidth      = m_WindowWidth;
	image.DIBHeight     = -m_WindowHeight;
	image.DIBBytes      = (BYTE *)m_lpImageData;

	
	
#ifndef _UNICODE
	TCHAR strDest[MAX_PATH];
	StringCchCopy(strDest, MAX_PATH, m_FullPath);
#else
	char strDest[MAX_PATH];
	WideCharToMultiByte(CP_ACP,0,m_FullPath,-1,strDest, MAX_PATH,NULL,NULL);	
#endif

	// Setup JPEG
	image.JPGFile       = strDest;		// ���� ��ο� �����̸�
	image.JPGWidth      = m_WindowWidth;
	image.JPGHeight     = m_WindowHeight;

	image.DIBColor      = IJL_BGR;
	image.DIBChannels   = 3;
	image.DIBPadBytes   = IJL_DIB_PAD_BYTES(image.DIBWidth,3);
	image.JPGColor      = IJL_YCBCR;
	image.JPGChannels   = 3;
	image.JPGSubsampling= IJL_411;
	image.jquality		= 100;					// Default 75 �μ� 100�� �ʹ� ������ ũ��. ���� �𸣰ڴ�.

	if( ijlWrite( &image, IJL_JFILE_WRITEWHOLEIMAGE ) != IJL_OK )
	{
		ijlFree( &image );
		return FALSE;
	}

	if( ijlFree( &image ) != IJL_OK )
	{
		return FALSE;
	}

	return TRUE;
}

//=============================================================================
//  @Name   FindGoonzuWindowsProc()
//! @author jaycee				
//! @date   2004-3-13
//! @param  hwnd
//! @param  lParam
//! @brief  EnumWindows�Լ��� �����츦 ã�� ������ �� ������ �Ѱ��ش�.
//=============================================================================
BOOL CALLBACK FindGoonzuWindowsProc(HWND hwnd,LPARAM lParam)
{
	CaptureJPG *pCapture = (CaptureJPG *) lParam;

	if((pCapture->GetWindowHandle()  == hwnd || 
		pCapture->GetWindowHandle() == (HWND)GetWindowLong(hwnd, GWL_HWNDPARENT))
		&& IsWindowVisible(hwnd))
	{
		GetClientRect(hwnd, &pCapture->m_WindowRect);

	}

	return TRUE;
}
//=============================================================================
//  @Name   CollectWindows()
//! @author jaycee				
//! @date   2004-3-13
//! @param  FullPathName�� ������ ���
//! @brief  JPG ���Ϸ� �ش� Image�� �����Ѵ�.
//=============================================================================
void CaptureJPG::CollectWindows()
{

	// FULL DISPLAY 
	//BitBlt(m_hMemDC,0,0,m_ScreenWidth,m_ScreenHeight,m_hScrDC,0,0,SRCCOPY);	

/*
	memset(m_lpImageData, 0, m_WindowWidth * m_WindowHeight * 3);
	BitBlt(m_hMemDCWinsize,0,0, m_WindowWidth, m_WindowHeight,m_hScrDC,m_WindowRect.left,m_WindowRect.top,SRCCOPY);	

	//memset(m_RT,	0, sizeof(m_RT));
	//m_RTCount	= 0;
	//SystemParametersInfo(SPI_GETWORKAREA, NULL, &m_ScRT, NULL);
	//===========================

	//BitBlt(m_hMemDC,0,0, m_ScreenWidth, m_ScreenHeight,m_hScrDC,0,0,BLACKNESS);	
	
	RECT rt;
	int  width, height;
	for(int i=0; i < m_RTCount;	++i)
	{
	rt = m_RT[i];
	if(rt.left>rt.right){m_RT[i].right  = rt.left;	m_RT[i].left = rt.right;}
	if(rt.top>rt.bottom){m_RT[i].bottom = rt.top;	m_RT[i].top  = rt.bottom;}

	rt.left		= __max(rt.left,	0);
	rt.left		= __max(rt.left,	m_ScRT.left);
	rt.left		= __min(rt.left,	m_ScRT.right);
	rt.left		= __min(rt.left,	m_ScreenWidth);

	rt.top		= __max(rt.top,		0);	
	rt.top		= __max(rt.top,		m_ScRT.top);	
	rt.top		= __min(rt.top,		m_ScRT.bottom);
	rt.top		= __min(rt.top,		m_ScreenHeight);

	rt.right	= __max(rt.right,	0);	
	rt.right	= __max(rt.right,	m_ScRT.left);	
	rt.right	= __min(rt.right,	m_ScRT.right);
	rt.right	= __min(rt.right,	m_ScreenWidth);

	rt.bottom	= __max(rt.bottom,	0);	
	rt.bottom	= __max(rt.bottom,	m_ScRT.top);	
	rt.bottom	= __min(rt.bottom,	m_ScRT.bottom);
	rt.bottom	= __min(rt.bottom,	m_ScreenHeight);

	width = rt.right-rt.left;	height= rt.bottom-rt.top;
	if(width<=0 ||height<=0) continue;

	BitBlt(m_hMemDC,rt.left,rt.top, width, height,m_hScrDC,rt.left,rt.top,SRCCOPY);	
	}
	*/
	
}

//=============================================================================
//  @Name   MakeFullPathName()
//! @author jaycee				
//! @date   2004-3-13
//! @param  FullPathName�� ������ ���
//! @brief  JPG ���Ϸ� �ش� Image�� �����Ѵ�.
//=============================================================================
void CaptureJPG::MakeFullPathName(TCHAR *Path)
{
	// Path, FileName 
	if(Path != NULL)
	{
		StringCchCopy(m_WorkPath, MAX_PATH, Path);
		int Length = _tcslen(m_WorkPath);
		if(m_WorkPath[Length-1] != '\\')	StringCchCat(m_WorkPath, MAX_PATH, TEXT("\\"));
	}
	else
	{
			StringCchCopy(m_WorkPath, MAX_PATH, TEXT("Screenshot\\"));
			DWORD dwAttr;
			if((dwAttr = GetFileAttributes(m_WorkPath)) == (DWORD)-1)
			{// ���丮�� ������ �������� ����. ���� ���丮�� ������
				CreateDirectory(m_WorkPath,NULL);
			}
			else if(!(dwAttr & FILE_ATTRIBUTE_DIRECTORY))
			{// �ش� ������ ���丮�� �ƴϹǷ�
				StringCchCopy(m_WorkPath, MAX_PATH, TEXT("Screenshot_\\"));
				CreateDirectory(m_WorkPath,NULL);
			}			
	}

	time_t ltime;
	struct tm *today;
	time( &ltime );
	today = localtime( &ltime );
	struct _timeb tstruct;
	_ftime( &tstruct );

	
	if(pclClient->siServiceArea == ConstServiceArea_Japan)
	{
		StringCchPrintf(m_FileName, MAX_PATH, TEXT("Kunshu(%04d%02d%02d_%02d%02d%02d.%03hu).jpg"), 
			today->tm_year+1900,today->tm_mon+1,today->tm_mday,
			today->tm_hour,today->tm_min,
			today->tm_sec, tstruct.millitm);
	}
	else if(pclClient->siServiceArea == ConstServiceArea_English)
	{
		StringCchPrintf(m_FileName, MAX_PATH, TEXT("GoonZu(%04d%02d%02d_%02d%02d%02d.%03hu).jpg"), 
			today->tm_year+1900,today->tm_mon+1,today->tm_mday,
			today->tm_hour,today->tm_min,
			today->tm_sec, tstruct.millitm);
	}
	else if(pclClient->siServiceArea == ConstServiceArea_NHNChina)
	{
		StringCchPrintf(m_FileName, MAX_PATH, TEXT("GoonZu(%04d%02d%02d_%02d%02d%02d.%03hu).jpg"), 
			today->tm_year+1900,today->tm_mon+1,today->tm_mday,
			today->tm_hour,today->tm_min,
			today->tm_sec, tstruct.millitm);
	}
	else if(pclClient->siServiceArea == ConstServiceArea_EUROPE)
	{
		StringCchPrintf(m_FileName, MAX_PATH, TEXT("GoonZu(%04d%02d%02d_%02d%02d%02d.%03hu).jpg"), 
			today->tm_year+1900,today->tm_mon+1,today->tm_mday,
			today->tm_hour,today->tm_min,
			today->tm_sec, tstruct.millitm);
	}
	else
	{
		StringCchPrintf(m_FileName, MAX_PATH, TEXT("(%04d%02d%02d_%02d%02d%02d.%03hu).jpg"), 
			today->tm_year+1900,today->tm_mon+1,today->tm_mday,
			today->tm_hour,today->tm_min,
			today->tm_sec, tstruct.millitm);
	}


	StringCchCopy(m_FullPath, MAX_PATH, m_WorkPath);
	StringCchCat(m_FullPath, MAX_PATH, m_FileName);
}