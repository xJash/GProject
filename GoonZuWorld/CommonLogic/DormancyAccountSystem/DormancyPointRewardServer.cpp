#include ".\dormancypointreward.h"

#include "../CommonLogic/msgtype.h"
#include "../CommonLogic/msg/Msgtype-DormancyAccount.h"
#include "../common/char/CharServer/Char-Server.h"
#include "../../server/server.h"

#include "../../CommonLogic/MsgType-Person.h"
#include "../../DBManager/GameDBManager_World/DBMsg-Dormancy.h"
#include "../MsgRval-Define.h"
#include "../NLib/NUtil.h"
#include "../common/Letter/Letter.h"

CDormancyPointRewardServer::CDormancyPointRewardServer(void) : CDormancyPointReward()
{
	m_pclServer = (cltServer *)pclClient;
}

CDormancyPointRewardServer::~CDormancyPointRewardServer(void)
{
}

// �޸� ���� ���� �����ϱ� ��û
BOOL	CDormancyPointRewardServer::SendDBChangeDormancyState(cltCharServer *pclServer, bool bDormancyState)
{
	if( NULL == pclServer)
		return FALSE;
	if( NULL == pclServer->pclCI)
		return FALSE;
	if( NULL == m_pclServer->pclGameDBProcess)
		return FALSE;

	// �޸� ����Ʈ ����
	CDormancyInfo &rclDormancyInfo = pclServer->pclCI->clDormancyInfo;

	// �޸� ���� ���� ����
	sDBRequest_ChangeDormancyState clMsg(pclServer->GetID(),pclServer->pclCI->GetPersonID(), bDormancyState);
	m_pclServer->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

	return TRUE;
}

// �޸� ���� ���� �����ϱ� ����
BOOL	CDormancyPointRewardServer::RecvDBChangeDormancyState(cltCharServer *pclServer, bool bDormancyState)
{
	if( NULL == pclServer)
		return FALSE;

	// �޸� ����Ʈ ����
	CDormancyInfo &rclDormancyInfo = pclServer->pclCI->clDormancyInfo;
	rclDormancyInfo.SetDormancyState(bDormancyState);

	SendClientDormancyInfo(pclServer);
	return TRUE;
}


// ����Ʈ ������ ����
BOOL	CDormancyPointRewardServer::BuyPointItemRequest(SI32 siCharId , cltCharServer *pclChar, SI32 siItemUnique)
{
	if( NULL == pclChar)
		return FALSE;
	if( NULL == m_pclDormancyPointItemMgr)
		return FALSE;
	// �޸� ����Ʈ ������ ���� �˻��Ѵ�.
	CDormancyPointItem *pclPointItem = m_pclDormancyPointItemMgr->GetDormancyPointItem(siItemUnique);
	if( NULL == pclPointItem)
		return FALSE;
	if( NULL == pclChar->pclCI)
		return FALSE;
	if( NULL == m_pclServer->pclItemManager)
		return FALSE;

	const SI32	ITEMNUM = 1;

	//---------------------------------------------
	// ���� �Ǿ� �ִ� ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	pclChar->ItemUseReserveAction();

	//---------------------------------------------
	// ���� �Ǿ� �ִ� źȯ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	pclChar->BulletUseReserveAction();


	// �޸� ����Ʈ ����
	CDormancyInfo &rclDormancyInfo = pclChar->pclCI->clDormancyInfo;

	// ������ �޸� ����Ʈ
	SI32 siPoint = rclDormancyInfo.GetDormancyPoint() - pclPointItem->GetPoint();

	if( siPoint < 0)
	{
		m_pclServer->SendServerResponseMsg(0, SRVAL_FAIL_NOT_ENOUGH_POINT, 0, 0, pclChar->GetID());
		return FALSE;
	}

	// ������
	cltItemInfo* pclItemInfo = m_pclServer->pclItemManager->FindItemInfo(siItemUnique);
	if( NULL == pclItemInfo )
	{
		return FALSE;
	}
	cltItem *pclItem = &pclItemInfo->clItem;
	if( NULL == pclItem)
	{
		return FALSE;
	}

	SI16 brareswitch = 0;
	// ���� ������
	cltItem clRewardItem;
	clRewardItem.Init();

	// ������ ���Ⱓ
	UI32 uiUsedate = pclItem->uiDateUseDay;

	if( FALSE == m_pclServer->pclItemManager->MakeRandItemUnique(siItemUnique, &clRewardItem, 0, 0, &brareswitch,0,0,0,0,0,uiUsedate))
		return FALSE;

	clRewardItem.SetItemNum( ITEMNUM );

	// �κ��� �߰� �� �� �ִ� ��
	SI16 siItempos;
	cltItem cltoitem;
	SI32 rtnvalue;
	if(pclChar->CanAddInv(INVMODE_ALL, &clRewardItem, &siItempos, &cltoitem, &rtnvalue) == TRUE)
	{
		sDBRequest_BuyDormancyPointItem clMsg(siCharId, pclChar->pclCI->GetPersonID(), &clRewardItem, clRewardItem.CanPile(m_pclServer->pclItemManager), siPoint, pclPointItem->GetPoint() * -1, siItempos);
		m_pclServer->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	}
	else
	{
		m_pclServer->SendServerResponseMsg(0, SRVAL_FAIL_IS_FULLIVEN, 0, 0, pclChar->GetID());
	}

	return TRUE;
}

// ����Ʈ ������ ����
BOOL	CDormancyPointRewardServer::BuyPointItemResponse(cltCharServer*	pclChar, cltItem *pclItem, SI32 siItemPos, SI32 siItemPoint)
{
	if( NULL == pclChar)
		return FALSE;
	if( NULL == pclChar->pclCI)
		return FALSE;
	if( NULL == pclItem)
		return FALSE;
	if( NULL == m_pclDormancyPointItemMgr)
		return FALSE;

	// �޸� ����Ʈ ����
	CDormancyInfo &rclDormancyInfo = pclChar->pclCI->clDormancyInfo;

	// 1.  ����Ʈ ���� ����
	m_PointProcess.ChangePoint(pclChar,siItemPoint);

	// 2. �κ��丮�� ������ ����
	if( siItemPos >= 0 && siItemPos < MAX_ITEM_PER_PERSON )
	{
		// �κ��丮�� ������Ʈ �Ѵ�. 
		pclChar->pclCI->clCharItem.clItem[siItemPos].Set(pclItem);

		// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
		cltGameMsgResponse_PersonItemInfo clinfo(siItemPos, PERSONITEMINFO_OPTION_NONE, 0, 0, pclItem, 0);
		cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
		pclChar->SendNetMsg((sPacketHeader*)&clMsg);
	}

	// �α� - �޸� ����Ʈ�� ������ ����
	if(m_pclServer->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// para1 => ���� ����Ʈ
		m_pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_DORMANCY, LOGCOMMAND_INDEX_DORMANCY_BUY_ITEM, 
			0, pclChar,NULL ,0, 0, 0, pclItem, 0, 0, 0, 0, 0, 0, 
			siItemPoint, 0, 0, 0, 0, NULL, NULL);
	}

	// 3.����Ʈ ���� ����
	SendClientDormancyInfo(pclChar);

	return TRUE;
}

// �޸� ����Ʈ ���� ����
BOOL	CDormancyPointRewardServer::SendClientDormancyInfo(cltCharServer*	pclChar)
{
	if( NULL == pclChar)
		return FALSE;

	// �޸� ����Ʈ ����
	CDormancyInfo &rclDormancyInfo = pclChar->pclCI->clDormancyInfo;

	// ����Ʈ ���� ����
	cltGameMsgResponse_DormancyRefreshPointInfo clInfo( rclDormancyInfo.GetDormancyPoint(), rclDormancyInfo.GetRemainedDormancyPlayTime(), rclDormancyInfo.GetDormancyState() ,rclDormancyInfo.GetStartedDate()->wYear,rclDormancyInfo.GetStartedDate()->wMonth, rclDormancyInfo.GetStartedDate()->wDay);
	cltMsg clMsg(GAMEMSG_RESPONSE_DORMANCY_REFRESHPOINTINFO, sizeof(clInfo), (BYTE*)&clInfo);
	pclChar->SendNetMsg((sPacketHeader*)&clMsg);
	
	return TRUE;
}

// DB�� �޸� ����Ʈ ���� ����
BOOL	CDormancyPointRewardServer::RecvDBDormancyInfo(cltCharServer*	pclChar, SI32 siPoint)
{
	if( NULL == pclChar)
		return FALSE;

	// �޸� ����Ʈ ����
	m_PointProcess.ChangePoint(pclChar, siPoint);

	return TRUE;
}

BOOL	CDormancyPointRewardServer::SendDBDormancyInfo(cltCharServer *pclServer, SI32 siDPoint)
{
	if( NULL == pclServer)
		return FALSE;
	if( NULL == pclServer->pclCI)
		return FALSE;
	if( NULL == m_pclServer->pclGameDBProcess)
		return FALSE;
	if( pclServer->GetID() <= 0)
		return FALSE;

	// �޸� ����Ʈ ����
	CDormancyInfo &rclDormancyInfo = pclServer->pclCI->clDormancyInfo;

	if( FALSE == rclDormancyInfo.GetDormancyState())
		return FALSE;

	// ����Ʈ ���� ����
	sDBRequest_SetDormancyPointInfo clMsg(pclServer->GetID(),pclServer->pclCI->GetPersonID(), siDPoint ,rclDormancyInfo.GetRemainedDormancyPlayTime());
	m_pclServer->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

	return TRUE;
}

// ����Ʈ ���
BOOL	CDormancyPointRewardServer::CalcPoint(cltCharServer *pclServer)
{
	if( NULL == pclServer )
		return FALSE;

	SI32 siReturnValue = CDormancyPointProcess::CALCPOINT_RESULT_CALCERROR;
	const SI32	INCREASEPOINT = 1;

	CDormancyInfo &rclDormancyInfo = pclServer->pclCI->clDormancyInfo;

	if(rclDormancyInfo.GetDormancyState() == FALSE)
	{
		return FALSE;
	}

	siReturnValue = m_PointProcess.CalcPoint(pclServer);

	if( CDormancyPointProcess::CALCPOINT_RESULT_INCREASEPLAYTIME == siReturnValue )
	{
		// �÷��� �ð� ���� ����
		SendDBDormancyInfo(pclServer, 0 );
	}
	else if( CDormancyPointProcess::CALCPOINT_RESULT_INCREASEPOINT == siReturnValue)
	{
		// ����Ʈ ���� �޽��� ����
		SendDBDormancyInfo(pclServer, INCREASEPOINT );

		if(m_pclServer->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// �α� ����� - �ð��� ���� ����Ʈ 1 ����
			m_pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_DORMANCY, LOGCOMMAND_INDEX_DORMANCY_INCREASE_POINT, 
				0, pclServer,NULL ,0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
				0, 0, 0, 0, 0, NULL, NULL);
		}
	}

	return TRUE;
}

// �Ⱓ�� ��������
BOOL	CDormancyPointRewardServer::IsExpiration(cltCharServer *pclServer, _SYSTEMTIME &rclCurrentDate)
{
	if( NULL == pclServer )
		return FALSE;

	SI32 siDate = GetDateFromExpiration(pclServer, rclCurrentDate);

	if( siDate == -1)
		return FALSE;

	if( DURATIONDATE < siDate)
	{
		// �α� - �޸� ����Ʈ�� ������ ����
		if(m_pclServer->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			m_pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_DORMANCY, LOGCOMMAND_INDEX_DORMANCY_BUY_ITEM, 
				0, pclServer,NULL ,0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
				0, 0, 0, 0, 0, NULL, NULL);
		}

		return TRUE;
	}

	return FALSE;
}


// �޸� ���� ���Ḧ ��� �Ѵ�.
BOOL	CDormancyPointRewardServer::WaringExpiration(cltCharServer *pclServer)
{
	if( NULL == pclServer )
		return FALSE;

	CDormancyInfo &rclDormancyInfo = pclServer->pclCI->clDormancyInfo;

	if(rclDormancyInfo.GetDormancyState() == FALSE)
	{
		return FALSE;
	}

	_SYSTEMTIME st;
	GetLocalTime(&st);

	SI32 siDate = GetDateFromExpiration(pclServer, st);

	// ���� ��¥
	SI32 siRemainedDate = DURATIONDATE - siDate ;

	if( siDate == -1)
		return FALSE;

	if( (0 <= siRemainedDate) && (siRemainedDate <= WARING_EXPIRATION_FLAG))
	{
		// ��� ���� ������
		cltLetterMsg_DormancyWaringExpiration clletter(siRemainedDate);
		m_pclServer->SendLetterMsg(pclServer->pclCI->GetPersonID(), (cltLetterHeader*)&clletter );

		return TRUE;
	}

	return FALSE;
}

// �޸� ���� ���¸� ������ �Ⱓ
SI32	CDormancyPointRewardServer::GetDateFromExpiration(cltCharServer *pclServer, _SYSTEMTIME &rclCurrentDate)
{
	if( NULL == pclServer )
		return -1;

	CDormancyInfo &rclDormancyInfo = pclServer->pclCI->clDormancyInfo;

	if(rclDormancyInfo.GetDormancyState() == FALSE)
	{
		return -1;
	}

	// ������
	_SYSTEMTIME *pStartedTime = rclDormancyInfo.GetStartedDate();

	// �ʿ� ���� �� �ʱ�ȭ
	rclCurrentDate.wHour = 0;
	rclCurrentDate.wMinute = 0;
	rclCurrentDate.wSecond = 0;

	// ���� ����� ���� ���ߴٸ�
	if( 0 == pStartedTime->wYear)
		return -1;

	if( NULL == pStartedTime)
		return -1;
	
	SI32 siDate = DiffDate(&rclCurrentDate, pStartedTime);

	return siDate;
}

// ó�� ���� ���� ����
BOOL	CDormancyPointRewardServer::DeterminProcessing(SI32	siCurrentime)
{
	return m_PointProcess.DeterminProcessing(siCurrentime);
}