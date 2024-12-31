//---------------------------------
// 2003/5/17 ���°�
//---------------------------------

#include "..\Common\CommonHeader.h"
#include "..\Client\Client.h"

#include <Graphic.h>
#include <Graphic_Capsule.h>

#include <Mouse.h>
#include "Map\FieldObject\FieldObject.h"

#include "mapedit.h"
#include "..\Client\SmallMap\SmallMap.h"

#include "..\resource.h"

extern cltCommonLogic* pclClient;
extern _InputDevice				IpD;

static DWORD CaptureClock ;      // ������ ĸ���� �ð�. 

cltMapEdit::cltMapEdit( TCHAR* appname, HWND hwnd, HINSTANCE hinst, SI32 gamemode, SI32 defaultservicearea, SI32 runmode ) : cltClient( appname, hwnd, hinst, gamemode, defaultservicearea, NULL, runmode )
{
	SI32 i, j;
	
	
	hMapEditDlg					= NULL;
	hGeoInfoDlg					= NULL;
	
	CurrentMode					= MAPEDIT_MODE_TERRAIN;
	CurrentTerrainUnique		= 0;
	CurrentFieldObjectUnique	= 0;
	CurrentFieldObjectBrush		= -1;
	SelectedGeoInfoSlot			= 0;
	CurrentCustomCollision		= BLOCK_CUSTOM;
	SelectedFieldObjectUnique	= 0;

	uiCollisionBrush			= 1;
	
	StringCchCopy(MapFileName, 256,		TEXT(""));
	StringCchCopy(MapFileShortName, 128,TEXT(""));
	
	StringCchCopy(CurrentDirectory, MAX_PATH, TEXT(""));
	
	// �㿡���Ϳ��� ����ϴ� File Open Box�������� �ʱ�ȭ 
	PopMapFileInitializeMap(GetHwnd());
	
	
	//-------------------------------------
	// FieldObject ǥ�ÿ� Surface
	//--------------------------------------
	pFOSurface		= NULL;
	pFOSurface2		= NULL;
	
	for(i = 0;i < FIELDOBJECT_COLL_MAP_YSIZE;i++)
		for(j = 0;j < FIELDOBJECT_COLL_MAP_XSIZE;j++)
		{
			FieldObjectCollMap[j][i] = 0;
		}
		
		FoTileSize	= 2;
}

cltMapEdit::~cltMapEdit()
{
	if(pFOSurface)
	{
		pFOSurface->Release();
		pFOSurface = NULL;
	}
	
	if(pFOSurface2)
	{
		pFOSurface2->Release();
		pFOSurface2 = NULL;
	}
	
	if (m_pNewMapPCXSpr.pImage)
	{
		GP.FreeSpr(m_pNewMapPCXSpr);
	}
	if(FloorSpr.pImage)
	{
		GP.FreeSpr(FloorSpr);
	}
	
}

void cltMapEdit::Create()
{
	cltClient::Create();
	
	/// �ٷ� �������� ����. 
	SetGameStatus(GS_GAME);
	
	GP.CreateSurface(pFOSurface,  FOSURFACE_XSIZE, FOSURFACE_YSIZE);
	GP.CreateSurface(pFOSurface2, FOSURFACE_XSIZE, FOSURFACE_YSIZE);
	
	
	// FieldObject �� �����ֱ� ���� �ٴ� Ÿ���� �ε��Ѵ�. 
	GP.LoadSprFromFile(TEXT("MapEdit\\Floor.Spr"), &FloorSpr);
}

void cltMapEdit::CreateNewMapTool()
{
	DialogBox(GetInstance(), MAKEINTRESOURCE(IDD_NEWMAP), GetHwnd(), (DLGPROC)StaticNewMapDlgProc);
}


BOOL CALLBACK cltMapEdit::StaticNewMapDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	return ((cltMapEdit*)pclClient)->NewMapDlgProc(hDlg, iMsg, wParam, lParam);
}

BOOL CALLBACK cltMapEdit::NewMapDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	
	HWND hwnd;
	TCHAR buffer[256];
	
	switch(iMsg)
	{
	case WM_INITDIALOG:
		// ���� ���� 
        hwnd=GetDlgItem(hDlg, IDC_MAP_XSIZE);
		StringCchPrintf(buffer, 256, TEXT("%d"), pclMapManager->pclCurrentMap->MH.MapXsize);
		SetWindowText(hwnd, buffer);
		
        hwnd=GetDlgItem(hDlg, IDC_MAP_YSIZE);
		StringCchPrintf(buffer, 256, TEXT("%d"), pclMapManager->pclCurrentMap->MH.MapYsize);
		SetWindowText(hwnd, buffer);
		
		// Ÿ�� ��Ʈ�� �ʱⰪ�� �����Ѵ�.
		StringCchPrintf(buffer, 256, TEXT("%d"), pclMapManager->pclCurrentMap->MH.TileSet1);
		SetDlgItemText(hDlg, IDC_EDIT_MAPEDIT_TILESET, buffer);
		
		return TRUE;
		
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDC_BUTTON_LOADSPR:
			{
				PopMapFileInitializeSpr(GetHwnd());
				if ( PopMapFileOpenDlg(GetHwnd(), MapFileName, MapFileShortName) )
				{
					if ( GP.LoadSprFromFile(MapFileName,&m_pNewMapPCXSpr) )
					{
						LPDIRECTDRAWSURFACE7 pSurface = NULL;
						SHORT xsize = m_pNewMapPCXSpr.GetXSize() ;
						SHORT ysize = m_pNewMapPCXSpr.GetYSize() ;

						GP.CreateSurface( pSurface, xsize,ysize);
						if( GP.LockSurface( pSurface ) ) {
							GP.PutSpr(&m_pNewMapPCXSpr, 0, 0, 0 );

							GP.UnlockSurface( pSurface );
						}

						//if ( pclClient->siServiceArea == ConstServiceArea_China )
						//{
						//	pclTileManager->LoadTileSet(230, 121);

						//	delete pclMapManager->pclMapArray[pclMapManager->CurrentMapIndex ];
						//	pclMapManager->pclMapArray[pclMapManager->CurrentMapIndex ] = NULL;
						//	pclMapManager->pclCurrentMap = NULL;

						//	pclMapManager->pclMapArray[pclMapManager->CurrentMapIndex ] = new cltMapClient(pclMapManager->CurrentMapIndex, 0, xsize, ysize, 0, 90, pclClient->pclCM, pclClient->pclTileManager, pclClient->pclFieldObjectManager);
						//	pclMapManager->MakeLastMap(pclMapManager->CurrentMapIndex);
						//	pclMapManager->pclCurrentMap  = pclMapManager->pclMapArray[pclMapManager->CurrentMapIndex ];

						//	pclMapManager->pclCurrentMap->MH.TileSet1	= 230;
						//	pclMapManager->pclCurrentMap->MH.TileSet2	= 121;
						//}
						//else
						//{
							pclTileManager->LoadTileSet(0, 90);

							delete pclMapManager->pclMapArray[pclMapManager->CurrentMapIndex ];
							pclMapManager->pclMapArray[pclMapManager->CurrentMapIndex ] = NULL;
							pclMapManager->pclCurrentMap = NULL;

							pclMapManager->pclMapArray[pclMapManager->CurrentMapIndex ] = new cltMapClient(pclMapManager->CurrentMapIndex, 0, xsize, ysize, 0, 90, pclClient->pclCM, pclClient->pclTileManager, pclClient->pclFieldObjectManager);
							pclMapManager->MakeLastMap(pclMapManager->CurrentMapIndex);
							pclMapManager->pclCurrentMap  = pclMapManager->pclMapArray[pclMapManager->CurrentMapIndex ];

							pclMapManager->pclCurrentMap->MH.TileSet1	= 0;
							pclMapManager->pclCurrentMap->MH.TileSet2	= 90;
						//}

						SI32 index[20] = {0,};
						SI32 k = 0 ;

						for ( SI32 i = 0 ; i < xsize ; i ++ )
						{
							for ( SI32 j = 0 ; j < ysize ; j ++)
							{
								//if ( pclClient->siServiceArea == ConstServiceArea_China )
								//{
								//	if ( g_graphics.GetSurfacePixel(i,j) == 0 ) // ����
								//	{
								//		pclMapManager->pclCurrentMap->PutTile2(0, i, j, 238); // ����
								//	}
								//	else if ( g_graphics.GetSurfacePixel(i,j) == 61728 ) // ����
								//	{
								//		pclMapManager->pclCurrentMap->PutTile2(0, i, j, 234); // ���ܵ�
								//	}
								//	else if ( g_graphics.GetSurfacePixel(i,j) == 183 ) // �Ķ�
								//	{
								//		pclMapManager->pclCurrentMap->PutTile2(0, i, j, 231); // ����
								//	}
								//	else if ( g_graphics.GetSurfacePixel(i,j) == 63234 ) // ���
								//	{
								//		pclMapManager->pclCurrentMap->PutTile2(0, i, j, 236); // ����2
								//	}
								//	else if ( g_graphics.GetSurfacePixel(i,j) == 26593 ) // �ʷ�
								//	{
								//		pclMapManager->pclCurrentMap->PutTile2(0, i, j, 237); // ����
								//	}
								//	else if ( g_graphics.GetSurfacePixel(i,j) == 19997 ) // �ϴ�
								//	{
								//		pclMapManager->pclCurrentMap->PutTile2(0, i, j, 232); // ����
								//	}
								//	else
								//	{
								//		pclMapManager->pclCurrentMap->PutTile2(0, i, j, 230); // �⺻
								//	}
								//}
								//else
								//{
									if ( g_graphics.GetSurfacePixel(i,j) == 0 ) // ����
									{
										pclMapManager->pclCurrentMap->PutTile2(0, i, j, 70); // ����
									}
									else if ( g_graphics.GetSurfacePixel(i,j) == 61728 ) // ����
									{
										pclMapManager->pclCurrentMap->PutTile2(0, i, j, 30); // ���ܵ�
									}
									else if ( g_graphics.GetSurfacePixel(i,j) == 183 ) // �Ķ�
									{
										pclMapManager->pclCurrentMap->PutTile2(0, i, j, 4); // ����
									}
									else if ( g_graphics.GetSurfacePixel(i,j) == 63234 ) // ���
									{
										pclMapManager->pclCurrentMap->PutTile2(0, i, j, 12); // �߱����ܵ�
									}
									else if ( g_graphics.GetSurfacePixel(i,j) == 26593 ) // �ʷ�
									{
										pclMapManager->pclCurrentMap->PutTile2(0, i, j, 60); // ����
									}
									else if ( g_graphics.GetSurfacePixel(i,j) == 19997 ) // �ϴ�
									{
										pclMapManager->pclCurrentMap->PutTile2(0, i, j, 9); // ����
									}
									else
									{
										pclMapManager->pclCurrentMap->PutTile2(0, i, j, 1); // �⺻
									}
								//}
							}
						}

						// ���� ������ �����.
						if(GameMode != GAMEMODE_SERVER)
						{
							pclMapManager->pclCurrentMap->MakeSmallMap(SMALLMAPMODE_MAPEDIT, NULL);
						}

						pSurface->Release();
						pSurface = NULL;


					}
				}
				EndDialog(hDlg, 0 );
			}
			return TRUE;
		case IDOK:
			{
				hwnd=GetDlgItem(hDlg, IDC_MAP_XSIZE);
				GetWindowText(hwnd, buffer, 10);
				SHORT xsize=_tstoi(buffer);
				
                hwnd=GetDlgItem(hDlg, IDC_MAP_YSIZE);
				GetWindowText(hwnd, buffer, 10);
				SHORT ysize=_tstoi(buffer);
				
				// Ÿ�� ��Ʈ�� �ʱⰪ�� �����Ѵ�.
				GetDlgItemText(hDlg, IDC_EDIT_MAPEDIT_TILESET, buffer, 60);
				SI32 tileset1 = _tstoi(buffer);
				SI32 tileset2 = 0;
				
				//-----------------------------
				// Ÿ�� ��Ʈ�� �ҷ��´�. 
				//-----------------------------
			pclTileManager->LoadTileSet(tileset1, tileset2);
				
				//-----------------------------
				// ������ �ʱ�ȭ�Ѵ�. 
				//-----------------------------
				delete pclMapManager->pclMapArray[pclMapManager->CurrentMapIndex ];
				pclMapManager->pclMapArray[pclMapManager->CurrentMapIndex ] = NULL;
				pclMapManager->pclCurrentMap = NULL;
				
				pclMapManager->pclMapArray[pclMapManager->CurrentMapIndex ] = new cltMapClient(pclMapManager->CurrentMapIndex, 0, xsize, ysize, tileset1, tileset2, pclClient->pclCM, pclClient->pclTileManager, pclClient->pclFieldObjectManager);
				pclMapManager->MakeLastMap(pclMapManager->CurrentMapIndex);
				pclMapManager->pclCurrentMap  = pclMapManager->pclMapArray[pclMapManager->CurrentMapIndex ];
				
				// ������ Ÿ�� ��Ʈ�� ����Ѵ�. 
				pclMapManager->pclCurrentMap ->MH.TileSet1	= tileset1;
				
				// ���� ������ �����.
				if(GameMode != GAMEMODE_SERVER)
				{
					pclMapManager->pclCurrentMap->MakeSmallMap(SMALLMAPMODE_MAPEDIT, NULL);
				}
				EndDialog(hDlg, 0 );
			}
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


void cltMapEdit::OpenMapEditSaveTool()
{
	PopMapFileInitializeMap(GetHwnd());

	// ���� ������ �ִ� ���¿����� ������ �ȵȴ�. 
	if(pclVillageManager)
	{
		SI32 result = MessageBox(NULL, TEXT("���� ������ �������� �����ؾ� ������ ������ �� �ֽ��ϴ�.\n")
			TEXT(" �������� ������ �����ϰ� ������ �����Ͻðڽ��ϱ�?"), 
			TEXT("Warning"), MB_OKCANCEL|MB_ICONEXCLAMATION  );

		if(result == IDOK)
		{
			// ���� ������ �������� �����Ѵ�. 
			Village();
			pclMapManager->pclCurrentMap->DeattachGate();
		}
		else
		{
			return ;
		}
	}
	
	
	GetCurrentDirectory(512, CurrentDirectory);
	   
	if(PopMapFileSaveDlg(GetHwnd(), MapFileName, MapFileShortName))
	{
		pclMapManager->pclCurrentMap->Save(MapFileName);
	}
	
	SetCurrentDirectory(CurrentDirectory);
}

void cltMapEdit::OpenMapEditLoadTool()
{
	TCHAR buffer[256];
	PopMapFileInitializeMap(GetHwnd());	

	// ���� ������ �ִ� ���¿����� �ҷ����Ⱑ  �ȵȴ�. 
	if(pclVillageManager)
	{
		SI32 result = MessageBox(NULL, TEXT("���� ������ �������� �����ؾ� ������ �ҷ��� �� �ֽ��ϴ�. \n") TEXT(" �������� ������ �����ϰ� ������ �ҷ����ðڽ��ϱ�?"), 
			TEXT("Warning"), MB_OKCANCEL|MB_ICONEXCLAMATION  );

		if(result == IDOK)
		{
			// ���� ������ �������� �����Ѵ�. 
			Village();
		}
		else
		{
			return ;
		}
	}
	
	GetCurrentDirectory(512, CurrentDirectory);
	   
	if(PopMapFileOpenDlg(GetHwnd(), MapFileName, MapFileShortName))
	{
		// �۾� ������ ���� ������ �����Ѵ�. 
		SetCurrentDirectory(CurrentDirectory);
		
		// ������ �ҷ��´� 
		delete pclMapManager->pclMapArray[pclMapManager->CurrentMapIndex ];
		pclMapManager->pclMapArray[pclMapManager->CurrentMapIndex ] = NULL;
		pclMapManager->pclCurrentMap = NULL;
		
		
		//----------------------------
		// ������ ����� �м��Ѵ�. 
		//----------------------------
		cltMapHeader clHeader;
		if(GetMapInfo(MapFileName, &clHeader) == FALSE)
		{
			MsgBox(TEXT("12f9nnf"), TEXT("f9j2f:%s"), buffer);
			return ;
		}
		
		
		//-----------------------------
		// Ÿ�� ��Ʈ�� �ҷ��´�. 
		//-----------------------------
		pclTileManager->LoadTileSet(clHeader.TileSet1, clHeader.TileSet2); 
		
		pclMapManager->Load(pclMapManager->CurrentMapIndex, 0, MapFileName, pclCM, pclTileManager,pclFieldObjectManager);
		pclMapManager->MakeLastMap(pclMapManager->CurrentMapIndex);
		
		pclMapManager->pclCurrentMap = pclMapManager->pclMapArray[pclMapManager->CurrentMapIndex ];
		
		// ���� ������ �����.
		pclMapManager->pclCurrentMap->MakeSmallMap(SMALLMAPMODE_MAPEDIT, NULL);
		
		
	}
	   
	SetCurrentDirectory(CurrentDirectory);
}


void cltMapEdit::MapEditAction()
{
	// ȭ���̵�����
	ScrollAction();
	
	SI32 mapx	= pclUnderMouseObject->MapX;
	SI32 mapy	= pclUnderMouseObject->MapY;
	
	// ���¶��� ������ ������Ʈ �Ѵ�. 
	TCHAR str[128];
	StringCchPrintf(str, 128, TEXT("MapX:%d MapY:%d"), mapx, mapy);
	SetStatusBarText(str, 0);
	
	StringCchPrintf(str, 128, TEXT("CurrentMode:%d"), CurrentMode);
	SetStatusBarText(str, 1);
	
	
	if(IpD.LeftPressSwitch==TRUE)
	{
		
		if(CurrentMode == MAPEDIT_MODE_TERRAIN)
		{
			// Terrain�� ������ ���� �ٸ� Ÿ����� ����� �����Ѵ�. 
			if(CurrentTerrainUnique)
			{
				SI32 siref		= pclMapManager->pclCurrentMap->pclTileManager->FindRefFromUnique_TileSet(CurrentTerrainUnique);
				SI32 atb			= pclMapManager->pclCurrentMap->pclTileManager->pclTileInfo[siref]->dwAtb;
				
				if(atb & TILEATB_NODIR)
				{
				}
				else if(atb & TILEATB_8DIR)
				{
					if(atb & TILEATB_LAYER1)
					{
						pclMapManager->pclCurrentMap->PutTile2(0, mapx, mapy, CurrentTerrainUnique);
					}
					else if(atb & TILEATB_LAYER2)
					{
						pclMapManager->pclCurrentMap->PutTile4(1, mapx, mapy, CurrentTerrainUnique);
					}
				}
				
			}
		}
		else if(CurrentMode == MAPEDIT_MODE_FIELDOBJET)
		{
			if(CurrentFieldObjectUnique)
			{
				SI32 ref = pclFieldObjectManager->FindRefFromUniqueMinus(CurrentFieldObjectUnique);
				if ( ref < 0 && pclFieldObjectManager->pclInfo[ref] == NULL ) return ;

				if ( pclFieldObjectManager->pclInfo[ref]->siTreeShadow )
				{
					if ( pclMapManager->pclCurrentMap->PutFieldObject(mapx+1, mapy+1, pclFieldObjectManager->pclInfo[ref]->siTreeShadow ) )
					{
                        if ( pclMapManager->pclCurrentMap->PutFieldObject(mapx, mapy, CurrentFieldObjectUnique) == FALSE )
						{
							pclMapManager->pclCurrentMap->DeleteFieldObject(mapx+1, mapy+1);
						}
					}
				}
				else
				{
					pclMapManager->pclCurrentMap->PutFieldObject(mapx, mapy, CurrentFieldObjectUnique);
				}
				
			}
		}
		else if(CurrentMode == MAPEDIT_MODE_FIELDOBJETBRUSH)
		{
			if(CurrentFieldObjectBrush >=0 && SelectedFieldObjectUnique)
			{
				SI32 ref = pclFieldObjectManager->FindRefFromUniqueMinus(SelectedFieldObjectUnique);
				if ( ref < 0 && pclFieldObjectManager->pclInfo[ref] == NULL ) return ;

				if ( pclFieldObjectManager->pclInfo[ref]->siTreeShadow )
				{
					if ( pclMapManager->pclCurrentMap->PutFieldObject(mapx+1, mapy+1, pclFieldObjectManager->pclInfo[ref]->siTreeShadow ) )
					{
						if ( pclMapManager->pclCurrentMap->PutFieldObject(mapx, mapy, SelectedFieldObjectUnique) == FALSE )
						{
							pclMapManager->pclCurrentMap->DeleteFieldObject(mapx+1, mapy+1);
						}
						else
						{
							SelectedFieldObjectUnique = pclFieldObjectManager->pclFieldObjectBrush[CurrentFieldObjectBrush]->GetRandUnique();
						}
					}
				}
				else
				{
					if(pclMapManager->pclCurrentMap->PutFieldObject(mapx, mapy, SelectedFieldObjectUnique)==TRUE)
					{
						// ������ ������ Object�� �����Ѵ�.
						SelectedFieldObjectUnique = pclFieldObjectManager->pclFieldObjectBrush[CurrentFieldObjectBrush]->GetRandUnique();
					}
				}
			}
		}
		else if(CurrentMode == MAPEDIT_MODE_GEOINFO)
		{
			if(SelectedGeoInfoSlot > 0)
			{
				pclMapManager->pclCurrentMap->pclMapGeoInfo->SetGeoMap(mapx, mapy, SelectedGeoInfoSlot);
			}
		}
		else if(CurrentMode == MAPEDIT_MODE_CUSTOMCOLL)
		{

			div_t dv;

			if( uiCollisionBrush <= 0 || uiCollisionBrush >= MAX_COLLISION_BRUSH_NUM ) uiCollisionBrush = 1;

			dv = div(uiCollisionBrush, 2);

			if(dv.rem == 0)
				uiCollisionBrush -= dv.rem;

			SI32 i=0, j=0;

			SI32 startx = mapx - dv.quot;
			SI32 starty = mapy - dv.quot;

			for(i=0; i<uiCollisionBrush; i++)
			{
				for(j=0; j<uiCollisionBrush; j++)
				{
					// Map������ ��� Custom Collision�� �������Ŀ� �����Ѵ�.
					pclMapManager->pclCurrentMap->DeleteCollMap(startx + i, starty + j, BLOCK_CUSTOM);
					pclMapManager->pclCurrentMap->DeleteCollMap(startx + i, starty + j, BLOCK_EVENT2);
					pclMapManager->pclCurrentMap->DeleteCollMap(startx + i, starty + j, BLOCK_EVENT3);
					pclMapManager->pclCurrentMap->DeleteCollMap(startx + i, starty + j, BLOCK_EVENT4);
					pclMapManager->pclCurrentMap->DeleteCollMap(startx + i, starty + j, BLOCK_EVENT5);
					pclMapManager->pclCurrentMap->DeleteCollMap(startx + i, starty + j, BLOCK_EVENT6);
					pclMapManager->pclCurrentMap->DeleteCollMap(startx + i, starty + j, BLOCK_EVENT7);

					pclMapManager->pclCurrentMap->SetCollMap(startx + i, starty + j, CurrentCustomCollision);

				}
			}

			// Map������ ��� Custom Collision�� �������Ŀ� �����Ѵ�.
			//pclMapManager->pclCurrentMap->DeleteCollMap(mapx, mapy, BLOCK_CUSTOM);
			//pclMapManager->pclCurrentMap->DeleteCollMap(mapx, mapy, BLOCK_EVENT1);
			//pclMapManager->pclCurrentMap->DeleteCollMap(mapx, mapy, BLOCK_EVENT2);
			//pclMapManager->pclCurrentMap->DeleteCollMap(mapx, mapy, BLOCK_EVENT3);
			//pclMapManager->pclCurrentMap->DeleteCollMap(mapx, mapy, BLOCK_EVENT4);
			//pclMapManager->pclCurrentMap->DeleteCollMap(mapx, mapy, BLOCK_EVENT5);
			//pclMapManager->pclCurrentMap->DeleteCollMap(mapx, mapy, BLOCK_EVENT6);
			//pclMapManager->pclCurrentMap->DeleteCollMap(mapx, mapy, BLOCK_EVENT7);

			//pclMapManager->pclCurrentMap->SetCollMap(mapx, mapy, CurrentCustomCollision);
		}
	}
	else if(IpD.RightPressSwitch==TRUE)
	{
		if(CurrentMode == MAPEDIT_MODE_TERRAIN)
		{
			// �θ� Ÿ���� ����ش�.(�����ִ� ȿ��) 
			if(CurrentTerrainUnique)
			{
				SI32 ref		= pclMapManager->pclCurrentMap->pclTileManager->FindRefFromUnique_TileSet(CurrentTerrainUnique);
				SI32 atb		= pclMapManager->pclCurrentMap->pclTileManager->pclTileInfo[ref]->dwAtb;
				
				SI32 unique;
				if(pclMapManager->pclCurrentMap->pclTileManager->pclTileInfo[ref]->pParent)
				{
					unique	= pclMapManager->pclCurrentMap->pclTileManager->pclTileInfo[ref]->pParent->Unique;
					
					if(atb & TILEATB_NODIR)
					{
						// �ƹ� ��ġ�� ���� �ʴ´�. 
					}
					else if(atb & TILEATB_8DIR)
					{
						if(atb & TILEATB_LAYER1)
						{
							pclMapManager->pclCurrentMap->PutTile2(0, mapx, mapy, unique);
						}
						else if(atb & TILEATB_LAYER2)
						{
							pclMapManager->pclCurrentMap->PutTile4(1, mapx, mapy, unique);
							
						}
					}
				}
				
			}
		}
		
		if(CurrentMode == MAPEDIT_MODE_FIELDOBJET
			|| CurrentMode == MAPEDIT_MODE_FIELDOBJETBRUSH)
		{
			//if(CurrentFieldObjectUnique)
			{
				pclMapManager->pclCurrentMap->DeleteFieldObject(mapx, mapy);
			}
		}
		else if(CurrentMode == MAPEDIT_MODE_GEOINFO)
		{
			//if(SelectedGeoInfoSlot > 0)
			{
				pclMapManager->pclCurrentMap->pclMapGeoInfo->SetGeoMap(mapx, mapy, 0);
			}
		}
		else if(CurrentMode == MAPEDIT_MODE_CUSTOMCOLL)
		{
			div_t dv;

			if( uiCollisionBrush <= 0 || uiCollisionBrush >= MAX_COLLISION_BRUSH_NUM ) uiCollisionBrush = 1;

			dv = div(uiCollisionBrush, 2);

			if(dv.rem == 0)
				uiCollisionBrush -= dv.rem;

			SI32 i=0, j=0;

			SI32 startx = mapx - dv.quot;
			SI32 starty = mapy - dv.quot;

			for(i=0; i<uiCollisionBrush; i++)
			{
				for(j=0; j<uiCollisionBrush; j++)
				{
					// Map������ ��� Custom Collision�� �������Ŀ� �����Ѵ�.
					pclMapManager->pclCurrentMap->DeleteCollMap(startx + i, starty + j, BLOCK_CUSTOM);
					pclMapManager->pclCurrentMap->DeleteCollMap(startx + i, starty + j, BLOCK_EVENT2);
					pclMapManager->pclCurrentMap->DeleteCollMap(startx + i, starty + j, BLOCK_EVENT3);
					pclMapManager->pclCurrentMap->DeleteCollMap(startx + i, starty + j, BLOCK_EVENT4);
					pclMapManager->pclCurrentMap->DeleteCollMap(startx + i, starty + j, BLOCK_EVENT5);
					pclMapManager->pclCurrentMap->DeleteCollMap(startx + i, starty + j, BLOCK_EVENT6);
					pclMapManager->pclCurrentMap->DeleteCollMap(startx + i, starty + j, BLOCK_EVENT7);
				}
			}


			//pclMapManager->pclCurrentMap->DeleteCollMap(mapx, mapy, BLOCK_CUSTOM);
			//pclMapManager->pclCurrentMap->DeleteCollMap(mapx, mapy, BLOCK_EVENT1);
			//pclMapManager->pclCurrentMap->DeleteCollMap(mapx, mapy, BLOCK_EVENT2);
			//pclMapManager->pclCurrentMap->DeleteCollMap(mapx, mapy, BLOCK_EVENT3);
			//pclMapManager->pclCurrentMap->DeleteCollMap(mapx, mapy, BLOCK_EVENT4);
			//pclMapManager->pclCurrentMap->DeleteCollMap(mapx, mapy, BLOCK_EVENT5);
			//pclMapManager->pclCurrentMap->DeleteCollMap(mapx, mapy, BLOCK_EVENT6);
			//pclMapManager->pclCurrentMap->DeleteCollMap(mapx, mapy, BLOCK_EVENT7);
		}   
		
		
	}
	
}

void cltMapEdit::PopMapFileInitializeMap(HWND hwnd)
{
	static TCHAR szFilter[]=TEXT("map file(*.,map)\0*.map\0") \
		TEXT("total file(*.*)\0*.*\0\0");
	
	ZeroMemory(&MapFileOpen, sizeof(OPENFILENAME));
	
	MapFileOpen.lStructSize=sizeof(OPENFILENAME);
	MapFileOpen.hwndOwner=hwnd;
	MapFileOpen.lpstrFilter=szFilter;
	MapFileOpen.lpstrFile=NULL;
	MapFileOpen.nMaxFile=_MAX_PATH;
	MapFileOpen.lpstrFileTitle=NULL;
	MapFileOpen.nMaxFileTitle=_MAX_FNAME+_MAX_EXT;
	MapFileOpen.lpstrInitialDir=NULL;
	MapFileOpen.lpstrTitle=NULL;
	MapFileOpen.Flags=0;
	MapFileOpen.nFileOffset=0;
	MapFileOpen.nFileExtension=0;
	MapFileOpen.lpstrDefExt=TEXT("map");
	MapFileOpen.lCustData=0L;
	MapFileOpen.lpfnHook=NULL;
	MapFileOpen.lpTemplateName=NULL;
	
}

void cltMapEdit::PopMapFileInitializeSpr(HWND hwnd)
{
	static TCHAR szFilter[]=TEXT("SPR file(*.,spr)\0*.spr\0") \
		TEXT("total file(*.*)\0*.*\0\0");
	
	ZeroMemory(&MapFileOpen, sizeof(OPENFILENAME));
	
	MapFileOpen.lStructSize=sizeof(OPENFILENAME);
	MapFileOpen.hwndOwner=hwnd;
	MapFileOpen.lpstrFilter=szFilter;
	MapFileOpen.lpstrFile=NULL;
	MapFileOpen.nMaxFile=_MAX_PATH;
	MapFileOpen.lpstrFileTitle=NULL;
	MapFileOpen.nMaxFileTitle=_MAX_FNAME+_MAX_EXT;
	MapFileOpen.lpstrInitialDir=NULL;
	MapFileOpen.lpstrTitle=NULL;
	MapFileOpen.Flags=0;
	MapFileOpen.nFileOffset=0;
	MapFileOpen.nFileExtension=0;
	MapFileOpen.lpstrDefExt=TEXT("spr");
	MapFileOpen.lCustData=0L;
	MapFileOpen.lpfnHook=NULL;
	MapFileOpen.lpTemplateName=NULL;
	
}

//// ����ȭ�� �ҷ�����
BOOL cltMapEdit::PopMapFileOpenDlg(HWND hwnd, TCHAR* pstrFileName,  TCHAR* pstrTitleName)
{
	
	MapFileOpen.hwndOwner=hwnd;
	MapFileOpen.lpstrFile=pstrFileName;
	MapFileOpen.lpstrFileTitle=pstrTitleName;
	MapFileOpen.Flags=OFN_HIDEREADONLY|OFN_CREATEPROMPT;
	
	return GetOpenFileName(&MapFileOpen);
	
}

//// ����ȭ�� �����ϱ� 
BOOL cltMapEdit::PopMapFileSaveDlg(HWND hwnd, TCHAR* pstrFileName, TCHAR* pstrTitleName)
{
	MapFileOpen.hwndOwner	= hwnd;
	MapFileOpen.lpstrFile   = pstrFileName;
	MapFileOpen.lpstrFileTitle=pstrTitleName;
	
	MapFileOpen.Flags=OFN_OVERWRITEPROMPT;
	
	return GetSaveFileName(&MapFileOpen);
}



// Terrain Tree�� �߰��ϴ� ��. (Windows API ���� 690������ ����) 
void cltMapEdit::InsertTree_Terrain(HWND hDlg, HTREEITEM pNode, cltTileInfo* pclParentTileInfo)
{
	SI32 index = 0;
	
	while(pclClient->pclTileManager->pclTileInfo[index])
	{
		
		cltTileInfo* pclTileInfo = pclClient->pclTileManager->pclTileInfo[index];
		
		if(pclParentTileInfo == pclTileInfo->pParent)
		{
			HTREEITEM Node  = TreeViewInsert(GetDlgItem(hDlg, IDC_TREE_TERRAIN), pclTileInfo->szName, pclTileInfo->Unique, pNode);
			
			InsertTree_Terrain(hDlg, Node, pclTileInfo);
		}
		
		index++;
	}
}

// Field Object�� Ʈ���� �߰�. 
void cltMapEdit::InsertTree_FieldObject(HWND hDlg, HTREEITEM pNode, cltFieldObjectTypeInfo* pclParentInfo)
{
	SI32 i;
	
	for(i = 0;i < MAX_FIELDOBJECTTYPE_NUMBER;i++)
	{
		if(pclClient->pclFieldObjectManager->pclTypeInfo[i] == NULL)continue;
		
		cltFieldObjectTypeInfo* pclTypeInfo = pclClient->pclFieldObjectManager->pclTypeInfo[i];
		
		if(pclParentInfo == pclTypeInfo->pParent)
		{
			HTREEITEM Node  = TreeViewInsert(GetDlgItem(hDlg, IDC_TREE_FIELDOBJECT), pclTypeInfo->pszName, pclTypeInfo->Unique, pNode);
			
			// �������� ���� Field Object �߰�. 
			SI32 temp_index = 0;
			while(pclClient->pclFieldObjectManager->pclInfo[temp_index] )
			{
				cltFieldObjectInfo* pclinfo = pclClient->pclFieldObjectManager->pclInfo[temp_index];
				
				if(pclinfo->dwType == pclTypeInfo->dwType)
				{
					TreeViewInsert(GetDlgItem(hDlg, IDC_TREE_FIELDOBJECT), pclinfo->pszName, pclinfo->Unique, Node);
				}
				
				temp_index++;
			}
			
			
			InsertTree_FieldObject(hDlg, Node, pclTypeInfo);
		}
	}
}


// Ʈ��������  �߰��Ѵ�.
HTREEITEM cltMapEdit::TreeViewInsert(HWND hwnd, TCHAR* name, SI32 para, HTREEITEM node)
{
	TV_ITEM tvi;
	TV_INSERTSTRUCT tvis;
	TCHAR cName[256];
	
	if(para == 0)		StringCchPrintf(cName, 256, TEXT("%s"), name);
	else				StringCchPrintf(cName, 256, TEXT("%s (%d)"), name, para);
	
	tvis.hInsertAfter	=	TVI_LAST;
	tvi.mask			=	TVIF_TEXT|TVIF_PARAM; 
	tvi.pszText			=	cName;	// name;
	tvi.lParam			=	para;
	
	if(node == 0)		tvis.hParent		=	TVI_ROOT;
	else				tvis.hParent		=	node;
	
	tvis.item			=	tvi;
	
	return TreeView_InsertItem(hwnd, &tvis);
	
}


void cltMapEdit::InsertFieldObjectBrush(HWND hDlg)
{
	
	SI32 index = 0;
	while(pclFieldObjectManager->pclFieldObjectBrush[index])
	{
		SendMessage(GetDlgItem(hDlg, IDC_FIELDOBJECTBRUSH), LB_ADDSTRING, index, (LPARAM)pclFieldObjectManager->pclFieldObjectBrush[index]->szName);
		index++;
	}
}



//-----------------------------------
// ��ٸ��� ��ȭ ���� ó�� ���� 
//-----------------------------------
BOOL cltMapEdit::ModalessDlgProc(MSG* pmsg)
{
	if(cltClient::ModalessDlgProc(pmsg) == TRUE)
	{
		return TRUE;
	}
	
	if(hMapEditDlg && IsWindow(hMapEditDlg) && IsDialogMessage(hMapEditDlg, pmsg))
	{
		return TRUE;
	}
	
	if(hGeoInfoDlg && IsWindow(hGeoInfoDlg) && IsDialogMessage(hGeoInfoDlg, pmsg))
	{
		return TRUE;
	}
	
	return FALSE;
}

//-----------------------------------
// WM_COMMAND�޽��� ó�� �Լ�. 
//-----------------------------------
bool cltMapEdit::DoMsg_WM_COMMAND(WPARAM wParam)
{
	cltClient::DoMsg_WM_COMMAND(wParam);
	
	switch(LOWORD(wParam))
	{
		
	case ID_TOOLBAR_NEWMAP:
		CreateNewMapTool();
		break;
	case ID_TOOLBAR_LOAD:
		OpenMapEditLoadTool();
		break;
	case ID_TOOLBAR_SAVE:
		OpenMapEditSaveTool();
		break;
		// SEPARATOR
	case ID_TOOLBAR_TERRAINTOOL:
		OpenMapEditTerrainTool();
		break;
	case ID_TOOLBAR_HEADERMANAGER:
		OpenMapEditHeaderManager();
		break;
	case ID_TOOLBAR_GEOINFO:
		CreateGeoInfoTool();
		break;
		// SEPARATOR
		
	case ID_TOOLBAR_CAPTUREMAP:
		if(TABS(CurrentClock  - CaptureClock ) > 1500)
		{
			CaptureClock = CurrentClock;
			
			cltMapClient* pclmap =(cltMapClient*)pclMapManager->pclCurrentMap;
			
			pclmap->MapCapture();
		}
		break;
		
	case ID_TOOLBAR_VILLAGE:
		Village();
		break;
		// SEPARATOR
		
	case ID_TOOLBAR_COLLDRAW:
		{
			cltMapClient* pclmap = (cltMapClient*)pclMapManager->pclCurrentMap;
			if(pclmap->bCollDrawSwitch == false)
			{
				pclmap->bCollDrawSwitch = true;
			}
			else
			{
				pclmap->bCollDrawSwitch = false;
			}
		}
		break;
		
	case ID_TOOLBAR_NEWCOLL:
		pclMapManager->pclCurrentMap->NewFieldObjectSetInMap();
		break;
		// ���� �浹 ��������. 
	case ID_TOOLBAR_CUSTOMCOLL:
		OpenCustomCollision();
		break;

	case ID_TOOLBAR_DELETEUNIQUE:
		DeleteUniqueTool();
		break;
		
		
		
	}
	
	return true;
	
}