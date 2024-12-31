#ifndef _NTEACHER_H_
#define _NTEACHER_H_

#include "../../InterfaceMgr/DialogController.h"
//#include "../../common/Father/Father.h"

class CImageStatic;
class CButton;
class CComboBox;
class CListView;
class CEdit;
class CStatic;
class CList;

class CNFatherDlg;
class CNChildDlg;

class CNTeacherDlg : public CDialogController
{
public:

	CNTeacherDlg();
	~CNTeacherDlg();

	void Create(bool bTeacherMode);

	static void CALLBACK StaticCallBackDialogNTeacherDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
	void CALLBACK CallBackDialogNTeacherDlg( UINT nEvent, int nControlID, CControllerObj* pControl );

	void Show();
	void Hide();

	void Action();

	void DrawDialogFirst( SI32 ScreenRX, SI32 ScreenRY  );

//	void ChildSort(SI32 sisortdata[]);

//	static BOOL CALLBACK StaticDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
//	BOOL CALLBACK DlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);

//	static BOOL CALLBACK StaticDlg2Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
//	BOOL CALLBACK Dlg2Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
/*
	// ���´��� �����ش�. 
	void ShowFatherName(HWND hDlg);
	// ���´� ����� ����� �����ش�. 
	void ShowFatherList();

	// ���´� ��� ��û�ڸ� �߰��Ѵ�. 
	bool AddApplyer(cltFatherApplyerInfo* pclinfo, SI32* preturnval);
	// ���´� ��� ��û�ڸ� ���� �Ѵ�. 
	bool DeleteApplyer(SI32 personid);
	// Ư�� ����ڰ� ����Ʈ�� �����ϴ°�. 
	bool IsExist(SI32 personid);


	// ���İ��� ����Ʈ�� ���Ѵ� 
	bool AddChildList(cltChildInfo* pclinfo);

	// ���İ��� ����Ʈ�� ��� �����Ѵ�. 
	void DelChildList();

	// ���İ��� �̸��� ���Ѵ�. 
	TCHAR* GetChildName(SI32 personid);

	void Action(cltCharManager* pclCM);
*/
public:

	bool			m_bTeacherMode;

	CNFatherDlg*	m_pNFatherDlg;
	CNChildDlg*		m_pNChildDlg;
/*
	bool m_bDlgRectInitSwitch;

	bool m_bUpdateFatherSwitch;
	bool m_bUpdateFatherApplyerListSwitch;
	bool m_bUpdateChildListSwitch;

	// ���´� ��� ��û�� ���. 
	cltFatherApplyerInfo clApplyerList[MAX_FATHER_APPLYER_LIST_NUMBER];

	// ���ڴ� ����Ʈ. 
	cltChildInfo clChildList[MAX_CHILD_LIST_IN_CLIENT_NUMBER];

	SI32 m_siSelectedIndex ;								// ������ ����Ʈ ����Ÿ
	SI32 m_siFatherApplyInx[MAX_FATHER_APPLYER_LIST_NUMBER]; // ���� ��û�� ����Ʈ ������ ���� �ε���
	SI32 m_siChildListInx[MAX_CHILD_LIST_IN_CLIENT_NUMBER];	// ���� ����Ʈ ������ �� ����Ʈ ����Ÿ(��ġ)
*/

};

#endif