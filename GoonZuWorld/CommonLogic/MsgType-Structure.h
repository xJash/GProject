#ifndef _MSGTYPESTRUCTURE_H
#define _MSGTYPESTRUCTURE_H

#include "Cityhall/Cityhall.h"
#include "HiredNPCMgr/HiredNPCMgr.h"
#include "NStructureDlg/Cityhall/NStructureMessageDlg.h"
#include "../../DBManager/GameDBManager_World/DBMsg-Cityhall.h"
#include "../server/Event/ContributionEvent_Common/ContributionEvent_Common.h"

//-------------------------------------------
//  �ǹ��� ��������� ��û�Ѵ�.
//-------------------------------------------
class cltGameMsgResponse_ChiefInfo{
public:
	cltRank	Rank;
	TCHAR	AccountID[MAX_PLAYER_NAME];

	cltGameMsgResponse_ChiefInfo( cltRank* pRank, TCHAR *pAccountID)
	{
		Rank.Set(pRank);
		MStrCpy( AccountID, pAccountID, MAX_PLAYER_NAME );
	}
};

//-------------------------------------------
// ���� �� �������� �ǹ� ������û  
//-------------------------------------------
class cltGameMsgRequest_VillageInfoStrInfo{
public:
	SI32 siVillageUnique;
	SI32 siStrType;

	cltGameMsgRequest_VillageInfoStrInfo(SI32 villageunique, SI32 strtype)
	{
		siVillageUnique		= villageunique;
		siStrType			= strtype;
	}
};

//-------------------------------------------
// [����] ���� �� �������� �ǹ� ���� ����
//-------------------------------------------
class cltGameMsgResponse_VillageInfoStrInfo{
public:
	SI32			siVillageUnique;
	SI32			siStrType;

	cltStrInfo		clTargetStr;

	SI32			siParam1;		// parameter1	//�������, cityhall���� ��������� ����
	SI32			siParam2;		// parameter2	//�������, cityhall���� ������ȸ ������ ����

	cltGameMsgResponse_VillageInfoStrInfo(SI32 villageunique, SI32 strtype, cltStrInfo* ptargetstr, SI32 param1=0, SI32 param2=0)
	{
		siVillageUnique		= villageunique;
		siStrType			= strtype;

		if( ptargetstr == NULL )
			memset( &clTargetStr, 0, sizeof( cltStrInfo ) );
		else
			memcpy( &clTargetStr, ptargetstr, sizeof( cltStrInfo ) );

        siParam1 = param1;
		siParam2 = param2;
	}
};


//-------------------------------------------
// �ǹ� ����. 
//-------------------------------------------
class cltGameMsgRequest_StrInfo{
public:
	SI32 siVillageUnique;
	SI32 siStrType;

	cltGameMsgRequest_StrInfo(SI32 villageunique, SI32 strtype)
	{
		siVillageUnique		= villageunique;
		siStrType			= strtype;
	}
};

//-------------------------------------------
// ���� ���� ���� ��û
//-------------------------------------------
class cltGameMsgRequest_GetTaxList{
public:
	SI32		siVillageUnique;					// ����  
	SI32		siStrType;							// �ü� 
	
	cltGameMsgRequest_GetTaxList( SI32 villageunique, SI32 strtype )
	{
		siVillageUnique		= villageunique;
		siStrType			= strtype;		
	}

};

//------------------------------------------
// ���� ���� ������ �����Ѵ� 
//------------------------------------------
class cltGameMsgResponse_GetTaxList
{
public:
	SI32				siResult;			// �����.
	SI32				siVillageUnique;	// �ǹ��� ��ġ�� ������ VillageUnique
	SI32				siStrType;			// �ü� 

	cltTaxInfo			clTaxInfo;

	cltGameMsgResponse_GetTaxList()
	{
		ZeroMemory(this, sizeof(cltGameMsgResponse_GetTaxList));
	}

	// �� �޽����� ��ȿ�� ����� ���Ѵ�. 
	SI32 GetTotalSize()
	{
		return sizeof(cltGameMsgResponse_GetTaxList); // - sizeof(cltTaxInfo) + clTaxInfo.GetTotalSize();
	}

};


//-------------------------------------------
// ������ ���� �Ѵ�
//-------------------------------------------
class cltGameMsgRequest_SetTax{
public:
	SI32		siVillageUnique;					// ����  
	SI32		siStrType;							// �ü� 

	UI16		usYear;								// ���� �⵵
	cltMoney	clDueTax;							// �ΰ� ���� 

	cltGameMsgRequest_SetTax(SI32 villageunique, SI32 strtype, UI16 year, cltMoney *pclMoney )
	{
		siVillageUnique		= villageunique;
		siStrType			= strtype;
		usYear				= year;
		clDueTax.Set( pclMoney );
	}
	

};

//-------------------------------------------
// ������ ���� �Ѵ�
//-------------------------------------------
class cltGameMsgRequest_PayTax{
public:
	SI32		siVillageUnique;					// ���� 
	SI32		siStrType;							// �ü� 

	UI16		usYear;								// ���� �⵵ 
	cltMoney	clPayTax;							// ���� ���� 

	cltGameMsgRequest_PayTax(SI32 villageunique, SI32 strtype, UI16 year, cltMoney *pclMoney )
	{
		siVillageUnique		= villageunique;
		siStrType			= strtype;
		usYear				= year;
		clPayTax.Set( pclMoney );
	}
	

};

//-------------------------------------------
// ������ ���� �Ѵ�
//-------------------------------------------
class cltGameMsgResponse_PayTax {
public:	
	SI32		siVillageUnique;					// ���� 
	SI32		siStrType;							// �ü� 

	cltMoney	clStructureMoney;	
	cltMoney	clCityhallMoney;					// ���ͱ����� ��

	cltGameMsgResponse_PayTax( SI32 villageunique, SI32 strtype, cltMoney *structureMoney, cltMoney *cityhallMoney )
	{
		siVillageUnique		= villageunique;
		siStrType			= strtype;

		clStructureMoney.Set( structureMoney );
		clCityhallMoney.Set( cityhallMoney );
	}
};


//-------------------------------------------
// ��� ������ ��û�Ѵ�
//-------------------------------------------
class cltGameMsgRequest_GetDividendList {
public:
	SI32		siVillageUnique;

	cltGameMsgRequest_GetDividendList( SI32 villageunique )
	{
		siVillageUnique	= villageunique;
	}

};

//-------------------------------------------
// ��� ������ �����Ѵ�
//-------------------------------------------
class cltGameMsgResponse_GetDividendList {
public:
	SI32				siResult;			// �����.
	SI32				siVillageUnique;	// �ǹ��� ��ġ�� ������ VillageUnique

	cltDividendInfo		clDividendInfo;

	cltGameMsgResponse_GetDividendList()
	{
		ZeroMemory( this, sizeof( cltGameMsgResponse_GetDividendList ) );
	}

	// �� �޽����� ��ȿ�� ����� ���Ѵ�. 
	SI32 GetTotalSize()
	{
		return sizeof(cltGameMsgResponse_GetDividendList); // - sizeof(cltTaxInfo) + clTaxInfo.GetTotalSize();
	}
	
};

//-------------------------------------------
// ���ֵ鿡�� ������ ����Ѵ�
//-------------------------------------------
class cltGameMsgRequest_PayDividend {
public:
	SI32			siVillageUnique;
	cltMoney		clTotalDividend;

	cltGameMsgRequest_PayDividend( SI32 villageUnique, cltMoney *pclMoney )
	{
		siVillageUnique = villageUnique;
		clTotalDividend.Set( pclMoney );
	}

};

//-------------------------------------------
// ���� NPC����� ��û�Ѵ� 
//-------------------------------------------
class cltGameMsgRequest_HireNPC {
public:
	SI32			siVillageUnique;
	UI16			usSlot;
	SI32			siNPCKind;
	
	cltGameMsgRequest_HireNPC( SI32 villageUnique, UI16 slot, SI32 npckind )
	{
		siVillageUnique		= villageUnique;
		usSlot				= slot;
		siNPCKind			= npckind;
	}
};


//-------------------------------------------
// ���� NPC��� ��û�� ���� ���� 
//-------------------------------------------
class cltGameMsgResponse_HireNPC {
public:
	SI32			siResult;
	SI32			siVillageUnique;
	
	cltGameMsgResponse_HireNPC()
	{
		ZeroMemory( this, sizeof( cltGameMsgResponse_HireNPC ) );
	}

};


//-------------------------------------------
// ������ ���� NPC������ ��û�Ѵ� 
//-------------------------------------------
class cltGameMsgRequest_GetNPCList
{
public:
	SI32			siVillageUnique;

	cltGameMsgRequest_GetNPCList( SI32 villageUnique )
	{
		siVillageUnique = villageUnique;
	}
};


//-------------------------------------------
// ������ ���� NPC������ ���´�
//-------------------------------------------
class cltGameMsgResponse_GetNPCList
{
public:
	SI32			siVillageUnique;
#ifdef _SAFE_MEMORY
	NSafeTArray<cltHiredNPC, MAX_HIRED_NPC_NUM>		clHiredNPC;
#else
	cltHiredNPC		clHiredNPC[ MAX_HIRED_NPC_NUM ];
#endif

	cltGameMsgResponse_GetNPCList()
	{
		ZeroMemory( this, sizeof( cltGameMsgResponse_GetNPCList ) );
	}
};

//-------------------------------------------
//  NPC�޿� ������ ���´�
//-------------------------------------------
class cltGameMsgResponse_NPCPayment
{
public:
	SI32				siCount;
#ifdef _SAFE_MEMORY
	NSafeTArray<cltHiredNPCPayInfo, MAX_HIREDNPC_KIND_NUM>		clHiredNPCPayInfo;
#else
	cltHiredNPCPayInfo	clHiredNPCPayInfo[ MAX_HIREDNPC_KIND_NUM ];
#endif

	cltGameMsgResponse_NPCPayment()
	{
		ZeroMemory( this, sizeof( cltGameMsgResponse_NPCPayment ) );
	}
};

//-------------------------------------------
// �ֹε�� ��û�� ��û 
//-------------------------------------------
class cltGameMsgRequest_ApplyResident
{
public:
	SI32			siVillageUnique;

	cltGameMsgRequest_ApplyResident( SI32 villageUnique )
	{
		siVillageUnique = villageUnique;
	}
};

//-------------------------------------------
// �ֹε�� ��Ҹ� ��û 
//-------------------------------------------
class cltGameMsgRequest_CancelResident
{
public:
	SI32			siVillageUnique;
	SI32			siPersonID;

	cltGameMsgRequest_CancelResident( SI32 villageUnique, SI32 personid )
	{
		siVillageUnique = villageUnique;
		siPersonID = personid;
	}
};



//-------------------------------------------
// �ֹε�� ��û �㰡�� ��û 
//-------------------------------------------
class cltGameMsgRequest_BeResident
{
public:
	SI32			siVillageUnique;
	SI32			siPersonID;

	cltGameMsgRequest_BeResident( SI32 villageUnique, SI32 personid )
	{
		siVillageUnique = villageUnique;
		siPersonID = personid;
	}
};


//-------------------------------------------
// �ֹ� ��� ��û�� ����Ʈ�� ��û
//-------------------------------------------
class cltGameMsgRequest_GetResidentApplyerList
{
public:
	SI32				siVillageUnique;

	cltGameMsgRequest_GetResidentApplyerList( SI32 villageUnique )
	{
		siVillageUnique = villageUnique;
	}
};

//-------------------------------------------
// �ֹ� ��� ��û�� ����Ʈ ����
//-------------------------------------------
class cltGameMsgResponse_GetResidentApplyerList
{
public:
	SI32				siVillageUnique;
	SI32				count;

#ifdef _SAFE_MEMORY
	NSafeTArray<cltResidentApplyer, MAX_RESIDENT_APPLYER>		clResidentApplyer;
#else
	cltResidentApplyer	clResidentApplyer[ MAX_RESIDENT_APPLYER ];
#endif

	cltGameMsgResponse_GetResidentApplyerList()
	{
		ZeroMemory( this, sizeof( cltGameMsgResponse_GetResidentApplyerList ) );
	}

	SI32				GetTotalSize() { return 8 + sizeof( cltResidentApplyer ) * count; }
};

class cltGameMsgRequest_GetResidentInfo
{
public:
	SI32			siVillageUnique;
	TCHAR			szPersonName[ 20 ];

	cltGameMsgRequest_GetResidentInfo( SI32 villageUnique, TCHAR *personName )
	{
		siVillageUnique = villageUnique;
		
		memcpy( szPersonName, personName, 20 );
		szPersonName[ 19 ] = NULL;
	}
};

class cltGameMsgResponse_GetResidentInfo
{
public:
	SI32				siResult;

	cltResident			clResident;	

	cltGameMsgResponse_GetResidentInfo()
	{
		ZeroMemory( this, sizeof( cltGameMsgResponse_GetResidentInfo ) );
	}
	
};


//-------------------------------------------
// �ֹ� ����Ʈ�� ��û
//-------------------------------------------
class cltGameMsgRequest_GetResidentList
{
public:
	SI32				siVillageUnique;
	SI32				siSort;						// ���� ���

	cltGameMsgRequest_GetResidentList( SI32 villageUnique, SI32 sort )
	{
		siVillageUnique = villageUnique;
		siSort = sort;
	}

};

//-------------------------------------------
// �ֹ� ����Ʈ�� ��û
//-------------------------------------------

class cltGameMsgResponse_GetResidentList
{
public:
	SI32				siVillageUnique;
	SI32				count;

#ifdef _SAFE_MEMORY
	NSafeTArray<cltResident, MAX_RESIDENT_NUMBER>		clResident;
#else
	cltResident	clResident[ MAX_RESIDENT_NUMBER ];
#endif

	cltGameMsgResponse_GetResidentList()
	{
		ZeroMemory( this, sizeof( cltGameMsgResponse_GetResidentList ) );
	}

	SI32				GetTotalSize() { return 8 + sizeof( cltResident ) * count; }

};

//-------------------------------------------
// �ֹ� ���� ����
//-------------------------------------------
class cltGameMsgRequest_SetResidentScore
{
public:
	SI32				siVillageUnique;
	SI32				siPersonId;
	SI32				siScore;

	cltGameMsgRequest_SetResidentScore( SI32 villageUnique, SI32 personid, SI32 score )
	{
		siVillageUnique = villageUnique;
		siPersonId = personid;
		siScore = score;
	}
};


class cltGameMsgRequest_SetStructureMessage
{
public:
	SI32				siVillageUnique;
	SI32				siStrType;

	TCHAR				szMessage[ MAX_STR_NOTICE_SIZE ];

	cltGameMsgRequest_SetStructureMessage( SI32 villageUnique, SI32 strType, TCHAR *msg )
	{
		siVillageUnique = villageUnique;
		siStrType = strType;

		memcpy( szMessage, msg, MAX_STR_NOTICE_SIZE );
		szMessage[ MAX_STR_NOTICE_SIZE - 1 ] = NULL;
	}

};

//-------------------------------------------
// �ǹ�(����) �˸��� ��û 
// ������ ��� STRTYPE�� RANK_CITYHALL�̴� 
//-------------------------------------------
class cltGameMsgRequest_GetStrNotice
{
public:
	SI32				siVillageUnique;
	SI32				siStrType;

	cltGameMsgRequest_GetStrNotice( SI32 villageUnique, SI32 strType )
	{
		siVillageUnique = villageUnique;
		siStrType = strType;
	}

};

//-------------------------------------------
// �ǹ�(����) �˸��� ���� 
// ������ ��� STRTYPE�� RANK_CITYHALL�̴� 
//-------------------------------------------
class cltGameMsgResponse_GetStrNotice
{
public:
	SI32				siVillageUnique;
	SI32				siStrType;

	TCHAR				szStrNotice[ MAX_STR_NOTICE_SIZE ];

	cltGameMsgResponse_GetStrNotice()
	{
		ZeroMemory( this, sizeof( cltGameMsgResponse_GetStrNotice ) );
	}
};


class cltGameMsgRequest_ResidentShare
{
public:
	cltMoney			clTotalShareMoney;
	SI32				siShareType;

	cltGameMsgRequest_ResidentShare( cltMoney *pclMoney, SI32 shareType )
	{
		clTotalShareMoney.Set( pclMoney );
		siShareType = shareType;
	}
};

/*
class cltGameMsgResponse_ResidentShare
{
public:
	

	cltGameMsgResponse_ResidentShare()
	{
		ZeroMemory( this, sizeof( cltGameMsgResponse_ResidentShare ) );
	}

};
*/

class cltGameMsgRequest_BuildStructure
{
public:
	SI32				siSlot;
	SI32				siStructureUnique;
	
	cltGameMsgRequest_BuildStructure( SI32 slot, SI32 structureUnique )
	{
		siSlot = slot;
		siStructureUnique = structureUnique;
	}

};

class cltGameMsgResponse_BuildStructure
{
public:
	SI32				siVillageUnique;
	SI32				siSlot;
	SI32				siStructureUnique;

	cltGameMsgResponse_BuildStructure( SI32 villageUnique, SI32 slot, SI32 structureUnique )
	{
		siVillageUnique = villageUnique;
		siSlot = slot;
		siStructureUnique = structureUnique;
	}

};

class cltGameMsgRequest_DestroyStructure
{
public:
	SI32				siSlot;

	cltGameMsgRequest_DestroyStructure( SI32 slot )
	{
		siSlot = slot;
	}
	
};

class cltGameMsgResponse_DestroyStructure
{
public:
	SI32				siVillageUnique;
	SI32				siSlot;
	SI32				siStructureUnique;

	cltGameMsgResponse_DestroyStructure( SI32 villageUnique, SI32 slot, SI32 structureUnique )
	{
		siVillageUnique = villageUnique;
		siSlot = slot;
		siStructureUnique = structureUnique;
	}
};

class cltGameMsgRequest_VillageNotice
{
public:
	SI32				siVillageUnique;
	cltGameMsgRequest_VillageNotice( SI32 VillageUnique )
	{
		siVillageUnique = VillageUnique;
	}
};

class cltGameMsgResponse_VillageNotice
{
public:
	SI32				siVillageUnique;
	TCHAR				strVillageNotice[ MAX_VILLAGENOTICE_LENGTH ];
	cltGameMsgResponse_VillageNotice( SI32 VillageUnique, TCHAR *VillageNotice )
	{
		siVillageUnique = VillageUnique;
		memcpy( strVillageNotice, VillageNotice, MAX_VILLAGENOTICE_LENGTH );
		strVillageNotice[ MAX_VILLAGENOTICE_LENGTH - 1 ] = NULL;
	}
};

class cltGameMsgResponse_AllStrChiefInfo
{
public:
	TCHAR				siRankType[ MAX_RANKTYPE_NUMBER ];
	TCHAR				szChiefPersonName[ MAX_RANKTYPE_NUMBER ][ MAX_PLAYER_NAME ];

	cltGameMsgResponse_AllStrChiefInfo()
	{
		ZeroMemory( this, sizeof( cltGameMsgResponse_AllStrChiefInfo ) );
	}
};

/*
class cltGameMsgRequest_RepairStructure
{
public:
	SI32				siRankType;

	SI16				siItemInventoryIndex;
	SI32				siItemUnique;
	SI16				siItemNum;

	cltGameMsgRequest_RepairStructure( SI32 ranktype, SI16 itemInventoryIndex, SI32 itemUnique, SI16 itemNum )
	{
		siRankType = ranktype;
		siItemInventoryIndex = itemInventoryIndex;
		siItemUnique = itemUnique;
		siItemNum = itemNum;
	}
};

class cltGameMsgResponse_RepairStructure
{
public:
	SI32				siRankType;
	SI16				siUseItemNum;

	cltGameMsgResponse_RepairStructure( SI32 ranktype, SI16 useitemnum )
	{
		siRankType = ranktype;
		siUseItemNum = useitemnum;
	}
};
*/

#define REPAIR_YEAR	8
#define NEW_REPAIR_YEAR	20

class cltGameMsgRequest_RepairStructure
{
public:
	SI32				siRankType;

	SI32				siStrRepairAmount;

	bool				bItemUse;				// [�߰� : Ȳ���� 2007. 12. 26 ������ ���.]

	cltGameMsgRequest_RepairStructure( SI32 RankType, SI32 StrRepairAmount, bool Item = false)
	{
		siRankType = RankType;
		siStrRepairAmount = StrRepairAmount;
		bItemUse		  = Item;
	}
};

class cltGameMsgResponse_RepairStructure
{
public:
	SI32				siRankType;
	SI32				siStrRepairAmount;
	GMONEY				siLeftBaseMoney;

	cltGameMsgResponse_RepairStructure( SI32 RankType, SI32 StrRepairAmount, GMONEY LeftBaseMoney )
	{
		siRankType = RankType;
		siStrRepairAmount = StrRepairAmount;
		siLeftBaseMoney = LeftBaseMoney;
	}
};

class cltGameMsgRequest_ProfitToCapitalFund
{
public:
	GMONEY				siMoney;

	cltGameMsgRequest_ProfitToCapitalFund( GMONEY money )
	{
		siMoney = money;
	}
};

class cltGameMsgRequest_StartEvent
{
public:
	SI32				siEventID;

	cltGameMsgRequest_StartEvent( SI32 eventid )
	{
		siEventID = eventid;
	}
};

class cltGameMsgResponse_VillageBoard
{
public:
	SI32				siVillageUnique;

	cltGameMsgResponse_VillageBoard(SI32 village)
	{
		siVillageUnique = village;
	}
};

class cltGameMsgResponse_VillageLevelDetailInfo
{
public:
	cltVillageLevelDetailInfo	clLevelInfo;
};

// ������ȸ ������ ���´� 
class cltGameMsgRequest_GeneralMeetingInfo
{
public:

};

class cltGameMsgResponse_GeneralMeetingInfo
{
public:
	cltGeneralMeetingInfo	clGeneralMeetingInfo;
};

// ������ȸ�� �����Ѵ� 
class cltGameMsgRequest_GeneralMeetingSuggest
{
public:
	TCHAR			szCandidateName[ MAX_PLAYER_NAME ];

	cltGameMsgRequest_GeneralMeetingSuggest( TCHAR *name )
	{
		memcpy( szCandidateName, name, MAX_PLAYER_NAME );
		szCandidateName[ MAX_PLAYER_NAME - 1 ] = NULL;
	}

};

class cltGameMsgResponse_GeneralMeetingSuggest
{
public:
};

// ��ǥ�Ѵ� 
class cltGameMsgRequest_GeneralMeetingVote
{
public:
	SI32			siVoteType;

	cltGameMsgRequest_GeneralMeetingVote( SI32 vote )
	{
		siVoteType = vote;
	}
};

class cltGameMsgResponse_GeneralMeetingVote
{
public:
	SI32			siPersonID;			
	SI32			siVoteType;

	cltGameMsgResponse_GeneralMeetingVote( SI32 personid, SI32 votetype )
	{
		siPersonID = personid;
		siVoteType = votetype;
	}
};

// ��ǥ��Ȳ ���� ��û
class cltGameMsgRequest_GeneralMeetingVoteRefresh
{
public:
	cltGameMsgRequest_GeneralMeetingVoteRefresh()
	{
	}
};


// ����� �ĺ��ڰ� ���ε��Ǹ� �Ѵ�
class cltGameMsgRequest_GeneralMeetingAcceptCandidate
{
public:

};

class cltGameMsgResponse_GeneralMeetingAcceptCandidate
{
public:

};


// ������ȸ ���� ���θ� ���´�
class cltGameMsgResponse_GeneralMeetingLetter
{
public:
	SI32		siVillageUnique[ MAX_STOCK_KIND_IN_ACOUNT ];

	cltGameMsgResponse_GeneralMeetingLetter()
	{
		ZeroMemory( this, sizeof(cltGameMsgResponse_GeneralMeetingLetter));
	}
};

// ������ȸ ���� ���θ� �����Ѵ�
class cltGameMsgRequest_GeneralMeetingParticipate
{
public:
	SI32		siVillageUnique;
	SI32		siParticipate;

	cltGameMsgRequest_GeneralMeetingParticipate( SI32 villageunique, SI32 participate )
	{
		siVillageUnique = villageunique;
		siParticipate = participate;
	}
};

// ������ȸ ���� ���θ� �����Ѵ�
class cltGameMsgResponse_GeneralMeetingParticipate
{
public:
	SI32		siVillageUnique;
	SI32		siParticipate;

	cltGameMsgResponse_GeneralMeetingParticipate( SI32 villageunique, SI32 participate )
	{
		siVillageUnique = villageunique;
		siParticipate = participate;
	}
};

class cltGameMsgRequest_GeneralMeetingChat
{
public:
	int			textlen;
	char		szText[ 128 ];
};

class cltGameMsgResponse_GeneralMeetingChat
{
public:
	char		szName[ MAX_PLAYER_NAME ];
	
	int			textlen;
	char		szText[ 128 ];
};


//#if defined(_CITYHALL_BANKRUPTCY)
//------------------------------------------0-
// ���� ���¿� ���� Ŭ���̾�Ʈ �˸� �޼��� 
// ANNOUNCEMENT_TYPE_FAIL_DECLARE_WAR : ��� ������ ������� �������� ���� �˸�
// ANNOUNCEMENT_TYPE_FAIL_STOCK_TRADE : ��� ������ �Ļ� ���¶� �ֽ� �ʱ�ȭ ������ ��� �ֽİŷ� ����
// ANNOUNCEMENT_TYPE_FAIL_GENERALMEETING_SUGGEST : ��� ������ �Ļ� ���¶� ���� ���� ���� �˸�
//-------------------------------------------
class cltGameMsgResponse_NotifyClientAboutCityHallState {
public:
	enum 
	{
		ANNOUNCEMENT_TYPE_DEFAULT						= 0,	// �ƹ��͵� ����
		ANNOUNCEMENT_TYPE_FAIL_DECLARE_WAR				= 1,	// �������� ������
		ANNOUNCEMENT_TYPE_FAIL_STOCK_TRADE				= 2,	// �ֽ� �ŷ� ����
		ANNOUNCEMENT_TYPE_FAIL_GENERALMEETING_SUGGEST	= 3,	// �Ļ� ���½� ���ѹ��� ����
		ANNOUNCEMENT_TYPE_FAIL_CITYHALLCHIEF_RESIGN		= 4,	// ������ �� ����� ���� ����
		ANNOUNCEMENT_TYPE_FAIL_BIDSTOCK					= 5,	// �Ļ� ���½� ���� ����
	};

	SI32			siVillageUnique;
	UI08			uiCityHallState;	// ���� ����
	UI08			uiAnnouncementType;	// Client�� �ѷ��� ��Ʈ Ÿ��
	
	cltGameMsgResponse_NotifyClientAboutCityHallState(SI32 villageunique, UI08 cityhallstate, UI08 announcementtype)
	{
		siVillageUnique = villageunique;
		uiCityHallState = cityhallstate;
		uiAnnouncementType = announcementtype;
	}
};
//#endif

class cltGameMsgRequest_ChangeStrBaseMoney
{
public:
	SI32			siType;		// �ǹ� ����
	GMONEY			siMoney;	// ������ ��

	cltGameMsgRequest_ChangeStrBaseMoney( SI32 Type, GMONEY Money ) : siType(Type), siMoney(Money)
	{
	}
};

//-------------------------------------------
// ������ �̺�ƮNPC ����� ��û�Ѵ�.
//-------------------------------------------

class cltGameMsgRequest_HireEventNPC 
{
public:
	SI32			siVillageUnique;

	SI32			siEventNpcKind;


	cltGameMsgRequest_HireEventNPC( SI32 villageUnique , SI32 eventNpcKind )
	{
		siVillageUnique		= villageUnique;
		siEventNpcKind		= eventNpcKind;
	}
};
//***************************************************************************************************
//
// Class Name 		: cltGameMsgRequest_DonateVillageMoney
//
// Last Modified 	: 2007 / 08 / 10
// Created		 	: �豤��
//
// Function			: [Ŭ�� -> ����] ��α� ���� 
//
//***************************************************************************************************
class cltGameMsgRequest_DonateVillageMoney
{
public:
	SI32	siVillageUnique;
	SI64	siDonateMoney;

	cltGameMsgRequest_DonateVillageMoney( SI32 VillageUnique, SI64 DonateMoney )
	{
		siVillageUnique = VillageUnique;
		siDonateMoney = DonateMoney;
	}
};

//***************************************************************************************************
//
// Class Name 		: cltGameMsgResponse_DonateVillageMoney
//
// Last Modified 	: 2007 / 08 / 10
// Created		 	: �豤��
//
// Function			: [Ŭ�� -> ����] ��α� ���� 
//
//***************************************************************************************************
class cltGameMsgResponse_DonateVillageMoney
{
public:
	SI32	siVillageUnique;
	SI64	siDonateMoney;

	cltGameMsgResponse_DonateVillageMoney( SI32 VillageUnique, SI64 DonateMoney )
	{
		siVillageUnique = VillageUnique;
		siDonateMoney = DonateMoney;
	}
};

//***************************************************************************************************
//
// Class Name 		: cltGameMsgRequest_DonateMemberList
//
// Last Modified 	: 2007 / 08 / 10
// Created		 	: �豤��
//
// Function			: [Ŭ�� -> ����] ����� ��� ��Ϻ���
//
//***************************************************************************************************
class cltGameMsgRequest_DonateMemberList
{
public:
	SI32	siVillageUnique;
	SI32	siRequestPage;

	cltGameMsgRequest_DonateMemberList( SI32 VillageUnique, SI32 RequestPage )
	{
		siVillageUnique = VillageUnique;
		siRequestPage = RequestPage;
	}
};

//***************************************************************************************************
//
// Class Name 		: cltGameMsgResponse_DonateMemberList
//
// Last Modified 	: 2007 / 08 / 10
// Created		 	: �豤��
//
// Function			: [Ŭ�� -> ����] ����� ��� ��Ϻ���
//
//***************************************************************************************************
class cltGameMsgResponse_DonateMemberList
{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<DonateMemberList, MAX_DONATEMEMBERLIST_PER_PAGE>		sDonateMemberList;
#else
	DonateMemberList    sDonateMemberList[MAX_DONATEMEMBERLIST_PER_PAGE];
#endif
	SI32				siMaxPage;

	cltGameMsgResponse_DonateMemberList( DonateMemberList* pDonateMemberList, SI32 MaxPage )
	{
		for( SI32 i = 0; i < MAX_DONATEMEMBERLIST_PER_PAGE; ++i )
		{
			sDonateMemberList[i].siDonateDate = pDonateMemberList[i].siDonateDate;
			sDonateMemberList[i].siDonateMoney = pDonateMemberList[i].siDonateMoney;
			MStrCpy( sDonateMemberList[i].szDonateName, pDonateMemberList[i].szDonateName, MAX_PLAYER_NAME );
		}

		siMaxPage = MaxPage;
	}
};

//***************************************************************************************************
//
// Class Name 		: cltGameMsgRequest_Event_InsertMaterial
//
// Last Modified 	: 2007 / 11 / 21
// Created		 	: �̰���
//
// Function			: [Ŭ�� -> ����] ����� �̺�Ʈ ��� �ֱ�
//
//***************************************************************************************************
class cltGameMsgRequest_Event_InsertMaterial
{
public:	
	SI32		m_siVillageUnique;		// ���� ����ũ
	SI16		m_siConstructType;		// ����� �� �ĺ���

#ifdef _SAFE_MEMORY
	NSafeTArray<SI16, MAX_MATERIAL_NUMBER>		m_siItemUnique;		// ��� ������
	NSafeTArray<SI16, MAX_MATERIAL_NUMBER>		m_siItemNum;		// ��� ������ ����

	NSafeTArray<SI16, MAX_MATERIAL_NUMBER>		m_siNeedNum;		// ��� ������ ����
#else
	SI16		m_siItemUnique[MAX_MATERIAL_NUMBER];	// ��� ������
	SI16		m_siItemNum[MAX_MATERIAL_NUMBER];		// ��� ������ ����

	SI16		m_siNeedNum[MAX_MATERIAL_NUMBER];		// ��� ������ ����
#endif

	cltGameMsgRequest_Event_InsertMaterial(SI32 siVillageUnique, SI16 siConstructType, SI16* psiItemUnique, SI16* psiItemNum, SI16* psiNeedNum)
	{
		m_siVillageUnique	= siVillageUnique;
		m_siConstructType	= siConstructType;

#ifdef _SAFE_MEMORY
		m_siItemUnique.ZeroMem();
		m_siItemNum.ZeroMem();
		m_siNeedNum.ZeroMem();

		if(psiItemUnique != NULL)		m_siItemUnique.MemCpy(psiItemUnique);
		if(psiItemNum != NULL)			m_siItemNum.MemCpy(psiItemNum);
		if(psiNeedNum != NULL)			m_siNeedNum.MemCpy(psiNeedNum);
#else
		ZeroMemory(m_siItemUnique, sizeof(m_siItemUnique));
		if(psiItemUnique != NULL)
		{
			memcpy(m_siItemUnique, psiItemUnique, sizeof(m_siItemUnique));
		}

		ZeroMemory(m_siItemNum, sizeof(m_siItemNum));
		if(psiItemNum != NULL)
		{
			memcpy(m_siItemNum, psiItemNum, sizeof(m_siItemNum));
		}

		ZeroMemory(m_siNeedNum, sizeof(m_siNeedNum));
		if(psiNeedNum != NULL)
		{
			memcpy(m_siNeedNum, psiNeedNum, sizeof(m_siNeedNum));
		}
#endif
	}
};

class cltGameMsgResponse_Event_InsertMaterial
{
public:	
	SI32		m_siResult;		// ���� ����ũ

	cltGameMsgResponse_Event_InsertMaterial(SI32 siResult)
	{
		m_siResult = siResult;
	}
};

//***************************************************************************************************
//
// Class Name 		: cltGameMsgRequest_Event_MaterialList
//
// Last Modified 	: 2007 / 11 / 21
// Created		 	: �̰���
//
// Function			: [Ŭ�� -> ����] ����� �̺�Ʈ ��� ���� ����
//
//***************************************************************************************************
class cltGameMsgRequest_Event_MaterialList
{
public:	
	SI32		m_siVillageUnique;		// ���� ����ũ
	SI16		m_siConstructType;		// ����� �� �ĺ���

	cltGameMsgRequest_Event_MaterialList(SI32 siVillageUnique, SI16 siConstructType)
	{
		m_siVillageUnique	= siVillageUnique;
		m_siConstructType	= siConstructType;
	}
};

class cltGameMsgResponse_Event_MaterialList
{
public:	
	SI32		m_siVillageUnique;		// ���� ����ũ
	SI16		m_siConstructType;		// ����� �� �ĺ���

#ifdef _SAFE_MEMORY
	NSafeTArray<SI16, MAX_MATERIAL_NUMBER>				m_siItemUnique;
	NSafeTArray<SI16, MAX_MATERIAL_NUMBER>				m_siItemNum;
#else
	SI16		m_siItemUnique[MAX_MATERIAL_NUMBER];	// ��� ������
	SI16		m_siItemNum[MAX_MATERIAL_NUMBER];		// ��� ������ ����
#endif

	cltGameMsgResponse_Event_MaterialList(SI32 siVillageUnique, SI16 siConstructType, SI16* psiItemUnique, SI16* psiItemNum)
	{
		m_siVillageUnique	= siVillageUnique;
		m_siConstructType	= siConstructType;

#ifdef _SAFE_MEMORY
		m_siItemUnique.ZeroMem();
		m_siItemNum.ZeroMem();

		if(psiItemUnique != NULL)		m_siItemUnique.MemCpy(psiItemUnique);
		if(psiItemNum != NULL)			m_siItemNum.MemCpy(psiItemNum);
#else
		ZeroMemory(m_siItemUnique, sizeof(m_siItemUnique));
		if(psiItemUnique != NULL)
		{
			memcpy(m_siItemUnique, psiItemUnique, sizeof(m_siItemUnique));
		}

		ZeroMemory(m_siItemNum, sizeof(m_siItemNum));
		if(psiItemNum != NULL)
		{
			memcpy(m_siItemNum, psiItemNum, sizeof(m_siItemNum));
		}
#endif
	}
};

//***************************************************************************************************
//
// Class Name 		: cltGameMsgRequest_Event_MaterialComplete
//
// Last Modified 	: 2007 / 11 / 21
// Created		 	: �̰���
//
// Function			: [Ŭ�� -> ����] ����� �̺�Ʈ ��� �ϼ�
//
//***************************************************************************************************
class cltGameMsgRequest_Event_MaterialComplete
{
public:	
	SI32		m_siVillageUnique;		// ���� ����ũ
	SI16		m_siConstructType;		// ����� �� �ĺ���

	cltGameMsgRequest_Event_MaterialComplete(SI32 siVillageUnique, SI16 siConstructType)
	{
		m_siVillageUnique	= siVillageUnique;
		m_siConstructType	= siConstructType;
	}
};


class cltGameMsgResponse_Event_MaterialComplete
{
public:	
	SI32		m_siResult;				// ���� ����

	SI32		m_siVillageUnique;		// ���� ����ũ
	SI16		m_siConstructType;		// ����� �� �ĺ���

	cltGameMsgResponse_Event_MaterialComplete(SI32 siResult, SI32 siVillageUnique, SI16 siConstructType)
	{
		m_siResult			= siResult;
		m_siVillageUnique	= siVillageUnique;
		m_siConstructType	= siConstructType;
	}
};

class cltGameMsgResponse_Event_CompleteBuild
{
public:	
	SI32		m_siVillageUnique;		// ���� ����ũ
	SI16		m_siConstructType;		// ����� �� �ĺ���
	SI32		m_siNPCKind;

	cltGameMsgResponse_Event_CompleteBuild(SI32 siVillageUnique, SI16 siConstructType, SI32	_siNPCKind)
	{
		m_siVillageUnique	= siVillageUnique;
		m_siConstructType	= siConstructType;
		m_siNPCKind			= _siNPCKind;
	}
};

class cltGameMsgRequest_ApplyResident2
{
public:
	SI32				siVillageUnique;
	TCHAR				szMentorName[MAX_PLAYER_NAME];

	cltGameMsgRequest_ApplyResident2( SI32 VillageUnique, TCHAR* pMentorName)
	{
		siVillageUnique = VillageUnique;
		memcpy( szMentorName, pMentorName, sizeof(szMentorName) );
	}
};

class cltGameMsgRequest_Contribution_Item_List
{
public:
	cltGameMsgRequest_Contribution_Item_List( SI32 _siNPCKind )
	{
		ZeroMemory( this, sizeof(*this) );

		m_siNPCKind = _siNPCKind;
	}

	SI32 m_siNPCKind;
};

class cltGameMsgResponse_Contribution_Item_List
{
public:
	cltGameMsgResponse_Contribution_Item_List( SI32* _psiItemUnique,  SI16* _psiItemNum )
	{
		ZeroMemory( this, sizeof(*this) );

		memcpy( m_siItemUnique, _psiItemUnique, sizeof(m_siItemUnique) );
		memcpy( m_siItemNum,	_psiItemNum,	sizeof(m_siItemNum) );
	}

	SI32 m_siItemUnique[CONTRIBUTION_ITEM_NUM];
	SI16 m_siItemNum[CONTRIBUTION_ITEM_NUM];
};

class cltGameMsgRequest_Contribution_Item_List_Input
{
public:
	cltGameMsgRequest_Contribution_Item_List_Input( SI32 _siNPCKind )
	{
		ZeroMemory( this, sizeof(*this) );

		m_siNPCKind = _siNPCKind;
	}

	SI32 m_siNPCKind;
};

class cltGameMsgResponse_Contribution_Item_List_Input
{
public:
	cltGameMsgResponse_Contribution_Item_List_Input( SI32* _psiInputItemUnique,  SI16* _psiInputItemNum )
	{
		ZeroMemory( this, sizeof(*this) );

		memcpy( m_siInputItemUnique, _psiInputItemUnique, sizeof(m_siInputItemUnique) );
		memcpy( m_siInputItemNum,	_psiInputItemNum,	sizeof(m_siInputItemNum) );
	}

	SI32 m_siInputItemUnique[CONTRIBUTION_ITEM_NUM];
	SI16 m_siInputItemNum[CONTRIBUTION_ITEM_NUM];
};

class cltGameMsgRequest_Contribution_Item_Input
{
public:
	cltGameMsgRequest_Contribution_Item_Input( SI32 _siNPCKind, SI32* _psiItemUnique,  SI16* _psiItemNum, SI32* _psiUseItemIvenPos )
	{
		ZeroMemory( this, sizeof(*this) );

		m_siNPCKind = _siNPCKind;
		memcpy( m_siItemUnique,		_psiItemUnique,		sizeof(m_siItemUnique) );
		memcpy( m_siItemNum,		_psiItemNum,		sizeof(m_siItemNum) );
		memcpy( m_siUseItemIvenPos,	_psiUseItemIvenPos,	sizeof(m_siUseItemIvenPos) );
	}

	SI32 	m_siNPCKind;
	SI32 	m_siItemUnique[CONTRIBUTION_ITEM_NUM];
	SI16 	m_siItemNum[CONTRIBUTION_ITEM_NUM];
	SI32 	m_siUseItemIvenPos[CONTRIBUTION_ITEM_NUM];
};

class cltGameMsgRequest_Contribution_Make_NPC
{
public:
	cltGameMsgRequest_Contribution_Make_NPC( SI32 _siNPCKind )
	{
		ZeroMemory( this, sizeof(*this) );

		m_siNPCKind = _siNPCKind;
	}

	SI32 	m_siNPCKind;
};

#endif