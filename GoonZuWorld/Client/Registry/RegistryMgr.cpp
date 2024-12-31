#include "RegistryMgr.h"
#include "CommonHeader.h"

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - CRegistryMgr::CRegistryMgr()
//	Desc : �� �� ��
//	Date : 2003. 06. 13
//	Update : 2003. 07. 04 - ���ֿ븸���� ���� ����
//--------------------------------------------------------------------------------------------
CRegistryMgr::CRegistryMgr(SI32 servicearea)
{
	memset( m_strPath, 0, _MAX_PATH );
	m_uiVersion = 0;
	m_hKey = NULL;

	if ( servicearea == ConstServiceArea_English )
		RegistryCreateKey( HKEY_CURRENT_USER, TEXT("Software\\NDOORS\\GoonZuEng"), KEY_ALL_ACCESS );
	else if( servicearea == ConstServiceArea_Japan )
#ifdef	_JAPAN_USER_TEST
		RegistryCreateKey( HKEY_CURRENT_USER, TEXT("Software\\GamePot\\Kunshu User Test"), KEY_ALL_ACCESS );
#else
		RegistryCreateKey( HKEY_CURRENT_USER, TEXT("Software\\GamePot\\Kunshu Online"), KEY_ALL_ACCESS );
#endif
	else if( servicearea == ConstServiceArea_China )
		RegistryCreateKey( HKEY_CURRENT_USER, TEXT("Software\\NDOORS\\GoonZuChina"), KEY_ALL_ACCESS );
	else if( servicearea == ConstServiceArea_Taiwan )
		RegistryCreateKey( HKEY_CURRENT_USER, TEXT("Software\\NDOORS\\GoonZuTaiwan"), KEY_ALL_ACCESS );
	else if( servicearea == ConstServiceArea_USA )
		RegistryCreateKey( HKEY_CURRENT_USER, TEXT("Software\\NDOORS\\Luminary"), KEY_ALL_ACCESS );
	else if( servicearea == ConstServiceArea_NHNChina )
		RegistryCreateKey( HKEY_CURRENT_USER, TEXT("Software\\NDOORS\\GoonZuNHNCHINA"), KEY_ALL_ACCESS );
	else if( servicearea == ConstServiceArea_EUROPE )
		RegistryCreateKey( HKEY_CURRENT_USER, TEXT("Software\\NDOORS\\GoonZuEurope"), KEY_ALL_ACCESS );
	else
		RegistryCreateKey( HKEY_CURRENT_USER, TEXT("Software\\NDOORS\\GoonZu"), KEY_ALL_ACCESS );
	
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - CRegistryMgr::~CRegistryMgr()
//	Desc : �� �� ��
//	Date : 2003. 06. 13
//	Update :
//--------------------------------------------------------------------------------------------
CRegistryMgr::~CRegistryMgr()
{
	if ( m_hKey != NULL )
	{
		RegCloseKey( m_hKey );
		m_hKey = NULL;
	}
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - bool CRegistryMgr::RegistryCreateKey( HKEY hKey, LPCTSTR lpKey, REGSAM samDesired )
//	Desc : RegCreateKeyEx ����
//		   samDesired �����δ� KEY_READ �Ǵ� KEY_WRITE�� �� �����. �Ѵ� �ҷ��� KEY_ALL_ACCESS
//	Date : 2003. 06. 13
//	Update :
//--------------------------------------------------------------------------------------------
bool CRegistryMgr::RegistryCreateKey( HKEY hKey, LPCTSTR lpKey, REGSAM samDesired )
{
	if ( ::RegCreateKeyEx( hKey, lpKey, 0, NULL, REG_OPTION_NON_VOLATILE, samDesired, NULL, &m_hKey, &m_dwDisp ) != ERROR_SUCCESS )
	{
		return false;
	}

	return true;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - bool CRegistryMgr::GetRegReadInt( LPCTSTR lpValueName, UI32 *puiReadValue )
//	Desc : ������Ʈ������ ������ ���� �о��.
//	Date : 2003. 06. 13
//	Update :
//--------------------------------------------------------------------------------------------
bool CRegistryMgr::GetRegReadInt( LPCTSTR lpValueName, UI32 *puiReadValue )
{
	DWORD Size;

	Size = sizeof(LONG);

	if ( ::RegQueryValueEx( m_hKey, lpValueName, 0, NULL, (LPBYTE)puiReadValue, &Size ) != ERROR_SUCCESS )
	{
		RegCloseKey( m_hKey );
		m_hKey = NULL;
		return false;
	}

	return true;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - bool CRegistryMgr::SetRegWriteInt( LPCTSTR lpValueName, UI32 uiWriteValue )
//	Desc : ������Ʈ���� ������ ���� �Է�.
//	Date : 2003. 06. 13
//	Update :
//--------------------------------------------------------------------------------------------
bool CRegistryMgr::SetRegWriteInt( LPCTSTR lpValueName, UI32 uiWriteValue )
{
	if ( ::RegSetValueEx( m_hKey, lpValueName, 0, REG_DWORD, (LPBYTE)&uiWriteValue, sizeof( UINT ) ) != ERROR_SUCCESS )
	{
		RegCloseKey( m_hKey );
		m_hKey = NULL;
		return false;
	}
	
	return true;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - bool CRegistryMgr::GetRegReadString( LPCTSTR lpValueName, CC08 *strReadValue, DWORD dwSize )
//	Desc : ������Ʈ������ ���ڿ� ���� �о��.
//	Date : 2003. 06. 13
//	Update :
//--------------------------------------------------------------------------------------------
bool CRegistryMgr::GetRegReadString( LPCTSTR lpValueName, TCHAR *strReadValue, DWORD dwSize )
{
	DWORD ldwSize = dwSize;

	if ( ::RegQueryValueEx( m_hKey, lpValueName, 0, NULL, (LPBYTE)strReadValue, &ldwSize ) != ERROR_SUCCESS )
	{
		RegCloseKey( m_hKey );
		m_hKey = NULL;
		return false;
	}
	
	return true;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - bool CRegistryMgr::SetRegWriteString( LPCTSTR lpValueName, TCHAR *strWriteValue )
//	Desc : ������Ʈ������ ���ڿ� ���� �Է�.
//	Date : 2003. 06. 13
//	Update :
//--------------------------------------------------------------------------------------------
bool CRegistryMgr::SetRegWriteString( LPCTSTR lpValueName, TCHAR *strWriteValue )
{
	if ( ::RegSetValueEx( m_hKey, lpValueName, 0, REG_SZ, (LPBYTE)strWriteValue, _tcslen(strWriteValue) + 1 ) != ERROR_SUCCESS )
	{
		RegCloseKey( m_hKey );
		m_hKey = NULL;
		return false;
	}

	return true;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - UI32 CRegistryMgr::GetVersion()
//	Desc : ������Ʈ���� �������� �о ������
//	Date : 2003. 07. 04
//	Update : 
//--------------------------------------------------------------------------------------------
UI32 CRegistryMgr::GetVersion()
{
	m_uiVersion = 0;

	if( m_hKey )
	{
		GetRegReadInt( TEXT("VERSION"), &m_uiVersion );


		/*
		//--------------------------------------------------------
		//-- ��ġ ���α׷� �ٲٴ� �� ó�� ( ���� Ŭ���̾�Ʈ���� ó���� )
		//if ( m_uiVersion > CHANGE_PATCH_VERSION )			// ������ CHANGE_PATCH_VERSION ���� ���ٸ� ���ӿ��� Patch1.exe �� Patch.exe �� �ٲ���.
		//{
			WIN32_FIND_DATA	wfd;

			HANDLE hSrch = FindFirstFile( TEXT("GoonZuRun1.exe"), &wfd );

			if ( hSrch != INVALID_HANDLE_VALUE )
			{
				if ( DeleteFile(  TEXT("Patch.exe") ) == TRUE )
				{
					rename( TEXT("GoonZuRun1.exe"), TEXT("Patch.exe") );
					CopyFile( TEXT("Patch.exe"), TEXT("GoonZuRun.exe"), FALSE );
				}
				else
				{
					DeleteFile(  TEXT("GoonZuRun.exe") );
					rename( TEXT("GoonZuRun1.exe"), TEXT("GoonZuRun.exe") );
				}
				
				FindClose( hSrch );
			}
		//}
		//--------------------------------------------------------
		*/
		
	}

	return m_uiVersion;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - TCHAR* CRegistryMgr::GetPath()
//	Desc : ���� ��θ� �� ������
//	Date : 2003. 07. 04
//	Update : 
//--------------------------------------------------------------------------------------------
TCHAR* CRegistryMgr::GetPath()
{
	memset( m_strPath, 0, _MAX_PATH );

	if ( m_hKey )
	{
		GetRegReadString( TEXT("PATH"), m_strPath, _MAX_PATH );		
	}
	else
	{
		StringCchCopy( m_strPath, _MAX_PATH, TEXT("Registry Error") );
	}

	return m_strPath;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CRegistryMgr::WriteVersion( UI32 uiVersion )
//	Desc : Version�� ������Ʈ���� ����
//	Date : 2003. 07. 04
//	Update : 
//--------------------------------------------------------------------------------------------
void CRegistryMgr::WriteVersion( UI32 uiVersion )
{
	uiVersion = 0;

	if ( m_hKey )
	{
		SetRegWriteInt( TEXT("VERSION"), uiVersion );
	}

	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CRegistryMgr::RegistryCloseKey()
//	Desc : Create �ߴ� Key �� �ݾ� �ش�.
//	Date : 2004. 04. 15
//	Update : 
//--------------------------------------------------------------------------------------------
void CRegistryMgr::RegistryCloseKey()
{
	RegCloseKey( m_hKey );
	m_hKey  = NULL;
	return;
}
