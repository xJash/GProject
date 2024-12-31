// [����] ����� ����Ʈ �˸�â
#pragma once

#include "../../InterfaceMgr/DialogController.h"
#include "../../InterfaceMgr/InterfaceFile.h"

class CNQuestInfoDlg_GoingQuest;

enum QUEST_INFO_TAB
{
	QUEST_INFO_TAB_GOINGQUEST = 0	// NQUESTINFO_PARENT_BUTTON_GOINGQUEST�� �ѽ���
	,QUEST_INFO_TAB_ALLQUEST		// NQUESTINFO_PARENT_BUTTON_ALLQUEST�� �ѽ���

	,QUEST_INFO_TAB_MAX
};

enum QUEST_INFO_RETMSG
{
	QUEST_INFO_REGMSG_GOING_QUESTCANCEL	= 0
};

class CNQuestInfoDlg_Parent : public CDialogController
{
// ��������
private:
	InterfaceFactory			m_InterfaceFactory;
	CDialogController*			m_pTabDialog[QUEST_INFO_TAB_MAX];


// �Լ�����
public:
	CNQuestInfoDlg_Parent();
	~CNQuestInfoDlg_Parent();

	void Create();

	static void CALLBACK StaticQuestInfoDlg_ParentProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void CALLBACK NQuestInfoDlg_ParentProc(UINT nEvent, int nControlID, CControllerObj* pControl);

	void Action();

	void Show();
	void Hide();

	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );

private:
	void SelectTabDialog( SI32 siControllID );
	void SetTabDialogButton( CButton* pclButton, COLORREF FontColor, SI16 siWeight );


};
