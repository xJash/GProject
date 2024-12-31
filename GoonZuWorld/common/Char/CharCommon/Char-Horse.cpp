//---------------------------------
// 2003/9/15 ���°�
//---------------------------------

#include "..\Common\CommonHeader.h"
#include "..\..\Client\Client.h"


#include "..\..\Client\Music\Music.h"

//--------------------------
// Common
//-------------------------
#include "PersonInfo.h"

#include "..\Common\Bullet\Bullet.h"
#include "Util\Util.h"


extern cltCommonLogic* pclClient;

// ���� ź��. 
bool cltCharCommon::RideHorse()
{
	cltHorse* pclhorse = pclCI->clHorseInfo.GetCurrentShowHorse();

	if(pclhorse == NULL || pclhorse->siHorseUnique <= 0)return false;

	//KHY - 1220 - ���Žý���.
	if(clTransFormInfo.bTransFormMode == true ) // ���� ���¸� ����.
		return false;

	// Ÿ�� �� ���� ������ ȹ���Ѵ�. 
	//pclCI->clHorseInfo.siCurrentHorseIndex	= pclCI->clHorseInfo.siCurrentShowHorse;
	pclCI->clHorseInfo.siCurrentHorseRIDEHORSE	= true;

	return true;
}

// ������ ������.
bool cltCharCommon::UnrideHorse()
{
	//if(pclCI->clHorseInfo.siCurrentHorseIndex	== -1)return false;

	// Ÿ�� �� ���� ������ ȹ���Ѵ�. 
	//pclCI->clHorseInfo.siCurrentHorseIndex	= -1;

	//KHY - 1220 - ���Žý���.
	if(clTransFormInfo.bTransFormMode == true ) // ���� ���¸� ����.
		return false;
	
	//KHY - 1001 - ��µ��� 5���� ���� ����.
	if(pclCI->clHorseInfo.siCurrentHorseRIDEHORSE	== false)return false;


	pclCI->clHorseInfo.siCurrentHorseRIDEHORSE	=  false;

	return true;
}

// ���� ������ �ִ°�?
bool cltCharCommon::HaveHorse()
{
	return pclCI->clHorseInfo.HaveHorse();
}

