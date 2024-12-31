/* ==========================================================================
Ŭ���� :		CNFriendDlg

�ۼ��� :		05/03/05
�ۼ��� :		���뷡

��  �� :		CNFriendDlg Ŭ������  ��ü ȭ�� ��� ����� NInterface��
���� ���� ȭ�� �ȿ��� ģ�� ��� �� ���� ���̾�α׸� �����Ѵ�.

��  �� :		

������� :		����

�����۾� :		cpp ����

========================================================================*/
//#if (defined(__LEON_START_ALL) || defined(__LEON_NFRIENDDLG__)) && defined(_DEBUG)

#pragma once

#include <Directives.h>
#include "..\..\..\Resource.h"
#include <commctrl.h>

#include "../../Client/client.h"
#include "../../CommonLogic/Msg/MsgType-Friend.h"
#include "../../CommonLogic/MsgType-System.h"
#include "../../CommonLogic/MsgType-Person.h"

#include "../../InterfaceMgr/DialogController.h"
#include "../../../Common/Item/ItemCommon/ItemUnit.h"


class cltFriendInfo;

class CList;
class CStatic;
class CEdit;
class CButton;
class CImageStatic;

// ����Ʈ ��Ʈ���� ����ؾ� �ҵ�
// �տ� ���� ���θ� üũ�ڽ� ������ ���ϰ�..
// ���� �ٷ� ������ �־ ���⵵ ������.
class CNFriendDlg : public CDialogController
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

	CNFriendDlg();
	~CNFriendDlg();

	void Initialize();
	void Destroy();

	void Create( );

	static	void CALLBACK StaticNFriendDlgProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void	CALLBACK NFriendDlgProc( UINT nEvent, int nControlID, CControllerObj* pControl );

	bool IsShow();
	void Show();
	void Hide();
	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );

	bool IsChanged();
	void LoadFriendList();

	void FriendAddList( SI16 ListIndex, SI32 PersonID, SI32 CharId, TCHAR *FriendName ,TCHAR *AccountID);
	void FriendDelList( SI16 ListIndex, SI32 PersonID );

	void FriendLogin( SI32 PersonID, SI32 CharID ,TCHAR * AccountID);
	void FriendLogOut( SI32 PersonID );

	void ShowFriendMemo();

	void Action();

	CList			*m_pFriendList;
	CStatic			*m_pFriendNameStatic;
	CEdit			*m_pFriendNameEdit;
	CButton			*m_pFriendDelButton;
	CButton			*m_pFriendWhisperChatButton;
	CButton			*m_pFriendAddButton;
	CButton			*m_pFriendMinhomeButton;
	CButton			*m_pFriendWarpButton;
	CImageStatic	*m_pFriendProfileImage;
	CStatic			*m_pFriendIntroStatic;
	CButton			*m_pFriendMemoButton;

	cltFriendInfo *m_pFriendInfo;

	TCHAR m_szAccountID[MAX_FRIEND_NUMBER][MAX_PLAYER_NAME];

private:

	bool m_bShow;


};

//#endif
