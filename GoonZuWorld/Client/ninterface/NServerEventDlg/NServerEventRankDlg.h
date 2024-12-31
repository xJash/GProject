//*************************************************************************
//
//	Ȳ���� 2008. 1. 23 => ���� ���� ���� �� ���� ��Ȳ ����â ����.
//
//*************************************************************************

#ifndef _NSERVER_EVENT_RANK_H_
#define _NSERVER_EVENT_RANK_H_

#pragma once

#include "Char\CharManager\CharManager.h"

#include "../../Client/client.h"
#include "../../InterfaceMgr/DialogController.h"
#include "../../InterfaceMgr/InterfaceFile.h"
#include "../../CommonLogic/CommonLogic.h"

#include "../../InterfaceMgr/Interface/ListView.h"
#include "../../Server/ServerEvent/ServerEvent_Manager.h"

#define SAFE_POINTER(p) if(NULL == p) return;

class NServerEventRankDlg : public CDialogController
{
public:
	enum{ SERVER_RANK, PERSONAL_RANK, SERVER_DAILRY_RANK };
	enum{ SIZE_BIG, SIZE_SMALL };

public:
	
	NServerEventRankDlg();
	~NServerEventRankDlg();

	void		Create();
	void		ButtonSetting( SI32 _ButtonKind );
	void		SetServerEventRankInfo(CNServerEvent_Rank_Record*		_pRankInfo);
	void		SetServerEventServerInfo(CNServerRankInfo*				_pRankInfo);
	void		SetServerEventDailyServerInfo(CNServerDailyRankInfo*	_pRankInfo);
	void		SetServerEventPersonalInfo(CNPersonalRankInfo*			_pRankInfo);

	void		ChangeRankList(SI32 _siType);		// ���̺� ���� ����.
	void		SetChangeRankList(SI32 _siType);	// ���̺� ���� ���� �� �ش� ���� ����. 
	void		SizeChange(bool _SizeType);			// 

	static void CALLBACK StaticNServerEventRankDlgProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
		   void CALLBACK NNServerEventRankDlgProc(UINT nEvent, int nControlID, CControllerObj* pControl);

private:
	InterfaceFactory			m_InterfaceFactory;

	CNServerEvent_Rank_Record	m_clServerEvent_Rank_Record;
	SI32						m_PushButtonIndex;						// ���� ���� ��ư�� �ε��� ��ȣ.
};

#endif