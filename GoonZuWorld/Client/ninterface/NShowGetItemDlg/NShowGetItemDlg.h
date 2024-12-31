#pragma once

#include "../../InterfaceMgr/DialogController.h"
#include "../../../common/item/ItemCommon/ItemUnit.h"



class CNShowGetItemDlg : public CDialogController
{
public:
	//�迵�� ���� 2007.12.10 [20391] ������ ȹ�� UI����
	CImageStatic*	m_pImageStaticBackGround;
	CImageStatic*	m_pImageStaticItemImage;
	CStatic*		m_pStatic_itemName;
	CStatic*		m_pStatic_itemUnits;
	CStatic*		m_pStatic_itemPrice;


	CNShowGetItemDlg();
	~CNShowGetItemDlg();

	void Create();
	void Action();
	void SetItemData( cltItem* pclItem, TCHAR* ptszItemName, GMONEY gmPrice );

	static void CALLBACK StaticCallBackDialogNShowGetItem( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void CALLBACK CallBackDialogNShowGetItem( UINT nEvent, int nControlID, CControllerObj* pControl );

protected:
	enum { ADD_TO_WIDTH = 8, MAX_LIMIT_WIDTH = 90 };

	SI16	m_siCurrentFrame;		// 10���Ŀ� �Ⱥ������� ���� ..
	SI32	m_siImageType;			// ���� �̹��� ����
	SI32	m_siImageIndex;			// ���� �̹��� �ε���
	
	SI16	m_siDialogWidth;		//���̾�α� �⺻ ũ��
	SI16	m_siItemWidth;			//������ �̸� ǥ�� ��Ʈ�� �⺻ ũ��

};