#pragma once

#include "../../InterfaceMgr/DialogController.h"
#include "..\CommonLogic\PostOffice\PostOffice.h"
#include "../../../common/Item/ItemCommon\cltItem.h"

class CButton;
class CStatic;
class CList;
class CComboBox;

class cltItem;
class cltSaveUersItemInfo;

#define BASIC_MARKETCONDITIONS_CHARGE 5000 //

// ���� ������ ã��
class CNMarketConditionsDlg : public CDialogController
{
public:

	CStatic*			m_pStatic[2];
	CList*			m_pList;
	CButton*			m_pButton[5];
	CComboBox*		m_pComboBox[2];

	SI32			m_siNPCCharUnique;
	SI32			m_selectWhatShowList; // 1 = �Ϲݰ˻�,  2 = ���� ���, 3 = ������ �ü�.

	SI32			m_siItemTypeIndex;	// ǰ�� �ε���
	SI32			m_siItemIndex;	// ǰ�� �ε���

	SI32			m_arrTypeIndex[MAX_ITEMTYPE_NUMBER]; // ǰ�� ���.
	SI16			m_arrItemIndex[100]; // ���õ� ������ ���. - ���� ���� �ʰ���.;;

	// ������ ���� ���� ���� ����.
	cltMarketConditionsInfo 		m_MarketConditionsInfo[100];
	_SYSTEMTIME				m_sTimeMarketConditionsInfo[8]; // 3= ������ �ü��� ����.	

	CNMarketConditionsDlg();
	~CNMarketConditionsDlg();

	void Create();

	void Set(SI32 npcunique);

	static void CALLBACK StaticCallBackDialogNMarketConditionsDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
	void CALLBACK CallBackDialogNMarketConditionsDlg( UINT nEvent, int nControlID, CControllerObj* pControl );

	void	 ShowList( cltMarketConditionsInfo * pclMCInfo , _SYSTEMTIME* pStimeMCInfo);

	void	 SetItemTypeInComboBox(BOOL bshowall);
	BOOL	 ShowItemListInComboBox(CComboBox* pComboBox, SI32 typeindex, bool btradeinterface);

	void	 RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );

};

