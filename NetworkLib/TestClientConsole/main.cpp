#include "ITZNetworkThread.h"
#include "ITZSessionFactory.h"
#include "ITZSessionManager.h"
#include "ITZSession.h"
#include "ITZNetIOCP.h"
#include "ITZPerson.h"
#include "ITZEncrypt.h"

#include "ITZRecvBuffer.h"
#include "ITZSendBuffer.h"

//#include "../TestServerConsole/msgType.h"

#include <conio.h>
#include <stdio.h>

class cChar : public ITZPerson
{
public:
	cChar() {};
	~cChar() {};
};


void WinSockInit()
{
	WORD	wVersionRequested;
	WSADATA	wsaData;

	int err;

	wVersionRequested = MAKEWORD( 2, 2 );

	err = WSAStartup( wVersionRequested, &wsaData );

	if( err != 0 ) {
		return;
	}

	if( LOBYTE( wsaData.wVersion ) != 2 ||
		HIBYTE( wsaData.wVersion ) != 2 ) {

		WSACleanup();
		return;
	}
}

struct cTestPH
{
	UI16	size;
	UI08	chk;
	UI16	cmd;
};

struct cPacket1
{
	cTestPH		ph;
	char 		data[ 1024 ];
};


int				count = 10000;

cPacket1		packet;

ITZRecvBuffer	recvBuf;



unsigned __stdcall thread( LPVOID param )
{

	char *pBuf;
	char *pTempPtr;
	SI32 siSize;
	SI32 temp;


	for( int i = 0; i < count; ++i ) {


		//packet.ph.size = 501;
		packet.ph.size = 10 + ( rand() % 512 );
		packet.ph.cmd = i;

		temp = packet.ph.size;
		pTempPtr = (char *)&packet;

		while( temp > 0 ) {

			recvBuf.GetRecvParam( &pBuf, &siSize );

			if( siSize == 0 ) {
				Sleep( 10 );
				continue;
			}

			if( siSize < temp ) {

				memcpy( pBuf, pTempPtr, siSize );

				recvBuf.Completion( siSize );

				pTempPtr += siSize;

				temp -= siSize;

			} else {

				memcpy( pBuf, pTempPtr, temp );

				recvBuf.Completion( temp );
				
				pTempPtr += temp;

				temp = 0;
			}
		}

//		Sleep( 20 );

//		if( i == 0 ) Sleep( rand() % 20 );
		
	}

	return 0;
}


void main()
{
	memset( &packet, 1, sizeof( packet ) );

	recvBuf.CreateRecvBuffer( 2000 );
	recvBuf.ClearBuffer();

	UI32 uiThreadID;

	HANDLE hThread = (HANDLE)_beginthreadex( NULL, 0, thread, NULL, 0, &uiThreadID );
	CloseHandle( hThread );	

	for( int i = 0; i < count; ++i ) {
		
		//printf( "%d...", recvBuf.GetPacketCount() );
	
		int count = recvBuf.GetPacketCount();
		cPacket1 *pPacket = (cPacket1 *)recvBuf.GetFirstPacket();

		if( pPacket == NULL ) {
			//printf( "pPacket == NULL" );
			--i;
			continue;
		}

		printf( "pc:%d  ", count );

		if( pPacket->ph.size > 600 || pPacket->ph.cmd != i ) {
			printf( "%d, %d, %d ERROR!!\n", pPacket->ph.size, pPacket->ph.cmd, (int)pPacket - (int)recvBuf.m_pBasePtr );
			exit(0);
		}

		printf( "size: %d, cmd: %d, addr:%d, endPtr:%d\n", 
			pPacket->ph.size, 
			pPacket->ph.cmd, 
			(int)pPacket - (int)recvBuf.m_pBasePtr,
			(int)recvBuf.m_pEndPtr - (int)recvBuf.m_pBasePtr );
		
		recvBuf.RemoveFirstPacket();

//		Sleep(20);
	}

/*
	WinSockInit();


	printf( "test client... (1:��Ŷ������, ESC:����)\n" );

	ITZSessionFactory< cChar > sf;

	ITZSessionManager			sm;

	ITZNetIOCP					iocp;
	ITZNetOverlapped			overlapped;
	
	ITZSession*					pSession;


	sf.CreateFactory( &sm, 1, 30000, 30000 );			// Session��ü���� �����ϰ�, SessionManager�� ������ �ش� 

	pSession = sm.GetSession( 0 );						// ���� �޴����� ���� �ϳ��� Ŭ���̾�Ʈ�� ������ ��´�

//	iocp.CreateIOCP( &sm, 1 );							// iocp�� �����Ѵ�

	overlapped.CreateOverlapped( &sm );					// overlapped�� �����Ѵ�


	// loop
	BOOL bRun = TRUE;
	while( bRun ) {

		Sleep( 10 );

		// ������ ������� ���� �����̸�, ���� �õ� �Ѵ�
		if( pSession->GetState() == SESSION_STATE_NONE ) {
			printf( "����õ�..." );
			if( sm.Connect( 0, "127.0.0.1", 4010 ) ) {
				printf( "����\n" ); 
			} else {
				printf( "����\n" );
				Sleep( 500 );
			}
		}


		// ������ ���������� ����� �����̸�, ������ ��Ŷ ó���� �Ѵ�
		if( pSession->GetState() == SESSION_STATE_ESTABLISHED ) {		

			char *pPacket = pSession->GetRecvBuffer()->GetFirstPacket();		// ���ۿ��� ��Ŷ�� �ϳ� �����´�

			if( pPacket != NULL ) {										
				// ��Ŷ�� ������,

				printf( "��Ŷ�� �ϳ� ����!\n" );

				pSession->GetRecvBuffer()->RemoveFirstPacket();						// ó�� �� ��Ŷ�� ���ۿ��� �����
			}
		}



		// console
		if( kbhit() ) {

			switch( getch() ) {
			case 27:
				bRun = FALSE;
				break;

			case '1':
				{
					printf( "��Ŷ ������ MSG_REQUEST_TEST1\n" );
					
					sRequest_Test1 sendMsg;

					sendMsg.packetHeader.usSize = sizeof( sendMsg );
					sendMsg.packetHeader.usCmd = MSG_REQUEST_TEST1;

					pSession->GetSendBuffer()->Write( (char *)&sendMsg ); 
				}
				break;

			case '2':
				{
					printf( "��Ŷ ������ MSG_REQUEST_TEST2\n" );
					
					sRequest_Test2 sendMsg;

					sendMsg.packetHeader.usSize = sizeof( sendMsg );
					sendMsg.packetHeader.usCmd = MSG_REQUEST_TEST2;

					pSession->GetSendBuffer()->Write( (char *)&sendMsg ); 
				}
				break;

			}
		}
	}

	WSACleanup();
*/
	return;
}
