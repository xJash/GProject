//---------------------------------
// 2004/8/27 ���°�
//---------------------------------
#include "../../Server/Server.h"
#include "Char-Server.h"
#include "../CharManager/CharManager.h"
#include "../../DBManager/GameDBManager_World/DBMsg-Person.h"
#include "../../Common/NPCManager/NPC.h"

#include "../../GameEvent/GameEvent.h"

#include "Msg/MsgType-Quest.h"
#include "../../CommonHeader.h"
#include "MsgRval-Define.h"

//-----------------------------
// Common
//-----------------------------
#include "PersonInfo.h"

//-----------------------------
// CommonLogic
//-----------------------------
#include "../../CommonLogic/MsgType-Person.h"
#include "../../CommonLogic/MsgType-Item.h"

#include "../../Common/Quest/NamingQuest.h"
#include "../../common/Char/CharServer/Char-Item.h"


extern cltCommonLogic* pclClient;





//[����] : ���ڿ��� �� npcī�ε带 �ʱ�ȭ �Ѵ�.
void cltCharServer::InitArray_RemoveUnLuckQuestNPC()
{
	// �밡�ٷ� �ʱ�ȭ;;
	m_arRemoveUnluckQuest_NPC[0] = TEXT( "KIND_SOPHIA" );
	m_arRemoveUnluckQuest_NPC[1] = TEXT( "KIND_SPARKY" );
	m_arRemoveUnluckQuest_NPC[2] = TEXT( "KIND_MERIEL" );
	m_arRemoveUnluckQuest_NPC[3] = TEXT( "KIND_BRAI" );
	m_arRemoveUnluckQuest_NPC[4] = TEXT( "KIND_BELITA" );
	m_arRemoveUnluckQuest_NPC[5] = TEXT( "KIND_HINEAS" );
	m_arRemoveUnluckQuest_NPC[6] = TEXT( "KIND_KELAN" );
	m_arRemoveUnluckQuest_NPC[7] = TEXT( "KIND_JEFFREY" );
	m_arRemoveUnluckQuest_NPC[8] = TEXT( "KIND_MOLDA" );

	m_arRemoveUnluckQuest_Unique[0] = 2000;
	m_arRemoveUnluckQuest_Unique[1] = 2400;
	m_arRemoveUnluckQuest_Unique[2] = 3000;
	m_arRemoveUnluckQuest_Unique[3] = 3500;
	m_arRemoveUnluckQuest_Unique[4] = 4000;
	m_arRemoveUnluckQuest_Unique[5] = 4500;
	m_arRemoveUnluckQuest_Unique[6] = 28000;
	m_arRemoveUnluckQuest_Unique[7] = 5500;
	m_arRemoveUnluckQuest_Unique[8] = 26000;
}

// ����Ʈ�� �Ķ��Ÿ�� ������Ų��. 
void cltCharServer::IncQuestPara(SI32 clearcond, SI32 para1, SI32 incnum)
{
	SI16 questtype;
	SI16 unique;
	SI32 startindex = 0;
	// �ش� ������ Ŭ���� ������ ���� ����Ʈ�� ã��������. 
	while(pclCI->clQuestInfo.IsQuestGoing( clearcond, &questtype, &unique, NULL, NULL, &startindex) == true)
	{
		if(pclCI->clQuestInfo.IncPara(questtype, para1, incnum) == true)
		{
			// Ŭ���̾�Ʈ�� ����Ʈ�� ���¸� �뺸�Ѵ�. 
			SetUpdateSwitch(UPDATE_QUEST, true, 0);

			if ( TABS( lastQuestSaveDBTime - pclClient->CurrentClock ) > 60000 )
			{
				// LEEKH MODIFY 2007.10.25
				cltPersonQuestUnitInfo* pQuestUnit = &pclCI->clQuestInfo.clUnit[questtype];
				if(pQuestUnit != NULL)
				{
					// DB�� ����Ʈ�� ���¸� �����Ѵ�. 
					sDBRequest_SetQuestInfo clMsg(pclCI->GetPersonID(), questtype, pQuestUnit);
					pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
				}
			}
		}
	}
}


// ĳ���Ͱ� �����ϰ� �ִ� ����Ʈ�� �����Ͽ� �����Ų��. 
void cltCharServer::DoQuestCheckAndAction(SI32 questclearcond)
{
	cltServer* pclserver = (cltServer*)pclClient;

	SI16 questtype, questunique;
	SI16 para1, para2;
	if(pclCI->clQuestInfo.IsQuestGoing(questclearcond, &questtype, &questunique, &para1, &para2) == true)
	{
		cltPersonQuestUnitInfo* pclquestinfo = &pclCI->clQuestInfo.clUnit[questtype];
		if(pclquestinfo->siCurQuestStep != QUEST_STEP_MIDDLE)return ;

		/*		//KHY - 0822 - ���Ǻ� ����Ʈ �߰�.
		if(questtype == QUEST_TYPE_SPECIAL || questtype == QUEST_TYPE_NAMING || questtype == QUEST_TYPE_HAPPYBEAN )
		{

		}
		else
		{
			if(pclquestinfo->siCurQuestUnique != questunique)return ;
		}*/

			switch( questtype )
		{
			case QUEST_TYPE_SPECIAL:
			case QUEST_TYPE_NAMING:
			case QUEST_TYPE_HAPPYBEAN:
			case QUEST_TYPE_MISSION1:
				{
				}
				break;
			default:
				{
					if( pclquestinfo->siCurQuestUnique != questunique )			return;
				}
				break;
		}

		// ����Ʈ�� ���¸� �����Ѵ�. 
		pclquestinfo->siQuestPara1	= para1;
		pclquestinfo->siQuestPara2	= para2;

		// DB�� ����Ʈ�� ���¸� �����Ѵ�. 
		sDBRequest_SetQuestInfo clMsg(pclCI->GetPersonID(), questtype, pclquestinfo);
		pclClient->SendDBMsg( DBSELECT_SUB, (sPacketHeader *)&clMsg);

		// Ŭ���̾�Ʈ�� ����Ʈ�� ���¸� �뺸�Ѵ�. 
		SetUpdateSwitch(UPDATE_QUEST, true, 0);
	}
}


// ��� ���� �ٸ���.
bool cltCharServer::MakeSpecialQuest_Scroll()
{

	cltQuestRewardInfo clrewardinfo;
	clrewardinfo.siExp	= pclCI->clIP.GetLevel() * 10;

	// ����Ʈ�� ���� ������ ���Ѵ�. 
	pclCI->clQuestInfo.clSpecialQuestInfo.clQuestClearConditionInfo.siFlag	=	QUEST_CLEAR_COND_SCROLL;
	pclCI->clQuestInfo.clSpecialQuestInfo.clQuestClearConditionInfo.siPara1	=	0;
	pclCI->clQuestInfo.clSpecialQuestInfo.clQuestClearConditionInfo.siPara2	=	1;

	// ������ ���Ѵ�. 
	pclCI->clQuestInfo.clSpecialQuestInfo.clQuestRewardInfo.Set(&clrewardinfo);

	return true;
}

// ��� �ø���  Ư�� ����Ʈ�� �����. 
bool cltCharServer::MakeSpecialQuest_Skill()
{

	//������ ����� ã�´�. 
	SI32 skillunique;		// �÷��� �� �������. 
	SI32 upgradeskilllevel;	// �÷��� �� ��� ����.



#ifdef _SAFE_MEMORY
	if(pclCI->clCharSkill.GetRandSkillForUpgrade(pclClient->pclSkillManager, &pclCI->clCharItem.clItem[0], &skillunique, &upgradeskilllevel )
		== false) return false; // �� �Ϸ� ����ġ ������ ����.
#else
	if(pclCI->clCharSkill.GetRandSkillForUpgrade(pclClient->pclSkillManager, pclCI->clCharItem.clItem, &skillunique, &upgradeskilllevel )
		== false) return false; // // �� �Ϸ� ����ġ ������ ����.
#endif

	cltQuestRewardInfo clrewardinfo;
	clrewardinfo.siExp		= pclCI->clIP.GetLevel() * 100;


	// ����Ʈ�� ���� ������ ���Ѵ�. 
	pclCI->clQuestInfo.clSpecialQuestInfo.clQuestClearConditionInfo.siFlag	=	QUEST_CLEAR_COND_SKILL;
	pclCI->clQuestInfo.clSpecialQuestInfo.clQuestClearConditionInfo.siPara1	=	skillunique;
	pclCI->clQuestInfo.clSpecialQuestInfo.clQuestClearConditionInfo.siPara2	=	upgradeskilllevel;


	// ������ ���Ѵ�. 
	pclCI->clQuestInfo.clSpecialQuestInfo.clQuestRewardInfo.Set(&clrewardinfo);

	return true;

}
// ��� �����ϱ� Ư�� ����Ʈ�� �����. 
bool cltCharServer::MakeSpecialQuest_Equip()
{

	SI32 equiplist[100];
	SI32 listindex	= 0;
	SI32 equippos[] ={
		PERSONITEM_WEAPON1,
			PERSONITEM_WEAPON2,
			PERSONITEM_HELMET, 
			PERSONITEM_BELT,
			PERSONITEM_ARMOUR, 
			PERSONITEM_SHOES,
	}; 

	SI32 equipposnum = sizeof(equippos) / sizeof(SI32);

	// ������� ���� ��ǰ�� ����. 
	for(SI32 i = 0;i <equipposnum;i++)
	{
		if(pclCI->clCharItem.clItem[ equippos[i] ].siUnique == 0)
		{
			equiplist[listindex] = equippos[i];
			listindex++;
		}

	}

	SI32 pos = 0;
	if(listindex)
	{
		pos = equiplist[rand() % listindex];
	}
	else
	{
		return false;
	}

	cltQuestRewardInfo clrewardinfo;
	clrewardinfo.siExp	= pclCI->clIP.GetLevel() * 100;


	// ����Ʈ�� ���� ������ ���Ѵ�. 
	pclCI->clQuestInfo.clSpecialQuestInfo.clQuestClearConditionInfo.siFlag	=	QUEST_CLEAR_COND_EQUIPPOS;
	pclCI->clQuestInfo.clSpecialQuestInfo.clQuestClearConditionInfo.siPara1	=	pos;
	pclCI->clQuestInfo.clSpecialQuestInfo.clQuestClearConditionInfo.siPara2	=	1;

	// ������ ���Ѵ�. 
	pclCI->clQuestInfo.clSpecialQuestInfo.clQuestRewardInfo.Set(&clrewardinfo);

	return true;
}


// �����ϱ�� Ư�� ����Ʈ�� �����. 
bool cltCharServer::MakeSpecialQuest_Fish()
{

	//SI32 fishlist[] ={
	//	16100,	// �ؾ� 
	//	16110,	// �ޱ� 
	//	16120	// �׾� 
	//};

	//SI32 fishlistnum = sizeof(fishlist) / sizeof(SI32);

	//SI32 fishkind	= fishlist[rand() % fishlistnum];
	//SI32 data = (rand() % 4);
	//SI32 fishnum	= max(2, data);	

	cltQuestRewardInfo clrewardinfo;
	clrewardinfo.siExp	= pclCI->clIP.GetLevel() * 100;

	// ����Ʈ�� ���� ������ ���Ѵ�. 
	pclCI->clQuestInfo.clSpecialQuestInfo.clQuestClearConditionInfo.siFlag	=	QUEST_CLEAR_COND_FISH;
	pclCI->clQuestInfo.clSpecialQuestInfo.clQuestClearConditionInfo.siPara1	=	0;
	pclCI->clQuestInfo.clSpecialQuestInfo.clQuestClearConditionInfo.siPara2	=	1;

	// ������ ���Ѵ�. 
	pclCI->clQuestInfo.clSpecialQuestInfo.clQuestRewardInfo.Set(&clrewardinfo);

	return true;
}

// �������� Ư�� ����Ʈ�� �����. 
bool cltCharServer::MakeSpecialQuest_Farm()
{

	SI32 farmitemnum = 0;

	//SI32 *pfarmlist = NULL;
	//if(pclClient->pclItemManager->GetFarmItemList(&farmitemnum, &pfarmlist) == false)
	//{
	//	if(pfarmlist)
	//	{
	//		delete[] pfarmlist;
	//		pfarmlist = NULL;
	//	}
	//	return false;
	//}

	//if(farmitemnum <= 0)return false;

	SI32 farmkind	= 0; // ������ ��� ����. �ʿ������ para���� �Է�..
	SI32 farmnum	= 1;

	// ����Ʈ�� ���� ������ ���Ѵ�. 
	pclCI->clQuestInfo.clSpecialQuestInfo.clQuestClearConditionInfo.siFlag	=	QUEST_CLEAR_COND_FARM;
	pclCI->clQuestInfo.clSpecialQuestInfo.clQuestClearConditionInfo.siPara1	=	farmkind;
	pclCI->clQuestInfo.clSpecialQuestInfo.clQuestClearConditionInfo.siPara2	=	farmnum;

	// ������ ���Ѵ�. 
	cltQuestRewardInfo clrewardinfo;
	clrewardinfo.siExp	= pclCI->clIP.GetLevel() * 100;

	pclCI->clQuestInfo.clSpecialQuestInfo.clQuestRewardInfo.Set(&clrewardinfo);

	return true;
}

// ä���ϱ�� Ư�� ����Ʈ�� �����. 
bool cltCharServer::MakeSpecialQuest_Mine()
{

	SI32 farmkind	= 0; // ������ ��� ����. �ʿ������ para���� �Է�..
	SI32 farmnum	= 1;

	// ����Ʈ�� ���� ������ ���Ѵ�. 
	pclCI->clQuestInfo.clSpecialQuestInfo.clQuestClearConditionInfo.siFlag	=	QUEST_CLEAR_COND_MINE;
	pclCI->clQuestInfo.clSpecialQuestInfo.clQuestClearConditionInfo.siPara1	=	farmkind;
	pclCI->clQuestInfo.clSpecialQuestInfo.clQuestClearConditionInfo.siPara2	=	farmnum;

	// ������ ���Ѵ�. 
	cltQuestRewardInfo clrewardinfo;
	clrewardinfo.siExp	= pclCI->clIP.GetLevel() * 100;

	pclCI->clQuestInfo.clSpecialQuestInfo.clQuestRewardInfo.Set(&clrewardinfo);

	return true;
}

// ģ�������� Ư�� ����Ʈ�� �����. 
bool cltCharServer::MakeSpecialQuest_MakeFriend()
{

	// ���� ģ���� ���� ���Ѵ�. 
	SI32 curfriendnum	= 0;
	if(pclFriendInfo)		curfriendnum = pclFriendInfo->GetFriendNum();
	if( curfriendnum >= MAX_FRIEND_NUMBER )return false;

	cltQuestRewardInfo clrewardinfo;

	clrewardinfo.siExp	= pclCI->clIP.GetLevel() * 100;


	// ����Ʈ�� ���� ������ ���Ѵ�. 
	pclCI->clQuestInfo.clSpecialQuestInfo.clQuestClearConditionInfo.siFlag	=	QUEST_CLEAR_COND_MAKEFRIEND;
	pclCI->clQuestInfo.clSpecialQuestInfo.clQuestClearConditionInfo.siPara1	=	1;
	pclCI->clQuestInfo.clSpecialQuestInfo.clQuestClearConditionInfo.siPara2	=	curfriendnum + 1;

	// ������ ���Ѵ�. 
	pclCI->clQuestInfo.clSpecialQuestInfo.clQuestRewardInfo.Set(&clrewardinfo);

	return true;
}

// ������ Ư�� ����Ʈ�� �����. 
bool cltCharServer::MakeSpecialQuest_Battle()
{
	SI32 monkind	= pclClient->GetUniqueFromHash( TEXT("KIND_RACCON") );
	SI32 monnum		= 1;
	SI32 exp		= 100;

	cltQuestRewardInfo clrewardinfo;

	// ������ �´� ������ ���Ϳ� ������ ���Ѵ�. 
	if(pclClient->pclKindInfoSet->FindGoodMonsterForSpecialQuest(pclCI->clIP.GetLevel(),&monkind, &monnum, &clrewardinfo ) == false)
	{
		return false;
	}

	/*
#ifdef _DEBUG
	monnum = 3;
#endif
	*/

		// ����Ʈ�� ���� ������ ���Ѵ�. 
		pclCI->clQuestInfo.clSpecialQuestInfo.clQuestClearConditionInfo.siFlag	=	QUEST_CLEAR_COND_KILLMON;
	pclCI->clQuestInfo.clSpecialQuestInfo.clQuestClearConditionInfo.siPara1	=	monkind;
	pclCI->clQuestInfo.clSpecialQuestInfo.clQuestClearConditionInfo.siPara2	=	monnum;

	// ������ ���Ѵ�. 
	pclCI->clQuestInfo.clSpecialQuestInfo.clQuestRewardInfo.Set(&clrewardinfo);

	return true;
}

// ���� ����غ��� ����Ʈ�� �����. 
bool cltCharServer::MakeSpecialQuest_UseItem()
{
	SI32 siitemlist[] ={
		ITEMUNIQUE(2565),	ITEMUNIQUE(2570),	ITEMUNIQUE(2575),
			ITEMUNIQUE(2580),	ITEMUNIQUE(2585),	ITEMUNIQUE(2590),	ITEMUNIQUE(2595),
			ITEMUNIQUE(2600),	ITEMUNIQUE(2605),	ITEMUNIQUE(2610),	ITEMUNIQUE(2615),
			ITEMUNIQUE(2620),	ITEMUNIQUE(2630),	ITEMUNIQUE(2635),

			ITEMUNIQUE(3735),	ITEMUNIQUE(3740),	ITEMUNIQUE(3745),	ITEMUNIQUE(3750),
			ITEMUNIQUE(3755),	ITEMUNIQUE(3760),	ITEMUNIQUE(3765),	ITEMUNIQUE(3770),
			ITEMUNIQUE(3775),	ITEMUNIQUE(3780),	ITEMUNIQUE(3785),	ITEMUNIQUE(3790),
			ITEMUNIQUE(3795),	ITEMUNIQUE(3800),	ITEMUNIQUE(3805),	ITEMUNIQUE(3810),
			ITEMUNIQUE(3815),	ITEMUNIQUE(3820),	ITEMUNIQUE(3825),	ITEMUNIQUE(3830),
			ITEMUNIQUE(3835),	ITEMUNIQUE(3840),
	};

	SI32 itemlistnum	= sizeof(siitemlist) / sizeof(SI32);
	if(itemlistnum <= 0)return false;

	SI16 itemunique = siitemlist[ rand() % itemlistnum];


#ifdef _DEBUG
	//SI16 itemnum	= 1;
	SI16 itemnum = 30 + ( rand() % 21); // ��� ���� ���� 30~50��. (�׽�Ʈ�� ����)
#else


	//SI16 itemnum	= 50;
	SI16 itemnum = 30 + ( rand() % 21); // ��� ���� ���� 30~50��.
#endif


	cltItemPriceUnit* pclprice = pclClient->pclItemManager->pclItemPrice->GetPrice(pclClient->pclItemManager, itemunique);
	if(pclprice == NULL)return false;



	cltQuestRewardInfo clrewardinfo;
	clrewardinfo.siExp		= pclCI->clIP.GetLevel() * 100;
	//clrewardinfo.siMoney	= pclprice->siPrice * itemnum * 50 / 100;

	// ����Ʈ�� ���� ������ ���Ѵ�. 
	pclCI->clQuestInfo.clSpecialQuestInfo.clQuestClearConditionInfo.siFlag	=	QUEST_CLEAR_COND_USEITEM;
	pclCI->clQuestInfo.clSpecialQuestInfo.clQuestClearConditionInfo.siPara1	=	itemunique;
	pclCI->clQuestInfo.clSpecialQuestInfo.clQuestClearConditionInfo.siPara2	=	itemnum;

	// ������ ���Ѵ�. 
	pclCI->clQuestInfo.clSpecialQuestInfo.clQuestRewardInfo.Set(&clrewardinfo);

	return true;
}



// ��ǰ �������� Ư�� ����Ʈ�� �����. 
bool cltCharServer::MakeSpecialQuest_GetItem()
{
	SI32 itemunique	= 0;
	SI32 itemnum	= 1;

	SI16 itemtypelist[] = {
		ITEMTYPE_MINERAL,	
			ITEMTYPE_CLOTH,
			ITEMTYPE_TREE,
	};

	SI32 itemtypelistnum = sizeof(itemtypelist) / sizeof(SI16);

	SI16 itemtype = itemtypelist[ rand() % itemtypelistnum];


	cltQuestRewardInfo clrewardinfo;

	// �� �κ��� �ִ°��� �ٽ� ã�´�.
	for ( SI32 i=0; i < 3; ++i  )
	{
		itemunique = pclClient->pclMarketManager->GetRandomOrder( itemtype );

		if(itemunique <= 0)
		{
			return false;
		}

		if( pclClient->pclItemManager->IsItemInfoAtb( itemunique, ITEMINFOATB_NOTDAILYQUEST ) )
		{
			return false;
		}

		// �� �κ��� ���� ��쿡�� ���̻� ã�� ����;
		if(pclCI->clCharItem.FindItemInv(itemunique) == false ) 
			break;
	}

#ifdef _DEBUG
	//itemnum = 3;
	itemnum = 30 + ( rand() % 21); // �������� ���� 30~50��.
#else
	//itemnum = 50;	// �������� 50��.
	itemnum = 30 + ( rand() % 21); // �������� ���� 30~50��.
#endif



	clrewardinfo.siExp		= pclCI->clIP.GetLevel() * 100;

	// ����Ʈ�� ���� ������ ���Ѵ�. 
	pclCI->clQuestInfo.clSpecialQuestInfo.clQuestClearConditionInfo.siFlag	=	QUEST_CLEAR_COND_ITEM;
	pclCI->clQuestInfo.clSpecialQuestInfo.clQuestClearConditionInfo.siPara1	=	itemunique;
	pclCI->clQuestInfo.clSpecialQuestInfo.clQuestClearConditionInfo.siPara2	=	itemnum;

	// ������ ���Ѵ�. 
	pclCI->clQuestInfo.clSpecialQuestInfo.clQuestRewardInfo.Set(&clrewardinfo);

	return true;
}


// ��ǰ �����ϱ� Ư�� ����Ʈ�� �����. 
bool cltCharServer::MakeSpecialQuest_MakeItem()
{

	SI16 skilllist[] = {
		SKILL_MAKEMED,	
			SKILL_MAKEFOOD,	
			SKILL_MAKEARMOUR1,	
			SKILL_MAKEHELMET1,	
			SKILL_MAKESWORD1,	
			SKILL_MAKESPEAR1,	
			SKILL_MAKEAXE1,	
			SKILL_MAKESTAFF1,
			SKILL_MAKEBOW1,	
			SKILL_MAKEGUN1,	
			SKILL_MAKESHOES1,	
			SKILL_MAKEBELT1,	
			SKILL_MAKEDRESS1,	
			SKILL_MAKEIRON1,
			SKILL_MAKETOOL1,
			SKILL_MAKEHAT1,
			SKILL_ARTIFACT
	};


	SI32 skillnum = sizeof(skilllist) / sizeof(SI16);

	SI16 skillbuffer[MAX_SKILL_NUMBER];
	SI16 skilllevelbuffer[MAX_SKILL_NUMBER];
	SI32 skillbufferindex = 0;
	for(SI32 i = 0;i < skillnum;i++)
	{
		SI32 tempskilllevel = pclCI->clCharSkill.GetTotalSkillLevel(skilllist[i], 0, NULL);
		if(tempskilllevel == 0)continue;

		skillbuffer[skillbufferindex]		= skilllist[i];
		skilllevelbuffer[skillbufferindex]	= tempskilllevel;
		skillbufferindex++;
	}

	if(skillbufferindex == 0)
	{
		return false;
	}

	SI32 index			= rand() % skillbufferindex;
	SI32 skillunique	= skillbuffer[index];
	SI32 skilllevel		= skilllevelbuffer[index];


	// Ư�� ����� ����� �ִ� ��ǰ�� ����Ʈ�� ���Ѵ�. 
	SI16 siitemlist[MAX_ITEMINFO_NUMBER];
	SI32 itemlistindex = 0;
	for(i = 0;i < MAX_ITEMINFO_NUMBER;i++)
	{

		if(pclClient->pclItemManager->pclItemInfo[i] == NULL)continue;
		if(pclClient->pclItemManager->pclItemInfo[i]->clSkillInfo.siSkill != skillunique)continue;
		if(pclClient->pclItemManager->pclItemInfo[i]->clSkillInfo.siSkillLevel > skilllevel)continue;
		if(pclClient->pclItemManager->pclItemInfo[i]->clSkillInfo.siSkillLevel < max(1, skilllevel/2) )continue;
		if(pclClient->pclItemManager->pclItemInfo[i]->clProductionInfo.clMaterial[0].siUnique == 0)continue;


		if(pclClient->pclItemManager->pclItemInfo[i]->CanMake_Skill(&pclCI->clCharSkill, &pclCI->clCharItem, &clPB.clTotalBA) == false)continue;

		siitemlist[itemlistindex] = pclClient->pclItemManager->pclItemInfo[i]->clItem.siUnique;
		itemlistindex++;
	}

	if(itemlistindex == 0)return false;

	SI32 makeitemunique = siitemlist[rand() % itemlistindex];
	//SI32 makenum	= 3 + ( rand() % 3 ); // ���� ���� 3~5��.

	SI32 makenum = 1 + ( rand() % 5 );	  // ���� ���� 1~ 5��.


	SI32 ref	= pclClient->pclItemManager->FindItemRefFromUnique(makeitemunique);
	if(ref <= 0)	return false;

	cltQuestRewardInfo clrewardinfo;

	clrewardinfo.siExp		= pclCI->clIP.GetLevel() * 100;
	clrewardinfo.siMoney	= 0;


	// ����Ʈ�� ���� ������ ���Ѵ�. 
	pclCI->clQuestInfo.clSpecialQuestInfo.clQuestClearConditionInfo.siFlag	=	QUEST_CLEAR_COND_MAKEITEM;
	pclCI->clQuestInfo.clSpecialQuestInfo.clQuestClearConditionInfo.siPara1	=	makeitemunique;
	pclCI->clQuestInfo.clSpecialQuestInfo.clQuestClearConditionInfo.siPara2	=	makenum;

	// ������ ���Ѵ�. 
	pclCI->clQuestInfo.clSpecialQuestInfo.clQuestRewardInfo.Set(&clrewardinfo);

	return true;

}


// ���� ��ȸ�ϱ� Ư�� ����Ʈ�� �����.
bool cltCharServer::MakeSpecialQuest_Gomap()
{
	cltQuestRewardInfo clrewardinfo;
	clrewardinfo.siExp	= pclCI->clIP.GetLevel() * 100;

	// ���� �� ������ �ε����� ���ؼ� siPara1�� �־��ش�.
	SI32 siDestTownIndex = 0;
	siDestTownIndex = rand() % 42 + 1;

	// ����Ʈ�� ���� ������ ���Ѵ�. 
	pclCI->clQuestInfo.clSpecialQuestInfo.clQuestClearConditionInfo.siFlag	=	QUEST_CLEAR_COND_LAMPGOMAP;
	pclCI->clQuestInfo.clSpecialQuestInfo.clQuestClearConditionInfo.siPara1	=	siDestTownIndex;	// ������ ������ �ε���.
	pclCI->clQuestInfo.clSpecialQuestInfo.clQuestClearConditionInfo.siPara2	=	1;

	// ������ ���Ѵ�. 
	pclCI->clQuestInfo.clSpecialQuestInfo.clQuestRewardInfo.Set(&clrewardinfo);

	return true;
}

// ���� ��ų ����ġ ����Ʈ 1 �ø��� ����Ʈ�� �����.
bool cltCharServer::MakeSpecialQuest_MakeSkillExpup()
{

	//������ ����� ã�´�. 
	SI32 skillunique = 0;		// �÷��� �� �������. 
	SI32 increaseSkillExp = 0;	// �÷��� �� ��� ����ġ�� ��ƿ� ����


#ifdef _SAFE_MEMORY
	if(pclCI->clCharSkill.GetRandSkillEXPupForUpgrade(pclClient->pclSkillManager, &pclCI->clCharItem.clItem[0], &skillunique, &increaseSkillExp)
		== false) return false; // �� �Ϸ� ����ġ ������ ����.
#else
	if(pclCI->clCharSkill.GetRandSkillEXPupForUpgrade(pclClient->pclSkillManager, pclCI->clCharItem.clItem, &skillunique, &increaseSkillExp)
		== false) return false; // // �� �Ϸ� ����ġ ������ ����.
#endif

	cltQuestRewardInfo clrewardinfo;
	clrewardinfo.siExp		= pclCI->clIP.GetLevel() * 100;


	// ����Ʈ�� ���� ������ ���Ѵ�. 
	pclCI->clQuestInfo.clSpecialQuestInfo.clQuestClearConditionInfo.siFlag	=	QUEST_CLEAR_COND_MAKESKILLEXPUP;
	pclCI->clQuestInfo.clSpecialQuestInfo.clQuestClearConditionInfo.siPara1	=	skillunique;
	pclCI->clQuestInfo.clSpecialQuestInfo.clQuestClearConditionInfo.siPara2	=	increaseSkillExp;		// ����ġ 1�� �����ϸ� ����Ǵ� ���� �߰�.

	// ������ ���Ѵ�. 
	pclCI->clQuestInfo.clSpecialQuestInfo.clQuestRewardInfo.Set(&clrewardinfo);

	return true;
}

// Ư�� ����Ʈ�� �����. (�������)
bool cltCharServer::MakeSpecialQuest()
{
	SI32 questtype = QUEST_TYPE_SPECIAL;

	// ���� Ư�� ����Ʈ��  �����Ѵ�. 
	pclCI->clQuestInfo.clSpecialQuestInfo.Init();
	pclCI->clQuestInfo.clUnit[questtype].Init();

	bool bsuccess = false;

	srand( (unsigned)time( NULL ) );


	// 5% Ȯ���� ���� ��
	if ( rand() % 100 < 5 ) 
		return false;


	for ( SI32 i = 0; i < 3 ; ++i )
	{
		SI32 sirand = rand() % 13;
		switch( sirand )
		{
		case 0:
		case 9:
		case 10:
			if(MakeSpecialQuest_Battle() == true)bsuccess = true;
			break;
		case 1:
			// �������.  
			if(MakeSpecialQuest_Farm() == true)bsuccess	= true;
			break;
		case 2:
			// �����ϱ�.
			if(MakeSpecialQuest_Fish() == true)bsuccess	= true;
			break;
		case 3:
			// ä���ϱ�.
			if(MakeSpecialQuest_Mine() == true)bsuccess	= true;
			break;
		case 4:
			// ��� �ø��� 
			if(MakeSpecialQuest_Skill() == true)bsuccess = true;
			break;
		case 5:
			// ���� ����غ���.
			if(MakeSpecialQuest_UseItem() == true)bsuccess	= true;
			break;
		case 6:
			// ģ�� �����. 
			if(MakeSpecialQuest_MakeFriend() == true)bsuccess = true;
			break;
		case 7:
			// ��ǰ ��������
			if(MakeSpecialQuest_GetItem() == true)bsuccess = true;
			break;
		case 8:
			// ��ǰ �����ϱ�
			if(MakeSpecialQuest_MakeItem() == true)bsuccess = true;
			break;
		case 11:
			// ���� ��ȸ�ϱ�.
			if(MakeSpecialQuest_Gomap() == true )bsuccess = true;
			break;
		case 12:
			// ����ġ 1 �ø���.
			if(MakeSpecialQuest_MakeSkillExpup() == true )bsuccess = true;
			break;
		default:
			bsuccess = false;
			break;
		}
		if ( bsuccess  ) break;
	}

	if ( bsuccess == false )
		return false;

	cltQuestInfoCommon* pclquestinfo = &pclCI->clQuestInfo.clSpecialQuestInfo;

	// ���� �������� ����Ʈ ������ ����Ѵ�. 
	pclCI->clQuestInfo.clUnit[questtype].siCurQuestUnique	= 1;
	pclCI->clQuestInfo.clUnit[questtype].siQuestCmd		= pclquestinfo->clQuestClearConditionInfo.siFlag;
	pclCI->clQuestInfo.clUnit[questtype].siCurQuestStep	= QUEST_STEP_MIDDLE;


	// Ư�� ����Ʈ ������ �����Ѵ�. 
	// DB�� ����Ʈ�� ���¸� �����Ѵ�. 
#ifdef _SAFE_MEMORY
	sDBRequest_SetSpecialQuestInfo clMsg1(pclCI->GetPersonID(), &pclCI->clQuestInfo.clSpecialQuestInfo, &pclCI->clQuestInfo.bWordAssemblySwitch[0]);
#else
	sDBRequest_SetSpecialQuestInfo clMsg1(pclCI->GetPersonID(), &pclCI->clQuestInfo.clSpecialQuestInfo, pclCI->clQuestInfo.bWordAssemblySwitch);
#endif
	pclClient->SendDBMsg(DBSELECT_SUB, (sPacketHeader*)&clMsg1);

	sDBRequest_SetQuestInfo clMsg2(pclCI->GetPersonID(), questtype, &pclCI->clQuestInfo.clUnit[questtype]);
	pclClient->SendDBMsg(DBSELECT_SUB, (sPacketHeader*)&clMsg2);

	// Ŭ���̾�Ʈ�� ����Ʈ�� ���¸� �뺸�Ѵ�. 
	SetUpdateSwitch(UPDATE_QUEST, true, 0);

	// Ư���ӹ��� ������ Ŭ���̾�Ʈ�� ������ ȭ�鿡 ǥ���� �� �ְ� �Ѵ�. 
	cltGameMsgResponse_SpeicalQuestMade clinfo( &pclCI->clQuestInfo.clSpecialQuestInfo);
	cltMsg clMsg3(GAMEMSG_RESPONSE_SPECIALQUESTMADE, sizeof(clinfo), (BYTE*)&clinfo);
	SendNetMsg((sPacketHeader*)&clMsg3);


	return true;
}
bool cltCharServer::MakeNamingQuest( SI32 index, SI32 level )
{
	if ( index < 0 || index >= MAX_NAMINGQUEST_INDEX )
		return false ;

	if ( level > pclClient->pclNamingQuestManager->GetMaxLevel( index ) )
		return false ;

	if ( level-1 != pclCI->clPersonNaming.m_siLevel[index] )	// ���� �ܰ��� ����Ʈ�� �ƴϸ�.
		return false ;
	cltNamingQuestUnit* pclUnit = pclClient->pclNamingQuestManager->GetQuestInfo(index, level);

	if ( pclUnit == NULL )
		return false;

	// ���� Ư�� ����Ʈ��  �����Ѵ�. 
	pclCI->clQuestInfo.clNamingQuestInfo.Init();
	pclCI->clQuestInfo.clUnit[QUEST_TYPE_NAMING].Init();

	// ����Ʈ�� ���� ������ ���Ѵ�. 
	pclCI->clQuestInfo.clNamingQuestInfo.clQuestClearConditionInfo.Set( pclUnit->GetQuestClerCond() );

	// ������ ���Ѵ�. 
	cltQuestRewardInfo clrewardinfo;
	clrewardinfo.siNamingIndex	= index;
	clrewardinfo.siNamingLevel	= level;

	pclCI->clQuestInfo.clNamingQuestInfo.clQuestRewardInfo.Set(&clrewardinfo);

	// ���� �������� ����Ʈ ������ ����Ѵ�. 
	pclCI->clQuestInfo.clUnit[QUEST_TYPE_NAMING].siCurQuestUnique	= 1;
	pclCI->clQuestInfo.clUnit[QUEST_TYPE_NAMING].siCurQuestStep		= QUEST_STEP_MIDDLE;
	pclCI->clQuestInfo.clUnit[QUEST_TYPE_NAMING].siQuestCmd			= pclUnit->GetQuestClerCond()->siFlag;

	// naming - ���̹� ����Ʈ ���¸� ����
	sDBRequest_SetNamingQuestInfo clMsg1(pclCI->GetPersonID(), &pclCI->clQuestInfo.clNamingQuestInfo );
	pclClient->SendDBMsg(DBSELECT_SUB, (sPacketHeader*)&clMsg1);

	// ����Ʈ ���¸� DB�� �����Ѵ�.
	sDBRequest_SetQuestInfo clMsg(pclCI->GetPersonID(), QUEST_TYPE_NAMING, &pclCI->clQuestInfo.clUnit[QUEST_TYPE_NAMING]);
	pclClient->SendDBMsg(DBSELECT_SUB, (sPacketHeader*)&clMsg);

	//// Ŭ���̾�Ʈ�� ����Ʈ�� ���¸� �뺸�Ѵ�. 
	SetUpdateSwitch(UPDATE_QUEST, true, 0);
	cltServer* pclserver = (cltServer*)pclClient;
	pclserver->SendServerResponseMsg(0, SRVAL_NAMINGQUEST_START_SUCCESS, 0, 0, GetCharID());

	return true;
}

// 2010�ų��̺�Ʈ - ���� ��� ����Ʈ�� �����.
bool cltCharServer::MakeQuest_RemoveUnLuckStatus_Battle()
{
	SI32 monkind	= pclClient->GetUniqueFromHash( TEXT("KIND_RACCON") );
	SI32 monnum		= 1;

	cltQuestRewardInfo clrewardinfo;

	// ������ �´� ������ ���Ϳ� ������ ���Ѵ�. 
	if(pclClient->pclKindInfoSet->FindGoodMonsterForRemoveUnLuckStatusQuest(pclCI->clIP.GetLevel(),&monkind, &monnum, &clrewardinfo) == false)
	{
		return false;
	}
//#ifdef _DEBUG
//	monnum = 1;
//#endif

	// ����Ʈ�� ���� ������ ���Ѵ�. 
	pclCI->clQuestInfo.clMissionQuestInfo.siUnique							=	MISSIONQUEST_UNIQUE_REMOVE_UNLUCK;
	pclCI->clQuestInfo.clMissionQuestInfo.clQuestClearConditionInfo.siFlag	=	QUEST_CLEAR_COND_KILLMON;
	pclCI->clQuestInfo.clMissionQuestInfo.clQuestClearConditionInfo.siPara1	=	monkind;
	pclCI->clQuestInfo.clMissionQuestInfo.clQuestClearConditionInfo.siPara2	=	monnum;

	// �̼� �Ϸ� ���� �ð��� �����Ѵ�
	pclCI->clQuestInfo.clMissionQuestInfo.SetLeftTime( 50000 );	// �ð����� ���� ���Ƿ� ����.

	// �������� �� �������� �̴´�.
	cltValuesRange* pDebuffReward = NULL;
	pDebuffReward = GetValuesWithRange(ItemValue_DebuffReward, sizeof(ItemValue_DebuffReward) / sizeof(cltValuesRange), 100);
	if(pDebuffReward == NULL)			return false;

	SI32 siItemUnique		= pDebuffReward->siPara1;	// ������ ����ũ
	SI32 siItemNum			= pDebuffReward->siPara2;	// ����
	SI32 siUseDate			= pDebuffReward->siPara3;	// �̿�Ⱓ

	// �������� ���� �������� ������ ���󳻿��� �߰�
	clrewardinfo.siItemUnique[0]	= ITEMUNIQUE( siItemUnique ); //����Ÿ�� ������
	clrewardinfo.siItemNum[0]		= siItemNum;
	clrewardinfo.siItemUseDate[0]	= siUseDate;

	// ������ ���Ѵ�. 
	pclCI->clQuestInfo.clMissionQuestInfo.clQuestRewardInfo.Set(&clrewardinfo);

	return true;
}

// 2010�ų��̺�Ʈ - ��ǰ �����ϱ� ����Ʈ�� �����.
bool cltCharServer::MakeQuest_RemoveUnLuckStatus_MakeItem()
{
	// 1. ĳ���� ������ ���Ѵ�.
	// 2. ĳ������ ������ ���� ���꽺ų�� �ʿ䷾(��ȹ������ �ٸ�)�� ���Ѵ�.
	// 3. ���꽺ų�� �ʿ䷾�� �������� ���ϸ� ��ǰ ���� ����Ʈ�� �ߵ����� �ʴ´�.

	SI16 siNeedMakeSkillLevel = 0;
	SI16 siCharacterLevel = pclCI->clIP.GetLevel();

	// ĳ���� ���� : 1~30 -> ������ �ߵ� ����
	// ĳ���� ���� : 31~60 -> �ʿ��� ���꽺ų ���� 1~ (1 �̻�)
	// ĳ���� ���� : 61~90 -> �ʿ��� ���꽺ų ���� 20~ (20 �̻�)
	// ĳ���� ���� : 91~120 -> �ʿ��� ���꽺ų ���� 40~ (40 �̻�)

	if ( 31 <= siCharacterLevel && 60 >= siCharacterLevel ) { siNeedMakeSkillLevel = 1; }
	else if ( 61 <= siCharacterLevel && 90 >= siCharacterLevel ) { siNeedMakeSkillLevel = 20; }
	else if ( 91 <= siCharacterLevel && 120 >= siCharacterLevel ) { siNeedMakeSkillLevel = 40; }
	else { return false; }

	// ĳ���Ͱ� ������ ���꽺ų�� ����(������ų/����)�� �˻��� ��Ű�� ������Ʈ�� �ߵ� ������ ������ �����ϴ��� üũ�Ѵ�.
	SI16 skilllist[] = {
		SKILL_MAKEMED,	
			SKILL_MAKEFOOD,	
			SKILL_MAKEARMOUR1,	
			SKILL_MAKEHELMET1,	
			SKILL_MAKESWORD1,	
			SKILL_MAKESPEAR1,	
			SKILL_MAKEAXE1,	
			SKILL_MAKESTAFF1,
			SKILL_MAKEBOW1,	
			SKILL_MAKEGUN1,	
			SKILL_MAKESHOES1,	
			SKILL_MAKEBELT1,	
			SKILL_MAKEDRESS1,	
			SKILL_MAKEIRON1,
			SKILL_MAKETOOL1,
			SKILL_MAKEHAT1,
			SKILL_ARTIFACT,
	};

	SI32 skillnum = sizeof(skilllist) / sizeof(SI16);

	SI16 skillbuffer[MAX_SKILL_NUMBER];
	SI16 skilllevelbuffer[MAX_SKILL_NUMBER];
	SI32 skillbufferindex = 0;
	for(SI32 i = 0;i < skillnum;i++)
	{
		SI32 tempskilllevel = pclCI->clCharSkill.GetTotalSkillLevel(skilllist[i], 0, NULL);

		if ( siNeedMakeSkillLevel <= tempskilllevel ) 
		{
			skillbuffer[skillbufferindex]		= skilllist[i];
			skilllevelbuffer[skillbufferindex]	= tempskilllevel;
			skillbufferindex++;
		}
	}

	if(skillbufferindex == 0)
	{
		return false;
	}

	// ����Ʈ �ߵ� ������ �����ϴ� ���꽺ų���� �̾Ƴ����� ���� �ϳ��� �����Ѵ�.
	SI32 index			= rand() % skillbufferindex;
	SI32 skillunique	= skillbuffer[index];
	SI32 skilllevel		= skilllevelbuffer[index];


	// Ư�� ����� ����� �ִ� ��ǰ�� ����Ʈ�� ���Ѵ�. 
	SI16 siitemlist[MAX_ITEMINFO_NUMBER];
	SI32 itemlistindex = 0;
	for(i = 0;i < MAX_ITEMINFO_NUMBER;i++)
	{

		if(pclClient->pclItemManager->pclItemInfo[i] == NULL)continue;
		if(pclClient->pclItemManager->pclItemInfo[i]->clSkillInfo.siSkill != skillunique)continue;
		if(pclClient->pclItemManager->pclItemInfo[i]->clSkillInfo.siSkillLevel > skilllevel)continue;
		if(pclClient->pclItemManager->pclItemInfo[i]->clSkillInfo.siSkillLevel < max(1, skilllevel/2) )continue;
		if(pclClient->pclItemManager->pclItemInfo[i]->clProductionInfo.clMaterial[0].siUnique == 0)continue;


		if(pclClient->pclItemManager->pclItemInfo[i]->CanMake_Skill(&pclCI->clCharSkill, &pclCI->clCharItem, &clPB.clTotalBA) == false)continue;

		siitemlist[itemlistindex] = pclClient->pclItemManager->pclItemInfo[i]->clItem.siUnique;
		itemlistindex++;
	}

	if(itemlistindex == 0) return false;

	// ĳ���� ������ ���������� �´� ����, ��� �� ���� ������ ���Ѵ�.
	SI32 makeitemunique = siitemlist[rand() % itemlistindex];
	SI32 makenum	= 6 + ( rand() % 15 );	// ���� ���� 6 ~ 20��.

	SI32 ref	= pclClient->pclItemManager->FindItemRefFromUnique(makeitemunique);
	if(ref <= 0)	return false;

	// ���� ������ ���� (�ϴ� ����)
	cltQuestRewardInfo	clrewardinfo;

	// �������� �� �������� �̴´�.
	cltValuesRange* pDebuffReward = NULL;
	pDebuffReward = GetValuesWithRange(ItemValue_DebuffReward, sizeof(ItemValue_DebuffReward) / sizeof(cltValuesRange), 100);
	if(pDebuffReward == NULL)			return false;

	SI32 siItemUnique		= pDebuffReward->siPara1;	// ������ ����ũ
	SI32 siItemNum			= pDebuffReward->siPara2;	// ����
	SI32 siUseDate			= pDebuffReward->siPara3;	// �̿�Ⱓ

	// �������� ���� �������� ������ ���󳻿��� �߰�
	clrewardinfo.siItemUnique[0]	= ITEMUNIQUE( siItemUnique ); //����Ÿ�� ������
	clrewardinfo.siItemNum[0]		= siItemNum;
	clrewardinfo.siItemUseDate[0]	= siUseDate;

	// ������� �ٰŴϱ� �߰�
	clrewardinfo.bDeBuff = true;

	// ����Ʈ�� ���� ������ ���Ѵ�. 
	pclCI->clQuestInfo.clMissionQuestInfo.siUnique							=	MISSIONQUEST_UNIQUE_REMOVE_UNLUCK;
	pclCI->clQuestInfo.clMissionQuestInfo.clQuestClearConditionInfo.siFlag	=	QUEST_CLEAR_COND_MAKEITEM;
	pclCI->clQuestInfo.clMissionQuestInfo.clQuestClearConditionInfo.siPara1	=	makeitemunique;
	pclCI->clQuestInfo.clMissionQuestInfo.clQuestClearConditionInfo.siPara2	=	makenum;

	// �̼� �Ϸ� ���� �ð��� �����Ѵ�
	pclCI->clQuestInfo.clMissionQuestInfo.SetLeftTime( 50000 );	// �ð����� ���� ���Ƿ� ����.

	// ������ ���Ѵ�. 
	pclCI->clQuestInfo.clMissionQuestInfo.clQuestRewardInfo.Set(&clrewardinfo);

	return true;
}

// 2010�ų��̺�Ʈ - NPC�� �����ϰ� �ִ� ����Ʈ�� �Ϸ��ϴ� ����Ʈ�� �����.
bool cltCharServer::MakeQuest_RemoveUnLuckStatus_NPCQuestComplete()
{
	SI32 siNPCKindUnique = -1;
	SI32 siQuestUnique = -1;

	SI16 i = 0;

	i = rand() % REMOVEUNLUCK_QUESTNPC_COUNT;

	if ( false == m_arRemoveUnluckQuest_NPC[i].IsEmpty() )
	{
		siQuestUnique = m_arRemoveUnluckQuest_Unique[i];
		siNPCKindUnique = pclClient->GetUniqueFromHash( ((TCHAR*)(m_arRemoveUnluckQuest_NPC[i])) );
	}
	else
	{
		return false;
	}

	// 	for ( i = 0; i < REMOVEUNLUCK_QUESTNPC_COUNT; ++i )
	// 	{
	// 		if ( true == m_arRemoveUnluckQuest_NPC[i].IsEmpty() ) continue;
	// 
	// 		siQuestUnique = m_arRemoveUnluckQuest_Unique[i];
	// 		if ( false == pclCI->clQuestInfo.IsClear( pclClient->pclQuestManager, siQuestUnique ) )
	// 		{
	// 			siNPCKindUnique = pclClient->GetUniqueFromHash( ((TCHAR*)(m_arRemoveUnluckQuest_NPC[i])) );
	// 			break;
	// 		}
	// 	}

	//////////////////////////////////////////////////////////////////////////

	cltQuestRewardInfo clrewardinfo;

	// �������� �� �������� �̴´�.
	cltValuesRange* pDebuffReward = NULL;
	pDebuffReward = GetValuesWithRange(ItemValue_DebuffReward, sizeof(ItemValue_DebuffReward) / sizeof(cltValuesRange), 100);
	if(pDebuffReward == NULL)			return false;

	SI32 siItemUnique		= pDebuffReward->siPara1;	// ������ ����ũ
	SI32 siItemNum			= pDebuffReward->siPara2;	// ����
	SI32 siUseDate			= pDebuffReward->siPara3;	// �̿�Ⱓ

	// �������� ���� �������� ������ ���󳻿��� �߰�
	clrewardinfo.siItemUnique[0]	= ITEMUNIQUE( siItemUnique ); //����Ÿ�� ������
	clrewardinfo.siItemNum[0]		= siItemNum;
	clrewardinfo.siItemUseDate[0]	= siUseDate;

	// ������� �ٰŴϱ� �߰�
	clrewardinfo.bDeBuff = true;

	// ����Ʈ�� ���� ������ ���Ѵ�. 
	pclCI->clQuestInfo.clMissionQuestInfo.siUnique				=	MISSIONQUEST_UNIQUE_REMOVE_UNLUCK;
	pclCI->clQuestInfo.clMissionQuestInfo.clQuestClearConditionInfo.siFlag	=	QUEST_CLEAR_COND_CLEARQUEST;
	pclCI->clQuestInfo.clMissionQuestInfo.clQuestClearConditionInfo.siPara1	=	siQuestUnique;
	pclCI->clQuestInfo.clMissionQuestInfo.clQuestClearConditionInfo.siPara2	=	siNPCKindUnique;

	// �̼� �Ϸ� ���� �ð��� �����Ѵ�
	pclCI->clQuestInfo.clMissionQuestInfo.SetLeftTime( 50000 );	// �ð����� ���� ���Ƿ� ����.

	// ������ ���Ѵ�. 
	pclCI->clQuestInfo.clMissionQuestInfo.clQuestRewardInfo.Set(&clrewardinfo);

	return true;
} 

// 2010�ų��̺�Ʈ - �� ������ �������� �����ϴ� ����Ʈ�� �����.
bool cltCharServer::MakeQuest_RemoveUnLuckStatus()
{
	SI32 questtype = QUEST_TYPE_MISSION1;

	// ���� ����Ʈ���� �����Ѵ�.
	pclCI->clQuestInfo.clMissionQuestInfo.Init();
	pclCI->clQuestInfo.clUnit[QUEST_TYPE_MISSION1].Init();

	bool bSuccess = false;

	srand( (unsigned)time( NULL ) );

	for( SI32 i = 0; i < 3; i++ )	// 3������ �õ�.
	{
		SI32 sirand = rand() % 3;
		switch( sirand )
		{
		case 0:
			// ���� ����Ʈ.
			if( MakeQuest_RemoveUnLuckStatus_Battle() == true )bSuccess = true;
			break;
		case 1:
			// ��ǰ �����ϱ�.
			if( MakeQuest_RemoveUnLuckStatus_MakeItem() == true )bSuccess = true;
			break;
		case 2:
			// NPC�� �����ϴ� ����Ʈ �Ϸ��ϱ�.
			if( MakeQuest_RemoveUnLuckStatus_NPCQuestComplete() == true )bSuccess = true;
			break;
		default:
			bSuccess = false;
			break;
		}
		if( bSuccess ) break;
	}

	if ( bSuccess == false )
		return false;

	return true;
}

bool cltCharServer::Make_GoonzuDayMission()
{
	SI32 questtype = QUEST_TYPE_MISSION1;

	// ���� ����Ʈ���� �����Ѵ�.
	pclCI->clQuestInfo.clMissionQuestInfo.Init();
	pclCI->clQuestInfo.clUnit[QUEST_TYPE_MISSION1].Init();

	bool bSuccess = false;

	//srand( (unsigned)time( NULL ) ); // ������ �̼� ��� �޾����� ������ �ּ�ó��. 

	for( SI32 i = 0; i < 5; i++ )	// 3������ �õ�.
	{
		SI32 sirand = rand() % 4;
		switch( sirand )
		{
		case 0:
			// ���ֵ��� ���� ����Ʈ.
			if( Make_GoonzuDayMission_Battle() == true )bSuccess = true;
			break;
		case 1:
			// ���ֵ��� ��ǰ �����ϱ�.
			if( Make_GoonzuDayMission_MakeItem() == true )bSuccess = true;
			break;
		case 2:
			// ���ֵ��� ��� �����ϱ�.
			if( Make_GoonzuDayMission_Collect() == true )bSuccess = true;
			break;
		case 3:
			// ���ֵ��� ������ ����ϱ�.
			if( Make_GoonzuDayMission_UseItem() == true )bSuccess = true;
			break;
		default:
			bSuccess = false;
			break;
		}
		if( bSuccess ) break;
	}

	if ( bSuccess == false )
		return false;

	//////////////////////////////////////////////////////////////////////////
	// �̼� �Ϸ� ���� �ð��� �����Ѵ�
	pclCI->clQuestInfo.clMissionQuestInfo.SetLeftTime( 10800 );	// �̼� ���� �ð� 3�ð�. (3600 * 3)

	// ����Ʈ ����
	SI32 siLevel = 0;
	siLevel = pclCI->clIP.GetLevel();
	cltQuestRewardInfo clrewardinfo;
	if ( MAX_CHARACTER_LEVEL <= siLevel )
	{
		clrewardinfo.siItemUnique[0]	= ITEMUNIQUE(3880); // ������ ����
		clrewardinfo.siItemNum[0]		= 1;		// ������ ����
		clrewardinfo.siExp				= 0;
	}
	else
	{
		SI64 siCalcExp = (clPB.GetNextExp() - clPB.GetPrevExp()) * 0.01;
		clrewardinfo.siExp = ( MAX_SI32< siCalcExp ) ? MAX_SI32: (SI32)siCalcExp;
		
	}	

	// ������ �����Ѵ�.
	pclCI->clQuestInfo.clMissionQuestInfo.clQuestRewardInfo.Set(&clrewardinfo);
	//////////////////////////////////////////////////////////////////////////
	

	// ��� �����ϰ� Ŭ���� ����Ʈ ������ ���Ž�Ų��.
	pclCI->clQuestInfo.clUnit[QUEST_TYPE_MISSION1].siCurQuestUnique		= pclCI->clQuestInfo.clMissionQuestInfo.siUnique;
	pclCI->clQuestInfo.clUnit[QUEST_TYPE_MISSION1].siQuestCmd			= pclCI->clQuestInfo.clMissionQuestInfo.clQuestClearConditionInfo.siFlag;
	pclCI->clQuestInfo.clUnit[QUEST_TYPE_MISSION1].siCurQuestStep		= QUEST_STEP_MIDDLE;

	// �̼� ����Ʈ ������ DB�� �����Ѵ�.
	sDBRequest_SetMissionQuestInfo clMissionQuestInfo(pclCI->GetPersonID(), &pclCI->clQuestInfo.clMissionQuestInfo );
	pclClient->SendDBMsg(DBSELECT_SUB, (sPacketHeader*)&clMissionQuestInfo);

	// ����Ʈ ���¸� DB�� �����Ѵ�.
	sDBRequest_SetQuestInfo clQuestInfo(pclCI->GetPersonID(), QUEST_TYPE_MISSION1, &pclCI->clQuestInfo.clUnit[QUEST_TYPE_MISSION1]);
	pclClient->SendDBMsg(DBSELECT_SUB, (sPacketHeader*)&clQuestInfo);

	// Ŭ���̾�Ʈ�� ����Ʈ�� ���¸� �뺸�Ѵ�. 
	SetUpdateSwitch(UPDATE_QUEST, true, 0);

	// Ŭ�� ���� �̼��� �뺸�Ѵ�.
	cltGameMsgResponse_GoonzuDayMissionMade clinfo( &pclCI->clQuestInfo.clMissionQuestInfo );
	cltMsg clMsg3(GAMEMSG_RESPONSE_GOONZUDAYMISSION, sizeof(clinfo), (BYTE*)&clinfo);
	SendNetMsg((sPacketHeader*)&clMsg3);

	return true;
}

// ���ֵ��̹̼� - ��������Ʈ
bool cltCharServer::Make_GoonzuDayMission_Battle()
{
	SI32 monkind = pclClient->GetUniqueFromHash( TEXT ("KIND_RACCON") );
	SI32 monnum = 1;

	// ������ �´� ������ ���Ϳ� ������ ���Ѵ�.
	if( pclClient->pclKindInfoSet->FindGoodMonsterForGoonzuDay(pclCI->clIP.GetLevel(),&monkind, &monnum ) == false)
	{
		return false;
	}

#ifdef _DEBUG
	monnum = 1;
#endif

	// ����Ʈ�� ���� ������ ���Ѵ�. 
	pclCI->clQuestInfo.clMissionQuestInfo.siUnique							=	MISSIONQUEST_UNIQUE_GOONZUDAY;
	pclCI->clQuestInfo.clMissionQuestInfo.clQuestClearConditionInfo.siFlag	=	QUEST_CLEAR_COND_KILLMON;
	pclCI->clQuestInfo.clMissionQuestInfo.clQuestClearConditionInfo.siPara1	=	monkind;
	pclCI->clQuestInfo.clMissionQuestInfo.clQuestClearConditionInfo.siPara2	=	monnum;

	return true;
}

// ���ֵ��̹̼� - �����۸����.
bool cltCharServer::Make_GoonzuDayMission_MakeItem()
{
	SI16 skilllist[] = {
		SKILL_MAKEMED,	
			SKILL_MAKEFOOD,	
			SKILL_MAKEARMOUR1,	
			SKILL_MAKEHELMET1,	
			SKILL_MAKESWORD1,	
			SKILL_MAKESPEAR1,	
			SKILL_MAKEAXE1,	
			SKILL_MAKESTAFF1,
			SKILL_MAKEBOW1,	
			SKILL_MAKEGUN1,	
			SKILL_MAKESHOES1,	
			SKILL_MAKEBELT1,	
			SKILL_MAKEDRESS1,	
			SKILL_MAKEIRON1,
			SKILL_MAKETOOL1,
			SKILL_MAKEHAT1,
			SKILL_ARTIFACT
	};


	SI32 skillnum = sizeof(skilllist) / sizeof(SI16);

	SI16 skillbuffer[MAX_SKILL_NUMBER];
	SI16 skilllevelbuffer[MAX_SKILL_NUMBER];
	SI32 skillbufferindex = 0;
	for(SI32 i = 0;i < skillnum;i++)
	{
		SI32 tempskilllevel = pclCI->clCharSkill.GetTotalSkillLevel(skilllist[i], 0, NULL);
		if(tempskilllevel == 0)continue;

		skillbuffer[skillbufferindex]		= skilllist[i];
		skilllevelbuffer[skillbufferindex]	= tempskilllevel;
		skillbufferindex++;
	}

	if(skillbufferindex == 0)
	{
		return false;
	}

	SI32 index			= rand() % skillbufferindex;
	SI32 skillunique	= skillbuffer[index];
	SI32 skilllevel		= min( 45, skilllevelbuffer[index] );


	// Ư�� ����� ����� �ִ� ��ǰ�� ����Ʈ�� ���Ѵ�. 
	SI16 siitemlist[MAX_ITEMINFO_NUMBER];
	SI32 itemlistindex = 0;
	for(i = 0;i < MAX_ITEMINFO_NUMBER;i++)
	{

		if(pclClient->pclItemManager->pclItemInfo[i] == NULL)continue;
		if(pclClient->pclItemManager->pclItemInfo[i]->clSkillInfo.siSkill != skillunique)continue;
		if(pclClient->pclItemManager->pclItemInfo[i]->clSkillInfo.siSkillLevel > skilllevel)continue;
		//if(pclClient->pclItemManager->pclItemInfo[i]->clSkillInfo.siSkillLevel < max(1, skilllevel/2) )continue;		// �������� ���� �������� ����°� ����Ʈ �������� ���ü��� �ִٸ� �̰� �ּ�
		if(pclClient->pclItemManager->pclItemInfo[i]->clProductionInfo.clMaterial[0].siUnique == 0)continue;


		if(pclClient->pclItemManager->pclItemInfo[i]->CanMake_Skill(&pclCI->clCharSkill, &pclCI->clCharItem, &clPB.clTotalBA) == false)continue;

		siitemlist[itemlistindex] = pclClient->pclItemManager->pclItemInfo[i]->clItem.siUnique;
		itemlistindex++;
	}

	if(itemlistindex == 0)return false;

	SI32 makeitemunique = siitemlist[rand() % itemlistindex];
	//SI32 makenum	= 3 + ( rand() % 3 ); // ���� ���� 3~5��.

	SI32 makenum = 2 + ( rand() % 7 );	  // ���� ���� 2~ 8��.

//#ifdef _DEBUG
//	SI32 makenum = 1;	
//#endif

	SI32 ref	= pclClient->pclItemManager->FindItemRefFromUnique(makeitemunique);
	if(ref <= 0)	return false;

	// ����Ʈ�� ���� ������ ���Ѵ�. 
	pclCI->clQuestInfo.clMissionQuestInfo.siUnique							=	MISSIONQUEST_UNIQUE_GOONZUDAY;
	pclCI->clQuestInfo.clMissionQuestInfo.clQuestClearConditionInfo.siFlag	=	QUEST_CLEAR_COND_MAKEITEM;
	pclCI->clQuestInfo.clMissionQuestInfo.clQuestClearConditionInfo.siPara1	=	makeitemunique;
	pclCI->clQuestInfo.clMissionQuestInfo.clQuestClearConditionInfo.siPara2	=	makenum;

	return true;
}

// ���ֵ��̹̼� - �����ۼ���.
bool cltCharServer::Make_GoonzuDayMission_Collect()
{
	SI32 itemunique	= 0;
	SI32 itemnum	= 1;

	SI16 itemtypelist[] = {
		ITEMTYPE_MINERAL,	
			ITEMTYPE_CLOTH,
			ITEMTYPE_TREE,
			ITEMTYPE_FOOD,
			ITEMTYPE_HEAL,
			ITEMTYPE_SEAFOOD,
			ITEMTYPE_ETC,
	};

	SI32 itemtypelistnum = sizeof(itemtypelist) / sizeof(SI16);

	SI16 itemtype = itemtypelist[ rand() % itemtypelistnum];


	cltQuestRewardInfo clrewardinfo;

	// �� �κ��� �ִ°��� �ٽ� ã�´�.
	for ( SI32 i=0; i < 3; ++i  )
	{
		itemunique = pclClient->pclMarketManager->GetRandomOrder( itemtype );

		if(itemunique <= 0) continue;

		if( pclClient->pclItemManager->IsItemInfoAtb( itemunique, ITEMINFOATB_NOTDAILYQUEST ) ) continue;

		// �� �κ��� ���� ��쿡�� ���̻� ã�� ����;
		if(pclCI->clCharItem.FindItemInv(itemunique) == false ) 
			break;
	}

	if ( 0 >= itemunique ) return false;

	itemnum = 5 + (rand() % 16);	// �������� 5 ~ 20��.

//#ifdef _DEBUG
//	itemnum = 1;	
//#endif

	// ����Ʈ�� ���� ������ ���Ѵ�. 
	pclCI->clQuestInfo.clMissionQuestInfo.siUnique							=	MISSIONQUEST_UNIQUE_GOONZUDAY;
	pclCI->clQuestInfo.clMissionQuestInfo.clQuestClearConditionInfo.siFlag	=	QUEST_CLEAR_COND_ITEM;
	pclCI->clQuestInfo.clMissionQuestInfo.clQuestClearConditionInfo.siPara1	=	itemunique;
	pclCI->clQuestInfo.clMissionQuestInfo.clQuestClearConditionInfo.siPara2	=	itemnum;

	return true;
}

// ���ֵ��̹̼� - �����ۻ��.
bool cltCharServer::Make_GoonzuDayMission_UseItem()
{
	SI32 siitemlist[] ={
		ITEMUNIQUE(2565),	ITEMUNIQUE(2570),	ITEMUNIQUE(2575),	ITEMUNIQUE(2685),
			ITEMUNIQUE(2580),	ITEMUNIQUE(2585),	ITEMUNIQUE(2590),	ITEMUNIQUE(2595),
			ITEMUNIQUE(2600),	ITEMUNIQUE(2605),	ITEMUNIQUE(2631),
			ITEMUNIQUE(2635),	ITEMUNIQUE(2675),	ITEMUNIQUE(2680),	ITEMUNIQUE(2681),	

			ITEMUNIQUE(3735),	ITEMUNIQUE(3740),	ITEMUNIQUE(3745),	ITEMUNIQUE(3750),
			ITEMUNIQUE(3755),	ITEMUNIQUE(3760),	ITEMUNIQUE(3765),	ITEMUNIQUE(3770),
			ITEMUNIQUE(3775),	ITEMUNIQUE(3780),	ITEMUNIQUE(3785),	ITEMUNIQUE(3790),
			ITEMUNIQUE(3795),	ITEMUNIQUE(3800),	ITEMUNIQUE(3805),	ITEMUNIQUE(3810),
			ITEMUNIQUE(3815),	ITEMUNIQUE(3820),	ITEMUNIQUE(3825),	ITEMUNIQUE(3830),
			ITEMUNIQUE(3835),	ITEMUNIQUE(3840),
	};

	SI32 itemlistnum	= sizeof(siitemlist) / sizeof(SI32);
	if(itemlistnum <= 0)return false;

	SI16 itemunique = siitemlist[ rand() % itemlistnum];

	SI16 itemnum = 5 + ( rand() % 16); // ��� ���� 5 ~ 20 ��.

//#ifdef _DEBUG
//	SI16 itemnum	= 1;
//#endif

	if ( 0 >= itemunique ) return false;

	cltItemPriceUnit* pclprice = pclClient->pclItemManager->pclItemPrice->GetPrice(pclClient->pclItemManager, itemunique);
	if(pclprice == NULL)return false;

	// ����Ʈ�� ���� ������ ���Ѵ�. 
	pclCI->clQuestInfo.clMissionQuestInfo.siUnique							=	MISSIONQUEST_UNIQUE_GOONZUDAY;
	pclCI->clQuestInfo.clMissionQuestInfo.clQuestClearConditionInfo.siFlag	=	QUEST_CLEAR_COND_USEITEM;
	pclCI->clQuestInfo.clMissionQuestInfo.clQuestClearConditionInfo.siPara1	=	itemunique;
	pclCI->clQuestInfo.clMissionQuestInfo.clQuestClearConditionInfo.siPara2	=	itemnum;

	return true;
}

//KHY - 0822 - ���Ǻ� ����Ʈ �߰�.
bool cltCharServer::MakeHappyBeanQuest()
{
	SI32 questtype = QUEST_TYPE_HAPPYBEAN;

	// ����  ���Ǻ� ����Ʈ �����Ѵ�. 
	pclCI->clQuestInfo.clHappyBeanQuestInfo.Init();
	pclCI->clQuestInfo.clUnit[questtype].Init();

	bool bsuccess = false;

	srand( (unsigned)time( NULL ) );

	for ( SI32 i = 0; i < 5 ; ++i ) // 5������ �õ�
	{
		// Ȯ�� ������ ���̱� ���� �ڵ� - by LEEKH 2007.09.04
		SI32 sirand = rand() % (4 * 100);//4; //����Ʈ �ټ��� ���� ����.

		if(sirand >= 300)
		{			
			// ���� ����Ʈ.
			if(MakeHappyBeanQuest_Battle() == true)bsuccess = true;
		}
		else if(sirand >= 200)
		{
			// ��� �ø��� 
			if(MakeHappyBeanQuest_Skill() == true)bsuccess = true;
		}
		else if(sirand >= 100)
		{
			// ��ǰ ��������
			if(MakeHappyBeanQuest_GetItem() == true)bsuccess = true;
		}
		else
		{
			// ��ǰ �����ϱ�
			if(MakeHappyBeanQuest_MakeItem() == true)bsuccess = true;
		}

		if ( bsuccess  ) break;
	}

	if ( bsuccess == false )
		return false;

	//cltQuestInfoCommon* pclquestinfo = &pclCI->clQuestInfo.clHappyBeanQuestInfo;

	//// ���� �������� ����Ʈ ������ ����Ѵ�. 
	//pclCI->clQuestInfo.clUnit[questtype].siCurQuestUnique	= 1;
	//pclCI->clQuestInfo.clUnit[questtype].siQuestCmd		= pclquestinfo->clQuestClearConditionInfo.siFlag;
	//pclCI->clQuestInfo.clUnit[questtype].siCurQuestStep	= QUEST_STEP_MIDDLE;

	//// ���Ǻ� ����Ʈ ������ �����Ѵ�. 
	//sDBRequest_SetHappyBeanQuestInfo clMsg1(pclCI->GetPersonID(), &pclCI->clQuestInfo.clHappyBeanQuestInfo );
	//pclClient->SendDBMsg(DBSELECT_SUB, (sPacketHeader*)&clMsg1);

	//// ����Ʈ ���¸� DB�� �����Ѵ�.
	//sDBRequest_SetQuestInfo clMsg(pclCI->GetPersonID(), questtype, &pclCI->clQuestInfo.clUnit[questtype]);
	//pclClient->SendDBMsg(DBSELECT_SUB, (sPacketHeader*)&clMsg);

	//// Ŭ���̾�Ʈ�� ����Ʈ�� ���¸� �뺸�Ѵ�. 
	//SetUpdateSwitch(UPDATE_QUEST, true, 0);
	return true;
}


//KHY - 0822 - ���Ǻ� ����Ʈ �߰�. ����.
bool cltCharServer::MakeHappyBeanQuest_Battle()
{
	SI32 monkind	= pclClient->GetUniqueFromHash( TEXT("KIND_RACCON") );
	SI32 monnum		= 1;

	cltQuestRewardInfo clrewardinfo;

	// ������ �´� ������ ���Ϳ� ������ ���Ѵ�. 
	if(pclClient->pclKindInfoSet->FindGoodMonsterForHappyBeanQuest(pclCI->clIP.GetLevel(),&monkind, &monnum, &clrewardinfo) == false)
	{
		return false;
	}
#ifdef _DEBUG
	monnum = 3;
#endif

	// ����Ʈ�� ���� ������ ���Ѵ�. 
	pclCI->clQuestInfo.clHappyBeanQuestInfo.clQuestClearConditionInfo.siFlag	=	QUEST_CLEAR_COND_KILLMON;
	pclCI->clQuestInfo.clHappyBeanQuestInfo.clQuestClearConditionInfo.siPara1	=	monkind;
	pclCI->clQuestInfo.clHappyBeanQuestInfo.clQuestClearConditionInfo.siPara2	=	monnum;

	// ������ ���Ѵ�. 
	pclCI->clQuestInfo.clHappyBeanQuestInfo.clQuestRewardInfo.Set(&clrewardinfo);

	return true;
}


//KHY - 0822 - ���Ǻ� ����Ʈ �߰�. ��ų��.
bool cltCharServer::MakeHappyBeanQuest_Skill()
{

	//������ ����� ã�´�. 
	SI32 skillunique;		// �÷��� �� �������. 
	SI32 upgradeskilllevel;	// �÷��� �� ��� ����. 

	srand( (unsigned)time( NULL ) );

#ifdef _SAFE_MEMORY
	if(pclCI->clCharSkill.GetRandSkillForUpgrade(pclClient->pclSkillManager, &pclCI->clCharItem.clItem[0], &skillunique, &upgradeskilllevel/*, NULL*/) == false)return false;
#else
	if(pclCI->clCharSkill.GetRandSkillForUpgrade(pclClient->pclSkillManager, pclCI->clCharItem.clItem, &skillunique, &upgradeskilllevel/*, NULL*/) == false)return false;
#endif

	cltQuestRewardInfo clrewardinfo;
	clrewardinfo.siItemUnique[0]	= ITEMUNIQUE(2770); //����Ÿ�� ������
	clrewardinfo.siItemNum[0]		= 1;

	SI32 sirand = rand() % 2; //+ 0 or +1

	// ����Ʈ�� ���� ������ ���Ѵ�. 
	pclCI->clQuestInfo.clHappyBeanQuestInfo.clQuestClearConditionInfo.siFlag	=	QUEST_CLEAR_COND_SKILL;
	pclCI->clQuestInfo.clHappyBeanQuestInfo.clQuestClearConditionInfo.siPara1	=	skillunique;
	pclCI->clQuestInfo.clHappyBeanQuestInfo.clQuestClearConditionInfo.siPara2	=	upgradeskilllevel+sirand; //��ų ������ 1~2�ø���.

	// ������ ���Ѵ�. 
	pclCI->clQuestInfo.clHappyBeanQuestInfo.clQuestRewardInfo.Set(&clrewardinfo);

	return true;

}


//KHY - 0822 - ���Ǻ� ����Ʈ �߰�. ��ǰ ��������.
bool cltCharServer::MakeHappyBeanQuest_GetItem()
{
	SI32 itemunique	= 0;
	SI32 itemnum	= 10;

	SI16 itemtypelist[] = {
		ITEMTYPE_MINERAL,	
			ITEMTYPE_CLOTH,
			ITEMTYPE_TREE,
	};

	srand( (unsigned)time( NULL ) );

	SI32 itemtypelistnum = sizeof(itemtypelist) / sizeof(SI16);

	SI16 itemtype = itemtypelist[ rand() % itemtypelistnum];


	// �� �κ��� �ִ°��� �ٽ� ã�´�.
	for ( SI32 i=0; i < 3; ++i  )
	{
		itemunique = pclClient->pclMarketManager->GetRandomOrder( itemtype );

		if(itemunique <= 0)
		{
			return false;
		}

		// �� �κ��� ���� ��쿡�� ���̻� ã�� ����;
		if(pclCI->clCharItem.FindItemInv(itemunique) == false ) 
			break;
	}

	SI32 sirand = rand() % 20; //+ 0 or +19

#ifdef _DEBUG
	itemnum = 3;
#else
	itemnum = itemnum +sirand ;
#endif

	cltQuestRewardInfo clrewardinfo;
	clrewardinfo.siItemUnique[0]	= ITEMUNIQUE(2770); //����Ÿ�� ������
	clrewardinfo.siItemNum[0]		= 1;

	// ����Ʈ�� ���� ������ ���Ѵ�. 
	pclCI->clQuestInfo.clHappyBeanQuestInfo.clQuestClearConditionInfo.siFlag	=	QUEST_CLEAR_COND_ITEM;
	pclCI->clQuestInfo.clHappyBeanQuestInfo.clQuestClearConditionInfo.siPara1	=	itemunique;
	pclCI->clQuestInfo.clHappyBeanQuestInfo.clQuestClearConditionInfo.siPara2	=	itemnum;

	// ������ ���Ѵ�. 
	pclCI->clQuestInfo.clHappyBeanQuestInfo.clQuestRewardInfo.Set(&clrewardinfo);

	return true;
}

//KHY - 0822 - ���Ǻ� ����Ʈ �߰�. ��ǰ �����ϱ�
bool cltCharServer::MakeHappyBeanQuest_MakeItem()
{

	SI16 skilllist[] = {
		SKILL_MAKEMED,	
			SKILL_MAKEFOOD,	
			SKILL_MAKEARMOUR1,	
			SKILL_MAKEHELMET1,	
			SKILL_MAKESWORD1,	
			SKILL_MAKESPEAR1,	
			SKILL_MAKEAXE1,	
			SKILL_MAKESTAFF1,
			SKILL_MAKEBOW1,	
			SKILL_MAKEGUN1,	
			SKILL_MAKESHOES1,	
			SKILL_MAKEBELT1,	
			SKILL_MAKEDRESS1,	
			SKILL_MAKEIRON1,
			SKILL_MAKETOOL1,
			SKILL_MAKEHAT1,
			SKILL_ARTIFACT,
	};


	SI32 skillnum = sizeof(skilllist) / sizeof(SI16);

	SI16 skillbuffer[MAX_SKILL_NUMBER];
	SI16 skilllevelbuffer[MAX_SKILL_NUMBER];
	SI32 skillbufferindex = 0;
	for(SI32 i = 0;i < skillnum;i++)
	{
		SI32 tempskilllevel = pclCI->clCharSkill.GetTotalSkillLevel(skilllist[i], 0, NULL);
		if(tempskilllevel == 0)continue;

		skillbuffer[skillbufferindex]		= skilllist[i];
		skilllevelbuffer[skillbufferindex]	= tempskilllevel;
		skillbufferindex++;
	}

	if(skillbufferindex == 0)
	{
		return false;
	}

	SI32 index			= rand() % skillbufferindex;
	SI32 skillunique	= skillbuffer[index];
	SI32 skilllevel		= skilllevelbuffer[index];


	// Ư�� ����� ����� �ִ� ��ǰ�� ����Ʈ�� ���Ѵ�. 
	SI16 siitemlist[MAX_ITEMINFO_NUMBER];
	SI32 itemlistindex = 0;
	for(i = 0;i < MAX_ITEMINFO_NUMBER;i++)
	{

		if(pclClient->pclItemManager->pclItemInfo[i] == NULL)continue;
		if(pclClient->pclItemManager->pclItemInfo[i]->clSkillInfo.siSkill != skillunique)continue;
		if(pclClient->pclItemManager->pclItemInfo[i]->clSkillInfo.siSkillLevel > skilllevel)continue;
		if(pclClient->pclItemManager->pclItemInfo[i]->clSkillInfo.siSkillLevel < max(1, skilllevel/2) )continue;
		if(pclClient->pclItemManager->pclItemInfo[i]->clProductionInfo.clMaterial[0].siUnique == 0)continue;


		if(pclClient->pclItemManager->pclItemInfo[i]->CanMake_Skill(&pclCI->clCharSkill, &pclCI->clCharItem, &clPB.clTotalBA) == false)continue;

		siitemlist[itemlistindex] = pclClient->pclItemManager->pclItemInfo[i]->clItem.siUnique;
		itemlistindex++;
	}

	if(itemlistindex == 0)return false;

	SI32 makeitemunique = siitemlist[rand() % itemlistindex];
	SI32 makenum	= 1 + ( rand() % 3 );

	SI32 ref	= pclClient->pclItemManager->FindItemRefFromUnique(makeitemunique);
	if(ref <= 0)	return false;

	cltQuestRewardInfo clrewardinfo;
	clrewardinfo.siItemUnique[0]	= ITEMUNIQUE(2770); //����Ÿ�� ������
	clrewardinfo.siItemNum[0]		= 1;


	// ����Ʈ�� ���� ������ ���Ѵ�. 
	pclCI->clQuestInfo.clHappyBeanQuestInfo.clQuestClearConditionInfo.siFlag	=	QUEST_CLEAR_COND_MAKEITEM;
	pclCI->clQuestInfo.clHappyBeanQuestInfo.clQuestClearConditionInfo.siPara1	=	makeitemunique;
	pclCI->clQuestInfo.clHappyBeanQuestInfo.clQuestClearConditionInfo.siPara2	=	makenum;

	// ������ ���Ѵ�. 
	pclCI->clQuestInfo.clHappyBeanQuestInfo.clQuestRewardInfo.Set(&clrewardinfo);

	return true;

}

bool cltCharServer::MakeMissionQuest(SI32 siMissionUnique)
{
	switch(siMissionUnique)
	{
	case MISSIONQUEST_UNIQUE_HOLLOWEEN:
		{
			MakeMissionQuest_Holloween();
		}
		break;
	case MISSIONQUEST_UNIQUE_REMOVE_UNLUCK:
		{
			MakeQuest_RemoveUnLuckStatus();
		}
		break;
	}

	return true;
}

enum HOLLOWEEN_MISSION
{
	HOLLOWEEN_MISSION_NONE,
	HOLLOWEEN_MISSION_HUNT,
	HOLLOWEEN_MISSION_MAKEITEM
};
bool cltCharServer::MakeMissionQuest_Holloween()
{
	bool bMakeQuest = false;
	SI32 siHolloweenMission = HOLLOWEEN_MISSION_NONE;
	SI32 siLevel = pclCI->clIP.GetLevel();
	SI32 i;

	SI32 siRand = rand() % 100;
	if(siRand >= 0 && siRand < 50)
	{
		siHolloweenMission = HOLLOWEEN_MISSION_HUNT;
	}
	else if (siRand >= 50 && siRand < 100)
	{
		siHolloweenMission = HOLLOWEEN_MISSION_MAKEITEM;
	}

	// 1 ~ 60 ���������� ������ ��� ����Ʈ�� �ο��Ѵ�.
	if( siLevel >= 1 && siLevel <= 60 )		siHolloweenMission = HOLLOWEEN_MISSION_HUNT;

	switch(siHolloweenMission)
	{
	case HOLLOWEEN_MISSION_HUNT:
		{
			SI32 siMinLevel = 0, siMaxLevel = 0;
			SI32 siKinds[512];
			SI32 siValidKinds[512];
			SI32 siValidKindCount = 0;
			SI32 siSelectedCharKind = 0;
			SI32 siSelectedCharLevel = 0;

			if		( siLevel >=  1 && siLevel <=  30 )		{	siMinLevel =  1;		siMaxLevel = 30;	}
			else if ( siLevel >= 31 && siLevel <=  60 )		{	siMinLevel = 31;		siMaxLevel = 60;	}
			else if ( siLevel >= 61 && siLevel <=  90 )		{	siMinLevel = 60;		siMaxLevel = 90;	}
			else if ( siLevel >= 91 && siLevel <= 100 )		{	siMinLevel = 60;		siMaxLevel = 100;	}
			else if ( siLevel >= 101 && siLevel <= 120 )	{	siMinLevel = 100;		siMaxLevel = 120;	}

			ZeroMemory(siKinds, sizeof(siKinds));
			ZeroMemory(siValidKinds, sizeof(siValidKinds));

			cltNPCManagerServer* pclNPCManagerServer = (cltNPCManagerServer*)pclClient->pclNPCManager;
			if(pclNPCManagerServer)
			{
				pclNPCManagerServer->GetKindLevel(siMinLevel, siMaxLevel, siKinds, 512);
				for(i=0; i<512; i++)
				{
					if( pclClient->pclKindInfoSet->IsValidKind(siKinds[i]) == false )		continue;
					if( pclClient->pclKindInfoSet->pclKI[siKinds[i]]->IsAtb(ATB_BOSS) )		continue;
					if( pclClient->pclKindInfoSet->pclKI[siKinds[i]]->IsAtb(ATB_DAILYQUEST | ATB_DAILYQUEST2) == false )	continue;

					siValidKinds[siValidKindCount] = siKinds[i];
					siValidKindCount++;
				}

				if( siValidKindCount > 0 )
				{
					SI32 siSelect = rand() % siValidKindCount;
					siSelectedCharKind = siValidKinds[siSelect];
					siSelectedCharLevel = pclClient->pclNPCManager->GetKindMaxLevel(siSelectedCharKind);
				}
			}

			if( siSelectedCharKind > 0 && siSelectedCharLevel > 0 )
			{
				// ���� �̼� ����Ʈ�� �����Ѵ�.
				pclCI->clQuestInfo.clMissionQuestInfo.Init();
				pclCI->clQuestInfo.clUnit[QUEST_TYPE_MISSION1].Init();

				SI32 siKillNum = (rand() % 41) + 10;	// 10 ~ 50 ����

				SI32 siCandyCountForLevel	= 1;
				SI32 siCandyCountForKillNum = 1;

				SI32 siDiffLevel = siSelectedCharLevel - siLevel;

				SI32 siQuestTimeSec = 1;

				if( siDiffLevel < -10 )							{	siCandyCountForLevel = 1;	}
				if( siDiffLevel >= -10 && siDiffLevel <= 10)	{	siCandyCountForLevel = 2;	}
				if( siDiffLevel > 10 )							{	siCandyCountForLevel = 3;	}

				if( siKillNum == 10 )							{	siCandyCountForKillNum = 1;	}
				if( siKillNum >= 11 && siKillNum <= 30 )		{	siCandyCountForKillNum = 2;	}
				if( siKillNum >= 31 && siKillNum <= 50 )		{	siCandyCountForKillNum = 3;	}

				if( siKillNum == 10 )							{	siQuestTimeSec = 15 * 60;	}
				if( siKillNum >= 11 && siKillNum <= 30 )		{	siQuestTimeSec = 30 * 60;	}
				if( siKillNum >= 31 && siKillNum <= 50 )		{	siQuestTimeSec = 60 * 60;	}

				// ���ο� ����Ʈ�� �����Ѵ�.
				pclCI->clQuestInfo.clMissionQuestInfo.siUnique							=	MISSIONQUEST_UNIQUE_HOLLOWEEN;
				pclCI->clQuestInfo.clMissionQuestInfo.clQuestClearConditionInfo.siFlag	=	QUEST_CLEAR_COND_KILLMON;
				pclCI->clQuestInfo.clMissionQuestInfo.clQuestClearConditionInfo.siPara1	=	siSelectedCharKind;
				pclCI->clQuestInfo.clMissionQuestInfo.clQuestClearConditionInfo.siPara2	=	siKillNum;

				pclCI->clQuestInfo.clMissionQuestInfo.SetLeftTime( siQuestTimeSec );

				pclCI->clQuestInfo.clMissionQuestInfo.clQuestRewardInfo.siItemUnique[0]	= ITEMUNIQUE(13050);	// ����
				pclCI->clQuestInfo.clMissionQuestInfo.clQuestRewardInfo.siItemNum[0]	= min(siCandyCountForLevel, siCandyCountForKillNum);

				bMakeQuest = true;
			}
		}
		break;
	case HOLLOWEEN_MISSION_MAKEITEM:
		{
			SI32 siMinSkillLevel = 0, siMaxSkillLevel = 0;
			SI16 siitemlist[MAX_ITEMINFO_NUMBER];
			SI32 itemlistindex = 0;

			if		( siLevel >= 61 && siLevel <=  90 )		{	siMinSkillLevel = 1;		siMaxSkillLevel = 20;		}
			else if	( siLevel >= 91 && siLevel <= 100 )		{	siMinSkillLevel = 21;		siMaxSkillLevel = 100;		}
			else if	( siLevel >= 101 && siLevel <= 120 )	{	siMinSkillLevel = 21;		siMaxSkillLevel = 100;		}

			for(i = 0;i < MAX_ITEMINFO_NUMBER;i++)
			{
				cltItemInfo* pclItemInfo = pclClient->pclItemManager->pclItemInfo[i];

				if(pclItemInfo == NULL)												continue;

				if(pclItemInfo->clSkillInfo.siSkillLevel < siMinSkillLevel )		continue;
				if(pclItemInfo->clSkillInfo.siSkillLevel > siMaxSkillLevel )		continue;
				if(pclItemInfo->clProductionInfo.clMaterial[0].siUnique == 0)		continue;
				// PCK : �������߿��� ��Ÿ�� �̺�Ʈ �������� �����Ѵ�. (09.08.28)
				if(pclItemInfo->siType == ITEMTYPE_ETC)								continue;
				if(pclItemInfo->siType == ITEMTYPE_EVENTITEM)						continue;

				siitemlist[itemlistindex] = pclItemInfo->clItem.siUnique;
				itemlistindex++;
			}

			SI32 siSelectedItemUnique = 0;
			SI32 siSelectedItemNum = 0;
			if( itemlistindex > 0 )
			{
				siSelectedItemUnique = siitemlist[rand() % itemlistindex];
				siSelectedItemNum = (rand() % 15) + 6;			// 6 ~ 20��
			}

			if( siSelectedItemUnique > 0 && siSelectedItemNum > 0 )
			{
				SI32 siQuestTimeSec = 60 * 60;		// 60��

				// ���ο� ����Ʈ�� �����Ѵ�.
				pclCI->clQuestInfo.clMissionQuestInfo.siUnique							=	MISSIONQUEST_UNIQUE_HOLLOWEEN;
				pclCI->clQuestInfo.clMissionQuestInfo.clQuestClearConditionInfo.siFlag	=	QUEST_CLEAR_COND_MAKEITEM;
				pclCI->clQuestInfo.clMissionQuestInfo.clQuestClearConditionInfo.siPara1	=	siSelectedItemUnique;
				pclCI->clQuestInfo.clMissionQuestInfo.clQuestClearConditionInfo.siPara2	=	siSelectedItemNum;

				pclCI->clQuestInfo.clMissionQuestInfo.SetLeftTime( siQuestTimeSec );

				pclCI->clQuestInfo.clMissionQuestInfo.clQuestRewardInfo.siItemUnique[0]	= ITEMUNIQUE(13050);	// ����
				pclCI->clQuestInfo.clMissionQuestInfo.clQuestRewardInfo.siItemNum[0]	= (rand() % 2) + 2;		// 2 ~ 3��

				bMakeQuest = true;
			}
		}
		break;
	}

	return bMakeQuest;
}