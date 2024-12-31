#ifndef _HTTPMGR_H_
#define _HTTPMGR_H_


#include "HttpBaseDefinition.h"

#include "../GoonzuWorld/common/SMLib/LibList/LibListMgr.h"

class CHttpMgr : public CLibListMgr
{
public:

	inline static unsigned __stdcall FileRecvThread(void* lpArg);			// FileRecvThread

	CHttpMgr( UI32 uiCount );
	~CHttpMgr();

	void Initialize();
	void Destroy();

	void CreateEmptyHttpObj( UI32 uiMaxObjNum );
	void SetBasePath( char *strBaseLocalPath, char *strBaseURL );

	bool Connect();						// HTTP ���� ó��
	void DisConnect();					// HTTP ���� ó��	

	DWORD GetFileTotalSize();			// ���� ���� ����� ����� ����
	DWORD GetFileRecvTotalSize();		// ���� ���� ����� ����� ����

	
	UC08 GetDownLoadStatus();			// ���� �ٿ�ε� ���¸� �˾ƿ�
	void DownLoadStart();

	DWORD GetFileRecvPercent();			// �� �ۼ�Ʈ �޾Ҵ��� �˾Ƴ��� ���ؼ�...
	

	void Push( UI32 uiVersion, char *strVersion );

	void FileRecv();
	void FileRecvStop();

	CC08 *GetLocalFileNamePath( SI32 siIndex );
	UI32 GetLastVersion();

private:
	HINTERNET		m_hInternet;
	HANDLE			m_hFileRecvThreadHandle;

	bool			m_bThreadRun;											// ���� �޴ٰ� �߰��� ���ߴ� ��찡 �߻��� �� �����Ƿ� �̶� flag �� �ּ� ���߰� �ϱ� ���ؼ�..
	UC08			m_ucDownLoadStatus;										// ���� ���¸� ������ ����. ( �ƹ� �͵� ���� �ʰ� ����, ������ �ٿ� �޴� ��, ������ ��� �ް� �ٽ� �ƹ��͵� ���� �ʰ� �ִ� ����. )

	DWORD			m_dwFileTotalSize;
	DWORD			m_dwFileRecvTotalSize;

	char			*m_strBaseURL;
	char			*m_strBaseLocalPath;

};

#endif