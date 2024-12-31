#pragma once

#include "../../InterfaceMgr/DialogController.h"
#include "..\CommonLogic\PostOffice\PostOffice.h"

class CButton;
class CStatic;
class CList;

class cltItem;
class cltSaveUersItemInfo;

#define BASIC_SERVICECHARGE 20000  //��µ��� ȸ�� ������ �⺻��. - ������ ���� �����ʿ�.

// ���� ������ ã��
class CNSaveItemListDlg : public CDialogController
{
public:
	
	CStatic*			m_pStatic[2];
	CList*				m_pList;
//	CButton*			m_pButton[2];

	//KHY - 1127 - Ŭ��� ��ǰ ���� ����
	CButton*			m_pButton[4];
	SI32				m_selectWhatShowList; // � ����Ʈ�� ������ ���ΰ�?(�����߳�)

	SI32				m_siSelectIndex;

	cltSaveUersItemInfo	m_clSaveUsersItemInfo[MAX_SAVEUSERITEM_LIST];

	//KHY - 1127 - Ŭ��� ��ǰ ���� ����
	cltSaveUersHorseInfo	m_clSaveUsersHorseInfo[MAX_SAVEUSERHORSE_LIST];

	CNSaveItemListDlg();
	~CNSaveItemListDlg();

	void Create();

	static void CALLBACK StaticCallBackDialogNSaveItemListDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
	void CALLBACK CallBackDialogNSaveItemListDlg( UINT nEvent, int nControlID, CControllerObj* pControl );

	void	 ShowList( cltSaveUersItemInfo* pSaveUersItemInfo ,cltSaveUersHorseInfo* pSaveUersHorseInfo);
	//KHY - 1127 - Ŭ��� ��ǰ ���� ����
	void  InDlgShowList(SI32 selectListType ); // ���̾� �α� �ȿ����� ����Ʈ ������ ���ؼ�.
	cltHorse* GetHorseFromList( SI32 index );
	cltItem* GetItemFromList( SI32 index );

	void	 RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );

};
