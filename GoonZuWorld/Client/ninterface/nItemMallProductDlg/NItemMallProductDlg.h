/* ==========================================================================
Ŭ���� :		CNItemMallProductDlg

�ۼ��� :		06/07/10
�ۼ��� :		�迵��

������� :		�������� �����۸� �������� ������

�����۾� :		
========================================================================*/

#pragma once

#include "../../Client/client.h"
#include "../../InterfaceMgr/DialogController.h"


#define MAX_ITEMMALL_ITEM_PER_PAGE	5


class CNItemMallProductDlg : public CDialogController
{
public:

	CNItemMallProductDlg();
	~CNItemMallProductDlg();

	void Initialize();
	void Destroy();

	void Create();

	static void CALLBACK StaticNItemMallProductDlgProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void CALLBACK NItemMallProductDlgProc( UINT nEvent, int nControlID, CControllerObj* pControl );

	void Action();	
	void VDirectDrawToBackScreen( LPDIRECTDRAWSURFACE7 lpBackScreen, SI32 ScreenRX, SI32 ScreenRY );

	void ListItemMallProduct();
	void ShowItemMallProductList();

	BOOL IsItemMallProduct(cltItem* pclItem);
	SI32 GetAlignValue( cltItem* pclItem ); // ������ ���� ������ �����̵� �켱�������� ��ȯ���ִ� �Լ�
public:

	InterfaceFactory	m_InterfaceFactory;

	// ������ ������ ��� ����Ʈ		
	list< cltItem > m_ItemMallProductList;
	list< cltItem >::iterator m_ItemMallProductListItr;

	SI32 m_siCurrentPage;
	SI32 m_siMaxPage;

	SI32 m_siImageType[MAX_ITEMMALL_ITEM_PER_PAGE];
	SI32 m_siImageIndex[MAX_ITEMMALL_ITEM_PER_PAGE];

};
