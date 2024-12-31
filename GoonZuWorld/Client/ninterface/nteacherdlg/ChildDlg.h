#ifndef _NChild_H_
#define _NChild_H_

#include "../../InterfaceMgr/DialogController.h"
#include "../common/CommonHeader.h"

class CImageStatic;
class CButton;
class CComboBox;
class CListView;
class CEdit;
class CStatic;
class CList;

#define ADD_FATHERSUPPLYER_ALREADY	1				// �̹� ��ϵǾ� �ִ�. 
#define ADD_FATHERSUPPLYER_FULL		2				// ����ڰ� ��á��. 
#define MAX_CHILD_LIST_IN_CLIENT_NUMBER		50		// ���İ��� �ִ� ��

class CNChildDlg : public CDialogController
{
public:

	CNChildDlg();
	~CNChildDlg();

	void Create();

	static void CALLBACK StaticCallBackDialogNChildDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
	void CALLBACK CallBackDialogNChildDlg( UINT nEvent, int nControlID, CControllerObj* pControl );

//	void Show();
//	void Hide();

	void Action();

	void DrawDialogFirst( SI32 ScreenRX, SI32 ScreenRY  );

	// ���´��� �����ش�. 
	void ShowFatherName();
	// ���´� ����� ����� �����ش�. 
	void ShowFatherList();

	// ���´� ��� ��û�ڸ� �߰��Ѵ�. 
	bool AddApplyer(cltFatherApplyerInfo* pclinfo, SI32* preturnval);
	// ���´� ��� ��û�ڸ� ���� �Ѵ�. 
	bool DeleteApplyer(SI32 personid);
	// Ư�� ����ڰ� ����Ʈ�� �����ϴ°�. 
	bool IsExist(SI32 personid);

	void EnableButton(CButton* pButton, BOOL Flag);

	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );

public:

	SI32			m_siSelectedIndex;	// ���¸�Ͽ��� ���õ� �ε���
	cltFatherApplyerInfo clApplyerList[MAX_FATHER_APPLYER_LIST_NUMBER];
	SI32 m_siFatherApplyInx[MAX_FATHER_APPLYER_LIST_NUMBER]; // ���� ��û�� ����Ʈ ������ ���� �ε���

	bool			m_bUpdateFatherSwitch;
	bool			m_bUpdateFatherApplyerListSwitch;

	CButton*		m_pButton[6];
	CStatic*		m_pStatic[4];
	CList*			m_pList;	
	CEdit*			m_pEdit;

};

#endif