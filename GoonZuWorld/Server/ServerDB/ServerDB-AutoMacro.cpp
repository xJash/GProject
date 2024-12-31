#include "..\Common\CommonHeader.h"
#include "..\Server\Server.h"
#include "../GMSystem/GMSectionData.h"
#include "../GMSystem/GMProtocol.h"
#include "..\GMSystem\GMMsg.h"
#include "../Server/Server.h"

#include "../CommonLogic/House/House.h"
#include "../Common/Skill/Skill-Manager.h"
#include "../Common/Char/CharManager/CharManager.h"

#include "../../DBManager/GameDBManager_World/DBMsg-AutoMacro.h"
#include "../../DBManager/GameDBManager_World/DBMsg-System.h"
#include "../../GoonZuWorld/CommonLogic/Msg/MsgType-AutoMacro.h"


// [�߰� : Ȳ���� 2007. 12. 7 �������α׷� �޽��� ó�� DB -> S]
void cltServer::DoMsg_DBMSG_RESPONSE_AUTOMACRO(sPacketHeader* pPacket)
{
	sDBResponse_AutoMacro* pReveMsg = (sDBResponse_AutoMacro*) pPacket;	

	SI32 id = pReveMsg->usCharID;
	// ������ ���� - by LEEKH 2008.02.13
	if( pclCM->IsValidID(id) == false )						return;

	if(pclCM->CR[id]->pclCI->GetPersonID() != pReveMsg->siPersonID)
	{
		return;
	}
	cltGameMsgReponse_AutoMacroOnOther AutoMacroOnOther(pReveMsg->uiAutoMacroCnt, pclCM->CR[id]->pclCI->clBI.clPerson.GetName());
	cltMsg clMsg( GAMEMSG_RESPONSE_AUTOMACRO_ON_OTHER, sizeof(AutoMacroOnOther), (BYTE*)&AutoMacroOnOther);

	// �����ġ(��ü����, ���ΰ��).
	if(1 == pReveMsg->uiAutoMacroCnt)
	{
		// ��ü ����
		SI32 index = 0;
		SI32 id	   = 0;
		while(id = pclClient->pclCM->GetCharOrder(index))
		{
			index++;

			// ������� �Ŀ��Ը� �����Ѵ�. 
			if( true == pclClient->pclCM->CR[id]->IsValidConnection() )
			{
				pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
			}
		}
	}
	// 7�ϰ� ���� ���� ����. �ϴ� ���������� �����ϰ� �޽����� ������.
	else 
	{
		// ��ü ����
		SI32 index = 0;
		SI32 id	   = 0;
		while(id = pclClient->pclCM->GetCharOrder(index))
		{
			index++;

			// ������� �Ŀ��Ը� �����Ѵ�. 
			if( true == pclClient->pclCM->CR[id]->IsValidConnection() )
			{
				pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
			}
		}
		/*
		sDBRequest_BlockUser clMsg(0, sDBRequest_BlockUser::BLOCK_UNTIL_DAYS, "", 7, "AutoMacro");
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
		*/
	}
}