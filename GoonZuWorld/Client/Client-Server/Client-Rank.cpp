//---------------------------------
// 2004/5/19 ���°�
//---------------------------------
#include "..\Common\CommonHeader.h"
#include "..\Client.h"

#include "..\Server\Candidate\Candidate.h"

#include "..\..\CommonLogic\Cityhall\Cityhall.h"
#include "Msg\MsgType-Rank.h"

extern cltCommonLogic* pclClient;

// �ź� ���ĺ��� ������ ����. 
void cltClient::DoMsg_GAMEMSG_RESPONSE_CANDIDATELIST(cltMsg* pclMsg, SI32 id)
{
	// ���� ����� ������ CityHallManager���� �����Ѵ�. 
	cltGameMsgResponse_CandidateList* pclPacket = (cltGameMsgResponse_CandidateList*)pclMsg->cData;
	
	pclCityHallManager->pclClientCandidateManager->SetCandidate(pclPacket->siIndex, pclPacket->clRank.GetRankType(), &pclPacket->clPerson);
	
	switch(pclPacket->clRank.GetRankType())
	{
	case RANKTYPE_CITYHALL:
		// ����� �ĺ�  ������ ������Ʈ �� ���� �䱸�Ѵ�. 
		pclCityHallManager->UpdateMayorCandidateSwitch = TRUE;
		break;
	case RANKTYPE_BANK:
	case RANKTYPE_STOCK:
	case RANKTYPE_MARKET:
	case RANKTYPE_HOUSE:
	case RANKTYPE_HUNT:
	case RANKTYPE_POSTOFFICE:
	case RANKTYPE_HORSEMARKET:
	case RANKTYPE_REALESTATEMARKET:
	case RANKTYPE_SUMMONMARKET:
	case RANKTYPE_LAND:
	case RANKTYPE_FEAST:
	case RANKTYPE_SUMMONHEROMARKET:
	case RANKTYPE_MINE:
	case RANKTYPE_GUILD:
	case RANKTYPE_NEWMARKET:
		// ���� �ĺ�  ������ ������Ʈ �� ���� �䱸�Ѵ�. 
		pclCityHallManager->UpdateChiefCandidateSwitch = TRUE;
		break;
		
	default:
		MsgBox(TEXT("fd9872j"), TEXT("f8f:%d"), pclPacket->clRank.GetRankType());
		break;
	}

}
