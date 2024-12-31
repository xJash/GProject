#ifndef _DBMSGBANK_H
#define _DBMSGBANK_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBMsg.h"
#include "..\..\GoonZuWorld\CommonLogic\Bank\Bank.h"


//------------------------------------------
// ���࿡ ������ ������ ���� ��û. 
//------------------------------------------
class sDBRequest_CreateBankAccount
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	// who
	SI32				siPersonID;					// ���� �Ա��� PersonID

	// by where
	SI32				siVillageUnique;			// ������ VillageUnique

	sDBRequest_CreateBankAccount(SI32 id, SI32 personid, SI32 villageunique)
	{
		packetHeader.usSize = sizeof( sDBRequest_CreateBankAccount );
		packetHeader.usCmd = DBMSG_REQUEST_CREATEBANKACCOUNT;
		usCharID		= id;

		siPersonID		= personid;
		siVillageUnique	= villageunique;
	}
};

class sDBResponse_CreateBankAccount
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;					// �����.

	// who, to where
	cltBankAccount		clBankAccount;				// �Ա����� ���� ����.

	sDBResponse_CreateBankAccount()
	{
		ZeroMemory(this, sizeof(sDBResponse_CreateBankAccount));
	}


};

//------------------------------------------
// ���࿡ ������ ������ ���� ��û. 
//------------------------------------------
class sDBRequest_CloseBankAccount
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	// who
	SI32				siPersonID;					// ���� �Ա��� PersonID

	// by where
	SI32				siVillageUnique;			// ������ VillageUnique

	sDBRequest_CloseBankAccount(SI32 id, SI32 personid, SI32 villageunique)
	{
		packetHeader.usSize = sizeof( sDBRequest_CloseBankAccount );
		packetHeader.usCmd = DBMSG_REQUEST_CLOSEBANKACCOUNT;
		usCharID		= id;

		siPersonID		= personid;
		siVillageUnique	= villageunique;
	}
};

class sDBResponse_CloseBankAccount
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;					// �����.

	// who, to where
	cltBankAccount		clBankAccount;				// ���� ���� ���� ���� ����. 	

	GMONEY				siMoney;					// ���� ���� ���� ���� ����. 

	// by where
	SI32				siVillageUnique;			// ������ VillageUnique for LOG

	sDBResponse_CloseBankAccount()
	{
		ZeroMemory(this, sizeof(sDBResponse_CloseBankAccount));
	}
};


//------------------------------------------
// ���࿡ ���� �Ա��� ���� ��û. 
//------------------------------------------
class sDBRequest_InputMoneyToBank
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	// who
	SI32				siPersonID;					// ���� �Ա��� PersonID

	// by where
	SI32				siVillageUnique;			// person�� ������ ���� �ִ� ���� ����(���� ������ ������ �� ��� ��� ������ ������ �ϴ���..) 

	// what
	cltMoney			clMoney;					// �Ա��� ���� �ݾ�. 

	// fee
	GMONEY				siFee;						// ������. 

	sDBRequest_InputMoneyToBank(SI32 id, SI32 personid, SI32 villageunique, cltMoney* pclmoney, GMONEY fee)
	{
		packetHeader.usSize = sizeof( sDBRequest_InputMoneyToBank );
		packetHeader.usCmd = DBMSG_REQUEST_INPUTMONEYTOBANK;
		usCharID		= id;

		siPersonID		= personid;
		siVillageUnique	= villageunique;
		clMoney.Set(pclmoney);	

		siFee			= fee;
	}
};

class sDBResponse_InputMoneyToBank
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;					// �����.

	// who, to where
	cltBankAccount		clBankAccount;				// �Ա����� ���� ����. 	

	// what
	cltMoney			clMoney;					// Person�� �����ϰ� �ִ� ����. 

	// to bank info
	cltMoney			clTotalInputMoney;			// �ش����࿡ �Աݵ� �� �ݾ�. 
	cltMoney			clCurrentLeftMoney;			// �ش����࿡ ���� �� �ݾ�. 

	// by bank info
	SI32			siByBankVillageUnique;		// ������ ���� ����ũ. 
	cltMoney		clByBankTotalInputMoney;	// �ش����࿡ �Աݵ� �� �ݾ�. 
	cltMoney		clByBankCurrentLeftMoney;	// �ش����࿡ ���� �� �ݾ�. 

	// what
	cltMoney			clInputMoney;				// �Ա��� ���� �ݾ�. for LOG

	// fee
	GMONEY				siFee;						// ������. for LOG
};

//------------------------------------------
// �������κ��� ���� ����� ���� ��û. 
//------------------------------------------
class sDBRequest_OutputMoneyFromBank
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;					// ���� ����� PersonID
	SI32				siVillageUnique;			// ����ϴ� ���� VillageUnique
	cltMoney			clMoney;					// ����� ���� �ݾ�. 

	GMONEY				siFee;						// ������. (����� ���� ������ ���¿��� ������.) 

	sDBRequest_OutputMoneyFromBank(SI32 id, SI32 personid, SI32 villageunique, cltMoney* pclmoney, GMONEY fee)
	{
		packetHeader.usSize = sizeof( sDBRequest_OutputMoneyFromBank );
		packetHeader.usCmd = DBMSG_REQUEST_OUTPUTMONEYFROMBANK;
		usCharID		= id;

		siPersonID		= personid;
		siVillageUnique	= villageunique;
		clMoney.Set(pclmoney);	

		siFee			= fee;
	}
};


class sDBResponse_OutputMoneyFromBank
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.
	cltBankAccount		clBankAccount;		// ������� ���� ����. 	
	cltMoney			clMoney;			// Person�� �����ϰ� �ִ� ����. 

	cltMoney			clTotalInputMoney;	// �ش����࿡ �Աݵ� �� �ݾ�. 
	cltMoney			clCurrentLeftMoney;	// �ش����࿡ ���� �� �ݾ�. 

	// by bank info
	SI32				siByBankVillageUnique;		// ������ ���� ����ũ. 
	cltMoney			clByBankTotalInputMoney;	// �ش����࿡ �Աݵ� �� �ݾ�. 
	cltMoney			clByBankCurrentLeftMoney;	// �ش����࿡ ���� �� �ݾ�. 
	bool				bCancelStockOrder;			// �ż��ֹ��ݾ׺��� ���忡 ���� ������ True
								
	cltMoney			clOutputMoney;				// ����� ���� �ݾ�. For LOG 

	GMONEY				siFee;						// ������. (����� ���� ������ ���¿��� ������.) For LOG

	sDBResponse_OutputMoneyFromBank()
	{
		ZeroMemory(this, sizeof(sDBResponse_OutputMoneyFromBank));
	}
};


//------------------------------------------
// ��������Ḧ  ������ ���� ��û
//------------------------------------------
class sDBRequest_SetBankFee
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	// Who
	SI32				siPersonID;

	// Where
	SI32				siVillageUnique;	// ������ ��ġ�� ���� VillageUnique

	// What
	cltFee			clFee;			//  �����ؾ� �� ������ ����. 


	sDBRequest_SetBankFee()
	{
		ZeroMemory(this, sizeof(sDBRequest_SetBankFee));
	}

	sDBRequest_SetBankFee(SI32 id, SI32 personid, SI32 villageunique, cltFee* pclfee)
	{
		packetHeader.usSize = sizeof( sDBRequest_SetBankFee );
		packetHeader.usCmd = DBMSG_REQUEST_SETBANKFEE;
		usCharID		= id;

		siPersonID		= personid;
		siVillageUnique	= villageunique;
		clFee.Set(pclfee);
	}
};


class sDBResponse_SetBankFee
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	// result 
	SI32				siResult;			// �����.

	// who
	SI32				siPersonID;

	// where
	SI32				siVillageUnique;	// ������ ��ġ�� ������ VillageUnique

	// what
	cltFee			clFee;					// ������ ������ ����. 

	sDBResponse_SetBankFee()
	{
		ZeroMemory(this, sizeof(sDBResponse_SetBankFee));
	}

};


#endif