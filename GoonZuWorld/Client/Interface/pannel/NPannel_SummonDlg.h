// [����] ���� UI : Pannel (��ȯ������)
#pragma once

#include "../../InterfaceMgr/DialogController.h"
#include "../../InterfaceMgr/InterfaceFile.h"

class cltCharClient;

class CNPannel_SummonDlg : public CDialogController
{
enum SUMMONDLG_VARIABLE
{
	SUMMONDLG_HP_NUM			= 0
	,SUMMONDLG_MP_NUM		
	,SUMMONDLG_EXP_NUM		
	,SUMMONDLG_STAMINA_NUM	

	,SUMMONDLG_BAR_WIDTH		= 126

	,SUMMONDLG_HP_START_X		= 5
	,SUMMONDLG_HP_START_Y		= 48

	,SUMMONDLG_MP_START_X		= 5
	,SUMMONDLG_MP_START_Y		= 53

	,SUMMONDLG_EXP_START_X		= 5
	,SUMMONDLG_EXP_START_Y		= 58

	,SUMMONDLG_STAMINA_START_X	= 5
	,SUMMONDLG_STAMINA_START_Y	= 68

	,SUMMONDLG_PORTRAIT_START_X	= 7
	,SUMMONDLG_PORTRAIT_START_Y	= 7

	,SUMMONDLG_PORTRAIT_WIDTH	= 42

	,SUMMONDLG_MAX_PORTRAIT		= 2
	,BASE_BAR_WIDTH		= 200		// ���� �� ����(�������� �ٿ� �ܺ��������̽� ���� ������ �Ǵ� ����)
};



public:
	CNPannel_SummonDlg();
	~CNPannel_SummonDlg();

	void Create();

	static void CALLBACK StaticPannel_SummonDlgProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void CALLBACK NPannel_SummonDlgProc(UINT nEvent, int nControlID, CControllerObj* pControl);


	void Action();

	void Show();
	void Hide();

	void DrawDialogLast( SI32 ScreenRX, SI32 ScreenRY );

	bool GetShowDialog() { return m_bShowDialog; }

	// ���� ��Ÿ���� ǥ���Ѵ�
	void DrawMagicCoolTime( cltCharClient* pclParent, SI32 ScreenRX, SI32 ScreenRY );
	void SetMagicCoolTime( SI32 siMagicCoolTime );

private:
	InterfaceFactory	m_InterfaceFactory;
	TSpr				m_sprGage;
	TSpr				m_sprSummonPortrait;
	TSpr				m_sprSummonStatus;

	TSpr				m_sprTransformBar;	
	TSpr				m_sprTGage2;		


	bool				m_bShowDialog;		// �� ���̾�αװ� �������� �Ⱥ�������

	// ��ȯ�� ���� ��Ÿ�� ǥ�ÿ�
	TSpr				m_sprMagicCoolTime;
	SI32				m_siMagicCoolTime;
	SI32				m_siMagicCoolTime_Start;
	SI32				m_siSummonIndex;

};
