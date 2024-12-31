#include "..\Common\CommonHeader.h"
#include "DevTool/DevServerInfo/DevServerInfo.h"
#include "../../CommonLogic/CommonLogic.h"
#include "..\Server\Server.h"
#include "..\CommonLogic\Msg\MsgType-Hunt.h"
#include "..\CommonLogic\MsgType-Person.h"
#include "..\CommonLogic\MsgRval-Define.h"

#include "Char\CharManager\CharManager.h"

#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Hunt.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Person.h"


void cltServer::DoMsg_DBMSG_RESPONSE_HUNTMONSTERFIELDLISTADD(sPacketHeader* pPacket)
{
	sDBResponse_HuntMonsterFieldListAdd * pclMsg = (sDBResponse_HuntMonsterFieldListAdd *)pPacket;
	
	if ( pclMsg->siResult != 1 )
	{
		return;
	}

	SI32 id = pclMsg->siCharID;

	if ( pclMsg->siPersonID < 1 || pclMsg->siCharID < 1 )
	{
		return;
	}

	if ( pclMsg->siAddListIndex < 0 || pclMsg->siAddListIndex >= MAX_HUNT_LINEUP_NUMBER )
	{
		return;
	}

	cltStrInfo *pclStrInfo = pclHuntManager->GetStrInfo( pclMsg->siVillageUnique );

	if ( pclStrInfo == NULL )
	{
		return;
	}

	if( pclMsg->siAddListIndex < 0 || pclMsg->siAddListIndex >= MAX_HUNT_LINEUP_NUMBER )		return;

	pclStrInfo->clHuntStrInfo.clHuntLineUp[pclMsg->siAddListIndex].siLineUpKind = pclMsg->siMonsterKind;
	pclStrInfo->clHuntStrInfo.clHuntLineUp[pclMsg->siAddListIndex].siLineUpKindNum = pclMsg->siMonsterNum;
	pclStrInfo->clHuntStrInfo.clHuntLineUp[pclMsg->siAddListIndex].siLineUpKindLevel = pclMsg->siMonsterLevel;

	if ( pclCM->IsValidID(id) && pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID)
	{
		cltGameMsgResponse_HuntMonsterFieldListAdd clinfo(
			pclMsg->siVillageUnique,
			pclMsg->siAddListIndex,
			pclMsg->siMonsterKind,
			pclMsg->siMonsterNum,
			pclMsg->siMonsterLevel
			);
		cltMsg clMsg(GAMEMSG_RESPONSE_HUNTMONSTERFIELDLISTADD, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 15] // �����忡 ���� ������ �������� �Է��Ѵ�. ( ����Ʈ�� �߰� )
			// param1 == ����Ʈ ��ȣ,	
			// param2 == ���� ����, 
			// param3 == ���� ����,	
			// param4 == ���� ����.
			cltServer* pclserver = (cltServer*)pclClient;
			pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_HUNT, LOGCOMMAND_INDEX_HUNT_MONSTERADD,
											0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
											pclMsg->siAddListIndex,
											pclMsg->siMonsterKind,
											pclMsg->siMonsterNum,
											pclMsg->siMonsterLevel, 0,  NULL, NULL);
		}
	}
	
	return;
}

void cltServer::DoMsg_DBMSG_RESPONSE_HUNTMONSTERFIELDLISTDEL(sPacketHeader* pPacket)
{
	sDBResponse_HuntMonsterFieldListDel * pclMsg = (sDBResponse_HuntMonsterFieldListDel *)pPacket;

	if ( pclMsg->siResult != 1 )
	{
		return;
	}

	SI32 id = pclMsg->siCharID;

	if ( pclMsg->siVillageUnique < 1 )
	{
		return;
	}
	
	if ( pclMsg->siDelListIndex < 0 || pclMsg->siDelListIndex >= MAX_HUNT_LINEUP_NUMBER )
	{
		return;
	}

	cltStrInfo *pclStrInfo = pclHuntManager->GetStrInfo( pclMsg->siVillageUnique );

	if ( pclStrInfo == NULL )
	{
		return;
	}

	if( pclMsg->siDelListIndex < 0 || pclMsg->siDelListIndex >= MAX_HUNT_LINEUP_NUMBER )		return;

	pclStrInfo->clHuntStrInfo.clHuntLineUp[ pclMsg->siDelListIndex ].siLineUpKind = 0;
	pclStrInfo->clHuntStrInfo.clHuntLineUp[ pclMsg->siDelListIndex ].siLineUpKindNum = 0;
	pclStrInfo->clHuntStrInfo.clHuntLineUp[ pclMsg->siDelListIndex ].siLineUpKindLevel = 0;

	if ( pclMsg->siPersonID < 1 || pclMsg->siCharID < 1 )
	{
		return;
	}

	if ( pclCM->IsValidID(id) && pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID)
	{
		cltGameMsgResponse_HuntMonsterFieldListDel clinfo( pclMsg->siVillageUnique, pclMsg->siDelListIndex );
		cltMsg clMsg(GAMEMSG_RESPONSE_HUNTMONSTERFIELDLISTDEL, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 10] // �����忡 �־��� ������ �������� ����Ʈ���� �����Ѵ�. ( ����Ʈ���� ���� )
			// param1 == ���� ����Ʈ �ε���. 
			cltServer* pclserver = (cltServer*)pclClient;
			pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_HUNT, LOGCOMMAND_INDEX_HUNT_MONSTERDEL,
											0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
											pclMsg->siDelListIndex, 0, 0, 0, 0, NULL, NULL);
		}
	}
	
	return;
}

void cltServer::DoMsg_DBMSG_RESPONSE_HUNTSTORAGEMONSTERIN(sPacketHeader* pPacket)
{
	sDBResponse_HuntStorageMonsterIn* pclMsg = (sDBResponse_HuntStorageMonsterIn*)pPacket;

	if ( pclMsg->siResult != 1 )
	{
		return;
	}

	SI32 id = pclMsg->siCharID;

	if ( pclMsg->siPersonID < 1 || pclMsg->siCharID < 1 )
	{
		return;
	}

	if ( pclMsg->siVillageUnique < 1 )
	{
		return;
	}

	cltStrInfo *pclStrInfo = pclHuntManager->GetStrInfo( pclMsg->siVillageUnique );

	if ( pclStrInfo == NULL )
	{
		return;
	}

	if ( pclMsg->siFromPersonInventoryItemIndex < PERSONITEM_INV0 || pclMsg->siFromPersonInventoryItemIndex >= MAX_ITEM_PER_PERSON )
	{
		pclLog->FilePrint( TEXT("HuntError.txt"), TEXT("1 InventoryItem Index = %d"), pclMsg->siFromPersonInventoryItemIndex );
		return;
	}

	if ( pclMsg->siToHuntStorageInventoryItemIndex < 0 || pclMsg->siToHuntStorageInventoryItemIndex >= MAX_HUNT_STG_NUMBER )
	{
		pclLog->FilePrint( TEXT("HuntError.txt"), TEXT("2 Hunt Storage Item Index = %d"), pclMsg->siToHuntStorageInventoryItemIndex );
		return;
	}

	if ( pclMsg->siToHuntStorageInventoryItemNum < 1 || pclMsg->siToHuntStorageInventoryItemNum > MAX_ITEM_PILE_NUMBER )
	{
		return;
	}
	
	pclStrInfo->clHuntStrInfo.clHuntStg[ pclMsg->siToHuntStorageInventoryItemIndex ].siItemUnique = pclMsg->siToHuntStorageInventoryItemUnique;
	pclStrInfo->clHuntStrInfo.clHuntStg[ pclMsg->siToHuntStorageInventoryItemIndex ].siItemNum = pclMsg->siToHuntStorageInventoryItemNum;

	if ( pclCM->IsValidID(id) && pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID)
	{
		if ( pclMsg->siFromPersonInventoryItemNum < 0 || pclMsg->siFromPersonInventoryItemNum > MAX_ITEM_PILE_NUMBER )
		{
			return;
		}

		if ( pclMsg->siFromPersonInventoryItemNum == 0 )
		{
			pclCM->CR[id]->pclCI->clCharItem.clItem[ pclMsg->siFromPersonInventoryItemIndex ].Init();
		}
		else
		{
			if ( pclCM->CR[id]->pclCI->clCharItem.clItem[ pclMsg->siFromPersonInventoryItemIndex ].siUnique != pclMsg->siFromPersonInventoryItemUnique )
			{
				pclLog->FilePrint( TEXT("HuntError.txt"), TEXT("3 Item Unique Wrong = %d, %d"), pclCM->CR[id]->pclCI->clCharItem.clItem[ pclMsg->siFromPersonInventoryItemIndex ].siUnique, pclMsg->siFromPersonInventoryItemUnique );
			}

			pclCM->CR[id]->pclCI->clCharItem.clItem[ pclMsg->siFromPersonInventoryItemIndex ].siUnique = pclMsg->siFromPersonInventoryItemUnique;
			pclCM->CR[id]->pclCI->clCharItem.clItem[ pclMsg->siFromPersonInventoryItemIndex ].siItemNum = pclMsg->siFromPersonInventoryItemNum;
		}

		cltGameMsgResponse_HuntMonsterIn clinfo(
			pclMsg->siVillageUnique,
			&pclCM->CR[id]->pclCI->clCharItem.clItem[ pclMsg->siFromPersonInventoryItemIndex ],
			pclMsg->siFromPersonInventoryItemIndex,
			pclMsg->siToHuntStorageInventoryItemIndex,
			pclMsg->siToHuntStorageInventoryItemUnique,
			pclMsg->siToHuntStorageInventoryItemNum
			);
		cltMsg clMsg(GAMEMSG_RESPONSE_HUNTMONSTERIN, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);


		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 10] // ������ â�� ������ �ִ´�.
			// param1 == �κ��丮 �ε���, 
			// param2 == ������ �ε���, 
			// param3 == ������ ����ũ, 
			// param4 == �����忡 �ִ� ������ ����. 
			cltServer* pclserver = (cltServer*)pclClient;
			pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_HUNT, LOGCOMMAND_INDEX_HUNT_STGINPUT,
											0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, &clinfo.clItem, 0, 0, 0, clinfo.siVillageUnique, 0, 0, 
											clinfo.siUserInventoryIndex, clinfo.siHuntStorageItemIndex, clinfo.siHuntStorageItemUnique, clinfo.siHuntStorageItemNum, 0, NULL, NULL);
		}
	}	
	
	return;
}

void cltServer::DoMsg_DBMSG_RESPONSE_HUNTSTORAGEMONSTEROUT(sPacketHeader* pPacket)
{
	sDBResponse_HuntStorageMonsterOut* pclMsg = (sDBResponse_HuntStorageMonsterOut*)pPacket;

	if ( pclMsg->siResult != 1 )
	{
		return;
	}

	SI32 id = pclMsg->siCharID;

	if ( pclMsg->siPersonID < 1 || pclMsg->siCharID < 1 )
	{
		return;
	}

	if ( pclMsg->siVillageUnique < 1 )
	{
		return;
	}

	cltStrInfo *pclStrInfo = pclHuntManager->GetStrInfo( pclMsg->siVillageUnique );

	if ( pclStrInfo == NULL )
	{
		return;
	}

	if ( pclMsg->siFromHuntStorageInventoryItemIndex < 0 || pclMsg->siFromHuntStorageInventoryItemIndex >= MAX_HUNT_STG_NUMBER )
	{
		pclLog->FilePrint( TEXT("HuntError.txt"), TEXT("4 Hunt Storage Item Index = %d"), pclMsg->siFromHuntStorageInventoryItemIndex );
		return;
	}

	if ( pclMsg->siToPersonInventoryItemIndex < PERSONITEM_INV0 || pclMsg->siToPersonInventoryItemIndex >= MAX_ITEM_PER_PERSON )
	{
		pclLog->FilePrint( TEXT("HuntError.txt"), TEXT("5 InventoryItem Index = %d"), pclMsg->siToPersonInventoryItemIndex );
		return;
	}

	if ( pclMsg->siFromHuntStorageInventoryItemNum < 0 || pclMsg->siFromHuntStorageInventoryItemNum > MAX_ITEM_PILE_NUMBER )
	{
		return;
	}	

	SI32 Ref = 0;
	Ref = pclItemManager->FindItemRefFromUnique( pclMsg->siToPersonInventoryItemUnique );
	if ( Ref <= 0 )
	{
		return;
	}

	SI32 MonKind = pclItemManager->pclItemInfo[Ref]->siMakeKind;

	if ( MonKind < 1 )
	{
		return;
	}


	/*
	for ( int i =0; i < MAX_HUNT_LINEUP_NUMBER; ++i )
	{
		if ( 
			pclStrInfo->clHuntStrInfo.clHuntLineUp[ i ].siLineUpKind == MonKind &&
			pclMsg->siFromHuntStorageInventoryItemNum < pclStrInfo->clHuntStrInfo.clHuntLineUp[ i ].siLineUpKindNum
			)
		{
			sDBRequest_HuntMonsterFieldListDel clMsg( 
				pclMsg->siPersonID, 
				pclMsg->siCharID, 
				pclMsg->siVillageUnique,
				i
				);
			pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

			break;
		}
	}
	*/
	

	if ( pclMsg->siFromHuntStorageInventoryItemNum == 0 )	
	{
		pclStrInfo->clHuntStrInfo.clHuntStg[ pclMsg->siFromHuntStorageInventoryItemIndex ].siItemUnique = 0;
		pclStrInfo->clHuntStrInfo.clHuntStg[ pclMsg->siFromHuntStorageInventoryItemIndex ].siItemNum = 0;
	}
	else
	{
		pclStrInfo->clHuntStrInfo.clHuntStg[ pclMsg->siFromHuntStorageInventoryItemIndex ].siItemUnique = pclMsg->siFromHuntStorageInventoryItemUnique;
		pclStrInfo->clHuntStrInfo.clHuntStg[ pclMsg->siFromHuntStorageInventoryItemIndex ].siItemNum = pclMsg->siFromHuntStorageInventoryItemNum;
	}

	if ( pclCM->IsValidID(id) && pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID )
	{
		if ( pclMsg->siToPersonInventoryItemNum < 1 || pclMsg->siToPersonInventoryItemNum > MAX_ITEM_PILE_NUMBER )
		{
			return;
		}

		
		if ( pclCM->CR[id]->pclCI->clCharItem.clItem[ pclMsg->siToPersonInventoryItemIndex ].siUnique > 0 && pclCM->CR[id]->pclCI->clCharItem.clItem[ pclMsg->siToPersonInventoryItemIndex ].siUnique != pclMsg->siToPersonInventoryItemUnique )
		{
			pclLog->FilePrint( TEXT("HuntError.txt"), TEXT("6 Item Unique Wrong = %d, %d"), pclCM->CR[id]->pclCI->clCharItem.clItem[ pclMsg->siToPersonInventoryItemIndex ].siUnique, pclMsg->siToPersonInventoryItemUnique );
		}

		pclCM->CR[id]->pclCI->clCharItem.clItem[ pclMsg->siToPersonInventoryItemIndex ].siUnique = pclMsg->siToPersonInventoryItemUnique;
		pclCM->CR[id]->pclCI->clCharItem.clItem[ pclMsg->siToPersonInventoryItemIndex ].siItemNum = pclMsg->siToPersonInventoryItemNum;

		cltGameMsgResponse_HuntMonsterOut clinfo(
			pclMsg->siVillageUnique,
			&pclCM->CR[id]->pclCI->clCharItem.clItem[ pclMsg->siToPersonInventoryItemIndex ],
			pclMsg->siToPersonInventoryItemIndex,
			pclMsg->siFromHuntStorageInventoryItemIndex,
			pclMsg->siFromHuntStorageInventoryItemUnique,
			pclMsg->siFromHuntStorageInventoryItemNum
			);
		cltMsg clMsg(GAMEMSG_RESPONSE_HUNTMONSTEROUT, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 15] // ������ â�� �� �ִ� ������ ������.
			// param1 == ���� �κ��丮 ��ȣ,		
			// param2 == ������ �κ� ������ ��ȣ, 
			// param3 == ������ �κ� ������ ����ũ, 
			// param4 == ������ �κ� ������ ����.
			cltServer* pclserver = (cltServer*)pclClient;
			pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_HUNT, LOGCOMMAND_INDEX_HUNT_STGOUTPUT,
											0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, &pclCM->CR[id]->pclCI->clCharItem.clItem[ pclMsg->siToPersonInventoryItemIndex ], 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
											pclMsg->siToPersonInventoryItemIndex,
											pclMsg->siFromHuntStorageInventoryItemIndex,
											pclMsg->siFromHuntStorageInventoryItemUnique,
											pclMsg->siFromHuntStorageInventoryItemNum, 0,  NULL, NULL);
		}
	}
	
	return;
}

void cltServer::DoMsg_DBMSG_RESPONSE_HUNTSTORAGEDECREASEDOLLITEMNUM(sPacketHeader* pPacket)
{
	sDBResponse_HuntStorageDecreaseDollItemNum *pclMsg = (sDBResponse_HuntStorageDecreaseDollItemNum*)pPacket;

	if ( pclMsg->siResult != 1 )
	{
		return;
	}

	if ( pclMsg->siVillageUnique < 1 )
	{
		return;
	}

	cltStrInfo *pclStrInfo = pclHuntManager->GetStrInfo( pclMsg->siVillageUnique );

	if ( pclStrInfo == NULL )
	{
		return;
	}

	for ( SI16 i = 0; i < MAX_HUNT_LINEUP_NUMBER; ++i )
	{
		SI16 siStorageItemIndex = pclMsg->siHuntStorageItemIndex[ i ];
		
		if ( siStorageItemIndex < 0 || siStorageItemIndex >= MAX_HUNT_STG_NUMBER )
		{
			continue;
		}

		if ( pclStrInfo->clHuntStrInfo.clHuntLineUp[ i ].siLineUpKindNum > pclMsg->siHuntStorageItemNum[ i ] )
		{
			pclStrInfo->clHuntStrInfo.clHuntStg[ siStorageItemIndex ].siItemUnique = pclMsg->siHuntStorageItemUnique[ i ];
			pclStrInfo->clHuntStrInfo.clHuntStg[ siStorageItemIndex ].siItemNum = pclMsg->siHuntStorageItemNum[ i ];
			
			/* // ���Ͱ� �����ص� LineUp ����Ʈ������ ������ ����� �ؼ�...
			sDBRequest_HuntMonsterFieldListDel clMsg( 
				0, 
				0, 
				pclMsg->siVillageUnique,
				i
				);
			pclGameDBProcess->SendMsg( ( sPacketHeader * ) &clMsg );
			*/
		}
		else if( pclMsg->siHuntStorageItemUnique[ i ] > 0 )
		{
			pclStrInfo->clHuntStrInfo.clHuntStg[ siStorageItemIndex ].siItemUnique = pclMsg->siHuntStorageItemUnique[ i ];
			pclStrInfo->clHuntStrInfo.clHuntStg[ siStorageItemIndex ].siItemNum = pclMsg->siHuntStorageItemNum[ i ];
		}
	}

	return;
}


void cltServer::DoMsg_DBMSG_RESPONSE_HUNTLEFTMONSTERSTGIN(sPacketHeader* pPacket)
{
	sDBResponse_HuntLeftMonsterStgIn* pclMsg = (sDBResponse_HuntLeftMonsterStgIn*)pPacket;
	
	if ( pclMsg->siResult != 1 )
	{
		return;
	}

	if ( pclMsg->siVillageUnique < 1 )
	{
		return;
	}

	cltStrInfo *pclStrInfo = pclHuntManager->GetStrInfo( pclMsg->siVillageUnique );

	if ( pclStrInfo == NULL )
	{
		return;
	}

	if ( pclMsg->siItemUnique < 1 || pclMsg->siItemNum < 1 )
	{
		return;
	}

	if ( pclMsg->siToHuntStorageInventoryItemIndex < 0 || pclMsg->siToHuntStorageInventoryItemIndex >= MAX_HUNT_STG_NUMBER )
	{
		return;
	}

	pclStrInfo->clHuntStrInfo.clHuntStg[ pclMsg->siToHuntStorageInventoryItemIndex ].siItemUnique = pclMsg->siItemUnique;
	pclStrInfo->clHuntStrInfo.clHuntStg[ pclMsg->siToHuntStorageInventoryItemIndex ].siItemNum = pclMsg->siItemNum;
	
	return;
}
//���� ���� ����Ʈ
void cltServer::DoMsg_DBMSG_RESPONSE_HOFLIST( sPacketHeader *pPacket ){
	//���κ��� ���� �� ���������
	sDBResponse_HOFList* pclMsg = (sDBResponse_HOFList*)pPacket;
	HOFList* pHOFList = (HOFList* )pclMsg->HOFrList;
	SI32 id = pclMsg->uiCharID;

	cltGameMsgResponse_HOFList sendMsg(pHOFList,pclMsg->siRequestPage,pclMsg->siMaxPage );//���ϴ� �������� �����ش�
	cltMsg clMsg( GAMEMSG_RESPONSE_HOFLIST, sizeof(sendMsg), (BYTE*)&sendMsg );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);	
}
//��ŷ ����Ʈ
void cltServer::DoMsg_DBMSG_RESPONSE_RANKINGLIST( sPacketHeader *pPacket )
{
	sDBResponse_YearRanking* pclMsg = (sDBResponse_YearRanking*)pPacket;
	HOFList* pHOFList = (HOFList* )pclMsg->HOFrList;
	SI32 id = pclMsg->uiCharID;
	
	if( id == 0 )
	{
		// ������ DB�� ��û�� ���
		if( pclMsg->uiYear == pclTime->clDate.uiYear )
		{
			// ����
			pclGuildManager->siTopClearPoint = pclMsg->HOFrList[0].siClearPoint;
		}
		else
		{

			//[����] ���ӽð����� 1���� ���� �ְ���庯�� => 2008-5-29
			pclClient->pclLog->FilePrint( "config\\GuildRank" , "Response_YearRanking = %d-%d-%d", pclTime->clDate.uiYear, pclTime->clDate.uiMonth, pclTime->clDate.uiDay);

			SI32 siBeforeTopGuildUnique = pclGuildManager->siBeforeYearTopGuildUnique;

			// ���⵵
			pclGuildManager->siBeforeYearTopGuildUnique = pclMsg->HOFrList[0].siGuildUnique;

			// 1�⿡ �ѹ��� ȣ�� �Ǵ� ���,
			// �������� �����ϰ�, ���� �α��� �� �����鿡�� �ְ���� ������ ������Ʈ�Ѵ�.
			if( pclMsg->bReward )
			{
				//[����] ���ӽð����� 1���� ���� ������ ��忡 �����ֱ�. => 2008-5-29
				pclClient->pclLog->FilePrint( "config\\GuildRank" , "Reward");

				//------------------------------------------------------------------------
				// 3����� ������ ����
				//------------------------------------------------------------------------
				for (SI32 rank=0; rank<3; rank++)
				{
					if( _tcslen(pclMsg->HOFrList[rank].szHOFGuildName) <= 0 )		continue;					
					cltGuildInfo* pGuildInfo = pclGuildManager->GetGuildInfo(pclMsg->HOFrList[rank].szHOFGuildName);
					if( pGuildInfo == NULL )										continue;

					// �ְ� ��� ������ �ֱ�.
					// ��� ������.
					SI32 GuildMaster = pGuildInfo->siMasterPersonID;

					cltItem clInputItem;
					SI16	bRareSwitch = 0;
					SI32	ItemUnique = 0;
					SI32	ItemNum = 1;
					SI32	usedate = 0;

					switch(rank)
					{
						case 0:
							{
								ItemUnique = ITEMUNIQUE(18525); // 1�� ���� ���� 12�� ¥��
								usedate = 12;
							}
							break;
						case 1:
							{
								ItemUnique = ITEMUNIQUE(23090); // 2��������.
								usedate = 12;
							}
							break;
						case 2:
							{
								ItemUnique = ITEMUNIQUE(24096); // 3�� �����̵� 7�ϱ�
							}
							break;
					}

					SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique(ItemUnique);
					if (ref <= 0)	continue;

					// ������ ��¥�� ������, �������� �⺻���� ����Ѵ�.
					if(usedate <= 0)	usedate = pclClient->pclItemManager->pclItemInfo[ref]->clItem.uiDateUseDay;

					pclClient->pclItemManager->MakeRandItemUnique( ItemUnique, &clInputItem, 0, 0, &bRareSwitch, 0, 0, 0, 0, 0, usedate);

					// 1��, 2�� -> ���Ⱓ�� �����Ѵ�.
					if( ItemUnique == ITEMUNIQUE(18525) || ItemUnique == ITEMUNIQUE(23090) )
					{
						clInputItem.uiDateYear	= sTime.wYear - 2000;
						clInputItem.uiDateMonth = sTime.wMonth;
						clInputItem.uiDateDay	= sTime.wDay;
					}
					clInputItem.siItemNum = ItemNum;

					cltSystemRewardInfo clInfo;

					clInfo.m_sGiveTime = sTime;

					//NDate ExpireDate;
					//ExpireDate.SetDate( sTime.wYear, sTime.wMonth, sTime.wDay );
					//ExpireDate.AddDays( 12 );

					//_SYSTEMTIME sExpireTime;
					//ZeroMemory( &sExpireTime, sizeof(_SYSTEMTIME) );
					//sExpireTime.wYear = ExpireDate.m_uiYear;
					//sExpireTime.wMonth = ExpireDate.m_uiMonth;
					//sExpireTime.wDay = ExpireDate.m_uiDay;

					//clInfo.m_sExpireTime = sExpireTime;
					// ���޹��� ������ 12�ϵ��ȸ� ������ �� �ִ�.
					TimeAddDate(&clInfo.m_sGiveTime, 12, &clInfo.m_sExpireTime);

					clInfo.m_clItem.Set( &clInputItem );
					NTCHARString128 kMsg( GetTxtFromMgr(7845) );
					kMsg.Replace("#rank#", SI32ToString(rank + 1));
					StringCchCopy(clInfo.m_szReason, sizeof(clInfo.m_szReason), kMsg);

					for(SI32 i=0; i<MAX_GUILD_MEMBER_NUM; i++)
					{
						SI32 siID = 0;
						if( pGuildInfo->clMember[i].siPersonID <= 0 )		continue;

						siID = pclCM->GetIDFromPersonID( pGuildInfo->clMember[i].siPersonID );

						sDBRequest_GiveSystemReward clMsg( GIVEREWARD_CHAR, pGuildInfo->clMember[i].siPersonID, siID, &clInfo );
						SendDBMsg( DBSELECT_BASE, (sPacketHeader*)&clMsg );
					}
				}
				//-----------------------------------------------------------------------------------

				// ���� �ְ� ����� �ְ���� ������ �ʱ�ȭ�Ѵ�.
				if (siBeforeTopGuildUnique > 0)
				{
					SI32 id;
					SI32 index = 0;

					while(id = pclClient->pclCM->GetCharOrder(index))
					{
						index++;
						if ( pclClient->pclCM->IsValidID(id) == false )			continue;
						cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[id];
						if(pclchar->GetSession() == NULL)						continue;

						if( pclchar->pclCI->clBI.clGuildRank.IsGuildMember() &&
							pclchar->pclCI->clBI.clGuildRank.GetGuildUnitIndex() == siBeforeTopGuildUnique )
						{
							// �ϴ� �ڱ� �ڽ��� �ְ������� �ƴѰ��� �����Ѵ�.
							pclchar->uiBestGuild = 0;

							cltServerResponseValue clreturn(0, SRVAL_SUCCESS_INSTANTDUNGEON_SET_BESTGUILD, pclchar->GetCharUnique(), 0);
							// Ŭ���̾�Ʈ�� ������ ������. 
							cltMsg clMsg(GAMEMSG_RESPONSE_SERVERRTN, sizeof(cltServerResponseValue), (BYTE*)&clreturn);

							pclchar->SendNeighbourMsg(&clMsg, true);
						}
					}
				}

				if(pclMsg->HOFrList[0].siGuildUnique > 0)
				{
					cltGuildInfo* pGuildInfo = pclGuildManager->GetGuildInfo(pclMsg->HOFrList[0].szHOFGuildName);
					SI32		  masterid = 0;
					if( pGuildInfo )
					{
						masterid = pclClient->pclCM->GetIDFromPersonID(pGuildInfo->siMasterPersonID);
					}
					const TCHAR*  pName		 = NULL;
					if( masterid > 0)
					{
						pName = pclClient->pclCM->CR[masterid]->GetName();
					}

					//[����] ���ӽð����� 1���� ���� �ٲ� �ְ� ��� �̸�. => 2008-5-29
					pclClient->pclLog->FilePrint( "config\\GuildRank" , "Best Guild Name = %s", pName);

					//[�߰� : Ȳ���� 2008. 1. 14 => �ְ� ��带 ��ü �������� �˸�.]
					cltGameMsgResponse_InstantDungeonReward sendMsg(pclMsg->HOFrList[0].szHOFGuildName, pclMsg->HOFrList[0].siGuildMarkindex, pName);
					cltMsg clMsg( GAMEMSG_RESPONSE_INSTANTSDUNGEON_REWARD, sizeof(sendMsg), (BYTE*)&sendMsg );
					pclCM->SendAllPersonMsg((sPacketHeader*)&clMsg);

					// �ְ���尡 �� ĳ������ �ֺ��� ��Ȳ�� �˸�.
					SI32 id;
					SI32 index = 0;
					while(id = pclClient->pclCM->GetCharOrder(index))
					{
						index++;
						if ( pclClient->pclCM->IsValidID(id) == false )			continue;
						cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[id];
						if(pclchar->GetSession() == NULL)						continue;

						if( pclchar->pclCI->clBI.clGuildRank.IsGuildMember() &&
							pclchar->pclCI->clBI.clGuildRank.GetGuildUnitIndex() == pclMsg->HOFrList[0].siGuildUnique )
						{
							// �ϴ� �ڱ� �ڽ��� �ְ��������� �����Ѵ�.
							pclchar->uiBestGuild = 1;

							cltServerResponseValue clreturn(0, SRVAL_SUCCESS_INSTANTDUNGEON_SET_BESTGUILD, pclchar->GetCharUnique(), 1);
							// Ŭ���̾�Ʈ�� ������ ������. 
							cltMsg clMsg(GAMEMSG_RESPONSE_SERVERRTN, sizeof(cltServerResponseValue), (BYTE*)&clreturn);

							pclchar->SendNeighbourMsg(&clMsg, true);
						}
					}
				}
			}
		}
		pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("cltGameMsgResponse_RankingListt"));
	}
	else
	{
		cltGameMsgResponse_RankingListt sendMsg(pHOFList,pclMsg->siRequestPage,pclMsg->siMaxPage);//���ϴ� �������� �����ش�
		cltMsg clMsg( GAMEMSG_RESPONSE_RAKINGLIST, sizeof(sendMsg), (BYTE*)&sendMsg );
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);	
	}
}