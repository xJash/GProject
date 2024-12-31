#pragma once 

#include "../Client/InterfaceMgr/DialogController.h"
#include "../Client/Interface/HouseUnit/HouseUnitBaseInfo.h"
#include "../CommonLogic/House/House.h"


class CEdit;
class CStatic;
class CButton;
class CComboBox;


class CHouseUnitBuffer;

class CNHouseUserShipDlg : public CDialogController
{
public:

	CNHouseUserShipDlg();
	~CNHouseUserShipDlg();

	void Create( CControllerMgr *pParent );
	void Show();
	void Hide();
	void Action();
	void RetMsgBox( bool RetValue, SI16 MsgIndex, char *pData, SI16 DataLen );

	static void CALLBACK StaticCallBackDialogNHouseUserShipDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
	void CALLBACK CallBackDialogNHouseUserShipDlg( UINT nEvent, int nControlID, CControllerObj* pControl );

	void EnableButton(CButton* pButton, BOOL Flag);	// ��ư Ȱ��ȭ ��Ȱ��ȭ
	//	void SetHouseUnitBuffer(CHouseUnitBuffer* pHouseUnitBuffer);
	void SetHouseUserItem(cltHouseUnit *pclHouseUnit);
	void SetHousePositionInfo(SI32 siCurrentVillageIndex, SI32 siCurrentHouseIndex);

	bool IsShipDataChanged();
	void LoadShipData();

public:

	CHouseUnitBuffer*	m_pHouseUnitBuffer;
	cltHouseUnit*		m_pclHouseUnit;
	SI32				m_siCurrentVillageIndex;
	SI32				m_siCurrentHouseIndex;

	cltShip						*m_pclHouseUnitShip;
	bool						m_bShipBuildingCreated;
	SI16						m_siShipBuildingLevel;
	SI32						m_siCurrentShipKindMake;
	SI32						m_siCurrentShipStepMake;
	SI32						m_siCurrentShipStepMakeDateVary;

	CStatic*	m_pStatic[3];	// 2: ������ �̹���
	CComboBox*	m_pCombo;	// ������
	CEdit*		m_pEdit;
	CButton*	m_pButton[4]; // 0 : ������ ���� 1: �� �����ϱ� 2: �� �����ϱ� 3: �� �������

};

