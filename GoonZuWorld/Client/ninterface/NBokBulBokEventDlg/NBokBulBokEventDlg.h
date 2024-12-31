//==========================================================================
// ����: ���Һ� �̴ϰ���
// ����ġ: Switch_BokBulBok
// ����: 
// �ۼ���: 2009.08.03
// �ۼ���: ������
//==========================================================================
#pragma once

#include "../../Client/Client.h"
#include "../../InterfaceMgr/DialogController.h"
#include "MsgType-System.h"

enum GameLocation
	{
		TOTAL_GAME_FIELD = 4,
	};

class NBokBulBokEventDlg: public CDialogController
{
public:

	NBokBulBokEventDlg();
	~NBokBulBokEventDlg();

	void init();
	
	void Create();
	void Destroy();
	void Action();
	void Show_FirstMessageDlg(GMONEY siTotalMoney);

	static void CALLBACK StaticNBokBulBok_JoinDlgProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl );
		   void CALLBACK NBokBulBok_InfoDlgProc( UINT nEvent, int nControlID, CControllerObj* pControl );

	//void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );

public:	
	void CheckAllMapUse(); // ���� ��� �ʿ��� ������ ���� �̿� ������ üũ �Ѵ�.
	void ShowWaitingPlayersList(); // ����� ��� ����Ʈ �˾�.
	
private:
	InterfaceFactory	m_InterfaceFactory;
};




