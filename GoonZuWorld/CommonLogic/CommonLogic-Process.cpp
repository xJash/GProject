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


// ���� ������ ��ƾ�� ����ִ� �Լ� 
// ���ϰ�: 0 -> normal
SHORT cltCommonLogic::GameProcess()
{
	// ���� ������ ���������� �ε��Ǿ� ���� �ʴٴ� ���� 
	// �����κ��� ���� �����͸� ���� �������� �ǹ��ϴ� ������ ������ �����ؼ��� �ȵȴ�. 
	if(pclMapManager == NULL)return 0;
	if(pclMapManager->pclCurrentMap == NULL)return 0;

	if(GameOverHead()==TRUE)return 0;
	
	GameAction();

	return 0;
}

/*cyj Client�� Server���� �����Ͽ� ����
SHORT cltCommonLogic::GameAction()
{
	static bool bgameactionswitch = true;

 	// ������ �ؾ� �� �κ��� ���Ѵ�. 
	if(ServerAction() == FALSE)return 0;

	if(bgameactionswitch == true)
	{
		// ������ ������ �ҷ��� ���� ������ ����. (Ŭ���̾�Ʈ����. ) 
		if(GameMode == GAMEMODE_CLIENT)
		{
			cltMapClient* pclmap = (cltMapClient* )pclMapManager->pclCurrentMap;
			if(pclmap == NULL)return 0;
		}


		bgameactionswitch = false;

		ClientAction2();
		
		IncreaseFrame();
		
		// ĳ������ �ൿ 
		pclCM->Action();
		

		pclBulletManager->Action();						// �Ѿ˵��� �ൿ 
	
		pclSmokeManager->Action();						// ������� �ൿ 
		
		pclMagicManager->Action();						// ��������  �ൿ 
		MagicPopAction();
		
		
		// ���� �ൿ 
		if(pclVillageManager)
		{
			pclVillageManager->Action();
		}

	}

	// Ŭ���̾�Ʈ�� �ؾ� �� �κ��� ���Ѵ�. 
	if(ClientAction1() == FALSE)
	{
		return 0;
	}

	bgameactionswitch = true;
	
	
	return 0;
}
*/
