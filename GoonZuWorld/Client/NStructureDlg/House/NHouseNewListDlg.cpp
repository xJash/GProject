#include "NHouseDlg.h"

#include "../../InterfaceMgr/Interface/List.h"
#include "../../InterfaceMgr/Interface/Button.h"
#include "../../InterfaceMgr/InterfaceMgr.h"

#include "Char\CharManager\CharManager.h"
#include "..\..\Server\Rank\Rank.h"

#include "../../CommonLogic/MsgType.h"
#include "../../CommonLogic/MsgType-Structure.h"

#include "../Lib/JYLibFunction.h"
#include "..\..\Client\Music\Music.h"
#include "../Client/NStructureDlg/House/UserInfo/NHouseUserInfoBaseDlg.h"
#include "../Client/NStructureDlg/House/NHouseExtensionDlg.h"
#include "../Client/NStructureDlg/House/NHouseNameChangeDlg.h"
#include "../CommonLogic/MsgType-House.h"

extern cltCommonLogic* pclClient;
extern CJYLibFunction g_JYLibFunction;

NHouseNewListDlg::NHouseNewListDlg()
{
}

NHouseNewListDlg::~NHouseNewListDlg()
{

}

void NHouseNewListDlg::InitDlg()
{
	cltHouseManager *pHouseManager = ((cltHouseManager *)m_pStrManager);

	SetControlMap( LIST_HOUSELIST, TEXT("listbox_houselist") );
	SetControlMap( BUTTON_ENTER, TEXT("button_enter") );
	SetControlMap( BUTTON_CANCELLATION_HOUSE, TEXT("button_recall_house") );
	// PCK - ��â�� ��� ���� �߰� (08.07.09)
	SetControlMap( LIST_MYHOUSELIST, TEXT("listbox_myhouselist"));

	SetControlMap( BUTTON_CHANGEHOUSENAME, TEXT("button_ChangName"));
	SetControlMap( BUTTON_EXTENSION, TEXT("button_Period"));
		
	CButton *pButton = (CButton*)m_pControlMap[ BUTTON_CANCELLATION_HOUSE ];
	pButton->Enable(FALSE);
	pButton = (CButton*)m_pControlMap[ BUTTON_ENTER ];
	pButton->Enable(FALSE);
	CButton* pChangeNameButton = (CButton *)m_pControlMap[BUTTON_CHANGEHOUSENAME];
	CButton* pExtensionButton = (CButton *)m_pControlMap[BUTTON_EXTENSION];
	pChangeNameButton->Enable(FALSE);
	pExtensionButton->Enable(FALSE);
	// ����Ʈ 
	CList *pList = (CList*)m_pControlMap[ LIST_HOUSELIST ];
	CList *pMyList = (CList*)m_pControlMap[ LIST_MYHOUSELIST ];

	pList->SetBorder(true);
	pList->SetBKColorUse(true);

	pMyList->SetBorder(true);
	pMyList->SetBKColorUse(true);

	TCHAR* pText = GetTxtFromMgr(1695);
	pList->SetColumn( 0, 53, pText );
	pMyList->SetColumn( 0, 53, pText );
	pText = GetTxtFromMgr(1696);
	pList->SetColumn( 1, 115, pText );//����ڸ���Ʈ ������.[2007.06.29 ����]
	pText = GetTxtFromMgr(40372);
	pMyList->SetColumn( 1, 100, pText );
	pText = GetTxtFromMgr(1697);
	pList->SetColumn( 2, 148, pText );// ������ by LeeKH 2007.07.30
	pText = GetTxtFromMgr(8763);
	pMyList->SetColumn( 2, 115, pText );
	pText = GetTxtFromMgr(1697);
	pMyList->SetColumn( 3, 68, pText );

	pList->Refresh();
	pMyList->Refresh();

	//-------------------------------------
	// ������ ��������Ʈ�� ��û�Ѵ�. 
	//-------------------------------------
	cltMsg clMsg( GAMEMSG_REQUEST_HOUSEUNITLIST, pHouseManager->siVillageUnique );
	pclClient->pclCM->CR[1]->SendNetMsg((sPacketHeader*)&clMsg );

	pHouseManager->siSelectedHouseUnitNumber = -1;

}

void NHouseNewListDlg::Action()
{
	cltHouseManager *pHouseManager = ((cltHouseManager *)m_pStrManager);

	if( pHouseManager->bUpdateHouseUnitListShowSwitch == true )
	{
		pHouseManager->bUpdateHouseUnitListShowSwitch = false;

		// ��������Ʈ�� �����ش�. 
		ShowHouseUnitList();
	}
}


void NHouseNewListDlg::ShowHouseUnitList()
{
	cltHouseManager *pHouseManager = ((cltHouseManager *)m_pStrManager);
	CList *pList = (CList*)m_pControlMap[ LIST_HOUSELIST ];
	CList *pMyList = (CList*)m_pControlMap[ LIST_MYHOUSELIST ];
	stListBoxItemData itemdata;
	stListBoxItemData stMyItemData;

	SI32 i;
	TCHAR buffer[256];

	// ����Ʈ�並 ��� �����. 
	pList->Clear();
	pMyList->Clear();

	for( i = 0; i < MAX_HOUSEUNIT_NUMBER; i++ )
	{
		itemdata.Init();
		stMyItemData.Init();

		StringCchPrintf(buffer, 256, TEXT("%d"), i+1);

		itemdata.siParam[0] = i;
		itemdata.Set( 0, buffer );

		stMyItemData.siParam[0] = i;
		stMyItemData.Set( 0, buffer );

		// [����-090525] �ϴ� ����ڰ� �ִ��� üũ.
		if( pHouseManager->clClientUnit[i].clPerson.GetPersonID() )
		{
			// ������(GAMEMSG_REQUEST_HOUSEUNITLIST)��������Ʈ�� ��û�ϸ� �Ǹ����� ���������� ���� �������� houseUnit�� ���ԵǾ� ����´� 
			itemdata.Set( 1, (TCHAR*)pHouseManager->clClientUnit[i].clPerson.GetName() );

			if( pHouseManager->clClientUnit[i].bSell == true )
			{
				TCHAR* pText = NULL;
				pText = GetTxtFromMgr(30104);
				itemdata.Set( 2, pText );
				stMyItemData.Set( 3, pText );
			}
			else // ����ڰ� �ִٴ°� �Ӵ����̶�� ���̰�, �Ǹ������� ������ üũ�����Ƿ� ������� �Դٴ� ���� ������ �Ӵ����̶�� ��.
			{
				TCHAR* pText = NULL;
				pText = GetTxtFromMgr(7532);
				itemdata.Set( 2, pText );
				stMyItemData.Set( 3, pText );
			}

			//����ڰ� �����, ������ �����ִ� ����Ʈ���� �߰��ϰ�, ����ڰ� ���� �ƴ϶�� ��ü ����Ʈ���� �߰�.
			if( pHouseManager->clClientUnit[i].clPerson.GetPersonID() == pclClient->pclCM->CR[1]->pclCI->GetPersonID() )
			{
				stMyItemData.Set( 1 , (TCHAR*)pHouseManager->clClientUnit[i].m_szName);

				cltDate& rclDate = pHouseManager->clClientUnit[i].clContract.clDate;
				
				TCHAR szDate[MAX_PATH] = {0,};
				
				SI32 siYear = pHouseManager->clClientUnit[i].clContract.siRentPeriod + rclDate.uiYear;

				StringCchPrintf(szDate, MAX_PATH , GetTxtFromMgr(3808), 
					siYear , 
					rclDate.uiMonth , 
					rclDate.uiDay ,
					rclDate.uiHour);
				
				stMyItemData.Set( 2 , szDate);

				pMyList->AddItem( &stMyItemData );
			}

			pList->AddItem( &itemdata );
		}
		else // ����ڰ� ������
		{
			TCHAR* pText = NULL;
			pText = GetTxtFromMgr(1691);	// ����ڰ� ���� �� â���� ��. 1�� �÷����� "��â��" ��� ���ڿ��� �־��ش�.
			itemdata.Set( 1, pText );

			pList->AddItem( &itemdata );
		}
	}

	
    // ����----------------------------------------------------------------------------------------
	//for( i = 0; i < MAX_HOUSEUNIT_NUMBER; i++ )
	//{ 
	//	itemdata.Init();

	//	StringCchPrintf(buffer, 256, TEXT("%d"), i+1);

	//	itemdata.siParam[0] = i;
	//	itemdata.Set( 0, buffer );

	//	if( pHouseManager->clClientUnit[i].clPerson.GetPersonID() )
	//	{
	//		// PersonID�� ���� �ڱ� ĳ���Ϳ� ������ ��â�� ��Ͽ��� ����ش�. - PCK(08.07.09)
	//		if(pHouseManager->clClientUnit[i].clPerson.GetPersonID() == pclClient->pclCM->CR[1]->pclCI->GetPersonID())
	//		{
	//			itemdata.Set( 1, (TCHAR*)pHouseManager->clClientUnit[i].clPerson.GetName() );

	//			if ( ConstServiceArea_China != pclClient->siServiceArea )
	//			{		
	//				TCHAR* pText;
	//				pText = GetTxtFromMgr(7532);
	//				itemdata.Set( 2, pText );
	//			}

	//			pMyList->AddItem( &itemdata);
	//		}

	//		itemdata.Set( 1, (TCHAR*)pHouseManager->clClientUnit[i].clPerson.GetName() );
	//		if ( ConstServiceArea_China != pclClient->siServiceArea )
	//		{		
	//			TCHAR* pText;
	//			pText = GetTxtFromMgr(7532);
	//			itemdata.Set( 2, pText );
	//		}
	//	}
	//	else
	//	{
	//		TCHAR* pText = GetTxtFromMgr(1691);
	//		itemdata.Set( 1, pText );
	//	}

	//	pList->AddItem( &itemdata );
	//}
	// ����----------------------------------------------------------------------------------------

	pList->Refresh();
	pMyList->Refresh();
}

void NHouseNewListDlg::NDlgTabProc( UINT nEvent, int nControlID, CControllerObj *pControl )
{
	cltHouseManager *pHouseManager = ((cltHouseManager *)m_pStrManager);
	CList *pList = (CList*)m_pControlMap[ LIST_HOUSELIST ];
	CList *pMyList = (CList*)m_pControlMap[ LIST_MYHOUSELIST ];
	cltClient* pclclient = (cltClient*)pclClient;

	CASE_CONTROL( LIST_HOUSELIST )
	{
		switch( nEvent )
		{
		case EVENT_LISTBOX_SELECTION:
			{			
				int index = pList->GetSelectedIndex();

				if( index < 0 ) return;

				stListBoxItemData *pItemData = pList->GetItemData( index, 0 );

				pHouseManager->siSelectedHouseUnitNumber = pItemData->siParam[0];

				TCHAR* pText = pItemData->strText[1]; 
				CButton* pEnerButton = (CButton *)m_pControlMap[BUTTON_ENTER];
				CButton* pCancellationButton = (CButton *)m_pControlMap[BUTTON_CANCELLATION_HOUSE];
				CButton* pChangeNameButton = (CButton *)m_pControlMap[BUTTON_CHANGEHOUSENAME];
				CButton* pExtensionButton = (CButton *)m_pControlMap[BUTTON_EXTENSION];
				
				if( !_tcscmp(pclClient->pclCM->CR[ 1 ]->GetName() , pText )) 
				{
					pEnerButton->Enable(TRUE);
					pCancellationButton->Enable(TRUE);
					pChangeNameButton->Enable(TRUE);
					pExtensionButton->Enable(TRUE);
				}
				else
				{
					pEnerButton->Enable(FALSE);
					pCancellationButton->Enable(FALSE);
					pChangeNameButton->Enable(FALSE);
					pExtensionButton->Enable(FALSE);
				}

				pMyList->ClearSelectIndex();
			}
			break;
		}
	}
	CASE_CONTROL( LIST_MYHOUSELIST )
	{
		switch( nEvent )
		{
		case EVENT_LISTBOX_SELECTION:
			{
				int index = pMyList->GetSelectedIndex();

				if( index < 0 ) return;

				stListBoxItemData *pItemData = pMyList->GetItemData( index, 0 );

				pHouseManager->siSelectedHouseUnitNumber = pItemData->siParam[0];

				TCHAR* pText = pItemData->strText[1]; 
				CButton* pEnerButton = (CButton *)m_pControlMap[BUTTON_ENTER];
				CButton* pCancellationButton = (CButton *)m_pControlMap[BUTTON_CANCELLATION_HOUSE];
				CButton* pChangeNameButton = (CButton *)m_pControlMap[BUTTON_CHANGEHOUSENAME];
				CButton* pExtensionButton = (CButton *)m_pControlMap[BUTTON_EXTENSION];
			
				if( pHouseManager->siSelectedHouseUnitNumber >= 0 && pHouseManager->siSelectedHouseUnitNumber < MAX_HOUSEUNIT_NUMBER) 
				{
					pEnerButton->Enable(TRUE);
					pCancellationButton->Enable(TRUE);
					pChangeNameButton->Enable(TRUE);
					pExtensionButton->Enable(TRUE);
				}
				else
				{
					pEnerButton->Enable(FALSE);
					pCancellationButton->Enable(FALSE);
					pChangeNameButton->Enable(FALSE);
					pExtensionButton->Enable(FALSE);
				}

				pList->ClearSelectIndex();
			}
			break;
		}
	}
	else CASE_CONTROL( BUTTON_CHANGEHOUSENAME)
	{	
		cltHouseUnit& rclHouseUnit = pHouseManager->clClientUnit[pHouseManager->siSelectedHouseUnitNumber];

		if(pclclient->m_pDialog[NHOUSENAMECHANGE_DLG ] != NULL)
			((CNHouseNameChangeDlg*)pclclient->m_pDialog[NHOUSENAMECHANGE_DLG])->DeleteDialog();

		pclclient->CreateInterface(NHOUSENAMECHANGE_DLG);
		if(pclclient->m_pDialog[NHOUSENAMECHANGE_DLG ] != NULL)
		{
			((CNHouseNameChangeDlg*)pclclient->m_pDialog[NHOUSENAMECHANGE_DLG])->SetVillageUnique(pHouseManager->siVillageUnique);
			((CNHouseNameChangeDlg*)pclclient->m_pDialog[NHOUSENAMECHANGE_DLG])->SetHouseUnitIndex(pHouseManager->siSelectedHouseUnitNumber);
			((CNHouseNameChangeDlg*)pclclient->m_pDialog[NHOUSENAMECHANGE_DLG])->SetOldHouseName(rclHouseUnit.m_szName);
		}
	}
	else CASE_CONTROL( BUTTON_EXTENSION)
	{
		cltRentContract& pclContract = pclclient->pclHouseManager->clClientStrInfo.clHouseStrInfo.clRentContract;

		NTCHARString1024 pBody(GetTxtFromMgr(40370));	

		TCHAR szMoney[MAX_PATH] = {0,};
		TCHAR szCYear[MAX_PATH] = {0,};
		TCHAR szYear[MAX_PATH] = {0,};
		TCHAR szMonth[MAX_PATH] = {0,};
		TCHAR szDay[MAX_PATH] = {0,};
		TCHAR szHour[MAX_PATH] = {0,};

		StringCchPrintf(szMoney, MAX_PATH, TEXT("%d"), pclContract.siRentFee);
		StringCchPrintf(szCYear, MAX_PATH, TEXT("%d"), pclContract.siRentPeriod);
		StringCchPrintf(szYear, MAX_PATH, TEXT("%d"), pclclient->clClientDate.uiYear + pclContract.siRentPeriod);
		StringCchPrintf(szMonth, MAX_PATH, TEXT("%d"), pclclient->clClientDate.uiMonth);
		StringCchPrintf(szDay, MAX_PATH, TEXT("%d"), pclclient->clClientDate.uiDay);
		StringCchPrintf(szHour, MAX_PATH, TEXT("%d"), pclclient->clClientDate.uiHour);

		pBody.Replace("#money#", szMoney);
		pBody.Replace("#cyear#", szCYear);
		pBody.Replace("#year#", szYear);
		pBody.Replace("#month#", szMonth);
		pBody.Replace("#day#", szDay);
		pBody.Replace("#hour#", szHour);

		if(pclclient->m_pDialog[NHOUSEEXTENSION_DLG ] != NULL)
			((CNHouseExtensionDlg*)pclclient->m_pDialog[NHOUSEEXTENSION_DLG])->DeleteDialog();

		pclclient->CreateInterface(NHOUSEEXTENSION_DLG);
		if(pclclient->m_pDialog[NHOUSEEXTENSION_DLG ] != NULL)
		{
			((CNHouseExtensionDlg*)pclclient->m_pDialog[NHOUSEEXTENSION_DLG])->SetExtensionInfoText(pBody);
			((CNHouseExtensionDlg*)pclclient->m_pDialog[NHOUSEEXTENSION_DLG])->SetVillageUnique(pHouseManager->siVillageUnique);
			((CNHouseExtensionDlg*)pclclient->m_pDialog[NHOUSEEXTENSION_DLG])->SetHouseUnitIndex(pHouseManager->siSelectedHouseUnitNumber);
		}
	}
	else CASE_CONTROL( BUTTON_CANCELLATION_HOUSE )
	{		
		if(pHouseManager->siSelectedHouseUnitNumber >=0)
		{
			cltGameMsgRequest_HouseCancellationPenaltyMoney clinfo(pHouseManager->siVillageUnique, pHouseManager->siSelectedHouseUnitNumber);
			cltMsg clMsg(GAMEMSG_REQUEST_HOUSECANCELLATIONPENALTYMONEY, sizeof(clinfo), (BYTE*) &clinfo );
			pclClient->pclCM->CR[ 1 ]->SendNetMsg((sPacketHeader*)&clMsg);

			CButton *pButton = (CButton*)m_pControlMap[ BUTTON_CANCELLATION_HOUSE ];
			pButton->Enable(FALSE);
		}

	}
	else CASE_CONTROL( BUTTON_ENTER )
	{
		if(pHouseManager->siSelectedHouseUnitNumber >= 0 && pHouseManager->siSelectedHouseUnitNumber < MAX_HOUSEUNIT_NUMBER )
		{
			//����� �Ǵ� ĳ������ ���̵� ���Ѵ�.
			SI32 id = 1;

			if(id)
			{
				//�Ͽ콺 �Ŵ��� ���� �Ͽ콺 ������ ���� �Ǹ� ������ ��� �ֱ� ������ �ش� ������ �Ǹ� ������ üũ ����.
				if(pHouseManager->clClientUnit[pHouseManager->siSelectedHouseUnitNumber].bSell == true)
				{
					// ������ �Ұ��� �ϴٴ� �޼���.

					TCHAR* pTitle = GetTxtFromMgr(30145);
					TCHAR* pText  = GetTxtFromMgr(30103);

					cltClient *pclclient = (cltClient*) pclClient;

					stMsgBox MsgBox;
					MsgBox.Set( this, pTitle, pText, MSGBOX_TYPE_OK, 0 );
					pclclient->SetMsgBox( &MsgBox, NULL, 0 );
				}

				else // �Ǹ����� â�� �ƴϸ� ������ ����.
				{
					pHouseManager->clClientUnit[pHouseManager->siSelectedHouseUnitNumber].clStorageInfo.Init();

					cltClient *pclclient = (cltClient *) pclClient;

					if(pclclient->m_pDialog[NHOUSEUSERINFOBASE_DLG] == NULL )
						pclclient->CreateInterface( NHOUSEUSERINFOBASE_DLG );

					if(pclclient->m_pDialog[NHOUSEUSERINFOBASE_DLG] )
					{
						((CNHouseUserInfoBaseDlg*)pclclient->m_pDialog[NHOUSEUSERINFOBASE_DLG])->SetPersonItemInfo(&pclCM->CR[1]->pclCI->clCharItem);
						((CNHouseUserInfoBaseDlg*)pclclient->m_pDialog[NHOUSEUSERINFOBASE_DLG])->SetHouseUserInfoBase(&pHouseManager->clClientUnit[pHouseManager->siSelectedHouseUnitNumber], &pclCM->CR[id]->pclCI->clCharSkill,
							pHouseManager->siVillageUnique, pHouseManager->siSelectedHouseUnitNumber);

							((CNHouseUserInfoBaseDlg*)pclclient->m_pDialog[NHOUSEUSERINFOBASE_DLG])->InitHouse();
					}

					else // �������� ������ �����ٰ� �ٽ� �����ش�.
					{
						pclclient->CreateInterface( NHOUSEUSERINFOBASE_DLG );

						((CNHouseUserInfoBaseDlg*)pclclient->m_pDialog[NHOUSEUSERINFOBASE_DLG])->SetPersonItemInfo(&pclCM->CR[1]->pclCI->clCharItem);
						((CNHouseUserInfoBaseDlg*)pclclient->m_pDialog[NHOUSEUSERINFOBASE_DLG])->SetHouseUserInfoBase(&pHouseManager->clClientUnit[pHouseManager->siSelectedHouseUnitNumber], &pclCM->CR[id]->pclCI->clCharSkill,
							pHouseManager->siVillageUnique, pHouseManager->siSelectedHouseUnitNumber);
						((CNHouseUserInfoBaseDlg*)pclclient->m_pDialog[NHOUSEUSERINFOBASE_DLG])->InitHouse();
					}
					
					GameMsgRequest_HouseUnitStgInfo clinfo(pHouseManager->siVillageUnique, pHouseManager->siSelectedHouseUnitNumber);
					cltMsg clMsg(GAMEMSG_REQUEST_STGINFO, sizeof(clinfo), (BYTE*)&clinfo);
					pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
				}
			}
		}
	}
	

	//����---------------------------------------------------------------------------------------------------------
	//	if(pHouseManager->siSelectedHouseUnitNumber >=0)
	//	{
	//		// ����� �Ǵ� ĳ������ ���̵� ���Ѵ�. 
	//		SI32 id = 1;

	//		if(id)
	//		{
	//			pHouseManager->clClientUnit[pHouseManager->siSelectedHouseUnitNumber].clStorageInfo.Init();

	//			cltClient *pclclient = (cltClient *)pclClient;

	//			if( pclclient->m_pDialog[NHOUSEUSERINFOBASE_DLG] == NULL )
	//				pclclient->CreateInterface( NHOUSEUSERINFOBASE_DLG ); 

	//			if( pclclient->m_pDialog[NHOUSEUSERINFOBASE_DLG] )
	//			{
	//				((CNHouseUserInfoBaseDlg*)pclclient->m_pDialog[NHOUSEUSERINFOBASE_DLG])->SetPersonItemInfo(&pclCM->CR[1]->pclCI->clCharItem);
	//				((CNHouseUserInfoBaseDlg*)pclclient->m_pDialog[NHOUSEUSERINFOBASE_DLG])->SetHouseUserInfoBase(&pHouseManager->clClientUnit[pHouseManager->siSelectedHouseUnitNumber], &pclCM->CR[id]->pclCI->clCharSkill,
	//					pHouseManager->siVillageUnique, pHouseManager->siSelectedHouseUnitNumber);

	//				((CNHouseUserInfoBaseDlg*)pclclient->m_pDialog[NHOUSEUSERINFOBASE_DLG])->InitHouse();
	//			}
	//			else	// �������� ������ �����ٰ� �ٽ� �����ش�
	//			{
	//				pclclient->CreateInterface( NHOUSEUSERINFOBASE_DLG );

	//				((CNHouseUserInfoBaseDlg*)pclclient->m_pDialog[NHOUSEUSERINFOBASE_DLG])->SetPersonItemInfo(&pclCM->CR[1]->pclCI->clCharItem);
	//				((CNHouseUserInfoBaseDlg*)pclclient->m_pDialog[NHOUSEUSERINFOBASE_DLG])->SetHouseUserInfoBase(&pHouseManager->clClientUnit[pHouseManager->siSelectedHouseUnitNumber], &pclCM->CR[id]->pclCI->clCharSkill,
	//					pHouseManager->siVillageUnique, pHouseManager->siSelectedHouseUnitNumber);
	//				((CNHouseUserInfoBaseDlg*)pclclient->m_pDialog[NHOUSEUSERINFOBASE_DLG])->InitHouse();
	//			}

	//			GameMsgRequest_HouseUnitStgInfo clinfo(pHouseManager->siVillageUnique, pHouseManager->siSelectedHouseUnitNumber);
	//			cltMsg clMsg(GAMEMSG_REQUEST_STGINFO, sizeof(clinfo), (BYTE*)&clinfo);
	//			pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	//		}

	//	}
    //����---------------------------------------------------------------------------------------------------------

}