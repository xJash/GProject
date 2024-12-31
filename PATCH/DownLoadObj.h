#ifndef _DOWNLOADOBJ_H_
#define _DOWNLOADOBJ_H_

#include "TypeDefinition.h"

//class CHttp;
class CFtpDownLoad;

class CDownLoadObj  
{
public:
	CDownLoadObj();													// �� �� ��
	virtual ~CDownLoadObj();										// �� �� ��

	void Initialize();												// �� �� ȭ
	void Destroy();													// ����ó��

	void SetBaseInfo( char *strUrl, char *strFolderPath, char *strUserID, char *strPassWord, US16 ftpPort );

	UI32 GetDownLoadVersion();										// DownLoad Version �� ����
	void SetDownLoadVersion();										// DownLoad Version �� ����.

	CC08 *GetstrDownLoadVersion();									// DownLoad Version ��Ʈ�� ������ ����.
	void SetstrDownLoadVersion( CC08 * strDownLoadVersion, SI32 siAddPathLength );		// DownLoad Version ��Ʈ�� �� ����

	//CC08 *GetstrDownLoadPath();										// DownLoad ��� ����.
	void SetstrDownLoadPath( CC08 * strDownLoadPath );				// DownLoad ��� ����. ( http://www.xxx.com/xxx.gif )
	
	CC08 *GetstrLocalFilePath();									// ���� ������ ��θ� ����.
	void SetstrLocalFilePath( CC08 * strLocalFilePath );			// ���� ������ ��θ� ������. ( c:\\Program Files\XXXCompany\GameName\\1.zip )
	void AddstrLocalPath();											// �⺻ ���("c:\program files\xxx\game\") �� ���ؼ� �߰��ؾ� �ϴ� ��. (xxx.exe)

	void SetFolderPath( char *strFolderPath );						// FTP ���� ���

	void DownLoadStart();											// �� ��ü�� ����� ��ġ ������ �ٿ�ε� ����
	
	bool CreateFtpObject();											// Ftp ��ü ���� �� http connect
	//CHttp *GetHttp();												// DownLoad�� ����ϴ� ��ü�� �����͸� ����
	CFtpDownLoad *GetFtp();													// DownLoad�� ����ϴ� ��ü�� �����͸� ����

private:
	UI32 m_uiDownLoadVersion;										// �ٿ�ε� �ҷ��� ������ ����
	CC08 m_strDownLoadVersion[32];									// �ٿ�ε� �ҷ��� ������ ����(��Ʈ��)
	CC08 m_strDownLoadPath[128];									// �ٿ�ε� ��ü ���
	CC08 m_strLocalFilePath[512];									// �ٿ�ε��� ������ ������ ���� ������ ��ü ���
	
	CC08 m_strFolderPath[128];										// FTP ���� ��� ����
	

	CC08 m_strID[ 32 ];
	CC08 m_strPassWord[ 32 ];

	US16 m_usFtpPort;
	
	//CHttp *m_pHttp;												// �ٿ�ε带 ������ ������ CHttp ��ü
	CFtpDownLoad	*m_pFtp;										// �ٿ�ε带 ������ ������ CFtp ��ü
};

#endif