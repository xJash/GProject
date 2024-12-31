#include "NLandDlg.h"

#include "../../InterfaceMgr/Interface/ListView.h"
#include "../StrBaseDlg/StrInventory.h"

#include "Char\CharManager\CharManager.h"
#include "..\..\Server\Rank\Rank.h"

#include "../../CommonLogic/MsgType.h"
#include "../../CommonLogic/MsgType-Structure.h"
#include "../../CommonLogic/Msg/MsgType-Land.h"
#include "../../CommonLogic/MsgType-Bank.h"

#include "../Lib/JYLibFunction.h"
#include "..\..\Client\Music\Music.h"
#include "../../CommonLogic/StructureClass/StructureClass.h"

#include "../../Client/InterfaceMgr/InterfaceMgr.h"

extern cltCommonLogic* pclClient;
extern CJYLibFunction g_JYLibFunction;

NLandUserDlg::NLandUserDlg()
{
}

NLandUserDlg::~NLandUserDlg()
{
	
}

void NLandUserDlg::InitDlg()
{

	cltLandManager *pLandManager = ((cltLandManager *)m_pStrManager);

	SetControlMap( EDIT_RENT_FEE, TEXT("editbox_rent_fee") );
	SetControlMap( EDIT_RENT_PERIOD, TEXT("editbox_rent_period") );

	SetControlMap( EDIT_CONTRACT, TEXT("editbox_contract") );

	SetControlMap( BUTTON_APPLY, TEXT("button_apply") );
	SetControlMap( BUTTON_CANCEL_APPLY, TEXT("button_cancel_apply") );


	ShowRentContractInUser();


}

void NLandUserDlg::ShowRentContractInUser()
{

	cltLandManager *pLandManager = ((cltLandManager *)m_pStrManager);

	TCHAR buffer[1024];

	StringCchPrintf(buffer, 1024, TEXT("%d"), pLandManager->clClientStrInfo.clLandStrInfo.clRentContract.siRentFee);
	SetEditText( EDIT_RENT_FEE, buffer );

	StringCchPrintf(buffer, 1024, TEXT("%d"), pLandManager->clClientStrInfo.clLandStrInfo.clRentContract.siRentPeriod);
	SetEditText( EDIT_RENT_PERIOD, buffer );

	TCHAR* pText = GetTxtFromMgr(1828);
	StringCchPrintf(buffer, 1024, pText);
	SetEditText( EDIT_CONTRACT, buffer );

}

void NLandUserDlg::Action()
{
	if( m_pBaseDlg->m_dwActionCount % 4 ) return;

	ShowRentContractInUser();
}


void NLandUserDlg::NDlgTabProc( UINT nEvent, int nControlID, CControllerObj *pControl )
{
	cltLandManager *pLandManager = ((cltLandManager *)m_pStrManager);
	cltClient *pclclient = (cltClient*)pclClient;

	CASE_CONTROL( BUTTON_APPLY )
	{
		// ����� �Ǵ� ĳ������ ���̵� ���Ѵ�. 
		SI32 id = 1;

        //���� ����.[2006.06.08 ����]
		BOOL bAccount = pclCM->CR[id]->pclCI->clBank.clAccountNum.IsValid();
		//���� ����

		
		// �ʿ� �ڰ� ������ ������Ű�� �ִ��� Ȯ���Ѵ�. 
		if( pclClient->pclCM->CR[id]->pclCI->clIP.GetLevel() < LEVELLIMIT_USE_LAND)
		{
			TCHAR buffer[256];
			TCHAR* pText = GetTxtFromMgr(1051);
			StringCchPrintf(buffer, 256, pText, LEVELLIMIT_USE_LAND);
			SetMainExplain( buffer);

			pclClient->PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_FAILURE")), 0, 0);
			return;
		}

		// ���� ���°� ���ٸ� ����[2006.06.08 ����]
		// ���� - ���°� ���ٸ� ���尳�� ��û �˾�â�� ��쵵�� ������ (PCK - 08.05.08)
		
		SI32 siBankCheck = pclClient->pclVillageManager->IsThereStructure(pclCM->CR[id]->GetCurrentVillageUnique(),RANKTYPE_BANK);

		if( bAccount==FALSE)
		{	
			if(pclCM->CR[id]->pclCI->clBank.clAccountNum.siVillageUnique == 0 && siBankCheck==1)
			{
				pclClient->PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_FAILURE")), 0, 0);
				TCHAR* pText = GetTxtFromMgr(1669);
				SetMainExplain(pText);

				stMsgBox MsgBox;
				// ���� dialog�� �� â ���� Child Dialog�϶�
				TCHAR* pTitle = GetTxtFromMgr(3942);
				pText = GetTxtFromMgr(8417);
				CControllerMgr *pParent = NULL;
				pParent = this->GetParentDialog();
				if(pParent == NULL ) return;
				MsgBox.Set( pParent, pTitle, pText, MSGBOX_TYPE_YESNO, 0 );
				BYTE TempBuffer[ 128 ];

				SI16 Size = sizeof( id );
				memcpy( TempBuffer, &id, sizeof( id ) );			
				pclclient->SetMsgBox( &MsgBox, TempBuffer, Size );
				return;
			}

			if(pclCM->CR[id]->pclCI->clBank.clAccountNum.siVillageUnique == 0)
			{
				TCHAR* pTitle = GetTxtFromMgr(3942);
				TCHAR* pText = GetTxtFromMgr(8418);
				pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText(pTitle, pText);
				return;
			}
		}

		//���� ������ ���� ���� �Ӵ�Ẹ�� ������ �˻��Ͽ� ������ ����[2006.06.08 ����]
		if( pclClient->pclCM->CR[id]->GetBankMoney() < pLandManager->clClientStrInfo.clLandStrInfo.clRentContract.siRentFee)
		{
			
			TCHAR* pText = GetTxtFromMgr(7115);
			
			SetMainExplain( pText);


			pclClient->PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_FAILURE")), 0, 0);
			return;
		}
		
		

		// �Ӵ� �Ⱓ�� Ȯ���Ѵ�.
		if( pLandManager->clClientStrInfo.clLandStrInfo.clRentContract.siRentPeriod == 0)
		{
			TCHAR* pText = GetTxtFromMgr(1827);
			SetMainExplain(pText);
			pclClient->PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_FAILURE")), 0, 0);
			return;
		}

		// �Ӵ��û�� �����Ѵ�. 
		cltGameMsgRequest_LandRentApply sendmsg( &pLandManager->clClientStrInfo.clLandStrInfo.clRentContract );
		cltMsg clMsg(GAMEMSG_REQUEST_LAND_RENTAPPLY, sizeof(sendmsg), (BYTE*)&sendmsg);
		pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	}

	else CASE_CONTROL( BUTTON_CANCEL_APPLY )
	{
		SI32 id = 1;

		/// ��� ��û�� ������ ������. 				
		cltMsg clMsg( GAMEMSG_REQUEST_LAND_CANCELAPPLY, 0 );
		pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	}
}

void NLandUserDlg::RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen )
{
	cltClient *pclclient = (cltClient*)pclClient;
	switch( MsgIndex )
	{
	case 0:
		{
			if ( pData == NULL || DataLen < 1 )
			{
				return;
			}

			if ( RetValue )
			{
				SI32 id = *((SI32*)pData);

				if(id)
				{
					cltGameMsgRequest_CreateBankAccount clinfo( pclCM->CR[id]->GetCurrentVillageUnique() );

					// ���� ���� ��û 
					cltMsg clMsg( GAMEMSG_REQUEST_CREATEBANKACCOUNT, sizeof(clinfo), (BYTE*)&clinfo);			
					pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);	
				}
			}
		}
		break;
	}
}