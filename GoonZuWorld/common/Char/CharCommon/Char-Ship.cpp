#include "..\Common\CommonHeader.h"
#include "..\..\Client\Client.h"

#include "..\..\..\DBManager\GameDBManager\DBMsg-Person.h"
#include "..\..\..\DBManager\GameDBManager\DBMsg-Item.h"

//--------------------------
// Common
//-------------------------
#include "PersonInfo.h"
#include "..\CharManager\CharManager.h"
#include "../Common/ShipListMgr/ShipListObj.h"
#include "../Common/ShipListMgr/ShipListMgr.h"
#include "../CommonLogic/Msg/MsgType-Ship.h"

#include "../Common/Order/order.h"

#include "../CharServer/Char-Server.h"

#include "../Server/Server.h"

#include "../CommonLogic/MsgRval-Define.h"

extern cltCommonLogic* pclClient;

void cltCharCommon::ShipPassengerDataInit()
{	
	siRequestEmbarkShipID = 0;
	clInnerStatus.siRideShipID = 0;	
	clInnerStatus.siSelfShipID = 0;
	clInnerStatus.siShipCharUnique = 0;
	clInnerStatus.siShipOwnerCharUnique = 0;
}

// �踦 ź ���·� ������ ��� ������ ó�� ( Ŭ���̾�Ʈ�� )
void cltCharCommon::ShipEnterToPortUnitForPassenger()
{	
	siRequestEmbarkShipID = 0;

	clInnerStatus.siShipCharUnique = 0;		// �谡 ���������ϱ�, ���� CharID �� �ʱ�ȭ �Ǿ�� ����..
}

bool cltCharCommon::GetShipOwnerInfo( SI32 *pShipOwnerCharUnique )
{
	if ( pShipOwnerCharUnique == NULL )
	{
		return false;
	}

	if ( clInnerStatus.siShipOwnerCharUnique < 1 )
	{
		return false;
	}

	*pShipOwnerCharUnique = clInnerStatus.siShipOwnerCharUnique;
	
	return true;
}

void cltCharCommon::SetShipOwnerInfo( SI32 ShipOwnerCharUnique )
{
	clInnerStatus.siShipOwnerCharUnique = ShipOwnerCharUnique;

	return;
}

void cltCharCommon::SendMsgToAllPassenger( char *pMsg )
{
	if ( clInnerStatus.siRideShipID  < 1 )
	{
		return;
	}



	return;
}

void cltCharCommon::SendMsgToShipOwner( char *pMsg )
{
	if ( clInnerStatus.siRideShipID  < 1 )
	{
		return;
	}

	return;
}

// �¼� �ϱ⸦ ��û
// VillageUnique == 0 �� ���� �߿��������� �¼�
// VillageUnique > 0 �� ��쿡�� �������� �¼�
void cltCharCommon::ReqEmbarkShip( SI32 ShipID, SI32 ShipOwnerPersonID )
{
	// �迡 Ÿ�� �ִ� ���¿����� �ȵ���..
	if ( clInnerStatus.siRideShipID > 0 || clInnerStatus.siShipOwnerCharUnique > 0 || clInnerStatus.siShipCharUnique > 0 )
	{
		return;
	}	

	if ( ShipOwnerPersonID < 1 )
	{
		return;
	}

	if ( ShipID < 1 )
	{
		return;
	}

	// ���ְ� ���� ���� ������ Ȯ��
	SI32 ShipOwnerCharID = pclClient->pclCM->GetIDFromPersonID( ShipOwnerPersonID );

	if ( ShipOwnerCharID < 1 || pclClient->pclCM->IsValidID( ShipOwnerCharID ) == FALSE )
	{
		return;
	}	

	CShipListObj *pShipListObj = pclClient->pclShipListMgr->GetShipListObj( ShipID );

	if ( pShipListObj == NULL )
	{
		// ���� ���
		pShipListObj = pclClient->pclShipListMgr->CreateShipListObj( ShipID, &pclClient->pclCM->CR[ShipOwnerCharID]->pclCI->clBI.clPerson, ShipOwnerCharID );
		if ( pShipListObj == NULL )
		{
			return;
		}
	}

	SI32 MyID = GetID();

	// �¼��ϴ� ����� ������ ��쿡�� �׳� �¼� ��Ŵ
	if ( MyID == ShipOwnerCharID )
	{		
		cltShipPassenger clTempShipPassenger;
		clTempShipPassenger.Init();
		clTempShipPassenger.Set( &pclCI->clBI.clPerson, MyID, SHIP_JOB_OWNER );

		// �踦 ������ ĳ���Ϳ� ����
		EmbarkShip( MyID, pclCI->GetPersonID(), ShipID );

		return;
	}

	/*
	// ���ְ� ����� �ϸ� siRequestEmbarkShipID �� 0 ���� ������ �ϴµ�.. �װ� �� ���ϰ� Ŭ��
	// ������ �迡 Ż���� ��û�� �迡 �� ��û�� ���.
	if ( siRequestEmbarkShipID == ShipID )
	{
	// ��û�Ǿ� �ִٰ� �˷������...

	// �迡 ��û�� ������... �� �� Ÿ�� ����... �� ��쿡�� �������� �˷������.. �Žñ� ���� ��û�ߴµ�, ��û�� �ʰ��ؼ� �� �¿�ٰ�.. ����Ʈ �ʱ�ȭ�� �϶��..

	return;
	}
	*/

	siRequestEmbarkShipID = ShipID;

	// �迡 ž�� ��û�� ���������� ����.
	cltGameMsgResponse_ShipPersonEmbark clinfo( true, ShipID );
	cltMsg clMsg( GAMEMSG_RESPONSE_SHIPPERSONEMBARK,  sizeof( clinfo ), (char*)&clinfo );
	SendNetMsg((char*)&clMsg);

	cltShipPassenger clShipPassenger;
	clShipPassenger.Init();
	clShipPassenger.Set( &pclCI->clBI.clPerson, MyID, SHIP_JOB_PASSENGER );

	// ���ֿ��� ���� �迡 �¼��ϱ⸦ ��û������ �˸�
	cltGameMsgResponse_ShipPersonEmbarkNotify clinfo1( ShipID, &clShipPassenger.clSimplePerson, pclCI->clIP.GetLevel() );
	cltMsg clMsg1( GAMEMSG_RESPONSE_SHIPPERSONEMBARKNOTIFY,  sizeof( clinfo1 ), (char*)&clinfo1 );
	pclClient->pclCM->CR[ShipOwnerCharID]->SendNetMsg((char*)&clMsg1);
}

void cltCharCommon::ReqEmbarkCancel( SI32 ShipID )
{
	// �踦 Ÿ�� ������ ��������...
	if ( ShipID > 0 )
	{
		return;
	}

	// ���� �踦 Ÿ�� ���� �ʴ� ��쿡�� �ش��ϰ���...
	if ( clInnerStatus.siRideShipID < 1 )
	{
		return;
	}

	// ������ ��û�� ���� ���� ���.
	if ( siRequestEmbarkShipID < 1 )
	{
		return;
	}

	siRequestEmbarkShipID = 0;

	cltGameMsgResponse_ShipPersonEmbarkCancel clinfo( true );
	cltMsg clMsg( GAMEMSG_RESPONSE_SHIPPERSONEMBARKCANCEL,  sizeof( clinfo ), (char*)&clinfo );
	SendNetMsg((char*)&clMsg);

	return;
}

// �¼� ��Ű�� - ���ָ� ȣ�� ����
void cltCharCommon::EmbarkShip( SI32 ShipPassengerCharID, SI32 ShipPassengerPersonID, SI32 ShipID )
{	
	cltServer *pclServer = (cltServer *)pclClient;

	if ( ShipID < 1 )
	{
		return;
	}

	if ( ShipPassengerCharID < 1 || ShipPassengerPersonID < 1 ||
		pclClient->pclCM->IsValidID( ShipPassengerCharID ) == FALSE ||
		pclClient->pclCM->CR[ShipPassengerCharID]->pclCI->GetPersonID() != ShipPassengerPersonID )
	{
		return;
	}

	SI32 MyID = GetID();

	if ( MyID != ShipPassengerCharID && pclClient->pclCM->CR[ShipPassengerCharID]->siRequestEmbarkShipID != ShipID )
	{
		return;
	}

	// ���� ���� Ȯ��
	if ( ! pclClient->pclCM->CR[MyID]->pclCI->clShipInfo.IsShipExist( ShipID ) )
	{
		return;
	}
	
	// �̹� �ٸ� �踦 Ÿ�� �ִٸ�, �¼� ��ų �� ���� ������..
	if ( pclClient->pclCM->CR[ShipPassengerCharID]->clInnerStatus.siRideShipID > 0 &&
		pclClient->pclCM->CR[ShipPassengerCharID]->clInnerStatus.siRideShipID != ShipID
		)
	{
		return;
	}

	CShipListObj *pShipListObj = pclClient->pclShipListMgr->GetShipListObj( ShipID );

	if ( pShipListObj == NULL )
	{
		// ���� ���
		pShipListObj = pclClient->pclShipListMgr->CreateShipListObj( ShipID, &pclCI->clBI.clPerson, MyID );
		if ( pShipListObj == NULL )
		{
			return;
		}
	}

	SI16 AddedIndex = -1;

	// ���迡 ���� �¼���Ű�� ���( ���ְ� �踦 ź�ٴ� ������ )
	if ( MyID == ShipPassengerCharID )
	{
		AddedIndex = pShipListObj->Add( &pclCI->clBI.clPerson, MyID, SHIP_JOB_OWNER );
		if ( AddedIndex < 0 )
		{
			pclServer->SendServerResponseMsg(0, SRVAL_SHIP_PASSENGERNUM_EXCEED, 0, 0, GetCharUnique());
			return;
		}

		cltShipPassenger clTempShipPassenger;
		clTempShipPassenger.Init();
		clTempShipPassenger.Set( &pclCI->clBI.clPerson, ShipPassengerCharID, SHIP_JOB_OWNER );

		// ���ֿ��� �¼��ϰ� ������ �˸�
		cltGameMsgResponse_ShipPersonEmbarkAllow clinfo( ShipID, AddedIndex, &clTempShipPassenger );
		cltMsg clMsg( GAMEMSG_RESPONSE_SHIPPERSONEMBARKALLOW,  sizeof( clinfo ), (char*)&clinfo );
		SendNetMsg((char*)&clMsg);
		
		// �°�(=����)���� �¼��Ǿ����� �˸�
		cltGameMsgResponse_ShipPersonEmbarkAllowNotify clinfo1( ShipID, pShipListObj->GetShipCharUnique(), GetCharUnique(), AddedIndex );
		cltMsg clMsg1( GAMEMSG_RESPONSE_SHIPPERSONEMBARKALLOWNOTIFY,  sizeof( clinfo1 ), (char*)&clinfo1 );
		pclClient->pclCM->CR[ShipPassengerCharID]->SendNetMsg((char*)&clMsg1);
	}
	else
	{
		AddedIndex = pShipListObj->Add( &pclClient->pclCM->CR[ShipPassengerCharID]->pclCI->clBI.clPerson, ShipPassengerCharID, SHIP_JOB_PASSENGER );
		if ( AddedIndex < 0 )
		{			
			pclServer->SendServerResponseMsg(0, SRVAL_SHIP_PASSENGERNUM_EXCEED, 0, 0, GetCharUnique());
			return;
		}

		cltShipPassenger clTempShipPassenger;
		clTempShipPassenger.Init();
		clTempShipPassenger.Set( &pclClient->pclCM->CR[ShipPassengerCharID]->pclCI->clBI.clPerson, ShipPassengerCharID, SHIP_JOB_PASSENGER );

		// ���ֿ��� �¼��ϰ� ������ �˸�
		cltGameMsgResponse_ShipPersonEmbarkAllow clinfo( ShipID, AddedIndex, &clTempShipPassenger );
		cltMsg clMsg( GAMEMSG_RESPONSE_SHIPPERSONEMBARKALLOW,  sizeof( clinfo ), (char*)&clinfo );
		SendNetMsg((char*)&clMsg);
		
		// �°����� �¼��Ǿ����� �˸�
		cltGameMsgResponse_ShipPersonEmbarkAllowNotify clinfo1( ShipID, pShipListObj->GetShipCharUnique(), pShipListObj->m_siShipOwnerCharUnique, AddedIndex );
		cltMsg clMsg1( GAMEMSG_RESPONSE_SHIPPERSONEMBARKALLOWNOTIFY,  sizeof( clinfo1 ), (char*)&clinfo1 );
		pclClient->pclCM->CR[ShipPassengerCharID]->SendNetMsg((char*)&clMsg1);
	}
		
	pclClient->pclCM->CR[ShipPassengerCharID]->siRequestEmbarkShipID = 0;
	pclClient->pclCM->CR[ShipPassengerCharID]->clInnerStatus.siRideShipID = ShipID;	

	pShipListObj->PersonWarpIntoShip(pclClient->pclCM->CR[ShipPassengerCharID]->pclCI->GetPersonID() );

	cltCharServer *pclPassengerChar = (cltCharServer *)pclClient->pclCM->CR[ShipPassengerCharID];
	pclPassengerChar->SendInnerStatusToNeighbour();

	return;
}

// �ϼ� - �� ������ �迡�� ������ �����
void cltCharCommon::DisEmbarkShip( SI32 ShipID, bool Force )
{
	if ( ShipID < 1 )
	{
		return;
	}

	// �迡 Ÿ�� ���� ���� ���� �Ǵ� �ٸ� �迡�� �ϼ��϶�� ����� ���.
	if ( clInnerStatus.siRideShipID < 1 || clInnerStatus.siRideShipID != ShipID )
	{
		return;
	}

	CShipListObj *pShipListObj = pclClient->pclShipListMgr->GetShipListObj( ShipID );

	// �踦 Ÿ��� �ִµ�, �谡 ���� ���� �̻��� ���.
	if ( pShipListObj == NULL )
	{
		char* pText = GetTxtFromMgr(3810);
		pclClient->pclLog->FilePrint( "Config/Ship.txt", pText, ShipID );
		return;
	}
	
	SI32 DisEmbarkX, DisEmbarkY;
	if ( pclMap->FindEmptyAreaForCharLocate( GetKind(), GetX(), GetY(), 10, &DisEmbarkX, &DisEmbarkY, true ) )
	{
		OrderStop(GetID(), BY_COMPUTER);
		((cltCharServer*)this)->SetInitProtectSwitch();

		cltWarpInfo clWarpInfo(1, GetMapIndex(), true, false, DisEmbarkX, DisEmbarkY, -1, -1);
		SetWarpInfo(&clWarpInfo, 3463);
		//Warp();
	}
	else
	{
		// ��ó�� �ϼ� �� ���� ���� ���¿��� ���� �ϼ� �̶��... �溹������ ���� ����
		if ( Force )
		{
			OrderStop(GetID(), BY_COMPUTER);
			((cltCharServer*)this)->SetInitProtectSwitch();
			
			if ( pclClient->siServiceArea == ConstServiceArea_China )
			{
				cltWarpInfo clWarpInfo(1, MAPINDEX_PALACE, true, false, 27, 87, -1, -1);
				SetWarpInfo( &clWarpInfo, 2465 );
			}
			else
			{
				if ( pclKI->siDefaultCountry == ConstServiceArea_China )
				{
					cltWarpInfo clWarpInfo(1, MAPINDEX_CHINABORDER, true, false, 17, 19, -1, -1);
					SetWarpInfo( &clWarpInfo, 2465 );
				}
				else
				{
					cltWarpInfo clWarpInfo(1, MAPINDEX_PALACE, true, false, 27, 87, -1, -1);
					SetWarpInfo( &clWarpInfo, 2465 );
				}
			}
			//Warp();
		}
		else
		{	
			// ���� �ϼ��� �� ���� ��ġ���� �˷������..
			return;
		}
	}
		
	pShipListObj->Del( pclCI->GetPersonID() );

	/*
	cltGameMsgResponse_ShipPersonDisEmbark clinfo( true, ShipID );
	cltMsg clMsg( GAMEMSG_RESPONSE_SHIPPERSONDISEMBARK,  sizeof( clinfo ), (char*)&clinfo );
	SendNetMsg( (char*)&clMsg );
	*/

	ShipPassengerDataInit();

	cltCharServer *pclChar = (cltCharServer *)this;
	pclChar->SendInnerStatusToNeighbour();	

	return;
}

// �ϼ� - �� ������ �迡�� ������ �����
void cltCharCommon::QuitGameDisEmbarkShip( SI32 ShipID, bool Force )
{
	if ( ShipID < 1 )
	{
		return;
	}

	// �迡 Ÿ�� ���� ���� ���� �Ǵ� �ٸ� �迡�� �ϼ��϶�� ����� ���.
	if ( clInnerStatus.siRideShipID < 1 || clInnerStatus.siRideShipID != ShipID )
	{
		return;
	}

	CShipListObj *pShipListObj = pclClient->pclShipListMgr->GetShipListObj( ShipID );

	// �踦 Ÿ��� �ִµ�, �谡 ���� ���� �̻��� ���.
	if ( pShipListObj == NULL )
	{
		char* pText = GetTxtFromMgr(3811);
		pclClient->pclLog->FilePrint( "Config/Ship.txt", pText, ShipID );
		return;
	}
	
	SI32 villageunique = 0;
	if(villageunique<=0)
	{
		// ���� ��ġ�� ������ �θ� ������ ã�´�. 
		SI32 parentmap = pclClient->pclMapManager->GetParentMap( GetMapIndex() );
		if(parentmap == 0)parentmap = GetMapIndex();


		// �θ� ������ �߿����� ��ǥ�� ã�´�. 
		SI32 x, y;
		if( parentmap != 0 &&
			pclClient->pclMapManager->pclGateManager->FindMainFieldPos(parentmap, &x, &y) == true )
		{
		}
		else
		{
			x	= pclCI->clBI.clLastMainMapPos.siX;
			y	= pclCI->clBI.clLastMainMapPos.siY;

		}

		// ����� ������ ã�´�.
		villageunique = pclClient->pclVillageManager->FindNearVillage(x, y);
	}
	
	if(villageunique >0)
	{
		
		SI32 mapindex	= pclClient->pclVillageManager->pclVillageInfo[villageunique]->siVillageUnique;
		
		SI32 maptypeunique = pclClient->pclMapManager->pclMapArray[ mapindex ]->siMapUnique;
		SI32 centerx = pclClient->pclMapManager->pclMapTypeManager->pclMapTypeInfo[maptypeunique]->siCenterX;
		SI32 centery = pclClient->pclMapManager->pclMapTypeManager->pclMapTypeInfo[maptypeunique]->siCenterY;

		OrderStop(siID, BY_COMPUTER);
		((cltCharServer*)this)->SetInitProtectSwitch();
		
		cltWarpInfo clWarpInfo(1, mapindex, true, false, centerx, centery, -1, -1);
		SetWarpInfo(&clWarpInfo, 3464);
		Warp();
	}
	else
	{
		if ( Force )
		{
			OrderStop(siID, BY_COMPUTER);
			((cltCharServer*)this)->SetInitProtectSwitch();

			if ( pclClient->siServiceArea == ConstServiceArea_China )
			{
				cltWarpInfo clWarpInfo(1, MAPINDEX_PALACE, true, false, 27, 87, -1, -1);
				SetWarpInfo( &clWarpInfo, 2465 );
				Warp();
			}
			else
			{
				if ( pclKI->siDefaultCountry == ConstServiceArea_China )
				{
					cltWarpInfo clWarpInfo(1, MAPINDEX_CHINABORDER, true, false, 17, 19, -1, -1);
					SetWarpInfo( &clWarpInfo, 2465 );
					Warp();
				}
				else
				{
					cltWarpInfo clWarpInfo(1, MAPINDEX_PALACE, true, false, 27, 87, -1, -1);
					SetWarpInfo( &clWarpInfo, 2465 );
					Warp();
				}
			}
		}
		else
		{	
			// ���� �ϼ��� �� ���� ��ġ���� �˷������..
			return;
		}
	}

	pShipListObj->Del( pclCI->GetPersonID() );	

	/*
	cltGameMsgResponse_ShipPersonDisEmbark clinfo( true, ShipID );
	cltMsg clMsg( GAMEMSG_RESPONSE_SHIPPERSONDISEMBARK,  sizeof( clinfo ), (char*)&clinfo );
	SendNetMsg( (char*)&clMsg );
	*/

	ShipPassengerDataInit();

	cltCharServer *pclChar = (cltCharServer *)this;
	pclChar->SendInnerStatusToNeighbour();	

	return;
}


// ������ ��ġ�� ����Ǿ���. 
void cltCharCommon::ShipMoveAction()
{
	// �������� �Ѵ�. 
	if(pclClient->GameMode != GAMEMODE_SERVER)return ;
	
	// �谡 �ƴϸ� �����Ѵ�. 
	if(IsShip(GetCharUnique()) == false)return ;	
	

	if ( clInnerStatus.siSelfShipID > 0 )
	{	
		CShipListObj *pShipLibObj = pclClient->pclShipListMgr->GetShipListObj( clInnerStatus.siSelfShipID );
		
		if ( pShipLibObj == NULL )
		{
			pclClient->pclLog->FilePrint("Config/Ship.txt", "ShipMoveAction pShipListObj == NULL, clInnerStatus.siSelfShipID = %d", clInnerStatus.siSelfShipID );
			return;
		}

		pShipLibObj->ShipAndPersonMove( GetX(), GetY() );
	}
}

// �� ����� �����ַ� �踦 �����.
bool cltCharCommon::MakeShip( cltShip *pclShip )
{
	if ( pclShip->siKind < 1 )
	{
		return false;
	}

	// ����� �������� �ʾ���.
	// �� ������� �ʾ���.


	
	SI32 MakeShipHnd = pclCI->clIP.GetHnd();

	// �����ֿ� ���� �� ���� ����
	SI16 Ref = pclClient->pclShipManager->GetRefFromShipKind( pclShip->siKind );
	if ( Ref < 0 )
	{
		return false;
	}

	// ������ �������� �� ���� �Ұ���
	if ( pclClient->pclShipManager->pclShipBaseInfoList[ Ref ]->m_siNeedHnd > MakeShipHnd )
	{
		return false;
	}

	// �ִ� �����ִ� 500 �̰� 500�϶� 25 % �� ���� ������ �����ϴ�.
	float MaxIncresePercent = 0.25f;
	float MaxHnd = 500.0f;


	//float IncreasePercent = MaxIncresePercent * MakeShipHnd / MaxHnd;

	// �켱�� �����ֿ� ���� ���� ��� ���� ����. ( ���� Ǯ�� �ٷ� �� )
	float IncreasePercent = 0.f;

	pclShip->siAP += (SI32)(pclShip->siAP * IncreasePercent);
	pclShip->siAC += (SI32)(pclShip->siAC * IncreasePercent);
	pclShip->siMoveSpeed += (SI32)(pclShip->siMoveSpeed * IncreasePercent);
	//pclShip->siMaxDurability += (SI32)( ( pclShip->siMaxDurability * 4 ) * IncreasePercent);
	pclShip->siDecreaseDurability = 0;
	pclShip->siDurability = pclShip->siDurability;

	// �ӵ��� �ִ� 20 �̴�.
	if ( pclShip->siMoveSpeed > 20 )
	{
		pclShip->siMoveSpeed = 20;
	}

	// �������� �ִ� 10000 �̴�.
	if ( pclShip->siDurability > 30000 )
	{
		pclShip->siDurability = 30000;
	}

	return true;
}

// �� ����� �����ַ� � �谡 ����� ������ ���� ������ �޾ƿ�( Ŭ���̾�Ʈ����. )
bool cltCharCommon::GetShipPerformance( cltShip *pShip, char *ShipText )
{
	if ( pShip == NULL || pShip->siShipID < 1 || ShipText == NULL )
	{
		return false;
	}

	return false;
}

