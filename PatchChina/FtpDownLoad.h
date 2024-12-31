#ifndef _FTPDOWNLOAD_H_
#define _FTPDOWNLOAD_H_

#include <wininet.h>
#include <process.h>
#include "TypeDefinition.h"

enum { STOP_STATUS, DOWNLOAD_STATUS, DOWNLOAD_COMPLETE_STATUS, DOWNLOAD_SPEED_ERROR, DOWNLOAD_STOP, LOCALFILE_MAKE_ERROR };

class CFtpDownLoad  
{
public:
	CFtpDownLoad();															// �� �� ��
	~CFtpDownLoad();														// �� �� ��

	
	inline static unsigned __stdcall FileRecvThread(void* lpArg);			// FileRecvThread

	void Initialize();														// �� �� ȭ
	void Destroy();															// ���� ó��

	bool Connect( char *strServerIP, char *strFolderPath, char *strID, char *strPassWord, US16 usFtpPort );					// FTP ���� ó��
	void DisConnect();														// HTTP ���� ó��

	bool FtpFileConnect( char* strURL, char* strLocalFileName );			// HTTP ���� URL�� ���� ó��, �ϵ忡 ������ ���ϸ��� ����

	void FtpDownLoadThreadStart();											// HTTP ������ �ޱ� ���� �����带 ����
	void FtpDownLoadThreadEnd();											// HTTP ������ �ޱ� ���� �����带 ����

	void FileRecv();														// �����忡�� ���� �ޱ� ���ؼ� �� �Լ��� ȣ����.
	void FileRecvStop();													// ���� �ޱ� �ߴ�.

	
	__int64 GetFileSize();													// ���� ������ ����� ����
	__int64	GetFileRecvSize();												// ���� ������ ����� ����

	DWORD GetFileRecvPercent();												// �� �ۼ�Ʈ �޾Ҵ��� �˾Ƴ��� ���ؼ�...
	UC08 GetDownLoadStatus();												// ���� �ٿ�ε� ���¸� �˾ƿ�

private:
	HINTERNET		m_hInternet;	
	HINTERNET		m_hFtp;
	HINTERNET		m_FindFile;
	HINTERNET		m_hFtpFile;
	
	
	HINTERNET		m_hReq;

	bool			m_bThreadRun;											// ���� �޴ٰ� �߰��� ���ߴ� ��찡 �߻��� �� �����Ƿ� �̶� flag �� �ּ� ���߰� �ϱ� ���ؼ�..
	HANDLE			m_hFileRecvThreadHandle;								// ������ �ڵ�
	UC08			m_ucDownLoadStatus;										// ���� ���¸� ������ ����. ( �ƹ� �͵� ���� �ʰ� ����, ������ �ٿ� �޴� ��, ������ ��� �ް� �ٽ� �ƹ��͵� ���� �ʰ� �ִ� ����. )

	CC08			m_strLocalFileNamePath[512];							// �ٿ�ε�ÿ� �ϵ忡 ���� ���� ���

	__int64			m_dwFileSize;											// �ٿ�ε��� ������ ũ��
	__int64			m_dwFileRecvSize;										// �󸶸�ŭ�� �����͸� �ٿ� �޾Ҵ��� �˼� �ְ� �ϱ� ���ؼ�...

	CC08			m_strServerIP[128];
};

#endif