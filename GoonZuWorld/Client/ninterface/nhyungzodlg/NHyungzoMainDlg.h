#pragma once 

#include "../../InterfaceMgr/DialogController.h"

class CImageStatic;
class CButton;
class CComboBox;
class CListView;
class CEdit;
class CStatic;
class CList;
class CRadioButton;
class COutLine;

class CNHyungzoMainDlg : public CDialogController
{
public:

	CNHyungzoMainDlg();
	~CNHyungzoMainDlg();

	void Create( CControllerMgr *pParent );
	void Action();

	void Show();
	void Hide();

	static void CALLBACK StaticCallBackDialogNHyungzoMainDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
	void CALLBACK CallBackDialogNHyungzoMainDlg( UINT nEvent, int nControlID, CControllerObj* pControl );

	void SetHyungzoMain(SI16 stealnum,SI16 suspecttime,SI16 prisontime,	SI16 prisonerpenalty);
	void SetEnableButton(BOOL flag);

	BOOL HyungzoMainCheck();

	inline SI16 GetStealNum()			{ return m_siStealNum;			}
	inline SI16 GetSuspectTime()		{ return m_siSuspectTime;		}
	inline SI16 GetPrisonTime()			{ return m_siPrisonTime;		}
	inline SI16 GetPrisonerPenalty()	{ return m_siPrisonerPenalty;	}

private:

	SI16 m_siStealNum; // ������ ��ƿ ���� Ƚ��
	SI16 m_siSuspectTime; // ��ũ�� ���α׷� üũ �ð�
	SI16 m_siPrisonTime; // ��ũ�� ����� ���� �ð�
	SI16 m_siPrisonerPenalty; // ��ũ�� ����� ���� ����

	CStatic*	m_pStatic[9];
	CEdit*		m_pEdit[3];
	CButton*	m_pButton[2];
	CRadioButton*	m_pRadio[5];
	COutLine*	m_pOutLine;
};