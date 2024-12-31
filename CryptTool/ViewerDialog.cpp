//=============================================================================
//
//	ViewerDialog.cpp
//
//	Copyright 2005 HQGame
//
//=============================================================================

#include "stdafx.h"
#include "CryptTool.h"
#include "ViewerDialog.h"

#include "D:/ProjectB/Source/HQCore/HQCorePrivate.h"

//=============================================================================
// CViewerDialog ��ȭ �����Դϴ�.
//=============================================================================
IMPLEMENT_DYNAMIC(CViewerDialog, CDialog)

//=============================================================================
//  @Name   CViewerDialog()
//! @author LeeKH						
//! @date   2005-12-27
//! @param  X   X
//! @return X
//! @brief  
//=============================================================================
CViewerDialog::CViewerDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CViewerDialog::IDD, pParent)
	, m_strViewer(_T(""))
{
}

//=============================================================================
//  @Name   ~CViewerDialog()
//! @author LeeKH						
//! @date   2005-12-27
//! @param  X   X
//! @return X
//! @brief  
//=============================================================================
CViewerDialog::~CViewerDialog()
{
}

//=============================================================================
//  @Name   DoDataExchange()
//! @author LeeKH						
//! @date   2005-12-27
//! @param  X   X
//! @return X
//! @brief  
//=============================================================================
void CViewerDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_VIEW, m_strViewer);
	DDX_Control(pDX, IDC_VIEW, m_edtViewer);
}


BEGIN_MESSAGE_MAP(CViewerDialog, CDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()

//=============================================================================
//  @Name   OnSize()
//! @author LeeKH						
//! @date   2005-12-26
//! @param  X   X
//! @return X
//! @brief  ���̾�α� ũ�Ⱑ �ٲ�� ����Ʈ�ڽ� ũ�� ����
//=============================================================================
void CViewerDialog::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	if (m_edtViewer.m_hWnd != NULL)
	{
		// ���̾�α׿� ����Ʈ �ڽ��� �� ä���.
		m_edtViewer.MoveWindow(0, 0, cx, cy);
	}
}

//=============================================================================
//  @Name   OnInitDialog()
//! @author LeeKH						
//! @date   2005-12-26
//! @param  X   X
//! @return X
//! @brief  �ʱ�ȭ �۾�
//=============================================================================
BOOL CViewerDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	CFileDialog	filedlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
		"CryptText Files (*.txt) |*.txt||", NULL);

	// ���� ����â ����
	if (filedlg.DoModal() == IDOK)
	{
		// ����Ʈ ��Ʈ���� ���� ����
		m_strViewer = "";
//���߿�.
/*
		HQCryptTextFileUA crypttxtUA;
		// ��ȣȭ �� Text���� ����
		if (crypttxtUA.OpenReadable(filedlg.GetPathName()))
		{
			// ���ϸ��� ������ Ÿ��Ʋ�� ����
			this->SetWindowText(filedlg.GetFileName());
			// �� �پ� �о ����Ʈ ��Ʈ�ѿ� �߰�
			while(crypttxtUA.ReadLine())
			{
				m_strViewer += crypttxtUA.GetBuffer();
				m_strViewer += "\r\n";
			}
			UpdateData(FALSE);
			DWORD dwSel = 0;
			dwSel = HIWORD(0);
			dwSel = LOWORD(-1);
			m_edtViewer.SetSel(dwSel);
		}
*/
	}
	else
	{
		OnCancel();
	}	

	return TRUE;
}

// CViewerDialog �޽��� ó�����Դϴ�.
