#pragma once


// CIdView ��ȭ �����Դϴ�.

class CIdView : public CDialog
{
	DECLARE_DYNAMIC(CIdView)

public:
	CIdView(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CIdView();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_IDVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeCombo5();
};
