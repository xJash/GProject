#pragma once

// CNewResultDlg ��ȭ �����Դϴ�.

class CNewResultDlg : public CDialog
{
	DECLARE_DYNAMIC(CNewResultDlg)

public:
	CNewResultDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CNewResultDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_NEWRESULT_DIALOG };

private:
	//=============================================================================
	// �ý��� ����
	//=============================================================================
	CDialog*		m_pResultDlg;

public:
	//=============================================================================
	// �������̽� �Լ�
	//=============================================================================
	void AddLogData(LPCSTR pszDate, LPCSTR pszServer, LPCSTR pszCommand, LPCSTR pszUser, LPCSTR pszTargetUser, LPCSTR pszItemUnique, LPCSTR pszLogText);

protected:
	//=============================================================================
	// ��� �Լ�
	//=============================================================================
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	//=============================================================================
	// �ʱ�ȭ �Լ�
	//=============================================================================
	virtual BOOL OnInitDialog();

	//=============================================================================
	// �̺�Ʈ �ڵ鷯
	//=============================================================================
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//=============================================================================
	// �޽��� �� �Լ��� �����߽��ϴ�.
	DECLARE_MESSAGE_MAP()
};
