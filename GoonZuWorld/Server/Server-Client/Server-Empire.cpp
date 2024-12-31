#include "Char\CharManager\CharManager.h"
#include "..\Server\Server.h"

#include "..\..\..\DBManager\GameDBManager_World\DBMsg.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Empire.h"

#include "MsgRval-Define.h"
#include "Msg\MsgType-Empire.h"

#include "../Empire/EmpireManager.h"

#include "..\..\Server\Rank\Rank.h"
#include "../../CommonLogic/MsgType-Structure.h"
//#include "../../../StrBaseDlg/StrBaseDlg.h"
#include "../../CommonLogic/Cityhall/Cityhall.h"


void cltServer::DoMsg_GAMEMSG_REQUEST_CREATEEMPIRE( cltMsg* pclMsg, SI32 id )
{
	if( pclCM->IsValidID( id ) == false )
		return;

	if( 0 < pclCM->CR[id]->pclCI->clBI.clEmpireInfo.GetEmpireUnique() )
	{
		return;
	}

	SI32 villageUnique = pclCM->CR[id]->pclCI->clCharRank.GetVillageUnique();

	if( RANKTYPE_CITYHALL != pclCM->CR[id]->pclCI->clCharRank.GetRankType() )
		return;

	cltRank* pRank = pclRankManager->GetRank( RANKTYPE_CITYHALL, villageUnique );

	if( NULL == pRank )
		return;

	SI32 personID = pclCM->CR[id]->pclCI->GetPersonID();
	if( false == pclRankManager->IsRank( personID, &pRank->clRank) )
		return;

	cltStrInfo *pStrInfo = GetStrInfo( villageUnique, RANKTYPE_CITYHALL );
	if( NULL == pStrInfo )
		return;

	if( pStrInfo->clCityhallStrInfo.clProfitMoney.itMoney < NEED_CREATEEMPIRE_MONEY )
		return;


	sDBRequest_CreateEmpire clCreateEmpire( id, villageUnique, NEED_CREATEEMPIRE_MONEY );
	pclGameDBProcess->SendMsg( (sPacketHeader *)&clCreateEmpire) ;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_DESTROYEMPIRE( cltMsg* pclMsg, SI32 id )
{
}

void cltServer::DoMsg_GAMEMSG_REQUEST_INVITEEMPIRE( cltMsg* pclMsg, SI32 id )
{
	if( false == pclCM->IsValidID( id ) )
		return;

	cltGameMsgRequest_InviteEmpire* pclInfo = (cltGameMsgRequest_InviteEmpire*)pclMsg->cData;

	/// �������� �ʴ��� ���
	SI32 toID = pclCM->GetIDFromName( pclInfo->szUserName );

	if( false == pclCM->IsValidID( toID ) )
	{
		/// ���� ������� ����ó��
		return;
	}

	SI32 fromPersonID = pclCM->CR[id]->pclCI->GetPersonID();
	SI32 empireUnique = pclCM->CR[id]->pclCI->clBI.clEmpireInfo.GetEmpireUnique();
	SI32 emperorVillageUnique = pclEmpireManager->GetEmperorVillageUniqueByEmpireUnique( empireUnique );

	if( cltGameMsgRequest_InviteEmpire::VILLAGE == pclInfo->siInviteType )
	{
		if( 0 < pclCM->CR[toID]->pclCI->clBI.clEmpireInfo.GetEmpireUnique() )
		{
			/// �̹� ������ �ִ� ������ �ʴ��� �� ���� ����ó��
			return;
		}

		if( RANKTYPE_CITYHALL != pclCM->CR[toID]->pclCI->clCharRank.GetRankType() )
		{
			/// ���� ������� �ʴ� ���� �� �ִ�
			return;
		}

		/// �ʴ� ���� ������� ������
		cltGameMsgResponse_InviteEmpire clInviteEmpire( pclInfo->siInviteType, empireUnique, fromPersonID, emperorVillageUnique );
		cltMsg clMsg(GAMEMSG_RESPONSE_INVITEEMPIRE, sizeof(clInviteEmpire), (BYTE*)&clInviteEmpire);
		pclCM->CR[toID]->SendNetMsg((sPacketHeader*)&clMsg);

		/// �ʴ��� ������� ������
		cltGameMsgResponse_InviteEmpire clInviteEmpire2( cltGameMsgResponse_InviteEmpire::EMPEROR, empireUnique, fromPersonID, emperorVillageUnique );
		cltMsg clMsg2(GAMEMSG_RESPONSE_INVITEEMPIRE, sizeof(clInviteEmpire2), (BYTE*)&clInviteEmpire2);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg2);
	}
	else if( cltGameMsgRequest_InviteEmpire::GUILD == pclInfo->siInviteType )
	{
		if( 0 < pclCM->CR[toID]->pclCI->clBI.clGuildRank.siEmpireUnique )
		{
			/// �̹� ��尡 ������ ���ԵǾ� �ִ� �����̹Ƿ� ����ó��
			return;
		}

		if( GUILDRANKTYPE_MASTER != pclCM->CR[toID]->pclCI->clBI.clGuildRank.GetRankType() )
		{
			/// ����常 �ʴ� ���� �� �ִ�
			return;
		}

		/// �ʴ� ���� ������� ������
		cltGameMsgResponse_InviteEmpire clInviteEmpire( pclInfo->siInviteType, empireUnique, fromPersonID, emperorVillageUnique );
		cltMsg clMsg(GAMEMSG_RESPONSE_INVITEEMPIRE, sizeof(clInviteEmpire), (BYTE*)&clInviteEmpire);
		pclCM->CR[toID]->SendNetMsg((sPacketHeader*)&clMsg);

		/// �ʴ��� ������� ������
		cltGameMsgResponse_InviteEmpire clInviteEmpire2( cltGameMsgResponse_InviteEmpire::EMPEROR, empireUnique, fromPersonID, emperorVillageUnique );
		cltMsg clMsg2(GAMEMSG_RESPONSE_INVITEEMPIRE, sizeof(clInviteEmpire2), (BYTE*)&clInviteEmpire2);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg2);
	}
}

void cltServer::DoMsg_GAMEMSG_REQUEST_JOINEMPIRE( cltMsg* pclMsg, SI32 id )
{
	if( pclCM->IsValidID( id ) == false )
		return;

	cltGameMsgRequest_JoinEmpire* pclInfo = (cltGameMsgRequest_JoinEmpire*)pclMsg->cData;

    SI32 fromID = pclCM->GetIDFromPersonID( pclInfo->siFromPersonID );

	/// ������ ���� ����
	if( cltGameMsgRequest_JoinEmpire::VILLAGE == pclInfo->siInviteType )
	{
		if( 0 < pclCM->CR[id]->pclCI->clBI.clEmpireInfo.GetEmpireUnique() )
			return;

		if( RANKTYPE_CITYHALL != pclCM->CR[id]->pclCI->clCharRank.GetRankType() )
		{
			/// ���� ������� �ʴ� ���� �� �ִ�
			return;
		}

		SI32 villageUnique = pclCM->CR[id]->pclCI->clCharRank.GetVillageUnique();;
		sDBRequest_JoinEmpire clJoinEmpire( fromID, id, pclInfo->siInviteType, pclInfo->siEmpireUnique, villageUnique, 0 );
		pclGameDBProcess->SendMsg( (sPacketHeader *)&clJoinEmpire);
	}
	/// ���� ���� ����
	else if( cltGameMsgRequest_JoinEmpire::GUILD == pclInfo->siInviteType )
	{
		if( 0 < pclCM->CR[id]->pclCI->clBI.clGuildRank.siEmpireUnique )
			return;

		if( GUILDRANKTYPE_MASTER != pclCM->CR[id]->pclCI->clBI.clGuildRank.GetRankType() )
		{
			/// ����常 �ʴ� ���� �� �ִ�
			return;
		}

		SI32 guildUnique = pclCM->CR[id]->pclCI->clBI.clGuildRank.GetGuildUnitIndex();
		sDBRequest_JoinEmpire clJoinEmpire( fromID, id, pclInfo->siInviteType, pclInfo->siEmpireUnique, 0, guildUnique );
		pclGameDBProcess->SendMsg( (sPacketHeader *)&clJoinEmpire);
	}
}

void cltServer::DoMsg_GAMEMSG_REQUEST_SECEDEEMPIRE( cltMsg* pclMsg, SI32 id )
{
	if( pclCM->IsValidID( id ) == false )
		return;

	cltGameMsgRequest_SecedeEmpire* pclInfo = (cltGameMsgRequest_SecedeEmpire*)pclMsg->cData;

	SI32 villageUnique = 0;
	SI32 guildUnique = 0;
	SI32 empireUnique = 0; 
	bool secedeEmpireByEmperor = false;
	SI32 secedeType = sDBRequest_SecedeEmpire::VILLAGE;

	if( cltGameMsgRequest_SecedeEmpire::EMPEROR == pclInfo->siSecedeType )
	{
		empireUnique = pclCM->CR[id]->pclCI->clBI.clEmpireInfo.GetEmpireUnique();
		villageUnique = pclInfo->siVillageUnique;
		guildUnique = pclInfo->siGuildUnique;
		secedeEmpireByEmperor = true;

		if( 0 < villageUnique )
		{
			secedeType = sDBRequest_SecedeEmpire::VILLAGE;
			if( false == pclEmpireManager->IsInVillageUnique( empireUnique, villageUnique ) )
				return;
		}
		else if( 0 < guildUnique )
		{
			secedeType = sDBRequest_SecedeEmpire::GUILD;
			if( false == pclEmpireManager->IsInGuildUnique( empireUnique, villageUnique ) )
				return;
		}
		
	}
	else if( cltGameMsgRequest_SecedeEmpire::VILLAGE_CHIEF == pclInfo->siSecedeType )
	{
		secedeType = sDBRequest_SecedeEmpire::VILLAGE;
		empireUnique = pclCM->CR[id]->pclCI->clBI.clEmpireInfo.GetEmpireUnique();
		villageUnique = pclCM->CR[id]->pclCI->clCharRank.GetVillageUnique();
		secedeEmpireByEmperor = false;

		if( false == pclEmpireManager->IsInVillageUnique( empireUnique, villageUnique ) )
			return;
	}
	else if( cltGameMsgRequest_SecedeEmpire::GUILD_CHIEF == pclInfo->siSecedeType )
	{
		secedeType = sDBRequest_SecedeEmpire::GUILD;
		empireUnique = pclCM->CR[id]->pclCI->clBI.clGuildRank.GetEmpireUnique();
		guildUnique = pclCM->CR[id]->pclCI->clBI.clGuildRank.GetGuildUnitIndex();
		secedeEmpireByEmperor = false;

		if( false == pclEmpireManager->IsInGuildUnique( empireUnique, villageUnique ) )
			return;
	}

	sDBRequest_SecedeEmpire clJoinEmpire( id, secedeEmpireByEmperor, secedeType, empireUnique, villageUnique, guildUnique );
	pclGameDBProcess->SendMsg( (sPacketHeader *)&clJoinEmpire);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_EMPIREINFO( cltMsg* pclMsg, SI32 id )
{
	if( pclCM->IsValidID( id ) == false )
		return;

	cltGameMsgRequest_EmpireInfo* pclInfo = (cltGameMsgRequest_EmpireInfo*)pclMsg->cData;

	if( true == pclInfo->bVillageChief )
	{
		/// ���� ���� ������ ������ ��쿡�� �ش� ��������ũ ������ ������ ã�Ƽ� �����ش�.
		CEmpireUnitInfo* empireUnitInfo = pclEmpireManager->FindEmpire( pclCM->CR[id]->pclCI->clBI.clEmpireInfo.GetEmpireUnique() );

		if( NULL == empireUnitInfo )
			return;

		TCHAR villageChiefName[MAX_EMPIRE_IN_VILLAGE][MAX_PLAYER_NAME] = {'\0'};
		SI32  residentNumber[MAX_EMPIRE_IN_VILLAGE] = {0, };

		TCHAR guildChiefName[MAX_EMPIRE_IN_GUILD][MAX_PLAYER_NAME] = {'\0'};
		SI32  guildMemberNumber[MAX_EMPIRE_IN_GUILD] = {0, };

		cltRank* pclRank;
		for( SI32 i = 0; i < MAX_EMPIRE_IN_VILLAGE; ++i )
		{
			SI32 villageUnique = empireUnitInfo->GetVillageUnique(i);
			if( 0 < villageUnique )
			{
				cltVillageInfo *pVillageInfo = pclClient->pclVillageManager->pclVillageInfo[ villageUnique ];
				if( pVillageInfo == NULL ) continue;

				pclRank = pclRankManager->GetRank( RANKTYPE_CITYHALL, villageUnique );

				if( pclRank )
				{
					if( pclRank->GetPersonID() )
					{
						StringCchCopy( villageChiefName[i], MAX_PLAYER_NAME, pclRank->GetName() );
					} 
					else
					{
						StringCchCopy( villageChiefName[i], MAX_PLAYER_NAME, "" );
					}
				}
				else
				{
					StringCchCopy( villageChiefName[i], MAX_PLAYER_NAME, "" );
				}

				cltStrInfo *pStrInfo = pclVillageManager->pclCityHallManager->GetStrInfo( villageUnique );

				if( NULL != pStrInfo )
				{
					residentNumber[i] = pStrInfo->clCityhallStrInfo.siResidentNum;
				}
				else
				{
					residentNumber[i] = 0;
				}
			}
			else
			{
				StringCchCopy( villageChiefName[i], 20, "" );
				residentNumber[i] = 0;
			}
		}

		for( SI32 i = 0; i < MAX_EMPIRE_IN_GUILD; ++i )
		{
			SI32 guildUnique = empireUnitInfo->GetGuildUnique(i);
			if( 0 < guildUnique )
			{
				cltGuildInfo* guildInfo = pclGuildManager->GetGuildInfo(guildUnique);
				if( guildInfo == NULL ) 
				{
					StringCchCopy( guildChiefName[i], MAX_PLAYER_NAME, "" );
					continue;
				}

				for( SI32 j = 0; j < MAX_GUILD_MEMBER_NUM; ++j )
				{
					if( GUILDRANKTYPE_MASTER == guildInfo->clMember[j].siType )				
					{
						StringCchCopy( guildChiefName[i], MAX_PLAYER_NAME,guildInfo->clMember[j].szCharName );
						break;
					}
				}

				guildMemberNumber[i] = guildInfo->GetMemberNum();
			}
		}

		cltGameMsgResponse_EmpireInfo clEmpireInfo( pclInfo->bRequestFirst,  pclInfo->bVillageChief, NULL, empireUnitInfo, villageChiefName, residentNumber, guildChiefName, guildMemberNumber );
		cltMsg clMsg(GAMEMSG_RESPONSE_EMPIREINFO, sizeof(clEmpireInfo), (BYTE*)&clEmpireInfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	}
	else
	{
		/// Ŭ���̾�Ʈ���� ó�� ��û�϶��� ��ü ������ ���� ���� ����ũ�� ó�� ������� ������ ������ ������.
		if( true == pclInfo->bRequestFirst )
		{
			CEmpireUnitInfo* empireUnitInfo = pclEmpireManager->FirstEmpire();

			if( NULL == empireUnitInfo )
				return;

			TCHAR villageChiefName[MAX_EMPIRE_IN_VILLAGE][MAX_PLAYER_NAME] = {'\0'};
			SI32  residentNumber[MAX_EMPIRE_IN_VILLAGE] = {0, };

			TCHAR guildChiefName[MAX_EMPIRE_IN_GUILD][MAX_PLAYER_NAME] = {'\0'};
			SI32  guildMemberNumber[MAX_EMPIRE_IN_GUILD] = {0, };

			cltRank* pclRank;
			for( SI32 i = 0; i < MAX_EMPIRE_IN_VILLAGE; ++i )
			{
				SI32 villageUnique = empireUnitInfo->GetVillageUnique(i);
				if( 0 < villageUnique )
				{
					cltVillageInfo *pVillageInfo = pclClient->pclVillageManager->pclVillageInfo[ villageUnique ];
					if( pVillageInfo == NULL ) continue;

					pclRank = pclRankManager->GetRank( RANKTYPE_CITYHALL, villageUnique );

					if( pclRank )
					{
						if( pclRank->GetPersonID() )
						{
							StringCchCopy( villageChiefName[i], MAX_PLAYER_NAME, pclRank->GetName() );
						} 
						else
						{
							StringCchCopy( villageChiefName[i], MAX_PLAYER_NAME, "" );
						}
					}
					else
					{
						StringCchCopy( villageChiefName[i], MAX_PLAYER_NAME, "" );
					}

					cltStrInfo *pStrInfo = pclVillageManager->pclCityHallManager->GetStrInfo( villageUnique );

					if( NULL != pStrInfo )
					{
						residentNumber[i] = pStrInfo->clCityhallStrInfo.siResidentNum;
					}
					else
					{
						residentNumber[i] = 0;
					}
				}
				else
				{
					StringCchCopy( villageChiefName[i], 20, "" );
					residentNumber[i] = 0;
				}
			}

			for( SI32 i = 0; i < MAX_EMPIRE_IN_GUILD; ++i )
			{
				SI32 guildUnique = empireUnitInfo->GetGuildUnique(i);
				if( 0 < guildUnique )
				{
					cltGuildInfo* guildInfo = pclGuildManager->GetGuildInfo(guildUnique);
					if( guildInfo == NULL ) 
					{
						StringCchCopy( guildChiefName[i], MAX_PLAYER_NAME, "" );
						continue;
					}

					for( SI32 j = 0; j < MAX_GUILD_MEMBER_NUM; ++j )
					{
						if( GUILDRANKTYPE_MASTER == guildInfo->clMember[j].siType )				
						{
							StringCchCopy( guildChiefName[i], MAX_PLAYER_NAME,guildInfo->clMember[j].szCharName );
							break;
						}
					}

					guildMemberNumber[i] = guildInfo->GetMemberNum();
				}
			}

			SI32 villageUnique[MAX_EMPIRENUMBER];
			for( SI32 i = 0; i < MAX_EMPIRENUMBER; ++i )
			{
				SI32 emperprVillageUnique = pclEmpireManager->GetEmperorVillageUniqueByIndex(i);
				if( 0 < emperprVillageUnique )
				{
					villageUnique[i] = emperprVillageUnique;
				}
				else
				{
					villageUnique[i] = 0;
				}
			}

			cltGameMsgResponse_EmpireInfo clEmpireInfo( pclInfo->bRequestFirst,  pclInfo->bVillageChief, villageUnique, empireUnitInfo, villageChiefName, residentNumber, guildChiefName, guildMemberNumber );
			cltMsg clMsg(GAMEMSG_RESPONSE_EMPIREINFO, sizeof(clEmpireInfo), (BYTE*)&clEmpireInfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		}
		else
		{
			/// ���� ���� ������ ������ ��쿡�� �ش� ��������ũ ������ ������ ã�Ƽ� �����ش�.
			SI32 empireUnique = pclEmpireManager->FindEmpireUnique( pclInfo->siVillageUnique );
			CEmpireUnitInfo* empireUnitInfo = pclEmpireManager->FindEmpire( empireUnique );

			if( NULL == empireUnitInfo )
				return;

			TCHAR villageChiefName[MAX_EMPIRE_IN_VILLAGE][MAX_PLAYER_NAME] = {'\0'};
			SI32  residentNumber[MAX_EMPIRE_IN_VILLAGE] = {0, };

			TCHAR guildChiefName[MAX_EMPIRE_IN_GUILD][MAX_PLAYER_NAME] = {'\0'};
			SI32  guildMemberNumber[MAX_EMPIRE_IN_GUILD] = {0, };

			cltRank* pclRank;
			for( SI32 i = 0; i < MAX_EMPIRE_IN_VILLAGE; ++i )
			{
				SI32 villageUnique = empireUnitInfo->GetVillageUnique(i);
				if( 0 < villageUnique )
				{
					cltVillageInfo *pVillageInfo = pclClient->pclVillageManager->pclVillageInfo[ villageUnique ];
					if( pVillageInfo == NULL ) continue;

					pclRank = pclRankManager->GetRank( RANKTYPE_CITYHALL, villageUnique );

					if( pclRank )
					{
						if( pclRank->GetPersonID() )
						{
							StringCchCopy( villageChiefName[i], MAX_PLAYER_NAME, pclRank->GetName() );
						} 
						else
						{
							StringCchCopy( villageChiefName[i], MAX_PLAYER_NAME, "" );
						}
					}
					else
					{
						StringCchCopy( villageChiefName[i], MAX_PLAYER_NAME, "" );
					}

					cltStrInfo *pStrInfo = pclVillageManager->pclCityHallManager->GetStrInfo( villageUnique );

					if( NULL != pStrInfo )
					{
						residentNumber[i] = pStrInfo->clCityhallStrInfo.siResidentNum;
					}
					else
					{
						residentNumber[i] = 0;
					}
				}
				else
				{
					StringCchCopy( villageChiefName[i], 20, "" );
					residentNumber[i] = 0;
				}
			}

			for( SI32 i = 0; i < MAX_EMPIRE_IN_GUILD; ++i )
			{
				SI32 guildUnique = empireUnitInfo->GetGuildUnique(i);
				if( 0 < guildUnique )
				{
					cltGuildInfo* guildInfo = pclGuildManager->GetGuildInfo(guildUnique);
					if( guildInfo == NULL ) 
					{
						StringCchCopy( guildChiefName[i], MAX_PLAYER_NAME, "" );
						continue;
					}

					for( SI32 j = 0; j < MAX_GUILD_MEMBER_NUM; ++j )
					{
						if( GUILDRANKTYPE_MASTER == guildInfo->clMember[j].siType )				
						{
							StringCchCopy( guildChiefName[i], MAX_PLAYER_NAME,guildInfo->clMember[j].szCharName );
							break;
						}
					}

					guildMemberNumber[i] = guildInfo->GetMemberNum();
				}
			}

			cltGameMsgResponse_EmpireInfo clEmpireInfo( pclInfo->bRequestFirst,  pclInfo->bVillageChief, NULL, empireUnitInfo, villageChiefName, residentNumber, guildChiefName, guildMemberNumber );
			cltMsg clMsg(GAMEMSG_RESPONSE_EMPIREINFO, sizeof(clEmpireInfo), (BYTE*)&clEmpireInfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		}
	}
}

void cltServer::DoMsg_GAMEMSG_REQUEST_SETEMPIREMONEY( cltMsg* pclMsg, SI32 id )
{
	if( pclCM->IsValidID( id ) == false )
		return;

	cltGameMsgRequest_SetEmpireMoney* pclInfo = (cltGameMsgRequest_SetEmpireMoney*)pclMsg->cData;

	SI32 villageUnique = pclCM->CR[id]->pclCI->clCharRank.GetVillageUnique();

	if( RANKTYPE_CITYHALL != pclCM->CR[id]->pclCI->clCharRank.GetRankType() )
		return;

	SI32 empireUnique = pclCM->CR[id]->pclCI->clBI.clEmpireInfo.GetEmpireUnique();

	if( 0 >= empireUnique )
	{
		/// ������ ����
		return;
	}

	SI32 addmoney = pclInfo->siInputMoney;
	
	cltStrInfo* pclStr = pclCityHallManager->GetStrInfo( villageUnique );

	if( NULL == pclStr )
	{
		/// �ǹ� ������ ����
		return;
	}
	
	if( addmoney > pclStr->clCityhallStrInfo.clProfitMoney.itMoney )
	{
		/// ���ͱ� ���ٴ� ���� �� �� ����
		return;
	}

	sDBRequest_SetEmpireMoney clSetEmpireMoney( sDBRequest_SetEmpireMoney::USER, id, empireUnique, villageUnique, addmoney );
	pclGameDBProcess->SendMsg( (sPacketHeader *)&clSetEmpireMoney);
}

