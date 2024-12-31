//------------------------------------------------------------------------------
//
//	��Ƽ��Ʈ ����ü ���� â.
//
//	2008. 2. 25
//	Ȳ����
//
//------------------------------------------------------------------------------
#ifndef _NARTIFACT_MIXTURE_DLG_
#define _NARTIFACT_MIXTURE_DLG_

#pragma once

#include "Char\CharManager\CharManager.h"

#include "../../Client/client.h"
#include "../../InterfaceMgr/DialogController.h"
#include "../../InterfaceMgr/InterfaceFile.h"
#include "../../CommonLogic/CommonLogic.h"

class NArtifactMixtureDlg : public CDialogController
{
	enum
	{
		GAGE_NUM	= 152,
		EFFECT_NUM	= 12
	};
	enum{ NO_SLOT = -1, EQUIP_SLOT, CRYSTAL_SLOT1, CRYSTAL_SLOT2, CRYSTAL_SLOT3, CRYSTAL_SLOT4, CRYSTAL_SLOT5, TOTAL_SLOT_COUNT }; 

public:
	NArtifactMixtureDlg();
	~NArtifactMixtureDlg();
	void Clear( void );

	void Create( CControllerMgr *pParent );

	void Action(void);
	void DrawDialogLast( SI32 ScreenRX, SI32 ScreenRY ); 

	static void CALLBACK StaticNArtifactMixtureDlgProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
		   void CALLBACK NArtifactMixtureDlgProc(UINT nEvent, int nControlID, CControllerObj* pControl);

		   
    bool InsertEquip( CListView* _pListView, cltItem* _cltItem );						// ��� ���Կ� ������ �ֱ�.
	void InsertEquipSetCrystal( void );													// ��� ������ ���� �ش� ����ü ������ ����.
    bool InsertCrystal( CListView* _pListView, cltItem* _cltItem );						// ����ü ���Կ� ������ �ֱ�.
	void DelListViewItem( CListView* _pListView, SI08 _SlotNum );						// �ش� ���Կ� ������ ����.
	void DelAllListViewItem( void );													// �ش� ���Կ� ������ ����.
	bool CanInsertEquip( void );														// ������ �迭 ������ ���� Ȯ��.
	bool CanInsertCrystal( cltItem* _cltItem );											// ������ �迭 ������ ���� Ȯ��.
	bool CanDel( void );																// ������ ������ �������� Ȯ��.
	bool CanMixure( SI32 _ItemUnique );													// ������ ���� Ȯ��.
	bool IsCristal( SI32 _ItemUnique );													// ����ü �������ΰ�.
	void MixtureSuccess( cltItem* _cltItem );											// ���� ����. S->C
	void DeleteBuffer( SI32 _ClassType, void* _ClassData );								// ���� �޽��� ���� �޸� ����.
	bool SameCrystalInvenItem( SI32 _InvenPos);											// �������� �κ������� ��ġ�� ������ ���� ���������� Ȯ���ϴ� �Լ�.
	bool SameEquipCrystalItem( cltItem* _cltItem );										// ��� �����ۿ� ���Կ� �߰��Ϸ��� ����ü�� �ִ��� Ȯ��(�����ɷ����� ����)
	void EquipExplain( cltItem* pEquip );												// ��� �������� ���� ����.
	void CrystalExplain( CEdit* _pExplainStatic, cltItem* pEquipItem, SI16 _siSlot);	// �����ۿ� ���� ������ ������ �����ش�.
	void EquipCrystalExplain( CEdit* _pExplainEdit, cltItem* pEquipCrystal, SI16 _siSlot ); // ���� ���� ����ü�� ������ �����ش�.
	void NotifyMsg( SI32 _MsgType );	
	bool SameEquipCrystalAbility( cltItem* _cltItem );									// ���� �ɷ��� ����ü�� �ִٸ�.
	bool Islevel(SI32 EquipItemUnique, SI32 CristalItemUnique);							// ũ����Ż�� �����Ҷ� ���������� �������� �˻�.
	bool IsAbilityType(cltItem* pclEquipItem, SI32 CristalItemAbilytype);				// ����ü�� �����Ϸ��� �����ۿ� ������ �Ǵ� ����ü ���� �˻�.
	bool IsMixture(void);																// ������ �������� �˻�.


	void SendServerMsg( SI32 _MsgType );												// ������ �޽����� ����.
	bool EndClickAndDrop( cltClickAndDrop* pclClickAndDrop );
	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );
	

public:
	InterfaceFactory	m_InterfaceFactory;

	SI16				m_InventoryPos[ TOTAL_SLOT_COUNT ];						// ���Կ� �� �������� ���� �κ��� ��ġ
	cltItem				m_clArtifactItem[ TOTAL_SLOT_COUNT ];					// ���Կ� �� ������.
	cltItem				m_clMixtureSuccessItem;

	SI08				m_CurrentSlot;

	BOOL				m_bCrystalSlotImageList[TOTAL_SLOT_COUNT];				// �������� ���԰� �󽽷��� ����. �ʱ�ȭ�� ��� ���� ���Ը� true;

	TSpr*				m_Spr[4];

	
	
	SI16				m_siGaugeCount;
	SI16				m_siEffectCount;
	bool				m_bGaugeAction;
	bool				m_bEffectAction;
};

#endif
