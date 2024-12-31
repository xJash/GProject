//---------------------------------
// 2005/3/14 ���°�
//---------------------------------

#include "Map\map.h"

#include "Client.h"

#define MAX_FOG_CHILD_NUM	9
#define MAX_FOG_NODE_NUM	200
class cltFogNode{
public:
	SI32 siX, siY;
	SI32 siChild[MAX_FOG_CHILD_NUM];
	SI32 siChildNum;

	cltFogNode()
	{
		siChildNum = 0;
		siX	= 0;
		siY	= 0;
	}
	void AddChild(SI32 index);
};

cltFogNode clSideFogNode[MAX_FOG_NODE_NUM];
SI32 siSideFogNodeNum	= 0;

cltFogNode clFogNode[MAX_FOG_NODE_NUM];
SI32 siFogNodeNum	= 0;

void cltFogNode::AddChild(SI32 childindex)
{
	SI32 i;

	// �ڽ��� �ڽ��� �ڽ����� ��� �Ұ�. 
	if(clFogNode[childindex].siX == siX && clFogNode[childindex].siY == siY)return ;


	// ������ �ڽĿ��� �˻��ؼ� �ߺ��ϴ� ���� ����� �Ѵ�. 
	for(i = 0;i < siChildNum;i++)
	{
		if(clFogNode[ siChild[i] ].siX == clFogNode[childindex].siX 
			&& clFogNode[ siChild[i] ].siY == clFogNode[childindex].siY)return ;
	}

	siChild[siChildNum] = childindex;
	siChildNum++;
	if(siChildNum > MAX_FOG_CHILD_NUM)
	{
		MsgBox(TEXT("cd3dsfsd"), TEXT("F3sdfsd"));
		SI32 a = 0;
	}

}

// ������ ��ϵǾ� �ִ� ���̵� ������� Ȯ���Ѵ�. 
bool IsSideFogNode(SI32 x, SI32 y, SI32* pindex)
{
	for(SI32 i = 0;i < siSideFogNodeNum;i++)
	{
		if(clSideFogNode[i].siX == x && clSideFogNode[i].siY == y)
		{
			*pindex = i;
			return true;
		}
	}
	return false;
}

void AddSideFogNode(SI32 x, SI32 y)
{
	// ������ ��ϵǾ� �ִ� ������� Ȯ���Ѵ�. 
	SI32 index;
	if(IsSideFogNode(x, y, &index))return ;

	clSideFogNode[siSideFogNodeNum].siX = x;
	clSideFogNode[siSideFogNodeNum].siY = y;
	siSideFogNodeNum++;
}


bool MakeFogNode(SI32 x, SI32 y, SI32* pindex)
{
	SI32 i;

	// ������ ��忡�� ã�ƺ���. 
	for(i = 0;i < siFogNodeNum;i++)
	{
		if(clFogNode[i].siX == x && clFogNode[i].siY == y)
		{
			*pindex = i;
			return true;
		}
	}

	// ������ ���ٸ� ���� �����. 
	clFogNode[siFogNodeNum].siX = x;
	clFogNode[siFogNodeNum].siY	= y;
	siFogNodeNum++;
	if(siFogNodeNum > MAX_FOG_NODE_NUM)
	{
		MsgBox(TEXT("v34sdf"), TEXT("fsdfqfds"));
	}

	*pindex = (siFogNodeNum-1);

	return true;
}
void AddChildNode(SI32 parentx, SI32 parenty, SI32 childx, SI32 childy)
{
	SI32 index, childindex;
	// �θ��带 ã�´�. 
	if(MakeFogNode(parentx, parenty, &index))
	{
		// �ڽ� ��带 ã�´�. 
		if(MakeFogNode(childx, childy, &childindex))
		{
			clFogNode[index].AddChild(childindex);
		}
		else
		{
			MsgBox(TEXT("fd3sdfS"), TEXT("F3dsfdsf"));
		}
	}
	else
	{
		MsgBox(TEXT("fd3sd22fS"), TEXT("F3dsfdsf"));
	}


}

void FogOp(cltMapClient* pclmap, SI32 index, SI32 charx, SI32 chary)
{
	SI32 i;

	SI32 x = clFogNode[index].siX;
	SI32 y = clFogNode[index].siY;


	pclmap->PutFog(charx + x , chary + y, FOG_NONE);
		
	// ���׸� ���ܾ� �� ���� �浹�����̶�� ����. 
	if(pclmap->IsColl(charx + x , chary + y, BLOCK_NORMAL) )return ;

	// �ڽ� ��尡 �ִٸ�, 
	for(i = 0;i < clFogNode[index].siChildNum;i++)
	{
		FogOp(pclmap, clFogNode[index].siChild[i], charx, chary);
	}
}

void cltClient::InitFogNode()
{

	SI32 i, j;
	SI32 range = 6;

	// �������κ��� �Ÿ��� 4�� ��ǥ�� ����Ʈ�� �߰��Ѵ�. 
	for(i = -range;i <= range;i++)
		for(j = -range;j <=range;j++)
		{
			double length = sqrt( double(i*i + j*j) );
			if((range-0.5) <= length && length < (range + 1.0) )
			{
				AddSideFogNode(j, i);
			}
		};
	SI32 a = 0;



	// �������� ���̵� �������� ���� ��θ� ã�� �ڽ� ���踦 ��Ͻ�Ų��. 
	for(i = 0; i< siSideFogNodeNum;i++)
	{
		SI32 x1 = 0;
		SI32 y1 = 0;
		SI32 x2	= clSideFogNode[i].siX;
		SI32 y2	= clSideFogNode[i].siY;

		SI32 PrevX = 0;
		SI32 PrevY = 0;


		SI32 index = 0;
		int t, distance;
		int xerr=0, yerr=0, delta_x, delta_y;
		int incx, incy;

		// X, Y������ ������ ���
		delta_x=x2-x1;
		delta_y=y2-y1;

		// ������ ������ ���� -0�� ������ �Ǵ� ������ �ǹ� 
		if(delta_x>0)       incx=1;
		else if(delta_x==0) incx=0;
		else                incx=-1;

		if(delta_y>0)       incy=1;
		else if(delta_y==0) incy=0;
		else                incy=-1;

		// ��� ������ ������ �� ū�� ����
		delta_x=TABS(delta_x);
		delta_y=TABS(delta_y);
		if(delta_x > delta_y)distance=delta_x;
		else distance=delta_y;

		// ���� �׸���. 
		for(t=0;t<=distance+1;t++)
		{

			AddChildNode(PrevX, PrevY, x1, y1);

			PrevX = x1;
			PrevY = y1;

			xerr+=delta_x;
			yerr+=delta_y;
			if(xerr>distance)
			{
				xerr-=distance;
				x1+=incx;
			}
			if(yerr>distance)
			{
				yerr-=distance;
				y1+=incy;
			}
		}

	};

	for(i = 0;i < siFogNodeNum;i++)
	{
		TCHAR buffer[256];
		StringCchPrintf(buffer, 256, TEXT("%2d. (X:%2d Y:%2d), (Child: %2d %2d %2d %2d %2d %2d %2d %2d %2d)"), 
			i, clFogNode[i].siX, clFogNode[i].siY, 
			clFogNode[i].siChild[0],
			clFogNode[i].siChild[1],
			clFogNode[i].siChild[2],
			clFogNode[i].siChild[3],
			clFogNode[i].siChild[4],
			clFogNode[i].siChild[5],
			clFogNode[i].siChild[6],
			clFogNode[i].siChild[7],
			clFogNode[i].siChild[8]);

		if (pclClient->GameMode == GAMEMODE_SERVER)
			pclLog->FilePrint(TEXT("Config\\FogNode.log"), TEXT("%s"), buffer);
	}
}


