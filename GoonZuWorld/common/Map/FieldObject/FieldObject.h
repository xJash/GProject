//---------------------------------
// 2003/5/17 ���°�
//---------------------------------

#ifndef _FIELDOBJECT_H
#define _FIELDOBJECT_H

#include <directives.h>
#include <windowsx.h>

#include "TSpr.h"
#include "../../../../NLib/NArray.h"

class HashStringInt;
class cltFieldObjectManager;

#define MAX_FIELDOBJECTSET_NUMBER			3000
#define MAX_FIELDOBJECTTYPE_NUMBER			200
#define MAX_FIELDOBJECT_PER_BRUSH			20	// �Ѱ� �귯�ô� ���� �� �ִ� Field Object ����. 
#define MAX_FIELDOBJECTBRUSH_NUMBER			20	// ���� �� �ִ� �ִ� �귯�� ����. 
#define	MAX_FIELD_OBJECT_PER_STRUCTURE_SET	15  // �Ѱ��� StructureSet�� ���� �� �ִ� FieldObect ����. 
#define MAX_VILLAGE_STRUCTURE_NUMBER		20	// ���� �� �ִ� �ִ� Structure�� ����. (�ǹ� ������ ��.) 
#define MAX_STRUCTURE_NAME_LENGTH			20	// �ǹ��� �̸� ����. 
#define MAX_FOUNIQUE						10000	// FieldObject �� �ִ� Unique
#ifdef _CHINA
	#define MAX_FOSPR_NUMBER				500	// FieldObject�� �ѹ��� �ε��� �� �ִ� �ִ� ����. 
#else
	#define MAX_FOSPR_NUMBER				100
#endif

//--------------------------------------------
// �ʵ� ������Ʈ�� Ÿ��. 
//--------------------------------------------
#define FOTYPE_VILLAGE						0
#define FOTYPE_GATE							12			// �� 
/*
#define FOTYPE_TREE							1			// ����. 			
#define FOTYPE_BAMBOO						2			// �볪�� . 			
#define FOTYPE_FLOWER						3			// Flower
#define FOTYPE_SUNFLOWER					4			// �عٶ��
#define FOTYPE_FLOWERTREE					5			// �ɳ���
#define FOTYPE_PINETREE						6			// �ҳ���
#define FOTYPE_MT							7			// �� 
#define FOTYPE_MTGREEN						8			// �����. 
#define FOTYPE_MTFALL						9			// ������ 
#define FOTYPE_MTSNOW						10			// �ܿ�� 
#define FOTYPE_VOLCANO						11			// ȭ�� 

#define FOTYPE_WATERFALL					13			// ���� 
#define FOTYPE_STATUE						14			// ���� 
#define FOTYPE_BUILD						15			// �ǹ� 
#define FOTYPE_VILLAGE1OBJ					16			// ����1 ������ 
#define FOTYPE_SEAPALACE					17			// ��� 1�� ������ 
#define FOTYPE_GOBLINHOUSE1					18			// ������ 1��. 
#define FOTYPE_NPC							19			// NPC
#define FOTYPE_POND							20			// Pond
#define FOTYPE_BRIDGE						21			// Bridge
#define FOTYPE_AROUNDBEAR					22			// ���ൿ�� �ֺ���. 
#define FOTYPE_AROUNDWOOD					23			// �����ұ� �ֺ���. 
#define FOTYPE_AROUNDSMALLFOREST			24			// ����Ǯ�� �ֺ���. 
#define FOTYPE_AROUNDCASTLE					25			// ���ѻ꼺 �ֺ���. 
#define FOTYPE_AROUNDCASTLESUB				26			// ���ѻ꼺 �ֺ���. (�ٴ�) 
#define FOTYPE_AROUNDGOBLIN					27			// ������ �ֺ���. 
#define FOTYPE_ARSANTA						28			// ��Ÿ �۾��� �ֺ���.
#define FOTYPE_AROUNDMIHWANG				29			// ��Ȳ�� �ֺ�. 
#define FOTYPE_PRISON						30			// ���� 
#define FOTYPE_PRISONBOTTOM					31
#define FOTYPE_PRISONWALL					32
#define FOTYPE_WOOD2PART					33			// ȭ�漺�κ�. 
#define FOTYPE_AROUNDGUMHA					34			// ���ϱ��ֺ��� 
#define FOTYPE_PALACE						35			// �溹�� 
#define FOTYPE_PALACEFLOOR					36
#define FOTYPE_FLOOR						37			// ���� �ٰ� ĳ���Ͱ� ���� ���ٴϴ� ������Ʈ��
#define FOTYPE_WALL							38			// �� ������
#define FOTYPE_FLAG							39			// ��ߵ�
#define FOTYPE_FRONTSCREEN					40			// ��ũ�� ���� ��� ������Ʈ�� - ĳ���Ͱ� �ڷ� ���� ������ ���� ex: �����
#define FOTYPE_FIELDTILE					41			// �ʵ������Ʈ�� Ÿ��ó�� ��� �� - �� �ö�
#define FOTYPE_FIELDTILESTATUE				42			// �ʵ������Ʈ�� Ÿ��ó�� ��� �� - ������ ����
#define FOTYPE_FIELDTILEBOTTOM				43			// �ʵ������Ʈ�� Ÿ��ó�� ��� �� - ������ �ö�
#define FOTYPE_GYUNGJOO						44			// �ʵ������Ʈ�� Ÿ��ó�� ��� �� - ���������� ������ ��
#define FOTYPE_SHELLFISH_FLOOR				45			// �¾��������� ���� - floor
#define FOTYPE_SHELLFISH_STATUE				46			// �¾��������� ���� - statue
#define FOTYPE_FENCE						47			// �����
#define FOTYPE_MTBAECKDOO					48			// ��λ�
#define FOTYPE_BEGINNER1					49			// �ʺ��� �����
// ���� ������
#define FOTYPE_GAURI_BUILD					50			// �ǹ�
#define FOTYPE_GAURI_STATUE					51			// ������
#define FOTYPE_GAURI_FLOOR					52			// �ٴڿ� �پ ��� �ö󰡴� ��
#define FOTYPE_SEASIDE_FLOOR				53			// �ĵ�,�����
#define FOTYPE_AOZI_STATUE					54			// �ƿ��� ź��
#define FOTYPE_PORTHOLE						55			// �������
#define FOTYPE_TOPOGRAPHY					56			// ����,���������
#define FOTYPE_MTSPECIAL					57			// Ư���� ���
#define FOTYPE_TREESHADOW					58			// ���� �׸���
// ���� ������
#define FOTYPE_DUNGEON_TILE					59			// ���� ����Ÿ��
#define FOTYPE_DUNGEON_STATUE				60			// ���� ������Ʈ��
#define FOTYPE_DUNGEON_WALL					61			// ��������

#define FOTYPE_GUMHA_WALL					62			// ����
#define FOTYPE_AOZI_WALL					63			// �ƿ���
#define FOTYPE_HAHOI_WALL					64			// ��ȸ
#define FOTYPE_JEJU_WALL					65			// ����

#define FOTYPE_HANGWA_WALL					66			// �Ѱ�
#define FOTYPE_HANGWA_STATUE				67

#define FOTYPE_PRISON_WALL					68			// ���ϰ���
#define FOTYPE_PRISON_STATUE				69

#define FOTYPE_JEJUVILLAGE_WALL				70
#define FOTYPE_JEJUVILLAGE_STATUE			71

#define FOTYPE_ICEFORTRESS_WALL				72			// ������
#define FOTYPE_ICEFORTRESS_STATUE			73

#define	FOTYPE_WOOD1_STATUE					74			// ���� �ұ� 1�� Ÿ�������� wood3���� �Ǿ� ����
#define	FOTYPE_WOOD2_STATUE					75			// ���� �ұ� 2�� Ÿ�������� wood1���� �Ǿ� ����

#define FOTYPE_BEARCAVE03_WALL				76
#define FOTYPE_BEARCAVE03_STATUE			77

#define FOTYPE_NAMHANMFW_WALL				78
#define FOTYPE_NAMHANMFW_STATUE				79

#define FOTYPE_OSAKA_WALL					81
#define FOTYPE_OSAKA_STATUE					82
#define FOTYPE_OSAKA_FLOOR					83

#define FOTYPE_KANGHWADO_WALL				84
#define FOTYPE_NEWHEAVENS01_WALL			85				// õ��� 1��
#define FOTYPE_NEWHEAVENS01_STATUE			86
#define FOTYPE_DOSUNPALACE_STATUE			87				// ������
#define FOTYPE_PIRATESHIP01_STATUE			88				// ������ 1��

#define FOTYPE_CHINA_PALACE					89				// �ڱݼ�
#define FOTYPE_CHINA_BEGINNER_STATUE		90				// �߱� �ʺ��� �� �� ���
#define FOTYPE_CHINA_BEGINNER_FLOOR			91				// �߱� �ʺ��� �ٴ�
#define FOTYPE_CHINA_PALACESHADOW			92				// �ڱݼ� �׸���

#define FOTYPE_CHINA_GOVERMENTOFFICE		93				// ��û
#define FOTYPE_CHINA_GUILD					94				// ��� ������
#define FOTYPE_CHINA_VILLAGE				95				// ���� ���� ������Ʈ
*/

// MAX_FIELDOBJECTTYPE_NUMBER				100

//---------------------------------------------
// �ʵ� ������Ʈ �Ӽ� 
//---------------------------------------------
// ���� 
// ���� 15��Ʈ : Field Object Unique 
// ���� 1��Ʈ  : ������Ʈ 
// ���� 16��Ʈ : Village Unique
// ���� (Tree, Bamboo���� ��� ���� �Ӽ��� ���´�. )
// ���� 15��Ʈ : Field Object Unique 
// ���� 1��Ʈ  : ������Ʈ 

#define FOATB_VILLAGE					((DWORD)1)
#define FOATB_TREE						((DWORD)1 << 1)
#define FOATB_MOUNTINE					((DWORD)1 << 2)
#define FOATB_GATE						((DWORD)1 << 3)
#define FOATB_STATUE					((DWORD)1 << 4)
#define FOATB_BUILD						((DWORD)1 << 5)
#define FOATB_FLOOR						((DWORD)1 << 6)  // �ٴڿ� �پ��ִ� ������Ʈ. 
#define FOATB_BRIDGE					((DWORD)1 << 7)

// Field Object Type�� ���� ���� 
class cltFieldObjectTypeInfo
{
public:
	cltFieldObjectTypeInfo(DWORD dwtype, UI08 color, TCHAR* name, DWORD atb, cltFieldObjectTypeInfo* pclinfo);
	~cltFieldObjectTypeInfo();

	cltFieldObjectTypeInfo* pParent;		// �θ� TypeInfo�� ������.  

	DWORD		dwType;
	DWORD		dwAtb;						// type�� �Ӽ�. FOATB_VILLAGE|FOATB_TREE ��.. 
	TCHAR*		pszName;					// Type�� �̸�. 
	SHORT		Unique;						// �� ������Ʈ ������ ���� ��ȣ. 
	UI08		uiColor;
};

class cltFieldObjectInfo
{
public:
	cltFieldObjectInfo( SHORT unique, DWORD dwtype, DWORD dwimagefilenumber, /*cltFieldObjectInfo* pparent, */
						TCHAR* szname, SI32 transmode,SI32 alphavalue,SI32 shadow,TCHAR* zipname);
	~cltFieldObjectInfo();

	void		Init();

	bool		GetInfoFileName(TCHAR* szfilename);
	
	bool		ReadSetArrayInfo(TCHAR* szfilename);								// �迭 ������ �о�´�. 
	bool		WriteSetArrayInfo(TCHAR* szfilename);								// �迭 ������ �����Ѵ�. 

	bool		ReadSetArrayInfoFromMemory(BYTE* pMemory);						// �迭 ������ �о�´�. 

	TSpr*		GetSpr(cltFieldObjectManager* pFOManager, DWORD dwframe);			// �̹����� ��� �ִ� ������ �����͸� �����Ѵ�. 	
	void		SetLastUseFrame(cltFieldObjectManager* pFOManager, DWORD frame);	// ���������� ���� �������� �����Ѵ�. 
	void		LoadDetailInfo();

	//BOOL AddChild(cltFieldObjectInfo* pparent);									// �ڽ� ��Ʈ�� �߰��Ѵ�. 

public:
	SHORT		Unique;					// �� ������Ʈ ������ ���� ��ȣ. 
	DWORD		dwType;					// �Ӽ��� ����.
	TCHAR*		pszName;				// ��Ʈ�� �̸�. 
	SI32		siTransMode;			// ����ִ� ��� 
	SI32		siAlphaValue;			// ���İ�
	SI32		siTreeShadow;			// ���� �׸��ڵ�
	SI16		siFOSprRef;				// �̹����� ����Ǿ� �ִ� ������ ���� ref
	SI32		TileXsize;
	SI32		TileYsize;
	SI32		TileCenterX;
	SI32		TileCenterY;
	SI32		IndentX;
	SI32		IndentY;
	SI32		AniFrame;
	SI32		AniDelay;
	bool		bIsMainMap;

	TCHAR*		pszZipName;				// �������� �̸�. 

};



class cltFieldObjectBrush
{
public:
	cltFieldObjectBrush(TCHAR* pname);
	~cltFieldObjectBrush();

	BOOL		Add(cltFieldObjectInfo* pfieldobjectinfo);		// �귯���� Field Object�� �߰��Ѵ�. 
	SI32		GetRandUnique();								// ������ �ִ� cltFieldObjectInfo�߿��� �Ѱ��� �����ϰ� �� �� ���� unique���� �����Ѵ�. 


public:
#ifdef _SAFE_MEMORY
	NSafeTArray<cltFieldObjectInfo*, MAX_FIELDOBJECT_PER_BRUSH>		pFieldObjectInfo;
#else
	cltFieldObjectInfo* pFieldObjectInfo[MAX_FIELDOBJECT_PER_BRUSH];	// �귯���� ���� �ִ� �ʵ� ������Ʈ�� ������. 
#endif

	SI32		FielObjectNumber;								// Field Object�� ����. 
	TCHAR		szName[MAX_PATH];
};

class cltFieldObjectManager
{
public:
	cltFieldObjectManager(SI32 gamemode);
	~cltFieldObjectManager();


	//--------------------------------------------------------
	// Field Object Type ���� 
	//--------------------------------------------------------

	bool		InitFieldObjectManager();
	bool		InitFieldObjectManager_China();

	
	BOOL		InitTypeSet();									// Field Object Type�� �ʱ�ȭ�Ѵ�. 
	BOOL		InitTypeSet_China();

	BOOL		InitBrush();									// �귯���� �����Ѵ�. 
	BOOL		InitSet();
	BOOL		LoadSet(DWORD frame, cltFieldObjectInfo* pclinfo, bool bmainmap = false );		// ���� ������ �°� ��Ʈ�� �о�´�. 
	SI32		FindRefFromUniqueMinus(SI32 siunique);			// ����ũ ���� �ٰŷ� ���۷����� ã�´�. 

	SI32		AnalyzeAtbString(TCHAR* string);					// ��Ʈ�� �Ӽ� ������ ��� string���ڿ��� �м��Ͽ� ���ڿ��� �Ǿ� �ִ� �ؽ�Ʈ�� ���ӳ����� �ǹ��ִ� ���ڷ� �����Ͽ� �����Ѵ�. 
	SI32		GetAtb(SI32 founique);							// FieldObject�� Atb�� ã�´�.
	void		DeleteIfNotUse(DWORD curframe);					// ������ ���� Field Object�� �޸𸮿��� �����Ѵ�. 
	SI32		FindUniqueFromName(TCHAR* name);					// �̸��� �ٰŷ� Unique�� ã�´�. 
	SI32		FindEmptySpr();									// Spr�̹����� ������ �� ������ ã�´�. 
	cltFieldObjectInfo* GetInfoPointer(TCHAR* szname);			// �ĺ��ڸ� ����Ͽ� ������ �����͸� ���Ѵ�. 


public:
	SI32					siLoadedSize;						// �޸𸮿� �ҷ��� �������� �� ����Ʈ ��. 

#ifdef _SAFE_MEMORY
	NSafeTArray<cltFieldObjectInfo*, MAX_FIELDOBJECTSET_NUMBER>			pclInfo;
	NSafeTArray<cltFieldObjectTypeInfo*, MAX_FIELDOBJECTTYPE_NUMBER>	pclTypeInfo;
	NSafeTArray<cltFieldObjectBrush*, MAX_FIELDOBJECTBRUSH_NUMBER>		pclFieldObjectBrush;

	NSafeTArray<SI16, MAX_FOUNIQUE>			siFORef;

	NSafeTArray<DWORD, MAX_FOSPR_NUMBER>	dwLastUseFrame;	// ���������� ���� ������. 
	NSafeTArray<SI16, MAX_FOSPR_NUMBER>		FOInfoUnique;
	NSafeTArray<TSpr, MAX_FOSPR_NUMBER>		FOSpr;			// �̹����� ���� ������. 
#else
	cltFieldObjectInfo*		pclInfo[MAX_FIELDOBJECTSET_NUMBER];
	cltFieldObjectTypeInfo* pclTypeInfo[MAX_FIELDOBJECTTYPE_NUMBER];
	cltFieldObjectBrush*	pclFieldObjectBrush[MAX_FIELDOBJECTBRUSH_NUMBER];

	SI16					siFORef[MAX_FOUNIQUE];

	DWORD					dwLastUseFrame[MAX_FOSPR_NUMBER];	// ���������� ���� ������. 
	SI16					FOInfoUnique[MAX_FOSPR_NUMBER];
	TSpr					FOSpr[MAX_FOSPR_NUMBER];			// �̹����� ���� ������. 
#endif

	HashStringInt*			pclHashTable;

};

//------------------------------------
// ������ ���� VillageStructure ����. 
//------------------------------------
class cltVillageStructureUnitInfo
{
public:
	SI32		siX, siY;
	SI32		siFieldObjectArray;
	bool		bKeySwitch;

	cltVillageStructureUnitInfo()
	{
		siX					= 0;
		siY					= 0;
		siFieldObjectArray	= 0;
		bKeySwitch			= false;
	}
};

class cltVillageStructureInfo
{
public:
	cltVillageStructureInfo(SI32 unique, TCHAR* szname, SI32 ranktype);
	~cltVillageStructureInfo();

	bool		IsKeyStructure(SI32 sicenterx, SI32 sicentery);									//sicenterx, sicentery�� �߽����� ��� �ִ� �ǹ��� �ǹ� ��Ʈ�� Ű�� �Ǵ� �ǹ����� Ȯ���Ѵ�. 
	BOOL		Add(SI32 six, SI32 siy, SI32 sifieldobjectunique, bool bkeyswitch = false);		// FieldObject�� StructureInfo�� �߰��Ѵ�. 	
	BOOL		AddUP(SI32 six, SI32 siy, SI32 sifieldobjectunique, bool bkeyswitch = false);	// UPFieldObject�� StructureInfo�� �߰��Ѵ�. 
	void		SetConstructionInfo( SI32 needVillageLevel, GMONEY needMoney, BOOL destroy, SI32 siNeedVillageScore = 0 );
	SI32		GetNeedVillagelevel();															// �Ǽ��� �ʿ��� ���� ������ ���Ѵ�. 

	SI32		siUnique;
	SI32		siRankType;
	SI32		siNeedVillageLevelRate;			// ���� ���ؼ� �ʿ���ϴ� ������ ���� .
	GMONEY		siNeedMoney;					// �Ǽ��� �ʿ��� �ڱ�. 
	BOOL		bDestroyable;					// ��ü ���� ����
	SI32		siNeedVillageScore;				// �ʿ��� ���� ����.

	TCHAR		szName[MAX_STRUCTURE_NAME_LENGTH];

	SI32		siFieldObjectNumber;		// ������ �ִ� FieldObject�� ����. 
#ifdef _SAFE_MEMORY
	NSafeTArray<cltVillageStructureUnitInfo, MAX_FIELD_OBJECT_PER_STRUCTURE_SET>	clUnit;
#else
	cltVillageStructureUnitInfo clUnit[MAX_FIELD_OBJECT_PER_STRUCTURE_SET];
#endif

	SI32		siUPFieldObjectNumber;		// ������ �ִ� UPFieldObject�� ����
#ifdef _SAFE_MEMORY
	NSafeTArray<cltVillageStructureUnitInfo, MAX_FIELD_OBJECT_PER_STRUCTURE_SET>	clUPUnit;
#else
	cltVillageStructureUnitInfo clUPUnit[MAX_FIELD_OBJECT_PER_STRUCTURE_SET];
#endif



};

//-----------------------------------
// VillageStructure ������ ������. 
//-----------------------------------
class cltVillageStructureSet
{
public:
	cltVillageStructureSet();
	~cltVillageStructureSet();

	SI32		FindRefFromUnique(SI32 unique);

	//sicenterx, sicentery�� �߽����� ��� �ִ� �ǹ��� strunique�ǹ� ��Ʈ�� Ű�� �Ǵ� �ǹ����� Ȯ���Ѵ�. 
	bool		IsKeyStructure(SI32 sicenterx, SI32 sicentery, SI32 strunique);

	// ranktype�� �ٰŷ� �ǹ� �̸��� ����. 
	bool		GetStructureNameFromRankType(SI32 ranktype, TCHAR* pname, SI16 txtSize);

	// �ǹ� �̸��� �ٰŷ� ranktype�� ���ش�.
	SI32		GetRankTypeFromStructureName(TCHAR* pname);
	SI32		GetRankTypeFromStrUnique( SI32 strunique );
	SI32		GetStrUniqueFromRankType( SI32 ranktype );
	SI32		FindRefFromRankType( SI32 ranktype );


public:
#ifdef _SAFE_MEMORY
	NSafeTArray<cltVillageStructureInfo*, MAX_VILLAGE_STRUCTURE_NUMBER>		pclVillageStructureInfo;
#else
	cltVillageStructureInfo* pclVillageStructureInfo[MAX_VILLAGE_STRUCTURE_NUMBER];
#endif
};

#endif
