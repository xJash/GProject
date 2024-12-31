#ifndef _NMAKECHAR_H_
#define _NMAKECHAR_H_

#include "../../InterfaceMgr/DialogController.h"
#include <Graphic.h>
#include <Graphic_Capsule.h>


class CImageStatic;
class CButton;
class CComboBox;
class CListView;
class CEdit;
class CStatic;
class CList;

#define SELECT_CHAR1 0	// �Ϻ���
#define SELECT_CHAR2 1  // �Ϻ���
#define SELECT_CHAR3 2  // ���糲
#define SELECT_CHAR4 3  // ���翩

class CMakeCharInfo
{
public :
	SI32 siUnique;
	SI32 siKind;
	SI32 siStartIndex;
	SI32 siIndexNum;
};

class CNMakeCharDlg : public CDialogController
{
public:

	CNMakeCharDlg();
	~CNMakeCharDlg();

	void Create();

	static void CALLBACK StaticCallBackDialogNMakeCharDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
	void CALLBACK CallBackDialogNMakeCharDlg( UINT nEvent, int nControlID, CControllerObj* pControl );

	void DrawDialogFirst( SI32 ScreenRX, SI32 ScreenRY  );
	void DrawDialogLast( SI32 ScreenRX, SI32 ScreenRY  );

	void ShowCharMakeWindow(bool bShow, SI16 fontindex = 0 );

	void SelectSlot(SI32 Slot);

	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );
	void Action();

private:
	SI32            m_siChar_flag; // ĳ���� ������ ���� �÷���
	SI32			m_siSelectedSlot;

	DWORD			m_dwStratClock;
	DWORD			m_dwLastClock;

	bool			m_bShowCharMakeWindow;
		
	CEdit*			m_pEditName;
	CButton*		m_pButton[3]; // 0 : ����� 1 : ��� 2 : �ݱ�
	CImageStatic*	m_pStatic[5]; // 0 : ū �׸� 1 : ���� �׸� 2 : ���� 3 : ���� 4 : ����
	
	CStatic*		m_pStaticCharname;

	CButton*		m_pButton_Char[4];
};

#endif

