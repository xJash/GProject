//---------------------------------
// 2004/9/1 ���°�
//---------------------------------
#include "..\..\Server\Server.h"

//-----------------------------
// Common
//-----------------------------
#include "PersonInfo.h"


extern cltCommonLogic* pclClient;

// ������ ������. 
bool cltCharServer::SendPrison()
{

	// ������ �־�� �� ���� �ð��� �־�� �������� ���� �� �ִ�. 
	if(pclCI->clGuiltyInfo.siLeftPrisonSecond <= 0)return false;

	clInnerStatus.SetStatus(INNERSTATUS_PRISON);

	// ���� ��ġ�� ���� �̵� ��Ų��. 
	cltWarpInfo clWarpInfo(1, PRISON_MAPINDEX, true, false, PRISON_X, PRISON_Y, -1, -1);	// �������� ���� 
	SetWarpInfo(&clWarpInfo, 5032);
	// ������ ���� ��Ų��. 
	Warp();

	//// ���� ���� �ȿ� ������, 
	//if(GetMapIndex() == 0 && GetX() >= 376 && GetX() <= 383 && GetY() >= 500 && GetY() <= 507)
	//{
	//}
	//else
	//{	
	//	// ���� ��ġ�� ���� �̵� ��Ų��. 
	//	cltWarpInfo clWarpInfo(1, PRISON_MAPINDEX, true, false, PRISON_X, PRISON_Y, -1, -1);	// �������� ���� 
	//	SetWarpInfo(&clWarpInfo, 5032);
	//	// ������ ���� ��Ų��. 
	//	Warp();

	//}

	return true;
}


// �ڵ� ������� ���θ� Ȯ���Ѵ�. 
bool cltCharServer::IsAutoHunting()
{
	// ���������� ������� 20���̻� ����ߴٸ�, 
	if(pclClient->CurrentClock - clSimpleVary.dwLastKillClock > 20000)return false;
	
	// ������ �ִ� ���̶��, 
	if ( !pclClient->pclMapManager->IsEncountMap( GetMapIndex() ) ) return false ;

	// �溹�ÿ� �ִ� ���̶��, 
	if(GetMapIndex() == MAPINDEX_PALACE)return false;
//	if(GetMapIndex() == MAPINDEX_CHINABORDER)return false;

	// ����� �ʿ� �ִ°��̶��
	if( pclClient->IsCountrySwitch(Switch_NewGuildHuntMapWar) )	// ������
	{
		if( IsGuildWarMap_Use_New_GuildWar( GetMapIndex() ) )
			return false;
		// ���ο� ����� ���̶��
		if( IsGuildWarMap_NEW( GetMapIndex() ) )
			return false;
	}
	else	// ������
	{
		if( IsGuildWarMap_Not_Use_New_GuildWar( GetMapIndex() ) )
			return false;
	}
	// ������ ���� �ִ� ���̶��, 
	if(clInnerStatus.IsStatus(INNERSTATUS_PRISON))return  false;

	return true;
}

// ��ƿ�� Ƚ���� ���´�. 
SI16 cltCharServer::GetStealNum()
{
	return siStealNum;
}

