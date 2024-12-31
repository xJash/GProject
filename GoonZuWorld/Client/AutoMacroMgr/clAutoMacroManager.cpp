#include "../Client/AutoMacroMgr/clAutoMacroManager.h"
#include "TlHelp32.h"
//#include "Psapi.h"
//#pragma comment(lib, "psapi.lib")


CAutoMacroManager::CAutoMacroManager(void)
{
	ZeroMemory(this, sizeof(CAutoMacroManager));

	NEW_PROCESS_NAME(m_pszProcessName[0], "OK����SPlus.exe");	
}

CAutoMacroManager::~CAutoMacroManager(void)
{
	for(SI32 i = 0; i < MAX_PROCESS_NAME_COUNT; ++i)
	{
		SAFE_DELETE_ARRAY(m_pszProcessName[i])
	}
}

void CAutoMacroManager::Init(void)
{
	
}

void CAutoMacroManager::ShutDown(void)
{
	for(SI32 i = 0; i < MAX_PROCESS_NAME_COUNT; ++i)
	{
		SAFE_DELETE_ARRAY(m_pszProcessName[i])
	}

	// Ŭ���̾�Ʈ ����.
	exit(1);
}


bool CAutoMacroManager::IsCheckMacro(void)
{
	// ȣȯ���� ���� �̺κ� ����
	/* 
	DWORD thisProcess	= GetCurrentProcessId();
	HANDLE hSnapshot	= ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	
	PROCESSENTRY32	pe32;
	pe32.dwSize		= sizeof(PROCESSENTRY32);
	BOOL bContiue	= Process32First(hSnapshot,&pe32);

	DWORD		arProcess[1024], cb;
	SI32		siProcessCnt;
	HANDLE		hProcess;
	HMODULE		hModule;
	TCHAR		szProcessName[256];

	// ���μ��� ����� �迭�� ���ϰ� ������ ����.
	::EnumProcesses(arProcess, sizeof(arProcess), &cb);
	siProcessCnt = cb/sizeof(cb);

	for(SI32 i = 0; i < MAX_PROCESS_NAME_COUNT; ++i)
	{
		//// ã�� ���μ����� �̸��� ������� ���ٴ� �����Ͽ� NULL �� ������ ���̻� �˻縦 ���� �ʴ´�.
		if(NULL == m_pszProcessName[i])
			break;
		
		for(SI32 j = 0; j < siProcessCnt; ++j)
		{
			hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, arProcess[j]);
			if(hProcess)
			{
				if(EnumProcessModules(hProcess, &hModule, sizeof(hModule), &cb))	
				{
					GetModuleBaseName(hProcess, hModule, szProcessName, sizeof(szProcessName));
					if( (_tcscmp(szProcessName, m_pszProcessName[i]) == 0 ))
					{
						CloseHandle(hSnapshot);
						return true;
					}
				}
			} 
		}
		

		CloseHandle(hSnapshot);
	}

	return false;
	*/

	/////////////////////////////////////////////////

	HANDLE	hSnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
	if ( INVALID_HANDLE_VALUE == hSnap )
	{
		return false;
	}

	PROCESSENTRY32	peEntry;	// ��������� �޾ƿ� ����ü
	peEntry.dwSize = sizeof(PROCESSENTRY32);

	BOOL			bContinue = false;

	for ( SI32 siCount=0; siCount<MAX_PROCESS_NAME_COUNT; siCount++ )
	{
		if( NULL == m_pszProcessName[siCount] )
		{
			break;
		}

		bContinue = Process32First( hSnap, &peEntry );

		while ( bContinue )
		{
			// �μ��� ����̸��� ������
			if ( _tcscmp(peEntry.szExeFile, m_pszProcessName[siCount]) == 0 )
			{
				CloseHandle( hSnap );
				return true;
			}

			bContinue = Process32Next( hSnap, &peEntry );
		}
	}

	CloseHandle( hSnap );

	return false;

}


bool CAutoMacroManager::Undate(void)
{
	// �������α׷��� ����Ѵٸ� ó��.
	if(true == IsCheckMacro())
	{
		return true;	
	}
	
	return false;
}
