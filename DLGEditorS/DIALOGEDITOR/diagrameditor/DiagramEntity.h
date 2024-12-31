#ifndef _DIAGRAMENTITY_H_
#define _DIAGRAMENTITY_H_

#include "DiagramPropertyDlg.h"

#include "../../SprFile/SprFile.h"
#include "../../MyDefine/MyDefine.h"
#include "../DLGDefine.h"

#define CMD_START			100
#define CMD_CUT				100
#define CMD_COPY			101
#define CMD_DUPLICATE		102
#define CMD_PROPERTIES		103
#define CMD_UP				104
#define CMD_DOWN			105
#define CMD_FRONT			106
#define CMD_BOTTOM			107
#define CMD_SELECT_GROUP	108
#define CMD_END				200

#define DEHT_NONE				0
#define DEHT_BODY				1
#define DEHT_TOPLEFT			2
#define DEHT_TOPMIDDLE			3
#define DEHT_TOPRIGHT			4
#define DEHT_BOTTOMLEFT			5
#define DEHT_BOTTOMMIDDLE		6
#define DEHT_BOTTOMRIGHT		7
#define DEHT_LEFTMIDDLE			8
#define DEHT_RIGHTMIDDLE		9

#define round(a) ( int ) ( a + .5 )

class CDiagramEntityContainer;
class CDiagramPropertyDlg;

// ���� dialog ID
extern CString strDLGUniqueID;
extern int sDLGUniqueNum;

// Ÿ�� �̹����� � ��Ʈ���� ���� ������. ��, �ݵ�� Ÿ�Ϸ� ������ ���� �� �־�� �Ѵ�.
// ���̾�α��� ����� ���� ���� �����ϰ� ����
// 1pixel �� ���̰� ���� �ʰ� �ϱ� ���Ѱ�
// PutSprParam1 �� �̹����� Font Index �� ����Ű�� ����
// PutSprParam2 �� PutSprOption�� PutSprAlphaT�� ��쿡 Alpha ���� �־���� ������ �׶� ���
// TileImgNum �� 1, 3, 9 ���߿� �ϳ��� �����ϴ�.
// 1���� �̹����� �������̳�, 3���� �̹����� �������̳�, 9���� �̹����� �������̳� ������..
// IsRowTile �̰��� ���ηθ� Ÿ���� ������ ����Ѵ�. 3���� �̹����� �⺻������ ���η� ��������,
// ��ũ�� ���� ���� ���η� Ÿ�� �̹����� �����Ƿ�...

class CMainFrame;

enum
{
	SPR_PUTSPRT,
	SPR_PUTSPRALPHAT,
};

class CDiagramEntity : public CObject
{

friend class CDiagramEntityContainer;

public:

	// Creation/initialization
	CDiagramEntity();
	CDiagramEntity(int count);

	virtual ~CDiagramEntity();

protected:

	virtual void	Clear();

public:

	virtual	CDiagramEntity* Clone();
	virtual void	Copy( CDiagramEntity* obj );

	virtual BOOL	FromString( const CString& str );
	virtual CString	Export( UINT format = 0 ) const;
	virtual CString	GetString();// const;
	static	CDiagramEntity* CreateFromString( const CString& str );

	// Object rectangle handling
	virtual CRect	GetRect() const;
	virtual void	SetRect( CRect rect );
	virtual void	SetRect( double left, double top, double right, double bottom, bool bIsLoading = false, int nModeDetail = -1 );
	virtual void	MoveRect( double x, double y );

	double			GetLeft() const;
	double			GetRight() const;
	double			GetTop() const;
	double			GetBottom() const;

	virtual void	SetLeft( double left );
	virtual void	SetRight( double right );
	virtual void	SetTop( double top );
	virtual void	SetBottom( double bottom );

	virtual void	SetMinimumSize( CSize minimumSize );
	virtual CSize	GetMinimumSize() const;
	virtual void	SetMaximumSize( CSize minimumSize );
	virtual CSize	GetMaximumSize() const;
	virtual void	SetConstraints( CSize min, CSize max );

	double			GetZoom() const;

	// Selection handling
	virtual void	Select( BOOL selected );
	virtual BOOL	IsSelected() const;
	virtual BOOL	BodyInRect( CRect rect ) const;

	// Interaction
	virtual int		GetHitCode( CPoint point ) const;
	virtual int		GetHitCode( const CPoint& point, const CRect& rect ) const;

	virtual BOOL	DoMessage( UINT msg, CDiagramEntity* sender, CWnd* from = NULL );

	// Auxilliary
	virtual void	ShowProperties( CWnd* parent, BOOL show = TRUE );
	virtual void	ShowPopup( CPoint point, CWnd* parent );

	// Visuals
	virtual void	Draw( CDC* dc, CRect rect );
	virtual HCURSOR GetCursor( int hit ) const;
	virtual void	DrawObject( CDC* dc, double zoom );

	// Properties
	virtual CString	GetTitle() const;
	virtual void	SetTitle( CString title );

	virtual CString	GetName() const;
	virtual void	SetName( CString name );

	CString			GetType() const;
	void			SetType( CString type );

	int				GetGroup() const;
	void			SetGroup( int group );

	/**
	 leon add
	 * todo - new property ############################################################################################################################################################
	 */
	CString			GetPicFullPath() const;
	void			SetPicFullPath( CString picFullPath );
	CString			GetOldPicFullPath() const;
	void			SetOldPicFullPath( CString oldPicFullPath );
	BOOL			IsEqualPicPath();
	// ��� ������ �� property ������ �����Ű�� �Լ�
    /*virtual*/			BOOL SetPropertyWithIndex(CString strVal, int index);
	/*virtual	*/		BOOL GetPropertyWithIndex(CString& strVal, int index);
	virtual			void SetPropertyDefault();
	int				GetPropertyCount();
	/*virtual*/			CString			GetFormatString();
   
	CDC*			GetBufferDC(int index);
	void			SetBufferDC( CDC* pbufferDC, int index );
	void			SetAllBufferDC( CDC* pbufferDC);
	void			CreateBufferDC(CDC* dc, int index);

	CBitmap*		GetBmp(int index);
	void			SetBmp( CBitmap* pmemBmp, int index );
	void			SetAllBmp( CBitmap* pmemBmp);
	void			CreateBmp(CDC* dc, int index);

	CBitmap*		GetOldBmp(int index);
	void			SetOldBmp( CBitmap* pmemBmp, int index );
	void			SetAllOldBmp( CBitmap* pmemBmp);

	void			DeleteBufferDC(int index);
	void			DeleteAllBufferDC();
	void			DeleteBmp(int index);
	void			DeleteAllBmp();

	void			RestoreMemBitmap(int index);
	void			RestoreAllMemBitmap();
	void			ClearOldBmp(int index);
	void			ClearAllOldBmp();

	void			MakeMemDC( CDC* dc, int tileImageStartFont = 0, int tileImageNum = 1);
	void			DrawImageOnMemDC(CDC* dc, int tileImageStartFont = 0, int tileImageNum = 1,  DWORD col_dest = TRANSPARENT_COLOR, DWORD col_src = TRANSPARENT_COLOR, DWORD col_exclusive_src = 0xffffffff, BOOL bexclusive = false );
	void			BitBltDS(CDC* dest, CDC* src, int dest_width, int dest_height, DWORD mode=SRCCOPY, int src_x=0, int src_y=0, int dest_x=0, int dest_y=0);
	
	bool			DrawTileImg( CDC* dest, SI16 PutSprOption, /*SI16 PutSprParam1,*/ SI16 PutSprParam2, SI16 XPos, SI16 YPos, SI16 Width, SI16 Height, SI16 TileImgNum, bool IsRowTile = true );

	int				SetToMultipleSize(double origin_val, double ref_multiple);

	virtual			void	IncreaseUniqueIDNum();	// �� ��ü�� ���� id ��ȣ�� ������Ű�� ���� �Լ�

	BOOL			IsOverLapping(CDiagramEntity* tmpObj, CString tmpIDNum);	// �Է� ���� id ��ȣ�� �̹� �����ϴ°�? true : false
	//##################################################################################################################################################################################

	BOOL			LoadFromString( CString& data );

//protected:
public:


	// Selection
	virtual void	DrawSelectionMarkers( CDC* dc, CRect rect ) const;
	virtual CRect	GetSelectionMarkerRect( UINT marker, CRect rect ) const;

	// Visuals
	void			GetFont( LOGFONT& lf ) const;

	// Properties
	void			SetMarkerSize( CSize markerSize );
	CSize			GetMarkerSize() const;

	void			SetZoom( double zoom );

	// CDiagramEntityContainer�� �����ϸ鼭 ���ÿ�
	// �о�� path ��θ� ��ü ��η� ����
	// todo - ���� �и� �ʿ�!!
	void						SetParent( CDiagramEntityContainer* parent );

	CDiagramEntityContainer*	GetParent() const;

	void						SetPropertyDialog( CDiagramPropertyDlg* dlg, UINT resid );
	CDiagramPropertyDlg*		GetPropertyDialog() const;

	virtual CString				GetDefaultGetString();// const;
	virtual CString				GetHeaderFromString( CString& str );
	virtual BOOL				GetDefaultFromString( CString& str );

//private:
public:
	// Position
	//double	m_left;
	//double	m_right;
	//double	m_top;
	//double	m_bottom;
	int	m_left;
	int	m_right;
	int	m_top;
	int	m_bottom;

	// Sizes
	CSize	m_markerSize;
	CSize	m_minimumSize;
	CSize	m_maximumSize;

	// States
	double	m_zoom;
	BOOL	m_selected;

	// Data
	CString m_type;
	CString m_title;
	CString m_name;

	int		m_group;

	/**
	leon add
	* todo - new property member
	*/
public:
	CMainFrame	*m_pFrame;	// MainFrame�� ������

	CString* m_pProperty;

	CString m_picFullPath;	// ��� �׸� FullPath
	CString m_oldPicFullPath;	// ���� ��� �׸� FullPath

	CDC* m_pbufferDC[MAX_CONTROL_BUFFER_LENGTH];	// �޸� buffer
	CBitmap* m_pmemBmp[MAX_CONTROL_BUFFER_LENGTH];	// �޸� bitmap
	CBitmap* m_pOldBmp[MAX_CONTROL_BUFFER_LENGTH];	// ���� �޸� bitmap 

	cltTSpr m_spr;	// �̹��� ���� ������

	CDiagramPropertyDlg*		m_propertydlg;
	UINT						m_propertydlgresid;

	CDiagramEntityContainer*	m_parent;

};

#endif // _DIAGRAMENTITY_H_
