#include "..\Client\Client.h"

#include <Graphic.h>
#include <Graphic_Capsule.h>

//------------------------------------
// CommonLogic
//------------------------------------
#include "..\..\CommonLogic\MagicMgr\MagicMgr.h"

//------------------------------------
// Common
//------------------------------------
#include "Bullet\Bullet.h"
#include "Smoke\Smoke.h"
#include "map.h"
#include "..\Resource.h"
#include "..\Order\Order.h"
#include "Char\CharManager\CharManager.h"
#include "Map\FieldObject\FieldObject.h"

//-----------------------------------
// Client
//-----------------------------------
//#include "..\..\Client\ColorTable\ColorTable.h"
#include "..\..\Client\DrawSequence\DrawSequence.h"
#include "Help\Help.h"
#include "..\..\Client\Ninterface\NMinimapdlg\Nminimapdlg.h"

#include "../../mapEdit/mapedit.h"
extern cltCommonLogic* pclClient;

extern	RECT				ScreenRect;							// ������ ǥ�õǴ� ���� 

// ����ؾ� �� �߽� ��ġ�� ���Ѵ�. 
void cltMapClient::GetDrawCenterXY(SI32 x, SI32 y, SI32* pcenterx, SI32* pcentery)
{

	*pcenterx =		   - VirtualMapX * MAP_TILE_XSIZE_HALF
					   + VirtualMapY * MAP_TILE_XSIZE_HALF
					   +x*MAP_TILE_XSIZE_HALF
					   -y*MAP_TILE_XSIZE_HALF
					   + ScreenRect.left+(ScreenRect.right-ScreenRect.left+1)/2;
	
	*pcentery =		   -VirtualMapY*MAP_TILE_YSIZE_HALF
					   -VirtualMapX*MAP_TILE_YSIZE_HALF
					   +ScreenRect.top+(ScreenRect.bottom-ScreenRect.top+1)/2
					   +y*MAP_TILE_YSIZE_HALF 
					   +x*MAP_TILE_YSIZE_HALF ;


}

// ������ �浹 ������ ǥ���Ѵ�. 
void cltMapClient::DrawMapCollInfo()
{
	if(bCollDrawSwitch == false)return;

	SI32 i, j;
	SI32 centerx, centery;
	int clipx1, clipy1, clipx2, clipy2;

	cltClient* pclclient = (cltClient*)pclClient;

	GP.GetClipArea(clipx1, clipy1, clipx2, clipy2 );
	GP.SetClipArea(0, 0, pclclient->siClientScreenXsize - 1, pclclient->siClientScreenYsize - 1 );

	   for(i = VirtualMapY - pclclient->siClientScreenHalfSize;i < VirtualMapY + pclclient->siClientScreenHalfSize;i++)
		   for(j = VirtualMapX - pclclient->siClientScreenHalfSize;j < VirtualMapX + pclclient->siClientScreenHalfSize;j++)
		   {
			   
			   // ���������� ����.
			   if(IsInMapArea(j, i) == true)
			   {
				   // ����ؾ� �� �߽� ��ġ�� ���Ѵ�. 
				   GetDrawCenterXY(j, i, &centerx, &centery);

				   SI32 collinfo = CalcCollInfo(j, i);
				   // �����Ӽ��� ǥ������ �ʴ´�. 
				   if(collinfo & BLOCK_LAND)
				   {
					   collinfo -= BLOCK_LAND;
				   }

				   if(collinfo)
				   {
					   SHORT _screenx, _screeny;
					   GetCenterXY(j, i, _screenx, _screeny);
					   
					   if(collinfo& BLOCK_CUSTOM)
					   {
						   GP.FillBox(_screenx - 15, _screeny - 15, _screenx + 15, _screeny + 15, 100,FALSE);
					   }
					   else if(collinfo& BLOCK_EVENT1)
					   {
						   GP.FillBox(_screenx - 15, _screeny - 15, _screenx + 15, _screeny + 15, 40,FALSE);
					   }
					   else if(collinfo& BLOCK_EVENT2)
					   {
						   GP.FillBox(_screenx - 15, _screeny - 15, _screenx + 15, _screeny + 15, 228,FALSE);
					   }
	   				   else if(collinfo& BLOCK_EVENT3)
					   {
						   GP.FillBox(_screenx - 15, _screeny - 15, _screenx + 15, _screeny + 15, 98,FALSE);
						   //g_graphics.FillBox16C(_screenx - 15, _screeny - 15, _screenx + 15, _screeny + 15, MakeRGB16(0,0,0));
					   }
					   else if(collinfo& BLOCK_EVENT4)
					   {
						   GP.FillBox(_screenx - 15, _screeny - 15, _screenx + 15, _screeny + 15, 130,FALSE);
						   //g_graphics.FillBox16C(_screenx - 15, _screeny - 15, _screenx + 15, _screeny + 15, MakeRGB16(0,0,0));
					   }
					   else if(collinfo& BLOCK_EVENT5)
					   {
						   GP.FillBox(_screenx - 15, _screeny - 15, _screenx + 15, _screeny + 15, 180,FALSE);
						   //g_graphics.FillBox16C(_screenx - 15, _screeny - 15, _screenx + 15, _screeny + 15, MakeRGB16(0,0,0));
					   }
					   else if(collinfo& BLOCK_EVENT6)
					   {
						   GP.FillBox(_screenx - 15, _screeny - 15, _screenx + 15, _screeny + 15, 200,FALSE);
						   //g_graphics.FillBox16C(_screenx - 15, _screeny - 15, _screenx + 15, _screeny + 15, MakeRGB16(0,0,0));
					   }
					   else if(collinfo& BLOCK_EVENT7)
					   {
						   GP.FillBox(_screenx - 15, _screeny - 15, _screenx + 15, _screeny + 15, 230,FALSE);
						   //g_graphics.FillBox16C(_screenx - 15, _screeny - 15, _screenx + 15, _screeny + 15, MakeRGB16(0,0,0));
					   }
				

					   GP.FillBox(_screenx - 10, _screeny - 10, _screenx + 10, _screeny + 10, 0,FALSE);
				   }
			   }
			   
		   }

	GP.SetClipArea(clipx1, clipy1, clipx2, clipy2 );
}


// ���� ���콺�� ��ġ�� Ÿ���� ��ġ�� ǥ���Ѵ�. 
void cltMapClient::DrawCurrentTilePos(SI32 mapx, SI32 mapy)
{
	if(IsInMapArea(mapx, mapy) == false )return ;

	// ����ؾ� �� �߽� ��ġ�� ���Ѵ�. 
	SI32 centerx, centery;
	GetDrawCenterXY(mapx, mapy, &centerx, &centery);
	
	UI08 color = 200;

	GP.Line(centerx-MAP_TILE_XSIZE_HALF, centery, centerx, centery -MAP_TILE_YSIZE_HALF, color ,FALSE);
	GP.Line(centerx, centery-MAP_TILE_YSIZE_HALF, centerx+MAP_TILE_XSIZE_HALF, centery, color,FALSE );

	GP.Line(centerx-MAP_TILE_XSIZE_HALF, centery, centerx, centery +MAP_TILE_YSIZE_HALF, color,FALSE );
	GP.Line(centerx, centery+MAP_TILE_YSIZE_HALF, centerx+MAP_TILE_XSIZE_HALF, centery, color ,FALSE);

	GP.FillBox(centerx-5,  centery-5, centerx+5,  centery+5, color,FALSE);






}


// ���� Ÿ���� �׸���. 
BOOL cltMapClient::DrawMap()
{
 
	int i, j;
	SI32 centerx, centery;
	int clipx1, clipy1, clipx2, clipy2;
	SI32 pgroup = 0;

	cltClient* pclclient = (cltClient*)pclClient;

	
	if(GP.LockSurface(pclclient->lpScreenMapBuffer )==FALSE ) return FALSE;
	
	GP.GetClipArea(clipx1, clipy1, clipx2, clipy2 );
	GP.SetClipArea(0, 0, pclclient->siClientScreenXsize-1, pclclient->siClientScreenYsize-1 );

	// �� �����ʹ� ������ ��´�. 
	if(pclClient->GameMode == GAMEMODE_MAPEDIT)
	{
		bMapDrawSwitch = true;
	}

	
	// �������� ��ũ��
	if((VirtualMapX  + 1 == siOldVirtualMapX) && (VirtualMapY  + 1 == siOldVirtualMapY))
	{
		Scroll_North(pclclient);
	}
	// �������� ��ũ�� 
	else if((VirtualMapX  - 1 == siOldVirtualMapX) && (VirtualMapY  - 1 == siOldVirtualMapY))
	{
		Scroll_South(pclclient);
	}
	// �������� ��ũ�� 
	else if((VirtualMapX  - 1 == siOldVirtualMapX) && (VirtualMapY  + 1 == siOldVirtualMapY))
	{
		Scroll_East(pclclient);
	}
	// �������� ��ũ�� 
	else if((VirtualMapX  + 1 == siOldVirtualMapX) && (VirtualMapY  - 1 == siOldVirtualMapY))
	{
		Scroll_West(pclclient);
	}
	// �ϵ������� ��ũ��
	else if((VirtualMapX   == siOldVirtualMapX) && (VirtualMapY  + 1 == siOldVirtualMapY))
	{
		Scroll_NorthEast(pclclient);
	}
	// �ϼ������� ��ũ��
	else if((VirtualMapX + 1 == siOldVirtualMapX) && (VirtualMapY  == siOldVirtualMapY))
	{
		Scroll_NorthWest(pclclient);
	}
	// ���������� ��ũ��
	else if((VirtualMapX  == siOldVirtualMapX) && (VirtualMapY - 1 == siOldVirtualMapY))
	{
		Scroll_SouthWest(pclclient);
	}
	// ���������� ��ũ��
	else if((VirtualMapX - 1 == siOldVirtualMapX) && (VirtualMapY  == siOldVirtualMapY))
	{
		Scroll_SouthEast(pclclient);
	}
	// ������ �ٽ� �׸���. 
	else if(bMapDrawSwitch == true)
	{
		if(VirtualMapX < pclclient->siClientScreenHalfSize || VirtualMapX > MH.MapXsize - pclclient->siClientScreenHalfSize
		|| VirtualMapY < pclclient->siClientScreenHalfSize || VirtualMapY > MH.MapYsize - pclclient->siClientScreenHalfSize)
		{
			GP.FillBox(0, 0, pclclient->siClientScreenXsize-1, pclclient->siClientScreenYsize-1, (UI08)0,TRUE);
		}
		   

	   for(i = VirtualMapY - pclclient->siClientScreenHalfSize;i < VirtualMapY + pclclient->siClientScreenHalfSize;i++)
		   for(j = VirtualMapX - pclclient->siClientScreenHalfSize;j < VirtualMapX + pclclient->siClientScreenHalfSize;j++)
		   {
			   // ���������� ����.
			   if(IsInMapArea(j, i) == false)continue;

			   // ����ؾ� �� �߽� ��ġ�� ���Ѵ�. 
			   GetDrawCenterXY(j, i, &centerx, &centery);

			   if(pclLayer[1]->GetDrawInfo_Unique(j, i) != 90)
			   {
				   DrawLayer(centerx, centery, 1, j, i);
			   }
			   else
			   {
				   DrawLayer(centerx, centery, 0, j, i);
			   }
		}
	}

	bMapDrawSwitch = false;

	GP.UnlockSurface(pclclient->lpScreenMapBuffer );

	GP.SetClipArea(clipx1, clipy1, clipx2, clipy2 );

	// ���� �ֱ��� VirtualX, Y�� ����Ѵ�. 
	siOldVirtualMapX = VirtualMapX;
	siOldVirtualMapY = VirtualMapY;
		
	return TRUE;
}


// ���� ������ �������� �׸���. 
void cltMapClient::DrawLandItem()
{
	SI32 i, j;
	SI32 centerx, centery;

	cltClient* pclclient = (cltClient*)pclClient;

	for(i=(VirtualMapY-pclclient->siClientScreenHalfSize);i<(VirtualMapY+pclclient->siClientScreenHalfSize);i++)
		for(j=(VirtualMapX-pclclient->siClientScreenHalfSize);j<(VirtualMapX+pclclient->siClientScreenHalfSize);j++)
		{
			if(IsInMapArea(j, i) == false)continue;

			cltItemMapInfo* pclinfo = &pclItemMap[j+ YOff[i]];

			if(pclinfo->uiItemUnique)
			{
				SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique(pclinfo->uiItemUnique);
				if(ref > 0)
				{
				   // ����ؾ� �� �߽� ��ġ�� ���Ѵ�. 
				   GetDrawCenterXY(j, i, &centerx, &centery);

					TSpr* pSpr = pclClient->GetGlobalSpr(GIMG_FIELDITEM);

					if(pSpr)
					{
						//cyj �ٴڿ� �������� ��� �������ָӴϷ� ���̵��� ����
						//SI32 fnt = pclClient->pclItemManager->pclItemInfo[ref]->siSmallImageIndex;
						SI32 fnt = 0;
						GP.PutSpr(pSpr, centerx - (pSpr->GetXSize() /2), centery - (pSpr->GetYSize() /2), fnt);
					}
				}
			}

		}
}

// ĳ���͸� ������ �׸���. 
void cltMapClient::DrawCharInMap(SI32 x, SI32 y)
{
	SI32 id;
	SI32 length;
	cltClient* pclclient = (cltClient*)pclClient;

	SI32 index = 0;
	while(id = pclClient->pclCM->GetCharOrder(index))
	{
		index++;

		if(pclClient->pclCM->IsValidID(id))
		{
			length = max( TABS(pclCM->CR[id]->GetX() - x), TABS(pclCM->CR[id]->GetY() - y));

			if( true == g_SoundOnOffDlg.m_bAloneDraw )
			{
				if( id == 1 || 
					pclCM->CR[id]->pclKI->IsAtb(ATB_MONSTER) ||
					pclCM->CR[id]->pclKI->IsAtb(ATB_SYSTEMNPC) ||
					pclCM->CR[id]->pclKI->IsAtb(ATB_DEFAULTCASTLE) )
				{
					// �ʹ� �� �Ÿ��� �ִ� ĳ���ʹ� ������� �ʴ´�. 
					if(length > 25)
						continue;
					if(GetFogMap(pclCM->CR[id]->GetX(), pclCM->CR[id]->GetY()) >= FOG_HALF)
						continue;

					// �ٸ� ��� ��ȯ���� �� �׷��ش�
					if( id != 1 && pclCM->CR[id]->clIdentity.siIdentity == IDENTITY_PERSON_SUMMON )
						continue;

					if(pclCM->CR[id]->GetCurrentOrder() == ORDER_DEAD)
					{
						((cltCharClient*)(pclCM->CR[id]))->Draw();
					}
					else
					{
						cltDrawObjData cldata(DRAWOBJ_TYPE_CHAR, id);
						pclclient->pclDrawSequence->Push(pclCM->CR[id]->GetX(), pclCM->CR[id]->GetY(), 1, 1, &cldata);
					}
				}
			}
			else
			{
				// �ʹ� �� �Ÿ��� �ִ� ĳ���ʹ� ������� �ʴ´�. 
				if(length > 25)continue;
				if(GetFogMap(pclCM->CR[id]->GetX(), pclCM->CR[id]->GetY()) >= FOG_HALF)continue;

				if(pclCM->CR[id]->GetCurrentOrder() == ORDER_DEAD)
				{
					((cltCharClient*)(pclCM->CR[id]))->Draw();
				}
				else
				{
					cltDrawObjData cldata(DRAWOBJ_TYPE_CHAR, id);
					pclclient->pclDrawSequence->Push(pclCM->CR[id]->GetX(), pclCM->CR[id]->GetY(), 1, 1, &cldata);
				}
			}
		}
	}
}

// ĳ���� �̸��� ǥ���Ѵ�. 
void cltMapClient::DrawCharName()
{
	SI32 i, j;
	SI32 id;

	cltClient* pclclient = (cltClient*)pclClient;

	for(i=(VirtualMapY-pclclient->siClientScreenHalfSize);i<=(VirtualMapY+pclclient->siClientScreenHalfSize);i++)
		for(j=(VirtualMapX-pclclient->siClientScreenHalfSize);j<=(VirtualMapX+pclclient->siClientScreenHalfSize);j++)
		{
			if(IsInMapArea(j, i) == false)continue;

			id = GetIDMap(j, i);
			if(id)
			{
				pclCM->CR[id]->DrawName();
			}
		}
		// ������� for
}

// ���� Ÿ���� ������ �� ��Ҹ� �׸���. 
BOOL cltMapClient::DrawObj()
{
	SHORT i, j;
	cltClient* pclclient = (cltClient*)pclClient;


	// ĳ���͸� ������ �׸���. 
	DrawCharInMap(VirtualMapX, VirtualMapY);

		
		for(i=(VirtualMapY-pclclient->siClientScreenHalfSize-6);i<=(VirtualMapY+pclclient->siClientScreenHalfSize+6);i++)
			for(j=(VirtualMapX-pclclient->siClientScreenHalfSize-6);j<=(VirtualMapX+pclclient->siClientScreenHalfSize+6);j++)
			{
				if(IsInMapArea(j, i) == false)continue;
				
				SI32 fieldobject = GetFieldObject_Unique(j, i);
				if(fieldobject && GetFieldObjectLengthToBottom(j, i) == 0 && GetFieldObjectLengthToRight(j, i) == 0)
				{
					SHORT cx, cy;
					GetCenterXYByMapCenterXY(j, i, cx, cy);

					SI32 ref	= pclClient->pclFieldObjectManager->FindRefFromUniqueMinus(fieldobject);
					if(ref >= 0)
					{
						SI32 type	= pclClient->pclFieldObjectManager->pclInfo[ref]->dwType;

						//��������� �� ������ �ϵ忡�� �о�´�.
						pclClient->pclFieldObjectManager->pclInfo[ref]->LoadDetailInfo();

						// �ٴڿ� ��� �������̸� 
						if(pclClient->pclFieldObjectManager->pclTypeInfo[type]->dwAtb & FOATB_FLOOR)
						{
							DrawFieldObject(j, i, cx, cy, fieldobject);
						}
						else
						{

							cltFieldObjDrawData clfodata;
							
							clfodata.x			= j;
							clfodata.y			= i;
							clfodata.cx			= cx;
							clfodata.cy			= cy;
							clfodata.founique	= fieldobject;
							clfodata.type		= type;
							
							cltDrawObjData cldata(DRAWOBJ_TYPE_FIELDOBJ, &clfodata);
							pclclient->pclDrawSequence->Push(
								j-pclClient->pclFieldObjectManager->pclInfo[ref]->TileXsize + 1, 
								i-pclClient->pclFieldObjectManager->pclInfo[ref]->TileYsize + 1, 
								pclClient->pclFieldObjectManager->pclInfo[ref]->TileXsize, 
								pclClient->pclFieldObjectManager->pclInfo[ref]->TileYsize, 
								&cldata);

						}
					}
				}

				if(pclClient->GameMode == GAMEMODE_MAPEDIT)
				{
					//	if(GetIDMap(j, i))
					{
						SHORT _screenx, _screeny;
						
						GetCenterXY(j, i, _screenx, _screeny);
						GP.FillBox(_screenx - 1, _screeny - 1, _screenx + 1, _screeny + 1, 16,FALSE);
					}
				}

				
			}
			// ������� for

				
	// ���� ������ �������� �׸���. 
	DrawLandItem();
	
	// �̴ϸʿ� ǥ���Ͽ� �� ������ �ʱ�ȭ �Ѵ�. ĳ���͸� �׷��ָ鼭 �ٽ� ä������.
	((CNMiniMapDlg*)pclclient->m_pDialog[NMINIMAP_DLG])->ClearMinimapNPC();

	cltDrawObjData *pcldata = pclclient->pclDrawSequence->Pop();	
	while( pcldata )
	{
		switch(pcldata->siType)
		{
		case DRAWOBJ_TYPE_CHAR:
			((cltCharClient*)(pclCM->CR[pcldata->siID]))->Draw();
			break;

		case DRAWOBJ_TYPE_FIELDOBJ:
			DrawFieldObject(pcldata->clFODrawData.x, pcldata->clFODrawData.y, pcldata->clFODrawData.cx, pcldata->clFODrawData.cy, pcldata->clFODrawData.founique);

			// �����̸� �̸��� ����ش�. 
			if(pcldata->clFODrawData.type == FOTYPE_VILLAGE)
			{
				SI32 villageunique = GetFieldObjectPara(pcldata->clFODrawData.x, pcldata->clFODrawData.y);
				
				SHORT centerx, centery;
				GetRefXY(pcldata->clFODrawData.x, pcldata->clFODrawData.y, centerx, centery);
				
				if(villageunique >=0 && pclClient->pclVillageManager->pclVillageInfo[villageunique])
				{
					pclClient->pclVillageManager->pclVillageInfo[villageunique]->Draw(centerx, centery);


					//------------------------------------------
					// ���ɵ� ���¶�� �ҵ� �׷��ش�. 
					//------------------------------------------
					if(pclClient->pclVillageManager->pclVillageInfo[villageunique]->bEnemyCaptureSwitch)
					{
						DrawFire(pcldata->clFODrawData.x,	pcldata->clFODrawData.y, pcldata->clFODrawData.cx, pcldata->clFODrawData.cy - 10, 0);
						DrawFire(pcldata->clFODrawData.x,	pcldata->clFODrawData.y, pcldata->clFODrawData.cx - 40, pcldata->clFODrawData.cy- 20, 1);
						DrawFire(pcldata->clFODrawData.x,	pcldata->clFODrawData.y, pcldata->clFODrawData.cx + 40, pcldata->clFODrawData.cy-20, 2);
						DrawFire(pcldata->clFODrawData.x,	pcldata->clFODrawData.y, pcldata->clFODrawData.cx - 60, pcldata->clFODrawData.cy-60, 3);


					}
				}


			}
			break;
		default:
			break;
		}

		pcldata = pclclient->pclDrawSequence->Pop();
	}

	// 2003.10.29
	// ���⸦ �׸������� �Ѿ��� �׸��� ������ ���� �ٲ�

	
	// ���⸦ �׸���. 
	pclClient->pclSmokeManager->Draw();

	// �Ѿ��� �׸���. 
	pclClient->pclBulletManager->Draw();
	
	// ������ �׸���. 
	pclClient->pclMagicManager->Draw();
	

	// ������ �浹 ������ ǥ���Ѵ�. 
	DrawMapCollInfo();
	
	// ���� ���콺�� ��ġ�� Ÿ���� ��ġ�� ������ OBJECT�� �׷��ش�.
	if(pclClient->GameMode == GAMEMODE_MAPEDIT)
	{
		SI32 siX = pclclient->pclUnderMouseObject->MapX;
		SI32 siY = pclclient->pclUnderMouseObject->MapY;
		
		switch(((cltMapEdit *)pclClient)->CurrentMode)
		{
		case MAPEDIT_MODE_FIELDOBJETBRUSH:
		case MAPEDIT_MODE_FIELDOBJET:
			if(IsInMapArea(siX, siY))
			{
				SI32 siUnique	= ((cltMapEdit *)pclClient)->SelectedFieldObjectUnique;
				SI32 ref		= pclFieldObjectManager->FindRefFromUniqueMinus(siUnique);
				if(ref>0)
				{
					//SI32 tilexsize	= pclFieldObjectManager->pclInfo[ref]->TileXsize;
					//SI32 tileysize	= pclFieldObjectManager->pclInfo[ref]->TileYsize;
					SI32 tilecenterx = pclFieldObjectManager->pclInfo[ref]->TileCenterX;
					SI32 tilecentery = pclFieldObjectManager->pclInfo[ref]->TileCenterY;
					
					SI32 siDrawX = siX + tilecenterx;
					SI32 siDrawY = siY + tilecentery;

					SHORT cx, cy;
					GetCenterXYByMapCenterXY(siDrawX, siDrawY, cx, cy);

					DrawFieldObject(siDrawX, siDrawY, cx, cy, siUnique, TRANSPARENT_MODE_SCREEN);
				}
				
				DrawCurrentTilePos(siX, siY);
			}
			break;
		case MAPEDIT_MODE_CUSTOMCOLL:
			{
				POINT mousePoint;
				GetCursorPos( &mousePoint );
				ScreenToClient( ((cltMapEdit *)pclClient)->GetHwnd(), &mousePoint );

				SI32 _screenx = mousePoint.x + ((cltMapEdit *)pclClient)->GetDrawStartX();
				SI32 _screeny = mousePoint.y + 16;

				SI32 CurrentCustomCollision = ((cltMapEdit *)pclClient)->CurrentCustomCollision;
				UI08 uiCollisionBrush = ((cltMapEdit *)pclClient)->uiCollisionBrush;
				uiCollisionBrush--;
				if( uiCollisionBrush <= 0 || uiCollisionBrush >= MAX_COLLISION_BRUSH_NUM ) uiCollisionBrush = 1;

				UI08 uiColor = 0;

				if( CurrentCustomCollision  & BLOCK_CUSTOM)
				{
					uiColor = 100;
				}
				else if( CurrentCustomCollision & BLOCK_EVENT2)
				{
					uiColor = 228;
				}
				else if( CurrentCustomCollision & BLOCK_EVENT3)
				{
					uiColor = 98;
				}
				else if( CurrentCustomCollision & BLOCK_EVENT4)
				{
					uiColor = 130;
				}
				else if( CurrentCustomCollision & BLOCK_EVENT5)
				{
					uiColor = 180;
				}
				else if( CurrentCustomCollision & BLOCK_EVENT6)
				{
					uiColor = 200;
				}
				else if( CurrentCustomCollision & BLOCK_EVENT7)
				{
					uiColor = 230;
				}

				SI32 startx = _screenx - MAP_TILE_XSIZE_HALF * uiCollisionBrush;
				SI32 starty = _screeny - MAP_TILE_YSIZE_HALF * uiCollisionBrush;
				SI32 width = MAP_TILE_XSIZE * uiCollisionBrush;
				SI32 height = MAP_TILE_YSIZE * uiCollisionBrush;
				GP.Box( startx, starty, startx + width, starty + height, uiColor);
				GP.Box( startx + 1, starty + 1, startx + width - 1, starty + height -1 , uiColor);

				GP.Line( startx, _screeny, _screenx, starty,  40, false );
				GP.Line( _screenx, starty, startx + width, _screeny, 40, false );
				GP.Line( startx + width, _screeny, _screenx, starty + height, 40, false );
				GP.Line( _screenx, starty + height, startx, _screeny, 40, false );

				GP.Box(_screenx - 10 * uiCollisionBrush, _screeny - 10 * uiCollisionBrush, _screenx + 10 * uiCollisionBrush, _screeny + 10 * uiCollisionBrush, 0);       
			}
			break;

		}
	}

	PopEffect();

			
	return TRUE;
}

// ���� ���� �����͸� �����ش�. 
void cltMapClient::SetGeoInfo(HDC hdc)
{
	SI32 i, j;
	SI32 centerx, centery;
	TCHAR buffer[256];

	cltClient* pclclient = (cltClient*)pclClient;

	// ��Ʈ�� �����Ѵ�. 
	HFONT hFont = g_FontManager.SetFont();
	HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);

	SetBkMode(hdc, TRANSPARENT);

	// ���������� ��ġ ������ �ʱ�ȭ�Ѵ�. 
	pclMapGeoInfo->InitGeoPosInfo();

   for(i = VirtualMapY - pclclient->siClientScreenHalfSize;i < VirtualMapY + pclclient->siClientScreenHalfSize;i++)
   {
	   for(j = VirtualMapX - pclclient->siClientScreenHalfSize;j < VirtualMapX + pclclient->siClientScreenHalfSize;j++)
	   {
		   // ���������� ����.
		   if(IsInMapArea(j, i) == true)
		   {
			   // ����ؾ� �� �߽� ��ġ�� ���Ѵ�. 
			   GetDrawCenterXY(j, i, &centerx, &centery);
			   
			   SI32 data = pclMapGeoInfo->GetGeoMap(j, i);
			   if(data )
			   {
				   // �������� ��ġ�� ������Ʈ �Ѵ�. 
				   pclMapGeoInfo->UpdateGeoPos(j, i, data);

				   // �ʿ������ΰ�쿡�� ǥ���Ѵ�. 
				   if(pclClient->GameMode == GAMEMODE_MAPEDIT)
				   {
					   StringCchPrintf(buffer, 256, TEXT("%d"), data);
					   
					   // ���ڿ��� ����� ���Ѵ�. 
					   SIZE size;
					   GetTextExtentPoint32(hdc, buffer, lstrlen(buffer), &size);
					   
					   TextOut(hdc, centerx-size.cx/2, centery-size.cy/2, buffer, lstrlen(buffer));
				   }
				   
			   }
		   }
	   }
   }


/////////////////////////

	if(pclClient->GameMode == GAMEMODE_MAPEDIT)
	{
		StringCchPrintf(buffer, 256, TEXT("%d , %d"), pclclient->pclUnderMouseObject->MapX ,pclclient->pclUnderMouseObject->MapY );
		TextOut(hdc, 500, 700, buffer, lstrlen(buffer));
		SelectObject(hdc, hOldFont);
	}

}

// ���� ���� �����͸� �����ش�. 
void cltMapClient::DrawGeoInfo(LPDIRECTDRAWSURFACE7 lpsurface, cltHelpManager* pclhelpmanager)
{
	SI32 i;
	SI32 centerx, centery;

   // ���������� ȭ�鿡 ����Ѵ�. 
   for(i = 0;i < MAX_GEO_NUMBER;i++)
   {
	   if(pclMapGeoInfo->siGeoPosAccount[i] > 0)
	   {
		   SI32 x = pclMapGeoInfo->siGeoPosX[i] /  pclMapGeoInfo->siGeoPosAccount[i];
		   SI32 y = pclMapGeoInfo->siGeoPosY[i] /  pclMapGeoInfo->siGeoPosAccount[i];
		   TCHAR* text = pclMapGeoInfo->szGetText[i];
		   
		   
		   if(IsInScreenTile(x, y) == TRUE)
		   {
			   // ����ؾ� �� �߽� ��ġ�� ���Ѵ�. 
			   GetDrawCenterXY(x, y, &centerx, &centery);

			   SI32 helpref = pclhelpmanager->GetHelp(text);
			   if(helpref >= 0)
			   {
				   pclhelpmanager->SetPos(helpref, centerx, centery);

			   }
			   else
			   {
					pclhelpmanager->Add(text, centerx, centery);
			   }

			   pclhelpmanager->Draw(lpsurface);

		   }
	   }
	   
   }
}

// ���� �׷��ش�. 
void cltMapClient::DrawFire(SHORT mapx, SHORT mapy, SHORT cx, SHORT cy, SI32 file)
{
	TSpr* pspr	= pclClient->GetGlobalSpr(GIMG_FIRE1 + file);

	if(pspr == NULL)return ;

	//-------------------------
	// ��� ���� ��ġ�� ã�´�.
	//-------------------------
	SI32 startx = cx - (pspr->GetXSize()/2)					;//+ pclFieldObjectManager->pclInfo[ref]->IndentX;
	SI32 starty = cy + MAP_TILE_YSIZE_HALF - pspr->GetYSize()	;//+ pclFieldObjectManager->pclInfo[ref]->IndentY;

	SI32 font = (pclClient->CurrentClock / 100) % pspr->GetImageNum();

	GP.PutSprLight1(pspr, startx, starty, font);

}

void cltMapClient::DrawFieldObject(SHORT mapx, SHORT mapy, SHORT cx, SHORT cy, SI32 fieldobjectunique, SI32 siForceTransMode)
{

	SI32 ref = pclFieldObjectManager->FindRefFromUniqueMinus(fieldobjectunique);
	if(ref < 0)return ;

	SI32 file = 0;
    SI32 font = 0;

	TSpr* pspr = pclFieldObjectManager->pclInfo[ref]->GetSpr(pclFieldObjectManager, pclClient->GetFrame());
	if(pspr == NULL)
	{
		return;
	}

	//-----------------------------------------------
	// ����� �ٰ��� Ÿ���� centerx, centery�� ���Ѵ�. 
	//------------------------------------------------
	SI32 tilex = mapx;
	SI32 tiley = mapy;

	//-------------------------
	// ��� ���� ��ġ�� ã�´�.
	//-------------------------
	SI32 startx = cx - (pspr->GetXSize()/2)					+ pclFieldObjectManager->pclInfo[ref]->IndentX;
	SI32 starty = cy + MAP_TILE_YSIZE_HALF - pspr->GetYSize()	+ pclFieldObjectManager->pclInfo[ref]->IndentY;

	//------------------------------
	// ����ؾ� �� �̹����� ã�´�. 
	//------------------------------
/*	if ( ref == 511 )
	{
		int sss = 0 ;
	}*/
	SI32 aniframe = pclFieldObjectManager->pclInfo[ref]->AniFrame;
	if(aniframe == 0)aniframe = 1;

	SI32 anidelay = pclFieldObjectManager->pclInfo[ref]->AniDelay;
	if(anidelay == 0)anidelay = 1;

	//font =   ( (pclClient->GetFrame() + GetFieldObjectRandomValue(tilex, tiley)) / anidelay)  % aniframe;
	font =   ( ( max(0, pclClient->CurrentClock / 50) + GetFieldObjectRandomValue(tilex, tiley)) / anidelay)  % aniframe;

	SI32 maxfont = pspr->GetImageNum() ;
	if ( font >= maxfont )
		return;

	SI32 simode = pclFieldObjectManager->pclInfo[ref]->siTransMode;
	if(siForceTransMode)	simode = siForceTransMode;
	SI32 alphavalue = pclFieldObjectManager->pclInfo[ref]->siAlphaValue ;
	if ( alphavalue < 0 || alphavalue > 8 ) alphavalue = 4 ;
	
	//--------------------
	// �̹����� ����Ѵ�. 
	//--------------------

	if(pspr->pImage)
	{
		SI32 xsize = pspr->GetXSize();
		SI32 ysize = pspr->GetYSize();

		if(GP.IsInClipArea(startx, starty, startx + xsize-1, starty + ysize-1) == TRUE)
		{
			SI32 mprmode = 0 ;
			switch(simode)
			{
			case TRANSPARENT_MODE_SCREEN: mprmode = PUT_SPR_SCREEN ; break;
			case TRANSPARENT_MODE_NORMAL: mprmode = PUT_SPR_SPR ; break;
			case TRANSPARENT_MODE_OLDTRANS:
			case TRANSPARENT_MODE_HALFTRANS:
			case TRANSPARENT_MODE_MULTIPLY: mprmode = PUT_SPR_MULTIPLY ; break;
			case TRANSPARENT_MODE_ADD: break;
			case TRANSPARENT_MODE_ALPHA: mprmode = PUT_SPR_ALPHA ; break ;
			default: mprmode = PUT_SPR_SPR ; break;
			}

			GP.PutMpr(pspr, startx, starty, mprmode, FALSE, font,alphavalue );

		}
		else
		{
			SI32 mprmode = 0 ;
			switch(simode)
			{
			case TRANSPARENT_MODE_SCREEN: mprmode = PUT_SPR_SCREEN ; break;
			case TRANSPARENT_MODE_NORMAL: mprmode = PUT_SPR_SPR ; break;
			case TRANSPARENT_MODE_OLDTRANS:
			case TRANSPARENT_MODE_HALFTRANS:
			case TRANSPARENT_MODE_MULTIPLY: mprmode = PUT_SPR_MULTIPLY ; break;
			case TRANSPARENT_MODE_ADD:
			case TRANSPARENT_MODE_ALPHA: mprmode = PUT_SPR_ALPHA ; break ;
			default: mprmode = PUT_SPR_SPR ; break;
			}
			
			GP.PutMpr(pspr, startx, starty, mprmode, TRUE , font,alphavalue);
		}
	}
	// ������ �̹����� �ε����� ���ߴٸ� �� ������ ǥ�����ش�. 
	else
	{
		TCHAR buffer[256];
		StringCchPrintf(buffer, 256, TEXT("Field Object is Empty:%d"), fieldobjectunique);
		pclClient->pclMessage->SetMsg(buffer);
	}


}


// ���� ��Ҹ� �׸��� �Լ��� 
// ����� �׸���. 
BOOL cltMapClient::DrawLayer(SHORT centerx, SHORT centery, SI32 layer, SHORT x, SHORT y)
{

	SHORT startx, starty;
	SHORT ref, file, font;
	int sx1, sy1, sx2, sy2;

	if(pclLayer[layer] == NULL)return FALSE;
	
	startx=centerx-MAP_TILE_XSIZE_HALF;
	starty=centery-MAP_TILE_YSIZE_HALF;
	
	ref = pclLayer[layer]->GetDrawInfo_Ref(x, y) ;
	file = pclLayer[layer]->GetDrawInfo_File(x, y);
	font = pclLayer[layer]->GetDrawInfo_Font(x, y);

	if(ref < 0 || ref >= MAX_TILESET_NUMBER)return FALSE;
	if(pclTileManager->pclTileInfo[ref] == NULL)return FALSE;

	TSpr* pspr = pclTileManager->pclTileInfo[ref]->pSpr[file];
	if(pspr)
	{
		GP.FitToClipArea(startx, starty, startx+(pspr->GetXSize())-1, starty+(pspr->GetYSize())-1, 
			sx1, sy1, sx2, sy2);
	}

	DrawTile(ref, file, font, x, y, startx, starty);

	return TRUE;

}


void cltMapClient::DrawTile(SI32 ref, SI32 file, SI32 font, SI32 x, SI32 y, SI32 startx, SI32 starty)
{
	
	TSpr* pspr = pclTileManager->pclTileInfo[ref]->pSpr[file];

	if(pspr)
	{
		if(GP.IsInClipArea(startx, starty, startx + pspr->GetXSize() -1, starty + pspr->GetYSize() -1) == TRUE)
		{
			
			if( pclClient->GameMode == GAMEMODE_MAPEDIT )
				GP.PutMpr(pspr,  startx, starty, PUT_SPR_SPR, TRUE, font );
			else
				GP.PutMpr(pspr,  startx, starty, PUT_SPR_SPR, FALSE, font );
		}
		else
		{
			// LeeKH - �� ����Ʈ ��常 �ϴ� ����� ����. - Ŭ���� ��ο���
			if( pclClient->GameMode == GAMEMODE_MAPEDIT )
				GP.PutMpr(pspr,  startx, starty, PUT_SPR_SPR, TRUE, font );
		}
	}
}


// �������� ��ũ��. 
void cltMapClient::Scroll_North(cltClient* pclclient)
{
	SI32 i, j;
	SI32 centerx, centery;


	SI32 xsize = pclclient->siClientScreenXsize;
	SI32 ysize = pclclient->siClientScreenYsize;


	SI32 linesize = xsize * 2;

	// �ߺ��Ǵ� ������ �����Ѵ�. 
	for(i = (ysize - MAP_TILE_YSIZE) - 1;i >= 0;i--)
	{
		memcpy(GP.GetSurfacePtr(0, i+MAP_TILE_YSIZE), GP.GetSurfacePtr(0, i), linesize);
	}

	// ���� �巯�� ������ �����. 
	for(i = 0;i < MAP_TILE_YSIZE;i++)
	{
		memset(GP.GetSurfacePtr(0, i), 0, linesize);
	}


   for(i = VirtualMapY - pclclient->siClientScreenHalfSize;i < VirtualMapY + pclclient->siClientScreenHalfSize;i++)
	   for(j = VirtualMapX - pclclient->siClientScreenHalfSize;j < VirtualMapX + pclclient->siClientScreenHalfSize;j++)
	   {
		   // ���������� ����.
		   if(IsInMapArea(j, i) == false)continue;
		   
		   // ����ؾ� �� �߽� ��ġ�� ���Ѵ�. 
		   GetDrawCenterXY(j, i, &centerx, &centery);

		   if((centery) > MAP_TILE_YSIZE )
		   {
			   continue;	// ���� ���� �� �κи� ��´�. 
		   }
		   
		   if(pclLayer[1]->GetDrawInfo_Unique(j, i) != 90)
		   {
			   DrawLayer(centerx, centery, 1, j, i);
		   }
		   else
		   {
			   DrawLayer(centerx, centery, 0, j, i);
		   }
	   }
}


// �������� ��ũ��. 
void cltMapClient::Scroll_South(cltClient* pclclient)
{
	SI32 i, j;
	SI32 centerx, centery;


	SI32 xsize = pclclient->siClientScreenXsize;
	SI32 ysize = pclclient->siClientScreenYsize;


	SI32 linesize = xsize * 2;

	// �ߺ��Ǵ� ������ �����Ѵ�. 
	for(i = MAP_TILE_YSIZE;i < ysize;i++)
	{
		memcpy(GP.GetSurfacePtr(0, i - MAP_TILE_YSIZE), GP.GetSurfacePtr(0, i), linesize);
	}

	// ���� �巯�� ������ �����. 
	for(i = ysize - MAP_TILE_YSIZE;i < ysize;i++)
	{
		memset(GP.GetSurfacePtr(0, i), 0, linesize);
	}



   for(i = VirtualMapY - pclclient->siClientScreenHalfSize;i < VirtualMapY + pclclient->siClientScreenHalfSize;i++)
	   for(j = VirtualMapX - pclclient->siClientScreenHalfSize;j < VirtualMapX + pclclient->siClientScreenHalfSize;j++)
	   {
		   // ���������� ����.
		   if(IsInMapArea(j, i) == false)continue;
		   
		   // ����ؾ� �� �߽� ��ġ�� ���Ѵ�. 
		   GetDrawCenterXY(j, i, &centerx, &centery);

		   if(centery < ysize - MAP_TILE_YSIZE )
		   {
			   continue;	// ���� ���� �� �κи� ��´�. 
		   }
		   
		   if(pclLayer[1]->GetDrawInfo_Unique(j, i) != 90)
		   {
			   DrawLayer(centerx, centery, 1, j, i);
		   }
		   else
		   {
			   DrawLayer(centerx, centery, 0, j, i);
		   }
	   }

}


// �������� ��ũ��. 
void cltMapClient::Scroll_East(cltClient* pclclient)
{
	SI32 i, j;
	SI32 centerx, centery;


	SI32 xsize = pclclient->siClientScreenXsize;
	SI32 ysize = pclclient->siClientScreenYsize;


	SI32 linesize	= (xsize - MAP_TILE_XSIZE) * 2;
	SI32 delsize	= MAP_TILE_XSIZE *2;


	// �ߺ��Ǵ� ������ �����Ѵ�. 
	for(i = 0;i < ysize;i++)
	{
		memmove(GP.GetSurfacePtr(0, i), GP.GetSurfacePtr(MAP_TILE_XSIZE, i), linesize);
	}

	// ���� �巯�� ������ �����. 
	for(i = 0;i < ysize;i++)
	{
		memset(GP.GetSurfacePtr(xsize - MAP_TILE_XSIZE, i), 0, delsize);
	}




   for(i = VirtualMapY - pclclient->siClientScreenHalfSize;i < VirtualMapY + pclclient->siClientScreenHalfSize;i++)
	   for(j = VirtualMapX - pclclient->siClientScreenHalfSize;j < VirtualMapX + pclclient->siClientScreenHalfSize;j++)
	   {
		   // ���������� ����.
		   if(IsInMapArea(j, i) == false)continue;
		   
		   // ����ؾ� �� �߽� ��ġ�� ���Ѵ�. 
		   GetDrawCenterXY(j, i, &centerx, &centery);

		   if(centerx < xsize - MAP_TILE_XSIZE )
		   {
			   continue;	// ���� ���� �� �κи� ��´�. 
		   }
		   
		   if(pclLayer[1]->GetDrawInfo_Unique(j, i) != 90)
		   {
			   DrawLayer(centerx, centery, 1, j, i);
		   }
		   else
		   {
			   DrawLayer(centerx, centery, 0, j, i);
		   }
	   }

}

// �������� ��ũ��. 
void cltMapClient::Scroll_West(cltClient* pclclient)
{
	SI32 i, j;
	SI32 centerx, centery;


	SI32 xsize = pclclient->siClientScreenXsize;
	SI32 ysize = pclclient->siClientScreenYsize;


	SI32 linesize	= (xsize - MAP_TILE_XSIZE) * 2;
	SI32 delsize	= MAP_TILE_XSIZE *2;

	// �ߺ��Ǵ� ������ �����Ѵ�. 
	for(i = 0;i < ysize;i++)
	{
		memmove(GP.GetSurfacePtr(MAP_TILE_XSIZE, i), GP.GetSurfacePtr(0, i), linesize);
	}

	// ���� �巯�� ������ �����. 
	for(i = 0;i < ysize;i++)
	{
		memset(GP.GetSurfacePtr(0, i), 0, delsize);
	}




   for(i = VirtualMapY - pclclient->siClientScreenHalfSize;i < VirtualMapY + pclclient->siClientScreenHalfSize;i++)
	   for(j = VirtualMapX - pclclient->siClientScreenHalfSize;j < VirtualMapX + pclclient->siClientScreenHalfSize;j++)
	   {
		   // ���������� ����.
		   if(IsInMapArea(j, i) == false)continue;
		   
		   // ����ؾ� �� �߽� ��ġ�� ���Ѵ�. 
		   GetDrawCenterXY(j, i, &centerx, &centery);

		   if(centerx > MAP_TILE_XSIZE )
		   {
			   continue;	// ���� ���� �� �κи� ��´�. 
		   }
		   
		   if(pclLayer[1]->GetDrawInfo_Unique(j, i) != 90)
		   {
			   DrawLayer(centerx, centery, 1, j, i);
		   }
		   else
		   {
			   DrawLayer(centerx, centery, 0, j, i);
		   }
	   }

}

// �ϵ������� ��ũ��. 
void cltMapClient::Scroll_NorthEast(cltClient* pclclient)
{
	SI32 i, j;
	SI32 centerx, centery;


	SI32 xsize = pclclient->siClientScreenXsize;
	SI32 ysize = pclclient->siClientScreenYsize;


	SI32 linesize	= (xsize - MAP_TILE_XSIZE_HALF) * 2;
	SI32 delsize	= MAP_TILE_XSIZE_HALF *2;


	// �ߺ��Ǵ� ������ �����Ѵ�. 
	for(i = (ysize - MAP_TILE_YSIZE_HALF) - 1;i >= 0;i--)
	{
		memmove(GP.GetSurfacePtr(0, i+MAP_TILE_YSIZE_HALF), GP.GetSurfacePtr(MAP_TILE_XSIZE_HALF, i), linesize);
	}

	// ���� �巯�� ������ �����. 
	for(i = 0;i < MAP_TILE_YSIZE_HALF;i++)
	{
		memset(GP.GetSurfacePtr(0, i), 0, linesize + delsize);
	}
	for(i = 0;i < ysize;i++)
	{
		memset(GP.GetSurfacePtr(xsize - MAP_TILE_XSIZE_HALF, i), 0, delsize);
	}


   for(i = VirtualMapY - pclclient->siClientScreenHalfSize;i < VirtualMapY + pclclient->siClientScreenHalfSize;i++)
	   for(j = VirtualMapX - pclclient->siClientScreenHalfSize;j < VirtualMapX + pclclient->siClientScreenHalfSize;j++)
	   {
		   // ���������� ����.
		   if(IsInMapArea(j, i) == false)continue;
		   
		   // ����ؾ� �� �߽� ��ġ�� ���Ѵ�. 
		   GetDrawCenterXY(j, i, &centerx, &centery);

		   if((centery) > MAP_TILE_YSIZE_HALF && centerx < (xsize - MAP_TILE_XSIZE_HALF) )
		   {
			   continue;
		   }

		   
		   if(pclLayer[1]->GetDrawInfo_Unique(j, i) != 90)
		   {
			   DrawLayer(centerx, centery, 1, j, i);
		   }
		   else
		   {
			   DrawLayer(centerx, centery, 0, j, i);
		   }
	   }

}

// �ϼ������� ��ũ��. 
void cltMapClient::Scroll_NorthWest(cltClient* pclclient)
{
	SI32 i, j;
	SI32 centerx, centery;


	SI32 xsize = pclclient->siClientScreenXsize;
	SI32 ysize = pclclient->siClientScreenYsize;


	SI32 linesize	= (xsize - MAP_TILE_XSIZE_HALF) * 2;
	SI32 delsize	= MAP_TILE_XSIZE_HALF *2;


	// �ߺ��Ǵ� ������ �����Ѵ�. 
	for(i = (ysize - MAP_TILE_YSIZE_HALF) - 1;i >= 0;i--)
	{
		memmove(GP.GetSurfacePtr(MAP_TILE_XSIZE_HALF, i+MAP_TILE_YSIZE_HALF), GP.GetSurfacePtr(0, i), linesize);
	}

	// ���� �巯�� ������ �����. 
	for(i = 0;i < MAP_TILE_YSIZE_HALF;i++)
	{
		memset(GP.GetSurfacePtr(0, i), 0, linesize + delsize);
	}
	for(i = 0;i < ysize;i++)
	{
		memset(GP.GetSurfacePtr(0, i), 0, delsize);
	}


   for(i = VirtualMapY - pclclient->siClientScreenHalfSize;i < VirtualMapY + pclclient->siClientScreenHalfSize;i++)
	   for(j = VirtualMapX - pclclient->siClientScreenHalfSize;j < VirtualMapX + pclclient->siClientScreenHalfSize;j++)
	   {
		   // ���������� ����.
		   if(IsInMapArea(j, i) == false)continue;
		   
		   // ����ؾ� �� �߽� ��ġ�� ���Ѵ�. 
		   GetDrawCenterXY(j, i, &centerx, &centery);

		   if((centery) > MAP_TILE_YSIZE_HALF && centerx > MAP_TILE_XSIZE_HALF )
		   {
			   continue;
		   }

		   
		   if(pclLayer[1]->GetDrawInfo_Unique(j, i) != 90)
		   {
			   DrawLayer(centerx, centery, 1, j, i);
		   }
		   else
		   {
			   DrawLayer(centerx, centery, 0, j, i);
		   }
	   }

}


// ���������� ��ũ��. 
void cltMapClient::Scroll_SouthWest(cltClient* pclclient)
{
	SI32 i, j;
	SI32 centerx, centery;


	SI32 xsize = pclclient->siClientScreenXsize;
	SI32 ysize = pclclient->siClientScreenYsize;


	SI32 linesize	= (xsize - MAP_TILE_XSIZE_HALF) * 2;
	SI32 delsize	= MAP_TILE_XSIZE_HALF *2;

	// �ߺ��Ǵ� ������ �����Ѵ�. 
	for(i = MAP_TILE_YSIZE_HALF;i < ysize;i++)
	{
		memmove(GP.GetSurfacePtr(MAP_TILE_XSIZE_HALF, i - MAP_TILE_YSIZE_HALF), GP.GetSurfacePtr(0, i), linesize);
	}


	// ���� �巯�� ������ �����. 
	for(i = ysize - MAP_TILE_YSIZE_HALF;i < ysize;i++)
	{
		memset(GP.GetSurfacePtr(0, i), 0, linesize + delsize);
	}

	for(i = 0;i < ysize;i++)
	{
		memset(GP.GetSurfacePtr(0, i), 0, delsize);
	}


   for(i = VirtualMapY - pclclient->siClientScreenHalfSize;i < VirtualMapY + pclclient->siClientScreenHalfSize;i++)
	   for(j = VirtualMapX - pclclient->siClientScreenHalfSize;j < VirtualMapX + pclclient->siClientScreenHalfSize;j++)
	   {
		   // ���������� ����.
		   if(IsInMapArea(j, i) == false)continue;
		   
		   // ����ؾ� �� �߽� ��ġ�� ���Ѵ�. 
		   GetDrawCenterXY(j, i, &centerx, &centery);

		   if(centery < ysize - MAP_TILE_YSIZE_HALF && centerx > MAP_TILE_XSIZE_HALF )
		   {
			   continue;
		   }

		   
		   if(pclLayer[1]->GetDrawInfo_Unique(j, i) != 90)
		   {
			   DrawLayer(centerx, centery, 1, j, i);
		   }
		   else
		   {
			   DrawLayer(centerx, centery, 0, j, i);
		   }
	   }

}


// ���������� ��ũ��. 
void cltMapClient::Scroll_SouthEast(cltClient* pclclient)
{
	SI32 i, j;
	SI32 centerx, centery;


	SI32 xsize = pclclient->siClientScreenXsize;
	SI32 ysize = pclclient->siClientScreenYsize;


	SI32 linesize	= (xsize - MAP_TILE_XSIZE_HALF) * 2;
	SI32 delsize	= MAP_TILE_XSIZE_HALF *2;

	// �ߺ��Ǵ� ������ �����Ѵ�. 
	for(i = MAP_TILE_YSIZE_HALF;i < ysize;i++)
	{
		memmove(GP.GetSurfacePtr(0, i - MAP_TILE_YSIZE_HALF), GP.GetSurfacePtr(MAP_TILE_XSIZE_HALF, i), linesize);
	}


	// ���� �巯�� ������ �����. 
	for(i = ysize - MAP_TILE_YSIZE_HALF;i < ysize;i++)
	{
		memset(GP.GetSurfacePtr(0, i), 0, linesize + delsize);
	}

	for(i = 0;i < ysize;i++)
	{
		memset(GP.GetSurfacePtr(xsize - MAP_TILE_XSIZE_HALF, i), 0, delsize);
	}


   for(i = VirtualMapY - pclclient->siClientScreenHalfSize;i < VirtualMapY + pclclient->siClientScreenHalfSize;i++)
	   for(j = VirtualMapX - pclclient->siClientScreenHalfSize;j < VirtualMapX + pclclient->siClientScreenHalfSize;j++)
	   {
		   // ���������� ����.
		   if(IsInMapArea(j, i) == false)continue;
		   
		   // ����ؾ� �� �߽� ��ġ�� ���Ѵ�. 
		   GetDrawCenterXY(j, i, &centerx, &centery);

		   if(centery < ysize - MAP_TILE_YSIZE_HALF && centerx < xsize - MAP_TILE_XSIZE_HALF )
		   {
			   continue;
		   }

		   
		   if(pclLayer[1]->GetDrawInfo_Unique(j, i) != 90)
		   {
			   DrawLayer(centerx, centery, 1, j, i);
		   }
		   else
		   {
			   DrawLayer(centerx, centery, 0, j, i);
		   }
	   }
}

void cltMapClient::PopEffect()
{
	for ( SI32 i = 0 ; i < CurrentEffect ; i ++ )
	{
		if ( pclEffectMap[i].gimg <= 0 || pclEffectMap[i].gimg > MAX_GLOBAL_IMG_FILE_NUMBER ) continue;

		TSpr* pspr	= pclClient->GetGlobalSpr(pclEffectMap[i].gimg);
		if ( pspr )
		{
			GP.PutSprScreen(pspr, pclEffectMap[i].x , pclEffectMap[i].y, pclEffectMap[i].font,pclEffectMap[i].reverse);
		}
		pclEffectMap[i].Init();
	}

	CurrentEffect = 0 ;
}

void cltMapClient::PushEffect(cltEffectMapInfo * pclinfo)
{
	if ( pclinfo == NULL ) return ;

	pclEffectMap[CurrentEffect].Set(pclinfo);
	CurrentEffect ++ ;
}



