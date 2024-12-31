#include "..\CommonLogic\CommonLogic.h"

#include "..\Char\KindInfo\KindInfo.h"
#include "..\..\Lib\AStar\AStarListMgr.h"

#include "Map\Map.h"
#include "Map\FieldObject\FieldObject.h"

extern cltCommonLogic* pclClient;


//---------------------------------------------------------
// �ǹ� ���� 
//---------------------------------------------------------
// Ư�� ���Կ� �ִ� �ǹ��� �����. 
void cltMapCommon::DeleteVillageStructure(SI32 slot)
{
	SI32 j;

	if( siVillageUnique < 0 || siVillageUnique >= MAX_VILLAGE_NUMBER )		return;
	SI32 strucureinfo	= pclClient->pclVillageManager->pclVillageInfo[siVillageUnique]->clVillageVary.clStructureInfo.Get(slot);

	SI32 strref = pclClient->pclVillageStructureSet->FindRefFromUnique(strucureinfo);
	if(strref >= 0)
	{
		if ( pclClient->pclVillageManager->pclVillageInfo[siVillageUnique]->bUpgradeSwitch && 
			pclClient->pclVillageStructureSet->pclVillageStructureInfo[strref]->siUPFieldObjectNumber > 0 )
		{
			for(j = 0;j < pclClient->pclVillageStructureSet->pclVillageStructureInfo[strref]->siUPFieldObjectNumber;j++)
			{
				SI32 x		= pclClient->pclMapManager->pclMapTypeManager->pclMapTypeInfo[siMapUnique]->StrLocation[slot].x + pclClient->pclVillageStructureSet->pclVillageStructureInfo[strref]->clUPUnit[j].siX;
				SI32 y		= pclClient->pclMapManager->pclMapTypeManager->pclMapTypeInfo[siMapUnique]->StrLocation[slot].y + pclClient->pclVillageStructureSet->pclVillageStructureInfo[strref]->clUPUnit[j].siY;

				DeleteFieldObject(x, y);
			}
		}
		else
		{
			for(j = 0;j < pclClient->pclVillageStructureSet->pclVillageStructureInfo[strref]->siFieldObjectNumber;j++)
			{
				SI32 x		= pclClient->pclMapManager->pclMapTypeManager->pclMapTypeInfo[siMapUnique]->StrLocation[slot].x + pclClient->pclVillageStructureSet->pclVillageStructureInfo[strref]->clUnit[j].siX;
				SI32 y		= pclClient->pclMapManager->pclMapTypeManager->pclMapTypeInfo[siMapUnique]->StrLocation[slot].y + pclClient->pclVillageStructureSet->pclVillageStructureInfo[strref]->clUnit[j].siY;

				DeleteFieldObject(x, y);
			}
		}
	}
}

// ������ �ǹ����� �����. 
void cltMapCommon::MakeVillageStructure()
{
	SI32 i, j;

	// �� Ÿ���� �������� �ʾҴٸ� ����. 
	if(siMapUnique <= 0)return ;
	if(siVillageUnique < 0 || siVillageUnique >= MAX_VILLAGE_NUMBER)		return;
	if(pclClient->pclVillageManager->pclVillageInfo[siVillageUnique] == NULL)return ;

	
	for(i = 0;i < MAX_CONSTRUCTION_NUM;i++)
	{
		SI32 strucureinfo	= pclClient->pclVillageManager->pclVillageInfo[siVillageUnique]->clVillageVary.clStructureInfo.Get(i);
		SI32 slot				=  i;
		
		// �������� ���ǵǾ� �ִٸ�, 
		if(strucureinfo == 0)continue;

		SI32 strref = pclClient->pclVillageStructureSet->FindRefFromUnique(strucureinfo);
		if(strref >= 0)
		{
			if ( pclClient->pclVillageManager->pclVillageInfo[siVillageUnique]->bUpgradeSwitch && 
				 pclClient->pclVillageStructureSet->pclVillageStructureInfo[strref]->siUPFieldObjectNumber > 0 )
			{
				for(j = 0;j < pclClient->pclVillageStructureSet->pclVillageStructureInfo[strref]->siUPFieldObjectNumber;j++)
				{
					SI32 unique = pclClient->pclVillageStructureSet->pclVillageStructureInfo[strref]->clUPUnit[j].siFieldObjectArray;
					SI32 x		= pclClient->pclMapManager->pclMapTypeManager->pclMapTypeInfo[siMapUnique]->StrLocation[slot].x + pclClient->pclVillageStructureSet->pclVillageStructureInfo[strref]->clUPUnit[j].siX;
					SI32 y		= pclClient->pclMapManager->pclMapTypeManager->pclMapTypeInfo[siMapUnique]->StrLocation[slot].y + pclClient->pclVillageStructureSet->pclVillageStructureInfo[strref]->clUPUnit[j].siY;

					PutFieldObject(x, y, unique);
				}
			}
			else
			{
				for(j = 0;j < pclClient->pclVillageStructureSet->pclVillageStructureInfo[strref]->siFieldObjectNumber;j++)
				{
					SI32 unique = pclClient->pclVillageStructureSet->pclVillageStructureInfo[strref]->clUnit[j].siFieldObjectArray;
					SI32 x		= pclClient->pclMapManager->pclMapTypeManager->pclMapTypeInfo[siMapUnique]->StrLocation[slot].x + pclClient->pclVillageStructureSet->pclVillageStructureInfo[strref]->clUnit[j].siX;
					SI32 y		= pclClient->pclMapManager->pclMapTypeManager->pclMapTypeInfo[siMapUnique]->StrLocation[slot].y + pclClient->pclVillageStructureSet->pclVillageStructureInfo[strref]->clUnit[j].siY;

					PutFieldObject(x, y, unique);
				}
			}
		}
	}
}

// ������ Ư�� ��ǥ�� �� �� �ǹ��� ���Կ� �ش��ϴ��� �˷��ش�. 
// ���ϰ� : -1 -> ������ �ƴ� ��
SI32 cltMapCommon::GetStructureSlot(SI32 villageunique, SI32 mapx, SI32 mapy)
{
	// �����ȿ� �ִ� ���� �ƴ϶�� ����. 
	if(villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER)	return -1;
	if(pclClient->pclMapManager->pclMapArray[villageunique] == NULL)return -1;

	SI32 maptypeunique = pclClient->pclMapManager->pclMapArray[villageunique]->siMapUnique;
	if( maptypeunique < 0 || maptypeunique >= MAX_MAPTYPE_NUMBER )	return -1;

	SI32 slot = -1;
	for(SI32 i = 0;i < MAX_CONSTRUCTION_NUM;i++)
	{
		if(mapx >= pclClient->pclMapManager->pclMapTypeManager->pclMapTypeInfo[maptypeunique]->StrLocation[i].x
		&& mapx < pclClient->pclMapManager->pclMapTypeManager->pclMapTypeInfo[maptypeunique]->StrLocation[i].x + 8
		&& mapy >= pclClient->pclMapManager->pclMapTypeManager->pclMapTypeInfo[maptypeunique]->StrLocation[i].y
		&& mapy < pclClient->pclMapManager->pclMapTypeManager->pclMapTypeInfo[maptypeunique]->StrLocation[i].y + 8)
		{
			slot = i;
		}

	}
	return slot;
}

// Ư�� ������ ���� ��ǥ�� �˷��ش�.
bool cltMapCommon::GetSlotStartPos(SI32 villageunique, SI32 slot, SI32* pstartx, SI32* pstarty)
{
	// �����ȿ� �ִ� ���� �ƴ϶�� ����. 
	if(villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER)	return false;
	if(pclClient->pclMapManager->pclMapArray[villageunique] == NULL)return false;

	SI32 maptypeunique = pclClient->pclMapManager->pclMapArray[villageunique]->siMapUnique;
	if( maptypeunique < 0 || maptypeunique >= MAX_MAPTYPE_NUMBER )	return false;

	if(slot < 0 || slot >= MAX_CONSTRUCTION_NUM)return false;

	*pstartx = pclClient->pclMapManager->pclMapTypeManager->pclMapTypeInfo[maptypeunique]->StrLocation[slot].x;
	*pstarty = pclClient->pclMapManager->pclMapTypeManager->pclMapTypeInfo[maptypeunique]->StrLocation[slot].y;

	return true;
}
