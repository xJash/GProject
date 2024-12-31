#include ".\bbbwaitlistmanager.h"

#include "../Server/Server.h"
#include "../Char/CharManager/CharManager.h"

#include "../CommonLogic/MsgType.h"
#include "../CommonLogic/Msg/MsgType-BokBulBok.h"





CBBBWaitListManager::CBBBWaitListManager(void)
{
	m_dwWaitListRefreshTime = 0;
}

CBBBWaitListManager::~CBBBWaitListManager(void)
{
	m_WaitList.clear();
}



//////////////////////////////////////////////////////////////////////////
bool CBBBWaitListManager::IsFull()
{
	SI16 siListLength = m_WaitList.size();
	if ( MAX_RESERVATION_NUM > siListLength )
	{
		return false;
	}

	return true;
}

bool CBBBWaitListManager::AddUser(SI32 siUserID, TCHAR* pszUserName)
{
	if ( true == _AlreadyExist( pszUserName ) ) return true; // ����� ����â�� �̹� �����ϰ� �ִ� ĳ���Ͷ��

	if ( m_WaitList.size() < MAX_RESERVATION_NUM )
	{
		_BBBWaitUserData pUserData;

		pUserData.siUserID = siUserID;
		MStrCpy( pUserData.szUserName, pszUserName, MAX_CHARACTER_NAME_LENGTH );

		m_WaitList.push_back( pUserData );
		return true;
	}
	else
	{
		return false;
	}
}

void CBBBWaitListManager::RemoveUser(SI32 siUserID)
{
	m_WLitr = m_WaitList.begin();

	while ( m_WaitList.end() != m_WLitr )
	{
		if ( siUserID == (*m_WLitr).siUserID )
		{
			WAITLIST::iterator itr = m_WLitr;
			++m_WLitr;
			m_WaitList.erase( itr );
			break;
		}
		else
		{
			++m_WLitr;
		}
	}
}

void CBBBWaitListManager::GetWaitList(_BBBWaitUserData* pWaitList)
{
	m_WLitr = m_WaitList.begin();

	int i = 0;
	while ( m_WaitList.end() != m_WLitr )
	{
		MStrCpy( pWaitList[i].szUserName, (*m_WLitr).szUserName, MAX_CHARACTER_NAME_LENGTH );

		++m_WLitr;
		++i;
	}
}

bool CBBBWaitListManager::_AlreadyExist(TCHAR* pszUserName)
{
	m_WLitr = m_WaitList.begin();

	while ( m_WaitList.end() != m_WLitr )
	{
		if ( 0 == _tcscmp( (*m_WLitr).szUserName, pszUserName ) )
		{
			return true;
		}

		++m_WLitr;
	}

	return false;
}

void CBBBWaitListManager::SubAction()
{
	cltServer* pServer = (cltServer*)pclClient;

	// 5�ʸ��� �ֱ������� ����� ����Ʈ ��ü�� �ѹ��� �˻��ؼ� ������ ������ ã�Ƴ� ���� �Ѵ�.
	if ( m_dwWaitListRefreshTime < pServer->CurrentClock )
	{
		_Refresh_UserList();
		m_dwWaitListRefreshTime = pServer->CurrentClock + 5000;		// 5�ʸ��� ���� (Ŭ��� �˷����� ����)
	}
}

void CBBBWaitListManager::_Refresh_UserList()
{	
	cltServer* pclServer = (cltServer*)pclClient;

	m_WLitr = m_WaitList.begin();
	while ( m_WaitList.end() != m_WLitr )
	{
		cltCharServer* pclChar = pclServer->pclCM->GetCharServer( (*m_WLitr).siUserID);

		if ( NULL == pclChar )
		{
			WAITLIST::iterator itr = m_WLitr;
			++m_WLitr;
			m_WaitList.erase( itr );
		}
		else
		{
			const TCHAR* pszCharName = pclChar->GetName();
			if ( 0 != _tcscmp(pszCharName, (*m_WLitr).szUserName) )
			{
				WAITLIST::iterator itr = m_WLitr;
				++m_WLitr;
				m_WaitList.erase( itr );
			}
			else
			{
				++m_WLitr;
			}
		}
	}
}

bool CBBBWaitListManager::WaitUserExist()
{
	m_WLitr = m_WaitList.begin();

	if ( m_WaitList.end() != m_WLitr )
	{
		cltServer* pServer = (cltServer*)pclClient;

		cltCharServer* pCharServer = pServer->pclCM->GetCharServer( (*m_WLitr).siUserID );
		if ( NULL != pCharServer )
		{
			const TCHAR* pszCharName = pCharServer->GetName();
			if ( 0 == _tcscmp( pszCharName, (*m_WLitr).szUserName ) )
			{
				return true;
			}
		}
		else	// ��� ����Ʈ�� �ִµ� ���� ������ �������� �ʴ� ĳ���̸� ����Ʈ���� ���� (�ΰ� �ߵ� �� �ߵ� �ؼ� ����ĳ���̴ϱ�)
		{
			// �� ĳ���� üũ���� ���� �׳� �ѹ濡 ����Ʈ ���δ� �˻�.
			_Refresh_UserList();
		}
	}

	// _Refresh_UserList() �Լ� ȣ���Ŀ��� ��⸮��Ʈ�� ������ ������ ������ �ϴ� ���� �������� false �����ϰ� ���� ������ üũ �ϵ��� �Ѵ�.
	return false;
}

void CBBBWaitListManager::Send_EnterMapQuestion()
{
	m_WLitr = m_WaitList.begin();

	if ( m_WaitList.end() != m_WLitr )
	{
		cltServer* pServer = (cltServer*)pclClient;

		cltCharServer* pCharServer = pServer->pclCM->GetCharServer( (*m_WLitr).siUserID );
		if ( NULL != pCharServer )
		{
			const TCHAR* pszCharName = pCharServer->GetName();
			if ( 0 == _tcscmp( pszCharName, (*m_WLitr).szUserName ) )
			{
				// Ŭ�� ���Һ� ���Ӹ����� �����ϰڳİ� �޼��� ����
				cltGameMsgResponse_BBB_WarpMapQuestion clinfo( (*m_WLitr).siUserID );
				cltMsg clMsg( GAMEMSG_RESPONSE_BBB_WARPMAPQUESTION, sizeof(clinfo), (BYTE*)&clinfo);
				pCharServer->SendNetMsg((sPacketHeader*)&clMsg);

				// �׸��� �� 1���� ����ڴ� ��⸮��Ʈ���� ����
				m_WaitList.erase( m_WLitr );
			}
		}
		else	// ��� ����Ʈ�� �ִµ� ���� ������ �������� �ʴ� ĳ���̸� ����Ʈ���� ���� (�ΰ� �ߵ� �� �ߵ� �ؼ� ����ĳ���̴ϱ�)
		{
			// �� ĳ���� üũ���� ���� �׳� �ѹ濡 ����Ʈ ���δ� �˻�.
			_Refresh_UserList();
		}
	}
}

SI32 CBBBWaitListManager::Get1stUserID()
{
	m_WLitr = m_WaitList.begin();

	if ( m_WaitList.end() != m_WLitr )
	{
		cltServer* pServer = (cltServer*)pclClient;

		cltCharServer* pCharServer = pServer->pclCM->GetCharServer( (*m_WLitr).siUserID );
		if ( NULL != pCharServer )
		{
			const TCHAR* pszCharName = pCharServer->GetName();
			if ( 0 == _tcscmp( pszCharName, (*m_WLitr).szUserName ) )
			{
				return (*m_WLitr).siUserID;
			}
		}
		else	// ��� ����Ʈ�� �ִµ� ���� ������ �������� �ʴ� ĳ���̸� ����Ʈ���� ���� (�ΰ� �ߵ� �� �ߵ� �ؼ� ����ĳ���̴ϱ�)
		{
			// �� ĳ���� üũ���� ���� �׳� �ѹ濡 ����Ʈ ���δ� �˻�.
			_Refresh_UserList();
		}
	}

	// _Refresh_UserList() �Լ� ȣ���Ŀ��� ��⸮��Ʈ�� ������ ������ ������ �ϴ� ���� �������� false �����ϰ� ���� ������ üũ �ϵ��� �Ѵ�.
	return 0;
}

