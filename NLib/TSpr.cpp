//-----------------------------------------------------------------------------
// 2005/09/20 ������
//-----------------------------------------------------------------------------

#include "TSpr.h"
#include <windows.h>


TSpr::TSpr()
{
	ZeroMemory( this, sizeof( TSpr ) );
}

TSpr::~TSpr()
{
	if( pImage ) {
		delete [] pImage;
		pImage = NULL;
	}
}

bool TSpr::LoadTSprFromFile( TCHAR *filename, int rgbmode )
{

#ifdef _DEBUG
	HANDLE hFile = NULL;
	hFile = CreateFile(	filename,
		GENERIC_READ,
		FILE_SHARE_READ,
		0,
		OPEN_EXISTING,
		0,
		0 );
#else
	HANDLE hFile = NULL;
	hFile = CreateFile(	filename,
		GENERIC_READ,
		FILE_SHARE_READ,
		0,
		OPEN_EXISTING,
		0,
		0 );
#endif

	if( hFile == INVALID_HANDLE_VALUE ) 
	{
		return false;
	}


	DWORD	dwRead;

	// ����� �д´�
	ReadFile( hFile, &header, sizeof( header ), &dwRead, NULL );
	
	if( sizeof( header ) != dwRead ) {
		CloseHandle( hFile );
		return false;
	}

	// �̹��� ���۸� �����
	if( pImage ) delete [] pImage;
	pImage = new UI08[ header.iImageDataSize ];

	// �̹����� �ҷ��´�
	ReadFile( hFile, pImage, header.iImageDataSize, &dwRead, NULL );
	if( dwRead != (DWORD)header.iImageDataSize ) {
		CloseHandle( hFile );
		return false;
	}

	
	// �����ȷ�Ʈ�̸�, �ȷ�Ʈ�� �ҷ��´�
	if( header.iVersion == TSPR_VERSION_16PAL ) {

		if( rgbmode == RGB16_MODE_555 ) {

			SetFilePointer( hFile, 512, 0, FILE_CURRENT );
		}
		
		ReadFile( hFile, pal, 512, &dwRead, NULL );
		if( dwRead != 512 ) {
			CloseHandle( hFile );
			return false;
		}

	}

	CloseHandle( hFile );

	return true;
}

bool TSpr::LoadTSprFromMemory( BYTE* pMemory, int rgbmode /* = RGB16_MODE_565 */ )
{
	if( pMemory == NULL )			return false;

	// ����� �д´�
	//ReadFile( hFile, &header, sizeof( header ), &dwRead, NULL );
	memcpy( &header, pMemory, sizeof(header) );
	pMemory += sizeof(header);

	// �̹��� ���۸� �����
	if( pImage ) delete [] pImage;
	pImage = new UI08[ header.iImageDataSize ];
	if( pImage == NULL )			return false;

	// �̹����� �ҷ��´�
	//ReadFile( hFile, pImage, header.iImageDataSize, &dwRead, NULL );
	memcpy( pImage, pMemory, header.iImageDataSize );
	pMemory += header.iImageDataSize;
	
	// �����ȷ�Ʈ�̸�, �ȷ�Ʈ�� �ҷ��´�
	if( header.iVersion == TSPR_VERSION_16PAL )
	{
		if( rgbmode == RGB16_MODE_555 )
		{
			//SetFilePointer( hFile, 512, 0, FILE_CURRENT );
			pMemory += 512;
		}
		
		//ReadFile( hFile, pal, 512, &dwRead, NULL );
		memcpy( pal, pMemory, 512 );
	}

	return true;
}

TPal::TPal()
{
	ZeroMemory( this, sizeof( TPal ) );
}

TPal::~TPal()
{
}

bool TPal::LoadPalFromFile( TCHAR *filename, int rgbmode )
{

	HANDLE hFile = NULL;
	hFile = CreateFile(	filename,
		GENERIC_READ,
		FILE_SHARE_READ,
		0,
		OPEN_EXISTING,
		0,
		0 );

	if( hFile == INVALID_HANDLE_VALUE ) 
	{
		return false;
	}

	// ���� ũ�⸦ ���´�
	DWORD dwFileSize;
	dwFileSize = GetFileSize( hFile, NULL );

	if( dwFileSize == INVALID_FILE_SIZE ||
		dwFileSize != 768 ) 
	{
		CloseHandle( hFile );
		return false;
	}


	UI08 p[ 768 ];

	RGB16 r, g, b;

	DWORD dwRead;
	ReadFile( hFile, p, 768, &dwRead, NULL );

	CloseHandle( hFile );

	if( dwRead != 768 ) {
		ZeroMemory( pal, 512 );
		return false;
	}

	for( int i = 0; i < 256; ++i ) {

		if( rgbmode == RGB16_MODE_565 ) {

			r = RGB16_565_RMASK & ( ( p[ i * 3 ] >> 1 ) << 11 );
			g = RGB16_565_GMASK & ( ( p[ i * 3 + 1 ] ) << 5 );
			b = RGB16_565_BMASK & ( p[ i * 3 + 2 ] >> 1 );

			pal[ i ] = r | g | b;

		} else if( rgbmode == RGB16_MODE_555 ) {

			r = RGB16_555_RMASK & ( ( p[ i * 3 ] >> 1 ) << 10 );
			g = RGB16_555_GMASK & ( ( p[ i * 3 + 1 ] >> 1 ) << 5 );
			b = RGB16_555_BMASK & ( p[ i * 3 + 2 ] >> 1 );

			pal[ i ] = r | g | b;
		}

	}

	return true;
}


