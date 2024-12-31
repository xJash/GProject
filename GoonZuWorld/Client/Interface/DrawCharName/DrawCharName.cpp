#include "DrawCharName.h"
#include "DrawCharNameSurface.h"

#include "../../Client/client.h"
#include "../../Lib/NGraphics/Graphics.h"

extern cltCommonLogic* pclClient;
CDrawCharName::CDrawCharName()
{
	cltClient *pclclient = (cltClient *)pclClient;

	if( pclClient->siServiceArea == ConstServiceArea_Japan )
	{
		if( pclClient->IsCountrySwitch( Switch_NONATIALIASED_QUALITY ) ){
			m_hNameFont = CreateFont(12, 0, 0, 0, 0, FALSE, FALSE, 0, pclclient->GetCharSet(), 0, 0, 0, NONANTIALIASED_QUALITY, TEXT("����"));
		}
		else {
			m_hNameFont = CreateFont(12, 0, 0, 0, 0, FALSE, FALSE, 0, pclclient->GetCharSet(), 0, 0, 0, 0, TEXT("����"));
		}        
	}
	else
	{
		if( pclClient->IsCountrySwitch( Switch_NONATIALIASED_QUALITY ) ){
			m_hNameFont = CreateFont(13, 0, 0, 0, 0, FALSE, FALSE, 0, pclclient->GetCharSet(), 0, 0, NONANTIALIASED_QUALITY, 0, TEXT("Tahoma"));
		}
		else {
			m_hNameFont = CreateFont(13, 0, 0, 0, 0, FALSE, FALSE, 0, pclclient->GetCharSet(), 0, 0, 0, 0, TEXT("Tahoma"));
		}
	}

	m_pTextBuffer = NULL;

	Initialize();
}

CDrawCharName::~CDrawCharName()
{
	Destroy();
	if(m_hNameFont)
		DeleteObject(m_hNameFont);
}

void CDrawCharName::Initialize()
{	
	if( m_pTextBuffer ) delete [] m_pTextBuffer;
	m_pTextBuffer = NULL;


	m_siWidth = 0;
	m_siHeight = 0;


	m_siSchoolImageWidth = 0;

	m_bSet			= false;
	m_bSchool		= false;
	m_bForceDraw	= false;

	ZeroMemory(m_szOldMakeCharName, sizeof(m_szOldMakeCharName));

	m_siOldEmblem = 0;

	return;
}

void CDrawCharName::Destroy()
{


	if( m_pTextBuffer ) {
		delete [] m_pTextBuffer;
		m_pTextBuffer = NULL;
	}

	m_bSet = false;

	return;
}

void CDrawCharName::Set( CDrawCharNameSurface *pDrawCharNameSurface, TCHAR *text, TSpr* pSchoolSprImageList, SI16 SchoolSprImageListIndex, SI16 sisex, UI08 gmmode,SI32 guildicon,TSpr*GuildImageList, SI32 siEmblemIndex, TSpr* psprEmblem )
{
	if ( false == m_bForceDraw )
	{
		if ( ((m_siOldEmblem == siEmblemIndex) && (_tcscmp(m_szOldMakeCharName, text) == 0)) || (_tcscmp( text, TEXT("") ) == 0) )
		{
			return;
		}
	}

	StringCchCopy( m_szOldMakeCharName, 128, text );
	m_siOldEmblem = siEmblemIndex;

	LPDIRECTDRAWSURFACE7 lpSurface = NULL;

	lpSurface = pDrawCharNameSurface->GetCharNameSurface();

	// �޸� ���� �ڵ� - by LEEKH
	if( lpSurface == NULL )								return;

	if( m_pTextBuffer == NULL ) m_pTextBuffer = new RGB16[ ( MAX_CHARNAME_SURFACE_WIDTH + 10 ) * ( MAX_CHARNAME_SURFACE_HEIGHT + 10 ) ];
	if( m_pTextBuffer == NULL)	return;

	g_graphics.ClearSurface( lpSurface, RGB16_TRANS );


	RECT rect; // , BackRect;
	HDC hdc;
	SI32 calcWidth = 0;

	SI32 startX = 0;
	SI32 endX = MAX_CHARNAME_SURFACE_WIDTH;

	if ( pSchoolSprImageList )
	{
		startX = pSchoolSprImageList->GetXSize();
		m_bSchool = true;
		m_siSchoolImageWidth = pSchoolSprImageList->GetXSize();
		endX = MAX_CHARNAME_SURFACE_WIDTH ;
	}
	if ( guildicon >= 0 && GuildImageList )
	{
		endX = MAX_CHARNAME_SURFACE_WIDTH - GuildImageList->GetXSize();
		if ( startX > 0 )
		{
			startX -= GuildImageList->GetXSize() / 2;
		}
	}
	if( lpSurface->GetDC(&hdc) == DD_OK)  
	{
		HFONT hOldFont = (HFONT)SelectObject( hdc, m_hNameFont ); 
		SetBkMode( hdc, TRANSPARENT );


		rect.left = startX;		
		rect.right = endX - 1;
		rect.top = 10;//0;[����]
		rect.bottom = MAX_CHARNAME_SURFACE_HEIGHT - 1;			


		m_siWidth = rect.right - rect.left;

		SetTextColor( hdc, RGB(68,68,68));

		// DT_CALCRECT <-- �� �÷��׸� ����ؼ� ���Ǿ� ���� ��Ȯ�� rect �� ����
		m_siHeight = DrawText( hdc, text, _tcslen(text), &rect, DT_CENTER|DT_CALCRECT );

		if ( m_siHeight +2  > MAX_CHARNAME_SURFACE_HEIGHT )
		{
			SelectObject( hdc, hOldFont );
			lpSurface->ReleaseDC(hdc);
			return;
		}

		calcWidth = rect.right - rect.left;
		//m_siWidth = rect.right - rect.left + pSchoolSprImageList->GetXSize();
		if ( m_siWidth > MAX_CHARNAME_SURFACE_WIDTH )
		{
			SelectObject( hdc, hOldFont );
			lpSurface->ReleaseDC(hdc);
			return;
		}			

		//		m_siHeight = DrawText( hdc, text, _tcslen(text), &rect, DT_CENTER|DT_WORDBREAK );


		//if ( m_siHeight < pSchoolSprImageList->GetYSize() )
		//{
		//	m_siHeight = pSchoolSprImageList->GetYSize();
		//}

		//if ( pSchoolSprImageList->GetYSize() > MAX_CHARNAME_SURFACE_HEIGHT )
		//{
		//	SelectObject( hdc, hOldFont );
		//	lpSurface->ReleaseDC(hdc);
		//	return;
		//}

		// �»�� �׵θ��� ���� ���� ���

		rect.left = startX;		
		rect.right = endX - 3;
		rect.top = 10;//0;[����]
		rect.bottom = MAX_CHARNAME_SURFACE_HEIGHT - 3;			

		//		DrawText( hdc, text, _tcslen(text), &rect, DT_CENTER|DT_WORDBREAK|DT_CALCRECT );
		DrawText( hdc, text, _tcslen(text), &rect, DT_CENTER|DT_WORDBREAK );



		// ���� �׵θ�
		rect.left = startX + 2;	 	 
		rect.right = endX - 1;
		rect.top = 10;//0;[����]
		rect.bottom = MAX_CHARNAME_SURFACE_HEIGHT - 3;			

		//	DrawText( hdc, text, _tcslen(text), &rect, DT_CENTER|DT_WORDBREAK|DT_CALCRECT );
		DrawText( hdc, text, _tcslen(text), &rect, DT_CENTER|DT_WORDBREAK );



		// ���ϴ� �׵θ�
		rect.left = startX;	 	
		rect.right = endX - 3;
		rect.top = 12;//2;[����]
		rect.bottom = MAX_CHARNAME_SURFACE_HEIGHT - 1;			

		//	DrawText( hdc, text, _tcslen(text), &rect, DT_CENTER|DT_WORDBREAK|DT_CALCRECT );
		DrawText( hdc, text, _tcslen(text), &rect, DT_CENTER|DT_WORDBREAK );


		// ���ϴ� �׵θ�
		rect.left = startX + 2;	 	
		rect.right = endX - 1;
		rect.top = 12;//2;[����]
		rect.bottom = MAX_CHARNAME_SURFACE_HEIGHT - 1;			

		//	DrawText( hdc, text, _tcslen(text), &rect, DT_CENTER|DT_WORDBREAK|DT_CALCRECT );
		DrawText( hdc, text, _tcslen(text), &rect, DT_CENTER|DT_WORDBREAK );


		//  @ ���� @
		// �ؽ�Ʈ ���ڻ� rgb���� ���� 250 ~ 255 ������.
		SI32 color = rand()%6;
		SetTextColor( hdc, RGB(250+color, 255-color, 250+(color>>1)));
		//SetTextColor( hdc, RGB(255, 255, 255));

		// �˸��� ���� ���
		rect.left = startX + 1;	 	
		rect.right = endX - 2;
		rect.top = 11;//1;[����]
		rect.bottom = MAX_CHARNAME_SURFACE_HEIGHT - 2;			

		//	DrawText( hdc, text, _tcslen(text), &rect, DT_CENTER|DT_WORDBREAK|DT_CALCRECT );
		DrawText( hdc, text, _tcslen(text), &rect, DT_CENTER|DT_WORDBREAK );

		SelectObject( hdc, hOldFont );
		lpSurface->ReleaseDC(hdc);		

		if ( GP.LockSurface( lpSurface ) == TRUE )
		{ 
			SI32 xIndent = 0;

			//if ( pSchoolSprImageList )
			//{
			//	GP.PutSpr(pSchoolSprImageList,(m_siWidth/2 - calcWidth/2), 0, SchoolSprImageListIndex );
			//	xIndent += pSchoolSprImageList->GetXSize();
			//}
			//if ( guildicon >= 0 && GuildImageList )
			//{
			//	GP.PutSpr(GuildImageList,(  m_siWidth/2 + calcWidth/2 )+xIndent , 0, guildicon );
			//}

			if ( guildicon >= 0 && GuildImageList )
			{
				if ( pSchoolSprImageList )
				{
					GP.PutSpr(pSchoolSprImageList,(m_siWidth/2 - calcWidth/2)-startX , 10, SchoolSprImageListIndex );
					xIndent += pSchoolSprImageList->GetXSize();
				}

				GP.PutSpr(GuildImageList,(  m_siWidth/2 + calcWidth/2 ) + xIndent - startX , 10, guildicon );

				// ������� ���� - ����
				if ( (psprEmblem) && (0 <= siEmblemIndex) )
				{
					GP.PutSprAlpha( psprEmblem, (m_siWidth/2 - calcWidth/2) - (psprEmblem->GetXSize()/2) - startX, 3, 15, siEmblemIndex );
				}
			}
			else
			{
				if ( pSchoolSprImageList )
				{
					GP.PutSpr(pSchoolSprImageList,(m_siWidth/2 - calcWidth/2), 10, SchoolSprImageListIndex );
					xIndent += pSchoolSprImageList->GetXSize();
				}

				// ������� ���� - ����
				if ( (psprEmblem) && (0 <= siEmblemIndex) )
				{
					GP.PutSprAlpha( psprEmblem, (m_siWidth/2 - calcWidth/2) - (psprEmblem->GetXSize()/2), 3, 15, siEmblemIndex );
				}
			}

			GP.UnlockSurface( lpSurface );
		}
	}


	{
		int size;
		if ( GP.LockSurface( lpSurface ) == TRUE )
		{
			if(m_pTextBuffer)
			{
				g_graphics.EncodeXpr( m_pTextBuffer, 
					MAX_CHARNAME_SURFACE_WIDTH + 10,
					MAX_CHARNAME_SURFACE_HEIGHT + 10,
					RGB16_TRANS,
					&size );
			}
			GP.UnlockSurface( lpSurface );
		}
	}

	m_bSet = true;



	//else  
	//{
	//	if( lpSurface->GetDC(&hdc) == DD_OK)
	//	{
	//		HFONT hOldFont = (HFONT)SelectObject( hdc, m_hNameFont );

	//		SetBkMode( hdc, TRANSPARENT ); 

	//		// ��� ���

	//		SetTextColor( hdc, RGB(68,68,68));





	//		/////////////// �����׵θ� ��۾�///////////////////

	//		//�»�


	//		rect.left = 0; 
	//		rect.right = MAX_CHARNAME_SURFACE_WIDTH - 3;
	//		rect.top = 0;
	//		rect.bottom = MAX_CHARNAME_SURFACE_HEIGHT - 3;



	//		m_siHeight = DrawText( hdc, text, _tcslen(text), &rect, DT_CENTER|DT_WORDBREAK );
	//		if ( m_siHeight +2  > MAX_CHARNAME_SURFACE_HEIGHT )
	//		{
	//			SelectObject( hdc, hOldFont );
	//			lpSurface->ReleaseDC(hdc);
	//			return;
	//		}

	//		// ���
	//		rect.left = 2; 
	//		rect.right = MAX_CHARNAME_SURFACE_WIDTH - 1;
	//		rect.top = 0;
	//		rect.bottom = MAX_CHARNAME_SURFACE_HEIGHT - 1;

	//		DrawText( hdc, text, _tcslen(text), &rect, DT_CENTER|DT_WORDBREAK );
	//	
	//		//����
	//		rect.left = 0; 
	//		rect.right = MAX_CHARNAME_SURFACE_WIDTH - 3;
	//		rect.top = 2;
	//		rect.bottom = MAX_CHARNAME_SURFACE_HEIGHT - 3;

	//		DrawText( hdc, text, _tcslen(text), &rect, DT_CENTER|DT_WORDBREAK );
	//	
	//		//����
	//		rect.left = 2; 
	//		rect.right = MAX_CHARNAME_SURFACE_WIDTH - 1;
	//		rect.top = 2;
	//		rect.bottom = MAX_CHARNAME_SURFACE_HEIGHT - 1;

	//		 DrawText( hdc, text, _tcslen(text), &rect, DT_CENTER|DT_WORDBREAK );
	//		

	//		// �˸��� ���� ��� (���)
	//		SetTextColor( hdc, RGB(255, 255, 255));

	//		rect.left = 1;
	//		rect.top = 1;
	//		rect.right = MAX_CHARNAME_SURFACE_WIDTH - 2;
	//		rect.bottom = MAX_CHARNAME_SURFACE_HEIGHT - 2;

	//		
	//		m_siWidth = rect.right - rect.left ;

	//		// DT_CALCRECT <-- �� �÷��׸� ����ؼ� ���Ǿ� ���� ��Ȯ�� rect �� ����
	//		m_siHeight = DrawText( hdc, text, _tcslen(text), &rect, DT_CENTER|DT_WORDBREAK|DT_CALCRECT );			calcWidth = rect.right - rect.left;


	//		m_siHeight = DrawText( hdc, text, _tcslen(text), &rect, DT_CENTER|DT_WORDBREAK);

	//		//DrawText( hdc, text, _tcslen(text), &rect, DT_CENTER|DT_WORDBREAK|DT_CALCRECT );

	//		SelectObject( hdc, hOldFont );
	//		lpSurface->ReleaseDC(hdc);
	//		// ��� ��ũ ����ֱ�
	//		//SI32 iconpos = MAX_CHARNAME_SURFACE_WIDTH - ( (MAX_CHARNAME_SURFACE_WIDTH - rect.right ) / 2 );
	//		if ( guildicon >= 0 && GuildImageList )
	//		{
	//			if ( GP.LockSurface( lpSurface ) == TRUE )
	//			{ 
	//				
	//				GP.PutSpr(GuildImageList,(  m_siWidth/2 - calcWidth/2 )  , 0, guildicon );

	//				//GP.PutSpr(GuildImageList, iconpos , 0, guildicon );

	//				GP.UnlockSurface( lpSurface );
	//			}
	//		}
	//	}

	//	{
	//		int size;
	//		if ( GP.LockSurface( lpSurface ) == TRUE )
	//		{
	//			g_graphics.EncodeXpr( m_pTextBuffer, 
	//				MAX_CHARNAME_SURFACE_WIDTH + 10,
	//				MAX_CHARNAME_SURFACE_HEIGHT + 10,
	//				RGB16_TRANS,
	//				&size );
	//			GP.UnlockSurface( lpSurface );
	//		}
	//	}
	//	m_bSet = true;
	//	m_bSchool = false;
	//}

	m_bForceDraw = false;

	return;
}

void CDrawCharName::Draw( SI32 si32CenterXPos, SI32 si32CenterYPos )
{	

	int x;

	if ( ! m_bSet )
	{
		return;
	}

	if ( m_bSchool )
	{
		x = si32CenterXPos - m_siWidth / 2 - m_siSchoolImageWidth / 2;
	}
	else
	{
		x = si32CenterXPos -m_siWidth / 2;
	}


//	GP.PutXpr16( x, si32CenterYPos,
//		MAX_CHARNAME_SURFACE_WIDTH + 10, MAX_CHARNAME_SURFACE_HEIGHT + 10,
//		m_pTextBuffer, RGB16_TRANS );

	if( m_pTextBuffer )
	{
		// By LEEKH - 2007.10.03
		// ��������� ���� �ڵ� - ĳ������ �̸��� ���������� ��´�.(������)
		GP.PutXpr16A( x, si32CenterYPos, MAX_CHARNAME_SURFACE_WIDTH + 10, MAX_CHARNAME_SURFACE_HEIGHT + 10,
					m_pTextBuffer, 14, RGB16_TRANS );
	}

	return;
}

void CDrawCharName::SetForceDraw( const bool bForceDraw )
{
	m_bForceDraw = bForceDraw;
}

bool CDrawCharName::GetForceDraw( void ) const
{
	return m_bForceDraw;
}