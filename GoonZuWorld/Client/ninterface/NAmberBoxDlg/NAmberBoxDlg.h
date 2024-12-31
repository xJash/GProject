#ifndef _NAMBERBOXDLG_H_
#define _NAMBERBOXDLG_H_

#include "../Client/client.h"
#include "../Common/Util/Util.h"
#include "../../InterfaceMgr/DialogController.h"
#include "../../ninterface/NAmberBoxDlg/NAmberBoxDlg.h"

//#define BOX_ITEM_NUM			48	// �ڽ����� ���ü� �ִ� �������� ����.
//#define SELECT_ITEM_LIST_NUM	3	// ���õǴ� �������� ����.

class CNAmberBoxDlg : public CDialogController
{
public:
	CNAmberBoxDlg();
	~CNAmberBoxDlg();

	void Create();
	void DrawDialogFirst( SI32 ScreenRX, SI32 ScreenRY  );
	void DrawDialogLast( SI32 ScreenRX, SI32 ScreenRY  );
	
	static void CALLBACK StaticNAmberBoxDlgProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
		   void CALLBACK NAmberBoxDlgProc( UINT nEvent, int nControlID, CControllerObj* pControl );

public:
	void SetItemList( SI32* _psiItemList, SI32 _siItemNum, SI16 _siUseItemUnique );	// ���ڸ� ���� ������ �������� ������ ����Ʈ�� �����ش�.
	void SelectItem( void );																	// ȣ�ڻ��ڿ��� ������ ������ ����.
	void SetSelectItemList( AmberboxSelectItemInfo* pclAmberboxSelectItemInfo );				// Ŭ�� �� ���� �� ������ ����.
	void SetSelectItemListClear( );																// ������ �������� ��� ����.
	bool IsSelectItem( void );																	// 

	void SendMsgSelectItemAdd(SI32 _siSlotIndex);												// ������ ��� �ε����� �������� Ŭ���ߴ��� �˸�.
	void SendMsgSelectItemGet(SI32 _siSlotIndex);												// ������ ��� �ε����� �������� ȹ�� �Ұ��� �˸�.
	void Mix();																					// �簢���� �����̴� ���� ���´�.
	void ClickSlot(SI32 _siSlotIndex);

private:
	bool					m_bInit;															// DB���� ���� ������ �������� ����Ʈ�� �޾Ҵ°�?
	
	InterfaceFactory		m_InterfaceFactory;

	AmberboxSelectItemInfo	m_clAmberboxSelectItemInfo[AMBER_BOX_SELECT_ITEM_LIST_NUM];

	SI32					m_bClickSlot;														// Ŭ����ư ������.
	SI32					m_siMix[AMBER_BOX_LIST_NUM];										// �����ϰ� �簢���� �����̰� ������ ��Ƶ�.

	SI32					m_siRandItemNum;													// �����ϰ� ���� �簢���� �׷����� ����Ʈ�� ������ ��ȣ. 
	DWORD					m_dwPrevTickCount;

	TSpr					m_Spr;																// �����ϰ� ���õǴ� ��ɻ��� ������.
	TSpr					m_SprListViewBack;																// �����ϰ� ���õǴ� ��ɻ��� ������.
	SI32					m_siRandItemListNum;												// ������ �������� ����.

	SI32					m_siSelectItemIndex[AMBER_BOX_SELECT_ITEM_LIST_NUM];				// �����ϰ� ���õ� �������� ����Ʈ���� �ε��� ��ȣ.

public:
	SI16					m_siUseItemUnique;													// ����ϴ� �������� ����ũ.
};
#endif
