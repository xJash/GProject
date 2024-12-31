#include "./CMabriumBattleRoyalStadium.h"
#include "../MsgType.h"
#include "../../Server/Server.h"

CMabriumBattleRoyalStadiumServer::CMabriumBattleRoyalStadiumServer()
{
	m_siMapIndex = MAPINDEX_BATTLEROYAL_MABRIUM;

	m_siKindBlackarmySword = pclClient->GetUniqueFromHash("KIND_BattleRoyalSword");
	m_siKindBlackarmyRifle = pclClient->GetUniqueFromHash("KIND_BattleRoyalRifle");
	m_siKindBlackarmyKatar = pclClient->GetUniqueFromHash("KIND_BattleRoyalKatar");
}
CMabriumBattleRoyalStadiumServer::~CMabriumBattleRoyalStadiumServer()
{
	
}

// ��Ʋ�ξ� ��⸦ �˸���.
BOOL	CMabriumBattleRoyalStadiumServer::NoticeWait()
{
	return Notice(GetTxtFromMgr(30400)); 
}

// ������� ������ �˸���.
BOOL	CMabriumBattleRoyalStadiumServer::NoticeOpen()
{
	return Notice(GetTxtFromMgr(30399)); 
}

// ����� �Ա��� ����.
void	CMabriumBattleRoyalStadiumServer::OpenGate()
{
	CBattleRoyalStadium::OpenGate();

	//cltMsg clMassage(GAMEMSG_RESPONSE_BATTLEROYAL_OPENSTADIUM, 0 );
	//m_pclServer->pclCM->SendAllPersonMsg((sPacketHeader*)&clMassage);
}

//======================================================================================================================

CMabriumBattleRoyalStadiumClient::CMabriumBattleRoyalStadiumClient()
{
	m_siMapIndex = MAPINDEX_BATTLEROYAL_MABRIUM;

	m_siKindBlackarmySword = pclClient->GetUniqueFromHash("KIND_BattleRoyalSword");
	m_siKindBlackarmyRifle = pclClient->GetUniqueFromHash("KIND_BattleRoyalRifle");
	m_siKindBlackarmyKatar = pclClient->GetUniqueFromHash("KIND_BattleRoyalKatar");
}
CMabriumBattleRoyalStadiumClient::~CMabriumBattleRoyalStadiumClient()
{

}