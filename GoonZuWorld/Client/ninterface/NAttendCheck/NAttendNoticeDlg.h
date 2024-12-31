// [����] �⼮üũ

#pragma once

#include "../../InterfaceMgr/DialogController.h"

class CEdit;
class CButton;


class CNAttendNoticeDlg : public CDialogController
{

	enum ATTENDNOTICE_EDIT
	{
		ATTENDNOTICE_EDIT_NOTICE		= 0		// ���� â ����
		,ATTENDNOTICE_EDIT_INFORMATION			// ���� ���� ����
		
		// �� ���� �߰��� �ּ���
		,ATTENDNOTICE_EDIT_MAX
	};

	enum ATTENDNOTICE_BUTTON
	{
		ATTENDNOTICE_BUTTON_STAMP		= 0		// �⼮ ���� ���
		,ATTENDNOTICE_BUTTON_CANCEL				// �⼮���� �ʱ�

		// �� ���� �߰��� �ּ���
		,ATTENDNOTICE_BUTTON_MAX
	};

public:
	CNAttendNoticeDlg();
	~CNAttendNoticeDlg();

	void Init();
	void Destroy();

	void Create();
	void Action();

	void Show( bool bShow );

	static void CALLBACK StaticAttendNoticeDlgProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void CALLBACK NAttendNoticeDlgProc(UINT nEvent, int nControlID, CControllerObj* pControl);

public:
	void SetInfo( SI16 siAttendenceDay, SI16 siNextRewardDay );
	

private:
	CEdit*		m_pEdit[ATTENDNOTICE_EDIT_MAX];
	CButton*	m_pButton[ATTENDNOTICE_BUTTON_MAX];

	SI16		m_siAttendenceDays;
	SI16		m_siNextRewardDays;
};

