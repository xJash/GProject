//
// Apex���� ������ ���� ���
//
// 2007/03/15 ������
// 2007/03/17 �׽�Ʈ �Ϸ�
//
// ���־� ��Ʃ��� �˻�â���� 'APEX-'�� ���� �۾� ���� �˻� ����
// _CHINA �� define �Ǿ��� ��쿡�� ó���Ѵ�
// APEX�� ����� ��� ��ó���⿡�� _CHINA�� �����ؾ� �Ѵ�

#include "ApexGoonZu.h"
#include "ApexClient.h"
#include "ApexProxy.h"

#include <Client.h>
#include <Server.h>
extern cltCommonLogic *pclClient;

_FUNC_C_REC pfCRec = NULL;
_FUNC_S_REC pfSRec = NULL;


//-----------------------------------------------------------------------------
// Apex Client 
//-----------------------------------------------------------------------------

// Apex Client �⵿
BOOL bApexStarted = FALSE;
int	StartApexClient()
{

#ifdef _CHINA
	long re= CHCStart( NetSendToGameServer, pfCRec );

	InterlockedExchange( (LPLONG)&bApexStarted, TRUE );

	char tempbuf[ 512 ];
	sprintf( tempbuf, "StartApexClient : %d\r\n", re );
	OutputDebugString( tempbuf );
#endif

	return 0;
}

// Apex Client ����

int	StopApexClient()
{

#ifdef _CHINA

	InterlockedExchange( (LPLONG)&bApexStarted, FALSE );

	char tempbuf[ 512 ];
	sprintf( tempbuf, "StopApexClient\r\n" );
	OutputDebugString( tempbuf );

	CHCEnd();
#endif
	return 0;
}

int NoticeApec_UserData( const char * pBuf, int nBufLen )
{
#ifdef _CHINA

	if( bApexStarted == FALSE ) return -1;

	if(pfCRec)
	{
		pfCRec(pBuf, nBufLen);
	}
#endif
	return 0;
};

// Apex Clinet �⵿ �ÿ� ����� ������ ��Ŷ�� ������ ��ƾ
long NetSendToGameServer( const char * pBuffer, int nLen )
{

#ifdef _CHINA

	if( bApexStarted == FALSE ) return -1;

	BYTE buffer[ PACKET_MAX_SIZE ];

	sPacketHeader *pPacket = (sPacketHeader *)buffer;

	pPacket->usCmd = GAMEMSG_REQUEST_APEXDATA;
	pPacket->usSize = sizeof( sPacketHeader ) + nLen;

	memcpy( buffer + sizeof( sPacketHeader ), pBuffer, nLen );

	((cltClient*)pclClient)->SendMsgToServer( pPacket );

	char tempbuf[ 512 ];
	sprintf( tempbuf, "ApexData SendToGameServer : %d\r\n", nLen );
	OutputDebugString( tempbuf );
#endif

	return 0;
}


//-----------------------------------------------------------------------------
// Apex Server
//-----------------------------------------------------------------------------

int	StartApexProxy()
{
#ifdef _CHINA
	CH_RESULT ret = CHSStart( NetSendToGameClient, pfSRec);
	CHSSetFunc( (void*)(GameServerKillUser), FLAG_KILLUSER );

	char tempbuf[ 512 ];
	sprintf( tempbuf, "StartApexProxy : %d\r\n", ret );
	OutputDebugString( tempbuf );
#endif
	return 0;
}

int	StopApexProxy()
{	
#ifdef _CHINA
	char tempbuf[ 512 ];
	sprintf( tempbuf, "StopApexProxy\r\n" );
	OutputDebugString( tempbuf );

	CHSEnd();
#endif
	return 0;
}

int NoticeApexProxy_UserLogin( int nSendId, char *szID )
{
#ifdef _CHINA
	char tempbuf[ 512 ];
	sprintf( tempbuf, "NoticeApexProxy_UserLogin: %d, %s\r\n", nSendId, szID );
	OutputDebugString( tempbuf );

	if(pfSRec)
	{
		pfSRec( 'L', nSendId, szID, strlen( szID ) );
	}
#endif
	return 0;
};

int	NoticeApexProxy_UserLogout( int nSendId, char *szID )
{
#ifdef _CHINA
	char tempbuf[ 512 ];
	sprintf( tempbuf, "NoticeApexProxy_UserLogOut: %d, %s\r\n", nSendId, szID );
	OutputDebugString( tempbuf );

	if(pfSRec)
	{
		pfSRec( 'G', nSendId, szID, strlen( szID ) );
	}
#endif
	return 0;
};


int	NoticeApexProxy_UserData( int nSendId, const char* pBuf, int nBufLen )
{
#ifdef _CHINA
	char tempbuf[ 512 ];
	sprintf( tempbuf, "NoticeApexProxy_UserData: %d, %d\r\n", nSendId, nBufLen );
	OutputDebugString( tempbuf );

	if(pfSRec)
	{
		pfSRec( 'T', nSendId, pBuf, nBufLen );
	}
#endif
	return 0;
};

long NetSendToGameClient( signed int nSendId, const char* pBuffer, int nLen )
{
#ifdef _CHINA
	BYTE buffer[ PACKET_MAX_SIZE ];

	sPacketHeader *pPacket = (sPacketHeader *)buffer;

	pPacket->usCmd = GAMEMSG_RESPONSE_APEXDATA;
	pPacket->usSize = sizeof( sPacketHeader ) + nLen;

	memcpy( buffer + sizeof( sPacketHeader ), pBuffer, nLen );

	((cltServer*)pclClient)->SendNetMsg( nSendId, pPacket );

	char tempbuf[ 512 ];
	sprintf( tempbuf, "ApexData SendToClient : %d\r\n", nLen );
	OutputDebugString( tempbuf );
#endif
	return 0;
}

long GameServerKillUser( signed int nId, int Action )
{
#ifdef _CHINA	
	char tempbuf[ 512 ];
	sprintf( tempbuf, "KillUser:%d\r\n", nId );
	OutputDebugString( tempbuf );

	((cltServer*)pclClient)->KillUser( nId );
#endif
	return 0;
}