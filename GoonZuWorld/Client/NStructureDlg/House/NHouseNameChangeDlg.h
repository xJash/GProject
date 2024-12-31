#pragma once
// NDormancyPointDlg.h: interface for the NDormancyPointDlg class.
//
//////////////////////////////////////////////////////////////////////
/* ==========================================================================
Ŭ���� :		CNHouseNameChangeDlg

�ۼ��� :		09/011/20
�ۼ��� :		�ڱ���

��  �� :		â�� �̸� ����
��  �� :		
������� :		����

�����۾� :		

========================================================================*/
#include "Resource.h"

#include "../../InterfaceMgr/DialogController.h"

class CButton;
class CStatic;

class CNHouseNameChangeDlg  : public CDialogController
{
public:
	CNHouseNameChangeDlg();
	~CNHouseNameChangeDlg();

	static VOID CALLBACK	StaticCNHouseNameChangeProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	VOID CALLBACK			NHouseNameChangeDlgProc(UINT nEvent, int nControlID, CControllerObj* pControl );
	VOID Create();

	VOID Destroy();
	
	VOID SetVillageUnique(SI32 siVillageUnique);
	VOID SetHouseUnitIndex(SI32 siHouseUnitIndex);
	VOID SetOldHouseName(TCHAR *pszOldHouseName);

	VOID RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );
private:
	InterfaceFactory m_InterfaceFactory;
	
	//	�����ϱ� ��ư
	CButton		*m_pChangeButton;
	//	����ϱ� ��ư
	CButton		*m_pCancelButton;
	
	CStatic		*m_pTextStatic;
	CStatic		*m_pText2Static;

	//	���� �̸�
	CEdit		*m_pOldNameEdit;
	//	���ο� �̸�
	CEdit		*m_pNewNameEdit;

	// ���� ����ũ
	SI32		m_siVillageUnique;
	// â�� ���� �ε���
	SI32		m_siHouseUnitIndex;
};
