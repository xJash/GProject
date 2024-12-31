//------------------------------------------------------------------------------
//
//	��Ƽ��Ʈ â.
//
//	2008. 2. 26
//	Ȳ����
//
//------------------------------------------------------------------------------
#ifndef _NARTIFACT_RESTORE_DLG_
#define _NARTIFACT_RESTORE_DLG_

#pragma once

#include "Char\CharManager\CharManager.h"

#include "../../Client/client.h"
#include "../../InterfaceMgr/DialogController.h"
#include "../../InterfaceMgr/InterfaceFile.h"
#include "../../CommonLogic/CommonLogic.h"
#include "Item/ItemCommon/Itemunit.h"

class NArtifactRestoreDlg : public CDialogController
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

	enum{ SLOT_COUNT = 6, DISASSEMBLE_ITEM_NUM = 5, };
	enum{ NO_SLOT	 = -1, EQUIP_SLOT, CRYSTAL_SLOT1, CRYSTAL_SLOT2, CRYSTAL_SLOT3, CRYSTAL_SLOT4, CRYSTAL_SLOT5 }; 

public:
	NArtifactRestoreDlg();
	~NArtifactRestoreDlg();
	void Clear( void );

	void Create( CControllerMgr *pParent );
	void Action(void);
	void DrawDialogLast( SI32 ScreenRX, SI32 ScreenRY ); 

	static void CALLBACK StaticNArtifactRestoreDlgProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
		   void CALLBACK NArtifactRestoreDlgProc(UINT nEvent, int nControlID, CControllerObj* pControl);
	
   void SetArtifactStorage(cltItem* _itemlist);									// ȯ�� �� ������ �ֱ�.
   void InsertEquipItem( CListView* _pListView, cltItem* _cltItem );			// ���Կ� ������ �ֱ�.
   void DelListViewItem( CListView* _pListView );								// �ش� ���Կ� ������ ����.
   void DelAllListViewItem( void );												// ��� ������ ����.
   bool CanInsert( void );														// ������ �迭 ������ ���� Ȯ��.
   bool CanDel( void );															// ������ ������ �������� Ȯ��.
   void DeleteBuffer( SI32 _ClassType, void* _ClassData );						// ���� �޽��� ���� �޸� ����.
   void SetDisasembleItem(cltItem* _cltItemlist);								// ���ص� ������ ����Ʈ�� �����Ѵ�. �׸��� ������ �غ�.
   
   bool EndClickAndDrop( cltClickAndDrop* pclClickAndDrop );					// �κ��丮���� �������� �����,
   void SendServerMsg( SI32 _MsgType );											// ������ �޽����� ����.
   void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );
   bool IsEmptyDisasembleItem(void);											// ���ذ� �Ǽ� �����ؾ� �� ��� �������� �ִ°�.
   bool IsRestoreItemType(SI32 _siItemUnique);									// ���ذ� �Ǵ� ������ Ÿ���ΰ�
   void NotifyMsg( SI32 _MsgType );												// ���� �˾� �޽���.

public:
	InterfaceFactory	m_InterfaceFactory;

	SI16				m_InventoryPos;										// ��� �������� �κ����� ��ġ.
	cltItem				m_clArtifactItem[ SLOT_COUNT ];				
	cltItem				m_clDisasembleItemItemList[DISASSEMBLE_ITEM_NUM];

	TSpr*				m_Spr[IMAGE_NUM];

	SI16				m_siGaugeCount;
	SI16				m_siEffectCount;
	bool				m_bGaugeAction;
	bool				m_bEffectAction;
};

#endif