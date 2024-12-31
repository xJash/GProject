#include "../CommonLogic/CommonLogic.h"
#include "Char/CharManager/CharManager.h"

#include "../Server/Server.h"

#include "../../../DBManager/GameDBManager_World/DBMsg-Guild.h"

#include "Guild/Guild.h"

#include "MsgRval-Define.h"
#include "MsgType-Guild.h"

void cltServer::DoMsg_GAMEMSG_REQUEST_GUILD_CREATEGUILD( cltMsg*pclMsg,SI32 id )
{
	cltGameMsgRequest_Guild_CreateGuild * pclinfo = (cltGameMsgRequest_Guild_CreateGuild*)pclMsg->cData;

	if( pclCM->IsValidID( id ) == false )
		return ;

	if ( pclVillageManager->IsValidVillage(pclinfo->siVillageUnique) == false )
		return ;

	if ( pclVillageManager->IsThereStructure(pclinfo->siVillageUnique,RANKTYPE_GUILD) == FALSE )
		return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL )
		return ;

	if ( pclchar->pclCI->clIP.GetLevel() < MIN_GUILD_MASTER_LEVEL )
		return ;

	if ( pclchar->pclCI->clBI.clGuildRank.siGuildUnitIndex != 0 )
		return ;

	cltDate clDate ;
	clDate.Set(&pclTime->clDate);

	sDBRequest_Guild_CreateGuild clMsg(pclchar->pclCI->GetPersonID(),id,pclinfo->siVillageUnique,pclinfo->szGuildName,&clDate);
	pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&clMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_GUILD_DESTROYGUILD( cltMsg*pclMsg,SI32 id )
{
	cltGameMsgRequest_Guild_DestroyGuild * pclinfo = (cltGameMsgRequest_Guild_DestroyGuild*)pclMsg->cData;

	if( pclCM->IsValidID( id ) == false )
		return ;

	if ( pclVillageManager->IsValidVillage(pclinfo->siVillageUnique) == false )
		return ;

	if ( pclVillageManager->IsThereStructure(pclinfo->siVillageUnique,RANKTYPE_GUILD) == FALSE )
		return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL )
		return ;

	if ( pclchar->pclCI->clBI.clGuildRank.siGuildUnitIndex != pclinfo->siGuildUnique )
		return ;

	// ��û�������� ��常 �ı��Ѵ�.
	cltGuildInfo* pclGuild = pclGuildManager->GetGuildInfo(pclinfo->siGuildUnique);
	if ( pclGuild == NULL ) return ;

	if ( pclGuild->uiConfirm != GUILDSTATUS_STANDING )
		return ;

	sDBRequest_Guild_DestroyGuild clMsg(pclchar->pclCI->GetPersonID(),id,pclinfo->siGuildUnique,pclinfo->siVillageUnique);
	pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&clMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_GUILD_JOINGUILD( cltMsg*pclMsg,SI32 id )
{
	cltGameMsgRequest_Guild_JoinGuild * pclinfo = (cltGameMsgRequest_Guild_JoinGuild*)pclMsg->cData;

	if( pclCM->IsValidID( id ) == false )
		return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL )
		return ;

	if ( pclchar->pclCI->clBI.clGuildRank.siGuildUnitIndex != 0 )
		return ;

	if ( pclinfo->siGuildUnique <= 0 )
		return ;

	cltGuildInfo* pclGuild = pclGuildManager->GetGuildInfo(pclinfo->siGuildUnique);
	if ( pclGuild == NULL ) return ;

	bool bMin = false ; // ����� ������ �� �ڸ��� �ֳ� ����?

	for ( SI32 i = 0 ; i < MAX_GUILD_MEMBER_NUM ; i ++ )
	{
		if ( pclGuild->clStandingMember[i].siPersonID == 0 )
		{
			bMin = true ; // ����� ������ �� �ڸ��� �ִ�.
			break; 
		}
	}

	if ( bMin == false )
		return ;

	sDBRequest_Guild_JoinGuild clMsg(pclchar->pclCI->GetPersonID(),id,pclGuild);
	pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&clMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_GUILD_CONFIRMJOINGUILD( cltMsg*pclMsg,SI32 id )
{
	cltGameMsgRequest_Guild_ConfirmJoinGuild * pclinfo = (cltGameMsgRequest_Guild_ConfirmJoinGuild*)pclMsg->cData;

	if( pclCM->IsValidID( id ) == false )
		return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL )
		return ;

	if ( pclchar->pclCI->clBI.clGuildRank.siGuildUnitIndex <= 0 )
		return ;

	if ( pclchar->pclCI->clBI.clGuildRank.siType != GUILDRANKTYPE_MASTER &&
		 pclchar->pclCI->clBI.clGuildRank.siType != GUILDRANKTYPE_SECONDMASTER )
		return ;

	SI32 siVillageUnique = pclchar->pclCI->clBI.clGuildRank.siVillageUnique ;
	SI32 siGuildUnique = pclchar->pclCI->clBI.clGuildRank.siGuildUnitIndex ;

	if ( pclVillageManager->IsValidVillage(siVillageUnique) == false )
		return ;

	if ( pclVillageManager->IsThereStructure(siVillageUnique,RANKTYPE_GUILD) == FALSE )
		return ;

	cltGuildInfo* pclGuild = pclGuildManager->GetGuildInfo(siGuildUnique);
	if ( pclGuild == NULL ) return ;

	bool bCorrect = false ; // ����� ������ �� personid�� �ֳ�?

	for ( SI32 i = 0 ; i < MAX_GUILD_MEMBER_NUM ; i ++ )
	{
		if ( pclinfo->bConfirm )
		{
			if ( pclGuild->clStandingMember[i].siPersonID == pclinfo->siStandingPersonID )
			{
				bCorrect = true ; // ����� ������ �ִ�
				break; 
			}
		}
		else
		{
			if ( pclGuild->clMember[i].siPersonID == pclinfo->siStandingPersonID )
			{
				bCorrect = true ; // ����� ������ �ִ�
				break; 
			}
			else if ( pclGuild->clStandingMember[i].siPersonID == pclinfo->siStandingPersonID )
			{
				bCorrect = true ; // ����� ������ �ִ�
				break; 
			}
		}
	}

	if ( bCorrect == false )
		return ;

	if ( pclinfo->bConfirm )
	{
		// ���� �ο��� ���� ��� �ο����� ũ�� �ʴٸ� �����Ѵ�.
		if ( pclGuild->GetLimitMemberNum() <= pclGuild->GetMemberNum() )
			return ;
	}

	sDBRequest_Guild_ConfirmJoinGuild clMsg(pclchar->pclCI->GetPersonID(),id,pclinfo->bConfirm == TRUE,pclinfo->siStandingPersonID);
	pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&clMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_GUILD_LEAVEGUILD( cltMsg*pclMsg,SI32 id )
{
	cltGameMsgRequest_Guild_LeaveGuild* pclinfo = (cltGameMsgRequest_Guild_LeaveGuild*)pclMsg->cData;

	if( pclCM->IsValidID( id ) == false )
		return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL )
		return ;

	if ( pclchar->pclCI->clBI.clGuildRank.siGuildUnitIndex != pclinfo->siGuildUnique )
		return ;

	if ( pclchar->pclCI->clBI.clGuildRank.siType == GUILDRANKTYPE_MASTER )
		return ;

	sDBRequest_Guild_LeaveGuild clMsg(pclchar->pclCI->GetPersonID()/*,id*/,pclinfo->siGuildUnique);
	pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&clMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_GUILD_CHANGEVILLAGE( cltMsg*pclMsg,SI32 id )
{
	cltGameMsgRequest_Guild_ChangeVillage* pclinfo = (cltGameMsgRequest_Guild_ChangeVillage*)pclMsg->cData;

	if( pclCM->IsValidID( id ) == false )
		return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL )
		return ;

	if ( pclchar->pclCI->clBI.clGuildRank.siGuildUnitIndex != pclinfo->siGuildUnique )
		return ;

	if ( pclchar->pclCI->clBI.clGuildRank.siType != GUILDRANKTYPE_MASTER )
		return ;

	if ( pclchar->pclCI->clBI.clGuildRank.uiConfirm != GUILDSTATUS_NORMAL )
		return ;

	SI32 siLeaveVillageUnique = pclchar->pclCI->clBI.clGuildRank.siVillageUnique ;
	SI32 siVillageUnique = pclinfo->siVillageUnique ;

	if ( pclVillageManager->IsValidVillage(siLeaveVillageUnique) == false ||
		 pclVillageManager->IsValidVillage(siVillageUnique) == false )
		 return ;

	if ( pclVillageManager->IsThereStructure(siVillageUnique , RANKTYPE_GUILD) == FALSE )
		 return ;

	sDBRequest_Guild_ChangeVillage clMsg(pclchar->pclCI->GetPersonID(),id,pclinfo->siGuildUnique,siVillageUnique,siLeaveVillageUnique);
	pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&clMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_GUILD_GETGUILDLIST( cltMsg*pclMsg,SI32 id )
{
	cltGameMsgRequest_Guild_GetGuildList* pclinfo = (cltGameMsgRequest_Guild_GetGuildList*)pclMsg->cData ;

	if( pclCM->IsValidID( id ) == false )
		return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL )
		return ;

	if ( pclVillageManager->IsValidVillage(pclinfo->siVillageUnique) == false )
		return ;

	cltGuildInfo clInfo[MAX_GUILD_PER_VILLAGE];
	SI32		mapindex[MAX_GUILD_PER_VILLAGE];

	SI32 index = 0 ;
	for ( SI32 i = 0 ; i < MAX_GUILD_NUM ; i ++ )
	{
		if ( pclGuildManager->clUnit[i].siVillageUnique == pclinfo->siVillageUnique ||
			pclGuildManager->clUnit[i].siMoveVillageUnique == pclinfo->siVillageUnique )
		{
			clInfo[index].Init() ;
			clInfo[index].Set(&pclGuildManager->clUnit[i]);
			mapindex[index] = pclGuildDungeonMgr->GetMapIndex( pclGuildManager->clUnit[i].siUnique );
			index ++ ;

			if ( index >= MAX_GUILD_PER_VILLAGE )
				break;
		}
	}
	cltGameMsgResponse_Guild_GetGuildList clGetGuildList( clInfo , mapindex,  pclinfo->siInterfaceFlag );
	cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_GETGUILDLIST, sizeof(cltGameMsgResponse_Guild_GetGuildList), (BYTE*)&clGetGuildList);
	pclchar->SendNetMsg((sPacketHeader*)&clMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_GUILD_GETGUILDINFO( cltMsg*pclMsg,SI32 id )
{
	cltGameMsgRequest_Guild_GetGuildInfo* pclinfo = (cltGameMsgRequest_Guild_GetGuildInfo*)pclMsg->cData; 

	if( pclCM->IsValidID( id ) == false )
		return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL )
		return ;

	if ( pclinfo->siUnique <= 0 )
		return ;

	cltGuildInfo* pclGuild = pclGuildManager->GetGuildInfo(pclinfo->siUnique);
	if ( pclGuild == NULL )
	{
		cltGameMsgResponse_Guild_GetGuildInfo clGetGuildInfo(0,NULL);
		cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_GETGUILDINFO, sizeof(cltGameMsgResponse_Guild_GetGuildInfo), (BYTE*)&clGetGuildInfo);
		pclchar->SendNetMsg((sPacketHeader*)&clMsg);
	}
	else
	{
		cltGameMsgResponse_Guild_GetGuildInfo clGetGuildInfo(1,pclGuild);
		cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_GETGUILDINFO, sizeof(cltGameMsgResponse_Guild_GetGuildInfo), (BYTE*)&clGetGuildInfo);
		pclchar->SendNetMsg((sPacketHeader*)&clMsg);
	}
}

void cltServer::DoMsg_GAMEMSG_REQUEST_GUILD_CONFIRMCREATEGUILD( cltMsg*pclMsg,SI32 id )
{
	cltGameMsgRequest_Guild_ConfirmCreateGuild* pclinfo = (cltGameMsgRequest_Guild_ConfirmCreateGuild* ) pclMsg->cData ;

	if( pclCM->IsValidID( id ) == false )
		return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL )
		return ;

	if ( pclinfo->siUnique <= 0 )
		return ;

	cltGuildInfo* pclGuild = pclGuildManager->GetGuildInfo(pclinfo->siUnique);
	if ( pclGuild == NULL )
		return ;

	cltSimpleRank clrank(RANKTYPE_GUILD, pclchar->pclMap->siVillageUnique );
	if(pclRankManager->IsRank(pclchar->pclCI->GetPersonID(), &clrank) == FALSE)
	{
		return ;
	}

	if ( pclGuild->uiConfirm == GUILDSTATUS_STANDING )
	{
		cltStrInfo* pclstr = pclGuildManager->GetStrInfo(pclGuild->siVillageUnique);
		if(pclstr == NULL)return ;
		GMONEY fee = pclstr->clGuildStrInfo.clFee.CalcFee(MIN_GUILD_CREATE_FEE);

		cltDate clDate;
		clDate.Set(&pclTime->clDate);

		sDBRequest_Guild_ConfirmCreateGuild clMsg(pclchar->pclCI->GetPersonID(),id,pclinfo->siUnique,pclinfo->bConfirm, MIN_GUILD_CREATE_FEE, fee, &clDate);
		pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&clMsg);

		pclDelMoneyStatistics->Add(DELMONEY_SERVICECHARGE, fee);
	}
	else if ( pclGuild->uiConfirm == GUILDSTATUS_CHANGEVILLAGE )
	{
		cltStrInfo* pclstr = pclGuildManager->GetStrInfo(pclchar->pclMap->siVillageUnique);
		if(pclstr == NULL)return ;
		GMONEY fee = pclstr->clGuildStrInfo.clFee.CalcFee(MIN_GUILD_CREATE_FEE);

		cltDate clDate;
		clDate.Set(&pclTime->clDate);

		sDBRequest_Guild_ConfirmCreateGuild clMsg(pclchar->pclCI->GetPersonID(),id,pclinfo->siUnique,pclinfo->bConfirm, 0, fee, &clDate);
		pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&clMsg);

		pclDelMoneyStatistics->Add(DELMONEY_SERVICECHARGE, fee);
	}
}

void cltServer::DoMsg_GAMEMSG_REQUEST_GUILD_SETSECONDMASTER( cltMsg*pclMsg,SI32 id )
{
	cltGameMsgRequest_Guild_SetSecondMaster* pclinfo = (cltGameMsgRequest_Guild_SetSecondMaster* ) pclMsg->cData ;

	if( pclCM->IsValidID( id ) == false )
		return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL )
		return ;

	if ( pclchar->pclCI->clBI.clGuildRank.siGuildUnitIndex <= 0 || pclchar->pclCI->clBI.clGuildRank.siType != GUILDRANKTYPE_MASTER )
		return ;

	cltGuildInfo* pclGuild = pclGuildManager->GetGuildInfo(pclchar->pclCI->clBI.clGuildRank.siGuildUnitIndex);
	if ( pclGuild == NULL )
		return ;

	if ( pclinfo->bSet )
	{
		if ( pclGuild->IsSecondMaster() == true )
			return ;
	}

	bool bCorrect = false ;
	for ( SI32 i = 0 ; i < MAX_GUILD_MEMBER_NUM ; i ++ )
	{
		if ( pclGuild->clMember[i].siPersonID == pclinfo->siPersonID )
		{
			if ( pclinfo->bSet ) // �Ӹ��̳�?
			{
				if ( pclGuild->clMember[i].siType != GUILDRANKTYPE_MEMBER )
					return ;
			}
			else // �����̳�?
			{
				if ( pclGuild->clMember[i].siType != GUILDRANKTYPE_SECONDMASTER )
					return ;
			}
				bCorrect = true ;
			break;
		}
	}

	if ( bCorrect )
	{
		sDBRequest_Guild_SetSecondMaster clMsg(pclchar->pclCI->GetPersonID(),id,pclinfo->siPersonID,pclinfo->bSet);
		pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&clMsg);
	}
}

void cltServer::DoMsg_GAMEMSG_REQUEST_GUILD_GIVEGUILDMONEY( cltMsg*pclMsg,SI32 id )
{
	cltGameMsgRequest_Guild_GiveGuildMoney* pclinfo = (cltGameMsgRequest_Guild_GiveGuildMoney*)pclMsg->cData ;

	if( pclCM->IsValidID( id ) == false )
		return ;

	if ( pclinfo->siMoney <= 0 )
		return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL )
		return ;

	if ( pclchar->pclCI->clBI.clGuildRank.siGuildUnitIndex <= 0 )
		return ;

	cltGuildInfo* pclGuild = pclGuildManager->GetGuildInfo(pclchar->pclCI->clBI.clGuildRank.siGuildUnitIndex);
	if ( pclGuild == NULL )
		return ;

	bool bCorrect = false ;
	for ( SI32 i = 0 ; i < MAX_GUILD_MEMBER_NUM ; i ++ )
	{
		if ( pclGuild->clMember[i].siPersonID == pclchar->pclCI->GetPersonID() )
		{
			bCorrect = true ;
			break;
		}
	}

	if ( bCorrect )
	{
		if ( pclchar->pclCI->clIP.GetMoney() >= pclinfo->siMoney )
		{
			sDBRequest_Guild_GiveGuildMoney clMsg(pclchar->pclCI->clBI.clGuildRank.GetGuildUnitIndex(), pclchar->pclCI->GetPersonID(),id,pclinfo->siMoney);
			pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&clMsg);
		}
	}
}


void cltServer::DoMsg_GAMEMSG_REQUEST_GUILD_SETSTRFEERATE(cltMsg*pclMsg,SI32 id)
{
	cltGameMsgRequest_Guild_SetStrFeeRate* pclinfo = (cltGameMsgRequest_Guild_SetStrFeeRate*)pclMsg->cData;

	if( pclCM->IsValidID( id ) == false )
		return ;

	if ( pclinfo->siFeeRate <= 0 )
		return ;

	if ( pclinfo->siVillageUnique <= 0 )
		return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL )
		return ;

	// �����?
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if( villageunique != pclinfo->siVillageUnique )
		return ;

	cltSimpleRank clrank(RANKTYPE_GUILD, villageunique);
	if(pclRankManager->IsRank(pclchar->pclCI->GetPersonID(), &clrank) == FALSE)
	{
		return ;
	}

	if ( pclinfo->siFeeRate <= 0 || pclinfo->siFeeRate > 10 )
		return ;

	// 10�踦 ���ش�.
	SI32 feerate = pclinfo->siFeeRate * 10 ;

	sDBRequest_Guild_SetStrFeeRate clMsg(pclchar->pclCI->GetPersonID(),id,pclinfo->siVillageUnique,feerate);
	pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&clMsg);

	
}

void cltServer::DoMsg_GAMEMSG_REQUEST_GUILD_CHANGESTATUS(cltMsg*pclMsg,SI32 id)
{
	cltGameMsgRequest_Guild_ChangeStatus* pclinfo = (cltGameMsgRequest_Guild_ChangeStatus*)pclMsg->cData;

	if( pclCM->IsValidID( id ) == false )
		return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL )
		return ;

	if ( pclchar->pclCI->clBI.clGuildRank.siType != GUILDRANKTYPE_MASTER )
		return;

	SI32 guildunique = pclchar->pclCI->clBI.clGuildRank.siGuildUnitIndex ;
	if ( guildunique <= 0 )
		return ;

	cltGuildInfo* pGuild = pclGuildManager->GetGuildInfo(guildunique);
	if ( pGuild == NULL )
		return ;

	
	// ��� ���� ����Ʈ�� ���� ���� ��� DB���� �ʱ�ȭ �ϵ��� ���� - tys[07/08/13]

	//SI32 totalStatus = pclinfo->clinfo.siBonus + pclinfo->clinfo.siDex
	//	+ pclinfo->clinfo.siHnd + pclinfo->clinfo.siLuck
	//	+ pclinfo->clinfo.siMag + pclinfo->clinfo.siStr
	//	+ pclinfo->clinfo.siVit;

	//if ( totalStatus != pGuild->clGPoint.siLevel )
	//{
	//	return;
	//}

if (pclClient->IsCountrySwitch(Switch_GuildstatusBugFix)) {//������ ������ ���ؼ� ���� ����ġ ���յǸ� ��ǻ� �ʿ���µ�..[2007.08.16 �ռ���]
	////SI32 totalStatus = pclinfo->clinfo.siBonus + pclinfo->clinfo.siDex/��彺�����ͽ� �������� ��� �۾��� ���� �ؼ� �۷ι��� �����ϰ�� �� �������ϰ� ����.
	//	+ pclinfo->clinfo.siHnd + pclinfo->clinfo.siLuck
	//	+ pclinfo->clinfo.siMag + pclinfo->clinfo.siStr
	//	+ pclinfo->clinfo.siVit;

	//if ( totalStatus != pGuild->clGPoint.siLevel )
	//{
		return;
	//}

}
else{
    SI32 totalStatus = pclinfo->clinfo.siBonus + pclinfo->clinfo.siDex
        + pclinfo->clinfo.siHnd + pclinfo->clinfo.siLuk
		+ pclinfo->clinfo.siMag + pclinfo->clinfo.siStr
		+ pclinfo->clinfo.siVit+ pclinfo->clinfo.siWis;
    if ( totalStatus != pGuild->clGPoint.siLevel )
	{
		return;
	}

}
	
	sDBRequest_Guild_ChangeStatus clMsg(pclchar->pclCI->GetPersonID(),id,guildunique,&pclinfo->clinfo);
	pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&clMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_GUILD_SETMARK(cltMsg*pclMsg,SI32 id)
{
	cltGameMsgRequest_Guild_SetMark* pclinfo = (cltGameMsgRequest_Guild_SetMark*)pclMsg->cData;

	if( pclCM->IsValidID( id ) == false )
		return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL )
		return ;

	if ( pclinfo->siMarkIndex <= 0 )
		return ;

	if ( pclchar->pclCI->clBI.clGuildRank.IsGuildMember() == false )
		return ;

	if ( pclchar->pclCI->clBI.clGuildRank.siType != GUILDRANKTYPE_MASTER )
		return ;

	sDBRequest_Guild_SetMark clMsg(pclchar->pclCI->GetPersonID(),pclchar->GetCharUnique(),pclchar->pclCI->clBI.clGuildRank.siGuildUnitIndex,pclinfo->siMarkIndex);
	pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&clMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_GUILD_CHANGENAME(cltMsg*pclMsg,SI32 id)
{
	cltGameMsgRequest_Guild_ChangeName* pclinfo = (cltGameMsgRequest_Guild_ChangeName*)pclMsg->cData;

	if( pclCM->IsValidID( id ) == false )
		return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL )
		return ;

	if ( pclinfo->szName[0] == NULL )
		return ;

	if ( pclchar->pclCI->clBI.clGuildRank.IsGuildMember() == false )
		return ;

	if ( pclchar->pclCI->clBI.clGuildRank.siType != GUILDRANKTYPE_MASTER )
		return ;

	sDBRequest_Guild_ChangeName clMsg(pclchar->pclCI->GetPersonID(),pclchar->GetCharUnique(),pclchar->pclCI->clBI.clGuildRank.siGuildUnitIndex,pclinfo->szName);
	pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&clMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_GUILD_CHANGEMASTER(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_Guild_ChangeMaster* pclinfo = (cltGameMsgRequest_Guild_ChangeMaster*)pclMsg->cData;

	if( pclCM->IsValidID( id ) == false )
		return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL )
		return ;

	if ( pclchar->pclCI->clBI.clGuildRank.IsGuildMember() == false )
		return ;

	if ( pclchar->pclCI->clBI.clGuildRank.siType != GUILDRANKTYPE_MASTER )
		return ;

	sDBRequest_Guild_ChangeMaster clMsg(pclchar->pclCI->GetPersonID(),pclchar->GetCharUnique(),pclchar->pclCI->clBI.clGuildRank.siGuildUnitIndex, pclinfo->siToPersonID );
	pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&clMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_GUILDWAR_RESERVELIST(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_GuildWar_ReserveList* pclinfo = (cltGameMsgRequest_GuildWar_ReserveList*)pclMsg->cData;

	if( pclCM->IsValidID( id ) == false )
		return;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL )	
		return ;

	if( IsCountrySwitch(Switch_NewGuildHuntMapWar) ) //������
	{
		if( pclinfo->siFieldIndex < 0 || pclinfo->siFieldIndex >= GUILDWAR_FIELDNUM_OLD	)		return;
	}
	else //������
	{
		if( pclinfo->siFieldIndex < 0 || pclinfo->siFieldIndex >= GUILDWAR_FIELDNUM	)		return;
	}
	

	cltGameMsgResponse_GuildWar_ReserveList cllist;

	// TODO : ���� �ð� ���Ĳ��� ������� �ϴµ�..

	SI32 startIndex = (((cltServer*)pclClient)->sTime.wHour * 2 ) + ( ((cltServer*)pclClient)->sTime.wMinute / 30 ) + 1;

	for ( SI32 i=startIndex; i<GUILDWAR_ROOMNUM ; i++ )
	{
		if( (i - startIndex) >= 0 && (i - startIndex) < GUILDWAR_ROOMNUM )
			cllist.clGuildWarList[i - startIndex].Set( &pclGuildWarReserveManager->m_clUnit[pclinfo->siFieldIndex][i] );
	}
	cltMsg clMsg(GAMEMSG_RESPONSE_GUILDWAR_RESERVELIST, sizeof(cltGameMsgResponse_GuildWar_ReserveList), (BYTE*)&cllist);
	pclchar->SendNetMsg((sPacketHeader*)&clMsg);
}
void cltServer::DoMsg_GAMEMSG_REQUEST_GUILDWAR_APPLYRESERVE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_GuildWar_ApplyReserve* pclinfo = (cltGameMsgRequest_GuildWar_ApplyReserve*)pclMsg->cData;

	if( pclCM->IsValidID(id) == false )
		return;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL)
		return;

	// �����Ͱ� �ƴϸ� ����
	if ( pclchar->pclCI->clBI.clGuildRank.GetRankType() != GUILDRANKTYPE_MASTER )
	{
		return;
	}

	// �ڽ��� ��带 ã�´�.
	SI32 guildUnique = pclchar->pclCI->clBI.clGuildRank.GetGuildUnitIndex();

	// ��� ����� ����ũ�� ���Ѵ�.
	SI32 enemyGuildUnique = 0;
	for ( SI32 i = 0 ; i <MAX_GUILD_NUM ; i++ )
	{
		if ( _tcscmp( pclGuildManager->clUnit[i].szName, pclinfo->szEnemyGuildName ) == 0 )
		{
			enemyGuildUnique = pclGuildManager->clUnit[i].siUnique;
			break;
		}
	}

	SI32 result = pclGuildWarReserveManager->ApplyReserve( pclinfo->siFieldIndex, pclinfo->siRoomIndex, guildUnique, enemyGuildUnique );

	cltGameMsgResponse_GuildWar_ApplyReserve clInfo(pclinfo->siFieldIndex, result);
	cltMsg clMsg(GAMEMSG_RESPONSE_GUILDWAR_APPLYRESERVE, sizeof(cltGameMsgResponse_GuildWar_ApplyReserve), (BYTE*)&clInfo);
	pclchar->SendNetMsg((sPacketHeader*)&clMsg);
}
void cltServer::DoMsg_GAMEMSG_REQUEST_GUILDDUNGEON_APPLYLIST(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_GuildDungeon_ApplyList* pclinfo = (cltGameMsgRequest_GuildDungeon_ApplyList*)pclMsg->cData;

	if( pclCM->IsValidID(id) == false )
		return;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL)
		return;

	if ( pclinfo->siMapIndex <= 0 ) return;


	cltGameMsgResponse_GuildDungeon_ApplyList clInfo;

	SI32 index = 0;
	for ( SI32 i=0; i<MAX_GUILD_NUM; i++)
	{
		if( pclGuildManager->clUnit[i].clGPoint.siApplyMapIndex == pclinfo->siMapIndex )
		{
			StringCchCopy( clInfo.szGuildName[index], MAX_GUILD_NAME, pclGuildManager->clUnit[i].GetName() );
			clInfo.siGuildPoint[index] = pclGuildManager->clUnit[i].clGPoint.siBattleGP;
			index++;
		}

		if ( index >= MAX_GUILDDUNGEONAPPLY ) break;
	}

	cltMsg clMsg(GAMEMSG_RESPONSE_GUILDDUNGEON_APPLYLIST, sizeof(cltGameMsgResponse_GuildDungeon_ApplyList), (BYTE*)&clInfo );
	pclchar->SendNetMsg((sPacketHeader*)&clMsg);
}
void cltServer::DoMsg_GAMEMSG_REQUEST_GUILDDUNGEON_APPLY(cltMsg* pclMsg, SI32 id)
{
	cltServer * pclserver = (cltServer*)pclClient;
	cltGameMsgRequest_GuildDungeon_Apply* pclinfo = (cltGameMsgRequest_GuildDungeon_Apply*)pclMsg->cData;

	if( pclCM->IsValidID(id) == false )
		return;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL)
		return;

	// �����Ͱ� �ƴϸ� ����
	if ( pclchar->pclCI->clBI.clGuildRank.GetRankType() != GUILDRANKTYPE_MASTER )
	{
		return;
	}

	// �ڽ��� ��带 ã�´�.
	SI32 guildUnique = pclchar->pclCI->clBI.clGuildRank.GetGuildUnitIndex();

	//// �̹� ��û�� ���ִٸ� ����
	cltGuildInfo* pGuild = pclGuildManager->GetGuildInfo(guildUnique);
	
	if ( pGuild != NULL && pGuild->clGPoint.siApplyMapIndex > 0 )
	{
		SI32 returnval = SRVAL_GUILDDUNGEON_FAIL_REG;
		SendServerResponseMsg( 0, returnval,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}
	if ( pclGuildDungeonMgr->CanApplyGuildDungeon(pclinfo->siMapIndex) == true ) // �ش� ������ ����Ϳ� ��û�� ���� �Ѱ�.
	{
		sDBRequest_GuildDungeon_Apply clMsg( guildUnique, pclinfo->siMapIndex, pclchar->GetID(),MESSAGETYPE_OLD );
		SendDBMsg(DBSELECT_BASE, (sPacketHeader*)&clMsg );
	}
	else
	{
		cltGameMsgResponse_GuildDungeon_Apply clInfo( false, pclinfo->siMapIndex );
		cltMsg clMsg( GAMEMSG_RESPONSE_GUILDDUNGEON_APPLY, sizeof(clInfo), (BYTE*)&clInfo );
		pclchar->SendNetMsg((sPacketHeader*)&clMsg);
	}
}
// ��� ����� ���� �ʵ�� 
void cltServer::DoMsg_GAMEMSG_REQUEST_GUILDHUNTMAPWAR_MAPREGISTER(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_GuildHuntMapWar_MapRegister* pclinfo = (cltGameMsgRequest_GuildHuntMapWar_MapRegister*)pclMsg->cData;

	if( pclCM->IsValidID(id) == false )
		return;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL)
		return;

	// �����Ͱ� �ƴϸ� ����
	if ( pclchar->pclCI->clBI.clGuildRank.GetRankType() != GUILDRANKTYPE_MASTER && 
		pclchar->pclCI->clBI.clGuildRank.GetRankType() != GUILDRANKTYPE_SECONDMASTER)
	{
		SI32 returnval = SRVAL_RETURN_NOTMASTER;
		SendServerResponseMsg( 0, returnval,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}

	// �ڽ��� ��带 ã�´�.
	SI32 guildUnique = pclchar->pclCI->clBI.clGuildRank.GetGuildUnitIndex();
	
	cltGuildInfo* pGuild = pclGuildManager->GetGuildInfo(guildUnique);
	if ( pGuild == NULL	)
	{
		return	;
	}
	if ( pGuild->clGPoint.siLevel < 4 || pGuild->GetMemberNum() < 5)
	{
		SI32 returnval = SRVAL_RETURN_REG_CANTSTATUSGUILD;
		SendServerResponseMsg( 0, returnval,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}
	if ( pGuild->clGPoint.siApplyMapIndex > 0 )
	{
		SI32 returnval = SRVAL_GUILDDUNGEON_FAIL_REG;
		SendServerResponseMsg( 0, returnval,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}
	if ( pclGuildDungeonMgr->CanApplyGuildDungeon(pclinfo->siMapIndex) == true )
	{
		sDBRequest_GuildDungeon_Apply clMsg( guildUnique, pclinfo->siMapIndex, pclchar->GetID(),MESSAGETYPE_NEW );
		SendDBMsg(DBSELECT_BASE, (sPacketHeader*)&clMsg );
	}
	else
	{
		cltGameMsgResponse_GuildDungeon_Apply clInfo( false, pclinfo->siMapIndex );
		cltMsg clMsg( GAMEMSG_RESPONSE_GUILDDUNGEON_APPLY, sizeof(clInfo), (BYTE*)&clInfo );
		pclchar->SendNetMsg((sPacketHeader*)&clMsg);
	}
}
// ��� ����� ����� ��û
void cltServer::DoMsg_GAMEMSG_REQUEST_GUILDHUNTMAPWAR_WARREGISTER(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_GuildHuntMapWarWar_Register* pclinfo = (cltGameMsgRequest_GuildHuntMapWarWar_Register*)pclMsg->cData;

	if( pclCM->IsValidID(id) == false )
		return;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL)	return;

	if( (sTime.wMinute >= 15 && sTime.wMinute < 20 )|| 
		(sTime.wMinute >= 35 && sTime.wMinute < 40 )||
		(sTime.wMinute >= 55 && sTime.wMinute <= 00 ))
	{		
		SI32 returnval = SRVAL_RETURN_NOT_REG_TIME;
		SendServerResponseMsg( 0, returnval,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return	; //5�������� ���� ��û�Ұ��� 
	}
	if ( pclchar->pclCI->clBI.clGuildRank.GetRankType() != GUILDRANKTYPE_MASTER && 
		pclchar->pclCI->clBI.clGuildRank.GetRankType() != GUILDRANKTYPE_SECONDMASTER)
	{
		SI32 returnval = SRVAL_RETURN_NOTMASTER;
		SendServerResponseMsg( 0, returnval,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}

	// �ڽ��� ��带 ã�´�.
	SI32 guildUnique = pclchar->pclCI->clBI.clGuildRank.GetGuildUnitIndex();

	// ��û�� ����Ʈ�� ������� �̹� ��û �ߴ��� Ȯ���Ѵ�. �̹� ��û�ߴٸ� ����
	if ( true == pclGuildHuntMapManager->IsSameGuild( guildUnique	) ) 
	{
		SI32 returnval = SRVAL_RETURN_BEFORE_REG_MAPWAR;
		SendServerResponseMsg( 0, returnval,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}
	//// ��� ����ũ�� ���ؼ� ��������� ������ �´�.
	cltGuildInfo* pGuild = pclGuildManager->GetGuildInfo(guildUnique)	;	
	if ( pGuild == NULL	)
	{
		return	;
	}
	if ( pGuild->clGPoint.siLevel < 4 || pGuild->GetMemberNum() < 5)
	{
		SI32 returnval = SRVAL_RETURN_REG_CANTSTATUSGUILD;
		SendServerResponseMsg( 0, returnval,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}

	if( pGuild != NULL && pGuild->clGPoint.siApplyMapIndex > 0 ) // ������ ��û�� ��忩�� ������� ��û�Ҽ� �ִ�.
	{
		sDBRequest_GuildHuntMapWar_SaveRegList clMsg(guildUnique ,AddList );
		SendDBMsg(DBSELECT_BASE, (sPacketHeader*)&clMsg );
	}
	else // �װ� �ƴ϶�� �ο�� ����
	{
		SI32 returnval = SRVAL_RETURN_NOT_RED_HUTMAP;	// ����� ��û ���� ������ ��û �ؾ��Ѵ�.
		SendServerResponseMsg( 0, returnval,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}
}
void cltServer::DoMsg_GAMEMSG_REQUEST_GUILDHUNTMAPWAR_SERVERTIME(cltMsg* pclMsg, SI32 id)
{
	cltServer* pclserver = (cltServer*)pclClient;

	cltGameMsgRequest_GuildHuntMapWarWar_Time* pclinfo = (cltGameMsgRequest_GuildHuntMapWarWar_Time*)pclMsg->cData;

	if( pclCM->IsValidID(id) == false )						return;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];						if ( pclchar == NULL)									return;

	_SYSTEMTIME stServerTime	;
	stServerTime.wMinute	=	pclserver->sTime.wMinute	;
	stServerTime.wSecond	=	pclserver->sTime.wSecond	;

    cltGameMsgResponse_GuildHuntMapWarWar_Time clinfo( stServerTime );
	cltMsg clMsg(GAMEMSG_RESPONSE_GUILDHUNTMAPWAR_SERVERTIME, sizeof(clinfo), (BYTE*)&clinfo);
	pclchar->SendNetMsg((sPacketHeader*)&clMsg);	

}
void cltServer::DoMsg_GAMEMSG_REQUEST_GUILDHUNTMAPWAR_HAVEMAP(cltMsg* pclMsg, SI32 id)
{
	cltServer* pclserver = (cltServer*)pclClient;

	cltGameMsgRequest_GuildHuntMapWarWar_HaveMapIndex* pclinfo = (cltGameMsgRequest_GuildHuntMapWarWar_HaveMapIndex*)pclMsg->cData;

	if( pclCM->IsValidID(id) == false )						return;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];						if ( pclchar == NULL)									return;
	SI32 siGuildUnique = pclchar->pclCI->clBI.clGuildRank.GetGuildUnitIndex();
	cltGuildInfo* pGuild = pclGuildManager->GetGuildInfo(siGuildUnique);
	if ( pGuild == NULL)	return	;
	cltGameMsgResponse_GuildHuntMapWarWar_HaveMapIndex clinfo( pGuild->clGPoint.siApplyMapIndex );
	cltMsg clMsg(GAMEMSG_RESPONSE_GUILDHUNTMAPWAR_HAVEMAP, sizeof(clinfo), (BYTE*)&clinfo);
	pclchar->SendNetMsg((sPacketHeader*)&clMsg);	

}
void cltServer::DoMsg_GAMEMSG_REQUEST_GUILDDUNGEON_STATUS(cltMsg* pclMsg, SI32 id)
{

	if( pclCM->IsValidID(id) == false )
		return;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL)
		return;

	cltGameMsgResponse_GuildDungeon_Status clInfo;

	SI16 index		 = 0;
	SI32 guildUnique = 0;
	for ( SI16 i=0; i< MAX_GUILDDUNGEON ; i++ )
	{
		clInfo.siMapIndex[i] = pclGuildDungeonMgr->m_clUnit[i].GetMapIndex();
		guildUnique = pclGuildDungeonMgr->m_clUnit[i].GetGuildUnique();
		if ( guildUnique )
		{
			StringCchCopy( clInfo.szGuildName[i], MAX_GUILD_NAME, pclGuildManager->GetGuildName(guildUnique) );
		}
		// PCK : �߱�, ������ �ں���, GP ���� �ۼ�Ʈ�� 0.03%�� �ǵ��� �Ѵ�. (09.04.14)
		if(pclClient->IsWhereServiceArea(ConstServiceArea_NHNChina) || pclClient->IsWhereServiceArea(ConstServiceArea_EUROPE))
		{
			clInfo.siExp[i] = Calc_GiveGP_Exception(pclGuildDungeonMgr->m_clUnit[i].GetExp());
			clInfo.siMoney[i] = Calc_GiveMoney_Exception(pclGuildDungeonMgr->m_clUnit[i].GetMoney());
		}
		else
		{
			if (IsCountrySwitch(Switch_NewGuildHuntMapWar) )
			{
				clInfo.siExp[i] = Calc_GiveGP_Exception(pclGuildDungeonMgr->m_clUnit[i].GetExp());
				clInfo.siMoney[i] = Calc_GiveMoney_Exception(pclGuildDungeonMgr->m_clUnit[i].GetMoney());				
			}
			else
			{
				clInfo.siExp[i] = Calc_GiveGP(pclGuildDungeonMgr->m_clUnit[i].GetExp());
				clInfo.siMoney[i] = Calc_GiveMoney(pclGuildDungeonMgr->m_clUnit[i].GetMoney());
			}
		}
	}

	cltMsg clMsg( GAMEMSG_RESPONSE_GUILDDUNGEON_STATUS, sizeof(clInfo), (BYTE*)&clInfo );
	pclchar->SendNetMsg((sPacketHeader*)&clMsg);
}
void cltServer::DoMsg_GAMEMSG_REQUEST_GUILD_MEMBERLIST(cltMsg* pclMsg, SI32 id)
{
	if( pclCM->IsValidID(id) == false )
		return;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL)
		return;

	cltGameMsgResponse_Guild_MemeberList clInfo;

	SI16 index = 0;

    SI32 myPersonID = pclchar->pclCI->GetPersonID();
	SI32 guildUnique = pclchar->pclCI->clBI.clGuildRank.GetGuildUnitIndex();

	if ( guildUnique <= 0 ) return;

	// [�߰� : Ȳ���� 2008. 1. 25 => ��� ����Ʈ ��û�� ������ ���� ������� �˻�.]
	if( pclchar->pclCI->clBI.clGuildRank.uiConfirm != GUILDSTATUS_STANDING	&&
		pclchar->pclCI->clBI.clGuildRank.siType	   != GUILDRANKTYPE_STANDING	)
	{
		
	}
	else
	{
		return;
	}

	cltGuildInfo* pGuild = pclGuildManager->GetGuildInfo( guildUnique );
	if ( pGuild == NULL )
		return;

	SI32 sendIndex = 0;
	SI32 charID	   = 0;
	for( SI16 i=0; i<MAX_GUILD_MEMBER_NUM; i++ )
	{
		if ( pGuild->clMember[i].siPersonID == 0 ) continue;
		// �ڱ� �ڽ��� ����.
		if ( myPersonID == pGuild->clMember[i].siPersonID ) continue;

		clInfo.siPersonID[sendIndex] = pGuild->clMember[i].siPersonID;
		StringCchCopy( clInfo.szName[sendIndex], MAX_PLAYER_NAME, pGuild->clMember[i].szCharName);

		charID = pclCM->GetIDFromPersonID(pGuild->clMember[i].siPersonID);

		if( pclCM->IsValidID(charID) )
		{
			clInfo.bConnected[sendIndex] = true;
			clInfo.siMapIndex[sendIndex] = pclCM->CR[charID]->GetMapIndex();
		}
		else
		{
			clInfo.bConnected[sendIndex] = false;
			clInfo.siMapIndex[sendIndex] = 0;
		}
		sendIndex++;
	}

	cltMsg clMsg( GAMEMSG_RESPONSE_GUILD_MEMBERLIST, sizeof(clInfo), (BYTE*)&clInfo );
	pclchar->SendNetMsg((sPacketHeader*)&clMsg);
}
void cltServer::DoMsg_GAMEMSG_REQUEST_GUILD_GETVILLAGELIST(cltMsg* pclMsg, SI32 id)
{
	if( pclCM->IsValidID(id) == false )
		return;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL)
		return;

	cltGameMsgReponse_Guild_VillageList clInfo;

	for(SI32 i = 0;i < MAX_VILLAGE_NUMBER;i++)
	{
		if(pclVillageManager->pclVillageInfo[i] == NULL)continue;


		cltStrInfo* pclstr = pclGuildManager->GetStrInfo(i);
		if(pclstr)
		{
			// ���°� �����̾�� 
			if(pclVillageManager->IsThereStructure(i, RANKTYPE_GUILD))
			{
				clInfo.bBuilt[i] = true;
			}
		}
	}

	cltMsg clMsg( GAMEMSG_RESPONSE_GUILD_GETVILLAGELIST, sizeof(clInfo), (BYTE*)&clInfo );
	pclchar->SendNetMsg((sPacketHeader*)&clMsg);
}
void cltServer::DoMsg_GAMEMSG_REQUEST_GUILDWAR_APPLYTOENEMY(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_GuildWar_ApplyToEnemy* pclinfo = (cltGameMsgRequest_GuildWar_ApplyToEnemy*)pclMsg->cData;
 
	if( pclCM->IsValidID(id) == false )
		return;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL)
		return;

	if ( bGuildWar == false )
	{
		SendServerResponseMsg(0, SRVAL_GUILDWAR_FAILAPPLY_NOTALLOWSERVER,  0, 0, id);
		return;
	}

	// siRoomIndex �� ��ȿ�� üũ
	if( pclinfo->siRoomIndex < 0 || pclinfo->siRoomIndex >= GUILDWAR_ROOMNUM ) return;

	// �����Ͱ� �ƴϸ� ����
	if ( pclchar->pclCI->clBI.clGuildRank.GetRankType() != GUILDRANKTYPE_MASTER )
	{
		return;
	}

	// �ڽ��� ��带 ã�´�.
	SI32 guildUnique = pclchar->pclCI->clBI.clGuildRank.GetGuildUnitIndex();

	// ��� ��带 ã�´�.
	cltGuildInfo* pHomeGuild = pclGuildManager->GetGuildInfo( guildUnique );
	cltGuildInfo* pEnemyGuild = pclGuildManager->GetGuildInfo( pclinfo->szEnemyGuildName );

	if ( pEnemyGuild == NULL || pHomeGuild == NULL )
	{
		SendServerResponseMsg(0, SRVAL_GUILDWAR_FAILAPPLY_FAULTNAME,  0, 0, id);
		return;
	}

	if ( pEnemyGuild->siUnique == pHomeGuild->siUnique )
	{
		SendServerResponseMsg(0, SRVAL_GUILDWAR_FAILAPPLY_MYGUILD,  0, 0, id);
		return;
	}

	if ( pHomeGuild->clGPoint.siLevel < GUILDWAR_MINLEVEL ||
		pEnemyGuild->clGPoint.siLevel < GUILDWAR_MINLEVEL )
	{
		SendServerResponseMsg(0, SRVAL_GUILDWAR_FAILAPPLY_LOWLEVEL,  0, 0, id);
		return;
	}

	// ���� ��帶������ personID�� ã�´�.

	SI32 enemyPersonID = pEnemyGuild->siMasterPersonID;

	SI32 enemyCharID = pclCM->GetIDFromPersonID(enemyPersonID);
	if ( pclCM->IsValidID(enemyCharID) == false )
	{
		SendServerResponseMsg(0, SRVAL_GUILDWAR_FAILAPPLY_NOTCONNECTED,  0, 0, id);
		return;
	}

	SI32 resultVal = pclGuildWarReserveManager->CanReserveRoom( pclinfo->siFieldIndex, pclinfo->siRoomIndex , pHomeGuild->siUnique , pEnemyGuild->siUnique ) ;

	if( resultVal == GUILDWAR_RESERVE_FAIL_ALREADYRESERVE )
	{
		SendServerResponseMsg(0, SRVAL_GUILDWAR_FAILAPPLY_IM_ALREADYRESERVE ,  0, 0, id);
		return;
	}
	else if( resultVal == GUILDWAR_RESERVE_FAIL_ENEMY_ALREADYRESERVE )
	{
		SendServerResponseMsg(0, SRVAL_GUILDWAR_FAILAPPLY_ENEMY_ALREADYRESERVE ,  0, 0, id);
		return;
	}
	else if ( resultVal == GUILDWAR_RESERVE_FAIL_ENEMY_OVERTIME )
	{
		SendServerResponseMsg(0, SRVAL_GUILDWAR_FAILAPPLY_OVERTIME ,  0, 0, id);
		return;
	}
	//cltCharServer* pclEnemyChar = (cltCharServer*)pclCM->CR[enemyCharID];

	//if ( pclEnemyChar = NULL )
	//	return;

	cltGameMsgResponse_GuildWar_ApplyToEnemy clInfo( pclinfo->siFieldIndex, pclinfo->siRoomIndex, guildUnique, pclGuildManager->GetGuildName( guildUnique ), pEnemyGuild->siUnique, pEnemyGuild->GetName() );
	cltMsg clMsg(GAMEMSG_RESPONSE_GUILDWAR_APPLYTOENEMY, sizeof( cltGameMsgResponse_GuildWar_ApplyToEnemy ), (BYTE*)&clInfo );
	pclCM->CR[enemyCharID]->SendNetMsg((sPacketHeader*)&clMsg);


}
void cltServer::DoMsg_GAMEMSG_REQUEST_GUILDWAR_CONFIRMAPPLY(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_GuildWar_ConfirmApply* pclinfo = (cltGameMsgRequest_GuildWar_ConfirmApply*)pclMsg->cData;

	if( pclCM->IsValidID(id) == false )
		return;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL)
		return;

	// siRoomIndex �� ��ȿ�� üũ
	if( pclinfo->siRoomIndex < 0 || pclinfo->siRoomIndex >= GUILDWAR_ROOMNUM )		return;
	// siFieldIndex �� ��ȿ�� üũ
	if( IsCountrySwitch(Switch_NewGuildHuntMapWar ) )	// ������ 
	{
		if( pclinfo->siFieldIndex < 0 || pclinfo->siFieldIndex >= GUILDWAR_FIELDNUM_OLD )	return;
	}
	else	// ������ 
	{
		if( pclinfo->siFieldIndex < 0 || pclinfo->siFieldIndex >= GUILDWAR_FIELDNUM )	return;
	}
	/* 
	1. ��û ����� �����Ͱ� �ִ��� üũ
	2. �ش� �ʵ� �ش� �ð��� �̹� �ٸ� ������� ���� �Ǿ��ִ��� üũ
	*/

	cltGuildInfo* pHomeGuild  = pclGuildManager->GetGuildInfo( pclinfo->siHomeGuildUnique );
	cltGuildInfo* pEnemyGuild = pclGuildManager->GetGuildInfo( pclinfo->siAwayGuildUnique );

	if( pHomeGuild == NULL || pEnemyGuild == NULL ) return;

	SI32 homePersonID = 0;
	if( pHomeGuild )
	{
		homePersonID = pHomeGuild->siMasterPersonID;
	}

	if( homePersonID < 1 )
	{
		return;
	}

	if ( pclinfo->bConfirm == false )
	{
		cltGuildInfo* pGuild = pclGuildManager->GetGuildInfo(pclinfo->siHomeGuildUnique);
		SI32 homeCharID = pclCM->GetIDFromPersonID(pGuild->siMasterPersonID);
		if ( pclCM->IsValidID(homeCharID) )
		{
			SendServerResponseMsg(0, SRVAL_GUILDWAR_FAILAPPLY_DENY,  0, 0, homeCharID);
		}
		return;
	}


    if( pclGuildWarReserveManager->IsReservedRoom( pclinfo->siFieldIndex, pclinfo->siRoomIndex ) )
	{
		SendServerResponseMsg(0, SRVAL_GUILDWAR_FAILAPPLY_ALREADY,  0, 0, id);
		return;
	}


	SI32 resultVal = pclGuildWarReserveManager->CanReserveRoom( pclinfo->siFieldIndex, pclinfo->siRoomIndex , pHomeGuild->siUnique , pEnemyGuild->siUnique ) ;

	if( resultVal == GUILDWAR_RESERVE_FAIL_ALREADYRESERVE )
	{
		SendServerResponseMsg(0, SRVAL_GUILDWAR_FAILAPPLY_IM_ALREADYRESERVE ,  0, 0, id);
		return;
	}
	else if( resultVal == GUILDWAR_RESERVE_FAIL_ENEMY_ALREADYRESERVE )
	{
		SendServerResponseMsg(0, SRVAL_GUILDWAR_FAILAPPLY_ENEMY_ALREADYRESERVE ,  0, 0, id);
		return;
	}
	if( pclGuildWarReserveManager->ReserveRoom( pclinfo->siFieldIndex, pclinfo->siRoomIndex, pclinfo->siHomeGuildUnique, pclinfo->siAwayGuildUnique ) ==false )
	{
		// �����ߴٴ� �޼��� ���ʿ� ����
	}
}
void cltServer::DoMsg_GAMEMSG_REQUEST_GUILDWAR_RECOMMANDLIST(cltMsg* pclMsg, SI32 id)
{
	if( pclCM->IsValidID(id) == false )			return;
	cltCharServer* pclchar = pclCM->GetCharServer(id);
	if ( pclchar == NULL)						return;
    
	SI32 guildUnique = pclchar->pclCI->clBI.clGuildRank.siGuildUnitIndex;
	cltGuildInfo* pGuild = pclGuildManager->GetGuildInfo( guildUnique );
	if ( pGuild == NULL )						return;

	// ���� ��Ŷ
	cltGameMsgResponse_GuildWar_RecommandList clinfo;

	// ��õ ��带 ã�´�.
	SI32 sendIndex = 0;
	BOOL bRecommend = FALSE;
	for(SI32 i=0; i<MAX_GUILD_NUM; i++)
	{
		bRecommend = FALSE;

		// ��Ŷ�� ���̻� ������ ���� �� ����.
		if( sendIndex >= MAX_RECOMMANDGUILDLIST)		break;

		// ��� ������ ���´�.
		cltGuildInfo* pclGuildInfo = &pclGuildManager->clUnit[i];
		if(pclGuildInfo == NULL)						continue;
		if(pclGuildInfo->siUnique <= 0)					continue;

		// ���� ���� ��õ���� �ʴ´�.
		if(pclGuildInfo->siUnique == pGuild->siUnique)	continue;

		// ��õ ����
		if( pclGuildInfo->clGPoint.siApplyMapIndex == pGuild->clGPoint.siApplyMapIndex )		bRecommend = TRUE;
		if( TABS( pclGuildInfo->clGPoint.siLevel - pGuild->clGPoint.siLevel ) < 3 )				bRecommend = TRUE;

		// ��õ���ǿ� �����ϴ� ����� ������ ��Ŷ�� �ִ´�.
		if(bRecommend)
		{
			SI32 masterCharID = pclCM->GetIDFromPersonID( pclGuildInfo->siMasterPersonID );
			if ( pclCM->IsValidID(masterCharID) )
			{
				StringCchCopy( clinfo.szMasterName[sendIndex], MAX_PLAYER_NAME, pclCM->CR[masterCharID]->GetName() );
				StringCchCopy( clinfo.szGuildName[sendIndex], MAX_GUILD_NAME,  pclGuildInfo->GetName() );
				clinfo.siLevel[sendIndex] = pclGuildInfo->clGPoint.siLevel;
				clinfo.siMemberCount[sendIndex] = pclGuildInfo->GetMemberNum();

				++sendIndex;
			}
		}
	}
	
	// ��õ ��带 ã�´�.
	/*SI32 i = rand() % MAX_GUILD_NUM;
	SI32 count = 0;
	SI32 sendIndex = 0;
	while ( count <= MAX_GUILD_NUM )
	{
		if( sendIndex >= MAX_RECOMMANDGUILDLIST )
			break;

		if( i > MAX_GUILD_NUM ) i=0;

		if ( pclGuildManager->clUnit[i].siUnique == pGuild->siUnique )
		{
			++count;
			++i;
			continue;
		}

		if ( pclGuildManager->clUnit[i].clGPoint.siApplyMapIndex == pGuild->clGPoint.siApplyMapIndex )
		{
			SI32 masterCharID = pclCM->GetIDFromPersonID( pclGuildManager->clUnit[i].siMasterPersonID );
			if ( pclCM->IsValidID(masterCharID) )
			{
				StringCchCopy( clinfo.szMasterName[sendIndex], MAX_PLAYER_NAME, pclCM->CR[masterCharID]->GetName() );
				StringCchCopy( clinfo.szGuildName[sendIndex], MAX_GUILD_NAME,  pclGuildManager->clUnit[i].GetName() );
				clinfo.siLevel[sendIndex] = pclGuildManager->clUnit[i].clGPoint.siLevel;
				clinfo.siMemberCount[sendIndex] = pclGuildManager->clUnit[i].GetMemberNum();

				++sendIndex;
				++count;
				++i;
				continue;
			}
		}
		
		if ( TABS( pclGuildManager->clUnit[i].clGPoint.siLevel - pGuild->clGPoint.siLevel ) < 3 )
		{
			SI32 masterCharID = pclCM->GetIDFromPersonID( pclGuildManager->clUnit[i].siMasterPersonID );
			if ( pclCM->IsValidID(masterCharID) )
			{
				StringCchCopy( clinfo.szMasterName[sendIndex], MAX_PLAYER_NAME, pclCM->CR[masterCharID]->GetName() );
				StringCchCopy( clinfo.szGuildName[sendIndex], MAX_GUILD_NAME,  pclGuildManager->clUnit[i].GetName() );
				clinfo.siLevel[sendIndex] = pclGuildManager->clUnit[i].clGPoint.siLevel;
				clinfo.siMemberCount[sendIndex] = pclGuildManager->clUnit[i].GetMemberNum();

				++sendIndex;
				++count;
				++i;
				continue;
			}
		}
		++count;
		++i;
	}*/

	cltMsg clMsg( GAMEMSG_RESPONSE_GUILDWAR_RECOMMANDLIST, sizeof(clinfo), (BYTE*)&clinfo);
	pclchar->SendNetMsg( (sPacketHeader*)&clMsg );
}

// �Ѵ��̻� ������� ���� �������� ����� ����
void cltServer::DoMsg_GAMEMSG_REQUEST_GUILD_NOTCONNECTMASTER_CHANGEMASTER(cltMsg* pclMsg, SI32 id)
{
	if( pclClient->IsCountrySwitch( Switch_Guild_GuildMaster_Change ) ){
		cltGameMsgRequest_Guild_NotConnectMaster_ChangeMaster* pclinfo = (cltGameMsgRequest_Guild_NotConnectMaster_ChangeMaster*)pclMsg->cData;

		if( pclCM->IsValidID( id ) == false )
			return ;

		cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
		if ( pclchar == NULL )
			return ;

		if ( pclchar->pclCI->clBI.clGuildRank.IsGuildMember() == false )
			return ;

		if ( pclchar->pclCI->clBI.clGuildRank.siType == GUILDRANKTYPE_MASTER )
			return ;

		SYSTEMTIME stLastConnect;
		TimeSubDate(&sTime, OVER30DAYSNOTINTOGAME, &stLastConnect);

		sDBRequest_Guild_NotConnect_ChangeMaster clMsg(pclchar->pclCI->GetPersonID(),pclchar->GetCharUnique(),pclchar->pclCI->clBI.clGuildRank.siGuildUnitIndex, &stLastConnect);
		pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&clMsg);
	}
	
}
//���� ����� 
void cltServer::DoMsg_GAMEMSG_REQUEST_GUILDHUNTMAPWAR_REQUEST(cltMsg* pclMsg, SI32 id)
{
	if( pclClient->IsCountrySwitch( Switch_NewGuildHuntMapWar ) )
	{
		cltGameMsgRequest_GuildHuntMapWarWar_Request* pclinfo = (cltGameMsgRequest_GuildHuntMapWarWar_Request*)pclMsg->cData;

		if ( pclCM->IsValidID(id) == false )								return	;

		cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id]	;
		if ( pclchar == NULL)												return	;
		if ( pclchar->pclCI->clBI.clGuildRank.IsGuildMember() == false )	return	;

		// �ش� ������ ���� ��Ų��.
		pclGuildHuntMapManager->WarpGuildWar_New( pclchar->pclCI->GetPersonID()	)	;
	}

}
void cltServer::DoMsg_GAMEMSG_REQUEST_GUILDHUNTMAPWAR_TOP10(cltMsg* pclMsg, SI32 id)
{
	if( true == pclClient->IsCountrySwitch( Switch_NewGuildHuntMapWar ) )
	{
		cltGameMsgRequest_GuilHuntMapdWar_GetTopTen* pclinfo = (cltGameMsgRequest_GuilHuntMapdWar_GetTopTen*)pclMsg->cData;
		if ( pclCM->IsValidID( id) == false )	return	;
		
		sDBRequest_GuildHuntMapWar_Rank_Get clMsg( pclinfo->siMapIndex, pclCM->CR[id]->pclCI->GetPersonID());
		pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&clMsg);
	}
}