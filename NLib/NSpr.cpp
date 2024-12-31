//-----------------------------------------------------------------------------
// 2005/09/20 ������
//-----------------------------------------------------------------------------

#include "NSpr.h"
#include <windows.h>

NSpr::NSpr()
: pHeader( 0 ), pImageInfo( 0 ), pImageData( 0 ), pPal565( 0 ), pPal555( 0 ) 
{}

NSpr::~NSpr()
{
	if( m_pBuffer ) {
		delete [] m_pBuffer;
		m_pBuffer = NULL;
	}

	pHeader = NULL;
	pImageInfo = NULL;
	pImageData = NULL;
	pPal565 = NULL;
	pPal555 = NULL;
}

void NSpr::CreateSpr( int canvasWidth, int canvasHeight, int imageNum )
{

	int headerSize = sizeof( NSprHeader );

	int palSize = 2 * RGB16_PALETTE_SIZE;
	int imageSize = ( ( canvasWidth * canvasHeight * sizeof( RGB16 ) + 3 ) / 4 ) * 4;

	int imageInfoSize = sizeof( NSprImageInfo ) * imageNum;
	int imageDataSize = imageSize * imageNum;

	int fileSize = headerSize + imageInfoSize + imageDataSize + palSize;

	if( m_pBuffer ) {
		delete [] m_pBuffer;
		m_pBuffer = NULL;
	}

	m_pBuffer = new unsigned char[ fileSize ];

	pHeader = (NSprHeader*)m_pBuffer;

	pImageInfo = (NSprImageInfo*)( m_pBuffer + headerSize );
	pImageData = m_pBuffer + headerSize + imageInfoSize;

	pPal565 = (RGB16*)( pImageData + imageDataSize );
	pPal555 = (RGB16*)( pImageData + imageDataSize + RGB16_PALETTE_SIZE );

	// ������� ����
	memcpy( pHeader->id, TEXT("NPR"), 4 );

	pHeader->version = NSPR_VERSION;
	pHeader->encodeType = NSPR_ENCODETYPE_NONE;

	pHeader->fileSize = fileSize;

	pHeader->canvasWidth = canvasWidth;
	pHeader->canvasHeight = canvasHeight;

	pHeader->imageNum = imageNum;
	pHeader->colorNum = 256;

	pHeader->offsetImageInfo = headerSize;
	pHeader->offsetImageData = headerSize + imageInfoSize;

	pHeader->offsetPal565 = pHeader->offsetImageData + imageDataSize;
	pHeader->offsetPal555 = pHeader->offsetPal565 + RGB16_PALETTE_SIZE;

	
	// ImageInfo ����
	for( int i = 0; i < imageNum; ++i )
	{
		pImageInfo[ i ].offset = i * imageSize;
		pImageInfo[ i ].size = canvasWidth * canvasHeight * sizeof( RGB16 );
		pImageInfo[ i ].width = canvasWidth;
		pImageInfo[ i ].height = canvasHeight;
		pImageInfo[ i ].x = 0;
		pImageInfo[ i ].y = 0;
	}
	
	// ImageData ����
	ZeroMemory( pImageData, imageSize * imageNum );

	// Palette ����
	ZeroMemory( pPal565, RGB16_PALETTE_SIZE );
	ZeroMemory( pPal555, RGB16_PALETTE_SIZE );
}

void NSpr::LoadSprFromFile( char *filename )
{

}
