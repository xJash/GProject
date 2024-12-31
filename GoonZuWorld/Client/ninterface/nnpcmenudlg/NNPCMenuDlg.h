// NNPCMenuDlg .h: interface for the CNNPCMenuDlg  class.
//
//////////////////////////////////////////////////////////////////////


/* ==========================================================================
	Ŭ���� :		CNNPCMenuDlg 

	�ۼ��� :		05/03/30
	�ۼ��� :		���¾�

	��  �� :		.
	                

	��  �� :		
	������� :		����

	�����۾� :		cpp �۾� �Ϸ� ��

   ========================================================================*/

#pragma once
#include <Directives.h>
#include <stdio.h>

#include "Resource.h"
#include "../../InterfaceMgr/DialogController.h"


class CStatic;
class CButton;



class CNNPCMenuDlg  : public CDialogController
{
public:
	CNNPCMenuDlg ();
	  ~CNNPCMenuDlg ();

	void Create();
	void CreateDlg(SI32 charkind,SI32 charunique,TCHAR * txt1 , TCHAR * txt2 ,
				   bool button1,bool button2,TCHAR * txt);

	static void CALLBACK	StatiCNNPCMenuProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl );
	void CALLBACK			NNPCMenuProc(UINT nEvent, int nControlID, CControllerObj* pControl);


	void Close();

private:


	CStatic     	*m_pNNPCMenuStatic1;
	CStatic     	*m_pNNPCMenuStatic2;
	CButton         *m_pNNPCMenuButton1;
	CButton         *m_pNNPCMenuButton2;
	CButton         *m_pNNPCMenuButton3;
	CButton         *m_pNNPCMenuButton4;

	SI32 m_siCharKind;
	SI32 m_siCharUnique;
	
	RECT	m_rtDlg;

	BOOL	m_bRect;

};

