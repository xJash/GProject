#include "DBGameProtocol.h"
//#include "DBMsg.h"
#include "DBMsg-Person.h"


void DBGameProtocol::IncreaseSkill()
{
	// ���� ��Ŷ
	sDBRequest_IncreaseSkill *pRecvMsg	= (sDBRequest_IncreaseSkill *)m_pPacket;
	
	// ���� ��Ŷ
	sDBResponse_IncreaseSkill sendMsg;
	
	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_INCREASESKILL;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;
	
	//[�߰� : Ȳ���� 2007. 10. 25 	�α׿� �̿�. ����� ������.]
	sendMsg.clUseItem.Set(&pRecvMsg->clUseItem);

	// PCK : ��ų�������� Ȯ��
	sendMsg.siReason = INCREASESKILL;

	BEGIN_SP( "rsp_SkillIncrease" )
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siPersonID,		sizeof(pRecvMsg->siPersonID) );
		m_odbc.SetParam( SQL_TINYINT, &pRecvMsg->uiSkillUnique,		sizeof(pRecvMsg->uiSkillUnique) );
		m_odbc.SetParam( SQL_TINYINT, &pRecvMsg->uiIncSkillLevel,	sizeof(pRecvMsg->uiIncSkillLevel) );
		m_odbc.SetParam( SQL_TINYINT, &pRecvMsg->uiMaxSkillLevel,	sizeof(pRecvMsg->uiMaxSkillLevel) );
		m_odbc.SetParam( SQL_TINYINT, &pRecvMsg->uiDecreaseSkillPoint,	sizeof(pRecvMsg->uiDecreaseSkillPoint) );
	END_SP()

	EXEC_SQL()
	
	BEGIN_FETCHDATA()
		m_odbc.GetData( &sendMsg.siResult,		0);
		m_odbc.GetData( &sendMsg.siPersonID,	0);
		m_odbc.GetData( &sendMsg.uiSkillUnique,	0);
		m_odbc.GetData( &sendMsg.uiSkillLevel,	0);
		m_odbc.GetData( &sendMsg.siSkillBonus,	0);
	END_FETCHDATA()

	// send
	SendPacket( (BYTE *)&sendMsg );

	// �α� �ۼ�
	if(sendMsg.siResult == 1)
	{
		char log[512] = "";
		sprintf(log, "SkillUnique = %d, IncSkillLevel = %d, SkillLevel = %d, SkillBonus = %d"
				, pRecvMsg->uiSkillUnique, pRecvMsg->uiIncSkillLevel
				, sendMsg.uiSkillLevel, sendMsg.siSkillBonus
				);
		sDBLogMsg_QueryString LogMsg("Increase Skill", sendMsg.siPersonID, NULL, NULL, log);
		SendLogMsg((sPacketHeader *)&LogMsg);
	}
}

// ��ų����
void DBGameProtocol::DecreaseSkill()
{
	// ���� ��Ŷ
	sDBRequest_DecreaseSkill *pRecvMsg	= (sDBRequest_DecreaseSkill *)m_pPacket;
	
	// ���� ��Ŷ
	sDBResponse_IncreaseSkill sendMsg;
	
	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_INCREASESKILL;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;

	// PCK : ��ų�������� Ȯ��
	sendMsg.siReason = DECREASESKILL;

	BEGIN_SP( "rsp_SkillDecrease" )
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siPersonID,		sizeof(pRecvMsg->siPersonID) );
		m_odbc.SetParam( SQL_TINYINT, &pRecvMsg->uiSkillUnique,		sizeof(pRecvMsg->uiSkillUnique) );
		m_odbc.SetParam( SQL_TINYINT, &pRecvMsg->uiDecSkillLevel,	sizeof(pRecvMsg->uiDecSkillLevel) );
		m_odbc.SetParam( SQL_TINYINT, &pRecvMsg->uiIncreaseSkillPoint,	sizeof(pRecvMsg->uiIncreaseSkillPoint) );
		SetChildSkillList ( pRecvMsg );
		m_odbc.SetParam( SQL_SMALLINT, &pRecvMsg->siMode,			sizeof(pRecvMsg->siMode) );
		m_odbc.SetParam( SQL_SMALLINT, &pRecvMsg->siItemPos,		sizeof(pRecvMsg->siItemPos) );
		SetItemParam( &pRecvMsg->clItem );
	END_SP()

	EXEC_SQL()
	
	BEGIN_FETCHDATA()
		m_odbc.GetData( &sendMsg.siResult,		0);
		m_odbc.GetData( &sendMsg.siPersonID,	0);
		m_odbc.GetData( &sendMsg.uiSkillUnique,	0);
		m_odbc.GetData( &sendMsg.uiSkillLevel,	0);
		m_odbc.GetData( &sendMsg.siSkillBonus,	0);
		m_odbc.GetData( &sendMsg.siMode, 0 );
	END_FETCHDATA()

	BEGIN_NEXTRECORDSET()
		BEGIN_FETCHDATA()
			m_odbc.GetData( &sendMsg.siItemPos, 0 );
			GetItemData( &sendMsg.clItem );
		END_FETCHDATA()
	END_NEXTRECORDSET()
	
	// send
	SendPacket( (BYTE *)&sendMsg );

	// �α� �ۼ�
	if(sendMsg.siResult == 1)
	{
		char log[512] = "";
		sprintf(log, "Mode = %d, SkillUnique = %d, DscSkillLevel = %d, IncSkillBonus = %d, SkillLevel = %d, SkillBonus = %d, InvPos = %d, LeftItemNum = %d"
				, pRecvMsg->siMode, pRecvMsg->uiSkillUnique, pRecvMsg->uiDecSkillLevel, pRecvMsg->uiIncreaseSkillPoint
				, sendMsg.uiSkillLevel, sendMsg.siSkillBonus
				, pRecvMsg->siItemPos, pRecvMsg->clItem.siItemNum
				);
		sDBLogMsg_QueryString LogMsg("Decrease Skill", sendMsg.siPersonID, NULL, pRecvMsg->clItem.siUnique, log);
		SendLogMsg((sPacketHeader *)&LogMsg);
	}
}

void DBGameProtocol::SetSkillExp()
{
	// ���� ��Ŷ
	sDBRequest_SetSkillExp *pRecvMsg	= (sDBRequest_SetSkillExp *)m_pPacket;
	
	// ���� ��Ŷ
	sDBResponse_SetSkillExp sendMsg;
	
	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_SETSKILLEXP;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;

	// PCK : �α׿� ��Ŷ �߰�
	sendMsg.uiSkillUnique = pRecvMsg->uiSkillUnique;
	sendMsg.siSkillExp = pRecvMsg->siSkillExp;

	BEGIN_SP( "rsp_SkillExpSet" )
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siPersonID,		sizeof(pRecvMsg->siPersonID) );
		m_odbc.SetParam( SQL_TINYINT, &pRecvMsg->uiSkillUnique,		sizeof(pRecvMsg->uiSkillUnique) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siSkillExp,	sizeof(pRecvMsg->siSkillExp) );
	END_SP()

	EXEC_SQL()
	
	BEGIN_FETCHDATA()
		m_odbc.GetData( &sendMsg.siResult,		0);
	END_FETCHDATA()

	// send
	SendPacket( (BYTE *)&sendMsg );

	// �α� �ۼ�
	if(sendMsg.siResult == 1)
	{
		char log[512] = "";
		sprintf(log, "SkillUnique = %d, SkillExp = %d"
				, pRecvMsg->uiSkillUnique, pRecvMsg->siSkillExp
				);
		sDBLogMsg_QueryString LogMsg("Set SkillExp", pRecvMsg->siPersonID, NULL, NULL, log);
		SendLogMsg((sPacketHeader *)&LogMsg);
	}
}

void DBGameProtocol::IncreaseMasterSkill()
{
	// ���� ��Ŷ
	sDBRequest_IncreaseMasterSkill *pRecvMsg	= (sDBRequest_IncreaseMasterSkill *)m_pPacket;
	
	// ���� ��Ŷ
	sDBResponse_IncreaseMasterSkill sendMsg;
	
	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_INCREASEMASTERSKILL;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;

	BEGIN_SP( "rsp_SkillIncreaseMaster" )
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siPersonID,		sizeof(pRecvMsg->siPersonID) );
		m_odbc.SetParam( SQL_TINYINT, &pRecvMsg->uiSkillUnique,		sizeof(pRecvMsg->uiSkillUnique) );
		m_odbc.SetParam( SQL_TINYINT, &pRecvMsg->uiIncSkillLevel,	sizeof(pRecvMsg->uiIncSkillLevel) );
		m_odbc.SetParam( SQL_TINYINT, &pRecvMsg->uiMaxSkillLevel,	sizeof(pRecvMsg->uiMaxSkillLevel) );
	END_SP()

	EXEC_SQL()
	
	BEGIN_FETCHDATA()
		m_odbc.GetData( &sendMsg.siResult,		0);
		m_odbc.GetData( &sendMsg.siPersonID,	0);
		m_odbc.GetData( &sendMsg.uiSkillUnique,	0);
		m_odbc.GetData( &sendMsg.uiSkillLevel,	0);
	END_FETCHDATA()

	// send
	SendPacket( (BYTE *)&sendMsg );

	// �α� �ۼ�
	if(sendMsg.siResult == 1)
	{
		char log[512] = "";
		sprintf(log, "SkillUnique = %d, IncSkillLevel = %d, SkillLevel = %d, SkillBonus = %d"
				, pRecvMsg->uiSkillUnique, pRecvMsg->uiIncSkillLevel
				, sendMsg.uiSkillLevel
				);
		sDBLogMsg_QueryString LogMsg("Increase Skill Master", sendMsg.siPersonID, NULL, NULL, log);
		SendLogMsg((sPacketHeader *)&LogMsg);
	}
}

void DBGameProtocol::SetWeaponSkill()
{
	// ���� ��Ŷ
	sDBRequest_Set_WeaponSkill *pRecvMsg	= (sDBRequest_Set_WeaponSkill *)m_pPacket;

	// ���� ��Ŷ
	sDBResponse_Set_WeaponSkill sendMsg;

	sendMsg.packetHeader.usCmd	= DBMSG_RESPONSE_SET_WEAPONSKILL;
	sendMsg.packetHeader.usSize	= sizeof( sendMsg );
	sendMsg.usCharID			= pRecvMsg->usCharID;

	// �α׿� ����
	sendMsg.siNeedSkillBonus	= pRecvMsg->uiNeedSkillPoint;
	sendMsg.siMoney				= pRecvMsg->siMoney;
	sendMsg.clNeedItem.Set( &pRecvMsg->clNeedItem );

	BEGIN_SP( "rsp_SkillIncreaseWeapon" )
		m_odbc.SetParam( SQL_INTEGER,	&pRecvMsg->siPersonID,			sizeof(pRecvMsg->siPersonID) );
		m_odbc.SetParam( SQL_TINYINT,	&pRecvMsg->uiSkillUnique,		sizeof(pRecvMsg->uiSkillUnique) );
		m_odbc.SetParam( SQL_TINYINT,	&pRecvMsg->uiNeedSkillPoint,	sizeof(pRecvMsg->uiNeedSkillPoint) );
		m_odbc.SetParam( SQL_BIGINT,	&pRecvMsg->siMoney,				sizeof(pRecvMsg->siMoney) );
		SetItemParam( &pRecvMsg->clNeedItem );
		m_odbc.SetParam( SQL_SMALLINT,	&pRecvMsg->siNeedItemPos,		sizeof(pRecvMsg->siNeedItemPos) );
	END_SP()

	EXEC_SQL()

	BEGIN_FETCHDATA()
		m_odbc.GetData( &sendMsg.siResult );
		m_odbc.GetData( &sendMsg.siPersonID );
		m_odbc.GetData( &sendMsg.uiSkillUnique );
		m_odbc.GetData( &sendMsg.uiSkillLevel );
		m_odbc.GetData( &sendMsg.siLeftBonus );
		m_odbc.GetData( &sendMsg.siLeftMoney );
	END_FETCHDATA()

	BEGIN_NEXTRECORDSET()
		BEGIN_FETCHDATA()
			GetItemData( &sendMsg.clLeftItem );
			m_odbc.GetData( &sendMsg.siItemPos );
		END_FETCHDATA()
	END_NEXTRECORDSET()
	// send
	SendPacket( (BYTE *)&sendMsg );

	/*
	// �α� �ۼ�
	if(sendMsg.siResult == 1)
	{
		char log[512] = "";
		sprintf(log, "SkillUnique = %d, SkillLevel = %d, SkillBonus = %d, LeftMoney = %I64d, PayMoney = %I64d"
				, sendMsg.uiSkillUnique, sendMsg.uiSkillLevel, sendMsg.siSkillBonus, sendMsg.siLeftMoney, sendMsg.siMoney
			);
		sDBLogMsg_QueryString LogMsg("Increase Skill Weapon", sendMsg.siPersonID, NULL, NULL, log);
		SendLogMsg((sPacketHeader *)&LogMsg);
	}
	*/
}
