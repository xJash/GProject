#ifndef _TEXTMGR_H
#define _TEXTMGR_H

#include <Directives.h>
#include <windows.h>
#include <stdio.h>

#define MAX_TEXTMGR_NUM		31
#define MAX_TOKEN	30
#define MAX_STRING_LENGTH 256
#define MAX_LENGTH 1024

class cltTextMgr
{
public:
	cltTextMgr();
	~cltTextMgr();

	void Create(char * szFileName);	
	
	char m_szNULL[8];
	char* GetTextMgr(int Unique);
	// �ؽ�Ʈ �Ŵ������� �ؽ�Ʈ�� ���´�.
	
	// ����ȭ �ؽ�Ʈ�� ���� �ѹ� �о��ش�

private:
	BOOL OpenFile(char * szFileName);
	char *m_szText[MAX_TEXTMGR_NUM];

};

//extern char tokens[ MAX_TOKEN ][ MAX_STRING_LENGTH ];
char * GetTxtFromMgr(SI32 index , bool bStructure = false );
void MStrCpy( char *pDest, const char *pSrc, int maxbuf );
void MsgBox(char * szCaption, char*szFormat,... );

extern cltTextMgr g_pTextMgr;








#endif
