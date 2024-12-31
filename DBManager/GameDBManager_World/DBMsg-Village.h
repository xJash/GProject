#ifndef _DBMSGVILLAGE_H
#define _DBMSGVILLAGE_H

#include "DBMsg.h"

//***************************************************************************************************
//
// Class Name 		: sDBRequest_VillageEventSuccess
//
// Last Modified 	: 2005 / 12 / 12 
// Created		 	: �豤��
//
// Function			: ���� �̺�Ʈ�� ���������� DB�� ����� ���� �̺�Ʈ Ƚ���� ���� ��Ų��
//
//*************************************************************************************************** 
class sDBRequest_VillageEventSuccess
{
public:
	sPacketHeader	packetHeader;

	SI32			siVillageUnique;
	

	sDBRequest_VillageEventSuccess( SI32 VillageUnique  )
	{
		packetHeader.usSize = sizeof( sDBRequest_VillageEventSuccess );
		packetHeader.usCmd = DBMSG_REQUEST_VILLAGEEVENTSUCCESS;

		siVillageUnique = VillageUnique;
		
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBRequest_VillageWarKillNumber
//
// Last Modified 	: 2005 / 12 / 13 
// Created		 	: �豤��
//
// Function			: ������ ������ ���� �������� DB�� ������
//
//*************************************************************************************************** 
class sDBRequest_VillageWarKillNumber
{
public:
	sPacketHeader	packetHeader;

	SI32			siVillageUnique[MAX_VILLAGE_NUMBER];
	SI32			siVillageWarKillNumber[MAX_VILLAGE_NUMBER];

	sDBRequest_VillageWarKillNumber( SI32* VillageUnique, SI32* VillageWarKillNumber )
	{
		packetHeader.usSize = sizeof( sDBRequest_VillageWarKillNumber );
		packetHeader.usCmd = DBMSG_REQUEST_VILLAGEWARKILLNUMBER;

		SI32 i;
		for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
		{
			if( VillageUnique[i] > 0 )
			{
				siVillageUnique[i]			= VillageUnique[i];
				siVillageWarKillNumber[i]	= VillageWarKillNumber[i];
			}
			else
			{
				siVillageUnique[i] = 0;
				siVillageWarKillNumber[i] = 0;
			}
		}
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBRequest_VillageResidentsVisitorsInfo
//
// Last Modified 	: 2005 / 12 / 13 
// Created		 	: �豤��
//
// Function			: [��û]��ü �ֹμ��� ���� �湮�ڼ��� DB�� ������
//
//*************************************************************************************************** 
class sDBRequest_VillageResidentsVisitorsInfo
{
public:
	sPacketHeader	packetHeader;

	sDBRequest_VillageResidentsVisitorsInfo()
	{
		packetHeader.usSize = sizeof( sDBRequest_VillageResidentsVisitorsInfo );
		packetHeader.usCmd = DBMSG_REQUEST_VILLAGERESIDENTSVISITORSINFO;
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBResponse_VillageResidentsVisitorsInfo
//
// Last Modified 	: 2006 / 03 / 09 
// Created		 	: �豤��
//
// Function			: [����]��ü �ֹμ��� ���� �湮�ڼ��� DB�� ������
//
//*************************************************************************************************** 
class sDBResponse_VillageResidentsVisitorsInfo
{
public:
	sPacketHeader	packetHeader;

	SI32 siResult;

	sDBResponse_VillageResidentsVisitorsInfo()
	{
		ZeroMemory( this, sizeof( sDBResponse_VillageResidentsVisitorsInfo ) );
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBRquest_VillageJoinPlayTime
//
// Last Modified 	: 2005 / 12 / 14
// Created		 	: �豤��
//
// Function			: ������ ���� ���� �� �÷��� �ð��� DB�� ������!!
//
//***************************************************************************************************
class sDBRequest_VillageJoinPlayTime
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;					
	SI32				siVillageJoinPlayTime;
	
	// PCK : ���Ե� ���� ����ũ (�α׿�)
	SI32				siVillageUnique;

	sDBRequest_VillageJoinPlayTime( SI32 PersonId, SI32 VillageJoinPlayTime, SI32 VillageUnique )
	{
		packetHeader.usSize = sizeof( sDBRequest_VillageJoinPlayTime );
		packetHeader.usCmd = DBMSG_REQUEST_VILLAGEJOINPLAYTIME;

		siPersonID = PersonId;
		siVillageJoinPlayTime = VillageJoinPlayTime;
		siVillageUnique = VillageUnique;
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBRquest_VillageJoinLevelUp
//
// Last Modified 	: 2005 / 12 / 14
// Created		 	: �豤��
//
// Function			: ������ ���� ���� �� ������ Ƚ��
//
//***************************************************************************************************
class sDBRequest_VillageJoinLevelUp
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;					
	
	// PCK : ������ Ƚ��, ���� ����ũ �߰�
	SI32				siLevelCount;
	SI32				siVillageUnique;

	sDBRequest_VillageJoinLevelUp( SI32 PersonId, SI32 LevelCount, SI32 VillageUnique )
	{
		packetHeader.usSize = sizeof( sDBRequest_VillageJoinLevelUp );
		packetHeader.usCmd = DBMSG_REQUEST_VILLAGEJOINLEVELUP;

		siPersonID = PersonId;
		siLevelCount = LevelCount;
		siVillageUnique = VillageUnique;
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBRquest_VillageJoinWarKillNumber
//
// Last Modified 	: 2005 / 12 / 14
// Created		 	: �豤��
//
// Function			: ���� ���� �Ŀ� �������� ������
//
//***************************************************************************************************
class sDBRequest_VillageJoinWarKillNumber
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;					
	SI32				siVillageJoinWarKillNumber;

	sDBRequest_VillageJoinWarKillNumber( SI32 PersonId, SI32 VillageJoinWarKillNumber )
	{
		packetHeader.usSize = sizeof( sDBRequest_VillageJoinWarKillNumber );
		packetHeader.usCmd = DBMSG_REQUEST_VILLAGEJOINWARKILLNUMBER;

		siPersonID = PersonId;
		siVillageJoinWarKillNumber = VillageJoinWarKillNumber;
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBRquest_VillageJoinMakeRareItem
//
// Last Modified 	: 2005 / 12 / 14
// Created		 	: �豤��
//
// Function			: ���� ���� �Ŀ� ��ǰȽ���� ����Ѵ�
//
//***************************************************************************************************
class sDBRequest_VillageJoinMakeRareItem
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;					
	
	sDBRequest_VillageJoinMakeRareItem( SI32 PersonId )
	{
		packetHeader.usSize = sizeof( sDBRequest_VillageJoinMakeRareItem );
		packetHeader.usCmd = DBMSG_REQUEST_VILLAGEJOINMAKERAREITEM;

		siPersonID = PersonId;
	}
};


//***************************************************************************************************
//
// Class Name 		: sDBRequest_VillageJoinMakeItem
//
// Last Modified 	: 2006 / 03 / 06
// Created		 	: �豤��
//
// Function			: ���� ���� �Ŀ� ������ ���� ����ġ
//
//***************************************************************************************************
class sDBRequest_VillageJoinMakeItem
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;		
	SI32				siItemSkillExp;

	// PCK : ���� ����ũ �߰�
	SI32				siVillageUnique;

	sDBRequest_VillageJoinMakeItem( SI32 PersonId, SI32 ItemSkillExp, SI32 VillageUnique )
	{
		packetHeader.usSize = sizeof( sDBRequest_VillageJoinMakeItem );
		packetHeader.usCmd = DBMSG_REQUEST_VILLAGEJOINMAKEITEM;

		siPersonID = PersonId;
		siItemSkillExp = ItemSkillExp;
		siVillageUnique = VillageUnique;
	}
};

//[����] ������ ������ �����ϴ� ��Ŷ. S->DB => 2008-4-3
class sDBRequest_Add_Village_Score
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;	

	SI32				m_siVillageUnique;		// ���� ����ũ.
	SI32				m_siAddVillageScore;    // �߰��� ���� ����.

	sDBRequest_Add_Village_Score(SI32 _siVillageUnique, SI32 _siAddVillageScore)
	{
		packetHeader.usSize = sizeof( sDBRequest_Add_Village_Score );
		packetHeader.usCmd  = DBMSG_REQUEST_ADD_VILLAGE_SCORE;
		
		m_siVillageUnique   = _siVillageUnique;
		m_siAddVillageScore = _siAddVillageScore;
	}

};

//[����] ������ ������ �����ϴ� ��Ŷ. DB->S => 2008-4-3
class sDBResponse_Add_Village_Score
{
public:
	sPacketHeader	packetHeader;

	SI32			siResult;
	SI32			m_siVillageUnique;		// ���� ����ũ.
	SI32			m_siVillageScore;		// ���� ���� ����.
	SI32			m_siAddVillageScore;	// �߰��� ���� ����. (+,-)

	sDBResponse_Add_Village_Score(void)
	{
		ZeroMemory(this, sizeof(sDBResponse_Add_Village_Score));
	}

	sDBResponse_Add_Village_Score(SI32 _siVillageUnique, SI32 _siVillageScore)
	{
		m_siVillageUnique   = _siVillageUnique;
		m_siVillageScore	= _siVillageScore;
	}
};

// PCK : ������ ���� ���� �� �÷��� �ð� (�α׿� ��Ŷ)
class sDBReponse_VillageJoinPlayTime
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;					
	SI32				siVillageJoinPlayTime;
	SI32				siVillageUnique;

	sDBReponse_VillageJoinPlayTime()
	{
		ZeroMemory(this, sizeof(sDBReponse_VillageJoinPlayTime));
	}
};

// PCK : ������ ���� ���� �� ������ Ƚ�� (�α׿� ��Ŷ)
class sDBResponse_VillageJoinLevelUp
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;					
	SI32				siLevelCount;
	SI32				siVillageUnique;

	sDBResponse_VillageJoinLevelUp()
	{
		ZeroMemory(this, sizeof(sDBResponse_VillageJoinLevelUp));
	}
};

// PCK : ���� �����Ŀ� ������ ���� ����ġ (�α׿� ��Ŷ)
class sDBResponse_VillageJoinMakeItem
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;		
	SI32				siItemSkillExp;
	SI32				siVillageUnique;

	sDBResponse_VillageJoinMakeItem()
	{
		ZeroMemory(this, sizeof(sDBResponse_VillageJoinMakeItem));
	}
};
#endif