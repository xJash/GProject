// CCDMergeDlg.h : ��� ����
//

#pragma once


// CCCDMergeDlg ��ȭ ����
class CCCDMergeDlg : public CDialog
{
// ����
public:
	CCCDMergeDlg(CWnd* pParent = NULL);	// ǥ�� ������

// ��ȭ ���� ������
	enum { IDD = IDD_CCDMERGE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ����


// ����
protected:
	HICON m_hIcon;

	// �޽��� �� �Լ��� �����߽��ϴ�.
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonFindpath();
	afx_msg void OnBnClickedButtonExecute();
};
