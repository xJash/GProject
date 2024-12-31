/* ==========================================================================
	Ŭ���� :		CNNotifyGetExpAndItemDlg

	�ۼ��� :		05/05/10
	�ۼ��� :		���뷡
	
	������� :		����

	�����۾� :		

   ========================================================================*/

#pragma once

#include <Directives.h>
#include "../../InterfaceMgr/DialogController.h"

class cltItem;
class CListView;
class CEdit;

class CNNotifyGetExpAndItemDlg : public CDialogController
{
public:
	enum
	{
		BIG_DISPLAY_MODE_DELTA_X = 16,
		SMALL_DISPLAY_MODE_DELTA_Y = 80,        
		DLG_WIDTH = 0,	// DDF ���Ͽ��� �о ó��
		DLG_HEIGHT = 0,	// DDF ���Ͽ��� �о ó��
		DLG_BIG_POS_X = 1024 - DLG_WIDTH + BIG_DISPLAY_MODE_DELTA_X,
		DLG_BIG_POS_Y = 80,
		DLG_SMALL_POS_X = 800 - DLG_WIDTH + SMALL_DISPLAY_MODE_DELTA_Y,
		DLG_SMALL_POS_Y = 80,
	};
	
	CNNotifyGetExpAndItemDlg();
	~CNNotifyGetExpAndItemDlg();
	
	static	void CALLBACK NNNotifyGetExpAndItemStaticProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl );
	void CALLBACK NNotifyGetExpAndItemProc( UINT nEvent, int nControlID, CControllerObj* pControl );

	void Create();
	void Show();
	void Hide();
	bool IsShow();

	bool m_bShow;

	void Show( cltItem *pclItem, SI32 Exp, SI32 GP, GMONEY Money );
	void SetNInventoryInListView(CListView* in_pListView, cltItem* in_pCltItem );
	void Show2( cltItem *pclItem, SI32 Exp, SI32 GP, GMONEY Money );
	
	//[����] ���� �̺�Ʈ - ���� ���� => 2008-4-2
	void MonsterAttackReward( SI32 ItemUnique, SI32 ItemNum, SI32 AddVillageScore );
	// ���ϸ� ����Ʈ 2 �Ϸ� �޼���
	void ShowDailyQuest2( cltItem *pclItem, SI32 Exp, SI32 GP, GMONEY Money );
	// ���ϸ� ����Ʈ 3 �Ϸ� �޼��� 
	void ShowDailyQuest3( cltItem *pclItem, SI32 Exp, SI32 GP, GMONEY Money );
	
private:
	CListView*	m_pListView_item_image;
	CEdit*		m_pEdit_explain;	
	
	SI16 m_siCount;
	
};

