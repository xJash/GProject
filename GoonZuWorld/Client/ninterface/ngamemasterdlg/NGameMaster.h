/* ==========================================================================
Ŭ���� :		cltNGameMaster

�ۼ��� :		05/10/31
�ۼ��� :		�ֿ���

������� :		����

�����۾� :		

========================================================================*/
//#if defined(__LEON_NCHARSTATUS__) && defined(_DEBUG)

#pragma once

#include <directives.h>

#include "CommonHeader.h"
#include "../../InterfaceMgr/DialogController.h"
#include "../common/Item/ItemCommon/cltItem.h"

class cltCharClient;
class cltParametaBox;
class cltSummonScroll;
class cltCharManager;
class cltItem;

class CButton;
class CCheckBox;
class CComboBox;
class CEdit;
class CImageStatic;
class CList;
class CRadioButton;
class CStatic;
class COutLine;
class CGMList;

// ��� ��� â
class CNGameMaster : public CDialogController
{
public:
	//CList			*m_listbox_GM_order;
	CGMList			*m_listbox_GM_order;
	CEdit			*m_editbox_GM_info;
	CEdit			*m_editbox_GM_txt;

	CStatic			*m_pStatic[9];		// ĳ��id, ����, ��ǰ������, ǰ��, ǰ��, ���, �������, ������̸�, ��Ÿ
	CComboBox		*m_pComboBox[6];	// ����, ǰ��, ǰ��, ���, �������, �����
	CEdit			*m_pEdit[2];		// ĳ��id, ��Ÿ
    
	CButton			*m_button_ok;
	CButton			*m_button_cancel;

	SI32			m_arrItemTypeIndex[MAX_ITEMTYPE_NUMBER];

	CNGameMaster();
	~CNGameMaster();

	void Create();

	static void CALLBACK NGameMasterStaticProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void CALLBACK NGameMasterStatusProc( UINT nEvent, int nControlID, CControllerObj* pControl );

	void Show();
	void Hide();
	void Action();
	void AddGMList();
	void AddMonsters();
	void AddVillageList();
	void AddHuntmaps();
	void AddSkills();

	void SetItemTypeInComboBox();
	BOOL ShowItemListInComboBox(CComboBox* pComboBox, SI32 typeindex);

	void SendGMOrder();

};

class CGMList : public CList
{
public:

	CGMList( CControllerMgr *pParent ) : CList( pParent ) {}
	bool HandleKeyboard( UINT uMsg, WPARAM &wParam, LPARAM &lParam );

};


//#endif
