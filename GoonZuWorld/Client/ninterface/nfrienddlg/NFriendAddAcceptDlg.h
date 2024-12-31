/* ==========================================================================
	Ŭ���� :		CNFriendAddAcceptDlg

	�ۼ��� :		05/03/05
	�ۼ��� :		���뷡

	��  �� :		CNFriendAddAcceptDlg Ŭ������  ��ü ȭ�� ��� ����� NInterface��
					���� ���� ȭ�� �ȿ��� ģ�� �߰� ��� ���̾�α׸� �����Ѵ�.

	��  �� :		

	������� :		����
	
	�����۾� :		cpp ����

   ========================================================================*/
//#if (defined(__LEON_START_ALL) || defined(__LEON_NFRIENDDLG__)) && defined(_DEBUG)

#pragma once

#include <Directives.h>
#include "..\..\..\Resource.h"

#include "../../Client/client.h"

#include "../../InterfaceMgr/DialogController.h"
#include "../../../Common/Item/ItemCommon/ItemUnit.h"

class CLibListMgr;
class CEdit;
class CButton;

struct stNAcceptObj
{
	SI08 siGroupID;
	SI32 siPersonID;
	SI32 siCharID;
	TCHAR strCharName[MAX_PLAYER_NAME];
	
	stNAcceptObj()
	{
		Init();
	}

	void Init()
	{
		memset( this, 0, sizeof( stNAcceptObj ) );
	}

	void Set( SI08 GroupID, SI32 PersonID, SI32 CharID, TCHAR *CharName )
	{
		siGroupID = GroupID;
		siPersonID = PersonID;
		siCharID = CharID;

		MStrCpy( strCharName, CharName, MAX_PLAYER_NAME );
	}
};

class CNFriendAddAcceptDlg : public CDialogController
{
public:
	enum
	{
		BIG_DISPLAY_MODE_DELTA_X = 16,
		SMALL_DISPLAY_MODE_DELTA_Y = 80,        
		DLG_BIG_POS_X = 1024 - 300 + BIG_DISPLAY_MODE_DELTA_X,
		DLG_BIG_POS_Y = 100,
		DLG_SMALL_POS_X = 800 - 300 + SMALL_DISPLAY_MODE_DELTA_Y,
		DLG_SMALL_POS_Y = 100,
	};

	CNFriendAddAcceptDlg();
	~CNFriendAddAcceptDlg();

	void Create();

	static	void CALLBACK StatiCNFriendAddAcceptDlgProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void	CALLBACK NFriendAddAcceptDlgProc( UINT nEvent, int nControlID, CControllerObj* pControl );

	bool IsShow();
	void Show();
	void Hide();

	void PushAccpetList( SI08 GroupID, SI32 PersonID, SI32 CharID, TCHAR *CharName );
	void PopAcceptList();

	void Action();

private:	
	bool m_bShow;
	CLibListMgr *m_pAcceptListMgr;

	SI08 m_siGroupID;
	SI32 m_siPersonID;
	SI32 m_siCharID;

	TCHAR m_strCharName[ MAX_PLAYER_NAME ];

	CEdit		*m_pFriendAddExplainEdit;
	CButton		*m_pFriendAddAcceptButton;
	CButton		*m_pFriendAddRefuseButton;	
};

//#endif	//#if defined(__LEON_NMASTER__) && defined(_DEBUG)

