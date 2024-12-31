#include "ITZSendBuffer.h"
#include "ITZEncrypt.h"
#include "ITZSession.h"

ITZSendBuffer::ITZSendBuffer()
{

	m_pSendBuf = NULL;

	m_siBufSize = 0;

	InitializeCriticalSection( &m_cs );

}

ITZSendBuffer::~ITZSendBuffer()
{

	if( m_pSendBuf ) delete [] m_pSendBuf;
	m_pSendBuf = NULL;

	DeleteCriticalSection( &m_cs );
}


void ITZSendBuffer::ClearBuffer()
{

	EnterCriticalSection( &m_cs );	

	m_siBeginPos = 0;	
	m_siEndPos = 0;		
	m_siDataLen = 0;	

	m_bComplete = TRUE;

	LeaveCriticalSection( &m_cs );

}

void ITZSendBuffer::CreateSendBuffer( ITZSession* pSession, SI32 size, SI32 headerType, bool bEncrypt )
{

	EnterCriticalSection( &m_cs );

	if( m_pSendBuf ) delete [] m_pSendBuf;

	m_pSendBuf = new BYTE[ size ];

	m_siBufSize = size;
	
	m_siBeginPos = 0;
	m_siEndPos = 0;
	m_siDataLen = 0;

	m_bComplete = TRUE;

	m_headerType = headerType;

	m_pSession = pSession;
	m_bEncrypt = bEncrypt;
	
	LeaveCriticalSection( &m_cs );

}

BOOL ITZSendBuffer::GetSendParam( BYTE **pSendPtr, SI32 *psiDataLen )
{
	EnterCriticalSection( &m_cs );

	if( m_bComplete == FALSE || m_siDataLen == 0 ) {

		*psiDataLen = 0;

		LeaveCriticalSection( &m_cs );

		return FALSE;
	}

	*pSendPtr = m_pSendBuf + m_siBeginPos;

	if( m_siBeginPos < m_siEndPos ){
	
		*psiDataLen = m_siDataLen;
	
	} else {

		*psiDataLen = m_siBufSize - m_siBeginPos;
	}

	m_bComplete = FALSE;

	LeaveCriticalSection( &m_cs );

	return TRUE;
}

void ITZSendBuffer::Completion( SI32 siSentBytes )
{

	EnterCriticalSection( &m_cs );		

	m_siBeginPos += siSentBytes;
	m_siDataLen -= siSentBytes;

	if( m_siBeginPos == m_siBufSize ) m_siBeginPos = 0;

	m_bComplete = TRUE;


	LeaveCriticalSection( &m_cs );
}


BOOL ITZSendBuffer::Write( BYTE *pPacket )
{

	EnterCriticalSection( &m_cs );	

	BYTE encBuf[ 100000 ];

	if( m_bEncrypt )
	{
		m_pSession->GetEncrypt2()->Encode( pPacket, encBuf );
		pPacket = encBuf;		
	}

	// local_siLenA : �� ��Ŷ ���� 
	// local_siLenB : ������ ���� ��� ��Ŷ�� �� �κ� ����
	// local_siLenC : ������ ���� ��� ��Ŷ�� �� �κ� ����
	
	local_siLenA = (SI32)( *(UI16 *)pPacket );

	if( m_headerType == 1 ) {

		local_siLenA = ntohs( local_siLenA ) + 8;

	}

	// ���ۿ� ���� ������ ������ FALSE�� ��ȯ�Ѵ�
	if( local_siLenA > m_siBufSize - m_siDataLen ) {

		LeaveCriticalSection( &m_cs );
		
		return FALSE;	
	}

	if( m_siEndPos + local_siLenA > m_siBufSize ) {
		// ������ ���� �ؾ��ϸ�,
		
		local_siLenB = m_siBufSize - m_siEndPos;
		local_siLenC = local_siLenA - local_siLenB;

		memcpy( m_pSendBuf + m_siEndPos, pPacket, local_siLenB );

		pPacket += local_siLenB;

		memcpy( m_pSendBuf, pPacket, local_siLenC );

		m_siEndPos = local_siLenC;

	} else {
		// �ѹ��� ���� �����ϸ�,

		memcpy( m_pSendBuf + m_siEndPos, pPacket, local_siLenA );

		m_siEndPos += local_siLenA;

		if( m_siEndPos == m_siBufSize ) m_siEndPos = 0;
	}

	m_siDataLen += local_siLenA;
	
	LeaveCriticalSection( &m_cs );

	return TRUE;
}

