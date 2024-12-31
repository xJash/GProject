// ��Ƽ��Ī
#ifndef _INFO_PARTYMATCHING_H_
#define _INFO_PARTYMATCHING_H_

#include "../../Common/CommonHeader.h"
#include "../../common/PartyMgr/PartyBaseInfo.h"





// ���� ��Ƽ ������� �� ������ ������ �������̽� �߰�




class CInfo_PartyMatching
{
public:
	CInfo_PartyMatching();
	~CInfo_PartyMatching();

public:
	// party member info
	SI32				m_siLeaderID;
	NTCHARString32		m_strLeaderName;

	NTCHARString64		m_strPartyName;
	NTCHARString128		m_strHelloMessage;

#if _SAFE_MEMORY
	NSafeTArray<SI32, MAX_PARTY_USER_NUM> m_PartyMemberIDList;
#else
	SI32				m_PartyMemberIDList[MAX_PARTY_USER_NUM];
#endif

	// quest info
	SI32				m_siParentQuest;
	SI32				m_siChildQuest;

	// interfaces
public:
	bool CheckCondition();

	// ���� ��Ƽ �Ŵ��� �̿��Ұ��, �̺κ� ��� ��Ƽ ���� ����Ʈ �ѹ��� �ʿ�. �ϴ� �ּ�
	void SetLeaderID(SI32 siLeaderID);
	void SetLeaderName(TCHAR* pszLeaderName);
	void SetPartyName(TCHAR* pszPartyName);
	void SetHelloMessage(TCHAR* pszHelloMessage);

	SI32 GetLeaderID();
	TCHAR* GetLeaderName();
	TCHAR* GetPartyName();
	TCHAR* GetHelloMessage();

	void AddMemberID(SI32 siMemberID);
	void RemoveMemberID(SI32 siMemberID);

	void SetParentQuest(SI32 siParentQuest);
	void SetChildQuest(SI32 siChildQuest);

	SI32 GetParentQuest();
	SI32 GetChildQuest();
};

#endif				//_INFO_PARTYMATCHING_H_