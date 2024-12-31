#ifndef _TEXTMGR_H
#define _TEXTMGR_H

#include <stdafx.h>
#include <Directives.h>
#include <windows.h>
#include <stdio.h>

#define MAX_TEXTMGR_NUM		6000

class cltTextMgr
{
public:
	cltTextMgr();
	~cltTextMgr();

	void Create(char * szFileName);

	char * GetTextMgr(SI32 Unique);
	char m_szNULL[8] ;

private:
	BOOL OpenFile(char * szFileName);

	char * m_szText[MAX_TEXTMGR_NUM];

};

extern cltTextMgr g_pTextMgr;
extern cltTextMgr g_pStructureMgr;

// �ؽ�Ʈ �Ŵ������� �ؽ�Ʈ�� ���´�.
char * GetTxtFromMgr(SI32 index , bool bStructure = false );
// ����ȭ �ؽ�Ʈ�� ���� �ѹ� �о��ش�
#define MAX_TOKEN	30
#define MAX_STRING_LENGTH 256
extern char tokens[ MAX_TOKEN ][ MAX_STRING_LENGTH ];

void ParseText( char *str );

#endif
