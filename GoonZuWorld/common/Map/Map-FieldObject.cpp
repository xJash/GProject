//---------------------------------
// 2003/5/17 ���°�
//---------------------------------
#include <CommonLogic.h>
#include "Map.h"
#include "Map\FieldObject\FieldObject.h"

// Field Object �귯�ø� ����ؼ� ����ش�. 
BOOL cltMapCommon::PutFieldObjectBrush(SI32 six, SI32 siy, SI32 brush)
{
	if(IsInMapArea(six, siy) == false)	return FALSE;
	if(pFieldObjectMap == NULL)			return FALSE;

	return PutFieldObject( six, siy, pclFieldObjectManager->pclFieldObjectBrush[brush]->GetRandUnique() );
}




// six, siy��ǥ�� �ִ� Field Object�� �����Ѵ�. 
BOOL cltMapCommon::DeleteFieldObject(SI32 six, SI32 siy)
{
	SI32 i, j;
	if(IsInMapArea(six, siy) == false)	return FALSE;
	if(pFieldObjectMap == NULL)			return FALSE;

	SI32 siunique = GetFieldObject_Unique(six , siy);

	if(siunique == 0)return FALSE;

	SI32 ref		= pclFieldObjectManager->FindRefFromUniqueMinus(siunique);
	if(ref < 0)return FALSE;

	SI32 tilexsize	= pclFieldObjectManager->pclInfo[ref]->TileXsize;
	SI32 tileysize	= pclFieldObjectManager->pclInfo[ref]->TileYsize;
	SI32 tilex		= six + GetFieldObjectLengthToRight(six, siy);
	SI32 tiley		= siy + GetFieldObjectLengthToBottom(six, siy);

	for(i = 0; i< tileysize;i++)
		for(j = 0;j < tilexsize ;j++)
		{
			SI32 x = tilex - tilexsize + 1 + j;
			SI32 y = tiley - tileysize + 1 + i;

			if(IsInMapArea(x, y) == true)
			{
				pFieldObjectMap[x + YOff[y]] = 0;
			}
		}

	return TRUE;
}

BOOL cltMapCommon::PutFieldObject(SI32 six, SI32 siy, TCHAR* name, SI32 para)
{
	SI32 siunique = pclFieldObjectManager->FindUniqueFromName(name);
	if(siunique == 0)
	{
		MsgBox(TEXT("f8rj33r"), TEXT("2984:%s"), name);
		return FALSE;
	}

	return PutFieldObject(six, siy, siunique, para);
}

BOOL cltMapCommon::PutFieldObject(SI32 six, SI32 siy, SI32 siunique, SI32 para)
{
	if(IsInMapArea(six, siy) == false)	return 0;
	if(pFieldObjectMap == NULL)			return 0;

	SI32 i, j;

	SI32 ref		= pclFieldObjectManager->FindRefFromUniqueMinus(siunique);
	if(ref < 0)return FALSE;

	// ��������� �� ������ �ϵ忡�� �о�´�.
	pclFieldObjectManager->pclInfo[ref]->LoadDetailInfo();

	SI32 tilexsize	= pclFieldObjectManager->pclInfo[ref]->TileXsize;
	SI32 tileysize	= pclFieldObjectManager->pclInfo[ref]->TileYsize;
	SI32 tilecenterx = pclFieldObjectManager->pclInfo[ref]->TileCenterX;
	SI32 tilecentery = pclFieldObjectManager->pclInfo[ref]->TileCenterY;

	//------------------------------------------------------------
	// Field Object ���� �ȿ� �ٸ� Field Object�� �ִ��� Ȯ���Ѵ�. 
	// �ٸ� ���� �ִٸ� ���ο� Field Object�� ���� �� ����. 
	//------------------------------------------------------------
	for(i = 0; i< tileysize;i++)
		for(j = 0;j < tilexsize ;j++)
		{
			SI32 x = six + j - tilexsize + 1 + tilecenterx ;
			SI32 y = siy + i - tileysize + 1 + tilecentery ;

			SI32 unique = GetFieldObject_Unique(x , y);
				
			if( unique )	return FALSE;
		}

	//-----------------------------------------------------------------
	// �ٸ� Field Object�� ���� ���¶�� �����ϴϱ� ���ο� ���� ��´�.
	//-----------------------------------------------------------------
	for(i = 0; i< tileysize;i++)
		for(j = 0;j < tilexsize ;j++)
		{
			SI32 x = six + tilecenterx - tilexsize + 1 + j;
			SI32 y = siy + tilecentery - tileysize + 1 + i;
			SetFieldObject_Unique(	x , y, siunique);

			// ��� ��ȿ�� �ʵ� ������Ʈ�� �Ķ��Ÿ �������� 
			// ����� �߽��� �Ǵ� �� �ϴ� ���� ��ǥ���� ������ ����Ѵ�.
			// �� ������ ��ġ�� ���� ���� �߽ɰ��� ��ǥ�� �ȴ�. 
			// ��� ��� �߽����� �ϴ� �ʵ� ������Ʈ������ ���� �Ǵ��� �� �ְ� ����� ���� 
			// �� �۾��� ��ǥ��. 
			SetFieldObjectLengthToBottom(x, y, tileysize - i - 1);
			SetFieldObjectLengthToRight(x, y,  tilexsize - j - 1); 

			SetFieldObjectPara(x, y, para);


			// �߽������� �ʵ� ������Ʈ�� ��ȿ�ϰ� ����� ����ġ�� ���ش�. 
			if(x == six && y == siy)
			{
				SetFieldObjectValidSwitch(x, y, TRUE);

				// �������� �־��ش�. 
				SetFieldObjectRandomValue(x, y, rand() % 16);
			}

		}

	

	return TRUE;
}

BOOL cltMapCommon::PutGateFieldObject(SI32 six, SI32 siy, SI32 siunique, SI32 para)
{
	if(IsInMapArea(six, siy) == false)	return 0;
	if(pFieldObjectMap == NULL)			return 0;

	SI32 i, j;

	SI32 ref		= pclFieldObjectManager->FindRefFromUniqueMinus(siunique);
	if(ref < 0)return FALSE;

	// ��������� �� ������ �ϵ忡�� �о�´�.
	pclFieldObjectManager->pclInfo[ref]->LoadDetailInfo();

	SI32 tilexsize	= pclFieldObjectManager->pclInfo[ref]->TileXsize;
	SI32 tileysize	= pclFieldObjectManager->pclInfo[ref]->TileYsize;
	SI32 tilecenterx = pclFieldObjectManager->pclInfo[ref]->TileCenterX;
	SI32 tilecentery = pclFieldObjectManager->pclInfo[ref]->TileCenterY;

	//------------------------------------------------------------
	// Field Object ���� �ȿ� �ٸ� Field Object�� �ִ��� Ȯ���Ѵ�. 
	// �ٸ� ���� �ִٸ� ���ο� Field Object�� ���� �� ����. 
	//------------------------------------------------------------
	for(i = 0; i< tileysize;i++)
	{
		for(j = 0;j < tilexsize ;j++)
		{
			SI32 x = six + j - tilexsize + 1 + tilecenterx ;
			SI32 y = siy + i - tileysize + 1 + tilecentery ;

			SI32 unique = GetFieldObject_Unique(x , y);

			// ��û�ѰͰ� �ٸ� ���� ���������� �ȵȴ�.
			if( unique > 0 && unique != siunique )	return FALSE;
		}
	}

	//-----------------------------------------------------------------
	// �ٸ� Field Object�� ���� ���¶�� �����ϴϱ� ���ο� ���� ��´�.
	//-----------------------------------------------------------------
	for(i = 0; i< tileysize;i++)
	{
		for(j = 0;j < tilexsize ;j++)
		{
			SI32 x = six + tilecenterx - tilexsize + 1 + j;
			SI32 y = siy + tilecentery - tileysize + 1 + i;
			SetFieldObject_Unique(	x , y, siunique);

			// ��� ��ȿ�� �ʵ� ������Ʈ�� �Ķ��Ÿ �������� 
			// ����� �߽��� �Ǵ� �� �ϴ� ���� ��ǥ���� ������ ����Ѵ�.
			// �� ������ ��ġ�� ���� ���� �߽ɰ��� ��ǥ�� �ȴ�. 
			// ��� ��� �߽����� �ϴ� �ʵ� ������Ʈ������ ���� �Ǵ��� �� �ְ� ����� ���� 
			// �� �۾��� ��ǥ��. 
			SetFieldObjectLengthToBottom(x, y, tileysize - i - 1);
			SetFieldObjectLengthToRight(x, y,  tilexsize - j - 1); 

			SetFieldObjectPara(x, y, para);

			// �߽������� �ʵ� ������Ʈ�� ��ȿ�ϰ� ����� ����ġ�� ���ش�. 
			if(x == six && y == siy)
			{
				SetFieldObjectValidSwitch(x, y, TRUE);

				// �������� �־��ش�. 
				SetFieldObjectRandomValue(x, y, rand() % 16);
			}

		}
	}

	return TRUE;
}

BOOL cltMapCommon::SetFieldObject_Unique(SI32 six, SI32 siy, SI32 siunique)
{
	if(IsInMapArea(six, siy) == false) return FALSE;
	if(pFieldObjectMap == NULL)return FALSE;

	uFieldObjectUnion fUnion;

	fUnion.Data32 = pFieldObjectMap[six + YOff[siy]];

	fUnion.FieldObject_Normal.SetFieldUnique(siunique);
	pFieldObjectMap[six + YOff[siy]]	= fUnion.Data32;

	return TRUE;
}

SI32 cltMapCommon::GetFieldObject_Unique(SI32 six, SI32 siy)
{
	if(IsInMapArea(six, siy) == false) return 0;
	if(pFieldObjectMap == NULL)return 0;

	uFieldObjectUnion fUnion;

	fUnion.Data32 = pFieldObjectMap[six + YOff[siy]];


	return fUnion.FieldObject_Normal.GetFieldUnique();
}


BOOL cltMapCommon::SetFieldObjectPara(SI32 six, SI32 siy, SI32 para)
{
	if(IsInMapArea(six, siy) == false) return FALSE;
	if(pFieldObjectMapPara == NULL)return FALSE;


	pFieldObjectMapPara[six + YOff[siy]] = para;

	return TRUE;
}

SI32 cltMapCommon::GetFieldObjectPara(SI32 six, SI32 siy)
{
	if(IsInMapArea(six, siy) == false) return 0;
	if(pFieldObjectMapPara == NULL)return 0;

	return pFieldObjectMapPara[six + YOff[siy]];
}

// ����� �ص� �Ǵ� ��ȿ�� �ʵ� ������Ʈ�ΰ� ���� ������Ʈ�ΰ� �˻��Ѵ�. 
BOOL cltMapCommon::GetFieldObjectValidSwitch(SI32 six, SI32 siy)
{
	if(IsInMapArea(six, siy) == false) return 0;
	if(pFieldObjectMap == NULL)return 0;

	uFieldObjectUnion fUnion;

	fUnion.Data32 = pFieldObjectMap[six + YOff[siy]];

	if(fUnion.FieldObject_Normal.GetValidSwitch())return TRUE;

	return FALSE;
}

// �ʵ� ������Ʈ�� ��� ��ȿ�ϰ� �ϰų� ��ȿ�ϰ� �Ѵ�. 
void cltMapCommon::SetFieldObjectValidSwitch(SI32 six, SI32 siy, BOOL bmode)
{
	if(IsInMapArea(six, siy) == false) return ;
	if(pFieldObjectMap == NULL)return ;

	uFieldObjectUnion fUnion;

	fUnion.Data32 = pFieldObjectMap[six + YOff[siy]];

	if(bmode == TRUE)
	{
		fUnion.FieldObject_Normal.SetValidSwitch(1);
		pFieldObjectMap[six + YOff[siy]] = fUnion.Data32;
	}
	else
	{
		fUnion.FieldObject_Normal.SetValidSwitch(0);
		pFieldObjectMap[six + YOff[siy]] = fUnion.Data32;
	}
}


void cltMapCommon::SetFieldObjectRandomValue(SI32 six, SI32 siy, BOOL value)
{
	if(IsInMapArea(six, siy) == false) return ;
	if(pFieldObjectMap == NULL)return ;

	uFieldObjectUnion fUnion;

	fUnion.Data32 = pFieldObjectMap[six + YOff[siy]];

	fUnion.FieldObject_Normal.SetRandomValue(value);
	pFieldObjectMap[six + YOff[siy]] = fUnion.Data32;
}

UI32 cltMapCommon::GetFieldObjectRandomValue(SI32 six, SI32 siy)
{
	if(IsInMapArea(six, siy) == false)	return 0;
	if(pFieldObjectMap == NULL)			return 0;

	uFieldObjectUnion fUnion;

	fUnion.Data32 = pFieldObjectMap[six + YOff[siy]];

	return fUnion.FieldObject_Normal.GetRandomValue(); 
}

void cltMapCommon::SetFieldObjectLengthToBottom(SI32 six, SI32 siy, SI32 length)
{
	if(IsInMapArea(six, siy) == false) return ;
	if(pFieldObjectMap == NULL)return ;

	uFieldObjectUnion fUnion;

	fUnion.Data32 = pFieldObjectMap[six + YOff[siy]];

	fUnion.FieldObject_Normal.SetLengthToBottom(length);
	pFieldObjectMap[six + YOff[siy]] = fUnion.Data32;

}

UI32 cltMapCommon::GetFieldObjectLengthToBottom(SI32 six, SI32 siy)
{
	if(IsInMapArea(six, siy) == false)	return 0;
	if(pFieldObjectMap == NULL)			return 0;

	uFieldObjectUnion fUnion;

	fUnion.Data32 = pFieldObjectMap[six + YOff[siy]];

	return fUnion.FieldObject_Normal.GetLengthToBottom();
}


void cltMapCommon::SetFieldObjectLengthToRight(SI32 six, SI32 siy, SI32 length)
{
	if(IsInMapArea(six, siy) == false) return ;
	if(pFieldObjectMap == NULL)return ;

	uFieldObjectUnion fUnion;

	fUnion.Data32 = pFieldObjectMap[six + YOff[siy]];

	fUnion.FieldObject_Normal.SetLengthToRight(length);
	pFieldObjectMap[six + YOff[siy]] = fUnion.Data32;

}

UI32 cltMapCommon::GetFieldObjectLengthToRight(SI32 six, SI32 siy)
{
	if(IsInMapArea(six, siy) == false)	return 0;
	if(pFieldObjectMap == NULL)			return 0;

	uFieldObjectUnion fUnion;

	fUnion.Data32 = pFieldObjectMap[six + YOff[siy]];

	return fUnion.FieldObject_Normal.GetLengthToRight();
}

// six, siy������ �ִ� Field Object�� �߽� ��ġ�� ���ؼ� �����Ѵ�. 
bool cltMapCommon::GetFieldObjectCenterPos(SI32 six, SI32 siy, SI32* pcenterx, SI32* pcentery)
{
	// �켱 �ش� ��ġ�� FieldObject�� �־�� �Ѵ�. 
	SI32 siunique = GetFieldObject_Unique(six, siy);
	if(siunique == 0)return false;

	SI32 ref		= pclFieldObjectManager->FindRefFromUniqueMinus(siunique);
	if(ref < 0)return false;

	SI32 tilecenterx = pclFieldObjectManager->pclInfo[ref]->TileCenterX;
	SI32 tilecentery = pclFieldObjectManager->pclInfo[ref]->TileCenterY;

	*pcenterx = six - tilecenterx + GetFieldObjectLengthToRight(six, siy);
	*pcentery = siy - tilecentery + GetFieldObjectLengthToBottom(six, siy);

	return true;
}

// ������ ���Ӱ� Field Object�� ��ġ�Ѵ�. 
void cltMapCommon::NewFieldObjectSetInMap()
{
	SI32 i, j;

	// ������ ������ ������ ���ο� ������ �����. 
	SI32* pFOMap = new SI32[MH.MapXsize * MH.MapYsize];

	ZeroMemory(pFOMap, sizeof(SI32) * MH.MapXsize * MH.MapYsize);

	// ���� �Ҵ��� ������ ���� ������ ����Ѵ�. 
	for(i = 0;i < MH.MapYsize;i++)
		for(j = 0;j < MH.MapXsize;j++)
		{
			if(GetFieldObject_Unique(j, i))
			{
				if(GetFieldObjectValidSwitch(j, i))
				{
					pFOMap[j + i*MH.MapXsize] = GetFieldObject_Unique(j, i);
				}
			}
		}


	// ������ FieldObject������ �ʱ�ȭ�Ѵ�.
	for(i = 0;i < MH.MapYsize;i++)
		for(j = 0;j < MH.MapXsize;j++)
		{
			pFieldObjectMap[j + i*MH.MapXsize]		= 0;
			pFieldObjectMapPara[j + i*MH.MapXsize]	= 0;
		}
	
	// ����� ������ ������  FieldObject�� �� �����Ѵ�. 
	for(i = 0;i < MH.MapYsize;i++)
		for(j = 0;j < MH.MapXsize;j++)
		{
			if(pFOMap[j + i*MH.MapXsize])
			{
				PutFieldObject(j, i, pFOMap[j + i*MH.MapXsize]);
			}
		}

	// ���Ӱ� �Ҵ��� ������ �����.
	if(pFOMap)
	{
		delete[] pFOMap;
		pFOMap = NULL;
	}

}
void cltMapCommon::DeleteFieldObjectUnique(SI32 siUnique)
{
	SI32 i, j;

	SI32 siDeletedUnique = 0;

	for(i = 0;i < MH.MapYsize;i++)
	{
		for(j = 0;j < MH.MapXsize;j++)
		{
			SI32 unique = GetFieldObject_Unique(j, i);
			if(unique == 0)continue;

			SI32 ref	= pclFieldObjectManager->FindRefFromUniqueMinus(unique);
			if(ref < 0)continue ;

			if ( pclFieldObjectManager->pclInfo[ref]->Unique == siUnique )
            {
				DeleteFieldObject(j, i);
				siDeletedUnique++;
			}
            
		}
	}
	TCHAR buffer[256];
	StringCchPrintf( buffer, 256, "%d���� ������Ʈ�� �����Ǿ����ϴ�", siDeletedUnique);
	MessageBox( NULL, buffer, TEXT("�����Ϸ�"), MB_OK|MB_TOPMOST );

}