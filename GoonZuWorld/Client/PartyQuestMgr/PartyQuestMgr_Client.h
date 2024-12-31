#ifndef __PARTYQUESTMGR_CLIENT_H__
#define __PARTYQUESTMGR_CLIENT_H__

#include <Directives.h>
#include "../../CommonLogic/PartyQuestMgr/PartyQuestMgr_Common.h"
#include "../../common/Char/CharServer/Char-Server.h"


class cltCommonLogic;
struct stClientPartyUser;

class CPartyQuestMgr_Client : public CPartyQuestMgr_Common
{
public:
	PartyQuest_UnitData m_PartyQuestData;
	TCHAR				m_szQuestInfoForDlg[1024];

public:
	bool	Initialize();		//	�Ŵ��� �ʱ�ȭ

	bool	DoCheckPartyQuest(SI32 siPartyUserNum, stClientPartyUser ClientPartyUser[]);	// ��Ƽ����Ʈ ���� ���� ���� üũ
	bool	CheckAlreadyPartyQuest();														// �̹� ����Ʈ ������ üũ
	bool	CheckPartyLeader();																// ��Ƽ����Ʈ ��Ƽ�� üũ
	bool	CheckUserNum(SI32 siPartyUserNum);												// ��Ƽ �ο� üũ
	bool	CheckLevel(stClientPartyUser ClientPartyUser[]);								// ��Ƽ���� ���� üũ

	void	StartPartyQuestData(PartyQuest_UnitData* PartyQuestData);
	void	UpdatePartyQuestData(PartyQuest_UnitData* PartyQuestData, DWORD dwQuestTime, bool bClear = false);	// ��Ƽ����Ʈ ������ ����
	void	UpdatePartyInfoMsg(PartyQuest_UnitData* PartyQuestData, DWORD dwQuestTime, bool bClear);			// ��Ƽ����Ʈ ���� �޼���
	void	DoGiveUpPartyQuest();

public:
	CPartyQuestMgr_Client();
	~CPartyQuestMgr_Client();
};



#endif	//__PARTYQUESTMGR_CLIENT_H__