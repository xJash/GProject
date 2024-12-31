//---------------------------------
// 2003/5/17 ���°�
//---------------------------------

#include "..\Common\CommonHeader.h"
#include "..\Client\Client.h"

#include <Graphic.h>
#include <Graphic_Capsule.h>

#include <Mouse.h>

#include "SmallMap.h"

#include "..\..\Resource.h"

extern cltCommonLogic* pclClient;


// �ؽ�Ʈ�� ����Ѵ�. 
void cltSmallMap::DrawText(HDC hdc, SI32 dotx, SI32 doty, char* text, COLORREF rgb)
{
	SIZE size;
	GetTextExtentPoint32(hdc, text, strlen(text), &size);
	
	SI32 x = dotx - DrawStartPosX - size.cx/2;
	SI32 y = doty - DrawStartPosY - size.cy;
	
	SetTextColor( hdc, RGB(0, 0, 0));
	TextOut(hdc, x+1, y+1, text, lstrlen(text));
	
	SetTextColor( hdc, rgb);
	TextOut(hdc, x, y, text, lstrlen(text));
}

// ��ũ�� ����Ѵ�. 
void cltSmallMap::DrawMark(SI32 dotx, SI32 doty)
{
	GP.FillBox(	dotx - 1 - DrawStartPosX, doty - 1 - DrawStartPosY, 
					dotx + 1 - DrawStartPosX, doty + 1 - DrawStartPosY, 
					SMAP_INFO_COLOR,FALSE);
}


// ���� �������� ������ ǥ���Ѵ�.
void cltSmallMap::DrawSMapInfo(SI32 x, SI32 y, char* text, COLORREF rgb)
{
	SI32 dotx, doty;
	if(GetSmallMapCordFromTileXY(x, y, &dotx, &doty) == TRUE)
	{
		// ���̴� ���� �ȿ� ���� ���� ����Ѵ�. 
		if(GP.IsInClipArea(	dotx-1 - DrawStartPosX, doty-1 - DrawStartPosY, 
			dotx+1 - DrawStartPosX, doty+1 - DrawStartPosY) == TRUE)
		{
			
			if(GP.LockSurface(pSmallMapWorkSurface2) == TRUE)
			{
				DrawMark(dotx, doty);
				
				GP.UnlockSurface(pSmallMapWorkSurface2);
			}
			
			HDC hdc;
			if(pSmallMapWorkSurface2->GetDC(&hdc) == DD_OK)
			{
				// ��Ʈ�� �����Ѵ�. 
				HFONT hFont = g_FontManager.SetFont();
				HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
				
				SetBkMode(hdc, TRANSPARENT);
				
				DrawText(hdc, dotx, doty, text, rgb);

				SelectObject( hdc, hOldFont );
				
				pSmallMapWorkSurface2->ReleaseDC(hdc);
			}
		}
	}
				
}