#ifndef __MSGTYPEPARTYQUEST_H__
#define __MSGTYPEPARTYQUEST_H__

#include "PersonInfo.h"

#pragma once 

//////////////////////////////////////////////////////////////////////////
//	��Ƽ����Ʈ ��Ŷ Ÿ��
//////////////////////////////////////////////////////////////////////////

// [REQUEST] ��Ƽ����Ʈ ���۽� ���� üũ
class cltGameMsgRequest_PartyQuest_CheckStart
{
public:
	SI32 m_siPartyIndex;

public:
	cltGameMsgRequest_PartyQuest_CheckStart(SI32 siPartyIndex)
	{
		ZeroMemory(this, sizeof(cltGameMsgRequest_PartyQuest_CheckStart));

		m_siPartyIndex = siPartyIndex;
	}
};

// [RESPONSE] ��Ƽ����Ʈ ���۽� ���� ���
class cltGameMsgResponse_PartyQuest_CheckStart
{
public:
	bool m_bResult;

public:
	cltGameMsgResponse_PartyQuest_CheckStart(bool bResult)
	{
		ZeroMemory(this, sizeof(cltGameMsgResponse_PartyQuest_CheckStart));

		m_bResult = bResult;
	}
};


// [REQUEST] ��Ƽ����Ʈ ���� ��û
class cltGameMsgRequest_PartyQuest_Start
{
public:
	SI32 m_siPartyIndex;

public:
	cltGameMsgRequest_PartyQuest_Start(SI32 siPartyIndex)
	{
		ZeroMemory(this, sizeof(cltGameMsgRequest_PartyQuest_Start));

		m_siPartyIndex = siPartyIndex;
	}
};

// [RESPONSE] ��Ƽ����Ʈ ���� ��û
class cltGameMsgResponse_PartyQuest_Start
{
public:
	PartyQuest_UnitData m_PartyQuestData;
public:
	cltGameMsgResponse_PartyQuest_Start(PartyQuest_UnitData* pPartyQuestData)
	{
		ZeroMemory(this, sizeof(cltGameMsgResponse_PartyQuest_Start));
		CopyMemory(&m_PartyQuestData, pPartyQuestData, sizeof(PartyQuest_UnitData));
	}
};

// [RESPONSE] ��Ƽ����Ʈ ���� ��û
class cltGameMsgResponse_PartyQuest_Update
{
public:
	bool				m_bClear;
	PartyQuest_UnitData m_PartyQuestData;
	DWORD				m_dwQuestTime;
	
public:
	cltGameMsgResponse_PartyQuest_Update(bool bClear, PartyQuest_UnitData* pPartyQuestData, DWORD dwQuestTime)
	{
		ZeroMemory(this, sizeof(cltGameMsgResponse_PartyQuest_Update));

		m_bClear = bClear;
		m_dwQuestTime = dwQuestTime;
		CopyMemory(&m_PartyQuestData, pPartyQuestData, sizeof(PartyQuest_UnitData));
	}
};
	
// [RESPONSE] ��Ƽ����Ʈ ����
class cltGameMsgResponse_PartyQuest_GiveUp
{
public:
	SI32 m_siMessage;

public:
	cltGameMsgResponse_PartyQuest_GiveUp(SI32 siMessage)
	{
		ZeroMemory(this, sizeof(cltGameMsgResponse_PartyQuest_GiveUp));
		m_siMessage = siMessage;
	}
};

#endif



