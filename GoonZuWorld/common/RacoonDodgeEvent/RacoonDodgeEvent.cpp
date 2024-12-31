//Switch_10MonthEvent_RacoonDodge
#include "RacoonDodgeEvent.h"
#include "../Common/CommonHeader.h"
#include "../CommonLogic/CommonLogic.h"
#include "../../Server/Server.h"
#include "../../NLib/NUtil.h"

#include "../Char/CharServer/Char-Server.h"
#include "../Char/CharManager/CharManager.h"
#include "../Char/CharCommon/Char-Common.h"

#include "../common/Event/event.h"

#include "../../DBManager/GameDBManager_World/DBMsg-PVP_League.h"
#include "../../DBManager/GameDBManager_World/DBMsg-Item.h"
#include "../../DBManager/GameDBManager_World/DBMsg-Person.h"
#include "../../CommonLogic/MsgType-Person.h"
#include "../../CommonLogic/Msg/MsgType-RacoonDodgeEvent.h"
#include "../../CommonLogic/MsgRval-Define.h"

#include "MsgType-System.h"

ReserveData::ReserveData()
{
	init();
}
ReserveData::~ReserveData()
{

}
void ReserveData::init()
{
	ZeroMemory(this , sizeof(ReserveData))	;

}
SI32 ReserveData::GetCharPersonID()
{
	return PersonID	;
}
TCHAR* ReserveData::GetCharName()
{
	return m_szCharName	;
}
void ReserveData::SetCharPersonID(SI32 siPersonID ) // ���� ��ƾ�� �ƴѰ��� �������߱�
{
	PersonID	= siPersonID ;
}
void ReserveData::SetCharName(TCHAR* charName)
{
	if ( charName ) StringCchCopy( m_szCharName, sizeof(m_szCharName), charName );
}
//=====================================================================================================
CRacoonDodgeEventMgr::CRacoonDodgeEventMgr()
{
	init()	;
}
CRacoonDodgeEventMgr::~CRacoonDodgeEventMgr()
{

}
void CRacoonDodgeEventMgr::init()
{
	for ( SI32 i = 0; i < MAX_RESERVER_NUM; i++)
	{
		pclReserveList[i].init()	;
	}

	for ( SI32 i = 0; i < EVENT_START_NUM*2; i++)
	{
		pclSelectPersonList[i].init()	;
	}
	
	for ( SI32 i = 0; i < MAX_MONSTER_NUM; i++)
	{
		pclMonsterUnique[i] = 0 ;
	}
	for ( SI32 i = 0; i < MAX_MAKE_MONSTER_NUM; i++)
	{
		MakeMonsterArray[i] = 0 ;
	}
	siWaitTime5Second	=	0;
	siMonsterKindNum	=	0;

	siGameStep			=	EVENTSTEP_WAIT;
	siGameLevel			=	EVENTLEVEL_WAIT;
	
	bLeadData			=	false	;
	siCheckFieldNum		=	0	;
	bCheck_1stMakeMonster	=	false	;

	SetRoundTime(30)	;

	dwCount_30Second	=	0	;
}

void CRacoonDodgeEventMgr::ClearData()
{
	cltServer* pclserver = (cltServer*)pclClient;

	for ( SI32 i = 0; i < EVENT_START_NUM*2; i++)
	{
		// ������ Ŭ���� ���� �޼��� Ŭ�����϶�� ���ش� 
		SI32 siPersonD_InClearData  = pclSelectPersonList[i].GetCharPersonID() ;
		SI32 siID = pclserver->pclCM->GetIDFromPersonID( siPersonD_InClearData)	;
		cltCharServer* pclCharServer = pclserver->pclCM->GetCharServer( siID ) ;	
		if(pclCharServer != NULL )
		{
			cltGameMsgResponse_30Seceond_Clear clinfo( siPersonD_InClearData );
			cltMsg clMsg3(GAMEMSG_RESPONS_RACOONDODGE_EVENT_30SECOND_CLEAR, sizeof(clinfo), (BYTE*)&clinfo);
			pclCharServer->SendNetMsg((sPacketHeader*)&clMsg3);

			cltGameMsgResponse_Round_Clear clinfo2( siPersonD_InClearData );
			cltMsg clMsg2(GAMEMSG_RESPONS_RACOONDODGE_EVENT_ROUNDCOUNT_CLEAR, sizeof(clinfo2), (BYTE*)&clinfo2);
			pclCharServer->SendNetMsg((sPacketHeader*)&clMsg2);
		}
		pclSelectPersonList[i].init()	;
	}
	for ( SI32 i = 0; i < MAX_MAKE_MONSTER_NUM; i++)
	{
		MakeMonsterArray[i] = 0 ;
	}
	siWaitTime5Second	=	0;
	siGameStep			=	EVENTSTEP_WAIT;
	siGameLevel			=	EVENTLEVEL_WAIT;

	siCheckFieldNum		=	0	;
	bCheck_1stMakeMonster	=	false	;
	dwCount_30Second		=	0	;
}

void CRacoonDodgeEventMgr::Action()
{
	cltServer* pclserver = (cltServer*)pclClient;

	if ( true == pclClient->IsCountrySwitch( Switch_10MonthEvent_RacoonDodge ) )
	{
		if(pclClient->pclEventTimeManager->InEventTime("RaccoonDodge", &pclserver->sTime) == false )	return	;

		if(bLeadData	==	false	)
		{
			// �ѹ��� �ε��ϸ�ȴ�.
			LoadRocFile();			// �ʵ� ��ǥ	
			LoadMonsterKindFile();	// ���� ī�ε�
			LoadMonsterInfoSetFile();// ��׷��ú� , ���� ���ǵ� ������
			bLeadData	=	true	;
		}
		switch ( siGameStep )
		{
		case EVENTSTEP_WAIT:
			{
				siCheckFieldNum = CheckPlayStageNum()	;
				if ( siCheckFieldNum < RACOONDODGEEVENT_STAGE_ONE )	return ;
				ChangeStep(EVENTSTEP_MAKE_PLAYUSERLIST)	;
			}break	;
		case EVENTSTEP_MAKE_PLAYUSERLIST:
			{
				ClearData();
				siCheckFieldNum = CheckPlayStageNum()	;
				if ( siCheckFieldNum >= RACOONDODGEEVENT_STAGE_ONE ) 
				{
					MakeSelectPersonList()	;			// ����Ʈ�� �����.				
					ChangeStep(EVENTSTEP_REQUEST_PLAY_EVENT_NOW)	;
				}
			}break	;
		case EVENTSTEP_REQUEST_PLAY_EVENT_NOW:
			{
				SendMessage_Request_PlayEvent()	;	// ������� ����Ʈ�� ���ؼ� ���� ���θ� �����.
				siWaitTime5Second	=	pclserver->CurrentClock ;
				// ���� �ܰ�� �ѱ�� ���� ���� ���� �ð� ����
				ChangeStep(EVENTSTEP_WAIT_ANSWER)	;
			}break	;
		case EVENTSTEP_WAIT_ANSWER:
			{
				// ���� ���� �ð��� 10�ʰ� �Ѿ� ���� ���� �ܰ�� �ѱ��
				if( (pclserver->CurrentClock - siWaitTime5Second)  > 10000 )  //10�ʴ��
				{
					ChangeStep(EVENTSTEP_GAMESTART)	;
				}				
			}break	;
		case EVENTSTEP_GAMESTART:
			{
				// 5�� ī��Ʈ ����
				Count5Second();
				//���� �� ����ؼ� 
				siWaitTime5Second	=	pclserver->CurrentClock ;
				ChangeStep(EVENTSTEP_WAITTIME)	;	// �̰� �������� �޾����� ���¸� ���� �ϴϱ�. Ŭ�󸶴� �ణ�� ���̰� �ִ�.
			}break	;
		case EVENTSTEP_WAITTIME:
			{
				if( (pclserver->CurrentClock - siWaitTime5Second)  > 10000 )  //10�ʰ� �����µ� ���� ������ ���� ó������ �ѱ��.-�� �н� �ѰŴϱ�
				{
					ClearData();
				}
				// ���⿡�� ��ŸƮ ���� Ÿ���� 5�ʰ� ��ٸ���.
			}break	;
		case EVENTSTEP_PLAY:
			{
				SI32 siTimeStart	=	0	;	// ������ ��ŸƮ �ѽð�
				// �����¿��� ������ �̷�� ����
				// ���� �����߿� ������ ���� ���� Ȯ�� �Ѵ�.
				// �̰� ���°� ����Ʈ �ܰ� �̻� �Ѿ� �������� ��� �Ѵ�.
				if ( GetLevel() > EVENTLEVEL_WAIT ) 
				{
					bool CanPlay = CanPlayEvent()	;
					if ( CanPlay == false )		// �ܰ谡 �Ѿ�� ���� ����� ���̻� �ʵ忡 ��� �÷��̰� �Ұ��� �ҋ�
					{
                        // ���͸� �� �׿� ������
						KillEventMonster();
						ClearData();
					}
				}
				switch( siGameLevel ) 
				{
				case EVENTLEVEL_WAIT :
					{
						// �̹��ܰ迡�� ����
						// ���� �ð��� ���� �Ѵ�.
						dwCount_30Second = pclserver->CurrentClock ;
						// �����ܰ�� �̵�
						ChangeLevel( EVENTLEVEL_LV1 )	;
					}
					break;
				case EVENTLEVEL_LV1:
					{
						DWORD dwRoundTimeLimit = 0	;
						dwRoundTimeLimit = pclserver->CurrentClock - dwCount_30Second;
						if ( bCheck_1stMakeMonster == false )
						{
							Count30Second()	;
							RoundSet()	;

							if ( siCheckFieldNum == RACOONDODGEEVENT_STAGE_TWO  )	// �ΰ����ٰ� ���͸� �����Ѵ� 
							{
								SetMonster( MAKE_MONSTER_NUM_10,RACOONDODGEEVENT_STAGE_FIELD_1ST )	;	// ó������ 10������ ����
								SetMonster( MAKE_MONSTER_NUM_10,RACOONDODGEEVENT_STAGE_FILED_2ND )	;	// ó������ 10������ ����
								bCheck_1stMakeMonster	=true ;
							}
							else if( siCheckFieldNum == RACOONDODGEEVENT_STAGE_ONE )
							{
								SetMonster( MAKE_MONSTER_NUM_10,RACOONDODGEEVENT_STAGE_FIELD_1ST )	;	// ó������ 10������ ����
								bCheck_1stMakeMonster	=true ;
							}
						}
						///------------------------------
						// 30�ʰ� �� ������ ���� �ܰ�� �̵� ��Ų��
						if( dwRoundTimeLimit > dwRoundTime )
						{
							SI32 siNowLevel  = GetLevel()	;
							// ���� �ܰ踦 ���� �ð��� ��� 
							dwCount_3Second	=	pclserver->CurrentClock ;
							dwCount_30Second	=	pclserver->CurrentClock ;
							ChangeLevel(siNowLevel+1)	;

							Count30Second()	;
							RoundSet()	;
						}
					}break	;
				case EVENTLEVEL_LV2:
				case EVENTLEVEL_LV3:
				case EVENTLEVEL_LV4:
				case EVENTLEVEL_LV5:
				case EVENTLEVEL_LV6:
				case EVENTLEVEL_LV7:
				case EVENTLEVEL_LV8:
				case EVENTLEVEL_LV9:
				case EVENTLEVEL_LV10:
					{
						DWORD sitemp_MonsterMakeTermTime = pclserver->CurrentClock	- dwCount_3Second	;
						DWORD sitemp_NextLevelTermTime = pclserver->CurrentClock	- dwCount_30Second	;

						if ( sitemp_MonsterMakeTermTime > MAKEMOSTER_TERM) // 3�� �������� ���� 
						{
							if ( siCheckFieldNum == RACOONDODGEEVENT_STAGE_TWO  )	// �ΰ����ٰ� ���͸� �����Ѵ� 
							{
								SetMonster( MAKE_MONSTER_NUM_1,RACOONDODGEEVENT_STAGE_FIELD_1ST )	;	// ó������ 10������ ����
								SetMonster( MAKE_MONSTER_NUM_1,RACOONDODGEEVENT_STAGE_FILED_2ND )	;	// ó������ 10������ ����
							}
							else if( siCheckFieldNum == RACOONDODGEEVENT_STAGE_ONE )
							{
								SetMonster( MAKE_MONSTER_NUM_1,RACOONDODGEEVENT_STAGE_FIELD_1ST )	;	// ó������ 10������ ����
								dwCount_3Second	=	pclserver->CurrentClock ;
							}
							if ( sitemp_NextLevelTermTime > dwRoundTime ) 
							{
								SI32 siNowLevel  = GetLevel()	;
								if ( siNowLevel == EVENTLEVEL_LV10) 
								{
									dwCount_3Second		=	0 ;
									dwCount_30Second	=	0	;
									siNowLevel	=	EVENTLEVEL_WAIT	;
									ChangeStep(EVENTSTEP_GAMEEND)	;
								}
								else
								{
									// 30�� �����ٰ� �˸���.,
									dwCount_30Second	=	pclserver->CurrentClock ;
									ChangeLevel(siNowLevel+1)	;

									Count30Second()	;
									RoundSet()	;
								}
							}
						}
					}break	;
				}				
			}break	;
		case EVENTSTEP_GAMEEND:
			{
				// ����� ���� ������ �ش�
				// ���� �ʾȿ� �ִ� ���Ǿ����� ��� ���� �Ѵ�.
				KillEventMonster();
				RewardMoney();
				ClearData();
			}break	;
		}
	}
}
bool CRacoonDodgeEventMgr::AddReserveList(SI32 siPersonID)
{
	cltServer* pclserver = (cltServer*)pclClient;

	if(pclClient->pclEventTimeManager->InEventTime("RaccoonDodge", &pclserver->sTime) == false )	return	false ;

	bool bSuccess = false ;
	SI32 SIEmptyindex =	0	;

	SI32 siReservationCharId = pclserver->pclCM->GetIDFromPersonID( siPersonID ) ; 
	cltCharServer* pclReservationCharServer = pclserver->pclCM->GetCharServer( siReservationCharId )	;
	if(pclReservationCharServer == NULL )	return bSuccess	;
	bool bCanReserveList	=	false ;
	bCanReserveList = CanReserveList(siPersonID )	;
	if(bCanReserveList == true  )
	{
		SIEmptyindex = FindEmptyPosiotion()	;

		TCHAR *szCharname = (TCHAR*)pclReservationCharServer->pclCI->clBI.GetName()	;

		pclReserveList[SIEmptyindex].SetCharPersonID(siPersonID)	;
		pclReserveList[SIEmptyindex].SetCharName(szCharname  )	;
		bSuccess = true ;
	}
	else
	{
		// ����
	}
	return bSuccess ;
}
void CRacoonDodgeEventMgr::SendMessage_Request_PlayEvent( )	// �����ڸ� �����ؼ� �޼����� ������.
{
	// ������� ����Ʈ�� ���� 
	cltServer* pclserver = (cltServer*)pclClient;

	for ( SI32 i = 0 ; i< EVENT_START_NUM*MAX_EVENTPLACE ; i++)
	{
		SI32 siPersonID =	0	;
		SI32 siID =			0	;

		siPersonID = pclSelectPersonList[ i ].GetCharPersonID() ;	// ������� ���� ����Ʈ���� personid�� ������
		if ( siPersonID <= 0 )	// ����Ʈ�� ����� ���� ���� ����
		{
			return	;
		}
		siID = pclserver->pclCM->GetIDFromPersonID( siPersonID ) ;	// ���� personid�� ���ؼ� charid�� ã�´�.
		cltCharServer* pclCharServer = pclserver->pclCM->GetCharServer( siID )	;	// �ش� id�� char������ get�Ѵ�.
		if( pclCharServer != NULL )
		{
			// ���� ���İ� Ŭ���̾�Ʈ�� ��Ŷ�� ������ .

			cltGameMsgResponse_Request_PlayEvent clinfo( pclCharServer->pclCI->GetPersonID() );	// �ϴ� �۽����̵�� �س��´�
			cltMsg clMsg(GAMEMSG_RESPONS_RACOONDODGE_EVENT_REQUEST_PLAYEVENT, sizeof(clinfo), (BYTE*)&clinfo);
			pclCharServer->SendNetMsg((sPacketHeader*)&clMsg);
		}
		else
		{
			// �߸��� char ���� �ش� �ɸ��ʹ� ���������� �ʴ�. 
		}
	}
}
// ���� ���� �ִ� �̺�Ʈ ���� ���� 
void CRacoonDodgeEventMgr::ChangeStep( SI32 siStep )
{
	siGameStep	=	siStep	;
}
void CRacoonDodgeEventMgr::ChangeLevel( SI32 siLevel )
{
	if ( siLevel >= EVENTLEVEL_LV10 )	siGameLevel	=	EVENTLEVEL_LV10	;
	siGameLevel	=	siLevel	;
}
//�� �ε����� ã�´� .
SI32 CRacoonDodgeEventMgr::FindEmptyPosiotion()
{
	SI32 siPersonID = 0  ;
	SI32 siEmptyindex = 0 ;

	for ( siEmptyindex = 0 ; siEmptyindex < MAX_RESERVER_NUM; siEmptyindex++)
	{
		siPersonID = pclReserveList[siEmptyindex].GetCharPersonID() ; 
		if ( siPersonID <= 0 )	// ����� ã�Ҵ�~
		{
			return siEmptyindex ;
		}
	}
	return siEmptyindex;
}
void CRacoonDodgeEventMgr::Select_Participated_PersonID( SI32 siPersonID)	//������ ����� ���� ó��
{
	// �ϴ��� : �ش� �۽��� �����ϰ� ok �޼����� ���� �ش� peron�� ã�Ƽ� ������ ���� ��Ų�� ����Ʈ������ ����
	
	SI32 siPersonIndex = FindPersonID_InList( siPersonID)	;	// ���� �ش� ����� ����ִ� �ε���
	// ���� ��Ų��.
	// �̺�Ʈ �ɸ��Ͷ�� ���� �Ѵ�.
	SetEventChar( siPersonID)	;
	// ����Ʈ���� ���� �Ѵ�.

}
SI32 CRacoonDodgeEventMgr::FindPersonID_InList( SI32 siInputPersonID)		// ����Ʈ���� �ش� ����� ã�Ƽ� �ε����� ���� �Ѵ�.
{
	SI32 siEmptyindex = 0	;
	SI32 siTempPersonID	=	0	;

	for ( siEmptyindex ; siEmptyindex < MAX_RESERVER_NUM; siEmptyindex++)
	{
		siTempPersonID = pclReserveList[siEmptyindex].GetCharPersonID() ; 

		if ( siTempPersonID == siInputPersonID ) // �׻���� ����Ʈ�� ��� �ִ����� �˾Ҵ�.
		{
			return siEmptyindex ;
		}
	}
	return siEmptyindex ;    
}
bool CRacoonDodgeEventMgr::SetEventChar( SI32 siPersonID)	// �̺�Ʈ�ɸ��Ͷ�� ���� �Ѵ�.
{
	cltServer* pclserver = (cltServer*)pclClient;
	bool bSuccess = false	;
	
	SI32 siEventCharId = pclserver->pclCM->GetIDFromPersonID( siPersonID )	;
	cltCharServer* pclEventChar = pclserver->pclCM->GetCharServer( siEventCharId )	;
	if( pclEventChar != NULL )
	{
		// �ش� �̺�Ʈ �ɸ��Ϳ��� �� �̺�Ʈ �ɸ��Ͷ�� ���� �Ѵ� .

		bSuccess	=	true	;
	}
	else
	{
	}

	return bSuccess		;

}
void CRacoonDodgeEventMgr::MakeSelectPersonList(void )	// ������ ������� �̾Ƴ��� ����Ʈ�� ����� �� ����Ʈ�� ���ฮ��Ʈ�ʹ� �ٸ���.
{
	bool bValue = false ; 
	SI32 siSelecrSlot = 0	;

	ReserveData			pclReserveList_Temp[MAX_RESERVER_NUM]	;				// ����Ʈ ������ ���ѿ��ฮ��Ʈ
	ZeroMemory( pclReserveList_Temp,sizeof(pclReserveList_Temp))	;			// ���� ����Ʈ �ʱ�ȭ
	SI32 siReserveListNum	=	CountReservePersonNum();

	// �̺�Ʈ ���� �ο��� �������� ����Ʈ ����⸦ �Ѵ�.
	if(siReserveListNum >= EVENT_START_NUM)	// �����ڶ� 5�� �̻��̸� ���� 5���� �A��.
	{
		SI32 siValue  = siReserveListNum / EVENT_START_NUM	;

		if ( siValue > 0 )
		{
			if(siValue >= MAX_EVENTPLACE)	siValue = MAX_EVENTPLACE	;
			for ( siSelecrSlot ; siSelecrSlot < EVENT_START_NUM * siValue ; siSelecrSlot++)
			{
				if ( siSelecrSlot >= EVENT_START_NUM*MAX_EVENTPLACE ) break	;

				pclSelectPersonList[siSelecrSlot].SetCharPersonID( pclReserveList[siSelecrSlot].GetCharPersonID() ) ;
				pclSelectPersonList[siSelecrSlot].SetCharName( pclReserveList[siSelecrSlot].GetCharName() );
				pclReserveList[siSelecrSlot].init()	;	// ������ ����.
			}
			// ����Ʈ���� ��������� ���� �Ѵ�

			for ( SI32 siIndex = 0 ; siIndex <MAX_RESERVER_NUM ; siIndex++) 
			{
				if ( siIndex >= MAX_RESERVER_NUM) break	;

				SI32 siTempIndex = 0 ;
				SI32 siPersonID = pclReserveList[siIndex].GetCharPersonID()	;	
				TCHAR* charName = pclReserveList[siIndex].GetCharName() ;
				if( siPersonID <= 0) continue	;
				if ( siPersonID > 0 ) 
				{
					pclReserveList_Temp[siTempIndex ].SetCharPersonID(siPersonID)	;
					pclReserveList_Temp[siTempIndex ].SetCharName(charName)	;
					pclReserveList[siIndex].init()	;	// �������� �����
				}
			}
			// �� �������� ����Ʈ�� ī�� �Ѵ�.
			for ( SI32 i = 0 ; i <MAX_RESERVER_NUM ; i++) 
			{
				if ( i >= MAX_RESERVER_NUM) break	;
				SI32 siPersonID = pclReserveList_Temp[i].GetCharPersonID();
				if ( siPersonID <= 0 )	break	;	// ������� ���� ���ʿ� ����
				TCHAR* pCharNeme = pclReserveList_Temp[i].GetCharName();
                pclReserveList[i].SetChar(siPersonID,pCharNeme)	;
			}
		}
	}
}

// 5�� �� ���� ī���� �޼��� ����

void CRacoonDodgeEventMgr::Count5Second(void )	// �����ڸ� �����ؼ� �޼����� ������.
{
	// ������� ����Ʈ�� ���� 
	cltServer* pclserver = (cltServer*)pclClient;

	for ( SI32 i = 0 ; i< EVENT_START_NUM*MAX_EVENTPLACE ; i++)
	{
		SI32 siPersonID =	0	;
		SI32 siID =			0	;

		siPersonID = pclSelectPersonList[ i ].GetCharPersonID() ;	// ������� ���� ����Ʈ���� personid�� ������
		if ( siPersonID <= 0 )	// ����Ʈ�� ����� ���� ���� ����
		{
			return	;
		}
		siID = pclserver->pclCM->GetIDFromPersonID( siPersonID ) ;	// ���� personid�� ���ؼ� charid�� ã�´�.

		cltCharServer* pclCharServer = pclserver->pclCM->GetCharServer( siID )	;	// �ش� id�� char������ get�Ѵ�.
		if( pclCharServer != NULL )
		{
			SI32 siMapindex = pclCharServer->GetMapIndex()	;
			if( siMapindex == PLAY_MAP_INDEX_INDODEVENT )// �ش� ���ε����� �ְ� 
			{
				cltMapCommon* pclmap = pclClient->pclMapManager->GetMapPointer(siMapindex)	;

				if(pclmap != NULL)
				{
					SI32 siColl = pclmap->CalcCollInfo( pclCharServer->GetX(), pclCharServer->GetY())	;
					if( siColl & BLOCK_EVENT1 || siColl & BLOCK_EVENT4 )	// 4�� �̺�Ÿ Ÿ���� ��� ������.
					{
						// 5��ī��Ʈ ���� �޼��� 
						cltGameMsgResponse_Remain5Seceond clinfo( pclCharServer->pclCI->GetPersonID() );	// �ϴ� �۽����̵�� �س��´�
						cltMsg clMsg(GAMEMSG_RESPONS_RACOONDODGE_EVENT_WAIT5SECOND, sizeof(clinfo), (BYTE*)&clinfo);
						pclCharServer->SendNetMsg((sPacketHeader*)&clMsg);
					}
				}
			}
		}
		else
		{
			// �߸��� char ���� �ش� �ɸ��ʹ� ���������� �ʴ�. 
		}
	}
}
SI32 CRacoonDodgeEventMgr::GetStep(void )	// �Ŵ��� �׼��� ���� ���¸� ������ �´�
{
	return siGameStep	;
}
SI32 CRacoonDodgeEventMgr::GetLevel(void )	// ������ ���෹���� ������ �´�
{
	return siGameLevel	;
}
void CRacoonDodgeEventMgr::WarpGameSpace(SI32 PersonID )	// �ش� ������ ���� �Ѵ�.
{
	// ������� ����Ʈ�� ���� 
	cltServer* pclserver = (cltServer*)pclClient;

	for ( SI32 i = 0 ; i< EVENT_START_NUM*MAX_EVENTPLACE ; i++)
	{
		SI32 siPersonID =	0	;
		SI32 siID =			0	;

		siPersonID = pclSelectPersonList[ i ].GetCharPersonID() ;	// ������� ���� ����Ʈ���� personid�� ������
		if ( PersonID == siPersonID )
		{
			if ( i < EVENT_START_NUM )
			{
				cltWarpInfo clWarpInfo(1, 0, true, false, 117, 102, -1, -1);
				clWarpInfo.uiMapIndex = PLAY_MAP_INDEX_INDODEVENT;

				SI32 siCharId = pclClient->pclCM->GetIDFromPersonID( siPersonID ) ;

				cltCharServer* pclchar = pclClient->pclCM->GetCharServer(siCharId);
				if (pclchar == NULL )	return	;
				pclchar->SetWarpInfo(&clWarpInfo, 2200);	// �ش� ��ġ�� ���� �Ѵ� .
				pclchar->Warp()	;
			}
			else
			{
				cltWarpInfo clWarpInfo(1, 0, true, false, 54, 101, -1, -1);
				clWarpInfo.uiMapIndex = PLAY_MAP_INDEX_INDODEVENT;

				SI32 siCharId = pclClient->pclCM->GetIDFromPersonID( siPersonID ) ;

				cltCharServer* pclchar = pclClient->pclCM->GetCharServer(siCharId);
				if (pclchar == NULL )	return	;
				pclchar->SetWarpInfo(&clWarpInfo, 2200);	// �ش� ��ġ�� ���� �Ѵ� .
				pclchar->Warp()	;
			}
		}
	}
}
void CRacoonDodgeEventMgr::SendReserveList(SI32 siPersonID)
{
	cltServer* pclserver = (cltServer*)pclClient;

	SI32 sicharID = pclserver->pclCM->GetIDFromPersonID( siPersonID )	;
	cltCharServer* pclCharServer = pclserver->pclCM->GetCharServer( sicharID )	;

	if( pclCharServer == NULL  )	return	;
	// ���� ���ฮ��Ʈ�� Ŭ���̾�Ʈ�� �����ش� 
	// ������ŭ �����
	ReserveData	clInfo[MAX_RESERVER_SHOW_NUM];

	for ( SI32 i = 0 ; i < MAX_RESERVER_SHOW_NUM; i++)
	{
		if( i >= MAX_RESERVER_SHOW_NUM )	break	;
		clInfo[i].SetCharName( pclReserveList[i].GetCharName() )	;
		clInfo[i].SetCharPersonID( pclReserveList[i].GetCharPersonID())	;
	}
	// ���� ���� ����Ʈ�� �����ش�
	cltGameMsgResponse_ReserveList clinfo( clInfo );
	cltMsg clMsg(GAMEMSG_RESPONS_RACOONDODGE_EVENT_RESERVATION, sizeof(clinfo), (BYTE*)&clinfo);
	pclCharServer->SendNetMsg((sPacketHeader*)&clMsg);
	
}

//siMake_Monster_Num ��ŭ ���͸� ��ǥ�� ����� ����.
void CRacoonDodgeEventMgr::SetMonster( SI32 siMake_Monster_Num, SI32 siStageindex)
{
	cltServer* pclserver = (cltServer*)pclClient;
	SI32 siMonsterKind	=	0	;	// �̾Ƴ� ���� ī�ε�
	SI32 siRocX	=	0	;	// ���ؿ� �Ǵ� X��ǥ
	SI32 siRocY	=	0	;	// ���ؿ� �Ǵ� Y��ǥ
	SI32 siX	=	0	;	// ���� ������ X��ǥ
	SI32 siY	=	0	;	// ���� ������ Y��ǥ
	SI32 siMapIndex		=	PLAY_MAP_INDEX_INDODEVENT	;	// ����߸� ���ε���
	SI32 silevel		=	0	;	// ���� ����
	SI32 siMakeCount	=	0	;	// ���� ����  ����
	SI32 siEnergy		=	10000;
	SI32 siLevel		=	10	;


	for (siMakeCount; siMakeCount <siMake_Monster_Num; siMakeCount++ )
	{

		SI32 monstermakeindex	=	0	;
		SI32 ramdomrocIndex = rand() % MAX_MONSTER_ROC	;

		if( siStageindex >= MAX_STAGE_NUM )		return	;
		siRocX = pclRocList[siStageindex].GetRocX( ramdomrocIndex)	;
		siRocY = pclRocList[siStageindex].GetRocY( ramdomrocIndex)	;

		if ( siRocX == 0 || siRocY == 0 ) 
		{
			if( siStageindex >= MAX_STAGE_NUM )		return	;
			siRocX = pclRocList[siStageindex].GetRocX( 0)	;
			siRocY = pclRocList[siStageindex].GetRocY( 0)	;
		}

		SI32 siKindSlot  = rand() % siMonsterKindNum	;
		siMonsterKind	=	pclMonsterUnique[siKindSlot];	// �迭�� ���� ���� ī�ε带 ������ �´�

		cltMapCommon* pclmap = pclserver->pclMapManager->GetMapPointer( siMapIndex )	;	// ��������
		if(pclmap != NULL)
		{
			cltInnerStatusInfo clinnerstatus;
			clinnerstatus.clEnemyType.Set(ENEMYTYPE_ALLPC, 0);

			cltIdentity clIdentity;
			clIdentity.MakeRaccoonDodgeEvent(IDENTITY_RACOONDODGE_EVENT);

			SI32 id = pclserver->SetNPCChar( siMonsterKind, 
				VILLAGE_NONE, 
				&clIdentity, 
				siLevel, 
				siEnergy, 
				siRocX, 
				siRocY, 
				siMapIndex, 
				NPCITEMMODE_NONE, 
				&clinnerstatus );
			//RememberEventMonster(id);
			SetAggressiveNMoveSpeed(id)	;
		}
		
	}
}
void CRacoonDodgeEventMgr::LoadRocFile()
{
		NDataLoader	dataloader;
		BOOL bLoadFile=FALSE;
	
		if( pclClient->IsWhereServiceArea( ConstSwitch_TextEncryption ) )
		{
			bLoadFile = dataloader.LoadDataFromCryptFile( TEXT("Data/RacoonDodge_RocInfo.txt") );
		}
		else
		{
			bLoadFile = dataloader.LoadDataFromFile( TEXT("Data/RacoonDodge_RocInfo.txt") );
		}
		if (!bLoadFile)
		{
			MsgBox( TEXT("Not LoadFromFile RacoonDodge_RocInfo.txt"),TEXT("Error"));
			return;
		}
		// ������ ���� ���� ������ 3����
		SI32 siStageIndex_Resource	=	0	;	// ���ҽ����� �޾� ���� �������� �ε���
		SI32 siMapRoc_X_Resource		=	0	;	// ���ҽ����� �޾� ���� �������� ���� ���� ��ȯ�� ��ǥ 
		SI32 siMapRoc_Y_Resource		=	0	;

		NDataTypeInfo pDataTypeInfo[] =
		{
			NDATA_INT32,	&siStageIndex_Resource,	4,
			NDATA_INT32,	&siMapRoc_X_Resource,	4,
			NDATA_INT32,	&siMapRoc_Y_Resource,	4,
			0,0,0
		};	
		dataloader.RegDataType( pDataTypeInfo );

		SI32 siStageIndex_In_DataArray	=	0	;	// �����͵� �ȿ� ��� ��ǥ���� ���� �ϱ� ���� ������ �ִ� �������� �ε���
		SI32 ArrayIndex_In_Data			=	0	;	// ��ǥ���� ������ �ִµ����� array�ε���
		SI32 RocCount					=	0	;

		SI32 siStageIndex				=	0	;	// �������� �ε��� 
		while (!dataloader.IsEndOfData() )	// ������ �ٽ� �ϴ��� 
		{
			if ( dataloader.ReadData( true ) )
			{
				// �ش� ��ǥ�� �����������̴´�. 
				if( siStageIndex >= MAX_STAGE_NUM )		return	;
				siStageIndex_In_DataArray	=	pclRocList[siStageIndex].GetStage(ArrayIndex_In_Data)	;

				// �������� �ε����� 0�̸� ù��° �������� �׸��� 
				if ( siStageIndex_In_DataArray == 0 && siStageIndex_In_DataArray != siStageIndex_Resource)
				{
					// ���� ó�� 
					if ( siStageIndex >= MAX_STAGE_NUM)	break	;
					if ( ArrayIndex_In_Data >= MAX_MONSTER_ROC)	break	;

					pclRocList[siStageIndex].SetRoc( siStageIndex_Resource ,siMapRoc_X_Resource,siMapRoc_Y_Resource)	;
				}
				else if ( siStageIndex_Resource == siStageIndex_In_DataArray )	// �̰� ���� �������� �ε��� �϶� ���� ������ �ε����� �ִ´�
				{
					// ���� ó�� 
					if ( siStageIndex >= MAX_STAGE_NUM)	break	;
					if ( ArrayIndex_In_Data >= MAX_MONSTER_ROC)	break	;
					// �� �ִ� �ֶ� ���� �ε����� �׷� ���� ���������� �� �ڷ� �ִ´�
					pclRocList[siStageIndex].SetRoc( siStageIndex_Resource,siMapRoc_X_Resource,siMapRoc_Y_Resource)	;
				}
				else if( siStageIndex_Resource != siStageIndex_In_DataArray )	// ���� �������� �϶� ���⿡�� ������ �ε�������� �̷��͵� �ʱ�ȭ �ؼ� �־��ش�
				{
					// ���� ó�� 
					if ( siStageIndex >= MAX_STAGE_NUM)	break	;
					if ( ArrayIndex_In_Data >= MAX_MONSTER_ROC)	break	;
					// �� �ִ� �ֶ� ���� �ε����� �׷� ���� ���������� �� �ڷ� �ִ´�
					siStageIndex++;
					pclRocList[siStageIndex].SetRoc( siStageIndex_Resource,siMapRoc_X_Resource,siMapRoc_Y_Resource)	;

				}
			}
		}	

}

void CRacoonDodgeEventMgr::LoadMonsterKindFile()
{
	NDataLoader	dataloader;
	BOOL bLoadFile=FALSE;

	if( pclClient->IsWhereServiceArea( ConstSwitch_TextEncryption ) )
	{
		bLoadFile = dataloader.LoadDataFromCryptFile( TEXT("Data/RacoonDodge_MonsterKindInfo.txt") );
	}
	else
	{
		bLoadFile = dataloader.LoadDataFromFile( TEXT("Data/RacoonDodge_MonsterKindInfo.txt") );
	}
	if (!bLoadFile)
	{
		MsgBox( TEXT("Not LoadFromFile RacoonDodge_MonsterKindInfo.txt"),TEXT("Error"));
		return;
	}
	// ������ ���� ���� ������ 3����
	TCHAR szMonsterKind[64]			=	TEXT("");

	NDataTypeInfo pDataTypeInfo[] =
	{
		NDATA_MBSTRING,	&szMonsterKind,	64,
			0,0,0
	};	
	dataloader.RegDataType( pDataTypeInfo );
	SI32 siArrayindex = 0 ;

	while (!dataloader.IsEndOfData() )	// ������ �ٽ� �ϴ��� 
	{
		if ( dataloader.ReadData( true ) )
		{
			if ( siArrayindex >= MAX_MONSTER_NUM )	break	;
			SI32 siMonsterUnique =	pclClient->GetUniqueFromHash(szMonsterKind);
			if(siMonsterUnique <= 0 )	continue	;
			pclMonsterUnique[siArrayindex]	=	siMonsterUnique	;
			siArrayindex++;
			siMonsterKindNum++;
		}
	}	

}
void CRacoonDodgeEventMgr::LoadMonsterInfoSetFile()
{
	NDataLoader	dataloader;
	BOOL bLoadFile=FALSE;

	if( pclClient->IsWhereServiceArea( ConstSwitch_TextEncryption ) )
	{
		bLoadFile = dataloader.LoadDataFromCryptFile( TEXT("Data/RacoonDodge_MonsterInfoSetInfoo.txt") );
	}
	else
	{
		bLoadFile = dataloader.LoadDataFromFile( TEXT("Data/RacoonDodge_MonsterInfoSetInfoo.txt") );
	}
	if (!bLoadFile)
	{
		MsgBox( TEXT("Not LoadFromFile RacoonDodge_MonsterInfoSetInfo.txt"),TEXT("Error"));
		return;
	}
	// ������ ���� ���� ������ 3����
	
	SI32 siGameLevel	=	0	;			// ���� ���� ����

	SI32 siAggressiveGap	=	0	;			// ���� ��׷��ú� ��
	SI32 siAggresiveAddPoint	=	0	;		// ���� ��׷��ú� ������

	SI32 siMoveSpeedGap	=	0	;			// ���� ���� ���ǵ� ��
	SI32 siMoveSpeedAddPoint	=	0	;	// ���� ���� ���ǵ� ������
	

	NDataTypeInfo pDataTypeInfo[] =
	{
		NDATA_INT32,	&siGameLevel,	4,

			NDATA_INT32,	&siAggressiveGap,	4,
			NDATA_INT32,	&siAggresiveAddPoint,	4,

			NDATA_INT32,	&siMoveSpeedGap,	4,
			NDATA_INT32,	&siMoveSpeedAddPoint,	4,
			0,0,0
	};	
	dataloader.RegDataType( pDataTypeInfo );
	SI32 siArrayindex = 0 ;

	while (!dataloader.IsEndOfData() )	// ������ �ٽ� �ϴ��� 
	{
		if ( dataloader.ReadData( true ) )
		{
			if (siArrayindex >= MAX_MONSTER_NUM)	break	;
			pclMonsterInfo_Level[siArrayindex].SetData( siGameLevel , siAggressiveGap,siAggresiveAddPoint,siMoveSpeedGap,siMoveSpeedAddPoint	);
			siArrayindex++;
		}
	}	

}
SI32 CRacoonDodgeEventMgr::CheckPlayStageNum()
{
	SI32 siReserveListNum	=	CountReservePersonNum();
	if(siReserveListNum > 0 )
	{
		if( siReserveListNum >= 10)	// ����� �Ѽ��� 10���� �Ѿ� ���� 
		{
			return RACOONDODGEEVENT_STAGE_TWO	;
		}
		else if (siReserveListNum >= 5 ) 
		{
			return RACOONDODGEEVENT_STAGE_ONE	;
		}
		else
		{
			return RACOONDODGEEVENT_STAGE_NONE	;
		}
	}
	return RACOONDODGEEVENT_STAGE_NONE	;
}
bool CRacoonDodgeEventMgr::CanReserveList(SI32 siPersonID)
{
	cltServer* pclserver = (cltServer*)pclClient;


	bool bResult = true	;
	SI32 siReservationCharId = pclserver->pclCM->GetIDFromPersonID( siPersonID ) ; 
	cltCharServer* pclReservationCharServer = pclserver->pclCM->GetCharServer( siReservationCharId )	;
	if(pclReservationCharServer == NULL )	return false ;

	// �̹� ����Ʈ�� �ִ��� Ȯ��
	// �� á��.
	SI32 siReserveListNum	=	CountReservePersonNum()	;

	if(siReserveListNum >= MAX_RESERVER_NUM )
	{
		pclserver->SendServerResponseMsg( 0, SRVAL_RACOONDODGEEVENT_NOTEMPTYLISTPLACE , 0, 0, pclReservationCharServer->GetCharUnique() );	// ���ڸ��� ����
		bResult=  false	;
	}

	for ( SI32 i = 0 ; i < MAX_RESERVER_NUM; i++ )
	{
		if(pclReserveList[i].GetCharPersonID() == siPersonID)
		{
			pclserver->SendServerResponseMsg( 0, SRVAL_RACOONDODGEEVENT_RESERVEPERSON, 0, 0, pclReservationCharServer->GetCharUnique() );// �̹� ��û �Ͽ���.
			bResult=  false	;
			break	;
		}
	}
	// �̹� ����忡 �ִ���Ȯ��

	SI32 siMapindex = pclReservationCharServer->GetMapIndex() ;
	if( siMapindex == PLAY_MAP_INDEX_INDODEVENT )// �ش� ���ε����� �ְ� 
	{
		cltMapCommon* pclmap = pclClient->pclMapManager->GetMapPointer(siMapindex)	;

		if(pclmap != NULL)
		{
			SI32 siColl = pclmap->CalcCollInfo( pclReservationCharServer->GetX(), pclReservationCharServer->GetY())	;
			if( siColl & BLOCK_EVENT1 || siColl & BLOCK_EVENT4 )	// 4�� �̺�Ÿ Ÿ
			{
				// �̹� ����忡 �ִ�
				pclserver->SendServerResponseMsg( 0, SRVAL_RACOONDODGEEVENT_CANNOTRESERVE_INPLAY, 0, 0, pclReservationCharServer->GetCharUnique() );// �̹� ��û �Ͽ���.
				bResult=  false	;
			}
		}

	}

	return bResult ;
}
void CRacoonDodgeEventMgr::SetAggressiveNMoveSpeed( SI32 siCharID )
{
	cltServer* pclserver = (cltServer*)pclClient;

	cltCharServer* pclCharerver = pclserver->pclCM->GetCharServer(siCharID)	;
	if( pclCharerver != NULL  )
	{
		// ���ӷ����� ���� ��׷��ú�� ���� ���ǵ� ���� 
		SI32 siGameLevel = GetLevel()	;

		SI32 Aggressive = 0	;
		SI32 Movespeed = 0	;


		SI32 siAgg_AddValue	=	0	;
		SI32 siAgg_Value	=	0	;

		SI32 siMoveSpeed_Value	=	0;
		SI32 siMoveSpeed_AddValue	=	0;

		for ( SI32 siSLot = 0 ; siSLot< MAX_PLAY_LEVEL; siSLot++)
		{
			if ( pclMonsterInfo_Level[siSLot].GetSiGameLevel() == siGameLevel ) 
			{
				siAgg_Value = pclMonsterInfo_Level[siSLot].GetAGV_Value() ;
				siAgg_AddValue = pclMonsterInfo_Level[siSLot].GetAGV_AddValue() ;
				siMoveSpeed_AddValue = pclMonsterInfo_Level[siSLot].GetMoveSpeed_Value() ;
				siMoveSpeed_Value = pclMonsterInfo_Level[siSLot].GetMoveSpeed_AddValue() ;
			}
		}
		if( siAgg_Value > 0 &&  siAgg_AddValue > 0 &&  siMoveSpeed_Value > 0 &&  siMoveSpeed_AddValue > 0 )
		{
			Aggressive = rand() % siAgg_Value	+	siAgg_AddValue	;
			Movespeed = rand() % siMoveSpeed_Value	+	siMoveSpeed_AddValue	;
			if ( Aggressive >= MAX_AGGRESSIVE ){				Aggressive =  MAX_AGGRESSIVE ;			}
			if ( Movespeed >= MAX_MOVESPEED ){				Movespeed =  MAX_MOVESPEED ;			}
			if ( Aggressive > 0 && Movespeed > 0 )
			{
				if(pclCharerver->clIdentity.siIdentity == IDENTITY_RACOONDODGE_EVENT )
				{
					pclCharerver->pclKI->siAggressive	= Aggressive	;
					pclCharerver->pclKI->siMoveSpeed	= Movespeed		;
				}
			}		
		}

		pclCharerver->dwTimerClock = pclserver->CurrentClock;
	}
}

void CRacoonDodgeEventMgr::Count30Second(void )	// �����ڸ� �����ؼ� �޼����� ������.
{
	// ������� ����Ʈ�� ���� 
	cltServer* pclserver = (cltServer*)pclClient;

	for ( SI32 i = 0 ; i< EVENT_START_NUM*MAX_EVENTPLACE ; i++)
	{
		SI32 siPersonID =	0	;
		SI32 siID =			0	;

		siPersonID = pclSelectPersonList[ i ].GetCharPersonID() ;	// ������� ���� ����Ʈ���� personid�� ������
		if ( siPersonID <= 0 )	//����Ʈ�� �������  �н�
		{
			continue	;
		}
		siID = pclserver->pclCM->GetIDFromPersonID( siPersonID ) ;	// ���� personid�� ���ؼ� charid�� ã�´�.

		cltCharServer* pclCharServer = pclserver->pclCM->GetCharServer( siID )	;	// �ش� id�� char������ get�Ѵ�.
		if( pclCharServer != NULL )
		{
			SI32 siMapindex = pclCharServer->GetMapIndex()	;
			if( siMapindex == PLAY_MAP_INDEX_INDODEVENT )// �ش� ���ε����� �ְ� 
			{
				cltMapCommon* pclmap = pclClient->pclMapManager->GetMapPointer(siMapindex)	;

				if(pclmap != NULL)
				{
					SI32 siColl = pclmap->CalcCollInfo( pclCharServer->GetX(), pclCharServer->GetY())	;
					if( siColl & BLOCK_EVENT1 || siColl & BLOCK_EVENT4 )	// 4�� �̺�Ÿ Ÿ���� ��� ������.
					{
						cltGameMsgResponse_30Seceond clinfo( pclCharServer->pclCI->GetPersonID(),dwRoundTime );
						cltMsg clMsg(GAMEMSG_RESPONS_RACOONDODGE_EVENT_30SECOND, sizeof(clinfo), (BYTE*)&clinfo);
						pclCharServer->SendNetMsg((sPacketHeader*)&clMsg);
					}
				}
			}
		}
		else
		{
			// �߸��� char ���� �ش� �ɸ��ʹ� ���������� �ʴ�. 
		}
	}
}
// ���̻� ����̾����� 
bool CRacoonDodgeEventMgr::CanPlayEvent(void )	// �����ڸ� �����ؼ� �޼����� ������.
{
	// ������� ����Ʈ�� ���� 
	cltServer* pclserver = (cltServer*)pclClient;

	SI32 siPlayGameNumNow	=	0	;	// ���� ��׷��ú� �߰� ������

	for ( SI32 i = 0 ; i< EVENT_START_NUM*MAX_EVENTPLACE ; i++)
	{
		SI32 siPersonID =	0	;
		SI32 siID =			0	;

		siPersonID = pclSelectPersonList[ i ].GetCharPersonID() ;	// ������� ���� ����Ʈ���� personid�� ������
		siID = pclserver->pclCM->GetIDFromPersonID( siPersonID ) ;	// ���� personid�� ���ؼ� charid�� ã�´�.

		cltCharServer* pclCharServer = pclserver->pclCM->GetCharServer( siID )	;	// �ش� id�� char������ get�Ѵ�.
		if( pclCharServer != NULL )
		{
			SI32 siMapindex = pclCharServer->GetMapIndex()	;
			if( siMapindex == PLAY_MAP_INDEX_INDODEVENT )// �ش� ���ε����� �ְ� 
			{
				cltMapCommon* pclmap = pclClient->pclMapManager->GetMapPointer(siMapindex)	;

				if(pclmap != NULL)
				{
					SI32 siColl = pclmap->CalcCollInfo( pclCharServer->GetX(), pclCharServer->GetY())	;
					if( siColl & BLOCK_EVENT1 || siColl & BLOCK_EVENT4 )	// 4�� �̺�Ÿ Ÿ���� ��� ������.
					{
						if( pclserver->pclCM->IsAlive(siID) == TRUE )
						{
							// �ش� �ɸ��Ͱ� �÷������̸� ī��Ʈ�� �ø��� .
							siPlayGameNumNow++;
						}
					}
					else
					{
						// ������ �ְ�� ȭ�鿡 ī��Ʈ�� ����� 
						cltGameMsgResponse_30Seceond_Clear clinfo( siPersonID );
						cltMsg clMsg3(GAMEMSG_RESPONS_RACOONDODGE_EVENT_30SECOND_CLEAR, sizeof(clinfo), (BYTE*)&clinfo);
						pclCharServer->SendNetMsg((sPacketHeader*)&clMsg3);

						cltGameMsgResponse_Round_Clear clinfo2( siPersonID );
						cltMsg clMsg2(GAMEMSG_RESPONS_RACOONDODGE_EVENT_ROUNDCOUNT_CLEAR, sizeof(clinfo2), (BYTE*)&clinfo2);
						pclCharServer->SendNetMsg((sPacketHeader*)&clMsg2);

						// �ְ� ����Ʈ���� ���� ���� 
						pclSelectPersonList[ i ].init()	;
					}
				}
			}
		}
		else
		{
			// �߸��� char ���� �ش� �ɸ��ʹ� ���������� �ʴ�. 
		}
	}
	if ( siPlayGameNumNow <= 0 ) 
	{
		// ���� ��Ų��

		return false	;
	}
	else
	{
		return true	;
	}
}
void CRacoonDodgeEventMgr::KillEventMonster(void )	// �̺�Ʈ ���͸� �� ���δ�.
{
	cltServer* pclserver = (cltServer*)pclClient;

	for ( SI32 siIndex = 0; siIndex <MAX_MAKE_MONSTER_NUM; siIndex++ ) 
	{
		SI32 siMonsterID = MakeMonsterArray[siIndex]	;
		// ���̵� ������ 0�� ä�� ����Ʈ�ּ� ����� .
		MakeMonsterArray[siIndex] = 0 ;
		cltCharServer* pclMonster = pclClient->pclCM->GetCharServer( siMonsterID );
		if ( pclMonster != NULL ) 
		{
			if(IDENTITY_RACOONDODGE_EVENT == pclMonster->clIdentity.siIdentity)
			{
				SI32 siMapindex = pclMonster->GetMapIndex()	;

				if( siMapindex == PLAY_MAP_INDEX_INDODEVENT )// �ش� ���ε����� �ְ� 
				{
					cltMapCommon* pclmap = pclClient->pclMapManager->GetMapPointer(siMapindex)	;

					if(pclmap != NULL)
					{
						SI32 siColl = pclmap->CalcCollInfo( pclMonster->GetX(), pclMonster->GetY())	;
						if( siColl & BLOCK_EVENT1 || siColl & BLOCK_EVENT4 )	// 4�� �̺�Ÿ Ÿ���� ��� ������.
						{
							pclMonster->SetLife(0)	;

						}
					}
				}
			
			}			
		}
	}
}
//void CRacoonDodgeEventMgr::RememberEventMonster(SI32 siID)
//{
//	for ( SI32 monstermakeindex = 0 ; monstermakeindex< MAX_MAKE_MONSTER_NUM; monstermakeindex++) 
//	{
//		if ( MakeMonsterArray[monstermakeindex] == 0 ) 
//		{
//			MakeMonsterArray[monstermakeindex] = siID	;
//			return ;
//		}
//	}
//}

//������ ���� 
void CRacoonDodgeEventMgr::RewardMoney(void)
{

	// ������� ����Ʈ�� ���� 
	cltServer* pclserver = (cltServer*)pclClient;

	// ������� ���� �Ѵ� .
	GMONEY gCost	=	(pclClient->pclItemManager->clItemStatistic.siNPCPriceRate*1000)/100	;	// npcrate�� ���� �ڽ�Ʈ
	GMONEY gReward = gCost * REWARDPOINT	;


	for ( SI32 i = 0 ; i< EVENT_START_NUM*MAX_EVENTPLACE ; i++)
	{
		SI32 siPersonID =	0	;
		SI32 siID =			0	;

		siPersonID = pclSelectPersonList[ i ].GetCharPersonID() ;	// ������� ���� ����Ʈ���� personid�� ������
		siID = pclserver->pclCM->GetIDFromPersonID( siPersonID ) ;	// ���� personid�� ���ؼ� charid�� ã�´�.

		cltCharServer* pclCharServer = pclserver->pclCM->GetCharServer( siID )	;	// �ش� id�� char������ get�Ѵ�.
		if( pclCharServer != NULL )
		{
			SI32 siMapindex = pclCharServer->GetMapIndex()	;
			if( siMapindex == PLAY_MAP_INDEX_INDODEVENT )// �ش� ���ε����� �ְ� 
			{
				cltMapCommon* pclmap = pclClient->pclMapManager->GetMapPointer(siMapindex)	;

				if(pclmap != NULL)
				{
					SI32 siColl = pclmap->CalcCollInfo( pclCharServer->GetX(), pclCharServer->GetY())	;
					if( siColl & BLOCK_EVENT1 || siColl & BLOCK_EVENT4 )	// 4�� �̺�Ÿ Ÿ���� ��� ������.
					{
						if( pclserver->pclCM->IsAlive(siID) == false ) 
						{
							continue	;
						}
						else
						{
							sDBRequest_ChangeMoney clMsg(pclCharServer->GetID(), pclCharServer->pclCI->GetPersonID(), CHANGE_MONEY_REASON_RACOONDODGE_REWARD, gReward);
							pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
							pclserver->SendServerResponseCharMsg2( 0, SRVAL_RETURN_RACOONDODGEEVENT_CLEAR, SI64ToString(gReward), NULL, NULL, pclCharServer->GetCharUnique() );		

							cltWarpInfo clWarpInfo(1, 0, true, false, 91, 135, -1, -1);
							clWarpInfo.uiMapIndex = PLAY_MAP_INDEX_INDODEVENT;
							pclCharServer->SetWarpInfo(&clWarpInfo, 2200);	// �ش� ��ġ�� ���� �Ѵ� .
							pclCharServer->Warp()	;

							if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog))     
							{
								// [�α��߰� : �ռ��� 2009. 8. 24] // �����̺�Ʈ ������ ���� 
								// Ÿ�� personID 
								pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_RACCOONDODGE_EVENT, LOGCOMMAND_INDEX_PVP_RACCOONDODGE_EVENT_REWARD, 
									0, pclCharServer,NULL ,0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
									gReward, 0, 0, 0, 0, NULL, NULL);	// para1 : ���
							}
						}
					}
				}
			}
		}
	}
}

void CRacoonDodgeEventMgr::SetRoundTime(SI32 siSecond)
{
	dwRoundTime = siSecond *1000	;
}

void CRacoonDodgeEventMgr::RoundSet(void )	// �����ڸ� �����ؼ� �޼����� ������.
{
	// ������� ����Ʈ�� ���� 
	cltServer* pclserver = (cltServer*)pclClient;

	for ( SI32 i = 0 ; i< EVENT_START_NUM*MAX_EVENTPLACE ; i++)
	{
		SI32 siPersonID =	0	;
		SI32 siID =			0	;

		siPersonID = pclSelectPersonList[ i ].GetCharPersonID() ;	// ������� ���� ����Ʈ���� personid�� ������
		if ( siPersonID <= 0 )	// ����Ʈ�� ����� ���� ���� ���
		{
			continue	;
		}
		siID = pclserver->pclCM->GetIDFromPersonID( siPersonID ) ;	// ���� personid�� ���ؼ� charid�� ã�´�.

		cltCharServer* pclCharServer = pclserver->pclCM->GetCharServer( siID )	;	// �ش� id�� char������ get�Ѵ�.
		if( pclCharServer != NULL )
		{
			SI32 siMapindex = pclCharServer->GetMapIndex()	;
			if( siMapindex == PLAY_MAP_INDEX_INDODEVENT )// �ش� ���ε����� �ְ� 
			{
				cltMapCommon* pclmap = pclClient->pclMapManager->GetMapPointer(siMapindex)	;

				if(pclmap != NULL)
				{
					SI32 siColl = pclmap->CalcCollInfo( pclCharServer->GetX(), pclCharServer->GetY())	;
					if( siColl & BLOCK_EVENT1 || siColl & BLOCK_EVENT4 )	// 4�� �̺�Ÿ Ÿ���� ��� ������.
					{

						SI32 siGameRound = GetLevel()	;
						switch ( siGameRound )
						{
						case EVENTLEVEL_LV1:
						case EVENTLEVEL_LV2:
						case EVENTLEVEL_LV3:
						case EVENTLEVEL_LV4:
						case EVENTLEVEL_LV5:
						case EVENTLEVEL_LV6:
						case EVENTLEVEL_LV7:
						case EVENTLEVEL_LV8:
						case EVENTLEVEL_LV9:
						case EVENTLEVEL_LV10:
							{
								cltGameMsgResponse_RoundCount clinfo( pclCharServer->pclCI->GetPersonID(),siGameRound-1 );
								cltMsg clMsg(GAMEMSG_RESPONS_RACOONDODGE_EVENT_ROUNDCOUNT, sizeof(clinfo), (BYTE*)&clinfo);
								pclCharServer->SendNetMsg((sPacketHeader*)&clMsg);
							}break;
						default:
							{
								cltGameMsgResponse_RoundCount clinfo( pclCharServer->pclCI->GetPersonID(),-1 );
								cltMsg clMsg(GAMEMSG_RESPONS_RACOONDODGE_EVENT_ROUNDCOUNT, sizeof(clinfo), (BYTE*)&clinfo);
								pclCharServer->SendNetMsg((sPacketHeader*)&clMsg);
							}
							break;
						}
					}
				}
			}
		}
		else
		{
			// �߸��� char ���� �ش� �ɸ��ʹ� ���������� �ʴ�. 
		}
	}
}

SI32 CRacoonDodgeEventMgr::CountReservePersonNum(void )	// �����ڸ� �����ؼ� �޼����� ������.
{
	SI32 siReserveListNum=	0	;
	for ( SI32 siSlotNum = 0 ; siSlotNum < MAX_RESERVER_NUM; siSlotNum++ ) 
	{
		SI32 siReservePersonId = pclReserveList[siSlotNum].GetCharPersonID() ;
		if ( siReservePersonId > 0  ) 
		{
			siReserveListNum++;
		}
	}
	return siReserveListNum	;
}