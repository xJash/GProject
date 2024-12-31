//---------------------------------
// 2004/1/31 ���°�
//---------------------------------

#include "CommonLogic.h"
#include "..\..\Client\Client.h"

#include "Master.h"
#include "..\Skill\Skill-Manager.h"
#include "Char\CharManager\CharManager.h"


#include "..\..\Resource.h"

#include "../../lib/WebHTML/WebHTML.h"

// �ӼӸ� ä�� ����. 
//#include "..\..\Client\Interface\PrivateChatDlg\PrivateChatBaseInfo.h"
//#include "..\..\Client\Interface\PrivateChatDlg\PrivateChatDlgMgr.h"

#include "..\..\Client\Interface\ErrorMsgDlg\ErrorMsgDlg.h"
#include "..\..\Client\Interface\NotifyMsgDlg\NotifyMsgDlg.h"

//------------------------------
// CommonLogic
//------------------------------
#include "MsgType-System.h"
#include "MsgType-Person.h"

extern cltCommonLogic* pclClient;

cltMasterManager::cltMasterManager()
{
	bDlgRectInitSwitch	= false;

	siCurrentSkillUnique	= 0;
	m_siSelectedIndex = -1 ;
}


cltMasterManager::~cltMasterManager()
{
	
}


void cltMasterManager::Sort(SI32 sisortdata[])
{
	SI32 i;
	SI32 index = 0;

	SI32 tempbuf[ MAX_MASTER_PER_SKILL ];

	for( i = 0; i < MAX_MASTER_PER_SKILL; ++i )
	{
		tempbuf[ i ] = i;
	}

	for(SI32 vill = 0; vill < MAX_MASTER_PER_SKILL  - 1; vill++)
	{
		for(i = vill + 1; i < MAX_MASTER_PER_SKILL; i++)
		{
			int cmpindex1 = tempbuf[ vill ];
			int cmpindex2 = tempbuf[ i ];

			if(sisortdata[cmpindex1] < sisortdata[cmpindex2])
			{
				int temp = tempbuf[ vill ];
				tempbuf[ vill ] = tempbuf[ i ];
				tempbuf[ i ] = temp;
			}
		}

	}

	for(i = 0; i < MAX_MASTER_PER_SKILL; ++i )
	{
		siSkillInfo[index] = tempbuf[ i ];
		index++;
	}

}


// Ư�� ��� �������� ��ϵǾ� �ִ°�.
bool cltMasterManager::IsRegisterd(SI32 id, SI32 skillunique)
{
	SI32 i;

	if(id <= 0)return false;
	

	for(i = 0;i < clMasterInfo[skillunique].siRegistedNumber;i++)
	{
		if(clMasterInfo[skillunique].clUnit[i].siCharUnique == id)return true;
	}

	return false;
}

// Ư�� ��� ���ο��� �����Ѵ�.
bool cltMasterManager::Unregist(SI32 id, SI32 skillunique)
{
	SI32 i, j;

	if(id <= 0)return false;

/*	if(skillunique == 30)
	{
		SI32 a = 0;
	}
*/

	for(i = 0;i < clMasterInfo[skillunique].siRegistedNumber;i++)
	{
		if(clMasterInfo[skillunique].clUnit[i].siCharUnique == id)
		{
			for(j = i + 1;j < MAX_MASTER_PER_SKILL;j++)
			{
				clMasterInfo[skillunique].clUnit[j - 1].Set( &clMasterInfo[skillunique].clUnit[j]);
				clMasterInfo[skillunique].clUnit[j].Init();
			}

			// ��ϵ� ������ ���δ�. 
			if(clMasterInfo[skillunique].siRegistedNumber > 0)
			{
				clMasterInfo[skillunique].siRegistedNumber--;
			}

			return true;
		}
	}

	return false;
}

// Ư�� ����ڰ� Ư�� ����� �ְ� �����ΰ� ?
bool cltMasterManager::IsTopSkill(SI32 id, SI32 skillunique)
{
	if(clMasterInfo[skillunique].clUnit[0].siCharUnique == id)return true;

	return false;

}

// Ư�� ����� �ι�° ������ ���Ѵ�. 
SI32 cltMasterManager::GetSecondSkillID(SI32 skillunique)
{
	return clMasterInfo[skillunique].clUnit[1].siCharUnique;
}

// Ư�� ��� �������� ����Ѵ�.
bool cltMasterManager::Regist(SI32 id, SI32 skillunique, SI32 skilllevel, SI32 personid)
{
	SI32 i, j;

	// �̹� ��ϵǾ� ���� �ʾƾ� �Ѵ�. 
	if(IsRegisterd(id, skillunique) == true)return false;

	for(i = 0;i < MAX_MASTER_PER_SKILL;i++)
	{
		// ����̶�� �߰��Ѵ�. 
		if(clMasterInfo[skillunique].clUnit[i].siCharUnique == 0)
		{
			clMasterInfo[skillunique].clUnit[i].siCharUnique	= id;
			clMasterInfo[skillunique].clUnit[i].siSkillLevel	= skilllevel;
			clMasterInfo[skillunique].clUnit[i].siPersonID		= personid;
			
			// ��ϵ� ������ ���δ�. 
			clMasterInfo[skillunique].siRegistedNumber++;

			return true;
		}
		// �̹� �����Ǿ� �ִ� ���̶��, 
		else if(clMasterInfo[skillunique].clUnit[i].siSkillLevel < skilllevel)
		{
			for(j = (MAX_MASTER_PER_SKILL - 1 - 1);j >= i;j--)
			{
				clMasterInfo[skillunique].clUnit[j + 1].Set( &clMasterInfo[skillunique].clUnit[j] );
			}

			clMasterInfo[skillunique].clUnit[i].siCharUnique	= id;
			clMasterInfo[skillunique].clUnit[i].siSkillLevel	= skilllevel;
			clMasterInfo[skillunique].clUnit[i].siPersonID		= personid;


			// ��ϵ� ������ ���δ�. 
			if(clMasterInfo[skillunique].siRegistedNumber < MAX_MASTER_PER_SKILL)
			{
				clMasterInfo[skillunique].siRegistedNumber++;
			}
			

			return true;
		}
	}

	return false;
}

bool cltMasterManager::Delete(SI32 id)
{
	SI32 skillnum;

	for(skillnum = 0; skillnum < MAX_SKILL_NUMBER;skillnum++)
	{
		Unregist(id, skillnum);
	}

	return true;
}