/* ==========================================================================
Ŭ���� :		 

�ۼ��� :		 
�ۼ��� :		 

������� :		 

�����۾� :		
========================================================================*/

#pragma once

#include "../../Client/client.h"
#include "../../InterfaceMgr/DialogController.h"

#define CONTRIBUTION_ITEM_NUM	6



class NContributionEvent_CommonDlg : public CDialogController
{
public:
	enum EVENT
	{
		EVENT_CONTRIBUTION_BUTTON_CLICK,	// ��� ��ư Ŭ���� �̺�Ʈ.
		EVENT_ACTION_BUTTON_CLICK,			// npc����� ��ư �̺�Ʈ.
		EVENT_ACTION_CONTRIBUTION_COMPLETE	// ����ϴٰ� ��ΰ� �Ϸ������ �̺�Ʈ.
	};
public:

	NContributionEvent_CommonDlg();
	~NContributionEvent_CommonDlg();

	void	Create( SI16 siControllID, CControllerMgr* _pChildControllerMgr, GUIChildCallBackEvent _pChildCallBack );	
	bool	EndClickAndDrop( cltClickAndDrop* pclClickAndDrop );
	
	static void CALLBACK StaticNContributionEvent_CommonDlgProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl );
	void CALLBACK NContributionEvent_CommonDlgProc( UINT nEvent, int nControlID, CControllerObj* pControl );

	void SetExplainText( TCHAR* pszString );
	void SetContributeButtonText( TCHAR* pszString );
	void SetActionButtonText( TCHAR* pszString );

	static void StaticSetContributionItemList( SI32* _psiItemUnique,  SI16* _psiItemNum );		// �̰��� �� â�� �������� ���ϰŶ� �������.
	static void StaticSetContributionInputItemList( SI32* _psiInputItemUnique,  SI16* _psiInputItemNum );
	
	void SetContributionItemList( SI32* _psiItemUnique,  SI16* _psiItemNum );					// ���� ���� ����.
	void GetContributionItemList( SI32 NPCKind );												// ����� �������� ������ ���� �������� ���� ���.
	
	void SetContributionInputItemList( SI32* _psiInputItemUnique,  SI16* _psiInputItemNum );	// ��� �� �������� ���� ����.
	void GetContributionInputItemList( SI32 NPCKind );											// ��� �� �������� ���� ���.
	
	void SetContributionUserItemList( void );													// ����ϴ� �������� ������ �κ����� �˻��Ͽ� ������ ����.

	void InputItem( void );																		// ���� ��ϵ� �������� �ֱ�.(���)
	bool IsComplete( void );																	// ��θ� �Ϸ��ߴ���.
	void MakeNPC( void );																		// ��ΰ� �������� ����� �ִ� NPC�� ����.

	void MakeItemNum( SI32 _siEditIndex );

private:
	InterfaceFactory		m_InterfaceFactory;

	CControllerMgr*			m_pChildControllerMgr;
	GUIChildCallBackEvent	m_pChildCallBack;

	static SI32				m_siControllID;

	SI32					m_siItemUnique[CONTRIBUTION_ITEM_NUM];
	SI16					m_siItemNum[CONTRIBUTION_ITEM_NUM];

	SI32					m_siInputItemUnique[CONTRIBUTION_ITEM_NUM];
	SI16					m_siInputItemNum[CONTRIBUTION_ITEM_NUM];

	bool					m_bComplete;
	SI32					m_siNPCKind;
};
