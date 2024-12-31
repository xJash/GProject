#ifndef _MSGTYPEHAPPYBEANQUEST_H_
#define _MSGTYPEHAPPYBEANQUEST_H_

//#include "../CommonLogic/Msg/MsgType-HappyBeanQuest.h"
//KHY - 0822 - ���Ǻ� ����Ʈ �߰�.
class cltGameMsgRequest_HappyBeanQuestStart
{
public:
	SI32 siQuestType;
	SI32 siQuestState;

	cltGameMsgRequest_HappyBeanQuestStart( SI32 QuestType, SI32 QuestState )
	{
		siQuestType = QuestType;
		siQuestState = QuestState;
	}
};

class cltGameMsgResponse_HappyBeanQuestStart_NO
{
public:
	//SI32 siQuestType;  //���߿� �ʿ��ϸ� �߰�����.
	SI32 siResult;

	cltGameMsgResponse_HappyBeanQuestStart_NO(SI32 Result )
	{
		//siQuestType = QuestType;
		siResult = Result;
	}
};


//-------------------------------------------------
// ���Ǻ� ����Ʈ�� �����Ǿ����� �˸���. 
//-------------------------------------------------
class cltGameMsgResponse_HappyBeanQuestStart_OK
{
public:
	cltQuestInfoCommon	clHappyBeanQuestInfo;

	cltGameMsgResponse_HappyBeanQuestStart_OK(cltQuestInfoCommon*	pclHappyBeanQuestInfo)
	{
		clHappyBeanQuestInfo.Set(pclHappyBeanQuestInfo);
	}
};


//-------------------------------------------------
// ���Ǻ� ����Ʈ ���� ���� �뺸 �޽���. 
//-------------------------------------------------
class cltGameMsgResponse_HappyBeanQuestReward
{
public:
	cltQuestRewardInfo clQuestRewardInfo;

	cltGameMsgResponse_HappyBeanQuestReward(cltQuestRewardInfo* pclinfo)
	{
		clQuestRewardInfo.Set(pclinfo);
	}
};

//-------------------------------------------------
// //KHY - 0906 - ���ӹ� �̺�Ʈ ����.
//-------------------------------------------------
class cltGameMsgResponse_EventCoupon
{
public:
	SI32 siEventCouponType;   //GAMEROOM_COUPON_EVENT =1
	SI32 siResult;

	cltGameMsgResponse_EventCoupon(SI32 eventcouponType, SI32 Result )
	{
		siEventCouponType = eventcouponType;
		siResult = Result;
	}
};
//�����̺�Ʈ [2007.09.10 �ռ���]
//class cltGameMsgResponse_AUCTIONEventCoupon
//{
//public:
//	SI32 siEventCouponType;   //AUCTION_CUPON_EVENT =2
//	SI32 siResult;
//
//	cltGameMsgResponse_AUCTIONEventCoupon(SI32 eventcouponType, SI32 Result )
//	{
//		siEventCouponType = eventcouponType;
//		siResult = Result;
//	}
//};


//-------------------------------------------------
// class : cltGameMsgRequest_MissionQuestStart
// desc  : �̼� ����Ʈ ����
//-------------------------------------------------
class cltGameMsgRequest_MissionQuest_Start
{
public:
	SI32 m_siMissionUnique;

	cltGameMsgRequest_MissionQuest_Start( SI32 siMissionUnique )
	{
		m_siMissionUnique = siMissionUnique;
	}
};


class cltGameMsgResponse_MissionQuest_Start
{
public:
	SI32					m_siMissionUnique;
	cltMissionQuestInfo		m_clMissionQuestInfo;

	cltGameMsgResponse_MissionQuest_Start( SI32 siMissionUnique, cltMissionQuestInfo* clMissionQuestInfo )
	{
		m_siMissionUnique	= siMissionUnique;
		m_clMissionQuestInfo.Set(clMissionQuestInfo);
	}
};


//-------------------------------------------------
// class : cltGameMsgRequest_MissionQuest_Accept
// desc  : �̼� ����Ʈ ����
//-------------------------------------------------
class cltGameMsgRequest_MissionQuest_Accept
{
public:
	SI32 m_siMissionUnique;

	cltGameMsgRequest_MissionQuest_Accept( SI32 siMissionUnique )
	{
		m_siMissionUnique = siMissionUnique;
	}
};

//-------------------------------------------------
// class : cltGameMsgRequest_MissionQuest_Cancel
// desc  : �̼� ����Ʈ ���
//-------------------------------------------------
class cltGameMsgRequest_MissionQuest_Cancel
{
public:
	SI32 m_siMissionUnique;

	cltGameMsgRequest_MissionQuest_Cancel( SI32 siMissionUnique )
	{
		m_siMissionUnique = siMissionUnique;
	}
};

//-------------------------------------------------
// class : cltGameMsgRequest_TreasureEvent_Npc_Kill
// desc  : ����ã�� �̺�Ʈ npc Ŭ�� �ߴ�. �̳��� �׿���!
//-------------------------------------------------
class cltGameMsgRequest_TreasureEvent_Npc_Kill
{
public:
	SI32 m_siNPC_CharUnique ;

	cltGameMsgRequest_TreasureEvent_Npc_Kill( SI32 siNPC_CharUnique )
	{
		m_siNPC_CharUnique = siNPC_CharUnique;
	}
};

// [����] : 2010�ų��̺�Ʈ - ���� '��'���� ����� ����Ʈ ���� ��Ŷ ������ �� �޼������� - ���� ���� ���� ������ �޼��� ������ 1�� ���̶� ���⿡ �Ż縮
class cltGameMsgRequest_2010NewYearEvent_QuestCancel
{
public:
	SI32 m_siPersonID;

	cltGameMsgRequest_2010NewYearEvent_QuestCancel( SI32 siPersonID )
	{
		m_siPersonID = siPersonID;
	}
};

class cltGameMsgResponse_GoonzuDayMissionClearReward
{
public:
	SI32 m_siPersonID;
	SI32 m_siExp;

	SI32 m_siItemUnique;
	SI16 m_siItemNum;

	cltGameMsgResponse_GoonzuDayMissionClearReward( SI32 siPersonID, SI32 siExp, SI32 siItemUnique, SI16 siItemNum )
	{
		ZeroMemory( this, sizeof(cltGameMsgResponse_GoonzuDayMissionClearReward) );

		m_siPersonID = siPersonID;
		m_siExp = siExp;
		m_siItemUnique = siItemUnique;
		m_siItemNum = siItemNum;
	}
};

#endif
