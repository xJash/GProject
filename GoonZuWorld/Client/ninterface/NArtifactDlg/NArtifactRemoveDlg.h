//------------------------------------------------------------------------------
//
//	��Ƽ��Ʈ â.
//
//	2008. 2. 26
//	Ȳ����
//
//------------------------------------------------------------------------------
#ifndef _NARTIFACT_REMOVE_DLG_
#define _NARTIFACT_REMOVE_DLG_

#pragma once

#include "Char\CharManager\CharManager.h"

#include "../../Client/client.h"
#include "../../InterfaceMgr/DialogController.h"
#include "../../InterfaceMgr/InterfaceFile.h"
#include "../../CommonLogic/CommonLogic.h"

class NArtifactRemoveDlg : public CDialogController
{
	enum
	{
		GAGE_NUM	= 152,
		EFFECT_NUM	= 12

	};
	enum
	{
		IMAGE_GAGE_BACK,			// ������ ���.
		IMAGE_GAGE,					// ������.
		IMAGE_EFFECT,				// ����Ʈ ȿ��.
		IMAGE_SLOT_REMOVE,			// ���ſ� �̹���.
		IMAGE_ARROW_IN_OUT,

		IMAGE_NUM,					// �̹��� ����.   
	};

	enum{ SLOT_COUNT = 6, };
	enum{ NO_SLOT = -1, EQUIP_SLOT, CRYSTAL_SLOT1, CRYSTAL_SLOT2, CRYSTAL_SLOT3, CRYSTAL_SLOT4, CRYSTAL_SLOT5,TOTAL_SLOT_COUNT }; 

public:
	NArtifactRemoveDlg();
	~NArtifactRemoveDlg();
	void Clear( void );

	void Create( CControllerMgr *pParent );
	void Action(void);

	static void CALLBACK StaticNArtifactRemoveDlgProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
		   void CALLBACK NArtifactRemoveDlgProc(UINT nEvent, int nControlID, CControllerObj* pControl);

	bool InsertListViewItem( CListView* _pListView, cltItem* _cltItem );		// ���Կ� ������ �ֱ�.
	void DelListViewItem( CListView* _pListView );								// �ش� ���Կ� ������ ����.
	void DelAllListViewItem( void );											// ��� ������ ����.
	bool CanInsert( void );														// ������ �迭 ������ ���� Ȯ��.
	bool CanDel( void );														// ������ ������ �������� Ȯ��.
	SI32 RemoveItemPos( void );													// ���� ���ſ� ����� �������� �κ��� �ִ��� Ȯ���ϰ� ��ġ ����.
	void ClickRemoveSlot( SI32 _SlotIndex );									// ������ ���� ����. 
	void InsertEquipSetCrystal( void );
	bool CanMixure( SI32 _ItemUnique );											// ������ ���� Ȯ��.
	bool InsertCrystal( CListView* _pListView, cltItem* _cltItem );
	bool CanInsertCrystal( cltItem* _cltItem );
	bool IsCristal( SI32 _siItemUnique );
	void DrawDialogLast( SI32 ScreenRX, SI32 ScreenRY  );
	bool SameCrystalInvenItem( SI32 _InvenPos);
	void NotifyMsg( SI32 _MsgType );
	void RemoveSuccess(cltItem* pEquip);
	void EquipExplain( cltItem* pEquip );												// ��� �������� ���� ����.
	void CrystalExplain( CEdit* _pExplainStatic, cltItem* pEquipItem, SI16 _siSlot);	// �����ۿ� ���� ������ ������ �����ش�.

	void SendServerMsg( SI32 _MsgType );												// ������ �޽����� ����.
	void DeleteBuffer( SI32 _ClassType, void* _ClassData );
	bool EndClickAndDrop( cltClickAndDrop* pclClickAndDrop );
	bool IsRemove(void);

public:
	InterfaceFactory	m_InterfaceFactory;

	SI16				m_InventoryPos[SLOT_COUNT];
	cltItem				m_clCrystalItem[ SLOT_COUNT ];									// ����ü�� ������ �� ����� �������� �κ����� ã�� �ִ´�. 

	cltItem				m_clArtifactItem[ SLOT_COUNT ];	

	SI08				m_CurrentSlot;

	bool				m_bRemoveSlotIndex[ SLOT_COUNT ];						// ����ü�� ������ �� ����� �������� �κ������� ��ġ. 	
	
	TSpr*				m_Spr[IMAGE_NUM];

	cltItem				m_clRemoveSuccessItem;

	SI16				m_siGaugeCount;
	SI16				m_siEffectCount;
	bool				m_bGaugeAction;
	bool				m_bEffectAction;
};

#endif