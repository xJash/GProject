#include "..\Client.h"
#include "..\Client\Music\Music.h"
#include "../CommonLogic/MsgType.h"

#include "../CommonLogic/Msg/MsgType-Port.h"
#include "../CommonLogic/House/House.h"

#include "..\Client\Interface/ErrorMsgDlg/ErrorMsgDlg.h"

//-------------------------------------
// Common
//-------------------------------------
#include "PersonInfo.h"
#include "Char\CharManager\CharManager.h"

// ���� ����Ʈ ����.
void cltClient::DoMsg_GAMEMSG_RESPONSE_PORTUNITLIST(cltMsg* pclMsg)
{
	cltGameMsgResponse_PortUnitList *pclInfo = (cltGameMsgResponse_PortUnitList *)pclMsg->cData;
	
	SI16 i = 0;

	// �켱 ����Ʈ�� �� ������
	for( i = 0; i < MAX_PORTUNIT_NUMBER; ++i )
	{
		pclPortManager->clClientPortUnit[ i ].Init();
	}
	
	for ( i = 0; i < MAX_SHIP_PER_PERSON; ++i )
	{
		if ( pclInfo->clPerson[ i ].GetPersonID() > 0 )
		{
			pclPortManager->clClientPortUnit[ pclInfo->siPortUnitIndexList[ i ] ].clPerson.Set( &pclInfo->clPerson[ i ] );
			pclPortManager->clClientPortUnit[ pclInfo->siPortUnitIndexList[ i ] ].clShip.siKind = pclInfo->siShipKind[ i ];
			pclPortManager->m_bPortListDlgUpdateSwitch = true;
		}
	}
	
	 
	return;
}

// ���� 1���� �� ������ ����.
void cltClient::DoMsg_GAMEMSG_RESPONSE_PORTUNITLISTDETAIL(cltMsg* pclMsg)
{
	cltGameMsgResponse_PortUnitListDetail *pclInfo = (cltGameMsgResponse_PortUnitListDetail*)pclMsg->cData;

	pclPortManager->clClientPortUnit[ pclInfo->siPortUnitSlot ].Set( &pclInfo->clPortUnit );

	return;
}

// ���� ����ڿ��� ������ ȸ���Ǿ����� �˷���.
void cltClient::DoMsg_GAMEMSG_RESPONSE_PORTUNITRECALLNOTIFY(cltMsg* pclMsg)
{
	cltGameMsgResponse_PortUnitRecallNotify *pclInfo = ( cltGameMsgResponse_PortUnitRecallNotify *)pclMsg;
	
	if ( pclInfo->siShipID < 1 )
	{
		return;
	}

	SI16 Ref = pclCM->CR[1]->pclCI->clShipInfo.GetShipDataIndex( pclInfo->siShipID );

	if ( Ref < 0 )
	{
		return;
	}
	
	pclCM->CR[1]->pclCI->clShipInfo.ShipExplode( pclInfo->siShipID );
	pclCM->CR[1]->pclCI->clShipItemInfo.Init( Ref );

	return;
}

// ������ �踦 ����.
void cltClient::DoMsg_GAMEMSG_RESPONSE_PORTSHIPENTERTOPORTUNIT(cltMsg* pclMsg)
{
	cltGameMsgResponse_PortShipEnterToPortUnit *pclInfo = (cltGameMsgResponse_PortShipEnterToPortUnit *)pclMsg->cData;

	if ( pclInfo->siHouseUnitSlot >= 0 )
	{
		pclHouseManager->clClientUnit[ pclInfo->siHouseUnitSlot ].clStorageInfo.clShip.Init();
	}
	
	
	pclPortManager->clClientPortUnit[ pclInfo->siPortUnitIndex ].clContract.Set( &pclInfo->clContract );
	
	if ( pclCM->CR[1]->pclCI->clShipInfo.IsShipExist( pclInfo->clShip.siShipID ) )
	{
		// ���� �ۿ��� ������ ������ ��� ���� ����
		pclCM->CR[1]->pclCI->clShipInfo.SetShipDataChange( &pclInfo->clShip );
	}
	else
	{
		// �����ҿ��� ������ ���� �ϴ� ��� �� �߰�
		pclCM->CR[1]->pclCI->clShipInfo.AddShip( &pclInfo->clShip );
	}
	
	pclCM->CR[1]->pclCI->clBank.SetMoney( (SI32)pclInfo->clBankMoney.itMoney );	
	
	pclPortManager->clClientPortUnit[ pclInfo->siPortUnitIndex ].clPerson.Set( pclCM->CR[1]->pclCI->GetPersonID(), pclCM->CR[1]->GetName() );
	pclPortManager->m_bPortListDlgUpdateSwitch = true;

	return;
}

// �������� �踦 ����
void cltClient::DoMsg_GAMEMSG_RESPONSE_PORTSHIPLEAVEFROMPORTUNIT(cltMsg* pclMsg)
{
	cltGameMsgResponse_PortShipLeaveFromPortUnit *pclInfo = (cltGameMsgResponse_PortShipLeaveFromPortUnit *)pclMsg->cData;

	pclPortManager->clClientPortUnit[ pclInfo->siPortUnitIndex ].Init();
	
	pclCM->CR[1]->pclCI->clShipInfo.SetShipDataChange( &pclInfo->clShip );

	return;
}


void cltClient::DoMsg_GAMEMSG_RESPONSE_PORTUNITCONTRACT(cltMsg* pclMsg)
{
	cltGameMsgResponse_PortUnitContract *pclInfo = (cltGameMsgResponse_PortUnitContract*)pclMsg->cData;

	pclPortManager->clClientStrInfo.clPortStrInfo.Set( &pclInfo->clContract );
	
	return;
}