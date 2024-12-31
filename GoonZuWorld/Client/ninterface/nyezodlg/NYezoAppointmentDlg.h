#pragma once 

#include "../../InterfaceMgr/DialogController.h"
#include "../common/CommonHeader.h"
#include "../Server/Minister/MinisterBase.h"
#include "../Server/Minister/Minister-Yezo.h"


class CImageStatic;
class CButton;
class CComboBox;
class CListView;
class CEdit;
class CStatic;
class CList;

class CNYezoAppointmentDlg : public CDialogController
{
public:

	CNYezoAppointmentDlg();
	~CNYezoAppointmentDlg();

	void Create();
	void Action();

	void Show();
	void Hide();

	static void CALLBACK StaticCallBackDialogNYezoAppointmentDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
	void CALLBACK CallBackDialogNYezoAppointmentDlg( UINT nEvent, int nControlID, CControllerObj* pControl );
	
	bool SetListDlg(SI32 index);
	void ShowListDlg(YezoAngelList yezoangellist []);

	void EnableButton(CButton* pButton, BOOL Flag);	// ��ư Ȱ��ȭ ��Ȱ��ȭ

private:


	YezoAngelList	m_stYezoAngelList[MAX_YEZO_ANGELLIST];

	SI32 m_siSelectListInx;
	SI32 m_siListIndex[MAX_YEZO_ANGELLIST];

	SI32 m_siSelectList;

	CList*		m_pList;
	CButton*	m_pButton[3];


};