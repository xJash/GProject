#include <CommonLogic.h>
#include "Char\CharCommon\Char-Common.h"

#include "..\..\Common\Util\Control\Control.h"

#include "..\..\Resource.h"

#include "Market.h"
#include "Control.h"
#include "..\..\Client\FontManager\FontManager.h"

#include "MsgType-Structure.h"

#include "../CityHall/TaxpaymentListDlg.h"

//--------------------------------------
// Common
//--------------------------------------
#include "PersonInfo.h"
#include "Char\CharManager\CharManager.h"

extern cltCommonLogic* pclClient;

// ���������� �����ش�. 
BOOL cltMarketManager::ShowFeeRate(HWND hDlg, SI32 rate)
{
	char buffer[256];
	HWND hwnd;
	
	float feerate = (float)rate/10;
	
	sprintf(buffer, "%3.1f",feerate); 

	hwnd = GetDlgItem( hDlg, IDC_EDIT_MARKET_FEERATE );
	SetWindowText( hwnd, buffer);

	return TRUE;
}

// ����������� �����ش�. 
BOOL cltMarketManager::ShowFeeRange(HWND hDlg)
{
	char buffer[256]="";
	HWND hwnd=NULL;
/*
	// ���� ������. 
	sprintf(buffer, "%d", clClientStrInfo.clMarketStrInfo.clFee.GetMinFee());
	
	hwnd = GetDlgItem( hDlg, IDC_EDIT_MARKETMINFEE );
	SetWindowText( hwnd, buffer);

	// �ְ� ������. 
	sprintf(buffer, "%d", clClientStrInfo.clMarketStrInfo.clFee.GetMaxFee());

	hwnd = GetDlgItem( hDlg, IDC_EDIT_MARKETMAXFEE );
	SetWindowText( hwnd, buffer);
*/
	return TRUE;
}
