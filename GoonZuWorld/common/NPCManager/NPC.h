//---------------------------------
// 2003/5/17 ���°�
//---------------------------------

#ifndef _NPC_H
#define _NPC_H

#include <directives.h>

#include "Char\CharCommon\Char-Common.h"
#include "../../../NLib/NArray.h"

#define MAX_NPC_KIND_PER_GROUP	5	// KKM 2007 / 08 / 22 NPC���� ���Ͽ��� �ִ� 5��	
#define MAX_NPC_PER_GROUP		1000
#define MAX_NPC_GROUP_NUMBER	1000

class cltNPCGroupUnit{
public:
	SI32 siKind;			// ��ġ�� NPC ����.		
	SI32 siKindMaxNum;		// ��ġ�� NPC�� �ִ� ����.
	SI32 siKindNum;			// ������ NPC�� ���� ����. 
	SI32 siKindLevel;

	cltNPCGroupUnit()
	{
		Init();
	}

	void Init()
	{
		siKind				= 0;
		siKindMaxNum		= 0;
		siKindNum			= 0;
		siKindLevel			= 0;
	}

	void Set(SI32 kind, SI32 maxnum, SI32 level)
	{
		siKind			= kind;
		siKindMaxNum	= maxnum;
		siKindLevel		= level;
	}
};

class cltNPCGroup
{
public:

	SI32 ID;				// �׷���� ��. 
	SI32 MaxNPCNumber;	// �׷쳻 NPC �հ� 
	SI32 siMapIndex;
	SI32 siX, siY;			// NPC ��ġ�� �߽�. 
	SI32 siRadius;			// NPC ��ġ�� �ݰ� 
	DWORD dwLastCheckClock;	// ��ġ�� �˻��� ������ �ð�. 
	DWORD dwSetIntervalClock;	// ��ġ �˻� ����. 	
	DWORD dwLastNoticeClock;	// ���� ������ Ŭ���̾�Ʈ�� �뺸�� ������ �ð�.

	bool bBossGroup ;		// ���� �׷��̳� �ƴϳ�

	SI32 NPCKindNumber;		// ��ġ�� NPC������ ����. 

	SI32 CurrentNPCNumber;	// ������ NPC ����.		

#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, MAX_NPC_PER_GROUP>					NPCList;
	NSafeTArray<SI32, MAX_NPC_PER_GROUP>					NPCKindList;

	NSafeTArray<cltNPCGroupUnit, MAX_NPC_KIND_PER_GROUP>	clUnit;
#else
	SI32 NPCList[MAX_NPC_PER_GROUP];
	SI32 NPCKindList[MAX_NPC_PER_GROUP];

	cltNPCGroupUnit clUnit[MAX_NPC_KIND_PER_GROUP];
#endif

	cltNPCGroup(SI32 id, SI32 maxnpcnumber, SI32 mapindex, SI32 x, SI32 y, SI32 radius, DWORD interval, bool bossGroup );
	~cltNPCGroup();

	// �׷쿡 ���� NPC�� ������ �� ���� �߰��Ѵ�.
	BOOL AddNPCKind(SI32 kind, SI32 num, SI32 level);
	bool AddChar(SI32 id, SI32 kindindex);
	bool SubChar(SI32 idindex);

	// NPCGroup�����ȿ� �����ϴ°� ?
	bool IsInNPCGroup(SI32 mapindex, SI32 x, SI32 y);

	// Ư�� kind�� ĳ���Ͱ� �� �׷쿡 �����ϴ°� ?
	bool IsInKind(SI32 kind);


};

class cltGetNPC
{
protected:
	SI32 m_siRadius;
	SI32 m_siX;
	SI32 m_siY;
	SI32 m_siLevel;
	SI32 m_siKind;
	SI32 m_siNumber;

public:
	cltGetNPC() : m_siRadius(0), m_siX(0), m_siY(0), m_siLevel(0), m_siKind(0), m_siNumber(0) {};
	~cltGetNPC() {};
	
public:
	void SetRadious( SI32 siRadius )	{ m_siRadius	= siRadius; };
	void SetX( SI32 siX )				{ m_siX			= siX; };
	void SetY( SI32 siY )				{ m_siY			= siY; };
	void SetLevel( SI32 siLevel )		{ m_siLevel		= siLevel; };
	void SetKind( SI32 siKind )			{ m_siKind		= siKind; };
	void SetNumber( SI32 siNumber )		{ m_siNumber	= siNumber; };
	

	void SetAll( SI32 siRadius, SI32 siX, SI32 siY, SI32 siLevel, SI32 siKind, SI32 siNumber )
	{
		m_siRadius		= siRadius;
		m_siX			= siX;
		m_siY			= siY;
		m_siLevel		= siLevel;
		m_siKind		= siKind;
		m_siNumber		= siNumber;
	}

	SI32 GetRadius( void )				{ return m_siRadius; };
	SI32 GetX( void )					{ return m_siX; };
	SI32 GetY( void )					{ return m_siY; };
	SI32 GetLevel( void )				{ return m_siLevel; };
	SI32 GetKind( void )				{ return m_siKind; };
	SI32 GetNumber( void )				{ return m_siNumber; };

};
//-------------------------------------------
// cltNPCManagerCommon
//-------------------------------------------
class cltNPCManagerCommon{
public:
	cltCharManager* pclCM;
#ifdef _SAFE_MEMORY
	NSafeTArray<cltNPCGroup*, MAX_NPC_GROUP_NUMBER>		pclNPCGroup;
#else
	cltNPCGroup* pclNPCGroup[MAX_NPC_GROUP_NUMBER];
#endif

	cltNPCManagerCommon(cltCharManager* pclCM);
	virtual ~cltNPCManagerCommon();

	virtual BOOL SetChar(){return FALSE;}

	enum NPCMC
	{
		NPCMC_SEARCH_COUNT = 20
	};


	BOOL SetNPCGroup(SI32& group, TCHAR* npcgroupname, bool clonemap = false, SI32 clonemapindex = 0 );
	BOOL SetNPCGroup();

	// NPCGroup�����ȿ� �����ϴ°� ?
	bool IsInNPCGroup(SI32 npcgroup, SI32 mapindex, SI32 x, SI32 y);

	bool MakeNPCInstance(SI32 mapindex,SI32 party,bool boss = false );
	bool DeleteNPCInstance(SI32 mapindex);
	bool CheckTimeOut(SI32 mapindex); // �ð� �ʰ� ���. true�� ���� �ð� �������� ����.

	void SendInstanceMapInfo(SI32 mapindex);
	void SetInstanceChar(SI32 mapindex);
	void SendGift(SI32 mapindex,SI32 myid,SI32 enemyid);
	
	// [����] 20404 - �� ���� �߰� 
	void SetGuildNPCPoint( SI32 siKind, cltIdentity *pclIdentity );	// ��� �δ� ���� ����
	void MakeGuildRegenerationNPC( SI32 siMapIndex );				// ��� �δ� ���� �����ϱ�
	bool GetGuildNPCInformation( IN SI32 siMapIndex, OUT SI32 *psiKind, OUT SI32 *psiNumber );		// ��� �δ� �ȿ� �ִ� ���� ����/�� �˾ƿ���
	bool GetGroupNPCInformation( IN SI32 siMapIndex, OUT cltGetNPC *pclGetNPC );		// NPC �׷쿡 �ִ� ���� ����/�� �˾ƿ���

	// npc �׷쿡�� Ư�� kind�� ������ ��´�.
	SI32 GetKindLevel(SI32 kind);

	// npc �׷쿡�� Ư�� kind�� �ְ����� ��´�.
	SI32 GetKindMaxLevel(SI32 kind);
};


//-------------------------------------------
// REGEN ������ ���������� ����ü // JAYCEE
//-------------------------------------------
class cltRegenPos {
public:
	TCHAR szMapName[50];
	TCHAR szMapPos[50];
	TCHAR szNearMapInfo[50];

	cltRegenPos()
	{
		memset(szMapName,		0, sizeof(szMapName));
		memset(szMapPos,		0, sizeof(szMapPos));
		memset(szNearMapInfo,	0, sizeof(szNearMapInfo));
	}	
};

//-------------------------------------------
// cltNPCManagerClient
//-------------------------------------------
class cltNPCManagerClient : public cltNPCManagerCommon{
public:

	cltNPCManagerClient(cltCharManager* pclCM);
	~cltNPCManagerClient();

	// npc �׷쿡�� Ư�� kind�� ��ġ ���� text�� ���´�.
	bool GetKindPos(SI32 kind, TCHAR* ptext, SI16 txtSize);
	bool GetKindPos(SI32 kind, cltRegenPos *regenpos, SI32 *siCount);
	// npc �׷쿡�� Ư�� kind�� ������ ��´�.
//	SI32 GetKindLevel(SI32 kind);
//	bool GetDirectionStr(SI32 sx, SI32 sy, SI32 dx, SI32 dy, TCHAR *szText);

	// npc �׷쿡�� Ư�� ��(index)�� �ִ� ���͵��� kind�� �����´�.
	bool GetKindMapInx(SI32 mapindex, SI32 siKind[], SI32 siKindLevel[], SI32 siMaxSize);
	// ã�Ƴ� ����Ÿ���� �̹� �ִ��� ������ �˻��Ѵ� ������ true ������ false
	bool FindKindData(SI32 siKind[], SI32 siCount, SI32 npckind);

};

//-------------------------------------------
// cltNPCManagerServer
//-------------------------------------------
class cltNPCManagerServer : public cltNPCManagerCommon{
public:

	cltNPCManagerServer(cltCharManager* pclCM);
	~cltNPCManagerServer();

	// NPC �׷� ������ ���� ĳ���͸� �߰��Ѵ�.
	BOOL SetChar();

	// npc �׷쿡�� Ư�� ���������� �ִ� ���͵��� kind�� �����´�.
	bool GetKindLevel(SI32 sLevel, SI32 eLevel, SI32 siKind[], SI32 maxsize);

	// ã�Ƴ� ����Ÿ���� �̹� �ִ��� ������ �˻��Ѵ� ������ true ������ false
	bool FindKindData(SI32 siKind[], SI32 siCount, SI32 npckind);

	//[�߰� : Ȳ���� 2007. 10. 31 ������ ������ �̸� ������ ������ ���� �̸��� �v������ �߰�.]
	// npc �׷쿡�� Ư�� ��(index)�� �ִ� ���͵��� kind�� �����´�.
	bool GetKindMapInx(SI32 mapindex, SI32 siKind[], SI32 siKindLevel[], SI32 siMaxSize);
};

#endif