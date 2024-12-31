// NInvestmentDlg.h: interface for the CNInvestmentDlg class.
//
//////////////////////////////////////////////////////////////////////

/* ==========================================================================
	Ŭ���� :		CNInvestmentDlg

	�ۼ��� :		05/03/29
	�ۼ��� :		���¾�

	��  �� :		.
	                

	��  �� :		
	������� :		����

	�����۾� :		cpp �۾� �Ϸ� ��

   ========================================================================*/
#pragma once


#include <Directives.h>
#include <stdio.h>
#include "../../InterfaceMgr/DialogController.h"


class CStatic;
class CList;
class CButton;


#include "Resource.h"

#define INVESTMENT_GETINFO_MONEY	10000 // ��ȸ��

class CNInvestmentDlg   : public CDialogController
{
public:
	CNInvestmentDlg();
	 ~CNInvestmentDlg();

	static void CALLBACK	StatiCNInvestmentDlgProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl );
	void CALLBACK			NInvestmentDlgProc(UINT nEvent, int nControlID, CControllerObj* pControl);
	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );

	void Create();
	void Set(SI32 npcunique);
	//void Show();
	//void Hide();

	void ShowListData(InvestmentLines* investmentlines);

private:
	

	CStatic     	*m_pInvestmentStatic1;
	CStatic     	*m_pInvestmentStatic2;
	CStatic     	*m_pInvestmentStatic3;
	CList       	*m_pInvestmentList;	
	CButton     	*m_pInvestmentButton1;
	CButton     	*m_pInvestmentButton2;

	BOOL m_bRectSwitch;
	RECT m_rtDlg;
	SI32 m_siNPCCharUnique;
	SI16 m_siItemUnique[MAX_INVESTMENT_ITEM_NUMBER];

};
