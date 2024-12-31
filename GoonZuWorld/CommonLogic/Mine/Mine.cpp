#include <CommonLogic.h>
#include "Char\CharCommon\Char-Common.h"
#include "Char\CharManager\CharManager.h"

#include "Mine.h"
#include "..\..\Resource.h"

#include "../../CommonLogic/MsgType-Structure.h"
#include "../../CommonLogic/msg/MsgType-Mine.h"

#include "../CityHall/TaxpaymentListDlg.h"
#include "../Server/Server.h"

#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Mine.h"
#include "..\..\Client\Music\Music.h"

extern cltCommonLogic* pclClient;


//----------------------------------------------
// cltMine
//----------------------------------------------
cltMine::cltMine(SI32 sivillageunique) : cltStructureBasic(sivillageunique)
{
	for( int i = 0; i < MAX_MINEUNIT_NUMBER; ++i ) {
		clUnit[ i ].Init();
	}

	 InitRentApplyer();
}


cltMine::~cltMine()
{

}




cltMineManager::cltMineManager(cltCharManager* pclcm, SI32 gamemode, SI32 portraitid, TCHAR *strFileName ) : cltStructureMngBasic(MAX_STOCK_TAB_NUMBER, pclcm, portraitid, strFileName )
{
	

	if(gamemode == GAMEMODE_SERVER)
	{

	}
	else
	{

	}


}


cltMineManager::~cltMineManager()
{
	

}


// ���� ȯ�� �λ縻ǥ��..
void cltMineManager::GreetingMsg(HWND hDlg)
{
	TCHAR* pText = GetTxtFromMgr(3250);
	SetMainExplain(hDlg, pText);
}

void cltMineManager::Do_WM_INITDIALOG(SI32 charunique)
{
	cltStructureMngBasic::Do_WM_INITDIALOG(charunique);
}


// ������ �ż��Ѵ�.
BOOL cltMineManager::CreateMine(SI32 siunique)
{
	if(pclStruct[siunique] == NULL)
	{
		pclStruct[siunique] = new cltMine(siunique);
		return TRUE;
	}

	return FALSE;
}

// �Ӵ�Ḧ ó���ϴµ��� �׼��� ���Ѵ�. 
void cltMineManager::Action( cltTime* pcltime, clock_t CurrentClock )
{
	if(pcltime == NULL)return ;

	// DB �ʱ�ȭ �Ϸ�ɶ����� ��ٸ�
	if( ((cltServer *)pclClient)->bCompleteDBInitAll == FALSE ) return;

	bool bdaychangedswitch = pcltime->IsDayChanged();

	//----------------------------------------
	// ���� �Ӵ���� ó���Ѵ�. 
	//----------------------------------------
	if(bdaychangedswitch)
	{
		SI32 i, j;
		
		cltMine* pclMine ;
		
		for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
		{
			pclMine = (cltMine*)pclStruct[i];
			if(pclMine)
			{
				for(j = 0;j < MAX_MINEUNIT_NUMBER;j++)
				{
					SI32 personid = pclMine->clUnit[j].clPerson.GetPersonID(); 
					
					if(personid <= 0)continue;
					
					// ��� ���ڰ� ���ð� ���� ���̾�� �Ѵ�. (�ſ� ����Ͽ� ���ҵȴ�.)
					if( (SI32)pcltime->clDate.uiDay != pclMine->clUnit[j].clContract.clDate.GetDay())continue;
					
					// �Ӵ�Ḧ ���Ѵ�. 
					GMONEY rentfee		= pclMine->clUnit[j].clContract.siRentFee;

					// ������ ����ũ�� ���Ѵ�. 
					SI32 villageunique	= i;

					// ���� ������ ��ġ�� ���Ѵ�. 
					SI32 Mineindex		= j;
					
					// ���忡�� �Ӵ�Ḧ �������� �ű���� DBManager���� ��û�Ѵ�. 
					sDBRequest_MinePayRentFee clMsg(0, personid, rentfee, villageunique, Mineindex);
					pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

					// ��� �Ⱓ�� ����Ǿ����� Ȯ���Ѵ�. 
					if(pclMine->clUnit[j].clContract.IsEnd(&pcltime->clDate) == true)
					{
						// DB�Ŵ������� ������ ȸ���� ���� ��û�Ѵ�. 
						sDBRequest_MineRecall clMsg(personid, MINERECALL_REASON_CONTRACTEND, villageunique, Mineindex);
						pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
					}
					else
					{
						//----------------------------------------------
						// ��� ���� �ӹ� ����. 
						//----------------------------------------------
						// ���� �ð� ����. 
						SI32 curvary	= pcltime->clDate.GetDateVary();
						
						// ��� ������ ����. 
						cltDate cldate;
						cldate.Set(&pclMine->clUnit[j].clContract.clDate);
						cldate.AddMonth(pclMine->clUnit[j].clContract.siRentPeriod * 12);
						
						SI32 endvary	= cldate.GetDateVary();
						if(endvary <= curvary + 90)
						{
/*
							// ������ ������. 
							cltServer* pclserver = (cltServer*)pclClient;
							cltLetterMsg_MineRecallWarning clletter(villageunique, Mineindex, (endvary - curvary) / 30);
							pclserver->SendLetterMsg( personid, (cltLetterHeader*)&clletter );
*/
						}
						
					}

				}
				
			}
		}

	}
}
BOOL cltMineManager::IsMiner( SI32 villageunique, SI32 personid )
{
	cltMine *pclMine = (cltMine*)pclStruct[ villageunique ];

	for( int i = 0; i < MAX_MINEUNIT_NUMBER; i++ )
	{		
		if( pclMine->clUnit[ i ].clPerson.GetPersonID() == personid ) return TRUE;
	}

	return FALSE;
}



// ���� ����������� Ȯ���Ѵ�. 
BOOL cltMine::IsSameContract( const cltRentContract* pclcontract )
{
	if(clStrInfo.clMineStrInfo.clRentContract.IsSame(pclcontract) == TRUE)
	{
		return TRUE;
	}

	return FALSE;
}

// ���� ��û�Ѵ�. 
BOOL cltMine::AddApplyer( const cltSimplePerson* pclapplyer, const cltRentContract* pclcontract )
{
	SI32 i;
	for( i = 0; i < MAX_APPLY_PER_MINE; i++ ) {

		if(clApplyer[i].clPerson.GetPersonID() == 0)
		{
			clApplyer[i].Set(pclapplyer, pclcontract);
			return TRUE;
		}
	}

	return FALSE;
}

// ���� ��û�ڸ� �����Ѵ�. 
BOOL cltMine::DeleteApplyer( SI32 personid )
{
	SI32 i;

	for(i = 0;i < MAX_APPLY_PER_MINE;i++)
	{
		if(clApplyer[i].clPerson.GetPersonID() == personid)
		{
			clApplyer[i].Init();
			return TRUE;
		}
	}

	return FALSE;
}

// �������� ���θ� Ȯ���Ѵ�. 
BOOL cltMine::IsEmpty(SI32 index)
{
	if(clUnit[index].clPerson.GetPersonID() ) return FALSE;

	return TRUE;
}

//PersonID�� ������ ���� ������� ������ ���Ѵ�. 
cltRentApplyer* cltMine::GetMineApplyerFromPersonID(SI32 personid)
{
	SI32 i;

	for(i = 0;i < MAX_APPLY_PER_MINE;i++)
	{
		if(clApplyer[i].clPerson.GetPersonID() == personid)
		{
			
			return &clApplyer[i];
		}
	}
	return NULL;
}

// �������� ���꿡 ����Ѵ�.
BOOL cltMine::SetRent( SI32 index, const cltSimplePerson* pclapplyer, const cltRentContract* pclcontract )
{
	clUnit[ index ].clPerson.Set( pclapplyer );
	clUnit[ index ].clContract.Set( pclcontract );

	return TRUE;
}

// Ư�� Person�� ���� ������ �������� Ȯ���Ѵ�. 
bool cltMine::IsMineHost(SI32 personid, SI32 Mineunitindex )
{
	if( personid == 0 )return false;
	if( Mineunitindex < 0 || Mineunitindex >= MAX_MINEUNIT_NUMBER ) return false;

	if( clUnit[ Mineunitindex ].clPerson.GetPersonID() == personid )return true;

	return false;
}

// �� ������ �Ӵ�Ḧ ¡���Ѵ�.
void cltMine::GetRentFee()
{
	SI32 i;

	// ���� ������ �˻��Ͽ� �Ӵ�Ḧ ¡���Ѵ�. 
	for( i = 0; i < MAX_MINEUNIT_NUMBER; i++ )
	{
		// �Ӵ밡 �Ǿ� �ִ� ���Ǹ� �˻��Ѵ�.
		SI32 personid = clUnit[i].clPerson.GetPersonID();
		if( personid <= 0 )continue;

		// ������ Ȯ���Ѵ�. 
		GMONEY fee = clUnit[i].clContract.siRentFee;
	}
}


// ���Ӽ����� ���������� ����Ʈ�� ��û�Ѵ�. 
void cltMineManager::RequestMineUnitList()
{
	SI32 id = 1;
	if(id == 0)return;

	cltMsg clMsg(GAMEMSG_REQUEST_MINE_UNITLIST, 0);
	pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

}

// ���Ӽ����� ���������� �� ���� ����Ʈ�� ��û�Ѵ�. 
void cltMineManager::RequestMineUnitListDetail()
{
	SI32 id = 1;
	if(id == 0)return;

	cltMsg clMsg(GAMEMSG_REQUEST_MINE_UNITDETAIL, 0);
	pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

}


// ���Ӽ����� ��������� ����Ʈ�� ��û�Ѵ�. 
void cltMineManager::RequestMineRentApplyerList()
{
	SI32 id = 1;
	if(id == 0)return;

	cltMsg clMsg(GAMEMSG_REQUEST_MINE_APPLYERLIST, 0);
	pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
}


