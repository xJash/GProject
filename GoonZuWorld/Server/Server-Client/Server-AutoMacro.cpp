
#include "Char\CharManager\CharManager.h"
#include "..\Server\Server.h"

#include "..\..\..\DBManager\GameDBManager_World\DBMsg.h"

#include "MsgRval-Define.h"

#include "Msg/MsgType-AutoMacro.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-AutoMacro.h"

//[�߰� : Ȳ���� 2007. 12. 5 �������α׷��� �۵����̶�� �޽����� ������ �޾� ó���ϴ�. C->S]
void cltServer::DoMsg_GAMEMSG_REQUEST_AUTOMACRO_ON( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_AutoMacroOn*	pclInfo = (cltGameMsgRequest_AutoMacroOn*)pclMsg->cData;

	
	sDBRequest_AutoMacro cltMsg(id, pclInfo->m_siType, pclInfo->m_siPersonID, pclInfo->szAutoProcessName, pclInfo->szIP);
	SendDBMsg(DBSELECT_BASE, (sPacketHeader*)&cltMsg);
}