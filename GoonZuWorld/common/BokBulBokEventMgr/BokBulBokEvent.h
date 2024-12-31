//===================================================================================================
// ����: ���Һ� �̴ϰ���
// ����ġ: Switch_BokBulBok
// ����: ���Һ� �̺�Ʈ�� ������ �޴���. (NPC����, ���ฮ��Ʈ����, ĳ���Ϳ���, ���ӽ�����������..)
// �ۼ���: 2009.08.06
// �ۼ���: ������
//===================================================================================================

#ifndef _BOKBULBOK_EVENT_H_
#define _BOKBULBOK_EVENT_H_



#include "../common/CommonHeader.h"
#include "../NLib/NUpdateTimer.h"	//5�� ���������� ���

#include "../../CommonLogic/Msg/MsgType-BokBulBok.h"

#include "BBBWaitListManager.h"
#include "BBBEventMapManager.h"
//#include "../common/BokBulBokEventMgr/BBBStage.h"



// ���Һ� ������ �� 10���� ���������� �����Ǿ��ִ�.
enum BokBulBok_Game_Stage
{
	BOKBULBOK_0_WAIT = 0,
	BOKBULBOK_1_STAGE,
	BOKBULBOK_2_STAGE,
	BOKBULBOK_3_STAGE,
	BOKBULBOK_4_STAGE,
	BOKBULBOK_5_STAGE,
	BOKBULBOK_6_STAGE,
	BOKBULBOK_7_STAGE,
	BOKBULBOK_8_STAGE,
	BOKBULBOK_9_STAGE,
	BOKBULBOK_10_STAGE,	
};

// ���� ������ ���� üũ
enum BokBulBok_Game_Status
{
	BOKBULBOK_STATUS_WAIT = 0,			// �̺�Ʈ ��� �ð�
	BOKBULBOK_STATUS_PLAYER_LIST,		// �������� ��û�� ���� ����Ʈ
	BOKBULBOK_STATUS_SEND_MSG,			// ����Ʈ�� ��ϵ� ��û�ڿ��� (����������) ���� ���θ� ���´�.
	BOKBULBOK_STATUS_WAITING_TIME_MSG,	// �������� �޼��� ���� �� 10�ʰ� ��ٷ���(���� ���� ��� �ڵ� ��ҵ�.)
	BOKBULBOK_STATUS_GAME_STATR,		// ���� ����
	BOKBULBOK_STATUS_GAME_PLAYING,		// ���� �÷��� ����
	BOKBULBOK_STATUS_GAME_OVER,			// ���� �� �� ���� ����	(���������� Ŭ���� �ϴ���, ������ ������� ���..)
};

enum NPC_Position
{
	BOKBULBOK_X = 22,
	BOKBULBOK_Y = 58,
};

enum BokBulBok_Failure_Msg
{
	BOKBULBOK_RESERVATION_FAIL = 0,
};



class CServer_BBBMgr
{
public:
	CServer_BBBMgr(void);
	~CServer_BBBMgr(void);

	//----------------------------------------------------
	// Server
	//----------------------------------------------------
private:
	SI32 m_siBokBulBok_NPC_ID;		// ���Һ� NPC�� ĳ���� ID
	//SI32 m_siTotalReservePlayer;	// ������ �� �ο���
	SI32 m_siTotalBalance;			// ���ݱ��� ���ҵ� �� ���� �ݾ�(�������)
	SI32 m_siGameFee;				// ���������� �����ؾ��� �����ݾ�
	SI32 m_siMyTotalGameFee;		// ���ӿ� �������� ������ �����ϰ� �ִ� �� �ݾ�.
	SI32 m_siRewardPrice;			// �������� ���޹��� �ݾ�.

public:
	GMONEY m_siTotalMoney;			// ���� ������ �Ѿ� (������ �������� 30% ���� ���� �׼�)
	GMONEY m_siTotalRewardPrice;	// ���� ����� �Ѿ� (�������� ������ ���ư� �ݾ�)

public:
	CBBBWaitListManager m_BBBWaitListMgr;				// ����� ����Ʈ ������
	CBBBEventMapManager m_BBBEventMapMgr;				// �̺�Ʈ �� ������

public:
	// ���Һ� ����
	DWORD dwNotice_Msg;			// ��� ���� (�⺻ 60��)
	DWORD dwNextmNoticetime;	// ���� ���� ��µ� �ð�

public: 
	void init(void);									// �ʱ�ȭ
	void Action();
	//bool CreateBokBulBokNPC();						// ���Һ� NPC ����.

	void AddBBBList(SI32 siPersonID);					// ��û�� ���� ������ ���̵� ���Һ� �Ŵ����� ����
	void StageFail(SI32 siPersonID);					// �������� Ŭ���� ����
	void StageClear(SI32 siPersonID);					// �������� Ŭ���� ����
	void LeaveMap(SI32 siPersonID);						// �ʿ� ���� �����̴� ������ ������.

	bool Insert_List(SI32 siPersonID);									// ��⸮��Ʈ ���
	void Remove_List(SI32 siPersonID);									// ��� ���
	void SendWaitListToClient(SI32 siPersonID, bool bResult);			// ������ ���� ����Ʈ�� Ŭ��� �����ش�.

	bool AddReserveList(SI32 siPersonID);				// ���� ������ ������ ����� ����Ʈ�� �߰��Ѵ�.

	void DeleteplayerfromWaitingList(SI32 siPersonID);	// ����� ����Ʈ���� �ش� �÷��̾ ���� ��Ų��.

	//void Warp_GameStart(SI32 siPerson);					// ������ ������ �̵� ��Ų��.

	void ActiveTemporaryReserve(SI32 siPersonID);
	void CancelTemporaryReserve(SI32 siPersonID);

	GMONEY GetRewardMoney();
	void SetEntranceFee(GMONEY siEntranceFee);

	void SetPlayTime(SI32 siPlayTime);		// �ʴ��� �÷��� �ð�(�и��� ���� �ƴ�)
	void ShowMonsterType(SI32 siID, SI32 siShowMonsterType);
	void Set20mNoticeTime(SI32 siNoticeTime);

	void Check_AlreadyReserved(SI32 siID);

	// ���ο��� ���� ����� ��� �Լ���
protected:
	SI16 _siAvailableMapNumber;

protected:
	bool _Check_Avail_Map();
	bool _Check_Avail_List();

	void _Check_StartBBB(SI32 siPersonID);
	void _SendMsg_WaitList(SI32 siPersonID);										// ��⸮��Ʈ�� ���
	void _SendMsg_EnterFail(SI32 siPersonID);

	void _Notice_20_Minute_TotalRewardMoney();
};

#endif