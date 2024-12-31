#ifndef _PARTYOBJ_H_
#define _PARTYOBJ_H_

#include "PartyBaseInfo.h"

#include "..\SMLib\LibList\Obj.h"
#include "../Common/CommonHeader.h"
#include "../CommonLogic/PartyQuestMgr/PartyQuestMgr_Common.h"

#define ITEM_GETPATTERN_NORMAL		0
#define ITEM_GETPATTERN_ROTATION	1
#define ITEM_GETPATTERN_FINISH		2
#define ITEM_GETPATTERN_RANDOM		3

class cltItem;

struct stPartyUser
{
	bool bPartyStatus;			// ��Ƽ�� ������ ������, �ƴϸ� �� ����Ʈ�� �����̳ĸ� �������� ���ؼ�...
	bool bIsPartyLeader;		// ��Ƽ���̳�, ��Ƽ���̳�
	SI32 siPersonID;			// PersonID
	SI32 siCharUnique;			// ĳ���� unique ��	
	SI32 siExp;					// ����ġ ȹ�淮
	SI32 siLevel;				// ����
	
	bool bItemGetChance;				// ��Ƽ �÷��̽� �������� ȹ���� ��ȸ�� �����ֵ��� �÷���. ��ȿ�� ��Ƽ���� ���� �������� �ѹ��� ȹ���ϸ� �ʱ�ȭ�ȴ�.
	//cltCharPos clCharPos;			// ��ġ (���ε���, ����ǥ)
	
	stPartyUser()
	{
		Initialize();
	}

	void Initialize()
	{
		bPartyStatus = false;	// ��Ƽ�� ���������� ���� �����̹Ƿ�...
		bIsPartyLeader = false;
		siPersonID = 0;
		siCharUnique = 0;
		siLevel = 0;
		siExp = 0;
		bItemGetChance = true;
	//	clCharPos.Init();
	}

	bool IsSamePersonID( SI32 PersonID )
	{
		if ( bPartyStatus )
		{
			if ( siPersonID == PersonID ) 
			{
				return true;
			}
		}
		
		return false;
	}

	void Join( SI32 PersonID, SI32 CharUnique, bool IsPartyLeader, SI32 Level )
	{
		bPartyStatus = true;	// ��Ƽ�� ������(PersonID) ��������.
		bIsPartyLeader = IsPartyLeader;
		siPersonID = PersonID;
		siCharUnique = CharUnique;
		siLevel = Level;
	};

	void Set( stPartyUser *pUser )
	{
		memcpy( this, pUser, sizeof( stPartyUser ) );
	}
};

class CPartyObj : public CObj
{
public:
	CPartyObj( SI32 PartyObjIndex );
	~CPartyObj();
	
	void Initialize();
	void Destroy();	

	bool IsEmptyUserListExist();
	SI16 GetEmptyPartyUserListIndex();
	
	SI32 GetPartyIndex();	
	bool IsSamePartyIndex( SI32 PartyIndex );

	SI16 GetSamePersonIDIndex( SI32 PersonID );

	bool IsPartyLeader( SI32 PersonID );

	SI16 GetChangedLeaderIndex();

	SI32 CreateParty( SI32 PersonID, SI32 CharUnique, SI32 Level );
	SI16 JoinParty( SI32 PersonID, SI32 CharUnique, SI32 Level );
	SI16 LeaveParty( SI32 PersonID, SI32 *pRet );
	SI16 ForceLeaveParty( SI32 PersonID );

	stPartyUser *GetPartyUser( SI16 UserListIndex );

	SI16 GetPartyUserListIndex( SI32 CharUnique );
	SI32 GetCharUnique( SI32 PersonID );

	SI32 GetPartyLeaderUnique();

	SI16 GetPartyUserNum();
	
	void SetItemGetPattern( SI16 ItemGetPattern ){m_siItemGetPattern = ItemGetPattern;};
	SI16 GetItemGetPattern(){return m_siItemGetPattern;};
	
	SI32 GetItemGetCharUnique(SI32 * PartyList, SI16 arayMaxIndex);

	TCHAR *GetPartyName();

	bool SetPartyName( TCHAR *PartyName );
	 
	void SendPartyChat( SI32 SendCharUnique, TCHAR *Name, TCHAR *ChatData );

	void IncreaseExp( SI32 PersonID, SI32 Exp );
	void NotifyExp();
	void NotifyMovePosToPartyMember(SI32 MovedCharUnique,SI16 Xpos, SI16 Ypos,BOOL bWarpSwitch = TRUE ); // ĳ������ ��ġ�� ��Ƽ������ �˸���.[ ���� ]
	void NotifyGetIemToPartyMember(SI32 ItemGetCharUnique,cltItem * pclItem);
	void NotifyItemGetPatternToPartyMember(SI16 ItemGetPattern );
	void NotifyLevelUpToPatryMember(SI32 LevelUpCharUnique,SI32 Level);
private:
	SI32		m_siPartyIndex;								// ��Ƽ ������ ���� �ε���

	stPartyUser m_stPartyUserList[ MAX_PARTY_USER_NUM ];	// ��Ƽ ���� ����Ʈ, �޸� ���� ���ϹǷ� �׳� ����� �־���.	
	bool		bIsPartyStaus;								// ��Ƽ���̳�, ��Ƽ���� �ƴϳ�.

	SI16		m_siPartyUserNum;

	SI16		m_siItemGetPattern;							// [����] ��Ƽ�� ������ ȹ�� ���
	//SI16		m_siItemGetPersonIndex;					// ��ȯ��Ŀ��� ���� �������� �޾ƾ��� �۽��� ��Ƽ��  ���̵�

	TCHAR		m_strPartyName[ MAX_PARTY_NAME_LENGTH ];	// ��Ƽ �̸�

public:
	// [��ȣ] ��Ƽ����Ʈ ����
	PartyQuest_UnitData		m_PartyQuestInfo;	
	DWORD					m_dwStartTime;
	DWORD					m_dwElapseTime;
	DWORD					m_dwEndTime;
};

#endif