// ChildView.h : CChildView 클래스의 인터페이스
//


#pragma once


// CChildView 창

class CChildView : public CWnd
{
// 생성
public:
	CChildView();

// 특성
public:

// 작업
public:

// 재정의
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현
public:
	virtual ~CChildView();

	// 메시지 맵 함수를 생성했습니다.
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
};

