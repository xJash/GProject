// ���� ���� �⺻
#pragma once 

#include "../Client/InterfaceMgr/DialogController.h"

#include "../CommonLogic/House/House.h"

class	CHouseUnitBuffer;
class	cltHorse;

class CButton;
class CListView;
class CEdit;
class CStatic;

class CNHouseUserItemDlg;
class CNHouseUserHorseDlg;
class CNHouseUserSecondhandDlg;
class CNHouseUserManagementDlg;
class CNHouseUserNewManagementDlg;

struct stHouseUnitData;

class CNHouseUserInfoBaseDlg : public CDialogController
{
public:

	CNHouseUserInfoBaseDlg();
	~CNHouseUserInfoBaseDlg();

	void Create();
	void Action();

	static void CALLBACK StaticCallBackDialogNHouseUserInfoBaseDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
	void CALLBACK CallBackDialogNHouseUserInfoBaseDlg( UINT nEvent, int nControlID, CControllerObj* pControl );

	bool	Pop( stHouseUnitData * pHouseUnitData );		// ������ �������� �Լ�
	void	SetPersonItemInfo(cltPItemInfo* pPersonItemInfo);	
	void	SetHouseUserInfoBase(cltHouseUnit *pclHouseUnit, cltPSkillInfo* pclskill, SI32 si32VillageIndex, SI32 si32HouseUnitSlot );
	void	ShowMakeItemFromUsedGoodsItem(cltItem* pcltItem);
	
	// ���� ���� �ٽ� �ʱ�ȭ(�׳� â����� �����ش�)
	void	InitHouse();

	void	SetButtonTextColor(SI32 Index);

	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );

	CNHouseUserNewManagementDlg* GetNHouseUserNewManagementDlg();
private:

	SI32						m_siTimerIndex;
	CHouseUnitBuffer			*m_pHouseUnitBuffer;

	cltPItemInfo				*m_pPersonItemInfo;
	SI32						m_siMag;
	cltHouseUnit				*m_pclHouseUnit;
	cltPSkillInfo				*m_pclPersonSkillInfo;	// Person�� ��ų ����. 

	CButton*	m_pButton[4];	// �������

	CNHouseUserItemDlg*			m_pNHouseUserItemDlg;
	CNHouseUserHorseDlg*		m_pNHouseUserHorseDlg;
	CNHouseUserSecondhandDlg*	m_pNHouseUserSecondhandDlg;
	CNHouseUserManagementDlg*	m_pNHouseUserManagement;
	CNHouseUserNewManagementDlg*m_pNHouseUserNewManagement;
};