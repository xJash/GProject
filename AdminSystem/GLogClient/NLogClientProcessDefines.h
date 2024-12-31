//=============================================================================
//
//	NLogClientProcessDefines.h
//
//	Copyright 2007 HQGame
//
//=============================================================================
#ifndef _NLOGCLIENTPROCESSDEFINES_H_
#define _NLOGCLIENTPROCESSDEFINES_H_

#define MAX_LOGCLIENT_PACKET_SIZE	5000
#define MAX_LOGCLIENT_PACKET_COUNT	1000

#define MAX_LOGCLIENT_CHANNEL		1

#define MAX_CONNECTING_TIME			2000

enum
{
	LOGCLIENTPROCESS_STATE_IDLE,
	LOGCLIENTPROCESS_STATE_REQUESTCONNECTING,
	LOGCLIENTPROCESS_STATE_CONNECTING,
	LOGCLIENTPROCESS_STATE_ESTABLISH,
	LOGCLIENTPROCESS_STATE_WAITLOG,
	LOGCLIENTPROCESS_STATE_FINISHLOG,
	LOGCLIENTPROCESS_STATE_WRONGID,
	LOGCLIENTPROCESS_STATE_WRONGPASS,
	LOGCLIENTPROCESS_STATE_DONOTINPUTID,
};

#endif
