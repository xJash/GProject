#ifndef _NNEWINVENTORY_H_
#define _NNEWINVENTORY_H_

#include "../../InterfaceMgr/DialogController.h"

#include "../../../Common/Item/ItemCommon/ItemUnit.h"


#define NEWMAKE_MATERIALFOR_MAKEITEM	1
#define NEWMAKE_TOOLSFOR_MAKEITEM		2
#define NEWMAKE_ORIGINALFOR_ENCHANT		3
#define NEWMAKE_MATFOR_ENCHANT			4
#define NEWMAKE_ELEFOR_ENCHANT			5


class CImageStatic;
class CButton;
class CComboBox;
class CListView;
class CEdit;
class CStatic;
class CChatTabButton;

class cltSummonInfo;

class CItemInventoryBuffer;
struct stMoveData;
#define DEFAULT_MAKEITEMNUM 1

#define TAB_SELECTED_PERSON 0
#define TAB_SELECTED_HORSE 1
#define TAB_SELECTED_BAG 2

class cltMakeItemContainer
{
public:
	cltMakeItemContainer()
	{
		Init();
	}
	void Init()
	{
		for(SI32 i=0; i<4; i++)
		{
			cltools[i].Init();          //���� ������ ��
			m_sitools[i] = 0;           //������ �ε���
		}
		for(SI32 i=0; i<25; i++)
		{
			clMaterials[i].Init();   //���� ������ 
			m_siMaterials[i] = 0;    //���� ������ �ε���
		}
		clOrgEnchantItem.Init();     //��æƮ ��ų ������
		clMatEnchantItem.Init();     //��æƮ�� ���� ������ ������
		for(SI32 i=0; i<NOW_ENCHANT_NUMBER; i++)
		{	
			clEleEnchantItem[i].Init(); //��æƮ �Ӽ���������
		}
	}

	cltItem cltools[4];			//������ ���� �� ������ �������
	SI32	m_sitools[4];			//������ �ε���
	cltItem clMaterials[25];		//������ ���� ��� ������ �������
	SI32	m_siMaterials[25];		//���� ������ �ε���
	cltItem clOrgEnchantItem;		//��æƮ ��ų ������
	cltItem clMatEnchantItem;		//��æƮ�� ���� ������ ������
	cltItem clEleEnchantItem[NOW_ENCHANT_NUMBER];	//��æƮ �Ӽ���������

};


class CNNewInventory : public CDialogController
{
public:
	CNNewInventory();
	~CNNewInventory();

	void Create();

	static void CALLBACK StaticCallBackDialogNNewInventory( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
	void CALLBACK CallBackDialogNNewInventory( UINT nEvent, int nControlID, CControllerObj* pControl );

	void MoveItem( SI32 Destination );

	void ShowTools( SI32 Destination ); //����â�� ��
	void ShowMaterials( SI32 Destination ); //����â�� ���â

	void ShowEnchantOrg(SI32 Destination); //��æƮâ�� ��æƮ��ų������ �����ֱ�
	void ShowEnchantMat(SI32 Destination); //��æƮâ�� ����������� �����ֱ�
	void ShowEnchantElem(SI32 Destination); //��æƮâ�� �Ӽ������� �����ֱ�

	void ChangeItem( SI32 Destination );
	void RepairItem( SI32 SelectedInventoryItemIndex );
	void UseNolimitTicket(SI32 ItemUnique,SI32 Type);
	void UseItem( SI16 Pos );
	void DropItem( SI16 Pos );
	void DropItem_New( cltItem* pclItem, SI16 Pos );
	void EquipItem( SI16 Pos );
	void ExchangeWeapon();
	void ExchangeClothes();

	bool CheckBag( SI32 siSource, SI32 siDestination );

	bool MoveItem( SI32 siSource, SI32 siDestination );
	bool ChangeItem( SI32 siSource, SI32 siDestination );

	//SI32    CheckIsInventory();
	SI32 GetInventoryType(SI32 type);
	SI32 GetInventoryTypeForSummon( SI32 siItemType );

	void CancellationSealingUp( SI32 siIndex);

	void Show();
	void Hide();

	void Action();

	bool IsSummonDataChanged();
	bool IsItemDataChanged();

	void LoadItemData();
	void LoadSummonData();
	void LoadInventoryTabData();

	void UpdateMakeItemData();

	void DrawDialogFirst( SI32 ScreenRX, SI32 ScreenRY  );
	void DrawDialogLast( SI32 ScreenRX, SI32 ScreenRY  );

	bool Pop( stMoveData * pMoveData );
	bool Pop( BYTE* pMoveData );


	void IsMinimi(bool bSet);
	void ChangeMaxMode(bool bSet);
	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );
	void CheckWrongSelectedInven();	// ���� ���µ� ���κ��� ���õ� ��츦 üũ���ش�
	void SelectInven(SI16 SelectInventoryIndex);

	void ShowInvenWeight();
	void ShowSlotNum();			// �κ��� ����/�ѽ��� ������ �����ش�.

	bool CheckCanEnchintItem(SI32 unique );
	bool CheckCanPutonItem(SI32 siUnique);
	bool CheckCanEquipItem(SI32 siUnique);

	void SetCharStatusChanged(bool Changed){ m_bStatusChanged = Changed; };
	void CheckCharStatusChanged();
	void MakeSetEnchant(bool bMakeButton);

	void SetInventoryMode(SI16 DialogId);

	virtual bool EndClickAndDrop( cltClickAndDrop* pclClickAndDrop );

	void GetPositionFromControllerID( IN SI16 siControllerID, IN SI16 siLastSelectedIndex, OUT SI16* psiSelectPos, OUT SI16* psiMakeItemPos );

	void UseWarpTargetWorld(SI32 siItemUnique )	;	//	 � Ƽ���� ������ �ش� ��ġ�� ���� �Ҷ� 

	void UseLevelLimitBoxOpen(SI32 siItemUnique )	;	// [����] ���� ���� ���ڿ��� �������� �ش� 

	

public:
	static SI16	m_siSelectedIndex;
	static bool	m_bMini;
	static bool	m_bMax;

	SI16		m_siActionFrame;
	SI16		m_siCurrentSummonIndex;
	SI16		m_siCurrentInventoryIndex;
	SI16		m_siComboBoxSelectedIndex;
	SI16		m_siLastSelectInventoryIndex;
	bool		m_bMakeButton;

	SI32		*m_pMakeableItemList;
	SI32		m_siMakeableItemNum;

	bool		m_bHorseHave;
	bool		m_bBagHave;
	bool		m_bClickChangeItem;	// ���� Ŭ������ ������ �ٲ۴�(�����)
	bool		m_bStatusChanged;

	cltItem		*m_pclInventoryItem;
	CItemInventoryBuffer *m_pBuffer;
	cltPItemInfo *m_pPersonItemInfo;

	CButton		*m_pMakeItemBtn;
	CButton		*m_pEnchantItemBtn;
	CButton		*m_pItemmallListBtn;
	//CComboBox	*m_pMakeItemComboBox;
	//CStatic		*m_pMakeItemStatic;
	CStatic		*m_pWeightStatic;
	//CEdit		*m_pMakeItemInputEdit;

	CListView	*m_pInventoryListView;
	CListView	*m_pMoveItemToHorseListView;
	CListView	*m_pMoveItemToBag0ListView;
	CListView	*m_pMoveItemToBag1ListView;

	CButton*	m_pButtonMini;
	CButton*	m_pButtonMax;
	CButton*	m_pButtonSpaceBox;					// [�߰� : Ȳ���� 2008. 1. 29 => ���� ����.  ��ư ������ .]
	//CChatTabButton*	m_pButtonManInventory;
	//CChatTabButton*	m_pButtonHorseInventory;
	//CChatTabButton*	m_pButtonBagInventory;

	CStatic*    m_pStatic[3];
	
	//	CStatic*    m_pStatic[2];
	static	cltMakeItemContainer	clMakeItemContainer;

};
#endif