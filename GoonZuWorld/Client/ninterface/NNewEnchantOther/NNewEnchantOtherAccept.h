

#pragma once


#include "..\..\..\Resource.h"
#include "../../InterfaceMgr/DialogController.h"
#include "../../InterfaceMgr/InterfaceMgr.h"


class CLibListMgr;
class CList;
class CStatic;
class CButton;
class COutLine;
class CEdit;
class cltItem;



class CNNewEnchantOthereAccept :public CDialogController	// �ŷ� ��û �޽��� �ڽ��� �̺�Ʈ ��鷯����
{
public:
	CNNewEnchantOthereAccept();
	~CNNewEnchantOthereAccept();

	void Create();
	//	void Set(SI32 CommonDlg_mode);
	void Action();
	//void LogOut();

	static void CALLBACK StatiCNNewEnchantOthereAcceptProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
	void CALLBACK NPrivateTradeAcceptDlgProc( UINT nEvent, int nControlID, CControllerObj* pControl );
	void RetMsgBox(bool RetValue, SI16 MsgIndex, BYTE* pData, SI16 DataLen);

private:
	SI32 siCommonDlg_mode;
	SI32 siExitCount;

	CEdit	*m_pEdit;
	CButton	*m_pOKButton;
	CButton	*m_pCancelButton;

};

