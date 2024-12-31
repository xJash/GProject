#include "ServerMap.h"

#include "ITZCell.h"
#include "ITZPerson.h"
#include "..\Server.h"
#include "MsgType.h"
#include "MsgType-Item.h"

#include "../../common/Char/CharServer/Char-Server.h"
#include "../../common/Char/CharManager/CharManager.h"

extern cltCommonLogic* pclClient;

cltServerMap::cltServerMap()
{
}

cltServerMap::~cltServerMap()
{
}


// ���� �߰��� �� ������ �ִ� �����鿡�� pPerson�� ������ �˸���
void cltServerMap::SendPersonEnterMsgToOthers( ITZPerson *pPerson, bool bticketusewarpswitch )
{

	cltCharServer *pChar = (cltCharServer *)pPerson;
	
	// ĳ������ ������ ���´�. 
	//---------------------------------
	// ���� ���� ���� �� ���� ������ �ߴ��� ���� ������ ���ؾ� �Ѵ�.
	//---------------------------------
	if(pChar->GetKind() == pclClient->GetUniqueFromHash( TEXT("KIND_BOMBDRAGON") ) ) 
	{
		SI32 a = 0;
	}
	cltMakeCharInfo	clMakeCharInfo;
	if(pChar->GetMakeCharInfo(&clMakeCharInfo, true, bticketusewarpswitch) == false)return;

	cltMsg clMsg(GAMEMSG_RESPONSE_LOGIN, sizeof(clMakeCharInfo), (BYTE*)&clMakeCharInfo);

	for( UI32 i = 0; i < m_uiNewCellCount; ++i ) {
	
		m_pNewCell[ i ]->SendPacket( (sPacketHeader *)&clMsg );			// �ش� ���� �ִ� �����鿡�� ��Ŷ ����
	
	}
	
}

// ������ �� ������ �ִ� �����鿡�� pPerson�� ������ �˸���
void cltServerMap::SendPersonLeaveMsgToOthers( ITZPerson *pPerson )
{

	cltCharServer *pChar = (cltCharServer *)pPerson;

	cltMsg clMsg(GAMEMSG_RESPONSE_LOGOUT, pChar->GetCharUnique());
	
	for( UI32 i = 0; i < m_uiRemoveCellCount; ++i ) {
		
		m_pRemoveCell[ i ]->SendPacket( (sPacketHeader *)&clMsg );		// �ش� ���� �ִ� �����鿡�� ��Ŷ ����
	}

}

// pPerson�� �̵� ������ ���ÿ����� �ִ� �����鿡�� �˸��� 
void cltServerMap::SendPersonMoveMsgToOthers( ITZPerson *pPerson )
{
	//pPerson->GetCell()->SendPacketNearAll( );		// pPerson�� ���ÿ����� �ִ� �����鿡�� �̵� ��Ŷ ���� 
}


// ���� �߰��� �� ������ �ִ� ĳ���͵��� ������ pPerson���� �˸��� 
void cltServerMap::SendNewOthersInfoToPerson( ITZPerson *pPerson )
{

	ITZObjectPtr *pItor;
	ITZPerson *pOtherPerson;
	cltCharServer *pChar;

	cltMsg clMsg(GAMEMSG_RESPONSE_LOGINMANY, 0, NULL);
	SI32 index = 0;

	if(pPerson->GetSession() == NULL)return ;

	for( UI32 i = 0; i < m_uiNewCellCount; ++i ) 
	{  

		LIST_LOOP( &m_pNewCell[ i ]->m_personPtrList, pItor )
		{
			pOtherPerson = (ITZPerson *)pItor->GetObject();

			pChar = (cltCharServer *)pOtherPerson;
			if(pChar == NULL)
			{
				pclClient->pclLog->FilePrint(TEXT("Config\\ErrorLog.log"), TEXT("SendNewOthersInfoToPerson()"));
				continue;
			}

			//-------------------------------
			// ���� ĳ������ �޽����� �����. 
			//--------------------------------
			cltMakeCharInfo	clMakeCharInfo;
			if(pChar->GetMakeCharInfo(&clMakeCharInfo, true, false) == false)continue;

			//-------------------------------
			// ���� ĳ������ �޽����� �����Ѵ�. 
			//--------------------------------
			if(clMakeCharInfo.uiType == MAKECHARTYPE_PC)
			{
				memcpy(&clMsg.cData[index], &clMakeCharInfo, sizeof(clMakeCharInfo));
				index += sizeof(clMakeCharInfo);
			}
			else 
			{
				memcpy(&clMsg.cData[index], &clMakeCharInfo, sizeof(cltMakeCharInfoCommon));
				index += sizeof(cltMakeCharInfoCommon);
			}

			//----------------------------------------
			// �ִ� ����� �����ϸ� �޽����� ������.
			//-----------------------------------------
			if(index + sizeof(clMakeCharInfo) >= MAX_CLTMSG_DATA_SIZE)
			{
				clMsg.clHead.usSize = sizeof(sPacketHeader) + index;

				cltCharServer* pclchar = pclClient->pclCM->GetCharServer( pPerson->GetCharID() );
				if( pclchar )
				{
					pclchar->SendNetMsg( (sPacketHeader*)&clMsg );
				}
				index = 0;	// �ٽ� ó������ �����Ѵ�. 
			}
		}

	}

	//-------------------------------------------
	// �������� ���� �޽����� �ִٸ� ������.
	//-------------------------------------------
	if(index)
	{
		clMsg.clHead.usSize = sizeof(sPacketHeader) + index;

		cltCharServer* pclchar = pclClient->pclCM->GetCharServer( pPerson->GetCharID() );
		if( pclchar )
		{
			pclchar->SendNetMsg( (sPacketHeader*)&clMsg );
		}
		index = 0;	// �ٽ� ó������ �����Ѵ�. 
	}

	


	for( i = 0; i < m_uiRemoveCellCount; ++i ) {

		LIST_LOOP( &m_pRemoveCell[ i ]->m_personPtrList, pItor )
		{
			pOtherPerson = (ITZPerson *)pItor->GetObject();

			pChar = (cltCharServer *)pOtherPerson;

			if( pChar == NULL ) continue;

			cltMsg clMsg(GAMEMSG_RESPONSE_LOGOUT, pChar->GetCharUnique());
			//pPerson->GetSendBuffer()->Write( (BYTE *)&clMsg );
			cltCharServer* pclchar = pclClient->pclCM->GetCharServer( pPerson->GetCharID() );
			if( pclchar )
			{
				pclchar->SendNetMsg( (sPacketHeader*)&clMsg );
			}
		}
	}
}

// ���� �߰��� �� ������ �ִ� �����۵��� ������ pPerson���� �˸��� 
void cltServerMap::SendNewItemsInfoToPerson( ITZPerson *pPerson )
{
	UI32 i, j;
	sItem *pItem;

	cltServer* pclServer = (cltServer*)pclClient;

	if(pPerson->GetSession() == NULL)return ;

	// ���� �߰��� �� ���� ��ŭ �ݺ� 
	for( i = 0; i < m_uiNewCellCount; ++i ) {  

		// ���� �ִ� ������ ���� ���� ��ŭ �ݺ� 
		for( j = 0; j < m_pNewCell[ i ]->m_uiItemSlotCount; ++j ) {
			
			pItem = m_pNewCell[ i ]->m_ppItem[ j ];

			// ������ ���Կ� �������� ������ �� ������ pPerson���� ���� 
			if( pItem->itemIndex != 0 ) {

				cItemNode* pnode = pclServer->pclItemList->GetItem(pItem->itemIndex);
				if(pnode)
				{
					SI32 itemunique	= pnode->item.siUnique;
					SI32 x			= pnode->x;
					SI32 y			= pnode->y;
					SI32 mapindex	= pnode->mapIndex;

					cltCharPos clPos(mapindex, x, y);
					cltGameMsgResponse_ItemDrop clInfo(&clPos, itemunique, pItem->itemIndex);
					cltMsg clMsg(GAMEMSG_RESPONSE_ITEMDROP, sizeof(clInfo), (BYTE*)&clInfo);

					//pPerson->GetSendBuffer()->Write((BYTE*)&clMsg);
					cltCharServer* pclchar = pclClient->pclCM->GetCharServer( pPerson->GetCharID() );
					if( pclchar )
					{
						pclchar->SendNetMsg( (sPacketHeader*)&clMsg );
					}
				}
			}
		}
	}

	// ������ �� ���� ��ŭ �ݺ�
	for( i = 0; i < m_uiRemoveCellCount; ++i ) {  

		// ���� �ִ� ������ ���� ���� ��ŭ �ݺ� 
		for( j = 0; j < m_pRemoveCell[ i ]->m_uiItemSlotCount; ++j ) {
			
			pItem = m_pRemoveCell[ i ]->m_ppItem[ j ];

			// ������ ���Կ� �������� ������ �� ������ pPerson���� ���� 
			if( pItem->itemIndex != 0 ) {

				cItemNode* pnode = pclServer->pclItemList->GetItem(pItem->itemIndex);
				if(pnode)
				{
					SI32 itemunique	= 0;			// ������ ���� ����. 
					SI32 x			= pnode->x;
					SI32 y			= pnode->y;
					SI32 mapindex	= pnode->mapIndex;

					cltCharPos clPos(mapindex, x, y);
					cltGameMsgResponse_ItemDrop clInfo(&clPos, itemunique, 0);
					cltMsg clMsg(GAMEMSG_RESPONSE_ITEMDROP, sizeof(clInfo), (BYTE*)&clInfo);

					//pPerson->GetSendBuffer()->Write((BYTE*)&clMsg);
					cltCharServer* pclchar = pclClient->pclCM->GetCharServer( pPerson->GetCharID() );
					if( pclchar )
					{
						pclchar->SendNetMsg( (sPacketHeader*)&clMsg );
					}
				}
			}
		}
	}
}


void cltServerMap::SendAddItemMsgToOthers( sItem *pItem )
{
	ITZCell *pCell = GetCell( pItem->x, pItem->y );

	if( pItem->itemIndex == 0 )return ;

	if( pCell == NULL)return ;

	cltServer* pclServer = (cltServer*)pclClient;

	cItemNode* pnode = pclServer->pclItemList->GetItem(pItem->itemIndex);
	if(pnode)
	{
		SI32 itemunique	= pnode->item.siUnique;			
		SI32 x			= pnode->x;
		SI32 y			= pnode->y;
		SI32 mapindex	= pnode->mapIndex;
		
		cltCharPos clPos(mapindex, x, y);
		cltGameMsgResponse_ItemDrop clInfo(&clPos, itemunique, pItem->itemIndex);
		cltMsg clMsg(GAMEMSG_RESPONSE_ITEMDROP, sizeof(clInfo), (BYTE*)&clInfo);
	
		pCell->SendPacketNearAll( (sPacketHeader*)&clMsg);
		
	}
}


void cltServerMap::SendDelItemMsgToOthers( sItem *pItem )
{
	ITZCell *pCell = GetCell( pItem->x, pItem->y );

	if( pItem->itemIndex == 0 )return ;

	if( pCell == NULL)return ;

	cltServer* pclServer = (cltServer*)pclClient;

	cItemNode* pnode = pclServer->pclItemList->GetItem(pItem->itemIndex);
	if(pnode)
	{
		SI32 itemunique	= 0;			// ������ ���� ����. 
		SI32 x			= pnode->x;
		SI32 y			= pnode->y;
		SI32 mapindex	= pnode->mapIndex;
		
		cltCharPos clPos(mapindex, x, y);
		cltGameMsgResponse_ItemDrop clInfo(&clPos, itemunique, 0);
		cltMsg clMsg(GAMEMSG_RESPONSE_ITEMDROP, sizeof(clInfo), (BYTE*)&clInfo);
	
		pCell->SendPacketNearAll( (sPacketHeader*)&clMsg);
	}
}
