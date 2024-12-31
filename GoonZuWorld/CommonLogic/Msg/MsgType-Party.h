#ifndef _MSGTYPEPARTY_H_
#define _MSGTYPEPARTY_H_

#include "..\..\Common\CommonHeader.h"
#include "..\..\Common\PartyMgr\PartyBaseInfo.h"

/*
// ��Ƽ ���� ��û
class cltGameMsgRequest_Party_Create
{
public:	
	TCHAR strPartyName[ MAX_PARTY_NAME_LENGTH ];

	cltGameMsgRequest_Party_Create( TCHAR *PartyName )
	{
		strncpy( strPartyName, PartyName, MAX_PARTY_NAME_LENGTH - 1 );
		strPartyName[ MAX_PARTY_NAME_LENGTH - 1 ] = '\0';
	};	
};

// ��Ƽ ���� ����( ����� ��Ƽ�� �����Ǿ����� �˷��� )
class cltGameMsgResponse_Party_Create
{
public:
	SI32 siPartyIndex;
	TCHAR strPartyName[ MAX_PARTY_NAME_LENGTH ];

	cltGameMsgResponse_Party_Create( SI32 PartyIndex, TCHAR *PartyName )
	{
		siPartyIndex = PartyIndex;
		strncpy( strPartyName, PartyName, MAX_PARTY_NAME_LENGTH - 1 );
		strPartyName[ MAX_PARTY_NAME_LENGTH - 1 ] = '\0';
	}
};
*/

class cltGameMsgRequest_Party_ChangeItemGetPattern
{
public:
	SI16 siItemGetPattern;
	cltGameMsgRequest_Party_ChangeItemGetPattern( SI16 ItemGetPattern)
	{
		siItemGetPattern = ItemGetPattern;
	}
};

class cltGameMsgResponse_Party_ChangeItemGetPattern
{
public:
	SI16 siItemGetPattern;
	cltGameMsgResponse_Party_ChangeItemGetPattern( SI16 ItemGetPattern)
	{
		siItemGetPattern = ItemGetPattern;
	}
};

class cltGameMsgRequest_Party_CreateInvite
{
public:	
	SI32 siInvitedCharUnique;
	cltGameMsgRequest_Party_CreateInvite( SI32 InvitedCharUnique )
	{
		siInvitedCharUnique = InvitedCharUnique;
	}
};

class cltGameMsgResponse_Party_CreateInvite
{
public:
	TCHAR strCharName[ MAX_PLAYER_NAME ];			// ĳ���͸�
	SI32 siPartyLeaderPersonID;						// ��Ƽ���� �ɷ��� ����� PersonID

	cltGameMsgResponse_Party_CreateInvite( TCHAR *CharName, SI32 PartyLeaderPersonID )
	{
		MStrCpy( strCharName, CharName, MAX_PLAYER_NAME );

		siPartyLeaderPersonID = PartyLeaderPersonID;
	}
};

class cltGameMsgRequest_Party_CreateJoin
{
public:
	SI32 siLeaderPersonID;							// ��Ƽ���� �ɷ��� ����� PersonID

	cltGameMsgRequest_Party_CreateJoin( SI32 LeaderPersonID )
	{
		siLeaderPersonID = LeaderPersonID;
	}
};

class cltGameMsgResponse_Party_CreateJoin
{
public:
	SI32 siPartyIndex;
	SI32 siLeaderPersonID;
	SI32 siLeaderCharUnique;
	SI32 siLeaderLevel;
	TCHAR strLeaderCharName[ MAX_PLAYER_NAME ];

	cltCharPos clLeaderCharPos;

	SI32 siMemberPersonID;
	SI32 siMemberCharUnique;
	SI32 siMemberLevel;
	TCHAR strMemberCharName[ MAX_PLAYER_NAME ];

	cltCharPos clMemberCharPos;

	TCHAR szPartyName[ MAX_PARTY_NAME_LENGTH ];

	// ��Ƽ��Ī ����
	bool bIsPartyQuestParty;
	SI32 siPartyQuest_Category;
	SI32 siPartyQuest_Mission;

	cltGameMsgResponse_Party_CreateJoin( SI32 PartyIndex, SI32 LeaderPersonID, SI32 LeaderCharUnique, SI32 LeaderLevel, TCHAR *LeaderCharName,cltCharPos *LeaderCharPos , SI32 MemberPersonID, SI32 MemberCharUnique, SI32 MemberLevel, TCHAR *MemberCharName, cltCharPos* MemberCharPos,
		TCHAR* pszPartyName = NULL, bool bispartyquest = false, SI32 sicategory = -1, SI32 simission = -1)
	{
		ZeroMemory( this, sizeof(cltGameMsgResponse_Party_CreateJoin) );

		siPartyIndex = PartyIndex;
		siLeaderPersonID = LeaderPersonID;
		siLeaderCharUnique = LeaderCharUnique;
		siLeaderLevel = LeaderLevel;
		MStrCpy( strLeaderCharName, LeaderCharName, MAX_PLAYER_NAME );
		clLeaderCharPos.Set(LeaderCharPos);
		siMemberPersonID = MemberPersonID;
		siMemberCharUnique = MemberCharUnique;
		siMemberLevel = MemberLevel;
		MStrCpy( strMemberCharName, MemberCharName, MAX_PLAYER_NAME );
		clMemberCharPos.Set(MemberCharPos);

		if ( NULL != pszPartyName )
		{
			MStrCpy( szPartyName, pszPartyName, MAX_PARTY_NAME_LENGTH );
		}

		// ��Ƽ��Ī ����Ʈ ����
		bIsPartyQuestParty = bispartyquest;
		siPartyQuest_Category = sicategory;
		siPartyQuest_Mission = simission;
	}
};

// ��Ƽ���� �ʴ� ��û
class cltGameMsgRequest_Party_Invite
{
public:
	SI32 siInvitedCharUnique;		// �ʴ�� ����� ĳ���� ����ũ��
	SI32 siPartyIndex;				// �ʴ��ҷ��� ��Ƽ ��ȣ

	cltGameMsgRequest_Party_Invite( SI32 InvitedCharUnique, SI32 PartyIndex )
	{
		siInvitedCharUnique = InvitedCharUnique;
		siPartyIndex = PartyIndex;
	}
};

// ��Ƽ���� �ʴ��� ��󿡰� ����
// Ŭ���̾�Ʈ �󿡴� "��Ƽ�� ��𾾰�"���� ��Ƽ�� �ʴ��ϼ̽��ϴ�. ��Ƽ�� �����Ͻðڽ��ϱ�? �̷��� ǥ��
class cltGameMsgResponse_Party_Invite
{
public:
	TCHAR strCharName[ MAX_PLAYER_NAME ];			// ĳ���͸�
	SI32 siPartyLeaderPersonID;						// ��Ƽ�� PersonID
	SI32 siPartyIndex;								// ��Ƽ��ȣ

	cltGameMsgResponse_Party_Invite( TCHAR *CharName, SI32 PartyLeaderPersonID, SI32 PartyIndex )
	{
		siPartyIndex = PartyIndex;

		siPartyLeaderPersonID = PartyLeaderPersonID;

		MStrCpy( strCharName, CharName, MAX_PLAYER_NAME );
	}
};

class cltGameMsgRequest_Party_InviteReject
{
public:
	SI32 siPartyLeaderPersonID;

	cltGameMsgRequest_Party_InviteReject( SI32 PartyLeaderPersonID )
	{
		siPartyLeaderPersonID = PartyLeaderPersonID;
	}
};

class cltGameMsgResponse_Party_InviteReject
{
public:
	TCHAR strCharName[ MAX_PLAYER_NAME ];

	cltGameMsgResponse_Party_InviteReject( TCHAR *CharName )
	{
		if ( NULL != CharName )
		{
			memcpy( strCharName, CharName, MAX_PLAYER_NAME - 1 );
			strCharName[ MAX_PLAYER_NAME - 1 ] = NULL;
		}
	}
};


class cltGameMsgRequest_Party_Join
{
public:
	SI32 siPartyIndex;
	SI32 siPartyLeaderPersonID;

	cltGameMsgRequest_Party_Join( SI32 PartyIndex, SI32 PartyLeaderPersonID )
	{
		siPartyIndex = PartyIndex;
		siPartyLeaderPersonID = PartyLeaderPersonID;
	}
};

class cltGameMsgResponse_Party_Join
{
public:
	SI32 siPartyIndex;
	SI16 siUserListIndex;
	SI16 siItemGetPattern;
	TCHAR szPartyName[MAX_PARTY_NAME_LENGTH];

	cltGameMsgResponse_Party_Join( SI32 PartyIndex, SI16 UserListIndex, SI16 ItemGetPattern, TCHAR* pszPartyName = NULL )
	{
		ZeroMemory( this, sizeof(cltGameMsgResponse_Party_Join) );

		siPartyIndex = PartyIndex;
		siUserListIndex = UserListIndex;
		siItemGetPattern = ItemGetPattern;

		if ( NULL != pszPartyName )
		{
			memcpy( szPartyName, pszPartyName, sizeof(TCHAR)*MAX_PARTY_NAME_LENGTH );
		}
	}
};

class cltGameMsgRequest_Party_Leave
{
public:
	SI32 siPartyIndex;

	cltGameMsgRequest_Party_Leave( SI32 PartyIndex )
	{
		siPartyIndex =  PartyIndex;
	}
};

class cltGameMsgRequest_Party_ForceLeave
{
public:
	SI32 siPartyIndex;
	SI32 siForceLeaveCharUnique;		// ���������� ĳ���� ����ũ��

	cltGameMsgRequest_Party_ForceLeave( SI32 PartyIndex, SI32 ForceLeaveCharUnique )
	{
		siPartyIndex = PartyIndex;
		siForceLeaveCharUnique = ForceLeaveCharUnique;
	}
};

class cltGameMsgRequest_Party_AllUserList
{
public:
	SI32 siPartyIndex;

	cltGameMsgRequest_Party_AllUserList( SI32 PartyIndex )
	{
		siPartyIndex = PartyIndex;
	}
};

class cltGameMsgResponse_Party_Delete
{
public:
	SI32 siPartyIndex;

	cltGameMsgResponse_Party_Delete( SI32 PartyIndex )
	{
		siPartyIndex = PartyIndex;
	}
};

// �� �޽����� ��Ƽ���� ��ο��� ������ ��Ƽ���� �߰� �ƴٴ� ���� �˸��� ������ ��
// ��Ƽ�� ���� ��û�� ����� strCharName �� �ʿ� ������, ������ ��Ƽ������ �ʿ��ϹǷ�...
// �������� ���� ���ؼ� �̷��� ����.
class cltGameMsgResponse_Party_AddUser
{
public:	
	bool bPartyLeader;						// ��Ƽ���̳�, ��Ƽ���̳ĸ� �˷� �ֱ� ���Ѱ�
	SI16 siUserListIndex;					// ���� ����Ʈ���� ���°�� ������...	
	SI32 siCharUnique;						// �̹��� ��Ƽ�� �����ϰ� �� ������ ĳ���� ����ũ ��
	SI32 siLevel;							// ����
	TCHAR strCharName[ MAX_PLAYER_NAME ];	
	cltCharPos clCharPos;

	cltGameMsgResponse_Party_AddUser( SI16 UserListIndex, SI32 CharUnique, bool PartyLeader, TCHAR *CharName, SI32 Level, cltCharPos* pclCharPos  )
	{
		siUserListIndex = UserListIndex;
		siCharUnique = CharUnique;
		bPartyLeader = PartyLeader;
		MStrCpy( strCharName, CharName, MAX_PLAYER_NAME );
		siLevel = Level;
		clCharPos.Set(pclCharPos);
	}
};

class cltGameMsgResponse_Party_DelUser
{
public:
	SI16 siUserListIndex;					// ���� ����Ʈ ���°�� �ִ���.
	SI32 siCharUnique;						// ������ ������ ĳ���� ����ũ��

	cltGameMsgResponse_Party_DelUser( SI16 UserListIndex, SI32 CharUnique )
	{
		siUserListIndex = UserListIndex;
		siCharUnique = CharUnique;
	}
};

class cltGameMsgResponse_Party_ForceDelUser
{
public:
	SI16 siUserListIndex;					// ���� ����Ʈ ���°�� �ִ���.
	SI32 siCharUnique;						// ������ ������ ĳ���� ����ũ��

	cltGameMsgResponse_Party_ForceDelUser( SI16 UserListIndex, SI32 CharUnique )
	{
		siUserListIndex = UserListIndex;
		siCharUnique = CharUnique;
	}
};

class cltGameMsgResponse_Party_ChangeLeader
{
public:
	SI16 siUserListIndex;					// ���� ����Ʈ ���°�� �ִ���.
	SI32 siCharUnique;						// ��Ƽ���� �� ������ ĳ���� ����ũ��

	cltGameMsgResponse_Party_ChangeLeader( SI16 UserListIndex, SI32 CharUnique )
	{
		siUserListIndex = UserListIndex;
		siCharUnique = CharUnique;
	}
};

class cltGameMsgResponse_Party_NotifyExp
{
public:
	SI32 siCharUnique;
	SI16 siUserListIndex;	// ���� ����Ʈ���� ���°�� ������...
	SI32 siExp;

	cltGameMsgResponse_Party_NotifyExp( SI32 CharUnique, SI16 UserListIndex, SI32 Exp )
	{
		siCharUnique = CharUnique;
		siUserListIndex = UserListIndex;
		siExp = Exp;
	}
};

class cltGameMsgResponse_Party_NotifyItemGet
{
public:
	SI32 siCharUnique;
	cltItem clItem;

	cltGameMsgResponse_Party_NotifyItemGet( SI32 CharUnique, cltItem* pclItem)
	{
		siCharUnique = CharUnique;
		clItem.Set(pclItem);		
	}
};

class cltGameMsgResponse_Party_PartyUserPos
{
public:
	SI32 siCharUnique;
	cltCharPos clCharPos;

	cltGameMsgResponse_Party_PartyUserPos(SI32 CharUnique, cltCharPos* pclCharPos)
	{
		siCharUnique = CharUnique;
		clCharPos.Set(pclCharPos);
	}
};

class cltGameMsgResponse_Party_NotifyLevelUp
{
public:
	SI32 siCharUnique;
	SI32 siLevel;

	cltGameMsgResponse_Party_NotifyLevelUp(SI32 CharUnique, SI32 Level)
	{
		siCharUnique = CharUnique;
		siLevel = Level;
	}
};


//////////////////////////////////////////////////////////////////////////
// ��û�� ������ [��Ƽ�� -> ����] �� ó���� ���� �޼��� ������
//////////////////////////////////////////////////////////////////////////

//--------------------------------------------------
class cltGameMsgRequest_Party_WantJoin
{
public:
	SI32 siLeaderUnique;
	SI32 siMemberUnique;
	TCHAR szMemberName[ MAX_PLAYER_NAME ];

	cltGameMsgRequest_Party_WantJoin(SI32 leaderunique, SI32 memberunique, TCHAR* pszmembername)
	{
		ZeroMemory( this, sizeof(cltGameMsgRequest_Party_WantJoin) );

		siLeaderUnique = leaderunique;
		siMemberUnique = memberunique;
		if ( NULL != pszmembername )
		{
			memcpy( szMemberName, pszmembername, sizeof(TCHAR)*MAX_PLAYER_NAME );
		}
	}
};

class cltGameMsgResponse_Party_WantJoin
{
public:
	SI32 siLeaderUnique;
	SI32 siMemberUnique;
	TCHAR szMemberName[ MAX_PLAYER_NAME ];
	SI32 siPartyIndex;

	cltGameMsgResponse_Party_WantJoin(SI32 leaderunique, SI32 memberunique, TCHAR* pszmembername, SI32 partyindex)
	{
		ZeroMemory( this, sizeof(cltGameMsgResponse_Party_WantJoin) );

		siLeaderUnique = leaderunique;
		siMemberUnique = memberunique;
		if ( NULL != pszmembername )
		{
			memcpy( szMemberName, pszmembername, sizeof(TCHAR)*MAX_PLAYER_NAME );
		}
		siPartyIndex = partyindex;
	}
};

//---------------------------------------------------
class cltGameMsgRequest_Party_WantJoinResult
{
public:
	bool bResult;
	SI32 siLeaderUnique;
	SI32 siMemberUnique;
	SI32 siPartyIndex;

	cltGameMsgRequest_Party_WantJoinResult(bool result, SI32 leaderunique, SI32 memberunique, SI32 partyindex)
	{
		ZeroMemory( this, sizeof(cltGameMsgRequest_Party_WantJoinResult) );

		bResult = result;
		siLeaderUnique = leaderunique;
		siMemberUnique = memberunique;
		siPartyIndex = partyindex;
	}
};

class cltGameMsgResponse_Party_WantJoinResult
{
public:
	bool bResult;
	SI32 siLeaderUnique;
	SI32 siMemberUnique;
	SI32 siPartyIndex;
	TCHAR szPartyName[ MAX_PARTY_NAME_LENGTH ];

	cltGameMsgResponse_Party_WantJoinResult(bool result, SI32 leaderunique, SI32 memberunique, SI32 partyindex, TCHAR* pszpartyname)
	{
		ZeroMemory( this, sizeof(cltGameMsgResponse_Party_WantJoinResult) );

		bResult = result;
		siLeaderUnique = leaderunique;
		siMemberUnique = memberunique;
		siPartyIndex = partyindex;
		if ( NULL != pszpartyname )
		{
			memcpy( szPartyName, pszpartyname, sizeof(TCHAR)*MAX_PARTY_NAME_LENGTH );
		}
	}
};

#endif






