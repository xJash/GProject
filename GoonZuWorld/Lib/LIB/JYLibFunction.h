#ifndef _JYLIBFUNCTION_H_
#define _JYLIBFUNCTION_H_

#include <Directives.h>
#include <windows.h>
#include <stdio.h>
#include "string.h"

#define MAX_ALLOC_RECTS  100

class CJYLibFunction
{
public:
	CJYLibFunction();
	~CJYLibFunction();

	void SetNumTxt(INT64 num , char * dest , char * add = NULL ); // num : ���� , dest : ����->���ڿ��� �Ǵ� ����Ÿ�� ���� �� , add : ������ ����(ex:��)
	void SetNumUnit(INT64 num , char * dest , char * add = NULL );

	HRGN DIBToRgn(HBITMAP hBmp, COLORREF BkColor, BOOL Direct);
};

extern CJYLibFunction g_JYLibFunction;

#endif