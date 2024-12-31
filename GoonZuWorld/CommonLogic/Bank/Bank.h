//---------------------------------
// 2003/5/17 ���°�
//---------------------------------

#ifndef _BANK_H
#define _BANK_H

#include "..\StructureClass\StructureClass.h"
#include "..\..\Common\CommonHeader.h"
#include "..\Account\Account.h"

//-----------------------------------------------
// Definition
//-----------------------------------------------
#define MAX_BANK_TAB_NUMBER	3
#define MAX_ACOUNT_PER_BANK	10000		// ������ ���� �� �ִ� �� ���� ��. 
#define MAX_MONEY_IN_ACOUNT	1000000000	// �� ������  ���� �� �ִ� �ִ� �ݾ�. 

class cltBankAccount {
private:
	GMONEY siMoney;

public:
	cltAccountNum	clAccountNum;
	SI32			siPersonID;		// ���� ���� PersonID

	cltBankAccount()
	{
		siMoney		= 0;
		siPersonID	= 0;
	}

	cltBankAccount(cltAccountNum* pclaccountnum, SI32 sipersonid, GMONEY money)
	{
		clAccountNum.Set(pclaccountnum);
		siPersonID		= sipersonid;
		siMoney			= money;
	};

	void Set(cltBankAccount* pclaccount)
	{
		clAccountNum.Set(&pclaccount->clAccountNum);
		siPersonID		= pclaccount->siPersonID;
		siMoney			= pclaccount->siMoney;

	}

	void SetMoney(GMONEY money)
	{
		siMoney = money;
	}

	GMONEY GetMoney()const{return siMoney;}

	BOOL IncreaseMoney(GMONEY money)
	{
		if((siMoney + money) > MAX_MONEY_IN_ACOUNT)return FALSE;

		siMoney += money;

		return TRUE;
	}

	BOOL DecreaseMoney(GMONEY money)
	{
		if(money > siMoney)return FALSE;
		 siMoney -= money;

		 return TRUE;
	}

	void GetGMSectionData(GMSectionData* pkGMSectionData);
};


//------------------------------------
// �� ��ũ�� Ŭ���� 
//------------------------------------
class cltBank : public cltStructureBasic {
private:
	SI32 siAcountCount;			// ���� ����. 

public:

	cltBank(SI32 sivillageunique);
	~cltBank();

	// ������ ������ �����Ѵ�.
	BOOL SetFee(cltFee* pclfee);

	// �����Ḧ ����Ѵ�. 
	GMONEY CalcFee(GMONEY money);


};


#endif
