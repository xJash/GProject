//---------------------------------
// 2003/6/12 ���°�
//---------------------------------

#include <CommonLogic.h>

#include "../../Client/client.h"

#include "Char/CharCommon/Char-Common.h"

#include "CityHall.h"
#include "../../Common/HintDlg/HintDlg.h"

#include "Char/CharManager/CharManager.h"

#include "../../Server/Candidate/Candidate.h"
#include "MsgType-Structure.h"
#include "MsgType-Person.h"

#include "../../Client/Interface/SearchDetailDlg/SearchDetailDlg.h"
#include "NInterface/NHintDlg/NHintDlg.h"
#include "NInterface/NSoundOnOffDlg/NSoundOnOffDlg.h"
#include "Interface/SoundOnOffDlg/SoundOnOffDlg.h"

#include "../../Resource.h"

extern cltCommonLogic* pclClient;


cltRankCandidate clRankCandidate[ MAX_RANKTYPE_NUMBER ]=
{
	{ RANKTYPE_CITYHALL,			TEXT(""),		TEXT(""),		35, TEXT("") },
	{ RANKTYPE_BANK,				TEXT(""),		TEXT(""),		30, TEXT("") },
	{ RANKTYPE_STOCK,				TEXT(""),		TEXT(""),		30, TEXT("") },
	{ RANKTYPE_MARKET,				TEXT(""),		TEXT(""),		30, TEXT("") },
	{ RANKTYPE_HOUSE,				TEXT(""),		TEXT(""),		30, TEXT("") },
	{ RANKTYPE_HUNT,				TEXT(""),	    TEXT(""),  		30, TEXT("") },	
	{ RANKTYPE_POSTOFFICE,  		TEXT(""),		TEXT(""),		30, TEXT("") },
	{ RANKTYPE_PORT,				TEXT(""),		TEXT(""),		30, TEXT("") },
	{ RANKTYPE_HORSEMARKET, 		TEXT(""),	    TEXT(""),	    30, TEXT("") },
	{ RANKTYPE_REALESTATEMARKET,	TEXT(""),		TEXT(""),		30, TEXT("") },
	{ RANKTYPE_SUMMONMARKET,		TEXT(""),		TEXT(""),	    30, TEXT("") },
	{ RANKTYPE_SHIPMARKET,			TEXT(""),		TEXT(""),	    30, TEXT("") },
	{ RANKTYPE_LAND,				TEXT(""),		TEXT(""),		30, TEXT("") },
	{ RANKTYPE_FEAST,				TEXT(""),	    TEXT(""),	    30, TEXT("") },
	{ RANKTYPE_SUMMONHEROMARKET,	TEXT(""),		TEXT(""),	    30, TEXT("") },
	{ RANKTYPE_MINE,				TEXT(""),		TEXT(""),		30, TEXT("") },
	{ RANKTYPE_GUILD,				TEXT(""),		TEXT(""),		30, TEXT("") },
	{ RANKTYPE_NEWMARKET,		TEXT(""),		TEXT(""),		30, TEXT("") },
	{ 0, NULL, NULL, NULL }
};




// �� �ü��� �� ���� ����Ʈ �ʱ�ȭ 
void cltCityHallManager::InitRankList( HWND hDlg )
{

}

// '��'�� Ÿ���� �����Ѵ�. 
void cltCityHallManager::SetCandidateCombo(HWND hDlg)
{
}


// ���õ� ���ڿ��� �ٰŷ� ������ ������ �����ش�. 
void cltCityHallManager::SetRankCandidateHelp(const TCHAR* szSelText)
{
}

// ���õ� RankType�� �Ǳ� ���� �ʿ��� ������ ���Ѵ�.
SI32 cltCityHallManager::GetNeedLevelFromRankType(SI32 ranktype)
{
	SI32 index = 0;

	while(clRankCandidate[index].siRankType)
	{
		if(ranktype == clRankCandidate[index].siRankType)
		{
			return clRankCandidate[index].siNeedLevel;
		}

		index++;
	}

	return 0;
}

// ���õ� ���ڿ�(�źи�)�� �ٰŷ� ������ �ź��ڵ带 ���´�.
SI32 cltCityHallManager::GetRankTypeFromRankName(const TCHAR* szSelText)
{
	SI32 ranktype = 0;
	SI32 index = 0;

	if(szSelText == NULL)return 0;

	while(ranktype = clRankCandidate[index].siRankType)
	{
		if(_tcscmp(szSelText, clRankCandidate[index].szRankName) == 0)
		{
			return ranktype;
		}

		index++;
	}

	return 0;
}


// ���õ� ���ڿ�(�ü���)�� �ٰŷ� ������ �ź��ڵ带 ���´�.
SI32 cltCityHallManager::GetRankTypeFromStructureName(const TCHAR* szSelText)
{
	SI32 ranktype = 0;
	SI32 index = 0;

	if(szSelText == NULL)return 0;

	while(ranktype = clRankCandidate[index].siRankType)
	{
		if(_tcscmp(szSelText, clRankCandidate[index].szStructureName) == 0)
		{
			return ranktype;
		}

		index++;
	}

	return 0;
}

