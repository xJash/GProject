//-----------------------------------------------------------------------------
// 2005/09/20 ������
//-----------------------------------------------------------------------------

#include "NMsgShareBuffer.h"

NMsgShareBuffer::NMsgShareBuffer()
{
	m_hMapFile = NULL;
	m_pMapPtr = NULL;

	m_hMutex = NULL;
}

NMsgShareBuffer::~NMsgShareBuffer()
{
	Destroy();
}

void NMsgShareBuffer::Destroy()
{
	if( m_pMapPtr ) UnmapViewOfFile( m_pMapPtr );
	m_pMapPtr = NULL;

	if( m_hMutex ) CloseHandle( m_hMutex );
	m_hMutex = NULL;

	if( m_hMapFile ) CloseHandle( m_hMapFile );
	m_hMapFile = NULL;
}

// �޸� �� ���� ���۸� �����Ѵ� 
void NMsgShareBuffer::CreateMsgShareBuffer( int maxmsgcount, TCHAR *szName )
{
	Destroy();

	m_mapsize = sizeof( NMsgShareBufferInfo ) + sizeof( NMsg ) * maxmsgcount;

	TCHAR buf[ 256 ];

	StringCchPrintf(buf, 256, TEXT("MUTEX%s"), szName );

	m_hMutex = CreateMutex( NULL, FALSE, buf );
		
	StringCchPrintf(buf, 256, TEXT("MAP%s"), szName );

	m_hMapFile = CreateFileMapping( INVALID_HANDLE_VALUE, NULL, 
		PAGE_READWRITE, 0, m_mapsize, buf );

	m_pMapPtr = (BYTE *)MapViewOfFile( m_hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, m_mapsize );

	m_pInfo = (NMsgShareBufferInfo *)m_pMapPtr;

	m_pMsg = (NMsg *)( m_pMapPtr + sizeof( NMsgShareBufferInfo ) );


	WaitForSingleObject( m_hMutex, INFINITE );

	memcpy( buf, m_pInfo->name, 16 );
	buf[ 15 ] = NULL;

	if( _tcscmp( buf, NMSGSHAREBUFFER_NAME ) != 0 ) {
		// �޸� �� ���۰� �ʱ�ȭ �Ǿ� ���� �ʴٸ�, �ʱ�ȭ �Ѵ� 

		StringCchCopy(m_pInfo->name, 16 ,NMSGSHAREBUFFER_NAME );

		m_pInfo->size = maxmsgcount;
		m_pInfo->count = 0;
		m_pInfo->beginpos = 0;
		m_pInfo->endpos = 0;
	}

	ReleaseMutex( m_hMutex );
}

// �޽����� ���ۿ� �ִ´�
void NMsgShareBuffer::WriteMsg( NMsg *pMsg )
{
	WaitForSingleObject( m_hMutex, INFINITE );

	if( m_pInfo->count == m_pInfo->size ) {
		// ���۰� ���� á�ٸ�,

		if( m_pInfo->endpos == m_pInfo->size ) {
			// �� ���̶��,
			m_pInfo->endpos = 0;
		}

		m_pMsg[ m_pInfo->endpos ] = *pMsg;
		++m_pInfo->endpos;

		if( m_pInfo->beginpos == m_pInfo->size ) {
			// �� ���̶��,
			m_pInfo->beginpos = 0;
		} else {
			++m_pInfo->beginpos;
		}

	} else {

		if( m_pInfo->endpos == m_pInfo->size ) {
			// �� ���̶��,
			m_pInfo->endpos = 0;
		}

		m_pMsg[ m_pInfo->endpos ] = *pMsg;
		++m_pInfo->endpos;

		++m_pInfo->count;
	}

	ReleaseMutex( m_hMutex );
}

void NMsgShareBuffer::WriteMsg( int msg, int param1, int param2, int time )
{
	NMsg nmsg;

	nmsg.msg = msg;
	nmsg.param1 = param1;
	nmsg.param2 = param2;
	nmsg.time = time;

	WriteMsg( &nmsg );
}