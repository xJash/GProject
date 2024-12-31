#ifndef _LISTVIEW_H_
#define _LISTVIEW_H_

#include "../ControllerObj.h"
#include "Scroll.h"


#define MAX_LISTVIEW_DUPLICATE_ITEM_NUM		30000			// ��ø ������ ���� ���� ( ���� 30000 �� ���� �� �����Ŷ�� ������ )

#define MAX_LISTVIEW_ITEM_NUM				128				// ������ ����
#define MAX_LISTVIEW_ITEM_NAME_LENGTH		64				// ������ �̸� ���� ����

class CToolTip;

#define LISTVIEW_ITEMMASK_SEALED		0x00000001
#define LISTVIEW_ITEMMASK_EXPIRED		0x00000002
#define LISTVIEW_ITEMMASK_CANNOTEQIP	0x00000004

struct stListViewItemData
{
	SI16 ImageFileIndex;									// ���° �̹��� ���Ͽ� �ִ���...
	SI16 ImageFontIndex;									// �̹��� ���� ���° Font
	SI16 ItemListViewPos;									// ����Ʈ �� ���� ��ġ	
	SI16 ItemNum;
	TCHAR ItemName[ MAX_LISTVIEW_ITEM_NAME_LENGTH ];			// ���� ������ �̸����� �����δ� "���� 3��" �̷������� ���� ���ڿ��� ���Ե�
	TCHAR ToolTipMsg[ MAX_TOOLTIP_MSG_SIZE ];				// ���� Msg
	SI16 bDrawAlphaOption;		// �̹����� �׷��ٶ��� �ɼ�( ������ ��)
	bool bItemSealed;			// ���εǾ����� ����
	SI32 siItemMask;			// by LEEKH 2007.10.11 - ������ ǥ�� ����ũ

	stListViewItemData()
	{
		memset( this, 0, sizeof( stListViewItemData ) );
	}

	stListViewItemData( stListViewItemData *pItemData )
	{
		memcpy( this, pItemData, sizeof( stListViewItemData ) );
	}

	void Init()
	{
		ZeroMemory(this, sizeof(*this));
	}

	void Set( stListViewItemData *pListViewItemData )
	{
		memcpy( this, pListViewItemData, sizeof( stListViewItemData ) );
	}

	void Set( SI16 FileIndex, SI16 FontIndex, SI16 ListViewPos, SI16 Num, TCHAR *Name, TCHAR *TipMsg,BOOL DrawAlphaOption = false, bool ItemSealed = false)
	{
		ImageFileIndex = FileIndex;
		ImageFontIndex = FontIndex;
		ItemListViewPos = ListViewPos;		
		ItemNum = Num;
		
		if ( Name )
		{
			_tcsncpy( ItemName, Name, MAX_LISTVIEW_ITEM_NAME_LENGTH - 1 );
			ItemName[ MAX_LISTVIEW_ITEM_NAME_LENGTH - 1 ] = NULL;
		}
		if ( TipMsg )
		{
			_tcsncpy( ToolTipMsg, TipMsg, MAX_TOOLTIP_MSG_SIZE - 1 );
			ToolTipMsg[ MAX_TOOLTIP_MSG_SIZE - 1 ] = NULL;
		}

		bDrawAlphaOption = DrawAlphaOption;
		bItemSealed = ItemSealed;

		if(ItemSealed)	siItemMask = siItemMask | LISTVIEW_ITEMMASK_SEALED;
	}

	void SetSealed(bool bSealed)
	{
		bItemSealed = bSealed;
		if(bSealed)
			siItemMask = siItemMask | LISTVIEW_ITEMMASK_SEALED;
		else
			siItemMask = siItemMask - LISTVIEW_ITEMMASK_SEALED;
	}

	void SetExpired(bool bExpired)
	{
		if(bExpired)
			siItemMask = siItemMask | LISTVIEW_ITEMMASK_EXPIRED;
		else
			siItemMask = siItemMask - LISTVIEW_ITEMMASK_EXPIRED;
	}

	void SetCanNotEquip(bool bCanNotEquip)
	{
		if(bCanNotEquip)
			siItemMask = siItemMask | LISTVIEW_ITEMMASK_CANNOTEQIP;
		else
			siItemMask = siItemMask - LISTVIEW_ITEMMASK_CANNOTEQIP;
	}

};

class CListView : public CControllerObj
{
public:
	CListView( CControllerMgr *pParent );
	CListView( CControllerMgr *pParent,SI32 siTmpBufferSize );

	~CListView();

	void Init();

	void Create( SI16 ControllerID,
		TCHAR *FileName, SI16 FontIndex, bool BKTileImg, SI16 BKTileImgNum,
		SI16 XPos, SI16 YPos, SI16 Width, SI16 Height, 
		SI16 SurfaceWidth, SI16 SurfaceHeight, 
		SI16 ListViewOffsetX, SI16 ListViewOffsetY,
		SI16 ListViewItemOffsetX, SI16 ListViewItemOffsetY,
		SI16 ListViewItemSizeWidth, SI16 ListViewItemSizeHeight,
		bool AllowEmptyItemPos, bool ItemNumShow,
		bool UseToolTip, SI16 ToolTipWidth, SI16 ToolTipHeight );
	
	bool InsertItem( stListViewItemData *pItemData );
	bool UpdateItem( stListViewItemData *pItemData );
	bool DeleteItem( SI16 ItemPos );
	void DeleteAllItems();
	bool ChangeItemNum( SI16 ItemPos, SI16 ItemNum );
	bool ChangeItemPos( SI16 PreItemPos, SI16 NextItemPos );

	void SetFocus( bool HasFocus );
	void ClearSelectedItem();

	SI16 GetMouseSelectedItemIndex( LONG XPos, LONG YPos );
	SI16 GetItemIndexFromPoint( POINT pt, bool AbsolutePoint = false );			// ��ǥ�� ������ Index ������

	SI16 GetSelectedItemIndex();
	SI16 GetLastSelectedItemIndex();	

	// Ű����δ� ������ ���� ���� �� ����Ű �Է½� Ȯ�� ����� �� �� ����.
	//bool HandleKeyboard( UINT uMsg, WPARAM wParam, LPARAM lParam );
	bool HandleMouse( UINT uMsg, POINT pt, WPARAM &wParam, LPARAM &lParam );
	
	void DrawController( SI16 BaseXPos, SI16 BaseYPos, SI32 LeftTime = 0 );
	void DrawItemNumber( SI16 DrawXPos, SI16 DrawYPos, SI16 ItemNum );

	void SetStartItemPos( SI16 StartItemPos )
	{
		m_siListViewStartItemPos = StartItemPos;
	}

	void UpdateScrollPos();	
	void Refresh();
	
	stListViewItemData *GetListViewItemData( SI16 Index );

	void SetBorder( bool Border );
	void SetBKColorUse( bool BKColorUse );
	void SetItemNumShow( bool ItemNumShow );
	
	void SetItemDrawAlphaOption( SI16 ItemPos,  bool DrawAlphaOption = true );//[����] �������� ������ ����� ���Ƿ� �����ϱ� ���ؼ�

	void SetListViewBorderAndBKColorUse( bool Border, bool BKColorUse );

	SI32 GetScrollTrackPos()
	{
		return m_pScroll->GetTrackPos();
	}

	void SetScrollTrackPos( SI32 siPosition )
	{
		m_pScroll->SetTrackPos( siPosition );
	}

	void SetUseToolTip( bool bUseToolTip )
	{
		m_bUseToolTip = bUseToolTip;
	}

	// ����Ʈ�� ��ϵ� ��ü ����.
	SI16 GetListViewItemCounter( void )
	{
		return m_siListViewItemCounter;
	}
	
private:
	CScroll *m_pScroll;				// ��ũ�� �κ�

	bool m_bLMPressed;				// ���� ���콺 ��ư
	bool m_bRMPressed;				// ������ ���콺 ��ư
	

	// �ʱ� �� ���� ����( index = -1 )
	// ���� ���� ( �������� �ణ ����� ���̰ų� �׷����� )
	SI16 m_siSelectedIndex;			// ���õ� �������� Index, ���õ��� �ʾҴٸ� -1 ����
	SI16 m_siLastSelectedIndex;		// ������ �������� �ִٸ� �� Index, ������ ����, ������ ��� ���� Index
									// m_siLastSelectedIndex �� �� �� ������ ������ ������, ������ ���� ��쿡 ���� üũ�� �ʿ��ϰ���.. �׷��� Ư���� ��찡 �ƴ϶�� m_siSelectedIndex �̰��� ����ϱ� �ٶ�
	SI16 m_siMouseOverItemIndex;	// Mouse Over �ÿ� ���� ������� ������.
									// bAllowEmpty true ���¶�� �̰�(m_siMouseOverItemIndex)�� false ���¶� Ʋ��...( ������ �ִٸ�... )

	SI16 m_siMaxHorizontalItemNum;	// ���ٿ� ��� �������� ������... ���� ���缭 �־�� ������...

	bool m_bItemExplainShow;		// ������ ����( ex : �׵� 2�� ) ������ �Ʒ��� ���ڸ� ���� ������ ���� flag
									// �� ���� �൵ �ɵ�. �������� �����ִ� �ɷ� ���
									// ��ø�� �������� ��� ������ �۰� �̹������� ���ڷ� ��� �𼭸��ʿ� ���� �ָ� ������.

	bool m_bItemNumShow;			// ������ ������ �𼭸� �κп� �����ٷ��� �ϴµ�, ���� �� �ʿ䰡 ���� ��쵵 ��������...
									// ������ � ���� �̹����� ���� ��쵵 ��������...

	bool		m_bUseToolTip;		// ����

	SI16 m_siListViewOffsetX;		// ListView �̹����� OffSet X
	SI16 m_siListViewOffsetY;		// ListView �̹����� OffSet Y

	SI16 m_siListViewItemOffsetX;	// ListView �������� OffSet X
	SI16 m_siListViewItemOffsetY;	// ListView �������� OffSet Y

	SI16 m_siListViewItemSizeWidth;	// ListView ������ �ϳ��� �����ϴ� ����(Width)
	SI16 m_siListViewItemSizeHeight;// ListView ������ �ϳ��� �����ϴ� ����(Height)

	bool m_bAllowEmptyItemPos;		// ����Ʈ��� 2����( � �ڸ�[(ex)3��° �ڸ�]�� ����ٸ�, 4��° �ڸ��� �ִ� �������� �����ִ� �͸� 3��° �ڸ��� ä������ �������� �����, �� ĭ�� ����ΰ� �����ִ� ��� 2������ ���� )

	SI16 m_siListViewItemCounter;

	stListViewItemData	*m_pListViewItemData[ MAX_LISTVIEW_ITEM_NUM ];

	SI16 m_siListViewStartItemPos;	// ����Ʈ�䰡 ������ ����Ʈ�� �߰������� ����� �� �ֱ� ����.

	RGB16*	m_ImgEncBuffer;

	SI32 m_siPreScrollPos;			// Update ����� ���� �ƾ��ٸ�, �̰� �ʿ���� ������
};

#endif
