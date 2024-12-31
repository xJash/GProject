#ifndef _CLIENT_BOKBULBOK_MANAGER_H_
#define _CLIENT_BOKBULBOK_MANAGER_H_

#include "../../Common/CommonHeader.h"




class CClient_BBBMgr
{
public:
	CClient_BBBMgr();
	~CClient_BBBMgr();


protected:
	bool m_bWaitListResult;
	DWORD m_dwStageStartTime;
	bool m_bStageStartFlag;

	SI16 m_siCurrentStage;

	// ������ ���� ���Ͽ��� �о���� �ð� ������
public:
	SI32 m_siStageStartDelay;				// �������� ���۶� ī��Ʈ �ð� (ī��Ʈ �ð� + ��ŸƮ1��)
	SI32 m_siStageLoseDelay;				// �������� ���� ǥ�� �ð�
	SI32 m_siStageWinDelay;					// �� �������� �� ǥ�� �ð�
	SI32 m_siStagePlayDelay;				// �������� �÷��� �ð�
	SI32 m_siTotalStageWinDelay;			// ���� �������� �Ϸ� �� �� ǥ�� �ð�
	bool m_b3secDelay;						// �̸�Ƽ�� ���� ������ üũ�� ���� �÷���
	


public:
	bool m_bGMShowMonsterType;				// ���� ��ɾ�� ���� ���� Ÿ�Ժ��� ǥ�� ����ֱ�

public:
	// 1. �������� ���� �޼����� [�ʿ� ���� ����] �϶��� ���� ó��- ������ �ٷ��̵�.
	// 2. �������� ���� �޼����� [��� ����Ʈ�� ��� ����] �϶��� ���� ó��
	// 3. �������� ���� �޼����� [���Һ� ���� ���� �Ұ�] �϶��� ���� ó��

	void Action();

	void Warp_GameStage(SI32 siPersonID);				// �ش� ĳ���͸� ������ ������ �̵� ��Ų��.

	void Pop_WaitListDlg();
	void Pop_EntryFailDlg();
	void Pop_DetailWaitListDlg(TCHAR** ppWaitList, bool bResult, GMONEY siTotalMoney);
	void Pop_WaitListCancelResult();
	void Pop_WarpMapQuestionDlg();
	void Pop_NotEnoughMoneyDlg();

	bool IsReserved() { return m_bWaitListResult; }							// ���� ��� ����Ʈ�� ��� �Ǿ� �ִ����� ���� üũ (�Ź� ������ ����� �����Ƿ�)
	void SetReserveStatus(bool bResult) { m_bWaitListResult = bResult; }	// ���� ����� ����Ʈ ��� ���¸� �����ϴ� �Լ�. (Ŭ���ʸ�.. ������ ��Ŷ ���� ������ ��)
	void RefreshWaitList(TCHAR** ppWaitList);

	void StageStart(SI32 siPersonID, SI16 siCurrentStage, DWORD dwStartTime);
	void StageFail(SI32 siPersonID, DWORD dwStartTime);
	void StageClear();
	void TotalStageClear();

	void Check_AlreadyReserved();
	void Receive_AlreadyReserved(TCHAR** ppWaitList, bool bResult, GMONEY siTotalMoney );

	void Notice_10ClearNotice(SI32 siRewardMoney, TCHAR* pszWinnerName);
	
	void DrawWinImage_ForMe();

protected:
	void _Load_BBBGameInfo();
	void _Clear_BBBStatus();
};

#endif				//_CLIENT_BOKBULBOK_MANAGER_H_