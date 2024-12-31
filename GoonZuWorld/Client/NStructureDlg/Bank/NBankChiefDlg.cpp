#include "NBankDlg.h"

#include "Char\CharManager\CharManager.h"
#include "..\..\Server\Rank\Rank.h"

#include "../../CommonLogic/MsgType-Structure.h"

#include "..\..\Client\Music\Music.h"

#include "../Lib/JYLibFunction.h"

extern cltCommonLogic* pclClient;
extern CJYLibFunction g_JYLibFunction;

NBankChiefDlg::NBankChiefDlg()
{
}

NBankChiefDlg::~NBankChiefDlg()
{
}

void NBankChiefDlg::InitDlg()
{
	SetControlMap( EDIT_FEERATE, TEXT("editbox_feerate") );
	SetControlMap( BUTTON_SETFEERATE, TEXT("button_setfeerate") );
}

void NBankChiefDlg::NDlgTabProc( UINT nEvent, int nControlID, CControllerObj *pControl )
{

	CASE_CONTROL( BUTTON_SETFEERATE )
	{
		int id = 1;
		if(id == 0)return;

		// �ڽ��� (��)����� �̹� ��ϵǾ� �־��  �Ѵ�. 
		{
			cltSimpleRank clrank( m_pStrManager->siRankType, m_pStrManager->siVillageUnique);
			if( pclCM->CR[1]->pclCI->clCharRank.IsSame(&clrank) == FALSE )
			{
				TCHAR* pText;
				if( m_pStrManager->siRankType == RANKTYPE_CITYHALL ) pText = GetTxtFromMgr(1547);
				else pText = GetTxtFromMgr(1440);
				SetMainExplain(pText);
				return;
			}
		}

		cltFee clFee;

		// �����ᰡ �������� Ȯ���Ѵ�. 
		float minfee = (float)_tstof( GetEditText( EDIT_FEERATE ) );
		if( clFee.SetFeeRate((SI32)(minfee*10)) == TRUE)
		{
			// ������ ������ ���� ��û�� �Ѵ�. 
			cltMsg clMsg(GAMEMSG_REQUEST_SETBANKFEE,  
				sizeof(cltFee), (BYTE*)&clFee);
			
			pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		}
		else
		{
			TCHAR* pText = GetTxtFromMgr(1439);
			SetMainExplain( pText);
		}

	}


}