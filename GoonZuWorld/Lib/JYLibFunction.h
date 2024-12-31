#ifndef _JYLIBFUNCTION_H_
#define _JYLIBFUNCTION_H_

#include <Directives.h>
#include <stdio.h>
#include "string.h"

#define MAX_ALLOC_RECTS  100

class CJYLibFunction
{
public:
	CJYLibFunction();
	~CJYLibFunction();

	void SetNumTxt(INT64 num , TCHAR * dest , SI16 destsize,  TCHAR * add = NULL ); // num : ���� , dest : ����->���ڿ��� �Ǵ� ����Ÿ�� ���� �� , add : ������ ����(ex:��)
	void SetNumUnit(INT64 num , TCHAR * dest , SI16 destsize, TCHAR * add = NULL );

	HRGN DIBToRgn(HBITMAP hBmp, COLORREF BkColor, BOOL Direct);
};

extern CJYLibFunction g_JYLibFunction;

#endif