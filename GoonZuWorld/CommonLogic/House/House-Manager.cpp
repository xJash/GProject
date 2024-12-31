//---------------------------------
// 2003/6/26 ���°�
//---------------------------------
//-------------------------------
// CommonLogic
//--------------------------------
#include <CommonLogic.h>
#include "MsgType-Structure.h"
#include "CityHall/TaxpaymentListDlg.h"
#include "House.h"
#include "MsgRval-Define.h"

#include "..\..\GoonZuWorld\Resource.h"

//--------------------------------
// Common
//--------------------------------
#include "Char\CharCommon\Char-Common.h"
#include "Char\CharManager\CharManager.h"

//---------------------------------
// Server
//---------------------------------
#include "Server.h"
#include "Statistics\Statistics.h"


//---------------------------------
// DBManager
//---------------------------------
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-House.h"


//--------------------------------
// Lib
//--------------------------------
#include "../../Lib/HashTable/HashTable_StringInt.h"



extern cltCommonLogic* pclClient;

cltHouseManager::cltHouseManager(cltCharManager* pclcm, SI32 gamemode, SI32 ranktype, TCHAR *strFileName ) : cltStructureMngBasic(MAX_HOUSE_TAB_NUMBER, pclcm, ranktype, strFileName )
{
	UpdateRentContractShowSwitch		= FALSE;
	bUpdateHouseUnitListShowChiefSwitch	= false;
	bUpdateHouseUnitListShowSwitch		= false;
	UpdateHouseVarySwitch				= FALSE;
	UpdateHouseApplyerListShowSwitch	= FALSE;

	CurrentSelectedHouseUnitSlot	= -1;
	CurrentSelectedApplyerSlot		= -1;
	siSelectedHouseUnitNumber		= -1;

	hImageList						= NULL;

}

cltHouseManager::~cltHouseManager()
{
}

// ������ �ż��Ѵ�.
SI32 cltHouseManager::CreateHouse(SI32 siunique)
{
	if(pclStruct[siunique] == NULL)
	{
		pclStruct[siunique] = new cltHouse(siunique);
		return siunique;
	}
	
	return 0;
}


// ���� ȯ�� �λ縻ǥ�� . 
void cltHouseManager::GreetingMsg(HWND hDlg)
{
	TCHAR* pText = GetTxtFromMgr(1698);
	SetMainExplain(hDlg, pText);
}

void cltHouseManager::Do_WM_INITDIALOG(SI32 charunique)
{
	cltStructureMngBasic::Do_WM_INITDIALOG(charunique);
}

// Ư�� ������ ��������� �����Ѵ�. 
BOOL cltHouseManager::SetRentContract(SI32 villageunique, const cltRentContract* pclcontract)
{
	if(pclStruct[villageunique])
	{
		return pclStruct[villageunique]->SetRentContract(pclcontract);
	}
	return FALSE;
}

// Ư�� ���������� Ư�� ���� ������ ���´�.
cltHouseUnit* cltHouseManager::GetHouseUnit(SI32 villageunique, SI32 houseunitslot )
{
	if(pclStruct[villageunique])
	{
		return pclStruct[villageunique]->GetHouseUnit(houseunitslot);
	}
	return NULL;
}

// ������ ȸ���Ѵ�. 
void cltHouseManager::RecallHouse(SI32 villageunique, SI32 houseindex)
{
	if(villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER)return ;

	cltHouse* pclhouse = (cltHouse*)pclStruct[villageunique];
	if(pclhouse == NULL)return ;

	// ���������� �ʱ�ȭ�Ѵ�. 
	pclhouse->clUnit[houseindex].Init();

}

BOOL cltHouseManager::IsSameContract(SI32 sivillageunique, const cltRentContract*pclcontract)
{
	return pclStruct[sivillageunique]->IsSameContract(pclcontract);
}

// ������û�ڸ� ����Ѵ�. 
BOOL cltHouseManager::AddApplyer(SI32 sivillageunique, const cltSimplePerson* pclapplyer, const cltRentContract* pclcontract )
{
	return pclStruct[sivillageunique]->AddApplyer(pclapplyer, pclcontract);
}

// ���� ��û�ڸ� �����Ѵ�. 
BOOL cltHouseManager::DeleteApplyer(SI32 sivillageunique, SI32 personid)
{
	return pclStruct[sivillageunique]->DeleteApplyer(personid);
}

// �������� ���θ� Ȯ���Ѵ�. 
BOOL cltHouseManager::IsEmpty(SI32 sivillageunique, SI32 slot)
{
	return pclStruct[sivillageunique]->IsEmpty(slot);
}

//PersonID�� ������ ������� ������ ���Ѵ�. 
cltRentApplyer* cltHouseManager::GetHouseApplyerFromPersonID(SI32 sivillageunique, SI32 personid)
{
	return pclStruct[sivillageunique]->GetHouseApplyerFromPersonID(personid);
}

// �������� ������ ����Ѵ�.
BOOL cltHouseManager::SetRent(SI32 sivillageunique, SI32 slot, const cltSimplePerson* pclapplyer, const cltRentContract* pclcontract, const TCHAR* pszHouseName)
{
	if( NULL != pszHouseName)
	{
		cltHouseUnit* pclHouseUnit = GetHouseUnit(sivillageunique, slot);
		StringCchCopy(pclHouseUnit->m_szName, MAX_PLAYER_NAME, pszHouseName);
	}
	
	return pclStruct[sivillageunique]->SetRent(slot, pclapplyer, pclcontract);
}

// Ư�� Person�� ���� ������ �������� Ȯ���Ѵ�. 
bool cltHouseManager::IsHouseHost(SI32 personid, SI32 villageunique, SI32 houseunitslot)
{
	if(villageunique < 0 || villageunique >= MAX_VILLAGE_NUMBER)return false;

	if(pclStruct[villageunique] == NULL)return false;

	return pclStruct[villageunique]->IsHouseHost(personid, houseunitslot);

}

// â��  �������� �߰��� �� �ִ��� Ȯ���Ѵ�. 
bool cltHouseManager::CanAddStg(SI32 villageunique, SI32 houseunitslot, cltItemManagerCommon* pclItemManager, cltItem* pclitem, SI32* pitempos)
{
	if(villageunique < 0 || villageunique >= MAX_VILLAGE_NUMBER)return false;

	if(pclStruct[villageunique] == NULL)return false;

	return pclStruct[villageunique]->CanAddStg(houseunitslot, pclItemManager, pclitem, pitempos);

}

// �������� â�� �ִ´�.
void cltHouseManager::SetItemStg(SI32 villageunique, SI32 houseunitslot, SI32 stgpos, cltItem* pclitem)
{
	if(villageunique < 0 || villageunique >= MAX_VILLAGE_NUMBER)return ;

	if(pclStruct[villageunique] == NULL)return ;

	pclStruct[villageunique]->SetItemStg(houseunitslot, stgpos, pclitem);

}

// â�� �������� �����͸� ���Ѵ�. 
cltItem* cltHouseManager::GetStgItemPointer(SI32 villageunique, SI32 houseunitslot, SI32 stgpos)
{
	if(villageunique < 0 || villageunique >= MAX_VILLAGE_NUMBER)return NULL;

	if(pclStruct[villageunique] == NULL)return NULL;

	return pclStruct[villageunique]->GetStgItemPointer(houseunitslot, stgpos);
}

// â���� �����͸� ���Ѵ�. 
cltHouseUnitStorageInfo* cltHouseManager::GetStgPointer(SI32 villageunique, SI32 houseunitslot)
{
	if(villageunique < 0 || villageunique >= MAX_VILLAGE_NUMBER)return NULL;

	if(pclStruct[villageunique] == NULL)return NULL;

	return pclStruct[villageunique]->GetStgPointer(houseunitslot);
}


// �Ӵ�Ḧ ó���ϴµ��� �׼��� ���Ѵ�. 
void cltHouseManager::Action( cltTime* pcltime, clock_t CurrentClock )
{
	if(pcltime == NULL)return ;

	// DB �ʱ�ȭ �Ϸ�ɶ����� ��ٸ�
	if( ((cltServer *)pclClient)->bCompleteDBInitAll == FALSE ) return;

	bool bdaychangedswitch = pcltime->IsDayChanged();
	
	static DWORD dwHouseStableHorseClock = 0;
	cltServer *pclserver = ( cltServer *)pclClient;

	//----------------------------------------
	// �� ���� ��ġ�� ���Ѵ�.
	//----------------------------------------	
	if ( TABS( CurrentClock - dwHouseStableHorseClock ) > 30000 )
	{
		dwHouseStableHorseClock = CurrentClock;
		
		SI32 i, j, k;
		cltHouse* pclHouse = NULL;

		for( i = 0; i < MAX_VILLAGE_NUMBER; ++i )
		{
			pclHouse = (cltHouse*)pclStruct[i];
			if ( pclHouse )
			{
				for(j = 0;j < MAX_HOUSEUNIT_NUMBER; ++j)
				{
					SI32 id, PersonID;

					if ( pclHouse->clUnit[j].clPerson.szName != NULL && _tcslen( pclHouse->clUnit[j].clPerson.szName ) > 0 )
					{
						if ( pclserver->pclHashTable->Find( pclHouse->clUnit[j].clPerson.szName, PersonID, id, 300 ) == false  )
						{
							continue;
						}
					}
					else
					{
						continue;
					}
					
					for ( k = 0; k < MAX_HOUSEUNIT_HORSENUMBER; ++k  )
					{
						if ( pclHouse->clUnit[j].clStorageInfo.clHorse[ k ].siHorseUnique > 0 )
						{
							cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[id];

							SI32 horseaction = pclchar->CharHorseAction( &pclHouse->clUnit[j].clStorageInfo.clHorse[ k ] , false);
							if(horseaction == HORSEACTION_UPDATE)
							{
								sDBRequest_HouseUnitHorseInfoSet clMsg( id, PersonID, i, j, k, &pclHouse->clUnit[j].clStorageInfo.clHorse[ k ] );
								pclClient->SendDBMsg(DBSELECT_BASE,  (sPacketHeader*)&clMsg );
							}
							
							SI32 ItemUnique = 0;
							SI32 ItemNum = 0;
							SI16 l = 0;
							if ( pclserver->pclHorseManager->GetHorseFoodNeed(&pclHouse->clUnit[j].clStorageInfo.clHorse[ k ],  &ItemUnique, &ItemNum ) )
							{
								SI16 ItemIndex = -1;
								cltItem clItem;
								clItem.Init();
								
								bool bFindHorseFeed = false;
								
								for ( l = 0; l < MAX_HOUSEUNIT_STORAGE_ITEM_NUMBER; ++l )
								{
									if ( pclHouse->clUnit[j].clStorageInfo.clItem[ l ].siUnique == ITEMUNIQUE(3855) )
									{
										if ( pclHouse->clUnit[j].clStorageInfo.clItem[ l ].siItemNum < ItemNum )
										{
											ItemNum = pclHouse->clUnit[j].clStorageInfo.clItem[ l ].siItemNum;
											
											clItem.siUnique = ITEMUNIQUE(3855);
											clItem.siItemNum = 1;
										}
										else
										{
											clItem.siUnique = ITEMUNIQUE(3855);
											clItem.siItemNum = 1;
										}

										bFindHorseFeed = true;

										break;
									}
								}

								if ( bFindHorseFeed == false )
								{
									for ( l = 0; l < MAX_HOUSEUNIT_STORAGE_ITEM_NUMBER; ++l )
									{
										if ( pclHouse->clUnit[j].clStorageInfo.clItem[ l ].siUnique == ITEMUNIQUE(3850) )
										{
											if ( pclHouse->clUnit[j].clStorageInfo.clItem[ l ].siItemNum < ItemNum )
											{
												ItemNum = pclHouse->clUnit[j].clStorageInfo.clItem[ l ].siItemNum;

												clItem.siUnique = ITEMUNIQUE(3850);
												clItem.siItemNum = 1;
											}
											else
											{
												clItem.siUnique = ITEMUNIQUE(3850);
												clItem.siItemNum = 1;
											}

											bFindHorseFeed = true;

											break;
										}
									}
								}

								if ( bFindHorseFeed == false )
								{
									for ( l = 0; l < MAX_HOUSEUNIT_STORAGE_ITEM_NUMBER; ++l )
									{
										if ( pclHouse->clUnit[j].clStorageInfo.clItem[ l ].siUnique == ItemUnique )
										{
											if ( pclHouse->clUnit[j].clStorageInfo.clItem[ l ].siItemNum < ItemNum )
											{
												ItemNum = pclHouse->clUnit[j].clStorageInfo.clItem[ l ].siItemNum;
												
												clItem.siUnique = ItemUnique;
												clItem.siItemNum = ItemNum;
											}
											else
											{
												clItem.siUnique = ItemUnique;
												clItem.siItemNum = ItemNum;
											}
											break;
										}
									}
									
									if ( l == MAX_HOUSEUNIT_STORAGE_ITEM_NUMBER )
									{
										continue;
									}
								}
								
								ItemIndex = l;

								if ( pclserver->pclHorseManager->GiveFood(&pclHouse->clUnit[j].clStorageInfo.clHorse[ k ],  &clItem ) )
								{
									sDBRequest_HouseUnitHorseInfoSet clMsg( id, PersonID, i, j, k, &pclHouse->clUnit[j].clStorageInfo.clHorse[ k ] );
									pclClient->SendDBMsg(DBSELECT_BASE,  (sPacketHeader*)&clMsg );
									
									sDBRequest_HouseUnitHorseEatFood clMsg1( id, PersonID, i, j, ItemIndex, clItem.siUnique, clItem.siItemNum );
									pclClient->SendDBMsg(DBSELECT_BASE,  (sPacketHeader*)&clMsg1 );
								}
							}
						}
						else
						{
							continue;
						}
					}
				}
			}
		}
	}
	


	//----------------------------------------
	// ���� �Ӵ���� ó���Ѵ�. 
	//----------------------------------------
	if(bdaychangedswitch)
	{
		SI32 i, j;
		
		cltHouse* pclHouse ;
		
		// ��踦 ���� �غ� �Ѵ�. 
		cltServer* pclserver = (cltServer*)pclClient;
		pclserver->pclStatisticsManager->clDailyStatistics.siTotalHouseNumber	= 0;
		pclserver->pclStatisticsManager->clDailyStatistics.siRentHouseNumber		= 0;

		for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
		{
			pclHouse = (cltHouse*)pclStruct[i];
			if(pclHouse)
			{
				for(j = 0;j < MAX_HOUSEUNIT_NUMBER;j++)
				{
					SI32 personid = pclHouse->clUnit[j].clPerson.GetPersonID(); 

					//  ��ü ���� ������ ���Ѵ�. 
					pclserver->pclStatisticsManager->clDailyStatistics.siTotalHouseNumber++;
					
					if(personid <= 0)continue;

					// �Ӵ�� ���� ������ ���Ѵ�. 
					pclserver->pclStatisticsManager->clDailyStatistics.siRentHouseNumber++;

					
					// ��� ���ڰ� ���ð� ���� ���̾�� �Ѵ�. (�ſ� ����Ͽ� ���ҵȴ�.)
					if( pcltime->clDate.uiDay != (UI32)pclHouse->clUnit[j].clContract.clDate.GetDay())continue;
					
					// �Ӵ�Ḧ ���Ѵ�. 
					GMONEY rentfee		= pclHouse->clUnit[j].clContract.siRentFee;
					// ������ ����ũ�� ���Ѵ�. 
					SI32 villageunique	= i;
					// ���� ������ ��ġ�� ���Ѵ�. 
					SI32 houseindex		= j;
					
					// ���忡�� �Ӵ�Ḧ �������� �ű���� DBManager���� ��û�Ѵ�. 
					sDBRequest_PayRentFee clMsg(0, personid, rentfee, villageunique, houseindex);
					pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

					pclserver->pclDelMoneyStatistics->Add(DELMONEY_SERVICECHARGE, rentfee);

					// ��� �Ⱓ�� ����Ǿ����� Ȯ���Ѵ�. 
					if(pclHouse->clUnit[j].clContract.IsEnd(&pcltime->clDate) == true)
					{
						// DB�Ŵ������� ������ ȸ���� ���� ��û�Ѵ�. 
						sDBRequest_RecallHouse clMsg(personid, HOUSERECALL_REASON_CONTRACTEND, villageunique, houseindex);
						pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);						
					}
					else
					{
						//----------------------------------------------
						// ��� ���� �ӹ� ����. 
						//----------------------------------------------
						// ���� �ð� ����. 
						SI32 curvary	= pcltime->clDate.GetDateVary();
						
						// ��� ������ ����. 
						cltDate cldate;
						cldate.Set(&pclHouse->clUnit[j].clContract.clDate);
						cldate.AddMonth(pclHouse->clUnit[j].clContract.siRentPeriod * 12);
						
						SI32 endvary	= cldate.GetDateVary();
						if(endvary <= curvary + 90)
						{
							// ������ ������. 
							cltServer* pclserver = (cltServer*)pclClient;
							cltLetterMsg_HouseRecallWarning clletter(villageunique, houseindex, (endvary - curvary)/30);
							pclserver->SendLetterMsg(personid, (cltLetterHeader*)&clletter);
						}
						
					}

				}
				
			}
		}

	}
}


// ���Ӽ����� ���������� ����Ʈ�� ��û�Ѵ�. 
void cltHouseManager::RequestHouseUnitList()
{
	SI32 id = 1;
	if(id == 0)return;

	cltMsg clMsg(GAMEMSG_REQUEST_HOUSEUNITLIST, siVillageUnique);
	pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

}

// ���Ӽ����� ���������� �� ���� ����Ʈ�� ��û�Ѵ�. 
void cltHouseManager::RequestHouseUnitListDetail()
{
	SI32 id = 1;
	if(id == 0)return;

	cltMsg clMsg(GAMEMSG_REQUEST_HOUSEUNITLIST_DETAIL, siVillageUnique);
	pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

}


// ���Ӽ����� ��������� ����Ʈ�� ��û�Ѵ�. 
void cltHouseManager::RequestHouseRentApplyerList()
{
	SI32 id = 1;
	if(id == 0)return;

	cltMsg clMsg(GAMEMSG_REQUEST_HOUSEAPPLYERLIST, siVillageUnique);
	pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
}


// ���� ���ϰ� ó�� �Լ�. 
void cltHouseManager::ServerRtnValOperate()
{
	// ���� �����κ��� ���� �޽����� ������ �д�. 
	SI32 returnval = siServerResponseValue;

	cltStructureMngBasic::ServerRtnValOperate();
	cltClient* pclclient = (cltClient*)pclClient;

	switch(returnval)
	{
		// �Ӵ밡 ������ ��� ���ø���Ʈ�� �Ӵ��û�� ����Ʈ�� ������ ��û�Ѵ�. 
	case SRVAL_HOUSE_SUCCESSHOUSERENT:
		{
	
			// �������� ����Ʈ ��û. 
			RequestHouseUnitList();
			// ���� ����� ��� ��û. 
			RequestHouseRentApplyerList();
		}	
		break;
	case SRVAL_HOUSE_SUCCESSCANCELLATION:
		{
		
			RequestHouseUnitList();
		}
		break;
	}
}

