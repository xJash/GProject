
#include "Char/CharManager/CharManager.h"
#include "../Server/Server.h"

#include "../../common/Order/order.h"

#include "../../../DBManager/GameDBManager_World/DBMsg.h"

#include "MsgRval-Define.h"
#include "MsgType-Person.h"
#include "MsgType-Item.h"

#include "../../../DBManager//GameDBManager_World/DBMsg-Family.h"
#include "../../../DBManager//GameDBManager_World/DBMsg-Item.h"

void cltServer::DoMsg_GAMEMSG_REQUEST_FAMILY_REQUEST_ADD_FAMILY(cltMsg* pclMsg, SI32 id )
{	
	cltGameRequest_Request_Add_Children* pclinfo = (cltGameRequest_Request_Add_Children*)pclMsg->cData;
	if ( NULL == pclinfo ){		return;	}
	if(IsCountrySwitch( Switch_We_Are_Family ) == false )	return	;

	cltCharCommon* pParentChar	=	pclCM->GetChar( id )	;
	if( pParentChar == NULL	)	return	;
	// ����� 
	SI32 siMatePersonID = pParentChar->pclMarriage->GetMatePersonID() ;		if ( siMatePersonID <= 0 )	return	;

	SI32 siMateid = pclCM->GetIDFromPersonID( siMatePersonID )	;
	if ( pclCM->IsValidID(siMateid) == false )
	{
		SendServerResponseMsg( 0, SRVAL_FAMILY_ADD_WRONG_NOTCONNECT_MATE, 0, 0, pParentChar->GetCharUnique() );	// �߸��� �ɸ��� �̴�		
		return	;
	}
	cltCharCommon* pMateChar	=	pclCM->GetChar( siMateid )	;			if ( pMateChar == NULL )	return	;

	SI32 siChildren_CharID	=	pclCM->GetIDFromName( pclinfo->m_szCharName )	;	// �ɸ��� �̸����� �ɸ����� ���̵� ���Ѵ�.
	if ( pclCM->IsValidID(siChildren_CharID)==false )
	{
		SendServerResponseMsg( 0, SRVAL_FAMILY_ADD_ERROR_NO_CHAR, 0, 0, pParentChar->GetCharUnique() );	// �߸��� �ɸ��� �̴�
		return	;
	}

	cltCharCommon* pChildrenChar	=	pclCM->GetChar( siChildren_CharID )	;		// �ڳడ �� �ɸ��� �� ���̵�.

	if( pChildrenChar == NULL	)	return	;

	// �̹� ������ ���� ��쿡�� ��û ����
	if ( pChildrenChar->IsMarried() == TRUE || pChildrenChar->pclFamily->GetMyClass_InFamily() > 0  )
	{
		SendServerResponseMsg( 0, SRVAL_FAMILY_ADD_WRONG_BEFORE_IN_FAMILY, 0, 0, pParentChar->GetCharUnique() );	//�̹� ������ �ִ� �ɸ��� 
		return	;
	}

	// Ŭ���̾�Ʈ���� �����ش�
	cltGameResponse_Request_Add_Children clinfo( pParentChar->pclCI->GetPersonID(),(TCHAR*)pParentChar->GetName(),
		pMateChar->pclCI->GetPersonID()	,(TCHAR*)pMateChar->GetName(),
		pChildrenChar->pclCI->GetPersonID(),(TCHAR*)pChildrenChar->GetName());
	
	cltMsg clMsg( GAMEMSG_RESPONSE_FAMILY_REQUEST_ADD_CHILDREN, sizeof(clinfo), (BYTE*)&clinfo );
	pChildrenChar->SendNetMsg( (sPacketHeader*)&clMsg );


}
void cltServer::DoMsg_GAMEMSG_REQUEST_FAMILY_ADD_FAMILY(cltMsg* pclMsg, SI32 id )	//��û�� �����ϸ� �������� ����.
{
	//�ڽ��� �ϰڴٴ� ������ �Ͽ���.
	cltGameRequest_Add_Children* pclinfo = (cltGameRequest_Add_Children*)pclMsg->cData;		if ( NULL == pclinfo ){		return;	}
	if(IsCountrySwitch( Switch_We_Are_Family ) == false )	return	;

	SI32 siParentPersonID = pclinfo->m_siParentPersonID	;
	SI32 siParentID = pclCM->GetIDFromPersonID(siParentPersonID) ;

	cltCharCommon* pParentChar	=	pclCM->GetChar( siParentID )	;						if( pParentChar == NULL	)	return	;

	 SI32 siMatePersonID = pParentChar->pclMarriage->GetMatePersonID()	;
	 SI32 siMateId = pclCM->GetIDFromPersonID( siMatePersonID )	;	
	 cltCharServer* pMateCharServer = pclCM->GetCharServer( siMateId )	;

	 if(pMateCharServer == NULL )	// ����ڰ� ������ 
	 {
		 SendServerResponseMsg( 0, SRVAL_FAMILY_ADD_WRONG_NOTCONNECT_MATE, 0, 0, pParentChar->GetCharUnique() );	// ����ڰ� ���� ��� �Ұ��� 
		return	;
	 }

	cltCharCommon* pChildrenChar	=	pclCM->GetChar( id )	;		// �ڳడ �� �ɸ��� �� ���̵�.
	if( pChildrenChar == NULL	)	return	;

	// üũ ���� 
	// 1. ���� ��� �̿���� �ִ°�?
	bool bUsedItem		=	false	;	// ����ߴ��� Ȯ��
	SI32 siUseItem		=	ITEMUNIQUE( 24121 )	;	// ���� �̿�� 
	SI32 siUseItemNum	=	1 ;						// 1��
	cltItem clitem;
	SI32 siref = pclClient->pclItemManager->FindItemRefFromUnique(siUseItem);			if(siref <= 0) return ;
	SI32 siHaveitemNum = pParentChar->pclCI->clCharItem.GetItemNum( siUseItem ) ;	// �������� � ������ �ִ��� Ȯ��.
	
	if ( siHaveitemNum >= siUseItemNum ) // ����� ���� �ִٸ� 
	{
		for(SI32 i = PERSONITEM_INV0;i < PERSONITEM_INV0 + MAX_INVITEM_PER_PERSON;i++)
		{
			if(pParentChar->pclCI->clCharItem.clItem[i].siUnique == siUseItem)
			{
				if ( siUseItemNum == 0 )	break	;	// ������ 0���� ������
				SI32 invItemNum = pParentChar->pclCI->clCharItem.clItem[i].GetItemNum()	;
				if ( invItemNum  >= siUseItemNum )
				{
					clitem.Set(&pclClient->pclItemManager->pclItemInfo[siref]->clItem);
					clitem.siItemNum = siUseItemNum;
					sDBRequest_UseItem clMsg(pParentChar->GetID(), pParentChar->pclCI->GetPersonID(), i, &clitem, USEITEM_REASON_NONE);
					pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
					bUsedItem	=	true	;
					break	;
				}
				else
				{
					clitem.Set(&pclClient->pclItemManager->pclItemInfo[siref]->clItem);
					clitem.siItemNum = invItemNum	;// �縸ŭ �ְ�
					//��ü �������� ���ش�
					siUseItemNum =  siUseItemNum - invItemNum	;
					// ����ض�
					sDBRequest_UseItem clMsg(pParentChar->GetID(), pParentChar->pclCI->GetPersonID(), i, &clitem, USEITEM_REASON_NONE);
					pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
					bUsedItem	=	true	;
				}
			}
		}
	}

	if ( bUsedItem == false ) 
	{
		// �������� ��� ����� ���ߴ� ���� �޼����� �����ش�.
		SendServerResponseMsg( 0, SRVAL_FAMILY_ADD_WRONG_No_TICKET, siUseItem, 0, pParentChar->GetCharUnique() );	// �߸��� �ɸ��� �̴�
		return	;
	}

	SYSTEMTIME stAddTime	;

	ZeroMemory(&stAddTime,	sizeof(SYSTEMTIME));

	TimeAddDate(&sTime,30,&stAddTime)	;

	// ���� �������� �߰� �Ѵ�.
	AddFamily(pParentChar->pclCI->GetPersonID(), pChildrenChar->pclCI->GetPersonID() ,stAddTime )	;	//�ð������� ���� �L��

	//DB�� ���� �Ѵ�.
	sDBRequest_Family_Add_Children clMsg( pParentChar->pclCI->GetPersonID(),(TCHAR*)pParentChar->GetName(),	
		pChildrenChar->pclCI->GetPersonID() , (TCHAR*)pChildrenChar->GetName(),
		stAddTime );// �ڽ� personID�� ������.
	SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
}
void cltServer::DoMsg_GAMEMSG_REQUEST_FAMILY_DEL_CHILDREN(cltMsg* pclMsg, SI32 id )	// �������� ���� 
{
	cltGameRequest_Del_Children* pclinfo = (cltGameRequest_Del_Children*)pclMsg->cData;
	if ( NULL == pclinfo ){		return;	}
	if(IsCountrySwitch( Switch_We_Are_Family ))
	{
		cltCharServer* pclcharRequestChar = pclCM->GetCharServer( id)	;				// ������ �õ��ϴ� �ɸ���
		
		SI32 siDetTargetId	=	pclCM->GetIDFromPersonID( pclinfo->m_siPersonID )	;	// ������ Ÿ�� �ɸ���
		cltCharServer* pclDelTargetchar = pclCM->GetCharServer( siDetTargetId)		;	
		if( pclDelTargetchar == NULL )	// �ش� �ɸ��Ͱ� ������ 
		{
			// ������ �ߴµ� Ż�� Ÿ���� �Ƿ��� ������ �ڽ��ϻ��� ����.
			// ������ ������. 
			cltLetterMsg_DelLetter clletter1;
			SendLetterMsg(pclinfo->m_siPersonID, (cltLetterHeader*)&clletter1);

			sDBRequest_Family_Del_Children clMsg( pclinfo->m_siPersonID );				// �ڽ� personID�� ������.
			SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
		}
		else	// �ش� �ɸ��Ͱ� ���� �� �ִ�.
		{
			// ������ �ִٸ� Ÿ���� ��ȥ�ߴ��� Ȯ��
			if( pclDelTargetchar->IsMarried() == TRUE )	//  �⺻������ ��ȥ �ߴٸ� �θ� �ɸ��� �̴�.
			{
				if(pclDelTargetchar->pclFamily != NULL && pclDelTargetchar->pclFamily->GetMyClass_InFamily() > MYCLASS_IN_FAMILY_NONE )	// �ڽ��� ������ �ִ�. ���������� ����.
				{
					// �ڽ��� �ִٸ� �ش� �ɸ��ʹ� ������ ������ ������ �ִ�.
					if( pclDelTargetchar->pclFamily->GetChildPersonID( 0 ) > 0)	// 0�� ���Կ� �ڽ��� �ִ��� Ȯ�� �Ѵ�.
					{
						// �ڽ��� �ִ�. ��ȥ�Ұ���
						SendServerResponseMsg( 0, SRVAL_FAMILY_ADD_WRONG_DEL_HAVECHILD, 0, 0, pclDelTargetchar->GetCharUnique() );
					}
					else
					{
						SI32 siMatePersonID = pclDelTargetchar->pclFamily->GetMatePersonID( pclDelTargetchar->pclCI->GetPersonID() )	;// Ÿ���� ����� 

						SI32 siMateID = pclCM->GetIDFromPersonID( siMatePersonID )	;
						cltCharServer* pclMateChar = pclCM->GetCharServer( siMateID)	;	
						if(pclMateChar != NULL )		// ����ڰ� NULL ���������� �ʴ�. Ư���� ������Ʈ�� �ʿ� ����.
						{
							pclMateChar->pclFamily->Init()	;	// �ʱ�ȭ �ϰ� Ŭ���̾�Ʈ�� ������Ʈ ���ش�.
							pclMateChar->pclMarriage->Init()	;	// �ʱ�ȭ �ϰ� Ŭ���̾�Ʈ�� ������Ʈ ���ش�.

							// �������϶��� �׳� �����ٴ� �޼����� �����ָ� �ȴ�
							cltLetterMsg_LeaveFamilyLetter clletter( (TCHAR*)pclDelTargetchar->GetName());
							SendLetterMsg( siMatePersonID , (cltLetterHeader*)&clletter );
							
							cltGameResponse_UpdateFamily clinfo( pclMateChar->pclFamily,pclMateChar->pclMarriage );
							cltMsg clMsgtoClient( GAMEMSG_RESPONSE_FAMILY_UPDATE, sizeof(clinfo), (BYTE*)&clinfo );
							pclMateChar->SendNetMsg( (sPacketHeader*)&clMsgtoClient );
						}
						// ����ڸ� ������Ʈ �������� ���� ���� �ʱ�ȭ �Ѵ�.
						pclDelTargetchar->pclFamily->Init()	;	// �������� �ʱ�ȭ
						pclDelTargetchar->pclMarriage->Init()	;	// ��ȥ���� �ʱ�ȭ

						SendServerResponseMsg( 0, SRVAL_FAMILY_ADD_WRONG_DEL_FAMILY, 0, 0, pclDelTargetchar->GetCharUnique() );

						//��������� Ŭ���̾�Ʈ�� �ʱ�ȭ�ϰ� Ŭ���̾�Ʈ�� �˷��ش�.
						cltGameResponse_UpdateFamily clinfo( pclDelTargetchar->pclFamily,pclDelTargetchar->pclMarriage );
						cltMsg clMsgtoClient( GAMEMSG_RESPONSE_FAMILY_UPDATE, sizeof(clinfo), (BYTE*)&clinfo );
						pclDelTargetchar->SendNetMsg( (sPacketHeader*)&clMsgtoClient );
						
						// ���� �˸���.
						sDBRequest_Family_Del_Children clMsg( pclDelTargetchar->pclCI->GetPersonID() );// �ڽ� personID�� ������.
						SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

					}
				}
				else	// ��ȥ�� ������ ������ ����.
				{					
					SI32 siMatePersonID = pclDelTargetchar->pclMarriage->GetMatePersonID()	;
					SI32 siMateID = pclCM->GetIDFromPersonID( siMatePersonID )	;
					cltCharServer* pclMate = pclCM->GetCharServer( siMateID )	;
					if ( pclMate == NULL )	// ����� ������ 
					{
						// �������϶��� �׳� �����ٴ� �޼����� �����ָ� �ȴ�
						cltLetterMsg_LeaveFamilyLetter clletter( (TCHAR*)pclDelTargetchar->GetName());
						SendLetterMsg(  siMatePersonID , (cltLetterHeader*)&clletter );
					}
					else	// ����ڰ� ���� �Ǿ� �ִ�.
					{
						pclMate->pclMarriage->Init()	;

						// �������϶��� �׳� �����ٴ� �޼����� �����ָ� �ȴ�
						cltLetterMsg_LeaveFamilyLetter clletter( (TCHAR*)pclDelTargetchar->GetName());
						SendLetterMsg(  siMatePersonID , (cltLetterHeader*)&clletter );

						//��������� Ŭ���̾�Ʈ�� �ʱ�ȭ�ϰ� Ŭ���̾�Ʈ�� �˷��ش�.
						cltGameResponse_UpdateFamily clinfo( pclMate->pclFamily,pclMate->pclMarriage );
						cltMsg clMsgtoClient( GAMEMSG_RESPONSE_FAMILY_UPDATE, sizeof(clinfo), (BYTE*)&clinfo );
						pclMate->SendNetMsg( (sPacketHeader*)&clMsgtoClient );
					}
					pclDelTargetchar->pclMarriage->Init()	;	// �������踦 û�� �Ѵ�.

					SendServerResponseMsg( 0, SRVAL_FAMILY_ADD_WRONG_DEL_FAMILY, 0, 0, pclDelTargetchar->GetCharUnique() );
					//��������� Ŭ���̾�Ʈ�� �ʱ�ȭ�ϰ� Ŭ���̾�Ʈ�� �˷��ش�.
					cltGameResponse_UpdateFamily clinfo( pclDelTargetchar->pclFamily ,pclDelTargetchar->pclMarriage);
					cltMsg clMsgtoClient( GAMEMSG_RESPONSE_FAMILY_UPDATE, sizeof(clinfo), (BYTE*)&clinfo );
					pclDelTargetchar->SendNetMsg( (sPacketHeader*)&clMsgtoClient );

					// ���� �˸���.
					sDBRequest_Family_Del_Children clMsg( pclDelTargetchar->pclCI->GetPersonID() );// �ڽ� personID�� ������.
					SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);


				}
			}
			else	// ��ȥ���� �ʾҴٸ� �ڽ� �ɸ��� 
			{
				for ( SI32 siSlot = 0 ; siSlot < MAX_PARENT_NUM; siSlot++) 
				{
					SI32 siParent_PersonID = pclDelTargetchar->pclFamily->GetParent_PersonId(siSlot)	;
					if(siParent_PersonID > 0 )
					{
						cltLetterMsg_LeaveFamilyLetter clletter( (TCHAR*)pclDelTargetchar->GetName());
						SendLetterMsg(  siParent_PersonID , (cltLetterHeader*)&clletter );
					}
				}
				for ( SI32 siSlot = 0 ; siSlot < MAX_CHILDREN_NUM; siSlot++) 
				{
					SI32 PersonID = pclDelTargetchar->pclFamily->GetParent_PersonId(siSlot)	;
					if (PersonID > 0 ) 
					{
						cltLetterMsg_LeaveFamilyLetter clletter( (TCHAR*)pclDelTargetchar->GetName());
						SendLetterMsg(  PersonID , (cltLetterHeader*)&clletter );
					}
				}
				//���� �� ��������
				pclDelTargetchar->pclFamily->Init()	;

				//��������� Ŭ���̾�Ʈ�� �ʱ�ȭ�� �Ѵ�.
				cltGameResponse_UpdateFamily clinfo( pclDelTargetchar->pclFamily,pclDelTargetchar->pclMarriage );
				cltMsg clMsgtoClient( GAMEMSG_RESPONSE_FAMILY_UPDATE, sizeof(clinfo), (BYTE*)&clinfo );
				pclDelTargetchar->SendNetMsg( (sPacketHeader*)&clMsgtoClient );

				// �������� ©�ȵ��� �޼����� �����ش�.
				SendServerResponseMsg( 0, SRVAL_FAMILY_ADD_WRONG_DEL_FAMILY, 0, 0, pclDelTargetchar->GetCharUnique() );

				sDBRequest_Family_Del_Children clMsg( pclDelTargetchar->pclCI->GetPersonID() );// �ڽ� personID�� ������.
				SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);


			}

		}

	}
}

// Ÿ�� �������������� ���� 
void cltServer::DoMsg_GAMEMSG_REQUEST_FAMILY_WARP(cltMsg* pclMsg, SI32 id )
{
	cltGameRequest_WarpFamily* pclinfo = (cltGameRequest_WarpFamily*)pclMsg->cData;
	if ( NULL == pclinfo ){		return;	}
	if(IsCountrySwitch( Switch_We_Are_Family ) == false )	return	;

	cltCharServer* pclChar = pclCM->GetCharServer( id );
	if ( NULL == pclChar )	{		return;	}

	// ����� ĳ���Ͱ� �����ϰ� ������ ������ �׸��� �ȵ�
	SI32			siTargetFamilyCharID	= pclCM->GetIDFromPersonID( pclinfo->m_siPersonID );
	cltCharServer*	pclTargetFamilyChar		= pclCM->GetCharServer( siTargetFamilyCharID );
	if ( NULL == pclTargetFamilyChar )	{		return	;	}

	SI32 siMateMapIndex = pclTargetFamilyChar->GetMapIndex();
	SI32 siMateXPos		= pclTargetFamilyChar->GetX();
	SI32 siMateYPos		= pclTargetFamilyChar->GetY();

	// ��ȿ���� ���� ���̶��!!
	if ( (0 > siMateMapIndex) || (MAX_MAP_NUMBER <= siMateMapIndex) )	{		return;	}

	// �ش� �� ������ ���ٸ�!!!
	if ( NULL == pclMapManager->pclMapArray[siMateMapIndex] )	{		return;	}

	// ��ȿ���� ���� �����̶��!!
	if ( false == pclMapManager->IsValidArea(siMateMapIndex, siMateXPos, siMateYPos) )	{		return;	}

	// ������ �������� üũ
	bool bVillageWarp = false;
	if ( (0 < siMateMapIndex) && (CUR_VILLAGE_LIMIT >= siMateMapIndex) )
	{
		if ( true == pclMapManager->pclVillageManager->IsValidVillage(siMateMapIndex) )		{			bVillageWarp = true;		}
	}

	// ������������ �����Ҽ� ������?
	if ( false == pclChar->CanWarpFrom() )	{		return;	}

	// �ش� �������� �����Ҽ�������?
	if ( false == pclChar->CanWarpTo(siMateMapIndex) ){		return;	}

	// �� �ɸ��ͷ� ������ �����Ҽ�������?
	if ( false == pclChar->CanWarpToChar(siTargetFamilyCharID) ){		return;	}

	SI32 siWarpUnique	= 0;

	// ������ �̵��� ���
	if ( bVillageWarp )
	{
		SI32 siGetMapTypeUnique = pclMapManager->pclMapArray[siMateMapIndex]->siMapUnique;
		if (0 > siGetMapTypeUnique){			return;		}
		siWarpUnique = 2300;
	}
	else
	{
		siWarpUnique = 2200;
	}

	if ( id )
	{
		OrderStop( id, BY_COMPUTER );

		// ���� ����Ʈ ǥ��
		cltGameMsgResponse_WarpEffect clinfo( id );
		cltMsg clMsg(GAMEMSG_RESPONSE_WARPEFFECT, sizeof(clinfo), (BYTE*)&clinfo);
		pclChar->SendNeighbourMsg(&clMsg, true);

		// ������ �����ϱ�
		cltWarpInfo clWarpInfo( 1, siMateMapIndex, false, true, siMateXPos, siMateYPos, -1, -1 );
		pclChar->SetWarpInfo( &clWarpInfo, siWarpUnique );
		pclChar->Warp();
	}
}
void cltServer::DoMsg_GAMEMSG_REQUEST_FAMILY_CHAT(cltMsg* pclMsg, SI32 id )	// ���� ê�� 
{
	cltGameRequest_ChatFamily* pclinfo = (cltGameRequest_ChatFamily*)pclMsg->cData;
	if ( NULL == pclinfo ){		return;	}
	if(IsCountrySwitch( Switch_We_Are_Family ) == false )	return	;

	// ���� ��� �̸�

	stChatEditData ChatEditData;
	ChatEditData.siChatDataColorIndex	=	CHATEDIT_COLOR_VIOLET;
	ChatEditData.siChatEditDataSize		=	sizeof(pclinfo->m_szChatData);
	MStrCpy( ChatEditData.strNameData, pclinfo->m_szCharName, sizeof(TCHAR)*MAX_PLAYER_NAME );	/// ä�� �����͸� �����..
	MStrCpy( ChatEditData.strChatData, pclinfo->m_szChatData, sizeof(TCHAR)*MAX_CHAT_DATA_LENGTH );

	cltCharServer* pclCharServer = pclCM->GetCharServer(id)	;

	// �����鿡�� �޼����� ������.

	for ( SI32 siSlot = 0 ; siSlot< MAX_PARENT_NUM; siSlot++ )
	{
		SI32 siPersonID = pclCharServer->pclFamily->GetParent_PersonId(siSlot) ;
		SI32 siID = pclCM->GetIDFromPersonID( siPersonID)	;
		if ( pclCM->IsValidID( siID) == false ) continue	;
		cltCharServer* pclChar = pclCM->GetCharServer( siID )	;
		// Ŭ���̾�Ʈ�� �ش� �ɸ����� ���� ������Ʈ
		cltGameResponse_ChatFamily clInfo( &ChatEditData );
		cltMsg clStatusInfoMsg( GAMEMSG_RESPONSE_FAMILY_CHAT, sizeof(clInfo), (BYTE*)&clInfo );
		pclChar->SendNetMsg( (sPacketHeader*)&clStatusInfoMsg);
	}
	for ( SI32 siSlot = 0 ; siSlot< MAX_CHILDREN_NUM; siSlot++ )
	{
		SI32 siPersonID = pclCharServer->pclFamily->GetChildPersonID(siSlot) ;
		SI32 siID = pclCM->GetIDFromPersonID( siPersonID)	;
		if ( pclCM->IsValidID( siID) == false ) continue	;
		cltCharServer* pclChar = pclCM->GetCharServer( siID )	;
		// Ŭ���̾�Ʈ�� �ش� �ɸ����� ���� ������Ʈ
		cltGameResponse_ChatFamily clInfo( &ChatEditData );
		cltMsg clStatusInfoMsg( GAMEMSG_RESPONSE_FAMILY_CHAT, sizeof(clInfo), (BYTE*)&clInfo );
		pclChar->SendNetMsg( (sPacketHeader*)&clStatusInfoMsg);
	}
}

// ���� ȿ�� ���� 
void cltServer::DoMsg_GAMEMSG_REQUEST_FAMILY_PLUS_FAMILYEFFECT(cltMsg* pclMsg, SI32 id )
{
	cltGameRequest_Plus_FamilyEffectDate* pclinfo = (cltGameRequest_Plus_FamilyEffectDate*)pclMsg->cData;
	if ( NULL == pclinfo ){		return;	}
	if(IsCountrySwitch( Switch_We_Are_Family ) == false )	return	;

	cltCharServer* pParentChar = pclCM->GetCharServer(id)	;	// �Ⱓ�� �ø��� �θ�
	if( pParentChar == NULL ) return	;
	SI32 siTergetPersonId = pclinfo->m_siPersonID	;	// �Ⱓ�� �ø� �ڽ�

	// ���� Ƽ�ϰ˻� ���� 
	// üũ ���� 
	// 1. ���� ��� �̿���� �ִ°�?
	bool bUsedItem		=	false	;	// ����ߴ��� Ȯ��
	SI32 siUseItem		=	ITEMUNIQUE( 24122 )	;	// ���� �̿�� 
	SI32 siUseItemNum	=	1 ;						// 1��
	cltItem clitem;
	SI32 siref = pclClient->pclItemManager->FindItemRefFromUnique(siUseItem);			if(siref <= 0) return ;
	SI32 siHaveitemNum = pParentChar->pclCI->clCharItem.GetItemNum( siUseItem ) ;	// �������� � ������ �ִ��� Ȯ��.
	if ( siHaveitemNum >= siUseItemNum ) // ����� ���� �ִٸ� 
	{
		for(SI32 i = PERSONITEM_INV0;i < PERSONITEM_INV0 + MAX_INVITEM_PER_PERSON;i++)
		{
			if(pParentChar->pclCI->clCharItem.clItem[i].siUnique == siUseItem)
			{
				if ( siUseItemNum == 0 )	break	;	// ������ 0���� ������
				SI32 invItemNum = pParentChar->pclCI->clCharItem.clItem[i].GetItemNum()	;
				if ( invItemNum  >= siUseItemNum )
				{
					clitem.Set(&pclClient->pclItemManager->pclItemInfo[siref]->clItem);
					clitem.siItemNum = siUseItemNum;
					sDBRequest_UseItem clMsg(id, pParentChar->pclCI->GetPersonID(), i, &clitem, USEITEM_REASON_NONE);
					pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
					bUsedItem	=	true	;
					break	;
				}
				else
				{
					clitem.Set(&pclClient->pclItemManager->pclItemInfo[siref]->clItem);
					clitem.siItemNum = invItemNum	;// �縸ŭ �ְ�
					//��ü �������� ���ش�
					siUseItemNum =  siUseItemNum - invItemNum	;
					// ����ض�
					sDBRequest_UseItem clMsg(id, pParentChar->pclCI->GetPersonID(), i, &clitem, USEITEM_REASON_NONE);
					pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
					bUsedItem	=	true	;
				}
			}
		}
	}
	
	if ( bUsedItem == false ) 
	{
		// �������� ��� ����� ���ߴ� ���� �޼����� �����ش�.
		SendServerResponseMsg( 0, SRVAL_FAMILY_ADD_WRONG_No_TICKET_PLUSDATE, siUseItem, 0,  pParentChar->GetCharUnique() )	;
		return	;
	}
	
	SYSTEMTIME ChangTime	;
	SYSTEMTIME DatevaryNow = pParentChar->pclFamily->FInd_Add_Date( siTergetPersonId )	;
	TimeAddDate(&DatevaryNow,30,&ChangTime)	;// 30�� �÷��ش�.

	// Ƽ���� �˻��ؼ� ����ϰ�
	// ���� �޼����� �����ش�.
	//DB�� ���� �Ѵ�.
	sDBRequest_Family_Plus_Add_Date clMsg( siTergetPersonId ,ChangTime );
	SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
}