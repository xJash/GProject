#include "Char/CharManager/CharManager.h"

#include "../Server/Server.h"
#include "../CommonLogic/Msg/MsgType-Guild.h"
#include "../CommonLogic/Guild/Guild.h"
#include "../Common/Item/ItemCommon/Item-GuildDungeon.h"

#include "../../../DBManager/GameDBManager_World/DBMsg-Guild.h"

#include "MsgType-Guild.h"
#include "MsgRval-Define.h"
#include "DevTool/DevServerInfo/DevServerInfo.h"
#include "../../CommonLogic/CommonLogic.h"

void cltServer::DoMsg_DBMSG_RESPONSE_GUILD_CREATEGUILD(sPacketHeader* pPacket)
{
	sDBResponse_Guild_CreateGuild* pclMsg = (sDBResponse_Guild_CreateGuild*)pPacket;

	if ( pclMsg->siResult == 1 )
	{
		if ( pclGuildManager->AddGuildInfo(&pclMsg->clInfo) )
		{
			SI32 charid = pclMsg->siCharID;

			if ( pclCM->IsValidID(charid) )
			{
				cltCharServer* pclchar = (cltCharServer*)pclCM->CR[charid];
				if ( pclchar == NULL )
					return ;


				if ( pclchar->pclCI->GetPersonID() == pclMsg->siPersonID )
				{
					pclchar->pclCI->clBI.clGuildRank.Set(GUILDRANKTYPE_MASTER,pclMsg->clInfo.siVillageUnique,
						pclMsg->clInfo.siUnique,pclMsg->clInfo.szName,pclMsg->clInfo.uiConfirm,pclMsg->clInfo.clGPoint.siMarkIndex);

					cltGameMsgResponse_Guild_CreateGuild clinfo(pclMsg->siResult,&pclMsg->clInfo);
					cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_CREATEGUILD, sizeof(clinfo), (BYTE*)&clinfo);
					pclchar->SendNetMsg((sPacketHeader*)&clMsg);
				}
			}
		}

		// LEEKH MODIFY 2007.10.25
		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 18] // ��尳��. (Ȯ���ʿ� : ������ �����Ѱ�?) 
			// param1		 == ��� ����ũ, 
			// pszCharParam1 == ����̸�. 
			// pszCharParam2 == �ð�.
			TCHAR pszCharParam2[50] = {'\0', };
			StringCchPrintf(pszCharParam2, sizeof(pszCharParam2), "%d-%d-%d, %d : %d",
																	pclMsg->clInfo.clDate.uiYear,
																	pclMsg->clInfo.clDate.uiMonth,
																	pclMsg->clInfo.clDate.uiDay,
																	pclMsg->clInfo.clDate.uiHour,
																	pclMsg->clInfo.clDate.uiMinute);
		
			cltCharServer* pclchar = NULL;
			if( pclCM->IsValidID(pclMsg->siCharID) )		pclchar = (cltCharServer*)pclCM->CR[pclMsg->siCharID];
			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_GUILD, LOGCOMMAND_INDEX_GUILD_CREATE,
								 0, pclchar, NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->clInfo.siVillageUnique, 0, 0, 
								 pclMsg->clInfo.siUnique, 0, 0, 0, 0, pclMsg->clInfo.GetName(), pszCharParam2);
		}
	}
	else if ( pclMsg->siResult == -2 ) // ������ �̸��� ��尡 �ִ�
	{
		SI32 charid = pclMsg->siCharID;

		if ( pclCM->IsValidID(charid) )
		{
			cltCharServer* pclchar = (cltCharServer*)pclCM->CR[charid];
			if ( pclchar == NULL )
				return ;

			if ( pclchar->pclCI->GetPersonID() == pclMsg->siPersonID )
			{
				cltGameMsgResponse_Guild_CreateGuild clinfo(pclMsg->siResult,&pclMsg->clInfo);
				cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_CREATEGUILD, sizeof(clinfo), (BYTE*)&clinfo);
				pclchar->SendNetMsg((sPacketHeader*)&clMsg);
			}
		}
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_GUILD_DESTROYGUILD(sPacketHeader* pPacket)
{
	sDBResponse_Guild_DestroyGuild* pclMsg = (sDBResponse_Guild_DestroyGuild*)pPacket;
	if(pclClient->IsCountrySwitch(Switch_Guild_DestroyOverMOnth)){
		// �޸������
		if ( pclMsg->siReason == 4 && pclMsg->siResult == 1 ){
			cltGuildInfo* pclGuild = pclGuildManager->GetGuildInfo(pclMsg->siGuildUnique);
			if (pclGuild == NULL)		return	;
			// ��带 �����ϰ� �޼����� ������.
			for ( SI32 i = 0 ; i < MAX_GUILD_MEMBER_NUM ; i ++ )
			{
				SI32 personid = pclGuild->clMember[i].siPersonID ;
				SI32 charid = pclCM->GetIDFromPersonID(personid);
				if ( pclCM->IsValidID(charid) ) // �������ִٸ�
				{
					pclCM->CR[charid]->pclCI->clBI.clGuildRank.Init();

					cltGameMsgResponse_Guild_SetGuildStatus clinfo(&pclGuild->clStatus,&pclCM->CR[charid]->pclCI->clBI.clGuildRank,pclCM->CR[charid]->GetCharUnique());
					cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_SETGUILDSTATUS, sizeof(clinfo), (BYTE*)&clinfo);
					((cltCharServer*)pclCM->CR[charid])->SendNeighbourMsg(&clMsg,true);

					// �޼��� �����ش�.
					cltLetterMsg_Guild_Destroy clLetter(pclMsg->siReason);
					SendLetterMsg(  personid , (cltLetterHeader*)&clLetter );
				}
				else
				{
					// �޼��� �����ش�.
					cltLetterMsg_Guild_Destroy clLetter(pclMsg->siReason);
					SendLetterMsg(  personid , (cltLetterHeader*)&clLetter );
				}
				

			}
			if ( pclGuildManager->DeleteGuildInfo(pclMsg->siGuildUnique) )
			{
				SI32 charid = pclMsg->siCharID;

				cltCharServer* pclchar = (cltCharServer*)pclCM->CR[charid];
				if ( pclchar == NULL )
					return ;

				if ( pclchar->pclCI->GetPersonID() == pclMsg->siPersonID )
				{
					cltGameMsgResponse_Guild_DestroyGuild clinfo(pclMsg->siResult,pclMsg->siGuildUnique,pclMsg->siVillageUnique,pclMsg->siReason);
					cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_DESTROYGUILD, sizeof(clinfo), (BYTE*)&clinfo);
					pclchar->SendNetMsg((sPacketHeader*)&clMsg);

					if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
					{
						// [�α��߰� : �ռ���] // �޸����û ����.
						// Param1 == ��� ����ũ
						cltServer* pclserver = (cltServer*)pclClient;
						pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_GUILD, LOGCOMMAND_INDEX_GUILD_DESTROY_MONTH,
							pclMsg->siReason, (cltCharServer*)pclchar, NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
							pclMsg->siGuildUnique, 0, 0, 0, 0, NULL, NULL);
					}
				}
			
				//��带 ���� �Ѵ�.
				cltGameMsgResponse_Guild_DestroyGuild clinfo(pclMsg->siResult,pclMsg->siGuildUnique,pclMsg->siVillageUnique,pclMsg->siReason);
				cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_DESTROYGUILD, sizeof(clinfo), (BYTE*)&clinfo);
			}
		}
	}

	if ( pclMsg->siReason != 4 && pclMsg->siResult == 1 )
	{
		cltGuildInfo* pclGuild = pclGuildManager->GetGuildInfo(pclMsg->siGuildUnique);
		if ( pclGuild == NULL ) return ;

		for ( SI32 i = 0 ; i < MAX_GUILD_MEMBER_NUM ; i ++ )
		{
			// ��� ȸ��
			SI32 personid = pclGuild->clMember[i].siPersonID ;
			SI32 charid = pclCM->GetIDFromPersonID(personid);
			if ( pclCM->IsValidID(charid) ) // �������ִٸ�
			{
				pclCM->CR[charid]->pclCI->clBI.clGuildRank.Init();

				cltGameMsgResponse_Guild_SetGuildStatus clinfo(&pclGuild->clStatus,&pclCM->CR[charid]->pclCI->clBI.clGuildRank,pclCM->CR[charid]->GetCharUnique());
				cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_SETGUILDSTATUS, sizeof(clinfo), (BYTE*)&clinfo);
				((cltCharServer*)pclCM->CR[charid])->SendNeighbourMsg(&clMsg,true);

				// �޼��� �����ش�.
				cltLetterMsg_Guild_Destroy clLetter(pclMsg->siReason);
				SendLetterMsg(  personid , (cltLetterHeader*)&clLetter );
			}

			// ��� ���� ��û��
			personid = pclGuild->clStandingMember[i].siPersonID ;
			charid = pclCM->GetIDFromPersonID(personid);
			if ( pclCM->IsValidID(charid) ) // �������ִٸ�
			{
				pclCM->CR[charid]->pclCI->clBI.clGuildRank.Init();

				cltGameMsgResponse_Guild_SetGuildStatus clinfo(&pclGuild->clStatus,&pclCM->CR[charid]->pclCI->clBI.clGuildRank,pclCM->CR[charid]->GetCharUnique());
				cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_SETGUILDSTATUS, sizeof(clinfo), (BYTE*)&clinfo);
				((cltCharServer*)pclCM->CR[charid])->SendNeighbourMsg(&clMsg,true);

				// �޼��� �����ش�.
				cltLetterMsg_Guild_Destroy clLetter(pclMsg->siReason);
				SendLetterMsg(  personid , (cltLetterHeader*)&clLetter );
			}
		}

		if ( pclGuildManager->DeleteGuildInfo(pclMsg->siGuildUnique) )
		{
			SI32 charid = pclMsg->siCharID;

			if ( pclCM->IsValidID(charid) )
			{
				cltCharServer* pclchar = (cltCharServer*)pclCM->CR[charid];
				if ( pclchar == NULL )
					return ;

				if ( pclchar->pclCI->GetPersonID() == pclMsg->siPersonID )
				{
					//pclchar->pclCI->clBI.clGuildRank.Init();

					cltGameMsgResponse_Guild_DestroyGuild clinfo(pclMsg->siResult,pclMsg->siGuildUnique,pclMsg->siVillageUnique,pclMsg->siReason);
					cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_DESTROYGUILD, sizeof(clinfo), (BYTE*)&clinfo);
					pclchar->SendNetMsg((sPacketHeader*)&clMsg);

					if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
					{
						// [�α��߰� : Ȳ���� 2007. 10. 10] // ����û ����.
						// Param1 == ��� ����ũ.  
						cltServer* pclserver = (cltServer*)pclClient;
						pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_GUILD, LOGCOMMAND_INDEX_GUILD_DESTROY,
														pclMsg->siReason, (cltCharServer*)pclchar, NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
														pclMsg->siGuildUnique, 0, 0, 0, 0, NULL, NULL);
					}
				}
			}
		}
	}	
}

void cltServer::DoMsg_DBMSG_RESPONSE_GUILD_JOINGUILD(sPacketHeader* pPacket)
{
	sDBResponse_Guild_JoinGuild* pclMsg = (sDBResponse_Guild_JoinGuild*)pPacket;

	if ( pclMsg->siResult == 1 )
	{
		cltGuildInfo* pclGuild = pclGuildManager->GetGuildInfo(pclMsg->clInfo.siUnique);
		if ( pclGuild == NULL ) return ;

		pclGuild->Set(&pclMsg->clInfo);

		SI32 charid = pclMsg->siCharID;
		if ( pclCM->IsValidID(charid) )
		{
			cltCharServer* pclchar = (cltCharServer*)pclCM->CR[charid];
			if ( pclchar == NULL )
				return ;

			if ( pclchar->pclCI->GetPersonID() == pclMsg->siPersonID )
			{
				pclchar->pclCI->clBI.clGuildRank.Set(GUILDRANKTYPE_STANDING,pclMsg->clInfo.siVillageUnique,
					pclMsg->clInfo.siUnique,pclMsg->clInfo.szName,pclMsg->clInfo.uiConfirm,pclMsg->clInfo.clGPoint.siMarkIndex);

				cltGameMsgResponse_Guild_JoinGuild clinfo(&pclMsg->clInfo);
				cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_JOINGUILD, sizeof(clinfo), (BYTE*)&clinfo);
				pclchar->SendNetMsg((sPacketHeader*)&clMsg);
			
				if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog))
				{
					// [�α��߰� : Ȳ���� 2007. 10. 18] // ��� ������ ��û
					// Param1 == ��� ����ũ.  pszParam1 == ����̸�, pszParam2 : ��尡�Կ�û�ð�
					TCHAR str[50] = {'\0', };
					StringCchPrintf(str, sizeof(str), TEXT("%d-%d-%d, %d : %d"),	pclMsg->clInfo.clDate.uiYear, 
																					pclMsg->clInfo.clDate.uiMonth,
																					pclMsg->clInfo.clDate.uiDay, 
																					pclMsg->clInfo.clDate.uiHour,
																					pclMsg->clInfo.clDate.uiMinute );

					cltServer* pclserver = (cltServer*)pclClient;
					pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_GUILD, LOGCOMMAND_INDEX_GUILD_JOIN,
													0, (cltCharServer*)pclchar, NULL, pclMsg->clInfo.siMasterPersonID, 0, 0, NULL, 0, 0, 0, pclMsg->clInfo.siVillageUnique, 0, 0, 
													pclMsg->clInfo.siUnique, 0, 0, 0, 0, pclMsg->clInfo.szName, str);
				}
			}
		}
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_GUILD_CONFIRMJOINGUILD(sPacketHeader* pPacket)
{
	sDBResponse_Guild_ConfirmJoinGuild* pclMsg = (sDBResponse_Guild_ConfirmJoinGuild*)pPacket ;

	if ( pclMsg->siResult == 1 )
	{
		cltGuildInfo* pclGuild = pclGuildManager->GetGuildInfo(pclMsg->clInfo.siUnique);
		if ( pclGuild == NULL ) return ;

		pclGuild->Set(&pclMsg->clInfo);

		// �㰡�� ��
		if ( pclMsg->bConfirm )
		{
			SI32 standingpersonid = pclMsg->siStandingPersonID ;
			SI32 standingID = pclCM->GetIDFromPersonID(standingpersonid);
			if ( pclCM->IsValidID(standingID) ) // �������ִٸ�
			{
				pclCM->CR[standingID]->pclCI->clBI.clGuildRank.Set(GUILDRANKTYPE_MEMBER,
					pclMsg->clInfo.siVillageUnique,pclMsg->clInfo.siUnique,pclMsg->clInfo.szName,
					pclMsg->clInfo.uiConfirm,pclMsg->clInfo.clGPoint.siMarkIndex);

				cltGameMsgResponse_Guild_SetGuildStatus clinfo(&pclGuild->clStatus,&pclCM->CR[standingID]->pclCI->clBI.clGuildRank,pclCM->CR[standingID]->GetCharUnique());
				cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_SETGUILDSTATUS, sizeof(clinfo), (BYTE*)&clinfo);
				((cltCharServer*)pclCM->CR[standingID])->SendNeighbourMsg(&clMsg,true);
			}

			if ( standingpersonid > 0 )
			{
				// �㰡 ���� �����ش�.
				cltLetterMsg_GuildJoin clletter( TRUE );
				SendLetterMsg(  standingpersonid , (cltLetterHeader*)&clletter );
			}


			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			{
				// [�α��߰� : Ȳ���� 2007. 10. 16] //  ��� ������ ��û�� ������ �������� �㰡.
				// param1		 == ��� ����ũ, 
				// pszCharParam1 == ����̸�.
				cltServer* pclserver = (cltServer*)pclClient;
				cltCharServer* pclchar = NULL;
				if( pclCM->IsValidID(pclMsg->siCharID) )		pclchar = (cltCharServer*)pclCM->CR[pclMsg->siCharID];
				pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_GUILD, LOGCOMMAND_INDEX_GUILD_JOINCONFIRM, 
												0, pclchar, NULL, standingpersonid, 0, 0, NULL, 0, 0, 0, pclMsg->clInfo.siVillageUnique, 0, 0,
												pclMsg->clInfo.siUnique, 0, 0, 0, 0, pclMsg->clInfo.szName, NULL);
			}
		}
		else // ������ ��
		{
			SI32 standingpersonid = pclMsg->siStandingPersonID ;
			SI32 standingID = pclCM->GetIDFromPersonID(standingpersonid);
			if ( standingID ) // �������ִٸ�
			{
				pclCM->CR[standingID]->pclCI->clBI.clGuildRank.Init() ;
				pclCM->CR[standingID]->clPB.clGuildBA.Init() ;// ��� ������ �ź� ���Ͽ������� ��� �ɷ�ġ �ʱ�ȭ 
				/*cltGuildStatus clstatus;
				ZeroMemory(&clstatus,sizeof(cltGuildStatus));*/

				cltGameMsgResponse_Guild_SetGuildStatus clinfo(&pclGuild->clStatus,&pclCM->CR[standingID]->pclCI->clBI.clGuildRank,pclCM->CR[standingID]->GetCharUnique());
				cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_SETGUILDSTATUS, sizeof(clinfo), (BYTE*)&clinfo);
				((cltCharServer*)pclCM->CR[standingID])->SendNeighbourMsg(&clMsg,true);
			}

			// ���� ���� �����ش�.
			if ( standingpersonid > 0 )
			{
				// �㰡 ���� �����ش�.
				cltLetterMsg_GuildJoin clletter( FALSE );
				SendLetterMsg(  standingpersonid , (cltLetterHeader*)&clletter );
			}
		}

		SI32 charid = pclMsg->siCharID;
		if ( pclCM->IsValidID(charid) )
		{
			cltCharServer* pclchar = (cltCharServer*)pclCM->CR[charid];
			if ( pclchar == NULL )
				return ;

			if ( pclchar->pclCI->GetPersonID() == pclMsg->siPersonID )
			{
				cltGameMsgResponse_Guild_ConfirmJoinGuild clinfo(pclMsg->bConfirm,pclMsg->siStandingPersonID,&pclMsg->clInfo);
				cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_CONFIRMJOINGUILD, sizeof(clinfo), (BYTE*)&clinfo);
				pclchar->SendNetMsg((sPacketHeader*)&clMsg);
			}
		}

		// ����ġ�� �ٿ�Ǹ� ������ �ٿ��Ų��.
		SI32 level = pclGuild->clGPoint.siLevel ;
		SI32 nextlevel = GetLevelFromExp( pclGuild->clGPoint.siPoint, EXPFORLEVEL_TYPE_GUILD );
		if ( level > nextlevel && pclGuild->clGPoint.siLevel > 1 )
		{
			sDBRequest_Guild_LevelUP clMsg(pclGuild->siUnique,nextlevel);
			pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&clMsg);
		}
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_GUILD_LEAVEGUILD(sPacketHeader* pPacket)
{
	sDBResponse_Guild_LeaveGuild* pclMsg = (sDBResponse_Guild_LeaveGuild*)pPacket;

	if ( pclMsg->siResult == 1 )
	{
		//[����] DB���� ���� CharID�� ���� personID�� ã�°����� ����. => 2008-9-3
		SI32 charid = pclCM->GetIDFromPersonID( pclMsg->siPersonID );// pclMsg->siCharID;
		if ( pclCM->IsValidID(charid) )
		{
			cltCharServer* pclchar = (cltCharServer*)pclCM->CR[charid];
			if ( pclchar == NULL )
				return ;

			if ( pclchar->pclCI->GetPersonID() == pclMsg->siPersonID )
			{
				pclchar->pclCI->clBI.clGuildRank.Init();

				cltGameMsgResponse_Guild_LeaveGuild clinfo(&pclMsg->clInfo);
				cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_LEAVEGUILD, sizeof(clinfo), (BYTE*)&clinfo);
				pclchar->SendNetMsg((sPacketHeader*)&clMsg);

				if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
				{
					// [�α��߰� : Ȳ���� 2007. 10. 10] // ��� Ż��.
					// param1	 == ��� ����ũ. 
					// pszParam1 == ��� �̸�.  
					SendLog_WriteLogToDB(LOGCOMMAND_TYPE_GUILD, LOGCOMMAND_INDEX_GUILD_LEAVE,
										 0, (cltCharServer*)pclchar, NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->clInfo.siVillageUnique, 0, 0, 
										 pclMsg->clInfo.siUnique, 0, 0, 0, 0, pclMsg->clInfo.szName, NULL);
				}
			}
		}

		cltGuildInfo* pclGuild = pclGuildManager->GetGuildInfo(pclMsg->clInfo.siUnique);
		if ( pclGuild == NULL ) return ;
		pclGuild->Set(&pclMsg->clInfo);

		// ����ġ�� �ٿ�Ǹ� ������ �ٿ��Ų��.
		SI32 level = pclGuild->clGPoint.siLevel ;
		SI32 nextlevel = GetLevelFromExp( pclGuild->clGPoint.siPoint, EXPFORLEVEL_TYPE_GUILD );
		if ( level > nextlevel && pclGuild->clGPoint.siLevel > 1 )
		{
			sDBRequest_Guild_LevelUP clMsg(pclGuild->siUnique,nextlevel);
			pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&clMsg);
		}
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_GUILD_CHANGEVILLAGE(sPacketHeader* pPacket)
{
	sDBResponse_Guild_ChangeVillage* pclMsg = (sDBResponse_Guild_ChangeVillage*)pPacket;

	if ( pclMsg->siResult == 1 )
	{
		cltGuildInfo* pclGuild = pclGuildManager->GetGuildInfo(pclMsg->clInfo.siUnique);
		if ( pclGuild == NULL ) return ;

		pclGuild->Set(&pclMsg->clInfo);

		//for ( SI32 i = 0 ; i < MAX_GUILD_MEMBER_NUM ; i ++ )
		//{
		//	SI32 personid = pclGuild->clMember[i].siPersonID ;
		//	SI32 charID = pclCM->GetIDFromPersonID(personid);
		//	if ( charID ) // �������ִٸ�
		//	{
		//		pclCM->CR[charID]->pclCI->clBI.clGuildRank.SetVillageUnique(pclMsg->siVillageUnique);
		//		pclCM->CR[charID]->pclCI->clBI.clGuildRank.uiConfirm = GUILDSTATUS_CHANGEVILLAGE;

		//		// �뺸���ش�.
		//		cltGameMsgResponse_Guild_SetGuildStatus clinfo(&pclGuild->clStatus,&pclCM->CR[charID]->pclCI->clBI.clGuildRank,pclCM->CR[charID]->GetCharUnique());
		//		cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_SETGUILDSTATUS, sizeof(clinfo), (BYTE*)&clinfo);
		//		((cltCharServer*)pclCM->CR[charID])->SendNeighbourMsg(&clMsg,true);
		//	}

		//	SI32 standingpersonid = pclGuild->clStandingMember[i].siPersonID ;
		//	SI32 standingcharID = pclCM->GetIDFromPersonID(standingpersonid);
		//	if ( standingcharID ) // �������ִٸ�
		//	{
		//		pclCM->CR[standingcharID]->pclCI->clBI.clGuildRank.SetVillageUnique(pclMsg->siVillageUnique);
		//		pclCM->CR[standingcharID]->pclCI->clBI.clGuildRank.uiConfirm = GUILDSTATUS_CHANGEVILLAGE;

		//		// �뺸���ش�.
		//		cltGameMsgResponse_Guild_SetGuildStatus clinfo(&pclGuild->clStatus,&pclCM->CR[standingcharID]->pclCI->clBI.clGuildRank,pclCM->CR[standingcharID]->GetCharUnique());
		//		cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_SETGUILDSTATUS, sizeof(clinfo), (BYTE*)&clinfo);
		//		((cltCharServer*)pclCM->CR[standingcharID])->SendNeighbourMsg(&clMsg,true);
		//	}
		//}

		SI32 masterID = pclMsg->siCharID ;
		if ( pclCM->IsValidID(masterID) )
		{
			cltCharServer* pclchar = (cltCharServer*)pclCM->CR[masterID];
			if ( pclchar == NULL )
				return ;

			if ( pclchar->pclCI->GetPersonID() == pclMsg->siPersonID )
			{
				cltGameMsgResponse_Guild_ChangeVillage clChangeVillage(&pclMsg->clInfo);
				cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_CHANGEVILLAGE, sizeof(cltGameMsgResponse_Guild_ChangeVillage), (BYTE*)&clChangeVillage);
				pclchar->SendNetMsg((sPacketHeader*)&clMsg);


				if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
				{
					// [�α��߰� : Ȳ���� 2007. 10. 11] // ��� ���� ����
					// param1 == ��� ����ũ. param2 == �������� ���� ����ũ
					//pszCharParam1 : ��� �̸�
					SendLog_WriteLogToDB(LOGCOMMAND_TYPE_GUILD, LOGCOMMAND_INDEX_GUILD_CHANGEVILLAGE, 
										 0, (cltCharServer*)pclchar, NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->clInfo.siVillageUnique, 0, 0,
										 pclMsg->clInfo.siUnique, pclMsg->clInfo.siMoveVillageUnique, 0, 0, 0, pclMsg->clInfo.szName, NULL);
				}
			}
		}
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_GUILD_CHANGEGUILDPOINT(sPacketHeader* pPacket)
{
	sDBResponse_Guild_ChangeGuildPoint* pclMsg = (sDBResponse_Guild_ChangeGuildPoint*)pPacket;

	if (pclMsg->siResult == 1 )
	{
		cltGuildInfo* pclGuild = pclGuildManager->GetGuildInfo(pclMsg->clinfo.siUnique);
		if ( pclGuild == NULL ) return ;

		pclGuild->Set(&pclMsg->clinfo);
		// ����ġ�� �ö󰡸� ������ ����Ų��.
		SI32 level = pclGuild->clGPoint.siLevel ;
		SI32 nextlevel = GetLevelFromExp( pclGuild->clGPoint.siPoint, EXPFORLEVEL_TYPE_GUILD );
		if ( level < nextlevel && pclGuild->clGPoint.siLevel < MAX_GUILD_LEVEL )
		{
			sDBRequest_Guild_LevelUP clMsg(pclGuild->siUnique,nextlevel);
			pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&clMsg);
		}
		// ����ġ�� �ٿ�Ǹ� ������ �ٿ��Ų��.
		level = pclGuild->clGPoint.siLevel ;
		nextlevel = GetLevelFromExp( pclGuild->clGPoint.siPoint, EXPFORLEVEL_TYPE_GUILD );
		if ( level > nextlevel && pclGuild->clGPoint.siLevel > 1 )
		{
			sDBRequest_Guild_LevelUP clMsg(pclGuild->siUnique,nextlevel);
			pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&clMsg);
		}

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 10] // ����� GP�� ��ȭ.
			// Param1		 == ��� ����ũ, 
			// param2		 == ��� ����Ʈ, 
			// pszCharParam1 == ��� �̸�. 
			cltServer * pclServer = (cltServer*)pclClient;
			pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_GUILD, LOGCOMMAND_INDEX_GUILD_CHANGEGUILDPOINT,
											0, NULL, NULL, 0, 0, 0, NULL, 0, 0, 0, pclGuild->siVillageUnique, 0, 0, 
											pclGuild->siUnique, pclGuild->clGPoint.siPoint, 0, 0, 0, 
											pclGuild->szName, NULL);
		}		
	}
}

void cltServer::DOMSG_DBMSG_RESPONSE_GUILD_GETGUILDINFO(sPacketHeader* pPacket)
{
	sDBResponse_Guild_GetGuildInfo* pclMsg = (sDBResponse_Guild_GetGuildInfo*)pPacket;

	if ( pclMsg->siResult == 1 )
	{
		SI32 startpos = pclMsg->siStartPos ;
		if (startpos < 0 )
			return ;

		SI32 index = 0 ;
		for ( SI32 i = startpos ; i < startpos + MAX_GUILD_PER_DBLIST ; i ++ )
		{
			if( i < 0 || i >= MAX_GUILD_NUM )	continue;
			pclGuildManager->clUnit[i].Set(&pclMsg->clInfo[index]);
			index ++ ;
		}
	}
	pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("sDBResponse_Guild_GetGuildInfo"));

}

enum{
	CONFIRMRESULT_CREATE_SUCCESS = 1,			// ���� ����
	CONFIRMRESULT_CREATE_DENINE,				// ���� �ź�
	CONFIRMRESULT_CREATE_FAILED,				// ���� ����
	CONFIRMRESULT_CHANGE_SUCCESS,				// ���� ����
	CONFIRMRESULT_CHANGE_DENINE,				// ���� �ź�
	CONFIRMRESULT_CHANGE_FAILED					// ���� ����
};

void cltServer::DOMSG_DBMSG_RESPONSE_GUILD_CONFIRMCREATEGUILD(sPacketHeader* pPacket)
{
	sDBResponse_Guild_ConfirmCreateGuild* pclMsg = (sDBResponse_Guild_ConfirmCreateGuild*)pPacket;

	if ( pclMsg->siResult < 1 )
		return;

	SI32	resultStatus = 0;

	if ( pclMsg->bConfirm )
	{
		if ( pclMsg->bState )
		{
			if ( pclMsg->siBeforeConfirm == GUILDSTATUS_STANDING )
			{
				resultStatus = CONFIRMRESULT_CREATE_SUCCESS;
			}
			else if (pclMsg->siBeforeConfirm == GUILDSTATUS_CHANGEVILLAGE )
			{
				resultStatus = CONFIRMRESULT_CHANGE_SUCCESS;
			}
		}
		else
		{
			if ( pclMsg->siBeforeConfirm == GUILDSTATUS_STANDING )
			{
				resultStatus = CONFIRMRESULT_CREATE_FAILED;
			}
			else if (pclMsg->siBeforeConfirm == GUILDSTATUS_CHANGEVILLAGE )
			{
				resultStatus = CONFIRMRESULT_CHANGE_FAILED;
			}
		}
	}
	else
	{
		if ( pclMsg->siBeforeConfirm == GUILDSTATUS_STANDING )
		{
			resultStatus = CONFIRMRESULT_CREATE_DENINE;
		}
		else if (pclMsg->siBeforeConfirm == GUILDSTATUS_CHANGEVILLAGE )
		{
			resultStatus = CONFIRMRESULT_CHANGE_DENINE;
		}

	}

	cltGuildInfo* pclGuild = pclGuildManager->GetGuildInfo(pclMsg->siGuildUnique);
	if ( pclGuild == NULL ) return ;

	// ����� ���� �ٸ��� ó���Ѵ�.
	
	UI08 confirmStatus = 0;

	switch( resultStatus )
	{
	case CONFIRMRESULT_CREATE_SUCCESS:
		{
			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			{
				// [�α��߰� : Ȳ���� 2007. 10. 31] // ��� ������ �㰡.
				// param1		 == ��� ����ũ.
				// param3		 == �Ӵ��				- �Ŵ� �������� ��.
				// pszCharParam1 == ��� �̸�.
				cltCharServer* pclchar = NULL;
				if( pclCM->IsValidID(pclMsg->siCharID) )		pclchar = (cltCharServer*)pclCM->CR[pclMsg->siCharID];
				SendLog_WriteLogToDB(LOGCOMMAND_TYPE_GUILD, LOGCOMMAND_INDEX_GUILD_CONFIRMCREATE, 
									 0, pclchar, NULL, pclMsg->siPersonID, pclMsg->siMoney, pclMsg->siLeftMoney, NULL, 0, 0, 0, 0, 0, 0,
									 pclMsg->clInfo.siUnique, 0, pclMsg->siFee, 0, 0, 
									 pclMsg->clInfo.GetName(), NULL);
			}

			confirmStatus = GUILDSTATUS_NORMAL;
			SI32 masterID = pclCM->GetIDFromPersonID(pclGuild->siMasterPersonID) ;
			if ( masterID > 0 )
			{
				if ( pclCM->IsValidID(masterID) )
				{
					cltCharServer* pclmaster = (cltCharServer*)pclCM->CR[masterID];
					if ( pclmaster == NULL )
						return ;

					pclmaster->pclCI->clBank.SetMoney(pclMsg->siLeftMoney);
					// �뺸�ؼ� ������Ʈ���ش�.
					pclmaster->SetUpdateSwitch(UPDATE_BANK,true,0);
				}
				cltLetterMsg_Guild_ConfirmCreateGuild clletter(TRUE, MIN_GUILD_CREATE_FEE);
				SendLetterMsg(  pclGuild->siMasterPersonID , (cltLetterHeader*)&clletter );
			}

			
		}
		break;
	case CONFIRMRESULT_CREATE_DENINE:
		{
			cltLetterMsg_Guild_ConfirmCreateGuild clletter(FALSE, 0);
			SendLetterMsg(  pclGuild->siMasterPersonID , (cltLetterHeader*)&clletter );
		}
		break;
	case CONFIRMRESULT_CREATE_FAILED:
		{
			cltLetterMsg_Guild_ConfirmCreateGuild clletter(FALSE, MIN_GUILD_CREATE_FEE);
			SendLetterMsg(  pclGuild->siMasterPersonID , (cltLetterHeader*)&clletter );
		}
		break;
	case CONFIRMRESULT_CHANGE_SUCCESS:
		{
			confirmStatus = GUILDSTATUS_NORMAL;
			SI32 masterID = pclCM->GetIDFromPersonID(pclGuild->siMasterPersonID) ;
			if ( masterID > 0 )
			{
				if ( pclCM->IsValidID(masterID) )
				{
					cltCharServer* pclmaster = (cltCharServer*)pclCM->CR[masterID];
					if ( pclmaster == NULL )
						return ;

					pclmaster->pclCI->clBank.SetMoney(pclMsg->siLeftMoney);
					// �뺸�ؼ� ������Ʈ���ش�.
					pclmaster->SetUpdateSwitch(UPDATE_BANK,true,0);
				}
				cltLetterMsg_Guild_ConfirmChangeVillage clletter(TRUE);
				SendLetterMsg(  masterID , (cltLetterHeader*)&clletter );
			}
		}
		break;
	case CONFIRMRESULT_CHANGE_DENINE:
		{
			confirmStatus = GUILDSTATUS_NORMAL;
			cltLetterMsg_Guild_ConfirmChangeVillage clletter( FALSE );
			SendLetterMsg(  pclGuild->siMasterPersonID , (cltLetterHeader*)&clletter );
		}
		break;
	case CONFIRMRESULT_CHANGE_FAILED:
		{
			confirmStatus = GUILDSTATUS_NORMAL;
			cltLetterMsg_Guild_ConfirmChangeVillage clletter( FALSE );
			SendLetterMsg(  pclGuild->siMasterPersonID , (cltLetterHeader*)&clletter );
		}
		break;
	}

	for ( SI32 i = 0 ; i < MAX_GUILD_MEMBER_NUM ; i ++ )
	{
		SI32 charID = pclCM->GetIDFromPersonID(pclGuild->clMember[i].siPersonID);
		if ( pclCM->IsValidID(charID) ) // �������ִٸ�
		{
			if ( confirmStatus )
				pclCM->CR[charID]->pclCI->clBI.clGuildRank.uiConfirm = GUILDSTATUS_NORMAL;
			else
				pclCM->CR[charID]->pclCI->clBI.clGuildRank.Init();

			// �뺸���ش�.
			cltGameMsgResponse_Guild_SetGuildStatus clinfo(&pclGuild->clStatus,&pclCM->CR[charID]->pclCI->clBI.clGuildRank,pclCM->CR[charID]->GetCharUnique());
			cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_SETGUILDSTATUS, sizeof(clinfo), (BYTE*)&clinfo);
			((cltCharServer*)pclCM->CR[charID])->SendNeighbourMsg(&clMsg,true);
		}
		charID = pclCM->GetIDFromPersonID(pclGuild->clStandingMember[i].siPersonID);
		if ( pclCM->IsValidID(charID) ) // �������ִٸ�
		{
			if ( confirmStatus )
				pclCM->CR[charID]->pclCI->clBI.clGuildRank.uiConfirm = GUILDSTATUS_NORMAL;
			else
				pclCM->CR[charID]->pclCI->clBI.clGuildRank.Init();

			// �뺸���ش�.
			cltGameMsgResponse_Guild_SetGuildStatus clinfo(&pclGuild->clStatus,&pclCM->CR[charID]->pclCI->clBI.clGuildRank,pclCM->CR[charID]->GetCharUnique());
			cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_SETGUILDSTATUS, sizeof(clinfo), (BYTE*)&clinfo);
			((cltCharServer*)pclCM->CR[charID])->SendNeighbourMsg(&clMsg,true);
		}
	}

	// ��� ������� �޼��� ����
	SI32 charid = pclMsg->siCharID;
	if ( pclCM->IsValidID(charid) )
	{
		cltCharServer* pclchar = (cltCharServer*)pclCM->CR[charid];
		if ( pclchar == NULL )
			return ;

		if ( pclchar->pclCI->GetPersonID() == pclMsg->siPersonID )
		{
			cltGameMsgResponse_Guild_ConfirmCreateGuild clinfo(pclMsg->siResult,&pclMsg->clInfo,pclMsg->bConfirm);
			cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_CONFIRMCREATEGUILD, sizeof(clinfo), (BYTE*)&clinfo);
			pclchar->SendNetMsg((sPacketHeader*)&clMsg);
		}
	}

	// ������ ��� ������ ������Ʈ

	pclGuild->Set(&pclMsg->clInfo);



	//if ( pclMsg->siResult == 1 )
	//{
	//	cltGuildInfo* pclGuild = pclGuildManager->GetGuildInfo(pclMsg->siGuildUnique);
	//	if ( pclGuild == NULL ) return ;

	//	UI08 siStatus = pclGuild->uiConfirm ;

	//	// �㰡�� ��
	//	if ( pclMsg->bConfirm )
	//	{
	//		if ( pclMsg->clInfo.siUnique == 0 ) // �㰡������ ��帶���Ϳ��� ���� ��� ��尡 �����Ǿ���.
	//		{
	//			for ( SI32 i = 0 ; i < MAX_GUILD_MEMBER_NUM ; i ++ )
	//			{
	//				SI32 charID = pclCM->GetIDFromPersonID(pclGuild->clMember[i].siPersonID);
	//				if ( charID ) // �������ִٸ�
	//				{
	//					pclCM->CR[charID]->pclCI->clBI.clGuildRank.Init();

	//					// �뺸���ش�.
	//					cltGameMsgResponse_Guild_SetGuildStatus clinfo(&pclGuild->clStatus,&pclCM->CR[charID]->pclCI->clBI.clGuildRank,pclCM->CR[charID]->GetCharUnique());
	//					cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_SETGUILDSTATUS, sizeof(clinfo), (BYTE*)&clinfo);
	//					((cltCharServer*)pclCM->CR[charID])->SendNeighbourMsg(&clMsg,true);
	//				}
	//				if ( pclGuild->clMember[i].siPersonID > 0 )
	//				{
	//					cltLetterMsg_Guild_ConfirmCreateGuild clletter(FALSE, MIN_GUILD_CREATE_FEE);
	//					SendLetterMsg(  pclGuild->clMember[i].siPersonID , (cltLetterHeader*)&clletter );
	//				}

	//				charID = pclCM->GetIDFromPersonID(pclGuild->clStandingMember[i].siPersonID);
	//				if ( charID ) // �������ִٸ�
	//				{
	//					pclCM->CR[charID]->pclCI->clBI.clGuildRank.Init();

	//					// �뺸���ش�.
	//					cltGameMsgResponse_Guild_SetGuildStatus clinfo(&pclGuild->clStatus,&pclCM->CR[charID]->pclCI->clBI.clGuildRank,pclCM->CR[charID]->GetCharUnique());
	//					cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_SETGUILDSTATUS, sizeof(clinfo), (BYTE*)&clinfo);
	//					((cltCharServer*)pclCM->CR[charID])->SendNeighbourMsg(&clMsg,true);
	//				}

	//				if ( pclGuild->clStandingMember[i].siPersonID > 0 )
	//				{
	//					cltLetterMsg_Guild_ConfirmCreateGuild clletter(FALSE, MIN_GUILD_CREATE_FEE);
	//					SendLetterMsg(  pclGuild->clStandingMember[i].siPersonID , (cltLetterHeader*)&clletter );
	//				}
	//			}
	//		}
	//		else // ��尡 ���������� �㰡�Ǿ���.
	//		{
	//			SI32 masterID = pclCM->GetIDFromPersonID(pclGuild->siMasterPersonID) ;
	//			if ( masterID > 0 )
	//			{
	//				if ( pclCM->IsValidID(masterID) )
	//				{
	//					cltCharServer* pclmaster = (cltCharServer*)pclCM->CR[masterID];
	//					if ( pclmaster == NULL )
	//						return ;

	//					pclmaster->pclCI->clBank.SetMoney(pclMsg->siLeftMoney);
	//					// �뺸�ؼ� ������Ʈ���ش�.
	//					pclmaster->SetUpdateSwitch(UPDATE_BANK,true,0);
	//				}
	//			}
	//			if ( pclGuild->siMasterPersonID > 0 )
	//			{
	//				if ( siStatus == GUILDSTATUS_STANDING )
	//				{
	//					cltLetterMsg_Guild_ConfirmCreateGuild clletter(TRUE, MIN_GUILD_CREATE_FEE);
	//					SendLetterMsg(  pclGuild->siMasterPersonID , (cltLetterHeader*)&clletter );
	//				}
	//				else if ( siStatus == GUILDSTATUS_CHANGEVILLAGE )
	//				{
	//					cltLetterMsg_Guild_ConfirmCreateGuild clletter(TRUE, 0);
	//					SendLetterMsg(  pclGuild->siMasterPersonID , (cltLetterHeader*)&clletter );
	//				}
	//			}

	//			for ( SI32 i = 0 ; i < MAX_GUILD_MEMBER_NUM ; i ++ )
	//			{
	//				SI32 charID = pclCM->GetIDFromPersonID(pclGuild->clMember[i].siPersonID);
	//				if ( charID ) // �������ִٸ�
	//				{
	//					pclCM->CR[charID]->pclCI->clBI.clGuildRank.uiConfirm = GUILDSTATUS_NORMAL ;

	//					// �뺸���ش�.
	//					cltGameMsgResponse_Guild_SetGuildStatus clinfo(&pclGuild->clStatus,&pclCM->CR[charID]->pclCI->clBI.clGuildRank,pclCM->CR[charID]->GetCharUnique());
	//					cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_SETGUILDSTATUS, sizeof(clinfo), (BYTE*)&clinfo);
	//					((cltCharServer*)pclCM->CR[charID])->SendNeighbourMsg(&clMsg,true);
	//				}
	//			}
	//		}
	//	}
	//	else // ����� ��尡 ������ ��
	//	{
	//		SI32 masterID = pclCM->GetIDFromPersonID(pclGuild->siMasterPersonID) ;
	//		if ( masterID > 0 )
	//		{
	//			if ( pclCM->IsValidID(masterID) )
	//			{
	//				cltCharServer* pclmaster = (cltCharServer*)pclCM->CR[masterID];
	//				if ( pclmaster == NULL )
	//					return ;

	//				// �뺸�ؼ� ������Ʈ���ش�.
	//				cltGameMsgResponse_Guild_SetGuildStatus clinfo(&pclGuild->clStatus,&pclmaster->pclCI->clBI.clGuildRank,pclmaster->GetCharUnique());
	//				cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_SETGUILDSTATUS, sizeof(clinfo), (BYTE*)&clinfo);
	//				pclmaster->SendNeighbourMsg(&clMsg,true);
	//			}
	//		}
	//		if ( pclGuild->siMasterPersonID > 0 )
	//		{
	//			cltLetterMsg_Guild_ConfirmCreateGuild clletter(FALSE,0);
	//			SendLetterMsg(  pclGuild->siMasterPersonID , (cltLetterHeader*)&clletter );
	//		}

	//		for ( SI32 i = 0 ; i < MAX_GUILD_MEMBER_NUM ; i ++ )
	//		{
	//			SI32 charID = pclCM->GetIDFromPersonID(pclGuild->clMember[i].siPersonID);
	//			if ( charID ) // �������ִٸ�
	//			{
	//				pclCM->CR[charID]->pclCI->clBI.clGuildRank.Init();
	//				// �뺸���ش�.
	//				cltGameMsgResponse_Guild_SetGuildStatus clinfo(&pclGuild->clStatus,&pclCM->CR[charID]->pclCI->clBI.clGuildRank,pclCM->CR[charID]->GetCharUnique());
	//				cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_SETGUILDSTATUS, sizeof(clinfo), (BYTE*)&clinfo);
	//				((cltCharServer*)pclCM->CR[charID])->SendNeighbourMsg(&clMsg,true);
	//			}

	//			charID = pclCM->GetIDFromPersonID(pclGuild->clStandingMember[i].siPersonID);
	//			if ( charID ) // �������ִٸ�
	//			{
	//				pclCM->CR[charID]->pclCI->clBI.clGuildRank.Init();
	//				// �뺸���ش�.
	//				cltGameMsgResponse_Guild_SetGuildStatus clinfo(&pclGuild->clStatus,&pclCM->CR[charID]->pclCI->clBI.clGuildRank,pclCM->CR[charID]->GetCharUnique());
	//				cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_SETGUILDSTATUS, sizeof(clinfo), (BYTE*)&clinfo);
	//				((cltCharServer*)pclCM->CR[charID])->SendNeighbourMsg(&clMsg,true);
	//			}
	//		}
	//	}

	//	pclGuild->Set(&pclMsg->clInfo);

	//	SI32 charid = pclMsg->siCharID;
	//	if ( pclCM->IsValidID(charid) )
	//	{
	//		cltCharServer* pclchar = (cltCharServer*)pclCM->CR[charid];
	//		if ( pclchar == NULL )
	//			return ;

	//		if ( pclchar->pclCI->GetPersonID() == pclMsg->siPersonID )
	//		{
	//			cltGameMsgResponse_Guild_ConfirmCreateGuild clinfo(pclMsg->siResult,&pclMsg->clInfo,pclMsg->bConfirm);
	//			cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_CONFIRMCREATEGUILD, sizeof(clinfo), (BYTE*)&clinfo);
	//			pclchar->SendNetMsg((sPacketHeader*)&clMsg);
	//		}
	//	}
	//}
}

void cltServer::DOMSG_DBMSG_RESPONSE_GUILD_SETSECONDMASTER(sPacketHeader* pPacket)
{
	sDBResponse_Guild_SetSecondMaster* pclMsg = (sDBResponse_Guild_SetSecondMaster*)pPacket ;

	if ( pclMsg->siResult == 1 )
	{
		cltGuildInfo* pclGuild = pclGuildManager->GetGuildInfo(pclMsg->clInfo.siUnique);
		if ( pclGuild == NULL ) return ;

		pclGuild->Set(&pclMsg->clInfo);

		SI32 siSecondMasterID = pclCM->GetIDFromPersonID(pclMsg->siSecondMasterPersonID) ;
		if ( pclCM->IsValidID(siSecondMasterID) )
		{
			if ( pclMsg->bSet )
			{
				pclCM->CR[siSecondMasterID]->pclCI->clBI.clGuildRank.siType = GUILDRANKTYPE_SECONDMASTER ;
			}
			else
			{
				pclCM->CR[siSecondMasterID]->pclCI->clBI.clGuildRank.siType = GUILDRANKTYPE_MEMBER ;
			}

			cltGameMsgResponse_Guild_SetGuildStatus clinfo(&pclGuild->clStatus,&pclCM->CR[siSecondMasterID]->pclCI->clBI.clGuildRank,pclCM->CR[siSecondMasterID]->GetCharUnique());
			cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_SETGUILDSTATUS, sizeof(clinfo), (BYTE*)&clinfo);
			((cltCharServer*)pclCM->CR[siSecondMasterID])->SendNeighbourMsg(&clMsg,true);
		}

		if( pclMsg->siSecondMasterPersonID > 0 )
		{
			cltLetterMsg_Guild_SecondMaster clletter(pclMsg->bSet);
			SendLetterMsg(  pclMsg->siSecondMasterPersonID , (cltLetterHeader*)&clletter );
		}

		SI32 charid = pclMsg->siCharID;
		if ( pclCM->IsValidID(charid) )
		{
			cltCharServer* pclchar = (cltCharServer*)pclCM->CR[charid];
			if ( pclchar == NULL )
				return ;

			if ( pclchar->pclCI->GetPersonID() == pclMsg->siPersonID )
			{
				cltGameMsgResponse_Guild_SetSecondMaster clinfo(pclMsg->siResult,&pclMsg->clInfo,pclMsg->bSet);
				cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_SETSECONDMASTER, sizeof(clinfo), (BYTE*)&clinfo);
				pclchar->SendNetMsg((sPacketHeader*)&clMsg);

				if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
				{
					// [�α��߰� : Ȳ���� 2007. 10. 11] // ��� ���Ǽ�
					// param1 == ��� ����ũ, pszparam1 == ����̸�
					SendLog_WriteLogToDB(LOGCOMMAND_TYPE_GUILD, LOGCOMMAND_INDEX_GUILD_SETSECONDMASTER, 
										 0, (cltCharServer*)pclchar, NULL, pclMsg->siSecondMasterPersonID, 0, 0, NULL, 0, 0, 0, 0, 0, 0,
										 pclMsg->clInfo.siUnique, 0, 0, 0, 0, pclMsg->clInfo.GetName(), NULL);
				}

			}
		}
	}
}

void cltServer::DOMSG_DBMSG_RESPONSE_GUILD_GIVEGUILDMONEY(sPacketHeader* pPacket)
{
	sDBResponse_Guild_GiveGuildMoney* pclMsg = (sDBResponse_Guild_GiveGuildMoney*)pPacket;

	if ( pclMsg->siResult == 1 )
	{
		cltGuildInfo* pclGuild = pclGuildManager->GetGuildInfo(pclMsg->clinfo.siUnique);
		if ( pclGuild == NULL ) return ;

		pclGuild->Set(&pclMsg->clinfo);

		if ( pclMsg->siPersonID == 0 )
			return;

		SI64 addgp = pclMsg->siMoney / 10000 ;

		sDBRequest_Guild_ChangeGuildPoint clMsg(pclGuild->siUnique,pclMsg->siPersonID,(SI32)addgp,TYPE_GUILDPOINT_ADD_GIVEGUILDMONEY,100);
		SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

		SI32 charid = pclMsg->siCharID;
		if ( pclCM->IsValidID(charid) )
		{
			cltCharServer* pclchar = (cltCharServer*)pclCM->CR[charid];
			if ( pclchar == NULL )
				return ;

			if ( pclchar->pclCI->GetPersonID() == pclMsg->siPersonID )
			{
				pclchar->pclCI->clIP.SetMoney(pclMsg->siLeftMoney);

				cltGameMsgResponse_Guild_GiveGuildMoney clinfo(pclMsg->siResult,&pclMsg->clinfo,pclMsg->siMoney,pclMsg->siLeftMoney);
				cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_GIVEGUILDMONEY, sizeof(clinfo), (BYTE*)&clinfo);
				pclchar->SendNetMsg((sPacketHeader*)&clMsg);

				if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
				{
					// [�α��߰� : Ȳ���� 2007. 10. 10] // ��� �ڱ��� ����
					// Param1	 == ��� ����ũ, 
					// pszParam1 == ��� �̸�. 
					cltServer * pclServer = (cltServer*)pclClient;
					pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_GUILD, LOGCOMMAND_INDEX_GUILD_GIVEMONEY,
													0, pclchar, NULL, 0, pclMsg->siMoney, pclMsg->siLeftMoney, NULL, 0, 0, 0, 0, 0, 0, 
													pclMsg->clinfo.siUnique, 0, 0, 0, 0, pclMsg->clinfo.szName, NULL);
				}
			}
		}

	}
}

void cltServer::DOMSG_DBMSG_RESPONSE_GUILD_GIVE_FEE(sPacketHeader* pPacket)
{
	sDBResponse_Guild_Give_Fee* pclMsg = (sDBResponse_Guild_Give_Fee*)pPacket;

	if ( pclMsg->siResult == 1 )
	{
		if ( pclMsg->siFaultNum > 0 )
		{
			cltGuildInfo* pGuild = pclGuildManager->GetGuildInfo(pclMsg->clinfo.siUnique);
			if ( pGuild == NULL )
				return ;

			if (pclMsg->siFaultNum == 1 )
			{
				//cltLetterMsg_Guild_Destroy clLetter();
				for ( SI32 i = 0 ; i < MAX_GUILD_MEMBER_NUM ; i++ )
				{
					if ( pGuild->clMember[i].siPersonID )
					{
						cltLetterMsg_Guild_Destroy clLetter(1);
						SendLetterMsg(  pGuild->clMember[i].siPersonID , (cltLetterHeader*)&clLetter );
					}
				}   
			}
			if (pclMsg->siFaultNum == 2 )
			{
				//cltLetterMsg_Guild_Destroy clLetter();
				for ( SI32 i = 0 ; i < MAX_GUILD_MEMBER_NUM ; i++ )
				{
					if ( pGuild->clMember[i].siPersonID )
					{
						cltLetterMsg_Guild_Destroy clLetter(2);
						SendLetterMsg(  pGuild->clMember[i].siPersonID , (cltLetterHeader*)&clLetter );
					}
				}
			}

			// ��ü��Ų��.
			if ( pclMsg->siFaultNum >= 3 )
			{
				for ( SI32 i = 0 ; i < MAX_GUILD_MEMBER_NUM ; i ++ )
				{
					if ( pGuild->clMember[i].siPersonID )
					{
						SI32 charid = pclCM->GetIDFromPersonID(pGuild->clMember[i].siPersonID);
						if ( pclCM->IsValidID(charid) )
						{
							cltCharServer* pclchar = (cltCharServer*)pclCM->CR[charid];
							if ( pclchar )
							{
								pclchar->pclCI->clBI.clGuildRank.Init();

								cltGameMsgResponse_Guild_SetGuildStatus clinfo(&pGuild->clStatus,&pclchar->pclCI->clBI.clGuildRank,pclchar->GetCharUnique());
								cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_SETGUILDSTATUS, sizeof(clinfo), (BYTE*)&clinfo);
								pclchar->SendNeighbourMsg(&clMsg,true);
							}
						}
						cltLetterMsg_Guild_Destroy clLetter(3);
						SendLetterMsg(  pGuild->clMember[i].siPersonID , (cltLetterHeader*)&clLetter );
					}
					else if ( pGuild->clStandingMember[i].siPersonID )
					{
						SI32 charid = pclCM->GetIDFromPersonID(pGuild->clStandingMember[i].siPersonID);
						if ( pclCM->IsValidID(charid) )
						{
							cltCharServer* pclchar = (cltCharServer*)pclCM->CR[charid];
							if ( pclchar )
							{
								pclchar->pclCI->clBI.clGuildRank.Init();
								cltGameMsgResponse_Guild_SetGuildStatus clinfo(&pGuild->clStatus,&pclchar->pclCI->clBI.clGuildRank,pclchar->GetCharUnique());
								cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_SETGUILDSTATUS, sizeof(clinfo), (BYTE*)&clinfo);
								pclchar->SendNeighbourMsg(&clMsg,true);
							}
						}
						cltLetterMsg_Guild_Destroy clLetter(3);
						SendLetterMsg(  pGuild->clStandingMember[i].siPersonID , (cltLetterHeader*)&clLetter );
					}
				}
				pGuild->Init();
			}
			else if ( pclMsg->siFaultNum == 2 )
			{
				pGuild->Set(&pclMsg->clinfo);
			}
			else if ( pclMsg->siFaultNum == 1 )
			{
				pGuild->Set(&pclMsg->clinfo);
			}
		}
		else
		{
			cltMoney clmoney;
			clmoney.Set(pclMsg->siLeftStrMoney);
			pclGuildManager->SetMoney(pclMsg->clinfo.siVillageUnique,&clmoney);

			cltGuildInfo* pGuild = pclGuildManager->GetGuildInfo(pclMsg->clinfo.siUnique);
			if ( pGuild )
				pGuild->Set(&pclMsg->clinfo);
		}

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 17] // ��� ������.
			// param1		 == �����Ḧ ������ ��� ����ũ.
			// Param2		 == ����� �ǹ� �ں���, 
			// param3		 == �Ӵ��, 
			// param4		 == ���� ���ڶ� �� �������� ��� ����Ƚ�� - 3��°�� ��� ��ü
			// pszCharParam1 == ����̸�.
			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_GUILD, LOGCOMMAND_INDEX_GUILD_GIVEFEE,
				0, NULL, NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->clinfo.siVillageUnique, 0, 0, 
				pclMsg->siGuildUnique, pclMsg->siLeftStrMoney, pclMsg->clinfo.siFee, pclMsg->siFaultNum, 0, 
				pclMsg->clinfo.szName, NULL);
		}
	}
}

void cltServer::DOMSG_DBMSG_RESPONSE_GUILD_CHANGESTATUS(sPacketHeader* pPacket)
{
	sDBResponse_Guild_ChangeStatus* pclMsg = (sDBResponse_Guild_ChangeStatus*)pPacket;

	if ( pclMsg->siResult == 1 )
	{
		cltGuildInfo* pGuild = pclGuildManager->GetGuildInfo(pclMsg->clinfo.siUnique);
		if ( pGuild )
		{
			pGuild->Set(&pclMsg->clinfo);

			for ( SI32 i = 0 ; i < MAX_GUILD_MEMBER_NUM ; i ++ )
			{
				if ( pGuild->clMember[i].siPersonID )
				{
					SI32 charid = pclCM->GetIDFromPersonID(pGuild->clMember[i].siPersonID);
					if ( pclCM->IsValidID(charid) )
					{
						cltCharServer* pclchar = (cltCharServer*)pclCM->CR[charid];
						if ( pclchar )
						{
							cltGameMsgResponse_Guild_SetGuildStatus clinfo(&pGuild->clStatus,&pclchar->pclCI->clBI.clGuildRank,pclchar->GetCharUnique());
							cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_SETGUILDSTATUS, sizeof(clinfo), (BYTE*)&clinfo);
							pclchar->SendNeighbourMsg(&clMsg,true);

							if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
							{
								// [�α��߰� : Ȳ���� 2007. 10. 10] // ��� �ɷ�ġ�� ����.
								// param1	 == ��� ����ũ, 
								// pszParam1 == ��� �̸�, 
								// pszParam2 == ��� ���� ����. < Str, Dex, Mag, Vit, Hnd, Luck, Bonus >
								TCHAR	str[50] = {'\0', };
								StringCchPrintf(str, sizeof(str), "%d, %d, %d, %d, %d, %d, %d",
																	pclMsg->clinfo.clStatus.siStr, 
																	pclMsg->clinfo.clStatus.siDex, 
																	pclMsg->clinfo.clStatus.siMag, 
																	pclMsg->clinfo.clStatus.siVit, 
																	pclMsg->clinfo.clStatus.siHnd, 
																	pclMsg->clinfo.clStatus.siLuk, 
																	pclMsg->clinfo.clStatus.siWis, 
																	pclMsg->clinfo.clStatus.siBonus);
								

								SendLog_WriteLogToDB(LOGCOMMAND_TYPE_GUILD, LOGCOMMAND_INDEX_GUILD_STATUSCHANGE,
													 0, pclchar, NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->clinfo.siVillageUnique, 0, 0, 
													 pclMsg->clinfo.siUnique, 0, 0, 0, 0, 
													 pclMsg->clinfo.szName, str);
							}
						}
					}
				}	
			}
		}

		SI32 charid = pclMsg->siCharID;
		if ( pclCM->IsValidID(charid) )
		{
			cltCharServer* pclchar = (cltCharServer*)pclCM->CR[charid];
			if ( pclchar == NULL )
				return ;

			if ( pclchar->pclCI->GetPersonID() == pclMsg->siPersonID )
			{
				cltGameMsgResponse_Guild_ChangeStatus clinfo(pclMsg->siResult,&pGuild->clStatus);
				cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_CHANGESTATUS, sizeof(clinfo), (BYTE*)&clinfo);
				pclchar->SendNetMsg((sPacketHeader*)&clMsg);
			}
		}
	}
}

void cltServer::DOMSG_DBMSG_RESPONSE_GUILD_SETSTRFEERATE(sPacketHeader* pPacket)
{
	sDBResponse_Guild_SetStrFeeRate*pclMsg = (sDBResponse_Guild_SetStrFeeRate*)pPacket;

	if ( pclMsg->siResult == 1 )
	{
		cltStrInfo* pclstr = pclGuildManager->GetStrInfo(pclMsg->siVillageUnique);
		if(pclstr == NULL)return ;

		// PCK : ����Ǳ����� �����Ḧ ����Ѵ�.
		SI32 siBeforeFeeRate = pclstr->clGuildStrInfo.clFee.GetFeeRate();

		pclstr->clGuildStrInfo.clFee.SetFeeRate(pclMsg->siFeeRate);

		SI32 charid = pclMsg->siCharID;
		if ( pclCM->IsValidID(charid) )
		{
			cltCharServer* pclchar = (cltCharServer*)pclCM->CR[charid];
			if ( pclchar == NULL )
				return ;

			if ( pclchar->pclCI->GetPersonID() == pclMsg->siPersonID )
			{
				cltGameMsgResponse_Guild_SetStrFeeRate clinfo(pclMsg->siResult,pclMsg->siVillageUnique,pclMsg->siFeeRate);
				cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_SETSTRFEERATE, sizeof(clinfo), (BYTE*)&clinfo);
				pclchar->SendNetMsg((sPacketHeader*)&clMsg);

				if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog))
				{
					// [�α��߰� : Ȳ���� 2007. 10. 10] // ��� �ǹ��� �����ᰡ ����.
					// Param1 == ����� ���� ������. Parma2 == ����Ǳ� ���� ������.
					SendLog_WriteLogToDB(LOGCOMMAND_TYPE_GUILD, LOGCOMMAND_INDEX_GUILD_SETSTRFEERATE,
										 0, (cltCharServer*)pclchar, NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
										 pclMsg->siFeeRate, siBeforeFeeRate, 0, 0, 0, NULL, NULL);
				}
			}
		}
	}
}


void cltServer::DOMSG_DBMSG_RESPONSE_GUILD_LEVELUP(sPacketHeader* pPacket)
{
	sDBResponse_Guild_LevelUP* pclMsg = (sDBResponse_Guild_LevelUP*)pPacket;

	if ( pclMsg->siResult == 1 )
	{
		cltGuildInfo* pGuild = pclGuildManager->GetGuildInfo(pclMsg->clinfo.siUnique);
		if ( pGuild )
		{
			pGuild->Set(&pclMsg->clinfo);

			for ( SI32 i = 0 ; i < MAX_GUILD_MEMBER_NUM ; i ++ )
			{
				if ( pGuild->clMember[i].siPersonID )
				{
					SI32 charid = pclCM->GetIDFromPersonID(pGuild->clMember[i].siPersonID);
					if ( pclCM->IsValidID(charid) )
					{
						cltCharServer* pclchar = (cltCharServer*)pclCM->CR[charid];
						if ( pclchar )
						{
							cltGameMsgResponse_Guild_SetGuildStatus clinfo(&pGuild->clStatus,&pclchar->pclCI->clBI.clGuildRank,pclchar->GetCharUnique());
							cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_SETGUILDSTATUS, sizeof(clinfo), (BYTE*)&clinfo);
							pclchar->SendNeighbourMsg(&clMsg,true);
						}
					}
				}
			}
		}
	}
}

void cltServer::DOMSG_DBMSG_RESPONSE_GUILD_SETMARK(sPacketHeader* pPacket)
{
	sDBResponse_Guild_SetMark* pclMsg = (sDBResponse_Guild_SetMark*)pPacket;

	if ( pclMsg->siResult == 1 )
	{
		cltGuildInfo* pGuild = pclGuildManager->GetGuildInfo(pclMsg->clinfo.siUnique);
		if ( pGuild )
		{
			pGuild->Set(&pclMsg->clinfo);

			for ( SI32 i = 0 ; i < MAX_GUILD_MEMBER_NUM ; i ++ )
			{
				SI32 personid = pGuild->clMember[i].siPersonID ;
				if ( personid )
				{
					SI32 charid = pclCM->GetIDFromPersonID(personid);
					if ( pclCM->IsValidID(charid) )
					{
						cltCharServer* pclchar = (cltCharServer*)pclCM->CR[charid];
						if ( pclchar )
						{
							pclchar->pclCI->clBI.clGuildRank.siMarkIndex = pclMsg->clinfo.clGPoint.siMarkIndex ;

							cltGameMsgResponse_Guild_SetGuildStatus clinfo(&pGuild->clStatus,&pclchar->pclCI->clBI.clGuildRank,pclchar->GetCharUnique());
							cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_SETGUILDSTATUS, sizeof(clinfo), (BYTE*)&clinfo);
							pclchar->SendNeighbourMsg(&clMsg,true);
						}
					}
				}
			}

			SI32 charid = pclMsg->siCharID;
			if ( pclCM->IsValidID(charid) )
			{
				cltCharServer* pclchar = (cltCharServer*)pclCM->CR[charid];
				if ( pclchar == NULL )
					return ;

				if ( pclchar->pclCI->GetPersonID() == pclMsg->siPersonID )
				{
					cltGameMsgResponse_Guild_SetMark clinfo(pclMsg->siResult,pclMsg->clinfo.clGPoint.siMarkIndex);
					cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_SETMARK, sizeof(clinfo), (BYTE*)&clinfo);
					pclchar->SendNetMsg((sPacketHeader*)&clMsg);
				}
			}
		}
	}
}

void cltServer::DOMSG_DBMSG_RESPONSE_GUILD_CHANGENAME(sPacketHeader* pPacket)
{
	sDBResponse_Guild_ChangeName* pclMsg = (sDBResponse_Guild_ChangeName*)pPacket;

	if ( pclMsg->siResult == 1 )
	{
		cltGuildInfo* pGuild = pclGuildManager->GetGuildInfo(pclMsg->clinfo.siUnique);
		if ( pGuild )
		{
			pGuild->Set(&pclMsg->clinfo);

			for ( SI32 i = 0 ; i < MAX_GUILD_MEMBER_NUM ; i ++ )
			{
				SI32 personid = pGuild->clMember[i].siPersonID ;
				if ( personid )
				{
					SI32 charid = pclCM->GetIDFromPersonID(personid);
					if ( pclCM->IsValidID(charid) )
					{
						cltCharServer* pclchar = (cltCharServer*)pclCM->CR[charid];
						if ( pclchar )
						{
							MStrCpy(pclchar->pclCI->clBI.clGuildRank.szGuildName,
									pclMsg->clinfo.szName,MAX_GUILD_NAME);

							cltGameMsgResponse_Guild_SetGuildStatus clinfo(&pGuild->clStatus,&pclchar->pclCI->clBI.clGuildRank,pclchar->GetCharUnique());
							cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_SETGUILDSTATUS, sizeof(clinfo), (BYTE*)&clinfo);
							pclchar->SendNeighbourMsg(&clMsg,true);
						}
					}
				}
			}

			SI32 charid = pclMsg->siCharID;
			if ( pclCM->IsValidID(charid) )
			{
				cltCharServer* pclchar = (cltCharServer*)pclCM->CR[charid];
				if ( pclchar == NULL )
					return ;

				if ( pclchar->pclCI->GetPersonID() == pclMsg->siPersonID )
				{
					cltGameMsgResponse_Guild_ChangeName clinfo(pclMsg->siResult,pclMsg->clinfo.szName);
					cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_CHANGENAME, sizeof(clinfo), (BYTE*)&clinfo);
					pclchar->SendNetMsg((sPacketHeader*)&clMsg);

					
					if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog))
					{
						// [�α��߰� : Ȳ���� 2007. 10. 10] // ��� �̸� ����.
						// param1 == ��� ����ũ, pszParam1 == ����Ǵ� �̸�.
						cltServer * pclServer = (cltServer*)pclClient;
						pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_GUILD, LOGCOMMAND_INDEX_GUILD_NAMECHANGE,
														0, pclchar, NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
														pclMsg->clinfo.siUnique, 0, 0, 0, 0, pclMsg->clinfo.szName, NULL);
					}

				}
			}
		}
	}
	else if ( pclMsg->siResult == -2 )
	{
		SI32 charid = pclMsg->siCharID;
		if ( pclCM->IsValidID(charid) )
		{
			cltCharServer* pclchar = (cltCharServer*)pclCM->CR[charid];
			if ( pclchar == NULL )
				return ;

			if ( pclchar->pclCI->GetPersonID() == pclMsg->siPersonID )
			{
				cltGameMsgResponse_Guild_ChangeName clinfo(pclMsg->siResult,pclMsg->clinfo.szName);
				cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_CHANGENAME, sizeof(clinfo), (BYTE*)&clinfo);
				pclchar->SendNetMsg((sPacketHeader*)&clMsg);
			}
		}
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_GUILD_CHANGEMASTER(sPacketHeader* pPacket)
{
	sDBResponse_Guild_ChangeMaster* pclMsg = (sDBResponse_Guild_ChangeMaster*)pPacket;

	if( pclMsg->siResult < 1 )
		return;

	cltGuildInfo* pclGuild = pclGuildManager->GetGuildInfo(pclMsg->clInfo.siUnique);

	if ( pclGuild == NULL ) return ;

	pclGuild->Set(&pclMsg->clInfo);

	SI32 newMasterID = pclCM->GetIDFromPersonID( pclMsg->siNewPersonID ) ;
	if ( pclCM->IsValidID(newMasterID) )
	{
		pclCM->CR[newMasterID]->pclCI->clBI.clGuildRank.siType = GUILDRANKTYPE_MASTER;

		cltGameMsgResponse_Guild_SetGuildStatus clinfo(&pclGuild->clStatus,&pclCM->CR[newMasterID]->pclCI->clBI.clGuildRank,pclCM->CR[newMasterID]->GetCharUnique());
		cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_SETGUILDSTATUS, sizeof(clinfo), (BYTE*)&clinfo);
		((cltCharServer*)pclCM->CR[newMasterID])->SendNeighbourMsg(&clMsg,true);
	}


	if( pclMsg->siNewPersonID > 0 )
	{
		cltLetterMsg_Guild_ChangeMaster clletter;
		SendLetterMsg(  pclMsg->siNewPersonID , (cltLetterHeader*)&clletter );
	}


	SI32 charid = pclMsg->siCharID;

	if  ( pclCM->IsValidID(charid) )
	{
		pclCM->CR[charid]->pclCI->clBI.clGuildRank.siType = GUILDRANKTYPE_MEMBER;

		cltGameMsgResponse_Guild_SetGuildStatus clinfo(&pclGuild->clStatus,&pclCM->CR[charid]->pclCI->clBI.clGuildRank,pclCM->CR[charid]->GetCharUnique());
		cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_SETGUILDSTATUS, sizeof(clinfo), (BYTE*)&clinfo);
		((cltCharServer*)pclCM->CR[charid])->SendNeighbourMsg(&clMsg,true);
	}


	if ( pclCM->IsValidID(charid) )
	{
		cltCharServer* pclchar = (cltCharServer*)pclCM->CR[charid];
		if ( pclchar == NULL )
			return ;

		if ( pclchar->pclCI->GetPersonID() == pclMsg->siPersonID )
		{
			cltGameMsgResponse_Guild_ChangeMaster clinfo(pclMsg->siResult,&pclMsg->clInfo);
			cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_CHANGEMASTER, sizeof(clinfo), (BYTE*)&clinfo);
			pclchar->SendNetMsg((sPacketHeader*)&clMsg);


			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog))
			{
				// [�α��߰� : Ȳ���� 2007. 10. 10] // ��� ������ ����
				// param1		 == �������ũ, 
				// pszCharParam1 == ��� �̸�.
				cltServer * pclServer = (cltServer*)pclClient;
				pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_GUILD, LOGCOMMAND_INDEX_GUILD_MASTERCHANGE,
												0, pclchar, NULL, pclMsg->siNewPersonID, 0, 0, NULL, 0, 0, 0, pclMsg->clInfo.siVillageUnique, 0, 0, 
												pclMsg->clInfo.siUnique, 0, 0, 0, 0,
												pclMsg->clInfo.szName, NULL);
			}
		}
	}
}
void cltServer::DoMsg_DBMSG_RESPONSE_GUILD_CLOSEGUILD(sPacketHeader* pPacket)
{
	sDBResponse_Guild_CloseGuild* pclMsg = (sDBResponse_Guild_CloseGuild*)pPacket;

	if( pclMsg->siResult < 1 )
		return;

	pclGuildManager->DeleteGuildInfo( pclMsg->siGuildUnique );

	SI32 charid = pclClient->pclCM->GetIDFromPersonID( pclMsg->siPersonID );

	if ( pclCM->IsValidID(charid) == false )
		return;

	//cltGameMsgResponse_Guild_CloseGuild clinfo(pclMsg->szGuildName);
	//cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_CLOSEGUILD, sizeof(clinfo), (BYTE*)&clinfo);
	//pclCM->CR[charid]->SendNetMsg((sPacketHeader*)&clMsg);
}
void cltServer::DoMsg_DBMSG_RESPONSE_GUILDWAR_ADDRESERVE(sPacketHeader* pPacket)
{
	sDBResponse_GuildWar_AddReserve* pclMsg = (sDBResponse_GuildWar_AddReserve*)pPacket;

	if( pclMsg->siResult < 1 )
		return;

	// �ƹ��͵� ó������ �ʴ´�
	
	SI32 CharID = pclCM->GetIDFromPersonID(pclMsg->siPersonID);

	if(FALSE == pclCM->IsValidID(CharID)) {		return;		}

	cltCharServer* pclchar = pclCM->GetCharServer(CharID);

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [�α��߰� : Ȳ���� 2007. 10. 10] // ����� ����. (�����ʿ� : ���� ������ ���� request�� �ּ�ó���� �α׺κ��� ����Ұǰ�?)
		// param1 == Field Index
		// param2 == Room Index
		// param3 == Home Guild Unique.
		// param4 == Away Guild Unique.
		cltServer * pclServer = (cltServer*)pclClient;
		pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_GUILD, LOGCOMMAND_INDEX_GUILD_WARADDRESERVE,
										0, pclchar, NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
										pclMsg->siFieldIndex, pclMsg->siRoomIndex, pclMsg->siHomeGuildUnique, pclMsg->siAwayGUildUnique, 0, 
										NULL, NULL);
	}
}
void cltServer::DoMsg_DBMSG_RESPONSE_GUILDWAR_RESERVELIST(sPacketHeader* pPacket)
{
	sDBResponse_GuildWar_ReserveList* pclMsg = (sDBResponse_GuildWar_ReserveList*)pPacket;

	if( pclMsg->siResult < 1)
		return;

	SI32 field = pclMsg->siFieldIndex;
	for( SI32 i = 0; i < GUILDWAR_ROOMNUM; i++ )
	{
		SI32 room = pclMsg->clUnit[i].m_siRoomIndex;

		if ( IsCountrySwitch(Switch_NewGuildHuntMapWar) )	// ������
		{
			if( field < 0 || field >= GUILDWAR_FIELDNUM_OLD )	continue;
			if( room < 0  || room >= GUILDWAR_ROOMNUM )	continue;
			pclGuildWarReserveManager->m_clUnit[field][room].Set( pclMsg->clUnit[i].m_siRoomIndex,
				pclMsg->clUnit[i].m_siHomeGuildUnique,
				pclMsg->clUnit[i].m_szHomeGuildName,
				pclMsg->clUnit[i].m_siAwayGuildUnique,
				pclMsg->clUnit[i].m_szAwayGuildName);
		}
		else	// ������
		{
			if( field < 0 || field >= GUILDWAR_FIELDNUM)	continue;
			if( room < 0  || room >= GUILDWAR_ROOMNUM )	continue;
			pclGuildWarReserveManager->m_clUnit[field][room].Set( pclMsg->clUnit[i].m_siRoomIndex,
				pclMsg->clUnit[i].m_siHomeGuildUnique,
				pclMsg->clUnit[i].m_szHomeGuildName,
				pclMsg->clUnit[i].m_siAwayGuildUnique,
				pclMsg->clUnit[i].m_szAwayGuildName);
		}
	}
	pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("sDBResponse_GuildWar_ReserveList"));
}
void cltServer::DoMsg_DBMSG_RESPONSE_GUILDDUNGEON_APPLY(sPacketHeader* pPacket)
{
	sDBResponse_GuildDungeon_Apply* pclMsg = (sDBResponse_GuildDungeon_Apply*)pPacket;

	SI32 charid = pclMsg->siCharID;

	if ( pclCM->IsValidID(charid) == false )
		return;

	if ( pclMsg->siResult > 0 )
	{
		cltGuildInfo* pGuild = pclGuildManager->GetGuildInfo(pclMsg->siGuildUnique);

		if ( pGuild )
		{
			pGuild->Set( &(pclMsg->clGuildInfo) );

			// �����鿡�� ���� �޼��� ����
			cltLetterMsg_GuildDungeon_Apply clletter( pclMsg->siMapIndex );
			for ( SI16 i=0; i<MAX_GUILD_MEMBER_NUM; i++ )
			{
				if ( pGuild->clMember[i].siPersonID > 0 )
				{
					SendLetterMsg( pGuild->clMember[i].siPersonID, (cltLetterHeader*)&clletter);
				}
			}

			cltGameMsgResponse_GuildDungeon_Apply clinfo( true, pclMsg->siMapIndex );
			cltMsg clMsg(GAMEMSG_RESPONSE_GUILDDUNGEON_APPLY, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[charid]->SendNetMsg((sPacketHeader*)&clMsg);

			cltGameMsgResponse_GuildHuntMapWarWar_HaveMapIndex clinfo2( pclMsg->siMapIndex );
			cltMsg clMsg2(GAMEMSG_RESPONSE_GUILDHUNTMAPWAR_HAVEMAP, sizeof(clinfo2), (BYTE*)&clinfo2);
			pclCM->CR[charid]->SendNetMsg((sPacketHeader*)&clMsg2);


		
			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			{
				// [�α��߰� : Ȳ���� 2007. 10. 15] // ����� ������ ��û�ϱ�.
				// param1		 == ��� ����ũ, 
				// param2		 == �ʹ�ȣ.
				// pszCharParam1 == ����̸�.
				cltServer* pclserver = (cltServer*)pclClient;
				pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_GUILD, LOGCOMMAND_INDEX_GUILD_DUNGEONAPPLY, 
												0, (cltCharServer*)pclCM->CR[charid], NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0,
												pclMsg->siGuildUnique, pclMsg->siMapIndex, 0, 0, 0, 
												pclMsg->clGuildInfo.szName, NULL);
			}
		}
	}
	else
	{
		cltGameMsgResponse_GuildDungeon_Apply clinfo( false, pclMsg->siMapIndex );
		cltMsg clMsg(GAMEMSG_RESPONSE_GUILDDUNGEON_APPLY, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[charid]->SendNetMsg((sPacketHeader*)&clMsg);
	}
}
void cltServer::DoMsg_DBMSG_RESPONSE_GUILDDUNGEON_SAVESTATUS(sPacketHeader* pPacket)
{
	// ���Ͼ���..;;
}
void cltServer::DoMsg_DBMSG_RESPONSE_GUILDDUNGEON_LOADSTATUS(sPacketHeader* pPacket)
{
	sDBResponse_GuildDungeon_LoadStatus* pclMsg = (sDBResponse_GuildDungeon_LoadStatus*)pPacket;

	if ( pclMsg->siResult > 0 )
	{
		pclGuildDungeonMgr->SetStatus( pclMsg->siMapIndex, pclMsg->siGuildUnique, pclMsg->siExp, pclMsg->siMoney);
	}
	pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("sDBResponse_GuildDungeon_LoadStatus"));

}
// ��� ����� ���� 
void cltServer::DoMsg_DBMSG_RESPONSE_GUILDDUNGEON_TRANSFEROWNERSHIP(sPacketHeader* pPacket)
{
	sDBResponse_GuildDungeon_TransferOwnership* pclMsg = (sDBResponse_GuildDungeon_TransferOwnership*)pPacket;

	cltServer* pclserver = (cltServer*)pclClient;

	if ( pclMsg->siResult > 0 )
	{
		// ��� ������ �ڷḦ ���� ����
		for ( SI32 i = 0; i < MAX_GUILDDUNGEON; i++ )
		{
			SI32	m_siitemUnique	=	0;	// ��� ����ͷ� ���� ������ ����ũ
			SI32	siitemNum		=	0;			// ��� ����ͷ� ���� ������ ����
			// �������� �����Ѵ�.
			if ( pclGuildDungeonMgr->m_clUnit[i].m_siGuildUnique )
			{
				cltGuildInfo* pGuild = pclGuildManager->GetGuildInfo( pclGuildDungeonMgr->m_clUnit[i].m_siGuildUnique );
				if ( pGuild )
				{
					//--------------------------------------------------------------------------
					SI32 siGuildGP		=	0	;	// ��� �� GP
					// ����� GP��� ��
					if ( true == IsWhereServiceArea(ConstServiceArea_NHNChina | ConstServiceArea_EUROPE) )
					{
						siGuildGP = Calc_GiveGP_Exception( pclGuildDungeonMgr->m_clUnit[i].GetExp() );
					}
					else
					{
						siGuildGP = Calc_GiveGP( pclGuildDungeonMgr->m_clUnit[i].GetExp() );
					}
					m_siitemUnique = 0;	// ������ ����ũ�� ������ ������ ������ 0���� �ʱ�ȭ 
					siitemNum = pclClient->pclGuildDungeonItemMgr->GetItem( pclGuildDungeonMgr->m_clUnit[i].m_siMapIndex, siGuildGP, &m_siitemUnique );	// ���� �������� ����ũ�� ������ ������ �´�.
					// �������� �������� ���� �Ѵ�.
					if ( siitemNum > 0 && m_siitemUnique > 0)	
					{
						// �������� ������ �����Ѵ�.
						cltItem clInputItem;
						SI16 bRareSwitch = 0;
						pclClient->pclItemManager->MakeRandItemUnique(m_siitemUnique, &clInputItem, 0, 0, &bRareSwitch);
						clInputItem.siItemNum = siitemNum;
						pclserver->SendPostOfficeItemToPerson( pGuild->siMasterPersonID, &clInputItem , NULL ,0  );
					}
					//--------------------------------------------------------------------------
					//--------------------------------------------------------------------------
					for (  SI32 sii = 0; sii < MAX_GUILDDUNGEON; sii++ ) 
					{

						if ( pclGuildDungeonMgr->m_clUnit[i].m_siGuildUnique != pclMsg->clChangedGuildInfo[sii].siGuildUnique ) continue	;
						SI32 AddExp   = pclMsg->clChangedGuildInfo[sii].siAddExp;
						GMONEY AddMoney = pclMsg->clChangedGuildInfo[sii].siAddMoney;
						if(AddExp   < 0)	AddExp	 = 0;
						if(AddMoney < 0)	AddMoney = 0;

						//���� �ִ´� .
						if ( pclClient->IsCountrySwitch(Switch_NewGuildHuntMapWar ))
						{
							// NEW ����ڱ����� ���� �ִ´�

							sDBRequest_Guild_GiveGuildMoney clMsg(pclGuildDungeonMgr->m_clUnit[i].m_siGuildUnique , 0 ,0 , AddMoney);
							SendDBMsg(DBSELECT_BASE,(sPacketHeader *)&clMsg);

						}
						else
						{
							// (��)	����忡�� ���� �ش�
							SI32 masterCharID = pclCM->GetIDFromPersonID(pGuild->siMasterPersonID);
							if(pclClient->pclCM->IsValidID(masterCharID))
							{
								pclCM->CR[ masterCharID ]->pclCI->clBank.IncreaseMoney( AddMoney );
								pclCM->CR[ masterCharID ]->SetUpdateSwitch(UPDATE_BANK, true, 0);
							}
						}
						//--------------------------------------------------------------------------
						//--------------------------------------------------------------------------					
						// ��� ����Ʈ �� �ø���.
						pGuild->clGPoint.siPoint += AddExp ;
						// ����ġ�� �ö󰡸� ������ ����Ų��.
						SI32 level = pGuild->clGPoint.siLevel ;
						SI32 nextlevel = GetLevelFromExp( pGuild->clGPoint.siPoint, EXPFORLEVEL_TYPE_GUILD );
						if ( level < nextlevel && pGuild->clGPoint.siLevel < MAX_GUILD_LEVEL )
						{
							sDBRequest_Guild_LevelUP clMsg(pGuild->siUnique,nextlevel);
							pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&clMsg);
						}
						// ����ġ�� �ٿ�Ǹ� ������ �ٿ��Ų��.
						level = pGuild->clGPoint.siLevel ;
						nextlevel = GetLevelFromExp( pGuild->clGPoint.siPoint, EXPFORLEVEL_TYPE_GUILD );
						if ( level > nextlevel && pGuild->clGPoint.siLevel > 1 )
						{
							sDBRequest_Guild_LevelUP clMsg(pGuild->siUnique,nextlevel);
							pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&clMsg);
						}
						// �������� ȹ���� ����ġ�� ���� �˷��ش�.
						cltLetterMsg_GuildDungeon_ChangeGPMoney clletter( 	AddExp, AddMoney, m_siitemUnique,siitemNum		);

						for ( SI16 j=0; j<MAX_GUILD_MEMBER_NUM; j++ )
						{
							if ( pGuild->clMember[j].siPersonID > 0 )
							{
								if( pGuild->clMember[j].siType == GUILDRANKTYPE_STANDING )
									continue;

								SendLetterMsg( pGuild->clMember[j].siPersonID, (cltLetterHeader*)&clletter);
							}
						}
					}

					//--------------------------------------------------------------------------
					//--------------------------------------------------------------------------
				}
			}
		}

		for ( SI32 i = 0; i < MAX_GUILDDUNGEON; i++ )
		{
			// ����� ������ �ʱ�ȭ
			pclGuildDungeonMgr->m_clUnit[i].m_siGuildUnique = 0;
			pclGuildDungeonMgr->m_clUnit[i].m_siExp = 0;
			pclGuildDungeonMgr->m_clUnit[i].m_siMoney = 0;

			// ����� ������ ����
			if ( pclMsg->clNewOwnerInfo[i].siGuildUnique > 0  )
			{
				pclGuildDungeonMgr->SetStatus( pclMsg->clNewOwnerInfo[i].siMapindex, pclMsg->clNewOwnerInfo[i].siGuildUnique, 0, 0 );

				cltGuildInfo* pGuild = pclGuildManager->GetGuildInfo(pclMsg->clNewOwnerInfo[i].siGuildUnique );
				if ( pGuild )
				{
					// �ڸ������ �˷���
					TCHAR* pTitle = GetTxtFromMgr(6755);
					TCHAR* pText = GetTxtFromMgr(6756);
					TCHAR buf[256] = TEXT("");
					StringCchPrintf( buf, 256, pText, pGuild->GetName(),
						pclMapManager->GetMapName(pclMsg->clNewOwnerInfo[i].siMapindex));

					pclserver->PushSpecialNews( buf, pTitle ,NULL, CAPTIONKIND_GUILD,CAPTIONKIND_NEWSCHAT);


					// �����鿡�� �������� ������� �˷��ش�.
					cltLetterMsg_GuildDungeon_GetOwnerShip clletter( pclMsg->clNewOwnerInfo[i].siMapindex );
					for ( SI16 j=0; j<MAX_GUILD_MEMBER_NUM; j++ )
					{
						if ( pGuild->clMember[j].siPersonID > 0 )
						{
							if( pGuild->clMember[j].siType == GUILDRANKTYPE_STANDING )
								continue;

							SendLetterMsg( pGuild->clMember[j].siPersonID, (cltLetterHeader*)&clletter);
						}
					}
				}
			}
		}

		for ( SI32 i = 0; i < MAX_GUILD_NUM ; i ++ )
		{
			// ����� ������ ��û �ʱ�ȭ
			pclGuildManager->clUnit[i].clGPoint.siApplyMapIndex = 0;
			pclGuildManager->clUnit[i].clGPoint.siBattleGP = 0;
			// ����� ���������� �ʱ�ȭ �Ǿ����ϴ�.
			// ����ȳ������� ����͸� ��û�Ҽ� �ֽ��ϴ�
			for ( SI32 siMember = 0; siMember < MAX_GUILD_MEMBER_NUM; siMember++) 
			{
				SI32 siMemberID = pclGuildManager->clUnit[i].clMember[siMember].siPersonID	;
				SI32 siID = pclserver->pclCM->GetIDFromPersonID(siMemberID)	;
				if (pclserver->pclCM->IsValidID(siID)) 
				{
					SI32 returnval = SRVAL_RETURN_CANNOTGUILDWAR_RESEASON;
					pclserver->SendServerResponseMsg( 0, returnval,  0, 0, pclserver->pclCM->CR[siID]->GetCharUnique() );
				}
			}

		}
	}
}

// ��Ȱ�� �޸��� üũ �޼���
void cltServer::DoMsg_DBMSG_RESPONSE_GUILD_CHECKDESTROY_MONTH(sPacketHeader* pPacket)
{
	sDBResponse_Guild_CheckDestroy_Month* pclMsg = (sDBResponse_Guild_CheckDestroy_Month*)pPacket;

	if(pclClient->IsCountrySwitch(Switch_Guild_DestroyOverMOnth)){
		// ����Ʈ�� �޾Ƽ� �ش� ���� �޸� ���� ���� �ϰ� �ش� ����� ȸ������ Ż�� ��Ų��.
		if ( pclMsg->siResult == 1) {// ������ ������ ��� ��
			for ( SI32 index = 0 ; index < MAX_GUILD_PER_DBLIST ; index ++ ){
				// �ش� ��� �ε��� ������ ������ �´�
				cltGuildInfo* pGuildInfo = &pclMsg->clInfo[index] ;
				if ( pGuildInfo->siUnique <= 0 ) continue ;
				//// ��� �ɹ��� Ż�� ��Ų��.
				//for( SI16 membernum = 0; membernum < MAX_GUILD_MEMBER_NUM; membernum++){
				//	if( pGuildInfo->clMember[ membernum ].siPersonID <= 0) continue;
				//	sDBRequest_Guild_LeaveGuild clMsg( pGuildInfo->clMember[membernum ].siPersonID, pGuildInfo->siUnique );
				//	pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&clMsg);
				//}
				// �ڵ�������� ������ �߰� �ؼ� ������ �ڴ�
				sDBRequest_Guild_DestroyGuild clMsg( 0,0,pGuildInfo->siUnique,pGuildInfo->siVillageUnique, 4 );
				pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&clMsg);
			}
		}
	}

}
// �Ѵ��̻� ���� ���� ��� �� ����
void cltServer::DoMsg_DBMSG_RESPONSE_GUILD_NOTCONNECT_GUILDMASTER(sPacketHeader* pPacket)
{
	if( false == pclClient->IsCountrySwitch(Switch_Guild_GuildMaster_Change) )
	{
		return;
	}

	sDBResponse_Guild_NotConnect_ChangeMaster* pclMsg = (sDBResponse_Guild_NotConnect_ChangeMaster*)pPacket;
	if ( NULL == pclMsg )
	{
		return;
	}
	
	// �����ߴٸ�
	if( pclMsg->siResult < 1 )
	{
		SI32 id	= pclMsg->siCharID;	
		SendServerResponseMsg(0, SRVAL_GUILD_FAIL_NOTCONNECTMASTER, 0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}

	cltGuildInfo* pclGuild = pclGuildManager->GetGuildInfo(pclMsg->clInfo.siUnique);
	if ( NULL == pclGuild )
	{
		return ;
	}
	pclGuild->Set(&pclMsg->clInfo);

	// ���� ��ü���� ���� ������
	for ( SI32 siIndex=0; siIndex<MAX_GUILD_MEMBER_NUM; ++siIndex )
	{
		SI32 siPersonID = pclGuild->clMember[siIndex].siPersonID;
		if ( 0 >= siPersonID )
		{
			continue;
		}

		SI32 siCharID = pclCM->GetIDFromPersonID( siPersonID );
		
		// ������ �ִٸ�
		if ( pclCM->IsValidID(siCharID) )
		{
			cltCharServer* pclchar = (cltCharServer*)pclCM->CR[siCharID];
			if ( NULL == pclchar )
			{
				continue;
			}
			
			// ������ ������� �������� ����(�׷��� �̰����� ���� ���ɼ��� ������?)
			if ( (siPersonID != pclMsg->siNewPersonID) && (GUILDRANKTYPE_MASTER == pclchar->pclCI->clBI.clGuildRank.siType) )
			{
				pclchar->pclCI->clBI.clGuildRank.siType = GUILDRANKTYPE_MEMBER;
			}
			// ���Ӱ� �ٲ� ��� �����Ͷ�� ���� ����
			else if ( siPersonID == pclMsg->siNewPersonID )
			{
				pclchar->pclCI->clBI.clGuildRank.siType = GUILDRANKTYPE_MASTER;
			}

			cltGameMsgResponse_Guild_SetGuildStatus clinfo( &pclGuild->clStatus, &pclchar->pclCI->clBI.clGuildRank, pclchar->GetCharUnique());
			cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_SETGUILDSTATUS, sizeof(clinfo), (BYTE*)&clinfo);
			pclchar->SendNeighbourMsg(&clMsg,true);
		}

		// ������ ����
		cltLetterMsg_Guild_ChangeMaster_Notconnect_Month clletter( pclMsg->szNewPersonName );
		SendLetterMsg(  siPersonID, (cltLetterHeader*)&clletter );

	}


	SI32 charid = pclMsg->siCharID;

	if ( pclCM->IsValidID(charid) )
	{
		cltCharServer* pclchar = (cltCharServer*)pclCM->CR[charid];
		if ( pclchar == NULL )
			return ;

		if ( pclchar->pclCI->GetPersonID() == pclMsg->siPersonID )
		{
			cltGameMsgResponse_Guild_ChangeMaster clinfo(pclMsg->siResult,&pclMsg->clInfo);
			cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_CHANGEMASTER, sizeof(clinfo), (BYTE*)&clinfo);
			pclchar->SendNetMsg((sPacketHeader*)&clMsg);


			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog))
			{
				// [����] �Ѵ��̻� ������ ��� ������ ����
				// param1		 == ��� ����ũ, 
				// pszCharParam1 == ��� �̸�.
				cltServer * pclServer = (cltServer*)pclClient;
				pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_GUILD, LOGCOMMAND_INDEX_GUILD_MASTERCHANGE_NOTCONNECT_MONTH,
					0, pclchar, NULL, pclMsg->siNewPersonID, 0, 0, NULL, 0, 0, 0, pclMsg->clInfo.siVillageUnique, 0, 0, 
					pclMsg->clInfo.siUnique, 0, 0, 0, 0,
					pclMsg->clInfo.szName, NULL);
			}
		}
	}

}
void cltServer::DoMsg_DBMSG_RESPONSE_GUILDHUNTMAPWAR_REGLIST(sPacketHeader* pPacket)
{
	sDBResponse_GuildHuntMapWar_SaveRegList* pclMsg = (sDBResponse_GuildHuntMapWar_SaveRegList*)pPacket;
	if ( NULL == pclMsg )			return;
	// �����ߴٸ�
	if( pclMsg->siResult < 1 )		return;

	if ( pclMsg->siType == DelList)
	{
		// ��û ����Ʈ�� �ش� �������ũ�� �ִ´�.
		SI32 siGuildunique = pclMsg->siGuildUnique	;
		pclGuildHuntMapManager->Delete(siGuildunique)	;
	}
	else
	{
		// ��û ����Ʈ�� �ش� �������ũ�� �ִ´�.
		SI32 siGuildunique = pclMsg->siGuildUnique	;
		pclGuildHuntMapManager->add(siGuildunique)	;
		cltGuildInfo* pclGuild = pclGuildManager->GetGuildInfo(siGuildunique);
		if ( pclGuild == NULL ) return ;

		if ( pclClient->IsCountrySwitch(Switch_NewGuildHuntMapWar))
		{
			// �����鿡�� ���� �޼��� ����
			cltLetterMsg_GuildDungeon_Apply_New clletter(0);
			for ( SI16 i=0; i<MAX_GUILD_MEMBER_NUM; i++ )
			{
				if ( pclGuild->clMember[i].siPersonID > 0 )
				{
					SendLetterMsg( pclGuild->clMember[i].siPersonID, (cltLetterHeader*)&clletter);
				}
			}
		}
		else
		{
			// �����鿡�� ���� �޼��� ����
			cltLetterMsg_GuildDungeon_Apply clletter(0);
			for ( SI16 i=0; i<MAX_GUILD_MEMBER_NUM; i++ )
			{
				if ( pclGuild->clMember[i].siPersonID > 0 )
				{
					SendLetterMsg( pclGuild->clMember[i].siPersonID, (cltLetterHeader*)&clletter);
				}
			}

			
		}
	}
}


void cltServer::DoMsg_DBMSG_RESPONSE_GUILDHUNTMAPWAR_GETTOP10(sPacketHeader* pPacket)
{
	cltServer* pclserver = (cltServer*)pclClient;

	sDBResponse_GuildHuntMapWar_Rank_Get* pclMsg = (sDBResponse_GuildHuntMapWar_Rank_Get*)pPacket;

	if(pclMsg == NULL)			return	;

	SI32 siPersonID = pclMsg->siPersonID;
	cltCharCommon* pclchar = pclserver->pclCM->GetChar( pclserver->pclCM->GetIDFromPersonID(siPersonID));

	// ��� �̸��� ��� �ش�.
	for ( SI32 siGuildSLot = 0; siGuildSLot < MAX_GUILDHUNTWAR_RANK_NUM; siGuildSLot++) 
	{
		SI32 siGuildUnique = pclMsg->m_GuildList[siGuildSLot].GetGuildUnique()	;
			if(siGuildUnique == 0)	break;
		TCHAR* szGuildName = pclserver->pclGuildManager->GetGuildName( siGuildUnique );
		if(szGuildName == NULL) return;
		pclMsg->m_GuildList[siGuildSLot].SetGuildName(szGuildName)	;
	}
	cltGameMsgResponse_GuilHuntMapdWar_GetTopTen clinfo( pclMsg->m_GuildList);
	cltMsg clMsg(GAMEMSG_RESPONSE_GUILDHUNTMAPWAR_GETTOP10, sizeof(clinfo), (BYTE*)&clinfo);
	pclchar->SendNetMsg((sPacketHeader*)&clMsg);	
}
void cltServer::DoMsg_DBMSG_RESPONSE_GUILDHUNTMAPWAR_RESULT(sPacketHeader* pPacket)
{
	sDBResponse_GuildHuntMapWar_Result* pclMsg = (sDBResponse_GuildHuntMapWar_Result*)pPacket;
	if (pclMsg->siResult == 1 )
	{
		cltGuildInfo* pclGuild = pclGuildManager->GetGuildInfo( pclMsg->siGuildunique );
		if ( pclGuild == NULL ) return ;
		pclGuild->clGPoint.siBattleGP	=	pclGuild->clGPoint.siBattleGP+pclMsg->siBGP	;	// bgp����

		for ( SI32 i = 0 ; i < MAX_GUILD_MEMBER_NUM ; i ++ )
		{
			// �ɸ��� ���̵� ã�´�.
			//------------------------------------------------------------------------------------
			SI32 siMemberPeronID = pclGuild->clMember[i].siPersonID	;

			SI32 sicharID	=	pclClient->pclCM->GetIDFromPersonID(siMemberPeronID)	;
			//------------------------------------------------------------------------------------
			if ( pclClient->pclCM->IsValidID(sicharID) ) 
			{
				cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[sicharID];
				cltGameMsgResponse_Guild_SetGuildStatus clinfo(&pclGuild->clStatus,&pclchar->pclCI->clBI.clGuildRank, pclchar->CharUnique);
				cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_SETGUILDSTATUS, sizeof(clinfo), (BYTE*)&clinfo);
				pclchar->SendNeighbourMsg(&clMsg,true);
			}
		}
	}
}
