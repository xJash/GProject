#include <CommonLogic.h>
#include "../../Server/Server.h"
#include "../../Client/Client.h"

#include "NewMarket-Manager.h"

cltNewMarketManager::cltNewMarketManager( cltCharManager* _pclCM, SI32 _siGamemode, SI32 _siRanktype, TCHAR* _pszFileName )
: cltStructureMngBasic( MAX_MARKET_TAB_NUMBER, _pclCM, _siRanktype, _pszFileName )
{
	
}

cltNewMarketManager::~cltNewMarketManager()
{

}

void cltNewMarketManager::Init( void )
{

}

void cltNewMarketManager::Action( bool _bDaychangedswitch )
{
	cltServer* pclserver = (cltServer*)pclClient;

	// DB �ʱ�ȭ �Ϸ�ɶ����� ��ٸ�
	if( ((cltServer*)pclClient)->bCompleteDBInitAll == FALSE ) return;

	

}

void cltNewMarketManager::GreetingMsg( HWND _hDlg )
{
	SetMainExplain( _hDlg,  "�̰� ����?" ); //GetTxtFromMgr(1667); ���� TEXT
}

void cltNewMarketManager::Do_WM_INITDIALOG( SI32 _siCharUnique )
{
	cltStructureMngBasic::Do_WM_INITDIALOG( _siCharUnique );
}

BOOL cltNewMarketManager::CreateNewMarket( SI32 _siVillageUnique )
{
	// ���ָ� �����. 
	if( NULL == pclStruct[_siVillageUnique] )
	{
		pclStruct[_siVillageUnique] = new cltNewMarket( _siVillageUnique );
		return TRUE;
	}



	return FALSE;
}


