#pragma once

#include "../../InterfaceMgr/DialogController.h"
//#include "../common/ItemMallManager/ItemMallManager.h"
#include "../common/item/ItemCommon/ItemMallData.h"
#include "../common/Item/ItemCommon/cltItem.h"
#include "../common/Char/CharCommon/Char-Common.h"
#include "../../DBManager/GameDBManager_World/DBMsg-ItemMall.h"

#include <vector>

typedef std::vector<cltItemMallData>  vecSelectItemMall;
typedef vecSelectItemMall::iterator   vecIterSelectItemMall;

class CButton;
class CImageStatic;
class CStatic;
class CList;
class CCharacterDrawing;

#define DELAYTIME	1500
#define SELECT_ITEM_NUM 6
#define SELECT_HAT		0
#define SELECT_DRESS	1
#define SELECT_MANTLE	2
#define SELECT_ANIMAL	3
#define SELECT_SETITEM1	4
#define SELECT_SETITEM2	5

// ���ο� �����۸�â(���)
class CNNewItemMallDlg : public CDialogController
{
public:

	CNNewItemMallDlg();
	~CNNewItemMallDlg();

	void Create();

	void InitItemMallData();
	void InitSelectItemMallData();
	void InitItemImageStatic();
	void InitEquipItemData();
	void InitSelectEquipItemData( SI16 index );
	void SetImageFontIndex( SI16 selectindex, bool select );
	void LoadItemMallData( SI32 page, SI32 maxpage, cltItemMallData* pclinfo );	// first ���� �޴� ����, second ���θ޴� ����
	void ShowItemMallData();
	void SelectItemList( SI16 SelectIndex );
	void SetCharDraw( SI16 index, SI16 unique );
	void SetCharSetDraw( SI16 index1, SI16 index2, SI16 index3, SI32 unique1, SI32 unique2, SI32 unique3 );
	void SetHaveHorseDraw( SI16 type );
	void SetMyCashInfo(SI32 realcash, SI32 eventcash);
	void ShowBuyWindow(SI16 index);
	void ShowSmallBuyWindow(SI16 index);
	void ShowPresentWindow(SI16 index);
	void DeleteItemList(SI16 index);
	void SelectThreeMenu(TCHAR* code);	// ��, �α�, ����� ������ ��ư
	BOOL ConvertExplain(TCHAR* pText , SI32 size);
	void ShowSiverCoinMark( SI32 index, bool Flag );
	
	void NHNChinaInit( void );
	void NHNChinaGoldItemMall( void );
	void NHNChinaEventItemMall( void );
	void NHNChinaShowCategory( bool	_bShow );


	static void CALLBACK StaticCallBackDialogNNewItemMallDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
	void CALLBACK CallBackDialogNNewItemMallDlg( UINT nEvent, int nControlID, CControllerObj* pControl );

	void DrawDialogLast( SI32 ScreenRX, SI32 ScreenRY  );
	void DrawDialogFirst(SI32 ScreenRX, SI32 ScreenRY );

//	void SetBillPageHandle( HWND* hWnd );
	
	void Action();
 
	BOOL CheckEquipAble(SI32 siItemUnique);

	TCHAR* m_FileName[5];

	//------------------------------
	// ����� ���� ��� �ڵ� 
	//------------------------------
	TCHAR				szHelmetCode[32];
	TCHAR				szArmourCode[32];
	TCHAR				szWeaponCode[32];
	TCHAR				szMantleCode[32];
	TCHAR				szHorseCode[32];	

	cltItem				clCharItem[MAX_SHAPE_ITEM];
	cltAniInfo			clAniInfo;
	CCharacterDrawing*  m_pCharDraw;

	DWORD				m_dwStratClock;			// Ŭ�� ������ ���ؼ�
	DWORD				m_dwLastClock;

	TCHAR				m_szType[4];
	SI32				m_siRealCash;
	SI32				m_siEventCash;
	SI16				m_siAniType;				// ��ź�Ŷ� �� ź�ű���
	SI16				m_siAniDirection;
	bool				m_bHaveHorse;				// ������
	SI16				m_siMaxPageNumber;			// �Ѿ����� ������ ��
	SI16				m_siCurrentPageNumber;		// ������ ������ ��

	SI16				m_siFirstMenuSelect;		// �����޴� ����
	SI16				m_siSecondMenuSelect;		// �����޴� ����
	SI16				m_siTempKey;				// �����޴��� 0~4�� ��ȯ

	SI16				m_siItemListSelect;			// 6���߿� �����ϴ°�!!
	bool				m_bSelect[MAX_ITEMMALL_LIST_NUM];				// ���� or ���
	bool				m_bPreviewSelect[5];		// 0: ����, �Ǻ�, ����, ��, ��Ʈ
	bool				m_bUseMenu;					// 
	SI16				m_siSetItemLoad;
 
	cltItemMallData		m_ItemDataList[MAX_ITEMMALL_LIST_NUM];
	vecSelectItemMall	m_vecSelectItemMall;	// �̸�����â�� ���õ� ������
	SI16				m_siCount;

	CButton*			m_pButtonForward;
//	CButton*			m_pButtonPresent;
	CButton*			m_pButtonExit;

	CImageStatic*		m_pButtonCharacter;			// ĳ����
	CImageStatic*		m_pButtonPower;				// �Ŀ�
	CImageStatic*		m_pButtonSummonHorse;		// ��ȯ/��
	CImageStatic*		m_pButtonMaterialFood;		// ���/����
	CImageStatic*		m_pButtonBeginner;			// �ʺ���	( �߱����� ������ư���� ���� )

	CButton*			m_pButtonNewItem;				// ��������
	CButton*			m_pButtonPopularItem;			// �α������
	CButton*			m_pButtonSpecialItem;			// ����Ⱦ�����

	CImageStatic*		m_pButtonSubject1;			// ���� �޴�1
	CImageStatic*		m_pButtonSubject2;			// ���� �޴�2	
	CImageStatic*		m_pButtonSubject3;			// ���� �޴�3
	CImageStatic*		m_pButtonSubject4;			// ���� �޴�4
	CImageStatic*		m_pButtonSubject5;			// ���� �޴�5

	CButton*			m_pButtonBuy1;					// ���� ��ư1
	CButton*			m_pButtonBuy2;
	CButton*			m_pButtonBuy3;
	CButton*			m_pButtonBuy4;
	CButton*			m_pButtonBuy5;
	CButton*			m_pButtonBuy6;

	CButton*			m_pButtonPresent[6];
//	CButton*			m_pButtonPresent1;				// ���� ��ư1
//	CButton*			m_pButtonPresent2;
//	CButton*			m_pButtonPresent3;
//	CButton*			m_pButtonPresent4;
//	CButton*			m_pButtonPresent5;
//	CButton*			m_pButtonPresent6;

	CButton*			m_pButtonReset;					// �̸� ����â �ʱ�ȭ
	CButton*			m_pButtonNcoin;					// ������ �����ϱ�

	CButton*			m_pButtonPrev;					// ������ ��� ��������
	CButton*			m_pButtonNext;					// ������ ��� ��������

	CButton*			m_pButtonSmallBuy[4];			// ���õ� ������ ��� ��ư
	CButton*			m_pButtonSmallNo[4];			// ���õ� ������ ���� ��ư

	CButton*			m_pButtonLeftTurn;				// �̸� ���⿡�� ���� ��ȯ
	CButton*			m_pButtonRightTurn;

	CButton*			m_pButtonGoldItemMall;			// [����] �Ϲ� �����۸�
	CButton*			m_pButtonEventItemMall;			// [����] �̺�Ʈ �����۸�
	CButton*			m_pButtonEventItemMallExplain;	// [����] �̺�Ʈ �����۸��� �Ǿ��� �� ���̴� ��ư. (�ϴ� ���̱⸸) 
	CButton*			m_pButtonEventMoneyInfo;		// [����] �̺�Ʈ �� ��ȸ.

	//CButton*			m_pButtonFreeReplenishment;		// ����������

	CImageStatic*		m_pISItem[6];					// ������ ��� �̹��� 6�� ���ý�(��Ʈ1��) ���� �ȵǸ�(��Ʈ 0��)
	CImageStatic*		m_pISShowItem[6];				// �������� ������ �׸�
	CImageStatic*		m_pISItemName[6];				// �������� �۾�

	CStatic*			m_pStaticItemPrice[6];			// �������� ����
	CStatic*			m_pStaticItemEventPrice[6];		// [����] �̺�Ʈ �������� ����
	
	CStatic*			m_pStaticCurrentPage;			// ���� ������
	CStatic*			m_pStaticMaxPage;				// �� ������
	CStatic*			m_pStaticCurrentPage1;			// ���� ������ (10�ڸ�)
	CStatic*			m_pStaticMaxPage1;				// �� ������ (1�ڸ�)

	CStatic*			m_pStaticMyNcoin;				// ���� ���� ������ ( �߱��� ���� )
	CStatic*			m_pStaticEvenyMoney;			// ���� ���� �̺�Ʈ �Ӵ�( �߱��� ���� )

	CList*				m_pList;						// ���õ� ������ ����Ʈ

	CStatic*			m_pStaticSilverCoin[6];			// ���� �׸� 6��

	CButton*			m_pButtonGetItem;				// �߱����� ���ϴ�. ������ ����â ����

	TSpr	    		m_SprBack;						// 1024*768 ��ü ȭ�鿡���� ���� ���׸�

//	HWND				m_BillPageHandle;
	BOOL				m_bBillPageActive;
	bool				m_bEventItemMall;				// �̺�Ʈ ������.
};