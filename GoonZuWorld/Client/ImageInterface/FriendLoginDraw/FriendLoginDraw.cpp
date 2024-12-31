#include "FriendLoginDraw.h"
#include "EtcTool\EtcTool.h"

#include "../../Client/client.h"
extern cltCommonLogic* pclClient;

#define MOVEUP_PIXEL						5			// MOVEUP_PIXEL ��ŭ ���� �̹����� �ö�


//KHY - 0626 - ģ���α����˾� ��ġ ����.
#define FRIENDLOGINIMAGE_START_XPOS			920
#define FRIENDLOGINIMAGE_START_YPOS			643
//#define FRIENDLOGINIMAGE_START_XPOS			80
//#define FRIENDLOGINIMAGE_START_YPOS			643


// �ؽ�Ʈ�� ��µǱ� �����ϴ� ���� ����� ��ǥ
#define TEXT_DRAW_START_XPOS				30
#define TEXT_DRAW_START_YPOS				13

// �ؽ�Ʈ ��� ������ ũ��
#define TEXT_DRAW_WIDTH						116
#define TEXT_DRAW_HEIGHT					39

CFriendLoginDraw::CFriendLoginDraw()
{
	m_lpSurface = NULL;
	m_pImageBuffer = NULL;
	
	if ( g_graphics.CreateSurface16( &m_lpSurface, MAX_FRIENDLOGIN_WIDTH, MAX_FRIENDLOGIN_HEIGHT, TRUE, RGB16_TRANS ) == FALSE )
	{
		MsgBox(TEXT("CreateOffScreen Error, CDrawChatSurface"), TEXT("fdsfsdgadg"));
	}

	m_pImageBuffer = new RGB16[ MAX_FRIENDLOGIN_WIDTH * MAX_FRIENDLOGIN_HEIGHT * 2 ];

	/*
	if ( GP.CreateOffScreen8( m_lpSurface, MAX_FRIENDLOGIN_WIDTH, MAX_FRIENDLOGIN_HEIGHT ) == FALSE )
	{
		MsgBox(TEXT("CreateOffScreen Error, CDrawChatSurface"), TEXT("fdsfsdgadg"));
	}

	m_LoginImgBuffer = new BYTE[ MAX_FRIENDLOGIN_WIDTH * MAX_FRIENDLOGIN_HEIGHT * 2 ];
	m_TextEncBuffer = new BYTE[ MAX_FRIENDLOGIN_WIDTH * MAX_FRIENDLOGIN_HEIGHT * 2 ];
	*/

	m_pLoginSpr = pclClient->GetGlobalSpr(GIMG_FRIENDLOGIN);


	Initialize();
}

CFriendLoginDraw::~CFriendLoginDraw()
{	
	if( m_pImageBuffer )
	{
		delete [] m_pImageBuffer;
		m_pImageBuffer = NULL;
	}
	/*
	if ( m_LoginImgBuffer )
	{
		delete [] m_LoginImgBuffer;
		m_LoginImgBuffer = NULL;
	}
	
	if ( m_TextEncBuffer )
	{
		delete [] m_TextEncBuffer;
		m_TextEncBuffer = NULL;
	}
	*/

	if( m_lpSurface )
	{
		m_lpSurface->Release();
		m_lpSurface = NULL;
	}
}

void CFriendLoginDraw::Initialize()
{
	m_bShow = false;
	m_siFrameCount = 0;
	m_siContinueCount = 0;
	m_siCurrentImageYPos = 0;
	
	
	return;
}

void CFriendLoginDraw::Set( TCHAR *CharName )
{
	if ( CharName == NULL || _tcslen ( CharName ) < 0 )
	{
		return;
	}

	cltClient *pclclient = (cltClient *)pclClient;

	m_bShow = true;
	m_siFrameCount = 0;
	m_siContinueCount = 0;	
	m_siCurrentImageYPos = pclclient->GetScreenYSize() - 50; //((cltClient *)pclClient)->siScreenMode800X600YSize + ((cltClient *)pclClient)->siScreenModeYOffSet + 30 ;

	// �޸� ���� �ڵ� - by LEEKH
	if( m_lpSurface == NULL )			return;

	g_graphics.ClearSurface( m_lpSurface, RGB16_TRANS );

	if ( GP.LockSurface( m_lpSurface ) == TRUE )
	{

		//GP.FillScreen( COLOR_TRANS );

		GP.PutSpr(m_pLoginSpr, 0,0 , 0 );

		GP.UnlockSurface( m_lpSurface );
	}

	HDC hdc;
	RECT rect;
	
	if( m_lpSurface->GetDC(&hdc) == DD_OK)
	{
		HFONT hOldFont = (HFONT)SelectObject( hdc, pclClient->pclMessage->hFont );
		SetBkMode( hdc, TRANSPARENT );

		rect.left = TEXT_DRAW_START_XPOS ;
		rect.right = TEXT_DRAW_WIDTH - 1;
		rect.top = TEXT_DRAW_START_YPOS;
		rect.bottom = TEXT_DRAW_HEIGHT - 1;
		
		TCHAR TextBuffer[256 ] = TEXT("");
		TCHAR* pText = GetTxtFromMgr(1432);

		StringCchPrintf( TextBuffer, 256, pText, CharName );
		
		DrawText( hdc, TextBuffer, -1, &rect, DT_CENTER | DT_WORDBREAK );

		SelectObject( hdc, hOldFont );
		m_lpSurface->ReleaseDC(hdc);
	}

	if ( GP.LockSurface( m_lpSurface ) == TRUE )
	{
		if(m_pImageBuffer)
		{
			int size;
			g_graphics.EncodeXpr( m_pImageBuffer, 
				MAX_FRIENDLOGIN_WIDTH,
				MAX_FRIENDLOGIN_HEIGHT,
				RGB16_TRANS,
				&size );
		}
		GP.UnlockSurface( m_lpSurface );
	}


	//GP.GetImage( 0, 0, m_pLoginSpr->clHeader.siHRes, m_pLoginSpr->clHeader.siVRes, m_LoginImgBuffer );
	//GP.EncodeMpr( m_TextEncBuffer, m_LoginImgBuffer, m_pLoginSpr->clHeader.siHRes, m_pLoginSpr->clHeader.siVRes, COLOR_TRANS );


	
	return;
}

void CFriendLoginDraw::Action()
{
	if ( ! m_bShow )
	{
		return;
	}
	
	cltClient *pclclient = (cltClient *)pclClient;

	++m_siFrameCount;

	if ( m_siFrameCount % 3 == 0 )		// 3Frame ���� �α��� �˸� �̹����� �ö�
	{
		// ���� �ö�ͼ� �� �����ְ� ���� ������� �ϹǷ�...
		if ( m_siCurrentImageYPos + 50 < pclclient->GetScreenYSize() - 50 )
		{
			if ( m_siContinueCount++ > 50 )		// �̹����� �� �ö� �Ŀ��� 2~3�� ������ ���������� ������� �ϹǷ�...
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

void CFriendLoginDraw::Draw( SI32 XMovePos, SI32 YMovePos )
{
	if ( ! m_bShow )
	{
		return;
	}

	GP.PutXpr16(FRIENDLOGINIMAGE_START_XPOS + XMovePos, 
				m_siCurrentImageYPos + YMovePos,
				MAX_FRIENDLOGIN_WIDTH,
				MAX_FRIENDLOGIN_HEIGHT,
				m_pImageBuffer,
				RGB16_TRANS
				);

	/*
	// Draw �ϴ� �κ�
	GP.PutMpr8( FRIENDLOGINIMAGE_START_XPOS + XMovePos, m_siCurrentImageYPos + YMovePos, m_pLoginSpr->clHeader.siHRes, m_pLoginSpr->clHeader.siVRes, m_TextEncBuffer ,
			   PUT_SPR_SPR,TRUE);
   */
	
	return;
}