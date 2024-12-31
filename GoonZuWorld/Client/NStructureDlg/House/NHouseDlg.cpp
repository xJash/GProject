#include "NHouseDlg.h"

#include "../StrBaseDlg/StrInfoDlg.h"
#include "../StrBaseDlg/StrPayTaxDlg.h"
#include "../StrBaseDlg/StrRepairDlg.h"
#include "../STrBaseDlg/StrResignChiefDlg.h"


#include "Char\CharManager\CharManager.h"
//#include "..\..\Server\Rank\Rank.h"

#include "../../CommonLogic/MsgType.h"
#include "../../CommonLogic/MsgType-Structure.h"

#include "../Lib/JYLibFunction.h"
#include "../CommonLogic/MsgType-House.h"



extern cltCommonLogic *pclClient;


NHouseDlg::NHouseDlg()
{

}

NHouseDlg::~NHouseDlg()
{

}

void NHouseDlg::Create()
{

	CreateDlg( NHOUSE_DLG, pclClient->pclHouseManager, 3 );

	// ����� �޴�
	SetTabInfo( 1, 1 );
	TCHAR* pText = GetTxtFromMgr(3457);
	//PCK - ���ο� â�� �������̽� ���� (�� â�� ��� �߰�)
	if ( pclClient->IsCountrySwitch(Switch_ChangeHouseList) )
	{
		AddUserTabDialog( 0, pText, 80, new NHouseNewListDlg, TEXT("NInterface/Data/NStructureDlg/DLG_HouseNewList.ddf"), TEXT("dialog_houselist") );		
	}
	else
	{
		AddUserTabDialog( 0, pText, 80, new NHouseListDlg, TEXT("NInterface/Data/NStructureDlg/DLG_HouseList.ddf"), TEXT("dialog_houselist") );
	}
	pText = GetTxtFromMgr(3458);
	AddUserTabDialog( 1, pText, 80, new NHouseUserDlg, TEXT("NInterface/Data/NStructureDlg/DLG_HouseUser.ddf"), TEXT("dialog_houseuser") );
	pText = GetTxtFromMgr(3459);
	AddUserTabDialog( 2, pText, 80, new NStrInfoDlg, TEXT("NInterface/Data/NStructureDlg/DLG_NStrInfoDlg.ddf"), TEXT("dialog_strinfo") );
	

	// ��� �޴�
	SetTabInfo( 1, 1 );

	pText = GetTxtFromMgr(3460);
	AddChiefTabDialog( 0, pText, 67, new NHouseChiefDlg, TEXT("NInterface/Data/NStructureDlg/DLG_HouseChief.ddf"), TEXT("dialog_housechief") );
	pText = GetTxtFromMgr(3443);
	AddChiefTabDialog( 1, pText, 67, new NStrPayTaxDlg, TEXT("NInterface/Data/NStructureDlg/DLG_NStrPayTaxDlg.ddf"), TEXT("dialog_strpaytax") );
	pText = GetTxtFromMgr(3444);
	AddChiefTabDialog( 2, pText, 67, new NStrRepairDlg, TEXT("NInterface/Data/NStructureDlg/DLG_NStrRepair.ddf"), TEXT("dialog_strrepair") );
	pText = GetTxtFromMgr(3445);
	AddChiefTabDialog( 3, pText, 67, new NStrResignChiefDlg, TEXT("NInterface/Data/NStructureDlg/DLG_NStrResignChief.ddf"), TEXT("dialog_resignchief") );
	InitDlg();

	SetActionTimer( 200 );
	SetTimerOnOff( true );

}


void NHouseDlg::RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen )
{
	switch( MsgIndex )
	{
	case 0:
		{
			if(RetValue)
			{
				cltHouseManager *pHouseManager = ((cltHouseManager *)m_pStrManager);
				//������ �޽����� ������ �ؾ��Ѵ�.				
				cltGameMsgRequest_HouseCancellation clinfo( pHouseManager->siVillageUnique, pHouseManager->siSelectedHouseUnitNumber );
				cltMsg clMsg(GAMEMSG_REQUEST_HOUSECANCELLATION ,sizeof(clinfo), (BYTE *)&clinfo );
				pclClient->pclCM->CR[ 1 ]->SendNetMsg( (sPacketHeader*) &clMsg );
			}

		}
		break;

	}
}


void NHouseDlg::GreetingMsg()
{
	TCHAR* pText = GetTxtFromMgr(1698);
	SetMainExplain(pText);
}


