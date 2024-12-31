//---------------------------------
// 2003/5/17 ���°�
//---------------------------------

#ifndef _MAPEDIT_H
#define _MAPEDIT_H

#include "..\Client\Client.h"

#define MAPEDIT_MODE_TERRAIN            0
#define MAPEDIT_MODE_FIELDOBJET         1
#define MAPEDIT_MODE_FIELDOBJETBRUSH    2
#define MAPEDIT_MODE_GEOINFO			3
#define MAPEDIT_MODE_CUSTOMCOLL			4

#define FOSURFACE_XSIZE					800
#define FOSURFACE_YSIZE					600

#define FIELDOBJECT_COLL_MAP_XSIZE		16
#define FIELDOBJECT_COLL_MAP_YSIZE		16

#define MAX_COLLISION_BRUSH_NUM			10

#include "..\Common\Map\Map.h"


class cltFieldObjectTypeInfo;

class cltMapEdit : public cltClient {
public:

	SI32 CurrentMode ;							
	SI32 CurrentTerrainUnique;				// ���� ���õ� Terrain Unique
	SI32 CurrentFieldObjectUnique;			// ���� ���õ� Field Object Unique
	SI32 CurrentFieldObjectBrush;			// ���� ���õ� Field Object Brush
	SI32 SelectedGeoInfoSlot;				// ���õ� ���� ���� 

	SI32 CurrentCustomCollision;			// ���� ���õ� �����浹 ���� 
	SI32 SelectedFieldObjectUnique;			// ���� ���õ� Field Object Unique

	UI08 uiCollisionBrush;					// �浹 ���� ������ ����ϴ� �귯�� ũ�� uiCollisionBrush x uiCollisionBrush

	OPENFILENAME MapFileOpen;				// ���� ȭ�Ͽ� 

	TCHAR MapFileName[256];
	TCHAR MapFileShortName[128];

	SHORT PutSeaMode;
	SHORT PutWaterMode;

	HWND					hMapEditDlg;
	HWND					hGeoInfoDlg;
	HWND					hDeleteUniqueDlg;

	//------------------------------------
	// ��� ���庯�� 
	//------------------------------------
	TCHAR					CurrentDirectory[MAX_PATH];

	//-------------------------------------
	// FieldObject ǥ�ÿ� Surface
	//--------------------------------------
	LPDIRECTDRAWSURFACE7 pFOSurface;
	LPDIRECTDRAWSURFACE7 pFOSurface2;

	SI32 FieldObjectCollMap[FIELDOBJECT_COLL_MAP_XSIZE][FIELDOBJECT_COLL_MAP_YSIZE];

	TSpr FloorSpr;
	TSpr m_pNewMapPCXSpr;

	SI32 FoTileSize;


	cltMapEdit( TCHAR* appname, HWND hwnd , HINSTANCE hinst, SI32 gamemode, SI32 defaultservicearea, SI32 runmode );
	~cltMapEdit();
	
	void WinSockAction(){};
	
	void MapEditAction();

	void Create();

	//-----------------------------------------
	// ��� ���� 
	//-----------------------------------------

	void PopMapFileInitializeMap(HWND hwnd);
	void PopMapFileInitializeSpr(HWND hwnd);
	BOOL PopMapFileOpenDlg(HWND hwnd, TCHAR* pstrFileName, TCHAR* pstrTitleName);
	BOOL PopMapFileSaveDlg(HWND hwnd, TCHAR* pstrFileName, TCHAR* pstrTitleName);


	//-------------------------------------------
	//	Ʈ�� ���� ���� 
	//-------------------------------------------
	void InsertTree_Terrain(HWND hDlg, HTREEITEM pNode, cltTileInfo* pclParentTileInfo);
	void InsertTree_FieldObject(HWND hDlg, HTREEITEM pNode, cltFieldObjectTypeInfo* pclParentInfo);

	// Ʈ��������  �߰��Ѵ�.
	HTREEITEM TreeViewInsert(HWND hwnd, TCHAR* name, SI32 para, HTREEITEM node);


	//-----------------------------------------
	// ����Ʈ �ڽ� 
	//-----------------------------------------
	void InsertFieldObjectBrush(HWND hDlg);


	//-------------------------------------------
	// �� ������ ���� �������̽� ���� ���� 
	//-------------------------------------------
	void CreateNewMapTool();
	static BOOL CALLBACK StaticNewMapDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
	BOOL CALLBACK NewMapDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);

	//------------------------------------------
	// ���� �ȳ� ���� �� 
	//------------------------------------------
	void CreateGeoInfoTool();
	static BOOL CALLBACK StaticGeoInfoDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
	BOOL CALLBACK GeoInfoDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
	// ���� ���� ����Ʈ �ڽ��� ���� �����Ѵ�. 
	void SetGeoInfoListBox(HWND hDlg);

	//------------------------------------------
	// �ش� ����ũ ���� ��
	//------------------------------------------
	void DeleteUniqueTool();
	static BOOL CALLBACK StaticDeleteUniqueDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
	BOOL CALLBACK DeleteUniqueDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);




	//------------------------------------------
	// Terrain Select Tool
	//------------------------------------------
	void OpenMapEditTerrainTool();
	static BOOL CALLBACK StaticSelectTerrainDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
	BOOL CALLBACK SelectTerrainDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
	
	// FOShape�� �����ϱ� ���� ��Ʈ���� �����Ѵ�. 
	void InitFOShape(HWND hDlg);

	// Field Object ǥ�ñ��� ������ �����Ѵ�. 
	void SetFOShape(HWND hDlg, SI32 founique);

	// Field Object�� FOSurface�� �Űܱ׸���. 
	void DrawFOShape(HWND hDlg, SI32 founique);

	//Field Object ������ �����Ѵ�.
	bool SaveFieldObjectInfo(SI32 founique);

	void DrawFloorTile(SI32 startx, SI32 starty, SI32 xsize, SI32 ysize, UI08 color);


	void OpenMapEditSaveTool();
	void OpenMapEditLoadTool();


	//----------------------------------
	// MapEdit-HeaderManager.cpp
	//----------------------------------
	// �� ��� ������ ��ȭ ��ȭ�� �����ش�.
	BOOL OpenMapEditHeaderManager();
	static BOOL CALLBACK StaticHeaderManagerDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
	BOOL CALLBACK HeaderManagerDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);


	//----------------------------------
	// MapEdit-CustomCollision.cpp
	//----------------------------------
	// ���� �浹üũ ������ȭ���� 
	BOOL OpenCustomCollision();
	static BOOL CALLBACK StaticCustomCollisionDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
	BOOL CALLBACK CustomCollisionDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);

	//-----------------------------------
	// ��ٸ��� ��ȭ ���� ó�� ���� 
	//-----------------------------------
	BOOL ModalessDlgProc(MSG* pmsg);

	//-----------------------------------
	// WM_COMMAND�޽��� ó�� �Լ�. 
	//-----------------------------------
	bool DoMsg_WM_COMMAND(WPARAM wParam);

	
};

#endif