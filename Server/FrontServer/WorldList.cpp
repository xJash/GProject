#include "WorldList.h"



cltWorldList::cltWorldList()
{
	m_count = 0;

	InitializeCriticalSection( &m_cs );
}

cltWorldList::~cltWorldList()
{
	DeleteCriticalSection( &m_cs );
}

void cltWorldList::Clear()
{
	EnterCriticalSection( &m_cs );

	m_count = 0;

	LeaveCriticalSection( &m_cs );
}


BOOL cltWorldList::GetWorldInfo( int worldId, WORLDINFO *pWorldInfo )
{
	EnterCriticalSection( &m_cs );

	BOOL ret = FALSE;

	if( worldId > 0 && worldId <= m_count ) {

		*pWorldInfo = m_worldlist[ worldId - 1 ];

		ret = TRUE;
	}

	LeaveCriticalSection( &m_cs );

	return ret;
}

BOOL cltWorldList::GetWorldInfo( TCHAR *szIP, WORLDINFO *pWorldInfo )
{

	EnterCriticalSection( &m_cs );

	BOOL ret = FALSE;

	for( int i = 0; i < m_count; ++i ) {

		if( _tcscmp( m_worldlist[ i ].baseinfo.gameserverip, szIP ) == 0 ) {

			*pWorldInfo = m_worldlist[ i ];
			ret = TRUE;
			break;
		}

	}

	LeaveCriticalSection( &m_cs );

	return ret;
}

BOOL cltWorldList::GetWorldInfoByServerID( SI32 siServerID, WORLDINFO *pWorldInfo )
{

	EnterCriticalSection( &m_cs );

	BOOL ret = FALSE;

	for( int i = 0; i < m_count; ++i ) {

		if( m_worldlist[ i ].baseinfo.siServerID == siServerID ) {

			*pWorldInfo = m_worldlist[ i ];
			ret = TRUE;
			break;
		}

	}

	LeaveCriticalSection( &m_cs );

	return ret;	
}


BOOL cltWorldList::GetWorldRefreshInfo( TCHAR *szIP,	GAMESERVER_REFRESHINFO *pRefreshInfo )
{
	EnterCriticalSection( &m_cs );

	BOOL ret = FALSE;

	for( int i = 0; i < m_count; ++i ) {

		if( _tcscmp( m_worldlist[ i ].baseinfo.gameserverip, szIP ) == 0 ) {

			*pRefreshInfo = m_worldlist[ i ].refreshinfo;

			ret = TRUE;
			break;
		}

	}

	LeaveCriticalSection( &m_cs );

	return ret;
}

BOOL cltWorldList::GetWorldRefreshInfoByServerID( SI32 siServerID, GAMESERVER_REFRESHINFO *pRefreshInfo )
{
	EnterCriticalSection( &m_cs );

	BOOL ret = FALSE;

	for( int i = 0; i < m_count; ++i ) {

		if( m_worldlist[ i ].baseinfo.siServerID == siServerID ) {

			*pRefreshInfo = m_worldlist[ i ].refreshinfo;

			ret = TRUE;
			break;
		}

	}

	LeaveCriticalSection( &m_cs );

	return ret;

}


void cltWorldList::SetWorldInfo( int worldId, WORLDINFO *pWorldInfo )
{
	EnterCriticalSection( &m_cs );

	if( worldId < 1 || worldId > m_count + 1 ) {
		LeaveCriticalSection( &m_cs );
		return;
	}

	if( worldId == m_count + 1 ) ++m_count;

	m_worldlist[ worldId - 1 ] = *pWorldInfo;
	
	m_worldlist[ worldId - 1 ].baseinfo.worldId = worldId;
	m_worldlist[ worldId - 1 ].refreshinfo.worldId = worldId;

	LeaveCriticalSection( &m_cs );
}


void cltWorldList::SetWorldRefreshInfo( int worldId, GAMESERVER_REFRESHINFO *pRefreshInfo )
{
	EnterCriticalSection( &m_cs );

	if( worldId < 1 || worldId > m_count ) {
		LeaveCriticalSection( &m_cs );
		return;
	}

	m_worldlist[ worldId - 1 ].refreshinfo = *pRefreshInfo;
	m_worldlist[ worldId - 1 ].refreshinfo.worldId = worldId;

	LeaveCriticalSection( &m_cs );
}


// response worldlist ��Ŷ�� �޾Ƽ� Ŭ������ �����Ѵ� ( ���� Ŭ���̾�Ʈ���� ��� )
void cltWorldList::SetWorldList( sResponse_WorldList *packet )
{
	EnterCriticalSection( &m_cs );	

	m_count = packet->usCount;

	for( int i = 0; i < m_count; ++i ) {

		m_worldlist[ i ] = packet->worldinfo[ i ];
	}

	LeaveCriticalSection( &m_cs );
}


// response world refresh all ��Ŷ�� �޾Ƽ� Ŭ������ �����Ѵ� ( ���� Ŭ���̾�Ʈ���� ��� )
void cltWorldList::SetWorldRefreshInfo( sNotify_WorldRefreshAll *packet )
{
	EnterCriticalSection( &m_cs );	

	for( int i = 0; i < packet->usCount; ++i ) {

		m_worldlist[ i ].refreshinfo = packet->refreshinfo[ i ];
	}

	LeaveCriticalSection( &m_cs );
}


// response worldlist ��Ŷ�� ����� �ش� ( ����Ʈ �������� ��� )
void cltWorldList::MakeWorldListPacket( sResponse_WorldList *packet )
{
	EnterCriticalSection( &m_cs );	

	packet->packetHeader.usSize = sizeof( sResponse_WorldList ) + ( m_count - 1 ) * sizeof( WORLDINFO );
	packet->packetHeader.usCmd = FRONTMSG_RESPONSE_WORLDLIST;

	packet->usCount = m_count;

	for( int i = 0; i < m_count; ++i ) {

		packet->worldinfo[ i ] = m_worldlist[ i ];
	}

	LeaveCriticalSection( &m_cs );
}

// response world refresh all ��Ŷ�� ����� �ش� ( ����Ʈ �������� ��� )
void cltWorldList::MakeWorldRefreshAllPacket( sNotify_WorldRefreshAll *packet )
{
	EnterCriticalSection( &m_cs );

	packet->packetHeader.usSize = sizeof( sNotify_WorldRefreshAll ) + ( m_count - 1 ) * sizeof( GAMESERVER_REFRESHINFO );
	packet->packetHeader.usCmd = FRONTMSG_NOTIFY_WORLDREFRESHALL;

	packet->usCount = m_count;

	for( int i = 0; i < m_count; ++i ) {

		packet->refreshinfo[ i ] = m_worldlist[ i ].refreshinfo;
	}
	

	LeaveCriticalSection( &m_cs );
}
