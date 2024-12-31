// PatchToolDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"

// CPatchToolDlg ��ȭ ����
class CPatchToolDlg : public CDialog
{
// ����
public:
	CPatchToolDlg(CWnd* pParent = NULL);	// ǥ�� ������

// ��ȭ ���� ������
	enum { IDD = IDD_PATCHTOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ����


// ����
protected:
	HICON m_hIcon;

	// �޽��� �� �Լ��� �����߽��ϴ�.
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();

protected:
	CString		m_SVN, m_SVN_Arg0;
	CString		m_IncrediBuild, m_IncrediBuild_Arg0;
	CString		m_PatchFolder;
	CString		m_SourceFolder;
	CString		m_ResourceFolder;
	BOOL		m_bPatching;

protected:
	BOOL ReBuild( LPCSTR pszSolutionPath, LPCSTR pszProjectName, LPCSTR BuildCfg );
	BOOL SvnExistPath( LPCSTR pszPath );
	BOOL SvnBranch( LPCSTR pszSrc, LPCSTR pszBranchTarget );
	BOOL SvnDiff( LPCSTR pszOld, LPCSTR pszNew, CStringArray &files );
	INT  SvnExport( CStringArray &files, LPCSTR pszSVNBase, LPCSTR pszTargetBase );
	BOOL SvnSwitch( LPCSTR pszSVNPath, LPCSTR pszTargetPath );

	BOOL Patch();

	void MakeFolder( LPCSTR pszFolder );
	void AddOutput( LPCSTR pszFormat, ... );

	CString Create_SrcTarget_SVNPath( LPCSTR pszCountry );
	CString GetBuildCfg_DBManager( LPCSTR pszCountry );
	CString GetBuildCfg_Game( LPCSTR pszCountry, BOOL bServer );

	void PumpMessage();

public:
	CComboBox m_combo_Country;
	CComboBox m_combo_patch;

	afx_msg void OnClose();
};
