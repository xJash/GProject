/* ==========================================================================
Ŭ���� :		CNGachaDlgNew

�ۼ��� :		07/04/11
�ۼ��� :		�迵��

������� :		����(�̱�) �ý��� �������̽�

�����۾� :		
========================================================================*/
 
#pragma once

#include "../../Client/client.h"
#include "../../InterfaceMgr/DialogController.h"
#include "../../server/GachaManager/GachaManager.h"

#define ANIMATION_FISH_NUM		24		// ����     �ִϸ��̼� �̹��� ��.
#define ANIMATION_OPENBOX_NUM	 8		// ���ڿ��� �ִϸ��̼� �̹��� ��.
#define SELECT_FISH_NUM			 5		// ���� ������ ����� ��.

class CNOpenBoxDlg : public CDialogController
{
public:
	enum { NONE, ANISTEP_FISH, ANISTEP_OPENBOX };

public:

	CNOpenBoxDlg();
	~CNOpenBoxDlg();

	void Init();

	void Create();
	void Destroy();

	void DrawDialogFirst(SI32 ScreenRX, SI32 ScreenRY );
	void DrawDialogLast(SI32 ScreenRX, SI32 ScreenRY );

	static void CALLBACK StaticNOpenBoxDlgProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
		   void CALLBACK NOpenBoxDlgProc( UINT nEvent, int nControlID, CControllerObj* pControl );
	
	void Action();	

	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );

public:
	bool CheckHaveKey( SI32 GachaUseKeyKind );
	void SetGachaUseKeyKind( SI32 _siGachaUseKeyKind );
	void SetCarryOverInfo( SI32 siGachaUseKeyKind, SI32 siSelectGachaProductIndex, SI32 siSelectGachaProductUnique );

private:
	InterfaceFactory	m_InterfaceFactory;
	SI32				m_siFontIndex;

	DWORD				m_siFrameTime[ANIMATION_FISH_NUM];	// ������ �̹����� ������ �ð�.
	DWORD				m_dwPrevTime;						// �ִϸ��̼� �ϴ� �̹����� ���� �ð�.

	SI32				m_siGachaUseKeyKind;				// � ���踦 ����ϴ���
	SI32				m_siAniStep;						// �ִϸ��̼� �ܰ�.(����, ���ڿ���)
	bool				m_bFishClick;						// ����⸦ �����ߴ°�?

	// Switch_CarryOverGacha On�϶� ����
	SI32				m_siSelectGachaProductIndex;		// �ʱⰪ�� -1�̿�����
	SI32				m_siSelectGachaProductUnique;		// ��í ������ ����ũ
};
 