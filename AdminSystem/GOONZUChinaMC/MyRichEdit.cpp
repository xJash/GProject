// MyRichEdit.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MyRichEdit.h"


// MyRichEdit

IMPLEMENT_DYNAMIC(MyRichEdit, CRichEditCtrl)
MyRichEdit::MyRichEdit()
{
	InitializeCriticalSection( &m_cs );	
}

MyRichEdit::~MyRichEdit()
{
	DeleteCriticalSection( &m_cs );
}


BEGIN_MESSAGE_MAP(MyRichEdit, CRichEditCtrl)
	ON_WM_CREATE()
END_MESSAGE_MAP()



// MyRichEdit �޽��� ó�����Դϴ�.


int MyRichEdit::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CRichEditCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.

	int nSize = default_char_size * 20;			// atoi for tchar
	CHARFORMAT cf;

	cf.cbSize		= sizeof(CHARFORMAT);
	cf.dwMask		= CFM_FACE | CFM_COLOR | CFM_ITALIC | CFM_BOLD | CFM_SIZE;
	cf.dwEffects	=(unsigned long) ~( CFE_AUTOCOLOR| CFE_BOLD|CFE_ITALIC);
	//cf.dwEffects|= CFE_BOLD;
	//cf.dwEffects|= CFE_ITALIC;
	cf.yHeight		= nSize;
	cf.crTextColor	= default_char_color;
	strcpy(cf.szFaceName, "����"); 

	SetWordCharFormat(cf);

	return 0;
}

void MyRichEdit::AddText( LPCTSTR msg, COLORREF color, int height )
{

	EnterCriticalSection( &m_cs );

	int iTotalTextLength = GetWindowTextLength();
	int iStartPos = iTotalTextLength;

	// Get size in Twips
	int nSize = height * 20;			// atoi for tchar

	CHARFORMAT cf;
	cf.cbSize		= sizeof(CHARFORMAT);
	cf.dwMask		= CFM_FACE | CFM_COLOR | CFM_ITALIC | CFM_BOLD | CFM_SIZE;
	cf.dwEffects	=(unsigned long) ~( CFE_AUTOCOLOR| CFE_BOLD|CFE_ITALIC);
	//cf.dwEffects|= CFE_BOLD;
	//cf.dwEffects|= CFE_ITALIC;
	cf.yHeight		= nSize;
	cf.crTextColor	= color;
	strcpy(cf.szFaceName, "����"); 

	SetWordCharFormat(cf);
	
	SetSel(iTotalTextLength, iTotalTextLength);
	ReplaceSel(msg);
	LineScroll(2);

	LeaveCriticalSection( &m_cs );

}
