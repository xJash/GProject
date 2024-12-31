//---------------------------------
// 2003/6/9 ���°�
//---------------------------------
#include "CityHall.h"

#include "Char\CharCommon\Char-Common.h"
#include "Char\CharManager\CharManager.h"


#include "..\..\CommonLogic\CommonLogic.h"
#include "..\..\Server\Candidate\Candidate.h"
#include "TaxPaymentListDlg.h"

#include "..\..\Resource.h"
#include "MsgType-Structure.h"


#include "..\..\CommonLogic\Bank\Bank-Manager.h"
#include "..\..\CommonLogic\Hunt\Hunt.h"
#include "..\..\CommonLogic\PostOffice\PostOffice.h"

#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Structure.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-CityHall.h"

#include "..\..\Server\Time\MyTime.h"
#include "..\..\Server\Server.h"

#include "../common/Event/event.h"

extern cltCommonLogic* pclClient;


void cltChatMemberManager::AddChatMember( int charid, int personid )
{

	DelChatMember( personid );

	for( int i = 0; i < 200; ++i )
	{
		if( clChatMember[ i ].charid == 0 ) 
		{
			clChatMember[ i ].charid = charid;
			clChatMember[ i ].personid = personid;
			break;
		}
	}
}

void cltChatMemberManager::DelChatMember( int personid )
{
	for( int i = 0; i < 200; ++i )
	{
		if( clChatMember[ i ].personid == personid ) 
		{
			clChatMember[ i ].charid = 0;
			clChatMember[ i ].personid = 0;
			break;
		}
	}		
}

void cltChatMemberManager::SendMsg( BYTE* msg )
{
	cltServer *pclServer = (cltServer *)pclClient;
	for( int i = 0; i < 200; ++i )
	{
		int id = clChatMember[ i ].charid;
		if( id == 0 ) continue;

		if( pclServer->pclCM->IsValidID(id) == FALSE ||
			pclServer->pclCM->CR[ id ]->pclCI->GetPersonID() 
			!= clChatMember[ i ].personid )
		{

			clChatMember[ i ].charid = 0;
			clChatMember[ i ].personid = 0;

			continue;
		}


		pclClient->pclCM->CR[id]->SendNetMsg( (sPacketHeader*)msg );
	}
}



//----------------------------------------------
// cltCityHall
//----------------------------------------------
cltCityHall::cltCityHall(SI32 sivillageunique) : cltStructureBasic(sivillageunique)
{
	pclCandidateManager = new cltCityHallCandidateManager();
	
	int i;

	for( i = 0; i < MAX_RESIDENT_APPLYER; i++ ) {
		clResidentApplyer[ i ].Init();
	}

	bPrepareBankruptcy = FALSE;
}

cltCityHall::~cltCityHall()
{

	if( pclCandidateManager )
	{
		delete pclCandidateManager;
		pclCandidateManager = NULL;
	}
}

// Chief �ĺ��� ����Ѵ�. 
BOOL cltCityHall::SetCandidate(SI32 index, cltSimpleRank* pclrank, cltSimplePerson* pclcandidate)
{
	return pclCandidateManager->SetCandidate(index, pclrank->GetRankType(), pclcandidate);
}

// �ĺ� ����� ����Ѵ�. 
BOOL cltCityHall::DeleteCandidate(SI32 personid)
{
	return pclCandidateManager->DeletePerson(personid);
}

// Ư�� �ź��� �ĺ� ����� ��� ����Ѵ�. 
BOOL cltCityHall::DeleteCandidate(cltSimpleRank* pclrank)
{
	return pclCandidateManager->DeleteRank(pclrank->siType);
}

cltSimplePerson* cltCityHall::GetCandidateInfoFromPersonID(SI32 ranktype, SI32 personid, SI32* pindex)
{
	if(pclCandidateManager == NULL)return NULL;

	return pclCandidateManager->GetCandidateInfoFromPersonID(ranktype, personid, pindex);
}

// ���ĺ����� ���ڸ� ���Ѵ�. 
SI32 cltCityHall::GetCandidateNum(SI32 ranktype)
{
	return pclCandidateManager->GetCandidateNum(ranktype);
}


cltSimplePerson* cltCityHall::GetCandidateInfoFromRef(SI32 ranktype, SI32 ref)
{
	return pclCandidateManager->GetCandidateInfoFromRef(ranktype, ref);
}


// �ֹ� ��� ��û�ڸ� �߰��Ѵ� 
BOOL cltCityHall::AddApplyer( cltResidentApplyer *pclApplyer )
{
	SI32 i;

	for( i = 0; i < MAX_RESIDENT_APPLYER; i++ )
	{
		if( clResidentApplyer[ i ].clApplyer.GetPersonID() == 0 )
		{
			clResidentApplyer[ i ].Set( pclApplyer );
			return TRUE;
		}
	}

	return FALSE;
}

// �ֹ� ��� ��û�ڸ� �����Ѵ�
BOOL cltCityHall::DeleteApplyer( SI32 personid )
{
	SI32 i;

	for( i = 0; i < MAX_RESIDENT_APPLYER; i++ )
	{
		if( clResidentApplyer[ i ].clApplyer.GetPersonID() == personid )
		{
			clResidentApplyer[ i ].Init();
			return TRUE;
		}
	}

	return FALSE;
}




void cltCityHall::SetSymbol( SI16 symbolKind, SI32 symbolLife, SI32 symbolMana, SI16 symbolCapa )
{
	clStrInfo.clCityhallStrInfo.siSymbolKind = symbolKind;
	clStrInfo.clCityhallStrInfo.siSymbolLife = symbolLife;
	clStrInfo.clCityhallStrInfo.siSymbolMana = symbolMana;
	clStrInfo.clCityhallStrInfo.siSymbolCapa = symbolCapa;

	sDBRequest_SetVillageSymbol sendMsg( siVillageUnique, symbolKind, symbolLife, symbolMana, symbolCapa );

	((cltServer *)pclClient)->pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );

	//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	//{
	// [�α��߰� : Ȳ���� 2007. 10. 9] // ���� ��ȣ��.
	//// param1 == �ɺ�(��ȣ��) ����, param2 == �ɺ�(��ȣ��) ü��, param3 == �ɺ�(��ȣ��) Mana, param4 == �ɺ�(��ȣ��) ����.
	//cltServer * pclServer = (cltServer*)pclClient;
	//pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_VILLAGE, LOGCOMMAND_INDEX_VILLAGE_SYMBOL_SET, 
	//								0, NULL, NULL, 0, 0, 0, NULL, 0, 0, 0, siVillageUnique, 0, 0, 
	//								symbolKind, symbolLife, symbolMana, symbolCapa, 0, NULL, NULL);
	//}
}

void cltCityHall::SetSymbolLife( SI32 symbolLife )
{
	clStrInfo.clCityhallStrInfo.siSymbolLife = symbolLife;

	sDBRequest_SetVillageSymbol sendMsg( siVillageUnique, 
		clStrInfo.clCityhallStrInfo.siSymbolKind, 
		symbolLife,
		clStrInfo.clCityhallStrInfo.siSymbolMana,
		clStrInfo.clCityhallStrInfo.siSymbolCapa );

	((cltServer *)pclClient)->pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );

	//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	//{
	// [�α��߰� : Ȳ���� 2007. 10. 9] // ���� ��ȣ��.
	//// param1 == �ɺ�(��ȣ��) ����, param2 == �ɺ�(��ȣ��) ü��, param3 == �ɺ�(��ȣ��) Mana, param4 == �ɺ�(��ȣ��) ����.
	//cltServer * pclServer = (cltServer*)pclClient;
	//pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_VILLAGE, LOGCOMMAND_INDEX_VILLAGE_SYMBOL_SET, 
	//								0, NULL, NULL, 0, 0, 0, NULL, 0, 0, 0, siVillageUnique, 0, 0, 
	//								clStrInfo.clCityhallStrInfo.siSymbolKind, symbolLife,
	//								clStrInfo.clCityhallStrInfo.siSymbolMana, clStrInfo.clCityhallStrInfo.siSymbolCapa, 0, NULL, NULL);
	//}
}

void cltCityHall::SetSymbolMana( SI32 symbolMana )
{
	clStrInfo.clCityhallStrInfo.siSymbolMana = symbolMana;

	sDBRequest_SetVillageSymbol sendMsg( siVillageUnique, 
		clStrInfo.clCityhallStrInfo.siSymbolKind, 
		clStrInfo.clCityhallStrInfo.siSymbolLife, 
		symbolMana,
		clStrInfo.clCityhallStrInfo.siSymbolCapa );

	((cltServer *)pclClient)->pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );

	//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	//{
	// [�α��߰� : Ȳ���� 2007. 10. 9] // ���� ��ȣ��.
	//// param1 == �ɺ�(��ȣ��) ����, param2 == �ɺ�(��ȣ��) ü��, param3 == �ɺ�(��ȣ��) Mana, param4 == �ɺ�(��ȣ��) ����.
	//cltServer * pclServer = (cltServer*)pclClient;
	//pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_VILLAGE, LOGCOMMAND_INDEX_VILLAGE_SYMBOL_SET, 
	//								0, NULL, NULL, 0, 0, 0, NULL, 0, 0, 0, siVillageUnique, 0, 0, 
	//								clStrInfo.clCityhallStrInfo.siSymbolKind, 
	//								clStrInfo.clCityhallStrInfo.siSymbolLife, 
	//								symbolMana,
	//								clStrInfo.clCityhallStrInfo.siSymbolCapa, 0, NULL, NULL);
	//}
}

void cltCityHall::SetSymbolCapa( SI16 symbolCapa )
{
	clStrInfo.clCityhallStrInfo.siSymbolCapa = symbolCapa;

	sDBRequest_SetVillageSymbol sendMsg( siVillageUnique, 
		clStrInfo.clCityhallStrInfo.siSymbolKind, 
		clStrInfo.clCityhallStrInfo.siSymbolLife, 
		clStrInfo.clCityhallStrInfo.siSymbolMana,
		symbolCapa );

	((cltServer *)pclClient)->pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );

	//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	//{
	// [�α��߰� : Ȳ���� 2007. 10. 9] // ���� ��ȣ��.
	//// param1 == �ɺ�(��ȣ��) ����, param2 == �ɺ�(��ȣ��) ü��, param3 == �ɺ�(��ȣ��) Mana, param4 == �ɺ�(��ȣ��) ����.
	//cltServer * pclServer = (cltServer*)pclClient;
	//pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_VILLAGE, LOGCOMMAND_INDEX_VILLAGE_SYMBOL_SET, 
	//								0, NULL, NULL, 0, 0, 0, NULL, 0, 0, 0, siVillageUnique, 0, 0, 
	//								clStrInfo.clCityhallStrInfo.siSymbolKind, 
	//								clStrInfo.clCityhallStrInfo.siSymbolLife, 
	//								clStrInfo.clCityhallStrInfo.siSymbolMana,
	//								symbolCapa , 0, NULL, NULL);
	//}
}




void cltCityHall::SetCastle( SI16 castleKind, SI32 castleLife, SI32 castleMana, SI16 castleCapa )
{
	clStrInfo.clCityhallStrInfo.siCastleKind = castleKind;
	clStrInfo.clCityhallStrInfo.siCastleLife = castleLife;
	clStrInfo.clCityhallStrInfo.siCastleMana = castleMana;
	clStrInfo.clCityhallStrInfo.siCastleCapa = castleCapa;

	sDBRequest_SetVillageCastle sendMsg( siVillageUnique, castleKind, castleLife, castleMana, castleCapa );

	((cltServer *)pclClient)->pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );

	//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	//{
	//	// [�α��߰� : Ȳ���� 2007. 10. 9] // ������ ������ ���°� ����� ��.
	//	// param1 == ĳ�� ����, param2 ==  ĳ�� ü��, param3 == ĳ�� Mana, param4 == ĳ�� ����.
	//	cltServer * pclServer = (cltServer*)pclClient;
	//	pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_VILLAGE, LOGCOMMAND_INDEX_VILLAGE_CASTLE_SET, 
	//									0, NULL, NULL, 0, 0, 0, NULL, 0, 0, 0, siVillageUnique, 0, 0, 
	//									castleKind, castleLife, castleMana, castleCapa, 0, NULL, NULL);
	//}
}

void cltCityHall::SetCastleLife( SI32 castleLife )
{
	clStrInfo.clCityhallStrInfo.siCastleLife = castleLife;

	sDBRequest_SetVillageCastle sendMsg( siVillageUnique, 
		clStrInfo.clCityhallStrInfo.siCastleKind, 
		castleLife,
		clStrInfo.clCityhallStrInfo.siCastleMana,
		clStrInfo.clCityhallStrInfo.siCastleCapa );

	((cltServer *)pclClient)->pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );

	//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	//{
	//	// [�α��߰� : Ȳ���� 2007. 10. 9] // ������ ������ ���°� ����� ��.
	//	// param1 == ĳ�� ����, param2 ==  ĳ�� ü��, param3 == ĳ�� Mana, param4 == ĳ�� ����.
	//	cltServer * pclServer = (cltServer*)pclClient;
	//	pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_VILLAGE, LOGCOMMAND_INDEX_VILLAGE_CASTLE_SET, 
	//									0, NULL, NULL, 0, 0, 0, NULL, 0, 0, 0, siVillageUnique, 0, 0, 
	//									clStrInfo.clCityhallStrInfo.siCastleKind, 
	//									castleLife,
	//									clStrInfo.clCityhallStrInfo.siCastleMana,
	//									clStrInfo.clCityhallStrInfo.siCastleCapa, 0, NULL, NULL);
	//}
}

void cltCityHall::SetCastleMana( SI32 castleMana )
{
	clStrInfo.clCityhallStrInfo.siCastleMana = castleMana;

	sDBRequest_SetVillageCastle sendMsg( siVillageUnique, 
		clStrInfo.clCityhallStrInfo.siCastleKind, 
		clStrInfo.clCityhallStrInfo.siCastleLife, 
		castleMana,
		clStrInfo.clCityhallStrInfo.siCastleCapa );

	((cltServer *)pclClient)->pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );

	//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	//{
	//	// [�α��߰� : Ȳ���� 2007. 10. 9] // ������ ������ ���°� ����� ��.
	//	// param1 == ĳ�� ����, param2 ==  ĳ�� ü��, param3 == ĳ�� Mana, param4 == ĳ�� ����.
	//	cltServer * pclServer = (cltServer*)pclClient;
	//	pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_VILLAGE, LOGCOMMAND_INDEX_VILLAGE_CASTLE_SET, 
	//									0, NULL, NULL, 0, 0, 0, NULL, 0, 0, 0, siVillageUnique, 0, 0, 
	//									clStrInfo.clCityhallStrInfo.siCastleKind, 
	//									clStrInfo.clCityhallStrInfo.siCastleLife, 
	//									castleMana,
	//									clStrInfo.clCityhallStrInfo.siCastleCapa, 0, NULL, NULL);
	//}
}

void cltCityHall::SetCastleCapa( SI16 castleCapa )
{
	clStrInfo.clCityhallStrInfo.siCastleCapa = castleCapa;

	sDBRequest_SetVillageCastle sendMsg( siVillageUnique, 
		clStrInfo.clCityhallStrInfo.siCastleKind, 
		clStrInfo.clCityhallStrInfo.siCastleLife, 
		clStrInfo.clCityhallStrInfo.siCastleMana,
		castleCapa );

	((cltServer *)pclClient)->pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );

	//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	//{
	//	// [�α��߰� : Ȳ���� 2007. 10. 9] // ������ ������ ���°� ����� ��.
	//	// param1 == ĳ�� ����, param2 ==  ĳ�� ü��, param3 == ĳ�� Mana, param4 == ĳ�� ����.
	//	cltServer * pclServer = (cltServer*)pclClient;
	//	pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_VILLAGE, LOGCOMMAND_INDEX_VILLAGE_CASTLE_SET, 
	//									0, NULL, NULL, 0, 0, 0, NULL, 0, 0, 0, siVillageUnique, 0, 0, 
	//									clStrInfo.clCityhallStrInfo.siCastleKind, 
	//									clStrInfo.clCityhallStrInfo.siCastleLife, 
	//									clStrInfo.clCityhallStrInfo.siCastleMana,
	//									castleCapa, 0, NULL, NULL);
	//}
}





//---------------------------------------------------------
// cltCityHallManager
//---------------------------------------------------------
cltCityHallManager::cltCityHallManager(cltCharManager* pclcm, SI32 gamemode, SI32 ranktype, TCHAR *strFileName ) : cltStructureMngBasic(MAX_CITYHALL_TAB_NUMBER, pclcm, ranktype, strFileName )
{

	UpdateWarTreeSwitch = FALSE;

	UpdateInvestSwitch  = FALSE;
	UpdateMayorCandidateSwitch	= FALSE;
	UpdateChiefCandidateSwitch	= FALSE;
	
	UpdateResidentInfoSwitch = FALSE;	
	bResidentInfoValid = FALSE;

	UpdateLevelInfoSwitch = FALSE;

	if(gamemode == GAMEMODE_CLIENT)
	{

		pclClientCandidateManager = new cltCityHallCandidateManager(); 
	}
	else
	{
		pclClientCandidateManager = NULL;
	}

	// �̺�Ʈ ��� AddEvent( eventid, �⺻���, �̺�Ʈ��, ���� )
	TCHAR* pTilte		= TEXT(" ");
	TCHAR* pText1		= TEXT(" ");
	TCHAR* pText2		= TEXT(" ");
	TCHAR pText[512]	= TEXT(" ");

	// ��Ƽ�콺 ������� �̺�Ʈ EVENT_HUNT
	if(	pclClient->IsCountrySwitch( Switch_Event_Hunt ) )
	{
		pTilte = GetTxtFromMgr(1606);
		pText1 = GetTxtFromMgr(1607);
		pText2 = GetTxtFromMgr(6721);
		 
		wsprintf(pText, "%s\r\n%s", pText1, pText2);

		clEventManager.AddEvent( CITYHALL_EVENT_HUNT, 20000000, pTilte, pText );
	}

	// ���� �̺�Ʈ - EVENT_MOFUMOFU	
	if ( pclClient->IsCountrySwitch( Switch_Event_MofuMofu ) )
	{
		pTilte = GetTxtFromMgr(7068);
		pText1 = GetTxtFromMgr(7069);
		pText2 = GetTxtFromMgr(7070);

		wsprintf(pText, "%s\r\n%s", pText1, pText2);

		clEventManager.AddEvent( CITYHALL_EVENT_MOFUMOFU, 20000000 * 1.5, pTilte, pText );
	}

	// [����] ���� �̺�Ʈ - ���� ����. 2008-3-26	
	if ( pclClient->IsCountrySwitch( Switch_Event_Monster_Attack ) )
	{
		pTilte = GetTxtFromMgr(8117);
		pText1 = GetTxtFromMgr(8118);
	
		
		//SI32 siCost = pclClient->pclItemManager->clItemStatistic.siNPCPriceRate * 500000;

		clEventManager.AddEvent( CITYHALL_EVENT_MONSTER_ATTACK, 20000000 * 1.3, pTilte, pText1 );
	}

//	���� ��ȭ�� �̺�Ʈ�� �������� �ʽ��ϴ�.

//	pTilte = GetTxtFromMgr(1608);
//	pText = GetTxtFromMgr(1609);

//	clEventManager.AddEvent( 2, 1000000, pTilte, pText );
}


cltCityHallManager::~cltCityHallManager()
{


	if( pclClientCandidateManager ) delete pclClientCandidateManager;

}

void cltCityHallManager::Update()
{
	// �ǹ��� ���� ������ ������ ��û�Ѵ�. 

	SI32 id = 1;

	if(id)
	{
		cltGameMsgRequest_StrInfo clInfo(siVillageUnique, RANKTYPE_CITYHALL);
		cltMsg clMsg(GAMEMSG_REQUEST_STRINFO, sizeof(clInfo), (BYTE*)&clInfo);
		pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	}
}


// ���� ȯ�� �λ縻ǥ�� . 
void cltCityHallManager::GreetingMsg(HWND hDlg)
{
	TCHAR* pText = GetTxtFromMgr(1610);

	SetMainExplain(hDlg, pText);
}

void cltCityHallManager::Do_WM_INITDIALOG(SI32 charunique)
{

	cltStructureMngBasic::Do_WM_INITDIALOG(charunique);

	SI32 id = 1;
	
	bChiefInfo = FALSE;
	bRecvChiefInfo = FALSE;


	// ��� �ǹ��� ��� ���� ��û 
	{
		cltMsg clMsg(GAMEMSG_REQUEST_ALLSTRCHIEFINFO, siVillageUnique );
		pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	}	
}

// �����  �ż��Ѵ�.
BOOL cltCityHallManager::CreateCityHall(SI32 siunique)
{
	if(pclStruct[siunique] == NULL)
	{
		pclStruct[siunique] = new cltCityHall(siunique);
		return TRUE;
	}
	return FALSE;
}

// Chief �ĺ��� ����Ѵ�. 
BOOL cltCityHallManager::SetCandidate(SI32 index, cltSimpleRank* pclrank, cltSimplePerson* pclcandidate)
{
	if(pclcandidate == NULL) return FALSE;

	SI32 ref = pclrank->GetVillageUnique();
	if(ref >=0 && pclStruct[ref])
	{
		return pclStruct[ref]->SetCandidate(index, pclrank, pclcandidate);
	}

	return FALSE;
}

// �ĺ� ����� ����Ѵ�. (��� ��å����..) 
BOOL cltCityHallManager::DeleteCandidate(SI32 villageunique, SI32 personid)
{
	if(personid == 0) return FALSE;
	if(villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER)return FALSE;

	return pclStruct[villageunique]->DeleteCandidate(personid);
}

// Ư�� �ź��� ��� �ĺ� ����� ����Ѵ�.
BOOL cltCityHallManager::DeleteCandidate(cltSimpleRank* pclrank)
{
	if(pclrank == 0) return FALSE;
	return pclStruct[pclrank->siVillageUnique]->DeleteCandidate(pclrank);
}

void cltCityHallManager::OnTimer()
{

}


// �ֱ����� ó�� 
void cltCityHallManager::Action(cltTime* pcltime)
{
	int i = 0;
	cltStrInfo *pclStrInfo = NULL;
	cltHiredNPC *pclHiredNPC = NULL;
	cltHiredNPC *pclEventHiredNPC = NULL;
	cltCityHall *pclCityHall = NULL;
	
	cltServer *pclServer = (cltServer *)pclClient;

	if(pcltime == NULL) return;

	// DB �ʱ�ȭ �Ϸ�ɶ����� ��ٸ�
	if( ((cltServer *)pclClient)->bCompleteDBInitAll == FALSE ) return;

	bool bdaychangedswitch = pcltime->IsDayChanged();

	if( bdaychangedswitch )
	{
		for( i = 1; i < MAX_VILLAGE_NUMBER; ++i ) 
		{
			// [����] �ʺ��� ���� : �ʺ��� ���� ����� ������ ������ �ʴ´�
			if ( pclClient->IsCountrySwitch(Switch_TutorialVillage) )
			{
				if ( i == Const_Beginner_Village)	{									continue;		}
			}

			pclCityHall = (cltCityHall *)pclStruct[ i ];	if( pclCityHall == NULL )	continue;
			pclStrInfo = GetStrInfo( i );					if( pclStrInfo == NULL )	continue;

			// ���� ���¿� ���� üũ�Ѵ�.
			switch( GetCityHallState( i ) )
			{
			case CITYHALL_BEING_BANKRUPT:	// ���� �Ļ� ��
				{
					// ���� �Ļ��� �Ǿ� ��� �ֽĿ� ���� ó���� �Ϸ�Ǿ��ٸ�
					if( pclStrInfo->clCityhallStrInfo.siTotalStockAmount == 0 )
					{
						pclStrInfo->clCityhallStrInfo.usCurStatus = CITYHALL_BEING_PROCESSING;

						// ���� ��� ���� ������ DB�� ������Ʈ �Ѵ�. => �ʱ�ȭ �Ϸ��
						sDBRequest_CityHall_State_Changed clMsg( i, CITYHALL_BEING_BANKRUPT, CITYHALL_BEING_INITIALIZED );
						((cltServer *)pclClient)->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
					}
				}
				break;

			case CITYHALL_BEING_INITIALIZED:// ���� �ʱ�ȭ ���� ��
				{
					if( pclStrInfo->clCityhallStrInfo.siTotalStockAmount == 0 )
					{
						pclStrInfo->clCityhallStrInfo.usCurStatus = CITYHALL_BEING_PROCESSING;

						// ���� ��� ���� ������ DB�� ������Ʈ �Ѵ�. => ������ ��
						sDBRequest_CityHall_State_Changed clMsg( i, CITYHALL_BEING_INITIALIZED, CITYHALL_BEING_STABLE );
						((cltServer *)pclClient)->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
					}
				}
				break;
			case CITYHALL_BEING_STABLE:		// ���� ������, �����⿡�����ʹ� �ֽ� ���� �� �ֽ� ������ �����ϴ�.
				{
					// ������� �Ӹ�Ǿ��°�
					cltRank* pclrank = ((cltServer *)pclClient)->pclRankManager->GetRank(RANKTYPE_CITYHALL, i);

					if(pclrank == NULL || pclrank->clPerson.siPersonID == 0  ) // ������� ������
						break;

					cltDate cldate;
					cldate.Set( &pclStrInfo->clCityhallStrInfo.clChiefDate );

					cldate.uiYear = cldate.uiYear + CITYHALL_STABLE_YEARS_AFTER_CHIEF_ELECTION;	// ������ ����

					// ������(����� ���� �� 1��)�� �� ������
					if( cldate.GetDateVary() < ((cltServer *)pclClient)->pclTime->clDate.GetDateVary() ) 
					{
						pclStrInfo->clCityhallStrInfo.usCurStatus = CITYHALL_BEING_PROCESSING;

						// ���� ��� ���� ������ DB�� ������Ʈ �Ѵ�. => ����� ��
						sDBRequest_CityHall_State_Changed clMsg( i, CITYHALL_BEING_STABLE, CITYHALL_BEING_NORMAL );
						((cltServer *)pclClient)->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
					}
				}
				break;
			case CITYHALL_BEING_NORMAL:		// ���� �����
				{
					// ����� ���� ���̶��
					// �迭�� �����ֱ� ������ NULL�� ����� �� ����.
					cltRank*		pclCityHallRank = pclServer->pclRankManager->GetRank(RANKTYPE_CITYHALL, i);
					SI32			siCityHallRankPersonID = pclCityHallRank->GetPersonID();

					// ������������ ���ٴ� �� ���ְ� ���ٴ� �̾߱Ⱑ �ǹǷ� ó������ �ʴ´�.
					if(pclStrInfo->clCityhallStrInfo.clChiefDate.GetDateVary() == 0 )			break;

					if(pclCityHallRank != NULL && siCityHallRankPersonID > 0 ) // ������� ���� ���̶��
					{
						cltDate cldate;
						cldate.Set( &pclStrInfo->clCityhallStrInfo.clChiefDate );

						cldate.uiYear = cldate.uiYear + 2;		// ���� ������ 2���� ��������...						
						if( cldate.GetDateVary() < ((cltServer *)pclClient)->pclTime->clDate.GetDateVary() )
						{
							bool bCityHallRank_Resign = true;
#ifdef _DEBUG
							// ======================== ����� ���� =================================
							// ���ְ� ��ڱ����� ���� ĳ���Ͷ�� �ڵ����� ���ӽ�Ű�� �ʴ´�.							
							// ���� ��� ���� üũ�� ĳ���� �̸��� "NDS"���� �����ϴ� ĳ���� �̴�.
							if( _tcsncmp(pclCityHallRank->GetName(), "NDS", 3 ) == 0 )
							{
								bCityHallRank_Resign = false;
							}
							// ======================================================================
#endif
							if( bCityHallRank_Resign )
							{
								cltSimpleRank clrank( RANKTYPE_CITYHALL, i);

								// Rank�������� ����ڸ� �����Ѵ�. 
								sDBRequest_Resign clMsg( 0, siCityHallRankPersonID, &clrank );
								pclServer->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
							}
						}
					}
					else // ������� ���� ���̶��
					{
						cltDate cldate;

						//============================================================================
						// ���� ����� �Ⱓ�� ������ ���ְ� ���ӵ��� 6������ ������ �Ļ� ��� �Ѵ�.
						//============================================================================
						cldate.Set( &pclStrInfo->clCityhallStrInfo.clResignDate );				
						cldate.AddMonth( CITYHALL_BANKRUPTCY_NOTIFY_AFTER_MONTHS );	// AddMonth �Լ��� �� ��

						// Letter�� �ѹ��� �ǽð����� ������
                        if( cldate.GetDateVary() == ((cltServer *)pclClient)->pclTime->clDate.GetDateVary() ) 
						{
							// �Ļ� �� ����� ���� ����, ������ȸ ���� ������ �� 6�����̸�
							// Ư�� ���� �鿡�� �˸�
							// �ش� ���ֵ��� PersonID�� DB�� ��û�Ѵ�. => Letter Msg�� �˸�
							sDBRequest_Notify_Cityhall_Bankruptcy clMsg( i, cltLetterMsg_VillageNameAndDate::LETTERTYPE_CITYHALLBANKRUPTCY_ALERT );
							((cltServer *)pclClient)->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
						}

						//============================================================================
						// ���� ����� �Ⱓ�� ������ ���ְ� ���ӵ��� 1���� ������ ���� �Ļ��Ų��.
						//============================================================================
						cldate.Set( &pclStrInfo->clCityhallStrInfo.clResignDate );
						cldate.uiYear = cldate.uiYear + CITYHALL_BANKRUPTCY_AFTER_YEARS;
						
						if( cldate.GetDateVary() <= ((cltServer *)pclClient)->pclTime->clDate.GetDateVary() ) 
						{
							// ������ȸ�� ���� ���� �Ļ����� ��
							if( pclCityHall->clGeneralMeetingInfo.siMatterType == 0 )
							{
								// ���� ��� ���� ������ DB�� ������Ʈ �Ѵ�. => �Ļ� ��
								sDBRequest_CityHall_State_Changed clMsg( i, CITYHALL_BEING_NORMAL, CITYHALL_BEING_BANKRUPT );
								((cltServer *)pclClient)->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
							}
						}
					}
				}
				break;
			} // switch( GetCityHallState( i ) ) ����

			// [����] ������ȸ�� ���� ���̸� => 2008-7-21
			if( pclCityHall->clGeneralMeetingInfo.siMatterType > 0 ) 
			{
				cltDate cldate;
				cldate.Set( &((cltServer *)pclClient)->pclTime->clDate );

				// [����] ���� ���� �Ⱓ�̸�.
				if( ( pclCityHall->clGeneralMeetingInfo.clStartDate.GetDateVary() <= cldate.GetDateVary() ) &&
					( pclCityHall->clGeneralMeetingInfo.clCloseDate.GetDateVary() >  cldate.GetDateVary() )		)
				{
					cltDate clAcceptClosedate;	// ���� ���� �ð�.				
					clAcceptClosedate.Set(&pclCityHall->clGeneralMeetingInfo.clStartDate);
					clAcceptClosedate.AddMonth(1);

					// ���� ���� �Ⱓ���� ���� 1���� �����ٸ�.
					if(clAcceptClosedate.GetDateVary() < cldate.GetDateVary() )
					{
						// �ĺ��ڰ� �������� ���� - 1�޾ȿ� �ĺ��ڰ� �������� ������ ���� ����
						if( pclCityHall->clGeneralMeetingInfo.siAcceptCandidate <= 0 )
						{
							sDBRequest_GeneralMeeting_CloseChief sendMsg( i, 0, &((cltServer *)pclClient)->pclTime->clDate );
							((cltServer *)pclClient)->pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );
						}
					}
				}
				// ���� ���� �ð�(���ѹ��� �� 3����)���� ���� �ð� ������ �ð��� �ƴϸ�.
				else 
				{
					sDBRequest_GeneralMeeting_CloseChief sendMsg( i, pclCityHall->clGeneralMeetingInfo.GetResult(), &((cltServer *)pclClient)->pclTime->clDate );
					((cltServer *)pclClient)->pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );
				}
			} 

		} // if ( pclStrInfo ) ����

		// �Ѵ޿� �ѹ� 1�Ͽ� �������� ���� �ൿ
		if( pcltime->clDate.uiDay == 1 ) 
		{
			cltDate clDate;
			clDate.Set( &((cltServer *)pclClient)->pclTime->clDate );
			if ( clDate.uiYear > 2 )
			{
				clDate.uiYear--;
				for ( i = 1; i < MAX_VILLAGE_NUMBER; ++i ) 
				{
					// [����] �ʺ��� ���� : �ʺ��� ���� ����� ������ ������ �ʴ´�
					if ( pclClient->IsCountrySwitch(Switch_TutorialVillage) )
					{
						if ( i == Const_Beginner_Village)			{		continue;		}
					}

					pclStrInfo = GetStrInfo( i );
					if( pclStrInfo ) 
					{
						// 1�⵿�� �α��� ���� ���� �ֹ��� Ż���Ų��.
						sDBRequest_ManyResidentOut sendMsg( i, &clDate );
						((cltServer *)pclClient)->pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );
					}
				} // for ( i = 1; i < MAX_VILLAGE_NUMBER; ++i ) ����
			}
		} // if( pcltime->clDate.uiDay == 1 ) ����
		
		// NPC ������ - �Ϸ翡 �ѹ� üũ
		for( SI32 villagenum = 1; villagenum < MAX_VILLAGE_NUMBER; ++villagenum ) 
		{
			// [����] �ʺ��� ���� : �ʺ��� ���� ����� ������ ������ �ʴ´�
			if ( pclClient->IsCountrySwitch(Switch_TutorialVillage) )
			{
				if ( villagenum == Const_Beginner_Village)		{		continue;		}
			}

			pclStrInfo = GetStrInfo( villagenum );
			if ( pclStrInfo ) 
			{
				// �Ϲ����� NPC�� 1���� ������ ����� ��ҵȴ�.
				for ( SI32  npcNum = 0; npcNum < MAX_HIRED_NPC_NUM; ++npcNum ) 
				{
					pclHiredNPC = &pclStrInfo->clCityhallStrInfo.clHiredNPC[ npcNum ];
					if( pclHiredNPC->siNPCKind > 0 ) 
					{
						// ��� 1���� �������� ��� ����
						SI32 hiredate = pclHiredNPC->clHireDate.GetDateVary();
						SI32 currdate = ((cltServer *)pclClient)->pclTime->clDate.GetDateVary();

						if( currdate - hiredate > 360 ) {

							sDBRequest_HireNPC clMsg( 0, villagenum, npcNum, 0, 0, 0, &((cltServer *)pclClient)->pclTime->clDate, HIRENPC_HIRENPC );
							((cltServer *)pclClient)->pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg );
						}
					} // if( pclHiredNPC->siNPCKind > 0 ) ����
				} // for( SI32  npcNum = 0; npcNum < MAX_HIRED_NPC_NUM; ++npcNum ) ����

				// EVENTNPC�� �Ϲ������� 1���� ������ ����� ��ҵȴ�.
				// NPC ���� ��������� Ʋ�� ���� �ִ�.
				for( SI32 eventnpcNum= 0; eventnpcNum < MAX_HIRED_EVENTNPC_NUM; ++eventnpcNum ) 
				{
					pclEventHiredNPC = &pclStrInfo->clCityhallStrInfo.clHiredEventNPC[ eventnpcNum ];
					if( pclClient->pclKindInfoSet->IsValidKind(pclEventHiredNPC->siNPCKind) == false )		continue;

	/*					SYSTEMTIME stevent, enevent;
						ZeroMemory(&stevent, sizeof(stevent));
						ZeroMemory(&enevent, sizeof(enevent));

						stevent.wYear = 2007;	stevent.wMonth = 12;	stevent.wDay = 1;
						enevent.wYear = 2007;	enevent.wMonth = 12;	enevent.wDay = 26;		enevent.wHour = 11;
						if(pclClient->IsWhereServiceArea(ConstServiceArea_Korea))
						{
							enevent.wYear = 2007;	enevent.wMonth = 12;	enevent.wDay = 27;		enevent.wHour = 6;
						}
						else if(pclClient->IsWhereServiceArea(ConstServiceArea_English))
						{
							enevent.wYear = 2007;	enevent.wMonth = 12;	enevent.wDay = 27;		enevent.wHour = 6;
						}
						else if(pclClient->IsWhereServiceArea(ConstServiceArea_NHNChina))
						{
							enevent.wYear = 2007;	enevent.wMonth = 12;	enevent.wDay = 27;		enevent.wHour = 6;
						}*/

						// ũ�������� Ʈ���� �̺�Ʈ �Ⱓ ���Ŀ��� �������.
						/*if( pclEventHiredNPC->siNPCKind == pclClient->GetUniqueFromHash(TEXT("KIND_PINE_TREE")) ||
							pclEventHiredNPC->siNPCKind == pclClient->GetUniqueFromHash(TEXT("KIND_CHRISTMASTREE")) )
						{
							if( TimeInBounds( &pclServer->sTime, &stevent, &enevent ) == false )
							{
								sDBRequest_HireNPC clMsg( 0, villagenum, eventnpcNum, 0, 0, 0, &((cltServer *)pclClient)->pclTime->clDate, HIRENPC_HIREEVENTNPC );

								((cltServer *)pclClient)->pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg );
							}
						}
						//[�߰� : Ȳ���� 2007. 12. 11 �ų� Ʈ�� �Ⱓ�� ������ �׾�.]
						else if( pclEventHiredNPC->siNPCKind == pclClient->GetUniqueFromHash(TEXT("KIND_KADOMACH")) || 
									pclEventHiredNPC->siNPCKind == pclClient->GetUniqueFromHash(TEXT("KIND_NEWYEARTREE"))	)
						{
							stevent.wYear = 2007;	stevent.wMonth = 12;	stevent.wDay = 26;
							enevent.wYear = 2008;	enevent.wMonth =  1;	enevent.wDay = 10;		enevent.wHour = 11;

							if(pclClient->IsWhereServiceArea(ConstServiceArea_English))
							{
								stevent.wYear = 2007;	stevent.wMonth = 12;	stevent.wDay = 27;	stevent.wHour = 7;
							}
							else if(pclClient->IsWhereServiceArea(ConstServiceArea_NHNChina))
							{
								stevent.wYear = 2007;	stevent.wMonth = 12;	stevent.wDay = 27;	stevent.wHour = 7;
							}

							if(false == TimeInBounds( &pclServer->sTime, &stevent, &enevent ))
							{
								sDBRequest_HireNPC clMsg( 0, villagenum, eventnpcNum, 0, 0, 0, &((cltServer *)pclClient)->pclTime->clDate, HIRENPC_HIREEVENTNPC );

								((cltServer *)pclClient)->pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg );
							}
						}*/
						//[����] ������ ���� �̺�Ʈ �Ⱓ �� ����. => 2008-6-11//
					if( pclEventHiredNPC->siNPCKind == pclClient->GetUniqueFromHash(TEXT("KIND_ROULETTESTATUEBASE"))  
						|| pclEventHiredNPC->siNPCKind == pclClient->GetUniqueFromHash(TEXT("KIND_ROULETTESTATUE"))	)
					{
						if(false == ((cltServer *)pclClient)->pclEventTimeManager->InEventTime("Hero_Bronze", &pclServer->sTime) )
						{
							sDBRequest_HireNPC clMsg( 0, villagenum, eventnpcNum, 0, 0, 0, &((cltServer *)pclClient)->pclTime->clDate, HIRENPC_HIREEVENTNPC );

							((cltServer *)pclClient)->pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg );
						}
					}
					//[����] �ҷ��� �д� �̺�Ʈ �Ⱓ�� ���� //Switch_HalloweenEvent
					else if( pclEventHiredNPC->siNPCKind == pclClient->GetUniqueFromHash(TEXT("KIND_HALLOWEENBASE"))  
							 || pclEventHiredNPC->siNPCKind == pclClient->GetUniqueFromHash(TEXT("KIND_HALLOWEEN"))	)
					{
						if(false == ((cltServer *)pclClient)->pclEventTimeManager->InEventTime("HalloweenEvent", &pclServer->sTime) )
						{
							sDBRequest_HireNPC clMsg( 0, villagenum, eventnpcNum, 0, 0, 0, &((cltServer *)pclClient)->pclTime->clDate, HIRENPC_HIREEVENTNPC );

							((cltServer *)pclClient)->pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg );
						}
					}
					//KHY - 1113 - ũ�������� �̺�Ʈ -  ũ���� ���� ����  �Ⱓ�� ����.
					else if(    pclEventHiredNPC->siNPCKind == pclClient->GetUniqueFromHash(TEXT("KIND_CHRISTMASTREEBASE"))  
							 || pclEventHiredNPC->siNPCKind == pclClient->GetUniqueFromHash(TEXT("KIND_CHRISTMASTREE1"))	)
					{
						if(false == ((cltServer *)pclClient)->pclEventTimeManager->InEventTime("ChristmasEvent", &pclServer->sTime) )
						{
							sDBRequest_HireNPC clMsg( 0, villagenum, eventnpcNum, 0, 0, 0, &((cltServer *)pclClient)->pclTime->clDate, HIRENPC_HIREEVENTNPC );

							((cltServer *)pclClient)->pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg );
						}
					}
					// ��� - �ų��̺�Ʈ - �ų⳪�� �Ⱓ�� ����
					else if( pclEventHiredNPC->siNPCKind == pclClient->GetUniqueFromHash(TEXT("KIND_NEWYEARTREEBASE"))  
						|| pclEventHiredNPC->siNPCKind == pclClient->GetUniqueFromHash(TEXT("KIND_NEWYEARTREE"))	)
					{
						if(false == ((cltServer *)pclClient)->pclEventTimeManager->InEventTime("NewYearEvent", &pclServer->sTime) )
						{
							sDBRequest_HireNPC clMsg( 0, villagenum, eventnpcNum, 0, 0, 0, &((cltServer *)pclClient)->pclTime->clDate, HIRENPC_HIREEVENTNPC );

							((cltServer *)pclClient)->pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg );
						}
					}
					// ��� - ���������� - ������ �Ⱓ�� ����
					else if( pclEventHiredNPC->siNPCKind == pclClient->GetUniqueFromHash(TEXT("KIND_HINADOLL")))
					{
						if(false == ((cltServer *)pclClient)->pclEventTimeManager->InEventTime("Hinamatsuri", &pclServer->sTime) )
						{
							sDBRequest_HireNPC clMsg( 0, villagenum, eventnpcNum, 0, 0, 0, &((cltServer *)pclClient)->pclTime->clDate, HIRENPC_HIREEVENTNPC );

							((cltServer *)pclClient)->pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg );
						}
					}
					else
					{
						SI32 hiredate = pclEventHiredNPC->clHireDate.GetDateVary();
						SI32 currdate = ((cltServer *)pclClient)->pclTime->clDate.GetDateVary();

						// �⺻������ �̺�Ʈ NPC�� 1���� �����ڿ� ����� ��ҵȴ�.
						SI32 siMaxHireDate = 360;

						// KIND_RETURNTOWER �̺�Ʈ NPC�� 2���� �����ڿ� ����� ��ҵȴ�.
						if( pclEventHiredNPC->siNPCKind == pclClient->GetUniqueFromHash(TEXT("KIND_RETURNTOWER")) )
							siMaxHireDate = 720;

						if( currdate - hiredate > siMaxHireDate ) 
						{
							sDBRequest_HireNPC clMsg( 0, villagenum, eventnpcNum, 0, 0, 0, &((cltServer *)pclClient)->pclTime->clDate, HIRENPC_HIREEVENTNPC );
							((cltServer *)pclClient)->pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg );
						}
					}
				} // for( SI32 eventnpcNum= 0; eventnpcNum < MAX_HIRED_EVENTNPC_NUM; ++eventnpcNum ) ����
			} // for villagenum ����
		} 
		
		if(	((cltServer*)pclClient)->bForceTimeSwitch == false )
		{
			WriteAllCityHallState();
		}
	}// if( bdaychangedswitch )
}

BOOL cltCityHallManager::IsGeneralMeeting( SI32 villageunique )
{
	cltCityHall *pclCityHall = (cltCityHall *)pclStruct[ villageunique ];

	if( pclCityHall && pclCityHall->clGeneralMeetingInfo.siMatterType > 0 ) {
		return TRUE;
	}

	return FALSE;
}

BOOL cltCityHallManager::IsPrepareBankruptcy( SI32 villageunique )
{
	cltCityHall *pclCityHall = (cltCityHall *)pclStruct[ villageunique ];

	if( pclCityHall && pclCityHall->bPrepareBankruptcy ) 
	{
		return TRUE;
	}

	return FALSE;
}

//#if defined(_CITYHALL_BANKRUPTCY)
// ����� �Ļ� ���¸� ����
UI08 cltCityHallManager::GetCityHallState( SI32 villageunique )
{
	cltStrInfo* pStrInfo = GetStrInfo( villageunique );

	if( pStrInfo == NULL || villageunique < 1 ) 
		return CITYHALL_UNDEFINED_STATE;
  //  if( pStrInfo->clCityhallStrInfo == NULL )
		//return CITYHALL_UNDEFINED_STATE;	
	
	return pStrInfo->clCityhallStrInfo.usCurStatus;
}

// �Ļ��� �� ������ ��� ��Ұ� �ʱ�ȭ �Ǿ��°�
BOOL cltCityHallManager::IsInitialized( SI32 villageunique )
{
	cltStrInfo* pStrInfo = GetStrInfo( villageunique );

	if( pStrInfo == NULL ) return FALSE;
	if( pStrInfo->clCityhallStrInfo.usCurStatus == CITYHALL_BEING_BANKRUPT
		&& pStrInfo->clCityhallStrInfo.siTotalStockAmount == 0 )
		return TRUE;

	return FALSE;

    // ���� Ʈ�� �и� �ʱ�ȭ
	// ...

	// �ֽ� �ʱ�ȭ
	// ...

	// NPC �ʱ�ȭ
	// ...

	// �����ڱ� �ʱ�ȭ
	// ...

	// �������� �ʱ�ȭ
	// ...

	// �⺻�ǹ�[������] �ʱ�ȭ
	// ...

	// ���� �ʱ�ȭ
	// ...

	// ��Ȳ�� �ʱ�ȭ
	// ...

	// ... ?
}

// ��û �Ļ���� Ȥ�� �����Ⱑ ������ DeadLine ������ ��´�.
cltDate  cltCityHallManager::GetCityHallBankruptcyDetailInfo( cltCityhallStrInfo* pstrinfo )
{
	cltDate cldate;
	cltDate remaineddate;	// ���� �ð�
	memset(&cldate, 0, sizeof(cltDate) );
	memset(&remaineddate, 0, sizeof(cltDate) );

	if( pclClient->GameMode != GAMEMODE_CLIENT ) return remaineddate;
	if( pstrinfo == NULL ) return remaineddate;

    switch( pstrinfo->usCurStatus )
	{
	case CITYHALL_BEING_NORMAL:			// �����
		{
			cldate.Set( &pstrinfo->clResignDate );

			cldate.uiYear = cldate.uiYear + CITYHALL_BANKRUPTCY_AFTER_YEARS;
			
			// ����� ���� �� 1���� ������ ����� ������ ���� �� ���� �Ļ� ���� 
			// �� ���� �ð� ����
			if( cldate.GetDateVary() >= ((cltClient*)pclClient)->clClientDate.GetDateVary() ) 
			{
				remaineddate.DiffDate( &cldate, &((cltClient*)pclClient)->clClientDate );
			}
		}
		break;
	case CITYHALL_BEING_BANKRUPT:		// �Ļ��
		{

		}
		break;
	case CITYHALL_BEING_INITIALIZED:	// �ʱ�ȭ��
		{

		}
		break;
	case CITYHALL_BEING_STABLE:			// ������
		{
			cldate.Set( &pstrinfo->clChiefDate );

			cldate.uiYear = cldate.uiYear + CITYHALL_STABLE_YEARS_AFTER_CHIEF_ELECTION;	// ������ ����

			if( cldate.GetDateVary() >= ((cltClient*)pclClient)->clClientDate.GetDateVary() ) 
			{
				remaineddate.DiffDate( &cldate, &((cltClient*)pclClient)->clClientDate );
			}
		}
		break;
	default :							// �� �� ����
		return remaineddate;
	}

	return remaineddate;
}

void cltCityHallManager::WriteAllCityHallState()
{
	SI32 i;

	cltStrInfo *pclStrInfo = NULL;
	cltCityHall *pclCityHall = NULL;

	FILE *fp = _tfopen( TEXT("Config/CityHallState.log"), TEXT("wt") );

	if ( fp == NULL )
	{
		return;
	}

	// �� ù��. 
	// Name : ������, State : ���� ����, Chief : ����� ����, Schedule : ���� �Ļ� ������
	// GeneralMeeting : ������ȸ ������ ����, TotalStock : ���ֽļ�
	_ftprintf( fp, TEXT("%s\t\t\t%s\t%s\t%s\t%s\t%s\n"), TEXT("Name"), TEXT("State"), TEXT("DeadLine"), TEXT("Chief"), TEXT("GeneralMeeting"), TEXT("TotalStock"));

	for (i = 0; i < MAX_VILLAGE_NUMBER; ++i )
	{
		pclCityHall = (cltCityHall *)pclStruct[ i ];

		if( pclCityHall == NULL ) continue;	

		pclStrInfo = GetStrInfo( i );
		if( pclStrInfo == NULL) continue;

		TCHAR* pname = pclClient->pclVillageManager->GetName( i );
		if(pname == NULL) return ;

		UI08 uiState = GetCityHallState( i );

		TCHAR* pChief = NULL;
		TCHAR* pGeneralMeeting = NULL;
		TCHAR* pStatename = NULL;
		TCHAR* pSchedule = NULL;

		TCHAR deadline[256];
		memset(deadline, 0, sizeof(deadline));

		// ����� ����
		cltRank* pclrank = ((cltServer *)pclClient)->pclRankManager->GetRank(RANKTYPE_CITYHALL, i);

		if(pclrank == NULL || pclrank->clPerson.siPersonID == 0  )
			pChief = TEXT("X");
		else
			pChief = TEXT("O");

		// ������ȸ ����
		if( pclCityHall->clGeneralMeetingInfo.siMatterType == 0 )
			pGeneralMeeting = TEXT("X");
		else
			pGeneralMeeting = TEXT("O");

		StringCchPrintf( deadline, 256, GetTxtFromMgr(1644), 0, 0, 0 );

		switch( uiState )
		{
		case 	CITYHALL_BEING_BANKRUPT	:		// �Ļ��
			{
				pStatename = GetTxtFromMgr(5240);

				StringCchPrintf( deadline, 256, TEXT("%s%s"), GetTxtFromMgr(5241), GetTxtFromMgr(1223)); 	// "�ʱ�ȭ �ʿ�"
			}
			break;
		case 	CITYHALL_BEING_INITIALIZED	:	// �ʱ�ȭ��
			{
				pStatename = GetTxtFromMgr(5241);
			}
			break;
		case 	CITYHALL_BEING_STABLE		:	// ������
			{
				pStatename = GetTxtFromMgr(5242);

				if(pclrank == NULL || pclrank->clPerson.siPersonID == 0  ) // ������� ������
					break;
				
				// ����� �������� �������̰� ������ >= �������̾����, ���� �� �� �� ����
				//if( pclStrInfo->clCityhallStrInfo.clChiefDate.GetDateVary() >= pclStrInfo->clCityhallStrInfo.clResignDate.GetDateVary() )
				{
					cltDate cldate;			// deadlline date
					cltDate remaineddate;	// ���� �ð�
					cldate.Set( 0, 0, 0, 0, 0);
					remaineddate.Set(0, 0, 0, 0, 0);
					pSchedule = GetTxtFromMgr(1644);	// %d�� %d�� %d��

					cldate.Set( &pclStrInfo->clCityhallStrInfo.clChiefDate );

					cldate.uiYear = cldate.uiYear + CITYHALL_STABLE_YEARS_AFTER_CHIEF_ELECTION;	// ������ ����

					if( cldate.GetDateVary() >= ((cltServer *)pclClient)->pclTime->clDate.GetDateVary() ) 
					{
						remaineddate.DiffDate( &cldate, &(((cltServer *)pclClient)->pclTime->clDate) );
					}
					
					StringCchPrintf( deadline, 256, pSchedule, remaineddate.uiYear, remaineddate.uiMonth, remaineddate.uiDay );
				}

			}
			break;
		case 	CITYHALL_BEING_NORMAL		:	// �����
			{
				pStatename = GetTxtFromMgr(5239);

				//if(pclrank == NULL || pclrank->clPerson.siPersonID == 0  ) // ������� ������
				{
					cltDate cldate;
					cltDate remaineddate;	// ���� �ð�
					cldate.Set(0, 0, 0, 0, 0 );
					remaineddate.Set(0, 0, 0, 0, 0);
					pSchedule = GetTxtFromMgr(1644);	// %d�� %d�� %d��

					//cldate.Set( &pclStrInfo->clCityhallStrInfo.clResignDate );
					//// AddMonth �Լ��� �� ��
					//cldate.AddMonth( CITYHALL_BANKRUPTCY_NOTIFY_AFTER_MONTHS );

					// ==================================================
					cldate.Set( &pclStrInfo->clCityhallStrInfo.clResignDate );

					cldate.uiYear = cldate.uiYear + CITYHALL_BANKRUPTCY_AFTER_YEARS;
					
					// ����� ���� �� 1���� ������ ����� ������ ���� �� ���� �Ļ� ���� ��
					// ���� �ð� ����
					if( cldate.GetDateVary() >= ((cltServer *)pclClient)->pclTime->clDate.GetDateVary() ) 
					{
						remaineddate.DiffDate( &cldate, &(((cltServer *)pclClient)->pclTime->clDate) );
					}

					StringCchPrintf( deadline, 256, pSchedule, remaineddate.uiYear, remaineddate.uiMonth, remaineddate.uiDay );
				}
			}
			break;
		default:
			{
				pStatename = TEXT("Error");			// ����
			}
			break;
		}

		SI32 siTotalStockAmount = pclStrInfo->clCityhallStrInfo.siTotalStockAmount;

		// TEXT("Name"), TEXT("State"), TEXT("DeadLine"), TEXT("Chief"), TEXT("GeneralMeeting"), TEXT("TotalStock")

		_ftprintf( fp, TEXT("%s\t\t\t%s\t%s\t%s\t%s\t%d\n"), 
			pname,
			pStatename,
			deadline,
			pChief,
			pGeneralMeeting,
			siTotalStockAmount            
			);
	}
	
	fclose( fp );

	return;
}

//#endif
