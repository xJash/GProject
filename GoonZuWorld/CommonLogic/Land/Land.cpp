#include <CommonLogic.h>
#include "Char\CharCommon\Char-Common.h"
#include "Char\CharManager\CharManager.h"

#include "Land.h"
#include "..\..\Resource.h"

#include "../../CommonLogic/MsgType-Structure.h"
#include "../../CommonLogic/msg/MsgType-Land.h"

#include "../CityHall/TaxpaymentListDlg.h"
#include "../Server/Server.h"

#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Land.h"
#include "..\..\Client\Music\Music.h"

extern cltCommonLogic* pclClient;


//----------------------------------------------
// cltLand
//----------------------------------------------
cltLand::cltLand(SI32 sivillageunique) : cltStructureBasic(sivillageunique)
{
	for( int i = 0; i < MAX_LANDUNIT_NUMBER; ++i ) {
		clUnit[ i ].Init();
	}

	 InitRentApplyer();
}


cltLand::~cltLand()
{

}




cltLandManager::cltLandManager(cltCharManager* pclcm, SI32 gamemode, SI32 Landraitid, TCHAR *strFileName ) : cltStructureMngBasic(MAX_STOCK_TAB_NUMBER, pclcm, Landraitid, strFileName )
{
	

	if(gamemode == GAMEMODE_SERVER)
	{

	}
	else
	{

	}

	
}


cltLandManager::~cltLandManager()
{
	
	
}


// ���� ȯ�� �λ縻ǥ��..
void cltLandManager::GreetingMsg(HWND hDlg)
{
	TCHAR* pText = GetTxtFromMgr(1829);
	SetMainExplain(hDlg, pText);
}

void cltLandManager::Do_WM_INITDIALOG(SI32 charunique)
{
	cltStructureMngBasic::Do_WM_INITDIALOG(charunique);
}


// ������ �ż��Ѵ�.
BOOL cltLandManager::CreateLand(SI32 siunique)
{
	if(pclStruct[siunique] == NULL)
	{
		pclStruct[siunique] = new cltLand(siunique);
		return TRUE;
	}

	return FALSE;
}

// �Ӵ�Ḧ ó���ϴµ��� �׼��� ���Ѵ�. 
void cltLandManager::Action( cltTime* pcltime, clock_t CurrentClock )
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
		
		cltLand* pclLand ;
		
		for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
		{
			pclLand = (cltLand*)pclStruct[i];
			if(pclLand)
			{
				for(j = 0;j < MAX_LANDUNIT_NUMBER;j++)
				{
					SI32 personid = pclLand->clUnit[j].clPerson.GetPersonID(); 
					
					if(personid <= 0)continue;
					
					// ��� ���ڰ� ���ð� ���� ���̾�� �Ѵ�. (�ſ� ����Ͽ� ���ҵȴ�.)
					if( (SI32)pcltime->clDate.uiDay != pclLand->clUnit[j].clContract.clDate.GetDay())continue;
					
					// �Ӵ�Ḧ ���Ѵ�. 
					GMONEY rentfee		= pclLand->clUnit[j].clContract.siRentFee;

					// ������ ����ũ�� ���Ѵ�. 
					SI32 villageunique	= i;

					// ���� ������ ��ġ�� ���Ѵ�. 
					SI32 Landindex		= j;
					
					// ���忡�� �Ӵ�Ḧ �������� �ű���� DBManager���� ��û�Ѵ�. 
					sDBRequest_LandPayRentFee clMsg(0, personid, rentfee, villageunique, Landindex);
					pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

					((cltServer *)pclClient)->pclDelMoneyStatistics->Add(DELMONEY_SERVICECHARGE, rentfee);

					// ��� �Ⱓ�� ����Ǿ����� Ȯ���Ѵ�. 
					if(pclLand->clUnit[j].clContract.IsEnd(&pcltime->clDate) == true)
					{
						// DB�Ŵ������� ������ ȸ���� ���� ��û�Ѵ�. 
						sDBRequest_LandRecall clMsg(personid, LANDRECALL_REASON_CONTRACTEND, villageunique, Landindex);
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
						cldate.Set(&pclLand->clUnit[j].clContract.clDate);
						cldate.AddMonth(pclLand->clUnit[j].clContract.siRentPeriod * 12);
						
						SI32 endvary	= cldate.GetDateVary();
						if(endvary <= curvary + 90)
						{
							// ������ ������. 
							cltServer* pclserver = (cltServer*)pclClient;
							cltLetterMsg_LandRecallWarning clletter(villageunique, Landindex, (endvary - curvary) / 30);
							pclserver->SendLetterMsg( personid, (cltLetterHeader*)&clletter );
						}
						
					}

				}
				
			}
		}

	}
}
BOOL cltLandManager::IsFarmer( SI32 villageunique, SI32 personid )
{
	cltLand *pclLand = (cltLand*)pclStruct[ villageunique ];

	for( int i = 0; i < MAX_LANDUNIT_NUMBER; i++ )
	{		
		if( pclLand->clUnit[ i ].clPerson.GetPersonID() == personid ) return TRUE;
	}

	return FALSE;
}



// ���� ����������� Ȯ���Ѵ�. 
BOOL cltLand::IsSameContract( const cltRentContract* pclcontract )
{
	if(clStrInfo.clLandStrInfo.clRentContract.IsSame(pclcontract) == TRUE)
	{
		return TRUE;
	}

	return FALSE;
}

// ���� ��û�Ѵ�. 
BOOL cltLand::AddApplyer( const cltSimplePerson* pclapplyer, const cltRentContract* pclcontract )
{
	SI32 i;
	for( i = 0; i < MAX_APPLY_PER_LAND; i++ ) {

		if(clApplyer[i].clPerson.GetPersonID() == 0)
		{
			clApplyer[i].Set(pclapplyer, pclcontract);
			return TRUE;
		}
	}

	return FALSE;
}

// ���� ��û�ڸ� �����Ѵ�. 
BOOL cltLand::DeleteApplyer( SI32 personid )
{
	SI32 i;

	for(i = 0;i < MAX_APPLY_PER_LAND;i++)
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
BOOL cltLand::IsEmpty(SI32 index)
{
	if(clUnit[index].clPerson.GetPersonID() ) return FALSE;

	return TRUE;
}

//PersonID�� ������ ���� ������� ������ ���Ѵ�. 
cltRentApplyer* cltLand::GetLandApplyerFromPersonID(SI32 personid)
{
	SI32 i;

	for(i = 0;i < MAX_APPLY_PER_LAND;i++)
	{
		if(clApplyer[i].clPerson.GetPersonID() == personid)
		{
			
			return &clApplyer[i];
		}
	}
	return NULL;
}

// �������� ���忡 ����Ѵ�.
BOOL cltLand::SetRent( SI32 index, const cltSimplePerson* pclapplyer, const cltRentContract* pclcontract )
{
	clUnit[ index ].clPerson.Set( pclapplyer );
	clUnit[ index ].clContract.Set( pclcontract );

	return TRUE;
}

// Ư�� Person�� ���� ������ �������� Ȯ���Ѵ�. 
bool cltLand::IsLandHost(SI32 personid, SI32 landunitindex )
{
	if( personid == 0 )return false;
	if( landunitindex < 0 || landunitindex >= MAX_LANDUNIT_NUMBER ) return false;

	if( clUnit[ landunitindex ].clPerson.GetPersonID() == personid )return true;

	return false;
}

// �� ������ �Ӵ�Ḧ ¡���Ѵ�.
void cltLand::GetRentFee()
{
	SI32 i;

	// ���� ������ �˻��Ͽ� �Ӵ�Ḧ ¡���Ѵ�. 
	for( i = 0; i < MAX_LANDUNIT_NUMBER; i++ )
	{
		// �Ӵ밡 �Ǿ� �ִ� ���Ǹ� �˻��Ѵ�.
		SI32 personid = clUnit[i].clPerson.GetPersonID();
		if( personid <= 0 )continue;

		// ������ Ȯ���Ѵ�. 
		GMONEY fee = clUnit[i].clContract.siRentFee;
	}
}



// ���Ӽ����� ���������� ����Ʈ�� ��û�Ѵ�. 
void cltLandManager::RequestLandUnitList()
{
	SI32 id = 1;
	if(id == 0)return;

	cltMsg clMsg(GAMEMSG_REQUEST_LAND_UNITLIST, 0);
	pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

}

// ���Ӽ����� ���������� �� ���� ����Ʈ�� ��û�Ѵ�. 
void cltLandManager::RequestLandUnitListDetail()
{
	SI32 id = 1;
	if(id == 0)return;

	cltMsg clMsg(GAMEMSG_REQUEST_LAND_UNITDETAIL, 0);
	pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

}


// ���Ӽ����� ��������� ����Ʈ�� ��û�Ѵ�. 
void cltLandManager::RequestLandRentApplyerList()
{
	SI32 id = 1;
	if(id == 0)return;

	cltMsg clMsg(GAMEMSG_REQUEST_LAND_APPLYERLIST, 0);
	pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
}


