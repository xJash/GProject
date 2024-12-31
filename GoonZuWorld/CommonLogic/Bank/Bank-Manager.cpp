//---------------------------------
// 2003/5/28 ���°�
//---------------------------------
#include <CommonLogic.h>
#include "Char\CharClient\Char-Client.h"

#include "Bank-Manager.h"

#include "..\..\Resource.h"

#include "../../CommonLogic/MsgType-Bank.h"
#include "../../CommonLogic/MsgType-Structure.h"

#include "../CityHall/TaxpaymentListDlg.h"


extern cltCommonLogic* pclClient;

//------------------------------------------
// cltBankManager
//------------------------------------------
cltBankManager::cltBankManager(cltCharManager* pclcm, SI32 ranktype, TCHAR *strFileName ) : cltStructureMngBasic( MAX_BANK_TAB_NUMBER, pclcm, ranktype, strFileName )
{
}


cltBankManager::~cltBankManager()
{

}


// ������ �ż��Ѵ�.
BOOL cltBankManager::CreateBank(SI32 siunique)
{
	
	// ������ �����. 
	if(pclStruct[siunique] == NULL)
	{
		pclStruct[siunique] = new cltBank(siunique);
		return TRUE;
	}
		
	return FALSE;
}



// ���� ������ �����ش�. 
void cltBankManager::DrawAcountInfo(HWND hDlg)
{

}

// ������ ������ �����ش�
void cltBankManager::DrawFeeInfo( HWND hDlg )
{
/*
	RECT rect;
	TCHAR buffer[256];
	SI32 money;

	
	SI32 id = cltCharCommon::CharUniqueInfo[CharUnique];

	BOOL bNoFee = ( pclCM->CR[id]->pclCI->clBank.clAccountNum.GetVillageUnique()
					== pclCM->CR[id]->GetCurrentVillageUnique() );

	BOOL bAccount = pclCM->CR[id]->pclCI->clBank.clAccountNum.IsValid();

	HDC hdc = GetDC( hDlg );

	// ������ ǥ��
	DrawBox1( hdc, 26, 336, 164, 34, RGB( 255, 255, 255 ), RGB( 0, 0, 0 ) );

	GetWindowText( m_wndEditMoney, buffer, 10 );
	money	=	_tstoi(buffer);

	SI32 fee = clClientStrInfo.clBankStrInfo.clFee.CalcFee(money); 

	if( bNoFee || bAccount == FALSE ) fee = 0;

	sprintf( buffer, TEXT("%d"), fee );	

	SetRect( &rect, 26 + 5, 336 + 5, 26 + 164, 336 + 34 );

	DrawText( hdc, buffer, _tcslen( buffer ), &rect, DT_LEFT | DT_VCENTER | DT_SINGLELINE );


	// ������ ����
	DrawBox1( hdc, 26, 382, 164, 34, RGB( 255, 255, 255 ), RGB( 0, 0, 0 ) );

	float feerate = (float)clClientStrInfo.clBankStrInfo.clFee.GetFeeRate() / 10;

	if( bNoFee || bAccount == FALSE ) {
		strcpy( buffer, TEXT("�����ᰡ �����ϴ�") );
	} else {
		sprintf(buffer, TEXT("%3.1f%c(%d��%d��)"), feerate, '%', clClientStrInfo.clBankStrInfo.clFee.GetMinFee(), clClientStrInfo.clBankStrInfo.clFee.GetMaxFee());
	}
	
	SetRect( &rect, 26 + 5, 382 + 5, 26 + 164, 382 + 34 );
	DrawText( hdc, buffer, _tcslen( buffer ), &rect, DT_LEFT | DT_VCENTER | DT_SINGLELINE );

	ReleaseDC( hDlg, hdc );
*/
}


void cltBankManager::DrawBankInfo( HDC hdc )
{
	/*
	RECT rect;

	DrawBox1( hdc, 16, 134, 348, 294, RGB( 255, 255, 255 ), RGB( 0, 0, 0 ) );

	
	TCHAR buffer[256];
	

	cltMoney margin		= clClientStrInfo.clCommonInfo.clMoney.Minus(&clClientStrInfo.clBankStrInfo.clTotalInputMoney);
	SI32 marginrate		= clClientStrInfo.clBankStrInfo.clTotalInputMoney.GetPercent(&margin);
	
	//--------------------------------
	// ������� ���� ���ϱ� 
	//--------------------------------
	cltSimplePerson* pclperson;
	pclperson = (cltSimplePerson*)&pclClient->pclVillageManager->pclVillageInfo[siVillageUnique]->clVillageVary.clRankPerson[RANKTYPE_BANK];

	TCHAR szChiefName[128];
	if(pclperson->GetPersonID())
	{
		wsprintf(szChiefName, TEXT("[%s], %d"), 
			pclperson->GetName(),
			pclperson->GetPersonID());
	}
	else
	{
		wsprintf( szChiefName, TEXT("%s"), TEXT("�����������") );
	}

	sprintf(buffer, TEXT("�������:%s\r\n�ѿ��ݾ�:%I64d ��\r\n�����ܾ�:%I64d ��\r\n������:%d �ۼ�Ʈ"), 
		szChiefName, 
		clClientStrInfo.clBankStrInfo.clTotalInputMoney.itMoney, 
		clClientStrInfo.clCommonInfo.clMoney.itMoney, 
		marginrate );
	
	//SetRect( &rect, 40, 150, 348, 294 );

	//DrawText( hdc, buffer, _tcslen( buffer ), &rect, DT_LEFT );
*/
}

// ���� �м� ������ �����ش�. 
void cltBankManager::ShowHelpAnalyze()
{
}


// ������ ���� ������ ���´�. 
BOOL cltBankManager::GetAcountInfo(cltAccountNum* pclaccountnum, cltBankAccount* pclAcountInfo)
{
	if(pclaccountnum == NULL)return FALSE;
	if(pclAcountInfo == NULL)return FALSE;

	SI32 ref = pclaccountnum->GetVillageUnique() ;
	if(ref == -1)return FALSE;
	if(pclStruct[ref] == NULL)return FALSE;

	return pclStruct[ref]->GetAcountInfo(pclaccountnum, pclAcountInfo);
}


// ���� ȯ�� �λ縻ǥ�� . 
void cltBankManager::GreetingMsg(HWND hDlg)
{
	TCHAR* pText = GetTxtFromMgr(1452);
	SetMainExplain(hDlg, pText);
}

void cltBankManager::Do_WM_INITDIALOG(SI32 charunique)
{
	cltStructureMngBasic::Do_WM_INITDIALOG(charunique);
}

// PersonID�� ������ �� ����� cltBankAcountInfo�� ���Ѵ�. 
// ��ü ���忡�� �˻��ϱ� ������ ����� ���ϰ� �ɸ���. 
BOOL cltBankManager::GetAcountInfo(SI32 personid, cltBankAccount* pclinfo)
{
	SI32 i;

	for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
	{
		// �� ���忡 �ش� PersonID�� �ִ��� Ȯ���Ѵ�. 
		if(pclStruct[i] && pclStruct[i]->GetAcountInfo(personid, pclinfo) == TRUE)
		{
			return TRUE;
		}
	}

	return FALSE;
}

// ������ ������ �����Ѵ�.
BOOL cltBankManager::SetFee(SI32 villageunique, cltFee* pclfee)
{
	return pclStruct[villageunique]->SetFee(pclfee);
}


