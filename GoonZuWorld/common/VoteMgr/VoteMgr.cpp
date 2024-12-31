#include "VoteMgr.h"
#include "Msg/MsgType-Vote.h"

//-----------------------------
// Common
//-----------------------------
#include "PersonInfo.h"
#include "Char\CharManager\CharManager.h"

#include "../Char/CharServer/Char-Server.h"

#include "..\..\Client\Client.h"

#include "../../Server/Server.h"

#include "../../CommonLogic/MsgRval-Define.h"

extern cltCommonLogic* pclClient;


CVoteMgr::CVoteMgr()
{
	m_pstCandidature	= new stCandidature[ MAX_CANDIDATURE_NUM ];
	m_strVoteExplain	= new TCHAR[ MAX_VOTEEXPLAIN_LENGTH ];
	m_siGateID			= 0;

	Initialize();	
}

CVoteMgr::~CVoteMgr()
{	
	if ( m_strVoteExplain )
	{
		delete [] m_strVoteExplain;
		m_strVoteExplain = NULL;
	}

	if ( m_pstCandidature )
	{
		delete [] m_pstCandidature;
		m_pstCandidature = NULL;
	}
	
}

void CVoteMgr::Initialize()
{
	m_bPlayStatus	= false;

	memset( m_pstCandidature, 0, sizeof(stCandidature) * MAX_CANDIDATURE_NUM );
	memset( m_strVoteExplain, 0, MAX_VOTEEXPLAIN_LENGTH);
}

void CVoteMgr::Destroy()
{
}

bool CVoteMgr::ReadVoteData()
{
	// ������ ���Ͽ� �ھ� �θ� �ڵ����� ����������... ������ �׷��� ���� ����.
	FILE *fp = _tfopen( TEXT("./Vote/Vote.txt"), TEXT("rt") );

	if ( fp == NULL )
		return false;

	TCHAR Buffer[256] = TEXT("");
	SI32 index = 0;

	// ��ǥ ����
	//_ftscanf( fp, TEXT("%s"), m_strVoteExplain );
	_fgetts( m_strVoteExplain, MAX_VOTEEXPLAIN_LENGTH - 3, fp );		// -3 �� ������ �������... ( Ȥ�ó� �ؼ�... )

	SI32 VoteExplainLen = _tcslen( m_strVoteExplain );
	if ( VoteExplainLen < 1 )
	{
		return false;
	}

	if ( m_strVoteExplain[ VoteExplainLen - 1 ] == '\n' )
	{
		m_strVoteExplain[ VoteExplainLen - 1 ] = '\0';
	}

	// �׳� ���� ����.
	_fgetts( Buffer, 127, fp );

	StringCchCat( m_strVoteExplain, MAX_VOTEEXPLAIN_LENGTH, TEXT("") );
	//strcat( m_strVoteExplain, TEXT("\r\n") );

	while( ! feof( fp ) )
	{
		_ftscanf( fp, TEXT("%d %s %s"), &m_pstCandidature[ index ].siListIndex, m_pstCandidature[ index ].strChatName, m_pstCandidature[ index ].strWebPageURL );
		
		++index;

		if ( index >= MAX_CANDIDATURE_NUM )		// Ȥ�ó� txt ���Ͽ� �ĺ����� ��û �������� �;...
			break;
	}

	fclose( fp );

	return true;
}

void CVoteMgr::SetVoteStatus( bool bSetPlay )
{
	if ( bSetPlay )
	{
		// ������ ��ǥ�� �������̶�� ��°�� �ұ�? �׳� �־� ����?
		// Ȥ�ó� ��ڰ� �Ǽ��� 2�� ȣ���� ���� �����Ƿ�...
		if ( m_bPlayStatus )
		{
			return;
		}
		VotePlay();		
	}
	else
	{
		VoteStop();
	}

	OpenTheGate( bSetPlay );
	
	return;
}

bool CVoteMgr::IsPlayStatus()
{
	return m_bPlayStatus;
}

void CVoteMgr::VoteStop()
{
	LeavePoolMap();

	Initialize();

	return;
}

void CVoteMgr::VotePlay()
{	
	Initialize();
	// �Է� ����(Vote.txt) ����
	if ( ReadVoteData() == false )
	{
		m_bPlayStatus = false;
		return;
	}

	cltServer *pclserver = (cltServer *)pclClient;
	if ( pclserver == NULL )
	{
		return;
	}

	m_bPlayStatus	= true;
	m_siGateID		= 0;
	
	SI32 id;
	SI32 index = 0;

	// ���� 40�̻�, ���� ��ǥ�� ���� ������Ը� �޽����� ����
	while( id = pclClient->pclCM->GetCharOrder(index) )
	{
		index++;

		cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[id];
		
		if ( (pclClient->pclCM->IsValidID( id )) && (pclchar != NULL) && (pclchar->GetSession())
			&& (pclClient->pclCM->CR[id]->pclCI->clIP.GetLevel() >= Const_CanVote_MinLevel)
			&& (pclClient->pclCM->CR[id]->pclCI->clBI.siVoteKingSelectionIndex == 0)
		)
		{
			pclserver->SendServerResponseMsg( 0, SRVAL_NOTICE_WARPTOPOLL_MAP, 0, 0, pclchar->GetID() );
		}
	}

	return;
}

stCandidature *CVoteMgr::GetCandidatureList()
{
	return m_pstCandidature;
}

TCHAR *CVoteMgr::GetVoteExplain()
{
	return m_strVoteExplain;
}

// [����] ��ǥ�� ����Ʈ�� ����, �ݴ� �Լ�
void CVoteMgr::OpenTheGate( bool bOpen )
{
	cltServer* pclserver = (cltServer*)pclClient;
	if ( pclserver == NULL )
	{
		return;
	}

	SI32 siGateKind	= pclClient->GetUniqueFromHash("KIND_POLLINGGATE");	// ��ǥ�� ����Ʈ KIND


	if ( true == bOpen )
	{
		// ����Ʈ�� �����ߴµ� Ȥ�� �� �����ұ����
		if ( m_siGateID > 0 )
		{
			return;
		}

		SI32 siX		= 13;	// ��ġ�� ���縮������ ���� ���ڵ� �ִ� ��
		SI32 siY		= 38;
		SI32 siMapIndex	= 158;	// ���縮��

		m_siGateID = pclserver->SetNPCChar(siGateKind, VILLAGE_NONE, NULL, 1, 0, siX, siY, siMapIndex, NPCITEMMODE_NONE, NULL );
	}
	else
	{
		// ����Ʈ�� �����ɶ� �޾ƿ� ���̵�� ������ �����Ѵ�
		if ( pclserver->pclCM->IsValidID( m_siGateID ) == false )
		{
			return;
		}

		// �ش� ���̵��� �ɸ��Ͱ� ���ٸ� ����
		cltCharServer* pclGateChar = (cltCharServer*)pclClient->pclCM->CR[m_siGateID];
		if ( pclGateChar == NULL )
		{
			return;
		}

		// �ش� ���̵��� �ɸ��͸� �޾ƿ����� ����Ʈ�� �ƴ϶�� ����
		if ( pclGateChar->GetKind() != siGateKind )
		{
			return;
		}

		// �ش� ����Ʈ�� �����ϰ�
		pclGateChar->DeleteInCell();

		// ������ �Ϸ�Ǿ����� ����Ʈ ���̵� �ٽ� �ʱ�ȭ��Ŵ
		if ( pclserver->pclCM->DeleteChar( m_siGateID ) == TRUE )
		{
			m_siGateID = 0;
		}
	}

}

// ��ǥ�� ����Ǹ� ��ǥ�Ҹʿ� �ִ� ĳ���ʹ� ��� ��������
void CVoteMgr::LeavePoolMap()
{
	cltServer* pclserver = (cltServer*)pclClient;
	if( pclserver == NULL )
	{
		return;
	}

	cltCharServer* pclchar = NULL;

	// �ʿ� �ִ� ĳ���͸� �� ������ �̵���Ų��.
	SI32			siIndex		= 0;
	SI32			siCharID	= 0;

	SI32			siX			= 26;
	SI32			siY			= 72;
	cltWarpInfo		clWarpInfo( 1, MAPINDEX_PALACE, true, false, siX, siY, -1, -1 );


	while ( siCharID = pclClient->pclCM->GetCharOrder(siIndex) )
	{
		siIndex++;

		if ( !IsPC(siCharID) )
		{
			continue;
		}

		pclchar = (cltCharServer* )pclClient->pclCM->CR[siCharID];
		if ( pclchar == NULL )
		{
			continue;
		}
		
		// ��ǥ�� �ʿ� ������ ��Ƽ��
		if ( pclchar->GetMapIndex() != Const_MapIndex_PollMap )
		{
			continue;
		}

		// ���縮���� �̵� ��Ų��.
		if ( pclClient->pclCM->IsAlive(siCharID) == TRUE )
		{
			pclchar->SetWarpInfo(&clWarpInfo, 3000);
			pclchar->Warp();
		}

	}	// while ( siCharID = pclClient->pclCM->GetCharOrder(siIndex) ) ����
}