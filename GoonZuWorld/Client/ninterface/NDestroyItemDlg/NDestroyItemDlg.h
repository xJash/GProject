//----------------------------------------------------------------------------
//
//	�������� ���� ����߷����� �̸��� �޾Ƽ� ���� �޼����� ������ ���̾�α�
//
//	2008.05.08 �ռ���
//
//----------------------------------------------------------------------------
#ifndef _NDESTROYITEMDLG_H
#define _NDESTROYITEMDLG_H

#pragma once

#include "Char\CharManager\CharManager.h"

#include "../../Client/client.h"
#include "../../InterfaceMgr/DialogController.h"
#include "../../InterfaceMgr/InterfaceFile.h"
#include "../../CommonLogic/CommonLogic.h"
#include "../../InterfaceMgr/InterfaceMgr.h"


class NDestroyItemDlg : public CDialogController
{
public:
	NDestroyItemDlg();
	~NDestroyItemDlg();

	void Create( void );

	static void CALLBACK StaticNDestroyItemDlgProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void CALLBACK NNDestroyItemDlgProc(UINT nEvent, int nControlID, CControllerObj* pControl);
	void Action(void);
	void SetDropItem( SI32 ItemIndex , cltItem dropitem );
private:
	InterfaceFactory	m_InterfaceFactory;
	cltItem				*Targetitem;
	TCHAR*				pItemName; // �޾ƿ� ������ �̸�
	cltItem				dropitemtoDestroy; // �ı��� ������ ����
	TCHAR*				ItemNameToDestroy;
	SI32				DropItemIndex;
};

#endif