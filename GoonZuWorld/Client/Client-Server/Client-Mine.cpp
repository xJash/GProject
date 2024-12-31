#include "..\Client.h"
#include "..\Client\Music\Music.h"
#include "../CommonLogic/MsgType.h"
#include "../CommonLogic/Msg/MsgType-Mine.h"

void cltClient::DoMsg_GAMEMSG_RESPONSE_MINE_UNITLIST(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_MineUnitList *pclinfo = (cltGameMsgResponse_MineUnitList *)pclMsg->cData;

	// ���� ������ ���� �����ڿ��� �����Ѵ�. 
	for( int i = 0; i < MAX_MINEUNIT_NUMBER; i++)
	{
		pclMineManager->clClientUnit[i].clPerson.Set(&pclinfo->clPerson[i]);
	}
	
	// ���� ������ ȭ�鿡 ǥ���ϵ��� �Ѵ�. 
	pclMineManager->bUpdateMineUnitListShowChiefSwitch = TRUE;
	pclMineManager->bUpdateMineUnitListShowSwitch		= TRUE;

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_MINE_UNITDETAIL(cltMsg* pclMsg, SI32 id)
{

	// ���� ������ Ȯ���Ѵ�. 
	cltGameMsgResponse_MineUnitListDetail* pclinfo = (cltGameMsgResponse_MineUnitListDetail*)pclMsg->cData;
	
	// ���� ������ ���� �����ڿ��� �����Ѵ�. 
	for( int i = 0;i < MAX_MINEUNIT_NUMBER; i++ )
	{
		pclMineManager->clClientUnit[i].clContract.Set(&pclinfo->clContract[i]);
	}

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_MINE_APPLYERLIST(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_MineApplyerList *pclinfo = (cltGameMsgResponse_MineApplyerList *)pclMsg->cData;

	for( int i = 0; i < MAX_APPLY_PER_MINE; i++ ) 
	{
		pclMineManager->clClientApplyer[ i ].Set( &pclinfo->clMineApplyer[ i ] );
	}

	pclMineManager->UpdateMineApplyerListShowSwitch = true;


}

void cltClient::DoMsg_GAMEMSG_RESPONSE_MINE_RENT(cltMsg* pclMsg, SI32 id)
{

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_MINE_DELAPPLYER(cltMsg* pclMsg, SI32 id)
{
	// ��û�� ����� ��� �����Ѵ�.
	SI32 siSlot = (SI32)*pclMsg->cData;

	for(int i = 0; i < MAX_APPLY_PER_MINE;i++)
	{
		if(siSlot >= 0 && siSlot == i)
		{
			pclMineManager->clClientApplyer[i].Init();
		}	
	}

	// ���� ������ ȭ�鿡 ǥ���ϵ��� �Ѵ�. 
	pclMineManager->UpdateMineApplyerListShowSwitch = TRUE;
}