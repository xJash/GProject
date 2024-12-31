#pragma once

#include "TradeLogView.h"

#include "NTradeLogClientProcess.h"
#include "../../NGameDataManager/NGameDataManager.h"

#define TRADELOGCLIENT_NETWORK_TIMER			120
#define TRADELOGCLIENT_NETWORK_TIMER_ELAPSE	20

#define TRADELOGCLIENT_SHOW_TIMER				200
#define TRADELOGCLIENT_SHOW_TIMER_ELAPSE		300

// CTradeLogFrame �������Դϴ�.

class CTradeLogFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CTradeLogFrame)
protected:
	CTradeLogFrame();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CTradeLogFrame();

	CTradeLogView		m_wndView;

public:
	SI32				m_siSearchCount;
	BOOL				m_bSearching;				// ���� �˻� ���ΰ�?

	HCURSOR				m_hArrowCursor;
	HCURSOR				m_hWaitCursor;

public:
	NTradeLogClientProcess*	GetLogClientProcess()		{	return m_pkTradeLogClientProcess;	}

	void	SearchEnable(BOOL nEnable);
	BOOL	AddLogData(stLOGData_TradeItem* pLogData);
	BOOL	RequestLogData(sDBRequest_TradeItemLog* pNewLogMsg);
	BOOL	Stop();
	void	SaveLogFile(CString kFileName, int nMode = LVNI_ALL);
	void	LoadLogFile(CString kFileName);

	BOOL	RequestLog();

	void	RefresgLogData();
	void	RemoveAllData();

protected:

	NTradeLogClientProcess*	m_pkTradeLogClientProcess;		// ������ ����ϴ� ��Ʈ��ũ ���μ���

	CPtrArray				m_LogDataList;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
};


