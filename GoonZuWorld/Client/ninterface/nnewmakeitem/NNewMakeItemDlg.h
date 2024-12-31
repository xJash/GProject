// MakeItemDlg.h: interface for the CNewMakeItemDlg class.
//
//////////////////////////////////////////////////////////////////////
/* ==========================================================================
	Ŭ���� :		CNNewMakeItemDlg

	�ۼ��� :		06/01/31
	�ۼ��� :		���¾�

	��  �� :		
	                

	��  �� :		
	������� :		����

	�����۾� :		

   ========================================================================*/


#pragma once
#include <Directives.h>
#include <stdio.h>

#include "..\..\..\Resource.h"
#include "../../Client/client.h"
#include "../../InterfaceMgr/DialogController.h"
#include "NNewMakeChild.h"
#include "NNewEnchantChild.h"
#include "NItemRepair.h"

class CListView;
class CStatic;
class CEdit;
class CButton;
class CComboBox;
class CNNewMakeChild;
class CNNewEnchantChild;

class CNewMakeItemDlg  : public CDialogController
{
public:
	CNewMakeItemDlg();
	 ~CNewMakeItemDlg();

	void					Create();	
	static void CALLBACK	StatiCNewMakeItemDlgProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void CALLBACK			NNewMakeItemDlgProc(UINT nEvent, int nControlID, CControllerObj* pControl);

	CNNewMakeChild *NewMakeTab;
	CNNewEnchantChild *NewEnchantTab;
	NItemRepairDlg *NewItemRepair;

	void ShowMakeTab();
	void ShowEnchantTab();
	void ShowRepairTab();

	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );
	void CloseDialog();

private:
	InterfaceFactory m_InterfaceFactory;

};

// �޽��� �ڽ� ���̵�
enum {
	MSGBOX_ID_CHANGEENCHANT = 0
};

typedef struct _tagChangeEnchantMsgPara
{
	SI16	siUnique;
	SI16	siElementIndex;
	SI16	siEnchantType;

} stChangeEnchantMsgPara;
