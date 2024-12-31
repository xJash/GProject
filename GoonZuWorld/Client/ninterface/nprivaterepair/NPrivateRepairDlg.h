#pragma once

#include "..\..\..\Resource.h"
#include "../../InterfaceMgr/DialogController.h"
#include "Item/ItemCommon/ItemUnit.h"
#include "../NPrivateTradeDlg/PrivateTradeBaseInfo.h"

class CEachPersonTradeOrderInfo;
class CLibListMgr;
class CList;
class CListView;
class CStatic;
class CButton;
class CEdit;

class cltItem;
class cltRentContract;
class cltHorse;
class cltPItemInfo;


class CNPrivateRepairDlg :public CDialogController
{
public:
	CNPrivateRepairDlg();
	~CNPrivateRepairDlg();


	static void CALLBACK StaticNPrivateRepairDlgProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void CALLBACK NPrivateRepairDlgProc(UINT nEvent, int nControlID, CControllerObj* pControl);

	void Show( SI32 siOtherCharUnique, SI16 TradeMode, SI16 Level, TCHAR *Name, TCHAR *AccountID, SI16 siPrivateTradeOrderMgrIndex, SI16 siPrivateTradeOrderCountIndex, SI32 OtherCharLevel );
	void Create();
	void Action();



	bool IsShow();
	
	void ClearPrivateTradeList();		
	void LoadInventoryData();
	bool IsInventoryChanged();

	void PrivateTradeOtherListReload();
	void PrivateTradeMyListReload();
	void PrivateTradeOtherListInfo( SI32 Index );
	void PrivateTradeMyListInfo( SI32 Index );
	
	void PrivateTradeAddItem( SI32 siCharUnique, SI32 siAddedIndex, cltItem *pclItem );
	void PrivateTradeDelList( SI32 CharUnique, SI16 DelType, SI16 Param );
	void PrivateTradeDelItem( SI32 siCharUnique, SI16 siDelIndex );
	void PrivateTradeAddPrice( SI32 siCharUnique, GMONEY siPrice );	
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
	void PushMyAccept();
	void PushMyCancel();
	bool Pop( BYTE *pData );
	
	
	
	CEdit            *m_pNTRepairEdit1;

private:

	CStatic          *m_pNTRepairStatic1;
	CStatic          *m_pNTRepairStatic2;
	CStatic          *m_pNTRepairStatic3;
	CList            *m_pNTRepairList1;
	CList            *m_pNTRepairList2;
	
	CEdit            *m_pNTRepairEdit2;
	CEdit            *m_pNTRepairEdit3;
	CEdit            *m_pNTRepairEdit4;
	CListView        *m_pNTRepairListView;
	CButton          *m_pNTRepairButton1;  //�ӼӸ� ������ 
	//CButton          *m_pNTRepairButton2;  //���� ���� ���� 
	CButton          *m_pNTRepairButton3;  //���� ��ǰ �ø��� 
	CButton          *m_pNTRepairButton4;  //���� ��ǰ ������ 
	CButton          *m_pNTRepairButton5;   //�Է� ��ư 
	CButton          *m_pNTRepairButton6;   // �Է� help ��ư
	CButton          *m_pNTRepairButton7;   //�����ϱ�
	CButton          *m_pNTRepairButton8;  // �����ϱ� help ��ư 


    



	SI16		        m_siSelectedModeIndex;	// �ŷ��� �����̳� �� �����ϱ� ���Ѱ�
	UI32	 	        m_uiLastAcceptFrame;	// �ŷ��� �־����� ����
	SI32                m_siOtherCharLevel;
	GMONEY				m_siPrice;				// �ŷ��� ���� ���� ����
	SI32                m_siInvSelectedIndex;
	
	
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
	cltItem				m_clItem[ MAX_ITEM_PER_PERSON ];
	cltItem             m_clUserItem[MAX_ITEM_PER_PERSON];
	

	TCHAR  				          m_strOtherCharName[ MAX_PLAYER_NAME ];	  
	CEachPersonTradeOrderInfo    *m_pEachPersonTradeOrderInfo;	// �ŷ� ���� ĳ���͸�	
	CLibListMgr                  *m_pPrivateTradeBufferMgr;	

};

