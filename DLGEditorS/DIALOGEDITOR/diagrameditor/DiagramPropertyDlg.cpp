#include "stdafx.h"
#include "DiagramPropertyDlg.h"
#include ".\diagrampropertydlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDiagramPropertyDlg
//
// ��Ʈ�� ���� ���� ����
extern CTRL_PROPERTY_COUNT_INFO ctrlnum[CTRL_COUNT];

CDiagramPropertyDlg::CDiagramPropertyDlg( UINT res, CWnd* parent ) : CDialog( res, parent )
{

	m_entity = NULL;
	m_redrawWnd = NULL;
	m_bError = false;

	for(int i=0; i<MAX_CONTROL_BUFFER_LENGTH; i++)
	{
        m_pbufferDC[i] = NULL;
		m_pmemBmp[i] = NULL;
		m_pOldBmp[i] = NULL;
	}
}

CDiagramPropertyDlg::~CDiagramPropertyDlg()
{
	DeleteAllBmp();
	DeleteAllBufferDC();
	ClearAllOldBmp();
}

BEGIN_MESSAGE_MAP(CDiagramPropertyDlg, CDialog)
	//{{AFX_MSG_MAP(CEditPropertyDlg)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

/**
leon add
* ������Ƽ ��ȭ���� �̹��� �̸����� ���
*/
void CDiagramPropertyDlg::OnPaint()
{
	if(GetEntity())
	{
		if(GetEntity()->m_pProperty != NULL)
		{
			if(m_picFullPath != STR_EMPTY && GetBufferDC(MASK_BACKGROUND_NUM) && GetBufferDC(REAL_BACKGROUND_NUM))
			{
				CRect rect(MINI_PICTURE_LEFT, MINI_PICTURE_TOP, MINI_PICTURE_LEFT + MINI_PICTURE_WIDTH, MINI_PICTURE_TOP + MINI_PICTURE_HEIGHT);

				CStdGrfx::draw3dFrame(this->GetDC(), rect);

				CString tmpCStr;
				int iTmp = -1;
				int iTileNum = -1;
				if( m_entity == NULL || m_entity->m_pProperty == NULL || m_spr.clHeader.siXsize < 1 || m_spr.clHeader.siYsize < 1 ) return;
				tmpCStr = m_entity->m_pProperty[ BG_TILE_IMAGE_NUM ];
				iTmp = _tstoi( tmpCStr );

				DrawMiniPicture( GetBufferDC(WORK_BACKGROUND_NUM), iTmp );

				//CStdGrfx::drawframed3dBox( this->GetDC(), rect );

				//BitBltDS( this->GetDC(), GetBufferDC(MASK_BACKGROUND_NUM), MINI_PICTURE_WIDTH, MINI_PICTURE_HEIGHT, m_spr.clHeader.siXsize, m_spr.clHeader.siYsize, SRCAND, 0, 0, MINI_PICTURE_LEFT, MINI_PICTURE_TOP);
				//BitBltDS( this->GetDC(), GetBufferDC(REAL_BACKGROUND_NUM), MINI_PICTURE_WIDTH, MINI_PICTURE_HEIGHT, m_spr.clHeader.siXsize, m_spr.clHeader.siYsize, SRCPAINT, 0, 0, MINI_PICTURE_LEFT, MINI_PICTURE_TOP);

				//CStdGrfx::drawframed3dBox( GetBufferDC(WORK_BACKGROUND_NUM), rect );

				//BitBltDS( GetBufferDC(WORK_BACKGROUND_NUM), GetBufferDC(MASK_BACKGROUND_NUM), MINI_PICTURE_WIDTH, MINI_PICTURE_HEIGHT, m_spr.clHeader.siXsize, m_spr.clHeader.siYsize, SRCAND, 0, 0, MINI_PICTURE_LEFT, MINI_PICTURE_TOP);
				//BitBltDS( GetBufferDC(WORK_BACKGROUND_NUM), GetBufferDC(REAL_BACKGROUND_NUM), MINI_PICTURE_WIDTH, MINI_PICTURE_HEIGHT, m_spr.clHeader.siXsize, m_spr.clHeader.siYsize, SRCPAINT, 0, 0, MINI_PICTURE_LEFT, MINI_PICTURE_TOP);
				//BitBltDS( this->GetDC(), GetBufferDC(WORK_BACKGROUND_NUM), MINI_PICTURE_WIDTH, MINI_PICTURE_HEIGHT, m_spr.clHeader.siXsize, m_spr.clHeader.siYsize, SRCCOPY, 0, 0, MINI_PICTURE_LEFT, MINI_PICTURE_TOP);

			}
			else
			{
				CRect rect(MINI_PICTURE_LEFT, MINI_PICTURE_TOP, MINI_PICTURE_LEFT + MINI_PICTURE_WIDTH, MINI_PICTURE_TOP + MINI_PICTURE_HEIGHT);
				CStdGrfx::drawframed3dBox( this->GetDC(), rect );
			}
		}
	}

	CDialog::OnPaint();
}

void CDiagramPropertyDlg::SetEntity( CDiagramEntity* entity )
/* ============================================================
	Function :		CDiagramPropertyDlg::SetEntity
	Description :	Sets the "CDiagramEntity"-entity derived 
					object that is associated with this dialog.
	Access :		Public

	Return :		void
	Parameters :	CDiagramEntity* entity	-	Set the object 
												for this dialog.
					
	Usage :			Call to set the "CDiagramEntity"-derived
					object to be associated with this dialog.

   ============================================================*/
{

	m_entity = entity;

}

CDiagramEntity* CDiagramPropertyDlg::GetEntity() const
/* ============================================================
	Function :		CDiagramPropertyDlg::GetEntity
	Description :	Returns the "CDiagramEntity" object of this 
					dialog
	Access :		Public

	Return :		CDiagramEntity*	-	The object attached to 
										this dialog
	Parameters :	none

	Usage :			Call to get the "CDiagramEntity"-derived 
					object associated to this dialog.

   ============================================================*/
{

	return m_entity;

}

BOOL CDiagramPropertyDlg::Create( UINT nIDTemplate, CWnd* pParentWnd )
/* ============================================================
	Function :		CDiagramPropertyDlg::Create
	Description :	Creates the dialog.
	Access :		Public

	Return :		BOOL				-	"TRUE" if window was 
											created ok.
	Parameters :	UINT nIDTemplate	-	Resource id of 
											dialog template.
					CWnd* pParentWnd	-	Parent of dialog 
											(normally the 
											"CDiagramEditor")
					
	Usage :			Called internally to create the property 
					dialog.

   ============================================================*/
{

	BOOL result;
	

	result = CDialog::Create( nIDTemplate, pParentWnd );

	SetRedrawWnd( pParentWnd );

	return result;

}

CWnd* CDiagramPropertyDlg::GetRedrawWnd() 
/* ============================================================
	Function :		CDiagramPropertyDlg::GetRedrawWnd
	Description :	Get the window that should be redrawn when 
					changes are made in this dialog.
	Access :		Public

	Return :		CWnd*	-	The window
	Parameters :	none

	Usage :			Call to get the window that should be 
					redrawn when applying changes in the box. 
					This member is used as the editor will not 
					redraw properly in a MDI-application 
					("GetParent()" returns the frame instead of 
					the editor).

   ============================================================*/
{ 

	return m_redrawWnd; 

}

void CDiagramPropertyDlg::SetRedrawWnd( CWnd* redrawWnd ) 
/* ============================================================
	Function :		CDiagramPropertyDlg::SetRedrawWnd
	Description :	Set the window that should be redrawn in 
					response to changes in this dialog.
	Access :		Public

	Return :		void
	Parameters :	CWnd* redrawWnd	-	Normally the editor.
					
	Usage :			Call to set the window that should be 
					redrawn when applying changes in the box. 
					This member is used as the editor will not 
					redraw properly in a MDI-application 
					("GetParent()" returns the frame instead of 
					the editor).

   ============================================================*/
{ 

	m_redrawWnd = redrawWnd; 

}

void CDiagramPropertyDlg::Redraw() 
/* ============================================================
	Function :		CDiagramPropertyDlg::Redraw
	Description :	Redraw the parent window of the dialog.
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Call to redraw the editor window when 
					applying changes in the box. 
					This member is used as the editor will not 
					redraw properly in a MDI-application 
					("GetParent()" returns the frame instead of 
					the editor).


   ============================================================*/
{ 

	CWnd* wnd = GetRedrawWnd();
	if( wnd )
		wnd->RedrawWindow();

}

CDC* CDiagramPropertyDlg::GetBufferDC(int index)
{
	return m_pbufferDC[index];
}

void CDiagramPropertyDlg::ClearAllOldBmp()
{
	for(int i=0; i<MAX_CONTROL_BUFFER_LENGTH; i++)
	{
		if(m_pOldBmp[i])
			m_pOldBmp[i] = NULL;
	}		
}

void CDiagramPropertyDlg::DeleteAllBmp()
{
	for(int i=0; i<MAX_CONTROL_BUFFER_LENGTH; i++)
	{
		if(m_pmemBmp[i])
		{
			delete m_pmemBmp[i];
			m_pmemBmp[i] = NULL;
		}
	}
}

void CDiagramPropertyDlg::DeleteAllBufferDC()
{
	for(int i=0; i<MAX_CONTROL_BUFFER_LENGTH; i++)
	{
	    if(m_pbufferDC[i])
		{
			m_pbufferDC[i]->FillSolidRect(0, 0, m_spr.clHeader.siXsize, m_spr.clHeader.siYsize, TRANSPARENT_COLOR);
			delete m_pbufferDC[i];
			m_pbufferDC[i] = NULL;
		}
	}
}

void CDiagramPropertyDlg::MakeMemDC( CDC* dc, int tileImageStartFont, int tileImageNum )
{
	// bufferDC�� ������ �̹� �����ϸ� ������ ����
	cltTSpr *pSpr = &m_spr;
	
	// mask buffer, real buffer ...
	ASSERT(MAX_CONTROL_BUFFER_LENGTH >= 2);

	int i=0;

	if(tileImageNum < 1 || tileImageStartFont< 0)
		return;

	/**
	* m_pbufferDC : �޸�DC�� �̹��� �ε���
	*/
	for(i=0; i<MAX_CONTROL_BUFFER_LENGTH; i++)
	{
		if(!m_pbufferDC[i])
		{
			m_pbufferDC[i] = new CDC;
			m_pbufferDC[i]->CreateCompatibleDC( dc );
		}

		// memory bmp
		if(!m_pmemBmp[i])
		{
			m_pmemBmp[i] = new CBitmap;
			m_pmemBmp[i]->CreateCompatibleBitmap( dc, pSpr->clHeader.siXsize * tileImageNum, pSpr->clHeader.siYsize );
		}

		if(!m_pOldBmp[i])
		{
			// m_pOldBmp�� �����͸� ����� ���̹Ƿ� new �Ҵ� �ʿ����
			m_pOldBmp[i] = (CBitmap*) m_pbufferDC[i]->SelectObject(m_pmemBmp[i]);
		}
	}

	// ���Ϸκ��� �о���� ���� �̹��� ���� ( tile image num ���� ��ŭ �ѹ��� ����)
	DrawImageOnMemDC( m_pbufferDC[REAL_BACKGROUND_NUM], tileImageStartFont, tileImageNum);

	// ���Ϸκ��� �о ����ũ ��Ʈ���� ����
	// ����κ� : ���
	// ����κ� : ������
	 //( tile image num ���� ��ŭ �ѹ��� ����)
	DrawImageOnMemDC(m_pbufferDC[MASK_BACKGROUND_NUM], tileImageStartFont, tileImageNum, WHITE_COLOR, TRANSPARENT_COLOR, TRANSPARENT_COLOR, true);

}

void CDiagramPropertyDlg::BitBltDS(CDC* dest, CDC* src, int dest_width, int dest_height, int src_width, int src_height, DWORD mode, int src_x, int src_y, int dest_x, int dest_y)
{
	double zoom_width=0, zoom_height=0;

	zoom_width = dest_width/1;
	zoom_height = dest_height/1;

	//if(	zoom_width > m_spr.clHeader.siXsize )
	//	zoom_width = m_spr.clHeader.siXsize;
	//
	//if(	zoom_height > m_spr.clHeader.siYsize )
	//	zoom_height = m_spr.clHeader.siYsize;

	if(dest !=NULL && src !=NULL)
	{
		dest->StretchBlt(dest_x, dest_y, dest_width, dest_height, src, src_x, src_y, src_width, src_height, mode);
	}
}

// ratio : default value�� 1��
void CDiagramPropertyDlg::DrawImageOnMemDC(CDC* dc, int tileImageStartFont, int tileImageNum, DWORD col_dest, DWORD col_src, DWORD col_exclusive_src, BOOL bexclusive )
{
	int i, j, k, m=0;
	DWORD color;
	unsigned char *psrc;

	// �̹��� ������ �ε��� �ȵǾ��ų� �� ��Ʈ �� ���� Ÿ�� �̹��� ���� �� ũ�� ����
	if(m_spr.Image == NULL || m_spr.clHeader.siFontNum < tileImageNum || m_spr.clHeader.siFontNum < tileImageStartFont + tileImageNum)
		return;

	cltTSpr *pSpr = &m_spr;
	CDC *pDC = dc;

	for(m = tileImageStartFont; m< tileImageStartFont+tileImageNum; m++)
	{
		psrc = &m_spr.Image[ m_spr.clHeader.clImgInfo[ m ].siStartPos ];

		for( i = 0; i < pSpr->clHeader.siYsize; ++i ) {

			j = 0;

			while( j < pSpr->clHeader.siXsize ) {

				if( *psrc == 254 ) {
				
					// pixel skip�ϱ�
					++psrc;

					for(k=0; k<*psrc; k++)
					{
						pDC->SetPixel( j + (m-tileImageStartFont)*(pSpr->clHeader.siXsize), i, col_dest );
						j++;
					}

					//j += *psrc;
					++psrc;

				} else {

					int cnt = 0;

					// DrawMpr�̶��
					if(pSpr->clHeader.siSprType !=0)
					{
						cnt = *psrc;
						++psrc;
					}
					else // DrawSpr�̶��
					{
						cnt = 1;
					}

					for( k = 0; k < cnt; ++k ) 
					{
						// 16�ȷ�Ʈ���� �÷� �о����
						WORD c, r, g, b; 

						c = pSpr->pal[ *psrc ];

						// r, g, b �� ����  (565�ȷ�Ʈ ���� : LoadSpr���� 565�� �о����Ƿ�)
						r = (c & RGB16_565_RMASK) >> 11;
						g = (c & RGB16_565_GMASK) >> 5;
						b = (c & RGB16_565_BMASK);

						// r(0~31), g(0~63), b(0~31) ���� 0~255������ ������ ��ȯ

						r = r << 3;		// 5bit -> 8bit
						g = g << 2;		// 6bit -> 8bit
						b = b << 3;		// 5bit -> 8bit

						color = RGB( r, g, b );
						
						if( color == col_src )
							pDC->SetPixel( j + (m-tileImageStartFont)*(pSpr->clHeader.siXsize), i, col_dest );
						else
						{
							if(bexclusive)
								pDC->SetPixel( j + (m-tileImageStartFont)*(pSpr->clHeader.siXsize), i, col_exclusive_src);
							else
								pDC->SetPixel( j + (m-tileImageStartFont)*(pSpr->clHeader.siXsize), i, color);
						}

						++psrc;
						++j;
					}//for(k..)
				}
			} //while(j..)
		}// for(i..)
	}// for( m...)
}

bool CDiagramPropertyDlg::DrawTileImg( CDC* dest, SI16 PutSprOption, /*SI16 PutSprParam1,*/ SI16 PutSprParam2, SI16 XPos, SI16 YPos, SI16 Width, SI16 Height, SI16 TileImgNum, bool IsRowTile)
{
	bool LeftTileXSize = false;
	bool LeftTileYSize = false;

	SI16 TileXSize = m_spr.clHeader.siXsize;
	SI16 TileYSize = m_spr.clHeader.siYsize;

	// Ÿ���� ������ ���� �� �ִ��� üũ ( �� ���ų�, �ʰ��� ������ �ȵ����� )
	// �Ʒ� 3�� �ּ� ó���� ������, �Ʒ� �ڵ忡 �ش��ϴ� ��쿡�� 
	// ����� ���� �ϰ�����, �� �κ��� �� ��� ��.
	/*
	if ( ( Width % TileXSize ) != 0 || ( Height % TileYSize ) != 0 )
	{
	return false;
	}
	*/

	SI16 RowNum = Height / TileYSize;

	if ( Height % TileYSize != 0 )
	{
		LeftTileXSize = true;
	}

	SI16 ColumnNum = Width / TileXSize;
	if ( Width % TileXSize != 0 )
	{
		LeftTileYSize = true;
	}

	/*
	SI16 i = 0;
	SI16 j = 0;
	*/

	SI16 CurrentDrawXPos = XPos;
	SI16 CurrentDrawYPos = YPos;

	// Ÿ�� 3���� �̷���� �̹���
	if ( TileImgNum == 3 )
	{	
		if ( IsRowTile )
		{
			// �Ʒ� ��º� �ϳ��� ��밡��������, ���� ���� ������ �ȿ��� switch �� for �� ������ ���� �� ���ٴ�,
			// �Ʒ��� ���� �ѹ��� ���� �ϴ� ������ ���� ����� ���ؼ� �ڵ带 �÷���.
			switch( PutSprOption )
			{
			case SPR_PUTSPRT:
				{
					for ( CurrentDrawXPos = XPos; CurrentDrawXPos < XPos + Width; CurrentDrawXPos+=TileXSize )
					{
						for ( CurrentDrawYPos = YPos; CurrentDrawYPos < YPos + Height; CurrentDrawYPos+=TileYSize )
						{
							if ( CurrentDrawXPos + TileXSize >= XPos + Width )
							{
								CurrentDrawXPos = XPos + Width - TileXSize;
							}
							else if ( CurrentDrawXPos + TileXSize > XPos + Width - TileXSize )
							{
								CurrentDrawXPos = XPos + Width - TileXSize * 2;
							}

							if ( CurrentDrawYPos + TileYSize > YPos + Height )
							{
								CurrentDrawYPos = YPos + Height - TileYSize;
							}

							if ( CurrentDrawXPos < XPos + 1 )
							{
								//pTileImg->PutSprT( CurrentDrawXPos, CurrentDrawYPos, PutSprParam1 );
								BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 0*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
								BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 0*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
							}
							else if ( CurrentDrawXPos >= XPos + Width - TileXSize )
							{	
								//pTileImg->PutSprT( CurrentDrawXPos, CurrentDrawYPos, PutSprParam1 + 2 );
								BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 2*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
								BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 2*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
							}
							else
							{	
								//pTileImg->PutSprT( CurrentDrawXPos, CurrentDrawYPos, PutSprParam1 + 1 );
								BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 1*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
								BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 1*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
							}							
						}
					}
				}
				break;
			case SPR_PUTSPRALPHAT:
				{
					for ( CurrentDrawXPos = XPos; CurrentDrawXPos < XPos + Width; CurrentDrawXPos+=TileXSize )
					{
						for ( CurrentDrawYPos = YPos; CurrentDrawYPos < YPos + Height; CurrentDrawYPos+=TileYSize )
						{
							if ( CurrentDrawXPos + TileXSize >= XPos + Width )
							{
								CurrentDrawXPos = XPos + Width - TileXSize;
							}
							else if ( CurrentDrawXPos + TileXSize > XPos + Width - TileXSize )
							{
								CurrentDrawXPos = XPos + Width - TileXSize * 2;
							}

							if ( CurrentDrawYPos + TileYSize > YPos + Height )
							{
								CurrentDrawYPos = YPos + Height - TileYSize;
							}

							if ( CurrentDrawXPos < XPos + 1 )
							{	
								//pTileImg->PutSprAlphaT( CurrentDrawXPos, CurrentDrawYPos, PutSprParam1, PutSprParam2 );
								BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 0*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
								BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 0*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
							}
							else if ( CurrentDrawXPos >= XPos + Width - TileXSize )
							{	
								//pTileImg->PutSprAlphaT( CurrentDrawXPos, CurrentDrawYPos, PutSprParam1 + 2, PutSprParam2 );
								BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 2*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
								BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 2*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
							}
							else
							{	
								//pTileImg->PutSprAlphaT( CurrentDrawXPos, CurrentDrawYPos, PutSprParam1 + 1, PutSprParam2 );
								BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 1*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
								BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 1*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
							}							
						}
					}
				}
				break;
			default:
				return false;
			}
		}
		else
		{
			// �Ʒ� ��º� �ϳ��� ��밡��������, ���� ���� ������ �ȿ��� switch �� for �� ������ ���� �� ���ٴ�,
			// �Ʒ��� ���� �ѹ��� ���� �ϴ� ������ ���� ����� ���ؼ� �ڵ带 �÷���.
			switch( PutSprOption )
			{
			case SPR_PUTSPRT:
				{
					for ( CurrentDrawXPos = XPos; CurrentDrawXPos < XPos + Width; CurrentDrawXPos+=TileXSize )
					{
						for ( CurrentDrawYPos = YPos; CurrentDrawYPos < YPos + Height; CurrentDrawYPos+=TileYSize )
						{
							if ( CurrentDrawXPos + TileXSize > XPos + Width )
							{
								CurrentDrawXPos = XPos + Width - TileXSize;
							}

							if ( CurrentDrawYPos + TileYSize >= YPos + Height )
							{
								CurrentDrawYPos = YPos + Height - TileYSize;
							}
							else if ( CurrentDrawYPos + TileYSize > YPos + Height - TileYSize )
							{
								CurrentDrawYPos = YPos + Height - TileYSize * 2;
							}

							if ( CurrentDrawYPos < YPos + 1 )
							{
								//pTileImg->PutSprT( CurrentDrawXPos, CurrentDrawYPos, PutSprParam1 );
								BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 0*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
								BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 0*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
							}
							else if ( CurrentDrawYPos >= YPos + Height - TileYSize )
							{	
								//pTileImg->PutSprT( CurrentDrawXPos, CurrentDrawYPos, PutSprParam1 + 2 );
								BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 2*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
								BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 2*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
							}
							else
							{	
								//pTileImg->PutSprT( CurrentDrawXPos, CurrentDrawYPos, PutSprParam1 + 1 );
								BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 1*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
								BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 1*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
							}							
						}
					}
				}
				break;
			case SPR_PUTSPRALPHAT:
				{
					for ( CurrentDrawXPos = XPos; CurrentDrawXPos < XPos + Width; CurrentDrawXPos+=TileXSize )
					{
						for ( CurrentDrawYPos = YPos; CurrentDrawYPos < YPos + Height; CurrentDrawYPos+=TileYSize )
						{
							if ( CurrentDrawXPos + TileXSize > XPos + Width )
							{
								CurrentDrawXPos = XPos + Width - TileXSize;
							}

							if ( CurrentDrawYPos + TileYSize >= YPos + Height )
							{
								CurrentDrawYPos = YPos + Height - TileYSize;
							}
							else if ( CurrentDrawYPos + TileYSize > YPos + Height - TileYSize )
							{
								CurrentDrawYPos = YPos + Height - TileYSize * 2;
							}

							if ( CurrentDrawYPos < YPos + 1 )
							{
								//pTileImg->PutSprAlphaT( CurrentDrawXPos, CurrentDrawYPos, PutSprParam1 + 0, PutSprParam2 );
								BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 0*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
								BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 0*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
							}
							else if ( CurrentDrawYPos >= YPos + Height - TileYSize )
							{	
								//pTileImg->PutSprAlphaT( CurrentDrawXPos, CurrentDrawYPos, PutSprParam1 + 2, PutSprParam2 );
								BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 2*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
								BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 2*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
							}
							else
							{	
								//pTileImg->PutSprAlphaT( CurrentDrawXPos, CurrentDrawYPos, PutSprParam1 + 1, PutSprParam2 );
								BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 1*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
								BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 1*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
							}							
						}
					}
				}
				break;
			default:
				return false;
			}
		}
	}
	else if ( TileImgNum == 9 )		// Ÿ�� 9���� �̷���� �̹���
	{
		// �Ʒ� ��º� �ϳ��� ��밡��������, ���� ���� ������ �ȿ��� switch �� for �� ������ ���� �� ���ٴ�,
		// �Ʒ��� ���� �ѹ��� ���� �ϴ� ������ ���� ����� ���ؼ� �ڵ带 �÷���.
		switch( PutSprOption )
		{
		case SPR_PUTSPRT:
			{
				for ( CurrentDrawXPos = XPos; CurrentDrawXPos < XPos + Width; CurrentDrawXPos+=TileXSize )
				{
					for ( CurrentDrawYPos = YPos; CurrentDrawYPos < YPos + Height; CurrentDrawYPos+=TileYSize )
					{
						if ( CurrentDrawXPos + TileXSize > XPos + Width )
						{
							CurrentDrawXPos = XPos + Width - TileXSize;
						}

						if ( CurrentDrawYPos + TileYSize > YPos + Height )
						{
							CurrentDrawYPos = YPos + Height - TileYSize;
						}

						if ( CurrentDrawXPos > XPos && CurrentDrawYPos > YPos && 
							CurrentDrawXPos < XPos + Width - TileXSize && CurrentDrawYPos < YPos + Height - TileYSize )
						{
							//pTileImg->PutSprT( CurrentDrawXPos, CurrentDrawYPos, PutSprParam1 + 4 );
							BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 4*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
							BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 4*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
						}
						else
						{
							if ( CurrentDrawXPos < XPos + 1 )
							{
								if ( CurrentDrawYPos < YPos + 1 )
								{
									//pTileImg->PutSprT( CurrentDrawXPos, CurrentDrawYPos, PutSprParam1 );
									BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 0*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
									BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 0*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
								}
								else if ( CurrentDrawYPos >= YPos + Height - TileYSize )
								{
									//pTileImg->PutSprT( CurrentDrawXPos, CurrentDrawYPos, PutSprParam1 + 6 );
									BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 6*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
									BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 6*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
								}
								else
								{
									//pTileImg->PutSprT( CurrentDrawXPos, CurrentDrawYPos, PutSprParam1 + 3 );
									BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 3*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
									BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 3*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
								}
							}
							else if ( CurrentDrawXPos >= XPos + Width - TileXSize )
							{
								if ( CurrentDrawYPos < YPos + 1 )
								{
									//pTileImg->PutSprT( CurrentDrawXPos, CurrentDrawYPos, PutSprParam1 + 2 );
									BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 2*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
									BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 2*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
								}
								else if ( CurrentDrawYPos >= YPos + Height - TileYSize )
								{
									//pTileImg->PutSprT( CurrentDrawXPos, CurrentDrawYPos, PutSprParam1 + 8 );
									BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 8*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
									BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 8*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
								}
								else
								{
									//pTileImg->PutSprT( CurrentDrawXPos, CurrentDrawYPos, PutSprParam1 + 5 );
									BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 5*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
									BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 5*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
								}
							}
							else if ( CurrentDrawYPos < YPos + 1 )
							{
								//pTileImg->PutSprT( CurrentDrawXPos, CurrentDrawYPos, PutSprParam1 + 1 );
								BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 1*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
								BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 1*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
							}
							else if ( CurrentDrawYPos >= YPos + Height - TileYSize )
							{
								//pTileImg->PutSprT( CurrentDrawXPos, CurrentDrawYPos, PutSprParam1 + 7 );
								BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 7*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
								BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 7*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
							}
						}
					}
				}
			}
			break;
		case SPR_PUTSPRALPHAT:
			{
				for ( CurrentDrawXPos = XPos; CurrentDrawXPos < XPos + Width; CurrentDrawXPos+=TileXSize )
				{
					for ( CurrentDrawYPos = YPos; CurrentDrawYPos < YPos + Height; CurrentDrawYPos+=TileYSize )
					{
						if ( CurrentDrawXPos + TileXSize > XPos + Width )
						{
							CurrentDrawXPos = XPos + Width - TileXSize;
						}

						if ( CurrentDrawYPos + TileYSize > YPos + Height )
						{
							CurrentDrawYPos = YPos + Height - TileYSize;
						}

						if ( CurrentDrawXPos > XPos && CurrentDrawYPos > YPos && 
							CurrentDrawXPos < XPos + Width - TileXSize && CurrentDrawYPos < YPos + Height - TileYSize )
						{
							//pTileImg->PutSprAlphaT( CurrentDrawXPos, CurrentDrawYPos, PutSprParam1 + 4, PutSprParam2 );
							BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 4*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
							BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 4*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
						}
						else
						{
							if ( CurrentDrawXPos < XPos + 1 )
							{
								if ( CurrentDrawYPos < YPos + 1 )
								{
									//pTileImg->PutSprAlphaT( CurrentDrawXPos, CurrentDrawYPos, PutSprParam1, PutSprParam2 );
									BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 0*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
									BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 0*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
								}
								else if ( CurrentDrawYPos >= YPos + Height - TileYSize )
								{
									//pTileImg->PutSprAlphaT( CurrentDrawXPos, CurrentDrawYPos, PutSprParam1 + 6, PutSprParam2 );
									BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 6*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
									BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 6*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
								}
								else
								{
									//pTileImg->PutSprAlphaT( CurrentDrawXPos, CurrentDrawYPos, PutSprParam1 + 3, PutSprParam2 );
									BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 3*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
									BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 3*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
								}
							}
							else if ( CurrentDrawXPos >= XPos + Width - TileXSize )
							{
								if ( CurrentDrawYPos < YPos + 1 )
								{
									//pTileImg->PutSprAlphaT( CurrentDrawXPos, CurrentDrawYPos, PutSprParam1 + 2, PutSprParam2 );
									BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 2*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
									BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 2*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
								}
								else if ( CurrentDrawYPos >= YPos + Height - TileYSize )
								{
									//pTileImg->PutSprAlphaT( CurrentDrawXPos, CurrentDrawYPos, PutSprParam1 + 8, PutSprParam2 );
									BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 8*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
									BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 8*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
								}
								else
								{
									//pTileImg->PutSprAlphaT( CurrentDrawXPos, CurrentDrawYPos, PutSprParam1 + 5, PutSprParam2 );
									BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 5*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
									BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 5*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
								}
							}
							else if ( CurrentDrawYPos < YPos + 1 )
							{
								//pTileImg->PutSprAlphaT( CurrentDrawXPos, CurrentDrawYPos, PutSprParam1 + 1, PutSprParam2 );
								BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 1*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
								BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 1*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
							}
							else if ( CurrentDrawYPos >= YPos + Height - TileYSize )
							{
								//pTileImg->PutSprAlphaT( CurrentDrawXPos, CurrentDrawYPos, PutSprParam1 + 7, PutSprParam2 );
								BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 7*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
								BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 7*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
							}
						}
					}
				}
			}
			break;
		default:
			return false;
		}
	}
	else if ( TileImgNum == 1 )		// Ÿ�� 1���� �̷���� �̹��� ( ���� ���� �ɰ� ���⿡, if �� �������� ���� )
	{
		// �Ʒ� ��º� �ϳ��� ��밡��������, ���� ���� ������ �ȿ��� switch �� for �� ������ ���� �� ���ٴ�,
		// �Ʒ��� ���� �ѹ��� ���� �ϴ� ������ ���� ����� ���ؼ� �ڵ带 �÷���.
		switch( PutSprOption )
		{
		case SPR_PUTSPRT:
			{
				for ( CurrentDrawXPos = XPos; CurrentDrawXPos < XPos + Width; CurrentDrawXPos+=TileXSize )
				{
					for ( CurrentDrawYPos = YPos; CurrentDrawYPos < YPos + Height; CurrentDrawYPos+=TileYSize )
					{
						if ( CurrentDrawXPos + TileXSize > XPos + Width )
						{
							CurrentDrawXPos = XPos + Width - TileXSize;
						}

						if ( CurrentDrawYPos + TileYSize > YPos + Height )
						{
							CurrentDrawYPos = YPos + Height - TileYSize;
						}

						//pTileImg->PutSprT( CurrentDrawXPos, CurrentDrawYPos, PutSprParam1 );
						BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 0*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
						BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 0*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
					}
				}
			}
			break;
		case SPR_PUTSPRALPHAT:
			{
				for ( CurrentDrawXPos = XPos; CurrentDrawXPos < XPos + Width; CurrentDrawXPos+=TileXSize )
				{
					for ( CurrentDrawYPos = YPos; CurrentDrawYPos < YPos + Height; CurrentDrawYPos+=TileYSize )
					{
						if ( CurrentDrawXPos + TileXSize > XPos + Width )
						{
							CurrentDrawXPos = XPos + Width - TileXSize;
						}

						if ( CurrentDrawYPos + TileYSize > YPos + Height )
						{
							CurrentDrawYPos = YPos + Height - TileYSize;
						}

						//pTileImg->PutSprAlphaT( CurrentDrawXPos, CurrentDrawYPos, PutSprParam1, PutSprParam2 );
						BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 0*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
						BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 0*TileXSize, 0, CurrentDrawXPos, CurrentDrawYPos);
					}
				}
			}
			break;
		default:
			return false;
		}
	}
	else
	{
		return false;
	}

	return true;	//SI16 TileXSize = m_spr.clHeader.siXsize;
	//SI16 TileYSize = m_spr.clHeader.siYsize;

	//// Ÿ���� ������ ���� �� �ִ��� üũ ( �� ���ų�, �ʰ��� ������ �ȵ����� )
	//// �Ʒ� 3�� �ּ� ó���� ������, �Ʒ� �ڵ忡 �ش��ϴ� ��쿡�� 
	//// ����� ���� �ϰ�����, �� �κ��� �� ��� ��.
	///*
	//if ( ( Width % TileXSize ) != 0 || ( Height % TileYSize ) != 0 )
	//{
	//	return false;
	//}
	//*/

	//SI16 RowNum = Height / TileYSize;
	//SI16 ColumnNum = Width / TileXSize;

	//SI16 i = 0;
	//SI16 j = 0;

	//if(RowNum == 0 || ColumnNum == 0)
	//{
	//	BitBltDS( dest, GetBufferDC(MASK_BACKGROUND_NUM), Width, Height, SRCAND, 0*TileXSize, 0, XPos + 0 * TileXSize, YPos + 0 * TileYSize);
	//	BitBltDS( dest, GetBufferDC(REAL_BACKGROUND_NUM), Width, Height, SRCPAINT, 0*TileXSize, 0, XPos + 0 * TileXSize, YPos + 0 * TileYSize);
	//}

	//// Ÿ�� 3���� �̷���� �̹���
	//if ( TileImgNum == 3 )
	//{	
	//	if ( IsRowTile )
	//	{
	//		// �Ʒ� ��º� �ϳ��� ��밡��������, ���� ���� ������ �ȿ��� switch �� for �� ������ ���� �� ���ٴ�,
	//		// �Ʒ��� ���� �ѹ��� ���� �ϴ� ������ ���� ����� ���ؼ� �ڵ带 �÷���.
	//		switch( PutSprOption )
	//		{
	//		case SPR_PUTSPRT:
	//			{
	//				for ( i = 0; i < RowNum; ++i )
	//				{
	//					for ( j = 0; j < ColumnNum; ++j )
	//					{
	//						if ( j < 1 )
	//						{
	//							//pTileImg->PutSprT( XPos + j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 0 );
	//							BitBltDS( dest, GetBufferDC(MASK_BACKGROUND_NUM), TileXSize, TileYSize, SRCAND, 0*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							BitBltDS( dest, GetBufferDC(REAL_BACKGROUND_NUM), TileXSize, TileYSize, SRCPAINT, 0*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//						}
	//						else if ( j >= ColumnNum - 1 )
	//						{
	//							//pTileImg->PutSprT( XPos + j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 2 );
	//							BitBltDS( dest, GetBufferDC(MASK_BACKGROUND_NUM), TileXSize, TileYSize, SRCAND, 2*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							BitBltDS( dest, GetBufferDC(REAL_BACKGROUND_NUM), TileXSize, TileYSize, SRCPAINT, 2*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//						}
	//						else
	//						{
	//							//pTileImg->PutSprT( XPos + j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 1 );
	//							BitBltDS( dest, GetBufferDC(MASK_BACKGROUND_NUM), TileXSize, TileYSize, SRCAND, 1*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							BitBltDS( dest, GetBufferDC(REAL_BACKGROUND_NUM), TileXSize, TileYSize, SRCPAINT, 1*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//						}
	//					}
	//				}
	//			}
	//			break;
	//		case SPR_PUTSPRALPHAT:
	//			{
	//				for ( i = 0; i < RowNum; ++i )
	//				{
	//					for ( j = 0; j < ColumnNum; ++j )
	//					{
	//						//if ( j < 1 )
	//						//{
	//						//	pTileImg->PutSprAlphaT( XPos + j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 0, PutSprParam2 );

	//						//}
	//						//else if ( j >= ColumnNum - 1 )
	//						//{
	//						//	pTileImg->PutSprAlphaT( XPos + j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 2, PutSprParam2 );
	//						//}
	//						//else
	//						//{
	//						//	pTileImg->PutSprAlphaT( XPos + j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 1, PutSprParam2 );
	//						//}
	//						if ( j < 1 )
	//						{
	//							//pTileImg->PutSprT( XPos + j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 0 );
	//							BitBltDS( dest, GetBufferDC(MASK_BACKGROUND_NUM), TileXSize, TileYSize, SRCAND, 0*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							BitBltDS( dest, GetBufferDC(REAL_BACKGROUND_NUM), TileXSize, TileYSize, SRCPAINT, 0*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//						}
	//						else if ( j >= ColumnNum - 1 )
	//						{
	//							//pTileImg->PutSprT( XPos + j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 2 );
	//							BitBltDS( dest, GetBufferDC(MASK_BACKGROUND_NUM), TileXSize, TileYSize, SRCAND, 2*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							BitBltDS( dest, GetBufferDC(REAL_BACKGROUND_NUM), TileXSize, TileYSize, SRCPAINT, 2*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//						}
	//						else
	//						{
	//							//pTileImg->PutSprT( XPos + j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 1 );
	//							BitBltDS( dest, GetBufferDC(MASK_BACKGROUND_NUM), TileXSize, TileYSize, SRCAND, 1*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							BitBltDS( dest, GetBufferDC(REAL_BACKGROUND_NUM), TileXSize, TileYSize, SRCPAINT, 1*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//						}
	//					}
	//				}
	//			}
	//			break;
	//		default:
	//			return false;
	//		}
	//	}
	//	else
	//	{
	//		// �Ʒ� ��º� �ϳ��� ��밡��������, ���� ���� ������ �ȿ��� switch �� for �� ������ ���� �� ���ٴ�,
	//		// �Ʒ��� ���� �ѹ��� ���� �ϴ� ������ ���� ����� ���ؼ� �ڵ带 �÷���.
	//		switch( PutSprOption )
	//		{
	//		case SPR_PUTSPRT:
	//			{
	//				for ( i = 0; i < RowNum; ++i )
	//				{
	//					for ( j = 0; j < ColumnNum; ++j )
	//					{
	//						if ( i < 1 )
	//						{
	//							//pTileImg->PutSprT( XPos + j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 0 );
	//							BitBltDS( dest, GetBufferDC(MASK_BACKGROUND_NUM), TileXSize, TileYSize, SRCAND, 0*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							BitBltDS( dest, GetBufferDC(REAL_BACKGROUND_NUM), TileXSize, TileYSize, SRCPAINT, 0*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//						}
	//						else if ( i >= RowNum - 1 )
	//						{
	//							//pTileImg->PutSprT( XPos + j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 2 );
	//							BitBltDS( dest, GetBufferDC(MASK_BACKGROUND_NUM), TileXSize, TileYSize, SRCAND, 2*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							BitBltDS( dest, GetBufferDC(REAL_BACKGROUND_NUM), TileXSize, TileYSize, SRCPAINT, 2*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//						}
	//						else
	//						{
	//							//pTileImg->PutSprT( XPos + j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 1 );
	//							BitBltDS( dest, GetBufferDC(MASK_BACKGROUND_NUM), TileXSize, TileYSize, SRCAND, 1*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							BitBltDS( dest, GetBufferDC(REAL_BACKGROUND_NUM), TileXSize, TileYSize, SRCPAINT, 1*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//						}
	//					}
	//				}
	//			}
	//			break;
	//		case SPR_PUTSPRALPHAT:
	//			{
	//				for ( i = 0; i < RowNum; ++i )
	//				{
	//					for ( j = 0; j < ColumnNum; ++j )
	//					{
	//						//if ( i < 1 )
	//						//{
	//						//	pTileImg->PutSprAlphaT( XPos + j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 0, PutSprParam2 );
	//						//}
	//						//else if ( i >= RowNum - 1 )
	//						//{
	//						//	pTileImg->PutSprAlphaT( XPos + j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 2, PutSprParam2 );
	//						//}
	//						//else
	//						//{
	//						//	pTileImg->PutSprAlphaT( XPos + j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 1, PutSprParam2 );
	//						//}
	//						if ( i < 1 )
	//						{
	//							//pTileImg->PutSprT( XPos + j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 0 );
	//							BitBltDS( dest, GetBufferDC(MASK_BACKGROUND_NUM), TileXSize, TileYSize, SRCAND, 0*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							BitBltDS( dest, GetBufferDC(REAL_BACKGROUND_NUM), TileXSize, TileYSize, SRCPAINT, 0*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//						}
	//						else if ( i >= RowNum - 1 )
	//						{
	//							//pTileImg->PutSprT( XPos + j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 2 );
	//							BitBltDS( dest, GetBufferDC(MASK_BACKGROUND_NUM), TileXSize, TileYSize, SRCAND, 2*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							BitBltDS( dest, GetBufferDC(REAL_BACKGROUND_NUM), TileXSize, TileYSize, SRCPAINT, 2*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//						}
	//						else
	//						{
	//							//pTileImg->PutSprT( XPos + j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 1 );
	//							BitBltDS( dest, GetBufferDC(MASK_BACKGROUND_NUM), TileXSize, TileYSize, SRCAND, 1*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							BitBltDS( dest, GetBufferDC(REAL_BACKGROUND_NUM), TileXSize, TileYSize, SRCPAINT, 1*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//						}
	//					}
	//				}
	//			}
	//			break;
	//		default:
	//			return false;
	//		}
	//	}
	//}
	//else if ( TileImgNum == 9 )		// Ÿ�� 9���� �̷���� �̹���
	//{
	//	// �Ʒ� ��º� �ϳ��� ��밡��������, ���� ���� ������ �ȿ��� switch �� for �� ������ ���� �� ���ٴ�,
	//	// �Ʒ��� ���� �ѹ��� ���� �ϴ� ������ ���� ����� ���ؼ� �ڵ带 �÷���.
	//	switch( PutSprOption )
	//	{
	//	case SPR_PUTSPRT:
	//		{
	//			for ( i = 0; i < RowNum; ++i )
	//			{
	//				for ( j = 0; j < ColumnNum; ++j )
	//				{
	//					// �ܰ��� �ƴ� ���� ����
	//					if ( i > 0 && j > 0 && i < RowNum - 1 && j < ColumnNum - 1 )
	//					{
	//						//pTileImg->PutSprT( XPos + j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 4 );
	//						BitBltDS( dest, GetBufferDC(MASK_BACKGROUND_NUM), TileXSize, TileYSize, SRCAND, 4*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//						BitBltDS( dest, GetBufferDC(REAL_BACKGROUND_NUM), TileXSize, TileYSize, SRCPAINT, 4*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);

	//					}
	//					// �ܰ� ����
	//					else
	//					{
	//						if ( i < 1 )
	//						{
	//							if ( j < 1 )
	//							{
	//								//pTileImg->PutSprT( XPos + j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 0 );
	//								BitBltDS( dest, GetBufferDC(MASK_BACKGROUND_NUM), TileXSize, TileYSize, SRCAND,  0*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//								BitBltDS( dest, GetBufferDC(REAL_BACKGROUND_NUM), TileXSize, TileYSize, SRCPAINT, 0*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							}
	//							else if ( j >= ColumnNum - 1 )
	//							{
	//								//pTileImg->PutSprT( XPos +j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 2 );
	//								BitBltDS( dest, GetBufferDC(MASK_BACKGROUND_NUM), TileXSize, TileYSize, SRCAND, 2*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//								BitBltDS( dest, GetBufferDC(REAL_BACKGROUND_NUM), TileXSize, TileYSize, SRCPAINT, 2*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							}
	//							else
	//							{
	//								//pTileImg->PutSprT( XPos +j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 1 );
	//								BitBltDS( dest, GetBufferDC(MASK_BACKGROUND_NUM), TileXSize, TileYSize, SRCAND, 1*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//								BitBltDS( dest, GetBufferDC(REAL_BACKGROUND_NUM), TileXSize, TileYSize, SRCPAINT, 1*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							}
	//						}
	//						else if ( i >= RowNum - 1 )
	//						{
	//							if ( j < 1 )
	//							{
	//								//pTileImg->PutSprT( XPos +j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 6 );
	//								BitBltDS( dest, GetBufferDC(MASK_BACKGROUND_NUM), TileXSize, TileYSize, SRCAND, 6*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//								BitBltDS( dest, GetBufferDC(REAL_BACKGROUND_NUM), TileXSize, TileYSize, SRCPAINT, 6*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							}
	//							else if ( j >= ColumnNum - 1 )
	//							{
	//								//pTileImg->PutSprT( XPos +j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 8 );
	//								BitBltDS( dest, GetBufferDC(MASK_BACKGROUND_NUM), TileXSize, TileYSize, SRCAND, 8*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//								BitBltDS( dest, GetBufferDC(REAL_BACKGROUND_NUM), TileXSize, TileYSize, SRCPAINT, 8*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							}
	//							else
	//							{
	//								//pTileImg->PutSprT( XPos +j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 7 );
	//								BitBltDS( dest, GetBufferDC(MASK_BACKGROUND_NUM), TileXSize, TileYSize, SRCAND, 7*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//								BitBltDS( dest, GetBufferDC(REAL_BACKGROUND_NUM), TileXSize, TileYSize, SRCPAINT, 7*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							}
	//						}
	//						else if ( j < 1 )
	//						{
	//							//pTileImg->PutSprT( XPos +j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 3 );
	//							BitBltDS( dest, GetBufferDC(MASK_BACKGROUND_NUM), TileXSize, TileYSize, SRCAND, 3*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							BitBltDS( dest, GetBufferDC(REAL_BACKGROUND_NUM), TileXSize, TileYSize, SRCPAINT, 3*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//						}
	//						else if ( j >= ColumnNum - 1 )
	//						{
	//							//pTileImg->PutSprT( XPos +j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 5 );
	//							BitBltDS( dest, GetBufferDC(MASK_BACKGROUND_NUM), TileXSize, TileYSize, SRCAND, 5*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							BitBltDS( dest, GetBufferDC(REAL_BACKGROUND_NUM), TileXSize, TileYSize, SRCPAINT, 5*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//						}
	//					}
	//				}
	//			}
	//		}
	//		break;
	//	case SPR_PUTSPRALPHAT:
	//		{
	//			for ( i = 0; i < RowNum; ++i )
	//			{
	//				for ( j = 0; j < ColumnNum; ++j )
	//				{
	//					// �ܰ��� �ƴ� ���� ����
	//					if ( i > 0 && j > 0 && i < RowNum - 1 && j < ColumnNum - 1 )
	//					{
	//						//pTileImg->PutSprAlphaT( XPos +j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 4, PutSprParam2 );
	//						BitBltDS( dest, GetBufferDC(MASK_BACKGROUND_NUM), TileXSize, TileYSize, SRCAND, 4*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//						BitBltDS( dest, GetBufferDC(REAL_BACKGROUND_NUM), TileXSize, TileYSize, SRCPAINT, 4*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);

	//					}
	//					// �ܰ� ����
	//					else
	//					{
	//						if ( i < 1 )
	//						{
	//							if ( j < 1 )
	//							{
	//								//pTileImg->PutSprAlphaT( XPos +j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 0, PutSprParam2 );
	//								BitBltDS( dest, GetBufferDC(MASK_BACKGROUND_NUM), TileXSize, TileYSize, SRCAND, 0*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//								BitBltDS( dest, GetBufferDC(REAL_BACKGROUND_NUM), TileXSize, TileYSize, SRCPAINT, 0*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);

	//							}
	//							else if ( j >= ColumnNum - 1 )
	//							{
	//								//pTileImg->PutSprAlphaT( XPos +j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 2, PutSprParam2 );
	//								BitBltDS( dest, GetBufferDC(MASK_BACKGROUND_NUM), TileXSize, TileYSize, SRCAND, 2*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//								BitBltDS( dest, GetBufferDC(REAL_BACKGROUND_NUM), TileXSize, TileYSize, SRCPAINT, 2*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							}
	//							else
	//							{
	//								//pTileImg->PutSprAlphaT( XPos + j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 1, PutSprParam2 );
	//								BitBltDS( dest, GetBufferDC(MASK_BACKGROUND_NUM), TileXSize, TileYSize, SRCAND, 1*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//								BitBltDS( dest, GetBufferDC(REAL_BACKGROUND_NUM), TileXSize, TileYSize, SRCPAINT, 1*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							}
	//						}
	//						else if ( i >= RowNum - 1 )
	//						{
	//							if ( j < 1 )
	//							{
	//								//pTileImg->PutSprAlphaT( XPos + j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 6, PutSprParam2 );
	//								BitBltDS( dest, GetBufferDC(MASK_BACKGROUND_NUM), TileXSize, TileYSize, SRCAND, 6*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//								BitBltDS( dest, GetBufferDC(REAL_BACKGROUND_NUM), TileXSize, TileYSize, SRCPAINT, 6*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							}
	//							else if ( j >= ColumnNum - 1 )
	//							{
	//								//pTileImg->PutSprAlphaT( XPos + j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 8, PutSprParam2 );
	//								BitBltDS( dest, GetBufferDC(MASK_BACKGROUND_NUM), TileXSize, TileYSize, SRCAND, 8*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//								BitBltDS( dest, GetBufferDC(REAL_BACKGROUND_NUM), TileXSize, TileYSize, SRCPAINT, 8*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							}
	//							else
	//							{
	//								//pTileImg->PutSprAlphaT( XPos + j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 7, PutSprParam2 );
	//								BitBltDS( dest, GetBufferDC(MASK_BACKGROUND_NUM), TileXSize, TileYSize, SRCAND, 7*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//								BitBltDS( dest, GetBufferDC(REAL_BACKGROUND_NUM), TileXSize, TileYSize, SRCPAINT, 7*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							}
	//						}
	//						else if ( j < 1 )
	//						{
	//							//pTileImg->PutSprAlphaT( XPos + j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 3, PutSprParam2 );
	//							BitBltDS( dest, GetBufferDC(MASK_BACKGROUND_NUM), TileXSize, TileYSize, SRCAND, 3*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							BitBltDS( dest, GetBufferDC(REAL_BACKGROUND_NUM), TileXSize, TileYSize, SRCPAINT, 3*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//						}
	//						else if ( j >= ColumnNum - 1 )
	//						{
	//							//pTileImg->PutSprAlphaT( XPos + j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 5, PutSprParam2 );
	//							BitBltDS( dest, GetBufferDC(MASK_BACKGROUND_NUM), TileXSize, TileYSize, SRCAND, 5*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							BitBltDS( dest, GetBufferDC(REAL_BACKGROUND_NUM), TileXSize, TileYSize, SRCPAINT, 5*TileXSize,0,  XPos + j * TileXSize, YPos + i * TileYSize);
	//						}
	//					}
	//				}
	//			}
	//		}
	//		break;
	//	default:
	//		return false;
	//	}
	//}
	//else if ( TileImgNum == 1 )		// Ÿ�� 1���� �̷���� �̹��� ( ���� ���� �ɰ� ���⿡, if �� �������� ���� )
	//{
	//	// �Ʒ� ��º� �ϳ��� ��밡��������, ���� ���� ������ �ȿ��� switch �� for �� ������ ���� �� ���ٴ�,
	//	// �Ʒ��� ���� �ѹ��� ���� �ϴ� ������ ���� ����� ���ؼ� �ڵ带 �÷���.
	//	switch( PutSprOption )
	//	{
	//	case SPR_PUTSPRT:
	//		{
	//			for ( i = 0; i < RowNum; ++i )
	//			{
	//				for ( j = 0; j < ColumnNum; ++j )
	//				{
	//					//pTileImg->PutSprT( XPos + j * TileXSize, YPos + i * TileYSize, PutSprParam1 );
	//					BitBltDS( dest, GetBufferDC(MASK_BACKGROUND_NUM), TileXSize, TileYSize, SRCAND, 0*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//					BitBltDS( dest, GetBufferDC(REAL_BACKGROUND_NUM), TileXSize, TileYSize, SRCPAINT, 0*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//				}
	//			}
	//		}
	//		break;
	//	case SPR_PUTSPRALPHAT:
	//		{
	//			for ( i = 0; i < RowNum; ++i )
	//			{
	//				for ( j = 0; j < ColumnNum; ++j )
	//				{
	//					//pTileImg->PutSprAlphaT( XPos + j * TileXSize, YPos + i * TileYSize, PutSprParam1, PutSprParam2 );
	//					BitBltDS( dest, GetBufferDC(MASK_BACKGROUND_NUM), TileXSize, TileYSize, SRCAND, 0*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//					BitBltDS( dest, GetBufferDC(REAL_BACKGROUND_NUM), TileXSize, TileYSize, SRCPAINT, 0*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//				}
	//			}
	//		}
	//		break;
	//	default:
	//		return false;
	//	}
	//}
	//else
	//{
	//	return false;
	//}

	//return true;
}


// FilefullPath�� �м��Ͽ� CFileNameTok Ŭ���� Ÿ�� ��������� ������
bool CDiagramPropertyDlg::ParsingFileFullPath(CString fullPath)
{
	//�ʱ�ȭ ��
	m_fileNameInfo.Initialize();
	// fullPath ���� �м�
    m_fileNameInfo.InitFullPath((char*)(LPCTSTR)fullPath);

	if(m_fileNameInfo.m_szFileName[0] == NULL)
		return FALSE;
	else
		return TRUE;
}

// TILEIMAGENUM_CHAR_LENGTH �ڸ� �� ��ŭ Ÿ�� �̹��� ������ ����
CString	CDiagramPropertyDlg::GetTileImageNum()
{
	if(m_fileNameInfo.m_szFileName[0] != NULL)
	{
		CString tmpStr = m_fileNameInfo.m_szFileName;

		tmpStr = tmpStr.Right(TILEINFO_COUNT_OF_FILENAME);

		return tmpStr.Mid(TILEIMAGENUM_START_POS, TILEIMAGENUM_CHAR_LENGTH);
	}
	else
		return STR_EMPTY;
}

// TILEMODE_CHAR_LENGTH ���� ��ŭ Ÿ���̹��� ��带 ����
CString	CDiagramPropertyDlg::GetTileMode()
{
	if(m_fileNameInfo.m_szFileName[0] != NULL)
	{
		CString tmpStr = m_fileNameInfo.m_szFileName;

		tmpStr = tmpStr.Right(TILEINFO_COUNT_OF_FILENAME);

		return tmpStr.Mid(TILEMODE_POS, TILEMODE_CHAR_LENGTH);
	}
	else
		return STR_EMPTY;
}

// ��Ʈ ��Ÿ�� ���� ��ȭ ���ڸ� ����
void CDiagramPropertyDlg::ShowFontDialog()
{
	CFontDialog dlg(&m_logFont);

	if(dlg.DoModal() == IDOK)
	{
        dlg.GetCurrentFont(&m_logFont);
		m_fontName = dlg.GetFaceName();
		m_fontColor = dlg.GetColor();
		m_fontSize = dlg.GetSize()/10;
	}
}

CString CDiagramPropertyDlg::GetFontName()
{
	if(m_fontName.Trim() == STR_EMPTY)
	{
		strcpy(m_logFont.lfFaceName, _T(DEFAULT_FONT_STYLE));
		m_fontName = m_logFont.lfFaceName;
	}

    return m_fontName;
}

int CDiagramPropertyDlg::GetFontSize()
{
	if(m_fontSize < 0)
	{
		m_logFont.lfHeight = DEFAULT_FONT_SIZE;//(DEFAULT_FONT_SIZE*100)/75;
		m_fontSize = m_logFont.lfHeight;
	}

    return m_fontSize;
}

int CDiagramPropertyDlg::GetFontColor()
{
	if(m_fontColor < 0)
	{
		m_fontColor = DEFAULT_FONT_COLOR;
	}

    return m_fontColor;
}
BOOL CDiagramPropertyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	// �۲� �ʱ�ȭ
	m_logFont.lfHeight = -MulDiv(DEFAULT_FONT_SIZE, GetDC()->GetDeviceCaps(LOGPIXELSY), 72);//(DEFAULT_FONT_SIZE*100)/75;/**10*/;	// �۲� ���� 10��� ����
	m_logFont.lfWidth = 0;		// �۲� ����
	m_logFont.lfEscapement = 0;	// ����
	m_logFont.lfOrientation = 0;	// ȸ�� ����
	m_logFont.lfWeight = FW_NORMAL;	// ����
	m_logFont.lfItalic = FALSE;		// �����
	m_logFont.lfUnderline = FALSE;	// ����
	m_logFont.lfStrikeOut = FALSE;	// ��Ҽ�
	m_logFont.lfCharSet = DEFAULT_CHARSET; // ���ڼ�Ʈ
	m_logFont.lfOutPrecision = OUT_CHARACTER_PRECIS;	// �����Ȯ��
	m_logFont.lfClipPrecision = CLIP_CHARACTER_PRECIS;	// Ŭ���� ��Ȯ��
	m_logFont.lfQuality = DEFAULT_QUALITY;	// ����� ��
	m_logFont.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;	// �ڰ�
	
	strcpy(m_logFont.lfFaceName, _T(DEFAULT_FONT_STYLE));

	m_fontColor = DEFAULT_FONT_COLOR;

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CDiagramPropertyDlg::DrawMiniPicture(CDC* in_pDC, int in_TileCount  )
{
	if( in_pDC == NULL ) return;

	int iTmp = -1;
	int iTileNum = -1;

	iTmp = in_TileCount;

	switch( iTmp )
	{
	case VALID_TILEIMAGE_NUM0:
		{
			//iTileNum = VALID_TILEIMAGE_NUM0;
			iTileNum = 1;
		}
		break;
	case VALID_TILEIMAGE_NUM1:
		{
			iTileNum = VALID_TILEIMAGE_NUM1;
		}
		break;
	case VALID_TILEIMAGE_NUM3:
		{
			iTileNum = VALID_TILEIMAGE_NUM3;
		}
		break;
	case VALID_TILEIMAGE_NUM9:
		{
			iTileNum = VALID_TILEIMAGE_NUM9;
		}
		break;
	default:
		return;
	}

	if( GetEntity() != NULL && iTileNum != -1 )
		GetEntity()->DrawTileImg( in_pDC, SPR_PUTSPRT, 0, MINI_PICTURE_LEFT, MINI_PICTURE_TOP, MINI_PICTURE_WIDTH, MINI_PICTURE_HEIGHT, iTileNum, true);
}
void CDiagramPropertyDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.

	if ( bShow && g_bMagnetMode )
	{
		CRect rectParent, rectChile;

		GetParent()->GetWindowRect( rectParent );
		this->GetWindowRect( rectChile );

		rectChile.MoveToXY( rectParent.right, rectParent.top );
		this->MoveWindow( rectChile );
	}

}
