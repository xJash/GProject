#ifndef _BANKMANAGER_H
#define _BANKMANAGER_H

#include "Bank.h"

class cltTaxPaymentListDlg;

//----------------------------------------
// �������� ��ũ�� �Ѱ����ϴ� Ŭ����. 
//----------------------------------------
class cltBankManager : public cltStructureMngBasic{
public:

	cltBankManager(cltCharManager* pclCM, SI32 ranktype, TCHAR *strFileName );
	~cltBankManager();

	// ������ �ż��Ѵ�.
	BOOL CreateBank(SI32 siunique);

	// ���� ������ �����ش�
	void ShowAccountInfo( HWND hDlg );

	void DrawBankInfo( HDC hdc );

	// ������ ������ �����ش�
	void DrawFeeInfo( HWND hDlg );

	// ���� ������ �����ش�. 
	void DrawAcountInfo( HWND hDlg );

	// ������ ���� ������ ���´�. 
	BOOL GetAcountInfo( cltAccountNum* pclaccountnum, cltBankAccount* pclAcount );

	// PersonID�� ������ �� ����� cltBankAcountInfo�� ���Ѵ�. 
	// ��ü ���忡�� �˻��ϱ� ������ ����� ���ϰ� �ɸ���. 
	BOOL GetAcountInfo( SI32 personid, cltBankAccount* pclaccount );

	// ���� ȯ�� �λ縻ǥ�� . 
	void GreetingMsg(HWND hDlg);
	void Do_WM_INITDIALOG(SI32 charunique);

	// ������ ������ �����Ѵ�.
	BOOL SetFee(SI32 villageunique, cltFee* pclfee);

	// ���� ������ ������Ʈ �Ѵ�. 
	bool SetBankVary(SI32 villageunique, cltBankVary* pclvary);	

	// ���� ������ �����͸� ���Ѵ�. 
	cltBankVary* GetBankVary(SI32 villageunique);

	// ������ �������� ������ ǥ���Ѵ�. 
	void ShowBankInfo(HWND hDlg);
	// ���� �м� ������ �����ش�. 
	void ShowHelpAnalyze();

	
	// ���������� �����ش�. 
	BOOL ShowFeeRate(HWND hDlg, SI32 rate);
	// ����������� �����ش�. 
	BOOL ShowFeeRange(HWND hDlg);
	


};

#endif
