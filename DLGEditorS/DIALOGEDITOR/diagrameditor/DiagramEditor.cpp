#include "stdafx.h"
#include "DiagramEditor.h"
#include <math.h>

#include "../../SprFile/SprFile.h"
#include "../../MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "../../TextMgr/TextMgr.h"
#include "../../../NLib/NTextManager.h"

//cyj extern cltTextMgr g_pTextMgr;
extern NTextManager g_pTextManager;

extern CString g_StartPath;

#pragma warning( disable : 4706 )

/////////////////////////////////////////////////////////////////////////////
// CDiagramEditor construction/destruction/initialization

CDiagramEditor::CDiagramEditor()
/* ============================================================
	Function :		CDiagramEditor::CDiagramEditor
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			

   ============================================================*/
{
	/**
	leon add
	* DLGProperty에 DLGEditor 연결
	*/
	m_DLGPropertyDlg.SetDLGEditor(this);

	m_bkgndCol = ::GetSysColor( COLOR_WINDOW );
	m_nonClientBkgndCol = ::GetSysColor( COLOR_3DSHADOW );

	m_gridCol = RGB( 192, 192, 192 );
	m_grid = TRUE;
	m_gridStyle = PS_SOLID;

	m_gridSize = CSize( GRID_DEFAULT_WIDTH, GRID_DEFAULT_HEIGHT );

	m_snap = FALSE;
	m_bgResize = FALSE;
	m_bgResizeZone = 10;
	m_bgResizeSelected = FALSE;
	m_markerSize = CSize( 8, 8 );

	m_drawObj = NULL;
	m_objs = NULL;
	m_multiSelObj = NULL;
	m_internalData = NULL;

	m_restraint = RESTRAINT_NONE;

	// Editor Window에서 데이터 값 컨트롤함 => DialogSetting 다이얼로그에서 참조함
	m_leftMargin = MARGIN_DEFAULT_LEFT;
	m_topMargin = MARGIN_DEFAULT_TOP;
	m_rightMargin = MARGIN_DEFAULT_RIGHT;
	m_bottomMargin = MARGIN_DEFAULT_BOTTOM;
	m_margin = FALSE;
	m_marginColor = RGB( 128, 128, 255 );

	m_popupMenu = NULL;
	m_multiDraw = FALSE;

	m_zoomFactor = 0.01;
	m_zoomMax = 10.0;
	m_zoomMin = 0.0;

	m_panningTimer = 100;
	m_panning = FALSE;

	m_keyInterface = KEY_ALL;

	m_cursorNorth		= ::LoadCursor( NULL, IDC_SIZENS );
	m_cursorNorthEast	= ::LoadCursor( NULL, IDC_SIZENESW );
	m_cursorEast		= ::LoadCursor( NULL, IDC_SIZEWE );
	m_cursorSouthEast	= ::LoadCursor( NULL, IDC_SIZENWSE );
	m_cursorSouth		= ::LoadCursor( NULL, IDC_SIZENS );
	m_cursorSouthWest	= ::LoadCursor( NULL, IDC_SIZENESW );
	m_cursorWest		= ::LoadCursor( NULL, IDC_SIZEWE );
	m_cursorNorthWest	= ::LoadCursor( NULL, IDC_SIZENWSE );

	SetScrollWheelMode( WHEEL_SCROLL );
	
	// buffer DC 초기화
	for(int i=0; i<MAX_DLG_BUFFER_LENGTH; i++)
	{
		m_pbufferDC[i] = NULL;
		m_pmemBmp[i] = NULL;
		m_pOldBmp[i] = NULL;
	}

	m_pFrame = NULL;
	// 배경 이미지가 존재하는 디폴트 경로
	//m_defaultImagePath = GOONZU_DEFAULT_ROOT_PATH;
	//if(m_objs != NULL)
	//	m_objs->SetDefaultFilePath( GOONZU_DEFAULT_ROOT_PATH );

	//LoadSettings();

	// 배경 이미지 전체 경로인 m_OldBGFullPath는 초기화하지 않음
	// m_OldBGFullPath = "";
	Clear();

}

CDiagramEditor::~CDiagramEditor()
/* ============================================================
	Function :		CDiagramEditor::~CDiagramEditor
	Description :	Destructor
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			

   ============================================================*/
{

	SaveSettings();

	delete m_drawObj;
	delete m_internalData;
	delete m_popupMenu;

	/**
	leon add
	* buffer DC 제거
	* 메모리 bmp부터 제거 => 연결된 DC제거
	*/
	for(int i=0; i<MAX_DLG_BUFFER_LENGTH; i++)
	{
		if(m_pmemBmp[i])
		{
			//m_pmemBmp[i]->DeleteObject();
			delete m_pmemBmp[i];
		}

		if(m_pbufferDC[i])
		{
			//m_pbufferDC[i]->SelectObject(m_pOldBmp[i]);
			//m_pbufferDC[i]->DeleteDC();
			delete m_pbufferDC[i];
		}
	}

}

void CDiagramEditor::Clear()
/* ============================================================
	Function :		CDiagramEditor::Clear
	Description :	Clears internal run-time variables.
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Call to reset internal states.

   ============================================================*/
{

	// 배경 이미지 전체 경로인 m_OldBGFullPath는 초기화하지 않음

	// Clearing internal states and vars
	m_selectionRect.SetRectEmpty();
	m_interactMode = MODE_NONE;
	m_zoom = 1.0;
	m_bgResizeSelected = FALSE;
	m_deltaPoint = CSize( 0, 0 );
	m_multiSelObj = NULL;
	m_drawing = FALSE;

	SetPanning( FALSE );

	delete m_drawObj;
	m_drawObj = NULL;

	/**
	leon add
	* buffer DC 초기화
	*/
	//if(m_objs && m_objs->m_BGFullPath && m_objs->m_BGFullPath != m_OldBGFullPath)
	if( m_pbufferDC != NULL)
	{
		// buffer DC 초기화
		for(int i=0; i<MAX_DLG_BUFFER_LENGTH; i++)
		{
			if(m_pmemBmp[i])
			{
				delete m_pmemBmp[i];
				m_pmemBmp[i] = NULL;
			}

			if(m_pbufferDC[i])
			{
				delete m_pbufferDC[i];
				m_pbufferDC[i] = NULL;
			}

			m_pOldBmp[i] = NULL;
		}

		m_OldBGFullPath = "";

        //m_objs->Clear();
		m_DLGPropertyDlg.m_spr.ClearImageData();

	}

	// 배경 이미지 전체 경로인 m_OldBGFullPath는 초기화하지 않음
	// m_OldBGFullPath = "";

	if( m_hWnd )
	{

		SetupScrollbars();
		SetHScroll( 0 );
		SetVScroll( 0 );

		RedrawWindow();

	}

}

BOOL CDiagramEditor::Create( DWORD dwStyle, const RECT &rect, CWnd *pParentWnd, CDiagramEntityContainer* data )
/* ============================================================
	Function :		CDiagramEditor::Create
	Description :	Creates a "CDiagramEditor" window.
	Access :		Public

	Return :		BOOL							-	"TRUE" if success
	Parameters :	DWORD dwStyle					-	Window styles for 
														the editor
					const RECT &rect				-	Window rectangle
					CWnd *pParentWnd				-	Parent of the 
														editor
					CDiagramEntityContainer* data	-	Pointer to data. 
														Might be "NULL".
					
	Usage :			If data is "NULL", a "CDiagramEntityContainer" 
					will be created internally, and the instance 
					of the editor will be responsible for the 
					container deletion.

   ============================================================*/
{
	if( data == NULL )
	{
		m_internalData = new CDiagramEntityContainer;
		SetInternalDiagramEntityContainer( m_internalData );
	}
	else
		SetDiagramEntityContainer( data );

	// m_objs를 얻은 다음 로딩
	if(m_objs != NULL)
	{
		m_objs->SetDefaultFilePath( GOONZU_DEFAULT_ROOT_PATH );
		m_objs->SetDefaultTxtFilePath( GOONZU_DEFAULT_TEXTMGR_PATH );
	}

	LoadSettings();

	BOOL res = CWnd::Create( NULL, NULL, dwStyle, rect, pParentWnd, NULL );
	CSize virtualSize;
	if( GetVirtualSize().cx == 0 &&  GetVirtualSize().cy == 0 )
		virtualSize = CSize( rect.right - rect.left, rect.bottom - rect.top );
	else
		virtualSize = GetVirtualSize();

	SetInternalVirtualSize( virtualSize );

	/**
	leon add
	* 메모리DC 생성
	*/
	// 배경 이미지 전체 경로 및 파일 이름 저장
	//m_OldBGFullPath = m_objs->m_BGFullPath;
	m_OldBGFullPath = m_objs->m_DLG_Property[DLG_BG_IMAGE_FULLPATH];

	return res;

}

void CDiagramEditor::New()
/* ============================================================
	Function :		CDiagramEditor::New
	Description :	Clears the current 'page' and creates a 
					new one.
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Call to start a new drawing.

   ============================================================*/
{

	SetRedraw( FALSE );
	Clear();
	m_objs->Clear();
	SetRedraw( TRUE );
	RedrawWindow();

}

void CDiagramEditor::SetDiagramEntityContainer( CDiagramEntityContainer* objs )
/* ============================================================
	Function :		CDiagramEditor::SetDiagramEntityContainer
	Description :	Sets the data container for the editor.
	Access :		Public
					
	Return :		void
	Parameters :	CDiagramEntityContainer* objs	-	the data 
														container
					
	Usage :			If this function is used, the caller is 
					responsible for deleting the container. Can 
					be called before or after "Create".

   ============================================================*/
{

	if( m_internalData )
		delete m_internalData;

	m_internalData = NULL;

	SetInternalDiagramEntityContainer ( objs );

}

void CDiagramEditor::SetInternalDiagramEntityContainer( CDiagramEntityContainer* objs )
/* ============================================================
	Function :		CDiagramEditor::SetInternalDiagramEntityContainer
	Description :	Sets the internal data container pointer.
	Access :		Protected

	Return :		void
	Parameters :	CDiagramEntityContainer* objs	-	A pointer to the 
														container to set.
					
	Usage :			Internal function.

   ============================================================*/
{

	m_objs = objs;

}

CDiagramEntityContainer* CDiagramEditor::GetDiagramEntityContainer() const
/* ============================================================
	Function :		CDiagramEditor::GetDiagramEntityContainer
	Description :	Returns a pointer to the data container.
	Access :		Public

	Return :		CDiagramEntityContainer*	-	The current data 
													container (might 
													be "NULL").
	Parameters :	none

	Usage :			If modifications are made to the contents of 
					the container, "SetModified" must be called as 
					appropriate. If visual changes are expected, 
					"RedrawWindow" must be called for the editor.

   ============================================================*/
{

	return m_objs;

}

BEGIN_MESSAGE_MAP( CDiagramEditor, CWnd )
	//{{AFX_MSG_MAP( CDiagramEditor )
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_SETCURSOR()
	ON_WM_SIZE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_GETDLGCODE()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MBUTTONDOWN()
	//}}AFX_MSG_MAP

	ON_WM_KILLFOCUS()
	ON_WM_TIMER()
	ON_WM_MOUSEWHEEL()
	ON_COMMAND_RANGE( CMD_START, CMD_END, OnObjectCommand )

	ON_COMMAND( ID_EDIT_CUT, OnEditCut )
	ON_COMMAND( ID_EDIT_COPY, OnEditCopy )
	ON_COMMAND( ID_EDIT_PASTE, OnEditPaste )
	ON_COMMAND( ID_EDIT_GROUP, OnEditGroup )
	ON_COMMAND( ID_EDIT_UNGROUP, OnEditUngroup )
	/**
	leon add
	* DLG Properyt 추가
	*/
	ON_COMMAND( ID_DLG_PROPERTY, OnDLGProperty)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDiagramEditor painting

void CDiagramEditor::OnPaint() 
/* ============================================================
	Function :		CDiagramEditor::OnPaint
	Description :	Draws the screen. A memory "CDC" is created 
					and drawn to.
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC. Do not call from code.

   ============================================================*/
{

	CPaintDC outputdc( this );

	// Getting coordinate data
	CRect rect;
	GetClientRect( &rect );

	SCROLLINFO sih;
	sih.cbSize = sizeof( SCROLLINFO );
	sih.fMask = SIF_POS;
	SCROLLINFO siv;
	siv.cbSize = sizeof( SCROLLINFO );
	siv.fMask = SIF_POS;
	if( !GetScrollInfo( SB_HORZ, &sih ) )
		sih.nPos = 0;
	if( !GetScrollInfo( SB_VERT, &siv ) )
		siv.nPos = 0;

	CRect totalRect;
	int virtwidth = round( static_cast< double >( GetVirtualSize().cx ) * GetZoom() ) + 1;
	int virtheight = round( static_cast< double >( GetVirtualSize().cy ) * GetZoom() ) + 1;
	totalRect.SetRect( 0, 0, virtwidth, virtheight );

	// Creating memory CDC
	CDC dc;
	dc.CreateCompatibleDC( &outputdc );
	CBitmap bmp;
	bmp.CreateCompatibleBitmap( &outputdc, rect.right, rect.bottom );
	CBitmap* oldbmp = dc.SelectObject( &bmp );

	// Painting
	EraseBackground( &dc, rect );

	dc.SetWindowOrg( sih.nPos, siv.nPos );

	Draw( &dc, totalRect );
	
	// Blit the memory CDC to screen
	outputdc.BitBlt( 0, 0, rect.right, rect.bottom, &dc, sih.nPos, siv.nPos, SRCCOPY );
	dc.SelectObject( oldbmp );

}

void CDiagramEditor::Draw( CDC* dc, CRect rect ) //const
/* ============================================================
	Function :		CDiagramEditor::Draw
	Description :	Calls a series of (virtual) functions to 
					draw to "dc". "rect" is the total rectangle 
					to draw to.
	Access :		Public

	Return :		void
	Parameters :	CDC* dc		-	The "CDC" to draw to.
					CRect rect	-	The complete rectangle 
									(including non-visible areas)
					
	Usage :			Should not normally be called from user code. 
					Can be called to draw the complete window. 
					Can be overriden to change drawing order.

   ============================================================*/
{

	double zoom = GetZoom();
	
	// Dialog 윈도우의 BackGround 이미지 그림
	DrawBackground( dc, rect, zoom );

	if( m_grid )
		DrawGrid( dc, rect, zoom );

	if( m_margin )
		DrawMargins( dc, rect, zoom );

	DrawObjects( dc, zoom );

	if( m_bgResize && m_bgResizeSelected )
		DrawSelectionMarkers( dc );

	if( GetPanning() )
		DrawPanning( dc );

	if( m_objs != NULL )
	{
		if( m_objs->m_DLG_Property[ DLG_TITLE_VISIBLE ] == STR_ONE )
		{
			LOGFONT lf;
			CFont font;

			HFONT hfont = ( HFONT ) ::GetStockObject( DEFAULT_GUI_FONT );
			CFont* pfont = CFont::FromHandle( hfont );
			pfont->GetLogFont( &lf );
			lf.lfHeight = round( static_cast< double >( lf.lfHeight ) * m_zoom );
			//// MS Sans Serif will not scale below 8 pts.
			//if( GetZoom() < 1 )
			//	lstrcpy( lf.lfFaceName, _T( "Arial" ) );
			
			lstrcpy(lf.lfFaceName, m_objs->m_DLG_Property[DLG_TEXT_STYLE]);
			lf.lfHeight = atoi((LPCTSTR)m_objs->m_DLG_Property[DLG_TEXT_SIZE]);

			font.CreateFontIndirect( &lf );
			dc->SelectObject( &font );

			dc->SetBkMode( TRANSPARENT );
			dc->SetTextColor(RGB(255,255,255));///*atoi((LPCTSTR)m_objs->m_DLG_Property[DLG_TEXT_COLOR])*/

			int ret = atoi((char*)(LPCTSTR)m_objs->m_DLG_Property[DLG_TITLE_STR]);

			if( ret > 0 ) 
				dc->DrawText( GetTxtFromMgr( ret ), rect, DT_LEFT | DT_TOP | DT_SINGLELINE );
			else
				dc->DrawText( m_objs->m_DLG_Property[DLG_TITLE_STR], /*GetTitle()*/ rect, DT_LEFT | DT_TOP | DT_SINGLELINE );

			dc->SelectStockObject( ANSI_VAR_FONT );
		}
	}
}

void CDiagramEditor::Print( CDC* dc, CRect rect, double zoom ) 
/* ============================================================
	Function :		CDiagramEditor::Print
	Description :	Prints the editor to printer or print a 
					preview.
	Access :		Public

	Return :		void
	Parameters :	CDC* dc		-	Printer- or preview "CDC" to 
									draw to.
					CRect rect	-	Total rect of editor.
					double zoom	-	Desired zoom value.
					
	Usage :			The function should be called to print the 
					editor to a printer or print preview. This 
					is because the zoom will most likely be set 
					to something different from the editor itself. 
					A good zoom factor can be calculated from 
					the difference between the screen- and 
					printer resolution:

					"printerDC.GetDeviceCaps( LOGPIXELSX ) / screenDC.GetDeviceCaps( LOGPIXELSX )"

					The grid, margin and selection markers are 
					not printed.
					Can be overriden to change drawing order, or 
					add drawing of the grid etc.
   ============================================================*/
{

	UnselectAll();
	DrawBackground( dc, rect, zoom );
	DrawObjects( dc, zoom );

}

BOOL CDiagramEditor::OnEraseBkgnd( CDC* ) 
/* ============================================================
	Function :		CDiagramEditor::OnEraseBkgnd
	Description :	Handles the "WM_ERASEBKGND" message. Handled 
					to avoid flicker - the editor is completely 
					redrawn in "OnPaint".
	Access :		Protected

	Return :		BOOL	-	
	Parameters :	CDC*	-	
					
	Usage :			Called from MFC. Do not call from code.

   ============================================================*/
{

	return TRUE;

}

/////////////////////////////////////////////////////////////////////////////
// CDiagramEditor painting virtuals

void CDiagramEditor::EraseBackground( CDC* dc, CRect rect ) const
/* ============================================================
	Function :		CDiagramEditor::EraseBackground
	Description :	Draws the non-client background
	Access :		Protected

	Return :		void
	Parameters :	CDC* dc		-	"CDC" to draw to.
					CRect rect	-	Total rect to draw to.
					
	Usage :			Virtual. Can be overridden in a derived class 
					to erase the non-client area.

   ============================================================*/
{

	dc->FillSolidRect( rect, m_nonClientBkgndCol );

}

void CDiagramEditor::DrawBackground( CDC* dc, CRect rect, double /*zoom*/) //const
/* ============================================================
	Function :		CDiagramEditor::DrawBackground
	Description :	Draws the virtual background
	Access :		Protected

	Return :		void
	Parameters :	CDC* dc			-	"CDC" to draw to.
					CRect rect		-	Total rect to draw to.
					double (zoom)	-	Current zoom level. 
										Coordinates can be 
										multiplied with this 
										value to get scaled.
					
	Usage :			Virtual. Can be overridden in a derived 
					class to draw the virtual paper area.

   ============================================================*/
{

	//dc->FillSolidRect( &rect, m_bkgndCol );
	//if(m_objs->m_BGFullPath && m_objs->m_BGFullPath != m_OldBGFullPath)
	if(m_objs->m_DLG_Property[DLG_BG_IMAGE_FULLPATH].Trim() != STR_EMPTY && m_objs->m_DLG_Property[DLG_BG_IMAGE_FULLPATH] != m_OldBGFullPath)
	{
		if(m_objs->m_DLG_Property[DLG_BG_TILE] != STR_ZERO)
			MakeMemDC( dc, atoi(m_objs->m_DLG_Property[DLG_BG_START_FONT]), atoi(m_objs->m_DLG_Property[DLG_BG_TILE_IMAGE_NUM]));
		else
			MakeMemDC( dc, atoi(m_objs->m_DLG_Property[DLG_BG_START_FONT]), WHOLE_IMAGE_STYLE_FONTNUM);
		//m_OldBGFullPath = m_objs->m_BGFullPath;
		m_OldBGFullPath = m_objs->m_DLG_Property[DLG_BG_IMAGE_FULLPATH];
	}
	
	//if(m_objs->m_BGFullPath  != "")
	if(m_objs->m_DLG_Property[DLG_BG_IMAGE_FULLPATH] != STR_EMPTY)
	{
		//// mask bitmap AND 연산
		//BitBltDS( dc, m_pbufferDC[MASK_BACKGROUND_NUM], rect.Width(), rect.Height(), SRCAND, 0, 0, rect.left, rect.top);
		//// 배경 그림 OR 연산
		//BitBltDS( dc, m_pbufferDC[REAL_BACKGROUND_NUM], rect.Width(), rect.Height(), SRCPAINT, 0, 0, rect.left, rect.top);
		if(m_objs->m_DLG_Property[DLG_BG_TILE] != STR_ZERO)
		{
			DrawTileImg(dc, SPR_PUTSPRT, 0, rect.left, rect.top, rect.Width(), rect.Height(), atoi(m_objs->m_DLG_Property[DLG_BG_TILE_IMAGE_NUM]), true);
		}
		else
		{
			// mask bitmap AND 연산
			BitBltDS( dc, m_pbufferDC[MASK_BACKGROUND_NUM], rect.Width(), rect.Height(), SRCAND, 0, 0, rect.left, rect.top);
			// 배경 그림 OR 연산
			BitBltDS( dc, m_pbufferDC[REAL_BACKGROUND_NUM], rect.Width(), rect.Height(), SRCPAINT, 0, 0, rect.left, rect.top);
		}

	}
}

void CDiagramEditor::DrawGrid( CDC* dc, CRect rect, double zoom ) const
/* ============================================================
	Function :		CDiagramEditor::DrawGrid
	Description :	Draws the grid
	Access :		Protected

	Return :		void
	Parameters :	CDC* dc		-	"CDC" to draw to.
					CRect rect	-	Total rect to draw to.
					double zoom	-	Current zoom level. 
									Coordinates can be 
									multiplied with this value 
									to get scaled.
					
	Usage :			Virtual. Can be overridden in a derived 
					class to draw the grid. Will not be called 
					if the grid is not visible.

   ============================================================*/
{

	COLORREF gridcol = GetGridColor();
	int gridstyle = GetGridPenStyle();

	CPen pen;
	pen.CreatePen( gridstyle, 1, gridcol );

	dc->SelectObject( &pen );

	// To avoid accumulating rounding errors, we don't
	// precalculate the grid size for the given zoom...

	int width = rect.Width();
	int height = rect.Height();

	int stepx = GetVirtualSize().cx / GetGridSize().cx;
	int stepy = GetVirtualSize().cy / GetGridSize().cy;

	// ...instead we calculate the position of each line.
	for( int x = 0 ; x <= stepx ; x++ )
	{
		dc->MoveTo( round( static_cast< double >( GetGridSize().cx * x ) * zoom ), 0 );
		dc->LineTo( round( static_cast< double >( GetGridSize().cx * x ) * zoom ), height );
	}

	for( int y = 0; y <= stepy ; y++ )
	{
		dc->MoveTo( 0, round( static_cast< double >( GetGridSize().cy * y ) * zoom ) );
		dc->LineTo( width, round( static_cast< double >( GetGridSize().cy * y ) * zoom ) );
	}

	dc->SelectStockObject( BLACK_PEN );

}

void CDiagramEditor::DrawMargins( CDC* dc, CRect rect, double zoom ) const
/* ============================================================
	Function :		CDiagramEditor::DrawMargins
	Description :	Draws the margins.
	Access :		Protected

	Return :		void
	Parameters :	CDC* dc		-	"CDC" to draw to.
					CRect rect	-	Total rect to draw to.
					double zoom	-	Current zoom level. 
									Coordinates can be 
									multiplied with this value 
									to get scaled.
					
	Usage :			Virtual. Can be overridden in a derived 
					class to draw the margins. Will not be 
					called if margins are not visible.

   ============================================================*/
{

	CPen pen;
	pen.CreatePen( PS_SOLID, 0, m_marginColor );
	dc->SelectObject( &pen );

	CPoint leftTop( rect.left + round( static_cast< double >( m_leftMargin ) * zoom ), rect.top + round( static_cast< double >( m_topMargin ) * zoom ) );
	CPoint leftBottom( rect.left + round( static_cast< double >( m_leftMargin ) * zoom ), rect.bottom - round( static_cast< double >( m_bottomMargin ) * zoom ) - 1 );
	CPoint rightTop( rect.right - round( static_cast< double >( m_rightMargin ) * zoom ) - 1, rect.top + round( static_cast< double >( m_topMargin ) * zoom ) );
	CPoint rightBottom( rect.right - round( static_cast< double >( m_rightMargin ) * zoom ) - 1, rect.bottom - round( static_cast< double >( m_bottomMargin ) * zoom ) - 1 );

	if( m_leftMargin )
	{
		dc->MoveTo( leftTop );
		dc->LineTo( leftBottom );
	}

	if( m_rightMargin )
	{
		dc->MoveTo( rightTop );
		dc->LineTo( rightBottom );
	}
	if( m_topMargin )
	{
		dc->MoveTo( leftTop );
		dc->LineTo( rightTop );
	}
	if( m_bottomMargin )
	{
		dc->MoveTo( leftBottom );
		dc->LineTo( rightBottom );
	}

	dc->SelectStockObject( BLACK_PEN );


}

void CDiagramEditor::DrawObjects( CDC* dc, double zoom ) const
/* ============================================================
	Function :		CDiagramEditor::DrawObjects
	Description :	Draws the object.
	Access :		Protected

	Return :		void
	Parameters :	CDC* dc		-	"CDC" to draw to.
					double zoom	-	Current zoom level. 
									Coordinates can be 
									multiplied with this value 
									to get scaled.
					
	Usage :			Virtual. Can be overridden in a derived 
					class to draw the data objects.

   ============================================================*/
{

	if( m_objs )
	{
		int count = 0;
		CDiagramEntity* obj;
		while( ( obj = m_objs->GetAt( count++ ) ) )
		{
			obj->m_pFrame = m_pFrame;
			obj->DrawObject( dc, zoom );
		}
	}

}

void CDiagramEditor::DrawSelectionMarkers( CDC* dc ) const
/* ============================================================
	Function :		CDiagramEditor::DrawSelectionMarkers
	Description :	Draws the selection markers.
	Access :		Protected

	Return :		void
	Parameters :	CDC* dc	-	The "CDC" to draw to.
					
	Usage :			Virtual. Can be overridden in a derived 
					class to draw the selection markers in 
					another way than the default black 
					rectangles. The selection rects are 
					displayed if the editor has background 
					resizing enabled and the user clicks in 
					the resize area around the virtual page 
					border. Selection markers are displayed 
					to allow resizing of the virtual page 
					with the mouse. 

   ============================================================*/
{

	// Draw selection markers
	CRect rectSelect;

	dc->SelectStockObject( BLACK_BRUSH );
	rectSelect = GetSelectionMarkerRect( DEHT_TOPLEFT );
	dc->Rectangle( rectSelect );

	rectSelect = GetSelectionMarkerRect( DEHT_TOPMIDDLE );
	dc->Rectangle( rectSelect );

	rectSelect = GetSelectionMarkerRect( DEHT_TOPRIGHT );
	dc->Rectangle( rectSelect );

	rectSelect = GetSelectionMarkerRect( DEHT_BOTTOMLEFT );
	dc->Rectangle( rectSelect );

	rectSelect = GetSelectionMarkerRect( DEHT_BOTTOMMIDDLE );
	dc->Rectangle( rectSelect );

	rectSelect = GetSelectionMarkerRect( DEHT_BOTTOMRIGHT );
	dc->Rectangle( rectSelect );

	rectSelect = GetSelectionMarkerRect( DEHT_RIGHTMIDDLE );
	dc->Rectangle( rectSelect );

	rectSelect = GetSelectionMarkerRect( DEHT_LEFTMIDDLE );
	dc->Rectangle( rectSelect );

}

CRect CDiagramEditor::GetSelectionMarkerRect( UINT marker ) const
/* ============================================================
	Function :		CDiagramEditor::GetSelectionMarkerRect
	Description :	Returns the selection rect for marker
	Access :		Public

	Return :		CRect		-	The rect of the selection 
									marker.
	Parameters :	UINT marker	-	The marker to get the rect 
									for ("DEHT_"-constants 
									defined in DiagramEntity.h)
					
	Usage :			Virtual. Can be overridden in a derived 
					class to change the selection rects for 
					the virtual page. The selection rects are 
					displayed if the editor has background 
					resizing enabled and the user clicks in 
					the resize area around the virtual page 
					border. Selection markers are displayed 
					to allow resizing of the virtual page 
					with the mouse.
					"marker" can be one of the following:
						"DEHT_NONE" No hit-point
						"DEHT_BODY" Inside object body
						"DEHT_TOPLEFT" Top-left corner
						"DEHT_TOPMIDDLE" Middle top-side
						"DEHT_TOPRIGHT" Top-right corner
						"DEHT_BOTTOMLEFT" Bottom-left corner
						"DEHT_BOTTOMMIDDLE" Middle bottom-side
						"DEHT_BOTTOMRIGHT" Bottom-right corner
						"DEHT_LEFTMIDDLE" Middle left-side
						"DEHT_RIGHTMIDDLE" Middle right-side
   ============================================================*/
{

	CRect rect( 0, 0, round( static_cast< double >( GetVirtualSize().cx ) * GetZoom() ), 
						round( static_cast< double >( GetVirtualSize().cy ) * GetZoom() ) );

	CRect rectMarker;
	int horz = m_markerSize.cx / 2;
	int vert = m_markerSize.cy / 2;

	switch( marker )
	{
		case DEHT_TOPLEFT:
			rectMarker.SetRect( rect.left - horz, 
								rect.top - vert, 
								rect.left + horz, 
								rect.top + vert );
		break;

		case DEHT_TOPMIDDLE:
			rectMarker.SetRect( rect.left + ( rect.Width() / 2 ) - horz, 
								rect.top - vert, 
								rect.left + ( rect.Width() / 2 ) + horz, 
								rect.top + vert );
		break;

		case DEHT_TOPRIGHT:
			rectMarker.SetRect( rect.right - horz, 
								rect.top - vert, 
								rect.right + horz, 
								rect.top + vert );
		break;

		case DEHT_BOTTOMLEFT:
			rectMarker.SetRect( rect.left - horz, 
								rect.bottom - vert, 
								rect.left + horz, 
								rect.bottom + vert );
		break;

		case DEHT_BOTTOMMIDDLE:
			rectMarker.SetRect( rect.left + ( rect.Width() / 2 ) - horz, 
								rect.bottom - vert, 
								rect.left + ( rect.Width() / 2 ) + horz, 
								rect.bottom + vert );
		break;

		case DEHT_BOTTOMRIGHT:
			rectMarker.SetRect( rect.right - horz, 
								rect.bottom - vert, 
								rect.right + horz, 
								rect.bottom + vert );
		break;

		case DEHT_LEFTMIDDLE:
			rectMarker.SetRect( rect.left - horz, 
								rect.top + ( rect.Height() / 2 ) - vert, 
								rect.left + horz, 
								rect.top + ( rect.Height() / 2 ) + vert );
		break;

		case DEHT_RIGHTMIDDLE:
			rectMarker.SetRect( rect.right - horz, 
								rect.top + ( rect.Height() / 2 ) - vert, 
								rect.right + horz, 
								rect.top + ( rect.Height() / 2 ) + vert );
		break;
	}

	return rectMarker;

}

/////////////////////////////////////////////////////////////////////////////
// CDiagramEditor property accessors

void CDiagramEditor::SetVirtualSize( const CSize& size, int nModeDetail )
/* ============================================================
	Function :		CDiagramEditor::SetVirtualSize
	Description :	Sets the size of the virtual paper.
	Access :		Public

	Return :		void
	Parameters :	const CSize& size	-	New virtual size.
					
	Usage :			The virtual page of the editor is the 
					'paper' where the user can draw. This 
					function marks the data as changed.

   ============================================================*/
{

	ASSERT( m_objs );
	SetInternalVirtualSize( size, nModeDetail );
	m_objs->SetModified( TRUE );

}

void CDiagramEditor::SetInternalVirtualSize( const CSize& size, int nModeDetail )
/* ============================================================
	Function :		CDiagramEditor::SetInternalVirtualSize
	Description :	Changes the virtual page size without 
					setting the data as modified.
	Access :		Private

	Return :		void
	Parameters :	const CSize& size	-	New virtual size.
					
	Usage :			Internal function. 

   ============================================================*/
{
	if( m_objs && size != GetVirtualSize() )
	{

		m_objs->SetVirtualSize( size, false, nModeDetail );
		
		/**
		leon add
		* Dialog 크기 실시간 변경
		*/
		m_DLGPropertyDlg.SetValues();

		SetupScrollbars();
		if( m_hWnd )
			RedrawWindow();

	}

}

CSize CDiagramEditor::GetVirtualSize() const
/* ============================================================
	Function :		CDiagramEditor::GetVirtualSize
	Description :	Returns the virtual size of the editor.
	Access :		Public

	Return :		CSize	-	The current virtual size.
	Parameters :	none

	Usage :			The virtual page of the editor is the 
					'paper' where the user can draw. 

   ============================================================*/
{

	CRect rect( 0, 0, 0, 0 );
	if( m_hWnd )
		GetClientRect( &rect );
	CSize size( CSize( 0, 0 ) );

	if( m_objs )
		size = m_objs->GetVirtualSize();

	if( size.cx == 0 )
		size.cx = rect.right;
	if( size.cy == 0 )
		size.cy = rect.bottom;

	return size;

}

void CDiagramEditor::SetBackgroundColor( COLORREF col )
/* ============================================================
	Function :		CDiagramEditor::SetBackgroundColor
	Description :	Sets the background color.
	Access :		Public

	Return :		void
	Parameters :	COLORREF col	-	New background color 
										to set.
					
	Usage :			The background is the virtual area of the 
					editor (might both be smaller or bigger 
					than the client rect).

   ============================================================*/
{

	m_bkgndCol = col;
	if( m_hWnd )
		RedrawWindow();

}

void CDiagramEditor::SetNonClientColor( COLORREF col )
/* ============================================================
	Function :		CDiagramEditor::SetNonClientColor
	Description :	Sets the non-client area color.
	Access :		Public

	Return :		void
	Parameters :	COLORREF col	-	New non-client area 
										color.
					
	Usage :			The non-client color is the color of the 
					area outside the virtual page.

   ============================================================*/
{

	m_nonClientBkgndCol = col;
	if( m_hWnd )
		RedrawWindow();

}

void CDiagramEditor::ShowGrid( BOOL grid )
/* ============================================================
	Function :		CDiagramEditor::ShowGrid
	Description :	Sets grid visibility.
	Access :		Public

	Return :		void
	Parameters :	BOOL grid	-	"TRUE" to show the grid, "FALSE" 
									to hide.
					
	Usage :			If the grid is visible, it will be drawn 
					using the grid pen style and color. The 
					grid lines will not be scaled with the 
					zoom (the space between them will of 
					course be, however)

   ============================================================*/
{

	m_grid = grid;
	if( m_hWnd )
		RedrawWindow();

}

BOOL CDiagramEditor::IsGridVisible() const
/* ============================================================
	Function :		CDiagramEditor::IsGridVisible
	Description :	Returns the visibility state of the grid.
	Access :		Public

	Return :		BOOL	-	"TRUE" if grid is visible.
	Parameters :	none

	Usage :			If the grid is visible, it will be drawn 
					using the grid pen style and color. The 
					grid lines will not be scaled with the 
					zoom (the space between them will of 
					course be, however)

   ============================================================*/
{

	return m_grid;

}

void CDiagramEditor::SetGridColor( COLORREF col )
/* ============================================================
	Function :		CDiagramEditor::SetGridColor
	Description :	Sets a new grid pen color.
	Access :		Public

	Return :		void
	Parameters :	COLORREF col	-	New grid pen color.
					
	Usage :			If the grid is visible, it will be drawn 
					using the grid pen style and color. The 
					grid lines will not be scaled with the 
					zoom (the space between them will of 
					course be, however)

   ============================================================*/
{

	m_gridCol = col;
	if( m_hWnd )
		RedrawWindow();

}

COLORREF CDiagramEditor::GetGridColor() const
/* ============================================================
	Function :		CDiagramEditor::GetGridColor
	Description :	Returns the current grid pen color.
	Access :		Public

	Return :		COLORREF	-	The current grid color.
	Parameters :	none

	Usage :			If the grid is visible, it will be drawn 
					using the grid pen style and color. The 
					grid lines will not be scaled with the 
					zoom (the space between them will of 
					course be, however)

   ============================================================*/
{

	return m_gridCol;

}

void CDiagramEditor::SetGridSize( CSize size )
/* ============================================================
	Function :		CDiagramEditor::SetGridSize
	Description :	Sets a new grid size.
	Access :		Public

	Return :		void
	Parameters :	CSize size	-	The new grid size.
					
	Usage :			If snap to grid is on, added, moved and 
					resized objects snap to the closest grid 
					position. If the background is resized, it 
					will also snap to the grid.

   ============================================================*/
{

	m_gridSize = size;
	if( m_hWnd )
		RedrawWindow();

}

CSize CDiagramEditor::GetGridSize() const
/* ============================================================
	Function :		CDiagramEditor::GetGridSize
	Description :	Gets the current grid size.
	Access :		Public

	Return :		CSize	-	The current grid size.
	Parameters :	none

	Usage :			If snap to grid is on, added, moved and 
					resized objects snap to the closest grid 
					position. If the background is resized, it 
					will also snap to the grid.

   ============================================================*/
{

	return m_gridSize;

}

void CDiagramEditor::SetGridPenStyle( int style )
/* ============================================================
	Function :		CDiagramEditor::SetGridPenStyle
	Description :	Sets the new grid pen style.
	Access :		Public

	Return :		void
	Parameters :	int style	-	The new pen style, one of 
									the style constants for 
									"CreatePen".
					
	Usage :			The grid (if visible) is drawn with a pen 
					created with the grid pen style. The grid 
					lines will not be scaled with the zoom 
					(the space between them will of course be, 
					however)

   ============================================================*/
{

	m_gridStyle = style;
	if( m_hWnd )
		RedrawWindow();

}

int CDiagramEditor::GetGridPenStyle() const
/* ============================================================
	Function :		CDiagramEditor::GetGridPenStyle
	Description :	Returns the pen style for the grid.
	Access :		Public

	Return :		int		-	The pen style, one of the style 
								constants for "CreatePen".
	Parameters :	none

	Usage :			The grid (if visible) is drawn with a pen 
					created with the grid pen style. The grid 
					lines will not be scaled with the zoom 
					(the space between them will of course be, 
					however)

   ============================================================*/
{

	return m_gridStyle;

}

void CDiagramEditor::SetSnapToGrid( BOOL snap )
/* ============================================================
	Function :		CDiagramEditor::SetSnapToGrid
	Description :	Enable/disable snap to grid.
	Access :		Public

	Return :		void
	Parameters :	BOOL snap	-	"TRUE" if objects should 
									snap to grid.
					
	Usage :			If snap to grid is on, added, moved and 
					resized objects snap to the closest grid 
					position. If the background is resized, it 
					will also snap to the grid.

   ============================================================*/
{

	m_snap = snap;

}

BOOL CDiagramEditor::GetSnapToGrid() const
/* ============================================================
	Function :		CDiagramEditor::GetSnapToGrid
	Description :	Gets the state of the snap-to-grid state.
	Access :		Public

	Return :		BOOL	-	"TRUE" if snap is on.
	Parameters :	none

	Usage :			If snap to grid is on, added, moved and 
					resized objects snap to the closest grid 
					position. If the background is resized, it 
					will also snap to the grid.

   ============================================================*/
{

	return m_snap;

}

void CDiagramEditor::SetResize( BOOL bgresize )
/* ============================================================
	Function :		CDiagramEditor::SetResize
	Description :	Enables/disables background resizing.
	Access :		Public

	Return :		void
	Parameters :	BOOL bgresize	-	"TRUE" if background 
										resizing is enabled.
					
	Usage :			If background resizing is enabled and the 
					user clicks between the resize zone value 
					and the virtual edge, the background is 
					displayed as selected.

   ============================================================*/
{

	m_bgResize = bgresize;

}

BOOL CDiagramEditor::GetResize() const
/* ============================================================
	Function :		CDiagramEditor::GetResize
	Description :	Returns the state of the background resize
					flag.
	Access :		Public

	Return :		BOOL	-	"TRUE" if background resizing is 
								enabled.
	Parameters :	none

	Usage :			If background resizing is enabled and the 
					user clicks between the resize zone value 
					and the virtual edge, the background is 
					displayed as selected.

   ============================================================*/
{

	return m_bgResize;

}

void CDiagramEditor::SetResizeZone( int bgresizezone )
/* ============================================================
	Function :		CDiagramEditor::SetResizeZone
	Description :	Sets a new resize zone for the editor.
	Access :		Public

	Return :		void
	Parameters :	int bgresizezone	-	New resize width.
					
	Usage :			If background resizing is enabled and the 
					user clicks between the resize zone value 
					and the virtual edge, the background is 
					displayed as selected.

   ============================================================*/
{

	m_bgResizeZone = bgresizezone;

}

int CDiagramEditor::GetResizeZone() const
/* ============================================================
	Function :		CDiagramEditor::GetResizeZone
	Description :	Returns the current resize zone.
	Access :		Public

	Return :		int		-	The resize zone in pixels.
	Parameters :	none

	Usage :			If background resizing is enabled and the 
					user clicks between the resize zone value 
					and the virtual edge, the background is 
					displayed as selected.

   ============================================================*/
{

	return m_bgResizeZone;

}

void CDiagramEditor::SetMargins( int left, int top, int right, int bottom )
/* ============================================================
	Function :		CDiagramEditor::SetMargins
	Description :	Sets margins for the virtual screen.
	Access :		Public

	Return :		void
	Parameters :	int left	-	New left margin.
					int top		-	New top margin.
					int right	-	New right margin.
					int bottom	-	New bottom margin.
					
	Usage :			Call to set new margins for the editor.

   ============================================================*/
{

	m_leftMargin = left;
	m_topMargin = top;
	m_rightMargin = right;
	m_bottomMargin = bottom;

}

void CDiagramEditor::GetMargins( int& left, int& top, int& right, int& bottom ) const
/* ============================================================
	Function :		CDiagramEditor::GetMargins
	Description :	Return the current margin.
	Access :		Public

	Return :		void
	Parameters :	int& left	-	Current left margin.
					int& top	-	Current top margin.
					int& right	-	Current right margin.
					int& bottom	-	Current bottom margin.
					
	Usage :			Call to get the margins of the editor.

   ============================================================*/
{

	left = m_leftMargin;
	top = m_topMargin;
	right = m_rightMargin;
	bottom = m_bottomMargin;

}

void CDiagramEditor::SetMarginColor( COLORREF marginColor )
/* ============================================================
	Function :		CDiagramEditor::SetMarginColor
	Description :	Set current margin colors.
	Access :		Public

	Return :		void
	Parameters :	COLORREF marginColor	-	The new color.
					
	Usage :			Call to set the margin color.

   ============================================================*/
{

	m_marginColor = marginColor;

	if( m_hWnd )
		RedrawWindow();

}

COLORREF CDiagramEditor::GetMarginColor() const
/* ============================================================
	Function :		CDiagramEditor::GetMarginColor
	Description :	Returns the current margin colors.
	Access :		Public

	Return :		COLORREF	-	Margin colors.
	Parameters :	none

	Usage :			Call to get the margin color.

   ============================================================*/
{

	return m_marginColor;

}

void CDiagramEditor::ShowMargin( BOOL show )
/* ============================================================
	Function :		CDiagramEditor::ShowMargin
	Description :	Show/hide margins.
	Access :		Public

	Return :		void
	Parameters :	BOOL show	-	"TRUE" to show margins, "FALSE" 
									to hide.
					
	Usage :			Call to show/hide the margins.

   ============================================================*/
{

	m_margin = show;

	if( m_hWnd )
		RedrawWindow();

}

BOOL CDiagramEditor::IsMarginVisible() const
/* ============================================================
	Function :		CDiagramEditor::IsMarginVisible
	Description :	Returns the visibility state of the 
					margins.
	Access :		Public

	Return :		BOOL	-	"TRUE" if the margins are 
								visible.
	Parameters :	none

	Usage :			Call to se if the margin visibility flag is 
					on.

   ============================================================*/
{

	return m_margin;

}

void CDiagramEditor::SetRestraints( int restraint )
/* ============================================================
	Function :		CDiagramEditor::SetRestraints
	Description :	Sets current restraint mode
	Access :		Public

	Return :		void
	Parameters :	BOOL restraint	-	restraint mode, see Usage 
										below
					
	Usage :			The restraint mode can be one of the 
					following ( defined in DialogEditor.h):
						"RESTRAINT_NONE" No restraints.
						"RESTRAINT_VIRTUAL" No objects can be moved outside the virtual rectangle.
						"RESTRAINT_MARGIN" No objects can be moved outside the background margins.

   ============================================================*/
{

	m_restraint = restraint;

}

int CDiagramEditor::GetRestraints() const
/* ============================================================
	Function :		CDiagramEditor::GetRestraints
	Description :	Returns the current restraint mode.
	Access :		Public

	Return :		int	-	The current restraint mode. See 
							Usage below

	Parameters :	none

	Usage :			The restraint mode can be one of the 
					following ( defined in DialogEditor.h):
						"RESTRAINT_NONE" No restraints.
						"RESTRAINT_VIRTUAL" No objects can be moved outside the virtual rectangle.
						"RESTRAINT_MARGIN" No objects can be moved outside the background margins.

   ============================================================*/
{

	return m_restraint;

}

BOOL CDiagramEditor::GetMultidraw() const
/* ============================================================
	Function :		CDiagramEditor::GetMultidraw
	Description :	Returns the multi draw state
	Access :		Public

	Return :		BOOL	-	"TRUE" if multi draw is set
	Parameters :	none

	Usage :			Multi draw means that the user can continue 
					to add controls after one is placed.

   ============================================================*/
{
	return m_multiDraw;
}

void CDiagramEditor::SetMultidraw( BOOL multidraw )
/* ============================================================
	Function :		CDiagramEditor::SetMultidraw
	Description :	Sets the multi draw state.
	Access :		Public

	Return :		void
	Parameters :	BOOL multidraw	-	New multi draw state
					
	Usage :			Multi draw means that the user can continue 
					to add controls after one is placed.

   ============================================================*/
{
	m_multiDraw = multidraw;
	m_drawing = FALSE;
	m_interactMode = MODE_NONE;
	delete m_drawObj;
	m_drawObj = NULL;
}

void CDiagramEditor::SetZoom( double zoom )
/* ============================================================
	Function :		CDiagramEditor::SetZoom
	Description :	Set the current zoom level.
	Access :		Public

	Return :		void
	Parameters :	double zoom	-	New zoom level. 1.0 means 
					no zoom.
					
	Usage :			If the virtual screen should be zoomed in 
					to double size, the zoom value should be 
					2.0, for example.

   ============================================================*/
{

	m_zoom = max( m_zoomMin, zoom );

	if( m_zoom != m_zoomMin )
		m_zoom = min( m_zoomMax, zoom );

	SetupScrollbars();
	if( m_hWnd )
		RedrawWindow();

}

double CDiagramEditor::GetZoom() const
/* ============================================================
	Function :		CDiagramEditor::GetZoom
	Description :	Returns the current zoom level of the editor. 
	Access :		Public

	Return :		double	-	The current zoom level. 1.0 is 
								no zoom.
	Parameters :	none

	Usage :			The zoom level is expressed as a double, 
					.25 means that all zoomed coordinates 
					should be multiplied with .25, for example.

   ============================================================*/
{

	return m_zoom;

}

void CDiagramEditor::SetZoomFactor( double zoomFactor )
/* ============================================================
	Function :		CDiagramEditor::SetZoomFactor
	Description :	Sets a new zoom factor
	Access :		Public

	Return :		void
	Parameters :	double zoomFactor	-	The new zoom factor
					
	Usage :			The zoom factor is used when the + and - 
					keys are enabled to zoom. The default value 
					is 0.01.

   ============================================================*/
{
	m_zoomFactor = zoomFactor;
}

double CDiagramEditor::GetZoomFactor() const
/* ============================================================
	Function :		CDiagramEditor::GetZoomFactor
	Description :	Returns the current zoom factor
	Access :		Public

	Return :		double	-	The zoom factor
	Parameters :	none

	Usage :			The zoom factor is used when the + and - 
					keys are enabled to zoom. The default value 
					is 0.01.

   ============================================================*/
{
	return m_zoomFactor;
}

double CDiagramEditor::GetZoomMax() const
/* ============================================================
	Function :		CDiagramEditor::GetZoomMax
	Description :	Returns the maximum allowed zoom level
	Access :		Public

	Return :		double	-	The maximum zoom level
	Parameters :	none

	Usage :			The zoom level will never go below or above 
					the min and max zoom levels

   ============================================================*/
{

	return m_zoomMax;

}

double CDiagramEditor::GetZoomMin() const
/* ============================================================
	Function :		CDiagramEditor::GetZoomMin
	Description :	Returns the minimum allowed zoom level
	Access :		Public

	Return :		double	-	The minimum zoom level
	Parameters :	none

	Usage :			The zoom level will never go below or above 
					the min and max zoom levels

   ============================================================*/
{

	return m_zoomMin;

}

void CDiagramEditor::SetZoomMax( double zoommax )
/* ============================================================
	Function :		CDiagramEditor::SetZoomMax
	Description :	Sets the maximum zoom level
	Access :		Public

	Return :		void
	Parameters :	double zoommax	-	The new max zoom
					
	Usage :			The zoom level will never go below or above 
					the min and max zoom levels

   ============================================================*/
{

	m_zoomMax = max( 0, zoommax );

}

void CDiagramEditor::SetZoomMin( double zoommin )
/* ============================================================
	Function :		CDiagramEditor::SetZoomMin
	Description :	Sets the mim zoom level
	Access :		Public

	Return :		void
	Parameters :	double zoommin	-	New minimum zoom level
					
	Usage :			The zoom level will never go below or above 
					the min and max zoom levels

   ============================================================*/
{

	m_zoomMin = max( 0, zoommin );

}

void CDiagramEditor::SetModified( BOOL dirty )
/* ============================================================
	Function :		CDiagramEditor::SetModified
	Description :	Set the modified-state of the data for the 
					document.
	Access :		Public

	Return :		void
	Parameters :	BOOL dirty	-	"TRUE" if the data should be 
									set as modified.
					
	Usage :			Call to mark the data as modified/saved.

   ============================================================*/
{

	if( m_objs )
		m_objs->SetModified( dirty );

}

BOOL CDiagramEditor::IsModified() const
/* ============================================================
	Function :		CDiagramEditor::IsModified
	Description :	Returns "TRUE" if the data in the editor is 
					modified.
	Access :		Public

	Return :		BOOL	-	"TRUE" if modified.
	Parameters :	none

	Usage :			Call to check if the data is modified.

   ============================================================*/
{

	BOOL res = FALSE;
	if( m_objs )
		res = m_objs->IsModified();

	return res;

}

CSize CDiagramEditor::GetMarkerSize() const
/* ============================================================
	Function :		CDiagramEditor::GetMarkerSize
	Description :	Gets the current selection marker size for 
					the editor background.
	Access :		Public

	Return :		CSize	-	The current size.
	Parameters :	none

	Usage :			Call to get the selection marker size.

   ============================================================*/
{

	return m_markerSize;

}

void CDiagramEditor::SetMarkerSize( CSize markerSize )
/* ============================================================
	Function :		CDiagramEditor::SetMarkerSize
	Description :	Sets the size of the selection markers for 
					the editor background.
	Access :		Public

	Return :		void
	Parameters :	CSize markerSize	-	New size of 
											markers.
					
	Usage :			Call to set the selection marker size.
					Will not set the selection marker size for 
					objects.

   ============================================================*/
{

	m_markerSize = markerSize;

}

UINT CDiagramEditor::GetKeyboardInterface() const
/* ============================================================
	Function :		CDiagramEditor::GetKeyboardInterface
	Description :	Returns the flags for the keyboard 
					interface
	Access :		Public

	Return :		UINT	-	The current flags
	Parameters :	none

	Usage :			The keyboard interface decides what keys 
					should be reacted on. The following flags 
					can be used:
						"KEY_ARROW" Will handle arrow keys. If shift is pressed, the selected objects will be resized, moved otherwise.
						"KEY_PGUPDOWN" Will handle Pg up & pg down. If Ctrl is pressed, the selected object will move to the top or the bottom of the z-order, one step up or down otherwise.
						"KEY_DELETE" Will handle delete key. The selected object(s) will be deleted, put into the container clipboard if Ctrl is pressed.
						"KEY_ESCAPE" Will handle escape key. If multi-draw mode, no object type is selected for drawing.
						"KEY_INSERT" Will handle insert key. The selected object will be copied if Ctrl is pressed, duplicated otherwise.
						"KEY_PLUSMINUS" Will handle the plus- and minus key. Will zoom in or out.
						"KEY_CTRL" Will handle Ctrl+A,Z,X,C,V and Enter keys. A = Select all Z = Undo X = Cut C = Copy V = Paste Enter = Show property dialog for the selected object.
					KEY_ALL sets all flags. KEY_NONE no flags.

   ============================================================*/
{

	return m_keyInterface;

}

void CDiagramEditor::SetKeyboardInterface( int keyInterface )
/* ============================================================
	Function :		CDiagramEditor::SetKeyboardInterface
	Description :	Sets the keyboard interface flag.
	Access :		Public

	Return :		void
	Parameters :	int keyInterface	-	The new flags
					
	Usage :			Call to set the keys the editor will handle.
					See "GetKeyboardInterface".

   ============================================================*/
{

	m_keyInterface = keyInterface;

}

void CDiagramEditor::SetPopupMenu( CDiagramMenu* popupmenu )
/* ============================================================
	Function :		CDiagramEditor::SetPopupMenu
	Description :	Sets the editor popup menu to popupmenu.
	Access :		Public

	Return :		void
	Parameters :	CDiagramMenu* popupmenu	-	The popup menu 
												to use.
					
	Usage :			Call to set the popup menu for the editor.
					Note that the editor owns the popup menu.

   ============================================================*/
{
	if( m_popupMenu )
		delete m_popupMenu;

	m_popupMenu = popupmenu;

}

CDiagramMenu* CDiagramEditor::GetPopupMenu() const
/* ============================================================
	Function :		CDiagramEditor::GetPopupMenu
	Description :	Returns a pointer to the editor popup menu.
	Access :		Public

	Return :		CDiagramMenu*	-	The popup menu. 
										Might be "NULL".
	Parameters :	none

	Usage :			Call to get a pointer to the editor popup 
					menu. Note that the editor owns the menu.

   ============================================================*/
{

	return m_popupMenu;

}

/////////////////////////////////////////////////////////////////////////////
// CDiagramEditor mouse handling

void CDiagramEditor::OnLButtonDown( UINT nFlags, CPoint point ) 
/* ============================================================
	Function :		CDiagramEditor::OnLButtonDown
	Description :	Handles the "WM_LBUTTONDOWN" message. We 
					select/deselect objects and set internal 
					modes as appropriate.
	Access :		Protected

	Return :		void
	Parameters :	UINT nFlags		-	Key-down flag
					CPoint point	-	Mouse position
					
	Usage :			Called from MFC. Do not call from code.

   ============================================================*/
{

	SetPanning( FALSE );

	// Declarations
	int count = 0;
	CDiagramEntity* obj;
	CPoint virtpoint( point );
	ScreenToVirtual( virtpoint );

	// Setting up
	SetFocus();
	SetCapture();

	// Resetting modes
	if( m_interactMode != MODE_DRAWING )
	{
		m_interactMode = MODE_NONE;
		m_subMode = DEHT_NONE;
	}

	m_bgResizeSelected = FALSE;
	m_multiSelObj = NULL;

	// If we click on an already selected object, 
	// and have more than one object selected,
	// we want to move all selected objects
	if( m_objs && GetSelectCount() > 1 && !( nFlags & MK_CONTROL ) )
	{

		while( ( obj = m_objs->GetAt( count++ ) ) )
		{
			if( obj->GetHitCode( virtpoint ) == DEHT_BODY && obj->IsSelected() )
			{
				m_interactMode = MODE_MOVING;
				CRect rect = obj->GetRect();

				// We might need to use a denormalized
				// rect, as lines will not be normalized.
				BOOL useright = FALSE;
				BOOL usebottom = FALSE;
				if( rect.left > rect.right )
					useright = TRUE;
				if( rect.top > rect.bottom )
					usebottom = TRUE;

				VirtualToScreen( rect );

				int startx = rect.left;
				if( useright )
					startx = rect.right;
				int starty = rect.top;
				if( usebottom )
					starty = rect.bottom;

				// Anchor object
				m_multiSelObj = obj;

				// Offset from top-left corner
				// in the anchor object.
				m_deltaPoint = point - CPoint( startx, starty );

			}
		}

		if( m_interactMode == MODE_MOVING )
		{
			// We have clicked in one of many selected objects.
			// Set cursor and snapshot for Undo.
			::SetCursor( m_multiSelObj->GetCursor( DEHT_BODY ) );
			m_objs->Snapshot();
		}

	}

	if( m_objs && m_interactMode == MODE_DRAWING )
	{
		// The user wants to draw an object.
		// We add it to the data container and sets the appropriate mode

		if( OutsideRestraints( virtpoint ) )
		{
			m_interactMode = MODE_NONE;
			return;
		}

		m_objs->Snapshot();

		UnselectAll();

		CDiagramEntity* newobj = m_drawObj->Clone();

		// If snap-to-grid is on, we must
		// update the desired position
		if( m_snap )
		{

			virtpoint.x = SnapX( virtpoint.x );
			virtpoint.y = SnapY( virtpoint.y );

		}

		newobj->SetRect( CRect( virtpoint.x, virtpoint.y, virtpoint.x , virtpoint.y ) );
		newobj->Select( TRUE );

		// Add the object to the container
		AddObject( newobj );

		// Set modes
		m_interactMode = MODE_RESIZING;
		m_subMode = DEHT_BOTTOMRIGHT;

	}

	if( m_objs && m_interactMode == MODE_NONE )
	{

		// Clearing states
		// If Ctrl is not held down, we
		// clear all selections
		if( !( nFlags & MK_CONTROL ) )
			UnselectAll();

		count = GetObjectCount();
		BOOL goon = TRUE;

		// We check if we click on any object. If that is 
		// the case, we return on what part of the object 
		// we clicked.
		while( goon && ( obj = m_objs->GetAt( --count ) ) )
		{
			CRect rect = obj->GetRect();
			VirtualToScreen( rect );

			// We check for a non-normailized rect, 
			// as this is allowed for - for example - lines.
			if( obj->GetTop() > obj->GetBottom() )
			{
				int temp = rect.top;
				rect.top = rect.bottom;
				rect.bottom = temp;
			}

			if( obj->GetLeft() > obj->GetRight() )
			{
				int temp = rect.left;
				rect.left = rect.right;
				rect.right = temp;
			}

			int hitCode = obj->GetHitCode( point, rect );
			if( hitCode != DEHT_NONE )
			{
				goon = FALSE;
				if( !( nFlags & MK_CONTROL ) )
				{
					// We unselect all again, as we might
					// have overlapping objects
					UnselectAll();
					obj->Select( TRUE );
				}
				else
				{
					// We toggle the selection of the 
					// object if Ctrl is pressed
					if( obj->IsSelected() )
						obj->Select( FALSE );
					else
						obj->Select( TRUE );
				}

				// We set the appropriate mode, either
				// moving or resizing depending on where
				// the click hit.
				if( hitCode == DEHT_BODY && !( nFlags & MK_CONTROL ) )
				{
					::SetCursor( obj->GetCursor( DEHT_BODY ) );
					m_interactMode = MODE_MOVING;

					CRect rect = obj->GetRect();

					// We might need to use a denormalized
					// rect, as lines will not be normalized.
					BOOL useright = FALSE;
					BOOL usebottom = FALSE;
					if( rect.left > rect.right )
						useright = TRUE;
					if( rect.top > rect.bottom )
						usebottom = TRUE;

					VirtualToScreen( rect );

					int startx = rect.left;
					if( useright )
						startx = rect.right;
					int starty = rect.top;
					if( usebottom )
						starty = rect.bottom;
					if( GetSelectCount() > 1 )
						m_multiSelObj = obj;
					m_deltaPoint = point - CPoint( startx, starty );

				}
				else if( !( nFlags & MK_CONTROL ) )
				{
					m_interactMode = MODE_RESIZING;
					m_subMode = hitCode;
				}
				else
					m_interactMode = MODE_NONE;
			}
		}

		// Save to undo-stack...
		if( m_interactMode != MODE_NONE )
			m_objs->Snapshot();

		// If no objects were selected, we assume either 
		// rubberbanding or background resize
		if( !IsAnyObjectSelected() )
		{
			if( m_bgResize )
			{
				// If we allow background resizing, we test if
				// the click was inside the resize zone.
				if( ( virtpoint.x >= GetVirtualSize().cx - m_bgResizeZone &&
					virtpoint.x <= GetVirtualSize().cx )
					||
					( virtpoint.y >= GetVirtualSize().cy - m_bgResizeZone && 
					virtpoint.y <= GetVirtualSize().cy )
					 )
				{
					m_bgResizeSelected = TRUE;
					int hitCode = GetHitCode( virtpoint );
					if( hitCode != DEHT_NONE && hitCode != DEHT_BODY )
					{
						// It was - set the appropriate mode
						m_interactMode = MODE_BGRESIZING;
						m_subMode = hitCode;
						m_objs->Snapshot();
					}

					RedrawWindow();
				}
			}

			if( m_interactMode == MODE_NONE )
			{
				// If nothing else is set, we assume
				// rubberbanding.
				m_selectionRect.left = m_selectionRect.right = point.x;
				m_selectionRect.top = m_selectionRect.bottom = point.y;
				m_interactMode = MODE_RUBBERBANDING;
			}
		}
	}

	// Cleaning up and redrawing as necessary.
	RemoveUnselectedPropertyDialogs();
	if( m_interactMode != MODE_NONE )
		RedrawWindow();

	//ShowProperties();
	CWnd::OnLButtonDown( nFlags, point );

}

void CDiagramEditor::OnMouseMove( UINT nFlags, CPoint point )
/* ============================================================
	Function :		CDiagramEditor::OnMouseMove
	Description :	Handles the "WM_MOUSEMOVE" message. We handle 
					moving or resizing of objects, or resizing 
					of the virtual screen.
	Access :		Protected

	Return :		void
	Parameters :	UINT nFlags		-	Key-down flags
					CPoint point	-	Mouse position
					
	Usage :			Called from MFC. Do not call from code.

   ============================================================*/
{

	if( m_interactMode != MODE_NONE )
	{

		CClientDC	dc( this );
		CRect clientRect;
		GetClientRect( &clientRect );
		CPoint virtpoint( point );
		ScreenToVirtual( virtpoint );

		if( m_interactMode == MODE_BGRESIZING )
		{

			if( m_snap )
			{

				virtpoint.x = SnapX( virtpoint.x );
				virtpoint.y = SnapY( virtpoint.y );

			}

			virtpoint.x = max( virtpoint.x, 1 );
			virtpoint.y = max( virtpoint.y, 1 );
			int xsize = GetVirtualSize().cx;
			int ysize = GetVirtualSize().cy;

			if( m_subMode == DEHT_TOPRIGHT )
			{
				xsize = virtpoint.x;
			}
			else if( m_subMode == DEHT_RIGHTMIDDLE )
			{
				xsize = virtpoint.x;
			}
			else if( m_subMode == DEHT_BOTTOMRIGHT )
			{
				xsize = virtpoint.x;
				ysize = virtpoint.y;
			}
			else if( m_subMode == DEHT_BOTTOMMIDDLE )
			{
				ysize = virtpoint.y;
			}
			else if( m_subMode == DEHT_BOTTOMLEFT )
			{
				ysize = virtpoint.y;
			}

			if( m_restraint == RESTRAINT_VIRTUAL )
			{
				CSize size = GetContainingSize();
				xsize = max( size.cx, xsize );
				ysize = max( size.cy, ysize );
			}
			else if( m_restraint == RESTRAINT_MARGIN )
			{
				CSize size = GetContainingSize();
				xsize = max( size.cx + m_rightMargin, xsize );
				ysize = max( size.cy + m_bottomMargin, ysize );
				xsize = max( m_leftMargin + m_rightMargin, xsize );
				ysize = max( m_topMargin + m_bottomMargin, ysize );
			}

			SetVirtualSize( CSize( xsize, ysize ), nFlags );
			ScrollPoint( point );

		}
		if( m_interactMode == MODE_RESIZING )
		{

			if( m_snap )
			{

				virtpoint.x = SnapX( virtpoint.x );
				virtpoint.y = SnapY( virtpoint.y );

			}

			// If we are moving, we will update one or 
			// two sides of the object.
			double ypos = static_cast< double >( virtpoint.y );
			double xpos = static_cast< double >( virtpoint.x );

			CDiagramEntity* obj = GetSelectedObject();
			if( obj )
			{
				CSize minimum = obj->GetMinimumSize();
				CSize maximum = obj->GetMaximumSize();
				if( m_subMode == DEHT_BOTTOMMIDDLE )
				{

					// Constraints
					if( minimum.cy != -1 && ypos - obj->GetTop() < minimum.cy )
						ypos = obj->GetTop() + minimum.cy;
					if( maximum.cy != -1 && ypos - obj->GetTop() > maximum.cy )
						ypos = obj->GetTop() + maximum.cy;

					AdjustForRestraints( xpos, ypos );
					obj->SetRect( obj->GetLeft(), obj->GetTop(), obj->GetRight(), ypos, false, nFlags );

				}
				else if( m_subMode == DEHT_TOPMIDDLE )
				{

					// Constraints
					if( minimum.cy != -1 && obj->GetBottom() - ypos < minimum.cy )
						ypos = obj->GetBottom() - minimum.cy;
					if( maximum.cy != -1 && obj->GetBottom() - ypos > maximum.cy )
						ypos = obj->GetBottom() - maximum.cy;

					AdjustForRestraints( xpos, ypos );
					obj->SetRect( obj->GetLeft(), ypos, obj->GetRight(), obj->GetBottom(), false, nFlags );

				}
				else if( m_subMode == DEHT_LEFTMIDDLE )
				{

					// Constraints
					if( minimum.cx != -1 && obj->GetRight() - xpos < minimum.cx )
						xpos = obj->GetRight() - minimum.cx;
					if( maximum.cx != -1 && obj->GetRight() - xpos > maximum.cx )
						xpos = obj->GetRight() - maximum.cx;

					AdjustForRestraints( xpos, ypos );
					obj->SetRect( xpos, obj->GetTop(), obj->GetRight(), obj->GetBottom(), false, nFlags );

				}
				else if( m_subMode == DEHT_RIGHTMIDDLE )
				{

					// Constraints
					if( minimum.cx != -1 && xpos - obj->GetLeft() < minimum.cx )
						xpos = obj->GetLeft() + minimum.cx;
					if( maximum.cx != -1 && xpos - obj->GetLeft() > maximum.cx )
						xpos = obj->GetLeft() + maximum.cx;

					AdjustForRestraints( xpos, ypos );
					obj->SetRect( obj->GetLeft(), obj->GetTop(), xpos, obj->GetBottom(), false, nFlags );

				}
				else if( m_subMode == DEHT_TOPLEFT )
				{

					// Constraints
					if( minimum.cy != -1 && obj->GetBottom() - ypos < minimum.cy )
						ypos = obj->GetBottom() - minimum.cy;
					if( minimum.cx != -1 && obj->GetRight() - xpos < minimum.cx )
						xpos = obj->GetRight() - minimum.cx;
					if( maximum.cy != -1 && obj->GetBottom() - ypos > maximum.cy )
						ypos = obj->GetBottom() - maximum.cy;
					if( maximum.cx != -1 && obj->GetRight() - xpos > maximum.cx )
						xpos = obj->GetRight() - maximum.cx;

					AdjustForRestraints( xpos, ypos );
					obj->SetRect( xpos, ypos, obj->GetRight(), obj->GetBottom(), false, nFlags );

				}
				else if( m_subMode == DEHT_TOPRIGHT )
				{

					// Constraints
					if( minimum.cy != -1 && obj->GetBottom() - ypos < minimum.cy )
						ypos = obj->GetBottom() - minimum.cy;
					if( minimum.cx != -1 && xpos - obj->GetLeft() < minimum.cx )
						xpos = obj->GetLeft() + minimum.cx;
					if( maximum.cy != -1 && obj->GetBottom() - ypos > maximum.cy )
						ypos = obj->GetBottom() - maximum.cy;
					if( maximum.cx != -1 && xpos - obj->GetLeft() > maximum.cx )
						xpos = obj->GetLeft() + maximum.cx;

					AdjustForRestraints( xpos, ypos );
					obj->SetRect( obj->GetLeft(), ypos, xpos, obj->GetBottom(), false, nFlags );

				}
				else if( m_subMode == DEHT_BOTTOMLEFT )
				{

					// Constraints
					if( minimum.cy != -1 && ypos - obj->GetTop() < minimum.cy )
						ypos = obj->GetTop() + minimum.cy;
					if( minimum.cx != -1 && obj->GetRight() - xpos < minimum.cx )
						xpos = obj->GetRight() - minimum.cx;
					if( maximum.cy != -1 && ypos - obj->GetTop() > maximum.cy )
						ypos = obj->GetTop() + maximum.cy;
					if( maximum.cx != -1 && obj->GetRight() - xpos > maximum.cx )
						xpos = obj->GetRight() - maximum.cx;

					AdjustForRestraints( xpos, ypos );
					obj->SetRect( xpos, obj->GetTop(), obj->GetRight(), ypos, false, nFlags );

				}
				else if( m_subMode == DEHT_BOTTOMRIGHT )
				{

					// Constraints
					if( minimum.cy != -1 && ypos - obj->GetTop() < minimum.cy )
						ypos = obj->GetTop() + minimum.cy;
					if( minimum.cx != -1 && xpos - obj->GetLeft() < minimum.cx )
						xpos = obj->GetLeft() + minimum.cx;
					if( maximum.cy != -1 && ypos - obj->GetTop() > maximum.cy )
						ypos = obj->GetTop() + maximum.cy;
					if( maximum.cx != -1 && xpos - obj->GetLeft() > maximum.cx )
						xpos = obj->GetLeft() + maximum.cx;

					AdjustForRestraints( xpos, ypos );
					obj->SetRect( obj->GetLeft(), obj->GetTop(), xpos, ypos, false, nFlags );

				}

			}

			// Scroll if we are outside any edge
			ScrollPoint( point );
			RedrawWindow();
		}
		else if( m_objs && m_interactMode == MODE_MOVING )
		{

			// If we move, we just update the positions
			// of all the objects.
			double offsetx = round( static_cast< double >( m_deltaPoint.x ) / GetZoom() );
			double offsety = round( static_cast< double >( m_deltaPoint.y ) / GetZoom() );
			int count = 0;
			CDiagramEntity* obj;
			double width;
			double height;

			double left;
			double top;

			if( m_multiSelObj )
			{
				left = virtpoint.x - offsetx;
				top = virtpoint.y - offsety;
				if( m_snap )
				{
					left = SnapX(  static_cast< int >( left ) );
					top = SnapY( static_cast< int >( top ) );
				}

				offsetx = left - m_multiSelObj->GetLeft();
				offsety = top - m_multiSelObj->GetTop();

				InsideRestraints( offsetx, offsety );

				m_multiSelObj->SetRect( m_multiSelObj->GetLeft() + offsetx, m_multiSelObj->GetTop() + offsety, m_multiSelObj->GetRight() + offsetx, m_multiSelObj->GetBottom() + offsety, false, nFlags );

				while( ( obj = m_objs->GetAt( count++ ) ) )
					if( obj->IsSelected() && obj != m_multiSelObj )
						obj->MoveRect( offsetx, offsety );
			}
			else
			{

				obj = GetSelectedObject();
				if( obj )
				{

					width = obj->GetRight() - obj->GetLeft();
					height = obj->GetBottom() - obj->GetTop();

					left = virtpoint.x - offsetx;
					top = virtpoint.y - offsety;

					if( m_snap )
					{
						left = SnapX( static_cast< int >( left ) );
						top = SnapY( static_cast< int >( top ) );
					}

					double right = left + width;
					double bottom = top + height;

					AdjustForRestraints( left, top, right, bottom );
					obj->SetRect( left, top, right , bottom, false, nFlags );

				}
			}

			// Scroll if we are outside any edge
			CPoint outside = ScrollPoint( point );
			RedrawWindow();

		}
		else if( m_interactMode == MODE_RUBBERBANDING )
		{

			// We are selecting objects
			CRect rect( m_selectionRect );

			// Erase old selection rect
			if( m_selectionRect.left != m_selectionRect.right || m_selectionRect.top != m_selectionRect.bottom )
			{
				rect.NormalizeRect();
				dc.DrawFocusRect( rect );
			}

			// Scroll if we are outside any edge
			CPoint outside = ScrollPoint( point );
			m_selectionRect.OffsetRect( -outside.x, -outside.y );

			// Update and draw the selection rect
			m_selectionRect.right = point.x;
			m_selectionRect.bottom = point.y;
			rect = m_selectionRect;
			rect.NormalizeRect();

			dc.DrawFocusRect( rect );

		}
	}

	if(m_pFrame != NULL)
	{
		CString strText;

		if( m_objs == NULL )
			strText.Format( "마우스 위치: X = %d, Y = %d", point.x, point.y );
		else
			strText.Format( "마우스 위치: X = %d, Y = %d 컨트롤개수: %d개", point.x, point.y, m_objs->GetSize() );
            

		m_pFrame->m_wndStatusBar.SetPaneText( 2, strText );
		
	}

	CWnd::OnMouseMove( nFlags, point );

}

void CDiagramEditor::OnLButtonUp( UINT nFlags, CPoint point )
/* ============================================================
	Function :		CDiagramEditor::OnLButtonUp
	Description :	Handles the "WM_LBUTTONUP" message. Mainly, 
					we snap to grid if appropriate.
	Access :		Protected

	Return :		void
	Parameters :	UINT nFlags		-	not interested.
					CPoint point	-	The position of the mouse.
					
	Usage :			Called from MFC. Do not call from code.

   ============================================================*/
{

	// Reset modes
	ReleaseCapture();

	int count = 0;
	CDiagramEntity* obj;

	if( m_objs && m_interactMode == MODE_MOVING )
	{

		// We set all the object rectangles to trigger
		// the virtual MoveObject function, thus 
		// allowing derived editors to know that 
		// objects has been moved.
		while( ( obj = m_objs->GetAt( count++ ) ) )
		{
			if( obj->IsSelected() )
			{
				CRect rect = obj->GetRect();
				if( m_snap )
				{
					// If we move objects, and snap to grid is on
					// we snap here
					int height = rect.Height();
					int width = rect.Width();

					// Find closest snap-points
					rect.left = SnapX( rect.left );
					rect.top = SnapY( rect.top );

					rect.right = rect.left + width;
					rect.bottom = rect.top + height;
				}

				MoveObject( obj, rect );
			}
		}

		m_objs->SetModified( TRUE );

	}
	else if( m_objs && m_interactMode == MODE_RESIZING )
	{
		// If we resize objects, and snap to grid is on
		// we snap here

		if( m_snap )
		{
			while( ( obj = m_objs->GetAt( count++ ) ) )
			{
				if( obj->IsSelected() )
				{
					CRect rect = obj->GetRect();
					CRect newrect = rect;

					// Find closest snap-points
					rect.left = SnapX( rect.left );
					rect.top = SnapY( rect.top );
					rect.right = SnapX( rect.right );
					rect.bottom = SnapY ( rect.bottom );

					// Updating rect depending on resize-type.
					switch( m_subMode )
					{
						case DEHT_BOTTOMMIDDLE:
							newrect.bottom = rect.bottom;
						break;
						case DEHT_TOPMIDDLE:
							newrect.top = rect.top;
						break;
						case DEHT_LEFTMIDDLE:
							newrect.left = rect.left;
						break;
						case DEHT_RIGHTMIDDLE:
							newrect.right = rect.right;
						break;
						case DEHT_TOPLEFT:
							newrect.top = rect.top;
							newrect.left = rect.left;
						break;
						case DEHT_TOPRIGHT:
							newrect.top = rect.top;
							newrect.right = rect.right;
						break;
						case DEHT_BOTTOMLEFT:
							newrect.bottom = rect.bottom;
							newrect.left = rect.left;
						break;
						case DEHT_BOTTOMRIGHT:
							newrect.bottom = rect.bottom;
							newrect.right = rect.right;
						break;
					}

					obj->SetRect( newrect );
				}
			}
		}
		m_objs->SetModified( TRUE );

	}
	else if( m_objs && m_interactMode == MODE_RUBBERBANDING )
	{

		// Remove all former selections
		UnselectAll();

		// We convert the selection rect to virtual coordinates, 
		// and make sure that the rect contains at least some 
		// width and height ( IntersectRect will not work otherwise )
		CRect rect( m_selectionRect );
		ScreenToVirtual( rect );
		if( rect.TopLeft() == rect.BottomRight() )
			rect.InflateRect( 1, 1 );

		// We loop all objects, checking if we got any overlap.
		count = 0;
		while( ( obj = m_objs->GetAt( count++ ) ) )
		{
			if( obj->BodyInRect( rect ) )
				obj->Select( TRUE );
		}

	}

	// Redraw and reset modes
	RedrawWindow();
	if( m_multiDraw && m_drawing && m_drawObj )
		m_interactMode = MODE_DRAWING;
	else
	{
		m_drawing = FALSE;
		m_interactMode = MODE_NONE;
	}

	m_subMode = DEHT_NONE;
	CWnd::OnLButtonUp( nFlags, point );

}

void CDiagramEditor::OnLButtonDblClk( UINT nFlags, CPoint point ) 
/* ============================================================
	Function :		CDiagramEditor::OnLButtonDblClk
	Description :	Handles the "WM_LBUTTONDBLCLK" message. We 
					show a property dialog if appropriate.
	Access :		Protected

	Return :		void
	Parameters :	UINT nFlags		-	not interested
					CPoint point	-	not interested
					
	Usage :			Called from MFC. Do not call from code.

   ============================================================*/
{

	ShowProperties();
	CWnd::OnLButtonDblClk( nFlags, point );

}

void CDiagramEditor::OnRButtonDown( UINT nFlags, CPoint point ) 
/* ============================================================
	Function :		CDiagramEditor::OnRButtonDown
	Description :	Handles the "WM_RBUTTONDOWN" message. 
	Access :		Protected

	Return :		void
	Parameters :	UINT nFlags		-	not interested
					CPoint point	-	not interested
					
	Usage :			Called from MFC. Do not call from code.

   ============================================================*/
{

	SetPanning( FALSE );

	if( m_objs )
	{
		int count = 0;
		CDiagramEntity* obj;
		CPoint virtpoint( point );
		ScreenToVirtual( virtpoint );

		// We check if we click on any object body. If that is 
		// the case, we select the object
		while( ( obj = m_objs->GetAt( count++ ) ) )
		{
			if( obj->GetHitCode( virtpoint ) == DEHT_BODY )
			{
				if( !obj->IsSelected() )
				{
					UnselectAll();
					obj->Select( TRUE );
				}
			}
		}

		RedrawWindow();
	}

	m_interactMode = MODE_NONE;
	m_drawing = FALSE;

	CWnd::OnRButtonDown( nFlags, point );

}

void CDiagramEditor::OnRButtonUp( UINT nFlags, CPoint point ) 
/* ============================================================
	Function :		CDiagramEditor::OnRButtonUp
	Description :	Handles the "WM_RBUTTONUP" message. We show 
					popup menues as appropriate.
	Access :		Protected

	Return :		void
	Parameters :	UINT nFlags		-	not interested
					CPoint point	-	not interested
					
	Usage :			Called from MFC. Do not call from code.

   ============================================================*/
{

	CPoint screen( point );
	CPoint virtpoint( point );

	ClientToScreen( &screen );
	ScreenToVirtual( virtpoint );

	if( GetSelectCount() == 1 )
	{
		CDiagramEntity* obj = GetSelectedObject();
		if( obj->GetHitCode( virtpoint ) == DEHT_BODY )
			obj->ShowPopup( screen, this );
		else
			ShowPopup( screen );
	}
	else
		ShowPopup( screen );

	CWnd::OnRButtonUp( nFlags, point );

}

UINT CDiagramEditor::OnGetDlgCode() 
/* ============================================================
	Function :		CDiagramEditor::OnGetDlgCode
	Description :	Handles the "WM_GETDLGCODE" message. We 
					return the keys we want.
	Access :		Protected

	Return :		UINT	-	"DLGC_WANTALLKEYS", we want all 
								keys.
	Parameters :	none

	Usage :			Called from MFC. Do not call from code.

   ============================================================*/
{

	return DLGC_WANTALLKEYS;

}

void CDiagramEditor::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags ) 
/* ============================================================
	Function :		CDiagramEditor::OnKeyDown
	Description :	Handles the "WM_KEYDOWN" message. We provide 
					a simple keyboard interface.
	Access :		Protected

	Return :		void
	Parameters :	UINT nChar		-	Character pressed
					UINT nRepCnt	-	not interested
					UINT nFlags		-	not interested
					
	Usage :			Called from MFC. Do not call from code.

   ============================================================*/
{

	SetPanning( FALSE );

	if( m_keyInterface != KEY_NONE )
	{
		// Clearing the flags
		GetAsyncKeyState( VK_SHIFT );
		GetAsyncKeyState( VK_CONTROL );

		if( m_objs )
		{

			int count = 0;
			CDiagramEntity* obj;

			double offsetstepx = 1.0 / GetZoom();
			double offsetstepy = 1.0 / GetZoom();
			if( m_snap )
			{
				offsetstepx = static_cast< double >( m_gridSize.cx )/ GetZoom();
				offsetstepy = static_cast< double >( m_gridSize.cy )/ GetZoom();
			}

			double offsetx = 0.0;
			double offsety = 0.0;

			BOOL move = FALSE;
			BOOL resize = FALSE;
			BOOL redraw = TRUE;
			
			if( ( m_keyInterface & KEY_ARROW ) && ( nChar == VK_DOWN ) )
			{
				offsety=offsetstepy;
				if( GetAsyncKeyState( VK_SHIFT ) )
					resize = TRUE;
				else
					move = TRUE;
			}
			else if( ( m_keyInterface & KEY_ARROW ) && ( nChar == VK_UP ) )
			{
				offsety=-offsetstepy;
				if( GetAsyncKeyState( VK_SHIFT ) )
					resize = TRUE;
				else
					move = TRUE;
			}
			else if( ( m_keyInterface & KEY_ARROW ) && ( nChar == VK_LEFT ) )
			{
				offsetx=-offsetstepx;
				if( GetAsyncKeyState( VK_SHIFT ) )
					resize = TRUE;
				else
					move = TRUE;
			}
			else if( ( m_keyInterface & KEY_ARROW ) && ( nChar == VK_RIGHT ) )
			{
				offsetx=offsetstepx;
				if( GetAsyncKeyState( VK_SHIFT ) )
					resize = TRUE;
				else
					move = TRUE;
			}
			else if( ( m_keyInterface & KEY_DELETE ) && ( nChar == VK_DELETE ) )
			{
				if( GetAsyncKeyState( VK_SHIFT ) )
					Cut();
				else
					DeleteAllSelected();
			}
			else if( ( m_keyInterface & KEY_INSERT ) && ( nChar == VK_INSERT ) )
			{
				if( GetAsyncKeyState( VK_SHIFT ) )
					Paste();
				else
					Duplicate();
			}
			else if( ( m_keyInterface & KEY_CTRL ) && nChar == VK_RETURN && GetAsyncKeyState( VK_CONTROL ) )
				ShowProperties();
			else if( ( m_keyInterface & KEY_CTRL ) && nChar == _TCHAR( 'A' ) && GetAsyncKeyState( VK_CONTROL ) )
				SelectAll();
			else if( ( m_keyInterface & KEY_CTRL ) && nChar == _TCHAR( 'X' ) && GetAsyncKeyState( VK_CONTROL ) )
				Cut();
			else if( ( m_keyInterface & KEY_CTRL ) && nChar == _TCHAR( 'V' ) && GetAsyncKeyState( VK_CONTROL ) )
				Paste();
			else if( ( m_keyInterface & KEY_CTRL ) && nChar == _TCHAR( 'C' ) && GetAsyncKeyState( VK_CONTROL ) )
				Copy();
			else if( ( m_keyInterface & KEY_CTRL ) && nChar == _TCHAR( 'Z' ) && GetAsyncKeyState( VK_CONTROL ) )
				Undo();
			else if( ( m_keyInterface & KEY_PGUPDOWN ) && nChar == VK_NEXT && GetAsyncKeyState( VK_CONTROL ) )
				Bottom();
			else if( ( m_keyInterface & KEY_PGUPDOWN ) && nChar == VK_PRIOR && GetAsyncKeyState( VK_CONTROL ) )
				Front();
			else if( ( m_keyInterface & KEY_PGUPDOWN ) && nChar == VK_NEXT)
				Down();
			else if( ( m_keyInterface & KEY_PGUPDOWN ) && nChar == VK_PRIOR)
				Up();

			if( move )
			{
				InsideRestraints( offsetx, offsety );
				m_objs->Snapshot();
				while( ( obj = m_objs->GetAt( count++ ) ) )
				{
					if( obj->IsSelected() )
					{
						double width = obj->GetRight() - obj->GetLeft();
						double height = obj->GetBottom() - obj->GetTop();

						double left = obj->GetLeft() + offsetx;
						double top = obj->GetTop() + offsety;

						if( m_snap )
						{
							left = SnapX( static_cast< int >( left ) );
							top = SnapY( static_cast< int >( top ) );
						}

						double right = left + width;
						double bottom = top + height;

						AdjustForRestraints( left, top, right, bottom );
						MoveObject( obj, CRect( round( left ), round( top ), round( right ), round( bottom ) ) );
						redraw = TRUE;
						m_objs->SetModified( TRUE );
					}
				}
			}

			if( resize )
			{
				m_objs->Snapshot();
				InsideRestraints( offsetx, offsety );
				while( ( obj = m_objs->GetAt( count++ ) ) )
				{
					if( obj->IsSelected() )
					{

						double right = obj->GetRight() + offsetx;
						double bottom = obj->GetBottom() + offsety;
						if( m_snap )
						{
							right = SnapX( static_cast< int >( right ) );
							bottom = SnapY( static_cast< int >( bottom ) );
						}

						obj->SetRect( obj->GetLeft(), obj->GetTop(), right, bottom );

						m_objs->SetModified( TRUE );
						redraw = TRUE;
					}
				}
			}

			if( redraw )
				RedrawWindow();
		}

		if( ( m_keyInterface & KEY_ESCAPE ) && ( nChar == VK_ESCAPE ) )
		{
			m_interactMode = MODE_NONE;
			m_drawing = FALSE;
		}

		// Keys independent of any data
		if( ( m_keyInterface & KEY_PLUSMINUS ) && ( nChar == VK_ADD ) )
			SetZoom( GetZoom() + GetZoomFactor() );

		if( ( m_keyInterface & KEY_PLUSMINUS ) && ( nChar == VK_SUBTRACT ) )
			SetZoom( GetZoom() - GetZoomFactor() );
	}

	CWnd::OnKeyDown( nChar, nRepCnt, nFlags );

}

BOOL CDiagramEditor::OnSetCursor( CWnd* pWnd, UINT nHitTest, UINT message ) 
/* ============================================================
	Function :		CDiagramEditor::OnSetCursor
	Description :	Handles the "WM_SETCURSOR" message. We set 
					cursors as appropriate.
	Access :		Protected

	Return :		BOOL			-	not interested
	Parameters :	CWnd* pWnd		-	not interested
					UINT nHitTest	-	not interested
					UINT message	-	not interested
					
	Usage :			Called from MFC. Do not call from code.

   ============================================================*/
{

	BOOL res = TRUE;
	HCURSOR cursor = GetCursor();
	if( cursor )
		::SetCursor( cursor );
	else
		res = CWnd::OnSetCursor( pWnd, nHitTest, message );

	return res;

}

HCURSOR CDiagramEditor::GetCursor( int hit ) const
/* ============================================================
	Function :		CDiagramEditor::GetCursor
	Description :	Returns a "HCURSOR" for the hit-point value 
					(defined in DiagramEntity.h) 
	Access :		Public

	Return :		HCURSOR	-	The cursor to show, "NULL" if 
								default.
	Parameters :	int hit	-	The hit-point value
					
	Usage :			Virtual. Can be overridden in a derived
					class to display other resize cursors. 
					"hit" can be one of the following:
						"DEHT_NONE" No hit-point
						"DEHT_BODY" Inside object body
						"DEHT_TOPLEFT" Top-left corner
						"DEHT_TOPMIDDLE" Middle top-side
						"DEHT_TOPRIGHT" Top-right corner
						"DEHT_BOTTOMLEFT" Bottom-left corner
						"DEHT_BOTTOMMIDDLE" Middle bottom-side
						"DEHT_BOTTOMRIGHT" Bottom-right corner
						"DEHT_LEFTMIDDLE" Middle left-side
						"DEHT_RIGHTMIDDLE" Middle right-side

   ============================================================*/
{

	// We only show cursors for a subset of the hit-point codes.
	HCURSOR cursor = LoadCursor( NULL, IDC_ARROW );
	switch( hit )
	{
		case DEHT_TOPRIGHT:
			cursor = LoadCursor( NULL, IDC_SIZENESW );
		break;
		case DEHT_BOTTOMMIDDLE:
			cursor = LoadCursor( NULL, IDC_SIZENS );
		break;
		case DEHT_BOTTOMRIGHT:
			cursor = LoadCursor( NULL, IDC_SIZENWSE );
		break;
		case DEHT_BOTTOMLEFT:
			cursor = LoadCursor( NULL, IDC_SIZENESW );
		break;
		case DEHT_RIGHTMIDDLE:
			cursor = LoadCursor( NULL, IDC_SIZEWE );
		break;
	}

	return cursor;

}

int CDiagramEditor::GetHitCode( CPoint point )
/* ============================================================
	Function :		CDiagramEditor::GetHitCode
	Description :	Will return the hit-point value (defined in 
					DiagramEntity.h) of point.
	Access :		Public

	Return :		int				-	The hit-point define of 
										point. "DEHT_NONE" if none.
	Parameters :	CPoint point	-	The point to hit-test.
					
	Usage :			Virtual. Can be overridden in a derived 
					class to return other hit-point values. 
					Should normally not be called from code.
					The hit point can be one of the following:
						"DEHT_NONE" No hit-point
						"DEHT_BODY" Inside object body
						"DEHT_TOPLEFT" Top-left corner
						"DEHT_TOPMIDDLE" Middle top-side
						"DEHT_TOPRIGHT" Top-right corner
						"DEHT_BOTTOMLEFT" Bottom-left corner
						"DEHT_BOTTOMMIDDLE" Middle bottom-side
						"DEHT_BOTTOMRIGHT" Bottom-right corner
						"DEHT_LEFTMIDDLE" Middle left-side
						"DEHT_RIGHTMIDDLE" Middle right-side

   ============================================================*/
{

	CRect rect( 0, 0, GetVirtualSize().cx, GetVirtualSize().cy );

	int result = DEHT_NONE;

	if( rect.PtInRect( point ) )
		result = DEHT_BODY;

	CRect rectTest;

	// We return all selection marker points for aestethical 
	// reasons, even if we can't resize the background to 
	// the top and left.
	VirtualToScreen( point );
	rectTest = GetSelectionMarkerRect( DEHT_TOPLEFT );
	if( rectTest.PtInRect( point ) )
		result = DEHT_TOPLEFT;

	rectTest = GetSelectionMarkerRect( DEHT_TOPMIDDLE );
	if( rectTest.PtInRect( point ) )
		result = DEHT_TOPMIDDLE;

	rectTest = GetSelectionMarkerRect( DEHT_TOPRIGHT );
	if( rectTest.PtInRect( point ) )
		result = DEHT_TOPRIGHT;

	rectTest = GetSelectionMarkerRect( DEHT_BOTTOMLEFT );
	if( rectTest.PtInRect( point ) )
		result = DEHT_BOTTOMLEFT;

	rectTest = GetSelectionMarkerRect( DEHT_BOTTOMMIDDLE );
	if( rectTest.PtInRect( point ) )
		result = DEHT_BOTTOMMIDDLE;

	rectTest = GetSelectionMarkerRect( DEHT_BOTTOMRIGHT );
	if( rectTest.PtInRect( point ) )
		result = DEHT_BOTTOMRIGHT;

	rectTest = GetSelectionMarkerRect( DEHT_LEFTMIDDLE );
	if( rectTest.PtInRect( point ) )
		result = DEHT_LEFTMIDDLE;

	rectTest = GetSelectionMarkerRect( DEHT_RIGHTMIDDLE );
	if( rectTest.PtInRect( point ) )
		result = DEHT_RIGHTMIDDLE;

	return result;

}

void CDiagramEditor::InsideRestraints( double& x, double& y )
/* ============================================================
	Function :		CDiagramEditor::InsideRestraints
	Description :	Returns the max x and y that the selected 
					objects can move, with the desired x and y 
					as in-parameters.
	Access :		Protected

	Return :		void
	Parameters :	double& x	-	Desired x-movement
					double& y	-	Desired y-movement.
					
	Usage :			Internal function. Will not actually move 
					the objects, only calculate the maximum 
					possible movement.

   ============================================================*/
{
	if( m_restraint != RESTRAINT_NONE )
	{

		int count = 0;
		CDiagramEntity* obj;
		double minleft = 0xffffffff;
		double mintop = 0xffffffff;
		double maxright = 0;
		double maxbottom = 0;

		while( ( obj = m_objs->GetAt( count++ ) ) )
		{
			if( obj->IsSelected() )
			{

				// Correcting, depending on restraint mode.
				// Note that checks will have to be made for all 
				// coordinates against all sides, as the coordinates 
				// might not be normalized (as for a line, for example).

				double left = obj->GetLeft() + x;
				double top = obj->GetTop() + y;
				double right = obj->GetRight() + x;
				double bottom = obj->GetBottom() + y;

				minleft = min( minleft, left );
				minleft = min( minleft, right );
				mintop = min( mintop, top );
				mintop = min( mintop, bottom );

				maxright = max( maxright, left );
				maxright = max( maxright, right );
				maxbottom = max( maxbottom, top );
				maxbottom = max( maxbottom, bottom );

			}
		}

		double leftedge = 0;
		double rightedge = 0;
		double topedge = 0;
		double bottomedge = 0;

		if( m_restraint == RESTRAINT_VIRTUAL )
		{
			leftedge = 0;
			topedge = 0;
			rightedge = GetVirtualSize().cx;
			bottomedge = GetVirtualSize().cy;
		}
		else if( m_restraint == RESTRAINT_MARGIN )
		{
			leftedge = m_leftMargin;
			topedge = m_topMargin;
			rightedge = GetVirtualSize().cx - m_rightMargin;
			bottomedge = GetVirtualSize().cy - m_bottomMargin;
		}

		if( minleft < leftedge )
			x = x - ( minleft - leftedge );
		if( mintop < topedge )
			y = y - ( mintop - topedge );
		if( maxright > rightedge )
			x = rightedge - ( maxright - x );
		if( maxbottom > bottomedge )
			y = bottomedge - ( maxbottom - y );

	}
}

void CDiagramEditor::AdjustForRestraints( double& left, double& top, double& right, double& bottom )
/* ============================================================
	Function :		CDiagramEditor::AdjustForRestraints
	Description :	Adjust the rect represented by the in-
					params to the current constraints.
	Access :		Protected

	Return :		void
	Parameters :	double& left	-	Desired left position. 
										Contains the corrected 
										left position on return.
					double& top		-	Desired top position.
										Contains the corrected 
										top position on return.
					double& right	-	Desired right position.
										Contains the corrected 
										right position on return.
					double& bottom	-	Desired bottom position.
										Contains the corrected 
										bottom position on return.
					
	Usage :			Internal function. Will not resize the rect. 
					The coordinates need not be normalized.

   ============================================================*/
{

	// Saving the size
	double width = fabs( right - left );
	double height = fabs( bottom - top );

	// Correcting, depending on restraint mode.
	// Note that checks will have to be made for all 
	// coordinates against all sides, as the coordinates 
	// might not be normalized (as for a line, for example).
	if( m_restraint == RESTRAINT_VIRTUAL )
	{

		if( left < 0 )
		{
			left = 0;
			right = left + width;
		}
		if( top < 0 )
		{
			top = 0;
			bottom = top + height;
		}
		if( right < 0 )
		{
			right = 0;
			left = right + width;
		}
		if( bottom < 0 )
		{
			bottom = 0;
			top = bottom + height;
		}

		if( right > GetVirtualSize().cx )
		{
			right = GetVirtualSize().cx;
			left = right - width;
		}
		if( bottom > GetVirtualSize().cy )
		{
			bottom = GetVirtualSize().cy;
			top = bottom - height;
		}

		if( left > GetVirtualSize().cx )
		{
			left = GetVirtualSize().cx;
			right = left - width;
		}
		if( top > GetVirtualSize().cy )
		{
			top = GetVirtualSize().cy;
			bottom = top - height;
		}
	}
	else if( m_restraint == RESTRAINT_MARGIN )
	{
		if( left < m_leftMargin )
		{
			left = m_leftMargin;
			right = left + width;
		}
		if( top < m_topMargin )
		{
			top = m_topMargin;
			bottom = top + height;
		}
		if( right < m_leftMargin )
		{
			right = m_leftMargin;
			left = right + width;
		}
		if( bottom < m_topMargin )
		{
			bottom = m_topMargin;
			top = bottom + height;
		}

		if( right > GetVirtualSize().cx - m_rightMargin )
		{
			right = ( GetVirtualSize().cx - m_rightMargin );
			left = right - width;
		}
		if( bottom > GetVirtualSize().cy - m_bottomMargin )
		{
			bottom = ( GetVirtualSize().cy - m_bottomMargin );
			top = bottom - height;
		}
		if( left > GetVirtualSize().cx - m_rightMargin )
		{
			left = ( GetVirtualSize().cx - m_rightMargin );
			right = left - width;
		}
		if( top > GetVirtualSize().cy - m_bottomMargin )
		{
			top = ( GetVirtualSize().cy - m_bottomMargin );
			bottom = top - height;
		}
	}

}

void CDiagramEditor::AdjustForRestraints( double& xpos, double& ypos )
/* ============================================================
	Function :		CDiagramEditor::AdjustForRestraints
	Description :	Adjust the rect represented by the in-
					params to the current constraints.
	Access :		Protected

	Return :		void
	Parameters :	double& xpos	-	Desired x position. 
										Contains the corrected 
										x position on return.
					double& ypos	-	Desired y position. 
										Contains the corrected 
										y position on return.
					
	Usage :			Internal function. Will only correct 
					position parameters, not change any object.

   ============================================================*/
{

	if( m_restraint == RESTRAINT_VIRTUAL )
	{
		xpos = max( xpos, 0 );
		xpos = min( xpos, GetVirtualSize().cx );
		ypos = max( ypos, 0 );
		ypos = min( ypos, GetVirtualSize().cy );
	}
	else if( m_restraint == RESTRAINT_MARGIN )
	{
		xpos = max( xpos, m_leftMargin );
		xpos = min( xpos, GetVirtualSize().cx - m_rightMargin );
		ypos = max( ypos, m_topMargin );
		ypos = min( ypos, GetVirtualSize().cy - m_bottomMargin );
	}

}

CSize CDiagramEditor::GetContainingSize() const
/* ============================================================
	Function :		CDiagramEditor::GetContainingSize
	Description :	Return the minimum size enveloping all 
					objects.
	Access :		Protected

	Return :		CSize	-	Minimum size necessary to 
								contain all objects.
	Parameters :	none

	Usage :			Internal function. Calculates the minimum
					size necessary for all objects.

   ============================================================*/
{

	int count = 0;
	CDiagramEntity* obj;
	int maxx = 0;
	int maxy = 0;

	if( m_objs )
	{
		while( ( obj = m_objs->GetAt( count++ ) ) )
		{
			maxx = max( round( obj->GetRight() ), maxx );
			maxy = max( round( obj->GetBottom() ), maxy );
		}
	}

	return CSize( maxx, maxy );

}

/////////////////////////////////////////////////////////////////////////////
// CDiagramEditor scrolling

void CDiagramEditor::OnHScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar ) 
/* ============================================================
	Function :		CDiagramEditor::OnHScroll
	Description :	Handles the "WM_VSCROLL" message. Updates the 
					screen.
	Access :		Protected

	Return :		void
	Parameters :	UINT nSBCode			-	Type of scroll operation
					UINT nPos				-	New scroll position
					CScrollBar* pScrollBar	-	
					
	Usage :			Called from MFC. Do not call from code.

   ============================================================*/
{

	SCROLLINFO si;
	si.cbSize = sizeof( SCROLLINFO );
	si.fMask = SIF_POS | SIF_RANGE;
	GetScrollInfo( SB_HORZ, &si );
	switch( nSBCode )
	{
		case SB_LEFT:			// Scroll to far left.
			si.nPos = si.nMin;
			break;
		case SB_LINELEFT:		// Scroll left.
			si.nPos = max( si.nPos - 1, si.nMin );
			break;
		case SB_LINERIGHT:		// Scroll right.
			si.nPos = min( si.nPos + 1, si.nMax );
			break;
		case SB_PAGELEFT:		// Scroll one page left.
			si.nPos = max( si.nPos - static_cast< int >( si.nPage ), si.nMin );
			break;
		case SB_PAGERIGHT:		// Scroll one page right.
			si.nPos = min( si.nPos + static_cast< int >( si.nPage ), si.nMax );
			break;
		case SB_RIGHT:			// Scroll to far right.
			si.nPos = si.nMax;
			break;
		case SB_THUMBPOSITION:	// Scroll to absolute position. The current position is specified by the nPos parameter.
			si.nPos = nPos;
			break;
		case SB_THUMBTRACK:		//
			si.nPos = nPos;
			break;
	}

	SetHScroll( si.nPos );
//	SetScrollInfo( SB_HORZ, &si );
	RedrawWindow();
	CWnd::OnHScroll( nSBCode, nPos, pScrollBar );

}

void CDiagramEditor::OnVScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar ) 
/* ============================================================
	Function :		CDiagramEditor::OnVScroll
	Description :	Handles the "WM_VSCROLL" message. Updates the 
					screen.
	Access :		Protected

	Return :		void
	Parameters :	UINT nSBCode			-	Type of scroll 
												operation.
					UINT nPos				-	New scroll position.
					CScrollBar* pScrollBar	-	
					
	Usage :			Called from MFC. Do not call from code.

   ============================================================*/
{

	SCROLLINFO si;
	si.cbSize = sizeof( SCROLLINFO );
	si.fMask = SIF_POS | SIF_RANGE;
	GetScrollInfo( SB_VERT, &si );
	switch( nSBCode )
	{
		case SB_TOP:			// Scroll to far left.
			si.nPos = si.nMin;
			break;
		case SB_LINEUP:			// Scroll left.
			si.nPos = max( si.nPos - 1, si.nMin );
			break;
		case SB_LINEDOWN:		// Scroll right.
			si.nPos = min( si.nPos + 1, si.nMax );
			break;
		case SB_PAGEUP:			// Scroll one page left.
			si.nPos = max( si.nPos - static_cast< int >( si.nPage ), si.nMin );
			break;
		case SB_PAGEDOWN:		// Scroll one page right.
			si.nPos = min( si.nPos + static_cast< int >( si.nPage ), si.nMax );
			break;
		case SB_BOTTOM:			// Scroll to far right.
			si.nPos = si.nMax;
			break;
		case SB_THUMBPOSITION:	// Scroll to absolute position. The current position is specified by the nPos parameter.
			si.nPos = nPos;
			break;
		case SB_THUMBTRACK:		//
			si.nPos = nPos;
			break;
	}

	SetVScroll( si.nPos );

//	SetScrollInfo( SB_VERT, &si );
	RedrawWindow();

	CWnd::OnVScroll( nSBCode, nPos, pScrollBar );

}

int CDiagramEditor::HScroll( int scroll )
/* ============================================================
	Function :		CDiagramEditor::HScroll
	Description :	Scrolls the editor window scroll steps
					horisontally.
	Access :		Protected

	Return :		int			-	The number of steps actually 
									scrolled.
	Parameters :	int scroll	-	The number of steps to scroll.
					
	Usage :			Internal function

   ============================================================*/
{

	int retval = 0;

	if( m_hWnd )
	{
		CRect clientRect;
		GetClientRect( &clientRect );
		if(clientRect.Size().cx < GetVirtualSize().cx )	
		{
			int desiredpos = 0;

			SCROLLINFO si;
			si.cbSize = sizeof( SCROLLINFO );
			if( GetScrollInfo( SB_HORZ, &si ) )
			{
				desiredpos = si.nPos + scroll;
				si.nPos = desiredpos;

				SetHScroll( si.nPos );
//				SetScrollInfo( SB_HORZ, &si );
				GetScrollInfo( SB_HORZ, &si );
				retval = scroll - ( desiredpos - si.nPos );
				if( retval )
					RedrawWindow();
			}
		}
	}

	return retval;

}

int CDiagramEditor::VScroll( int scroll )
/* ============================================================
	Function :		CDiagramEditor::VScroll
	Description :	Scrolls the editor window scroll steps
					vertically.
	Access :		Protected

	Return :		int			-	The number of steps actually 
									scrolled.
	Parameters :	int scroll	-	The number of steps to scroll.
					
	Usage :			Internal function.

   ============================================================*/
{

	int retval = 0;

	if( m_hWnd )
	{
		CRect clientRect;
		GetClientRect( &clientRect );
		if(clientRect.Size().cy < GetVirtualSize().cy )
		{
			int desiredpos = 0;

			SCROLLINFO si;
			si.cbSize = sizeof( SCROLLINFO );
			if( GetScrollInfo( SB_VERT, &si ) )
			{
				desiredpos = si.nPos + scroll;
				si.nPos = desiredpos;

				SetVScroll( si.nPos );
//				SetScrollInfo( SB_VERT, &si );
				GetScrollInfo( SB_VERT, &si );
				retval = scroll - ( desiredpos - si.nPos );
				if( retval )
					RedrawWindow();
			}
		}
	}

	return retval;

}

CPoint CDiagramEditor::ScrollPoint( CPoint point )
/* ============================================================
	Function :		CDiagramEditor::ScrollPoint
	Description :	Scrolls the editor if point is outside the 
					window.
	Access :		Protected

	Return :		CPoint			-	The pixels scrolled 
										horisontally and 
										vertically.
	Parameters :	CPoint point	-	The position of the mouse 
										pointer.
					
	Usage :			Internal function.

   ============================================================*/
{

	CPoint out( 0, 0 );
	CRect clientRect;
	GetClientRect( &clientRect );

	if( point.x > clientRect.right )
		out.x = HScroll( 10 );

	if( point.x < 0 )
		out.x = HScroll( -10 );

	if( point.y > clientRect.bottom )
		out.y = VScroll( 10 );

	if( point.y < 0 )
		out.y = VScroll( -10 );

	return out;

}

void CDiagramEditor::SetupScrollbars()
/* ============================================================
	Function :		CDiagramEditor::SetupScrollbars
	Description :	Sets up/removes scrollbars depending on the 
					relation between the client- and virtual 
					rect.
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Internal function.

   ============================================================*/
{

	if( m_hWnd )
	{
		CRect rect;
		GetClientRect( rect );

		DWORD add = 0;
		DWORD remove = 0;

		if( round( static_cast< double >( GetVirtualSize().cx ) * GetZoom() ) <= rect.right )
		{
			if( GetStyle() & WS_HSCROLL )
				remove |= WS_HSCROLL;
		}
		else
		{
			if( !( GetStyle() & WS_HSCROLL ) )
				add |= WS_HSCROLL;
		}
		if( round( static_cast< double >( GetVirtualSize().cy ) * GetZoom() ) <= rect.bottom )
		{
			if( GetStyle() & WS_VSCROLL )
				remove |= WS_VSCROLL;
		}
		else
		{
			if( !( GetStyle() & WS_VSCROLL ) )
				add |= WS_VSCROLL;
		}

		SCROLLINFO si;
		si.cbSize = sizeof( SCROLLINFO );
		si.fMask = SIF_RANGE | SIF_PAGE;
		si.nMin = 0;
		int width = round( static_cast< double >( GetVirtualSize().cx ) * GetZoom() );
		if( width > rect.right )
		{
			si.nMax = width;
			si.nPage = rect.right;
		}
		else
		{
			si.nMax = 0;
			si.nPage = 0;
		}

		SetScrollInfo( SB_HORZ, &si );
		
		int height = round( static_cast< double >( GetVirtualSize().cy ) * GetZoom() );
		if( height > rect.bottom )
		{
			si.nMax = height;
			si.nPage = rect.bottom;
		}
		else
		{
			si.nMax = 0;
			si.nPage = 0;
		}

		SetScrollInfo( SB_VERT, &si );

		if( add || remove )
			ModifyStyle( remove, add, SWP_FRAMECHANGED );

	}

}

/////////////////////////////////////////////////////////////////////////////
// CDiagramEditor sizing

void CDiagramEditor::OnSize( UINT nType, int cx, int cy ) 
/* ============================================================
	Function :		CDiagramEditor::OnSize
	Description :	Handles the "WM_SIZE" message. Sets up/modifies 
					scrollbars as necessary.
	Access :		Protected

	Return :		void
	Parameters :	UINT nType	-	
					int cx		-	The new x size
					int cy		-	The new y size
					
	Usage :			Called from MFC. Do not call from code.

   ============================================================*/
{

	CWnd::OnSize( nType, cx, cy );
	SetupScrollbars();

}

/////////////////////////////////////////////////////////////////////////////
// CDiagramEditor coordinate handling

void CDiagramEditor::ScreenToVirtual( CRect& rect ) const
/* ============================================================
	Function :		CDiagramEditor::ScreenToVirtual
	Description :	Converts rect from screen- to virtual 
					coordinates.
	Access :		Public
					
	Return :		void
	Parameters :	CRect& rect	-	The rect to convert
					
	Usage :			Call to - for example - display coordinates,

   ============================================================*/
{

	// We have to normalize, add scroll bar positions and 
	// apply current zoom.

	rect.NormalizeRect();

	SCROLLINFO sih;
	SCROLLINFO siv;

	sih.cbSize = sizeof( SCROLLINFO );
	sih.fMask = SIF_POS;
	siv.cbSize = sizeof( SCROLLINFO );
	siv.fMask = SIF_POS;

	if( !::GetScrollInfo( m_hWnd, SB_HORZ, &sih ) )
		sih.nPos = 0;
	if( !::GetScrollInfo( m_hWnd, SB_VERT, &siv ) )
		siv.nPos = 0;

	rect.SetRect( round( static_cast< double >( rect.left	+ sih.nPos ) / GetZoom() ), 
				  round( static_cast< double >( rect.top	+ siv.nPos ) / GetZoom() ), 
				  round( static_cast< double >( rect.right	+ sih.nPos ) / GetZoom() ), 
				  round( static_cast< double >( rect.bottom	+ siv.nPos ) / GetZoom() ) );

}

void CDiagramEditor::ScreenToVirtual( CPoint& point ) const
/* ============================================================
	Function :		CDiagramEditor::ScreenToVirtual
	Description :	Converts point from screen- to virtual 
					coordinates.
	Access :		Public

	Return :		void
	Parameters :	CPoint& point	-	The point to convert.	
					
	Usage :			Call to - for example - display coordinates,

   ============================================================*/
{

	// Convert point to the virtual
	// coordinate system. We have to normalize, 
	// add scroll bar positions and apply current 
	// scale.

	SCROLLINFO sih;
	SCROLLINFO siv;

	sih.cbSize = sizeof( SCROLLINFO );
	sih.fMask = SIF_POS;
	siv.cbSize = sizeof( SCROLLINFO );
	siv.fMask = SIF_POS;

	if( !::GetScrollInfo( m_hWnd, SB_HORZ, &sih ) )
		sih.nPos = 0;
	if( !::GetScrollInfo( m_hWnd, SB_VERT, &siv ) )
		siv.nPos = 0;

	point.x = round( static_cast< double >( point.x + sih.nPos ) / GetZoom() );
	point.y = round( static_cast< double >( point.y + siv.nPos ) / GetZoom() );

}

void CDiagramEditor::ScreenToVirtual( CSize& size ) const
/* ============================================================
	Function :		CDiagramEditor::ScreenToVirtual
	Description :	Converts size from screen- to virtual 
					coordinates.
	Access :		Public

	Return :		void
	Parameters :	CSize& size	-	The size to convert.
					
	Usage :			Call to - for example - display coordinates,

   ============================================================*/
{

	// We have to deduct scroll bar positions 
	// and apply current zoom.


	SCROLLINFO sih;
	SCROLLINFO siv;

	sih.cbSize = sizeof( SCROLLINFO );
	sih.fMask = SIF_POS;
	siv.cbSize = sizeof( SCROLLINFO );
	siv.fMask = SIF_POS;

	if( !::GetScrollInfo( m_hWnd, SB_HORZ, &sih ) )
		sih.nPos = 0;
	if( !::GetScrollInfo( m_hWnd, SB_VERT, &siv ) )
		siv.nPos = 0;

	size.cx = round( static_cast< double >( size.cx + sih.nPos ) / GetZoom() );
	size.cy = round( static_cast< double >( size.cy + siv.nPos ) / GetZoom() );

}

void CDiagramEditor::VirtualToScreen( CRect& rect ) const
/* ============================================================
	Function :		CDiagramEditor::VirtualToScreen
	Description :	Converts rect from the virtual to the 
					screen coordinate system. 
	Access :		Public

	Return :		void
	Parameters :	CRect& rect	-	The rect to convert. Will be 
									normalized on return.
					
	Usage :			Call to - for example - display coordinates,

   ============================================================*/
{

	// We have to normalize, deduct scroll bar positions 
	// and apply current zoom.

	rect.NormalizeRect();

	SCROLLINFO sih;
	SCROLLINFO siv;

	sih.cbSize = sizeof( SCROLLINFO );
	sih.fMask = SIF_POS;
	siv.cbSize = sizeof( SCROLLINFO );
	siv.fMask = SIF_POS;

	if( !::GetScrollInfo( m_hWnd, SB_HORZ, &sih ) )
		sih.nPos = 0;
	if( !::GetScrollInfo( m_hWnd, SB_VERT, &siv ) )
		siv.nPos = 0;

	rect.SetRect( round( static_cast< double >( rect.left	) * GetZoom() - static_cast< double >( sih.nPos ) ), 
				  round( static_cast< double >( rect.top	) * GetZoom() - static_cast< double >( siv.nPos ) ), 
				  round( static_cast< double >( rect.right	) * GetZoom() - static_cast< double >( sih.nPos ) ), 
				  round( static_cast< double >( rect.bottom	) * GetZoom() - static_cast< double >( siv.nPos ) ) );

}

void CDiagramEditor::VirtualToScreen( CPoint& point ) const
/* ============================================================
	Function :		CDiagramEditor::VirtualToScreen
	Description :	Converts point from the virtual to the 
					screen coordinate system. 
	Access :		Public

	Return :		void
	Parameters :	CPoint& point	-	The point to convert. 
					
	Usage :			Call to - for example - display coordinates,

   ============================================================*/
{

	point.x = round( static_cast< double >( point.x ) * GetZoom() );
	point.y = round( static_cast< double >( point.y ) * GetZoom() );


}

int CDiagramEditor::SnapX( int coord ) const
/* ============================================================
	Function :		CDiagramEditor::SnapX
	Description :	Snaps coord vertically to the closest 
					grid point.
	Access :		Protected

	Return :		int			-	The resulting x-coordinate.
	Parameters :	int coord	-	The coordinate to snap
					
	Usage :			Internal function. Will snap even if snap 
					to grid is off.

   ============================================================*/
{

	double x = static_cast< double >( coord );
	double gridx = static_cast< double >( m_gridSize.cx );
	return round( x / gridx ) * m_gridSize.cx;

}

int CDiagramEditor::SnapY( int coord ) const
/* ============================================================
	Function :		CDiagramEditor::SnapY
	Description :	Snaps coord horisontally to the closest 
					grid point.
	Access :		Protected

	Return :		int			-	The resulting y-coordinate.
	Parameters :	int coord	-	The coordinate to snap
					
	Usage :			Internal function. Will snap even if snap 
					to grid is off.

   ============================================================*/
{

	double y = static_cast< double >( coord );
	double gridy = static_cast< double >( m_gridSize.cy );
	return round( y / gridy ) * m_gridSize.cy;

}

/////////////////////////////////////////////////////////////////////////////
// CDiagramEditor object manipulations

BOOL CDiagramEditor::IsAnyObjectSelected() const
/* ============================================================
	Function :		CDiagramEditor::IsAnyObjectSelected
	Description :	Returns "TRUE" if any object is selected.
	Access :		Public

	Return :		BOOL	-	"TRUE" if any object is selected.
	Parameters :	none

	Usage :			Call to check if any objects are selected.

   ============================================================*/
{

	BOOL res = FALSE;
	if( m_objs )
	{
		int count = 0;
		CDiagramEntity* obj;
		while( ( obj = m_objs->GetAt( count++ ) ) )
			if( obj->IsSelected() )
				res = TRUE;
	}

	return res;

}

int CDiagramEditor::GetSelectCount() const
/* ============================================================
	Function :		CDiagramEditor::GetSelectCount
	Description :	Returns the number of selected objects in 
					the data container.
	Access :		Public

	Return :		int	-	The number of selected objects.
	Parameters :	none

	Usage :			Call to get the number of selected objects.

   ============================================================*/
{

	int res = 0;

	if( m_objs )
		res = m_objs->GetSelectCount();

	return res;

}

CDiagramEntity* CDiagramEditor::GetSelectedObject() const
/* ============================================================
	Function :		CDiagramEditor::GetSelectedObject
	Description :	Returns the top selected object in the 
					container.
	Access :		Public

	Return :		CDiagramEntity*	-	The top selected object, 
										or "NULL" if none.
	Parameters :	none

	Usage :			Call to get the currently selected object. 
					Note that this function will return a single 
					object (top in the z-order) even if several 
					are selected.

   ============================================================*/
{

	int count = 0;
	CDiagramEntity* retval = NULL;
	CDiagramEntity* obj;

	if( m_objs )
		while( ( obj = m_objs->GetAt( count++ ) ) )
			if( obj->IsSelected() )
				retval = obj;

	return retval;

}

int CDiagramEditor::GetObjectCount() const
/* ============================================================
	Function :		CDiagramEditor::GetObjectCount
	Description :	Returns the number of objects in the container.
	Access :		Public

	Return :		int	-	The number of objects.
	Parameters :	none

	Usage :			Call to get the number of objects in the 
					data container.

   ============================================================*/
{

	int size = 0;
	if( m_objs )
		size = m_objs->GetSize();

	return size;

}

// 에디터 툴에서 새로 객체를 생성할 때만 호출 된다.
// 파일로 부터 생성할 때는 직접 Add(..)함수를 호출한다.
void CDiagramEditor::AddObject( CDiagramEntity* obj ) 
/* ============================================================
	Function :		CDiagramEditor::AddObject
	Description :	Adds "obj" to the data container.
	Access :		Public

	Return :		void
	Parameters :	CDiagramEntity* obj	-	The object to add.
					
	Usage :			Called to add objects to the container after 
					- for example - a load operation. Note that 
					the modified flag must be set manually if 
					this is desired (if implementing an Append 
					command, for example).
					This function can be overridden to trap
					object additions.

   ============================================================*/
{

	if( m_objs )
	{
		if( obj == NULL ) return;

		// 새로 객체가 추가되면 기존의 to bottom, to front 등의 레이어 재정렬!!
		Sort_ObjArray_by_Ctrl_Saving_Order( &(m_objs->m_objs) );

		for( int i = CTRL_COUNT-1; i>=0; i--)
		{
			if( strcmp( ((CDiagramEntity*)obj)->m_pProperty[ KIND_NAME ], ctrl_saving_order[i].type) == 0 )
				break;
		}

		if( i>0 && i < CTRL_COUNT )
		{
			for(int j= 0; j<(m_objs->m_objs).GetCount(); j++)
			{
				// 현재 i 번째 순서의 컨트롤을 저장하기 위해 컨트롤 종류로 걸러냄
				for( int k=i-1; k>=0; k--)
				{
					if( strcmp( ((CDiagramEntity*)m_objs->m_objs[j])->m_pProperty[ KIND_NAME ], ctrl_saving_order[k].type) == 0 )
					{
						// 배열의 j번째 객체 삽입!
						m_objs->Add( obj, false, j );
						return;
					}
				}
			}

			// 현재까지 생성된 객체 중에 없는 타입이라면 제일 끝에 저장함
			m_objs->Add( obj );
		}
		else
		{
			// i == 0 이면 제일 마지막에 저장할 타입(즉, 제일 상위 레이어 타입)이므로, 기존 처럼 제일 끝에 객체 추가!!
            m_objs->Add( obj );
		}
	}
}

// CObjArray 객체 정렬 함수!!
// 파일 저장 순서와는 반대로 저장
void CDiagramEditor::Sort_ObjArray_by_Ctrl_Saving_Order( CObArray* in_pObjs )
{
	if(in_pObjs == NULL ) return;

    int _Count = in_pObjs->GetCount();
	if( _Count <=0 ) return;

	CObArray tmp_ObjA;
	int i= 0, j=0;

	for( i = CTRL_COUNT-1; i>=0; i--)
	{
		for( j= 0; j<in_pObjs->GetCount(); j++)
		{
			// 현재 i 번째 순서의 컨트롤을 저장하기 위해 컨트롤 종류로 걸러냄
			if( strcmp( ((CDiagramEntity*)(in_pObjs->GetAt(j)))->m_pProperty[ KIND_NAME ], ctrl_saving_order[i].type) == 0 )
			{
                tmp_ObjA.Add( ((CDiagramEntity*)(in_pObjs->GetAt(j))) );                          
			}
		}
	}

	in_pObjs->RemoveAll();

	for( i = 0; i<tmp_ObjA.GetCount(); i++)
	{
        in_pObjs->Add( (CDiagramEntity*)(tmp_ObjA[i]) );
	}
};

CDiagramEntity* CDiagramEditor::GetObject( int index )  const
/* ============================================================
	Function :		CDiagramEditor::GetObject
	Description :	Gets the object at index "index".
	Access :		Public

	Return :		CDiagramEntity*	-	The object, "NULL" if not 
										found.
	Parameters :	int index		-	The index to get the 
										object from
					
	Usage :			Call to get a specific object from the 
					container. 
					The objects are the responsibility of the 
					container and should not be deleted.

   ============================================================*/
{

	CDiagramEntity* obj = NULL;
	if( m_objs )
		obj = m_objs->GetAt( index );

	return obj;

}

void CDiagramEditor::StartDrawingObject( CDiagramEntity* obj )
/* ============================================================
	Function :		CDiagramEditor::StartDrawingObject
	Description :	Starts drawing an object of type "obj".
	Access :		Public

	Return :		void
	Parameters :	CDiagramEntity* obj	-	Pointer to an object 
											of the desired type.
					
	Usage :			Should be called with a pointer to the 
					appropriate object type when the user 
					selects to draw an object. obj becomes 
					the property of the editor and should not 
					be deleted.

   ============================================================*/
{

	if(obj != NULL)
		obj->m_pFrame = m_pFrame;

	delete m_drawObj;
	m_drawObj = obj;

	if( obj )
	{
		m_drawing = TRUE;
		m_interactMode = MODE_DRAWING;
		::SetCursor( LoadCursor( NULL, IDC_CROSS ) );
	}
	else
	{
		m_drawing = FALSE;
		m_interactMode = MODE_NONE;
		::SetCursor( LoadCursor( NULL, IDC_ARROW ) );
	}

}

BOOL CDiagramEditor::IsDrawing() const
/* ============================================================
	Function :		CDiagramEditor::IsDrawing
	Description :	Returns if the user is drawing or not
	Access :		Public

	Return :		BOOL	-	"TRUE" if the user is currently 
								drawing
	Parameters :	none

	Usage :			Called for command enabling if multi-draw
					mode is enabled.

   ============================================================*/
{
	return m_drawObj && m_drawing;
}

void CDiagramEditor::UnselectAll()
/* ============================================================
	Function :		CDiagramEditor::UnselectAll
	Description :	Unselects all objects in the container.
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Call to unselect all objects. 
					Should not be callable if "GetObjectCount() 
					== 0" (there are no objects in the container).

   ============================================================*/
{

	if( m_objs )
	{
		int count = 0;
		CDiagramEntity* obj;
		while( ( obj = m_objs->GetAt( count++ ) ) )
			obj->Select( FALSE );
	}

}

void CDiagramEditor::SelectAll()
/* ============================================================
	Function :		CDiagramEditor::SelectAll
	Description :	Selects all objects.
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Call to select all objects. 
					Should not be callable if "GetObjectCount() 
					== 0" (there are no objects in the container).

   ============================================================*/
{

	if( m_objs )
	{
		int count = 0;
		CDiagramEntity* obj;
		while( ( obj = m_objs->GetAt( count++ ) ) )
			obj->Select( TRUE );
		RedrawWindow();
	}

}

void CDiagramEditor::DeleteAllSelected()
/* ============================================================
	Function :		CDiagramEditor::DeleteAllSelected
	Description :	Deletes all selected objects from the 
					container.
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Call to delete all selected objects from the 
					editor. Should not be callable if 
					"GetSelectCount() == 0" ( or "IsAnyObjectSelected() 
					== FALSE" )

   ============================================================*/
{

	if( m_objs )
	{
		m_objs->Snapshot();
		m_objs->RemoveAllSelected();
		RedrawWindow();
	}

}

void CDiagramEditor::DeleteAll()
/* ============================================================
	Function :		CDiagramEditor::DeleteAll
	Description :	Deletes all objects from the container.
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Call to delete all objects from the editor.

   ============================================================*/
{

	if( m_objs )
	{
		m_objs->Snapshot();
		m_objs->RemoveAll();
		RedrawWindow();
	}

}

/////////////////////////////////////////////////////////////////////////////
// CDiagramEditor layout

void CDiagramEditor::LeftAlignSelected()
/* ============================================================
	Function :		CDiagramEditor::LeftAlignSelected
	Description :	Aligns all selected objects to the left of
					the top selected object in the data container. 
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Call to align the left edge of all selected 
					objects.
					Should only be callable if "GetSelectCount() > 
					1", that is, more than one object is selected.

   ============================================================*/
{

	if( GetSelectCount() > 1 )
	{
		m_objs->Snapshot();
		CDiagramEntity* obj = GetSelectedObject();
		if( obj )
		{
			double left = obj->GetLeft();
			int count = 0;
			while( ( obj = m_objs->GetAt( count++ ) ) )
			{
				if( obj->IsSelected() )
				{
					double width = obj->GetRight() - obj->GetLeft();
					double right = left + width;
					obj->SetRect( left, obj->GetTop(), right, obj->GetBottom() );
				}
			}

		}
		SetModified( TRUE );
		RedrawWindow();
	}

}

void CDiagramEditor::RightAlignSelected()
/* ============================================================
	Function :		CDiagramEditor::RightAlignSelected
	Description :	Aligns all selected objects to the right of
					the top selected object in the data container. 
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Call to align the right edge of all selected 
					objects.
					Should only be callable if "GetSelectCount() > 
					1", that is, more than one object is selected.

   ============================================================*/
{

	if( GetSelectCount() > 1 )
	{
		m_objs->Snapshot();
		CDiagramEntity* obj = GetSelectedObject();
		if( obj )
		{
			double right = obj->GetRight();
			int count = 0;
			while( ( obj = m_objs->GetAt( count++ ) ) )
			{
				if( obj->IsSelected() )
				{
					double width = obj->GetRight() - obj->GetLeft();
					double left = right - width;
					obj->SetRect( left, obj->GetTop(), right, obj->GetBottom() );
				}
			}

		}
		SetModified( TRUE );
		RedrawWindow();
	}

}

void CDiagramEditor::TopAlignSelected()
/* ============================================================
	Function :		CDiagramEditor::TopAlignSelected
	Description :	Aligns all selected objects to the top of
					the top selected object in the data container. 
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Call to align the top of all selected 
					objects.
					Should only be callable if "GetSelectCount() > 
					1", that is, more than one object is selected.

   ============================================================*/
{

	if( GetSelectCount() > 1 )
	{
		m_objs->Snapshot();
		CDiagramEntity* obj = GetSelectedObject();
		if( obj )
		{
			double top = obj->GetTop();
			int count = 0;
			while( ( obj = m_objs->GetAt( count++ ) ) )
			{
				if( obj->IsSelected() )
				{
					double height = obj->GetBottom() - obj->GetTop();
					double bottom = top + height;
					obj->SetRect( obj->GetLeft(), top, obj->GetRight(), bottom );
				}
			}

		}
		SetModified( TRUE );
		RedrawWindow();
	}

}

void CDiagramEditor::BottomAlignSelected()
/* ============================================================
	Function :		CDiagramEditor::BottomAlignSelected
	Description :	Aligns all selected objects to the bottom of
					the top selected object in the data container. 
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Call to align the bottom of all selected 
					objects.
					Should only be callable if "GetSelectCount() > 
					1", that is, more than one object is selected.

   ============================================================*/
{

	if( GetSelectCount() > 1 )
	{
		m_objs->Snapshot();
		CDiagramEntity* obj = GetSelectedObject();
		if( obj )
		{
			double bottom = obj->GetBottom();
			int count = 0;
			while( ( obj = m_objs->GetAt( count++ ) ) )
			{
				if( obj->IsSelected() )
				{
					double height = obj->GetBottom() - obj->GetTop();
					double top = bottom - height;
					obj->SetRect( obj->GetLeft(), top, obj->GetRight(), bottom );
				}
			}

		}
		SetModified( TRUE );
		RedrawWindow();
	}

}

void CDiagramEditor::MakeSameSizeSelected()
/* ============================================================
	Function :		CDiagramEditor::MakeSameSizeSelected
	Description :	Makes all selected objects the same size as 
					the top selected object in the data container.
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Call to make all selected objects the same 
					size.
					Should only be called if "GetSelectCount() > 
					1", that is, more than one object is selected.

   ============================================================*/
{

	if( GetSelectCount() > 1 )
	{
		m_objs->Snapshot();
		CDiagramEntity* obj = GetSelectedObject();
		if( obj )
		{
			double width = obj->GetRight() - obj->GetLeft();
			double height = obj->GetBottom() - obj->GetTop();
			int count = 0;
			while( ( obj = m_objs->GetAt( count++ ) ) )
				if( obj->IsSelected() )
					obj->SetRect( obj->GetLeft(), obj->GetTop(), obj->GetLeft() + width, obj->GetTop() + height );

		}
		SetModified( TRUE );
		RedrawWindow();
	}

}

void CDiagramEditor::Duplicate()
/* ============================================================
	Function :		CDiagramEditor::Duplicate
	Description :	Duplicates the currently selected object.
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Call to put a copy of the selected object on 
					the screen.

   ============================================================*/
{
	if( GetSelectCount() == 1 )
	{
		CDiagramEntity* obj = GetSelectedObject();
		if( obj )
		{
			m_objs->Snapshot();
			m_objs->Duplicate( obj );
			obj->Select( FALSE );
			RedrawWindow();
		}
	}
}

void CDiagramEditor::Up()
/* ============================================================
	Function :		CDiagramEditor::Up
	Description :	Moves the currently selected object one 
					step up in the object z-order.
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Call to move the selected object one step 
					up in the z-order.
					This command should only be callable if
					"GetSelectCount()" returns 1, that is, if one 
					and only one object is selected.

   ============================================================*/
{

	if( GetSelectCount() == 1 )
	{
		CDiagramEntity* obj = GetSelectedObject();
		if( obj )
		{
			m_objs->Up( obj );
			RedrawWindow();
		}
	}
}

void CDiagramEditor::Down()
/* ============================================================
	Function :		CDiagramEditor::Down
	Description :	Moves the currently selected object one 
					step down in the object z-order.
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Call to move the selected object one step 
					down in the z-order.
					This command should only be callable if
					"GetSelectCount()" returns 1, that is, if one 
					and only one object is selected.

   ============================================================*/
{

	if( GetSelectCount() == 1 )
	{
		CDiagramEntity* obj = GetSelectedObject();
		if( obj )
		{
			m_objs->Down( obj );
			RedrawWindow();
		}
	}
}

void CDiagramEditor::Front()
/* ============================================================
	Function :		CDiagramEditor::Front
	Description :	Moves the selected object to the front of 
					all other objects.
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Call to move the selected object to the 
					top of the z-order. 
					This command should only be callable if
					"GetSelectCount()" returns 1, that is, if one 
					and only one object is selected.

   ============================================================*/
{

	if( GetSelectCount() == 1 )
	{
		CDiagramEntity* obj = GetSelectedObject();
		if( obj )
		{
			m_objs->Front( obj );
			RedrawWindow();
		}
	}
}

void CDiagramEditor::Bottom()
/* ============================================================
	Function :		CDiagramEditor::Bottom
	Description :	Moves the selected object to the bottom of 
					all objects.
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Call to move the selected object to the 
					bottom of the z-order. 
					This command should only be callable if
					"GetSelectCount()" returns 1, that is, if one 
					and only one object is selected.

   ============================================================*/
{

	if( GetSelectCount() == 1 )
	{
		CDiagramEntity* obj = GetSelectedObject();
		if( obj )
		{
			m_objs->Bottom( obj );
			RedrawWindow();
		}
	}
}

void CDiagramEditor::ShowProperties()
/* ============================================================
	Function :		CDiagramEditor::ShowProperties
	Description :	Shows the property dialog for the one and 
					only selected object in the data container.
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Call to display a property dialog for the 
					selected object. This command should 
					normally only be callable if "GetSelectCount()" 
					returns 1, that is, if one and only one object 
					is selected.

   ============================================================*/
{

	if( GetSelectCount() == 1 )
	{ 
		CDiagramEntity* obj = GetSelectedObject();
		if( obj )
			obj->ShowProperties( this );
	}
}

void CDiagramEditor::RemoveUnselectedPropertyDialogs()
/* ============================================================
	Function :		CDiagramEditor::RemoveUnselectedPropertyDialogs
	Description :	Removes all property dialogs for unselected 
					objects.
	Access :		Private

	Return :		void
	Parameters :	none

	Usage :			Internal function. Call to remove all 
					property dialogs for non-selected objects 
					from screen.

   ============================================================*/
{

	if( m_objs )
	{
		int count = 0;
		CDiagramEntity* obj;
		while( ( obj = m_objs->GetAt( count++ ) ) )
			if( !obj->IsSelected() )
				obj->ShowProperties( this, FALSE );
	}

}

void CDiagramEditor::ShowPopup( CPoint point ) 
/* ============================================================
	Function :		CDiagramEditor::ShowPopup
	Description :	Shows a popup menu in response to a right-
					click if no object is selected.
	Access :		Public

	Return :		void
	Parameters :	CPoint point	-	The point to track the 
										menu from.
					
	Usage :			Internal function. Call to show the editor 
					popup menu.

   ============================================================*/
{

	if( !m_popupMenu )
		m_popupMenu = new CDiagramMenu;

	if( m_popupMenu )
	{
		CMenu* menu = m_popupMenu->GetPopupMenu( this );
		if( menu )
			menu->TrackPopupMenu( TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this );
	}

}

/////////////////////////////////////////////////////////////////////////////
// CDiagramEditor copy/paste/undo

void CDiagramEditor::OnEditCut()
/* ============================================================
	Function :		CDiagramEditor::OnEditCut
	Description :	Command handler for the MFC standard 
					"ID_EDIT_CUT" command.
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC. Call "Cut" from code instead.

   ============================================================*/
{

	Cut();

}

void CDiagramEditor::OnEditCopy()
/* ============================================================
	Function :		CDiagramEditor::OnEditCopy
	Description :	Command handler for the MFC standard 
					"ID_EDIT_COPY" command.
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC. Call "Copy" from code 
					instead.

   ============================================================*/
{

	Copy();

}

void CDiagramEditor::OnEditPaste()
/* ============================================================
	Function :		CDiagramEditor::OnEditPaste
	Description :	Command handler for the MFC standard 
					"ID_EDIT_PASTE" command.
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC. Call "Paste" from code 
					instead.

   ============================================================*/
{

	Paste();

}

void CDiagramEditor::OnEditGroup()
/* ============================================================
	Function :		CDiagramEditor::OnEditGroup
	Description :	Handler for the "ID_EDIT_GROUP" command
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Groups the currently selected objects. 
					Grouped objects can be moved as a 
					single entity. Technically, when one object 
					in a group is selected, all other objects 
					are also selected automatically.

   ============================================================*/
{

	Group();

}

void CDiagramEditor::OnEditUngroup()
/* ============================================================
	Function :		CDiagramEditor::OnEditUngroup
	Description :	Handler for the "ID_EDIT_UNGROUP" command
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Ungroups the currently selected objects.
					Grouped objects can be moved as a 
					single entity. Technically, when one object 
					in a group is selected, all other objects 
					are also selected automatically.

   ============================================================*/
{

	Ungroup();

}

void CDiagramEditor::Cut()
/* ============================================================
	Function :		CDiagramEditor::Cut
	Description :	Cut the currently selected items to the 
					internal "CDiagramEntityContainer" clipboard.
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Call to delete and place the currently 
					selected objects to the 'clipboard'.

   ============================================================*/
{

	if( m_objs )
	{
		m_objs->Snapshot();
		m_objs->CopyAllSelected();
		DeleteAllSelected();
	}

}

void CDiagramEditor::Copy()
/* ============================================================
	Function :		CDiagramEditor::Copy
	Description :	Copy the currently selected items to the 
					internal "CDiagramEntityContainer" clipboard.
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Call to copy the selected objects to the 
					'clipboard'.

   ============================================================*/
{

	if( m_objs )
	{
		m_objs->Snapshot();
		m_objs->CopyAllSelected();
	}

}

void CDiagramEditor::Paste()
/* ============================================================
	Function :		CDiagramEditor::Paste
	Description :	Paste copied or cut objects to the screen.
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Call to paste the contents of the clipboard 
					to the screen.

   ============================================================*/
{

	// Removes the current selection and pastes the contents
	// of the data paste-array.
	if( m_objs )
	{
		SetRedraw( FALSE );
		m_objs->Snapshot();
		UnselectAll();
		m_objs->Paste();
		SetRedraw( TRUE );
		RedrawWindow();
	}

}

void CDiagramEditor::Undo()
/* ============================================================
	Function :		CDiagramEditor::Undo
	Description :	Undo the last operation.
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Call to restore the objects to the last 
					snapshot.

   ============================================================*/
{

	if( m_objs )
	{
		m_objs->Undo();
		RedrawWindow();
	}

}

void CDiagramEditor::Group()
/* ============================================================
	Function :		CDiagramEditor::OnEditGroup
	Description :	Groups the currently selected objects.
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Call to group the currently selected 
					objects. Grouped objects can be moved as a 
					single entity. Technically, when one object 
					in a group is selected, all other objects 
					are also selected automatically.

   ============================================================*/
{

	if( m_objs )
	{
		SetRedraw( FALSE );
		m_objs->Snapshot();
		m_objs->Group();
		SetRedraw( TRUE );
		RedrawWindow();
	}

}

void CDiagramEditor::Ungroup()
/* ============================================================
	Function :		CDiagramEditor::OnEditUngroup
	Description :	Ungroups the currently selected objects.
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Call to ungroup the currently selected 
					objects. Grouped objects can be moved as a 
					single entity. Technically, when one object 
					in a group is selected, all other objects 
					are also selected automatically.

   ============================================================*/
{

	if( m_objs )
	{
		SetRedraw( FALSE );
		m_objs->Snapshot();
		m_objs->Ungroup();
		SetRedraw( TRUE );
		RedrawWindow();
	}

}

void CDiagramEditor::UpdateCut( CCmdUI* pCmdUI ) const
/* ============================================================
	Function :		CDiagramEditor::UpdateCut
	Description :	Command enabling for a Cut command UI-
					element.
	Access :		Public

	Return :		void
	Parameters :	CCmdUI* pCmdUI	-	Command element to 
										update
					
	Usage :			Can be called from a doc/view command update 
					function

   ============================================================*/
{

	// We can only cut if there is something selected
	pCmdUI->Enable( IsAnyObjectSelected() );

}

void CDiagramEditor::UpdateCopy( CCmdUI* pCmdUI ) const
/* ============================================================
	Function :		CDiagramEditor::UpdateCopy
	Description :	Command enabling for a Copy command UI-
					element.
	Access :		Public

	Return :		void
	Parameters :	CCmdUI* pCmdUI	-	Command element to 
										update
					
	Usage :			Can be called from a doc/view command update 
					function

   ============================================================*/
{

	pCmdUI->Enable( IsAnyObjectSelected() );

}

void CDiagramEditor::UpdatePaste( CCmdUI* pCmdUI ) const
/* ============================================================
	Function :		CDiagramEditor::UpdatePaste
	Description :	Command enabling for a Paste command UI-
					element.
	Access :		Public

	Return :		void
	Parameters :	CCmdUI* pCmdUI	-	Command element to 
										update
					
	Usage :			Can be called from a doc/view command update 
					function

   ============================================================*/
{

	if( m_objs )
		pCmdUI->Enable( m_objs->ObjectsInPaste() );

}

void CDiagramEditor::UpdateUndo( CCmdUI* pCmdUI ) const
/* ============================================================
	Function :		CDiagramEditor::UpdateUndo
	Description :	Command enabling for an Undo command UI-
					element.
	Access :		Public

	Return :		void
	Parameters :	CCmdUI* pCmdUI	-	Command element to 
										update
					
	Usage :			Can be called from a doc/view command update 
					function

   ============================================================*/
{

	if( m_objs )
		pCmdUI->Enable( m_objs->IsUndoPossible() );

}

void CDiagramEditor::UpdateGroup( CCmdUI* pCmdUI ) const
/* ============================================================
	Function :		CDiagramEditor::UpdateGroup
	Description :	Command enabling for an Group command UI-
					element.
	Access :		Public

	Return :		void
	Parameters :	CCmdUI* pCmdUI	-	Command element to 
										update
					
	Usage :			Can be called from a doc/view command update 
					function

   ============================================================*/
{

	if( m_objs )
		pCmdUI->Enable( GetSelectCount() > 1 );

}

void CDiagramEditor::UpdateUngroup( CCmdUI* pCmdUI ) const
/* ============================================================
	Function :		CDiagramEditor::UpdateUngroup
	Description :	Command enabling for an Ungroup command UI-
					element.
	Access :		Public

	Return :		void
	Parameters :	CCmdUI* pCmdUI	-	Command element to 
										update
					
	Usage :			Can be called from a doc/view command update 
					function

   ============================================================*/
{

	if( m_objs )
		pCmdUI->Enable( GetSelectCount() > 1 );

}

/////////////////////////////////////////////////////////////////////////////
// CDiagramEditor saving

void CDiagramEditor::Save( CStringArray& stra )
/* ============================================================
	Function :		CDiagramEditor::Save
	Description :	Saves a string representation of the 
					container (normally the virtual size) and 
					all objects to "stra".
	Access :		Public

	Return :		void
	Parameters :	CStringArray& stra	-	The array to fill
					
	Usage :			Call to save the data of the editor to a 
					"CStringArray". Virtual. Can be overridden in 
					a derived class to add non-container data 
					before and after the objects

   ============================================================*/
{

	if( m_objs )
	{
		stra.Add( m_objs->GetString() );
		SaveObjects( stra );
		SetModified( FALSE );
	}

}

BOOL CDiagramEditor::FromString( const CString& str )
/* ============================================================
	Function :		CDiagramEditor::FromString
	Description :	Sets the virtual size from a string 
					representation of the paper.
	Access :		Public

	Return :		BOOL				-	"TRUE" if "str" is a 
											representation of a 
											'paper'.
	Parameters :	const CString& str	-	String representation.
					
	Usage :			Call to set the size of the virtual paper 
					from a string.

   ============================================================*/
{
	BOOL result = FALSE;
	if( m_objs )
		result = m_objs->FromString( str );

	return result;

}


void CDiagramEditor::SaveObjects( CStringArray& stra )
/* ============================================================
	Function :		CDiagramEditor::SaveObjects
	Description :	Saves a string representation of the 
					current objects to "stra", one object in 
					each string.
	Access :		Public

	Return :		void
	Parameters :	CStringArray& stra	-	The array to fill
					
	Usage :			Virtual. Can be overridden in a derived 
					class to add more per-object information to 
					the save array.

   ============================================================*/
{

	if( m_objs )
	{
		int count = 0;
		CDiagramEntity* obj;
		while( ( obj = m_objs->GetAt( count++ ) ) )
			stra.Add( obj->GetString() );
	}

}

/////////////////////////////////////////////////////////////////////////////
// CDiagramEditor command handling

void CDiagramEditor::OnObjectCommand( UINT nID )
/* ============================================================
	Function :		CDiagramEditor::OnObjectCommand
	Description :	Called from "WM_COMMAND" messages in the 
					range "CMD_START" to "CMD_END" inclusive 
					(defined in DiagramEntity.h). Those are 
					messages that will be passed on to all 
					selected objects.
	Access :		Protected

	Return :		void
	Parameters :	UINT nID	-	The command to send.
					
	Usage :			Called from MFC. Do not call from code.

   ============================================================*/
{

	if( m_objs )
	{
		m_objs->Snapshot();
		m_objs->SendMessageToObjects( nID, TRUE, NULL, static_cast< CWnd* >( this ) );
		RedrawWindow();
	}

}

int CDiagramEditor::GetInteractMode() const
/* ============================================================
	Function :		CDiagramEditor::GetInteractMode
	Description :	Get the interact mode.
	Access :		Protected

	Return :		int		-	Current interact mode
	Parameters :	none

	Usage :			The interact mode can be one of the 
					following:
						"MODE_NONE" No mode
						"MODE_RUBBERBANDING" User is selecting
						"MODE_MOVING" User is moving object(s)
						"MODE_RESIZING" User is resizing object
						"MODE_DRAWING" User is drawing object
						"MODE_BGRESIZING" User is resizing the virtual paper

   ============================================================*/
{

	return m_interactMode;

}

void CDiagramEditor::SetInteractMode( int interactMode, int subMode )
/* ============================================================
	Function :		CDiagramEditor::SetInteractMode
	Description :	Sets the current mode of the editor
	Access :		Protected

	Return :		void
	Parameters :	int interactMode	-	The mode to set
					int subMode			-	The point of the 
											selected object, if 
											appropriate.
					
	Usage :			Call to set the interact mode of the 
					editor. The interact mode can be one of 
					the following:
						"MODE_NONE" No mode
						"MODE_RUBBERBANDING" User is selecting
						"MODE_MOVING" User is moving object(s)
						"MODE_RESIZING" User is resizing object
						"MODE_DRAWING" User is drawing object
						"MODE_BGRESIZING" User is resizing the virtual paper
					The submode, relevant when the mode is 
					MODE_RESIZING or MODE_BGRESIZING, can be 
					one of the following:
						"DEHT_NONE" No hit
						"DEHT_BODY" Object body
						"DEHT_TOPLEFT" Top-left corner
						"DEHT_TOPMIDDLE" Top-side
						"DEHT_TOPRIGHT" Top-right corner
						"DEHT_BOTTOMLEFT" Bottom left corner
						"DEHT_BOTTOMMIDDLE" Bottom-side
						"DEHT_BOTTOMRIGHT" Bottom-right corner
						"DEHT_LEFTMIDDLE" Left side
						"DEHT_RIGHTMIDDLE" Right side
					and indicates the point where the mouse is 
					as regards the currently selected object 
					(or the background).

   ============================================================*/
{

	m_interactMode = interactMode;
	m_subMode = subMode;

}

CDiagramEntity* CDiagramEditor::GetDrawingObject()
/* ============================================================
	Function :		CDiagramEditor::GetDrawingObject
	Description :	Gets the object the user will draw.
	Access :		Protected

	Return :		CDiagramEntity*	-	Object
	Parameters :	none

	Usage :			Call to get the object that will be drawn 
					when the user clicks the 'paper'.

   ============================================================*/
{

	return m_drawObj;

}

COLORREF CDiagramEditor::GetBackgroundColor() const
/* ============================================================
	Function :		CDiagramEditor::GetBackgroundColor
	Description :	Accessor for the background color
	Access :		Public

	Return :		COLORREF	-	Current background color
	Parameters :	none

	Usage :			Call to get the background color

   ============================================================*/
{

	return m_bkgndCol;

}

/////////////////////////////////////////////////////////////////////////////
// CDiagramEditor zoom to fit functions

void CDiagramEditor::ZoomToFitScreen()
/* ============================================================
	Function :		CDiagramEditor::ZoomToFitScreen
	Description :	Zooms and scrolls so that all of the 
					current diagram is visible on screen.
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Call to make the complete diagram visible.

   ============================================================*/
{

	SetRedraw( FALSE );
	CRect rect;
	GetClientRect( rect );
	CPoint start = GetDiagramEntityContainer()->GetStartPoint();
	ZoomToFit( start, CSize( rect.Width(), rect.Height() ) );
	SetRedraw( TRUE );
	RedrawWindow();

}

BOOL CDiagramEditor::ZoomToFit( CPoint start, CSize size )
/* ============================================================
	Function :		CDiagramEditor::ZoomToFit
	Description :	Zooms the diagram to the size "size" and 
					sets the scrollbar positions at "start".
	Access :		Public

	Return :		BOOL			-	"TRUE" if any zoom (if
										that is the case, the 
										screen should be redrawn.
	Parameters :	CPoint start	-	Starting position of the 
										diagram, non-zoomed.
					CSize size		-	Size the diagram should 
										be zoomed to.
					
	Usage :			Call to zoom the diagram to a specific size.

   ============================================================*/
{

	BOOL result = FALSE;

	if( ZoomToFit( size ) )
	{

		// Set scrollbar positions
		SCROLLINFO si;
		si.cbSize = sizeof( SCROLLINFO );
		si.fMask = SIF_POS;
		if( GetScrollInfo( SB_HORZ, &si ) )
		{
			si.nPos = round( ( start.x - GetMarkerSize().cx ) * GetZoom() );
			SetHScroll( si.nPos );

			si.nPos = round( ( start.y - GetMarkerSize().cy ) * GetZoom() );
			SetVScroll( si.nPos );

		}
		result = TRUE;
	}

	return result;

}

BOOL CDiagramEditor::ZoomToFit( CSize size )
/* ============================================================
	Function :		CDiagramEditor::ZoomToFit
	Description :	Zooms the diagram to the size "size".
	Access :		Public

	Return :		BOOL		-	"TRUE" if zoomed. The screen
									should be redrawn if that is 
									the case.
	Parameters :	CSize size	-	Size to zoom to.
					
	Usage :			Call to zoom the diagram to a specific size.

   ============================================================*/
{

	BOOL result = FALSE;
	CSize objects = GetDiagramEntityContainer()->GetTotalSize();

	if( objects.cx && objects.cy )
	{
		// We add a little margin
		objects.cx += GetMarkerSize().cx * 2;
		objects.cy += GetMarkerSize().cy * 2;

		// Calculate new zoom
		double zoomx = static_cast< double >( size.cx ) / static_cast< double >( objects.cx );
		double zoomy = static_cast< double >( size.cy ) / static_cast< double >( objects.cy );

		SetZoom( min( zoomx, zoomy ) );
		result = TRUE;

	}
	
	return result;

}

/////////////////////////////////////////////////////////////////////////////
// CDiagramEditor mouse wheel handling

BOOL CDiagramEditor::OnMouseWheel( UINT nFlags, short zDelta, CPoint pt )
/* ============================================================
	Function :		CDiagramEditor::OnMouseWheel
	Description :	Handles the "WM_MOUSEWHEEL"-message.
	Access :		Protected

	Return :		BOOL			-	From default
	Parameters :	UINT nFlags		-	Not used
					short zDelta	-	Delta (notches * "WHEEL_DELTA")
					CPoint pt		-	Mouse position
					
	Usage :			Called from MFC. Scrolls the vertically.

   ============================================================*/
{

	if( GetScrollWheelMode() == WHEEL_SCROLL )
	{
		SCROLLINFO si;
		si.cbSize = sizeof( SCROLLINFO );
		si.fMask = SIF_POS | SIF_RANGE;
		static int mouseDelta;

		mouseDelta += zDelta;
		int increment = ( mouseDelta / WHEEL_DELTA );
		if( GetScrollInfo( SB_VERT, &si ) )
		{
			if( si.nMax )
			{
				si.nPos -= increment;
				mouseDelta -= increment * WHEEL_DELTA;
				SetVScroll( si.nPos );
//				SetScrollInfo( SB_VERT, &si, TRUE );
				RedrawWindow();
			}
		}
	}
	else if( GetScrollWheelMode() == WHEEL_ZOOM )
	{
		if( zDelta < 0 )
			SetZoom( GetZoom() + GetZoomFactor() );
		else
			SetZoom( GetZoom() - GetZoomFactor() );
	}

	return CWnd::OnMouseWheel( nFlags, zDelta, pt );

}

/////////////////////////////////////////////////////////////////////////////
// CDiagramEditor panning

void CDiagramEditor::OnMButtonDown( UINT nFlags, CPoint point ) 
/* ============================================================
	Function :		CDiagramEditor::OnMButtonDown
	Description :	Handler for the "WM_MBUTTONDOWN"-message
	Access :		Protected

	Return :		void
	Parameters :	UINT nFlags		-	Not used
					CPoint point	-	Current mouse position
					
	Usage :			Called from MFC. Don't call from code. 
					We start panning.

   ============================================================*/
{

	if( !GetPanning() )
	{
		SCROLLINFO si;
		if( GetScrollInfo( SB_HORZ, &si ) ||
			GetScrollInfo( SB_VERT, &si ) )
		{
			SetPanningOrigin( point );
			SetPanning( TRUE );
		}
	}
	else
	{
		SetPanning( FALSE );
	}

	CWnd::OnMButtonDown( nFlags, point );
	RedrawWindow();

}

void CDiagramEditor::OnTimer( UINT nIDEvent )
/* ============================================================
	Function :		CDiagramEditor::OnTimer
	Description :	Handler for the "WM_TIMER"-message
	Access :		Protected

	Return :		void
	Parameters :	UINT nIDEvent	-	Current timer
					
	Usage :			Called from MFC. We pan if we are in 
					panning mode.

   ============================================================*/
{

	if( nIDEvent == m_panningTimer )
	{

		KillTimer( m_panningTimer );

		const MSG* msg = GetCurrentMessage();
		CPoint test = GetPanningOrigin();
		CPoint point( msg->pt );
		ScreenToClient( &point );

		int diffx = ( point.x - test.x ) / 16;
		int diffy = ( point.y - test.y ) / 16;

		SCROLLINFO sih;
		sih.cbSize = sizeof( SCROLLINFO );
		sih.fMask = SIF_POS;
		sih.nPos = 0;
		SCROLLINFO siv;
		siv.cbSize = sizeof( SCROLLINFO );
		siv.fMask = SIF_POS;
		siv.nPos = 0;

		GetScrollInfo( SB_HORZ, &sih );
		GetScrollInfo( SB_VERT, &siv );

		sih.nPos += diffx;
		siv.nPos += diffy;

		SetHScroll( sih.nPos );
		SetVScroll( siv.nPos );
//		SetScrollInfo( SB_HORZ, &sih );
//		SetScrollInfo( SB_VERT, &siv );
		RedrawWindow();

		m_panningTimer = SetTimer( m_panningTimer, 10, NULL );

	}

}

void CDiagramEditor::OnKillFocus( CWnd* pNewWnd )
/* ============================================================
	Function :		CDiagramEditor::OnKillFocus
	Description :	Handler for the "WM_KILLFOCUS"-message
	Access :		Protected

	Return :		void
	Parameters :	CWnd* pNewWnd	-	Window getting the focus
					
	Usage :			Called from MFC. We kill the panning

   ============================================================*/
{

	if( GetPanning() )
		SetPanning( FALSE );

	CWnd::OnKillFocus( pNewWnd );

}

BOOL CDiagramEditor::GetPanning() const
/* ============================================================
	Function :		CDiagramEditor::GetPanning
	Description :	Accessor for the panning flag.
	Access :		Public

	Return :		BOOL	-	"TRUE" if we are currently 
								panning.
	Parameters :	none

	Usage :			Call to see if we are panning

   ============================================================*/
{

	return m_panning;

}

CPoint CDiagramEditor::GetPanningOrigin() const
/* ============================================================
	Function :		CDiagramEditor::GetPanningOrigin
	Description :	Accessor for the panning origin.
	Access :		Public

	Return :		CPoint	-	Origin for panning.
	Parameters :	none

	Usage :			Call to get the panning origin. The panning 
					origin is the point where the user clicked 
					the middle mouse button.

   ============================================================*/
{

	return m_panOrigin;

}

void CDiagramEditor::SetPanning( BOOL panning )
/* ============================================================
	Function :		CDiagramEditor::SetPanning
	Description :	Accessor for the panning flag
	Access :		Public

	Return :		void
	Parameters :	BOOL panning	-	"TRUE" if we should 
										start panning.
					
	Usage :			Call to start or stop panning.

   ============================================================*/
{

	if( m_panning && panning == FALSE )
		KillTimer( m_panningTimer );

	m_panning = panning;

	if( m_panning )
		m_panningTimer = SetTimer( m_panningTimer, 10, NULL );

}

void CDiagramEditor::SetPanningOrigin( CPoint point )
/* ============================================================
	Function :		CDiagramEditor::SetPanningOrigin
	Description :	Sets the panning origin.
	Access :		Public

	Return :		void
	Parameters :	CPoint point	-	The origin for the 
										panning.
					
	Usage :			Call to set the origin when starting to 
					pan the screen. The panning origin is the
					point where the user clicked the middle 
					mouse button.

   ============================================================*/
{

	m_panOrigin = point;

}

void CDiagramEditor::DrawPanning( CDC* dc ) const
/* ============================================================
	Function :		CDiagramEditor::DrawPanning
	Description :	Draws the panning origin marker.
	Access :		Public

	Return :		void
	Parameters :	CDC* dc	-	"CDC" to draw to
					
	Usage :			Call to draw the panning origin marker. You
					can override this to draw a different 
					origin marker for the pan.

   ============================================================*/
{

	CDiagramEditor* const local = const_cast< CDiagramEditor* const >( this );

	SCROLLINFO sih;
	sih.cbSize = sizeof( SCROLLINFO );
	sih.fMask = SIF_POS;
	SCROLLINFO siv;
	siv.cbSize = sizeof( SCROLLINFO );
	siv.fMask = SIF_POS;
	if( !local->GetScrollInfo( SB_HORZ, &sih ) )
		sih.nPos = 0;
	if( !local->GetScrollInfo( SB_VERT, &siv ) )
		siv.nPos = 0;

	dc->SelectStockObject( WHITE_BRUSH );
	CPen pen;
	pen.CreatePen( PS_SOLID, 0, RGB( 128, 128, 128 ) );

	dc->SelectObject( &pen );
	CPoint	pt = GetPanningOrigin();
	CRect	rect( pt.x - 16 + sih.nPos, pt.y - 16 + siv.nPos, pt.x + 16 + sih.nPos, pt.y + 16 + siv.nPos);
	dc->Ellipse( rect );

	rect.InflateRect( -12, -12 );
	dc->SelectStockObject( LTGRAY_BRUSH );
	dc->Ellipse( rect );

	dc->SelectStockObject( BLACK_PEN );

}

void CDiagramEditor::MoveObject( CDiagramEntity* obj, const CRect& rect )
/* ============================================================
	Function :		CDiagramEditor::MoveObject
	Description :	Moves an object to "rect"
	Access :		Protected

	Return :		void
	Parameters :	CDiagramEntity* obj	-	Object to move
					const CRect& rect	-	New position
					
	Usage :			This function can be overridden to trap
					object movement.

   ============================================================*/
{

	obj->SetRect( rect );

}

HCURSOR CDiagramEditor::GetCursor()
/* ============================================================
	Function :		CDiagramEditor::GetCursor
	Description :	Gets a handle to the cursor appropriate 
					depending on mode, position etc.
	Access :		Protected

	Return :		HCURSOR	-	Appropriate cursor
	Parameters :	none

	Usage :			Call to get a cursor to display depending on 
					the current context.

   ============================================================*/
{

	HCURSOR result = NULL;

	if( m_panning )
	{
		const MSG* msg = GetCurrentMessage();
		CPoint test = GetPanningOrigin();
		CPoint point( msg->pt );
		ScreenToClient( &point );

		if( point.x > test.x + 16 )
		{
			if ( point.y > test.y + 16 )
				result = m_cursorSouthEast;
			else if( point.y < test.y - 16 )
				result = m_cursorNorthEast;
			else
				result = m_cursorEast;
		}
		else if( point.x < test.x - 16 )
		{
			if ( point.y > test.y + 16 )
				result = m_cursorSouthWest;
			else if( point.y < test.y  - 16 )
				result = m_cursorNorthWest;
			else
				result = m_cursorWest;
		}
		else if( point.y < test.y )
			result = m_cursorSouth;
		else
			result = m_cursorNorth;


	}
	else if( m_interactMode == MODE_DRAWING )
	{
		result = LoadCursor( NULL, IDC_CROSS );
	}
	else if( m_objs )
	{

		int count = 0;
		CDiagramEntity* obj = NULL;
		const MSG* msg = GetCurrentMessage();
		CPoint point( msg->pt );
		ScreenToClient( &point );

		while( ( obj = m_objs->GetAt( count++ ) ) )
		{
			if( obj->IsSelected() )
			{

				CRect rect = obj->GetRect();
				VirtualToScreen( rect );

				int hitCode = obj->GetHitCode( point, rect );
				if( hitCode != DEHT_NONE && hitCode != DEHT_BODY )
					result = obj->GetCursor( hitCode );

			}
		}

		if( result == NULL )
		{
			int hitCode = GetHitCode( point );
			if( hitCode != DEHT_NONE && hitCode != DEHT_BODY && m_bgResizeSelected )
				result = GetCursor( hitCode );
		}
	}

	return result;

}

void CDiagramEditor::SetScrollWheelMode( int mode )
/* ============================================================
	Function :		CDiagramEditor::SetScrollWheelMode
	Description :	Accessor for the scroll wheel mode flag.
	Access :		Public

	Return :		void
	Parameters :	int mode	-	New mode
					
	Usage :			"mode" can be any of
						"WHEEL_SCROLL" The editor will scroll when the scroll wheel is rolled.
						"WHEEL_ZOOM" The editor will zoom when the scroll wheel is rolled.
   ============================================================*/
{

	m_scrollwheel = mode;

}

int CDiagramEditor::GetScrollWheelMode() const
/* ============================================================
	Function :		CDiagramEditor::GetScrollWheelMode
	Description :	Accessor for the scroll wheel mode flag.
	Access :		Public

	Return :		int	-	Current mode
	Parameters :	none

	Usage :			The mode can be any of
						"WHEEL_SCROLL" The editor will scroll when the scroll wheel is rolled.
						"WHEEL_ZOOM" The editor will zoom when the scroll wheel is rolled.
   ============================================================*/
{

	return m_scrollwheel;

}

void CDiagramEditor::SetHScroll( int pos )
/* ============================================================
	Function :		CDiagramEditor::SetHScroll
	Description :	Sets the horizontal scrollbar position to 
					"pos".
	Access :		Protected

	Return :		void
	Parameters :	int pos	-	New position
					
	Usage :			Called when the scroll bar position is set. 
					Can be overrided to trigger scroll bar 
					events.

   ============================================================*/
{

	pos = max( 0, pos );

	SCROLLINFO si;
	si.cbSize = sizeof( SCROLLINFO );
	si.fMask = SIF_POS;
	si.nPos = pos;

	SetScrollInfo( SB_HORZ, &si );

}

void CDiagramEditor::SetVScroll( int pos )
/* ============================================================
	Function :		CDiagramEditor::SetVScroll
	Description :	Sets the vertical scrollbar position to 
					"pos".
	Access :		Protected

	Return :		void
	Parameters :	int pos	-	New position
					
	Usage :			Called when the scroll bar position is set. 
					Can be overrided to trigger scroll bar 
					events.

   ============================================================*/
{

	pos = max( 0, pos );

	SCROLLINFO si;
	si.cbSize = sizeof( SCROLLINFO );
	si.fMask = SIF_POS;
	si.nPos = pos;

	SetScrollInfo( SB_VERT, &si );

}

BOOL CDiagramEditor::OutsideRestraints( CPoint point )
/* ============================================================
	Function :		CDiagramEditor::OutsideRestraints
	Description :	Checks if "point" lies outside the current 
					restraints.
	Access :		Protected

	Return :		BOOL			-	"TRUE" if "point" is 
										outside the current 
										constraints.
	Parameters :	CPoint point	-	Coordinates to check.
					
	Usage :			Call to see if coordinates are outside the 
					current restraints.

   ============================================================*/
{

	BOOL result = FALSE;


	if( m_restraint == RESTRAINT_VIRTUAL )
	{

		if( point.x < 0 )
			result = TRUE;
		if( point.y < 0 )
			result = TRUE;

		if( point.x > GetVirtualSize().cx )
			result = TRUE;
		if( point.y > GetVirtualSize().cy )
			result = TRUE;

	}
	else if( m_restraint == RESTRAINT_MARGIN )
	{

		if( point.x < m_leftMargin )
			result = TRUE;
		if( point.y < m_topMargin )
			result = TRUE;

		if( point.x > GetVirtualSize().cx - m_rightMargin )
			result = TRUE;
		if( point.y > GetVirtualSize().cy - m_bottomMargin )
			result = TRUE;

	}

	return result;

}

void CDiagramEditor::ScrollIntoView()
/* ============================================================
	Function :		CDiagramEditor::ScrollIntoView
	Description :	Scrolls the selected items into view.
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Call to scroll the selected item(s) into 
					view.

   ============================================================*/
{

	if( GetSelectCount() )
	{
		CPoint start = GetDiagramEntityContainer()->GetStartPoint();
		CSize objects = GetDiagramEntityContainer()->GetTotalSize();
		CRect rect;
		GetClientRect( rect );
		CSize screen( rect.Width(), rect.Height() );
		if( objects.cx > screen.cx || objects.cy > screen.cy )
		{

			ZoomToFitScreen();

		}
		else
		{

			int leftmargin = ( screen.cx - objects.cx ) / 2;
			int topmargin = ( screen.cy - objects.cy ) / 2;
			int leftstart = start.x - leftmargin;
			int topstart = start.y - topmargin;

			SetHScroll( leftstart );
			SetVScroll( topstart );
			RedrawWindow();

		}
	}

}

void CDiagramEditor::ScrollIntoView( CDiagramEntity* obj )
/* ============================================================
	Function :		CDiagramEditor::ScrollIntoView
	Description :	Scrolls "obj" into view.
	Access :		Public

	Return :		void
	Parameters :	CDiagramEntity* obj	-	Object to scroll 
											into view

	Usage :			Call to scroll "obj" into view.

   ============================================================*/
{

	CRect objrect = obj->GetRect();
	objrect.NormalizeRect();

	CPoint start = objrect.TopLeft();
	CSize objects( objrect.Width(), objrect.Height() );
	CRect rect;
	GetClientRect( rect );
	CSize screen( rect.Width(), rect.Height() );
	if( objects.cx > screen.cx || objects.cy > screen.cy )
	{

		ZoomToFitScreen();

	}
	else
	{

		int leftmargin = ( screen.cx - objects.cx ) / 2;
		int topmargin = ( screen.cy - objects.cy ) / 2;
		int leftstart = start.x - leftmargin;
		int topstart = start.y - topmargin;

		SetHScroll( leftstart );
		SetVScroll( topstart );
		RedrawWindow();

	}

}

/**
leon add
* 이미지 로딩 및 메모리DC 처리
*/
void CDiagramEditor::MakeMemDC( CDC* dc, int tileImageStartFont, int tileImageNum )
{
	cltTSpr *pSpr = &(m_objs->m_spr);
	int i=0;

	if(tileImageNum < 1 || tileImageStartFont< 0)
		return;
	/**
	* m_pbufferDC : 메모리DC에 이미지 로딩함
	*/
	for(i=0; i<MAX_DLG_BUFFER_LENGTH; i++)
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
			// m_pOldBmp는 포인터만 사용할 것이므로 new 할당 필요없음
			m_pOldBmp[i] = (CBitmap*) m_pbufferDC[i]->SelectObject(m_pmemBmp[i]);
		}
	}
	
	// 파일로부터 읽어들인 실제 이미지 버퍼 ( tile image num 개수 만큼 한번에 읽음)
	DrawImageOnMemDC( m_pbufferDC[REAL_BACKGROUND_NUM], tileImageStartFont, tileImageNum);

	// 파일로부터 읽어서 마스크 비트맵을 만듦
	// 투명부분 : 흰색
	// 색깔부분 : 검은색
	 //( tile image num 개수 만큼 한번에 읽음)
	DrawImageOnMemDC(m_pbufferDC[MASK_BACKGROUND_NUM], tileImageStartFont, tileImageNum, WHITE_COLOR, TRANSPARENT_COLOR, TRANSPARENT_COLOR, true);

}

void CDiagramEditor::BitBltDS(CDC* dest, CDC* src, int dest_width, int dest_height, DWORD mode, int src_x, int src_y, int dest_x, int dest_y)
{
	double zoom_width=0, zoom_height=0;

	zoom_width = dest_width/GetZoom();
	zoom_height = dest_height/GetZoom();

	//if(	zoom_width > m_objs->m_spr.clHeader.siXsize )
	//	zoom_width = m_objs->m_spr.clHeader.siXsize;
	//
	//if(	zoom_height > m_objs->m_spr.clHeader.siYsize )
	//	zoom_height = m_objs->m_spr.clHeader.siYsize;

	if(dest !=NULL && src !=NULL)
	{
		dest->StretchBlt(dest_x, dest_y, dest_width, dest_height, src, src_x, src_y, zoom_width, zoom_height, mode);
	}

	//if(dest !=NULL && src !=NULL)
	//	dest->StretchBlt(dest_x, dest_y, dest_width, dest_height, src, src_x, src_y, dest_width/GetZoom(), dest_height/GetZoom(), mode);
	//dest->StretchBlt(dest_x, dest_y, dest_width, dest_height, src, src_x, src_y, dest_width, dest_height, mode);
}

void CDiagramEditor::DrawImageOnMemDC(CDC* dc, int tileImageStartFont, int tileImageNum, DWORD col_dest, DWORD col_src, DWORD col_exclusive_src, BOOL bexclusive )
{
	int i, j, k, m, n;
	DWORD color;
	unsigned char *psrc;

	if(m_objs->m_spr.Image == NULL || m_objs->m_spr.clHeader.siFontNum < tileImageNum || m_objs->m_spr.clHeader.siFontNum < tileImageStartFont + tileImageNum)
		return;

	// DrawSpr ...
	cltTSpr *pSpr = &(m_objs->m_spr);
	CDC *pDC = dc;

	for(m = tileImageStartFont; m< tileImageStartFont+tileImageNum; m++)
	{
		psrc = &((m_objs->m_spr).Image[ (m_objs->m_spr).clHeader.clImgInfo[ m ].siStartPos ]);

		for( i = 0; i < pSpr->clHeader.siYsize; ++i ) {

			j = 0;

			while( j < pSpr->clHeader.siXsize ) {

				if( *psrc == 254 ) {
				
					// pixel skip하기
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

					// DrawMpr이라면
					if(pSpr->clHeader.siSprType !=0)
					{
						cnt = *psrc;
						++psrc;
					}
					else // DrawSpr이라면
					{
						cnt = 1;
					}

					for( k = 0; k < cnt; ++k ) 
					{
						// 16팔레트에서 컬러 읽어오기
						WORD c, r, g, b; 

						c = pSpr->pal[ *psrc ];

						// r, g, b 값 추출  (565팔레트 기준 : LoadSpr에서 565로 읽었으므로)
						r = (c & RGB16_565_RMASK) >> 11;
						g = (c & RGB16_565_GMASK) >> 5;
						b = (c & RGB16_565_BMASK);

						// r(0~31), g(0~63), b(0~31) 값을 0~255범위의 값으로 변환

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

bool CDiagramEditor::DrawTileImg( CDC* dest, SI16 PutSprOption, /*SI16 PutSprParam1,*/ SI16 PutSprParam2, SI16 XPos, SI16 YPos, SI16 Width, SI16 Height, SI16 TileImgNum, bool IsRowTile)
{
	bool LeftTileXSize = false;
	bool LeftTileYSize = false;

	SI16 TileXSize = m_objs->m_spr.clHeader.siXsize;
	SI16 TileYSize = m_objs->m_spr.clHeader.siYsize;

	// 타일이 완전히 덮을 수 있는지 체크 ( 덜 덮거나, 초과해 버리면 안됨으로 )
	// 아래 3줄 주석 처리해 버리면, 아래 코드에 해당하는 경우에는 
	// 배경을 찍기는 하겠지만, 끝 부분을 안 찍게 됨.
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

	// 타일 3개로 이루어진 이미지
	if ( TileImgNum == 3 )
	{	
		if ( IsRowTile )
		{
			// 아래 출력부 하나로 사용가능하지만, 따로 만든 이유는 안에서 switch 문 for 문 여러번 도는 것 보다는,
			// 아래와 같이 한번만 돌게 하는 식으로 성능 향상을 위해서 코드를 늘렸음.
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
			// 아래 출력부 하나로 사용가능하지만, 따로 만든 이유는 안에서 switch 문 for 문 여러번 도는 것 보다는,
			// 아래와 같이 한번만 돌게 하는 식으로 성능 향상을 위해서 코드를 늘렸음.
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
	else if ( TileImgNum == 9 )		// 타일 9개로 이루어진 이미지
	{
		// 아래 출력부 하나로 사용가능하지만, 따로 만든 이유는 안에서 switch 문 for 문 여러번 도는 것 보다는,
		// 아래와 같이 한번만 돌게 하는 식으로 성능 향상을 위해서 코드를 늘렸음.
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
	else if ( TileImgNum == 1 )		// 타일 1개로 이루어진 이미지 ( 제일 사용안 될것 같기에, if 문 최하위로 뒀음 )
	{
		// 아래 출력부 하나로 사용가능하지만, 따로 만든 이유는 안에서 switch 문 for 문 여러번 도는 것 보다는,
		// 아래와 같이 한번만 돌게 하는 식으로 성능 향상을 위해서 코드를 늘렸음.
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

	return true;
	//SI16 TileXSize = m_objs->m_spr.clHeader.siXsize;
	//SI16 TileYSize = m_objs->m_spr.clHeader.siYsize;

	//// 타일이 완전히 덮을 수 있는지 체크 ( 덜 덮거나, 초과해 버리면 안됨으로 )
	//// 아래 3줄 주석 처리해 버리면, 아래 코드에 해당하는 경우에는 
	//// 배경을 찍기는 하겠지만, 끝 부분을 안 찍게 됨.
	///*
	//if ( ( Width % TileXSize ) != 0 || ( Height % TileYSize ) != 0 )
	//{
	//	return false;
	//}
	//*/

	//if(TileXSize <= 0 || TileYSize <=0)
	//	return FALSE;

	//SI16 RowNum = Height / TileYSize;
	//SI16 ColumnNum = Width / TileXSize;

	//SI16 i = 0;
	//SI16 j = 0;

	//if(RowNum == 0 || ColumnNum == 0)
	//{
	//	BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], Width, Height, SRCAND, 0*TileXSize, 0, XPos + 0 * TileXSize, YPos + 0 * TileYSize);
	//	BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], Width, Height, SRCPAINT, 0*TileXSize, 0, XPos + 0 * TileXSize, YPos + 0 * TileYSize);
	//}

	//// 타일 3개로 이루어진 이미지
	//if ( TileImgNum == 3 )
	//{	
	//	if ( IsRowTile )
	//	{
	//		// 아래 출력부 하나로 사용가능하지만, 따로 만든 이유는 안에서 switch 문 for 문 여러번 도는 것 보다는,
	//		// 아래와 같이 한번만 돌게 하는 식으로 성능 향상을 위해서 코드를 늘렸음.
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
	//							BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 0*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 0*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//						}
	//						else if ( j >= ColumnNum - 1 )
	//						{
	//							//pTileImg->PutSprT( XPos + j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 2 );
	//							BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 2*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 2*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//						}
	//						else
	//						{
	//							//pTileImg->PutSprT( XPos + j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 1 );
	//							BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 1*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 1*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
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
	//							BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 0*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 0*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//						}
	//						else if ( j >= ColumnNum - 1 )
	//						{
	//							//pTileImg->PutSprT( XPos + j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 2 );
	//							BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 2*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 2*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//						}
	//						else
	//						{
	//							//pTileImg->PutSprT( XPos + j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 1 );
	//							BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 1*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 1*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
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
	//		// 아래 출력부 하나로 사용가능하지만, 따로 만든 이유는 안에서 switch 문 for 문 여러번 도는 것 보다는,
	//		// 아래와 같이 한번만 돌게 하는 식으로 성능 향상을 위해서 코드를 늘렸음.
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
	//							BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 0*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 0*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//						}
	//						else if ( i >= RowNum - 1 )
	//						{
	//							//pTileImg->PutSprT( XPos + j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 2 );
	//							BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 2*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 2*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//						}
	//						else
	//						{
	//							//pTileImg->PutSprT( XPos + j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 1 );
	//							BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 1*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 1*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
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
	//							BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 0*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 0*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//						}
	//						else if ( i >= RowNum - 1 )
	//						{
	//							//pTileImg->PutSprT( XPos + j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 2 );
	//							BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 2*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 2*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//						}
	//						else
	//						{
	//							//pTileImg->PutSprT( XPos + j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 1 );
	//							BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 1*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 1*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
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
	//else if ( TileImgNum == 9 )		// 타일 9개로 이루어진 이미지
	//{
	//	// 아래 출력부 하나로 사용가능하지만, 따로 만든 이유는 안에서 switch 문 for 문 여러번 도는 것 보다는,
	//	// 아래와 같이 한번만 돌게 하는 식으로 성능 향상을 위해서 코드를 늘렸음.
	//	switch( PutSprOption )
	//	{
	//	case SPR_PUTSPRT:
	//		{
	//			for ( i = 0; i < RowNum; ++i )
	//			{
	//				for ( j = 0; j < ColumnNum; ++j )
	//				{
	//					// 외곽이 아닌 내부 영역
	//					if ( i > 0 && j > 0 && i < RowNum - 1 && j < ColumnNum - 1 )
	//					{
	//						//pTileImg->PutSprT( XPos + j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 4 );
	//						BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 4*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//						BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 4*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);

	//					}
	//					// 외곽 영역
	//					else
	//					{
	//						if ( i < 1 )
	//						{
	//							if ( j < 1 )
	//							{
	//								//pTileImg->PutSprT( XPos + j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 0 );
	//								BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND,  0*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//								BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 0*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							}
	//							else if ( j >= ColumnNum - 1 )
	//							{
	//								//pTileImg->PutSprT( XPos +j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 2 );
	//								BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 2*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//								BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 2*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							}
	//							else
	//							{
	//								//pTileImg->PutSprT( XPos +j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 1 );
	//								BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 1*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//								BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 1*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							}
	//						}
	//						else if ( i >= RowNum - 1 )
	//						{
	//							if ( j < 1 )
	//							{
	//								//pTileImg->PutSprT( XPos +j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 6 );
	//								BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 6*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//								BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 6*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							}
	//							else if ( j >= ColumnNum - 1 )
	//							{
	//								//pTileImg->PutSprT( XPos +j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 8 );
	//								BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 8*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//								BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 8*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							}
	//							else
	//							{
	//								//pTileImg->PutSprT( XPos +j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 7 );
	//								BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 7*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//								BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 7*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							}
	//						}
	//						else if ( j < 1 )
	//						{
	//							//pTileImg->PutSprT( XPos +j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 3 );
	//							BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 3*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 3*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//						}
	//						else if ( j >= ColumnNum - 1 )
	//						{
	//							//pTileImg->PutSprT( XPos +j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 5 );
	//							BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 5*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 5*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
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
	//					// 외곽이 아닌 내부 영역
	//					if ( i > 0 && j > 0 && i < RowNum - 1 && j < ColumnNum - 1 )
	//					{
	//						//pTileImg->PutSprAlphaT( XPos +j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 4, PutSprParam2 );
	//						BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 4*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//						BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 4*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);

	//					}
	//					// 외곽 영역
	//					else
	//					{
	//						if ( i < 1 )
	//						{
	//							if ( j < 1 )
	//							{
	//								//pTileImg->PutSprAlphaT( XPos +j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 0, PutSprParam2 );
	//								BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 0*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//								BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 0*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);

	//							}
	//							else if ( j >= ColumnNum - 1 )
	//							{
	//								//pTileImg->PutSprAlphaT( XPos +j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 2, PutSprParam2 );
	//								BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 2*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//								BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 2*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							}
	//							else
	//							{
	//								//pTileImg->PutSprAlphaT( XPos + j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 1, PutSprParam2 );
	//								BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 1*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//								BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 1*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							}
	//						}
	//						else if ( i >= RowNum - 1 )
	//						{
	//							if ( j < 1 )
	//							{
	//								//pTileImg->PutSprAlphaT( XPos + j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 6, PutSprParam2 );
	//								BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 6*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//								BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 6*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							}
	//							else if ( j >= ColumnNum - 1 )
	//							{
	//								//pTileImg->PutSprAlphaT( XPos + j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 8, PutSprParam2 );
	//								BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 8*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//								BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 8*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							}
	//							else
	//							{
	//								//pTileImg->PutSprAlphaT( XPos + j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 7, PutSprParam2 );
	//								BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 7*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//								BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 7*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							}
	//						}
	//						else if ( j < 1 )
	//						{
	//							//pTileImg->PutSprAlphaT( XPos + j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 3, PutSprParam2 );
	//							BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 3*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 3*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//						}
	//						else if ( j >= ColumnNum - 1 )
	//						{
	//							//pTileImg->PutSprAlphaT( XPos + j * TileXSize, YPos + i * TileYSize, PutSprParam1 + 5, PutSprParam2 );
	//							BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 5*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//							BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 5*TileXSize,0,  XPos + j * TileXSize, YPos + i * TileYSize);
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
	//else if ( TileImgNum == 1 )		// 타일 1개로 이루어진 이미지 ( 제일 사용안 될것 같기에, if 문 최하위로 뒀음 )
	//{
	//	// 아래 출력부 하나로 사용가능하지만, 따로 만든 이유는 안에서 switch 문 for 문 여러번 도는 것 보다는,
	//	// 아래와 같이 한번만 돌게 하는 식으로 성능 향상을 위해서 코드를 늘렸음.
	//	switch( PutSprOption )
	//	{
	//	case SPR_PUTSPRT:
	//		{
	//			for ( i = 0; i < RowNum; ++i )
	//			{
	//				for ( j = 0; j < ColumnNum; ++j )
	//				{
	//					//pTileImg->PutSprT( XPos + j * TileXSize, YPos + i * TileYSize, PutSprParam1 );
	//					BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 0*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//					BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 0*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
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
	//					BitBltDS( dest, m_pbufferDC[MASK_BACKGROUND_NUM], TileXSize, TileYSize, SRCAND, 0*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
	//					BitBltDS( dest, m_pbufferDC[REAL_BACKGROUND_NUM], TileXSize, TileYSize, SRCPAINT, 0*TileXSize, 0, XPos + j * TileXSize, YPos + i * TileYSize);
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

/**
leon add
* DLG Property 추가
*/
void CDiagramEditor::OnDLGProperty()
{
	m_DLGPropertyDlg.ShowProperties(this);
}

void CDiagramEditor::DeleteAllBmp()
{
	for(int i=0; i<MAX_CONTROL_BUFFER_LENGTH; i++)
	{
		//m_pmemBmp[i]->DeleteObject();
		delete m_pmemBmp[i];
		m_pmemBmp[i] = NULL;
	}
}

void CDiagramEditor::ClearAllOldBmp()
{
	for(int i=0; i<MAX_CONTROL_BUFFER_LENGTH; i++)
		m_pOldBmp[i] = NULL;
}

void CDiagramEditor::DeleteAllBufferDC()
{
	for(int i=0; i<MAX_CONTROL_BUFFER_LENGTH; i++)
	{
	    if(m_pbufferDC[i])
		{
			//m_pbufferDC[i]->DeleteDC();
			//m_pbufferDC[i]->ReleaseOutputDC();
			m_pbufferDC[i]->FillSolidRect(0, 0, m_objs->m_spr.clHeader.siXsize, m_objs->m_spr.clHeader.siYsize, TRANSPARENT_COLOR);
			delete m_pbufferDC[i];
			m_pbufferDC[i] = NULL;
		}
	}
}

bool CDiagramEditor::CheckIntegrity()
{
	bool tmpChanged = false;
	// 무결성 검사 ####################################################
	if(m_gridSize.cx < DLG_GRID_MIN_LENGTH)
	{
		m_gridSize.cx = DLG_GRID_MIN_LENGTH;
		tmpChanged = true;
	}

	if(m_gridSize.cy < DLG_GRID_MIN_LENGTH)
	{
		m_gridSize.cy = DLG_GRID_MIN_LENGTH;
		tmpChanged = true;
	}

	if(m_leftMargin < DLG_MARGIN_MIN_LENGTH)
	{
		m_leftMargin = DLG_MARGIN_MIN_LENGTH;
		tmpChanged = true;
	}

	if(m_topMargin < DLG_MARGIN_MIN_LENGTH)
	{
		m_topMargin = DLG_MARGIN_MIN_LENGTH;
		tmpChanged = true;
	}

	if(m_rightMargin < DLG_MARGIN_MIN_LENGTH)
	{
		m_rightMargin = DLG_MARGIN_MIN_LENGTH;
		tmpChanged = true;
	}

	if(m_bottomMargin < DLG_MARGIN_MIN_LENGTH)
	{
		m_bottomMargin = DLG_MARGIN_MIN_LENGTH;
		tmpChanged = true;
	}

	CString tmpStr;

	// 좌우 불필요한 공백 제거
	if(m_objs != NULL)
		tmpStr = m_objs->GetDefaultFilePath();

	tmpStr.Trim();

	tmpStr.Replace( FILE_PATH_SPLITTER_BACKSLASH, FILE_PATH_SPLITTER_SLASH);

	if(m_objs != NULL)
		m_objs->SetDefaultFilePath(tmpStr);

	int length = 0;

    m_objs->m_defaultImagePath.Trim();
	length = m_objs->m_defaultImagePath.GetLength();

	if(m_objs->m_defaultImagePath[length-1] != FILE_PATH_SPLITTER_SLASH && m_objs->m_defaultImagePath[length-1] != FILE_PATH_SPLITTER_BACKSLASH)
		m_objs->m_defaultImagePath = m_objs->m_defaultImagePath + FILE_PATH_SPLITTER_SLASH;

	//// 좌우 불필요한 공백 제거 및 마지막에 '\\' 혹은 '/'로 끝났나 확인!!
	//m_defaultImagePath.Trim(WHITESPACE_N_TAB);

	//if(m_defaultImagePath != STR_EMPTY)
	//
	//	m_defaultImagePath FILE_PATH_SPLITTER_BACKSLASH;
	//
	// ##################################################################

	return tmpChanged;
}

bool CDiagramEditor::SaveSettings()
{
	//char curPath[512];
	//char fullPath[1024];
	//memset(curPath, 0, 512);
	//memset(fullPath, 0, 512);
	//DWORD length = GetCurrentDirectory(512, curPath);

	//if(length <= 0 ) return false;

	//// patchinfo
	//_snprintf(fullPath, 1024, "%s\\DLGSetting.txt", curPath);

	FILE *fp = fopen(g_StartPath/*fullPath*//*"c:/DLGSetting.txt"*/, "wt");

	if( fp == NULL)
		return FALSE;

	// 무결성 검사
	CheckIntegrity();

	if(m_objs != NULL)
	{
		fprintf( fp, "%d %d\n%d %d %d %d\n%s\n%s\n%d", m_gridSize.cx, m_gridSize.cy, m_leftMargin, m_topMargin,
			m_rightMargin, m_bottomMargin, m_objs->GetDefaultFilePath(), m_objs->GetDefaultTxtFilePath(), g_bMagnetMode/*m_defaultImagePath*/);
	}

	fclose(fp);

	return TRUE;
}

bool CDiagramEditor::LoadSettings()
{
	//char curPath[512];
	//char fullPath[1024];
	//memset(curPath, 0, 512);
	//memset(fullPath, 0, 512);
	//DWORD length = GetCurrentDirectory(512, curPath);

	//if(length <= 0 ) return false; 

	//// patchinfo
	//_snprintf(fullPath, 1024, "%s\\DLGSetting.txt", curPath);

	FILE *fp = fopen( g_StartPath/*fullPath*//*"c:/DLGSetting.txt"*/, "rt" );
	char charBuffer[1024];
	int readNum = 0;

	if ( fp == NULL )
	{
		fp = fopen(g_StartPath/*fullPath*//*"c:/DLGSetting.txt"*/, "wt");

		if(fp == NULL)
			return FALSE;

		// 무결성 검사
		CheckIntegrity();

		if(m_objs != NULL)
			fprintf( fp, "%d %d\n%d %d %d %d\n%s\n%s\n%d", m_gridSize.cx, m_gridSize.cy, m_leftMargin, m_topMargin,
				m_rightMargin, m_bottomMargin, m_objs->GetDefaultFilePath(), m_objs->GetDefaultTxtFilePath(), g_bMagnetMode/*m_defaultImagePath*/);

		fclose(fp);

		return true;
	}
	else
	{

		fgets(charBuffer, 256, fp);
		//readNum = fread(charBuffer, sizeof(char), 1023, fp);
		//if(readNum > 0)
		{
			int tmpint = 0;
			//charBuffer[readNum] = '\0';

			CString tmpstr = charBuffer;
			int start = 0, end = 0;
			// 파일에서 Grid 값 가져오기
			//end = tmpstr.Find("\n", start);
			//tmpint = sscanf(tmpstr.Mid(start, end), "%d %d", &m_gridSize.cx, &m_gridSize.cy);
			tmpint = sscanf(charBuffer, "%d %d", &m_gridSize.cx, &m_gridSize.cy);

			if(tmpint == 2)
			{
				//start = end;

				//// 파일에서 Margin 값 가져오기
				//end = tmpstr.Find("\n", start+1);
				//tmpint = sscanf(tmpstr.Mid(start, end), "%d %d %d %d", &m_leftMargin, &m_topMargin, &m_rightMargin, &m_bottomMargin);
				fgets(charBuffer, 256, fp);
				tmpint = sscanf(charBuffer, "%d %d %d %d", &m_leftMargin, &m_topMargin, &m_rightMargin, &m_bottomMargin);

				if(tmpint == 4)
				{
					//start = end;

					//end = tmpstr.Find("\n", start);
					//m_defaultImagePath = tmpstr.Mid(start);
					if(m_objs != NULL)
					{
						//end = tmpstr.Find("\n", start+1);

						CString tmp1, tmp2;
						tmp1 = GOONZU_DEFAULT_ROOT_PATH;
						tmp2 = GOONZU_DEFAULT_TEXTMGR_PATH;
						//tmp = tmpstr.Mid(start, end );
						//sscanf(tmpstr.Mid( start ), "%s\r\n%s", tmp1, tmp2 );
						//sscanf(tmpstr.Mid(start, end), "%s", &tmp );
						//m_objs->SetDefaultFilePath(tmpstr.Mid(start+1, end-1));
						
						// 작업폴더명
						fgets(charBuffer, 256, fp);
						//tmpint = sscanf(charBuffer, "%s", tmp1);
                        if( strcmp(charBuffer, "" ) != 0 && strlen(charBuffer) > 1 )			
							m_objs->SetDefaultFilePath( charBuffer/*tmp1*/ );
						else
							m_objs->SetDefaultFilePath( tmp1 );

						// TextMgr.txt 파일경로
						fgets(charBuffer, 256, fp);
						m_objs->SetDefaultTxtFilePath( charBuffer );

                        if( strcmp(charBuffer, "" ) != 0 && strlen(charBuffer) > 1 )			
							m_objs->SetDefaultTxtFilePath( charBuffer );
						else
							m_objs->SetDefaultTxtFilePath( tmp1 );

						//start = end;

						//m_objs->SetDefaultTxtFilePath(tmpstr.Mid(start));						
						//fgets(charBuffer, 256, fp);
						//charBuffer[256] = '\0';
						//tmpint = sscanf(charBuffer, "%s", tmp2);
						
						//m_objs->SetDefaultTxtFilePath( charBuffer );

					}

					fclose(fp);
					if(CheckIntegrity())
					{
						SaveSettings();
						return true;
					}
				}
			}
		}

		//cyj g_pTextMgr.Create( (char *)(LPCTSTR)m_objs->m_defaultTxtPath );
		g_pTextManager.CreateTextManager();
		if ( g_pTextManager.LoadTextFromCryptFile( (char *)(LPCTSTR)m_objs->m_defaultTxtPath , 1) == false )
		{
			CString strFilePath = m_objs->m_defaultTxtPath;
			strFilePath.Insert( strFilePath.GetLength()-1, _T('\0') );

			if ( g_pTextManager.LoadTextFromFile( (TCHAR*)(LPCTSTR)strFilePath , 1) == false )
			{
				AfxMessageBox( _T("TextMgr.txt파일을 열수없습니다") );
				exit(0);
			}
		}

		//AfxMessageBox( GetTxtFromMgr( 1 ) );

		CheckIntegrity();
		SaveSettings();
	}
	fclose(fp);
}

#pragma warning( default : 4706 )
