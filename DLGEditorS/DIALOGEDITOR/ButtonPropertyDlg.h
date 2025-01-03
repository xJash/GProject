#if !defined(AFX_BUTTONPROPERTYDLG_H__6A91D1F2_5F64_4AEC_9C04_4D7874D357E5__INCLUDED_)
#define AFX_BUTTONPROPERTYDLG_H__6A91D1F2_5F64_4AEC_9C04_4D7874D357E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ButtonPropertyDlg.h : header file
//

#include "DLGDefine.h"
#include "DiagramEditor/DiagramPropertyDlg.h"
#include "../resource.h"
#include "afxwin.h"

/////////////////////////////////////////////////////////////////////////////
// CButtonPropertyDlg dialog

class CButtonPropertyDlg : public CDiagramPropertyDlg
{
// Construction
public:
	CButtonPropertyDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CButtonPropertyDlg)
	enum { IDD = IDD_DIALOG_BUTTON_PROPERTIES };
	CEdit	m_editBTN_Property[BTN_PROPERTY_COUNT];
//}}AFX_DATA

	virtual void SetValues();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CButtonPropertyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CButtonPropertyDlg)
	afx_msg void OnPaint();
	afx_msg void OnButtonApply();
	afx_msg void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedHide();
	afx_msg void OnBnClickedButtonBtnSearch();
	afx_msg void OnBnClickedButtonBtnPathEmpty();
	afx_msg void OnBnClickedButtonBtnTextSearch();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUTTONPROPERTYDLG_H__6A91D1F2_5F64_4AEC_9C04_4D7874D357E5__INCLUDED_)
