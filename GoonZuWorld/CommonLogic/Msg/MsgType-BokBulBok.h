#ifndef _MSGTYPEBOKBULBOK_H_
#define _MSGTYPEBOKBULBOK_H_

#include "../../Common/CommonHeader.h"
#include "../../common/BokBulBokEventMgr/BBBWaitListManager.h"





// ���Һ� ���� ���� ���� ���� üũ
class cltGameRequest_BBBCheckCondition
{
public:
	SI32 m_siPersonID;

public:
	cltGameRequest_BBBCheckCondition( SI32 PersonID )
	{
		m_siPersonID = PersonID;
	}
};

// ���Һ��� ���� ���������� ���� ���� �޼���
class cltGameResponse_BBBCheckCondition
{
public:
	SI32 m_siPersonID;

public:
	cltGameResponse_BBBCheckCondition( SI32 siPersonID )
	{
		m_siPersonID = siPersonID;
	}
};

// ���Һ� ����ڸ���Ʈ ������ ���� �޼��� ( Ŭ��-> ���� )
class cltGameMsgRequest_BBB_WaitList_Answer
{
public:
	SI32 m_siPersonID;

public:
	cltGameMsgRequest_BBB_WaitList_Answer( SI32 siPersonID )
	{
		m_siPersonID = siPersonID;
	}
};

// ���Һ� ����ڸ���Ʈ ��ҿ� ���� �޼��� ( Ŭ��-> ���� )
class cltGameMsgRequest_BBB_WaitList_Cancel
{
public:
	SI32 m_siPersonID;

public:
	cltGameMsgRequest_BBB_WaitList_Cancel( SI32 siPersonID )
	{
		m_siPersonID = siPersonID;
	}
};

// ����� ����Ʈ ���޿� �޼��� ( ����-> Ŭ��)
class cltGameResponse_BBB_WaitList_Answer
{
public:
	TCHAR m_aCharName[MAX_RESERVATION_NUM][MAX_CHARACTER_NAME_LENGTH];
	bool m_bResult;
	GMONEY m_siTotalMoney;

public:
	cltGameResponse_BBB_WaitList_Answer(_BBBWaitUserData* pWaitList, bool bResult, GMONEY siTotalMoney )
	{
		ZeroMemory( m_aCharName, sizeof(TCHAR) * MAX_RESERVATION_NUM * MAX_CHARACTER_NAME_LENGTH );


		for ( int i = 0; i < MAX_RESERVATION_NUM; ++i )
		{
			MStrCpy( m_aCharName[i], pWaitList[i].szUserName, MAX_CHARACTER_NAME_LENGTH );
		}

		m_bResult = bResult;
		m_siTotalMoney = siTotalMoney;
	}
};

// ��⸦ ��� �ش޶�� ��û�� ���� ������ ó�� ��� (����->Ŭ��)
class cltGameMsgResponse_BBB_WaitList_Cancel
{
public:
	TCHAR m_aCharName[MAX_RESERVATION_NUM][MAX_CHARACTER_NAME_LENGTH];
	bool m_bResult;

public:
	cltGameMsgResponse_BBB_WaitList_Cancel(_BBBWaitUserData* pWaitList, bool bResult)
	{
		ZeroMemory( m_aCharName, sizeof(TCHAR) * MAX_RESERVATION_NUM * MAX_CHARACTER_NAME_LENGTH );


		for ( int i = 0; i < MAX_RESERVATION_NUM; ++i )
		{
			MStrCpy( m_aCharName[i], pWaitList[i].szUserName, MAX_CHARACTER_NAME_LENGTH );
		}

		m_bResult = bResult;
	}
};

// �������� ������ �˸��� ��Ŷ ���� (����->Ŭ��)
class cltGameMsgResponse_BBB_StageStart
{
public:
	SI32 m_siPersonID;
	SI16 m_siCurrentStage;
	DWORD m_dwStageStartTime;

public:
	cltGameMsgResponse_BBB_StageStart(SI32 siPersonID, SI16 siCurrentStage, DWORD dwStageStartTime)
	{
		m_siPersonID = siPersonID;
		m_siCurrentStage = siCurrentStage;
		m_dwStageStartTime = dwStageStartTime;
	}
};

// �������� Ŭ���� ���� �޼���
class cltGameMsgRequest_BBB_StageFail
{
public:
	SI32 m_siPersonID;

public:
	cltGameMsgRequest_BBB_StageFail(SI32 siPersonID)
	{
		m_siPersonID = siPersonID;
	}
};

// �������� ���н� Lose ����� �޼���.
class cltGameMsgResponse_BBB_StageFail
{
public:
	SI32 m_siPersonID;
	DWORD m_dwStageEndTime;

public:
	cltGameMsgResponse_BBB_StageFail(SI32 siPersonID, DWORD dwStageEndTime)
	{
		m_siPersonID = siPersonID;
		m_dwStageEndTime = dwStageEndTime;
	}
};

// �������� ������ Win ����� �޼���.
class cltGameMsgResponse_BBB_StageWin
{
public:
	SI32 m_siPersonID;
	DWORD m_dwStageClearTime;
public:
	cltGameMsgResponse_BBB_StageWin(SI32 siPersonID, DWORD dwStageClearTime)
	{
		m_siPersonID = siPersonID;
		m_dwStageClearTime = dwStageClearTime;
	}
};

class cltGameMsgResponse_BBB_WarpMapQuestion
{
public:
	SI32 m_siPersonID;

public:
	cltGameMsgResponse_BBB_WarpMapQuestion(SI32 siPersonID)
	{
		m_siPersonID = siPersonID;
	}
};

class cltGameMsgRequest_BBB_WarpMapAnswer
{
public:
	SI32 m_siPersonID;
	bool m_bWantWarpMap;

public:
	cltGameMsgRequest_BBB_WarpMapAnswer(SI32 siPersonID, bool bWantWarpMap)
	{
		m_siPersonID = siPersonID;
		m_bWantWarpMap = bWantWarpMap;
	}
};

class cltGameMsgResponse_BBB_NotEnoughMoney
{
public:
	SI32 m_siPersonID;

public:
	cltGameMsgResponse_BBB_NotEnoughMoney(SI32 siPersonID)
	{
		m_siPersonID = siPersonID;
	}
};

class cltGameMsgResponse_BBB_StageClear
{
public:
	SI32 m_siPersonID;

public:
	cltGameMsgResponse_BBB_StageClear(SI32 siPersonID)
	{
		m_siPersonID = siPersonID;
	}
};

class cltGameMsgResponse_BBB_GM_ShowMonstertype
{
public:
	SI32 m_siPersonID;
	bool m_bShow;

public:
	cltGameMsgResponse_BBB_GM_ShowMonstertype(SI32 siPersonID, bool bShow)
	{
		m_siPersonID = siPersonID;
		m_bShow = bShow;
	}
};

class cltGameMsgResponse_BBB_10ClearNotice
{
public:
	SI32 m_siPersonID;
	SI32 m_siMoney;
	NTCHARString256	szWinnerName;

public:
	cltGameMsgResponse_BBB_10ClearNotice(SI32 siPersonID, SI32 siMoney, NTCHARString256 pszWinnerName )
	{
		m_siPersonID = siPersonID;
		m_siMoney = siMoney;
		szWinnerName = pszWinnerName;
	}
};

class cltGameMsgRequest_BBB_AlreadyReserved
{
public:
	SI32 m_siPersonID;

public:
	cltGameMsgRequest_BBB_AlreadyReserved(SI32 siPersonID)
	{
		m_siPersonID = siPersonID;
	}
};



// 

#endif