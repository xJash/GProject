#include "NSummonMarketDlg.h"

#include "../../../CommonLogic/Msg/MsgType-SummonMarket.h"
#include "../../../CommonLogic/MsgType-Structure.h"
#include "../../../CommonLogic/CityHall/TaxpaymentListDlg.h"

extern CJYLibFunction g_JYLibFunction;
extern cltCommonLogic* pclClient;

NSummonMarketInfoDlg::NSummonMarketInfoDlg()
{
}

NSummonMarketInfoDlg::~NSummonMarketInfoDlg()
{
	
}

void NSummonMarketInfoDlg::InitDlg()
{
	// �忹�� �Ŵ���
	cltSummonMarketManager *pSummonManager = ((cltSummonMarketManager *)m_pStrManager);
	if( pSummonManager == NULL ) return;

	SetControlMap( EDITBOX_STRDURA,  "editbox_strdura" );
	SetControlMap( EDITBOX_STRCHIEF,  "editbox_strchief" );
	SetControlMap( EDITBOX_STRMONEY,  "editbox_strmoney" );
	SetControlMap( BUTTON_TAXLIST, "button_taxlist");

}

void NSummonMarketInfoDlg::NDlgTabProc( UINT nEvent, int nControlID, CControllerObj *pControl )
{
	// �忹�� �Ŵ���
	cltSummonMarketManager *pSummonMarketManager = ((cltSummonMarketManager *)m_pStrManager);

	CASE_CONTROL( BUTTON_TAXLIST )
		{
			char* pText = GetTxtFromMgr(471);
			pSummonMarketManager->pclTaxPaymentDlg->Create( NULL, NULL, pSummonMarketManager, pText );
		}
}

void NSummonMarketInfoDlg::Action()
{
	// �忹�� �Ŵ���
	cltSummonMarketManager *pSummonMarketManager = ((cltSummonMarketManager *)m_pStrManager);

	char buffer[256];

	// �ǹ� �������� ǥ���Ѵ�
	sprintf( buffer, "%d/%d", pSummonMarketManager->clClientStrInfo.clCommonInfo.siStrDura, 10000 );
	SetEditText( EDITBOX_STRDURA, buffer );

	// �忹������� �̸��� ǥ���Ѵ�. 
	if(pSummonMarketManager->UpdateChiefSwitch == true)
	{
		pSummonMarketManager->UpdateChiefSwitch = false;

		// ���� �����ش�. 
		if(pSummonMarketManager->siVillageUnique > 0)
		{
			ShowChief( &pclClient->pclVillageManager->pclVillageInfo[pSummonMarketManager->siVillageUnique]->clVillageVary.clRankPerson[RANKTYPE_PORT], 
				pclClient->pclVillageManager->pclVillageInfo[pSummonMarketManager->siVillageUnique]->RankAccountID[RANKTYPE_PORT]
				);
		}
	}

	// �������� �ڱ��� ǥ���Ѵ�.  
	memset( buffer, 0, 256 );
	char* pText = GetTxtFromMgr(611);
	g_JYLibFunction.SetNumUnit( pSummonMarketManager->clClientStrInfo.clCommonInfo.clMoney.itMoney, buffer, pText );
	SetEditText( EDITBOX_STRMONEY, buffer );
}

// ���� ������ �����ش�. 
BOOL NSummonMarketInfoDlg::ShowChief( cltSimplePerson* pclperson, char *paccountid)
{
	char buffer[256];
	
	if(pclperson->GetPersonID())
	{
		wsprintf(buffer, "%s", pclperson->GetName());
	}
	else
	{
		char* pText = GetTxtFromMgr(1287);
		wsprintf(buffer, pText);
	}

	SetEditText( EDITBOX_STRCHIEF, buffer );

	// Chief SummonMarketrait Draw Routine!!
	//DrawSummonMarketrait(paccountid);
	
	return TRUE;
}
