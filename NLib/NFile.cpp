#include "NFile.h"

#include "NDataTypes.h"

NFile::NFile()
{
	m_pBuffer = NULL;

	m_dwBufferSize = 0;
	m_dwFileSize = 0;
	
}

NFile::~NFile()
{
	NDelete_Array( m_pBuffer );
}

bool NFile::LoadFile( TCHAR *filename )
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
	DWORD dwFileSizeHigh;
	dwFileSize = GetFileSize( hFile, &dwFileSizeHigh );

	m_dwFileSize = dwFileSize;
	m_dwBufferSize = ( dwFileSize * 4 + 3 ) / 4;

	// ���� ����
	if( m_pBuffer ) delete [] m_pBuffer;
	m_pBuffer = new BYTE[ m_dwBufferSize ];

	// ���Ͽ��� ������ �о����
	if( hFile )
	{
		DWORD dwBytesRead;
		ReadFile( hFile, (void*)m_pBuffer, dwFileSize, &dwBytesRead, NULL );

		CloseHandle( hFile );
		hFile = NULL;

		if( dwBytesRead != dwFileSize ) {
			NDelete_Array( m_pBuffer );
			return false;
		}
	}

	return true;
}