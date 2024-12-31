//-----------------------------------------------------------------------------
// 2005/09/13 이제완
//-----------------------------------------------------------------------------

#include "NDataTypes.h"
#include "NTextManager.h"
#include "NHashTableString.h"
#include "NFile.h"
#include "NUtil.h"
#include "NTCHARString.h"

NTextManager::NTextManager()
{
	//m_pBuffer = NULL;
	m_pHashTable = NULL;

	m_iCurBufPos = 0;
}

NTextManager::~NTextManager()
{
	NDelete(m_pHashTable);
	//NDelete_Array(m_pBuffer);
}


void NTextManager::CreateTextManager()
{

	m_iCurBufPos = 0;
	//m_pBuffer = new TCHAR[ 500 * 1024 ];
	m_pBuffer.NewMem( 500 * 1024 );

	m_pHashTable = new NHashTableString< TCHAR* >;

	m_pHashTable->CreateHashTableString( 12000, 15000, MAX_TEXT_KEY );

}


bool NTextManager::LoadTextFromFile( TCHAR *filename, int setcolumn )
{
	TCHAR strKey[ MAX_TEXT_KEY ];

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

	// 파일 크기를 얻어온다
	DWORD dwFileSize;
	DWORD dwFileSizeHigh;
	dwFileSize = GetFileSize( hFile, &dwFileSizeHigh );

	DWORD dwFileWLen;
	dwFileWLen = dwFileSize >> 1;

	// 버퍼 생성
	WCHAR *pBuf = NULL;
	pBuf = new WCHAR[ dwFileWLen + 1 ];

	// 파일에서 데이터 읽어오기
	if( hFile ) 
	{
		DWORD dwBytesRead;
		ReadFile( hFile, (void*)pBuf, dwFileSize, &dwBytesRead, NULL );

		CloseHandle( hFile );

		hFile = NULL;

		if( dwBytesRead != dwFileSize ) {
			delete [] pBuf;
			return false;
		}
	}

	pBuf[ dwFileWLen ] = NULL;

	int	iCurCol = 0;

	WCHAR *pCurPos = pBuf;					// 현재 위치
	WCHAR *pStartPos = pBuf;				// 문자열 시작 위치
	WCHAR *pEndPos = pBuf + dwFileWLen;

	int len, i;
	while( pCurPos < pEndPos ) 
	{
		// 탭 구분자 이면
		if( *pCurPos == L'\t' )	
		{
			*pCurPos = L'\0';

			if( pCurPos != pStartPos ) {

				if( iCurCol == 0 ) {

					// 유니코드를 읽어 멀티바이트로 바꾸고 버퍼에 쓴다 
#ifdef _UNICODE
					wcscpy( strKey, pStartPos );
					len = wcslen( pStartPos );
#else
					len = WideCharToMultiByte( CP_ACP, 0, pStartPos, -1, strKey, MAX_TEXT_KEY, NULL, NULL );
#endif

				} else if( iCurCol == setcolumn ) {

					// 유니코드를 읽어 멀티바이트로 바꾸고 버퍼에 쓴다 
#ifdef _UNICODE
					wcscpy( &m_pBuffer[ m_iCurBufPos ], pStartPos );
					len = wcslen( pStartPos );
#else
					len = WideCharToMultiByte( CP_ACP, 0, pStartPos, -1, &m_pBuffer[ m_iCurBufPos ], 1024, NULL, NULL );
#endif

					// 양쪽에 " 가 있다면 제거한다.
					NTCHARString1024 kText( &m_pBuffer[ m_iCurBufPos ] );
					kText.RemoveDoubleQuotation();
					StringCchCopy( &m_pBuffer[ m_iCurBufPos ], 1024, kText );

					for( i = 0; i < len; ++i )
					{
						if( m_pBuffer[ m_iCurBufPos + i ] == TEXT('\\') )
						{
							if( m_pBuffer[ m_iCurBufPos + i + 1 ] == TEXT('r') )
							{
								m_pBuffer[ m_iCurBufPos + i ] = TEXT('\r');
								m_pBuffer[ m_iCurBufPos + i + 1 ] = TEXT('\n');

								++i;
								continue;
							}
						}
					}

					m_pHashTable->Insert( strKey, &m_pBuffer[ m_iCurBufPos ] );

					m_iCurBufPos += len;
				}
			}

			++iCurCol;
			++pCurPos;

			pStartPos = pCurPos;

			continue;

			// 줄바꿈 구분자 이면 
		} else if( *pCurPos == L'\r' ) {
			*pCurPos = L'\0';


			if( pCurPos != pStartPos && iCurCol == setcolumn ) {

				// 유니코드를 읽어 멀티바이트로 바꾸고 버퍼에 쓴다 
#ifdef _UNICODE
				wcscpy( &m_pBuffer[ m_iCurBufPos ], pStartPos );
				len = wcslen( pStartPos );
#else
				len = WideCharToMultiByte( CP_ACP, 0, pStartPos, -1, &m_pBuffer[ m_iCurBufPos ], 1024, NULL, NULL );
#endif

				// 양쪽에 " 가 있다면 제거한다.
				NTCHARString1024 kText( &m_pBuffer[ m_iCurBufPos ] );
				kText.RemoveDoubleQuotation();
				StringCchCopy( &m_pBuffer[ m_iCurBufPos ], 1024, kText );

				for( i = 0; i < len; ++i )
				{
					if( m_pBuffer[ m_iCurBufPos + i ] == TEXT('\\') )
					{
						if( m_pBuffer[ m_iCurBufPos + i + 1 ] == TEXT('r') )
						{
							m_pBuffer[ m_iCurBufPos + i ] = TEXT('\r');
							m_pBuffer[ m_iCurBufPos + i + 1 ] = TEXT('\n');

							++i;
							continue;
						}
					}
				}

				if( strKey ) m_pHashTable->Insert( strKey, &m_pBuffer[ m_iCurBufPos ] );

				m_iCurBufPos += len;
			}

			iCurCol = 0;
			pCurPos += 2;
			pStartPos = pCurPos;

			strKey[ 0 ] = NULL;

			continue;

		}

		++pCurPos;
	}

	if( pBuf ) delete [] pBuf;

	return true;
}

// 기존 함수 수정해도 되나.. 예외처리 위하여 새로 만듬..
bool NTextManager::LoadTextFromCryptFile( TCHAR *filename, int setcolumn )
{
	TCHAR strKey[ MAX_TEXT_KEY ];

	WCHAR *pBuf = NULL;

	NFile file;
	DWORD dwFileWLen;

	if ( file.LoadFile( filename ) == false )
	{
#ifdef _DEBUG
		NTCHARString64 kMsg;
		kMsg  = filename;
		kMsg += " 파일이 없습니다.";
		MessageBox(NULL, kMsg, "ERROR", MB_OK);
#endif
		return false;
	}

	NCryptHeader *pHeader = (NCryptHeader *)file.GetBuffer();
	if( pHeader->id[ 0 ] == 'N' &&
		pHeader->id[ 1 ] == 'C' &&
		pHeader->id[ 2 ] == 'R' ) 
	{
		// 암호화 된 경우
		BYTE *pData = (BYTE*)pHeader + sizeof( NCryptHeader );
		int size = pHeader->dwDataSize;
		BYTE key = pHeader->key;

		dwFileWLen = size >> 1;
		pBuf = new WCHAR[ dwFileWLen + 1 ];

		NByteDecrypt( pData, (BYTE*)pBuf, size, key );

		pBuf[ dwFileWLen ] = NULL;
	}
	else
	{
#ifdef _DEBUG
		// 암호화 되지 않은 경우
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

		// 파일 크기를 얻어온다
		DWORD dwFileSize;
		DWORD dwFileSizeHigh;
		dwFileSize = GetFileSize( hFile, &dwFileSizeHigh );

		dwFileWLen = dwFileSize >> 1;

		// 버퍼 생성
		pBuf = new WCHAR[ dwFileWLen + 1 ];

		// 파일에서 데이터 읽어오기
		if( hFile ) 
		{
			DWORD dwBytesRead;
			ReadFile( hFile, (void*)pBuf, dwFileSize, &dwBytesRead, NULL );

			CloseHandle( hFile );

			hFile = NULL;

			if( dwBytesRead != dwFileSize ) 
			{
				delete [] pBuf;
				return false;
			}
		}
		pBuf[ dwFileWLen ] = NULL;
#else
		return false;
#endif
	}

	int	iCurCol = 0;

	WCHAR *pCurPos = pBuf;					// 현재 위치
	WCHAR *pStartPos = pBuf;				// 문자열 시작 위치
	WCHAR *pEndPos = pBuf + dwFileWLen;

	int len, i;
	while( pCurPos < pEndPos ) 
	{

		// 탭 구분자 이면
		if( *pCurPos == L'\t' )	
		{
			*pCurPos = L'\0';

			if( pCurPos != pStartPos ) {

				if( iCurCol == 0 ) {

					// 유니코드를 읽어 멀티바이트로 바꾸고 버퍼에 쓴다 
#ifdef _UNICODE
					wcscpy( strKey, pStartPos );
					len = wcslen( pStartPos );
#else
					len = WideCharToMultiByte( CP_ACP, 0, pStartPos, -1, strKey, MAX_TEXT_KEY, NULL, NULL );
#endif

				} else if( iCurCol == setcolumn ) {

					// 유니코드를 읽어 멀티바이트로 바꾸고 버퍼에 쓴다 
#ifdef _UNICODE
					wcscpy( &m_pBuffer[ m_iCurBufPos ], pStartPos );
					len = wcslen( pStartPos );
#else
					len = WideCharToMultiByte( CP_ACP, 0, pStartPos, -1, &m_pBuffer[ m_iCurBufPos ], 1024, NULL, NULL );
#endif

					// 양쪽에 " 가 있다면 제거한다.
					NTCHARString1024 kText( &m_pBuffer[ m_iCurBufPos ] );
					kText.RemoveDoubleQuotation();
					StringCchCopy( &m_pBuffer[ m_iCurBufPos ], 1024, kText );

					for( i = 0; i < len; ++i )
					{
						if( m_pBuffer[ m_iCurBufPos + i ] == TEXT('\\') )
						{
							if( m_pBuffer[ m_iCurBufPos + i + 1 ] == TEXT('r') )
							{
								m_pBuffer[ m_iCurBufPos + i ] = TEXT('\r');
								m_pBuffer[ m_iCurBufPos + i + 1 ] = TEXT('\n');

								++i;
								continue;
							}
						}
					}

					m_pHashTable->Insert( strKey, &m_pBuffer[ m_iCurBufPos ] );

					m_iCurBufPos += len;
				}
			}

			++iCurCol;
			++pCurPos;

			pStartPos = pCurPos;

			continue;

			// 줄바꿈 구분자 이면 
		} else if( *pCurPos == L'\r' ) {
			*pCurPos = L'\0';


			if( pCurPos != pStartPos && iCurCol == setcolumn ) {

				// 유니코드를 읽어 멀티바이트로 바꾸고 버퍼에 쓴다 
#ifdef _UNICODE
				wcscpy( &m_pBuffer[ m_iCurBufPos ], pStartPos );
				len = wcslen( pStartPos );
#else
				len = WideCharToMultiByte( CP_ACP, 0, pStartPos, -1, &m_pBuffer[ m_iCurBufPos ], 1024, NULL, NULL );
#endif

				// 양쪽에 " 가 있다면 제거한다.
				NTCHARString1024 kText( &m_pBuffer[ m_iCurBufPos ] );
				kText.RemoveDoubleQuotation();
				StringCchCopy( &m_pBuffer[ m_iCurBufPos ], 1024, kText );

				for( i = 0; i < len; ++i )
				{
					if( m_pBuffer[ m_iCurBufPos + i ] == TEXT('\\') )
					{
						if( m_pBuffer[ m_iCurBufPos + i + 1 ] == TEXT('r') )
						{
							m_pBuffer[ m_iCurBufPos + i ] = TEXT('\r');
							m_pBuffer[ m_iCurBufPos + i + 1 ] = TEXT('\n');

							++i;
							continue;
						}
					}
				}

				if( strKey ) m_pHashTable->Insert( strKey, &m_pBuffer[ m_iCurBufPos ] );

				m_iCurBufPos += len;
			}

			iCurCol = 0;
			pCurPos += 2;
			pStartPos = pCurPos;

			strKey[ 0 ] = NULL;

			continue;

		}

		++pCurPos;
	}

	if( pBuf ) delete [] pBuf;

	return true;
}

TCHAR* NTextManager::GetText( TCHAR *strKey )
{
	TCHAR *text;
	
	if( m_pHashTable->Find( strKey, text ) ) return text;

	return NULL;
}

TCHAR* NTextManager::GetSafeText( TCHAR *strKey )
{
	TCHAR *text;
	
	if( m_pHashTable->Find( strKey, text ) ) return text;

	return TEXT("");
}

