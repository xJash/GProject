#pragma once

#include "../../InterfaceMgr/DialogController.h"

class CButton;
class CStatic;
class CList;
class COutLine;
class CEdit;

// ��ť �ŷ�â
class CNAqTradeWindowDlg : public CDialogController
{
public:
	CButton*	m_pButton[5];
	CStatic*	m_pStatic[13];	// 2: ����ȯ��, 5: ����, �ѱݾ�:10
	CList*		m_pList;
	CList*		m_pMyWorldMoneyList;
	COutLine*	m_pOutLine[3];

	CEdit*		m_pEditExplain;	// ��ť ������ ����
	CEdit*		m_pEditSellAq;	// �� ��ť��
	CEdit*		m_pEditAqPrice;	// 1��ť�� �ݾ�
	CEdit*		m_pEditBuyAq;	// ����� ��ť��

	SI64		m_siSellWorldMoneyNum;	// �� ��ť��
	SI64		m_siSellWorldMoneyPrice; // �� ��ť�� �ݾ�

	SI64		m_siAverageWorldMoneyPrice; // ��ť�� �ü�

	CNAqTradeWindowDlg();
	~CNAqTradeWindowDlg();

	SI32 siListIndex[MAX_LISTBOX_ITEM_NUM];
	SI32 siSelectedIndex;

	void Create();

	static void CALLBACK StaticCallBackDialogNAqTradeWindowDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
	void CALLBACK CallBackDialogNAqTradeWindowDlg( UINT nEvent, int nControlID, CControllerObj* pControl );

	void SetTradeList();
	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );
};