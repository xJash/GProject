// ChildView.h : CChildView Ŭ������ �������̽�
//


#pragma once


// CChildView â

class CChildView : public CWnd
{
// ����
public:
	CChildView();

// Ư��
public:

// �۾�
public:

// ������
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ����
public:
	virtual ~CChildView();

	// �޽��� �� �Լ��� �����߽��ϴ�.
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
};

