//-----------------------------------------------------------------------------
// 2005/09/26 ������
//-----------------------------------------------------------------------------

#ifndef _MAPTYPEMANAGER_H
#define _MAPTYPEMANAGER_H

#define MAX_MAPTYPE_NUMBER	200										// ���� Ÿ���� �ִ� ����. 

#define MAPTYPE_ATB_VILLAGE_SPRING			(DWORD)1				// �� ����
#define MAPTYPE_ATB_VILLAGE_SUMMER			((DWORD)1 << 1)			// ���� ����
#define MAPTYPE_ATB_VILLAGE_AUTUMN			((DWORD)1 << 2)			// ���� ����
#define MAPTYPE_ATB_VILLAGE_WINTER			((DWORD)1 << 3)			// �ܿ� ����
#define MAPTYPE_ATB_VILLAGE_PORT			((DWORD)1 << 4)			// �ױ� ���� 
#define MAPTYPE_ATB_HUNT					((DWORD)1 << 5)			// ������ ��
 


#define MAPTYPE_STRUCTURE_POINT_X_SLOT0	9
#define MAPTYPE_STRUCTURE_POINT_Y_SLOT0	42
#define MAPTYPE_STRUCTURE_POINT_X_SLOT1	36
#define MAPTYPE_STRUCTURE_POINT_Y_SLOT1	52
#define MAPTYPE_STRUCTURE_POINT_X_SLOT2	46
#define MAPTYPE_STRUCTURE_POINT_Y_SLOT2	52
#define MAPTYPE_STRUCTURE_POINT_X_SLOT3	24
#define MAPTYPE_STRUCTURE_POINT_Y_SLOT3	40
#define MAPTYPE_STRUCTURE_POINT_X_SLOT4	6
#define MAPTYPE_STRUCTURE_POINT_Y_SLOT4	26
#define MAPTYPE_STRUCTURE_POINT_X_SLOT5	34
#define MAPTYPE_STRUCTURE_POINT_Y_SLOT5	40
#define MAPTYPE_STRUCTURE_POINT_X_SLOT6	46
#define MAPTYPE_STRUCTURE_POINT_Y_SLOT6	26
#define MAPTYPE_STRUCTURE_POINT_X_SLOT7	49
#define MAPTYPE_STRUCTURE_POINT_Y_SLOT7	42
#define MAPTYPE_STRUCTURE_POINT_X_SLOT8	22
#define MAPTYPE_STRUCTURE_POINT_Y_SLOT8	52
#define	MAPTYPE_STRUCTURE_POINT_X_SLOT9	9
#define	MAPTYPE_STRUCTURE_POINT_Y_SLOT9 52

//-----------------------------------------------------------------------------
// �� Ÿ�� ����. 
//-----------------------------------------------------------------------------
class cltMapTypeInfo
{
public:
	cltMapTypeInfo();
	~cltMapTypeInfo();

	void	SetMapType( SI32 mapunique, TCHAR* pname, 
						SI32 centerx, SI32 centery, SI32 gatex, SI32 gatey, 
						POINT* ppoint,
						SI32 atb, SI32 adapt, SI32 level, GMONEY money,SI32 huntadapt );

public:
	SI32	siMapUnique;
	TCHAR	szMapTypeName[ 64 ];

	SI32	siCenterX;
	SI32	siCenterY;

	SI32	siGateX;	
	SI32	siGateY;								// �� �����ȿ����� ���� ����Ʈ ��ġ. 

#ifdef _SAFE_MEMORY
	NSafeTArray<POINT, MAX_CONSTRUCTION_NUM>		StrLocation;
#else
	POINT	StrLocation[ MAX_CONSTRUCTION_NUM ];	// �ǹ� ���� ��ǥ. 
#endif

	SI32	siAdaptVillageType;						// �������� ��� ���� Ÿ������ ���� �� �ִ°� ?
													// (0�̸� ���������� ���� �� ����) 

	SI32	siAdaptHuntType;						// �� ������ ������ ������ ���� ���ִ°�? 0�̸� ��� ���Ѵ�.

	SI32	siAdaptNeedVillageLevel;				// ���� ������ ä���ϴµ� �ʿ��� ���� ���� 
	GMONEY	siAdaptNeedVillageMoney;				// ���� ������ ä���ϴµ� �ʿ��� ���� �ڱ�. 
	SI32	siAtb;

};

//-----------------------------------------------------------------------------
// �� Ÿ�� ���� ������
//-----------------------------------------------------------------------------
class cltMapTypeManager
{
public:
	cltMapTypeManager();
	~cltMapTypeManager();

	void		LoadMapTypeInfo();					// MapTypeInfo�� �ε��Ѵ�
	void		LoadMapTypeInfo_Village();			// MapTypeInfo_Village�� �ε��Ѵ�
	void		LoadMapTypeInfo_Hunt();				// MapTypeInfo_Hunt�� �ε��Ѵ�

	bool		AddMapType( SI32 mapunique, TCHAR* maptypename, 
							SI32 centerx = 0, SI32 centery = 0, 
							SI32 gatex = 0, SI32 gatey = 0, 
							POINT* ppoint = 0, SI32 atb = 0, 
							SI32 adapt = 0, SI32 level = 0, 
							GMONEY money = 0, SI32 huntadapt = 0 );

	bool		SetMapType( SI32 mapunique, TCHAR* maptypename, 
							SI32 centerx = 0, SI32 centery = 0, 
							SI32 gatex = 0, SI32 gatey = 0, 
							POINT* ppoint = 0, SI32 atb = 0, 
							SI32 adapt = 0, SI32 level = 0, 
							GMONEY money = 0, SI32 huntadapt = 0 );

	TCHAR*		GetMapTypeNameFromUnique( SI32 mapunique );

public:
#ifdef _SAFE_MEMORY
	NSafeTArray<cltMapTypeInfo*, MAX_MAPTYPE_NUMBER>		pclMapTypeInfo;
#else
	cltMapTypeInfo*		pclMapTypeInfo[ MAX_MAPTYPE_NUMBER ];
#endif

};


#endif