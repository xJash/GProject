/* ==========================================================================
Ŭ���� :		CNPersonalShopDlg

�ۼ��� :		05/03/31
�ۼ��� :		���뷡

������� :		����

�����۾� :		1. leon todo - Edit Text ���� üũ �ʿ�
2. leon care - -1 ���� �������� Ȯ�� ��


========================================================================*/

#include "./NPersonalShopDlg.h"

#pragma once

#include <tchar.h>

#include "../../../Common/SMLib/LibList/LibList.h"
#include "../../../Common/PrivateTradeOrderMgr/PrivateTradeOrderObj.h"

//#include "../../Interface/PrivateChatDlg/PrivateChatDlgMgr.h"

#include "../../Interface/ErrorMsgDlg/ErrorMsgDlg.h"

#include "Char/CharCommon/Char-Common.h"
#include "Char/CharManager/CharManager.h"

#include "../../CommonLogic/MsgType-Person.h"
#include "../../CommonLogic/Msg/MsgType-Web.h"

#include "../../CommonLogic/Msg/MsgType-Personalshop.h"
#include "../../Client/Client.h"
#include "../../Client/Music/Music.h"

#include "../../../Client/InterfaceMgr/Interface/Button.h"
#include "../../../Client/InterfaceMgr/Interface/Edit.h"
#include "../../../Client/InterfaceMgr/Interface/ImageStatic.h"
#include "../../../Client/InterfaceMgr/Interface/List.h"
#include "../../../Client/InterfaceMgr/Interface/ListView.h"
#include "../../../Client/InterfaceMgr/Interface/ComboBox.h"
#include "../../../Client/InterfaceMgr/Interface/RadioButton.h"
#include "../../../Client/InterfaceMgr/Interface/Static.h"
#include "../../../Client/InterfaceMgr/Interface/OutLine.h"
#include "../../../Client/abusefilter/AbuseFilter.h"

#include "../../InterfaceMgr/InterfaceFile.h"
#include "../../InterfaceMgr/InterfaceMgr.h"
#include "../NSoundOnOffDlg/NSoundOnOffDlg.h"


extern cltCommonLogic* pclClient;

CNPersonalShopDlg::CNPersonalShopDlg()
{
	m_bShow = false;
	m_bTimer= false;

	//m_hUserInventory	= NULL;
	//m_pList_shop_showcase = NULL;

	m_bSelf		 = false;
	m_siShopMode = 0;
	m_bShopStarted = false;

	m_bShopDataChanged = false;
	m_bShopMoneyCheck = FALSE;

	memset(	m_szShopBanner, 0 , sizeof(m_szShopBanner));
	m_clShopData.Init();

	m_pPersonItemInfo	= NULL;
	m_siShopperCharUnique = 0;		// MINI HOMEPAGE�� ���� ���� 
	m_siShopperPersonID	  = 0;
	memset(m_szAccountID, 0, sizeof(m_szAccountID));
	memset(m_szCharName,  0, sizeof(m_szCharName));

	m_siUserInventorySelectedRealItemIndex  = -1;
	m_siUserInventorySelectedIndex			= -1;
	m_siShopShowCaseSelectedRealItemIndex	= -1;
	m_siShopShowCaseSelectedIndex			= -1;

	m_pclInventoryItem = NULL;

	m_pOutLine_test = NULL;

	m_pImageStatic_profile	 = NULL; 
	m_pEdit_explain	 = NULL; 
	m_pButton_minihome	 = NULL; 
	m_pStatic_shopitem	 = NULL; 
	m_pList_shop_showcase	 = NULL; 
	//	m_pEdit_item_explain	 = NULL; 
	m_pStatic_user_item	 = NULL; 
	m_pListView_user_inventory	 = NULL; 
	m_pButton_item_cancel	 = NULL; 
	m_pStatic_shop_setting	 = NULL; 
	m_pRadioButtonButton_sell	 = NULL; 
	m_pRadioButtonButton_buy	 = NULL; 
	m_pRadioButtonButton_makeitem	 = NULL; 
	m_pStatic_handpoint	 = NULL; 
	m_pComboBox_iteminfo_type	 = NULL; 
	m_pEdit_handpoint	 = NULL; 
	m_pEdit_skillpoint	 = NULL; 
	m_pStatic_skillpoint	 = NULL; 
	m_pStatic_item_name	 = NULL; 
	m_pComboBox_iteminfo_name	 = NULL; 
	m_pStatic_price	 = NULL; 
	m_pEdit_price	 = NULL; 
	m_pStatic_count	 = NULL; 
	m_pStatic_amount	 = NULL; 
	m_pEdit_amount	 = NULL; 
	m_pStatic_won	 = NULL; 
	m_pButton_reg_buy_sell	 = NULL; 
	m_pEdit_message	 = NULL; 
	m_pButton_start	 = NULL; 
	m_pButton_stop	 = NULL; 
	m_pButton_close	 = NULL; 
	m_pComboBox_makeitem_name	 = NULL; 
	m_pStatic_money	 = NULL; 
	m_pStatic_item_type	 = NULL; 
	m_pStatic_makeitem_name	 = NULL; 

	m_pButton_item_search = NULL;

	m_pImageStatic_Item = NULL;

	m_pRadioPremium = NULL;
	m_pRadioNormal	= NULL;

	m_pShopTitle_Static = NULL;
	m_pShopTitle_Edit	= NULL;
	m_pCombobox_personshop_kind = NULL;
	m_plistview_ticket  = NULL;
	m_plistview_item	= NULL; 
	m_pimagestatic_premium_back = NULL;


	m_siImageType = -1;
	m_siImageIndex = -1;

	Initialize();
}



CNPersonalShopDlg::~CNPersonalShopDlg()
{
	////---------------------------------
	//// HTML �� �����Ѵ�.
	////---------------------------------
	////==================================
	//hwnd = GetDlgItem(hDlg, IDC_STATIC_SHOP_PROFILE);
	//if(hwnd)
	//{
	//	DoPageAction(hwnd, WEBPAGE_STOP);
	//	UnEmbedBrowserObject(hwnd);
	//}
	////==================================
	SetTimerOnOff( false );

	if( m_pOutLine_test )						delete m_pOutLine_test;

	if( 	m_pImageStatic_profile	 )  		delete 	m_pImageStatic_profile	;
	if( 	m_pEdit_explain	 )  				delete 	m_pEdit_explain	;
	if( 	m_pButton_minihome	 )  			delete 	m_pButton_minihome	;
	if( 	m_pStatic_shopitem	 )  			delete 	m_pStatic_shopitem	;
	if( 	m_pList_shop_showcase	 )  		delete 	m_pList_shop_showcase	;
	//	if( 	m_pEdit_item_explain	 )  	delete 	m_pEdit_item_explain	;
	if( 	m_pStatic_user_item	 )  			delete 	m_pStatic_user_item	;
	if( 	m_pListView_user_inventory	 )  	delete 	m_pListView_user_inventory	;
	if( 	m_pButton_item_cancel	 )  		delete 	m_pButton_item_cancel	;
	if( 	m_pStatic_shop_setting	 )  		delete 	m_pStatic_shop_setting	;
	if( 	m_pRadioButtonButton_sell	 )  	delete 	m_pRadioButtonButton_sell	;
	if( 	m_pRadioButtonButton_buy	 )  	delete 	m_pRadioButtonButton_buy	;
	if( 	m_pRadioButtonButton_makeitem	 )  delete 	m_pRadioButtonButton_makeitem	;
	if( 	m_pStatic_handpoint	 )  			delete 	m_pStatic_handpoint	;
	if( 	m_pComboBox_iteminfo_type	 )  	delete 	m_pComboBox_iteminfo_type	;
	if( 	m_pEdit_handpoint	 )  			delete 	m_pEdit_handpoint	;
	if( 	m_pEdit_skillpoint	 )  			delete 	m_pEdit_skillpoint	;
	if( 	m_pStatic_skillpoint	 )  		delete 	m_pStatic_skillpoint	;
	if( 	m_pStatic_item_name	 )  			delete 	m_pStatic_item_name	;
	if( 	m_pComboBox_iteminfo_name	 )  	delete 	m_pComboBox_iteminfo_name	;
	if( 	m_pStatic_price	 )  				delete 	m_pStatic_price	;
	if( 	m_pEdit_price	 )  				delete 	m_pEdit_price	;
	if( 	m_pStatic_count	 )  				delete 	m_pStatic_count	;
	if( 	m_pStatic_amount	 )  			delete 	m_pStatic_amount	;
	if( 	m_pEdit_amount	 )  				delete 	m_pEdit_amount	;
	if( 	m_pStatic_won	 )  				delete 	m_pStatic_won	;
	if( 	m_pButton_reg_buy_sell	 )  		delete 	m_pButton_reg_buy_sell	;
	if( 	m_pEdit_message	 )  				delete 	m_pEdit_message	;
	if( 	m_pButton_start	 )  				delete 	m_pButton_start	;
	if( 	m_pButton_stop	 )  				delete 	m_pButton_stop	;
	if( 	m_pButton_close	 )  				delete 	m_pButton_close	;
	if( 	m_pComboBox_makeitem_name	 )  	delete 	m_pComboBox_makeitem_name	;
	if( 	m_pStatic_money	 )  				delete 	m_pStatic_money	;
	if( 	m_pStatic_item_type	 )  			delete 	m_pStatic_item_type	;
	if( 	m_pStatic_makeitem_name	 )  		delete 	m_pStatic_makeitem_name	;

	if(		m_pButton_item_search	)			delete m_pButton_item_search;

	if(		m_pImageStatic_Item		)			delete m_pImageStatic_Item;

	if ( m_pclInventoryItem )
	{
		delete [] m_pclInventoryItem;
		m_pclInventoryItem = NULL;
	}	

	SAFE_DELETE(m_pRadioPremium );
	SAFE_DELETE(m_pRadioNormal );
	SAFE_DELETE(m_pShopTitle_Static);
	SAFE_DELETE(m_pShopTitle_Edit);

	SAFE_DELETE( m_pCombobox_personshop_kind );
	SAFE_DELETE( m_plistview_ticket );
	SAFE_DELETE( m_plistview_item	);
	SAFE_DELETE( m_pimagestatic_premium_back	);
	




}

void CNPersonalShopDlg::Initialize()
{
	return;
}

void CNPersonalShopDlg::Destroy()
{

	return;
}

void CNPersonalShopDlg::Create()
{
	if(!IsCreate())
	{
		cltClient *pclclient = (cltClient *)pclClient;
		m_pPersonItemInfo = &pclClient->pclCM->CR[1]->pclCI->clCharItem;

		CInterfaceFile file;
		//[����] �к� �����̾�. => 2008-3-25
		if(pclClient->IsCountrySwitch(Switch_SpecialPersonShop))
		{
			file.LoadFile(TEXT("NInterface/Data/NPersonalShopDlg/DLG_NPersonalShopNew.ddf"));
		}
		else
		{
			file.LoadFile(TEXT("NInterface/Data/NPersonalShopDlg/DLG_NPersonalShop.ddf"));
		}

		file.CreatePopupDialog( this, NPERSONALSHOP_DLG, TEXT("dialog_personalshop"),StaticNPersonalShopDlgProc);

		m_pOutLine_test = new COutLine ( this );

		m_pImageStatic_profile			= new 	CImageStatic	( this )	;
		m_pEdit_explain					= new 	CEdit	( this )	;
		m_pButton_minihome				= new 	CButton	( this )	;
		m_pStatic_shopitem				= new 	CStatic	( this )	;
		m_pList_shop_showcase			= new 	CList	( this )	;
		//		m_pEdit_item_explain	 = new 	CEdit	( this )	;
		m_pStatic_user_item				= new 	CStatic	( this )	;
		m_pListView_user_inventory		= new 	CListView	( this )	;
		m_pButton_item_cancel			= new 	CButton	( this )	;
		m_pStatic_shop_setting			= new 	CStatic	( this )	;
		m_pRadioButtonButton_sell	 	= new 	CRadioButton	( this )	;
		m_pRadioButtonButton_buy	 	= new 	CRadioButton	( this )	;
		m_pRadioButtonButton_makeitem	= new 	CRadioButton	( this )	;
		m_pStatic_handpoint				= new 	CStatic	( this )	;
		m_pComboBox_iteminfo_type		= new 	CComboBox	( this )	;
		m_pEdit_handpoint				= new 	CEdit	( this )	;
		m_pEdit_skillpoint				= new 	CEdit	( this )	;
		m_pStatic_skillpoint			= new 	CStatic	( this )	;
		m_pStatic_item_name				= new 	CStatic	( this )	;
		m_pComboBox_iteminfo_name		= new 	CComboBox	( this )	;
		m_pStatic_price	 				= new 	CStatic	( this )	;
		m_pEdit_price	 				= new 	CEdit	( this )	;
		m_pStatic_count	 				= new 	CStatic	( this )	;
		m_pStatic_amount				= new 	CStatic	( this )	;
		m_pEdit_amount	 				= new 	CEdit	( this )	;
		m_pStatic_won	 				= new 	CStatic	( this )	;
		m_pButton_reg_buy_sell			= new 	CButton	( this )	;
		m_pEdit_message	 				= new 	CEdit	( this )	;
		m_pButton_start	 				= new 	CButton	( this )	;
		m_pButton_stop	 				= new 	CButton	( this )	;
		m_pButton_close	 				= new 	CButton	( this )	;
		m_pComboBox_makeitem_name		= new 	CComboBox	( this )	;
		m_pStatic_money					= new 	CStatic	( this )	;
		m_pStatic_item_type				= new 	CStatic	( this )	;
		m_pStatic_makeitem_name			= new 	CStatic	( this )	;

		m_pImageStatic_Item				= new CImageStatic( this )	;

		m_pButton_item_search			= new CButton( this );

		m_pRadioPremium					= new CRadioButton( this );
		m_pRadioNormal					= new CRadioButton( this );

		m_pShopTitle_Edit				= new CEdit( this );
		m_pShopTitle_Static				= new CStatic( this );
		m_pCombobox_personshop_kind		= new CComboBox( this );
		m_plistview_ticket				= new CListView( this );
		m_plistview_item				= new CListView( this );
		m_pimagestatic_premium_back		= new CStatic( this );


		file.CreateControl( m_pImageStatic_profile,			NPERSONALSHOP_DLG_IMAGESTATIC_PROFILE, TEXT("imagestatic_profile") );
		file.CreateControl( m_pEdit_explain,				NPERSONALSHOP_DLG_EDITBOX_EXPLAIN, TEXT("editbox_explain") );
		file.CreateControl( m_pButton_minihome,				NPERSONALSHOP_DLG_BUTTON_MINIHOME, TEXT("button_minihome") );
		file.CreateControl( m_pStatic_shopitem,				NPERSONALSHOP_DLG_STATICTEXT_SHOPITEM, TEXT("statictext_shopitem") );
		file.CreateControl( m_pList_shop_showcase,			NPERSONALSHOP_DLG_LISTBOX_SHOP_SHOWCASE, TEXT("listbox_shop_showcase") );
		//		file.CreateControl( m_pEdit_item_explain, NPERSONALSHOP_DLG_EDITBOX_ITEM_EXPLAIN, TEXT("editbox_item_explain") );
		file.CreateControl( m_pStatic_user_item,			NPERSONALSHOP_DLG_STATICTEXT_USER_ITEM, TEXT("statictext_user_item") );
		file.CreateControl( m_pListView_user_inventory,		NPERSONALSHOP_DLG_LISTVIEW_USER_INVENTORY, TEXT("listview_user_inventory") );
		file.CreateControl( m_pButton_item_cancel,			NPERSONALSHOP_DLG_BUTTON_ITEM_CANCEL, TEXT("button_item_cancel") );
		file.CreateControl( m_pStatic_shop_setting,			NPERSONALSHOP_DLG_STATICTEXT_SHOP_SETTING, TEXT("statictext_shop_setting") );
		file.CreateControl( m_pRadioButtonButton_sell,		NPERSONALSHOP_DLG_RADIOBUTTON_SELL, TEXT("radiobutton_sell") );
		file.CreateControl( m_pRadioButtonButton_buy,		NPERSONALSHOP_DLG_RADIOBUTTON_BUY, TEXT("radiobutton_buy") );
		file.CreateControl( m_pRadioButtonButton_makeitem,	NPERSONALSHOP_DLG_RADIOBUTTON_MAKEITEM, TEXT("radiobutton_makeitem") );
		file.CreateControl( m_pStatic_handpoint,			NPERSONALSHOP_DLG_STATICTEXT_HANDPOINT, TEXT("statictext_handpoint") );
		file.CreateControl( m_pEdit_handpoint,				NPERSONALSHOP_DLG_EDITBOX_HANDPOINT, TEXT("editbox_handpoint") );
		file.CreateControl( m_pEdit_skillpoint,				NPERSONALSHOP_DLG_EDITBOX_SKILLPOINT, TEXT("editbox_skillpoint") );
		file.CreateControl( m_pStatic_skillpoint,			NPERSONALSHOP_DLG_STATICTEXT_SKILLPOINT, TEXT("statictext_skillpoint") );
		file.CreateControl( m_pStatic_item_name,			NPERSONALSHOP_DLG_STATICTEXT_ITEM_NAME, TEXT("statictext_item_name") );
		file.CreateControl( m_pStatic_price,				NPERSONALSHOP_DLG_STATICTEXT_PRICE, TEXT("statictext_price") );
		file.CreateControl( m_pEdit_price,					NPERSONALSHOP_DLG_EDITBOX_PRICE, TEXT("editbox_price") );
		file.CreateControl( m_pStatic_count,				NPERSONALSHOP_DLG_STATICTEXT_COUNT, TEXT("statictext_count") );
		file.CreateControl( m_pStatic_amount,				NPERSONALSHOP_DLG_STATICTEXT_AMOUNT, TEXT("statictext_amount") );
		file.CreateControl( m_pEdit_amount,					NPERSONALSHOP_DLG_EDITBOX_AMOUNT, TEXT("editbox_amount") );
		file.CreateControl( m_pStatic_won,					NPERSONALSHOP_DLG_STATICTEXT_WON, TEXT("statictext_won") );
		file.CreateControl( m_pButton_reg_buy_sell,			NPERSONALSHOP_DLG_BUTTON_REG_BUY_SELL, TEXT("button_reg_buy_sell") );
		file.CreateControl( m_pEdit_message, 				NPERSONALSHOP_DLG_EDITBOX_MESSAGE, TEXT("editbox_message") );
		file.CreateControl( m_pButton_start, 				NPERSONALSHOP_DLG_BUTTON_START, TEXT("button_start") );
		file.CreateControl( m_pButton_stop,					NPERSONALSHOP_DLG_BUTTON_STOP, TEXT("button_stop") );
		file.CreateControl( m_pButton_close, 				NPERSONALSHOP_DLG_BUTTON_CLOSE, TEXT("button_close") );
		file.CreateControl( m_pStatic_money, 				NPERSONALSHOP_DLG_STATICTEXT_MONEY, TEXT("statictext_money") );
		file.CreateControl( m_pStatic_item_type	, 			NPERSONALSHOP_DLG_STATICTEXT_ITEM_TYPE	, 	TEXT("statictext_item_type")	 )	;
		file.CreateControl( m_pStatic_makeitem_name	, 		NPERSONALSHOP_DLG_STATICTEXT_MAKEITEM_NAME	, 	TEXT("statictext_makeitem_name")	 )	;
		file.CreateControl(	m_pImageStatic_Item	,			NPERSONALSHOP_DLG_IMAGESTATIC_IMAGE	,	TEXT("imagestatic_NONAME1")	 );

		// ���� ���� - ��ǰ �˻� ��ư
		file.CreateControl( m_pButton_item_search,	NPERSONALSHOP_DLG_BUTTON_ITEM_SEARCH, TEXT("button_item_search") );

		file.CreateControl( m_pComboBox_makeitem_name, NPERSONALSHOP_DLG_COMBOBOX_MAKEITEM_NAME, TEXT("combobox_makeitem_name") );
		file.CreateControl( m_pComboBox_iteminfo_name, NPERSONALSHOP_DLG_COMBOBOX_ITEMINFO_NAME, TEXT("combobox_iteminfo_name") );
		file.CreateControl( m_pComboBox_iteminfo_type, NPERSONALSHOP_DLG_COMBOBOX_ITEMINFO_TYPE, TEXT("combobox_iteminfo_type") );

		file.CreateControl( m_pOutLine_test, NPERSONALSHOP_DLG_OUTLINE_TEST, TEXT("outline_test"));

		file.CreateControl( m_pShopTitle_Static,NPERSONALSHOP_DLG_STATIC_SHOPTITLE,TEXT("statictext_ShopTitle"));
		file.CreateControl( m_pShopTitle_Edit,NPERSONALSHOP_DLG_EDIT_SHOPTITLE,TEXT("editbox_ShopTitle"));

		//[����] �к� �����̾�. => 2008-3-25
		if(pclClient->IsCountrySwitch(Switch_SpecialPersonShop))
		{				
			file.CreateControl( m_plistview_ticket,				NPERSONALSHOP_DLG_LISTVIEW_TICKET,  TEXT("listview_ticket"));
			file.CreateControl( m_plistview_item,				NPERSONALSHOP_DLG_LISTVIEW_ITEM,	TEXT("listview_item"));
			file.CreateControl( m_pimagestatic_premium_back,	NPERSONALSHOP_DLG_PREMIUM_BACK,		TEXT("imagestatic_premium_back"));
			
			file.CreateControl( m_pCombobox_personshop_kind, NPERSONALSHOP_DLG_COMBOBOX_PERSONSHOP_KIND_LIST, TEXT("combobox_personshop_kind"));
			stComboBoxItemData stTmpComboBoxItemData;
			stTmpComboBoxItemData.Init();
			stTmpComboBoxItemData.Set( GetTxtFromMgr(6616) );
			m_pCombobox_personshop_kind->AddItem(&stTmpComboBoxItemData);
			stTmpComboBoxItemData.Init();
			stTmpComboBoxItemData.Set( GetTxtFromMgr(6615) );
			m_pCombobox_personshop_kind->AddItem(&stTmpComboBoxItemData);
			stTmpComboBoxItemData.Init();
			stTmpComboBoxItemData.Set( GetTxtFromMgr(8187) );
			m_pCombobox_personshop_kind->AddItem(&stTmpComboBoxItemData);

			m_pCombobox_personshop_kind->SetCursel(0);

			m_pStatic_money->SetTextPrintOption( DT_CENTER );
			m_pStatic_money->Refresh();

		}
		else
		{
			file.CreateControl( m_pRadioPremium, NPERSONALSHOP_DLG_RADIO_PREMIUM, TEXT("radiobutton_premium") );
			file.CreateControl( m_pRadioNormal, NPERSONALSHOP_DLG_RADIO_NORMAL, TEXT("radiobutton_normal") );	
		}
		

		m_pShopTitle_Edit->SetMaxEditTextLength(MAX_SHOP_TITLE_LENGTH);

		m_bShow = false;

		m_pclInventoryItem = new cltItem[ MAX_ITEM_PER_PERSON ];
		memset( m_pclInventoryItem, 0, sizeof( cltItem ) * MAX_ITEM_PER_PERSON );


		//m_hUserInventory = GetDlgItem( hDlg, m_pListView_user_inventory );
		//m_pList_shop_showcase = GetDlgItem( hDlg, IDC_LIST_SHOP_SHOWCASE );

		//pclclient->pclImageList->ConnectToListView( m_hUserInventory, LVSIL_NORMAL );
		//pclclient->pclImageList->ConnectToListView( m_pList_shop_showcase, LVSIL_NORMAL );

		//if(m_hUserInventory)
		//{
		//	ListView_SetExtendedListViewStyle( m_hUserInventory, LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE | LVS_EX_UNDERLINEHOT | LVS_EX_INFOTIP );
		//}

		if(m_pList_shop_showcase )
		{

			m_pList_shop_showcase->SetFontSize(12);
			m_pList_shop_showcase->SetFontWeight(0);
			//ListView_SetExtendedListViewStyle( m_pList_shop_showcase, LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE | LVS_EX_INFOTIP);
			TCHAR* pText = GetTxtFromMgr(1227);
			m_pList_shop_showcase->SetColumn( 0, 135, pText ); //85
			pText = GetTxtFromMgr(1678);
			m_pList_shop_showcase->SetColumn( 1, 100, pText ); //80
			pText = GetTxtFromMgr(1679);
			m_pList_shop_showcase->SetColumn( 2, 60, pText ); //50
			pText = GetTxtFromMgr(2191);
			m_pList_shop_showcase->SetColumn( 3, 90, pText ); //80
			m_pList_shop_showcase->SetColumn( 4, 24, NULL ); //18
			m_pList_shop_showcase->SetBorder( true );
			m_pList_shop_showcase->SetBKColorUse( true );
			m_pList_shop_showcase->SetTextPrintOption(DT_CENTER);
			m_pList_shop_showcase->Refresh();

		}


		// ������ ������ �����ش�. 
		cltItemManagerClient* pclitemmanager = (cltItemManagerClient*)pclClient->pclItemManager;
		/*pclitemmanager*/this->SetItemTypeInCombo( false);

		m_pListView_user_inventory->SetListViewBorderAndBKColorUse( true, true );

		//---------------------------------
		// INIT CONTROLS		   --------
		m_pEdit_handpoint->SetNumberMode( true );
		m_pEdit_handpoint->SetMaxEditTextLength( 5 );
		m_pEdit_skillpoint->SetNumberMode( true );
		m_pEdit_skillpoint->SetMaxEditTextLength( 5 );
		m_pEdit_price->SetNumberMode( true );
		//m_pEdit_price->SetMaxEditTextLength( 11 );
		m_pEdit_amount->SetNumberMode( true );
		m_pEdit_amount->SetMaxEditTextLength( 6 );

		//SendMessage(GetDlgItem( m_hDlg, m_pEdit_explain),EM_LIMITTEXT, MAX_PERSONAL_SHOP_TEXT_SIZE-1, 0);

		//TCHAR Tempbuffer[128];
		//_itot(MAX_ITEM_PILE_NUMBER, Tempbuffer, 10);
		//SendMessage(GetDlgItem( m_hDlg, m_pEdit_amount),EM_LIMITTEXT, _tcslen(Tempbuffer), 0);
		//
		//_itot(MAX_PRICE_IN_MARKET, Tempbuffer, 10);
		//SendMessage(GetDlgItem( m_hDlg, m_pEdit_price),EM_LIMITTEXT, _tcslen(Tempbuffer), 0);

		LoadUserInventory();
		LoadShopShwocase();

		////---------------------------------
		//// HTML �� �ʱ�ȭ�Ѵ�.
		////---------------------------------
		////==================================
		//hwnd = GetDlgItem(hDlg, IDC_STATIC_SHOP_PROFILE);
		//if (hwnd)
		//{
		//	EmbedBrowserObject(hwnd);
		//}
		////===============================
		//MoveWindow( GetDlgItem( hDlg, IDC_STATIC_SHOP_PROFILE ), 1, 4, 73, 73, TRUE );


		m_pRadioButtonButton_makeitem->Show(false);

		//KHY - 0220 -  Ǫġ�ڹ� �ɼ� ����. = ��������
		if(!pclClient->IsCountrySwitch(Switch_Puchikomi)) 
		{
			m_pButton_minihome->Show(false);
		}

		SetTimerOnOff( true );
		m_bTimer = true;
		//Hide();
	}
	else
	{
		DeleteDialog();
	}	
}


void CALLBACK CNPersonalShopDlg::StaticNPersonalShopDlgProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl)
{
	CNPersonalShopDlg *pThis = (CNPersonalShopDlg*) pControllerMgr;
	pThis->NPersonalShopDlgProc( nEvent, nControlID, pControl );
}

void CALLBACK CNPersonalShopDlg::NPersonalShopDlgProc( UINT nEvent, int nControlID, CControllerObj* pControl )
{
	switch( nControlID )
	{
	case COMMON_DIALOG_CLOSEBUTTON:
		{
			DeleteDialog();
		}
		break;
	case NPERSONALSHOP_DLG_EDITBOX_PRICE:
		{
			switch(nEvent) {
				case EVENT_EDITBOX_CHANGE:
					{
						// ���� ���� �ŷ� ���� �ݾ�
						NTCHARString512	kRawPrice( m_pEdit_price->GetText() );
						GMONEY		siPrice = _tstoi64(kRawPrice);
						if( siPrice > pclClient->GetGlobalValue("GV_PersonalShopMoneyLimit"))
							siPrice = pclClient->GetGlobalValue("GV_PersonalShopMoneyLimit");
						m_pEdit_price->SetText( SI64ToString(siPrice) );
						break;
					}
			}
		}

	case NPERSONALSHOP_DLG_BUTTON_CLOSE:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					DeleteDialog();
				}
				break;
			}
		}
		break;

	case NPERSONALSHOP_DLG_LISTVIEW_USER_INVENTORY:
		{
			switch( nEvent )
			{
			case EVENT_LISTVIEW_LBUTTONDOWN:
				{
					m_siUserInventorySelectedRealItemIndex = m_pListView_user_inventory->GetSelectedItemIndex();
					m_siUserInventorySelectedIndex = m_pListView_user_inventory->GetSelectedItemIndex();
					if(m_siUserInventorySelectedRealItemIndex < 0 ) return;
					//m_siUserInventorySelectedIndex = nia->iItem;

					//SI32 siListViewIndex = 0;

					//for ( int i = PERSONITEM_INV0; i < MAX_ITEM_PER_PERSON; ++i )
					//{
					//if ( m_clUserItem[ i ].siUnique != 0 )
					if ( m_clUserItem[ /*PERSONITEM_INV0 +*/ m_siUserInventorySelectedRealItemIndex ].siUnique != 0 )
					{
						//if ( m_siUserInventorySelectedIndex == siListViewIndex )
						//{
						if((m_bSelf == TRUE  && m_siShopMode == PSHOP_MODE_SELL) ||
							(m_bSelf == FALSE && m_siShopMode == PSHOP_MODE_BUY))
						{
							//SetDlgItemInt( hDlg, m_pEdit_amount, m_clUserItem[ i ].GetItemNum(), FALSE );
							TCHAR tmpChar[10];
							StringCchPrintf(tmpChar, 10, TEXT("%d"), m_clUserItem[ /*PERSONITEM_INV0 +*/ m_siUserInventorySelectedRealItemIndex ].GetItemNum());

							m_pEdit_amount->SetText( tmpChar );
							SetItemImageData( m_clUserItem[ m_siUserInventorySelectedRealItemIndex ].siUnique );
						}
						//break;
						//}
						//else
						//{
						//	++siListViewIndex;
						//}
					}
				}
				break;
			}
		}
		break;
	case NPERSONALSHOP_DLG_LISTBOX_SHOP_SHOWCASE:
		{
			switch( nEvent )
			{
			case EVENT_LISTBOX_SELECTION:
				{
					SI16 siTmpRow = -1, siTmpCol = -1;
					m_pList_shop_showcase->GetSelectedIndex( &siTmpRow, &siTmpCol );

					if(siTmpRow < 0 ) return;
					m_siShopShowCaseSelectedRealItemIndex = m_siShopTradeIndex[siTmpRow];
					m_siShopShowCaseSelectedIndex = m_siShopTradeIndex[siTmpRow];

					if (m_siShopShowCaseSelectedIndex == -1) 
						break;
					//m_siShopShowCaseSelectedIndex = nia->iItem;

					//SI32 siListViewIndex = 0;
					//
					//for ( int i = 0; i < MAX_SHOP_ITEM_NUMBER; ++i )
					//{
					if ( m_clShopData.m_clItem[ m_siShopShowCaseSelectedRealItemIndex ].siUnique != 0 )
					{
						//if ( m_siShopShowCaseSelectedIndex == siListViewIndex )
						//{
						if((m_bSelf == FALSE  && m_siShopMode == PSHOP_MODE_SELL) ||
							(m_bSelf == TRUE   && m_siShopMode == PSHOP_MODE_BUY))
						{
							//SetDlgItemInt( hDlg, m_pEdit_amount, m_clShopData.m_clItem[ i ].GetItemNum(), FALSE );
							TCHAR tmpChar[10];
							StringCchPrintf(tmpChar, 10, TEXT("%d"), m_clShopData.m_clItem[ m_siShopShowCaseSelectedRealItemIndex ].GetItemNum());

							m_pEdit_amount->SetText( tmpChar );
						}

						TCHAR ItemExplain[ 512 ] = TEXT("");
						cltItemManagerClient* pclitemmanager = (cltItemManagerClient*)pclClient->pclItemManager;
						if(m_siShopMode == PSHOP_MODE_SELL) // ������ �ȶ��� ��Ȯ�� ������ �����ֳ�.
							pclitemmanager->GetExplain( &m_clShopData.m_clItem[ m_siShopShowCaseSelectedRealItemIndex ], ItemExplain );
						else								// ������ �춧�� �ش� ��ǰ�� ���.
							pclitemmanager->GetExplain( m_clShopData.m_clItem[ m_siShopShowCaseSelectedRealItemIndex ].siUnique, ItemExplain );

						SI32 silen = _tcslen(ItemExplain);
						if( silen > 2 && ItemExplain[silen-1] =='\n') {	ItemExplain[silen-1] = 0;	}
						if( silen > 2 && ItemExplain[silen-2] =='\r') {	ItemExplain[silen-2] = 0;	}

						// Edit �ؽ�Ʈ ���� ����!!
						//								ItemExplain[ MAX_PERSONAL_SHOP_TEXT_SIZE - 1] = '\0';
						//								m_pEdit_item_explain->SetText( ItemExplain );
						DisplayMessage(TRUE,ItemExplain);

						SetItemImageData(m_clShopData.m_clItem[ m_siShopShowCaseSelectedRealItemIndex ].siUnique);

						//	break;
						//}
						//else
						//{
						//	++siListViewIndex;
						//}
					}
					//}
				}
				break;
			}
		}
		break;

	case NPERSONALSHOP_DLG_COMBOBOX_ITEMINFO_TYPE:
		{
			switch ( nEvent )
			{
			case EVENT_COMBOBOX_SELECTION_CHANGED:
				{
					TCHAR szSelText[128];
					szSelText[0] = '\0';
					TCHAR *pTmpChar = NULL;
					SI16 siTmp = -1;
					siTmp = m_pComboBox_iteminfo_type->GetSelectedIndex();
					if( siTmp < 0 ) return;

					pTmpChar = m_pComboBox_iteminfo_type->GetText( siTmp );
					if(pTmpChar == NULL ) return;

					StringCchCopy( szSelText, 128, pTmpChar ); 						

					SI32 itemtypeunique = pclClient->pclItemManager->FindItemTypeUniqueFromTypeName(szSelText);
					if(itemtypeunique >=0)
					{
						// itemtypeunique�� �ش��ϴ� ������ ����Ʈ�� �����ش�. 
						cltItemManagerClient* pclitemmanager = (cltItemManagerClient*)pclClient->pclItemManager;
						/*pclitemmanager->*/this->ShowItemListInCombo(itemtypeunique, true);

					}
				}
				break;
			}
		}
		break;
	case NPERSONALSHOP_DLG_RADIOBUTTON_SELL:
		{
			switch( nEvent )
			{
			case EVENT_RADIOBUTTON_CHANGED:
				{
					if( m_pRadioButtonButton_sell->IsCheck() )
					{
						// �ٸ� ����� �����Ƿڸ� �ޱ����� ListBox �ʱ�ȭ ���� ����
						if(m_siShopMode!=PSHOP_MODE_SELL)
						{
							bool bPremium = m_pRadioPremium->IsCheck();

							m_clShopData.InitData();
							memset(	m_szShopBanner, 0 , sizeof(m_szShopBanner));
							ShopInit(TRUE, PSHOP_MODE_SELL);

							ShowPremiumMode( bPremium );
						}
					}
				}
				break;
			}
		}
		break;
	case NPERSONALSHOP_DLG_RADIOBUTTON_BUY:
		{
			switch( nEvent )
			{
			case EVENT_RADIOBUTTON_CHANGED:
				{
					if( m_pRadioButtonButton_buy->IsCheck() )
					{
						if(m_siShopMode!=PSHOP_MODE_BUY)
						{
							bool bPremium = m_pRadioPremium->IsCheck();

							m_clShopData.InitData();
							memset(	m_szShopBanner, 0 , sizeof(m_szShopBanner));
							ShopInit(TRUE, PSHOP_MODE_BUY);

							ShowPremiumMode( bPremium );
						}
					}
				}
				break;
			}
		}
		break;
	case NPERSONALSHOP_DLG_RADIOBUTTON_MAKEITEM:
		{
			switch( nEvent )
			{
			case EVENT_RADIOBUTTON_CHANGED:
				{
					if( m_pRadioButtonButton_makeitem->IsCheck() )
					{
						if(m_siShopMode!=PSHOP_MODE_MAKEITEM)
						{
							m_clShopData.InitData();
							memset(	m_szShopBanner, 0 , sizeof(m_szShopBanner));
							ShopInit(TRUE, PSHOP_MODE_MAKEITEM);
						}
					}
				}
				break;
			}
		}
		break;
	case NPERSONALSHOP_DLG_BUTTON_ITEM_SEARCH:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					cltClient *pclclient = (cltClient *)pclClient;
					pclclient->CreateInterface( NPERSONALSHOPSEARCH_DLG );
				}
				break;
			}
		}
		break;
	case NPERSONALSHOP_DLG_BUTTON_MINIHOME:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					if ( m_siShopperCharUnique > 0 )
					{
						cltGameMsgRequest_UserPuchikomiURL clUserPuchikomi( m_siShopperCharUnique );
						cltMsg clMsg( GAMEMSG_REQUEST_USERPUCHIKOMIURL , sizeof( clUserPuchikomi ), (BYTE*)&clUserPuchikomi );
						cltClient *pclclient = ( cltClient * )pclClient;
						pclclient->SendMsgToServer( (sPacketHeader*)&clMsg );

						/*
						cltGameMsgRequest_Userid clUserid( m_siShopperCharUnique );
						cltMsg clMsg( GAMEMSG_REQUEST_USERID, sizeof( clUserid ), (BYTE*)&clUserid );
						cltClient *pclclient = ( cltClient * )pclClient;
						pclclient->SendMsgToServer((sPacketHeader*)&clMsg);
						*/
					}
				}
				break;
			}
		}
		break;

	case NPERSONALSHOP_DLG_BUTTON_REG_BUY_SELL:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					Do_Button_reg_buy_sell();
				}
				break;
			}
		}
		break;

	case NPERSONALSHOP_DLG_BUTTON_ITEM_CANCEL:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					// �ڽ��� ������ �������� �ʾ������� ��Ҹ� �Ҽ� �ִ�.
					if(m_bSelf==TRUE && m_bShopStarted==FALSE)
					{
						//[����] �к� �����̾�. => 2008-3-25
						if(pclClient->IsCountrySwitch(Switch_SpecialPersonShop))
						{
							SI32 Index = m_pCombobox_personshop_kind->GetSelectedIndex();
							if(SHOP_TYPE_SPECIAL_PREMIUM == Index)
							{
								m_plistview_item->DeleteAllItems();													
								DropShopItem(1);
								return;
							}
						}
					
						if(DropShopItem(m_siShopShowCaseSelectedIndex)==true)
						{
							m_bShopDataChanged = true;
						}
					}
				}
				break;
			}
		}
		break;
	case NPERSONALSHOP_DLG_BUTTON_START:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{

					// [����] ���� ������ �� �� �ִ� �������� üũ
					SI32 siMapIndex	= pclClient->pclCM->CR[1]->GetMapIndex();

					if ( pclClient->pclMapManager->IsCanMarketOpenMap(siMapIndex) == false )
					{	
						cltClient *pclclient = (cltClient*)pclClient;
											
						if ( (pclclient != NULL) && (pclclient->m_pDialog[NOTIFYMSG_DLG]) )
						{
							TCHAR* pTitle = GetTxtFromMgr(512);
							TCHAR* pText = GetTxtFromMgr(8282);
							pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText );
						}
						return;
					}

					//[����] �к� �����̾�. => 2008-3-25
					if(pclClient->IsCountrySwitch(Switch_SpecialPersonShop))
					{
						SI32 Index = m_pCombobox_personshop_kind->GetSelectedIndex();
						switch(Index)
						{
							case SHOP_TYPE_NORMAL:
							case SHOP_TYPE_PREMIUM:
								{
									StartPersonalShop();
								}
								break;
							case SHOP_TYPE_SPECIAL_PREMIUM:
								{
									StartPersonalSpecialShop();
								}
								break;
						}
					}
					else
					{
						StartPersonalShop();
					}
					
				}
				break;
			}
		}
		break;
	case NPERSONALSHOP_DLG_BUTTON_STOP:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					StopPersonalShop();
				}
				break;
			}
		}
		break;
	//[����] �к� �����̾�. ����Ʈ ���ý�.
	case NPERSONALSHOP_DLG_COMBOBOX_PERSONSHOP_KIND_LIST:
		{
			switch( nEvent )
			{
				case EVENT_COMBOBOX_SELECTION_CHANGED:
					{
						SI32 Index = m_pCombobox_personshop_kind->GetSelectedIndex();
						switch(Index)
						{
							case SHOP_TYPE_NORMAL:
								{
									ShopDataClear();
									NormalShopInitNew();	
								}
								break;
							case SHOP_TYPE_PREMIUM:
								{
									ShopDataClear();
                                    PremiumShopInitNew();	
								}
								break;
							case SHOP_TYPE_SPECIAL_PREMIUM:
								{
									ShopDataClear();
									PremiumShopInitNew();	
									
									SI32 pos = pclClient->pclCM->CR[1]->pclCI->clCharItem.GetItemPos(ITEMUNIQUE(SPECIAL_PREMIUN_TICKET_UNIQUE));
									if(0 > pos)
									{
										m_pCombobox_personshop_kind->SetCursel(SHOP_TYPE_PREMIUM);
										TCHAR* pText = GetTxtFromMgr(8405);
										DisplayMessage(FALSE, pText);
										return;
									}
									// ���� ������ Item�� ������ �����Ѵ�.
									if( AddSpecialShopSellItem( pos ) == true)
									{
										m_bShopDataChanged = true;

										TCHAR buffer[256] = "";
										TCHAR* pText = GetTxtFromMgr(2199);
										StringCchPrintf(buffer, sizeof(buffer), pText, 1);
										m_pStatic_shopitem->SetText(buffer, DT_LEFT | DT_VCENTER );

									}
								}
								break;
						}
						LoadUserInventory();  

					}
					break;
			}
		}
		break;

	case NPERSONALSHOP_DLG_RADIO_PREMIUM:
		{
			switch( nEvent )
			{
			case EVENT_RADIOBUTTON_CHANGED:
				{
					if( m_pRadioPremium->IsCheck() )
					{										
						PremiumShopInit();	
					}
				}
				break;
			}
		}
		break;
	case NPERSONALSHOP_DLG_RADIO_NORMAL:
		{
			switch( nEvent )
			{
			case EVENT_RADIOBUTTON_CHANGED:
				{
					if( m_pRadioNormal->IsCheck() )
					{										
						NormalShopInit();	
					}
				}
				break;
			}
		}
		break;
	}
}

bool CNPersonalShopDlg::IsShow()
{
	return m_bShow;
}

void CNPersonalShopDlg::Show( SI32 siCharUnique, SI32 siPersonID, SI16 ShopMode, TCHAR *Name, TCHAR *AccountID, BOOL bShopStarted )
{

	//if(m_bShow == false)	ShowWindow( m_hDlg, SW_SHOWNOACTIVATE );

	//if ( IsUserInventoryChanged() )
	//{
	//	LoadUserInventory();
	//}

	//if ( IsShopShowCaseChanged() )
	//{
	//	LoadShopShwocase();
	//}

	if(m_bShow == false)	
		CControllerMgr::Show( true );
	m_bShow = true;



	if(m_bTimer == false) 	
	{
		SetActionTimer( PERSONALSHOPDLG_SETTIMER_TIME );
		SetTimerOnOff( true );
	}

	m_bTimer = true;

	if(AccountID && _tcslen(AccountID))	StringCchCopy(m_szAccountID, MAX_PLAYER_NAME, AccountID);
	if(Name&& _tcslen(Name))				StringCchCopy(m_szCharName,  MAX_PLAYER_NAME, Name);

	m_siShopperCharUnique = siCharUnique;
	m_siShopperPersonID   = siPersonID;
	m_bShopStarted		  = bShopStarted;


	/*	HWND hwnd = GetDlgItem(m_hDlg, IDC_STATIC_SHOP_PROFILE);
	if(hwnd)
	{
		TCHAR ProfileURL[MAX_PATH]; // = "" ;
		pclClient->GetCZProfileUrl( ProfileURL, m_szAccountID);
		DisplayHTMLPage(hwnd, ProfileURL);
	}*/

		//---------------------------------
		// ���۰����� ������ ����� �����Ѵ�.
		//---------------------------------
		SetMakeableItemList();

	// �ڱ��ڽ��ϰ�� 
	BOOL bSelf = (siCharUnique == pclClient->pclCM->CR[1]->GetCharUnique());

	ShopInit(bSelf, ShopMode);

	//SetForegroundWindow( m_hDlg );
	return;
}

void CNPersonalShopDlg::ShopInit(BOOL bSelf, SI16 shopmode)
{
	// �����̾� ���� üũ

	//todo : �κ��丮�� �����̾� Ƽ�� üũ?
	NormalShopInit();

	// DialogBox ���� 
	TCHAR buffer[256];
	switch(shopmode)
	{
	case PSHOP_MODE_BUY:	
		{
			TCHAR* pText = GetTxtFromMgr(2192);
			StringCchPrintf(buffer, 256, pText,	  m_szCharName);
		}
		break;	
	case PSHOP_MODE_SELL:
		{
			TCHAR* pText = GetTxtFromMgr(2193);
			StringCchPrintf(buffer, 256, pText,	  m_szCharName);	
		}
		break;
	case PSHOP_MODE_MAKEITEM:	 // ���� �Ƿ�
		{
			TCHAR* pText = GetTxtFromMgr(2194);
			StringCchPrintf(buffer, 256, pText, m_szCharName);	
		}
		break;
	case PSHOP_MODE_MAKEITEM_WANT:	 // ���� �Ƿڸ� �ޱ⸦ ���Ҷ� //Switch_Change_manufacture_request_interface
		{
			TCHAR* pText = GetTxtFromMgr(2194);
			StringCchPrintf(buffer, 256, pText, m_szCharName);	
		}
		break;
	}

	this->SetTitle( buffer );

	switch(shopmode)
	{
	case PSHOP_MODE_BUY:
		{
			TCHAR* pText = GetTxtFromMgr(1678);
			m_pList_shop_showcase->SetColumn( 1, 100, pText );
			m_pList_shop_showcase->Refresh();
			//ListViewSetColumn( m_pList_shop_showcase,  80, pText,		1, 1);
		}
		break;	
	case PSHOP_MODE_SELL:
		{
			TCHAR* pText = GetTxtFromMgr(1678);
			m_pList_shop_showcase->SetColumn( 1, 100, pText );
			m_pList_shop_showcase->Refresh();
			//ListViewSetColumn( m_pList_shop_showcase,  80, pText,		1, 1);
		}
		break;
	case PSHOP_MODE_MAKEITEM:// ���� �Ƿ�
		{
			TCHAR* pText = GetTxtFromMgr(2195);	// ���� ������ 
			m_pList_shop_showcase->SetColumn( 1, 100, pText );
			m_pList_shop_showcase->Refresh();
		}
		break;
	case PSHOP_MODE_MAKEITEM_WANT:// ���� �Ƿڸ� �ޱ⸦ ���Ҷ� //Switch_Change_manufacture_request_interface
		{
			TCHAR* pText = GetTxtFromMgr(2195);	// ���� ������ 
			m_pList_shop_showcase->SetColumn( 1, 100, pText );
			m_pList_shop_showcase->Refresh();
		}
		break;
	}


	m_bSelf		 = bSelf;
	m_siShopMode = shopmode;

	m_clShopData.m_siShopMode = m_siShopMode;

	// ��������� �����.
	cltShopBannerData clShopBanner;
	clShopBanner.SetData(&m_clShopData);
	clShopBanner.MakeBannerText(pclClient->pclItemManager, m_szShopBanner);


	// MESSAGE EDIT�ʱ�ȭ 
	DisplayMessage(TRUE, TEXT(""));
	m_pEdit_handpoint->SetText( TEXT(""));
	m_pEdit_skillpoint->SetText( TEXT(""));

	// �ڱ��ڽ��� ���� ���� 
	if(bSelf == TRUE)
	{
		// �ڽ� ĳ�� �ʻ� ����!
		cltClient *pclclient = (cltClient*)pclClient;
/*		SI16 siTmp = 0;

		for ( int i = 0 ; i < KIND_SYSTEM ; i ++ )
		{
			if ( i != pclclient->pclCM->CR[1]->pclCI->clBI.GetKind() ) continue;
			cltKindInfo *pclKindInfo = pclClient->pclKindInfoSet->pclKI[i];
			if ( pclKindInfo == NULL ) continue ;

			siTmp = i ;
			break ;
		}
*/
		m_pImageStatic_profile->SetFileName(TEXT("Interface/Portrait/portraiticon.spr"));

		switch(pclclient->pclCM->CR[1]->GetKind())
		{
		case KIND_HERO3:	m_pImageStatic_profile->SetFontIndex( 4 ); break;	//KIND_HERO3
		case KIND_HEROINE3:	m_pImageStatic_profile->SetFontIndex( 5 ); break;	//KIND_HEROINE3
		case KIND_HERO4:	m_pImageStatic_profile->SetFontIndex( 6 ); break;	//KIND_HERO4
		case KIND_HEROINE4:	m_pImageStatic_profile->SetFontIndex( 7 ); break;	//KIND_HEROINE4
		}

		switch(shopmode)
		{
		case PSHOP_MODE_BUY:	// ���� ������ ��� ���  	
			{
				m_pList_shop_showcase->Clear();

				m_pEdit_explain->SetText( m_szShopBanner );

				TCHAR* pText = GetTxtFromMgr(2196);
				StringCchPrintf(buffer, 256, pText, MAX_SHOP_ITEM_NUMBER);

				m_pStatic_shopitem->SetText( buffer , DT_LEFT | DT_VCENTER );

				m_pButton_item_cancel->Show( TRUE );
				m_pButton_reg_buy_sell->Show( TRUE );

				// ���� ���� HIDE
				m_pStatic_shop_setting->Show( TRUE );

				m_pRadioButtonButton_buy->Show( TRUE );
				m_pRadioButtonButton_sell->Show( TRUE );
				//m_pRadioButtonButton_makeitem->Show( TRUE );
				// Default Gray
				if(m_pRadioButtonButton_buy->IsCheck() != true )
					m_pRadioButtonButton_buy->SetCheck( TRUE, CONTROLLER_KIND_RADIOBUTTON );

				m_pComboBox_iteminfo_type->Show( TRUE );
				m_pStatic_item_type->Show( TRUE );
				m_pComboBox_iteminfo_name->Show( TRUE );
				m_pStatic_item_name->Show( TRUE );

				// MAKEITEM HIDE
				m_pComboBox_makeitem_name->Show( FALSE);
				m_pStatic_makeitem_name->Show( FALSE);
				m_pStatic_handpoint->Show( FALSE);
				m_pStatic_skillpoint->Show( FALSE);
				m_pEdit_handpoint->Show( FALSE);
				m_pEdit_skillpoint->Show( FALSE);

				m_pComboBox_makeitem_name->Enable(TRUE);
				m_pEdit_handpoint->Enable(TRUE);
				m_pEdit_skillpoint->Enable(TRUE);


				m_pListView_user_inventory->Enable(TRUE);

				m_pStatic_price->Show(TRUE);
				m_pEdit_price->Show(TRUE);
				m_pStatic_money->Show(TRUE);

				//"���Թ�ǰ ���/���"
				pText = GetTxtFromMgr(2197);
				m_pStatic_price->SetText( pText);
				pText = GetTxtFromMgr(2198);
				m_pButton_reg_buy_sell->SetText(pText);

				m_pEdit_amount->SetText(TEXT(""));
				m_pEdit_price->SetText(TEXT(""));

				m_pButton_start->Show(TRUE);
				m_pButton_stop->Show(TRUE);

				// ������ �̹� ������ �Ǿ����� 
				if(m_bShopStarted)
				{
					m_pButton_item_cancel->Enable(FALSE);
					m_pButton_reg_buy_sell->Enable(FALSE);
					m_pButton_start->Enable(FALSE);
					m_pButton_stop->Enable(TRUE);

					m_pEdit_amount->Enable( FALSE);
					m_pEdit_price->Enable(  FALSE);

					m_pRadioButtonButton_buy->Enable(FALSE);
					m_pRadioButtonButton_sell->Enable(FALSE);
					m_pRadioButtonButton_makeitem->Enable(FALSE);

					m_pComboBox_iteminfo_type->Enable(  FALSE);
					m_pComboBox_iteminfo_name->Enable(  FALSE);
					HidePremiumInterface();

				}
				else
				{
					m_pButton_item_cancel->Enable(TRUE);
					m_pButton_reg_buy_sell->Enable(TRUE);
					m_pButton_start->Enable(TRUE);
					m_pButton_stop->Enable(FALSE);

					m_pEdit_amount->Enable( TRUE);
					m_pEdit_price->Enable(  TRUE);

					m_pRadioButtonButton_buy->Enable(TRUE);
					m_pRadioButtonButton_sell->Enable(TRUE);
					//	m_pRadioButtonButton_makeitem->Enable(TRUE);

					m_pComboBox_iteminfo_type->Enable(  TRUE);
					m_pComboBox_iteminfo_name->Enable(  TRUE);
				}

				//=========================================
				// COMBO LIST CLEAR
				//=========================================
				// leon care!!
				m_pComboBox_iteminfo_type->SetCursel(-1);
				m_pComboBox_iteminfo_name->Clear();
			}

			break;
		case PSHOP_MODE_SELL:	// ���� ������ �Ǵ� ��� 
			{
				m_pList_shop_showcase->Clear();

				// Edit �ؽ�Ʈ ���� ����!!
				m_szShopBanner[ MAX_PERSONAL_SHOP_TEXT_SIZE - 1] = '\0';
				m_pEdit_explain->SetText( m_szShopBanner);

				TCHAR* pText = GetTxtFromMgr(2199);
				StringCchPrintf(buffer, 256, pText, MAX_SHOP_ITEM_NUMBER);
				m_pStatic_shopitem->SetText(buffer, DT_LEFT | DT_VCENTER );
				m_pButton_item_cancel->Show(TRUE);
				m_pButton_reg_buy_sell->Show(TRUE);



				// ���� ���� HIDE
				m_pStatic_shop_setting->Show(TRUE);
				m_pRadioButtonButton_buy->Show(TRUE);
				m_pRadioButtonButton_sell ->Show(TRUE);
				//				m_pRadioButtonButton_makeitem->Show(TRUE);

				// Default Gray
				if(m_pRadioButtonButton_sell->IsCheck() != true )
					m_pRadioButtonButton_sell->SetCheck( true, CONTROLLER_KIND_RADIOBUTTON );

				m_pComboBox_iteminfo_type->Show(FALSE);
				m_pStatic_item_type->Show(FALSE);
				m_pComboBox_iteminfo_name->Show(FALSE);
				m_pStatic_item_name->Show(FALSE);

				// MAKEITEM HIDE
				m_pComboBox_makeitem_name->Show(FALSE);
				m_pStatic_makeitem_name->Show(FALSE);
				m_pStatic_handpoint->Show(FALSE);
				m_pStatic_skillpoint->Show(FALSE);
				m_pEdit_handpoint->Show(FALSE);
				m_pEdit_skillpoint->Show(FALSE);

				m_pComboBox_makeitem_name->Enable(TRUE);
				m_pEdit_handpoint->Enable(TRUE);
				m_pEdit_skillpoint->Enable(TRUE);

				m_pListView_user_inventory->Enable(TRUE);

				m_pStatic_price->Show(TRUE);
				m_pEdit_price->Show(TRUE);
				m_pStatic_money->Show(TRUE);

				pText = GetTxtFromMgr(2197);
				m_pStatic_price->SetText( pText, DT_LEFT | DT_TOP | DT_WORDBREAK);
				pText = GetTxtFromMgr(2200);
				m_pButton_reg_buy_sell->SetText(pText);

				m_pEdit_amount->SetText(TEXT(""));
				m_pEdit_price->SetText(TEXT(""));

				m_pButton_start->Show(TRUE);
				m_pButton_stop->Show(TRUE);

				// ������ �̹� ������ �Ǿ����� 
				if(m_bShopStarted)
				{
					m_pButton_item_cancel->Enable(FALSE);
					m_pButton_reg_buy_sell->Enable(FALSE);
					m_pButton_start->Enable(FALSE);
					m_pButton_stop->Enable(TRUE);
					m_pEdit_amount->Enable( FALSE);
					m_pEdit_price->Enable(  FALSE);

					m_pRadioButtonButton_buy->Enable(FALSE);
					m_pRadioButtonButton_sell->Enable(FALSE);
					m_pRadioButtonButton_makeitem->Enable(FALSE);

					HidePremiumInterface();
				}
				else
				{
					m_pButton_item_cancel->Enable(TRUE);
					m_pButton_reg_buy_sell->Enable(TRUE);
					m_pButton_start->Enable(TRUE);
					m_pButton_stop->Enable(FALSE);
					m_pEdit_amount->Enable( TRUE);
					m_pEdit_price->Enable(  TRUE);

					m_pRadioButtonButton_buy->Enable(TRUE);
					m_pRadioButtonButton_sell->Enable(TRUE);
					//m_pRadioButtonButton_makeitem->Enable(TRUE);
				}
			}

			break;

		case PSHOP_MODE_MAKEITEM:	// ���� ������ ������ �Ƿ��Ѵ�.
			{

				m_pList_shop_showcase->Clear();

				// Edit �ؽ�Ʈ ���� ����!!
				m_szShopBanner[ MAX_PERSONAL_SHOP_TEXT_SIZE - 1] = '\0';
				m_pEdit_explain->SetText(m_szShopBanner);

				TCHAR* pText = GetTxtFromMgr(2201);
				StringCchPrintf(buffer, 256, pText, MAX_SHOP_MAKEITEM_NUMBER);
				m_pStatic_shopitem->SetText(buffer, DT_LEFT | DT_VCENTER );

				m_pButton_item_cancel->Show(TRUE);
				m_pButton_reg_buy_sell->Show(TRUE);

				// ���� ���� HIDE
				m_pStatic_shop_setting->Show(TRUE);
				m_pRadioButtonButton_sell ->Show(TRUE);
				m_pRadioButtonButton_buy->Show(TRUE);
				//m_pRadioButtonButton_makeitem->Show(TRUE);

				// Default Gray
				if(m_pRadioButtonButton_makeitem->IsCheck() != true )
					m_pRadioButtonButton_makeitem->SetCheck( true, CONTROLLER_KIND_RADIOBUTTON);

				m_pComboBox_iteminfo_type->Show(FALSE);
				m_pStatic_item_type->Show(FALSE);
				m_pComboBox_iteminfo_name->Show(FALSE);
				m_pStatic_item_name->Show(FALSE);

				// MAKEITEM SHOW
				m_pComboBox_makeitem_name->Show(TRUE);
				m_pStatic_makeitem_name->Show(TRUE);
				m_pStatic_handpoint->Show(TRUE);
				m_pStatic_skillpoint->Show(TRUE);
				m_pEdit_handpoint->Show(TRUE);
				m_pEdit_skillpoint->Show(TRUE);

				m_pComboBox_makeitem_name->Enable(TRUE);
				m_pEdit_handpoint->Enable(TRUE);
				m_pEdit_skillpoint->Enable(TRUE);

				m_pListView_user_inventory->Enable(TRUE);

				m_pStatic_price->Show(TRUE);
				m_pEdit_price->Show(TRUE);
				m_pStatic_money->Show(TRUE);

				//"���Թ�ǰ ���/���"
				pText = GetTxtFromMgr(2202);
				m_pStatic_price->SetText( pText, DT_LEFT | DT_TOP | DT_WORDBREAK);
				pText = GetTxtFromMgr(2203);
				m_pButton_reg_buy_sell->SetText(pText);

				m_pEdit_amount->SetText(TEXT(""));
				m_pEdit_price->SetText(TEXT(""));

				m_pButton_start->Show(TRUE);
				m_pButton_stop->Show(TRUE);

				// ������ �̹� ������ �Ǿ����� 
				if(m_bShopStarted)
				{
					m_pButton_item_cancel->Enable(FALSE);
					m_pButton_reg_buy_sell->Enable(FALSE);
					m_pButton_start->Enable(FALSE);
					m_pButton_stop->Enable(TRUE);

					m_pEdit_amount->Enable( FALSE);
					m_pEdit_price->Enable(  FALSE);

					m_pRadioButtonButton_buy->Enable(FALSE);
					m_pRadioButtonButton_sell->Enable(FALSE);
					m_pRadioButtonButton_makeitem->Enable(FALSE);

					m_pComboBox_iteminfo_type->Enable(FALSE);
					m_pComboBox_iteminfo_name->Enable(FALSE);

					m_pComboBox_makeitem_name->Enable(FALSE);
					m_pEdit_handpoint->Enable(FALSE);
					m_pEdit_skillpoint->Enable(FALSE);

					HidePremiumInterface();

				}
				else
				{
					m_pButton_item_cancel->Enable(TRUE);
					m_pButton_reg_buy_sell->Enable(TRUE);
					m_pButton_start->Enable(TRUE);
					m_pButton_stop->Enable(FALSE);

					m_pEdit_amount->Enable( TRUE);
					m_pEdit_price->Enable(  TRUE);

					m_pRadioButtonButton_buy->Enable(TRUE);
					m_pRadioButtonButton_sell->Enable(TRUE);
					//m_pRadioButtonButton_makeitem->Enable(TRUE);

					m_pComboBox_iteminfo_type->Enable(FALSE);
					m_pComboBox_iteminfo_name->Enable(FALSE);

					m_pComboBox_makeitem_name->Enable(TRUE);
					m_pEdit_handpoint->Enable(TRUE);
					m_pEdit_skillpoint->Enable(TRUE);
				}

				//=========================================
				// COMBO LIST CLEAR
				//=========================================
				m_pComboBox_iteminfo_type->SetCursel( -1 );
				m_pComboBox_iteminfo_name->Clear();
			}

			break;
		case PSHOP_MODE_MAKEITEM_WANT:	// ���� ������ ���� �ޱ⸦ �Ƿ��Ѵ�//Switch_Change_manufacture_request_interface
			{
				m_pList_shop_showcase->Clear();

				// Edit �ؽ�Ʈ ���� ����!!
				m_szShopBanner[ MAX_PERSONAL_SHOP_TEXT_SIZE - 1] = '\0';
				m_pEdit_explain->SetText(m_szShopBanner);

				TCHAR* pText = GetTxtFromMgr(2201);
				StringCchPrintf(buffer, 256, pText, MAX_SHOP_MAKEITEM_NUMBER);
				m_pStatic_shopitem->SetText(buffer, DT_LEFT | DT_VCENTER );

				m_pButton_item_cancel->Show(TRUE);
				m_pButton_reg_buy_sell->Show(TRUE);

				// ���� ���� HIDE
				m_pStatic_shop_setting->Show(TRUE);
				m_pRadioButtonButton_sell ->Show(TRUE);
				m_pRadioButtonButton_buy->Show(TRUE);

				// Default Gray
				if(m_pRadioButtonButton_makeitem->IsCheck() != true )
					m_pRadioButtonButton_makeitem->SetCheck( true, CONTROLLER_KIND_RADIOBUTTON);

				m_pComboBox_iteminfo_type->Show(FALSE);
				m_pStatic_item_type->Show(FALSE);
				m_pComboBox_iteminfo_name->Show(FALSE);
				m_pStatic_item_name->Show(FALSE);

				// MAKEITEM SHOW
				m_pComboBox_makeitem_name->Show(TRUE);
				m_pStatic_makeitem_name->Show(TRUE);
				m_pStatic_handpoint->Show(TRUE);
				m_pStatic_skillpoint->Show(TRUE);
				m_pEdit_handpoint->Show(TRUE);
				m_pEdit_skillpoint->Show(TRUE);

				m_pComboBox_makeitem_name->Enable(TRUE);
				m_pEdit_handpoint->Enable(TRUE);
				m_pEdit_skillpoint->Enable(TRUE);

				m_pListView_user_inventory->Enable(TRUE);

				m_pStatic_price->Show(TRUE);
				m_pEdit_price->Show(TRUE);
				m_pStatic_money->Show(TRUE);

				//"���Թ�ǰ ���/���"
				pText = GetTxtFromMgr(2202);
				m_pStatic_price->SetText( pText, DT_LEFT | DT_TOP | DT_WORDBREAK);
				pText = GetTxtFromMgr(2203);
				m_pButton_reg_buy_sell->SetText(pText);

				m_pEdit_amount->SetText(TEXT(""));
				m_pEdit_price->SetText(TEXT(""));

				m_pButton_start->Show(TRUE);
				m_pButton_stop->Show(TRUE);

				// ������ �̹� ������ �Ǿ����� 
				if(m_bShopStarted)
				{
					m_pButton_item_cancel->Enable(FALSE);
					m_pButton_reg_buy_sell->Enable(FALSE);
					m_pButton_start->Enable(FALSE);
					m_pButton_stop->Enable(TRUE);

					m_pEdit_amount->Enable( FALSE);
					m_pEdit_price->Enable(  FALSE);

					m_pRadioButtonButton_buy->Enable(FALSE);
					m_pRadioButtonButton_sell->Enable(FALSE);
					m_pRadioButtonButton_makeitem->Enable(FALSE);

					m_pComboBox_iteminfo_type->Enable(FALSE);
					m_pComboBox_iteminfo_name->Enable(FALSE);

					m_pComboBox_makeitem_name->Enable(FALSE);
					m_pEdit_handpoint->Enable(FALSE);
					m_pEdit_skillpoint->Enable(FALSE);

					HidePremiumInterface();

				}
				else
				{
					m_pButton_item_cancel->Enable(TRUE);
					m_pButton_reg_buy_sell->Enable(TRUE);
					m_pButton_start->Enable(TRUE);
					m_pButton_stop->Enable(FALSE);

					m_pEdit_amount->Enable( TRUE);
					m_pEdit_price->Enable(  TRUE);

					m_pRadioButtonButton_buy->Enable(TRUE);
					m_pRadioButtonButton_sell->Enable(TRUE);
					//m_pRadioButtonButton_makeitem->Enable(TRUE);

					m_pComboBox_iteminfo_type->Enable(FALSE);
					m_pComboBox_iteminfo_name->Enable(FALSE);

					m_pComboBox_makeitem_name->Enable(TRUE);
					m_pEdit_handpoint->Enable(TRUE);
					m_pEdit_skillpoint->Enable(TRUE);
				}

				//=========================================
				// COMBO LIST CLEAR
				//=========================================
				m_pComboBox_iteminfo_type->SetCursel( -1 );
				m_pComboBox_iteminfo_name->Clear();
			}

			break;
		}
	}
	else
	{

		HidePremiumInterface();

		cltClient *pclclient = (cltClient*)pclClient;

		SI32 id = cltCharCommon::CharUniqueInfo[m_siShopperCharUnique];
		if(id == 0)
		{
			return ;
		}

		cltCharClient* pclchar = (cltCharClient*)pclclient->pclCM->CR[id];
/*		SI16 siTmp = 0;

		for ( int i = 0 ; i < KIND_SYSTEM ; i ++ )
		{
			if ( i == pclchar->GetKind() ) continue;
			cltKindInfo *pclKindInfo = &(pclchar->pclKI[i]);
			if ( pclKindInfo == NULL ) continue ;

			siTmp = pclKindInfo->siSex ;
			break ;
		}
*/
		m_pImageStatic_profile->SetFileName(TEXT("Interface/Portrait/portraiticon.spr"));

		switch(pclchar->GetKind())
		{
		case KIND_HERO3:	m_pImageStatic_profile->SetFontIndex( 4 ); break;	//KIND_HERO3
		case KIND_HEROINE3:	m_pImageStatic_profile->SetFontIndex( 5 ); break;	//KIND_HEROINE3
		case KIND_HERO4:	m_pImageStatic_profile->SetFontIndex( 6 ); break;	//KIND_HERO4
		case KIND_HEROINE4:	m_pImageStatic_profile->SetFontIndex( 7 ); break;	//KIND_HEROINE4
		}

		switch(shopmode)
		{
		case PSHOP_MODE_BUY:
			{
				// Edit �ؽ�Ʈ ���� ����!!
				m_szShopBanner[ MAX_PERSONAL_SHOP_TEXT_SIZE - 1] = '\0';
				m_pEdit_explain->SetText(m_szShopBanner);

				TCHAR* pText = GetTxtFromMgr(2196);
				StringCchPrintf(buffer, 256, pText, MAX_SHOP_ITEM_NUMBER);
				m_pStatic_shopitem->SetText(buffer, DT_LEFT | DT_VCENTER );

				m_pButton_item_cancel->Show(FALSE);
				// ���� ���� HIDE
				m_pStatic_shop_setting->Show(TRUE);
				m_pRadioButtonButton_buy->Show(TRUE);
				m_pRadioButtonButton_sell ->Show(TRUE);
				//				m_pRadioButtonButton_makeitem->Show(TRUE);

				// Default Gray
				if( m_pRadioButtonButton_buy->IsCheck() != true )
					m_pRadioButtonButton_buy->SetCheck( true, CONTROLLER_KIND_RADIOBUTTON );

				// COMBOBOX�� �ڽ��� BUY�� ���ϴ� �����ϋ��� �Ѵ�.
				m_pComboBox_iteminfo_type->Show(FALSE);
				m_pStatic_item_type->Show(FALSE);
				m_pComboBox_iteminfo_name->Show(FALSE);
				m_pStatic_item_name->Show(FALSE);

				// MAKEITEM HIDE
				m_pComboBox_makeitem_name->Show(FALSE);
				m_pStatic_makeitem_name->Show(FALSE);
				m_pStatic_handpoint->Show(FALSE);
				m_pStatic_skillpoint->Show(FALSE);
				m_pEdit_handpoint->Show(FALSE);
				m_pEdit_skillpoint->Show(FALSE);

				m_pComboBox_makeitem_name->Enable(TRUE);
				m_pEdit_handpoint->Enable(TRUE);
				m_pEdit_skillpoint->Enable(TRUE);

				m_pListView_user_inventory->Enable(TRUE);

				m_pStatic_price->Show(FALSE);
				m_pEdit_price->Show(FALSE);
				m_pStatic_money->Show(FALSE);

				pText = GetTxtFromMgr(2197);
				m_pStatic_price->SetText( pText, DT_LEFT | DT_TOP | DT_WORDBREAK);
				pText = GetTxtFromMgr(2205);
				m_pButton_reg_buy_sell->SetText(pText);

				m_pEdit_amount->SetText(TEXT(""));
				m_pEdit_price->SetText(TEXT(""));
				m_pEdit_amount->Enable(TRUE);
				m_pEdit_price->Enable(TRUE);

				m_pButton_reg_buy_sell->Enable(TRUE);
				m_pButton_start->Show(FALSE);
				m_pButton_stop->Show(FALSE);

				m_pRadioButtonButton_buy->Enable(FALSE);
				m_pRadioButtonButton_sell->Enable(FALSE);
				m_pRadioButtonButton_makeitem->Enable(FALSE);

				//=========================================
				// COMBO LIST CLEAR
				//=========================================
				m_pComboBox_iteminfo_type->SetCursel( -1 );
				m_pComboBox_iteminfo_name->Clear();
			}

			break;
		case PSHOP_MODE_SELL:
			{
				// Edit �ؽ�Ʈ ���� ����!!
				m_szShopBanner[ MAX_PERSONAL_SHOP_TEXT_SIZE - 1] = '\0';
				m_pEdit_explain->SetText(m_szShopBanner);

				TCHAR* pText = GetTxtFromMgr(2206);

				StringCchPrintf(buffer, 256, pText, MAX_SHOP_ITEM_NUMBER);
				m_pStatic_shopitem->SetText(buffer, DT_LEFT | DT_VCENTER );

				m_pButton_item_cancel->Show(FALSE);

				// ���� ���� HIDE
				m_pStatic_shop_setting->Show(TRUE);
				m_pRadioButtonButton_sell ->Show(TRUE);
				m_pRadioButtonButton_buy->Show(TRUE);
				//				m_pRadioButtonButton_makeitem->Show(TRUE);

				// Default Gray
				if(m_pRadioButtonButton_sell->IsCheck() != true )
					m_pRadioButtonButton_sell->SetCheck( true, CONTROLLER_KIND_RADIOBUTTON );

				// COMBOBOX�� �ڽ��� BUY�� ���ϴ� �����ϋ��� �Ѵ�.
				m_pComboBox_iteminfo_type->Show(FALSE);
				m_pStatic_item_type->Show(FALSE);
				m_pComboBox_iteminfo_name->Show(FALSE);
				m_pStatic_item_name->Show(FALSE);

				// MAKEITEM HIDE
				m_pComboBox_makeitem_name->Show(FALSE);
				m_pStatic_makeitem_name->Show(FALSE);
				m_pStatic_handpoint->Show(FALSE);
				m_pStatic_skillpoint->Show(FALSE);
				m_pEdit_handpoint->Show(FALSE);
				m_pEdit_skillpoint->Show(FALSE);

				m_pComboBox_iteminfo_name->Enable(TRUE);
				m_pEdit_handpoint->Enable(TRUE);
				m_pEdit_skillpoint->Enable(TRUE);

				m_pListView_user_inventory->Enable(TRUE);

				m_pStatic_price->Show(FALSE);
				m_pEdit_price->Show(FALSE);
				m_pStatic_money->Show(FALSE);

				pText = GetTxtFromMgr(2197);
				m_pStatic_price->SetText( pText, DT_LEFT | DT_TOP | DT_WORDBREAK);
				pText = GetTxtFromMgr(2207);
				m_pButton_reg_buy_sell->SetText(pText);

				m_pEdit_amount->SetText(TEXT(""));
				m_pEdit_price->SetText(TEXT(""));
				m_pEdit_amount->Enable(TRUE);
				m_pEdit_price->Enable(TRUE);

				m_pButton_reg_buy_sell->Enable(TRUE);
				m_pButton_start->Show(FALSE);
				m_pButton_stop->Show(FALSE);

				m_pRadioButtonButton_buy->Enable(FALSE);
				m_pRadioButtonButton_sell->Enable(FALSE);
				m_pRadioButtonButton_makeitem->Enable(FALSE);

			}

			break;

		case PSHOP_MODE_MAKEITEM:
			{
				// Edit �ؽ�Ʈ ���� ����!!
				m_szShopBanner[ MAX_PERSONAL_SHOP_TEXT_SIZE - 1] = '\0';
				m_pEdit_explain->SetText(m_szShopBanner);

				TCHAR* pText = GetTxtFromMgr(2201);
				StringCchPrintf(buffer, 256, pText, MAX_SHOP_MAKEITEM_NUMBER);
				m_pStatic_shopitem->SetText(buffer, DT_LEFT | DT_VCENTER );

				m_pButton_item_cancel->Show(FALSE);

				// ���� ���� HIDE
				m_pStatic_shop_setting->Show(TRUE);
				m_pRadioButtonButton_sell ->Show(TRUE);
				m_pRadioButtonButton_buy->Show(TRUE);
				//				m_pRadioButtonButton_makeitem->Show(TRUE);

				// Default Gray
				// �ٸ� ����� ���
				//cltShopTradeData	tmpShopData; 

				// ����� �ٸ� ��� ���� ������ �� ��
				//if( bSelf == false )
				//{
				//	tmpShopData.Set(&m_clShopData);
				//m_siShopMode = PSHOP_MODE_SELL;
				//}
				m_siShopMode = PSHOP_MODE_SELL;

				if( m_pRadioButtonButton_sell->IsCheck() != true )
					m_pRadioButtonButton_sell->SetCheck( true, CONTROLLER_KIND_RADIOBUTTON );

				//m_clShopData.Set( &tmpShopData );
				m_siShopMode = PSHOP_MODE_MAKEITEM;

				// COMBOBOX�� �ڽ��� BUY�� ���ϴ� �����ϋ��� �Ѵ�.
				m_pComboBox_iteminfo_type->Show(FALSE);
				m_pStatic_item_type->Show(FALSE);
				m_pComboBox_iteminfo_name->Show(FALSE);
				m_pStatic_item_name->Show(FALSE);

				// MAKEITEM HIDE
				m_pComboBox_makeitem_name->Show(FALSE);
				m_pStatic_makeitem_name->Show(FALSE);
				m_pStatic_handpoint->Show(FALSE);
				m_pStatic_skillpoint->Show(FALSE);
				m_pEdit_handpoint->Show(FALSE);
				m_pEdit_skillpoint->Show(FALSE);

				m_pComboBox_makeitem_name->Enable(TRUE);
				m_pEdit_handpoint->Enable(TRUE);
				m_pEdit_skillpoint->Enable(TRUE);

				m_pListView_user_inventory->Enable(TRUE);

				m_pStatic_price->Show(FALSE);
				m_pEdit_price->Show(FALSE);
				m_pStatic_money->Show(FALSE);

				pText = GetTxtFromMgr(2202);
				m_pStatic_price->SetText( pText, DT_LEFT | DT_TOP | DT_WORDBREAK);
				pText = GetTxtFromMgr(2208);
				m_pButton_reg_buy_sell->SetText(pText);

				m_pEdit_amount->SetText(TEXT(""));
				m_pEdit_price->SetText(TEXT(""));
				m_pEdit_amount->Enable(TRUE);
				m_pEdit_price->Enable(TRUE);

				m_pButton_reg_buy_sell->Enable(TRUE);
				m_pButton_start->Show(FALSE);
				m_pButton_stop->Show(FALSE);

				m_pRadioButtonButton_buy->Enable(FALSE);
				m_pRadioButtonButton_sell->Enable(FALSE);
				m_pRadioButtonButton_makeitem->Enable(FALSE);
			}

			break;
		case PSHOP_MODE_MAKEITEM_WANT://Switch_Change_manufacture_request_interface
			{
				// Edit �ؽ�Ʈ ���� ����!!
				m_szShopBanner[ MAX_PERSONAL_SHOP_TEXT_SIZE - 1] = '\0';
				m_pEdit_explain->SetText(m_szShopBanner);

				TCHAR* pText = GetTxtFromMgr(2201);
				StringCchPrintf(buffer, 256, pText, MAX_SHOP_MAKEITEM_NUMBER);
				m_pStatic_shopitem->SetText(buffer, DT_LEFT | DT_VCENTER );

				m_pButton_item_cancel->Show(FALSE);

				// ���� ���� HIDE
				m_pStatic_shop_setting->Show(TRUE);
				m_pRadioButtonButton_sell ->Show(TRUE);
				m_pRadioButtonButton_buy->Show(TRUE);

				m_siShopMode = PSHOP_MODE_SELL;

				if( m_pRadioButtonButton_sell->IsCheck() != true )
					m_pRadioButtonButton_sell->SetCheck( true, CONTROLLER_KIND_RADIOBUTTON );

				//m_clShopData.Set( &tmpShopData );
				m_siShopMode = PSHOP_MODE_MAKEITEM_WANT;

				// COMBOBOX�� �ڽ��� BUY�� ���ϴ� �����ϋ��� �Ѵ�.
				m_pComboBox_iteminfo_type->Show(FALSE);
				m_pStatic_item_type->Show(FALSE);
				m_pComboBox_iteminfo_name->Show(FALSE);
				m_pStatic_item_name->Show(FALSE);

				// MAKEITEM HIDE
				m_pComboBox_makeitem_name->Show(FALSE);
				m_pStatic_makeitem_name->Show(FALSE);
				m_pStatic_handpoint->Show(FALSE);
				m_pStatic_skillpoint->Show(FALSE);
				m_pEdit_handpoint->Show(FALSE);
				m_pEdit_skillpoint->Show(FALSE);

				m_pComboBox_makeitem_name->Enable(TRUE);
				m_pEdit_handpoint->Enable(TRUE);
				m_pEdit_skillpoint->Enable(TRUE);

				m_pListView_user_inventory->Enable(TRUE);

				m_pStatic_price->Show(FALSE);
				m_pEdit_price->Show(FALSE);
				m_pStatic_money->Show(FALSE);

				pText = GetTxtFromMgr(2202);
				m_pStatic_price->SetText( pText, DT_LEFT | DT_TOP | DT_WORDBREAK);
				pText = GetTxtFromMgr(2208);
				m_pButton_reg_buy_sell->SetText(pText);

				m_pEdit_amount->SetText(TEXT(""));
				m_pEdit_price->SetText(TEXT(""));
				m_pEdit_amount->Enable(TRUE);
				m_pEdit_price->Enable(TRUE);

				m_pButton_reg_buy_sell->Enable(TRUE);
				m_pButton_start->Show(FALSE);
				m_pButton_stop->Show(FALSE);

				m_pRadioButtonButton_buy->Enable(FALSE);
				m_pRadioButtonButton_sell->Enable(FALSE);
				m_pRadioButtonButton_makeitem->Enable(FALSE);
			}

			break;
		}
	}
}

void CNPersonalShopDlg::Hide()
{
	if(m_bShow==true)	CControllerMgr::Show( false );
	m_bShow = false;

	SetTimerOnOff( false );
}



bool CNPersonalShopDlg::IsUserInventoryChanged()
{
	for ( int j = PERSONITEM_INV0; j < MAX_ITEM_PER_PERSON; ++j )
	{
		SI32 size = sizeof(cltItem);

		BYTE* src = (BYTE*)&m_clUserItem[ j ];
		BYTE* dst = (BYTE*)&m_pPersonItemInfo->clItem[ j ];

		for( int i = 0; i < size; ++i )
		{
			if( src[i] != dst[i] )
			{
				return true;
			}
		}
	}

	return false;
}


bool CNPersonalShopDlg::IsShopShowCaseChanged()
{
	if(m_bShopDataChanged) return true;

	return false;
}

void CNPersonalShopDlg::LoadUserInventory()
{	
	m_siUserInventorySelectedIndex = -1;


	for ( int i = PERSONITEM_INV0; i < MAX_ITEM_PER_PERSON; ++i )
	{
		m_clUserItem[ i ] = m_pPersonItemInfo->clItem[ i ];
	}

	//[����] �к� �����̾�. => 2008-3-25
	if(pclClient->IsCountrySwitch(Switch_SpecialPersonShop))
	{
		SI32 Index = m_pCombobox_personshop_kind->GetSelectedIndex();
		if(0 > Index)
			return;
		if(SHOP_TYPE_SPECIAL_PREMIUM == Index)
		{							
			SetNInventoryInListViewSpecialPremium();
		}
		else
		{
			SetNInventoryInListView();
		}
	}
	else
	{
		SetNInventoryInListView( /*pclClient->pclItemManager, m_hDlg, m_pListView_user_inventory, NULL, m_pPersonItemInfo*/ );
	}

	

	// ListView ToolTip
	//case LVN_GETINFOTIP:
	//	{
	//		if ( ngt->iItem >= 0 )
	//		{
	//			SI32 siListViewIndex = 0;
	//			
	//			for ( int i = PERSONITEM_INV0; i < MAX_ITEM_PER_PERSON; ++i )
	//			{
	//				if ( m_clUserItem[ i ].siUnique != 0 )
	//				{
	//					if ( ngt->iItem == siListViewIndex )
	//					{
	//						pclClient->pclItemManager->GetExplain( &m_clUserItem[ i ], ngt->pszText );
	//						break;
	//					}
	//					else
	//					{
	//						++siListViewIndex;
	//					}
	//				}
	//			}							
	//		}
	//	}
	//	break;
	//}

	// ListBox ToolTip
	//	case LVN_GETINFOTIP:
	//		{
	//			if ( ngt->iItem >= 0 )
	//			{
	//				SI32 siListViewIndex = 0;
	//				
	//				for ( int i = 0; i < MAX_SHOP_ITEM_NUMBER; ++i )
	//				{
	//					if ( m_clShopData.m_clItem[ i ].siUnique != 0 )
	//					{
	//						if ( ngt->iItem == siListViewIndex )
	//						{
	//							cltItemManagerClient* pclitemmanager = (cltItemManagerClient*)pclClient->pclItemManager;
	//
	//							if(m_siShopMode == PSHOP_MODE_SELL) // ������ �ȶ��� ��Ȯ�� ������ �����ֳ�.
	//								pclitemmanager->GetExplain( &m_clShopData.m_clItem[ i ],          ngt->pszText );
	//							else								// ������ �춧�� �ش� ��ǰ�� ���.
	//								pclitemmanager->GetExplain( m_clShopData.m_clItem[ i ].siUnique,  ngt->pszText );
	//							
	//							break;
	//						}
	//						else
	//						{
	//							++siListViewIndex;
	//						}
	//					}
	//				}							
	//			}
	//		}
	//		break;
	//	}

	return;
}

void CNPersonalShopDlg::SetNInventoryInListView()
{
	if(NULL == m_pclInventoryItem)
		return;

	SI16 StartPos = 0;

	// ����â�� ������ ������ �о�ͼ� �V���� �ش�.
	SI16 i = 0, j = 0;

	SI32 id = 1;

	SI32 GlobalImageIndex = -1;
	SI32 GlobalImageFont = -1;


	// ���, ��, ���� �κ�
	m_pListView_user_inventory->DeleteAllItems();

	//for( j = 0; j < INVMODE_ALL - 1; j++)
	{
		StartPos = PERSONITEM_INV0 + ( j * MAX_ITEM_PER_INVENTORY );
		m_pListView_user_inventory->SetStartItemPos( StartPos );

		for ( i = 0; i < MAX_ITEM_PER_PERSON; ++i )
		{
			m_pclInventoryItem[ i ].Set( &pclClient->pclCM->CR[id]->pclCI->clCharItem.clItem[ i ] );

			if ( m_pclInventoryItem[ i ].siUnique > 0 )
			{
				bool bCanSell = true;

				if ( m_pclInventoryItem[ i ].IsBelonging(pclClient->pclItemManager) )		bCanSell = false;
				if ( m_pclInventoryItem[ i ].clItemCommon.clCommonInfo.uiGetItemReason == cltItemCommonInfo::REASON_GIVE_PARTYHALL_ITEM )
					bCanSell = false;					

				if ( bCanSell )
				{
					TCHAR *ItemName = (TCHAR*)pclClient->pclItemManager->GetName( m_pclInventoryItem[ i ].siUnique );

					if ( ItemName )
					{
						TCHAR ToolTipMsg[ MAX_TOOLTIP_MSG_SIZE ] = TEXT("");
						pclClient->pclItemManager->GetExplain( &m_pclInventoryItem[ i ], ToolTipMsg );

						if ( i >= StartPos && i < MAX_ITEM_PER_PERSON ) // 2 : 0(���), 1(��), 2(����) ��� ����
						{
							pclClient->pclItemManager->GetItemGImageFileIndexAndFont( m_pclInventoryItem[ i ].siUnique, &GlobalImageIndex, &GlobalImageFont);

							stListViewItemData ListViewItemData;
							ListViewItemData.Set( GlobalImageIndex, GlobalImageFont, i - StartPos, m_pclInventoryItem[ i ].siItemNum, ItemName, ToolTipMsg );
							m_pListView_user_inventory->InsertItem( &ListViewItemData );
						}
					}
				}
			}
		}
	}
}

bool CNPersonalShopDlg::IsItemType(cltItem* _pItem)
{
	SI32 ItemType = _pItem->GetType(pclClient->pclItemManager);
	switch( ItemType )
	{
		case	ITEMTYPE_SWORD:			
		case	ITEMTYPE_SPEAR:			
		case	ITEMTYPE_AXE:			
		case	ITEMTYPE_BOW:			
		case	ITEMTYPE_GUN:			
		case	ITEMTYPE_STAFF:			
		case	ITEMTYPE_HELMET:			
		case	ITEMTYPE_ARMOUR:			
		case	ITEMTYPE_BELT:
		case	ITEMTYPE_MANTLE:

		// �ƹ�Ÿ ������ ���λ��� �Ǹ� ����
		case	ITEMTYPE_AVATAR_MANTLE:
		case	ITEMTYPE_AVATAR_NECK:
		case	ITEMTYPE_AVATAR_RING:
		case	ITEMTYPE_AVATAR_DRESS:
		case	ITEMTYPE_AVATAR_HAT:

		case	ITEMTYPE_SHOES:			return true;
	}

	return false;
}

void CNPersonalShopDlg::SetNInventoryInListViewSpecialPremium()
{
	if(NULL == m_pclInventoryItem)
		return;

	SI16 StartPos = 0;

	// ����â�� ������ ������ �о�ͼ� �V���� �ش�.
	SI16 i = 0, j = 0;

	SI32 id = 1;

	SI32 GlobalImageIndex = -1;
	SI32 GlobalImageFont = -1;


	// ���, ��, ���� �κ�
	m_pListView_user_inventory->DeleteAllItems();

	StartPos = PERSONITEM_INV0 + ( j * MAX_ITEM_PER_INVENTORY );
	m_pListView_user_inventory->SetStartItemPos( StartPos );

	for ( i = 0; i < MAX_ITEM_PER_PERSON; ++i )
	{
		m_pclInventoryItem[ i ].Set( &pclClient->pclCM->CR[id]->pclCI->clCharItem.clItem[ i ] );

		if ( m_pclInventoryItem[ i ].siUnique > 0 )
		{
			if( false == IsItemType(&m_pclInventoryItem[ i ]) )
				continue; 

			//[����] �޸� ���� �ý��� - �޸� ��� ������ �̶�� ��� ���� �ʾƾ� �Ѵ�.
			if( NULL != pclClient->pclDormancySystem)
			{
				CDormancyEquipItemRewardClient *pclDormancyClient = (CDormancyEquipItemRewardClient *)pclClient->pclDormancySystem->GetDormancyEquipItemReward();

				if( NULL != pclDormancyClient)
				{
					if( TRUE == pclDormancyClient->IsDormancyEquipItem(m_pclInventoryItem[ i ].siUnique))
						continue;
				}
			}

			//�к��� Ǯ���ְ� �к� ���� Ƽ���̶��.... ���
			if (   m_pclInventoryItem[ i ].siUnique > 0 && m_pclInventoryItem[ i ].IsBelonging(pclClient->pclItemManager) == true
				|| SPECIAL_PREMIUN_TICKET_UNIQUE == m_pclInventoryItem[ i ].siUnique )
			{
				TCHAR *ItemName = (TCHAR*)pclClient->pclItemManager->GetName( m_pclInventoryItem[ i ].siUnique );

				if ( ItemName )
				{
					TCHAR ToolTipMsg[ MAX_TOOLTIP_MSG_SIZE ] = TEXT("");
					pclClient->pclItemManager->GetExplain( &m_pclInventoryItem[ i ], ToolTipMsg );

					if ( i >= StartPos && i < MAX_ITEM_PER_PERSON ) // 2 : 0(���), 1(��), 2(����) ��� ����
					{
						pclClient->pclItemManager->GetItemGImageFileIndexAndFont( m_pclInventoryItem[ i ].siUnique, &GlobalImageIndex, &GlobalImageFont);

						stListViewItemData ListViewItemData;
						ListViewItemData.Set( GlobalImageIndex, GlobalImageFont, i - StartPos, m_pclInventoryItem[ i ].siItemNum, ItemName, ToolTipMsg );
						m_pListView_user_inventory->InsertItem( &ListViewItemData );
					}
				}
			}
		}
	}
}

void CNPersonalShopDlg::SetSpecialPremiumListview(SI32 _Index, cltItem* _pclItem)
{
	CListView* pListView = NULL;
	if( 0 == _Index )
	{
		pListView = m_plistview_ticket;
	}
	else if( 1 == _Index )
	{
		pListView = m_plistview_item;
	}

	if(NULL == pListView)
		return;

	SI32 GlobalImageIndex = -1;
	SI32 GlobalImageFont = -1;
	SI32 StartPos=0;
	SI32 id = 1;
	TCHAR ItemName[128] = "";
	if( _pclItem->siUnique > 0)
	{
		if( _pclItem->GetFullName( pclClient->pclItemManager, ItemName, 128 ) == true )
		{
			if ( pclClient->pclItemManager->GetItemGImageFileIndexAndFont( _pclItem->siUnique, &GlobalImageIndex, &GlobalImageFont ) )
			{
				TCHAR ToolTipMsg[ MAX_TOOLTIP_MSG_SIZE ] = TEXT("");
				pclClient->pclItemManager->GetExplain( _pclItem, ToolTipMsg );

				stListViewItemData ListViewItemData;
				ListViewItemData.Set( GlobalImageIndex, GlobalImageFont, 0 - StartPos , _pclItem->GetItemNum(), ItemName, ToolTipMsg, false );														
				pListView->InsertItem( &ListViewItemData );
			}
		}
	}
}

void CNPersonalShopDlg::LoadShopShwocase()
{
	stListBoxItemData tmpListBoxItemData;
	m_siShopShowCaseSelectedIndex = -1;

	int i = 0, listIndex = 0;

	m_bShopDataChanged = false;

	TCHAR itemname[128];
	TCHAR itembuffer[128];
	m_pList_shop_showcase->Clear();

	for ( i = 0; i < MAX_SHOP_ITEM_NUMBER; ++i )
	{	
		m_siShopTradeIndex[i] = -1;
	}

	for ( i = 0; i < MAX_SHOP_ITEM_NUMBER; ++i )
	{	
		/*cyj
		if (m_clShopData.m_clItem[i].siItemNum == 0)
		{
			// ��������� �����.
			cltShopBannerData clShopBanner;
			clShopBanner.SetData(&m_clShopData);
			clShopBanner.MakeBannerText(pclClient->pclItemManager, m_szShopBanner);

			m_pEdit_explain->SetText( m_szShopBanner );
			strcpy(m_szShopBanner, ((cltClient*)pclClient)->pclCM->CR[1]->szPersonalShopText);
		}
		*/

			//cyj ���� ������ ���� 0 �̻��϶��� ���̵��� ����
			if(m_clShopData.m_clItem[i].siUnique && m_clShopData.m_clItem[i].siItemNum > 0)
			{
				if(m_clShopData.m_clItem[ i ].GetFullName(pclClient->pclItemManager, itemname, 128) == true)
				{
					//ListViewInsertItem(, -1 , i, 0, itemname,   i);
					tmpListBoxItemData.Init();
					tmpListBoxItemData.siParam[0] = i;
					tmpListBoxItemData.Set( 0, itemname );

					TCHAR* pText = GetTxtFromMgr(611);
					g_JYLibFunction.SetNumUnit(m_clShopData.m_siPrice[i], itembuffer, 128, pText);

					//ListViewInsertItem(m_pList_shop_showcase, -1 , i, 1, itembuffer, -1);
					tmpListBoxItemData.siParam[0] = -1;
					tmpListBoxItemData.Set( 1, itembuffer, ((cltClient*)pclClient)->GetColorByPrice(m_clShopData.m_siPrice[i]) );

					pText = GetTxtFromMgr(2209);
					StringCchPrintf(itembuffer, 128, pText, m_clShopData.m_clItem[ i ].siItemNum);
					tmpListBoxItemData.siParam[0] = -1;
					tmpListBoxItemData.Set( 2, itembuffer );

					//ListViewInsertItem(m_pList_shop_showcase, -1 , i, 2, itembuffer, -1);


					if(m_clShopData.m_siCurrentPrice[i])
					{

						TCHAR		szPrice[64] = { '\0', };
						GMONEY		siPrice = m_clShopData.m_siCurrentPrice[i] ;
						g_JYLibFunction.SetNumUnit(siPrice, szPrice, sizeof(szPrice));
						NTCHARString512	kText(GetTxtFromMgr(1640));
						kText.Replace("#money#",szPrice);
						//m_pEdit_condition_fee->SetText( kText );
						tmpListBoxItemData.siParam[0] = -1;
						tmpListBoxItemData.Set( 3, kText );

						//pText = GetTxtFromMgr(1640);
						////g_JYLibFunction.SetNumUnit(m_clShopData.m_siCurrentPrice[i], itembuffer,"��");
						//StringCchPrintf(itembuffer, 128, pText,m_clShopData.m_siCurrentPrice[i]);
						//tmpListBoxItemData.siParam[0] = -1;
						//tmpListBoxItemData.Set( 3, itembuffer );
						////ListViewInsertItem(m_pList_shop_showcase, -1 , i, 3, itembuffer, -1);
					}

					m_pList_shop_showcase->AddItem( &tmpListBoxItemData );

					if(pclClient->IsCountrySwitch(Switch_SpecialPersonShop))
					{
						//[����] �к� �����̾�. ����Ʈ�信 �ִ´�. ������ ������ 2���� ����.
						if( 2 > listIndex)
						{
							SetSpecialPremiumListview( listIndex, &m_clShopData.m_clItem[i] );
						}
					}

					m_siShopTradeIndex[listIndex] = i;
					listIndex++;
				}
			}
	}
	m_pList_shop_showcase->Refresh();

	//	m_pEdit_item_explain->SetText(TEXT("") );	
	return;
}


void CNPersonalShopDlg::Do_Button_reg_buy_sell()
{
	if(m_bSelf)
	{
		switch(m_siShopMode)
		{
		case PSHOP_MODE_BUY:	// ���� ������ �ڵ��� �� �� �ֵ��� ���� 
			{
				if(AddShopBuyItem() == true)
				{
					m_bShopDataChanged = true;
				}
			}
			break;
		case PSHOP_MODE_SELL:	// ���� ������ �ڵ����� �� �� �ֵ��� ���� 
			{

				//[����] �к� �����̾�. => 2008-3-25
				if(pclClient->IsCountrySwitch(Switch_SpecialPersonShop))
				{
					SI32 Index = m_pCombobox_personshop_kind->GetSelectedIndex();
					if(SHOP_TYPE_SPECIAL_PREMIUM == Index)
					{							
						// ���� ������ Item�� ������ �����Ѵ�.
						if(AddSpecialShopSellItem(m_siUserInventorySelectedRealItemIndex)==true)
						{
							m_bShopDataChanged = true;
						}
					}
					// ���� ������ Item�� ������ �����Ѵ�. 
					else if(AddShopSellItem(m_siUserInventorySelectedRealItemIndex)==true)
					{
						m_bShopDataChanged = true;
					}
				}
				// ���� ������ Item�� ������ �����Ѵ�. 
				else if(AddShopSellItem(m_siUserInventorySelectedRealItemIndex)==true)
				{
					m_bShopDataChanged = true;
				}
			}
			break;
		case PSHOP_MODE_MAKEITEM:
			{
				if(AddShopMakeItem() == true)
				{
					m_bShopDataChanged = true;
				}
			}
			break;
		case PSHOP_MODE_MAKEITEM_WANT:	//Switch_Change_manufacture_request_interface
			{
				if(AddShopMakeItem() == true)
				{
					m_bShopDataChanged = true;
				}
			}
			break;
		}
	}
	else
	{
		switch(m_siShopMode)
		{
		case PSHOP_MODE_BUY:	// ���� ������ϴ°��� ������ ���� �Ǵ�.
			{
				// showcase�� �ִ� ��ǰ�� ���� ���� ������ŭ �� ������ �Ǵ�.
				SellShopItem(m_siUserInventorySelectedRealItemIndex);
			}
			break;
		case PSHOP_MODE_SELL:	// ���� ���� �Ȱ� �ִ� ������ ���.
			{
				BuyShopItem();
			}
			break;
		case PSHOP_MODE_MAKEITEM:
			{
				MakeShopItem();
			}
			break;
		case PSHOP_MODE_MAKEITEM_WANT://Switch_Change_manufacture_request_interface
			{
				MakeShopItem();
			}
			break;
		}
	}


}

bool CNPersonalShopDlg::AddShopBuyItem()
{
	TCHAR szSelText[128];
	TCHAR *pTmpChar = NULL, *pTmpChar2 = NULL;
	SI16 siTmpIndex = -1;
	// ��ǰ ��Ͽ��� ������ ������ ���������� ������ showcase�� �����Ѵ�. 
	szSelText[0] = '\0';

	siTmpIndex = m_pComboBox_iteminfo_name->GetSelectedIndex();

	if(siTmpIndex < 0 ) return false;

	pTmpChar = m_pComboBox_iteminfo_name->GetText( siTmpIndex );

	//if(GetWindowText(GetDlgItem(m_hDlg, m_pComboBox_iteminfo_name), szSelText, 100))
	if(pTmpChar != NULL )
	{
		_tcscpy( szSelText, pTmpChar );

		SI32 itemunique = pclClient->pclItemManager->FindUniqueFromName(szSelText);
		if(itemunique)
		{
			//----------------------------------------
			// �������� ��Ÿ ������ ǥ���Ѵ� 
			//----------------------------------------
			SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique(itemunique);
			if(ref > 0)
			{
				//DisplayMessage(TRUE,(TCHAR*) pclClient->pclItemManager->pclItemInfo[ref]->GetName());
				SI32 i = 0;
				SI32 siAmountSuccess= 0, siPriceSuccess = 0;
				TCHAR AmountBuffer[256]=TEXT(""), PriceBuffer[256]=TEXT("");
				pTmpChar = NULL;
				pTmpChar2 = NULL;
				pTmpChar = m_pEdit_amount->GetText();
				pTmpChar2 = m_pEdit_price->GetText();

				if(pTmpChar == NULL || pTmpChar2 == NULL)
				{
					TCHAR* pText = GetTxtFromMgr(2210);
					DisplayMessage(FALSE, pText);
					return false;
				}

				_tcscpy( AmountBuffer, pTmpChar );
				_tcscpy( PriceBuffer, pTmpChar2 );

				siAmountSuccess = _tcslen( AmountBuffer );
				siPriceSuccess = _tcslen( PriceBuffer );

				if(siAmountSuccess <= 0 || siPriceSuccess <= 0 )
				{
					TCHAR* pText = GetTxtFromMgr(2210);
					DisplayMessage(FALSE, pText);
					return false;
				}

				SI64 siAmountValue = 0, siPriceValue = 0;

				// AMOUNT
				siAmountValue = _tstoi64(AmountBuffer);
				if(siAmountValue <=0 )
				{
					TCHAR* pText = GetTxtFromMgr(1688);
					DisplayMessage(FALSE, pText);
					return false;
				}
				if(siAmountValue > MAX_ITEM_PILE_NUMBER)
				{
					TCHAR buffer[256];
					TCHAR* pText = GetTxtFromMgr(2211);
					StringCchPrintf(buffer, 256, pText, MAX_ITEM_PILE_NUMBER);
					DisplayMessage(FALSE, buffer);
					return false;
				}

				// PRICE 
				siPriceValue  = _tstoi64(PriceBuffer);
				if(siPriceValue <= 0)
				{
					TCHAR* pText = GetTxtFromMgr(2212);
					DisplayMessage(FALSE, pText);
					return false;
				}
				if(siPriceValue > MAX_PRICE_IN_MARKET)
				{
					TCHAR buffer[256];
					TCHAR* pText = GetTxtFromMgr(2213);
					StringCchPrintf(buffer, 256, pText, MAX_PRICE_IN_MARKET);
					DisplayMessage(FALSE, buffer);
					return false;
				}

				// ���� �������� ������ �߰��Ҽ� ����.
				for ( i = 0; i < MAX_SHOP_ITEM_NUMBER; ++i )
				{	
					if(m_clShopData.m_clItem[i].siUnique == itemunique)
					{
						TCHAR* pText = GetTxtFromMgr(2214);
						DisplayMessage(FALSE, pText);
						return false;
					}
				}

				for ( i = 0; i < MAX_SHOP_ITEM_NUMBER; ++i )
				{	
					if(m_clShopData.m_clItem[i].siUnique == 0)
					{
						m_clShopData.m_clItem[i].siUnique		= itemunique;
						m_clShopData.m_clItem[i].siItemNum		= (SI32)siAmountValue;
						m_clShopData.m_siPrice[i]				= siPriceValue;
						m_clShopData.m_siSelectedInventoryPos[i]= 0;

						TCHAR itemname[128];
						if(m_clShopData.m_clItem[ i ].GetFullName(pclClient->pclItemManager, itemname, 128) == true)			
						{
							TCHAR buffer[512];
							TCHAR* pText = GetTxtFromMgr(2215);
							TCHAR num[128]= TEXT(" ") ;
							TCHAR money[128]= TEXT(" ") ;
							StringCchPrintf(num, 128, TEXT("%d"),(SI32)siAmountValue);
							
							TCHAR		szPrice[64] = { '\0', };
							GMONEY		siPrice = siPriceValue ;
							g_JYLibFunction.SetNumUnit(siPrice, szPrice, sizeof(szPrice));
							
							Nsprintf(buffer,pText,TEXT("item"), itemname   ,TEXT("num"),  num  ,TEXT("money"), szPrice   ,NULL);

							//sprintf(buffer, pText,
							//				itemname, (SI32)siAmountValue, (SI32)siPriceValue);
							DisplayMessage(TRUE, buffer);


							// EDIT�� ��������� ǥ���Ѵ�.
							cltShopBannerData clShopBanner;
							clShopBanner.SetData(&m_clShopData);
							clShopBanner.MakeBannerText(pclClient->pclItemManager, m_szShopBanner);
							// Edit �ؽ�Ʈ ���� ����!!
							m_szShopBanner[ MAX_PERSONAL_SHOP_TEXT_SIZE - 1] = '\0';
							m_pEdit_explain->SetText(m_szShopBanner);
						}

						return true;
					}
				}
				TCHAR* pText = GetTxtFromMgr(2216);
				DisplayMessage(FALSE, pText);
				return false;
			}
		}
	}

	DisplayMessage(FALSE, TEXT(""));
	return false;
}

bool CNPersonalShopDlg::AddShopSellItem(SI32 siUserInventoryRealIndex)
{
	if(siUserInventoryRealIndex < PERSONITEM_INV0 ||  siUserInventoryRealIndex >= MAX_ITEM_PER_PERSON)
		return false;

	SI32 i = 0;
	SI32 siAmountSuccess= 0, siPriceSuccess = 0;
	TCHAR AmountBuffer[256]=TEXT(""), PriceBuffer[256]=TEXT("");
	TCHAR *pTmpChar = NULL, *pTmpChar2 = NULL;

	pTmpChar = NULL;
	pTmpChar2 = NULL;
	pTmpChar = m_pEdit_amount->GetText();
	pTmpChar2 = m_pEdit_price->GetText();

	if(pTmpChar == NULL || pTmpChar2 == NULL)
	{
		return false;
	}

	_tcscpy( AmountBuffer, pTmpChar );
	_tcscpy( PriceBuffer, pTmpChar2 );

	siAmountSuccess = _tcslen( AmountBuffer );
	siPriceSuccess = _tcslen( PriceBuffer );

	//siAmountSuccess = GetDlgItemText( m_hDlg, m_pEdit_amount, AmountBuffer,  128 );
	//siPriceSuccess  = GetDlgItemText( m_hDlg, m_pEdit_price,  PriceBuffer,  128 );

	if(siAmountSuccess <= 0 || siAmountSuccess <= 0 ) return false;
	SI64 siAmountValue = 0, siPriceValue = 0;

	// AMOUNT
	siAmountValue = _tstoi64(AmountBuffer);
	if( siAmountValue <=0 )
	{
		TCHAR* pText = GetTxtFromMgr(1668);
		DisplayMessage(FALSE, pText);
		return false;
	}
	if( siAmountValue > m_clUserItem[siUserInventoryRealIndex].siItemNum  )
	{
		TCHAR* pText = GetTxtFromMgr(2217);
		DisplayMessage(FALSE, pText);
		return false;
	}
	if( siAmountValue > MAX_ITEM_PILE_NUMBER)
	{
		TCHAR buffer[256];
		TCHAR* pText = GetTxtFromMgr(2211);
		StringCchPrintf(buffer, 256, pText, MAX_ITEM_PILE_NUMBER);
		DisplayMessage(FALSE, buffer);
		return false;
	}

	// PRICE 
	siPriceValue  = _tstoi64(PriceBuffer);
	if(siPriceValue <= 0)
	{
		TCHAR* pText = GetTxtFromMgr(2212);
		DisplayMessage(FALSE, pText);
		return false;
	}
	if(siPriceValue > MAX_PRICE_IN_MARKET)
	{
		TCHAR buffer[256];
		TCHAR* pText = GetTxtFromMgr(2213);
		StringCchPrintf(buffer, 256, pText, 
			MAX_PRICE_IN_MARKET);
		DisplayMessage(FALSE, buffer);
		return false;
	}


	// ���� �������� ������ �߰��Ҽ� ����.
	for ( i = 0; i < MAX_SHOP_ITEM_NUMBER; ++i )
	{	
		if(m_clShopData.m_siSelectedInventoryPos[i] == siUserInventoryRealIndex)
		{
			TCHAR* pText = GetTxtFromMgr(2214);
			DisplayMessage(FALSE, pText);
			return false;
		}
	}

	for ( i = 0; i < MAX_SHOP_ITEM_NUMBER; ++i )
	{	
		if( m_clShopData.m_clItem[ i ].siUnique == 0 )
		{
			m_clShopData.m_clItem[ i ].Set(&m_clUserItem[siUserInventoryRealIndex]);

			// �缳�� 
			m_clShopData.m_clItem[ i ].siItemNum		= (SI32)siAmountValue;
			m_clShopData.m_siPrice[ i ]					= siPriceValue;
			m_clShopData.m_siSelectedInventoryPos[ i ]	= siUserInventoryRealIndex;

			TCHAR itemname[128];
			if(m_clShopData.m_clItem[ i ].GetFullName(pclClient->pclItemManager, itemname, 128) == true)			
			{
				TCHAR buffer[512];
				TCHAR* pText = GetTxtFromMgr(2218);
				TCHAR num[128]= TEXT(" ") ;
				TCHAR money[128]= TEXT(" ") ;
				StringCchPrintf(num, 128, TEXT("%d"),(SI32)siAmountValue);
				TCHAR		szPrice[64] = { '\0', };
				GMONEY		siPrice = siPriceValue ;
				g_JYLibFunction.SetNumUnit(siPrice, szPrice, sizeof(szPrice));

				Nsprintf(buffer,pText,TEXT("item"), itemname   ,TEXT("num"),  num  ,TEXT("money"), szPrice   ,NULL);

				//sprintf(buffer, pText, itemname, (SI32)siAmountValue, (SI32)siPriceValue);

				// EDIT�� ��������� ǥ���Ѵ�.
				cltShopBannerData clShopBanner;
				clShopBanner.SetData(&m_clShopData);
				clShopBanner.MakeBannerText(pclClient->pclItemManager, m_szShopBanner);
				// Edit �ؽ�Ʈ ���� ����!!
				m_szShopBanner[ MAX_PERSONAL_SHOP_TEXT_SIZE - 1] = '\0';
				m_pEdit_explain->SetText(m_szShopBanner);

				DisplayMessage(TRUE, buffer);  


			}

			return true;
		}
	}

	TCHAR* pText = GetTxtFromMgr(2216);
	DisplayMessage(FALSE, pText);
	return false;
}
void CNPersonalShopDlg::ShopDataClear()
{
	m_plistview_ticket->DeleteAllItems();
	m_plistview_item->DeleteAllItems(); 
	

	m_pList_shop_showcase->Clear();
	m_pList_shop_showcase->Refresh();
#ifdef _SAFE_MEMORY
	m_clShopData.m_clItem.ZeroMem();
	m_clShopData.m_siSelectedInventoryPos.ZeroMem();
#else
	ZeroMemory(m_clShopData.m_clItem,				  sizeof(m_clShopData.m_clItem));	
	ZeroMemory(m_clShopData.m_siSelectedInventoryPos, sizeof(m_clShopData.m_siSelectedInventoryPos));	
#endif
	
}

bool CNPersonalShopDlg::AddSpecialShopSellItem(SI32 siUserInventoryRealIndex)
{
	if(siUserInventoryRealIndex < PERSONITEM_INV0 ||  siUserInventoryRealIndex >= MAX_ITEM_PER_PERSON)
		return false;

	// Ƽ�Ͼ������ΰ�..
	bool ItemKindTicket = false;
	//0��  ������ �˻�.
	if(0 < m_clShopData.m_clItem[0].siUnique )
	{
		// ���� �к� �������� ����־�� �Ѵ�.
		if(SPECIAL_PREMIUN_TICKET_UNIQUE != m_clShopData.m_clItem[0].siUnique )
		{
			TCHAR* pText = "���� ��ϵ� �������� �к� �����̾� Ƽ���� �ƴմϴ�.";GetTxtFromMgr(2212);
			DisplayMessage(FALSE, pText);
			return false;
		}
	}
	else
	{
		if(0 >= m_clShopData.m_clItem[0].siUnique )
		{
			if( SPECIAL_PREMIUN_TICKET_UNIQUE != m_clUserItem[siUserInventoryRealIndex].siUnique )
			{
				TCHAR* pText = "�к� �����̾� Ƽ���� ���� ����ϼž� 1���� ������ ����� �����մϴ�.";GetTxtFromMgr(2212);
				DisplayMessage(FALSE, pText);
				return false;
			}
			else
			{
				// ����ϴ°� Ƽ�� �������̴�. 
				ItemKindTicket = true;
			}
		}
	}
	

	// �̹� �ι��� �������� ��� ������ ���̻� �߰� ����.
	if( 0 < m_clShopData.m_clItem[1].siUnique )
	{
		TCHAR* pText = GetTxtFromMgr(8186);
		DisplayMessage(FALSE, pText);
		return false;
	}

	SI32 i = 0;
	SI32 siAmountSuccess= 0, siPriceSuccess = 0;
	TCHAR AmountBuffer[256]=TEXT(""), PriceBuffer[256]=TEXT("");
	TCHAR *pTmpChar = NULL, *pTmpChar2 = NULL;

	pTmpChar = NULL;
	pTmpChar2 = NULL;
	pTmpChar = m_pEdit_amount->GetText();
	pTmpChar2 = m_pEdit_price->GetText();

	if(pTmpChar == NULL || pTmpChar2 == NULL)
	{
		return false;
	}

	_tcscpy( AmountBuffer, pTmpChar );
	_tcscpy( PriceBuffer, pTmpChar2 );

	siAmountSuccess = _tcslen( AmountBuffer );
	siPriceSuccess = _tcslen( PriceBuffer );

	//siAmountSuccess = GetDlgItemText( m_hDlg, m_pEdit_amount, AmountBuffer,  128 );
	//siPriceSuccess  = GetDlgItemText( m_hDlg, m_pEdit_price,  PriceBuffer,  128 );
	
	SI64 siAmountValue = 0, siPriceValue = 0;
	if(false == ItemKindTicket)    
	{
        if(siAmountSuccess <= 0 || siAmountSuccess <= 0 ) 
			return false;  
		
		siAmountValue = 0, siPriceValue = 0;

		// AMOUNT
		siAmountValue = _tstoi64(AmountBuffer);
		if( siAmountValue <=0 )
		{
			TCHAR* pText = GetTxtFromMgr(1668);
			DisplayMessage(FALSE, pText);
			return false;
		}
		if( siAmountValue > m_clUserItem[siUserInventoryRealIndex].siItemNum  )
		{
			TCHAR* pText = GetTxtFromMgr(2217);
			DisplayMessage(FALSE, pText);
			return false;
		}
		if( siAmountValue > MAX_ITEM_PILE_NUMBER)
		{
			TCHAR buffer[256];
			TCHAR* pText = GetTxtFromMgr(2211);
			StringCchPrintf(buffer, 256, pText, MAX_ITEM_PILE_NUMBER);
			DisplayMessage(FALSE, buffer);
			return false;
		}

		// PRICE 
		siPriceValue  = _tstoi64(PriceBuffer);
		if(siPriceValue <= 0)
		{
			TCHAR* pText = GetTxtFromMgr(2212);
			DisplayMessage(FALSE, pText);
			return false;
		}
		if(siPriceValue > MAX_PRICE_IN_MARKET)
		{
			TCHAR buffer[256];
			TCHAR* pText = GetTxtFromMgr(2213);
			StringCchPrintf(buffer, 256, pText, 
				MAX_PRICE_IN_MARKET);
			DisplayMessage(FALSE, buffer);
			return false;
		}
	}
	else
	{
		siAmountValue = 0;
		siPriceValue  = 0;
	}
	
	// ���� �������� ������ �ϳ��� �ŷ�.
	siAmountValue = 1;

	// ���� �������� ������ �߰��Ҽ� ����.
	for ( i = 0; i < MAX_SHOP_ITEM_NUMBER; ++i )
	{	
		if(m_clShopData.m_siSelectedInventoryPos[i] == siUserInventoryRealIndex)
		{
			TCHAR* pText = GetTxtFromMgr(2214);
			DisplayMessage(FALSE, pText);
			return false;
		}
	}

	for ( i = 0; i < MAX_SHOP_ITEM_NUMBER; ++i )
	{	
		if( m_clShopData.m_clItem[ i ].siUnique == 0 )
		{
			m_clShopData.m_clItem[ i ].Set(&m_clUserItem[siUserInventoryRealIndex]);

			// �缳�� 
			m_clShopData.m_clItem[ i ].siItemNum		= (SI32)siAmountValue;
			m_clShopData.m_siPrice[ i ]					= siPriceValue;
			m_clShopData.m_siSelectedInventoryPos[ i ]	= siUserInventoryRealIndex;

			TCHAR itemname[128];
			if(m_clShopData.m_clItem[ i ].GetFullName(pclClient->pclItemManager, itemname, 128) == true)			
			{
				TCHAR buffer[512];
				TCHAR* pText = GetTxtFromMgr(2218);
				TCHAR num[128]= TEXT(" ") ;
				TCHAR money[128]= TEXT(" ") ;
				StringCchPrintf(num, 128, TEXT("%d"),(SI32)siAmountValue);
				StringCchPrintf(money, 128, TEXT("%I64d"),siPriceValue);
				Nsprintf(buffer,pText,TEXT("item"), itemname   ,TEXT("num"),  num  ,TEXT("money"), money   ,NULL);

				//sprintf(buffer, pText, itemname, (SI32)siAmountValue, (SI32)siPriceValue);

				// EDIT�� ��������� ǥ���Ѵ�.
				cltShopBannerData clShopBanner;
				clShopBanner.SetData(&m_clShopData);
				clShopBanner.MakeBannerText(pclClient->pclItemManager, m_szShopBanner);
				// Edit �ؽ�Ʈ ���� ����!!
				m_szShopBanner[ MAX_PERSONAL_SHOP_TEXT_SIZE - 1] = '\0';
				m_pEdit_explain->SetText(m_szShopBanner);

				DisplayMessage(TRUE, buffer);  


			}

			return true;
		}
	}

	TCHAR* pText = GetTxtFromMgr(2216);
	DisplayMessage(FALSE, pText);
	return false;
}


bool CNPersonalShopDlg::AddShopMakeItem()
{
	TCHAR szSelText[128];
	TCHAR *pTmpChar = NULL;
	TCHAR Nbuffer[512]=TEXT(" ");

	SI16 siTmpIndex = -1;
	szSelText[0] = '\0';

	siTmpIndex = m_pComboBox_makeitem_name->GetSelectedIndex();

	if(siTmpIndex < 0 ) return false;

	pTmpChar = m_pComboBox_makeitem_name->GetText( siTmpIndex );

	// ���۸�Ͽ��� ������ ������ ���������� ������ showcase�� �����Ѵ�. 
	//if(GetWindowText(GetDlgItem(m_hDlg, m_pComboBox_iteminfo_name), szSelText, 100))
	if(pTmpChar != NULL )
	{

		_tcscpy( szSelText, pTmpChar );

		TCHAR *pTemp1 = _tcsstr(szSelText, TEXT("-"));	
		TCHAR* pText = GetTxtFromMgr(2219);
		TCHAR *pTemp2 = _tcsstr(szSelText, pText);	
		if(pTemp1 == NULL || pTemp2 == NULL) return false;

		*pTemp1 = '\0';	pTemp1++;
		*pTemp2 = '\0';

		SI64 siMaxMakeItem = _tstoi64(pTemp1);
		if(siMaxMakeItem <= 0)				{ return false;   }

		SI32 itemunique = pclClient->pclItemManager->FindUniqueFromName(szSelText);
		if(itemunique)
		{
			//----------------------------------------
			// �������� ��Ÿ ������ ǥ���Ѵ� 
			//----------------------------------------
			SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique(itemunique);
			if(ref > 0)
			{
				SI32 i = 0;
				SI32 siAmountSuccess= 0, siPriceSuccess = 0;
				SI32 siHandSuccess= 0,   siSkillSuccess = 0;
				TCHAR AmountBuffer[256]=TEXT(""), PriceBuffer[256]=TEXT("");
				TCHAR HandBuffer[256]=TEXT(""),   SkillBuffer[256]=TEXT("");
				TCHAR *pTmpChar1, *pTmpChar2, *pTmpChar3, *pTmpChar4;
				pTmpChar1 = pTmpChar2 = pTmpChar3 = pTmpChar4 = NULL;

				pTmpChar1 = m_pEdit_amount->GetText();
				pTmpChar2 = m_pEdit_price->GetText();
				pTmpChar3 = m_pEdit_handpoint->GetText();
				pTmpChar4 = m_pEdit_skillpoint->GetText();

				if( pTmpChar1 == NULL || pTmpChar2 == NULL || pTmpChar3 == NULL || pTmpChar1 == NULL )
				{
					TCHAR* pText = GetTxtFromMgr(2220);
					DisplayMessage(FALSE, pText);
					return false;
				}

				_tcscpy( AmountBuffer, pTmpChar1 );
				_tcscpy( PriceBuffer, pTmpChar2 );
				_tcscpy( HandBuffer, pTmpChar3 );
				_tcscpy( SkillBuffer, pTmpChar4 );

				siAmountSuccess =  _tcslen( AmountBuffer );
				siPriceSuccess = _tcslen( PriceBuffer );
				siHandSuccess = _tcslen( HandBuffer );
				siSkillSuccess = _tcslen( SkillBuffer );

				//siAmountSuccess = GetDlgItemText( m_hDlg, m_pEdit_amount, AmountBuffer, 128 );
				//siPriceSuccess  = GetDlgItemText( m_hDlg, m_pEdit_price,  PriceBuffer,  128 );
				//siHandSuccess   = GetDlgItemText( m_hDlg, m_pEdit_handpoint,		HandBuffer,   128 );
				//siSkillSuccess  = GetDlgItemText( m_hDlg, m_pEdit_skillpoint,		SkillBuffer,  128 );


				if(siAmountSuccess <= 0 || siPriceSuccess <= 0 || siHandSuccess<=0 || siSkillSuccess <=0)
				{
					TCHAR* pText = GetTxtFromMgr(2220);
					DisplayMessage(FALSE, pText);
					return false;
				}

				SI64 siAmountValue = 0, siPriceValue = 0;
				SI64 siHandValue = 0,   siSkillValue = 0;

				// AMOUNT
				siAmountValue = _tstoi64(AmountBuffer);
				if(siAmountValue <=0 )
				{
					TCHAR* pText = GetTxtFromMgr(1668);
					DisplayMessage(FALSE, pText);
					return false;
				}
				if(siAmountValue > siMaxMakeItem )
				{
					TCHAR buffer[256];
					TCHAR* pText = GetTxtFromMgr(2221);
					StringCchPrintf(buffer, 256, pText, siMaxMakeItem);
					DisplayMessage(FALSE, buffer);
					return false;
				}
				if(siAmountValue > MAX_ITEM_PILE_NUMBER)
				{
					TCHAR buffer[256];
					TCHAR* pText = GetTxtFromMgr(2211);
					StringCchPrintf(buffer, 256, pText, MAX_ITEM_PILE_NUMBER);
					DisplayMessage(FALSE, buffer);
					return false;
				}

				// PRICE 
				siPriceValue  = _tstoi64(PriceBuffer);
				if(siPriceValue < 0)
				{
					TCHAR* pText = GetTxtFromMgr(2222);
					DisplayMessage(FALSE, pText);
					return false;
				}
				if(siPriceValue > MAX_PRICE_IN_MARKET)
				{
					TCHAR buffer[256];
					TCHAR* pText = GetTxtFromMgr(2223);
					StringCchPrintf(buffer, 256, pText, 
						MAX_PRICE_IN_MARKET);
					DisplayMessage(FALSE, buffer);
					return false;
				}

				// ������ 
				siHandValue  = _tstoi64(HandBuffer);
				if(siHandValue < 0)
				{
					TCHAR* pText = GetTxtFromMgr(2224);
					DisplayMessage(FALSE, pText);
					return false;
				}
				if(siHandValue > 2000)
				{
					TCHAR buffer[256];
					TCHAR* pText = GetTxtFromMgr(2225);
					StringCchPrintf(buffer, 256, pText, 
						2000);
					DisplayMessage(FALSE, buffer);
					return false;
				}

				// ��ų���� 
				siSkillValue  = _tstoi64(SkillBuffer);
				if(siSkillValue < 0)
				{
					TCHAR* pText = GetTxtFromMgr(2226);
					DisplayMessage(FALSE, pText);
					return false;
				}
				if(siSkillValue > MAX_SKILL_LEVEL+30)
				{
					TCHAR buffer[256];
					TCHAR* pText = GetTxtFromMgr(2227);
					StringCchPrintf(buffer, 256, pText, 
						MAX_SKILL_LEVEL+30);
					DisplayMessage(FALSE, buffer);
					return false;
				}


				// ���� �������� ������ �߰��Ҽ� ����.
				for ( i = 0; i < MAX_SHOP_ITEM_NUMBER; ++i )
				{	
					if(m_clShopData.m_clItem[i].siUnique == itemunique)
					{
						TCHAR* pText = GetTxtFromMgr(2214);
						DisplayMessage(FALSE, pText);
						return false;
					}
				}

				// 1���� �����Ҽ��ֵ��� �Ѵ�.
				for ( i = 0; i < MAX_SHOP_MAKEITEM_NUMBER; ++i )
				{	
					if(m_clShopData.m_clItem[i].siUnique == 0)
					{
						m_clShopData.m_clItem[i].siUnique		= itemunique;
						m_clShopData.m_clItem[i].siItemNum		= (SI32)siAmountValue;
						m_clShopData.m_siPrice[i]				= (SI32)siPriceValue;
						m_clShopData.m_siSelectedInventoryPos[i]= 0;
						m_clShopData.m_siHandPoint				= siHandValue;
						m_clShopData.m_siSkillLevel				= siSkillValue;


						TCHAR itemname[128];
						if(m_clShopData.m_clItem[ i ].GetFullName(pclClient->pclItemManager, itemname, 128) == true)			
						{
							TCHAR buffer[512];
							TCHAR item[128]= TEXT(" ") ;
							TCHAR num[128]= TEXT(" ") ;
							TCHAR money[128]= TEXT(" ") ;
							TCHAR hand[128]= TEXT(" ") ;
							TCHAR skill[128]= TEXT(" ") ;							
							TCHAR* pText = GetTxtFromMgr(2228);
							StringCchPrintf(num, 128, TEXT("%d"), (SI32)siAmountValue);
							StringCchPrintf(money, 128, TEXT("%d"),(SI32)siPriceValue);
							StringCchPrintf(hand, 128, TEXT("%d"),(SI32)siHandValue);
							StringCchPrintf(skill, 128, TEXT("%d"), (SI32)siSkillValue);

							Nsprintf(buffer,pText,TEXT("item"), itemname   ,TEXT("num"),  num  ,TEXT("money"), money   ,TEXT("hand"), hand   ,TEXT("skill"),  skill  ,NULL);
							//sprintf(buffer, pText,
							//				itemname, (SI32)siAmountValue, (SI32)siPriceValue,
							//				(SI32)siHandValue, (SI32)siSkillValue
							//				);
							DisplayMessage(TRUE, buffer);


							// EDIT�� ��������� ǥ���Ѵ�.
							cltShopBannerData clShopBanner;
							clShopBanner.SetData(&m_clShopData);
							clShopBanner.MakeBannerText(pclClient->pclItemManager, m_szShopBanner);
							// Edit �ؽ�Ʈ ���� ����!!
							m_szShopBanner[ MAX_PERSONAL_SHOP_TEXT_SIZE - 1] = '\0';
							m_pEdit_explain->SetText(m_szShopBanner);
						}

						return true;
					}
				}
				TCHAR* pText = GetTxtFromMgr(2216);
				DisplayMessage(FALSE, pText);
				return false;
			}
		}
	}

	DisplayMessage(FALSE, TEXT(""));
	return false;
}

bool CNPersonalShopDlg::DropShopItem(SI32 siShopShowCaseSelectedIndex)
{
	if(siShopShowCaseSelectedIndex<0 || siShopShowCaseSelectedIndex>=MAX_SHOP_ITEM_NUMBER)
	{
		TCHAR* pText = GetTxtFromMgr(2229);
		DisplayMessage(FALSE, pText);
		return false;
	}

	m_clShopData.m_clItem[siShopShowCaseSelectedIndex].Init();
	m_clShopData.m_siSelectedInventoryPos[siShopShowCaseSelectedIndex]	= 0;
	m_clShopData.m_siPrice[siShopShowCaseSelectedIndex]					= 0;

	cltShopTradeData	TempShopData;
	memcpy(&TempShopData, &m_clShopData, sizeof(cltShopTradeData));
	memset(&m_clShopData, 0, sizeof( cltShopTradeData ) );		// �޸𸮸� Clear ��Ų��.

	// ������ ���� �����Ѵ�. 
	m_clShopData.m_siShopMode =  TempShopData.m_siShopMode;
	m_clShopData.m_siPersonID =  TempShopData.m_siPersonID; 
	StringCchCopy(m_clShopData.m_szAccountID, MAX_PLAYER_NAME, TempShopData.m_szAccountID);

	SI32 siIndex = 0;
	for ( SI32 i = 0; i < MAX_SHOP_ITEM_NUMBER; ++i )
	{	
		if(TempShopData.m_clItem[i].siUnique>0)
		{
			m_clShopData.m_clItem[siIndex].Set(&TempShopData.m_clItem[i]);
			m_clShopData.m_siSelectedInventoryPos[siIndex]  = TempShopData.m_siSelectedInventoryPos[i]; 
			m_clShopData.m_siPrice[siIndex]					= TempShopData.m_siPrice[i];
			siIndex++;
		}
	}	

	// EDIT�� ��������� ǥ���Ѵ�.
	cltShopBannerData clShopBanner;
	clShopBanner.SetData(&m_clShopData);
	clShopBanner.MakeBannerText(pclClient->pclItemManager, m_szShopBanner);

	// Edit �ؽ�Ʈ ���� ����!!
	m_szShopBanner[ MAX_PERSONAL_SHOP_TEXT_SIZE - 1] = '\0';
	m_pEdit_explain->SetText(m_szShopBanner);

	TCHAR* pText = GetTxtFromMgr(2230);
	DisplayMessage(TRUE, pText);

	return true;
}

bool CNPersonalShopDlg::SellShopItem(SI32 siUserInventoryRealIndex)
{
	if(siUserInventoryRealIndex < PERSONITEM_INV0 ||  siUserInventoryRealIndex >= MAX_ITEM_PER_PERSON)
	{	
		TCHAR* pText = GetTxtFromMgr(2231);
		DisplayMessage(FALSE, pText); 
		return false;
	}

	SI32 siFoundShowCaseIndex = -1;
	for ( SI32 i = 0; i < MAX_SHOP_ITEM_NUMBER; ++i )
	{	
		if(m_clShopData.m_clItem[i].siUnique>0)
		{
			if(m_clUserItem[siUserInventoryRealIndex].siUnique == m_clShopData.m_clItem[i].siUnique)
			{
				siFoundShowCaseIndex = i;
				break;
			}
		}
	}

	// ������ �߰��ߴٸ� (���� unique�� �ø��� �����Ƿ� �����ϴ�.)
	if(siFoundShowCaseIndex>= 0 && siFoundShowCaseIndex<MAX_SHOP_ITEM_NUMBER)
	{
		// ������ ���ǰ����� �����ؾ��Ѵ�.
		if(m_clShopData.m_clItem[ siFoundShowCaseIndex ].siItemNum>0 && m_clShopData.m_clItem[ siFoundShowCaseIndex ].siItemNum <= MAX_ITEM_PILE_NUMBER)
		{
			TCHAR AmountBuffer[256];
			TCHAR* pTmpChar = NULL;
			GMONEY  siPrice		    = 0;
			SI32  siAmountSuccess	= 0;
			SI64  siAmountValue     = 0;

			pTmpChar =m_pEdit_amount->GetText();

			if( pTmpChar == NULL )
				return FALSE;

			_tcscpy( AmountBuffer, pTmpChar );

			siAmountSuccess = _tcslen( AmountBuffer );

			if(siAmountSuccess > 127) return false;

			if(siAmountSuccess>0)	siAmountValue = _tstoi64(AmountBuffer);
			// �Ǹſ䱸���� ������ ���� ���� �̳�����Ѵ�.
			if(siAmountValue > 0 )
			{
				// ������ ������ Showcase�������� ũ�� �ִ� Showcase������ �����Ѵ�.
				if(siAmountValue >= m_clShopData.m_clItem[ siFoundShowCaseIndex ].siItemNum ) 
					siAmountValue = m_clShopData.m_clItem[ siFoundShowCaseIndex ].siItemNum;

				// ������ ������ �����ؾ��Ѵ�.
				if(m_clShopData.m_siPrice[siFoundShowCaseIndex] > 0 && m_clShopData.m_siPrice[siFoundShowCaseIndex] <= MAX_PRICE_IN_MARKET)
				{
					cltClient *pclclient = ( cltClient * )pclClient;
					cltItem clitem;

					//cyj ���������κ��� �ִ� �������� ��������.. ��.��;;
					//clitem.Set(&m_clShopData.m_clItem[ siFoundShowCaseIndex ]);	// �ٸ� ��� ������ ������ 
					clitem.Set(&m_clUserItem[siUserInventoryRealIndex]);

					clitem.siItemNum  = (SI32)siAmountValue;					// ������ �ٸ���.
					siPrice			  = m_clShopData.m_siPrice[ siFoundShowCaseIndex ];
					cltGameMsgRequest_SellPersonalShop clInfo(m_siShopperCharUnique, m_siShopMode, m_siShopperPersonID, &clitem, siPrice, siFoundShowCaseIndex, siUserInventoryRealIndex);
					cltMsg clMsg( GAMEMSG_REQUEST_SELLPERSONALSHOP, sizeof(clInfo), (BYTE*)&clInfo );
					pclclient->SendMsgToServer((sPacketHeader*)&clMsg);

					DisplayMessage(TRUE, TEXT(""));
					return true;
				}
				else {
					TCHAR* pText = GetTxtFromMgr(2232);
					DisplayMessage(FALSE, pText);  }
			}
			else { 
				TCHAR* pText = GetTxtFromMgr(2233);
				DisplayMessage(FALSE, pText);  }
		}
		else { 
			TCHAR* pText = GetTxtFromMgr(2234);
			DisplayMessage(FALSE, pText);	}
	}
	else	{  
		TCHAR* pText = GetTxtFromMgr(2235);
		DisplayMessage(FALSE, pText);	}


	return false;

}

bool CNPersonalShopDlg::BuyShopItem()
{
	// showcase�� �ִ� ��ǰ�� ���� ���� ������ŭ ������ ���.
	if(m_siShopShowCaseSelectedIndex>= 0 && m_siShopShowCaseSelectedIndex< MAX_SHOP_ITEM_NUMBER)
	{
		if(m_clShopData.m_clItem[ m_siShopShowCaseSelectedIndex ].siItemNum>0)
		{
			TCHAR AmountBuffer[256];
			TCHAR *pTmpChar = NULL;
			GMONEY  siPrice		    = 0;
			SI32  siAmountSuccess	= 0;
			SI64  siAmountValue     = 0;

			pTmpChar = m_pEdit_amount->GetText();

			if(pTmpChar == NULL ) return false;

			_tcscpy( AmountBuffer, pTmpChar );

			siAmountSuccess = _tcslen( AmountBuffer );

			if(siAmountSuccess > 127 ) return false;

			if(siAmountSuccess>0)	siAmountValue = _tstoi64(AmountBuffer);
			if(siAmountValue > 0)
			{
				// ���� ���� �ִµ��� ������ ������ ���ݰ� ���Ѵ�.
				SI64 BuyerMoney   = (SI64)pclClient->pclCM->CR[1]->pclCI->clIP.GetMoney();
				SI64 siTotalPrice = (SI64)m_clShopData.m_siPrice[m_siShopShowCaseSelectedIndex] * siAmountValue ;
				if ( BuyerMoney  >= siTotalPrice )
				{
					cltClient *pclclient = ( cltClient * )pclClient;
					cltItem clitem;
					clitem.Set(&m_clShopData.m_clItem[ m_siShopShowCaseSelectedIndex ]);	// �ٸ� ��� ������ ������ 
					clitem.siItemNum  = (SI32)siAmountValue;								// ������ �ٸ���.
					siPrice			  = m_clShopData.m_siPrice[ m_siShopShowCaseSelectedIndex ];
					cltGameMsgRequest_BuyPersonalShop clInfo(m_siShopperCharUnique, m_siShopMode, m_siShopperPersonID, &clitem, siPrice, m_siShopShowCaseSelectedIndex);
					cltMsg clMsg( GAMEMSG_REQUEST_BUYPERSONALSHOP, sizeof(clInfo), (BYTE*)&clInfo );
					pclclient->SendMsgToServer((sPacketHeader*)&clMsg);

					DisplayMessage(TRUE, TEXT(""));
					return true;
				}
				else {
					TCHAR* pText = GetTxtFromMgr(2236);
					DisplayMessage(FALSE, pText);	}
			}
			else {
				TCHAR* pText = GetTxtFromMgr(2237);
				DisplayMessage(FALSE, pText); }
		}
		else { 
			TCHAR* pText = GetTxtFromMgr(2238);
			DisplayMessage(FALSE, pText);	}
	}
	else { TCHAR* pText = GetTxtFromMgr(2239);
	DisplayMessage(FALSE, pText); }

	return false;
}
bool CNPersonalShopDlg::MakeShopItem()
{
	// showcase�� �ִ� ��ǰ�� ���� ���� ������ŭ ������ �����.
	if(m_siShopShowCaseSelectedIndex>= 0 && m_siShopShowCaseSelectedIndex< MAX_SHOP_MAKEITEM_NUMBER)
	{
		if(m_clShopData.m_clItem[ m_siShopShowCaseSelectedIndex ].siItemNum>0)
		{
			TCHAR AmountBuffer[256];
			SI32  siAmountSuccess	= 0;
			SI64  siAmountValue     = 0;
			TCHAR *pTmpChar = NULL;
			pTmpChar = m_pEdit_amount->GetText();

			if(pTmpChar == NULL )
			{
				TCHAR* pText = GetTxtFromMgr(2240);
				DisplayMessage(FALSE, pText); 

				return false;
			}

			_tcscpy( AmountBuffer, pTmpChar );
			//siAmountSuccess = GetDlgItemText( m_hDlg, m_pEdit_amount, AmountBuffer,  128 );

			siAmountSuccess = _tcslen( AmountBuffer );

			if(siAmountSuccess>0)	siAmountValue = _tstoi64(AmountBuffer);
			if(siAmountValue > 0)
			{
				cltClient *pclclient = ( cltClient * )pclClient;
				cltItem clitem;
				clitem.Set(&m_clShopData.m_clItem[ m_siShopShowCaseSelectedIndex ]);	// �ٸ� ��� ������ ������ 
				clitem.siItemNum  = (SI32)siAmountValue;								// ������ �ٸ���.

				GMONEY	siPrice	    = 0;
				SI32  siHandpoint   = 0;
				SI32  siSkillLevel  = 0;
				siPrice			  = m_clShopData.m_siPrice[ m_siShopShowCaseSelectedIndex ];
				siHandpoint		  = m_clShopData.m_siHandPoint;
				siSkillLevel	  = m_clShopData.m_siSkillLevel;
				cltGameMsgRequest_MakePersonalShop clInfo(m_siShopperCharUnique, m_siShopMode, m_siShopperPersonID, &clitem, siPrice, siHandpoint, siSkillLevel,m_siShopShowCaseSelectedIndex,0);
				cltMsg clMsg( GAMEMSG_REQUEST_MAKEPERSONALSHOP, sizeof(clInfo), (BYTE*)&clInfo );
				pclclient->SendMsgToServer((sPacketHeader*)&clMsg);

				DisplayMessage(TRUE, TEXT(""));
				return true;
			}
			else { 
				TCHAR* pText = GetTxtFromMgr(2240);
				DisplayMessage(FALSE, pText); }
		}
		else { 
			TCHAR* pText = GetTxtFromMgr(2241);
			DisplayMessage(FALSE, pText);	}
	}
	else { 
		TCHAR* pText = GetTxtFromMgr(2242);
		DisplayMessage(FALSE, pText); }

	return false;
}
void CNPersonalShopDlg::DisplayMessage(SI32 siSuccess, TCHAR *pBuffer)
{
	if(siSuccess<=0)	pclClient->PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_FAILURE")) , 0, 0);
	if(pBuffer)
	{
		//SetWindowText(GetDlgItem( m_hDlg, m_pEdit_message), pBuffer);
		m_pEdit_message->SetText( pBuffer );
	}
}


void CNPersonalShopDlg::StartPersonalShop()
{
	cltClient *pclclient = ( cltClient * )pclClient;

	if(m_siShopMode == PSHOP_MODE_BUY)
	{
		SI64 siTotalPrice = 0;
		SI32 i;
		for ( i = 0; i < MAX_SHOP_ITEM_NUMBER; ++i )
		{
			if(m_clShopData.m_clItem[i].siUnique > 0)
				siTotalPrice += (m_clShopData.m_clItem[i].siItemNum * (SI64)m_clShopData.m_siPrice[i]);
		}

		// ���� ���� �ִµ��� ������ ������ ���ݰ� ���Ѵ�.
		SI64 BuyerMoney   = (SI64)pclClient->pclCM->CR[1]->pclCI->clIP.GetMoney();

		if ( BuyerMoney  < siTotalPrice )
		{
			TCHAR* pTitle = GetTxtFromMgr(6083);
			TCHAR* pText = GetTxtFromMgr(6084);

			pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
			return;
		}
	}

	SI32 siTicketNum = 1;

	m_clShopData.m_bPremium = m_pRadioPremium->IsCheck();
	
	//[����] �к� �����̾�. => 2008-3-25
	if(pclClient->IsCountrySwitch(Switch_SpecialPersonShop))  
	{
		SI32 Index = m_pCombobox_personshop_kind->GetSelectedIndex();
		if(1 == Index)
		{
			m_clShopData.m_bPremium = true;
		}
		else
		{
			m_clShopData.m_bPremium = false;
		}
	}


	// �����̾����� �����ߴµ� �����̾� Ƽ���� ������ �������� �ʰ� ��� �޽��� ������
	if((m_clShopData.m_bPremium == true) )
	{

		if(pclclient->pclCM->CR[1]->pclCI->clCharItem.GetItemNum(ITEMUNIQUE(24075)) < siTicketNum )
		{
			TCHAR * pTitle = GetTxtFromMgr(6083);
			TCHAR * pText = GetTxtFromMgr(6617);

			pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
			return;
		}

		SI16 TitleLength = _tcslen(m_pShopTitle_Edit->GetText());

		if( TitleLength <= 0 )
		{
			TCHAR* pText = GetTxtFromMgr(6639);
			DisplayMessage(FALSE, pText);
			return ;
		}
	}

	if (
		(( m_clShopData.m_bPremium	 == false ) &&  pclclient->pclCM->CR[1]->pclCI->clCharItem.GetItemNum(ITEMUNIQUE(24010)) >= siTicketNum)
		|| ((m_clShopData.m_bPremium == true)	&&	pclclient->pclCM->CR[1]->pclCI->clCharItem.GetItemNum(ITEMUNIQUE(24075)) >= siTicketNum )
		)
	{
		TCHAR buffer[256] = TEXT("") ;
		TCHAR* pText = GetTxtFromMgr(2243);
		StringCchPrintf(buffer, 256, pText, siTicketNum);

		if(m_pRadioPremium->IsCheck() == false)
			pText = GetTxtFromMgr(2244);
		else
			pText = GetTxtFromMgr(6618);

		stMsgBox MsgBox;
		MsgBox.Set( this, pText, buffer, MSGBOX_TYPE_YESNO, 0 );
		pclclient->SetMsgBox( &MsgBox, NULL, 0 );
	}
	else	
	{
		TCHAR buffer[256] = TEXT("") ;
		TCHAR* pText = GetTxtFromMgr(2245);
		StringCchPrintf(buffer, 256, pText, siTicketNum);
		DisplayMessage(FALSE, buffer);
	}
}
void CNPersonalShopDlg::StartPersonalSpecialShop()
{
	cltClient *pclclient = ( cltClient * )pclClient;

	SI32 siTicketNum = 1;

	if(pclclient->pclCM->CR[1]->pclCI->clCharItem.GetItemNum(ITEMUNIQUE(SPECIAL_PREMIUN_TICKET_UNIQUE)) < siTicketNum )
	{
		TCHAR * pTitle = GetTxtFromMgr(6083);
		TCHAR * pText = GetTxtFromMgr(6617);

		pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
		return;
	}

	SI16 TitleLength = _tcslen(m_pShopTitle_Edit->GetText());

	if( TitleLength <= 0 )
	{
		TCHAR* pText = GetTxtFromMgr(6639);
		DisplayMessage(FALSE, pText);
		return ;
	}

	if(0 >= m_clShopData.m_clItem[1].siUnique)
	{
		TCHAR* pText = GetTxtFromMgr(1865);
		DisplayMessage(FALSE, pText);
		return ;
		return;
	}

	m_clShopData.m_bPremium = true;

	TCHAR buffer[256] = TEXT("") ;
	TCHAR* pText = GetTxtFromMgr(8404);
	StringCchPrintf(buffer, 256, pText, siTicketNum);
	
	pText = GetTxtFromMgr(5614);
	
	stMsgBox MsgBox;
	MsgBox.Set( this, pText, buffer, MSGBOX_TYPE_YESNO, 0 );
	pclclient->SetMsgBox( &MsgBox, NULL, 0 );

}
void CNPersonalShopDlg::StopPersonalShop()
{
	//	m_bShopMoneyCheck = FALSE;

	cltGameMsgRequest_StopPersonalShop clshopdata( m_siShopperCharUnique);
	cltMsg clMsg( GAMEMSG_REQUEST_STOPPERSONALSHOP, sizeof( clshopdata ), (BYTE*)&clshopdata );
	cltClient *pclclient = ( cltClient * )pclClient;
	pclclient->SendMsgToServer((sPacketHeader*)&clMsg);

	DeleteDialog();
	//Hide();
}


void CNPersonalShopDlg::ShowMoneyText()
{
	SI32 siPriceSuccess = 0;
	TCHAR PriceBuffer[256]=TEXT("");
	TCHAR *pTmpChar = NULL;

	pTmpChar = m_pEdit_price->GetText();

	if(pTmpChar == NULL ) return;

	_tcscpy( PriceBuffer, pTmpChar );

	siPriceSuccess  = _tcslen( PriceBuffer );
	//siPriceSuccess  = GetDlgItemText( m_hDlg, m_pEdit_price,  PriceBuffer,  128 );
	if(siPriceSuccess <= 0 || siPriceSuccess >= 128 )
	{
		m_pStatic_money->SetText(TEXT(""), DT_LEFT | DT_VCENTER );
		//SetWindowText( GetDlgItem( m_hDlg, m_pStatic_money->SetText(TEXT(""));
	}
	else
	{
		SI64 siPriceValue = 0;
		siPriceValue  = _tstoi64(PriceBuffer);
		if(siPriceValue <= 0)
		{
			m_pStatic_money->SetText(TEXT(""), DT_LEFT | DT_VCENTER );
			//SetWindowText( GetDlgItem( m_hDlg, m_pStatic_money->SetText(TEXT(""));
		}
		else
		{
			TCHAR szMoney[128];
			TCHAR* pText = GetTxtFromMgr(611);
			//cyj ���λ��� �ݾ� �޸�������.
			//g_JYLibFunction.SetNumTxt(siPriceValue , szMoney,pText);
			g_JYLibFunction.SetNumUnit(siPriceValue , szMoney, 128, pText);

			m_pStatic_money->SetText( szMoney, DT_LEFT | DT_VCENTER );
			//SetWindowText( GetDlgItem( m_hDlg, m_pStatic_money),  szMoney);
		}
	}
}


void CNPersonalShopDlg::SetMakeableItemList()
{
	stComboBoxItemData tmpComboBoxItemData;

	if(m_pComboBox_iteminfo_name == NULL ) return;

	// �޺� �ڽ��� �����.
	m_pComboBox_makeitem_name->Clear();

	SI32 m_siMakeableItemNum = 0;
	SI32 *m_pMakeableItemList = NULL;
	SI32 id = 1;

	// ������ ������ �����ش�. 
	cltItemManagerClient* pclitemmanager = (cltItemManagerClient*)pclClient->pclItemManager;
	if(pclitemmanager->FindMakeableItem(
		NULL, 
		&pclClient->pclCM->CR[id]->pclCI->clCharItem,
		NULL,
		MAX_INVITEM_PER_PERSON,
		&pclClient->pclCM->CR[id]->pclCI->clCharItem.clItem[PERSONITEM_INV0],
		&m_siMakeableItemNum,
		&m_pMakeableItemList,
		true) == true)
	{
		TCHAR buffer[256];
		for(SI32 i = 0; i < m_siMakeableItemNum; ++i)
		{
			TCHAR* pText = GetTxtFromMgr(2246);
			StringCchPrintf(buffer, 256, pText, pclitemmanager->GetName(m_pMakeableItemList[i*2]), m_pMakeableItemList[i*2 + 1]);
			tmpComboBoxItemData.Init();
			tmpComboBoxItemData.Set( buffer );
			m_pComboBox_makeitem_name->AddItem( &tmpComboBoxItemData );
			//SendMessage( hCombobox, CB_ADDSTRING, 0, (LPARAM)buffer );
		}

	}

	if(m_pMakeableItemList)
	{
		delete []m_pMakeableItemList;
		m_pMakeableItemList = NULL;
	}
}

void CNPersonalShopDlg::Action()
{
	cltClient *pclclient = ( cltClient * )pclClient;

	// ���� ���ڶ�� ���� �����Ų��
	/*	if(m_siShopMode == PSHOP_MODE_BUY && m_bShopMoneyCheck == TRUE &&
	pclclient->pclCM->CR[1]->pclCI->GetPersonID() == m_siShopperPersonID )
	{
		SI64 siTotalPrice = 0;
		SI32 i;
		for ( i = 0; i < MAX_SHOP_ITEM_NUMBER; ++i )
		{
			if(m_clShopData.m_clItem[i].siUnique > 0)
				siTotalPrice += (m_clShopData.m_clItem[i].siItemNum * (SI64)m_clShopData.m_siPrice[i]);
		}

		// ���� ���� �ִµ��� ������ ������ ���ݰ� ���Ѵ�.
		SI64 BuyerMoney   = (SI64)pclClient->pclCM->CR[1]->pclCI->clIP.GetMoney();

		if ( BuyerMoney  < siTotalPrice )
		{
			TCHAR* pTitle = GetTxtFromMgr(1351); 
			TCHAR* pText = "������ �� ���� ������ ������ �����մϴ�";

			pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
			StopPersonalShop();
			return;
		}
	}
	*/
		if ( IsUserInventoryChanged() )
		{
			LoadUserInventory();
		}

		if ( IsShopShowCaseChanged() )
		{
			LoadShopShwocase();
		}

		ShowMoneyText();
		//==================================
		// �������� �Ѱ��� �������� �ʾҴµ� ���� �Ҽ� ����.
		//==================================
		// �ڽ��� ������ ���� ������ ��� �������� �ϳ��� ���ٸ� HIDE
		if(m_bSelf == TRUE && m_bShopStarted == FALSE)
		{
			BOOL bHasItem = FALSE;
			for ( int i = 0; i < MAX_SHOP_ITEM_NUMBER; ++i )
			{
				if ( m_clShopData.m_clItem[ i ].siUnique != 0 )
				{
					bHasItem = TRUE;
					break;
				}
			}
			if(bHasItem == TRUE)	m_pButton_start->Enable( TRUE );
			else					m_pButton_start->Enable( FALSE );
		}
}

// cltItemManagerClient ���� ������ ======================================================================
// ������ ������ �����ش�. 
BOOL CNPersonalShopDlg::SetItemTypeInCombo( bool bshowall)
{
	cltItemManagerCommon* pclItemManager;
	pclItemManager = pclClient->pclItemManager;

	if(pclItemManager == NULL ) return false;

	SI32 i;
	stComboBoxItemData stTmpComboBoxItemData;
	// �޺� �ڽ��� �����.
	m_pComboBox_iteminfo_type->Clear();

	// �޺� �ڽ��� �������� ������ �����Ѵ�. 
	for(i = 0;i < MAX_ITEMTYPE_NUMBER;i++)
	{	
		cltItemTypeInfo* pinfo = pclItemManager->pclItemTypeInfo[i];
		if(pinfo == NULL)continue;

		// �ŷ� �Ұ� ǰ���̸� �������� �ʴ� �����̶��, 
		if(bshowall == false)
		{
			if(pinfo->IsAtb(ITEMATB_NOTRADE))continue;
		}
		// �޺�����Ʈ���� ����� �Ӽ��� �ִٸ�
		if( pinfo->IsAtb(ITEMATB_HIDECOMBOLIST) ) continue;

		//[���� : Ȳ���� 2007. 10. 17 ���� ���� ������ ǰ�� ��ȯ���� ������ �ʾ� ������.]
	/*	if(pinfo->siUnique == ITEMTYPE_DOLL)
			continue;*/

		stTmpComboBoxItemData.Init();
		stTmpComboBoxItemData.Set( (TCHAR*)pinfo->GetName());

		m_pComboBox_iteminfo_type->AddItem( &stTmpComboBoxItemData );
	}
	return TRUE;
}

// itemtypeunique�� �ش��ϴ� ������ ����Ʈ�� �����ش�. 
BOOL CNPersonalShopDlg::ShowItemListInCombo( SI32 itemtypeunique, bool btradeinterface)
{
	cltItemManagerCommon* pclItemManager;
	pclItemManager = pclClient->pclItemManager;

	if(pclItemManager == NULL ) return false;

	SI32 i;
	stComboBoxItemData tmpComboBoxItemData;
	// �޺� �ڽ��� �����.
	m_pComboBox_iteminfo_name->Clear();

	// �޺� �ڽ��� �������� ������ �����Ѵ�. 
	for(i = 0;i < MAX_ITEMINFO_NUMBER;i++)
	{	
		cltItemInfo* pinfo = pclItemManager->pclItemInfo[i];
		if(pinfo == NULL)continue;
		if(pinfo->siType != itemtypeunique)continue;

		// �־��� Ÿ�԰� ���� �����۸� �����Ѵ�. 
		// ����ڿ��� �������� �������� ��쿡��. 
		bool bshow = false;
		if(pinfo->IsItemInfoAtb(ITEMINFOATB_SHOWLIST))
		{
			if(btradeinterface == true)
			{
			//	if(pinfo->IsItemInfoAtb(ITEMINFOATB_TRADELIST)  == true)
				{
					bshow = true;
				}
			}
			else
			{
				bshow = true;
			}

			if(bshow)
			{
				tmpComboBoxItemData.Init();
				tmpComboBoxItemData.Set( (TCHAR*) pinfo->GetName() );

				m_pComboBox_iteminfo_name->AddItem( &tmpComboBoxItemData );

				//ComboAddString(hDlg, dlgitem, (LPARAM)pinfo->GetName());
			}
		}
	}

	return TRUE;
}

void CNPersonalShopDlg::RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen )
{
	cltClient *pclclient = (cltClient *)pclClient;

	switch( MsgIndex )
	{
	case 0:	// ���� ���� ����
		{
			if ( RetValue )
			{
				//[����] �к� �����̾�. => 2008-3-25
				if(pclClient->IsCountrySwitch(Switch_SpecialPersonShop))
				{
					SI32 Index = m_pCombobox_personshop_kind->GetSelectedIndex();
					if( SHOP_TYPE_SPECIAL_PREMIUM == Index )
					{
						SendServermessgeSpecialShop( pData );
						return;
					}
				}

				SI32 PersonID = *((SI32*)pData);

				TCHAR szText[MAX_PERSONAL_SHOP_TEXT_SIZE]=TEXT("");
				TCHAR *pTmpChar = NULL;
				bool	premium = false;

				premium = m_pRadioPremium->IsCheck();
				
				//[����] �к� �����̾�. => 2008-3-25
				if(pclClient->IsCountrySwitch(Switch_SpecialPersonShop))
				{
					SI32 Index = m_pCombobox_personshop_kind->GetSelectedIndex();
					if(1 == Index)
					{
						premium = true;
					}
					else
					{
						premium = false;
					}
				}

				pTmpChar = m_pEdit_explain->GetText();
				if( pTmpChar == NULL )
					return ;

				_tcscpy( szText, pTmpChar );

				if(_tcslen(szText) >= MAX_PERSONAL_SHOP_TEXT_SIZE ) return;

				// �����̾��϶� Ƽ�� üũ

				SI32 siTicketNum = 1;


				// �����̾����� �����ߴµ� �����̾� Ƽ���� ������ �������� �ʰ� ��� �޽��� ������
				if((m_clShopData.m_bPremium == true))
				{

					if(pclclient->pclCM->CR[1]->pclCI->clCharItem.GetItemNum(ITEMUNIQUE(24075)) < siTicketNum )
					{
						TCHAR * pTitle = GetTxtFromMgr(6083);
						TCHAR * pText = GetTxtFromMgr(6617);

						pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
						return;
					}

					SI16 TitleLength = _tcslen(m_pShopTitle_Edit->GetText());

					if( TitleLength <= 0 )
					{
						TCHAR* pText = GetTxtFromMgr(6639);
						DisplayMessage(FALSE, pText);
						return ;
					}

#ifdef _IAF_EXPORT
					if( pclClient->IsWhereServiceArea(ConstServiceArea_USA) )
					{
						TCHAR ResultBuf[1024] = "";
						IAF::Filtering( m_pShopTitle_Edit->GetText(), ResultBuf, sizeof(ResultBuf), IAF::FILTER_CHARACTER );
						memcpy( m_pShopTitle_Edit->GetText(), ResultBuf, strlen(ResultBuf) * sizeof(ResultBuf[0]) + 1 );
					}
#else
					pclclient->m_pCAbuseFilter->CheckAbuse(m_pShopTitle_Edit->GetText());
#endif


					StringCchCopy(m_clShopData.m_szShopTitle,MAX_SHOP_TITLE_LENGTH,m_pShopTitle_Edit->GetText());

				}


				// ���� �ٲ�� �־ �������ش�.
				m_clShopData.m_siShopMode   = m_siShopMode;
				// ������϶��� üũ�Ѵ�
				if(m_clShopData.m_siShopMode == PSHOP_MODE_BUY)
				{
					cltCharClient* pclChar = (cltCharClient*)pclClient->pclCM->CR[1];
					pclChar->bMyShopStart = TRUE;

					for ( SI32 i = 0; i < MAX_SHOP_ITEM_NUMBER; ++i )
					{	
						if(m_clShopData.m_clItem[i].siUnique>0)
						{
							pclChar->clMyShopData.m_clItem[i].Set(&m_clShopData.m_clItem[i]);
							pclChar->clMyShopData.m_siPrice[i] = m_clShopData.m_siPrice[i];
						}
					}	
				}

				// [����] ���� �����߿��� �Ҽ�����
				if ( true == pclClient->pclCM->CR[1]->bIsElectionStump )
				{
					TCHAR* pTitle = GetTxtFromMgr(836);
					TCHAR* pText = GetTxtFromMgr(8278);

					pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
					return;
				}
				

				cltGameMsgRequest_StartPersonalShop clshopdata( m_siShopperCharUnique,  &m_clShopData);
				cltMsg clMsgDt( GAMEMSG_REQUEST_STARTPERSONALSHOP, sizeof( clshopdata ), (BYTE*)&clshopdata );
				pclclient->SendMsgToServer((sPacketHeader*)&clMsgDt);

				DeleteDialog();
			}
		}
		break;
	}
}

void CNPersonalShopDlg::RefreshSelectedItem()
{
	SI16 siTmpRow = -1, siTmpCol = -1;
	m_pList_shop_showcase->GetSelectedIndex( &siTmpRow, &siTmpCol );

	if(siTmpRow < 0 ) return;
	m_siShopShowCaseSelectedRealItemIndex = m_siShopTradeIndex[siTmpRow];
	m_siShopShowCaseSelectedIndex = m_siShopTradeIndex[siTmpRow];

	if (m_siShopShowCaseSelectedIndex == -1) 
		return;

	if ( m_clShopData.m_clItem[ m_siShopShowCaseSelectedRealItemIndex ].siUnique != 0 )
	{
		TCHAR ItemExplain[ 512 ] = TEXT("");
		cltItemManagerClient* pclitemmanager = (cltItemManagerClient*)pclClient->pclItemManager;
		if(m_siShopMode == PSHOP_MODE_SELL) // ������ �ȶ��� ��Ȯ�� ������ �����ֳ�.
			pclitemmanager->GetExplain( &m_clShopData.m_clItem[ m_siShopShowCaseSelectedRealItemIndex ], ItemExplain );
		else								// ������ �춧�� �ش� ��ǰ�� ���.
			pclitemmanager->GetExplain( m_clShopData.m_clItem[ m_siShopShowCaseSelectedRealItemIndex ].siUnique, ItemExplain );

		SI32 silen = _tcslen(ItemExplain);
		if( silen > 2 && ItemExplain[silen-1] =='\n') {	ItemExplain[silen-1] = 0;	}
		if( silen > 2 && ItemExplain[silen-2] =='\r') {	ItemExplain[silen-2] = 0;	}

		DisplayMessage(TRUE,ItemExplain);
	}

}


void CNPersonalShopDlg::SetItemImageData(SI32 ItemUnique)
{
	if(pclClient->pclItemManager->GetItemGImageFileIndexAndFont( ItemUnique, &m_siImageType, &m_siImageIndex ) )
	{}
	else
	{
		m_siImageType = -1;
		m_siImageIndex = -1;
	}
}

void CNPersonalShopDlg::VDirectDrawToBackScreen( LPDIRECTDRAWSURFACE7 lpBackScreen, SI32 ScreenRX, SI32 ScreenRY )
{

	if( m_siImageIndex < 0 || m_siImageType < 0 )
		return;

	cltClient *pclclient = ( cltClient * )pclClient;
	TSpr *pSpr = pclclient->pclGImg->GetGlobalSpr( m_siImageType );

	if ( pSpr )
	{
		GP.PutSpr( pSpr ,ScreenRX +  GetX() + 30,ScreenRY +  GetY() + 452, m_siImageIndex);
	}

}

void CNPersonalShopDlg::NormalShopInit()
{

	m_pRadioNormal->SetNonEventCheck();
	m_pShopTitle_Static->Show(false);
	m_pShopTitle_Edit->Show(false);
}

void CNPersonalShopDlg::PremiumShopInit()
{

	m_pRadioPremium->SetNonEventCheck();
	m_pShopTitle_Static->Show(true);
	m_pShopTitle_Edit->Show(true);

}

void CNPersonalShopDlg::NormalShopInitNew()
{
	m_pShopTitle_Static->Show(false);
	m_pShopTitle_Edit->Show(false);
	m_pRadioButtonButton_buy->Enable(true);
	m_pList_shop_showcase->Show( true );
 
	// �к� �����̾��� ����Ʈ �並 ���δ�.
	m_plistview_ticket->Show( false );
	m_plistview_item->Show( false );
}

void CNPersonalShopDlg::PremiumShopInitNew()
{
	m_pShopTitle_Static->Show(true);
	m_pShopTitle_Edit->Show(true);


	bool bSpecialPremium = false;
	SI32 Index = m_pCombobox_personshop_kind->GetSelectedIndex();
	if( SHOP_TYPE_SPECIAL_PREMIUM == Index )
	{
		bSpecialPremium = true;
		m_pRadioButtonButton_buy->Enable(false);
	}
	// �к� �����̾��� ����Ʈ �並 ���δ�.
	m_plistview_ticket->Show( bSpecialPremium );
	m_plistview_item->Show( bSpecialPremium );
	
	// �ƴϸ� ��� ����Ʈ �ڽ�.
	m_pList_shop_showcase->Show( !bSpecialPremium );
}


void CNPersonalShopDlg::HidePremiumInterface()
{
	m_pRadioPremium->Show(false);
	m_pRadioNormal->Show(false);
	m_pShopTitle_Edit->Show(false);
	m_pShopTitle_Static->Show(false);
	m_pCombobox_personshop_kind->Show(false);  
}

void CNPersonalShopDlg::SendServermessgeSpecialShop(BYTE *pData)
{
	cltClient *pclclient = (cltClient *)pclClient;
	SI32 PersonID = *((SI32*)pData);

	TCHAR szText[MAX_PERSONAL_SHOP_TEXT_SIZE]=TEXT("");
	TCHAR *pTmpChar = NULL;
	bool	premium = false;

	premium = true;

	pTmpChar = m_pEdit_explain->GetText();
	if( pTmpChar == NULL )
		return ;

	_tcscpy( szText, pTmpChar );

	if(_tcslen(szText) >= MAX_PERSONAL_SHOP_TEXT_SIZE ) return;

	SI32 siTicketNum = 1;

	if(pclclient->pclCM->CR[1]->pclCI->clCharItem.GetItemNum(ITEMUNIQUE(SPECIAL_PREMIUN_TICKET_UNIQUE)) < siTicketNum )
	{
		TCHAR * pTitle = GetTxtFromMgr(6083);
		TCHAR * pText = GetTxtFromMgr(6617);

		pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
		return;
	}

	SI16 TitleLength = _tcslen(m_pShopTitle_Edit->GetText());

	if( TitleLength <= 0 )
	{
		TCHAR* pText = GetTxtFromMgr(6639);
		DisplayMessage(FALSE, pText);
		return ;
	}

#ifdef _IAF_EXPORT
	if( pclClient->IsWhereServiceArea(ConstServiceArea_USA) )
	{
		TCHAR ResultBuf[1024] = "";
		IAF::Filtering( m_pShopTitle_Edit->GetText(), ResultBuf, sizeof(ResultBuf), IAF::FILTER_CHARACTER );
		memcpy( m_pShopTitle_Edit->GetText(), ResultBuf, strlen(ResultBuf) * sizeof(ResultBuf[0]) + 1 );
	}
#else
	pclclient->m_pCAbuseFilter->CheckAbuse(m_pShopTitle_Edit->GetText());
#endif

	StringCchCopy(m_clShopData.m_szShopTitle,MAX_SHOP_TITLE_LENGTH,m_pShopTitle_Edit->GetText());


	// ���� �ٲ�� �־ �������ش�.
	m_clShopData.m_siShopMode   = m_siShopMode;
	
	// ������϶��� üũ�Ѵ�
	if(m_clShopData.m_siShopMode == PSHOP_MODE_BUY)
	{
		cltCharClient* pclChar = (cltCharClient*)pclClient->pclCM->CR[1];
		pclChar->bMyShopStart = TRUE;

		for ( SI32 i = 0; i < MAX_SHOP_ITEM_NUMBER; ++i )
		{	
			if(m_clShopData.m_clItem[i].siUnique>0)
			{
				pclChar->clMyShopData.m_clItem[i].Set(&m_clShopData.m_clItem[i]);
				pclChar->clMyShopData.m_siPrice[i] = m_clShopData.m_siPrice[i];
			}
		}	
	}

	cltGameMsgRequest_StartPersonalShop clshopdata( m_siShopperCharUnique,  &m_clShopData);
	cltMsg clMsgDt( GAMEMSG_REQUEST_STARTPERSONALSHOP, sizeof( clshopdata ), (BYTE*)&clshopdata );
	pclclient->SendMsgToServer((sPacketHeader*)&clMsgDt);

	DeleteDialog();
}
// ========================================================================================================

void CNPersonalShopDlg::ShowPremiumMode( bool bPremium )
{
	bool bNowPremiumMode = bPremium;

	if( pclClient->IsCountrySwitch(Switch_SpecialPersonShop) )
	{
		if ( SHOP_TYPE_PREMIUM == m_pCombobox_personshop_kind->GetSelectedIndex() )
		{
			bNowPremiumMode = true;
		}
	}

	if ( bNowPremiumMode )
	{
		PremiumShopInit();
	}
}
