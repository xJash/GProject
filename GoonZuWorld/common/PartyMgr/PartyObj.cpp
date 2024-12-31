#include "PartyObj.h"
#include "..\Char\CharCommon\Char-Common.h"
#include "Char\CharManager\CharManager.h"

#include "..\CommonLogic\CommonLogic.h"
#include "..\CommonLogic\MsgType-System.h"
#include "..\CommonLogic\Msg\MsgType-Party.h"

extern cltCommonLogic *pclClient;

CPartyObj::CPartyObj( SI32 PartyIndex ) : CObj()
{
	m_siPartyIndex = PartyIndex;
	Initialize();

	m_dwStartTime	= 0;
	m_dwElapseTime	= 0;
	m_dwEndTime		= 0;
}

CPartyObj::~CPartyObj()
{
	m_dwStartTime	= 0;
	m_dwElapseTime	= 0;
	m_dwEndTime		= 0;

	Destroy();
}
	
void CPartyObj::Initialize()
{
	for ( SI32 i = 0; i < MAX_PARTY_USER_NUM; ++i )
	{
		m_stPartyUserList[ i ].Initialize();
	}

	TCHAR* pText = GetTxtFromMgr(3098);
	StringCchCopy ( m_strPartyName, MAX_PARTY_NAME_LENGTH, pText );

	bIsPartyStaus = false;		// ��Ƽ���� �ƴ�

	m_siPartyUserNum = 0;
	
	m_siItemGetPattern = ITEM_GETPATTERN_ROTATION; //��Ƽȹ�渷��
	//m_siItemGetPattern = ITEM_GETPATTERN_NORMAL;
//	m_siItemGetPersonIndex = 0;

	ZeroMemory(&m_PartyQuestInfo, sizeof(PartyQuest_UnitData));
	
	return;
}

void CPartyObj::Destroy()
{
	return;
}

bool CPartyObj::IsEmptyUserListExist()
{
	for ( SI16 i = 0; i < MAX_PARTY_USER_NUM; ++i )
	{
		if ( ! m_stPartyUserList[ i ].bPartyStatus )
		{
			return true;
		}
	}

	return false;
}

// ���� ���� -1 �̸� ��Ƽ���� �� �� ����
SI16 CPartyObj::GetEmptyPartyUserListIndex()
{
	for ( SI16 i = 0; i < MAX_PARTY_USER_NUM; ++i )
	{
		if ( ! m_stPartyUserList[ i ].bPartyStatus )
		{
			return i;
		}
	}

	return -1;
}

SI32 CPartyObj::GetPartyIndex()
{
	return m_siPartyIndex;
}


bool CPartyObj::IsSamePartyIndex( SI32 PartyIndex )
{
	if ( ! bIsPartyStaus )				// ��Ƽ ���� �ƴ϶�� üũ�� �ʿ� ����.
	{
		return false;
	}

	if ( PartyIndex == m_siPartyIndex )
	{
		return true;
	}

	return false;
}

SI16 CPartyObj::GetSamePersonIDIndex( SI32 PersonID )
{
	for ( SI16 i = 0; i < MAX_PARTY_USER_NUM; ++i )
	{
		if ( m_stPartyUserList[ i ].IsSamePersonID( PersonID ) )
		{
			return i;
		}
	}

	return -1;
}

bool CPartyObj::IsPartyLeader( SI32 PersonID )
{
	for ( SI16 i = 0; i < MAX_PARTY_USER_NUM; ++i )
	{
		if ( m_stPartyUserList[ i ].bIsPartyLeader && m_stPartyUserList[ i ].IsSamePersonID( PersonID ) )
		{
			return true;
		}
	}

	return false;
}


SI32 CPartyObj::GetPartyLeaderUnique()
{
	for ( SI16 i = 0; i < MAX_PARTY_USER_NUM; ++i )
	{
		if(m_stPartyUserList[i].bIsPartyLeader)
			return m_stPartyUserList[i].siCharUnique;
	}
	return 0;
}

SI16 CPartyObj::GetChangedLeaderIndex()
{
	for ( SI16 i = 0; i < MAX_PARTY_USER_NUM; ++i )
	{
		if ( m_stPartyUserList[ i ].bPartyStatus )
		{
			m_stPartyUserList[ i ].bIsPartyLeader = true;		// ��Ƽ������ �Ӹ�
			return i;
		}
	}

	return -1;
}

SI32 CPartyObj::CreateParty( SI32 PersonID, SI32 CharUnique, SI32 Level )
{
	m_stPartyUserList[ 0 ].Join( PersonID, CharUnique, true, Level );		// ��Ƽ �����ڴ� ���� ���� ��ġ�ϹǷ�...
	
//	m_siItemGetPersonIndex = 0;
	    
	bIsPartyStaus = true;

	++m_siPartyUserNum;

	return GetPartyIndex();
}

SI16 CPartyObj::JoinParty( SI32 PersonID, SI32 CharUnique, SI32 Level )
{
	SI16 EmptyListIndex = GetEmptyPartyUserListIndex();

	if ( EmptyListIndex < 0 )
	{
		return -1;
	}
	
	SI16 SamePersonIndex = GetSamePersonIDIndex( PersonID );

	if ( SamePersonIndex < 0 )
	{
		m_stPartyUserList[ EmptyListIndex ].Join( PersonID, CharUnique, false, Level );		// ��Ƽ���� �ƴϹǷ�, false
		
		++m_siPartyUserNum;

		return EmptyListIndex;
	}
	else
	{
		m_stPartyUserList[ SamePersonIndex ].Join( PersonID, CharUnique, false, Level );

		return SamePersonIndex;
	}	
}

SI16 CPartyObj::LeaveParty( SI32 PersonID, SI32 *pRet )
{
	SI16 SamePersonIDIndex = GetSamePersonIDIndex( PersonID );

	if ( SamePersonIDIndex < 0 )
	{
		return -1;
	}

	--m_siPartyUserNum;

	// ��Ƽ���� ���̻� ���� ���� ��Ƽ�� �����ؾ� �ϹǷ�
	if ( m_siPartyUserNum < 2 )
	{
		*pRet = SamePersonIDIndex;
		return PARTY_DELETE;
	}

	// ��Ƽ���̶�� ��Ƽ�� �Ѱ� �־�� �ϹǷ�..
	if ( m_stPartyUserList[ SamePersonIDIndex ].bIsPartyLeader )
	{
		bool bFind = false;

		for ( SI16 i = 1; i < MAX_PARTY_USER_NUM; ++i )
		{
			if ( m_stPartyUserList[i].bPartyStatus && m_stPartyUserList[i].bIsPartyLeader == false )
			{
				SI32 CharUnique = m_stPartyUserList[i].siCharUnique;

				if ( CharUnique < 1 )
				{
					continue;
				}

				SI32 id = pclClient->pclCM->GetIDFromCharUnique( CharUnique );
				
				if ( id < 1 )
				{
					continue;
				}
				else
				{
					bFind = true;

					*pRet = i;
					m_stPartyUserList[ i ].bIsPartyLeader = true;	// ��Ƽ�� �ٲ����.


					// SamePersonIDIndex �� 0 ��
					m_stPartyUserList[ SamePersonIDIndex ].Initialize();
					m_stPartyUserList[ 0 ].Set( &m_stPartyUserList[ i ] );
					m_stPartyUserList[ i ].Initialize();
					break;
				}
			}
		}

		if ( bFind )
		{
			return PARTY_CHANGE_LEADER;
		}
		else
		{
			*pRet = SamePersonIDIndex;
			return PARTY_DELETE;
		}
	}

	m_stPartyUserList[ SamePersonIDIndex ].Initialize();
	*pRet = SamePersonIDIndex;

	return SamePersonIDIndex;
}

SI16 CPartyObj::ForceLeaveParty( SI32 PersonID )
{
	SI16 SamePersonIDIndex = GetSamePersonIDIndex( PersonID );

	if ( SamePersonIDIndex < 0 )
	{
		return -1;
	}

	m_stPartyUserList[ SamePersonIDIndex ].Initialize();

	--m_siPartyUserNum;

	return SamePersonIDIndex;
}

stPartyUser *CPartyObj::GetPartyUser( SI16 UserListIndex )
{
	return &m_stPartyUserList[ UserListIndex ];
}

SI16 CPartyObj::GetPartyUserListIndex( SI32 CharUnique )
{
	for ( SI16 i = 0; i < MAX_PARTY_USER_NUM; ++i )
	{
		if ( m_stPartyUserList[ i ].bPartyStatus && m_stPartyUserList[ i ].siCharUnique == CharUnique )
		{
			return i;
		}
	}

	return -1;
}

SI32 CPartyObj::GetCharUnique( SI32 PersonID )
{
	for ( SI16 i = 0; i < MAX_PARTY_USER_NUM; ++i )
	{
		if ( m_stPartyUserList[ i ].bPartyStatus && m_stPartyUserList[ i ].siPersonID == PersonID )
		{
			return m_stPartyUserList[ i ].siCharUnique;
		}
	}

	return -1;
}

SI16 CPartyObj::GetPartyUserNum()
{
	return m_siPartyUserNum;
}

SI32 CPartyObj::GetItemGetCharUnique(SI32 * PartyList, SI16 arayMaxIndex)	
{	//[����] ��ȯȹ�� ��Ŀ��� �������� ������ ��Ƽ���� ĳ��������ũ�� ��´�.
	// ���ڴ� ���� ���� �ʿ� �ִ� ��Ƽ���� ����Ʈ�̴�.
	
	if(PartyList == NULL || arayMaxIndex <= 0 || arayMaxIndex > MAX_PARTY_USER_NUM)
		return -1;	

    for(SI16 i = 0; i< MAX_PARTY_USER_NUM; i++)	
	{	
		if( m_stPartyUserList[i].bPartyStatus && m_stPartyUserList[i].bItemGetChance) // ��Ƽ���̰�,�������� ȹ���� ��ȸ�� �����ְ�
		{			
			for(SI16 j = 0; j <  arayMaxIndex; j++) //������ ȹ�� ��ȿ ����Ʈ �ȿ� ���ԵǾ� �ִٸ�
			{
				if(PartyList[j] ==  m_stPartyUserList[i].siCharUnique)
				{  // CharUnique �� �����ϰ� ������ ���� ��ȸ�� ���ش�.
					m_stPartyUserList[i].bItemGetChance = false;
					return m_stPartyUserList[i].siCharUnique ;
				}
			}			
		}	
	}
	
	// ��ȿ�� ��Ƽ�� ����� �������� ���� ��ȸ�� ���� ����� ������. ��ȿ��Ƽ���� ������ ȹ���ȸ �ʱ�ȭ
	
	SI32 returnVal = -1;

	for(SI16 i = 0; i< MAX_PARTY_USER_NUM; i++)	
	{	
		if( m_stPartyUserList[i].bPartyStatus && m_stPartyUserList[i].bItemGetChance == false) // ��Ƽ���̰� ȹ���ȸ�� ���ٸ�
		{			
			for(SI16 j = 0; j <  arayMaxIndex; j++) //������ ȹ�� ��ȿ ����Ʈ �ȿ� ���ԵǾ� �ִٸ�
			{
				if(PartyList[j] ==  m_stPartyUserList[i].siCharUnique)
				{
					m_stPartyUserList[i].bItemGetChance = true;

					// �������� ĳ���� ����ũ���� ���� �����Ǿ� ���� �ʴٸ� �ϳ� �־��� �׸��� �ٽ� false
					if( returnVal <= 0)
					{
						m_stPartyUserList[i].bItemGetChance = false;
						returnVal = m_stPartyUserList[i].siCharUnique;					
					}

                    break;
				}
			}			
		}	
	}

	// ��ȸ�� �ʱ�ȭ�� ������
	// �������� ���� ĳ���� ����ũ ���� �����Ǿ���.

	return returnVal;	
}


TCHAR *CPartyObj::GetPartyName()
{
	if ( ! bIsPartyStaus )				// ��Ƽ ���� �ƴ϶�� üũ�� �ʿ� ����.
	{
		return NULL;
	}

	return m_strPartyName;
}

bool CPartyObj::SetPartyName( TCHAR *PartyName )
{
	if ( PartyName == NULL || _tcslen( PartyName ) < 1 )
	{
		return false;
	}

	MStrCpy( m_strPartyName, PartyName, MAX_PARTY_NAME_LENGTH );

	return true;
}

void CPartyObj::SendPartyChat( SI32 SendCharUnique, TCHAR *Name, TCHAR *ChatData )
{
	if ( Name == NULL || _tcslen( Name ) < 1 || ChatData == NULL || _tcslen( ChatData ) < 1 )
	{
		return;
	}

	cltGameMsgResponse_Chat clChat(SendCharUnique, CHATMODE_PARTY, (TCHAR*)Name, ChatData );
	cltMsg clMsg(GAMEMSG_RESPONSE_CHAT, clChat.siDataSize, (BYTE*)&clChat);

	for ( SI32 i = 0; i < MAX_PARTY_USER_NUM; ++i )
	{		
		if ( m_stPartyUserList[ i ].bPartyStatus && pclClient->pclCM->IsValidID( m_stPartyUserList[ i ].siCharUnique ) )
		{
			pclClient->pclCM->CR[ m_stPartyUserList[ i ].siCharUnique ]->SendNetMsg( (sPacketHeader*)&clMsg );
		}
	}


	return;
}

void CPartyObj::IncreaseExp( SI32 PersonID, SI32 Exp )
{
	for ( SI32 i = 0; i < MAX_PARTY_USER_NUM; ++i )
	{
		if ( m_stPartyUserList[ i ].bPartyStatus && m_stPartyUserList[ i ].siPersonID == PersonID )
		{
			m_stPartyUserList[ i ].siExp += Exp;
		}
	}
	return;
}

void CPartyObj::NotifyExp()
{
	for ( SI32 i = 0; i < MAX_PARTY_USER_NUM; ++i )
	{
		if ( m_stPartyUserList[ i ].bPartyStatus && pclClient->pclCM->IsValidID( m_stPartyUserList[ i ].siCharUnique ) )
		{
			for ( int j = 0; j < MAX_PARTY_USER_NUM; ++j )
			{
				if ( m_stPartyUserList[ j ].bPartyStatus && pclClient->pclCM->IsValidID( m_stPartyUserList[ j ].siCharUnique ) )
				{
					cltGameMsgResponse_Party_NotifyExp clParty_NotifyExp( m_stPartyUserList[ j ].siCharUnique, j, m_stPartyUserList[ j ].siExp );
					cltMsg clMsg(GAMEMSG_RESPONSE_PARTY_NOTIFYEXP, sizeof(clParty_NotifyExp), (BYTE*)&clParty_NotifyExp);

					pclClient->pclCM->CR[ m_stPartyUserList[ i ].siCharUnique ]->SendNetMsg( (sPacketHeader*)&clMsg );
				}
			}
		}
	}
	return;
}

void CPartyObj::NotifyMovePosToPartyMember(SI32 MovedCharUnique, SI16 Xpos, SI16 Ypos, BOOL bWarpSwitch)
{
	WRITE_MEMLOG( 140, 1, 0, 0 );

	if(pclClient->pclCM->IsValidID(MovedCharUnique) == false) return;

	if(pclClient->pclCM->CR[MovedCharUnique]->siPartyIndex != m_siPartyIndex ) return;

    cltCharPos clCharPos( pclClient->pclCM->CR[MovedCharUnique]->GetMapIndex(), Xpos , Ypos);

 	for(SI16 i = 0; i < MAX_PARTY_USER_NUM ; i++)
	{
		if( m_stPartyUserList[i].bPartyStatus && pclClient->pclCM->IsValidID(m_stPartyUserList[i].siCharUnique) )
		{
			//  ������ ���� ��ġ �˷��ִ°� �ƴ϶�� ( �̵����� ���� ��ġ�˸��̶��)
			if( bWarpSwitch == FALSE)
			{
 				if( m_stPartyUserList[i].siCharUnique == MovedCharUnique)
 					continue;

				//�ٸ����̸� ��ġ�� �˷��� �ʿ䰡 ����.
				if(pclClient->pclCM->CR[m_stPartyUserList[i].siCharUnique]->GetMapIndex() != pclClient->pclCM->CR[MovedCharUnique]->GetMapIndex() ) 
					continue;
				
				// ���ÿ��� �ȿ� �ִٸ� ��ġ�� �̹� �˰� �����Ƿ� �����ʿ䰡 ����. (���ÿ��� ���� -> 15 ���� ����)
				if(max(TABS(pclClient->pclCM->CR[m_stPartyUserList[i].siCharUnique]->GetX() - pclClient->pclCM->CR[MovedCharUnique]->GetX()),
					TABS(pclClient->pclCM->CR[m_stPartyUserList[i].siCharUnique]->GetY() - pclClient->pclCM->CR[MovedCharUnique]->GetY())) < 20)
						continue;				

			}

			cltGameMsgResponse_Party_PartyUserPos clinfo( MovedCharUnique ,&clCharPos);
			cltMsg clMsg(GAMEMSG_RESPONSE_PARTY_PARTYUSERPOS, sizeof(clinfo),(BYTE*)&clinfo);
			pclClient->pclCM->CR[m_stPartyUserList[i].siCharUnique]->SendNetMsg((sPacketHeader*)&clMsg);
		}
	}
	
	return;
}

void CPartyObj::NotifyGetIemToPartyMember(SI32 ItemGetCharUnique,cltItem * pclItem)
{	
	WRITE_MEMLOG( 140, 2, 0, 0 );

	if(pclClient->pclCM->IsValidID(ItemGetCharUnique) == false) return;

	if(pclClient->pclCM->CR[ItemGetCharUnique]->siPartyIndex != m_siPartyIndex ) return;
	
	if(pclItem == NULL) return;


	
	for ( SI32 i = 0; i < MAX_PARTY_USER_NUM; ++i )
	{
		if ( m_stPartyUserList[ i ].bPartyStatus && pclClient->pclCM->IsValidID( m_stPartyUserList[ i ].siCharUnique ) )
		{
			//�ڽſ��Դ� ������ �ʴ´�
			if( m_stPartyUserList[i].siCharUnique == ItemGetCharUnique)
				continue;
			
			cltGameMsgResponse_Party_NotifyItemGet clinfo(  ItemGetCharUnique , pclItem );
			cltMsg clMsg(GAMEMSG_RESPONSE_PARTY_NOTIFYITEMGET,sizeof(clinfo), (BYTE*)&clinfo);
			pclClient->pclCM->CR[m_stPartyUserList[i].siCharUnique]->SendNetMsg((sPacketHeader*)&clMsg);
		}
	}
}

void CPartyObj::NotifyItemGetPatternToPartyMember(SI16 ItemGetPattern )
{
	cltGameMsgResponse_Party_ChangeItemGetPattern clinfo(ItemGetPattern);
	cltMsg clMsg(GAMEMSG_RESPONSE_PARTY_CHANGEITEMGETPATTERN,sizeof(clinfo),(BYTE*)&clinfo);

	for ( SI16 i = 0; i < MAX_PARTY_USER_NUM; ++i )
	{
		if ( m_stPartyUserList[ i ].bPartyStatus && pclClient->pclCM->IsValidID( m_stPartyUserList[ i ].siCharUnique ) )
		{
			pclClient->pclCM->CR[ m_stPartyUserList[ i ].siCharUnique ]->SendNetMsg((sPacketHeader*)&clMsg );
		}
	}
}

void CPartyObj::NotifyLevelUpToPatryMember(SI32 LevelUpCharUnique, SI32 Level)
{
	cltGameMsgResponse_Party_NotifyLevelUp clinfo(LevelUpCharUnique,Level);
	cltMsg clMsg(GAMEMSG_RESPONSE_PARTY_NOTIFYLEVELUP,sizeof(clinfo),(BYTE*)&clinfo);

	for ( SI16 i = 0; i < MAX_PARTY_USER_NUM; ++i )
	{
		if ( m_stPartyUserList[ i ].bPartyStatus && pclClient->pclCM->IsValidID( m_stPartyUserList[ i ].siCharUnique ) )
		{
			pclClient->pclCM->CR[ m_stPartyUserList[ i ].siCharUnique ]->SendNetMsg((sPacketHeader*)&clMsg );
		}
	}
}

