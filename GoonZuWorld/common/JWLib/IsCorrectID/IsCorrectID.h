#ifndef _ISCORRECTID_H_
#define _ISCORRECTID_H_

#include <windows.h>

BOOL IsCorrectID( TCHAR *szID );

BOOL IsNumber( WCHAR wChar ); // ����
BOOL IsAlphabet( WCHAR wChar ); // ����
BOOL IsHangul( WCHAR wChar ); // �ѱ�
BOOL IsUnifiedHanja( WCHAR wChar ); // ������ ���� ����
BOOL IsHanjaRadicals( WCHAR wChar ); // ���� �μ�
BOOL IsHanjaSymbolsNPunctuation( WCHAR wChar ); // ���� ��ȣ
BOOL IsHiragana( WCHAR wChar ); // ���󰡳�
BOOL IsKatakana( WCHAR wChar ); // īŸī��
BOOL IsCompatibilityHanja1( WCHAR wChar ); // ȣȯ ����
BOOL IsHanjaExtended( WCHAR wChar ); // ���� Ȯ��
BOOL IsCompatibilityHanja2( WCHAR wChar ); // ȣȯ ����
BOOL IsHalfNFullWidth( WCHAR wChar ); // �ݰ� �ڸ�(HalfWidth and Fullwidth Forms);
BOOL IsHanjaForms( WCHAR wChar ); // ���� ����
BOOL IsMathematicalSymbols( WCHAR wChar ); // ���� ������ȣ
BOOL IsHanjaSupplement( WCHAR wChar ); // ȣȯ ���� ����

#endif