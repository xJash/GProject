#include "BillComponent/Bill.h"
#include "BillInterfaces.h"

/**--------------------------------------------------------------
-- ProcedureName   : GetUserBalance
-- Description     : �ܾ���ȸ �������̽�
-- Return Value    : long
--                   0 = ����, �׿� = �����߻�
-- Parameter       :
--    [IN]szBillServer : ��������IP:Port (������ ������ ; �� �и�)
--                       (��)111.111.111.111:50050;111.111.111.111:50050
--    [IN]szUserID     : �̿���ID
--    [OUT]lngRealCash : RealCash �ܾ�
--    [OUT]lngBonus    : Bonus ĳ�� �ܾ�
--    [OUT]lngMileage  : ���ϸ��� �ܾ�
--
-- Copyright �� 2006 by PayLetter Inc. All rights reserved.
---------------------------------------------------------------*/
long BillInterfaces::GetUserBalance
(
	char*	szBillServer,	// BillServerIP:Port (111.111.111.111:50050;111.111.111.111:50050)
	char*	szUserID,		// UserID

	long*	lngRealCash,	// RealCash �ܾ�
	long*	lngBonus,		// Bonus ĳ�� �ܾ�
	long*	lngMileage		// ���ϸ��� �ܾ�
)	
{
	CBill		Bill;
	long		nTxResult = 0;

	// �ʱ�ȭ
	*lngRealCash	= 0;
	*lngBonus		= 0;
	*lngMileage		= 0;

	try
	{
		Bill.PutHOST(szBillServer);
		Bill.PutTxCmd(TXCMD_ACCOUNTINFO);

		Bill.SetField(BILL_SITECODE,	MY_SITECODE);
		Bill.SetField(BILL_GAMECODE,	MY_GAMECODE);
		Bill.SetField(BILL_USERID,		szUserID);

		nTxResult = Bill.StartAction();
	}
	catch(...)
	{
		return (-2);
	}

	// �ܾ� ��ȸ ����, RealCash, Bonus, Mileage�� ���Ѵ�.
	if (nTxResult == BILL_SUCCESS)
	{
		char szTmp[32];

		Bill.GetVal(BILL_CASHREAL, szTmp, sizeof(szTmp));
		*lngRealCash = atol(szTmp);

		Bill.GetVal(BILL_CASHBONUS, szTmp, sizeof(szTmp));
		*lngBonus	= atol(szTmp);

		Bill.GetVal(BILL_MILEAGE, szTmp, sizeof(szTmp));
		*lngMileage	= atol(szTmp);
	}

	return(nTxResult);
}

/**--------------------------------------------------------------
-- ProcedureName   : ChargeItem
-- Description     : ������ ����(����) �������̽�
-- Return Value    : long
--                   0 = ��������, �׿� = �����߻�
-- Parameter       :
--    [IN]szBillServer : ��������IP:Port (������ ������ ; �� �и�)
--                       (��)111.111.111.111:50050;111.111.111.111:50050
--    [IN]szUserID     : �̿���ID
--    [IN]szGameItemKey: ���� ������ ����Ű
--    [IN]szGameItemName: ���� ������ ��
--    [IN]szUserIP     : �̿��� IP�ּ� (xxx.xxx.xxx.xxx ��)
--    [IN]lngItemPrice : ���ž����� ����(�ܰ�)
--    [IN]lngItemPiece : ������ ����(��κ� 1�� ����.)
--    [IN]lngPresentFlag: ��������(1:�Ϲݱ���, 2:����)
--    [IN]lngCPID      : ������ ���� CP(1:����,2:��Ʋ��Ƽī)
--    [OUT]lngRealCash : RealCash �ܾ�
--    [OUT]lngBonus    : Bonus ĳ�� �ܾ�
--    [OUT]lngMileage  : ���ϸ��� �ܾ�
--    [OUT]szChargeNo  : ���ݹ�ȣ (������� �� ��� �ʿ���.)
--
-- Copyright �� 2006 by PayLetter Inc. All rights reserved.
---------------------------------------------------------------*/
long BillInterfaces::ChargeItem
(
	char*	szBillServer,	// BillServerIP:Port (111.111.111.111:50050;111.111.111.111:50050)
	char*	szUserID,		// UserID

	char*	szGameItemKey,	// ���� ������ Ű
	char*	szGameItemName,	// ���� ������ ��
	char*	szUserIP,		// �̿����� IP ��巹��
	long	lngItemPrice,	// ����(����) �ݾ�
	long	lngItemPiece,	// 1�� ����
	long	lngItemCnt,		// ������ ����
	long	lngPresentFlag,	// ���� ����(�����̸� 1, �ƴϸ� 0)
	long	lngCPID,		// ������ ���� CP(1:����,2:��Ʋ��Ƽī)

	long*	lngRealCash,	// RealCash �ܾ�
	long*	lngBonus,		// Bonus ĳ�� �ܾ�
	long*	lngMileage,		// ���ϸ��� �ܾ�
	char*	szChargeNo		// ���ݹ�ȣ(19 Bytes) (����Ҷ� �ʿ���.)
)	
{
	CBill		Bill;
	long		nTxResult = 0;

	// �ʱ�ȭ
	*lngRealCash	= 0;
	*lngBonus		= 0;
	*lngMileage		= 0;

	try
	{
		Bill.PutHOST(szBillServer);
		Bill.PutTxCmd(TXCMD_CHARGEGAMEITEM); // chargegameitem

		Bill.SetField(BILL_SITECODE,	MY_SITECODE);
		Bill.SetField(BILL_GAMECODE,	MY_GAMECODE);
		Bill.SetField(BILL_USERID,		szUserID);
		Bill.SetField(BILL_GAMEITEMKEY,	szGameItemKey);
		Bill.SetField(BILL_PRODNAME,	szGameItemName);
		Bill.SetField(BILL_IPADDR,		szUserIP);
	
		Bill.SetFieldLong(BILL_CPID,		lngCPID);
		Bill.SetFieldLong(BILL_CHARGEAMT,	lngItemPrice);
		Bill.SetFieldLong(BILL_ITEMPIECE,	lngItemPiece);
		Bill.SetFieldLong(BILL_ITEMCNT,		lngItemCnt);
		Bill.SetFieldLong(BILL_PRESENTFLAG,	lngPresentFlag);

		nTxResult = Bill.StartAction();
	}
	catch(...)
	{
		return (-2);
	}

	// ������ ����(����) ����
	// ������ RealCash, Bonus, Mileage �ܾ� �� ���ݹ�ȣ�� ���Ѵ�.
	if (nTxResult == BILL_SUCCESS)
	{
		char szTmp[32];

		Bill.GetVal(BILL_CASHREAL, szTmp, sizeof(szTmp));
		*lngRealCash = atol(szTmp);

		Bill.GetVal(BILL_CASHBONUS, szTmp, sizeof(szTmp));
		*lngBonus	= atol(szTmp);

		Bill.GetVal(BILL_MILEAGE, szTmp, sizeof(szTmp));
		*lngMileage	= atol(szTmp);

		szChargeNo[0] = NULL;
		if (szChargeNo != NULL)
			Bill.GetVal(BILL_CHARGENO,	szChargeNo, 20);
	}

	return(nTxResult);
}

/**--------------------------------------------------------------
-- ProcedureName   : CancelPurchase
-- Description     : ������� �������̽�
-- Return Value    : long
--                   0 = ����, �׿� = �����߻�
-- Parameter       :
--    [IN]szBillServer : ��������IP:Port (������ ������ ; �� �и�)
--                       (��)111.111.111.111:50050;111.111.111.111:50050
--    [IN]szUserID     : �̿���ID
--    [IN]szChargeNo   : ����� ���ݹ�ȣ (���Ž� �����ؾ� ��.)
--    [OUT]lngRealCash : ������� �� RealCash �ܾ�
--    [OUT]lngBonus    : ������� �� Bonus ĳ�� �ܾ�
--    [OUT]lngMileage  : ������� �� ���ϸ��� �ܾ�
--
-- Copyright �� 2006 by PayLetter Inc. All rights reserved.
---------------------------------------------------------------*/
long BillInterfaces::CancelPurchase
(
	char* szBillServer,	// BillServerIP:Port (111.111.111.111:50050;111.111.111.111:50050)
	char* szUserID,		// UserID
	char* szChargeNo,		// ���ݹ�ȣ

	long*		lngRealCash,	// ������� �� RealCash �ܾ�
	long*		lngBonus,		// ������� �� Bonus ĳ�� �ܾ�
	long*		lngMileage		// ������� �� ���ϸ��� �ܾ�
)	
{
	CBill		Bill;
	long		nTxResult = 0;

	// �ʱ�ȭ
	*lngRealCash	= 0;
	*lngBonus		= 0;
	*lngMileage		= 0;

	try
	{
		Bill.PutHOST(szBillServer);
		Bill.PutTxCmd(TXCMD_USECANCELDIRECT);

		Bill.SetField(BILL_SITECODE,	MY_SITECODE);
		Bill.SetField(BILL_USERID,		szUserID);
		Bill.SetField(BILL_CHARGENO,	szChargeNo);

		nTxResult = Bill.StartAction();
	}
	catch(...)
	{
		return (-2);
	}

	// ������� ����
	// ������� �� RealCash, Bonus, Mileage�� ���Ѵ�.
	if (nTxResult == BILL_SUCCESS)
	{
		char szTmp[32];

		Bill.GetVal(BILL_CASHREAL, szTmp, sizeof(szTmp));
		*lngRealCash = atol(szTmp);

		Bill.GetVal(BILL_CASHBONUS, szTmp, sizeof(szTmp));
		*lngBonus	= atol(szTmp);

		Bill.GetVal(BILL_MILEAGE, szTmp, sizeof(szTmp));
		*lngMileage	= atol(szTmp);
	}

	return(nTxResult);
}

/**--------------------------------------------------------------
-- ProcedureName   : ChargeByMileage
-- Description     : ���ϸ����� ������ ���� �������̽�
-- Return Value    : long
--                   0 = ��������, �׿� = �����߻�
-- Parameter       :
--    [IN]szBillServer : ��������IP:Port (������ ������ ; �� �и�)
--                       (��)111.111.111.111:50050;111.111.111.111:50050
--    [IN]szUserID     : �̿���ID
--    [IN]szGameItemName: ���� ������ ��
--    [IN]lngMileageAmt : ����(����) �ݾ�(�ҿ� ���ϸ���)
--    [OUT]lngMileage  : ���ϸ��� �ܾ�
--    [OUT]szChargeNo  : ���ݹ�ȣ (������� �� ��� �ʿ���.)
--
-- Copyright �� 2006 by PayLetter Inc. All rights reserved.
---------------------------------------------------------------*/
long BillInterfaces::ChargeByMileage
(
	char*	szBillServer,	// BillServerIP:Port (111.111.111.111:50050;111.111.111.111:50050)
	char*	szUserID,		// UserID
	char*	szGameItemName,	// ���� ���� ������ ��
	long	lngMileageAmt,	// ����(����) �ݾ�(�ҿ� ���ϸ���)

	long*	lngMileage,		// ������ ���ϸ��� �ܾ�
	char*	szChargeNo		// ���ݹ�ȣ(19 Bytes) (����Ҷ� �ʿ���.)
)	
{
	CBill		Bill;
	long		nTxResult = 0;

	*lngMileage		= 0;

	try
	{
		Bill.PutHOST(szBillServer);
		Bill.PutTxCmd(TXCMD_CHARGEBYMILEAGE); // chargebymileage

		Bill.SetField(BILL_SITECODE,		MY_SITECODE);
		Bill.SetField(BILL_GAMECODE,		MY_GAMECODE);
		Bill.SetField(BILL_USERID,			szUserID);
		Bill.SetField(BILL_PRODNAME,		szGameItemName);
		Bill.SetFieldLong(BILL_CHARGEAMT,	lngMileageAmt);

		nTxResult = Bill.StartAction();
	}
	catch(...)
	{
		return (-2);
	}

	// ���ϸ����� ������ ����(����) ����
	// ������ Mileage �ܾ� �� ���ݹ�ȣ�� ���Ѵ�.
	if (nTxResult == BILL_SUCCESS)
	{
		char szTmp[32];

		Bill.GetVal(BILL_MILEAGE, szTmp, sizeof(szTmp));
		*lngMileage	= atol(szTmp);

		szChargeNo[0] = NULL;
		if (szChargeNo != NULL)
			Bill.GetVal(BILL_CHARGENO,	szChargeNo, 20);
	}

	return(nTxResult);
}

/**--------------------------------------------------------------
-- ProcedureName   : PayBonus
-- Description     : ���ʽ� ĳ�� ���� �������̽�
-- Return Value    : long
--                   0 = ���޼���, �׿� = �����߻�
-- Parameter       :
--    [IN]szBillServer : ��������IP:Port (������ ������ ; �� �и�)
--                       (��)111.111.111.111:50050;111.111.111.111:50050
--    [IN]szUserID     : �̿���ID
--    [IN]szUserName   : �̿��ڸ�(ĳ���͸��� �ƴ�)
--    [IN]szReason     : ���޻���(�ݵ�� �����, 50 Bytes �̳�)
--    [IN]lngBonusAmt  : ���� ���ʽ�ĳ�� �ݾ�
--    [OUT]lngRealCash : ���ʽ� ĳ�� ���� �� RealCash �ܾ�
--    [OUT]lngBonus    : ���ʽ� ĳ�� ���� �� Bonus ĳ�� �ܾ�
--    [OUT]lngMileage  : ���ʽ� ĳ�� ���� �� ���ϸ��� �ܾ�
--
-- Copyright �� 2006 by PayLetter Inc. All rights reserved.
---------------------------------------------------------------*/
long BillInterfaces::PayBonus
(
	char*	szBillServer,	// BillServerIP:Port (111.111.111.111:50050;111.111.111.111:50050)
	char*	szUserID,		// UserID
	char*	szUserName,		// �̿��ڸ�(ĳ���͸��� �ƴ�)
	char*	szReason,		// ���޻���(�ݵ�� �����, 50 Bytes �̳�)
	long	lngBonusAmt,	// ���� ���ʽ�ĳ�� �ݾ�

	long*	lngRealCash,	// ���ʽ� ĳ�� ���� �� RealCash �ܾ�
	long*	lngBonus,		// ���ʽ� ĳ�� ���� �� Bonus ĳ�� �ܾ�
	long*	lngMileage		// ���ʽ� ĳ�� ���� �� ���ϸ��� �ܾ�
)	
{
	CBill		Bill;
	long		nTxResult = 0;

	// �ʱ�ȭ
	*lngRealCash	= 0;
	*lngBonus		= 0;
	*lngMileage		= 0;

	try
	{
		Bill.PutHOST(szBillServer);
		Bill.PutTxCmd(TXCMD_PAYCASH); // paycash

		Bill.SetField(BILL_SITECODE,	MY_SITECODE);
		Bill.SetField(BILL_USERID,		szUserID);
		Bill.SetField(BILL_USERNAME,	szUserName);
		Bill.SetField(BILL_PAYTOOLNAME,	szReason);
		Bill.SetField(BILL_PGCODE,		BILL_PGCODE_BONUSCASH);

		Bill.SetFieldLong(BILL_CASHAMT,	lngBonusAmt);
		Bill.SetFieldLong(BILL_PAYTOOL,	BILL_PAYTOOL_BONUSCASH);

		nTxResult = Bill.StartAction();
	}
	catch(...)
	{
		return (-2);
	}

	// ���ʽ� ĳ�� ���� ����
	// ������ Mileage �ܾ� �� ���ݹ�ȣ�� ���Ѵ�.
	if (nTxResult == BILL_SUCCESS)
	{
		char szTmp[32];

		Bill.GetVal(BILL_CASHREAL, szTmp, sizeof(szTmp));
		*lngRealCash = atol(szTmp);

		Bill.GetVal(BILL_CASHBONUS, szTmp, sizeof(szTmp));
		*lngBonus	= atol(szTmp);

		Bill.GetVal(BILL_MILEAGE, szTmp, sizeof(szTmp));
		*lngMileage	= atol(szTmp);
	}

	return(nTxResult);
}
