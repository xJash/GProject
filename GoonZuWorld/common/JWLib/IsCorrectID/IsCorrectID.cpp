#include "IsCorrectID.h"

#include "../../../Client/Client.h"
extern cltCommonLogic* pclClient;

BOOL IsNumber( WCHAR wChar ) // ����
{
	if( wChar >= L'0' && wChar <= L'9' ) return TRUE;	// �����̸� ��� 

	return FALSE;
}

BOOL IsAlphabet( WCHAR wChar ) // ����
{
	if( wChar >= L'A' && wChar <= L'Z' ) return TRUE;	// ������ �빮���̸� ��� 
	if( wChar >= L'a' && wChar <= L'z' ) return TRUE;	// ������ �ҹ����̸� ���

	return FALSE;
}

BOOL IsHangul( WCHAR wChar ) // �ѱ�
{
	if( wChar >= 0xAC00 && wChar <= 0xD7A3 ) return TRUE;	// �ѱ��̸� ���( Ư������ ���� )

	return FALSE;
}

BOOL IsUnifiedHanja( WCHAR wChar ) // ������ ���� ����
{
	if( wChar >= 0x4E00 && wChar <= 0x9FFF ) return TRUE;	// �����ϰ���

	return FALSE;
}

BOOL IsHanjaRadicals( WCHAR wChar ) // ���� �μ�
{
	if( wChar >= 0x2E80 && wChar <= 0x2EFF ) return TRUE;	// CJK ���ںμ�

	return FALSE;
}

BOOL IsHanjaSymbolsNPunctuation( WCHAR wChar ) // ���� ��ȣ
{
	if( wChar >= 0x3000 && wChar <= 0x303F ) return TRUE;	// CJK Symbols and Punctuation

	return FALSE;
}

BOOL IsHiragana( WCHAR wChar ) // ���󰡳�
{
	if( wChar >= 0x3040 && wChar <= 0x309F ) return TRUE;	// ���󰡳�

	return FALSE;
}


BOOL IsKatakana( WCHAR wChar ) // īŸī��
{
	if( wChar >= 0x30A0 && wChar <= 0x30FF ) return TRUE;	// īŸī��

	return FALSE;
}


BOOL IsCompatibilityHanja1( WCHAR wChar ) // ȣȯ ����
{
	if( wChar >= 0x3300 && wChar <= 0x33FF ) return TRUE;	// ������ ȣȯ

	return FALSE;
}


BOOL IsHanjaExtended( WCHAR wChar ) // ���� Ȯ��
{
	if( wChar >= 0x3400 && wChar <= 0x4DB5 ) return TRUE;	// ����Ȯ��

	return FALSE;
}

BOOL IsCompatibilityHanja2( WCHAR wChar ) // ȣȯ ����
{
	if( wChar >= 0xF900 && wChar <= 0xFAFF ) return TRUE;	// ������ȣȯ

	return FALSE;
}

BOOL IsHalfNFullWidth( WCHAR wChar ) // �ݰ� �ڸ�(HalfWidth and Fullwidth Forms)
{
	if( wChar >= 0xFF00 && wChar <= 0xFFEF ) return TRUE;	// HalfWidth and Fullwidth Forms

	return FALSE;
}

BOOL IsHanjaForms( WCHAR wChar ) // ���� ����
{
	if( wChar >= 0xFE30 && wChar <= 0xFE4F ) return TRUE;	// �Ͼ��Ÿ

	return FALSE;
}


BOOL IsMathematicalSymbols( WCHAR wChar ) // ���� ������ȣ
{
	if( wChar >= 0x1D400 && wChar <= 0x1D7FF ) return TRUE;	// �Ͼ��Ÿ

	return FALSE;
}


BOOL IsHanjaSupplement( WCHAR wChar ) // ȣȯ ���� ����
{
	if( wChar >= 0x2F800 && wChar <= 0x2FA1F ) return TRUE;	// �Ͼ��Ÿ

	return FALSE;
}


BOOL IsCorrectID( TCHAR *szID )
{	

	/*
	if( pclClient->siServiceArea != ConstServiceArea_Korea ) {

			return TRUE;
		}
	*/

	//===================================
	// ID �����Ҽ� �ִ� �����ڵ� ���
	//==================================
	/*
	2E80..2EFF		CJK ���ںμ�
	3000..303F		CJK Symbols and Punctuation
	3040..309F		���󰡳�
	30A0..30FF		īŸī��
	3300..33FF		������ ȣȯ
	3400..4DB5		����Ȯ��
	4E00..9FFF		�����ϰ���
	F900..FAFF		������ȣȯ
	*/



	WCHAR	wszID[ 32 ];
	int		nLength		= 0;

#ifdef _UNICODE
	StringCchCopy( wszID, 32, szID );
#else
	MultiByteToWideChar( CP_ACP, MB_COMPOSITE, szID, -1, wszID, 32 );
#endif

	nLength = (int)wcslen( wszID );

	for( int i = 0; i < nLength; ++i ) 
	{
		// ����ġ������ �� break; �� ��Ű��.
		switch( pclClient->siServiceArea ) 
		{
		case ConstServiceArea_Japan:
			{
				if ( IsHiragana( wszID[ i ] )					== TRUE ) continue;
				if ( IsKatakana( wszID[ i ] )					== TRUE ) continue;
				if ( IsHanjaRadicals( wszID[ i ] )				== TRUE ) continue;
				if ( IsHanjaSymbolsNPunctuation( wszID[ i ] )	== TRUE ) continue;
				if ( IsCompatibilityHanja1( wszID[ i ] )		== TRUE ) continue;
				if ( IsCompatibilityHanja2( wszID[ i ] )		== TRUE ) continue;
				if ( IsHanjaExtended( wszID[ i ] )				== TRUE ) continue;
				if ( IsHalfNFullWidth( wszID[ i ] )				== TRUE ) continue;
				if ( IsHanjaForms( wszID[ i ] )					== TRUE ) continue;
				if ( IsMathematicalSymbols( wszID[ i ] )		== TRUE ) continue;
				if ( IsHanjaSupplement( wszID[ i ] )			== TRUE ) continue;

				if ( IsUnifiedHanja( wszID[ i ] )	== TRUE ) continue;
				if ( IsNumber( wszID[ i ] )		== TRUE ) continue;
				if ( IsAlphabet( wszID[ i ] )	== TRUE ) continue;
			}
			break;
		case ConstServiceArea_China:
		case ConstServiceArea_Taiwan:
		case ConstServiceArea_NHNChina:
			{
				if ( IsUnifiedHanja( wszID[ i ] )	== TRUE ) continue;
				if ( IsNumber( wszID[ i ] )		== TRUE ) continue;
				if ( IsAlphabet( wszID[ i ] )	== TRUE ) continue;
			}
			break;
		case ConstServiceArea_English:
		case ConstServiceArea_USA:
		case ConstServiceArea_EUROPE:
			{
				if ( IsNumber( wszID[ i ] )		== TRUE ) continue;
				if ( IsAlphabet( wszID[ i ] )	== TRUE ) continue;
			}
			break;
		case ConstServiceArea_Korea:
			{
				if ( IsNumber( wszID[ i ] )		== TRUE ) continue;
				if ( IsAlphabet( wszID[ i ] )	== TRUE ) continue;
				if ( IsHangul( wszID[ i ] )		== TRUE ) continue;
			}
			break;
		}
	/*
		if( wszID[ i ] >= L'0' && wszID[ i ] <= L'9' ) continue;		// �����̸� ��� 

		if( wszID[ i ] >= L'A' && wszID[ i ] <= L'Z' ) continue;		// ������ �빮���̸� ��� 

		if( wszID[ i ] >= L'a' && wszID[ i ] <= L'z' ) continue;		// ������ �ҹ����̸� ���

	#ifdef _KOREA
		// �ѱ�����
		if( wszID[ i ] >= 0xAC00 && wszID[ i ] <= 0xD7A3 ) continue;	// �ѱ��̸� ���( Ư������ ���� )
	#endif

#ifndef _ENGLISH

	#ifdef _CHINA
		if( wszID[ i ] >= 0x4E00 && wszID[ i ] <= 0x9FFF ) continue;	// �����ϰ���
	#else
		if( wszID[ i ] >= 0x2E80 && wszID[ i ] <= 0x2EFF ) continue;	// CJK ���ںμ�

		if( wszID[ i ] >= 0x3000 && wszID[ i ] <= 0x303F ) continue;	// CJK Symbols and Punctuation

		if( wszID[ i ] >= 0x3040 && wszID[ i ] <= 0x309F ) continue;	// ���󰡳�

		if( wszID[ i ] >= 0x30A0 && wszID[ i ] <= 0x30FF ) continue;	// īŸī��

		if( wszID[ i ] >= 0x3300 && wszID[ i ] <= 0x33FF ) continue;	// ������ ȣȯ

		if( wszID[ i ] >= 0x3400 && wszID[ i ] <= 0x4DB5 ) continue;	// ����Ȯ��

		if( wszID[ i ] >= 0x4E00 && wszID[ i ] <= 0x9FFF ) continue;	// �����ϰ���

		if( wszID[ i ] >= 0xF900 && wszID[ i ] <= 0xFAFF ) continue;	// ������ȣȯ

		if( wszID[ i ] >= 0xFF00 && wszID[ i ] <= 0xFFEF ) continue;	// HalfWidth and Fullwidth Forms

		if( wszID[ i ] >= 0xFE30 && wszID[ i ] <= 0xFE4F ) continue;	// �Ͼ��Ÿ

		if( wszID[ i ] >= 0x1D400 && wszID[ i ] <= 0x1D7FF ) continue;	// �Ͼ��Ÿ

		if( wszID[ i ] >= 0x2F800 && wszID[ i ] <= 0x2FA1F ) continue;	// �Ͼ��Ÿ
	#endif


#endif

	*/
		return FALSE;
	}

	return TRUE;
}
