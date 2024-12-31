// tys-

#include "Char/CharManager/CharManager.h"
#include "../Server/Server.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-Person.h"
#include "../../CommonLogic/MsgRval-Define.h"
#include "../../CommonLogic/Msg/MsgType-SystemReward.h"

void cltServer::DoMsg_DBMSG_RESPONSE_SYSTEMREWARDLIST( sPacketHeader* pPacket )
{
	sDBResponse_SystemRewardList* pclinfo = (sDBResponse_SystemRewardList*)pPacket;

	SI32 id = pclinfo->usCharID ;
	if ( pclCM->IsValidID(id) == false ) return ;

	SI32 personid = pclinfo->siPersonID ;
	if ( pclCM->CR[id]->pclCI->GetPersonID() != personid ) return ;
	
	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL ) return ;

	if ( pclinfo->siResult != 1 )
		return;

	cltGameMsgResponse_SystemRewardList	clinfo;

	clinfo.m_siCurPage = pclinfo->m_siCurPage;
	clinfo.m_siMaxPage = pclinfo->m_siMaxPage;

	for ( SI32 i=0; i < MAX_SYSTEMREWARD_LIST; ++i )
	{
		clinfo.clInfo[i].Set( &pclinfo->clInfo[i] );
	}

	cltMsg clMsg(GAMEMSG_RESPONSE_SYSTEMREWARDLIST, sizeof(clinfo), (BYTE*)&clinfo);
	pclchar->SendNetMsg((sPacketHeader*)&clMsg);
}

void cltServer::DoMsg_DBMSG_RESPONSE_RECIEVESYSTEMREWARD( sPacketHeader* pPacket )
{
	sDBResponse_RecieveSystemReward* pclinfo = (sDBResponse_RecieveSystemReward*)pPacket;

	// ������ ���� �߰�
	if( pclinfo->siItemPos < 0 || pclinfo->siItemPos >= MAX_ITEM_PER_PERSON )			return;

	SYSTEMTIME sTime;
	SI32 id = pclinfo->usCharID ;
	if ( pclCM->IsValidID(id) == false ) return ;

	SI32 personid = pclinfo->siPersonID ;
	if ( pclCM->CR[id]->pclCI->GetPersonID() != personid ) return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL ) return ;

	if ( pclinfo->siResult != 1 )
		return;

	// ������ ������Ʈ
	pclchar->pclCI->clCharItem.clItem[ pclinfo->siItemPos ].Set( &pclinfo->clItem );

	// �� ������Ʈ
	pclchar->pclCI->clIP.SetMoney( pclinfo->siMoney );
	//�����ð�������Ʈ
	GetLocalTime(&sTime);

	pclAddMoneyStatistics->Add(ADDMONEY_STATISTIC_SYSTEMREWARD, pclinfo->clInfo.m_siMoney);

	// [��ȣ_NHN->NDOORS] �̰��α�
	SendLog_WriteLogToDB(	LOGCOMMAND_TYPE_REWARD, 
							LOGCOMMAND_INDEX_REWARD_TINTIN, 
							0,
							pclchar, 
							NULL, 
							0, 
							0, 
							0, 
							&pclinfo->clItem, 
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
							(TCHAR*)pclchar->pclCI->clBI.GetName(), 
							NULL);

	// Ŭ���̾�Ʈ�� ���� ����
	cltGameMsgResponse_RecieveSystemReward clinfo( &pclinfo->clInfo, pclinfo->siItemPos, &pclinfo->clItem, pclinfo->siMoney);
	cltMsg clMsg(GAMEMSG_RESPONSE_RECIEVESYSTEMREWARD, sizeof(clinfo), (BYTE*)&clinfo);
	pclchar->SendNetMsg((sPacketHeader*)&clMsg);

	//// ������� ����Ʈ ������Ʈ
	//sDBRequest_SystemRewardList	clMsg2(pclchar->pclCI->GetPersonID(), (UI16)pclchar->GetCharUnique(),sTime);
	//pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg2);
}

void cltServer::DoMsg_DBMSG_RESPONSE_GIVESYSTEMREWARD( sPacketHeader* pPacket )
{
	sDBResponse_GiveSystemReward* pclinfo = (sDBResponse_GiveSystemReward*)pPacket;

	SI32 id = pclinfo->usCharID ;
	if ( pclCM->IsValidID(id) == false ) return ;

	SI32 personid = pclinfo->siPersonID ;
	if ( pclCM->CR[id]->pclCI->GetPersonID() != personid ) return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL ) return ;

	if ( pclinfo->siResult != 1 )
		return;

	// ���� ���� �˸�. -  �Ͻ� ����
	cltLetterMsg_GiveSystemReward clletter( &pclinfo->clInfo );
	//SendLetterMsg( pclchar->pclCI->GetPersonID(), (cltLetterHeader*)&clletter );
}