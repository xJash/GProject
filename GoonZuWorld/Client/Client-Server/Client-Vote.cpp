#include "..\Client.h"
#include "..\Music\Music.h"
#include "..\CommonLogic\MsgType.h"
#include "Char\CharManager\CharManager.h"

#include "..\CommonLogic\Msg\MsgType-Vote.h"
#include "..\Interface\VoteDlg\VoteDlg.h"
#include "..\NInterface\NVoteDlg\NVoteDlg.h"
#include "..\Interface\ErrorMsgDlg\ErrorMsgDlg.h"
#include "..\Interface\NotifyMsgDlg\NotifyMsgDlg.h"
#include "..\Interface\SoundOnOffDlg\SoundOnOffDlg.h"
#include "../NInterface/NSoundOnOffDlg/NSoundOnOffDlg.h"

#include "../Interface/DrawChat/DrawChat.h"

#include "../ninterface/nvotedlg/NVoteStatusDlg.h"


void cltClient::DoMsg_GAMEMSG_RESPONSE_VOTEKINGAVAILABLE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_VoteKingAvailable *pclVoteKingAvailable = (cltGameMsgResponse_VoteKingAvailable*) pclMsg->cData;
	

	if ( g_SoundOnOffDlg.m_bFullScreenMode )
	{
		if(!m_pDialog[ NVOTEKING_DLG ])
		{
			CreateInterface(NVOTEKING_DLG);	
			
		}
		((CNVoteDlg*)m_pDialog[ NVOTEKING_DLG ])->Set( pclVoteKingAvailable->strVoteExplain, pclVoteKingAvailable->sCandidature );
	}

	return;
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_VOTEKINGSELECTION(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_VoteKingSelection *pclVoteKingSelection = (cltGameMsgResponse_VoteKingSelection*) pclMsg->cData;
	
	TCHAR* pTitle = GetTxtFromMgr(1409);
	TCHAR* pText = GetTxtFromMgr(1410);

	m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText, pclVoteKingSelection->strCharName );

	return;
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_VOTEKINGAGGREGATE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_VoteKingAggregate *pclVoteKingAggregate = (cltGameMsgResponse_VoteKingAggregate*) pclMsg->cData;
	
	TCHAR buf[256] = TEXT("");
	TCHAR charInfo[256] = TEXT("");
//	SI32 charid;
    
	TCHAR* pTitle = GetTxtFromMgr(5749);
	TCHAR* pText;

	pText = GetTxtFromMgr(5750);
	bool	bVoteIsNull = false;

	for (int i = 0; i < MAX_CANDIDATURE_NUM; i++)
	{
		if (id > 0)
		{
			if ( _tcscmp( pclVoteKingAggregate->pCharNames[i] , TEXT("") ) == 0)
			{
				if ( i == 0 )	bVoteIsNull = true;
				break;
			}
				
			StringCchPrintf(charInfo, 256, pText, pclVoteKingAggregate->pCharNames[i], pclVoteKingAggregate->siVoteCounts[i]);
			StringCchCat(buf, 256, charInfo);
			
		}
		
	}
	if ( bVoteIsNull )
		pText = GetTxtFromMgr(5751);
	else
        pText = buf;

	m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);

	return;
}

// [����] ���Žý��� : ������ʸ� ������
void cltClient::DoMsg_GAMEMSG_RESPONSE_STARTELECTIONSTUMP(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_StartElectionStump* pclinfo = (cltGameMsgResponse_StartElectionStump*)pclMsg->cData;
	if ( pclinfo == NULL )
	{
		return;
	}

	SI32 siCharID = cltCharCommon::CharUniqueInfo[ pclinfo->m_siCharUnique ];
	if ( pclCM->IsValidID( siCharID ) == false )
	{
		return;
	}

	cltCharClient* pclChar = (cltCharClient*)pclCM->CR[ siCharID ];
	if ( pclChar == NULL )
	{
		return;
	}

	// �ĺ��� �̸�
	StringCchCopy( pclChar->szCandidate, Const_Max_Candidate, pclinfo->m_tszCandidate );
	pclChar->szCandidate[ Const_Max_Candidate - 1 ] = '\0';

	// ���� ����
	StringCchCopy( pclChar->szMaintenance, Const_Max_Maintenance, pclinfo->m_tszMaintenance );
	pclChar->szMaintenance[ Const_Max_Maintenance - 1 ] = '\0';
	

	// ���������� �����Ѵ�
	pclChar->bIsElectionStump = true;

	// �̹����� ����
	pclChar->pclDrawChat->Set( pclDrawChatSurface, pclinfo->m_tszMaintenance, true, ELECTIONSTUMP, PSHOP_MODE_SELL, pclinfo->m_tszCandidate );

}

// [����] ���Žý��� : ����Ȱ�� ����
void cltClient::DoMsg_GAMEMSG_RESPONSE_ENDELECTIONSTUMP(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_EndElectionStump *pclinfo = (cltGameMsgResponse_EndElectionStump*)pclMsg->cData;
	if ( pclinfo == NULL )
	{
		return;
	}

	SI32 siCharID = cltCharCommon::CharUniqueInfo[ pclinfo->m_siCharUnique ];
	if ( pclCM->IsValidID( siCharID ) == false )
	{
		return;
	}

	cltCharClient* pclChar = (cltCharClient*)pclCM->CR[ siCharID ];
	if ( pclChar == NULL )
	{
		return;
	}

	// ������ �����
	pclChar->pclDrawChat->StopDraw();
	pclChar->bIsElectionStump = false;

	StringCchCopy( pclChar->szCandidate,	Const_Max_Candidate,	TEXT("") );
	StringCchCopy( pclChar->szMaintenance,	Const_Max_Maintenance,	TEXT("") );

}

// [����] ���ּ��� ��ǥ�� ���۵Ǿ���
void cltClient::DoMsg_GAMEMSG_RESPONSE_STARTVOTESTATUS(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_StartVoteStatus *pclinfo = (cltGameMsgResponse_StartVoteStatus*)pclMsg->cData;
	if ( pclinfo == NULL )
	{
		return;
	}

	if ( m_pDialog[NVOTESTATUS_DLG] == NULL )
	{
		CreateInterface(NVOTESTATUS_DLG);
	}

	((CNVoteStatusDlg*)m_pDialog[NVOTESTATUS_DLG])->SetStartVoteStatus( 
		(TCHAR**)pclinfo->m_tszCandidateName, 
		pclinfo->m_siTotalVote,  
		pclinfo->m_siCandidateNum, 
		pclinfo->m_siTopVote 
	);

}

// [����] ���ּ��� ��ǥ �� ��Ȳ
void cltClient::DoMsg_GAMEMSG_RESPONSE_VOTESTATUS(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_VoteStatus *pclinfo = (cltGameMsgResponse_VoteStatus*)pclMsg->cData;
	if ( pclinfo == NULL )
	{
		return;
	}

	if ( m_pDialog[NVOTESTATUS_DLG] == NULL )
	{
		CreateInterface(NVOTESTATUS_DLG);
	}

	((CNVoteStatusDlg*)m_pDialog[NVOTESTATUS_DLG])->SetVoteStatus( pclinfo->m_siNowVote );
}