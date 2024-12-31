#ifndef _NINSTANTDUNGEONBOARD_H
#define _NINSTANTDUNGEONBOARD_H

#define GUILD_MARK_NUM 5	//������ ��帶ũ �ִ� ����
#define MAX_DISPLAY_PAGE_NUM	10 //��ȭ�鿡 ������ �ִ� ����

#pragma once

#include "../../Client/client.h"
#include "../../InterfaceMgr/DialogController.h"
#include "../DBManager/GameDBManager_World/DBMsg-Hunt.h"
class NInstantDungeonBoradDlg : public CDialogController
{
private:

public:
	NInstantDungeonBoradDlg();
	~NInstantDungeonBoradDlg();

	void Initialize();
	void Destroy();
	void Create();

	static void CALLBACK StaticNInstantDungeonBoradDlgProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void CALLBACK NInstantDungeonBoradDlgProc(UINT nEvent, int nControlID, CControllerObj* pControl);

	void SetListBoxRanking();
	void SetListBoxHOF();
	void ChangeListBoxRanking(HOFList *hoflist , SI16 requestpage, SI16 Maxpage );
	void ChangeListBoxHOF(HOFList *hoflist, SI16 requestpage, SI16 Maxpage);

	InterfaceFactory	m_InterfaceFactory;
	SI32				m_siRequestPage;
	SI32				m_siMaxPage;
	TSpr				m_GuildMark;
	SI32				m_MaxDisplatPage;//�������� ������ �ִ� ����
};




#endif