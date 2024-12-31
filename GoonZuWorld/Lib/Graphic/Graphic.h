//---------------------------------
// 2003/9/21 ���°�
//---------------------------------

#ifndef _GRAPHIC_H
#define _GRAPHIC_H

#include <directives.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include <ddraw.h>


#include "../../Lib/EtcTool/EtcTool.h"

#include "../NGraphics/Graphics.h"

class NGraphics;
extern NGraphics g_graphics;

#define MAX_DISPLAYMODE_NUM		200		// �׷��� ī�尡 ���� �� �ִ� ȭ�� ����� �ִ� ����. 

//------------------------
// ����ܰ� 
//------------------------
#define MAX_LIGHT_STEP			10			// ���� �ܰ�.
#define MAX_DARK_STEP			32			// ��ο� �ܰ�. 

//------------------------
// ������ 
//------------------------
#define COLOR_BLACK				0				// ������
#define COLOR_WHITE				255				// ���. 
#define COLOR_TRANS				254				// ����� 


//------------------------
// ȭ�� ��� ����  
//------------------------
#define MODE_GRAPHICS640_480     1
#define MODE_GRAPHICS800_600     2
#define MODE_GRAPHICS1024_768    3
#define MODE_GRAPHICS1280_1024   4
// KHY - 1218 - 1024x600 �ػ� �߰�. imsi
#define MODE_GRAPHICS1024_600   5


//-------------------------
// ���ǽ� ���� 
//-------------------------
#define SURFACE_PRIMARY			0
#define SURFACE_BACK			1



class cltGrp {
public:
	HWND	hWnd;				// ������ �ڵ�

	int ScreenMode;
    int ScreenXsize;
    int ScreenYsize;
    int ColorDepth;
    int SurfaceWidth, SurfaceHeight;
    int nDisplayModes;

    bool bLockSwitch;			// Surface�� ��� �ִ°� ?

    int ClipX1, ClipY1, ClipX2, ClipY2;
	RECT ClipRect;
    int YOFF[1024];
	

    LPDIRECTDRAWPALETTE     lpDDPal;        // Direct Draw Palette

public:
    LPDIRECTDRAWCLIPPER lpClipper;  


public:


	LPDIRECTDRAWSURFACE7   lpDDSConvertSurface;

	RECT   m_rcWindow;

    UI08 *Screen8;
	
    LPDIRECTDRAW7           lpDD7; 
    LPDIRECTDRAWSURFACE7     lpDDSPrimary;   // DirectDraw primary surface
    LPDIRECTDRAWSURFACE7     lpDDSBack;      // DirectDraw back surface
	
    DDSURFACEDESC2   SurfaceDesc;
    PALETTEENTRY PalEntries[256];
    
//	UI16 TempPaletteTable[256];

    UI08 Palette[768];
    UI08 CurrentPal[768];   // ���� Ȱ��ȭ �Ǿ� �ִ� �ȷ�Ʈ�� �����Ѵ�. 
    UI08 OriginalPal[768];
	
    // 16��Ʈ�� �ȷ�Ʈ�� �����Ѵ�. 
    UI08	Palette16[64][64][64];
    UI08	PaletteRGB[256][3];
    
	
	SI32 ScreenFlag;

	int GetScreenMode()   { return ScreenMode; }
	int GetScreenXsize()  { return ScreenXsize; }
	int GetScreenYsize()  { return ScreenYsize; }
	void SetScreenXsize(int xsize) { ScreenXsize = xsize; }
	void SetScreenYsize(int ysize) { ScreenYsize = ysize; }
	int GetColorDepth()   { return ColorDepth; }
	int GetSurfaceWidth() { return SurfaceWidth; }
	
	
	// ������ �Լ� 
	cltGrp();
	
	/////////////////////////////////////////////////////////////////
	//  ��Ÿ ó���Լ� 
	////////////////////////////////////////////////////////////////
	BOOL Error(TCHAR * szCaption);
	
    // ���ǽ��� ���Ѵ�. 
    // surface: ���ǽ� ��� SURFACE_PRIMARY, SURFACE_BACK
    BOOL LockSurface(int surface);
	
    // ���ǽ��� ����Ѵ�. 
    // surface: ���ǽ� ��� SURFACE_PRIMARY, SURFACE_BACK
    BOOL UnlockSurface(int surface);
	
    BOOL LockSurface(LPDIRECTDRAWSURFACE7 pSurface);
    BOOL UnlockSurface(LPDIRECTDRAWSURFACE7 pSurface);
	
	// ȭ���� ������ �����.
    BOOL	ClearSurface(LPDIRECTDRAWSURFACE7 pSurface);

	// ���̷�Ʈ ��ο� ���ǽ��� �ƴ϶� ������ �޸𸮸� ���ؼ� �� �� �ֵ��� �����. 
    BOOL LockSurface(UI08*, int xsize, int ysize);

    
	//-----------------------------
	// ȭ�� ��� ����. 
	//-----------------------------
	// ȭ�� ��带 �߰��Ѵ�. 

	
	
	void GetClipArea( int& x1, int &y1, int &x2, int &y2);
    void SetClipArea( int x1,  int y1,  int x2,  int y2);
	
	// ��ü ȭ���� Ŭ���� �������� �����Ѵ�. 
	void SetClipFullScreen();
	
    BOOL IsInClipArea(int x1, int y1, int x2, int y2);
	int GetClipRect(RECT* rect);
	BOOL FitToClipArea(int sx1, int sy1, int sx2, int sy2, int& dx1, int& dy1, int& dx2, int& dy2);


	
	void WaitForVerticalBlank();
	
	// �ջ�� ���� �����Ѵ�. 
	void Restore();
	
	void UpdateScreen(HWND hwnd, LPDIRECTDRAWSURFACE7 pSurface, 
		              SI32 xsize, SI32 ysize, SI32 xindent, SI32 yindent, 
					  SI32 srcstartx, SI32 srcstarty, bool bwaitrefresh, 
					  SI32 screenXSize, SI32 screenYSize , bool bWebDlg = false, HWND hWebDlg = NULL,
					  bool bNewFullScreen = false );
	
	// ������ ������ ���´�. 
	void GetSprRandPos8T(int x, int y, int xsize, int ysize, unsigned char *image, SI32* pgetnum, POINT* ppoint);
	// ������ ������ ���´�. 
	void GetSprRandPos8RT(int x, int y, int xsize, int ysize, unsigned char *image, SI32* pgetnum, POINT* ppoint);
	// ������ ������ ���´�. (��)
	void GetSprRandPos8TH(int x, int y, int xsize, int ysize, unsigned char *image, SI32* pgetnum, POINT* ppoint);
	// ������ ������ ���´�. (��)
	void GetSprRandPos8RTH(int x, int y, int xsize, int ysize, unsigned char *image, SI32* pgetnum, POINT* ppoint);

public:

	HRESULT BltFast(DWORD surface,  DWORD dwX,  DWORD dwY,                            
		LPDIRECTDRAWSURFACE7 lpDDSrcSurface,  LPRECT lpSrcRect, DWORD dwTrans );

};

//static HRESULT CALLBACK EnumDisplayModesCallBack(LPDDSURFACEDESC2 pddsd, LPVOID Context);

extern		cltGrp clGrp;


inline BOOL cltGrp::LockSurface(UI08* buffer, int xsize, int ysize)
{
	Screen8 = (UI08*) buffer;
	
	SurfaceWidth =xsize;
	
	SurfaceHeight=ysize;
	
	return TRUE;
}

// ���ǽ��� ���Ѵ�. 
// surface: ���ǽ� ��� SURFACE_PRIMARY, SURFACE_BACK
inline BOOL cltGrp::LockSurface(int surface)
{
	switch(surface)
	{
	case SURFACE_PRIMARY:
		return LockSurface( lpDDSPrimary );
		break;
	case SURFACE_BACK:
		return LockSurface( lpDDSBack );
		break;
	default:
		MsgBox(TEXT("LockSurface"), TEXT("fd3ff"));

	}

	return TRUE;
}

// ���ǽ��� ����Ѵ�. 
// surface: ���ǽ� ��� SURFACE_PRIMARY, SURFACE_BACK
inline BOOL cltGrp::UnlockSurface(int surface)
{
	switch(surface)
	{
	case SURFACE_PRIMARY:
		return UnlockSurface( lpDDSPrimary );
		break;
	case SURFACE_BACK:
		return UnlockSurface( lpDDSBack );
		break;
	default:
		MsgBox(TEXT("UnlockSurface"), TEXT("f3rfssa"));

	}
	return TRUE;
}

////////////////////////////////////////////////////////
///  Surface ��ü�� lock���Ѽ� �׸��� �׸� �� �ְ� �Ѵ�.
////////////////////////////////////////////////////////
inline BOOL cltGrp::LockSurface(LPDIRECTDRAWSURFACE7 pSurface)
{
	BOOL success = FALSE;
	HRESULT result;

	ZeroMemory( &SurfaceDesc, sizeof( SurfaceDesc ) );
	SurfaceDesc.dwSize=sizeof( SurfaceDesc );

	if( bLockSwitch == true)
	{
		MsgBox( TEXT("Locked"), TEXT("fds3ff"));
	    return FALSE;
	}

	bLockSwitch = true;

	BOOL exitloop = FALSE;

	do
	{
		result = pSurface->Lock( NULL, &SurfaceDesc, DDLOCK_WAIT, NULL );

		if( result == DDERR_SURFACELOST )
		{
			pSurface->Restore();
		}

		else if( result != DDERR_WASSTILLDRAWING )
		{
			exitloop=TRUE;
		}
	}
	while( ! exitloop );

	if( result == DD_OK )
	{
		Screen8 = (UI08*) SurfaceDesc.lpSurface;

	    SurfaceWidth = SurfaceDesc.lPitch / ( ColorDepth / 8 );
		SurfaceHeight = SurfaceDesc.dwHeight;

		return TRUE;
	}
	else
	{
	    MsgBox(TEXT("LockSurface"), TEXT("Error"));
		
		if(result==DDERR_SURFACEBUSY)
		{
			MsgBox(TEXT("SurfaceBusy"), TEXT("dsa2ds"));
		}
	}

	return FALSE;
}

////////////////////////////////////////////////////////////////
// Lock�� �� ��ü�� Ǯ���ش�.
////////////////////////////////////////////////////////////////
inline BOOL cltGrp::UnlockSurface(LPDIRECTDRAWSURFACE7 pSurface)
{
	if(bLockSwitch == true)
	{
		bLockSwitch = false;
	}
	else
	{
		MsgBox(TEXT("Unlocked"), TEXT("sf3fdf"));
	}
	
	pSurface->Unlock(NULL);
	return TRUE;
}

inline void cltGrp::GetClipArea(int&x1, int &y1, int&x2, int&y2)
{
	x1=ClipX1;
	y1=ClipY1;
	x2=ClipX2;
	y2=ClipY2;
}

inline int cltGrp::GetClipRect(RECT* rect)
{
	rect->left   = ClipX1;
	rect->right  = ClipX2;
	rect->top    = ClipY1;
	rect->bottom = ClipY2;

	return 0;
}

inline void cltGrp::SetClipArea(int x1, int y1, int x2, int y2)
{
	ClipX1=x1;
	ClipX2=x2;
	ClipY1=y1;
	ClipY2=y2;
}

inline void cltGrp::SetClipFullScreen()
{
	ClipX1 = 0;
	ClipX2 = ScreenXsize-1;
	ClipY1 = 0;
	ClipY2 = ScreenYsize-1;
}

inline BOOL cltGrp::IsInClipArea(int x1, int y1, int x2, int y2)
{
	if(ClipX1 <= x1 && x2 <= ClipX2 && ClipY1 <= y1 && y2 <= ClipY2 )
		return TRUE;
	
	return FALSE; 
}

inline BOOL cltGrp::FitToClipArea(int sx1, int sy1, int sx2, int sy2, int& dx1, int& dy1, int& dx2, int& dy2)
{
	dx1=max(sx1, ClipX1);
	dx2=min(sx2, ClipX2);
	dy1=max(sy1, ClipY1);
	dy2=min(sy2, ClipY2);
	return TRUE;
}

inline void cltGrp::Restore()
{
	if(lpDD7)
	{
		 lpDD7->RestoreAllSurfaces();
	}
}



#endif

