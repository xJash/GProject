//---------------------------------
// 2003/5/30 ���°�
//---------------------------------
#include <CommonLogic.h>
#include "Char\CharCommon\Char-Common.h"

#include "Bank-Manager.h"
#include "..\..\Common\Util\Control\Control.h"
#include "..\..\Server\Rank\Rank.h"

#include "..\..\Resource.h"

#include "../CityHall/TaxpaymentListDlg.h"

extern cltCommonLogic*		pclClient;


// ������ �������� ������ ǥ���Ѵ�. 
void cltBankManager::ShowBankInfo(HWND hDlg)
{
	char buffer[256]="";

	// �ǹ� �������� ǥ���Ѵ�
	sprintf( buffer, "%d/%d", clClientStrInfo.clCommonInfo.siStrDura, 10000 );
	SetDlgItemText( hDlg, IDC_EDIT_STRDURA, buffer );

	// ����� �̸��� ǥ���Ѵ�. 
	if(UpdateChiefSwitch == true)
	{
		UpdateChiefSwitch = false;

		// ���� �����ش�. 
		if(siVillageUnique > 0)
		{
			ShowChief(hDlg, IDC_EDIT_STRCHIEF, 
				&pclClient->pclVillageManager->pclVillageInfo[siVillageUnique]->clVillageVary.clRankPerson[RANKTYPE_BANK],
				pclClient->pclVillageManager->pclVillageInfo[siVillageUnique]->RankAccountID[RANKTYPE_BANK]
				);
		}
	}

	char* pText = GetTxtFromMgr(611);

	g_JYLibFunction.SetNumUnit( clClientStrInfo.clCommonInfo.clMoney.itMoney, buffer, pText );
	SetDlgItemText( hDlg, IDC_EDIT_STRMONEY, buffer );

	
	g_JYLibFunction.SetNumUnit( clClientStrInfo.clBankStrInfo.clTotalInputMoney.itMoney, buffer, pText );
	SetDlgItemText( hDlg, IDC_EDIT_BANK_TOTAL_INPUT_MONEY, buffer );

	// ���ͱ� 
	__int64 margin = clClientStrInfo.clCommonInfo.clMoney.itMoney - clClientStrInfo.clBankStrInfo.clTotalInputMoney.itMoney;
	g_JYLibFunction.SetNumUnit( margin, buffer, pText);
	SetDlgItemText( hDlg, IDC_EDIT_BANK_PROFITRATE, buffer );

}

