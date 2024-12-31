#ifndef _LETTERDLGBASEINFO_H_
#define _LETTERDLGBASEINFO_H_

#include <Directives.h>

#include "..\..\..\Resource.h"

#define		MAX_LETTERMSG_NUM		20				// ������ ���� �� �ִ� �ִ� ����
#define		MAX_LETTERMSG_SIZE		1024			// ������ ���ƿ��� ������ �뷮


#define		LETTER_INSERT_MSG		29000
#define		LETTER_DELETE_MSG		29001

struct	stLetterHeader
{
	UI16 uiMsg;
	UI16 uiMsgSize;
};

struct stLetterInsert
{
	stLetterHeader sHeader;	
	TCHAR strLetterMsg[ MAX_LETTERMSG_SIZE - 100 ];
	SI32 siTitleTxtMgr;

	stLetterInsert()
	{
		sHeader.uiMsg = LETTER_INSERT_MSG;
		sHeader.uiMsgSize = sizeof( stLetterInsert );
		siTitleTxtMgr = 0;
	}
};

//class CLetterDlg;
class CNLetterDlg;
//extern	CLetterDlg	g_LetterDlg;
extern	CNLetterDlg	g_NLetterDlg;

#endif