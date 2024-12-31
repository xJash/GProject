#include "NCityhallDlg.h"


//#include "../../InterfaceMgr/Interface/List.h"
#include "../../InterfaceMgr/Interface/ComboBox.h"

#include "Char\CharManager\CharManager.h"
#include "..\..\Server\Rank\Rank.h"

#include "../../CommonLogic/MsgType-Structure.h"

#include "../../CommonLogic/Cityhall/TaxPaymentListDlg.h"

// Ǯ��ũ�� ���� �ƴϳ�
#include "../../Client/Interface/SoundOnOffDlg/SoundOnOffDlg.h"
#include "../../Client/InterfaceMgr/InterfaceMgr.h"
#include "../../Client/NInterface/NSoundOnOffDlg/NSoundOnOffDlg.h"

#include "NHireSystemNPCDlg.h"
#include "Map\FieldObject\FieldObject.h"

#include "..\..\Client\Music\Music.h"

#include "../Lib/JYLibFunction.h"
#include "../../InterfaceMgr/InterfaceMgr.h"

#include "../common/Event/event.h"

extern cltCommonLogic* pclClient;
extern CJYLibFunction g_JYLibFunction;

bool m_bNewYearEvent = false;	// �ų� �̺�Ʈ����...

NCityhallChiefDlg::NCityhallChiefDlg()
{
}

NCityhallChiefDlg::~NCityhallChiefDlg()
{
	//[����] �ҿ��� �Ӹ�â�� ���� ��ûâ�� ������ �Ӹ�â�� ������ Ŭ�� �״°� ����. => 2008-6-16 
	cltClient* pclclient = (cltClient *)pclClient;
	pclclient->DestroyInterface( pclclient->m_pDialog[NAPPOINTMENTCHIEF_DLG]  );
	pclclient->DestroyInterface( pclclient->m_pDialog[NCITYHALLCONSTRUCT_DLG] );
	pclclient->DestroyInterface( pclclient->m_pDialog[NBERESIDENT_DLG]        );
	pclclient->DestroyInterface( pclclient->m_pDialog[NRESIDENTLIST_DLG]	  );
	pclclient->DestroyInterface( pclclient->m_pDialog[NHIRENPC_DLG]			  );
	pclclient->DestroyInterface( pclclient->m_pDialog[NSTRUCTUREMESSAGE_DLG]  );
	pclclient->DestroyInterface( pclclient->m_pDialog[NVILLAGETREE_DLG]		  );
}

void NCityhallChiefDlg::InitDlg()
{
	cltCityHallManager *pCityhallManager = ((cltCityHallManager *)m_pStrManager);

	SetControlMap( COMBO_STRUCT, TEXT("combobox_struct") );
	SetControlMap( EDIT_TAX, TEXT("editbox_tax") );

	SetControlMap( BUTTON_SETTAX, TEXT("button_settax") );
	SetControlMap( BUTTON_BERANK, TEXT("button_berank") );
	SetControlMap( BUTTON_CONSTRUCT, TEXT("button_construct") );
	SetControlMap( BUTTON_REG_RESIDENT, TEXT("button_reg_resident") );
	SetControlMap( BUTTON_ADMIN_RESIDENT, TEXT("button_admin_resident") );
	SetControlMap( BUTTON_HIRENPC, TEXT("button_hirenpc") );
	SetControlMap( BUTTON_SETNOTICE, TEXT("button_setnotice") );
	SetControlMap( BUTTON_DECLAREWAR, TEXT("button_declarewar") );


	SetControlMap( BUTTON_MAKETREE, TEXT("button_MakeTree") );
	SetControlMap( STATIC_HIRE_EVENTNPC, TEXT("statictext_Tree") );
	
	SetControlMap( COMBO_EVENTNPC , TEXT("combobox_eventnpc") );

	CButton * pTreeButton = (CButton *)m_pControlMap[ BUTTON_MAKETREE ];
	CComboBox* pComboBoxHireNpc = (CComboBox*)m_pControlMap[COMBO_EVENTNPC];//��ҿ��� ������� �޺��ڽ��� �����ϵ��� �ѵ�
	pComboBoxHireNpc->Enable(false);

	//KHY - 1113 - ũ�������� �̺�Ʈ
	cltClient* pclclient = (cltClient *)pclClient;

	if(pclClient->pclEventTimeManager->InEventTime("ChristmasEvent", &pclclient->sTime) )
	{
		pComboBoxHireNpc->Enable(true);
	}
	if(pclClient->pclEventTimeManager->InEventTime("NewYearEvent", &pclclient->sTime) )
	{
		pComboBoxHireNpc->Enable(true);
	}
	if ( pclClient->IsCountrySwitch(Switch_VillageWarpTower)) {//����ž�� ���ﶧ  �̺�Ʈ�� ��쿡�� ����Ҽ� �ֵ��� �Ѵ�.
		pComboBoxHireNpc->Enable(true);
	}

	((CEdit*)m_pControlMap[ EDIT_TAX ])->SetMaxEditTextLength(MAX_TAX_NUM);//�����̻��� �ؽ�Ʈ �Է¹��� [2007.07.05����]
	pTreeButton->Enable(false);

	CComboBox *pCombo = (CComboBox *)m_pControlMap[ COMBO_STRUCT ];
	stComboBoxItemData itemdata;

	//cyj �������� ��� ����
	CButton *pButton = (CButton *)m_pControlMap[ BUTTON_DECLAREWAR ];
	pButton->Show(false);

	// �ǹ����� �޺��� �߰��Ѵ�
	SI32 index = 0;
	SI32 siStructureUnique;

	cltVillageInfo *pVillageInfo = pclClient->pclVillageManager->pclVillageInfo[ pCityhallManager->siVillageUnique ];
	cltVillageStructureInfo *pStructureInfo;	

	int ref;

	if( pVillageInfo ) {

		for( int i = 0; i < MAX_CONSTRUCTION_NUM; ++i ) {

			siStructureUnique = pVillageInfo->clVillageVary.clStructureInfo.Get( i );

			if( siStructureUnique == 1 ) continue;

			
			if( siStructureUnique ) {

				ref = pclClient->pclVillageStructureSet->FindRefFromUnique( siStructureUnique );

				if( ref != -1 ) {

					pStructureInfo = pclClient->pclVillageStructureSet->pclVillageStructureInfo[ ref ];

					if( pStructureInfo ) {
						
						// [����] �ʺ��� ���� : ��� �繫�Ҹ� �ҿ��ָ� ��û�� �� �ִ�
						if ( pclClient->IsCountrySwitch(Switch_TutorialVillage) )
						{
							if ( (Const_Beginner_Village == pCityhallManager->siVillageUnique) && (RANKTYPE_GUILD != pStructureInfo->siRankType) )
							{
								continue;
							}
						}
						
						itemdata.Init();
						itemdata.Set( pStructureInfo->szName );
						
						if(pCombo)		pCombo->AddItem( &itemdata );

					}
				}
			}
		}

	}

	SI32	siEventNPCCount = 0;

	SI32	siEventNPC[10];
	ZeroMemory(siEventNPC, sizeof(siEventNPC));

	// [���] ���� - EventPeriod.txt���� ���� �����ϰ�
	if(pclClient->pclEventTimeManager->InEventTime("NewYearEvent", &pclclient->sTime) )
	{
		siEventNPC[siEventNPCCount++] = pclClient->GetUniqueFromHash( TEXT("KIND_NEWYEARTREEBASE"));
	}

	//KHY - 1113 - ũ�������� �̺�Ʈ
	if(pclClient->pclEventTimeManager->InEventTime("ChristmasEvent", &pclclient->sTime) )
	{
		// ũ�������� �̺�Ʈ
		//siEventNPC[0] = pclClient->GetUniqueFromHash( TEXT("KIND_PINE_TREE"));  // ������.
		siEventNPC[siEventNPCCount++] = pclClient->GetUniqueFromHash( TEXT("KIND_CHRISTMASTREEBASE"));
	}


	//��ȯž ��ġ
	if(pclClient->IsCountrySwitch(Switch_VillageWarpTower)) 
	{
		//��ȯž��ġ.
		siEventNPC[siEventNPCCount++] = pclClient->GetUniqueFromHash( TEXT("KIND_RETURNTOWER"));
	}
	
	//���������� �߰�.
	if(pclClient->pclEventTimeManager->InEventTime("Hinamatsuri", &pclclient->sTime)) 
	{
		siEventNPC[siEventNPCCount++] = pclClient->GetUniqueFromHash( TEXT("KIND_HINADOLL"));
	}
	//-----------------------------------------------------------
	//[����] ������ ���� ���� �̺�Ʈ �߰�. => 2008-6-9
	if(pclClient->IsCountrySwitch(Switch_Hero_Bronze_Statue)) 
	{
		cltClient* pclclient = (cltClient*)pclClient;
		if( pclClient->pclEventTimeManager->InEventTime("Hero_Bronze", &pclclient->sTime) )
		{
			siEventNPC[siEventNPCCount++] = pclClient->GetUniqueFromHash( TEXT("KIND_ROULETTESTATUEBASE"));
		}
	}
	//-----------------------------------------------------------
	//-----------------------------------------------------------
	//[����] �ҷ��� �̺�Ʈ 
	if(pclClient->IsCountrySwitch(Switch_HalloweenEvent)) 
	{
		cltClient* pclclient = (cltClient*)pclClient;
		if( pclClient->pclEventTimeManager->InEventTime("HalloweenEvent", &pclclient->sTime) )
		{
			siEventNPC[siEventNPCCount++] = pclClient->GetUniqueFromHash( TEXT("KIND_HALLOWEENBASE"));
		}
	}
	//-----------------------------------------------------------

	CComboBox *pEventNpcCombo = (CComboBox *)m_pControlMap[ COMBO_EVENTNPC ];
	stComboBoxItemData comboBoxItem;

	if(pEventNpcCombo)
	{
		for(int i=0; i<10; i++)
		{
			if( siEventNPC <= 0 )			continue;

			TCHAR * npcName = NULL;
			npcName = (TCHAR*)pclClient->pclKindInfoSet->GetName(siEventNPC[i]);

			if( npcName )
			{
				comboBoxItem.Init();
				comboBoxItem.Set( npcName );
				if(pEventNpcCombo != NULL)		pEventNpcCombo->AddItem( &comboBoxItem );
			}
		}

		if (pEventNpcCombo->GetItemNum() > 0)
		{
			CButton * pTreeButton = (CButton *)m_pControlMap[ BUTTON_MAKETREE ];
			if(pTreeButton)		pTreeButton->Enable( true );
		}
	}

	// [����] �ʺ��� ���� : ��û ������ �޴� ���� ��ư ����
	if ( pclClient->IsCountrySwitch(Switch_TutorialVillage) )
	{
		if ( Const_Beginner_Village == pCityhallManager->siVillageUnique )
		{
			((CButton*)m_pControlMap[ BUTTON_SETTAX ])->Enable( false );
			((CButton*)m_pControlMap[ BUTTON_CONSTRUCT ])->Enable( false );
			((CButton*)m_pControlMap[ BUTTON_REG_RESIDENT ])->Enable( false );
			((CButton*)m_pControlMap[ BUTTON_ADMIN_RESIDENT ])->Enable( false );
			((CButton*)m_pControlMap[ BUTTON_HIRENPC ])->Enable( false );
			((CButton*)m_pControlMap[ BUTTON_SETNOTICE ])->Enable( false );
			((CButton*)m_pControlMap[ BUTTON_DECLAREWAR ])->Enable( false );
			((CButton*)m_pControlMap[ BUTTON_MAKETREE ])->Enable( false );
		}
	}
}

void NCityhallChiefDlg::Action()
{
	cltCityHallManager *pCityhallManager = ((cltCityHallManager *)m_pStrManager);
}

void NCityhallChiefDlg::NDlgTabProc( UINT nEvent, int nControlID, CControllerObj *pControl )
{
	cltCityHallManager *pCityhallManager = ((cltCityHallManager *)m_pStrManager);
	cltClient *pclclient = (cltClient*)pclClient;

	CComboBox *pCombo = (CComboBox *)m_pControlMap[ COMBO_STRUCT ];
	stComboBoxItemData *pItemdata;

	CASE_CONTROL( BUTTON_APPLY)// �����̻��� �ؽ�Ʈ �Է¹��� [2007.07.05����]
	{
		TCHAR buffer[256] = "" ;
		TCHAR * TaxLen = GetEditText(EDIT_TAX);
		StringCchPrintf(buffer, 256, TaxLen);

		if ( strlen(TaxLen) >= MAX_TAX_NUM){
			TCHAR* pText = GetTxtFromMgr(1543);
			SetMainExplain( pText);
			return;
		}


	}


	CASE_CONTROL( BUTTON_SETTAX )
	{

		// �ڽ��� (��)����� �̹� ��ϵǾ� �־��  �Ѵ�. 
		{
			cltSimpleRank clrank( m_pStrManager->siRankType, m_pStrManager->siVillageUnique);
			if( pclCM->CR[1]->pclCI->clCharRank.IsSame(&clrank) == FALSE )
			{
				TCHAR* pText;
				if( m_pStrManager->siRankType == RANKTYPE_CITYHALL ) pText = GetTxtFromMgr(1547);
				else pText = GetTxtFromMgr(1440);
				SetMainExplain(pText);
				return;
			}
		}

		// ���� ����
		SI32 id = 1;
		if(id)
		{
			TCHAR buf[ 256 ];			
			SI32 index = pCombo->GetSelectedIndex();

			if( index < 0 ) 
			{
				TCHAR* pText = GetTxtFromMgr(1543);
				SetMainExplain( pText);
				return;
			}
			pItemdata = pCombo->GetItemData( index );
			MStrCpy( buf, pItemdata->strText, 64 );
			SI32 strtype = pclClient->pclVillageStructureSet->GetRankTypeFromStructureName( buf );
			cltMoney clMoney;
			int tax = _tstoi( GetEditText( EDIT_TAX ) );

			if( tax <= 0 ) {

				TCHAR* pText = GetTxtFromMgr(1544);
				SetMainExplain(pText);

			} else {

				clMoney.Set( tax );

				cltGameMsgRequest_SetTax clSetTax( pCityhallManager->siVillageUnique, strtype, 0, &clMoney );

				cltMsg clMsg( GAMEMSG_REQUEST_SETTAX, sizeof(cltGameMsgRequest_SetTax), (BYTE*)&clSetTax );

				pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);


			}					

			
		}

	}

	else CASE_CONTROL( BUTTON_BERANK )
	{
		// �ڽ��� (��)����� �̹� ��ϵǾ� �־��  �Ѵ�. 
		{
			cltSimpleRank clrank( m_pStrManager->siRankType, m_pStrManager->siVillageUnique);
			if( pclCM->CR[1]->pclCI->clCharRank.IsSame(&clrank) == FALSE )
			{
				TCHAR* pText;
				if( m_pStrManager->siRankType == RANKTYPE_CITYHALL ) pText = GetTxtFromMgr(1547);
				else pText = GetTxtFromMgr(1440);
				SetMainExplain(pText);
				return;
			}
		}


		SI32 index = pCombo->GetSelectedIndex();

		if( index < 0 ) return;

		pItemdata = pCombo->GetItemData( index );

		pclclient->CreateInterface( NAPPOINTMENTCHIEF_DLG );
		//pCityhallManager->pclAppointmentChiefDlg->Create( NULL, pclClient->GetHwnd(), pCityhallManager, pItemdata->strText );
		
	}

	else CASE_CONTROL( BUTTON_CONSTRUCT )
	{

		// �ڽ��� (��)����� �̹� ��ϵǾ� �־��  �Ѵ�. 
		{
			cltSimpleRank clrank( m_pStrManager->siRankType, m_pStrManager->siVillageUnique);
			if( pclCM->CR[1]->pclCI->clCharRank.IsSame(&clrank) == FALSE )
			{
				TCHAR* pText;
				if( m_pStrManager->siRankType == RANKTYPE_CITYHALL ) pText = GetTxtFromMgr(1547);
				else pText = GetTxtFromMgr(1440);
				SetMainExplain(pText);
				return;
			}
		}

		pclclient->CreateInterface( NCITYHALLCONSTRUCT_DLG );
	}

	else CASE_CONTROL( BUTTON_REG_RESIDENT )
	{

		// �ڽ��� (��)����� �̹� ��ϵǾ� �־��  �Ѵ�. 
		{
			cltSimpleRank clrank( m_pStrManager->siRankType, m_pStrManager->siVillageUnique);
			if( pclCM->CR[1]->pclCI->clCharRank.IsSame(&clrank) == FALSE )
			{
				TCHAR* pText;
				if( m_pStrManager->siRankType == RANKTYPE_CITYHALL ) pText = GetTxtFromMgr(1547);
				else pText = GetTxtFromMgr(1440);
				SetMainExplain(pText);
				return;
			}
		}


		pclclient->CreateInterface( NBERESIDENT_DLG );

	}

	else CASE_CONTROL( BUTTON_ADMIN_RESIDENT )
	{

		// �ڽ��� (��)����� �̹� ��ϵǾ� �־��  �Ѵ�. 
		{
			cltSimpleRank clrank( m_pStrManager->siRankType, m_pStrManager->siVillageUnique);
			if( pclCM->CR[1]->pclCI->clCharRank.IsSame(&clrank) == FALSE )
			{
				TCHAR* pText;
				if( m_pStrManager->siRankType == RANKTYPE_CITYHALL ) pText = GetTxtFromMgr(1547);
				else pText = GetTxtFromMgr(1440);
				SetMainExplain(pText);
				return;
			}
		}


		pclclient->CreateInterface( NRESIDENTLIST_DLG );
	}

	else CASE_CONTROL( BUTTON_HIRENPC )
	{

		// �ڽ��� (��)����� �̹� ��ϵǾ� �־��  �Ѵ�. 
		{
			cltSimpleRank clrank( m_pStrManager->siRankType, m_pStrManager->siVillageUnique);
			if( pclCM->CR[1]->pclCI->clCharRank.IsSame(&clrank) == FALSE )
			{
				TCHAR* pText;
				if( m_pStrManager->siRankType == RANKTYPE_CITYHALL ) pText = GetTxtFromMgr(1547);
				else pText = GetTxtFromMgr(1440);
				SetMainExplain(pText);
				return;
			}
		}

		if(!(pclclient->m_pDialog[ NHIRENPC_DLG ]))
		{
			pclclient->CreateInterface(NHIRENPC_DLG);
		}
		((CNHireSystemNPCDlg*)pclclient->m_pDialog[ NHIRENPC_DLG ])->Set( pCityhallManager);
		}
	
	else CASE_CONTROL( BUTTON_MAKETREE )
	{

		// �ڽ��� (��)����� �̹� ��ϵǾ� �־��  �Ѵ�. 

		cltSimpleRank clrank( m_pStrManager->siRankType, m_pStrManager->siVillageUnique);
		if( pclCM->CR[1]->pclCI->clCharRank.IsSame(&clrank) == FALSE )
		{
			TCHAR* pText;
			if( m_pStrManager->siRankType == RANKTYPE_CITYHALL ) pText = GetTxtFromMgr(1547);
			else pText = GetTxtFromMgr(1440);
			SetMainExplain(pText);
			return;
		}


		
		CComboBox * pNpcEventCombo = NULL;
			
        pNpcEventCombo = (CComboBox*)m_pControlMap[ COMBO_EVENTNPC ];

		if( pNpcEventCombo == NULL )  return;

		SI16 selectedIndex = pNpcEventCombo->GetSelectedIndex();

		if( selectedIndex < 0 ) return;
		
		TCHAR * pNpcName = NULL;			
		pNpcName = pNpcEventCombo->GetText( selectedIndex );

		if( pNpcName == NULL ) return;

		SI32 selectedEventNpcKind = 0;
		selectedEventNpcKind = pclClient->pclKindInfoSet->FindKindFromName( pNpcName );
        
		if( selectedEventNpcKind <= 0) return;

		TCHAR* pText = GetTxtFromMgr(6710);
		TCHAR* pTitle = GetTxtFromMgr(6709);

		TCHAR szBuffer[256] = {'\0', };
		GMONEY siPrice = 0;
			
		
		// �ų��̺�Ʈ�� �ƴϰ� ũ�������� �̺�Ʈ �̸�.
		//if(false == m_bNewYearEvent && pclClient->IsCountrySwitch(Switch_ChristmasEvent)) 
		if(pclClient->pclEventTimeManager->InEventTime("ChristmasEvent", &pclclient->sTime) )
		{
			//SI64 siGV_Christmastreevalue = pclClient->GetGlobalValue(TEXT("GV_Christmasvalue"));//Ʈ�� ����� ���� �о� �´�
			SI64 siGV_Christmastreevalue = 0;//Ʈ�� ����� ���� �о� �´�
			
			SI32 npcrate = pclClient->pclItemManager->clItemStatistic.siNPCPriceRate;	//NPCRate�� �о� �´�.

			if (npcrate < 100)		  siGV_Christmastreevalue =  5000000;
			else if (npcrate < 300)   siGV_Christmastreevalue =  10000000;
			else if (npcrate < 700)   siGV_Christmastreevalue =  20000000;
			else if (npcrate < 1000)  siGV_Christmastreevalue =  40000000;
			else if (npcrate < 2000)  siGV_Christmastreevalue =  60000000;
			else if (npcrate < 3000)  siGV_Christmastreevalue =  80000000;
			else if (npcrate < 4000)  siGV_Christmastreevalue =  100000000;
			else if (npcrate < 5500)  siGV_Christmastreevalue =  120000000;
			else if (npcrate < 8500)  siGV_Christmastreevalue =  160000000;
			else if (npcrate < 14500) siGV_Christmastreevalue =  280000000;
			else if (npcrate < 25500) siGV_Christmastreevalue =  500000000;
			else if (npcrate < 33500) siGV_Christmastreevalue =  650000000;
			else if (npcrate < 35500) siGV_Christmastreevalue =  800000000;
			else					  siGV_Christmastreevalue =  800000000;

			if(siGV_Christmastreevalue <= 0)
				return;

			GMONEY villagemoney = pclClient->pclCityHallManager->clClientStrInfo.clCommonInfo.clMoney.itMoney;//�ں���
			if (villagemoney < siGV_Christmastreevalue )
			{
				cltClient *pclclient = (cltClient *)pclClient;
				TCHAR buffer[128] = TEXT("");
				TCHAR *pBaseText = GetTxtFromMgr(7685);//�ں����� ���ڶ� %s �Ǽ��� �����Ͽ����ϴ�.
				TCHAR *pNameText = GetTxtFromMgr(7630);//Ʈ���볪��
				TCHAR* pTitleText = GetTxtFromMgr(512);
				StringCchPrintf(buffer,128,pBaseText,pNameText);
				pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitleText, buffer );//���� �޼���.
				return;
			}
			siPrice = siGV_Christmastreevalue;
			pText = GetTxtFromMgr(8796);
			pTitle = GetTxtFromMgr(6708);

			const TCHAR* pszName = pclClient->pclKindInfoSet->GetName(selectedEventNpcKind);
			StringCchPrintf(szBuffer, 256, pText, pszName, siPrice, pszName);
		}
		else
		{
			StringCchPrintf(szBuffer, 256, pText, siPrice);
		}

		//[�߰� : Ȳ���� 2007. 12. 10 �ų��̺�Ʈ Ʈ�� ��ġâ.]
		if( pclClient->pclEventTimeManager->InEventTime("NewYearEvent", &pclclient->sTime) )
		{
			//SI64	siGV_NewYearValue	= pclClient->GetGlobalValue(TEXT("GV_NewYearValue")); //�ų� �̺�Ʈ Ʈ�� ����� ���� �о� �´�.
			//if(siGV_NewYearValue <= 0)
			//	return;

			SI32 siWarpTowerPrice = 5000000;
			SI32 npcRate = pclClient->pclItemManager->clItemStatistic.siNPCPriceRate;	//NPCRate�� �о� �´�.
			if (npcRate < 100)		 siWarpTowerPrice =   5000000;
			else if (npcRate < 300)  siWarpTowerPrice =  10000000;
			else if (npcRate < 700)  siWarpTowerPrice =  20000000;
			else if (npcRate < 1000) siWarpTowerPrice =  40000000;
			else if (npcRate < 2000) siWarpTowerPrice =  60000000;
			else if (npcRate < 3000) siWarpTowerPrice =  80000000;
			// KHY - 1021 - NPCRate �� Ȯ��.
			else if (npcRate < 4000) siWarpTowerPrice =  100000000;
			else if (npcRate < 5500) siWarpTowerPrice =  120000000;
			else if (npcRate < 8500) siWarpTowerPrice =  160000000;
			else if (npcRate < 14500) siWarpTowerPrice = 280000000;
			else if (npcRate < 25500) siWarpTowerPrice = 500000000;
			else if (npcRate < 33500) siWarpTowerPrice = 650000000;
			else					  siWarpTowerPrice = 800000000;

			GMONEY	villagemoney		= pclClient->pclCityHallManager->clClientStrInfo.clCommonInfo.clMoney.itMoney; // ���� �ں���.
			TCHAR*	pTreeNameText		= NULL;

			// Ʈ�� �̸� ���.
			pTreeNameText = GetTxtFromMgr(9673);

			// ���� �ں��ݿ� ���� �޽��� ���.
			if (villagemoney < siWarpTowerPrice)
			{
				TCHAR* pFailText  = GetTxtFromMgr(7685); // �ں����� ���ڶ� %s �Ǽ��� �����Ͽ����ϴ�.
				TCHAR* pTitleText = GetTxtFromMgr(512);  // Ÿ��Ʋ�� ����.

				StringCchPrintf(szBuffer, 128, pFailText, pTreeNameText);
				pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText(pTitleText, szBuffer); //���� �޼���.
				return;
			}

			siPrice = siWarpTowerPrice;
			pText   = GetTxtFromMgr(8796);
			pTitle  = GetTxtFromMgr(6708);

			StringCchPrintf(szBuffer, 256, pText, pTreeNameText, siPrice, pTreeNameText);
		}
		
		if (pclClient->IsCountrySwitch(Switch_VillageWarpTower)) 
		{
			//���� ��ȯž.
			if( selectedEventNpcKind == pclClient->GetUniqueFromHash( TEXT("KIND_RETURNTOWER")))
			{
				SI32 siWarpTowerPrice = 5000000;
				SI32 npcRate = pclClient->pclItemManager->clItemStatistic.siNPCPriceRate;//NPCRate�� �о� �´�.
				if (npcRate < 500) siWarpTowerPrice = 5000000;
				else if (npcRate < 1000) siWarpTowerPrice = 10000000;
				else if (npcRate < 1500) siWarpTowerPrice = 15000000;
				else if (npcRate < 2000) siWarpTowerPrice = 20000000;
				else if (npcRate < 2500) siWarpTowerPrice = 25000000;
				else if (npcRate < 3000) siWarpTowerPrice = 30000000;
				
				// KHY - 1021 - NPCRate �� Ȯ��.
				else if (npcRate < 4000) siWarpTowerPrice = 35000000;
				else if (npcRate < 5500) siWarpTowerPrice = 48000000;
				else if (npcRate < 8500) siWarpTowerPrice = 70000000;
				else if (npcRate < 14500) siWarpTowerPrice = 120000000;
				else if (npcRate < 25500) siWarpTowerPrice = 220000000;
				else if (npcRate < 33500) siWarpTowerPrice = 300000000;
				else {
					siWarpTowerPrice = 400000000;
				}


				GMONEY	villagemoney		= pclClient->pclCityHallManager->clClientStrInfo.clCommonInfo.clMoney.itMoney; // ���� �ں���.
				TCHAR*	pTreeNameText		= NULL;
				// Ʈ�� �̸� ���.
				pTreeNameText = GetTxtFromMgr(7746);
				// ���� �ں��ݿ� ���� �޽��� ���.
				if (villagemoney < siWarpTowerPrice)
				{
					TCHAR* pFailText  = GetTxtFromMgr(7685); // �ں����� ���ڶ� %s �Ǽ��� �����Ͽ����ϴ�.
					TCHAR* pTitleText = GetTxtFromMgr(512);  // Ÿ��Ʋ�� ����.

					StringCchPrintf(szBuffer, 128, pFailText, pTreeNameText);
					pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText(pTitleText, szBuffer); //���� �޼���.
					return;
				}

				siPrice = siWarpTowerPrice;
				pText   = GetTxtFromMgr(7654);
				pTitle  = GetTxtFromMgr(6708);

				StringCchPrintf(szBuffer, 256, pText, pTreeNameText, siPrice, pTreeNameText);
			}
		}
		
		//[����] ������ ���� ���� �̺�Ʈ ����. => 2008-6-9
		if (pclClient->IsCountrySwitch(Switch_Hero_Bronze_Statue)) 
		{
			if( selectedEventNpcKind == pclClient->GetUniqueFromHash( TEXT("KIND_ROULETTESTATUEBASE")))
			{
				SI32 siWarpTowerPrice = 5000000;
				SI32 npcRate = pclClient->pclItemManager->clItemStatistic.siNPCPriceRate;	//NPCRate�� �о� �´�.
				if (npcRate < 100)		 siWarpTowerPrice =   5000000;
				else if (npcRate < 300)  siWarpTowerPrice =  10000000;
				else if (npcRate < 700)  siWarpTowerPrice =  20000000;
				else if (npcRate < 1000) siWarpTowerPrice =  40000000;
				else if (npcRate < 2000) siWarpTowerPrice =  60000000;
				else if (npcRate < 3000) siWarpTowerPrice =  80000000;
				// KHY - 1021 - NPCRate �� Ȯ��.
				else if (npcRate < 4000) siWarpTowerPrice =  100000000;
				else if (npcRate < 5500) siWarpTowerPrice =  120000000;
				else if (npcRate < 8500) siWarpTowerPrice =  160000000;
				else if (npcRate < 14500) siWarpTowerPrice =  280000000;
				else if (npcRate < 25500) siWarpTowerPrice =  500000000;
				else if (npcRate < 33500) siWarpTowerPrice =  650000000;
				else					 siWarpTowerPrice = 800000000;

				GMONEY	villagemoney		= pclClient->pclCityHallManager->clClientStrInfo.clCommonInfo.clMoney.itMoney; // ���� �ں���.

				// �������� �̸� ���.
				const TCHAR*	pHeroBronzeNameText	= pclClient->pclKindInfoSet->GetName(selectedEventNpcKind);;
				
				// ���� �ں��ݿ� ���� �޽��� ���.
				if (villagemoney < siWarpTowerPrice)
				{
					TCHAR* pFailText  = GetTxtFromMgr(7685); // �ں����� ���ڶ� %s �Ǽ��� �����Ͽ����ϴ�.
					TCHAR* pTitleText = GetTxtFromMgr(512);  // Ÿ��Ʋ�� ����.

					StringCchPrintf(szBuffer, 128, pFailText, pHeroBronzeNameText);
					pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText(pTitleText, szBuffer); //���� �޼���.
					return;
				}

				siPrice = siWarpTowerPrice;
				pText   = GetTxtFromMgr(8796);
				pTitle  = GetTxtFromMgr(6708);

				StringCchPrintf(szBuffer, 256, pText, pHeroBronzeNameText, siPrice, pHeroBronzeNameText);
			}
		}
		//[����] �ҷ��� �д� 
		if (pclClient->IsCountrySwitch(Switch_HalloweenEvent)) 
		{
			if( selectedEventNpcKind == pclClient->GetUniqueFromHash( TEXT("KIND_HALLOWEENBASE")))
			{
				SI32 siWarpTowerPrice = 50000000	;
				SI32 npcRate = pclClient->pclItemManager->clItemStatistic.siNPCPriceRate;	//NPCRate�� �о� �´�.
				if (npcRate < 100)		 siWarpTowerPrice   =    1500000;
				else if (npcRate < 300)  siWarpTowerPrice   =    3000000;
				else if (npcRate < 700)  siWarpTowerPrice   =    5000000;
				else if (npcRate < 1000) siWarpTowerPrice   =   10000000;
				else if (npcRate < 1450) siWarpTowerPrice	=	18000000;
				else if (npcRate < 1750) siWarpTowerPrice   =   29000000;
				else if (npcRate < 2050) siWarpTowerPrice   =   42000000;
				else if (npcRate < 2350) siWarpTowerPrice   =   58000000;
				else if (npcRate < 3000) siWarpTowerPrice   =   78000000;
				// KHY - 1021 - NPCRate �� Ȯ��.
				else if (npcRate < 4000)  siWarpTowerPrice  =  100000000;
				else if (npcRate < 5500)  siWarpTowerPrice  =  130000000;
				else if (npcRate < 8500)  siWarpTowerPrice  =  180000000;
				else if (npcRate < 14500) siWarpTowerPrice  =  120000000;
				else if (npcRate < 25500) siWarpTowerPrice  =  250000000;
				else if (npcRate < 33500) siWarpTowerPrice  =  400000000;
				else					  siWarpTowerPrice  =  850000000;

				GMONEY	villagemoney		= pclClient->pclCityHallManager->clClientStrInfo.clCommonInfo.clMoney.itMoney; // ���� �ں���.

				// �������� �̸� ���.
				const TCHAR*	pHeroBronzeNameText	= pclClient->pclKindInfoSet->GetName(selectedEventNpcKind);;

				// ���� �ں��ݿ� ���� �޽��� ���.
				if (villagemoney < siWarpTowerPrice)
				{
					TCHAR* pFailText  = GetTxtFromMgr(7685); // �ں����� ���ڶ� %s �Ǽ��� �����Ͽ����ϴ�.
					TCHAR* pTitleText = GetTxtFromMgr(512);  // Ÿ��Ʋ�� ����.

					StringCchPrintf(szBuffer, 128, pFailText, pHeroBronzeNameText);
					pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText(pTitleText, szBuffer); //���� �޼���.
					return;
				}

				siPrice = siWarpTowerPrice;
				pText   = GetTxtFromMgr(8796);
				pTitle  = GetTxtFromMgr(6708);

				StringCchPrintf(szBuffer, 256, pText, pHeroBronzeNameText, siPrice, pHeroBronzeNameText);
			}
		}
		
		//[�߰� : Ȳ���� 2008. 2. 18 ���������� ��� ��ư Ŭ��.]
		if(pclClient->pclEventTimeManager->InEventTime("Hinamatsuri", &pclclient->sTime))
		{
			SI64 npcRate = pclClient->pclItemManager->clItemStatistic.siNPCPriceRate;//NPCRate�� �о� �´�.
			
			siPrice = npcRate * 300000;
					
			GMONEY	villagemoney	= pclClient->pclCityHallManager->clClientStrInfo.clCommonInfo.clMoney.itMoney; // ���� �ں���.
			TCHAR*	pTreeNameText	= NULL;
			// Ʈ�� �̸� ���.
			pTreeNameText = GetTxtFromMgr(6853);
			
			// ���� �ں��ݿ� ���� �޽��� ���.
			if (villagemoney < siPrice)
			{
				TCHAR* pFailText  = GetTxtFromMgr(7685); // �ں����� ���ڶ� %s �Ǽ��� �����Ͽ����ϴ�.
				TCHAR* pTitleText = GetTxtFromMgr(512);  // Ÿ��Ʋ�� ����.

				StringCchPrintf(szBuffer, 128, pFailText, pTreeNameText);
				pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText(pTitleText, szBuffer); //���� �޼���.
				return;
			}

			pText   = GetTxtFromMgr(7654);
			pTitle  = GetTxtFromMgr(6708);

			StringCchPrintf(szBuffer, 256, pText, pTreeNameText, siPrice, pTreeNameText);
		}

		stMsgBox MsgBox;
		// ���� dialog�� �� â ���� Child Dialog�϶�
		CControllerMgr *pParent = NULL;
		pParent = this->GetParentDialog();
		if(pParent == NULL ) return;
		MsgBox.Set( pParent,pTitle  ,szBuffer , MSGBOX_TYPE_YESNO, 30 );

		BYTE TempBuffer[ 128 ];
		SI16 Size = sizeof( selectedEventNpcKind );
		memcpy( TempBuffer, &selectedEventNpcKind, sizeof( selectedEventNpcKind ) );
		pclclient->SetMsgBox( &MsgBox, TempBuffer, Size );

	}

	else CASE_CONTROL( BUTTON_SETNOTICE ) 
	{

		// �ڽ��� (��)����� �̹� ��ϵǾ� �־��  �Ѵ�. 
		{
			//�����ȳ���.
			cltSimpleRank clrank( m_pStrManager->siRankType, m_pStrManager->siVillageUnique);
			if( pclCM->CR[1]->pclCI->clCharRank.IsSame(&clrank) == FALSE )
			{
				TCHAR* pText;
				if( m_pStrManager->siRankType == RANKTYPE_CITYHALL ) pText = GetTxtFromMgr(1547);
				else pText = GetTxtFromMgr(1440);
				SetMainExplain(pText);
				return;
			}
		}


		//pCityhallManager->pclStrMsgDlg->Create( NULL, pclClient->GetHwnd(), pCityhallManager, RANKTYPE_CITYHALL );

		if( pclclient->m_pDialog[ NSTRUCTUREMESSAGE_DLG ] != NULL )
			return;

		pclclient->CreateInterface( NSTRUCTUREMESSAGE_DLG );
	}

	else CASE_CONTROL( BUTTON_DECLAREWAR )
	{

		// �ڽ��� (��)����� �̹� ��ϵǾ� �־��  �Ѵ�. 
		{
			cltSimpleRank clrank( m_pStrManager->siRankType, m_pStrManager->siVillageUnique);
			if( pclCM->CR[1]->pclCI->clCharRank.IsSame(&clrank) == FALSE )
			{
				TCHAR* pText;
				if( m_pStrManager->siRankType == RANKTYPE_CITYHALL ) pText = GetTxtFromMgr(1547);
				else pText = GetTxtFromMgr(1440);
				SetMainExplain(pText);
				return;
			}
		}

		//pCityhallManager->pclDeclareWarDlg->Create( NULL, pclClient->GetHwnd(), pCityhallManager );

		if( pclclient->m_pDialog[ NVILLAGETREE_DLG ] == NULL )
			pclclient->CreateInterface( NVILLAGETREE_DLG );
	}

}


void NCityhallChiefDlg::RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen )
{
	switch( MsgIndex )
	{
		case 30:
			{
				if ( RetValue )
				{
					if ( pData == NULL || DataLen < 1 )
					{
						return;
					}


					SI32 eventNpcKind = *((SI32*)pData);

					// EVENT NPC ����� ������ ��û�Ѵ� 

					cltGameMsgRequest_HireEventNPC clHireNPC( m_pStrManager->siVillageUnique , eventNpcKind ); 

					cltMsg clMsg( GAMEMSG_REQUEST_HIREEVENTNPC, sizeof(cltGameMsgRequest_HireEventNPC), (BYTE*)&clHireNPC );

					pclClient->pclCM->CR[1]->SendNetMsg((sPacketHeader*)&clMsg);				
				}

			}
			break;
	}

}


bool NCityhallChiefDlg::NewYearEventTime(void)
{
	//[�߰� : Ȳ���� 2007. 12. 10 �ų��̺�Ʈ ���� ����Ʈ �߰� ���� �Ⱓ.]
	SYSTEMTIME	StartTime;	ZeroMemory(&StartTime, sizeof(StartTime));
	SYSTEMTIME	EndTime;	ZeroMemory(&EndTime,   sizeof(EndTime));
	switch(pclClient->siServiceArea)
	{
	case ConstServiceArea_English:	
		{
			StartTime.wYear	 = 2008;		EndTime.wYear 	= 2008;
			StartTime.wMonth =   11;		EndTime.wMonth	=	12;
			StartTime.wDay	 =   10;		EndTime.wDay	=   31;
			StartTime.wHour	 =    0;		EndTime.wHour	=   23;
		}
		break;
	case ConstServiceArea_Korea:	
		{
			StartTime.wYear	 = 2007;		EndTime.wYear 	= 2008;
			StartTime.wMonth =   12;		EndTime.wMonth	=	 1;
			StartTime.wDay	 =   27;		EndTime.wDay	=   10;
			StartTime.wHour	 =    0;		EndTime.wHour	=   23;
		}
		break;
	case ConstServiceArea_Japan:	
		{
			StartTime.wYear	 = 2007;		EndTime.wYear 	= 2008;
			StartTime.wMonth =   12;		EndTime.wMonth	=	 1;
			StartTime.wDay	 =   26;		EndTime.wDay	=   10;
			StartTime.wHour	 =    0;		EndTime.wHour	=   23;
		}
		break;
	case ConstServiceArea_Taiwan:	
	case ConstServiceArea_USA:	
		{
			StartTime.wYear	 = 2007;		EndTime.wYear 	= 2008;
			StartTime.wMonth =   12;		EndTime.wMonth	=	 1;
			StartTime.wDay	 =   26;		EndTime.wDay	=    9;
			StartTime.wHour	 =    0;		EndTime.wHour	=   23;
		}
		break;
	case ConstServiceArea_NHNChina:	
		{
			StartTime.wYear	 = 2007;		EndTime.wYear 	= 2008;
			StartTime.wMonth =   12;		EndTime.wMonth	=	 1;
			StartTime.wDay	 =   26;		EndTime.wDay	=    8;
			StartTime.wHour	 =    0;		EndTime.wHour	=   23;
		}
		break;
	case ConstServiceArea_EUROPE:	
		{
			StartTime.wYear	 = 2007;		EndTime.wYear 	= 2008;
			StartTime.wMonth =   12;		EndTime.wMonth	=	 1;
			StartTime.wDay	 =   26;		EndTime.wDay	=    8;
			StartTime.wHour	 =    0;		EndTime.wHour	=   23;
		}
		break;
	}

	m_bNewYearEvent = false;

	cltClient* pclclient = (cltClient*)pclClient;
	if( true == TimeInBounds(&pclclient->sTime, &StartTime, &EndTime))
	{
		return true;
	}

	return false;
}
