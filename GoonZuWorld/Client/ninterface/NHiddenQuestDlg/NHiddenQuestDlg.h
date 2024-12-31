#pragma once

#include <Directives.h>
#include "../../Client/client.h"
#include "../../InterfaceMgr/DialogController.h"

class CDailyQuest2ObjData;
class CDailyQuest3ObjData;

class cltItem;
class CListView;
class CEdit;

class NHiddenQuestDlg : public CDialogController
{
public:

	NHiddenQuestDlg();
	~NHiddenQuestDlg();
	
	static	void CALLBACK NHiddenQuestDlgProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl );
	void CALLBACK NHiddenQuestDlgitemProc( UINT nEvent, int nControlID, CControllerObj* pControl );

	void Create();
	void Show();
	void Hide();
	bool IsShow();

	bool m_bShow;
	SI16 siIndex;

	void SetPramformDailyQuest2(SI16 para , CDailyQuest2ObjData *pDailyQuest2ObjDataList); // ���ϸ� ����Ʈ 2���� ���� ȣ���

	void SetPramformDailyQuest3(SI16 para , CDailyQuest3ObjData *pDailyQuest3ObjDataList);	// ���ϸ� ����Ʈ 3���� ���� ȣ���� ���.

	void SetNInventoryInListView(CListView* in_pListView);
	void SetNInventoryInListView2(CListView* in_pListView);
	
private:
	CDailyQuest2ObjData *m_pDailyQuest2ObjDataList;
	CDailyQuest3ObjData *m_pDailyQuest3ObjDataList;
	CListView*	m_pListView_item_image;
	CEdit*		m_pEdit_explain;
	CButton*	m_pButton_OK;
	CButton*	m_pButton_Cancel;
	BOOL		m_bMoneySelected;

	SI32			m_siImageType;	// ������ �̹���1 Ÿ��(�̹����� 3��)
	SI32			m_siImageIndex; // ������ �̹������� ����
	
	SI16 m_siCount;
	SI16 flag2;
	SI16 flag3;

	
};

