#include "./CGrandMabriumBattleRoyalStadium.h"

CGrandMabriumBattleRoyalStadiumServer::CGrandMabriumBattleRoyalStadiumServer()
{
	m_siMapIndex = MAPINDEX_BATTLEROYAL_GRANDMABRIUM;
	
	m_siKindBlackarmySword = pclClient->GetUniqueFromHash("KIND_BattleRoyalSword2");
	m_siKindBlackarmyRifle = pclClient->GetUniqueFromHash("KIND_BattleRoyalRifle2");
	m_siKindBlackarmyKatar = pclClient->GetUniqueFromHash("KIND_BattleRoyalKatar2");
}
CGrandMabriumBattleRoyalStadiumServer::~CGrandMabriumBattleRoyalStadiumServer()
{

}

// ��Ʋ�ξ� ��⸦ �˸���.
BOOL	CGrandMabriumBattleRoyalStadiumServer::NoticeWait()
{
	return TRUE; 
}

// ������� ������ �˸���.
BOOL	CGrandMabriumBattleRoyalStadiumServer::NoticeOpen()
{
	return TRUE; 
}

void	CGrandMabriumBattleRoyalStadiumServer::OpenGate()
{
	CBattleRoyalStadium::OpenGate();
}

//======================================================================================================================

CGrandMabriumBattleRoyalStadiumClient::CGrandMabriumBattleRoyalStadiumClient()
{
	m_siMapIndex = MAPINDEX_BATTLEROYAL_GRANDMABRIUM;

	m_siKindBlackarmySword = pclClient->GetUniqueFromHash("KIND_BattleRoyalSword2");
	m_siKindBlackarmyRifle = pclClient->GetUniqueFromHash("KIND_BattleRoyalRifle2");
	m_siKindBlackarmyKatar = pclClient->GetUniqueFromHash("KIND_BattleRoyalKatar2");
}
CGrandMabriumBattleRoyalStadiumClient::~CGrandMabriumBattleRoyalStadiumClient()
{

}