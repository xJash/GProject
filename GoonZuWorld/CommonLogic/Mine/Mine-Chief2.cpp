#include <CommonLogic.h>
#include "..\..\Server\Server.h"
#include "Char\CharCommon\Char-Common.h"

//-------------------------------------
// Common
//-------------------------------------
#include "PersonInfo.h"
#include "..\..\Common\Util\Control\Control.h"
#include "Char\CharManager\CharManager.h"

#include "..\..\Resource.h"

#include "Mine.h"

#include "MsgRval-Define.h"
#include "../../CommonLogic/MsgType-Structure.h"
#include "../../CommonLogic/Msg/MsgType-Mine.h"

extern cltCommonLogic* pclClient;



// ���Ӽ����� ���������� ����Ʈ�� ��û�Ѵ�. 
void cltMineManager::RequestMineUnitList()
{
	SI32 id = 1;
	if(id == 0)return;

	cltMsg clMsg(GAMEMSG_REQUEST_MINE_UNITLIST, 0);
	pclClient->pclCM->CR[id]->SendNetMsg((char*)&clMsg);

}

// ���Ӽ����� ���������� �� ���� ����Ʈ�� ��û�Ѵ�. 
void cltMineManager::RequestMineUnitListDetail()
{
	SI32 id = 1;
	if(id == 0)return;

	cltMsg clMsg(GAMEMSG_REQUEST_MINE_UNITDETAIL, 0);
	pclClient->pclCM->CR[id]->SendNetMsg((char*)&clMsg);

}


// ���Ӽ����� ��������� ����Ʈ�� ��û�Ѵ�. 
void cltMineManager::RequestMineRentApplyerList()
{
	SI32 id = 1;
	if(id == 0)return;

	cltMsg clMsg(GAMEMSG_REQUEST_MINE_APPLYERLIST, 0);
	pclClient->pclCM->CR[id]->SendNetMsg((char*)&clMsg);
}



// ��� ������ �����ش�. 
BOOL cltMineManager::ShowRentContract(HWND hDlg)
{
	char buffer[256];

	sprintf(buffer, "%d", clClientStrInfo.clMineStrInfo.clRentContract.siRentFee);
	SetDlgItemText(hDlg, IDC_EDIT_SETRENTFEE, buffer);

	sprintf(buffer, "%d", clClientStrInfo.clMineStrInfo.clRentContract.siRentPeriod);
	SetDlgItemText(hDlg, IDC_EDIT_SETRENTPERIOD, buffer);

	return TRUE;
}


// ���� ����Ʈ ������ �����ش�. 
BOOL cltMineManager::ShowMineUnitListInChief(HWND hDlg)
{
	SI32 i;
	char buffer[256];

	// ���� ����Ʈ�� �����. 
	ListDelete(hDlg, IDC_LIST_MINEUNITLISTINCHIEF);

	for( i = 0;i < MAX_MINEUNIT_NUMBER; i++)
	{
		if(clClientUnit[i].clPerson.GetPersonID() == 0)
		{
			char* pText = GetTxtFromMgr(3245);
			sprintf(buffer, "%d %s", i+1, pText);			
		}
		else
		{
			sprintf(buffer, "%d %s", i+1, clClientUnit[i].clPerson.GetName());
		}

		ListAddString(hDlg, IDC_LIST_MINEUNITLISTINCHIEF, (LPARAM)buffer);
	}

	return TRUE;
}

// ���� ���� ������� ����Ʈ�� �����ش�. 
BOOL cltMineManager::ShowMineApplyerListInChief(HWND hDlg)
{
	SI32 i;
	char buffer[256];

	// ���� ����Ʈ�� �����. 
	ListDelete(hDlg, IDC_LIST_MINEAPPLYERLIST);

	for( i = 0; i < MAX_APPLY_PER_MINE; i++ )
	{
		if(clClientApplyer[i].clPerson.GetPersonID() == 0)
		{
			char* pText = GetTxtFromMgr(1692);
			sprintf(buffer, "%d %s", i+1, pText);			
		}
		else
		{
			sprintf(buffer, "%d %s", i+1, clClientApplyer[i].clPerson.GetName());
		}

		ListAddString(hDlg, IDC_LIST_MINEAPPLYERLIST, (LPARAM)buffer);
	}

	return TRUE;
}

// ���õ� ���� ����Ʈ�� ������ �����ش�. 
BOOL cltMineManager::ShowSelectedMineUnitExplain(HWND hDlg, SI32 index)
{
	char buffer[256];
	char date[128];
	if(index < 0)return FALSE;

	// ��� �������� ���Ѵ�. 
	cltDate cldate;
	cldate.Set(&clClientUnit[index].clContract.clDate);
	cldate.AddMonth(clClientUnit[index].clContract.siRentPeriod*12);
	
	cldate.GetDateText(date);

	char* pText = GetTxtFromMgr(1825);
	sprintf(buffer, pText, 
		index+1, 
		clClientUnit[index].clPerson.GetName(),
		clClientUnit[index].clContract.siRentFee,
		date);

	SetDlgItemText(hDlg, IDC_EDIT_MINEUNITEXPLAIN, buffer);
	
	return TRUE;
}

