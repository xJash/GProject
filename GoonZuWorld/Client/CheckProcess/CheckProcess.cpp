//#pragma comment(lib, "psapi.lib")

#include "../../CommonLogic/CommonLogic.h"
#include "../../CommonLogic/MsgType-System.h"

#include "../common/Char/CharManager/CharManager.h"
#include "../common/Char/CharServer/Char-Server.h"

#include "../dxutil.h"

#include "CheckProcess.h"
//#include "Psapi.h"
#include "TlHelp32.h"



extern cltCommonLogic* pclClient;


//------------------------------------------------------------------------------------------------------------------------------
// ���⿡�� ���ʹ� Server������ ���˴ϴ�
//------------------------------------------------------------------------------------------------------------------------------
cltCheckProcessMacroList::cltCheckProcessMacroList()
{
	Init();
}

cltCheckProcessMacroList::~cltCheckProcessMacroList()
{
	for ( SI32 siIndex=0; siIndex<Const_Max_MacroList; ++siIndex )
	{
		SAFE_DELETE( m_pclMacro[siIndex] );
	}
}

void cltCheckProcessMacroList::Init( void )
{
	ZeroMemory( this, sizeof(cltCheckProcessMacroList) );
}

bool cltCheckProcessMacroList::AddMacroName( TCHAR* pszMacroName )
{
	if ( (NULL == pszMacroName) || (_tcscmp(pszMacroName, TEXT("")) == 0) )
	{
		return false;
	}

	if ( Const_Max_MacroList <= m_siListCount )
	{
		return false;
	}

	m_pclMacro[m_siListCount] = new cltCheckProcessMacro;
	if ( NULL == m_pclMacro[m_siListCount] )
	{
		return false;
	}

	m_pclMacro[m_siListCount]->Set( pszMacroName );

	++m_siListCount;

	return true;
}

bool cltCheckProcessMacroList::GetMacroNameFirst( OUT TCHAR* pszTextBuffer, IN SI32 siBufferSize )
{
	m_siReadCount = 0; // ���� �о���� ����Ʈ�� ��ȣ�� ó������ �ǵ���

	bool bReturnValue = GetMacorNameNext( pszTextBuffer, siBufferSize );

	return bReturnValue;
}

bool cltCheckProcessMacroList::GetMacorNameNext( OUT TCHAR* pszTextBuffer, IN SI32 siBufferSize )
{
	if ( false == GetMacorNameFromIndex( pszTextBuffer, siBufferSize, m_siReadCount ) )
	{
		return false;
	}

	// GetMacroNameNext���� ������ ������ �ϳ� �÷���
	++m_siReadCount;

	return true;
}

bool cltCheckProcessMacroList::GetMacorNameNow( OUT TCHAR* pszTextBuffer, IN SI32 siBufferSize )
{
	bool bReturnValue = GetMacorNameFromIndex( pszTextBuffer, siBufferSize, m_siReadCount );

	return bReturnValue;
}

bool cltCheckProcessMacroList::GetMacorNameFromIndex( OUT TCHAR* pszTextBuffer, IN SI32 siBufferSize, IN SI32 siIndex )
{
	if ( (NULL == pszTextBuffer) || (0 >= siBufferSize) )
	{
		return false;
	}

	if ( 0 >= m_siListCount )
	{
		return false;
	}
	
	// �˻��Ϸ��� �ε��� ��ȣ�� ���� �����ϴ� ����Ʈ �������� ũ�� �ȵȴ�
	if ( siIndex >= m_siListCount )
	{
		return false;
	}

	// Ȥ�� ���� NULL �˻�
	if ( NULL == m_pclMacro[siIndex] )
	{
		return false;
	}

	StringCchCopy( pszTextBuffer, siBufferSize, m_pclMacro[siIndex]->GetMacroName() );

	return true;

}

void cltCheckProcessMacroList::LoadMacroList( void )
{
	TCHAR		szFileName[]	= TEXT("ServerInfo/MacroList.txt");
	BOOL		bLoadFile		= FALSE;
	NDataLoader	dataloader;

	//KHY - 0810 - �ؽ�Ʈ ���ҽ� ��ȣȭ.
	if( pclClient->IsWhereServiceArea( ConstSwitch_TextEncryption ) )
	{
		bLoadFile = dataloader.LoadDataFromCryptFile( szFileName );
	}
	else
	{
		bLoadFile = dataloader.LoadDataFromFile( szFileName );
	}

	if (!bLoadFile)
	{
		return;
	}

	TCHAR szMacroName[64] = TEXT("");

	NDataTypeInfo pDataTypeInfo[] =
	{
		NDATA_MBSTRING,	szMacroName,	64,
		0,0,0
	};

	dataloader.RegDataType( pDataTypeInfo );

	SI16 index = 0;

	while( !dataloader.IsEndOfData() ) 
	{
		if (dataloader.ReadData())	
		{
			AddMacroName( szMacroName );
		}
	}
}

//------------------------------------------------------------------------------------------------------------------------------
// ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ�
// ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ�
// ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ�
//------------------------------------------------------------------------------------------------------------------------------

cltCheckProcessPersonInfo::cltCheckProcessPersonInfo()
{
	Init();
}

cltCheckProcessPersonInfo::~cltCheckProcessPersonInfo()
{
}

void cltCheckProcessPersonInfo::Init()
{
	ZeroMemory( this, sizeof(cltCheckProcessPersonInfo) );
}

//------------------------------------------------------------------------------------------------------------------------------
// ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ�
// ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ�
// ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ�
//------------------------------------------------------------------------------------------------------------------------------

cltCheckProcessManager::cltCheckProcessManager()
{
	Init();
}

cltCheckProcessManager::~cltCheckProcessManager()
{
	DestroyPersonInfo();
}

void cltCheckProcessManager::DestroyPersonInfo()
{
	for ( SI32 siIndex=0; siIndex<MAX_PERSON_NUMBER; ++siIndex )
	{
		SAFE_DELETE( m_pclCP_PersonInfo[siIndex] );
	}

}

void cltCheckProcessManager::Init()
{
	ZeroMemory( this, sizeof(cltCheckProcessManager) );

	// 1������ ����
#ifdef _DEBUG
	m_kUpdateTimer_WaitTime.Init(5 * 1000);
#else
	m_kUpdateTimer_WaitTime.Init(60 * 1000);
#endif
}

void cltCheckProcessManager::InitForLog()
{
	DestroyPersonInfo();

	ZeroMemory( m_szModuleName, sizeof(m_szModuleName) );

	m_siPersonCount = 0;

	m_siGMPersonID	= 0;
}

void cltCheckProcessManager::Action()
{
	if ( CHECKPROCESS_STATE_READY == m_siState )
	{
		return;
	}

	if ( m_kUpdateTimer_WaitTime.IsTimed(::GetTickCount(), false) ) 
	{
		// �ϴ� ���� ���� ����
		m_siState = CHECKPROCESS_STATE_READY;

		switch ( m_siType ) 
		{
			case CHECKPROCESS_TYPE_MULTICLIENT:
				{
					WriteLog();
				}
				break;
			
			// ��ũ�ζ�� ����Ʈ�� �ִ� ���� ����� �˻��Ѵ�
			case CHECKPROCESS_TYPE_MACRO:
				{
					// �α׸� ����ϸ� ��� �ʱ�ȭ�� �Ǳ⶧���� ���⿡�� GM�� PersonID�� ����� ���´�
					SI32 siGMPersonID = m_siGMPersonID;

					WriteLog();

					// ����Ʈ�� �ִ� ���� ����� �˻��Ѵ�
					TCHAR szModuleName[Const_Max_Module_Name] = { '\0', };
					if ( false == m_clMacroList.GetMacorNameNext(szModuleName, sizeof(szModuleName)) )
					{
						return;
					}

					// ������ ���ƴ� GM PersonID�� �ǵ���
					m_siGMPersonID = siGMPersonID;

					SendOrderToClient( m_siGMPersonID, CHECKPROCESS_TYPE_MACRO, szModuleName );
				}
				break;

			case CHECKPROCESS_TYPE_MODULENAME:
				{
					WriteLog();
				}
				break;
		}	
	}
	
}

bool cltCheckProcessManager::SendOrderToClient( SI32 siGMPersonID, SI32 siType, TCHAR* pszModuleName/* =NULL  */)
{
	// �ѹ��� �ϳ��� ����� �� �ֵ��� �̹� �������̶�� ������Ѵ�
	if ( CHECKPROCESS_STATE_PROCESSING == m_siState )
	{
		return false;
	}

	if ( (CHECKPROCESS_TYPE_NONE >= siType) || (CHECKPROCESS_TYPE_MAX <= siType) )
	{
		return false;
	}

	
	ZeroMemory( m_szModuleName, sizeof(m_szModuleName) );


	switch ( siType )
	{
		case CHECKPROCESS_TYPE_MULTICLIENT:
			{
				// �ϴ��� ����				
			}
			break;

		case CHECKPROCESS_TYPE_MACRO:
			{
				if ( NULL == pszModuleName )
				{
					// �������� �μ��� ������ �������� ��ũ�� ����Ʈ�� �� ó�� �̸��� ����´�
					if ( false == m_clMacroList.GetMacroNameFirst(m_szModuleName, sizeof(m_szModuleName)) )
					{
						return false;
					}
				}
				else
				{
					// �׷��� ������� �μ��� ���� �̸�����
					if ( _tcscmp(pszModuleName, TEXT("")) == 0 )
					{
						return false;
					}

					StringCchCopy( m_szModuleName, sizeof(m_szModuleName), pszModuleName );
				}
			}
			break;

		case CHECKPROCESS_TYPE_MODULENAME:
			{
				// ��ڰ� ������ �̸����� ����
				if ( (NULL == pszModuleName) || (_tcscmp(pszModuleName, TEXT("")) == 0) )
				{
					return false;
				}
				
				StringCchCopy( m_szModuleName, sizeof(m_szModuleName), pszModuleName );
			}
			break;
	}

	// GM ID ����
	m_siGMPersonID	= siGMPersonID;

	// ���� Ÿ���� ���Ѵ�
	m_siType		= siType;

	// ���縦 ���������� �����ϰ�
	m_siState		= CHECKPROCESS_STATE_PROCESSING;

	// ������ ��� �������� ���μ���üũ�� ������
	cltGameMsgResponse_CheckProcess clInfo( m_szModuleName, siType );
	cltMsg clMsg( GAMEMSG_RESPONSE_CHECKPROCESS, sizeof(clInfo), (BYTE*)&clInfo );
	pclClient->pclCM->SendAllPersonMsg( (sPacketHeader*)&clMsg );
	
	// ��ٸ� �ð��� �۵��Ѵ�
	m_kUpdateTimer_WaitTime.SetActive( true , ::GetTickCount() );

	return true;
}

void cltCheckProcessManager::SendResultToGM( SI16* psiList )
{
	if ( NULL == psiList )
	{
		return;
	}
	
	SI32 siGMCharID = pclClient->pclCM->GetIDFromPersonID( m_siGMPersonID );

	cltCharServer* pclchar = pclClient->pclCM->GetCharServer( siGMCharID );
	if ( NULL == pclchar )
	{
		return;
	}

	// Ȥ�� ���� ������ ID�� GM�� �ƴҶ�
	if ( BASIC_GAMEMASTER_LEVEL >= pclchar->GetGameMasterLevel() )
	{
		return;
	}


	cltGameMsgResponse_CheckProcess_Result clInfo( m_szModuleName, psiList, m_siType );
	cltMsg clMsg( GAMEMSG_RESPONSE_CHECKPROCESS_RESULT, sizeof(clInfo), (BYTE*)&clInfo );
	pclchar->SendNetMsg( (sPacketHeader*)&clMsg );


}

void cltCheckProcessManager::CompareSameUser( IN SI16* psiMultiClientList, OUT SI16* psiSendList )
{
	if ( (NULL == psiMultiClientList) || (NULL == psiSendList) )
	{
		return;
	}

	// 2������ 21�������� �ο��� 60�� ����
	SI16 siCompareList[Const_Max_SendList][60];
	memset( siCompareList, -1, sizeof(siCompareList) );


	for ( SI32 siIndex=0; siIndex<MAX_PERSON_NUMBER; ++siIndex )
	{
		SI16 siListIndex = psiMultiClientList[siIndex];

		if ( -1 >= siListIndex )
		{
			break;
		}

		cltCheckProcessPersonInfo* pclPersonInfo = m_pclCP_PersonInfo[siListIndex];
		if ( NULL == pclPersonInfo )
		{
			continue;
		}

		SI16 siRealSearchIndex = (pclPersonInfo->GetProcessCount() - 2);

		// Ȥ�� �׷����� �������� ��ƼŬ���� ������ 22���� �Ѿ��
		if ( (Const_Max_SendList+2) <= siRealSearchIndex )
		{
			//���⿡�� ������ �Ұ��ΰ� ���ؾ��Ѵ�
			continue;
		}
		
		
		for ( SI32 siSearchIndex=0; siSearchIndex<60; ++siSearchIndex )
		{
			if ( -1 >= siCompareList[siRealSearchIndex][siSearchIndex] )
			{
				siCompareList[siRealSearchIndex][siSearchIndex] = siListIndex;
				break;
			}
			else if ( true == pclPersonInfo->IsSame( m_pclCP_PersonInfo[siCompareList[siRealSearchIndex][siSearchIndex]] ) )
			{
				break;
			}
		}
	}

	for ( SI32 siCount=0; siCount<Const_Max_SendList; ++siCount )
	{
		for ( SI32 siListCount=0; siListCount<60; ++siListCount )
		{
			if ( -1 < siCompareList[siCount][siListCount] )
			{
				psiSendList[siCount] += 1;
			}
		}
	}

}

bool cltCheckProcessManager::AddPersonInfo( SI32 siCharID, SI16 siProcessCount, TCHAR* pszMacAddress )
{
	if ( MAX_PERSON_NUMBER <= m_siPersonCount )
	{
		return false;
	}

	cltCharServer* pclchar = pclClient->pclCM->GetCharServer( siCharID );
	if ( NULL == pclchar )
	{
		return false;
	}

	m_pclCP_PersonInfo[ m_siPersonCount ] = new cltCheckProcessPersonInfo;
	if ( NULL == m_pclCP_PersonInfo[m_siPersonCount] )
	{
		return false;
	}

	m_pclCP_PersonInfo[ m_siPersonCount ]->Set( pclchar->pclCI->GetPersonID(), siCharID, siProcessCount, pclchar->GetSession()->GetIP(), pszMacAddress );

	++m_siPersonCount;

	return true;

}

void cltCheckProcessManager::WriteLog( void )
{
	TCHAR szFileName[MAX_PATH] = { '\0', }; 
	if ( false == GetSaveLogFileName(szFileName, sizeof(szFileName)) )
	{
		return;
	}

	// ��Ƽ Ŭ���̾�Ʈ�� ����ϴ� ������ �ε����� ����
	SI16 siMulticlientList[MAX_PERSON_NUMBER];
	SI16 siListCount = 0;

	// ��ũ�� ����� ī��Ʈ
	SI16 siUserCount = 0;

	// �ε����� 0���� �����ϴϱ� -1�� �ʱ�ȭ
	memset( siMulticlientList, -1, sizeof(siMulticlientList) );

	for ( SI32 siIndex=0; siIndex<MAX_PERSON_NUMBER; ++siIndex )
	{
		if ( NULL == m_pclCP_PersonInfo[siIndex] )
		{
			break;
		}

		cltCheckProcessPersonInfo* pclPersonInfo = m_pclCP_PersonInfo[siIndex];
		if ( NULL == pclPersonInfo )
		{
			continue;
		}
		
		// ��ƼŬ���̾�Ʈ ����� üũ�ÿ��� ����
		if ( 2 <= pclPersonInfo->GetProcessCount() )
		{
			siMulticlientList[siListCount] = siIndex;
			
			++siListCount;
		}

		// ��ũ��/��� üũ�ÿ��� ����
		++siUserCount;

		// ���⼭ NULL ���͵� �Ʒ����� üũ�մϴ�
		cltCharServer* pclchar = pclClient->pclCM->GetCharServer( pclPersonInfo->GetCharID() );

		NTCHARString512 strLog( TEXT("#personid#\t#noname#\t#count#\t#ip#\t#mac#") );

		strLog.Replace( TEXT("#personid#"),	SI32ToString(pclPersonInfo->GetPersonID()) );
		strLog.Replace( TEXT("#count#"),	SI32ToString(pclPersonInfo->GetProcessCount()) );
		strLog.Replace( TEXT("#ip#"),		pclPersonInfo->GetIP() );
		strLog.Replace( TEXT("#mac#"),		pclPersonInfo->GetMacAddress() );
		
		// Ȥ�� PersonID�� �ٸ����� �ֱ⶧���� ���� �˻�
		if ( (pclchar) && (pclchar->pclCI->GetPersonID() == pclPersonInfo->GetPersonID()) )
		{
			strLog.Replace( TEXT("#noname#"), pclchar->GetName() );
		}

		pclClient->pclLog->FilePrint( szFileName, (TCHAR*)strLog );
	}

	// �α� �ۼ��� ����� ��û�� GM���� ������
	SI16 siSendList[Const_Max_SendList] = { 0, };

	switch ( m_siType )
	{
		case CHECKPROCESS_TYPE_MULTICLIENT:
			{
				CompareSameUser( siMulticlientList, siSendList );
			}
			break;
		case CHECKPROCESS_TYPE_MACRO:
		case CHECKPROCESS_TYPE_MODULENAME:
			{
				siSendList[0] = siUserCount;
			}
			break;
	}

	SendResultToGM( siSendList );

	// ��� �α� ���� ������ �ʱ�ȭ �Ѵ�
	InitForLog();
}

bool cltCheckProcessManager::GetSaveLogFileName( TCHAR* pszTextBuffer, SI32 siBufferSize )
{
	if ( (NULL == pszTextBuffer) || (0 >= siBufferSize) )
	{
		return false;
	}

	cltServer* pclserver = (cltServer*)pclClient;
	if ( NULL == pclserver )
	{
		return false;
	}

	UI16 uiYear		= pclserver->sTime.wYear;
	UI16 uiMonth	= pclserver->sTime.wMonth;
	UI16 uiDay		= pclserver->sTime.wDay;

	switch ( m_siType )
	{
		case CHECKPROCESS_TYPE_MULTICLIENT:
			{
				StringCchPrintf( pszTextBuffer, siBufferSize, TEXT("Config/MulitClient_%04d%02d%02d.log"), uiYear, uiMonth, uiDay );
			}
			break;

		case CHECKPROCESS_TYPE_MACRO:
			{
				StringCchPrintf( pszTextBuffer, siBufferSize, TEXT("Config/Macro_%s_%04d%02d%02d.log"), m_szModuleName, uiYear, uiMonth, uiDay );
			}
			break;

		case CHECKPROCESS_TYPE_MODULENAME:
			{
				StringCchPrintf( pszTextBuffer, siBufferSize, TEXT("Config/Module_%s_%04d%02d%02d.log"), m_szModuleName, uiYear, uiMonth, uiDay );
			}
			break;

		default:
			return false;
	}

	return true;
}

void cltCheckProcessManager::LoadMacroList( void )
{
	m_clMacroList.LoadMacroList();
}

//------------------------------------------------------------------------------------------------------------------------------
// ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ�
// ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ�
// ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ� ��輱 �Դϴ�
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
// ���⿡�� ���ʹ� Client������ ���˴ϴ�
//------------------------------------------------------------------------------------------------------------------------------

cltCheckProcess::cltCheckProcess()
{
	Init();
}

cltCheckProcess::~cltCheckProcess()
{
}

void cltCheckProcess::Init()
{
	ZeroMemory( this, sizeof(cltCheckProcess) );

	// �� ��� �̸�(����)��������
	GetGoonZuModuleName( m_szGoonZuModuleName, sizeof(m_szGoonZuModuleName) );
}

// ���� �� ��� �̸��� �����´�
BOOL cltCheckProcess::GetGoonZuModuleName( TCHAR* pszGoonZuName, SI32 siTextSize )
{
	// 98 ȣȯ���� ���� �Ʒ� ���� ����
	/*
	HANDLE hThisProcess = GetCurrentProcess();

	if ( hThisProcess )
	{
		if ( 0 < GetModuleBaseName(hThisProcess, NULL, pszGoonZuName, siTextSize) )
		{
			return TRUE;
		}
	}

	return FALSE;
	*/

	if ( (NULL == pszGoonZuName) || (0 >= siTextSize) )
	{
		return FALSE;
	}

	switch ( pclClient->siServiceArea )
	{
	case ConstServiceArea_Japan:
		{
			StringCchCopy( pszGoonZuName, siTextSize, TEXT("Kunshu.exe") );
		}
		break;

	case ConstServiceArea_EUROPE:
	case ConstServiceArea_USA:
		{
			StringCchCopy( pszGoonZuName, siTextSize, TEXT("Luminary.exe") );
		}
		break;

	default:
		{
			StringCchCopy( pszGoonZuName, siTextSize, TEXT("GoonZu.exe") );
		}
		break;
	}

	return TRUE;
}

/* �̳༮�� 95,98d�� ������ �ȵǴϱ� �Ʒ� ���� �༮���� ����
SI32 cltCheckProcess::GetGoonZuProcessCount()
{
	// �� ��� �̸�(����)��������
	TCHAR		szGoonZuModuleName[Const_Max_Module_Name] = { '\0',  };
	if ( FALSE == GetGoonZuModuleName(szGoonZuModuleName, sizeof( szGoonZuModuleName )) )
	{
		return 0;
	}
	
	SI32		siReturnCount			= 0;

	DWORD		dwProcessList[1024]		= {0, };
	DWORD		cb						= 0;
	SI32		siProcessCount			= 0;

	HANDLE		hProcess;
	HMODULE		hModule;
	TCHAR		szProcessName[256]		= {'\0', };

	// ���μ��� ����� �迭�� ���ϰ� ������ ����.
	::EnumProcesses(dwProcessList, sizeof(dwProcessList), &cb);
	siProcessCount = cb/sizeof(cb);

	// �� ���μ��� ��Ͽ��� ���� �� �̸��� ���� ���μ����� �˻���
	for ( SI32 siIndex=0; siIndex<siProcessCount; ++siIndex )
	{
		hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, dwProcessList[siIndex] );

		if ( (hProcess) && (EnumProcessModules(hProcess, &hModule, sizeof( hModule ), &cb)) )
		{
			GetModuleBaseName( hProcess, hModule, szProcessName, sizeof(szProcessName) );
			if ( (_tcscmp( szProcessName, szGoonZuModuleName ) == 0) )
			{
				++siReturnCount;
			}
		} 
	}

	return siReturnCount;
}
*/

SI32 cltCheckProcess::GetGoonZuProcessCount()
{
	SI32 siReturnCount = GetProcessCountFormModuleName( m_szGoonZuModuleName );

	return siReturnCount;
	
}

// win95/98/2000 ����(nt4.0�� ��������-���� ���⼭ ���ָ�?)
SI32 cltCheckProcess::GetProcessCountFormModuleName( const TCHAR* pszModuleName )
{
	if ( NULL == pszModuleName )
	{
		return 0;
	}

	if ( _tcscmp(pszModuleName, TEXT("")) == 0 )
	{
		return 0;
	}

	SI32	siReturnCount = 0;

	HANDLE	hSnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
	if ( INVALID_HANDLE_VALUE == hSnap )
	{
		return 0;
	}

	PROCESSENTRY32	peEntry;	// ��������� �޾ƿ� ����ü
	peEntry.dwSize = sizeof(PROCESSENTRY32);

	SI32 siExitCount	= 0;	// Ż���

	BOOL bContinue		= Process32First( hSnap, &peEntry );


	while ( bContinue )
	{
		// Ȥ�� �ݺ����� ������ ����ɱ��
		if ( Const_Max_Exit_Count <= siExitCount++ )
		{
			break;
		}

		// �μ��� ����̸��� ������
		if ( _tcscmp(peEntry.szExeFile, pszModuleName) == 0 )
		{
			++siReturnCount;
		}

		bContinue = Process32Next( hSnap, &peEntry );
	}

	CloseHandle( hSnap );


	return siReturnCount;
}

void cltCheckProcess::ExcuteCheckProcess( SI32 siType, TCHAR* pszModuleName )
{
	cltClient* pclclient = (cltClient*)pclClient;
	if ( NULL == pclclient )
	{
		return;
	}

	cltCharClient* pclchar = pclClient->pclCM->GetCharClient(1);
	if ( NULL == pclchar )
	{
		return;
	}

	SI16 siModuleCount = 0;

	// ��� üũ Ÿ�Կ� ���� �з�
	switch ( siType )
	{
		case CHECKPROCESS_TYPE_MULTICLIENT:
			{
				siModuleCount = GetGoonZuProcessCount();
			}
			break;

		case CHECKPROCESS_TYPE_MACRO:
		case CHECKPROCESS_TYPE_MODULENAME:
			{
				if ( (NULL == pszModuleName) || (_tcscmp(pszModuleName, TEXT("")) == 0) )
				{
					return;
				}
			
				siModuleCount = GetProcessCountFormModuleName( pszModuleName );
			}
			break;

		default:
			{
				return;
			}
	}

	// üũ�ߴµ� �̰��� ����� 0�̶�� ���� �ʿ����
	if ( 0 >= siModuleCount )
	{
		return;
	}

	// Ŭ���̾�Ʈ�� MacAddress�� �����´�
	TCHAR szMacAddress[Const_Max_MacAddress] = { '\0', };
	pclclient->GetMacAddress( pclchar->GetSession()->GetSocket(), szMacAddress, sizeof(szMacAddress) );
	

	cltGameMsgRequest_CheckProcess clInfo( szMacAddress, siModuleCount );
	cltMsg clMsg( GAMEMSG_REQUEST_CHECKPROCESS, sizeof(clInfo), (BYTE*)&clInfo );
	pclclient->SendMsgToServer( (sPacketHeader*)&clMsg );
}