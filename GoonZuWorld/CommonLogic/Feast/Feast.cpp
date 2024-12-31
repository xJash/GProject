#include <CommonLogic.h>
#include "Char\CharCommon\Char-Common.h"
#include "Char\CharManager\CharManager.h"

#include "Feast.h"
#include "..\..\Resource.h"

#include "../../CommonLogic/MsgType-Structure.h"
#include "../../CommonLogic/msg/MsgType-Feast.h"

#include "../CityHall/TaxpaymentListDlg.h"
#include "../Server/Server.h"

#include "NDate.h"

#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Feast.h"
#include "..\..\..\DBManager\GameDBManager_World\DbMsg-person.h"
#include "..\..\Client\Music\Music.h"

#include "MsgRval-Define.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-item.h"

extern cltCommonLogic* pclClient;


//----------------------------------------------
// cltFeast
//----------------------------------------------
cltFeast::cltFeast(SI32 sivillageunique) : cltStructureBasic(sivillageunique)
{
}


cltFeast::~cltFeast()
{

}




cltFeastManager::cltFeastManager(cltCharManager* pclcm, SI32 gamemode, SI32 portraitid, TCHAR *strFileName ) : cltStructureMngBasic(MAX_STOCK_TAB_NUMBER, pclcm, portraitid, strFileName )
{
	bUpdateUser = FALSE;
	bUpdateChief2 = FALSE;

	m_pclMyItem			= new cltItem[ MAX_ITEM_PER_PERSON ];
	m_pclStgItem		= new cltFeastStg[ MAX_FEAST_STG_NUMBER ];

	if(gamemode == GAMEMODE_SERVER)
	{

	}
	else
	{

	}

	SI32 i = 0; 
#ifdef _SAFE_MEMORY
	for(i=0; i<MAX_PARTYHALL_MAP; i++)		clPartyHallResvInfo[i].ZeroMem();
	m_siGatePositionID.ZeroMem();
	m_PartyHallUserPos.ZeroMem();
	m_DecorationPos.ZeroMem();
#else
	ZeroMemory(clPartyHallResvInfo, sizeof(clPartyHallResvInfo));
	ZeroMemory(m_siGatePositionID,  sizeof(m_siGatePositionID)); 
	ZeroMemory(m_PartyHallUserPos,	sizeof(m_PartyHallUserPos));
	ZeroMemory(m_DecorationPos,		sizeof(m_DecorationPos)); 
#endif

	// ���� ���� ��ġ.
	POINT PartyHallUserPos[MAX_PARTYHALL_MAP] = { 
													25, 46, 
													 9, 11, 
													23, 50, 
													21, 54, 
													32, 53 
												};

	// ��Ĺ� �߰��� ��ġ�� ���⼭.
	POINT DecorationPos[MAX_PARTYHALL_MAP] = { 
												23, 18, 
												36, 24, 
												36, 38, 
												20, 30, 
												44, 48
											};

#ifdef _SAFE_MEMORY
	for(i=0; i<MAX_PARTYHALL_MAP; i++)	m_PartyHallUserPos[i] = PartyHallUserPos[i];
	for(i=0; i<MAX_PARTYHALL_MAP; i++)	m_DecorationPos[i] = DecorationPos[i];
#else
	memcpy(m_PartyHallUserPos,	PartyHallUserPos,	sizeof(m_PartyHallUserPos));
	memcpy(m_DecorationPos,		DecorationPos,		sizeof(m_DecorationPos));
#endif

}


cltFeastManager::~cltFeastManager()
{
	if ( m_pclMyItem )			delete [] m_pclMyItem;
	if ( m_pclStgItem )			delete [] m_pclStgItem;
}


// ���� ȯ�� �λ縻ǥ��..
void cltFeastManager::GreetingMsg(HWND hDlg)
{
	TCHAR* pText = GetTxtFromMgr(1844);
	SetMainExplain(hDlg, pText);
}

void cltFeastManager::Do_WM_INITDIALOG(SI32 charunique)
{
	bUpdateUser = FALSE;
	bUpdateChief2 = FALSE;

	cltStructureMngBasic::Do_WM_INITDIALOG(charunique);
}


// ���ڽ��� �ż��Ѵ�.
BOOL cltFeastManager::CreateFeast(SI32 siunique)
{
	if(pclStruct[siunique] == NULL)
	{
		pclStruct[siunique] = new cltFeast(siunique);
		return TRUE;
	}

	return FALSE;
}

SI32 cltFeastManager::GetReveIndex( SI32 _PartyHallIndex, SI32 _PersonID )
{
	// �ε��� �����̸� -1����.
	if( 0 > _PartyHallIndex || MAX_PARTYHALL_MAP <= _PartyHallIndex )
		return -1;


	cltPatyHallResvInfo* pPatyHallResvInfoList = &clPartyHallResvInfo[_PartyHallIndex][0];	

	for(SI32 ResvIndex = 0; ResvIndex < MAX_PARTYHALL_RESERVATION_INFO_LIST; ++ResvIndex)
	{
		if( _PersonID == pPatyHallResvInfoList[ResvIndex].m_siPersonID )
		{
			return ResvIndex;
		}
	}

	// ������ -1����.
	return -1;
}

void cltFeastManager::PartyhallEnd( void )
{
	cltServer* pclserver = (cltServer* )pclClient;

	SYSTEMTIME StartTime, CloseTime;
	ZeroMemory( &StartTime, sizeof(StartTime) );
	ZeroMemory( &CloseTime,	sizeof(CloseTime) ); 
	
	StartTime.wYear  = 2008;
	StartTime.wMonth =	  1;
	StartTime.wDay   =    1;
		
	bool RequestPartyList = false;
	SI32 PersonID		  = 0;	
	SI32 id				  = 0;

	pclClient->pclLog->FilePrint( TEXT("config\\PartyHall.log"), TEXT("pclserver->sTime.wMinute : %d"),  pclserver->sTime.wMinute);

	if( 0 == pclserver->sTime.wMinute)	
	{
		GiveItem();

		// ������ ������ ���縮���� �̵�.
		for( SI32 UserIDCount = 1; UserIDCount < MAX_PERSON_NUMBER; ++UserIDCount )
		{
			if( false == pclCM->IsValidID( UserIDCount ) )
				continue;

			//for(SI32 PartyHallCount = 0; PartyHallCount < MAX_PARTYHALL_MAP; ++PartyHallCount )
			{
				if( pclCM->CR[UserIDCount]->GetMapIndex() >= PARTYHALL_START_MAP_INDEX &&
					pclCM->CR[UserIDCount]->GetMapIndex() <  PARTYHALL_START_MAP_INDEX	+ MAX_PARTYHALL_MAP	)
					// ��Ƽ�忡 �ִ� ������ �ִٸ�.
					//if( (PARTYHALL_START_MAP_INDEX + PartyHallCount) == pclCM->CR[UserIDCount]->GetMapIndex() )
				{
					SI32		siWarpX = 27; //12 + (rand() % 5);   
					SI32		siWarpY = 87; //12 + (rand() % 5);
					cltWarpInfo clWarp(1, MAPINDEX_PALACE, false, false, siWarpX, siWarpY, -1, -1);

					pclCM->CR[ UserIDCount ]->SetWarpInfo( &clWarp, 1024 );
					pclCM->CR[ UserIDCount ]->Warp();

					// ��Ƽ�� ���Ḧ �˸�.
					pclserver->SendServerResponseMsg(0, SRVAL_FAIL_PARTYHALL,  PARTYHALL_CLOSE, 0, pclCM->CR[ UserIDCount ]->GetCharUnique());		
				}
			}
		}

		// ��ƼȦ npc ��� ����.
		for( SI32 Count = 0; Count < MAX_CHAR_NUMBER; ++Count )
		{
			if( false == IsNPC(Count) )						  continue;
			if( false == pclserver->pclCM->IsValidID(Count) ) continue;

			if( pclserver->pclCM->CR[Count]->GetMapIndex() >= PARTYHALL_START_MAP_INDEX &&
				pclserver->pclCM->CR[Count]->GetMapIndex() <  PARTYHALL_START_MAP_INDEX	+ MAX_PARTYHALL_MAP	)
			{ 
				if( pclserver->pclCM->CR[Count]->GetKind() != pclClient->GetUniqueFromHash( TEXT("KIND_PARTYNPC") ) )
					pclserver->pclCM->DeleteChar( Count ); 
			}
		}


		// ��Ĺ� ���� �� �����.
		cltPatyHallResvInfo* pPatyHallResvInfo = NULL;
		for(SI32 Count = 0; Count < MAX_PARTYHALL_MAP; ++Count)
		{
			pclClient->pclLog->FilePrint( TEXT("config\\PartyHall.log"), TEXT("�ʹ�ȣ : %d, ���� ��Ĺ� : %d"),  Count, m_siGatePositionID[Count]);

			// ���� ��Ĺ� ����.
			if( 0 < m_siGatePositionID[Count] )
			{
				//pclserver->pclCM->DeleteChar( m_siGatePositionID[Count] ); 
				m_siGatePositionID[Count] = 0;
			}
			// ���� �ð��� ��Ĺ� ���̵� ����. 
			m_siGatePositionID[Count] = 0;

			pPatyHallResvInfo = &pclClient->pclFeastManager->clPartyHallResvInfo[Count][0];

			pclClient->pclLog->FilePrint( TEXT("config\\PartyHall.log"), TEXT("PersonID : %d"),  pPatyHallResvInfo[pclserver->sTime.wHour].m_siPersonID);

			if(0 < pPatyHallResvInfo[pclserver->sTime.wHour].m_siPersonID)
			{
				pclClient->pclLog->FilePrint( TEXT("config\\PartyHall.log"), TEXT("�ð� : %d, ���ο� ��Ĺ� : %d"),  pclserver->sTime.wHour, pPatyHallResvInfo[pclserver->sTime.wHour].m_siDecorationKind);

				// ���ο� ��Ĺ� ��ġ.
				if( 0 < pPatyHallResvInfo[pclserver->sTime.wHour].m_siDecorationKind )
				{
					m_siGatePositionID[Count] = pclserver->SetNPCChar( pPatyHallResvInfo[pclserver->sTime.wHour].m_siDecorationKind, 
																		VILLAGE_NONE, NULL, 
																		1, 
																		0, 
																		m_DecorationPos[Count].x, 
																		m_DecorationPos[Count].y, 
																		PARTYHALL_START_MAP_INDEX + Count, 
																		NPCITEMMODE_NONE, 
																		NULL );

					pclClient->pclLog->FilePrint( TEXT("config\\PartyHall.log"), TEXT("�ð� : %d, ��ġ�� ���ο� ��Ĺ� : %d"),  pclserver->sTime.wHour, m_siGatePositionID[Count]);

					//[����] �����ϸ� ���� �� �õ��Ѵ�.
					if( 0 >= m_siGatePositionID[Count] )
					{
						for( SI32 Count2 = 0; Count2 < 5; ++Count2 )
						{
							m_siGatePositionID[Count] = pclserver->SetNPCChar( pPatyHallResvInfo[pclserver->sTime.wHour].m_siDecorationKind, 
																				VILLAGE_NONE, NULL, 
																				1, 
																				0, 
																				m_DecorationPos[Count].x + rand()%3,          
																				m_DecorationPos[Count].y + rand()%3, 
																				PARTYHALL_START_MAP_INDEX + Count, 
																				NPCITEMMODE_NONE, 
																				NULL );

							pclClient->pclLog->FilePrint( TEXT("config\\PartyHall.log"), TEXT("�ð� : %d, ��ġ�� �����Ͽ� ��õ��ϴ� ���ο� ��Ĺ� : %d"),  pclserver->sTime.wHour, m_siGatePositionID[Count]);

							if( 0 < m_siGatePositionID[Count] )	break;
						}
					}
				}
			}
						
			
			// ��Ƽ ������  �˸�.
			SI32 PersonID = pPatyHallResvInfo[pclserver->sTime.wHour].m_siPersonID;
			if(0 < PersonID)
			{
				SI32 id		  = 0;
				id = pclClient->pclCM->GetIDFromPersonID(PersonID);
				if(false == pclClient->pclCM->IsValidID(id))
					continue;
				
				pclserver->SendServerResponseMsg(0, SRVAL_FAIL_PARTYHALL,  PARTYHALL_OPEN, 0, pclClient->pclCM->CR[id]->GetCharUnique());		
			}
		}

		SYSTEMTIME RequestTime;
		ZeroMemory(&RequestTime, sizeof(RequestTime));
		TimeAddHour(&pclserver->sTime, -1, &RequestTime);

		sDBRequest_PartyHall_ReserveList clPartyHallMsg( RequestTime );
		((cltServer *)pclClient)->pclGameDBProcess->SendMsg((sPacketHeader *)&clPartyHallMsg);
	}
}

void cltFeastManager::Action()
{
	// DB �ʱ�ȭ �Ϸ�ɶ����� ��ٸ�
	if( ((cltServer *)pclClient)->bCompleteDBInitAll == FALSE ) return;

	cltServer* pclserver = (cltServer* )pclClient;

	static SI32 Minute = -1;
	if( Minute == pclserver->sTime.wMinute )
		return;
	else
		Minute = pclserver->sTime.wMinute;

	
	
	TCHAR buffer1[ 1024 ];
	TCHAR buffer2[ 1024 ];

	//[����] ��ƼȦ. ��ƼȦ�� ����. 2008. 3. 10
	if( pclClient->IsCountrySwitch( Switch_PartyHall ) )
	{
		//[����] ��ƼȦ. ��Ƽ�� ����� ��Ƽ�� ����. 
		PartyhallEnd();

		// �̰� 5�п� �ѹ��� ä���ش�.
		if(0 == Minute%5)
		{
			GiveReward();
		}
	}
		
	
	NDate date, sysdate;
	SI32 dv, sysdv;

	SYSTEMTIME systime;
	GetLocalTime( &systime );

	sysdate.SetDate( systime.wYear, systime.wMonth, systime.wDay );
	sysdv = sysdate.GetDateVary();

	cltFeast *pclFeast;

	int i, status;

	for( i = 0; i < MAX_VILLAGE_NUMBER; ++i )
	{
		pclFeast = (cltFeast*)pclStruct[i];
		if ( pclFeast )
		{
			status = pclFeast->clStrInfo.clFeastStrInfo.clFeastInfo.siStatus;
			if( status  == 0 ) continue;

			cltFeastResvInfo *pclResvInfo = &pclFeast->clStrInfo.clFeastStrInfo.clFeastResvInfo;

			date.SetDate( pclResvInfo->siYear, pclResvInfo->siMonth, pclResvInfo->siDay );
			dv = date.GetDateVary();


			if( status != 0 ) {
				if( pclserver->GetFrame() % ( 20 * 60 * 10 ) == 0 &&
					(SI32)pclserver->pclTime->clDate.uiYear == pclResvInfo->siYear &&
					(SI32)pclserver->pclTime->clDate.uiMonth == pclResvInfo->siMonth &&
					(SI32)pclserver->pclTime->clDate.uiDay + 1 >= pclResvInfo->siDay ) 
				{

					TCHAR* pText = GetTxtFromMgr(1845);
					StringCchPrintf( buffer1, 1024, pText, 
						pclserver->pclVillageManager->GetName( i ),
						pclResvInfo->siYear, pclResvInfo->siMonth, pclResvInfo->siDay,
						pclResvInfo->siHour, pclResvInfo->siMinute );

					StringCchPrintf( buffer2, 1024, TEXT("%s"), pclResvInfo->szPersonName );

					

					pclserver->PushSpecialNews( buffer1, buffer2 , NULL, CAPTIONKIND_NEWS,CAPTIONKIND_NEWSCHAT);

					SI32 k;
					for ( k = 0 ; k < sizeof(pclResvInfo->szReason) ; k ++ )
					{
						if( pclResvInfo->szReason[k] == '\r' ||
							pclResvInfo->szReason[k] == '\n' )
						{
							pclResvInfo->szReason[k] = ' ';
						}
					}

					MStrCpy(buffer1, pclResvInfo->szReason, sizeof(pclResvInfo->szReason) );

					pclserver->PushSpecialNews( buffer1, buffer2 ,NULL, CAPTIONKIND_NEWS,CAPTIONKIND_NEWSCHAT);
				}
			}

			if( status == 1 ) {
				// ��ȸ���̸�,

				if( sysdv > dv || ( sysdv == dv && 
					systime.wHour * 60 + systime.wMinute >= 
					pclResvInfo->siHour * 60 + pclResvInfo->siMinute + 20 )) {

						// ��ȸ�� ������.
						pclFeast->clStrInfo.clFeastStrInfo.clFeastInfo.siStatus = 0;

						sDBRequest_FeastClose sendMsg( i );
						pclserver->pclGameDBProcess->SendMsg((sPacketHeader *)&sendMsg);	
				}
			
			} else if( status == 2 ) {
				// �������̸�,

				if( sysdv > dv || ( sysdv == dv && 
					systime.wHour * 60 + systime.wMinute >= 
					pclResvInfo->siHour * 60 + pclResvInfo->siMinute )) {

						pclFeast->clStrInfo.clFeastStrInfo.clFeastInfo.siStatus = 1;

						// ��ȸ�� �����Ѵ�.
						sDBRequest_FeastOpen sendMsg( i );
						pclserver->pclGameDBProcess->SendMsg((sPacketHeader *)&sendMsg);
				}
			}
		}
	}
}

BOOL cltFeastManager::IsMyInventoryChanged()
{

	int i, j;
	BYTE* src;
	BYTE* dst;

	for ( j = PERSONITEM_INV0; j < MAX_ITEM_PER_PERSON; ++j )		// ����â�� üũ�� �ʿ� �����Ƿ�, 10 ���� ��.
	{
		SI32 size = sizeof(cltItem);

		src = (BYTE*)&m_pclMyItem[ j ];
		dst = (BYTE*)&pclClient->pclCM->CR[1]->pclCI->clCharItem.clItem[ j ];

		for( i = 0;i < size; i++)
		{
			if( src[i] != dst[i] )
			{
				return TRUE;
			}
		}
	}

	return FALSE;
}


BOOL cltFeastManager::IsStgChanged()
{
	for ( int i = 0; i < MAX_FEAST_STG_NUMBER; ++i )
	{
		if ( m_pclStgItem[ i ].siItemNum != clClientStrInfo.clFeastStrInfo.clFeastStg[ i ].siItemNum || 
			m_pclStgItem[ i ].siItemUnique != clClientStrInfo.clFeastStrInfo.clFeastStg[ i ].siItemUnique )
		{
			return true;
		}
	}	

	return false;
}

// ��Ƽ�忡 ��Ĺ��� ������ ���� �������� �ɲ��� ����. �ǰ����� ��������.
void cltFeastManager::GiveReward(void)
{
	cltServer* pclserver = (cltServer* )pclClient;

	SI32 DecorationMapIndex[MAX_PARTYHALL_MAP];
	ZeroMemory(DecorationMapIndex, sizeof(DecorationMapIndex));

	SI32 DecorationID	= 0;
	SI32 DecorationNum  = 0;
	for(SI32 DecorationCount = 0; DecorationCount < MAX_PARTYHALL_MAP; ++DecorationCount)
	{
		DecorationID = m_siGatePositionID[DecorationCount];
		if(0 >= DecorationID)
			continue;
		
		DecorationMapIndex[DecorationNum++] = pclCM->CR[DecorationID]->GetMapIndex();
	}
	
	// ����� �����Ƿ� ����.
	if(0 >= DecorationNum)
		return;

	// ����� +5 ����, ������� +5 ����.
	SI32	siLevel		= 0;
	SI16	siHungry	= 0;	
	SI16	siAddHungry	= 0;	// ������ �ǰ�.
	SI32	max			= 0;	// ����� �ִ� ũ��.
	TCHAR*	pName		= NULL;
	for(SI32 UserCount = 1; UserCount < MAX_PERSON_NUMBER; ++UserCount)
	{
		if(false == pclCM->IsValidID(UserCount))
			continue;		

		for(SI32 DecorationCount = 0; DecorationCount < DecorationNum; ++DecorationCount)
		{
			if(pclCM->CR[UserCount]->GetMapIndex() == DecorationMapIndex[DecorationCount])
			{
				siLevel  = pclCM->CR[UserCount]->pclCI->clIP.GetLevel();
				siHungry = pclCM->CR[UserCount]->pclCI->clHealthInfo.siHungry;
				if(siLevel - siHungry > 5)
				{
					siAddHungry = 5;
				}
				else
				{	
					siAddHungry = siLevel - siHungry;
				}
				max	= min(100, MAXORG(siLevel));								
				pclCM->CR[UserCount]->pclCI->clHealthInfo.siHungry += siAddHungry;
				
				if(max > pclCM->CR[UserCount]->pclCI->clHealthInfo.siInnerOrg1)
					pclCM->CR[UserCount]->pclCI->clHealthInfo.IncreaseInnerOrg1(min(5, max - pclCM->CR[UserCount]->pclCI->clHealthInfo.siInnerOrg1));

				if(max > pclCM->CR[UserCount]->pclCI->clHealthInfo.siInnerOrg2)
					pclCM->CR[UserCount]->pclCI->clHealthInfo.IncreaseInnerOrg2(min(5, max - pclCM->CR[UserCount]->pclCI->clHealthInfo.siInnerOrg2));
				
				if(max > pclCM->CR[UserCount]->pclCI->clHealthInfo.siInnerOrg3)
                    pclCM->CR[UserCount]->pclCI->clHealthInfo.IncreaseInnerOrg3(min(5, max - pclCM->CR[UserCount]->pclCI->clHealthInfo.siInnerOrg3));

				if(max > pclCM->CR[UserCount]->pclCI->clHealthInfo.siInnerOrg4)
					pclCM->CR[UserCount]->pclCI->clHealthInfo.IncreaseInnerOrg4(min(5, max - pclCM->CR[UserCount]->pclCI->clHealthInfo.siInnerOrg4));
 
				// DB�� �����Ѵ�. 
				sDBRequest_SetHealth clMsg(pclCM->CR[UserCount]->pclCI->GetPersonID(), &pclCM->CR[UserCount]->pclCI->clHealthInfo);
				pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
				pclCM->CR[UserCount]->SetUpdateSwitch(UPDATE_HEALTH, true, 0);
				
				
				// ��Ĺ� �� �ݺ��� ��ž.
				DecorationCount = DecorationNum;
			}
		}
	}
}

void cltFeastManager::GiveItem(void)
{
	cltServer* pclserver = (cltServer* )pclClient;
	SYSTEMTIME GiveItemTime;
	TimeAddHour(&pclserver->sTime, -1, &GiveItemTime);

	for(SI32 Count = 0; Count < MAX_PARTYHALL_MAP; ++Count)
	{
		//-----------------------------
		// ������ �������� �ִ��� Ȯ��.
		//-----------------------------
		cltPatyHallResvInfo* pPartyHallResvList	= &pclClient->pclFeastManager->clPartyHallResvInfo[ Count ][ 0 ];
		cltPatyHallResvInfo* pPartyHallResvInfo = NULL;

		

		// �������� ������ ��Ƽ���� ������.
		pPartyHallResvInfo = &pPartyHallResvList[GiveItemTime.wHour];

		// ���� �������� ������ ���.
		cltPartyHallPresentItemInfo* pPartyItem = &pPartyHallResvInfo->m_PresentItem[0];

		// ù��° �������� ������ ���� �����۵� �����Ƿ� ����. 
		if( 0 >= pPartyItem->m_siItemUnique || 0 >= pPartyItem->m_siItemNum )
			continue;
		//----------------------------
		SI32		PersonIDGiveItem[MAX_PERSON_NUMBER];
		ZeroMemory( PersonIDGiveItem, sizeof( PersonIDGiveItem ) );

		
		SI32 MapIndex		= PARTYHALL_START_MAP_INDEX + Count;
		SI32 id				= 0;	
		SI32 UserCountNum	= 0;
		for(SI32 IdCount = 1; IdCount < MAX_PERSON_NUMBER; ++IdCount)
		{
			// ���̵� ��� �˻�.
			if( false == pclCM->IsValidID(IdCount) ) 
				continue;

			// ��Ƽ�忡 �ִ� ������ ���̵� ����.
			if( MapIndex == pclCM->CR[IdCount]->GetMapIndex() )
			{
				PersonIDGiveItem[UserCountNum] = IdCount;
				++UserCountNum; 
			}
		}

		// ������ ���� ������ ����.
		if( 0 >= UserCountNum )
		{
			// �ش� ���� ������ ���� ����.
			ZeroMemory( pPartyItem, sizeof(cltPartyHallPresentItemInfo) * RESERVATIO_PRESENT_ITEM );
			continue;
		}

		SI32 GiveItemNum[RESERVATIO_PRESENT_ITEM];
		ZeroMemory( GiveItemNum, sizeof(GiveItemNum));
		for( SI32 count = 0; count < RESERVATIO_PRESENT_ITEM; ++count )
		{
			if( 0 >= pPartyItem[count].m_siItemNum )
				break;

			GiveItemNum[count] = pPartyItem[count].m_siItemNum / UserCountNum;
			if( 0 >= GiveItemNum[count] )
				GiveItemNum[count] = 1;
		}


		SI32			ItemSlot = 0;
		cltCharServer*	pclchar	 = NULL;
		for( SI32 UserCount = 0; UserCount < UserCountNum; ++UserCount )
		{	
			if(false == pclCM->IsValidID(PersonIDGiveItem[UserCount]))
				continue;

			pclchar = (cltCharServer*)pclCM->CR[PersonIDGiveItem[UserCount]];
			if(NULL == pclchar)
				continue;

			pclchar->GiveItem( pPartyItem[ItemSlot].m_siItemUnique, GiveItemNum[ItemSlot], INPUTITEMPERSON_OPTION_PARTYHALL_GIVE_ITEM, 0 );

			// ������ ������ �������� ����.
			pPartyItem[ItemSlot].m_siItemNum -= GiveItemNum[ItemSlot];

			// �����Ϸ��� �纸�� ���������� ���ٸ� 1���� ��������.
			if( GiveItemNum[ItemSlot] > pPartyItem[ItemSlot].m_siItemNum )
				GiveItemNum[ItemSlot] = 1;

			// ���̻� ������ �������� ������ ���� �������� ��������.
			if( 0 >= pPartyItem[ItemSlot].m_siItemNum )	
				++ItemSlot;

			// ������ �������� �� ���� ������ ��ž.
			if( RESERVATIO_PRESENT_ITEM <= ItemSlot )
				break;

			// ���̻� ���� ������ ������ �������� ������.
			if( 0 >= pPartyItem[ItemSlot].m_siItemNum )
				break;

			// ������ �����ε� ���� �������� �ִٸ� �ٽ� ó�� �������� �������� �ټ��ְ� �Ѵ�.
			if( (UserCount + 1) == UserCountNum ) 
			{
				if( 0 < pPartyItem[ItemSlot].m_siItemNum )
				{
					UserCount = -1;
				}
			}
		}

		// �ش� ���� ������ ���� ����.
		ZeroMemory( pPartyItem, sizeof(cltPartyHallPresentItemInfo) * RESERVATIO_PRESENT_ITEM );
	}
}

bool cltFeastManager::IsPartyHallMap( SI32 MapIndex )
{
	if( MapIndex >= PARTYHALL_START_MAP_INDEX &&
		MapIndex <  PARTYHALL_START_MAP_INDEX	+ MAX_PARTYHALL_MAP	)
		return true;

	return false;
}
