//---------------------------------
// 2004/2/6 ���°�
//---------------------------------

#include "Char/CharManager/CharManager.h"

#include "../Server/Server.h"

#include "../../DBManager/GameDBManager_World/DBMsg.h"

#include "Msg/MsgType-Village.h"

#include "../Client/ninterface/nvillagedetailinfo/NVillageDetailInfo.h"

#include "../CommonLogic/Cityhall/Cityhall.h"
#include "../CommonLogic/Hunt/Hunt.h"
#include "../CommonLogic/HorseMarket/HorseMarket.h"
#include "../CommonLogic/SummonMarket/SummonMarket.h"
#include "../CommonLogic/SummonHeroMarket/SummonHeroMarket.h"
#include "../CommonLogic/Land/Land.h"
#include "../CommonLogic/Feast/Feast.h"
#include "../CommonLogic/RealEstate/RealEstate.h"
#include "../CommonLogic/Mine/Mine.h"
#include "../CommonLogic/Guild/Guild.h"

// ���� �� ���� ��û . 
void cltServer::DoMsg_GAMEMSG_REQUEST_VILLAGEDETAILINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_VillageDetailInfo* pclinfo = (cltGameMsgRequest_VillageDetailInfo*)pclMsg->cData;

	// ������ �޽��� ���� �ð��� üũ�Ѵ�. 
	if(id && pclCM->CR[id]->CheckLastMsgClock(1000) == true)
	{
		return ;
	}


	SI32 i;
	bool bcheckswitch = false;
	cltGameMsgResponse_VillageDetailInfo clinfo;

	// �������� ������. 
	if(pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_WAR)
	{
		bcheckswitch = true;

		clinfo.siVillageDetailInfoType = pclinfo->siVillageDetailInfoType;
		for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
		{
			if(pclVillageManager->pclVillageInfo[i] == NULL)continue;

			clinfo.siWarKillNum[i] = pclVillageManager->pclVillageInfo[i]->siWarKillNumber;
		}
	}
	// �ֹ� 100��� �������� ������. 
	if(pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_WARPERRESIDENT)
	{
		bcheckswitch = true;

		// �������� ���´�. 
		clinfo.siVillageDetailInfoType = pclinfo->siVillageDetailInfoType;
		for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
		{
			if(pclVillageManager->pclVillageInfo[i] == NULL)continue;

			clinfo.siWarKillNum[i] = pclVillageManager->pclVillageInfo[i]->siWarKillNumber;
		}
	
		// �ֹμ��� ����Ͽ� �����Ѵ�. 
		for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
		{
			if(pclVillageManager->pclVillageInfo[i] == NULL)continue;

			cltStrInfo* pclstrinfo = pclCityHallManager->GetStrInfo(i);
			if(pclstrinfo)
			{
				SI32 peoplenum  = pclstrinfo->clCityhallStrInfo.siResidentNum;

				peoplenum = max(1, (peoplenum / 100) + min(1, (peoplenum % 100)));

				clinfo.siWarKillNum[i] = clinfo.siWarKillNum[i] / peoplenum;
			}
		}


	}
	// �ֹμ� ������. 
	if(pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_PEOPLE)
	{
		bcheckswitch = true;

		clinfo.siVillageDetailInfoType = pclinfo->siVillageDetailInfoType;
		for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
		{
			if(pclVillageManager->pclVillageInfo[i] == NULL)continue;

			cltStrInfo* pclstrinfo = pclCityHallManager->GetStrInfo(i);
			if(pclstrinfo)
			{
				clinfo.uiPeople[i] = pclstrinfo->clCityhallStrInfo.siResidentNum;
			}
		}

		if ( pclCM->IsValidID(id) )
		{
			pclCM->CR[id]->DoQuestCheckAndAction( QUEST_CLEAR_COND_SORTRESIDENT );
		}
	}
	// ���� ����ڼ�.
	if(pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_USER)
	{
		bcheckswitch = true;

		clinfo.siVillageDetailInfoType = pclinfo->siVillageDetailInfoType;
		for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
		{
			if(pclVillageManager->pclVillageInfo[i] == NULL)continue;

			clinfo.siUserNum[i] = pclVillageManager->pclVillageInfo[i]->siUserNum;
		}
	}
	// ���⵵ ����. 
	if(pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_PREVYEARDBID)
	{
		bcheckswitch = true;

		clinfo.siVillageDetailInfoType = pclinfo->siVillageDetailInfoType;
		for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
		{
			if(pclVillageManager->pclVillageInfo[i] == NULL)continue;


			cltStrInfo* pclstr = pclCityHallManager->GetStrInfo(i);
			if(pclstr)
			{
				SI32 year = max(0, pclTime->clDate.uiYear-1);
				clinfo.siBidMoney[i] = pclstr->clCityhallStrInfo.GetTotalDividendMoney(year);
			}
		}
	}
	// ������ ���� ����. 
	if(pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_HUNT)
	{
		bcheckswitch = true;

		clinfo.siVillageDetailInfoType = pclinfo->siVillageDetailInfoType;
		for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
		{
			if(pclVillageManager->pclVillageInfo[i] == NULL)continue;


			cltStrInfo* pclstr = pclHuntManager->GetStrInfo(i);
			if(pclstr)
			{
				
				// ������ ���°� �����̾�� 
				//[����] �������� ������ ���������� �ȳ����°� ����. �Ʒ� ���ǹ��� ����? => 2008-5-7
				if(/*pclstr->clHuntStrInfo.siHuntStatus == HUNT_ENTER_ENABLESTATUS 
				&& */pclVillageManager->IsThereStructure(i, RANKTYPE_HUNT))
				{
					clinfo.siStrData[i] = pclstr->clHuntStrInfo.siUserNum + 1;	// ������ 1 �̻����� �����Ѵ�. 
				}				
				else
				{
					clinfo.siStrData[i] = 0;
				}
			}
		}
	}
	// �纹�� 
	if(pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_HORSEMARKET)
	{
		bcheckswitch = true;

		clinfo.siVillageDetailInfoType = pclinfo->siVillageDetailInfoType;
		for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
		{
			if(pclVillageManager->pclVillageInfo[i] == NULL)continue;


			cltStrInfo* pclstr = pclHorseMarketManager->GetStrInfo(i);
			if(pclstr)
			{
				// ������ ���°� �����̾�� 
				if(pclVillageManager->IsThereStructure(i, RANKTYPE_HORSEMARKET))
				{
					clinfo.siStrData[i] = pclstr->clHorseMarketStrInfo.clFee.GetFeeRate()+1;
				}
				else
				{
					clinfo.siStrData[i] = 0;
				}
			}
		}
	}
	// ���� 
	if(pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_STOCK)
	{
		bcheckswitch = true;

		clinfo.siVillageDetailInfoType = pclinfo->siVillageDetailInfoType;
		for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
		{
			if(pclVillageManager->pclVillageInfo[i] == NULL)continue;


			cltStrInfo* pclstr = pclStockManager->GetStrInfo(i);
			if(pclstr)
			{
				// ����  ���°� �����̾�� 
				if(pclVillageManager->IsThereStructure(i, RANKTYPE_STOCK))
				{
					clinfo.siStrData[i] = pclstr->clStockStrInfo.clFee.GetFeeRate()+1;
				}
				else
				{
					clinfo.siStrData[i] = 0;
				}
			}
		}
	}
	if(pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_NEWMARKET)
	{
		bcheckswitch = true;

		clinfo.siVillageDetailInfoType = pclinfo->siVillageDetailInfoType;
		cltStrInfo* pclStrInfo = NULL;
		for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
		{
			pclStrInfo = pclNewMarketManager->GetStrInfo(i);
			if( NULL != pclStrInfo	)
			{
				// ����  ���°� �����̾�� 
				if(pclVillageManager->IsThereStructure(i, RANKTYPE_NEWMARKET))
				{
					clinfo.siStrData[i] = pclStrInfo->clNewMarketStrInfo.clFee.GetFeeRate() + 1;
				}
				else
				{
					clinfo.siStrData[i] = 0;
				}
			}
		}
	}
	// �Ű�
	if(pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_REALESTATEMARKET)
	{
		bcheckswitch = true;

		clinfo.siVillageDetailInfoType = pclinfo->siVillageDetailInfoType;
		for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
		{
			if(pclVillageManager->pclVillageInfo[i] == NULL)continue;


			cltStrInfo* pclstr = pclRealEstateMarketManager->GetStrInfo(i);
			if(pclstr)
			{
				// ���°� �����̾�� 
				if(pclVillageManager->IsThereStructure(i, RANKTYPE_REALESTATEMARKET))
				{
					clinfo.siStrData[i] = pclstr->clRealEstateMarketStrInfo.clFee.GetFeeRate()+1;
				}
				else
				{
					clinfo.siStrData[i] = 0;
				}
			}
		}
	}
	// �忹��
	if(pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_SUMMONMARKET)
	{
		bcheckswitch = true;

		clinfo.siVillageDetailInfoType = pclinfo->siVillageDetailInfoType;
		for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
		{
			if(pclVillageManager->pclVillageInfo[i] == NULL)continue;


			cltStrInfo* pclstr = pclSummonMarketManager->GetStrInfo(i);
			if(pclstr)
			{
				// ���°� �����̾�� 
				if(pclVillageManager->IsThereStructure(i, RANKTYPE_SUMMONMARKET))
				{
					clinfo.siStrData[i] = pclstr->clSummonMarketStrInfo.clFee.GetFeeRate()+1;
				}
				else
				{
					clinfo.siStrData[i] = 0;
				}
			}
		}
	}
	// �񺯻� 
	if(pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_SUMMONHEROMARKET)
	{
		bcheckswitch = true;

		clinfo.siVillageDetailInfoType = pclinfo->siVillageDetailInfoType;
		for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
		{
			if(pclVillageManager->pclVillageInfo[i] == NULL)continue;


			cltStrInfo* pclstr = pclSummonHeroMarketManager->GetStrInfo(i);
			if(pclstr)
			{
				// ���°� �����̾�� 
				if(pclVillageManager->IsThereStructure(i, RANKTYPE_SUMMONHEROMARKET))
				{
					clinfo.siStrData[i] = pclstr->clSummonHeroMarketStrInfo.clFee.GetFeeRate()+1;
				}
				else
				{
					clinfo.siStrData[i] = 0;
				}
			}
		}
	}
	// ����
	if(pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_FARM)
	{
		bcheckswitch = true;

		clinfo.siVillageDetailInfoType = pclinfo->siVillageDetailInfoType;
		for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
		{
			if(pclVillageManager->pclVillageInfo[i] == NULL)continue;


			cltStrInfo* pclstr = pclLandManager->GetStrInfo(i);
			if(pclstr)
			{
				// ���°� �����̾�� 
				if(pclVillageManager->IsThereStructure(i, RANKTYPE_LAND))
				{
					clinfo.siStrData[i] = pclstr->clLandStrInfo.clRentContract.siRentFee + 1;
				}
				else
				{
					clinfo.siStrData[i] = 0;
				}
			}
		}
	}
	
	// ���ڽ�
	if(pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_FEAST)
	{
		bcheckswitch = true;

		clinfo.siVillageDetailInfoType = pclinfo->siVillageDetailInfoType;
		for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
		{
			if(pclVillageManager->pclVillageInfo[i] == NULL)continue;


			cltStrInfo* pclstr = pclFeastManager->GetStrInfo(i);
			if(pclstr)
			{
				// ���°� �����̾�� 
				if(pclVillageManager->IsThereStructure(i, RANKTYPE_FEAST))
				{
					clinfo.siStrData[i] = pclstr->clFeastStrInfo.clFeastInfo.siCost + 1;
				}
				else
				{
					clinfo.siStrData[i] = 0;
				}
			}
		}
	}


	// ����
	if(pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_MINE)
	{
		bcheckswitch = true;

		clinfo.siVillageDetailInfoType = pclinfo->siVillageDetailInfoType;
		for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
		{
			if(pclVillageManager->pclVillageInfo[i] == NULL)continue;


			cltStrInfo* pclstr = pclMineManager->GetStrInfo(i);
			if(pclstr)
			{
				// ���°� �����̾�� 
				if(pclVillageManager->IsThereStructure(i, RANKTYPE_MINE))
				{
					clinfo.siStrData[i] = pclstr->clMineStrInfo.clRentContract.siRentFee + 1;
				}
				else
				{
					clinfo.siStrData[i] = 0;
				}
			}
		}
	}
	
	
	// ���� ����
	if(pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_VILLAGEWARRECORD)
	{
		bcheckswitch = true;


		clinfo.siVillageDetailInfoType = pclinfo->siVillageDetailInfoType;
		for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
		{
			if(pclVillageManager->pclVillageInfo[i] == NULL)continue;

			cltStrInfo* pclstr = pclCityHallManager->GetStrInfo(i);
			if(pclstr)
			{				
				clinfo.siVillageWarRecordWinAndLose[0][i] = pclstr->clCityhallStrInfo.siVillaeWarRecordWin;
				clinfo.siVillageWarRecordWinAndLose[1][i] = pclstr->clCityhallStrInfo.siVillaeWarRecordLose;
			}
		}
	}
	// �����ڱ�
	if(pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_VILLAGEMONEY)
	{
		bcheckswitch = true;


		clinfo.siVillageDetailInfoType = pclinfo->siVillageDetailInfoType;
		for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
		{
			if(pclVillageManager->pclVillageInfo[i] == NULL)continue;

			cltStrInfo* pclstr = pclCityHallManager->GetStrInfo(i);
			if(pclstr)
			{
				clinfo.siStrData[i] = (SI32)(pclstr->clCommonInfo.clMoney.itMoney / 1000);
			}
		}
	}
	// �����湮�ڼ�
	if(pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_VISITORNUM)
	{
		bcheckswitch = true;

		clinfo.siVillageDetailInfoType = pclinfo->siVillageDetailInfoType;
		for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
		{
			if(pclVillageManager->pclVillageInfo[i] == NULL)continue;

			clinfo.siStrData[i] = pclVillageManager->pclVillageInfo[i]->GetVisitNum();
		}
	}
	// �������ͱ�
	if(pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_VILLAGEPROFIT)
	{
		bcheckswitch = true;


		clinfo.siVillageDetailInfoType = pclinfo->siVillageDetailInfoType;
		for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
		{
			if(pclVillageManager->pclVillageInfo[i] == NULL)continue;

			cltStrInfo* pclstr = pclCityHallManager->GetStrInfo(i);
			if(pclstr)
			{
				clinfo.siStrData[i] = (GMONEY)pclstr->clCityhallStrInfo.clProfitMoney.itMoney / 1000;
			}
		}
	}
	// �����ֽļ�
	if(pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_VILLAGESTOCK)
	{
		bcheckswitch = true;


		clinfo.siVillageDetailInfoType = pclinfo->siVillageDetailInfoType;
		for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
		{
			if(pclVillageManager->pclVillageInfo[i] == NULL)continue;

			cltStrInfo* pclstr = pclCityHallManager->GetStrInfo(i);
			if(pclstr)
			{
				clinfo.siStrData[i] = (SI32)pclstr->clCityhallStrInfo.siTotalStockAmount;
			}
		}
	}
	// ������ȸ���ึ�� 
	if(pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_GENERALMEETING)
	{
		bcheckswitch = true;

		clinfo.siVillageDetailInfoType = pclinfo->siVillageDetailInfoType;
		for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
		{
			if(pclVillageManager->pclVillageInfo[i] == NULL)continue;
			clinfo.siStrData[i] = pclCityHallManager->IsGeneralMeeting(i); 
		}
	}
	
	// ��û ���� ����( ����, �Ļ�, ���� ��..)
	if(pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_CITYHALLSTATE)
	{
		bcheckswitch = true;

		clinfo.siVillageDetailInfoType = pclinfo->siVillageDetailInfoType;
		for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
		{
			if(pclVillageManager->pclVillageInfo[i] == NULL)continue;
			clinfo.uiCityHallState[i] = pclCityHallManager->GetCityHallState(i);
		}
	}

	// ���� ����
	if(pclinfo->siVillageDetailInfoType == NVILLAGEDETAILINFOTYPE_SCORE)
	{
		bcheckswitch = true;

		clinfo.siVillageDetailInfoType = pclinfo->siVillageDetailInfoType;
		for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
		{
			if(pclVillageManager->pclVillageInfo[i] == NULL)continue;
			clinfo.siTotalVillageScore[i] = pclVillageManager->pclVillageInfo[i]->clVillageVary.siTotalVillageScore;
		}
	}



	if(bcheckswitch)
	{
		// Ŭ���̾�Ʈ�� �޽����� ������. 
		cltMsg clMsg(GAMEMSG_RESPONSE_VILLAGEDETAILINFO, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	}

}
