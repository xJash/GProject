//---------------------------------
// 2003/11/11 ���°�
//---------------------------------

#include "..\..\Common\CommonHeader.h"
#include "..\Client\Client.h"

#include <Graphic.h>
#include <Graphic_Capsule.h>

#include "..\Map.h"
#include "..\Resource.h"
#include "..\Client\Music\Music.h"
#include "..\..\Smoke\Smoke.h"
#include "../..\Char\KindInfo\KindInfo.h"
#include "..\..\Lib\AStar\AStarListMgr.h"
#include "..\..\Client\SmallMap\SMallMap.h"

#include "..\..\Client\Effect\FireFly\FireFlyMgr.h"				// �ݵ���

#include "../../Client/Effect/IceFlash/IceFlashMgr.h"
#include "../../Client/NInterface/NMiniMapDlg/NMiniMapDlg.h"
#include "../../Client/Interface/SoundOnOffDlg/SoundOnOffDlg.h"

#include "..\mapEdit\mapedit.h"
#include <MoveMark.h>

extern cltCommonLogic* pclClient;
extern	RECT				ScreenRect;							// ������ ǥ�õǴ� ���� 

cltMapClient::cltMapClient(SI32 mapindex, SI32 mapunique, SHORT xsize, SHORT ysize, SI32 tileset1, SI32 tileset2, cltCharManager* pclcm, cltTileManager* pcltileset, cltFieldObjectManager* pclfieldobjectmanager) 
: cltMapCommon(mapindex, mapunique, xsize, ysize, tileset1, tileset2, pclcm, pcltileset, pclfieldobjectmanager)
{

	bMapDrawSwitch = true;

	bCollDrawSwitch	= false;

	// ���� ������ �����. 
	pclMoveMark		= new _MoveMark(this);

	if(pclClient->GameMode == GAMEMODE_CLIENT)
	{
		pclWaterDrop	= new CWaterDropMgr(pclClient->GetGlobalSpr(GIMG_WATERDROP), xsize*MAP_TILE_XSIZE, ysize*MAP_TILE_YSIZE, xsize*ysize/20);
		pclFireFly		= new CFireFlyMgr(pclClient->GetGlobalSpr(GIMG_FIREFLY), xsize*MAP_TILE_XSIZE, ysize*MAP_TILE_YSIZE, xsize*ysize/20);
		pclIceFlash		= new CIceFlashMgr(pclClient->GetGlobalSpr(GIMG_ICEFLASH), xsize*MAP_TILE_XSIZE, ysize*MAP_TILE_YSIZE, xsize*ysize/20);
		pclSeedDrop		= new CSeedDropMgr(GIMG_SEEDDROP1, 4, xsize*MAP_TILE_XSIZE, ysize*MAP_TILE_YSIZE, xsize*ysize/30);

		CurrentEffect = 0 ;
		for ( SI32 i = 0 ; i < MAX_EFFECT_PER_MAP ; i ++ )
		{
			pclEffectMap[i].Init();
		}

		if ( pclClient->GameMode == GAMEMODE_CLIENT )
		{
			uiFogMap			= new UI08[xsize * ysize] ;
			if ( uiFogMap )
			{
				SI32 j = 0 ;
				if ( pclClient->pclMapManager->IsFogMap(mapindex) )
				{
					for ( j = 0 ; j < xsize * ysize ; j ++ )
						uiFogMap[j] = FOG_BLACK ;
				}
				else
				{
					for ( j = 0 ; j < xsize * ysize ; j ++ )
						uiFogMap[j] = FOG_NONE ;
				}
			}
		}
	}
	else
	{
		pclWaterDrop	= NULL;
		pclFireFly		= NULL;
		pclIceFlash		= NULL;
		pclSeedDrop		= NULL;
	}

	VirtualMapX	= VirtualMapY	= 0;

}

cltMapClient::~cltMapClient()
{	
	if ( pclClient->GameMode == GAMEMODE_CLIENT )
	{
		if ( uiFogMap )
		{
			delete[] uiFogMap;
			uiFogMap = NULL ;
		}
	}

	NDelete( pclWaterDrop );
	NDelete( pclFireFly );
	NDelete( pclIceFlash );
	NDelete( pclMoveMark );
	NDelete( pclSeedDrop );

}

// �������� X, Y��ǥ�� ��ġ�� �����ش�. ����� �������� �ȴ�. (ȭ����ǥ)
// x, y :�⺻ ��ǥ 
BOOL cltMapClient::GetRefXY(SHORT x, SHORT y, SHORT & centerx, SHORT & centery)
{


	if(IsInMapArea(x, y) == false)return FALSE;

	// ��ũ�� ������ �߽� ��ǥ�� ���Ѵ�. 
	centerx=-VirtualMapX*MAP_TILE_XSIZE_HALF
		+VirtualMapY*MAP_TILE_XSIZE_HALF
		+ScreenRect.left+(ScreenRect.right-ScreenRect.left+1)/2
		+x*MAP_TILE_XSIZE_HALF
		-y*MAP_TILE_XSIZE_HALF;

	centery=-VirtualMapY*MAP_TILE_YSIZE_HALF
		-VirtualMapX*MAP_TILE_YSIZE_HALF
		+ScreenRect.top+(ScreenRect.bottom-ScreenRect.top+1)/2
		+y*MAP_TILE_YSIZE_HALF
		+x*MAP_TILE_YSIZE_HALF;

	return TRUE;
}

// �������� X, Y��ǥ�� �߽��� ��ǥ�� �����ش�. (ȭ����ǥ)
// x, y :�⺻ ��ǥ 
BOOL cltMapClient::GetCenterXY(SHORT x, SHORT y, SHORT & centerx, SHORT & centery)
{

	if(IsInMapArea(x, y) == false)return FALSE;

	// ��ũ�� ������ �߽� ��ǥ�� ���Ѵ�. 
	centerx=-VirtualMapX*MAP_TILE_XSIZE_HALF
		+VirtualMapY*MAP_TILE_XSIZE_HALF
		+ScreenRect.left+(ScreenRect.right-ScreenRect.left+1)/2
		+x*MAP_TILE_XSIZE_HALF
		-y*MAP_TILE_XSIZE_HALF;

	centery=-VirtualMapY*MAP_TILE_YSIZE_HALF
		-VirtualMapX*MAP_TILE_YSIZE_HALF
		+ScreenRect.top+(ScreenRect.bottom-ScreenRect.top+1)/2
		+y*MAP_TILE_YSIZE_HALF
		+x*MAP_TILE_YSIZE_HALF;

	return TRUE;
}

// �������� X, Y��ǥ�� �߽��� ��ǥ�� �����ش�. (ȭ����ǥ)
BOOL cltMapClient::GetCenterXYByMapCenterXY(SHORT x, SHORT y, SHORT & centerx, SHORT & centery)
{

	if(IsInMapArea(x, y) == false)return FALSE;

	SI32 mapcenterx = 0, mapcentery = 0;
	GetXYDotFromXYCord(x, y, mapcenterx, mapcentery);

	centerx=mapcenterx - (VirtualMapX * MAP_TILE_XSIZE_HALF)
		+ (VirtualMapY * MAP_TILE_XSIZE_HALF)
		+ ScreenRect.left + (ScreenRect.right - ScreenRect.left + 1) / 2;

	centery=mapcentery - VirtualMapY * MAP_TILE_YSIZE_HALF
		- VirtualMapX * MAP_TILE_YSIZE_HALF
		+ ScreenRect.top + (ScreenRect.bottom - ScreenRect.top + 1) / 2;

	return TRUE;

}


// ���� ��ǥ�� ȭ�� ��ǥ�� ��ȯ�Ѵ�.
void cltMapClient::TransFromRealDotToScreenDot(SHORT realx, SHORT realy, SHORT& screenx, SHORT &screeny)
{

	screenx=realx+ScreenRect.left+(ScreenRect.right-ScreenRect.left+1)/2+(-VirtualMapX*MAP_TILE_XSIZE_HALF+VirtualMapY*MAP_TILE_XSIZE_HALF);
	screeny=realy+ScreenRect.top+(ScreenRect.bottom-ScreenRect.top+1)/2 +(-VirtualMapY*MAP_TILE_YSIZE_HALF-VirtualMapX*MAP_TILE_YSIZE_HALF);
}

// ȭ�� ��ǥ�� ���� ��ǥ�� ��ȯ�Ѵ�.
void cltMapClient::TransFromScreenToRealXY(SHORT screenx, SHORT screeny, SHORT& realx, SHORT &realy)
{
	realx = screenx - (ScreenRect.left + (ScreenRect.right-ScreenRect.left+1)/2)-(-VirtualMapX*MAP_TILE_XSIZE_HALF+VirtualMapY*MAP_TILE_XSIZE_HALF);

	realy = screeny - (ScreenRect.top  + (ScreenRect.bottom-ScreenRect.top+1)/2)-(-VirtualMapY*MAP_TILE_YSIZE_HALF-VirtualMapX*MAP_TILE_YSIZE_HALF) + MAP_TILE_YSIZE_HALF;
}






// mousex, mousey�� Ŭ���̾�Ʈ ������ �ִ°�?
BOOL cltMapClient::IsPtInMap(SHORT mouse_x, SHORT mouse_y)
{

	if(mouse_x>=ScreenRect.left && mouse_x<=ScreenRect.right
		&& mouse_y>=ScreenRect.top  && mouse_y<=ScreenRect.bottom)
	{
		return TRUE;
	}

	return FALSE;
}



// x, y��ǥ�� ȭ��ȿ� �ִ��� Ȯ���Ѵ�.
BOOL cltMapClient::IsInScreen(SHORT x, SHORT y)
{

	SHORT centerx, centery;

	if(GetCenterXY(x, y, centerx, centery)==TRUE)
	{
		if(ScreenRect.left<= centerx && centerx <= ScreenRect.right
			&& ScreenRect.top<=  centery && centery <= ScreenRect.bottom)return TRUE;
	}

	return FALSE;

}

// x, y Ÿ�� ��ǥ�� ȭ��ȿ� �ִ��� Ȯ���Ѵ�.
BOOL cltMapClient::IsInScreenTile(SI32 x, SI32 y)
{
	if(IsInMapArea(x, y) == false)return FALSE;

	cltClient* pclclient = (cltClient*)pclClient;

	if(VirtualMapX - pclclient->siClientScreenHalfSize <= x && x < VirtualMapX + pclclient->siClientScreenHalfSize
		&& VirtualMapY - pclclient->siClientScreenHalfSize <= y && y < VirtualMapY + pclclient->siClientScreenHalfSize)
	{
		return TRUE;
	}

	return FALSE;
}


//-------------------------------------
// ���� ���� ���� 
//-------------------------------------
BOOL cltMapClient::MakeSmallMap(SI32 smallmapmode, TCHAR* mapfilename)
{
	if ( g_SoundOnOffDlg.m_bFullScreenMode && pclClient->GameMode != GAMEMODE_MAPEDIT )
	{
		cltClient *pclclient = (cltClient *)pclClient;

		if ( pclclient->m_pDialog[ NMINIMAP_DLG ] == NULL)
		{
			pclclient->CreateInterface( NMINIMAP_DLG );
		}
		
		if ( pclclient->m_pDialog[ NMINIMAP_DLG]->IsShow() == false )
		{
			 pclclient->m_pDialog[ NMINIMAP_DLG]->Show(TRUE);
		}

		if ( pclclient->m_pDialog[ NMINIMAP_DLG ] )
		{	
			(( CNMiniMapDlg *) pclclient->m_pDialog[ NMINIMAP_DLG ])->Set( mapfilename, this, siMapIndex );
			if(pclclient->bSmallMapSwitch == FALSE)
				(( CNMiniMapDlg *) pclclient->m_pDialog[ NMINIMAP_DLG ])->Minimi(TRUE);
		}
	}

	return TRUE;
}

//---------------------------------------
// ���� ���� ���� 
//---------------------------------------
void cltMapClient::ScrollOperation()
{
	// ��ũ�� ������ �ʱ�ȭ�Ѵ�. 
	SI32 Scroll=0;

	// Ű���忡 ���� ��ũ���� �����Ѵ�. 
	if(GetAsyncKeyState(VK_UP)   < -1)	   Scroll |= NORTH;
	if(GetAsyncKeyState(VK_DOWN) < -1)	   Scroll |= SOUTH;
	if(GetAsyncKeyState(VK_LEFT) < -1)     Scroll |= WEST;
	if(GetAsyncKeyState(VK_RIGHT)< -1)	   Scroll |= EAST;


	// ��ũ�� ���̸� ������ �׸���. 
	if(Scroll)
	{
		SetMapDrawSwitch(true);
	}

	// ��ũ�� ������ �ӽ÷� �����Ѵ�. 
	SHORT tempvirtualmapx=VirtualMapX;
	SHORT tempvirtualmapy=VirtualMapY;

	// ���� ��ũ�� 
	if(Scroll&NORTH)
	{
		if(DecreaseVirtualMapY(1)==TRUE)
		{

			if(DecreaseVirtualMapX(1)==FALSE)
			{
				if(DecreaseVirtualMapY(1)==FALSE)
					IncreaseVirtualMapY(1);
			}
		}
		else
		{
			DecreaseVirtualMapX(2);
		}
	}
	// ���� ��ũ�� 
	else if(Scroll&SOUTH)
	{
		if(IncreaseVirtualMapY(1)==TRUE)
		{

			if(IncreaseVirtualMapX(1)==FALSE)
			{
				if(IncreaseVirtualMapY(1)==FALSE)
					DecreaseVirtualMapY(1);

			}
		}
		else
		{
			IncreaseVirtualMapX(2);
		}
	}

	// ���� ��ũ�� 
	if(Scroll&WEST)
	{
		if(DecreaseVirtualMapX(1)==TRUE)
		{
			if(IncreaseVirtualMapY(1)==FALSE)
			{
				if(DecreaseVirtualMapX(1)==FALSE)
					IncreaseVirtualMapX(1);
			}
		}
		else
		{
			IncreaseVirtualMapY(2);
		}
	}
	// ���� ��ũ�� 
	else if(Scroll&EAST)
	{
		if(IncreaseVirtualMapX(1)==TRUE)
		{
			if(DecreaseVirtualMapY(1)==FALSE)
			{
				if(IncreaseVirtualMapX(1)==FALSE)
				{
					DecreaseVirtualMapX(1);
				}
			}
		}
		else
		{
			DecreaseVirtualMapY(2);
		}
	}


	if(VirtualMapX==tempvirtualmapx+1 && VirtualMapY==tempvirtualmapy-3)
	{
		VirtualMapX=tempvirtualmapx;
		VirtualMapY=tempvirtualmapy-2;
	}
	else if(VirtualMapX==tempvirtualmapx-3 && VirtualMapY==tempvirtualmapy+1)
	{
		VirtualMapX=tempvirtualmapx-2;
		VirtualMapY=tempvirtualmapy;
	}
	else if(VirtualMapX==tempvirtualmapx+3 && VirtualMapY==tempvirtualmapy-1)
	{
		VirtualMapX=tempvirtualmapx+2;
		VirtualMapY=tempvirtualmapy;
	}
	else if(VirtualMapX==tempvirtualmapx-1 && VirtualMapY==tempvirtualmapy+3)
	{
		VirtualMapX=tempvirtualmapx;
		VirtualMapY=tempvirtualmapy+2;
	}


	// ������ ��ũ���� �̷�� ������ ���̷�� ������ Ȯ���Ѵ�. 
	if(tempvirtualmapx!=VirtualMapX || tempvirtualmapy!=VirtualMapY)
	{

	}
	else
	{
	}
}



// ������ ������  PCX ���Ϸ� �����Ѵ�.
BOOL cltMapClient::MapSaveAsPCX(LPDIRECTDRAWSURFACE7 pSurface, int xsize, int ysize)
{
	TCHAR buffer[FILE_NAME_SIZE];
	BYTE* imagebuffer;

	imagebuffer =  new BYTE [xsize * ysize];

	if(GP.LockSurface(pSurface) == TRUE)
	{
		GP.GetImage(0, 0, xsize, ysize, imagebuffer);
		GP.UnlockSurface(pSurface);
	}

	cltMapEdit *pcltMapEdit =(cltMapEdit *) pclClient;
	TCHAR OnlyFileName[FILE_NAME_SIZE];
	memset(OnlyFileName, 0, sizeof(OnlyFileName));
	_tcsncpy(OnlyFileName, pcltMapEdit->MapFileShortName, _tcslen(pcltMapEdit->MapFileShortName)-4);
	StringCchPrintf(buffer, FILE_NAME_SIZE, TEXT("%s.pcx"), OnlyFileName);

	PCX pcx;
	pcx.Head.hres	=xsize;
	pcx.Head.vres	=ysize;
	pcx.Head.xmax	=xsize-1;
	pcx.Head.ymax	=ysize-1;
	pcx.Head.bpl     = xsize;
	pcx.Head.shres   = xsize;
	pcx.Head.svres   = ysize;

	pcx.Image=imagebuffer;
	GP.SavePCX(pcx, buffer);

	delete[] imagebuffer;

	return TRUE;
}

BOOL cltMapClient::MapSaveAsBMP(LPDIRECTDRAWSURFACE7 pSurface, int xsize, int ysize)
{

	TCHAR buffer[FILE_NAME_SIZE], OnlyFileName[FILE_NAME_SIZE];

	cltMapEdit *pcltMapEdit =(cltMapEdit *) pclClient;

	memset(OnlyFileName, 0, sizeof(OnlyFileName));

	_tcsncpy(OnlyFileName, pcltMapEdit->MapFileShortName, _tcslen(pcltMapEdit->MapFileShortName)-4);
	//_tcscpy(OnlyFileName, TEXT("Test"));
	StringCchPrintf(buffer, FILE_NAME_SIZE, TEXT("%s.bmp"), OnlyFileName);


	UI08 *pImage;

	SI32 lpitch = ( ( xsize * 3 + 3 ) / 4 ) * 4;
	SI32 imagesize = lpitch * ysize;

	pImage = new UI08[ imagesize ];

	BITMAPFILEHEADER bmfh;
	BITMAPINFO bitmapinfo;

	ZeroMemory( &bmfh, sizeof( BITMAPFILEHEADER ) );

	bmfh.bfType = ((WORD) ('M' << 8) | 'B');
	bmfh.bfSize = sizeof( BITMAPFILEHEADER ) + sizeof( BITMAPINFOHEADER ) + imagesize;
	bmfh.bfOffBits = sizeof( BITMAPFILEHEADER ) + sizeof( BITMAPINFOHEADER );

	bitmapinfo.bmiHeader.biSize	= sizeof( BITMAPINFOHEADER );
	bitmapinfo.bmiHeader.biWidth = xsize;
	bitmapinfo.bmiHeader.biHeight = ysize;
	bitmapinfo.bmiHeader.biPlanes = 1;
	bitmapinfo.bmiHeader.biBitCount = 24;
	bitmapinfo.bmiHeader.biCompression = BI_RGB;
	bitmapinfo.bmiHeader.biSizeImage = 0;
	bitmapinfo.bmiHeader.biXPelsPerMeter = 0;
	bitmapinfo.bmiHeader.biYPelsPerMeter = 0;
	bitmapinfo.bmiHeader.biClrUsed = 0;
	bitmapinfo.bmiHeader.biClrImportant = 0;


	if(GP.LockSurface(pSurface) == TRUE)
	{
		int i, j;
		UI08 r, g, b;
		UI16 c;

		for( i = 0; i < ysize; ++i ) {
			for( j = 0; j < xsize; ++j ) { 

				c = *(UI16*)GP.GetSurfacePtr( j, i );

				g_graphics.GetRGB16( c, &r, &g, &b );

				pImage[ (ysize - i - 1) * lpitch + (j * 3) ] = b;
				pImage[ (ysize - i - 1) * lpitch + (j * 3) + 1 ] = g;
				pImage[ (ysize - i - 1) * lpitch + (j * 3) + 2 ] = r;
			}
		}


		GP.UnlockSurface(pSurface);
	}

	HANDLE hFile = CreateFile( buffer, 
		GENERIC_WRITE, 
		NULL, 
		NULL, 
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL );

	if( hFile == INVALID_HANDLE_VALUE ) {
		delete [] pImage;
		return FALSE;
	}

	DWORD written;
	WriteFile( hFile, &bmfh, sizeof( bmfh ), &written, NULL );
	WriteFile( hFile, &bitmapinfo, sizeof( BITMAPINFOHEADER ), &written, NULL );
	WriteFile( hFile, pImage, imagesize, &written, NULL );

	CloseHandle( hFile );


	delete [] pImage;

	return TRUE;

}


// �ҷ����ų� �����ϰ� ������ ������ �������� ������ �����. 
void cltMapClient::MakeLastMap()
{
	cltMapCommon::MakeLastMap();

	if( pclWaterDrop )
	{
		// ����̸�, 
		if( MH.TileSet1 == 190 || MH.TileSet1 == 191 )
		{
			pclWaterDrop->SetActive(true);
		}
		else
		{
			pclWaterDrop->SetActive(false);
		}
	}

	if ( pclSeedDrop )
	{
		// ����Ǯ��
		if ( MH.TileSet1 == 249)
		{
			pclSeedDrop->SetActive( true );									
		}
		else
		{
			pclSeedDrop->SetActive( false );
		}
	}


	if ( pclFireFly )
	{
		// �������̸�, 
		if( MH.TileSet1 == 210 || MH.TileSet1 == 211 )
		{
			pclFireFly->SetActive( true );
		}
		else if ( MH.TileSet1 == 220 )										// 220 �� ���ൿ��2��
		{
			pclFireFly->SetActive( true, 1150, 130, 1350, 350, 15 );		// ���⼭ �Ķ���ͷ� ��ǥ��( xleft, ytop, xright, ybottom )�ָ�, Ư�� ��ǥ���� ������ �ϱ⵵ �ǰ�...
		}
		else if ( MH.TileSet1 == 101 ) // õ���
		{
		}
		else
		{
			pclFireFly->SetActive( false );
		}
	}

	if ( pclIceFlash )
	{
		// ������
		if ( MH.TileSet1 == 94 || MH.TileSet1 == 97 )
		{
			pclIceFlash->SetActive( true );									
		}
		else if ( MH.TileSet1 == 101 ) // õ���
		{
		}
		else
		{
			pclIceFlash->SetActive( false );
		}
	}
}

// �Ѱ��� FOG_BLACK�� �׸���. 
BOOL cltMapClient::DrawFogBlack(cltClient* pclclient, SI32 x, SI32 y, SI32 centerx, SI32 centery)
{

	SI32 startx=centerx-MAP_TILE_XSIZE_HALF;
	SI32 starty=centery-MAP_TILE_YSIZE_HALF;

	if(GP.IsInClipArea(startx, starty, startx + MAP_TILE_XSIZE -1, starty + MAP_TILE_YSIZE -1) == false)return false;

	UI32 fogdata = GetFogMap(x, y);
	if(fogdata == FOG_BLACK)
	{
		// �������� ��´�. 
		for(SI32 i = 0;i < MAP_TILE_YSIZE;i++)
		{
			memset(GP.GetSurfacePtr(startx + pclclient->TileMaskTransArray[i], starty + i), 0, (pclclient->TileMaskImgArray[i]<<1));
		}
	}

	return true;
}

bool cltMapClient::DrawFog(LPDIRECTDRAWSURFACE7 lpsurface , cltClient * pclclient)
{


	SHORT i, j;
	SI32 centerx, centery;
	SI32 startx, starty;
	TSpr* pspr	= pclclient->GetGlobalSpr(GIMG_FOG);

	if(pspr == NULL)
		return false;

	for(i = VirtualMapY - pclclient->siClientScreenHalfSize;i < VirtualMapY + pclclient->siClientScreenHalfSize;i++)
		for(j = VirtualMapX - pclclient->siClientScreenHalfSize;j < VirtualMapX + pclclient->siClientScreenHalfSize;j++)
		{
			// ���������� ����.
			if(IsInMapArea(j, i) == false)
				continue;

			// ����ؾ� �� �߽� ��ġ�� ���Ѵ�. 
			GetDrawCenterXY(j, i, &centerx, &centery);

			startx=centerx-MAP_TILE_XSIZE_HALF;
			starty=centery-MAP_TILE_YSIZE_HALF;


			if(GP.IsInClipArea(startx, starty, startx + pspr->GetXSize() -1, starty + pspr->GetYSize() -1) == false)continue;

			SI32 font;

			switch(GetFogMap(j, i))
			{
			case FOG_BLACK:	
				//DrawFogBlack(pclclient, j, i, centerx, centery);
				//pspr->PutSprT( startx, starty, 15);
				//GP.FillBox(startx+ 20, starty+20, startx+ 80 - 20, starty + 40 - 20, 100, false);
				DrawFogBlack(pclclient, j, i, centerx, centery);
				break;
			case FOG_HALF:
				CalcFogData(j, i, &font);
				if(font >= 0)
				{
					//pspr->PutSprAlphaT( startx, starty, font,6);
					//pspr->PutSprT(startx,starty,font);

					GP.PutSprShadow(pspr, startx, starty, font);
					
					//pspr->PutSprMultiplyT(startx,starty,font);
				}
				break;
			case FOG_NONE:
				CalcFogData(j, i, &font);
				if(font >= 0)
				{
					//pspr->PutSprAlphaT( startx, starty, font,6);
					//pspr->PutSprT(startx,starty,font);
					
					GP.PutSprShadow(pspr, startx, starty, font);

					//pspr->PutSprMultiplyT(startx,starty,font);
				}
				break;
			}
		};

	return true;
}

// ��� ȿ������ �����Ѵ�. 
void cltMapClient::PlayBackEffect()
{
	static DWORD lastframe = 0;

	if(lastframe == pclClient->GetFrame())return ;

	if(pclClient->GetFrame() % 400 )return ;
	lastframe = pclClient->GetFrame();


	switch(siMapIndex)
	{
	//case 0:
	//	pclClient->PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BACK_MAIN")), 0, 0);
	//	break;

	case 94: // ���2�� 
	case 109: // ���1��
		pclClient->PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BACK_SEAPALACE")), 0, 0);
		break;

	case 98: // ������. 
	case 110: // ������2��
		pclClient->PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BACK_GOBLIN")), 0, 0);
		break;
		
	case 104:// ��Ȳ��  
	case 105:// ��Ȳ��  
	case 106:// ��Ȳ��  
		pclClient->PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_BACK_MIHWABGSA")), 0, 0);
		break;


	default:
		break;

	}

}

// ��ǰ �����ۿ��� ǥ���Ѵ�.
void cltMapClient::MakeRareItemSmoke(bool breverseswitch, SI32 x, SI32 y, SI32 xsize, SI32 ysize,
									 UI08* image, SI32 rare, bool horse)
{
	POINT plist[1];
	SI32 list = 1;
	

	if( rare & JEWELEFFECT_RARE1 )
	{
		if(pclClient->GetFrame() % 20 )return ; 
	}
	else if( rare & JEWELEFFECT_RARE2 )
	{
		if(pclClient->GetFrame() % 10 )return ; 
	}
	else 
	{
		if(pclClient->GetFrame() % 15 )return ;
	}
    

	if ( horse )
	{
		if(breverseswitch)
		{
			GP.GetSprRandPos8H(x, y, xsize, ysize, image, &list, plist,TRUE);
		}
		else
		{
			GP.GetSprRandPos8H(x, y, xsize, ysize, image, &list, plist,FALSE);
		}
	}
	else
	{
		if(breverseswitch)
		{
			GP.GetSprRandPos8(x, y, xsize, ysize, image, &list, plist,TRUE);
		}
		else
		{
			GP.GetSprRandPos8(x, y, xsize, ysize, image, &list, plist,FALSE);
		}
	}
	
	SHORT realx, realy;
	
	for(SI32 i = 0;i < list;i++)
	{
		
		// ȭ�� ��ǥ�� ���� ��ǥ�� ��ȯ�Ѵ�.
		TransFromScreenToRealXY((SHORT)plist[i].x, (SHORT)plist[i].y, realx, realy);

		// ���̸� �����Ѵ�.
		realy -= 10;

		SI32 smoke = 0;
/*		if(rare)
		{
			rare = 1 + pclClient->GetFrame() / 100 % 4;
		}
	*/	
		/*

		switch(rare)
		{
		case RARELEVEL_1:smoke = SMOKE_RAREITEMSMOKE3;	break;
		default:			smoke = SMOKE_RAREITEMSMOKE1;	break;
		}*/

		if( rare & JEWELEFFECT_RARE1 )
		{
			smoke = SMOKE_RAREITEMSMOKE3;
		}
		else if( rare & JEWELEFFECT_RARE2 )
		{
			smoke = SMOKE_RAREITEMSMOKE1;
		}
		else if( rare & MARRIED_FULLDRESS )
		{
			smoke = SMOKE_MARRIED_FULLDRESS;
		}



		if ( horse )
		{
			smoke = SMOKE_HORSE_TICKET_EFFECT ;
		}

		if(smoke)
		{

			pclClient->pclSmokeManager->SetSmoke(smoke, realx, realy, this);
		}
	}

}

//-----------------------------------------------
// cltMapClient
//-----------------------------------------------
cltMapClient::cltMapClient()
{
	ZeroMemory(this, sizeof(cltMapClient));
}

void cltMapClient::SetMapDrawSwitch(bool mode)
{
	bMapDrawSwitch	=	mode;
}

UI32 cltMapClient::GetFogMap(SI32 x, SI32 y)
{
	if(IsInMapArea(x, y) == false)return FOG_NONE;

	return uiFogMap[x + YOff[y]] ;
}

void cltMapClient::SetFogMap(SI32 x, SI32 y, UI32 data)
{
	if(IsInMapArea(x, y) == false)return;

	uiFogMap[x + YOff[y]] = data ;
}

// x, y�⺻ ��ǥ 
BOOL cltMapClient::IsLand(SHORT x, SHORT y)
{
	if( pCollMap == NULL )	return TRUE;
	if( pCollMap[x+YOff[y]] & BLOCK_DEEPWATER )		return FALSE;   
	return TRUE;
}

// x, y�⺻ ��ǥ 
BOOL cltMapClient::IsSea(SHORT x, SHORT y)
{
	if( pCollMap == NULL )	return FALSE;
	if( pCollMap[x+YOff[y]] & BLOCK_DEEPWATER )	return TRUE;
	return FALSE;
}

void cltMapClient::SetVirtualPos(SI16 siX, SI16 siY)
{
	VirtualMapX  = siX;
	VirtualMapY  = siY;
}

