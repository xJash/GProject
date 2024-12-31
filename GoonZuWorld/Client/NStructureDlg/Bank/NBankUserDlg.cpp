#include "NBankDlg.h"

#include "Char\CharManager\CharManager.h"
#include "..\..\Server\Rank\Rank.h"

#include "../../CommonLogic/MsgType-Bank.h"
#include "../../CommonLogic/MsgType-Structure.h"

#include "../Lib/JYLibFunction.h"

#include "../../Client/InterfaceMgr/InterfaceMgr.h"

extern cltCommonLogic* pclClient;
extern CJYLibFunction g_JYLibFunction;

NBankUserDlg::NBankUserDlg()
{
}

NBankUserDlg::~NBankUserDlg()
{
}

void NBankUserDlg::InitDlg()
{
	SetControlMap( BUTTON_INPUT_ALL, TEXT("button_input_all") );
	SetControlMap( BUTTON_INPUT, TEXT("button_input") );
	SetControlMap( BUTTON_OUTPUT, TEXT("button_output") );
	SetControlMap( BUTTON_OUTPUT_ALL, TEXT("button_output_all") );
	SetControlMap( BUTTON_CREATE_BANKBOOK, TEXT("button_create_bankbook") );
	SetControlMap( BUTTON_DELETE_BANKBOOK, TEXT("button_delete_bankbook") );

	SetControlMap( EDIT_CREATE_VILLAGE, TEXT("editbox_create_village") );
	SetControlMap( EDIT_ACCOUNTNUM, TEXT("editbox_accountnum") );
	SetControlMap( EDIT_BANK_MONEY, TEXT("editbox_bank_money") );
	
	SetControlMap( EDIT_CURRENT_MONEY, TEXT("editbox_currentmoney") );
		
	SetControlMap( EDIT_MONEY, TEXT("editbox_money") );
	SetControlMap( EDIT_MONEY_UNIT, TEXT("editbox_money_unit") );

	SetControlMap( EDIT_FEE, TEXT("editbox_fee") );
	SetControlMap( EDIT_FEERATE, TEXT("editbox_feerate") );

	//[�迵�� �߰�:2007.11.21 - �ݾ� �Է½� ���� �̿ܿ� ���� �Է� ���ϵ��� ����]
	((CEdit*)m_pControlMap[ EDIT_MONEY ])->SetNumberMode( true );

	ShowAccountInfo();
}

void NBankUserDlg::ShowAccountInfo()
{
	TCHAR buffer[256];
	TCHAR szVillage[ 32 ];
	TCHAR szAccountNum[ 32 ];
	TCHAR szMoney[ 32 ];
	TCHAR szCurrentMoney[ 32 ];

	SI32 id = 1;

	TCHAR* pText = NULL;
	
	pText = GetTxtFromMgr(1466);
	StringCchCopy( szVillage, 32, pText );
	
	pText = GetTxtFromMgr(1287);
	StringCchCopy( szAccountNum, 32, pText );
	
	StringCchCopy( szMoney, 32, TEXT("0") );	

	if(pclCM->CR[id]->pclCI->clBank.clAccountNum.IsValid() == FALSE)
	{
	}
	else
	{
		SI32 unique = pclCM->CR[id]->pclCI->clBank.clAccountNum.GetVillageUnique();
		
		if(unique >= 0)
		{
			StringCchCopy( szVillage, 32, pclClient->pclVillageManager->pclVillageInfo[unique]->szName );
			StringCchPrintf( szAccountNum, 32, TEXT("%d-%d"), pclCM->CR[id]->pclCI->clBank.clAccountNum.GetAccountNum(), unique );
			
			pText = GetTxtFromMgr(611);
			g_JYLibFunction.SetNumUnit(pclCM->CR[id]->pclCI->clBank.GetMoney(), szMoney, 32, pText);

		}
		else
		{
			return ;
		}
	}

	// ���� ������ ������Ʈ �Ѵ�. 


	SetEditText( EDIT_CREATE_VILLAGE, szVillage );
	SetEditText( EDIT_ACCOUNTNUM, szAccountNum );
	SetEditText( EDIT_BANK_MONEY, szMoney );
	
	
	pText = GetTxtFromMgr(611);
	g_JYLibFunction.SetNumUnit(pclCM->CR[id]->pclCI->clIP.GetMoney(), szCurrentMoney, 32, pText);

	SetEditText( EDIT_CURRENT_MONEY, szCurrentMoney );

	float feerate = (float)m_pStrManager->clClientStrInfo.clBankStrInfo.clFee.GetFeeRate() / 10;

	StringCchPrintf( buffer, 256, TEXT("%3.1f%%"), feerate );

	SetEditText( EDIT_FEERATE, buffer, COLOR_DIALOG_READONLYTEXT );

	if(pclClient->IsCountrySwitch(Switch_BasicStructureSet)){
		SI32 dura = pclClient->pclBankManager->clClientStrInfo.clCommonInfo.siStrDura;//�ǹ��� �������� ������ �´�.

		if (dura <= 0) 
			((CButton*)m_pControlMap[ BUTTON_CREATE_BANKBOOK ])->Enable(false);//�ǹ��������� 0 �̸� ���� ���� �Ұ���.
		else
			((CButton*)m_pControlMap[ BUTTON_CREATE_BANKBOOK ])->Enable(true);//���� ���� ����.

	}

}

void NBankUserDlg::Action()
{
	ShowAccountInfo();

	TCHAR szMoney[ 128 ];
	GMONEY money;

	MStrCpy( szMoney, GetEditText( EDIT_MONEY ), 11 );

	money = _tstoi64( szMoney );

	TCHAR *pText = GetTxtFromMgr(611);
	//cyj �ݾ״��� ,�� ����
	//g_JYLibFunction.SetNumTxt( money, szMoney, pText );
	g_JYLibFunction.SetNumUnit( money, szMoney, 128, pText );
	SetEditText( EDIT_MONEY_UNIT, szMoney , COLOR_DIALOG_READONLYTEXT  );

	GMONEY fee = m_pStrManager->clClientStrInfo.clBankStrInfo.clFee.CalcFee( money );

	g_JYLibFunction.SetNumUnit( fee, szMoney, 128, pText );
	SetEditText( EDIT_FEE, szMoney , COLOR_DIALOG_READONLYTEXT );

}


void NBankUserDlg::NDlgTabProc( UINT nEvent, int nControlID, CControllerObj *pControl )
{
	
	SI32 id = 1;
	GMONEY money;
	TCHAR buffer[ 128 ];

	cltClient *pclclient = (cltClient*)pclClient;

	

	// ����ݾ� �Է�
	CASE_CONTROL( EDIT_MONEY )
	{

	}

	// ������ ��� �Ա�
	else CASE_CONTROL( BUTTON_INPUT_ALL )
	{

		if( pclCM->CR[id]->pclCI->clIP.GetMoney() == 0 ) {
			
			TCHAR* pText = GetTxtFromMgr(1453);
			SetMainExplain( pText );

		} else {

			// ������ �������� ��� �Ա��� ���� ��û�Ѵ�. 
			cltGameMsgRequest_GMoney clmoney(0);
			cltMsg clMsg( GAMEMSG_REQUEST_INPUTTOBANKALLMONEY, sizeof(clmoney), (BYTE*)&clmoney );
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		}
	}

	// �Ա� �ϱ�
	else CASE_CONTROL( BUTTON_INPUT )
	{
		MStrCpy( buffer, GetEditText( EDIT_MONEY ), 11 );

		money	=	_tstoi64(buffer);


		// ���ΰ��� ���� ������ ���� �ݾ��̰ų�.
		if( pclCM->CR[id]->pclCI->clIP.GetMoney() < money )
		{
			TCHAR* pText = GetTxtFromMgr(1454);
			SetMainExplain( pText );
		}
		// 0 ���� �۰ų� ���� �ݾ��̰ų�. 
		else if( money <=0 )
		{
			TCHAR* pText = GetTxtFromMgr(1455);
			SetMainExplain( pText );
		}
		else
		{
			// ������ ���� �Ա��� ���� ��û�Ѵ�. 
			cltGameMsgRequest_GMoney clmoney(money);
			cltMsg clMsg(GAMEMSG_REQUEST_INPUTTOBANK, sizeof(clmoney), (BYTE*)&clmoney);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		}

	}

	// ��� �ϱ�
	else CASE_CONTROL( BUTTON_OUTPUT )
	{
		MStrCpy( buffer, GetEditText( EDIT_MONEY ), 11 );

		money	=	_tstoi64(buffer);

		// Person�� �ľ��ϰ� �ִ� �ܾ׺��� ���� �ݾ��̰ų�. 
		if(pclCM->CR[id]->pclCI->clBank.GetMoney() < money)
		{
			TCHAR* pText = GetTxtFromMgr(1456);
			SetMainExplain( pText);
		}
		// 0 ���� �۰ų� ���� �ݾ��̰ų�. 
		else if(money <=0)
		{
			TCHAR* pText = GetTxtFromMgr(1457);
			SetMainExplain( pText);
		}
		else
		{
			// ������ ���� ����� ���� ��û�Ѵ�. 
			cltGameMsgRequest_GMoney clmoney(money);
			cltMsg clMsg(GAMEMSG_REQUEST_OUTPUTFROMBANK,sizeof(clmoney), (BYTE*)&clmoney);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		}

	}
	
	// ��� �ݾ� ��� �ϱ�
	else CASE_CONTROL( BUTTON_OUTPUT_ALL )
	{
		money = pclClient->pclCM->CR[id]->pclCI->clBank.GetMoney();

		if( money <= 0)
		{
			TCHAR* pText = GetTxtFromMgr(1457);
			SetMainExplain( pText);
		}
		else
		{
			TCHAR* pTitle = GetTxtFromMgr(5595);
			TCHAR* pText = GetTxtFromMgr(5596);
			
			stMsgBox MsgBox;
			// ���� dialog�� �� â ���� Child Dialog�϶�
			CControllerMgr *pParent = NULL;
			pParent = this->GetParentDialog();
			if(pParent == NULL ) return;
			MsgBox.Set( pParent, pTitle, pText, MSGBOX_TYPE_YESNO, 1 );
			BYTE TempBuffer[ 128 ];
			SI16 Size = sizeof( money );
			memcpy( TempBuffer, &money, sizeof( money ) );
			pclclient->SetMsgBox( &MsgBox, TempBuffer, Size );
		}
	}

	// ���� ����
	else CASE_CONTROL( BUTTON_CREATE_BANKBOOK )
	{

		if( pclCM->CR[id]->pclCI->clBank.clAccountNum.IsValid() == TRUE ) {
			// ������ ������,
			TCHAR* pText = GetTxtFromMgr(1458);
			SetMainExplain( pText);

		} else {
			// ������ ������,
			cltGameMsgRequest_CreateBankAccount clinfo( pclCM->CR[id]->GetCurrentVillageUnique() );

			// ���� ���� ��û 
			cltMsg clMsg( GAMEMSG_REQUEST_CREATEBANKACCOUNT, sizeof(clinfo), (BYTE*)&clinfo);			
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);					
		}
	}

	// ���� ����
	else CASE_CONTROL( BUTTON_DELETE_BANKBOOK )
	{

		if( pclCM->CR[id]->pclCI->clBank.clAccountNum.IsValid() == TRUE ) {
			// ������ ������,

			TCHAR* pText = GetTxtFromMgr(1459);
			TCHAR* pTitle = GetTxtFromMgr(1460);

			stMsgBox MsgBox;
			// ���� dialog�� �� â ���� Child Dialog�϶�
			CControllerMgr *pParent = NULL;
			pParent = this->GetParentDialog();
			if(pParent == NULL ) return;

			//KHY - 0613 - ��������. ���忡 ���� �����ȵ�.
//			MsgBox.Set( pParent, pTitle, pText, MSGBOX_TYPE_OK, 0 );


			MsgBox.Set( pParent, pTitle, pText, MSGBOX_TYPE_YESNO, 0 );

			
			BYTE TempBuffer[ 128 ];
			SI16 Size = sizeof( id );
			memcpy( TempBuffer, &id, sizeof( id ) );
			pclclient->SetMsgBox( &MsgBox, TempBuffer, Size );

			//if( MessageBox(NULL, pText, pTitle, MB_ICONQUESTION | MB_YESNO) == IDYES ) 
			//{

			//	cltGameMsgRequest_CloseBankAccount clinfo( pclCM->CR[id]->GetCurrentVillageUnique() );

			//	// ���� ���� ��û
			//	cltMsg clMsg( GAMEMSG_REQUEST_CLOSEBANKACCOUNT, sizeof(clinfo), (BYTE*)&clinfo);				
			//	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
			//}


		} else {
			// ������ ������,
			TCHAR* pText = GetTxtFromMgr(1461);
			SetMainExplain(pText);

			cltGameMsgRequest_CreateBankAccount clinfo( pclCM->CR[id]->GetCurrentVillageUnique() );

		}

	}

}

void NBankUserDlg::RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen )
{
	switch( MsgIndex )
	{
	case 0:	// ���� ������
		{
			if ( pData == NULL || DataLen < 1 )
			{
				return;
			}

			if ( RetValue )
			{
				SI32 id = *((SI32*)pData);

				cltGameMsgRequest_CloseBankAccount clinfo( pclCM->CR[id]->GetCurrentVillageUnique() );

				// ���� ���� ��û
				cltMsg clMsg( GAMEMSG_REQUEST_CLOSEBANKACCOUNT, sizeof(clinfo), (BYTE*)&clinfo);				
				pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
			}
		}
		break;

	case 1:
		{
			if ( pData == NULL || DataLen < 1 )
			{
				return;
			}

			if( RetValue )
			{
				GMONEY money = *((SI64*)pData);

				cltGameMsgRequest_GMoney clmoney(money);
				// ������ ���� ����� ���� ��û�Ѵ�. 
				cltMsg clMsg(GAMEMSG_REQUEST_OUTPUTFROMBANKALLMONEY, sizeof(clmoney), (BYTE*)&clmoney);
				pclCM->CR[1]->SendNetMsg((sPacketHeader*)&clMsg);
			}
		}
		break;
	}
}
