
/* ==========================================================================
	Ŭ���� :		CNNPCTradeDlg

	�ۼ��� :		2005/03/31
	�ۼ��� :		���¾�

	��  �� :		.
	                

	��  �� :		
	������� :		����

	�����۾� :		cpp �۾� �Ϸ� ��

   ========================================================================*/

#include "../../interface/NPC1/NPCTradeBaseInfo.h"
#include "../../InterfaceMgr/DialogController.h"
#define MAX_AVAILABLE_CASHITEMNUM		256


class CNPCTradeBuffer;
class CButton;
class CStatic;
class CListView;
class CEdit;

class CNNPCTradeDlg : public CDialogController
{
public:
	CNNPCTradeDlg();
	~CNNPCTradeDlg();

	void	Initialize();
	void	Destroy();
	//void    Set(cltPItemInfo *pPersonItemInfo, cltNPCItemInfo *pNPCItemInfo);

	void	Create( );

	
	static void CALLBACK StaticNNPCTradeDlgProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void CALLBACK NNPCTradeDlgProc(UINT nEvent, int nControlID, CControllerObj* pControl);

	bool	IsUserInventoryChanged();						// ���� �κ��丮�� �ٲ� ���� �ִ��� üũ
	bool	IsNPCInventoryChanged();						// NPC �κ��丮�� �ٲ� ���� �ִ��� üũ

	void	LoadUserInventory();							// ���� �κ��丮 ������ �ε�
	void	LoadNPCInventory();								// NPC  �κ��丮 ������ �ε�

	void	SellItemToNPC();								// ������ NPC ���� �������� �Ǹ�
	void	BuyItemFromNPC();								// NPC �� ���� ������ ������ ����

	void    SettingListView();
	void	UpdateUserInventory();							// ������ �������� �Ȱų� ������ �ÿ� ������ ���� �����͸� �޾Ƽ� ����Ǿ�����, �� �� update �� �ֱ� ���ؼ�...
	void	UpdateNPCInventory();							// NPC�� �κ��丮�� ���� ���� ���� ������, Ȥ�ó� ������ ���� ���� �����Ƿ�...
	void    Action();
	
	void	Show(SI32 npckind);								// ���̾�α� ���� �ֱ�	
	//void	Hide();											// ���̾�α� �����

	//bool	IsShow();

	bool	Pop( stNPCTradeData * pNPCTradeData );			// ������ �������� �Լ�

	void	SetText( TCHAR *strText );						// �Ȱų� ��ų� ������ ��Ȳ�� ������� �ϹǷ�...
	void	SetText( SI32 siTextIndex );					// �Ȱų� ��ų� ������ ��Ȳ�� ������� �ϹǷ�...
	bool LoadBuyCashItemInfo();
	bool IsSameItemTypeExist( TCHAR *ItemType );
	bool IsCheckCashItem(SI32 Uinque);

	void	SetDialogInfo( SI32 siTitleTextNum, SI32 siExplainTextNum );


private:
	cltItem					m_clUserItem[ MAX_ITEM_PER_PERSON ];
	GMONEY					m_siUserItemPrice[ MAX_ITEM_PER_PERSON ];

	cltItem					m_clNPCItem[ MAX_NPC_ITEM_NUMBER ];
	GMONEY					m_siNPCItemPrice[ MAX_NPC_ITEM_NUMBER ];

	cltPItemInfo			*m_pPersonItemInfo;
	cltNPCItemInfo			*m_pNPCItemInfo;

	//HWND					m_hDlg;
	//HWND					m_hUserInventory;
	//HWND					m_hNPCInventory;
	//HWND					m_hNPCTradeInfoViewEdit;
	bool					m_bShowFlag;


	CNPCTradeBuffer			*m_pNPCTradeBuffer;

	SI32					m_siUserInventorySelectedIndex;
	SI32					m_siNPCInventorySelectedIndex;

	SI32					m_siSellItemNum;
	SI32					m_siBuyItemNum;
	
	SI32					m_siNPCCharUnique;
	SI32					m_siNPCKind;

	CStatic     	       *m_pNNPCTradeStatic1;
	CStatic     	       *m_pNNPCTradeStatic2;
	CStatic     	       *m_pNNPCTradeStatic3;
	CStatic     	       *m_pNNPCTradeStatic4;
	CStatic     	       *m_pNNPCTradeStatic5;
	CEdit                  *m_pNNPCTradeEdit;
	CButton                *m_pNNPCTradeButton1;
	CButton                *m_pNNPCTradeButton2;
	CListView              *m_pNNPCTradeListView1;
	CListView              *m_pNNPCTradeListView2;


	TCHAR m_strItemTypeList[ MAX_ITEMTYPE_NUMBER ][ 64 ];
	SI16 m_siItemUniqueList[ MAX_AVAILABLE_CASHITEMNUM ];
	UI16 m_uiItemPriceList[ MAX_AVAILABLE_CASHITEMNUM ];

	//HBITMAP					m_hPortraitBitmap;

};
