#include "VoteStatusMgr.h"
#include "Msg/MsgType-Vote.h"
#include "../../NLib/NUpdateTimer.h"
#include "Char\CharManager\CharManager.h"


extern cltCommonLogic* pclClient;

CVoteStatusMgr::CVoteStatusMgr()
{
	Init();
}

CVoteStatusMgr::~CVoteStatusMgr()
{

}


void CVoteStatusMgr::Init()
{
#ifdef _SAFE_MEMORY
	m_siVote.ZeroMem();
	m_siSendVote.ZeroMem();
#else
	ZeroMemory( m_siVote,	(sizeof(SI32)*MAX_CANDIDATURE_NUM) );
	ZeroMemory( m_siSendVote,	(sizeof(SI32)*MAX_CANDIDATURE_NUM) );
#endif
	ZeroMemory( m_tszCandidateName , (sizeof(TCHAR) * MAX_CANDIDATURE_NUM * MAX_PLAYER_NAME) );

	m_siCandidateNum	= 0;
	m_siTimeCounter		= 0;

	m_siTopVoteNum		= 0;
	m_siTotalVote		= 0;

	m_bStart			= false;
}


void CVoteStatusMgr::StartVoteStatus( SI32 *psiVote )
{
	//-- ����üũ
	if ( psiVote == NULL )
	{
		return;
	}

	//-- �̹� ��ǥ ���� ���̶�� ��ǥ�� ���� ����
	if ( m_bStart == true )
	{
		return;
	}

	//-- ��� ������ �ʱ�ȭ
	Init();

	SI08	siTopVote		= 0;
	SI32	siNewVote		= 0;
	SI32	siOldVote		= 0;
	SI32	siTotalVote		= 0;
	
	SI32	siTrickNum		= 200;	// ��ǥ �������� ��ǥ�� ��Ƣ���
	SI32	siRealTotalVote	= 0;	// �� ��ġ�� 0�̸� ��ǥ ������ �ʿ����
		
	if ( false == ReadCandidateName() )
	{
		return;
	}

	//-- �ĺ��� ��, �ִ� ��ǥ ǥ���� ��´�
	for ( SI32 siCount=0; siCount<MAX_CANDIDATURE_NUM; siCount++ )
	{
		// �ĺ��� �̸��� ����������
		if ( _tcscmp(m_tszCandidateName[siCount], TEXT("")) == 0 )
		{
			break;
		}
		// �ִ� ��ǥ���� ���ϱ� ���� ���� �۾�
		siNewVote = psiVote[siCount];
		
		// �ĺ��ں� ���� ��ǥ���� �����ϰ�
		m_siVote[siCount]	=	psiVote[siCount] + siTrickNum;
		siRealTotalVote		+=	psiVote[siCount];

		// �ִ� ��ǥ�ڰ� ���°���� ���ϰ�
		if ( siNewVote > siOldVote )
		{
			siTopVote = siCount;
			siOldVote = siNewVote;
		}
		
		// ��� ��ǥ���� ���Ѵ�
		siTotalVote += m_siVote[siCount];

		// �ĺ��� �� ���ϱ�
		m_siCandidateNum++;
	}
	
	//-- �ĺ��ڰ� ���ų� ��ǥ���� ���ٸ� ����
	if ( (0 >= m_siCandidateNum) || (0 >= siRealTotalVote) )
	{
		return;
	}

	m_siTopVoteNum	= m_siVote[siTopVote];
	m_siTotalVote	= siTotalVote;

	//-- ��ǥ�� ���۵Ǿ���
	m_bStart		= true;

	//-- �޽����� �����Ѵ�	
	cltGameMsgResponse_StartVoteStatus clMsgStartVoteStatus( (TCHAR**)m_tszCandidateName, m_siCandidateNum, m_siTotalVote, m_siTopVoteNum );
	cltMsg clMsg( GAMEMSG_RESPONSE_STARTVOTESTATUS, sizeof(clMsgStartVoteStatus), (BYTE*)&clMsgStartVoteStatus);
	pclClient->pclCM->SendAllPersonMsg( (sPacketHeader*)&clMsg );

	//-- Action �Լ��� �⵿��Ų��
	m_kActionTimer.Init(1 * 1000 * Const_VoteStatusMgr_End_Count);					// 1�п� �ѹ��� �����
	m_kActionTimer.SetActive(true, ::GetTickCount());	
	
}


void CVoteStatusMgr::Action()
{
	if ( m_kActionTimer.IsTimed( GetTickCount() ) == false )
	{
		return;
	}

	SendVoteStatus();

	m_siTimeCounter++;

	if ( m_siTimeCounter >= (Const_VoteStatusMgr_End_Count+1) )
	{
		m_kActionTimer.SetActive( false, GetTickCount() );
		m_bStart = false;
	}
}


void CVoteStatusMgr::SendVoteStatus()
{
	if ( (m_siCandidateNum <= 0) || (m_siCandidateNum > MAX_CANDIDATURE_NUM) )
	{
		return;
	}

	REAL32	fSendRate	= 0.0f;
	SI32	siSendVote	= 0;
	SI32	siRandNum	= 0;

	// 10�п� �ѹ��� �������� ���� �ȵ�� ����
	bool	bCondition	= false;//( (m_siTimeCounter > 0) && ((m_siTimeCounter % 10) == 0) );

	
	for ( SI32 siCount=0; siCount<m_siCandidateNum; siCount++ )
	{
		
		//-- ���� 1�� ī��Ʈ(1�п� �ѹ���) �Ҷ����� 0.33~3.32(100 / 30 = 3.33 ���ڸ� ����)
		siRandNum	= (rand() % 300) + 33; 
		fSendRate	= ( siRandNum / 10000.0f);

		// 10�п� �ѹ��� �� �ð��� ����ؼ�
		if ( true == bCondition )
		{
			fSendRate = 0.0333f * m_siTimeCounter;
		}

		if ( fSendRate < 0.0033f )
		{
			fSendRate = 0.0033f;
		}
		
		siSendVote = (SI32)(m_siVote[siCount] * fSendRate);

		if ( true == bCondition )
		{
			m_siSendVote[siCount] = siSendVote;
		}
		else
		{
			m_siSendVote[siCount] += siSendVote;
		}
		
		// ��ǥ�� �����ų� �������� ��ǥ������ ������
		if ( (m_siSendVote[siCount] > m_siVote[siCount]) || (m_siTimeCounter >= Const_VoteStatusMgr_End_Count) )
		{
			 m_siSendVote[siCount] = m_siVote[siCount];
		}
	}

	//-- ��ǥ��Ȳ �޽��� ����
	cltGameMsgResponse_VoteStatus clMsgVoteStatus( &m_siSendVote[0] );
	cltMsg clMsg( GAMEMSG_RESPONSE_VOTESTATUS, sizeof(clMsgVoteStatus), (BYTE*)&clMsgVoteStatus);
	pclClient->pclCM->SendAllPersonMsg( (sPacketHeader*)&clMsg );
}

// [����] �ĺ��� �̸��� �̾ƿ´�
bool CVoteStatusMgr::ReadCandidateName()
{
	// 
	FILE *fp = _tfopen( TEXT("./Vote/Vote.txt"), TEXT("rt") );

	if ( fp == NULL )
	{
		return false;
	}

	TCHAR	Buffer[256] = TEXT("");

	// ��ǥ ����
	// �����ڴ� �׳� ������
	for ( SI32 siCount=0; siCount<2; siCount++ )
	{
		_fgetts( Buffer, sizeof(Buffer), fp );
	}

	// ���� �̸� �о����
	SI32	siTempNum				= 0;		// ���� ����
	TCHAR	szTempUrl[256]			= TEXT("");	// ���� ����
	TCHAR	szName[MAX_PLAYER_NAME]	= TEXT("");	// �ĺ��� �̸�
	SI32	siIndex					= 0;

	while( ! feof( fp ) )
	{
		ZeroMemory( szName, (sizeof(TCHAR)*MAX_PLAYER_NAME) );

		_ftscanf( fp, TEXT("%d %s %s"), &siTempNum, szName, szTempUrl );

		StringCchCopy( m_tszCandidateName[siIndex], MAX_PLAYER_NAME, szName );

		++siIndex;

		if ( siIndex >= MAX_CANDIDATURE_NUM )
		{
			break;
		}
	}

	fclose( fp );

	return true;
}

void CVoteStatusMgr::WriteResult( SI32 *psiVote )
{
	if ( psiVote == NULL )
	{
		return;
	}

	if ( ReadCandidateName() == false )
	{
		return;
	}

	NTCHARString<2048>		Log;

	for (SI32 i = 0 ; i < MAX_CANDIDATURE_NUM ; i++)
	{
		if ( _tcscmp( m_tszCandidateName[i], TEXT("") ) == 0 )
		{
			break;
		}

		if( Log.Length() > 0 )		Log += "\t";

		Log += m_tszCandidateName[i];
		Log += ":";
		Log += SI32ToString( psiVote[i] );
	}

	// ������ �α׷� ����Ѵ�.
	pclClient->pclLog->FilePrint("Config\\voteresult.txt", "%s", (TCHAR*)Log);
}