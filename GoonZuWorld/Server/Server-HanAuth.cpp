//---------------------------------
// 2006/6/17 �̰���
//---------------------------------

#include "..\Common\CommonHeader.h"
#include "..\Server\Server.h"

#include "Char\CharManager\CharManager.h"

#include "..\..\DBManager\GameDBManager_World\DBMsg-Item.h"
#include "..\..\DBManager\GameDBManager_World\DBMsg-System.h"
#include "..\..\DBManager\GameDBManager_World\DBMsg-ItemMall.h"

extern cltCommonLogic* pclClient;

// -HanAuth_Lib
#ifdef USE_HANXNOTI
//#ifdef _SERVER
// -HanAuth_Lib

bool __stdcall cltServer::HanXNoti_DoMsg_GMTMessageReq_K_GOONZU(XStream::Handle stream, void* pAdditionalData, void* pContext)
{
	//----------------------------------------------------------------
	// ������ ������ ��
	//----------------------------------------------------------------
#ifdef _SERVER
	//----------------------------------------------------------------

	if(pclClient->GameMode == GAMEMODE_CLIENT)		return false;

	cltServer* pclserver = (cltServer*)pclClient;
	if(pclserver->pclGameDBProcess == NULL)			return false;

	GMTMessageReq_K_GOONZU	kRecvMsg;
	kRecvMsg.Load(stream);

	GMTMessageAns_K_GOONZU	kSendMsg;
	kSendMsg.nIdx = kRecvMsg.nIdx;
	kSendMsg.nErrCode = MRS_ERRORCODE_SUCCESS;

	pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.log"), TEXT("Msg:[%s] [%s]"), TEXT("GMTMessageReq_K_GOONZU"), kRecvMsg.strMessage.c_str() );

	TCHAR msgtext[1024];
	StringCchCopy(msgtext, 1024, kRecvMsg.strMessage.c_str() );

	// ��ü ����
	pclserver->SendNoticeMsg(-1, 0, 0, msgtext);

	XNoti::Connector::SendAnswerMessage(pContext, kSendMsg);

	//----------------------------------------------------------------
	// ������ ������ ��
	//----------------------------------------------------------------
#endif // _SERVER
	//----------------------------------------------------------------

	return true;
}

bool __stdcall cltServer::HanXNoti_DoMsg_GMTKickReq_K_GOONZU(XStream::Handle stream, void* pAdditionalData, void* pContext)
{
	//----------------------------------------------------------------
	// ������ ������ ��
	//----------------------------------------------------------------
#ifdef _SERVER
	//----------------------------------------------------------------

	if(pclClient->GameMode == GAMEMODE_CLIENT)		return false;

	cltServer* pclserver = (cltServer*)pclClient;
	if(pclserver->pclGameDBProcess == NULL)			return false;

	GMTKickReq_K_GOONZU	kRecvMsg;
	kRecvMsg.Load(stream);

	GMTKickAns_K_GOONZU	kSendMsg;
	kSendMsg.nIdx = kRecvMsg.nIdx;
	kSendMsg.nErrCode = MRS_ERRORCODE_SUCCESS;

	pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.log"), TEXT("Msg:[%s] [%s]"), TEXT("GMTKickReq_K_GOONZU"), kRecvMsg.strPlayerName.c_str());

	SI32 id;
	id = pclClient->pclCM->GetIDFromName((TCHAR*)kRecvMsg.strPlayerName.c_str());

	if(id > 0)
	{
		cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[id];

#ifdef USE_GAME_GUARD_SERVER
		pclchar->CCSAuthClose();
#endif
		if(pclchar->GetSession())
		{
			pclchar->GetSession()->CloseSocket();
		}
	}
	else
	{
		kSendMsg.nErrCode = MRS_ERRORCODE_INVALID_CHARNAME;
	}

	XNoti::Connector::SendAnswerMessage(pContext, kSendMsg);

	//----------------------------------------------------------------
	// ������ ������ ��
	//----------------------------------------------------------------
#endif // _SERVER
	//----------------------------------------------------------------

	return true;
}

bool __stdcall cltServer::HanXNoti_DoMsg_GMTChatBlockReq_K_GOONZU(XStream::Handle stream, void* pAdditionalData, void* pContext)
{
	//----------------------------------------------------------------
	// ������ ������ ��
	//----------------------------------------------------------------
#ifdef _SERVER
	//----------------------------------------------------------------

	if(pclClient->GameMode == GAMEMODE_CLIENT)		return false;

	cltServer* pclserver = (cltServer*)pclClient;
	if(pclserver->pclGameDBProcess == NULL)			return false;

	GMTChatBlockReq_K_GOONZU	kRecvMsg;
	kRecvMsg.Load(stream);

	GMTChatBlockAns_K_GOONZU	kSendMsg;
	kSendMsg.nIdx = kRecvMsg.nIdx;
	// �⺻������ -1 �� ó��
	kSendMsg.nErrCode = MRS_ERRORCODE_FAILED;

	pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.log"), TEXT("Msg:[%s] [%s]"), TEXT("GMTChatBlockReq_K_GOONZU"), kRecvMsg.strPlayerName );

	XNoti::Connector::SendAnswerMessage(pContext, kSendMsg);

	//----------------------------------------------------------------
	// ������ ������ ��
	//----------------------------------------------------------------
#endif // _SERVER
	//----------------------------------------------------------------

	return true;
}

bool __stdcall cltServer::HanXNoti_DoMsg_GMTCmdReq_K_GOONZU(XStream::Handle stream, void* pAdditionalData, void* pContext)
{
	//----------------------------------------------------------------
	// ������ ������ ��
	//----------------------------------------------------------------
#ifdef _SERVER
	//----------------------------------------------------------------

	if(pclClient->GameMode == GAMEMODE_CLIENT)		return false;

	cltServer* pclserver = (cltServer*)pclClient;
	if(pclserver->pclGameDBProcess == NULL)			return false;

	GMTCmdReq_K_GOONZU	kRecvMsg;
	kRecvMsg.Load(stream);

	GMTCmdAns_K_GOONZU	kSendMsg;
	kSendMsg.nIdx = kRecvMsg.nIdx;
	// �⺻������ MRS_ERRORCODE_INVALID_COMMAND �� ó��
	kSendMsg.nErrCode = MRS_ERRORCODE_INVALID_COMMAND;

	TCHAR	szFullCmd[1024];
	TCHAR	szCmd[64];
	TCHAR*	pToken;

	StringCchCopy(szFullCmd, sizeof(szFullCmd), kRecvMsg.strCmd.c_str());
	pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.log"), TEXT("Msg:[%s] [%s]"), TEXT("GMTCmdReq_K_GOONZU"), szFullCmd );

	pToken = _tcstok(szFullCmd, "|");
	if(pToken)
	{
		StringCchCopy(szCmd, sizeof(szCmd), pToken);

		if( _tcscmp(szCmd, "ci") == 0)
		{
			kSendMsg.nErrCode = MRS_ERRORCODE_SUCCESS;

			TCHAR*	pCharName;
			TCHAR*	pItemName;
			TCHAR*	pCount;

			pCharName = _tcstok(NULL, "|");
			pItemName = _tcstok(NULL, "|");
			pCount = _tcstok(NULL, "|");

			if(pCharName && pItemName && pCount)
			{
				SI32 id = pclClient->pclCM->GetIDFromName(pCharName);
				cltCharServer* pclchar = NULL;
				if(id > 0)				{		pclchar = (cltCharServer*)pclClient->pclCM->CR[id];				}
				if(pclchar == NULL)		{		kSendMsg.nErrCode = MRS_ERRORCODE_INVALID_CHARNAME;				}

				SI32 itemunique = pclClient->pclItemManager->FindUniqueFromName(pItemName);
				if(itemunique <= 0)		{		kSendMsg.nErrCode = MRS_ERRORCODE_INVALID_ITEMNAME;				}

				SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique(itemunique);
				if (ref <= 0)			{		kSendMsg.nErrCode = MRS_ERRORCODE_INVALID_ITEMNAME;				}

				SI32 num = 0;
				num = atoi(pCount);
				if(num <= 0)			{		kSendMsg.nErrCode = MRS_ERRORCODE_INVALID_ITEMCOUNT;			}

				if(kSendMsg.nErrCode == MRS_ERRORCODE_SUCCESS)
				{
					UI16 usedate = pclClient->pclItemManager->pclItemInfo[ref]->clItem.uiDateUseDay;
					pclClient->pclCM->GiveItem(id, itemunique, num, GIVEITEM_MODE_PERSON, INPUTITEMPERSON_OPTION_MASTER, usedate, pclchar->GetID() );
				}
			}
			else
			{
				kSendMsg.nErrCode = MRS_ERRORCODE_INVALID_PARAMETER;
			}
		}
	}

	XNoti::Connector::SendAnswerMessage(pContext, kSendMsg);

	//--------------------------------endAnsw--------------------------------
	// ������ ������ ��
	//----------------------------------------------------------------
#endif // _SERVER
	//----------------------------------------------------------------

	return true;
}

bool __stdcall cltServer::HanXNoti_DoMsg_GameCharacterListReq(XStream::Handle stream, void* pAdditionalData, void* pContext)
{
	//----------------------------------------------------------------
	// ������ ������ ��
	//----------------------------------------------------------------
#ifdef _SERVER
	//----------------------------------------------------------------

	if(pclClient->GameMode == GAMEMODE_CLIENT)		return false;

	cltServer* pclserver = (cltServer*)pclClient;
	if(pclserver->pclGameDBProcess == NULL)			return false;

	GameCharacterListReq	kRecvMsg;
	kRecvMsg.Load(stream);

	GameCharacterListAns	kSendMsg;
	kSendMsg.nIdx	= kRecvMsg.nIdx;

	if(pclserver->dwDBLatency > 2000)
	{
		// ���� ó�� - DB ���� �ִ�.
		XNoti::Connector::SendAnswerMessage(pContext, kSendMsg);
		pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.log"), TEXT("Msg:[%s] [DBLatency Too High]"), TEXT("AddInventoryItemReq") );
		return true;
	}

	//----------------------------------------------------------------
	// ������ ��û�Ѵ�.
	//----------------------------------------------------------------	
	SI32 siArrayIndex = pclserver->HanXNoti_GetEmptyWaiting(kRecvMsg.nIdx);
	if(siArrayIndex < 0)
	{
		// ���� ó�� - �� �̻� �޽����� ó���� �� �����ϴ�.
		XNoti::Connector::SendAnswerMessage(pContext, kSendMsg);
		pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.log"), TEXT("Msg:[%s] [Not Empty]"), TEXT("GameCharacterListReq") );
		return true;
	}

	pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.log"), TEXT("Msg:[%s] [siArrayIndex:%d] [Idx:%d] [memberid:%s] [serverid:%s] [characterId:%s]"), TEXT("GameCharacterListReq"), siArrayIndex, kRecvMsg.nIdx, kRecvMsg.memberid.c_str(), kRecvMsg.serverid.c_str(), kRecvMsg.characterId.c_str() );

	if(kRecvMsg.memberid.length() > 0)
	{
		// DB�� ĳ���� ����Ʈ�� ��û
		sDBRequest_AccountInfoForHanXNoti clMsg( siArrayIndex, kRecvMsg.nIdx, (TCHAR*)kRecvMsg.serverid.c_str(), (TCHAR*)kRecvMsg.memberid.c_str() );
		pclserver->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
		pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.log"), TEXT("Msg:[%s] [siArrayIndex:%d] [Request:%s]"), TEXT("GameCharacterListReq"), siArrayIndex, TEXT("sDBRequest_AccountInfoForHanXNoti") );
	}
	else
	{
		sDBRequest_CharInfoForHanXNoti clMsg( siArrayIndex, kRecvMsg.nIdx, (TCHAR*)kRecvMsg.serverid.c_str(), (TCHAR*)kRecvMsg.characterId.c_str() );
		pclserver->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
		pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.log"), TEXT("Msg:[%s] [siArrayIndex:%d] [Request:%s]"), TEXT("GameCharacterListReq"), siArrayIndex, TEXT("sDBRequest_CharInfoForHanXNoti") );
	}

	//----------------------------------------------------------------
	// ��ȣ�� ���⸦ ��ٸ���. : �ִ� 5�ʰ� ��ٸ���.
	//----------------------------------------------------------------	
	DWORD dwWait = WaitForSingleObject(pclserver->m_kHanXNoti_Waitings[siArrayIndex].m_hWaitingHandle, 5 * 1000);
	if(dwWait == WAIT_OBJECT_0)
	{
		// ��ȣ�� �Դ�.
		if(pclserver->m_pkHanXNoti_AnsMessages[siArrayIndex] != NULL)
		{
			if(pclserver->m_pkHanXNoti_AnsMessages[siArrayIndex]->GetID() == GameCharacterListAns::tagMsgID)
			{
				// ����ó��
				GameCharacterListAns*	pkSendMsg = (GameCharacterListAns*)pclserver->m_pkHanXNoti_AnsMessages[siArrayIndex];
				XNoti::Connector::SendAnswerMessage(pContext, *pkSendMsg);
				pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.log"), TEXT("Msg:[%s] [Send Result]"), TEXT("GameCharacterListAns") );
			}
			else
			{
				// �߸��� �޽����� �޾Ҵ�.
				XNoti::Connector::SendAnswerMessage(pContext, kSendMsg);
				pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.log"), TEXT("Msg:[%s] [Wrong Message]"), TEXT("GameCharacterListAns") );
			}
		}
		else
		{
			// ����
			XNoti::Connector::SendAnswerMessage(pContext, kSendMsg);
			pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.log"), TEXT("Msg:[%s] [Wrong Message]"), TEXT("GameCharacterListAns") );
		}
	}
	else if(dwWait == WAIT_TIMEOUT)
	{
		// Ÿ�� �ƿ�
		XNoti::Connector::SendAnswerMessage(pContext, kSendMsg);
		pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.log"), TEXT("Msg:[%s] [Time Out]"), TEXT("GameCharacterListAns") );
	}
	else
	{
		// ����
		XNoti::Connector::SendAnswerMessage(pContext, kSendMsg);
		pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.log"), TEXT("Msg:[%s] [System Error]"), TEXT("GameCharacterListAns") );
	}

	// ���� �޽��� ó���� ���� Ŭ����� ������ �����Ѵ�.
	pclserver->HanXNoti_ClearWaiting(siArrayIndex);

	pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.log"), TEXT("<END> Msg:[%s] [siArrayIndex:%d] [Idx:%d]"), TEXT("GameCharacterListAns"), siArrayIndex, kSendMsg.nIdx );

	//----------------------------------------------------------------
	// ������ ������ ��
	//----------------------------------------------------------------
#endif // _SERVER
	//----------------------------------------------------------------

	return true;
}

bool __stdcall cltServer::HanXNoti_DoMsg_AddInventoryItemReq(XStream::Handle stream, void* pAdditionalData, void* pContext)
{
	//----------------------------------------------------------------
	// ������ ������ ��
	//----------------------------------------------------------------
#ifdef _SERVER
	//----------------------------------------------------------------

	if(pclClient->GameMode == GAMEMODE_CLIENT)		return false;

	cltServer* pclserver = (cltServer*)pclClient;
	if(pclserver->pclGameDBProcess == NULL)			return false;
	
	AddInventoryItemReq	kRecvMsg;
	kRecvMsg.Load(stream);

	AddInventoryItemAns	kSendMsg;
	kSendMsg.nIdx	= kRecvMsg.nIdx;
	kSendMsg.result = MRS_ERRORCODE_ADDINVENTORYITEMREQ_FAILED;

	if(pclserver->dwDBLatency > 2000)
	{
		// ���� ó�� - DB ���� �ִ�.
		XNoti::Connector::SendAnswerMessage(pContext, kSendMsg);
		pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.log"), TEXT("Msg:[%s] [DBLatency Too High]"), TEXT("AddInventoryItemReq") );
		return true;
	}

	//----------------------------------------------------------------
	// ������ ��û�Ѵ�.
	//----------------------------------------------------------------	
	SI32 siArrayIndex = pclserver->HanXNoti_GetEmptyWaiting(kRecvMsg.nIdx);
	if(siArrayIndex < 0)
	{
		// ���� ó�� - �� �̻� �޽����� ó���� �� �����ϴ�.
		//kSendMsg.result = MRS_ERRORCODE_SYSTEM_MSGFULL;
		XNoti::Connector::SendAnswerMessage(pContext, kSendMsg);
		pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.log"), TEXT("Msg:[%s] [Not Empty]"), TEXT("AddInventoryItemReq") );
		return true;
	}

	BOOL bBuy = FALSE;

	if(kRecvMsg.sendmemberid.length() <= 0)					bBuy = TRUE;
	if(kRecvMsg.sendmemberid == kRecvMsg.memberid)			bBuy = TRUE;

	if(	bBuy == FALSE)
	{
		TCHAR	szTxCode[50];
		wsprintf(szTxCode, "%d", kRecvMsg.orderseq);

		SI32	siProductKey;
		siProductKey = atoi(kRecvMsg.itemId.c_str());

		
		// �����ϱ�
		sDBRequest_ItemMall_Giftitem_ForXNoti clMsg( siArrayIndex, kRecvMsg.nIdx, siProductKey, (TCHAR*)kRecvMsg.sendmemberid.c_str(), (TCHAR*)kRecvMsg.memberid.c_str(), kRecvMsg.count, (SI32)kRecvMsg.price, (TCHAR*)kRecvMsg.giftMessage.c_str(), szTxCode, (TCHAR*)kRecvMsg.characterId.c_str(), (TCHAR*)kRecvMsg.sendcharacterId.c_str());
		pclserver->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);



		pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.log")	, TEXT("Msg:[%s] [siArrayIndex:%d] [Idx:%d] [sendmemberid:%s] [sendserverid:%s] [sendcharacterId:%s] [memberid:%s] [serverid:%s] [characterId:%s] [itemid:%s]"), TEXT("sDBRequest_ItemMall_Giftitem_ForXNoti"), siArrayIndex, kRecvMsg.nIdx, kRecvMsg.sendmemberid.c_str(), kRecvMsg.sendserverid.c_str(), kRecvMsg.sendcharacterId.c_str(), kRecvMsg.memberid.c_str(), kRecvMsg.serverid.c_str(), kRecvMsg.characterId.c_str(), kRecvMsg.itemId.c_str() );

		//----------------------------------------------------------------
		// ��ȣ�� ���⸦ ��ٸ���. : �ִ� 5�ʰ� ��ٸ���.
		//----------------------------------------------------------------	
		DWORD dwWait = WaitForSingleObject(pclserver->m_kHanXNoti_Waitings[siArrayIndex].m_hWaitingHandle, 5 * 1000);
		if(dwWait == WAIT_OBJECT_0)
		{
			// ��ȣ�� �Դ�.
			if(pclserver->m_pkHanXNoti_AnsMessages[siArrayIndex] != NULL)
			{
				if(pclserver->m_pkHanXNoti_AnsMessages[siArrayIndex]->GetID() == AddInventoryItemAns::tagMsgID)
				{
					kSendMsg.result = MRS_ERRORCODE_SUCCESS;

					// ����ó��
					AddInventoryItemAns*	pkSendMsg = (AddInventoryItemAns*)pclserver->m_pkHanXNoti_AnsMessages[siArrayIndex];
					XNoti::Connector::SendAnswerMessage(pContext, *pkSendMsg);
					pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.log"), TEXT("Msg:[%s] [Send Result]"), TEXT("AddInventoryItemAns") );
				}
				else
				{
					// �߸��� �޽����� �޾Ҵ�.
					//kSendMsg.result = MRS_ERRORCODE_SYSTEM_ERROR;
					XNoti::Connector::SendAnswerMessage(pContext, kSendMsg);
					pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.log"), TEXT("Msg:[%s] [Wrong Message]"), TEXT("AddInventoryItemAns") );
				}
			}
			else
			{
				// ����
				XNoti::Connector::SendAnswerMessage(pContext, kSendMsg);
				pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.log"), TEXT("Msg:[%s] [Wrong Message]"), TEXT("AddInventoryItemAns") );
			}
		}
		else if(dwWait == WAIT_TIMEOUT)
		{
			// Ÿ�� �ƿ�
			//kSendMsg.result = MRS_ERRORCODE_SYSTEM_TIMEOUT;
			XNoti::Connector::SendAnswerMessage(pContext, kSendMsg);
			pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.log"), TEXT("Msg:[%s] [Time Out]"), TEXT("AddInventoryItemAns") );
		}
		else
		{
			// ����
			//kSendMsg.result = MRS_ERRORCODE_SYSTEM_ERROR;
			XNoti::Connector::SendAnswerMessage(pContext, kSendMsg);
			pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.log"), TEXT("Msg:[%s] [System Error]"), TEXT("AddInventoryItemAns") );
		}

		// ���� �޽��� ó���� ���� Ŭ����� ������ �����Ѵ�.
		pclserver->HanXNoti_ClearWaiting(siArrayIndex);

		pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.log"), TEXT("<END> Msg:[%s] [siArrayIndex:%d] [Idx:%d] [result:%d]"), TEXT("AddInventoryItemAns"), siArrayIndex, kSendMsg.nIdx, kSendMsg.result );
	}
	else
	{
		TCHAR	szTxCode[50];
		wsprintf(szTxCode, "%d", kRecvMsg.orderseq);

		SI32	siProductKey;
		siProductKey = atoi(kRecvMsg.itemId.c_str());

		// �����ϱ�
		sDBRequest_ItemMall_Buyitem_ForXNoti clMsg( siArrayIndex, kRecvMsg.nIdx, (TCHAR*)kRecvMsg.memberid.c_str(), (TCHAR*)kRecvMsg.characterId.c_str(), siProductKey, kRecvMsg.count, (SI32)kRecvMsg.price, szTxCode, pclClient->siServiceArea);
		pclserver->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

		pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.log"), TEXT("Msg:[%s] [siArrayIndex:%d] [Idx:%d] [memberid:%s] [serverid:%s] [characterId:%s] [itemid:%s] [count:%d]"), TEXT("sDBRequest_ItemMall_Buyitem_ForXNoti"), siArrayIndex, kRecvMsg.nIdx, (TCHAR*)kRecvMsg.memberid.c_str(), (TCHAR*)kRecvMsg.serverid.c_str(), (TCHAR*)kRecvMsg.characterId.c_str(), (TCHAR*)kRecvMsg.itemId.c_str(), kRecvMsg.count );

		//----------------------------------------------------------------
		// ��ȣ�� ���⸦ ��ٸ���. : �ִ� 5�ʰ� ��ٸ���.
		//----------------------------------------------------------------	
		DWORD dwWait = WaitForSingleObject(pclserver->m_kHanXNoti_Waitings[siArrayIndex].m_hWaitingHandle, 5 * 1000);
		if(dwWait == WAIT_OBJECT_0)
		{
			// ��ȣ�� �Դ�.
			if(pclserver->m_pkHanXNoti_AnsMessages[siArrayIndex] != NULL)
			{
				if(pclserver->m_pkHanXNoti_AnsMessages[siArrayIndex]->GetID() == AddInventoryItemAns::tagMsgID)
				{
					kSendMsg.result = MRS_ERRORCODE_SUCCESS;

					// ����ó��
					AddInventoryItemAns*	pkSendMsg = (AddInventoryItemAns*)pclserver->m_pkHanXNoti_AnsMessages[siArrayIndex];
					XNoti::Connector::SendAnswerMessage(pContext, *pkSendMsg);
					pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.log"), TEXT("Msg:[%s] [Send Result]"), TEXT("AddInventoryItemAns") );
				}
				else
				{
					// �߸��� �޽����� �޾Ҵ�.
					kSendMsg.result = MRS_ERRORCODE_SYSTEM_ERROR;
					XNoti::Connector::SendAnswerMessage(pContext, kSendMsg);
					pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.log"), TEXT("Msg:[%s] [Wrong Message]"), TEXT("AddInventoryItemAns") );
				}
			}
		}
		else if(dwWait == WAIT_TIMEOUT)
		{
			// Ÿ�� �ƿ�
			kSendMsg.result = MRS_ERRORCODE_SYSTEM_TIMEOUT;
			XNoti::Connector::SendAnswerMessage(pContext, kSendMsg);
			pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.log"), TEXT("Msg:[%s] [TimeOut]"), TEXT("AddInventoryItemAns") );
		}
		else
		{
			// ����
			kSendMsg.result = MRS_ERRORCODE_SYSTEM_ERROR;
			XNoti::Connector::SendAnswerMessage(pContext, kSendMsg);
			pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.log"), TEXT("Msg:[%s] [System Error]"), TEXT("AddInventoryItemAns") );
		}

		// ���� �޽��� ó���� ���� Ŭ����� ������ �����Ѵ�.
		pclserver->HanXNoti_ClearWaiting(siArrayIndex);

		pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.log"), TEXT("<END> Msg:[%s] [siArrayIndex:%d] [Idx:%d] [result:%d]"), TEXT("AddInventoryItemAns"), siArrayIndex, kSendMsg.nIdx, kSendMsg.result );
	}

	//----------------------------------------------------------------
	// ������ ������ ��
	//----------------------------------------------------------------
#endif // _SERVER
	//----------------------------------------------------------------

	return true;
}


bool __stdcall cltServer::HanXNoti_DoMsg_DeleteInventoryReq(XStream::Handle stream, void* pAdditionalData, void* pContext)
{
	//----------------------------------------------------------------
	// ������ ������ ��
	//----------------------------------------------------------------
#ifdef _SERVER
	//----------------------------------------------------------------

	if(pclClient->GameMode == GAMEMODE_CLIENT)		return false;

	cltServer* pclserver = (cltServer*)pclClient;
	if(pclserver->pclGameDBProcess == NULL)			return false;

	DeleteInventoryReq	kRecvMsg;
	kRecvMsg.Load(stream);

	DeleteInventoryAns	kSendMsg;
	kSendMsg.nIdx	= kRecvMsg.nIdx;
	kSendMsg.result = MRS_ERRORCODE_DELETEINVENTORYREQ_FAILED;

	if(pclserver->dwDBLatency > 2000)
	{
		// ���� ó�� - DB ���� �ִ�.
		XNoti::Connector::SendAnswerMessage(pContext, kSendMsg);
		pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.log"), TEXT("Msg:[%s] [DBLatency Too High]"), TEXT("DeleteInventoryReq") );
		return true;
	}

	//----------------------------------------------------------------
	// ������ ��û�Ѵ�.
	//----------------------------------------------------------------	
	SI32 siArrayIndex = pclserver->HanXNoti_GetEmptyWaiting(kRecvMsg.nIdx);
	if(siArrayIndex < 0)
	{
		// ���� ó�� - �� �̻� �޽����� ó���� �� �����ϴ�.
		XNoti::Connector::SendAnswerMessage(pContext, kSendMsg);
		pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.log"), TEXT("Msg:[%s] [Not Empty]"), TEXT("DeleteInventoryReq") );
		return true;
	}

	TCHAR	szTxCode[50];
	wsprintf(szTxCode, "%d", kRecvMsg.orderseq);

	SI32	siProductKey;
	siProductKey = atoi(kRecvMsg.itemId.c_str());

	// ������ ���
	sDBRequest_ItemMall_CancelOrder_XNoti clMsg( szTxCode );
	pclserver->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

	pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.log")	, TEXT("Msg:[%s] [siArrayIndex:%d] [Idx:%d] [memberid:%s] [serverid:%s] [characterId:%s] [itemid:%s] [TxCode:%s]"), TEXT("sDBRequest_ItemMall_CancelOrder_XNoti"), siArrayIndex, kRecvMsg.nIdx, kRecvMsg.memberid.c_str(), kRecvMsg.serverid.c_str(), kRecvMsg.characterId.c_str(), kRecvMsg.itemId.c_str(), szTxCode );

	// ����ó��
	kSendMsg.result = MRS_ERRORCODE_SUCCESS;
	XNoti::Connector::SendAnswerMessage(pContext, kSendMsg);
	pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.log"), TEXT("Msg:[%s] [Send Result]"), TEXT("DeleteInventoryReq") );

	//======================================
	// DB���� ������ ���� �ʴ´�.
	//======================================
	/*
	//----------------------------------------------------------------
	// ��ȣ�� ���⸦ ��ٸ���. : �ִ� 5�ʰ� ��ٸ���.
	//----------------------------------------------------------------	
	DWORD dwWait = WaitForSingleObject(pclserver->m_kHanXNoti_Waitings[siArrayIndex].m_hWaitingHandle, 5 * 1000);
	if(dwWait == WAIT_OBJECT_0)
	{
	// ��ȣ�� �Դ�.
	if(pclserver->m_pkHanXNoti_AnsMessages[siArrayIndex] != NULL)
	{
	if(pclserver->m_pkHanXNoti_AnsMessages[siArrayIndex]->GetID() == DeleteInventoryAns::tagMsgID)
	{
	kSendMsg.result = MRS_ERRORCODE_SUCCESS;

	// ����ó��
	DeleteInventoryAns*	pkSendMsg = (DeleteInventoryAns*)pclserver->m_pkHanXNoti_AnsMessages[siArrayIndex];
	XNoti::Connector::SendAnswerMessage(pContext, *pkSendMsg);
	pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.txt"), TEXT("Msg:[%s] [Send Result]"), TEXT("DeleteInventoryReq") );
	}
	else
	{
	// �߸��� �޽����� �޾Ҵ�.
	XNoti::Connector::SendAnswerMessage(pContext, kSendMsg);
	pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.txt"), TEXT("Msg:[%s] [Wrong Message]"), TEXT("DeleteInventoryReq") );
	}
	}
	else
	{
	// ����
	XNoti::Connector::SendAnswerMessage(pContext, kSendMsg);
	pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.txt"), TEXT("Msg:[%s] [Wrong Message]"), TEXT("DeleteInventoryReq") );
	}
	}
	else if(dwWait == WAIT_TIMEOUT)
	{
	// Ÿ�� �ƿ�
	XNoti::Connector::SendAnswerMessage(pContext, kSendMsg);
	pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.txt"), TEXT("Msg:[%s] [Time Out]"), TEXT("DeleteInventoryReq") );
	}
	else
	{
	// ����
	XNoti::Connector::SendAnswerMessage(pContext, kSendMsg);
	pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.txt"), TEXT("Msg:[%s] [System Error]"), TEXT("DeleteInventoryReq") );
	}
	*/

	// ���� �޽��� ó���� ���� Ŭ����� ������ �����Ѵ�.
	pclserver->HanXNoti_ClearWaiting(siArrayIndex);

	pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.log"), TEXT("<END> Msg:[%s] [siArrayIndex:%d] [Idx:%d] [result:%d]"), TEXT("DeleteInventoryReq"), siArrayIndex, kSendMsg.nIdx, kSendMsg.result );

	//----------------------------------------------------------------
	// ������ ������ ��
	//----------------------------------------------------------------
#endif // _SERVER
	//----------------------------------------------------------------

	return true;
}


// -HanAuth_Lib
//#endif // _SERVER
#endif // USE_HANXNOTI
// -HanAuth_Lib
