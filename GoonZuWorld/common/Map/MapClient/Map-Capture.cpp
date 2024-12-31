#include "..\Client\Client.h"

#include <Graphic.h>
#include <Graphic_Capsule.h>

//#include "..\..\Client\ColorTable\ColorTable.h"

#include "Bullet\Bullet.h"
#include "Smoke\Smoke.h"
#include "..\Map.h"
#include "..\Resource.h"
#include "..\..\Client\DrawSequence\DrawSequence.h"
#include "..\..\CommonLogic\MagicMgr\MagicMgr.h"

extern cltCommonLogic* pclClient;

extern	RECT				ScreenRect;							// ������ ǥ�õǴ� ���� 

//-------------------------------------------------
// ���� ĸ�� ���� 
//-------------------------------------------------

BOOL CALLBACK cltMapClient::StaticMapCaptureDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	cltMapClient* pclmap = (cltMapClient*)pclClient->pclMapManager->pclCurrentMap;
	return pclmap->MapCaptureDlgProc(hDlg, iMsg, wParam, lParam);
}

BOOL CALLBACK cltMapClient::MapCaptureDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{

	static SI32 tilerate = 2;
	static SI32 minirate = 8;

	HWND hwnd =NULL ;
	TCHAR buffer[256]=TEXT("");

	switch(iMsg)
	{
	case WM_INITDIALOG:
		CheckRadioButton(hDlg, IDC_RADIO_MAINFIELD, IDC_RADIO_NORMALFIELD, IDC_RADIO_MAINFIELD);
		return TRUE;

	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDOK:

			if(SendDlgItemMessage(hDlg, IDC_RADIO_MAINFIELD, BM_GETCHECK, 0, 0) == BST_CHECKED)
			{
				//tilerate = 2;	minirate = 8;
				tilerate = 2;	minirate = 16;
			}
			else
			{
				tilerate = 1;	minirate = 16;
			}

			if(tilerate <= 0 || tilerate > 10)
			{
				MessageBox(NULL, TEXT("��� Ÿ�� ������ �������� �ʽ��ϴ�. (1~10)"), TEXT("Warning"), MB_OK|MB_TOPMOST);
				return TRUE;
			}
			if(minirate <= 0 || minirate > 20)
			{
				MessageBox(NULL, TEXT("��� ������ �������� �ʽ��ϴ�. (1~20)"), TEXT("Warning"), MB_OK|MB_TOPMOST);
				return TRUE;
			}

			EndDialog(hDlg, tilerate | (minirate<<16) );
			return TRUE;

		case IDCANCEL:

			// ������ �����Ѵ�. 
			EndDialog(hDlg, 0);
			return TRUE;
		}
		break;
	}

	return FALSE;
}


BOOL cltMapClient::MapCapture()
{
	SHORT i, j;
	int xsize, ysize;
	int centerx, centery;
	int x1, y1, x2, y2;
	SI32 capcurerate	= 4;
	SI32 smallrate		= 4;	// ��� ���� 

	LPDIRECTDRAWSURFACE7  pSurface = NULL;
	LPDIRECTDRAWSURFACE7  pCaptureSurface = NULL;

	SI32 screenxsize = GP.GetScreenXsize();
	SI32 screenysize = GP.GetScreenYsize();

	//----------------------------------
	// �ʿ��� �Ķ��Ÿ�� ���´�. 
	//----------------------------------
	SI32 data = DialogBox(pclClient->GetInstance(), MAKEINTRESOURCE(IDD_MAPCAPTURESIZE), pclClient->GetHwnd(), (DLGPROC)StaticMapCaptureDlgProc);
	if(data == 0)
	{
		return FALSE;
	}

	capcurerate = data & 0x0000ffff;
	smallrate	= (data >> 16) / 2;

	if(MessageBox(NULL, TEXT("������ ũ�⿡ ���� ���� �ð��� �ɸ� ���� �ֽ��ϴ�. ĸ�ĸ� ����Ϸ��� ��� ��ư�� ��������."), TEXT("���� ĸ�� ����"), MB_OKCANCEL) == IDCANCEL)
		return FALSE;

	xsize	=	(MH.MapXsize/capcurerate)*MAP_TILE_XSIZE_HALF+(MH.MapYsize/capcurerate)*MAP_TILE_XSIZE_HALF;
	ysize	=	(MH.MapXsize/capcurerate)*MAP_TILE_YSIZE_HALF+(MH.MapYsize/capcurerate)*MAP_TILE_YSIZE_HALF;
	

	//---------------------------------
	// �ʿ��� �޸𸮸� �Ҵ��Ѵ�. 
	//---------------------------------


	if(g_graphics.CreateSurface16( &pSurface, xsize, ysize, FALSE) == FALSE)
	{

		int rx, ry;

		MessageBox(NULL, TEXT("�� ĸ�Ŀ� �޸𸮰� �����մϴ�. ���� ���ǽ��� ��õ��մϴ�.\r\n �����ɸ� �� ����.."), TEXT("Error"), MB_OK);

		// ���� ���ǽ� ���� 
		if(g_graphics.CreateSurface16( &pSurface, xsize / 2 + 2, ysize / 2 + 2, FALSE) == FALSE)
		{
			MessageBox(NULL, TEXT("�׷��� �����մϴ�. �� ĸ�� ����.."), TEXT("Error"), MB_OK);
			return FALSE;
		}

		// �� ��ҿ� ���ǽ� ����
		if(g_graphics.CreateSurface16( &pCaptureSurface, xsize/smallrate, ysize/smallrate, FALSE) == FALSE)
		{
			MessageBox(NULL, TEXT("�� ��ҿ� �޸� ����"), TEXT("Error"), MB_OK|MB_TOPMOST);
			return FALSE;
		}


		VirtualMapX=0;
		VirtualMapY=0;

		for( int xx = 0; xx < 2; ++xx )
		{

			for( int yy = 0; yy < 2; ++yy )
			{

				rx = ( xsize / 2 ) * xx;
				ry = ( ysize / 2 ) * yy;

				GP.ClearSurface( pSurface );

				if(GP.LockSurface(pSurface) == TRUE)
				{
					
					GP.SetScreenXsize(xsize / 2 + 2);
					GP.SetScreenYsize(ysize / 2 + 2);
					
					GP.GetClipArea(x1, y1, x2, y2 );
					GP.SetClipArea(0, 0, xsize / 2, ysize / 2 );
					
					for(i=0;i<MH.MapYsize/capcurerate;i++)
						for(j=0;j<MH.MapXsize/capcurerate;j++)
						{
							/*centerx=xsize/2
								+j*MAP_TILE_XSIZE_HALF
								-i*MAP_TILE_XSIZE_HALF;
							
							centery=MAP_TILE_YSIZE/2
								+i*(MAP_TILE_YSIZE/2) 
								+j*(MAP_TILE_YSIZE/2);
								*/
							centerx=(MH.MapYsize/capcurerate)*MAP_TILE_XSIZE_HALF
								+j*MAP_TILE_XSIZE_HALF
								-i*MAP_TILE_XSIZE_HALF;
							centery=MAP_TILE_YSIZE_HALF
								+i*MAP_TILE_YSIZE_HALF
								+j*MAP_TILE_YSIZE_HALF;
								
							if(pclLayer[1]->GetDrawInfo_Unique(j*capcurerate, i*capcurerate) != 90)
							{
								DrawLayer(centerx - rx, centery - ry, 1, j*capcurerate, i*capcurerate);
							}
							else
							{
								DrawLayer(centerx - rx, centery - ry, 0, j*capcurerate, i*capcurerate);
							}
						}
						
					for(i=0;i<MH.MapYsize/capcurerate;i++)
					{
						for(j=0;j<MH.MapXsize/capcurerate;j++)
						{
							centerx=(MH.MapYsize/capcurerate)*MAP_TILE_XSIZE_HALF
								+j*MAP_TILE_XSIZE_HALF
								-i*MAP_TILE_XSIZE_HALF;
							
							centery=MAP_TILE_YSIZE/2
								+i*(MAP_TILE_YSIZE/2) 
								+j*(MAP_TILE_YSIZE/2);
							
							for( int kx = 0; kx < capcurerate; ++kx )
							{
								for( int ky = 0; ky < capcurerate; ++ky )
								{
									SI32 x = j*capcurerate + kx;
									SI32 y = i*capcurerate + ky;
									SI32 fieldobject = GetFieldObject_Unique(x, y);

									if (fieldobject == 2010 || fieldobject == 2020 || fieldobject == 2030 || 
										fieldobject == 2040 || fieldobject == 2050 || fieldobject == 2051 || 
										fieldobject == 2052 || fieldobject == 2053 || fieldobject == 2058)
									{
										if(fieldobject && GetFieldObjectLengthToBottom(x, y) == 0 && GetFieldObjectLengthToRight(x, y) == 0)
										{

											DrawFieldObject(x,  y, centerx - rx, centery - ry, fieldobject);

										}
									}
									else
									{
										if (kx == 0 && ky == 0)
										{
											if(fieldobject && GetFieldObjectLengthToBottom(x, y) == 0 && GetFieldObjectLengthToRight(x, y) == 0)
											{

												DrawFieldObject(x,  y, centerx - rx, centery - ry, fieldobject);

											}
										}
									}
									
								}
							}
								
						}
					}
				
					GP.UnlockSurface(pSurface);
					
					int rrx = (xsize/smallrate) / 2 * xx;
					int rry = (ysize/smallrate) / 2 * yy;
					int rrx1, rry1;

					if( rrx == 0 ) {
						rrx1 = 0; 
						rrx+= 1;
					} else {
						rrx1 = rrx - 1;
					}
					
					if( rry == 0 ) {
						rry1 = 0; 
						rry+=1;
					} else {
						rry1 = rry - 1;
					}

					RECT srcRect;
					SetRect( &srcRect,
						1,
						1,
						xsize / 2 - 1,
						ysize / 2 - 1);

					RECT destRect;
					SetRect( &destRect, 
						rrx1, rry1, 
						rrx + (xsize/smallrate) / 2, 
						rry + (ysize/smallrate) / 2);

					pCaptureSurface->Blt( &destRect, pSurface,  &srcRect, DDBLT_WAIT , NULL );												 
					//pCaptureSurface->Blt( NULL, pSurface,  &destRect, DDBLT_WAIT , NULL );												 
				}
			}
		}
	 

		MessageBox(NULL, TEXT("���� ���&��� �Ϸ�"), TEXT("Information"), MB_OK|MB_TOPMOST);



	} else {

		smallrate = 4;

		VirtualMapX=0;
		VirtualMapY=0;

		if(GP.LockSurface(pSurface) == TRUE)
		{
			
			GP.SetScreenXsize(xsize);
			GP.SetScreenYsize(ysize);
			
			GP.GetClipArea(x1, y1, x2, y2 );
			GP.SetClipArea(0, 0, xsize -1, ysize -1 );
			
			for(i=0;i<MH.MapYsize/capcurerate;i++)
				for(j=0;j<MH.MapXsize/capcurerate;j++)
				{
					/*
					centerx=xsize/2
						+j*MAP_TILE_XSIZE_HALF
						-i*MAP_TILE_XSIZE_HALF;
					
					centery=MAP_TILE_YSIZE/2
						+i*(MAP_TILE_YSIZE/2) 
						+j*(MAP_TILE_YSIZE/2);
				
					*/
					centerx=(MH.MapYsize/capcurerate)*MAP_TILE_XSIZE_HALF
						+j*MAP_TILE_XSIZE_HALF
						-i*MAP_TILE_XSIZE_HALF;

					centery=MAP_TILE_YSIZE_HALF
						+i*MAP_TILE_YSIZE_HALF
						+j*MAP_TILE_YSIZE_HALF;
					
					if(pclLayer[1]->GetDrawInfo_Unique(j*capcurerate, i*capcurerate) != 90)
					{
						DrawLayer(centerx, centery, 1, j*capcurerate, i*capcurerate);
					}
					else
					{
						DrawLayer(centerx, centery, 0, j*capcurerate, i*capcurerate);
					}
				}
				
			for(i=0;i<MH.MapYsize/capcurerate;i++)
				for(j=0;j<MH.MapXsize/capcurerate;j++)
				{
					centerx=(MH.MapYsize/capcurerate)*MAP_TILE_XSIZE_HALF
						+j*MAP_TILE_XSIZE_HALF
						-i*MAP_TILE_XSIZE_HALF;
					
					centery=MAP_TILE_YSIZE/2
						+i*(MAP_TILE_YSIZE/2) 
						+j*(MAP_TILE_YSIZE/2);
/*
					centery=MAP_TILE_YSIZE
						+i*(MAP_TILE_YSIZE) 
						+j*(MAP_TILE_YSIZE);

*/					
					
					SI32 x = j*capcurerate;
					SI32 y = i*capcurerate;
					SI32 fieldobject = GetFieldObject_Unique(x, y);
					if(fieldobject && GetFieldObjectLengthToBottom(x, y) == 0 && GetFieldObjectLengthToRight(x, y) == 0)
					{
						DrawFieldObject(x, y, centerx, centery, fieldobject);						
					}
						
				}
		
		GP.UnlockSurface(pSurface);
												 
		}
	 

//		MessageBox(NULL, TEXT("���� ��� �Ϸ�"), TEXT("Information"), MB_OK|MB_TOPMOST);

		// ���� ���. 
		if(g_graphics.CreateSurface16( &pCaptureSurface, xsize/smallrate, ysize/smallrate, FALSE) == FALSE)
		{
			MessageBox(NULL, TEXT("�� ��ҿ� �޸� ����"), TEXT("Error"), MB_OK|MB_TOPMOST);
			return FALSE;
		}

		pCaptureSurface->Blt( NULL, pSurface,  NULL, DDBLT_WAIT , NULL );
	}
   
   
//   MessageBox(NULL, TEXT("���� ��� �Ϸ�"), TEXT("Information"), MB_OK|MB_TOPMOST);
   
   MapSaveAsBMP(pCaptureSurface, xsize/smallrate, ysize/smallrate);
   
   MessageBox(NULL, TEXT("���� ĸ�� �Ϸ� "), TEXT("Information"), MB_OK|MB_TOPMOST);

	if(pCaptureSurface)
	{
		pCaptureSurface->Release();
		pCaptureSurface = NULL;
	}

	if(pSurface)
	{
		pSurface->Release();
		pSurface = NULL;
	}


	cltClient* pclclient = (cltClient*)pclClient;

	// ȭ���� ������ �����Ѵ�. 
	ScreenRect.left		=	0;
	ScreenRect.right	=	pclclient->siClientScreenXsize - 1;
	ScreenRect.top		=	0;
	ScreenRect.bottom	=	pclclient->siClientScreenYsize - 1;

	GP.SetClipArea(0, 0, pclclient->siClientScreenXsize - 1, pclclient->siClientScreenYsize - 1 );

	GP.SetScreenXsize(screenxsize);
	GP.SetScreenYsize(screenysize);

	return TRUE;
}
