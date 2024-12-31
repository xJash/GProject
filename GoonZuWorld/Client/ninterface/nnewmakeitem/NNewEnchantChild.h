
#pragma once

#include "Resource.h"
#include "NNewMakeItemDlg.h"


#include "../../InterfaceMgr/DialogController.h"
#include "../Client/Inventory/ItemInventoryBaseDefinition.h"

class CButton;
class CListView;

class CNNewEnchantChild  : public CDialogController
{
public:

	CNNewEnchantChild();
	~CNNewEnchantChild();

	static void CALLBACK	StatiCNNewEnchantChildProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void CALLBACK			NNewEnchantChildProc(UINT nEvent, int nControlID, CControllerObj* pControl );
	void Create(CControllerMgr *pParent);	
	void Show();
	void Hide();
	void EnableButton(bool bWater, bool bFire, bool bWind, bool bGround);
	void OriginalListViewMsgProc( CListView* pListView, SI16 ItemPos, UINT nEvent );
	void MaterialListViewMsgProc( CListView* pListView, SI16 ItemPos, UINT nEvent );
	void ElementListViewMsgProc( CListView* pListView, SI16 ItemPos, UINT nEvent );

	void ShowOrgEnchantItem(cltItem cltOrgItem);
	void ShowMatEnchantItem(cltItem cltMatItem);
	void ShowEleEnchantItem(cltItem cltEleItem[]);
	bool IsCheckMaterial();
	//bool IsCheckSkill(cltItem clItem);
	void SetEnchantCharUnique(SI32 CharUnique);
	
	void SetEnchantOtherState(BOOL bEnchantOther );

	void SetInitInchant();
	

	void SetChangeEnchanteButton( SI32 siEnchantType );
	void ShowChangeEnchantMsgBox( SI32 siEnchantType );
	void CheckChangeEnchantItem( SI16 siItemUnique, SI16 siElementIndex );

	InterfaceFactory m_InterfaceFactory;

	bool CheckEnchantMaterial( SI32 siEnchantType, SI32 siMaterialUnique );
	bool EndClickAndDrop( cltClickAndDrop* pclClickAndDrop );

private:
	//cltItem					m_clUserItem[ MAX_ITEM_PER_PERSON ];
	//SI32					m_siUserItemPrice[ MAX_ITEM_PER_PERSON ];
	//cltPItemInfo			*m_pPersonItemInfo;


	cltItem m_clOrgEnchantItem;		//��æƮ ��ų ������
	cltItem m_clMatEnchantItem;		//��æƮ�� ���� ������ ������
	cltItem m_clEleEnchantItem[NOW_ENCHANT_NUMBER];	//��þƮ ��� ������ 
	SI32 m_siEnchantableItemList;
	SI32 m_siEnchantableItemCompare;

	SI32 m_siOtherCharUnique;


};