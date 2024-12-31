#include "..\Client\Client.h"
#include "Char\CharServer\Char-Server.h"

#include "..\CharManager\CharManager.h"
#include "..\..\Map\Map.h"
#include "..\..\Order\Order.h"
#include "..\..\Util\Util.h"

extern cltCommonLogic* pclClient;

//-----------------------------------------------------------------------------
//  �� �ڸ� ã�� �Լ� 
//-----------------------------------------------------------------------------
// ���ڸ��� ã�� x, y�� �־� �ش�.
BOOL cltCharServer::FindEmptyArea(SHORT& x, SHORT &y)
{
   int i, j;
   SHORT tempx, tempy;

	  for(i=-1;i<=1;i++)
		 for(j=-1;j<=1;j++)
		 {
			 if(j==-1 || j==1 || i==-1 || i==1)
			 {
				 tempx=GetX()+j;
				 tempy=GetY()+i;

				 // ĳ���͸� ��ġ�� �� �ִ� ������ �ִ� �������� Ȯ���Ѵ�. 
			     if(pclMap->IsInMapArea(tempx, tempy) == true
				 && pclMap->IsEmpty(tempx, tempy))
				{
				   x=tempx;
				   y=tempy;
				   return TRUE;
				}
			 }
		 }
   return FALSE;
}

BOOL cltCharServer::FindEmptyArea(SHORT& x, SHORT &y, SHORT xsize, SHORT ysize)
{
   SHORT i, j;
   int length, min_length=10000;
   SHORT min_x = 0, min_y = 0;
   SHORT tempx, tempy;
   BOOL skipswitch ;

	  for(i=-4;i<=4;i++)
		  for(j=-4;j<=4;j++)
		  {
			  tempx=GetX()+j;
			  tempy=GetY()+i;
			  skipswitch = FALSE;
			  
			  // ĳ���͸� ��ġ�� �� �ִ� ������ �ִ� �������� Ȯ���Ѵ�. 
			  if(pclMap->IsEmpty(tempx, tempy, xsize, ysize, GetX(), GetY())==TRUE)
			  {
				  
				  if(skipswitch == FALSE)
				  {
					  length=(tempx-GetX())*(tempx-GetX())+(tempy-GetY())*(tempy-GetY());
					  
					  if(length < min_length)
					  {
						  min_x=tempx;
						  min_y=tempy;
						  min_length=length;
					  }
				  }
			  }
		  }

		 // ���ڸ��� ������, 
		 if(min_length==10000)
		 {
			 return FALSE;
		 }
		 else  // ���ڸ��� ������, 
		 {
			 x=min_x; y=min_y;
			 return TRUE;
		 }

   //return FALSE;
}



//------------------------------------------------------------------------------
// �ΰ����� ����. 
//-----------------------------------------------------------------------------


// ���� �� �غ� �Ǿ� �ִ°�?
BOOL cltCharServer::CanWork()
{

   return TRUE;
}


// ���� ���� ��ó 
bool cltCharServer::FindEnemyAction(SI32 id)
{
	
	if(pclCM->IsAlive(id) == FALSE)return false;


	if(CanAttack(id) == TRUE)
	{
		OrderAttack(siID, id, BY_COMPUTER);
		return true;
	}
 
	return false;
}


// Ư�� �������� ĳ���͸� �о��. 
BOOL cltCharServer::Pull(SI32 dir)
{

	SI32 x = 0, y = 0;

	switch(dir)
	{
	case SOUTH:			x = GetX() ;  y = GetY()+1;	break;
	case SOUTH|WEST:	x = GetX()-1; y = GetY()+1;	break;
	case WEST:			x = GetX()-1; y = GetY();		break;
	case WEST|NORTH:    x = GetX()-1; y = GetY()-1;	break;
	case NORTH:         x = GetX() ;  y = GetY()-1;	break;
	case NORTH|EAST:    x = GetX()+1; y = GetY()-1;	break;
	case EAST:          x = GetX()+1; y = GetY();		break;
	case EAST|SOUTH:    x = GetX()+1; y = GetY()+1;	break;
	default:
		MsgBox(TEXT("CharPull"), TEXT("kind:%d dir:%d"), GetKind(), dir);
	}

	// �̵������� ��� �ִٸ�,
	if(IsColl(x, y, Block) == false)
	{
		SetX(x);
		SetY(y);
	}

	return TRUE;
}




