#include "..\Client\Client.h"


#include "smoke.h"
#include "Char\CharAni\CharAni.h"
#include "Map\Map.h"


extern cltCommonLogic* pclClient;


cltSmokeCommon::cltSmokeCommon()
{
	pclSKI	= NULL;
	pclMap	= NULL;

	//----------------
	// �źа��� 
	//----------------
	ID		= 0;
	Kind	= 0;
	GroundKind = 0 ;

	//--------------------
	// ��ǥ 
	///-------------------
	RealX	= 0;
	RealY	= 0;
	X		= 0;
	Y		= 0;		
	CenterX	= 0;
	CenterY	= 0;

	//--------------------
	// �ൿ 
	//--------------------
	CurrentOrder	= 0;               // ���� ĳ���Ͱ� �ϰ� �ִ� �۾� 
	Animation		= 0;
	Step			= 0;

	//--------------------
	// ���� �Ⱓ.
	//--------------------
	MaxRepeatNumber	= 0;
	RepeatNumber	= 0;
	m_siStepDelay	= 0;
	LastChangedFrame= 0;	
	MoveFrameNumber	= 0;

	//--------------------
	// ���� 
	//--------------------
	AttackID		= 0;
	Apower			= 0;

	//--------------------
	// �ɼ� 
	//--------------------
	RisingSwitch	= FALSE;

}


void cltSmokeCommon::Init(SHORT kind, SHORT id, SHORT realx, SHORT realy, cltMapCommon* pmap,
						  cltSmokeKindInfo* pclinfo,SI32 tempdirection,SI32 groundkind )
{
	pclinfo->LoadSpr();

	pclSKI				=	pclinfo;
	ID					=	id;
	Kind				=	kind;
	GroundKind			=	groundkind;
    MaxRepeatNumber		=	pclSKI->MaxRepeatNumber;
	RisingSwitch		=	pclSKI->RisingSwitch;
	m_siStepDelay		=	pclSKI->m_siStepDelay;
	pclMap				=	pmap;

	Step				=	0;

	RealX=realx;
	RealY=realy;

	AttackID= 0;

	CurrentOrder=ORDER_SMOKE_EXP;

	LastChangedFrame = pclClient->GetFrame();

	TempDirection = tempdirection;

	Init();
}


BOOL cltSmokeCommon::Action()
{
	switch(CurrentOrder)
	{
	case ORDER_SMOKE_EXP:
		
		// ���� �ö󰣴�. 
		if(RisingSwitch==TRUE)
		{
			RealY-=2;
		}

		Animation=ANITYPE_EXP;

		if(TABS(LastChangedFrame - pclClient->GetFrame()) >= m_siStepDelay)
		{
			LastChangedFrame = pclClient->GetFrame();
		    Step++;
		}

		if(Step == MoveFrameNumber)
		{
			if ( GroundKind )
			{
				pclClient->pclSmokeManager->SetSmoke(GroundKind,CenterX,CenterY,pclMap);
			}

			if(RepeatNumber<MaxRepeatNumber)
			{
				RepeatNumber++;
				Step=0;
			}
			else
			  return FALSE;
		}
		break;
	default:
		break;
	}

	CalculateRealXY();
	return TRUE;
}

void cltSmokeCommon::CalculateRealXY()
{
//	int centerx, centery;  // ���� ��ġ�� �߽� ��ǥ 

	// X, Y��ǥ�� ���Ѵ�. 
	pclMap->GetRealTileByRealDot(RealX, RealY, &X, &Y);

	CenterX=RealX;
	CenterY=RealY;
}
