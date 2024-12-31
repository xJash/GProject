// GLogClientDlg.h : ��� ����
//

#pragma once

//=============================================================================
//	CLASS   X
//! @brief  �α� �� ���� ���̾�α�
//=============================================================================
class CGLogClientDlg : public CDialog
{
// ��ȭ ���� ������
enum { IDD = IDD_GLOGCLIENT_DIALOG };

// ����
public:
	CGLogClientDlg(CWnd* pParent = NULL);	// ǥ�� ������

public:
	SI32				m_siSearchCount;

protected:
	//=============================================================================
	// �ý��� ����
	//=============================================================================
	HICON m_hIcon;

	NLogClientProcess*	m_pclLogClientProcess;		// ������ ����ϴ� ��Ʈ��ũ ���μ���

	CLogToolBarDlg		m_LogToolBarDlg;			// �α� �˻� ����
	CLogToolResultDlg	m_LogToolResultDlg;			// �α� �˻� ��� ���̾�α�

	BOOL				m_bSearching;				// ���� �˻� ���ΰ�?

public:
	//=============================================================================
	// �������̽� �Լ�
	//=============================================================================
	BOOL RequestLogData(char* pszStartTime, char* pszEndTime, char* pszServerName, char* pszCommand, char* pszCategory, char* pszPersonName, char* pszDstPersonName, char* pszItemUnique, char* pszUserSearch);
	BOOL Stop();

	NLogClientProcess* GetLogClientProcess()		{		return m_pclLogClientProcess;			}

	BOOL AddLogData(stLOGData* pLogData);
	void ClearLog();
	void SearchEnable(BOOL nEnable);

protected:
	//=============================================================================
	// ��� �Լ�
	//=============================================================================
	void			NetworkProcess();
	virtual void	DoDataExchange(CDataExchange* pDX);	// DDX/DDV ����
	virtual BOOL	PreTranslateMessage(MSG* pMsg);

	//=============================================================================
	// �ʱ�ȭ �Լ�
	//=============================================================================
	virtual BOOL	OnInitDialog();

	//=============================================================================
	// �̺�Ʈ �ڵ鷯
	//=============================================================================
	afx_msg void		OnPaint();
	afx_msg HCURSOR		OnQueryDragIcon();
	afx_msg void		OnTimer(UINT nIDEvent);
	afx_msg void		OnDestroy();
	afx_msg void		OnSize(UINT nType, int cx, int cy);

	//=============================================================================
	// �޽��� �� �Լ��� �����߽��ϴ�.
	DECLARE_MESSAGE_MAP()
};
