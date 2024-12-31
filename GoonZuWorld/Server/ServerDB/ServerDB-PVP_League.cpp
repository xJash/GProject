//---------------------------------
// 2003/8/6 ���°�
//---------------------------------
// APEX- 
#include "../../Apex/ApexGoonZu.h"
// -APEX

#include "../../Common/CommonHeader.h"
#include "../../Server/Server.h"

#include "../../../NLib/NUtil.h"
#include "../../../NLib/NTCHARString.h"

#include "../Common/Map/Map.h"
#include "../Common/Father/Father.h"
#include "../Common/VoteMgr/VoteMgr.h"
#include "../Common/Skill/Skill-Manager.h"
#include "Char/CharManager/CharManager.h"
#include "../Common/Order/Order.h"
#include "../common/GameEvent/GameEvent.h"
#include "../common/Item/ItemCommon/cltSetItem.h"

#include "../CommonLogic/Feast/Feast.h"

#include "Guild/Guild.h"

#include "MsgRval-Define.h"
#include "MsgType-Person.h"
#include "MsgType-System.h"
#include "MsgType-Horse.h"
#include "Msg/MsgType-Vote.h"
#include "Msg/MsgType-Friend.h"
#include "Msg/MsgType-Summon.h"
#include "Msg/MsgType-Village.h"
#include "Msg/MsgType-ItemMall.h"
#include "Msg/MsgType-npc.h"
#include "MsgType-Structure.h"
#include "Msg/MsgType-Web.h"
#include "Msg/MsgType-NamingQuest.h"

#include "MsgType-Item.h"
#include "MsgType-Guild.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-System.h"

//-----------------------------------------
// Server
//-----------------------------------------
#include "../Server/Statistics/Statistics.h"
#include "../Server/Minister/Minister-yezo.h"
#include "../Server/Minister/MinisterMgr.h"

#include "../../DBManager/GameDBManager_World/DBMsg-Person.h"
#include "../../DBManager/GameDBManager_World/DBMsg-Stock.h"
#include "../../DBManager/GameDBManager_World/DBMsg-Summon.h"
#include "../../DBManager/GameDBManager_World/DBMsg-Cityhall.h"
#include "../../DBManager/GameDBManager_World/DBMsg-item.h"
#include "../../DBManager/GameDBManager_World/DBMsg-PostOffice.h"
#include "../../DBManager/GameDBManager_World/DBMsg-Agriculture.h"
#include "../../DBManager/GameDBManager_World/DBMsg-Friend.h"

#include "../Notice/Notice.h"
#include "HashTable/HashTable_StringInt.h"
#include "HashTable/HashTable_IntInt.h"

#include "../../Server/AuthServer/AuthMsg.h"

#include "NDate.h"

#include "../../../NLib/NUtil.h"
#include "../../Lib/MD5/md5.h"

#include "../../CommonLogic/Msg/MsgType-HappyBeanQuest.h"

#include "../../common/VoteMgr/VoteBaseInfo.h"

#include "../../DBManager/GameDBManager_World/DBMsg-PVP_League.h"
//PVP-League ����
void cltServer::DoMsg_DBMSG_RESPONSE_PVP_LEAGUE_BATTLE_END( sPacketHeader* pPacket)
{
	sDBResponse_PVP_League_Battle_End * pclMsg = (sDBResponse_PVP_League_Battle_End*)pPacket;
	if ( NULL == pclMsg )
	{
		return;
	}

	if ( NULL == pclPVP_LeagueMgr )
	{
		return;
	}

	SI32 siMyPersonID			= pclMsg->siMyPersonID;
	SI32 siEnemyPersonID		= pclMsg->siEnemyPersonID;

	SI32 siMyCharID				= pclCM->GetIDFromPersonID(siMyPersonID) ;
	SI32 siEnemyCharID			= pclCM->GetIDFromPersonID(siEnemyPersonID) ;

	cltCharServer *pclMyChar	= pclCM->GetCharServer( siMyCharID );
	cltCharServer *pclEnemyChar	= pclCM->GetCharServer( siEnemyCharID );

	if ( pclMyChar != NULL )// �ɸ��Ͱ� ������ ������ ���� ���� �ʴ´�.
	{
		// ������ ���� ���� �ð��� ���� .
		pclMyChar->SetPVP_LeagueEndBAttleTime(pclMsg->stLAstPVPTime)	;
	}

	if ( pclEnemyChar != NULL )// �ɸ��Ͱ� ������ ������ ���� ���� �ʴ´�.
	{
		// ������ ���� ���� �ð��� ���� .
		pclEnemyChar->SetPVP_LeagueEndBAttleTime(pclMsg->stLAstPVPTime)	;
	}

	// �̰�����.
	if ( pclMsg->siWinOrLose == PVPLEAGUE_RESULT_WIN )  
	{
		pclPVP_LeagueMgr->Send_PVP_Battle_Result( siMyPersonID , siEnemyPersonID , PVPLEAGUE_RESULT_WIN )	;
	}
	// ������ 
	if ( pclMsg->siWinOrLose == PVPLEAGUE_RESULT_LOSE ) 
	{
		pclPVP_LeagueMgr->Send_PVP_Battle_Result(   siEnemyPersonID  , siMyPersonID, PVPLEAGUE_RESULT_LOSE )	;
	}
	// �������.
	if ( pclMsg->siWinOrLose == PVPLEAGUE_RESULT_DRAW) 
	{
		pclPVP_LeagueMgr->Send_PVP_Battle_Result( siMyPersonID , siEnemyPersonID , PVPLEAGUE_RESULT_DRAW )	;
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_PVP_LEAGUE_INFOGET(sPacketHeader* pPacket)
{
	sDBResponse_PVP_League_InfoGet* pclMsg = (sDBResponse_PVP_League_InfoGet*)pPacket;
	if ( NULL == pclMsg )
	{
		return;
	}

	SI32 siCharID = pclCM->GetIDFromPersonID( pclMsg->m_siPersonID );
	if ( false == pclCM->IsValidID(siCharID) )
	{
		return;
	}
	
	cltCharServer* pclchar = pclCM->GetCharServer( siCharID );
	if ( NULL == pclchar )
	{
		return;
	}

	// �������� ����
	if ( pclchar->pclPVP_LeagueInfo )
	{
		pclchar->pclPVP_LeagueInfo->Init();// �ʱ�ȭ �ѹ� �ϰ� ���Ѵ�.
		pclchar->pclPVP_LeagueInfo->Set( &pclMsg->m_clPVP_LeaugeInfo );
	}
	//--------------
	SYSTEMTIME stLAsttime = pclchar->pclPVP_LeagueInfo->stLastPVPTime;
	NDate Lastdate	;
	NDate nowdate	;
	Lastdate.SetDate(stLAsttime.wYear, stLAsttime.wMonth, stLAsttime.wDay )	;
	nowdate.SetDate( sTime.wYear, sTime.wMonth,sTime.wDay);

	if( Lastdate.GetDateVary() > 0 &&	nowdate.GetDateVary() - Lastdate.GetDateVary() >= 3  )
	{
		SI32 siBeforGrade = pclchar->pclPVP_LeagueInfo->m_siGrade	;// ���� ���.
		if ( PVP_LEAGUE_GRADE_9 < siBeforGrade ) // ���ϵ���� ���� �ƹ��͵� ���Ѵ�.
		{
			SI32 ChangeGrade = siBeforGrade -	MAX_PVP_LEAGUE_GRADE_UP_DOWN_POINT	;
			pclchar->SetPVP_LeagueEndBAttleTime(sTime )	;

			sDBRequest_PVP_League_Battle_ChangeGrade clMsg(  pclchar->pclCI->GetPersonID() ,  ChangeGrade , sTime);
			pclGameDBProcess->SendMsg( DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);
		}
	}
	//=================================
	// Ŭ���̾�Ʈ ����
	cltGameMsgResponse_PVP_League_InfoGet clPVPLeagueInfoGet( &pclMsg->m_clPVP_LeaugeInfo );
	cltMsg clMsg( GAMEMSG_RESPONSE_PVP_LEAGUE_INFOGET, sizeof(clPVPLeagueInfoGet), (BYTE*)&clPVPLeagueInfoGet );
	pclchar->SendNetMsg( (sPacketHeader*)&clMsg );
		
}	

void cltServer::DoMsg_DBMSG_RESPONSE_PVP_LEAGUE_UI_INFOGET(sPacketHeader* pPacket)
{
	sDBResponse_PVP_League_UI_InfoGet* pclMsg = (sDBResponse_PVP_League_UI_InfoGet*)pPacket;
	if ( NULL == pclMsg )
	{
		return;
	}

	SI32 siCharID = pclMsg->m_siCharID;
	if ( false == pclCM->IsValidID(siCharID) )
	{
		return;
	}

	cltCharServer* pclchar = pclCM->GetCharServer( siCharID );
	if ( NULL == pclchar )
	{
		return;
	}

	// ���� �� ������ ���ٸ� PersonID�� 0 �� ������ �ȴ� �̶����� �ٸ� ������ ���� Top10�� ������ �ִ�
	// ������ PersonID�� 0�̻��̸� �ش� CharID�� ���� ������� �˻��Ѵ�(�� ������ ���� �ٸ�������� ����� �� �����Ƿ�)
	if ( (pclMsg->m_siPersonID) && (pclCM->GetIDFromPersonID(pclMsg->m_siPersonID) != siCharID) )
	{
		return;
	}

	cltGameMsgResponse_PVP_League_UI_InfoGet clPVPLeagueUIInfoGet( 
		pclMsg->m_siWin, 
		pclMsg->m_siLose, 
		pclMsg->m_siDraw,
		pclMsg->m_siGroupNum,
		pclMsg->m_clLatest,
		pclMsg->m_clTop
		);
	cltMsg clMsg( GAMEMSG_RESPONSE_PVP_LEAGUE_UI_INFOGET, sizeof(clPVPLeagueUIInfoGet), (BYTE*)&clPVPLeagueUIInfoGet );
	pclchar->SendNetMsg( (sPacketHeader*)&clMsg );
}
void cltServer::DoMsg_DBMSG_RESPONSE_PVP_LEAGUE_BATTLE_CHANGEGRADE(sPacketHeader* pPacket)
{
	sDBResponse_PVP_League_Battle_ChangeGrade* pclMsg = (sDBResponse_PVP_League_Battle_ChangeGrade*)pPacket;
	if ( NULL == pclMsg )
	{
		return;
	}

	SI32			siMyPersonID	= pclMsg->siMyPersonID;
	SI32			siMyCharID		= pclCM->GetIDFromPersonID( siMyPersonID );
	cltCharServer*	pclchar			= pclCM->GetCharServer( siMyCharID );
	if ( NULL == pclchar )
	{
		return;
	}

	// ���� ĳ���� ��� ����
	SI16 siGrade = pclMsg->siGrade;
	pclchar->SetPVP_LeagueGrade( siGrade );
	pclchar->SetPVP_LeagueEndBAttleTime( pclMsg->stLAstPVPTime)	;

	// Ŭ���̾�Ʈ ���� ����
	cltGameMsgResponse_PVP_League_Battle_ChangeGrade cltChangeGrade( siGrade );
	cltMsg clMsg( GAMEMSG_RESPONSE_PVP_LEAGUE_BATTLE_CHANGEGRADE, sizeof(cltChangeGrade), (BYTE*)&cltChangeGrade );
	pclchar->SendNetMsg( (sPacketHeader*)&clMsg );

}