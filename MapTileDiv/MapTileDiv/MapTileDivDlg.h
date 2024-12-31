// MapTileDivDlg.h : ��� ����
//

#pragma once

#include "directives.h"


// CMapTileDivDlg ��ȭ ����
class CMapTileDivDlg : public CDialog
{
// ����
public:
	CMapTileDivDlg(CWnd* pParent = NULL);	// ǥ�� ������

	int EncodeZpr( UI08 *pDestImage, UI08 *pSrcImage, int width, int height );

	void LoadSpr( char *filename, unsigned char **pImg );
	void LoadPCX( char *filename );

	unsigned short m_pal565[ 256 ];
	unsigned short m_pal555[ 256 ];
	unsigned char m_pcxpal[ 768 ];

	unsigned char *m_image;
	int			  m_imagewidth;
	int			  m_imageheight;
	
	unsigned char *m_mask;




// ��ȭ ���� ������
	enum { IDD = IDD_MAPTILEDIV_DIALOG };

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
};
