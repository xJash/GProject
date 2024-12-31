#include "..\Client\Client.h"
#include "..\Server\Server.h"

#include "bullet.h"
#include "..\Smoke\Smoke.h"
#include "Util\Util.h"
#include "Char\CharManager\CharManager.h"

extern cltCommonLogic* pclClient;
extern UI08 SqrtVary[];

//-------------------------------------------
//	cltBulletCommon
//-------------------------------------------
cltBulletCommon::cltBulletCommon()
{
	pclMap	= NULL;
	pclBKI	= NULL;

	Kind			= 0;
	siMagicKind		= 0;
	CurrentOrder	= 0;

	CurveBulletRealX	=  CurveBulletRealY	= 0;

	MapSX	=	MapSY	= 0;
	MapDX	=	MapDY	= 0;

	TargetDirection	= 0;
	OldTargetDirection = 0;
	TempDirection	= 0;

	CurveRate		= 0;

	X				= 0;
	Y				= 0;	

	ShooterID		= 0;

	Apower			= 0;

	MoveStep		= 0;
	MaxMoveStep		= 0;

	Type			= 0;

	ChaseSwitch			= FALSE;
	ChaseRepeatNumber	= 0;

	StepWidth			= 0;

	CurveSwitch			= FALSE;

	CenterX	= CenterY	= 0;
}


bool cltBulletCommon::Init(cltMapCommon* pclmap, SHORT kind, SHORT magickind, SHORT id, 
					 SI32 shooter_id, SHORT apower, 
					 const cltPos* pcltilestartpos, 
					 const cltPos* pcldotstartpos, 
					 const cltAttackTarget* pcltarget, 
					 const cltPos* pcldotdestpos, 
					 cltBulletKindInfo* pclbki)
{
	pclbki->LoadSpr();		// JAYCEE
	
	pclMap			= pclmap;
	pclBKI			= pclbki;
	
	Kind			=	kind;
	siMagicKind		=   magickind;
    CurrentOrder	=	ORDER_BULLET_MOVE;

	clRealSrcPos.Set(pcldotstartpos);
	CurveBulletRealX=	pcldotstartpos->siX;
	CurveBulletRealY=	pcldotstartpos->siY;

	clRealDestPos.Set(pcldotdestpos);

	clAttackTarget.Set(pcltarget);

	if(pclMap->IsInMapArea(pcltilestartpos->siX, pcltilestartpos->siY) == true)
	{
	   MapSX = pcltilestartpos->siX; 
	   MapSY = pcltilestartpos->siY;
	}
	else
	{
		if (pclClient->GameMode == GAMEMODE_SERVER)
			pclClient->pclLog->FilePrint(TEXT("Config\\ErrorLog.log"), TEXT("BULLET013 kind:%d map:%d x:%d y:%d mapx:%d mapy:%d id:%d"), 
				kind, pclClient->pclCM->CR[shooter_id]->GetMapIndex(),
				pcltilestartpos->siX, pcltilestartpos->siY,
				pclMap->MH.MapXsize, pclMap->MH.MapYsize,
				id);

		return false;
	}

	if(pclMap->IsInMapArea(clAttackTarget.clPos.siX, clAttackTarget.clPos.siY) == true)
	{
	   MapDX = clAttackTarget.clPos.siX; 
	   MapDY = clAttackTarget.clPos.siY;
	}
	else
	{
		if (pclClient->GameMode == GAMEMODE_SERVER)
			pclClient->pclLog->FilePrint(TEXT("Config\\ErrorLog.log"), TEXT("BULLET2313 kind:%d x:%d y:%d mapx:%d mapy:%d id:%d"), 
				kind, clAttackTarget.clPos.siX, clAttackTarget.clPos.siY,
				pclMap->MH.MapXsize, pclMap->MH.MapYsize,
				id);

		return false;
	}


	//TargetDirection	=	0;
	OldTargetDirection = 0;
	TargetDirection = DecideDirection8(pcltilestartpos->siX, pcltilestartpos->siY, clAttackTarget.clPos.siX, clAttackTarget.clPos.siY);

	CurveRate=5;


	DecideDirection(clRealSrcPos.siX, clRealSrcPos.siY, clRealDestPos.siX, clRealDestPos.siY);

	X=0;
	Y=0;
	ShooterID=shooter_id;

	Apower	=	apower;
	

	MoveStep=0;
	MaxMoveStep=0;
	

	Type=0;
	
	ChaseSwitch=FALSE;
	ChaseRepeatNumber=0;

	StepWidth			=	pclBKI->StepWidth;

	ChaseSwitch			=	pclBKI->ChaseSwitch;
	CurveSwitch			=	pclBKI->CurveSwitch;

	Init();

	 GetCourse();


	 
	 return true;
}


void cltBulletCommon::DecideDirection(SHORT x1, SHORT y1, SHORT x2, SHORT y2)
{

	SHORT dir=DecideDirection16(x1, y1, x2, y2);
	
	switch(dir)
	{
	     case 0:
			  TempDirection=SOUTH|EAST;
			  break;
	     case 1:
			  TempDirection=SSE;
			  break;
	     case 2:
			  TempDirection=SOUTH;
			  break;
	     case 3:
			  TempDirection=SSW;
			  break;
	     case 4:
			  TempDirection=SOUTH|WEST;
			  break;
	     case 5:
			  TempDirection=WWS;
			  break;
	     case 6:
			  TempDirection=WEST;
			  break;
	     case 7:
			  TempDirection=WWN;
			  break;
	     case 8:
			  TempDirection=WEST|NORTH;
			  break;
	     case 9:
			  TempDirection=NNW;
			  break;
		 case 10:
			 TempDirection=NORTH;
			 break;
		 case 11:
			 TempDirection=NNE;
			 break;
		 case 12:
			 TempDirection=NORTH|EAST;
			 break;
		 case 13:
			 TempDirection=EEN;
			 break;
		 case 14:
			 TempDirection=EAST;
			 break;
		 case 15:
			 TempDirection=EES;
			 break;
		 default:
			 TempDirection=SOUTH|EAST;
			 break;
	}

}

#define PI	3.1415
#define MAX_SAMPLE_ANGLE_NUM	17
double AngleSample[] = { 85, 80, 75, 70, 65, 60, 55, 50, 45, 40, 35, 30, 25, 20, 15, 10, 5 };

BOOL GetLinearCourse(SI32 siSX, SI32 siSY, SI32 siDX, SI32 siDY, SI32 siStepWidth, SI32 siMaxStep, SI32 *siMoveX, SI32 *siMoveY, SI32 *siTotalMoveStep)
{

	SI32 stepWidth = siStepWidth;
	
	if ( pclClient->GetFrameDelay() == 25 )
	{
		stepWidth /= 2;
	}

	if ( 0 >= stepWidth )
	{
		stepWidth = 1;
	}

	SI32 x1	= siSX, y1 = siSY, x2 = siDX, y2 = siDY;
	
	SHORT x, y;
	SHORT delta_x, delta_y, half, error=0;
	SHORT step=0;
	SHORT index=0;
	
	if(x1>x2)delta_x=x1-x2;
	else     delta_x=x2-x1;
	if(y1>y2)delta_y=y1-y2;
	else	 delta_y=y2-y1;
	
	siMoveX[step]=x1;
	siMoveY[step]=y1;
	step++;
	
	if(delta_x>delta_y)
	{
		y=y1;
		half=(SHORT)(delta_x/2);
		
		if(x1<x2)
		{
			for(x=x1+1;x<=x2;x++)
			{
				error+=delta_y;
				if(error>half)
				{
					if(y1<y2)y++;
					else y--;
					error-=delta_x;
				}
				++index%=stepWidth;
				if(index==0)
				{
					siMoveX[step]=x;
					siMoveY[step]=y;
					if(step<siMaxStep)
						step++;
					
				}
			}
		}
		else
		{
			for(x=x1+1;x>=x2;x--)
			{
				error+=delta_y;
				if(error>half)
				{
					if(y1<y2)y++;
					else y--;
					error-=delta_x;
				}
				++index%=stepWidth;
				if(index==0)
				{
					siMoveX[step]=x;
					siMoveY[step]=y;
					if(step<siMaxStep)
						step++;
				}
			}
		}
	}
	else
	{
		x=x1;
		half=(SHORT)(delta_y/2);
		
		if(y1<y2)
		{
			for(y=y1+1;y<=y2;y++)
			{
				error+=delta_x;
				if(error>half)
				{
					if(x1<x2)x++;
					else x--;
					error-=delta_y;
				}
				++index%=stepWidth;
				if(index==0)
				{
					siMoveX[step]=x;
					siMoveY[step]=y;
					if(step<siMaxStep)
						step++;
				}
			}
		}
		else
		{
			for(y=y1+1;y>=y2;y--)
			{
				error+=delta_x;
				if(error>half)
				{
					if(x1<x2)x++;
					else x--;
					error-=delta_y;
				}
				++index%=stepWidth;
				if(index==0)
				{
					siMoveX[step]=x;
					siMoveY[step]=y;
					if(step<siMaxStep)
						step++;
				}
			}
		}
	}
	
	*siTotalMoveStep=step-1;
	return TRUE;
}



void cltBulletCommon::GetCourse( double SpeedIncTime )
{	
	if(pclBKI->siAtb & BLTATB_BOOMERANG)
	{
		// ������ �ö��� ��ǥ�� ���Ѵ�.
		SI32 siMoveStep1 = 0, siMoveStep2= 0;

		GetLinearCourse(clRealSrcPos.siX, clRealSrcPos.siY, clRealDestPos.siX, clRealDestPos.siY, 
			            StepWidth, MAX_SHOOT_RANGE/2, &CourseX[0], &CourseY[0], &siMoveStep1);
		GetLinearCourse(clRealDestPos.siX, clRealDestPos.siY, clRealSrcPos.siX, clRealSrcPos.siY,  
			            StepWidth, MAX_SHOOT_RANGE/2, &CourseX[siMoveStep1], &CourseY[siMoveStep1], &siMoveStep2);

		MaxMoveStep = siMoveStep1 + siMoveStep2;
	}
	else if ( pclBKI->siAtb & BLTATB_CURVE )
	{	
		SI32 X1	= clRealSrcPos.siX;
		SI32 Y1 = clRealSrcPos.siY;
		SI32 X2 = clRealDestPos.siX;
		SI32 Y2 = clRealDestPos.siY;
		
		if ( X2 == X1 )		{	++X2;	}
		if ( Y2 == Y1 )		{	++Y2;	}
		
		double V = 55;
		double length = TSQRT( (double)((X2-X1)*(X2-X1) + (Y2-Y1)*(Y2-Y1) ));
		
		double RotateAngle = atan( (Y2-Y1)*1.0 / (X2-X1)*1.0 );

		if ( X2 < X1 )		{	RotateAngle += PI;	}
	
		
		double FindAngle = 0;
		double FineV;
		switch ( (int)(length/100) )
		{
		case 1:			FineV = 43;			break;
		case 2:			FineV = 53;			break;
		case 3:			FineV = 61;			break;
		case 4:			FineV = 69;			break;
		case 5:			FineV = 76;			break;
		case 0:			FineV = 29;			break;
		case 6:			FineV = 82;			break;
		case 7:			FineV = 88;			break;
		default:		FineV = 99;			break;
		}
		
		
		double TempTime;
		double TempThrowAngle;
		double TempZPos;
		
		int AngleMax = 80;
		while( --AngleMax > 0 )
		{
			TempThrowAngle = AngleMax * PI / 180.0;
			TempTime = length/(FineV * cos( TempThrowAngle ) );
			
			TempZPos = FineV * sin( TempThrowAngle ) * TempTime - ( 0.5 )*9.8*TempTime*TempTime;
			
			if ( TABS( (int)TempZPos ) < 15 )
			{
				// ��� �����ȿ� �ִ� ���� ã����
				FindAngle = TempThrowAngle;
				V = FineV;
				break;			
			}
		}
	

		//FindAngle=60;
		// ������ �� �� �ִ� ���� ����
		if ( FindAngle == 0 )	{		return;		}	
		
		//double ThrowAngle = 63 * PI / 180.0;	// �������� �ٲ� ( ���� 50 ���� ���� )
		double ThrowAngle = FindAngle;			// ������ ��
		double ViewAngle = (90+180) * PI / 180.0;		// ���� ���� ( �츮�� 45���̴�. ���� 45 �� ���� ���̰� �����Ƿ�... ) 
		
		/*
		if ( Y2 > Y1 )
		{
			if ( X2 > X1 )		{	ViewAngle = ViewAngle;		}
			else				{	ViewAngle = PI - ViewAngle;	}
		}
		else
		{
			if ( X2 > X1 )		{	ViewAngle = ViewAngle * (-1);		}
			else				{	ViewAngle = PI + ViewAngle;			}
		}
		*/
		
		double totaltime = length/(V * cos( ThrowAngle ) );
		
		// CourseX,CourseY ����� ���� �����ϱ� ������... 
		if ( totaltime >= 20 )	{	return;		}
		
		double Xi, Yj, Zk;	
		double PreXi = X1, PreYj = Y1, PerZk = 0;
		
		SI32 siStep = 0;
		for ( double t = 0; t < totaltime; t += SpeedIncTime )
		{
			// �迭 ���� �Ѱ迡 ����. ( ���� �ʰ��ؼ� ���� -> Access Violation �߰�¡... )
			if ( siStep >= MAX_SHOOT_RANGE )
			{
				break;
			}
			
			Xi = X1 + V * cos( ThrowAngle )*cos( RotateAngle  ) /** cos(RotateAngle)*/ * t;		// X��
			Yj = Y1 + V * cos( ThrowAngle )*sin( RotateAngle  ) /** sin(RotateAngle)*/ * t;		// Y��
			Zk = V * sin( ThrowAngle ) * t - ( 0.5 )*9.8*t*t;				// �տ����� ���� �ö󰡴� y�� �����̰�, �ڿ����� �߷¿� ���� ��¡...<--- �����δ� Z �࿡ ���� ���� ����
			
			Xi += Zk*cos(ViewAngle );
			Yj += Zk*sin( ViewAngle );
			
			CourseX[ siStep ] = (SI32)Xi;
			CourseY[ siStep++ ] = (SI32)Yj;
			
			PreXi = Xi;
			PreYj = Yj;
			
			if ( Zk < 0 )
			{
				break;
			}
		}
		
		MaxMoveStep=siStep-1;
		
		SI32 a = CourseX[MaxMoveStep];
		SI32 b = CourseY[MaxMoveStep];

		SI32 c = clAttackTarget.clPos.GetX();
		SI32 d = clAttackTarget.clPos.GetY();
	}
	else
	{
		GetLinearCourse(clRealSrcPos.siX, clRealSrcPos.siY, clRealDestPos.siX, clRealDestPos.siY, 
			            StepWidth, MAX_SHOOT_RANGE, &CourseX[0], &CourseY[0], &MaxMoveStep);
	}

}


BOOL cltBulletCommon::Action()
{

   switch(CurrentOrder)
   {
	   case ORDER_BULLET_MOVE:

		   SetAnimation(ANI_BULLET_MOVE);

		   // �ִϸ��̼� �������� ������Ʈ �Ѵ�. 
		   AniStepAction();

		   // ����ź�� ��쿡, 
		   if(ChaseSwitch==TRUE)
		   {
			   // ������ �Ÿ���ŭ ���� ��ǥ�� ���� ���ư� �Ŀ�, 
		      if(MoveStep>2 && ChaseRepeatNumber<15)
			  {
				  // ��ǥ�� ��� ������, 
				  SI32 attackid = clAttackTarget.GetAttackID();
				   if(pclClient->pclCM->IsAlive(attackid) )
				   {
					   // ��ǥ�� ���ο� ��ġ�� ���� ��, 
					   pclClient->pclCM->CR[attackid]->GetHitPoint(&clRealDestPos);
				       ChaseRepeatNumber++;

					   MapDX = pclClient->pclCM->CR[attackid]->GetX();
					   MapDY = pclClient->pclCM->CR[attackid]->GetY();

				       //RealDX+=VaryX;
				       //RealDY+=VaryY;

				       MoveStep		=	0;
					   MaxMoveStep	=	0;
					   DecideDirection(clRealSrcPos.siX, clRealSrcPos.siY, clRealDestPos.siX, clRealDestPos.siY);

			           GetCourse();			
				   }
			  }
		   }


		   // ��ǥ�� �����Ѵ�. 
			clRealSrcPos.siX = CourseX[MoveStep];
			clRealSrcPos.siY = CourseY[MoveStep];

			if(pclBKI->siAtb & BLTATB_BOOMERANG)
			{

				if(MoveStep==MaxMoveStep)
				{
					return FALSE;
				}
				// ������ �Ǹ� Hit ó���� �Ѵ�.
				else if(MoveStep==MaxMoveStep/2)
				{
					Hit();
				}

				// ������ ������ �ϴ� ���̸� ������ �����.
				MakeTail(TempDirection);
				MoveStep++;
			}
			else	// �θ޶��� �ƴϸ� ������ ������ Hitó���� �Ѵ�.
			{
				
				if(MoveStep==MaxMoveStep)
				{
					Hit();
					return FALSE;
					
				}
				else
				{
					// ������ ������ �ϴ� ���̸� ������ �����.
					MakeTail(TempDirection);
					MoveStep++;
					
				}
			}

		   break;
   }

   CalculateRealXY();
   return TRUE;
}


BOOL cltBulletCommon::Hit()
{

	//------------------------------
	// Ŭ���̾�Ʈ�� ��쿡�� �ǰ� ���⸦ �����.
	//-------------------------------
	MakeHitSmoke();

	//------------------------------
	// Ŭ���̾�Ʈ�� ��쿡�� �ǰ� ���带 ����Ѵ�.
	//-------------------------------
	MakeHitSound();




	if(pclBKI->siAtb & BLTATB_FRAGMENT)
	{
		return HitFragment();
	}
	else
	{
		return HitNormal();
	}


	//return FALSE;

}

BOOL cltBulletCommon::HitFragment()
{
	
	// ��ǥ�� ���Ѵ�. 
	pclMap->GetRealTileByRealDot(clRealSrcPos.siX, clRealSrcPos.siY, &MapDX, &MapDY);

	// ���� ��������, 
	if(pclMap->IsColl(MapDX, MapDY, BLOCK_DEEPWATER))
	{
		//pclClient->pclSmokeManager->SetSmoke(KIND_SMOKE_WATEREXP, clRealSrcPos.siX, clRealSrcPos.siY, pclMap);
	}
	else
	{
		//pclClient->pclSmokeManager->SetSmoke(KIND_SMOKE_SMALLEXP2, clRealSrcPos.siX, clRealSrcPos.siY, pclMap);
	}
	return TRUE;
}


BOOL cltBulletCommon::HitNormal()
{
	SHORT mapx=0, mapy=0;
	SI32 attackatb = 0;
	SI32 range = 0;


	//----------------------------------
	// ���� �Ӽ��� �����Ѵ�.
	//----------------------------------
	attackatb	=	pclBKI->siAttackType;
	if(attackatb <= 0)return TRUE;
	
	if(pclBKI->siAtb & BLTATB_RANGE1)
	{
		range = 1;
	}
	else
	{
		range = 0;
	}

	if(pclClient->GameMode == GAMEMODE_SERVER)
	{
		cltAttackDamageInfo cldamageinfo(attackatb, Apower, siMagicKind);
		((cltServer*)pclClient)->HitOperation(ShooterID, &cldamageinfo, range, &clAttackTarget, pclMap);
	}	

	return TRUE;
}


void cltBulletCommon::CalculateRealXY()
{

	// X, Y��ǥ�� ���Ѵ�. 
	pclMap->GetRealTileByRealDot(clRealSrcPos.siX, clRealSrcPos.siY, &X, &Y);


	CenterX = clRealSrcPos.siX;
	CenterY = clRealSrcPos.siY;

}
