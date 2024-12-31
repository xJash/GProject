#pragma once
#include "afxwin.h"
#include "afxcmn.h"

enum ENUM_RESULT_COLUMN
{
	RESULT_COLUMN_NUM,
	RESULT_COLUMN_DATE,
	RESULT_COLUMN_SERVER,
	RESULT_COLUMN_COMMAND,
	RESULT_COLUMN_USER,
	RESULT_COLUMN_TARGETUSER,
	RESULT_COLUMN_ITEMUNIQUE,
	RESULT_COLUMN_LOGTEXT
};

struct CResultSort
{
	ENUM_RESULT_COLUMN	Column;
	int					nType;		// 1: Number, 2: String
	int					nSort;		// 1: ��������, 0: ��������
};

// CLogToolResultDlg ��ȭ �����Դϴ�.

class CLogToolResultDlg : public CDialog
{
// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_RESULT_DIALOG };

	DECLARE_DYNAMIC(CLogToolResultDlg)

public:
	CLogToolResultDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CLogToolResultDlg();

private:
	//=============================================================================
	// �ý��� ����
	//=============================================================================
	int				m_nRowCount;
	CNewResultDlg*	m_pChildResultDlg;
	
protected:
	//=============================================================================
	// ��Ʈ�Ѱ� ����Ǵ� ����
	//=============================================================================
	CString		m_strDetailSearchWord;
	CStatic		m_groupboxDetail;
	CEdit		m_editLogText;
	CListCtrl	m_listviewResult;

public:
	//=============================================================================
	// �������̽� �Լ�
	//=============================================================================
	void 			AddLogData(LPCSTR pszDate, LPCSTR pszServer, LPCSTR pszCommand, LPCSTR pszUser, LPCSTR pszTargetUser, LPCSTR pszItemUnique, LPCSTR pszLogText);
	void 			ClearLog();
	BOOL 			Init();

protected:
	//=============================================================================
	// ��� �Լ�
	//=============================================================================
	int	 			AddListCtrlItem(CListCtrl* pListCtrl, int nItem, int nSubItem, char* pszItemText);

	void 			SaveLogFile(CString kFileName, bool bInfo = true);
	void			SaveSelected_LogFile(CString kFileName, bool bInfo = true);
	bool 			LoadLogFile(CString kFileName);

	virtual void	DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL	PreTranslateMessage(MSG* pMsg);

	//=============================================================================
	// �ʱ�ȭ �Լ�
	//=============================================================================
	virtual BOOL	OnInitDialog();

	//=============================================================================
	// �����Լ�
	//=============================================================================
	static int CALLBACK MyCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

	//=============================================================================
	// �̺�Ʈ �ڵ鷯
	//=============================================================================
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonDelSelect();
	afx_msg void OnBnClickedButtonDelDeselect();
	afx_msg void OnBnClickedButtonDetailsearch();
	afx_msg void OnBnClickedButtonSendnewwindow();
	afx_msg void OnBnClickedButtonExport();
	afx_msg void OnNMClickListResult(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonSelexport();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButtonImport();

	//=============================================================================
	// �޽��� �� �Լ��� �����߽��ϴ�.
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnHdnItemclickListResult(NMHDR *pNMHDR, LRESULT *pResult);
};
