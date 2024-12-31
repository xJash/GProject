//*************************************************************************
//	2008-1-23 
//	Ȳ���� 
//	ĳ���� ���� ����â���� ����� �󼼴ɷ�ġ ����â.
//	
//	
//*************************************************************************

#ifndef _NCHAR_ABILITY_DATAIL_DLG_H_
#define _NCHAR_ABILITY_DATAIL_DLG_H_

#pragma once

#include "Char\CharManager\CharManager.h"

#include "../../Client/client.h"
#include "../../InterfaceMgr/DialogController.h"
#include "../../InterfaceMgr/InterfaceFile.h"
#include "../../CommonLogic/CommonLogic.h"

#include "../../InterfaceMgr/Interface/ListView.h"

class NCharAbilityDatailDlg : public CDialogController
{
public:
	
	NCharAbilityDatailDlg();
	~NCharAbilityDatailDlg();

	void	Create();
	void	SetExplain( void );
	void	SetAbilityInfo( void );
	
	static void CALLBACK StaticNCharAbilityDatailDlgProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
		   void CALLBACK NCharAbilityDatailDlgProc(UINT nEvent, int nControlID, CControllerObj* pControl);

	void TextMsg(SI32 _MsgType);

private:
	InterfaceFactory	m_InterfaceFactory;

    TCHAR				m_szBuffer[64];				// ������ �Ҽ��� ��ȯ�Ͽ� ���ڿ��� ���� �� ����Ѵ�.
};

#endif