//---------------------------------
// 2003/6/9 ���°�
//---------------------------------

#include <Graphic.h>
#include <Graphic_Capsule.h>

#include "Help.h"
#include "../../CommonLogic/CommonLogic.h"
#include "../../Client/GlobalImgFile/GlobalImgFile.h"
#include "../../Client/FontManager/FontManager.h"

extern cltCommonLogic* pclClient;


//----------------------------------------------------
// cltHelp
//----------------------------------------------------
cltHelp::cltHelp(TCHAR* sztitle, SI32 six, SI32 siy)
{
	SI32 i;
	SI32 ynum;
	HDC hdc;
	SIZE size;
	SI32 font ;
	lpSurface = NULL;

	LastUpdateFrame	= 0;	

	size.cx = 0;
	size.cy = 0;

	ShowSize.cx = 0;
	ShowSize.cy = 0;

	siX			= six;
	siY			= siy;

	MStrCpy( szTitle, sztitle, MAX_HELP_TILE_LENGTH );

	if( g_graphics.CreateSurface16( &lpSurface, HELP_SURFACE_XSIZE, HELP_SURFACE_YSIZE, TRUE, RGB16_TRANS ) == TRUE)
	{
		g_graphics.ClearSurface( lpSurface, RGB16_TRANS );


		//------------------------------
		// �ؽ�Ʈ�� ũ�⸦ ���´�.
		//------------------------------
		if(lpSurface->GetDC(&hdc) == DD_OK)
		{
			// ��Ʈ�� �����Ѵ�. 
			HFONT hFont;
			if ( pclClient->siServiceArea == ConstServiceArea_English	||
				pclClient->siServiceArea == ConstServiceArea_NHNChina	||
				pclClient->siServiceArea == ConstServiceArea_EUROPE
			)
			{
				hFont = g_FontManager.SetFont( 13, TEXT("Tahoma") );
			}
			else
			{
				hFont = g_FontManager.SetFont();
			}
			HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);

			GetTextExtentPoint32(hdc, szTitle, _tcslen(szTitle), &size);

			SelectObject(hdc, hOldFont);

			lpSurface->ReleaseDC(hdc);
		}

		//-----------------------------
		// HelpPannel�� ����Ѵ�. 
		//-----------------------------
		SI32 partxnum = size.cx / 16;
		if(size.cx % 16)partxnum++;

		SI32 partynum = size.cy / 16;
		if(size.cy % 16)partynum++;

		TSpr* pspr = pclClient->GetGlobalSpr(GIMG_HELPPANNEL);

		if(GP.LockSurface(lpSurface) == TRUE)
		{

			// ��� 
			for(i = 0;i < partxnum + 2;i++)
			{
				if(i == 0)
				{
					// ���� ���. 
					font = 0;
					GP.PutSpr(pspr,i*16, 0, font);
				}
				else if(i == (partxnum +1))
				{
					// ������ ���. 
					font = 1;
					GP.PutSpr(pspr,i*16, 0, font);

				}
				else
				{
					font = 10  + (rand() % 2);
					GP.PutSpr(pspr,i*16, 0,font);
				}
			}

			// �ߴ�. 
			for(ynum = 0;ynum < partynum; ynum++)
			{
				for(i = 0;i < partxnum+2;i++)
				{
					if(i == 0)
					{
						// ���� ���. 
						font = 20;
						GP.PutSpr(pspr,i*16, 16 + ynum*16,font);
					}
					else if(i == (partxnum +1))
					{
						// ������ ���. 
						font = 22;
						GP.PutSpr(pspr,i*16, 16 + ynum*16,font);
						
					}
					else
					{
						font = 21;
						GP.PutSpr(pspr,i*16, 16 + ynum*16, font);
					}
					
				}

			}

			// �ϴ� 
			for(i = 0;i < partxnum + 2;i++)
			{
				if(i == 0)
				{
					// ���� �ϴ�. 
					font = 2;
					GP.PutSpr(pspr,i*16, (partynum+1)*16,font);
				}
				else if(i == (partxnum +1))
				{
					// ������ �ϴ�. 
					font = 3;
					GP.PutSpr(pspr,i*16, (partynum+1)*16,font);
				}
				else
				{
					font = 30  + (rand() % 2);
					GP.PutSpr(pspr,i*16, (partynum+1)*16,font);
				}
			}

			GP.UnlockSurface(lpSurface);
		}

		// �ؽ�Ʈ�� ����� ���Ѵ�. 
		ShowSize.cx = (partxnum + 2) * 16;
		ShowSize.cy	= (partynum + 2) * 16;

		//------------------------------
		// �ؽ�Ʈ�� ����Ѵ�. 
		//-----------------------------
		if(lpSurface->GetDC(&hdc) == DD_OK)
		{
			// ��Ʈ�� �����Ѵ�. 
			HFONT hFont;
			if ( pclClient->siServiceArea == ConstServiceArea_English	||
				pclClient->siServiceArea == ConstServiceArea_NHNChina	||
				pclClient->siServiceArea == ConstServiceArea_EUROPE
			)
			{
				hFont = g_FontManager.SetFont( 13, TEXT("Tahoma") );
			}
			else
			{
				hFont = g_FontManager.SetFont();
			}

			HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);

			SetTextColor( hdc, BLANK_TEXT_COLOR);
			SetBkMode(hdc, TRANSPARENT);

			// Ÿ��Ʋ�� ����. 
			if(size.cx <= HELP_SURFACE_XSIZE && size.cy <= HELP_SURFACE_YSIZE)
			{
				TextOut(hdc, ShowSize.cx/2 - size.cx/2, ShowSize.cy/2 - size.cy/2,
					szTitle, _tcslen(szTitle) );

			}

			SelectObject(hdc, hOldFont);

			lpSurface->ReleaseDC(hdc);
		}

	
	}

	

	
}

cltHelp::~cltHelp()
{
	if(lpSurface)
	{
		lpSurface->Release();
		lpSurface = NULL;
	}
}

BOOL cltHelp::Draw(LPDIRECTDRAWSURFACE7 lpdstsurface)
{

	RECT rect;
	rect.left	= 0;
	rect.right	= ShowSize.cx;
	rect.top	=  0;
	rect.bottom	= ShowSize.cy;

	
	// ������ ������ �����. 
	if(siX > GP.GetScreenXsize() - 80)return FALSE;
	if(siY > GP.GetScreenYsize() - 40)return FALSE;
	if(siX + ShowSize.cx < 80)return FALSE;
	if(siY + ShowSize.cy < 40)return FALSE;

	// ���� �ð��� ������ �����Ѵ�. 
	if(TABS(pclClient->GetFrame() - LastUpdateFrame) > 2)return FALSE;

	if(siX < 0)siX = 0;
	if(siX + ShowSize.cx >= GP.GetScreenXsize())siX  = GP.GetScreenXsize() - ShowSize.cx - 1;

	if(siY < 0)siY = 0;
	if(siY + ShowSize.cy >= GP.GetScreenYsize())siY  = GP.GetScreenYsize() - ShowSize.cy - 1;


	lpdstsurface->BltFast(siX, siY, lpSurface, &rect, DDBLTFAST_SRCCOLORKEY);

	return TRUE;
}

//--------------------------------------------------
// cltHelpManager
//--------------------------------------------------
cltHelpManager::cltHelpManager()
{
	SI32 i;

	for(i = 0;i < MAX_HELP_NUMBER;i++)
	{
		pclHelp[i] = NULL;
	}
}


cltHelpManager::~cltHelpManager()
{
	SI32 i;

	for(i = 0; i < MAX_HELP_NUMBER;i++)
	{
		if(pclHelp[i])
		{
			delete pclHelp[i];
			pclHelp[i] = NULL;
		}
	}
}

// ���ο� Help�� �߰��Ѵ�. 
BOOL cltHelpManager::Add(TCHAR* sztitle, SI32 six, SI32 siy)
{
	SI32 i;

	for(i = 0;i < MAX_HELP_NUMBER;i++)
	{
		if(pclHelp[i] == NULL)
		{
			pclHelp[i] = new cltHelp(sztitle, six  + HELP_OFFSETX , siy + HELP_OFFSETY);
			pclHelp[i]->LastUpdateFrame = pclClient->GetFrame();
			return TRUE;
		}
	}

	return FALSE;
}

// sztitle�� ���� Help�� �̹� �����ϴ��� Ȯ���Ѵ�.
SI32 cltHelpManager::GetHelp(TCHAR* sztitle)
{
	SI32 i;

	for(i = 0;i < MAX_HELP_NUMBER;i++)
	{
		if(pclHelp[i])
		{
			if(_tcscmp(pclHelp[i]->szTitle, sztitle) == 0)
			{
				return i;
			}
		}
	}

	return -1;
}

// ȭ�鿡 ����Ѵ�.
BOOL cltHelpManager::Draw(LPDIRECTDRAWSURFACE7 lpdstsurface)
{
	SI32 i;
	for(i = 0;i < MAX_HELP_NUMBER;i++)
	{
		if(pclHelp[i])
		{
			// ��� ������ ������ ����� �����Ѵ�.
			if(pclHelp[i]->Draw(lpdstsurface) == FALSE)
			{
				delete pclHelp[i];
				pclHelp[i] = NULL;
			}

		}
	}

	return TRUE;
}

void cltHelpManager::SetPos(SI32 ref, SI32 x, SI32 y)
{
	if(pclHelp[ref])
	{
		pclHelp[ref]->LastUpdateFrame = pclClient->GetFrame();
		pclHelp[ref]->siX = x + HELP_OFFSETX;
		pclHelp[ref]->siY = y+ HELP_OFFSETY;
	}
}

void cltHelpManager::DeleteAll()
{
	SI32 i;

	for(i = 0; i < MAX_HELP_NUMBER;i++)
	{
		if(pclHelp[i])
		{
			delete pclHelp[i];
			pclHelp[i] = NULL;
		}
	}

}