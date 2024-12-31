//------------------------------------------------------------------------------
//
//	��Ƽ��Ʈ â.
//
//	2008. 2. 26
//	Ȳ����
//
//------------------------------------------------------------------------------
#ifndef _NARTIFACT_SLOT_CREATE_DLG_
#define _NARTIFACT_SLOT_CREATE_DLG_

#pragma once

#include "Char\CharManager\CharManager.h"

#include "../../Client/client.h"
#include "../../InterfaceMgr/DialogController.h"
#include "../../InterfaceMgr/InterfaceFile.h"
#include "../../CommonLogic/CommonLogic.h"

class NArtifactSlotCreateDlg : public CDialogController
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
		

		IMAGE_NUM,					// �̹��� ����.   
	};

	enum{ 
			EQUIP_SLOT		 = 0,	// ���   ���� ��ȣ.
			CRYSTAL_SLOT	 = 1,	// ����ü ���� ��ȣ.
			USED_SLOT_COUNT  = 2,	// ��밡���� ���� ��.
			RESULT_ITEM_SLOT = 2,	// ����� ������ ���Թ�ȣ.
		};

public:
	NArtifactSlotCreateDlg();
	~NArtifactSlotCreateDlg();
	void Clear( void );

	void Create( CControllerMgr *pParent );
	void Action(void);
	void DrawDialogLast( SI32 ScreenRX, SI32 ScreenRY ); 

	static void CALLBACK StaticNArtifactSlotCreateDlgProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
		   void CALLBACK NArtifactSlotCreateDlgProc(UINT nEvent, int nControlID, CControllerObj* pControl);

	bool InsertEquip( CListView* _pListView, cltItem* _cltItem );				// ��� ���Կ� ������ �ֱ�.
	bool InsertCrystal( CListView* _pListView, cltItem* _cltItem );				// ����ü ���Կ� ������ �ֱ�.
	void DelListViewItem( CListView* _pListView );								// �ش� ���Կ� ������ ����.
	void DelAllListViewItem( void );											// ��� ������ ����.
	bool CanInsertEquip( void );												// ������ �迭 ������ ���� Ȯ��.
	bool CanInsertCrystal( cltItem* _cltItem );									// ������ �迭 ������ ���� Ȯ��.
	bool CanInsert( void );														// ������ �迭 ������ ���� Ȯ��.
	bool CanDel( void );														// ������ ������ �������� Ȯ��.
	bool IsCristal( SI32 _ItemUnique );											// ����ü �������ΰ�.
	bool EndClickAndDrop( cltClickAndDrop* pclClickAndDrop );
	void SlotCreateSuccess( cltItem* _cltItem );
	void DeleteBuffer( SI32 _ClassType, void* _ClassData );
	void SendServerMsg( SI32 _MsgType );
	void NotifyMsg( SI32 _MsgType );
	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );
	bool IsSlotCreateMsg(void);

public:
	InterfaceFactory	m_InterfaceFactory;

	SI16				m_InventoryPos[USED_SLOT_COUNT];		
	cltItem				m_clArtifactItem[ USED_SLOT_COUNT ];	
	cltItem				m_clCreateSlotSuccessItem;

	SI08				m_CurrentSlot;

	TSpr*				m_Spr[IMAGE_NUM];

	SI16				m_siGaugeCount;
	SI16				m_siEffectCount;
	bool				m_bGaugeAction;
	bool				m_bEffectAction;
};

#endif