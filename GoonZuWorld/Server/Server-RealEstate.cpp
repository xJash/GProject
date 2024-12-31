//---------------------------------
// 2003/10/11 ���°�
//---------------------------------

#include "..\Common\CommonHeader.h"
#include "..\Server\Server.h"


#include "../../Server/AuthServer/AuthMsg.h"
#include "..\..\DBManager\GameDBManager_World\DBMsg-House.h"

#include "..\CommonLogic\MsgType-RealEstate.h"

//-------------------------------------
// Common
//-------------------------------------
#include "PersonInfo.h"
#include "Char\CharManager\CharManager.h"

// �ε��� ��� ���� ��û. 
void cltServer::DoMsg_GAMEMSG_REQUEST_EXTENDCONTRACT(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_ExtendContract* pclinfo = (cltGameMsgRequest_ExtendContract*)pclMsg->cData;

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();
	if(personid <= 0)return ;

	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique <= 0)return ;

	SI32 realestatetype = pclinfo->siRealEstateType ;
	if(realestatetype != REALESTATE_TYPE_HOUSE)return ;

	SI32 index = pclinfo->siIndex;

	//-------------------------------------------------
	// �־��� �ε����� id�� �������� Ȯ���Ѵ�. 
	//-------------------------------------------------
	if( pclHouseManager->IsHouseHost(personid, villageunique, index) == false)
	{
		return ;
	}

	//------------------------------------------------
	// Ŭ���̾�Ʈ�� �䱸�� ����� ������ ���� �������� Ȯ���Ѵ�. 
	//------------------------------------------------
	
	cltStrInfo* pclvary = pclHouseManager->GetStrInfo(villageunique);
	if(pclvary == NULL)return ;

	if(pclvary->clHouseStrInfo.clRentContract.IsSame(&pclinfo->clContract) == false)
	{
		return ;
	}

	//----------------------------------------------
	// ��� ���ڸ� ������Ʈ �Ѵ�. 
	//---------------------------------------------
	cltRentContract clcontract;
	clcontract.Set(&pclinfo->clContract);
	clcontract.clDate.Set(&pclTime->clDate);

	//-----------------------------------------------
	// DB�� ����� ������ ���� ��û�Ѵ�. 
	//-----------------------------------------------
	sDBRequest_ExtendContract clMsg(id, personid, villageunique, realestatetype, index, &clcontract);
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

	pclDelMoneyStatistics->Add(DELMONEY_SERVICECHARGE, clcontract.siRentFee);
}
