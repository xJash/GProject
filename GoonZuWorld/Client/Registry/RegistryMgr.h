#ifndef _REGISTRYMGR_H_
#define _REGISTRYMGR_H_

#include <Directives.h>
#include <stdlib.h>
#include <stdio.h>

#define		CHANGE_PATCH_VERSION		90			// CHANGE_PATCH_VERSION�� ���� ������ ���ٸ� Patch1.exe �� �ִ� ���� �����ؼ� �ִٸ�, Patch.exe �� ����� Patch1.exe �� Patch.exe �� �̸��� �ٲ���
													// ������ ���� �ݵ�� �ٲ� �̸��� ���ϸ��� Patch1.exe ���߸� �Ѵٴ� ���̴�.

class CRegistryMgr  
{
public:
	CRegistryMgr(SI32 servicearea=1);
	~CRegistryMgr();

	bool	RegistryCreateKey( HKEY hKey, LPCTSTR lpKey, REGSAM samDesired );

	bool	GetRegReadInt( LPCTSTR lpValueName, UI32* puiReadValue );
	bool	SetRegWriteInt( LPCTSTR lpValueName, UI32 uiWriteValue );

	bool	GetRegReadString( LPCTSTR lpValueName, TCHAR *strReadValue, DWORD dwSize );
	bool	SetRegWriteString( LPCTSTR lpValueName, TCHAR *strWriteValue );
	
	
	//---------------------------------------------------------------------------------
	UI32	GetVersion();							// Version �� ������Ʈ������ �о��
	TCHAR*	GetPath();								// ���� ���(Path) �� ������Ʈ������ �о��
	void	WriteVersion( UI32 uiVersion );			// Version �� ������Ʈ���� ����
	//---------------------------------------------------------------------------------

	
	void	RegistryCloseKey();

private:
	HKEY		m_hKey;
	DWORD		m_dwDisp;

	TCHAR		m_strPath[ _MAX_PATH ];
	UI32		m_uiVersion;

};

#endif