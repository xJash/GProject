#include <CommonLogic.h>
#include "Char/CharCommon/Char-Common.h"
#include "Char/CharManager/CharManager.h"

#include "../Server/Server.h"

#include "GuildWar.h"
#include "../CommonLogic/MsgType-Guild.h"

#include "../../DBManager/GameDBManager_World/DBMsg-Guild.h"

#include "../Client/MarkManager/MarkManager.h"
#include "../Server/ServerEvent/ServerEvent_Manager.h"
//#include "../CommonLogic/Guild/GuildHuntMapWarStatMgr.h"

#define MAX_GUILDWAR_DRINK_POTION	5

#define GUILDWAR_NOTICE_START		1
#define GUILDWAR_NOTICE_WIN			2
#define	GUILDWAR_NOTICE_LOSE		3
#define GUILDWAR_NOTICE_DRAW		4 

extern cltCommonLogic* pclClient;

//------------------------------------------------------------------------------------
// cltGuildWarManager
//------------------------------------------------------------------------------------
cltGuildWarManager::cltGuildWarManager()
{
	Init();
}

cltGuildWarManager::~cltGuildWarManager()
{

}

// �����ϰ� �����ִ� �Լ�. ������ ���۵ɶ� ȣ�����ְ� ������ �����ؾ��Ѵ�.
void cltGuildWarManager::Init()
{
	m_siHomeGuildUnique		=	0;		// ���1 ����ũ
	m_szHomeGuildName[0]	=	'\0';
	m_siHomeGuildKill		=	0;		// ���1 ���μ���
	m_siAwayGuildUnique		=	0;		// ���2 ����ũ
	m_szAwayGuildName[0]	=	'\0';
	m_siAwayGuildKill		=	0;		// ���2 ���μ���
	
	m_siHomePersonID.ZeroMem();
	m_siAwayPersonID.ZeroMem();

	m_siHomePersonDrinkPutionCnt.ZeroMem();
	m_siAwayPersonDrinkPutionCnt.ZeroMem();

	m_HomePersonDeadClock.ZeroMem();
	m_AwayPersonDeadClock.ZeroMem();
	
	m_WarStartClock = 0;

	m_bStartedWar = false;
	m_bCheckTenSecond = false;

	m_WarEndClock = 0;
	m_bEndWar = false;
}

// ������ ��� ���õ� ���¿��� ȣ���� �ִ� �Լ�. �������� ���������� ���þȵǾ������� �ٷ� ������.
bool cltGuildWarManager::StartGame()
{
	cltServer * pclServer = (cltServer*)pclClient;

	if( m_siHomeGuildUnique <= 0 || m_siAwayGuildUnique <= 0 )				return false;

	if( m_siHomePersonID[0] == 0 && m_siAwayPersonID[0] == 0 )
	{
		{
			sDBRequest_Guild_ChangeGuildPoint clMsg(m_siHomeGuildUnique, 0 , -100 ,TYPE_GUILDPOINT_GUILDWAR);
			pclServer->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
		}
		{
			sDBRequest_Guild_ChangeGuildPoint clMsg(m_siAwayGuildUnique, 0 , -100 ,TYPE_GUILDPOINT_GUILDWAR);
			pclServer->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
		}
		{
			sDBRequest_Guild_GiveGuildMoney clMsg(m_siHomeGuildUnique , 0 ,0 , -1000);
			pclServer->SendDBMsg(DBSELECT_BASE,(sPacketHeader *)&clMsg);
		}
		{
			sDBRequest_Guild_GiveGuildMoney clMsg(m_siAwayGuildUnique , 0 ,0 , -1000);
			pclServer->SendDBMsg(DBSELECT_BASE,(sPacketHeader *)&clMsg);
		}

		// TODO : �޼��� �˷��ٰ�!!

		return false;
	}


	// ���� �ð� ����
	m_WarStartClock = pclServer->CurrentClock;
	
	m_bStartedWar = true;	

	// [����] ���� �̺�Ʈ : ����� ���� �˻�
	if ( pclClient->IsCountrySwitch(Switch_Server_Event) )
	{
		pclServer->pclServerEventManager->GetServerEvent_Quest()->IncServerEventQuestCondition( SERVEREVENT_TYPE_OPEN_GVG, 0, 1 );
	}

	return true;
}


bool cltGuildWarManager::AddMember(SI32 personID, SI32 guildUnique )
{
	for( SI32 i = 0; i < MAX_GUILD_MEMBER_NUM; i++ )
	{
		if( guildUnique == m_siHomeGuildUnique )
		{
			if( m_siHomePersonID[i] == 0 )
			{
				m_siHomePersonID[i] = personID;
				return true;
			}
            
		}
		else if( guildUnique == m_siAwayGuildUnique )
		{
			if( m_siAwayPersonID[i] == 0 )
			{
				m_siAwayPersonID[i] = personID;
				return true;
			}
		}
	}

	return false;
}

bool cltGuildWarManager::RemoveMember(SI32 personID)
{
	for( SI32 i = 0; i < MAX_GUILD_MEMBER_NUM; i++ )
	{
		if( m_siHomePersonID[i] == personID )
		{
			m_siHomePersonID[i] = 0;
			m_siHomePersonDrinkPutionCnt[i] = 0;
			return true;
		}

		if( m_siAwayPersonID[i] == personID )
		{
			m_siAwayPersonID[i] = 0;
			m_siAwayPersonDrinkPutionCnt[i] = 0;
			return true;
		}
	}
	return false;

}


// ��� ������ �����Ҽ� �ִ��� ����
bool cltGuildWarManager::CanAttack(SI32 myGuildUnique, SI32 targetGuildUnique)
{
	if (m_bStartedWar == false)
		return false;

	if ( m_bCheckTenSecond == false )
		return false;

	if( myGuildUnique == m_siHomeGuildUnique && targetGuildUnique == m_siAwayGuildUnique )
		return true;

	if( myGuildUnique == m_siAwayGuildUnique && targetGuildUnique == m_siHomeGuildUnique )
		return true;
	
	return false;
}

bool cltGuildWarManager::DrinkPotion(SI32 personID)
{
	for( SI32 i = 0; i < MAX_GUILD_MEMBER_NUM; i ++ )
	{
		if( m_siHomePersonID[i] == personID )
		{
			m_siHomePersonDrinkPutionCnt[i] += 1;
            
			return true;
		}
		if( m_siAwayPersonID[i] == personID )
		{
			m_siAwayPersonDrinkPutionCnt[i] += 1;
			
			return true;
		}
	}
	
	return false;
}

// ������ �Դµ� ������ �д�.
bool cltGuildWarManager::CanDrinkPotion(SI32 personID)
{
	// ��������
	for( SI32 i = 0; i < MAX_GUILD_MEMBER_NUM ; i++ )
	{
		if( m_siHomePersonID[i] == personID  )
		{
			if(m_siHomePersonDrinkPutionCnt[i] >= MAX_GUILDWAR_DRINK_POTION)
				return false;
			else
				return true;
		}
		if( m_siAwayPersonID[i] == personID  )
		{
			if(m_siAwayPersonDrinkPutionCnt[i] >= MAX_GUILDWAR_DRINK_POTION)
				return false;
			else
				return true;
		}
	}

	return true;
}

// ��������� ������ ���� ���� ���� ó�����ִ� �Լ�. �������� ���� �ʱ�ȭ���ش�.
void cltGuildWarManager::GuildWarEnd()
{
	// TODO : ������� ���ó��

	m_bStartedWar = false;
	m_bCheckTenSecond = false;
	m_WarStartClock = 0;
	m_bEndWar = true;
	m_WarEndClock = pclClient->CurrentClock;

	cltServer* pclserver = (cltServer*)pclClient;

	// �� ��忡�� �� GP�� ���� ����Ѵ�.
	SI32 homeGiveGP = ( m_siHomeGuildKill - m_siAwayGuildKill ) * 10;
	SI32 awayGiveGP = ( m_siAwayGuildKill - m_siHomeGuildKill ) * 10;

	cltGuildInfo* pclHomeGuild = pclClient->pclGuildManager->GetGuildInfo( m_siHomeGuildUnique );
	cltGuildInfo* pclAwayGuild = pclClient->pclGuildManager->GetGuildInfo( m_siAwayGuildUnique );

	if ( pclHomeGuild == NULL || pclAwayGuild == NULL )
		return;
	
	SI32 homeCurrGP = pclHomeGuild->clGPoint.siPoint;
	SI32 awayCurrGP = pclAwayGuild->clGPoint.siPoint;
	if ( pclClient->IsCountrySwitch(Switch_NewGuildHuntMapWar) )// ���� �ǰ� ������ ���и� �����ش�.
	{
		// ����� ���и� ������.
		SI32 HomeResult = m_siHomeGuildKill - m_siAwayGuildKill	;
		SI32 AwayResult = m_siAwayGuildKill - m_siHomeGuildKill	;
		
		// ���� ��� �ڸ� ���
		TCHAR* pTitle = GetTxtFromMgr(6749);
		TCHAR buf[256] = TEXT("");
		StringCchPrintf( buf, 256, TEXT("%s %d : %d %s"), m_szHomeGuildName, m_siHomeGuildKill, m_siAwayGuildKill, m_szAwayGuildName );
		pclserver->PushSpecialNews( buf, pTitle ,NULL, CAPTIONKIND_NEWS,CAPTIONKIND_NEWSCHAT);

		// ����� Ŭ���̾�Ʈ�� �˸�
		for ( SI32 i = 0 ; i < MAX_GUILD_MEMBER_NUM ; i ++ )
		{
			SI32 charID = pclClient->pclCM->GetIDFromPersonID( m_siHomePersonID[i] );
			if ( pclClient->pclCM->IsValidID( charID ) ) // �������ִٸ�
			{
				cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[charID];

				if (pclClient->pclCM->IsAlive( charID ) == false) // ����� ������ �׾� �ִٸ� �츰��.
				{
					pclClient->pclCM->CR[charID]->Revive();
				}

				pclchar->pclCI->clBI.clGuildRank.SetEnemyGuild(0);
				{
					cltGameMsgResponse_Guild_SetGuildStatus clinfo( &pclHomeGuild->clStatus, &pclchar->pclCI->clBI.clGuildRank, pclchar->GetCharUnique() );
					cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_SETGUILDSTATUS, sizeof(clinfo), (BYTE*)&clinfo);
					pclchar->SendNeighbourMsg(&clMsg,true);
				}
				{
					cltGameMsgResponse_GuildWar_End clinfo( HomeResult, 0 );
					cltMsg clMsg(GAMEMSG_RESPONSE_GUILDWAR_END, sizeof(clinfo), (BYTE*)&clinfo);
					pclchar->SendNetMsg((sPacketHeader*)&clMsg);
				}
			}

			charID = pclClient->pclCM->GetIDFromPersonID( m_siAwayPersonID[i] );
			if ( pclClient->pclCM->IsValidID( charID ) ) // �������ִٸ�
			{
				cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[charID];

				pclchar->pclCI->clBI.clGuildRank.SetEnemyGuild(0);
				{
					cltGameMsgResponse_Guild_SetGuildStatus clinfo(&pclHomeGuild->clStatus,&pclchar->pclCI->clBI.clGuildRank,pclchar->GetCharUnique());
					cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_SETGUILDSTATUS, sizeof(clinfo), (BYTE*)&clinfo);
					pclchar->SendNeighbourMsg(&clMsg,true);
				}
				{
					cltGameMsgResponse_GuildWar_End clinfo( AwayResult, 0 );
					cltMsg clMsg(GAMEMSG_RESPONSE_GUILDWAR_END, sizeof(clinfo), (BYTE*)&clinfo);
					pclchar->SendNetMsg((sPacketHeader*)&clMsg);
				}
			}
		}

		// PCK : �α� �߰� - ����� ��� (09.07.31)
		// param1 : HomeGuildKill, param2 : AwayGuildKill, param3 : HomeGuildResult, param4, AwayGuildResult, Charparam1 : HomeGuildName, CharParam2 : AwayGuildName
		cltServer* pclserver = (cltServer*)pclClient;

		pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_GUILD, LOGCOMMAND_INDEX_GUILD_WARRESULT, 
			0,NULL, NULL , 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
			m_siHomeGuildKill, m_siAwayGuildKill, HomeResult, AwayResult, 0, m_szHomeGuildName, m_szAwayGuildName);

	}
	else	/// ���� ȹ���� ����� ���� ��
	{
		// ���� GP�� ���ڸ� ��쿡 ����� GP����
		if ( homeGiveGP < 0 )
		{
			if ( homeCurrGP <= 0 )
			{
				homeGiveGP = 0;
				awayGiveGP = 0;
			}
			else if ( homeCurrGP + homeGiveGP < 0 )
			{
				homeGiveGP = -homeCurrGP;
				awayGiveGP = homeCurrGP;
			}
		}
		else if ( awayGiveGP < 0 )
		{
			if ( awayCurrGP <= 0 )
			{
				homeGiveGP = 0;
				awayGiveGP = 0;
			}
			if ( awayCurrGP + awayGiveGP < 0 )
			{
				homeGiveGP = awayCurrGP;
				awayGiveGP = -awayCurrGP;
			}
		}

		{
			sDBRequest_Guild_ChangeGuildPoint clMsg(m_siHomeGuildUnique,0 ,homeGiveGP,TYPE_GUILDPOINT_GUILDWAR);
			pclserver->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
		}
		{
			sDBRequest_Guild_ChangeGuildPoint clMsg(m_siAwayGuildUnique,0 ,awayGiveGP,TYPE_GUILDPOINT_GUILDWAR);
			pclserver->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
		}

		// ���� ��� �ڸ� ���
		TCHAR* pTitle = GetTxtFromMgr(6749);
		TCHAR buf[256] = TEXT("");
		StringCchPrintf( buf, 256, TEXT("%s %d : %d %s"), m_szHomeGuildName, m_siHomeGuildKill, m_siAwayGuildKill, m_szAwayGuildName );

		pclserver->PushSpecialNews( buf, pTitle ,NULL, CAPTIONKIND_NEWS,CAPTIONKIND_NEWSCHAT);

		// ������ ���� ���� ��� �����Ϳ��� ���� �������� �����ش�
		if ( pclClient->IsWhereServiceArea( ConstServiceArea_China ) == false )
		{
			SI32 winnerGuildMaster = 0;
			SI16 itemNum =  0  ;
			SI32 pointGap = m_siHomeGuildKill - m_siAwayGuildKill ;
			if (pointGap > 0 ) {
				if( pointGap >= 20 )
				{
					winnerGuildMaster = pclHomeGuild->siMasterPersonID;
					itemNum = 5;
				}
				else if( pointGap >= 10 && pointGap < 20)
				{
					winnerGuildMaster = pclHomeGuild->siMasterPersonID;
					itemNum = 2;	
				}
				else if( pointGap > 0 && pointGap < 10  )
				{
					winnerGuildMaster = pclHomeGuild->siMasterPersonID;
					itemNum = 1;	
				}
			}
			if (pointGap< 0 ) {
				if( pointGap <  0 && pointGap >  -10)
				{
					winnerGuildMaster = pclAwayGuild->siMasterPersonID;
					itemNum = 1;	
				}
				else if( pointGap <=  -10 && pointGap >=  -19 )
				{
					winnerGuildMaster = pclAwayGuild->siMasterPersonID;
					itemNum = 2;	
				}
				else if( pointGap <=  -20 )
				{
					winnerGuildMaster = pclAwayGuild->siMasterPersonID;
					itemNum = 5;	
				}
			}		


			if( winnerGuildMaster > 0 && itemNum > 0 )
			{
				cltItem clInputItem;
				SI16 bRareSwitch = 0;
				SI32 ItemUnique = ITEMUNIQUE(3860);

				pclClient->pclItemManager->MakeRandItemUnique( ItemUnique,&clInputItem,0,0,&bRareSwitch);

				clInputItem.siItemNum = itemNum;

				((cltServer*)pclClient)->SendPostOfficeItemToPerson( winnerGuildMaster, &clInputItem , NULL ,0  );
			}
		}

		for ( SI32 i = 0 ; i < MAX_GUILD_MEMBER_NUM ; i ++ )
		{
			SI32 charID = pclClient->pclCM->GetIDFromPersonID( m_siHomePersonID[i] );
			if ( pclClient->pclCM->IsValidID( charID ) ) // �������ִٸ�
			{
				cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[charID];

				if (pclClient->pclCM->IsAlive( charID ) == false) // ����� ������ �׾� �ִٸ� �츰��.
				{
					pclClient->pclCM->CR[charID]->Revive();
				}

				pclchar->pclCI->clBI.clGuildRank.SetEnemyGuild(0);
				{
					cltGameMsgResponse_Guild_SetGuildStatus clinfo( &pclHomeGuild->clStatus, &pclchar->pclCI->clBI.clGuildRank, pclchar->GetCharUnique() );
					cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_SETGUILDSTATUS, sizeof(clinfo), (BYTE*)&clinfo);
					pclchar->SendNeighbourMsg(&clMsg,true);
				}
				{
					cltGameMsgResponse_GuildWar_End clinfo( homeGiveGP, 0 );
					cltMsg clMsg(GAMEMSG_RESPONSE_GUILDWAR_END, sizeof(clinfo), (BYTE*)&clinfo);
					pclchar->SendNetMsg((sPacketHeader*)&clMsg);
				}
			}

			charID = pclClient->pclCM->GetIDFromPersonID( m_siAwayPersonID[i] );
			if ( pclClient->pclCM->IsValidID( charID ) ) // �������ִٸ�
			{
				cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[charID];

				pclchar->pclCI->clBI.clGuildRank.SetEnemyGuild(0);
				{
					cltGameMsgResponse_Guild_SetGuildStatus clinfo(&pclHomeGuild->clStatus,&pclchar->pclCI->clBI.clGuildRank,pclchar->GetCharUnique());
					cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_SETGUILDSTATUS, sizeof(clinfo), (BYTE*)&clinfo);
					pclchar->SendNeighbourMsg(&clMsg,true);
				}
				{
					cltGameMsgResponse_GuildWar_End clinfo( awayGiveGP, 0 );
					cltMsg clMsg(GAMEMSG_RESPONSE_GUILDWAR_END, sizeof(clinfo), (BYTE*)&clinfo);
					pclchar->SendNetMsg((sPacketHeader*)&clMsg);
				}
			}
		}

		// PCK : �α� �߰� - ����� ��� (09.07.31)
		// param1 : HomeGuildKill, param2 : AwayGuildKill, param3 : HomeGuildGP, param4, AwayGuildGP, Charparam1 : HomeGuildName, CharParam2 : AwayGuildName
		cltServer* pclserver = (cltServer*)pclClient;

		pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_GUILD, LOGCOMMAND_INDEX_GUILD_WARRESULT, 
			0,NULL, NULL , 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
			m_siHomeGuildKill, m_siAwayGuildKill, homeGiveGP, awayGiveGP, 0, m_szHomeGuildName, m_szAwayGuildName);
	}
}

// ��������� �׾��� ��� ���� ó���� ���ش�.
bool cltGuildWarManager::GuildWarDie(SI32 personID)
{
	cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[pclClient->pclCM->GetIDFromPersonID( personID )];

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

	for ( SI32 i=0; i < MAX_GUILD_MEMBER_NUM ; i++ )
	{
		if ( m_siHomePersonID[i] == personID )
		{	
			SI32 siRand = rand()%4;
			xPos = Const_HomePos[ siRand * 2 ];
			yPos = Const_HomePos[ siRand * 2 + 1];

			// ���� ���Ƚ�� �ʱ�ȭ
			m_siHomePersonDrinkPutionCnt[i] = 0;

			// ���� �ð� ���
			m_HomePersonDeadClock[i] = pclClient->CurrentClock;
		}
		else if ( m_siAwayPersonID[i] == personID )
		{
			SI32 siRand = rand()%4;
			xPos = Const_AwayPos[ siRand * 2 ];
			yPos = Const_AwayPos[ siRand * 2 + 1];

			m_siAwayPersonDrinkPutionCnt[i] = 0;
			m_AwayPersonDeadClock[i] = pclClient->CurrentClock;
		}
	}
	
	cltWarpInfo clWarpInfo(1, pclchar->GetMapIndex(), false, false, xPos, yPos, -1, -1);

	pclchar->SetWarpInfo(&clWarpInfo, 2200);
	pclchar->Warp();

	pclchar->SendDB_PosLifeMana();	

	// Ŭ���̾�Ʈ�� ������Ʈ �Ѵ�. 
	pclchar->SetUpdateSwitch(UPDATE_IP, true, 0);

	return true;
}

bool cltGuildWarManager::IsGod( SI32 personID )
{
	for( SI32 i = 0; i < MAX_GUILD_MEMBER_NUM ; i++ )
	{
		if( m_siHomePersonID[i] == personID  )
		{
			if( TABS(pclClient->CurrentClock - m_HomePersonDeadClock[i]) < GUILDWAR_GODTIME )
				return true;
			else 
				return false;
		}
		if( m_siAwayPersonID[i] == personID  )
		{
			if( TABS(pclClient->CurrentClock - m_AwayPersonDeadClock[i]) < GUILDWAR_GODTIME )
				return true;
			else 
				return false;
		}
	}

	return false;
}

void cltGuildWarManager::Action()
{
	cltServer * pclServer = (cltServer*)pclClient;

	// TODO : ������
	if( m_bStartedWar )
	{
		if(m_bCheckTenSecond == false )
		{
			if ( TABS( pclClient->CurrentClock - m_WarStartClock ) > 60000 )
			{
				// 1�а� �����Ŀ� ���� ����� �����Ѵ�.
				SetEnemy();

				m_bCheckTenSecond = true;
			}
			return;
		}

		SI32 homeUserCount = 0;
		SI32 awayUserCount = 0;

		for ( SI32 i = 0 ; i < MAX_GUILD_MEMBER_NUM ; i ++ )
		{
			SI32 charID = pclClient->pclCM->GetIDFromPersonID( m_siHomePersonID[i] );
			if ( pclClient->pclCM->IsValidID(charID) ) // �������ִٸ�
			{
				cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[charID];
				if( pclServer->IsCountrySwitch(Switch_NewGuildHuntMapWar) )	//������
				{
					if ( IsGuildWarMap_Use_New_GuildWar(pclchar->GetMapIndex()) )
					{
						homeUserCount++;
					}
				}
				else	// ������
				{
					if ( IsGuildWarMap_Not_Use_New_GuildWar(pclchar->GetMapIndex()) )
					{
						homeUserCount++;
					}
				}
			}
			else
			{
				m_siHomePersonID[i] =0;
			}
			charID = pclClient->pclCM->GetIDFromPersonID( m_siAwayPersonID[i] );
			if ( pclClient->pclCM->IsValidID(charID) ) // �������ִٸ�
			{
				cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[charID];
				if( pclClient->IsCountrySwitch( Switch_NewGuildHuntMapWar ) )
				{
					if ( IsGuildWarMap_Use_New_GuildWar( pclchar->GetMapIndex() ) )
					{
						awayUserCount++;
					}

				}
				else
				{
					if ( IsGuildWarMap_Not_Use_New_GuildWar( pclchar->GetMapIndex() ) )
					{
						awayUserCount++;
					}
				}
			}
			else
			{
				m_siAwayPersonID[i] =0;
			}
		}

		// ������� HomeGuild ������ �ϳ��� ���ٸ� �й��̰� AwayGuild�� Kill���� 10 ���� �����ش�.
		if( homeUserCount == 0 )
		{
			m_siAwayGuildKill += 10;
			GuildWarEnd();
		}

		// ������� AwayGuild ������ �ϳ��� ���ٸ� �й��̰� HomeGuild�� Kill���� 10 ���� �����ش�.
		if( awayUserCount == 0 )
		{
			m_siHomeGuildKill += 10;
			GuildWarEnd();
		}

		// 15���� ������ ������ �����Ѵ�.
		if ( TABS( pclClient->CurrentClock - m_WarStartClock ) > 1000 * 60 * GUILDWAR_TIME )
		{
			if ( !m_bEndWar )
			{
				GuildWarEnd();
			}
		}
	}

	if ( m_bEndWar  )
	{
		if ( TABS(pclClient->CurrentClock - m_WarEndClock ) > 10000 )
		{
			// ����� ������ 10�ʰ� ������ �溹������ ���� ��Ų��.
			WarpByEnd();
		}
	}

}  
void cltGuildWarManager::AddKillPoint( SI32 personId )
{
	for( SI32 i = 0; i < MAX_GUILD_MEMBER_NUM ; i++ )
	{
		if( m_siHomePersonID[i] == personId  )
		{
			m_siHomeGuildKill++;
			break;
		}
		else if( m_siAwayPersonID[i] == personId )
		{
			m_siAwayGuildKill++;
			break;
		}
	}


	for ( SI32 i = 0 ; i < MAX_GUILD_MEMBER_NUM ; i ++ )
	{
		SI32 charID = pclClient->pclCM->GetIDFromPersonID( m_siHomePersonID[i] );
		if ( pclClient->pclCM->IsValidID( charID ) ) // �������ִٸ�
		{
			cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[charID];

			// �������� �������� �˷��ش�.
			cltGameMsgResponse_GuildWar_KillPoint clinfo( m_siHomeGuildKill, m_siAwayGuildKill );
			cltMsg clMsg(GAMEMSG_RESPONSE_GUILDWAR_KILLPOINT, sizeof(clinfo), (BYTE*)&clinfo);
			pclchar->SendNetMsg((sPacketHeader*)&clMsg);
		}
		charID = pclClient->pclCM->GetIDFromPersonID( m_siAwayPersonID[i] );
		if ( pclClient->pclCM->IsValidID( charID ) ) // �������ִٸ�
		{
			cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[charID];

			cltGameMsgResponse_GuildWar_KillPoint clinfo( m_siHomeGuildKill, m_siAwayGuildKill );
			cltMsg clMsg(GAMEMSG_RESPONSE_GUILDWAR_KILLPOINT, sizeof(clinfo), (BYTE*)&clinfo);
			pclchar->SendNetMsg((sPacketHeader*)&clMsg);

		}
	}
}

void cltGuildWarManager::WarpByEnd()
{
	m_bEndWar = false;

	for ( SI32 i = 0 ; i < MAX_GUILD_MEMBER_NUM ; i ++ )
	{
		SI32 homeCharID = pclClient->pclCM->GetIDFromPersonID(m_siHomePersonID[i]);
		if ( pclClient->pclCM->IsValidID( homeCharID ) ) // �������ִٸ�
		{
			((cltCharServer*)pclClient->pclCM->CR[homeCharID])->WarpToSafeZone();
		}
		SI32 awayCharID = pclClient->pclCM->GetIDFromPersonID(m_siAwayPersonID[i]);
		if ( pclClient->pclCM->IsValidID( awayCharID ) ) // �������ִٸ�
		{
			((cltCharServer*)pclClient->pclCM->CR[awayCharID])->WarpToSafeZone();
		}
	}
}

void cltGuildWarManager::SetEnemy()
{
	cltGuildInfo* pclHomeGuild = pclClient->pclGuildManager->GetGuildInfo( m_siHomeGuildUnique );
	cltGuildInfo* pclAwayGuild = pclClient->pclGuildManager->GetGuildInfo( m_siAwayGuildUnique );

	if ( pclHomeGuild == NULL ||  pclAwayGuild == NULL )	
		return;

	for ( SI32 i = 0 ; i < MAX_GUILD_MEMBER_NUM ; i ++ )
	{
		SI32 charID = pclClient->pclCM->GetIDFromPersonID( m_siHomePersonID[i] );
		if ( pclClient->pclCM->IsValidID( charID ) ) // �������ִٸ�
		{
			cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[charID];

			//�������� ����
			pclchar->pclCI->clBI.clGuildRank.SetEnemyGuild(m_siAwayGuildUnique);
			{
				cltGameMsgResponse_Guild_SetGuildStatus clinfo(&pclHomeGuild->clStatus,&pclchar->pclCI->clBI.clGuildRank,pclchar->GetCharUnique());
				cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_SETGUILDSTATUS, sizeof(clinfo), (BYTE*)&clinfo);
				pclchar->SendNeighbourMsg(&clMsg,true);
			}
			// ������� ���۵Ǿ��ٰ� Ŭ���̾�Ʈ���� �˷��ش�.
			{
				cltGameMsgResponse_GuildWar_Start clinfo( m_szHomeGuildName, m_szAwayGuildName, pclHomeGuild->clGPoint.siMarkIndex, pclAwayGuild->clGPoint.siMarkIndex );
				cltMsg clMsg(GAMEMSG_RESPONSE_GUILDWAR_START, sizeof(clinfo), (BYTE*)&clinfo);
				pclchar->SendNetMsg((sPacketHeader*)&clMsg);
			}
			if ( pclClient->IsCountrySwitch( Switch_NewGuildHuntMapWar ))
			{
				pclchar->ParametaBoxAction();
				// ������� ä���. 
				pclchar->pclCI->clIP.SetLife( pclchar->clPB.GetMaxLife() );
				// ������ ä���ش�
				pclchar->pclCI->clIP.SetMana( pclchar->clPB.GetMaxMana() );
			}
		}
		charID = pclClient->pclCM->GetIDFromPersonID( m_siAwayPersonID[i] );
		if ( pclClient->pclCM->IsValidID( charID ) ) // �������ִٸ�
		{
			cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[charID];

			//�������� ����
			pclchar->pclCI->clBI.clGuildRank.SetEnemyGuild(m_siHomeGuildUnique);
			{	
				cltGameMsgResponse_Guild_SetGuildStatus clinfo(&pclHomeGuild->clStatus,&pclchar->pclCI->clBI.clGuildRank,pclchar->GetCharUnique());
				cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_SETGUILDSTATUS, sizeof(clinfo), (BYTE*)&clinfo);
				pclchar->SendNeighbourMsg(&clMsg,true);
			}
			// ������� ���۵Ǿ��ٰ� Ŭ���̾�Ʈ���� �˷��ش�.
			{
				cltGameMsgResponse_GuildWar_Start clinfo( m_szHomeGuildName, m_szAwayGuildName, pclHomeGuild->clGPoint.siMarkIndex, pclAwayGuild->clGPoint.siMarkIndex );
				cltMsg clMsg(GAMEMSG_RESPONSE_GUILDWAR_START, sizeof(clinfo), (BYTE*)&clinfo);
				pclchar->SendNetMsg((sPacketHeader*)&clMsg);
			}
			if ( pclClient->IsCountrySwitch( Switch_NewGuildHuntMapWar ) )
			{
				pclchar->ParametaBoxAction();
				// ������� ä���. 
				pclchar->pclCI->clIP.SetLife( pclchar->clPB.GetMaxLife() );
				// ������ ä���ش�
				pclchar->pclCI->clIP.SetMana( pclchar->clPB.GetMaxMana() );
			}
		}
	}
}

cltGuildWarClient::cltGuildWarClient()
{
	Init();
}

void cltGuildWarClient::Init()
{
	m_bGuildWarSwitch = false;
	StringCchCopy( m_szHomeGuildName, MAX_GUILD_NAME, TEXT(""));
	StringCchCopy( m_szAwayGuildName, MAX_GUILD_NAME, TEXT(""));
	m_siHomeGuildPoint = 0;
	m_siAwayGuildPoint = 0;

	m_siHomeGuildMarkIndex = 0;
	m_siAwayGuildMarkIndex = 0;

	m_noticeClock = 0;
	m_bDrawFlag = false;
	m_endClock = 0;
}

void cltGuildWarClient::StartGuildWar( TCHAR* homename, TCHAR* awayname, SI16 homemark, SI16 awaymark )
{
	m_bGuildWarSwitch = true;
	StringCchCopy( m_szHomeGuildName, MAX_GUILD_NAME, homename );
	StringCchCopy( m_szAwayGuildName, MAX_GUILD_NAME, awayname );
	m_siHomeGuildPoint = 0;
	m_siAwayGuildPoint = 0;

	m_siHomeGuildMarkIndex = homemark;
	m_siAwayGuildMarkIndex = awaymark;

	m_bDrawFlag = GUILDWAR_NOTICE_START;
	m_noticeClock = pclClient->CurrentClock;
	m_endClock =  pclClient->CurrentClock + ( (GUILDWAR_TIME) * 1000 * 60 );
}
void cltGuildWarClient::EndGuildWar( SI32 recvGP )
{
	if ( recvGP > 0 ) 		m_bDrawFlag = GUILDWAR_NOTICE_WIN;
	else if ( recvGP < 0 )	m_bDrawFlag = GUILDWAR_NOTICE_LOSE;
	else m_bDrawFlag = GUILDWAR_NOTICE_DRAW;

	m_noticeClock = pclClient->CurrentClock; 

	m_bGuildWarSwitch = false;
	StringCchCopy( m_szHomeGuildName, MAX_GUILD_NAME, TEXT(""));
	StringCchCopy( m_szAwayGuildName, MAX_GUILD_NAME, TEXT(""));
	m_endClock = 0;
	//m_siHomeGuildPoint = 0; 
	//m_siAwayGuildPoint = 0;
}
void cltGuildWarClient::DrawStatus(LPDIRECTDRAWSURFACE7 lpsurface, SI32 rx, SI32 ry)
{
	SI32 yindent  = 0;

	if ( g_SoundOnOffDlg.m_bFullScreenMode )
	{
		yindent = 30 ;
	}

	cltClient* pclclient = (cltClient*)pclClient;


	if(m_bDrawFlag)
	{
		TSpr* pspr = pclClient->GetGlobalSpr(GIMG_GUILDWAR_NOTICE);
		if(pspr == NULL)return ;

		// ���� ����, ���� �˸� �޼��� ���
		SI32 xPos = (pclclient->siClientScreenXsize - pspr->GetXSize())/2 + rx - 10 ;
		SI32 yPos = ry+yindent + 90;

		if( GP.LockSurface(lpsurface)==TRUE )
		{
			GP.PutSpr(pspr, xPos, yPos, m_bDrawFlag - 1 );//�̹��� ���ҽ� �и� �۾� [2007.07.18 �ռ���]

			GP.UnlockSurface(lpsurface);
		}
	}

	if( TABS(pclClient->CurrentClock - m_noticeClock) > 10000)
	{
		m_bDrawFlag = 0;
	}

	// �ð� ���
	if( m_endClock )
	{
		clock_t overTime = ( m_endClock - ( pclClient->CurrentClock ) ) / 1000;

		overTime = max( 0, overTime );

		TSpr* pspr = pclClient->GetGlobalSpr(GIMG_WARKILLNUM);
		if(pspr == NULL)return ;

		// ���� ����, ���� �˸� �޼��� ���
		SI32 xPos = (pclclient->siClientScreenXsize - pspr->GetXSize())/2 + rx;
		SI32 yPos = ry+yindent + 50;

		if( GP.LockSurface(lpsurface)==TRUE )
		{
			if ( overTime / 100 > 0 )
			{
				GP.PutSpr(pspr, xPos, yPos, overTime/100 );
				GP.PutSpr(pspr, xPos + 17, yPos, overTime % 100 / 10 );
				GP.PutSpr(pspr, xPos + 34, yPos, overTime % 10 );
			}
			else if ( overTime / 10 > 0 )
			{
				GP.PutSpr(pspr, xPos + 8, yPos, overTime / 10 );
				GP.PutSpr(pspr, xPos + 25, yPos, overTime % 10 );
			}
			else
			{
				GP.PutSpr(pspr, xPos+17, yPos, overTime % 10 );
			}
			GP.UnlockSurface(lpsurface);
		}
	}

	if( m_bDrawFlag || m_bGuildWarSwitch )
	{
		// ī��Ʈ ���
		if ( GP.LockSurface(lpsurface)==TRUE )
		{
			TSpr* pspr =  pclClient->GetGlobalSpr(GIMG_GUILDWAR_COUNT);
			//TSpr* pmarkspr = pclClient->GetGlobalSpr( GIMG_VILLAGEMARK01 );


			if(pspr == NULL)
			{
				GP.UnlockSurface(lpsurface);
				return ;
			}

			SI32 homeX = (pclclient->siClientScreenXsize - pspr->GetXSize())/2 + rx - 190 ;
			SI32 awayX = (pclclient->siClientScreenXsize - pspr->GetXSize())/2 + rx + 170 ;

			SI32 homeY = ry+yindent + 100;
			SI32 awayY = homeY;

			SI32 markXpos = 0;
			// Ȩ��� ���
			if ( m_siHomeGuildPoint / 100 > 0 )
			{
				GP.PutSpr(pspr, homeX, homeY+30, m_siHomeGuildPoint/100 );
				GP.PutSpr(pspr, homeX + 30, homeY+30, m_siHomeGuildPoint % 100 / 10 );
				GP.PutSpr(pspr, homeX + 60, homeY+30, m_siHomeGuildPoint % 10 );
				markXpos = homeX + 30;
			}
			else if ( m_siHomeGuildPoint / 10 > 0 )
			{
				GP.PutSpr(pspr, homeX, homeY+30, m_siHomeGuildPoint / 10 );
				GP.PutSpr(pspr, homeX + 30, homeY+30, m_siHomeGuildPoint % 10 );
				markXpos = homeX + 15;
			}
			else
			{
				GP.PutSpr(pspr, homeX, homeY+30, m_siHomeGuildPoint % 10 );
				markXpos = homeX;
			}

			if ( m_siHomeGuildMarkIndex > 0 )
			{
				SI32 guildicon = -1;
				TSpr* pmarkspr = NULL;		

				pclclient->m_pMarkManager->GetMarkSprAndFontIndex(m_siHomeGuildMarkIndex , &pmarkspr , &guildicon );
				if( pmarkspr != NULL && guildicon >= 0 )
				{
					GP.PutSpr(pmarkspr, markXpos, homeY, guildicon );
				}
				
			}

			// ������� ���
			if ( m_siAwayGuildPoint / 100 > 0 )
			{
				GP.PutSpr(pspr, awayX, awayY+30, m_siAwayGuildPoint/100 );
				GP.PutSpr(pspr, awayX + 30, awayY+30, m_siAwayGuildPoint % 100 / 10 );
				GP.PutSpr(pspr, awayX + 60, awayY+30, m_siAwayGuildPoint % 10 );
				markXpos = awayX + 30;
			}
			else if ( m_siAwayGuildPoint / 10 > 0 )
			{
				GP.PutSpr(pspr, awayX + 30, awayY+30, m_siAwayGuildPoint / 10 );
				GP.PutSpr(pspr, awayX + 60, awayY+30, m_siAwayGuildPoint % 10 );
				markXpos = awayX + 45;
			}
			else
			{
				GP.PutSpr(pspr, awayX + 60, awayY+30, m_siAwayGuildPoint % 10 );
				markXpos = awayX + 60;
			}

			if ( m_siAwayGuildMarkIndex > 0 )
			{
				SI32 guildicon = -1;
				TSpr* pmarkspr = NULL;		

				pclclient->m_pMarkManager->GetMarkSprAndFontIndex(m_siAwayGuildMarkIndex , &pmarkspr , &guildicon );
				if( pmarkspr != NULL && guildicon >= 0 )
				{
					GP.PutSpr(pmarkspr, markXpos, homeY, guildicon );
				}
			}

			GP.UnlockSurface(lpsurface);

		}
	}
}