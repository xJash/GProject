#ifndef _MSGTYPEVOTE_H_
#define _MSGTYPEVOTE_H_

#include "..\..\Common\VoteMgr\VoteMgr.h"


class cltGameMsgResponse_VoteKingAvailable
{
public:
	TCHAR			strVoteExplain[ MAX_VOTEEXPLAIN_LENGTH ];
	stCandidature	sCandidature[ MAX_CANDIDATURE_NUM ];

	cltGameMsgResponse_VoteKingAvailable( TCHAR *VoteExplain, stCandidature *pCandidature )
	{
		MStrCpy( strVoteExplain, VoteExplain, MAX_VOTEEXPLAIN_LENGTH );
		memcpy( sCandidature, pCandidature, sizeof( stCandidature ) * MAX_CANDIDATURE_NUM );
	}
};

class cltGameMsgRequest_VoteKingSelection
{
public:

	SI16 siListIndex;

	cltGameMsgRequest_VoteKingSelection( SI16 ListIndex )
	{
		siListIndex = ListIndex;
	}
};

class cltGameMsgResponse_VoteKingSelection
{
public:
	SI16 siListIndex;
	TCHAR strCharName[ MAX_PLAYER_NAME ];

	cltGameMsgResponse_VoteKingSelection( SI16 ListIndex, TCHAR *CharName )
	{
		siListIndex = ListIndex;
		MStrCpy( strCharName, CharName, MAX_PLAYER_NAME );
	}
};

class cltGameMsgResponse_VoteKingAggregate
{
public:
	TCHAR				pCharNames[MAX_CANDIDATURE_NUM][MAX_PLAYER_NAME];		// �ĺ��ڵ��� �̸�
	SI32				siVoteCounts[MAX_CANDIDATURE_NUM];		// �ĺ��ڵ��� ��ǥ��

	cltGameMsgResponse_VoteKingAggregate( TCHAR **CharNames, SI32* VoteCounts )
	{
		memcpy(siVoteCounts, VoteCounts, sizeof(SI32) * MAX_CANDIDATURE_NUM);
		memcpy(pCharNames, CharNames, MAX_PLAYER_NAME * MAX_CANDIDATURE_NUM * sizeof(TCHAR));
	}
};

// [����] ���Žý��� : ���� �뺸�� ��Ŷ
class cltGameMsgRequest_ElectionStump
{
public:
	SI16 m_siCharUnique;	// ������ �ϰ��ִ� ĳ���� ����ũ


	cltGameMsgRequest_ElectionStump( SI16 siCharUnique )
	{
		m_siCharUnique = siCharUnique;
	}
};



// [����] ���Žý��� : ���� ���ۿ� ��Ŷ
class cltGameMsgRequest_StartElectionStump
{
public:
	TCHAR		m_tszCandidate[ Const_Max_Candidate ];		// ���� �ĺ��� �̸�
	TCHAR		m_tszMaintenance[ Const_Max_Maintenance ];	// ��������


	cltGameMsgRequest_StartElectionStump( TCHAR* pszCandidate, TCHAR* pszMaintenance )
	{
		StringCchCopy( m_tszCandidate, Const_Max_Candidate, pszCandidate );
		StringCchCopy( m_tszMaintenance, Const_Max_Maintenance, pszMaintenance );
	}
};

// [����] ���Žý��� : ���� ���� ����
class cltGameMsgResponse_StartElectionStump
{
public:
	SI32		m_siCharUnique;								// ������ ĳ���� Unique
	TCHAR		m_tszCandidate[ Const_Max_Candidate ];		// ���� �ĺ��� �̸�
	TCHAR		m_tszMaintenance[ Const_Max_Maintenance ];	// ��������


	cltGameMsgResponse_StartElectionStump( SI32 siCharUnique, TCHAR* pszCandidate, TCHAR* pszMaintenance )
	{

		m_siCharUnique = siCharUnique;

		StringCchCopy( m_tszCandidate, Const_Max_Candidate, pszCandidate );
		StringCchCopy( m_tszMaintenance, Const_Max_Maintenance, pszMaintenance );
	}
};

// [����] ���Žý��� : ���� ����
class cltGameMsgResponse_EndElectionStump
{
public:
	SI32		m_siCharUnique;								// ������ ĳ���� Unique

	cltGameMsgResponse_EndElectionStump( SI32 siCharUnique )
	{
		m_siCharUnique = siCharUnique;
	}
};


// [����] ���ּ��� ��ǥ ����
class cltGameMsgResponse_StartVoteStatus
{
public:
	TCHAR	m_tszCandidateName[MAX_CANDIDATURE_NUM][MAX_PLAYER_NAME];	// �ĺ��� �̸�
	SI08	m_siCandidateNum;											// �ĺ��� ��

	SI32	m_siTotalVote;												// ��ü ��ǥ��
	SI32	m_siTopVote;												// �ִ� ��ǥ��

	cltGameMsgResponse_StartVoteStatus( TCHAR** ppszCandidateName, SI08 siCandidateNum, SI32 siTotalVote, SI32 siTopVote )
	{
		memcpy( m_tszCandidateName, ppszCandidateName, ( sizeof(TCHAR) * MAX_CANDIDATURE_NUM * MAX_PLAYER_NAME ) );

		m_siCandidateNum	= siCandidateNum;

		m_siTotalVote		= siTotalVote;
		m_siTopVote			= siTopVote;
	}
};

// [����] ���ּ��� ��ǥ ��Ȳ
class cltGameMsgResponse_VoteStatus
{
public:
	SI32	m_siNowVote[MAX_CANDIDATURE_NUM]; // ���� �� �ĺ��ں� ��ǥ��Ȳ

	cltGameMsgResponse_VoteStatus( SI32 *psiNowVote )
	{
		memcpy( m_siNowVote, psiNowVote, (sizeof(SI32) * MAX_CANDIDATURE_NUM) );
	}
};

#endif
