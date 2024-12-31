// MakeItemDlg.h: interface for the CNMakeItemDlg class.
//
//////////////////////////////////////////////////////////////////////
/* ==========================================================================
	Ŭ���� :		CNSiegeWinDlg

	�ۼ��� :		05/03/18
	�ۼ��� :		���¾�

	��  �� :		
	                

	��  �� :		
	������� :		����

	�����۾� :		cpp �۾� �Ϸ� ��

   ========================================================================*/


#pragma once
#include <Directives.h>
#include <stdio.h>

#include "..\..\..\Resource.h"
#include "../../Client/client.h"
#include "../../InterfaceMgr/DialogController.h"


class CImageStatic;
class CStatic;




class CNMakeItemDlg  : public CDialogController
{
public:
	CNMakeItemDlg();
	 ~CNMakeItemDlg();

	void					Create();
	void					Set( cltItem *pclItem, SI32 baseexp, SI32 skillunique,SI32 skillexp,SI32 monstercorp);

	static void CALLBACK	StatiCNMakeItemDlgProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void CALLBACK			NMakeItemDlgProc(UINT nEvent, int nControlID, CControllerObj* pControl);

	void Action();

private:
	CImageStatic			*m_pNMakeitemImage;
	CStatic					*m_pNMakeitemStatic;
	SI32			m_siImageType;	// ������ �̹��� Ÿ��(�̹����� 3��)
	SI32			m_siImageIndex; // ������ �̹������� ����

	SI16			m_siCurrentFrame; // �˾� ��������� �����Ӽ� üũ
};
