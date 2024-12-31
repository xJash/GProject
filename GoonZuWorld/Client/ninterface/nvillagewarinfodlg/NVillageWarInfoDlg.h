// VillageWarInfoDlg.h: interface for the CNVillageWarInfoDlg class.
//
//////////////////////////////////////////////////////////////////////

//---------------------------------
// 2005/3/8 
//---------------------------------
/* ==========================================================================
	Ŭ���� :		cltNVillageDetailInfoManager

	�ۼ��� :		05/03/08       // 05/03/28 �Ϸ�  
	�ۼ��� :		���¾�

	��  �� :		

	��  �� :		

	������� :		����
	
	�����۾� :		cpp �۾� �Ϸ� ���

   ========================================================================*/



//#if !defined(AFX_VILLAGEWARINFODLG_H__037A6596_8567_4FB7_BF53_ECB9D418D87E__INCLUDED_)
//#define AFX_VILLAGEWARINFODLG_H__037A6596_8567_4FB7_BF53_ECB9D418D87E__INCLUDED_

//#if _MSC_VER > 1000

#pragma once
//#endif // _MSC_VER > 1000


#include <Directives.h>
#include <stdio.h>

#include "..\..\..\Resource.h"
#include "../../InterfaceMgr/DialogController.h"


class CNVillageWarInfoDlg :public CDialogController
{
public:
	CNVillageWarInfoDlg();
	~CNVillageWarInfoDlg();

	static void CALLBACK	StatiCNVillageWarInfoDlgProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void CALLBACK			CNVillageWarInfoDlgProc( UINT nEvent, int nControlID, CControllerObj* pControl);


	void Create();
	void Action();

	void Set(SI32 winvillage,SI32 losevillage);

private:


	BOOL m_bRectSwitch;
	RECT m_rtDlg;
	SI16 m_siBitmapAnimationIndex;
	CStatic	*m_pnstatic_villagewarinfo1;
	CStatic	*m_pnstatic_villagewarinfo2;

	

//	HBRUSH m_hEditBrush;

};

//#endif // !defined(AFX_VILLAGEWARINFODLG_H__037A6596_8567_4FB7_BF53_ECB9D418D87E__INCLUDED_)

