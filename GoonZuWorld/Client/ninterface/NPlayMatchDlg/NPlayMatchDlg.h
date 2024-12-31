/* ==========================================================================
	Ŭ���� :		NPlayMatchDlg

	�ۼ��� :		05/07/22
	�ۼ��� :		���뷡
	
	������� :		����

	�����۾� :		

   ========================================================================*/
//#if defined(__LEON_NCHARSTATUS__) && defined(_DEBUG)

#pragma once

#include <directives.h>

#include "CommonHeader.h"
#include "../../InterfaceMgr/DialogController.h"

class CButton;
class CCheckBox;
class CComboBox;
class CEdit;
class CImageStatic;
class CList;
class CRadioButton;
class CStatic;

class NPlayMatchDlg : public CDialogController
{
public:


	CStatic     		*m_pNNPCMenuStatic1;
	CStatic     		*m_pNNPCMenuStatic2;

	CButton 			*m_pButton_blackarmy_apply;
	CButton 			*m_pButton_blackarmy_mvp;

	CButton				*m_pButton_Dungeon;
	CButton				*m_pButton_Battle;

	CButton				*m_pButton_HuntingMapInfo;	// ���� ����� ����
	CButton				*m_pButton_BattleGuildSet;	// ����� ������ ��û.

	NPlayMatchDlg();
	~NPlayMatchDlg();

	void Create();
	//void RetMsgBox( bool RetValue, SI16 MsgIndex, char *pData, SI16 DataLen );

	static void CALLBACK NPlayMatchStaticProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void CALLBACK NPlayMatchProc( UINT nEvent, int nControlID, CControllerObj* pControl );

	void Close();
	void SetNPCText(TCHAR *text);

};

//#endif
