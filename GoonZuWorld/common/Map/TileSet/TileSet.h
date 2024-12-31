//-----------------------------------------------------------------------------
// 2005/09/27 ������
//-----------------------------------------------------------------------------

#ifndef _TILESET_H
#define _TILESET_H

#include "ndatatypes.h"
#include "TSpr.h"
#include "../../../../NLib/NArray.h"

#define MAX_TILESET_NUMBER			255
#define MAX_CHILD_TILE_SET_NUMBER	20				// ���� �� �ִ� �ִ� �ڽ� Ÿ���� ��. 
#define MAX_TILE_PER_TILESET		100				// �� Ÿ�� ��Ʈ ���� ���� �� �ִ� �ִ��� Ÿ�� �̹������� ��.	
#define MAX_TILE_UNIQUE_NUMBER		1000			// Ÿ�� ����ũ�� �̼� ������ �Ѿ �� ����. 


#define TILEATB_BASE			((DWORD)1)			// �⺻ Ÿ��. �ٸ� Ÿ�ϰ��� ���� ������ ���� �ȿ� ������� �ʴ�. 
#define TILEATB_SUB				((DWORD)1 << 1)		// ���� Ÿ��. �θ� Ÿ�ϰ��� ���� ������ ���� �ȿ� ����ִ�.

#define TILEATB_NODIR			((DWORD)1 << 2)
#define TILEATB_8DIR			((DWORD)1 << 4)

#define TILEATB_LAYER1			((DWORD)1 << 5)		// �ٴڿ� ��� Ÿ�� (��������Ʈ�� �ƴ�) 
#define TILEATB_LAYER2			((DWORD)1 << 6)		// �ٴ� ���� ��� Ÿ�� (��������Ʈ)

#define TILEATB_1X				((DWORD)1 << 7)		// 1��� Ÿ��
#define TILEATB_2X				((DWORD)1 << 8)		// 2��� Ÿ��
#define TILEATB_4X				((DWORD)1 << 9)		// 4��� Ÿ��

#define TILEATB_BLOCK			((DWORD)1 << 10)	// �浹����. 
#define TILEATB_WATER			((DWORD)1 << 11)	// ������. 
#define TILEATB_DEEPWATER		((DWORD)1 << 12)	// ��������. 

//#define TILEATB_XSPR			((DWORD)1 << 13)	// xspr���� ������ Ÿ���ΰ�

// Ÿ�Ͽ� ���� 
#define MAPTILE_SOUTH			((DWORD)1)
#define MAPTILE_WEST			((DWORD)1 << 1)
#define MAPTILE_NORTH			((DWORD)1 << 2)
#define MAPTILE_EAST			((DWORD)1 << 3)

class XSpr;

// Ÿ�ϼ�Ʈ�� ������ ó���ϴ� Ŭ����. 
class cltTileInfo
{
public:
	cltTileInfo(SHORT unique, DWORD dwatb, UI08 color, DWORD dwimagefilenumber, cltTileInfo* pparent, TCHAR* szname);
	~cltTileInfo();

	SI32			FreeAllSpr();								// ������ ��� Ÿ�� ��Ʈ�� �޸� �����Ѵ�
	BOOL			AddChild(cltTileInfo* pparent);				// �ڽ� Ÿ�� ��Ʈ�� �߰��Ѵ�
	BOOL			ReadTileSetArrayInfo(TCHAR* szfilename);		// Ÿ�� �迭 ������ �о�´�


public:
	SHORT			Unique;								// �� Ÿ�� ��Ʈ ������ ���� ��ȣ. 
	DWORD			dwAtb;								// Ÿ�� �Ӽ��� Ư��. 
	TCHAR			szName[MAX_PATH];					// Ÿ�� ��Ʈ�� �̸�. 
	cltTileInfo*	pParent;							// �θ� Ÿ�� ��Ʈ�� ������. (�θ� Ÿ���� �� ���� �ۿ� ����.) 
#ifdef _SAFE_MEMORY
	NSafeTArray<cltTileInfo*, MAX_CHILD_TILE_SET_NUMBER>	pChild;
#else
	cltTileInfo*	pChild[MAX_CHILD_TILE_SET_NUMBER];	// �ڽ� Ÿ�� ��Ʈ�� �����͵�. ( �ڽ� Ÿ���� �������� �� �� �ִ�.) 	
#endif
	DWORD			dwChildNumber;						// �ڽ� Ÿ���� ���� ����. 
	UI08			uiColor;							// �� �����Ϳ��� ���� ��ǥ����. 

	DWORD			TileImageFileNumber ;				// Ÿ�� �̹��� ������ ����. 
#ifdef _SAFE_MEMORY
	NSafeTArray<TSpr*, MAX_TILE_PER_TILESET>		pSpr;
#else
	TSpr*			pSpr[MAX_TILE_PER_TILESET];			// Ÿ�� �̹����� ���� ������. 
#endif
	BYTE*	pTileSetArrayInfo;					// Ÿ���� �迭�Ǿ� �ִ� ��Ģ���� ������ ������

};


class cltTileManager
{
public:
	cltTileManager(const TCHAR* szsavepath);
	~cltTileManager();


public:
	BOOL			InitTileSet();
	BOOL			DeleteTileSet();	
	bool			FreeTileSet();								// ��� Ÿ�� ��Ʈ�� �޸𸮿��� �����Ѵ�. 

	//------------------------------------
	// Ÿ�� ��Ʈ �ҷ����� 
	//------------------------------------
	BOOL			LoadTileSet(SI32 sibasetilesetunique);		// ���� ������ �°� Ÿ�� ��Ʈ�� �о�´�. 	
	bool			LoadTileSet(SI32 tileset1, SI32 tileset2);	// ������ �ʿ��� Ÿ�ϼ�Ʈ�� ���� �ε��Ѵ�. 

	SI32			FindRefFromUnique_TileSet(SI32 siunique);	// ����ũ ���� �ٰŷ� ���۷����� ã�´�. 
	cltTileInfo*	GetTileInfoPointer(TCHAR* szname);			// �ĺ��ڸ� ����Ͽ� Ÿ�������� �����͸� ���Ѵ�. 

public:
#ifdef _SAFE_MEMORY
	NSafeTArray<SI16, MAX_TILE_UNIQUE_NUMBER>		siTileRef;
#else
	SI16			siTileRef[MAX_TILE_UNIQUE_NUMBER];
#endif
	SI32			siLoadedTileSetImageSize;					// Ÿ�� ��Ʈ�� �ҷ��� Ÿ���� ����Ʈ ��
																// ���� �󸶳� ���� �޸𸮰� Ÿ�ϼ�Ʈ�� �Ҵ�Ǿ� �ִ��� �� �� �ִ�.

	TCHAR			szSavePath[MAX_PATH];						// ������ �о���� ��θ� �����Ѵ�. 
#ifdef _SAFE_MEMORY
	NSafeTArray<cltTileInfo*, MAX_TILESET_NUMBER>		pclTileInfo;
#else
	cltTileInfo*	pclTileInfo[MAX_TILESET_NUMBER];
#endif
};


#endif
