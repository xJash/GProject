#include "stdafx.h"
#include "Patch.h"
#include "DownLoadObj.h"
#include "FtpDownLoad.h"


//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - CDownLoadObj::CDownLoadObj()
//	Desc : FTP ������ �ޱ� ���� �����带 ����
//	Date : 2003. 06. 13
//	Update : 
//--------------------------------------------------------------------------------------------
CDownLoadObj::CDownLoadObj()
{
	m_pFtp = NULL;
	Initialize();
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - CDownLoadObj::~CDownLoadObj()
//	Desc : HTTP ������ �ޱ� ���� �����带 ����
//	Date : 2003. 06. 13
//	Update : 
//--------------------------------------------------------------------------------------------
CDownLoadObj::~CDownLoadObj()
{
	Destroy();
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CDownLoadObj::Initialize()
//	Desc : �� �� ȭ
//	Date : 2003. 06. 23
//	Update : 
//--------------------------------------------------------------------------------------------
void CDownLoadObj::Initialize()
{
	m_uiDownLoadVersion = 0;
	ZeroMemory( m_strDownLoadPath, 128 );
	ZeroMemory( m_strDownLoadVersion, 32 );
	ZeroMemory( m_strFolderPath, 128 );
	ZeroMemory( m_strID, 32 );
	ZeroMemory( m_strPassWord, 32 );

	if ( m_pFtp )
	{
		delete m_pFtp;
		m_pFtp = NULL;
	}
	
	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CDownLoadObj::Destroy()
//	Desc : ����ó��
//	Date : 2003. 06. 23
//	Update : 
//--------------------------------------------------------------------------------------------
void CDownLoadObj::Destroy()
{
	m_uiDownLoadVersion = 0;
	ZeroMemory( m_strDownLoadPath, 128 );
	ZeroMemory( m_strDownLoadVersion, 32 );
	ZeroMemory( m_strFolderPath, 128 );

	if ( m_pFtp )
	{
		delete m_pFtp;
		m_pFtp = NULL;
	}

	return;
}

void CDownLoadObj::SetBaseInfo( char *strUrl, char *strFolderPath, char *strUserID, char *strPassWord, US16 ftpPort )
{
	strcpy( m_strDownLoadPath, strUrl );

	if ( strFolderPath == NULL )
	{
		m_strFolderPath[0] = NULL;
	}
	else
	{
		strcpy( m_strFolderPath, strFolderPath );
	}

	strcpy( m_strID, strUserID );

	if ( strPassWord == NULL )
	{
		m_strPassWord[0] = NULL;
	}
	else
	{
		strcpy( m_strPassWord, strPassWord );
	}
	
	m_usFtpPort = ftpPort;

	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - UI32 CDownLoadObj::GetDownLoadVersion()
//	Desc : DownLoad Version �� ����
//	Date : 2003. 06. 13
//	Update : 
//--------------------------------------------------------------------------------------------
UI32 CDownLoadObj::GetDownLoadVersion()
{
	return m_uiDownLoadVersion;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CDownLoadObj::SetDownLoadVersion()
//	Desc : DownLoad Version �� ����.
//	Date : 2003. 06. 13
//	Update : 
//--------------------------------------------------------------------------------------------
void CDownLoadObj::SetDownLoadVersion()
{
	m_uiDownLoadVersion = atoi( m_strDownLoadVersion );

	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CDownLoadObj::SetDownLoadVersion()
//	Desc : DownLoad Version ��Ʈ�� ������ ����.
//	Date : 2003. 06. 23
//	Update : 
//--------------------------------------------------------------------------------------------
CC08 *CDownLoadObj::GetstrDownLoadVersion()
{
	return m_strDownLoadVersion;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CDownLoadObj::SetstrDownLoadVersion( CC08 * strDownLoadVersion, SI32 siAddPathLength )
//	Desc : DownLoad Version ��Ʈ�� �� ����
//	Date : 2003. 06. 23
//	Update : 
//--------------------------------------------------------------------------------------------
void CDownLoadObj::SetstrDownLoadVersion( CC08 * strDownLoadVersion, SI32 siAddPathLength )
{
	strncpy( m_strDownLoadVersion, strDownLoadVersion, siAddPathLength );
	strcat( m_strDownLoadVersion, "\0" );
	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - CC08 *CDownLoadObj::GetstrDownLoadPath()
//	Desc : DownLoad ��� ����.
//	Date : 2003. 06. 13
//	Update : 
//--------------------------------------------------------------------------------------------
/*
CC08 *CDownLoadObj::GetstrDownLoadPath()
{
	return m_strDownLoadPath;
}
*/

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CDownLoadObj::SetstrDownLoadPath(  CC08 * strDownLoadPath )
//	Desc : DownLoad ��� ����. ( http://www.xxx.com/xxx.gif )
//		   ������ ��ġ ���α׷����� �� �Լ��� ȣ��ÿ��� http://www.xxx.com/ ������ �� ��.
//		   �ڿ� AddDownLoadPath �Լ��� ȣ���ؼ� ������ DownLoad ��θ� ������.
//	Date : 2003. 06. 13
//	Update : 
//--------------------------------------------------------------------------------------------
void CDownLoadObj::SetstrDownLoadPath(  CC08 * strDownLoadPath )
{
	strcpy( m_strDownLoadPath, strDownLoadPath );
	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - CC08 *CDownLoadObj::GetstrLocalFilePath()
//	Desc : ���� ������ ��θ� ����.
//	Date : 2003. 06. 23
//	Update : 
//--------------------------------------------------------------------------------------------
CC08 *CDownLoadObj::GetstrLocalFilePath()
{
	return m_strLocalFilePath;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CDownLoadObj::SetstrDownLoadPath(  CC08 * strDownLoadPath )
//	Desc : ���� ������ ��θ� ������. ( c:\Program Files\XXXCompany\GameName\1.zip )
//		   ������ ��ġ ���α׷����� �� �Լ��� ȣ��ÿ��� c:\Program Files\XXXCompany\GameName\ ������ �� ��.
//	Date : 2003. 06. 23
//	Update : 
//--------------------------------------------------------------------------------------------
void CDownLoadObj::SetstrLocalFilePath( CC08 * strLocalFilePath )
{
	strcpy( m_strLocalFilePath, strLocalFilePath );
	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CDownLoadObj::AddstrLocalPath()
//	Desc : �⺻ ���("c:\program files\xxx\game\") �� ���ؼ� �߰��ؾ� �ϴ� ��. (xxx.exe)
//	Date : 2003. 06. 23
//	Update : 
//--------------------------------------------------------------------------------------------
void CDownLoadObj::AddstrLocalPath()
{
	strcat( m_strLocalFilePath, m_strDownLoadVersion );
	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CDownLoadObj::SetFolderPath( char *strFolderPath )
//	Desc : FTP ��� ����
//	Date : 2003. 09. 05
//	Update : 
//--------------------------------------------------------------------------------------------
void CDownLoadObj::SetFolderPath( char *strFolderPath )
{
	memset( m_strFolderPath, 0, 128 );
	strcpy( m_strFolderPath, strFolderPath );
	
	return;
}



//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - bool CDownLoadObj::CreateFtpObject()
//	Desc : Ftp ��ü ���� �� Ftp connect
//	Date : 2003. 06. 23
//	Update : 
//--------------------------------------------------------------------------------------------
bool CDownLoadObj::CreateFtpObject()
{
	m_pFtp = new CFtpDownLoad();

	if ( ! m_pFtp->Connect( m_strDownLoadPath, m_strFolderPath, m_strID, m_strPassWord, m_usFtpPort ) )
	{
		return false;
	}

	if ( ! m_pFtp->FtpFileConnect( m_strDownLoadVersion, m_strLocalFilePath ) )
	{
		return false;
	}
	

	return true;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CDownLoadObj::DownLoadStart()
//	Desc : �� ��ü�� ����� ��ġ ������ �ٿ�ε� ����.
//	Date : 2003. 06. 23
//	Update : 
//--------------------------------------------------------------------------------------------
void CDownLoadObj::DownLoadStart()
{
	m_pFtp->FtpDownLoadThreadStart();

	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - CFtpDownLaod *CDownLoadObj::GetFtp()
//	Desc : DownLoad�� ����ϴ� ��ü�� �����͸� ����
//	Date : 2003. 06. 23
//	Update : 
//--------------------------------------------------------------------------------------------
CFtpDownLoad *CDownLoadObj::GetFtp()
{
	return m_pFtp;
}