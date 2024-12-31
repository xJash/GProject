#pragma once

#include "../../common/CommonHeader.h"
#include "../../InterfaceMgr/DialogController.h"
#include "../../CommonLogic/Msg/MsgType-Village.h"

// ������ ���� ��ũ 
class CNGoonzuSiegeRankDlg : public CDialogController
{
public:
	CNGoonzuSiegeRankDlg();
	~CNGoonzuSiegeRankDlg();

	void Create( CControllerMgr *pParent );

	static void CALLBACK StaticCallBackDialogNGoonzuSiegeRankDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
	void CALLBACK CallBackDialogNGoonzuSiegeRankDlg( UINT nEvent, int nControlID, CControllerObj* pControl );

	void ShowRank(cltGameMsgResponse_VillageDetailInfo* pclinfo);
	SI32 Sort(SI64 sisortdata[], SI32* pvillageunique);
	void Action();

	SI32		m_siListdata[MAX_VILLAGE_NUMBER];

	CList*		m_pListVillageRank;
	CButton*	m_pButtonSiege;
};

// ������ ����Ʈ
class CNGoonzuSiegeListDlg : public CDialogController
{
public:
	CNGoonzuSiegeListDlg();
	~CNGoonzuSiegeListDlg();

	void Create( CControllerMgr *pParent );

	static void CALLBACK StaticCallBackDialogNGoonzuSiegeListDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
	void CALLBACK CallBackDialogNGoonzuSiegeListDlg( UINT nEvent, int nControlID, CControllerObj* pControl );

	void ShowList();
	SI32 Sort(SI64 sisortdata[], SI32* pvillageunique);
	void Action();

	SI32		m_siListdata[MAX_VILLAGE_NUMBER];

	CList*		m_pListSiegeList;
	CStatic*	m_pStaticSiegeTime;
};

// ������ â ( ���̽� )
class CNGoonzuSiegeDlg : public CDialogController
{
public:

	CNGoonzuSiegeDlg();
	~CNGoonzuSiegeDlg();

	void Create();
	static void CALLBACK StaticCallBackDialogNGoonzuSiegeDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
	void CALLBACK CallBackDialogNGoonzuSiegeDlg( UINT nEvent, int nControlID, CControllerObj* pControl );

	CNGoonzuSiegeRankDlg* m_pVillageRankDlg;
	CNGoonzuSiegeListDlg* m_pSiegeListDlg;


	CButton*	m_pButtonVillageRank;
	CButton*	m_pButtonSiegeList;

};
