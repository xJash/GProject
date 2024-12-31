#ifndef _NFOREIGNMERCHANTBuyItem_H_
#define _NFOREIGNMERCHANTBuyItem_H_


#include "../../InterfaceMgr/DialogController.h"
#include "Msg/MsgType-NPC.h"
//#include "../Client/Interface/ForeignMerchant/ForeignMerchantBaseInfo.h"

class CImageStatic;
class CButton;
class CComboBox;
class CListView;
class CEdit;
class CStatic;
class CList;

class cltPItemInfo;
class CLibListMgr;
class CForeignMerchantNPC;

#define FOREIGNMERCHANTDLG_SETTIMER_TIME			1000

#define MAX_FOREIGN_MERCHANT_OBJ_NUM				30
#define MAX_FOREIGN_MERCHANT_OBJ_BUFFER_SIZE		128		// 128 byte �� ���

struct stForeignMerchantHeader
{
	UI16 uiMsg;
	UI16 uiSize;
};

struct stSellToForeignMerchant
{
	stForeignMerchantHeader sHeader;
	SI16					siForeignMerchantKind;		// ���� ����(�Ϻ� ����, û����)
	UI16					uiSelectedIndex;			// ������ ��ġ (�翬�� 10�̻��� ���̰���... ����â������ �ٷ� �ȼ� �����Ƿ�... )
	UI16					uiSellItemNum;				// ������ �Ǹ� ����
	SI16					siSellItemUnique;			// ������ ����ũ ��, <--- ������ ���輺 ������... �Ⱓ�� ������ �������� �ٸ� ���������� ����Ǵ� ���ȿ� ������ ��Ŷ�� ��쿡 ���� ���å

	SI32					siNPCCharUnique;			// NPC CharUnique

	stSellToForeignMerchant()
	{
		siForeignMerchantKind = 0;
		uiSelectedIndex = 0;
		uiSellItemNum = 0;
		siSellItemUnique = 0;
		siNPCCharUnique = 0;

		sHeader.uiMsg = SELL_TO_FOREIGNMERCHANT;
		sHeader.uiSize = sizeof( stSellToForeignMerchant );
	}
};

struct stNForeignMerchantBuyItemData
{
	stSellToForeignMerchant *pSellToForeignMerchant;
	SI16 siParam;
};

class CNForeignMerchantBuyItemDlg : public CDialogController
{
public:

	CNForeignMerchantBuyItemDlg();
	~CNForeignMerchantBuyItemDlg();

	void Create();
	void Action();

	static void CALLBACK StaticCallBackDialogNForeignMerchantBuyItemDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
	void CALLBACK CallBackDialogNForeignMerchantBuyItemDlg( UINT nEvent, int nControlID, CControllerObj* pControl );
	
	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );

	void SetNormalItemBuyMode(SI32 NPCCharUnique);

	void SetData(void *pBuffer );
//////////////////////////////////////////////////////////////////////////////////////////////
//	�Ϲ� ������ ����
	void LoadInventoryData();
	void LoadForeignNPCData();

	bool IsInventoryChanged();
	bool IsNPCBuyItemInfoChanged();

	void Push( UI16 uiSellItemNum );
	bool Pop( stSellToForeignMerchant *pSellToForeignMerchant );
	void EnableButton(CButton* pButton, BOOL Flag);	// ��ư Ȱ��ȭ ��Ȱ��ȭ
//////////////////////////////////////////////////////////////////////////////////////////////

private:

	SI32				m_siImageType;	// ���� �̹��� ����
	SI32				m_siImageIndex;	// ���� �̹��� �ε���
	SI16				m_siForeignMerchantKind;
	SI32				m_siSelectedIndex;
	SI32				m_siListBoxSelectedIndex;
	SI32				m_si32ImageListIndex;
	SI32				m_siNPCCharUnique;
	SI32				m_siItemType;

	bool				m_bIsListRotate;

	cltItem						m_clItem[ MAX_ITEM_PER_PERSON ];		// ������ �������� üũ�� �ʿ� �����Ƿ�...
	cltPItemInfo				*m_pPersonItemInfo;	
	CLibListMgr					*m_pForeignMerchantMgr;
	CForeignMerchantNPC			*m_pForeignMerchantNPC;
	stForeignMerchantNPCInfo	m_ForeignMerchantNPCInfo;

	

	CStatic*	m_pStatic[6];
	CEdit*		m_pEdit[2];
	CComboBox*	m_pCombo;
	CList*		m_pList;
	CListView*	m_pListView;
	CButton*	m_pButtonSellItem;
	CButton*	m_pButtonClose;
};

#endif
