#include "Graphics.h"
#include "Graphic.h"

#include "Graphics_XPR16.h"
#include "TSpr.h"
#include "Graphic_Capsule.h"

#include "NUtil.h"

#include <memory.h>
#include <wchar.h>

// 생성자
XPR16::XPR16() : m_ppImage( NULL ), m_siFontNum( 0 ), m_siXSize( 0 ), m_siYSize( 0 ), m_colorkey( 0 )
{
}

// 소멸자
XPR16::~XPR16()
{
	Destroy();
}

// 제거함수 
void XPR16::Destroy()
{
	m_siFontNum = 0;
	m_siXSize = 0;
	m_siYSize = 0;
	m_colorkey = 0;

	for( int i = 0; i < m_siFontNum; ++i ) 
	{
		NDelete_Array( m_ppImage[ i ] );
	}

	NDelete_Array( m_ppImage );
}

// 파일로딩 
bool XPR16::LoadFromSpr16( TCHAR *szFilename )
{
	Destroy();

	// 작업용 버퍼
	RGB16	*pSrcImage = NULL;
	RGB16	*pEncodeImage = NULL;
	
	int		size;

	TSpr	spr;

	if( GP.LoadSprFromFile( szFilename, &spr ) == FALSE ) return false;

	// 폰트 개수, x size, y size 설정 
	m_siFontNum = spr.GetImageNum();
	m_siXSize = spr.GetXSize();
	m_siYSize = spr.GetYSize();


	// 투명색 설정
	m_colorkey = spr.pal[ COLOR_TRANS ];

	// 폰트 개수 만큼 이미지 포인터 생성
	m_ppImage = new RGB16*[ m_siFontNum ];
	if(m_ppImage == NULL)		return false;

	// pSrcImage 생성
	pSrcImage = new RGB16[ m_siXSize * m_siYSize ];
	if(pSrcImage == NULL)		return false;

	// pEncodeImage 생성
	pEncodeImage = new RGB16[ m_siXSize * m_siYSize * 2 ];
	if(pEncodeImage == NULL)		return false;

	// pSrcImage초기화 ( 2바이트 단위 memset )
	wmemset( pSrcImage, m_colorkey, m_siXSize * m_siYSize );
	
	// g_graphics의 pitch 및 image위치 보관
	long pitch = g_graphics.m_lPitch;
	void* pImage = g_graphics.m_pImage;

	g_graphics.m_lPitch = m_siXSize << 1;
	g_graphics.m_pImage = pSrcImage;

	// 폰트 개수 만큼 반복
	for( int i = 0; i < m_siFontNum; ++i )
	{
		// pSrcImage에 출력
		if( spr.header.iEncodeType == 0 ) {
			GP.PutSpr(&spr, 0, 0, i );
		} else {
			g_graphics.PutMpr16T( 0, 0, &spr.pImage[ spr.header.ImageInfo[ i ].iStartPos ], 
				spr.GetXSize(), spr.GetYSize() );
		}

		// pSrcImage -> pEncodeImage XPR 인코딩
		g_graphics.EncodeXpr( pEncodeImage, m_siXSize, m_siYSize, m_colorkey, &size );

		// 이미지 생성 및 복사
	
		m_ppImage[ i ] = new RGB16[ size >> 1 ];
		if(m_ppImage[ i ])		memcpy( m_ppImage[ i ], pEncodeImage, size );
	}

	// g_graphics의 pitch 및 image위치 복구
	g_graphics.m_lPitch = pitch;
	g_graphics.m_pImage = pImage;

	// 작업용 버퍼 해제
	NDelete_Array( pSrcImage );
	NDelete_Array( pEncodeImage );

	return true;
}

void XPR16::PutXpr16( int x, int y, int font )
{
	if( m_siFontNum <= font)
		return;

	if(m_ppImage == NULL)				return;
	if(m_ppImage[ font ] == NULL)		return;

	if( clGrp.IsInClipArea( x, y, x + m_siXSize - 1, y + m_siYSize - 1 ) == TRUE ) {

		g_graphics.PutXpr16T( x, y, m_siXSize, m_siYSize, m_ppImage[ font ], m_colorkey );

	} else {

		g_graphics.PutXpr16CT( x, y, m_siXSize, m_siYSize, m_ppImage[ font ], m_colorkey );
	}
}

void XPR16::PutXpr16A( int x, int y, int font, int alpha )
{
	if( m_siFontNum <= font)
		return;

	if(m_ppImage == NULL)				return;
	if(m_ppImage[ font ] == NULL)		return;

	if( clGrp.IsInClipArea( x, y, x + m_siXSize - 1, y + m_siYSize - 1 ) == TRUE ) {

		g_graphics.PutXpr16AT( x, y, m_siXSize, m_siYSize, m_ppImage[ font ], m_colorkey, alpha );

	} else {

		g_graphics.PutXpr16CAT( x, y, m_siXSize, m_siYSize, m_ppImage[ font ], m_colorkey, alpha );
	}
}
