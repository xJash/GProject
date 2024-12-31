#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include "ndatatypes.h"

#include <ddraw.h>
#include <d3d.h>

#define _GRAPHICS_ASMCODE

typedef unsigned short		RGB16;

#define COLOR_BLACK			0					// ������
#define COLOR_WHITE			255					// ���. 
#define COLOR_TRANS			254					// ����� 

// 16 bit mode
#define RGB16_565			1
#define RGB16_555			2

#define RGB16_TRANS			0x7111

#define RGB16_565_RMASK		0xF800	
#define RGB16_565_GMASK		0x07E0
#define RGB16_565_BMASK		0x001F

#define RGB16_555_RMASK		0x7C00
#define RGB16_555_GMASK		0x03E0
#define RGB16_555_BMASK		0x001F

#define MAX_ALPHA_LEVEL		17
#define MAX_EFFECTF			4
#define MAX_EFFECT			10

#define EFFECT_LIGHTEN		0		
#define EFFECT_SCREEN		1
#define EFFECT_COLORDODGE	2
#define EFFECT_DODGEBURN	3
#define EFFECT_DIFFERENT	4

#define EFFECT_GLIGHT		5
#define EFFECT_GSCREEN		6
#define EFFECT_GADD			7
#define EFFECT_GMULTIPLY	8

class XSpr;

class NGraphics;
class NSurface;

class NGraphics
{
public:
    NGraphics();
    ~NGraphics();
	

	RGB16 GetSurfacePixel( int x, int y ) {
	
		return *(RGB16*)( (UI08*)m_pImage + ( y * m_lPitch ) + ( x << 1 ) );

	}


	RGB16 MakeRGB16( UI16 r, UI16 g, UI16 b );
	void GetRGB16( UI16 c, UI08 *r, UI08 *g, UI08 *b );


    HWND					GetHWnd() { return m_hWnd; }
    LPDIRECTDRAW7			GetDirectDraw() { return m_pDD; }
    LPDIRECTDRAWSURFACE7	GetFrontBuffer() { return m_pddsFrontBuffer; }
    LPDIRECTDRAWSURFACE7	GetBackBuffer() { return m_pddsBackBuffer; }
	LPDIRECTDRAWSURFACE7	GetConvertBuffer() { return m_pddsConvertBuffer; }

    BOOL		IsWindowed() { return m_bWindowed; }

	void		SetSkipDraw( BOOL bSkipDraw ) { m_bSkipDraw = bSkipDraw; }

	// �ʱ�ȭ �Լ� 
	BOOL		CreateGraphics( HWND hWnd, DWORD dwWidth, DWORD dwHeight, DWORD dwBPP, BOOL bWindowed );
    BOOL		CreateFullScreenGraphics( HWND hWnd, DWORD dwWidth, DWORD dwHeight, DWORD dwBPP, DWORD dwBackXSize = 0, DWORD dwBackYSize = 0, bool bNewFullScreen = false);
    BOOL		CreateWindowedGraphics( HWND hWnd, DWORD dwWidth, DWORD dwHeight, DWORD dwBPP, DWORD dwBackXSize = 0, DWORD dwBackYSize = 0);
    
	void		DestroyObjects();

	HRESULT		InitClipper();
    HRESULT		UpdateBounds();

    // Display methods
    HRESULT		Clear( DWORD dwColor = 0 );
	HRESULT		ClearSurface( LPDIRECTDRAWSURFACE7 lpdds, DWORD dwColor = 0 );

	HRESULT		ColorKeyBlt( DWORD x, DWORD y, LPDIRECTDRAWSURFACE7 pdds, RECT* prc = NULL );
    
	HRESULT		Blt( DWORD x, DWORD y, LPDIRECTDRAWSURFACE7 pdds, RECT* prc = NULL, DWORD dwFlags = 0 );
    HRESULT		Blt( DWORD x, DWORD y, NSurface* pSurface, RECT* prc = NULL );
    
    HRESULT		SetPalette( LPDIRECTDRAWPALETTE pPalette );
    
	HRESULT		Present();

	BOOL		CreateSurface16( LPDIRECTDRAWSURFACE7 *ppSurface, DWORD dwWidth, DWORD dwHeight, BOOL bColorkeyed = FALSE, RGB16 colorkey = 0 );

    HRESULT		CreateSurface( NSurface** ppSurface, DWORD dwWidth, DWORD dwHeight );
    
	HRESULT		CreateSurfaceFromText( NSurface** ppSurface, HFONT hFont, TCHAR* strText, 
									   COLORREF crBackground, COLORREF crForeground );

	BOOL		Lock();
	void		Unlock();

	BOOL		LockSurface( LPDIRECTDRAWSURFACE7 lpdds );
	void		UnlockSurface( LPDIRECTDRAWSURFACE7 lpdds );
	

	// Clipping
	void		SetClipFullScreen();
	void		SetClipRect( RECT *pRect );
	void		SetClipRect( int x1, int y1, int x2, int y2 );
	
	// Color table
	void		CreateColorTable( SI32 siMaxTableNum = 0 );
	void		SetColorTable( BYTE *pal, SI32 siTableIndex = 0 );

	BOOL		LoadColorTableFromFile( TCHAR* filename, SI32 siTableIndex = 0 );

	void		SetCurrentColorTable( SI32 tableindex );
	void		SetCurrentColorTable( RGB16 *pColorTable );

	// Alpha table
	void		CreateAlphaTable();

	// Effect table
	void		CreateEffectTable();
	void		CreateEffectFTable();

	BOOL		IsInClipArea( int x1, int y1, int x2, int y2 );


	//-------------------------------------------------------------------------
	// �׸��� �Լ�
	//-------------------------------------------------------------------------
	void		FillBox16( int x1, int y1, int x2, int y2, RGB16 color );
	void		FillBox16C( int x1, int y1, int x2, int y2, RGB16 color );

	void		Box16( int x1, int y1, int x2, int y2, RGB16 color );
	void		Box16C( int x1, int y1, int x2, int y2, RGB16 color );

	void		Line16( int x1, int y1, int x2, int y2, RGB16 color );
	void		Line16C( int x1, int y1, int x2, int y2, RGB16 color );

	void		HLine16( int x, int y, int l, RGB16 color );
	void		HLine16C( int x, int y, int l, RGB16 color );

	void		VLine16( int x, int y, int l, RGB16 color );
	void		VLine16C( int x, int y, int l, RGB16 color );

 
	//-------------------------------------------------------------------------
	// 16bit Image ��� �Լ�
	//-------------------------------------------------------------------------

	void		PutSurface16T( int x, int y, LPDIRECTDRAWSURFACE7 pdds );

	void		PutImage16T( int x, int y, int width, int height, UI08 *pSrcImage, int pitch, RGB16 colorkey );
	void		PutImage16CT( int x, int y, int width, int height, UI08 *pSrcImage, int pitch, RGB16 colorkey );

	void		PutImage16AT( int x, int y, int width, int height, UI08 *pSrcImage, int pitch, RGB16 colorkey );
	void		PutImage16CAT( int x, int y, int width, int height, UI08 *pSrcImage, int pitch, RGB16 colorkey );

	void		PutImage16ET( int x, int y, int width, int height, UI08 *pSrcImage, int pitch, RGB16 colorkey );
	void		PutImage16CET( int x, int y, int width, int height, UI08 *pSrcImage, int pitch, RGB16 colorkey );

	//-------------------------------------------------------------------------
	// ���� ��������Ʈ ��� �Լ�
	//-------------------------------------------------------------------------
	
	// SPR ����� ����
	void		PutSpr16N( int x, int y, UI08 *pSrcImage, int width, int height, UI08 *pDestImage = NULL );
	void		PutSpr16CN( int x, int y, UI08 *pSrcImage, int width, int height, UI08 *pDestImage = NULL );
	void		PutSpr16RN( int x, int y, UI08 *pSrcImage, int width, int height, UI08 *pDestImage = NULL );
	void		PutSpr16CRN( int x, int y, UI08 *pSrcImage, int width, int height, UI08 *pDestImage = NULL );

	// SPR ����� ����
	void		PutSpr16T( int x, int y, UI08 *pSrcImage, int width, int height, UI08 *pDestImage = NULL );
	void		PutSpr16CT( int x, int y, UI08 *pSrcImage, int width, int height, UI08 *pDestImage = NULL );
	void		PutSpr16RT( int x, int y, UI08 *pSrcImage, int width, int height, UI08 *pDestImage = NULL );
	void		PutSpr16CRT( int x, int y, UI08 *pSrcImage, int width, int height, UI08 *pDestImage = NULL );

	// SPR ����� ���� ȸ�� �� Ȯ��/���
	void		PutSpr16ST( int drawx, int drawy, UI08 *pSrcImage, int Width, int Height, UI08 *pDestImage, FLOAT fDegree, FLOAT fScale );
	void		PutSpr16SRT( int drawx, int drawy, UI08 *pSrcImage, int Width, int Height, UI08 *pDestImage, FLOAT fDegree, FLOAT fScale );

	// SPR ���ĺ���  
	void		PutSpr16AT( int x, int y, UI08 *pSrcImage, int width, int height, int alpha, UI08 *pDestImage = NULL );	
	void		PutSpr16CAT( int x, int y, UI08 *pSrcImage, int width, int height, int alpha, UI08 *pDestImage = NULL ); 
	void		PutSpr16RAT( int x, int y, UI08 *pSrcImage, int width, int height, int alpha, UI08 *pDestImage = NULL ); 
	void		PutSpr16CRAT( int x, int y, UI08 *pSrcImage, int width, int height, int alpha, UI08 *pDestImage = NULL ); 

	// SPR ���ĺ��� ȸ�� �� Ȯ��/���
	void		PutSpr16SAT( int drawx, int drawy, UI08 *pSrcImage, int Width, int Height, int alpha, UI08 *pDestImage, FLOAT fDegree, FLOAT fScale);
	void		PutSpr16SRAT( int drawx, int drawy, UI08 *pSrcImage, int Width, int Height, int alpha, UI08 *pDestImage, FLOAT fDegree, FLOAT fScale);

	// SPR ����Ʈ 
	void		PutSpr16ET( int x, int y, UI08 *pSrcImage, int width, int height, int effect, UI08 *pDestImage = NULL );	
	void		PutSpr16CET( int x, int y, UI08 *pSrcImage, int width, int height, int effect, UI08 *pDestImage = NULL ); 
	void		PutSpr16RET( int x, int y, UI08 *pSrcImage, int width, int height, int effect, UI08 *pDestImage = NULL ); 
	void		PutSpr16CRET( int x, int y, UI08 *pSrcImage, int width, int height, int effect, UI08 *pDestImage = NULL ); 

	// SPR ����Ʈ FAST
	void		PutSpr16EFT( int x, int y, UI08 *pSrcImage, int width, int height, int effectf, UI08 *pDestImage = NULL );	
	void		PutSpr16CEFT( int x, int y, UI08 *pSrcImage, int width, int height, int effectf, UI08 *pDestImage = NULL ); 
	void		PutSpr16REFT( int x, int y, UI08 *pSrcImage, int width, int height, int effectf, UI08 *pDestImage = NULL ); 
	void		PutSpr16CREFT( int x, int y, UI08 *pSrcImage, int width, int height, int effectf, UI08 *pDestImage = NULL ); 


	// MPR ����� ����
	void		PutMpr16T( int x, int y, UI08 *pSrcImage, int width, int height, UI08 *pDestImage = NULL ); 
	void		PutMpr16CT( int x, int y, UI08 *pSrcImage, int width, int height, UI08 *pDestImage = NULL ); 

	// MPR ���ĺ���
	void		PutMpr16AT( int x, int y, UI08 *pSrcImage, int width, int height, int alpha, UI08 *pDestImage = NULL ); 
	void		PutMpr16CAT( int x, int y, UI08 *pSrcImage, int width, int height, int alpha, UI08 *pDestImage = NULL ); 

	// MPR ����Ʈ
	void		PutMpr16ET( int x, int y, UI08 *pSrcImage, int width, int height, int effect, UI08 *pDestImage = NULL ); 
	void		PutMpr16CET( int x, int y, UI08 *pSrcImage, int width, int height, int effect, UI08 *pDestImage = NULL ); 


	// ZPR ����� ����
	void		PutZpr16T( int x, int y, UI08 *pSrcImage, int width, int height, UI08 *pDestImage = NULL ); 
	void		PutZpr16CT( int x, int y, UI08 *pSrcImage, int width, int height, UI08 *pDestImage = NULL ); 


	// XPR ����� ����
	void		PutXpr16T( int x, int y, int width, int height, RGB16 *pSrcImage, RGB16 colorkey );
	void		PutXpr16CT( int x, int y, int width, int height, RGB16 *pSrcImage, RGB16 colorkey );

	// XPR ���ĺ��� 
	void		PutXpr16AT( int x, int y, int width, int height, RGB16 *pSrcImage, int alpha, RGB16 colorkey );
	void		PutXpr16CAT( int x, int y, int width, int height, RGB16 *pSrcImage, int alpha, RGB16 colorkey );

	// XPR ����Ʈ 
	void		PutAlphaB16T( int x, int y, int width, int height, UI08 *pSrcImage ); 
	void		PutAlphaB16CT( int x, int y, int width, int height, UI08 *pSrcImage ); 

	// ��������Ʈ �� ����
	BYTE		GetSpr16T( int x, int y, int width, int height, UI08 *pSrcImage );
	BYTE		GetSpr16RT( int x, int y, int width, int height, UI08 *pSrcImage );

	//-------------------------------------------------------------------------
	// Encode
	//-------------------------------------------------------------------------
	void		EncodeXpr( RGB16 *pDestImage, int width, int height, RGB16 colorkey, int *size );

	BOOL		LoadXpr( TCHAR *filename, XSpr *pXSpr );
	
public:
    LPDIRECTDRAW7			m_pDD;
    LPDIRECTDRAWSURFACE7	m_pddsFrontBuffer;
    LPDIRECTDRAWSURFACE7	m_pddsBackBuffer;

	LPDIRECTDRAWSURFACE7	m_pddsConvertBuffer;

	LPDIRECTDRAWSURFACE7	m_pddsLockedSurface;
	
	BOOL					m_bSkipDraw;

	DDSURFACEDESC2			m_ddsd;

    HWND					m_hWnd;
    RECT					m_rcWindow;
    BOOL					m_bWindowed;

	// clipping
	RECT					m_rcClip;

	// surface lock
	BOOL					m_bLocked;

	// backsurface info
	void					*m_pImage;
	LONG					m_lPitch;

	DWORD					m_width;
	DWORD					m_height;

	DWORD					m_dwBPP;

	// 8bit mode palette
	LPDIRECTDRAWPALETTE		m_pddPalette;
	PALETTEENTRY			m_palEntry[ 256 ];

	// 16bit rgb mode
	SI32					m_rgbmode;										// 1: 565   2: 555
	
	// 16bit Alpha table
	RGB16*					m_pAlphaTable[ MAX_ALPHA_LEVEL ];

	// 16bit Effect Table
	RGB16*					m_pEffectFTable[ MAX_EFFECTF ];
	RGB16					m_pEffectTable[ MAX_EFFECT ][ 1024 ];

	// Color table
	UI08*					m_pColorTable;						// �÷� ���̺� 
	UI08*					m_pCurrentColorTablePtr;			// ���� �÷� ���̺��� ������ 

	SI32					m_siMaxColorTableNum;				// �ִ� �÷� ���̺� ����

private:
	void					_init();

};


class NSurface
{

public:
	NSurface();
	~NSurface();

	HRESULT Create( LPDIRECTDRAW7 pDD, DDSURFACEDESC2* pddsd );
	HRESULT Create( LPDIRECTDRAWSURFACE7 pdds );
	
	HRESULT Destroy();

	LPDIRECTDRAWSURFACE7	GetDDrawSurface() { return m_pdds; }
	BOOL					IsColorKeyed() { return m_bColorKeyed; }

	HRESULT		DrawBitmap( HBITMAP hBMP, DWORD dwBMPOriginX = 0, DWORD dwBMPOriginY = 0, 
							DWORD dwBMPWidth = 0, DWORD dwBMPHeight = 0 );

	HRESULT		DrawBitmap( TCHAR* strBMP, DWORD dwDesiredWidth, DWORD dwDesiredHeight );

	HRESULT		DrawText( HFONT hFont, TCHAR* strText, DWORD dwOriginX, DWORD dwOriginY,
						  COLORREF crBackground, COLORREF crForeground );

	HRESULT		SetColorKey( DWORD dwColorKey );
	DWORD		ConvertGDIColor( COLORREF dwGDIColor );

	static HRESULT	GetBitMaskInfo( DWORD dwBitMask, DWORD* pdwShift, DWORD* pdwBits );

private:
	LPDIRECTDRAWSURFACE7	m_pdds;
	DDSURFACEDESC2			m_ddsd;
	BOOL					m_bColorKeyed;
};


struct XSPRFileHeader
{
	char	id[ 4 ];					// "XPR"
	int		filesize;					// ������üũ��
	char	version;					// 1
	char	encodetype;					// 1: spr  2: mpr  3: zpr
	char	pixelformat;				// 0: 8bit indexed  1: 16bit 565  2: 16bit 555
	char	pal_type;					// 0: no palette  16: (565, 555)  24:(888)
	short	canvasWidth;				// ĵ���� �ʺ�
	short	canvasHeight;				// ĵ���� ���� 
	short	xnum;						// ���� ����
	short	ynum;						// ���� ����

	char	reserved1[ 20 ];			// ����1

	// body info 
	int		bodysize;					// �̹��� �±� + �̹��� ������ ũ��
	int		imagenum;					// �̹��� ���� 

	char	reserved2[ 16 ];			// ����2
};


struct XSPRImgTag
{
	int				offset;
	int				size;
	short			x;
	short			y;
	short			width;
	short			height;
};


class XSpr
{
public:
	XSpr();
	~XSpr();

	void Destroy();

	BOOL LoadXSpr( char *filename );

public:
	XSPRFileHeader		m_header;
	
	unsigned char*		m_pBody;

	XSPRImgTag*			m_pImageTag;
	unsigned char*		m_pImage;
	unsigned short*		m_pPal;
};

#endif