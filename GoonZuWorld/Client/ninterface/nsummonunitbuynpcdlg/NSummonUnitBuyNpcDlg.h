#pragma once 

#include "../../InterfaceMgr/DialogController.h"

class CImageStatic;
class CButton;
class CComboBox;
class CListView;
class CEdit;
class CStatic;
class CList;

#define TRADE_SUMMONRANK	6

class CNSummonUnitBuyNpcDlg : public CDialogController
{
public:

	CNSummonUnitBuyNpcDlg();
	~CNSummonUnitBuyNpcDlg();

	void Create();
	void Action();

	static void CALLBACK StaticCallBackDialogNSummonUnitBuyNpcDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
	void CALLBACK CallBackDialogNSummonUnitBuyNpcDlg( UINT nEvent, int nControlID, CControllerObj* pControl );

	void LoadSummonUnit(SI32 siSummonUnitId);
	void CheckSummonUintLevel();	// ��ȯ�� ��ȭ�ܰ� üũ
	void CheckTicketNumber(SI32 siSummonUnitRank);
	void SellToNPCSuccess();
	void SetSummonPrice(SI16 siIndex, GMONEY siSummonPrice);

	void Set( SI32 NPCCharUnique );

	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );

private:

	SI16 m_siSummonUnitIndex;		//	��ȯ�� �ε��� 0, 1��
	SI16 m_siSummonUnitRank;	//	��ȯ�� ���
	SI32 m_siUseTicketNumber;	//	��ȭ�̿�� ����
	SI32 m_siTicketValue;		//  ��ȭ�̿�ǰ�
	GMONEY m_siSelectSummonPrice;	//  ��ȯ���� �ȸ� ����
	REAL32 m_fRate;				//  ��ȯ�� ��� ������

	CStatic*	m_pStatic[2];		// 0 : ��ȯ�� ��� ���� ��, 1: ��ȯ�� ��
	CEdit*		m_pEdit[2];			// 0 : ��ȯ�� ������ �ϴ¸�   1: ��ȯ�� �ɷ�ġ

	CButton*	m_pBtnSummonUnitSell;
	CButton*	m_pBtnClose;
};