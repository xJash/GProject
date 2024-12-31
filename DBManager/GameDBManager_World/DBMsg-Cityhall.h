#ifndef _DBMSGCITYHALL_H
#define _DBMSGCITYHALL_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "DBMsg.h"
#include "..\..\GoonZuWorld\CommonLogic\Cityhall\GeneralMeeting.h"
#include "..\..\GoonZuWorld\CommonLogic\Cityhall\Cityhall.h"
#include "..\..\GoonZuWorld\Server\Candidate\Candidate.h"


//-----------------------------------------
// ��û�� ���ĺ��� ���� ��û�Ѵ�. 
//-----------------------------------------
class sDBRequest_Candidate
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;				// ���ĺ���. 
	cltSimpleRank		clRank;					// ���ĺ� ��� �ź�. 

	sDBRequest_Candidate()
	{
		ZeroMemory(this, sizeof(sDBRequest_Candidate));
	}

	sDBRequest_Candidate(SI32 id, SI32 personid, cltSimpleRank* pclrank)
	{
		packetHeader.usSize = sizeof( sDBRequest_Candidate );
		packetHeader.usCmd = DBMSG_REQUEST_CANDIDATE;
		usCharID			= id;

		siPersonID			= personid;
		clRank.Set(pclrank);
	}
};


class sDBResponse_Candidate
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.

	SI32				siIndex;			// ���ĺ��� ���� ������ �ε���. 
	cltSimplePerson		clPerson;			// ���ĺ����� ����. 
	cltSimpleRank		clRank;				// ���ĺ��� �ź� 

	sDBResponse_Candidate()
	{
		ZeroMemory(this, sizeof(sDBResponse_Candidate));
	}
};

//-----------------------------------------
// ��û�� ���ĺ��� ���� ����� ���� ��û�Ѵ�. 
//-----------------------------------------
class sDBRequest_CancelCandidate
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;				// ���ĺ���. 

	sDBRequest_CancelCandidate()
	{
		ZeroMemory(this, sizeof(sDBRequest_CancelCandidate));
	}

	sDBRequest_CancelCandidate(SI32 id, SI32 personid)
	{
		packetHeader.usSize = sizeof( sDBRequest_CancelCandidate );
		packetHeader.usCmd = DBMSG_REQUEST_CANCELCANDIDATE;
		usCharID			= id;

		siPersonID			= personid;
	}
};


class sDBResponse_CancelCandidate
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.

	SI32				siIndex;			// ���ĺ��� ���� ������ �ε���. 
	cltSimplePerson		clPerson;			// ���ĺ����� ����. 
	cltSimpleRank		clRank;				// ���ĺ��� �ź� 

	sDBResponse_CancelCandidate()
	{
		ZeroMemory(this, sizeof(sDBResponse_CancelCandidate));
	}
};


//-----------------------------------------
// Person�� Ư�� Rank�� ����� �� ���� ��û�Ѵ�. 
//-----------------------------------------
class sDBRequest_BeRank
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;			// ����̵Ǵ� Person
	SI32				siCandidateIndex;	// �ĺ��� �ε���. 
	cltSimpleRank		clRank;				// Rank����.

	sDBRequest_BeRank()
	{
		ZeroMemory(this, sizeof(sDBRequest_BeRank));
	}

	sDBRequest_BeRank(SI32 id, SI32 personid, SI32 candidateindex, cltSimpleRank* pclrank)
	{
		packetHeader.usSize = sizeof( sDBRequest_BeRank );
		packetHeader.usCmd = DBMSG_REQUEST_BERANK;
		usCharID			= id;

		siPersonID			= personid;
		siCandidateIndex	= candidateindex;
		clRank.Set(pclrank);
	}
};


class sDBResponse_BeRank
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.

	cltRank				clRank;				// ��� �ź��� ��� �Ǿ��°� ?

	SI32				siCandidateIndex;	// �ĺ��� �ε���. 
	cltSimplePerson		clCandidatePerson;	// �ĺ����� �ֽ� ����. 

	sDBResponse_BeRank()
	{
		ZeroMemory(this, sizeof(sDBResponse_BeRank));
	}
};


//-----------------------------------------
// �������� �ĺ��� ������ ���� ���� ��û�Ѵ�. 
//-----------------------------------------
class sDBRequest_ManyCandidateInfo
{
public:
	sPacketHeader		packetHeader;

	cltSimpleRank		clRank;

	sDBRequest_ManyCandidateInfo()
	{
		ZeroMemory(this, sizeof(sDBRequest_ManyCandidateInfo));
	}

	sDBRequest_ManyCandidateInfo(cltSimpleRank* pclrank)
	{
		packetHeader.usSize = sizeof( sDBRequest_ManyCandidateInfo );
		packetHeader.usCmd = DBMSG_REQUEST_MANYCANDIDATEINFO;

		clRank.Set(pclrank);
	}
};


class sDBResponse_ManyCandidateInfo
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.

	cltSimpleRank		clRank;							// ���ĺ��� �ź�
	cltSimplePerson		clPerson[MAX_CANDIDATE_NUMBER];	// �ĺ��� ���. (�ε����� �ǹ� ����)��

	sDBResponse_ManyCandidateInfo()
	{
		ZeroMemory(this, sizeof(sDBResponse_ManyCandidateInfo));
	}
};


//-----------------------------------------
// ��ϵ� �ĺ����� ��� �����Ѵ�. 
//-----------------------------------------
class sDBRequest_DelCandidate
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	cltSimpleRank		clRank;		// ������ �ź�. (�� �źп� ���ĺ��� ������� ����� ��� �����Ѵ�.) 

	sDBRequest_DelCandidate()
	{
		ZeroMemory(this, sizeof(sDBRequest_DelCandidate));
	}

	sDBRequest_DelCandidate(SI32 id, cltSimpleRank* pclrank)
	{
		packetHeader.usSize = sizeof( sDBRequest_DelCandidate );
		packetHeader.usCmd = DBMSG_REQUEST_DELCANDIDATE;

		usCharID	= id;

		clRank.Set(pclrank);
	}
};


class sDBResponse_DelCandidate
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.

	cltSimpleRank		clRank;				// ���ĺ��� �ź�

	sDBResponse_DelCandidate()
	{
		ZeroMemory(this, sizeof(sDBResponse_DelCandidate));
	}
};

//-----------------------------------------
// ��ϵ� �ź����� �����Ѵ�. 
//-----------------------------------------
class sDBRequest_Resign
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;	// ����� �Ǵ� Person
	cltSimpleRank		clRank;		// ������ �ź�. 

	sDBRequest_Resign()
	{
		ZeroMemory(this, sizeof(sDBRequest_Resign));
	}

	sDBRequest_Resign(SI32 id, SI32 personid, cltSimpleRank* pclrank)
	{
		packetHeader.usSize = sizeof( sDBRequest_Resign );
		packetHeader.usCmd	= DBMSG_REQUEST_RESIGN;

		usCharID	= id;
		siPersonID	= personid;

		clRank.Set(pclrank);
	}
};


class sDBResponse_Resign
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.

	cltSimpleRank		clRank;				// ������ �ź�
	cltSimplePerson		clPerson;			// ������ �źп� ��������� ���� Person����. 

//#if defined(_CITYHALL_BANKRUPTCY)
	cltDate				clDate;				// ������ ����
	SI32				siVillageUnique;	// ������ ���� ���� => �������� ���ſ� ���
//#endif

	sDBResponse_Resign()
	{
		ZeroMemory(this, sizeof(sDBResponse_Resign));
	}
};



//-----------------------------------------
// ������ NPC����� ��û�Ѵ� 
//-----------------------------------------
enum{HIRENPC_HIRENPC, HIRENPC_HIREEVENTNPC}; //npc ��� ��� 
class sDBRequest_HireNPC
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;			// VillageUnique

	UI16				usSlot;						// slot
	cltHiredNPC			clHireNPCInfo;				// NPC Info
	UI08				uiMode;						// NPC ��� �̳� Tree ����̳�

	sDBRequest_HireNPC( UI16 id, SI32 villageunique, UI16 slot, SI32 npckind, GMONEY hirepay, GMONEY monthlypay, cltDate *hireDate , UI08 mode )
	{

		packetHeader.usSize = sizeof( sDBRequest_HireNPC );
		packetHeader.usCmd = DBMSG_REQUEST_HIRENPC;

		usCharID = id;

		siVillageUnique	= villageunique;

		usSlot = slot;

		clHireNPCInfo.siNPCKind = npckind;
		clHireNPCInfo.siHirePay = hirepay;
		clHireNPCInfo.siMonthlyPay = monthlypay;
		clHireNPCInfo.clHireDate.Set( hireDate );
		
		uiMode = mode;

	}

};

class sDBResponse_HireNPC
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;					// �����.

	SI32				siVillageUnique;			// VillageUnique

	UI16				usSlot;						// slot
	cltHiredNPC			clHireNPCInfo;				// NPCInfo


	cltMoney			clCityhallMoney;			// ��� �����ڱ� 
	
	UI08				uiMode;						// NPC ����̳� Ʈ�� ����̳�

	sDBResponse_HireNPC()
	{
		ZeroMemory( this, sizeof( sDBResponse_HireNPC ) );
	}

};



//---------------------------------------
// �ֹ� ����� ��û�Ѵ� 
//---------------------------------------
class sDBRequest_ApplyResident
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;					// person ID
	SI32				siVillageUnique;			// ������ VillageUnique
	cltDate				clDate;						// ��û��

	bool				bSendMsg;					// ������ ���� ��û�� �ƴ� �ٸ� ĳ���� �ʴ�� ��û�� �ȰŶ� ����� �޾� ������ �޽��� ó���� ����. 


	sDBRequest_ApplyResident( SI32 id, SI32 personid, SI32 villageUnique, cltDate *pclDate, bool _bSendMsg = false )
	{

		packetHeader.usSize = sizeof( sDBRequest_ApplyResident );
		packetHeader.usCmd = DBMSG_REQUEST_APPLYRESIDENT;

		usCharID		= id;

		siPersonID		= personid;
		siVillageUnique	= villageUnique;

		clDate.Set( pclDate );
		
		bSendMsg = _bSendMsg;
	}

};

//---------------------------------------
// �ֹ� ��� ��û�� �����Ѵ�
//---------------------------------------
class sDBResponse_ApplyResident
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;					// ���: 1���� 0���� -1�̹� ��û�Ǿ����� -2�̹� �ֹ��� -3��û���ʰ�

    cltResidentApplyer	clApplyer;					// ��û�� ����
	SI32				siVillageUnique;			// ������ VillageUnique (-1�̰ų� -2�� ��� �ش縶���� �ڵ带 ��ȯ)

	bool				bSendMsg;					// ������ ���� ��û�� �ƴ� �ٸ� ĳ���� �ʴ�� ��û�� �ȰŶ� ����� �޾� ������ �޽��� ó���� ����. 

	sDBResponse_ApplyResident()
	{
		ZeroMemory( this, sizeof( sDBResponse_ApplyResident ) );
	}

};

//---------------------------------------
// �ֹ� ��� ��û�� ����Ʈ�� ��û�Ѵ� 
//---------------------------------------
class sDBRequest_GetResidentApplyerList
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;			// ������ VillageUnique

	sDBRequest_GetResidentApplyerList( UI16 id, SI32 villageUnique )
	{
		packetHeader.usSize = sizeof( sDBRequest_GetResidentApplyerList );
		packetHeader.usCmd = DBMSG_REQUEST_GETRESIDENTAPPLYERLIST;

		usCharID		= id;

		siVillageUnique = villageUnique;
	}

};


//---------------------------------------
// �ֹ� ��� ��û�� ����Ʈ�� ��ȯ�Ѵ�
//---------------------------------------
class sDBResponse_GetResidentApplyerList
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;					// ���: 1���� 0����

	SI32				siVillageUnique;
	
	cltResidentApplyer	clApplyer[ MAX_RESIDENT_APPLYER ];

	sDBResponse_GetResidentApplyerList()
	{
		ZeroMemory( this, sizeof( sDBResponse_GetResidentApplyerList ) );
	}

};


//---------------------------------------
// �ֹ� ����Ʈ�� ��û�Ѵ� 
//---------------------------------------
class sDBRequest_GetResidentList
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;			// ������ VillageUnique
	SI32				siSort;

	sDBRequest_GetResidentList( UI16 id, SI32 villageUnique, SI32 sort )
	{
		packetHeader.usSize = sizeof( sDBRequest_GetResidentList );
		packetHeader.usCmd = DBMSG_REQUEST_GETRESIDENTLIST;

		usCharID		= id;

		siVillageUnique = villageUnique;
		siSort = sort;
	}

};


//---------------------------------------
// �ֹ� ����Ʈ�� ��ȯ�Ѵ�
//---------------------------------------
class sDBResponse_GetResidentList
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;					// ���: 1���� 0����

	SI32				siVillageUnique;
	
	cltResident			clResident[ MAX_RESIDENT_NUMBER ];

	sDBResponse_GetResidentList()
	{
		ZeroMemory( this, sizeof( sDBResponse_GetResidentList ) );
	}

};


//---------------------------------------
// �ֹ� ��� ��û�� �㰡�Ѵ� 
//---------------------------------------
class sDBRequest_BeResident
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;
	SI32				siVillageUnique;

	cltDate				clDate;						// �����
	
	bool				bAutoResident;				// �̰��� true �̸� ������û����Ʈ�� ��� ���Եȴ�


	sDBRequest_BeResident( UI16 id, SI32 personid, SI32 villageUnique, cltDate *pclDate, bool autoResident ) 
	{
		packetHeader.usSize = sizeof( sDBRequest_BeResident );
		packetHeader.usCmd = DBMSG_REQUEST_BERESIDENT;

		usCharID		= id;

		siPersonID		= personid;
		siVillageUnique = villageUnique;

		clDate.Set( pclDate );

		bAutoResident	= autoResident;

	}

};


//---------------------------------------
// �ֹ� ��� ��û �㰡������ ����
//---------------------------------------
class sDBResponse_BeResident
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;					// 1:����	0:����

	SI32				siVillageUnique;

	cltResident			clResident;

	sDBResponse_BeResident()
	{
		ZeroMemory( this, sizeof( sDBResponse_BeResident ) );
	}

};


//---------------------------------------
// �ֹ� ��� ��û�� ����Ѵ� or �ֹε���� �����Ѵ� 
//---------------------------------------
class sDBRequest_CancelResident
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;
	SI32				siVillageUnique;

	bool				bAutoCancel;

	sDBRequest_CancelResident( UI16 id, SI32 personid, SI32 villageUnique, bool autoCancel )
	{
		packetHeader.usSize = sizeof( sDBRequest_CancelResident );
		packetHeader.usCmd = DBMSG_REQUEST_CANCELRESIDENT;

		usCharID		= id;

		siPersonID		= personid;
		siVillageUnique = villageUnique;

		bAutoCancel		= autoCancel;
	}

};



//---------------------------------------
// �ֹ� ��� ��û ��� �� ���� ��û�� ���� ���� 
//---------------------------------------
class sDBResponse_CancelResident
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;					// 1:����	0:����

	SI32				siPersonID;					// personid
	SI32				siVillageUnique;			// ���� ����ũ 

	SI32				siResidentNum;				// ���� �ֹ� ���� 
	
	sDBResponse_CancelResident()
	{
		ZeroMemory( this, sizeof( sDBResponse_CancelResident ) );
	}

};

//---------------------------------------
// �ֹ� �� ������ ��û�Ѵ� 
//---------------------------------------
class sDBRequest_GetResidentInfo
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;
	TCHAR				szPersonName[MAX_PLAYER_NAME];

	sDBRequest_GetResidentInfo( UI16 id, SI32 villageUnique, TCHAR *personName )
	{
		packetHeader.usCmd = DBMSG_REQUEST_GETRESIDENTINFO;
		packetHeader.usSize = sizeof( sDBRequest_GetResidentInfo );

		usCharID = id;

		siVillageUnique = villageUnique;

		memcpy( szPersonName, personName, MAX_PLAYER_NAME );
		szPersonName[ MAX_PLAYER_NAME - 1 ] = NULL;
	}
};


//---------------------------------------
// �ֹ� �� ���� ��û�� ���� ����
//---------------------------------------
class sDBResponse_GetResidentInfo
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;							// 1:����, 0:����

	SI32				siVillageUnique;

	TCHAR				szPersonName[MAX_PLAYER_NAME];
	SI32				siPersonID;

	SI32				siScore;

	cltDate				clRegDate;


	sDBResponse_GetResidentInfo()
	{
		ZeroMemory( this, sizeof( sDBResponse_GetResidentInfo ) );
	}
};

class sDBRequest_SetResidentScore
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;
	
	SI32				siVillageUnique;
	SI32				siPersonID;
	SI32				siScore;

	sDBRequest_SetResidentScore( SI32 villageUnique, SI32 personid, SI32 score )
	{
		packetHeader.usCmd = DBMSG_REQUEST_SETRESIDENTSCORE;
		packetHeader.usSize = sizeof( sDBRequest_SetResidentScore );

		siVillageUnique = villageUnique;
		siPersonID = personid;
		siScore = score;
	}

};

class sDBResponse_SetResidentScore
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;


};

class sDBRequest_CityHallSetInOutMoney
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;						// ���� 
	SI32				siStrType;								// ����� �ǹ�
	SI32				siInOutCode;							// ����� �ڵ�
	cltDate				clDate;									// ������� 
	cltMoney			clInOutMoney;							// ����ݾ� 
	cltMoney			clCityHallMoney;						// ��ܺ����ڱ�

	sDBRequest_CityHallSetInOutMoney( SI32 villageunique, SI32 strtype, SI32 inoutcode, cltDate *pclDate, cltMoney *pclMoney, cltMoney *pclCityhallMoney )
	{
		packetHeader.usCmd = DBMSG_REQUEST_CITYHALL_SETINOUTMONEY;
		packetHeader.usSize = sizeof( sDBRequest_CityHallSetInOutMoney );

		siVillageUnique = villageunique;
		siStrType = strtype;
		siInOutCode = inoutcode;
		clDate.Set( pclDate );
		clInOutMoney.Set( pclMoney );
		clCityHallMoney.Set( pclCityhallMoney );
	}
};

// PCK : �α׿� ����
class sDBResponse_CityHallSetInOutMoney
{
public:
	sPacketHeader	packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;						// ���� 
	SI32				siStrType;								// ����� �ǹ�
	SI32				siInOutCode;							// ����� �ڵ�
	cltDate				clDate;									// ������� 
	cltMoney			clInOutMoney;							// ����ݾ� 
	cltMoney			clCityHallMoney;						// ��ܺ����ڱ�

	sDBResponse_CityHallSetInOutMoney()
	{
		ZeroMemory( this, sizeof( sDBResponse_CityHallSetInOutMoney ) );
	}
};
class sDBRequest_SetVillageSymbol
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;						// ����
	
	SI16				siSymbolKind;							// �ɺ�(��ȣ��) ����
	SI32				siSymbolLife;							// �ɺ�(��ȣ��) ü��
	SI32				siSymbolMana;							// �ɺ�(��ȣ��) Mana
	SI16				siSymbolCapa;							// �ɺ�(��ȣ��) ���� 

	sDBRequest_SetVillageSymbol( SI32 villageunique, SI16 symbolKind, SI32 symbolLife, SI32 symbolMana, SI16 symbolCapa )
	{
		packetHeader.usCmd = DBMSG_REQUEST_SETVILLAGESYMBOL;
		packetHeader.usSize = sizeof( sDBRequest_SetVillageSymbol );

		siVillageUnique = villageunique;
		
		siSymbolKind = symbolKind;
		siSymbolLife = symbolLife;
		siSymbolMana = symbolMana;
		siSymbolCapa = symbolCapa;
	}

};


class sDBRequest_SetSymbolStatus
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;						// ����

	SI16				siStatKind;								// ���� ����: 1:����  2: ü��  3:Mana  4:����
	SI32				siStatValue;							// ���� ��ġ

	GMONEY				siCost;									// ���� ���
	cltDate				clDate;

	sDBRequest_SetSymbolStatus( SI32 id, SI32 villageunique, SI16 statKind, SI32 statValue, GMONEY cost, cltDate *pclDate )
	{
		packetHeader.usCmd = DBMSG_REQUEST_SETSYMBOLSTATUS;
		packetHeader.usSize = sizeof( sDBRequest_SetSymbolStatus );

		usCharID = id;
		siVillageUnique = villageunique;
		siStatKind = statKind;
		siStatValue = statValue;
		siCost = cost;
		clDate.Set( pclDate );
	}
};

class sDBResponse_SetSymbolStatus
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;								// ���: 1:���� 0:���� 2:��ܺ����ڱݺ���

	SI32				siVillageUnique;						// ����

	SI16				siStatKind;								// ���� ���� 
	SI32				siStatValue;							// ���� ��ġ

	GMONEY				siCost;									// ���� ���
	cltDate				clDate;									// �ð�

	cltMoney			clCityhallMoney;						// ��� �ڱ� 

	sDBResponse_SetSymbolStatus()
	{
		ZeroMemory( this, sizeof( sDBResponse_SetSymbolStatus ) );
	}
};


class sDBRequest_SetVillageCastle
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;						// ����
	
	SI16				siCastleKind;							// ĳ�� ����
	SI32				siCastleLife;							// ĳ�� ü��
	SI32				siCastleMana;							// ĳ�� Mana
	SI16				siCastleCapa;							// ĳ�� ���� 

	sDBRequest_SetVillageCastle( SI32 villageunique, SI16 castleKind, SI32 castleLife, SI32 castleMana, SI16 castleCapa )
	{
		packetHeader.usCmd = DBMSG_REQUEST_SETVILLAGECASTLE;
		packetHeader.usSize = sizeof( sDBRequest_SetVillageCastle );

		siVillageUnique = villageunique;
		
		siCastleKind = castleKind;
		siCastleLife = castleLife;
		siCastleMana = castleMana;
		siCastleCapa = castleCapa;
	}

};


class sDBRequest_SetCastleStatus
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;						// ����

	SI16				siStatKind;								// ���� ����: 1:����  2: ü��  3:Mana  4:����
	SI32				siStatValue;							// ���� ��ġ

	GMONEY				siCost;									// ���� ���
	cltDate				clDate;

	sDBRequest_SetCastleStatus( SI32 id, SI32 villageunique, SI16 statKind, SI32 statValue, GMONEY cost, cltDate *pclDate )
	{
		packetHeader.usCmd = DBMSG_REQUEST_SETCASTLESTATUS;
		packetHeader.usSize = sizeof( sDBRequest_SetCastleStatus );

		usCharID = id;
		siVillageUnique = villageunique;
		siStatKind = statKind;
		siStatValue = statValue;
		siCost = cost;
		clDate.Set( pclDate );
	}
};

class sDBResponse_SetCastleStatus
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;								// ���: 1:���� 0:���� 2:��ܺ����ڱݺ���

	SI32				siVillageUnique;						// ����

	SI16				siStatKind;								// ���� ���� 
	SI32				siStatValue;							// ���� ��ġ

	GMONEY				siCost;									// ���� ���
	cltDate				clDate;									// �ð�

	cltMoney			clCityhallMoney;						// ��� �ڱ� 

	sDBResponse_SetCastleStatus()
	{
		ZeroMemory( this, sizeof( sDBResponse_SetCastleStatus ) );
	}
};

class sDBRequest_ResidentShare
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;


	SI32				siVillageUnique;
	cltMoney 			clTotalShareMoney;				// �� ����

	SI32				siCount;						// ����� ���� 

	SI32				siCharIndex[ 100 ];
	SI32				siPersonID[ 100 ];				// PersonID
	GMONEY				siShareMoney[ 100 ];			// ���� 

	sDBRequest_ResidentShare()
	{
		packetHeader.usCmd = DBMSG_REQUEST_RESIDENTSHARE;
		packetHeader.usSize = sizeof( sDBRequest_ResidentShare );
	}
};

class sDBResponse_ResidentShare
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;

	SI32				siVillageUnique;
	
	cltMoney			clTotalShareMoney;				// �� ���� 
	cltMoney			clCityhallMoney;

	SI32				siCount;						// ����� ����

	SI32				siCharIndex[ 100 ];
	SI32				siPersonID[ 100 ];				// PersonID
	GMONEY				siShareMoney[ 100 ];
	GMONEY				siMoney[ 100 ];					// ���� ������ 

	sDBResponse_ResidentShare()
	{
		ZeroMemory( this, sizeof( sDBResponse_ResidentShare ) );
	}
};

class sDBRequest_SetVillageLevel
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;
	SI32				siLevel;

	SI32				siSlaveVillageNum;
	SI32				siResidentLevel;
	SI32				siVisitLevel;

	sDBRequest_SetVillageLevel( SI32 villageunique, SI32 level, SI32 slave, SI32 resident, SI32 visit )
	{
		packetHeader.usCmd = DBMSG_REQUEST_SETVILLAGELEVEL;
		packetHeader.usSize = sizeof( sDBRequest_SetVillageLevel );

		siVillageUnique = villageunique;
		siLevel = level;

		siSlaveVillageNum = slave;
		siResidentLevel = resident;
		siVisitLevel = visit;
	}

};

class sDBResponse_SetVillageLevel
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;

	SI32				siVillageUnique;
	SI32				siLevel;

	SI32				siSlaveVillageNum;
	SI32				siResidentLevel;
	SI32				siVisitLevel;

	sDBResponse_SetVillageLevel()
	{
		ZeroMemory( this, sizeof( sDBResponse_SetVillageLevel ) );
	}


};


// ���ͱ� -> �ں������� ��ȯ
class sDBRequest_ProfitToCapitalFund
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;			// villageunique
	GMONEY				siMoney;					// ��ȯ�� �ݾ�

	sDBRequest_ProfitToCapitalFund( UI16 id, SI32 villageunique, GMONEY money )
	{
		packetHeader.usCmd = DBMSG_REQUEST_PROFITTOCAPITALFUND;
		packetHeader.usSize = sizeof( sDBRequest_ProfitToCapitalFund );
		
		usCharID = id;
		siVillageUnique = villageunique;
		siMoney = money;
	}

};

class sDBResponse_ProfitToCapitalFund
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;					// 1:���� 0:���� 2:���ͱ� ����
	
	SI32				siVillageUnique;

	cltMoney			clCapitalFund;				// �ں���
	cltMoney			clProfitMoney;				// ���ͱ�

	sDBResponse_ProfitToCapitalFund()
	{
		ZeroMemory( this, sizeof( sDBResponse_ProfitToCapitalFund ) );
	}

};


class sDBRequest_SetVillageMap
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;
	SI32				siVillageMapIndex;
	GMONEY				siNeedMoney;
	SI08				siMapType;

	sDBRequest_SetVillageMap( UI16 id, SI32 villageunique, SI32 villagemap, GMONEY needmoney, SI08 maptype )
	{
		packetHeader.usCmd = DBMSG_REQUEST_SETVILLAGEMAP;
		packetHeader.usSize = sizeof( sDBRequest_SetVillageMap );

		usCharID = id;

		siVillageUnique = villageunique;
		siVillageMapIndex = villagemap;
		siNeedMoney = needmoney;
		siMapType = maptype;
	}


};

class sDBResponse_SetVillageMap
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;
	
	SI32				siResult;

	SI32				siVillageUnique;
	SI32				siVillageMapIndex;
	GMONEY				siNeedMoney;
	SI08				siMapType;

	sDBResponse_SetVillageMap()
	{
		ZeroMemory( this, sizeof( sDBResponse_SetVillageMap ) );
	}

};

class sDBRequest_ManyResidentOut
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;
	cltDate				clDate;

	sDBRequest_ManyResidentOut( SI32 villageunique, cltDate *pclDate )
	{
		packetHeader.usCmd = DBMSG_REQUEST_MANYRESIDENTOUT;
		packetHeader.usSize = sizeof( sDBRequest_ManyResidentOut );

		siVillageUnique = villageunique;
		clDate.Set( pclDate );

	}
};

class sDBResponse_ManyResidentOut
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;

	SI32				siVillageUnique;
	cltDate				clDate;

	UI16				usCount;
	SI32				siPersonID[ 200 ];

	sDBResponse_ManyResidentOut()
	{
		ZeroMemory( this, sizeof( sDBResponse_ManyResidentOut ) );
	}
};


// ���� ��ȸ ������ ��û�Ѵ� 
class sDBRequest_GeneralMeetingInfo
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;

	sDBRequest_GeneralMeetingInfo( SI32 villageunique )
	{
		packetHeader.usCmd = DBMSG_REQUEST_GENERALMEETING_INFO;
		packetHeader.usSize = sizeof(sDBRequest_GeneralMeetingInfo);

		siVillageUnique = villageunique;
	}

};

class sDBResponse_GeneralMeetingInfo
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;

	SI32				siVillageUnique;			
	SI32				siMatterType;						// �Ȱ� ���� 
	SI32				siPersonID;							// ������ personid
	cltDate				clStartDate;						// ���� ������ ��������
	cltDate				clCloseDate;						// ���� ����
	SI32				siTotalStock;						// ���� �� �ֽļ� 
	SI32				siCandidatePersonID;				// ����� �ĺ��� person id
	TCHAR				szCandidateName[ MAX_PLAYER_NAME ];	// ����� �ĺ��� �̸� 
	SI32				siAcceptCandidate;					// ����� �ĺ��� ���� ���� 

	cltGeneralMeetingVoter	voter[ 100 ];					// ��ǥ���� ����

	sDBResponse_GeneralMeetingInfo()
	{
		ZeroMemory( this, sizeof( sDBResponse_GeneralMeetingInfo ) );
	}

};

// ������ȸ�� ����� �Ӹ���� �����Ѵ� 
class sDBRequest_GeneralMeeting_SuggestChief
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;					// ���� 
	SI32				siPersonID;							// ������ personid

	TCHAR				szCandidateName[ MAX_PLAYER_NAME ];	// �ĺ��� name
	SI32				siStartDate;
	cltDate				clCloseDate;

	sDBRequest_GeneralMeeting_SuggestChief( UI16 id, SI32 villageunique, SI32 personid, TCHAR *candidate, SI32 StartDate, cltDate *pclDate )
	{
		packetHeader.usCmd = DBMSG_REQUEST_GENERALMEETING_SUGGEST_CHIEF;
		packetHeader.usSize = sizeof(sDBRequest_GeneralMeeting_SuggestChief);

		usCharID = id;

		siVillageUnique = villageunique;
		siPersonID = personid;

		memcpy( szCandidateName, candidate, MAX_PLAYER_NAME );
		szCandidateName[ MAX_PLAYER_NAME - 1 ] = NULL;
		siStartDate = StartDate;
		clCloseDate.Set( pclDate );
	}

};

class sDBResponse_GeneralMeeting_SuggestChief
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;

	SI32				siVillageUnique;					// ���� 
	SI32				siTotalStock;						// ���� �� �ֽ� ��
	SI32				siPersonID;							// ������ personid
	SI32				siStockAmount;						// �������� �ش� ���� �����ֽļ� 

	cltDate				clStartDate;						// ���� ���� ��
	cltDate				clCloseDate;

	SI32				siCandidatePersonID;				// �ĺ��� personid
	TCHAR				szCandidateName[ MAX_PLAYER_NAME ];	// �ĺ��� name

	cltGeneralMeetingVoter	clVoter[ 100 ];					// ��ǥ���� ����

	sDBResponse_GeneralMeeting_SuggestChief()
	{
		ZeroMemory( this, sizeof( sDBResponse_GeneralMeeting_SuggestChief ) );
	}

};

//[�߰� : Ȳ���� 2008. 2. 20 => ���� ������ȸ ���� ���θ� ��ڰ� �����ϰ� �� ��Ŷ.]
class sDBRequest_GeneralMeeting_Suggest_On_Off
{
public:
	sPacketHeader		m_packetHeader;
	
	SI32				m_siVillageUnique;					// ���� 
	
    bool				m_bGeneralMeeting_Suggest_On_Off;
	
	sDBRequest_GeneralMeeting_Suggest_On_Off( SI32 _villageunique, bool _On_Off )
	{
		m_packetHeader.usCmd  = DBMSG_REQUEST_GENERALMEETING_SUGGEST_ON_OFF;
		m_packetHeader.usSize = sizeof(sDBRequest_GeneralMeeting_Suggest_On_Off);

		m_siVillageUnique				 = _villageunique;
		m_bGeneralMeeting_Suggest_On_Off = _On_Off;
	}
};

class sDBResponse_GeneralMeeting_Suggest_On_Off
{
public:
	sPacketHeader		m_packetHeader;
	
	SI32				m_siResult;

	SI32				m_siVillageUnique;					// ���� 

	bool				m_bGeneralMeeting_Suggest_On_Off;

	sDBResponse_GeneralMeeting_Suggest_On_Off()
	{
		ZeroMemory( this, sizeof( sDBResponse_GeneralMeeting_Suggest_On_Off ) );

		m_packetHeader.usCmd  = DBMSG_RESPONSE_GENERALMEETING_SUGGEST_ON_OFF;
		m_packetHeader.usSize = sizeof(sDBResponse_GeneralMeeting_Suggest_On_Off);
	}

};


//[�߰� : Ȳ���� 2008. 2. 20 => ���� ������ȸ ���� ���θ� ��ڰ� �����ϰ� �� ��Ŷ.]
class sDBRequest_GeneralMeeting_Suggest_On_Off_List
{
public:
	sPacketHeader		m_packetHeader;


	sDBRequest_GeneralMeeting_Suggest_On_Off_List( SI32 _villageunique, bool _On_Off )
	{
		m_packetHeader.usCmd  = DBMSG_REQUEST_GENERALMEETING_SUGGEST_ON_OFF_LIST;
		m_packetHeader.usSize = sizeof(sDBRequest_GeneralMeeting_Suggest_On_Off_List);
	}
};

class sDBResponse_GeneralMeeting_Suggest_On_Off_List
{
public:
	sPacketHeader		m_packetHeader;

	bool				m_bGeneralMeeting_Suggest_On_Off_List[MAX_VILLAGE_NUMBER];

	sDBResponse_GeneralMeeting_Suggest_On_Off_List()
	{
		ZeroMemory( this, sizeof( sDBResponse_GeneralMeeting_Suggest_On_Off_List ) );

		m_packetHeader.usCmd  = DBMSG_RESPONSE_GENERALMEETING_SUGGEST_ON_OFF_LIST;
		m_packetHeader.usSize = sizeof(sDBResponse_GeneralMeeting_Suggest_On_Off_List);
	}

};





//---------------







// ��ǥ�Ѵ� 
class sDBRequest_GeneralMeeting_Vote
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;
	SI32				siVoterPersonID;

	SI32				siVoteType;

	sDBRequest_GeneralMeeting_Vote( UI16 id, SI32 villageunique, SI32 personid, SI32 votetype )
	{
		packetHeader.usCmd = DBMSG_REQUEST_GENERALMEETING_VOTE;
		packetHeader.usSize = sizeof(sDBRequest_GeneralMeeting_Vote);

		usCharID = id;

		siVillageUnique = villageunique;
		siVoterPersonID = personid;
		siVoteType = votetype;
	}

};

class sDBResponse_GeneralMeeting_Vote
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;

	SI32				siVillageUnique;
	SI32				siVoterPersonID;
	TCHAR				szVoterName[ MAX_PLAYER_NAME ];

	SI32				siVoteType;

	sDBResponse_GeneralMeeting_Vote()
	{
		ZeroMemory( this, sizeof( sDBResponse_GeneralMeeting_Vote ) );
	}

};

// ����� �ĺ��ڰ� ���� ���Ǹ� �Ѵ� 
class sDBRequest_GeneralMeeting_AcceptCandidate
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;
	SI32				siPersonID;

	//KHY - 1115 - ������ȸ �ߵ� ���� ����. - 	����� �ĺ��ڰ� ���� ���Ǹ� �ϴ� ���� 2���� ��ǥ�Ⱓ���� �����Ѵ�.
	SI32				siStartDate;
	cltDate				clCloseDate;

	sDBRequest_GeneralMeeting_AcceptCandidate( UI16 id, SI32 villageunique, SI32 personid ,SI32 StartDate, cltDate *pclDate)
	{
		packetHeader.usCmd = DBMSG_REQUEST_GENERALMEETING_ACCEPTCANDIDATE;
		packetHeader.usSize = sizeof(sDBRequest_GeneralMeeting_AcceptCandidate);

		usCharID = id;

		siVillageUnique = villageunique;
		siPersonID = personid;

		siStartDate = StartDate;
		clCloseDate.Set( pclDate );
	}

};

class sDBResponse_GeneralMeeting_AcceptCandidate
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;

	SI32				siVillageUnique;
	SI32				siPersonID;

	//KHY - 1115 - ������ȸ �ߵ� ���� ����. - 	����� �ĺ��ڰ� ���� ���Ǹ� �ϴ� ���� 2���� ��ǥ�Ⱓ���� �����Ѵ�.
	SI32				siStartDate;
	cltDate				clCloseDate;

	sDBResponse_GeneralMeeting_AcceptCandidate()
	{
		ZeroMemory( this, sizeof( sDBResponse_GeneralMeeting_AcceptCandidate ) );
	}

};

// ����� �Ӹ�� ������ȸ�� �����Ѵ�
class sDBRequest_GeneralMeeting_CloseChief
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;
	
	cltDate				clDate;

	SI32				siVillageUnique;
	SI32				siVoteResult;

	sDBRequest_GeneralMeeting_CloseChief( SI32 villageunique, SI32 result, cltDate *pclDate )
	{
		packetHeader.usCmd = DBMSG_REQUEST_GENERALMEETING_CLOSE_CHIEF;
		packetHeader.usSize = sizeof(sDBRequest_GeneralMeeting_CloseChief);

		siVillageUnique = villageunique;
		siVoteResult = result;

		clDate.Set( pclDate );
	}

};

class sDBResponse_GeneralMeeting_CloseChief
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;

	cltDate				clDate;

	SI32				siVillageUnique;
	SI32				siVoteResult;

	SI32				siChiefPersonID;
	TCHAR				szChiefName[ MAX_PLAYER_NAME ];

	sDBResponse_GeneralMeeting_CloseChief()
	{
		ZeroMemory( this, sizeof( sDBResponse_GeneralMeeting_CloseChief ) );
	}

};

//  ��ǥ���� ������ȸ ���� ���θ� �����Ѵ�
class sDBRequest_GeneralMeeting_SetVoterState
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;
	SI32				siPersonID;
	SI32				siParticipate;

	sDBRequest_GeneralMeeting_SetVoterState( SI32 villageunique, SI32 personid, SI32 participate )
	{
		packetHeader.usCmd = DBMSG_REQUEST_GENERALMEETING_SETVOTERSTATE;
		packetHeader.usSize = sizeof(sDBRequest_GeneralMeeting_SetVoterState);

		siVillageUnique = villageunique;
		siPersonID = personid;
		siParticipate = participate;
	}
};


class sDBResponse_GeneralMeeting_SetVoterState
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;

	SI32				siVillageUnique;
	SI32				siPersonID;
	SI32				siParticipate;

	sDBResponse_GeneralMeeting_SetVoterState()
	{
		ZeroMemory( this, sizeof( sDBResponse_GeneralMeeting_SetVoterState ) );
	}

};

class sDBRequest_SetVillageWarResult
{
public:
	sPacketHeader		packetHeader;
		
	// ������ �������� �¸�����, �й� ������ ����ũ
	SI32				m_siwinVillageUnique;
	SI32				m_siloseVillageUnique;
	// �¸��� �������� + �ϰ� �й��� ������ - �ؾ��� ��������
	SI32				m_siwinnerGetVillageWarScore;
	// �¸��� �������� + �ϰ� �й��� ������ - �ؾ��� ��û �ں���
	GMONEY				m_siwinnerGetVillageMoney;

	// �й��� ������ ��û������ ��ϵ� ���� �й���
	NDate				m_clDateLoser;

	sDBRequest_SetVillageWarResult( SI32 winVillageUnique, SI32 loseVillageUnique, SI32 winnerGetVillageWarScore, GMONEY winnerGetVillageMoney, NDate* Dateloser )
	{
		packetHeader.usCmd = DBMSG_REQUEST_SETVILLAGEWAR_RESULT;
		packetHeader.usSize = sizeof(sDBRequest_SetVillageWarResult);
		m_siwinVillageUnique = winVillageUnique;
		m_siloseVillageUnique = loseVillageUnique;
		m_siwinnerGetVillageWarScore = winnerGetVillageWarScore;
		m_siwinnerGetVillageMoney	= winnerGetVillageMoney;		
		m_clDateLoser.Set(Dateloser);
	}
};


class sDBResponse_SetVillageWarResult
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;

	SI32				m_siwinVillageUnique;
	SI32				m_siloseVillageUnique;	
	GMONEY				m_siwinnerVillageMoney; // ����, ���� �� ������ ���� ��û �ڱ�
	GMONEY				m_siloserVillageMoney; // ����, ���� �� ������ ���� ��û �ڱ�
	// �¸��� �������� + �ϰ� �й��� ������ - �ؾ��� ��û �ں���
	GMONEY				m_siwinnerGetVillageMoney;
	NDate				m_clDateLoser;

	sDBResponse_SetVillageWarResult()
	{
		ZeroMemory( this, sizeof( sDBResponse_SetVillageWarResult ) );
	}
};



//#if defined(_CITYHALL_BANKRUPTCY)
//---------------------------------------
// [��û] ��� ����(�Ļ��, �ʱ�ȭ��, ������, �����)�� ����Ǿ���.
//---------------------------------------
class sDBRequest_CityHall_State_Changed
{
public:
	sPacketHeader		packetHeader;
	UI08				usPrevStatus;
	UI08				usCurStatus;

	SI32				siVillageUnique;


	sDBRequest_CityHall_State_Changed( SI32 villageunique, UI08 usprevstatus, UI08 uscurstatus )
	{
		packetHeader.usCmd = DBMSG_REQUEST_CITYHALL_STATE_CHANGED;
		packetHeader.usSize = sizeof(sDBRequest_CityHall_State_Changed);

		siVillageUnique = villageunique;
		usPrevStatus = usprevstatus;
		usCurStatus = uscurstatus;
	}

};

//---------------------------------------
// [����] ��� ����(�Ļ��, �ʱ�ȭ��, ������, �����)�� ����Ǿ���.
//---------------------------------------
class sDBReponse_CityHall_State_Changed
{
public:
	sPacketHeader		packetHeader;
	UI08				usPrevStatus;
	UI08				usCurStatus;

	SI32				siVillageUnique;

	SI32				siResult;

	sDBReponse_CityHall_State_Changed( )
	{
		ZeroMemory( this, sizeof( sDBReponse_CityHall_State_Changed ) );
	}

};




//---------------------------------------
// [��û] ��� ���°� �Ļ�Ǿ����� LETTER�� �˸���.
//---------------------------------------
class sDBRequest_Notify_Cityhall_Bankruptcy
{
public:
	enum {
		MAX_STOCKHOLDER_NUMBER = MAX_BANKRUPT_STOCKHOLDER_NUMBER_TO_BE_NOTIFIED, // �Ļ��� �˸� �ִ� ���ּ��� ���ڷ� �Է¹��� �ʰ� �����ȴ�.
		// �Ļ�� ������ ���� �� �ֽļ��� 1~500�������
	};

	sPacketHeader		packetHeader;

	SI32				siVillageUnique;		// �Ļ�� ���� ���� ��ȣ
	UI08				usType;					// �Ļ� ����, �Ļ� �������� ����

	sDBRequest_Notify_Cityhall_Bankruptcy( SI32 villageunique, UI08 ustype)
	{
		packetHeader.usCmd = DBMSG_REQUEST_NOTIFY_CITYHALL_BANKRUPTCY;
		packetHeader.usSize = sizeof(sDBRequest_Notify_Cityhall_Bankruptcy);

		siVillageUnique = villageunique;
		usType = ustype;
	}

};

//---------------------------------------
// [����] ��� ���°� �Ļ�Ǿ����� LETTER�� �˸���.
//---------------------------------------
class sDBReponse_Notify_Cityhall_Bankruptcy
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;
	SI32				siVillageUnique;
	SI32				siPersonID[MAX_BANKRUPT_STOCKHOLDER_NUMBER_TO_BE_NOTIFIED];	// ���� ��û�Ҷ� �ִ���� ������
	UI08				usType;					// �Ļ� ����, �Ļ� �������� ����
    
	sDBReponse_Notify_Cityhall_Bankruptcy( )
	{
		ZeroMemory( this, sizeof( sDBReponse_Notify_Cityhall_Bankruptcy ) );
	}

};

//***************************************************************************************************
//
// Class Name 		: sDBRequest_DonateVillageMoney
//
// Last Modified 	: 2007 / 08 / 10
// Created		 	: �豤��
//
// Function			: ������ �� ����ϱ�
//
//***************************************************************************************************
// ���� 10�������� ���� - by LEEKH 2007.12.06
const SI32 MIN_DONATE_MONEY = 100000;

class sDBRequest_DonateVillageMoney
{
public:
	sPacketHeader		packetHeader;

	SI32				siCharID;
	/// ����ϴ� ��� PersonID
	SI32				siPersonID;		
	/// ��ι޴� ����
	SI32				siVillageUnique;
	/// ��γ�¥
	SI32				siDonateDate;
	/// ��αݾ�
	SI64				siDonateMoney;


	sDBRequest_DonateVillageMoney( SI32 CharID, SI32 PersonID, SI32 VillageUnique, SI32 DonateDate, SI64 DonateMoney )
	{
		packetHeader.usSize = sizeof( sDBRequest_DonateVillageMoney );
		packetHeader.usCmd = DBMSG_REQUEST_DONATEVILLAGEMONEY;

		siCharID = CharID;
		siPersonID = PersonID;
		siVillageUnique = VillageUnique;
		siDonateDate = DonateDate;
		siDonateMoney = DonateMoney;
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBResponse_DonateVillageMoney
//
// Last Modified 	: 2007 / 08 / 10
// Created		 	: �豤��
//
// Function			: ������ �� ����ϱ�
//
//***************************************************************************************************
class sDBResponse_DonateVillageMoney
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;

	SI32				siCharID;
	/// ����ϴ� ��� PersonID
	SI32				siPersonID;		
	/// ��ι޴� ����
	SI32				siVillageUnique;
	/// ��γ�¥
	SI32				siDonateDate;
	/// ��αݾ�
	SI64				siDonateMoney;
	/// ����� ��� �̸�
	TCHAR				szDonateName[MAX_PLAYER_NAME];
	/// ����� ���� ���ͱ�
	SI64				siChangedVillageProfitMoney;
	/// ����Ŀ� ��ȭ�� ������
	SI64				siChangedMyMoney;

	sDBResponse_DonateVillageMoney()
	{
		ZeroMemory(this, sizeof(sDBResponse_DonateVillageMoney));
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBRequest_DonateMemberList
//
// Last Modified 	: 2007 / 08 / 10
// Created		 	: �豤��
//
// Function			: ����� ����Ʈ �ҷ�����
//
//***************************************************************************************************
struct DonateMemberList
{
	/// ����� ��� �̸�
	TCHAR				szDonateName[MAX_PLAYER_NAME];
	/// ����� �ð�
	SI32				siDonateDate;
	/// ����� �ݾ�
	SI64				siDonateMoney;
};

const SI32 MAX_DONATEMEMBERLIST_PER_PAGE = 10;

class sDBRequest_DonateMemberList
{
public:
	sPacketHeader		packetHeader;

	SI32				siCharID;
	SI32				siVillageUnique;
	SI32				siRequestPage;

	sDBRequest_DonateMemberList( SI32 CharID, SI32 VillageUnique, SI32 RequestPage )
	{
		packetHeader.usSize = sizeof( sDBRequest_DonateMemberList );
		packetHeader.usCmd = DBMSG_REQUEST_DONATEMEMBERLIST;

		siCharID = CharID;
		siVillageUnique = VillageUnique;
		siRequestPage = RequestPage;
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBResponse_DonateMemberList
//
// Last Modified 	: 2007 / 08 / 10
// Created		 	: �豤��
//
// Function			: ����� ����Ʈ �ҷ�����
//
//***************************************************************************************************
class sDBResponse_DonateMemberList
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;
	SI32				siCharID;
	SI32				siVillageUnique;
	// ��û�� ������
	SI32				siRequestPage;
	/// ��� �ҷ��� ��������ũ
	DonateMemberList    sDonateMemberList[MAX_DONATEMEMBERLIST_PER_PAGE];
	SI32				siMaxPage;

	sDBResponse_DonateMemberList()
	{
		ZeroMemory(this, sizeof(sDBResponse_DonateMemberList));
	}
};
// ��� �Ļ꿡 ���� ������ �ʱ�ȭ �Ѵ�.
// �Ļ� �� ���� ���� ���� �ʱ�ȭ�� ���� ���˽� ���۾����� �Ѵ�.
//class sDBRequest_Village_Initialization
//{
//public:
//	sPacketHeader		packetHeader;
//	UI08				usPrevStatus;
//	UI08				usCurStatus;
//
//	SI32				siVillageUnique;
//
//
//	sDBRequest_Village_Initialization( SI32 villageunique, UI08 usprevstatus, UI08 uscurstatus )
//	{
//		packetHeader.usCmd = DBMSG_REQUEST_VILLAGE_INITIALIZATION;
//		packetHeader.usSize = sizeof(sDBRequest_Village_Initialization);
//
//		siVillageUnique = villageunique;
//		usPrevStatus = usprevstatus;
//		usCurStatus = uscurstatus;
//	}
//
//};
//
//class sDBReponse_Village_Initialization
//{
//public:
//	sPacketHeader		packetHeader;
//	UI08				usPrevStatus;
//	UI08				usCurStatus;
//
//	SI32				siVillageUnique;
//
//	SI32				siResult;
//
//	sDBReponse_Village_Initialization( )
//	{
//		ZeroMemory( this, sizeof( sDBReponse_Village_Initialization ) );
//	}
//
//};
//#endif




#endif