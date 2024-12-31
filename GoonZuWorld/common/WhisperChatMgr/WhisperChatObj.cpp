#include "WhisperChatObj.h"

#include "../Char/CharCommon/Char-Common.h"
#include "Char\CharManager\CharManager.h"

#include "..\CommonLogic\CommonLogic.h"

//--------------------------------------
// Common
//--------------------------------------
#include "PersonInfo.h"

extern cltCommonLogic *pclClient;

CWhisperChatObj::CWhisperChatObj( SI32 Index )
{
	m_siIndex = Index;

	Init();
}

CWhisperChatObj::~CWhisperChatObj()
{

}

void CWhisperChatObj::Init()
{
	++m_siCounter;

	if ( m_siCounter > 30000 )
	{
		m_siCounter = 0;
	}

	m_siMemberNum = 0;

#ifdef _SAFE_MEMORY
	m_stWhisperChatMemberList.ZeroMem();
#else
	memset( m_stWhisperChatMemberList, 0, sizeof( stWhisperChatMember ) * MAX_WHISPERCHAT_OBJ_USERNUM );
#endif

	return;
}

SI32 CWhisperChatObj::GetWhisperChatIndex()
{
	return m_siIndex;
}

// �ӼӸ�â ����
SI32 CWhisperChatObj::Create( SI32 CharID1, SI32 PersonID1, TCHAR *CharName1, SI32 CharID2, SI32 PersonID2, TCHAR *CharName2 )
{
	Init();

	m_stWhisperChatMemberList[ 0 ].Set( CharID1, PersonID1, CharName1 );
	m_stWhisperChatMemberList[ 1 ].Set( CharID2, PersonID2, CharName2 );

	 m_siMemberNum = 2;
	
	return m_siIndex;
}

bool CWhisperChatObj::IsCreated( SI32 PersonID1, SI32 PersonID2 )
{
	if ( m_siMemberNum != 2 )
	{
		return false;
	}

	bool bPerson1Find = false;
	bool bPerson2Find = false;

	for ( SI16 i = 0; i < MAX_WHISPERCHAT_OBJ_USERNUM; ++i )
	{
		if ( m_stWhisperChatMemberList[ i ].siPersonID == PersonID1 )
		{
			bPerson1Find = true;
		}
		else if ( m_stWhisperChatMemberList[ i ].siPersonID == PersonID2 )
		{
			bPerson2Find = true;
		}
	}

	if ( bPerson1Find && bPerson2Find )
	{
		return true;
	}
	
	return false;
}

// �Ѹ� �ʴ��ؼ� ������
bool CWhisperChatObj::AddMember( SI32 CharID, SI32 PersonID, TCHAR *CharName )
{
	SI16 EmptyListIndex = GetEmptyGroupListIndex();
	
	if ( EmptyListIndex < 0 )
	{
		return false;
	}

	m_stWhisperChatMemberList[ EmptyListIndex ].Set( CharID, PersonID, CharName );
	++m_siMemberNum;
	
	return true;
}

// �Ѹ� Ż���ؼ� ����
void CWhisperChatObj::DelMember( SI32 PersonID )
{
	for ( SI16 i = 0; i < MAX_WHISPERCHAT_OBJ_USERNUM; ++i )
	{
		if ( m_stWhisperChatMemberList[ i ].siPersonID == PersonID )
		{
			m_stWhisperChatMemberList[ i ].Init();
			--m_siMemberNum;
			break;
		}
	}

	return;
}

// ���� ��� �ִ� ���� �ִ��� üũ
SI16 CWhisperChatObj::GetEmptyGroupListIndex()
{
	for ( SI16 i = 0; i < MAX_WHISPERCHAT_OBJ_USERNUM; ++i )
	{
		if ( m_stWhisperChatMemberList[ i ].siPersonID == 0 )
		{
			return i;
		}
	}

	return -1;
}

// ���� �ӼӸ��� �������� ������� ����Ʈ
void CWhisperChatObj::GetWhisperChatMemberList( stWhisperChatMember *pWhisperChatMemberList )
{
	if ( pWhisperChatMemberList == NULL )
	{
		return;
	}

	SI32 i = 0;
#ifdef _SAFE_MEMORY
	for(i=0; i<MAX_WHISPERCHAT_OBJ_USERNUM; i++)			pWhisperChatMemberList[i].Set(&m_stWhisperChatMemberList[i]);
#else
	memcpy( pWhisperChatMemberList, m_stWhisperChatMemberList, sizeof( stWhisperChatMember ) * MAX_WHISPERCHAT_OBJ_USERNUM );
#endif

	return;
}

// �ӼӸ� ������
void CWhisperChatObj::SendWhisperChat( SI32 FromCharID, SI32 FromPersonID )
{
	return;
}

// �ӼӸ� ���� ����鿡�� �޽��� ������( �������� �޽��� ���� )
void CWhisperChatObj::SendMsgToWhisperChatMembers( sPacketHeader *pclMsg )
{
	SI32 CharID = 0;

	for ( SI16 i = 0; i < MAX_WHISPERCHAT_OBJ_USERNUM; ++i )
	{
		if ( m_stWhisperChatMemberList[ i ].siPersonID > 0 )
		{
			CharID = m_stWhisperChatMemberList[ i ].siCharID;
			
			if ( pclClient->pclCM->IsValidID( CharID ) &&
				pclClient->pclCM->CR[ CharID ]->pclCI->GetPersonID() == m_stWhisperChatMemberList[ i ].siPersonID
				)
			{
				pclClient->pclCM->CR[ CharID ]->SendNetMsg( (sPacketHeader*)pclMsg );
			}
		}
	}

	return;
}