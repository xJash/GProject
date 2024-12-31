#include "ITZRecvBuffer.h"

ITZRecvBuffer::ITZRecvBuffer()
{
	m_pRecvBuf = NULL;

	m_pBasePtr = NULL;
	m_pBeginPtr = NULL;
	m_pCompletePtr = NULL;
	m_pLastPtr = NULL;
	m_pEndPtr = NULL;

	m_siNumPacket = 0;

	m_bRemovable = FALSE;

	InitializeCriticalSection( &m_cs );
}

ITZRecvBuffer::~ITZRecvBuffer()
{
	if( m_pRecvBuf ) delete [] m_pRecvBuf;
	m_pRecvBuf = NULL;

	DeleteCriticalSection( &m_cs );

}

void ITZRecvBuffer::ClearBuffer()
{

	EnterCriticalSection( &m_cs );	

	m_pBeginPtr = m_pBasePtr;

	m_pLastPtr = m_pBasePtr;

	m_pCompletePtr = m_pBasePtr;

	m_siNumPacket = 0;

	m_bRemovable = FALSE;

	LeaveCriticalSection( &m_cs );
}

void ITZRecvBuffer::CreateRecvBuffer( SI32 size, SI32 headerType )
{

	EnterCriticalSection( &m_cs );	

	m_siMaxSize = size;

	if( m_pRecvBuf ) delete [] m_pRecvBuf;

	m_pRecvBuf = new char[ PACKET_MAX_SIZE + size ];

	m_pBasePtr = m_pRecvBuf + PACKET_MAX_SIZE;
	m_pEndPtr = m_pBasePtr + size;
	m_pLastPtr = m_pBasePtr;
	m_pCompletePtr = m_pBasePtr;
	
	m_siNumPacket = 0;
	
	m_bRemovable = FALSE;

	m_headerType = headerType;

	LeaveCriticalSection( &m_cs );	

}

void ITZRecvBuffer::GetRecvParam( char **pRecvPtr, SI32 *psiFreeSize )
{
	
   	EnterCriticalSection( &m_cs );	
 
	if( m_pLastPtr == m_pEndPtr ) {

		if( m_pBeginPtr < m_pBasePtr ) {

			*psiFreeSize = 0;

			LeaveCriticalSection( &m_cs );
			return;

		}

		m_pLastPtr = m_pBasePtr;
	}

	*pRecvPtr = m_pLastPtr;

	if( m_pBeginPtr == m_pLastPtr && m_siNumPacket > 0  ) {

		*psiFreeSize = 0;

	} else if( m_pLastPtr < m_pBeginPtr ) {

		*psiFreeSize = (SI32)( m_pBeginPtr - m_pLastPtr );

	} else {

		*psiFreeSize = (SI32)( m_pEndPtr - m_pLastPtr );
	}
	
/*
	printf( "GetRecvParam..%d, begin:%d, last:%d, complete:%d, recvPtr:%d, Size:%d\n",
		(int)m_siNumPacket,
		(int)m_pBeginPtr - (int)m_pBasePtr,
		(int)m_pLastPtr - (int)m_pBasePtr,
		(int)m_pCompletePtr - (int)m_pBasePtr,
		(int)*pRecvPtr - (int)m_pBasePtr,
		*psiFreeSize
		);
*/

	LeaveCriticalSection( &m_cs );

}


BOOL ITZRecvBuffer::Completion( SI32 siRecvdBytes )
{	
	
	EnterCriticalSection( &m_cs );

	UI16 usPacketSize = 0;
	int numPacket = 0;

//	local_pCheckPtr = m_pCompletePtr;
		
	m_pLastPtr += siRecvdBytes;

	char *pTemp;
	SI32 siTemp;

	while( 1 ) {

		// �޽��� ũ�� �о� ����
		if( m_pCompletePtr == m_pEndPtr - 1 ) {

			if( m_pLastPtr < m_pCompletePtr ) {
				
				pTemp = (char *)&usPacketSize;

				*pTemp			=	*m_pCompletePtr;
				*(pTemp + 1)	=   *m_pBasePtr;

				if( m_headerType == 1 ) {
					usPacketSize = ntohs( usPacketSize ) + 8;
				}

			} else {

				goto end;
			}

		} else if( m_pCompletePtr == m_pLastPtr - 1 ) {
			
			goto end;

		} else {

			usPacketSize = *(UI16 *)m_pCompletePtr;

			if( m_headerType == 1 ) {
				usPacketSize = ntohs( usPacketSize ) + 8;
			}
		}


		if( usPacketSize < 2 ) {
			
//			MessageBox( 0, "recv: wrong packet",0, 0 );

			LeaveCriticalSection( &m_cs );

			return FALSE;
		}

		if( usPacketSize > PACKET_MAX_SIZE - 8 ) {
			// �޽��� �ִ� ũ�� ���� ū ���̸�, 

//			MessageBox( 0, "recv: wrong packet",0, 0 );

			LeaveCriticalSection( &m_cs );

			return FALSE;
		}

		pTemp = m_pCompletePtr + usPacketSize;
 
		if( pTemp > m_pEndPtr ) {

			if( m_pLastPtr < m_pCompletePtr ) {

				if( pTemp - m_pEndPtr > m_pLastPtr - m_pBasePtr ) break;
				else {

					siTemp = pTemp - m_pEndPtr;
					m_pCompletePtr = m_pBasePtr + siTemp;

					++numPacket;

					if( m_pCompletePtr == m_pLastPtr ) break;

					continue;
				}
			} else {

				break;
			}
			
		}

		if( pTemp > m_pLastPtr ) break;

		m_pCompletePtr = pTemp;

		++numPacket;

		if( pTemp == m_pLastPtr ) break;		
	} 

	if( m_pCompletePtr == m_pEndPtr ) m_pCompletePtr = m_pBasePtr;

end:
	m_siNumPacket += numPacket;

/*
	printf( "Completion.. recvd:%d, begin:%d, last:%d, complete:%d\n", 
		siRecvdBytes,
		(int)m_pBeginPtr - (int)m_pBasePtr,
		(int)m_pLastPtr - (int)m_pBasePtr,
		(int)m_pCompletePtr - (int)m_pBasePtr
		);
*/
	LeaveCriticalSection( &m_cs );

	return TRUE;

}


char* ITZRecvBuffer::GetFirstPacket()
{
	SI32 siTemp;

	if( m_siNumPacket == 0 ) return NULL;

	EnterCriticalSection( &m_cs );	

	UI16 usDataSize;
/*
	printf( "GetFirst.. begin:%d, last:%d, complete:%d\n", 
		(int)m_pBeginPtr - (int)m_pBasePtr,
		(int)m_pLastPtr - (int)m_pBasePtr,
		(int)m_pCompletePtr - (int)m_pBasePtr
		);
*/
	if( m_pBeginPtr == m_pEndPtr - 1 ) {

		*( m_pBasePtr - 1 ) = *m_pBeginPtr;
		m_pBeginPtr = m_pBasePtr - 1;
	}

	usDataSize = *(UI16 *)m_pBeginPtr;

	if( m_headerType == 1 ) {
		usDataSize = ntohs( usDataSize ) + 8;
	}

	if( m_pBeginPtr + usDataSize > m_pEndPtr ) {

		siTemp = m_pEndPtr - m_pBeginPtr;

		memcpy( m_pBasePtr - siTemp, m_pBeginPtr, siTemp );

		m_pBeginPtr = m_pBasePtr - siTemp;
	}

	m_bRemovable = TRUE;

	LeaveCriticalSection( &m_cs );

	return m_pBeginPtr;
}

void ITZRecvBuffer::RemoveFirstPacket()
{

	UI16 usDataSize;

	if( m_bRemovable == FALSE ) return;

	EnterCriticalSection( &m_cs );

	--m_siNumPacket;

	usDataSize = *(UI16 *)m_pBeginPtr;

	if( m_headerType == 1 ) {
		usDataSize = ntohs( usDataSize ) + 8;
	}

	m_pBeginPtr += usDataSize;

	if( m_pBeginPtr == m_pEndPtr ) m_pBeginPtr = m_pBasePtr;

	m_bRemovable = FALSE;

	LeaveCriticalSection( &m_cs );

}

