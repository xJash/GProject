#include "DBGameProtocol.h"
#include "DBMsg-Family.h"
#include "DBMsg.h"

#include "../../common/CommonHeader.h"
#include "../../common/Char/CharCommon/Char-Common.h"
// ���� �ý���

void DBGameProtocol::Add_Family_Children()
{
	// ���� ��Ŷ
	sDBRequest_Family_Add_Children	*pRecvMsg = (sDBRequest_Family_Add_Children*)m_pPacket;

	// ���� ��Ŷ
	sDBResponse_Family_Add_Children	sendMsg;

	ZeroMemory(&sendMsg,sizeof(sendMsg))	;

	sendMsg.m_packetHeader.usCmd	= DBMSG_RESPONSE_FAMILY_ADD_CHILDREN;
	sendMsg.m_packetHeader.usSize	= sizeof( sendMsg );

	SI32 siParent_PersonID ;
	TCHAR szParentCharName[MAX_PLAYER_NAME]= TEXT("");

	SI32 siChildren_PersonID ;
	TCHAR szChildCharName[MAX_PLAYER_NAME]= TEXT("");
	SI32 siDateVary	=	0;
	//��Ű����Ʈ �߰�-------------���� ������Ë� �ڽĵ��� �� �߰� ����� �մϴ�.
	SI32 siCookieEndTime	=	0	;	// ��Ű ���� Ÿ��
	SI32 siCookieLimitTime	=	0	;	// ��Ű ��� ���� Ÿ��
	SI32 siCookieLevel		=	0	;	// ��Ű ����
	//��Ű����Ʈ �߰�-------------���� ������Ë� �ڽĵ��� �� �߰� ����� �մϴ�.

	TIMESTAMP_STRUCT stSaveTS;	//-> ���� �����ϴ³�
	ZeroMemory(&stSaveTS, sizeof(stSaveTS));	
	TIMESTAMP_STRUCT stRevTS;	//-> db�κ��� ���� ��
	ZeroMemory(&stRevTS, sizeof(stRevTS));

	Convert_TIMESTAMP_from_SYSTEMTIME( &stSaveTS ,&pRecvMsg->m_stCurrentTime ) 	;

	// DB Query
	BEGIN_SP( "rsp_FamilyAddChild" )
	m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->m_siParentPersonID, sizeof(pRecvMsg->m_siParentPersonID) );		// �߰��ϴ� �θ�
	m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->m_siChildrenPersonID, sizeof(pRecvMsg->m_siChildrenPersonID) );	// �����ϴ� �ڽ�
	m_odbc.SetParam( SQL_TIMESTAMP, &stSaveTS, sizeof(stSaveTS) );				// �߰��� �ð�.(��������Ʈ ���� datevary)
	END_SP()

	EXEC_SQL()
	BEGIN_FETCHDATA()
	// �θ� ����
	m_odbc.GetData( &siParent_PersonID);
	m_odbc.GetData( szParentCharName,sizeof(szParentCharName));
	//------------------------------------------------------------
	sendMsg.m_cFamily.SetParent(siParent_PersonID,szParentCharName)	;
	END_FETCHDATA()
	BEGIN_NEXTRECORDSET()
	// �ڽ� ���� 
	BEGIN_FETCHDATA()
	m_odbc.GetData( &siChildren_PersonID);
	m_odbc.GetData( szChildCharName ,sizeof(szChildCharName));
	m_odbc.GetData( &stRevTS );
	//��Ű����Ʈ �߰�-------------���� ������Ë� �ڽĵ��� �� �߰� ����� �մϴ�.-> DB�۾��� ���ؼ� �ּ�
	siCookieEndTime	=	0	;	// ��Ű ���� Ÿ��
	siCookieLimitTime	=	0	;	// ��Ű ��� ���� Ÿ��
	siCookieLevel		=	0	;	// ��Ű ����
	m_odbc.GetData( &siCookieLevel );
	m_odbc.GetData( &siCookieLimitTime );
	m_odbc.GetData( &siCookieEndTime );
	//��Ű����Ʈ �߰�-------------���� ������Ë� �ڽĵ��� �� �߰� ����� �մϴ�.
	//------------------------------------------------------------
	SYSTEMTIME stRevTime	;
	Convert_SYSTEMTIME_from_TIMESTAMP(&stRevTime, &stRevTS );
	sendMsg.m_cFamily.SetChildren(siChildren_PersonID, szChildCharName, stRevTime)	;
	sendMsg.m_cFamily.SetCookie(siChildren_PersonID,siCookieLevel,siCookieEndTime,siCookieLimitTime,MYCLASS_IN_FAMILY_CHILDREN)	;//->DB�۾��� ���ؼ�����
	END_FETCHDATA()
	END_NEXTRECORDSET()



	// send
	SendPacket( (BYTE *)&sendMsg );

}
// �ڽ� ����
void DBGameProtocol::Del_Family_Children()
{
	// ���� ��Ŷ
	sDBRequest_Family_Del_Children	*pRecvMsg = (sDBRequest_Family_Del_Children*)m_pPacket;

	// ���� ��Ŷ
	sDBResponse_Family_Del_Children	sendMsg;

	ZeroMemory(&sendMsg,sizeof(sendMsg))	;

	sendMsg.m_packetHeader.usCmd	= DBMSG_RESPONSE_FAMILY_DEL_CHILDREN;
	sendMsg.m_packetHeader.usSize	= sizeof( sendMsg );

	SI32 siParent_PersonID ;
	TCHAR szParentCharName[MAX_PLAYER_NAME]= TEXT("");

	SI32 siChildren_PersonID ;
	TCHAR szChildCharName[MAX_PLAYER_NAME]= TEXT("");
	SI32 siDateVary	=	0;
	//��Ű����Ʈ �߰�-------------���� ������Ë� �ڽĵ��� �� �߰� ����� �մϴ�.
	SI32 siCookieEndTime	=	0	;	// ��Ű ���� Ÿ��
	SI32 siCookieLimitTime	=	0	;	// ��Ű ��� ���� Ÿ��
	SI32 siCookieLevel		=	0	;	// ��Ű ����
	//��Ű����Ʈ �߰�-------------���� ������Ë� �ڽĵ��� �� �߰� ����� �մϴ�.

	SYSTEMTIME stRevTime	;// ��ȯ�ؼ� ���� �ð�
	TIMESTAMP_STRUCT stRevTS;	//-> db�κ��� ���� ��
	ZeroMemory(&stRevTS, sizeof(stRevTS));

	// DB Query
	BEGIN_SP( "rsp_FamilyDelChild" )
	m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->m_siChildrenPersonID, sizeof(pRecvMsg->m_siChildrenPersonID) );	// ����� �ڽ�
	
	END_SP()
	EXEC_SQL()
	BEGIN_FETCHDATA()
	// �θ� ����
	m_odbc.GetData( &siParent_PersonID);
	m_odbc.GetData( szParentCharName,sizeof(szParentCharName));
	//------------------------------------------------------------
	sendMsg.m_cFamily.SetParent(siParent_PersonID,szParentCharName)	;
	END_FETCHDATA()
	BEGIN_NEXTRECORDSET()
	// �ڽ� ���� 
	BEGIN_FETCHDATA()
	m_odbc.GetData( &siChildren_PersonID);
	m_odbc.GetData( szChildCharName ,sizeof(szChildCharName));
	m_odbc.GetData( &stRevTS );
	//��Ű����Ʈ �߰�-------------���� ������Ë� �ڽĵ��� �� �߰� ����� �մϴ�.->DB�۾��� ���ؼ� ����
	siCookieEndTime	=	0	;	// ��Ű ���� Ÿ��
	siCookieLimitTime	=	0	;	// ��Ű ��� ���� Ÿ��
	siCookieLevel		=	0	;	// ��Ű ����
	m_odbc.GetData( &siCookieLevel );
	m_odbc.GetData( &siCookieLimitTime );
	m_odbc.GetData( &siCookieEndTime );
	//��Ű����Ʈ �߰�-------------���� ������Ë� �ڽĵ��� �� �߰� ����� �մϴ�.
	//------------------------------------------------------------
	
	Convert_SYSTEMTIME_from_TIMESTAMP(&stRevTime, &stRevTS );
	sendMsg.m_cFamily.SetChildren(siChildren_PersonID,szChildCharName,stRevTime)	;
	sendMsg.m_cFamily.SetCookie(siChildren_PersonID,siCookieLevel,siCookieEndTime,siCookieLimitTime,MYCLASS_IN_FAMILY_CHILDREN)	;
	END_FETCHDATA()
	END_NEXTRECORDSET()

		// send
	SendPacket( (BYTE *)&sendMsg );

}
void DBGameProtocol::Get_Family_info()
{
	// ���� ��Ŷ
	sDBRequest_Get_FamilyInfo* pRecvMsg = (sDBRequest_Get_FamilyInfo*)m_pPacket;

	// ���� ��Ŷ
	sDBResponse_Get_FamilyInfo	sendMsg;

	ZeroMemory(&sendMsg,sizeof(sendMsg))	;

	sendMsg.m_packetHeader.usCmd	= DBMSG_RESPONSE_GET_FAMILYINFO;
	sendMsg.m_packetHeader.usSize	= sizeof( sendMsg );

	SI32 siParent_PersonID = 0 ;
	TCHAR szParentCharName[MAX_PLAYER_NAME]	= TEXT("");

	SI32 siChildren_PersonID = 0 ;
	SI32 siDateVary =	0	;
	TCHAR szChildCharName[MAX_PLAYER_NAME]	= TEXT("");
	//��Ű����Ʈ �߰�-------------���� ������Ë� �ڽĵ��� �� �߰� ����� �մϴ�.
	SI32 siCookieEndTime	=	0	;	// ��Ű ���� Ÿ��
	SI32 siCookieLimitTime	=	0	;	// ��Ű ��� ���� Ÿ��
	SI32 siCookieLevel		=	0	;	// ��Ű ����
	//��Ű����Ʈ �߰�-------------���� ������Ë� �ڽĵ��� �� �߰� ����� �մϴ�.

	SYSTEMTIME stRevTime	;// ��ȯ�ؼ� ���� �ð�
	TIMESTAMP_STRUCT stRevTS;	//-> db�κ��� ���� ��
	ZeroMemory(&stRevTS, sizeof(stRevTS));
	
	// DB Query
	BEGIN_SP( "rsp_FamilyInfoGet" )
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->m_siPersonID, sizeof(pRecvMsg->m_siPersonID) );// ������ ��û�� ���.
	END_SP()
	EXEC_SQL()
	BEGIN_FETCHDATA()
	// �θ� ����
		m_odbc.GetData( &siParent_PersonID);
		m_odbc.GetData( szParentCharName,sizeof(szParentCharName));
		//------------------------------------------------------------
		sendMsg.m_cFamily.SetParent(siParent_PersonID,szParentCharName)	;
	END_FETCHDATA()

	BEGIN_NEXTRECORDSET()
	// �ڽ� ���� 
		BEGIN_FETCHDATA()
		m_odbc.GetData( &siChildren_PersonID);
		m_odbc.GetData( szChildCharName ,sizeof(szChildCharName));
		m_odbc.GetData( &stRevTS );
		//��Ű����Ʈ �߰�-------------���� ������Ë� �ڽĵ��� �� �߰� ����� �մϴ�.->db�۾��� ���ؼ� ����
		siCookieEndTime	=	0	;	// ��Ű ���� Ÿ��
		siCookieLimitTime	=	0	;	// ��Ű ��� ���� Ÿ��
		siCookieLevel		=	0	;	// ��Ű ����
		m_odbc.GetData( &siCookieLevel );
		m_odbc.GetData( &siCookieLimitTime );
		m_odbc.GetData( &siCookieEndTime );
		//��Ű����Ʈ �߰�-------------���� ������Ë� �ڽĵ��� �� �߰� ����� �մϴ�.
		//------------------------------------------------------------
		Convert_SYSTEMTIME_from_TIMESTAMP(&stRevTime, &stRevTS );
		sendMsg.m_cFamily.SetChildren(siChildren_PersonID,szChildCharName,stRevTime)	;
		sendMsg.m_cFamily.SetCookie(siChildren_PersonID,siCookieLevel,siCookieEndTime,siCookieLimitTime,MYCLASS_IN_FAMILY_CHILDREN)	;
		END_FETCHDATA()
	END_NEXTRECORDSET()

	sendMsg.m_siPersonID	=	pRecvMsg->m_siPersonID	;
	// send
	SendPacket( (BYTE *)&sendMsg );
}
void DBGameProtocol::Plus_FamilyEffect_date()
{
	// ���� ��Ŷ
	sDBRequest_Family_Plus_Add_Date* pRecvMsg = (sDBRequest_Family_Plus_Add_Date*)m_pPacket;

	// ���� ��Ŷ
	sDBResponse_Family_Plus_Add_Date	sendMsg;

	ZeroMemory(&sendMsg,sizeof(sendMsg))	;

	sendMsg.m_packetHeader.usCmd	= DBMSG_RESPONSE_FAMILY_PLUS_ADD_DATE;
	sendMsg.m_packetHeader.usSize	= sizeof( sendMsg );

	SI32 siParent_PersonID =	0	;
	TCHAR szParentCharName[MAX_PLAYER_NAME]= TEXT("");

	SI32 siChildren_PersonID =	0	;
	TCHAR szChildCharName[MAX_PLAYER_NAME]= TEXT("");
	SI32 siDateVary	=	0	;
	//��Ű����Ʈ �߰�-------------���� ������Ë� �ڽĵ��� �� �߰� ����� �մϴ�.
	SI32 siCookieEndTime	=	0	;	// ��Ű ���� Ÿ��
	SI32 siCookieLimitTime	=	0	;	// ��Ű ��� ���� Ÿ��
	SI32 siCookieLevel		=	0	;	// ��Ű ����
	//��Ű����Ʈ �߰�-------------���� ������Ë� �ڽĵ��� �� �߰� ����� �մϴ�.

	TIMESTAMP_STRUCT stSaveTS;	//-> ���� �����ϴ³�
	ZeroMemory(&stSaveTS, sizeof(stSaveTS));	
	TIMESTAMP_STRUCT stRevTS;	//-> db�κ��� ���� ��
	ZeroMemory(&stRevTS, sizeof(stRevTS));
	SYSTEMTIME stRevTime	;// ��ȯ�ؼ� ���� �ð�

	Convert_TIMESTAMP_from_SYSTEMTIME( &stSaveTS ,&pRecvMsg->m_siDateVary ) 	;

	// DB Query
	BEGIN_SP( "rsp_FamilyEffectDateSet  " )
	m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->m_siPersonID, sizeof(pRecvMsg->m_siPersonID) );// ���
	m_odbc.SetParam( SQL_TIMESTAMP, &stSaveTS, sizeof(stSaveTS) );// ���
	END_SP()
	EXEC_SQL()
	BEGIN_FETCHDATA()
		// �θ� ����
	m_odbc.GetData( &siParent_PersonID);
	m_odbc.GetData( szParentCharName,sizeof(szParentCharName));
	//------------------------------------------------------------
	sendMsg.m_cFamily.SetParent(siParent_PersonID,szParentCharName)	;
	END_FETCHDATA()

	BEGIN_NEXTRECORDSET()
	// �ڽ� ���� 
	BEGIN_FETCHDATA()
	m_odbc.GetData( &siChildren_PersonID);
	m_odbc.GetData( szChildCharName ,sizeof(szChildCharName));
	m_odbc.GetData( &stRevTS );
	//��Ű����Ʈ �߰�-------------���� ������Ë� �ڽĵ��� �� �߰� ����� �մϴ�.->DB�۾��� ���ؼ�����
	siCookieEndTime	=	0	;	// ��Ű ���� Ÿ��
	siCookieLimitTime	=	0	;	// ��Ű ��� ���� Ÿ��
	siCookieLevel		=	0	;	// ��Ű ����
	m_odbc.GetData( &siCookieLevel );
	m_odbc.GetData( &siCookieLimitTime );
	m_odbc.GetData( &siCookieEndTime );
	//��Ű����Ʈ �߰�-------------���� ������Ë� �ڽĵ��� �� �߰� ����� �մϴ�.
	//------------------------------------------------------------
	Convert_SYSTEMTIME_from_TIMESTAMP(&stRevTime, &stRevTS );
	sendMsg.m_cFamily.SetChildren(siChildren_PersonID,szChildCharName,stRevTime)	;
	sendMsg.m_cFamily.SetCookie(siChildren_PersonID,siCookieLevel,siCookieEndTime,siCookieLimitTime,MYCLASS_IN_FAMILY_CHILDREN)	;
	END_FETCHDATA()
	END_NEXTRECORDSET()

	// send
	SendPacket( (BYTE *)&sendMsg );
}
void DBGameProtocol::Set_Cookie_Effect()
{
	// ���� ��Ŷ
	sDBRequest_Set_My_CookeEffect* pRecvMsg = (sDBRequest_Set_My_CookeEffect*)m_pPacket;

	// ���� ��Ŷ
	sDBResponse_Set_My_CookeEffect	sendMsg;

	ZeroMemory(&sendMsg,sizeof(sendMsg))	;

	sendMsg.m_packetHeader.usCmd	= DBMSG_RESPONSE_FAMILY_SET_COOKIE_EFFECT;
	sendMsg.m_packetHeader.usSize	= sizeof( sendMsg );

	SI32 siParent_PersonID =	0	;
	TCHAR szParentCharName[MAX_PLAYER_NAME]= TEXT("");

	SI32 siChildren_PersonID =	0	;
	TCHAR szChildCharName[MAX_PLAYER_NAME]= TEXT("");
	SI32 siDateVary	=	0	;
	//��Ű����Ʈ �߰�-------------���� ������Ë� �ڽĵ��� �� �߰� ����� �մϴ�.
	SI32 siCookieEndTime	=	0	;	// ��Ű ���� Ÿ��
	SI32 siCookieLimitTime	=	0	;	// ��Ű ��� ���� Ÿ��
	SI32 siCookieLevel		=	0	;	// ��Ű ����
	//��Ű����Ʈ �߰�-------------���� ������Ë� �ڽĵ��� �� �߰� ����� �մϴ�.
	
	TIMESTAMP_STRUCT stRevTS;	//-> db�κ��� ���� ��
	ZeroMemory(&stRevTS, sizeof(stRevTS));
	SYSTEMTIME stRevTime	;// ��ȯ�ؼ� ���� �ð�;

	// DB Query
	BEGIN_SP( "rsp_FamilyCookieEffectDateSet" )
	m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->m_siPersonID, sizeof(pRecvMsg->m_siPersonID) );// ��Ű ����Ʈ�� ����� ���
	m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->m_siCookieLevel, sizeof(pRecvMsg->m_siCookieLevel) );// ��Ű ����Ʈ ����
	m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->m_siEndDateVary, sizeof(pRecvMsg->m_siEndDateVary) );// ��Ű ����Ʈ ���� �ð�	
	m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->m_siUseLimitDateVary, sizeof(pRecvMsg->m_siUseLimitDateVary) );// ��Ű ����Ʈ ��� ���� �ð�
	END_SP()
	EXEC_SQL()
	BEGIN_FETCHDATA()
	// �θ� ����
	m_odbc.GetData( &siParent_PersonID);
	m_odbc.GetData( szParentCharName,sizeof(szParentCharName));
	//------------------------------------------------------------
	sendMsg.m_cFamily.SetParent(siParent_PersonID,szParentCharName)	;
	END_FETCHDATA()

	BEGIN_NEXTRECORDSET()
	// �ڽ� ���� 
	BEGIN_FETCHDATA()
	m_odbc.GetData( &siChildren_PersonID);
	m_odbc.GetData( szChildCharName ,sizeof(szChildCharName));
	m_odbc.GetData( &stRevTS );
	//��Ű����Ʈ �߰�-------------���� ������Ë� �ڽĵ��� �� �߰� ����� �մϴ�.
	siCookieEndTime	=	0	;	// ��Ű ���� Ÿ��
	siCookieLimitTime	=	0	;	// ��Ű ��� ���� Ÿ��
	siCookieLevel		=	0	;	// ��Ű ����
	m_odbc.GetData( &siCookieLevel );
	m_odbc.GetData( &siCookieLimitTime );
	m_odbc.GetData( &siCookieEndTime );
	//��Ű����Ʈ �߰�-------------���� ������Ë� �ڽĵ��� �� �߰� ����� �մϴ�.
	//------------------------------------------------------------
	Convert_SYSTEMTIME_from_TIMESTAMP(&stRevTime, &stRevTS );
	sendMsg.m_cFamily.SetChildren(siChildren_PersonID,szChildCharName,stRevTime)	;
	sendMsg.m_cFamily.SetCookie(siChildren_PersonID,siCookieLevel,siCookieEndTime,siCookieLimitTime,MYCLASS_IN_FAMILY_CHILDREN)	;
	END_FETCHDATA()
	END_NEXTRECORDSET()

	sendMsg.m_siPersonID	=	pRecvMsg->m_siPersonID	;
	// send
	SendPacket( (BYTE *)&sendMsg );
}