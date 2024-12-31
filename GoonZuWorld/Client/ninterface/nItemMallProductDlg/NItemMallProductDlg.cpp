
#include "NItemMallProductDlg.h"

#include "../../Interface/ErrorMsgDlg/ErrorMsgDlg.h"

#include "Char/CharCommon/Char-Common.h"
#include "Char/CharManager/CharManager.h"

#include "../../CommonLogic/MsgType-Person.h"
#include "../../Client/Client.h"

#include "../../InterfaceMgr/InterfaceFile.h"
#include "../../InterfaceMgr/InterfaceMgr.h"
#include "../NSoundOnOffDlg/NSoundOnOffDlg.h"


#include "NDate.h"

CNItemMallProductDlg::CNItemMallProductDlg()
{	
	Initialize();
}

CNItemMallProductDlg::~CNItemMallProductDlg()
{
	Destroy();
}


void CNItemMallProductDlg::Initialize()
{

	m_ItemMallProductList.clear();
	m_ItemMallProductListItr = m_ItemMallProductList.end();
	
	m_siCurrentPage  = 1;
	m_siMaxPage = 0;

	for( SI16 i = 0 ; i < MAX_ITEMMALL_ITEM_PER_PAGE; i++ )
	{
		m_siImageType[i] = -1;
		m_siImageIndex[i] = -1;
	}

}

void CNItemMallProductDlg::Destroy()
{
	


}

void CNItemMallProductDlg::Create()
{
	if ( !IsCreate() )
	{
		CInterfaceFile file;

		file.LoadFile(TEXT("NInterface/Data/NItemMallProductDlg/DLG_NItemMallProduct.ddf"));
		file.CreatePopupDialog( this, NITEMMALLPRODUCT_DLG , TEXT("dialog_itemMallProduct"), StaticNItemMallProductDlgProc );

		file.CreateControl( m_InterfaceFactory.CreateUserInterface( STATIC, NITEMMALLPRODUCT_STATIC_1 , this ), NITEMMALLPRODUCT_STATIC_1 ,   "statictext_NONAME1"); 
		file.CreateControl( m_InterfaceFactory.CreateUserInterface( STATIC, NITEMMALLPRODUCT_STATIC_2 , this ), NITEMMALLPRODUCT_STATIC_2 ,   "statictext_NONAME2"); 		

		file.CreateControl( m_InterfaceFactory.CreateUserInterface( IMAGESTATIC, NITEMMALLPRODUCT_IMAGE_1, this ), NITEMMALLPRODUCT_IMAGE_1, "imagestatic_NONAME1");
		file.CreateControl( m_InterfaceFactory.CreateUserInterface( IMAGESTATIC, NITEMMALLPRODUCT_IMAGE_2, this ), NITEMMALLPRODUCT_IMAGE_2, "imagestatic_NONAME2");
		file.CreateControl( m_InterfaceFactory.CreateUserInterface( IMAGESTATIC, NITEMMALLPRODUCT_IMAGE_3, this ), NITEMMALLPRODUCT_IMAGE_3, "imagestatic_NONAME3");
		file.CreateControl( m_InterfaceFactory.CreateUserInterface( IMAGESTATIC, NITEMMALLPRODUCT_IMAGE_4, this ), NITEMMALLPRODUCT_IMAGE_4, "imagestatic_NONAME4");
		file.CreateControl( m_InterfaceFactory.CreateUserInterface( IMAGESTATIC, NITEMMALLPRODUCT_IMAGE_5, this ), NITEMMALLPRODUCT_IMAGE_5, "imagestatic_NONAME5");


		file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT, NITEMMALLPRODUCT_EDIT_1 , this ), NITEMMALLPRODUCT_EDIT_1,   "editbox_NONAME1");
		file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT, NITEMMALLPRODUCT_EDIT_2 , this ), NITEMMALLPRODUCT_EDIT_2,   "editbox_NONAME2");
		file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT, NITEMMALLPRODUCT_EDIT_3 , this ), NITEMMALLPRODUCT_EDIT_3,   "editbox_NONAME3");
		file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT, NITEMMALLPRODUCT_EDIT_4 , this ), NITEMMALLPRODUCT_EDIT_4,   "editbox_NONAME4");
		file.CreateControl( m_InterfaceFactory.CreateUserInterface( EDIT, NITEMMALLPRODUCT_EDIT_5 , this ), NITEMMALLPRODUCT_EDIT_5,   "editbox_NONAME5");
		

		file.CreateControl( m_InterfaceFactory.CreateUserInterface( BUTTON, NITEMMALLPRODUCT_BUTTON_PRE, this ), NITEMMALLPRODUCT_BUTTON_PRE,   "button_NONAME1"); 	
		file.CreateControl( m_InterfaceFactory.CreateUserInterface( BUTTON, NITEMMALLPRODUCT_BUTTON_NEXT, this ), NITEMMALLPRODUCT_BUTTON_NEXT,   "button_NONAME2"); 

		file.CreateControl( m_InterfaceFactory.CreateUserInterface( STATIC, NITEMMALLPRODUCT_STATIC_PAGE , this ), NITEMMALLPRODUCT_STATIC_PAGE ,   "statictext_NONAME3"); 		
		
		m_InterfaceFactory.GetEdit(NITEMMALLPRODUCT_EDIT_1)->ShowScrollBar(false);
		m_InterfaceFactory.GetEdit(NITEMMALLPRODUCT_EDIT_2)->ShowScrollBar(false);
		m_InterfaceFactory.GetEdit(NITEMMALLPRODUCT_EDIT_3)->ShowScrollBar(false);
		m_InterfaceFactory.GetEdit(NITEMMALLPRODUCT_EDIT_4)->ShowScrollBar(false);
		m_InterfaceFactory.GetEdit(NITEMMALLPRODUCT_EDIT_5)->ShowScrollBar(false);
		
		MovePos(250,105);


		ListItemMallProduct();
		ShowItemMallProductList();
	}
	else
	{
        DeleteDialog();

	}
}

void CALLBACK CNItemMallProductDlg::StaticNItemMallProductDlgProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl)
{
	CNItemMallProductDlg *pThis = (CNItemMallProductDlg*) pControllerMgr;
	pThis->NItemMallProductDlgProc( nEvent, nControlID, pControl );
}

void CALLBACK CNItemMallProductDlg::NItemMallProductDlgProc( UINT nEvent, int nControlID, CControllerObj* pControl )
{
	switch( nControlID )
	{
	case COMMON_DIALOG_CLOSEBUTTON:
		{
			DeleteDialog();
		}
		break;
	case NITEMMALLPRODUCT_BUTTON_PRE:
		{
			if(nEvent == EVENT_BUTTON_CLICKED)
			{
				m_siCurrentPage--;
				m_siCurrentPage = max(m_siCurrentPage,1);
				ShowItemMallProductList();
			}
		}
		break;
	case NITEMMALLPRODUCT_BUTTON_NEXT:
		{
			if(nEvent == EVENT_BUTTON_CLICKED)
			{
				m_siCurrentPage++;		
				ShowItemMallProductList();
			}
		}
		break;
	}

}




void CNItemMallProductDlg::Action()
{
	// �����۸� ������ ������ ����� üũ�� ����



}


void CNItemMallProductDlg::VDirectDrawToBackScreen( LPDIRECTDRAWSURFACE7 lpBackScreen, SI32 ScreenRX, SI32 ScreenRY )
{

   	cltClient *pclclient = ( cltClient * )pclClient;

	for( SI32 i = 0 ; i < MAX_ITEMMALL_ITEM_PER_PAGE; i++ )
	{

		if(m_siImageIndex[i] < 0 || m_siImageType[i] < 0)   
			continue;

		TSpr *pSpr = pclclient->pclGImg->GetGlobalSpr( m_siImageType[i] );

		if ( pSpr )
		{
			GP.PutSpr( pSpr ,ScreenRX +  GetX() + 24,ScreenRY +  GetY() + 53 + 42 * i , m_siImageIndex[i] );
		}

	}

}


void CNItemMallProductDlg::ListItemMallProduct()
{
	
	m_ItemMallProductList.clear();

	// ����Ʈ�� �����۸� �������� ������ ���� ����
	cltPItemInfo* pclCharItem =	&pclClient->pclCM->CR[1]->pclCI->clCharItem;
	cltItem * pclItem;
	BOOL	bInserted = FALSE;

	for( SI32 i = 0; i < MAX_ITEM_PER_PERSON; i++ )
	{
		if ( IsItemMallProduct( &pclCharItem->clItem[i] ) )
		{
			m_ItemMallProductListItr = 	m_ItemMallProductList.begin();

			while( m_ItemMallProductListItr != m_ItemMallProductList.end())
			{
				pclItem = &(*m_ItemMallProductListItr);
                if(pclItem != NULL && pclItem->siUnique > 0)
				{
					// �� ��ġ�� ã�Ҵٸ�
					if( GetAlignValue(pclItem) > GetAlignValue(&pclCharItem->clItem[i]) )
					{						
						m_ItemMallProductList.insert(m_ItemMallProductListItr,pclCharItem->clItem[i]);
						bInserted = TRUE;	
						break;
					}

				}
				m_ItemMallProductListItr++;
			}
			
			if(bInserted == FALSE )
			{
				m_ItemMallProductList.insert(m_ItemMallProductListItr,pclCharItem->clItem[i]);
			}                   

			bInserted = FALSE;
		}		 
	}
}


// ���� ������ ����Ʈ�� ������ �ܺ� �̹��� , ����Ʈ �ڽ��� �ű�

void CNItemMallProductDlg::ShowItemMallProductList()
{
	cltClient* pclclient = (cltClient*)pclClient;

	// �ܺ� ��Ʈ�� �ʱ�ȭ

	m_InterfaceFactory.GetEdit(NITEMMALLPRODUCT_EDIT_1)->Clear();
	m_InterfaceFactory.GetEdit(NITEMMALLPRODUCT_EDIT_2)->Clear();
	m_InterfaceFactory.GetEdit(NITEMMALLPRODUCT_EDIT_3)->Clear();
	m_InterfaceFactory.GetEdit(NITEMMALLPRODUCT_EDIT_4)->Clear();
	m_InterfaceFactory.GetEdit(NITEMMALLPRODUCT_EDIT_5)->Clear();
	

	m_ItemMallProductListItr = m_ItemMallProductList.begin();

	SI32 UserCnt = 0;
	cltItem	 * pclItem = NULL;

	// ����Ʈ�� ũ��� ������ ũ�� ���� �� ���� ������ ����
	list<cltItem>::size_type listNum;
	listNum = m_ItemMallProductList.size();

	if( listNum <= 0) return;
	
	m_siMaxPage = (listNum -1) / MAX_ITEMMALL_ITEM_PER_PAGE + 1;

	m_siCurrentPage = min( m_siCurrentPage , m_siMaxPage );
	
	TCHAR strBuffer[256] = {'\0',};
	StringCchPrintf(strBuffer,256,TEXT("%d/%d"),m_siCurrentPage,m_siMaxPage);
	
	m_InterfaceFactory.GetStatic( NITEMMALLPRODUCT_STATIC_PAGE )->SetText(strBuffer);


    
	// ���� �������� ���� ������ ����Ʈ�� ���������� ����Ʈ Ž��
	for(SI16 i = 0; i < (m_siCurrentPage - 1) * MAX_ITEMMALL_ITEM_PER_PAGE ; i++ )
	{
		m_ItemMallProductListItr++;
	}

	SI32 ShowListCnt = 0;

	while( m_ItemMallProductListItr != m_ItemMallProductList.end() )
	{
		pclItem = &(*m_ItemMallProductListItr);
		
		// ����ó�� ��¦
		if( pclItem == NULL || pclItem->siUnique <= 0  )
		{
			m_ItemMallProductListItr++;
			continue;
		}

		// ������ �ؽ�Ʈ ���� ����

        TCHAR tmpBuffer[256] = {'\0',};
		TCHAR DestBuffer[512] = {'\0',};
		TCHAR * pItemName = (TCHAR*)pclClient->pclItemManager->GetName( pclItem->siUnique );
 		TCHAR * pSrcText = GetTxtFromMgr(5600); // �����ϴϱ� ���� ����Ű�� ���� ����.
		
		if( pclItem->CanPile(pclClient->pclItemManager) )
		{
			StringCchPrintf( DestBuffer , 512 ,"[%s] x %d  \r\n",pItemName, pclItem->siItemNum );
		}
		else
		{
			StringCchPrintf( DestBuffer , 512 ,"[%s] \r\n",pItemName);
		}
		
		// ������ ������ �Ⱓ�� ������.
		if ( pclItem->uiDateYear > 0 && pclItem->uiDateMonth > 0 && pclItem->uiDateDay > 0 && pclItem->uiDateUseDay > 0 )
		{
			pSrcText = GetTxtFromMgr(5600);
			StringCchPrintf(tmpBuffer, 256, pSrcText,pclItem->uiDateYear+2000,pclItem->uiDateMonth,pclItem->uiDateDay) ;
			StringCchCat(DestBuffer,512,tmpBuffer);

			NDate ndate;
			ndate.SetDate(pclItem->uiDateYear+2000,pclItem->uiDateMonth,pclItem->uiDateDay);
			ndate.AddDays(pclItem->uiDateUseDay);
			
			pSrcText = GetTxtFromMgr(5601) ;
			StringCchPrintf(tmpBuffer, 256, pSrcText,ndate.m_uiYear,ndate.m_uiMonth,ndate.m_uiDay);
			StringCchCat(DestBuffer, 512, tmpBuffer);

		}
		// ���� ������ �������� ���� �Ⱓ�� ������.
		else if ( pclItem->uiDateYear == 0 && pclItem->uiDateMonth == 0 && pclItem->uiDateDay == 0 && pclItem->uiDateUseDay > 0)
		{
			pSrcText = GetTxtFromMgr(5895);			
			StringCchCat(DestBuffer,512,pSrcText);

			pSrcText = GetTxtFromMgr(5658) ;
			StringCchPrintf(tmpBuffer, 256, pSrcText,pclItem->uiDateUseDay) ;
			StringCchCat(DestBuffer,512,tmpBuffer);
		}
		// ��Ÿ ������. �����̾� ���� ���.
		else
		{
			SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique(pclItem->siUnique);
			if(ref <= 0)return;

			// ������ Ÿ���� ������ ���, �ػ����� ���� ȿ���ִ� �������� �ؽ�Ʈ ǥ��
			if( pclItem->GetType(pclClient->pclItemManager) == ITEMTYPE_FOOD )
			{
				if(pclItem->siUnique == ITEMUNIQUE(3860) || pclItem->siUnique == ITEMUNIQUE(3865) || pclItem->siUnique == ITEMUNIQUE(3870))
				{
					pSrcText = GetTxtFromMgr(5607);
					// �ػ����ڴ� ���ӽð� 1�ϰ� ȿ��
					StringCchPrintf(tmpBuffer, 256, pSrcText, 1);
					StringCchCat(DestBuffer, 512, tmpBuffer);
				}
				else if(pclItem->siUnique == ITEMUNIQUE(3860) )
				{
					pSrcText = GetTxtFromMgr(5607);
					// �ػ����ڴ� ���ӽð� 1�ϰ� ȿ��
					StringCchPrintf(tmpBuffer, 256, pSrcText, 2);
					StringCchCat(DestBuffer, 512, tmpBuffer);
				}
				// ���� �����ΰ�. 
				else if(pclClient->pclItemManager->pclItemInfo[ref]->siHorseFoodSwitch > 0 )
				{
					pSrcText = GetTxtFromMgr(3534);
	
					StringCchCat(DestBuffer, 512, pSrcText);
				}
			}

			// ������ Ÿ���� ���� ��� ���� �ɷ¿� ���� �ؽ�Ʈ ǥ��
			if( pclItem->GetType(pclClient->pclItemManager) == ITEMTYPE_HEAL )
			{
				if(pclClient->pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_PREMIUM)
				{   
					// HEALEFT_PREMIUM�� ���ӽð� 1�ϰ� ȿ��
					pSrcText = GetTxtFromMgr(5607);
					StringCchPrintf( tmpBuffer , 256 , pSrcText , 1);
					StringCchCat(DestBuffer, 512, tmpBuffer);
				}
				if(pclClient->pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_COMBAT)
				{

				}
				if(pclClient->pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_DIGESTIVE )
				{
					pSrcText = GetTxtFromMgr(6046);
					StringCchCat(DestBuffer,512,pSrcText);
				}
				if(pclClient->pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_ALLDESEASE )
				{
					pSrcText = GetTxtFromMgr(6047);
					StringCchCat(DestBuffer,512,pSrcText);
				}
				if(pclClient->pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_BULLET )
				{
					pSrcText = GetTxtFromMgr(6277);					
					StringCchPrintf(tmpBuffer, 512 , pSrcText , 365);
					StringCchCat(DestBuffer,512,tmpBuffer);
				}
			}
		}
		
		m_InterfaceFactory.GetEdit(NITEMMALLPRODUCT_EDIT_1 + ShowListCnt )->SetText(DestBuffer);
	

		// �׷��� �̹��� ���� ����

		if(pclClient->pclItemManager->GetItemGImageFileIndexAndFont( pclItem->siUnique , &m_siImageType[ShowListCnt], &m_siImageIndex[ShowListCnt] ) )
		{
		}
		else
		{
			m_siImageIndex[ShowListCnt] = -1;
			m_siImageType[ShowListCnt]  = -1;
		}
       
		// ���� ����. �׸��� ȭ�鿡 ������ ������ ī��Ʈ �ϳ� ����.

		m_ItemMallProductListItr++;
		ShowListCnt++;

		if( ShowListCnt >= MAX_ITEMMALL_ITEM_PER_PAGE )
			break;

	}		

	for( i = ShowListCnt; i < MAX_ITEMMALL_ITEM_PER_PAGE ; i++ )
	{
		m_siImageIndex[i] = -1;        
		m_siImageIndex[i] = -1;
	}

}

BOOL CNItemMallProductDlg::IsItemMallProduct(cltItem* pclItem)
{

	//�����۸� �Ӽ��� ������ �Ⱓ�� ���� �����۸� �߰�//�����۸� �������̸� �Ⱓ �߰� �κ� �ƴѰ�?
	if( pclClient->pclItemManager->IsItemInfoAtb( pclItem->siUnique, ITEMINFOATB_ITEMMALL ) == true &&	
		((pclItem->uiDateYear > 0 && pclItem->uiDateMonth > 0 && pclItem->uiDateDay > 0 && pclItem->uiDateUseDay > 0 ) ||
		(pclItem->uiDateYear == 0 && pclItem->uiDateMonth == 0 && pclItem->uiDateDay == 0 && pclItem->uiDateUseDay > 0 ))
		)
	{
		return TRUE;
	}


	return FALSE;

}


SI32 CNItemMallProductDlg::GetAlignValue( cltItem* pclItem )
{
	//  ����, �Ǻ�, ����, ����� �� �켱���� ��ġ�� ������.
	if(pclItem->GetType(pclClient->pclItemManager) == ITEMTYPE_HAT )
	{
		if(pclItem->uiDateYear > 0 && pclItem->uiDateMonth > 0 && pclItem->uiDateDay > 0 && pclItem->uiDateUseDay > 0 ) 
		{
			return 100;
		}
		else if(pclItem->uiDateYear == 0 && pclItem->uiDateMonth == 0 && pclItem->uiDateDay == 0 && pclItem->uiDateUseDay > 0 )
		{
			return 10100;
		}
		else
		{
			return 20100;
		}
	}
	else if(pclItem->GetType(pclClient->pclItemManager) == ITEMTYPE_DRESS)
	{
		if(pclItem->uiDateYear > 0 && pclItem->uiDateMonth > 0 && pclItem->uiDateDay > 0 && pclItem->uiDateUseDay > 0 ) 
		{
			return 200;
		}
		else if(pclItem->uiDateYear == 0 && pclItem->uiDateMonth == 0 && pclItem->uiDateDay == 0 && pclItem->uiDateUseDay > 0 )
		{
			return 10200;
		}
		else
		{
			return 20200;
		}
	}
	else if(pclItem->GetType(pclClient->pclItemManager) == ITEMTYPE_MANTLE)
	{
		if(pclItem->uiDateYear > 0 && pclItem->uiDateMonth > 0 && pclItem->uiDateDay > 0 && pclItem->uiDateUseDay > 0 ) 
		{
			return 250;
		}
		else if(pclItem->uiDateYear == 0 && pclItem->uiDateMonth == 0 && pclItem->uiDateDay == 0 && pclItem->uiDateUseDay > 0 )
		{
			return 10250;
		}
		else
		{
			return 20250;
		}
	}
	else if(pclItem->GetType(pclClient->pclItemManager) == ITEMTYPE_NECK)
	{
		if(pclItem->uiDateYear > 0 && pclItem->uiDateMonth > 0 && pclItem->uiDateDay > 0 && pclItem->uiDateUseDay > 0 ) 
		{
			return 300;
		}
		else if(pclItem->uiDateYear == 0 && pclItem->uiDateMonth == 0 && pclItem->uiDateDay == 0 && pclItem->uiDateUseDay > 0 )
		{
			return 10300;
		}
		else
		{
			return 20300;
		}
	}

	// �׹��� �Ⱓ�� �������� �켱������ ������.
	if(pclItem->uiDateYear > 0 && pclItem->uiDateMonth > 0 && pclItem->uiDateDay > 0 && pclItem->uiDateUseDay > 0 ) 
	{
		return 400;
	}
	else if(pclItem->uiDateYear == 0 && pclItem->uiDateMonth == 0 && pclItem->uiDateDay == 0 && pclItem->uiDateUseDay > 0 )
	{
		return 10400;
	}
	
	

	// ����� �켱������ ������.
	if( pclItem->GetType( pclClient->pclItemManager ) == ITEMTYPE_HEAL )
	{
        return 20500;		
	}
	// ���ķ��� �켱������ ������.
	else if( pclItem->GetType( pclClient->pclItemManager ) == ITEMTYPE_FOOD  )
	{
		return 20600;		
	}
	// �ٴ� ���ķ��� �켱������ ������.
	else if( pclItem->GetType( pclClient->pclItemManager ) == ITEMTYPE_SEAFOOD  )
	{
		return 20700;		
	}
	// �������� �켱������ ������.
	else if( pclItem->GetType( pclClient->pclItemManager ) == ITEMTYPE_ANIMAL )
	{
		return 20800;		
	}
	// Ƽ�Ϸ��� �켱������ ������.
	else if( pclItem->GetType( pclClient->pclItemManager ) == ITEMTYPE_TICKET )
	{
		return 20900;		
	}
	

	return 30000;
}


