// FieldObjectMergeDlg.h : ��� ����
//

#pragma once


class CFieldObject
{
public:
	CString		m_strName;
	CString		m_ZipName;
};

// CFieldObjectMergeDlg ��ȭ ����
class CFieldObjectMergeDlg : public CDialog
{
// ����
public:
	CFieldObjectMergeDlg(CWnd* pParent = NULL);	// ǥ�� ������
	~CFieldObjectMergeDlg();

// ��ȭ ���� ������
	enum { IDD = IDD_FIELDOBJECTMERGE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ����


// ����
protected:
	HICON m_hIcon;

	CPtrArray		m_arrFieldObject;

	// �޽��� �� �Լ��� �����߽��ϴ�.
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonExecute();
};
