//---------------------------------
// 2003/5/17 ���°�
//---------------------------------
/* ==========================================================================
	Ŭ���� :		cltNQuestStatus

	�ۼ��� :		05/03/14
	�ۼ��� :		���뷡
	
	������� :		����

	�����۾� :		

   ========================================================================*/
//#if defined(__LEON_NCHARSTATUS__) && defined(_DEBUG)

#pragma once

#include <directives.h>

#include "CommonHeader.h"
#include "../../InterfaceMgr/DialogController.h"

#define MAX_CHARSTATUS_PAGE_NUMBER	5

#define WANTIED_ANIMAL_CHANGE_TYPE	2

#define QUESTTYPE_DAILY		-101

#define QUESTTYPE_DAILY2	100 // ���ϸ� ����Ʈ 2
#define QUESTTYPE_DAILY3	101 // ���ϸ� ����Ʈ 2

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

// ����Ʈ ���� â


class cltNQuestStatus : public CDialogController
{
public:

	CStatic			*m_pStatictext_SpecialQuest;
	CStatic			*m_pStatictext_CollectWord;
	CEdit			*m_pEditbox_SpecialExplain;
	CStatic			*m_pStatictext_CompleteCount;
	CButton			*m_pButton_Cancel_Special;
	COutLine		*m_pOutLine_SpecialQuest;
	

	CButton			*m_pButton_cancel_quest;
	//KHY - 0822 - ���Ǻ� ����Ʈ �߰�.
	CButton			*m_pButton_SpeicalQuest;
	CButton			*m_pButton_HappyBeanQuest;

	SI16			siQuestSwitch; //QUEST_TYPE 

	CStatic			*m_pStatictext_generalquest;
	CEdit			*m_pEditbox_generalquest;
	CStatic			*m_pStatictext_quest_clear;
	CList			*m_pListbox_quest_clear;
	CStatic			*m_pStatictext_questsum;
	
	SI32			m_QuestListData[MAX_QUEST_TYPE];
	
	cltPQuestInfo	clOldQuestInfo;
	cltPDailyQuestInfo clOldDailyQuestInfo;
	cltPDailyQuest2Info clOldDailyQuest2Info;

	cltNQuestStatus();
	~cltNQuestStatus();
	void Create();
	bool IsShow();
	void Show();
	void Hide();
	void Action();
	void ShowCurrentQuestInfo( SI32 id );

	void ShowSelectedQuestStory( SI32 SelectedListIndex );

	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );

	bool m_bShow;

	cltCharManager* pclCM;

	SI32 CharUnique;	


	static void CALLBACK NQuestStatusStaticProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void CALLBACK NQuestStatusProc( UINT nEvent, int nControlID, CControllerObj* pControl );

	void Close();
};


//#endif
