#include "Graphics.h"
#include "Graphic.h"

#include "Graphics_XPR16.h"

#include "../NUtil/NUtil.h"

#include <memory.h>
#include <wchar.h>

// ������
XPR16::XPR16() : m_ppImage( NULL ), m_siFontNum( 0 ), m_siXSize( 0 ), m_siYSize( 0 ), m_colorkey( 0 )
{
}

// �Ҹ���
XPR16::~XPR16()
{
	Destroy();
}

// �����Լ� 
void XPR16::Destroy()
{
	m_siFontNum = 0;
	m_siXSize = 0;
	m_siYSize = 0;
	m_colorkey = 0;

	for( int i = 0; i < m_siFontNum; ++i ) 
	{
		_delete( m_ppImage[ i ] );
	}

	_delete( m_ppImage );
}

// ���Ϸε� 
bool XPR16::LoadFromSpr16( char *szFilename )
{
	Destroy();

	// �۾��� ����
	RGB16	*pSrcImage = NULL;
	RGB16	*pEncodeImage = NULL;
	
	int		size;

	cltTSpr	spr;

	if( clGrp.LoadSpr( szFilename, &spr ) == FALSE ) return false;

	// ��Ʈ ����, x size, y size ���� 
	m_siFontNum = spr.clHeader.siFontNum;
	m_siXSize = spr.clHeader.siXsize;
	m_siYSize = spr.clHeader.siYsize;

	// ����� ����
	m_colorkey = spr.pal[ COLOR_TRANS ];

	// ��Ʈ ���� ��ŭ �̹��� ������ ����
	m_ppImage = new RGB16*[ m_siFontNum ];

	// pSrcImage ����
	pSrcImage = new RGB16[ m_siXSize * m_siYSize ];

	// pEncodeImage ����
	pEncodeImage = new RGB16[ m_siXSize * m_siYSize * 2 ];

	// pSrcImage�ʱ�ȭ ( 2����Ʈ ���� memset )
	wmemset( pSrcImage, m_colorkey, m_siXSize * m_siYSize );
	
	// g_graphics�� pitch �� image��ġ ����
	long pitch = g_graphics.m_lPitch;
	void* pImage = g_graphics.m_pImage;

	g_graphics.m_lPitch = m_siXSize << 1;
	g_graphics.m_pImage = pSrcImage;

	// ��Ʈ ���� ��ŭ �ݺ�
	for( int i = 0; i < m_siFontNum; ++i )
	{
		// pSrcImage�� ���
		if( spr.clHeader.siSprType == 0 ) {
			spr.PutSprT( 0, 0, i );
		} else {
			g_graphics.PutMpr16T( 0, 0, &spr.Image[ spr.clHeader.clImgInfo[ i ].siStartPos ], 
				spr.clHeader.siXsize, spr.clHeader.siYsize );
		}

		// pSrcImage -> pEncodeImage XPR ���ڵ�
		g_graphics.EncodeXpr( pEncodeImage, m_siXSize, m_siYSize, m_colorkey, &size );

		// �̹��� ���� �� ����
	
		m_ppImage[ i ] = new RGB16[ size >> 1 ];
		memcpy( m_ppImage[ i ], pEncodeImage, size );

	}

	// g_graphics�� pitch �� image��ġ ����
	g_graphics.m_lPitch = pitch;
	g_graphics.m_pImage = pImage;

	// �۾��� ���� ����
	_delete( pSrcImage );
	_delete( pEncodeImage );

	return true;
}

void XPR16::PutXpr16( int x, int y, int font )
{
	if( clGrp.IsInClipArea( x, y, x + m_siXSize - 1, y + m_siYSize - 1 ) == TRUE ) {

		g_graphics.PutXpr16T( x, y, m_siXSize, m_siYSize, m_ppImage[ font ], m_colorkey );

	} else {

		g_graphics.PutXpr16CT( x, y, m_siXSize, m_siYSize, m_ppImage[ font ], m_colorkey );
	}
}

void XPR16::PutXpr16A( int x, int y, int font, int alpha )
{
	if( clGrp.IsInClipArea( x, y, x + m_siXSize - 1, y + m_siYSize - 1 ) == TRUE ) {

		g_graphics.PutXpr16AT( x, y, m_siXSize, m_siYSize, m_ppImage[ font ], m_colorkey, alpha );

	} else {

		g_graphics.PutXpr16CAT( x, y, m_siXSize, m_siYSize, m_ppImage[ font ], m_colorkey, alpha );
	}
}
