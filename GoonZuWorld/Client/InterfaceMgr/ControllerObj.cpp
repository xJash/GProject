#include "ControllerObj.h"
#include "ControllerMgr.h"
#include "ControllerSurfaceObj.h"

#include <Graphic.h>
#include <Graphic_Capsule.h>

#include "InterfaceMgr.h"

#include <Client.h>
#include "../Client/DLGPositionSave/DLGPositionSave.h"

#include "./interfaceimgmgr/InterfaceImgMgr.h"

extern cltCommonLogic *pclClient;

/*
extern CInterfaceMgr *g_pInterfaceMgr;
*/

CControllerObj::CControllerObj( CControllerMgr *pParent ) : CObj()
{
	m_pParent = pParent;
	Init();
}
CControllerObj::CControllerObj( CControllerMgr *pParent,SI32 siTmpBufferSize ) : CObj(siTmpBufferSize)
{
	m_pParent = pParent;
	Init();
}

void CControllerObj::Init()
{
	// Controller �ʱ�ȭ
	m_siControllerID = 0;
	m_siControllerKind = CONTROLLER_KIND_NONE;

	// HotKey
	m_uiHotkey = 0;

	// Controller �� ó���� Ȱ��ȭ�� ���ÿ� ������� ������... ���ÿ� ��Ŀ���� �������..
	m_bEnable = true;
	m_bShow = true;
	m_bHasFocus = false;
	m_bMouseOver = false;

	m_bBKTileImg = true;					// ��κ� ��� �̹����� Tile�� ó���� ���� ( �뷮 ���̱� )
	m_siBKTileImgNum = 9;					// 9�� Ÿ�Ϸ� �̷�� �� ��찡 ��������...
	m_siDrawOption = SPR_PUTSPRT;
	m_siAlphaValue = 12;


	// ��, ��ư�� ���� ��� ���� �̹����� ��¥�� ���� ( ������, �ڵ��ϱ� ������... )
	// ��� �̹��� ���
	TMemSet( m_strFileName, 0, MAX_PATH );

	// ��ǥ �ʱ�ȭ
	m_siXPos = 0;
	m_siYPos = 0;
	m_siWidth = 0;
	m_siHeight = 0;

	m_siMaxSurfaceWidth = 0;
	m_siMaxSurfaceHeight = 0;


	// �ٲ�� �ִ��� ������ ���� flag
	m_bChanged = false;

	// Surface
	m_pControllerSurfaceObj = NULL;

	StringCchCopy( m_strFontKind, MAX_PATH, DEFAULT_FONT_KIND );
	m_siFontWidth = 0;
	m_siFontHeight = BASE_FONT_HEIGHT;
	m_siFontWeight = FW_NORMAL;		//FW_BOLD;
	m_FontColor = RGB( 0, 0, 0 );

	m_siTextPrintOption = 0;

	m_bBorder = false;
	m_crBorder = CONTROLLER_BORDER_COLOR;

	m_bBKColorUse = false;
	m_crBKColor = CONTROLLER_BACKGROUND_COLOR;

	m_siBackGroundDrawOption = SPR_PUTSPRT;
	m_siParam1 = BASE_ALPHA_VALUE;
	m_siParam2 = 0;

	m_bImageArea = false;
}

CControllerObj::~CControllerObj()
{
	if( m_pControllerSurfaceObj )
	{
		delete m_pControllerSurfaceObj;
		m_pControllerSurfaceObj = NULL;
	}

	m_pParent->Del( this );
}

void CControllerObj::Create( SI16 ControllerID, SI16 ControllerKind,
							TCHAR *FileName, SI16 FontIndex, bool BKTileImg, SI16 BKTileImgNum,
							SI16 XPos, SI16 YPos, SI16 Width, SI16 Height, 
							SI16 MaxSurfaceWidth, SI16 MaxSurfaceHeight )
{
#ifdef _DEBUG
	if ( Width > MaxSurfaceWidth )
	{
		TCHAR Buffer[ 128 ] = TEXT("");
		TCHAR* pText = GetTxtFromMgr(3905);
		StringCchPrintf( Buffer, 128, pText, ControllerID, Width, MaxSurfaceWidth );
		MessageBox( pclClient->GetHwnd(), Buffer, TEXT("Error"), MB_OK );
	}
	if ( Height > MaxSurfaceHeight )
	{
		TCHAR Buffer[ 128 ] = TEXT("");
		TCHAR* pText = GetTxtFromMgr(3906);
		StringCchPrintf( Buffer,  128, pText, ControllerID, Height, MaxSurfaceHeight );
		MessageBox( pclClient->GetHwnd(), Buffer, TEXT("Error"), MB_OK );
	}
#endif


	m_siControllerKind = ControllerKind;
	m_siControllerID = ControllerID;

	// NULL �Ǵ� < 1 �� ���� ����� RGB �ܻ����� �Ǿ� ���� �� ��������...
	if ( FileName == NULL || !FileName[ 0 ] )
	{
		TMemSet( m_strFileName, 0, MAX_PATH );
	}
	else
	{
		StringCchCopy( m_strFileName, MAX_PATH, FileName );
	}

	m_siFontIndex = FontIndex;

	m_bBKTileImg = BKTileImg;
	m_siBKTileImgNum = BKTileImgNum;

	m_siXPos = XPos;
	m_siYPos = YPos;

	m_siWidth = Width;
	m_siHeight = Height;

	m_siMaxSurfaceWidth = MaxSurfaceWidth;
	m_siMaxSurfaceHeight = MaxSurfaceHeight;

	m_bChanged = false;

	if ( m_pControllerSurfaceObj )
	{
		delete m_pControllerSurfaceObj;
		m_pControllerSurfaceObj = NULL;
	}

	m_pControllerSurfaceObj = new CControllerSurfaceObj();
	m_pControllerSurfaceObj->Create( MaxSurfaceWidth, MaxSurfaceHeight );


	if( m_pParent )
	{
		m_pParent->Add( this );
	}
}

void CControllerObj::SetSurfaceObjSize(SI16 SurfaceWidth, SI16 SurfaceHeight)
{
	if ( m_pControllerSurfaceObj )
	{
		delete m_pControllerSurfaceObj;
		m_pControllerSurfaceObj = NULL;
	}

	m_pControllerSurfaceObj = new CControllerSurfaceObj();
	m_pControllerSurfaceObj->Create( SurfaceWidth, SurfaceHeight );

}


void CControllerObj::Draw( SI16 BaseXPos, SI16 BaseYPos )
{	
	if ( ! IsShow() )
	{
		return;
	}

	/*
	// ��� �̹��� �ε�
	if ( GetBKImg()->Image == NULL && GetFileName() != NULL )
	{
		if( ! LoadBKImg() )
		{
			// ��� ������ �� �׷��ָ� �׸�������, return �ڵ�� �ּ�ó���� (ex : Static Controller )
			//return;
		}
	}
	*/

	DrawController( BaseXPos, BaseYPos );
}

// �� ��ǥ�� �� Controller ������ �ִ��� �ƴ��� Ȯ��
bool CControllerObj::IsInArea( SI32 XPos, SI32 YPos )
{
	cltClient *pclclient = (cltClient*)pclClient;

	if ( ! IsShow() )
	{
		return false;
	}

	if ( m_siXPos < XPos && m_siYPos < YPos &&
		m_siXPos + m_siWidth > XPos && m_siYPos + m_siHeight > YPos )
	{
		if( IsBKTileImg() == false && m_bImageArea )
		{
			TSpr *pBkImg = pclclient->m_pInterfaceMgr->GetInterfaceImgrMgr()->LoadInterfaceImg( GetFileName() );
            BYTE btColor = GP.GetSprColor( pBkImg, XPos - m_siXPos, YPos - m_siYPos, GetFontIndex(), false );

			return (btColor != COLOR_TRANS);
		}
		else
			return true;
	}

	return false;
}

// �� move �� ��쿡�� ���� ������ ����. ���̾�α׶� ������� �̰͸� �����̰� �Ҷ� ����
void CControllerObj::Move( SI16 OffsetX, SI16 OffsetY )
{
	m_siXPos += OffsetX;
	m_siYPos += OffsetY;

	return;
}

void CControllerObj::Show( bool ShowOption )
{
	m_bShow = ShowOption;

	if ( m_bShow )
	{
		Refresh();
	}

	if ( ShowOption == false &&
		GetParent()->GetMouseOverObj() != NULL && 
		GetParent()->GetMouseOverObj() == this )
	{
		OnMouseLeave();
		GetParent()->SetMouseOverObj( NULL );
		g_DlgPositionSave.SetPosition( GetControllerID(), GetX(), GetY() );
	}

	return;
}

bool CControllerObj::LButtonDown( SI16 XPos, SI16 YPos, SI16 *pControllerID, SI16 *pKind )
{
	if ( ! m_bShow )
	{
		return false;
	}

	if ( IsInArea( XPos, YPos ) )
	{
		return true;
	}

	return false;
}

bool CControllerObj::LButtonUp( SI16 XPos, SI16 YPos, SI16 *pControllerID, SI16 *pKind )
{
	if ( ! m_bShow )
	{
		return false;
	}

	if ( IsInArea( XPos, YPos ) )
	{
		return true;
	}

	return false;
}

bool CControllerObj::RButtonDown( SI16 XPos, SI16 YPos, SI16 *pControllerID, SI16 *pKind )
{
	if ( ! m_bShow )
	{
		return false;
	}

	if ( IsInArea( XPos, YPos ) )
	{
		return true;
	}

	return false;
}


bool CControllerObj::RButtonUp( SI16 XPos, SI16 YPos, SI16 *pControllerID, SI16 *pKind )
{
	if ( ! m_bShow )
	{
		return false;
	}

	if ( IsInArea( XPos, YPos ) )
	{
		return true;
	}

	return false;
}

bool CControllerObj::MouseMove( SI16 XPos, SI16 YPos, SI16 PreXPos, SI16 PreYPos, SI16 *pControllerID, SI16 *pKind )
{
	if ( ! m_bShow )
	{
		return false;
	}

	if ( IsInArea( XPos, YPos ) )
	{
		return true;
	}

	return false;
}

/*
void CControllerObj::SetBKImg( TCHAR *FileName )
{
	// NULL �Ǵ� < 1 �� ���� ����� RGB �ܻ����� �Ǿ� ���� �� ��������...
	if ( FileName == NULL || _tcslen( FileName ) < 1 )
	{
		TMemSet( m_strFileName, 0, MAX_PATH );
		return;
	}
	else
	{
		_tcscpy( m_strFileName, FileName );
	}

	return;
}
*/

/*
bool CControllerObj::LoadBKImg()
{
	// NULL �Ǵ� < 1 �� ���� ����� RGB �ܻ����� �Ǿ� ���� �� ��������...
	if ( GetFileName() == NULL || _tcslen( GetFileName() ) < 1 )
	{
		return false;
	}
	else
	{
		// ��� �̹��� �ε�Ǿ� �ִٸ�.. �ε� �� �ʿ� ��������...
		if ( GetBKImg()->Image == NULL )
		{	
			if ( GP.LoadSpr( GetFileName(), GetBKImg() ) == FALSE )
			{
				return false;
			}
		}

		return true;
	}

	return false;
}

bool CControllerObj::LoadCaretImg( TCHAR *FileName )
{
	// NULL �Ǵ� < 1 �� ���� ����� RGB �ܻ����� �Ǿ� ���� �� ��������...
	if ( FileName == NULL || _tcslen( FileName ) < 1 )
	{
		return false;
	}
	else
	{
		// ��� �̹��� �ε�Ǿ� �ִٸ�.. �ε� �� �ʿ� ��������...
		if ( GetCaretImg()->Image == NULL )
		{	
			if ( GP.LoadSpr( FileName, GetCaretImg() ) == FALSE )
			{
				return false;
			}
		}

		return true;
	}

	return false;
}
*/

void CControllerObj::MoveControl( SI16 XPos, SI16 YPos )
{
	SetX( XPos );
	SetY( YPos );

	return;
}

void CControllerObj::DrawBorder( HDC hDC, SI16 XPos, SI16 YPos, SI16 Width, SI16 Height )
{
	DrawRoundRect( hDC, XPos, YPos, Width, Height, IsBorder(), m_bBKColorUse, m_crBorder, m_crBKColor );
	return;
}

void CControllerObj::SetControllerPos( SI16 XPos, SI16 YPos, SI16 Width, SI16 Height, SI16 SurfaceWidth, SI16 SurfaceHeight )
{
#ifdef _DEBUG
	if ( Width > SurfaceWidth )
	{
		TCHAR Buffer[ 128 ] = TEXT("");
		TCHAR* pText = GetTxtFromMgr(3907);
		StringCchPrintf( Buffer,128, pText, Width, SurfaceWidth );
		MessageBox( pclClient->GetHwnd(), Buffer, TEXT("Error"), MB_OK );
	}
	if ( Height > SurfaceHeight )
	{
		TCHAR Buffer[ 128 ] = TEXT("");
		TCHAR* pText = GetTxtFromMgr(3908);
		StringCchPrintf( Buffer, 128, pText, Height, SurfaceHeight );
		MessageBox( pclClient->GetHwnd(), Buffer, TEXT("Error"), MB_OK );

	}
#endif

	m_siXPos = XPos;
	m_siYPos = YPos;

	m_siWidth = Width;
	m_siHeight = Height;

	m_siMaxSurfaceWidth = SurfaceWidth;
	m_siMaxSurfaceHeight = SurfaceHeight;

	if ( m_pControllerSurfaceObj )
	{
		delete m_pControllerSurfaceObj;
		m_pControllerSurfaceObj = NULL;
	}

	m_pControllerSurfaceObj = new CControllerSurfaceObj();
	m_pControllerSurfaceObj->Create( m_siMaxSurfaceWidth, m_siMaxSurfaceHeight );

	Refresh();

	return;
}

void CControllerObj::BackGroundDrawOption( SI16 BackGroundDrawOption, SI16 Param1, SI16 Param2 )
{
	m_siBackGroundDrawOption = BackGroundDrawOption;
	m_siParam1 = Param1;
	m_siParam2 = Param2;

	return;
}

void CControllerObj::SetSurfaceWidth( SI16 siSurfaceWidht )
{
	m_siMaxSurfaceWidth = siSurfaceWidht;

	if ( m_pControllerSurfaceObj )
	{
		delete m_pControllerSurfaceObj;
		m_pControllerSurfaceObj = NULL;
	}

	m_pControllerSurfaceObj = new CControllerSurfaceObj();
	m_pControllerSurfaceObj->Create( m_siMaxSurfaceWidth, m_siMaxSurfaceHeight );

	Refresh();

	return;
}

void CControllerObj::SetSurfaceHeight( SI16 siSurfaceHeight )
{
	m_siMaxSurfaceHeight = siSurfaceHeight;

	if ( m_pControllerSurfaceObj )
	{
		delete m_pControllerSurfaceObj;
		m_pControllerSurfaceObj = NULL;
	}

	m_pControllerSurfaceObj = new CControllerSurfaceObj();
	m_pControllerSurfaceObj->Create( m_siMaxSurfaceWidth, m_siMaxSurfaceHeight );

	Refresh();

	return;
}
