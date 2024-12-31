#ifndef _HTTPOBJ_H_
#define _HTTPOBJ_H_

#include "HttpBaseDefinition.h"

#include "../GoonzuWorld/common/SMLib/LibList/Obj.h"

class CHttpObj : public CObj
{
public:
	CHttpObj();
	~CHttpObj();

	void Initialize();
	void Destroy();
	
	void DisConnect();

	void Set( UI32 uiVersion, char *strHttpURL, char *strLocalFilePath );

	UC08 GetStatus()
	{
		return m_ucDownLoadStatus;
	}

	DWORD GetFileSize();													// ���� ������ ����� ����
	DWORD GetFileRecvSize();												// ���� ������ ����� ����

	DWORD HttpFileConnect( HINTERNET hInternet );			// HTTP ���� URL�� ���� ó��, �ϵ忡 ������ ���ϸ� ����

	void FileCreate();
	DWORD FileRecv();

	BOOL FileExist();										// �ϵ忡 ���� ���ϰ� ���� ������ �ִ��� üũ

	CC08 *GetLocalFileNamePath();
	UI32 GetVersion();

	void SetDownLoadComplete()	{	m_ucDownLoadStatus = DOWNLOAD_COMPLETE_STATUS;	}	// �ٿ�ε� �Ϸ�� ����

private:
	HINTERNET		m_hURL;													// �ѹ��� �������� ���Ͽ� �����ؼ� �޾� ������ m_hURL �� �������� ����...

	DWORD			m_dwFileSize;											// �ٿ�ε��� ������ ũ��
	DWORD			m_dwFileRecvSize;										// �󸶸�ŭ�� �����͸� �ٿ� �޾Ҵ��� �˼� �ְ� �ϱ� ���ؼ�...

	CC08			m_strLocalFileNamePath[1536];							// �ٿ�ε�ÿ� �ϵ忡 ���� ���� ���
	CC08			m_strHttpURL[ 1024 ];

	UC08			m_ucDownLoadStatus;										// ���� ���¸� ������ ����. ( �ƹ� �͵� ���� �ʰ� ����, ������ �ٿ� �޴� ��, ������ ��� �ް� �ٽ� �ƹ��͵� ���� �ʰ� �ִ� ����. )
	
	UI32			m_uiVersion;

	HANDLE			m_hFile;
};

#endif