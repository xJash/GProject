#pragma once 

#include "../Client/InterfaceMgr/DialogController.h"
#include "../Client/Interface/HouseUnit/HouseUnitBaseInfo.h"
#include "../CommonLogic/House/House.h"

class CButton;
class CListView;
class CEdit;
class CStatic;

class cltPItemInfo;
class CHouseUnitBuffer;

class CNHouseUserItemDlg : public CDialogController
{
public:

	CNHouseUserItemDlg();
	~CNHouseUserItemDlg();

	void Create( CControllerMgr *pParent );
	void Show();
	void Hide();
	void Action();

	static void CALLBACK StaticCallBackDialogNHouseUserItemDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
	void CALLBACK CallBackDialogNHouseUserItemDlg( UINT nEvent, int nControlID, CControllerObj* pControl );

	void SetPersonItemInfo(cltPItemInfo* pPersonItemInfo);	
	void SetHouseUnitBuffer(CHouseUnitBuffer* pHouseUnitBuffer);
	void SetHousePositionInfo(SI32 siCurrentVillageIndex, SI32 siCurrentHouseIndex);
	void SetHouseUserItem(cltHouseUnit *pclHouseUnit);
    void LoadUserInventory();
	void LoadWareHouseInventory();

	bool IsWareHouseInventoryChanged();
	bool IsUserInventoryChanged();

	void InputToWareHouse();
	void OutputToWareHouse();

public:
	
	SI32			m_siUserInventorySelectedRealItemIndex;
	SI32			m_siUserInventorySelectedIndex;
	SI32			m_siWareHouseInventorySelectedIndex;
	SI32			m_siWareHouseInventorySelectedRealItemIndex;
	SI32			m_siWareHouseInputOutputItemNum;
	SI32			m_siUserInventorySelectedItemNumber;
	SI32			m_siUserWareHouseSelectedItemNumber;
	SI32			m_siCurrentVillageIndex;
	SI32			m_siCurrentHouseIndex;

	CHouseUnitBuffer			*m_pHouseUnitBuffer;

	cltPItemInfo*	m_pPersonItemInfo;
	cltHouseUnit*	m_pclHouseUnit;
	cltItem			m_clUserItem[ MAX_ITEM_PER_PERSON ];
	cltItem			m_clWareHouseItem[ MAX_HOUSEUNIT_STORAGE_ITEM_NUMBER ];
	
	CEdit*		m_pEdit;
	CStatic*	m_pStatic[3];	// 0 : ���� 1: ����ǰ 2: â��
	CButton*	m_pButton[2];	// �������
	CListView*	m_pListView[2];	// 0 : ���� �κ� 1: ���� �κ�
	
	CButton*	m_pArrangementButton;	// â�� ����
	CEdit*		m_pEditItemCount; //[�߰� : Ȳ���� 2008. 2. 20 => â�� ������ ���� ���ϰ�.]
};