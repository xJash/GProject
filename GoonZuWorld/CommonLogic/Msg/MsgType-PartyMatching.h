// ��Ƽ��Ī
#ifndef _MSGTYPEPARTYMATCHINGQUEST_H_
#define _MSGTYPEPARTYMATCHINGQUEST_H_

#include "../../Common/CommonHeader.h"

#include "../../common/PartyMgr/PartyBaseInfo.h"
#include "../../CommonLogic/PartyMatchingMgr/Defines_PartyMatchingMgr.h"
#include "../../CommonLogic/PartyMatchingMgr/Info_PartyMatching.h"



//#include "../../CommonLogic/PartyMatchingMgr/Client_PartyMatchingMgr.h"




//////////////////////////////////////////////////////////////////////////


// ������ ��Ƽ�� ��Ƽ�� ������ �޶�� ������ ��û
class cltGameRequest_GetPartyMemberInfo
{
public:
	SI32 siLeaderUnique;

public:
	cltGameRequest_GetPartyMemberInfo(SI32 sileaderunique)
	{
		ZeroMemory( this, sizeof(cltGameRequest_GetPartyMemberInfo) );
		siLeaderUnique = sileaderunique;
	}
};

// ��Ƽ���� ������ ã�Ƽ� ��û�ߴ� Ŭ�� ������
class cltGameResponse_GetPartyMemberInfo
{
public:
	SI32 siLeaderUnique;
	NTCHARString16 aPartyMemberNameList[MAX_PARTY_USER_NUM];

public:
	cltGameResponse_GetPartyMemberInfo(SI32 sileaderunique)
	{
		ZeroMemory( this, sizeof(cltGameResponse_GetPartyMemberInfo) );

		siLeaderUnique = sileaderunique;
	}
};

// ����ߴ� ��Ƽ��Ī�� ������ ��Ŷ (��ȭ������ ��ư ������ ����) - ���� �ƹ��͵� ���°� ����.
class cltGameRequest_RemovePartyMatching
{
public:
	cltGameRequest_RemovePartyMatching()
	{
	}
};

// ���ܻ�Ȳ �˸� ��Ŷ�� �޼��� ����
class cltGameResponse_PartyMatchingException
{
public:
	SI16 siExceptionFlags;

public:
	cltGameResponse_PartyMatchingException(SI16 siexceptionflags)
	{
		ZeroMemory( this, sizeof(cltGameResponse_PartyMatchingException) );

		siExceptionFlags = siexceptionflags;
	}
};

//////////////////////////////////////////////////////////////////////////




// ��Ƽ ����Ʈ ���� ���� ���� üũ ��û
class cltGameRequest_PartyMatchingLevel
{
public:
	SI32 m_siPersonID;
	SI16 m_siLevelType;

public:
	cltGameRequest_PartyMatchingLevel( SI32 PersonID, SI16 siLevelType )
	{
		m_siPersonID = PersonID;
		m_siLevelType = siLevelType;
	}
};

// ��Ƽ ����Ʈ ���� ���� ���� üũ ����
class cltGameResponse_PartyMatchingLevel
{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<CInfo_PartyMatching, MAX_PARTYMATCHING_LIST_SEND_SIZE>		m_PartyMatchingList;
#else
	CInfo_PartyMatching														m_PartyMatchingList[MAX_PARTYMATCHING_LIST_SEND_SIZE];
#endif

	bool bNeedClearOldList;

public:
	cltGameResponse_PartyMatchingLevel()
	{
		ZeroMemory( this, sizeof(CInfo_PartyMatching) );
	}

	// ���޹��� siIndex��ġ(m_PartyMatchingList �迭������ �ε���)�� ��Ƽ ��Ī ������ �ִ´�. (�ڵ�ȭ ���� �ʴ´�. ����� ������ �ε��� ���� ��Ʈ�� �ϵ��� å���� �ش�.)
	void AddPartyMatchingInfo(SI16 siIndex, CInfo_PartyMatching& rPartyMatchingInfo)
	{
		if ( 0 > siIndex || MAX_PARTYMATCHING_LIST_SEND_SIZE <= siIndex ) return;

		memcpy( &m_PartyMatchingList[siIndex], &rPartyMatchingInfo, sizeof(rPartyMatchingInfo) );

		/*m_PartyMatchingList[siIndex].m_siLeaderID = rPartyMatchingInfo.m_siLeaderID;
		m_PartyMatchingList[siIndex].m_strLeaderName = rPartyMatchingInfo.m_strLeaderName;
		m_PartyMatchingList[siIndex].m_strPartyName = rPartyMatchingInfo.m_strPartyName;
		m_PartyMatchingList[siIndex].m_strHelloMessage = rPartyMatchingInfo.m_strHelloMessage;
		m_PartyMatchingList[siIndex].m_siParentQuest = rPartyMatchingInfo.m_siParentQuest;
		m_PartyMatchingList[siIndex].m_siChildQuest = rPartyMatchingInfo.m_siChildQuest;

		for ( SI16 i = 0; i < MAX_PARTY_USER_NUM; ++i )
		{
			m_PartyMatchingList[siIndex].m_PartyMemberIDList[i] = rPartyMatchingInfo.m_PartyMemberIDList[i];
		}*/
	}
};


// ���ο� ��Ƽ��Ī�� ����ϰڴٴ� request ��Ŷ�� �޼��� ����
class cltGameRequest_PartyMatchingCreate
{
public:
	SI32 m_siCharID;
	CInfo_PartyMatching m_Info;

public:
	cltGameRequest_PartyMatchingCreate(CInfo_PartyMatching& rInfo)
	{
		ZeroMemory( this, sizeof(cltGameRequest_PartyMatchingCreate) );

		Set_PartyMatchingInfo( rInfo );
	}

	void Set_PartyMatchingInfo(CInfo_PartyMatching& rInfo)
	{
		memcpy( &m_Info, &rInfo, sizeof(rInfo) );
	}
};

// ������ ���������� ��Ƽ��Ī�� ��� �Ǿ��ٴ� response ��Ŷ�� �޼��� ����
class cltGameResponse_PartyMatchingCreate
{
public:
	SI32 m_siCharID;
	bool m_bResult;

public:
	cltGameResponse_PartyMatchingCreate(bool bResult)
	{
		ZeroMemory( this, sizeof(cltGameResponse_PartyMatchingCreate) );

		m_bResult = bResult;
	}
};















class cltGameRequest_PartyCreateConditionCheck
{
public:
	SI32 m_siPersonID;

public:
	cltGameRequest_PartyCreateConditionCheck(SI32 PersonID)
	{
		m_siPersonID = PersonID;
	}
};

class cltGameResponse_PartyCreateConditionCheck
{
public:
	SI32 m_siPersonID;


public:
	cltGameResponse_PartyCreateConditionCheck(SI32 PersonID, CInfo_PartyMatching& rPartyInfo)
	{
		ZeroMemory( this, sizeof(cltGameResponse_PartyCreateConditionCheck) );

		m_siPersonID = PersonID;
	}

};



#endif