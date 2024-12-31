#include "BokBulBokEvent.h"
#include "../Common/CommonHeader.h"
#include "../CommonLogic/CommonLogic.h"
#include "../Server/Server.h"
#include "../../NLib/NUtil.h"

#include "../CommonLogic/MsgType.h"

#include "../Char/CharServer/Char-Server.h"
#include "../Char/CharManager/CharManager.h"
#include "../Char/CharCommon/Char-Common.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-Person.h"

#include "../common/Event/event.h"

//extern cltCommonLogic* pclClient;

CServer_BBBMgr::CServer_BBBMgr()
{
	m_siBokBulBok_NPC_ID = 0;
	_siAvailableMapNumber = -1;

	m_siTotalMoney = 0;
	m_siTotalRewardPrice = 0;

	dwNotice_Msg = 60 * 60 * 1000;     //  60�и��� ���� (wantMinutes * 60 * 1000)  //dwNotice_20Minute ���� ����.
}

CServer_BBBMgr::~CServer_BBBMgr()
{
	m_siBokBulBok_NPC_ID = 0;
}

//////////////////////////////////////////////////////////////////////////
void CServer_BBBMgr::AddBBBList(SI32 siPersonID)
{
	// 1. ���� ���� �����ϸ� ���ӿ� ���� �϶�� Ŭ�� ��Ŷ ����
	// 2. �� ���� ������ ��� ����Ʈ�� �߰� �����ϴٰ� Ŭ�� ��Ŷ ����
	// 3. 1, 2�� �ƴϸ� ���� ���� ���� �ߴٰ� Ŭ�� ��Ŷ ����.

	if ( true == _Check_Avail_Map() )				// ����� �־ �÷��̰� �����ϴ�.
	{
		_Check_StartBBB( siPersonID );				// ���Һ� ���� ����
	}
	else if ( true == _Check_Avail_List() )			// ��⸮��Ʈ�� Ǯ�� �ƴ϶� ��� ����Ʈ�� ����� �����ϴ�
	{
		_SendMsg_WaitList( siPersonID );			// ��� ����Ʈ�� ���
	}
	else											// �̵� ���� �ƴ϶� ������ ���� �Ҽ��� ����.
	{
		_SendMsg_EnterFail( siPersonID );
	}
}

bool CServer_BBBMgr::_Check_Avail_Map()
{
	if ( false == m_BBBEventMapMgr.IsFull() )
	{
		return true;
		//return false;	// ����Ʈ �׽�Ʈ
	}

	return false;
}

bool CServer_BBBMgr::_Check_Avail_List()
{
	if ( false == m_BBBWaitListMgr.IsFull() )
	{
		return true;
	}

	return false;
}

void CServer_BBBMgr::_Check_StartBBB( SI32 siPersonID )
{
	cltServer* pclServer = (cltServer*)pclClient;

	cltCharServer* pclChar = pclServer->pclCM->GetCharServer( siPersonID );
	if ( NULL == pclChar )
		return;

	TCHAR* pszCharName = (TCHAR*)pclChar->pclCI->clBI.GetName();

	SI16 siMapNumber = m_BBBEventMapMgr.AddUser( siPersonID, pszCharName );
}

void CServer_BBBMgr::_SendMsg_WaitList( SI32 siPersonID )
{
	cltServer* pclServer = (cltServer*)pclClient;

	cltCharServer* pclChar = pclServer->pclCM->GetCharServer( siPersonID );
	if ( NULL == pclChar )
		return;

	TCHAR* pszCharName = (TCHAR*)pclChar->pclCI->clBI.GetName();

	// ���� ���� ���� ������ ��� ����Ʈ�� ��� �����ϴٴ� ��Ŷ�� Ŭ��� ����
	cltGameResponse_BBBCheckCondition clinfo( siPersonID );
	cltMsg clMsg( GAMEMSG_RESPONSE_BOKBULBOK_CHECK_WAITLIST_ENABLE, sizeof(clinfo), (BYTE*)&clinfo);
	pclChar->SendNetMsg((sPacketHeader*)&clMsg);
}

void CServer_BBBMgr::_SendMsg_EnterFail( SI32 siPersonID )
{
	// Ŭ�� ���� �޼��� ���� ����.
	cltServer* pclServer = (cltServer*)pclClient;

	cltCharServer* pclChar = pclServer->pclCM->GetCharServer( siPersonID );
	if ( NULL == pclChar )
		return;

	cltGameResponse_BBBCheckCondition clinfo( siPersonID );
	cltMsg clMsg( GAMEMSG_RESPONSE_BOKBULBOK_CHECK_ENTRYREQUEST_FAIL, sizeof(clinfo), (BYTE*)&clinfo);
	pclChar->SendNetMsg((sPacketHeader*)&clMsg);
}



//////////////////////////////////////////////////////////////////////////
void CServer_BBBMgr::SendWaitListToClient(SI32 siPersonID, bool bResult)
{
	cltServer* pclServer = (cltServer*)pclClient;

	cltCharServer* pclChar = pclServer->pclCM->GetCharServer( siPersonID );
	if ( NULL == pclChar )
		return;

	// ��⸮��Ʈ ���������� ����� ����Ʈ ������
	_BBBWaitUserData aWaitList[MAX_RESERVATION_NUM];
	ZeroMemory( aWaitList, (sizeof(_BBBWaitUserData) * MAX_RESERVATION_NUM) );

	m_BBBWaitListMgr.GetWaitList( aWaitList );

	// �޼����� ����� ����Ʈ �־� Ŭ��� ����
	cltGameResponse_BBB_WaitList_Answer clinfo( aWaitList, bResult, m_siTotalRewardPrice );
	cltMsg clMsg( GAMEMSG_RESPONSE_BBB_WAITLIST_ANSWER, sizeof(clinfo), (BYTE*)&clinfo);
	pclChar->SendNetMsg((sPacketHeader*)&clMsg);
}

//////////////////////////////////////////////////////////////////////////


//bool CServer_BBBMgr::CreateBokBulBokNPC()
//{
//	cltServer* pclServer = (cltServer*)pclClient;
//
//	if (pclServer == NULL)
//		return false;
//  
//	SI32 siKindOfNPC = pclClient->GetUniqueFromHash("KIND_BOKBULBOKNPC");
//	if(0 >= siKindOfNPC)
//		return false;
//
//	m_siBokBulBok_NPC_ID = pclServer->SetNPCChar(	
//		siKindOfNPC,
//		VILLAGE_NONE,
//		NULL,
//		1,
//		1,
//		BOKBULBOK_X,
//		BOKBULBOK_Y,
//		MAPINDEX_BOKBULBOK_NPC, 
//		NPCITEMMODE_NONE,
//		NULL );
//
//	if(m_siBokBulBok_NPC_ID != 0 )
//		return true;
//	else 
//		return false;
//}

void CServer_BBBMgr::Action()
{
	cltServer* pclServer = (cltServer*)pclClient;

	m_BBBWaitListMgr.SubAction();
	m_BBBEventMapMgr.SubAction();

	if ( true == m_BBBWaitListMgr.WaitUserExist() )
	{
		if ( false == m_BBBEventMapMgr.IsFull() )
		{
			// ����ڰ� �ְ�, ����� ������ ����� �ϴ� ���� �ص�ä�� 1���� ����ڿ��� ���� �Ұųİ� �޼��� ����.
			SI32 siID = m_BBBWaitListMgr.Get1stUserID();
			m_BBBEventMapMgr.SetTemporaryReserve( siID );
			m_BBBWaitListMgr.Send_EnterMapQuestion();
		}
	}

	if ( dwNextmNoticetime < pclServer->CurrentClock )
	{
		dwNextmNoticetime = pclServer->CurrentClock + dwNotice_Msg;
		_Notice_20_Minute_TotalRewardMoney();
	}

	/*if(m_siBokBulBok_NPC_ID == 0)
	{
		bool bResult = CreateBokBulBokNPC();

		if(bResult == false)
			return;
	}*/
}

bool CServer_BBBMgr::Insert_List(SI32 siPersonID)
{
	cltServer* pclServer = (cltServer*)pclClient;

	cltCharServer* pclChar = pclServer->pclCM->GetCharServer( siPersonID );
	if ( NULL == pclChar )
		return false;

	TCHAR* pszCharName = (TCHAR*)pclChar->pclCI->clBI.GetName();

	return m_BBBWaitListMgr.AddUser( siPersonID, pszCharName );
}

void CServer_BBBMgr::Remove_List(SI32 siPersonID)
{
	cltServer* pclServer = (cltServer*)pclClient;

	cltCharServer* pclChar = pclServer->pclCM->GetCharServer( siPersonID );
	if ( NULL == pclChar )
		return;

	m_BBBWaitListMgr.RemoveUser( siPersonID );

	_BBBWaitUserData aWaitList[MAX_RESERVATION_NUM];
	ZeroMemory( aWaitList, (sizeof(_BBBWaitUserData) * MAX_RESERVATION_NUM) );

	m_BBBWaitListMgr.GetWaitList( aWaitList );

	// �޼����� ����� ����Ʈ �־� Ŭ��� ����
	cltGameMsgResponse_BBB_WaitList_Cancel clinfo( aWaitList, true );
	cltMsg clMsg( GAMEMSG_RESPONSE_BBB_WAITLIST_CANCEL, sizeof(clinfo), (BYTE*)&clinfo);
	pclChar->SendNetMsg((sPacketHeader*)&clMsg);
}

//void CServer_BBBMgr::Warp_GameStart(SI32 siPersonID)
//{	
//	// ������ ����
//	//cltWarpInfo clWarpInfo(1, 0, false, false, 63, 14, -1, -1);
//	//clWarpInfo.uiMapIndex = PLAY_MAP_INDEX;
//
//	//SI32 siCharId = pclClient->pclCM->GetIDFromPersonID( siPersonID ) ;
//
//	//cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->GetCharServer(siCharId);
//	//if (pclchar == NULL )	return	;
//	//pclchar->SetWarpInfo(&clWarpInfo, 2200);	// �ش� ��ġ�� ���� �Ѵ� .
//	//pclchar->Warp()	;
//}

void CServer_BBBMgr::LeaveMap(SI32 siPersonID)
{
	m_BBBEventMapMgr.RemoveUser( siPersonID );
}

void CServer_BBBMgr::StageFail(SI32 siPersonID)
{
	m_BBBEventMapMgr.StageFail( siPersonID );
}

void CServer_BBBMgr::StageClear(SI32 siPersonID)
{
	m_BBBEventMapMgr.StageClear( siPersonID );
}

void CServer_BBBMgr::ActiveTemporaryReserve(SI32 siPersonID)
{
	m_BBBEventMapMgr.ActiveTemporaryReserve( siPersonID );
}

void CServer_BBBMgr::CancelTemporaryReserve(SI32 siPersonID)
{
	m_BBBEventMapMgr.CancelTemporaryReserve( siPersonID );
}

GMONEY CServer_BBBMgr::GetRewardMoney()
{
	GMONEY siRewardPrice = m_siTotalRewardPrice;
	m_siTotalRewardPrice = 0;			// �������� Ŭ����� ������ ��� �Ҷ��� �� �Լ� ȣ��ǹǷ�.. 
	m_siTotalMoney = 0;
	// �Լ� ȣ��ɶ� ���� ������� 0���� �ʱ�ȭ �ϰ� �������ִ� 
	// �ݾ��� ��������� �Ѱ��ش�.

	return siRewardPrice;
}

void CServer_BBBMgr::SetEntranceFee(GMONEY siEntranceFee)
{
	m_siTotalMoney = m_siTotalMoney + siEntranceFee;	// �� ���� �ݾ�
	m_siTotalRewardPrice = m_siTotalMoney * 0.7;		// �� ������� 70%

	sDBRequest_BBB_Set_RewardMoney clMsg( m_siTotalMoney );
	pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
}

void CServer_BBBMgr::SetPlayTime(SI32 siPlayTime)
{
	m_BBBEventMapMgr.SetPlayTime( siPlayTime );
}

void CServer_BBBMgr::ShowMonsterType(SI32 siID, SI32 siShowMonsterType)
{
	cltServer* pServer = (cltServer*)pclClient;

	cltCharServer* pclChar = (cltCharServer*)pServer->pclCM->CR[siID];
	if ( NULL == pclChar )
		return;

	// �޼����� ����� ����Ʈ �־� Ŭ��� ����
	cltGameMsgResponse_BBB_GM_ShowMonstertype clinfo( siID, true );
	cltMsg clMsg( GAMEMSG_RESPONSE_BBB_GM_SHOWMONSTERTYPE, sizeof(clinfo), (BYTE*)&clinfo);
	pclChar->SendNetMsg((sPacketHeader*)&clMsg);
}

void CServer_BBBMgr::_Notice_20_Minute_TotalRewardMoney()
{
	cltServer* pServer = (cltServer*)pclClient;

	TCHAR* pHeadTag = GetTxtFromMgr(5482); 

	NTCHARString256 strRewardMoney;
	NTCHARString256 pContents( GetTxtFromMgr(40069) );

	g_JYLibFunction.SetNumUnit( m_siTotalRewardPrice, strRewardMoney, 256 );

	pContents.Replace( "#money#", strRewardMoney );

	// ������ �ƴҶ��� ��ü ���� �ѷ���
	if( true != pclClient->IsWhereServiceArea( ConstServiceArea_Korea ) )
	{
		pServer->PushSpecialNews( (TCHAR*)pContents, pHeadTag, NULL, CAPTIONKIND_NEWS, CAPTIONKIND_NEWSCHAT );
	}

	//cltGameMsgResponse_Notice clNotice( pHeadTag, pContents, true);
	//cltMsg clMsg( GAMEMSG_RESPONSE_NOTICE, clNotice.siDataSize, (BYTE*)&clNotice );
	//pServer->pclCM->SendAllPersonMsg((sPacketHeader*)&clMsg);
}

void CServer_BBBMgr::Set20mNoticeTime(SI32 siNoticeTime)
{
	cltServer* pServer = (cltServer*)pclClient;

	if ( siNoticeTime > 0 )
	{
		dwNotice_Msg = siNoticeTime * 60 * 1000;

		dwNextmNoticetime = pServer->CurrentClock + dwNotice_Msg;	   //(2)

		_Notice_20_Minute_TotalRewardMoney();
	}
}

void CServer_BBBMgr::Check_AlreadyReserved(SI32 siID)
{
	cltServer* pclServer = (cltServer*)pclClient;

	cltCharServer* pclChar = pclServer->pclCM->GetCharServer( siID );
	if ( NULL == pclChar )
		return;

	if ( true == m_BBBWaitListMgr._AlreadyExist( (TCHAR*)pclChar->GetName() ) )
	{
		// ��⸮��Ʈ ���������� ����� ����Ʈ ������
		_BBBWaitUserData aWaitList[MAX_RESERVATION_NUM];
		ZeroMemory( aWaitList, (sizeof(_BBBWaitUserData) * MAX_RESERVATION_NUM) );

		m_BBBWaitListMgr.GetWaitList( aWaitList );

		// �޼����� ����� ����Ʈ �־� Ŭ��� ����
		cltGameResponse_BBB_WaitList_Answer clinfo( aWaitList, true, m_siTotalRewardPrice );
		cltMsg clMsg( GAMEMSG_RESPONSE_BBB_ALREADYRESERVED, sizeof(clinfo), (BYTE*)&clinfo);
		pclChar->SendNetMsg((sPacketHeader*)&clMsg);
	}
	else
	{
		// ��⸮��Ʈ ���������� ����� ����Ʈ ������
		_BBBWaitUserData aWaitList[MAX_RESERVATION_NUM];
		ZeroMemory( aWaitList, (sizeof(_BBBWaitUserData) * MAX_RESERVATION_NUM) );

		m_BBBWaitListMgr.GetWaitList( aWaitList );

		// �޼����� ����� ����Ʈ �־� Ŭ��� ����
		cltGameResponse_BBB_WaitList_Answer clinfo( aWaitList, false, m_siTotalRewardPrice );
		cltMsg clMsg( GAMEMSG_RESPONSE_BBB_ALREADYRESERVED, sizeof(clinfo), (BYTE*)&clinfo);
		pclChar->SendNetMsg((sPacketHeader*)&clMsg);
	}
}