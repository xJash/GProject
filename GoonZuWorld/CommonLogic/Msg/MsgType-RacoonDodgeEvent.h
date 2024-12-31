//Switch_10MonthEvent_RacoonDodge
#ifndef _MSGTYPERACOONDODGEEVENT_H_
#define _MSGTYPERACOONDODGEEVENT_H_

#include "..\..\Common\CommonHeader.h"
#include "../../../DBManager/GameDBManager_World/dbMsg.h"

// ���� �̺�Ʈ ���� 
class cltGameMsgRequest_ReservationEvent	
{
public:
	SI32 siPersonID	;

	cltGameMsgRequest_ReservationEvent( SI32 PersonID )
	{
		siPersonID = PersonID;
	}
};
// ������ ���� ����� ����Ʈ�� �����ش�.
class cltGameMsgResponse_ReservationEvent
{
public:
	SI32 siPersonID	;

	cltGameMsgResponse_ReservationEvent( SI32 PersonID )
	{
		siPersonID = PersonID;
	}
};
// ���� �̺�Ʈ�� �� ���� ���� ���� 
class cltGameMsgReQuest_Request_PlayEvent
{
public:
	SI32 siPersonID	;

	cltGameMsgReQuest_Request_PlayEvent( SI32 PersonID )
	{
		siPersonID = PersonID;
	}
};
// ���� �̺�Ʈ�� �� ���� ���� ���� 
class cltGameMsgResponse_Request_PlayEvent
{
public:
	SI32 siPersonID	;

	cltGameMsgResponse_Request_PlayEvent( SI32 PersonID )
	{
		siPersonID = PersonID;
	}
};
// ���ڸ��������ϴٿ����� �Ҽ� �����ϴ�.
class cltGameMsgRequest_Cannot_Reservation_NotEmptyList
{
public:
	SI32 siPersonID	;

	cltGameMsgRequest_Cannot_Reservation_NotEmptyList( SI32 PersonID )
	{
		siPersonID = PersonID;
	}
};

class cltGameMsgResponse_Cannot_Reservation_NotEmptyList
{
public:
	SI32 siPersonID	;

	cltGameMsgResponse_Cannot_Reservation_NotEmptyList( SI32 PersonID )
	{
		siPersonID = PersonID;
	}
};
// 5������ ���� �޼����� ������
class cltGameMsgResponse_Remain5Seceond
{
public:
	SI32 siPersonID	;

	cltGameMsgResponse_Remain5Seceond( SI32 PersonID )
	{
		siPersonID = PersonID;
	}
};
// 5�� ��� ���� ����
class cltGameMsgRequest_RacoonDodgeEveent_StartGame
{
public:
	SI32 siPersonID	;

	cltGameMsgRequest_RacoonDodgeEveent_StartGame( SI32 PersonID )
	{
		siPersonID = PersonID;
	}
};

class cltGameMsgResponse_RacoonDodgeEveent_StartGame
{
public:
	SI32 siPersonID	;

	cltGameMsgResponse_RacoonDodgeEveent_StartGame( SI32 PersonID )
	{
		siPersonID = PersonID;
	}
};
// ���ฮ��Ʈ�� ��û�Ѵ�
class cltGameMsgRequest_ReserveList
{
public:
	SI32 siPersonID	;

	cltGameMsgRequest_ReserveList( SI32 PersonID )
	{
		siPersonID = PersonID;
	}
};
// ���ฮ��Ʈ�� ������.
class cltGameMsgResponse_ReserveList
{
public:
	ReserveData	clInfo[MAX_RESERVER_SHOW_NUM];

	cltGameMsgResponse_ReserveList( ReserveData* Listinfo )
	{
		memcpy( clInfo, Listinfo, sizeof(clInfo))	;
	}
};
// 30�� Ÿ�� �޼����� ������
class cltGameMsgResponse_30Seceond
{
public:
	SI32 siPersonID	;
	SI32 siSecond	;

	cltGameMsgResponse_30Seceond( SI32 PersonID , SI32 Second)
	{
		siPersonID = PersonID;
		siSecond = Second;
	}
};
// 30�� Ÿ�� �� ���� �Ѵ� 
class cltGameMsgResponse_30Seceond_Clear
{
public:
	SI32 siPersonID	;

	cltGameMsgResponse_30Seceond_Clear( SI32 PersonID)
	{
		siPersonID = PersonID;
	}
};
// ���� ǥ�ø� �Ѵ�.
class cltGameMsgResponse_RoundCount
{
public:
	SI32 siPersonID	;
	SI32 siRound	;

	cltGameMsgResponse_RoundCount( SI32 PersonID , SI32 Round)
	{
		siPersonID = PersonID;
		siRound = Round;
	}
};
// ���� ǥ�ø� ���� �Ѵ� 
class cltGameMsgResponse_Round_Clear
{
public:
	SI32 siPersonID	;

	cltGameMsgResponse_Round_Clear( SI32 PersonID)
	{
		siPersonID = PersonID;
	}
};
#endif
