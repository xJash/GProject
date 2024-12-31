//---------------------------------
// 2004/4/28 ���°�
//---------------------------------
#include "..\..\Server\Server.h"
#include "Skill\Skill-Manager.h"
#include "..\..\DBManager\GameDBManager_World\DBMsg-Person.h"

//-----------------------------
// Common
//-----------------------------
#include "PersonInfo.h"


extern cltCommonLogic* pclClient;

// ����ڰ� ������ ���� ���� ������ ó���Ѵ�. 
SI32 cltCharServer::CharHorseAction(cltHorse* pclhorse, bool bselfswitch)
{
	if(pclhorse == NULL)			return HORSEACTION_NONE;

	bool bupdateswitch = false;
	
	if(IsPC(GetCharUnique()) == false)return HORSEACTION_NONE;

	cltServer* pclserver = (cltServer*)pclClient;

	//  ������� �����ü� ��������� ���´�. 
#ifdef _SAFE_MEMORY
	SI32 horseskilllevel = pclCI->clCharSkill.GetTotalSkillLevel(SKILL_HORSETRAINING, 0 , 0, &pclCI->clCharItem.clItem[0]);
#else
	SI32 horseskilllevel = pclCI->clCharSkill.GetTotalSkillLevel(SKILL_HORSETRAINING, 0 , 0, pclCI->clCharItem.clItem);
#endif
	SI32 datevary = pclserver->pclTime->clDate.GetDateVary();
	
	SI32 rewardamount	= 0;
	SI32 horseaction	= pclserver->pclHorseManager->Action(pclserver, pclhorse, horseskilllevel, datevary, bselfswitch, &rewardamount);
	if(horseaction == 1)
	{
		// DB�� ���� ���� ������ �����ؾ� �Ѵ�. 
		bupdateswitch = true;
	}
	else if ( horseaction == 3 ) // ���ɷ�����̿�Ƕ�����
	{
		return HORSEATTION_TICKET;
	}
	else if ( horseaction == 4 ) // ���ɷ�����̿�Ƕ�����
	{
		return HORSEATTION_PREMIUMPARTS;
	}
	//KHY - 1001 - ��µ��� 5���� ���� ����. - ���° ���� �״��� �˱����ؼ�// 200 + �������� �ε��������� ��ȯ�ȴ�.
	else if(horseaction >= HORSEACTION_DIE)	// ���ó��. 
	{
		return horseaction;
	}


	// ������ �ִ� ��� �� ���ü� ����ġ�� ��� ��Ų��. 
	if(rewardamount)
	{
		SI32 skillunique	= SKILL_HORSETRAINING;
		SI32 maxskilllevel	= pclClient->pclSkillManager->GetMaxLevel(skillunique);
		if(skillunique >= 0)
		{
			SetSkillUpdate(skillunique, rewardamount * 2);
		}
	}

	if(bupdateswitch)
	{
		return HORSEACTION_UPDATE;
	}

	return HORSEACTION_NONE;
	
}

// �̿����� �� ���� ���¸� �뺸�Ѵ�. 
bool cltCharServer::SendNeighbourMyHorseStatus(SI32 index)
{
	// ������ Ŭ���̾�Ʈ���� ���� ������ ������Ʈ �Ѵ�. 
	SetUpdateSwitch(UPDATE_HORSE, true, 0);
	
	// �̿����� ���� ������ ������Ʈ �Ѵ�. 
	if(index == pclCI->clHorseInfo.siCurrentShowHorse)
	{
		cltHorse* pclhorse = pclCI->clHorseInfo.GetCurrentShowHorse();

		if(pclhorse)
		{
			cltGameMsgResponse_NeighbourHorse clInfo(GetCharUnique(), pclhorse->siHorseUnique);
			cltMsg clMsg(GAMEMSG_RESPONSE_NEIGHBOURHORSE, sizeof(clInfo), (BYTE*)&clInfo);
			SendNeighbourMsg(&clMsg, false);
		}
	}

	return true;

}

// �ڵ����� �� ���̸� �ش�. 
bool cltCharServer::AutoHorseFood(SI32 itemunique, SI32 itemnum)
{
	
	// ���ɻ�ᰡ �ִ��� Ȯ���Ѵ�. 
	SI32 needitemunique	= ITEMUNIQUE(3855);
	SI32 needitemnum	= 1;
	SI32 pos = pclCI->clCharItem.GetItemPos(needitemunique);

	// �����ᰡ �ִ��� Ȯ���Ѵ�.
	if(pos < 0)
	{
		needitemunique = ITEMUNIQUE(3850);
		needitemnum	   = 1;
		pos = pclCI->clCharItem.GetItemPos(needitemunique);

	}

	if(pos < 0)
	{
		pos = pclCI->clCharItem.GetItemPos(itemunique);
		if(pos < 0)return false;

		needitemunique = itemunique;
		needitemnum = itemnum;
	}

	// ������ ��ǰ�� ã�Ҵ�. 
	cltItemUseInfo clinfo(pos, needitemunique);
	((cltServer*)pclClient)->UseItemAction(GetID(), &clinfo);

	// ����ᰡ ������ �ʿ��� ���̰� �ִ��� Ȯ���Ѵ�. 
	return true;
}

// �� ������ DB�� ������Ʈ �Ѵ�. 
void cltCharServer::UpdateHorseToDB(cltServer* pclserver, SI32 index, cltHorse* pclhorse, SI32 reason)
{
	sDBRequest_SetHorse cldbmsg(GetID(), pclCI->GetPersonID(), reason, index, pclhorse);
	pclserver->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&cldbmsg);
}
