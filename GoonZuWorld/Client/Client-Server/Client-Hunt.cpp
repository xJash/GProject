//---------------------------------
// 2004/2/18 ���°�
//---------------------------------

#include "..\Client.h"
#include "..\Music\Music.h"
#include "..\CommonLogic\MsgType.h"

#include "..\CommonLogic\Msg\MsgType-Hunt.h"
#include "..\CommonLogic\Hunt\Hunt.h"
#include "../NInterface/NInstantDungeonDlg/NInstantDungeonBoardDlg.h"
#include "../NInterface/NInstantDungeonDlg/NInstantDungeonNotipyDlg.h"
#include "../ninterface/NServerEventDlg/NServerEventIndunInfo.h"

//-------------------------------------
// Common
//-------------------------------------
#include "PersonInfo.h"
#include "Char\CharManager\CharManager.h"

#include "../Client/ninterface/NInstantDungeonDlg/InstantDungeonRunInfoDlg.h"
#include "../Client/ninterface/NInstantDungeonDlg/InstanstDungeonStatusDlg.h"
#include "../Client/ninterface/nrareitemdlg/NRareItemDlg.h"

#include "../Client/Interface/SoundOnOffDlg/SoundOnOffDlg.h"
#include "../Client/ninterface/nsoundonoffdlg/NSoundOnOffDlg.h"



void cltClient::DoMsg_GAMEMSG_RESPONSE_HUNTMONSTERFIELDLISTADD(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_HuntMonsterFieldListAdd *pclInfo = (cltGameMsgResponse_HuntMonsterFieldListAdd*)pclMsg->cData;
	
	
	if ( pclCM->CR[1]->GetCurrentVillageUnique() == pclInfo->siVillageUnique )
	{
		pclHuntManager->clClientStrInfo.clHuntStrInfo.clHuntLineUp[ pclInfo->siAddListIndex ].siLineUpKind = pclInfo->siMonsterKind;
		pclHuntManager->clClientStrInfo.clHuntStrInfo.clHuntLineUp[ pclInfo->siAddListIndex ].siLineUpKindNum = pclInfo->siMonsterNum;
		pclHuntManager->clClientStrInfo.clHuntStrInfo.clHuntLineUp[ pclInfo->siAddListIndex ].siLineUpKindLevel = pclInfo->siMonsterLevel;
		pclHuntManager->LoadLineUpInfoList();
	}
	
	return;
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_HUNTMONSTERFIELDLISTDEL(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_HuntMonsterFieldListDel *pclInfo = (cltGameMsgResponse_HuntMonsterFieldListDel*)pclMsg->cData;
	
	if ( pclCM->CR[1]->GetCurrentVillageUnique() == pclInfo->siVillageUnique )
	{
		pclHuntManager->clClientStrInfo.clHuntStrInfo.clHuntLineUp[ pclInfo->siDelListIndex ].siLineUpKind = 0;
		pclHuntManager->clClientStrInfo.clHuntStrInfo.clHuntLineUp[ pclInfo->siDelListIndex ].siLineUpKindLevel = 0;
		pclHuntManager->clClientStrInfo.clHuntStrInfo.clHuntLineUp[ pclInfo->siDelListIndex ].siLineUpKindNum = 0;
		pclHuntManager->LoadLineUpInfoList();
	}
	
	return;
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_HUNTMONSTERIN(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_HuntMonsterIn *pclInfo = (cltGameMsgResponse_HuntMonsterIn*)pclMsg->cData;

	id = 1;
	pclCM->CR[id]->pclCI->clCharItem.clItem[ pclInfo->siUserInventoryIndex ].Set( &pclInfo->clItem );

	if ( pclCM->CR[1]->GetCurrentVillageUnique() == pclInfo->siVillageUnique )
	{
		pclHuntManager->clClientStrInfo.clHuntStrInfo.clHuntStg[ pclInfo->siHuntStorageItemIndex ].siItemUnique = pclInfo->siHuntStorageItemUnique;
		pclHuntManager->clClientStrInfo.clHuntStrInfo.clHuntStg[ pclInfo->siHuntStorageItemIndex ].siItemNum = pclInfo->siHuntStorageItemNum;
	}
		
	return;
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_HUNTMONSTEROUT(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_HuntMonsterOut *pclInfo = (cltGameMsgResponse_HuntMonsterOut*)pclMsg->cData;

	id = 1;
	pclCM->CR[id]->pclCI->clCharItem.clItem[ pclInfo->siUserInventoryIndex ].Set( &pclInfo->clItem );

	if ( pclCM->CR[1]->GetCurrentVillageUnique() == pclInfo->siVillageUnique )
	{
		pclHuntManager->clClientStrInfo.clHuntStrInfo.clHuntStg[ pclInfo->siHuntStorageItemIndex ].siItemUnique = pclInfo->siHuntStorageItemUnique;
		pclHuntManager->clClientStrInfo.clHuntStrInfo.clHuntStg[ pclInfo->siHuntStorageItemIndex ].siItemNum = pclInfo->siHuntStorageItemNum;
	}

	

	return;
}

// ������ ��庥Ƽ���� ���Ѵ�. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_HUNTADDRATE(cltMsg* pclMsg, SI32 id)
{
	pclHuntManager->siHuntAddRate = (SI32)pclMsg->siData32[0];
}


//[�߰� : Ȳ���� 2008. 1. 9 => �ν���Ʈ���� �������� �ޱ�.]
void cltClient::DoMsg_GAMEMSG_RESPONSE_INSTANTSDUNGEON_STATUS(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_InstantsDungeonStatus* pclInfo = (cltGameMsgResponse_InstantsDungeonStatus*)pclMsg->cData;

	CreateInterface(NINSTANST_DUNGEON_STATUS_DLG);
	
	InstanstDungeonStatusDlg* pStatusDlg = (InstanstDungeonStatusDlg*)m_pDialog[ NINSTANST_DUNGEON_STATUS_DLG ];
	pStatusDlg->InitList(pclInfo);
}


//[�߰� : Ȳ���� 2008. 1. 10 => �ν���Ʈ���� ���� �������� �ޱ�.]
void cltClient::DoMsg_GAMEMSG_RESPONSE_INSTANTSDUNGEON_RUN_STATUS(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_cInstantsDungeonRunInfo* pclInfo = (cltGameMsgResponse_cInstantsDungeonRunInfo*)pclMsg->cData;

	CreateInterface(NINSTANST_DUNGEON_RUN_INFO_DLG);
	
	InstanstDungeonRunInfoDlg* pRunStatusDlg = (InstanstDungeonRunInfoDlg*)m_pDialog[ NINSTANST_DUNGEON_RUN_INFO_DLG ];	
	pRunStatusDlg->Show( true );
	pRunStatusDlg->Init( pclInfo );

	if( pclInfo->siMode == DUNGEONRUN_END )
		pRunStatusDlg->DeleteDialog();
}

//���� ���� ����Ʈ
void cltClient::DoMsg_GAMEMSG_RESPONSE_HOFList(cltMsg* pclMsg, SI32 id)
{

	cltGameMsgResponse_HOFList *pclInfo = (cltGameMsgResponse_HOFList*)pclMsg->cData;

	//((cltClient*)pclClient)->CreateInterface( NINSTANTDUNGEONBOARD_DLG );
	if ( m_pDialog[ NINSTANTDUNGEONBOARD_DLG ] )
	{
#ifdef _SAFE_MEMORY
		(((NInstantDungeonBoradDlg*)m_pDialog[ NINSTANTDUNGEONBOARD_DLG ])->ChangeListBoxHOF(&pclInfo->stHOFList[0],pclInfo->siCurPage, pclInfo->siMaxPage));
#else
		(((NInstantDungeonBoradDlg*)m_pDialog[ NINSTANTDUNGEONBOARD_DLG ])->ChangeListBoxHOF(pclInfo->stHOFList,pclInfo->siCurPage, pclInfo->siMaxPage));
#endif
	}
	

}

//��ŷ ����Ʈ 
void cltClient::DoMsg_GAMEMSG_RESPONSE_RakingList(cltMsg* pclMsg, SI32 id)
{//�����κ��� �޾Ҵ� 

	cltGameMsgResponse_RankingListt *pclInfo = (cltGameMsgResponse_RankingListt*)pclMsg->cData;
	
	//((cltClient*)pclClient)->CreateInterface( NINSTANTDUNGEONBOARD_DLG );
	if ( m_pDialog[ NINSTANTDUNGEONBOARD_DLG ] )
	{
#ifdef _SAFE_MEMORY
		(((NInstantDungeonBoradDlg*)m_pDialog[ NINSTANTDUNGEONBOARD_DLG ])->ChangeListBoxRanking(&pclInfo->stHOFList[0], pclInfo->siPageNum, pclInfo->siMaxPageNum));
#else
		(((NInstantDungeonBoradDlg*)m_pDialog[ NINSTANTDUNGEONBOARD_DLG ])->ChangeListBoxRanking(pclInfo->stHOFList, pclInfo->siPageNum, pclInfo->siMaxPageNum));
#endif
	}
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_INSTANTMAP_GATEINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_InstanceMap_GateInfo* pclInfo = (cltGameMsgResponse_InstanceMap_GateInfo*)pclMsg->cData;

	cltCharClient* pclchar = (cltCharClient*)pclClient->pclCM->CR[1];
	SI32 mapindex = pclchar->GetMapIndex();

	if( mapindex <= 0 || mapindex > MAX_MAP_NUMBER )	return;

	SI32	i, k, j;
	for(i = 0;i < pclInfo->siCount;i++)
	{
		cltInstanceMapGate* pclgate = &pclInfo->clGates[i];

		if(pclgate->FOUnique == 0)				continue;
		if(pclgate->SrcMapIndex != mapindex)	continue;

		pclClient->pclMapManager->pclMapArray[pclgate->SrcMapIndex]->DeleteFieldObject( pclgate->SrcX, pclgate->SrcY );
		pclClient->pclMapManager->pclMapArray[pclgate->SrcMapIndex]->PutFieldObject(pclgate->SrcX, pclgate->SrcY, pclgate->FOUnique, pclgate->siUnique);

		// Gate Field Object�ֺ��� �浹 ������ �����Ѵ�. 
		for(k= -10;k<10;k++)
			for(j= - 10;j<10;j++)
			{
				SI32 collinfo = pclClient->pclMapManager->pclMapArray[pclgate->SrcMapIndex]->CalcCollInfo(pclgate->SrcX + j, pclgate->SrcY + k);
				if(collinfo)
				{
					pclClient->pclMapManager->pclMapArray[pclgate->SrcMapIndex]->SetCollMap(pclgate->SrcX + j, pclgate->SrcY + k, collinfo);
				}
			}

	}
}

// [�߰� : Ȳ���� 2008. 1. 11 => �δ� �������� �����ذ� ó��]
void cltClient::DoMsg_GAMEMSG_RESPONSE_INSTANTSDUNGEON_REWARD(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_InstantDungeonReward* pclInfo = (cltGameMsgResponse_InstantDungeonReward*)pclMsg->cData;

	CreateInterface(NINSTANST_DUNGEON_NOTIPY);

	InstanstDungeonNotipyDlg* pInstantDungeonRewad = (InstanstDungeonNotipyDlg*)m_pDialog[ NINSTANST_DUNGEON_NOTIPY ];	
	pInstantDungeonRewad->SetInstantDungeon(pclInfo->siGuildMarkIndex, pclInfo->szGuildName, pclInfo->szGuildMasteName);
}


//[�߰� : Ȳ���� 2008. 1. 17 => �δ� �ְ� ���� ���� �˸�.]	
void cltClient::DoMsg_GAMEMSG_RESPONSE_INSTANTSDUNGEON_TOP_CHANGE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_InstantDungeon_Top_Change* pclInfo = (cltGameMsgResponse_InstantDungeon_Top_Change*)pclMsg->cData;

	CreateInterface(NINSTANST_DUNGEON_NOTIPY);

	InstanstDungeonNotipyDlg* pInstantDungeonTopChange = (InstanstDungeonNotipyDlg*)m_pDialog[ NINSTANST_DUNGEON_NOTIPY ];	
	pInstantDungeonTopChange->SetInstantDungeonTopChange(pclInfo->siGuildMarkIndex, pclInfo->szGuildName, pclInfo->siScore, pclInfo->szGuildMasteName);
}

// [����] ������ : Ŭ�����ؼ� �������� �������� �޾Ҵٰ� �˷���
void cltClient::DoMsg_GAMEMSG_RESPONSE_INSTANTDUNGEON_PARTY_CLEAR( cltMsg* pclMsg, SI32 id )
{
	if ( true == g_SoundOnOffDlg.m_bJewelItemNotifyReject )
	{
		return;
	}

	cltGameMsgResponse_InstantDungeon_Party_Clear* pclInfo = (cltGameMsgResponse_InstantDungeon_Party_Clear*)pclMsg->cData;
	if ( pclInfo == NULL )
	{
		return;
	}

	cltClient* pclclient = (cltClient*)pclClient;
	if ( pclclient == NULL )
	{
		return;
	}

	if ( pclInfo->siGetItemUnique <= 0 )
	{
		return;
	}

	NTCHARString64		kTitle( GetTxtFromMgr(7981) );
	NTCHARString256		kMessage( GetTxtFromMgr(7984) );

	cltItem				clGetItem;
	SI16				siRareSwitch = 0;

	if ( pclItemManager->MakeRandItemUnique( pclInfo->siGetItemUnique, &clGetItem, 0, 0, &siRareSwitch, 0, 0, 0, 0, 0, 1 ) == false )
	{
		return;
	}

	kMessage.Replace( TEXT("#username#"), pclInfo->tszUserName );
	kMessage.Replace( TEXT("#itemname#"), clGetItem.GetShortName(pclItemManager) );

	PushEffect(pclclient->GetUniqueFromHash(TEXT("SOUND_EFFECT_MAKE_MASTER")), 0, 0);

	if(pclclient->m_pDialog[NRAREITEM_DLG ] == NULL)
	{
		CreateInterface( NRAREITEM_DLG );
	}
	((CNRareItemDlg*)pclclient->m_pDialog[NRAREITEM_DLG ])->SetBestGacha(&clGetItem, pclInfo->tszUserName, kTitle, kMessage);
	
}

// [����] ������ : �������� ��Ÿ���ٴ� �޽���
void cltClient::DoMsg_GAMEMSG_RESPONSE_PIRATESHIP_APPEAR( cltMsg* pclMsg, SI32 id )
{
	NTCHARString64	kMessage = GetTxtFromMgr( 7983 );

	pclMessage->SetMsg( kMessage, 0, RGB(255, 255, 0) );
}

// [����] ���� �̺�Ʈ �δ� : �δ����� ��Ȳ ����
void cltClient::DoMsg_GAMEMSG_RESPONSE_SERVER_EVENT_INSTANCEDUNGEON_RUNINFO( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgResponse_Server_Event_InstanceDungeon_RunInfo* pclInfo = (cltGameMsgResponse_Server_Event_InstanceDungeon_RunInfo*)pclMsg->cData;
	if ( pclInfo == NULL )
	{
		return;
	}

	cltClient* pclclient = (cltClient*)pclClient;
	if ( pclclient == NULL )
	{
		return;
	}

	if ( NULL == pclclient->m_pDialog[SERVER_EVENT_INDUNINFO] )
	{
		CreateInterface( SERVER_EVENT_INDUNINFO );
	}

	CNServerEventIndunInfoDlg* pIndunInfo = (CNServerEventIndunInfoDlg*)pclclient->m_pDialog[ SERVER_EVENT_INDUNINFO ];
	if ( NULL == pIndunInfo )
	{
		return;
	}

	pIndunInfo->SetServerEventIndunInfo( 
		pclInfo->m_siServerUnique, 
		pclInfo->m_siClearStep,
		pclInfo->m_dwRemainTime,
		pclInfo->m_siRemainMonster,
		pclInfo->m_siScore,
		pclInfo->m_siDungeonScore
	);

}