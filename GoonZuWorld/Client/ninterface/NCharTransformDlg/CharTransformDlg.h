#pragma once

#include "../../Client/client.h"
#include "../../InterfaceMgr/DialogController.h"

class CStatus;

/**************************************************************************************/
//
//	[�߰� : Ȳ���� 2007. 12. 20 ����â Ŭ���� �߰�.]
//
/**************************************************************************************/
class CNChartransformDlg : public CDialogController
{ 
	enum { TRANSFORM, RETMSG_USE_ITEM, RETMSG_ADD_1_DAY, RETMSG_ADD_7_DAY, RETMSG_ADD_30_DAY  };	

public:
	CNChartransformDlg();
	~CNChartransformDlg();

	void Init();
	void Destroy();
	void Create();
	void Action();

	void DrawChar( SI32 ScreenRX, SI32 ScreenRY );
	void DrawDialogLast( SI32 ScreenRX, SI32 ScreenRY  );

	void Status(void);										// �������� �����ϱ�.
	SI32 GetFindCharSlot(SI32 _kind);						// kind�� ���� ĳ���� ���� ��ȣ ���.
		
	static void CALLBACK StaticChartransformDlgProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void CALLBACK NChartransformDlgProc(UINT nEvent, int nControlID, CControllerObj* pControl);

	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );
	void Msg(SI32 MsgNum);

	void SetStatus(CStatus& _Status);
	TCHAR* CNChartransformDlg::GetWeaponEffectExplain( void );
	

private:
	InterfaceFactory	m_InterfaceFactory;
	SI32				m_siCharKind;

	cltAniInfo			m_claniinfo;
	SI32				Animation;
	SI32				siDirection;
	SI32				Font;

	SI32				realxsize;
	SI32				realysize;

	SI32				xstart;
	SI32				ystart;

	TSpr				m_Spr;
};

// ���� ����.
class CStatus
{
public:
	SI32	Dex;
	SI32	Str;
	SI32	Vit;
	SI32	Mag;
	SI32	m_AC;
	
	CStatus()
	{
		ZeroMemory( this, sizeof( CStatus ) );
	}
	~CStatus()
	{
		
	}
};