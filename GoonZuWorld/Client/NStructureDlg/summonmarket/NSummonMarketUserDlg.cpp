#include "NSummonMarketDlg.h"

#include "..\..\Server\Server.h"
#include "Char\CharManager\CharManager.h"

#include "MsgRval-Define.h"
#include "../../CommonLogic/MsgType-Structure.h"
#include "../../CommonLogic/Msg/MsgType-SummonMarket.h"

#include <tchar.h>
#include "../../InterfaceMgr/Interface/List.h"
#include "../../InterfaceMgr/Interface/Edit.h"
#include "../../InterfaceMgr/Interface/Static.h"
#include "../../InterfaceMgr/Interface/CheckBox.h"

#include "../../../CommonLogic/MsgType-Structure.h"
#include "../../../Client/Interface/SoundOnOffDlg/SoundOnOffDlg.h"

#include "../../Client/InterfaceMgr/InterfaceMgr.h"
#include "Char\CharCommon\Char-Common.h"

extern cltCommonLogic* pclClient;

NSummonMarketUserDlg::NSummonMarketUserDlg()
{
	GP.LoadSprFromFile( TEXT("Interface/Pannel/IMAGE_33x30_00_000.SPR"), &m_sprSummonPortrait);
	m_Price = 0;
}

NSummonMarketUserDlg::~NSummonMarketUserDlg()
{
}

void NSummonMarketUserDlg::InitDlg()
{
	// �忹�� �Ŵ���
	cltSummonMarketManager *pSummonManager = ((cltSummonMarketManager *)m_pStrManager);
	if( pSummonManager == NULL )
		return;

	SetControlMap(	BUTTON_SELL	,			TEXT("button_sell"));
	SetControlMap(	BUTTON_CANCELORDER,		TEXT("button_cancelorder"));
	SetControlMap(	EDITBOX_REALFEE,		TEXT("editbox_realfee"));
	SetControlMap(	EDITBOX_SELLPRICE,		TEXT("editbox_sellprice"));
	SetControlMap(	EDITBOX_SELLPRICECHAR,	TEXT("editbox_sellpricechar"));
	SetControlMap(	EDITBOX_PLAYERNAME,		TEXT("editbox_playername"));
	SetControlMap(	LISTBOX_MYSUMMON,		TEXT("listbox_mysummon"));
	SetControlMap(	LISTBOX_MYORDER,		TEXT("listbox_myorder"));
	
	SetControlMap(	LISTBOX_DETAILINFO,		TEXT("listbox_base_info"));
	SetControlMap(	LISTBOX_ABILITY_INFO,	TEXT("listbox_ability_ifo"));
	
	SetControlMap(  STATICTEXT_FEERATE,		TEXT("statictext_feerate" ));
	SetControlMap(  CHECKBOX_SELECTSELL,	TEXT("checkbox_selectsell" ));

	SetControlMap(  IMAGESTATIC_MYSUMMON_1,	TEXT("imagestatic_NONAME1" ));
	SetControlMap(  IMAGESTATIC_MYSUMMON_2,	TEXT("imagestatic_NONAME2" ));
	SetControlMap(  IMAGESTATIC_MYSUMMON_3,	TEXT("imagestatic_NONAME3" ));
	SetControlMap(  IMAGESTATIC_MYORDER_1,	TEXT("imagestatic_NONAME4" ));
	SetControlMap(  IMAGESTATIC_MYORDER_2,	TEXT("imagestatic_NONAME5" ));
	SetControlMap(  IMAGESTATIC_MYORDER_3,	TEXT("imagestatic_NONAME6" ));

	SetControlMap(  STATIC_SELECT_CHAR_NAME,	TEXT("statictext_NONAME6" ));

	// ����Ʈ ���
	CList *pList_mysummon		 = (CList*)m_pControlMap[ LISTBOX_MYSUMMON ];
	CList *pList_myorder		 = (CList*)m_pControlMap[ LISTBOX_MYORDER ];
	CList *pList_detailinfo		 = (CList*)m_pControlMap[ LISTBOX_DETAILINFO ];
	CList *pList_Abilityinfo	 = (CList*)m_pControlMap[ LISTBOX_ABILITY_INFO ];
	CEdit *pEdit_sellprice		 = (CEdit*)m_pControlMap[ EDITBOX_SELLPRICE ];
	CEdit *pEdit_selectname		 = (CEdit*)m_pControlMap[ EDITBOX_PLAYERNAME ];
	CCheckBox *pCheck_selectsell = (CCheckBox*)m_pControlMap[ CHECKBOX_SELECTSELL ];
	CStatic *pStatic_Char_Name   = (CStatic*)m_pControlMap[ STATIC_SELECT_CHAR_NAME ];
	
	//[����] ��Ʈ�� �Ⱥ��̰�. 
	pList_mysummon->Show(false);	
	pList_myorder->Show(false);	
	pCheck_selectsell->Show(false);
	pEdit_selectname->Show(false);
	pStatic_Char_Name->Show(false);

	

	// default�� �Ϲݰŷ��� ����
	pCheck_selectsell->SetCheck( false );
	pEdit_selectname->Enable( false );

	if( pList_mysummon == NULL || pList_mysummon == NULL || pList_mysummon == NULL ) 
		return; 

	pSummonManager->siMySummonSelectedIndex = -1;
	pSummonManager->siMyOrderSelectedIndex = -1;

#ifdef _SAFE_MEMORY
	pSummonManager->clMyOrder.ZeroMem();
#else
	ZeroMemory( pSummonManager->clMyOrder, sizeof( cltSummonOrder ) );
#endif
	
	

	pList_mysummon->SetTextPrintOption( DT_LEFT | DT_VCENTER | DT_SINGLELINE );
	pList_myorder->SetTextPrintOption( DT_LEFT | DT_VCENTER | DT_SINGLELINE );
	pList_mysummon->SetBorder( true );
	pList_mysummon->SetBKColorUse( true );
	pList_myorder->SetBorder( true );
	pList_myorder->SetBKColorUse( true );
	pList_detailinfo->SetBorder( true );
	pList_Abilityinfo->SetBorder( true );
	pList_detailinfo->SetBKColorUse( true );
	pList_Abilityinfo->SetBKColorUse( true );

	TCHAR* pText[3];
	pText[0] = GetTxtFromMgr(449);
	pText[1] = GetTxtFromMgr(1556);
	pText[2] = NULL;

	int width[]		= { 70, 100 };
	int i;
	for( i = 0; i < 2; ++i ) 
	{ 
        //pList_mysummon->SetColumn( i, width[i], pText[i] );
        //pList_myorder->SetColumn(  i, width[i], pText[i] );
	}

	pList_mysummon->Refresh();
	pList_myorder->Refresh();

	pEdit_sellprice->SetNumberMode( true );

	ShowMySummonList();
	ShowMyOrderInfo();

	{
		int width[]  = { 75, 113 };   
		int width2[] = { 75,  73 };  
		//pList_detailinfo->SetTextPrintOption( DT_LEFT | DT_VCENTER | DT_SINGLELINE );
		//pList_Abilityinfo->SetTextPrintOption( DT_LEFT | DT_VCENTER | DT_SINGLELINE );

		TCHAR* pText[3];

		pText[0] = GetTxtFromMgr(1780);
		pText[1] = GetTxtFromMgr(1565);
		pText[2] = NULL;

		for( i = 0; i < 2; ++i ) 
		{ 
			pList_detailinfo->SetColumn(  i, width[i], pText[i] );
			pList_Abilityinfo->SetColumn( i, width2[i], pText[i] );
		}
	}		

	pList_detailinfo->Refresh();
	pList_Abilityinfo->Refresh();

	SI32 id = 1;

	// �� �ֹ� ���� ��û 
	cltMsg clMsg( GAMEMSG_REQUEST_SUMMONMARKET_MYORDER, 0 );
	pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
}

void NSummonMarketUserDlg::Action()
{
	// �忹�� �Ŵ���
	cltSummonMarketManager *pSummonManager = ((cltSummonMarketManager *)m_pStrManager);
	if( pSummonManager == NULL ) return;

	// ����Ʈ ���
	CList *pList_mysummon = (CList*)m_pControlMap[ LISTBOX_MYSUMMON ];
	CList *pList_myorder = (CList*)m_pControlMap[ LISTBOX_MYORDER ];
	CList *pList_detailinfo = (CList*)m_pControlMap[ LISTBOX_DETAILINFO ];
	if( pList_mysummon == NULL || pList_mysummon == NULL || pList_mysummon == NULL ) return; 

	// ������ ������ ǥ���Ѵ�. 
	ShowFee();

	if( pSummonManager->bShowMyOrderSwitch )
	{
		pSummonManager->bShowMyOrderSwitch = FALSE;
		ShowMyOrderList( );
	}

	TCHAR buffer[256];
	TCHAR *pchTmp = NULL;
	pchTmp = GetEditText( EDITBOX_SELLPRICE );
	if( pchTmp == NULL ) return;
	if( _tcslen(pchTmp) >= 50 ) return;
	_tcscpy( buffer, pchTmp );
	SI64 price = _tstoi64(buffer);
	ShowRealFee( price );

//	TCHAR* pText = GetTxtFromMgr(611);
//	g_JYLibFunction.SetNumUnit(price, buffer, 256, pText);
//	SetEditText( EDITBOX_SELLPRICECHAR, buffer );

	
}

void NSummonMarketUserDlg::NDlgTabProc( UINT nEvent, int nControlID, CControllerObj *pControl )
{
	cltClient *pclclient = (cltClient*)pclClient;
	// �忹�� �Ŵ���
	cltSummonMarketManager *pSummonManager = ((cltSummonMarketManager *)m_pStrManager);
	if( pSummonManager == NULL ) return;

	// ����Ʈ ���
	CList *pList_mysummon = (CList*)m_pControlMap[ LISTBOX_MYSUMMON ];
	CList *pList_myorder = (CList*)m_pControlMap[ LISTBOX_MYORDER ];
	CList *pList_detailinfo = (CList*)m_pControlMap[ LISTBOX_DETAILINFO ];
	CEdit *pEdit_sellprice = (CEdit*)m_pControlMap[ EDITBOX_SELLPRICE ];
	CEdit *pEdit_selectname = (CEdit*)m_pControlMap[ EDITBOX_PLAYERNAME ];
	CButton *pButton_sell = (CButton*)m_pControlMap[ BUTTON_SELL ];
	CCheckBox *pCheck_selectsell = (CCheckBox*)m_pControlMap[ CHECKBOX_SELECTSELL ];

	if( pList_mysummon == NULL || pList_mysummon == NULL || pList_mysummon == NULL 
		|| pCheck_selectsell == NULL) return; 

	SI32 id = 1;

	CASE_CONTROL( EDITBOX_SELLPRICE )
	{
		switch( nEvent )
		{
			case EVENT_EDITBOX_CHANGE:
				{
					if(11 < _tcslen(GetEditText(EDITBOX_SELLPRICE)))
					{    
						/*if(MAX_TRADE_MONEY < _tstoi64(GetEditText(EDITBOX_SELLPRICE)))
						{
							pEdit_sellprice->SetText(SI64ToString(MAX_TRADE_MONEY));
						}*/

						pEdit_sellprice->SetText(SI64ToString(_tstoi64(GetEditText(EDITBOX_SELLPRICE))/10));
					}
				}
				break;
		}
	}
	else CASE_CONTROL( LISTBOX_MYSUMMON )
	{
		switch( nEvent )
		{
		case EVENT_LISTBOX_SELECTION:
			{
				TCHAR *pchTmp = NULL;
				SI16 siRow = -1, siCol = -1;
				
				pList_mysummon->GetSelectedIndex( &siRow, &siCol );
				if( siRow == -1 || siCol == -1 ) return;
				stListBoxItemData *pstListBoxItemData = NULL;
				pstListBoxItemData = pList_mysummon->GetItemData( siRow, 0 );
				if( pstListBoxItemData == NULL ) return;
				pSummonManager->siMySummonSelectedIndex = pstListBoxItemData->siParam[0];	

				ShowMySummonInfo( );
			}
			break;

		default:
			{
				//pSummonManager->siMySummonSelectedIndex = -1;
			}
			break;
		}
	}
	else CASE_CONTROL( LISTBOX_MYORDER )
	{
		switch( nEvent )
		{
		case EVENT_LISTBOX_SELECTION:
			{
				TCHAR *pchTmp = NULL;
				SI16 siRow = -1, siCol = -1;
				
				pList_myorder->GetSelectedIndex( &siRow, &siCol );
				if( siRow == -1 || siCol == -1 ) return;
				stListBoxItemData *pstListBoxItemData = NULL;
				pstListBoxItemData = pList_myorder->GetItemData( siRow, 0 );
				if( pstListBoxItemData == NULL ) return;
				pSummonManager->siMyOrderSelectedIndex = pstListBoxItemData->siParam[0];

				ShowMyOrderInfo( );
			}
			break;
		default:
			{
				//pSummonManager->siMyOrderSelectedIndex = -1;
			}
			break;
		}
	} 
	else CASE_CONTROL( BUTTON_SELL )
	{
		switch( nEvent )
		{
		case EVENT_BUTTON_CLICKED:
			{
				if( pSummonManager->siMySummonSelectedIndex < 0 ) 
				{
					TCHAR* pText = GetTxtFromMgr(3488);
					SetMainExplain(pText);
					break;
				}

				cltSummon *pclSummon = pclClient->pclCM->CR[ 1 ]->pclCI->clSummonInfo.GetSummon( pSummonManager->siMySummonSelectedIndex );
				if( pclSummon == NULL ) 
					break;

				// ��ȯ���� �׾����� �ֹ��� �� ����
				if( pclSummon->siStatus == SUMMON_STATUS_DEAD ||
					pclSummon->clIP.GetLife() <= 0 ) 
				{
					TCHAR* pText = GetTxtFromMgr(1796);
					SetMainExplain(  pText );
					break;	
				}
								
				// ��ȯ���� ��� ���� ������ �ǸŰ� �Ұ���.	
				if(TRUE == pclClient->pclCM->CR[ 1 ]->pclCI->clSummonInfo.IsHaveEquipItem( pSummonManager->siMySummonSelectedIndex ) )
				{
					TCHAR* pText = GetTxtFromMgr(15355);
					SetMainExplain(  pText );
					break;	
				}

				if( pclClient->pclKindInfoSet->IsValidKind(pclSummon->siKind) == false )
				{
					TCHAR* pText = GetTxtFromMgr(1795);
					SetMainExplain(  pText );
					break;
				}

				TCHAR personname[ MAX_PLAYER_NAME ];

				TCHAR buffer[ 1024 ];
				GMONEY price;

				price = _tstoi64(GetEditText(EDITBOX_SELLPRICE));

				if( price <= 0 ) 
				{
					TCHAR* pText = GetTxtFromMgr(1758);
					SetMainExplain(  pText );
					break;
				}

				if( price < 5000 ) 
				{
					TCHAR* pText = GetTxtFromMgr(1759);
					SetMainExplain(  pText );
					break;
				}

				if( price > MAX_TRADE_MONEY ) 
				{
					TCHAR* pText = GetTxtFromMgr(1794);
					SetMainExplain(  pText );
					break;
				}

				if( pclCM->CR[id]->pclCI->clBank.clAccountNum.siVillageUnique == 0 )
				{
					TCHAR* pText = GetTxtFromMgr(5590);
					SetMainExplain(pText);
					break; 
				}

				m_Price = price;

				cltKindInfo* pclKI	= NULL;
				//[����] ��ȯ�� ���̺� �и�. => 2008-6-18
				if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
				{
					pclKI = pclClient->pclKindInfoSet->pclSummonKI[ pclSummon->siKind ];
				}
				else
				{
					pclKI = pclClient->pclKindInfoSet->pclKI[ pclSummon->siKind ];
				}
				if(NULL == pclKI)
					break;

				if(false == pclKI->bSummonTrade)
				{
					TCHAR* pText = GetTxtFromMgr(8584);
					SetMainExplain(  pText );
					break;
				}

				// �����ŷ���
				if( pCheck_selectsell->IsCheck() == TRUE )
				{
					TCHAR *pchTmp = NULL;
					pchTmp = GetEditText( EDITBOX_PLAYERNAME );
					if(pchTmp == NULL ) return;
					if( _tcslen( pchTmp ) >= 32 ) return;
					_tcscpy( buffer, pchTmp );

					for( int i = 0; i < (int)(_tcslen( buffer )); ++i ) 
					{
						if( buffer[ i ] != ' ' ) break;
					}

					StringCchCopy( personname, MAX_PLAYER_NAME, &buffer[ i ] );

					if( personname[ 0 ] == NULL ) {
						TCHAR* pText = GetTxtFromMgr(3639);
						SetMainExplain(pText);
						break;
					}
				}

				GMONEY	tax	  = (GMONEY)((double)price * 0.01);
				TCHAR*	pText = GetTxtFromMgr(3197);
				StringCchPrintf(buffer, sizeof(buffer), pText, tax);

				stMsgBox MsgBox;
				// ���� dialog�� �� â ���� Child Dialog�϶�
				CControllerMgr *pParent = GetParentDialog();
				if(pParent == NULL )		return;

				// �Ϲݰŷ���
				if( pCheck_selectsell->IsCheck() == FALSE )
				{
					pText = GetTxtFromMgr(1798); 

					MsgBox.Set( pParent, pText, buffer, MSGBOX_TYPE_YESNO, 0 );
					BYTE TempBuffer[ 128 ];
					SI16 Size = sizeof( id ) + sizeof( price );
					memcpy( TempBuffer, &id, sizeof( id ) );
					memcpy( &TempBuffer[ sizeof(id) ], &price, sizeof( price ) );
					pclclient->SetMsgBox( &MsgBox, TempBuffer, Size );
				}
				else	// �����ŷ���
				{
					pText = GetTxtFromMgr(3196); 

					MsgBox.Set( pParent, pText, buffer, MSGBOX_TYPE_YESNO, 1 );
					BYTE TempBuffer[ 128 ];
					SI16 Size = sizeof( id ) + sizeof( price ) + sizeof( personname );
					memcpy( TempBuffer, &id, sizeof( id ) );
					memcpy( &TempBuffer[ sizeof(id) ], &price, sizeof( price ) );
					memcpy( &TempBuffer[ sizeof(id) + sizeof( price ) ], personname, sizeof( personname ) );
					pclclient->SetMsgBox( &MsgBox, TempBuffer, Size );
				}
			}
			break;
		}
	}
	else CASE_CONTROL( BUTTON_CANCELORDER )
	{
		switch( nEvent )
		{
		case EVENT_BUTTON_CLICKED:
			{
				// ��ȯ�� ȸ�� 
				if( pSummonManager->siMyOrderSelectedIndex < 0 ) 
					break;

				if(FALSE == pclClient->pclCM->CR[1]->pclCI->clSummonInfo.CanHaveSummon())
				{
					// ��ȯ���� ���̻� ������ �� ���� 
					TCHAR* pText = GetTxtFromMgr(15358);
					SetMainExplain(  pText );
					break;
				}

				cltGameMsgRequest_SummonMarketCancelOrder sendMsg(
					pSummonManager->clMyOrder[ pSummonManager->siMyOrderSelectedIndex ].siIndex );

				cltMsg clMsg( GAMEMSG_REQUEST_SUMMONMARKET_CANCELORDER, sizeof( sendMsg), (BYTE*)&sendMsg );
				pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg );

			}
			break;
		}
	}
	else CASE_CONTROL( CHECKBOX_SELECTSELL )
	{
		switch( nEvent )
		{
			case EVENT_CHECKBOX_CHANGED:
				{
					TCHAR* pText = NULL;
					if( pCheck_selectsell->IsCheck() == FALSE )
					{
						pText = GetTxtFromMgr( 4816 );
						pButton_sell->SetText( pText );
						pEdit_selectname->SetText( TEXT("") );	// �����ŷ� �ƴҶ� �����ŷ��ڸ� ����
						pEdit_selectname->Enable( false );

					}
					else
					{
						pText = GetTxtFromMgr( 4818 );
						pButton_sell->SetText( pText );
						pEdit_selectname->Enable( true );
					}
				}
		}
	}
	else CASE_CONTROL( IMAGESTATIC_MYSUMMON_1 )
	{
		switch( nEvent )
		{
			case EVENT_IMAGESTATIC_LBUTTONUP:
				{
					pSummonManager->siMySummonSelectedIndex = 0;	

					ShowMySummonInfo();
					ClickSummonPotrait(pSummonManager->siMySummonSelectedIndex);
				}
				break;
		}
	}
	else CASE_CONTROL( IMAGESTATIC_MYSUMMON_2 )
	{
		switch( nEvent )
		{
		case EVENT_IMAGESTATIC_LBUTTONUP:
			{
				pSummonManager->siMySummonSelectedIndex = 1;	

				ShowMySummonInfo();
				ClickSummonPotrait(pSummonManager->siMySummonSelectedIndex);
			}
			break;
		}
	}
	else CASE_CONTROL( IMAGESTATIC_MYSUMMON_3 )
	{
		switch( nEvent )
		{
		case EVENT_IMAGESTATIC_LBUTTONUP:
			{
				pSummonManager->siMySummonSelectedIndex = 2;	

				ShowMySummonInfo();
				ClickSummonPotrait(pSummonManager->siMySummonSelectedIndex);
			}
			break;
		}
	}
	else CASE_CONTROL( IMAGESTATIC_MYORDER_1 )
	{
		switch( nEvent )
		{
		case EVENT_IMAGESTATIC_LBUTTONUP:
			{
				pSummonManager->siMyOrderSelectedIndex = 0;

				ShowMyOrderInfo();
				ClickSummonPotrait(pSummonManager->siMyOrderSelectedIndex + 3);
			}
			break;  
		}
	}
	else CASE_CONTROL( IMAGESTATIC_MYORDER_2 )
	{
		switch( nEvent )
		{
		case EVENT_IMAGESTATIC_LBUTTONUP:
			{
				pSummonManager->siMyOrderSelectedIndex = 1;

				ShowMyOrderInfo();
				ClickSummonPotrait(pSummonManager->siMyOrderSelectedIndex + 3);
			}
			break;
		}
	}
	else CASE_CONTROL( IMAGESTATIC_MYORDER_3 )
	{
		switch( nEvent )
		{
		case EVENT_IMAGESTATIC_LBUTTONUP:
			{
				pSummonManager->siMyOrderSelectedIndex = 2;

				ShowMyOrderInfo();
				ClickSummonPotrait(pSummonManager->siMyOrderSelectedIndex + 3); 
			}
			break;
		}
	}
}

void NSummonMarketUserDlg::ShowMySummonInfo( )
{
	// �忹�� �Ŵ���
	cltSummonMarketManager *pSummonManager = ((cltSummonMarketManager *)m_pStrManager);
	if( pSummonManager == NULL ) return;
	// ����Ʈ ���
	CList *pList_mysummon	 = (CList*)m_pControlMap[ LISTBOX_MYSUMMON ];
	CList *pList_myorder	 = (CList*)m_pControlMap[ LISTBOX_MYORDER ];
	CList *pList_Abilityinfo = (CList*)m_pControlMap[ LISTBOX_ABILITY_INFO ];
	CList *pList_detailinfo	 = (CList*)m_pControlMap[ LISTBOX_DETAILINFO ];
	if( pList_mysummon == NULL || pList_mysummon == NULL || pList_mysummon == NULL ) return; 

	if( pSummonManager->siMySummonSelectedIndex < 0 || 
		pSummonManager->siMySummonSelectedIndex >= MAX_SUMMON_OWN ) return;

	TCHAR buffer[256];

	pList_detailinfo->Clear();
	pList_Abilityinfo->Clear();

	TCHAR* pText[16];

	pText[0]  = GetTxtFromMgr(1782);
	pText[1]  = GetTxtFromMgr(1556);
	pText[2]  = GetTxtFromMgr(1506);
	pText[3]  = GetTxtFromMgr(1319);
	pText[4]  = GetTxtFromMgr(1783);
	pText[5]  = GetTxtFromMgr(1784);
	pText[6]  = GetTxtFromMgr(1785);
	pText[7]  = GetTxtFromMgr(1786);
	pText[8]  = GetTxtFromMgr(1787);
	pText[9]  = GetTxtFromMgr(1788);
	pText[10] = GetTxtFromMgr(1789);
	pText[11] = GetTxtFromMgr(1790);
	pText[12] = GetTxtFromMgr(1791);
	pText[13] = GetTxtFromMgr(8594);
	pText[14] = GetTxtFromMgr(8607);
	pText[15] = GetTxtFromMgr(8608);

	if( pSummonManager->siMySummonSelectedIndex < 0 ) return;

	cltSummon *pclSummon = pclClient->pclCM->CR[ 1 ]->pclCI->clSummonInfo.GetSummon( pSummonManager->siMySummonSelectedIndex );
	if(0 >= pclSummon->siKind)
	{
		pList_detailinfo->Refresh();
		pList_Abilityinfo->Refresh();
		return;
	}

	stListBoxItemData stTmpListBoxItemData;
	// ����
	stTmpListBoxItemData.Init();
	stTmpListBoxItemData.Set( 0, pText[ 0 ] );
	cltKindInfo* pclKI	= NULL;
	//[����] ��ȯ�� ���̺� �и�. => 2008-6-18
	if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
	{
		pclKI = pclClient->pclKindInfoSet->pclSummonKI[ pclSummon->siKind ];
	}
	else
	{
		pclKI = pclClient->pclKindInfoSet->pclKI[ pclSummon->siKind ];
	}
	if(NULL == pclKI)
		return;

	stTmpListBoxItemData.Set( 1, (TCHAR*)pclKI->GetName() );
	pList_detailinfo->AddItem( &stTmpListBoxItemData );

	// �̸�
	stTmpListBoxItemData.Init();
	stTmpListBoxItemData.Set( 0, pText[ 1 ] );
	stTmpListBoxItemData.Set( 1, pclSummon->szName );
	pList_detailinfo->AddItem( &stTmpListBoxItemData );

	// ����
	_itot( pclSummon->clIP.GetLevel(), buffer, 10 );
	stTmpListBoxItemData.Init();
	stTmpListBoxItemData.Set( 0, pText[ 2 ] );
	stTmpListBoxItemData.Set( 1, buffer );
	pList_detailinfo->AddItem( &stTmpListBoxItemData );

	// ����ġ
	
	_i64tot( pclSummon->clIP.GetCurExp(), buffer, 10 );// SI32->SI64 ����ġ �����÷ο춧���� ����
	stTmpListBoxItemData.Init();
	stTmpListBoxItemData.Set( 0, pText[ 3 ] );
	stTmpListBoxItemData.Set( 1, buffer );
	pList_detailinfo->AddItem( &stTmpListBoxItemData );

	// ü��
	
	_itot( pclSummon->clIP.GetLife(), buffer, 10 );
	stTmpListBoxItemData.Init();
	stTmpListBoxItemData.Set( 0, pText[ 4 ] );
	stTmpListBoxItemData.Set( 1, buffer );
	pList_detailinfo->AddItem( &stTmpListBoxItemData );

	// ������

	_itot( pclSummon->clIP.GetMana(), buffer, 10 );
	stTmpListBoxItemData.Init();
	stTmpListBoxItemData.Set( 0, pText[ 5 ] );
	stTmpListBoxItemData.Set( 1, buffer );
	pList_detailinfo->AddItem( &stTmpListBoxItemData );

	// ���׹̳�
	stTmpListBoxItemData.Init();
	stTmpListBoxItemData.Set( 0, pText[ 13 ] );
	StringCchPrintf(buffer, sizeof(buffer), GetTxtFromMgr(1252), pclSummon->clIP.GetLuk()/10); 
	stTmpListBoxItemData.Set( 1, buffer );
	pList_detailinfo->AddItem( &stTmpListBoxItemData );
	

	// �ٷ�
	_itot( pclSummon->clIP.GetStr(), buffer, 10 );
	stTmpListBoxItemData.Init();
	stTmpListBoxItemData.Set( 0, pText[ 6 ] );
	stTmpListBoxItemData.Set( 1, buffer );
	pList_Abilityinfo->AddItem( &stTmpListBoxItemData );

	// ���߷�

	_itot( pclSummon->clIP.GetDex(), buffer, 10 );
	stTmpListBoxItemData.Init();
	stTmpListBoxItemData.Set( 0, pText[ 7 ] );
	stTmpListBoxItemData.Set( 1, buffer );
	pList_Abilityinfo->AddItem( &stTmpListBoxItemData );

	// ����
	_itot( pclSummon->clIP.GetMag(), buffer, 10 );
	stTmpListBoxItemData.Init();
	stTmpListBoxItemData.Set( 0, pText[ 8 ] );
	stTmpListBoxItemData.Set( 1, buffer );
	pList_Abilityinfo->AddItem( &stTmpListBoxItemData );
  
	// �����
	_itot( pclSummon->clIP.GetVit(), buffer, 10 );
	stTmpListBoxItemData.Init();
	stTmpListBoxItemData.Set( 0, pText[ 9 ] );
	stTmpListBoxItemData.Set( 1, buffer );
	pList_Abilityinfo->AddItem( &stTmpListBoxItemData );

	// ���ʽ�
	_itot( pclSummon->clIP.GetBonus(), buffer, 10 );
	stTmpListBoxItemData.Init();
	stTmpListBoxItemData.Set( 0, pText[ 10 ] );
	stTmpListBoxItemData.Set( 1, buffer );
	pList_Abilityinfo->AddItem( &stTmpListBoxItemData );

	// ���뼮
	_itot( pclSummon->siAttackWearStoneNum, buffer, 10 );
	stTmpListBoxItemData.Init();
	stTmpListBoxItemData.Set( 0, pText[ 14 ] );
	stTmpListBoxItemData.Set( 1, buffer );
	pList_Abilityinfo->AddItem( &stTmpListBoxItemData );

	// ���뼮
	_itot( pclSummon->siDefenseWearStoneNum, buffer, 10 );
	stTmpListBoxItemData.Init();
	stTmpListBoxItemData.Set( 0, pText[ 15 ] );
	stTmpListBoxItemData.Set( 1, buffer );
	pList_Abilityinfo->AddItem( &stTmpListBoxItemData );

	
	// ����
	/*for( SI32 i = 0; i < 2; ++i )
	{
		stTmpListBoxItemData.Init();
		stTmpListBoxItemData.Set( 0, pText[ 11 + i ] );
		if( pclSummon->clScroll.siUnique[i] )
		{
			stTmpListBoxItemData.Set( 0, (TCHAR *)pclClient->pclItemManager->GetName( pclSummon->clScroll.siUnique[i] ) );

			StringCchPrintf( buffer, 256, TEXT("%0.1f%%"), (float)(pclSummon->clScroll.siPercent[i] / 10.0));
			stTmpListBoxItemData.Set( 1, buffer );
		}
		else
		{
			stTmpListBoxItemData.Set( 0, TEXT("") );
			stTmpListBoxItemData.Set( 1, TEXT("") );
		}

		pList_detailinfo->AddItem( &stTmpListBoxItemData );
	}*/

	pList_detailinfo->Refresh();
	pList_Abilityinfo->Refresh();
}

void NSummonMarketUserDlg::ShowMyOrderInfo( )
{

	// �忹�� �Ŵ���
	cltSummonMarketManager *pSummonManager = ((cltSummonMarketManager *)m_pStrManager);
	if( pSummonManager == NULL ) return;

	// ����Ʈ ���
	CList *pList_mysummon	 = (CList*)m_pControlMap[ LISTBOX_MYSUMMON ];
	CList *pList_myorder	 = (CList*)m_pControlMap[ LISTBOX_MYORDER ];
	CList *pList_detailinfo  = (CList*)m_pControlMap[ LISTBOX_DETAILINFO ];
	CList *pList_Abilityinfo = (CList*)m_pControlMap[ LISTBOX_ABILITY_INFO ];
	if( pList_mysummon   == NULL || pList_myorder     == NULL || 
		pList_detailinfo == NULL || pList_Abilityinfo == NULL	) 
		return; 

	if( pSummonManager->siMyOrderSelectedIndex < 0 ||
		pSummonManager->siMyOrderSelectedIndex >= MAX_SUMMONMARKET_ORDER_PER_PERSON ) return;

	TCHAR buffer[256];

	pList_detailinfo->Clear();
	pList_Abilityinfo->Clear(); 

	TCHAR* pText[16];
  
	pText[0]  = GetTxtFromMgr(1782);
	pText[1]  = GetTxtFromMgr(1556);
	pText[2]  = GetTxtFromMgr(1506);
	pText[3]  = GetTxtFromMgr(1319);
	pText[4]  = GetTxtFromMgr(1783);
	pText[5]  = GetTxtFromMgr(1784);
	pText[6]  = GetTxtFromMgr(1785);
	pText[7]  = GetTxtFromMgr(1786);
	pText[8]  = GetTxtFromMgr(1787);
	pText[9]  = GetTxtFromMgr(1788);
	pText[10] = GetTxtFromMgr(1789);
	pText[11] = GetTxtFromMgr(1790);
	pText[12] = GetTxtFromMgr(1791);
	pText[13] = GetTxtFromMgr(8594);
	pText[14] = GetTxtFromMgr(8607);
	pText[15] = GetTxtFromMgr(8608);

	if( pSummonManager->siMyOrderSelectedIndex < 0 ) return;

	//[����] ���� �Ǹ��Ϸ��� �ø� ���� �����ֱ�.
	CEdit *pEdit_sellpriceChar = (CEdit*)m_pControlMap[ EDITBOX_SELLPRICECHAR ];
	TCHAR* pSellPriceText = GetTxtFromMgr(611);
	g_JYLibFunction.SetNumUnit(pSummonManager->clMyOrder[pSummonManager->siMyOrderSelectedIndex].siPrice, buffer, 256, pSellPriceText);
	SetEditText( EDITBOX_SELLPRICECHAR, buffer );
	ZeroMemory(buffer, sizeof(buffer));  


	cltSummon *pclSummon = &(pSummonManager->clMyOrder[ pSummonManager->siMyOrderSelectedIndex ].clSummon);
	if(0 >= pclSummon->siKind)  
	{
		pList_detailinfo->Refresh();
		pList_Abilityinfo->Refresh();
		return;
	}

	stListBoxItemData stTmpListBoxItemData;
	// ����
	stTmpListBoxItemData.Init();
	stTmpListBoxItemData.Set( 0, pText[0 ] );

    cltKindInfo* pclKI	= NULL;
	//[����] ��ȯ�� ���̺� �и�. => 2008-6-18
	if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
	{
		pclKI = pclClient->pclKindInfoSet->pclSummonKI[ pclSummon->siKind ];
	}
	else
	{
		pclKI = pclClient->pclKindInfoSet->pclKI[ pclSummon->siKind ];
	}
	if(NULL == pclKI)
		return;

	stTmpListBoxItemData.Set( 1, (TCHAR*)pclKI->GetName() );
	pList_detailinfo->AddItem( &stTmpListBoxItemData );

	// �̸�
	stTmpListBoxItemData.Init();
	stTmpListBoxItemData.Set( 0, pText[ 1] );
	stTmpListBoxItemData.Set( 1, pclSummon->szName );
	pList_detailinfo->AddItem( &stTmpListBoxItemData );

	// ����
	_itot( pclSummon->clIP.GetLevel(), buffer, 10 );
	stTmpListBoxItemData.Init();
	stTmpListBoxItemData.Set( 0, pText[2 ] );
	stTmpListBoxItemData.Set( 1, buffer );
	pList_detailinfo->AddItem( &stTmpListBoxItemData );

	// ����ġ
	
	_i64tot( pclSummon->clIP.GetCurExp(), buffer, 10 );// SI32->SI64 ����ġ �����÷ο춧���� ����
	stTmpListBoxItemData.Init();
	stTmpListBoxItemData.Set( 0, pText[3 ] );
	stTmpListBoxItemData.Set( 1, buffer );
	pList_detailinfo->AddItem( &stTmpListBoxItemData );

	// ü��
	
	_itot( pclSummon->clIP.GetLife(), buffer, 10 );
	stTmpListBoxItemData.Init();
	stTmpListBoxItemData.Set( 0, pText[ 4] );
	stTmpListBoxItemData.Set( 1, buffer );
	pList_detailinfo->AddItem( &stTmpListBoxItemData );

	// ������
	_itot( pclSummon->clIP.GetMana(), buffer, 10 );
	stTmpListBoxItemData.Init();
	stTmpListBoxItemData.Set( 0, pText[5 ] );
	stTmpListBoxItemData.Set( 1, buffer );
	pList_detailinfo->AddItem( &stTmpListBoxItemData );  

	// ���׹̳�
	stTmpListBoxItemData.Init();
	stTmpListBoxItemData.Set( 0, pText[ 13 ] );
	
	// [����] : ATB_SUMMONSTAMINASTATIC�� ������ �⺻ ��ȯ�� ���¹̳ʰ��ҷ��� �����Ų��. (08.07.18)
	SI32 amt = 0;
	if (pclKI->IsAtb(ATB_SUMMONSTAMINASTATIC) == TRUE )
	{
		amt = SUMMON_DECREASESTAMINA_AMT;
	}
	else
	{
		// �Ҹ�Ǵ� ���¹̳��� ���� ���Ѵ�.
		amt =  SUMMON_DECREASESTAMINA_AMT - (pclKI->siSummonRank / 5) ;

		// �Ҹ�Ǵ� ���¹̳��� ���� 0���� �۾� ���� 1�� ������Ų��.
		if(amt <= 0) { amt = 1; }
	}

	StringCchPrintf(buffer, sizeof(buffer), GetTxtFromMgr(1252), pclSummon->clIP.GetLuk() / amt);  
	stTmpListBoxItemData.Set( 1, buffer );
	pList_detailinfo->AddItem( &stTmpListBoxItemData );

	// �ٷ�
	_itot( pclSummon->clIP.GetStr(), buffer, 10 );
	stTmpListBoxItemData.Init();
	stTmpListBoxItemData.Set( 0, pText[6 ] );
	stTmpListBoxItemData.Set( 1, buffer );
	pList_Abilityinfo->AddItem( &stTmpListBoxItemData );

	// ���߷�
	_itot( pclSummon->clIP.GetDex(), buffer, 10 );
	stTmpListBoxItemData.Init();
	stTmpListBoxItemData.Set( 0, pText[ 7] );
	stTmpListBoxItemData.Set( 1, buffer );
	pList_Abilityinfo->AddItem( &stTmpListBoxItemData );

	// ����
	_itot( pclSummon->clIP.GetMag(), buffer, 10 );
	stTmpListBoxItemData.Init();
	stTmpListBoxItemData.Set( 0, pText[8 ] );
	stTmpListBoxItemData.Set( 1, buffer );
	pList_Abilityinfo->AddItem( &stTmpListBoxItemData );

	// �����
	_itot( pclSummon->clIP.GetVit(), buffer, 10 );
	stTmpListBoxItemData.Init();
	stTmpListBoxItemData.Set( 0, pText[ 9 ] );
	stTmpListBoxItemData.Set( 1, buffer );
	pList_Abilityinfo->AddItem( &stTmpListBoxItemData );

	// ���ʽ�
	_itot( pclSummon->clIP.GetBonus(), buffer, 10 );
	stTmpListBoxItemData.Init();
	stTmpListBoxItemData.Set( 0, pText[ 10 ] );
	stTmpListBoxItemData.Set( 1, buffer );
	pList_Abilityinfo->AddItem( &stTmpListBoxItemData );

	// ���뼮
	_itot( pclSummon->siAttackWearStoneNum, buffer, 10 );
	stTmpListBoxItemData.Init();
	stTmpListBoxItemData.Set( 0, pText[ 14 ] );
	stTmpListBoxItemData.Set( 1, buffer );
	pList_Abilityinfo->AddItem( &stTmpListBoxItemData );

	// ���뼮
	_itot( pclSummon->siDefenseWearStoneNum, buffer, 10 );
	stTmpListBoxItemData.Init();
	stTmpListBoxItemData.Set( 0, pText[ 15 ] );
	stTmpListBoxItemData.Set( 1, buffer );
	pList_Abilityinfo->AddItem( &stTmpListBoxItemData );

	// ����
	/*for( SI32 i = 0; i < 2; ++i )
	{
		stTmpListBoxItemData.Init();
		stTmpListBoxItemData.Set( 0, pText[ 11 + i ] );
		if( pclSummon->clScroll.siUnique[i] )
		{
			stTmpListBoxItemData.Set( 0, (TCHAR *)pclClient->pclItemManager->GetName( pclSummon->clScroll.siUnique[i] ) );

			StringCchPrintf( buffer, 256, TEXT("%0.1f%%"), (float)(pclSummon->clScroll.siPercent[i] / 10.0));
			stTmpListBoxItemData.Set( 1, buffer );
		}
		else
		{
			stTmpListBoxItemData.Set( 0, TEXT(""));
			stTmpListBoxItemData.Set( 1, TEXT(""));
		}

		pList_detailinfo->AddItem( &stTmpListBoxItemData );
	}*/

	pList_detailinfo->Refresh();
	pList_Abilityinfo->Refresh();  
}

// ������ ������ �����ش�.
BOOL NSummonMarketUserDlg::ShowFee()
{
	// �忹�� �Ŵ���
	cltSummonMarketManager *pSummonManager = ((cltSummonMarketManager *)m_pStrManager);
	if( pSummonManager == NULL ) return false;

	CStatic *pStatic_feerate = (CStatic*)m_pControlMap[ STATICTEXT_FEERATE ];
	TCHAR buffer[256];
	float feerate = (float)(pSummonManager->clClientStrInfo.clSummonMarketStrInfo.clFee.GetFeeRate() / 10);

	StringCchPrintf(buffer, 256, TEXT("%3.1f%%"), feerate);
    pStatic_feerate->SetText( buffer, DT_LEFT | DT_VCENTER | DT_SINGLELINE );

	return TRUE;
}

// ������ �����ؾ� �� �ݾ��� �����ش�. 
BOOL NSummonMarketUserDlg::ShowRealFee(GMONEY price)
{
	// �忹�� �Ŵ���
	cltSummonMarketManager *pSummonManager = ((cltSummonMarketManager *)m_pStrManager);
	if( pSummonManager == NULL ) return false;

	TCHAR buffer[256];

	StringCchPrintf(buffer, 256, TEXT("%I64d"), pSummonManager->clClientStrInfo.clSummonMarketStrInfo.clFee.CalcFee( price ));
	SetEditText( EDITBOX_REALFEE, buffer );

	return TRUE;
}

void NSummonMarketUserDlg::ShowMySummonList()
{
	// �忹�� �Ŵ���
	cltSummonMarketManager *pSummonManager = ((cltSummonMarketManager *)m_pStrManager);
	if( pSummonManager == NULL ) return;
	// ����Ʈ ���
	CList *pList_mysummon = (CList*)m_pControlMap[ LISTBOX_MYSUMMON ];
	CList *pList_myorder = (CList*)m_pControlMap[ LISTBOX_MYORDER ];
	CList *pList_detailinfo = (CList*)m_pControlMap[ LISTBOX_DETAILINFO ];
	if( pList_mysummon == NULL || pList_mysummon == NULL || pList_mysummon == NULL ) return; 

	pList_mysummon->Clear();

	int index = 0;

	cltSummon*		pclSummon = NULL;
	cltKindInfo*	pclKI	  = NULL;
	for( int i = 0; i < MAX_SUMMON_OWN; i++ )
	{

		pclSummon = &pclCM->CR[ 1 ]->pclCI->clSummonInfo.clSummon[ i ];

		if( pclSummon->siKind != 0 ) 
		{
			//[����] ��ȯ�� ���̺� �и�. => 2008-6-18
			if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
			{
				pclKI = pclClient->pclKindInfoSet->pclSummonKI[ pclSummon->siKind ];
			}
			else
			{
				pclKI = pclClient->pclKindInfoSet->pclKI[ pclSummon->siKind ];
			}

			if(NULL == pclKI)
				continue;
			//��ȯ�� �굵 �ǸŰ����ϰ� ��.
			//if( pclKI->bSummonMall == TRUE ) continue;

			stListBoxItemData tmpListBoxItemData;
			tmpListBoxItemData.Init();
			tmpListBoxItemData.Set( 0, (TCHAR *)pclKI->GetName());
			tmpListBoxItemData.siParam[0] = i;
			tmpListBoxItemData.Set( 1, pclSummon->szName );

			pList_mysummon->AddItem( &tmpListBoxItemData );

			index++;
		}
	}	

	pList_mysummon->Refresh();

	pSummonManager->siMySummonSelectedIndex = -1;
}

void NSummonMarketUserDlg::ShowMyOrderList()
{
	// �忹�� �Ŵ���
	cltSummonMarketManager *pSummonManager = ((cltSummonMarketManager *)m_pStrManager);
	if( pSummonManager == NULL ) 
		return;

	// ����Ʈ ���
	CList *pList_mysummon = (CList*)m_pControlMap[ LISTBOX_MYSUMMON ];
	CList *pList_myorder = (CList*)m_pControlMap[ LISTBOX_MYORDER ];
	CList *pList_detailinfo = (CList*)m_pControlMap[ LISTBOX_DETAILINFO ];
	if( pList_mysummon == NULL || pList_mysummon == NULL || pList_mysummon == NULL ) return; 

	ShowMySummonList( );

	pList_myorder->Clear();

	int index = 0;

	cltKindInfo* pclKI = NULL;
	for( int i = 0; i < MAX_SUMMONMARKET_ORDER_PER_PERSON; i++ )
	{
		if( pSummonManager->clMyOrder[ i ].siPersonID != 0 ) {

			stListBoxItemData tmpListBoxItemData;
			tmpListBoxItemData.Init();
			
			//[����] ��ȯ�� ���̺� �и�. => 2008-6-18
			if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
			{
				pclKI = pclClient->pclKindInfoSet->pclSummonKI[ pSummonManager->clMyOrder[ i ].clSummon.siKind ];
			}
			else
			{
				pclKI = pclClient->pclKindInfoSet->pclKI[ pSummonManager->clMyOrder[ i ].clSummon.siKind ];
			}
			if(NULL == pclKI)
				continue;

			tmpListBoxItemData.Set( 0, (TCHAR *)pclKI->GetName());
			tmpListBoxItemData.siParam[0] = i;
			tmpListBoxItemData.Set( 1, pSummonManager->clMyOrder[ i ].clSummon.szName );

			pList_myorder->AddItem( &tmpListBoxItemData );

			index++;
		}	
	}

	pList_myorder->Refresh();

	pSummonManager->siMyOrderSelectedIndex = -1;
}

void NSummonMarketUserDlg::RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen )
{
	// �忹�� �Ŵ���
	cltSummonMarketManager *pSummonManager = ((cltSummonMarketManager *)m_pStrManager);

	switch( MsgIndex )
	{
	case 0:	// ��ȯ�� �ȱ�
		{
			if ( pData == NULL || DataLen < 1 )
			{
				return;
			}

			if ( RetValue )
			{
				SI32   id    = *((SI32*)pData);
				//SI32 price = *((SI32*)(pData + 4));
				cltGameMsgRequest_SummonMarketSell sendMsg( pSummonManager->siMySummonSelectedIndex, m_Price, TEXT(""), cltGameMsgRequest_SummonMarketSell::TRADE_TYPE_NORMAL );
				cltMsg clMsg( GAMEMSG_REQUEST_SUMMONMARKET_SELL, sizeof( sendMsg ), (BYTE*)&sendMsg );
				pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg );
				
				m_Price = 0;
			}
		}
		break;
	case 1:	// ��ȯ�� ���� �ȱ�
		{
			if ( pData == NULL || DataLen < 1 )
			{
				return;
			}

			if ( RetValue )
			{
				SI32 id    = *((SI32*)pData);
				//SI32 price = *((SI32*)(pData + 4));
				TCHAR personname[128];
				memcpy( personname, ((TCHAR*)(pData + 8)), sizeof( personname ));

				cltGameMsgRequest_SummonMarketSell sendMsg( pSummonManager->siMySummonSelectedIndex, m_Price, personname, cltGameMsgRequest_SummonMarketSell::TRADE_TYPE_SELECTIVE );
				cltMsg clMsg( GAMEMSG_REQUEST_SUMMONMARKET_SELL, sizeof( sendMsg ), (BYTE*)&sendMsg );
				pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg );

				m_Price = 0;
			}
		}
		break;
	}
}

void NSummonMarketUserDlg::DrawDialogLast( SI32 ScreenRX, SI32 ScreenRY )
{
	cltCharClient* pclChar = (cltCharClient*)pclClient->pclCM->CR[1];
	if ( pclChar == NULL )
	{
		return;
	}

	// ���̾�α׳����� ���� ������ġ
	SI32 siRealPortraitStartX	= GetX() + ScreenRX + 28;
	SI32 siRealPortraitStartY	= GetY() + ScreenRY + 51;  

	SI32 i = 0;

	// ���� ������ ��ȯ��. 
	for( SI32 siCount = 0; siCount < MAX_SUMMON_OWN; siCount++ )
	{
		cltSummon*		pclSummon	= pclChar->pclCI->clSummonInfo.GetSummon(siCount);

		if( (pclSummon == NULL) || (pclSummon->siKind <= 0) || (pclSummon->siKind >= MAX_KIND_NUMBER) )
		{
			continue;
		}

		SI32		 siKind	= pclSummon->siKind;
		cltKindInfo* pclKI	= NULL;
		//[����] ��ȯ�� ���̺� �и�. => 2008-6-18
		if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
		{
			pclKI = pclClient->pclKindInfoSet->pclSummonKI[ siKind ];
		}
		else
		{
			pclKI = pclClient->pclKindInfoSet->pclKI[ siKind ];
		}

		if ( pclKI == NULL )
		{
			continue;
		}

		//-----------------------------------------------------------------------------
		//	��ȯ�� �ʻ� [����]
		//-----------------------------------------------------------------------------
		SI32 siSummonPortrait	= pclKI->siSummonPortrait;
		SI32 siPortraitIndex	= 0;

		SI08 siSummonStatus		= pclSummon->siStatus;


		if( siSummonPortrait >= 0 )
		{
			// ��ȯ����/���׹̳ʰ� ���»��´� ��ȯ�� �ʻ��� ����
			siPortraitIndex = (siSummonPortrait * 2);
						
			// ȸ������/�������¶�� ��ȯ�� �ʻ��� ����
			if ( (siSummonStatus == SUMMON_STATUS_DEAD) ||
				 (false == pclKI->bSummonTrade)			||
				 (TRUE == pclClient->pclCM->CR[ 1 ]->pclCI->clSummonInfo.IsHaveEquipItem( siCount )) )
			{  
				siPortraitIndex = (siSummonPortrait * 2) + 1;
			}

			// ���ϰ� ���߱� ������ �׸��� ���� �ùٸ� ��ȣ���� üũ
			if ( (siPortraitIndex < m_sprSummonPortrait.header.iImageNum) && (siPortraitIndex >= 0) )
			{ 
				GP.PutSpr( &m_sprSummonPortrait, ((SUMMONDLG_PORTRAIT_WIDTH+3) * siCount) + siRealPortraitStartX , siRealPortraitStartY, siPortraitIndex);
			}
		}	
	} 

	// �ȱ� ���� ��ȯ�� �ʻ�ȭ.
	cltSummonMarketManager *pSummonManager = ((cltSummonMarketManager *)m_pStrManager);
	if( pSummonManager == NULL ) 
		return;

	cltKindInfo* pclKI	= NULL;

	for( SI32 siCount = 0; siCount < MAX_SUMMON_OWN; siCount++ )
	{
		
		//[����] ��ȯ�� ���̺� �и�. => 2008-6-18
		if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
		{
			pclKI = pclClient->pclKindInfoSet->pclSummonKI[ pSummonManager->clMyOrder[ siCount ].clSummon.siKind ];
		}
		else
		{
			pclKI = pclClient->pclKindInfoSet->pclKI[ pSummonManager->clMyOrder[ siCount ].clSummon.siKind ];
		}

		if ( pclKI == NULL )
		{
			continue;
		}

		//-----------------------------------------------------------------------------
		//	��ȯ�� �ʻ� [����]
		//-----------------------------------------------------------------------------
		SI32 siSummonPortrait	= pclKI->siSummonPortrait;

		if( siSummonPortrait >= 0 )
		{
			// ��ȯ����/���׹̳ʰ� ���»��´� ��ȯ�� �ʻ��� ����
			SI32 siPortraitIndex = (siSummonPortrait * 2);
						
			// ���ϰ� ���߱� ������ �׸��� ���� �ùٸ� ��ȣ���� üũ
			if ( (siPortraitIndex < m_sprSummonPortrait.header.iImageNum) && (siPortraitIndex >= 0) )
			{    
				GP.PutSpr( &m_sprSummonPortrait, ((SUMMONDLG_PORTRAIT_WIDTH+3) * siCount) + siRealPortraitStartX + 171 , siRealPortraitStartY, siPortraitIndex);
			} 
		}	
	} 
}

void NSummonMarketUserDlg::ClickSummonPotrait(SI32 _Index)
{
	CImageStatic* pImageStatic[6];
	pImageStatic[0] = (CImageStatic*)m_pControlMap[ IMAGESTATIC_MYSUMMON_1 ];
	pImageStatic[1] = (CImageStatic*)m_pControlMap[ IMAGESTATIC_MYSUMMON_2 ];
	pImageStatic[2] = (CImageStatic*)m_pControlMap[ IMAGESTATIC_MYSUMMON_3 ];
	pImageStatic[3] = (CImageStatic*)m_pControlMap[ IMAGESTATIC_MYORDER_1 ];
	pImageStatic[4] = (CImageStatic*)m_pControlMap[ IMAGESTATIC_MYORDER_2 ];
	pImageStatic[5] = (CImageStatic*)m_pControlMap[ IMAGESTATIC_MYORDER_3 ];

	pImageStatic[0]->SetFontIndex(1);
	pImageStatic[0]->Refresh();
	pImageStatic[1]->SetFontIndex(1);
	pImageStatic[1]->Refresh();
	pImageStatic[2]->SetFontIndex(1);
	pImageStatic[2]->Refresh();
	pImageStatic[3]->SetFontIndex(1);
	pImageStatic[3]->Refresh();
	pImageStatic[4]->SetFontIndex(1);
	pImageStatic[4]->Refresh();
	pImageStatic[5]->SetFontIndex(1);
	pImageStatic[5]->Refresh();

	pImageStatic[_Index]->SetFontIndex(0);
	pImageStatic[_Index]->Refresh();
}

void NSummonMarketUserDlg::RequestMyOrder(void)
{
	cltMsg clMsg( GAMEMSG_REQUEST_SUMMONMARKET_MYORDER, 0 );
	pclClient->pclCM->CR[1]->SendNetMsg((sPacketHeader*)&clMsg);
}