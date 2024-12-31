/* ==========================================================================
Ŭ���� :		CNManufactureDlg_New

�ۼ��� :		09/12/16
�ۼ��� :		�ռ���

������� :

�����۾� :		
========================================================================*/

#pragma once

#include "../../Client/client.h"
#include "../../InterfaceMgr/DialogController.h"

class CEachPersonTradeOrderInfo;
class CLibListMgr;


class CNManufactureDlg_New : public CDialogController
{
public:
	
	CNManufactureDlg_New();
	~CNManufactureDlg_New();

	void Initialize();
	void Destroy();

	void Create();

	static	void CALLBACK StaticNManufactureDlg_NewProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void	CALLBACK NManufactureDlg_NewProc( UINT nEvent, int nControlID, CControllerObj* pControl );

	void Show( SI32 siCharUnique, SI32 siPersonID, SI16 ShopMode, TCHAR *Name, TCHAR *AccountID, BOOL bShopStarted );
	void Hide();
	void Action();
	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );

	void SetMakeableItemList();

	void ShopInit(BOOL bSelf);

	void StartPersonalShop();

	void DisplayMessage(BOOL siSuccess, TCHAR *pBuffer);


	void MakeShopItem();
	bool DropShopItem();

	void StopPersonalShop();
	void RefreshShowData();
	void SetItemImageData(SI32 ItemUnique);

	void VDirectDrawToBackScreen( LPDIRECTDRAWSURFACE7 lpBackScreen, SI32 ScreenRX, SI32 ScreenRY );

	bool CheckMakeData_Client()		;					// ����ٰ� �ϱ� ���� �����͸� üũ �Ѵ�.
	bool CheckMakeData_Maker()		;					// ����ڴٰ� �ϱ� ���� �����͸� üũ �Ѵ�.

	void SetComboBox_ItemCategory()	;
	void SetComboBox_ItemCategory_Select();
	
	bool ChekMakeItem_By_ItemType(SI32 siItemtype);	// �ش� �׸��� �ڽ��� ����� �ִ� �������� �ִ��� Ȯ�� �Ѵ�.
	bool CeckHaveTool( SI32 siItemUnique )	;		// ��ǥ �������� ����� ���� ������ �ִ°� ?
	bool CeckHaveSkill( SI32 siItemUnique )	;		// ��ǥ �������� ����� ��ų�� ������ �ִ°� ?

	bool ChekMakeItem( cltItemInfo* pinfo )	;
	void Set_Manufacture_Mode()				;		// ������ ���� ����
	void Set_Client_Mode()				;		// �����Ƿ��� ���� ����
	void MakeItemDataSet(SI32 siItemUnique)	;	// ���� ������ �����͸� �����Ѵ�.
	void SetEditBox();							// ��ƼƮ �ڽ��� �����͵��� �ִ´� .
	bool CheckItemType( SI32 siType )		;
public:

	InterfaceFactory	m_InterfaceFactory;


	BOOL			m_bSelf;
	BOOL		    m_bShopStarted;  
	BOOL			m_bShow;	

	cltItem			m_clUserItem[ MAX_ITEM_PER_PERSON ];

	BOOL				m_bShopDataChanged;
	TCHAR				m_szShopBanner[MAX_PERSONAL_SHOP_TEXT_SIZE];

	SI32				m_siShopTradeIndex[MAX_SHOP_ITEM_NUMBER];	

	cltShopTradeData	m_clShopData;

	SI32			m_siShopperCharUnique;
	SI32			m_siShopperPersonID;
	TCHAR			m_szAccountID[MAX_PLAYER_NAME];
	TCHAR			m_szCharName[MAX_PLAYER_NAME];

	SI32			m_siImageType;
	SI32			m_siImageIndex;

	bool			m_bClient	;

};
