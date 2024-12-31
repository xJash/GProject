#pragma once

#include "../../Client/client.h"
#include "../../InterfaceMgr/DialogController.h"
/*--------------------------------------------------------------------------------------
[�߰� : Ȳ���� 2007. 11. 20 ũ�������� ����Ʈ Ŭ���� �߰�.]
 

--------------------------------------------------------------------------------------*/
class CNChristmasQuestDlg : public CDialogController
{ 
public:
	CNChristmasQuestDlg();
	~CNChristmasQuestDlg();

	void Init();
	void Destroy();

	void Create();

	static	void CALLBACK StaticChristmasQuestListDlgProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
			void CALLBACK NChristmasQuestListDlgProc(UINT nEvent, int nControlID, CControllerObj* pControl);
	//void Action();

	InterfaceFactory	m_InterfaceFactory;

	SI32 m_siSelectedIndex;
	
	void StartChristmasQuest();
};