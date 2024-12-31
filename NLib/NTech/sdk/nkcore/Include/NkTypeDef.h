//////////////////////////////////////////////////////////////////////////
// �ý��ۿ��� ���Ǵ� ��� �⺻ Ÿ�Ե� ������
// ������ hwpark@ndoors.net
//////////////////////////////////////////////////////////////////////////
#pragma once

// �⺻Ÿ�԰� �����쿡�� ����ϴ� Ÿ�Ը� ����մϴ�.
#include <windef.h>

//////////////////////////////////////////////////////////////////////////
// Generic Programming Utility Types

// ������ Ÿ������ ����� ���ø� Ŭ����
template <int V> struct		tmi2t { enum { eValue=V }; };
// Ÿ���� �ٸ� Ÿ������ ����� ���ø� Ŭ����
template <class T> struct	tmt2t { typedef T OriginalType; };

// �Ʒ� �����ǵ� Ÿ�� ������� �ʽ��ϴ�.
/*
//////////////////////////////////////////////////////////////////////////
// �⺻ Ÿ�� ������

typedef void				tvoid;
typedef bool				tbool; // 1byte
typedef char				tsi1b; // 1byte : -128 to 127
typedef unsigned char		tui1b; // 1byte : 0 to 255
typedef short				tsi2b; // 2byte integer : -32,768 to 32,767
typedef unsigned short		tui2b; // 2byte integer : 0 to 65,535
typedef long				tsi4b; // 4byte integer : -2,147,483,648 to 2,147,483,647
typedef unsigned long		tui4b; // 4byte integer : 0 to 4,294,967,295
typedef __int64				tsi8b; // 8byte integer : -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807
typedef size_t				tsize; // 8byte maybe
typedef float				tfp4b; // 4byte floating point : 3.4E +/- 38 (7 digits)
typedef double				tfp8b; // 8byte floating point : 1.7E +/- 308 (15 digits)

// �����ڵ� Ȱ��ȭ ���ο� ���� �����Ǵ� ���� Ÿ��
#if defined(UNICODE) | defined(_UNICODE)
typedef wchar_t				ttchr;
#else
typedef char				ttchr;
#endif

typedef char				tchar;
typedef wchar_t				twchr;
typedef tchar*				tcstr;
typedef twchr*				twstr;

//////////////////////////////////////////////////////////////////////////
// ����� �⺻ Ÿ�� ������

typedef const tvoid			cvoid;
typedef const tbool			cbool;
typedef const tsi1b			csc1b;
typedef const tui1b			cuc1b;
typedef const tsi2b			csi2b;
typedef const tui2b			cui2b;
typedef const tsi4b			csi4b;
typedef const tui4b			cui4b;
typedef const tsi8b			csi8b;
typedef const tsize			csize;
typedef const tfp4b			cfp4b;
typedef const tfp8b			cfp8b;

typedef const ttchr			ctchr;

typedef const tchar			cchar;
typedef const twchr			cwchr;

typedef const tcstr			ccstr;
typedef const twstr			cwstr;

typedef const tmi2t			cmi2t;
typedef const tmt2t			cmt2t;

//////////////////////////////////////////////////////////////////////////
*/
