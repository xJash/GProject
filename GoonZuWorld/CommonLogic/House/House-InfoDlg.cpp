//---------------------------------
// 2003/6/26 ���°�
//---------------------------------
#include <CommonLogic.h>
#include "Char\CharCommon\Char-Common.h"

#include "..\..\Common\Util\Control\Control.h"

#include "..\..\Resource.h"

#include "House.h"

#include "..\CityHall\TaxPaymentListDlg.h"


extern cltCommonLogic* pclClient;


BOOL CALLBACK cltHouseManager::StaticHouseInfoDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	return pclClient->pclHouseManager->HouseInfoDlgProc(hDlg, iMsg, wParam, lParam);
}

BOOL CALLBACK cltHouseManager::HouseInfoDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	SI32 id=0;
	
	switch(iMsg)
	{
	case WM_INITDIALOG:
		{
			// Ÿ�̸Ӹ� �����Ѵ�. 
			SetTimer(hDlg, 1, 500, NULL);

		}
		return TRUE;
		
	case WM_TIMER:
		{
			char buffer[256];

			// �ǹ� �������� ǥ���Ѵ�
			sprintf( buffer, "%d/%d", clClientStrInfo.clCommonInfo.siStrDura, 10000 );
			SetDlgItemText( hDlg, IDC_EDIT_STRDURA, buffer );

			// ��������� �̸��� ǥ���Ѵ�. 
			if(UpdateChiefSwitch == true)
			{
				UpdateChiefSwitch = false;

				// ���� �����ش�. 
				if(siVillageUnique > 0)
				{
					ShowChief(hDlg, IDC_EDIT_STRCHIEF, 
						&pclClient->pclVillageManager->pclVillageInfo[siVillageUnique]->clVillageVary.clRankPerson[RANKTYPE_HOUSE], 
						pclClient->pclVillageManager->pclVillageInfo[siVillageUnique]->RankAccountID[RANKTYPE_HOUSE]
						);
				}
			}

			// �������� �ڱ��� ǥ���Ѵ�. 
			char* pText = GetTxtFromMgr(611);
			g_JYLibFunction.SetNumUnit( clClientStrInfo.clCommonInfo.clMoney.itMoney, buffer, pText );
			SetDlgItemText(hDlg, IDC_EDIT_STRMONEY, buffer);

		}
		return TRUE;

	case WM_CHAR:
		return TRUE;

	case WM_DESTROY:
		// Ÿ�̸Ӹ� �����Ѵ�. 
		KillTimer(hDlg, 1);

		DeleteTabDlg();
		return TRUE;

	case WM_NOTIFY:
		{
		}
		return TRUE;

	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDC_BUTTON_TAXLIST:
			{
				char* pText = GetTxtFromMgr(370);
				pclTaxPaymentDlg->Create( NULL, hDlg, this, pText );
			}
			break;
			
		}
		return FALSE;
	}

	return FALSE;
}
