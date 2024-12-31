//---------------------------------
// 2003/6/18 ���°�
//---------------------------------
#include <CommonLogic.h>
#include "Char\CharCommon\Char-Common.h"

#include "..\..\Common\Util\Control\Control.h"

#include "..\..\Resource.h"

#include "Market.h"
#include "Control.h"
#include "..\..\Client\FontManager\FontManager.h"
#include "..\..\Client\Music\Music.h"
#include <JYLibFunction.h>

//--------------------------------------
// Common
//--------------------------------------
#include "PersonInfo.h"
#include "Char\CharManager\CharManager.h"

extern cltCommonLogic* pclClient;


// ���� â�� �����Ѵ�. 
/*BOOL cltMarketManager::SetMarketStorage(HWND hDlg, SI32 id)
{
	LVITEM LI;
	SI32 i;
	char buffer[256];

	// �̹��� ����Ʈ�� ����Ʈ �� ��Ʈ�ѿ� ����Ѵ�. 
	HWND hwnd = GetDlgItem(hDlg, IDC_LIST_MARKETSTORAGE);

	// �̹��� ����Ʈ�� ����Ʈ ��� ����Ǿ� ���� ������, 
	// ���� ��Ų��. 
	if(ImageListConnectedToStorageSwitch == FALSE)
	{
		ImageListConnectedToStorageSwitch = TRUE;

		if(pclImageList)
		{
			pclImageList->ConnectToListView(hwnd, LVSIL_NORMAL);
		}
	}

	// �̹� ������Ʈ �Ǿ� �ִٸ� �߰��� ������Ʈ ���� �ʴ´�. 
	if(clOldAccount.IsSame(&pclCM->CR[id]->pclCI->clMarket.clInfo) == TRUE)
	{
		return TRUE;
	}
	else
	{
		clOldAccount.Set(&pclCM->CR[id]->pclCI->clMarket.clInfo);
	}

	// ������ �׸��� ��� �����Ѵ�. 
	ListView_DeleteAllItems(hwnd);

	// ����Ʈ �� ��Ʈ�ѿ� �׸��� �߰��Ѵ�. 
	LI.mask=LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
	LI.state=0;
	LI.stateMask=0;
	
	SI32 index = 0;
	for(i = 0;i < MAX_ORDER_PER_PERSON;i++)
	{
		cltItem* pclitem = &pclCM->CR[id]->pclCI->clMarket.clInfo.clItem[i];

		if(pclitem->siUnique)
		{

			LI.iImage	= pclitem->GetImage(pclClient->pclItemManager);
			LI.iSubItem	= 0;
			LI.iItem	= index;
			
			char itemname[128];
			if(pclitem->GetFullName(pclClient->pclItemManager, itemname) == true)
			{
				
				sprintf(buffer, "%s %d��", itemname, pclitem->GetItemNum());
				LI.pszText	= buffer;
				LI.lParam	= i;
				index++;
				
				ListView_InsertItem(hwnd, &LI);
			}
		}
	}

	return TRUE;

}*/

/*BOOL cltMarketManager::SetInventory(HWND hDlg, SI32 id)
{
//	LVITEM LI;
//	SI32 i;
//	char buffer[256];
	
	if(id <= 0)return FALSE;


	// ĳ������ �κ��丮�� ã�´�. 
	cltPItemInfo* pcliteminfo = &pclCM->CR[id]->pclCI->clCharItem;

	// ���� �κ��丮�� ���ο� �κ��丮�� ������, 
	if(clOldPersonItemInfo.IsSame( pcliteminfo, true) == TRUE)
	{
		return FALSE;
	}
	else
	{
		// ������ �κ��丮�� ����Ѵ�. �Ŀ� �κ��丮�� ����Ǿ����� Ȯ���ؾ� �ϱ� �����̴�. 
		clOldPersonItemInfo.Set(pcliteminfo);
	}

	if(ImageListConnectedSwitch == FALSE)
	{
		if(SetInventoryInListView(pclClient->pclItemManager, hDlg, IDC_LIST_MARKETINV, pclImageList, pcliteminfo) == TRUE)
		{
			ImageListConnectedSwitch = TRUE;
		}
	}
	else 
	{
		SetInventoryInListView(pclClient->pclItemManager, hDlg, IDC_LIST_MARKETINV, NULL, pcliteminfo);
	}

	return TRUE;

}*/

//�ֹ� ������ �����ش�. 
/*BOOL cltMarketManager::ShowOrderList(HWND hDlg, SI32 id)
{
	SI32 i;
	char buffer[256];

	// ����Ʈ �ڽ��� �ʱ�ȭ�Ѵ�. 
	SendDlgItemMessage(hDlg, IDC_LIST_MARKETSELLORDER, LB_RESETCONTENT, 0, 0);

	for(i = 0;i < MAX_ORDER_PER_PERSON;i++)
	{
		cltMarketAccount* pclaccount = &pclCM->CR[id]->pclCI->clMarket.clInfo;

		if(pclaccount->clItem[i].siUnique)
		{
			cltItem clitem;
			clitem.Set(&pclaccount->clItem[i]);

			char itemname[128];
			if(clitem.GetFullName(pclClient->pclItemManager, itemname) == true)
			{
				sprintf(buffer, "%s -%d��  ���� %I64d��",itemname, clitem.siItemNum, pclaccount->clMoney[i].itMoney); 
				SendDlgItemMessage(hDlg, IDC_LIST_MARKETSELLORDER, LB_ADDSTRING, 0, (LPARAM)buffer);
			}
		}
	}


	return TRUE;
}*/

//���� ��ư�� Ȱ��ȭ/��Ȱ��ȭ ��Ų��.
BOOL cltMarketManager::EnableSellButton(HWND hDlg, SI32 dlgItem, BOOL mode, BOOL letmode)
{
	// ���� � �����̳Ŀ� ���� ���� ������ �����ϴ� ���(letmode == TRUE)�� �ƴϸ�, 
	if(letmode == FALSE)
	{
		if(SellButtonEnableSwitch == mode)return FALSE;
	}

	SellButtonEnableSwitch = mode;
	HWND hwnd = GetDlgItem(hDlg, dlgItem);
	EnableWindow(hwnd, mode);

	return TRUE;
}

//ȸ�� ��ư�� Ȱ��ȭ/��Ȱ��ȭ ��Ų��.
BOOL cltMarketManager::EnableGetFromMarketButton(HWND hDlg, SI32 dlgItem, BOOL mode, BOOL letmode)
{
	// ���� � �����̳Ŀ� ���� ���� ������ �����ϴ� ���(letmode == TRUE)�� �ƴϸ�, 
	if(letmode == FALSE)
	{
		if(GetFromMarketButtonEnableSwitch == mode)return FALSE;
	}

	GetFromMarketButtonEnableSwitch = mode;
	HWND hwnd = GetDlgItem(hDlg, dlgItem);
	EnableWindow(hwnd, mode);

	return TRUE;
}




// ������ ������ �����ش�.
BOOL cltMarketManager::ShowFee(HWND hDlg)
{
	char buffer[256];
	float feerate = (float)clClientStrInfo.clMarketStrInfo.clFee.GetFeeRate() / 10;

	sprintf(buffer, "%3.1f%%", feerate);
	SetDlgItemText(hDlg, IDC_STATIC_MARKETFEE, buffer);

	return TRUE;
}

// ������ �����ؾ� �� �ݾ��� �����ش�. 
BOOL cltMarketManager::ShowRealFee(HWND hDlg, SI32 itemnum, SI32 price)
{
	char buffer[256];

	SI32 totalmoney = itemnum * price;

	sprintf(buffer, "%d", clClientStrInfo.clMarketStrInfo.clFee.CalcFee(totalmoney));
	SetDlgItemText(hDlg, IDC_EDIT_MARKETREALFEE, buffer);

	return TRUE;
}

// SJY
BOOL cltMarketManager::IsChangedInvItem()
{
	for ( int j = PERSONITEM_INV0; j < PERSONITEM_SUMMON1EQUIP0; ++j )
	{
		SI32 size = sizeof(cltItem);

		char* src = (char*)&m_InvItem[j];
		char* dst = (char*)&pclCM->CR[1]->pclCI->clCharItem.clItem[j];

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

void cltMarketManager::LoadInvItemData()
{
	for ( int i = PERSONITEM_INV0; i < PERSONITEM_SUMMON1EQUIP0; ++i )
	{
		m_InvItem[i].siUnique = 0 ;
		m_InvItem[i].siItemNum = 0 ;

		m_InvItem[i] = pclCM->CR[1]->pclCI->clCharItem.clItem[i];
	}

	return;
}

BOOL cltMarketManager::IsChangedStgItem()
{
	for ( int j = 0; j < MAX_ORDER_PER_PERSON; ++j )
	{
		SI32 size = sizeof(cltItem);

		char* src = (char*)&m_StgItem[j];
		char* dst = (char*)&pclCM->CR[1]->pclCI->clMarket.clInfo.clItem[j];

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

void cltMarketManager::LoadStgItemData()
{
	for ( int i = 0; i < MAX_ORDER_PER_PERSON; ++i )
	{
		m_StgItem[i].siUnique = 0 ;
		m_StgItem[i].siItemNum = 0 ;

		m_StgItem[i] = pclCM->CR[1]->pclCI->clMarket.clInfo.clItem[i];
	}

	return;
}