//---------------------------------
// 2003/10/22 ���°�
//---------------------------------

#include "..\Client\Client.h"


#include "..\..\..\Lib\AStar\AStarListMgr.h"
#include "..\..\Util\Util.h"
#include "..\..\Order\Order.h"

extern cltCommonLogic* pclClient;

//---------------------------------
// ĳ���͸� �̵��ϰ� ����� ���� ������ �Ѵ�. 
//---------------------------------
bool cltCharCommon::SetMove(SI32 dx, SI32 dy)
{
	if(dx <  0)						dx	=	0;
	if(dx >= pclMap->MH.MapXsize)	dx	=	pclMap->MH.MapXsize - 1;
    if(dy < 0)						dy	=	0;
 	if(dy >= pclMap->MH.MapYsize)	dy	=	pclMap->MH.MapYsize - 1;

	clMoveInfo.siDX=dx; 
	clMoveInfo.siDY=dy;

	// �̵� ��� �ʱ�ȭ. 
	clMovePointList.Init();
	
	//clMoveInfo.dwLastMoveClock = pclClient->CurrentClock;

	return TRUE;
}

//------------------------------------------
// ĳ���͸� �̵��ϰ� �����.
//------------------------------------------
int cltCharCommon::Move(bool bstraightswitch)
{
	int x = GetX(), y= GetY();
	int direction;
	SI32 aniindex = 0;

	// �̵� �Ӽ��� �ƴϸ� �̵����� �ʴ´�. 
	if(IsAtb(ATB_MOVE)==FALSE)	return MOVERTNVAL_MOVEDONE;

	if(clMoveInfo.siMovePercent == 0)
	{
		bool findpathswitch = false;
		
		// ������ ���� ���� �����̸� ���� ã�´�. 
		if(clMovePointList.siPointNum == 0)
		{
			findpathswitch = true;
		}
		
		if(findpathswitch == true)
		{
			// �̵� ��θ� ã�� ���� �ʱ�ȭ�Ѵ�. 
			clMovePointList.Init();

			pclMap->MoveID	= siID;
		
			
			SI32 num	= MAX_CHAR_MOVE_POINT;
			BOOL ret;

			if ( GetCharUnique() < 1000 )
			{
				int a = 0;
			}
			
			if(pclMap->pclPath)
			{
				ret = pclMap->pclPath->FindNextPath( bstraightswitch, GetX(), GetY(), clMoveInfo.siDX, clMoveInfo.siDY, &clMovePointList.clPos[0], &num );
			}
			else
			{
				return MOVERTNVAL_MOVEDONE;
			}

			clMovePointList.siPointNum = num;

			// ���� �̵����� ���ϸ� �̵��� �ߴ��Ѵ�.
			if(clMovePointList.siPointNum == 0)return MOVERTNVAL_MOVEDONE;
			else if(clMovePointList.clPos[clMovePointList.siPointNum-1 ].siX == GetX() && clMovePointList.clPos[clMovePointList.siPointNum-1].siY == GetY())
			{
				return MOVERTNVAL_MOVEDONE;
			}
			
			if(TABS(clMovePointList.clPos[clMovePointList.siPointNum-1 ].siX - GetX()) > 1
			|| TABS(clMovePointList.clPos[clMovePointList.siPointNum-1 ].siY - GetY()) > 1 )
			{
				return MOVERTNVAL_MOVEDONE;
			}
		}
	}
	
	// �̵� ������ �ʱ�ȭ�Ѵ�. 
	direction	=	0;
	
	//---------------------------------------
	// �̵��� ��ġ�� ã�´�. 
	//---------------------------------------
	clMoveInfo.siNX	=	GetX();
	clMoveInfo.siNY	=	GetY();
	if(GetX() < clMovePointList.clPos[clMovePointList.siPointNum-1].siX)
	{
		clMoveInfo.siNX++;
		direction|=EAST;
	}
	else if(GetX() > clMovePointList.clPos[clMovePointList.siPointNum-1].siX)
	{
		clMoveInfo.siNX--;
		direction|=WEST;
	}
	if(GetY() < clMovePointList.clPos[clMovePointList.siPointNum-1].siY)
	{
		clMoveInfo.siNY++;
		direction|=SOUTH;
	}
	else if(GetY() > clMovePointList.clPos[clMovePointList.siPointNum-1].siY)
	{
		clMoveInfo.siNY--;
		direction|=NORTH;
	}

	//---------------------------------------
	// ������ ��ȯ�Ѵ�. 
	//---------------------------------------
	if(direction)
	{
		if(ChangeDirection(direction)==FALSE)return MOVERTNVAL_MOVING;
	}
	

	//-------------------------------
	// �̵� �ӵ��� ���Ѵ�. 
	//-------------------------------
	SI32 movespeed = clPB.GetTotalMoveSpeed();
	
	//--------------------------------
	// ���� %�� �̵���Ų��. 
	//-------------------------------
	DWORD lastmovedelay	= min((CHAR_ACTION_INTERVAL_FRAME+1)*50, (pclClient->CurrentClock - clMoveInfo.dwLastMoveClock));
	
	// Ŭ���̾�Ʈ������ ���۽��� �̵��� ����� �Ѵ�. 
	if(pclClient->GameMode == GAMEMODE_CLIENT)
	{
		lastmovedelay = min(100, lastmovedelay);
	}

	clMoveInfo.dwLastMoveClock		= 	pclClient->CurrentClock;
	SI32 movedlength = movespeed * lastmovedelay / 50;

	movedlength += min(100, clMoveInfo.siSparePercent);
	clMoveInfo.siSparePercent = 0;
	
	if(clMoveInfo.IncMovePercent(movedlength) >= 50)
	{
		// �̵��� ������ �浹�����̾�� �ȵȴ�. 
		if(IsColl(clMoveInfo.siNX, clMoveInfo.siNY, Block) == false )
		{
			clMoveInfo.siMovePercent = clMoveInfo.siMovePercent-100;
			
			// �̵��� ������ �����.
			SetMoveStandardPos(GetX(), GetY(), clMoveInfo.siNX, clMoveInfo.siNY);
			
			// ĳ������ ��ġ�� �����Ѵ�. 
			SetX(clMoveInfo.siNX);
			SetY(clMoveInfo.siNY);

			if (pclClient->pclMapManager->IsFogMap(GetMapIndex()) )
			{
				FogAction();
			}

			SetUpdateSwitch(UPDATE_BASICINFO, true, 0);
			
			
			// �̿��� ������Ʈ �Ѵ�. 
			SetNeighbour();
		}
		else
		{
			// ���� �ٽ� ã�� �����. 
			clMovePointList.siPointNum	= 0;
			clMoveInfo.siMovePercent	= 0;
		}
	}
	// ��ǥ ��ȯ�� ������ �� ������, 
	else if(clMoveInfo.siMovePercent <= 0)
	{
	}
	else
	{
		// �̵��� ������ �����.
		SetMoveStandardPos(GetX(), GetY(), clMoveInfo.siNX, clMoveInfo.siNY);
	}
	
	// RX, RY�� ����Ѵ�.(Ŭ���̾�Ʈ������. ) 
	CalculateRXY();

	SetAnimation(ANITYPE_MOVE);
	DoAnimationDelay();
	
	// �߰���ǥ���� �̻���� ����
	if(clMoveInfo.siMovePercent == 0)
	{
		// ���� ������ ���� 
		if(clMoveInfo.siDX == GetX() && clMoveInfo.siDY == GetY())
		{
			return MOVERTNVAL_MOVEDONE;
		}
		// �߰� ������ ���� 
		if(clMovePointList.IsArrive(GetX(), GetY()))
		{
			// ����ó��. 
			clMovePointList.Arrive();

			return MOVERTNVAL_HALFDONE;
		}
	}
	
	return MOVERTNVAL_MOVING;

}

BOOL cltCharCommon::MoveDone()
{
	if(clMoveInfo.siMovePercent)return FALSE;
	return TRUE;
}

BOOL cltCharCommon::CanMoveTo(SI32 x, SI32 y)
{
	// ���� ������ ����ٸ� FALSE
	if(pclMap->IsInMapArea(x, y) == false)return FALSE;

	return TRUE;
}

// ���� ������ Ư�� ��ǥ�� �̵���Ų��. 
BOOL cltCharCommon::MoveTo(SI32 x, SI32 y)
{
	// ���� ������ ����ٸ� FALSE
	if(pclMap->IsInMapArea(x, y) == false)return FALSE;

	DeleteID();
	
	SetX(x);
	SetY(y);
	
	SetID();

	return FALSE;

}

// ĳ���Ͱ� x, y��ġ�� ���� �� �ִ°� ���°�?
bool cltCharCommon::IsColl(SHORT x, SHORT y)
{
	return pclMap->IsColl(x, y, Block);
}

// ĳ���Ͱ� x, y��ġ�� �� ���� �� �ִ°� ���°�?
bool cltCharCommon::IsColl(SHORT x, SHORT y, SHORT block)
{
	if(pclMap->IsColl(x, y, block))
	{
		return true;
	}
	return false;	
}


// �浹 ������ �����Ѵ�. 
bool cltCharCommon::SetBlock()
{
	bool bchanged = false;

	//------------------------------------
	// �̺�Ʈ 1
	//------------------------------------
	if(pclClient->bEventSwitch[1] == true)
	{
		if((Block & BLOCK_EVENT1) == 0)
		{
			Block |= BLOCK_EVENT1;
			bchanged = true;
		}
	}
	else
	{
		if(Block & BLOCK_EVENT1)
		{
			Block -= BLOCK_EVENT1;
		}
	}


	if(clInnerStatus.clEventInfo.bEvent1Switch)
	{
		if(Block & BLOCK_EVENT1)
		{
			Block -= BLOCK_EVENT1;
		}
	}

	//------------------------------------
	// �̺�Ʈ 2
	//------------------------------------
	if(pclClient->bEventSwitch[2] == true)
	{
		if((Block & BLOCK_EVENT2) == 0)
		{
			// �̺�Ʈ�� ���ʹ� Event2������ �󸶵��� �� �� �ִ�. 
			if(pclKI->IsAtb(ATB_EVENTXBOX) == false)
			{
				Block |= BLOCK_EVENT2;
				bchanged = true;
			}
		}
	}
	else
	{
		if(Block & BLOCK_EVENT2)
		{
			Block -= BLOCK_EVENT2;
		}
	}


	if(clInnerStatus.clEventInfo.bEvent2Switch)
	{
		if(Block & BLOCK_EVENT2)
		{
			Block -= BLOCK_EVENT2;
		}
	}
	
	//------------------------------------
	// �̺�Ʈ 3
	//------------------------------------
	if(pclClient->bEventSwitch[3] == true)
	{
		if((Block & BLOCK_EVENT3) == 0)
		{
			Block |= BLOCK_EVENT3;
			bchanged = true;
		}
	}
	else
	{
		if(Block & BLOCK_EVENT3)
		{
			Block -= BLOCK_EVENT3;
		}
	}

	if(clInnerStatus.clEventInfo.bEvent3Switch)
	{
		if(Block & BLOCK_EVENT3)
		{
			Block -= BLOCK_EVENT3;
		}
	}

	//------------------------------------
	// �̺�Ʈ 4
	//------------------------------------
	if(pclClient->bEventSwitch[4] == true)
	{
		if((Block & BLOCK_EVENT4) == 0)
		{
			Block |= BLOCK_EVENT4;
			bchanged = true;
		}
	}
	else
	{
		if(Block & BLOCK_EVENT4)
		{
			Block -= BLOCK_EVENT4;
		}
	}

	if(clInnerStatus.clEventInfo.bEvent4Switch)
	{
		if(Block & BLOCK_EVENT4)
		{
			Block -= BLOCK_EVENT4;
		}
	}

	//------------------------------------
	// �̺�Ʈ 5
	//------------------------------------
	if(pclClient->bEventSwitch[5] == true)
	{
		if((Block & BLOCK_EVENT5) == 0)
		{
			Block |= BLOCK_EVENT5;
			bchanged = true;
		}
	}
	else
	{
		if(Block & BLOCK_EVENT5)
		{
			Block -= BLOCK_EVENT5;
		}
	}

	if(clInnerStatus.clEventInfo.bEvent5Switch)
	{
		if(Block & BLOCK_EVENT5)
		{
			Block -= BLOCK_EVENT5;
		}
	}

	//------------------------------------
	// �̺�Ʈ 6
	//------------------------------------
	if(pclClient->bEventSwitch[6] == true)
	{
		if((Block & BLOCK_EVENT6) == 0)
		{
			Block |= BLOCK_EVENT6;
			bchanged = true;
		}
	}
	else
	{
		if(Block & BLOCK_EVENT6)
		{
			Block -= BLOCK_EVENT6;
		}
	}

	if(clInnerStatus.clEventInfo.bEvent6Switch)
	{
		if(Block & BLOCK_EVENT6)
		{
			Block -= BLOCK_EVENT6;
		}
	}

	//------------------------------------
	// �̺�Ʈ 7
	//------------------------------------
	if(pclClient->bEventSwitch[7] == true)
	{
		if((Block & BLOCK_EVENT7) == 0)
		{
			Block |= BLOCK_EVENT7;
			bchanged = true;
		}
	}
	else
	{
		if(Block & BLOCK_EVENT7)
		{
			Block -= BLOCK_EVENT7;
		}
	}

	if(clInnerStatus.clEventInfo.bEvent7Switch)
	{
		if(Block & BLOCK_EVENT7)
		{
			Block -= BLOCK_EVENT7;
		}
	}

	if(pclClient->GameMode == GAMEMODE_SERVER && bchanged)
	{
		// ���ڿ� Ÿ�� �����ʰ� �浹�ϴ� �����̶��, 
		if( IsColl(GetX(), GetY()) == true)
		{
			OrderStop(GetID(), BY_COMPUTER);

			cltWarpInfo clWarpInfo(1, GetMapIndex(), false, false, GetX(), GetY(), -1, -1);
			SetWarpInfo(&clWarpInfo, 20);
			Warp();
		}
	}


	return true;
}