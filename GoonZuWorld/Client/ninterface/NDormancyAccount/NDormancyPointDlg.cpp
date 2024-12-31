#include "client.h"


#include "NDormancyPointDlg.h"

#include "../../InterfaceMgr/Interface/ImageStatic.h"
#include "../../InterfaceMgr/Interface/Button.h"
#include "../../InterfaceMgr/Interface/List.h"
#include "../../InterfaceMgr/Interface/Edit.h"
#include "../../InterfaceMgr/Interface/Static.h"
#include "../../InterfaceMgr/InterfaceMgr.h"
#include "../../InterfaceMgr/InterfaceImgMgr/InterfaceImgMgr.h"
#include "../../InterfaceMgr/InterfaceFile.h"
#include "Char\CharManager\CharManager.h"

#include "../../../CommonLogic/MsgType-Item.h"
#include "../../../CommonLogic/MsgType.h"
#include "../../../CommonLogic/CommonLogic.h"

#include "../../ninterface/npartydlg/NPartyDlg.h"
#include "../../ninterface/nletterdlg/NLetterDlg.h"
#include "../NHelpButton/NHelpButtonDlg.h"
#include "../NMarriageLoveLevelDlg/NMarriageLoveLevelDlg.h"
#include "../nprivatechatdlg/NPrivateChatDlgMgr.h"
#include "../NFamilyCookieDlg/NFamilyCookieDlg.h"
#include "../NFamilyInfoDlg/NFamilyInfoDlg.h"

#include "../CommonLogic/Msg/MsgType-DormancyAccount.h"

extern cltCommonLogic* pclClient;

CNDormancyPointDlg::CNDormancyPointDlg()
{
	m_siImageType = -1;
	m_siImageIndex = -1;

	m_siSelctedUnique = 0;	// ���õ� ������

	//	������ �̹���
	m_pItemImage = NULL;
	//	������ ����Ʈ
	m_pItemListBox = NULL;
	//	���� ��ư
	m_pBuyButton = NULL;
	//	���� ��ư
	m_pCloseButton = NULL;
	//	����
	m_pTextStatic = NULL;
	//  �޸� ����Ʈ ����
	m_pPointInfoEdit = NULL;

	//	�̴Ϲ� ��ư
	m_pMinimiButton = NULL;

	m_bMini	= FALSE;
	m_siOldPosX = 0;
	m_siOldPosY = 0;
	m_siOldXSize = 0;
	m_siOldYSize = 0;

	m_siMinimizedSlot = 0;
	ZeroMemory(m_szTempBgImgFilePath,MAX_PATH * sizeof(TCHAR));	// �ӽ� ��� �̹��� ���� ���
	ZeroMemory(m_szTempTitle,MAX_PATH * sizeof(TCHAR));	// �ӽ� ��� �̹��� ���� ���
}
CNDormancyPointDlg::~CNDormancyPointDlg()
{

	//	������ �̹���
	SAFE_DELETE(m_pItemImage);
	//	������ ����Ʈ
	SAFE_DELETE(m_pItemListBox);
	//	���� ��ư
	SAFE_DELETE(m_pBuyButton);
	//	���� ��ư
	SAFE_DELETE(m_pCloseButton);
	//	����
	SAFE_DELETE(m_pTextStatic);
	//  �޸� ����Ʈ ����
	SAFE_DELETE(m_pPointInfoEdit);
	//	�̴Ϲ� ��ư 
	SAFE_DELETE(m_pMinimiButton);
}

void CNDormancyPointDlg::Destroy()
{
	DeleteDialog();
}

void CNDormancyPointDlg::Create()
{
	cltClient *pclclient = (cltClient *)pclClient;

	if ( !IsCreate() )
	{
		CInterfaceFile file;

		file.LoadFile("NInterface/Data/NDormancyAccount/DLG_NDormancyPointDlg.ddf");
		//	������ �̹���
		m_pItemImage = new CImageStatic(this);
		if( NULL == m_pItemImage)
		{
			return;
		}
		//	������ ����Ʈ
		m_pItemListBox = new CList(this);
		if( NULL == m_pItemListBox)
		{
			return;
		}
		//	���� ��ư
		m_pBuyButton = new CButton(this);
		if( NULL == m_pBuyButton)
		{
			return;
		}
		//	���� ��ư
		m_pCloseButton = new CButton(this);
		if( NULL == m_pCloseButton)
		{
			return;
		}
		//	����
		m_pTextStatic = new CStatic(this);
		if( NULL == m_pTextStatic)
		{
			return;
		}
		//  �޸� ����Ʈ ����
		m_pPointInfoEdit = new CEdit(this);
		if( NULL == m_pPointInfoEdit)
		{
			return;
		}
		//	�̴Ϲ� ��ư 
		m_pMinimiButton = new CButton(this);
		if( NULL == m_pMinimiButton)
		{
			return;
		}

		file.CreatePopupDialog( this, NDORMANCYPOINT_DLG, "dialog_DormancyPoint", StatiCNDormancyPointProc);

		file.CreateControl( m_pItemImage, NDORMANCYPOINT_IMAGE_ITEM,   "imagestatic_Item"); 
		file.CreateControl( m_pBuyButton, NDORMANCYPOINT_BUTTON_BUY,   "button_buy"); 
		file.CreateControl( m_pItemListBox, NDORMANCYPOINT_LISTBOX_ITEMLIST,   "listbox_itemlist"); 
		file.CreateControl( m_pPointInfoEdit, NDORMANCYPOINT_EDITBOX_POINTINFO,   "editbox_pointinfo");
		file.CreateControl( m_pCloseButton, NDORMANCYPOINT_BUTTON_CLOSE,   "button_close");
		file.CreateControl( m_pTextStatic, NDORMANCYPOINT_STATIC_TEXT,   "statictext_Text"); 
		file.CreateControl( m_pMinimiButton, NDORMANCYPOINT_BUTTON_MINIMI,   "button_minimi"); 
	}

	m_pTextStatic->SetText(GetTxtFromMgr(40082));

	// title �ӽ� ����
	StringCchCopy(m_szTempTitle, MAX_PATH, GetTitle());

	TCHAR* pText = GetTxtFromMgr(8120);
	m_pItemListBox->SetColumn( 0, 160, pText );
	pText = GetTxtFromMgr(40088);
	m_pItemListBox->SetColumn( 1, 50, pText );

	ShowPointItemList();
	
	m_pItemListBox->Refresh();

	//  ��� �̹��� ���� �̸� �ӽ� ����
	StringCchCopy(m_szTempBgImgFilePath,MAX_PATH,GetFileName());

	Minimi(TRUE);

	return;
}

void CALLBACK CNDormancyPointDlg::StatiCNDormancyPointProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl)
{
	CNDormancyPointDlg *pThis = (CNDormancyPointDlg*)pControllerMgr;
	if( NULL != pThis)
	{
		pThis->NDormancyPointDlgProc( nEvent, nControlID, pControl );
	}
}

void CALLBACK CNDormancyPointDlg::NDormancyPointDlgProc(UINT nEvent, int nControlID, CControllerObj* pControl)
{
	cltClient *pclclient = (cltClient *)pclClient;
	CNDormancyPointDlg* pclDlg = (CNDormancyPointDlg*)pclclient->m_pDialog[NDORMANCYPOINT_DLG];
	if( NULL == pclDlg)
		return;

	switch( nControlID)
	{
	case COMMON_DIALOG_CLOSEBUTTON:
		{
			Minimi(TRUE);
			break;	
		}
	case NDORMANCYPOINT_BUTTON_CLOSE:	// â���߱�
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					Minimi(TRUE);
					break;
				}
			}
			break;	
		}
	case NDORMANCYPOINT_BUTTON_MINIMI:	// â�����
		{	
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					Minimi(FALSE);
					break;
				}
			}
		}
		break;
	case NDORMANCYPOINT_LISTBOX_ITEMLIST:	
		{
			switch( nEvent )
			{
			case EVENT_LISTBOX_SELECTION:
				{
					pclDlg->SelectItem();
					break;
				}
			}
		}
		break;
	case NDORMANCYPOINT_BUTTON_BUY:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					pclDlg->BuySelectItem();
				}
				break;
			}
		}
		break;	
	}
	return;
}

// ���� ������ ����
VOID CNDormancyPointDlg::BuySelectItem()
{
	cltClient *pclclient = (cltClient *)pclClient;

	CDormancySystem *pclDormancySystem = pclclient->pclDormancySystem;
	if(NULL == pclDormancySystem)
	{
		return;
	}

	CDormancyPointRewardClient *pclDormancyClient = (CDormancyPointRewardClient *)pclDormancySystem->GetDormancyPointReward();
	if(NULL == pclDormancyClient)
	{
		return;
	}

	pclDormancyClient->BuyPointItemRequest(m_siSelctedUnique);
}

//	������ ����
VOID CNDormancyPointDlg::SelectItem()
{
	cltClient *pclclient = (cltClient *)pclClient;

	CDormancySystem *pclDormancySystem = pclclient->pclDormancySystem;
	if(NULL == pclDormancySystem)
	{
		return;
	}

	CDormancyPointRewardClient *pclDormancyClient = (CDormancyPointRewardClient *)pclDormancySystem->GetDormancyPointReward();
	if(NULL == pclDormancyClient)
	{
		return;
	}

	// ���� ������ ����ũ ���
	SI32 siSelectedIndex = m_pItemListBox->GetSelectedIndex();
	SI32 siItemtypeunique = pclDormancyClient->GetItemUnique(siSelectedIndex);
	m_siSelctedUnique = siItemtypeunique;

	// �̹��� �׸���
	pclclient->pclItemManager->GetItemGImageFileIndexAndFont( m_siSelctedUnique, &m_siImageType, &m_siImageIndex );
}

void CNDormancyPointDlg::VDirectDrawToBackScreen( LPDIRECTDRAWSURFACE7 lpBackScreen, SI32 ScreenRX, SI32 ScreenRY )
{
	if ( ! IsShow() )
		return;

	if(m_siImageIndex < 0)   
		return;

	cltClient *pclclient = ( cltClient * )pclClient;
	TSpr *pSpr = pclclient->pclGImg->GetGlobalSpr( m_siImageType );

	if ( pSpr )
	{
		GP.PutSpr( pSpr ,ScreenRX + GetX() + m_pItemImage->GetX() + 10, ScreenRY + GetY() + m_pItemImage->GetY() + 2, m_siImageIndex);
	} 
}

VOID CNDormancyPointDlg::Minimi(BOOL bMini)
{
	if(m_bMini == bMini)	return;
	cltClient *pclclient = (cltClient*)pclClient;
	m_bMini = bMini;
	if(m_bMini == TRUE)
	{	
		m_siOldPosX = GetX();
		m_siOldPosY	= GetY();

		m_siOldXSize = GetWidth();
		m_siOldYSize = GetHeight();

		SetMoveable(FALSE);
		SetFileName(NULL);
		
		SI32 PartyMinimizedSlot = 0;
		SI32 LetterMinimizedSlot = 0;
		SI32 HelpButtonMiniMizedSlot = 0;
		SI32 LoveLevelMiniMizedSlot = 0; 
		SI32 FamilyCookieEffect = 0;
		SI32 FamilyInfoSlot = 0;
		SI32 PrivateChatMinimizedSlot = 0;

		if( pclclient->m_pDialog[NPARTY_DLG])
			PartyMinimizedSlot = ((CNPartyDlg*)pclclient->m_pDialog[NPARTY_DLG])->GetMinimizedSlot();

		if( pclclient->m_pDialog[NLETTER_DLG])
			LetterMinimizedSlot = ((CNLetterDlg*)pclclient->m_pDialog[NLETTER_DLG])->GetMinimizedSlot();

		if(pclClient->IsCountrySwitch(Switch_FreshManHelpDialog))
		{
			if( pclclient->m_pDialog[NHELPBUTTON_DLG])
				HelpButtonMiniMizedSlot = ((CNHelpButtonDlg*)pclclient->m_pDialog[NHELPBUTTON_DLG])->GetMinimizedSlot();
		}

		if ( pclclient->m_pDialog[NMARRIAGELOVELEVEL_DLG] )
			LoveLevelMiniMizedSlot = ((CNMarriageLoveLevelDlg*)pclclient->m_pDialog[NMARRIAGELOVELEVEL_DLG])->GetMinimizedSlot();

		if ( pclclient->m_pDialog[NFAMILYCOOKIELEVEL_DLG] )
			FamilyCookieEffect = ((CNFamilyCookieDlg*)pclclient->m_pDialog[NFAMILYCOOKIELEVEL_DLG])->GetMinimizedSlot();

		if ( pclclient->m_pDialog[NFAMILYINFO_DLG] )
			FamilyInfoSlot = ((CNFamilyInfoDlg*)pclclient->m_pDialog[NFAMILYINFO_DLG])->GetMinimizedSlot();

		if( pclclient->m_pNPrivateChatDlgMgr)
			PrivateChatMinimizedSlot = pclclient->m_pNPrivateChatDlgMgr->GetMinimizedSlot();

		// �� ������ ã�´�.
		for(SI32 i = 1; i <= MAX_MINIMIZE_SLOT; i++)
		{
			if( i == PartyMinimizedSlot || i == FamilyInfoSlot || i == LetterMinimizedSlot || i == HelpButtonMiniMizedSlot || i == LoveLevelMiniMizedSlot || i == FamilyCookieEffect || i == PrivateChatMinimizedSlot )
				continue;
			m_siMinimizedSlot = i;
			break;
		}

		// ���Կ� ���� x ��ǥ�� ������ �ش�.
		SetDialogPos( pclclient->GetScreenXSize() - 40 - (m_siMinimizedSlot -1) * 45 , 215, 34, 34 );

		//  ���̾�α� title
		SetTitle(TEXT(""));
		//	������ �̹���
		m_pItemImage->Show(FALSE);
		//	������ ����Ʈ
		m_pItemListBox->Show(FALSE);
		//	���� ��ư
		m_pBuyButton->Show(FALSE);
		//	���� ��ư
		m_pCloseButton->Show(FALSE);
		//	����
		m_pTextStatic->Show(FALSE);
		//  �޸� ����Ʈ ����
		m_pPointInfoEdit->Show(FALSE);
		//  �̴Ϲ�
		m_pMinimiButton->Show(TRUE);
	}
	else
	{
		SetMoveable(TRUE);
		SetDialogPos( m_siOldPosX, m_siOldPosY, m_siOldXSize, m_siOldYSize );
		SetFileName(m_szTempBgImgFilePath);

		//  ���̾�α� title
		SetTitle(m_szTempTitle);
		//	������ �̹���
		m_pItemImage->Show(TRUE);
		//	������ ����Ʈ
		m_pItemListBox->Show(TRUE);
		//	���� ��ư
		m_pBuyButton->Show(TRUE);
		//	���� ��ư
		m_pCloseButton->Show(TRUE);
		//	����
		m_pTextStatic->Show(TRUE);
		//  �޸� ����Ʈ ����
		m_pPointInfoEdit->Show(TRUE);
		//  �̴Ϲ�
		m_pMinimiButton->Show(FALSE);
	}
}

// ����Ʈ ������ ��� ��������
VOID CNDormancyPointDlg::ShowPointItemList()
{
	cltClient *pclclient = (cltClient *)pclClient;

	CDormancySystem *pclDormancySystem = pclclient->pclDormancySystem;
	if(NULL == pclDormancySystem)
	{
		return;
	}

	CDormancyPointRewardClient *pclDormancyClient = (CDormancyPointRewardClient *)pclDormancySystem->GetDormancyPointReward();
	if(NULL == pclDormancyClient)
	{
		return;
	}

	// ����Ʈ �ڽ� ������
	stListBoxItemData itemdata;

	cltItemInfo *pclItemInfo = NULL;
	TCHAR	pszPoint[MAX_PATH] = {0,};

	for(SI32 i = 0 ; i < pclDormancyClient->GetItemCount() ; i++)
	{
		pclItemInfo = pclDormancyClient->GetItemInfo(i);
		if( NULL != pclItemInfo)
		{
			ZeroMemory(pszPoint, MAX_PATH * sizeof(TCHAR) );
			_itot(pclDormancyClient->GetItemPoint(i), pszPoint, 10);
			
			itemdata.Init();
			itemdata.Set(0, (TCHAR*)pclItemInfo->GetName());
			itemdata.Set(1, pszPoint);
			m_pItemListBox->AddItem( &itemdata );
		}
	}
	return;
}

//  �޸� ���� ����
VOID CNDormancyPointDlg::RefreshDormancyInfo()
{
	cltClient *pclclient = (cltClient *)pclClient;

	cltCharClient *pclChar = pclclient->pclCM->GetCharClient(1);
	if(NULL == pclChar)
		return;

	CDormancyInfo &rclDormancyInfo =  pclChar->pclCI->clDormancyInfo;
	_SYSTEMTIME *pTime = rclDormancyInfo.GetStartedDate();
	if( NULL == pTime)
		return;
	_SYSTEMTIME ExpirationTime;
	TimeAddDate(pTime, CDormancyPointReward::DURATIONDATE, &ExpirationTime);
	
	TCHAR szText[MAX_PATH] = {0,};
	TCHAR szTextPoint[MAX_PATH] = {0,};
	TCHAR szTextEnd[MAX_PATH] = {0,};
	TCHAR szPoint[MAX_PATH] = {0,};
	TCHAR szEndYear[MAX_PATH] = {0,};
	TCHAR szEndMonth[MAX_PATH] = {0,};
	TCHAR szEndDate[MAX_PATH] = {0,};
	
	StringCchPrintf(szPoint, MAX_PATH, TEXT("%d"), pclChar->pclCI->clDormancyInfo.GetDormancyPoint());
	StringCchPrintf(szEndYear, MAX_PATH, TEXT("%d"), ExpirationTime.wYear);
	StringCchPrintf(szEndMonth, MAX_PATH, TEXT("%d"), ExpirationTime.wMonth);
	StringCchPrintf(szEndDate, MAX_PATH, TEXT("%d"), ExpirationTime.wDay);

	NTCHARString128 kTextPoint( GetTxtFromMgr(40080) );
	NTCHARString128 kTextEndDate( GetTxtFromMgr(40081) );

	kTextPoint.Replace(TEXT("#point#"),szPoint);
	kTextEndDate.Replace(TEXT("#year#"),szEndYear);
	kTextEndDate.Replace(TEXT("#month#"),szEndMonth);
	kTextEndDate.Replace(TEXT("#day#"),szEndDate);

	StringCchCopy(szTextPoint, MAX_PATH,  kTextPoint);
	StringCchCopy(szTextEnd, MAX_PATH,  kTextEndDate);
	StringCchPrintf(szText, MAX_PATH, TEXT("%s \r\n%s"),szTextPoint, szTextEnd);

	m_pPointInfoEdit->SetText(szText);

	return;
}

//	�޼��� �ڽ� ó��
void CNDormancyPointDlg::RetMsgBox(bool bRetValue, SI16 siMsgIndex, BYTE *pData, SI16 siDataLen  )
{
	cltClient *pClient = (cltClient*)pclClient;

	if(pClient == NULL)
		return;

	switch(siMsgIndex)
	{
	case 0:	//	�ݾ� üũ
		{
			if(bRetValue)	//	 clicked ok
			{
				// ���� ����ũ
				/*SI32 siSelectedUnique = (SI32*)pData;

				cltClient *pclclient = (cltClient *)pclClient;

				CDormancySystem *pclDormancySystem = pclclient->pclDormancySystem;
				if(NULL == pclDormancySystem)
				{
					return;
				}

				CDormancyPointRewardClient *pclDormancyClient = (CDormancyPointRewardClient *)pclDormancySystem->GetDormancyPointReward();
				if(NULL == pclDormancyClient)
				{
					return;
				}

				pclDormancyClient->BuyPointItemRequest(siSelectedUnique);*/

				////	���� �ݾ�
				//GMONEY siMyMoney	= pclClient->pclCM->CR[1]->pclCI->clIP.GetMoney();

				////	 �÷��� �ݾ�
				//SI32 siNpcrate		= pclClient->pclItemManager->clItemStatistic.siNPCPriceRate;
				//GMONEY siNeedMoney	= siNpcrate * 10;

				//if(siMyMoney >= siNeedMoney)
				//{
				//	//	 �÷��� �� �ݾ��� �ִ�. ���� ������ �����Ѵ�.
				//	pClient->GetGawiBawiBoMgr()->NextSteps();
				//}
				//else		
				//{
				//	// �÷��� �ݾ��� ���ڸ���.
				//	TCHAR*	pTitle	= GetTxtFromMgr(10345);
				//	TCHAR*	pBody	= GetTxtFromMgr(1261);
				//	pClient->m_pDialog[NOTIFYMSG_DLG]->SetText(pTitle, pBody);

				//	pClient->GetGawiBawiBoMgr()->GiveUp();
				//}
			}
			else			//	 clicked cancel
			{
				/*pClient->GetGawiBawiBoMgr()->GiveUp();*/
			}
		}
		break;
	}
}