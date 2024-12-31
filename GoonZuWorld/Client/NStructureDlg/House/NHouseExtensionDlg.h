#pragma once
// NDormancyPointDlg.h: interface for the NDormancyPointDlg class.
//
//////////////////////////////////////////////////////////////////////
/* ==========================================================================
Ŭ���� :		CNHouseExtensionDlg

�ۼ��� :		09/011/20
�ۼ��� :		�ڱ���

��  �� :		â�� �Ⱓ ����
��  �� :		
������� :		����

�����۾� :		

========================================================================*/
#include "Resource.h"

#include "../../InterfaceMgr/DialogController.h"

class CButton;
class CStatic;

class CNHouseExtensionDlg  : public CDialogController
{
public:
	CNHouseExtensionDlg();
	~CNHouseExtensionDlg();

	static VOID CALLBACK	StaticCNHouseExtensionProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	VOID CALLBACK			NHouseExtensionDlgProc(UINT nEvent, int nControlID, CControllerObj* pControl );
	VOID Create();

	VOID Destroy();
	
	// �Ӵ� ���� 
	VOID SetExtensionInfoText(TCHAR* pszText);
	
	VOID SetVillageUnique(SI32 siVillageUnique);
	VOID SetHouseUnitIndex(SI32 siHouseUnitIndex);

private:
	InterfaceFactory m_InterfaceFactory;
	
	//	�� ��ư
	CButton		*m_pYesButton;
	//	�ƴϿ� ��ư
	CButton		*m_pNoButton;
	//	�Ӵ� ����
	CStatic		*m_pContractStatic;
	//	����
	CStatic		*m_pTextStatic;
	CStatic		*m_pContractStaticLine;
	CStatic		*m_pTextStaticLine;

	// ���� ����ũ
	SI32		m_siVillageUnique;
	// â�� ���� �ε���
	SI32		m_siHouseUnitIndex;
};
