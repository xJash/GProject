#pragma once

#include <Directives.h>
#include "../../Common/CommonHeader.h"

class CPartyObj;

//////////////////////////////////////////////////////////////////////////
//	��Ƽ ����Ʈ �Ŵ���
//	Ŭ���̾�Ʈ�� �������� �������� ����.
//////////////////////////////////////////////////////////////////////////

const SI32 MAX_PARTYQUEST_CATEGORY_NUM	= 10;	//	��Ƽ����Ʈ ī�װ� ���ϳ��� �� ����
const SI32 MAX_PARTYQUEST_MISSION_NUM	= 10;	//	��Ƽ����Ʈ �̼��� �� ����
const SI32 MAX_PARTYQUEST_STEP_NUM		= 5;	//	��Ƽ����Ʈ STEP�� �� ����
const SI32 MAX_PARTYQUEST_REWARD_NUM	= 5;	//	��Ƽ����Ʈ ����������� �� ����

//////////////////////////////////////////////////////////////////////////
//	Data Files
//////////////////////////////////////////////////////////////////////////

// ��Ƽ����Ʈ�� ���� ������
struct PartyQuest_UnitData
{
	// ��Ƽ����Ʈ ������ ���� ��� ������	
	bool	m_bGoingQuest;
	SI32	m_siCategoryIndex;
	SI32	m_siMissionIndex;
	SI32	m_siQuestStep;
	SI32	m_siQuestType;
	SI32	m_siCondition1;
	SI32	m_siCondition2;
	SI32	m_siAmount;
	SI32	m_siRewardEXP;
	SI32	m_siRewardItemUnique[MAX_PARTYQUEST_REWARD_NUM];
	SI32	m_siRewardItemAmount[MAX_PARTYQUEST_REWARD_NUM];
	SI32	m_siRewardItemUseDay[MAX_PARTYQUEST_REWARD_NUM];
	SI32	m_siTimeLimit;

	PartyQuest_UnitData()
	{
		ZeroMemory(this, sizeof(PartyQuest_UnitData));
	}
};

// ��Ƽ����Ʈ�� ī�װ� ������
struct PartyQuest_CatecoryData
{
	// ī�װ� ���� ��� ������
	SI32	m_siIndex;
	SI32	m_siKind;
	SI32	m_siMinLevel;
	SI32	m_siMaxLevel;
	SI32	m_siMinUser;
	SI32	m_siMaxUser;
	SI32	m_siMissionCount;

	PartyQuest_UnitData m_PartyQuest_UnitData[MAX_PARTYQUEST_MISSION_NUM][MAX_PARTYQUEST_STEP_NUM];

	PartyQuest_CatecoryData(){ZeroMemory(this, sizeof(PartyQuest_CatecoryData));}
};


//////////////////////////////////////////////////////////////////////////
//	��Ƽ����Ʈ �Ŵ���
//////////////////////////////////////////////////////////////////////////

enum PARTYQUEST_CATEGORY_KIND
{
	PARTYQUEST_KIND_NONE,
	PARTYQUEST_KIND_NORMAL,
	PARTYQUEST_KIND_PCROOM,
	PARTYQUEST_KIND_END,
};

enum PARTYQUEST_TYPE
{
	PARTYQUEST_TYPE_NONE,
	PARTYQUEST_TYPE_HUNTING,
	PARTYQUEST_TYPE_MAKEITEM,
	PARTYQUEST_TYPE_CLEAR,
	PARTYQUEST_TYPE_END,
};


enum PARTYQUEST_UPDATE_STATE
{
	PARTYQUEST_UPDATE_STATE_NONE,
	PARTYQUEST_UPDATE_STATE_INCREASE,		// �ش� ����Ʈ ����
	PARTYQUEST_UPDATE_STATE_CLEAR,			// ����Ʈ Ŭ����
	PARTYQUEST_UPDATE_STATE_END,
};


class CPartyQuestMgr_Common
{
public:
	PartyQuest_CatecoryData m_PartyQuest_CategoryData[MAX_PARTYQUEST_CATEGORY_NUM];

public:
	bool	Initialize();	//	�Ŵ��� �ʱ�ȭ

	// About Load Resource 
	bool	LoadFiles_PartyQuest();
	SI32	QuestKindToInteger(TCHAR* szQuestKindToInteger);
	SI32	QuestTypeToInteger(TCHAR* szQuestType);
	SI32	QuestCondition1ToInteger(TCHAR* szQuestCondition1);
	SI32	QuestCondition2ToInteger(TCHAR* szQuestCondition2);


	
	PartyQuest_CatecoryData*GetPartyQuestCategoryData(SI32 siIndex = 0);
	PartyQuest_UnitData*	GetPartyQuestUnitData(SI32 siCategoryIndex, SI32 siMissionIndex, SI32 siStepIndex);							// ����Ʈ ���� ������ ��������
	PartyQuest_UnitData*	GetPartyQuestUnitData(SI32 siCategoryIndex, SI32 siMissionIndex, SI32 siStepIndex, TCHAR* szTitle);			// ����Ʈ ���� ������ Ÿ��Ʋ�� �Բ� ��������

	bool	DoCheckPartyQuest(CPartyObj* pPartyObject);	// ��Ƽ����Ʈ ���� ���� ���� üũ
	bool	CheckAlreadyPartyQuest(CPartyObj* pPartyObject);		// �̹� ����Ʈ������
	bool	CheckPartyLeader(CPartyObj* pPartyObject);	// ��Ƽ����Ʈ ��Ƽ�� üũ
	bool	CheckUserNum(CPartyObj* pPartyObject);		// ��Ƽ �ο� üũ
	bool	CheckLevel(CPartyObj* pPartyObject);		// ���� üũ
	bool	CheckPCRoom(CPartyObj* pPartyObject);		// �ǽù� ���� ����Ʈ üũ

	bool	SetPartyQuestData(PartyQuest_UnitData* pQuestData, SI32 siCategoryIndex, SI32 siMissionindex, SI32 siStep = 0);	// ��Ƽ������ class CPartyObj �� �ִ� ��Ƽ����Ʈ �����͸� Setting �մϴ�.
	

public:
	CPartyQuestMgr_Common();
	~CPartyQuestMgr_Common();
};



