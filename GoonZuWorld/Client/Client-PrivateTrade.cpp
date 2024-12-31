#include "Client.h"
#include "..\Common\PrivateTradeOrderMgr\PrivateTradeOrderObj.h"
//#include "Resource.h"

#include "NInterface\NPrivateTradeDlg\NPrivateTradeDlg.h"
#include "NInterface\NPrivateTradeDlg\NPrivateTradeAcceptDlg.h"
#include "NInterface/NPrivateRepair/NPrivateRepairDlg.h"
#include "..\CommonLogic\Msg\MsgType-PrivateTrade.h"
#include "NInterface/NSoundOnOffDlg/NSoundOnOffDlg.h"
#include "Interface/SoundOnOffDlg/SoundOnOffDlg.h"
#include "InterfaceMgr/NMsgBoxDlg.h"
#include "NInterface/NNewMakeItem/NNewMakeItemDlg.h"
#include "NInterface/NNewEnchantOther/NNewEnchantOther.h"

#include "NInterface/NCharStatus/NCharStatus.h"
#include "NInterface/NCharStatus/NCharHorse.h"

void cltClient::DoMsg_GAMEMSG_RESPONSE_PRIVATETRADE_ACCEPT(cltMsg* pclMsg, SI32 id)//[����]
{   
	
	// ������ �ŷ��� �䱸�ؿ��µ� ���ϰڳĴ� �Ͱ� 
	// ������ �ŷ��� �ź��ؼ� �ŷ��� ���Ѵ� ���
	//�ΰ��� ����� �޽����� �ڵ鸵 �Ѵ�.

	cltGameMsgResponse_PrivateTrade_Accept *pclPrivateTrade_Accept = (cltGameMsgResponse_PrivateTrade_Accept *) pclMsg->cData;
	
	//�ŷ� �ź� �޽����� �°�� ����
	TCHAR buffer[255];
	TCHAR* pText = NULL;

	// PRIVATETRADE_TRADE_MODE_REJECT_ACCEPT ��� ���� �޽��� �÷��״� �ϳ��� �޽�����, ������ ���� �������� ����. ��->����->�������->����->�� 

	if( pclPrivateTrade_Accept->siTradeMode == PRIVATETRADE_TRADE_MODE_REJECT_ACCEPT || pclPrivateTrade_Accept->siTradeMode == PRIVATETRADE_TRADE_MODE_ALREADYTRADE 
		|| pclPrivateTrade_Accept->siTradeMode == PRIVATE_ENCHANT_MODE_REJECT_ACCEPT || pclPrivateTrade_Accept->siTradeMode == PRIVATE_ENCHANT_MODE_ALREADYTRADE )
	{
		
		if(pclPrivateTrade_Accept->siTradeMode == PRIVATETRADE_TRADE_MODE_REJECT_ACCEPT)
		{
			pText = GetTxtFromMgr(5755);
			
		}
		else if(pclPrivateTrade_Accept->siTradeMode == PRIVATETRADE_TRADE_MODE_ALREADYTRADE)
		{
			pText = GetTxtFromMgr(5756);
			
		}
		else if(pclPrivateTrade_Accept->siTradeMode == PRIVATE_ENCHANT_MODE_REJECT_ACCEPT)
		{
			pText = GetTxtFromMgr(6040);

		}
		else if(pclPrivateTrade_Accept->siTradeMode == PRIVATE_ENCHANT_MODE_ALREADYTRADE)
		{
			pText = GetTxtFromMgr(6041);

		}
		StringCchPrintf(buffer, 255, pText,pclPrivateTrade_Accept->strCharName);	
		pclMessage->SetMsg(buffer);
		return;
	}
	// ������ ��þƮ�Ƿڸ� �³��� �־���
	else if( pclPrivateTrade_Accept->siTradeMode == PRIVATE_ENCHANT_MODE_AGREE_ACCEPT )
	{	 
		// ���� �³� �޾����ϱ� ���� �Ƿڸ� �����Ѵ�.
 		cltGameMsgRequest_PrivateTrade clPrivateTrade( pclPrivateTrade_Accept->siOtherCharUnique, PRIVATETRADE_ENCHANT_MODE );
		cltMsg clMsg(GAMEMSG_REQUEST_PRIVATETRADE,
			sizeof(clPrivateTrade), (BYTE*)&clPrivateTrade);
		SendMsgToServer((sPacketHeader*)&clMsg);

	}

	// Ʈ���̵� ��û�� ������
	else if(pclPrivateTrade_Accept->siTradeMode == PRIVATETRADE_TRADE_MODE )
	{
		// �̹�  ��þƮâ, ��þƮ �Ƿ�â ,�ŷ��䱸â Ȥ�� �ŷ�â�� ����� �ŷ������� ��ȯ
		if(m_pDialog[NPRIVATETRADEACCEPT_DLG] || m_pDialog[NPRIVATETRADE_DLG] )
		{
			cltGameMsgRequest_PrivateTrade_Accept clinfo(pclPrivateTrade_Accept ->siOtherCharUnique,PRIVATETRADE_TRADE_MODE_ALREADYTRADE );

			cltMsg clMsg(GAMEMSG_REQUEST_PRIVATETRADE_ACCEPT, sizeof(clinfo), (BYTE*)&clinfo);
			SendMsgToServer((sPacketHeader*)&clMsg);	// �ŷ��� �޽��� ����
			return;
		}
		else if( m_pDialog[NNEWENCHANTOTHERACCEPT_DLG] ||  m_pDialog[NNEWENCHANTOTHER_DLG]) 
		{	
			cltGameMsgRequest_PrivateTrade_Accept clinfo(pclPrivateTrade_Accept ->siOtherCharUnique,PRIVATE_ENCHANT_MODE_ALREADYTRADE );

			cltMsg clMsg(GAMEMSG_REQUEST_PRIVATETRADE_ACCEPT, sizeof(clinfo), (BYTE*)&clinfo);
			SendMsgToServer((sPacketHeader*)&clMsg);	// ��þƮ �Ƿ��� �޽��� ����
			return;				
		}
		// �ŷ� �� ���ϰڳĴ� �޽��� �ڽ� ���
		else
		{
			CreateInterface(NPRIVATETRADEACCEPT_DLG);
			CreateInterface( NPRIVATETRADEACCEPT_MSGBOX_DLG);
			TCHAR *pTitle = GetTxtFromMgr(2329);

			pText = GetTxtFromMgr(5754);


			TCHAR pBuffer[255];
			StringCchPrintf(pBuffer, 255, pText,pclPrivateTrade_Accept->strCharName);
			stMsgBox MsgBox;

			MsgBox.Set( m_pDialog[NPRIVATETRADEACCEPT_DLG], pTitle, pBuffer, MSGBOX_TYPE_YESNO, 0 );

			((CNMsgBoxDlg*)m_pDialog[NPRIVATETRADEACCEPT_MSGBOX_DLG])->SetMsgData((BYTE*)&MsgBox,
				(BYTE*)pclPrivateTrade_Accept,sizeof(cltGameMsgResponse_PrivateTrade_Accept));
		}
	}	
	// ��þƮ �ش޶�� ��û�� ������
	else if( pclPrivateTrade_Accept->siTradeMode == PRIVATETRADE_ENCHANT_MODE  )
	{

		if(m_pDialog[NPRIVATETRADEACCEPT_DLG] || m_pDialog[NPRIVATETRADE_DLG] )
		{
			cltGameMsgRequest_PrivateTrade_Accept clinfo(pclPrivateTrade_Accept ->siOtherCharUnique,PRIVATETRADE_TRADE_MODE_ALREADYTRADE );

			cltMsg clMsg(GAMEMSG_REQUEST_PRIVATETRADE_ACCEPT, sizeof(clinfo), (BYTE*)&clinfo);
			SendMsgToServer((sPacketHeader*)&clMsg);	// �ŷ��� �޽��� ����
			return;
		}
		// �̹� ��þƮ ���̶�� ��þƮ �� �޽��� ���� ����
		else if (  m_pDialog[NNEWENCHANTOTHERACCEPT_DLG] ||  m_pDialog[NNEWENCHANTOTHER_DLG]  ) 
		{	
			cltGameMsgRequest_PrivateTrade_Accept clinfo(pclPrivateTrade_Accept ->siOtherCharUnique,PRIVATE_ENCHANT_MODE_ALREADYTRADE );

			cltMsg clMsg(GAMEMSG_REQUEST_PRIVATETRADE_ACCEPT, sizeof(clinfo), (BYTE*)&clinfo);
			SendMsgToServer((sPacketHeader*)&clMsg);	// ��þƮ �� �޽��� ����
			return;				
		}
		// ��þƮ �Ƿڰ� �Դµ� ���ϰڳĴ� �޽��� ǥ��
		else
		{
			CreateInterface( NNEWENCHANTOTHERACCEPT_DLG );
			CreateInterface( NPRIVATETRADEACCEPT_MSGBOX_DLG);
			TCHAR *pTitle = GetTxtFromMgr(6039);

			pText = GetTxtFromMgr(6038);

			TCHAR pBuffer[255];
			StringCchPrintf(pBuffer, 255, pText,pclPrivateTrade_Accept->strCharName);
			stMsgBox MsgBox;

			MsgBox.Set( m_pDialog[NNEWENCHANTOTHERACCEPT_DLG], pTitle, pBuffer, MSGBOX_TYPE_YESNO, 0 );

			((CNMsgBoxDlg*)m_pDialog[NPRIVATETRADEACCEPT_MSGBOX_DLG])->SetMsgData((BYTE*)&MsgBox,
				(BYTE*)pclPrivateTrade_Accept,sizeof(cltGameMsgResponse_PrivateTrade_Accept));
		}
	}

}

void cltClient::DoMsg_GAMEMSG_RESPONSE_PRIVATETRADE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_PrivateTrade *pclPrivateTrade = (cltGameMsgResponse_PrivateTrade *) pclMsg->cData;


	if(pclPrivateTrade->siTradeMode == PRIVATETRADE_TRADE_MODE)
	{
		if(( m_pDialog[ NPRIVATETRADE_DLG ])==NULL)
		{
			CreateInterface(NPRIVATETRADE_DLG);
		}
		((CNPrivateTradeDlg*)m_pDialog[NPRIVATETRADE_DLG])->Show(pclPrivateTrade->siOtherCharUnique, pclPrivateTrade->siTradeMode, pclPrivateTrade->siOtherCharLevel, pclPrivateTrade->strCharName, pclPrivateTrade->strAccountID, pclPrivateTrade->siPrivateTradeOrderMgrIndex, pclPrivateTrade->siPrivateTradeOrderCountIndex, pclPrivateTrade->siOtherCharLevel);
	}

	else if(pclPrivateTrade->siTradeMode == PRIVATETRADE_ENCHANT_MODE)
	{
		if(( m_pDialog[ NNEWENCHANTOTHER_DLG ])==NULL)
		{
			CreateInterface(NNEWENCHANTOTHER_DLG);
		}
		((CNNewEnchantOther*)m_pDialog[NNEWENCHANTOTHER_DLG])->Show(pclPrivateTrade->siOtherCharUnique, pclPrivateTrade->siTradeMode,  pclPrivateTrade->siOtherCharLevel, pclPrivateTrade->strCharName, pclPrivateTrade->strAccountID, pclPrivateTrade->siPrivateTradeOrderMgrIndex, pclPrivateTrade->siPrivateTradeOrderCountIndex, pclPrivateTrade->siOtherCharLevel);


		if(m_pDialog[NNEWITEMMAKE_DLG])
		{
			CNewMakeItemDlg* makeItem = (CNewMakeItemDlg*)m_pDialog[NNEWITEMMAKE_DLG];
			makeItem->NewEnchantTab->SetEnchantCharUnique(pclPrivateTrade->siOtherCharUnique);
		//	makeItem->NewEnchantTab->SetEnchantOtherState(TRUE);

		}            
	}


	return;
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_PRIVATETRADE_CANCEL(cltMsg* pclMsg, SI32 id)
{

	if( m_pDialog[ NPRIVATETRADE_DLG ])
	{
		((CNPrivateTradeDlg*)m_pDialog[NPRIVATETRADE_DLG])->DeleteDialog();

		TCHAR* pText = GetTxtFromMgr(5758);

		pclMessage->SetMsg(pText);

	}
		

	if( m_pDialog[ NNEWENCHANTOTHER_DLG ])
	{
		((CNNewEnchantOther*)m_pDialog[NNEWENCHANTOTHER_DLG])->DeleteDialog();
		
		if( m_pDialog[ NNEWITEMMAKE_DLG ] )
		{
			 ( (CNewMakeItemDlg* )m_pDialog[ NNEWITEMMAKE_DLG ] )->NewEnchantTab->SetInitInchant();
			//  ( (CNewMakeItemDlg* )m_pDialog[ NNEWITEMMAKE_DLG ] )->NewEnchantTab->SetEnchantOtherState(TRUE);
		}
//		TCHAR* pText = GetTxtFromMgr(6031);
	//	pclMessage->SetMsg(pText);
	}

	return;
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_PRIVATETRADE_ADDITEM(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_PrivateTrade_AddItem *pclPrivateTradeAddItem = ( cltGameMsgResponse_PrivateTrade_AddItem * ) pclMsg->cData;

	if(m_pDialog[NPRIVATETRADE_DLG])
		((CNPrivateTradeDlg*)m_pDialog[NPRIVATETRADE_DLG])->PrivateTradeAddItem( pclPrivateTradeAddItem->siCharUnique, pclPrivateTradeAddItem->siAddedIndex, &pclPrivateTradeAddItem->clItem );

	if( m_pDialog[ NPTRADEREPRAIR_DLG ])
		((CNPrivateRepairDlg*)m_pDialog[NPTRADEREPRAIR_DLG])->PrivateTradeAddItem( pclPrivateTradeAddItem->siCharUnique, pclPrivateTradeAddItem->siAddedIndex, &pclPrivateTradeAddItem->clItem );
	
	return;
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_PRIVATETRADE_DELLIST(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_PrivateTrade_DelList *pclPrivateTradeDelList = ( cltGameMsgResponse_PrivateTrade_DelList * ) pclMsg->cData;
	
	if(m_pDialog[ NPRIVATETRADE_DLG ])
	{
		((CNPrivateTradeDlg*)m_pDialog[NPRIVATETRADE_DLG])->PrivateTradeDelList( pclPrivateTradeDelList->siCharUnique, pclPrivateTradeDelList->siDelType, pclPrivateTradeDelList->siParam );
	}
	if( m_pDialog[ NPTRADEREPRAIR_DLG ])
	{
		((CNPrivateRepairDlg*)m_pDialog[NPTRADEREPRAIR_DLG])->PrivateTradeDelList( pclPrivateTradeDelList->siCharUnique, pclPrivateTradeDelList->siDelType, pclPrivateTradeDelList->siParam );

	}
	

	return;
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_PRIVATETRADE_DELITEM(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_PrivateTrade_DelItem *pclPrivateTradeDelItem = ( cltGameMsgResponse_PrivateTrade_DelItem * ) pclMsg->cData;

	if(m_pDialog[ NPRIVATETRADE_DLG ])
	{
		((CNPrivateTradeDlg*)m_pDialog[NPRIVATETRADE_DLG])->PrivateTradeDelItem( pclPrivateTradeDelItem->siCharUnique, pclPrivateTradeDelItem->siDelIndex );
	}


	if( m_pDialog[ NPTRADEREPRAIR_DLG ])
	{
		((CNPrivateRepairDlg*)m_pDialog[NPTRADEREPRAIR_DLG])->PrivateTradeDelItem( pclPrivateTradeDelItem->siCharUnique, pclPrivateTradeDelItem->siDelIndex );
	}

	return;
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_PRIVATETRADE_ADDPRICE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_PrivateTrade_AddPrice *pclPrivateTradeAddPrice = ( cltGameMsgResponse_PrivateTrade_AddPrice * ) pclMsg->cData;

	if ( g_SoundOnOffDlg.m_bFullScreenMode )
	{
		if(m_pDialog[ NPRIVATETRADE_DLG ])
		{
			((CNPrivateTradeDlg*)m_pDialog[NPRIVATETRADE_DLG])->PrivateTradeAddPrice( pclPrivateTradeAddPrice->siOtherCharUnique, pclPrivateTradeAddPrice->siPrice );
		}
	}

	if( m_pDialog[ NPTRADEREPRAIR_DLG ])
	{
		((CNPrivateRepairDlg*)m_pDialog[NPTRADEREPRAIR_DLG])->PrivateTradeAddPrice( pclPrivateTradeAddPrice->siOtherCharUnique, pclPrivateTradeAddPrice->siPrice );
		//CreateInterface( NPRIVATETRADE_DLG);
	}


	return;
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_PRIVATETRADE_ADDSTOCK(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_PrivateTrade_AddStock *pclPrivateTradeAddStock = ( cltGameMsgResponse_PrivateTrade_AddStock * ) pclMsg->cData;

	if(m_pDialog[ NPRIVATETRADE_DLG ])
	{
		((CNPrivateTradeDlg*)m_pDialog[NPRIVATETRADE_DLG])->PrivateTradeAddStock( pclPrivateTradeAddStock->siOtherCharUnique, pclPrivateTradeAddStock->siVillageUnique, pclPrivateTradeAddStock->siStockNum );
	}

	return;
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_PRIVATETRADE_ADDHOUSEUNIT(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_PrivateTrade_AddHouseUnit *pclPrivateTradeAddHouseUnit = ( cltGameMsgResponse_PrivateTrade_AddHouseUnit * ) pclMsg->cData;

	if(m_pDialog[ NPRIVATETRADE_DLG ])
	{
		((CNPrivateTradeDlg*)m_pDialog[NPRIVATETRADE_DLG])->PrivateTradeAddHouseUnit( pclPrivateTradeAddHouseUnit->siOtherCharUnique,
			pclPrivateTradeAddHouseUnit->siHouseVillageUnique,
			pclPrivateTradeAddHouseUnit->siHouseUnitSlot,
			&pclPrivateTradeAddHouseUnit->clRentContract
			);
	}

	return;
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_PRIVATETRADE_ADDHORSE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_PrivateTrade_AddHorse *pclPrivateTradeAddHorse = ( cltGameMsgResponse_PrivateTrade_AddHorse* ) pclMsg->cData;

	if ( g_SoundOnOffDlg.m_bFullScreenMode )
	{
		if(m_pDialog[ NPRIVATETRADE_DLG ])
		{
		((CNPrivateTradeDlg*)m_pDialog[NPRIVATETRADE_DLG])->PrivateTradeAddHorse( pclPrivateTradeAddHorse->siOtherCharUnique, pclPrivateTradeAddHorse->siHorseIndex, &pclPrivateTradeAddHorse->clHorseInfo );
		}
	}

	return;
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_PRIVATETRADE_MYACCEPT(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_PrivateTrade_MyAccept *pclPrivateTrade_MyAccept = ( cltGameMsgResponse_PrivateTrade_MyAccept * ) pclMsg->cData;

	if(m_pDialog[ NPRIVATETRADE_DLG ])
	{
		((CNPrivateTradeDlg*)m_pDialog[NPRIVATETRADE_DLG])->PrivateTradeMyAccept();
	}

	if( m_pDialog[ NPTRADEREPRAIR_DLG ])
	{
		((CNPrivateRepairDlg*)m_pDialog[NPTRADEREPRAIR_DLG])->PrivateTradeMyAccept();

	}

	return;
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_PRIVATETRADE_MYCANCEL(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_PrivateTrade_MyCancel *pclPrivateTrade_MyCancel = ( cltGameMsgResponse_PrivateTrade_MyCancel * ) pclMsg->cData;

	if(m_pDialog[ NPRIVATETRADE_DLG ])
	{
		((CNPrivateTradeDlg*)m_pDialog[NPRIVATETRADE_DLG])->PrivateTradeMyCancel();
	}

	if( m_pDialog[ NPTRADEREPRAIR_DLG ])
	{
		((CNPrivateRepairDlg*)m_pDialog[NPTRADEREPRAIR_DLG])->PrivateTradeMyCancel();
	}

	return;
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_PRIVATETRADE_OTHERACCEPT(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_PrivateTrade_OtherAccept *pclPrivateTrade_OtherAccept = ( cltGameMsgResponse_PrivateTrade_OtherAccept * ) pclMsg->cData;

	if(m_pDialog[ NPRIVATETRADE_DLG ])
	{
		((CNPrivateTradeDlg*)m_pDialog[NPRIVATETRADE_DLG])->PrivateTradeOtherAccept( pclPrivateTrade_OtherAccept->siResult );
	}


	if( m_pDialog[ NPTRADEREPRAIR_DLG ])
	{
		((CNPrivateRepairDlg*)m_pDialog[NPTRADEREPRAIR_DLG])->PrivateTradeOtherAccept( pclPrivateTrade_OtherAccept->siResult );
	}
	
	return;
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_PRIVATETRADE_OTHERCANCEL(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_PrivateTrade_OtherCancel *pclPrivateTrade_OtherCancel = ( cltGameMsgResponse_PrivateTrade_OtherCancel * ) pclMsg->cData;

	if(m_pDialog[ NPRIVATETRADE_DLG ])
	{
		((CNPrivateTradeDlg*)m_pDialog[NPRIVATETRADE_DLG])->PrivateTradeOtherCancel();
	}


	if( m_pDialog[ NPTRADEREPRAIR_DLG ])
	{
		((CNPrivateRepairDlg*)m_pDialog[NPTRADEREPRAIR_DLG])->PrivateTradeOtherCancel();

	}

	

	return;
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_PRIVATETRADE_END(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_PrivateTrade_End *pclPrivateTrade_End = ( cltGameMsgResponse_PrivateTrade_End * ) pclMsg->cData;
	
	if(m_pDialog[ NPRIVATETRADE_DLG ])
	{
		((CNPrivateTradeDlg*)m_pDialog[NPRIVATETRADE_DLG])->PrivateTradeEnd( pclPrivateTrade_End->siResult,
			pclPrivateTrade_End->siRecvStockVillageUnique, pclPrivateTrade_End->siRecvStockNum,
			pclPrivateTrade_End->siSendStockVillageUnique, pclPrivateTrade_End->siSendStockNum,
			pclPrivateTrade_End->siRecvHouseVillageUnique, pclPrivateTrade_End->siRecvHouseUnitSlot,
			&pclPrivateTrade_End->clRecvRentContract,
			pclPrivateTrade_End->siSendHouseVillageUnique, pclPrivateTrade_End->siSendHouseUnitSlot,
			pclPrivateTrade_End->siHorseIndex, &pclPrivateTrade_End->clHorse 
			);
	}

	if( m_pDialog[ NNEWENCHANTOTHER_DLG ])
	{
		((CNNewEnchantOther*)m_pDialog[NNEWENCHANTOTHER_DLG])->PrivateTradeEnd( pclPrivateTrade_End->siResult,
			pclPrivateTrade_End->siRecvStockVillageUnique, pclPrivateTrade_End->siRecvStockNum,
			pclPrivateTrade_End->siSendStockVillageUnique, pclPrivateTrade_End->siSendStockNum,
			pclPrivateTrade_End->siRecvHouseVillageUnique, pclPrivateTrade_End->siRecvHouseUnitSlot,
			&pclPrivateTrade_End->clRecvRentContract,
			pclPrivateTrade_End->siSendHouseVillageUnique, pclPrivateTrade_End->siSendHouseUnitSlot,
			pclPrivateTrade_End->siHorseIndex, &pclPrivateTrade_End->clHorse 
			);
	}

	if( m_pDialog[ NPTRADEREPRAIR_DLG ])
	{
		((CNPrivateRepairDlg*)m_pDialog[NPTRADEREPRAIR_DLG])->PrivateTradeEnd( pclPrivateTrade_End->siResult,
			pclPrivateTrade_End->siRecvStockVillageUnique, pclPrivateTrade_End->siRecvStockNum,
			pclPrivateTrade_End->siSendStockVillageUnique, pclPrivateTrade_End->siSendStockNum,
			pclPrivateTrade_End->siRecvHouseVillageUnique, pclPrivateTrade_End->siRecvHouseUnitSlot,
			&pclPrivateTrade_End->clRecvRentContract,
			pclPrivateTrade_End->siSendHouseVillageUnique, pclPrivateTrade_End->siSendHouseUnitSlot,
			pclPrivateTrade_End->siHorseIndex, &pclPrivateTrade_End->clHorse 
			);
	}

	//KHY - 1001 - ��µ��� 5���� ���� ����.
	/*if( m_pDialog[ CLTNCHARSTATUS_DLG ] )
	{		
		((cltNCharStatus*) m_pDialog[ CLTNCHARSTATUS_DLG ])->m_pTabDlg1->m_bChangedInitHorseStatus = TRUE;
		((cltNCharStatus*) m_pDialog[ CLTNCHARSTATUS_DLG ])->m_pTabDlg1->InitHorseStatusInfo();
		((cltNCharStatus*) m_pDialog[ CLTNCHARSTATUS_DLG ])->m_pTabDlg1->UpdateHorseStatusInfo();
	}*/
	TCHAR* pText = GetTxtFromMgr(5757);

	pclMessage->SetMsg(pText);

	return;
}