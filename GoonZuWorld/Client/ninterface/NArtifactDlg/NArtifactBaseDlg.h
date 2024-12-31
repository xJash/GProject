//------------------------------------------------------------------------------
//
//	��Ƽ��Ʈ â.
//
//	2008. 2. 26
//	Ȳ����
//
//------------------------------------------------------------------------------
#ifndef _NARTIFACT_BASE_DLG_
#define _NARTIFACT_BASE_DLG_

#pragma once

#include "Char\CharManager\CharManager.h"

#include "../../Client/client.h"
#include "../../InterfaceMgr/DialogController.h"
#include "../../InterfaceMgr/InterfaceFile.h"
#include "../../CommonLogic/CommonLogic.h"

#include "../Client/ninterface/NArtifactDlg/NArtifactMixtureDlg.h"
#include "../Client/ninterface/NArtifactDlg/NArtifactSlotCreateDlg.h"
#include "../Client/ninterface/NArtifactDlg/NArtifactRestoreDlg.h"
#include "../Client/ninterface/NArtifactDlg/NArtifactRemoveDlg.h"

class NArtifactBaseDlg : public CDialogController
{
public: 
	enum{ MIX, CREATE, RESTORE, REMOVE };

public:
	NArtifactBaseDlg();
	~NArtifactBaseDlg();

	void Create( void );
	
	static void CALLBACK StaticNArtifactBaseDlgProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
		   void CALLBACK NArtifactBaseDlgProc(UINT nEvent, int nControlID, CControllerObj* pControl);


    void ButtonSetting( SI32 _ButtonKind );		// ���� ��ư�� �ش��ϴ°͸� ��ư���� ����ϱ�.
	void EquipmentListViewMsgProc( CListView* pListView, SI16 ItemPos, UINT nEvent );	
	void SetPotrait( void );															// �ʻ�ȭ �׸���
	void SetExplain(SI32 _siType);
	bool IsGage(void);																	// ���� ������ �̹����� Ȱ��ȭ ���ִ� â�� �ִٸ�.
	
	void Clear( void );

	void Action(void);
	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );

public:
	NArtifactMixtureDlg		m_NArtifactMixtureDlg;
	NArtifactSlotCreateDlg	m_NArtifactSlotCreateDlg;
	NArtifactRestoreDlg		m_NArtifactRestoreDlg;
	NArtifactRemoveDlg		m_NArtifactRemoveDlg;

private:
	InterfaceFactory	m_InterfaceFactory;
};

#endif