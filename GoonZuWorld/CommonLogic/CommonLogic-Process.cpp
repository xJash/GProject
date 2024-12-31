#include "..\Common\CommonHeader.h"

#include "..\Client\Client.h"
#include "..\Server\Server.h"

#include <MainFunction.h>

#include "..\Client\Music\Music.h"
#include "..\Lib\Sound\SoundMgr.h"
#include "..\MapEdit\MapEdit.h"
#include "MagicMgr\MagicMgr.h"

#include "Map\Map.h"
#include "Char\CharManager\CharManager.h"
#include "Map\Map.h"
#include "Bullet\bullet.h"
#include "Smoke\Smoke.h"


// 실제 게임의 루틴이 들어있는 함수 
// 리턴값: 0 -> normal
SHORT cltCommonLogic::GameProcess()
{
	// 현재 지도가 정상적으로 로딩되어 있지 않다는 것은 
	// 서버로부터 아직 데이터를 받지 못했음을 의미하는 것으로 게임을 진행해서는 안된다. 
	if(pclMapManager == NULL)return 0;
	if(pclMapManager->pclCurrentMap == NULL)return 0;

	if(GameOverHead()==TRUE)return 0;
	
	GameAction();

	return 0;
}

/*cyj Client와 Server에서 구분하여 구현
SHORT cltCommonLogic::GameAction()
{
	static bool bgameactionswitch = true;

 	// 서버가 해야 할 부분을 행한다. 
	if(ServerAction() == FALSE)return 0;

	if(bgameactionswitch == true)
	{
		// 적절한 지도가 불려져 있지 않으면 실패. (클라이언트에서. ) 
		if(GameMode == GAMEMODE_CLIENT)
		{
			cltMapClient* pclmap = (cltMapClient* )pclMapManager->pclCurrentMap;
			if(pclmap == NULL)return 0;
		}


		bgameactionswitch = false;

		ClientAction2();
		
		IncreaseFrame();
		
		// 캐릭터의 행동 
		pclCM->Action();
		

		pclBulletManager->Action();						// 총알들의 행동 
	
		pclSmokeManager->Action();						// 연기들의 행동 
		
		pclMagicManager->Action();						// 마법들의  행동 
		MagicPopAction();
		
		
		// 마을 행동 
		if(pclVillageManager)
		{
			pclVillageManager->Action();
		}

	}

	// 클라이언트가 해야 할 부분을 행한다. 
	if(ClientAction1() == FALSE)
	{
		return 0;
	}

	bgameactionswitch = true;
	
	
	return 0;
}
*/
