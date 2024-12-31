#include "./CBattleRoyalFactory.h"
#include "./CMabriumBattleRoyal.h"
#include "./CGrandMabriumBattleRoyal.h"

// ��Ʋ�ξ� ����
CBattleRoyal*	CBattleRoyalFactory::CreateBattleRoyal(SI32 siKind)
{
	switch(siKind)
	{
	case MABRIUM:
		{
			return new CMabriumBattleRoyal();
		}
	case GRANDMABRIUM:
		{
			return new CGrandMabriumBattleRoyal();
		}
	}
	return NULL; 
}

// ��Ʋ�ξ� ����
BOOL	CBattleRoyalFactory::DestroyBattleRoyal(CBattleRoyal* pclBattleRoyal)
{
	if( NULL == pclBattleRoyal)
		return FALSE;

	delete pclBattleRoyal;
	return TRUE;
}