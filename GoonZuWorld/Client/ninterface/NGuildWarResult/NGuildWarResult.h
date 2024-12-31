#pragma once

#include "../../InterfaceMgr/DialogController.h"
#include "../Common/SystemReward/SystemReward.h"

class CNGuildWarResult : public CDialogController
{
public:
	enum 
	{
		INPUT_HOME,		//	Ȩ�� ������ input
		INPUT_AWAY,		//	����� ������ input
		INPUT_LINE,		//	����Ʈ�� �� ���� ������ input
	};

	//	��� ��� ������ ������ �� ������
	struct	GuildMember	
	{
		TCHAR	m_szUserName[MAX_PLAYER_NAME];	//	���� �̸�
		SI32	m_siKillCount;					//	ų��
		SI32	m_siDeathCount;					//	����
		SI32	m_siTeamIndex;					//	Home?Away?
	};


	stListBoxItemData	m_tempItemData;
	GuildMember			m_clGulidMember;						//	����Ʈ�� �����͸� ���� ����ü
	SI32				m_siInputCount;							//	����Ʈ�� ������ ������ ���� ī��Ʈ
	SI32				m_siActionCount;						//	���â�� �Ⱥ����ٶ� ���� ī��Ʈ �Ŀ� show(false) �����ش�.


public:
	CNGuildWarResult();
	~CNGuildWarResult();

	void Init();
	void Destroy();

	void Create();

	static void CALLBACK StaticGuildWarResultDlgProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void CALLBACK NGuildWarResultDlgProc(UINT nEvent, int nControlID, CControllerObj* pControl);

	InterfaceFactory	m_InterfaceFactory;

	void Action();
	void setWinLose(SI32 siWinLose);
	void InputData(SI32 siTeamIndex, TCHAR* pUserName, SI32 siKillPoint, SI32 siDeathPoint);
	void SetList();
};