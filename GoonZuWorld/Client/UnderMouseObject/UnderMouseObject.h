#ifndef _UNDERMOUSEOBJECT_H
#define _UNDERMOUSEOBJECT_H

#include <Directives.h>

class cltCharManager;
class cltIDManager;
class cltMapClient;
class cltClient;

class CDrawSequence;

//-------------------------------------------
// ���콺�� ������ ��ü�� ����.
//-------------------------------------------
class cltMouseObject{
public:
	int X, Y;
	SI32 ID;

	cltMouseObject()
	{
		Init();
	}

	void Init()
	{
		X	= 0;
		Y	= 0;
		ID	= 0;
	}

	void Set(SI32 x, SI32 y, SI32 id)
	{
		X	= x;
		Y	= y;
		ID	= id;
	}
};

//------------------------------------------
// ���콺 �Ʒ� ��ü�� ó���ϴ� Ŭ����. 
//------------------------------------------
class cltUnderMouseObject{
public:
	cltClient*		pclGame;
	cltCharManager* pclCM;

	// ĳ������ ���, 
	SI32 ID;					// ���콺 ������ �Ʒ��� �ִ� ĳ����. 
	SI32 siUnderMouseLockChar;	// ���콺 ������ �� ĳ����. 

	SI32 siUnderUserCnt;

	// �ǹ��� ���, 
	SI32 siStructureUnique;		// �ǹ��� ����. 
	// NPC�� ���, 
	SI32 siNPCUnique;			// NPC�� ���, 
	// Gate �� ���, 
	SI32 siGateUnique;
	// ������ ���, 
	SI32 siVillageUnique;
	// å���� ���, 
	SI32 siDeskUnique;

	// ���콺 ���� Ÿ�� ��Ȳ. 
	SI32 siTileAtb;		

	// �������� ���, 
	SI32 siItemUnique;
	SI32 siItemIndex;
	SI32 siItemX, siItemY;


	SI32 siRX, siRY;			// ��Ʈ ������ ȭ�� ��� ����.

	DWORD NewIDSelectedClock;	// ���ο� ĳ���͸� ������ �ð�. 

	CDrawSequence* pclDrawSequence;	// ���콺 ���� ĳ���͸� ã���� ����ϴ� ���� ����

public:
	SI32 MapX, MapY;                    // ���콺�� ��ġ�� Tile ��ǥ 

	cltUnderMouseObject(cltClient* pclgame, cltCharManager* pclcm)
	{
		pclGame	= pclgame;
		pclCM	=  pclcm;
		

		Init();
	}

	~cltUnderMouseObject();

	void Init();
	 
	// ���󿡼� ĳ���͸� ã�´�. 
	BOOL FindLandChar(cltMapClient* pclMap, OUT SI32 * newid, OUT SI32 * underUserCnt );
	// ���๰�� ã�´�. 
	SI32 FindStructure(cltMapClient* pclMap);
	// Gate�� ã�´�. 
	SI32 FindGate(cltMapClient* pclMap);
	// ������  ã�´�. 
	SI32 FindVillage(cltMapClient* pclMap);
	
	// FieldObject�� ã�´�. ã���� �� FOUnique�� �����Ѵ�. 
	SI32 FindFieldObject(cltMapClient* pclMap);


	// �������� ã�´�. ã���� true ����. 
	bool FindItem(cltMapClient* pclMap, SI32* pitemunique, SI32* pitemindex);


	// ���콺 �Ʒ� ��ü�� �ľ��Ѵ�. 
	void GetUnderMouseObject(cltMapClient* pclMap, SI32 screenmousex, SI32 screenmousey);

	SI32 GetUnderMouseID()const{return ID;}
	void SetUnderMouseID(SI32 id){ID = id;}
   
	SI32 GetUnderUserCnt()const{return siUnderUserCnt;}
	void SetUnderUserCnt(SI32 cnt){ siUnderUserCnt  = cnt;}

	SI32 GetStructureUnique()const{return siStructureUnique;}
	SI32 GetNPCUnique()const{return siNPCUnique;}

	SI32 GetGateUnique()const{return siGateUnique;}

	SI32 GetVillageUnique()const{return siVillageUnique;}
	
	SI32 GetItemUnique()const{return siItemUnique;}
	SI32 GetItemIndex()const{ return siItemIndex;}
	SI32 GetItemX()const{return siItemX;}
	SI32 GetItemY()const{return siItemY;}
	
	void SetRX(SI32 rx){siRX = rx;}
	SI32 GetRX()const{return siRX;}

	void SetRY(SI32 ry){siRY = ry;}
	SI32 GetRY()const{return siRY;}
	
};



#endif