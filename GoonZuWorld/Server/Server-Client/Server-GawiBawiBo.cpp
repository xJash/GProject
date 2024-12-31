#include "Char/CharManager/CharManager.h"
#include "../Server/Server.h"

#include "../../common/Order/order.h"
#include "../../common/JWLib/IsCorrectID/IsCorrectID.h"
#include "../../../DBManager/GameDBManager_World/DBMsg.h"

#include "MsgRval-Define.h"
#include "MsgType-Person.h"
#include "../../CommonLogic/MsgType-GawiBawiBo.h"
#include "../GawiBawiBoMgr/GawiBawiBoMgr_Server.h"

#include "../../DBManager/GameDBManager_World/DBMsg-Person.h"


//  [8/12/2009 ��ȣ_GAWIBAWIBO]	�ݾ� ����
void cltServer::DoMsg_GAMEMSG_REQUEST_GAWIBAWIBO_CHARGED_MONEY(cltMsg* pclMsg, SI32 id)
{
	cltGameRequest_GawiBawiBo_ChargedMoney* pclInfo = (cltGameRequest_GawiBawiBo_ChargedMoney*)pclMsg->cData;
	if(NULL == pclInfo)
		return;

	cltCharServer* pclChar = pclCM->GetCharServer( id );
	if ( NULL == pclChar )
		return;

	GMONEY siMoney = GetGawiBawiBoMgr()->GetChargedMoney();	
	if(siMoney < 0)
		return;
    
	//	�ݾ��� ������ų����
	sDBRequest_ChangeMoney clMsg(pclChar->GetID(), pclChar->pclCI->GetPersonID(), CHANGE_MONEY_REASON_GAWIBAWIBO_CHARGED_MONEY, -siMoney);
	pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);


	//	 �÷��̾ ������ �ݾ��� �α� ����
	cltServer* pclserver = (cltServer*)pclClient;
	pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_GAWIBAWIBO, 
									LOGCOMMAND_INDEX_GAWIBAWIBO_DEL_MONEY, 		
									0, 
									pclChar, 
									NULL, 
									0,
									siMoney,
									0,
									NULL,
									0,
									0,
									0,
									0,
									0,
									0,
									0, 
									0,
									0, 
									0, 
									0, 
									NULL, 
									NULL);
}


//  [8/12/2009 ��ȣ_GAWIBAWIBO]	�¹��� ����
void cltServer::DoMsg_GAMEMSG_REQUEST_GAWIBAWIBO_CALCULATE_RESULT(cltMsg* pclMsg, SI32 id)
{
	cltGameRequest_GawiBawiBo_CalculateResult* pclInfo = (cltGameRequest_GawiBawiBo_CalculateResult*)pclMsg->cData;
	if(NULL == pclInfo)
		return;

	cltCharServer* pclChar = pclCM->GetCharServer( id );
	if ( NULL == pclChar )
		return;

	//	 �¹��� ��� ����
	SI08 siResult = GetGawiBawiBoMgr()->GetCalculateResult();
	SI08 siValidCount = CGawiBawiBoMgr_Server::GAWIBAWIBO_RESULT_VALIDCOUNT_NONE;


	// �׻� �̱�� ����̸�
	if(GetGawiBawiBoMgr()->IsAlwaysWin() == true)	 
		siResult = CGawiBawiBoMgr_Server::GAWIBAWIBO_RESULT_WIN;
	

	// ���������� �ɸ������ε� �÷��̾ �̰�ٸ�
	if(siResult == CGawiBawiBoMgr_Server::GAWIBAWIBO_RESULT_WIN)
	{
		if(GetGawiBawiBoMgr()->GetLimitWin() <= pclChar->GetGawiBawiBoCount())		
			siResult = CGawiBawiBoMgr_Server::GAWIBAWIBO_RESULT_LOSE;
	}

	if(siResult == CGawiBawiBoMgr_Server::GAWIBAWIBO_RESULT_WIN || siResult == CGawiBawiBoMgr_Server::GAWIBAWIBO_RESULT_ABUSE_WIN)	// �̰�ٸ� ���� ī��Ʈ ����
	{
		siValidCount = GetGawiBawiBoMgr()->IsValidCount(pclChar->GetGawiBawiBoCount()+1);

		switch(siValidCount)
		{
		case CGawiBawiBoMgr_Server::GAWIBAWIBO_RESULT_VALIDCOUNT_VALID:	// ����ī��Ʈ ���� ��ȿ�Ѱ�.
				pclChar->IncreaseGawiBawiBoCount();
			break;

		case CGawiBawiBoMgr_Server::GAWIBAWIBO_RESULT_VALIDCOUNT_MAXWIN:
				pclChar->IncreaseGawiBawiBoCount();
			break;

		case CGawiBawiBoMgr_Server::GAWIBAWIBO_RESULT_VALIDCOUNT_INVALID:
			{
				pclClient->pclLog->FilePrint("GAWIBAWIBO_ERR.txt", "[Error-StraightWin] GAWIBAWIBO_RESULT_VALIDCOUNT_INVALID :: Current Count = %d",pclChar->GetGawiBawiBoCount()+1);				
				pclChar->InitGawiBawiBoCount();
			}
			break;

		default:
			break;
		}
	}
	else if(siResult == CGawiBawiBoMgr_Server::GAWIBAWIBO_RESULT_LOSE)	//	���ٸ� ���� ī��Ʈ �ʱ�ȭ
		pclChar->InitGawiBawiBoCount();

	cltGameResponse_GawiBawiBo_CalculateResult clInfo(siResult, pclChar->GetGawiBawiBoCount(), siValidCount);
	cltMsg clStatusInfoMsg( GAMEMSG_RESPONSE_GAWIBAWIBO_CALCULATE_RESULT, sizeof(clInfo), (BYTE*)&clInfo );
	pclChar->SendNetMsg( (sPacketHeader*)&clStatusInfoMsg);
}

//	���� ��Ŷ
void cltServer::DoMsg_GAMEMSG_REQUEST_GAWIBAWIBO_REWARD(cltMsg* pclMsg, SI32 id)
{
	cltGameRequest_GawiBawiBo_Reward* pclInfo = (cltGameRequest_GawiBawiBo_Reward*)pclMsg->cData;
	if(NULL == pclInfo)
		return;

	cltCharServer* pclChar = pclCM->GetCharServer( id );
	if ( NULL == pclChar )
		return;


    //	 Ŭ���̾�Ʈ���� �ַ��� ����� �������� ������ ���� �ݾ��� ��ġ�ϴ°�?
	GMONEY siServerMoney = GetGawiBawiBoMgr()->GetCalculateCumulativeMoney(pclChar->GetGawiBawiBoCount());
	//GMONEY siClientMoney = pclInfo->m_siMoney;
	
	////	Ŭ���̾�Ʈ�� ����ݾװ� ������ ����ݾ��� �ٸ� ���
	//if(siServerMoney != siClientMoney)
	//{
	//	pclClient->pclLog->FilePrint("GAWIBAWIBO_ERR.txt", "[Error-RewardMonyeData] ServerMoney = %d, ClientMoney = %d",siServerMoney, siClientMoney);
	//	assert(0);

	//	return;
	//}

	// 8���� �̻� �ߴٸ� �ֺ��ε鿡�� �˸�
	if(pclChar->GetGawiBawiBoCount() >= 8)
	{
		TCHAR szName[256] = "0,";
		StringCchCopy(szName, 256, pclChar->GetName());

		cltGameResponse_GawiBawiBo_Notice_Reward cNotice(szName, pclChar->GetGawiBawiBoCount(), siServerMoney);
		cltMsg clMsg(GAMEMSG_RESPONSE_GAWIBAWIBO_NOTICE_RESULT, sizeof(cltGameResponse_GawiBawiBo_Notice_Reward), (BYTE*)&cNotice);

		//pclChar->SendNeighbourMsg(&clMsg, true);
		pclCM->SendAllPersonInMapMsg((sPacketHeader*)&clMsg, MAPINDEX_FESTIVAL);
	}

	//	 ���� �޴� ���� ������ �ߴ� �� ����̹Ƿ� ����ī��Ʈ �ʱ�ȭ
	pclChar->InitGawiBawiBoCount();

	//	 �������ַ��� �ݾ׿� ������ �����Ƿ� ������ �ش�.
	if(GetGawiBawiBoMgr()->IsValidCount(pclChar->GetGawiBawiBoCount()) == CGawiBawiBoMgr_Server::GAWIBAWIBO_RESULT_VALIDCOUNT_MAXWIN)
	{
		// �ְ����̶��~
		sDBRequest_ChangeMoney clMsg(pclChar->GetID(), pclChar->pclCI->GetPersonID(), CHANGE_MONEY_REASON_GAWIBAWIBO_REWARD_MAX_MONEY, +siServerMoney);
		pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);	
	}
	else
	{
		sDBRequest_ChangeMoney clMsg(pclChar->GetID(), pclChar->pclCI->GetPersonID(), CHANGE_MONEY_REASON_GAWIBAWIBO_REWARD_MONEY, +siServerMoney);
		pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);	
	}



	//	�÷��̾ ���� ���� �ݾ��� �α׿� ����.
	cltServer* pclserver = (cltServer*)pclClient;
	pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_GAWIBAWIBO, 
									LOGCOMMAND_INDEX_GAWIBAWIBO_ADD_MONEY, 		
									0, 
									pclChar, 
									NULL, 
									0,
									siServerMoney,
									0,
									NULL,
									0,
									0,
									0,
									0,
									0,
									0,
									0, 
									0,
									0, 
									0, 
									0, 
									NULL, 
									NULL);
}
