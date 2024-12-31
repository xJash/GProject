//---------------------------------
// 2003/9/21 ���°�
//---------------------------------

#include <Graphic.h>
#include "EtcTool\EtcTool.h"

// �׷��� ���̺귯�� ��ü 
cltGrp clGrp;


cltGrp::cltGrp()
{
	ZeroMemory(this, sizeof(cltGrp));

	ScreenMode  = MODE_GRAPHICS800_600;
    ScreenXsize = 800;
    ScreenYsize = 600;
    ColorDepth  = 8;
	
	SurfaceWidth = ScreenXsize;
	SurfaceHeight = ScreenYsize;

	// Surface�� ��� �ִ°� ?
	bLockSwitch		=	false;

	nDisplayModes	=	0;

	lpDD7 = NULL;
	lpDDSPrimary = NULL;
	lpDDSBack			= NULL;
	lpDDSConvertSurface = NULL;

	lpClipper			= NULL;
	

}

BOOL cltGrp::Error(TCHAR * szCaption)
{
	TCHAR buffer[256];
	TCHAR text[128];
	DWORD errcode = GetLastError();
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, errcode, 0, buffer,  128, NULL);
	StringCchPrintf(text, 128, TEXT("ErrorCode=%d Message=%s"), errcode, buffer);
	MsgBox(text, szCaption);

	return TRUE;
}
 
// ������ ������ ���´�. 
void cltGrp::GetSprRandPos8TH(int x, int y, int xsize, int ysize, unsigned char *image, SI32* pgetnum, POINT* ppoint)
{
	int i, j,index=0;
	UI08 *vidptr=Screen8+y*SurfaceWidth + x;

	SI32 maxnum = *pgetnum;
	*pgetnum = 0;

	for(i = 0;i < ysize;i++)
	{
		j = 0;

		while(j < xsize)
		{
			if(image[index]==COLOR_TRANS)
			{
				index++;
				j+=image[index];
				index++;
			}
			else
			{
				if(rand() % 100 == 0 && (*pgetnum) < maxnum && i > 115)
				{
					ppoint[*pgetnum].x = x + j;
					ppoint[*pgetnum].y = y + i;
					(*pgetnum)++;
				}

				index++;
				j++;
			}
		}
		vidptr+=SurfaceWidth;
	}
}

// ������ ������ ���´�. 
void cltGrp::GetSprRandPos8RTH(int x, int y, int xsize, int ysize, unsigned char *image, SI32* pgetnum, POINT* ppoint)
{
	int i, j,index=0;
	UI08 *vidptr=Screen8+y*SurfaceWidth + x;

	SI32 maxnum = *pgetnum;
	*pgetnum = 0;

	for(i = 0;i < ysize;i++)
	{
		j = 0;

		while(j < xsize)
		{
			if(image[index]==COLOR_TRANS)
			{
				index++;
				j+=image[index];
				index++;
			}
			else
			{
				if(rand() % 100 == 0 && (*pgetnum) < maxnum && i > 115 )
				{
					ppoint[*pgetnum].x = x + xsize-j-1;
					ppoint[*pgetnum].y = y + i;
					(*pgetnum)++;
				}

				index++;
				j++;
			}
		}
		vidptr+=SurfaceWidth;
	}
}


// ������ ������ ���´�. 
void cltGrp::GetSprRandPos8T(int x, int y, int xsize, int ysize, unsigned char *image, SI32* pgetnum, POINT* ppoint)
{
	int i, j,index=0;
	UI08 *vidptr=Screen8+y*SurfaceWidth + x;

	SI32 maxnum = *pgetnum;
	*pgetnum = 0;

	 for(i = 0;i < ysize;i++)
	 {
		j = 0;

		while(j < xsize)
		{
			if(image[index]==COLOR_TRANS)
			{
			   index++;
			   j+=image[index];
			   index++;
			}
			else
			{
				if(rand() % 200 == 0 && (*pgetnum) < maxnum)
				{
					ppoint[*pgetnum].x = x + j;
					ppoint[*pgetnum].y = y + i;
					(*pgetnum)++;
				}

			   index++;
			   j++;
			}
		}
		vidptr+=SurfaceWidth;
	 }
}

// ������ ������ ���´�. 
void cltGrp::GetSprRandPos8RT(int x, int y, int xsize, int ysize, unsigned char *image, SI32* pgetnum, POINT* ppoint)
{
	int i, j,index=0;
	UI08 *vidptr=Screen8+y*SurfaceWidth + x;

	SI32 maxnum = *pgetnum;
	*pgetnum = 0;

	 for(i = 0;i < ysize;i++)
	 {
		j = 0;

		while(j < xsize)
		{
			if(image[index]==COLOR_TRANS)
			{
			   index++;
			   j+=image[index];
			   index++;
			}
			else
			{
				if(rand() % 200 == 0 && (*pgetnum) < maxnum)
				{
					ppoint[*pgetnum].x = x + xsize-j-1;
					ppoint[*pgetnum].y = y + i;
					(*pgetnum)++;
				}

			   index++;
			   j++;
			}
		}
		vidptr+=SurfaceWidth;
	 }
}


HRESULT cltGrp::BltFast(DWORD surface,  DWORD dwX,  DWORD dwY,                            
                        LPDIRECTDRAWSURFACE7 lpDDSrcSurface,  LPRECT lpSrcRect, DWORD dwTrans )
{

	switch(surface)
	{

	   case SURFACE_PRIMARY:
		   if( lpDDSPrimary )
		     return lpDDSPrimary->BltFast(dwX, dwY, lpDDSrcSurface, lpSrcRect, dwTrans); 
		  break;

	   case SURFACE_BACK:
		   if( lpDDSBack )
		     return lpDDSBack->BltFast(dwX, dwY, lpDDSrcSurface, lpSrcRect, dwTrans); 
		  break;

	   default:
		   MsgBox(TEXT("BltFast"), TEXT("fsd3fdf"));
		   break;
	}

	return 0;

}

BOOL cltGrp::ClearSurface(LPDIRECTDRAWSURFACE7 pSurface)
{
	DDBLTFX ddbltfx;
	ZeroMemory( &ddbltfx, sizeof(ddbltfx) );
	ddbltfx.dwSize      = sizeof(ddbltfx);
	ddbltfx.dwFillColor = 0;
	
	if (pSurface) 
	{
		return pSurface->Blt( NULL, NULL, NULL, DDBLT_COLORFILL, &ddbltfx );
	}
	
	return FALSE;
}


void cltGrp::UpdateScreen( HWND hwnd, LPDIRECTDRAWSURFACE7 pSurface, 
						   SI32 xsize, SI32 ysize, SI32 xindent, SI32 yindent, 
						   SI32 srcstartx, SI32 srcstarty, bool bwaitrefresh, 
						   SI32 screenXSize, SI32 screenYSize , bool bWebDlg, HWND hWebDlg, 
						   bool bNewFullScreen)
{

	DWORD					dwTrans  = DDBLT_WAIT;
	LPDIRECTDRAWCLIPPER		pClipper = NULL;

	if(pSurface == NULL)
	{
		return ;
	}	

	// �����̰� �ӽ÷� �־���. �� �� �� 
	if(IsIconic(hwnd) == TRUE) return;


	if( g_graphics.IsWindowed() ) {

		HDC destHdc;
		HDC hdc;

		RECT rect;
		GetClientRect( hwnd, &rect );

		// ���� Ŭ���̾�Ʈ ��ǥ 2���� ��ũ�� ��ǥ�� �����Ѵ�.
		if(ClientToScreen( hwnd, (POINT*) &rect )	== FALSE) return; 
		if(ClientToScreen( hwnd, (POINT*) &rect + 1)== FALSE) return; 

		// �����̰� �ӽ÷� �־���.
		if(rect.bottom <-30000 ||rect.left<-30000 || rect.right <-30000 || rect.top<-30000) return;

		rect.left += xindent;
		rect.top  += yindent;

		// ���� �� ������ �̹����� �׻� ������ ������� �����ϰ� �Ѵ�. 
		rect.right = rect.left + xsize;
		rect.bottom = rect.top + ysize;


		RECT srcrect = rect;
		srcrect.right -= srcrect.left;
		srcrect.left	= 0;
		srcrect.bottom -= srcrect.top;
		srcrect.top		=0;

		if ( pSurface->GetDC( &hdc ) == DD_OK )
		{

			lpDDSConvertSurface->GetDC(&destHdc);
			BitBlt(destHdc, 0, 0, xsize, ysize,	hdc, srcstartx, srcstarty, SRCCOPY);

			pSurface->ReleaseDC(hdc);
			lpDDSConvertSurface->ReleaseDC(destHdc);
		}

		if(bwaitrefresh)
		{
			lpDD7->WaitForVerticalBlank( DDWAITVB_BLOCKBEGIN, NULL );
		}	

		lpDDSPrimary->Blt( &rect, clGrp.lpDDSConvertSurface, &srcrect, DDBLT_WAIT, NULL );		


	} else {

		if( bNewFullScreen )
		{
			RECT rect;

			SetRect( &rect, 0, 0, screenXSize, screenYSize );

			RECT srcrect = rect;

			srcrect.left += srcstartx;
			srcrect.top += srcstarty;
			srcrect.right += srcstartx;
			srcrect.bottom += srcstarty;

			lpDDSPrimary->Blt( &rect, pSurface, &srcrect, DDBLT_WAIT, NULL );
		}
		else
		{
			if (bWebDlg == true && IsWindow(hWebDlg) )
			{
				RECT rect;

				SetRect( &rect, 0, 0, screenXSize, screenYSize );

				RECT srcrect = rect;

				srcrect.left += srcstartx;
				srcrect.top += srcstarty;
				srcrect.right += srcstartx;
				srcrect.bottom += srcstarty;

				RECT htmlrect;
				//			RECT tmp_srcrect;
				GetWindowRect( hWebDlg, &htmlrect );

				if (htmlrect.left >= 0)
				{
					SetRect( &rect, 0, 0, htmlrect.left, screenYSize );
					srcrect = rect;
					srcrect.left += srcstartx;
					srcrect.top += srcstarty;
					srcrect.right += srcstartx;
					srcrect.bottom += srcstarty;
					lpDDSPrimary->Blt( &rect, pSurface, &srcrect, DDBLT_WAIT, NULL );
				}
				else
					htmlrect.left = 0;

				if (htmlrect.top >= 0)
				{
					SetRect( &rect, htmlrect.left, 0, screenXSize, htmlrect.top );
					srcrect = rect;
					srcrect.left += srcstartx;
					srcrect.top += srcstarty;
					srcrect.right += srcstartx;
					srcrect.bottom += srcstarty;
					lpDDSPrimary->Blt( &rect, pSurface, &srcrect, DDBLT_WAIT, NULL );

				}
				else
					htmlrect.top = 0;

				if (htmlrect.bottom < screenYSize)
				{
					SetRect( &rect, htmlrect.left, htmlrect.bottom, screenXSize, screenYSize );
					srcrect = rect;
					srcrect.left += srcstartx;
					srcrect.top += srcstarty;
					srcrect.right += srcstartx;
					srcrect.bottom += srcstarty;
					lpDDSPrimary->Blt( &rect, pSurface, &srcrect, DDBLT_WAIT, NULL );
				}
				else htmlrect.bottom = screenYSize;

				if (htmlrect.right < screenXSize)
				{
					SetRect( &rect, htmlrect.right, htmlrect.top, screenXSize, htmlrect.bottom );
					srcrect = rect;
					srcrect.left += srcstartx;
					srcrect.top += srcstarty;
					srcrect.right += srcstartx;
					srcrect.bottom += srcstarty;
					lpDDSPrimary->Blt( &rect, pSurface, &srcrect, DDBLT_WAIT, NULL );
				}
				else htmlrect.right = screenXSize;

			}
			else
			{
				RECT rect;

				SetRect( &rect, 0, 0, screenXSize, screenYSize );

				RECT srcrect = rect;

				srcrect.left += srcstartx;
				srcrect.top += srcstarty;
				srcrect.right += srcstartx;
				srcrect.bottom += srcstarty;

				/*
				// FLIP���
				lpDDSConvertSurface->Blt( &rect, pSurface, &srcrect, DDBLT_WAIT, NULL );
				lpDDSPrimary->Flip( NULL, 0 );
				*/

				lpDDSPrimary->Blt( &rect, pSurface, &srcrect, DDBLT_WAIT, NULL );
			}
		}
	}

}	

