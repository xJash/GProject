//---------------------------------
// 2004/11/16 ���°�
//---------------------------------

#include "Char-Common.h"
#include "..\..\Order\Order.h"

// ��ȯ���� ��ǰ�� ����ϰ� �ִ°�?
/*
bool cltCharCommon::IsSummonHaveItem(SI32 summonindex)
{

	SI32 startpos	= PERSONITEM_SUMMON1EQUIP0  + (summonindex * MAX_SHAPE_ITEM); 
	SI32 endpos		= startpos + MAX_SHAPE_ITEM;
	if(endpos > MAX_ITEM_PER_PERSON)return false;

	SI32 i;

	// ������ ����ϰ� �ִ��� Ȯ���Ѵ�. 
	for(i = startpos;i < endpos;i++)
	{
		if(pclCI->clCharItem.clItem[i].siUnique)return true;
	}
	
	return false;
}
*/

bool cltCharCommon::Action_Special()
{
	SetAnimation( clCurOrder.siPara1 );
	DoAnimationDelay();

	NTCHARString512	kText;
	kText = "clAniInfo.GetAniStep() = ";
	kText += SI32ToString(clAniInfo.GetAniStep());
	kText += "\n";
	OutputDebugString(kText);

	SI32 aniref			= GetKindInfo()->clCharAniManager.FindRefFromAnitype(Animation);
	SI32 framenumber	= GetKindInfo()->clCharAniManager.GetFrameNum(aniref);

	//if( clAniInfo.GetAniStep() == 0 )
	if( clAniInfo.GetAniStep() == framenumber - 1 )
	{
		bHitDoneSwitch	= false;
		bBusySwitch		= false;

		return true;
	}
	else 
		return false;
}
