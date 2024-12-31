#ifndef _DBMSGEMPIRE_H
#define _DBMSGEMPIRE_H

#include "DBMsg.h"
#include "../../GoonZuWorld/Server/Empire/EmpireManager.h"

//***************************************************************************************************
//
// Class Name 		: sDBRequest_CreateEmpire
//
// Last Modified 	: 2007 / 10 / 15 
// Created		 	: �豤��
//
// Function			: [��û]������ �����.
//
//*************************************************************************************************** 
class sDBRequest_CreateEmpire
{
public:

	sPacketHeader	packetHeader;
	
	/// ������ ����� ���
	SI32			siCharID;
	/// �������� ���ְ� �� ����
	SI32			siVillageUnique;
	/// ���� ���鶧 �ʿ��� �ݾ�
	SI64			siNeedMoney;

	sDBRequest_CreateEmpire( SI32 CharID, SI32 VillageUnique, SI64 NeedMoney )
	{
		packetHeader.usSize = sizeof( sDBRequest_CreateEmpire );
		packetHeader.usCmd = DBMSG_REQUEST_CREATEEMPIRE;

		siCharID = CharID;
		siVillageUnique = VillageUnique;
		siNeedMoney = NeedMoney;
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBResponse_CreateEmpire
//
// Last Modified 	: 2007 / 10 / 15 
// Created		 	: �豤��
//
// Function			: [����]������ �����.
//
//*************************************************************************************************** 
class sDBResponse_CreateEmpire
{
public:
	sPacketHeader	packetHeader;

	SI32 siResult;
	SI32 siCharID;
	/// ������� ���� ����ũ
	SI32 siEmpireUnique;
	/// ������ ������� �Ŀ� ���ְ� �� ����
	SI32			siVillageUnique;
	/// ������ ����� ���� ������ ���ͱ�
	SI64 siLeftProfitMoney;			

	sDBResponse_CreateEmpire()
	{
		ZeroMemory( this, sizeof( sDBResponse_CreateEmpire ) );
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBRequest_DestroyEmpire
//
// Last Modified 	: 2007 / 10 / 15 
// Created		 	: �豤��
//
// Function			: [��û]������ ��ü�ȴ�( �ý��������� )
//
//*************************************************************************************************** 
class sDBRequest_DestroyEmpire
{
public:

	sPacketHeader	packetHeader;

	/// ��ü�� ���� ����ũ
	SI32			siEmpireUnique;

	sDBRequest_DestroyEmpire( SI32 EmpireUnique )
	{
		packetHeader.usSize = sizeof( sDBRequest_DestroyEmpire );
		packetHeader.usCmd = DBMSG_REQUEST_DESTROYEMPIRE;

		siEmpireUnique = EmpireUnique;
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBResponse_DestroyEmpire
//
// Last Modified 	: 2007 / 10 / 15 
// Created		 	: �豤��
//
// Function			: [����]������ ��ü�ȴ�( �ý��������� )
//
//*************************************************************************************************** 
class sDBResponse_DestroyEmpire
{
public:
	sPacketHeader	packetHeader;

	SI32 siResult;
	/// ��ü�� ������ �ҼӵǾ� �ִ� ���� ����ũ
	SI32 siVillageUnique[MAX_EMPIRE_IN_VILLAGE];
	/// ��ü�� ������ �ҼӵǾ� �ִ� ��� ����ũ
	SI32 siGuildUnique[MAX_EMPIRE_IN_GUILD];			

	sDBResponse_DestroyEmpire()
	{
		ZeroMemory( this, sizeof( sDBResponse_DestroyEmpire ) );
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBRequest_JoinEmpire
//
// Last Modified 	: 2007 / 10 / 16 
// Created		 	: �豤��
//
// Function			: [��û]������ ���� ��û�� �Ѵ�.
//
//*************************************************************************************************** 
class sDBRequest_JoinEmpire
{
public:

	sPacketHeader	packetHeader;

	enum { VILLAGE = 0, GUILD };
	/// ���� ������ ��û�ϴ� ���
	SI32			siCharID;
	/// ���� ������ ��û�޴� ���
	SI32			siOtherCharID;
	/// ������ ���� �����ϴ���, ���� ���� �����ϴ���
	SI32			siJoinType;
	/// ������ ������ ����ũ
	SI32			siEmpireUnique;
	/// ������ ������ ������ ����ũ
	SI32			siVillageUnique;
	/// ������ ������ ����� ����ũ
	SI32			siGuildUnique;

	sDBRequest_JoinEmpire( SI32 CharID, SI32 OtherCharID, SI32 JoinType, 
		                   SI32 EmpireUnique, SI32 VillageUnique, SI32 GuildUnique )
	{
		packetHeader.usSize = sizeof( sDBRequest_JoinEmpire );
		packetHeader.usCmd = DBMSG_REQUEST_JOINEMPIRE;

		siCharID = CharID;
		siOtherCharID = OtherCharID;
		siJoinType = JoinType;
		siEmpireUnique = EmpireUnique;
		siVillageUnique = VillageUnique;
		siGuildUnique = GuildUnique;
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBResponse_JoinEmpire
//
// Last Modified 	: 2007 / 10 / 16 
// Created		 	: �豤��
//
// Function			: [����]���� �������׼� ���� ��û�� �޴´�
//
//*************************************************************************************************** 
class sDBResponse_JoinEmpire
{
public:
	sPacketHeader	packetHeader;

	SI32 siResult;
	/// ���� ������ ��û�ϴ� ���
	SI32			siCharID;
	/// ���� ������ ��û�޴� ���
	SI32			siOtherCharID;
	/// ���Ե� ������ ����ũ
	SI32			siEmpireUnique;
	/// ������ ���� �����ϴ���, ���� ���� �����ϴ���
	SI32			siJoinType;
	/// ������ ������ ������ ����ũ
	SI32			siVillageUnique;
	/// ������ ������ ����� ����ũ
	SI32			siGuildUnique;
	
	sDBResponse_JoinEmpire()
	{
		ZeroMemory( this, sizeof( sDBResponse_JoinEmpire ) );
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBRequest_SecedeEmpire
//
// Last Modified 	: 2007 / 10 / 16 
// Created		 	: �豤��
//
// Function			: [��û]�������� Ż���Ѵ�
//
//*************************************************************************************************** 
class sDBRequest_SecedeEmpire
{
public:

	sPacketHeader	packetHeader;

	enum { VILLAGE = 0, GUILD };
	/// ���� Ż�� ��û�ϴ� ���
	SI32			siCharID;
	/// Ż�� ���ְ� �ϴ���(true), �ƴϸ� ������ �Ҽӵ� ������� ��帶���Ͱ� �ϴ���(false)
	bool			bSecedeEmpireByEmperor; 
	/// ������ ���� Ż���ϴ���, ���� ���� Ż���ϴ���
	SI32			siSecedeType;
	/// Ż���� ������ ����ũ
	SI32			siEmpireUnique;
	/// �������� Ż���� ������ ����ũ
	SI32			siVillageUnique;
	/// �������� Ż���� ����� ����ũ
	SI32			siGuildUnique;

	sDBRequest_SecedeEmpire( SI32 CharID, bool SecedeEmpireByEmperor, SI32 SecedeType, 
		SI32 EmpireUnique, SI32 VillageUnique, SI32 GuildUnique )
	{
		packetHeader.usSize = sizeof( sDBRequest_SecedeEmpire );
		packetHeader.usCmd = DBMSG_REQUEST_SECEDEEMPIRE;

		siCharID = CharID;
		bSecedeEmpireByEmperor = SecedeEmpireByEmperor;
		siSecedeType = SecedeType;
		siEmpireUnique = EmpireUnique;
		siVillageUnique = VillageUnique;
		siGuildUnique = GuildUnique;
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBResponse_SecedeEmpire
//
// Last Modified 	: 2007 / 10 / 16 
// Created		 	: �豤��
//
// Function			: [����]�������� Ż���Ѵ�
//
//*************************************************************************************************** 
class sDBResponse_SecedeEmpire
{
public:
	sPacketHeader	packetHeader;

	SI32 siResult;
	/// ���� Ż�� ��û�ϴ� ���
	SI32			siCharID;
	/// Ż�� ���ְ� �ϴ���(true), �ƴϸ� ������ �Ҽӵ� ������� ��帶���Ͱ� �ϴ���(false)
	bool			bSecedeEmpireByEmperor; 
	/// ������ ���� Ż���ϴ���, ���� ���� Ż���ϴ���
	SI32			siSecedeType;
	/// Ż���ϴ� ���� ����ũ
	SI32			siEmpireUnique;
	/// �������� Ż���� ������ ����ũ
	SI32			siVillageUnique;
	/// �������� Ż���� ����� ����ũ
	SI32			siGuildUnique;

	sDBResponse_SecedeEmpire()
	{
		ZeroMemory( this, sizeof( sDBResponse_SecedeEmpire ) );
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBRequest_AllEmpireInfo
//
// Last Modified 	: 2007 / 10 / 15 
// Created		 	: �豤��
//
// Function			: [��û] DB�� ����� ���� ������ ��û�Ѵ�.
//
//*************************************************************************************************** 
class sDBRequest_AllEmpireInfo
{
public:

	sPacketHeader	packetHeader;

	sDBRequest_AllEmpireInfo()
	{
		packetHeader.usSize = sizeof( sDBRequest_AllEmpireInfo );
		packetHeader.usCmd = DBMSG_REQUEST_ALLEMPIREINFO;
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBResponse_AllEmpireInfo
//
// Last Modified 	: 2007 / 10 / 15 
// Created		 	: �豤��
//
// Function			: [����] DB�� ����� ���� ������ ��û�Ѵ�.
//
//*************************************************************************************************** 
class sDBResponse_AllEmpireInfo
{
public:
	sPacketHeader	packetHeader;

	CEmpireUnitInfo clEmpireInfo[MAX_EMPIRENUMBER];

	sDBResponse_AllEmpireInfo()
	{
		ZeroMemory( this, sizeof( sDBResponse_AllEmpireInfo ) );
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBRequest_SetEmpireMoney
//
// Last Modified 	: 2007 / 10 / 26 
// Created		 	: �豤��
//
// Function			: [��û] ���� �ں����� �����Ѵ�.( ���ϰų� ���� )
//
//*************************************************************************************************** 
class sDBRequest_SetEmpireMoney
{
public:

	sPacketHeader	packetHeader;

	enum { USER = 0, SYSTEM };
	/// ��ü�� ��������, �ý�������
	SI16 siType;
	/// ���� �ں����� �ִ� ���
	SI32 siCharID;
	/// ���� �ں����� ��ȭ�� ���� ����ũ
	SI32 siEmpireUnique;
	/// ��� �������� ���� �ں����� �ִ���
	SI32 siVillageUnique;
	/// ���ϰų� �� �ݾ�( ��� �Ǵ� ���� )
	SI64 siAddMoney;

	sDBRequest_SetEmpireMoney( SI16 Type, SI32 CharID, SI32 EmpireUnique, SI32 VillageUnique, SI64 AddMoney )
	{
		packetHeader.usSize = sizeof( sDBRequest_SetEmpireMoney );
		packetHeader.usCmd = DBMSG_REQUEST_SETEMPIREMONEY;

		siType = Type; 
		siCharID = CharID; 
		siEmpireUnique = EmpireUnique; 
		siVillageUnique = VillageUnique; 
		siAddMoney = AddMoney; 
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBResponse_SetEmpireMoney
//
// Last Modified 	: 2007 / 10 / 26
// Created		 	: �豤��
//
// Function			: [����] ���� �ں����� �����Ѵ�.( ���ϰų� ���� )
//
//*************************************************************************************************** 
class sDBResponse_SetEmpireMoney
{
public:
	sPacketHeader	packetHeader;

	/// ���ϰ�
	SI32	siResult;
	/// ���� �ں����� �ִ� ���
	SI32	siCharID;
	/// ���� �ں����� ����� ���� ����ũ
	SI32	siEmpireUnique;
	/// ���� �ں����� ���� ����
	SI32	siVillageUnique;
	/// �ٲ� ���� �ں���
	SI64	siLeftEmpireMoney;
	/// �ٲ� ���� ���ͱ�
	SI64	siLeftVillageProfitMoney;
	/// ���� �ں����� ���� �������� �������� ������ ������ �ݾ�
	SI64	siInputTotalEmpireMoney;
	///	���� �ں��� ���� ��
	SI64	siAddMoney;

	sDBResponse_SetEmpireMoney()
	{
		ZeroMemory( this, sizeof( sDBResponse_SetEmpireMoney ) );
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBRequest_ChangeEmperor
//
// Last Modified 	: 2007 / 10 / 26 
// Created		 	: �豤��
//
// Function			: [��û] ���� ���ְ� �ٲ��( ����, ������ �ٲ�� )
//
//*************************************************************************************************** 
class sDBRequest_ChangeEmperor
{
public:

	sPacketHeader	packetHeader;

	/// ���� ���ְ� �� ���
	SI32	siCharID;
	/// ���ο� ���� PersonID
	SI32	siNewEmperorPersonID;
	/// ���ְ� �ٲ� ���� ����ũ
	SI32	siEmpireUnique;
	/// ���� ���� ���� ����ũ
	SI32	siOldEmperorVillageUnique;
	/// ���ο� ���� ���� ����ũ
	SI32	siNewEmperorVillageUnique;
	
	sDBRequest_ChangeEmperor( SI32 CharID, SI32 NewEmperorPersonID, 
		                      SI32 EmpireUnique, SI32 NewEmperorVillageUnique )
	{
		packetHeader.usSize = sizeof( sDBRequest_ChangeEmperor );
		packetHeader.usCmd = DBMSG_REQUEST_CHANGEEMPEROR;

		siCharID = CharID; 
		siNewEmperorPersonID = NewEmperorPersonID; 
		siEmpireUnique = EmpireUnique; 
		siNewEmperorVillageUnique = NewEmperorVillageUnique; 
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBResponse_ChangeEmperor
//
// Last Modified 	: 2007 / 10 / 26
// Created		 	: �豤��
//
// Function			: [����] ���� ���ְ� �ٲ��( ����, ������ �ٲ�� )
//
//*************************************************************************************************** 
class sDBResponse_ChangeEmperor
{
public:
	sPacketHeader	packetHeader;

	/// ���ϰ�
	SI32	siResult;
	/// ���� ���ְ� �� ���
	SI32	siCharID;
	/// ���� ���� PersonID
	SI32	siOldEmperorPersonID;
	/// ���ο� ���� PersonID
	SI32	siNewEmperorPersonID;
	/// ���ְ� �ٲ� ���� ����ũ
	SI32	siEmpireUnique;
	/// ���� ���� ���� ����ũ
	SI32	siOldEmperorVillageUnique;
	/// ���ο� ���� ���� ����ũ
	SI32	siNewEmperorVillageUnique;
	/// ���� ���� �ں���
	SI64	siLeftEmpireMoney;
	
	sDBResponse_ChangeEmperor()
	{
		ZeroMemory( this, sizeof( sDBResponse_ChangeEmperor ) );
	}
};

#endif