// [����] ���� UI : Pannel (�ɸ��� �⺻����)
#pragma once

#include "../../InterfaceMgr/DialogController.h"
#include "../../InterfaceMgr/InterfaceFile.h"
#include "../../NLib/NUpdateTimer.h"


class CNPannel_CharStatusDlg : public CDialogController
{
enum CHARSTATUS_VARIABLE
{
	CHARSTATUS_HP_NUM		= 0
	,CHARSTATUS_MP_NUM		= 4
	,CHARSTATUS_EXP_NUM		= 8

	// �������� ���� ����
	,CHARSTATUS_BAR_WIDTH		= 144
	// HP ������ ������ġ
	,CHARSTATUS_HP_START_X		= 96
	,CHARSTATUS_HP_START_Y		= 40
	// MP ������ ������ġ
	,CHARSTATUS_MP_START_X		= 96
	,CHARSTATUS_MP_START_Y		= 52
	// EXP ������ ������ġ
	,CHARSTATUS_EXP_START_X		= 96
	,CHARSTATUS_EXP_START_Y		= 64
	// ����� ������ġ
	,CHARSTATUS_HUNGRY_START_X	= 117
	,CHARSTATUS_HUNGRY_START_Y	= 7
	// ���� ����� �˸��� ũ��
	,CHARSTATUS_HUNGRY_WIDTH	= 8

	// �ȿ��� ���� �ؽ�Ʈ ���� ������
	,CHARSTATUS_BUF_SIZE		= 128

};

public:
	CNPannel_CharStatusDlg();
	~CNPannel_CharStatusDlg();

	void Create();

	static void CALLBACK StaticPannel_CharStatusDlgProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void CALLBACK NPannel_CharStatusDlgProc(UINT nEvent, int nControlID, CControllerObj* pControl);

	void DrawDialogLast( SI32 ScreenRX, SI32 ScreenRY );
	void DrawDialogFirst( SI32 ScreenRX, SI32 ScreenRY );

	void Show();
	void Hide();


private:
	void DrawCharStatus( SI32 ScreenRX, SI32 ScreenRY );// ĳ���� ���� �׸��� ó�� �Լ�
	void DrawHungry( SI32 ScreenRX, SI32 ScreenRY );	// ����� �׸��� ó�� �Լ�
	void WriteCharStatus( void );						// �ɸ��� ���� �ؽ�Ʈ ���� ó�� �Լ�
	void WriteToolTip( void );							// ��ǳ�� ó�� �Լ�

	bool GetToolTipText( TCHAR* pszToolTip );			// ��ǳ�� �ؽ�Ʈ�� ���� �´�
	SI32 GetHealthTextNum( void );						// �ǰ����� ���� �ؽ�Ʈ�޴��� ��ȣ�� ���� �´�

private:
	InterfaceFactory	m_InterfaceFactory;

	TSpr				m_sprGage;
	TSpr				m_sprHungry;

	SI32				m_siHungryStatus;

	NUpdateTimer		m_kUpdateTimer_DrawToolTip;

};
