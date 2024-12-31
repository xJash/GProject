#pragma once

#include <Directives.h>
#include <stdio.h>

class CAbuseFilter
{
public:
	CAbuseFilter();
	~CAbuseFilter(void);

protected:
	TCHAR *m_pBufferPool;
	TCHAR **m_szBuffer;
	TCHAR **m_szWhiteBuffer;
	SI32 m_siMaxNum;
	SI32 m_siMaxWhiteNum;

protected:
	BOOL IsAbuse( TCHAR *buf1,TCHAR *buf2, SI16 txtSize );

public:
	void Create(TCHAR * szFileName, TCHAR *szFileName2 );
	bool CheckAbuse(TCHAR * buffer);	// �������� �ܾ *�� ��ü���ش�.

	bool CheckAbuseWord(TCHAR * buffer);	// �������� �ܾ üũ�Ѵ�. ������ true


};