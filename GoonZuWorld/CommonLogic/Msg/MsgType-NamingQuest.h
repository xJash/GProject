#pragma once 

class cltGameMsgRequest_NamingQuestStart
{
public:
	SI32 siIndex;
	SI32 siLevel;

	cltGameMsgRequest_NamingQuestStart( SI32 Index, SI32 Level )
	{
		siIndex = Index;
		siLevel = Level;
	}
};

// ��Ī ����Ʈ �Ϸ���.. �˸� �޼���
class cltGameMsgResponse_SetPersonNamingInfo
{
public:
	SI32 siIndex;
	SI32 siLevel;

	cltGameMsgResponse_SetPersonNamingInfo( SI32 index, SI32 level )
	{
		siIndex = index;
		siLevel = level;
	}
};
class cltGameMsgRequest_SetPeronCurrentNaming
{
public:
	SI32 siIndex;
	SI32 siLevel;

	cltGameMsgRequest_SetPeronCurrentNaming( SI32 index, SI32 level )
	{
		siIndex = index;
		siLevel = level;
	}

};
class cltGameMsgResponse_SetPersonCurrentNaming
{
public:
	SI32 siCharUnique;
	SI32 siIndex;
	SI32 siLevel;

	cltGameMsgResponse_SetPersonCurrentNaming( SI32 charunique, SI32 index, SI32 level )
	{
		siCharUnique = charunique;
		siIndex = index;
		siLevel = level;
	}
};