//
// Apex���� ������ ���� ���
//
// 2007/03/15 ������
// 2007/03/17 �׽�Ʈ �Ϸ�
//
// ���־� ��Ʃ��� �˻�â���� 'APEX-'�� ���� �۾� ���� �˻� ����
// _USE_APEX �� define �Ǿ��� ��쿡�� ó���Ѵ�
// APEX�� ����� ��� ��ó���⿡�� _USE_APEX�� �����ؾ� �Ѵ�

#ifndef _APEXGOONZU_H
#define _APEXGOONZU_H

#include "NDataTypes.h"

#ifdef _CHINA
	#pragma comment(lib, "AHClientInterface.lib")
#endif

// Client
int	StartApexClient();
int	StopApexClient();
int NoticeApec_UserData( const char * pBuf, int nBufLen );

long NetSendToGameServer( const char * pBuffer,int nLen );


// Server
int	StartApexProxy();
int StopApexProxy();

int NoticeApexProxy_UserLogin( int nSendId, char *szID );
int	NoticeApexProxy_UserLogout( int nSendId, char *szID );
int	NoticeApexProxy_UserData( int nSendId, const char* pBuf, int nBufLen );

long NetSendToGameClient( signed int nSendId, const char* pBuffer, int nLen );
long GameServerKillUser( signed int nId, int Action );

#endif

