//////////////////////////////////////////////////////////////////////////
//-
//////////////////////////////////////////////////////////////////////////


#pragma once

#include <directives.h>

#include "CommonHeader.h"
#include "../../Client/client.h"
#include "../../InterfaceMgr/DialogController.h"

class CButton;
class CImageStatic;


class NGawiBawiBoDlg : public CDialogController
{
private:
	static const SI32	m_sMaxSelectButtonNum	= 4;
	static const SI32	m_sMaxStatus			= 2;


	enum ENUM_GAWIBAWIBO_SELECT		//	���������� ���� �ε���
	{
		GAWIBAWIBO_NONE,
		GAWIBAWIBO_GAWI,
		GAWIBAWIBO_BAWI,
		GAWIBAWIBO_BO,
	};

	enum ENUM_GAWIBAWIBO_TEAM		//	�� �ε���
	{
		GAWIBAWIBO_PLAYER,
		GAWIBAWIBO_NPC,
	};

	enum ENUM_GAWIBAWIBO_ICON_INDEX		//	�� �� ���� ������ �ε���
	{
		GAWIBAWIBO_NPC_GAWI			= 0,
		GAWIBAWIBO_NPC_BO			= 1,
		GAWIBAWIBO_NPC_BAWI			= 2,
		
		GAWIBAWIBO_PLAYER_GAWI		= 3,
		GAWIBAWIBO_PLAYER_BO		= 4,
		GAWIBAWIBO_PLAYER_BAWI		= 5,

		GAWIBAWIBO_PLAYER_WIN_1		= 6,
		GAWIBAWIBO_PLAYER_WIN_2		= 7,
		GAWIBAWIBO_NPC_WIN_1		= 9,
		GAWIBAWIBO_NPC_WIN_2		= 10,
		GAWIBAWIBO_PLAYER_LOSE_1	= 12,
		GAWIBAWIBO_PLAYER_LOSE_2	= 13,
		GAWIBAWIBO_NPC_LOSE_1		= 15,
		GAWIBAWIBO_NPC_LOSE_2		= 16,

		GAWIBAWIBO_PLAYER_WAIT_1	= 18,
		GAWIBAWIBO_PLAYER_WAIT_2	= 19,

		GAWIBAWIBO_NPC_WAIT_1		= 21,
		GAWIBAWIBO_NPC_WAIT_2		= 22,
	};	

	enum ENUM_GAWIBAWIBO_STATUS		// ���� ����
	{
		GAWIBAWIBO_STATUS_NONE,
		GAWIBAWIBO_STATUS_WAIT_SELECT,		// ���� ��ٸ�����.
		GAWIBAWIBO_STATUS_SELECT_COMPLETE,	// ���� �Ϸ�.
		GAWIBAWIBO_STATUS_RESULT,			// ���� ���.
	};

	enum ENUM_GAWIBAWIBO_CALCULATE_RESULT
	{
		GAWIBAWIBO_RESULT_NONE,
		GAWIBAWIBO_RESULT_ABUSE_WIN,
		GAWIBAWIBO_RESULT_WIN,
		GAWIBAWIBO_RESULT_DRAW,
		GAWIBAWIBO_RESULT_LOSE,
		GAWIBAWIBO_RESULT_END,
	};

	InterfaceFactory	m_InterfaceFactory;

	CButton*			m_pSelectButton[m_sMaxSelectButtonNum];	//	����������  ���� ��ư

	CStatic*			m_pStcStatusIcon[m_sMaxStatus];			//	�غ��� �̹���
	CStatic*			m_pStcResult;							//	��� �̹���
	CStatic*			m_pStcCumulativeMoney;					//	�����ݾ�
	CStatic*			m_pStcAbuseNPC[m_sMaxSelectButtonNum];	//  NPC �������� �� Ȱ��ȭ
	CImageStatic*		m_pImgStcBalloon;						//  NPC ��ǳ��
	CImageStatic*		m_pImgStcCount;							//  NPC ī��Ʈ

	TSpr*				m_pSprGawiBawiBo;
	TSpr*				m_pSprResult;

	SI16				m_siSelecteIndex;						//	���� ���
	SI16				m_siStatus;								//	���¾������� ����
	CCharacterDrawing*  m_pCharDraw;							
	cltAniInfo			m_clAniInfoPlayer;
	cltAniInfo			m_clAniInfoNPC;

	SI16				m_siAniDirection;
	SI16				m_siAniTypePlayer;						// �ִϸ��̼� Ÿ��
	SI16				m_siAniTypeNPC;
	POINT				m_lnPositionPlayer;
	POINT				m_lnPositionNPC;


public:

	NGawiBawiBoDlg();
	~NGawiBawiBoDlg();

	void	Create();

	static	void CALLBACK StaticNGawiBawiBoDlgProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void	CALLBACK NGawiBawiBoDlgProc( UINT nEvent, int nControlID, CControllerObj* pControl );

	void	Action();	
	void	DrawDialogLast(SI32 ScreenRX, SI32 ScreenRY);

	void	SetStatus(SI16 siStatus);

	void	SetGiveUpEnable();
	void	SetStatusIcon();
	void	SetStatusCharacter();

	void	WaitForSelect(){m_siStatus = GAWIBAWIBO_STATUS_WAIT_SELECT;}	//	�÷��̾��� �� ������ ��ٸ�����

	void	SeleceComplete(){m_siStatus = GAWIBAWIBO_STATUS_SELECT_COMPLETE;}	//	���� �Ϸ�
	void	ResultComplete(){m_siStatus = GAWIBAWIBO_STATUS_RESULT;}	//	���� �Ϸ�
	
	void	SetIcon(SI08 siPlayer, SI08 siIconIndex);			//	������ ����

	void	SetCumulativeMoneyText(GMONEY siMoney);				//	�����ݾ� ��Ʈ�� ����
	bool	SelectedBtn(SI16 siIndex);							//	������ ��ư ����
	void	SetPlayerDraw();	
	void	SetNPCDraw();

	void	Counting(clock_t nCount);							//	ī��Ʈ ������
	void	EndCount();											//	ī��Ʈ ����

	void	DrawPlayer(SI32 ScreenRX, SI32 ScreenRY);
	void	DrawNPC(SI32 ScreenRX, SI32 ScreenRY);

	void	RandomSelect(SI32 siIndex);										//	�������� �и� ����

	void	RetMsgBox(bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen);
};
