#ifndef _NPOSTOFFICEDLG_H
#define _NPOSTOFFICEDLG_H

#include "../StrBaseDlg/StrBaseDlg.h"
#include "../../CommonLogic/PostOffice/PostOffice.h"

class NStrInventory;

class NPostOfficeDlg : public NStrBaseDlg
{
public:
	NPostOfficeDlg();
	virtual ~NPostOfficeDlg();

	void Create();

	void GreetingMsg();

	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );
};

// ��ǰ ������
class NPostOfficeSendItemDlg : public NStrTabDlg
{
public:
	enum {
		EDIT_PLAYERNAME,
		EDIT_ITEMNAME,
		EDIT_AMOUNT,
		EDIT_RECEIVERNAME,
		EDIT_MSG,

		LISTVIEW_MYINVENTORY,

		BUTTON_SENDITEM,
		BUTTON_SENDMSG

	};

	NPostOfficeSendItemDlg();
	virtual ~NPostOfficeSendItemDlg();

	void InitDlg();

	void Action();

	void NDlgTabProc( UINT nEvent, int nControlID, CControllerObj *pControl );

	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );
	void WriteName(TCHAR* pName);

public:
	NStrInventory*	m_pMyInventory;

};



// ���� ������
class NPostOfficeSendMoneyDlg : public NStrTabDlg
{
public:
	enum {
		EDIT_PLAYERNAME,
		
		EDIT_CURRENTMONEY,
		EDIT_MONEY,
		EDIT_MONEY_UNIT,
		EDIT_FEE,
		EDIT_FEERATE,
		EDIT_MSG,
		EDIT_RECEIVERNAME,

		BUTTON_SENDMONEY,
		BUTTON_SENDMSG		
	};

	NPostOfficeSendMoneyDlg();
	virtual ~NPostOfficeSendMoneyDlg();

	void InitDlg();

	void Action();

	void NDlgTabProc( UINT nEvent, int nControlID, CControllerObj *pControl );

	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );
};


// ������	
class NPostOfficeRecvDlg : public NStrTabDlg
{
public:
	enum {
		LIST_RECVLIST,
		EDIT_MSG,

		BUTTON_RECV,
		BUTTON_RECVOK,
		BUTTON_SENDOK,
		BUTTON_REPLY//�����ϱ� [2007.08.17 �ռ���]
	};

	NPostOfficeRecvDlg();
	virtual ~NPostOfficeRecvDlg();

	void InitDlg();

	void Action();

	void NDlgTabProc( UINT nEvent, int nControlID, CControllerObj *pControl );

};

// �ۼ��ų�������
class NPostOfficeRecordDlg : public NStrTabDlg
{
public:
	enum {
		LIST_RECORDLIST,
		EDIT_MSG,

		BUTTON_RECORD

	};
	NPostOfficeRecordDlg();
	virtual ~NPostOfficeRecordDlg();

	void InitDlg();

	void Action();

	void ShowRecordList();

	void NDlgTabProc( UINT nEvent, int nControlID, CControllerObj *pControl );

};


// ���� ��� �޴�
class NPostOfficeChiefDlg : public NStrTabDlg
{
public:
	enum {
		EDIT_FEERATE_MONEY,
		EDIT_FEERATE_ITEM,
		EDIT_FEE_MSG,

		BUTTON_SETUP
	};
	NPostOfficeChiefDlg();
	virtual ~NPostOfficeChiefDlg();

	void InitDlg();

	void NDlgTabProc( UINT nEvent, int nControlID, CControllerObj *pControl );
};



//[����] ��ü �޽��� ������. ��ǰ ������ => 2008-8-4
class NNewPostOfficeSendItemDlg : public NStrTabDlg
{
public:
	enum 
	{
		STATIC_PLAYERNAME,
		EDIT_PLAYERNAME,
		EDIT_ITEMNAME,
		EDIT_AMOUNT,
		EDIT_RECEIVERNAME,
		EDIT_MSG,

		LISTVIEW_MYINVENTORY,

		BUTTON_SENDITEM,
		BUTTON_SENDMSG
	};

	NNewPostOfficeSendItemDlg();
	virtual ~NNewPostOfficeSendItemDlg();

	void InitDlg();

	void Action();
	void Destroy();
	void Show();
	void Hide();

	void NDlgTabProc( UINT nEvent, int nControlID, CControllerObj *pControl );

	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );
	void WriteName(TCHAR* pName);

public:
	NStrInventory*	m_pMyInventory;

};

#endif