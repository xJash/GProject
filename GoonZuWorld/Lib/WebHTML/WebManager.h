// [3/3/2006]
//
//	�������� ���Ŵ���
//
#pragma once


#include "atlstr.h"

#define URL_MAX			256

class CNdoorsWebManager
{
public:
	CNdoorsWebManager();
	~CNdoorsWebManager();

public:

	void Navigate_PostType( CString & strURL , CString & strPost );
	void Navigate_Popup( CString & strLoginURL,  CString & strPost , UINT cx, UINT cy, HWND * hWnd );

};
