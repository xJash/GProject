#ifndef _DBMSGPVP_LEAGUE_H
#define _DBMSGPVP_LEAGUE_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "DBMsg.h"

//----------------------------------------------
// Common
//----------------------------------------------
#include "../../GoonZuWorld/Common/CommonHeader.h"
#include "../../GoonZuWorld/Common/PersonInfo.h"

#include "../../GoonZuWorld/Common/Char/CharCommon/Char-Common.h"


class sDBRequest_PVP_League_Battle_End
{
public:
	sPacketHeader		packetHeader;
	SI32				siMyPersonID	;		// ���� PersonID
	SI32				siEnemyPersonID	;		// ���� PersonID
	SI32				siWinOrLose		;		// PVPLEAGUE_RESULT_WIN
	SYSTEMTIME			stLAstPVPTime	;		// ���������� �� PVP �ð�.

	sDBRequest_PVP_League_Battle_End()
	{
		ZeroMemory(this, sizeof(sDBRequest_PVP_League_Battle_End));
	}

	sDBRequest_PVP_League_Battle_End(SI32 MyPersonID, SI32 EnemyPersonID,SI16 WinOrLose,SYSTEMTIME LAstPVPTime )
	{
		packetHeader.usSize = sizeof( sDBRequest_PVP_League_Battle_End );
		packetHeader.usCmd = DBMSG_REQUEST_PVP_LEAGUE_BATTLE_END;
		siMyPersonID		=	MyPersonID			;
		siEnemyPersonID		=	EnemyPersonID		;
		siWinOrLose			=	WinOrLose			;
		stLAstPVPTime		=	LAstPVPTime			;
	}
};

class sDBResponse_PVP_League_Battle_End
{
public:
	sPacketHeader		packetHeader;
	SI32				siMyPersonID	;		// ���� PersonID
	SI32				siEnemyPersonID	;		// ���� PersonID
	SI32				siWinOrLose		;
	SYSTEMTIME			stLAstPVPTime	;		// ���������� �� PVP �ð�.

	sDBResponse_PVP_League_Battle_End()
	{
		ZeroMemory(this, sizeof(sDBResponse_PVP_League_Battle_End));
	}
};

//--------------------------------------------------
// ���Ѵ��� ���̾�α׿��� �ʿ��� ������ ��û��
//--------------------------------------------------
class sDBRequest_PVP_League_UI_InfoGet
{
public:
	sPacketHeader	m_packetHeader;

	SI32			m_siPersonID;
	SI32			m_siCharID;

	sDBRequest_PVP_League_UI_InfoGet( )
	{
		ZeroMemory( this, sizeof(sDBRequest_PVP_League_UI_InfoGet) );

		m_packetHeader.usSize	= sizeof( sDBRequest_PVP_League_UI_InfoGet );
		m_packetHeader.usCmd	= DBMSG_REQUEST_PVP_LEAGUE_UI_INFOGET;
	}

	sDBRequest_PVP_League_UI_InfoGet( SI32 siPersonID, SI32 siCharID )
	{
		ZeroMemory( this, sizeof(sDBRequest_PVP_League_UI_InfoGet) );

		m_packetHeader.usSize	= sizeof( sDBRequest_PVP_League_UI_InfoGet );
		m_packetHeader.usCmd	= DBMSG_REQUEST_PVP_LEAGUE_UI_INFOGET;

		m_siPersonID			= siPersonID;
		m_siCharID				= siCharID;
	}

};

class sDBResponse_PVP_League_UI_InfoGet
{
public:
	sPacketHeader		m_packetHeader;

	SI32				m_siPersonID;
	SI32				m_siCharID;

	SI32				m_siWin;		// �¸�
	SI32				m_siLose;		// �й�
	SI32				m_siDraw;		// ���º�

	SI32				m_siGroupNum;	// ����޿� �����ִ� ������� ��

	cltPVP_League_OtherUserInfo	m_clLatest[Const_PVP_League_Latest_Max];	// �ֱٰ��
	cltPVP_League_OtherUserInfo	m_clTop[Const_PVP_League_Top_Max];			// ���� �÷��̾�


	sDBResponse_PVP_League_UI_InfoGet( )
	{
		ZeroMemory( this, sizeof(sDBResponse_PVP_League_UI_InfoGet) );
	}
};	// DBMSG_RESPONSE_PVP_LEAGUE_UI_INFOGET

//--------------------------------------------------
// ���Ѵ������� ������ ���� �־�� �ϴ� ����
//--------------------------------------------------
class sDBRequest_PVP_League_InfoGet
{
public:
	sPacketHeader	m_packetHeader;

	SI32			m_siPersonID;


	sDBRequest_PVP_League_InfoGet( )
	{
		ZeroMemory( this, sizeof(sDBRequest_PVP_League_InfoGet) );

		m_packetHeader.usSize	= sizeof( sDBRequest_PVP_League_InfoGet );
		m_packetHeader.usCmd	= DBMSG_REQUEST_PVP_LEAGUE_INFOGET;
	}

	sDBRequest_PVP_League_InfoGet( SI32 siPersonID )
	{
		ZeroMemory( this, sizeof(sDBRequest_PVP_League_InfoGet) );

		m_packetHeader.usSize	= sizeof( sDBRequest_PVP_League_InfoGet );
		m_packetHeader.usCmd	= DBMSG_REQUEST_PVP_LEAGUE_INFOGET;

		m_siPersonID			= siPersonID;
	}
};

class sDBResponse_PVP_League_InfoGet
{
public:
	sPacketHeader		m_packetHeader;

	SI32				m_siPersonID;

	cltPVP_LeagueInfo	m_clPVP_LeaugeInfo;

	sDBResponse_PVP_League_InfoGet( )
	{
		ZeroMemory( this, sizeof(sDBResponse_PVP_League_InfoGet) );
	}
};	// DBMSG_RESPONSE_PVP_LEAGUE_INFOGET

class sDBRequest_PVP_League_Battle_ChangeGrade
{
public:
	sPacketHeader		packetHeader;
	SI32				siMyPersonID	;		// ���� PersonID
	SI32				siGrade			;
	SYSTEMTIME			stLAstPVPTime	;		// ��������

	sDBRequest_PVP_League_Battle_ChangeGrade()
	{
		ZeroMemory(this, sizeof(sDBRequest_PVP_League_Battle_ChangeGrade));
	}

	sDBRequest_PVP_League_Battle_ChangeGrade(SI32 MyPersonID ,SI32 Grade, SYSTEMTIME LAstPVPTime )
	{
		packetHeader.usSize = sizeof( sDBRequest_PVP_League_Battle_ChangeGrade );
		packetHeader.usCmd = DBMSG_REQUEST_PVP_LEAGUE_BATTLE_CHANGEGRADE;
		siMyPersonID		=	MyPersonID		;
		siGrade				=	Grade			;
		stLAstPVPTime		=	LAstPVPTime		;
	}
};
class sDBResponse_PVP_League_Battle_ChangeGrade
{
public:
	sPacketHeader		packetHeader;
	SI32				siMyPersonID	;		// ���� PersonID
	SI32				siGrade			;
	SYSTEMTIME			stLAstPVPTime	;

	sDBResponse_PVP_League_Battle_ChangeGrade()
	{
		ZeroMemory(this, sizeof(sDBResponse_PVP_League_Battle_ChangeGrade));
	}
};
#endif