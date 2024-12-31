#include "NCityhallDlg.h"

//#include "../../InterfaceMgr/Interface/List.h"
#include "../../InterfaceMgr/Interface/ComboBox.h"

#include "Char\CharManager\CharManager.h"
#include "..\..\Server\Rank\Rank.h"

#include "Map\FieldObject\FieldObject.h"
#include "../../CommonLogic/MsgType-Structure.h"

#include "..\..\Client\Music\Music.h"

#include "../Lib/JYLibFunction.h"

#include "../../InterfaceMgr/InterfaceMgr.h"

extern cltCommonLogic* pclClient;
extern CJYLibFunction g_JYLibFunction;

extern cltRankCandidate clRankCandidate[];

NCityhallResidentDlg::NCityhallResidentDlg()
{
}

NCityhallResidentDlg::~NCityhallResidentDlg()
{
}

void NCityhallResidentDlg::InitDlg()
{
	TCHAR* pText = GetTxtFromMgr(5004);
	for(int sun_count=0; sun_count<16;sun_count++)
	{
		pText = GetTxtFromMgr(5004+sun_count);
		StringCchCopy(clRankCandidate[sun_count].szStructureName, 64, pText);

		pText = GetTxtFromMgr(5020+sun_count);
		StringCchCopy(clRankCandidate[sun_count].szRankName, 64, pText);

		pText = GetTxtFromMgr(5036+sun_count);
		StringCchCopy(clRankCandidate[sun_count].szExplain, 256, pText);


	}
	cltCityHallManager *pCityhallManager = ((cltCityHallManager *)m_pStrManager);

	SetControlMap( EDIT_CHIEFNAME, TEXT("editbox_chiefname") );
	SetControlMap( EDIT_BEGINCHIEF, TEXT("editbox_beginchief") );
	SetControlMap( EDIT_ENDCHIEF, TEXT("editbox_endchief") );

	SetControlMap( BUTTON_RESIDENTAPPLY, TEXT("button_residentapply") );
	SetControlMap( BUTTON_CANCEL_RESIDENTAPPLY, TEXT("button_cancel_residentapply") );

	SetControlMap( BUTTON_RANKAPPLY, TEXT("button_rankapply") );
	SetControlMap( BUTTON_CANCEL_RANKAPPLY, TEXT("button_cancel_rankapply") );

	SetControlMap( COMBO_RANK, TEXT("combobox_rank") );


	CComboBox *pCombo = (CComboBox *)m_pControlMap[ COMBO_RANK ];
	stComboBoxItemData itemdata;

	// ��� Ÿ���� �޺��� �߰��Ѵ� 
/*
	SI32 ranktype;
	SI32 index = 0;

	while( pStructureInfo->siRankType = clRankCandidate[index].siRankType )
	{
		if( ranktype != 1 ) {

			itemdata.Init();
			itemdata.Set( clRankCandidate[index].szRankName );
			pCombo->AddItem( &itemdata );
		}

	}
*/
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

					if( pStructureInfo ) 
					{
						// [����] �ʺ��� ���� : �ʺ��� ������ �ҿ��� �ĺ���� ����Ʈ���� ��� �� �������� �Ѵ�
						if ( pclClient->IsCountrySwitch(Switch_TutorialVillage) == true )
						{
							if ( Const_Beginner_Village == pVillageInfo->siVillageUnique )
							{
								if ( RANKTYPE_GUILD != pStructureInfo->siRankType )
								{
									continue;
								}
							}
						}

						index = 0;
						while( clRankCandidate[index++].siRankType )
						{
							if( pStructureInfo->siRankType == clRankCandidate[index].siRankType ) 
							{

								itemdata.Init();
								itemdata.Set( clRankCandidate[index].szRankName );
								pCombo->AddItem( &itemdata );
								break;
							}
						}
						
					}
				}
			}
		}

	}

}

void NCityhallResidentDlg::Action()
{

	if( m_pBaseDlg->m_dwActionCount % 4 != 0 ) return;

	cltCityHallManager *pCityhallManager = ((cltCityHallManager *)m_pStrManager);

	TCHAR buffer[256 ];

	if( pCityhallManager->bRecvChiefInfo ) {
		
		StringCchCopy( buffer, 256, pCityhallManager->clChiefInfo[ 1 ].szID );
		SetEditText( EDIT_CHIEFNAME, buffer );

		TCHAR* pText = GetTxtFromMgr(1561);

		if( _tcscmp( pCityhallManager->clChiefInfo[ 1 ].szID, pText) == 0 ) {
			SetEditText( EDIT_BEGINCHIEF, buffer );
			SetEditText( EDIT_ENDCHIEF, buffer );
			return;
		}

		cltDate clDate;
		clDate.Set( &pCityhallManager->clClientStrInfo.clCityhallStrInfo.clChiefDate );

		pText = GetTxtFromMgr(1605);

		StringCchPrintf( buffer, 256, pText, clDate.uiYear, clDate.uiMonth, clDate.uiDay );
		SetEditText( EDIT_BEGINCHIEF, buffer );

		clDate.uiYear = clDate.uiYear + 2;

		StringCchPrintf( buffer, 256, pText, clDate.uiYear, clDate.uiMonth, clDate.uiDay );
		SetEditText( EDIT_ENDCHIEF, buffer );

	} else {

		TCHAR* pText = GetTxtFromMgr(1561);

		StringCchCopy( buffer, 256, pText );

		SetEditText( EDIT_CHIEFNAME, buffer );
		SetEditText( EDIT_BEGINCHIEF, buffer );
		SetEditText( EDIT_ENDCHIEF, buffer );
	}
}

void NCityhallResidentDlg::NDlgTabProc( UINT nEvent, int nControlID, CControllerObj *pControl )
{
	cltClient *pclclient = (cltClient*)pclClient;

	cltCityHallManager *pCityhallManager = ((cltCityHallManager *)m_pStrManager);

	CComboBox *pCombo = (CComboBox *)m_pControlMap[ COMBO_RANK ];
	stComboBoxItemData *pitemdata;

	CASE_CONTROL( BUTTON_RESIDENTAPPLY )
	{
		SI32 id = 1;

		if( id ) {
			// ������ �ֹ� ��� ��û�� �Ѵ�
			cltMsg clMsg(GAMEMSG_REQUEST_APPLYRESIDENT, pCityhallManager->siVillageUnique);
			pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		}
	}

	else CASE_CONTROL( BUTTON_CANCEL_RESIDENTAPPLY )
	{
		TCHAR buffer[256 ];

		TCHAR* pText = GetTxtFromMgr(1603);
		StringCchPrintf(buffer, 256,  pText );

		pText = GetTxtFromMgr(1604);

		stMsgBox MsgBox;
		// ���� dialog�� �� â ���� Child Dialog�϶�
		CControllerMgr *pParent = NULL;
		pParent = this->GetParentDialog();
		if(pParent == NULL ) return;
		MsgBox.Set( pParent, pText, buffer, MSGBOX_TYPE_YESNO, 2 );
		pclclient->SetMsgBox( &MsgBox, NULL, 0);

		//if (  MessageBox(NULL, buffer, pText, MB_ICONQUESTION | MB_YESNO) == IDNO ) return;
		//SI32 id = 1;

		//if( id ) {
		//	// ������ �ֹ� ��� ��û�� �Ѵ� 
		//	cltGameMsgRequest_CancelResident msg( pCityhallManager->siVillageUnique, pclClient->pclCM->CR[id]->pclCI->GetPersonID() );
		//	cltMsg clMsg(GAMEMSG_REQUEST_CANCELRESIDENT, sizeof( cltGameMsgRequest_CancelResident ), (BYTE*)&msg );
		//	pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		//}

	}

	else CASE_CONTROL( BUTTON_RANKAPPLY )
	{
		SI32 id = 1;

		if(id)
		{

			// ���õ� �ź� �̸��� Ȯ���Ѵ�. 
			int index = pCombo->GetSelectedIndex();

			if( index < 0 ) return;

			pitemdata = pCombo->GetItemData( index );

			// ���õ� ���ڿ��� �ٰŷ� ������ �ź��ڵ带 ���´�.
			SI32 ranktype = pCityhallManager->GetRankTypeFromRankName( pitemdata->strText );

			// [����] �ʺ��� ���� : �ʺ��� ������ ��常 �ҿ��� ��û �����ϰ� �� �ź��� ��ȣõ�簡 �ƴϸ� �ȵȴ�
			if ( pclClient->IsCountrySwitch(Switch_TutorialVillage) )
			{
				if ( pCityhallManager->siVillageUnique == Const_Beginner_Village )
				{
					if ( (RANKTYPE_GUILD != ranktype) || (false == pclClient->pclCM->CR[id]->pclCI->clBI.uiAngelSwitch) )
					{
						return;
					}
				}
			}


			if(ranktype)
			{
				cltSimpleRank clrank( ranktype, pCityhallManager->siVillageUnique );
				
				// ������ ���ĺ� ��� ��û�� ������. 
				cltMsg clMsg(GAMEMSG_REQUEST_CANDIDATE, sizeof(cltSimpleRank), (BYTE*)&clrank);				
				pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
			}
			else
			{
				TCHAR* pText = GetTxtFromMgr(1600);
				SetMainExplain(pText);
			}
		}
	}

	else CASE_CONTROL( BUTTON_CANCEL_RANKAPPLY )
	{
		TCHAR buffer[256 ];

		TCHAR* pText = GetTxtFromMgr(1601);
		StringCchPrintf(buffer, 256, pText );

		pText = GetTxtFromMgr(1602);

		stMsgBox MsgBox;
		// ���� dialog�� �� â ���� Child Dialog�϶�
		CControllerMgr *pParent = NULL;
		pParent = this->GetParentDialog();
		if(pParent == NULL ) return;
		MsgBox.Set( pParent, pText, buffer, MSGBOX_TYPE_YESNO, 3 );
		pclclient->SetMsgBox( &MsgBox, NULL, 0);

		//if (  MessageBox(NULL, buffer, pText, MB_ICONQUESTION | MB_YESNO) == IDNO ) return;

		//SI32 id = 1;
		//if( id ) {
		//	// ������ ���ĺ� ��� ��� ��û�� ������. 
		//	cltMsg clMsg(GAMEMSG_REQUEST_CANCELCANDIDATE, pCityhallManager->siVillageUnique);
		//	pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		//}
	}

}

void NCityhallResidentDlg::RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen )
{
	cltCityHallManager *pCityhallManager = ((cltCityHallManager *)m_pStrManager);

	switch( MsgIndex )
	{
	case 2:	//
		{
			if ( RetValue )
			{
				SI32 id = 1;

				if( id ) {
					// ������ �ֹ� ��� ��û�� �Ѵ� 
					cltGameMsgRequest_CancelResident msg( pCityhallManager->siVillageUnique, pclClient->pclCM->CR[id]->pclCI->GetPersonID() );
					cltMsg clMsg(GAMEMSG_REQUEST_CANCELRESIDENT, sizeof( cltGameMsgRequest_CancelResident ), (BYTE*)&msg );
					pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

				}
			}
		}
		break;
	case 3:	//
		{
			if ( RetValue )
			{
				SI32 id = 1;
				if( id ) {
					// ������ ���ĺ� ��� ��� ��û�� ������. 
					cltMsg clMsg(GAMEMSG_REQUEST_CANCELCANDIDATE, pCityhallManager->siVillageUnique);
					pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
				}
			}
		}
		break;
	}
}
