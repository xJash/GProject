#include "../../../common/Event/event.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-Cityhall.h"

#include "../Server/Server.h"
#include "../CommonLogic/MsgType-person.h"
#include "../CommonLogic/Cityhall/Cityhall.h"
#include "../CommonLogic/MsgRval-Define.h"
#include "../ContributionEvent_Common/ContributionEvent_Common.h"

#include "GiantRaccoonResurrectEvent.h"


//==============================================================================
// - ���̾�Ʈ ���� ��Ȱ ���� ����.
//==============================================================================
cltGiantRaccoonResurrectEvent::cltGiantRaccoonResurrectEvent( void )
{
	Clear();

	// ��ӹ��� cltContributionEvent_Common�� ���� ����Ѵ�.
	if( false == Insert( pclClient->GetUniqueFromHash( "KIND_RACCOONTREEBASE" ), 
						 this, 
						 static_IsMakeNpc, 
						 static_CompleteMakeNpc,
						 static_IsContribution )		)
	{
		MessageBox( NULL, TEXT("Error"), TEXT("cltGiantRaccoonResurrectEvent() Insert() Fail"), 0 );
	}

	
	if( false == FileLoad() ) 
		MessageBox( NULL, TEXT("Error"), TEXT("cltGiantRaccoonResurrectEvent() Fail"), 0 );

	m_pclContributionInfo = FindContributionInfo( pclClient->GetUniqueFromHash( "KIND_RACCOONTREEBASE" ) );
	if( NULL == m_pclContributionInfo ) 
		MessageBox( NULL, TEXT("Error"), TEXT("cltGiantRaccoonResurrectEvent() ContributionInfo Fail"), 0 );

}

cltGiantRaccoonResurrectEvent::~cltGiantRaccoonResurrectEvent( void )
{
	SAFE_DELETE( m_pclGRREVillageInfo );
	SAFE_DELETE_ARRAY( m_pclGRREHuntMapMonsterInfo );
}


void	cltGiantRaccoonResurrectEvent::Clear( void )
{
	ZeroMemory( this, sizeof(*this) );
}

bool	cltGiantRaccoonResurrectEvent::FileLoad( void )
{
	bool		bLoadFile = false;
	NDataLoader	dataloader;
	if( pclClient->IsWhereServiceArea( ConstSwitch_TextEncryption ) )
	{
		bLoadFile = dataloader.LoadDataFromCryptFile( "Data/GiantRaccoonResurrectEvent.txt" );		
	}
	else
	{
		if ( pclClient->IsWhereServiceArea(ConstServiceArea_China) )
		{
			bLoadFile = dataloader.LoadDataFromCryptFile( "Data/GiantRaccoonResurrectEvent.txt" );
		}
		else
		{
			bLoadFile = dataloader.LoadDataFromFile( "Data/GiantRaccoonResurrectEvent.txt" );
		}
	}
	
	TCHAR	szMonsterKind[128]		 = "";
	TCHAR	szMap[512]				 = "";
	TCHAR	szEventHour[256]		 = "";
	SI32	siMapRegenMonsterNum	 = 0;
	SI32	siMapOnceRegenMonsterNum = 0;
	SI32	siMonsterRegenTickCount	 = 0;

	NDataTypeInfo pDataTypeInfo[] =
	{
		NDATA_MBSTRING,	szMonsterKind,				sizeof(szMonsterKind),
		NDATA_MBSTRING,	szMap,						sizeof(szMap),
		NDATA_MBSTRING,	szEventHour,				sizeof(szEventHour),
		NDATA_INT32,	&siMapRegenMonsterNum,		sizeof(siMapRegenMonsterNum),
		NDATA_INT32,	&siMapOnceRegenMonsterNum,	sizeof(siMapOnceRegenMonsterNum),
		NDATA_INT32,	&siMonsterRegenTickCount,	sizeof(siMonsterRegenTickCount),
		0,0,0
	};

	dataloader.RegDataType( pDataTypeInfo );
	while( !dataloader.IsEndOfData() ) 
	{
		if( dataloader.ReadData() )
		{
			m_dwMonsterRegenTickCount = (DWORD)siMonsterRegenTickCount * 1000; // ��
			
			if( false == Init(  szMap, 
								szEventHour,
								pclClient->GetUniqueFromHash( szMonsterKind ), 
								siMapRegenMonsterNum, 
								siMapOnceRegenMonsterNum ) ) 
			{
				return false;
			}
		}
	}

	return bLoadFile;
}

bool	cltGiantRaccoonResurrectEvent::Init( TCHAR* _pszMap, TCHAR* _pszEventHour, SI32 _siRegenMonsterKind, SI32 siMapRegenMonsterNum, SI32 siMapOnceRegenMonsterNum )
{
	SI32 siMapCount		 = 0;
	SI32 siMapIndex[128] = { 0, };
	TCHAR* pszData = _tcstok(_pszMap, ":");
	while( pszData )
	{
		siMapIndex[siMapCount++] = _ttoi(pszData);
		
		pszData = _tcstok(NULL, ":");
	}

	m_siTotalMapNum			 = siMapCount;
	m_siTotalRegenMonsterNum = m_siTotalMapNum * siMapRegenMonsterNum;

	m_pclGRREVillageInfo		 = new cltGRREVillageInfo;
	if( NULL == m_pclGRREVillageInfo ) return false;

	m_pclGRREHuntMapMonsterInfo  = new cltGRREHuntMapMonsterInfo[m_siTotalMapNum];
	if( NULL == m_pclGRREHuntMapMonsterInfo ) return false;

	for( SI32 siCount = 0; siCount < m_siTotalMapNum; ++siCount )   
	{
		m_pclGRREHuntMapMonsterInfo[siCount].Init( siMapIndex[siCount], siMapOnceRegenMonsterNum );
	}
	
	m_pclGRREHuntMapMonsterInfo->SetRegenMonsterKind( _siRegenMonsterKind );
	m_pclGRREHuntMapMonsterInfo->SetMapRegenMonsterNum( siMapRegenMonsterNum );
	m_pclGRREHuntMapMonsterInfo->SetMapOnceRegenMonsterNum( siMapOnceRegenMonsterNum );

	pszData = _tcstok(_pszEventHour, ",");
	pszData++;
	while( pszData )
	{
		m_bEventHour[_ttoi(pszData)] = true;

		pszData = _tcstok(NULL, ",");
	}
	
	
	return true;
}

void	cltGiantRaccoonResurrectEvent::Action( void )
{
	// DB �ʱ�ȭ �Ϸ�ɶ����� ��ٸ�
	if( ((cltServer *)pclClient)->bCompleteDBInitAll == FALSE ) return;
	
	// ������ ���� ����Ǹ� �׵��� ��εǾ��� �������� �����Ѵ�.
	static bool bInputItemListDel = false;
	if( false == bInputItemListDel && false == IsEventActiveTime() ) 
	{
		InputItemListDel();
	}
	bInputItemListDel = true;
	

	cltServer* pclserver = (cltServer*)pclClient;
	if( pclserver->pclEventTimeManager->InEventTime("GiantRaccoon_Resurrect_Event", &pclserver->sTime ) )
	{
		// ������ NPC ����
		if( 0 >= m_siNpcID )
		{
			m_siNpcID = pclserver->SetNPCChar( pclClient->GetUniqueFromHash("KIND_POTRACCOON"), 
											VILLAGE_NONE, 
											NULL, 
											1, 
											0, 
											242, 
											313, 
											0, 
											NPCITEMMODE_NONE, 
											NULL );
		}

		bool bEventActiveTime = IsEventActiveTime();

		// �̺�Ʈ �ð��̰� �̺�Ʈ�� �������� �ƴϸ� ����.
		if( true == bEventActiveTime && false == m_bEventActive ) 
		{
			Start();		
		}
		// �̺�Ʈ �ð��� �ƴϰ� �̺�Ʈ�� �������̸� ����.
		else if( false == bEventActiveTime && true == m_bEventActive )
		{
			End();
		}
		// �̺�Ʈ �ð��̰� �̺�Ʈ�� ���� ���̸�.
		else if( true == bEventActiveTime && true == m_bEventActive )
		{
			Run();
		}
	}
	else
	{
		// ������ NPC ����
		if( 0 < m_siNpcID )
		{
			cltCharServer* pclChar = pclserver->pclCM->GetCharServer( m_siNpcID );
			if( pclChar )
			{
				pclChar->DeleteInCell();
				pclserver->pclCM->DeleteChar( pclChar->GetID() );

				m_siNpcID = 0;
			}
		}
	}

	CheckNPC();
}
void	cltGiantRaccoonResurrectEvent::CheckNPC( void )
{
	static DWORD TickCount = 0;
	if( TABS(GetTickCount() - TickCount) < 10000 ) return;
	TickCount = GetTickCount();

	cltServer*	pclserver = (cltServer*)pclClient;

	bool bEventTime = false;
	if( pclserver->pclEventTimeManager->InEventTime("GiantRaccoon_Resurrect_Event", &pclserver->sTime ) )
	{
		bEventTime = true;
	}
			
	bool		bNPC			= true;
	cltStrInfo* pclStrInfo		= NULL;
	SI32		siHireNpcIndex	= -1;
	SI32		siFireNpcIndex	= -1;
	for( SI32 i = 0; i < MAX_VILLAGE_NUMBER; i++ )
	{
		if( i == Const_Beginner_Village ) continue;

		pclStrInfo = pclserver->pclCityHallManager->GetStrInfo( i );
		if( pclStrInfo == NULL )	continue;

		bNPC			= false;
		siHireNpcIndex	= -1;		// ����� ������ �ε��� ��ȣ.
		siFireNpcIndex	= -1;		// ����� �����ϴ� �ε��� ��ȣ.
        for( SI32 siCount = 0; siCount < MAX_HIRED_EVENTNPC_NUM; siCount++ )
		{
			// ����� ������ �ε��� ��ȣ�� �ѹ� ~�����ϸ� �������� �ʾƵ� �ȴ�.
			if( 0 > siHireNpcIndex && 0 >= pclStrInfo->clCityhallStrInfo.clHiredEventNPC[siCount].siNPCKind )
				siHireNpcIndex = siCount;

			if(		pclStrInfo->clCityhallStrInfo.clHiredEventNPC[siCount].siNPCKind == m_pclContributionInfo->m_siNPCKind
				||	pclStrInfo->clCityhallStrInfo.clHiredEventNPC[siCount].siNPCKind == m_pclContributionInfo->m_siMakeNPCKind ) 
			{
				bNPC			= true;
				siFireNpcIndex	= siCount;
				break;
			}
		}

		// �̺�Ʈ �Ⱓ�̸鼭 ������ ������ npc�� �ְ� ������ �̺�Ʈ �ð��� �ƴϸ�.
		if( bEventTime && bNPC && false == IsEventActiveTime() )
		{
			// �׸��� �װ� �ϼ��� NPC���.
			if( pclStrInfo->clCityhallStrInfo.clHiredEventNPC[siFireNpcIndex].siNPCKind == m_pclContributionInfo->m_siMakeNPCKind )
			{
				sDBRequest_HireNPC clFireMsg(	0, 
												i, 
												siFireNpcIndex, 
												0, 
												0, 
												0, 
												&pclserver->pclTime->clDate, 
												HIRENPC_HIREEVENTNPC );

				pclserver->pclGameDBProcess->SendMsg( (sPacketHeader *)&clFireMsg );
				
				sDBRequest_HireNPC clHireMsg(	0, 
												i, 
												siFireNpcIndex, 
												m_pclContributionInfo->m_siNPCKind, 
												0, 
												0, 
												&pclserver->pclTime->clDate, 
												HIRENPC_HIREEVENTNPC );

				pclserver->pclGameDBProcess->SendMsg( (sPacketHeader *)&clHireMsg );
			}
		}
		// �̺�Ʈ �Ⱓ�̸鼭 ������ ������ npc�� ���� ��� �����.
		if( bEventTime && false == bNPC )
		{
			sDBRequest_HireNPC clHireMsg(	0, 
											i, 
											siHireNpcIndex, 
											m_pclContributionInfo->m_siNPCKind, 
											0, 
											0, 
											&pclserver->pclTime->clDate, 
											HIRENPC_HIREEVENTNPC );
			
			pclserver->pclGameDBProcess->SendMsg( (sPacketHeader *)&clHireMsg );
		}

		// �̺�Ʈ �Ⱓ �ƴѵ� ������ ������ npc�� ���� ��� �����Ѵ�.
		if( false == bEventTime && bNPC )
		{
			sDBRequest_HireNPC clFireMsg(	0, 
											i, 
											siFireNpcIndex, 
											0, 
											0, 
											0, 
											&pclserver->pclTime->clDate, 
											HIRENPC_HIREEVENTNPC );

			pclserver->pclGameDBProcess->SendMsg( (sPacketHeader *)&clFireMsg );
		}
	}
}

void	cltGiantRaccoonResurrectEvent::Start( void )
{
	m_bInputItem					= true;
	m_bEventActive					= true;
	m_dwBeginMonsterRegenTickCount	= GetTickCount();
	
	MonsterRegen();

	m_pclGRREVillageInfo->Clear();

	cltServer*	pclserver = (cltServer*)pclClient;
	cltMsg clMsg( GAMEMSG_RESPONSE_GIANTRACCOON_RESURRECT_EVENT_START, PACKET_EMPTY );
	pclserver->pclCM->SendAllPersonMsg( (sPacketHeader*)&clMsg );
}

void	cltGiantRaccoonResurrectEvent::End( void )
{
	m_bEventActive = false;

	MonsterDel();
	InputItemListDel();
}
void	cltGiantRaccoonResurrectEvent::Run( void )
{
	if( m_dwMonsterRegenTickCount > TABS( GetTickCount() - m_dwBeginMonsterRegenTickCount) ) return;
	
	m_dwBeginMonsterRegenTickCount = GetTickCount();

	MonsterRegen();	
}

bool	cltGiantRaccoonResurrectEvent::IsEventActiveTime( void )
{
	cltServer*	pclserver = (cltServer*)pclClient;
	
	return m_bEventHour[pclserver->sTime.wHour];
}

bool	cltGiantRaccoonResurrectEvent::IsInputItem( void )
{
	return m_bInputItem;
}

void	cltGiantRaccoonResurrectEvent::SetFirstMakeVillage( SI32 _siFirstMakeVillage )
{
	m_bInputItem = false;

	m_pclGRREVillageInfo->SetFirstMakeVillage( _siFirstMakeVillage );
}

SI32	cltGiantRaccoonResurrectEvent::GetFirstMakeVillage( void )
{
	return m_pclGRREVillageInfo->GetFirstMakeVillage();
}

bool	cltGiantRaccoonResurrectEvent::IsFirstMakeVillage( SI32 _siFirstMakeVillage )
{
	return m_pclGRREVillageInfo->IsFirstMakeVillage( _siFirstMakeVillage );
}

void	cltGiantRaccoonResurrectEvent::MonsterDel( void )
{
	for( SI32 siCount = 0; siCount < m_siTotalMapNum; ++siCount )
	{
		m_pclGRREHuntMapMonsterInfo[siCount].MonsterDel();
	}
}

void	cltGiantRaccoonResurrectEvent::InputItemListDel( void )
{
	cltServer*	pclserver  = (cltServer*)pclClient;
	cltStrInfo* pclStrInfo = NULL;
	for( SI32 siVillageCount = 0; siVillageCount < MAX_VILLAGE_NUMBER; siVillageCount++ )
	{
		pclStrInfo = pclserver->pclCityHallManager->GetStrInfo( siVillageCount );
		if( pclStrInfo == NULL )	continue;

		for( SI32 siCount = 0; siCount < MAX_HIRED_EVENTNPC_NUM; siCount++ )
		{
			if(		pclStrInfo->clCityhallStrInfo.clHiredEventNPC[siCount].siNPCKind == m_pclContributionInfo->m_siNPCKind
				||	pclStrInfo->clCityhallStrInfo.clHiredEventNPC[siCount].siNPCKind == m_pclContributionInfo->m_siMakeNPCKind ) 
			{
				if( IsFirstMakeVillage( siVillageCount ) )
					ContributionItemListDelete( siVillageCount, m_pclContributionInfo->m_siNPCKind );
				break;
			}
		}
	}
}

void	cltGiantRaccoonResurrectEvent::MonsterRegen( void )
{
	if( GetTotalRegenMonsterCount() >= m_siTotalRegenMonsterNum ) return;

	SI32 siTotalRegenMonsterCount = 0;
	for( SI32 siCount = 0; siCount < m_siTotalMapNum; ++siCount )
	{
		m_pclGRREHuntMapMonsterInfo[siCount].MonsterRegen();
	}
}

SI32	cltGiantRaccoonResurrectEvent::GetTotalRegenMonsterCount( void )
{
	SI32 siTotalRegenMonsterCount = 0;
	for( SI32 siCount = 0; siCount < m_siTotalMapNum; ++siCount )
	{
		siTotalRegenMonsterCount += m_pclGRREHuntMapMonsterInfo[siCount].GetRegenMonsterCount();
	}

	return siTotalRegenMonsterCount;
}

bool	cltGiantRaccoonResurrectEvent::static_IsMakeNpc( void* _pclGiantRaccoonResurrectEvent, cltCharServer* _pclChar )
{
	return ((cltGiantRaccoonResurrectEvent*)_pclGiantRaccoonResurrectEvent)->IsMakeNpc( _pclChar );
}

bool	cltGiantRaccoonResurrectEvent::static_CompleteMakeNpc( void* _pclGiantRaccoonResurrectEvent, cltCharServer* _pclChar )
{
	return ((cltGiantRaccoonResurrectEvent*)_pclGiantRaccoonResurrectEvent)->CompleteMakeNpc( _pclChar );
}

bool	cltGiantRaccoonResurrectEvent::static_IsContribution( void* _pclGiantRaccoonResurrectEvent, cltCharServer* _pclChar )
{
	return ((cltGiantRaccoonResurrectEvent*)_pclGiantRaccoonResurrectEvent)->IsContribution( _pclChar );
}

bool	cltGiantRaccoonResurrectEvent::IsMakeNpc( cltCharServer* _pclChar )
{
	// �̺�Ʈ �ð��� �ƴϸ� ����Ⱑ �Ұ���.
	if( false == IsEventActiveTime() ) return false;

	// ��ΰ� �����Ѱ�. ����Ⱑ �Ұ����ϸ� �̰� � �������� �̹� ��Ȱž�� �Ǽ��߱� �����̴�.
	if( false == IsInputItem()		  ) return false;

	return true;
}

bool	cltGiantRaccoonResurrectEvent::CompleteMakeNpc( cltCharServer* _pclChar )
{
	SetFirstMakeVillage( _pclChar->GetCurrentVillageUnique() );

	cltServer*	pclserver  = (cltServer*)pclClient;
	
	SI32			siID		= 0;
	SI32			siIndex		= 0;
	cltCharServer*	pclChar		= NULL;
	SI32			siUsetime	= pclserver->pclTime->clDate.GetHourVary() + 24; // ���ǽð� 48�а�.
	
	while( siID = pclserver->pclCM->pclIDManager->GetCharOrder(siIndex) )
	{
		siIndex++;
		pclChar = pclserver->pclCM->GetCharServer( siID );
		if( NULL== pclChar || false == IsPC(siID) ) continue;

		if( IsFirstMakeVillage( pclChar->pclCI->clBI.siHomeVillage ) )
		{
			SI32 siSlot = pclChar->pclCI->clBI.clBufInfo.FindEmptySlot( BUF_GIANTRACCOON_RESURRECT_EVENT_FIRST_VILLAGE, false );	
			if( -1 >= siSlot ) continue;
			
			stBuf addBuf( BUF_GIANTRACCOON_RESURRECT_EVENT_FIRST_VILLAGE, 5, siUsetime );
			pclChar->AddBufThroughDB( siSlot, &addBuf , false, 0, NULL, 0 );
		}
	}

	return true;
}

bool	cltGiantRaccoonResurrectEvent::IsContribution( cltCharServer* _pclChar )
{
	// �̺�Ʈ �ð��� �ƴϸ� ��ΰ� �Ұ���.
	if( false == IsEventActiveTime() ) 
	{
		((cltServer*)pclClient)->SendServerResponseMsg( 0, SRVAL_GIANTRACCOONRESURRECTEVENT_NO_TIME, 0, 0, _pclChar->GetID() );
		return false;
	}

	// ��ΰ� �����Ѱ�. ��ΰ� �Ұ����ϸ� �̰� � �������� �̹� ��Ȱž�� �Ǽ��߱� �����̴�.
	if( false == IsInputItem()		  ) 
	{
		((cltServer*)pclClient)->SendServerResponseMsg( 0, SRVAL_GIANTRACCOONRESURRECTEVENT_ALREAY_MAKE_NPC, 0, 0, _pclChar->GetID() );
		return false;
	}

	return true;
}


//==============================================================================
// - ���̾�Ʈ ���� ��Ȱ ���� �� ������ ���� ����.
//==============================================================================
SI32 cltGRREHuntMapMonsterInfo::m_siRegenMonsterKind	   = 0;
SI32 cltGRREHuntMapMonsterInfo::m_siMapRegenMonsterNum     = 0;
SI32 cltGRREHuntMapMonsterInfo::m_siMapOnceRegenMonsterNum = 0;

cltGRREHuntMapMonsterInfo::cltGRREHuntMapMonsterInfo( void )
{
	Clear();
}

cltGRREHuntMapMonsterInfo::~cltGRREHuntMapMonsterInfo( void )
{
	if( m_psiMonsterID ) delete[] m_psiMonsterID;
}

void	cltGRREHuntMapMonsterInfo::Init( SI32 _siMapIndex, SI32 _siMapOnceRegenMonsterNum )
{
	m_siMapIndex	= _siMapIndex;
	m_psiMonsterID	= new SI32[_siMapOnceRegenMonsterNum];
	ZeroMemory( m_psiMonsterID, sizeof(SI32)*_siMapOnceRegenMonsterNum );
}

void	cltGRREHuntMapMonsterInfo::Clear( void )
{
	ZeroMemory( this, sizeof(*this) );
}

SI32	cltGRREHuntMapMonsterInfo::GetMapIndex( void )
{
	return m_siMapIndex;
}

void	cltGRREHuntMapMonsterInfo::MonsterDel( void )
{
	cltServer* pclserver = (cltServer*)pclClient;

	cltCharServer*	pclMonsterChar = NULL;
	for( SI32 siCount = 0; m_siMapOnceRegenMonsterNum > siCount; ++siCount )
	{
		pclMonsterChar = pclserver->pclCM->GetCharServer( m_psiMonsterID[siCount] ); 
		if( pclMonsterChar && (m_siRegenMonsterKind == pclMonsterChar->GetKind()) )
		{
			cltGameMsgResponse_IncLife clInfo( pclMonsterChar->GetCharUnique(), 0, 0, 0, 0, INCLIFE_REASON_EVENT_END );
			cltMsg clMsg( GAMEMSG_RESPONSE_INCLIFE, PACKET(clInfo) );
			pclMonsterChar->SendNeighbourMsg( &clMsg, true );

			pclMonsterChar->SetLife(0);
		}
	}

	ZeroMemory( m_psiMonsterID, sizeof(m_psiMonsterID) * m_siMapOnceRegenMonsterNum );	// �ش� �ʿ� ���� �� ������ ID ����.
	m_siRegenMonsterCount = 0;															// ���� �� ������ ���� �� 0.
}

void	cltGRREHuntMapMonsterInfo::MonsterRegen( void )
{
	if( m_siMapRegenMonsterNum <= m_siRegenMonsterCount ) return;
	
	cltServer* pclserver = (cltServer*)pclClient;

	cltInnerStatusInfo clinnerstatus;
	clinnerstatus.clEnemyType.Set(ENEMYTYPE_ALLPC, 0);   

	bool			bFindLocate			= false;
	SI32 			tempx 				= (rand() % 5);
	SI32 			tempy 				= (rand() % 5);
	SI32 			x 					= 0;
	SI32 			y 					= 0;
	SI32			siExitCnt			= 0;
	const SI32		Const_Limit_Count	= 30;
	
	cltCharServer*	pclMonsterChar		= NULL;

	for( SI32 siCount = 0; m_siMapOnceRegenMonsterNum > siCount; ++siCount )
	{
		pclMonsterChar = pclserver->pclCM->GetCharServer( m_psiMonsterID[siCount] ); 
		if( pclMonsterChar && (m_siRegenMonsterKind == pclMonsterChar->GetKind()) ) continue; 

		// ��ġ�� ��ã�� ���ٸ� �ִ� 30������ ������ ����
		do 
		{
			if ( siExitCnt++ > Const_Limit_Count ) break;

			tempx = 1 + rand() % pclClient->pclMapManager->pclMapArray[m_siMapIndex]->GetXsize();
			tempy = 1 + rand() % pclClient->pclMapManager->pclMapArray[m_siMapIndex]->GetYsize();

			bFindLocate	= pclClient->pclMapManager->pclMapArray[m_siMapIndex]->FindEmptyAreaForCharLocate(	m_siMapIndex, 
																											tempx, 
																											tempy, 
																											10, 
																											&x, 
																											&y, 
																											true);
		}while( false == bFindLocate );
		
				
		if ( true == bFindLocate )
		{
			m_psiMonsterID[siCount] = pclserver->SetNPCChar(m_siRegenMonsterKind, 
															VILLAGE_NONE, 
															NULL, 
															90, 
															0, 
															x, 
															y, 
															m_siMapIndex, 
															NPCITEMMODE_NORMAL, 
															&clinnerstatus);
			if( m_psiMonsterID[siCount] )
			{ 
				if( m_psiMonsterID[siCount] ) ++m_siRegenMonsterCount;

				// ������ ���Ͱ� ���̾�Ʈ ���� ��Ȱ �̺�Ʈ ������ ������ �������� ����.
				cltCharServer* pclNewMonsterChar = pclClient->pclCM->GetCharServer( m_psiMonsterID[siCount] );
				if( pclNewMonsterChar ) 
				{
                	pclNewMonsterChar->clIdentity.MakeGiantRaccoonResurrectEvent();
				
					//������ ���Ϳ��� �������� ����Ѵ�.
					pclNewMonsterChar->pclCI->clCharItem.clItem[PERSONITEM_INV0]= ITEMUNIQUE(13064);
					pclNewMonsterChar->pclCI->clCharItem.clItem[PERSONITEM_INV0]= 1;
				}
			}
		}
	}
}

SI32	cltGRREHuntMapMonsterInfo::GetRegenMonsterCount( void )
{
	return m_siRegenMonsterCount;
}

void	cltGRREHuntMapMonsterInfo::SetRegenMonsterKind( SI32 _siRegenMonsterKind )
{
	m_siRegenMonsterKind = _siRegenMonsterKind;
}

void	cltGRREHuntMapMonsterInfo::SetMapRegenMonsterNum( SI32 _siMapRegenMonsterNum )
{
	m_siMapRegenMonsterNum = _siMapRegenMonsterNum;
}

void	cltGRREHuntMapMonsterInfo::SetMapOnceRegenMonsterNum( SI32 _siMapOnceRegenMonsterNum )
{
	m_siMapOnceRegenMonsterNum = _siMapOnceRegenMonsterNum;
}


//==============================================================================
// - �� ������ ���̾�Ʈ ���� ��Ȱ ���� ����.
//==============================================================================
cltGRREVillageInfo::cltGRREVillageInfo( void )
{
	Clear();
}

cltGRREVillageInfo::~cltGRREVillageInfo( void )
{

}

void	cltGRREVillageInfo::Clear( void )
{
	ZeroMemory( this, sizeof(*this) );
}

void	cltGRREVillageInfo::SetFirstMakeVillage( SI32 _siFirstMakeVillage )
{
	m_siFirstMakeVillage = _siFirstMakeVillage;
}

SI32	cltGRREVillageInfo::GetFirstMakeVillage( void )
{
	return m_siFirstMakeVillage;
}

bool	cltGRREVillageInfo::IsFirstMakeVillage( SI32 _siFirstMakeVillage )
{
	return m_siFirstMakeVillage ? m_siFirstMakeVillage == _siFirstMakeVillage : false;
}

