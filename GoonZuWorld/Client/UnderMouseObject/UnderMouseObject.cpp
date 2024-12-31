//---------------------------------
// 2003/9/19 ���°�
//---------------------------------

#include "..\..\Client\Client.h"

#include "UnderMouseObject.h"

//----------------------------
// CommonLogic
//----------------------------
#include "../../CommonLogic/MsgType-Structure.h"


//-----------------------------
// Common
//-----------------------------
#include "PersonInfo.h"
#include "..\..\Common\SystemNPC\SystemNPC.h"
#include "..\..\Common\SystemNPC\ForeignMerchantNPC\ForeignMerchantNPC.h"
#include "Char\CharManager\CharManager.h"
#include "Map\FieldObject\FieldObject.h"

#include "../../Common/Agriculture/Mining/MiningMgr.h"

//------------------------------
// Client
//------------------------------
#include "..\Client\ImageInterface/VillageNotice/VillageNotice.h"
#include "../Client/ninterface/nRightMouseUserListDlg/NRightMouseUserListDlg.h"
#include "../Client/DrawSequence/DrawSequence.h"

#include "Help\Help.h"



extern SHORT	GameRealX;
extern SHORT	GameRealY;

extern cltCommonLogic* pclClient;

//---------------------------------------------------------
// cltUnderMouseObject
//---------------------------------------------------------

void cltUnderMouseObject::Init()
{
	ID						= 0;
	siUnderMouseLockChar	= 0;
	siStructureUnique		= 0;
	siNPCUnique				= 0;
	siGateUnique			= 0;
	siVillageUnique			= 0;
	siDeskUnique			= 0;
	siTileAtb				= 0;

	MapX					= 0;
	MapY					= 0;

	NewIDSelectedClock		= 0;	// ���ο� ĳ���͸� ������ �ð�. 

	pclDrawSequence = new CDrawSequence();
};

cltUnderMouseObject::~cltUnderMouseObject()
{
	NDelete(pclDrawSequence);
}

// ���󿡼� ĳ���͸� ã�´�. 
BOOL cltUnderMouseObject::FindLandChar(cltMapClient* pclMap , OUT SI32 * newid, OUT SI32 * underUserCnt   )
{
	cltClient * pclclient = (cltClient*) pclClient;
	
	// ���󿡼� ĳ���͸� ã�´�. 
	SI32 range, i, j;
	SI16 length     = 0;
	SI32 min_length = 10000;
	SI32 id			= 0;
	SI32 index		= 0;
	SI32 playerCnt = 0; // ���콺 �Ʒ��� �ִ� �÷��̾��� ī��Ʈ [����] �������� �÷��̾��� ��� �޴��� �����ֵ��� ���� ��Ƹ�
	
	*newid		= 0;		// ã�� ĳ������ ID
	*underUserCnt = 0;		// �����ִ� ĳ������ ����

	// ���̾�α� ó��
	if( pclclient->m_pDialog[NRIGHTMOUSEUSERLIST_DLG] == NULL )
	{
		pclclient->CreateInterface(NRIGHTMOUSEUSERLIST_DLG);
		pclclient->m_pDialog[NRIGHTMOUSEUSERLIST_DLG]->Show(FALSE);
	}

	// ���� ��� ���̾�αװ� ���� �������� ����� ������Ʈ �صд�. �����¼����� �����ֱ⸸ �Ѵ�.
	if( pclclient->m_pDialog[NRIGHTMOUSEUSERLIST_DLG]->IsShow() == false )
	{
		((NRightMouseUserListDlg*)pclclient->m_pDialog[NRIGHTMOUSEUSERLIST_DLG])->Initialize();
	}

/*	index = 0;
	// ��ó�� �ִ� ĳ���͵��� ����Ʈ ����
	while(id = pclCM->GetCharOrder(index))
	{
		index++;

		if(pclCM->IsValidID(id))
		{
			length = max( TABS(pclCM->CR[id]->GetX() - MapX), TABS(pclCM->CR[id]->GetY() - MapY));
			
			if(length > 3)continue;				// �ʹ� �� �Ÿ��� �ִ� ĳ���ʹ� �������� �ʴ´�.
			if(id == 1 && pclCM->CR[1]->siSelectedCharIndex == -1)continue;	// ������̾�� �ȵȴ�. 
			if(pclCM->IsAlive(id) == false)continue;	// ��� �־�� �Ѵ�. 
			if(pclCM->CR[id]->pclKI->IsAtb(ATB_HORSE) == true)continue;	// ���� �˻����� �ʴ´�. 

			cltDrawObjData cldata(DRAWOBJ_TYPE_CHAR, id);
			pclDrawSequence->Push(pclCM->CR[id]->GetX(), pclCM->CR[id]->GetY(), 1, 1, &cldata);
		}
	}

	min_length = 10000;
	cltDrawObjData *pcldata = pclDrawSequence->Pop();	
	while( pcldata )
	{
		if(pcldata->siType == DRAWOBJ_TYPE_CHAR)
		{
			SI32 siCharID = pcldata->siID;
			SI16 siLen = 0;

			// ĳ���� �ڽ� �ȿ� ������ ���
			if(pclCM->CR[siCharID]->IsAbsPtInObj(GameRealX, GameRealY, siLen) == TRUE)
			{
				// �׸� �׸��� ������ ���ĵǾ����Ƿ�
				// ���߿� ã�� ĳ���ͷ� ������ �����Ѵ�.
				*newid  = siCharID;

				if( pclclient->m_pDialog[NRIGHTMOUSEUSERLIST_DLG]->IsShow() == false )
				{
					if( IsPC(pclCM->CR[siCharID]->GetCharUnique()) )
					{
						*underUserCnt += 1; // ���콺 �ؿ� �ִ� �÷��̾��� ī��Ʈ ����
						((NRightMouseUserListDlg*)pclclient->m_pDialog[NRIGHTMOUSEUSERLIST_DLG])->AddUser(id, pclCM->CR[siCharID]->GetKind() , pclCM->CR[siCharID]->pclCI->clIP.GetLevel(), (TCHAR*)pclCM->CR[siCharID]->GetName() ); 
					}
				}
			}
		}

		pcldata = pclDrawSequence->Pop();
	}
*/

	while(id = pclCM->GetCharOrder(index))
	{
		index++;

		if(pclCM->IsValidID(id))
		{
			length = max( TABS(pclCM->CR[id]->GetX() - MapX), TABS(pclCM->CR[id]->GetY() - MapY));

			// �ʹ� �� �Ÿ��� �ִ� ĳ���ʹ� �������� �ʴ´�.
			if(length > 3)continue;
			if(id == 1 && pclCM->CR[1]->siSelectedCharIndex == -1)continue;	// ������̾�� �ȵȴ�. 
			if(pclCM->IsAlive(id) == false)continue;	// ��� �־�� �Ѵ�. 
			if(pclCM->CR[id]->pclKI->IsAtb(ATB_HORSE) == true)continue;	// ���� �˻����� �ʴ´�. 
			

			if(pclCM->CR[id]->IsAbsPtInObj(GameRealX, GameRealY, length)==TRUE)
			{
				
				if(length <= min_length)	
				{
					min_length = length;
					
					if(*newid  == 0)	//id �� ���õǾ� ���� �ʴٸ�
					{
						*newid  = id;
					}
					
					if( pclclient->m_pDialog[NRIGHTMOUSEUSERLIST_DLG]->IsShow() == false )
					{
						if( IsPC(*newid) && pclCM->CR[id]->pclKI->IsAtb(ATB_SYSTEMNPC) == false && pclCM->CR[id]->pclKI->IsAtb(ATB_MONSTER) == false ) // NPC�� �ƴ� �÷��̾���
						{
							*underUserCnt += 1; // ���콺 �ؿ� �ִ� �÷��̾��� ī��Ʈ ����
							((NRightMouseUserListDlg*)pclclient->m_pDialog[NRIGHTMOUSEUSERLIST_DLG])->AddUser(id, pclCM->CR[id]->GetKind() , pclCM->CR[id]->pclCI->clIP.GetLevel(), (TCHAR*)pclCM->CR[id]->GetName() ); 
						}
					}
				}
			}

		}

	}

	for(range = 0 ; range <= 2 ; range++)
	{
		for(i=MapY - range;i <= MapY + range; i++)
			for(j=MapX - range;j <= MapX + range; j++)
			{
				if(i==(MapY-range) || i== (MapY+range) || j==(MapX-range) || j==(MapX+range)){}
				else continue;
				
				// ������ �������� �����ϴ��� �˻��Ѵ�. 
				if(pclMap->IsInMapArea(j, i) == false) continue;

				// ��ȿ�� ĳ������ ���̵� ã�ƾ� �Ѵ�. 
				id = pclMap->GetIDMap(j, i);
				if(id == 1 && pclCM->CR[1]->siSelectedCharIndex == -1)continue;	// ������̾�� �ȵȴ�. 
				if(pclCM->IsAlive(id) == false)continue;	// ��� �־�� �Ѵ�. 
				if(pclCM->CR[id]->pclKI->IsAtb(ATB_HORSE) == true)continue;	// ���� �˻����� �ʴ´�. 
				
				if(pclCM->CR[id]->IsAbsPtInObj(GameRealX, GameRealY, length)==TRUE)
				{

					if(length < min_length)
					{
						min_length = length;
						*newid      = id;

						TCHAR buffer[256];
						StringCchPrintf(buffer, 256, TEXT("id:%d charunique:%d------------"), *newid, pclCM->CR[id]->GetCharUnique()); 
						pclClient->pclMessage->SetMsg(buffer);

					}
				}
			}
			
	}

	return TRUE;
}


// FieldObject�� ã�´�. ã���� �� FOUnique�� �����Ѵ�. 
SI32 cltUnderMouseObject::FindFieldObject(cltMapClient* pclMap)
{

	// FOUnique�� ��ȿ�ϸ� ����. 
	SI32 founique = pclMap->GetFieldObject_Unique(MapX, MapY);
	if( founique <= 0)return 0;

	return founique;
}


// �������� ã�´�. ã���� true ����. 
bool cltUnderMouseObject::FindItem(cltMapClient* pclMap, SI32* pitemunique, SI32* pitemindex)
{

	cltItemMapInfo* pclinfo = pclMap->GetItemMap(MapX, MapY);
	if(pclinfo == NULL)return false;

	*pitemunique	= pclinfo->uiItemUnique;
	*pitemindex		= pclinfo->uiItemIndex;

	return true;
}

// ���๰�� ã�´�. 
SI32 cltUnderMouseObject::FindStructure(cltMapClient* pclMap)
{
	if(pclMap == NULL)				return 0;

	// ������ �ƴϸ� �����Ѵ�. 
	if(pclMap->siVillageUnique <= 0)return 0;

	// �ǹ��� �������� Ȯ���Ѵ�. (���� ��ġ�� ���� Ȯ���Ѵ�.)
	SI32 slot = pclMap->GetStructureSlot(pclMap->siVillageUnique, MapX, MapY);
	if(slot < 0)return 0;
	
	// �ش� ������ ���� ��ǥ�� ���Ѵ�. 
	SI32 slotstartx, slotstarty;
	if(pclMap->GetSlotStartPos(pclMap->siVillageUnique, slot, &slotstartx, &slotstarty) == false)return 0;

	// ���Կ� �ǹ��� �ִ� ���� �ƴ϶�� �����Ѵ�. 
	SI32 structureunique = pclGame->pclVillageManager->pclVillageInfo[pclMap->siVillageUnique]->clVillageVary.clStructureInfo.Get(slot);
	if(structureunique <= 0) return 0;

	// ������Ʈ�� �ִ� ���� ��ȿ�ϴ�. 
	if(pclMap->GetFieldObject_Unique(MapX, MapY) == 0)return 0;

	// ������Ʈ�� �߽� ��ġ�� ���Ѵ�.
	SI32 centerx, centery;
	if(pclMap->GetFieldObjectCenterPos(MapX, MapY, &centerx, &centery) == false)return 0;

	// �߽� ������Ʈ�� keyobject�� ��쿡�� ��ȿ�ϴ�.
	if(pclGame->pclVillageStructureSet->IsKeyStructure(centerx-slotstartx , centery-slotstarty, structureunique) == false) return 0;
	
	return structureunique;
}

// Gate�� ã�´�. 
SI32 cltUnderMouseObject::FindGate(cltMapClient* pclMap)
{
	// ������Ʈ�� �ִ� ���� ��ȿ�ϴ�. 
	SI32 founique = pclMap->GetFieldObject_Unique(MapX, MapY);
	if(founique <= 0)return 0;

	SI32 ref = pclMap->pclFieldObjectManager->FindRefFromUniqueMinus(founique);
	if(ref < 0)return 0;

	SI32 type = pclMap->pclFieldObjectManager->pclInfo[ref]->dwType;
	
	if(type != FOTYPE_GATE)return 0;

	SI32 gateunique = pclMap->GetFieldObjectPara(MapX, MapY);
	if(gateunique <= 0)return  0;

	return gateunique ;
}

// ������  ã�´�. 
SI32 cltUnderMouseObject::FindVillage(cltMapClient* pclMap)
{
	// ������Ʈ�� �ִ� ���� ��ȿ�ϴ�. 
	SI32 founique = pclMap->GetFieldObject_Unique(MapX, MapY);
	if(founique <= 0)return 0;

	SI32 ref = pclMap->pclFieldObjectManager->FindRefFromUniqueMinus(founique);
	if(ref < 0)return 0;

	SI32 type = pclMap->pclFieldObjectManager->pclInfo[ref]->dwType;
	
	if(type != FOTYPE_VILLAGE)return 0;

	SI32 villageunique = pclMap->GetFieldObjectPara(MapX, MapY);
	if(villageunique <= 0)return  0;

	return villageunique ;
}

// ���콺 �Ʒ� ��ü�� �ľ��Ѵ�. 
void cltUnderMouseObject::GetUnderMouseObject(cltMapClient* pclMap, SI32 screenmousex, SI32 screenmousey)
{
	static DWORD dwLastCheckLockClock = 0;

	// ���콺�� �������� �ִ� ���� �ƴ϶�� , 
	if(pclMap->IsInMapArea(MapX, MapY) == false) return ;
	
	//-------------------------------------
	// ���콺 �ؿ� �ִ� ĳ���͸� ���Ѵ�. 
	//-------------------------------------
	SI32 newid = 0;
	SI32 underUserCnt = 0;

	// ���󿡼� ã�´�. 
	FindLandChar(pclMap,&newid, &underUserCnt);

    

	if(newid == 0 && siUnderMouseLockChar)
	{
		newid = siUnderMouseLockChar;
	}
	
	// ���ο� ���̵� ������ �ð��� ���Ѵ�. 
	if((newid == 0) || newid != GetUnderMouseID())
	{
		NewIDSelectedClock = pclGame->CurrentClock;
	}

	// ���� �������� �ʴ´�. 
	if(newid && pclClient->pclCM->CR[newid]->pclKI->IsAtb(ATB_HORSE))
	{
		newid = 0;
	}

	//cyh ��ڰ� HIDE����϶��� �������� �ʴ´�
	if (newid > 0)
	{
		if(pclClient->pclCM->CR[newid]->pclCI->clBI.uiGMMode == GMMODE_ATB_HIDE)
		{
			newid = 0;
			
		}
	}
	//�����ð� �̻� ĳ���͸� �����ϰ� �ִ� ���̸�, 
	if(TABS(NewIDSelectedClock - pclGame->CurrentClock) > 500)
	{
		// �ٽ� ��û���� �ʵ��� �Ѵ�. 
		NewIDSelectedClock = pclGame->CurrentClock;

		//ĳ������ �̸��� ��ȿ���� Ȯ���Ѵ�. 
		cltCharClient* pclChar = (cltCharClient*)pclGame->pclCM->CR[newid];

		if( newid > 0 && IsPC(pclChar->GetCharUnique()))
		{
			// �̸��� ��ȿ�ϸ�, 
			if(_tcscmp(pclChar->GetName(), TEXT("")) == 0)
			{
				// ��ȿ���� �ʴٸ� ������ �̸��� ��û�Ѵ�. 
				cltGameMsgRequest_GetName clInfo( pclChar->GetCharUnique() );
				cltMsg clNormalMsg(GAMEMSG_REQUEST_NAME, sizeof(clInfo), (BYTE*)&clInfo);

				pclGame->SendMsgToServer((sPacketHeader*)&clNormalMsg);
			}
		}
	}

	// ���콺 ���� ĳ���͸� �����Ѵ�. 
	SetUnderMouseID(newid);
	// ���콺 ���� ĳ���� ���� �����Ѵ�.
	SetUnderUserCnt( underUserCnt );

	// ���콺 ���� ĳ���͸� Lock�Ѵ�. 
	if(newid && siUnderMouseLockChar != newid)
	{
		siUnderMouseLockChar	= newid;
		dwLastCheckLockClock	= pclClient->CurrentClock;
	}
	else if(siUnderMouseLockChar)
	{
		if(TABS(pclClient->CurrentClock - dwLastCheckLockClock) > 2000)
		{
			siUnderMouseLockChar = 0;
		}
	}
	
	
	//-----------------------------------
	// ���콺 �ؿ� �ִ� �ǹ��� ã�´�. 
	//-----------------------------------
	SI32 structureunique = 0;
	structureunique = FindStructure(pclMap);

	siStructureUnique = structureunique;
	
	// ������ �����Ѵ�.
	if(siStructureUnique)
	{
		TCHAR buffer[256];
		SI32 ref = pclGame->pclVillageStructureSet->FindRefFromUnique(siStructureUnique);

		if(ref >= 0)
		{
			StringCchPrintf(buffer, 256, pclGame->pclVillageStructureSet->pclVillageStructureInfo[ref]->szName);
			
			// �ʺ����̸�, 
			if(pclCM->CR[1]->pclCI->clIP.GetLevel() < 10)
			{
				TCHAR* pText = GetTxtFromMgr(1119);
				
				StringCchCat(buffer, 256, pText);
			}

			
			SI32 index = pclGame->pclHelpManager->GetHelp(buffer);
			if( index >= 0 )
			{
				pclGame->pclHelpManager->SetPos(index, screenmousex, screenmousey);
			}
			else
			{
				pclGame->pclHelpManager->Add(buffer, screenmousex, screenmousey);
			}
		}
	}

	//-----------------------------------
	// ���콺 �ؿ� �ִ� ������ ã�´�. 
	//-----------------------------------
	SI32 villageunique = 0;
	villageunique	= FindVillage(pclMap);
	siVillageUnique	= villageunique;
	
	cltClient *pclclient = (cltClient *)pclClient;

	// ���� �ȳ����� �׸� �� �ְ� �Ѵ�.
	if ( siVillageUnique > 0 )
	{
		if ( pclclient->pclVillageNotice->Set( siVillageUnique, screenmousex, screenmousey) )
		{
			cltGameMsgRequest_VillageNotice clInfo( siVillageUnique );		
			cltMsg clMsg(GAMEMSG_REQUEST_VILLAGENOTICE, sizeof(clInfo), (BYTE*)&clInfo);
			pclClient->SendMsgToServer((sPacketHeader*)&clMsg);	
		}
	}
	// ���� �ȳ����� �׸� �� ���� �Ѵ�.
	else
	{
		pclclient->pclVillageNotice->Set( 0, screenmousex, screenmousey);
	}


	//-----------------------------------
	// ���콺 �ؿ� �ִ� Gate�� ã�´�. 
	//-----------------------------------
	SI32 gateunique = 0;
	gateunique = FindGate(pclMap);

	siGateUnique = gateunique;
	
	// ������ �����Ѵ�.
	if(siGateUnique)
	{
		TCHAR buffer[256] = { '\0', };

		if( siGateUnique < INSTANCEMAPGATE_START )
		{
			StringCchPrintf(buffer, 256, TEXT("%s"), pclGame->pclMapManager->pclGateManager->clGate[siGateUnique].szName);
		
			SI32 index = pclGame->pclHelpManager->GetHelp(buffer);
			if( index >= 0 )
			{
				pclGame->pclHelpManager->SetPos(index, screenmousex, screenmousey);
			}
			else
			{
				pclGame->pclHelpManager->Add(buffer, screenmousex, screenmousey);
			}
		}
	}


	//-----------------------------
	// ���콺 �ؿ� �ִ� �������� ã�´�.
	//-----------------------------
	SI32 itemunique;
	SI32 itemindex;
	if(FindItem(pclMap, &itemunique, &itemindex) == true)
	{
		siItemUnique	= itemunique;
		siItemIndex		= itemindex;
		siItemX			= MapX;
		siItemY			= MapY;

		cltItemManagerClient* pclitemmanager = (cltItemManagerClient*)pclGame->pclItemManager;
		SI32 ref = pclitemmanager->FindItemRefFromUnique(siItemUnique);
		if(ref > 0)
		{
			TCHAR buffer[256];
			StringCchPrintf(buffer, 256, pclitemmanager->pclItemInfo[ref]->GetName());
			
			SI32 index = pclGame->pclHelpManager->GetHelp(buffer);
			if( index >= 0 )
			{
				pclGame->pclHelpManager->SetPos(index, screenmousex, screenmousey);
			}
			else
			{
				pclGame->pclHelpManager->Add(buffer, screenmousex, screenmousey);
			}
		}

	}
	else
	{
		siItemUnique	= 0;
		siItemIndex		= 0;
	}

	
	//-------------------------------
	// ���콺 �ؿ� �ִ� å���� ã�´�. 
	//-------------------------------
	SI32 deskunique	= FindFieldObject(pclMap);
	siDeskUnique = 0;
	if(deskunique == FOUNIQUE(30))			// �����Ǽ�
	{
		siDeskUnique	= deskunique;
		TCHAR buffer[256];
		TCHAR* pText = GetTxtFromMgr(1120);
		

		StringCchCopy(buffer, 256, pText);

		SI32 index = pclGame->pclHelpManager->GetHelp(buffer);
		if( index >= 0 )
		{
			pclGame->pclHelpManager->SetPos(index, screenmousex, screenmousey);
		}
		else
		{
			pclGame->pclHelpManager->Add(buffer, screenmousex, screenmousey);
		}
	}
	else if(deskunique == FOUNIQUE(31))		// �����Ǽ�
	{
		siDeskUnique	= deskunique;
		TCHAR buffer[256];
		TCHAR* pText = GetTxtFromMgr(1121);
		

		StringCchCopy(buffer, 256, pText);

		SI32 index = pclGame->pclHelpManager->GetHelp(buffer);
		if( index >= 0 )
		{
			pclGame->pclHelpManager->SetPos(index, screenmousex, screenmousey);
		}
		else
		{
			pclGame->pclHelpManager->Add(buffer, screenmousex, screenmousey);
		}
	}
	else if(deskunique == FOUNIQUE(32))		// �����Ǽ�
	{
		siDeskUnique	= deskunique;
		TCHAR buffer[256];
		TCHAR* pText = GetTxtFromMgr(1122);
		

		StringCchCopy(buffer, 256, pText);

		SI32 index = pclGame->pclHelpManager->GetHelp(buffer);
		if( index >= 0 )
		{
			pclGame->pclHelpManager->SetPos(index, screenmousex, screenmousey);
		}
		else
		{
			pclGame->pclHelpManager->Add(buffer, screenmousex, screenmousey);
		}
	}
	else if(deskunique == FOUNIQUE(34))		// ȣ���Ǽ�
	{
		siDeskUnique	= deskunique;
		TCHAR buffer[256];
		TCHAR* pText = GetTxtFromMgr(1123);
		

		StringCchCopy(buffer, 256, pText);

		SI32 index = pclGame->pclHelpManager->GetHelp(buffer);
		if( index >= 0 )
		{
			pclGame->pclHelpManager->SetPos(index, screenmousex, screenmousey);
		}
		else
		{
			pclGame->pclHelpManager->Add(buffer, screenmousex, screenmousey);
		}
	}
	else if(deskunique == FOUNIQUE(35))		// �����Ǽ�
	{
		siDeskUnique	= deskunique;
		TCHAR buffer[256];
		TCHAR* pText = GetTxtFromMgr(1124);
		

		StringCchCopy(buffer, 256, pText);

		SI32 index = pclGame->pclHelpManager->GetHelp(buffer);
		if( index >= 0 )
		{
			pclGame->pclHelpManager->SetPos(index, screenmousex, screenmousey);
		}
		else
		{
			pclGame->pclHelpManager->Add(buffer, screenmousex, screenmousey);
		}
	}
	else if(deskunique == FOUNIQUE(39) )		// ��������
	{
		siDeskUnique	= deskunique;
		TCHAR buffer[256];
		TCHAR* pText = GetTxtFromMgr(599); // ����


		StringCchCopy(buffer, 256, pText);
		SI32 index = pclGame->pclHelpManager->GetHelp(buffer);
		if( index >= 0 )
		{
			pclGame->pclHelpManager->SetPos(index, screenmousex, screenmousey);
		}
		else
		{
			pclGame->pclHelpManager->Add(buffer, screenmousex, screenmousey);
		}
	}
	else if(deskunique == FOUNIQUE(303) )		// ���ŰԽ���
	{
		
 		siDeskUnique	= deskunique;
		TCHAR buffer[256];
		TCHAR* pText = GetTxtFromMgr(6998); // ���ŰԽ���


		StringCchCopy(buffer, 256, pText);

		SI32 index = pclGame->pclHelpManager->GetHelp(buffer);
		if( index >= 0 )
		{
			pclGame->pclHelpManager->SetPos(index, screenmousex, screenmousey);
		}
		else
		{
			pclGame->pclHelpManager->Add(buffer, screenmousex, screenmousey);
		}	

	}
	else if(deskunique == FOUNIQUE(301) )		// ���뱺�ָ��
	{

		siDeskUnique	= deskunique;
		TCHAR buffer[256];
		TCHAR* pText = GetTxtFromMgr(7021); // ���뱺�ָ��


		StringCchCopy(buffer, 256, pText);

		SI32 index = pclGame->pclHelpManager->GetHelp(buffer);
		if( index >= 0 )
		{
			pclGame->pclHelpManager->SetPos(index, screenmousex, screenmousey);
		}
		else
		{
			pclGame->pclHelpManager->Add(buffer, screenmousex, screenmousey);
		}	

	}
	//[�߰� : Ȳ���� 2008. 1. 10 => �δ� ���� ��Ȳ���� �����ִ� �Խ��� ����.]
	else if ( deskunique == FOUNIQUE(305) ) 
	{
		siDeskUnique = deskunique;
		TCHAR buffer[256];
		TCHAR* pText = GetTxtFromMgr(7830); // ���⿡ �Խ��� ���� ������...

		StringCchCopy(buffer, 256, pText);

		SI32 index = pclGame->pclHelpManager->GetHelp(buffer);
		if( index >= 0 )
		{
			pclGame->pclHelpManager->SetPos(index, screenmousex, screenmousey);
		}
		else
		{
			pclGame->pclHelpManager->Add(buffer, screenmousex, screenmousey);
		}	
	}

	else if ( deskunique == FOUNIQUE(307) ) //��ŷ.���� ���� ������
	{
		siDeskUnique = deskunique;
		TCHAR buffer[256];
		TCHAR* pText = GetTxtFromMgr(7854); // ���⿡ �Խ��� ���� ������...

		StringCchCopy(buffer, 256, pText);

		SI32 index = pclGame->pclHelpManager->GetHelp(buffer);
		if( index >= 0 )
		{
			pclGame->pclHelpManager->SetPos(index, screenmousex, screenmousey);
		}
		else
		{
			pclGame->pclHelpManager->Add(buffer, screenmousex, screenmousey);
		}	
	}
	else if ( deskunique == FOUNIQUE(9468) ) // ������
	{
		siDeskUnique = deskunique;
		TCHAR buffer[256];
		TCHAR* pText = GetTxtFromMgr(30098);

		StringCchCopy(buffer, 256, pText);

		SI32 index = pclGame->pclHelpManager->GetHelp(buffer);
		if( index >= 0 )
		{
			pclGame->pclHelpManager->SetPos(index, screenmousex, screenmousey);
		}
		else
		{
			pclGame->pclHelpManager->Add(buffer, screenmousex, screenmousey);
		}	
	}

	/*cyj �����Ǽ� ����
	else if(deskunique == 5640)
	{
		siDeskUnique	= deskunique;
		TCHAR buffer[256];
		TCHAR* pText = GetTxtFromMgr(1125);
		

		StringCchCopy(buffer, 256, pText);

		SI32 index = pclGame->pclHelpManager->GetHelp(buffer);
		if( index >= 0 )
		{
			pclGame->pclHelpManager->SetPos(index, screenmousex, screenmousey);
		}
		else
		{
			pclGame->pclHelpManager->Add(buffer, screenmousex, screenmousey);
		}
	}
	*/
		
	//-----------------------------------
	// ���콺 ���� Ÿ�� ����ũ�� ã�´�. 
	//-----------------------------------
	siTileAtb = pclMap->GetMouseTileAtb(MapX, MapY);


	return ;
}
