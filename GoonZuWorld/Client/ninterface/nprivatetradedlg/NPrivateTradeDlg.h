#pragma once


#include "..\..\..\Resource.h"
#include "../../InterfaceMgr/DialogController.h"
#include "Stock/Stock.h"
#include "Char/CharCommon/Char-EconomyInfo.h"


class CEachPersonTradeOrderInfo;
class CLibListMgr;
class CList;
class CStatic;
class CButton;
class COutLine;
class CEdit;

class cltItem;
class cltRentContract;
class cltHorse;

class CNTradeChild1;
class CNTradeChild2;
class CNTradeChild3;
class CNTradeChild4;

class CNPrivateTradeDlg :public CDialogController
{
public:
	CNPrivateTradeDlg();
	~CNPrivateTradeDlg();


	static void CALLBACK StaticNPrivateTradeDlgProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void CALLBACK NPrivateTradeDlgProc(UINT nEvent, int nControlID, CControllerObj* pControl);

	void Show( SI32 siOtherCharUnique, SI16 TradeMode, SI16 Level, TCHAR *Name, TCHAR *AccountID, SI16 siPrivateTradeOrderMgrIndex, SI16 siPrivateTradeOrderCountIndex, SI32 OtherCharLevel );
	void Create();
	void Action();

	CNTradeChild1 *NTradetabDlg1;
	CNTradeChild2 *NTradetabDlg2;
	CNTradeChild3 *NTradetabDlg3;
	CNTradeChild4 *NTradetabDlg4;




	bool IsShow();	
	//void Hide();
	void ClearPrivateTradeList();
	
	//void LoadStockList();
	bool IsStockListChanged();

	void PrivateTradeOtherListReload();
	void PrivateTradeMyListReload();

	void PrivateTradeOtherListInfo( SI32 Index );
	void PrivateTradeMyListInfo( SI32 Index );
	
	void PrivateTradeAddItem( SI32 siCharUnique, SI32 siAddedIndex, cltItem *pclItem );
	void PrivateTradeDelList( SI32 CharUnique, SI16 DelType, SI16 Param );
	void PrivateTradeDelItem( SI32 siCharUnique, SI16 siDelIndex );
	void PrivateTradeAddPrice( SI32 siCharUnique, GMONEY siPrice );
	void PrivateTradeAddStock( SI32 siCharUnique, SI32 siStockVillageUnique, SI32 siStockNum );
	void PrivateTradeAddHouseUnit( SI32 siCharUnique, SI32 siHouseVillageUnique, SI32 HouseUnitSlot, cltRentContract *pRentContract );
	void PrivateTradeAddHorse( SI32 siCharUnique, SI16 HorseIndex, cltHorse *pclHorse );
	void PrivateTradeMyAccept();
	void PrivateTradeMyCancel();
	void PrivateTradeOtherAccept( SI16 siResult );
	void PrivateTradeOtherCancel();
	void PrivateTradeEnd( SI32 siResult, 
		SI32 RecvStockVillageUnique, SI32 RecvStockNum, 
		SI32 SendStockVillageUnique, SI32 SendStockNum,
		SI32 RecvHouseVillageUnique, SI32 RecvHouseUnitSlot,
		cltRentContract *pclRecvRentContract,
		SI32 SendHouseVillageUnique, SI32 SendHouseUnitSlot, 
		SI16 HorseIndex, cltHorse *pclHorse );
	
	bool GetDelType( SI32 SelectedListIndex, SI16 *pType, SI16 *pParam );

	void PushCancel();
	void PushAddItem();
	void PushDelList();
	void PushDelItem();
	void PushPrice();
	void PushStock();
	void PushHouseUnit();
	void PushHorse();	
	void PushMyAccept();
	void PushMyCancel();	

	bool Pop( BYTE *pData );
	
		

	CEdit               *m_pNPTradeEdit;	
	CButton             *m_pNPTradeButton9;   //�����ϱ�
	SI16		        m_siSelectedModeIndex;	// �ŷ��� �����̳� �� �����ϱ� ���Ѱ�
	//UI32	 	        m_uiLastAcceptFrame;	// �ŷ��� �־����� ����->�������� �������� �����Ͽ��µ� Ŀ��Ʈ Ÿ���� ���� �ϴ� ������ ���� �Ͽ����ϴ�. 2009-03-09 m_uiLastAcceptFrame->m_uiLastAcceptTime
	SI32	 	        m_siLastAcceptTime;	// �ŷ��� �־����� ����->�������� �������� �����Ͽ��µ� Ŀ��Ʈ Ÿ���� ���� �ϴ� ������ ���� �Ͽ����ϴ�. 2009-03-09

	SI32				m_siStockKindList[MAX_STOCK_KIND_IN_ACOUNT];	// �ֽ� ����Ʈ ( ���� )
	SI32				m_siStockNumList[MAX_STOCK_KIND_IN_ACOUNT];		// �ֽ� ����Ʈ ( ���� )
	SI32				m_siStockVillageUnique;	// �ŷ��� ���� �ֽ� ����
	SI32				m_siStockNum;			// �ŷ��� ���� �ֽļ�
	SI32				m_siHouseVillageUniqueList[ MAX_REAL_ESTATE_NUMBER_PER_PERSON ];	// ���� �Ҽ� ����
	SI32				m_siHouseUnitSlotList[ MAX_REAL_ESTATE_NUMBER_PER_PERSON ];			// ���� ��ȣ

	

	SI32                m_siOtherCharLevel;
	GMONEY				m_siPrice;				// �ŷ��� ���� ���� ����
	
	

private:


	COutLine           *m_pNPTradeOutline1; 
	COutLine           *m_pNPTradeOutline2; 
	COutLine           *m_pNPTradeOutline3; 

	CList              *m_pNPTradeList4; 
	CList              *m_pNPTradeList6; 


    CStatic            *m_pNPTradeStatic1;
	
	
	CStatic      *m_pNPTradeStatic3;	
	CEdit      *m_pNPTradeEdit5;	
	CEdit      *m_pNPTradeEdit7;
	CStatic      *m_pNPTradeStatic8;
	CStatic      *m_pNPTradeStatic9;

	CButton      *m_pNPTradeButton1;  // �ӼӸ� ������ ���� ?
	CButton      *m_pNPTradeButton2;  //�ӼӸ� ������
	CButton      *m_pNPTradeButton3;  //��������
	CButton      *m_pNPTradeButton4;  //��, ����
	CButton      *m_pNPTradeButton5;  //�ֽ�
	CButton      *m_pNPTradeButton6;   //��
	CButton      *m_pNPTradeButton7;   //�ε���
	CButton      *m_pNPTradeButton8;   //���� �����
	
	CButton      *m_pNPTradeButton10;  //�����ϱ� ���� ����ǥ
	CButton      *m_pNPTradeButton11;  //������ǰ���� ?

	
	SI16 m_siBitmapAnimationIndex;

	
	bool m_bShow;
	bool m_bMyAccept;

	SI32 m_siAccpetCounter;

	SI32 m_siOtherCharUnique;


	SI16 m_siPrivateTrdeOrderMgrIndex;
	SI16 m_siPrivateTrdeOrderCountIndex;

   
	SI32				m_siMyPrivateTradeListSelectedIndex;	// ���� �÷����� ����Ʈ �߿��� ������ ����
	SI32				m_siOtherPrivateTradeListSelectedIndex;	// ������ �÷����� ����Ʈ �߿��� ������ ����

	cltPItemInfo		*m_pPersonItemInfo;	
	//HBITMAP				m_hItemImage;
	//SI32				m_si32ImageListIndex;
	//bool				m_bIsListRotate;
		


	cltItem				m_clItem[ MAX_ITEM_PER_PERSON ];
	
	

	

	TCHAR				m_strOtherCharName[ MAX_PLAYER_NAME ];	
   CEachPersonTradeOrderInfo *m_pEachPersonTradeOrderInfo;	// �ŷ� ���� ĳ���͸�
   //SI32				m_siStockKindList[MAX_STOCK_KIND_IN_ACOUNT];	// �ֽ� ����Ʈ ( ���� )
	//SI32				m_siStockNumList[MAX_STOCK_KIND_IN_ACOUNT];	

	
	CLibListMgr         *m_pPrivateTradeBufferMgr;
	

};

