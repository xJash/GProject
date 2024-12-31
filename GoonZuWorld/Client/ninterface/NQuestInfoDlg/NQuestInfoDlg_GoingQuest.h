// [����] ����� ����Ʈ �˸�â
#pragma once

#include "../../InterfaceMgr/DialogController.h"
#include "../../InterfaceMgr/InterfaceFile.h"

enum DAILY_QUESTTYPE
{
     DAILY_QUESTTYPE_1	= (MAX_QUEST_TYPE + 1)	// ������Ʈ
	,DAILY_QUESTTYPE_2							// ���̾� ����Ʈ
	,DAILY_QUESTTYPE_3							// ��Ʋ�� ����Ʈ
	,PARTY_QUESTTYPE							// all quest type ������ �߰��߽��ϴ�. ������ ����ƮŸ�Կ� ������ ���� �ʱ� ����	

	,ALL_QUEST_TYPE								// MAX_QUEST_TYPE + DAILY_QUESTTYPE + 1
};


class cltDailyQuestInfo
{
public:
	SI16	m_siDailyQuestType;		// ���ϸ� ����Ʈ 1,2,3
	SI32	m_siCondition;			// 1,2�϶��� ����/ 3�϶��� ������
	SI16	m_siNowAmount;			// ���� �� ����
	SI16	m_siNeedAmount;			// �ʿ��� ����
	SI32	m_siLeftTime;			// ���� �ð�
	bool	m_bHidden;				// ��������Ʈ ����

	SI32	m_siRewardExp;			// ���� ����ġ
	GMONEY	m_gmRewardMoney;		// ���� ��
	SI32	m_siRewardItemUnique;	// ���� ������
	SI16	m_siRewardItemAmount;	// ���� ������ ����	

public:
	cltDailyQuestInfo()
	{
		Init();
	}

	cltDailyQuestInfo( cltPDailyQuestInfo* pclDailyQuestInfo1 );
	cltDailyQuestInfo( cltPDailyQuest2Info* pclDailyQuestInfo2 );
	cltDailyQuestInfo( cltPDailyQuest3Info* pclDailyQuestInfo3 );

	void Init()
	{
		ZeroMemory( this, sizeof(cltDailyQuestInfo) );
	}

	bool GetDailyQuestInfo( OUT TCHAR* pszBuffer, IN SI32 siBufferSize, OUT SI32* siGimgIndex, OUT SI32* siFont );
	bool GetDailyQuestRewardText( OUT TCHAR* pszBuffer, IN SI32 siBufferSize );

	void DailyQuestCancel();

};

const SI32 Const_Max_Buf_Size = 2048;


class CNQuestInfoDlg_GoingQuest : public CDialogController
{

	// ��������
private:
	InterfaceFactory	m_InterfaceFactory;
	SI32				m_siGoingQuestList[ALL_QUEST_TYPE];
	

	// �Լ�����
public:
	CNQuestInfoDlg_GoingQuest();
	~CNQuestInfoDlg_GoingQuest();

	void Create(CControllerMgr* pParent);
	
	static void CALLBACK StaticQuestInfoDlg_GoingQuestProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void CALLBACK NQuestInfoDlg_GoingQuestProc(UINT nEvent, int nControlID, CControllerObj* pControl);

	void Action();

	void Show();
	void Hide();

	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );

private:
	void LoadGoingQuestList();

	bool AddDailyQuestInfo( cltDailyQuestInfo* pclDailyQuestInfo );

	bool AddQuestInfo( SI32 siQuestType, cltPersonQuestUnitInfo* pclPQuestInfo );

	bool AddPartyQuestInfo(TCHAR* szInfo);

	void SetQuestListBoxItemData( SI32 siGimgIndex, SI32 siFont, TCHAR* pszText );
	void SetQuestListBoxItemData( SI32 siGimgIndex, SI32 siFont, TCHAR* pszText, COLORREF colorRef);

	void SelectQuestInfo( SI32 siSelectedIndex );
	void GetMagicLampQuestInfoText( OUT TCHAR* pszBuffer, IN SI32 siBufferSize );

	void QuestContinue( SI32 siSelectedIndex );

	void ShowQuestCancelMsgBox( SI32 siSelectedIndex );
	void QuestCancel( SI32 siQuestType );
	
};
