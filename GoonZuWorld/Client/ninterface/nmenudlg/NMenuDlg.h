#ifndef _NMENUDLG_H_
#define _NMENUDLG_H_

#include "../../InterfaceMgr/DialogController.h"

class CList;

class CNMenuDlg : public CDialogController
{
public:
	CNMenuDlg();
	~CNMenuDlg();

	void Create();

	static void CALLBACK StaticCallBackDialogNMenu( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
	void CALLBACK CallBackDialogNMenu( UINT nEvent, int nControlID, CControllerObj* pControl );

	void Set( SI16 Index );

	void Execute( SI16 Param );

	void ClearFocus();
	void SetFocus( bool Focus );

	void SetPosion(SI32 id, SI32 mode = 0);	// id�� ���̾�α� id , mode�� 0�̸� 1024ȭ�鿡�� ���� 1�̸� ������

private:
	CList	*m_pList;
	SI16	m_siSelectedMenuIndex;

};

#endif