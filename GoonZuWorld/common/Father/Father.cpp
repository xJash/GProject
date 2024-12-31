//---------------------------------
// 2004/2/25 ���°�
//---------------------------------
#include "CommonLogic.h"
#include "..\..\Client\Client.h"

#include "../../lib/WebHTML/WebHTML.h"

#include "Father.h"
#include "..\..\Resource.h"
#include "MsgType-Person.h"
#include "MsgType-System.h"
#include "..\..\Client\Interface\ErrorMsgDlg\ErrorMsgDlg.h"
#include "..\..\Client\Interface\NotifyMsgDlg\NotifyMsgDlg.h"
#include "JwLib\IsCorrectID\IsCorrectID.h"
#include "NInterface/NHintDlg/NHintDlg.h"

#include "../../common/HintDlg/HintDlg.h"
#include "Char\CharManager\CharManager.h"

extern cltCommonLogic* pclClient;


cltFatherManager::cltFatherManager()
{
	m_siSelectedIndex = -1 ;

	bDlgRectInitSwitch	= false;

	bUpdateFatherSwitch				= false;
	bUpdateFatherApplyerListSwitch	= false;
	bUpdateChildListSwitch			= false;
}

cltFatherManager::~cltFatherManager()
{
}

// Ư�� ����ڰ� ����Ʈ�� �����ϴ°�. 
bool cltFatherManager::IsExist(SI32 personid)
{
	SI32 i;

	if(personid <= 0)return false;

	for(i = 0;i < MAX_FATHER_APPLYER_LIST_NUMBER;i++)
	{
		if(clApplyerList[i].siPersonID == personid)
		{
			return true;
		}
	}

	return false;
}

// ���� ��� ��û�ڸ� ���� �Ѵ�. 
bool cltFatherManager::DeleteApplyer(SI32 personid)
{
	SI32 i;

	if(personid <= 0)return false;

	// �̹� �ִ� ���� �ƴ��� Ȯ���Ѵ�. 
	for(i = 0;i < MAX_FATHER_APPLYER_LIST_NUMBER;i++)
	{
		if(clApplyerList[i].siPersonID == personid)
		{
			clApplyerList[i].Init();
		}
	}

	return true;
}

// ����  ��� ��û�ڸ� �߰��Ѵ�. 
bool cltFatherManager::AddApplyer(cltFatherApplyerInfo* pclinfo, SI32* preturnval)
{
	SI32 i;
	SI32 minlevel	= 1000;
	SI32 minindex	= -1;

	if(pclinfo->siPersonID <= 0)return false;
	SI32 id = pclinfo->siCharUnique;
	if(pclClient->pclCM->IsValidID(id) == false)return false;
	SI32 level = pclClient->pclCM->CR[id]->pclCI->clIP.GetLevel();

	// �̹� �ִ� ���� �ƴ��� Ȯ���Ѵ�. 
	for(i = 0;i < MAX_FATHER_APPLYER_LIST_NUMBER;i++)
	{
		if(clApplyerList[i].siPersonID == pclinfo->siPersonID)
		{
			*preturnval = ADD_FATHERSUPPLYER_ALREADY;
			return false;
		}
	}


	// ���ڸ��� ã�� �߰��Ѵ�. 
	for(i = 0;i < MAX_FATHER_APPLYER_LIST_NUMBER;i++)
	{
		if(clApplyerList[i].siCharUnique == 0)
		{
			clApplyerList[i].Set(pclinfo);
			return true;
		}
		else
		{
			if(pclClient->pclCM->IsValidID(clApplyerList[i].siCharUnique))
			{
				SI32 templevel = pclClient->pclCM->CR[ clApplyerList[i].siCharUnique ]->pclCI->clIP.GetLevel();
				if(minlevel > templevel)
				{
					minlevel = templevel;
					minindex = i;
				}
			}
		}
	}

	// ���� ���� ���� ���ٸ� �� ����ڸ� Ż����Ű�� �� ����ڸ� ����Ѵ�. 
	if(minindex >= 0)
	{
		if(level >minlevel)
		{
			clApplyerList[minindex].Set(pclinfo);
			return true;
		}
	}

	*preturnval = ADD_FATHERSUPPLYER_FULL;
	return false;
}

void cltFatherManager::Action(cltCharManager* pclCM)
{
	SI32 i;
	
	// ��ȣõ�� ���θ� ��Ȯ���Ѵ�. 
	for(i = 0;i < MAX_FATHER_APPLYER_LIST_NUMBER;i++)
	{
		clApplyerList[i].bAngelSwitch = false;

		SI16 fatherid = clApplyerList[i].siCharUnique;
		if(pclCM->IsValidID(fatherid) == false)continue;

		if(pclCM->CR[fatherid]->pclCI->clBI.uiAngelSwitch)
		{
			clApplyerList[i].bAngelSwitch = true;
		}
	}
}