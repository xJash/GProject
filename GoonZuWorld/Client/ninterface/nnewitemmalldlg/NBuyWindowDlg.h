#pragma once

#include "../../InterfaceMgr/DialogController.h"
//#include "../common/ItemMallManager/ItemMallManager.h"
#include "../common/Item/ItemCommon/ItemMallData.h"

class CButton;
class CStatic;
class CEdit;
class CRadioButton;

class CNBuyWindowDlg : public CDialogController
{
public:

	SI32			m_siMyNcoin;
	SI32			m_siMyEventCoin;			// [����] �߱������� ���� �̺�Ʈ �Ӵ�.
	SI32			m_siRealCoin;				// �����̸� ����, �����̸� ����
	SI32			m_siSelectProductKey;
	SI32			m_siSelectItemPrice;		// ����
	SI32			m_siSelectItemEventPrice;	//[����] �߱� �����۸����� ����ϴ� �̺�Ʈ �Ӵ�.
	SI32			m_siBuyItemNum;

	TCHAR			m_szSelectItemName[50];
	bool			m_bAgeLimit;				//[����] �ŷ�����. KOR: ����, ENG: ���� => 2008-9-22

	cltItemMallData	m_clItemData[3];

	CButton*		m_pButton[5];
	CRadioButton*	m_pRadioButton[3];
	CStatic*		m_pStatic[21];
	CEdit*			m_pEdit;
	CEdit*			m_pEditExplain;

	//[����] �߱� �����۸� ���� �������̽�.
	CStatic*		m_pEventStaticBack;
	CStatic*		m_pEventStatic[9];

	CNBuyWindowDlg();
	~CNBuyWindowDlg();

	void Create();

	static void CALLBACK StaticCallBackDialogNBuyWindowDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
	void CALLBACK CallBackDialogNBuyWindowDlg( UINT nEvent, int nControlID, CControllerObj* pControl );

	void InitItemData();

	void SetBuyItemInfo(cltItemMallData& pitemmalldata);

	// �Ⱓ�� �������� 2�ܰ�� ����� üũ�Ѵ�
	void SetBuyFirstItemInfo(TCHAR* explain, TCHAR* explain2, TCHAR* itemname, SI32 itemfontindex);
	void SetBuyDateItemInfo(cltItemMallData* pitemmalldata);

	void SetCashInfo(SI32 mycash, SI32 myeventcash, bool showsilvercoinmark );

	// ���� üũ
	void SelectRadioButton( SI16 index );

	void ShowSiverCoinMark( bool Flag );

	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );

	void NHNChinaInit( void );
	void NHNChinaItemSet( void );
};


class CNBuySecondWindowDlg : public CDialogController
{
public:

	enum { BUY = 0, PRESENT };
	UI08			m_uiMode;

	SI32			m_siSelectProductKey;
	SI32			m_siSelectItemPrice;
	SI32			m_siSelectItemEventPrice;
	
	SI32			m_siSelectBuyItemNum;

	TCHAR			m_szSelectItemName[50];

	TCHAR			m_szGetAccountID[MAX_PLAYER_NAME] ; // ���� ���� ��� AccountID
	TCHAR			m_szComment[200];

	SI16			m_siGetServerUnique;
	TCHAR			m_szGetCharName[MAX_PLAYER_NAME];
	SI32			m_siItemImageFont;

	InterfaceFactory	m_InterfaceFactory;

	CNBuySecondWindowDlg();
	~CNBuySecondWindowDlg();

	void Create();

	static void CALLBACK StaticCallBackDialogNBuySecondWindowDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
	void CALLBACK CallBackDialogNBuySecondWindowDlg( UINT nEvent, int nControlID, CControllerObj* pControl );

	void SetBuyInfo( SI32 SelectProductKey, SI32 BuyItemNum, SI32 SelectItemPrice, SI32 SelectItemEventPrice, TCHAR* SelectItemName );
	void SetPresentInfo( TCHAR*getid,SI32 key,SI32 num,SI32 price,SI32 Eventprice,TCHAR*comment,TCHAR* itemname,SI16 ServerUnique,TCHAR* CharName,SI32 ItemImageFont );
};