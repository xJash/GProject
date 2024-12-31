#pragma once

#include "DLGDefine.h"
#include "DiagramEditor/DiagramPropertyDlg.h"
#include "../resource.h"
#include "DLGDefine.h"

// CDLGPropertyDlg ��ȭ �����Դϴ�.
class CDiagramEditor;

class CDLGPropertyDlg : public CDiagramPropertyDlg//public CDialog
{
	DECLARE_DYNAMIC(CDLGPropertyDlg)

public:
	CDLGPropertyDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDLGPropertyDlg();
	virtual void SetValues();
	
	virtual void	ShowProperties( CWnd* parent, BOOL show = TRUE );
	void SetDLGEditor(CDiagramEditor* pDLGEditor);

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DLGPROPERTYDLG };
	//{{AFX_DATA(CDialogSettings)
	// �ڽ�â ���� ���� �� ���ڿ��� �����ǹǷ�..
	CEdit m_editDLG_Property[DLG_PROPERTY_COUNT];
	//}}AFX_DATA

public:
	CWnd* m_pParent;
	CDiagramEditor* m_pDLGEditor;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonDlgApply();
	afx_msg void OnBnClickedButtonDlgClose();
	afx_msg void OnBnClickedButtonDlgSearch();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtonDlgPathEmpty2();
	afx_msg void OnOK();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
