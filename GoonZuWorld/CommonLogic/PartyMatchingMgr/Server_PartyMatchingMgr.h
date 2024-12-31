// ��Ƽ��Ī
#ifndef _SERVER_PARTYMATCHING_MANAGER_H_
#define _SERVER_PARTYMATCHING_MANAGER_H_

#include "../../Common/CommonHeader.h"
#include "Info_PartyMatching.h"

#include "../../CommonLogic/PartyQuestMgr/PartyQuestMgr_Common.h"





////////////////////////////////////////////////////////////////////////
//������ ��Ƽ ��Ī �Ŵ��� : ��Ƽ ����Ʈ ����
////////////////////////////////////////////////////////////////////////


class CServer_PartyMatchingMgr
{
public:
	CServer_PartyMatchingMgr();
	~CServer_PartyMatchingMgr();


	//--------- ��Ƽ���� ��ü ���� ���
protected:
	// ��Ƽ���� ��ü�� ����Ʈ (NkRbTreeMap�̿�)
	typedef NkRbTreeMap<SI32, CInfo_PartyMatching> PMLIST;
	PMLIST m_aPMList[MAX_PARTYQUEST_CATEGORY_NUM];

	DWORD m_dwWaitListRefreshTime;

protected:
	void _Refresh_UserList();

public:
	// �ʿ� �������̽���
	void Remove_PartyMatching(SI32 siLeaderID);
	TCHAR* GetPartyName(SI32 siLeaderUnique);
	bool IsExist(SI32 siLeaderUnique);


	//--------- ���� ��Ƽ��Ī �Ŵ����� ���
protected:
	// send Packet to CLIENT
	void _sendpacket_PartyMatchingList(SI32 siCharID, const PMLIST& rPMList);
	void _sendpacket_PartyMatchingCreate(SI32 siCharID, bool bSuccess);

public:
	// default
	void Action();

	// msg process
	void MsgProcess_Request_PartyMatchingLevel(SI32 siCharID, SI16 siLevelType);
	void MsgProcess_Request_PartyMatchingCreate(SI32 siCharID, CInfo_PartyMatching& rInfo);

	SI32 Get_Category(SI32 siLeaderUnique);
	SI32 Get_Mission(SI32 siLeaderUnique);
};

#endif				//_SERVER_PARTYMATCHING_MANAGER_H_