#include "StrSubResignChiefDlg.h"

#include "Char\CharManager\CharManager.h"
#include "..\..\Server\Rank\Rank.h"

#include "../../CommonLogic/MsgType-Structure.h"

#include "..\..\Client\Music\Music.h"

#include "../Lib/JYLibFunction.h"

extern cltCommonLogic* pclClient;
extern CJYLibFunction g_JYLibFunction;


NStrSubResignChiefDlg::NStrSubResignChiefDlg()
{
}

NStrSubResignChiefDlg::~NStrSubResignChiefDlg()
{
}

void NStrSubResignChiefDlg::InitDlg()
{
	SetControlMap( BUTTON_RESIGN, TEXT("button_resign") );
}

void NStrSubResignChiefDlg::NDlgTabProc( UINT nEvent, int nControlID, CControllerObj *pControl )
{
	
	CASE_CONTROL( BUTTON_RESIGN )
	{
		// ������ (��)������� �������� ��û�Ѵ�.
		SI32 id = 1;
		if(id)
		{
			//// �ڽ��� (��)����� �̹� ��ϵǾ� �־��  �Ѵ�. 
			//cltSimpleRank clrank( m_pStrManager->siRankType, m_pStrManager->siVillageUnique);
			//if( pclCM->CR[id]->pclCI->clCharRank.IsSame(&clrank) == TRUE )
			//{

			//	cltMsg clMsg(GAMEMSG_REQUEST_RESIGN, 
			//		sizeof(cltSimpleRank), (BYTE*)&clrank);

			//	pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
			//}
			//else
			//{
			//	TCHAR* pText;
			//	if( m_pStrManager->siRankType == RANKTYPE_CITYHALL ) pText = GetTxtFromMgr(1547);
			//	else pText = GetTxtFromMgr(1440);
			//	SetMainExplain(pText);
			//}

		}		

	}
}