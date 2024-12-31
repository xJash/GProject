#include "NNewMarketDlg.h"

#include "Char\CharManager\CharManager.h"
#include "..\..\Server\Rank\Rank.h"

#include "../../CommonLogic/MsgType-Structure.h"

#include "..\..\Client\Music\Music.h"

#include "../Lib/JYLibFunction.h"

extern cltCommonLogic* pclClient;
extern CJYLibFunction g_JYLibFunction;

NNewMarketChiefDlg::NNewMarketChiefDlg()
{
}

NNewMarketChiefDlg::~NNewMarketChiefDlg()
{
}

void NNewMarketChiefDlg::InitDlg()
{
	SetControlMap( EDIT_FEERATE, TEXT("editbox_feerate") );
	SetControlMap( BUTTON_SETFEERATE, TEXT("button_setfeerate") );
	
	SetControlMap( BUTTON_SETFEERATE_DOWN, TEXT("button_down") );
	SetControlMap( BUTTON_SETFEERATE_UP,   TEXT("button_up") );
	
	if( pclClient->IsCountrySwitch( Switch_NewMarket ) )
	{
		((CButton*)m_pControlMap[BUTTON_SETFEERATE])->Show(false);
	}
	else
	{
		((CButton*)m_pControlMap[BUTTON_SETFEERATE_DOWN])->Show(false);
		((CButton*)m_pControlMap[BUTTON_SETFEERATE_UP])->Show(false);
	}

	cltNewMarketManager* pMarketManager = ((cltNewMarketManager*)m_pStrManager);

	TCHAR szBuffer[16];
	m_fFeeRate = (float)pMarketManager->clClientStrInfo.clNewMarketStrInfo.clFee.GetFeeRate() / 10;

	StringCchPrintf( szBuffer, sizeof(szBuffer), TEXT("%3.1f%%"), m_fFeeRate );
	SetEditText( EDIT_FEERATE, szBuffer );

	SetActionTimer( 3000 );
	SetTimerOnOff( true );
}

void NNewMarketChiefDlg::Action()
{
	SetTimerOnOff( false );

	// ���������� �ֱ�������. (ó�� ������ �ȵɶ��� �ִ�.)
	cltNewMarketManager* pMarketManager = ((cltNewMarketManager*)m_pStrManager);

	TCHAR szBuffer[16];
	m_fFeeRate = (float)pMarketManager->clClientStrInfo.clNewMarketStrInfo.clFee.GetFeeRate() / 10;

	StringCchPrintf( szBuffer, sizeof(szBuffer), TEXT("%3.1f%%"), m_fFeeRate );
	SetEditText( EDIT_FEERATE, szBuffer );
}

void NNewMarketChiefDlg::NDlgTabProc( UINT nEvent, int nControlID, CControllerObj *pControl )
{
	CASE_CONTROL( BUTTON_SETFEERATE_DOWN )
	{
		if( m_fFeeRate > MIN_FEE_RATE_NEWMARKET )
			m_fFeeRate -= 0.09f;

		TCHAR szBuffer[16];
		StringCchPrintf( szBuffer, sizeof(szBuffer), TEXT("%3.1f%%"), m_fFeeRate );
		SetEditText( EDIT_FEERATE, szBuffer );

		cltFee clFee;

		// �����ᰡ �������� Ȯ���Ѵ�. 
		if( clFee.SetFeeRateNew(m_fFeeRate*10) == TRUE)
		{
			clFee.SetMinFee(0);
			clFee.SetMaxFee(0);
			// ������ ������ ���� ��û�� �Ѵ�. 
			cltMsg clMsg( GAMEMSG_REQUEST_SETNEWMARKETFEE,  sizeof(cltFee), (BYTE*)&clFee );

			pclClient->pclCM->CR[1]->SendNetMsg((sPacketHeader*)&clMsg);
		}
		else
		{
			TCHAR* pText = GetTxtFromMgr(1439);
			SetMainExplain( pText);
		}
	}
	CASE_CONTROL( BUTTON_SETFEERATE_UP )
	{
		if( m_fFeeRate < MAX_FEE_RATE_NEWMARKET )
			m_fFeeRate += 0.11f;

		TCHAR szBuffer[16];
		StringCchPrintf( szBuffer, sizeof(szBuffer), TEXT("%3.1f%%"), m_fFeeRate );
		SetEditText( EDIT_FEERATE, szBuffer );

		cltFee clFee;

		// �����ᰡ �������� Ȯ���Ѵ�. 
		if( clFee.SetFeeRateNew(m_fFeeRate*10) == TRUE)
		{
			clFee.SetMinFee(0);
			clFee.SetMaxFee(0);
			// ������ ������ ���� ��û�� �Ѵ�. 
			cltMsg clMsg( GAMEMSG_REQUEST_SETNEWMARKETFEE,  sizeof(cltFee), (BYTE*)&clFee );
			pclClient->pclCM->CR[1]->SendNetMsg((sPacketHeader*)&clMsg);
		}
		else
		{
			TCHAR* pText = GetTxtFromMgr(1439);
			SetMainExplain( pText);
		}
	}
	CASE_CONTROL( BUTTON_SETFEERATE )
	{
		int id = 1;
	
		// �ڽ��� (��)����� �̹� ��ϵǾ� �־��  �Ѵ�. 
		{
			cltSimpleRank clrank( m_pStrManager->siRankType, m_pStrManager->siVillageUnique);
			if( pclCM->CR[id]->pclCI->clCharRank.IsSame(&clrank) == FALSE )
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
		if( clFee.SetFeeRateNew((SI32)( minfee * 10)) == TRUE)
		{
			// ������ ������ ���� ��û�� �Ѵ�. 
			cltMsg clMsg( GAMEMSG_REQUEST_SETNEWMARKETFEE,  sizeof(cltFee), (BYTE*)&clFee );
			
			pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		}
		else
		{
			TCHAR* pText = GetTxtFromMgr(1439);
			SetMainExplain( pText);
		}
	}
}