//---------------------------------
// 2003/5/17 ���°�
//---------------------------------

#ifndef _SMALLMAP_H
#define _SMALLMAP_H

#include "..\..\Common\Map\Map.h"

#define SMALLMAPMODE_MAPEDIT		1
#define SMALLMAPMODE_GAME			2


#define SMAP_INFOMODE_VILLAGE		0
#define SMAP_INFO_COLOR				40

class cltSmallMap{

public:
	HWND m_hDlg;								// ��ü ��� ���� ���̾�α� �ڽ��� HWND

	cltMapClient* pclMap;
	SI32 SmallMapMode;

	SI32 CurrentInfoMode;
	LPDIRECTDRAWSURFACE7  pSmallMapSurface;		 // ��������� ������ ��� ����.
	LPDIRECTDRAWSURFACE7  pSmallMapWorkSurface;  // ��������� ������ ����(��ҵ�.)�� ��� ����. 
	LPDIRECTDRAWSURFACE7  pSmallMapWorkSurface2; // ȭ������ �Ű��� ���� �̹����� ��� �� ����. 

	SI32 MapXsize, MapYsize;					// ������ ���� ���� Ÿ�� ũ��. 

	SI32 SmallMapXsize, SmallMapYsize;			// ��� ���� ������ ���� ���� ũ��. 
	SI32 CurrentMapXsize, CurrentMapYsize;		// ���� ��� ���������� ���� ���� ���� ũ�� 


	SI32 ParentMapX, ParentMapY;				// �̺����� ������ ���� �ٰŷ� ���� ������ �����̰� �ȴ�. 

	SI32 DrawStartPosX, DrawStartPosY;			// ȭ�鿡 ������ִ� ������ġ. 
	RECT DrawAreaRect;

	SI32 StandardX, StandardY;					// ��������� ǥ���ϴ� ������ �Ǵ� ����.
	SI32 OldStandardX,OldStandardY;
	
	SI32 UserPosX, UserPosY;					// ������� Ÿ�� ��ǥ ��ġ. 

	SI32 MouseX, MouseY;
	SI32 DragStartX, DragStartY;

	BOOL LeftPressSwitch;
	BOOL LeftPressDragSwitch;

	BOOL ConnectToMapSwitch;					// ������ ��������� ������Ű�°� ?(�̵��� ���� ������. ) 
	
	SI32 SmallMapRate;							// ��� ���� (5~10, 10�̸� ������ ���� �������. ) 
	SI32 siOrgSmallMapRate;						// ���� ������ ������� ����. 

	char SmallMapFileName[MAX_PATH];

	cltSmallMap(SI32 smallmapmode, char* SmallMapFileName,  cltMapClient* pclmap);
	~cltSmallMap();

	
	BOOL CALLBACK SMapDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);

	BOOL DrawSmallMap(HWND hDlg);

	BOOL IncreaseDrawStartX(SI32 inc);
	BOOL IncreaseDrawStartY(SI32 inc);

	// ������� �󿡼� x, y��Ʈ�� �ش��ϴ� Ÿ�� ��ǥ�� �����ش�. 
	BOOL GetSmallMapTileXYFromCord(SI32 dotx, SI32 doty, SI32* ptilex, SI32* ptiley);

	// ������� �󿡼� Ÿ�� x, y ��ǥ�� �ش��ϴ� ��ǥ�� �����ش�. 
	BOOL GetSmallMapCordFromTileXY(SI32 tilex, SI32 tiley, SI32* pdotx, SI32* pdoty);

	BOOL SetScrollPara(HWND hDlg);

	// �������� ������ ����Ѵ�. 
	void CalcMapConnection(HWND hDlg);

	// ���� ���� ������ �°� ����ؼ� �۾��� ���ǽ��� �Ű� �׸���. 
	void ReadyRateMap();

	void UpdateSmallMap();
	void UpdateSmallMap(SI32 x, SI32 y);

	void SetUserPos(SI32 x, SI32 y)
	{
		UserPosX = x;
		UserPosY = y;
	}

	// �ؽ�Ʈ�� ����Ѵ�. 
	void DrawText(HDC hdc, SI32 dotx, SI32 doty, char* text, COLORREF rgb);

	// ��ũ�� ����Ѵ�. 
	void DrawMark(SI32 dotx, SI32 doty);


	// ���� �������� ������ ǥ���Ѵ�.
	void DrawSMapInfo(SI32 x, SI32 y, char* text, COLORREF rgb  = RGB(250, 250, 250) );

	DWORD		m_lastTickCount;

};

#endif