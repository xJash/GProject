//---------------------------------
// 2004/8/13 ���°�
//---------------------------------
#include "Hunting.h"

#include "..\..\Char\KindInfo\KindInfo.h"

#include "..\..\CommonLogic\CommonLogic.h"
#include "..\..\CommonLogic\MsgType-System.h"

//-----------------------------
// Common
//-----------------------------
#include "PersonInfo.h"
#include "Char\CharManager\CharManager.h"

//-------------------------------------
// Server
//-------------------------------------
#include "..\..\Server\Server.h"
#include "..\..\Server\Statistics\Statistics.h"

#include "..\DBManager\GameDBManager_World\DBMsg-Village.h"
#include "..\DBManager\GameDBManager_World\DBMsg-Item.h"

#include "../common/Event/event.h"

extern cltCommonLogic* pclClient;

cltEventHunting::cltEventHunting()
{
	Init();
}

cltEventHunting::~cltEventHunting()
{
}

void cltEventHunting::Init()
{
	cltEvent::Init();

	siMonsterID		= 0;
	siMonsterLevel	= 10;
	siCost			= 0;
	//siHuntingEventcount = 0;
	m_arEventCount_EachVillage.ZeroMem();
}

// �Ұ��縮 ��� �̺�Ʈ�� �����Ѵ�. 
bool cltEventHunting::Start(SI32 sivillageunique, SI32 cost)
{
	// �̹� �̺�Ʈ ���̸� ������ �� ����. 
	if(bEventSwitch == true)return false;

	bEventSwitch = true;

	siVillageUnique = sivillageunique;			// �̺�Ʈ ����� �Ǵ� ����
	dwLeftClock		= 30 * 60 * 1000;			// �̺�Ʈ �ܿ� �ð� - �� 30��
	dwStartClock	= pclClient->CurrentClock;	// �̺�Ʈ ���� �ð�
    siCost			= cost;						// �̺�Ʈ���	

	//HuntingEventCount_Increase();

	// ���͸� �����. 
	MakeMonster();

	// DB�� ������ �޽����� �����Ѵ�. 
	((cltServer*)pclClient)->pclStatisticsManager->clDailyStatistics.siHuntingEventNumber++;

	pclClient->pclLog->FilePrint(TEXT("Config\\Hunting.log"), TEXT("[EVENTSTART]\tVillageUnique=%d\tCost=%d"), siVillageUnique, siCost);

	return true;
	 
}



// �Ұ��縮 ��� �̺�Ʈ�� �����Ѵ�. 
void cltEventHunting::End()
{
	// �̹� �̺�Ʈ�� �ߴܵ� ���¸� �ߴ��� �� ����. 
	if(bEventSwitch == false)return ;

	bEventSwitch = false;

	pclClient->pclLog->FilePrint(TEXT("Config\\Hunting.log"), TEXT("[EVENTEND]") );
	// ���ʹ� ���ش�. 
	if(pclClient->pclCM->IsAlive(siMonsterID) == TRUE )
	{
		if(pclClient->pclCM->CR[siMonsterID]->clIdentity.siIdentity == IDENTITY_VILLAGEHUNT)
		{
			pclClient->pclCM->CR[siMonsterID]->DeleteInCell();
			pclClient->pclCM->DeleteChar(siMonsterID);
		}
		
	}

    _Contributors.clear();
}


// �Ұ��縮 ��� �̺�Ʈ ����. 
bool cltEventHunting::Action()
{
	bool bwinswitch = false;
	bool bloseswitch = false;


	// ���� �ֱ�� ���´�. 
	if(pclClient->GetFrame() % 111)return false;


	// �̹� �̺�Ʈ�� �ߴܵ� ���¸� ������ �� ����. 
	if(bEventSwitch == false)return false;

	// �ð��� �ʰ��Ǹ� �й� 
	DWORD dwelapsedclock = pclClient->CurrentClock - dwStartClock;
	if(dwelapsedclock >= dwLeftClock)
	{
		bloseswitch = true;

		TCHAR* pvillname = pclClient->pclVillageManager->GetName(siVillageUnique);
		if(pvillname)
		{
			TCHAR* pText = GetTxtFromMgr(5086);
			pclClient->pclLog->FilePrint(TEXT("Config\\Hunting.log"), pText, pvillname, siMonsterLevel, siCost);
		}
	}

	SI32 leftsecond;
	if(dwLeftClock > dwelapsedclock)
	{
		leftsecond = (dwLeftClock - dwelapsedclock) / 1000 ;
	}
	else
	{
		leftsecond = 0;
	}

	// ��ɰ��� �׿���. (�¸�) 
	if(pclClient->pclCM->IsAlive(siMonsterID) == false)
	{
		HuntingEventCount_Increase();

		bwinswitch = true;

		TCHAR* pvillname = pclClient->pclVillageManager->GetName(siVillageUnique);
		if(pvillname)
		{
			TCHAR* pText = GetTxtFromMgr(3640);
			pclClient->pclLog->FilePrint(TEXT("Config\\Hunting.log"), pText, pvillname, siMonsterLevel, siCost, leftsecond);
		}

		// ù��° �����϶� �������� ������ ����
		cltServer* pServer = (cltServer*)pclClient;
		if ( NULL == pServer )
		{
			return false;
		}

		SI32 siRewardItemUnique = 0;
		SI32 siRewardItemNum	= 0;

		// ���ֵ����̰�, ��Ƽ�콺 �̺�Ʈ ���� Ƚ ���� 1ȸ�϶� �������� ������ ����.
		if ( pServer->pclEventTimeManager->InEventTime(TEXT( "GoonzuDay_Week" ), &pServer->sTime)
			&& EVENT_GOONZUDAY_PLAY_COUNT == HuntingEvnetCount_Get() )
		{
			if(pclClient->IsWhereServiceArea(ConstServiceArea_Korea))
			{
				siRewardItemUnique	= ITEMUNIQUE(24131);		// GE �������� ������
			}
			else
			{
				siRewardItemUnique	= ITEMUNIQUE(24111);		// �������� ������
			}
			siRewardItemNum		= 1;
		}

		// ���� �ð��� ����Ͽ� ����ġ�� �ش�.
		SI32 index = 0;
		SI32 id;
		while(id = pclClient->pclCM->GetCharOrder(index))
		{
			index++;

			cltCharServer* pclchar  = (cltCharServer*)pclClient->pclCM->CR[id];
			// ������� �Ŀ��Ը� �����Ѵ�. 
			if(pclchar->IsValidConnection() == false)continue;
			// �ش� ���� �ֹο��Ը� �ش�.
			if(pclchar->pclCI->clBI.siHomeVillage != siVillageUnique)continue;

			// ����ġ
			SI64 exp = leftsecond * 3 * pclchar->pclCI->clIP.GetLevel() / MAX_CHARACTER_LEVEL;// SI32->SI64 ����ġ �����÷ο춧���� ����	
			pclchar->IncreaseExp(exp);

			if ( false == IsMosterHit( id, exp, siRewardItemUnique, siRewardItemNum ) )
			{
				// ���� ���� Ŭ�� �뺸
				cltGameMsgResponse_HuntingReward clinfo(exp, 0, 0, 0);
				cltMsg clMsg(GAMEMSG_RESPONSE_HUNTINGREWARD, sizeof(clinfo), (BYTE*)&clinfo);
				pclchar->SendNetMsg((sPacketHeader*)&clMsg);
			}
		}
	}

	if(bwinswitch || bloseswitch)
	{
		End();
	}

	if(TABS(pclClient->CurrentClock - dwLastInfoClock) > 3000)
	{
		dwLastInfoClock = pclClient->CurrentClock;
		
		// ���� ��Ȳ�� �̺�Ʈ ����ڵ鿡�� �뺸�Ѵ�.(�ܿ��ð�..) 
		SI32 mode = 0;
		if(bwinswitch)
		{
			mode = 1;

			//cyj ������������ : ������ DB�� �޼����� ������.			
			sDBRequest_VillageEventSuccess clMsg( siVillageUnique );
			((cltServer*)pclClient)->SendDBMsg(DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);

			//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			//{
			//	// [�α��߰� : Ȳ���� 2007. 10. 9] // ���� �̺�Ʈ ����.
			//	//
			//	cltServer * pclServer = (cltServer*)pclClient;
			//	pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_VILLAGE, LOGCOMMAND_INDEX_VILLAGE_EVENT_SUCCESS, 
			//									0, NULL, NULL, 0, 0, 0, NULL, 0, 0, 0, siVillageUnique, 0, 0, 
			//									0, 0, 0, 0, 0, NULL, NULL);
			//}

		}
		else if(bloseswitch)
		{
			mode = -1;
		}
		cltGameMsgResponse_HuntingInfo clinfo(siVillageUnique, leftsecond, mode);
		cltMsg clMsg(GAMEMSG_RESPONSE_HUNTINGINFO, sizeof(clinfo), (BYTE*)&clinfo);
		pclClient->pclCM->SendAllPersonHomeMsg((sPacketHeader*)&clMsg, siVillageUnique);
	}

	return true;
}

// ��ɰ��� �����. 
void cltEventHunting::MakeMonster()
{
	SI32 i;
	// ���� ������ �����Ѵ�. 
	SI32 kind = pclClient->GetUniqueFromHash( TEXT("KIND_CHIMERA"));

	// �ش� ������ ����Ʈ�� �߰��Ѵ�.
	SI16 villagelist[MAX_VILLAGE_NUMBER];
	SI32 index = 0;
	for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
	{
		villagelist[i] = 0;
	}

	for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
	{
		if(pclClient->pclVillageManager->pclVillageInfo[i])
		{
			villagelist[index] = i;
			index++;
		}
	}

	SI32 villageunique = 0;
	if(index)
	{
		villageunique = villagelist[rand() % index];
	}
	else
	{
		MsgBox(TEXT("fdsfiff"), TEXT("f3fdf"));
		return ;
	}


	// ã�� ���� �ֺ��� ���͸� �����.
	SI32 tempx, tempy;
	SI32 x, y;
	do
	{
		tempx = pclClient->pclVillageManager->pclVillageInfo[villageunique]->PosX + (5 - rand() % 10);
		tempy = pclClient->pclVillageManager->pclVillageInfo[villageunique]->PosY + (5 - rand() % 10);
		
	}
	while(pclClient->pclMapManager->pclMapArray[0]->FindEmptyAreaForCharLocate(kind, tempx, tempy, 10, &x, &y, true) == false);

	// ���͸� ��ġ�Ѵ�. 
	cltIdentity clIdentity;
	clIdentity.MakeHunt(IDENTITY_VILLAGEHUNT, siVillageUnique);

	cltServer* pclserver = (cltServer*)pclClient;

	cltInnerStatusInfo clinnerstatus;
	clinnerstatus.clEnemyType.Set(ENEMYTYPE_ONEVILLAGE, siVillageUnique);

	if(	pclClient->IsCountrySwitch( Switch_Event_Hunt_Reform ) )
	{
		//[����]  ������ 80~120 ���� 5������ �����ϰ� => 2008-5-30
		siMonsterLevel = ((rand() % 9) + 16) * 5;
	}
	else
	{
		// ������ 1~100 ���� 10������ �����ϰ�
		siMonsterLevel = ((rand() % 10) + 1) * 10;
	}

	SI32 id = pclserver->SetNPCChar(kind, VILLAGE_NONE, &clIdentity, siMonsterLevel, 0, x, y, 0, NPCITEMMODE_NORMAL, &clinnerstatus );

	if(id)
	{
		siMonsterID	= id;	// ������ ���̵� Ȯ���Ѵ�.
	}

	pclClient->pclLog->FilePrint(TEXT("Config\\Hunting.log"), TEXT("[MAKEMONSTER]\tVillageUnique=%d\tX=%d\tY=%d\tLevel=%d"), siVillageUnique, x, y, siMonsterLevel );
}

// �Ѵ�� ģ����� ��~ �߰�
void cltEventHunting::AddContributor(SI32 AttackerID)
{
	_Contributors.insert(AttackerID);
}

void cltEventHunting::HuntingEventCount_Increase()
{
	//++siHuntingEventcount;
	if ( MAX_VILLAGE_NUMBER <= siVillageUnique || 0 > siVillageUnique ) return;
	m_arEventCount_EachVillage[siVillageUnique] = m_arEventCount_EachVillage[siVillageUnique] + 1;
}

void cltEventHunting::HuntingEventCount_Reset()
{
	//siHuntingEventcount = 0;
	m_arEventCount_EachVillage.ZeroMem();
}

SI16 cltEventHunting::HuntingEvnetCount_Get()
{
	//return siHuntingEventcount;
	if ( MAX_VILLAGE_NUMBER <= siVillageUnique || 0 > siVillageUnique ) return 0;
	else return m_arEventCount_EachVillage[siVillageUnique];
}

bool cltEventHunting::IsMosterHit(SI32 siCharID, SI64 siExp, SI32 siRewardItemUnique, SI32 siRewardItemNum)
{
	std::set<SI32>::const_iterator Iter = _Contributors.begin();

	while(Iter != _Contributors.end())
	{
		if ( siCharID == (*Iter) )
		{
			if(pclClient->pclCM->IsValidID(*Iter) && pclClient->pclCM->CR[*Iter]->pclCI->clBI.siHomeVillage == siVillageUnique)
			{
				((cltCharServer *)pclClient->pclCM->CR[(*Iter)])->GiveItem(24000, 1, INPUTITEMPERSON_OPTION_CHIMERA_REWARD, 0);

				// ����
				if ( 0 < siRewardItemUnique )
				{
					((cltCharServer *)pclClient->pclCM->CR[(*Iter)])->GiveItem(siRewardItemUnique, siRewardItemNum, INPUTITEMPERSON_OPTION_CHIMERA_REWARD, 0);

					// ���� ���� Ŭ�� �뺸
					cltGameMsgResponse_HuntingReward clinfo(siExp, 0, siRewardItemUnique, siRewardItemNum);
					cltMsg clMsg(GAMEMSG_RESPONSE_HUNTINGREWARD, sizeof(clinfo), (BYTE*)&clinfo);
					((cltCharServer *)pclClient->pclCM->CR[(*Iter)])->SendNetMsg((sPacketHeader*)&clMsg);

					return true;
				}
			}
		}

		++Iter;
	}

	return false;
}