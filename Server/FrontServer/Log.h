#ifndef _LOGPRINT_H_
#define _LOGPRINT_H_

#include "../../GoonZuWorld/Lib/Directives.h"
#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/timeb.h>

class CLogPrint  
{
public:
	CLogPrint();												// �� �� ��
	virtual ~CLogPrint();										// �� �� ��

	void LogPrint( TCHAR *format, ... );							// ȭ�� ���
	void FilePrint( TCHAR* filename, TCHAR *format,... );			// ���� ���

	// Config������ �⵵, �޷� ���е� �α׸� �����. filename�� ���� �̸��� �ȴ�.
	void FileConfigPrint( TCHAR* filename, TCHAR *format,... );

	// ���Ͽ� �α׸� ����Ѵ�. - added by LeeKH
	void WriteFileLog( TCHAR* pszFileName, TCHAR* pszSource, int nLine, TCHAR* pszLogFormat, ... );

	static void GetDateFileName(TCHAR* pszFileName, TCHAR* pszOutFileName);

private:
	CRITICAL_SECTION	m_LogCrit;								// �α� ��½� ��Ű�� ���� ���� �ϱ� ���ؼ�

	TCHAR				dbgbuf[2048];							// �α�

	TCHAR				m_Time[ 128 ];							// �ð�
	TCHAR				m_Date[ 128 ];							// ��¥


};

#endif

extern CLogPrint g_CLogPrint;
