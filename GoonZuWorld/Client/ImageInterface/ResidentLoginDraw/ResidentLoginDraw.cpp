#include "ResidentLoginDraw.h"
#include "EtcTool\EtcTool.h"

#include "../../Client/client.h"
extern cltCommonLogic* pclClient;

#define MOVEUP_PIXEL						5			// MOVEUP_PIXEL 만큼 위로 이미지가 올라감

#define RESIDENTLOGINIMAGE_START_XPOS			80
#define RESIDENTLOGINIMAGE_START_YPOS			643

// 텍스트가 출력되기 시작하는 좌측 상단의 좌표
#define TEXT_DRAW_START_XPOS				30
#define TEXT_DRAW_START_YPOS				13

// 텍스트 출력 가능한 크기
#define TEXT_DRAW_WIDTH						116
#define TEXT_DRAW_HEIGHT					39


CResidentLoginDraw::CResidentLoginDraw()
{

	if ( g_graphics.CreateSurface16( &m_lpSurface, MAX_RESIDENTLOGIN_WIDTH, MAX_RESIDENTLOGIN_HEIGHT, TRUE, RGB16_TRANS ) == FALSE )
	{
		MsgBox(TEXT("CreateOffScreen Error, CDrawChatSurface"), TEXT("fdsfsdgadg"));
	}

	m_pImageBuffer = new RGB16[ MAX_RESIDENTLOGIN_WIDTH * MAX_RESIDENTLOGIN_HEIGHT * 2];

	m_pLoginSpr = pclClient->GetGlobalSpr(GIMG_RESIDENCELOGIN);

	Initialize();
}

CResidentLoginDraw::~CResidentLoginDraw()
{	
	if( m_lpSurface )
	{
		m_lpSurface->Release();
		m_lpSurface = NULL;
	}


	if( m_pImageBuffer ) {
		delete [] m_pImageBuffer;
		m_pImageBuffer = NULL;
	}

}

void CResidentLoginDraw::Initialize()
{
	m_bShow = false;
	m_siFrameCount = 0;
	m_siContinueCount = 0;
	m_siCurrentImageYPos = 0;
	
	
	return;
}

void CResidentLoginDraw::Set( TCHAR *CharName )
{
	if ( CharName == NULL || _tcslen ( CharName ) < 0 )
	{
		return;
	}

	cltClient *pclclient = (cltClient *)pclClient;

	m_bShow = true;
	m_siFrameCount = 0;
	m_siContinueCount = 0;	
	m_siCurrentImageYPos = pclclient->GetScreenYSize() - 50;

	// 메모리 보안 코드 - by LEEKH
	if( m_lpSurface == NULL )			return;

	g_graphics.ClearSurface( m_lpSurface, RGB16_TRANS );

	if ( GP.LockSurface( m_lpSurface ) == TRUE )
	{

		GP.PutSpr(m_pLoginSpr, 0, 0, 0 );
		GP.UnlockSurface( m_lpSurface );
	}

	HDC hdc;
	RECT rect;
	
	if( m_lpSurface->GetDC(&hdc) == DD_OK)
	{
		HFONT hOldFont = (HFONT)SelectObject( hdc, pclClient->pclMessage->hFont );
		SetBkMode( hdc, TRANSPARENT );
		
		rect.left = TEXT_DRAW_START_XPOS;
		rect.right = TEXT_DRAW_WIDTH - 1;
		rect.top = TEXT_DRAW_START_YPOS;
		rect.bottom = TEXT_DRAW_HEIGHT - 1;
		
		TCHAR TextBuffer[256 ] = TEXT("");
		TCHAR* pText = GetTxtFromMgr(1432);
		StringCchPrintf( TextBuffer, 256, pText, CharName );
		
		DrawText( hdc, TextBuffer, _tcslen( TextBuffer ), &rect, DT_CENTER );

		SelectObject( hdc, hOldFont );
		m_lpSurface->ReleaseDC(hdc);
	}

	{
		int size;
		if( GP.LockSurface( m_lpSurface ) == TRUE )
		{
			if(m_pImageBuffer)
			{
				g_graphics.EncodeXpr( m_pImageBuffer, 
									MAX_RESIDENTLOGIN_WIDTH,
									MAX_RESIDENTLOGIN_HEIGHT,
									RGB16_TRANS,
									&size );
			}
			GP.UnlockSurface( m_lpSurface );
		}
	}

	return;
}

void CResidentLoginDraw::Action()
{
	if ( ! m_bShow )
	{
		return;
	}

	cltClient *pclclient = (cltClient *)pclClient;
	
	++m_siFrameCount;

	if ( m_siFrameCount % 3 == 0 )		// 3Frame 마다 로그인 알림 이미지가 올라감
	{
		// 위로 올라와서 다 보여주고 나면 사라져야 하므로...
		if ( m_siCurrentImageYPos + 50 < pclclient->GetScreenYSize() - 50 )
		{
			if ( m_siContinueCount++ > 50 )		// 이미지가 다 올라간 후에도 2~3초 정도는 지속적으로 보여줘야 하므로...
			{
				m_bShow = false;
				m_siContinueCount = 0;
				m_siCurrentImageYPos = pclclient->GetScreenYSize() - 50;
			}			
		}
		else
		{
			m_siCurrentImageYPos -= MOVEUP_PIXEL;
		}
		m_siFrameCount = 0;
	}

	return;
}

void CResidentLoginDraw::Draw( SI32 XMovePos, SI32 YMovePos )
{
	if ( ! m_bShow )
	{
		return;
	}

	GP.PutXpr16(RESIDENTLOGINIMAGE_START_XPOS + XMovePos, 
		        m_siCurrentImageYPos + YMovePos,
				MAX_RESIDENTLOGIN_WIDTH,
				MAX_RESIDENTLOGIN_HEIGHT,
				m_pImageBuffer,
				RGB16_TRANS
				);
	
	return;
}