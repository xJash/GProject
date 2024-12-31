// [����] ���� UI : Pannel (�ɸ��� �⺻����)
#pragma once

#include "../../InterfaceMgr/DialogController.h"
#include "../../InterfaceMgr/InterfaceFile.h"
#include "../../Server/ServerEvent/ServerEvent-InstanceMapInfo.h"



class NServerInstanceMapBounusDlg : public CDialogController
{
	enum{ DATA_NUM = 4,	};
	enum{ FIGURE, ROLL_PAPER, IMAGE_NUM};
	enum{ 
			VIEW_TYPE_FIGURE,				// �̺�Ʈ�� �δ��� ����ܰ�� ���� �������� ���ʽ� �˸�.
			VIEW_TYPE_DAILY_RANK_1,			// �Ϸ� ��ŷ 1���� �˷���.
			VIEW_TYPE_OPEN_THE_GATE,		// ���� �̺�Ʈ �δ����� ����
			VIEW_TYPE_MESSAGE,				// ��
		};


public:
	NServerInstanceMapBounusDlg();
	~NServerInstanceMapBounusDlg();

	void Create(void);
	void Action(void);
	void DrawDialogFirst( SI32 ScreenRX, SI32 ScreenRY );
	void DrawDialogLast( SI32 ScreenRX, SI32 ScreenRY );

	void SetIstanceMapStepCount(SI16* pData);
	void SetDailyBestServerNotice(void);
	void SetGateState( bool bGateMode );
	void SetCharMessage( TCHAR* pszMessage );
	void SetMessage( SI32 _siTextNum );

	static void CALLBACK StaticServerInstanceMapBounusDlgProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
		   void CALLBACK NServerInstanceMapBounusDlgProc(UINT nEvent, int nControlID, CControllerObj* pControl);

private:
	InterfaceFactory	m_InterfaceFactory;

	SI16				m_siData[DATA_NUM];
	DWORD				m_dwOpenTickCount;
	SI32				m_RollPaperSize;

	TSpr				m_Spr[IMAGE_NUM];

    SI16				m_siViewType;
};
