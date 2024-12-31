#ifndef __PARTYQUESTMGR_SERVER_H__
#define __PARTYQUESTMGR_SERVER_H__

#include <Directives.h>
#include "../../CommonLogic/PartyQuestMgr/PartyQuestMgr_Common.h"
#include "../../common/Char/CharServer/Char-Server.h"


class cltCommonLogic;

class CPartyQuestMgr_Server : public CPartyQuestMgr_Common
{
private:

public:
	bool	Initialize();	//	�Ŵ��� �ʱ�ȭ
	void 	UpdatePartyQuest(SI32 siCharID, SI32 siPartyIndex, SI32 siQuestType, SI32 siCondition, SI32 siAmount);	// ��Ƽ����Ʈ ���� ����

	bool	DoCheckPartyQuest(CPartyObj* pPartyObject);		// ��Ƽ����Ʈ ���� ���� ���� üũ
	bool	CheckAlreadyPartyQuest(CPartyObj* pPartyObject);
	bool	CheckPartyLeader(CPartyObj* pPartyObject);		// ��Ƽ����Ʈ ��Ƽ�� üũ
	bool	CheckUserNum(CPartyObj* pPartyObject);			// ��Ƽ �ο� üũ
	bool	CheckLevel(CPartyObj* pPartyObject);			// ���� üũ
	bool	CheckPCRoom(CPartyObj* pPartyObject);			// �ǽù� ���� ����Ʈ üũ
	
	bool	IncreasePartyQuestCondition(SI32 siPartyIndex, SI32 siQuestType, SI32 siCondition, SI32 siAmount);		// ����Ʈ Amount����
	bool	ProcessCurrentQuestClear(SI32 siPartyIndex, SI32 siCharID);	// ���� �������� ����Ʈ�� Ŭ���� �ߴ��� üũ
	bool	ProcessAllQuestClear(SI32 siPartyIndex);		// ��� ����Ʈ�� Ŭ���� �ߴ���
	void	ProcessReward(SI32 siPartyIndex, SI32 siCharID);				// ����Ʈ ����
	bool	DoGiveUpPartyQuest(SI32 siPartyIndex, SI32 siLeaveCharID, SI32 siMessage);	// ��Ƽ����Ʈ ����� 
	void	UpdatePartyQuestTime(SI32 siPartyIndex, PartyQuest_UnitData* pPartyQuestData);
	bool	CheckSameArea(CPartyObj* pPartyObj);

public:
	CPartyQuestMgr_Server();
	~CPartyQuestMgr_Server();
};



#endif	//__PARTYQUESTMGR_SERVER_H__