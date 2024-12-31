#pragma once
// NNewEnchantOther.h: interface for the NNewEnchantOther class.
//
//////////////////////////////////////////////////////////////////////
/* ==========================================================================
Ŭ���� :		CNRightMouseUserListDlg.h

�ۼ��� :		06/02/17
�ۼ��� :		�迵��

��  �� :		���� ������ �����ִ� ���� ������ ���콺�� Ŭ���ϸ� ���� ����� ������

��  �� :		
������� :		����

�����۾� :		

========================================================================*/
#include "Resource.h"

#include "../../InterfaceMgr/DialogController.h"
#include "../../../common/CommonHeader.h"
//#include "../../../Client/Inventory/ItemInventoryBaseDefinition.h"

class CList;

#define	NRIGHTMOUSEUSERLIST_DLG_WIDTH	120
#define	NRIGHTMOUSEUSERLIST_DLG_HEIGHT	170
#define MAX_STRING_SIZE	100

struct stUnderMouseUserData
{
	SI32  siUserId;
	SI32  siKind;
	SI32  siLevel;
	TCHAR strCharName[ MAX_PLAYER_NAME ];
	
	stUnderMouseUserData()
	{
		Init();
	}

	stUnderMouseUserData( SI32 id, SI32 Kind , SI32 Level, TCHAR * CharName )
	{
		Init();

		siUserId = id;
		siKind = Kind;
		siLevel = Level;
		StringCchCopy(strCharName,MAX_PLAYER_NAME,CharName);
	}

	void Init()
	{
		memset( this, 0, sizeof( stUnderMouseUserData ) );
	}
};



class NRightMouseUserListDlg : public CDialogController
{
public:

	NRightMouseUserListDlg();
	~NRightMouseUserListDlg();

	void Create();

	static void CALLBACK StaticCallBackDialogNRightMouseUserListDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
	void CALLBACK CallBackDialogNRightMouseUserListDlg( UINT nEvent, int nControlID, CControllerObj* pControl );

	void Initialize();
	void SetUnderUserList(BOOL bCheckName);

	void AddUser(SI32 id, SI32 Kind , SI32 Level, TCHAR * CharName );
	void SetUserName(SI32 id, TCHAR * CharName );
	
	void Show();
	void Hide();

	void ClearFocus();
	void SetFocus(bool Focus);
	void CalcWitdhUserList(SI32 siStringSizeMax);
	void CalcHeightUserList(SI32 UserListIndex);

private:
	//InterfaceFactory m_InterfaceFactory;

	list< stUnderMouseUserData > m_UnderMouseUserList;
	list< stUnderMouseUserData >::iterator m_UnderMouseUserListItr;

	CList*		m_pUserList;
	// PCK : ĳ���� �̸��� ���� ����Ʈ ũ�⸦ �����ϱ� ���ؼ� �ӽ÷� ���� Static Ŭ����
	CStatic*	m_pTempStaticUserList;

	BOOL m_bShow;
};

