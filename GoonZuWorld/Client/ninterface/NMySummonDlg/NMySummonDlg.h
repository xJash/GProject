//--------------------------------------------------------------------------------
//	�ۼ��� : �ռ���
//	�ۼ���¥ : 2008 �� 08�� 12��~
//	���� : ��ȯ�� ���� �ý���
//--------------------------------------------------------------------------------
#pragma once 

#include "../../InterfaceMgr/DialogController.h"
//
class CImageStatic	;
class CStatic		;
class CButton		;
class CEdit			;
class CList			;
class CComboBox		;
class CRadioButton	;
class COutLine		;
//
//#define TRADE_SUMMONRANK	6
//
class CNMySummonDlg : public CDialogController
{
	public:
		CList*		m_plSummonList		;	// ������ �ִ� ��ȯ������� ��Ÿ���� ����Ʈ
		CButton*	m_pBtnOutput		;	// ��ȯ�� �������� Input
		CButton*	m_pBtnInput			;	// ��ȯ�� ���Կ��� Output

		CButton*	m_pBtSlot1			;	// ���Թ�ư1
		CButton*	m_pBtSlot2			;	// ���Թ�ư2
		CButton*	m_pBtSlot3			;	// ���Թ�ư3
        
		CImageStatic*	m_stSummonSlot1	;	// Ȱ��ȭ�� ��ȯ�� ��
		CImageStatic*	m_stSummonSlot2	;	// Ȱ��ȭ�� ��ȯ�� ��
		CImageStatic*	m_stSummonSlot3	;	// Ȱ��ȭ�� ��ȯ�� ��

		COutLine*	m_OutlineSlot1		;	// ���гη� �� �ƿ�����
		COutLine*	m_OutlineSlot2		;	// ���гη� �� �ƿ�����
		COutLine*	m_OutlineSlot3		;	// ���гη� �� �ƿ�����

		CStatic*	m_pStaticNoName01	;	// ����
		CStatic*	m_pStaticNoName02	;	// ����
		CButton*	m_pBtUseTicket		;	// ���Թ�ư1
		COutLine*	m_pOutLine02		;	// ���Թ�ư1
		COutLine*	m_pOutLine01		;	// ���Թ�ư1
		

		CNMySummonDlg()		;
		~CNMySummonDlg()	;

		void Create();
		void Action();
		static void CALLBACK StaticCallBackDialogCNMySummonDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
		void CALLBACK CallBackDialogCNMySummonDlg( UINT nEvent, int nControlID, CControllerObj* pControl );
		void LodaMyOutSummon();
		void LodaMyhaveSummonList();
		void SetListSelectItem( SI16 ListSelectItem ) ;
		void SetSelectSlot( SI16 siSelectSlot ) ;
		SI16 GetListSelectItem(  ) ;
		SI16 GetSelectSlot(  ) ;
	private:
		SI16	siListSelectIndex	;
		SI16	siSlotSelectIndex	;
};