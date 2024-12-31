//---------------------------------
// 2006/3/14/�迵��   
//---------------------------------

#include "Char\CharManager\CharManager.h"

#include "..\Server\Server.h"

#include "..\Common\Map\Map.h"

#include "MsgType-System.h"
#include "../../NBillServer/NBillMsg.h"
#include "../CommonLogic/msg/MsgType-ItemMall.h"

//#include "../../Server/AuthServer/AuthMsg.h"
//#include "..\..\DBManager\GameDBManager_World\DBMsg-Person.h"

void cltServer::DoMsg_BILLMSG_RESPONSE_ENCRYPTIDPW(sPacketHeader* pPacket)
{
	NBillResponse_EncryptIDPW * pclMsg = (NBillResponse_EncryptIDPW*)pPacket;
	

	if ( pclMsg->m_personid <= 0 ) return ;	

	SI32 id = pclCM->GetIDFromPersonID(pclMsg->m_personid);
	if ( pclCM->IsValidID(id) == false ) return ;
	if ( id != pclMsg->m_charid ) return ;
	
	//cltCharServer *pclChar = (cltCharServer *)pclCM->CR[id];

	// Ŭ���̾�Ʈ �������� �α��ε� �� ���������� �ּҸ� ������ �ش�.
	
	cltGameMsgResponse_BillPage_URL	clinfo( pclMsg->m_ret );
	cltMsg clMsg(GAMEMSG_RESPONSE_BILLPAGE_URL,sizeof(clinfo),(BYTE*)&clinfo);
	pclCM->CR[ id ]->SendNetMsg((sPacketHeader*)&clMsg);

}

void cltServer::DoMsg_BILLMSG_RESPONSE_ENCRYPTIDPW_WEB(sPacketHeader* pPacket)
{
	NBillResponse_EncryptIDPW_Web * pclMsg = (NBillResponse_EncryptIDPW_Web*)pPacket;

	if ( pclMsg->m_personid <= 0 ) return ;	

	SI32 id = pclCM->GetIDFromPersonID(pclMsg->m_personid);
	if ( pclCM->IsValidID(id) == false ) return ;
	if ( id != pclMsg->m_charid ) return ;

	//cltCharServer *pclChar = (cltCharServer *)pclCM->CR[id];

	// Ŭ���̾�Ʈ �������� �α��ε� �� ���������� �ּҸ� ������ �ش�.

	cltGameMsgResponse_LoginPage_URL	clinfo( pclMsg->m_ret, pclMsg->m_szUrl );
	cltMsg clMsg(GAMEMSG_RESPONSE_LOGINPAGE_URL,sizeof(clinfo),(BYTE*)&clinfo);
	pclCM->CR[ id ]->SendNetMsg((sPacketHeader*)&clMsg);

}


void cltServer::DoMsg_BILLMSG_RESPONSE_ENCRYPTIDPW_GACHA(sPacketHeader* pPacket)
{
	NBillResponse_EncryptIDPW_Gacha * pclMsg = (NBillResponse_EncryptIDPW_Gacha*)pPacket;

	if ( pclMsg->m_personid <= 0 ) return ;	

	SI32 id = pclCM->GetIDFromPersonID(pclMsg->m_personid);
	if ( pclCM->IsValidID(id) == false ) return ;
	if ( id != pclMsg->m_charid ) return ;

	//cltCharServer *pclChar = (cltCharServer *)pclCM->CR[id];

	// Ŭ���̾�Ʈ �������� �α��ε�  ���������� �ּҸ� ������ �ش�.

	cltGameMsgResponse_GachaPage_URL	clinfo( pclMsg->m_ret );
	cltMsg clMsg(GAMEMSG_RESPONSE_GACHAPAGE_URL,sizeof(clinfo),(BYTE*)&clinfo);
	pclCM->CR[ id ]->SendNetMsg((sPacketHeader*)&clMsg);

}