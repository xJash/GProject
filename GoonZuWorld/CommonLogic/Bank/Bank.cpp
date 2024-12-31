//---------------------------------
// 2003/5/17 ���°�
//---------------------------------
//#include <Graphic.h>
#include "Bank.h"
#include "..\..\CommonLogic\CommonLogic.h"

#include "..\..\Resource.h"

extern cltCommonLogic* pclClient;

//-------------------------------------------
// cltBankAccount
//-------------------------------------------
void cltBankAccount::GetGMSectionData(GMSectionData* pkGMSectionData)
{
	if( pkGMSectionData == NULL )		return;

	pkGMSectionData->BeginData( "BankAccount" );
	{
		pkGMSectionData->AddDataInt("money",		siMoney);
		pkGMSectionData->AddDataInt("village",		clAccountNum.siVillageUnique);
		pkGMSectionData->AddDataInt("number",		clAccountNum.siAccountNum);
	}
	pkGMSectionData->EndData( "BankAccount" );
}

//-------------------------------------------
// cltBank
//-------------------------------------------
cltBank::cltBank(SI32 sivillageunique) : cltStructureBasic(sivillageunique)
{

	siAcountCount	= 0;

}

cltBank::~cltBank()
{

}


// ������ ������ �����Ѵ�.
BOOL cltBank::SetFee(cltFee* pclfee)
{
	clStrInfo.clBankStrInfo.clFee.Set(pclfee);
	return  TRUE;
}


// �����Ḧ ����Ѵ�. 
GMONEY cltBank::CalcFee(GMONEY money)
{
	return clStrInfo.clBankStrInfo.clFee.CalcFee(money);
}




