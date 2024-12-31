
#pragma once

#include "../../InterfaceMgr/DialogController.h"

enum WARNDURABILITY_SHOW_COLOR
{
	WARNDURABILITY_SHOW_COLOR_NONE = 0
	,WARNDURABILITY_SHOW_COLOR_01
	,WARNDURABILITY_SHOW_COLOR_02
	,WARNDURABILITY_SHOW_COLOR_03
};


typedef struct _stWarnController
{
	SI32	m_siInventoryPos;	// ���� �˻��ϰ��� �ϴ� �������� �κ��丮 ��ġ
	SI32	m_siControllerID;	// �κ��丮 ��ġ�� �ش��ϴ� ��Ʈ�ѷ�
	SI32*	m_psiCompareValue;	// ������ ǰ��(ex �Ͱ���1, �Ͱ���2)�� ����� �� ������ �Ҹ� ������ ���ϱ� ����(���� ���� �������� ��Ÿ���� �Ǳ� �����̴�)
} stWarnController;


class CNWarnDurabilityDlg : public CDialogController
{

// -- Member Variable Area
private:
	InterfaceFactory m_InterfaceFactory;
protected:

public:


// -- Member Function Area
private:

protected:

public:
	CNWarnDurabilityDlg( void );
	~CNWarnDurabilityDlg( void );

	void Init();
	void Create();

	void Action();

	static void CALLBACK StaticCallBackDialogNWarnDurabilityDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
	void CALLBACK CallBackDialogNWarnDurabilityDlg( UINT nEvent, int nControlID, CControllerObj* pControl );

public:
	void SetAllControllersShowMode( bool bShowMode );
	void WarnDurabilityForAction( void );
};