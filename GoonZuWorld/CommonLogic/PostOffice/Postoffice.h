#ifndef _POSTOFFICE_H
#define _POSTOFFICE_H

#include <Directives.h>

#include "..\StructureClass\StructureClass.h"

//#include <Stdio.h>

//#include "..\..\Common\Item\ItemCommon\cltitem.h"

#define	MAX_POSTOFFICE_TAB_NUMBER	6

class cltTaxPaymentListDlg;

#define MAX_SAVEUSERITEM_LIST				60
#define MAX_SAVEUSERHORSE_LIST				20
#define MAX_POSTOFFICE_RECV_NUMBER			30
#define MAX_POSTOFFICE_MSG_SIZE				128
#define MAX_POSTOFFICE_RECORD_NUMBER		100

#define LPARAMHIWORD_ITEM	1
#define LPARAMHIWORD_MSG	2
#define LPARAMHIWORD_MONEY	3

#define POSTOFFICE_MSGTYPE_ITEM			1
#define POSTOFFICE_MSGTYPE_MSG			2
#define POSTOFFICE_MSGTYPE_MONEY		3

// ������� ������ ������ ������ ����
class cltSaveUersItemInfo
{
public:
	
	SI32				siIndex;			// DB�� ����Ǿ� �մ� �ε���	
	SI64				siServiceCharge;	// ������ ������ŭ�� ������
	cltItem				clItem;				// item
	cltDate				clDate;				// �۽���

	cltSaveUersItemInfo()
	{
		ZeroMemory( this, sizeof(cltSaveUersItemInfo) );
	}
};			

//KHY - 1127 - Ŭ��� ��ǰ ���� ����
// ������� ������ ������ ��µ��� ����
class cltSaveUersHorseInfo
{
public:
	
	SI32				siIndex;			// DB�� ����Ǿ� �մ� �ε���	
	SI64				siServiceCharge;	// ������ ������ŭ�� ������
	cltDate				clDate;				// �۽���

	cltHorse			clHorse;  //����� �������� �����´�.

	cltSaveUersHorseInfo()
	{
		ZeroMemory( this, sizeof(cltSaveUersHorseInfo) );
	}
};			

class cltMarketConditionsInfo
{
public:

	SI16 		siUnique; 							// ������ ����ũ.
	GMONEY		siMarketConditionsMoney;			// �ü�.
	GMONEY		siDifferenceMoney;					 // ����.

	cltMarketConditionsInfo()
	{
		ZeroMemory( this, sizeof(cltMarketConditionsInfo) );
	}
};			

// ���ž���������
class cltPostOfficeRecvItemInfo
{
public:
	SI32				siMsgID;

	SI32				siPostType;												// 0:�Ϲ�����, 1:���
	TCHAR				szSenderPersonName[ MAX_PLAYER_NAME ];					// �۽��� name
	cltItem				clItem;													// item

	cltDate				clDate;													// �۽���

	cltPostOfficeRecvItemInfo()
	{
		ZeroMemory( this, sizeof(cltPostOfficeRecvItemInfo) );
	}
};

// ������������
class cltPostOfficeRecvMoneyInfo
{
public:
	SI32				siMsgID;

	SI32				siPostType;												// 0:�Ϲ�����, 1:���
	TCHAR				szSenderPersonName[ MAX_PLAYER_NAME ];					// �۽��� name
	GMONEY				siMoney;												// �ݾ�

	cltDate				clDate;													// �۽���

	cltPostOfficeRecvMoneyInfo()
	{
		ZeroMemory( this, sizeof(cltPostOfficeRecvMoneyInfo) );
	}
};

// ���Ÿ޽�������
class cltPostOfficeRecvMsgInfo
{
public:
	SI32				siMsgID;

	SI32				siPostType;												// 0:�Ϲ�����, 1:���
	TCHAR				szSenderPersonName[ MAX_PLAYER_NAME ];					// �۽��� name
	TCHAR				szMsg[ MAX_POSTOFFICE_MSG_SIZE ];						// �޽��� 

	cltDate				clDate;													// �۽���

	cltPostOfficeRecvMsgInfo()
	{
		ZeroMemory( this, sizeof(cltPostOfficeRecvMsgInfo) );
	}
};

class cltPostOfficeRecvDataInfo
{
public:
	cltDate		clDate;
	TCHAR		szPersonName[ MAX_PLAYER_NAME ];
	TCHAR		szMsg[ 210 ];
	LONG		lParam;

	cltPostOfficeRecvDataInfo()
	{
		ZeroMemory( this, sizeof( cltPostOfficeRecvDataInfo ) );
	}
};



// �ۼ��ų���
class cltPostOfficeRecordInfo
{
public:
	SI32				siMsgID;
	SI16				siMsgType;												// �ۼ��ų���Ÿ��
	SI32				siPostType;												// 0:�Ϲ�����, 1:���
	SI16				siSendRecv;												// 1:�۽� 2:����
	TCHAR				szPersonName[ MAX_PLAYER_NAME ];						// �ۼ����� name
	SI16				siItemUnique;											// ������ Unique
	SI16				siItemNum;												// ������ Num
//	TCHAR				szMsg[ MAX_POSTOFFICE_MSG_SIZE ];						// �޽���
	GMONEY				siMoney;												// �ݾ�

	cltDate				clDate;													// ����

	cltPostOfficeRecordInfo()
	{
		ZeroMemory( this, sizeof( cltPostOfficeRecordInfo ) );
	}

};


//-------------------------------------------------
// �������� ��ü��
//-------------------------------------------------
class cltPostOffice : public cltStructureBasic{
private:

public:
	cltPostOffice(SI32 sivillageunique);
	~cltPostOffice();

};

//-----------------------------------------------
// ��ü�� ������. 
//-----------------------------------------------
class cltPostOfficeManager : public cltStructureMngBasic{
public:

	cltPostOfficeManager(cltCharManager* pclCM, SI32 gamemode, SI32 ranktype, TCHAR *strFileName );
	~cltPostOfficeManager();

	// ���� ȯ�� �λ縻ǥ�� . 
	void GreetingMsg(HWND hDlg);
	void Do_WM_INITDIALOG(SI32 id);

	// ��ü���� �ż��Ѵ�.
	BOOL CreatePostOffice(SI32 siunique);

	void LoadMyInventory( HWND hDlg );
	BOOL IsMyInventoryChanged();

	void AddItemToRecvList( cltPostOfficeRecvItemInfo *pItemInfo );
	void AddMsgToRecvList( cltPostOfficeRecvMsgInfo *pMsgInfo );
	void AddMoneyToRecvList( cltPostOfficeRecvMoneyInfo *pMoneyInfo );
	
	void DispMsgInfo( HWND hDlg );

	void ListRecvItem_DeleteAll();												// ������ ����Ʈ�� �ʱ�ȭ�Ѵ�
	void ListRecvItem_DelItem( LPARAM lParam );									// �����Կ��� �ϳ��� �������� �����

	cltItem* GetItemFromList( SI32 siMsgID );									// �����Կ��� ������(��ǰ)������ ���´�

	void ShowPostOfficeInfo();

public:	
	cltItem						*m_pclMyItem;				// �� �κ��丮 üũ

	HWND						m_hUserInventory;

	HIMAGELIST					m_hImageList;
	
	SI32						m_siInventorySelectedIndex;
	HWND						m_hwndRecvList;
	
	SI32						m_siCurMsgType;
	SI32						m_siCurMsgID;

	BOOL						m_bAddItemToRecvList;
	BOOL						m_bAddMsgToRecvList;
	BOOL						m_bAddMoneyToRecvList;
	BOOL						m_bRefreshList;
	
	BOOL						m_bMainExplain;

#ifdef _SAFE_MEMORY
	NSafeTArray<cltPostOfficeRecvDataInfo, MAX_POSTOFFICE_RECV_NUMBER>		m_recvDataInfo;
	NSafeTArray<cltPostOfficeRecvItemInfo, MAX_POSTOFFICE_RECV_NUMBER>		m_recvItemInfo;
	NSafeTArray<cltPostOfficeRecordInfo, MAX_POSTOFFICE_RECORD_NUMBER>		m_recordinfo;
#else
	cltPostOfficeRecvDataInfo	m_recvDataInfo[ MAX_POSTOFFICE_RECV_NUMBER ]; 
	cltPostOfficeRecvItemInfo	m_recvItemInfo[ MAX_POSTOFFICE_RECV_NUMBER ];
	cltPostOfficeRecordInfo		m_recordinfo[ MAX_POSTOFFICE_RECORD_NUMBER ];
#endif
	SI32						m_recordcount;

	BOOL						bUpdateRecord;
	void						ShowRecordList( HWND hDlg );


};

#endif
