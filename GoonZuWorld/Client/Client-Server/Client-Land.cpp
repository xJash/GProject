#include "..\Client.h"
#include "..\Client\Music\Music.h"
#include "../CommonLogic/MsgType.h"
#include "../CommonLogic/Msg/MsgType-Land.h"

void cltClient::DoMsg_GAMEMSG_RESPONSE_LAND_UNITLIST(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_LandUnitList *pclinfo = (cltGameMsgResponse_LandUnitList *)pclMsg->cData;

	// ���� ������ ���� �����ڿ��� �����Ѵ�. 
	for( int i = 0; i < MAX_LANDUNIT_NUMBER; i++)
	{
		pclLandManager->clClientUnit[i].clPerson.Set(&pclinfo->clPerson[i]);
	}
	
	// ���� ������ ȭ�鿡 ǥ���ϵ��� �Ѵ�. 
	pclLandManager->bUpdateLandUnitListShowChiefSwitch = TRUE;
	pclLandManager->bUpdateLandUnitListShowSwitch		= TRUE;

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_LAND_UNITDETAIL(cltMsg* pclMsg, SI32 id)
{

	// ���� ������ Ȯ���Ѵ�. 
	cltGameMsgResponse_LandUnitListDetail* pclinfo = (cltGameMsgResponse_LandUnitListDetail*)pclMsg->cData;
	
	// ���� ������ ���� �����ڿ��� �����Ѵ�. 
	for( int i = 0;i < MAX_LANDUNIT_NUMBER; i++ )
	{
		pclLandManager->clClientUnit[i].clContract.Set(&pclinfo->clContract[i]);
	}

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_LAND_APPLYERLIST(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_LandApplyerList *pclinfo = (cltGameMsgResponse_LandApplyerList *)pclMsg->cData;

	for( int i = 0; i < MAX_APPLY_PER_LAND; i++ ) 
	{
		pclLandManager->clClientApplyer[ i ].Set( &pclinfo->clLandApplyer[ i ] );
	}

	pclLandManager->UpdateLandApplyerListShowSwitch = true;


}

void cltClient::DoMsg_GAMEMSG_RESPONSE_LAND_RENT(cltMsg* pclMsg, SI32 id)
{

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_LAND_DELAPPLYER(cltMsg* pclMsg, SI32 id)
{
	// ��û�� ����� ��� �����Ѵ�. 
	SI32 siSlot = (SI32)*pclMsg->cData;

	for(int i = 0; i < MAX_APPLY_PER_LAND;i++)
	{
		if(siSlot >=0 && siSlot == i)
		{
			pclLandManager->clClientApplyer[i].Init();
		}		
	}

	// ���� ������ ȭ�鿡 ǥ���ϵ��� �Ѵ�. 
	pclLandManager->UpdateLandApplyerListShowSwitch = TRUE;
}