
#pragma once

#include "../../InterfaceMgr/DialogController.h"
#include "../../common/Family/Family.h"

enum
{
	CLICK_MODE_PARENT_NONE	=	0,	// ����� �������
	CLICK_MODE_PARENT_ME,			// �θ��̰� �� �ڽ��� �������
	CLICK_MODE_PARENT_MATE,			// �θ��̰� ����ڸ� �������
	CLICK_MODE_PARENT_CHILDREN,		// �θ��̰� �ڽ��� �������
	CLICK_MODE_CHILDREN_ME,			// �ڽ��̰� ���� �������
	CLICK_MODE_CHILDREN_OTHER,		// �ڽ��̰� �ٸ� �ڽ��� �������
	CLICK_MODE_CHILDREN_PARENT,		// �ڽ��̰� �θ� �������
};

#define MAX_RICHEDIT_OBJ_SIZE							500		// �ִ� 500 Byte�� �����Ϳ� �Ҵ� ��.

class CNFamilyInfoDlg : public CDialogController
{

// -- Member Variable Area
private:
	InterfaceFactory m_InterfaceFactory;
protected:

public:


// -- Member Function Area
private:

protected:

public:
	CNFamilyInfoDlg( void );
	~CNFamilyInfoDlg( void );

	SI32		siWarpTargetFamily	;
	TCHAR*		m_strChatData;
	
	BOOL		m_bMini	;
	SI16		m_siOldPosX;
	SI16		m_siOldPosY;
	SI32		m_siOldXSize;
	SI32		m_siOldYSize;

	SI16		m_siMinimizedSlot;

	bool		m_bShowparents	;
	bool		m_bShowchildres	;
	bool		m_bShowchat	;

	void Init();
	void Create();

	void Action();

	static void CALLBACK StaticCallBackDialogNFamilyInfoDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
	void CALLBACK CallBackDialogNFamilyInfoDlg( UINT nEvent, int nControlID, CControllerObj* pControl );

	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );
	void OnButtonClickMate( void );
	void DisplayFamilyInfo( void );
	void CheckMateConnect( void );
	void OpenPopUp(SI32 ButtonIndex, bool bParent ,SI32 siPersonID , TCHAR* CharName)	;
	void WarpFamily(SI32 siTargetGamilyPersonID, TCHAR* TarGetCharName )	;
	void SendChat(void)	;
	void RecvChat( stChatEditData* szChatDat )	;
	void Minimi(BOOL bMini);
	SI16 GetMinimizedSlot(){return m_siMinimizedSlot;};
	void SetMinimizedSlot(SI16 MinimizedSlot){  m_siMinimizedSlot = MinimizedSlot; };
	void ClearDlg();
	void OpenPopUpSet( SI32 siButtonindex );
	
	// ���� ����â ����
	void ShowParent( bool bShow )	;
	void ShowChindren( bool bShow )	;
	void ShowChat( bool bShow )	;
	void MoveCParent( SI32 sihight)	;
	void MoveChindren( SI32 sihight)	;
	void MoveChat( SI32 sihight)	;

};