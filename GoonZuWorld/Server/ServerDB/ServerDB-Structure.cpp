//---------------------------------
// 2003/10/17 ���°�
//---------------------------------

#include "Char\CharManager\CharManager.h"

#include "..\Server\Server.h"


//-----------------------------
// Common
//-----------------------------
#include "..\..\Common\Map\Map.h"
#include "Map\FieldObject\FieldObject.h"

// �ǹ�
#include "..\CommonLogic\Cityhall\Cityhall.h"
#include "..\CommonLogic\Bank\Bank-Manager.h"
#include "..\CommonLogic\Stock\Stock.h"
#include "..\CommonLogic\Market\Market.h"
#include "..\CommonLogic\House\House.h"
#include "..\CommonLogic\Hunt\Hunt.h"
#include "..\CommonLogic\PostOffice\PostOffice.h"
#include "..\CommonLogic\HorseMarket\HorseMarket.h"
#include "..\CommonLogic\RealEstate\RealEstate.h"
#include "..\CommonLogic\SummonMarket\SummonMarket.h"
#include "..\CommonLogic\Land\Land.h"
#include "..\CommonLogic\Feast\Feast.h"
#include "..\CommonLogic\SummonHeroMarket\SummonHeroMarket.h"
#include "..\CommonLogic\Mine\Mine.h"
#include "..\CommonLogic\Guild\Guild.h"


#include "..\../../Server/AuthServer/AuthMsg.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Cityhall.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Structure.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-Item.h"
#include "MsgType-Structure.h"
#include "MsgRval-Define.h"
#include "DevTool/DevServerInfo/DevServerInfo.h"
#include "../../CommonLogic/CommonLogic.h"


#define TUTORIALSTOCKMONEY 5000	//��ī�� ���丮�� ���� �ֽ� ����


void cltServer::DoMsg_DBMSG_RESPONSE_CHANGESTRMONEY(sPacketHeader* pPacket)
{
	sDBResponse_ChangeStrMoney* pclMsg = (sDBResponse_ChangeStrMoney*)pPacket;

	cltStrInfo *pStrInfo = GetStrInfo( pclMsg->siVillageUnique, pclMsg->siStrType );

	// �����̸� �ǹ� �����ڱ� ���� 
	if( pclMsg->siResult == 1 ) 
	{
		if( pStrInfo ) 
		{
			pStrInfo->clCommonInfo.clMoney.Set( &pclMsg->clMoney );
		}

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 11] // ������ �ǹ��� �ǹ��� ���� �ڱ��� ���� ��Ű�ų� ����.
			// param1 == �ǹ� ����.  
			// param2 == �ǹ� ����, 
			// param3 == ���� �ݾ�, 
			// param4 == �ǹ� �����ڱ� 
			cltServer * pclServer = (cltServer*)pclClient;
			pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_STRUCTURE, LOGCOMMAND_INDEX_STRUCTURE_CHANGE_STRUCTURE_MONEY, 
											pclMsg->siReason, NULL, NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
											pclMsg->siStrType, pclMsg->lParam, pclMsg->siChangeMoney, pclMsg->clMoney.itMoney, 0, 
											NULL, NULL);
		}
	}

	switch( pclMsg->siReason )
	{
	case CHANGESTRMONEY_NPCPAY:
		{
			SI32 slot = LOWORD( pclMsg->lParam );
			SI32 npckind = HIWORD( pclMsg->lParam );

			if( pclMsg->siResult == 1 ) {
				// NPC �޿� ���� ���� 			

				// ��� ����� ������ �߰�

				if( pStrInfo ) {

					cltMoney clMoney;
					clMoney.Set( (SI64)(pclMsg->siChangeMoney ) );

					pStrInfo->clCityhallStrInfo.clInOutMoneyInfo.AddInOutMoneyInfo( npckind,
						INOUTCODE_NPCPAY, &pclTime->clDate, &clMoney, &pclMsg->clMoney );

					sDBRequest_CityHallSetInOutMoney sendMsg( pclMsg->siVillageUnique, npckind, 
						INOUTCODE_NPCPAY, &pclTime->clDate, &clMoney, &pclMsg->clMoney );

					pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );

					clMoney.Set( -clMoney.itMoney );
					clCurrencyInfo.clOutputMoney_NPCPayment.Increase( &clMoney );
				}
				

				
			} else {
				// ���� �ڱ� ���� �������

				sDBRequest_HireNPC clMsg( 0, pclMsg->siVillageUnique, slot, 0, 0, 0, &pclTime->clDate  , HIRENPC_HIRENPC );

				pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg );

			}
			
		}
		break;
	case CHANGESTRMONEY_EVENTPAY:
		{
			if( pclMsg->siResult == 1 ) {
				// �̺�Ʈ ��� ���� ���� 			
				// ��� ����� ������ �߰�

				if( pStrInfo ) {

					cltMoney clMoney;
					clMoney.Set( (SI64)(pclMsg->siChangeMoney ) );

					pStrInfo->clCityhallStrInfo.clInOutMoneyInfo.AddInOutMoneyInfo( 0,
						INOUTCODE_EVENTPAY, &pclTime->clDate, &clMoney, &pclMsg->clMoney );

					sDBRequest_CityHallSetInOutMoney sendMsg( pclMsg->siVillageUnique, 0, 
						INOUTCODE_EVENTPAY, &pclTime->clDate, &clMoney, &pclMsg->clMoney );

					pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );
				}
			
			} else {
				// ���� �ڱ� ���� 

			}
		}
		break;


	case CHANGESTRMONEY_VILLAGEMARK:
		{
			if( pclMsg->siResult == 1 ) {
				// ��� ����� ������ �߰�

				if( pStrInfo ) {

					cltMoney clMoney;
					clMoney.Set( (SI64)(pclMsg->siChangeMoney ) );

					pStrInfo->clCityhallStrInfo.clInOutMoneyInfo.AddInOutMoneyInfo( 0,
						INOUTCODE_VILLAGEMARK, &pclTime->clDate, &clMoney, &pclMsg->clMoney );

					sDBRequest_CityHallSetInOutMoney sendMsg( pclMsg->siVillageUnique, 0, 
						INOUTCODE_VILLAGEMARK, &pclTime->clDate, &clMoney, &pclMsg->clMoney );

					pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );
				}
			}
		}
		break;

	case CHANGESTRMONEY_VILLAGEMAP:
		{
			if( pclMsg->siResult == 1 ) {
				// ��� ����� ������ �߰�

				if( pStrInfo ) {

					cltMoney clMoney;
					clMoney.Set( (SI64)(pclMsg->siChangeMoney ) );

					switch(pclMsg->siStrType)
					{
					case RANKTYPE_CITYHALL:
						{
							pStrInfo->clCityhallStrInfo.clInOutMoneyInfo.AddInOutMoneyInfo( 0,
								INOUTCODE_VILLAGEMAP, &pclTime->clDate, &clMoney, &pclMsg->clMoney );

							sDBRequest_CityHallSetInOutMoney sendMsg( pclMsg->siVillageUnique, 0, 
								INOUTCODE_VILLAGEMAP, &pclTime->clDate, &clMoney, &pclMsg->clMoney );

							pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );

						}
						break;
					case RANKTYPE_HUNT:
						{
							// ������ ���� ����� ������ ���� => ������ �ǹ� ���� �ڱ� ������
						}
						break;
					default:
						break;
					}
				}
			}
		}
		break;
	case CHANGESTRMONEY_INSTANCEPROFIT:
		{
			if( pclMsg->siResult == 1 ) {
				// ��� ����� ������ �߰�

				if( pStrInfo ) {

					cltMoney clMoney;
					clMoney.Set( (SI64)(pclMsg->siChangeMoney ) );

					pStrInfo->clCityhallStrInfo.clInOutMoneyInfo.AddInOutMoneyInfo( 0,
						INOUTCODE_INSTANCEPROFIT, &pclTime->clDate, &clMoney, &pclMsg->clMoney );

					sDBRequest_CityHallSetInOutMoney sendMsg( pclMsg->siVillageUnique, 0, 
						INOUTCODE_INSTANCEPROFIT, &pclTime->clDate, &clMoney, &pclMsg->clMoney );

					pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );

	
				}
			}
		}
		break;
	case CHANGESTRMONEY_DESTORYSTR:
		{
			if( pclMsg->siResult == 1 ) {
				// ��� ����� ������ �߰�

				if( pStrInfo ) {

					cltMoney clMoney;
					clMoney.Set( (SI64)(pclMsg->siChangeMoney ) );

					pStrInfo->clCityhallStrInfo.clInOutMoneyInfo.AddInOutMoneyInfo( 0,
						INOUTCODE_DESTROYSTR, &pclTime->clDate, &clMoney, &pclMsg->clMoney );

					sDBRequest_CityHallSetInOutMoney sendMsg( pclMsg->siVillageUnique, 0, 
						INOUTCODE_DESTROYSTR, &pclTime->clDate, &clMoney, &pclMsg->clMoney );

					pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );
				}
			}
		}
		break;
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_SETSTRINFO(sPacketHeader* pPacket)
{
	sDBResponse_SetStrInfo* pclMsg = (sDBResponse_SetStrInfo*)pPacket;

	// ����� Ȯ���Ѵ�. 
	if( pclMsg->siResult == 0 )
	{
		return ;
	}

	switch(pclMsg->clStrInfo.clCommonInfo.siStrType)
	{
	case RANKTYPE_BANK:
		pclBankManager->SetStrInfo(pclMsg->siVillageUnique, &pclMsg->clStrInfo);
		
		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 22] // ���� ����.
			// param1 == Ÿ�� ����� ������,		 
			// param2 == ���� ������, 
			// param3 == �ִ� ������ 
			// param4 == ���´� �ִ� �Ա� ���ɾ�,	 
			// param5 == ���Աݾ�
			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_BANK, LOGCOMMAND_INDEX_BANK_SET_BANK, 
								 0, NULL, NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
								 pclMsg->clStrInfo.clBankStrInfo.clFee.GetFeeRate(),
								 pclMsg->clStrInfo.clBankStrInfo.clFee.GetMinFee(), 
								 pclMsg->clStrInfo.clBankStrInfo.clFee.GetMaxFee(), 
								 pclMsg->clStrInfo.clBankStrInfo.clMaxMoney.itMoney, 
								 pclMsg->clStrInfo.clBankStrInfo.clTotalInputMoney.itMoney, NULL, NULL);
		}
		break;

	case RANKTYPE_STOCK:
		pclStockManager->SetStrInfo(pclMsg->siVillageUnique, &pclMsg->clStrInfo);
		break;

	case RANKTYPE_MARKET:
		pclMarketManager->SetStrInfo(pclMsg->siVillageUnique, &pclMsg->clStrInfo);
		break;

	case RANKTYPE_HUNT:
		pclHuntManager->SetStrInfo(pclMsg->siVillageUnique, &pclMsg->clStrInfo);
		break;

	case RANKTYPE_HOUSE:
		pclHouseManager->SetStrInfo(pclMsg->siVillageUnique, &pclMsg->clStrInfo);
		break;

	case RANKTYPE_CITYHALL:
		pclCityHallManager->SetStrInfo(pclMsg->siVillageUnique, &pclMsg->clStrInfo);
		break;

	case RANKTYPE_POSTOFFICE:
		pclPostOfficeManager->SetStrInfo(pclMsg->siVillageUnique, &pclMsg->clStrInfo);
		break;

	
	case RANKTYPE_HORSEMARKET:
		pclHorseMarketManager->SetStrInfo(pclMsg->siVillageUnique, &pclMsg->clStrInfo );
		break;

	case RANKTYPE_REALESTATEMARKET:
		pclRealEstateMarketManager->SetStrInfo(pclMsg->siVillageUnique, &pclMsg->clStrInfo );
		break;

	case RANKTYPE_SUMMONMARKET:
		pclSummonMarketManager->SetStrInfo(pclMsg->siVillageUnique, &pclMsg->clStrInfo );
		break;

	
	case RANKTYPE_LAND:
		pclLandManager->SetStrInfo(pclMsg->siVillageUnique, &pclMsg->clStrInfo );
		break;
	case RANKTYPE_FEAST:
		pclFeastManager->SetStrInfo(pclMsg->siVillageUnique, &pclMsg->clStrInfo );
		break;

	case RANKTYPE_SUMMONHEROMARKET:
		pclSummonHeroMarketManager->SetStrInfo(pclMsg->siVillageUnique, &pclMsg->clStrInfo );
		break;

	case RANKTYPE_MINE:
		pclMineManager->SetStrInfo(pclMsg->siVillageUnique, &pclMsg->clStrInfo );
		break;
	case RANKTYPE_GUILD:
		pclGuildManager->SetStrInfo(pclMsg->siVillageUnique, &pclMsg->clStrInfo );
		break;

	case RANKTYPE_NEWMARKET:
		pclNewMarketManager->SetStrInfo(pclMsg->siVillageUnique, &pclMsg->clStrInfo );
		break;

	default:
		MsgBox(TEXT("fdsv8dfjfd"), TEXT("fdskf83j:%d"), pclMsg->clStrInfo.clCommonInfo.siStrType);
	}

}

void cltServer::DoMsg_DBMSG_RESPONSE_GETSTRINFO(sPacketHeader* pPacket)
{
	sDBResponse_GetStrInfo* pclMsg = (sDBResponse_GetStrInfo*)pPacket;

	if( pclMsg->siVillageUnique < 0 || pclMsg->siVillageUnique >= MAX_VILLAGE_NUMBER )		return;

	// ����� Ȯ���Ѵ�. 
	if(pclMsg->siResult == 0)
	{
		return ;
	}
	SI32 i;

	switch(pclMsg->clStrInfo.clCommonInfo.siStrType)
	{
	case RANKTYPE_BANK:
		pclBankManager->SetStrInfo(pclMsg->siVillageUnique, &pclMsg->clStrInfo);
		pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("sDBResponse_GetStrInfo : RANKTYPE_BANK"));
		break;

	case RANKTYPE_STOCK:
		pclStockManager->SetStrInfo(pclMsg->siVillageUnique, &pclMsg->clStrInfo);
		pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("sDBResponse_GetStrInfo : RANKTYPE_STOCK"));
		break;

	case RANKTYPE_MARKET:
		pclMarketManager->SetStrInfo(pclMsg->siVillageUnique, &pclMsg->clStrInfo);
		pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("sDBResponse_GetStrInfo : RANKTYPE_MARKET"));
		break;

	case RANKTYPE_HUNT:
		pclHuntManager->SetStrInfo(pclMsg->siVillageUnique, &pclMsg->clStrInfo);
		pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("sDBResponse_GetStrInfo : RANKTYPE_HUNT"));
		break;

	case RANKTYPE_HOUSE:
		pclHouseManager->SetStrInfo(pclMsg->siVillageUnique, &pclMsg->clStrInfo);
		pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("sDBResponse_GetStrInfo : RANKTYPE_HOUSE"));
		break;

	case RANKTYPE_CITYHALL:
		{
			pclCityHallManager->SetStrInfo(pclMsg->siVillageUnique, &pclMsg->clStrInfo);

			//----------------------------------
			// NPC�� ����Ѵ�. 
			//----------------------------------
			for( i = 0; i < MAX_HIRED_NPC_NUM; i++ )
			{
				SI32 kind = pclMsg->clStrInfo.clCityhallStrInfo.clHiredNPC[i].siNPCKind;
				if( kind ) {

					Hire(kind, i, pclMsg->siVillageUnique, true);

					//----------------------------------
					// NPC Pay Manager�� �߰�
					//----------------------------------
					pclHiredNPCPayManager->AddNPC( kind );
				}
			}


			//----------------------------------
			// �̺�Ʈ NPC�� �����.
			//----------------------------------

//			SI32 siCurrentEventNPC = 0;

			for ( i = 0; i <MAX_HIRED_EVENTNPC_NUM; i++ ) {
				SI32 kind = pclMsg->clStrInfo.clCityhallStrInfo.clHiredEventNPC[i].siNPCKind;

				if( kind > 0 )
				{
					if( pclClient->pclKindInfoSet->IsValidKind( kind ) )
					{
						HireEventNPC(kind, pclMsg->siVillageUnique, i, true);
						//----------------------------------
						// NPC Pay Manager�� �߰�
						//----------------------------------
						pclHiredNPCPayManager->AddNPC( kind );
					}
				}
			}
 
			//------------------------------------
			// VillageManager�� �������� ���� ���� 
			//------------------------------------
			//cltDate * CurDate = &pclTime->clDate;
			NDate StandardDate;	// ���� �ð�. ���� 8�÷� ����
			
			StandardDate.SetDate(sTime.wYear,sTime.wMonth,sTime.wDay);

				
			for( i = 0; i < MAX_VILLAGE_NUMBER; ++i )
			{
				if( pclMsg->clStrInfo.clCityhallStrInfo.bDeclareWarVillage[ i ] == 1 ) {

					pclVillageManager->siDeclareWarVillage[ pclMsg->siVillageUnique ] = i;
					
					//pclVillageManager->clDeclareWarDate[ pclMsg->siVillageUnique ].Set( 
					//	&pclMsg->clStrInfo.clCityhallStrInfo.clDeclareWarDate );
					pclVillageManager->clDeclareWarDate[pclMsg->siVillageUnique ].SetDate
						( pclMsg->clStrInfo.clCityhallStrInfo.uiDeclareWarDateYear
						 ,pclMsg->clStrInfo.clCityhallStrInfo.uiDeclareWarDateMonth
						 ,pclMsg->clStrInfo.clCityhallStrInfo.uiDeclareWarDateDay	);


					
					// ���� ���ῡ ���۵Ǵ� �������̶�� siNowWarVillage ������ �߰�
					NDate * DeclareWarDate = &pclVillageManager->clDeclareWarDate[ pclMsg->siVillageUnique ];

					// ������ ���� ��¥�� ���� 8�ø� �������� 3�� ���̾��ٸ� ���������� ����.
					if( DeclareWarDate->GetDateVary() + 2  == StandardDate.GetDateVary() )
					{
						pclVillageManager->siNowWarVillage[pclMsg->siVillageUnique] = pclVillageManager->siDeclareWarVillage[pclMsg->siVillageUnique];
					}
				}
			}
			
			clLastSettedNowVillageWarIinfo.uiYear  = sTime.wYear - 2000;
			clLastSettedNowVillageWarIinfo.uiMonth = sTime.wMonth;
			clLastSettedNowVillageWarIinfo.uiDay   = sTime.wDay;


			{
				cltCityHall *pclCityHall = (cltCityHall *)pclCityHallManager->pclStruct[ pclMsg->siVillageUnique ];
				pclCityHall->clLevelInfo.siVisitorNum = pclMsg->clStrInfo.clCityhallStrInfo.siVisitLevel;
			}
			pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("sDBResponse_GetStrInfo : RANKTYPE_CITYHALL"));
		}
		break;

	case RANKTYPE_POSTOFFICE:
		pclPostOfficeManager->SetStrInfo(pclMsg->siVillageUnique, &pclMsg->clStrInfo);
			pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("sDBResponse_GetStrInfo : RANKTYPE_POSTOFFICE"));
		break;
	

	case RANKTYPE_HORSEMARKET:
		pclHorseMarketManager->SetStrInfo(pclMsg->siVillageUnique, &pclMsg->clStrInfo );
			pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("sDBResponse_GetStrInfo : RANKTYPE_HORSEMARKET"));
		break;

	case RANKTYPE_REALESTATEMARKET:
		pclRealEstateMarketManager->SetStrInfo(pclMsg->siVillageUnique, &pclMsg->clStrInfo );
			pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("sDBResponse_GetStrInfo : RANKTYPE_REALESTATEMARKET"));
		break;

	case RANKTYPE_SUMMONMARKET:
		pclSummonMarketManager->SetStrInfo(pclMsg->siVillageUnique, &pclMsg->clStrInfo );
			pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("sDBResponse_GetStrInfo : RANKTYPE_SUMMONMARKET"));
		break;

	
	case RANKTYPE_LAND:
		pclLandManager->SetStrInfo(pclMsg->siVillageUnique, &pclMsg->clStrInfo );
			pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("sDBResponse_GetStrInfo : RANKTYPE_LAND"));
		break;

	case RANKTYPE_FEAST:
		pclFeastManager->SetStrInfo(pclMsg->siVillageUnique, &pclMsg->clStrInfo );
			pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("sDBResponse_GetStrInfo : RANKTYPE_FEAST"));
		break;

	case RANKTYPE_SUMMONHEROMARKET:
		pclSummonHeroMarketManager->SetStrInfo(pclMsg->siVillageUnique, &pclMsg->clStrInfo );
			pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("sDBResponse_GetStrInfo : RANKTYPE_SUMMONHEROMARKET"));
		break;

	case RANKTYPE_MINE:
		pclMineManager->SetStrInfo(pclMsg->siVillageUnique, &pclMsg->clStrInfo );
			pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("sDBResponse_GetStrInfo : RANKTYPE_MINE"));
		break;
	case RANKTYPE_GUILD:
		pclGuildManager->SetStrInfo(pclMsg->siVillageUnique, &pclMsg->clStrInfo );
			pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("sDBResponse_GetStrInfo : RANKTYPE_GUILD"));
		break;

	case RANKTYPE_NEWMARKET:
		pclNewMarketManager->SetStrInfo(pclMsg->siVillageUnique, &pclMsg->clStrInfo );
			pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("sDBResponse_GetStrInfo : RANKTYPE_NEWMARKET"));
		break;

	default:
		MsgBox(TEXT("fdjfd1"), TEXT("fdskf83j:%d"), pclMsg->clStrInfo.clCommonInfo.siStrType);
	}

}


void cltServer::DoMsg_DBMSG_RESPONSE_SETTAX( sPacketHeader* pPacket )
{

	SI32 id = 0;
	SI32 returnval = 0;

	sDBResponse_SetTax* pclMsg = (sDBResponse_SetTax *)pPacket;

	// ����� Ȯ���Ѵ�. 
	if(pclMsg->siResult == 0)
	{
		return ;
	} else {

		switch( pclMsg->siStrType )
		{
		case RANKTYPE_BANK:
			pclBankManager->SetTax( pclMsg->siVillageUnique, pclMsg->usYear, &pclMsg->clDueTax );
			break;

		case RANKTYPE_STOCK:
			pclStockManager->SetTax( pclMsg->siVillageUnique, pclMsg->usYear, &pclMsg->clDueTax );
			break;

		case RANKTYPE_MARKET:
			pclMarketManager->SetTax( pclMsg->siVillageUnique, pclMsg->usYear, &pclMsg->clDueTax );
			break;

		case RANKTYPE_HUNT:
			pclHuntManager->SetTax( pclMsg->siVillageUnique, pclMsg->usYear, &pclMsg->clDueTax );
			break;

		case RANKTYPE_HOUSE:
			pclHouseManager->SetTax( pclMsg->siVillageUnique, pclMsg->usYear, &pclMsg->clDueTax );
			break;

		case RANKTYPE_CITYHALL:
			pclCityHallManager->SetTax( pclMsg->siVillageUnique, pclMsg->usYear, &pclMsg->clDueTax );
			break;
			
		case RANKTYPE_POSTOFFICE:
			pclPostOfficeManager->SetTax( pclMsg->siVillageUnique, pclMsg->usYear, &pclMsg->clDueTax );
			break;

		
		case RANKTYPE_HORSEMARKET:
			pclHorseMarketManager->SetTax( pclMsg->siVillageUnique, pclMsg->usYear, &pclMsg->clDueTax );
			break;

		case RANKTYPE_REALESTATEMARKET:
			pclRealEstateMarketManager->SetTax( pclMsg->siVillageUnique, pclMsg->usYear, &pclMsg->clDueTax );
			break;

		case RANKTYPE_SUMMONMARKET:
			pclSummonMarketManager->SetTax( pclMsg->siVillageUnique, pclMsg->usYear, &pclMsg->clDueTax );
			break;

		

		case RANKTYPE_LAND:
			pclLandManager->SetTax( pclMsg->siVillageUnique, pclMsg->usYear, &pclMsg->clDueTax );
			break;

		case RANKTYPE_FEAST:
			pclFeastManager->SetTax( pclMsg->siVillageUnique, pclMsg->usYear, &pclMsg->clDueTax );
			break;

		case RANKTYPE_SUMMONHEROMARKET:
			pclSummonHeroMarketManager->SetTax( pclMsg->siVillageUnique, pclMsg->usYear, &pclMsg->clDueTax );
			break;

		case RANKTYPE_MINE:
			pclMineManager->SetTax( pclMsg->siVillageUnique, pclMsg->usYear, &pclMsg->clDueTax );
			break;
		case RANKTYPE_GUILD:
			pclGuildManager->SetTax( pclMsg->siVillageUnique, pclMsg->usYear, &pclMsg->clDueTax );
			break;
		case RANKTYPE_NEWMARKET:
			pclNewMarketManager->SetTax( pclMsg->siVillageUnique, pclMsg->usYear, &pclMsg->clDueTax );
			break;

		default:
			MsgBox(TEXT("fdjfd2"), TEXT("fdskf83j:%d"), pclMsg->siStrType );
		}
	}

	returnval = SRVAL_TAX_SUCCESS_SETTAX;

	id = pclMsg->usCharID;
	if(pclCM->IsValidID(id)== false)
	{
		id = 0;
		return ;
	}

	if(returnval)
	{
		SendServerResponseMsg( RANKTYPE_CITYHALL, returnval,  0, 0, pclCM->CR[id]->GetCharUnique());
	}

}

void cltServer::DoMsg_DBMSG_RESPONSE_PAYTAX( sPacketHeader* pPacket )
{
	SI32 id = 0;
	SI32 receiver = 0;
	SI32 returnval = 0;	
	
	cltMoney clMoney;
	
	sDBResponse_PayTax* pclMsg = (sDBResponse_PayTax *)pPacket;

	cltStrInfo *pclinfo1, *pclinfo2;

	receiver = pclMsg->siStrType;

	id = pclMsg->usCharID;
	if(pclCM->IsValidID(id)== false) {
		id = 0;
		return ;
	}

	// ����� Ȯ���Ѵ�. 
	if(pclMsg->siResult <= 0 )
	{
		if( pclMsg->siResult == -1 ) {
			returnval = SRVAL_TAX_FAIL_PAYTAX_NOTENOUGHMONEY;
		}	
		
	} else {

		pclCM->CR[id]->pclCI->clIP.SetMoney( pclMsg->siPersonMoney );

		pclCM->CR[id]->SetUpdateSwitch(UPDATE_IP, true, 0);

		//-------------------------------------
		// ������� ������ ������. 
		//-------------------------------------
		GMONEY salarymoney = pclMsg->siChiefPay;
		
		// ������� ���� 
		cltRank* pclrank = pclRankManager->GetRank(pclMsg->siStrType, pclMsg->siVillageUnique);
		if(pclrank)
		{
			cltLetterMsg_GetSalary clletter(&pclrank->clRank, salarymoney);
			// ������ DB�� Ŭ���̾�Ʈ���� ������. 
			SendLetterMsg(pclrank->clPerson.GetPersonID(), (cltLetterHeader*)&clletter);
		}

		// ��� ����� ������ �߰��Ѵ�
		cltStrInfo *pclStrInfo = GetStrInfo( pclMsg->siVillageUnique, RANKTYPE_CITYHALL );
		if( pclStrInfo ) {

			clMoney.Set( (SI64)(pclMsg->clPaidTax.itMoney - pclMsg->siChiefPay) );
			
			pclStrInfo->clCityhallStrInfo.clInOutMoneyInfo.AddInOutMoneyInfo( pclMsg->siStrType,
				INOUTCODE_TAX, &pclTime->clDate, &clMoney, &pclMsg->clCityhallMoney );

			sDBRequest_CityHallSetInOutMoney sendMsg( pclMsg->siVillageUnique, pclMsg->siStrType, 
				INOUTCODE_TAX, &pclTime->clDate, &clMoney, &pclMsg->clCityhallMoney );

			pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );

			//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog))
			//{
			//	// TEMP LEEKH --------------------------------------------------------------
			//	// [�α��߰� : Ȳ���� 2007. 10. 18] // ��û �����ڱ� ����� ����.				
			//	// param1 == ����� �ݾ�, param2 == ��ܺ����ڱ�, pszParam1 == �ð�.
			//	TCHAR pszCharParam1[50] = {'\0', };
			//	StringCchPrintf(pszCharParam1, sizeof(pszCharParam1), TEXT("%d-%d-%d, %d:%d"),	
			//																pclTime->clDate.uiYear,
			//																pclTime->clDate.uiMonth,
			//																pclTime->clDate.uiDay,
			//																pclTime->clDate.uiHour,
			//																pclTime->clDate.uiMinute);


			//	cltServer* pclserver = (cltServer*)pclClient;
			//	pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_CITYHALL, LOGCOMMAND_INDEX_CITYHALL_INOUTMONEY, 
			//									0, NULL, NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
			//									clMoney.itMoney, pclMsg->clCityhallMoney.itMoney, 0, 0, 0, 
			//									pszCharParam1, NULL);
			//	// TEMP LEEKH --------------------------------------------------------------
			//}

		}


		switch( pclMsg->siStrType )
		{
		case RANKTYPE_BANK:
			pclBankManager->SetPaidTax( pclMsg->siVillageUnique, pclMsg->usYear, &pclMsg->clPaidTax );
			
			pclinfo1 = pclBankManager->GetStrInfo( pclMsg->siVillageUnique );
			pclinfo2 = pclCityHallManager->GetStrInfo( pclMsg->siVillageUnique );
			
			if( pclinfo1 && pclinfo2 ) {
				pclinfo1->clCommonInfo.clMoney.Set(&pclMsg->clStructureMoney );
				//pclinfo2->clCommonInfo.clMoney.Set(&pclMsg->clCityhallMoney );
				pclinfo2->clCityhallStrInfo.clProfitMoney.Set(&pclMsg->clCityhallMoney );
			}
			break;

		case RANKTYPE_STOCK:
			pclStockManager->SetPaidTax( pclMsg->siVillageUnique, pclMsg->usYear, &pclMsg->clPaidTax );

			pclinfo1 = pclStockManager->GetStrInfo( pclMsg->siVillageUnique );
			pclinfo2 = pclCityHallManager->GetStrInfo( pclMsg->siVillageUnique );
			
			if( pclinfo1 && pclinfo2 ) {
				pclinfo1->clCommonInfo.clMoney.Set(&pclMsg->clStructureMoney );
				//pclinfo2->clCommonInfo.clMoney.Set(&pclMsg->clCityhallMoney );
				pclinfo2->clCityhallStrInfo.clProfitMoney.Set(&pclMsg->clCityhallMoney );
			}
			break;

		case RANKTYPE_MARKET:
			pclMarketManager->SetPaidTax( pclMsg->siVillageUnique, pclMsg->usYear, &pclMsg->clPaidTax );

			pclinfo1 = pclMarketManager->GetStrInfo( pclMsg->siVillageUnique );
			pclinfo2 = pclCityHallManager->GetStrInfo( pclMsg->siVillageUnique );
			
			if( pclinfo1 && pclinfo2 ) {
				pclinfo1->clCommonInfo.clMoney.Set(&pclMsg->clStructureMoney );
				//pclinfo2->clCommonInfo.clMoney.Set(&pclMsg->clCityhallMoney );
				pclinfo2->clCityhallStrInfo.clProfitMoney.Set(&pclMsg->clCityhallMoney );
			}
			break;

		case RANKTYPE_HUNT:
			pclHuntManager->SetPaidTax( pclMsg->siVillageUnique, pclMsg->usYear, &pclMsg->clPaidTax );

			pclinfo1 = pclHuntManager->GetStrInfo( pclMsg->siVillageUnique );
			pclinfo2 = pclCityHallManager->GetStrInfo( pclMsg->siVillageUnique );
			
			if( pclinfo1 && pclinfo2 ) {
				pclinfo1->clCommonInfo.clMoney.Set(&pclMsg->clStructureMoney );
				//pclinfo2->clCommonInfo.clMoney.Set(&pclMsg->clCityhallMoney );
				pclinfo2->clCityhallStrInfo.clProfitMoney.Set(&pclMsg->clCityhallMoney );
			}
			break;


		case RANKTYPE_HOUSE:
			pclHouseManager->SetPaidTax( pclMsg->siVillageUnique, pclMsg->usYear, &pclMsg->clPaidTax );

			pclinfo1 = pclHouseManager->GetStrInfo( pclMsg->siVillageUnique );
			pclinfo2 = pclCityHallManager->GetStrInfo( pclMsg->siVillageUnique );
			
			if( pclinfo1 && pclinfo2 ) {
				pclinfo1->clCommonInfo.clMoney.Set(&pclMsg->clStructureMoney );
				//pclinfo2->clCommonInfo.clMoney.Set(&pclMsg->clCityhallMoney );
				pclinfo2->clCityhallStrInfo.clProfitMoney.Set(&pclMsg->clCityhallMoney );
			}
			break;

		case RANKTYPE_POSTOFFICE:
			pclPostOfficeManager->SetPaidTax( pclMsg->siVillageUnique, pclMsg->usYear, &pclMsg->clPaidTax );

			pclinfo1 = pclPostOfficeManager->GetStrInfo( pclMsg->siVillageUnique );
			pclinfo2 = pclCityHallManager->GetStrInfo( pclMsg->siVillageUnique );
			
			if( pclinfo1 && pclinfo2 ) {
				pclinfo1->clCommonInfo.clMoney.Set(&pclMsg->clStructureMoney );
				//pclinfo2->clCommonInfo.clMoney.Set(&pclMsg->clCityhallMoney );
				pclinfo2->clCityhallStrInfo.clProfitMoney.Set(&pclMsg->clCityhallMoney );
			}
			break;

		
		case RANKTYPE_HORSEMARKET:
			pclHorseMarketManager->SetPaidTax( pclMsg->siVillageUnique, pclMsg->usYear, &pclMsg->clPaidTax );

			pclinfo1 = pclHorseMarketManager->GetStrInfo( pclMsg->siVillageUnique );
			pclinfo2 = pclCityHallManager->GetStrInfo( pclMsg->siVillageUnique );
			
			if( pclinfo1 && pclinfo2 ) {
				pclinfo1->clCommonInfo.clMoney.Set(&pclMsg->clStructureMoney );
				//pclinfo2->clCommonInfo.clMoney.Set(&pclMsg->clCityhallMoney );
				pclinfo2->clCityhallStrInfo.clProfitMoney.Set(&pclMsg->clCityhallMoney );
			}
			break;

		case RANKTYPE_REALESTATEMARKET:
			pclRealEstateMarketManager->SetPaidTax( pclMsg->siVillageUnique, pclMsg->usYear, &pclMsg->clPaidTax );

			pclinfo1 = pclRealEstateMarketManager->GetStrInfo( pclMsg->siVillageUnique );
			pclinfo2 = pclCityHallManager->GetStrInfo( pclMsg->siVillageUnique );
			
			if( pclinfo1 && pclinfo2 ) {
				pclinfo1->clCommonInfo.clMoney.Set(&pclMsg->clStructureMoney );
				//pclinfo2->clCommonInfo.clMoney.Set(&pclMsg->clCityhallMoney );
				pclinfo2->clCityhallStrInfo.clProfitMoney.Set(&pclMsg->clCityhallMoney );
			}
			break;

		case RANKTYPE_SUMMONMARKET:
			pclSummonMarketManager->SetPaidTax( pclMsg->siVillageUnique, pclMsg->usYear, &pclMsg->clPaidTax );

			pclinfo1 = pclSummonMarketManager->GetStrInfo( pclMsg->siVillageUnique );
			pclinfo2 = pclCityHallManager->GetStrInfo( pclMsg->siVillageUnique );
			
			if( pclinfo1 && pclinfo2 ) {
				pclinfo1->clCommonInfo.clMoney.Set(&pclMsg->clStructureMoney );
				//pclinfo2->clCommonInfo.clMoney.Set(&pclMsg->clCityhallMoney );
				pclinfo2->clCityhallStrInfo.clProfitMoney.Set(&pclMsg->clCityhallMoney );
			}
			break;

		
		case RANKTYPE_LAND:
			pclLandManager->SetPaidTax( pclMsg->siVillageUnique, pclMsg->usYear, &pclMsg->clPaidTax );

			pclinfo1 = pclLandManager->GetStrInfo( pclMsg->siVillageUnique );
			pclinfo2 = pclCityHallManager->GetStrInfo( pclMsg->siVillageUnique );
			
			if( pclinfo1 && pclinfo2 ) {
				pclinfo1->clCommonInfo.clMoney.Set(&pclMsg->clStructureMoney );
				//pclinfo2->clCommonInfo.clMoney.Set(&pclMsg->clCityhallMoney );
				pclinfo2->clCityhallStrInfo.clProfitMoney.Set(&pclMsg->clCityhallMoney );
			}
			break;

		case RANKTYPE_FEAST:
			pclFeastManager->SetPaidTax( pclMsg->siVillageUnique, pclMsg->usYear, &pclMsg->clPaidTax );

			pclinfo1 = pclFeastManager->GetStrInfo( pclMsg->siVillageUnique );
			pclinfo2 = pclCityHallManager->GetStrInfo( pclMsg->siVillageUnique );
			
			if( pclinfo1 && pclinfo2 ) {
				pclinfo1->clCommonInfo.clMoney.Set(&pclMsg->clStructureMoney );
				//pclinfo2->clCommonInfo.clMoney.Set(&pclMsg->clCityhallMoney );
				pclinfo2->clCityhallStrInfo.clProfitMoney.Set(&pclMsg->clCityhallMoney );
			}
			break;

		case RANKTYPE_SUMMONHEROMARKET:
			pclSummonHeroMarketManager->SetPaidTax( pclMsg->siVillageUnique, pclMsg->usYear, &pclMsg->clPaidTax );

			pclinfo1 = pclSummonHeroMarketManager->GetStrInfo( pclMsg->siVillageUnique );
			pclinfo2 = pclCityHallManager->GetStrInfo( pclMsg->siVillageUnique );
			
			if( pclinfo1 && pclinfo2 ) {
				pclinfo1->clCommonInfo.clMoney.Set(&pclMsg->clStructureMoney );
				//pclinfo2->clCommonInfo.clMoney.Set(&pclMsg->clCityhallMoney );
				pclinfo2->clCityhallStrInfo.clProfitMoney.Set(&pclMsg->clCityhallMoney );
			}
			break;

		case RANKTYPE_MINE:
			pclMineManager->SetPaidTax( pclMsg->siVillageUnique, pclMsg->usYear, &pclMsg->clPaidTax );

			pclinfo1 = pclMineManager->GetStrInfo( pclMsg->siVillageUnique );
			pclinfo2 = pclCityHallManager->GetStrInfo( pclMsg->siVillageUnique );
			
			if( pclinfo1 && pclinfo2 ) {
				pclinfo1->clCommonInfo.clMoney.Set(&pclMsg->clStructureMoney );
				//pclinfo2->clCommonInfo.clMoney.Set(&pclMsg->clCityhallMoney );
				pclinfo2->clCityhallStrInfo.clProfitMoney.Set(&pclMsg->clCityhallMoney );
			}
			break;
		case RANKTYPE_GUILD:
			pclGuildManager->SetPaidTax( pclMsg->siVillageUnique, pclMsg->usYear, &pclMsg->clPaidTax );

			pclinfo1 = pclGuildManager->GetStrInfo( pclMsg->siVillageUnique );
			pclinfo2 = pclCityHallManager->GetStrInfo( pclMsg->siVillageUnique );

			if( pclinfo1 && pclinfo2 ) {
				pclinfo1->clCommonInfo.clMoney.Set(&pclMsg->clStructureMoney );
				//pclinfo2->clCommonInfo.clMoney.Set(&pclMsg->clCityhallMoney );
				pclinfo2->clCityhallStrInfo.clProfitMoney.Set(&pclMsg->clCityhallMoney );
			}
			break;
		case RANKTYPE_NEWMARKET:
			pclNewMarketManager->SetPaidTax( pclMsg->siVillageUnique, pclMsg->usYear, &pclMsg->clPaidTax );

			pclinfo1 = pclNewMarketManager->GetStrInfo( pclMsg->siVillageUnique );
			pclinfo2 = pclCityHallManager->GetStrInfo( pclMsg->siVillageUnique );

			if( pclinfo1 && pclinfo2 ) {
				pclinfo1->clCommonInfo.clMoney.Set(&pclMsg->clStructureMoney );
				//pclinfo2->clCommonInfo.clMoney.Set(&pclMsg->clCityhallMoney );
				pclinfo2->clCityhallStrInfo.clProfitMoney.Set(&pclMsg->clCityhallMoney );
			}
			break;


		default:
			MsgBox(TEXT("fdjfd3"), TEXT("fdskf83j:%d"), pclMsg->siStrType );
		}

		returnval = SRVAL_TAX_SUCCESS_PAYTAX;
	}

	if( returnval ) {
		SendServerResponseMsg( receiver, returnval,  0, 0, pclCM->CR[id]->GetCharUnique());

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// TEMP LEEKH --------------------------------------------------------------
			// [�α��߰� : Ȳ���� 2007. 10. 11] // ���� ����. 
			// param1 == �ǹ��� Ÿ��, 
			// param2 == �ð� : ��, 
			// pszParam1 == �ð�.
			TCHAR str[50] = {'\0', };
			StringCchPrintf(str, sizeof(str), TEXT("%d-%d-%d, %d : %d"),	
													pclMsg->clDate.uiYear,
													pclMsg->clDate.uiMonth,
													pclMsg->clDate.uiDay,
													pclMsg->clDate.uiHour,
													pclMsg->clDate.uiMinute);


			cltServer * pclServer = (cltServer*)pclClient;
			pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_TAX, LOGCOMMAND_INDEX_TAX_PAY, 
											0, (cltCharServer*)pclCM->CR[id], NULL, 0, pclMsg->clPaidTax.itMoney, pclMsg->siPersonMoney, 
											NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
											pclMsg->siStrType, pclMsg->usYear, 0, 0, 0, str, NULL);
			// TEMP LEEKH --------------------------------------------------------------
		}

	}


}

void cltServer::DoMsg_DBMSG_RESPONSE_PAYDIVIDEND( sPacketHeader* pPacket )
{
	
	//SI32 id = 0;
	//SI32 receiver = 0;
	//SI32 returnval = 0;	
	//
	//sDBResponse_PayDividend* pclMsg = (sDBResponse_PayDividend *)pPacket;

	//id = pclMsg->usCharID;
	//if(pclCM->IsValidID(id)== false) {
	//	id = 0;
	//	return ;
	//}

	//// ����� Ȯ���Ѵ�. 
	//if(pclMsg->siResult <= 0 )
	//{
	//	switch( pclMsg->siResult )
	//	{
	//	case -1:
	//		returnval = SRVAL_DIVIDEND_FAIL_NOTENOUGHMONEY;
	//		break;

	//	case -2:
	//		returnval = SRVAL_DIVIDEND_FAIL_WRONGMONEY;
	//		break;
	//	}
	//	
	//} else {

	//	pclCM->CR[id]->pclCI->clIP.SetMoney( pclMsg->siPersonMoney );

	//	pclCM->CR[id]->SetUpdateSwitch(UPDATE_IP, true, 0);

	//	cltStrInfo *pclStrInfo = GetStrInfo( pclMsg->siVillageUnique, RANKTYPE_CITYHALL );

	//	// ��� ����� ������ �߰��Ѵ�

	//	if( pclStrInfo ) {

	//		//pclStrInfo->clCommonInfo.clMoney.Set( &pclMsg->clCityhallMoney );	// ����� ��� �����ڱ� 
	//		pclStrInfo->clCityhallStrInfo.clProfitMoney.Set( &pclMsg->clCityhallMoney ); // ����� ��� �����ڱ� 

	//		pclStrInfo->clCityhallStrInfo.clDividendInfo.AddDividendInfo( &pclMsg->clDate, pclMsg->siTotalStock, &pclMsg->clDividendPrice );


	//		cltMoney clMoney;

	//		clMoney.Set( -(SI64)(pclMsg->clDividendPrice.itMoney * pclMsg->siTotalStock) );

	//		pclStrInfo->clCityhallStrInfo.clInOutMoneyInfo.AddInOutMoneyInfo( RANKTYPE_CITYHALL,
	//			INOUTCODE_DIVIDEND, &pclTime->clDate, &clMoney, &pclMsg->clCityhallMoney );

	//		sDBRequest_CityHallSetInOutMoney sendMsg( pclMsg->siVillageUnique, RANKTYPE_CITYHALL, 
	//			INOUTCODE_DIVIDEND, &pclTime->clDate, &clMoney, &pclMsg->clCityhallMoney );

	//		pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );
	//	}
	//	
	//	cltStrInfo *pclParentStrInfo = GetStrInfo( pclMsg->siParentVillage, RANKTYPE_CITYHALL );

	//	if( pclParentStrInfo ) {
	//		//pclParentStrInfo->clCommonInfo.clMoney.Set( &pclMsg->clParentCityhallMoney );		// ����� �θ� ���� ��� �����ڱ� 
	//		pclParentStrInfo->clCityhallStrInfo.clProfitMoney.Set( &pclMsg->clParentCityhallMoney );		// ����� �θ� ���� ��� �����ڱ� 
	//	}

	//	// ��� ����� ����(��������)
	//	{
	//		if( pclParentStrInfo ) {

	//			cltMoney clMoney;
	//			clMoney.Set( -(SI64)(pclMsg->siParentPay ) );

	//			pclStrInfo->clCityhallStrInfo.clInOutMoneyInfo.AddInOutMoneyInfo( pclMsg->siParentVillage,
	//				INOUTCODE_TOPARENT, &pclTime->clDate, &clMoney, &pclMsg->clCityhallMoney );

	//			sDBRequest_CityHallSetInOutMoney sendMsg( pclMsg->siVillageUnique, pclMsg->siParentVillage, 
	//				INOUTCODE_TOPARENT, &pclTime->clDate, &clMoney, &pclMsg->clCityhallMoney );

	//			pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );
	//			
	//		}
	//	}

	//	// ��� ����� ����(��������)
	//	{
	//		if( pclParentStrInfo ) {

	//			cltMoney clMoney;
	//			clMoney.Set( (SI64)(pclMsg->siParentPay ) );

	//			pclParentStrInfo->clCityhallStrInfo.clInOutMoneyInfo.AddInOutMoneyInfo( pclMsg->siVillageUnique,
	//				INOUTCODE_FROMCHILD, &pclTime->clDate, &clMoney, &pclMsg->clParentCityhallMoney );

	//			sDBRequest_CityHallSetInOutMoney sendMsg( pclMsg->siParentVillage, pclMsg->siVillageUnique, 
	//				INOUTCODE_FROMCHILD, &pclTime->clDate, &clMoney, &pclMsg->clParentCityhallMoney );

	//			pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );
	//		}
	//	}

	//	// ��������� ���� 
	//	cltRank* pclrank = pclRankManager->GetRank(RANKTYPE_CITYHALL, pclMsg->siVillageUnique);
	//	if(pclrank)
	//	{
	//		cltLetterMsg_GetSalary clletter(&pclrank->clRank, pclMsg->siChiefPay);
	//		// ������ DB�� Ŭ���̾�Ʈ���� ������. 
	//		SendLetterMsg(pclrank->clPerson.GetPersonID(), (cltLetterHeader*)&clletter);
	//	}
	//	
	//	// ���ֿ��� ���� 
	//	if( pclMsg->siKingPersonID )
	//	{
	//		cltLetterMsg_GetKingPay clletter( pclMsg->siVillageUnique, pclMsg->siKingPay, pclMsg->siKingPayPersent );

	//		// ������ DB�� Ŭ���̾�Ʈ���� ������. 
	//		SendLetterMsg( pclMsg->siKingPersonID, (cltLetterHeader*)&clletter);
	//	}
	//	

	//	// ��� ���� ����� �����ο��� ������ ������. 
	//	for(SI32 i = 0;i < pclMsg->usPersonCount;i++)
	//	{
	//		cltLetterMsg_GetDividend clletter(pclMsg->siVillageUnique, (SI32)(pclMsg->clDividendPerson[i].clMoney.itMoney * pclMsg->clDividendPrice.itMoney));
	//		// ������ DB�� Ŭ���̾�Ʈ���� ������. 
	//		SendLetterMsg(pclMsg->clDividendPerson[i].siPersonID, (cltLetterHeader*)&clletter);
	//	}


	//	returnval = SRVAL_DIVIDEND_SUCCESS_PAYDIVIDEND;
	//}

	//if( returnval ) {
	//	SendServerResponseMsg( RANKTYPE_CITYHALL, returnval,  0, 0, pclCM->CR[id]->GetCharUnique());
	//}

}

void cltServer::DoMsg_DBMSG_RESPONSE_AUTOPAYDIVIDEND( sPacketHeader* pPacket )
{
	sDBResponse_AutoPayDividend* pclMsg = (sDBResponse_AutoPayDividend*)pPacket;

	if( pclMsg == NULL )
		return;

	if( pclMsg->siResult != 1 )
		return;

	cltStrInfo *pclStrInfo = GetStrInfo( pclMsg->siVillageUnique, RANKTYPE_CITYHALL );

	// ��� ����� ������ �߰��Ѵ�
	if( pclStrInfo )
	{	
		// [����] �ʺ��� ���� : �ʺ��� ������ �ڵ����� ���ֹ���� ���� �ʴ´�.
		if( pclClient->IsCountrySwitch(Switch_TutorialVillage) )
		{
			if ( pclMsg->siVillageUnique == Const_Beginner_Village )
			{
				return;
			}
		}

		pclStrInfo->clCityhallStrInfo.clProfitMoney.Set( &pclMsg->clCityhallMoney ); // ����� ��� �����ڱ� 
		pclStrInfo->clCityhallStrInfo.clDividendInfo.AddDividendInfo( &pclMsg->clDate, pclMsg->siTotalStock, &pclMsg->clStockDividendPrice );

		cltMoney clMoney;
		clMoney.Set( -(SI64)(pclMsg->clStockDividendPrice.itMoney * pclMsg->siTotalStock) );

		pclStrInfo->clCityhallStrInfo.clInOutMoneyInfo.AddInOutMoneyInfo( RANKTYPE_CITYHALL,
			INOUTCODE_DIVIDEND, &pclTime->clDate, &clMoney, &pclMsg->clCityhallMoney );

		sDBRequest_CityHallSetInOutMoney sendMsg( pclMsg->siVillageUnique, RANKTYPE_CITYHALL, 
			INOUTCODE_DIVIDEND, &pclTime->clDate, &clMoney, &pclMsg->clCityhallMoney );

		pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );

		//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		//{
		//	// TEMP LEEKH --------------------------------------------------------------
		//	// [�α��߰� : Ȳ���� 2007. 10. 18] // ��û �����ڱ� ����� ����.				
		//	// param1 == ����� �ݾ�, param2 == ��ܺ����ڱ�, pszParam1 == �ð�.
		//	TCHAR pszCharParam1[50] = {'\0', };
		//	StringCchPrintf(pszCharParam1, sizeof(pszCharParam1), TEXT("%d-%d-%d, %d:%d"),	
		//																pclTime->clDate.uiYear,
		//																pclTime->clDate.uiMonth,
		//																pclTime->clDate.uiDay,
		//																pclTime->clDate.uiHour,
		//																pclTime->clDate.uiMinute);

		//	
		//	cltServer* pclserver = (cltServer*)pclClient;
		//	pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_CITYHALL, LOGCOMMAND_INDEX_CITYHALL_INOUTMONEY, 
		//									0, NULL, NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
		//									clMoney.itMoney, pclMsg->clCityhallMoney.itMoney, 0, 0, 0, 
		//									pszCharParam1, NULL);
		//}
		// �ֹ� ������� ������ ���
		clMoney.Set( -(SI64)(pclMsg->clResidentDividendPrice.itMoney * pclStrInfo->clCityhallStrInfo.siResidentNum) );

		pclStrInfo->clCityhallStrInfo.clInOutMoneyInfo.AddInOutMoneyInfo( RANKTYPE_CITYHALL,
			INOUTCODE_RESIDENTSHARE, &pclTime->clDate, &clMoney, &pclMsg->clCityhallMoney );

		sDBRequest_CityHallSetInOutMoney sendMsg2( pclMsg->siVillageUnique, RANKTYPE_CITYHALL, 
			INOUTCODE_RESIDENTSHARE, &pclTime->clDate, &clMoney, &pclMsg->clCityhallMoney );

		pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg2 );

		//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		//{
		//	// TEMP LEEKH --------------------------------------------------------------
		//	// [�α��߰� : Ȳ���� 2007. 9. 20] // ��û �����ڱ� ����� ����.				
		//	// param1 == ����� �ݾ�, param2 == ��ܺ����ڱ�, pszParam1 == �ð�.

		//	TCHAR pszCharParam1[50] = {'\0', };
		//	StringCchPrintf(pszCharParam1, sizeof(pszCharParam1), TEXT("%d-%d-%d, %d:%d"),	
		//																pclTime->clDate.uiYear,
		//																pclTime->clDate.uiMonth,
		//																pclTime->clDate.uiDay,
		//																pclTime->clDate.uiHour,
		//																pclTime->clDate.uiMinute);


		//	cltServer* pclserver = (cltServer*)pclClient;
		//	pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_CITYHALL, LOGCOMMAND_INDEX_CITYHALL_INOUTMONEY, 
		//									0, NULL, NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
		//									clMoney.itMoney, pclMsg->clCityhallMoney.itMoney, 0, 0, 0, 
		//									pszCharParam1, NULL);
		//	// TEMP LEEKH --------------------------------------------------------------
		//}

		/*/--------------------------------------------------------------------------------//
		�ֹ� ���� ���� �� �α� ��� 2007.09.05
		//--------------------------------------------------------------------------------/*/
		SI32 villageuniaue	= pclMsg->siVillageUnique;					// ���޴� ���� ����ũ
		SI32 totalstock		= pclMsg->siTotalStock;						// �ѹ�� �ֽļ�.
		GMONEY totalmoney	= pclMsg->clResidentDividendPrice.itMoney;	// �ֹ� �Ѹ� �� ������
		SendLog_WriteLogToDB(LOGCOMMAND_TYPE_STOCK,LOGCOMMAND_INDEX_STOCKRESIDENSHARE,0,NULL,NULL,0,
							 0, 0, NULL, 0, 0, 0, villageuniaue, 0, 0,
							 totalmoney, totalstock, pclMsg->usResidentPersonCount, 0, 0, 
							 NULL, NULL);
		//----------------------------------------------------------------------------------//
		
		// �սǼ������� ����
		clMoney.Set( -(SI64)pclMsg->clTaxDividendPrice.itMoney  );

		pclStrInfo->clCityhallStrInfo.clInOutMoneyInfo.AddInOutMoneyInfo( RANKTYPE_CITYHALL,
			INOUTCODE_NATIONTAX, &pclTime->clDate, &clMoney, &pclMsg->clCityhallMoney );

		sDBRequest_CityHallSetInOutMoney sendMsg3( pclMsg->siVillageUnique, RANKTYPE_CITYHALL, 
			INOUTCODE_NATIONTAX, &pclTime->clDate, &clMoney, &pclMsg->clCityhallMoney );

		pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg3 );

		//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		//{
		//	// TEMP LEEKH --------------------------------------------------------------
		//	// [�α��߰� : Ȳ���� 2007. 9. 20] // ��û �����ڱ� ����� ����.				
		//	// param1 == ����� �ݾ�, param2 == ��ܺ����ڱ�, pszParam1 == �ð�.
		//	TCHAR pszCharParam1[50] = {'\0', };
		//	StringCchPrintf(pszCharParam1, sizeof(pszCharParam1), TEXT("%d-%d-%d, %d:%d"),	
		//																pclTime->clDate.uiYear,
		//																pclTime->clDate.uiMonth,
		//																pclTime->clDate.uiDay,
		//																pclTime->clDate.uiHour,
		//																pclTime->clDate.uiMinute);


		//	cltServer* pclserver = (cltServer*)pclClient;
		//	pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_CITYHALL, LOGCOMMAND_INDEX_CITYHALL_INOUTMONEY, 
		//									0, NULL, NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
		//									clMoney.itMoney, pclMsg->clCityhallMoney.itMoney, 0, 0, 0, 
		//									pszCharParam1, NULL);
		//	// TEMP LEEKH --------------------------------------------------------------
		//}
	}

	// ��������� ���� 
	cltRank* pclrank = pclRankManager->GetRank(RANKTYPE_CITYHALL, pclMsg->siVillageUnique);
	if(pclrank)
	{
		cltLetterMsg_GetSalary clletter(&pclrank->clRank, pclMsg->siChiefPay);
		// ������ DB�� Ŭ���̾�Ʈ���� ������. 
		SendLetterMsg(pclrank->clPerson.GetPersonID(), (cltLetterHeader*)&clletter);

		//KHY - 0730 - ��� ���� ������ ���� �� �ݾ��� ������Ʈ �����ش�.
		//pclCM->CR[pclrank->clPerson.GetPersonID()]->pclCI->clBank.SetMoney( pclMsg->siPersonMoney );
		//pclCM->CR[pclrank->clPerson.GetPersonID()]->SetUpdateSwitch(UPDATE_BANK, true, 0);

		SI32 siRankID = pclCM->GetIDFromPersonID(pclrank->clPerson.GetPersonID());
		if(pclCM->IsValidID(siRankID))
		{
			pclCM->CR[siRankID]->pclCI->clBank.SetMoney( pclMsg->siPersonMoney );
			pclCM->CR[siRankID]->SetUpdateSwitch(UPDATE_BANK, true, 0);			
		}
	}

	// ���ֿ��� ���� 
	if( pclMsg->siKingPersonID )
	{
		cltLetterMsg_GetKingPay clletter( pclMsg->siVillageUnique, pclMsg->siKingPay, pclMsg->siKingPayPersent );

		// ������ DB�� Ŭ���̾�Ʈ���� ������. 
		SendLetterMsg( pclMsg->siKingPersonID, (cltLetterHeader*)&clletter);

		//KHY - 0730 - ��� ���� ������ ���� �� �ݾ��� ������Ʈ �����ش�.
		//pclCM->CR[ pclMsg->siKingPersonID]->pclCI->clBank.SetMoney(  pclMsg->clKingAllMoney );
		//pclCM->CR[ pclMsg->siKingPersonID]->SetUpdateSwitch(UPDATE_BANK, true, 0);			

		SI32 siKingID = pclCM->GetIDFromPersonID( pclMsg->siKingPersonID );
		if(pclCM->IsValidID(siKingID))
		{
			pclCM->CR[siKingID]->pclCI->clBank.SetMoney( pclMsg->clKingAllMoney );
			pclCM->CR[siKingID]->SetUpdateSwitch(UPDATE_BANK, true, 0);			
		}
	}

	if( pclMsg->usStockPersonCount > MAX_DIVIDEND_PERSON )		pclMsg->usStockPersonCount = MAX_DIVIDEND_PERSON;
	SI32 i;
	// (����)��� ���� ����� �����ο��� ������ ������. 
	for( i = 0;i < pclMsg->usStockPersonCount; ++i)
	{
		if (pclMsg->clStockDividendPerson[i].siPersonID > 0 &&  pclMsg->clStockDividendPerson[i].clMoney.itMoney > 0)
		{
			cltLetterMsg_GetDividend clletter(pclMsg->siVillageUnique, pclMsg->clStockDividendPerson[i].clMoney.itMoney, 0);
			// ������ DB�� Ŭ���̾�Ʈ���� ������. 
			SendLetterMsg(pclMsg->clStockDividendPerson[i].siPersonID, (cltLetterHeader*)&clletter);

			//KHY - 0730 - ��� ���� ������ ���� �� �ݾ��� ������Ʈ �����ش�.
			//pclCM->CR[pclMsg->clStockDividendPerson[i].siPersonID]->pclCI->clBank.SetMoney(  pclMsg->clStockDividendPerson[i].clAllMoney.itMoney );
			//pclCM->CR[pclMsg->clStockDividendPerson[i].siPersonID]->SetUpdateSwitch(UPDATE_BANK, true, 0);			

			SI32 siStockDividendID = pclCM->GetIDFromPersonID( pclMsg->clStockDividendPerson[i].siPersonID );
			if(pclCM->IsValidID(siStockDividendID))
			{
				pclCM->CR[siStockDividendID]->pclCI->clBank.SetMoney( pclMsg->clStockDividendPerson[i].clAllMoney.itMoney );
				pclCM->CR[siStockDividendID]->SetUpdateSwitch(UPDATE_BANK, true, 0);			

				if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
				{
					// [�α��߰� : Ȳ���� 2007. 10. 11] // �ֽ� ����
					cltServer * pclServer = (cltServer*)pclClient;
					pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_CITYHALL, LOGCOMMAND_INDEX_CITYHALL_DIVIDENDRESIDENTS, 
													0, NULL, NULL, pclMsg->clStockDividendPerson[i].siPersonID, 
													pclMsg->clStockDividendPerson[i].clMoney.itMoney, 
													pclMsg->clStockDividendPerson[i].clAllMoney.itMoney, NULL, 0, NULL, 0, pclMsg->siVillageUnique, 0, 0, 
													0, 0, 0, 0, 0, NULL, NULL);
				}
			}
		}
	}

	if( pclMsg->usResidentPersonCount > MAX_DIVIDEND_PERSON )		pclMsg->usResidentPersonCount = MAX_DIVIDEND_PERSON;
	// (�ֹ�)��� ���� ����� �����ο��� ������ ������. 
	for( i = 0;i < pclMsg->usResidentPersonCount; ++i)
	{
		if (pclMsg->clResidentDividendPerson[i].siPersonID > 0 && pclMsg->clResidentDividendPerson[i].clMoney.itMoney > 0)
		{
			cltLetterMsg_GetDividend clletter(pclMsg->siVillageUnique, pclMsg->clResidentDividendPerson[i].clMoney.itMoney, 1);
			// ������ DB�� Ŭ���̾�Ʈ���� ������. 
			SendLetterMsg(pclMsg->clResidentDividendPerson[i].siPersonID, (cltLetterHeader*)&clletter);

			//KHY - 0730 - ��� ���� ������ ���� �� �ݾ��� ������Ʈ �����ش�.
			//pclCM->CR[pclMsg->clStockDividendPerson[i].siPersonID]->pclCI->clBank.SetMoney(  pclMsg->clStockDividendPerson[i].clAllMoney.itMoney );
			//pclCM->CR[pclMsg->clStockDividendPerson[i].siPersonID]->SetUpdateSwitch(UPDATE_BANK, true, 0);			

			SI32 siStockDividendID = pclCM->GetIDFromPersonID( pclMsg->clStockDividendPerson[i].siPersonID );
			if(pclCM->IsValidID(siStockDividendID))
			{
				pclCM->CR[siStockDividendID]->pclCI->clBank.SetMoney( pclMsg->clStockDividendPerson[i].clAllMoney.itMoney );
				pclCM->CR[siStockDividendID]->SetUpdateSwitch(UPDATE_BANK, true, 0);			
			}
		}
	}

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// TEMP LEEKH --------------------------------------------------------------
		// [�α��߰� : Ȳ���� 2007. 10. 18] // �ڵ� ����ϱ�	(�����ʿ� : ������ �� �� ������.)		
		// param1	 == ���ִ� ����, 
		// param2	 == �ֹ� �Ѹ�� ������ �ݾ�, 
		// param3	 == �ս� �������� ������ �ݾ�,
		// pszParam1 == �ֱ� �����.
		TCHAR pszCharParam1[50] = {'\0', };
		StringCchPrintf(pszCharParam1, sizeof(pszCharParam1), TEXT("%d-%d-%d, %d:%d"),	
																	pclTime->clDate.uiYear,
																	pclTime->clDate.uiMonth,
																	pclTime->clDate.uiDay,
																	pclTime->clDate.uiHour,
																	pclTime->clDate.uiMinute);


		cltServer* pclserver = (cltServer*)pclClient;
		pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_CITYHALL, LOGCOMMAND_INDEX_CITYHALL_DIVIDENDSUMMARY, 
										0, NULL, NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
										pclMsg->clStockDividendPrice.itMoney, 
										pclMsg->clResidentDividendPrice.itMoney, 
										pclMsg->clTaxDividendPrice.itMoney, 
										0, 0, 
										pszCharParam1, NULL);
		// TEMP LEEKH --------------------------------------------------------------
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_PAYFEE( sPacketHeader* pPacket )
{
	sDBResponse_PayFee *pclMsg = (sDBResponse_PayFee *)pPacket;

	cltStrInfo *pclinfo;

	// ����� Ȯ���Ѵ�. 
	if(pclMsg->siResult <= 0 )
	{

	} else {
		
		pclinfo = GetStrInfo( pclMsg->siVillageUnique, pclMsg->siStrType );

		if( pclinfo ) {
			
			// �ǹ� �����ڱ� ����
			pclinfo->clCommonInfo.clMoney.Set( &pclMsg->clStructureMoney );

			SI32 id	= pclMsg->usCharID;

			if( pclCM->IsValidID(id) == TRUE ) {

				if( pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID ) {

					// ������ ���� ���� ����
					pclCM->CR[id]->pclCI->clBank.SetMoney( pclMsg->clPersonMoney.itMoney );

					// Ŭ���̾�Ʈ���� �˷��ش�. 
					pclCM->CR[id]->SetUpdateSwitch(UPDATE_BANK, true, 0);

				}

			}

		}

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 11] // ������ �ǹ��� ������ ���θ� ��û.
			// param1 == �ǹ��� Ÿ��.  
			// param2 == ������ Ÿ��, 
			// param4 == �ǹ��� �����ڱ�
			cltServer * pclServer = (cltServer*)pclClient;
			pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_STRUCTURE, LOGCOMMAND_INDEX_STRUCTURE_PAY_FEE, 
											0, NULL, NULL, pclMsg->siPersonID, pclMsg->clFeeMoney.itMoney, pclMsg->clPersonMoney.itMoney, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
											pclMsg->siStrType, pclMsg->siFeeType, 0, pclMsg->clStructureMoney.itMoney, 0, 
											NULL, NULL);
		}

	}

}


void cltServer::DoMsg_DBMSG_RESPONSE_CHIEFINFO(sPacketHeader* pPacket)
{
	sDBResponse_ChiefInfo *pclMsg = (sDBResponse_ChiefInfo *)pPacket;

	if( pclMsg->siResult != 1 )						return;

	// ���� �׾������� ó���Ѵ�.
	SI32 id	= pclMsg->usCharID;

	if(pclCM->IsValidID(id) == TRUE && pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID)
	{
		// Ŭ���̾�Ʈ�� ������ ������. 
		cltGameMsgResponse_ChiefInfo clInfo(&pclMsg->Rank, pclMsg->AccountID);
		cltMsg clMsg(GAMEMSG_RESPONSE_CHIEFINFO, sizeof(clInfo), (BYTE*)&clInfo);
		
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	}

	return;
}

// kkm
void cltServer::DoMsg_DBMSG_RESPONSE_REPAIRSTRUCTURE(sPacketHeader* pPacket)
{
	sDBResponse_RepairStructure *pclMsg = (sDBResponse_RepairStructure *)pPacket;

	SI32 id = pclMsg->usCharID;

	if(pclCM->IsValidID(id) == FALSE)
		return;

	switch( pclMsg->siResult )
	{
	case 1:
		{

			cltStrInfo *pclStrInfo = GetStrInfo( pclMsg->siVillageUnique, pclMsg->siRankType );

			if( pclStrInfo )
			{
				pclStrInfo->clCommonInfo.siRepairStrDura = pclMsg->siUpdateStrRepairAmount;
				pclStrInfo->clCommonInfo.clBaseMoney.itMoney = pclMsg->siLeftBaseMoney;
			}

			cltGameMsgResponse_RepairStructure sendMsg( pclMsg->siRankType, pclMsg->siUpdateStrRepairAmount, pclMsg->siLeftBaseMoney );
			cltMsg clMsg( GAMEMSG_RESPONSE_REPAIRSTRUCTURE, sizeof( sendMsg ), (BYTE*)&sendMsg );
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		
			if(0 != pclMsg->siItemUnique)
			{
				// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
				cltGameMsgResponse_PersonItemInfo clinfo( pclMsg->siItemPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clItem, 0 );
				cltMsg clMsg2(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
				pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg2);
			}
			
			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			{
				// [�α��߰� : Ȳ���� 2007. 10. 11] // �ǹ� ����. 
				// param1 == �ǹ� ����. 
				// param2 == �����ҷ��� ��û�ϴ� ��. 
				// param3 == �����а� �� �ڿ� ������(������ �ְ� 1000)
				// param4 == �����ϰ� ������ �ǹ� �ں���
				cltServer * pclServer = (cltServer*)pclClient;
				pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_STRUCTURE, LOGCOMMAND_INDEX_STRUCTURE_REPAIR, 
												0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
												pclMsg->siRankType, pclMsg->siStrRepairAmount, pclMsg->siUpdateStrRepairAmount, pclMsg->siLeftBaseMoney, 0, NULL, NULL);
			}

		}
		break;

	}
}
/*
void cltServer::DoMsg_DBMSG_RESPONSE_REPAIRSTRUCTURE(sPacketHeader* pPacket)
{
	sDBResponse_RepairStructure *pclMsg = (sDBResponse_RepairStructure *)pPacket;
	
	SI32 id = pclMsg->usCharID;
	
	if(pclCM->IsValidID(id) == FALSE) return;

	switch( pclMsg->siResult ) {
	case 1:
		{

			cltStrInfo *pclStrInfo = GetStrInfo( pclMsg->siVillageUnique, pclMsg->siRankType );

			if( pclStrInfo ) {
				pclStrInfo->clCommonInfo.siUseItemNum = pclMsg->siUseItemNum;
			}

			// �κ��丮 ����
//			if( pclCM->IsValidID(id) ) //&& pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID )
//			{

			if ( pclMsg->siItemNum < 0 || pclMsg->siItemNum > MAX_ITEM_PILE_NUMBER )
			{
				return;
			}

			if ( pclMsg->siItemNum == 0 )
			{
				pclCM->CR[id]->pclCI->clCharItem.clItem[ pclMsg->siItemInventoryIndex ].Init();
			}
			else
			{
				if ( pclCM->CR[id]->pclCI->clCharItem.clItem[ pclMsg->siItemInventoryIndex ].siUnique != pclMsg->siItemUnique )
				{
					return;
				}

				pclCM->CR[id]->pclCI->clCharItem.clItem[ pclMsg->siItemInventoryIndex ].siUnique = pclMsg->siItemUnique;
				pclCM->CR[id]->pclCI->clCharItem.clItem[ pclMsg->siItemInventoryIndex ].siItemNum = pclMsg->siItemNum;
			}

			pclCM->CR[id]->SetUpdateSwitch( UPDATE_INVENTORY, true , 0);

			cltGameMsgResponse_RepairStructure sendMsg( pclMsg->siRankType, pclMsg->siUseItemNum );
			cltMsg clMsg( GAMEMSG_RESPONSE_REPAIRSTRUCTURE, sizeof( sendMsg ), (BYTE*)&sendMsg );
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		}
		break;

	}

}
*/

void cltServer::DoMsg_DBMSG_RESPONSE_SETSTRREPAIRITEM(sPacketHeader* pPacket)
{
	sDBResponse_SetStrRepairItem *pclMsg = (sDBResponse_SetStrRepairItem *)pPacket;

	cltStrInfo *pclStrInfo = GetStrInfo( pclMsg->siVillageUnique, pclMsg->siRankType );

	if( pclStrInfo ) {
		pclStrInfo->clCommonInfo.siNeedItemUnique = pclMsg->siItemUnique;
		pclStrInfo->clCommonInfo.siNeedItemNum = pclMsg->siItemNum;
		pclStrInfo->clCommonInfo.siUseItemNum = 0;
	}

}

void cltServer::DoMsg_DBMSG_RESPONSE_SETSTRDURA(sPacketHeader* pPacket)
{
	sDBResponse_SetStrDura *pclMsg = (sDBResponse_SetStrDura *)pPacket;
	
	cltStrInfo *pclStrInfo = GetStrInfo( pclMsg->siVillageUnique, pclMsg->siRankType );

	if( pclStrInfo ) {
		pclStrInfo->clCommonInfo.siStrDura = pclMsg->siStrDura;
	}
	
	
	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [�α��߰� : Ȳ���� 2007. 10. 11] // �ǹ��� ������.
		// param1 == �ǹ� ����. 
		// param2 == ������.
		cltServer * pclServer = (cltServer*)pclClient;
		pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_STRUCTURE, LOGCOMMAND_INDEX_STRUCTURE_SET_STRDUR, 
										0, NULL, NULL, NULL, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
										pclMsg->siRankType, pclMsg->siStrDura, 0, 0, 0, NULL, NULL);
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_CHANGESTRDURA(sPacketHeader* pPacket)
{
	sDBResponse_ChangeStrDura *pclMsg = (sDBResponse_ChangeStrDura *)pPacket;

	if( pclMsg->siVillageUnique < 0 || pclMsg->siVillageUnique >= MAX_VILLAGE_NUMBER )		return;

	cltStrInfo *pclStrInfo = GetStrInfo( pclMsg->siVillageUnique, pclMsg->siRankType );

	if( pclStrInfo ) {
		pclStrInfo->clCommonInfo.siStrDura = pclMsg->siStrDura;
	}
	else return ;

	//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	//{
	//	// [�α��߰� : Ȳ���� 2007. 10. 11] // �ǹ��� ������ �������� �ǹ���ü .
	//	// param1 == �ǹ� ����. param2 == ������.
	//	cltServer * pclServer = (cltServer*)pclClient;
	//	pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_STRUCTURE, LOGCOMMAND_INDEX_STRUCTURE_CHANGE_STRDUR, 
	//									0, NULL, NULL, NULL, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
	//									pclMsg->siRankType, pclMsg->siStrDura, 0, 0, 0, NULL, NULL);
	//}

	// �������� 0 �����̸� �ǹ���ü
	if( pclMsg->siStrDura <= 0 ) {

		SI32 strunique = pclVillageStructureSet->GetStrUniqueFromRankType( pclMsg->siRankType );
		if( strunique == 0 ) return;

		cltVillageInfo *pclVillageInfo = pclVillageManager->pclVillageInfo[ pclMsg->siVillageUnique ];
		if( pclVillageInfo == NULL ) return;

		// ��ü������ �ǹ��ΰ�..
		int ref = pclVillageStructureSet->FindRefFromRankType( pclMsg->siRankType );
		if( ref == -1 ) return;
		// ������ ������ �ִ°�?
		if( pclVillageInfo->clVillageVary.clStructureInfo.IsThereStructure(pclMsg->siRankType) == FALSE ) return;

		// ��ü �Ұ����� �ǹ���..
		if( pclVillageStructureSet->pclVillageStructureInfo[ ref ]->bDestroyable == FALSE )
		{

			// ���� 0���� ���� 
			{
				sDBRequest_SetStrDura sendMsg( pclMsg->siVillageUnique, pclMsg->siRankType, 0 );
				pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );
			}

			// ���� �ڱ� �谨
			{
				cltStrInfo *pclStrInfo = GetStrInfo( pclMsg->siVillageUnique, RANKTYPE_CITYHALL );
				if ( pclStrInfo == NULL ) return ;

				SI32 money = (SI32)(pclStrInfo->clCommonInfo.clMoney.itMoney * 0.5);

				if( money > 0 ) {
					sDBRequest_ChangeStrMoney sendMsg( CHANGESTRMONEY_DESTORYSTR, 0, pclMsg->siVillageUnique,
													   RANKTYPE_CITYHALL, -money );
					pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );

				}
			}

		}
		else // ��ü ������ �ǹ���
		{
			SI32 slot = pclVillageInfo->clVillageVary.clStructureInfo.GetSlotFromStrUnique( strunique );
			if( slot == -1 ) return;


			SI32 sidatevary = pclTime->clDate.GetDateVary();
			sDBRequest_DestroyStructure sendMsg( 0, pclMsg->siVillageUnique, slot, strunique, pclMsg->siRankType, sidatevary );
			pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );

		}
	}

}

void cltServer::DoMsg_DBMSG_RESPONSE_CHANGESTRBASEMONEY(sPacketHeader* pPacket)
{
	sDBResponse_ChangeStrBaseMoney *pclMsg = (sDBResponse_ChangeStrBaseMoney *)pPacket;

	if( pclMsg->siResult != 1 )
		return;

	if( pclMsg->siVillageUnique <= 0 || pclMsg->siVillageUnique >= MAX_VILLAGE_NUMBER )
		return;

	SI32 tempVillageUnique = pclMsg->siVillageUnique;

	// ��û �ں����� ������
	cltMoney clMoney;
	clMoney.itMoney = -pclMsg->siChangeMoney;

	cltStrInfo* pclinfo = pclCityHallManager->GetStrInfo( tempVillageUnique );

	pclinfo->clCommonInfo.clMoney.Set( &pclMsg->clCityhallMoney );

	// ��� �ֱ� ������ ���� 
	pclinfo->clCityhallStrInfo.clInOutMoneyInfo.AddInOutMoneyInfo( RANKTYPE_CITYHALL,
		INOUTCODE_SETBASEMONEY, &pclTime->clDate, &clMoney, &pclMsg->clCityhallMoney );

	sDBRequest_CityHallSetInOutMoney sendMsg( tempVillageUnique, RANKTYPE_CITYHALL, 
		INOUTCODE_SETBASEMONEY, &pclTime->clDate, &clMoney, &pclMsg->clCityhallMoney );

	pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );

	clMoney;
	clMoney.Set(&pclMsg->clBaseMoney);

	SI32 tempStrType = pclMsg->siStrType;
	if( RANKTYPE_CITYHALL == tempStrType)
	{
		pclCityHallManager->SetBaseMoney( tempVillageUnique, &clMoney );
	}
	if( RANKTYPE_BANK ==  tempStrType)
	{
		pclBankManager->SetBaseMoney( tempVillageUnique, &clMoney );
	}
	else if( RANKTYPE_STOCK == tempStrType )
	{
		pclStockManager->SetBaseMoney( tempVillageUnique, &clMoney );
	}
	else if( RANKTYPE_MARKET == tempStrType )
	{
		pclMarketManager->SetBaseMoney( tempVillageUnique, &clMoney );
	}
	else if( RANKTYPE_HOUSE == tempStrType )
	{
		pclHouseManager->SetBaseMoney( tempVillageUnique, &clMoney );
	}
	else if( RANKTYPE_POSTOFFICE == tempStrType )
	{
		pclPostOfficeManager->SetBaseMoney( tempVillageUnique, &clMoney );
	}
	else if( RANKTYPE_HORSEMARKET == tempStrType )
	{
		pclHorseMarketManager->SetBaseMoney( tempVillageUnique, &clMoney );
	}
	else if( RANKTYPE_REALESTATEMARKET == tempStrType )
	{
		pclRealEstateMarketManager->SetBaseMoney( tempVillageUnique, &clMoney );
	}
	else if( RANKTYPE_SUMMONMARKET == tempStrType )
	{
		pclSummonMarketManager->SetBaseMoney( tempVillageUnique, &clMoney );
	}
	else if( RANKTYPE_LAND == tempStrType )
	{
		pclLandManager->SetBaseMoney( tempVillageUnique, &clMoney );
	}
	else if( RANKTYPE_FEAST == tempStrType )
	{
		pclFeastManager->SetBaseMoney( tempVillageUnique, &clMoney );
	}
	else if( RANKTYPE_SUMMONHEROMARKET == tempStrType )
	{
		pclSummonHeroMarketManager->SetBaseMoney( tempVillageUnique, &clMoney );
	}
	else if( RANKTYPE_MINE == tempStrType )
	{
		pclMineManager->SetBaseMoney( tempVillageUnique, &clMoney );
	}
	else if( RANKTYPE_HUNT == tempStrType )
	{
		pclHuntManager->SetBaseMoney( tempVillageUnique, &clMoney );
	}
	else if ( RANKTYPE_GUILD == tempStrType )
	{
		pclGuildManager->SetBaseMoney(tempVillageUnique,&clMoney);
	}
	else if ( RANKTYPE_NEWMARKET == tempStrType )
	{
		pclNewMarketManager->SetBaseMoney(tempVillageUnique,&clMoney);
	}

	SI32 id = pclMsg->siCharID;
	if( pclCM->IsValidID(id) )
	{
		// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
		SendServerResponseMsg(RANKTYPE_CITYHALL, SRVAL_CITYHALL_SUCCESS_SETBASEMONEY,  0, 0, pclCM->CR[id]->GetCharUnique());
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_SETSTRREPAIRAMOUNT(sPacketHeader* pPacket)
{
	sDBResponse_SetStrRepairAmount *pclMsg = (sDBResponse_SetStrRepairAmount *)pPacket;

	cltStrInfo *pclStrInfo = GetStrInfo( pclMsg->siVillageUnique, pclMsg->siRankType );

	if( pclStrInfo ) 
	{
		pclStrInfo->clCommonInfo.siRepairStrDura = 0;
	}

	
	//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	//{
	//	// [�α��߰� : Ȳ���� 2007. 10. 11] // �ǹ��� �������� ��û.
	//	// param1 == �ǹ� ����.
	//	cltServer * pclServer = (cltServer*)pclClient;
	//	pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_STRUCTURE, LOGCOMMAND_INDEX_STRUCTURE_SET_REPAIR_AMOUNT, 
	//									0, NULL, NULL, NULL, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
	//									pclMsg->siRankType, 0, 0, 0, 0, NULL, NULL);
	//}
}

void cltServer::DoMsg_DBMSG_RESPONSE_CONTRIBUTION_ITEM_LIST_INPUT(sPacketHeader* pPacket)
{
	sDBResponse_Contribution_Item_List_Input* pclMsg = (sDBResponse_Contribution_Item_List_Input*)pPacket;

	cltCharServer* pclchar = pclCM->GetCharServer( pclMsg->m_usCharID );
	if( NULL == pclchar )	return;

	cltItem clUseItem;
	SI32	siInvenPos = -1;
	for( SI32 siCount = 0; CONTRIBUTION_ITEM_NUM > siCount; ++siCount )
	{
		if( 0 < pclMsg->m_siInputItemIvenPos[siCount] ) 
		{
			siInvenPos = pclchar->pclCI->clCharItem.GetItemPos( pclMsg->m_siItemUnique[siCount] );
			if( pclMsg->m_siInputItemIvenPos[siCount] != siInvenPos ) continue;

			clUseItem.Set( &pclchar->pclCI->clCharItem.clItem[siInvenPos] );
			clUseItem.siItemNum = pclMsg->m_siInputItemNum[siCount];

			sDBRequest_UseItem useitem(	pclchar->GetID(),
										pclchar->pclCI->GetPersonID(),
										siInvenPos,
										&clUseItem, 
										USEITEM_REASON_CONTRIBUTION_ITEM_INPUT	);

			pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&useitem);
		}
	}

	cltGameMsgResponse_Contribution_Item_List_Input clinfo( pclMsg->m_siItemUnique, pclMsg->m_siItemNum );
	cltMsg clMsg( GAMEMSG_RESPONSE_CONTRIBUTION_ITEM_LIST_INPUT, PACKET(clinfo) );
	pclchar->SendNetMsg((sPacketHeader*)&clMsg);
}

void cltServer::DoMsg_DBMSG_RESPONSE_CONTRIBUTION_MAKE_NPC(sPacketHeader* pPacket)
{
	sDBResponse_Contribution_Make_NPC* pclMsg = (sDBResponse_Contribution_Make_NPC*)pPacket;

	if( 1 != pclMsg->m_siResult )	return;

	cltCharServer* pclchar = pclCM->GetCharServer( pclMsg->m_usCharID );
	if( NULL == pclchar )	return;

	// npc ������ 1���̴�.
	cltStrInfo* pclinfo = pclCityHallManager->GetStrInfo( pclMsg->m_siVillageUnique );
	if( pclinfo == NULL )	return;

	// ������� NPC�� ������ NPC�� ã�´�.
	cltContributionInfo* pclContributionInfo = NULL;
	for( SI32 siCount = 0; siCount < MAX_HIRED_EVENTNPC_NUM; siCount++ )
	{
		if( pclinfo->clCityhallStrInfo.clHiredEventNPC[siCount].siNPCKind == pclMsg->m_siNPCKind ) 
		{
			pclContributionInfo = m_clContributionEvent_Common.FindContributionInfo( pclMsg->m_siNPCKind );
			if( NULL == pclContributionInfo ) return;

			// NPC �ذ�
			sDBRequest_HireNPC clFireMsg(	pclMsg->m_usCharID, 
											pclMsg->m_siVillageUnique, 
											siCount, 
											0, 
											0, 
											0, 
											&pclTime->clDate, 
											HIRENPC_HIREEVENTNPC );
			pclGameDBProcess->SendMsg( (sPacketHeader *)&clFireMsg );

			// NPC ���
			sDBRequest_HireNPC clHireMsg(	pclMsg->m_usCharID, 
											pclMsg->m_siVillageUnique, 
											siCount, 
											pclContributionInfo->m_siMakeNPCKind, 
											0, 
											0, 
											&pclTime->clDate, 
											HIRENPC_HIREEVENTNPC );
			pclGameDBProcess->SendMsg( (sPacketHeader *)&clHireMsg );

			break;
		}
	}

	if( false == m_clContributionEvent_Common.CompleteMakeNpc( pclMsg->m_siNPCKind, pclchar ) )
		return;

	// ���๰ �ϼ� ����.
	cltGameMsgResponse_Event_CompleteBuild clComplete( pclMsg->m_siVillageUnique, 0, pclContributionInfo->m_siMakeNPCKind );
	cltMsg clCompleteMsg( GAMEMSG_RESPONSE_EVENT_COMPLETEBUILD, sizeof( clComplete ), (BYTE*)&clComplete );
	pclCM->SendAllPersonMsg( (sPacketHeader*)&clCompleteMsg );
}
