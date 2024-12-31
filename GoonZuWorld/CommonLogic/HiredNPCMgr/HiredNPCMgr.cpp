#include "commonlogic.h"
#include "..\..\Common\Char\KindInfo\KindInfo.h"

#include "HiredNPCMgr.h"


extern cltCommonLogic* pclClient;


cltHiredNPCPayInfo::cltHiredNPCPayInfo()
{
	Init();
}

cltHiredNPCPayInfo::~cltHiredNPCPayInfo()
{

}

void cltHiredNPCPayInfo::Init()
{
	siNPCKind = 0;
	siTotalHiredNum = 0;
	siPayment = 0;
}

cltHiredNPCPayManager::cltHiredNPCPayManager()
{
	Init();
}

cltHiredNPCPayManager::~cltHiredNPCPayManager()
{

}

void cltHiredNPCPayManager::Init()
{
	siTotalNPCNum = 0;
	siNPCKindNum = 0;

	for( int i = 0; i < MAX_HIREDNPC_KIND_NUM; ++i )
	{
		clHiredNPCPayInfo[ i ].siNPCKind = 0;
	}
}

void cltHiredNPCPayManager::AddNPC( int npckind )
{
	int i;

	// ��ϵ� NPC Kind�� �ִ��� �˻� 
	for( i = 0; i < MAX_HIREDNPC_KIND_NUM; ++i )
	{
		if( clHiredNPCPayInfo[ i ].siNPCKind == npckind ) {
			// ��� �Ǿ� ������ 

			++clHiredNPCPayInfo[ i ].siTotalHiredNum;
			++siTotalNPCNum;

			CalcPayment( i );
			return;
		}
	}

	for( i = 0; i < MAX_HIREDNPC_KIND_NUM; ++i ) 
	{
		if( clHiredNPCPayInfo[ i ].siNPCKind == 0 ) {

			clHiredNPCPayInfo[ i ].siNPCKind = npckind;
			clHiredNPCPayInfo[ i ].siTotalHiredNum = 1;
			++siTotalNPCNum;

			CalcPayment( i );
			return;
		}
	}
}

void cltHiredNPCPayManager::DelNPC( int npckind )
{
	int i;
	for( i = 0; i < MAX_HIREDNPC_KIND_NUM; ++i )
	{
		if( clHiredNPCPayInfo[ i ].siNPCKind == npckind ) {
			// ��� �Ǿ� ������ ���ڸ� 1���� 

			--clHiredNPCPayInfo[ i ].siTotalHiredNum;
			--siTotalNPCNum;

			if( clHiredNPCPayInfo[ i ].siTotalHiredNum == 0 ) {
				// ���ڰ� 0�̸� Kind�� ���ش�

				clHiredNPCPayInfo[ i ].siNPCKind = 0;
			}

			CalcPayment( i );
		}
	}
}

void cltHiredNPCPayManager::CalcPayment( int i )
{


	GMONEY pay =  (GMONEY)clHiredNPCPayInfo[ i ].siTotalHiredNum - 2  * 12000 + 20000;

	if( pay < 20000 ) pay = 20000;
	if( pay > 200000 ) pay = 200000;
	
	pay += pclClient->pclKindInfoSet->GetHireBasicMoney( clHiredNPCPayInfo[ i ].siNPCKind );

	clHiredNPCPayInfo[ i ].siPayment = pay;
	
/*
	SI32 pay = pclClient->pclKindInfoSet->GetHireBasicMoney( clHiredNPCPayInfo[ i ].siNPCKind )
		* ( pclClient->pclItemManager->clItemStatistic.siNPCPriceRate / 100. );
*/
}

GMONEY cltHiredNPCPayManager::GetPayment( int npckind )
{
	int i;
	for( i = 0; i < MAX_HIREDNPC_KIND_NUM; ++i )
	{
		if( clHiredNPCPayInfo[ i ].siNPCKind == npckind ) {
			return clHiredNPCPayInfo[ i ].siPayment;
		}
	}
	return 0;
}

