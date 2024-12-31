#ifndef _MSGTYPEQUEST_H
#define _MSGTYPEQUEST_H

//-------------------------------------------
// Ŭ���̾�Ʈ�� ����Ʈ ���� ���� �뺸. 
//-------------------------------------------
class cltGameMsgRequest_QuestStatus{
public:
	SI16	siQuestType;
	SI16	siQuestUnique;
	SI16	siQuestClearCond;
	SI16	siQuestPara1;
	SI16	siQuestPara2;

	cltGameMsgRequest_QuestStatus(SI16 questtype, SI16 questunique, SI16 questclearcond, SI16 para1, SI16 para2)
	{
		siQuestType			= questtype;
		siQuestUnique		= questunique;
		siQuestClearCond	= questclearcond;
		siQuestPara1		= para1;
		siQuestPara2		= para2;
	}
};

//-------------------------------------------
// ����Ʈ ��� ��û
//-------------------------------------------
class cltGameMsgRequest_CancelQuest{
public:
	SI16	siQuestType;
	SI16	siQuestUnique;

	cltGameMsgRequest_CancelQuest(SI16 questtype, SI16 questunique)
	{
		siQuestType			= questtype;
		siQuestUnique		= questunique;
	}
};


//-------------------------------------------
// ����Ʈ ���� ��û. 
//-------------------------------------------
class cltGameMsgRequest_QuestGoing{
public:
	SI16	siQuestType;
	SI16	siQuestUnique;
	SI16	siQuestStep;
	SI16	siSelectItemIndex;

	cltGameMsgRequest_QuestGoing(SI16 questtype, SI16 questunique, SI16 queststep, SI16 selectitemindex = 0)
	{
		siQuestType			= questtype;
		siQuestUnique		= questunique;
		siQuestStep			= queststep;
		siSelectItemIndex	= selectitemindex;
	}
};


#endif
