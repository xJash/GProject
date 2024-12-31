#ifndef _NFather_H_
#define _NFather_H_

#include "../../InterfaceMgr/DialogController.h"
#include "../common/CommonHeader.h"
//#include "../common/Father/Father.h"

#define ADD_FATHERSUPPLYER_ALREADY	1				// �̹� ��ϵǾ� �ִ�. 
#define ADD_FATHERSUPPLYER_FULL		2				// ����ڰ� ��á��. 
#define MAX_CHILD_LIST_IN_CLIENT_NUMBER		50		// ���İ��� �ִ� ��

class CImageStatic;
class CButton;
class CComboBox;
class CListView;
class CEdit;
class CStatic;
class CList;

class CNFatherDlg : public CDialogController
{
public:

	CNFatherDlg();
	~CNFatherDlg();

	void Create();

	static void CALLBACK StaticCallBackDialogNFatherDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
	void CALLBACK CallBackDialogNFatherDlg( UINT nEvent, int nControlID, CControllerObj* pControl );

//	void Show();
//	void Hide();

	void Action();

	void DrawDialogFirst( SI32 ScreenRX, SI32 ScreenRY  );

	// ���İ��� �̸��� ���Ѵ�. 
	TCHAR* GetChildName(SI32 personid);

	// ���İ��� ����Ʈ�� ��� �����Ѵ�. 
	void DelChildList();
	void ChildSort(SI32 sisortdata[]);
	bool AddChildList(cltChildInfo* pclinfo);

	void EnableButton(CButton* pButton, TCHAR* pText, BOOL Flag = false);	// ��ư Ȱ��ȭ ��Ȱ��ȭ

	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );
	
public:

	SI32				m_siSelectedIndex;
	SI32				m_siSelectedChildID;
	bool				m_bUpdateChildListSwitch;

	cltChildInfo		clChildList[MAX_CHILD_LIST_IN_CLIENT_NUMBER];
	SI32				m_siChildListInx[MAX_CHILD_LIST_IN_CLIENT_NUMBER];	// ���� ����Ʈ ������ �� ����Ʈ ����Ÿ(��ġ)

	CButton*			m_pButton[9];
	CStatic*			m_pStatic[3];
	CList*				m_pList;	

	CButton*		m_pResidentInviteButton;

};

#endif