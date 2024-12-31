//---------------------------------
// 2003/5/17 ���°�
//---------------------------------

#include "..\Common\CommonHeader.h"
#include "..\Client\Client.h"


#include <Winuser.h>
#include <Graphic.h>
#include <Graphic_Capsule.h>

#include <Mouse.h>

#include "SmallMap.h"
#include "Map\FieldObject\FieldObject.h"

#include "..\..\Resource.h"

extern cltCommonLogic* pclClient;


SI32 siMinRate;
SI32 siMaxRate;
SI32 siCurRate;

// JAYCEE 
#define WM_MOUSEWHEEL                   0x020A
#define WHEEL_DELTA                     120     /* Value for rolling one detent */


cltSmallMap::cltSmallMap(SI32 smallmapmode, char* smallmapfilename,  cltMapClient* pclmap)
{

	m_hDlg				= NULL; 
	SmallMapXsize		= 0;
	SmallMapYsize		= 0;
	ZeroMemory(&DrawAreaRect, sizeof(DrawAreaRect));

	pclMap				= pclmap;
	SmallMapMode		= smallmapmode;

	CurrentInfoMode		= SMAP_INFOMODE_VILLAGE;

	MapXsize			= pclMap->MH.MapXsize;
	MapYsize			= pclMap->MH.MapYsize;

	DrawStartPosX		= 0;
	DrawStartPosY		= 0;

	StandardX			= 0;
	StandardY			= 0;

	OldStandardX		= -1;
	OldStandardY		= -1;
	
	// �θ� �������� ��ġ ��ȭ�� �䱸�ϴ� ����. 
	// -1�� �ʱ�ȭ�Ǹ� ��ġ ��ȭ�� �䱸���� �ʴ´�. 
	ParentMapX			= -1;
	ParentMapY			= -1;

	UserPosX			= 0;
	UserPosY			= 0;

	ConnectToMapSwitch	= TRUE;

	SmallMapRate		= 30;//10;
	siOrgSmallMapRate	= 32;

	MouseX				= 0;
	MouseY				= 0;
	DragStartX			= 0;
	DragStartY			= 0;
	LeftPressSwitch		= FALSE;
	LeftPressDragSwitch	= FALSE;
	

	pSmallMapSurface		= NULL;
	pSmallMapWorkSurface	= NULL;	// �ݵ�� �ʱ�ȭ�Ǿ�� �Ѵ�. 
	pSmallMapWorkSurface2	= NULL;

	if(smallmapfilename)
		strcpy(SmallMapFileName, smallmapfilename);
	else
		strcpy(SmallMapFileName, "NOMAP");

}

cltSmallMap::~cltSmallMap()
{
	if(m_hDlg)
	{
		DestroyWindow(m_hDlg);
		m_hDlg = NULL;
	}

	if(pSmallMapSurface)
	{
		pSmallMapSurface->Release();
		pSmallMapSurface	= NULL;
	}

	if(pSmallMapWorkSurface)
	{
		pSmallMapWorkSurface->Release();
		pSmallMapWorkSurface	= NULL;
	}

	if(pSmallMapWorkSurface2)
	{
		pSmallMapWorkSurface2->Release();
		pSmallMapWorkSurface2	= NULL;
	}

}


BOOL cltSmallMap::IncreaseDrawStartX(SI32 inc)
{
	SI32 data = DrawStartPosX + inc;

	DrawStartPosX = data;

	if(data < 0)									DrawStartPosX = 0;
	if(data > CurrentMapXsize - DrawAreaRect.right)	DrawStartPosX = CurrentMapXsize - DrawAreaRect.right;


	return TRUE;
}

BOOL cltSmallMap::IncreaseDrawStartY(SI32 inc)
{
	SI32 data = DrawStartPosY + inc;

	DrawStartPosY = data;

	if(data < 0)									 DrawStartPosY = 0;
	if(data > CurrentMapYsize - DrawAreaRect.bottom) DrawStartPosY = CurrentMapYsize - DrawAreaRect.bottom;

	return TRUE;
}


BOOL CALLBACK cltSmallMap::SMapDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{

	HWND hwnd;
	SI32 goodrate;
	SI32 maxrate, minrate;
	BOOL SliderSwitch = TRUE;


	switch(iMsg)
	{
	case WM_INITDIALOG:

		m_lastTickCount = GetTickCount() - 5000;

		// ��ü ������ ����ؾ� �� ������ ���´�. 
		hwnd = GetDlgItem(hDlg, IDC_SMALLMAPAREA);
		GetClientRect( hwnd, &DrawAreaRect );

		// ��� ������ �ҷ��´�.
		SmallMapXsize	= (pclMap->MH.MapXsize*MAP_TILE_XSIZE_HALF + pclMap->MH.MapYsize*MAP_TILE_XSIZE_HALF) / siOrgSmallMapRate;
		SmallMapYsize	= (pclMap->MH.MapXsize*MAP_TILE_YSIZE_HALF + pclMap->MH.MapYsize*MAP_TILE_YSIZE_HALF) / siOrgSmallMapRate;
		
		// ������ ��� �������� ������, 
		goodrate	= 1 +  max( DrawAreaRect.right  * 1 * 10 / SmallMapXsize, 
								DrawAreaRect.bottom * 1 * 10 / SmallMapYsize);
		
		if(SmallMapXsize < DrawAreaRect.right 
		|| SmallMapYsize < DrawAreaRect.bottom)
		{
			SmallMapRate		= goodrate ;
			maxrate				= goodrate;
			minrate				= goodrate;
			SliderSwitch		= FALSE;
			
		}
		else
		{
			SmallMapRate		= 10;
			maxrate				= 10;
			minrate				= goodrate;
			SliderSwitch		= TRUE;
		}
		
		if(SmallMapMode == SMALLMAPMODE_GAME)
		{
			
			cltTSpr Spr;
			
			if(GP.LoadSpr(SmallMapFileName, &Spr) == FALSE)
			{
				return TRUE;
			}
			
			CurrentMapXsize = SmallMapXsize*SmallMapRate/10;
			CurrentMapYsize = SmallMapYsize*SmallMapRate/10;
			
			if( pSmallMapSurface ) {
				pSmallMapSurface->Release();
				pSmallMapSurface = NULL;
			}

#ifdef GRA_MODE_16

			if(g_graphics.CreateSurface16( &pSmallMapSurface, Spr.clHeader.siXsize, Spr.clHeader.siYsize ) == FALSE)
			{
				MessageBox(NULL, "435t67", "Error", MB_OK|MB_TOPMOST);
			}
#else
			if(GP.CreateOffScreen8(pSmallMapSurface, Spr.clHeader.siXsize, Spr.clHeader.siYsize, FALSE) == FALSE)
			{
				MessageBox(NULL, "435t67", "Error", MB_OK|MB_TOPMOST);
			}
#endif
			
			// Ŭ���� ������ �����Ѵ�. 
			SI32 x1, y1, x2, y2;
			GP.GetClipArea(x1, y1, x2, y2 );

			GP.SetClipArea(0, 0, Spr.clHeader.siXsize-1, Spr.clHeader.siYsize-1 );

			if(GP.LockSurface(pSmallMapSurface) == TRUE)
			{
				Spr.PutImgT(0, 0, 0);
				
				GP.UnlockSurface(pSmallMapSurface);
			}
			// Ŭ���� ������ �����Ѵ�.
			GP.SetClipArea(x1, y1, x2, y2 );
			
			if(Spr.Image)
			{
				GP.FreeSpr(Spr);
				Spr.Image = NULL;
			}
			
		}
		else
		{
			CurrentMapXsize = SmallMapXsize*SmallMapRate/10;
			CurrentMapYsize = SmallMapYsize*SmallMapRate/10;
			
			UpdateSmallMap();
		}
		
		// ��� ������ ���ǽ��� ����� ���� �̹����� ������ �°� ����ؼ� �׸���. 
		ReadyRateMap();

		// Ÿ�̸Ӹ� �����Ѵ�. 
		SetTimer(hDlg, 1, 50, NULL);
		// Ÿ�̸Ӹ� �����Ѵ�. 
		SetTimer(hDlg, 2, 2000, NULL);
	
		if( pSmallMapWorkSurface2 ) {
			pSmallMapWorkSurface2->Release();
			pSmallMapWorkSurface2 = NULL;
		}

#ifdef GRA_MODE_16
		if(g_graphics.CreateSurface16( &pSmallMapWorkSurface2, DrawAreaRect.right, DrawAreaRect.bottom ) == FALSE)
		{
			MessageBox(NULL, "1132435t67", "Error", MB_OK|MB_TOPMOST);
		}
#else
		if(GP.CreateOffScreen8(pSmallMapWorkSurface2, DrawAreaRect.right, DrawAreaRect.bottom, FALSE) == FALSE)
		{
			MessageBox(NULL, "1132435t67", "Error", MB_OK|MB_TOPMOST);
		}
#endif


		siMinRate = minrate;
		siMaxRate = maxrate;

		siCurRate = SmallMapRate;

		return TRUE;

	case WM_NOTIFY:
		{
			LPNMHDR hdr;
			LPNMTREEVIEW ntv;
			hdr = (LPNMHDR)lParam;
			ntv = (LPNMTREEVIEW)lParam;

		}
		return TRUE;



	case WM_SETCURSOR:
		ShowHardwareCursor(TRUE);
		return TRUE;

	case WM_LBUTTONUP:
		LeftPressSwitch     = FALSE;
		LeftPressDragSwitch = FALSE;
		return TRUE;

	case WM_LBUTTONDOWN:
		LeftPressSwitch		= TRUE;
		LeftPressDragSwitch = FALSE;
		return TRUE;

	case WM_MOUSEMOVE:
		{
			if(LeftPressSwitch == TRUE)	LeftPressDragSwitch = TRUE;
			else						LeftPressDragSwitch = FALSE;	
			MouseX = LOWORD(lParam) ;
			MouseY = HIWORD(lParam) ;
		}
		return TRUE;

	case WM_MOUSEWHEEL:
		{
			SI16 zDelta = (SI16)HIWORD(wParam); //wParam;
			SI16 siWheelDir = zDelta/ WHEEL_DELTA;

			SI32 siMaxRange    = siMaxRate;
			SI32 siMinRange	   = siMinRate;
			SI32 siCurPosition = siCurRate;
			SI32 siPosition    = siCurPosition;
			if(siWheelDir>0) siPosition++;
			else	  		 siPosition--;		
			siPosition = max(siPosition, siMinRange);
			siPosition = min(siPosition, siMaxRange);

			if(siCurPosition != siPosition)
			{
				siCurRate = siPosition;
				SmallMapRate = siCurRate;
				
				CurrentMapXsize = SmallMapXsize*SmallMapRate/10;
				CurrentMapYsize = SmallMapYsize*SmallMapRate/10;
				
				
				// �������� ������ ����Ѵ�. 
				CalcMapConnection(hDlg);
				
				// ��� ������ ���ǽ��� ����� ���� �̹����� ������ �°� ����ؼ� �׸���. 
				ReadyRateMap();
				
				InvalidateRect(hDlg, NULL, FALSE);

			}
			
			DragStartX = MouseX;
			DragStartY = MouseY;

			//DXUtil_Trace("%d : %d ~ %d\n", siWheelDir, siMinRange, siMaxRange);

		}
		break;
	case WM_KEYDOWN:
	//case WM_SYSKEYDOWN:
	case WM_CHAR:
		return TRUE;


	case WM_TIMER:
		
		switch( wParam)
		{
		case 1:
			
			// ���� ��ư�� ó�� �������� 
			if(LeftPressSwitch == TRUE && LeftPressDragSwitch == FALSE)
			{
				if(MouseX > DrawAreaRect.left && MouseX < DrawAreaRect.right
				&& MouseY > DrawAreaRect.top && MouseY < DrawAreaRect.bottom)
				{
					DragStartX = MouseX;
					DragStartY = MouseY;
				}

			}
			// ��� ������ ������ 
			else if(LeftPressSwitch == TRUE && LeftPressDragSwitch == TRUE)
			{
			
				if(    MouseX > DrawAreaRect.left && MouseX < DrawAreaRect.right
					&& MouseY > DrawAreaRect.top && MouseY < DrawAreaRect.bottom)
				{	
					
					if(MouseX!=DragStartX || MouseY != DragStartY)
					{
						
						IncreaseDrawStartX(-(MouseX - DragStartX));
						IncreaseDrawStartY(-(MouseY - DragStartY));
						
						ConnectToMapSwitch = FALSE;
						
						InvalidateRect(hDlg, NULL, FALSE);
						
						DragStartX = MouseX;
						DragStartY = MouseY;
					}
					/*

					SI32 tilex, tiley;
					GetSmallMapTileXYFromCord(MouseX + DrawStartPosX, MouseY + DrawStartPosY, &tilex, &tiley);
			
					if(tilex >= 0 && tilex < MapXsize && tiley >=0 && tiley < MapYsize)
					{
						ParentMapX = tilex;
						ParentMapY = tiley;

						StandardX  = tilex;	StandardY  = tiley;
					}
					*/

				}
			}
			// ���� ��ư�� �������� 
			else if(LeftPressSwitch == FALSE && LeftPressDragSwitch == FALSE)
			{
				DragStartX = MouseX;
				DragStartY = MouseY;

			}
			
			// �������� ������ ����Ѵ�. 
			
			// ���� ��ǥ�� ����� ��쿡�� ȭ�� ����� �����Ѵ�. 
			if( (OldStandardX != StandardX || OldStandardY != StandardY)
				&& GetTickCount() - m_lastTickCount >= 1000 )
			{
				m_lastTickCount = GetTickCount();

				OldStandardX = StandardX ;
				OldStandardY = StandardY ;
				
				CalcMapConnection(hDlg);
				InvalidateRect(hDlg, NULL, FALSE);
			}
			break;
			
		case 2:
			if(SmallMapMode == SMALLMAPMODE_MAPEDIT)
			{
				UpdateSmallMap();
				InvalidateRect(hDlg, NULL, FALSE);
			}
			break;

		}


		return TRUE;

	case WM_PAINT:
		{

			HDC hdc;
			PAINTSTRUCT ps;

			hdc = BeginPaint(hDlg, &ps);
			EndPaint(hDlg, &ps);
			
			DrawSmallMap(hDlg);

		}
		return TRUE;

	case WM_CLOSE:
		if(pSmallMapSurface)
		{
			pSmallMapSurface->Release();
			pSmallMapSurface= NULL;
		}


		if(pSmallMapWorkSurface)
		{
			pSmallMapWorkSurface->Release();
			pSmallMapWorkSurface	= NULL;
		}

		if(pSmallMapWorkSurface2)
		{
			pSmallMapWorkSurface2->Release();
			pSmallMapWorkSurface2	= NULL;
		}

		// Ÿ�̸Ӹ� �����Ѵ�. 
		KillTimer(hDlg, 1);
		// Ÿ�̸Ӹ� �����Ѵ�. 
		KillTimer(hDlg, 2);

		DestroyWindow(m_hDlg);
		return TRUE;
		
	case WM_DESTROY:
		// �������� ��ġ�� ����Ѵ�. 
		GetWindowRect(hDlg, &pclClient->pclMapManager->DlgRect);
		pclClient->pclMapManager->DlgRectInitSwitch = TRUE;

		// â�� ������ ������ �� Toogle ����ġ�� ����.
		((cltClient *)pclClient)->bSmallMapSwitch = false;

		m_hDlg = NULL;
		return TRUE;

	case WM_COMMAND:
		switch(wParam)
		{
		case IDOK:
			DestroyWindow(m_hDlg);
			m_hDlg = NULL;
			return TRUE;

		case IDCANCEL:
			DestroyWindow(m_hDlg);
			m_hDlg = NULL;
			return TRUE;

			
		}
		return TRUE;
	}
	return FALSE;
}


BOOL cltSmallMap::DrawSmallMap(HWND hDlg)
{
	RECT rect;

	if(pSmallMapWorkSurface == NULL)return FALSE;
	if(pSmallMapWorkSurface2 == NULL)return FALSE;

	HWND hwnd = GetDlgItem(hDlg, IDC_SMALLMAPAREA);

	GetClientRect( hwnd, &rect );
	
	// ���� Ŭ���̾�Ʈ ��ǥ 2���� ��ũ�� ��ǥ�� �����Ѵ�.
	ClientToScreen( hwnd, (POINT*)&rect );
	ClientToScreen( hwnd, (POINT*)&rect + 1);

	// pSmallMapWorkSurface�� ��ҵ� �̹����� pSmallMapWorkSurface2�� �ű��. 
	// �ϴ� �Ű� ���� �� ���� �߰����� �̹��� �۾��� ���Ѵ�. 
	RECT trect;
	trect.left	= DrawStartPosX;
	trect.right	= DrawStartPosX + DrawAreaRect.right - 1;
	trect.top	= DrawStartPosY;
	trect.bottom = DrawStartPosY + DrawAreaRect.bottom - 1;

	pSmallMapWorkSurface2->BltFast(0, 0, pSmallMapWorkSurface, &trect, DDBLTFAST_NOCOLORKEY);

	SI32 clipx1, clipx2, clipy1, clipy2;
	GP.GetClipArea(clipx1, clipy1, clipx2, clipy2 );
	GP.SetClipArea(0, 0, DrawAreaRect.right - 1, DrawAreaRect.bottom - 1 );

	if(GP.LockSurface(pSmallMapWorkSurface2) == TRUE)
	{
	
		SI32 dotx, doty;

		/*
		if(GetSmallMapCordFromTileXY(UserPosX, UserPosY, &dotx, &doty) == TRUE)
		{
			clGrp.FillBox(dotx - 5 - DrawStartPosX, doty - 5 - DrawStartPosY, 
				dotx + 5 - DrawStartPosX, doty + 5 - DrawStartPosY, 
				SMAP_INFO_COLOR);
		}
		*/
		
		if(GetSmallMapCordFromTileXY(pclMap->VirtualMapX, pclMap->VirtualMapY, &dotx, &doty) == TRUE)
		{
			
			SI32 range = SmallMapRate;
			
			for(SI32 i =0 ; i < 3; ++i)
			{
				GP.Box(dotx - range - DrawStartPosX+i, doty - range - DrawStartPosY+i, 
					dotx + range - DrawStartPosX-i, doty + range - DrawStartPosY-i, 
					SMAP_INFO_COLOR);
				
			}
		}
		
		GP.UnlockSurface(pSmallMapWorkSurface2);
	}
	
	
	// ���� �����ֱ� ����̸�, 
	if(CurrentInfoMode	 == SMAP_INFOMODE_VILLAGE/*	&& SmallMapRate >= 3*/)	
	{
		SI32 index;
		
		//-----------------------------------------
		// ������ ��ġ�� ����ش�. 
		//-----------------------------------------
		if(pclClient->pclVillageManager 
		&& pclClient->pclMapManager->CurrentMapIndex == 0)		// ���� �������� �Ѵ�. 
		{
			for(index = 0;index < MAX_VILLAGE_NUMBER;index++)
			{
				if(pclClient->pclVillageManager->pclVillageInfo[index] == NULL)continue;

				SI32 x = pclClient->pclVillageManager->pclVillageInfo[index]->PosX;
				SI32 y = pclClient->pclVillageManager->pclVillageInfo[index]->PosY;
				char* pname = pclClient->pclVillageManager->pclVillageInfo[index]->szName;

				// ������ ���ɴ��� ���¶��, �Ӱ� ǥ��. 
				if(pclClient->pclVillageManager->pclVillageInfo[index]->bEnemyCaptureSwitch == true)
				{
					DrawSMapInfo(x, y, pname, RGB(240, 0, 0));
				}
				else
				{
					DrawSMapInfo(x, y, pname);
				}
			}
		}

		//----------------------------------
		// ����Ʈ�� ǥ���Ѵ�. 
		//----------------------------------
		cltGate clGate;
		index = 0;
		while(pclClient->pclMapManager->pclGateManager->FindGate(index, &clGate) == true)
		{
			index++;
			
			SI32 mapindex = pclClient->pclMapManager->CurrentMapIndex;
			if(clGate.SrcMapIndex == mapindex)
			{
				SI32 x = clGate.SrcX;
				SI32 y = clGate.SrcY;
				char* pname = clGate.szName;

				DrawSMapInfo(x, y, pname);
			}
			
		}
	}

	GP.SetClipArea(clipx1, clipy1, clipx2, clipy2 );


	HDC srchdc;
	HDC desthdc = GetDC(hwnd);
	if(desthdc )
	{
		pSmallMapWorkSurface2->GetDC(&srchdc);

		BitBlt(desthdc, 0, 0, rect.right - rect.left, 
			rect.bottom - rect.top, srchdc, 0, 0, SRCCOPY);

		pSmallMapWorkSurface2->ReleaseDC(srchdc);
		ReleaseDC(hwnd, desthdc);
	}

	
	return TRUE;
}

// ������� �󿡼� x, y��Ʈ�� �ش��ϴ� Ÿ�� ��ǥ�� �����ش�. 
BOOL cltSmallMap::GetSmallMapTileXYFromCord(SI32 dotx, SI32 doty, SI32* ptilex, SI32* ptiley)
{
	SI32 rate = siOrgSmallMapRate;
//	dotx = dotx - (MapYsize*MAP_TILE_XSIZE_HALF)/16;

//	*ptilex  =  (dotx/2+doty) * 10 * rate /MAP_TILE_XSIZE_HALF  / SmallMapRate;
	*ptilex  = ((dotx*rate*10/SmallMapRate- MapYsize*MAP_TILE_XSIZE_HALF)/MAP_TILE_XSIZE_HALF
		       +(doty*rate*10/SmallMapRate)/MAP_TILE_YSIZE_HALF)/2;
	*ptiley  = ((doty*rate*10/SmallMapRate)/MAP_TILE_YSIZE_HALF
		       -(dotx*rate*10/SmallMapRate- MapYsize*MAP_TILE_XSIZE_HALF)/MAP_TILE_XSIZE_HALF)/2;

	return TRUE;
}

// ������� �󿡼� Ÿ�� x, y ��ǥ�� �ش��ϴ� ��ǥ�� �����ش�. 
BOOL cltSmallMap::GetSmallMapCordFromTileXY(SI32 tilex, SI32 tiley, SI32* pdotx, SI32* pdoty)
{

	SI32 rate = siOrgSmallMapRate;

	// ��ũ�� ������ �߽� ��ǥ�� ���Ѵ�. 
	*pdotx = (MapYsize* MAP_TILE_XSIZE_HALF 
		    + tilex * MAP_TILE_XSIZE_HALF
		     -tiley * MAP_TILE_XSIZE_HALF)/rate * SmallMapRate / 10 ;

	*pdoty = (tilex * MAP_TILE_YSIZE_HALF
		     +tiley * MAP_TILE_YSIZE_HALF)/rate * SmallMapRate / 10;

	return TRUE;

}


// �������� ������ ����Ѵ�. 
void cltSmallMap::CalcMapConnection(HWND hDlg)
{
	// ������ �����Ǵ� ���� ������ �����ӿ� ���� ��������� �������ش�. 
	if(ConnectToMapSwitch == TRUE)
	{
		SI32 dotx, doty;
		if(GetSmallMapCordFromTileXY(StandardX, StandardY, &dotx, &doty) == TRUE)
		{
			DrawStartPosX = min(CurrentMapXsize - DrawAreaRect.right,  max(0, dotx - (DrawAreaRect.right/2)) );
			DrawStartPosY = min(CurrentMapYsize - DrawAreaRect.bottom, max(0, doty - (DrawAreaRect.bottom/2)) );
		}
	}

}


// ���� ���� ������ �°� ����ؼ� �۾��� ���ǽ��� �Ű� �׸���. 
void cltSmallMap::ReadyRateMap()
{
	// ũ�Ⱑ ��ȿ���� ������ ����. 
	if(CurrentMapXsize == 0 || CurrentMapYsize == 0)return ;

	if( pSmallMapWorkSurface == NULL ) {

#ifdef GRA_MODE_16
	
	if(g_graphics.CreateSurface16( &pSmallMapWorkSurface, CurrentMapXsize, CurrentMapYsize, FALSE) == FALSE)
	{
		MessageBox(NULL, "32435t67", "Error", MB_OK|MB_TOPMOST);
	}
#else
	if(GP.CreateOffScreen8(pSmallMapWorkSurface, CurrentMapXsize, CurrentMapYsize, FALSE) == FALSE)
	{
		MessageBox(NULL, "32435t67", "Error", MB_OK|MB_TOPMOST);
	}
#endif
	}

	//-----------------------------------------------------------
	// ���� ������ Ȯ��/����ؼ� pSmallMapWorkSurface�� �׸���. 
	//-----------------------------------------------------------

	// ������ ����. 
	RECT rect;
	rect.left	= 0;
	rect.right	= CurrentMapXsize;
	rect.top	= 0;
	rect.bottom	= CurrentMapYsize;
	
	pSmallMapWorkSurface->Blt( &rect, pSmallMapSurface, NULL, DDBLT_WAIT , NULL );
		
}

void cltSmallMap::UpdateSmallMap(SI32 x, SI32 y)
{
	SI32 dotx, doty;
	UI08 color	= 0;
	SI32 unique;

	GetSmallMapCordFromTileXY(x, y, &dotx, &doty);

	unique = pclMap->GetFieldObject_Unique(x, y);


	if(unique == 1)
	{
		char buffer[256];
		wsprintf(buffer, "%d %d", x, y);
		pclClient->pclMessage->SetMsg(buffer);
	}

	if(unique)
	{
		SI32 ref	= pclMap->pclFieldObjectManager->FindRefFromUniqueMinus(unique);
		if(ref < 0)return ;

		SI32 type	= pclMap->pclFieldObjectManager->pclInfo[ref]->dwType;
		color		= pclMap->pclFieldObjectManager->pclTypeInfo[type]->uiColor;

	}
	else
	{
		SI32 ref = pclMap->pclLayer[0]->GetDrawInfo_Ref(x, y);
		if(ref >= 0 && ref < MAX_TILESET_NUMBER && pclMap->pclTileManager->pclTileInfo[ref])
		{
			color = pclMap->pclTileManager->pclTileInfo[ref]->uiColor;
		}
		else
		{
			char buffer[256];
			sprintf(buffer, "Tile x:%d y:%d", x, y);
			pclClient->pclMessage->SetMsg(buffer);
		}
	}

	SI32 size = 1 + (SmallMapRate / 10) ;

	GP.FillBox(dotx-size, doty-size, dotx+1, doty+size, color,FALSE);

}


void cltSmallMap::UpdateSmallMap()
{
	
	if(SmallMapMode != SMALLMAPMODE_MAPEDIT)return ;
	if(pSmallMapWorkSurface == NULL)return ;

	SI32 i, j;
	// �ϴ� ���ǽ��� �����. 
	GP.ClearSurface(pSmallMapWorkSurface);

	SI32 clipx1, clipy1, clipx2, clipy2;
	GP.GetClipArea(clipx1, clipy1, clipx2, clipy2 );
	
	GP.SetClipArea(0, 0, CurrentMapXsize-1, CurrentMapYsize-1 );

	if(GP.LockSurface(pSmallMapWorkSurface) == TRUE)
	{
		for(i = 0; i < MapYsize ;i++)
			for(j = 0; j < MapXsize;j++)
			{
				UpdateSmallMap(j, i);
			}
			
		GP.UnlockSurface(pSmallMapWorkSurface);
	}
	GP.SetClipArea(clipx1, clipy1, clipx2, clipy2 );

}

