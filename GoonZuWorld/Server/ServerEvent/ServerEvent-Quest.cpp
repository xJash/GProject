#include "../CommonLogic/CommonLogic.h"

#include "../common/Char/KindInfo/kindinfo.h"
#include "../common/Char/CharManager/CharManager.h"
#include "../common/NPCManager/NPC.h"

#include "../dxutil.h"

#include "../CommonLogic/MsgType-System.h"
#include "../DBManager/GameDBManager_World/DBMsg-Item.h"
#include "../DBManager/GameDBManager_World/DBMsg-System.h"


#include "ServerEvent-Quest.h"

extern cltCommonLogic* pclClient;

CNServerEvent_QuestData::CNServerEvent_QuestData( void ) : 
	m_siEventType(0),			// ���� �̺�Ʈ Ÿ��

	m_siCondition1(0),			// Ŭ���� �ϱ� ���� �ʿ��� ���� 1
	m_siCondition2(0),			// Ŭ���� �ϱ� ���� �ʿ��� ���� 2

	m_siNeedClearAmount(0),		// Ŭ���� �ϱ� ���� �ʿ��� ����

	m_siRewardItemUnique(0),	// Ŭ����� ����Ǵ� ������(����ũ)
	m_siRewardItemAmount(0),	// ����Ǵ� ������ ����

	m_siLimitMinute(0)			// ���ѽð�
{

}

CNServerEvent_QuestData::CNServerEvent_QuestData( CNServerEvent_QuestData* pclSEQuestData )
{
	if ( NULL == pclSEQuestData )
	{
		return;
	}

	SetServerEvent_QuestData( pclSEQuestData );
}

CNServerEvent_QuestData::~CNServerEvent_QuestData()
{

}

void CNServerEvent_QuestData::Init()
{
	ZeroMemory( this, sizeof(CNServerEvent_QuestData) );
}

bool CNServerEvent_QuestData::SetServerEvent_QuestData( 
	SI32	siEventType,

	SI32	siCondition1,
	SI32	siCondition2,

	SI32	siNeedClearAmount,

	SI32	siRewardItemUnique,
	SI32	siRewardItemAmount,

	SI32	siLimitMinute
)
{
	if ( (SERVEREVENT_TYPE_NONE >= siEventType) || ( SERVEREVENT_TYPE_END <= siEventType) )
	{
		return false;
	}

	m_siEventType			= siEventType;			// ���� �̺�Ʈ Ÿ��

	m_siCondition1			= siCondition1;			// Ŭ���� �ϱ� ���� �ʿ��� ���� 1
	m_siCondition2			= siCondition2;			// Ŭ���� �ϱ� ���� �ʿ��� ���� 2

	m_siNeedClearAmount		= siNeedClearAmount;	// Ŭ���� �ϱ� ���� �ʿ��� ����

	m_siRewardItemUnique	= siRewardItemUnique;	// Ŭ����� ����Ǵ� ������(����ũ)
	m_siRewardItemAmount	= siRewardItemAmount;	// ����Ǵ� ������ ����

	m_siLimitMinute			= siLimitMinute;		// ���ѽð�

	return true;
}

bool CNServerEvent_QuestData::SetServerEvent_QuestData( CNServerEvent_QuestData* pclSEQuestData )
{
	if ( NULL == pclSEQuestData )
	{
		return false;
	}

	if ( (SERVEREVENT_TYPE_NONE >= pclSEQuestData->GetEventType()) || ( SERVEREVENT_TYPE_END <= pclSEQuestData->GetEventType()) )
	{
		return false;
	}

	m_siEventType			= pclSEQuestData->GetEventType();			// ���� �̺�Ʈ Ÿ��

	m_siCondition1			= pclSEQuestData->GetCondition1();			// Ŭ���� �ϱ� ���� �ʿ��� ���� 1
	m_siCondition2			= pclSEQuestData->GetCondition2();			// Ŭ���� �ϱ� ���� �ʿ��� ���� 2

	m_siNeedClearAmount		= pclSEQuestData->GetNeedClearAmount();		// Ŭ���� �ϱ� ���� �ʿ��� ����

	m_siRewardItemUnique	= pclSEQuestData->GetRewardItemUnique();	// Ŭ����� ����Ǵ� ������(����ũ)
	m_siRewardItemAmount	= pclSEQuestData->GetRewardItemAmount();	// ����Ǵ� ������ ����

	m_siLimitMinute			= pclSEQuestData->GetLimitMinute();			// ���ѽð�

	return true;
}

void CNServerEvent_QuestData::SetEventType( SI32 siEventType )
{
	if ( (SERVEREVENT_TYPE_NONE >= siEventType) || ( SERVEREVENT_TYPE_END <= siEventType) )
	{
		return;
	}

	m_siEventType = siEventType;
}

SI32 CNServerEvent_QuestData::DecLimitMinute( SI32 siDecMinute )
{
	if ( 0 > siDecMinute )
	{
		return m_siLimitMinute;
	}

	m_siLimitMinute -= siDecMinute;

	if ( 0 > m_siLimitMinute )
	{
		m_siLimitMinute = 0;
	}

	return m_siLimitMinute;
}

/**************************************************************************************************************************/
/*------------------------------------------------------------------------------------------------------------------------*/
/*                                                    ��輱 �Դϴ�                                                       */
/*------------------------------------------------------------------------------------------------------------------------*/
/**************************************************************************************************************************/


CNServerEvent_QuestData_Manager::CNServerEvent_QuestData_Manager( void )
{
	Init();
}


CNServerEvent_QuestData_Manager::~CNServerEvent_QuestData_Manager()
{
	for (SI32 siCount=0; siCount<Const_ServerEvent_Max_QuestData; siCount++)
	{
		SAFE_DELETE( m_pcltSEQuestData[siCount] );
	}
}


void CNServerEvent_QuestData_Manager::Init( void )
{
#ifdef _SAFE_MEMORY
	m_pcltSEQuestData.ZeroMem();
#else
	ZeroMemory( m_pcltSEQuestData, sizeof( m_pcltSEQuestData ) );
#endif

	m_siServerEventDataCount = 0;
}


bool CNServerEvent_QuestData_Manager::AddServerEvent_QuestData( 
	SI32 siEventType, 
	
	SI32 siCondition1, 
	SI32 siCondition2, 
	
	SI32 siNeedClearAmount, 
	
	SI32 siRewardItemUnique, 
	SI32 siRewardItemAmount, 
	
	SI32 siLimitMinute 
)
{
	bool bResult = false;


	if ( Const_ServerEvent_Max_QuestData <= m_siServerEventDataCount )
	{
		return false;
	}
	

	m_pcltSEQuestData[ m_siServerEventDataCount ] = new CNServerEvent_QuestData;
	if ( NULL == m_pcltSEQuestData[ m_siServerEventDataCount ] )
	{
		return false;
	}

	bResult = m_pcltSEQuestData[ m_siServerEventDataCount ]->SetServerEvent_QuestData(
		siEventType,
		siCondition1, siCondition2,
		siNeedClearAmount,
		siRewardItemUnique, siRewardItemAmount,
		siLimitMinute
	);

	if ( bResult )
	{
		m_siServerEventDataCount++;
	}
	else
	{
		SAFE_DELETE( m_pcltSEQuestData[m_siServerEventDataCount] )
	}
	

	return bResult;
}


bool CNServerEvent_QuestData_Manager::AddServerEvent_QuestData( CNServerEvent_QuestData* pclSEQuestData )
{
	bool bResult = false;


	if ( NULL == pclSEQuestData )
	{
		return false;
	}

	if ( Const_ServerEvent_Max_QuestData <= m_siServerEventDataCount )
	{
		return false;
	}

	m_pcltSEQuestData[ m_siServerEventDataCount ] = new CNServerEvent_QuestData;
	if ( NULL == m_pcltSEQuestData[ m_siServerEventDataCount ] )
	{
		return false;
	}
	
	bResult = m_pcltSEQuestData[ m_siServerEventDataCount ]->SetServerEvent_QuestData( pclSEQuestData );

	if ( bResult )
	{
		m_siServerEventDataCount++;
	}
	else
	{
		SAFE_DELETE( m_pcltSEQuestData[m_siServerEventDataCount] )
	}


	return bResult;
}

bool CNServerEvent_QuestData_Manager::LoadQuestDataFile( SI16 siServerUnique )
{
	/*
	NTCHARString128 strPath		= TEXT( "ServerData/ServerEventQuest/" );
	NTCHARString128 strFileName = TEXT( "" );

	switch (siServerUnique) 
	{
		case 1: strFileName = TEXT( "ServerEventQuest1.txt" ); break;
		case 2: strFileName = TEXT( "ServerEventQuest2.txt" ); break;
		case 3: strFileName = TEXT( "ServerEventQuest3.txt" ); break;
		case 4: strFileName = TEXT( "ServerEventQuest4.txt" ); break;
	}

	strPath += strFileName;

#ifdef _DEBUG
	strPath = TEXT( "ServerData/ServerEventQuest/ServerEventQuest1.txt" );
#endif
*/

	NTCHARString128 strPath	= TEXT( "ServerData/ServerEventQuest/ServerEventQuest.txt" );

	NDataLoader	dataloader;

	if ( false == dataloader.LoadDataFromFile(TEXT( strPath )) )
	{
		return false;
	}


	TCHAR	szEventType[64]		= TEXT("");

	TCHAR	szCondition1[64]	= TEXT("");
	TCHAR	szCondition2[64]	= TEXT("");
	SI32	siAmount			= 0;

	SI32	siRewardItemUnique	= 0;
	SI32	siRewardItemAmount	= 0;

	SI32	siLimitMinute		= 0;


	NDataTypeInfo pDataTypeInfo[] =
	{
		NDATA_MBSTRING,	szEventType,			64,
		NDATA_MBSTRING,	szCondition1,			64,
		NDATA_MBSTRING,	szCondition2,			64,
		NDATA_INT32,	&siAmount,				4,
		NDATA_INT32,	&siRewardItemUnique,	4,
		NDATA_INT32,	&siRewardItemAmount,	4,
		NDATA_INT32,	&siLimitMinute,			4,
		0,0,0
	};

	dataloader.RegDataType( pDataTypeInfo );

	bool	bCondition			= false;
	SI32	siEventType			= 0;
	SI32	siCondition1		= 0;
	SI32	siCondition2		= 0;


	while( !dataloader.IsEndOfData() ) 
	{
		if (dataloader.ReadData())	
		{
			siEventType = EventTypeStringToInteger(szEventType);
			bCondition	= ConditionToInteger( siEventType, szCondition1, szCondition2, siCondition1, siCondition2 );

			if ( (siEventType) && (bCondition) )
			{
				AddServerEvent_QuestData( 
					siEventType,
					siCondition1, 
					siCondition2, 
					siAmount, 
					siRewardItemUnique, 
					siRewardItemAmount, 
					siLimitMinute
				);
			}
		}
	}

	return true;
}

SI32 CNServerEvent_QuestData_Manager::EventTypeStringToInteger( TCHAR* pszEventTypeString )
{
	if ( NULL == pszEventTypeString )
	{
		return SERVEREVENT_TYPE_NONE;
	}

	if     ( _tcscmp(pszEventTypeString, "SERVEREVENT_TYPE_HUNTLEVEL") == 0 )			return SERVEREVENT_TYPE_HUNTLEVEL;
	else if( _tcscmp(pszEventTypeString, "SERVEREVENT_TYPE_HUNTKIND") == 0 )			return SERVEREVENT_TYPE_HUNTKIND;
	else if( _tcscmp(pszEventTypeString, "SERVEREVENT_TYPE_HUNTBOSS") == 0 )			return SERVEREVENT_TYPE_HUNTBOSS;
	else if( _tcscmp(pszEventTypeString, "SERVEREVENT_TYPE_QUESTCLEAR") == 0 )			return SERVEREVENT_TYPE_QUESTCLEAR;
	else if( _tcscmp(pszEventTypeString, "SERVEREVENT_TYPE_USEITEM") == 0 )				return SERVEREVENT_TYPE_USEITEM;
	else if( _tcscmp(pszEventTypeString, "SERVEREVENT_TYPE_MAKELEVELITEM") == 0 )		return SERVEREVENT_TYPE_MAKELEVELITEM;
	else if( _tcscmp(pszEventTypeString, "SERVEREVENT_TYPE_MAKERAREITEM") == 0 )		return SERVEREVENT_TYPE_MAKERAREITEM;
	else if( _tcscmp(pszEventTypeString, "SERVEREVENT_TYPE_INSTANCEMAPCLEAR") == 0 )	return SERVEREVENT_TYPE_INSTANCEMAPCLEAR;
	else if( _tcscmp(pszEventTypeString, "SERVEREVENT_TYPE_FISH") == 0 )				return SERVEREVENT_TYPE_FISH;
	else if( _tcscmp(pszEventTypeString, "SERVEREVENT_TYPE_FARM") == 0 )				return SERVEREVENT_TYPE_FARM;
	else if( _tcscmp(pszEventTypeString, "SERVEREVENT_TYPE_MINE") == 0 )				return SERVEREVENT_TYPE_MINE;
	else if( _tcscmp(pszEventTypeString, "SERVEREVENT_TYPE_SKILLUP") == 0 )				return SERVEREVENT_TYPE_SKILLUP;
	else if( _tcscmp(pszEventTypeString, "SERVEREVENT_TYPE_BLACKWARCLEAR") == 0 )		return SERVEREVENT_TYPE_BLACKWARCLEAR;
	else if( _tcscmp(pszEventTypeString, "SERVEREVENT_TYPE_RESIDENTVILLAGE") == 0 )		return SERVEREVENT_TYPE_RESIDENTVILLAGE;
	else if( _tcscmp(pszEventTypeString, "SERVEREVENT_TYPE_OPEN_GVG") == 0 )			return SERVEREVENT_TYPE_OPEN_GVG;
	else if( _tcscmp(pszEventTypeString, "SERVEREVENT_TYPE_COUNTUSER_INMAP") == 0 )		return SERVEREVENT_TYPE_COUNTUSER_INMAP;
	else if( _tcscmp(pszEventTypeString, "SERVEREVENT_TYPE_LEVELUP") == 0 )				return SERVEREVENT_TYPE_LEVELUP;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ���ο� Ÿ���� �� ���� �߰��� �ּ���
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
	else 
	{
		NTCHARString256 strText( pszEventTypeString );
		NTCHARString64	strCaption( _T("Error ServerEventQuest.txt") );


		strText += _T(" Type Not Found");

		MessageBox(NULL, strText, strCaption, MB_ICONWARNING | MB_OK );
	}
#endif


	return SERVEREVENT_TYPE_NONE;
}

bool CNServerEvent_QuestData_Manager::ConditionToInteger( IN SI32 siEventType, IN TCHAR* pszCondition1, IN TCHAR* pszCondition2, OUT SI32 &rsiCondition1, OUT SI32 &rsiCondition2 )
{
	if ( (SERVEREVENT_TYPE_NONE >= siEventType) || ( SERVEREVENT_TYPE_END <= siEventType) )
	{
		return false;
	}

	if ( (NULL == pszCondition1) || (NULL == pszCondition2) )
	{
		return false;
	}


	switch ( siEventType ) 
	{
	case SERVEREVENT_TYPE_HUNTLEVEL:
	case SERVEREVENT_TYPE_USEITEM:
	case SERVEREVENT_TYPE_MAKELEVELITEM:
		{
			rsiCondition1 = _tstoi( pszCondition1 );
			rsiCondition2 = _tstoi( pszCondition2 );
		}
		break;

	//-------------------------------------------------------------
	case SERVEREVENT_TYPE_HUNTKIND:
	case SERVEREVENT_TYPE_HUNTBOSS:
		{
			SI32 siMonsterKind	= pclClient->pclKindInfoSet->FindKindFromCode( pszCondition1 );	// KIND
	
			rsiCondition1 = siMonsterKind;
			rsiCondition2 = 0;
		}
		break;

	//-------------------------------------------------------------
	case SERVEREVENT_TYPE_QUESTCLEAR:
		{
			SI32 siQuestType = _tstoi( pszCondition1 );

			
			if ( (QUEST_TYPE_SPECIAL > siQuestType) || (MAX_QUEST_TYPE <= siQuestType) )
			{
				ShowMessageBox( TEXT("SERVEREVENT_TYPE_QUESTCLEAR"), siQuestType );
				return false;
			}

			rsiCondition1 = siQuestType;	// 
			rsiCondition2 = 0;				// �Ⱦ�
		}
		break;

	//-------------------------------------------------------------
	case SERVEREVENT_TYPE_INSTANCEMAPCLEAR:
		{
			SI32 siInstanceMapIndex = _tstoi( pszCondition1 );

			
			if ( (INSTANCEMAP_TYPE_NONE > siInstanceMapIndex) || (INSTANCEMAP_TYPE_MAX <= siInstanceMapIndex) )
			{
				ShowMessageBox( TEXT("SERVEREVENT_TYPE_INSTANCEMAPCLEAR"), siInstanceMapIndex );
				return false;
			}

			rsiCondition1 = siInstanceMapIndex;
			rsiCondition2 = 0;					// �Ⱦ�
		}
		break;

	//-------------------------------------------------------------
	case SERVEREVENT_TYPE_RESIDENTVILLAGE:
		{
			SI32 siVillageUnique = _tstoi( pszCondition1 );


			if ( (VILLAGE_NONE > siVillageUnique) || (MAX_VILLAGE_NUMBER <= siVillageUnique) )
			{
				ShowMessageBox( TEXT("SERVEREVENT_TYPE_RESIDENTVILLAGE"), siVillageUnique );
				return false;
			}

			rsiCondition1 = siVillageUnique;	// 
			rsiCondition2 = 0;					// �Ⱦ�
		}
		break;

	case SERVEREVENT_TYPE_COUNTUSER_INMAP:
		{
			SI32 siMapIndex = _tstoi( pszCondition1 );


			if ( (VILLAGE_NONE > siMapIndex) || (MAX_MAP_NUMBER <= siMapIndex) )
			{
				ShowMessageBox( TEXT("SERVEREVENT_TYPE_COUNTUSER_INMAP"), siMapIndex );
				return false;
			}

			rsiCondition1 = siMapIndex;	// 
			rsiCondition2 = 0;			// �Ⱦ�
		}
		break;
	case SERVEREVENT_TYPE_LEVELUP:
		{
			SI32 siLevel = _tstoi( pszCondition1 );
			
			
			if ( (0 > siLevel) || (MAX_CHARACTER_LEVEL < siLevel) )
			{
				ShowMessageBox( TEXT("SERVEREVENT_TYPE_LEVELUP"), siLevel );
				return false;
			}

			rsiCondition1 = siLevel;
			rsiCondition2 = 0;			// �Ⱦ�
		}
		break;
	//-------------------------------------------------------------
	case SERVEREVENT_TYPE_MAKERAREITEM:
	case SERVEREVENT_TYPE_FISH:
	case SERVEREVENT_TYPE_FARM:
	case SERVEREVENT_TYPE_MINE:
	case SERVEREVENT_TYPE_SKILLUP:
	case SERVEREVENT_TYPE_BLACKWARCLEAR:
	case SERVEREVENT_TYPE_OPEN_GVG:
		{
			rsiCondition1 = 0;	// �Ⱦ�
			rsiCondition2 = 0;	// �Ⱦ�
		}
		break;
	//-------------------------------------------------------------
	default:
		{
			return false;
		}
		
	}
	

	return true;

}

bool CNServerEvent_QuestData_Manager::GetRandQuestData( OUT CNServerEvent_QuestData* pclSEQuestData, IN SI32 siSelectIndex/* =-1  */)
{
	if ( NULL == pclSEQuestData )
	{
		return false;
	}

	if ( 0 >= m_siServerEventDataCount  )
	{
		return false;
	}

	SI32 siGetIndex = 0;
	// �ʱ�ȭ
	if ( 0 > siSelectIndex )
	{
		siGetIndex = rand() % m_siServerEventDataCount;
	}
	else
	{
		siGetIndex = siSelectIndex;
	}
	
	CNServerEvent_QuestData clQuestData( m_pcltSEQuestData[ siGetIndex ] );

	SI32 siEventType	= clQuestData.GetEventType();
	SI32 siCondition1	= clQuestData.GetCondition1();
	SI32 siCondition2	= clQuestData.GetCondition2();
	
	

	// Ư�� �̺�Ʈ Ÿ�Կ� ���� ����Ʈ ������ �޶���
	switch ( siEventType )
	{
		case SERVEREVENT_TYPE_HUNTKIND:
			{
				// �⺻ ������
				SI32 siKind	= siCondition1;

				
				// ���� ī�ε尡 ������ ���� �ʴٸ� �����ϰ� �̾Ƴ���
				if ( 0 == siKind )
				{
					siKind = GetRandMonsterKindForHuntKind();
				}

				// KIND�� �� �̾� �Դٸ� ����
				if ( 0 >= siKind )
				{
					return false;
				}

				siCondition1 = siKind;
				siCondition2 = 0;
			}
			break;

		case SERVEREVENT_TYPE_HUNTBOSS:
			{
				// �⺻ ������
				SI32 siKind	= siCondition1;

				// ���� ī�ε尡 ������ ���� �ʴٸ� �����ϰ� �̾Ƴ���
				if ( 0 == siKind )
				{
					TCHAR szBossKind[][60] = {
						{TEXT("KIND_GOLDBEETLE")},
						{TEXT("KIND_SIMTORYONG")},
						{TEXT("KIND_BOSSMONKEY")},
						{TEXT("KIND_TOAD")},
						{TEXT("KIND_CRANE")},
						{TEXT("KIND_KINGCRYSTAL")},
						{TEXT("KIND_FROZENGOLEM")},
						{TEXT("KIND_FROZENQUEEN")},
						{TEXT("KIND_MANDRAGORA")},
						{TEXT("KIND_DRAGONKING")},
						{TEXT("KIND_OTOHIME")},
						{TEXT("KIND_DRACULA")},
						{TEXT("KIND_CERBERUS")},
						{TEXT("KIND_HELLDOG")},
						{TEXT("KIND_GREENTURTLE")},
						{TEXT("KIND_KINGYACHA")},
						{TEXT("KIND_HELLDOG_2")},
						{TEXT("KIND_KINGYACHA_2")},
						{TEXT("KIND_GREENTURTLE_2")}
					};

					SI32 siRandValue = rand() % 19;

					siKind = pclClient->GetUniqueFromHash( szBossKind[siRandValue] );	
				}

				// KIND�� �� �̾� �Դٸ� ����
				if ( 0 >= siKind )
				{
					return false;
				}

				siCondition1 = siKind;
				siCondition2 = 0;

			}
			break;

		case SERVEREVENT_TYPE_USEITEM:
			{
				// �⺻ ������
				SI32 siItemType		= siCondition1;
				SI32 siItemUnique	= siCondition2;
				
				
				// ������ Ÿ���� �����Ѵٸ� �� Ÿ���� ������ ����ũ�߿� �����ϰ� �̴´�
				if ( 0 < siItemType )
				{
					siItemUnique = GetRandItemUinqueForUseItem( siItemType );
				}
				
				// Ȥ�� ����ũ�� ���̾� �ü��� �ֱ⶧���� ������ �˻��غ���
				if ( 0 >= siItemUnique )
				{
					return false;
				}

				siCondition1 = siItemType;
				siCondition2 = siItemUnique;
			}
			break;

		case SERVEREVENT_TYPE_COUNTUSER_INMAP:
			{
				SI32 siMapIndex = siCondition1;

				// �� �ε����� �������� ������ �����ϰ� �̾Ƴ���
				if ( 0 >= siMapIndex )
				{
					siMapIndex = GetRandMapIndexForUserCount();
				}

				// Ȥ�� �� �ε����� ���̾� �´ٸ�
				if ( 0 >= siMapIndex )
				{
					return false;
				}

				siCondition1 = siMapIndex;
				siCondition2 = 0;
			}
			break;
	}

	clQuestData.SetCondition1( siCondition1 );
	clQuestData.SetCondition2( siCondition2 );

	pclSEQuestData->SetServerEvent_QuestData( &clQuestData );

	return true;
}

void CNServerEvent_QuestData_Manager::ShowMessageBox(TCHAR* pszEventType, SI32 siCondition1, SI32 siCondition2)
{
#ifdef _DEBUG
	if ( NULL == pszEventType )
	{
		return;
	}


	NTCHARString256 strErrorMes( TEXT("#eventtype# �̺�Ʈ Ÿ���� #cond1#, #cond2# ������ �߸��Ǿ����ϴ�") );

	strErrorMes.Replace( TEXT("#eventtype#"),	pszEventType );
	strErrorMes.Replace( TEXT("#cond1#"),		SI32ToString( siCondition1 ) );
	strErrorMes.Replace( TEXT("#cond2#"),		SI32ToString( siCondition2 ) );

	MessageBox( NULL, strErrorMes, "ERROR", MB_ICONWARNING | MB_OK );

#endif

}

SI32 CNServerEvent_QuestData_Manager::LoadHuntParentMapIndex( SI32* psiMapIndex )
{
	if ( NULL == psiMapIndex )
	{
		return 0;
	}

	NDataLoader	dataloader;
	BOOL bLoadFile=FALSE;

	//KHY - 0810 - �ؽ�Ʈ ���ҽ� ��ȣȭ.
	if( pclClient->IsWhereServiceArea( ConstSwitch_TextEncryption ) )
	{
		bLoadFile = dataloader.LoadDataFromCryptFile( TEXT("Data/HuntmapInfo.txt") );
	}
	else
	{
		bLoadFile = dataloader.LoadDataFromFile( TEXT("Data/HuntmapInfo.txt") );
	}

	if (!bLoadFile)
	{
		MsgBox( TEXT("Not LoadFromFile HuntmapInfo"),TEXT("Error"));
		return 0;
	}

	SI32	siTextMgrNum		= 0;
	TCHAR	szMapUnique[256]	= TEXT("");
	SI32	siMapIndex			= 0;
	
	SI32	siCount				= 0;
	

	NDataTypeInfo pDataTypeInfo[] =
	{
		NDATA_INT32,	&siTextMgrNum,	4,		
		NDATA_MBSTRING,	szMapUnique,	256,
		NDATA_INT32,	&siMapIndex,	4,
		0,0,0
	};

	dataloader.RegDataType( pDataTypeInfo );


	while ( !dataloader.IsEndOfData() ) {

		if ( dataloader.ReadData() ) 
		{
			if ( szMapUnique[ 0 ] != NULL)
			{
				// ���縮��, �ʺ��ڻ���ʹ� ���� �ȵǰ�
				if ( (MAPINDEX_PALACE == siMapIndex) || (MAPINDEX_BEGINNER1 == siMapIndex) )
				{
					continue;
				}

				psiMapIndex[ siCount ] = siMapIndex;

				siCount++;

				if ( SMV_FORHUNTKIND_MAXMAPNUM <= siCount )
				{
					break;
				}
			}
		}
	}


	return siCount;

}

SI32 CNServerEvent_QuestData_Manager::FindHuntChildMapIndex( IN SI32 siParentMapIndex ,OUT SI32 psiMapIndex[] )
{
	SI32 siCount			= 0;
	SI32 siChildMapIndex	= 0;
	
	

	if ( (0 > siParentMapIndex) || (MAX_MAP_NUMBER <= siParentMapIndex) )
	{
		return 0;
	}
	
	if ( NULL == psiMapIndex )
	{
		return 0;
	}

	for ( SI32 siMapIndex=0; siMapIndex<MAX_MAP_NUMBER; siMapIndex++ )
	{
		if ( siParentMapIndex == pclClient->pclMapManager->GetParentMap( siMapIndex ) )
		{
			psiMapIndex[ siCount ] = siMapIndex;
			
			siCount++;

			if ( SMV_FORHUNTKIND_MAXMAPNUM <= siCount )
			{
				break;
			}
		}
	}


	return siCount;
}

SI32 CNServerEvent_QuestData_Manager::RandHuntMonsterKind( SI32 siMapIndex, SI32 siATB/* =0  */)
{
	SI32 siKind[SMV_FORHUNTKIND_MAXNPCNUM]		= {0, };
	SI32 siKindLevel[SMV_FORHUNTKIND_MAXNPCNUM] = {0, };	// �������� ���� �׳� �Լ��� �ֱ����� ���̿�
	SI32 siMaxKindNum							= SMV_FORHUNTKIND_MAXNPCNUM;
	SI32 siRandValue							= 0;
	SI32 siReturnKind							= 0;
	

	if ( (0 > siMapIndex) || (MAX_MAP_NUMBER <= siMapIndex) )
	{
		return 0;
	}

	// �ش� �� �ε����� �����ϴ� ���͸� KIND�� ���´�
	
	((cltNPCManagerServer*)pclClient->pclNPCManager)->GetKindMapInx( siMapIndex, siKind, siKindLevel, SMV_FORHUNTKIND_MAXNPCNUM );
	// �ش� �� �ε����� �����ϴ� ���� ���� ��
	for ( SI32 siIndex=0; siIndex<SMV_FORHUNTKIND_MAXNPCNUM; siIndex++ )
	{
		if ( 0 == siKind[ siIndex ]  )
		{
			siMaxKindNum = siIndex;
		}
	}

	// �����ϰ� ���� �����ϰ�
	siRandValue = rand() % siMaxKindNum;

	// ã���� �ϴ� ���Ͱ� �ȳ��ü��� �ֱ� ������ ����� ������ �����ش�
	for ( SI32 siSearchCount=0; siSearchCount<SMV_FORHUNTKIND_MAXNPCNUM; siSearchCount++ )
	{
		siRandValue = (siRandValue+1) % siMaxKindNum;

		if ( 0 == siKind[ siRandValue ] )
		{
			continue;
		}

		// siATB ������ ���� ��
		if ( 0 >= siATB	)		
		{
			// ������ �ƴϾ�� �Ѵ�
			if ( false == pclClient->pclKindInfoSet->pclKI[ siKind[siRandValue] ]->IsAtb( ATB_BOSS ) )
			{
				// �����ϰ� ���� �����Ѱ��� �ε����� �ؼ� KIND�� �̾ƿ´�
				siReturnKind = siKind[ siRandValue ];
				break;
			}
		}
		// siATB ������ ���� ��
		else
		{
			// �̾� ������ ������ KIND�� ���Ͱ� ���� siATB�� �������� �Ѱ��ش�.
			if ( true == pclClient->pclKindInfoSet->pclKI[ siKind[siRandValue] ]->IsAtb( siATB ) )
			{
				// �����ϰ� ���� �����Ѱ��� �ε����� �ؼ� KIND�� �̾ƿ´�
				siReturnKind = siKind[ siRandValue ];
				break;
			}
		}
	}


	return siReturnKind;
}

SI32 CNServerEvent_QuestData_Manager::GetRandMonsterKindForHuntKind( SI32 siATB/* =0  */)
{
	SI32 siRandValueIndex	= 0;
	SI32 siRandValueKind	= 0;
	SI32 siKind				= 0;
	SI32 siReadCount		= 0;
	SI32 siParentMapCount	= 0;
	SI32 siParentMapIndex[ SMV_FORHUNTKIND_MAXMAPNUM ]	= {0, };
	SI32 siChildMapIndex[ SMV_FORHUNTKIND_MAXMAPNUM ]	= {0, };
	
	// HuntMapInfo.txt���� ������ �� �ε����� �����´�	
	siParentMapCount = LoadHuntParentMapIndex( siParentMapIndex );
	if ( 0 >= siParentMapCount )
	{
		return 0;
	}

	siRandValueIndex = rand() % siParentMapCount;

	// �������� Ư���� ATB�� ������ ���͸� �� �̾� �ü��� �ִ� �׷��� ������ ������ ������ �����ش�
	for ( SI32 siCount=0; siCount<SMV_FORHUNTKIND_MAXMAPNUM; siCount++ )
	{
		SI32 siTempKind = 0;
		siRandValueIndex = (siRandValueIndex+1) % siParentMapCount;

		// ���� ���Ͱ� �����ϴ� �� �ε����� �����´�
		siReadCount = FindHuntChildMapIndex( siParentMapIndex[ siRandValueIndex ], siChildMapIndex );
		if ( 0 >= siReadCount )
		{
			return 0;
		}

		// �ش� �� �ε����� ���� �ִ� ���͸� �����ϰ� �ϳ� �̾ƿ´�.
		siRandValueKind = rand() % siReadCount;
		siTempKind = RandHuntMonsterKind( siChildMapIndex[ siRandValueKind ] );

		if ( 0 < siTempKind )
		{
			siKind = siTempKind;
			break;
		}
	}


	return siKind;
}




SI32 CNServerEvent_QuestData_Manager::GetRandItemUinqueForUseItem( SI32 siItemType )
{
	SI32 siItemUnique = 0;

	if ( 0 >= siItemType )
	{
		return 0;
	}

	switch ( siItemType )
	{
		case ITEMTYPE_FOOD:
			{
				SI32 siRandUnique[]	= {
					3735, 3740, 3745, 3750, 3755, 
					3760, 3765, 3770, 3775, 3780, 
					3785, 3790, 3795, 3800, 3805, 
					3810, 3815, 3820, 3825, 3830, 
					3835, 3840
				};
				SI32 siCount		= (SI32)( sizeof(siRandUnique) / sizeof(SI32) );
				SI32 siRandIndex	= rand() % siCount;

				siItemUnique = siRandUnique[ siRandIndex ];
			}
			break;

		case ITEMTYPE_HEAL:
			{
				SI32 siRandUnique[]	= { 2565, 2570, 2575, 2580, 2585, 2590, 2595, 2600, 2605 };
				SI32 siCount		= (SI32)( sizeof(siRandUnique) / sizeof(SI32) );
				SI32 siRandIndex	= rand() % siCount;

				siItemUnique = siRandUnique[ siRandIndex ];
			}
			break;
		default :
			{
				return 0;
			}
	}

	return siItemUnique;
}

SI32 CNServerEvent_QuestData_Manager::GetRandMapIndexForUserCount( void )
{
	SI32 siRandValueIndex	= 0;
	SI32 siMapIndex			= 0;
	SI32 siReadCount		= 0;
	SI32 siParentMapCount	= 0;
	SI32 siParentMapIndex[ SMV_FORHUNTKIND_MAXMAPNUM ]	= {0, };
	SI32 siChildMapIndex[ SMV_FORHUNTKIND_MAXMAPNUM ]	= {0, };

	// HuntMapInfo.txt���� ������ �� �ε����� �����´�	
	siParentMapCount = LoadHuntParentMapIndex( siParentMapIndex );
	if ( 0 >= siParentMapCount )
	{
		return 0;
	}

	siRandValueIndex = rand() % siParentMapCount;

	// ���� ���Ͱ� �����ϴ� �� �ε����� �����´�
	siReadCount = FindHuntChildMapIndex( siParentMapIndex[ siRandValueIndex ], siChildMapIndex );
	if ( 0 >= siReadCount )
	{
		return 0;
	}

	siRandValueIndex = rand() % siReadCount;

	siMapIndex = siChildMapIndex[ siRandValueIndex ];

	return siMapIndex;
}


SI32 CNServerEvent_QuestData_Manager::GetIndexFromType( SI32 siEventType, SI32 siStartPos/* =0  */)
{
	SI32 siReturnIndex = -1;


	if ( (SERVEREVENT_TYPE_NONE >= siEventType) || ( SERVEREVENT_TYPE_END <= siEventType) )
	{
		return -1;
	}

	if ( (0 > siStartPos) || (m_siServerEventDataCount < siStartPos) )
	{
		return -1;
	}

	for ( SI32 siIndex=siStartPos; siIndex<m_siServerEventDataCount; siIndex++ )
	{
		if ( m_pcltSEQuestData[ siIndex ] == NULL )
		{
			break;
		}

		if ( siEventType == m_pcltSEQuestData[ siIndex ]->GetEventType() )
		{
			siReturnIndex = siIndex;
		}
	}


	return siReturnIndex;
}
/**************************************************************************************************************************/
/*------------------------------------------------------------------------------------------------------------------------*/
/*                                                    ��輱 �Դϴ�                                                       */
/*------------------------------------------------------------------------------------------------------------------------*/
/**************************************************************************************************************************/

CNServerEvent_Quest::CNServerEvent_Quest( void ) : m_clSEQuestData(), m_clSEQD_Manager(), m_siNowAmount(0), m_siCharacterIndex(0), m_dwServerEventQuestColck(0)
{
	// m_siCharacterLimit ���ڸ� �����Ҷ� Const_ServerEvent_Max_QuestCharacter���� ũ�� �ȵ˴ϴ�
	m_siCharacterLimit			= min( 8, Const_ServerEvent_Max_QuestCharacter );
#ifdef _SAFE_MEMORY
	m_bCharacter.ZeroMem();
#else
	ZeroMemory( m_bCharacter, sizeof( m_bCharacter ) );
#endif

	m_siFailAddCharacterLimit	= m_siCharacterLimit * Const_ServerEvent_MulNum;
	memset( m_siInFailCharacter, -1, sizeof(m_siInFailCharacter) );
	
}

CNServerEvent_Quest::~CNServerEvent_Quest()
{
}

void CNServerEvent_Quest::Init( void )
{
	m_clSEQuestData.Init();
	m_siNowAmount				= 0;
	m_dwServerEventQuestColck	= 0;
}

void CNServerEvent_Quest::InitCharacter( void )
{
#ifdef _SAFE_MEMORY
	m_bCharacter.ZeroMem();
#else
	ZeroMemory( m_bCharacter, sizeof( m_bCharacter ) );
#endif

	memset( m_siInFailCharacter, -1, sizeof(m_siInFailCharacter) );

	m_siCharacterIndex = 0;
}

bool CNServerEvent_Quest::LoadQuestData( SI16 siServerUnique )
{
	bool bResult = m_clSEQD_Manager.LoadQuestDataFile( siServerUnique );

	return bResult;
}

void CNServerEvent_Quest::MakeNewServerEventQuest(SI32 siEventType/* =0 */)
{
	if ( SERVEREVENT_TYPE_END <= siEventType )
	{
		return;
	}

	cltServer* pclserver = (cltServer*)pclClient;
	if ( NULL == pclserver )
	{
		return;
	}
	
	// ���� �̺�Ʈ �ð��� �ƴҶ��� �������� �ʴ´�
	if ( false == pclserver->pclEventTimeManager->InEventTime(TEXT( "GoonzuDay_Week" ), &pclserver->sTime) )
	{
		pclserver->pclServerEventManager->SetServerEventState( SERVER_EVENT_STATE_WAIT );
		return;
	}

	CNServerEvent_QuestData clQuestData;
	bool					bGetQuest		= false;
	SI32					siSelectIndex	=-1;

	if ( SERVEREVENT_TYPE_NONE < siEventType )
	{
		siSelectIndex = m_clSEQD_Manager.GetIndexFromType( siEventType );
	}

	Init();
	// Ȥ�� �𸣴� ��� �ݺ��ϸ鼭 ��������Ʈ�� ����
	for ( SI32 siCount=0; siCount<10; siCount++ )
	{
		clQuestData.Init();

		// Ư�� Ÿ���� ����Ʈ�� �޾ƾ� �Ѵٸ�
		if ( SERVEREVENT_TYPE_NONE < siEventType )
		{
			if ( true == m_clSEQD_Manager.GetRandQuestData( &clQuestData, siSelectIndex ) )
			{
				if ( siEventType == clQuestData.GetEventType() )
				{
					m_dwServerEventQuestColck = pclClient->CurrentClock;

					m_clSEQuestData.SetServerEvent_QuestData( &clQuestData );
					bGetQuest = true;
					break;
				}
			}

		}
		// Ư�� Ÿ���� ����Ʈ�� �޴°��� �ƴ϶��
		else
		{
			if ( true == m_clSEQD_Manager.GetRandQuestData( &clQuestData ) )
			{
				// �決����Ʈ�� �޾Ƽ��� �ȵȴ�
				if ( SERVEREVENT_TYPE_BLACKWARCLEAR != clQuestData.GetEventType() )
				{
					m_dwServerEventQuestColck = pclClient->CurrentClock;

					m_clSEQuestData.SetServerEvent_QuestData( &clQuestData );
					bGetQuest = true;
					break;
				}
			}
		}
	}

	if ( false == bGetQuest )
	{
		pclserver->pclServerEventManager->SetServerEventState( SERVER_EVENT_STATE_START_QUEST );
		return;
	}


	pclserver->pclServerEventManager->SetServerEventState( SERVER_EVENT_STATE_GOING_QUEST );

	// ���⿡ ���ο� ����Ʈ�� �����Ǿ��ٰ� ������
	SendMessageToClient( SERVEREVENT_QUEST_PACKETTYPE_QUESTSTART );
	// ���� ������ ����Ʈ ������ DB�� ����
	SendMessageToDB( SERVEREVENT_QUEST_PACKETTYPE_SET_QUESTINFO );
	// ����Ʈ ����
	pclClient->pclLog->FilePrint( TEXT("config\\ServerEvent.log"), TEXT("[QuestStart]\tQuestType=%d\tCondition1=%d\tCondition2=%d"), clQuestData.GetEventType(), clQuestData.GetCondition1(), clQuestData.GetCondition2() );

}

void CNServerEvent_Quest::MakeCharacter( void )
{
	SI32 siIndex		= 0;
	SI32 siRandIndex	= 0;
	SI16 siForSwap		= 0;


	InitCharacter();

	for ( siIndex=0; siIndex<m_siCharacterLimit; siIndex++ )
	{
		m_siInFailCharacter[ siIndex ] = siIndex;
	}


	/*
		���� ���� ������ �ִ� 100%���� �����Ҽ��ִ�
		�� ���� ���ڰ� 8�����̸� �ִ� 8���� ������ �� �ִ�

		�� ���� 8���ڱ����϶� ���� ����Ʈ�� �ִ� 16ȸ �̷������
	*/
	
	for ( siIndex=0; siIndex<m_siFailAddCharacterLimit; siIndex++ )
	{
		siRandIndex = rand() % m_siFailAddCharacterLimit;

		if ( siRandIndex != siIndex )
		{
			siForSwap							= m_siInFailCharacter[ siIndex ];
			m_siInFailCharacter[ siIndex ]		= m_siInFailCharacter[ siRandIndex ];
			m_siInFailCharacter[ siRandIndex ]	= siForSwap;
		}
	}
}

void CNServerEvent_Quest::IncServerEventQuestCondition( SI32 siEventType, SI32 siCondition, SI32 siAmount )
{
	if ( (SERVEREVENT_TYPE_NONE >= siEventType) || ( SERVEREVENT_TYPE_END <= siEventType) )
	{
		return;
	}

	// ���� �μ��� ���� Ÿ���� ����Ʈ�� ���������� ����
	bool		bQuestGoing		= false;

	const SI32	siNowType		= m_clSEQuestData.GetEventType();
	const SI32	siNowCond1		= m_clSEQuestData.GetCondition1();
	const SI32	siNowCond2		= m_clSEQuestData.GetCondition2();


	if ( siNowType != siEventType )
	{
		return;
	}

	// �̺�Ʈ Ÿ�Ժ��� Amount���� �˻�
	switch ( siEventType ) 
	{
		case SERVEREVENT_TYPE_HUNTLEVEL:
		case SERVEREVENT_TYPE_MAKELEVELITEM:
			{
				// Ȥ�� �𸣴� �ѹ��� �˻��ϴ� ����~
				if ( siNowType == siEventType )
				{
					if ( (siNowCond1 <= siCondition) && (siNowCond2 >= siCondition) )
					{
						bQuestGoing = true;
					}
				}
			}
			break;

		case SERVEREVENT_TYPE_HUNTKIND:
		case SERVEREVENT_TYPE_HUNTBOSS:
		case SERVEREVENT_TYPE_QUESTCLEAR:
		case SERVEREVENT_TYPE_INSTANCEMAPCLEAR:
		case SERVEREVENT_TYPE_COUNTUSER_INMAP:
			{
				if ( siNowType == siEventType )
				{
					if ( siNowCond1 == siCondition )
					{
						bQuestGoing = true;
					}
				}
			}
			break;

		case SERVEREVENT_TYPE_USEITEM:
			{
				if ( siNowType == siEventType )
				{
					if ( siNowCond2 == siCondition )
					{
						bQuestGoing = true;
					}
				}
			}
			break;

		case SERVEREVENT_TYPE_LEVELUP:
			{
				if ( siNowType == siEventType )
				{
					if ( siNowCond1 <= siCondition )
					{
						bQuestGoing = true;
					}
				}

			}
			break;

		case SERVEREVENT_TYPE_MAKERAREITEM:
		case SERVEREVENT_TYPE_FISH:
		case SERVEREVENT_TYPE_FARM:
		case SERVEREVENT_TYPE_MINE:
		case SERVEREVENT_TYPE_SKILLUP:
		case SERVEREVENT_TYPE_BLACKWARCLEAR:
		case SERVEREVENT_TYPE_RESIDENTVILLAGE:
		case SERVEREVENT_TYPE_OPEN_GVG:
			{
				if ( siNowType == siEventType )
				{
					bQuestGoing = true;
				}
			}
			break;
	}

	// Amount ���� ���ǿ� �����ϸ� Amount ����
	if ( true == bQuestGoing )
	{
		IncAmount( siAmount );
	}
	
	// ���� ����Ʈ Ŭ���� ���� �˻�
	ServerEventQuestClearProcess();

}

bool CNServerEvent_Quest::IsClearServerEventQuest( void )
{
	// Ȥ�� ���� ����Ʈ�� ���� �ʾҴµ� �� �Լ��� ���� ���״ٸ�
	if ( (0 == m_clSEQuestData.GetEventType())
		|| (0 == m_clSEQuestData.GetNeedClearAmount())
		)
	{
		return false;
	}

	if ( m_clSEQuestData.GetNeedClearAmount() <= m_siNowAmount )
	{
		return true;
	}


	return false;
}

bool CNServerEvent_Quest::AllClearServerEventQuest()
{
	for ( SI32 siIndex=0; siIndex<m_siCharacterLimit; siIndex++ )
	{
		if ( false == m_bCharacter[ siIndex ] )
		{
			return false;
		}
	}

	
	return true;
	
}

void CNServerEvent_Quest::IncAmount( SI32 siAmount )
{
	if ( 0 > siAmount )
	{
		return;
	}

	m_siNowAmount += siAmount;

	// Ȥ�� ���� ���״µ� �����÷ξ� ��ٸ�?
	if ( 0 > m_siNowAmount )
	{
		m_siNowAmount = MAX_SI32;
	}

}

void CNServerEvent_Quest::RewardCharacter( void )
{
	// Ȥ�� �𸣴� �˻�
	if ( (m_siCharacterIndex) > m_siFailAddCharacterLimit )
	{
		return;
	}

	SI32 siCharacterIndex = m_siInFailCharacter[m_siCharacterIndex];
	// ���� �ε����� ���ڰ� ���� ��
	if ( 0 <= siCharacterIndex )
	{
		m_bCharacter[ siCharacterIndex ] = true;
		SendMessageToClient( SERVEREVENT_QUEST_PACKETTYPE_GETCHAR, siCharacterIndex );
		pclClient->pclLog->FilePrint( TEXT("config\\ServerEvent.log"), TEXT("[GetChar]\tCharIndex=%d\tVariableIndex=%d"), siCharacterIndex, m_siCharacterIndex );
	}
	// ���� �ε����� ���ڰ� ���� ��(���ڸ� ���� ����)
	else
	{
		SendMessageToClient( SERVEREVENT_QUEST_PACKETTYPE_CHAR_FAIL );
		pclClient->pclLog->FilePrint( TEXT("config\\ServerEvent.log"), TEXT("[FailGetChar]\tCharIndex=%d\tVariableIndex=%d"), siCharacterIndex, m_siCharacterIndex );
		//cltGameMsgResponse_Server_Event_Quest clInfo( SERVEREVENT_MESSAGETYPE_CHAR_FAIL );
	}

	// �ε����� �ϳ� ���� ��Ų��
	m_siCharacterIndex++;
}

void CNServerEvent_Quest::RewardItem( SI32 siItemUnique, SI32 siItemAmount )
{
	SI32 siRef		= 0;
	UI16 uiUseDate	= 0;


	if ( (0 >= siItemUnique) || (0 >= siItemAmount) )
	{
		return;
	}

	siRef = pclClient->pclItemManager->FindItemRefFromUnique( siItemUnique );
	if ( siRef <= 0 )
	{
		return;
	}

	uiUseDate = pclClient->pclItemManager->pclItemInfo[ siRef ]->clItem.uiDateUseDay;

	pclClient->pclCM->GiveItem( 0, siItemUnique, siItemAmount, GIVEITEM_MODE_MINLEVEL, 
		INPUTITEMPERSON_OPTION_SERVER_EVENT, uiUseDate, 0, Const_ServerEvent_RewardItemGetMinLevel 
	);
	
	pclClient->pclLog->FilePrint( TEXT("config\\ServerEvent.log"), TEXT("[QuestReward]\tItemUnique=%d\tAmount=%d"), siItemUnique, siItemAmount );
}

void CNServerEvent_Quest::Action()
{
	// Ȥ�� ���� �̺�Ʈ�� ���µ� ó���ȴٸ�?
	if ( 0 >= m_clSEQuestData.GetEventType() )
	{
		return;
	}

	// 60��(1��)�� �ȳ����� ����
	if ( TABS(pclClient->CurrentClock - m_dwServerEventQuestColck) < 60000 )
	{
		return;
	}

	bool bIsGoingBlackWar	= pclClient->pclBlackWarManager->IsBlackWar();
	SI32 siDecMinute		= (SI32)(TABS(pclClient->CurrentClock - m_dwServerEventQuestColck) / 60000);
	SI32 siLimitMinute		= MAX_SI32;

	// ����ð��� ������Ʈ �Ѵ�
	m_dwServerEventQuestColck = pclClient->CurrentClock;
	
	// ���� ���� �ð��� �ٿ��ְ� �� ���� �ð��� ���´�
	siLimitMinute = m_clSEQuestData.DecLimitMinute( siDecMinute );

	// ���� ���� �������̶��
	//------------------------------------------------------------------------------------------------------------------------------------------
	if ( (true == bIsGoingBlackWar) && (SERVEREVENT_TYPE_BLACKWARCLEAR != m_clSEQuestData.GetEventType()) )
	{
		// ���Ǳ��� ����Ʈ�� �����Ѵ�.
		if ( false == ServerEventQuestClearProcess( SERVEREVENT_TYPE_BLACKWARCLEAR ) )
		{
			MakeNewServerEventQuest( SERVEREVENT_TYPE_BLACKWARCLEAR );
		}
	}
	// ���� �ð��� ���ٸ�
	//------------------------------------------------------------------------------------------------------------------------------------------
	else if ( 0 >= siLimitMinute )
	{
		// ���� �̺�Ʈ�� Ŭ���� �ߴ��� ���� �˻�
		bool bIsQuestClear = ServerEventQuestClearProcess();

		// Ŭ���� ���� ���ߴٸ� ���⿡�� ���ο� �����̺�Ʈ ����
		if ( false == bIsQuestClear )
		{
			pclClient->pclLog->FilePrint( TEXT("config\\ServerEvent.log"), TEXT("[QuestFail]\tQuestType=%d\tCondition1=%d\tCondition2=%d"), m_clSEQuestData.GetEventType(), m_clSEQuestData.GetCondition1(), m_clSEQuestData.GetCondition2() );

			// �� ����Ʈ�� �����ߴٴ� �޽���
			SendMessageToClient( SERVEREVENT_QUEST_PACKETTYPE_QUEST_FAIL );

			// ���⿡ �ð��� ������ ���ο� ����Ʈ�� ���� �ߴٰ� ������
			MakeNewServerEventQuest();
		}
	}
	//------------------------------------------------------------------------------------------------------------------------------------------
	else
	{
		// ��� ������ ����Ʈ�� �ٸ������� ó���ϱ� ����� �̰����� �ϰ������� �Ѵ�
		if ( SERVEREVENT_TYPE_COUNTUSER_INMAP == m_clSEQuestData.GetEventType() )
		{
			SI32 siMapIndex		= m_clSEQuestData.GetCondition1();
			SI32 siUserCount	= 0;

			siUserCount = pclClient->pclMapManager->GetUserCountByMapIndex( siMapIndex );

			SetNowAmount( 0 );// �㿡 ��� ������� Ư���� ���� �������� ī��Ʈ�ϱ� ������ �����Ǹ� �ȵȴ�

			IncServerEventQuestCondition( SERVEREVENT_TYPE_COUNTUSER_INMAP, siMapIndex, siUserCount );
		}

		// ���⿡ ���� ����Ʈ ��Ȳ�� Ŭ���̾�Ʈ�� ������
		SendMessageToClient( SERVEREVENT_QUEST_PACKETTYPE_RUNINFO );
		SendMessageToDB( SERVEREVENT_QUEST_PACKETTYPE_SET_QUESTINFO );
	}

}

bool CNServerEvent_Quest::ServerEventQuestClearProcess(SI32 siEventType/* =0 */)
{
	const SI32	siRewardItem	= m_clSEQuestData.GetRewardItemUnique();
	const SI32	siRewardNum		= m_clSEQuestData.GetRewardItemAmount();
	bool		bIsQuestClear	= IsClearServerEventQuest();


	if ( SERVEREVENT_TYPE_NONE >= m_clSEQuestData.GetEventType() )
	{
		return false;
	}

	// ���� ����Ʈ Ŭ���� ���� �˻�
	if ( true == bIsQuestClear )
	{
		// Ŭ��� ���� ���ڸ� �޴´�
		RewardCharacter();

		// Ŭ��� ���� ������ �޴´�
		RewardItem( siRewardItem, siRewardNum );

		pclClient->pclLog->FilePrint( TEXT("config\\ServerEvent.log"), TEXT("[QuestClear]\tQuestType=%d\tCondition1=%d\tCondition2=%d\tCondition1=%d\tCondition2=%d"), m_clSEQuestData.GetEventType(), m_clSEQuestData.GetCondition1(), m_clSEQuestData.GetCondition2() );

		// ���� ����Ʈ�� Ŭ���� �ߴٸ� ��� ���� ����Ʈ(���ڸ� ��� ä������)�� Ŭ���� �ߴ��� �˻�
		if ( true == AllClearServerEventQuest() )
		{
			// �ʱ�ȭ
			m_clSEQuestData.Init();
			// ���� ���� �ʱ�ȭ
			InitCharacter();

			// ���� ����
			cltServer* pclserver = (cltServer*)pclClient;
			if ( pclserver )
			{
				pclserver->pclServerEventManager->ManagerExcute( SERVER_EVENT_COMMANDTYPE_INDUN_START );
			}
			SendMessageToClient( SERVEREVENT_QUEST_PACKETTYPE_ALLCLEAR );
			// �ʱ�ȭ��(�ƹ��͵� ����) ������ DB�� ����
			SendMessageToDB( SERVEREVENT_QUEST_PACKETTYPE_SET_QUESTINFO );
		}
		else
		{
			MakeNewServerEventQuest( siEventType );
		}
	}

	return bIsQuestClear;
}

void CNServerEvent_Quest::SetCharacterLimit( SI16 siCharacterLimit )
{
	if ( (0 >= siCharacterLimit) || (Const_ServerEvent_Max_QuestCharacter < siCharacterLimit) )
	{
		return;
	}

	m_siCharacterLimit = siCharacterLimit;
}

void CNServerEvent_Quest::SetNowAmount( SI32 siNowAmount )
{
	if ( 0 > siNowAmount )
	{
		return;
	}
	
	m_siNowAmount = siNowAmount;
}

void CNServerEvent_Quest::SetCharacterIndex( SI16 siCharacterIndex )
{
	if ( (0 > siCharacterIndex) || ((Const_ServerEvent_Max_QuestCharacter*Const_ServerEvent_MulNum) < siCharacterIndex) )
	{
		return;
	}

	m_siCharacterIndex = siCharacterIndex;
}

void CNServerEvent_Quest::SetCharacter( bool bCharacter[] )
{
	if ( NULL == bCharacter )
	{
		return;
	}
	SI32 i = 0;
#ifdef _SAFE_MEMORY
	for(i=0; i<Const_ServerEvent_Max_QuestCharacter; i++)		m_bCharacter[i] = bCharacter[i];
#else
	memcpy( m_bCharacter, bCharacter, sizeof(m_bCharacter) );
#endif
}

void CNServerEvent_Quest::SetInFailCharacter( SI16 siInFailCharacter[] )
{
	if ( NULL == siInFailCharacter )
	{
		return;
	}

	memcpy( m_siInFailCharacter, siInFailCharacter, sizeof(m_siInFailCharacter) );
}

void CNServerEvent_Quest::SetServerEventQuestColck( DWORD dwServerEventQuestColck )
{
	m_dwServerEventQuestColck = dwServerEventQuestColck;
}

void CNServerEvent_Quest::StartServerEventQuest(void)
{
	cltServer* pclserver = (cltServer*)pclClient;
	if ( NULL == pclserver )
	{
		return;
	}
	

	// ���� �̹� ����Ʈ�� �����Ѵٸ�(DB���� �޾ƿ�) ����Ʈ�� �������� ����Ʈ ���� ���·� �����Ѵ�
	if ( m_clSEQuestData.GetEventType() > SERVEREVENT_TYPE_NONE )
	{
		pclserver->pclServerEventManager->SetServerEventState( SERVER_EVENT_STATE_GOING_QUEST );
		return;
	}

	MakeCharacter();
	MakeNewServerEventQuest();
}

void CNServerEvent_Quest::SendMessageToClient( SI32 siPacketType, SI32 siPara1/* =0 */, SI32 siPara2/* =0  */)
{
	// ��� ����ġ �������� ó���Ѵٸ� ���ʿ��� �۾��̰����� ���߿� Ȥ�� �𸣴� ���� üũ����
	if ( (SERVEREVENT_QUEST_PACKETTYPE_NONE >= siPacketType) || (SERVEREVENT_QUEST_PACKETTYPE_END <= siPacketType) )
	{
		return;
	}

	switch ( siPacketType ) 
	{
		case SERVEREVENT_QUEST_PACKETTYPE_QUESTSTART:
			{
				cltGameMsgResponse_Server_Event_Quest_Start clQuestStart( &m_clSEQuestData, m_siCharacterLimit, m_siNowAmount, &m_bCharacter[0] );
				cltMsg clMsg(GAMEMSG_RESPONSE_SERVER_EVENT_QUEST_START, sizeof(clQuestStart), (BYTE*)&clQuestStart);
				pclClient->pclCM->SendAllPersonMsg((sPacketHeader*)&clMsg);
			}
			break;

		case SERVEREVENT_QUEST_PACKETTYPE_RUNINFO:
			{
				cltGameMsgResponse_Server_Event_Quest_RunInfo clRunInfo( m_clSEQuestData.GetLimitMinute(), m_siNowAmount );
				cltMsg clMsg(GAMEMSG_RESPONSE_SERVER_EVENT_QUEST_RUNINFO, sizeof(clRunInfo), (BYTE*)&clRunInfo);
				pclClient->pclCM->SendAllPersonMsg((sPacketHeader*)&clMsg);
			}
			break;

		case SERVEREVENT_QUEST_PACKETTYPE_GETCHAR:
			{
				cltGameMsgResponse_Server_Event_Quest_ClearStatus clClearStatus( SERVEREVENT_MESSAGETYPE_GETCHAR, siPara1 );
				cltMsg clMsg(GAMEMSG_RESPONSE_SERVER_EVENT_QUEST_CLEARSTATUS, sizeof(clClearStatus), (BYTE*)&clClearStatus);
				pclClient->pclCM->SendAllPersonMsg((sPacketHeader*)&clMsg);
			}
			break;

		case SERVEREVENT_QUEST_PACKETTYPE_QUEST_FAIL:
			{
				cltGameMsgResponse_Server_Event_Quest_ClearStatus clClearStatus( SERVEREVENT_MESSAGETYPE_QUEST_FAIL );
				cltMsg clMsg(GAMEMSG_RESPONSE_SERVER_EVENT_QUEST_CLEARSTATUS, sizeof(clClearStatus), (BYTE*)&clClearStatus);
				pclClient->pclCM->SendAllPersonMsg((sPacketHeader*)&clMsg);
			}
			break;

		case SERVEREVENT_QUEST_PACKETTYPE_CHAR_FAIL:
			{
				cltGameMsgResponse_Server_Event_Quest_ClearStatus clClearStatus( SERVEREVENT_MESSAGETYPE_CHAR_FAIL );
				cltMsg clMsg(GAMEMSG_RESPONSE_SERVER_EVENT_QUEST_CLEARSTATUS, sizeof(clClearStatus), (BYTE*)&clClearStatus);
				pclClient->pclCM->SendAllPersonMsg((sPacketHeader*)&clMsg);
			}
			break;

		case SERVEREVENT_QUEST_PACKETTYPE_ALLCLEAR:
			{
				cltGameMsgResponse_Server_Event_Quest_ClearStatus clClearStatus( SERVEREVENT_MESSAGETYPE_QUEST_ALLCLEAR );
				cltMsg clMsg(GAMEMSG_RESPONSE_SERVER_EVENT_QUEST_CLEARSTATUS, sizeof(clClearStatus), (BYTE*)&clClearStatus);
				pclClient->pclCM->SendAllPersonMsg((sPacketHeader*)&clMsg);
			}
			break;
	}

}

void CNServerEvent_Quest::SendMessageToDB( SI32 siPacketType )
{
	cltServer* pclserver = (cltServer*)pclClient;
	if ( NULL == pclserver )
	{
		return;
	}

	switch ( siPacketType ) 
	{
		case SERVEREVENT_QUEST_PACKETTYPE_GET_QUESTINFO:
			{
				sDBRequest_Server_Event_Server_Quest_Info_Get clMsg;
				pclserver->pclGameDBProcess->SendMsg( (sPacketHeader*)&clMsg );
			}
			break;

		case SERVEREVENT_QUEST_PACKETTYPE_SET_QUESTINFO:
			{
				sDBRequest_Server_Event_Server_Quest_Info_Set clMsg( &m_clSEQuestData, &m_bCharacter[0], m_siInFailCharacter, m_siCharacterIndex, m_siNowAmount );
				pclserver->pclGameDBProcess->SendMsg( (sPacketHeader*)&clMsg );
			}
			break;
	}
	
}

void CNServerEvent_Quest::QuestClearForGM( void )
{
	// ����Ʈ�� Ŭ���� �ϱ����� Amount�� �޾ƿ� ��
	SI32 siNeedAmount = m_clSEQuestData.GetNeedClearAmount();
	
	// �����ϰ�
	SetNowAmount( siNeedAmount );

	// Ŭ���� ���μ��� ����
	ServerEventQuestClearProcess();

}