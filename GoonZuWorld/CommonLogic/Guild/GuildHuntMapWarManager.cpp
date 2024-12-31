#include"GuildHuntMapWarManager.h"

#include "../Common/CommonHeader.h"
#include "../CommonLogic/CommonLogic.h"
#include "../../Server/Server.h"
#include "../../NLib/NUtil.h"
#include "../common/Char/CharServer/Char-Server.h"
#include "../common/Char/CharManager/CharManager.h"
#include "../common/Char/CharCommon/Char-Common.h"

#include "../common/Event/event.h"

#include "../../DBManager/GameDBManager_World/DBMsg-Item.h"
#include "../../CommonLogic/MsgType-Person.h"
#include "../../CommonLogic/MsgRval-Define.h"
#include "MsgType-System.h"

#include "GuildWar.h"
#include "../CommonLogic/MsgType-Guild.h"
#include "../../DBManager/GameDBManager_World/DBMsg-Guild.h"

#include "../Client/MarkManager/MarkManager.h"
#include "../Server/ServerEvent/ServerEvent_Manager.h"

cltGuildHuntMapWarManager::cltGuildHuntMapWarManager()
{
	init();
}
cltGuildHuntMapWarManager::~cltGuildHuntMapWarManager()
{

}
void cltGuildHuntMapWarManager::init()
{
	for ( SI32 i = 0 ; i < MAX_GUILD_NUM ; i++)
	{
		pclGuildList[i].Init();
		//pclTempGuildList[i].Init();
	}
	TempMatchingListClear();
	MatchingListClear();
	ListClear();
	siListCount	=	0	;
	siStatus	=	EMPTY_MATCHING_LIST;
	ClearStatus();
	for ( SI32 siSlot = 0 ;siSlot<MAX_GUILDHUNTWAR_MAPNUM;siSlot++ ) 
	{
		for (SI32 siMember = 0; siMember<MAX_GUILD_MEMBER_NUM; siMember++) 
		{
			m_HomePersonDeadClock[siSlot][siMember]	=	0	;
			m_AwayPersonDeadClock[siSlot][siMember]	=	0	;
		}
	}
}
// ��û ����Ʈ�� �ִ´�.
SI32 cltGuildHuntMapWarManager::add( SI32 siGuildUnique )
{
	cltServer* pclserver = (cltServer*)pclClient;
	if( 0 >= siGuildUnique  )					return WRONGGUILDUNIQUE_REQUEST_LIST	;
	// ���� ��尡 �ִ��� �˻�.
	if ( true == IsSameGuild( siGuildUnique ) )	return SAMEGUILD_REQUEST_LIST	;
	// ����� ��û ������ �ð����� �˻�.
	// ���� �ð�
	SYSTEMTIME stTime	= pclserver->sTime	;
	stTime.wHour	=	pclserver->sTime.wHour		;
	stTime.wMinute	=	pclserver->sTime.wMinute	;
	stTime.wSecond	=	pclserver->sTime.wSecond	;
	if ( 
		(stTime.wMinute >= 15 && stTime.wMinute <= 20)  
		|| (stTime.wMinute >= 35 && stTime.wMinute <= 40)  
		|| (stTime.wMinute >= 55 && stTime.wMinute <= 59) )	return 0 ;
	// ������� ã�´�.

	SI32 siEmptySlot = -1	;
	for ( SI32 i = 0 ; i < MAX_GUILD_NUM ; i++)
	{
		if( 0 >= pclGuildList[i].GetGuildUnique() )
		{
			siEmptySlot = i	;
			break	;
		}
	}
	if ( siEmptySlot == -1 )					return FULL_REQUEST_LIST ;
	// �������ũ�� ������� ���� �Ѵ�.
	pclGuildList[siEmptySlot].SetGuildUnique( siGuildUnique ) ;
	siListCount++	;
	return SUCCEED_RWQUEST_LIST	;
}
// ��û����Ʈ���� �ش� ��带 ���� �Ѵ�.
bool cltGuildHuntMapWarManager::Delete( SI32 siGuildQunique )
{
	bool bResult = false ;
	if( 0 >= siGuildQunique  )					return bResult	;
	for ( SI32 i = 0 ; i < MAX_GUILD_NUM ; i++ )
	{
		if ( true == pclGuildList[i].IsSameGuild( siGuildQunique) )
		{
			pclGuildList[i].SetGuildUnique( 0 );
			bResult	=	true	;
			break	;
		}
	}
	return bResult	;
}
// ��û ����Ʈ�� ���� ��尡 �ִ��� �˻�
bool cltGuildHuntMapWarManager::IsSameGuild(SI32 siUnique)
{
	bool bResult	=	false	;
	for ( SI32 i = 0 ; i < MAX_GUILD_NUM ; i++)
	{
		if( true == pclGuildList[i].IsSameGuild( siUnique ) )
		{
			bResult =  true	;
			break	;
		}
	}
	return bResult	;
}
SI32 cltGuildHuntMapWarManager::GetRequestCount()
{
	return siListCount	;
}
void cltGuildHuntMapWarManager::ListClear()
{
	for ( SI32 i = 0 ; i < MAX_GUILDHUNTWAR_MAPNUM ; i++ )
	{
		pclKillPointHome[i].init();
		pclKillPointAway[i].init();
	}
	for ( SI32 siSlot = 0 ;siSlot<MAX_GUILDHUNTWAR_MAPNUM;siSlot++ ) 
	{
		for (SI32 siMember = 0; siMember<MAX_GUILD_MEMBER_NUM; siMember++) 
		{
			pclWarStatus_Home[siSlot][siMember].Init();
			pclWarStatus_Away[siSlot][siMember].Init();
			pclEndWarStatus_Home[siSlot][siMember].Init()	;
			pclEndWarStatus_Away[siSlot][siMember].Init()	;
		}
	}
}
void cltGuildHuntMapWarManager::MatchingListClear()
{
	for ( SI32 i = 0 ; i < MAX_GUILDHUNTWAR_MAPNUM ; i++ )
	{
		pclGuildMatchingListHome[i].Init() ;
		pclGuildMatchingListAway[i].Init() ;
	}
}
void cltGuildHuntMapWarManager::TempMatchingListClear()
{
	for ( SI32 i = 0 ; i < MAX_GUILDHUNTWAR_MAPNUM ; i++ )
	{
		pclGuildMatchingListHomeTemp[i].Init();
		pclGuildMatchingListAwayTemp[i].Init();
	}
}
SI32 cltGuildHuntMapWarManager::FindSameGuildUnique( SI32 siGuildUnique )
{
	SI32 siResult	=	NOT_FIND_LIST;
	// ������ ��Ī����Ʈ�� ���� ��谡 �ִ��� Ȯ�� �Ѵ�.
	for ( SI32 siSlot = 0 ; siSlot < MAX_GUILDHUNTWAR_MAPNUM ; siSlot++)
	{
		if ( true ==  pclGuildMatchingListHome[siSlot].IsSameGuild( siGuildUnique ) )
		{
			siResult	= GUILDWAR_HOMEGUILD ;
		}
		if ( true == pclGuildMatchingListAway[siSlot].IsSameGuild( siGuildUnique ) )
		{
			siResult	=	GUILDWAR_AWAYGUILD ;
		}
	}
	return siResult	;
}
void cltGuildHuntMapWarManager::MixList()
{
	for (SI32 siListSlot = siListCount ; siListSlot > 0 ; siListSlot-- ) // ���� ������ ���̱� ����.
	{
		SI32 siRandomNum = rand() % siListSlot ;													// ���� ���� ������ for������ ���Դϴ�.
		SI32 temp  = pclGuildList[siRandomNum].GetGuildUnique()						;   //   �������
		pclGuildList[siRandomNum].SetGuildUnique(pclGuildList[siListSlot-1].GetGuildUnique())	;
		pclGuildList[siListSlot-1].SetGuildUnique(temp)								;  // ������� ���� �ٲٰ�
	}
}
//void cltGuildHuntMapWarManager::ArrangeTempList()
//{
//	SI32 Emptysolotcount	=	0;	// ������� �� ���°��� ���� �ϱ� ���ؼ� ����Ѵ�.
//		
//	//��� ������ ����Ʈ 
//	#if _SAFE_MEMORY
//		NSafeTArray<cltGuildHuntMapWarListData, MAX_GUILD_NUM>			List	;
//	#else
//		cltGuildHuntMapWarListData				List[MAX_GUILD_NUM]	;
//	#endif
//		for (SI32 sislot = 0; sislot<MAX_GUILD_NUM; sislot++)
//		{
//			List[sislot].Init();
//		}
//	for ( SI32 i = 0 ; i < MAX_GUILD_NUM ; i++)
//	{
//		SI32 siUnique = pclTempGuildList[i].GetGuildUnique()	;
//		if ( siUnique == 0)	continue;
//		List[Emptysolotcount].SetGuildUnique(siUnique);
//		Emptysolotcount = Emptysolotcount+1;
//		if ( siListCount == Emptysolotcount)
//		{
//			for (SI32 slot = 0; slot <MAX_GUILD_NUM; slot++)
//			{
//				pclTempGuildList[slot].SetGuildUnique( List[slot].GetGuildUnique());
//			}break	;
//		}
//	}
//}
//void cltGuildHuntMapWarManager::ArrangeGuildList()
//{
//	SI32 Emptysolotcount	=	0;	// ������� �� ���°��� ���� �ϱ� ���ؼ� ����Ѵ�.
//
//	//��� ������ ����Ʈ 
//#if _SAFE_MEMORY
//	NSafeTArray<cltGuildHuntMapWarListData, MAX_GUILD_NUM>			List	;
//#else
//	cltGuildHuntMapWarListData				List[MAX_GUILD_NUM]	;
//#endif
//	for (SI32 sislot = 0; sislot<MAX_GUILD_NUM; sislot++)
//	{
//		List[sislot].Init();
//	}
//	for ( SI32 i = 0 ; i < MAX_GUILD_NUM ; i++)
//	{
//		SI32 siUnique = pclTempGuildList[i].GetGuildUnique();		if ( siUnique == 0)	continue;
//		List[Emptysolotcount].SetGuildUnique(siUnique);
//		Emptysolotcount = Emptysolotcount+1;
//		if ( siListCount < Emptysolotcount)
//		{
//			for (SI32 slot = 0; slot <MAX_GUILD_NUM; slot++)
//			{
//				pclGuildList[slot].SetGuildUnique( List[slot].GetGuildUnique());
//			}break	;
//		}
//	}
//}
void cltGuildHuntMapWarManager::MakeMatchingList()
{
	cltServer* pclserver = (cltServer*)pclClient;
	if ( siListCount < 2)	return	;
	MixList();
	for ( SI32 i = 0 ; i < MAX_GUILDHUNTWAR_MAPNUM; i++)
	{
		pclGuildMatchingListHomeTemp[i].Init();
		pclGuildMatchingListAwayTemp[i].Init();
	}
	// ����Ʈ�� ������.
	for (SI32 siSlot = 0; siSlot < siListCount; siSlot++)
	{
		if(siSlot > MAX_GUILD_NUM)	return	;
		if(siSlot > siListCount)	return	;

		SI32 GuildUnique = pclGuildList[ siSlot ].GetGuildUnique() ;
		if ( GuildUnique <= 0 )	continue	;
		cltGuildInfo* pclHomeGuildinfo = pclserver->pclGuildManager->GetGuildInfo(GuildUnique)	;
		for ( SI32 siASlot = 0; siASlot < siListCount; siASlot++ )
		{
			SI32 AGuildUnique = pclGuildList[ siASlot ].GetGuildUnique() ;
			if ( 0 == AGuildUnique )	continue	;	// ������� �н�
			if (AGuildUnique	==	GuildUnique)	continue;
			cltGuildInfo* pclAwayGuildinfo = pclserver->pclGuildManager->GetGuildInfo(AGuildUnique)	;
			// Ȩ���� �ο����� �ִ��� Ȯ�� �Ѵ�
			if( true == pclHomeGuildinfo->FindBeforeEnemyGuild( AGuildUnique ) )	continue;	// ������ �ο����� �ִ� ���� �н�
			//// ����� ����  �ο����� �ִ��� Ȯ�� �Ѵ�
			if( true == pclAwayGuildinfo->FindBeforeEnemyGuild( GuildUnique ) )	continue;	// ������ �ο����� �ִ� ���� �н�
			pclGuildMatchingListHomeTemp[ siSlot ].SetGuild( GuildUnique)	;
			pclGuildMatchingListAwayTemp[ siSlot ].SetGuild( AGuildUnique )	;
			pclGuildList[siSlot].Init()		;			
			pclGuildList[siASlot].Init()	;
			siListCount	=	siListCount-2	;
		}
	}
	for (SI32 slot = 0 ; slot < MAX_GUILDHUNTWAR_MAPNUM; slot++ ) 
	{
		SI32 siHomeGuildUnique = pclGuildMatchingListHomeTemp[slot].GetGuildUniqeue();		if(siHomeGuildUnique <= 0 )	break	;
		SI32 siAwayGuildUnique = pclGuildMatchingListAwayTemp[slot].GetGuildUniqeue();		if(siAwayGuildUnique <= 0 )	break	;
		cltGuildInfo* HomeGuildInfo = pclserver->pclGuildManager->GetGuildInfo( siHomeGuildUnique )	;
		cltGuildInfo* AwayGuildInfo = pclserver->pclGuildManager->GetGuildInfo( siAwayGuildUnique )	;
		{
			HomeGuildInfo->setHuntWarEnemy( siAwayGuildUnique )	;// �ο� ���� ���� �Ѵ�.
			sDBRequest_GuildHuntMapWar_SaveRegList clMsg(siHomeGuildUnique ,DelList );
			pclserver->SendDBMsg(DBSELECT_BASE, (sPacketHeader*)&clMsg );	// ��� ����Ʈ���� �A��.
		}
		{
			AwayGuildInfo->setHuntWarEnemy( siHomeGuildUnique )	;// �ο� ���� ���� �Ѵ�.
			sDBRequest_GuildHuntMapWar_SaveRegList clMsg(siAwayGuildUnique ,DelList );
			pclserver->SendDBMsg(DBSELECT_BASE, (sPacketHeader*)&clMsg );// ��� ����Ʈ���� �A��
		}
		TCHAR* pHomeGuildName = HomeGuildInfo->GetName()	;
		TCHAR* pAwayGuildName = AwayGuildInfo->GetName()	;

		// 5������ ��� �ɹ��鿡�� �ش� ���� �����ϰ� �ƴٰ� �˷��ش�.
		for ( SI32 siGuildMember = 0; siGuildMember < MAX_GUILD_MEMBER_NUM; siGuildMember++)
		{
			SI32 siHomeGuildMemberPersonID = HomeGuildInfo->clMember[siGuildMember].siPersonID	;	// ���� ��� �ɹ�
			SI32 siAwayGuildMemberPersonID = AwayGuildInfo->clMember[siGuildMember].siPersonID	;	// ���� ��� �ɹ�
			SI32 siHomememberID = pclserver->pclCM->GetIDFromPersonID(siHomeGuildMemberPersonID)	;
			SI32 siAwayMwmberID = pclserver->pclCM->GetIDFromPersonID(siAwayGuildMemberPersonID)	;
			if( pclserver->pclCM->IsValidID(siHomememberID) )
			{
				cltCharCommon* pclChar = pclserver->pclCM->GetChar(siHomememberID)	;
				cltGameMsgResponse_GuilHuntMapdWar_SendMatchingResult clinfo(HomeGuildInfo->GetName(),pAwayGuildName );
				cltMsg clMsg(GAMEMSG_RESPONSE_GUILDHUNTMAPWAR_SENDMATCHINGRESULT, sizeof(clinfo), (BYTE*)&clinfo);
				pclChar->SendNetMsg((sPacketHeader*)&clMsg);
			}
			if( pclserver->pclCM->IsValidID(siAwayMwmberID) )
			{
				cltCharCommon* pclChar = pclserver->pclCM->GetChar(siAwayMwmberID)	;
				cltGameMsgResponse_GuilHuntMapdWar_SendMatchingResult clinfo(HomeGuildInfo->GetName(),pHomeGuildName );
				cltMsg clMsg(GAMEMSG_RESPONSE_GUILDHUNTMAPWAR_SENDMATCHINGRESULT, sizeof(clinfo), (BYTE*)&clinfo);
				pclChar->SendNetMsg((sPacketHeader*)&clMsg);
			}
		}

	}
}
void cltGuildHuntMapWarManager::ArrangeList()
{
#if _SAFE_MEMORY
	NSafeTArray<cltGuildHuntMapWarListData, MAX_GUILD_NUM>		pclBackupGuildList				;	//	����� ��û	����Ʈ
#else
	cltGuildHuntMapWarListData				pclBackupGuildList[MAX_GUILD_NUM]			;		//	����� ��û	����Ʈ
#endif

	SI32	i;
	// ��ü ����
	for(i=0; i<MAX_GUILD_NUM; i++)				{	pclBackupGuildList[i].SetGuildUnique( pclGuildList[i].GetGuildUnique() );	}
	// ��ü ����
	for (i = 0 ; i<MAX_GUILD_NUM; i++)			{	pclGuildList[i].Init();								}

	// �����͸� �ٽ� ä��
	SI32	siIndex = 0;
	for(i=0; i<MAX_GUILD_NUM; i++)
	{
		if( 0 != pclBackupGuildList[i].GetGuildUnique() )
		{
			if( siIndex >= siListCount )			break;
			pclGuildList[siIndex++].SetGuildUnique( pclBackupGuildList[i].GetGuildUnique() );
		}
	}
}
void cltGuildHuntMapWarManager::Action()
{
	// ���⼭ ����.
	// ��Ī ��Ų����Ʈ�� ���� 
	// ��� ���� ���� �Ѵ�.
	// �ϴ� �� �׼��� ������ ����.

	if (pclClient->GameMode != GAMEMODE_SERVER  )				return	;

	cltServer* pclserver = (cltServer*)pclClient;

	// ���� �ð�
	SYSTEMTIME stTime	= pclserver->sTime	;
	stTime.wHour	=	pclserver->sTime.wHour		;
	stTime.wMinute	=	pclserver->sTime.wMinute	;
	stTime.wSecond	=	pclserver->sTime.wSecond	;

	SI32 siStatus = GetStatus();
	if ( false == pclserver->IsCountrySwitch(Switch_NewGuildHuntMapWar) )	return	;	//����� ����ġ�� ������ ������ �ƾ� �۵� ���ϵ��� �Ѵ�.
	if( true == CanMakeMathingList() ) // ��Ī ����Ʈ�� ����� ���ؼ� ����� ��û ��尡 2�� ��� �̻����� Ȯ�� �Ѵ�.
	{
		// 20�� 5�����̵Ǹ� ������ ����Ʈ�� �������� ��Ī ����Ʈ�� �����.
		// ����� �ð� 15��, 35��, 55��
		if (( stTime.wMinute == 15 && stTime.wSecond == 0 )
			||(stTime.wMinute == 35 && stTime.wSecond == 0 )
			||(stTime.wMinute == 55 && stTime.wSecond == 0 ))
		{
			MakeMatchingList();//��Ī ����Ʈ�� �����.
		}
	}
	switch ( siStatus )
	{
	case EMPTY_MATCHING_LIST :
		{
			if ( (stTime.wMinute == 19 && stTime.wSecond == 30)
				||(stTime.wMinute == 39&& stTime.wSecond == 30)
				||(stTime.wMinute == 59&& stTime.wSecond == 30)			)
			{
				if(true == CopyTempMatchinfList())
				{
					SetStatus( MAKE_MATCHING_LIST )		;
				}
			}
		}break;
	case MAKE_MATCHING_LIST ://�ð��� �Ǹ� ���� �Ұ��� ���� ����.
		{
			if ( ( stTime.wMinute == 0 || stTime.wMinute == 1 || 
				stTime.wMinute == 20 ||stTime.wMinute == 21 || 
				stTime.wMinute == 40 || stTime.wMinute == 41) 
				&& ( stTime.wSecond == 0 || stTime.wSecond == 30 ))
			{
				RequestWarpGuildWarMap();
			}
			if ( stTime.wMinute == 2 ||stTime.wMinute == 22 ||stTime.wMinute == 42 )
			{
				// ���� ��忡�� 1���̻� ���� �ߴ��� Ȯ�� �Ѵ�.
				CanStartGuildWar()	;
				// ��� ���� �ʱ�ȭ
				ClearStatus();	// ���� �ʱ�ȭ 
				SetStatus( GUILDWAR_READY )	;
			}
		}break;
	case GUILDWAR_READY ://������ ��� �ǰ� �ð��� �Ǹ� ������� ���� �Ѵ�.
		{
			//���� �����ϰ� .- EX 20�п� ���� ���� ��쿡 23�п� ���� .1���� �׳� ��� �ð�.
			if ( stTime.wMinute == 3 ||stTime.wMinute == 23 ||stTime.wMinute == 43 )
			{
				// ���� ���踦 ���� �Ѵ�.
				SetEnemy_New()	;	

				SetStatus(GUILDWAR_START)	;
			}								
		}break;
	case GUILDWAR_START:
		{
			Start()	; 					
			SetStatus(GUILDWAR_END)	;
		}break;
	case GUILDWAR_END:
		{
			CanStartGuildWar();// ����
			// 38���� �Ǹ� ��⸦ ���� �ϰ� ����� ���� �Ѵ�.
			if ( stTime.wMinute == 18 ||stTime.wMinute == 38 ||stTime.wMinute == 58 )
			{
				// ������ ������ �����͸� �����
				MakeEndData();
				EndGuildWar_New();
				SetStatus(GUILDWAR_END_WAIT)	;
			}
		}break;
	case GUILDWAR_END_WAIT:
		{
			if ( stTime.wMinute == 19 ||stTime.wMinute == 39 ||stTime.wMinute == 59 )
			{
				ClearStatus();	// ���� �ʱ�ȭ
				// 39�п� ���� ��Ų��.
				EndGuildWarWarp();
				SetStatus(GUILDWAR_CLEANUP)	;
			}
		}break;
	case GUILDWAR_CLEANUP:
		{
			// ������� ���� �ϰ� ���� ��⸦ ���� ��Ī����Ʈ���� Ŭ�����ϰ� ������ƾ ������ �Ѵ�.
			ListClear();
			MatchingListClear();
			SetStatus(EMPTY_MATCHING_LIST)	;
		}break	;
	}


}
void cltGuildHuntMapWarManager::RequestWarpGuildWarMap()
{
	cltServer* pclserver = (cltServer*)pclClient;
	///���õ� ������� �����鿡�� �޼����� ������.
	// ������ ���� �ش� ������ ����� �ʿ� �ִ��� Ȯ�� �ؾ� �Ѵ�.
	for ( SI32 i = 0; i < MAX_GUILDHUNTWAR_MAPNUM;	i++ )
	{
		SI32 siHomeuildUnique = pclGuildMatchingListHome[i].GetGuildUniqeue()	;	// Ȩ ��� ����ũ
		SI32 siAwayuildUnique = pclGuildMatchingListAway[i].GetGuildUniqeue()	;	// ����� ��� ����ũ

		if ( siHomeuildUnique <= 0 || siAwayuildUnique <= 0)			continue	;

		cltGuildInfo* HomeGuildInfo = pclserver->pclGuildManager->GetGuildInfo(siHomeuildUnique);
		cltGuildInfo* AwayGuildInfo = pclserver->pclGuildManager->GetGuildInfo(siAwayuildUnique);
		
		if(HomeGuildInfo == NULL )	continue	;
		if(AwayGuildInfo == NULL )	continue	;

		for ( SI32 siMemberCount = 0 ; siMemberCount < MAX_GUILD_MEMBER_NUM ; siMemberCount++ )
		{
			SI32 siHomeGuildMemberPersonID = HomeGuildInfo->clMember[ siMemberCount ].siPersonID	;
			SI32 siAwayGuildMemberPersonID = AwayGuildInfo->clMember[ siMemberCount ].siPersonID	;


			SI32 siCharID_Home = pclserver->pclCM->GetIDFromPersonID( siHomeGuildMemberPersonID )	;
			SI32 siCharID_Away = pclserver->pclCM->GetIDFromPersonID( siAwayGuildMemberPersonID )	;

			cltCharCommon* pclChar_Home = pclserver->pclCM->GetChar(siCharID_Home)	;
			cltCharCommon* pclChar_Away = pclserver->pclCM->GetChar(siCharID_Away)	;

			if( pclChar_Home != NULL)
			{
				if( pclClient->pclCM->IsValidID(pclChar_Home->GetID())){
					SI32 siMapindexHome =  pclChar_Home->GetMapIndex();
					if ( siMapindexHome >= MAPINDEX_GUILDWARFIELD && siMapindexHome < MAPINDEX_GUILDWARFIELD+GUILDWAR_FIELDNUM )
					{
					}
					else
					{
						// Ȩ ��������
						cltGameMsgResponse_GuildHuntMapWarWar_Request clResponseGuildWarHome( REQUEST_WARP_HUNTMAPGUILDWAR_WARP, siHomeGuildMemberPersonID,pclserver->sTime );
						cltMsg clMsgHome( GAMEMSG_RESPONSE_GUILDHUNTMAPWAR_REQUEST_WARP, sizeof(clResponseGuildWarHome), (BYTE*)&clResponseGuildWarHome );
						pclChar_Home->SendNetMsg((sPacketHeader*)&clMsgHome);
					}
				}				
			}
			if( pclChar_Away != NULL)
			{
				if(pclClient->pclCM->IsValidID(pclChar_Away->GetID())){
					SI32 siMapindexAway =  pclChar_Away->GetMapIndex();
					if ( siMapindexAway >= MAPINDEX_GUILDWARFIELD && siMapindexAway < MAPINDEX_GUILDWARFIELD+GUILDWAR_FIELDNUM )
					{

					}
					else
					{
						// ����� ��������
						cltGameMsgResponse_GuildHuntMapWarWar_Request clResponseGuildWarAway( REQUEST_WARP_HUNTMAPGUILDWAR_WARP, siAwayGuildMemberPersonID, pclserver->sTime );
						cltMsg clMsgAway( GAMEMSG_RESPONSE_GUILDHUNTMAPWAR_REQUEST_WARP, sizeof(clResponseGuildWarAway), (BYTE*)&clResponseGuildWarAway );
						pclChar_Away->SendNetMsg((sPacketHeader*)&clMsgAway);
					}
				}
			}
		}

	}
}
void cltGuildHuntMapWarManager::WarpGuildWar_New(SI32 personID ) //���� ������ ���� ��Ų��.
{
	SI32 fieldindex =	0	;
	// �ش� �ɸ��͸� ���� ��Ų��.
	cltServer* pclserver = (cltServer*)pclClient;
	if ( pclserver == NULL )											return ;
	SI32 charID = pclClient->pclCM->GetIDFromPersonID(personID);
	if( false == pclClient->pclCM->IsValidID( charID ) )				return	;
	cltCharCommon* pclChar = pclserver->pclCM->GetChar( charID)	;
	if(pclChar == NULL )												return	;
	TCHAR* dzGuildName = pclChar->pclCI->clBI.clGuildRank.szGuildName;
	if ( dzGuildName == NULL)											return	;
	cltGuildInfo* pclGuildInfo = pclserver->pclGuildManager->GetGuildInfo(dzGuildName);
	if(pclGuildInfo == NULL )											return	;
	SI32 siGuildUnique = pclGuildInfo->siUnique	;
	// Ȩ������ ����� ������
	SI32 HomeAway = IsHomeGuildorAwayGuild( siGuildUnique )	;
	// ���� �̵��ؾ��� ���� �����Ѵ�
	fieldindex = FindWarpMapIndex(siGuildUnique);
	switch ( HomeAway )
	{
	case GUILDWAR_HOMEGUILD :
		{
			cltWarpInfo clWarpInfo(1, 0, false, true, 0, 0, -1, -1);
			clWarpInfo.uiMapIndex = GUILDWARFIELD_INDEX + fieldindex;
			SI32 siRand = rand()%4;
			clWarpInfo.uiX = Const_HomePos[ siRand * 2 ];
			clWarpInfo.uiY = Const_HomePos[ siRand * 2 + 1];
			cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->GetCharServer(charID);
			if (pclchar == NULL )	return	;
			pclchar->SetWarpInfo(&clWarpInfo, 2200);

		}break;
	case GUILDWAR_AWAYGUILD :
		{
			cltWarpInfo clWarpInfo(1, 0, false, true, 0, 0, -1, -1);
			clWarpInfo.uiMapIndex = GUILDWARFIELD_INDEX + fieldindex;
			SI32 siRand = rand()%4;
			clWarpInfo.uiX = Const_AwayPos[ siRand * 2 ];
			clWarpInfo.uiY = Const_AwayPos[ siRand * 2 + 1];
			cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->GetCharServer(charID);
			if (pclchar == NULL )	return	;
			pclchar->SetWarpInfo(&clWarpInfo, 2200);

		}break;
	}
}
void cltGuildHuntMapWarManager::ClearStatus()
{
	ClearWarStatus();
	ClearKillPoint();
}
void cltGuildHuntMapWarManager::ClearWarStatus()
{
	for (SI32 siMapSlot = 0; siMapSlot< MAX_GUILDHUNTWAR_MAPNUM; siMapSlot++) 
	{
		for (SI32 siMemberSlot = 0; siMemberSlot< MAX_GUILD_MEMBER_NUM; siMemberSlot++) 
		{
			pclWarStatus_Home[siMapSlot][siMemberSlot].Init();
			pclWarStatus_Away[siMapSlot][siMemberSlot].Init();
			m_HomePersonDeadClock[siMapSlot][siMemberSlot]	=	0	;
			m_AwayPersonDeadClock[siMapSlot][siMemberSlot]	=	0	;
			pclEndWarStatus_Home[siMapSlot][siMemberSlot].Init()	;
			pclEndWarStatus_Away[siMapSlot][siMemberSlot].Init()	;
		}
	}
}
void cltGuildHuntMapWarManager::ClearKillPoint()
{
	for (SI32 siMapSlot = 0; siMapSlot< MAX_GUILDHUNTWAR_MAPNUM; siMapSlot++) 
	{
		pclKillPointHome[siMapSlot].init()	;
		pclKillPointAway[siMapSlot].init()	;
	}

}
void cltGuildHuntMapWarManager::ClearTargetStatus(SI32 siGuildUnique )
{
	SI32 siMapSlot	=	0	;
	SI32 HomeAway	=	0	;
	//���� ����� �ʿ��� ������ �� ������� Ȯ���Ѵ�.
	for (SI32 siMapIndex = 0; siMapIndex < MAX_GUILDHUNTWAR_MAPNUM; siMapIndex++ ) 
	{
		SI32 siHomeGuildUnique = pclGuildMatchingListHome[siMapIndex].GetGuildUniqeue()	;
		SI32 siAwayGuildUnique = pclGuildMatchingListAway[siMapIndex].GetGuildUniqeue()	;
		if (siHomeGuildUnique == siGuildUnique ) 
		{
			siMapSlot	=	siMapIndex	;
			HomeAway	=	GUILDWAR_HOME	;

			break	;
		}
		else if (siAwayGuildUnique == siGuildUnique ) 
		{
			siMapSlot	=	siMapIndex	;
			HomeAway	=	GUILDWAR_AWAY	;
			break	;
		}
		switch( HomeAway )
		{
		case GUILDWAR_HOME:
			{
				pclKillPointHome[siMapSlot].init()	;
				for (SI32 siMapSlot = 0; siMapSlot< MAX_GUILDHUNTWAR_MAPNUM; siMapSlot++)
				{
					for (SI32 siMemberSlot = 0; siMemberSlot< MAX_GUILD_MEMBER_NUM; siMemberSlot++) 
					{
						pclWarStatus_Home[siMapSlot][siMemberSlot].Init();
					}
				}
			}break;
		case GUILDWAR_AWAY:
			{
				pclKillPointAway[siMapSlot].init()	;
				for (SI32 siMapSlot = 0; siMapSlot< MAX_GUILDHUNTWAR_MAPNUM; siMapSlot++) 
				{
					for (SI32 siMemberSlot = 0; siMemberSlot< MAX_GUILD_MEMBER_NUM; siMemberSlot++) 
					{
						pclWarStatus_Away[siMapSlot][siMemberSlot].Init();
					}
				}
			}break;
		}

	}

}
void cltGuildHuntMapWarManager::Start()
{
	// ������� ���� �ϱ� ���� ��� ���� ���� �������� �ʱ�ȭ �Ѵ�.

	//������� ���� �Ѵ�.
	//	2. ����
	for ( SI32 i = 0; i < MAX_GUILDHUNTWAR_MAPNUM; i++) 
	{
		// Ȩ & ����̱�� �鿡�� ������ ���� �Ѵ�.
		SI32 siHomeGuildUnique = pclGuildMatchingListHome[i].GetGuildUniqeue();
		SI32 siAwayGuildUnique = pclGuildMatchingListAway[i].GetGuildUniqeue();
		if ( siHomeGuildUnique <= 0 || siAwayGuildUnique <= 0 ) continue	;

		cltGuildInfo* pclHomeGuild = pclClient->pclGuildManager->GetGuildInfo( siHomeGuildUnique );
		cltGuildInfo* pclAwayGuild = pclClient->pclGuildManager->GetGuildInfo( siAwayGuildUnique );

		if ( pclHomeGuild == NULL ||  pclAwayGuild == NULL )		continue	;
		for ( SI32 i = 0 ; i < MAX_GUILD_MEMBER_NUM ; i ++ )
		{
			SI32 siHomeMemberPeronID = pclHomeGuild->clMember[i].siPersonID	;
			SI32 siAwayMemberPeronID = pclAwayGuild->clMember[i].siPersonID	;
			SI32 siHomecharID	=	pclClient->pclCM->GetIDFromPersonID(siHomeMemberPeronID)	;
			SI32 siAwaycharID	=	pclClient->pclCM->GetIDFromPersonID(siAwayMemberPeronID)	;
			if ( pclClient->pclCM->IsValidID(siHomecharID) ) 
			{
				cltCharServer* pclHomechar = (cltCharServer*)pclClient->pclCM->CR[siHomecharID];
				// ������� ���۵Ǿ��ٰ� Ŭ���̾�Ʈ���� �˷��ش�.
				{
					cltGameMsgResponse_GuilHuntMapdWar_Start clinfo( pclHomeGuild->siUnique,pclAwayGuild->siUnique,pclHomeGuild->szName, pclAwayGuild->szName, pclHomeGuild->clGPoint.siMarkIndex, pclAwayGuild->clGPoint.siMarkIndex );
					cltMsg clMsg(GAMEMSG_RESPONSE_GUILDHUNTMAPWAR_START, sizeof(clinfo), (BYTE*)&clinfo);
					pclHomechar->SendNetMsg((sPacketHeader*)&clMsg);
				}
			}
			if ( pclClient->pclCM->IsValidID(siAwaycharID) ) 
			{
				cltCharServer* pclAwaychar = (cltCharServer*)pclClient->pclCM->CR[siAwaycharID];
				// ������� ���۵Ǿ��ٰ� Ŭ���̾�Ʈ���� �˷��ش�.
				{
					cltGameMsgResponse_GuilHuntMapdWar_Start clinfo( pclHomeGuild->siUnique, pclAwayGuild->siUnique, pclHomeGuild->szName, pclAwayGuild->szName,  pclHomeGuild->clGPoint.siMarkIndex, pclAwayGuild->clGPoint.siMarkIndex );
					cltMsg clMsg(GAMEMSG_RESPONSE_GUILDHUNTMAPWAR_START, sizeof(clinfo), (BYTE*)&clinfo);
					pclAwaychar->SendNetMsg((sPacketHeader*)&clMsg);
				}
			}
		}
	}
}
void cltGuildHuntMapWarManager::EndGuildWar_New()
{
	for ( SI32 i = 0; i < MAX_GUILDHUNTWAR_MAPNUM; ++i) 
	{
		SI32 HomeResult	=GUILDWAR_END_NORESULT	;
		SI32 AwayResult	= GUILDWAR_END_NORESULT	;
		SI32 siHomeGuildUnique = pclGuildMatchingListHome[i].GetGuildUniqeue();
		SI32 siAwayGuildUnique = pclGuildMatchingListAway[i].GetGuildUniqeue();
		if ( siAwayGuildUnique <= 0 || siHomeGuildUnique <= 0 ) return	;
		cltGuildInfo* pclHomeGuild = pclClient->pclGuildManager->GetGuildInfo( siHomeGuildUnique );
		cltGuildInfo* pclAwayGuild = pclClient->pclGuildManager->GetGuildInfo( siAwayGuildUnique );
		if ( pclHomeGuild == NULL ||  pclAwayGuild == NULL )		return;
		// ���� ���и� �����ش�.
		if( pclKillPointHome[i].siKillPoint > pclKillPointAway[i].siKillPoint ) // Ȩ�� �¸�
		{
			HomeResult = GUILDWAR_END_WIN;
			AwayResult = GUILDWAR_END_LOSE;
		}
		else if( pclKillPointHome[i].siKillPoint < pclKillPointAway[i].siKillPoint )// ������� �¸�
		{
			HomeResult = GUILDWAR_END_LOSE;
			AwayResult = GUILDWAR_END_WIN;

		}
		else if( pclKillPointHome[i].siKillPoint == pclKillPointAway[i].siKillPoint ) //���
		{
			HomeResult = GUILDWAR_END_DRAW;
			AwayResult = GUILDWAR_END_DRAW;
		}
		SendResultToDB(siHomeGuildUnique,HomeResult);
		SendResultToDB(siAwayGuildUnique,AwayResult);
		DelEnemy(siHomeGuildUnique,siAwayGuildUnique);
		for ( SI32 simemberslot = 0 ; simemberslot < MAX_GUILD_MEMBER_NUM ; simemberslot ++ )
		{
			SI32 siHomeMemberPeronID = pclHomeGuild->clMember[simemberslot].siPersonID	;
			SI32 siAwayMemberPeronID = pclAwayGuild->clMember[simemberslot].siPersonID	;

			SI32 siHomecharID	=	pclClient->pclCM->GetIDFromPersonID(siHomeMemberPeronID)	;
			SI32 siAwaycharID	=	pclClient->pclCM->GetIDFromPersonID(siAwayMemberPeronID)	;
			if ( pclClient->pclCM->IsValidID(siHomecharID) ) 
			{
				cltCharServer* pclHomechar = (cltCharServer*)pclClient->pclCM->CR[siHomecharID];
				// Ŭ���̾�Ʈ�� ���Ḧ �˷��ش�.
				{
					cltGameMsgResponse_GuilHuntMapdWar_End clinfo( HomeResult,pclEndWarStatus_Home[i],pclEndWarStatus_Away[i]  );
					cltMsg clMsg(GAMEMSG_RESPONSE_GUILDHUNTMAPWAR_WAREND, sizeof(clinfo), (BYTE*)&clinfo);
					pclHomechar->SendNetMsg((sPacketHeader*)&clMsg);
				}
			}
			if ( pclClient->pclCM->IsValidID(siAwaycharID) ) 
			{
				cltCharServer* pclAwaychar = (cltCharServer*)pclClient->pclCM->CR[siAwaycharID];
				{
					cltGameMsgResponse_GuilHuntMapdWar_End clinfo( AwayResult,pclEndWarStatus_Home[i],pclEndWarStatus_Away[i] );
					cltMsg clMsg(GAMEMSG_RESPONSE_GUILDHUNTMAPWAR_WAREND, sizeof(clinfo), (BYTE*)&clinfo);
					pclAwaychar->SendNetMsg((sPacketHeader*)&clMsg);
				}
			}
		}
	}
}
void cltGuildHuntMapWarManager::SetEnemy_New()
{
	for ( SI32 i = 0; i < MAX_GUILDHUNTWAR_MAPNUM; i++) 
	{
		//////////////////////////////////////////////////////////////////////////		
		SI32 siHomeGuildUnique = pclGuildMatchingListHome[i].GetGuildUniqeue();
		SI32 siAwayGuildUnique = pclGuildMatchingListAway[i].GetGuildUniqeue();
		//////////////////////////////////////////////////////////////////////////
		if ( siHomeGuildUnique <= 0 || siAwayGuildUnique <= 0 ) continue	;

		cltGuildInfo* pclHomeGuild = pclClient->pclGuildManager->GetGuildInfo( siHomeGuildUnique );
		cltGuildInfo* pclAwayGuild = pclClient->pclGuildManager->GetGuildInfo( siAwayGuildUnique );
		//////////////////////////////////////////////////////////////////////////
		if ( pclHomeGuild == NULL ||  pclAwayGuild == NULL )		continue;
		//////////////////////////////////////////////////////////////////////////
		// for���� ���鼭 ����带 ���� ���ش�.
		//////////////////////////////////////////////////////////////////////////
		for ( SI32 i = 0 ; i < MAX_GUILD_MEMBER_NUM ; i ++ )
		{
			// �ɸ��� ���̵� ã�´�.
			//------------------------------------------------------------------------------------
			SI32 siHomeMemberPeronID = pclHomeGuild->clMember[i].siPersonID	;
			SI32 siAwayMemberPeronID = pclAwayGuild->clMember[i].siPersonID	;

			SI32 siHomecharID	=	pclClient->pclCM->GetIDFromPersonID(siHomeMemberPeronID)	;
			SI32 siAwaycharID	=	pclClient->pclCM->GetIDFromPersonID(siAwayMemberPeronID)	;
			//------------------------------------------------------------------------------------
			if ( pclClient->pclCM->IsValidID(siHomecharID) ) 
			{
				cltCharServer* pclHomechar = (cltCharServer*)pclClient->pclCM->CR[siHomecharID];
				pclHomechar->pclCI->clBI.clGuildRank.siEnemyGuildUnique = siAwayGuildUnique	;

				pclHomechar->ParametaBoxAction();
				// ������� ä���. 
				pclHomechar->pclCI->clIP.SetLife( pclHomechar->clPB.GetMaxLife() );
				// ������ ä���ش�
				pclHomechar->pclCI->clIP.SetMana( pclHomechar->clPB.GetMaxMana() );
				{
					cltGameMsgResponse_Guild_SetGuildStatus clinfo(&pclHomeGuild->clStatus,&pclHomechar->pclCI->clBI.clGuildRank, pclHomechar->CharUnique);
					cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_SETGUILDSTATUS, sizeof(clinfo), (BYTE*)&clinfo);
					pclHomechar->SendNeighbourMsg(&clMsg,true);
				}
			}
			if ( pclClient->pclCM->IsValidID(siAwaycharID) ) 
			{
				cltCharServer* pclAwaychar = (cltCharServer*)pclClient->pclCM->CR[siAwaycharID];
				pclAwaychar->pclCI->clBI.clGuildRank.siEnemyGuildUnique = siHomeGuildUnique	;
				pclAwaychar->ParametaBoxAction();
				// ������� ä���. 
				pclAwaychar->pclCI->clIP.SetLife( pclAwaychar->clPB.GetMaxLife() );
				// ������ ä���ش�
				pclAwaychar->pclCI->clIP.SetMana( pclAwaychar->clPB.GetMaxMana() );
				{
					cltGameMsgResponse_Guild_SetGuildStatus clinfo2(&pclAwayGuild->clStatus, &pclAwaychar->pclCI->clBI.clGuildRank, pclAwaychar->CharUnique);
					cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_SETGUILDSTATUS, sizeof(clinfo2), (BYTE*)&clinfo2);
					pclAwaychar->SendNeighbourMsg(&clMsg,true);
				}
			}
		}
	}
}
SI32 cltGuildHuntMapWarManager:: IsHomeGuildorAwayGuild( SI32 siGuildunique)
{
	SI32 siResult =	NOT_FIND_LIST	;
	for ( SI32 siGuildSlot = 0; siGuildSlot < MAX_GUILDHUNTWAR_MAPNUM; siGuildSlot++)
	{
		if( true == pclGuildMatchingListHome[siGuildSlot].IsSameGuild( siGuildunique) )
		{
			siResult = GUILDWAR_HOMEGUILD	;
			return siResult	;
		}
		else if( true == pclGuildMatchingListAway[siGuildSlot].IsSameGuild( siGuildunique) )
		{
			siResult = GUILDWAR_AWAYGUILD	;
			return siResult	;
		}
	}
	return siResult	;
}
SI32 cltGuildHuntMapWarManager:: FindWarpMapIndex( SI32 siGuildunique)
{
	SI32 siResult =	0	;
	for ( SI32 siGuildSlot = 0; siGuildSlot < MAX_GUILDHUNTWAR_MAPNUM; siGuildSlot++)
	{
		if( true == pclGuildMatchingListHome[siGuildSlot].IsSameGuild( siGuildunique) )
		{
			siResult =  siGuildSlot	;
			return siResult	;
			break	;
		}
		else if( true == pclGuildMatchingListAway[siGuildSlot].IsSameGuild( siGuildunique) )
		{
			siResult =  siGuildSlot	;
			return siResult	;
			break;
		}
	}
	return siResult	;
}
void cltGuildHuntMapWarManager::SetStatus(SI32 Status)
{
	siStatus	=	Status	;
}
SI32 cltGuildHuntMapWarManager::GetStatus()
{
	return siStatus	;
}
bool cltGuildHuntMapWarManager::CanMakeMathingList()
{
	// ����Ʈ�� 2�� �̻� ��尡 ��ϵǾ� �־�� ��Ī ����Ʈ�� �����.
	bool bResult	=	 false;
	if(siListCount >= 2)		bResult = true;

	return bResult;
}
void cltGuildHuntMapWarManager::EndGuildWarWarp()
{
	cltServer* pclserver = (cltServer*)pclClient;
	///���õ� ������� �����鿡�� �޼����� ������.
	// ������ ���� �ش� ������ ����� �ʿ� �ִ��� Ȯ�� �ؾ� �Ѵ�.
	for ( SI32 i = 0; i < MAX_GUILDHUNTWAR_MAPNUM;	i++ )
	{
		SI32 siHomeuildUnique = pclGuildMatchingListHome[i].GetGuildUniqeue()	;	// Ȩ ��� ����ũ
		SI32 siAwayuildUnique = pclGuildMatchingListAway[i].GetGuildUniqeue()	;	// ����� ��� ����ũ
		if ( siHomeuildUnique <= 0 || siAwayuildUnique <= 0)			continue	;
		GuildWarptoSafeZone(siHomeuildUnique);
		GuildWarptoSafeZone(siAwayuildUnique);
	}
}
void cltGuildHuntMapWarManager::GuildWarptoSafeZone( SI32 siGuildUnique )
{
	cltServer* pclserver = (cltServer*)pclClient;
	cltGuildInfo* pGuildInfo = pclserver->pclGuildManager->GetGuildInfo(siGuildUnique);

	for ( SI32 siMemberCount = 0 ; siMemberCount < MAX_GUILD_MEMBER_NUM ; siMemberCount++ )
	{
		SI32 siHomeGuildMemberPersonID = pGuildInfo->clMember[ siMemberCount ].siPersonID	;
		SI32 siCharID	= pclserver->pclCM->GetIDFromPersonID( siHomeGuildMemberPersonID )	;

		cltCharCommon* pclChar = pclserver->pclCM->GetChar(siCharID)	;

		if( pclChar != NULL)
		{
			SI32 ID = pclChar->GetID()	;
			if( pclClient->pclCM->IsValidID(ID))
			{
				if (pclClient->pclCM->IsAlive( ID ) == false) // ����� ������ �׾� �ִٸ� �츰��.
				{
					pclClient->pclCM->CR[ID]->Revive();
				}

				SI32 siMapindexHome =  pclChar->GetMapIndex();
				if ( siMapindexHome >= MAPINDEX_GUILDWARFIELD && siMapindexHome < MAPINDEX_GUILDWARFIELD+GUILDWAR_FIELDNUM )
				{
					cltCharServer* pCharserver = (cltCharServer*)pclClient->pclCM->GetCharServer(ID)	;
					if ( pCharserver != NULL )
					{
						pCharserver->WarpToSafeZone();
					}

				}
			}				
		}
	}

}
void cltGuildHuntMapWarManager:: DelEnemy(SI32 siHomeGuildUnique , SI32 siAwayGuildUnique )	// ���� ��带 ���� �Ѵ�.
{
	cltServer* pclserver = (cltServer*)pclClient;
	cltGuildInfo* pclHomeGuild	=	pclserver->pclGuildManager->GetGuildInfo(siHomeGuildUnique)		;
	cltGuildInfo* pclAwayGuild	=	pclserver->pclGuildManager->GetGuildInfo(siAwayGuildUnique)		;
	for ( SI32 simemberslot = 0 ; simemberslot < MAX_GUILD_MEMBER_NUM ; simemberslot ++ )
	{
		SI32 siHomeMemberPeronID = pclHomeGuild->clMember[simemberslot].siPersonID	;
		SI32 siAwayMemberPeronID = pclAwayGuild->clMember[simemberslot].siPersonID	;

		SI32 siHomecharID	=	pclClient->pclCM->GetIDFromPersonID(siHomeMemberPeronID)	;
		SI32 siAwaycharID	=	pclClient->pclCM->GetIDFromPersonID(siAwayMemberPeronID)	;
		if ( pclClient->pclCM->IsValidID(siHomecharID) ) 
		{
			// ���� ��带 ���� ��Ų��
			cltCharServer* pclHomechar = (cltCharServer*)pclClient->pclCM->CR[siHomecharID];
			pclHomechar->pclCI->clBI.clGuildRank.SetEnemyGuild( 0)	;
			{
				cltGameMsgResponse_Guild_SetGuildStatus clinfo(&pclHomeGuild->clStatus,&pclHomechar->pclCI->clBI.clGuildRank,pclHomechar->GetCharUnique());
				cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_SETGUILDSTATUS, sizeof(clinfo), (BYTE*)&clinfo);
				pclHomechar->SendNeighbourMsg(&clMsg,true);
			}
		}
		if ( pclClient->pclCM->IsValidID(siAwaycharID) ) 
		{
			cltCharServer* pclAwaychar = (cltCharServer*)pclClient->pclCM->CR[siAwaycharID];
			pclAwaychar->pclCI->clBI.clGuildRank.SetEnemyGuild( 0)	;
			{
				cltGameMsgResponse_Guild_SetGuildStatus clinfo(&pclAwayGuild->clStatus,&pclAwaychar->pclCI->clBI.clGuildRank,pclAwaychar->GetCharUnique());
				cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_SETGUILDSTATUS, sizeof(clinfo), (BYTE*)&clinfo);
				pclAwaychar->SendNeighbourMsg(&clMsg,true);
			}
		}
	}
}

void cltGuildHuntMapWarManager:: SendResultToDB(SI32 siGuildUnique, SI32 siFlag )		// ���и� ���� ������.
{
	SI32 siResultPoint	=	0	;// ����� ���� BGP
	SI32 siResultFlag	=	GUILDWAR_END_NORESULT	;	// ��� ���� 
	switch( siFlag ) {
	case GUILDWAR_END_WIN :
	case GUILDWAR_END_WIN_NOWARP :{
		siResultFlag	=	GUILDWAR_END_WIN	;
		siResultPoint	=	GUILDWAR_WINPOINT	;
								  }
								  break;
	case GUILDWAR_END_DRAW :
	case GUILDWAR_END_DRAW_NOWARP :{
		siResultFlag	=	GUILDWAR_END_DRAW	;
		siResultPoint	=	GUILDWAR_DRAWPOINT	;
								   }
								   break;
	case GUILDWAR_END_LOSE :
	case GUILDWAR_END_LOSE_NOWARP:{
		siResultFlag	=	GUILDWAR_END_LOSE	;
		siResultPoint	=	GUILDWAR_LOSEPOINT	;
								  }
								  break;
	default:
		{
			siResultFlag	=	GUILDWAR_END_NORESULT	;
			siResultPoint	=	0	;
		}
	}
	sDBRequest_GuildHuntMapWar_Result clMsg(siGuildUnique, siResultFlag  ,siResultPoint );
	pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader*)&clMsg );

}
void cltGuildHuntMapWarManager:: CanStartGuildWar()
{
	cltServer* pclserver = (cltServer*)pclClient;
	// ���� �ʺ��� ������� �����Ҽ� �ִ��� Ȯ�� �Ѵ�.
	// ������ �Ѹ� ok���� �ʾҴٸ� �������� �Ѿ�� �ʰ� ���� �Ѵ�.
	for ( SI32 i = 0; i < MAX_GUILDHUNTWAR_MAPNUM;	i++ )
	{
		SI32 siHomeGuildUnique = pclGuildMatchingListHome[i].GetGuildUniqeue();
		SI32 siAwayGuildUnique = pclGuildMatchingListAway[i].GetGuildUniqeue();
		if ( siHomeGuildUnique == 0 || siAwayGuildUnique == 0 )					continue	;
		SI32 homePersonCount_Home = GetInHuntMapWarPersonNumHome(i);
		SI32 AwayPersonCount_Home = GetInHuntMapWarPersonNumAway(i);
		if ( homePersonCount_Home == 0 || AwayPersonCount_Home == 0 ) 
		{
			// ��� ����
			cltGuildInfo* pclHomeGuild = pclserver->pclGuildManager->GetGuildInfo( siHomeGuildUnique)	;
			cltGuildInfo* pclAwayGuild =  pclserver->pclGuildManager->GetGuildInfo( siAwayGuildUnique )	;
			if ( pclHomeGuild == NULL ||  pclAwayGuild == NULL )		return;		
			// Ȩ���� ������
			if ( homePersonCount_Home <= 0 &&AwayPersonCount_Home > 0 )
			{
				//Ȩ���� �й� �Ͽ����� ���� �����ش�.
				SendResultToDB(siHomeGuildUnique,GUILDWAR_END_LOSE);				
				SendResultToDB(siAwayGuildUnique,GUILDWAR_END_WIN);

				SendResultWarHome(i,GUILDWAR_END_LOSE_NOWARP );
				SendResultWarAway(i,GUILDWAR_END_WIN_NOWARP );
				// ������ �� ��带��Ī����Ʈ���� ���� �Ѵ�.
				pclGuildMatchingListHome[i].Init()	;	// Ȩ ��� ����ũ
				pclGuildMatchingListAway[i].Init()	;	// ����� ��� ����ũ
				DelEnemy(siHomeGuildUnique,siAwayGuildUnique);
				ClearTargetStatus(siHomeGuildUnique);	// �ش� ����� ���� ����
				ClearTargetStatus(siAwayGuildUnique);	// �ش� ����� ���� ����
				GuildWarptoSafeZone(siAwayGuildUnique);

			}
			// ��������� ������
			else if ( homePersonCount_Home > 0 &&AwayPersonCount_Home <= 0 )
			{
				SendResultToDB(siHomeGuildUnique,GUILDWAR_END_WIN );				
				SendResultToDB(siAwayGuildUnique,GUILDWAR_END_LOSE);
				SendResultWarHome(i,GUILDWAR_END_WIN_NOWARP);
				SendResultWarAway(i,GUILDWAR_END_LOSE_NOWARP);
				// ������ �� ��带��Ī����Ʈ���� ���� �Ѵ�.
				pclGuildMatchingListHome[i].Init()	;	// Ȩ ��� ����ũ
				pclGuildMatchingListAway[i].Init()	;	// ����� ��� ����ũ
				DelEnemy(siHomeGuildUnique,siAwayGuildUnique);
				ClearTargetStatus(siHomeGuildUnique);	// �ش� ����� ���� ����
				ClearTargetStatus(siAwayGuildUnique);	// �ش� ����� ���� ����
				GuildWarptoSafeZone(siHomeGuildUnique);
			}
			// 
			else if ( homePersonCount_Home <= 0 &&AwayPersonCount_Home <= 0 )
			{
				SendResultToDB(siHomeGuildUnique,GUILDWAR_END_DRAW );				
				SendResultToDB(siAwayGuildUnique,GUILDWAR_END_DRAW);
				SendResultWarHome(i,GUILDWAR_END_DRAW_NOWARP );
				SendResultWarAway(i,GUILDWAR_END_DRAW_NOWARP );
				// ������ �� ��带��Ī����Ʈ���� ���� �Ѵ�.
				pclGuildMatchingListHome[i].Init()	;	// Ȩ ��� ����ũ
				pclGuildMatchingListAway[i].Init()	;	// ����� ��� ����ũ
				DelEnemy(siHomeGuildUnique,siAwayGuildUnique);
				ClearTargetStatus(siHomeGuildUnique);	// �ش� ����� ���� ����
				ClearTargetStatus(siAwayGuildUnique);	// �ش� ����� ���� ����
			}
		}
	}
}
void cltGuildHuntMapWarManager::addKillPoint(SI32 siKillerId,SI32 DeathID)
{
	cltServer* pclserver = (cltServer*)pclClient;
	SI32 HomeNaway = 0;	//	 0�̸� Ȩ 1�̸� �����
	if ( false == pclserver->pclCM->IsValidID(siKillerId ) )	return;
	if ( false == pclserver->pclCM->IsValidID(DeathID ) )		return;
	cltCharCommon* pclKiller = pclserver->pclCM->GetChar(siKillerId)	;
	cltCharCommon* pclDeath = pclserver->pclCM->GetChar(DeathID)	;
	SI32 siDeathPersonID = pclDeath->pclCI->GetPersonID()	;// ���� ����� personID
	SI32 sikillerPersonID = pclKiller->pclCI->GetPersonID()	;// ���� ����� personID
	// ���� ���� Ȩ���� ������� �����ؼ� ����Ʈ �ø���
	for (SI32 siSlot = 0 ; siSlot < MAX_GUILDHUNTWAR_MAPNUM; siSlot++)
	{		
		SI32 siHomeGuildUnique = pclGuildMatchingListHome[siSlot].GetGuildUniqeue();
		SI32 siAwayGuildUnique = pclGuildMatchingListAway[siSlot].GetGuildUniqeue();

		if ( siHomeGuildUnique <= 0 || siAwayGuildUnique <= 0)	continue ;

		cltGuildInfo* pcHomelGuildinfo = pclserver->pclGuildManager->GetGuildInfo(siHomeGuildUnique);
		cltGuildInfo* pcAwaylGuildinfo = pclserver->pclGuildManager->GetGuildInfo(siAwayGuildUnique);
		for (SI32 i = 0; i<MAX_GUILD_MEMBER_NUM; i++ ) 
		{
			// Ȩ������ �׾���
			if( siDeathPersonID == pcHomelGuildinfo->clMember[i].siPersonID && pcHomelGuildinfo->clMember[i].siPersonID != 0)
			{		
				HomeNaway	=	GUILDWAR_HOME;
				SaveKillinfo(siSlot,HomeNaway,0,siDeathPersonID);//����ī��Ʈ�� �ø���
			}
			// ����������� �׾���
			else if( siDeathPersonID == pcAwaylGuildinfo->clMember[i].siPersonID && pcAwaylGuildinfo->clMember[i].siPersonID != 0)
			{	
				HomeNaway	=	GUILDWAR_AWAY;
				SaveKillinfo(siSlot, HomeNaway,0, siDeathPersonID);//����ī��Ʈ�� �ø���
			}
		}
		if (HomeNaway == GUILDWAR_HOME ) 
		{
			pclKillPointAway[siSlot].SetKillPoint(1);
			SaveKillinfo(siSlot,GUILDWAR_AWAY,sikillerPersonID,0);// Įī��Ʈ�� �ø���.
			SendKill( siSlot, siKillerId,DeathID,HomeNaway );
			break;
		}
		else if(HomeNaway == GUILDWAR_AWAY )
		{
			pclKillPointHome[siSlot].SetKillPoint(1);
			SaveKillinfo(siSlot,GUILDWAR_HOME,sikillerPersonID,0);// Įī��Ʈ�� �ø���.
			SendKill( siSlot, siKillerId,DeathID,HomeNaway );
			break	;
		}

	}
}
void cltGuildHuntMapWarManager::SendKill(SI32 siSlot,SI32 KillerID,SI32 KilledID,SI32 HomeAway)
{
	cltServer* pclserver = (cltServer*)pclClient;

	cltCharCommon* pKiller = pclserver->pclCM->GetChar( KillerID);
	cltCharCommon* pKilled = pclserver->pclCM->GetChar( KilledID);

	TCHAR* killername =  (TCHAR*)pKiller->pclCI->clBI.GetName();
	TCHAR* killedname =  (TCHAR*)pKilled->pclCI->clBI.GetName();

	SI32 sikillerPersonID = pclserver->pclCM->CR[KillerID]->pclCI->GetPersonID();
	SI32 sikilledPersonID = pclserver->pclCM->CR[KilledID]->pclCI->GetPersonID();

	SI32 siHomeGuild = pclGuildMatchingListHome[siSlot].GetGuildUniqeue();
	SI32 siAwayGuild = pclGuildMatchingListAway[siSlot].GetGuildUniqeue();

	if(siHomeGuild <= 0 || siAwayGuild <= 0)	return	;

	cltGuildInfo * homeguildinfo = pclserver->pclGuildManager->GetGuildInfo(siHomeGuild);
	cltGuildInfo * awayguildinfo = pclserver->pclGuildManager->GetGuildInfo(siAwayGuild);

	for ( SI32 i = 0 ; i < MAX_GUILD_MEMBER_NUM; i++) {
		SI32 siHomePersonID = homeguildinfo->clMember[i].siPersonID	;
		SI32 siAwayPersonID = awayguildinfo->clMember[i].siPersonID	;

		SI32 siHomeID = pclserver->pclCM->GetIDFromPersonID( siHomePersonID	);
		SI32 siAwayID = pclserver->pclCM->GetIDFromPersonID( siAwayPersonID	);
		if ( pclserver->pclCM->IsValidID( siHomeID ) ) 
		{
			cltCharCommon* pHomerchar = pclserver->pclCM->GetChar( siHomeID)	;
			SI32 siHomeMApIndex = pHomerchar->GetMapIndex();
			if( siHomeMApIndex >= MAPINDEX_GUILDWARFIELD && siHomeMApIndex < MAPINDEX_GUILDWARFIELD+GUILDWAR_FIELDNUM )
			{
				cltGameMsgResponse_GuilHuntMapdWar_ADDKillPoint clinfo( killername,killedname,HomeAway );
				cltMsg clMsg(GAMEMSG_RESPONSE_GUILDHUNTMAPWAR_ADD_KILLPOINT, sizeof(clinfo), (BYTE*)&clinfo);
				pHomerchar->SendNetMsg( (sPacketHeader*)&clMsg );
			}
		}
		if ( pclserver->pclCM->IsValidID( siAwayID ) ) 
		{
			cltCharCommon* pAwaychar = pclserver->pclCM->GetChar( siAwayID)		;

			SI32 siAwayMApIndex = pAwaychar->GetMapIndex();

			if( siAwayMApIndex >= MAPINDEX_GUILDWARFIELD && siAwayMApIndex < MAPINDEX_GUILDWARFIELD+GUILDWAR_FIELDNUM )
			{
				cltGameMsgResponse_GuilHuntMapdWar_ADDKillPoint clinfo( killername, killedname, HomeAway );
				cltMsg clMsg(GAMEMSG_RESPONSE_GUILDHUNTMAPWAR_ADD_KILLPOINT, sizeof(clinfo), (BYTE*)&clinfo);
				pAwaychar->SendNetMsg( (sPacketHeader*)&clMsg );
			}
		}
	}
}
bool cltGuildHuntMapWarManager::CopyTempMatchinfList()
{
	cltServer* pclserver = (cltServer*)pclClient;
	bool bResult = false;
	// ����Ʈ�� �ѱ�� ���� ������� ������ ���� �ִ��� Ȯ���Ѵ�.ó����� ����Ʈ�� ������� ����.
	// ������ ���ٰ� �˷��ش�.
	SI32 siHomeUnique = pclGuildMatchingListHomeTemp[0].GetGuildUniqeue();
	SI32 siAwayUnique = pclGuildMatchingListAwayTemp[0].GetGuildUniqeue();
	if ( siHomeUnique == 0 && siAwayUnique == 0) 
	{
		for (SI32 siGuildSlot=0 ; siGuildSlot < MAX_GUILD_NUM; siGuildSlot++ ) 
		{
			SI32 siGuildUnique = pclGuildList[siGuildSlot].GetGuildUnique()	;
			if(siGuildUnique == 0 )	continue	;
			cltGuildInfo* pclGuildInfo = pclserver->pclGuildManager->GetGuildInfo( siGuildUnique )	;
			if(pclGuildInfo == NULL)	continue	;			
			for (SI32 siMember = 0 ; siMember < MAX_GUILD_MEMBER_NUM; siMember++) 
			{
				SI32 siPersonID = pclGuildInfo->clMember[siMember].siPersonID	;
				SI32 siID = pclserver->pclCM->GetIDFromPersonID(siPersonID);
				if (pclserver->pclCM->IsValidID(siID)) 
				{
					SI32 returnval = SRVAL_RETURN_CANNOTGUILDWAR_NOGUILD;// �ο� ��밡 �����ϴ�.
					pclserver->SendServerResponseMsg( 0, returnval,  0, 0, pclserver->pclCM->CR[siID]->GetCharUnique() );
				}
			}
			return bResult	;
		}
	}

	else
	{
		bResult =true;
	}
	// ����Ʈ�� ī�� �ϰ�
	// temp����Ʈ�� �����.
	for (SI32 slot = 0 ; slot < MAX_GUILDHUNTWAR_MAPNUM; slot++ ) 
	{
		SI32 siHomeUnique = pclGuildMatchingListHomeTemp[slot].GetGuildUniqeue();
		SI32 siAwayUnique = pclGuildMatchingListAwayTemp[slot].GetGuildUniqeue();
		if ( siHomeUnique >0 && siAwayUnique >0 ) {;
		pclGuildMatchingListHome[slot].SetGuild(siHomeUnique );
		pclGuildMatchingListHomeTemp[slot].Init();	;
		pclGuildMatchingListAway[slot].SetGuild( siAwayUnique);			
		pclGuildMatchingListAwayTemp[slot].Init();	;
		bResult = true	;
		}
	}
	return	bResult;
}
SI32 cltGuildHuntMapWarManager::GetInHuntMapWarPersonNumHome(SI32 slot)
{
	cltServer* pclserver = (cltServer*)pclClient;
	SI32 siHomepersonCount	=	0;
	SI32 siHomeuildUnique = pclGuildMatchingListHome[slot].GetGuildUniqeue()	;	// Ȩ ��� ����ũ
	if(siHomeuildUnique <= 0)	return	siHomepersonCount;
	cltGuildInfo* HomeGuildInfo = pclserver->pclGuildManager->GetGuildInfo(siHomeuildUnique);
	if(HomeGuildInfo == NULL)	return	siHomepersonCount;

	for ( SI32 siMemberCount = 0 ; siMemberCount < MAX_GUILD_MEMBER_NUM ; siMemberCount++ )
	{
		SI32 siHomeGuildMemberPersonID = HomeGuildInfo->clMember[ siMemberCount ].siPersonID	;
		SI32 siCharID_Home = pclserver->pclCM->GetIDFromPersonID( siHomeGuildMemberPersonID )	;
		cltCharCommon* pclChar_Home = pclserver->pclCM->GetChar(siCharID_Home)	;
		if( pclChar_Home != NULL)
		{
			if( pclClient->pclCM->IsValidID(pclChar_Home->GetID()))
			{
				SI32 siMapindexHome =  pclChar_Home->GetMapIndex();
				if ( siMapindexHome >= MAPINDEX_GUILDWARFIELD && siMapindexHome < MAPINDEX_GUILDWARFIELD+GUILDWAR_FIELDNUM )
				{
					siHomepersonCount	=	siHomepersonCount+1	;
				}
			}				
		}
	}
	return siHomepersonCount;
}
SI32 cltGuildHuntMapWarManager::GetInHuntMapWarPersonNumAway(SI32 slot)
{
	cltServer* pclserver = (cltServer*)pclClient;
	SI32 siAwaypersonCount	=	0;
	SI32 siAwayuildUnique = pclGuildMatchingListAway[slot].GetGuildUniqeue()	;	// Ȩ ��� ����ũ
	if(siAwayuildUnique <= 0)	return	siAwaypersonCount;
	cltGuildInfo* AwayGuildInfo = pclserver->pclGuildManager->GetGuildInfo(siAwayuildUnique);
	if( AwayGuildInfo == NULL)	return	siAwaypersonCount;
	for ( SI32 siMemberCount = 0 ; siMemberCount < MAX_GUILD_MEMBER_NUM ; siMemberCount++ )
	{
		SI32 siAwayGuildMemberPersonID = AwayGuildInfo->clMember[ siMemberCount ].siPersonID	;
		SI32 siCharID_Away = pclserver->pclCM->GetIDFromPersonID( siAwayGuildMemberPersonID )	;
		cltCharCommon* pclChar_Away = pclserver->pclCM->GetChar(siCharID_Away)	;
		if( pclChar_Away != NULL)
		{
			if( pclClient->pclCM->IsValidID(pclChar_Away->GetID()))
			{
				SI32 siMapindexAway =  pclChar_Away->GetMapIndex();
				if ( siMapindexAway >= MAPINDEX_GUILDWARFIELD && siMapindexAway < MAPINDEX_GUILDWARFIELD+GUILDWAR_FIELDNUM )
				{
					siAwaypersonCount	=	siAwaypersonCount+1	;
				}
			}				
		}
	}
	return siAwaypersonCount;
}

void cltGuildHuntMapWarManager::SendResultWarHome(SI32 slot,SI32 siWarResult)
{
	cltServer* pclserver = (cltServer*)pclClient;
	SI32 siHomeuildUnique = pclGuildMatchingListHome[slot].GetGuildUniqeue()	;	// Ȩ ��� ����ũ
	if(siHomeuildUnique <= 0)	return	;
	cltGuildInfo* HomeGuildInfo = pclserver->pclGuildManager->GetGuildInfo(siHomeuildUnique);
	if(HomeGuildInfo == NULL)	return	;

	for ( SI32 siMemberCount = 0 ; siMemberCount < MAX_GUILD_MEMBER_NUM ; siMemberCount++ )
	{
		SI32 siHomeGuildMemberPersonID = HomeGuildInfo->clMember[ siMemberCount ].siPersonID	;
		SI32 siCharID_Home = pclserver->pclCM->GetIDFromPersonID( siHomeGuildMemberPersonID )	;
		cltCharCommon* pclChar_Home = pclserver->pclCM->GetChar(siCharID_Home)	;
		if( pclChar_Home != NULL)
		{
			if( pclClient->pclCM->IsValidID(pclChar_Home->GetID()))
			{
				cltGameMsgResponse_GuilHuntMapdWar_End clinfo( siWarResult,pclEndWarStatus_Home[slot],pclEndWarStatus_Away[slot] );
				cltMsg clMsg(GAMEMSG_RESPONSE_GUILDHUNTMAPWAR_WAREND, sizeof(clinfo), (BYTE*)&clinfo);
				pclChar_Home->SendNetMsg((sPacketHeader*)&clMsg);
			}				
		}
	}
}
void cltGuildHuntMapWarManager::SendResultWarAway(SI32 slot,SI32 siWarResult)
{
	cltServer* pclserver = (cltServer*)pclClient;
	SI32 siAwayuildUnique = pclGuildMatchingListAway[slot].GetGuildUniqeue()	;	// Ȩ ��� ����ũ
	if(siAwayuildUnique <= 0)	return	;
	cltGuildInfo* AwayGuildInfo = pclserver->pclGuildManager->GetGuildInfo(siAwayuildUnique);
	if(AwayGuildInfo == NULL)	return	;
	for ( SI32 siMemberCount = 0 ; siMemberCount < MAX_GUILD_MEMBER_NUM ; siMemberCount++ )
	{
		SI32 siAwayGuildMemberPersonID = AwayGuildInfo->clMember[ siMemberCount ].siPersonID	;
		SI32 siCharID_Away = pclserver->pclCM->GetIDFromPersonID( siAwayGuildMemberPersonID )	;
		cltCharCommon* pclChar_Away = pclserver->pclCM->GetChar(siCharID_Away)	;
		if( pclChar_Away != NULL)
		{
			if( pclClient->pclCM->IsValidID(pclChar_Away->GetID()))
			{
				cltGameMsgResponse_GuilHuntMapdWar_End clinfo(siWarResult,pclEndWarStatus_Home[slot],pclEndWarStatus_Away[slot] );
				cltMsg clMsg(GAMEMSG_RESPONSE_GUILDHUNTMAPWAR_WAREND, sizeof(clinfo), (BYTE*)&clinfo);
				pclChar_Away->SendNetMsg((sPacketHeader*)&clMsg);
			}				
		}
	}
}
void cltGuildHuntMapWarManager::SaveKillinfo(SI32 siMapSlot,SI32 siHomeAway,SI32 siKillerPersonID,SI32 siDiePersonID)
{
	switch(siHomeAway) 
	{
	case GUILDWAR_HOME:
		{
			// �׿�����
			if ( siKillerPersonID > 0 ) 
			{
				SI32 siMemberSlot	=	0	;
				if( true == FindMeInWarStatus(siMapSlot,siHomeAway,siKillerPersonID, &siMemberSlot ) )	// �� �۽����̵� �̹� ��ϵǾ� �ִ�.
				{
					if( siKillerPersonID == pclWarStatus_Home[siMapSlot][siMemberSlot].GetPerosonID() )
					{
						pclWarStatus_Home[siMapSlot][siMemberSlot].AddKillPoint();
						return	;
					}
				}
				else
				{
					for ( SI32 siPersonSlot = 0; siPersonSlot < MAX_GUILD_MEMBER_NUM; siPersonSlot++) 
					{
						if( 0 == pclWarStatus_Home[siMapSlot][siPersonSlot].GetPerosonID() )
						{
							pclWarStatus_Home[siMapSlot][siPersonSlot].SetGuildUnique( pclGuildMatchingListHome[siMapSlot].GetGuildUniqeue());
							pclWarStatus_Home[siMapSlot][siPersonSlot].SetGuildPersonID( siKillerPersonID );
							pclWarStatus_Home[siMapSlot][siPersonSlot].AddKillPoint();
							return	;
						}
					}
				}
			}
			// �׾�����.
			if ( siDiePersonID > 0 ) 
			{
				SI32 siMemberSlot	=	0	;
				if( true == FindMeInWarStatus(siMapSlot,siHomeAway,siDiePersonID, &siMemberSlot ) )	// �� �۽����̵� �̹� ��ϵǾ� �ִ�.
				{
					if( siDiePersonID == pclWarStatus_Home[siMapSlot][siMemberSlot].GetPerosonID() )
					{
						pclWarStatus_Home[siMapSlot][siMemberSlot].AddDiePoint();
						return	;
					}
				}
				else
				{
					for ( SI32 siPersonSlot = 0; siPersonSlot < MAX_GUILD_MEMBER_NUM; siPersonSlot++) 
					{
						if( 0 == pclWarStatus_Home[siMapSlot][siPersonSlot].GetPerosonID() )
						{
							pclWarStatus_Home[siMapSlot][siPersonSlot].SetGuildUnique(pclGuildMatchingListHome[siMapSlot].GetGuildUniqeue());
							pclWarStatus_Home[siMapSlot][siPersonSlot].SetGuildPersonID( siDiePersonID );
							pclWarStatus_Home[siMapSlot][siPersonSlot].AddDiePoint();
							return;
						}
					}
				}
			}
		}
		break;
	case GUILDWAR_AWAY:
		{
			// �׿�����
			if ( siKillerPersonID > 0 ) 
			{
				SI32 siMemberSlot	=	0	;
				if( true == FindMeInWarStatus(siMapSlot,siHomeAway,siKillerPersonID, &siMemberSlot ) )	// �� �۽����̵� �̹� ��ϵǾ� �ִ�.
				{
					if( siKillerPersonID == pclWarStatus_Away[siMapSlot][siMemberSlot].GetPerosonID() )
					{
						pclWarStatus_Away[siMapSlot][siMemberSlot].AddKillPoint();
						return	;
					}
				}
				else
				{
					for ( SI32 siPersonSlot = 0; siPersonSlot < MAX_GUILD_MEMBER_NUM; siPersonSlot++) 
					{
						if( 0 == pclWarStatus_Away[siMapSlot][siPersonSlot].GetPerosonID() )
						{
							pclWarStatus_Away[siMapSlot][siPersonSlot].SetGuildUnique(pclGuildMatchingListAway[siMapSlot].GetGuildUniqeue());
							pclWarStatus_Away[siMapSlot][siPersonSlot].SetGuildPersonID( siKillerPersonID );
							pclWarStatus_Away[siMapSlot][siPersonSlot].AddKillPoint();
							return	;
						}
					}
				}
			}
			// �׾�����.
			if ( siDiePersonID > 0 ) 
			{
				SI32 siMemberSlot	=	0	;
				if( true == FindMeInWarStatus(siMapSlot,siHomeAway,siDiePersonID, &siMemberSlot ) )	// �� �۽����̵� �̹� ��ϵǾ� �ִ�.
				{
					if( siDiePersonID == pclWarStatus_Away[siMapSlot][siMemberSlot].GetPerosonID() )
					{
						pclWarStatus_Away[siMapSlot][siMemberSlot].AddDiePoint();
						return	;
					}
				}
				else
				{
					for ( SI32 siPersonSlot = 0; siPersonSlot < MAX_GUILD_MEMBER_NUM; siPersonSlot++) 
					{
						if( 0 == pclWarStatus_Away[siMapSlot][siPersonSlot].GetPerosonID() )
						{
							pclWarStatus_Away[siMapSlot][siPersonSlot].SetGuildUnique(pclGuildMatchingListAway[siMapSlot].GetGuildUniqeue());
							pclWarStatus_Away[siMapSlot][siPersonSlot].SetGuildPersonID( siDiePersonID );
							pclWarStatus_Away[siMapSlot][siPersonSlot].AddDiePoint();
							return;
						}
					}
				}
			}
		}
		break;
	}
}
void cltGuildHuntMapWarManager::MakeEndData()
{
	cltServer* pclserver = (cltServer*)pclClient;

	for (SI32 siMapSlot= 0; siMapSlot < MAX_GUILDHUNTWAR_MAPNUM; siMapSlot++) 
	{
		for (SI32 siMemberSlot = 0 ; siMemberSlot < MAX_GUILD_MEMBER_NUM; siMemberSlot ++) 
		{
			// ������ �ѱ��.
			SI32 siHomeGuildUnique = pclWarStatus_Home[siMapSlot][siMemberSlot].GetGuildUnique()	;
			SI32 siAwayGuildUnique = pclWarStatus_Away[siMapSlot][siMemberSlot].GetGuildUnique()	;
			if ( siHomeGuildUnique <= 0 || siAwayGuildUnique <= 0 )	continue	;
			cltGuildInfo* pHomeGuildInfo = pclserver->pclGuildManager->GetGuildInfo( siHomeGuildUnique ) ;
			cltGuildInfo* pAwayGuildInfo = pclserver->pclGuildManager->GetGuildInfo( siAwayGuildUnique ) ;
			if(pHomeGuildInfo!= NULL)
			{
				//�ִ´�
				pclEndWarStatus_Home[siMapSlot][siMemberSlot].SetGuildName( pHomeGuildInfo->GetName() )	;
			}
			if(pAwayGuildInfo!=NULL	)
			{
				//�ִ´�
				pclEndWarStatus_Away[siMapSlot][siMemberSlot].SetGuildName( pAwayGuildInfo->GetName() )	;
			}

			
			// ����� ������ �̸��� �ִ´�.
			SI32 siHomePersonID = pclWarStatus_Home[siMapSlot][siMemberSlot].GetPerosonID()	;
			SI32 siAwayPersonID = pclWarStatus_Away[siMapSlot][siMemberSlot].GetPerosonID()	;
			SI32 hId = pclserver->pclCM->GetIDFromPersonID( siHomePersonID);
			SI32 aId = pclserver->pclCM->GetIDFromPersonID( siAwayPersonID);
			cltCharCommon* pHomeChar = pclserver->pclCM->GetChar( hId)	;
			cltCharCommon* pAwayChar = pclserver->pclCM->GetChar( aId)	;
			if(pHomeChar != NULL )
			{
				//�ִ´�
				pclEndWarStatus_Home[siMapSlot][siMemberSlot].SetPersonName( (TCHAR*)pHomeChar->pclCI->clBI.GetName() )	;
				SI32 siKillPoint_Home = pclWarStatus_Home[siMapSlot][siMemberSlot].GetKillPoint();
				pclEndWarStatus_Home[siMapSlot][siMemberSlot].SetKillPoint( siKillPoint_Home)	;
				// ��������Ʈ
				SI32 siDiePoint_Home = pclWarStatus_Home[siMapSlot][siMemberSlot].GetiDieNum();
				pclEndWarStatus_Home[siMapSlot][siMemberSlot].SetDiePoint( siDiePoint_Home )	;

			}
			if (pAwayChar!= NULL )
			{
				//�ִ´�
				pclEndWarStatus_Away[siMapSlot][siMemberSlot].SetPersonName( (TCHAR*)pAwayChar->pclCI->clBI.GetName() )	;
				// ų����Ʈ
				SI32 siKillPoint_Awy = pclWarStatus_Away[siMapSlot][siMemberSlot].GetKillPoint();
				pclEndWarStatus_Away[siMapSlot][siMemberSlot].SetKillPoint( siKillPoint_Awy )	;
				// ��������Ʈ
				SI32 siDiePoint_Awy = pclWarStatus_Away[siMapSlot][siMemberSlot].GetiDieNum();

				pclEndWarStatus_Away[siMapSlot][siMemberSlot].SetDiePoint( siDiePoint_Awy )	;
			}
		}
	}
}
bool cltGuildHuntMapWarManager::FindMeInWarStatus( SI32 siMapSlot,SI32 Hone_Away,SI32 siPersonID,SI32* MemberSlot )
{
	bool bResult = false ;
	switch( Hone_Away ) 
	{
	case GUILDWAR_HOME :
		{
			for (SI32 siMemberSlot = 0 ; siMemberSlot < MAX_GUILD_MEMBER_NUM; siMemberSlot++) 
			{
				SI32 Home = pclWarStatus_Home[siMapSlot][siMemberSlot].GetPerosonID()	;
				if( siPersonID ==  Home)
				{
					bResult = true	;
					*MemberSlot = siMemberSlot;
					break;
				}
			}
		}
		break;
	case GUILDWAR_AWAY :
		{
			for (SI32 siMemberSlot = 0 ; siMemberSlot < MAX_GUILD_MEMBER_NUM; siMemberSlot++) 
			{
				SI32 Away = pclWarStatus_Away[siMapSlot][siMemberSlot].GetPerosonID() ;
				if( siPersonID ==  Away)
				{
					bResult = true	;
					*MemberSlot = siMemberSlot;
					break;
				}
			}
		}
		break;
	}
	return bResult	;
}
bool cltGuildHuntMapWarManager::FindMatchingList(SI32 GuildUnique )
{
	bool bResult = false ;
	for( SI32 siSlot = 0 ; siSlot < MAX_GUILDHUNTWAR_MAPNUM; siSlot++)
	{
		SI32 siHome = pclGuildMatchingListHome[siSlot].GetGuildUniqeue()	;
		SI32 siAway = pclGuildMatchingListAway[siSlot].GetGuildUniqeue()	;
		if (GuildUnique == siHome|| GuildUnique ==siAway ) 
		{
			bResult = true ;
			return	bResult;
		}
	}
	return	bResult;
}
// ��������� �׾��� ��� ���� ó���� ���ش�.
bool cltGuildHuntMapWarManager::GuildWarRevive(SI32 personID)
{
	cltServer* pclserver = (cltServer*)pclClient;


	cltCharServer* pclchar = pclserver->pclCM->GetCharServer( pclClient->pclCM->GetIDFromPersonID( personID ) );
	if( pclchar == NULL ) return false	;

	// ���� ������ �ش�
	pclchar->siKilledMode = KILLEDMODE_GUILDWAR;
	// ������� ä���. 
	pclchar->pclCI->clIP.SetLife( pclchar->clPB.GetMaxLife() );
	// ������ ä���ش�
	pclchar->pclCI->clIP.SetMana( pclchar->clPB.GetMaxMana() );

	// ���� ���·� �����.
	pclchar->SetCurrentOrder( ORDER_REVIVE );

	SI32 xPos, yPos;
	xPos = yPos = 0;

	for ( SI32 i=0; i < MAX_GUILDHUNTWAR_MAPNUM ; i++ )
	{
		SI32 siHomeuildUnique = pclGuildMatchingListHome[i].GetGuildUniqeue()	;
		SI32 siAwayuildUnique = pclGuildMatchingListAway[i].GetGuildUniqeue()	;
		if ( siHomeuildUnique <= 0 || siAwayuildUnique <= 0)			continue	;

		cltGuildInfo* HomeGuildInfo = pclserver->pclGuildManager->GetGuildInfo(siHomeuildUnique)	;
		cltGuildInfo* AwayGuildInfo = pclserver->pclGuildManager->GetGuildInfo(siAwayuildUnique)	;

		for ( SI32 siMemberCount = 0 ; siMemberCount < MAX_GUILD_MEMBER_NUM ; siMemberCount++ )
		{
			SI32 siHomeGuildMemberPersonID = HomeGuildInfo->clMember[ siMemberCount ].siPersonID	;
			SI32 siAwayGuildMemberPersonID = AwayGuildInfo->clMember[ siMemberCount ].siPersonID	;
			if ( personID == siHomeGuildMemberPersonID ) 
			{
				SI32 siRand = rand()%4;
				xPos = Const_HomePos[ siRand * 2 ];
				yPos = Const_HomePos[ siRand * 2 + 1];
				cltWarpInfo clWarpInfo(1 , pclchar->GetMapIndex(), false, false, xPos, yPos, -1, -1);

				pclchar->SetWarpInfo(&clWarpInfo, 2200);
				pclchar->Warp();
				m_HomePersonDeadClock[i][siMemberCount]	=	pclClient->CurrentClock;// ���� �ð� ���

				pclchar->	SendDB_PosLifeMana();	

				// Ŭ���̾�Ʈ�� ������Ʈ �Ѵ�. 
				pclchar->SetUpdateSwitch(UPDATE_IP, true, 0);

				return true;
			}
			else if( personID == siAwayGuildMemberPersonID )
			{
				SI32 siRand = rand()%4;
				xPos = Const_AwayPos[ siRand * 2 ];
				yPos = Const_AwayPos[ siRand * 2 + 1];
				cltWarpInfo clWarpInfo(1 , pclchar->GetMapIndex(), false, false, xPos, yPos, -1, -1);
				pclchar->SetWarpInfo(&clWarpInfo, 2200);
				pclchar->Warp();
				m_AwayPersonDeadClock[i][siMemberCount]	=	pclClient->CurrentClock;	// ���� �ð� ���
				pclchar->SendDB_PosLifeMana();	

				// Ŭ���̾�Ʈ�� ������Ʈ �Ѵ�. 
				pclchar->SetUpdateSwitch(UPDATE_IP, true, 0);

				return true;
			}
		}
	}
	return false;
}

bool cltGuildHuntMapWarManager::IsGod( SI32 personID )
{
	cltServer* pclserver = (cltServer*)pclClient;

	cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->GetCharServer(pclClient->pclCM->GetIDFromPersonID( personID ));
	if(pclchar == NULL)	return	false ;

	for ( SI32 i=0; i < MAX_GUILDHUNTWAR_MAPNUM ; i++ )
	{
		SI32 siHomeuildUnique = pclGuildMatchingListHome[i].GetGuildUniqeue()	;
		SI32 siAwayuildUnique = pclGuildMatchingListAway[i].GetGuildUniqeue()	;
		if ( siHomeuildUnique <= 0 || siAwayuildUnique <= 0)			continue	;

		cltGuildInfo* HomeGuildInfo = pclserver->pclGuildManager->GetGuildInfo(siHomeuildUnique)	;
		cltGuildInfo* AwayGuildInfo = pclserver->pclGuildManager->GetGuildInfo(siAwayuildUnique)	;

		for ( SI32 siMemberCount = 0 ; siMemberCount < MAX_GUILD_MEMBER_NUM ; siMemberCount++ )
		{
			SI32 siHomeGuildMemberPersonID = HomeGuildInfo->clMember[ siMemberCount ].siPersonID	;
			SI32 siAwayGuildMemberPersonID = AwayGuildInfo->clMember[ siMemberCount ].siPersonID	;
			if ( personID == siHomeGuildMemberPersonID ) 
			{
				if( TABS(pclClient->CurrentClock - m_HomePersonDeadClock[i][siMemberCount]) < GUILDHUNTMAPGODTIME )
					return true;
				else 
					return false;
			}
			if ( personID == siAwayGuildMemberPersonID ) 
			{
				if( TABS(pclClient->CurrentClock - m_AwayPersonDeadClock[i][siMemberCount]) < GUILDHUNTMAPGODTIME )
					return true;
				else 
					return false;
			}
		}
	}
	return false;
}