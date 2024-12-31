//---------------------------------
// 2004/2/18 ���°�
//---------------------------------


#include <CommonLogic.h>
#include "..\..\Server\Server.h"

#include "Char\CharCommon\Char-Common.h"
#include "Char\CharManager\CharManager.h"

//---------------------------------------
// Server
//---------------------------------------
#include "..\..\Server\Statistics\Statistics.h"
#include "..\..\Resource.h"

#include "Hunt.h"
#include "..\..\DBManager\GameDBManager_World\DBMsg-Market.h"
#include "..\..\DBManager\GameDBManager_World\DBMsg-Hunt.h"
#include "..\..\DBManager\GameDBManager_World\DBMsg-Structure.h"

#include "MsgRval-Define.h"
#include "../../CommonLogic/MsgType-Structure.h"
#include "../../CommonLogic/Msg\MsgType-Hunt.h"

#include "../../Common/Item/ItemCommon/ItemUnit.h"
#include "../../Common/Char/CharCommon/Char-Common.h"

#include "../CityHall/TaxpaymentListDlg.h"
#include "../../Client/Interface/ErrorMsgDlg/ErrorMsgDlg.h"
#include "../../Client/Interface/NotifyMsgDlg/NotifyMsgDlg.h"

#include "..\..\DBManager\GameDBManager_World\DBMsg-Person.h"
#include "../../common/Event/event.h"

extern cltCommonLogic* pclClient;


//-----------------------------------------------
// cltHunt
//-----------------------------------------------
cltHunt::cltHunt(SI32 sivillageunique) : cltStructureBasic(sivillageunique)
{
	m_PreClock = 0;

	siLeftMonNum	= 0;
	siLeftUserNum	= 0;
	dwLastCheckClock		= 0;
	dwLastGiveExpClock	= 0;

}

cltHunt::~cltHunt()
{
	
}

void cltHunt::AddLeftMon(SI32 kind, SI16* pdata)
{
	SI32 i;


	for(i = 0;i < MAX_HUNT_LINEUP_NUMBER;i++)
	{
		if(pdata[i * 2] == kind)
		{
			pdata[i * 2 + 1]++;
			return ;
		}
	}

	for(i = 0;i < MAX_HUNT_LINEUP_NUMBER;i++)
	{
		if(pdata[i * 2] == 0)
		{
			pdata[i * 2]		= kind;
			pdata[i * 2 + 1]	= 1;
			return ;
		}
	}
	
}

// �����忡 ���� ���� ������ Ȯ���Ѵ�.
void cltHunt::CheckLeftMonNum(SI16* pdata)
{

	SI32 id;
	SI32 index = 0;
	SI32 mapindex = siVillageUnique + 200;
	while(id = pclClient->pclCM->GetCharOrder(index))
	{
		index++;

		if (pclClient->pclCM->IsAlive(id) == FALSE)										continue;	// ��� �־�� �ϰ�, 
		if (IsPC(id) )																	continue;	// ����ڰ� �ƴϾ�� �ϰ�, 
		if (pclClient->pclCM->CR[id]->GetMapIndex() != mapindex)						continue;	// �������� ������ �־�� �Ѵ�.
		if (pclClient->pclCM->CR[id]->clIdentity.siIdentity == IDENTITY_PERSON_SUMMON)	continue;	// ��ȯ�� ������ �ȵȴ�.
		if (pclClient->pclCM->CR[id]->clIdentity.siIdentity == IDENTITY_SOULGUARD)		continue;	// ��ȣ����

		SI32 kind		= pclClient->pclCM->CR[id]->GetKind();

		if( kind == pclClient->GetUniqueFromHash(TEXT("KIND_JOKER")) ) continue;


		SI32 itemunique = pclClient->pclKindInfoSet->pclKI[kind]->siDollUnique;

		AddLeftMon(itemunique, pdata);
	}
	

}

// ����ڸ� �� �Ѵ´�. 
void cltHunt::GoOutUser()
{
	// ��� �����忡�� �� ������. 
	SI32 id;
	SI32 index = 0;
	SI32 mapindex = siVillageUnique + 200;

	if(pclClient->pclMapManager->pclMapArray[siVillageUnique] == NULL)return ;

	SI32 maptypeunique = pclClient->pclMapManager->pclMapArray[siVillageUnique]->siMapUnique;
	if(maptypeunique <= 0)return ;

	// ����� ���� �ʱ�ȭ�Ѵ�. 
	siLeftUserNum = 0;

	SI32 x = pclClient->pclMapManager->pclMapTypeManager->pclMapTypeInfo[maptypeunique]->siCenterX;
	SI32 y = pclClient->pclMapManager->pclMapTypeManager->pclMapTypeInfo[maptypeunique]->siCenterY;

	while(id = pclClient->pclCM->GetCharOrder(index))
	{
		index++;

		if(pclClient->pclCM->IsAlive(id))
		{
			// ����ڴ� ��� ��������. 
			if(IsPC(id) && pclClient->pclCM->CR[id]->GetMapIndex() == mapindex)
			{
				cltWarpInfo clWarpInfo(1, siVillageUnique, false, false, x, y, -1, -1);
				pclClient->pclCM->CR[id]->SetWarpInfo(&clWarpInfo, 800);
				pclClient->pclCM->CR[id]->Warp();

				// ������ �˸���. 
				((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_HUNT_NOTENOUGHMON,  0, 0, id);

			}
		}
	}


}
// ���͸� ��ġ�Ѵ�. 
bool cltHunt::SetMonster()
{

	SI32 i;
	SI32 x, y;

	siLeftMonNum	= 0;

	cltServer* pclserver = (cltServer*)pclClient;
	

	SI32 kind;
	SI32 maxkindnum;
	SI32 level;
	
	SI32 monindex = 0;
	cltHuntLineUp* pcllineup = clStrInfo.clHuntStrInfo.clHuntLineUp;
	
	_SYSTEMTIME sTime;
	GetLocalTime(&sTime);

	for(i = 0;i < MAX_HUNT_LINEUP_NUMBER;i++)
	{
		kind		= pcllineup[i].siLineUpKind;
		maxkindnum	= pcllineup[i].siLineUpKindNum;
		level		= pcllineup[i].siLineUpKindLevel;

		//	�̺�Ʈ �Ⱓ������ ĥ���� ��ġ �Ƚ�Ų��.
		if(!pclClient->pclEventTimeManager->InEventTime(TEXT("Chuseok_Monster_Appear"), &sTime))
		{
			if(kind == pclClient->GetUniqueFromHash(TEXT("KIND_TURKEY")))
			{
				continue;
			}
		}

		siLeftMonNum += maxkindnum;

		SI32 curmonnum  = 0;
		while(curmonnum < maxkindnum)
		{
			SI32 mapindex = siVillageUnique + 200;
			
			x = rand() % pclserver->pclMapManager->pclMapArray[mapindex]->GetXsize();
			y = rand() % pclserver->pclMapManager->pclMapArray[mapindex]->GetYsize();
			
			SI32 dx, dy;
			if(pclserver->pclMapManager->pclMapArray[mapindex]->FindEmptyAreaForCharLocate(kind, x, y, 10, &dx, &dy, true) == false)continue;
			
			// NPC�� ����� �����۵� �ش�. 
			cltInnerStatusInfo clinnerstatus;
			clinnerstatus.clEnemyType.Set(ENEMYTYPE_ALLPC, 0);
			
			if(pclserver->SetNPCChar(kind, VILLAGE_NONE, NULL, 1, 0, dx, dy, mapindex, NPCITEMMODE_HUNT, &clinnerstatus ) > 0)
			{
				curmonnum++;
			}
			
		}
		monindex++;
	}

	return true;

}



void cltHunt::Action()
{		
	
	// ���� �� ���� ���⿡��, ������ ������ ������ �� ���� �������� �ƴ������� �˷��ֱ� ���ؼ�...
	if( TABS(pclClient->CurrentClock - m_PreClock) > 60000 )			// 60000 = 60��
	{
		m_PreClock = pclClient->CurrentClock;

		if( pclClient->pclHuntManager->IsHuntLineUpMonsterReady( siVillageUnique ) == false )
		{
			clStrInfo.clHuntStrInfo.siHuntStatus = HUNT_ENTER_ITEMINSUFFICIENY;
		}
		else
		{
			for( SI32 i = 0; i < MAX_HUNT_LINEUP_NUMBER; ++i )
			{
				if ( clStrInfo.clHuntStrInfo.clHuntLineUp[i].siLineUpKind > 0 )
				{
					break;
				}
			}

			if ( i == MAX_HUNT_LINEUP_NUMBER )
			{
				clStrInfo.clHuntStrInfo.siHuntStatus = HUNT_ENTER_ITEMINSUFFICIENY;
			}
			else
			{
				clStrInfo.clHuntStrInfo.siHuntStatus = HUNT_ENTER_ENABLESTATUS;
			}
		}
	}
	

	if(siLeftUserNum == 0)
	{
		if(siLeftMonNum)
		{
			// ���� ���ʹ� â�� �ٽ� �ִ´�. 
			SI16 siLeftMonInfo[MAX_HUNT_LINEUP_NUMBER * 2];
			ZeroMemory(siLeftMonInfo, sizeof(siLeftMonInfo));
			CheckLeftMonNum(siLeftMonInfo);
			
			pclClient->pclHuntManager->RecoverDollItem(siVillageUnique, siLeftMonInfo);
			
			// mapindex�� �ִ� ��� npc�� �����Ѵ�. 
			pclClient->pclCM->DeleteAllNPCInMapIndex(siVillageUnique + 200);
			
			// ���͸� ��� �����Ѵ�. 
			siLeftMonNum	= 0;
			
		}
	}

	// ����ڰ� �����ϰ� ���ʹ� ��� óġ �Ǿ��ٸ�, 
	if(siLeftUserNum && siLeftMonNum == 0)
	{
		// ���Ͱ� �����ϸ� ����. 
		if(pclClient->pclHuntManager->IsHuntLineUpMonsterReady(siVillageUnique) == true)
		{
			// �������� ���� ���͸� ��� �����ϰ� ���Ӱ� ���͸� �����. 
			if(pclClient->pclHuntManager->SetNewMonster(siVillageUnique) == true)
			{
				// ������ â���� ��� �Ҹ��Ų��. 
				pclClient->pclHuntManager->WasteStgDoll(siVillageUnique);
			}
		}
		else
		{
			// ��� �������� ����ڸ� ��������. 
			GoOutUser();
			return ;
		}

	}

	//-------------------------------------------------
	// ������� ����ġ�� �ش�. (10�� ����) 
	//-------------------------------------------------
	if(TABS(pclClient->CurrentClock - dwLastGiveExpClock)  >= 600000)
	{
		dwLastGiveExpClock = pclClient->CurrentClock;

		// ����ġ�� ������ ������� �ش�. 
		// ������� ���� ���ο� ������� ����ġ�� �ش�.
		if(clStrInfo.clHuntStrInfo.siChiefExp)
		{
			cltServer* pclserver = (cltServer*)pclClient;
			cltRank* pclrank = pclserver->pclRankManager->GetRank(RANKTYPE_HUNT, siVillageUnique);
			if(pclrank)
			{
				SI32 huntchiefpersonid = pclrank->clPerson.siPersonID;
				
				if(huntchiefpersonid)
				{
					pclClient->pclCM->IncExp(huntchiefpersonid, clStrInfo.clHuntStrInfo.siChiefExp, CHANGE_EXP_REASON_HUNTCHIEF);
					
					// ����ġ�� �ʱ�ȭ�Ѵ�. 
					clStrInfo.clHuntStrInfo.siChiefExp = 0;
				}
			}
		}
		
		// �����忡 �����ؾ� �� ���� �ִ°� ?
		if(clStrInfo.clHuntStrInfo.siTempMoney)
		{

			sDBRequest_ChangeStrMoney sendMsg( CHANGESTRMONEY_HUNT, 0, siVillageUnique, RANKTYPE_HUNT,  clStrInfo.clHuntStrInfo.siTempMoney);
			((cltServer *)pclClient)->SendDBMsg(DBSELECT_BASE,  (sPacketHeader *)&sendMsg );

	
			// ������ ���� �ʱ�ȭ �Ѵ�. 
			clStrInfo.clHuntStrInfo.siTempMoney = 0;
		}
	}
}


cltHuntManager::cltHuntManager(cltCharManager* pclcm, SI32 gamemode, SI32 ranktype, TCHAR *strFileName ) : cltStructureMngBasic(MAX_HUNT_TAB_NUMBER, pclcm, ranktype, strFileName )
{	
	
	m_hHuntChiefDlg = NULL;
	m_hHuntUserDlg = NULL;

	m_hImageList = NULL;
	
	
	m_pclMyItem = new cltItem[ MAX_ITEM_PER_PERSON ];
	m_pclHuntStg = new cltHuntStg[ MAX_HUNT_STG_NUMBER ];
	memset( m_pclHuntStg, 0, sizeof( cltHuntStg ) * MAX_HUNT_STG_NUMBER );

	memset( m_strListSelectedMonsterName, 0, 64 );

	// ������ ��
#ifdef _SAFE_MEMORY
	m_siHuntMapUnique.ZeroMem();
#else
	memset( m_siHuntMapUnique, 0, sizeof(m_siHuntMapUnique) );
#endif
	m_siHuntMapNumber = 0;
	m_siHuntMapNumber = 0;
	
	siHuntAddRate = 0;


}

cltHuntManager::~cltHuntManager()
{
	m_siInventorySelectedIndex = -1;
	m_siHuntStorageSelectedIndex = -1;
	
	if ( m_pclMyItem )
	{
		delete [] m_pclMyItem;
	}

	if( m_pclHuntStg )
	{
		delete m_pclHuntStg;
		m_pclHuntStg = NULL;
	}
}

// ���� ȯ�� �λ縻ǥ�� . 
void cltHuntManager::GreetingMsg(HWND hDlg)
{
	TCHAR* pText = GetTxtFromMgr(2153);
	SetMainExplain(hDlg, pText);
}

void cltHuntManager::Do_WM_INITDIALOG(SI32 charunique)
{
	
	cltStructureMngBasic::Do_WM_INITDIALOG(charunique);
}

// �������� �ż��Ѵ�.
BOOL cltHuntManager::CreateHunt(SI32 siunique)
{
	
	// �������� �����. 
	if(pclStruct[siunique] == NULL)
	{
		pclStruct[siunique] = new cltHunt(siunique);
		return TRUE;
	}
		
	return FALSE;
}

// �������� ���͸� ��� �����ϰ� �ٽ� �����. 
bool cltHuntManager::SetNewMonster(SI32 villageunique)
{

	// mapindex�� �ִ� ��� npc�� �����Ѵ�. 
	pclClient->pclCM->DeleteAllNPCInMapIndex(villageunique + 200);

	// ���Ӱ� npc�� ��ġ�Ѵ�.
	cltHunt* pclhunt = (cltHunt*)pclStruct[villageunique];
	if(pclhunt == NULL)return false;

	return pclhunt->SetMonster();
}


void cltHuntManager::Action()
{
	SI32 i;

	//----------------------------------------------
	// ������ ��庥Ƽ���� ����Ѵ�. 
	//----------------------------------------------
	siHuntAddRate	= 0;
	SI32 targetrate = 30;	// ������ �̿����� ��ǥ ����. 

	// DB �ʱ�ȭ �Ϸ�ɶ����� ��ٸ�
	if( ((cltServer *)pclClient)->bCompleteDBInitAll == FALSE ) return;


	cltServer* pclserver = (cltServer*)pclClient;
	if(pclserver && pclserver->pclStatisticsManager && pclserver->pclStatisticsManager->clDailyStatistics.siDungeonUserNumber)
	{
		// ������ �̿����� ����. 
		SI32 rate = pclserver->pclStatisticsManager->clDailyStatistics.siHuntUserNumber * 100  / pclserver->pclStatisticsManager->clDailyStatistics.siDungeonUserNumber;
		
		// ��������. . 
		if(targetrate > rate)
		{
			SI32 shortrate = (targetrate - rate) * 100 / targetrate;
			
			if(shortrate)
			{
				siHuntAddRate = 80 * shortrate / 100;
			}
		}
	}
	
	// �����庰 ���� ���� �ľ��Ѵ�. 
	static DWORD dwLastCheckClcok = 0;
	if(TABS(pclClient->CurrentClock - dwLastCheckClcok) > 5000)
	{
		dwLastCheckClcok = pclClient->CurrentClock;

		// ������ �ܿ� ���͸� �ʱ�ȭ�Ѵ�. 
		for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
		{
			cltHunt* pclhunt = (cltHunt*)pclStruct[i];
			if(pclhunt == NULL)continue;
			
			pclhunt->siLeftMonNum = 0;
			pclhunt->siLeftUserNum = 0;
		}

		SI32 id;
		SI32 index = 0;
		while(id = pclClient->pclCM->GetCharOrder(index))
		{
			index++;
			
			// ����� ĳ���ʹ� ��ȿ. 
			if(pclClient->pclCM->IsAlive(id) == false)continue;
			
			SI32 mapindex = pclClient->pclCM->CR[id]->GetMapIndex();
			// ���� �ɷ��� ���ų� �����忡 ���� ������ ��ȿ. 
			if(pclCM->CR[id]->IsAtb(ATB_ATTACK)==false || pclClient->pclMapManager->IsHuntMap(mapindex) == false)continue;

			cltHunt* pclhunt = (cltHunt*)pclStruct[mapindex - 200];
	
			if(IsPC(id))
			{
				pclhunt->siLeftUserNum++;
			}
			else
			{
				// ��ȯ���� �ƴϸ�, 
				if(pclCM->CR[id]->clIdentity.siIdentity != IDENTITY_PERSON_SUMMON)
				{
					pclhunt->siLeftMonNum++;
				}
			}
		}
	}


	for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
	{
		cltHunt* pclhunt = (cltHunt*)pclStruct[i];
		if(pclhunt == NULL)continue;

		pclhunt->Action();

	}

}


bool cltHuntManager::IsMyInventoryChanged()
{
	for ( int j = PERSONITEM_INV0; j < MAX_ITEM_PER_PERSON; ++j )		// ����â�� üũ�� �ʿ� �����Ƿ�, 10 ���� ��.
	{
		SI32 size = sizeof(cltItem);

		BYTE* src = (BYTE*)&m_pclMyItem[ j ];
		BYTE* dst = (BYTE*)&pclClient->pclCM->CR[1]->pclCI->clCharItem.clItem[ j ];

		for(int i = 0;i < size; i++)
		{
			if( src[i] != dst[i] )
			{
				return true;
			}
		}
	}

	return false;
}

void cltHuntManager::LoadMyInventory()
{

	/*
	for ( int i = PERSONITEM_INV0; i < PERSONITEM_SUMMON1EQUIP0; ++i )
	{
		m_pclMyItem[i] = pclClient->pclCM->CR[1]->pclCI->clCharItem.clItem[ i ];
	}
	
	if( m_hHuntChiefDlg )
	{
		ListView_DeleteAllItems( GetDlgItem( m_hHuntChiefDlg, IDC_LIST_INVENTORY ) );
		
		SetInventoryInListView( pclClient->pclItemManager, m_hHuntChiefDlg, IDC_LIST_INVENTORY, NULL, &pclClient->pclCM->CR[1]->pclCI->clCharItem );
	}
	*/
	return;
}

bool cltHuntManager::IsHuntStorageInventoryChanged()
{
	for ( int i = 0; i < MAX_HUNT_STG_NUMBER; ++i )
	{
		if ( m_pclHuntStg[ i ].siItemNum != clClientStrInfo.clHuntStrInfo.clHuntStg[ i ].siItemNum || m_pclHuntStg[ i ].siItemUnique != clClientStrInfo.clHuntStrInfo.clHuntStg[ i ].siItemUnique )
		{
			return true;
		}
	}	
	
	return false;
}

void cltHuntManager::LoadHuntStorageInventory()
{
	/*
	SendMessage( m_hMonsterComboList, CB_RESETCONTENT, 0, 0 );

	for ( int i = 0; i < MAX_HUNT_STG_NUMBER; ++i )
	{
		m_pclHuntStg[i].Set( &clClientStrInfo.clHuntStrInfo.clHuntStg[ i ] );
		if ( m_pclHuntStg[i].siItemUnique != 0 )
		{
			SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique( m_pclHuntStg[i].siItemUnique );
			if(ref > 0)
			{
				SI32 monkind = pclClient->pclItemManager->pclItemInfo[ref]->siMakeKind;
				TCHAR *strMonsterName = (TCHAR*)pclClient->pclKindInfoSet->GetName( monkind );

				if ( strMonsterName != NULL )
				{
					SendMessage( m_hMonsterComboList, CB_ADDSTRING, 0, (LPARAM)strMonsterName );
				}
			}

			
		}
	}

	// ����Ʈ �信 �׷��ִ� �κ�
	if( m_hHuntChiefDlg )
	{
		ListView_DeleteAllItems( GetDlgItem( m_hHuntChiefDlg, IDC_LIST_HUNTSTORAGE ) );
		SetInventoryInListView( pclClient->pclItemManager, m_hHuntChiefDlg, IDC_LIST_HUNTSTORAGE, NULL, m_pclHuntStg, MAX_HUNT_STG_NUMBER, true );
	}
	*/
	return;
}

void cltHuntManager::LoadLineUpInfoList()
{
	if( pStrBaseDlg ) {
		bUpdateLineUpInfo = TRUE;
	
	} else {

		ListView_DeleteAllItems( m_hHuntLineUpInfoList );

		memset( m_strListSelectedMonsterName, 0, 64 );
		
		LVITEM LI;

		SI16 Count = 0;
		LI.mask = LVIF_TEXT; // LVIF_IMAGE;
		LI.state = 0;
		LI.stateMask = 0;
		//LI.iImage = -1;
		TCHAR Buffer[ 32 ] = TEXT("");

		for ( int i = 0; i < MAX_HUNT_LINEUP_NUMBER; ++i )
		{
			if ( clClientStrInfo.clHuntStrInfo.clHuntLineUp[ i ].siLineUpKind > 0 )
			{
				LI.iItem = Count++;			
				LI.iSubItem = 0;			
				TCHAR *MonsterName = (TCHAR*)pclClient->pclKindInfoSet->GetName( clClientStrInfo.clHuntStrInfo.clHuntLineUp[ i ].siLineUpKind );
				if ( MonsterName == NULL )
				{
					continue;
				}
				//strcpy( LI.pszText, MonsterName );
				LI.pszText = MonsterName;
				SendMessage( m_hHuntLineUpInfoList, LVM_INSERTITEM, 0, (LPARAM)&LI );
				
				LI.iSubItem = 1;			
				StringCchPrintf( Buffer, 32, TEXT("%d"), clClientStrInfo.clHuntStrInfo.clHuntLineUp[ i ].siLineUpKindLevel );
				//strcpy( LI.pszText, Buffer );
				LI.pszText = Buffer;			

				SendMessage( m_hHuntLineUpInfoList, LVM_SETITEM, 0, (LPARAM)&LI );

				LI.iSubItem = 2;			
				StringCchPrintf( Buffer, 32,  TEXT("%d"), clClientStrInfo.clHuntStrInfo.clHuntLineUp[ i ].siLineUpKindNum );
				//strcpy( LI.pszText, Buffer );
				LI.pszText = Buffer;			
				SendMessage( m_hHuntLineUpInfoList, LVM_SETITEM, 0, (LPARAM)&LI );
			}
		}
	}

	return;
}

// ������ â���� ��� �Ҹ��Ų��. 
void cltHuntManager::WasteStgDoll(SI32 villageunique)
{
	cltStrInfo* pclstr = GetStrInfo( villageunique );
	
	if( pclstr == NULL )
	{
		return;
	}

	SI16 siStorageItemUnique[ MAX_HUNT_LINEUP_NUMBER ];
	SI16 siStorageItemNum[  MAX_HUNT_LINEUP_NUMBER ];
	SI16 siStorageItemIndex[ MAX_HUNT_LINEUP_NUMBER ];

	memset( siStorageItemUnique, 0, sizeof( SI16 ) * MAX_HUNT_LINEUP_NUMBER );
	memset( siStorageItemNum, 0, sizeof( SI16 ) *  MAX_HUNT_LINEUP_NUMBER );
	memset( siStorageItemIndex, 0, sizeof( SI16 ) * MAX_HUNT_LINEUP_NUMBER );

	
	for ( SI16 i = 0; i < MAX_HUNT_LINEUP_NUMBER; ++i )
	{
		if ( pclstr->clHuntStrInfo.clHuntLineUp[ i ].siLineUpKind > 0 )
		{
			for ( SI16 j = 0; j < MAX_HUNT_STG_NUMBER; ++j )
			{
				if ( pclstr->clHuntStrInfo.clHuntStg[ j ].siItemUnique > 0 )
				{
					SI32 Ref = pclClient->pclItemManager->FindItemRefFromUnique( pclstr->clHuntStrInfo.clHuntStg[ j ].siItemUnique );
					if ( Ref > 0 )
					{
						SI32 monkind = pclClient->pclItemManager->pclItemInfo[Ref]->siMakeKind;

						if ( monkind == pclstr->clHuntStrInfo.clHuntLineUp[ i ].siLineUpKind )
						{
							siStorageItemUnique[ i ] = pclstr->clHuntStrInfo.clHuntStg[ j ].siItemUnique;

							//cyj �����������ϳ��� ���� 10�����̹Ƿ�
							siStorageItemNum[ i ] = pclstr->clHuntStrInfo.clHuntLineUp[ i ].siLineUpKindNum / 10;
							siStorageItemIndex[ i ] = j;
							break;
						}
					}
				}
			}
		}
	}

	sDBRequest_HuntStorageDecreaseDollItemNum clMsg( villageunique, siStorageItemUnique, siStorageItemIndex, siStorageItemNum );
	pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
}

bool cltHuntManager::IsHuntLineUpMonsterReady( SI32 VillageUnique )
{
	cltStrInfo* pclstr = GetStrInfo( VillageUnique );
	
	if( pclstr == NULL )
	{
		return false;
	}
	
	SI32 i = 0;
	for( ; i < MAX_HUNT_LINEUP_NUMBER; ++i )
	{
		if ( pclstr->clHuntStrInfo.clHuntLineUp[i].siLineUpKind > 0 )
		{
			break;
		}
	}

	if ( i == MAX_HUNT_LINEUP_NUMBER )
	{		
		return false;
	}


	for ( i =0; i < MAX_HUNT_LINEUP_NUMBER; ++i )
	{
		if ( pclstr->clHuntStrInfo.clHuntLineUp[ i ].siLineUpKind > 0 )
		{
			bool bFindSameKind = false;
			for ( int j = 0; j < MAX_HUNT_STG_NUMBER; ++j )
			{
				SI32 StorageItemUnique = pclstr->clHuntStrInfo.clHuntStg[ j ].siItemUnique;

				if ( StorageItemUnique > 0 )
				{
					SI32 Ref = pclClient->pclItemManager->FindItemRefFromUnique( StorageItemUnique );
					
					if ( Ref > 0 )
					{
						SI32 MonKind = pclClient->pclItemManager->pclItemInfo[ Ref ]->siMakeKind;
						if ( pclstr->clHuntStrInfo.clHuntLineUp[ i ].siLineUpKind == MonKind )
						{
							bFindSameKind = true;
							if ( pclstr->clHuntStrInfo.clHuntLineUp[ i ].siLineUpKindNum > pclstr->clHuntStrInfo.clHuntStg[ j ].siItemNum )
							{
								return false;
							}
						}						
					}
				}
			}

			if ( bFindSameKind == false )
			{
				return false;
			}
		}
	}			

	return true;
}

void cltHuntManager::RecoverDollItem( SI32 VillageUnique, SI16 *pItemDataList )		// pItemDataList[0] = ItemUnique, pItemDataList[1] = ItemNum
{
	cltStrInfo* pclstr = GetStrInfo( VillageUnique );
	
	if( pclstr == NULL )
	{
		return;
	}

	for ( SI16 i = 0; i < MAX_HUNT_LINEUP_NUMBER; ++i )
	{
		if (pItemDataList[ i * 2] > 0)
		{
			//cyj �����������ϳ��� ���� 10���� �����̹Ƿ�
			pItemDataList[ i * 2 + 1] = pItemDataList[ i * 2 + 1] / 10;
		}
	}

	SI16 InputListIndex = -1;

	for ( SI16 i = 0; i < MAX_HUNT_LINEUP_NUMBER; ++i )
	{
		if ( pItemDataList[ i * 2 ] > 0 )
		{
			InputListIndex = -1;
			for ( SI16 j = 0; j < MAX_HUNT_STG_NUMBER; ++j )
			{
				// ������ ���� ���� ã����.
				if ( pclstr->clHuntStrInfo.clHuntStg[ j ].siItemUnique == pItemDataList[ i * 2 ] )
				{
					// �����ۿ� �߰��Ҽ� ����.
					if ( pclstr->clHuntStrInfo.clHuntStg[ j ].siItemNum < MAX_ITEM_PILE_NUMBER )
					{
						if ( pclstr->clHuntStrInfo.clHuntStg[ j ].siItemNum + pItemDataList[ i * 2 + 1 ] > MAX_ITEM_PILE_NUMBER )
						{
							pItemDataList[ i * 2 + 1 ] = MAX_ITEM_PILE_NUMBER - pclstr->clHuntStrInfo.clHuntStg[ j ].siItemNum;
						}
						InputListIndex = j;
						break;
					}
					else
					{
						InputListIndex = -1;
						break;
					}
				}
				// ������ ���� �� �����̸鼭, �������� �� ������ �� ã�� ���
				else if ( InputListIndex < 0 && pclstr->clHuntStrInfo.clHuntStg[ j ].siItemUnique < 1 )
				{
					InputListIndex = j;
					continue;
				}
			}
			
			if ( InputListIndex > -1 )
			{
				sDBRequest_HuntLeftMonsterStgIn clMsg( VillageUnique, InputListIndex, pItemDataList[ i * 2 ], pItemDataList[ i * 2 + 1 ] );
				pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
			}
		}
	}
	
	return;
}