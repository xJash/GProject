#ifndef _DBMSG_FAMILY_H_
#define _DBMSG_FAMILY_H_

#include "DBMsg.h"
#include "DBMsg-Person.h"
#include "../../common/Family/Family.h"

//[����] ���� �ý��� - �ڳ� ��� 
class sDBRequest_Family_Add_Children
{
public:
	sPacketHeader	m_packetHeader			;
	SI32			m_siParentPersonID		;	// �߰��ϴ� �θ� �ɸ���
	TCHAR			m_szParentName[MAX_PLAYER_NAME]			;	// �߰��ϴ� �θ� �ɸ���
	SI32			m_siChildrenPersonID	;	// �߰��� �ڽ� �ɸ���
	TCHAR			m_ChildrenName[MAX_PLAYER_NAME]			;	// �߰��� �ڽ� �ɸ���
	SYSTEMTIME		m_stCurrentTime			;	// �߰� �� �ð�,.
public:
	sDBRequest_Family_Add_Children( SI32 siParentPersonID, TCHAR* szParentName, SI32 siChildrenPersonID, TCHAR* szChildrenName, SYSTEMTIME stCurrentTime )
	{
		m_packetHeader.usCmd	=	DBMSG_REQUEST_FAMILY_ADD_CHILDREN;
		m_packetHeader.usSize	=	sizeof(sDBRequest_Family_Add_Children);
		m_siParentPersonID		=	siParentPersonID	;
		m_siChildrenPersonID	=	siChildrenPersonID	;
		memcpy( m_szParentName, szParentName, MAX_PLAYER_NAME );
		memcpy( m_ChildrenName, szChildrenName, MAX_PLAYER_NAME );
		m_stCurrentTime	=	stCurrentTime	;
	}
};


class sDBResponse_Family_Add_Children
{
public:
	sPacketHeader			m_packetHeader;
	SI32					m_siResult	;
	CFamily					m_cFamily;
public:
	sDBResponse_Family_Add_Children()
	{
		ZeroMemory( this, sizeof(sDBResponse_Family_Add_Children) );
	}

};
//[����] ���� �ý��� - �ڳ� ����
class sDBRequest_Family_Del_Children
{
public:
	sPacketHeader	m_packetHeader			;	
	SI32			m_siChildrenPersonID	;	// ������ �ڳ�
public:
	sDBRequest_Family_Del_Children( SI32 siChildrenPersonID )
	{
		m_packetHeader.usCmd	= DBMSG_REQUEST_FAMILY_DEL_CHILDREN;
		m_packetHeader.usSize	= sizeof(sDBRequest_Family_Del_Children);
		m_siChildrenPersonID	=	siChildrenPersonID	;
	}
};


class sDBResponse_Family_Del_Children
{
public:
	sPacketHeader			m_packetHeader;
	CFamily					m_cFamily;
public:
	sDBResponse_Family_Del_Children()
	{
		ZeroMemory( this, sizeof(sDBResponse_Family_Del_Children) );
	}
};

//[����] ���� �ý��� - ���� ȿ�� ����
class sDBRequest_Family_Plus_Add_Date
{
public:
	sPacketHeader	m_packetHeader	;
	SI32			m_siPersonID	;	// �Ⱓ�� �ø� ���
	SYSTEMTIME		m_siDateVary	;	// �÷��� �Ⱓ.
public:
	sDBRequest_Family_Plus_Add_Date( SI32 siPersonID , SYSTEMTIME siDateVary )
	{
		m_packetHeader.usCmd	= DBMSG_REQUEST_FAMILY_PLUS_ADD_DATE;
		m_packetHeader.usSize	= sizeof(sDBRequest_Family_Plus_Add_Date);
		m_siPersonID	=	siPersonID	;
		m_siDateVary	=	siDateVary	;
	}
};


class sDBResponse_Family_Plus_Add_Date	
{
public:
	sPacketHeader	m_packetHeader	;
	SI32			m_siResult		;	
	CFamily			m_cFamily;
public:
	sDBResponse_Family_Plus_Add_Date()
	{
		ZeroMemory( this, sizeof(sDBResponse_Family_Plus_Add_Date) );
	}
};;

#endif
