#include "Guild-Dungeon.h"
#include "../../Server/Server.h"
#include "../../CommonLogic/CommonLogic.h"
#include "../../DBManager/GameDBManager_World/DBMsg-Guild.h"
#include "DevTool/DevServerInfo/DevServerInfo.h"

extern cltCommonLogic* pclClient;

cltGuildDungeonMgr::cltGuildDungeonMgr()
{
	m_UpdateDBClock = 0;
	m_SendDBDay = 0;
	SetDungeon();
}

cltGuildDungeonMgr::~cltGuildDungeonMgr()
{

}

void cltGuildDungeonMgr::SetDungeon()
{
	SI32 i = 0;
	for ( SI32 mapindex = 0; mapindex < MAX_MAP_NUMBER ; mapindex++ )
	{
		if ( pclClient->pclMapManager->IsGuildMap(mapindex) )
		{
			m_clUnit[i++].SetMapIndex( mapindex );

			if ( i >= MAX_GUILDDUNGEON ) return;
		}
	}
}

void cltGuildDungeonMgr::SetStatus(SI32 mapindex, SI32 guildunque, SI32 exp, GMONEY money )
{
	for ( SI32 i=0; i< MAX_GUILDDUNGEON; i++ )
	{
		if ( m_clUnit[i].GetMapIndex() == mapindex )
		{
			m_clUnit[i].SetGuildUnique( guildunque );
			m_clUnit[i].SetExp( exp );
			m_clUnit[i].SetMoney( money );

			break;
		}
	}
}

bool cltGuildDungeonMgr::CanApplyGuildDungeon( SI32 mapindex )
{
	cltServer* pclserver= (cltServer*)pclClient;

	SI32 count = 0;
	for( SI32 i=0 ; i <MAX_GUILD_NUM; i++)
	{
		if ( pclClient->pclGuildManager->clUnit[i].clGPoint.siApplyMapIndex == mapindex )
			count++;

		if ( count == MAX_GUILDDUNGEONAPPLY )
			break;
	}

	if ( count <  MAX_GUILDDUNGEONAPPLY )
	{
		return true;
	}

	return false;
}

void cltGuildDungeonMgr::AddExp(SI32 mapindex, SI32 exp )
{
	for ( SI16 i=0; i<MAX_GUILDDUNGEON; i++)
	{
		if ( m_clUnit[i].GetMapIndex() ==  mapindex)
		{
			SI32 GuildUnique = m_clUnit[i].GetGuildUnique() ; // ���ε����� ��� ����� �̰� , ���� �� �ʿ� ��� ����ũ�� ������쿡�� exp�� ���Ѵ�
			if ( GuildUnique > 0 ) {
				m_clUnit[i].AddExp( exp );
				break;
			}

		}
	}
}

void cltGuildDungeonMgr::AddMoney(SI32 mapindex, GMONEY money )
{
	for ( SI16 i=0; i<MAX_GUILDDUNGEON; i++)
	{
		if ( m_clUnit[i].GetMapIndex() ==  mapindex)
		{
			SI32 GuildUnique = m_clUnit[i].GetGuildUnique() ; // ���ε����� ��� ����� �̰� , ���� �� �ʿ� ��� ����ũ�� ������쿡�� exp�� ���Ѵ�
			if ( GuildUnique > 0 ) {
				m_clUnit[i].AddMoney( money );
				break;
			}

		}
	}
}
SI32 cltGuildDungeonMgr::GetExp(SI32 mapindex )
{
	for ( SI16 i=0; i<MAX_GUILDDUNGEON; i++)
	{
		if ( m_clUnit[i].GetMapIndex() == mapindex )
		{
			return m_clUnit[i].GetExp();
		}
	}

	return 0;
}

GMONEY cltGuildDungeonMgr::GetMoney(SI32 mapindex )
{
	for ( SI16 i=0; i<MAX_GUILDDUNGEON; i++)
	{
		if ( m_clUnit[i].GetMapIndex() == mapindex )
		{
			return m_clUnit[i].GetMoney();
		}
	}
	return 0;
}

void cltGuildDungeonMgr::Action()
{
	// 1�п� �ѹ��� DB�� ����.

	cltServer* pclserver = (cltServer*)pclClient;

	if ( (TRUE == pclserver->bCompleteDBInitAll) && (TABS(pclClient->CurrentClock - m_UpdateDBClock) > 1000 * 60) )
	{
		// DB�� ������.

		m_UpdateDBClock = pclClient->CurrentClock;

		UpdateDB();
	}

	if (pclserver->IsCountrySwitch(Switch_NewGuildHuntMapWar) ) 
	{
		WORD currentDay = 0;
		currentDay = pclserver->sTime.wDay;
		if(1 == pclserver->pclTime->clDate.uiMonth	&&  1 == pclserver->pclTime->clDate.uiDay)
		{
			// ȹ���� GP�� ���� �������� �����ϰ� ( DB ���� )
			// �ʱ�ȭ ��Ų��
			if ( m_SendDBDay != currentDay )
			{
				MoveProcess();
				m_SendDBDay = currentDay;
			}
		}
	}
	else
	{
		WORD currentDay = 0;
		currentDay = pclserver->sTime.wDay;
		if ( currentDay == 1 || currentDay == 7 || currentDay == 13 
			|| currentDay == 19 || currentDay == 25 )
		{
			if ( pclserver->sTime.wHour == 0 && pclserver->sTime.wMinute == 0 )
			{
				if ( m_SendDBDay != currentDay )
				{	
					// ȹ���� GP�� ���� �������� �����ϰ� ( DB ���� )
					// �ʱ�ȭ ��Ų��

					MoveProcess();

					m_SendDBDay = currentDay;	
				}
			}
		}		
	}
}

void cltGuildDungeonMgr::UpdateDB()
{
	for ( SI16 i = 0; i < MAX_GUILDDUNGEON ; i++ )
	{
		if ( m_clUnit[i].GetMapIndex() == 0 )
			continue;

		//[����] ��� ����ũ�� ������ db�� ����� ���� �ʴ´�. => 2008-10-10
		/*if ( m_clUnit[i].GetGuildUnique() <= 0 ) 
			continue;*/
		
		if( m_clUnit[i].GetMapIndex() )
		{
			sDBRequest_GuildDungeon_SaveStatus clMsg(	m_clUnit[i].GetMapIndex(), 
														m_clUnit[i].GetExp(), 
														m_clUnit[i].GetMoney() );
			pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader*)&clMsg );
		}
	}
}

void cltGuildDungeonMgr::LoadFromDB()
{
	for ( SI16 i = 0; i < MAX_GUILDDUNGEON ; i++ )
	{
		if ( m_clUnit[i].GetMapIndex() == 0 )
			continue;

		sDBRequest_GuildDungeon_LoadStatus clMsg( m_clUnit[i].GetMapIndex() );
		pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader*)&clMsg );
	}
	pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("sDBRequest_GuildDungeon_LoadStatus"));
}

void cltGuildDungeonMgr::MoveProcess()
{
	// ������ ���� �۾� �ϱ����� ��������� ���¸� DB�� ����
	UpdateDB();

	// ������ �����Ѵ�.
	// DB���� �ϴ��۾� 
	// 1. �� map���� ���� ���� GP�� ȹ���� ��� ����
	// 2. ��� ����� ��û mapindex�� battleGP �ʱ�ȭ ��Ŵ
	// 3. map���� ������ ����� �������� �ѱ�

	// PCK : �߱�, ������ �ں���, GP ���� �ۼ�Ʈ�� 0.03%�� �ǵ��� �Ѵ�. (09.04.14)
	if(pclClient->IsWhereServiceArea(ConstServiceArea_NHNChina) || pclClient->IsWhereServiceArea(ConstServiceArea_EUROPE))
	{
		sDBRequest_GuildDungeon_TransferOwnership clMsg(GUILDDUNGEON_GIVEGPRATIO_EXCEPTION, GUILDDUNGEON_GIVEMONEYRATIO_EXCEPTION);
		pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader*)&clMsg );
	}
	else
	{
		if ( pclClient->IsCountrySwitch(Switch_NewGuildHuntMapWar) )
		{
			sDBRequest_GuildDungeon_TransferOwnership clMsg(GUILDDUNGEON_GIVEGPRATIO_EXCEPTION, GUILDDUNGEON_GIVEMONEYRATIO_EXCEPTION);
			pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader*)&clMsg );
		}
		else
		{
			sDBRequest_GuildDungeon_TransferOwnership clMsg(GUILDDUNGEON_GIVEGPRATIO, GUILDDUNGEON_GIVEMONEYRATIO);
			pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader*)&clMsg );
		}
	}
}

SI32 cltGuildDungeonMgr::GetMapIndex(SI32 guildunique )
{
	for ( SI16 i = 0; i < MAX_GUILDDUNGEON ; i++ )
	{
		if ( m_clUnit[i].GetMapIndex() == 0 )
			continue;

		if ( m_clUnit[i].GetGuildUnique() == guildunique )
			return m_clUnit[i].GetMapIndex();
	}

	return 0;
}