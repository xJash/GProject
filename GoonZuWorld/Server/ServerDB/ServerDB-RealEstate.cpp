//---------------------------------
// 2003/10/13 ���°�
//---------------------------------

#include "..\Common\CommonHeader.h"
#include "..\Server\Server.h"

//-------------------------------------
// Common
//-------------------------------------
#include "PersonInfo.h"
#include "..\..\Common\Map\Map.h"
#include "Char\CharManager\CharManager.h"

#include "..\../../Server/AuthServer/AuthMsg.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-House.h"

#include "MsgRval-Define.h"

// �ε��� ����� �����Ѵ�. 
void cltServer::DoMsg_DBMSG_RESPONSE_EXTENDCONTRACT(sPacketHeader* pPacket)
{
	sDBResponse_ExtendContract* pclMsg = (sDBResponse_ExtendContract*)pPacket;

	SI32 returnval = 0;

	SI32 villageunique	= pclMsg->siVillageUnique;
	SI32 realestatetype	= pclMsg->siRealEstateType;
	SI32 houseindex		= pclMsg->siIndex;

	cltRentContract* pclcontract = &pclMsg->clRentContract; 
		
	switch(pclMsg->siResult)
	{
	case 0:
		break;
	case 1: 
		{
			switch(realestatetype)
			{
			case REALESTATE_TYPE_HOUSE:
				{
					// ���� ���������� ����Ѵ�. 
					pclHouseManager->SetRent(villageunique, houseindex, &pclMsg->clPerson, pclcontract);
					
					SI32 id = pclMsg->usCharID;
					if(pclCM->IsValidID(id) && pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->clPerson.GetPersonID())
					{
						// Person�� �ľ��� �ε��� ������ ������Ʈ �Ѵ�. 
						pclCM->CR[id]->pclCI->clRealEstate.Add(REALESTATE_TYPE_HOUSE, pclMsg->siVillageUnique, pclMsg->siIndex, &pclMsg->clRentContract);
						pclCM->CR[id]->SetUpdateSwitch(UPDATE_REALESTATE, true, 0);

						// ���� ������ ������Ʈ �Ѵ�. 
						pclCM->CR[id]->pclCI->clBank.SetMoney(pclMsg->siBankMoney);
						pclCM->CR[id]->SetUpdateSwitch(UPDATE_BANK, true, 0);

						if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog))
						{
							// TEMP LEEKH --------------------------------------------------------------
							// [�α��߰� : Ȳ���� 2007. 10. 10] // �ε��� ����� ����.
							// param2		 == �ε����� ����, 
							// param3		 == �ε����� ��ȣ.  
							// pszCharParam1 == �ð�.
							TCHAR pszCharParam1[50] = {'\0', };
							ZeroMemory(pszCharParam1, sizeof(pszCharParam1));
							StringCchPrintf(pszCharParam1, sizeof(pszCharParam1), TEXT("%d-%d-%d, %d : %d"),	
								pclMsg->clRentContract.clDate.uiYear,
								pclMsg->clRentContract.clDate.uiMonth,
								pclMsg->clRentContract.clDate.uiDay,
								pclMsg->clRentContract.clDate.uiHour,
								pclMsg->clRentContract.clDate.uiMinute );



							SendLog_WriteLogToDB(LOGCOMMAND_TYPE_HOUSE, LOGCOMMAND_INDEX_HOUSE_EXTENDHOUSECONTRACT,
								0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, pclMsg->siBankMoney, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
								pclMsg->siRealEstateType, pclMsg->siIndex, 0, 0, 0,
								pszCharParam1, NULL);
							// TEMP LEEKH --------------------------------------------------------------
						}

						returnval = SRVAL_HOUSE_SUCCESSEXTENDCONTRACT;
					}
				}
				break;
			default:
				MsgBox(TEXT("fdsfijfd"), TEXT("fdfef:%d"), realestatetype);
				return ;
				break;
			}
		}
		break;
	case -1:	
		break;
	case -2:	
		returnval	= SRVAL_HOUSE_FAILEXTENDCONTRAC_NOMONEY; 
		break;
	}

	SI32 id	= pclMsg->usCharID;
	if(pclCM->IsValidID(id) == FALSE)return ;

	if(returnval)
	{
		// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
		SendServerResponseMsg(RANKTYPE_HOUSE, returnval,  0, 0, pclCM->CR[id]->GetCharUnique());
	}
}