#ifndef _MSGTYPEVILLAGE_H
#define _MSGTYPEVILLAGE_H

#include "./CityHall/CityHall.h"
#include "NDate.h"

// [�߰� : Ȳ���� 2008. 2. 21 => ���� ������ȸ ���� ���� �˷��ֱ����� ����ü.]
class cltGameMsgResponse_VillageGeneralMeeting{
public:
	bool	m_siVillageGeneralMeeting[MAX_VILLAGE_NUMBER];

	cltGameMsgResponse_VillageGeneralMeeting( void )
	{
		ZeroMemory( this, sizeof( cltGameMsgResponse_VillageGeneralMeeting ) );
	}
}; 



//-------------------------------------------
// ���� ���� �뺸. 
//-------------------------------------------
class cltGameMsgRequest_VillageDetailInfo{
public:

	SI16	siVillageDetailInfoType;

	cltGameMsgRequest_VillageDetailInfo(SI32 detailtype)
	{
		siVillageDetailInfoType = detailtype;
	}
};

class cltGameMsgResponse_VillageDetailInfo{
public:

	SI16	siVillageDetailInfoType;

	union{
		SI32	siWarKillNum[MAX_VILLAGE_NUMBER];		// �������� �뺸. 
		UI32	uiPeople[MAX_VILLAGE_NUMBER];			// �ֹμ�. 
		SI32	siUserNum[MAX_VILLAGE_NUMBER];			// ���� ����ڼ�. 
		GMONEY	siBidMoney[MAX_VILLAGE_NUMBER];			// ����. 
		GMONEY	siStrData[MAX_VILLAGE_NUMBER];			// �ǹ� ������. 
		//SI32	siVillageLevel[MAX_VILLAGE_NUMBER];		// ���� ���� ����. 
		SI16	siVillageWarRecordWinAndLose[2][MAX_VILLAGE_NUMBER];	// ���� ������ ����. �迭�� ���� ���� �¸�, ���� ���� �й� ������
		//SI16	siVillageWarRecordLose[MAX_VILLAGE_NUMBER];
		UI08	uiCityHallState[MAX_VILLAGE_NUMBER];	// ��û��������(����, �Ļ�, ���� �� )
		SI32	siTotalVillageScore[MAX_VILLAGE_NUMBER];// ���� �� ����

	};

	cltGameMsgResponse_VillageDetailInfo()
	{
		ZeroMemory(this, sizeof(cltGameMsgResponse_VillageDetailInfo));
	}
};

class cltGameMsgResponse_DeclareWar{
public:
	SI32		siVillageUnique;
	SI32		siTargetVillage;

	NDate		clDate;

	cltGameMsgResponse_DeclareWar()
	{
		ZeroMemory( this, sizeof(cltGameMsgResponse_DeclareWar) );
	}

};

class cltGameMsgResponse_CancelDeclareWar{
public:
	SI32		siVillageUnique;
	SI32		siTargetVillage;

	cltGameMsgResponse_CancelDeclareWar()
	{
		ZeroMemory( this, sizeof(cltGameMsgResponse_CancelDeclareWar) );
	}
};

class cltGameMsgResponse_VillageWarResult
{
public:
	SI32		siWinVillage;
	SI32		siLoseVillage;

	cltGameMsgResponse_VillageWarResult()
	{
		ZeroMemory( this, sizeof(cltGameMsgResponse_VillageWarResult) );
	}
};


class cltGameMsgResponse_VillageWarResultToVillageMember
{
public:
	SI32		siWinVillage;
	SI32		siLoseVillage;

	SI32		siWinnerGetVillageWarScore;
	GMONEY		siWinnerGetVillageMoney;

	cltGameMsgResponse_VillageWarResultToVillageMember(SI32 WinVillage, SI32 LoseVillage, SI32 WinnerGetVillageWarScore, GMONEY WinnerGetVillageMoney  )
	{
		siWinVillage = WinVillage;
		siLoseVillage = LoseVillage;
		siWinnerGetVillageWarScore = WinnerGetVillageWarScore;
		siWinnerGetVillageMoney = WinnerGetVillageMoney;		
	}
};


class cltGameMsgRequest_SetSymbolStatus
{
public:
	SI16		siStatKind;
	SI32		siStatValue;

	cltGameMsgRequest_SetSymbolStatus( SI16 statKind, SI32 statValue )
	{
		siStatKind = statKind;
		siStatValue = statValue;
	}

};

class cltGameMsgResponse_SetSymbolStatus
{
public:
	SI32		siVillageUnique;

	SI16		siStatKind;
	SI32		siStatValue;

	GMONEY		siCost;

	cltGameMsgResponse_SetSymbolStatus()
	{
		ZeroMemory( this, sizeof( cltGameMsgResponse_SetSymbolStatus ) );
	}

};

class cltGameMsgRequest_SetCastleStatus
{
public:
	SI16		siStatKind;
	SI32		siStatValue;

	cltGameMsgRequest_SetCastleStatus( SI16 statKind, SI32 statValue )
	{
		siStatKind = statKind;
		siStatValue = statValue;
	}

};

class cltGameMsgResponse_SetCastleStatus
{
public:
	SI32		siVillageUnique;

	SI16		siStatKind;
	SI32		siStatValue;

	GMONEY		siCost;

	cltGameMsgResponse_SetCastleStatus()
	{
		ZeroMemory( this, sizeof( cltGameMsgResponse_SetCastleStatus ) );
	}

};

class cltGameMsgRequest_ResidentsList
{
public:
	SI32		siVillageUnique;

	cltGameMsgRequest_ResidentsList( SI32 VillageUnique )
	{
		siVillageUnique = VillageUnique;
	}
};

class cltVillageResidentsList
{
public:
	cltSimplePerson	clPerson;
	SI32			siLevel;
	SI32			siMilitaryMerit;

	cltSimpleRank	clSimpleRank;
		
	TCHAR			strAccountID[ MAX_PLAYER_NAME ];

	void Set( cltVillageResidentsList *pclVillageResidentsObj )
	{
		memcpy( this, pclVillageResidentsObj, sizeof( cltVillageResidentsList ) );
	}

	void Set( cltSimplePerson *pSimplePerson, SI32 Level, SI32 MilitaryMerit, cltSimpleRank *pclSimpleRank, TCHAR *AccountID )
	{
		clPerson.Set( pSimplePerson );
		siLevel = Level;
		siMilitaryMerit = MilitaryMerit;
		
		clSimpleRank.Set( pclSimpleRank );

		memcpy( strAccountID, AccountID, MAX_PLAYER_NAME - 1 );
		strAccountID[ MAX_PLAYER_NAME - 1 ] = '\0';
	}
};

class cltGameMsgResponse_ResidentsList
{
public:
	UI32					uiCount;
	SI32					siVillageUnique;
		
	cltVillageResidentsList	clResident[ MAX_RESIDENT_NUMBER ];

	cltGameMsgResponse_ResidentsList()
	{
		memset( this, 0, sizeof( cltGameMsgResponse_ResidentsList ) );
	}

	void Set( SI32 VillageUnique )
	{
		siVillageUnique = VillageUnique;
	}

	void Add( cltVillageResidentsList *pclVillageResidentsObj )
	{
		if ( uiCount >= MAX_RESIDENT_NUMBER )
		{
			return;
		}

		clResident[ uiCount ++ ].Set( pclVillageResidentsObj );
	}
	
	void Add( cltSimplePerson *pSimplePerson, SI32 Level, SI32 MilitaryMerit, cltSimpleRank *pclSimpleRank, TCHAR *AccountID )
	{
		if ( uiCount >= MAX_RESIDENT_NUMBER )
		{
			return;
		}

		clResident[ uiCount ++ ].Set( pSimplePerson, Level, MilitaryMerit, pclSimpleRank, AccountID );
	}

	SI32 GetTotalSize()
	{
		return sizeof( UI32 ) + sizeof( SI32 ) + sizeof( cltVillageResidentsList ) * ( uiCount );
	}	
};

class cltGameMsgResponse_ResidentLogin
{
public:	
	SI32					siVillageUnique;
	TCHAR					strCharName[ MAX_PLAYER_NAME ];
	
	cltGameMsgResponse_ResidentLogin( SI32 VillageUnique, TCHAR *CharName )
	{
		siVillageUnique = VillageUnique;
		memcpy ( strCharName, CharName, MAX_PLAYER_NAME );
		strCharName[ MAX_PLAYER_NAME - 1 ] = NULL;
	}
};

class cltGameMsgRequest_SetVillageMark
{
public:
	SI32		siVillageMark;

	cltGameMsgRequest_SetVillageMark( SI32 villagemark )
	{
		siVillageMark = villagemark;
	}

};

class cltGameMsgResponse_SetVillageMark
{
public:

	SI32		siVillageUnique;
	SI32		siVillageMark;

	cltGameMsgResponse_SetVillageMark( SI32 villageunique, SI32 villagemark )
	{
		siVillageUnique = villageunique;
		siVillageMark = villagemark;
	}
};


class cltGameMsgRequest_SetVillageMap
{
public:
	enum {
		MAPTYPE_CITYHALL = 	1			, // �����
		MAPTYPE_BANK					, // ������� 
		MAPTYPE_STOCK					, // ������� 
		MAPTYPE_MARKET					, // �������
		MAPTYPE_HOUSE					, // �������
		MAPTYPE_HUNT					, // ��������� 
		MAPTYPE_POSTOFFICE				, // ��ü�����
		MAPTYPE_PORT					, // �������
		MAPTYPE_HORSEMARKET				, // �纹�����
		MAPTYPE_REALESTATEMARKET		, // �Ű����
		MAPTYPE_SUMMONMARKET			, // �忹�����
		MAPTYPE_LAND					, // �������  
		MAPTYPE_FEAST					, // ���ڽ����
		MAPTYPE_SUMMONHEROMARKET		, // �񺯻����
		MAPTYPE_MINE					, // �������
		MAPTYPE_GUILD					, // ������ 	
	};

	SI32		siVillageMapUnique;
	SI08		siMapType;

	cltGameMsgRequest_SetVillageMap( SI32 mapunique, SI08 maptype)
	{
		siVillageMapUnique = mapunique;
		siMapType = maptype;
	}

};

class cltGameMsgResponse_SetVillageMap
{
public:

	SI32		siVillageUnique;
	SI32		siVillageMapUnique;

	cltGameMsgResponse_SetVillageMap( SI32 villageunique, SI32 mapunique )
	{
		siVillageUnique = villageunique;
		siVillageMapUnique = mapunique;
	}
};

class cltGameMsgResponse_SetVillageUpgrade
{
public:
	SI32		siVillageUnique[10] ;

	cltGameMsgResponse_SetVillageUpgrade(SI32 * villageunique)
	{
		for ( SI32 i = 0 ; i < 10 ; i ++ )
		{
			siVillageUnique[i] = villageunique[i];
		}
	}
};


//[����] ������ ������ �����ϴ� ��Ŷ. C->S => 2008-4-3
class cltGameMsgRequest_AddVillageScore
{
public:
	SI32		m_siAddVillageScore;

	cltGameMsgRequest_AddVillageScore(SI32 _siAddVillageScore)
	{
		m_siAddVillageScore = _siAddVillageScore;
	}

};

//[����] ������ ������ �����ϴ� ��Ŷ. S->C => 2008-4-3
class cltGameMsgResponse_AddVillageScore
{
public:

	SI32		m_siVillageUnique;
	SI32		m_siAddVillageScore;

	cltGameMsgResponse_AddVillageScore( SI32 _siVillageUnique, SI32 _siAddVillageScore )
	{
		m_siVillageUnique   = _siVillageUnique;
		m_siAddVillageScore = _siAddVillageScore;
	}
};

//[����] ���� ������ �̺�Ʈ(���� ����/��Ƽ�콺(�Ұ��縮/Ű�޶�))�� ���󳻿�ó��
class cltGameMsgResponse_Event_MonsterAttack_Reward
{
public:
	SI32		m_siCharExp;
	SI32		m_siFameExp;
	SI32		m_siRewardItemUnique;
	SI32		m_siRewardItemNum;

	cltGameMsgResponse_Event_MonsterAttack_Reward(SI32 charexp, SI32 fameexp, SI32 rewarditemunique, SI32 rewarditemnum)
	{
		ZeroMemory( this, sizeof(cltGameMsgResponse_Event_MonsterAttack_Reward) );

		m_siCharExp = charexp;
		m_siFameExp = fameexp;
		m_siRewardItemUnique = rewarditemunique;
		m_siRewardItemNum = rewarditemnum;
	}
};


#endif