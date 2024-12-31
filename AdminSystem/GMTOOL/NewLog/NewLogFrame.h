#pragma once

#include "NewLogView.h"
#include "NNewLogClientProcess.h"
#include "../../NGameDataManager/NGameDataManager.h"
#include "../ItemManagerClient.h"
#include "../../DBManager/LogDBManager/LogDBMsg.h"

#define NEWLOGCLIENT_NETWORK_TIMER			120
#define NEWLOGCLIENT_NETWORK_TIMER_ELAPSE	20

#define NEWLOGCLIENT_SHOW_TIMER				200
#define NEWLOGCLIENT_SHOW_TIMER_ELAPSE		300

#define NEWLOGCLIENT_MAX_COLUMN				75

// CNewLogFrame �������Դϴ�.

class CNewLogFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CNewLogFrame)
protected:
	CNewLogFrame();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CNewLogFrame();

	

public:
	CNewLogView			m_wndView;
	SI32				m_siSearchCount;
	BOOL				m_bSearching;				// ���� �˻� ���ΰ�?

	HCURSOR				m_hArrowCursor;
	HCURSOR				m_hWaitCursor;

	cltItemManagerClient* m_pclItemManagerClient;

public:
	NNewLogClientProcess*	GetLogClientProcess()		{	return m_pkNewLogClientProcess;	}

	void	SearchEnable(BOOL nEnable);
	BOOL	AddLogData(stNewLOGData* pLogData, SI32 siDataCount = MAX_STLOGDATA_PER_PACKET);
	BOOL	RequestLogData(sDBRequest_NewLog* pNewLogMsg);
	BOOL	Stop();
	void	SaveLogFile(CString kFileName, int nMode = LVNI_ALL);
	void	LoadLogFile(CString kFileName);

	BOOL	RequestLog();

	void	RefresgLogData();
	void	RemoveAllData();
	BOOL	DeleteLogData(SI32 siIndex);

	BOOL ConvertToLogDataToStringData( stNewLOGData* pLogData, cltNewLogString* pStringData, int nMaxStringData );

	stNewLOGData* GetNewLogData(int siIndex);

	void ActivateFrame(int nCmdShow = -1);
protected:

	NNewLogClientProcess*	m_pkNewLogClientProcess;		// ������ ����ϴ� ��Ʈ��ũ ���μ���

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


