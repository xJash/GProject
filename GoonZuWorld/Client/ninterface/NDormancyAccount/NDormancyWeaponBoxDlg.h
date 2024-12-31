#pragma once
// NDormancyWeaponBox.h: interface for the NDormancyWeaponBox class.
//
//////////////////////////////////////////////////////////////////////
/* ==========================================================================
Ŭ���� :		CNDormancyWeaponBoxDlg

�ۼ��� :		09/08/01
�ۼ��� :		�ڱ���

��  �� :		�޸���� ���� �ڽ�


��  �� :		
������� :		����

�����۾� :		

========================================================================*/
#include "Resource.h"

#include "../../InterfaceMgr/DialogController.h"
#include "../Client/Inventory/ItemInventoryBaseDefinition.h"

class CButton;

class CNDormancyWeaponBoxDlg  : public CDialogController
{
public:
	CNDormancyWeaponBoxDlg();
	~CNDormancyWeaponBoxDlg();

	static VOID CALLBACK	StatiCNDormancyWeaponBoxProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	VOID CALLBACK			NDormancyWeaponBoxDlgProc(UINT nEvent, int nControlID, CControllerObj* pControl );
	VOID Create();

	VOID Destroy();

	// ���� �ڽ� ����ũ ����
	VOID SetBoxInfo(SI32	siBoxUnique, SI32 siBoxPos);

	// ���� �Ϸ�
	VOID CompleteToSelectItem();

	//	������ ����
	VOID SelectItem(SI32 siControllID,CControllerObj* pControl);
private:
	const static SI32	MAX_ITEM_COUNT = 6;
	const static SI32	UNIQUE_BOX = 13354;
	InterfaceFactory m_InterfaceFactory;
	
	SI32		m_siBoxUnique;
	SI32		m_siBoxPos;

	SI32		m_siSelctedOrder;		// ���õ� ������

	//  ������ �̹��� �ε���
	SI32		m_siImageIndex[MAX_ITEM_COUNT];
	//  ������ �̹��� Ÿ��
	SI32		m_siImageType[MAX_ITEM_COUNT];
	//	������ ����Ʈ�� ��
	CListView	*m_pItemListView[MAX_ITEM_COUNT];
	//	���� ��ư
	CButton		*m_pOkButton;
	//	����
	CStatic		*m_pTextStatic;
	CEdit		*m_pTextEdit;
	//	������ �̹��� �� ���
	VOID SetItemImage();
};
