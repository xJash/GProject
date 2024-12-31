#include "NVoteStatusDlg.h"

#include "../../Client/client.h"

//#include "../../InterfaceMgr/interface/ImageStatic.h"
#include "../../InterfaceMgr/Interface/Button.h"
#include "../../InterfaceMgr/Interface/Static.h"
#include "../../InterfaceMgr/Interface/Edit.h"



#include "../../InterfaceMgr/InterfaceMgr.h"
#include "../../InterfaceMgr/InterfaceImgMgr/InterfaceImgMgr.h"

#include "../../InterfaceMgr/InterfaceFile.h"



extern cltCommonLogic* pclClient;

CNVoteStatusDlg::CNVoteStatusDlg() : CDialogController()
{
	//m_pcisBack			= NULL;
	m_pcsVote			= NULL;
	m_pcsPercentage		= NULL;
	m_pcbMinimum		= NULL;
	m_pcbMaximum		= NULL;
	m_pcsDisplay		= NULL;

	Init();

	//-- Ÿ�̹� �ð� ����

	// �ĺ��� �̸��� ������ �ֱ� 1��
	m_kUpdateTimer_WriteCandidate.Init( 1 * 1000 );

	// �ĺ��� �׸��� �׸� �ֱ� 1/10��
	m_kUpdateTimer_DrawCandidate.Init( 100 );

	GP.LoadSprFromFile( TEXT("NInterface/image/IMAGE_30x40_00_000.SPR"), &m_sprCandidate );
}

CNVoteStatusDlg::~CNVoteStatusDlg()
{
	//SAFE_DELETE( m_pcisBack );
	SAFE_DELETE( m_pcsVote );
	SAFE_DELETE( m_pcsPercentage );
	SAFE_DELETE( m_pcbMinimum );
	SAFE_DELETE( m_pcbMaximum );
	SAFE_DELETE( m_pcsDisplay );

	if ( m_sprCandidate.pImage )
	{
		GP.FreeSpr( m_sprCandidate );
	}

}

void CNVoteStatusDlg::Create( )
{
	if (IsCreate() == true )
	{
		return;
	}

	CInterfaceFile file;

	//-- �⺻����
	file.LoadFile(TEXT("NInterface/Data/NVoteKing/DLG_NVoteStatus.ddf"));
	file.CreatePopupDialog( this, NVOTESTATUS_DLG, TEXT("dialog_votestatus"), StaticVoteStatusDlgProc);

	//-- ��ü����
	//m_pcisBack			= new CImageStatic( this );
	m_pcsVote			= new CStatic( this );
	m_pcsPercentage		= new CStatic( this );
	m_pcbMinimum		= new CButton( this );
	m_pcbMaximum		= new CButton( this );
	m_pcsDisplay		= new CStatic( this );

	//-- �޼����� ����
	file.CreateControl( m_pcbMinimum,		NVOTESTATUS_MINIMUMBUTTON,	TEXT("button_minimum") );
	file.CreateControl( m_pcbMaximum,		NVOTESTATUS_MAXIMUMBUTTON,	TEXT("button_maximum") );

	file.CreateControl( m_pcsVote,			NVOTESTATUS_VOTE,			TEXT("statictext_vote") );
	file.CreateControl( m_pcsPercentage,	NVOTESTATUS_PERCENTAGE,		TEXT("statictext_percentage") );
	
	file.CreateControl( m_pcsDisplay,		NVOTESTATUS_DISPLAY,		TEXT("statictext_display") );

	//file.CreateControl( m_pcisBack,			NVOTESTATUS_BACK,			TEXT("imagestatic_back") );

	//-- �ؽ�Ʈ ����
	m_pcsDisplay->SetFontWeight( 600 );
	m_pcsDisplay->SetFontColor( RGB( 255, 250, 250 ) );
	//m_pcsDisplay->SetHeight( 0 );
	//m_pcsDisplay->SetWidth( 0 );
	
	m_pcsVote->SetFontWeight( 600 );
	m_pcsVote->SetFontColor( RGB( 255, 250, 250 ) );

	m_pcsPercentage->SetFontWeight( 600 );
	m_pcsPercentage->SetFontColor( RGB( 255, 250, 250 ) );

	//-- �⺻ ���� ��ġ / ���� ����
	SetX( VOTESTATUS_BASE_DIALOG_X );
	SetY( VOTESTATUS_BASE_DIALOG_Y );
	SaveNowDialog();
	WindowModeChange( VOTESTATUS_MODE_MAXIMUM );
		
	SetActionTimer( 200 );
	SetTimerOnOff( true );


	return;
}

void CNVoteStatusDlg::Init()
{
	ZeroMemory( m_tszCandidateName,	(sizeof( TCHAR ) * MAX_CANDIDATURE_NUM * MAX_PLAYER_NAME) );
	ZeroMemory( m_siVote,			(sizeof( SI32 ) * MAX_CANDIDATURE_NUM) );
	ZeroMemory( m_siDrawVote,		(sizeof( SI32 ) * MAX_CANDIDATURE_NUM) );

	for ( SI08 siCount=0; siCount<MAX_CANDIDATURE_NUM; siCount++ )
	{
		m_siDrawOrder[ siCount ] = siCount;
	}

	memset( m_siDrawMode, VOTESTATUS_DRAWMODE_RUN, (sizeof(SI08) * MAX_CANDIDATURE_NUM) );

	m_siTotalVote		= 0;
	m_siNowTotalVote	= 0;

	m_siCandidateNum	= 0;
	m_siNowShowNum		= 0;
	m_siTopVoteNum		= 0;

	m_siNowFrame		= 0;

	m_bLock				= false;

	m_siVoteStatus		= VOTESTATUS_VOTE_READY;
}

void CALLBACK CNVoteStatusDlg::StaticVoteStatusDlgProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl )
{
	CNVoteStatusDlg *pThis = (CNVoteStatusDlg*) pControllerMgr;
	pThis->NVoteStatusDlgProc( nEvent, nControlID, pControl );
}

void CALLBACK CNVoteStatusDlg::NVoteStatusDlgProc(UINT nEvent, int nControlID, CControllerObj* pControl )
{
	switch(nControlID)
	{
	case NVOTESTATUS_MINIMUMBUTTON:
		{
			switch(nEvent)
			{				

			case EVENT_BUTTON_CLICKED:
				{
					WindowModeChange( VOTESTATUS_MODE_MINIMUM );
				}
				break;
			}
		}
		break;

	case NVOTESTATUS_MAXIMUMBUTTON:
		{
			switch(nEvent)
			{				

			case EVENT_BUTTON_CLICKED:
				{
					WindowModeChange( VOTESTATUS_MODE_MAXIMUM );
				}
				break;
			}

		}
		break;

	}

	return;
}

//--------------------------------------------------------------------------------------------- 
//	TCHAR** pptszCnadidateName	: ���� �ĺ��ڵ��� �̸�
//	SI32 siTotalVote			: �� ��ǥ��
//	SI08 siMaxCandidate			: ���� ������ �ĺ��� ��
//	SI32 siTopVoteNum			: ���� �ĺ��� �� �ִ� ��ǥ��
//--------------------------------------------------------------------------------------------- 
void CNVoteStatusDlg::SetStartVoteStatus( TCHAR** pptszCnadidateName, SI32 siTotalVote,  SI08 siCandidateNum, SI32 siTopVoteNum )
{
	

	if ( (pptszCnadidateName == NULL) || (siTotalVote <= 0) )
	{
		return;
	}

	if ( (siCandidateNum <= 0) || (siCandidateNum > MAX_CANDIDATURE_NUM) )
	{
		return;
	}
	//SaveNowDialog();
	Init();

	m_bLock = true;
	
	m_siCandidateNum	= siCandidateNum;
	m_siTopVoteNum		= siTopVoteNum;
	m_siTotalVote		= siTotalVote;

	memcpy( m_tszCandidateName, pptszCnadidateName, (sizeof(TCHAR) * MAX_CANDIDATURE_NUM * MAX_PLAYER_NAME) );

	// ��带 �ִ�ȭ ���� ��ȯ
	WindowModeChange( VOTESTATUS_MODE_MAXIMUM );
	
	// �ĺ��� �����ֱ� Ÿ�̸� �õ�
	m_kUpdateTimer_WriteCandidate.SetActive( true, GetTickCount() );
	// �ĺ��� �׸��� Ÿ�̸� �õ�
	m_kUpdateTimer_DrawCandidate.SetActive( true, GetTickCount() );

	m_siVoteStatus = VOTESTATUS_VOTE_RUN;

	m_bLock = false;

}

void CNVoteStatusDlg::SetVoteStatus( SI32 *psiNowVote )
{
	if ( psiNowVote == NULL )
	{
		return;
	}

	// ��ǥ ��Ȳ�� �޴µ� �߰��� �α����ؼ� ó�� ���� ������ ���� ���ߴٸ� ������ ���� ������ ��û
	if ( VOTESTATUS_VOTE_READY == m_siVoteStatus )
	{
		cltMsg clMsg( GAMEMSG_REQUEST_STARTVOTESTATUS, 0, NULL );
		pclClient->SendMsgToServer((sPacketHeader*)&clMsg);

		return;
	}

	if ( m_siCandidateNum <= 0 )
	{
		return;
	}

	m_bLock = true;

	for ( SI32 siCount=0; siCount<m_siCandidateNum; siCount++ )
	{
		m_siVote[siCount] = psiNowVote[siCount];
	}

	//memcpy( m_siVote, psiNowVote, (sizeof(SI32)*MAX_CANDIDATURE_NUM) );

	// �׸��� ���� ����
	for ( SI32 siCount=0; siCount<m_siCandidateNum; siCount++ )
	{
		m_siDrawOrder[ siCount ] = (m_siDrawOrder[ siCount ] + 1) % m_siCandidateNum;
	}

	m_bLock = false;

}

void CNVoteStatusDlg::DrawDialogLast( SI32 ScreenRX, SI32 ScreenRY )
{
	if ( true == m_bLock )
	{
		return;
	}

	if ( VOTESTATUS_MODE_MAXIMUM == m_bWindowMode )
	{
		DrawCandidate( ScreenRX, ScreenRY );
	}
	
}

void CNVoteStatusDlg::DrawCandidate( SI32 siRX, SI32 siRY )
{
	if ( (m_siCandidateNum <= 0) || (m_siCandidateNum > MAX_CANDIDATURE_NUM) )
	{
		return;
	}

	if ( m_siTopVoteNum <= 0 )
	{
		return;
	}

	if ( VOTESTATUS_MODE_MAXIMUM != m_bWindowMode )
	{
		return;
	}

	if ( m_kUpdateTimer_DrawCandidate.IsTimed( GetTickCount() ) == true )
	{
		m_siNowFrame = (++m_siNowFrame) % VOTESTATUS_MAX_FRAME;
	}

	// ���� ��ǥ�� ǥ�õ� ��ġ ������
	SI32	siCorrectionX		= this->GetX() + siRX;
	SI32	siCorrectionY		= this->GetY() + siRY;

	SI32	siStartPositionX	= VOTESTATUS_CANDIDATE_START_X + siCorrectionX - (VOTESTATUS_CANDIDATE_WIDTH/2);
	SI32	siStartPositionY	= VOTESTATUS_CANDIDATE_START_Y + siCorrectionY - VOTESTATUS_CANDIDATE_HEIGHT + 6;
	SI32	siDrawX				= 0;
	REAL32	fDrawWidthRate		= 0.0f;

	SI32	siNowFrame			= 0;
	SI32	siNowFont			= 0;
	SI32	siCount				= 0;
	SI32	siRealIndex			= 0;


	for ( SI32 siIndex=0; siIndex<m_siCandidateNum; siIndex++ )
	{
		//-- �׸��� ����
		siRealIndex		= m_siDrawOrder[ siIndex ];
		siCount			= m_siDrawVote[siRealIndex];
	
		fDrawWidthRate	= siCount / ( m_siTopVoteNum * 1.0f );
		siDrawX			= (SI32)( VOTESTATUS_BASE_DIALOG_WIDTH * fDrawWidthRate );

		siNowFrame		= (m_siNowFrame + siCount) % VOTESTATUS_MAX_FRAME;
		// ���ٿ� �׸��� 6�� �־ *6�� ��
		siNowFont		= (siRealIndex*6) + siNowFrame + m_siDrawMode[siRealIndex];

		GP.PutSpr( &m_sprCandidate, (siStartPositionX + siDrawX), siStartPositionY, siNowFont );
	
	}
}

void CNVoteStatusDlg::Action()
{
	if ( true == m_bLock )
	{
		return;
	}

	switch ( m_siVoteStatus )
	{
		case VOTESTATUS_VOTE_READY:
			{
				Show( false );
			}
			break;

		case VOTESTATUS_VOTE_RUN:
			{
				if ( IsShow() == false )
				{
					Show( true );
				}

				// 1�ʿ� �ѹ��� �������� �ĺ��ڰ� ����ȴ�
				if ( m_kUpdateTimer_WriteCandidate.IsTimed(GetTickCount()) )
				{
					if ( 0 >= m_siCandidateNum )
					{
						return;
					}

					m_siNowShowNum = (m_siNowShowNum + 1) % m_siCandidateNum;

					WriteCandidate( m_siNowShowNum );

				} // if ( m_kUpdateTimer_WriteCandidate.IsTimed(GetTickCount()) ) ����

				VoteCount();

			}
			break;

		case VOTESTATUS_VOTE_END:
			{
				WriteCandidate( m_siNowShowNum );

				if ( m_kUpdateTimer_End.IsTimed(GetTickCount()) )
				{
					DeleteDialog();
				}
			}
			break;
	} // switch ( m_siVoteStatus ) ����

}

// �ĺ��� ǥ�õǴ� ����
void CNVoteStatusDlg::WriteCandidate( SI08 siShowCandidateNumber )
{
	if ( (siShowCandidateNumber < 0) || (siShowCandidateNumber >= m_siCandidateNum) )
	{
		return;
	}
	
	NTCHARString128	kCandidateVote( GetTxtFromMgr(8106) );
	NTCHARString128 kPercentage( GetTxtFromMgr(8107) );

	REAL32			fPercentage		= 0.0f;
	SI32			siCandidateVote = m_siVote[siShowCandidateNumber];

	//---------------------------------------------------------------------------------------------------
	//	���� ��ǥ �� ǥ�� 
	//---------------------------------------------------------------------------------------------------
	
	// �ĺ��� ��ǥ��	
	if ( m_siNowTotalVote <= 0 )
	{
		fPercentage = 0.0f;
	}
	else
	{
		fPercentage	= siCandidateVote / (REAL32)(m_siNowTotalVote) * 100;
	}
	// �ĺ��� ��ȣ(�迭 �ε����̱� ������ 0���� ������)
	kCandidateVote.Replace( TEXT("#number#"), SI32ToString(siShowCandidateNumber+1) );
	// �ĺ��� �̸�
	kCandidateVote.Replace( TEXT("#name#"), m_tszCandidateName[siShowCandidateNumber] );
	// �ĺ��� ��ǥ��
	kCandidateVote.Replace( TEXT("#vote#"), SI32ToString(siCandidateVote) );
	// �ĺ��� ��ǥ��
	kCandidateVote.Replace( TEXT("#percentage#"), REAL32ToString( fPercentage ) );


	m_pcsVote->SetText( kCandidateVote, DT_VCENTER );
	m_pcsDisplay->SetText( kCandidateVote, DT_VCENTER );

	//---------------------------------------------------------------------------------------------------
	//	��ü ��ǥ �� ǥ�� 
	//---------------------------------------------------------------------------------------------------

	// ��ǥ��
	if ( m_siTotalVote <= 0 )
	{
		fPercentage = 0.0f;
	}
	else
	{
		fPercentage = m_siNowTotalVote / (REAL32)(m_siTotalVote) * 100;
	}
	// ��ü ��ǥ��
	kPercentage.Replace( TEXT("#totalvote#"), SI32ToString( m_siTotalVote ) );
	// ��ǥ��
	kPercentage.Replace( TEXT("#percentage#"), REAL32ToString( fPercentage ) );

	// ����
	m_pcsPercentage->SetText( kPercentage, DT_VCENTER );
	
}

void CNVoteStatusDlg::WindowModeChange( bool bWindowMode )
{
	if ( VOTESTATUS_MODE_MINIMUM == bWindowMode )
	{
		//-- ���̴� ��Ʈ��
		//m_pcbMaximum->Show( true );
		m_pcsDisplay->Show( true );
		m_pcbMaximum->SetDrawOption( SPR_PUTSPRT );
		
		//-- �Ⱥ��̴� ��Ʈ��
		m_pcsVote->Show( false );
		m_pcsPercentage->Show( false );
		//m_pcbMinimum->Show( false );
		m_pcbMinimum->SetAlphaValue( 0 );
		m_pcbMinimum->SetDrawOption( SPR_PUTSPRALPHAT );
		
		SaveNowDialog();
				
		//-- ������ ũ�� �ּ�ȭ
		SetDialogPos( VOTESTATUS_BASE_DIALOG_X, VOTESTATUS_BASE_DIALOG_Y, 0, 0 );
		
		SetMoveable( false );
		
		//-- ������ ����
		SetAlphaMode( 0 );
		
	}
	else
	{
		//-- �Ⱥ��̴� ��Ʈ��
		//m_pcbMaximum->Show( false );
		m_pcsDisplay->Show( false );
		m_pcbMaximum->SetAlphaValue( 0 );
		m_pcbMaximum->SetDrawOption( SPR_PUTSPRALPHAT );

		//-- ���̴� ��Ʈ��
		m_pcsVote->Show( true );
		m_pcsPercentage->Show( true );
		//m_pcbMinimum->Show( true );
		m_pcbMinimum->SetDrawOption( SPR_PUTSPRT );
		
		//-- ������ ũ�� �ִ�ȭ
		SetDialogPos( m_siWindowPosX, m_siWindowPosY, m_siWindowWidth, m_siWindowHeight );


		SetMoveable( true );

		// ������ ����
		SetDrawOption( SPR_PUTSPRT );

	}

	m_bWindowMode = bWindowMode;

	WriteCandidate( m_siNowShowNum );

}

void CNVoteStatusDlg::SaveNowDialog()
{
	//-- ���� ������ ũ��/��ġ ����
	m_siWindowPosX		= this->GetX();
	m_siWindowPosY		= this->GetY();

	m_siWindowWidth		= this->GetWidth();
	m_siWindowHeight	= this->GetHeight();

}

SI08 CNVoteStatusDlg::SearchTopCandidate()
{
	if ( (0 >= m_siCandidateNum) || (MAX_CANDIDATURE_NUM < m_siCandidateNum) )
	{
		return -1;
	}

	SI08 siTopNumber	= -1;
	SI32 siTopVote		= 0;

	for ( SI32 siCount=0; siCount<m_siCandidateNum; siCount++ )
	{
		if ( siTopVote < m_siVote[siCount] )
		{
			siTopNumber = siCount;
			siTopVote	= m_siVote[siCount];
		}
	}

	return siTopNumber;
}

void CNVoteStatusDlg::EndVote()
{
	if ( m_siVoteStatus == VOTESTATUS_VOTE_END )
	{
		return;
	}

	// ���� ��带 ����� �ٲ��ְ�
	m_siVoteStatus = VOTESTATUS_VOTE_END;

	// �����Ű�� Ÿ�̸� 10��
	m_kUpdateTimer_End.Init( 10 * 1000 );
	// ���� Ÿ�̸Ӹ� �õ��Ѵ�
	m_kUpdateTimer_End.SetActive( true, GetTickCount() );

	// �� �ĺ��ڵ��� �̹���
	memset( m_siDrawMode, VOTESTATUS_DRAWMODE_LOSE, (sizeof(SI08) * MAX_CANDIDATURE_NUM) );

	// �̱� �ĺ����� �̹���
	SI08 siSearchNumber = SearchTopCandidate();

	if ( siSearchNumber >= 0 )
	{
		m_siDrawMode[siSearchNumber] = VOTESTATUS_DRAWMODE_WIN;
	}

	// �̱� �ĺ����� �����θ� �������� ����
	m_siNowShowNum = siSearchNumber;

	// �̱� �ĺ��� �̹����� �� ó���� �������� �ϱ�
	SI32 siTopOrder	= (m_siCandidateNum-1);
	SI32 siSwapNum	= 0;

	// ���� ��ȣ�� �ٲ� �ʿ����
	if ( m_siNowShowNum != siTopOrder )
	{
		siSwapNum						= m_siDrawOrder[m_siNowShowNum];
		m_siDrawOrder[m_siNowShowNum]	= m_siDrawOrder[siTopOrder];
		m_siDrawOrder[siTopOrder]		= siSwapNum;
	}
}

void CNVoteStatusDlg::VoteCount()
{
	if ( (m_siCandidateNum <= 0) || (m_siCandidateNum > MAX_CANDIDATURE_NUM) )
	{
		return;
	}

	if ( m_siTopVoteNum <= 0 )
	{
		return;
	}

	SI32	siNowTotalVote = 0;


	for ( SI32 siIndex=0; siIndex<m_siCandidateNum; siIndex++ )
	{
		//-- ��� ����
		m_siDrawVote[siIndex]++;

		if ( m_siDrawVote[siIndex] >= m_siVote[siIndex] )
		{
			m_siDrawVote[siIndex] = m_siVote[siIndex];
		}

		siNowTotalVote += m_siDrawVote[siIndex];
	}

	m_siNowTotalVote = siNowTotalVote;


	// ��ǥ�� �������� Ȯ���ϰ� �����ٸ�
	if ( m_siNowTotalVote >= m_siTotalVote )
	{
		EndVote();
	}

}
