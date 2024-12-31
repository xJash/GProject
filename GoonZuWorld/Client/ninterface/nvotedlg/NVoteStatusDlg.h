#pragma once

#include "../../InterfaceMgr/DialogController.h"
#include "../../Common/VoteMgr/VoteBaseInfo.h"
#include "../../Common/CommonHeader.h"

#include "../NLib/NUpdateTimer.h"


class CImageStatic;
class CStatic;
class CButton;
class CEdit;


class CNVoteStatusDlg : public CDialogController
{
enum VOTESTATUS_VARIABLE
{
	VOTESTATUS_BASE_DIALOG_WIDTH		= 250	// ���̾�α� �⺻ ����
	,VOTESTATUS_BASE_DIALOG_X			= 83	// ���̾�α� �⺻ ���� X
	,VOTESTATUS_BASE_DIALOG_Y			= 260	// ���̾�α� �⺻ ���� Y

	,VOTESTATUS_CANDIDATE_START_X		= 0		// �ĺ��ڰ� �׷��� ó�� ���� ��ġ(X)
	,VOTESTATUS_CANDIDATE_START_Y		= 0		// �ĺ��ڰ� �׷��� ó�� ���� ��ġ(Y)

	,VOTESTATUS_CANDIDATE_WIDTH			= 30	// �ĺ��� �׸� ũ��(����)
	,VOTESTATUS_CANDIDATE_HEIGHT		= 40	// �ĺ��� �׸� ũ��(����)

	,VOTESTATUS_MODE_MINIMUM			= 0		// �ּ�ȭ ���
	,VOTESTATUS_MODE_MAXIMUM			= 1		// �ִ�ȭ ���

	,VOTESTATUS_MAX_FRAME				= 2		// �� ���ϴ� �����ϴ� ������ ��

	,VOTESTATUS_DRAWMODE_RUN			= 0		// �޸��� �׸�
	,VOTESTATUS_DRAWMODE_LOSE			= 1 * VOTESTATUS_MAX_FRAME	// ������ �׸�
	,VOTESTATUS_DRAWMODE_WIN			= 2 * VOTESTATUS_MAX_FRAME	// �缱���� �� �׸�

	,VOTESTATUS_VOTE_READY				= 0		// ��ǥ ���� - �����
	,VOTESTATUS_VOTE_RUN				= 1		// ��ǥ ���� - ������
	,VOTESTATUS_VOTE_END				= 2		// ��ǥ ���� - ����

};

public:
	CNVoteStatusDlg();
	~CNVoteStatusDlg();

	void Create();
	void Init();

	static void CALLBACK StaticVoteStatusDlgProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void CALLBACK NVoteStatusDlgProc(UINT nEvent, int nControlID, CControllerObj* pControl);

	void Action();

	void DrawDialogLast( SI32 ScreenRX, SI32 ScreenRY );

//-- ������ ��������
public:
	void SetStartVoteStatus( TCHAR** pptszCnadidateName, SI32 siTotalVote,  SI08 siCandidateNum, SI32 siTopVoteNum );
	void SetVoteStatus( SI32 *psiNowVote );

//-- ǥ�ð���
public:
	void DrawCandidate( SI32 siRX, SI32 siRY );
	void WriteCandidate( SI08 siShowCandidateNumber );
	
//- ������ ��� ����
public:
	void WindowModeChange( bool bWindowMode );

private:
	void SaveNowDialog();
	void EndVote();
	void VoteCount();
	SI08 SearchTopCandidate();
	

//-- ��Ʈ�ѿ� ����
private:
	//CImageStatic		*m_pcisBack;
	CStatic				*m_pcsVote;
	CStatic				*m_pcsPercentage;
	CButton				*m_pcbMinimum;
	CButton				*m_pcbMaximum;
	CStatic				*m_pcsDisplay;
//-- �ĺ��� ���� ����
	TCHAR				m_tszCandidateName[MAX_CANDIDATURE_NUM][MAX_PLAYER_NAME];
	SI32				m_siVote[MAX_CANDIDATURE_NUM];			// ������ ���� ���� ���� ��ǥ��
	SI32				m_siDrawVote[MAX_CANDIDATURE_NUM];		// �ɸ��� Draw�� ���� ���庯��
	SI08				m_siDrawMode[MAX_CANDIDATURE_NUM];		// ��ο� ����

	SI32				m_siDrawOrder[MAX_CANDIDATURE_NUM];		// �ĺ��� �׸��� ����

	SI32				m_siTotalVote;		// �� ��ǥ��
	SI32				m_siNowTotalVote;	// ���� ��ǥ��

	SI08				m_siCandidateNum;	// �ĺ��� ��
	SI08				m_siNowShowNum;		// ���� �������� �ĺ��� ��ȣ
	SI32				m_siTopVoteNum;		// �׷����� �ִ� ����(�ִ� ��ǥ�ڼ��� ��ǥ��)

	SI08				m_siNowFrame;		// ���� �׸��� ������

	SI08				m_siVoteStatus;		// ��ǥ ��Ȳ

	TSpr				m_sprCandidate;		// �ĺ���  �׸�

//-- �������� ���� ����
private:
	bool				m_bWindowMode;		// ���� ������ ���

	SI16				m_siWindowPosX;		// �ִ����϶� ������ ������ X
	SI16				m_siWindowPosY;		// �ִ����϶� ������ ������ X

	SI16				m_siWindowWidth;	// �ִ����϶� ������ ����
	SI16				m_siWindowHeight;	// �ִ����϶� ������ ����

	bool				m_bLock;			// ������ ���濩������


	NUpdateTimer		m_kUpdateTimer_WriteCandidate;	// �ĺ��� �̸��� �������� �κ�
	NUpdateTimer		m_kUpdateTimer_DrawCandidate;	// �ĺ��� �׸��� �׷����� �κ�
	NUpdateTimer		m_kUpdateTimer_End;				// ������ �� ����Ű�� Ÿ�̸�
};
