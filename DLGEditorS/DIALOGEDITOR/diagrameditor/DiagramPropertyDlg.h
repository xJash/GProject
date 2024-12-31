	#ifndef _DIAGRAMPROPERTYDLG_H_
#define _DIAGRAMPROPERTYDLG_H_

#include "DiagramEntity.h"

#include "../../FileNameTokenizer.h"
#include "../../SprFile/SprFile.h"
#include "../../MyDefine/MyDefine.h"

#include "../StdGrfx.h"

class CDiagramEntity;
class CDiagramPropertyDlg : public CDialog
{
public:
	/**
	leon add
	* picture property double buffering
	*/
	void			MakeMemDC( CDC* dc, int tileImageStartFont = 0, int tileImageNum = 1);
	void			DrawImageOnMemDC(CDC* dc, int tileImageStartFont = 0, int tileImageNum = 1,  DWORD col_dest = TRANSPARENT_COLOR, DWORD col_src = TRANSPARENT_COLOR, DWORD col_exclusive_src = 0xffffffff, BOOL bexclusive = false );
	void			BitBltDS(CDC* dest, CDC* src, int dest_width, int dest_height, int src_width, int src_height, DWORD mode=SRCCOPY, int src_x=0, int src_y=0, int dest_x=0, int dest_y=0);

	bool			DrawTileImg( CDC* dest, SI16 PutSprOption, /*SI16 PutSprParam1,*/ SI16 PutSprParam2, SI16 XPos, SI16 YPos, SI16 Width, SI16 Height, SI16 TileImgNum, bool IsRowTile = true );

	void			DrawMiniPicture(CDC* in_pDC, int in_TileCount );
	void			DeleteAllBufferDC();
	void			DeleteAllBmp();
	void			ClearAllOldBmp();

	CDC*			GetBufferDC(int index);

	// font ���� ���̾�α� ���� ����
	void			ShowFontDialog();

	CString			GetFontName();
	int				GetFontColor();
	int				GetFontSize();

	// �� ��Ʈ�� ���� �۾� ���� �Լ���
	virtual void	SetValues() = 0;

	// ���� �̸��� �м��ؼ� .. �� ��Ʈ�� �Ӽ� �Ϻ�(Ÿ�� ���, Ÿ�� ����)
	// ���� �м� �ؿ´�.
	bool			ParsingFileFullPath(CString fullPath);
	CString			GetTileImageNum();
	CString			GetTileMode();

public:

	CDiagramPropertyDlg( UINT res, CWnd* parent );
	~CDiagramPropertyDlg();

	BOOL Create( UINT nIDTemplate, CWnd* pParentWnd );

	void			SetEntity( CDiagramEntity* entity );
	CDiagramEntity*	GetEntity() const;

	virtual CWnd*	GetRedrawWnd();
	virtual void	SetRedrawWnd( CWnd* redrawWnd );
	virtual void	Redraw();

	/**
	leon add
	* ������Ƽ ��ȭ���ڿ��� �Է� ���� ������ �����ϰ� ǥ��
	*/
	CString m_picFullPath;
	CString m_oldPicFullPath;

	CDC* m_pbufferDC[MAX_CONTROL_BUFFER_LENGTH];
	CBitmap* m_pmemBmp[MAX_CONTROL_BUFFER_LENGTH];
	CBitmap* m_pOldBmp[MAX_CONTROL_BUFFER_LENGTH];

	cltTSpr m_spr;

	// ��Ʈ�� ������Ƽ�� ��Ʈ �Ӽ� �߰�
	LOGFONT m_logFont;
	CString		m_fontName;
	int		m_fontSize;
	COLORREF m_fontColor;

	// FileName Parsing �� ���� �������
	// ���� �̸��� �м��ؼ� .. �� ��Ʈ�� �Ӽ� �Ϻ�(Ÿ�� ���, Ÿ�� ����)
	// ���� �м� �ؿ´�.
	CFileNameTok m_fileNameInfo;

	bool m_bError;	// �Ӽ��� ���� �߻� !! => �˾�â �ȴݱ� ����

private:
	CDiagramEntity*	m_entity;
	CWnd*			m_redrawWnd;

protected:
    afx_msg void OnPaint();

    DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};

#endif // _DIAGRAMPROPERTYDLG_H_