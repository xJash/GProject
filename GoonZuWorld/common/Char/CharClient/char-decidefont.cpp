
#include "..\..\Client\Client.h"


extern cltCommonLogic* pclClient;

// ���� �� �׸��� �����Ѵ�. 
void cltCharClient::DecideFont()
{
	if(bUpdateAnimationSwitch == false)return ;
	
	bUpdateAnimationSwitch	=	false;
	
	// by LEEKH 2007.12.24 - TRANSFORM
	if(Animation == ANITYPE_SLEEP || Animation == ANITYPE_SLEEPCAT)
	{
		pclKI->clCharAniManager.DecideDrawImg(Animation, siDirection, clAniInfo, pclClient->CurrentClock,&pImgSpr,
			&Font, &bReverseSwitch, &siEffectFont ,&siShadowAni , &siShadowFont);
	}
	else
	{
		GetKindInfo(true)->clCharAniManager.DecideDrawImg(Animation, siDirection, clAniInfo, pclClient->CurrentClock,&pImgSpr,
			&Font, &bReverseSwitch, &siEffectFont ,&siShadowAni , &siShadowFont);
	}
}