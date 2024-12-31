//---------------------------------
// 2004/11/15 ���ؿ�
//---------------------------------

#ifndef _GRCAPSULE_H
#define _GRCAPSULE_H

#include <Directives.h>

#include "../../Lib/Graphic/Graphic.h"

#include "../../Lib/EtcTool/EtcTool.h"

#include "TSpr.h"

#define SPR_MODE_T			0
#define SPR_MODE_CT			1
#define SPR_MODE_RT			2
#define SPR_MODE_CRT		3

#define PUT_SPR_SPR			1
#define PUT_SPR_SHADOW		2
#define PUT_SPR_LIGHT		3
#define PUT_SPR_LIGHT1		4
#define PUT_SPR_ADD			5
#define PUT_SPR_SCREEN		6
#define PUT_SPR_MULTIPLY	7
#define PUT_SPR_ALPHA		8


///////////////////////////
// PCX ���� 
///////////////////////////
struct PCXPAL {
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

class _head
{
public:
	char maker;
	char  ver;
	char encode;
	char bpp;

	short int xmin,ymin;
	short int xmax,ymax;		//!!���� ���� �ִ밪
	short int hres,vres;		//!!���� ���� �ػ�

	char palette[48];

	char  vmode;
	char  nplanes;

	short int bpl;			//!!�� �ٴ� �� ����Ʈ ..
	short int palette_type;
	short int shres;			//!!�ػ�  ���� hres
	short int svres;			//!!�ػ�  ���� vres

	char unused[54];
};

class _tail 
{
public:
	char identification;          
	unsigned char palette[768];    //!!�ȷ�Ʈ..
};

struct PCX 
{
	_head Head;
	_tail Tail;

	unsigned char *Image;
};



class cltGraphic_Capsule{
public:
	cltGraphic_Capsule();
	~cltGraphic_Capsule();

	void PutSpr( TSpr *pSpr, int x, int y, int font = 0, BOOL bReverse = FALSE );
	void PutSprMultiply( TSpr *pSpr, int x, int y, int font = 0, BOOL bReverse = FALSE );
	void PutSprScreen( TSpr *pSpr, int x, int y, int font = 0, BOOL bReverse = FALSE );
	void PutSprAdd( TSpr *pSpr, int x, int y, int font = 0, BOOL bReverse = FALSE );
	void PutSprLight( TSpr *pSpr, int x, int y, int font = 0, BOOL bReverse = FALSE );
	void PutSprLight1( TSpr *pSpr, int x, int y, int font = 0, BOOL bReverse = FALSE );
	void PutSprShadow( TSpr *pSpr, int x, int y, int font = 0, BOOL bReverse = FALSE );
	void PutSprAlpha( TSpr *pSpr, int x, int y, int alpha, int font = 0, BOOL bReverse = FALSE );

	// ��������Ʈ ȸ��, Ȯ��/���
	void PutSprRS( TSpr *pSpr, int x, int y, int font = 0, BOOL bReverse = FALSE, FLOAT fRotateDegree = 0.0f, FLOAT fScale = 1.0f );
	void PutSprAlphaRS( TSpr *pSpr, int x, int y, int alpha, int font = 0, BOOL bReverse = FALSE, FLOAT fRotateDegree = 0.0f, FLOAT fScale = 1.0f );

	SI32 DrawNumber( TSpr *pSpr, int x, int y, int startfont, int num );
	SI32 DrawNumber( TSpr *pSpr, int x, int y, int startfont, int num, int nDigit );

	void PutSprEF( TSpr *pSpr, int x, int y, int effect, int font = 0, BOOL bReverse = FALSE );
	void PutMpr( TSpr *pSpr, int x, int y, int mprmode, BOOL cmmode, int font = 0, int alpha = 8 );


	void PutSpr(SI32 x, SI32 y, SI32 xsize, SI32 ysize, UI08* image, 
				SI16 putspr, SI16 sprmode );

	void PutMpr(SHORT x, SHORT y, SHORT xsize, SHORT ysize, UI08* image,
				SI16 mprmode,BOOL bCMmode,SI32 alphavalue = 4);

	// ������ ������ ���´�. 
	void GetSprRandPos8(int x, int y, int xsize, int ysize,
						unsigned char *image, SI32* pgetnum, POINT* ppoint,BOOL bRTmode);
	// ������ ������ ���´�. (��)
	void GetSprRandPos8H(int x, int y, int xsize, int ysize,
						unsigned char *image, SI32* pgetnum, POINT* ppoint,BOOL bRTmode);

	void FillScreen(unsigned char color);

	void Line(int x1, int y1, int x2, int y2, unsigned char color,BOOL bx2mode);

	void FillBox(int x1, int y1, int x2, int y2, unsigned char color,BOOL b32mode);
	void Box(int x1, int y1, int x2, int y2, unsigned char color);

	void PutImage(int x,int y,int xsize,int ysize, unsigned char *image,BOOL b32mode);
	void PutSpr(SI32 x, SI32 y, SI32 xsize, SI32 ysize, UI08* image);

	void GetImage(SI32 x, SI32 y, SI32 xsize, SI32 ysize, UI08* buffer);

	void PutXpr16( SI32 x, SI32 y, SI32 xsize, SI32 ysize, RGB16* image, RGB16 colorkey );
	void PutXpr16A( SI32 x, SI32 y, SI32 xsize, SI32 ysize, RGB16* image, int alpha, RGB16 colorkey );

	void PutSpr16EF( SI32 x, SI32 y, SI32 xsize, SI32 ysize, UI08* image, int effect, BOOL bReverse );

	// ��������Ʈ�� Ư�� ��ġ ���� �����´�.
	BYTE GetSprColor( TSpr *pSpr, SI32 x, SI32 y, SI32 font, bool bReverse );

	//------------------------------------------------
	// Spr ����		
	//------------------------------------------------

	int SavePCX(PCX & pcx, TCHAR *filename);
	void record(int count, unsigned char color, FILE* fp);


	BOOL LoadSprFromFile( TCHAR *filename, TSpr *pSpr );
	BOOL LoadSprFromMemory( BYTE* pMemory, TSpr *pSpr );
	BOOL LoadTileFromFile( TCHAR *filename, TSpr *pSpr );
	BOOL FreeSpr( TSpr& spr );

	BOOL EncodeSpr(UI08* dest, UI08* src, int xsize, int ysize, UI08 colorkey);
	BOOL EncodeMpr(UI08* dest, UI08* src, int xsize, int ysize, UI08 colorkey);

public:
	BOOL InitGP(HWND hwnd,SI32 screenmode,LPDIRECTDRAWSURFACE7 & lpbackscreen,SI32 xsize , SI32 ysize, BOOL bFullScreen = FALSE, SI32 screenXSize = 0, SI32 screenYSize = 0, bool bNewFullScreen = false );
	void ReleaseGP();

	void SetClipArea(SI32 x1,SI32 y1,SI32 x2,SI32 y2 );
	void GetClipArea( int& x1, int &y1, int &x2, int &y2 );

	void SetClipFullScreen();

    BOOL IsInClipArea(int x1, int y1, int x2, int y2);
	int GetClipRect(RECT* rect);
	BOOL FitToClipArea(int sx1, int sy1, int sx2, int sy2, int& dx1, int& dy1, int& dx2, int& dy2);

	BOOL CreateSurface(LPDIRECTDRAWSURFACE7 & pSurface, int xsize, int ysize, int colorkeyswitch = TRUE);

	UI08* GetSurfacePtr( int x, int y );

	// �ջ�� ���� �����Ѵ�. 
	void Restore();

	// ��üȭ�� ����
	void RestoreDisplayToWindow();
	void SetDisplayToGameMode();

	void UpdateScreen(HWND hwnd, LPDIRECTDRAWSURFACE7 pSurface, SI32 xsize, SI32 ysize,
					  SI32 xindent, SI32 yindent, SI32 srcstartx, SI32 srcstarty , bool bwaitrefresh,
					  SI32 screenXSize, SI32 screenYSize , bool bWebDlg = false, HWND hWebDlg = NULL,
					  bool bNewFullScreen = false );
	
public:
    // ���ǽ��� ���Ѵ�. 
    // surface: ���ǽ� ��� SURFACE_PRIMARY, SURFACE_BACK
//    BOOL LockSurface(int surface);

    // ���ǽ��� ����Ѵ�. 
    // surface: ���ǽ� ��� SURFACE_PRIMARY, SURFACE_BACK
//    BOOL UnlockSurface(int surface);

    BOOL LockSurface(LPDIRECTDRAWSURFACE7 pSurface);
    BOOL UnlockSurface(LPDIRECTDRAWSURFACE7 pSurface);

	// ȭ���� ������ �����.
    BOOL	ClearSurface(LPDIRECTDRAWSURFACE7 pSurface);

	// ���̷�Ʈ ��ο� ���ǽ��� �ƴ϶� ������ �޸𸮸� ���ؼ� �� �� �ֵ��� �����. 
    BOOL LockSurface(UI08*, int xsize, int ysize);

	// ������ lpddPal��ü�� ������ �ȷ�Ʈ�� �����Ѵ�. 
    HRESULT SetPalette();
    BOOL SetPalette(unsigned char* pal);

public:
	int GetScreenMode();
	int GetScreenXsize();
	int GetScreenYsize();
	void SetScreenXsize(int xsize);
	void SetScreenYsize(int ysize);
	int GetColorDepth();
	int GetSurfaceWidth();



private:
	void PutSprSpr(SI32 x, SI32 y, SI32 xsize, SI32 ysize, UI08* image, SI16 sprmode );
	void PutSprShadow(SI32 x, SI32 y, SI32 xsize, SI32 ysize, UI08* image, SI16 sprmode );
	void PutSprLight(SI32 x, SI32 y, SI32 xsize, SI32 ysize, UI08* image, SI16 sprmode );
	void PutSprLight1(SI32 x, SI32 y, SI32 xsize, SI32 ysize, UI08* image, SI16 sprmode );
	void PutSprAdd(SI32 x, SI32 y, SI32 xsize, SI32 ysize, UI08* image, SI16 sprmode );
	void PutSprScreen(SI32 x, SI32 y, SI32 xsize, SI32 ysize, UI08* image, SI16 sprmode );
	void PutSprMultiply(SI32 x, SI32 y, SI32 xsize, SI32 ysize, UI08* image, SI16 sprmode );


};

extern cltGraphic_Capsule GP;


inline BOOL cltGraphic_Capsule::IsInClipArea(int x1, int y1, int x2, int y2)
{
	return clGrp.IsInClipArea(x1,y1,x2,y2);
}

inline int cltGraphic_Capsule::GetClipRect(RECT* rect)
{
	return clGrp.GetClipRect(rect);
}

inline BOOL cltGraphic_Capsule::FitToClipArea(int sx1, int sy1, int sx2, int sy2, int& dx1, int& dy1,
									   int& dx2, int& dy2)
{
	return clGrp.FitToClipArea(sx1,sy1,sx2,sy2,dx1,dy1,dx2,dy2);
}

inline UI08* cltGraphic_Capsule::GetSurfacePtr( int x, int y )
{	
	return (UI08*)g_graphics.m_pImage + ( y * g_graphics.m_lPitch ) + ( x << 1 );

}

inline void cltGraphic_Capsule::GetImage(SI32 x, SI32 y, SI32 xsize, SI32 ysize, UI08* buffer)
{


}

inline BOOL cltGraphic_Capsule::LockSurface(LPDIRECTDRAWSURFACE7 pSurface)
{

	BOOL ret;


	ret = g_graphics.LockSurface(pSurface);

	return ret;
}

inline BOOL cltGraphic_Capsule::UnlockSurface(LPDIRECTDRAWSURFACE7 pSurface)
{


	g_graphics.UnlockSurface(pSurface);

	return TRUE;
}

// ȭ���� ������ �����.
inline BOOL cltGraphic_Capsule::ClearSurface(LPDIRECTDRAWSURFACE7 pSurface)
{
	return clGrp.ClearSurface(pSurface);
}

// ���̷�Ʈ ��ο� ���ǽ��� �ƴ϶� ������ �޸𸮸� ���ؼ� �� �� �ֵ��� �����. 

inline BOOL cltGraphic_Capsule::LockSurface(UI08*buffer, int xsize, int ysize)
{
	return clGrp.LockSurface(buffer,xsize,ysize);
}

inline void cltGraphic_Capsule::GetClipArea( int& x1, int &y1, int &x2, int &y2 )
{
	clGrp.GetClipArea(x1, y1, x2, y2);
}

inline void cltGraphic_Capsule::SetClipArea(SI32 x1,SI32 y1,SI32 x2,SI32 y2 )
{
	clGrp.SetClipArea(x1, y1, x2, y2);
	g_graphics.SetClipRect( x1, y1, x2, y2 );
}


#endif
