//*************************************************************************
//
//	Ȳ���� 2008. 1. 23 => ���� ���� ���� �� ���� ��Ȳ ����â ����.
//
//*************************************************************************

#ifndef _NSPACE_BOX_DLG_H_
#define _NSPACE_BOX_DLG_H_

#pragma once

#include "Char\CharManager\CharManager.h"

#include "../../Client/client.h"
#include "../../InterfaceMgr/DialogController.h"
#include "../../InterfaceMgr/InterfaceFile.h"
#include "../../CommonLogic/CommonLogic.h"

#include "../../InterfaceMgr/Interface/ListView.h"

class CNSpaceBoxDlg : public CDialogController
{
public:
	enum{ SPACE_BOX, TREASURE_BOX };
	enum{	
			MSG_EXPLAIN,					// ����.
			MSG_TIME_OVER_BOX,				// �ð� �ʰ��� ��� �Ұ�.			
			MSG_FULL_BOX,					// ���ڰ� ������.
			MSG_NO_MOVE_ITEM_SELECT,		// �̵��� �������� ���� �ȵ�.
			MSG_OVER_COUNT,					// �̵��ϴ� �������� ������ ���� ���� �ʰ�.
			MSG_GACHA_ITEM_DIFFICULT_BOX,	// ��í �������� �ִ� �ڽ��� �ƴ�.
			MSG_NOMAL_ITEM_DIFFICULT_BOX,	// �Ϲ� �������� �ִ� �ڽ��� �ƴ�.
			MSG_ITEM_MOVE_COUNT_RANGE,		// ������ �̵� ������ ������ �����.
		};

	CNSpaceBoxDlg();
	~CNSpaceBoxDlg();

	void Create();
	void Destroy();
	void DrawDialogLast( SI32 ScreenRX, SI32 ScreenRY  );

	static void CALLBACK StaticSpaceBoxDlgProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
		   void CALLBACK SpaceBoxDlgProc(UINT nEvent, int nControlID, CControllerObj* pControl);
  

    void SetMyListView(void);
	void SetSpaceBoxListView(void);
	void SetTreasureBoxListView(void);
	void SetRemainTime(void);

	void TextMsg(SI32 _MsgType);

private:
	InterfaceFactory	m_InterfaceFactory;

	cltItem				m_clUserItem[ MAX_ITEM_PER_PERSON ];
	
	SI32				m_siKeepPos;
	SI32				m_siRecoveryPos;
	bool				m_BoxViewType;

	TSpr				m_Spr;

	CButton*			m_pKeepButton;
};

#endif