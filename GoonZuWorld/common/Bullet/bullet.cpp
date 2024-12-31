#include "..\Client\Client.h"

#include "bullet.h"
#include "..\Smoke\Smoke.h"
#include "Util\Util.h"

extern cltCommonLogic* pclClient;

cltBulletServer::cltBulletServer() : cltBulletCommon()
{
	HitIDIndex	= 0;

}


void cltBulletServer::Init()
{
	SI32 i;

	HitIDIndex	=	0;
    for(i=0;i<MAX_HIT_ID;i++)
	   HitID[i]= 0;

}


//
// �ѹ� ������ ĳ���͸� �ٽ� �������� �ʱ� ���ؼ�.
// ������ �ʱ�ȭ�Ѵ�. 
//

void cltBulletServer::InitPushID()
{
	HitIDIndex=0;
}

//
// id = �Ѿ��� id
// 
//

void cltBulletServer::PushHitID(SI32 id)
{

	HitID[HitIDIndex]=id;

	if(HitIDIndex<(MAX_HIT_ID-1))
	   HitIDIndex++;
}

//
// id = �Ѿ��� id
// �Ѿ��� ��ǥ�� �¾ҳ�?
//

BOOL cltBulletServer::IsAlreadyPushID(SI32 id)
{
	int i=0;

	for(i=0;i<HitIDIndex;i++)
	{
		if(HitID[i] == id )return TRUE;
	}

	return FALSE;
}


