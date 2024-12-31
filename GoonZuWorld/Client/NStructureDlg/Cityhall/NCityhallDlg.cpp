#include "NCityhallDlg.h"

#include "NVillageTreeDlg.h"
#include "../StrBaseDlg/StrInfoDlg.h"
#include "../StrBaseDlg/StrPayTaxDlg.h"
#include "../StrBaseDlg/StrRepairDlg.h"
#include "../STrBaseDlg/StrResignChiefDlg.h"

extern cltCommonLogic *pclClient;


NCityhallDlg::NCityhallDlg()
{

}

NCityhallDlg::~NCityhallDlg()
{
	cltClient* pclclient = (cltClient*)pclClient;

    if(pclclient != NULL && pclclient->m_pDialog[ NVILLAGETREE_DLG ] != NULL 
		&& ((NVillageTreeDlg*)pclclient->m_pDialog[ NVILLAGETREE_DLG ])->IsCreate() == true )
		((NVillageTreeDlg*)pclclient->m_pDialog[ NVILLAGETREE_DLG ])->DeleteDialog();

	if( pclclient->m_pDialog[ NGENERALMEETING2_DLG ] )
	{
		pclclient->m_pDialog[ NGENERALMEETING2_DLG ]->DeleteDialog();
	}
}

void NCityhallDlg::Create()
{

	CreateDlg( NCITYHALL_DLG, pclClient->pclCityHallManager );


	// ����� �޴�
	SetTabInfo( 2, 1 );
	TCHAR* pText = GetTxtFromMgr(3461);
	AddUserTabDialog( 0, pText, 80, new NCityhallInfoDlg, 
		TEXT("NInterface/Data/NStructureDlg/DLG_Cityhall_Info.ddf"), TEXT("dialog_cityhallinfo") );

	 pText = GetTxtFromMgr(3462);
	AddUserTabDialog( 1, pText, 80, new NCityhallInfo2Dlg, 
		TEXT("NInterface/Data/NStructureDlg/DLG_Cityhall_Info2.ddf"), TEXT("dialog_cityhallinfo2") );
	
	// ���� ���
	pText = GetTxtFromMgr(3463);
	AddUserTabDialog( 2, pText, 80, new NCityhallStockHolderDlg, TEXT("NInterface/Data/NStructureDlg/DLG_Cityhall_StockHolder.ddf"), TEXT("dialog_cityhallstockholder") );


	 pText = GetTxtFromMgr(3464);
	SetTabInfo( 2, 2 );
	AddUserTabDialog( 3, pText, 80, new NCityhallResidentDlg, 
		TEXT("NInterface/Data/NStructureDlg/DLG_Cityhall_Resident.ddf"), TEXT("dialog_cityhallresident") );

	// KHY - ���� ��ȸ ��ư Ȯ��
	pText = GetTxtFromMgr(3465);
	AddUserTabDialog( 4, pText, 160, new NCityhallGeneralMeetingDlg, TEXT("NInterface/Data/NStructureDlg/DLG_Cityhall_GeneralMeeting.ddf"), TEXT("dialog_cityhallgeneralmeeting") );

	
	if(pclClient->IsCountrySwitch(Switch_DonateDlg)) //KHY - ��α����� ��������.
	{
		pText = GetTxtFromMgr(10163);
		AddUserTabDialog( 5, pText, 100, new NCityhallDonateDlg, TEXT("NInterface/Data/NStructureDlg/DLG_Cityhall_Donate.ddf"), TEXT("dialog_donate") );
	}
#ifdef _CHINA
	SetTabInfo( 2, 3 );

	pText = GetTxtFromMgr(10204);
	 AddUserTabDialog( 6, pText, 80, new NCityhallUserMenuEmpireDlg, TEXT("NInterface/Data/NStructureDlg/DLG_Cityhall_Empire.ddf"), TEXT("dialog_Empire") );
#endif

	// �������� ����
	// pText = GetTxtFromMgr(5254);
	//AddUserTabDialog( 5, pText, 80, new NCityhallDividendListDlg, 
	//	TEXT("NInterface/Data/NStructureDlg/DLG_Cityhall_DividedListDlg.ddf"), TEXT("dialog_cityhalldividedlist") );
	

	// ��� �޴�
	SetTabInfo( 2, 1 );
	 pText = GetTxtFromMgr(3466);
	//cyj ����޴� �ǻ���� 64���� 80���� ����(�������� ���� �޴� ������ ���Ͽ�)
	AddChiefTabDialog( 0, pText, 60, new NCityhallChiefDlg, 
		TEXT("NInterface/Data/NStructureDlg/DLG_Cityhall_Chief.ddf"), TEXT("dialog_cityhallchief") );

	pText = GetTxtFromMgr(3467);
	AddChiefTabDialog( 1, pText, 60, new NCityhallCapitalDlg, 
		TEXT("NInterface/Data/NStructureDlg/DLG_Cityhall_Capital.ddf"), TEXT("dialog_cityhallcapital") );

	if ( ConstServiceArea_China == pclClient->siServiceArea )
	{
		pText = GetTxtFromMgr(3468);
		AddChiefTabDialog( 2, pText, 50, new NCityhallGodDlg, 
			TEXT("NInterface/Data/NStructureDlg/DLG_Cityhall_God.ddf"), TEXT("dialog_cityhallgod") );

		pText = GetTxtFromMgr(5998);
		AddChiefTabDialog( 3, pText, 100, new NCityhallSetBaseMoneyDlg, 
			"NInterface/Data/NStructureDlg/DLG_Cityhall_SetBaseMoney.ddf", "dialog_cityhallsetbasemoney" );
	}
	else
	{
		pText = GetTxtFromMgr(3468);
		AddChiefTabDialog( 2, pText, 60, new NCityhallGodDlg, 
			TEXT("NInterface/Data/NStructureDlg/DLG_Cityhall_God.ddf"), TEXT("dialog_cityhallgod") );

		pText = GetTxtFromMgr(5998);
		AddChiefTabDialog( 3, pText, 90, new NCityhallSetBaseMoneyDlg, 
			"NInterface/Data/NStructureDlg/DLG_Cityhall_SetBaseMoney.ddf", "dialog_cityhallsetbasemoney" );
	}

	SetTabInfo( 2, 2 );

	pText = GetTxtFromMgr(3469);
	AddChiefTabDialog( 4, pText, 90, new NCityhallEventDlg, 
		TEXT("NInterface/Data/NStructureDlg/DLG_Cityhall_Event.ddf"), TEXT("dialog_cityhallevent") );

	//pText = GetTxtFromMgr(1536);	

	//cyj ��û�� �������� ���� �޴� �ӽ� ����
	//pText = GetTxtFromMgr(5052);
	//AddChiefTabDialog( 4, pText, 128, new NCityhallChangeMapDlg, 
	//	TEXT("NInterface/Data/NStructureDlg/DLG_Cityhall_ChangeMap.ddf"), TEXT("dialog_cityhallchangemap") );

	pText = GetTxtFromMgr(3444);	
	AddChiefTabDialog( 5, pText, 90, new NStrRepairDlg, 
		TEXT("NInterface/Data/NStructureDlg/DLG_NStrRepair.ddf"), TEXT("dialog_strrepair") );

	pText = GetTxtFromMgr(3445);
	AddChiefTabDialog( 6, pText, 90, new NStrResignChiefDlg, 
		TEXT("NInterface/Data/NStructureDlg/DLG_NStrResignChief.ddf"), TEXT("dialog_resignchief") );

#ifdef _CHINA
	SetTabInfo( 2, 3 );

	pText = GetTxtFromMgr(10212);
	AddChiefTabDialog( 7, pText, 80, new NCityhallChiefMenuEmpireDlg, TEXT("NInterface/Data/NStructureDlg/DLG_Cityhall_Empire2.ddf"), TEXT("dialog_Empire2") );
#endif

	// [����] �ʺ��� ���� : ��û ��ư���� ���� ���ѻ���
	if ( pclClient->IsCountrySwitch(Switch_TutorialVillage) )
	{
		if ( Const_Beginner_Village == pclClient->pclCityHallManager->siVillageUnique )
		{
			//-- ���� �ܹ�ư
			DisableTabButton( 2 );	// ���� ���
			DisableTabButton( 4 );	// ���� ��ȸ
			if ( pclClient->IsCountrySwitch(Switch_DonateDlg) )
			{
				DisableTabButton( 5 );	// �������
			}
			
			//-- ������ �ܹ�ư
			DisableTabButton( 1, true );
			DisableTabButton( 2, true );
			DisableTabButton( 3, true );
			DisableTabButton( 4, true );
			DisableTabButton( 5, true );
			DisableTabButton( 6, true );
			if ( pclClient->IsWhereServiceArea(ConstServiceArea_China) )
			{
				DisableTabButton( 7, true );
			}
		}
	}




	InitDlg(TRUE);	// CityHallâ ������ ���� ���� ����(�Ļ�, ����,.. ) ������

	SetActionTimer( 200 );
	SetTimerOnOff( true );

}

void NCityhallDlg::GreetingMsg()
{
	// ������ Unique�� ���Ѵ�. 
	TCHAR* pText = GetTxtFromMgr(1610);
	SetMainExplain(pText);
}

void NCityhallDlg::RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen )
{
	switch( MsgIndex )
	{
	// User Tab
	case 0:
	case 1: // NCityhallGeneralMeetingDlg
		((NCityhallGeneralMeetingDlg*)m_pUserChildDlg[ 4 ])->RetMsgBox( RetValue, MsgIndex, pData, DataLen );
		break;
	case 2:
	case 3: // NCityhallResidentDlg
		((NCityhallResidentDlg*)m_pUserChildDlg[ 3 ])->RetMsgBox( RetValue, MsgIndex, pData, DataLen );
		break;
	// Chief Tab		
	case 20:	// NCityhallEventDlg
		((NCityhallEventDlg*)m_pChiefChildDlg[ 4 ])->RetMsgBox( RetValue, MsgIndex, pData, DataLen );
		break;
	case 21:	//NCityhallGodDlg
	case 22:
	case 23:
	case 24:
	case 25:
		((NCityhallGodDlg*)m_pChiefChildDlg[ 2 ])->RetMsgBox( RetValue, MsgIndex, pData, DataLen );
		break;
	case 26:	// NCityhallChangeMapDlg
		((NCityhallChangeMapDlg*)m_pChiefChildDlg[ 4 ])->RetMsgBox( RetValue, MsgIndex, pData, DataLen );
		break;
	case 30:
		((NCityhallChiefDlg*)m_pChiefChildDlg[0])->RetMsgBox( RetValue, MsgIndex, pData, DataLen );
		break;
	case 31:
		((NCityhallDonateDlg*)m_pUserChildDlg[5])->RetMsgBox( RetValue, MsgIndex, pData, DataLen );
		break;
	}
}
