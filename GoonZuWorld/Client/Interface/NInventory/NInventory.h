#ifndef _NINVENTORY_H_
#define _NINVENTORY_H_

#include "../../InterfaceMgr/DialogController.h"

#include "../../../Common/Item/ItemCommon/ItemUnit.h"

class CImageStatic;
class CButton;
class CComboBox;
class CListView;
class CEdit;
class CStatic;

class cltSummonInfo;

class CItemInventoryBuffer;
struct stMoveData;

class CNInventory : public CDialogController
{
public:
	CNInventory();
	~CNInventory();

	void Create();

	static void CALLBACK StaticCallBackDialogNInventory( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
	void CALLBACK CallBackDialogNInventory( UINT nEvent, int nControlID, CControllerObj* pControl );

	void EquipmentListViewMsgProc( CListView* pListView, SI16 ItemPos, UINT nEvent );
	void MoveItem( SI32 Destination );
	void ChangeItem( SI32 Destination );
	void RepairItem( SI32 SelectedInventoryItemIndex );
	void UseItem( SI16 Pos );
	void DropItem( SI16 Pos );
	void ExchangeWeapon();
	void ExchangeClothes();
	//SI32    CheckIsInventory();
	SI32 GetInventoryType(SI32 type);

	void CancellationSealingUp( SI32 siIndex);	// �к� ����

	void SetMakeItemNumEnable();						// ��ø �ȵǴ� �������� �������� 1�� ����

	void Show();
	void Hide();
	
	void Action();

	bool IsSummonDataChanged();
	bool IsItemDataChanged();

	void LoadItemData();
	void LoadSummonData();
	void LoadInventoryTabData();

	void DrawDialogFirst( SI32 ScreenRX, SI32 ScreenRY  );
	void DrawDialogLast( SI32 ScreenRX, SI32 ScreenRY  );

	bool Pop( stMoveData * pMoveData );
	bool Pop( BYTE* pMoveData );

	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );

private:
	SI16		m_siSelectedIndex;
	//SI16		m_siPreItemDragIndex;

	SI16		m_siActionFrame;

	CButton		*m_pMakeItemBtn;
	CComboBox	*m_pMakeItemComboBox;
	CStatic		*m_pMakeItemStatic;
	CEdit		*m_pMakeItemInputEdit;
	
	
	CListView	*m_pEquipmemntItemListView[ MAX_SHAPE_ITEM ];		// ��� ������ ������ ����

	CListView	*m_pMoveItemToHorseListView;
	CListView	*m_pMoveItemToBagListView;

	CListView	*m_pInventoryListView;
	
	CButton		*m_pChangeEquipmentWindow[ 3 ];						// ���â �ٲٱ�( ��ĳ��, ��ȯ����1, ��ȯ����2 )
	CButton		*m_pChangeInventoryWindow[ 3 ];						// �κ�â �ٲٱ�( ���, ��, ���� )

	CButton		*m_pChangeWeapon;									// ���� �ٲٴ� ��ư
	CButton		*m_pChangeClothes;									// ���� �ٲٴ� ��ư


	cltItem		*m_pclEquipItem;
	cltItem		*m_pclInventoryItem;

	SI16		m_siCurrentSummonIndex;
	SI16		m_siCurrentInventoryIndex;

	SI32		*m_pMakeableItemList;
	SI32		m_siMakeableItemNum;

	bool		m_bHorseHave;
	bool		m_bBagHave;

	cltSummonInfo *m_pSummonInfo;

	CItemInventoryBuffer *m_pBuffer;

	SI16		m_siComboBoxSelectedIndex;

	SI16		m_siCurrentWeightDrawPos;
	SI16		m_siCurrentWeightDrawXSize;
	RGB16*		m_WeightImgEncBuffer;
	CControllerSurfaceObj *m_pWeightSurfaceObj;
	SI16		m_siWeightSurfaceWidth;
	SI16		m_siWeightSurfaceHeight;
	cltPItemInfo *m_pPersonItemInfo;
};

#endif