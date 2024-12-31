// CNSelectItemCountDlg - 06/07/14[����]
// �κ��丮�� ������ �и�, ������ ��ӽ� ������ ���� ���� ���̾�α�

#pragma once

#include "../../InterfaceMgr/DialogController.h"

#define COUNT_MODE_SPLITITEM		1
#define COUNT_MODE_DROPITEM			2
#define COUNT_MODE_PRESENTITEM		3

class CNSelectItemCountDlg : public CDialogController
{
public:
	CNSelectItemCountDlg();
	~CNSelectItemCountDlg();

	void Create();

	static void CALLBACK StaticCallBackDialogNSelectItemCount( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void CALLBACK CallBackDialogNSelectItemCount( UINT nEvent, int nControlID, CControllerObj* pControl );

	CStatic*		m_pStaticTotal;
	CEdit*			m_pEditTotal;
	CStatic*		m_pStaticInput;
	CEdit*			m_pEditInput;
	CButton*		m_pButtonSubmit;
	CButton*		m_pButtonCancel;

	SI32			m_siSelectedItemCount;
	SI32			m_siSelectedItemIndex;

	SI16			m_siMode;

	void	SetCountMode( SI16 mode );
	void	SplitItem();
	void	DropItem();
	void	PresentItem();

	void SetSelectedItemIndex(SI32 siSelectedItemIndex);
private:

};