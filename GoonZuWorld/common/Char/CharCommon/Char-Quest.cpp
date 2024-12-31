#include "..\Common\CommonHeader.h"
#include "..\Common\Char\CharServer\Char-Server.h"
#include "..\Common\Char\KindInfo\KindInfo.h"
#include "..\..\Client\Client.h"
#include "Char\CharManager\CharManager.h"

#include "..\..\CommonLogic\MsgType-System.h"

// ä�� ����. 
#include "..\Client\Interface\DrawChat\DrawChatSurface.h"
#include "..\Client\Interface\DrawChat\DrawChat.h"

#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Person.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Item.h"
#include "..\Server\GameDBProcess\GameDBProcess.h"

#include "../CommonLogic//Feast/Feast.h"


//--------------------------
// Common
//-------------------------
#include "PersonInfo.h"

extern cltCommonLogic* pclClient;


// ���� �Ϸ���� ���� ���� ���� ����Ʈ�� ��Ʈ�� ã�´�. 
SI32 cltCharCommon::GetMinBit(SI32 type)
{
	if( type < 0 || type >= MAX_QUEST_TYPE)		return -1;

	SI32 i;
	SI32 minbit = -1;
	SI32 minunique = 1000000;

	SI32 tempdata = pclCI->clQuestInfo.clUnit[type].siQuestState;
	for(i = 0;i < MAX_QUEST_PER_TYPE_NUMBER;i++)
	{
		if((tempdata & 0x00000001) == 0)	// �� ���� ��Ʈ�� 0�� ��쿡, 
		{
			// �ش� ��Ʈ�� ����ũ�� ã�´�. 
			SI32 questunique = pclClient->pclQuestManager->GetUniqueFromBit(type, i);
			if(questunique)
			{
				// ����ũ�� �ּ� ����ũ�̸�, 
				if(questunique < minunique)
				{
					minunique	= questunique;
					minbit		= i;
				}
			}
		}

		tempdata = (tempdata >> 1);
		
	}

	return minbit;
}

// Ư�� ����ũ�� ����Ʈ�� �Ϸ��ߴ��� Ȯ���Ѵ�. 
bool cltCharCommon::ClearQuest(SI32 questunique)
{
	//---------------------------------
	// ����Ʈ�� Ÿ�԰� ��Ʈ�� ���´�.
	//---------------------------------
	cltQuestInfo* pclinfo = pclClient->pclQuestManager->GetQuestInfo(questunique);
	if(pclinfo == NULL)return false;


	SI32 questtype	= pclinfo->siType;
	if(questtype < 0 || questtype >= MAX_QUEST_TYPE)		return false;
	SI32 bit		= pclClient->pclQuestManager->GetBitFromUnique(questtype, questunique);

	//--------------------------------
	// ������� �ش� ����Ʈ ���¸� Ȯ���Ѵ�
	//--------------------------------
	cltPersonQuestUnitInfo* pclquestinfo = &pclCI->clQuestInfo.clUnit[questtype];
	if(pclquestinfo == NULL)			return false;
	
	if(pclquestinfo->GetBit(bit))
	{
		return true;
	}
	return false;
}

// �ӹ��� �Ϸ� ������ ������Ű�°�?
bool cltCharCommon::IsClearCondition(SI32 questtype, cltQuestClearConditionInfo* pclcond)
{
	SI32 i;
	
	if(questtype < 0 || questtype >= MAX_QUEST_TYPE)	return false;
	if(pclcond == NULL)return false;

	// ������ �׳� Ŭ���� �Ǵ� ����Ʈ �̴�. 
	if(pclcond->siFlag == QUEST_CLEAR_COND_NONE )	
	{
		return true;
	}

	// Status ���ʽ� �����̶��, 
	if(pclcond->siFlag == QUEST_CLEAR_COND_BONUSZERO)
	{
		if(pclCI->clIP.GetBonus()	== 0)	// ���ʽ� ��ġ�� ���ƾ� ���� ����. 
		{
			return true;
		}
	}
	// ��� ��ȯ���� Status ���ʽ� �����̶��, 
	if(pclcond->siFlag == QUEST_CLEAR_COND_SUMMONBONUS)
	{
		for(i = 0;i < MAX_SUMMON_OWN;i++)
		{
			if(pclCI->clSummonInfo.clSummon[i].siKind && pclCI->clSummonInfo.clSummon[i].clIP.GetBonus() )	// ���ʽ� ��ġ�� ���ƾ� ���� ����. 
			{
				return false;
			}
		}

		return true;
	}
	// ��� ���� �����̶��, 
	if(pclcond->siFlag == QUEST_CLEAR_COND_SKILLBONUSZERO)
	{
		if(pclCI->clIP.GetSkillBonus()	== 0)	// ���ʽ� ��ġ�� ���ƾ� ���� ����. 
		{
			return true;
		}
	}
	
	// ���� ��ƿ;� �Ѵ�. 
	if(pclcond->siFlag == QUEST_CLEAR_COND_MONEY)
	{
		if(pclCI->clIP.GetMoney()	>= pclcond->siPara2)	
		{
			return true;
		}
	}
	// ���� ���忡 �Ա��ؾ� �Ѵ�. 
	if(pclcond->siFlag == QUEST_CLEAR_COND_BANK)
	{
		if(pclCI->clBank.GetMoney() >= (GMONEY)pclcond->siPara2)	
		{
			return true;
		}
	}
	// ������� ���ؾ� �Ѵ�. 
	if(pclcond->siFlag == QUEST_CLEAR_COND_HUNGRY)
	{
		 if(pclCI->clQuestInfo.clUnit[questtype].siQuestPara2 > 0)
		 {
			 return true;
		 }
	}
	// ���⸦ �����Ѵ�. WEAPON1, 2 ���� �˻��Ѵ�.
	if(pclcond->siFlag == QUEST_CLEAR_COND_REPAIRWEAPON)
	{
		if(pclCI->clCharItem.clItem[PERSONITEM_WEAPON1].siUnique)	
		{
			if(pclCI->clCharItem.clItem[PERSONITEM_WEAPON1].GetDurability() >= pclCI->clCharItem.clItem[PERSONITEM_WEAPON1].GetMaxDurability(pclClient->pclItemManager))
			{
				return true;
			}
		}
		if(pclCI->clCharItem.clItem[PERSONITEM_WEAPON2].siUnique)	
		{
			if(pclCI->clCharItem.clItem[PERSONITEM_WEAPON2].GetDurability() >= pclCI->clCharItem.clItem[PERSONITEM_WEAPON2].GetMaxDurability(pclClient->pclItemManager))
			{
				return true;
			}
		}
	}
	
	// ������ �� �̻��� �Ѵ�. 
	if(pclcond->siFlag == QUEST_CLEAR_COND_LEVEL)
	{
		if(pclCI->clIP.GetLevel() >= pclcond->siPara2)	 
		{
			return true;
		}
	}
	// �������� �� �̻��� �Ѵ�. 
	if(pclcond->siFlag == QUEST_CLEAR_COND_FAMELEVEL)
	{
		if(pclCI->clIP.siFameLevel >= pclcond->siPara2)	 
		{
			return true;
		}
	}
	// ü���� ������ ȸ���Ǿ�� �Ѵ�. 
	if(pclcond->siFlag == QUEST_CLEAR_COND_FULLLIFE)
	{
		if(pclCI->clIP.GetLife() >= clPB.GetMaxLife())	 
		{
			return true;
		}
	}
	// �ֽ��� �����ؾ� �Ѵ�. 
	if(pclcond->siFlag == QUEST_CLEAR_COND_STOCK)
	{
		if(pclCI->clStock.clInfo.HaveStock() == true)
		{
			return true;
		}
	}
	// ģ���� �θ� ����ؾ� �Ѵ�. 
	if(pclcond->siFlag == QUEST_CLEAR_COND_MAKEFRIEND)
	{
		if( pclFriendInfo && pclFriendInfo->GetFriendNum() >= pclcond->siPara2 )
		{
			return true;
		}
	}
	
	// ���� ������ �Ѵ�. 
	if(pclcond->siFlag == QUEST_CLEAR_COND_HORSE)
	{
		if(pclCI->clHorseInfo.HaveHorse())
		{
			return true;
		}
	}
	// ��ȯ�� �������� 
	if(pclcond->siFlag == QUEST_CLEAR_COND_SUMMON)
	{
		if(pclCI->clSummonInfo.clSummon[0].siKind)
		{
			return true;
		}
	}
	// ��ȯ�� Ȱ��ȭ
	if(pclcond->siFlag == QUEST_CLEAR_COND_SUMMONACTIVE)
	{
		for ( SI32 siIndex=0; siIndex<MAX_SUMMON_OWN; ++siIndex )
		{
			SI32 siSummonKind	= pclCI->clSummonInfo.clSummon[siIndex].siKind;
			SI32 siSummonStatus	= pclCI->clSummonInfo.clSummon[siIndex].siStatus;

			if ( (0 < siSummonKind) && (MAX_KIND_NUMBER > siSummonKind) && (SUMMON_STATUS_TAKEOUT == siSummonStatus) )
			{
				return true;
			}
		}
	}

	if(pclcond->siFlag == QUEST_CLEAR_COND_SUMMONDIE )
	{
		for ( SI32 siIndex=0; siIndex<MAX_SUMMON_OWN; ++siIndex )
		{
			SI32 siSummonKind	= pclCI->clSummonInfo.clSummon[siIndex].siKind;
			SI32 siSummonStatus	= pclCI->clSummonInfo.clSummon[siIndex].siStatus;

			if ( (0 < siSummonKind) && (MAX_KIND_NUMBER > siSummonKind) && (SUMMON_STATUS_DEAD == siSummonStatus) )
			{
				return true;
			}
		}
	}

	// ��ȯ�� 2���� Ű���. 
	if(pclcond->siFlag == QUEST_CLEAR_COND_SUMMON2)
	{
		if(pclCI->clSummonInfo.clSummon[0].siKind && pclCI->clSummonInfo.clSummon[1].siKind)
		{
			return true;
		}
	}

	// ��ȯ�� ���� ���� �̻� ��ȭ ��Ű��
	if(pclcond->siFlag == QUEST_CLEAR_COND_SUMMONEVOLUTIONRANK)
	{
		for ( SI32 siIndex=0; siIndex<MAX_SUMMON_OWN; ++siIndex )
		{
			SI32 siSummonKind	= pclCI->clSummonInfo.clSummon[siIndex].siKind;
			SI32 siSummonStatus	= pclCI->clSummonInfo.clSummon[siIndex].siStatus;

			if ( (0 < siSummonKind) && (MAX_KIND_NUMBER > siSummonKind) && (SUMMON_STATUS_TAKEOUT == siSummonStatus) )
			{
				cltKindInfo* pclKindInfo = pclClient->pclKindInfoSet->pclKI[siSummonKind];
				// ���� ���� �ִ� ��ȯ���� ��ȭ ����� Ȯ���ؼ� Ŭ���� ���θ� �����Ѵ�.
				if ( (pclKindInfo) && (pclKindInfo->siSummonRank >= pclcond->siPara1) )
				{
					return true;
				}
			}
		}
	}

	// Ư�� ����� ������ �� �̻��̾�� �Ѵ�.
	if(pclcond->siFlag == QUEST_CLEAR_COND_SKILL)
	{
		SI32 skillunique = pclcond->siPara1;

#ifdef _SAFE_MEMORY
		if( pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0, &pclCI->clCharItem.clItem[0]) >=  pclcond->siPara2)
		
#else
		if( pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0, pclCI->clCharItem.clItem) >=  pclcond->siPara2)
			
#endif
		{
			return true;
		}
	}

	// [����] Ư�� ����� ���� ����ġ�� 1 ����Ʈ �̻� �Ǿ�� �Ѵ�.
	if(pclcond->siFlag == QUEST_CLEAR_COND_MAKESKILLEXPUP)
	{
		SI32 skillunique = pclcond->siPara1;

#ifdef _SAFE_MEMORY
		if( pclCI->clCharSkill.GetTotalSkillExp(skillunique) >= pclcond->siPara2 ) // ����ġ�� 1 �����ߴ����� ���� ���ǵ� �߰�.
#else
		if( pclCI->clCharSkill.GetTotalSkillExp(skillunique) >= pclcond->siPara2 )
#endif
		{
			return true;
		}
	}

	// �⺻ ��������� ������ �� �̻��̾�� �Ѵ�.
	if(pclcond->siFlag == QUEST_CLEAR_COND_BASICWEAPONSKILL)
	{
#ifdef _SAFE_MEMORY
		if(pclCI->clCharSkill.GetTotalSkillLevel(SKILL_USESWORD1,	0, 0, &pclCI->clCharItem.clItem[0])	>=  pclcond->siPara2 
		|| pclCI->clCharSkill.GetTotalSkillLevel(SKILL_USESPEAR1,	0, 0, &pclCI->clCharItem.clItem[0])	>=  pclcond->siPara2
		|| pclCI->clCharSkill.GetTotalSkillLevel(SKILL_USEAXE1,		0, 0, &pclCI->clCharItem.clItem[0])	>=  pclcond->siPara2
		|| pclCI->clCharSkill.GetTotalSkillLevel(SKILL_USEBOW1,		0, 0, &pclCI->clCharItem.clItem[0])	>=  pclcond->siPara2
		|| pclCI->clCharSkill.GetTotalSkillLevel(SKILL_USEGUN1,		0, 0, &pclCI->clCharItem.clItem[0])	>=  pclcond->siPara2
		|| pclCI->clCharSkill.GetTotalSkillLevel(SKILL_USESTAFF1,	0, 0, &pclCI->clCharItem.clItem[0])	>=  pclcond->siPara2)
#else
		if(pclCI->clCharSkill.GetTotalSkillLevel(SKILL_USESWORD1,	0, 0, pclCI->clCharItem.clItem)	>=  pclcond->siPara2 
		|| pclCI->clCharSkill.GetTotalSkillLevel(SKILL_USESPEAR1,	0, 0, pclCI->clCharItem.clItem)	>=  pclcond->siPara2
		|| pclCI->clCharSkill.GetTotalSkillLevel(SKILL_USEAXE1,		0, 0, pclCI->clCharItem.clItem)	>=  pclcond->siPara2
		|| pclCI->clCharSkill.GetTotalSkillLevel(SKILL_USEBOW1,		0, 0, pclCI->clCharItem.clItem)	>=  pclcond->siPara2
		|| pclCI->clCharSkill.GetTotalSkillLevel(SKILL_USEGUN1,		0, 0, pclCI->clCharItem.clItem)	>=  pclcond->siPara2
		|| pclCI->clCharSkill.GetTotalSkillLevel(SKILL_USESTAFF1,	0, 0, pclCI->clCharItem.clItem)	>=  pclcond->siPara2)
#endif
		{
			return true;
		}
	}

	///////////////
	// Ư�� ��ǰ�� ���� Ȯ��. 
	if(pclcond->siFlag == QUEST_CLEAR_COND_EQUIP)
	{

		SI32 itemunique = pclcond->siPara1;

		// ���â�߿� �ش� ��ǰ�� �ִ��� Ȯ���Ѵ�. 
		if(pclCI->clCharItem.HaveInEquip(itemunique) == true)
		{
			return true;
		}
	}
	// Ư�� ����â�� ��ǰ�� �ִ��� Ȯ��. 
	if(pclcond->siFlag == QUEST_CLEAR_COND_EQUIPPOS)
	{
		// ���â�߿� �ش� ��ǰ�� �ִ��� Ȯ���Ѵ�. 
		if( pclcond->siPara1 >= 0 && pclcond->siPara1 < MAX_ITEM_PER_PERSON &&
			pclCI->clCharItem.clItem[pclcond->siPara1].siUnique)
		{
			return true;
		}
	}
	
	// ���濡 ���� �־��. 
	if(pclcond->siFlag == QUEST_CLEAR_COND_BAG)
	{

		SI32 itemunique = pclcond->siPara1;

		// ���â�߿� �ش� ��ǰ�� �ִ��� Ȯ���Ѵ�. 
		if(pclCI->clCharItem.IsBagHaveItem() == true)
		{
			return true;
		}
	}

	if(pclcond->siFlag == QUEST_CLEAR_COND_SETFATHER )
	{
		if ( pclCI->clIP.GetLevel() >= 20 || pclCI->clBI.clFatherInfo.clFather.siPersonID > 0 )
		{
			return true ;
		}
	}

	// �λ縻 �����ϱ�
	if( pclcond->siFlag == QUEST_CLEAR_COND_SETGREETING )
	{
		if( _tcslen( pclCI->clBI.szGreeting ) > 0 )
		{
			return true;
		}
	}

	// ��� ����or����(��⵵ ����)
	if( pclcond->siFlag == QUEST_CLEAR_COND_APPLYGUILD )
	{
		if( pclCI->clBI.clGuildRank.siType > 0 )
		{
			return true;
		}
	}

	// ��Ƽ�� �ִٸ�
	if( pclcond->siFlag == QUEST_CLEAR_COND_MAKEPARTY )
	{
		if( siPartyIndex > 0)
		{
			return true;
		}
	}

	// ĳ���� ����â�� ���� �����̶��, 
	// ���â�� ������ �����̶��, 
	// NPC���� ������ �Ǹ��ϴ� �����̸�, 
	if(pclcond->siFlag == QUEST_CLEAR_COND_OPENCHARSTATUS 
	|| pclcond->siFlag == QUEST_CLEAR_COND_OPENSKILL
	|| pclcond->siFlag == QUEST_CLEAR_COND_SELLNPC
	|| pclcond->siFlag == QUEST_CLEAR_COND_ITEMINFO
	|| pclcond->siFlag == QUEST_CLEAR_COND_NEWS
	|| pclcond->siFlag == QUEST_CLEAR_COND_GOMAP
	|| pclcond->siFlag == QUEST_CLEAR_COND_LAMPGOMAP		// ������� ���� ��ȸ
	|| pclcond->siFlag == QUEST_CLEAR_COND_SELLMARKET
	|| pclcond->siFlag == QUEST_CLEAR_COND_SCROLL
	|| pclcond->siFlag == QUEST_CLEAR_COND_USEWENNYOLDMAN2
	|| pclcond->siFlag == QUEST_CLEAR_COND_FEEDHORSE1
	|| pclcond->siFlag == QUEST_CLEAR_COND_FEEDHORSE2
	|| pclcond->siFlag == QUEST_CLEAR_COND_STRUCTUREOPEN
	|| pclcond->siFlag == QUEST_CLEAR_COND_ITEMINFODLG
	|| pclcond->siFlag == QUEST_CLEAR_COND_SELLSWORDNPC
	|| pclcond->siFlag == QUEST_CLEAR_COND_OTHERMINIHOME
	|| pclcond->siFlag == QUEST_CLEAR_COND_BUYFROMPBSTORE
	|| pclcond->siFlag == QUEST_CLEAR_COND_OPENPBSTORE
	|| pclcond->siFlag == QUEST_CLEAR_COND_OPENSTOCKMARKET
	|| pclcond->siFlag == QUEST_CLEAR_COND_LOOKPANSEO
	|| pclcond->siFlag == QUEST_CLEAR_COND_OPENVILLAGEBOARD
	|| pclcond->siFlag == QUEST_CLEAR_COND_OPENCITYHALL
	|| pclcond->siFlag == QUEST_CLEAR_COND_APPLYVILLAGE
	|| pclcond->siFlag == QUEST_CLEAR_COND_USEFAN
	|| pclcond->siFlag == QUEST_CLEAR_COND_SENDITEMBYPOST
	|| pclcond->siFlag == QUEST_CLEAR_COND_REVIVESUMMON
	|| pclcond->siFlag == QUEST_CLEAR_COND_USEWENNYOLDMAN
	|| pclcond->siFlag == QUEST_CLEAR_COND_OPENHUNT
	|| pclcond->siFlag == QUEST_CLEAR_COND_SKILLMASTER
	|| pclcond->siFlag == QUEST_CLEAR_COND_BROADCAST
	|| pclcond->siFlag == QUEST_CLEAR_COND_USEWARPTICKET1
	|| pclcond->siFlag == QUEST_CLEAR_COND_USEWARPTICKET2
	|| pclcond->siFlag == QUEST_CLEAR_COND_DAILYQUEST
	|| pclcond->siFlag == QUEST_CLEAR_COND_SPECIALQUEST
	|| pclcond->siFlag == QUEST_CLEAR_COND_SUMMONEVOLUTION
	|| pclcond->siFlag == QUEST_CLEAR_COND_SUMMONSCROLL
	|| pclcond->siFlag == QUEST_CLEAR_COND_ITEMMALL 
	|| pclcond->siFlag == QUEST_CLEAR_COND_GONPC
	|| pclcond->siFlag == QUEST_CLEAR_COND_CLICKITEMINFO
	|| pclcond->siFlag == QUEST_CLEAR_COND_OPENMAKEITEM
	|| pclcond->siFlag == QUEST_CLEAR_COND_CLICKMAKEBUTTON
	|| pclcond->siFlag == QUEST_CLEAR_COND_OPENENCHANTITEM
	|| pclcond->siFlag == QUEST_CLEAR_COND_SETENCHANTITEM
	|| pclcond->siFlag == QUEST_CLEAR_COND_SETENCHANTELEMENT
	|| pclcond->siFlag == QUEST_CLEAR_COND_WARPTOPALACE
	|| pclcond->siFlag == QUEST_CLEAR_COND_BUYFROMPBSTORE
	|| pclcond->siFlag == QUEST_CLEAR_COND_PRIVATETRADE
	|| pclcond->siFlag == QUEST_CLEAR_COND_SELLFROMPBSTORE
	|| pclcond->siFlag == QUEST_CLEAR_COND_HUNTMAPINFODLG
	|| pclcond->siFlag == QUEST_CLEAR_COND_PARTYHUNTING
	|| pclcond->siFlag == QUEST_CLEAR_COND_MAGICINFODLG
	|| pclcond->siFlag == QUEST_CLEAR_COND_OPENHOUSE
	|| pclcond->siFlag == QUEST_CLEAR_COND_OPENREALESTATEMARKET
	|| pclcond->siFlag == QUEST_CLEAR_COND_BLACKARMY
	|| pclcond->siFlag == QUEST_CLEAR_COND_OPENHORSEMARKET
	|| pclcond->siFlag == QUEST_CLEAR_COND_REVIVESUMMONBYDOLL
	|| pclcond->siFlag == QUEST_CLEAR_COND_OPENHOZODLG
	|| pclcond->siFlag == QUEST_CLEAR_COND_OPENBYUNGZODLG
	|| pclcond->siFlag == QUEST_CLEAR_COND_OPENGONGZODLG
	|| pclcond->siFlag == QUEST_CLEAR_COND_OPENIZODLG
	|| pclcond->siFlag == QUEST_CLEAR_COND_OPENGOONZUDLG
	|| pclcond->siFlag == QUEST_CLEAR_COND_VOTEKING
	|| pclcond->siFlag == QUEST_CLEAR_COND_MAKEBOOK
	|| pclcond->siFlag == QUEST_CLEAR_COND_SEARCHMONSTERINFO
	|| pclcond->siFlag == QUEST_CLEAR_COND_USEWARPTICKET3
	|| pclcond->siFlag == QUEST_CLEAR_COND_USEMAGIC
	|| pclcond->siFlag == QUEST_CLEAR_COND_BUYTOPBSTORE
	|| pclcond->siFlag == QUEST_CLEAR_COND_VILLAGEDETAILINFO
	|| pclcond->siFlag == QUEST_CLEAR_COND_ENCHANTANYITEM
	|| pclcond->siFlag == QUEST_CLEAR_COND_OPENFRIEND
	|| pclcond->siFlag == QUEST_CLEAR_COND_OPENMASTER
	|| pclcond->siFlag == QUEST_CLEAR_COND_OPENMAKEREQUEST
	|| pclcond->siFlag == QUEST_CLEAR_COND_MAKEREQUESTSTART
	|| pclcond->siFlag == QUEST_CLEAR_COND_OPENNAMINGQUEST
	|| pclcond->siFlag == QUEST_CLEAR_COND_DISASSEMBLEITEM
	|| pclcond->siFlag == QUEST_CLEAR_COND_SUMMONCHANGESTATUS
	|| pclcond->siFlag == QUEST_CLEAR_COND_SUMMONATTACK
	|| pclcond->siFlag == QUEST_CLEAR_COND_SUMMONLEVELUP
	|| pclcond->siFlag == QUEST_CLEAR_COND_MAKEINTBOOK
	|| pclcond->siFlag == QUEST_CLEAR_COND_MAGICACTIVE
	|| pclcond->siFlag == QUEST_CLEAR_COND_GOHUNTMAP
	|| pclcond->siFlag == QUEST_CLEAR_COND_OPENGUILD
	|| pclcond->siFlag == QUEST_CLEAR_COND_LOOKPRISON
	|| pclcond->siFlag == QUEST_CLEAR_COND_OPENGOONZUDLG_NOTICE
	|| pclcond->siFlag == QUEST_CLEAR_COND_SORTRESIDENT
	|| pclcond->siFlag == QUEST_CLEAR_COND_CLICKITEMPROPERTY
	|| pclcond->siFlag == QUEST_CLEAR_COND_OPENSKILLETC
	|| pclcond->siFlag == QUEST_CLEAR_COND_SITDOWN
	|| pclcond->siFlag == QUEST_CLEAR_COND_NPCINFO
	|| pclcond->siFlag == QUEST_CLEAR_COND_OPENGUILDUSER	
	|| pclcond->siFlag == QUEST_CLEAR_COND_SEARCHMONSTERINFO
	|| pclcond->siFlag == QUEST_CLEAR_COND_SEARCHSTOCKINFO
	|| pclcond->siFlag == QUEST_CLEAR_COND_CLICKSTOCKOFFER
	|| pclcond->siFlag == QUEST_CLEAR_COND_CLICKCITYHALLFUND
	|| pclcond->siFlag == QUEST_CLEAR_COND_CLICKGENERALMETTING
	|| pclcond->siFlag == QUEST_CLEAR_COND_CLICKPERSONALSHOP
	|| pclcond->siFlag == QUEST_CLEAR_COND_OPENITEMMALL
	|| pclcond->siFlag == QUEST_CLEAR_COND_ANGELLISTCLICK
	|| pclcond->siFlag == QUEST_CLEAR_COND_POLICESETCLICK
	|| pclcond->siFlag == QUEST_CLEAR_COND_SEARCHFARM
	|| pclcond->siFlag == QUEST_CLEAR_COND_LEASECLICK
	|| pclcond->siFlag == QUEST_CLEAR_COND_OPENQUESTDIALOG
	|| pclcond->siFlag == QUEST_CLEAR_COND_TAKEPUPILS
	|| pclcond->siFlag == QUEST_CLEAR_COND_CHATTOBEGGINER
	|| pclcond->siFlag == QUEST_CLEAR_COND_MEMOCLICK
	|| pclcond->siFlag == QUEST_CLEAR_COND_MOVETOGROUPCLICK
	|| pclcond->siFlag == QUEST_CLEAR_COND_REQUESTMENTORSUCCESS
	|| pclcond->siFlag == QUEST_CLEAR_COND_OPENFATHERDIALOG
	|| pclcond->siFlag == QUEST_CLEAR_COND_ORDERTOMARKET
	|| pclcond->siFlag == QUEST_CLEAR_COND_OPENPOSTOFFICEDIALOG
	|| pclcond->siFlag == QUEST_CLEAR_COND_TEACHERSET
	|| pclcond->siFlag == QUEST_CLEAR_COND_SWORDSKILLCLICK
	|| pclcond->siFlag == QUEST_CLEAR_COND_PVPWIN
	|| pclcond->siFlag == QUEST_CLEAR_COND_PVPLEAGUERESERVE
	|| pclcond->siFlag == QUEST_CLEAR_COND_PVPLEAGUEWIN
	|| pclcond->siFlag == QUEST_CLEAR_COND_SETMYKEY
	|| pclcond->siFlag == QUEST_CLEAR_COND_SUMMONHOUSE_INPUT
	|| pclcond->siFlag == QUEST_CLEAR_COND_SUMMONHOUSE_OUTPUT
	|| pclcond->siFlag == QUEST_CLEAR_COND_MARKETCONDITION
	|| pclcond->siFlag == QUEST_CLEAR_COND_BUFFCLICK
	|| pclcond->siFlag == QUEST_CLEAR_COND_GONPC_INFORMATION
	|| pclcond->siFlag == QUEST_CLEAR_COND_MAKESKILLEXPUP
	|| pclcond->siFlag == QUEST_CLEAR_COND_TRANSMONSTERTRICERAMONS
	|| pclcond->siFlag == QUEST_CLEAR_COND_SEARCH_TOTALMAP
	) 
	{
		if(pclcond->siPara1 == pclCI->clQuestInfo.clUnit[questtype].siQuestPara1
		&& pclcond->siPara2 == pclCI->clQuestInfo.clUnit[questtype].siQuestPara2)
		{
			return true;
		}
		
		// �����۸� �����ϱ� ����Ʈ ���ε�SBSȸ���̸�,  
		if(pclcond->siFlag == QUEST_CLEAR_COND_ITEMMALL)
		{
			if(IsSBS())return true;
		}
		
		// ���� �ֹ� ��û ����Ʈ ���ε� �̹� ���� �ֹ��̸�, 
		if(pclcond->siFlag == QUEST_CLEAR_COND_APPLYVILLAGE)
		{
			if(pclCI->clBI.siHomeVillage)return true;
		}
		

		// �ʺ��ڻ���� ���� ����Ʈ�̰� �������� ������ �ɷ� �ִٸ�, 
		// ���ǹ� ���� - by LEEKH 2007.11.21
		if(pclcond->siFlag == QUEST_CLEAR_COND_GOMAP)
		{
			if( pclCI->clQuestInfo.clUnit[questtype].siQuestPara1 == MAPINDEX_BEGINNER1 )
			{
				// �ʺ��� ����Ϳ� ���� ����Ʈ�ε�
				// ĳ������ ���� ������ ����Ϳ� �� ���� ��� �׳� PASS
				if( pclCI->clIP.GetLevel() > MAX_LEVEL_FOR_BEGINNERMAP )
				{
					return true;
				}
			}
		}

		// ȣǰ ����Ʈ�ε� �̹� ������ �ִٸ�
		if(pclcond->siFlag == QUEST_CLEAR_COND_USEWENNYOLDMAN )
		{
			if ( pclCI->clBI.bWennyOldManUpgrade )
			{
				return true ;
			}
		}
		
		// ���� �α��ε� �̹� ������ �̹� �ξ��ٸ�
		if(pclcond->siFlag == QUEST_CLEAR_COND_TEACHERSET )
		{
			if ( 0 < pclCI->clBI.clFatherInfo.clFather.GetPersonID() )
			{
				return true;
			}
		}
	}

	// �������̶��..
	if( pclcond->siFlag == QUEST_CLEAR_COND_GOHUNTMAP )
	{
		if ( GetHuntVillageUnique() > 0 )
			return true;
	}
	
	// ���ӵ��� ���̴� ����Ʈ ���̶��, 
	if(pclcond->siFlag == QUEST_CLEAR_COND_HORSESPEED)
	{
		// ���� ���� �ӵ��� ���Ѵ�. 
		cltHorse* pclhorse = pclCI->clHorseInfo.GetCurrentShowHorse();

		if(pclhorse)
		{
			SI32 curspeed= pclhorse->GetRealMoveSpeed();
			if(curspeed >= pclcond->siPara2)
			{
				return true;
			}
		}
	}

	// �κ� ������ �����̶��, 
	if(pclcond->siFlag == QUEST_CLEAR_COND_ITEM)
	{
		SI32 itemunique = pclcond->siPara1;
		SI32 itemnum	= pclcond->siPara2;

		if(itemnum <= pclCI->clCharItem.GetItemNum(itemunique))
		{
			return true;
		}
	}

	if(pclcond->siFlag == QUEST_CLEAR_COND_ITEMCHECK)
	{
		SI32 itemunique = pclcond->siPara1;
		SI32 itemnum	= pclcond->siPara2;

		if(itemnum <= pclCI->clCharItem.GetItemNum(itemunique))
		{
			return true;
		}
	}

	// ���͸� ������ �̻� óġ�϶�� �����̸�, 
	if ( (pclcond->siFlag == QUEST_CLEAR_COND_KILLMON)	
		|| (pclcond->siFlag	== QUEST_CLEAR_COND_PARTYKILLMON)		// ���͸� ��Ƽ �ΰ� óġ�ϴ� ����Ʈ���	
		|| (pclcond->siFlag == QUEST_CLEAR_COND_TWOWAYKILLMON)		// ���͸� ȥ�� Ȥ�� ��Ƽ �ΰ� óġ�ϴ� ����Ʈ���
		|| (pclcond->siFlag == QUEST_CLEAR_COND_TWOWAYKILLMONBONUS)	// ���͸� ȥ�� Ȥ�� ��Ƽ �ΰ� óġ�ϴ� ����Ʈ���
		|| (pclcond->siFlag == QUEST_CLEAR_COND_MAPKILLMON)			// �ش� ���� ���͸� ��� �̻� �׿��� �ϴ� ����Ʈ���
	)
	{
		// ����Ʈ�� �ӹ��� ���� óġ�̰�. 
		if(pclCI->clQuestInfo.clUnit[questtype].siQuestCmd == pclcond->siFlag)
		{
			// óġ�ؾ� �� �� �̻��� óġ�ϸ�, 
			if(pclCI->clQuestInfo.clUnit[questtype].siQuestPara2 >= pclcond->siPara2)
			{
				return true;
			}
		}
	}

	// ���͸� ������ �̻� ������ �����̶��, 
	if(pclcond->siFlag	== QUEST_CLEAR_COND_HITMON)
	{
		// ����Ʈ�� �ӹ��� ���� �������̰�. 
		if(pclCI->clQuestInfo.clUnit[questtype].siQuestCmd == pclcond->siFlag)
		{
			// ������ �� �� �̻��� ������, 
			if(pclCI->clQuestInfo.clUnit[questtype].siQuestPara2 >= pclcond->siPara2)
			{
				return true;
			}
		}
	}

	// ��ȯ���� ���͸� ������ �̻� óġ�϶�� �����̸�, 
	if(pclcond->siFlag	== QUEST_CLEAR_COND_SUMMONBATTLE)
	{
		// ����Ʈ�� �ӹ��� ���� óġ�̰�. 
		if(pclCI->clQuestInfo.clUnit[questtype].siQuestCmd == pclcond->siFlag)
		{
			// óġ�ؾ� �� �� �̻��� óġ�ϸ�, 
			if(pclCI->clQuestInfo.clUnit[questtype].siQuestPara2 >= pclcond->siPara2)
			{
				return true;
			}
		}

	}

	// Ư�� ����⸦ ������ �̻� ��ƾ� �ϴ� ����. 
	if( (pclcond->siFlag == QUEST_CLEAR_COND_FISH) || (pclcond->siFlag == QUEST_CLEAR_COND_FISHNOSKILL) )
	{
		// ����Ʈ�� �ӹ��� ���� óġ�̰�. 
		if(pclCI->clQuestInfo.clUnit[questtype].siQuestCmd == pclcond->siFlag)
		{
			// óġ�ؾ� �� �� �̻��� óġ�ϸ�, 
			if(pclCI->clQuestInfo.clUnit[questtype].siQuestPara2 >= pclcond->siPara2)
			{
				return true;
			}
		}
	}
	
	// Ư�� ���  ������ �̻� ��Ȯ�ؾ� �ϴ� ����. 
	if( (pclcond->siFlag == QUEST_CLEAR_COND_FARM) || (pclcond->siFlag == QUEST_CLEAR_COND_FARMNOSKILL) )
	{
		// ����Ʈ�� �ӹ��� ���� óġ�̰�. 
		if(pclCI->clQuestInfo.clUnit[questtype].siQuestCmd == pclcond->siFlag)
		{
			// óġ�ؾ� �� �� �̻��� óġ�ϸ�, 
			if(pclCI->clQuestInfo.clUnit[questtype].siQuestPara2 >= pclcond->siPara2)
			{
				return true;
			}
		}
	}

	// Ư�� ������ ������ �̻� ä���ؾ� �ϴ� ����.
	if( pclcond->siFlag == QUEST_CLEAR_COND_MINE || pclcond->siFlag == QUEST_CLEAR_COND_MINENOSKILL )
	{
		// ����Ʈ�� �ӹ��� ���� óġ�̰�. 
		if(pclCI->clQuestInfo.clUnit[questtype].siQuestCmd == pclcond->siFlag)
		{
			// óġ�ؾ� �� �� �̻��� óġ�ϸ�, 
			if(pclCI->clQuestInfo.clUnit[questtype].siQuestPara2 >= pclcond->siPara2)
			{
				return true;
			}
		}
	}

	// ������� �������� ȹ���ؾ� �ϴ� ����
	if ( pclcond->siFlag == QUEST_CLEAR_COND_HUNT_ITEM )
	{
		// ����Ʈ�� �ӹ��� ���� óġ�̰�. 
		if(pclCI->clQuestInfo.clUnit[questtype].siQuestCmd == pclcond->siFlag)
		{
			// óġ�ؾ� �� �� �̻��� óġ�ϸ�, 
			if(pclCI->clQuestInfo.clUnit[questtype].siQuestPara2 >= pclcond->siPara2)
			{
				return true;
			}
		}
	}

	
	// ��ǰ�� ������ �̻� ������  �����̸�, (��ǰ,ȣǰ,�ű� �߰�)
	if ( (pclcond->siFlag	== QUEST_CLEAR_COND_MAKEITEM) 
		|| (pclcond->siFlag == QUEST_CLEAR_COND_MAKE_RAREITEM) 
	)
	{
		// ����Ʈ�� �ӹ��� ��ǰ ����� �̰�. 
		if(pclCI->clQuestInfo.clUnit[questtype].siQuestCmd == pclcond->siFlag)
		{
			// ���� ��ǰ�� ������ �� �̻��̸�,
			if(pclCI->clQuestInfo.clUnit[questtype].siQuestPara2 >= pclcond->siPara2)
			{
				return true;
			}
		}
	}

	// Ʃ�丮��� ��ǰ�� ������ �̻� ������  �����̸�, 
	if (pclcond->siFlag	== QUEST_CLEAR_COND_TUTORIALMAKEITEM)
	{
		// ����Ʈ�� �ӹ��� ��ǰ ����� �̰�. 
		if(pclCI->clQuestInfo.clUnit[questtype].siQuestCmd == pclcond->siFlag)
		{
			// ���� ��ǰ�� ������ �� �̻��̸�,
			if(pclCI->clQuestInfo.clUnit[questtype].siQuestPara2 >= pclcond->siPara2)
			{
				return true;
			}
		}
	}

	// ��ǰ�� ������ �̻� ��þƮ�϶��  �����̸�, 
	if ( (pclcond->siFlag == QUEST_CLEAR_COND_ENCHANTITEM)
		|| (pclcond->siFlag == QUEST_CLEAR_COND_ENCHANTEQUIPLEVELWEAPON)
	)
	{
		// ����Ʈ�� �ӹ���  ��þƮ �̰�. 
		if(pclCI->clQuestInfo.clUnit[questtype].siQuestCmd == pclcond->siFlag)
		{
			// ��þƮ�� ��ǰ�� ������ �� �̻��̸�,
			if(pclCI->clQuestInfo.clUnit[questtype].siQuestPara2 >= pclcond->siPara2)
			{
				return true;
			}
		}
	}

	// ���ֿ� Ư�� �������� �ø����  �����̸�, 
	if(pclcond->siFlag	== QUEST_CLEAR_COND_TUTORIALMAKEITEM)
	{
		// ����Ʈ�� �ӹ��� ���ֿ� Ư�� �������� �ø����  �����̸�, 
		if(pclCI->clQuestInfo.clUnit[questtype].siQuestCmd == pclcond->siFlag)
		{
			// ���� ��ǰ�� ������ �� �̻��̸�,
			if(pclCI->clQuestInfo.clUnit[questtype].siQuestPara2 >= pclcond->siPara2)
			{
				return true;
			}
		}
	}


	// ��ǰ�� ������ �̻� ����϶��  �����̸�, 
	if(pclcond->siFlag	== QUEST_CLEAR_COND_USEITEM)
	{
		// ����Ʈ�� �ӹ��� ��ǰ ����ϱ��̰� 
		if(pclCI->clQuestInfo.clUnit[questtype].siQuestCmd == pclcond->siFlag)
		{
			// ���� ��ǰ�� ������ �� �̻��̸�,
			if(pclCI->clQuestInfo.clUnit[questtype].siQuestPara2 >= pclcond->siPara2)
			{
				return true;
			}
		}
	}

	// Ư�� ����Ʈ�� �ο� �޾ƾ� �ϴ� �����̶��, 
	if(pclcond->siFlag == QUEST_CLEAR_COND_GETQUEST)
	{
		SI32 questtype = pclClient->pclQuestManager->GetQuestTypeFromNPCKind(pclcond->siPara1);
		return pclCI->clQuestInfo.IsQuestClearOrGoing( questtype );
	}

	// Ư�� ����Ʈ�� ���� �ϴ� �����̶��, 
	if(pclcond->siFlag == QUEST_CLEAR_COND_CLEARQUEST)
	{
		return pclCI->clQuestInfo.IsClear(pclClient->pclQuestManager, pclcond->siPara1);
	}


	// ����â�� ���� �����̶��, 
	if(pclcond->siFlag == QUEST_CLEAR_COND_OPENHEADCHAT)
	{
		if(pclClient->GameMode == GAMEMODE_SERVER)
		{
			if(((cltCharServer*)this)->bHeadChatSwitch == true)
			{
				return true;
			}
		}
		else
		{
			SI32 chatmode = ((cltCharClient*)this)->pclDrawChat->GetChatMode();
			if(chatmode == CHATMODE_HEAD)
			{
				return true;
			}

		}
	}

	// �������� ���ֿ� �ø��� �����̶��, 
	if(pclcond->siFlag == QUEST_CLEAR_COND_UPITEMTOMARKET)
	{
		// ����Ʈ�� �ӹ��� ���ֿ� �ø����̰�
		if(pclCI->clQuestInfo.clUnit[questtype].siQuestCmd == pclcond->siFlag)
		{
			// �÷��� ��ǰ�� ������ �� �̻��̸�,
			if(pclCI->clQuestInfo.clUnit[questtype].siQuestPara2 >= pclcond->siPara2)
			{
				return true;
			}
		}
	}
	// �������� �������ο��� �Ĵ� �����̶��, 
	if(pclcond->siFlag == QUEST_CLEAR_COND_SELLTRADER)
	{
		// ����Ʈ�� �ӹ��� �������ο��� �Ĵ� �Ű�
		if(pclCI->clQuestInfo.clUnit[questtype].siQuestCmd == pclcond->siFlag)
		{
			// �� ��ǰ�� ������ �� �̻��̸�,
			if(pclCI->clQuestInfo.clUnit[questtype].siQuestPara2 >= pclcond->siPara2)
			{
				return true;
			}
		}
	}
	// ������� ����Ʈ�� �޾Ұų� �޴´ٸ�
	if ( pclcond->siFlag == QUEST_CLEAR_COND_GETMAGICLAMPQUEST )
	{
		if ( pclCI->clQuestInfo.clUnit[QUEST_TYPE_SPECIAL].siCurQuestUnique > 0 )
		{
			return true;
		}
	}
	// ���� ����� �ƹ����̳� �����Ѱ��� �ִٸ�
	if ( pclcond->siFlag == QUEST_CLEAR_COND_ISLEARNED_MANUFACTURE )
	{
		SI16 siSkillType[] = {
				SKILL_MAKEMED		// ������.
				,SKILL_MAKEFOOD		// �丮��.
				,SKILL_MAKEARMOUR1	// �������ۼ�1
				,SKILL_MAKEHELMET1	// �������ۼ�1
				,SKILL_MAKESWORD1	// �����ۼ�1
				,SKILL_MAKESPEAR1	// â���ۼ�1
				,SKILL_MAKEAXE1		// �������ۼ�1
				,SKILL_MAKESTAFF1	// ���������ۼ�1
				,SKILL_MAKEBOW1		// Ȱ���ۼ�1
				,SKILL_MAKEGUN1		// �����ۼ�1
				,SKILL_MAKESHOES1	// �Ź����ۼ�1	
				,SKILL_MAKEBELT1	// ������ۼ�1	
				,SKILL_MAKEDRESS1	// �Ǻ����ۼ�1
				,SKILL_MAKEIRON1	// ö�����ۼ� 
				,SKILL_MAKETOOL1	// ���굵�����ۼ�
				,SKILL_MAKEHAT1		// �������ۼ�
				,SKILL_ARTIFACT		// ��Ƽ��Ʈ ���ۼ�
				,SKILL_MAKEAVATAR_DRESS	// �ƹ�Ÿ �Ǻ� ���ۼ�
				,SKILL_MAKEAVATAR_HAT	// �ƹ�Ÿ ���� ���ۼ�
				,SKILL_MAKEAVATAR_MANTLE	// �ƹ�Ÿ ���� ���ۼ�
				,SKILL_MAKEAVATAR_RING	// �ƹ�Ÿ ���� ���ۼ�
				,SKILL_MAKEAVATAR_NECK	// �ƹ�Ÿ ����� ���ۼ�
		};
		SI16 siCount = (SI16)( sizeof(siSkillType)/sizeof(SI16) );
		//SI16 siCount = 17;// �ٲ����� ���⶧���� ������ ���� ���� �ͺ��� �ٷ� ���ڸ� �־���

		for (SI16 i=0; i<siCount; i++)
		{
#ifdef _SAFE_MEMORY
			if ( pclCI->clCharSkill.GetTotalSkillLevel(siSkillType[i],	0, 0, &pclCI->clCharItem.clItem[0])	>= pclcond->siPara2 )
#else
			if ( pclCI->clCharSkill.GetTotalSkillLevel(siSkillType[i],	0, 0, pclCI->clCharItem.clItem)	>= pclcond->siPara2 )
#endif
			{
				return true;
			}
		}
	}
	// ���縮���� �ִ� ���� ����Ʈ �߿� �ƹ����̳� 1�ܰ� �̻� Ŭ���� �ߴٸ�
	if ( pclcond->siFlag == QUEST_CLEAR_COND_ISGET_MANUFACTUREQUEST )
	{
		SI16 siQuestType[] = {
			QUEST_TYPE_MAKEHEAL1	// ���� �������� (�ﷹ��)
			,QUEST_TYPE_MAKESWORD1	// ���� �������� (������)
			,QUEST_TYPE_MAKEBOW1	// ���� Ȱ������ (������)
			,QUEST_TYPE_MAKEHELMET1	// ���� ���������� (�츣��Ƽ��)
			,QUEST_TYPE_MAKESPEAR1	// ���� â������ (���Ǿ)
			,QUEST_TYPE_MAKEARMOUR1	// ���� ������ (�ƸӸ���)
			,QUEST_TYPE_MAKEAX1		// ���� ������ (�׽þ�)
			,QUEST_TYPE_MAKEGUN1	// �� ������ (�ų�)
			,QUEST_TYPE_MAKESTAFF1	// ������ ������
			,QUEST_TYPE_MAKEBELT1	// ���(��Ʈ) ������ (��Ƽ��)
			,QUEST_TYPE_MAKESHOES1	// �Ź� ������ (������)
		};
		//SI16 siCount = (SI16)( sizeof(siQuestType)/sizeof(SI16) );
		SI16 siCount = 11;

		for (SI16 i=0; i<siCount; i++)
		{
			if ( pclCI->clQuestInfo.clUnit[ siQuestType[i] ].siQuestState > 0 )
			{
				return true;
			}
		}
	}

	// (Para1)�� ������ (Para2) �̻��̾�� �Ѵ�
	if ( pclcond->siFlag == QUEST_CLEAR_COND_CHECKSTATUS )
	{
		switch (pclcond->siPara1)
		{
		case 1:// �ٷ�(Str)
			{
				if ( clPB.clTotalBA.GetStr() >= pclcond->siPara2 ) return true;
			}
			break;
		case 2:// ���߷�(Agi)
			{
				if ( clPB.clTotalBA.GetDex() >= pclcond->siPara2 ) return true;
			}
			break;
		case 3:// ����(Wis)
			{
				if ( clPB.clTotalBA.GetMag() >= pclcond->siPara2 ) return true;
			}
			break;
		case 4:// �����(Vit)
			{
				if ( clPB.clTotalBA.GetVit() >= pclcond->siPara2 ) return true;
			}
			break;
		case 5:// ������(Dex)
			{
				if ( clPB.clTotalBA.GetHnd() >= pclcond->siPara2 ) return true;
			}
			break;
		case 6:// ���(Luck)
			{
				if ( clPB.clTotalBA.GetLuk() >= pclcond->siPara2 ) return true;
			}
			break;
		case 7:// �̵��ӵ�(Speed)
			{
				if ( clPB.GetTotalMoveSpeed() >= pclcond->siPara2 ) return true;
			}
			break;
		case 8:// ���ݷ�(Attack)
			{
				if( pclClient->IsCountrySwitch(Switch_HealthAddChange) )
				{
					if ( (clPB.GetTotalPHysicalMinAttackDmg() >= pclcond->siPara2) ) return true;
				}
				else
				{
					if ( (clPB.GetTotalMinDamage() >= pclcond->siPara2) ) return true;
				}
			}
			break;
		case 9:// ����(Defense)
			{
				if( pclClient->IsCountrySwitch(Switch_HealthAddChange) )
				{
					if ( clPB.GetPHysicalDefensive() >= pclcond->siPara2 ) return true;
				}
				else
				{
					if ( clPB.GetTotalAC() >= pclcond->siPara2 ) return true;
				}
			}
			break;
		}
	}

	// 6���� ���� Ÿ�� �� �ƹ� Ÿ���̳� para1 �̻��̸� ����Ʈ Ŭ����
	if ( pclcond->siFlag == QUEST_CLEAR_COND_ALLWEAPONSKILL ) 
	{
		SI32 siSkillType[]	= { SKILL_USESWORD1, SKILL_USESPEAR1, SKILL_USESTAFF1, SKILL_USEAXE1, SKILL_USEBOW1, SKILL_USEGUN1 };
	

		for ( UI16 uiCount=0; uiCount<6; uiCount++ )
		{
#ifdef _SAFE_MEMORY
			if ( pclCI->clCharSkill.GetTotalSkillLevel(siSkillType[uiCount], 0, 0, &pclCI->clCharItem.clItem[0]) >= pclcond->siPara1 )
#else
			if ( pclCI->clCharSkill.GetTotalSkillLevel(siSkillType[uiCount], 0, 0, pclCI->clCharItem.clItem) >= pclcond->siPara1 )
#endif
			{
				return true;
			}
		}
	}
//	// 35���� ��ų�� �ƹ� ��ų�̳� para1 �̻��̸� ����Ʈ Ŭ����
//	if ( pclcond->siFlag == QUEST_CLEAR_COND_UPSKILL ) 
//	{
//		SI32 siSkillType[]	= { SKILL_USESWORD1,
//			SKILL_USESPEAR1,
//			SKILL_USESTAFF1,
//			SKILL_USEAXE1,
//			SKILL_USEBOW1,
//			SKILL_USEGUN1,
//			//��� ���߼�
//			SKILL_MAKEMED,
//			SKILL_MAKEFOOD,		
//			SKILL_MAKEARMOUR1,	
//			SKILL_MAKEHELMET1,	
//			SKILL_MAKESWORD1,	
//			SKILL_MAKESPEAR1,	
//			SKILL_MAKEAXE1,
//			SKILL_MAKESTAFF1,	
//			SKILL_MAKEBOW1,
//			SKILL_MAKEGUN1,
//			SKILL_MAKESHOES1,
//			SKILL_MAKEBELT1,
//			SKILL_MAKEDRESS1,
//			SKILL_USESWORD1,	
//			SKILL_USESPEAR1,	
//			SKILL_USEBOW1,	
//			SKILL_USEAXE1,	
//			SKILL_USEGUN1,	
//			SKILL_USESTAFF1,	
//			SKILL_SUMMON,	
//			SKILL_FISH,
//			SKILL_HORSETRAINING,
//			SKILL_MAKEIRON1,
//			SKILL_MAKETOOL1,
//			SKILL_CAPTURE,
//			SKILL_MAKEHAT1,
//			SKILL_FARM,
//			SKILL_MINE,
//			SKILL_ARTIFACT };
//
//
//		for ( UI16 uiCount=0; uiCount<35; uiCount++ )
//		{
//#ifdef _SAFE_MEMORY
//			if ( pclCI->clCharSkill.GetTotalSkillLevel(siSkillType[uiCount], 0, 0, &pclCI->clCharItem.clItem[0]) >= pclcond->siPara1 )
//#else
//			if ( pclCI->clCharSkill.GetTotalSkillLevel(siSkillType[uiCount], 0, 0, pclCI->clCharItem.clItem) >= pclcond->siPara1 )
//#endif
//			{
//				return true;
//			}
//		}
//	}
    
	// ����ĭ 2ĭ�߿� ��ĭ�̶� ������ ��â�Ǿ� �ִ°�?
	if (pclcond->siFlag == QUEST_CLEAR_COND_EQUIPBAG)
	{
		if(pclCI->clQuestInfo.clUnit[questtype].siQuestCmd == pclcond->siFlag)
		{
			SI32 siBagUnique1 = pclCI->clCharItem.clItem[PERSONITEM_BAG].siUnique;
			SI32 siBagUnique2 = pclCI->clCharItem.clItem[PERSONITEM_BAG_SUB].siUnique;

			// ���â�߿� �ش� ��ǰ�� �ִ��� Ȯ���Ѵ�. 
			if( (siBagUnique1 > 0) || (siBagUnique2 > 0))
			{
				return true;
			}

		}
	}
	
	// ���� ���� �ɹ��߿� �ƹ��� para2��ŭ ��ƶ�
	if (pclcond->siFlag == QUEST_CLEAR_COND_KILLDARKSOLDIER)
	{
		if(pclCI->clQuestInfo.clUnit[questtype].siQuestCmd == pclcond->siFlag)
		{
			// óġ�ؾ� �� �� �̻��� óġ�ϸ�, 
			if(pclCI->clQuestInfo.clUnit[questtype].siQuestPara2 >= pclcond->siPara2)
			{
				return true;
			}
		}
	}

	// ���� ����� ��� �� ����̶� Max�̸� Ŭ����
	if (pclcond->siFlag == QUEST_CLEAR_COND_FULL_ORGAN)
	{
		if(pclCI->clQuestInfo.clUnit[questtype].siQuestCmd == pclcond->siFlag)
		{
			SI32 siLevel		= pclCI->clIP.GetLevel();
			SI32 siMaxOrgan		= min(100, MAXORG(siLevel));
			SI32 siOrganType[]	= {HEALTH_ORGAN_TYPE_ORG1, HEALTH_ORGAN_TYPE_ORG2, HEALTH_ORGAN_TYPE_ORG3, HEALTH_ORGAN_TYPE_ORG4};
			
			
			for (SI32 siIndex=0; siIndex<4; siIndex++)
			{
				SI32 siGetOrgan = pclCI->clHealthInfo.GetOrg( siOrganType[siIndex] );

				if (siGetOrgan >= siMaxOrgan)
				{
					return true;
				}
			}
			
		}
	}

	// ���忡�� ������ �����ؾ��ϴ� ����Ʈ���
	if ( pclcond->siFlag == QUEST_CLEAR_COND_BUYMARKET )
	{
		// ���� �ɸ� ����Ʈ Ȯ�� �ϰ�
		if ( pclCI->clQuestInfo.clUnit[questtype].siQuestCmd == pclcond->siFlag )
		{
			// ��ߵǴ� ���� �̻��̸�
			if ( pclCI->clQuestInfo.clUnit[questtype].siQuestPara2 >= pclcond->siPara2 )
			{
				return true;
			}
		}
	}
	
	// Ư�� ������ ������ ����� ����Ʈ ���
	if ( pclcond->siFlag == QUEST_CLEAR_COND_MAKELEVELITEM )
	{
		// ���� �ɸ� ����Ʈ Ȯ�� �ϰ�
		if ( pclCI->clQuestInfo.clUnit[questtype].siQuestCmd == pclcond->siFlag )
		{
			// ������ �ϴ� ���� �̻��̸�
			if ( pclCI->clQuestInfo.clUnit[questtype].siQuestPara2 >= pclcond->siPara2 )
			{
				return true;
			}
		}
	}

	// Ư�� ������ ������ ����� ����Ʈ ��� - ���� ���� ����
	if ( pclcond->siFlag == QUEST_CLEAR_COND_TUTORIALMAKELEVELITEM )
	{
		// ���� �ɸ� ����Ʈ Ȯ�� �ϰ�
		if ( pclCI->clQuestInfo.clUnit[questtype].siQuestCmd == pclcond->siFlag )
		{
			// ������ �ϴ� ���� �̻��̸�
			if ( pclCI->clQuestInfo.clUnit[questtype].siQuestPara2 >= pclcond->siPara2 )
			{
				return true;
			}
		}
	}

	// Ư������ ���⸦ � �̻� ���� ����� ����Ʈ ���
	if ( pclcond->siFlag == QUEST_CLEAR_COND_TAKEEQUIPLEVELWEAPON )
	{
		// ���� �ɸ� ����Ʈ Ȯ�� �ϰ�
		if ( pclCI->clQuestInfo.clUnit[questtype].siQuestCmd == pclcond->siFlag )
		{
			SI16 siNeedLevel	= pclcond->siPara1;	// �ʿ� ����
			SI32 siNeedAmount	= pclcond->siPara2; // �ʿ��� ����
			SI32 siNowAmount	= 0;				// ���� ���� �ִ� ����

			// ���� �� �κ��丮�� �������� �˻�
			for ( SI32 siIndex=MAX_SHAPE_ITEM; siIndex<MAX_ITEM_PER_PERSON; ++siIndex )
			{
				cltItem* pclItem = &pclCI->clCharItem.clItem[siIndex];
				if ( NULL == pclItem )
				{
					continue;
				}
				
				// ������ Ÿ���� ��,â,����,Ȱ,��,�����̰� �ƴϸ� �н�
				if ( false == pclItem->IsWeapon( pclClient->pclItemManager ) )
				{
					continue;
				}

				// ���뷹���� ���ǿ� �´� �͸� ī��Ʈ
				if ( siNeedLevel == pclItem->GetEquipLevel(pclClient->pclItemManager) )
				{
					++siNowAmount;
				}
			}

			if ( siNeedAmount <= siNowAmount )
			{
				return true;
			}
		}
	}
	
	// ȯ���� ���� � �������� ������ ����(����, �Ӽ�����)
	if ( (pclcond->siFlag == QUEST_CLEAR_COND_GETELEMENT_RESTORE) || (pclcond->siFlag == QUEST_CLEAR_COND_GETPOWDER_RESTORE) )
	{
		if(pclCI->clQuestInfo.clUnit[questtype].siQuestCmd == pclcond->siFlag)
		{
			// ���� ��ǰ�� ������ �� �̻��̸�,
			if(pclCI->clQuestInfo.clUnit[questtype].siQuestPara2 >= pclcond->siPara2)
			{
				return true;
			}
		}
	}

	// Ư�� �������� ���� �� �ִ� �������� ��� ��ƿ���
	if ( pclcond->siFlag == QUEST_CLEAR_COND_TAKEITEM_MATERIAL )
	{
		if ( pclCI->clQuestInfo.clUnit[questtype].siQuestCmd == pclcond->siFlag )
		{
			SI32 siUnique = pclcond->siPara1;
			SI32 siAmount = pclcond->siPara2;

			if ( true == pclCI->clCharItem.IsHaveMaterialItem(pclClient->pclItemManager, siUnique, siAmount) )
			{
				return true;
			}
		}
	}

	// ������ �ִ� ���� �������� ��������
	if ( pclcond->siFlag == QUEST_CLEAR_COND_TAKEWEAPONHAVESLOT )
	{
		if ( pclCI->clQuestInfo.clUnit[questtype].siQuestCmd == pclcond->siFlag )
		{
			SI32 siNeedAmount	= pclcond->siPara2;
			SI32 siNowAmount	= 0;

			// ���� �� �κ��� ������ �ִ� �������� �˻��Ѵ�
			for ( SI32 siIndex=MAX_SHAPE_ITEM; siIndex<MAX_ITEM_PER_PERSON; ++siIndex )
			{
				cltItem* pclItem = &pclCI->clCharItem.clItem[siIndex];
				if ( NULL == pclItem )
				{
					continue;
				}
				
				if ( false == pclItem->IsWeapon( pclClient->pclItemManager ) )
				{
					continue;
				}

				if ( false == pclItem->IsHaveCrystalSlot() )
				{
					continue;
				}

				siNowAmount += pclItem->siItemNum;
			}

			if ( siNeedAmount <= siNowAmount )
			{
				return true;
			}
		}
	}

	// ���� �����ۿ� ������ �����϶�� ����Ʈ���
	// �����ۿ� ������Ʈ�� �����غ���� ����Ʈ ���
	if ( (pclcond->siFlag == QUEST_CLEAR_COND_ARTIFACTMIXWEAPON)
		|| (pclcond->siFlag == QUEST_CLEAR_COND_ARTIFACTMIX)
	)
	{
		// ���� �ɸ� ����Ʈ Ȯ�� �ϰ�
		if ( pclCI->clQuestInfo.clUnit[questtype].siQuestCmd == pclcond->siFlag )
		{
			// ���� �̻��̸�
			if ( pclCI->clQuestInfo.clUnit[questtype].siQuestPara2 >= pclcond->siPara2 )
			{
				return true;
			}
		}
	}

	// Ư������� ����ü�� ������ ����Ʈ���
	if ( pclcond->siFlag == QUEST_CLEAR_COND_MAKECRYSTAL )
	{
		// ���� �ɸ� ����Ʈ Ȯ�� �ϰ�
		if ( pclCI->clQuestInfo.clUnit[questtype].siQuestCmd == pclcond->siFlag )
		{
			// ������ �ϴ� ���� �̻��̸�
			if ( pclCI->clQuestInfo.clUnit[questtype].siQuestPara2 >= pclcond->siPara2 )
			{
				return true;
			}
		}
	}

	// �ƹ� ��ȯ���� ���ʽ� ������ 0���� ����� ����Ʈ ���
	if ( pclcond->siFlag == QUEST_CLEAR_COND_SUMMONBONUSZERO )
	{
		if ( pclCI->clQuestInfo.clUnit[questtype].siQuestCmd == pclcond->siFlag )
		{
			for ( SI32 siIndex=0; siIndex<MAX_SUMMON_OWN; ++siIndex )
			{
				SI32 siSummonKind	= pclCI->clSummonInfo.clSummon[siIndex].siKind;
				SI32 siSummonStatus	= pclCI->clSummonInfo.clSummon[siIndex].siStatus;
				SI32 siSummonBonus	= pclCI->clSummonInfo.clSummon[siIndex].clIP.GetBonus();

				if ( (0 < siSummonKind) && (MAX_KIND_NUMBER > siSummonKind) && (SUMMON_STATUS_TAKEOUT == siSummonStatus) && (0 >= siSummonBonus) )
				{
					return true;
				}
			}
		}
	}

	// Ư�� ������ ������ ����� ����Ʈ ���
	if ( pclcond->siFlag == QUEST_CLEAR_COND_LEARNWEAPONSKILL )
	{
		// ���� �ɸ� ����Ʈ Ȯ�� �ϰ�
		if ( pclCI->clQuestInfo.clUnit[questtype].siQuestCmd == pclcond->siFlag )
		{
			SI32 siGrade = pclcond->siPara1-1;	// 1�ܰ���� �����̱⶧���� �迭�� 0�����̴� �׷��� -1���ش�
			SI32 siLevel = pclcond->siPara2;
			if ( (0 <= siGrade) && (3 > siGrade) )
			{
				SI32 siSkillUnique[3][6] = {
					{SKILL_SWORD_INCDR,		SKILL_SPEAR_INCAC,		SKILL_AXE_DECGAP,	SKILL_BOW_DRAIN,	SKILL_GUN_INCPHYAR,		SKILL_STAFF_INCMAG}
					,{SKILL_SWORD_INCVIT,	SKILL_SPEAR_DOUBLEAT,	SKILL_AXE_INDURE,	SKILL_BOW_INCRANGE,	SKILL_GUN_DECMAGDELAY,	SKILL_STAFF_DECUSEMANA}
					,{SKILL_SWORD_INCMAGAT,	SKILL_SPEAR_INCMAGAT,	SKILL_AXE_INCCRI,	SKILL_BOW_INCMAGAT,	SKILL_GUN_INCWEAAT,		SKILL_STAFF_INCMAGAT}
				};

				// 1�ܰ迡�� 3�ܰ�(siGrade) ��ų�� �ƹ��ų� siLevel�� ������ Ŭ����
				for ( SI32 siIndex=0; siIndex<6; siIndex++ )
				{
					if ( siLevel <= pclCI->clCharSkill.GetSkillLevel(siSkillUnique[siGrade][siIndex]) )
					{
						return true;
					}
				}
			}
		}
	}

	// ���������̻� ��æƮ �� ������ ������ ����
	if(pclcond->siFlag == QUEST_CLEAR_COND_ENCHANTEQUIPPOS)
	{
		// ���� �ɸ� ����Ʈ Ȯ��
		if(pclCI->clQuestInfo.clUnit[questtype].siQuestCmd == pclcond->siFlag)
		{
			// 1. �ش� �����κ��� ����κ����� Ȯ��
			if(pclcond->siPara1 == PERSONITEM_WEAPON1 || pclcond->siPara1 == PERSONITEM_WEAPON2)
			{
				// ���� �κ��� ������ �α����� �� �˻��Ѵ�.
				if(pclCI->clCharItem.clItem[PERSONITEM_WEAPON1].Element.siPower >= pclcond->siPara2)
				{
					return true;
				}
				else if(pclCI->clCharItem.clItem[PERSONITEM_WEAPON2].Element.siPower >= pclcond->siPara2)
				{
					return true;
				}
			}
			else
			{
				// 2. �ش� �������� ���� ��æƮ ���� �̻����� ��æƮ �Ǿ� ������
				if( pclCI->clCharItem.clItem[pclcond->siPara1].Element.siPower >= pclcond->siPara2)
				{
					return true;
				}
			}
		}
	}

	// ������ų���� ����ϴ� ����Ʈ���
	if(pclcond->siFlag	== QUEST_CLEAR_COND_USE_SKILLBOOK)
	{
		// ����Ʈ�� �ӹ��� ������ų�� ����ϱ��̰�
		if(pclCI->clQuestInfo.clUnit[questtype].siQuestCmd == pclcond->siFlag)
		{
			// ���� ��ǰ�� ������ �� �̻��̸�,
			if(pclCI->clQuestInfo.clUnit[questtype].siQuestPara2 >= pclcond->siPara2)
			{
				return true;
			}
		}
	}

	////192 para1���� ��ŭ ��ü�޼��� ������.
	//if ( pclcond->siFlag == QUEST_CLEAR_COND_SEND_MESSAGE )
	//{
	//	// ���� �ɸ� ����Ʈ Ȯ�� �ϰ�
	//	if ( pclCI->clQuestInfo.clUnit[questtype].siQuestCmd == pclcond->siFlag )
	//	{
	//		// para1 ���� �̻��̸�.
	//		if ( pclCI->clQuestInfo.clUnit[questtype].siQuestPara1 >= pclcond->siPara2 )
	//		{
	//			return true;
	//		}
	//	}
	//}
//		//192 para1�������� ��ų�ø���
//	if ( pclcond->siFlag == QUEST_CLEAR_COND_UPSKILL )
//	{
//		// ���� �ɸ� ����Ʈ Ȯ�� �ϰ�
//		if ( pclCI->clQuestInfo.clUnit[questtype].siQuestCmd == pclcond->siFlag )
//		{
//			//QUEST_CLEAR_COND_ALLWEAPONSKILL
//			SI32 siSkillType[]	= { 
//				// ���� ����
//				SKILL_USESWORD1,
//				SKILL_USESPEAR1,
//				SKILL_USESTAFF1,
//				SKILL_USEAXE1,
//				SKILL_USEBOW1,
//				SKILL_USEGUN1,
//				//��� ���߼�
//				SKILL_MAKEMED,
//				SKILL_MAKEFOOD,		
//				SKILL_MAKEARMOUR1,	
//				SKILL_MAKEHELMET1,	
//				SKILL_MAKESWORD1,	
//				SKILL_MAKESPEAR1,	
//				SKILL_MAKEAXE1,
//				SKILL_MAKESTAFF1,	
//				SKILL_MAKEBOW1,
//				SKILL_MAKEGUN1,
//				SKILL_MAKESHOES1,
//				SKILL_MAKEBELT1,
//				SKILL_MAKEDRESS1,
//				SKILL_USESWORD1,	
//				SKILL_USESPEAR1,	
//				SKILL_USEBOW1,	
//				SKILL_USEAXE1,	
//				SKILL_USEGUN1,	
//				SKILL_USESTAFF1,	
//				SKILL_SUMMON,	
//				SKILL_FISH,
//				SKILL_HORSETRAINING,
//				SKILL_MAKEIRON1,
//				SKILL_MAKETOOL1,
//				SKILL_CAPTURE,
//				SKILL_MAKEHAT1,
//				SKILL_FARM,
//				SKILL_MINE,
//				SKILL_ARTIFACT,
//			};
//			for ( UI16 uiCount=0; uiCount<6; uiCount++ )
//			{
//#ifdef _SAFE_MEMORY
//				if ( pclCI->clCharSkill.GetTotalSkillLevel(siSkillType[uiCount], 0, 0, &pclCI->clCharItem.clItem[0]) >= pclcond->siPara1 )
//#else
//				if ( pclCI->clCharSkill.GetTotalSkillLevel(siSkillType[uiCount], 0, 0, pclCI->clCharItem.clItem) >= pclcond->siPara1 )
//#endif
//				{
//					return true;
//				}
//			}
//		}
//	}
	////193 ���ϸ� ����Ʈ 2,3 �� para1��ŭ Ŭ����
	//if ( pclcond->siFlag == QUEST_CLEAR_COND_DAILY23SUCCES )
	//{
	//	// ���� �ɸ� ����Ʈ Ȯ�� �ϰ�
	//	if ( pclCI->clQuestInfo.clUnit[questtype].siQuestCmd == pclcond->siFlag )
	//	{
	//		// para1 ���� �̻��̸�.
	//		if ( pclCI->clQuestInfo.clUnit[questtype].siQuestPara1 >= pclcond->siPara1 )
	//		{
	//			return true;
	//		}
	//	}
	//}
	////193 ���� ��ũ�� para1 ��ŭ �޼�
	//if ( pclcond->siFlag == QUEST_CLEAR_COND_CHANGELING )
	//{
	//	// ���� �ɸ� ����Ʈ Ȯ�� �ϰ�
	//	if ( pclCI->clQuestInfo.clUnit[questtype].siQuestCmd == pclcond->siFlag )
	//	{
	//		SI32 sisync = clTransFormInfo.GetSynchroTransForm(clTransFormInfo.uiNowTransFormKind);
	//		
	//		if ( sisync >= pclcond->siPara1 )
	//		{
	//			return true;
	//		}
	//	}		
	//}
	////194 ����/���� ���ݷ��� para1��ŭ �޼� -> QUEST_CLEAR_COND_CHECKSTATUS�̰ɷ� ��ü .
	//if ( pclcond->siFlag == QUEST_CLEAR_COND_ATTACKPOINT )
	//{

	//}
	//195 ����Ȱ��( ���/ ä�� / ����) ��ǰ para1�� �̻� ����
	//if ( pclcond->siFlag == QUEST_CLEAR_COND_PRODUCTION_ACTIVITIES )
	//{
	//	// ���� �ɸ� ����Ʈ Ȯ�� �ϰ�
	//	if ( pclCI->clQuestInfo.clUnit[questtype].siQuestCmd == pclcond->siFlag )
	//	{
	//		// para1 ���� �̻��̸�.
	//		if ( pclCI->clQuestInfo.clUnit[questtype].siQuestPara1 >= pclcond->siPara1 )
	//		{
	//			return true;
	//		}
	//	}
	//}
	////196 ���� �̺�Ʈ PARA1 ȸ �̻� ����
	//if ( pclcond->siFlag == QUEST_CLEAR_COND_VILLAGEEVENT )
	//{
	//	// ���� �ɸ� ����Ʈ Ȯ�� �ϰ�
	//	if ( pclCI->clQuestInfo.clUnit[questtype].siQuestCmd == pclcond->siFlag )
	//	{
	//		// para1 ���� �̻��̸�.
	//		if ( pclCI->clQuestInfo.clUnit[questtype].siQuestPara1 >= pclcond->siPara1 )
	//		{
	//			return true;
	//		}
	//	}
	//}
	////197 pvp ���� para1 ȸ �̻� ����
	//if (pclcond->siFlag == QUEST_CLEAR_COND_PVP_PLAYING )
	//{
	//	// ���� �ɸ� ����Ʈ Ȯ�� �ϰ�
	//	if ( pclCI->clQuestInfo.clUnit[questtype].siQuestCmd == pclcond->siFlag )
	//	{
	//		// para1 ���� �̻��̸�.
	//		if ( pclCI->clQuestInfo.clUnit[questtype].siQuestPara1 >= pclcond->siPara1 )
	//		{
	//			return true;
	//		}
	//	}
	//}
	////198 ����� �ý��� �̿�亯 para1�� �̻�
	//if (pclcond->siFlag == QUEST_CLEAR_COND_HELPERSERVICE )
	//{
	//	// ���� �ɸ� ����Ʈ Ȯ�� �ϰ�
	//	if ( pclCI->clQuestInfo.clUnit[questtype].siQuestCmd == pclcond->siFlag )
	//	{
	//		// para1 ���� �̻��̸�.
	//		if ( pclCI->clQuestInfo.clUnit[questtype].siQuestPara1 >= pclcond->siPara1 )
	//		{
	//			return true;
	//		}
	//	}
	//}
	////199 ���� ���� 10���� ���.
	//if (pclcond->siFlag == QUEST_CLEAR_COND_KILLBOSS )
	//{
	//	// ���� �ɸ� ����Ʈ Ȯ�� �ϰ�
	//	if ( pclCI->clQuestInfo.clUnit[questtype].siQuestCmd == pclcond->siFlag )
	//	{
	//		// para1 ���� �̻��̸�.
	//		if ( pclCI->clQuestInfo.clUnit[questtype].siQuestPara1 >= pclcond->siPara1 )
	//		{
	//			return true;
	//		}
	//	}
	//}
	return false;
}

// �ӹ��� �Ϸ� ���ǿ��� �������� �䱸�Ǹ� �������� ĳ���Ϳ��Լ� �����Ѵ�. 
bool cltCharCommon::DoClearCondition(cltQuestClearConditionInfo* pclcond)
{
	SI32 i;

	if(pclcond == NULL)return false;
	cltPItemInfo* pcliteminfo = NULL;
	cltCharServer* pclchar = (cltCharServer*)this;

	// �κ� ������ �����̶��, 
	if(pclcond->siFlag == QUEST_CLEAR_COND_ITEM)
	{
		SI32 itemunique = pclcond->siPara1;
		SI32 itemnum	= pclcond->siPara2;
		cltItem clitem;

		pcliteminfo = &pclCI->clCharItem;

		for(i = PERSONITEM_INV0;i < PERSONITEM_INV0 + MAX_INVITEM_PER_PERSON;i++)
		{
			if(pcliteminfo->clItem[i].siUnique == itemunique)
			{
				clitem.Set(&pcliteminfo->clItem[i]);
				cltItem *pclFrom = &pclchar->pclCI->clCharItem.clItem[ i ];
				SI32 InvPos = pcliteminfo->GetItemPos( clitem.siUnique );

				if(itemnum <= clitem.siItemNum)
				{
					clitem.siItemNum = itemnum;

					//cyj ��������ۿ� ��ġ ���� �߰�
					while( pclchar->clItemUseReserveInfo.Push( clitem.siUnique, -clitem.siItemNum, InvPos ) == false )
					{
						pclchar->ItemUseReserveAction();
					}

					// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
					if( pclFrom->siItemNum <= clitem.siItemNum )
					{
						pclchar->ItemUseReserveAction();
					}

					// pclchar->ItemUseReserveAction(); �ؿ� �־�� �Ѵ�. 
					// �׷��� ������ �κ����� ��ǰ�� ��ġ�� ã�� �� ����.!
					pclFrom->Decrease(clitem.siItemNum);

					// Ŭ���̾�Ʈ�� ����� ������ ������. 
					cltGameMsgResponse_PersonItemInfo clinfo( i, PERSONITEMINFO_OPTION_NONE, 0, 0, pclFrom, 0);
					cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
					pclchar->SendNetMsg((sPacketHeader*)&clMsg);

/*					// ����ڷκ��� �������� ���� �޽����� ����Ѵ�. 
					sDBRequest_OutputItemFromPerson clMsg(GetID(), pclCI->GetPersonID(), i, &clitem);
					pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);*/
					
					itemnum = 0;
				}
				else
				{
					//cyj ��������ۿ� ��ġ ���� �߰�
					while( pclchar->clItemUseReserveInfo.Push( clitem.siUnique, -clitem.siItemNum, InvPos ) == false )
					{
						pclchar->ItemUseReserveAction();
					}

					// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
					if( pclFrom->siItemNum <= clitem.siItemNum )
					{
						pclchar->ItemUseReserveAction();
					}

					// pclchar->ItemUseReserveAction(); �ؿ� �־�� �Ѵ�. 
					// �׷��� ������ �κ����� ��ǰ�� ��ġ�� ã�� �� ����.!
					pclFrom->Decrease(clitem.siItemNum);

					// Ŭ���̾�Ʈ�� ����� ������ ������. 
					cltGameMsgResponse_PersonItemInfo clinfo( i, PERSONITEMINFO_OPTION_NONE, 0, 0, pclFrom, 0);
					cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
					pclchar->SendNetMsg((sPacketHeader*)&clMsg);

/*					// ����ڷκ��� �������� ���� �޽����� ����Ѵ�. 
					sDBRequest_OutputItemFromPerson clMsg(GetID(), pclCI->GetPersonID(), i, &clitem);
					pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);*/

					itemnum -= clitem.siItemNum;
				}
			}
		}
	}

	return true;
}

