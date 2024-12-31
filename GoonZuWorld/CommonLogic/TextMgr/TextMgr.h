#ifndef _TEXTMGR_H
#define _TEXTMGR_H

#include "../../lib/Directives.h"
#include <stdio.h>

#define MAX_TEXTMGR_NUM		6000

/*
class cltTextMgr
{
public:
	cltTextMgr();
	~cltTextMgr();

	void Create(TCHAR * szFileName);

	TCHAR * GetTextMgr(SI32 Unique);
	TCHAR m_szNULL[8] ;

private:
	BOOL OpenFile(TCHAR * szFileName);

	TCHAR * m_szText[MAX_TEXTMGR_NUM];

};
*/
//extern cltTextMgr g_pTextMgr;
//extern cltTextMgr g_pStructureMgr;

// �ؽ�Ʈ �Ŵ������� �ؽ�Ʈ�� ���´�.
TCHAR * GetTxtFromMgr(SI32 index , bool bStructure = false );
// ������ �ؽ�Ʈ �Ŵ������� �ؽ�Ʈ�� ���´�.
TCHAR * GetItemTxtFromMgr(SI32 index);

// �����Ŵ������� �ؽ�Ʈ�� ���´�.
TCHAR * GetHelpFromMgr(SI32 index);

// ����ȭ �ؽ�Ʈ�� ���� �ѹ� �о��ش�
#define MAX_TOKEN	30
#define MAX_STRING_LENGTH 256
extern TCHAR tokens[ MAX_TOKEN ][ MAX_STRING_LENGTH ];

void ParseText( TCHAR *str );

#endif
