#ifndef _NMINIMAPDLG_H_
#define _NMINIMAPDLG_H_


#include "../../InterfaceMgr/DialogController.h"

#include <CommonHeader.h>

class CImageStatic;
class CButton;
class cltMapClient;


#define MAX_MINIMAP_NPC	10

struct stMinimapNPC
{
    SI32 siKind;
	cltCharPos clPosMinimap;
	
	stMinimapNPC()
	{
		Init();
	}

	stMinimapNPC( SI32 Kind, cltCharPos* Pos )
	{
		Init();
        siKind = Kind;
		clPosMinimap.Set(Pos);
	}

	void Init()
	{
		memset( this, 0, sizeof( stMinimapNPC ) );
	}
	

	BOOL IsSameData( stMinimapNPC * pData )
	{
		BYTE* Org = (BYTE*)this;
        BYTE* Param = (BYTE*)pData;
		SI32 siMySize = sizeof(stMinimapNPC);

        for( SI32 i = 0; i < siMySize ; i++ )
		{
			if( Org[i] != Param[i] )
			{
				return FALSE;
			}
		}

		return TRUE;
	}
};

#define MAX_MONSTERHOME_NUMBER	10

struct stMonsterHome
{
	SI32	siXpos;
	SI32	siYpos;
	TCHAR	szHomeName[128];

	stMonsterHome()
	{
		Init();
	}

	stMonsterHome( SI32 x, SI32 y, TCHAR* Name )
	{
		siXpos = x;
		siYpos = y;
		StringCchCopy( szHomeName, 128, Name );
	}

	void Init()
	{
		ZeroMemory( this , sizeof( stMonsterHome ) );
	}

	void Set( SI32 x, SI32 y, TCHAR* Name )
	{
		siXpos = x;
		siYpos = y;
		StringCchCopy( szHomeName, 128, Name );
	}

	bool IsValid()
	{
		if( siXpos < 0)		return false;
		if( siYpos < 0)		return false;
		if( _tcslen(szHomeName) <= 0 )		return false;

		return true;
	}
};

class CNMiniMapDlg : public CDialogController
{
public:
	CNMiniMapDlg();
	~CNMiniMapDlg();

	void Create();
	
	void Show();
	void Hide();

    void Minimi(BOOL bMini);
	BOOL GetMinimi(){return m_bMini; };
	void EnLarge();
	void Reduce();

	static void CALLBACK StaticCallBackDialogNMiniMap( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
	void CALLBACK CallBackDialogNMiniMap( UINT nEvent, int nControlID, CControllerObj* pControl );

	void Set( TCHAR *SmallMapFileName, cltMapClient *pclmap, SI32 MapIndex );
	void ReadyRateMap( cltMapClient *pMap );

	void VDirectDrawToBackScreen( LPDIRECTDRAWSURFACE7 lpBackScreen, SI32 ScreenRX, SI32 ScreenRY );
	void DrawExplain( HDC hdc, SI32 DrawXPos, SI32 DrawYPos, SI32 dotx, SI32 doty, TCHAR* text, COLORREF rgb);
	void DrawMark( SI32 DrawXPos, SI32 DrawYPos, SI32 dotx, SI32 doty );
	void DrawSMapInfo( LPDIRECTDRAWSURFACE7 lpBackScreen, SI32 DrawXPos, SI32 DrawYPos, SI32 x, SI32 y, TCHAR* text, COLORREF rgb = RGB(250, 250, 250) );
	void DrawSMapStructureInfo( LPDIRECTDRAWSURFACE7 lpBackScreen, SI32 DrawXPos, SI32 DrawYPos, SI32 x, SI32 y, SI32 siStructureUnique );	
	void DrawSMapNPCInfo( LPDIRECTDRAWSURFACE7 lpBackScreen, SI32 DrawXPos, SI32 DrawYPos, SI32 x, SI32 y, SI32 siKind );
	void ChangeStandardPos( SI32 XPos, SI32 YPos )
	{
		m_siStandardPosX = XPos;
		m_siStandardPosY = YPos;
	}
	

	bool GetSmallMapCordFromTileXY( SI32 tilex, SI32 tiley, SI32* pdotx, SI32* pdoty );
	void RefreshPos();

	void SetPosition(TCHAR* szPosition);
	
	// ĳ���͸� �׷��ָ� �̴ϸʿ��� npc ������ �������ش�.

	// ĳ���͸� �׸��� �� �̴ϸ��� npc ������ �ʱ�ȭ
	void ClearMinimapNPC();		// [����] ����Ʈ NPC�� �̴ϸʿ� �����ֱ� ���� �޼ҵ��
	// ĳ���͸� �׷��ָ� �̴ϸ��� npc ������ ����
	void SetMinimapNPC( SI32 Kind, cltCharPos* Pos  );	
	
	void Action();

	// ���� ������ ����
	void SetMonsterHome();
	// �������� �̵� 
	void GoRaccoonWorld()	;

	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );

private:
	CImageStatic			*m_pImageStatic;
//	CButton*				m_pButton[4]; // 0:��� 1:Ȯ�� 2: �ݱ� 3:Ȱ��
	TSpr					m_MiniPlayerSpr;
	TSpr					m_MiniStructureSpr;
	TSpr					m_MiniNPCSpr;
	TSpr					m_ButtonSpr;

	SI16					m_siMiniMapWidth;			// Image Static ������� ����
	SI16					m_siMiniMapHeight;

	SI32					m_siCurrentMapWidth;		// Ȯ�� ��ҿ� ���� �� ������ ������ ��.
	SI32					m_siCurrentMapHeight;

	SI16					m_siStandardPosX;			// ���� ��ǥ
	SI16					m_siStandardPosY;

	SI32					m_siDrawStartXPos;
	SI32					m_siDrawStartYPos;

	TCHAR					m_strSmallMapFileName[ FILE_NAME_SIZE ];

	LPDIRECTDRAWSURFACE7	m_lpSmallMapSurface;
	LPDIRECTDRAWSURFACE7	m_lpSmallMapWorkSurface;

	bool					m_bSet;
	bool					m_bFollowMovePos;

	float					m_fScale;

	SI32					m_siSurfaceWidth;
	SI32					m_siSurfaceHeight;

	SI32					m_siRealMapXSize;
	SI32					m_siRealMapYSize;
	 
	CButton*				m_pButtonDetail;
	CButton*				m_pButtonMainmap; // ���θ� ��ư
//	CButton*				m_pButtonGenerally;
	CButton*				m_pButtonMini;
	BOOL					m_bMini;
	BOOL					m_bDraw;
	BOOL					m_bEnlarge;

	CButton*				m_pButtonGoRaccoonWorld;	// ����������� ��ư 

	BYTE colorArray[6];
	POINT point[10];

	//stMinimapNPC			m_OldMinimapNPC[MAX_MINIMAP_NPC]; // ������ ���� �񱳿� ����
	SI32					m_OldMinimapNPCTable;
	SI32					m_MinimapNPCTable;
	stMinimapNPC			m_MinimapNPC[MAX_MINIMAP_NPC];
	
	SI32					m_OldStructureInfo[MAX_CONSTRUCTION_NUM];
	stMonsterHome			m_MonsterHome[MAX_MONSTERHOME_NUMBER];


	POINT m_ClickStartPoint;
	POINT m_DragEndPoint;
	POINT m_MovedPoint;


};


#endif