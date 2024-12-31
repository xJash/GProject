#pragma once
#include "afxdtctl.h"
#include "afxwin.h"

enum
{
	LOGCLIENT_COMMAMDMODE_NONE			= 0,
	LOGCLIENT_COMMAMDMODE_COMMAND		= 1,
	LOGCLIENT_COMMAMDMODE_COMMANDFILTER	= 2,
};

// CLogToolBarDlg ��ȭ �����Դϴ�.

class CLogToolBarDlg : public CDialog
{
// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TOOL_DIALOG };

	DECLARE_DYNAMIC(CLogToolBarDlg)

public:
	CLogToolBarDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CLogToolBarDlg();

protected:
	//=============================================================================
	// �ý��� ����
	//=============================================================================
	CStringArray	m_FilterArray;
	SI32			m_siCommandMode;

	//=============================================================================
	// ��Ʈ�Ѱ� ����Ǵ� ����
	//=============================================================================
	CString 		m_strServerName;
	CString 		m_strPersonName;
	CString 		m_strDate;
	CString 		m_strStartTime;
	CString 		m_strEndTime;
	CString 		m_strSearchWord;
	CString 		m_strCommandFilter;
	CString			m_strTargetName;
	CString			m_strCommand;
	CString			m_strItemUnique;

public:
	//=============================================================================
	// �������̽� �Լ�
	//=============================================================================
	BOOL			Init();

protected:
	//=============================================================================
	// ��� �Լ�
	//=============================================================================
	virtual void	DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL	PreTranslateMessage(MSG* pMsg);

	BOOL			LoadServerName(LPCTSTR pszFileName);
	BOOL			LoadCommandFilter(LPCTSTR pszFileName);

	//=============================================================================
	// �̺�Ʈ �ڵ鷯
	//=============================================================================
	afx_msg void	OnBnClickedBtnSearch();
	afx_msg void	OnBnClickedButtonStop();
	afx_msg void	OnBnClickedRadioCommand();

	//=============================================================================
	// �ʱ�ȭ �Լ�
	//=============================================================================
	virtual BOOL	OnInitDialog();

	//=============================================================================
	// �޽��� �� �Լ��� �����߽��ϴ�.
	DECLARE_MESSAGE_MAP()
};
