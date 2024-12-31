#ifndef __BILL_INTERFACES_H__
#define __BILL_INTERFACES_H__


// TX ��ɾ�
#define	TXCMD_ACCOUNTINFO		"accountinfo"		// �ܾ���ȸ ��ɾ�
#define	TXCMD_CHARGEGAMEITEM	"chargegameitem"	// ����(����) ��ɾ�
#define TXCMD_USECANCELDIRECT	"usecanceldirect"	// ����(����)���
#define	TXCMD_CHARGEBYMILEAGE	"chargebymileage"	// ���ϸ����� �����ϱ�
#define	TXCMD_PAYCASH			"paycash"			// ���ʽ�ĳ�� ����

#define	MY_SITECODE				"ndoor"		// 5 bytes
#define	MY_GAMECODE				"goonzu"	// 20 bytes

#define BILL_SUCCESS			0
#define	BILL_PAYTOOL_BONUSCASH	4

#define	BILL_PGCODE_BONUSCASH	"bonuscash"

#define BILL_PGCODE				"pgcode"
#define BILL_USERID				"userid"
#define BILL_USERNAME			"username"
#define BILL_SITECODE			"sitecode"
#define BILL_CASHREAL			"cashreal"
#define BILL_CASHBONUS			"cashbonus"
#define BILL_MILEAGE			"mileage"
#define BILL_ITEMID				"itemid"
#define BILL_GAMEITEMKEY		"gameitemkey"
#define BILL_PRESENTFLAG		"presentflag"
#define BILL_PRODNAME			"prodname"
#define BILL_CHARGEAMT			"chargeamt"
#define BILL_ITEMPIECE			"itempiece"
#define BILL_ITEMCNT			"itemcnt"
#define BILL_GAMECODE			"gamecode"
#define BILL_IPADDR				"ipaddr"
#define BILL_CHARGENO			"chargeno"
#define BILL_PAYTOOL			"paytool"
#define BILL_PAYTOOLNAME		"paytoolname"
#define BILL_CASHAMT			"cashamt"
#define BILL_CPID				"cpid"

class BillInterfaces
{
public:
	// �ܾ���ȸ �������̽�
	static long GetUserBalance
		(
			char*	szBillServer,	// BillServerIP:Port (111.111.111.111:50090;111.111.111.111:50090)
			char*	szUserID,		// UserID

			long*	lngRealCash,	// RealCash �ܾ�
			long*	lngBonus,		// Bonus ĳ�� �ܾ�
			long*	lngMileage		// ���ϸ��� �ܾ�
		);
	// ������ ����(����) �������̽�
	static	long BillInterfaces::ChargeItem
		(
			char*	szBillServer,	// BillServerIP:Port (111.111.111.111:50090;111.111.111.111:50090)
			char*	szUserID,		// UserID

			char*	szGameItemKey,	// ���� ������ Ű
			char*	szGameItemName,	// ���� ������ ��
			char*	szUserIP,		// �̿����� IP ��巹��
			long	lngItemPrice,	// ����(����) �ݾ�
			long	lngItemPiece,	// 1�� ����
			long	lngItemCnt,		// ������ ����
			long	lngPresentFlag,	// ���� ����(�����̸� 1, �ƴϸ� 0)
			long	IngCPID,		// ������ ���� CP(1:����,2:��Ʋ��Ƽī)

			long*	lngRealCash,	// RealCash �ܾ�
			long*	lngBonus,		// Bonus ĳ�� �ܾ�
			long*	lngMileage,		// ���ϸ��� �ܾ�
			char*	szChargeNo		// ���ݹ�ȣ(19 Bytes) (����Ҷ� �ʿ���.)
		);
	// ���� ��� �������̽�
	static	long BillInterfaces::CancelPurchase
		(
			char*	szBillServer,	// BillServerIP:Port (111.111.111.111:50090;111.111.111.111:50090)
			char*	szUserID,		// UserID
			char*	szChargeNo,		// ���ݹ�ȣ

			long*	lngRealCash,			// ������� �� RealCash �ܾ�
			long*	lngBonus,				// ������� �� Bonus ĳ�� �ܾ�
			long*	lngMileage			// ������� �� ���ϸ��� �ܾ�
		);
	// ���ϸ����� ������ ���� �������̽�
	static	long BillInterfaces::ChargeByMileage
		(
			char*	szBillServer,	// BillServerIP:Port (111.111.111.111:50090;111.111.111.111:50090)
			char*	szUserID,		// UserID

			char*	szGameItemName,	// ���� ���� ������ ��
			long	lngMileageAmt,	// ����(����) �ݾ�(�ҿ� ���ϸ���)

			long*	lngMileage,		// ������ ���ϸ��� �ܾ�
			char*	szChargeNo		// ���ݹ�ȣ(19 Bytes) (����Ҷ� �ʿ���.)
		);
	// ���ʽ� ĳ�� ���� �������̽�
	static	long BillInterfaces::PayBonus
		(
			char*	szBillServer,	// BillServerIP:Port (111.111.111.111:50090;111.111.111.111:50090)
			char*	szUserID,		// UserID
			char*	szUserName,		// �̿��ڸ�(ĳ���͸��� �ƴ�)
			char*	szReason,		// ���޻���(50 Bytes �̳�)
			long	lngBonusAmt,	// ���� ���ʽ�ĳ�� �ݾ�

			long*	lngRealCash,	// ���ʽ� ĳ�� ���� �� RealCash �ܾ�
			long*	lngBonus,		// ���ʽ� ĳ�� ���� �� Bonus ĳ�� �ܾ�
			long*	lngMileage		// ���ʽ� ĳ�� ���� �� ���ϸ��� �ܾ�
		);
};

#endif
