//=============================================================================
//
//	CryptToolDlg.h
//
//	Copyright 2005 HQGame
//
//=============================================================================
#ifndef _CRYPTTOOLDLG_H_
#define _CRYPTTOOLDLG_H_

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#include "D:/ProjectB/Source/HQCore/HQCorePrivate.h"	// HQGame�� ���� Include

//=============================================================================
//	CLASS   CCryptToolDlg
//! @brief  CCryptToolDlg ��ȭ ����
//=============================================================================
class CCryptToolDlg : public CDialog
{
	// ����
public:
	CCryptToolDlg(CWnd* pParent = NULL);	// ǥ�� ������
	~CCryptToolDlg()						// �Ҹ���
	{
		m_imgIcons.DeleteImageList();
	}

	//=============================================================================
	// ��ȭ ���� ������
	//=============================================================================
	enum { IDD = IDD_CRYPTTOOL_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ����

protected:
	HICON m_hIcon;

	//=============================================================================
	// �޽��� �� �Լ��� �����߽��ϴ�.
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	//=============================================================================

public:
	//=============================================================================
	// ��Ʈ�� ����
	//=============================================================================
	CListCtrl m_lstResult;
	CListBox m_lstFolders;

	//=============================================================================
	// �ؽ�Ʈ ��Ʈ�Ѱ� ����� ����
	//=============================================================================
	CString m_wKeyR;
	CString m_wKeyC1;
	CString m_wKeyC2;

	//=============================================================================
	// üũ�ڽ� ��Ʈ�Ѱ� ����� ����
	//=============================================================================
	BOOL m_bDelText;

	//=============================================================================
	// �Ϲ� ����
	//=============================================================================
	CImageList	m_imgIcons;

	//=============================================================================
	// �̺�Ʈ �Լ���
	//=============================================================================
	afx_msg void OnBnClickedBtnprocess();
	afx_msg void OnBnClickedBtnfindfolder();
	afx_msg void OnBnClickedBtnview();
	afx_msg void OnBnClickedBtnadd();
	afx_msg void OnBnClickedBtndel();
	afx_msg void OnBnClickedBtndecode();
	afx_msg void OnBnClickedBtndecodeprocess();
};

#endif

