#include "stdafx.h"
//#include "commonlogic.h"

#include "TextMgr.h"
#include "../../NLib/NTextManager.h"

//extern cltCommonLogic* pclClient;

#define Free(p)		free(p); p = NULL;

cltTextMgr g_pTextMgr;
//cltTextMgr g_pStructureMgr;
NTextManager g_pTextManager;

void MStrCpy( char *pDest, const char *pSrc, int maxbuf )
{
	if( pSrc == NULL ) {
		pDest[ 0 ] = NULL;
	
	} else {
		memcpy( pDest, pSrc, maxbuf );
		pDest[ maxbuf - 1 ] = NULL;
	}
}

void MsgBox(char * szCaption, char*szFormat,... )
{
	char szBuffer[256];
    char *pArguments;

	pArguments=( char * )&szFormat + sizeof( szFormat );
	vsprintf( szBuffer, szFormat, pArguments );

	MessageBox(NULL, szBuffer, szCaption, MB_OK|MB_TOPMOST);
}


char tokens[ MAX_TOKEN ][ MAX_STRING_LENGTH ];

cltTextMgr::cltTextMgr()
{
	for ( int i = 0 ; i < MAX_TEXTMGR_NUM ; i ++ )
		m_szText[i] = NULL ;

	MStrCpy(m_szNULL,"NULL",8);
}

cltTextMgr::~cltTextMgr()
{
	for ( int i = 0 ; i < MAX_TEXTMGR_NUM ; i ++ )
	{
		if ( m_szText[i] != NULL )
		{
			Free(m_szText[i]);
		}
	}
}

void cltTextMgr::Create(char * szFileName)
{
	if ( !OpenFile(szFileName) )
		MsgBox("error","can't open %s file!!",szFileName);
}

BOOL cltTextMgr::OpenFile(char * szFileName)
{
	FILE * fp = NULL ;

	char str[1024] = "" ;
	char * buf = NULL ;

	int textlength = 0 ;
	int oldlength = 0 ;
	int locate;

	fp = fopen(szFileName,"r");
	if ( fp == NULL ) return FALSE ;

	// �ʹ� 4�� ����
	for ( int i = 0 ; i < 4 ; i ++ )
		fgets(str,1024,fp);

	oldlength = ftell(fp);

	while( true )
	{
		if ( fgets(str,1024,fp) == NULL ) break ;
		if ( strstr(str,"<end>") ) break ;

		textlength = ftell(fp);
		textlength -= oldlength ;
		oldlength += textlength ;

		buf = (char*)malloc(textlength);
		strcpy(buf,str);
		locate = atoi(buf)-1;
		int j = atoi(buf) ;
		if ( j > MAX_TEXTMGR_NUM )
		{
			MsgBox("error","OverFlow %s! MAX_TEXTMGR_NUM is %d",szFileName,MAX_TEXTMGR_NUM);
			break ;
		}
		int k = 0 ;
		while(true)
		{
			j /= 10 ;
			if ( j == 0 ) break ;
			k ++ ;
		}
		//memcpy(buf,buf+k+2,strlen(buf));
		m_szText[locate] = (char*)malloc(textlength);
		strcpy(m_szText[locate],&buf[k+2]);
		m_szText[locate][textlength-4-k] = NULL ;

		for ( k = 0 ; k < textlength ; k ++ )
		{
			if ( (m_szText[locate][k] == '\\' && m_szText[locate][k+1] == 'r' ) && m_szText[locate][k+1] != NULL )
			{
				m_szText[locate][k] = '\r';
				m_szText[locate][k+1] = '\n';
			}
			else if ( (m_szText[locate][k] == '\\' && m_szText[locate][k+1] == 't' ) && m_szText[locate][k+1] != NULL )
			{
				m_szText[locate][k] = '\r';
				m_szText[locate][k+1] = '\t';
			}
		}

		Free(buf);
	}

	fclose(fp);

	return TRUE ;
}

char * cltTextMgr::GetTextMgr(SI32 Unique)
{
	if ( Unique <= 0 || Unique > MAX_TEXTMGR_NUM ) return NULL ;
	return m_szText[Unique-1];
}

// �ؽ�Ʈ �Ŵ������� �ؽ�Ʈ�� ���´�.
char * GetTxtFromMgr(SI32 index , bool bStructure )
{
	/*cyj NTextManager�� ��ü
	char * buffer = NULL ;

	if ( bStructure )
	{
	buffer = g_pStructureMgr.GetTextMgr(index);
	if ( !buffer )
	{
	#ifdef _DEBUG
	MsgBox("NoStructureMsg","%d",index);
	#endif
	return g_pStructureMgr.m_szNULL;
	}
	}
	else
	{
	buffer = GetTxtFromMgr(index);
	if ( !buffer )
	{
	#ifdef _DEBUG
	MsgBox("NoTextMsg","%d",index);
	#endif
	return g_pTextMgr.m_szNULL;
	}
	}
	*/

	char * buffer = NULL ;
	char strIndex[MAX_TEXT_KEY] = "";
	char szNULL[8] = "";

	if ( bStructure )
	{
		wsprintf(strIndex, "%d", index+6000);

		buffer = g_pTextManager.GetText(strIndex);
		if (!buffer)
		{
			MsgBox("NoStructureMsg","%d",index);

			MStrCpy(szNULL,"NULL",8);
			return szNULL;
		}

	}
	else
	{
		wsprintf(strIndex, "%d", index);

		buffer = g_pTextManager.GetText(strIndex);
		if (!buffer)
		{
			MsgBox("NoTextMsg","%s",strIndex);

			MStrCpy(szNULL,"NULL",8);
			return szNULL;
		}

	}

	return buffer ;
}


void ParseText( char *str )
{
	int i;
	int startpos = 0;

	int token_index = 0;
	int token_len = 0;
	
	int first_space = 0; 
	BOOL bSpace = FALSE;

	int len = strlen( str );

	for( i = 0; i < MAX_TOKEN; ++i ) {

		tokens[ i ][ 0 ] = NULL; 
	}


	for( int i = 0; i <= len; ++i ) 
	{
		if( str[ i ] == ' ' )
		{
			if( bSpace == FALSE )
			{
				first_space = i;
				bSpace = TRUE;
			}
			continue;
		}

		if( str[ i ] == '\t' || str[ i ] == 10 || str[ i ] == 13 || str[ i ] == NULL ) 
		{

			if( bSpace ) {

				token_len = first_space - startpos;

			} else {

				token_len = i - startpos;
			}

			if( token_len > 0 )
			{
				memcpy( tokens[ token_index ], &str[ startpos ], token_len );
			}

			tokens[ token_index ][ token_len ] = NULL;

			startpos = i + 1;
			token_index++;
		}

		bSpace = FALSE;
	}
}
