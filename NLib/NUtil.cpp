//-----------------------------------------------------------------------------
// 2005/11/19 이제완
//-----------------------------------------------------------------------------
#include "NUtil.h"
#include "NFile.h"

#include "../GoonZuWorld/Lib/dxutil.h"

#include "NArray.h"
#include "NTCHARString.h"

#include <malloc.h>

// 시간 계산을 위한 기준 변수
UI64	uiSec = 0;

bool IsEncryptedFile( TCHAR *filename )
{
	FILE *pFP;
	pFP = NLibFOpen(filename, "rb");
	if (pFP == NULL)		return false;

	NCryptHeader Header1;

	//헤더를 읽음
	UI32 uiRead = (UI32)fread(&Header1, 1, sizeof(Header1), pFP);
	if (uiRead != sizeof(Header1))
	{
		NLibFClose(pFP);
		return false;
	}
	// 파일 닫기
	NLibFClose(pFP);

	//암호화 된 파일인지 확인.////////////////////////////////////////////////
	if( (Header1.id[ 0 ] == 'N' &&
		 Header1.id[ 1 ] == 'C' &&
		 Header1.id[ 2 ] == 'R') ) 
	{
		return true;
	}
	//////////////////////////////////////////////////////////////////////

	return false;
}

bool NWriteFile( TCHAR *filename, BYTE *pBuffer, int size )
{
	HANDLE hFile = NULL;
	hFile = CreateFile(	filename,
		GENERIC_WRITE,
		0,
		0,
		CREATE_ALWAYS,
		0,
		0 );

	if( hFile == INVALID_HANDLE_VALUE ) 
	{
		return false;
	}

	DWORD dwWritten;
	WriteFile( hFile, pBuffer, size, &dwWritten, NULL  );
	CloseHandle( hFile );

	return true;
}


bool NWriteCryptFile( TCHAR *filename, BYTE *pSrc, int size )
{
	bool bRet;

	// 버퍼 생성
	DWORD dwBufSize = ( ( sizeof(NCryptHeader) + size ) * 4 + 3 ) / 4;
	BYTE *pBuf = new BYTE[ dwBufSize ];

	// 암호화 파일 헤더 설정
	NCryptHeader *pHeader = (NCryptHeader *)pBuf;

	BYTE chksum, key;

	int r = rand() % ('Z' - 'A');
	
	chksum = 0;
	key = (BYTE)r + 'A';

	memcpy( pHeader->id, TEXT("NCR"), 4 );

	pHeader->version = 1;
	pHeader->encodeType = 1;

	pHeader->dwDataSize = size;

	pHeader->key = key;
	pHeader->chksum = chksum;

	NByteEncrypt( pSrc, pBuf + sizeof( NCryptHeader ), size, key );

	bRet = NWriteFile( filename, pBuf, dwBufSize );

	NDelete_Array( pBuf );

	return bRet;
}

//KHY - 0806 - 암호화 적용.
SI16  NWriteEnCryptFile(const TCHAR *basefilename, TCHAR *newfilename )
{
	SI16 bRet;

	FILE *pFP;
	pFP = NLibFOpen(basefilename, "rb");
	if (pFP == NULL)		return FALSE;

	BYTE *pkData = NULL;
	UI32 uiSize;

	// 암호화 된 Text파일의 크기 계산
	fseek(pFP, 0, SEEK_END);
	uiSize = (UI32)ftell(pFP);
	if (uiSize == 0)
	{
		NLibFClose(pFP);
		return FALSE;
	}
	fseek(pFP, 0, SEEK_SET);

	// 메모리 할당
	pkData = new BYTE[uiSize];
	if (pkData == NULL)
	{
		NLibFClose(pFP);
		SAFE_DELETE_ARRAY(pkData);
		return FALSE;
	}
	// 파일의 전체를 읽음
	UI32 uiRead = (UI32)fread(pkData, 1, uiSize, pFP);
	if (uiRead != uiSize)
	{
		NLibFClose(pFP);
		SAFE_DELETE_ARRAY(pkData);
		return FALSE;
	}
	// 파일 닫기
	NLibFClose(pFP);

//암호화 된 파일인지 확인.////////////////////////////////////////////////

	NCryptHeader *pHeader1 = (NCryptHeader *)pkData;

	if( (pHeader1->id[ 0 ] == 'N' &&
		pHeader1->id[ 1 ] == 'C' &&
		pHeader1->id[ 2 ] == 'R') ) 
	{
			bRet = 2; // 이미 암호화 되어 있음.
			return bRet;
	}
//////////////////////////////////////////////////////////////////////

	// 버퍼 생성
	DWORD dwBufSize = ( ( sizeof(NCryptHeader) + uiSize ) * 4 + 3 ) / 4;
	BYTE *pBuf = new BYTE[ dwBufSize ];

	// 암호화 파일 헤더 설정
	NCryptHeader *pHeader = (NCryptHeader *)pBuf;

	BYTE chksum, key;

	int r = rand() % ('Z' - 'A');
	
	chksum = 0;
	key = (BYTE)r + 'A';

	memcpy( pHeader->id, TEXT("NCR"), 4 );

	pHeader->version = 1;
	pHeader->encodeType = 1;

	pHeader->dwDataSize = uiSize;

	pHeader->key = key;
	pHeader->chksum = chksum;

	NByteEncrypt( pkData, pBuf + sizeof( NCryptHeader ), uiSize, key );

	bRet = NWriteFile( newfilename, pBuf, dwBufSize );

	NDelete_Array( pBuf );
	NDelete_Array( pkData);

	return bRet;
}

bool NWriteDeCryptFile( const TCHAR *basefilename, TCHAR *newfilename )
{
	bool bRet = false;

	FILE *pFP;
	pFP = NLibFOpen(basefilename, "rb");
	if (pFP == NULL)		return FALSE;

	BYTE *pkData = NULL;
	UI32 uiSize;

	// 암호화 된 Text파일의 크기 계산
	fseek(pFP, 0, SEEK_END);
	uiSize = ftell(pFP);
	if (uiSize == 0)
	{
		NLibFClose(pFP);
		return FALSE;
	}
	fseek(pFP, 0, SEEK_SET);

	// 메모리 할당
	pkData = new BYTE[uiSize];
	if (pkData == NULL)
	{
		NLibFClose(pFP);
		SAFE_DELETE_ARRAY(pkData);
		return FALSE;
	}
	// 파일의 전체를 읽음
	UI32 uiRead = (UI32)fread(pkData, 1, uiSize, pFP);
	if (uiRead != uiSize)
	{
		NLibFClose(pFP);
		SAFE_DELETE_ARRAY(pkData);
		return FALSE;
	}
	// 파일 닫기
	NLibFClose(pFP);

	NCryptHeader *pHeader = (NCryptHeader *)pkData;
	if( pHeader->id[ 0 ] == 'N' &&
		pHeader->id[ 1 ] == 'C' &&
		pHeader->id[ 2 ] == 'R' ) 
	{
		BYTE *pData = (BYTE*)pHeader + sizeof( NCryptHeader );
		int size = pHeader->dwDataSize;
		BYTE key = pHeader->key;
		UI32 uiRsize = uiSize - sizeof( NCryptHeader );
		BYTE *pBuf = new BYTE[uiRsize];

		NByteDecrypt( pData, pBuf, size, key );

		bRet = NWriteFile( newfilename, pBuf, uiRsize );

		NDelete_Array( pBuf );
		NDelete_Array( pkData);


		return bRet;

	}

	return bRet;

}
////////////////////////////////////////////////////////////////////////////
bool NLoadCryptFile( TCHAR *filename, BYTE **pDest, int* pSize )
{
	NFile file;

	if( file.LoadFile( filename ) == false ) return false;

	NCryptHeader *pHeader = (NCryptHeader *)file.GetBuffer();
	BYTE *pData = (BYTE*)pHeader + sizeof( NCryptHeader );

	*pDest = new BYTE[pHeader->dwDataSize + 10];
	if(*pDest == NULL)		return false;

	int size = pHeader->dwDataSize;
	BYTE key = pHeader->key;

	*pSize = size;
	NByteDecrypt( pData, *pDest, size, key );

	return true;
}

bool NLoadCryptFile( TCHAR *filename, BYTE *pDest )
{
	NFile file;

	if( file.LoadFile( filename ) == false ) return false;
	
	NCryptHeader *pHeader = (NCryptHeader *)file.GetBuffer();
	BYTE *pData = (BYTE*)pHeader + sizeof( NCryptHeader );

	int size = pHeader->dwDataSize;
	BYTE key = pHeader->key;

	NByteDecrypt( pData, pDest, size, key );

	return true;
}

void NByteEncrypt( BYTE *pSrc, BYTE *pDest, int size, BYTE key )
{
	BYTE *pCurSrc = pSrc + size - 1;
	BYTE *pCurDest = pDest + size - 1;

	*pCurDest = *pCurSrc ^ key;

	--pCurSrc;
	--pCurDest;

	while( pCurSrc >= pSrc )
	{
		*pCurDest = *pCurSrc ^ *( pCurDest + 1 );
		*pCurDest = *pCurDest + key;

		--pCurSrc;
		--pCurDest;
	}
}


void NByteDecrypt( BYTE *pSrc, BYTE *pDest, int size, BYTE key )
{
	BYTE *pEndSrc = pSrc + size - 1;

	while( pSrc < pEndSrc )
	{
		*pDest = *pSrc - key;
		*pDest = *pDest ^ *( pSrc + 1 );

		++pSrc;
		++pDest;
	}

	*pDest = *pSrc ^ key;
}

//---------------------------------------------------------------
// FUNC   : MakeBasicTimeValue
// DATE   : 2007-11-12
// 작성자 : 이강형
// DESC   : 시간 계산을 위한 기준 변수 계산 함수
//---------------------------------------------------------------
void MakeBasicTimeValue()
{
	SYSTEMTIME	st_cur;
	SYSTEMTIME	st_t;

	FILETIME	ft_cur;
	FILETIME	ft_t;

	UI64		uicur;
	UI64		uit;

	// 2007-01-01 12:00:00 을 기준시간으로 해서 계산
	st_cur.wYear = 2007;	st_cur.wMonth = 1;	st_cur.wDay = 1;
	st_cur.wHour = 12;	st_cur.wMinute = 0;	st_cur.wSecond = 0;	st_cur.wMilliseconds = 0;
	st_cur.wDayOfWeek = 1;

	// 1초에 해당하는 값을 계산
	memcpy(&st_t, &st_cur, sizeof(st_t));
	st_t.wSecond++;

	SystemTimeToFileTime(&st_cur,	&ft_cur);
	SystemTimeToFileTime(&st_t,		&ft_t);

	memcpy(&uicur,	&ft_cur,	sizeof(uicur));
	memcpy(&uit,	&ft_t,		sizeof(uit));

	uiSec = uit - uicur;
}

//---------------------------------------------------------------
// FUNC   : TimeInBounds
// DATE   : 2007-11-12
// 작성자 : 이강형
// DESC   : Cur시각이 Start시각과 End시각 사이에 Cur시각 안에 있는지 체크
// EX     : 
//---------------------------------------------------------------
bool TimeInBounds(SYSTEMTIME* Cur, SYSTEMTIME* Start, SYSTEMTIME* End)
{
	FILETIME	FileTime_Cur;
	FILETIME	FileTime_Start;
	FILETIME	FileTime_End;

	UI64		uiCur;
	UI64		uiStart;
	UI64		uiEnd;

	SystemTimeToFileTime(Cur,	&FileTime_Cur);
	SystemTimeToFileTime(Start,	&FileTime_Start);
	SystemTimeToFileTime(End,	&FileTime_End);

	memcpy(&uiCur,	 &FileTime_Cur,	  sizeof(uiCur));
	memcpy(&uiStart, &FileTime_Start, sizeof(uiStart));
	memcpy(&uiEnd,	 &FileTime_End,	  sizeof(uiEnd));

	if( uiStart < uiCur && uiCur < uiEnd)
		return true;
	else
		return false;
}

//---------------------------------------------------------------
// FUNC   : DiffDate
// DATE   : 2009-08-30
// 작성자 : 박기형
// DESC   : 과거 시간에서 현재 시간까지 지난 날짜를 구한다.
// EX     : 
//---------------------------------------------------------------
UI32 DiffDate(SYSTEMTIME* Cur, SYSTEMTIME* Past)
{
	if(uiSec == 0)		MakeBasicTimeValue();

	if( NULL == Cur)
		return 0;
	if( NULL == Past)
		return 0;

	FILETIME	FileTime_Cur;
	FILETIME	FileTime_Past;

	UI64		uiCur;
	UI64		uiPast;

	SystemTimeToFileTime(Cur,	&FileTime_Cur);
	SystemTimeToFileTime(Past,	&FileTime_Past);

	memcpy(&uiCur,	 &FileTime_Cur,	  sizeof(uiCur));
	memcpy(&uiPast,  &FileTime_Past,  sizeof(uiPast));

	if(uiCur <= uiPast)
		return 0;

	return (uiCur - uiPast) / ( 60 * 60 * 24 * uiSec);
}

//---------------------------------------------------------------
// FUNC   : TimeAddHour
// DATE   : 2007-11-12
// 작성자 : 황진성
// DESC   : pSrc 에서 siHour 만큼 더한 결과를 pRet로 반환
// EX     : 2007-11-12 12:00:00 에서 5분 만큼 더한 경우
//        : 2007-11-12 12:05:00 가 반환됨
//---------------------------------------------------------------
void TimeAddSecond(SYSTEMTIME* pSrc, SI32 siSecond, SYSTEMTIME* pRet)
{
	if(uiSec == 0)		MakeBasicTimeValue();

	if(pSrc == NULL)			return;
	if(pRet == NULL)			return;

	FILETIME	FileTime_Src;
	FILETIME	FileTime_Ret;

	UI64		uiSrc;
	UI64		uiRet;
	UI64		uiAddSecond;

	uiAddSecond = (uiSec) * siSecond;

	SystemTimeToFileTime(pSrc,	&FileTime_Src);
	memcpy(&uiSrc, &FileTime_Src, sizeof(uiSrc));

	uiRet = uiSrc + uiAddSecond;
	memcpy(&FileTime_Ret, &uiRet, sizeof(FileTime_Ret));

	FileTimeToSystemTime(&FileTime_Ret, pRet);
}

//---------------------------------------------------------------
// FUNC   : TimeAddHour
// DATE   : 2007-11-12
// 작성자 : 황진성
// DESC   : pSrc 에서 siHour 만큼 더한 결과를 pRet로 반환
// EX     : 2007-11-12 12:00:00 에서 5분 만큼 더한 경우
//        : 2007-11-12 12:05:00 가 반환됨
//---------------------------------------------------------------
void TimeAddMinute(SYSTEMTIME* pSrc, SI32 siMinute, SYSTEMTIME* pRet)
{
	if(uiSec == 0)		MakeBasicTimeValue();

	if(pSrc == NULL)			return;
	if(pRet == NULL)			return;

	FILETIME	FileTime_Src;
	FILETIME	FileTime_Ret;

	UI64		uiSrc;
	UI64		uiRet;
	UI64		uiAddMinute;

	uiAddMinute = (uiSec * 60) * siMinute;

	SystemTimeToFileTime(pSrc,	&FileTime_Src);
	memcpy(&uiSrc, &FileTime_Src, sizeof(uiSrc));

	uiRet = uiSrc + uiAddMinute;
	memcpy(&FileTime_Ret, &uiRet, sizeof(FileTime_Ret));

	FileTimeToSystemTime(&FileTime_Ret, pRet);
}

//---------------------------------------------------------------
// FUNC   : TimeAddHour
// DATE   : 2007-11-12
// 작성자 : 이강형
// DESC   : pSrc 에서 siHour 만큼 더한 결과를 pRet로 반환
// EX     : 2007-11-12 12:00:00 에서 3시간 만큼 더한 경우
//        : 2007-11-12 15:00:00 가 반환됨
//---------------------------------------------------------------
void TimeAddHour(SYSTEMTIME* pSrc, SI32 siHour, SYSTEMTIME* pRet)
{
	// 시간을 분으로 계산해서 함수 호출
	TimeAddMinute(pSrc, siHour * 60, pRet);

/*	if(uiSec == 0)		MakeBasicTimeValue();

	if(pSrc == NULL)			return;
	if(pRet == NULL)			return;

	FILETIME	FileTime_Src;
	FILETIME	FileTime_Ret;

	UI64		uiSrc;
	UI64		uiRet;
	UI64		uiAddHour;

	uiAddHour = (uiSec * 60 * 60) * siHour;

	SystemTimeToFileTime(pSrc,	&FileTime_Src);
	memcpy(&uiSrc, &FileTime_Src, sizeof(uiSrc));

	uiRet = uiSrc + uiAddHour;
	memcpy(&FileTime_Ret, &uiRet, sizeof(FileTime_Ret));

	FileTimeToSystemTime(&FileTime_Ret, pRet);*/
}

//---------------------------------------------------------------
// FUNC   : TimeAddDate
// DATE   : 2007-11-12
// 작성자 : 이강형
// DESC   : pSrc 에서 siDate 만큼 더한 결과를 pRet로 반환
// EX     : 2007-11-12 12:00:00 에서 3일 만큼 더한경우
//        : 2007-11-15 12:00:00 가 반환됨
//---------------------------------------------------------------
void TimeAddDate(SYSTEMTIME* pSrc, SI32 siDate, SYSTEMTIME* pRet)
{
	// 날짜를 시간으로 계산해서 함수 호출
	TimeAddHour(pSrc, siDate * 24, pRet);
}

//---------------------------------------------------------------
// FUNC   : TimeSubHour
// DATE   : 2007-11-12
// 작성자 : 이강형
// DESC   : pSrc 에서 siHour 만큼 차감한 결과를 pRet로 반환
// EX     : 2007-11-12 12:00:00 에서 3을 차감하는 경우
//        : 2007-11-12 09:00:00 가 반환됨
//---------------------------------------------------------------
void TimeSubHour(SYSTEMTIME* pSrc, SI32 siHour, SYSTEMTIME* pRet)
{
	// 음수로 변환해서 호출
	TimeAddHour(pSrc, -(siHour), pRet);
}

//---------------------------------------------------------------
// FUNC   : TimeSubHour
// DATE   : 2007-11-12
// 작성자 : 이강형
// DESC   : pSrc 에서 siDate 만큼 차감한 결과를 pRet로 반환
// EX     : 2007-11-12 12:00:00 에서 3을 차감하는 경우
//        : 2007-11-09 12:00:00 가 반환됨
//---------------------------------------------------------------
void TimeSubDate(SYSTEMTIME* pSrc, SI32 siDate, SYSTEMTIME* pRet)
{
	// 날짜를 시간으로 계산해서 함수 호출
	// 음수로 변환해서 호출
	TimeAddHour(pSrc, -(siDate * 24), pRet);
}

//---------------------------------------------------------------
// FUNC   : TimeCompare
// DATE   : 2007-11-12
// 작성자 : 이강형
// DESC   : 시간비교 함수
// EX     : 
//---------------------------------------------------------------
int TimeCompare(SYSTEMTIME* pX, SYSTEMTIME* pY)
{
	if(pX == NULL)			return 0;
	if(pY == NULL)			return 0;

	FILETIME	FileTime_X;
	FILETIME	FileTime_Y;

	UI64		uiX;
	UI64		uiY;

	SystemTimeToFileTime(pX,	&FileTime_X);
	SystemTimeToFileTime(pY,	&FileTime_Y);

	memcpy(&uiX, &FileTime_X, sizeof(uiX));
	memcpy(&uiY, &FileTime_Y, sizeof(uiY));

	if(uiX == uiY)
		return 0;
	else if(uiX > uiY)
		return 1;
	
	return -1;
}


//---------------------------------------------------------------
// FUNC   : TimeOperation
// DATE   : 2008-11-12
// 작성자 : 이강형
// DESC   : 시간계산 함수
// EX     : 
//---------------------------------------------------------------
SI64 TimeOperation(SYSTEMTIME* pX, SYSTEMTIME* pY)
{
	if(pX == NULL)			return 0;
	if(pY == NULL)			return 0;

	FILETIME	FileTime_X;
	FILETIME	FileTime_Y;

	UI64		uiX;
	UI64		uiY;

	SystemTimeToFileTime(pX,	&FileTime_X);
	SystemTimeToFileTime(pY,	&FileTime_Y);

	memcpy(&uiX, &FileTime_X, sizeof(uiX));
	memcpy(&uiY, &FileTime_Y, sizeof(uiY));

	return uiX - uiY;
}

//---------------------------------------------------------------
// FUNC   : GetTimeValue
// DATE   : 2008-11-12
// 작성자 : 이강형
// DESC   : 시간을 SI64 값으로 변환
// EX     : 
//---------------------------------------------------------------
SI64 GetTimeValue(SYSTEMTIME* pX)
{
	if(pX == NULL)			return 0;

	FILETIME	FileTime_X;

	UI64		uiX;

	SystemTimeToFileTime(pX,	&FileTime_X);

	memcpy(&uiX, &FileTime_X, sizeof(uiX));

	return uiX;;
}

void OutputMemory_Error(const TCHAR* szMsg)
{
	FILE*	fp = fopen("Config\\Memory_Error.log", "a");

	if(fp)
	{
		fprintf(fp, "%s\n", szMsg);
		fclose(fp);
	}
}

int RandomInt(int nStart, int nEnd)
{
	return (rand() % (nEnd - nStart + 1)) + nStart;
}


//=============================================================================
// STRING
//=============================================================================
inline DOUBLE	HQStoF( const TCHAR* pStr )									{	return _tstof( pStr );						}
inline SI32		HQStoI( const TCHAR* pStr )									{	return _tstoi( pStr );						}
inline DOUBLE	HQStoD( const TCHAR* pString, TCHAR **pEnd)					{   return	_tcstod(pString, pEnd);				}
inline UI32		HQStoUL(const TCHAR* pString, TCHAR **pEnd, SI32 siBase)    {   return	_tcstoul(pString, pEnd, siBase);	}

inline SI32		HQAtoI( const TCHAR* pChar)									{	return _ttoi( pChar );						}
inline SI64		HQAtoI64( const TCHAR* pChar)								{	return _ttoi64( pChar );					}
inline SI32		HQAtoL( const TCHAR* pChar)									{	return _ttol( pChar );						}


inline SI32		HQStrLen( const TCHAR* pString )							{	return (SI32)_tcslen( pString );			}
inline SI32		HQStrCmp( const TCHAR* pString1, const TCHAR* pString2 )	{	return _tcscmp( pString1, pString2 );		}
inline SI32		HQStriCmp(const TCHAR* pString1, const TCHAR* pString2 )	{	return _tcsicmp( pString1, pString2 );		}
inline SI32		HQStrtoL( const TCHAR* pStart, TCHAR** pEnd, SI32 siBase )	{	return _tcstoul( pStart, pEnd, siBase );	}
inline SI32		HQStrnCmp( const TCHAR* pA, const TCHAR* pB, SI32 siCount)	{	return _tcsncmp( pA, pB, siCount );			}
inline SI32		HQStrniCmp(const TCHAR* pA, const TCHAR* pB, SI32 siCount)	{	return _tcsnicmp( pA, pB, siCount );		}
inline TCHAR*	HQStrStr( const TCHAR* pString, const TCHAR* pFind )		{	return _tcsstr( pString, pFind );			}
inline TCHAR*	HQStrChr( const TCHAR* pString, SI32 c )					{	return _tcschr( pString, c );				}
inline TCHAR*	HQStrrChr( const TCHAR* pString, SI32 c )					{	return _tcsrchr( pString, c );				}
inline TCHAR*	HQStrCat( TCHAR* pDest, const TCHAR* pSrc )					{	return _tcscat( pDest, pSrc );				}
inline TCHAR*	HQStrnCat(TCHAR* pDest, const TCHAR* pSrc, SI32 siCount)	{	return _tcsncat(pDest, pSrc , siCount);		}
inline TCHAR*	HQStrCpy( TCHAR* pDest, const TCHAR* pSrc )					{	return _tcscpy( pDest, pSrc );				}
inline TCHAR*	HQStrnCpy( TCHAR* pDest, const TCHAR* pSrc, SI32 siMaxLen )	{	_tcsncpy(pDest, pSrc, siMaxLen ); pDest[siMaxLen-1]=0; return pDest;	}
inline TCHAR*	HQStrUpr( TCHAR* pString )									{	return _tcsupr( pString );					}
inline TCHAR*	HQStrLwr( TCHAR* pString )									{	return _tcslwr(pString);					}
inline TCHAR*	HQStrTok( TCHAR* pString, TCHAR* pDelimit )					{	return _tcstok( pString, pDelimit );		}
inline SI32		HQIsSpace( TCHAR cString )									{	return _istspace( cString );				}

inline void		HQMemZero( void* pDest, SI32 siCount )							{	memset( pDest, 0,	 siCount );			}

#define HQ_BUFFER_LINE	1024*10
#define HQ_STRING_MAX_DATA				2048

//=============================================================================
//  @Name   HQDivideByTab()
//! @author LeeKH						
//! @date   2006-3-30
//! @param  X   X
//! @return X
//! @brief  지원 포맷 - %s(TCHAR*), %c(TCHAR), %d(SI32), %f(FLOAT), %I64d(SI64), %x(DWORD)
//=============================================================================
SI32 HQDivideByTab( const TCHAR* pszStream, TCHAR* pszFormat, ...)
{
	if (pszStream == NULL)				return 0;
	if (pszFormat == NULL)				return 0;

	TCHAR	szBuffer[HQ_BUFFER_LINE];
	SI32	siCount = 0;

	TCHAR	szDivider[] = TEXT("\t");
	TCHAR*	pszToken = NULL;
	SI32	siPtr = 0;

	TCHAR*	pszParam = NULL;
	SI32*	psiParam = NULL;
	FLOAT*	pfParam = NULL;
	SI64*	psi64Param = NULL;
	TCHAR*	pcParam = NULL;
	DWORD*	pdwParam = NULL;

	TCHAR*	pszStoped = NULL;

	// 전체 복사 - HQStrTok() 함수의 기능때문에 전체를 복사해서 사용
	HQStrnCpy(szBuffer, pszStream, HQ_BUFFER_LINE);
	SI32	siBufferLength = HQStrLen(szBuffer);
	if (siBufferLength == 0)				return siCount;

	// 공백 지우기 - 뒤에서 부터 진행
	siPtr = siBufferLength-1;
	while (siPtr >= 0)
	{
		if (HQIsSpace(szBuffer[siPtr]))
			szBuffer[siPtr] = NULL;
		else
			break;
		siPtr--;
	}

	// 첫번째 토큰 얻기
	pszToken = HQStrTok(szBuffer, szDivider);
	if (pszToken == NULL)		return siCount;

	siPtr = 0;
	// 공백 건너뛰기 - 포맷문자열
	while (HQIsSpace(pszFormat[siPtr]))
	{
		siPtr++;
		if (pszFormat[siPtr] == NULL)		return siCount;
	}

	// 파라미터 리스트 시작
	va_list arglist;
	va_start(arglist, pszFormat);

	while(pszFormat[siPtr] != NULL)
	{
		// 공백 건너뛰기 - 포맷문자열
		while (HQIsSpace(pszFormat[siPtr]))
		{
			siPtr++;
			if (pszFormat[siPtr] == NULL)		break;
		}

		// 타입은 "%"가 먼저 나온다.
		if (pszFormat[siPtr] == TEXT('%'))
		{
			siPtr++;
			// TYPE : s
			if (pszFormat[siPtr] == TEXT('s'))
			{
				siPtr++;
				pszParam = va_arg(arglist, TCHAR*);
				if (pszParam == NULL)		break;
				HQStrCpy(pszParam, pszToken);
				siCount++;
			}
			// TYPE : c
			else if (pszFormat[siPtr] == TEXT('c'))
			{
				siPtr++;
				pcParam = va_arg(arglist, TCHAR*);
				if (pcParam == NULL)		break;
				*pcParam = pszToken[0];
				siCount++;
			}
			// TYPE : d
			else if (pszFormat[siPtr] == TEXT('d'))
			{
				siPtr++;
				psiParam = va_arg(arglist, SI32*);
				if (psiParam == NULL)		break;
				*psiParam = HQAtoI(pszToken);
				siCount++;
			}
			// TYPE : f
			else if (pszFormat[siPtr] == TEXT('f'))
			{
				siPtr++;
				pfParam = va_arg(arglist, FLOAT*);
				if (pfParam == NULL)		break;
				*pfParam = (FLOAT)HQStoF(pszToken);
				siCount++;
			}
			// TYPE : I64d
			else if (pszFormat[siPtr] == TEXT('I'))
			{
				if (pszFormat[siPtr+1] == TEXT('6') && pszFormat[siPtr+2] == TEXT('4') &&
					pszFormat[siPtr+3] == TEXT('d') )
				{
					siPtr += 4;
					psi64Param = va_arg(arglist, SI64*);
					if (psi64Param == NULL)		break;
					*psi64Param = HQAtoI64(pszToken);
					siCount++;
				}
				else
					break;
			}
			// TYPE : x
			else if (pszFormat[siPtr] == TEXT('x'))
			{
				siPtr++;
				pdwParam = va_arg(arglist, DWORD*);
				if (pdwParam == NULL)		break;
				*pdwParam = HQStoUL(pszToken, &pszStoped, 16);
				siCount++;
			}
			else
				break;
		}
		else
			break;

		// 다음 토큰 진행
		pszToken = HQStrTok(NULL, szDivider);
		if (pszToken == NULL)	break;
	}

	// 파라미터 리스트 종료
	va_end(arglist);
	return siCount;
}

//=============================================================================
//  @Name   HQDivideBy()
//! @author LeeKH						
//! @date   2006-5-19
//! @param  X   X
//! @return X
//! @brief  지원 포맷 - %s(TCHAR*), %c(TCHAR), %d(SI32), %f(FLOAT), %I64d(SI64), %x(DWORD)
//=============================================================================
SI32 HQDivideBy( const TCHAR* pszDivider, const TCHAR* pszStream, TCHAR* pszFormat, ...)
{
	// 보안코드
	if (pszDivider == NULL)							return 0;
	if (pszStream == NULL)							return 0;
	if (pszFormat == NULL)							return 0;
	// HQStrnCpy 사용시 메모리영역을 넘는걸 방지하기 위해 숫자를 줄임
	if (HQStrLen(pszStream) > HQ_BUFFER_LINE - 10)	return 0;

	// 버퍼      ... 10240
	TCHAR				szBuffer[HQ_BUFFER_LINE];
	// 토큰 한개 ... 2048
	TCHAR				szToken[HQ_STRING_MAX_DATA];

	SI32	siCount = 0;

	SI32	siPtr = 0;
	SI32	siStart, siEnd, siLength;

	TCHAR*	pszParam = NULL;
	SI32*	psiParam = NULL;
	FLOAT*	pfParam = NULL;
	SI64*	psi64Param = NULL;
	TCHAR*	pcParam = NULL;
	DWORD*	pdwParam = NULL;

	TCHAR*	pszStoped = NULL;

	HQMemZero(szBuffer, sizeof(szBuffer));
	HQStrnCpy(szBuffer, pszStream, HQ_BUFFER_LINE);
	SI32	siBufferLength = HQStrLen(pszStream);
	if (siBufferLength == 0)				return siCount;

	// 공백 지우기 - 뒤에서 부터 진행
	siPtr = siBufferLength-1;
	while (siPtr >= 0)
	{
		if (HQIsSpace(szBuffer[siPtr]))
		{
			siBufferLength = siPtr;
			szBuffer[siPtr] = NULL;
		}
		else
			break;
		siPtr--;
	}

	// 첫번째 토큰 얻기
	siStart = 0;
	TCHAR* pszFind = HQStrStr(&szBuffer[siStart], pszDivider);	
	if (pszFind == NULL)		return siCount;
	siEnd = (SI32)(pszFind - szBuffer);
	siLength = siEnd - siStart;
	HQMemZero(szToken, sizeof(szToken));
	if (siLength > 0)
	{
		if (siLength >= HQ_STRING_MAX_DATA)			return 0;		// 보안코드
		HQStrnCpy(szToken, &szBuffer[siStart], siLength + 1);		
	}
	siStart = siEnd + 1;

	siPtr = 0;
	// 공백 건너뛰기 - 포맷문자열
	while (HQIsSpace(pszFormat[siPtr]))
	{
		siPtr++;
		if (pszFormat[siPtr] == NULL)		return siCount;
	}

	// 파라미터 리스트 시작
	va_list arglist;
	va_start(arglist, pszFormat);

	while(pszFormat[siPtr] != NULL)
	{
		// 공백 건너뛰기 - 포맷문자열
		while (HQIsSpace(pszFormat[siPtr]))
		{
			siPtr++;
			if (pszFormat[siPtr] == NULL)		break;
		}

		// 타입은 "%"가 먼저 나온다.
		if (pszFormat[siPtr] == TEXT('%'))
		{
			siPtr++;
			// TYPE : s
			if (pszFormat[siPtr] == TEXT('s'))
			{
				siPtr++;
				pszParam = va_arg(arglist, TCHAR*);
				if (pszParam == NULL)		break;
				if (HQStrLen(szToken) > 0)
					HQStrCpy(pszParam, szToken);
				else
					pszParam[0] = NULL;
				siCount++;
			}
			// TYPE : c
			else if (pszFormat[siPtr] == TEXT('c'))
			{
				siPtr++;
				pcParam = va_arg(arglist, TCHAR*);
				if (pcParam == NULL)		break;
				if (HQStrLen(szToken) > 0)
					*pcParam = szToken[0];
				else
					*pcParam = NULL;
				siCount++;
			}
			// TYPE : d
			else if (pszFormat[siPtr] == TEXT('d'))
			{
				siPtr++;
				psiParam = va_arg(arglist, SI32*);
				if (psiParam == NULL)		break;
				if (HQStrLen(szToken) > 0)
					*psiParam = HQAtoI(szToken);
				else
					*psiParam = 0;
				siCount++;
			}
			// TYPE : f
			else if (pszFormat[siPtr] == TEXT('f'))
			{
				siPtr++;
				pfParam = va_arg(arglist, FLOAT*);
				if (pfParam == NULL)		break;
				if (HQStrLen(szToken) > 0)
					*pfParam = (FLOAT)HQStoF(szToken);
				else
					*pfParam  = 0.0f;
				siCount++;
			}
			// TYPE : I64d
			else if (pszFormat[siPtr] == TEXT('I'))
			{
				if (pszFormat[siPtr+1] == TEXT('6') && pszFormat[siPtr+2] == TEXT('4') &&
					pszFormat[siPtr+3] == TEXT('d') )
				{
					siPtr += 4;
					psi64Param = va_arg(arglist, SI64*);
					if (psi64Param == NULL)		break;
					if (HQStrLen(szToken) > 0)
						*psi64Param = HQAtoI64(szToken);
					else
						*psi64Param = 0;
					siCount++;
				}
				else
					break;
			}
			// TYPE : x
			else if (pszFormat[siPtr] == TEXT('x'))
			{
				siPtr++;
				pdwParam = va_arg(arglist, DWORD*);
				if (pdwParam == NULL)		break;
				if (HQStrLen(szToken) > 0)
					*pdwParam = HQStoUL(szToken, &pszStoped, 16);
				else
					*pdwParam = 0;
				siCount++;
			}
			else
				break;
		}
		else
			break;

		// 다음 토큰 진행
		if (siStart > siBufferLength)				break;
		TCHAR* pszFind = HQStrStr(&szBuffer[siStart], pszDivider);
		if (pszFind == NULL)
		{
			if (siStart < siBufferLength)
				siEnd = siBufferLength;
			else
				break;
		}
		else
			siEnd = (SI32)(pszFind - szBuffer);
		siLength = siEnd - siStart;
		HQMemZero(szToken, sizeof(szToken));
		if (siLength > 0)
		{
			if (siLength >= HQ_STRING_MAX_DATA)				break;										// 보안코드
			if (siStart + siLength + 1 > HQ_BUFFER_LINE)	siLength = HQ_BUFFER_LINE - siStart - 1;	// 보안코드
			HQStrnCpy(szToken, &szBuffer[siStart], siLength + 1);
		}
		siStart = siEnd + 1;
	}

	// 파라미터 리스트 종료
	va_end(arglist);
	return siCount;
}

SI32 HQDivideBy2( const TCHAR* pszDivider, const TCHAR* pszStream, TCHAR* pszFormat, ...)
{
	if (pszStream == NULL)				return 0;
	if (pszFormat == NULL)				return 0;

	TCHAR	szBuffer[HQ_BUFFER_LINE];
	SI32	siCount = 0;

	TCHAR	szDivider[5] ={ '\0', };
	_tcsncpy(szDivider, pszDivider, sizeof(pszDivider));	
	
	TCHAR*	pszToken = NULL;
	SI32	siPtr = 0;

	TCHAR*	pszParam = NULL;
	SI32*	psiParam = NULL;
	FLOAT*	pfParam = NULL;
	SI64*	psi64Param = NULL;
	TCHAR*	pcParam = NULL;
	DWORD*	pdwParam = NULL;

	TCHAR*	pszStoped = NULL;

	// 전체 복사 - HQStrTok() 함수의 기능때문에 전체를 복사해서 사용
	HQStrnCpy(szBuffer, pszStream, HQ_BUFFER_LINE);
	SI32	siBufferLength = HQStrLen(szBuffer);
	if (siBufferLength == 0)				return siCount;

	// 공백 지우기 - 뒤에서 부터 진행
	siPtr = siBufferLength-1;
	while (siPtr >= 0)
	{
		if (HQIsSpace(szBuffer[siPtr]))
			szBuffer[siPtr] = NULL;
		else
			break;
		siPtr--;
	}

	// 첫번째 토큰 얻기
	pszToken = HQStrTok(szBuffer, szDivider);
	if (pszToken == NULL)		return siCount;

	siPtr = 0;
	// 공백 건너뛰기 - 포맷문자열
	while (HQIsSpace(pszFormat[siPtr]))
	{
		siPtr++;
		if (pszFormat[siPtr] == NULL)		return siCount;
	}

	// 파라미터 리스트 시작
	va_list arglist;
	va_start(arglist, pszFormat);

	while(pszFormat[siPtr] != NULL)
	{
		// 공백 건너뛰기 - 포맷문자열
		while (HQIsSpace(pszFormat[siPtr]))
		{
			siPtr++;
			if (pszFormat[siPtr] == NULL)		break;
		}

		// 타입은 "%"가 먼저 나온다.
		if (pszFormat[siPtr] == TEXT('%'))
		{
			siPtr++;
			// TYPE : s
			if (pszFormat[siPtr] == TEXT('s'))
			{
				siPtr++;
				pszParam = va_arg(arglist, TCHAR*);
				if (pszParam == NULL)		break;
				HQStrCpy(pszParam, pszToken);
				siCount++;
			}
			// TYPE : c
			else if (pszFormat[siPtr] == TEXT('c'))
			{
				siPtr++;
				pcParam = va_arg(arglist, TCHAR*);
				if (pcParam == NULL)		break;
				*pcParam = pszToken[0];
				siCount++;
			}
			// TYPE : d
			else if (pszFormat[siPtr] == TEXT('d'))
			{
				siPtr++;
				psiParam = va_arg(arglist, SI32*);
				if (psiParam == NULL)		break;
				*psiParam = HQAtoI(pszToken);
				siCount++;
			}
			// TYPE : f
			else if (pszFormat[siPtr] == TEXT('f'))
			{
				siPtr++;
				pfParam = va_arg(arglist, FLOAT*);
				if (pfParam == NULL)		break;
				*pfParam = (FLOAT)HQStoF(pszToken);
				siCount++;
			}
			// TYPE : I64d
			else if (pszFormat[siPtr] == TEXT('I'))
			{
				if (pszFormat[siPtr+1] == TEXT('6') && pszFormat[siPtr+2] == TEXT('4') &&
					pszFormat[siPtr+3] == TEXT('d') )
				{
					siPtr += 4;
					psi64Param = va_arg(arglist, SI64*);
					if (psi64Param == NULL)		break;
					*psi64Param = HQAtoI64(pszToken);
					siCount++;
				}
				else
					break;
			}
			// TYPE : x
			else if (pszFormat[siPtr] == TEXT('x'))
			{
				siPtr++;
				pdwParam = va_arg(arglist, DWORD*);
				if (pdwParam == NULL)		break;
				*pdwParam = HQStoUL(pszToken, &pszStoped, 16);
				siCount++;
			}
			else
				break;
		}
		else
			break;

		// 다음 토큰 진행
		pszToken = HQStrTok(NULL, szDivider);
		if (pszToken == NULL)	break;
	}

	// 파라미터 리스트 종료
	va_end(arglist);
	return siCount;
}

bool MemoryToHex( const void* pData, UI32 siDataSize, TCHAR* pszOut, UI32 siOutSize )
{
	if( pData == NULL )						return false;
	if( pszOut == NULL )					return false;
	if( siDataSize == 0 )					return false;
	if( siOutSize == 0 )					return false;
	if( siDataSize * 2 > siOutSize )		return false;

	UI08*	puiData = (UI08*)pData;
	for( UI32 i=0; i<siDataSize; i++ )
	{
		StringCchPrintf(&pszOut[i*2], 3, "%02X", puiData[i]);
	}
	pszOut[siDataSize * 2] = '\0';

	return true;
}

bool MemoryToBinary( const void* pData, UI32 siDataSize, TCHAR* pszOut, UI32 siOutSize )
{
	if( pData == NULL )						return false;
	if( pszOut == NULL )					return false;
	if( siDataSize == 0 )					return false;
	if( siOutSize == 0 )					return false;
	if( siDataSize * 8 > siOutSize )		return false;

	UI08*	puiData = (UI08*)pData;
	TCHAR	szTemp[9];
	SI32	siTemp, siPtr;
	for( UI32 i=0; i<siDataSize; i++ )
	{
		for( SI32 j=0; j<9; j++ )	szTemp[j] = '0';
		szTemp[8] = '\0';

		siPtr = 7;
		siTemp = puiData[i];
		while( siTemp > 0 )
		{
			szTemp[siPtr] = siTemp % 2 + '0';
			siTemp /= 2;
			siPtr--;
		}
		
		StringCchPrintf(&pszOut[i*8], 9, "%s", szTemp);
	}
	pszOut[siDataSize * 8] = '\0';

	return true;
}

UI08 HexToUI08(char hex)
{
	switch(hex)
	{
	case '0':		return 0;
	case '1':		return 1;
	case '2':		return 2;
	case '3':		return 3;
	case '4':		return 4;
	case '5':		return 5;
	case '6':		return 6;
	case '7':		return 7;
	case '8':		return 8;
	case '9':		return 9;
	case 'A':
	case 'a':
		return 10;
	case 'B':
	case 'b':
		return 11;
	case 'C':
	case 'c':
		return 12;
	case 'D':
	case 'd':
		return 13;
	case 'E':
	case 'e':
		return 14;
	case 'F':
	case 'f':
		return 15;
	}
	return 0;
}

bool HexToMemory(char* pMem, const char* pszHex)
{
	char tmp[3];
	SI32 siLen = strlen(pszHex);
	UI08 uiTmp1, uiTmp2;

	for(SI32 i=0, j=0; i<siLen; i+=2, j++)
	{
		ZeroMemory(tmp, 3);
		strncpy(tmp, &pszHex[i], 2);

		uiTmp1 = HexToUI08(tmp[0]);
		uiTmp2 = HexToUI08(tmp[1]);

		pMem[j] = ((uiTmp1 & 0x0f) << 4) | (uiTmp2 & 0x0f);
	}

	return true;
}
