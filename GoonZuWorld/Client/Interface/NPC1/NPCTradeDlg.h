#ifndef _NPCTRADEDLG_H_
#define _NPCTRADEDLG_H_

#include "NPCTradeBaseInfo.h"

class	CNPCTradeBuffer;
#define MAX_AVAILABLE_CASHITEMNUM		256

class CNPCTradeDlg
{
public:
	CNPCTradeDlg();
	~CNPCTradeDlg();

	void	Initialize();
	void	Destroy();

	void	Create( HINSTANCE hInst, HWND hWnd, cltPItemInfo *pPersonItemInfo, cltNPCItemInfo *pNPCItemInfo );

	
	static BOOL CALLBACK StaticNPCTradeDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
	BOOL CALLBACK NPCTradeDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);

	bool	IsUserInventoryChanged();						// ���� �κ��丮�� �ٲ� ���� �ִ��� üũ
	bool	IsNPCInventoryChanged();						// NPC �κ��丮�� �ٲ� ���� �ִ��� üũ

	void	LoadUserInventory();							// ���� �κ��丮 ������ �ε�
	void	LoadNPCInventory();								// NPC  �κ��丮 ������ �ε�

	void	SellItemToNPC();								// ������ NPC ���� �������� �Ǹ�
	void	BuyItemFromNPC();								// NPC �� ���� ������ ������ ����

	void	UpdateUserInventory();							// ������ �������� �Ȱų� ������ �ÿ� ������ ���� �����͸� �޾Ƽ� ����Ǿ�����, �� �� update �� �ֱ� ���ؼ�...
	void	UpdateNPCInventory();							// NPC�� �κ��丮�� ���� ���� ���� ������, Ȥ�ó� ������ ���� ���� �����Ƿ�...
	
	void	Show(SI32 charunique);							// ���̾�α� ���� �ֱ�	
	void	Hide();											// ���̾�α� �����

	bool	IsShow();

	bool	Pop( stNPCTradeData * pNPCTradeData );			// ������ �������� �Լ�

	void	SetText( char *strText );						// �Ȱų� ��ų� ������ ��Ȳ�� ������� �ϹǷ�...
	void	SetText( SI32 siTextIndex );					// �Ȱų� ��ų� ������ ��Ȳ�� ������� �ϹǷ�...
	bool    LoadBuyCashItemInfo();
	bool    IsSameItemTypeExist( char *ItemType );
	bool    IsCheckCashItem(SI32 Uinque);



private:
	cltItem					m_clUserItem[ MAX_ITEM_PER_PERSON ];
	SI32					m_siUserItemPrice[ MAX_ITEM_PER_PERSON ];

	cltItem					m_clNPCItem[ MAX_NPC_ITEM_NUMBER ];
	SI32					m_siNPCItemPrice[ MAX_NPC_ITEM_NUMBER ];

	cltPItemInfo			*m_pPersonItemInfo;
	cltNPCItemInfo			*m_pNPCItemInfo;

	HWND					m_hDlg;
	HWND					m_hUserInventory;
	HWND					m_hNPCInventory;
	HWND					m_hNPCTradeInfoViewEdit;
	bool					m_bShowFlag;


	CNPCTradeBuffer			*m_pNPCTradeBuffer;

	SI32					m_siUserInventorySelectedIndex;
	SI32					m_siNPCInventorySelectedIndex;

	SI32					m_siSellItemNum;
	SI32					m_siBuyItemNum;
	
	SI32					m_siNPCCharUnique;
	SI32					m_siNPCKind;

	HBITMAP					m_hPortraitBitmap;

	char m_strItemTypeList[ MAX_ITEMTYPE_NUMBER ][ 64 ];
	SI16 m_siItemUniqueList[ MAX_AVAILABLE_CASHITEMNUM ];
	UI16 m_uiItemPriceList[ MAX_AVAILABLE_CASHITEMNUM ];

};

#endif