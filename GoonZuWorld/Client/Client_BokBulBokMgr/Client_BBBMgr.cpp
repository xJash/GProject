#include "Client_BBBMgr.h"

#include "../../NLib/NUtil.h"

#include "Char/CharManager/CharManager.h"
#include "../CommonLogic/CommonLogic.h"
#include "../Lib/dxutil.h"
#include "../../Client/Client.h"

#include "../InterfaceMgr/InterfaceFile.h"
#include "../InterfaceMgr/InterfaceMgr.h"
#include "../InterfaceMgr/DialogController.h"

#include "../Interface/ErrorMsgDlg/ErrorMsgDlg.h"
#include "../Interface/NotifyMsgDlg/NotifyMsgDlg.h"

#include "../ninterface/nrareitemdlg/NRareItemDlg.h"
#include "../NInterface/NCommonMsgDlg/NCommonMsgDlg.h"
#include "../ninterface/NBokBulBokEventDlg/NBokBulBokEventReserveListDlg.h"
#include "../ninterface/NBokBulBokEventDlg/NBokBulBokEventDlg.h"

#include "../../CommonLogic/MsgType.h"
#include "../../CommonLogic/Msg/MsgType-BokBulBok.h"







CClient_BBBMgr::CClient_BBBMgr()
{
	m_bWaitListResult = false;
	m_dwStageStartTime = 0;
	m_bStageStartFlag = false;

	m_siStageStartDelay = 6000;
	m_siStageLoseDelay = 5000;
	m_siStageWinDelay = 5000;
	m_siTotalStageWinDelay = 5000;
	m_siStagePlayDelay = 15000;
	m_b3secDelay = false;

	m_bGMShowMonsterType = false;

	if ( pclClient->IsCountrySwitch(Switch_BokBulBok) == true )
	{
		_Load_BBBGameInfo();
	}
}

CClient_BBBMgr::~CClient_BBBMgr()
{
}


void CClient_BBBMgr::Action()
{
	cltClient* pClient = (cltClient*)pclClient;
	cltCharClient* pclChar = pClient->pclCM->GetCharClient( 1 );
	if ( NULL == pclChar )
	{
		_Clear_BBBStatus();
		return;
	}
	else
	{
		if ( true == m_bStageStartFlag )
		{
			if ( PLAY_MAP_INDEX == pclChar->GetMapIndex() )
			{
				cltMapCommon* pclmap = pClient->pclMapManager->GetMapPointer( PLAY_MAP_INDEX );
				if ( NULL != pclmap )
				{
					SI32 siColl = pclmap->CalcCollInfo( pclChar->GetX(), pclChar->GetY());
					if( 0 == (siColl & BLOCK_EVENT2 || siColl & BLOCK_EVENT3 || siColl & BLOCK_EVENT5 || siColl & BLOCK_EVENT6) )		// 2, 3, 5, 6�� �̺�Ʈ Ÿ���� ��� ���� ������
					{
						_Clear_BBBStatus();   
					}
				}
				else						// �̺�Ʈ �� ��ü�� ����.
				{
					_Clear_BBBStatus();
				}
			}
			else							// ������ �̺�Ʈ �ʿ� ����.
			{
				_Clear_BBBStatus();
			}
		}
	}

	// �������� �����Ҷ� 5�� ī��Ʈ -> ���� -> �÷���Ÿ��(15��) ī��Ʈ
	if ( true == pclChar->bBBBEvent_5SecCountDownFlag )
	{
		if ( (pclChar->siBBBEvent_5SecCountDown + m_siStageStartDelay) < pClient->CurrentClock )
		{
			// 5�� ī��Ʈ ����
			pclChar->bBBBEvent_5SecCountDownFlag = false;
			pclChar->siBBBEvent_5SecCountDown = 0;

			// �÷���Ÿ�� ī��Ʈ + ���� ǥ�� ����
			pClient->bTimeCount = true;
			pClient->siTimeSet	=	m_siStagePlayDelay;				// 15��..�ʴ����� �ֽ��ϴ�~
			pClient->dwWriteSetTime	=	pclClient->CurrentClock;	// �ð��� ������ �ð�
		}
	}

	if ( true == pclChar->bBBBEvent_StageFailFlag )
	{
		if ( (pclChar->siBBBEvent_StageFailCountDown + m_siStageLoseDelay) < pClient->CurrentClock )
		{
			pclChar->bBBBEvent_StageFailFlag = false;
			pclChar->siBBBEvent_StageFailCountDown = 0;

			m_b3secDelay = true;
			pclChar->siBBBEvent_TotalStageClearCountDown = pClient->CurrentClock + 1000;
		}
	}

	if ( true == m_b3secDelay )
	{
		if ( pclChar->siBBBEvent_TotalStageClearCountDown < pClient->CurrentClock )
		{
			m_b3secDelay = false;
			m_bStageStartFlag = false;
			pclChar->bBBBEvent_TotalStageClearFlag = true;
			pclChar->siBBBEvent_TotalStageClearCountDown = pClient->CurrentClock;
		}
	}

	if ( true == pclChar->bBBBEvent_TotalStageClearFlag )
	{
		if ( pclChar->siBBBEvent_TotalStageClearCountDown + m_siStageLoseDelay < pClient->CurrentClock )
		{
			pclChar->bBBBEvent_TotalStageClearFlag = false;
			pclChar->siBBBEvent_TotalStageClearCountDown = 0;
		}
	}

	if ( true == pclChar->bBBBEvent_StageClearFlag )
	{
		if ( (pclChar->siBBBEvent_StageClearCountDown + m_siStageWinDelay) < pClient->CurrentClock )
		{
			pclChar->bBBBEvent_StageClearFlag = false;
			pclChar->siBBBEvent_StageClearCountDown = 0;
		}
	}
}

void CClient_BBBMgr::Warp_GameStage(SI32 siPersonID)
{
	// ������ ����
	//m_pClient_BBBMgr->Warp_GameStage(siCharPersonID); // �̰� ������ ����;;
}

// ���� ��� ������̰� ���ฮ��Ʈ ����Ҷ� �ߴ� �޼���.
void CClient_BBBMgr::Pop_WaitListDlg()
{
	//����Ʈ�� �����ϰڳĴ� ��ȭ���� �˾�.
	cltClient* pClient = (cltClient*)pclClient;

	if (pClient->m_pDialog[NCOMMONMSG_DLG] == NULL)
	{
		pClient->CreateInterface( NCOMMONMSG_DLG );
	}

	((CNCommonMsgDlg*)pClient->m_pDialog[NCOMMONMSG_DLG])->Set(COMMONDLG_BBB_WAIT_QUESTION);
	//((CNCommonMsgDlg*)pClient->m_pDialog[NCOMMONMSG_DLG])->SetShowTimeSec(10);	// ��� ���� �ð� 10��.
}

// ���Һ� �����ڸ���Ʈ�� �� á���� �ߴ� �޼���
void CClient_BBBMgr::Pop_EntryFailDlg()
{
	cltClient* pClient = (cltClient*)pclClient;

	TCHAR*	pTitle	= GetTxtFromMgr(40065); // ���Һ� ����
	TCHAR*	pBody	= GetTxtFromMgr(40076); // ���ݸ� �� ���� ������~ �ѹ� �����̳׿�. ��� �ڿ� ��û�� �ּ���.
	pClient->m_pDialog[NOTIFYMSG_DLG]->SetText(pTitle, pBody);

	//pClient->m_pDialog[NOTIFYMSG_DLG]->DeleteDialog();

}

// ����� ����Ʈ�� ������ ���� ���԰�, �� �̸����� ��ȭ���ڿ� ä���� ��ȭ���ڸ� �����
void CClient_BBBMgr::Pop_DetailWaitListDlg(TCHAR** ppWaitList, bool bResult, GMONEY siTotalMoney )
{
	if ( NULL == ppWaitList ) return;
	cltClient* pClient = (cltClient*)pclClient;

	cltCharClient* pclChar = pclClient->pclCM->GetCharClient( 1 );
	if ( NULL == pclChar )
	{
		return;
	}

	// ����� ����Ʈ ��Ȳ�� �����ִ� ��ȭ���ڸ� ���
	if (pClient->m_pDialog[NBOKBULBOK_RESERVELIST_DLG] == NULL)
	{
		pClient->CreateInterface( NBOKBULBOK_RESERVELIST_DLG );

		// ���� ����� ����Ʈ â�� �㶧�� ���� �޼���â �����. 
		// ���Ŀ� ��â �������� ����� ��û ��ư������ ���� ���� ����� �������� ���ƿ͵� �޼���â�� ����� �ʴ´�. 
		// ��� ������ ���� �޼���â�� ���.
		if ( false == bResult ) // ��� ���� �� 
		{
			// ���� ��Ȳ �˷��ִ� ��ȭ���� ���
			cltClient* pClient = (cltClient*)pclClient;

			TCHAR*	pTitle	= GetTxtFromMgr(40065); // ���Һ� ����
			TCHAR*	pBody	= GetTxtFromMgr(40029); // ����� ��ܿ� ��� ����
			pClient->m_pDialog[NOTIFYMSG_DLG]->SetText(pTitle, pBody);
		}
	}

	((CBokBulBokEventReserveListDlg*)pClient->m_pDialog[NBOKBULBOK_RESERVELIST_DLG])->SetListData( ppWaitList );
	//((CNCommonMsgDlg*)pClient->m_pDialog[NCOMMONMSG_DLG])->SetShowTimeSec();	// ��� ���� �ð� 10��.


	// ����� ��� ��û�� ���� ����� �˷��ִ� ��ȭ���� ��� (����� ��� ����/���п� ����)
	m_bWaitListResult = bResult;		// ó�� ����� Ŭ���̾�Ʈ�� BBB�Ŵ����� �����صΰ�,

	// ó�� ����� ���� ��ȭ���ڸ� ���
	if ( true == bResult )
	{
		// ����� ��Ͽ� �����ߴٴ� �޼���â
		cltClient* pClient = (cltClient*)pclClient;

		TCHAR*	pTitle	= GetTxtFromMgr(40065); // ���Һ� ����
		TCHAR*	pBody	= GetTxtFromMgr(40074); // ����� ��ϵǼ̽��ϴ�.���ݸ� ��ٸ��� �����Ͻ� �� �־��.
		pClient->m_pDialog[NOTIFYMSG_DLG]->SetText(pTitle, pBody);
	}
	else
	{
		// ����� ��� ��û ������ ����Ʈ�� Ǯ �Ǵ� �ٶ��� ��� ���ϰ� ����Ʈ�� ���� ��Ȳ.
	}
}

void CClient_BBBMgr::Pop_WaitListCancelResult()
{
	cltClient* pClient = (cltClient*)pclClient;

	cltCharClient* pclChar = pclClient->pclCM->GetCharClient( 1 );
	if ( NULL == pclChar )
	{
		return;
	}

	// ��� ����Ʈ���� �������ٴ°� �˷��ִ� ��ȭ���� ���
	TCHAR*	pTitle	= GetTxtFromMgr(40065); // ���Һ� ����
	TCHAR*	pBody	= GetTxtFromMgr(40112); // ����� ��ܿ��� ���� �Ǿ����ϴ�.
	pClient->m_pDialog[NOTIFYMSG_DLG]->SetText(pTitle, pBody);
}

void CClient_BBBMgr::RefreshWaitList(TCHAR** ppWaitList)
{
	if ( NULL == ppWaitList ) return;
	cltClient* pClient = (cltClient*)pclClient;

	cltCharClient* pclChar = pclClient->pclCM->GetCharClient( 1 );
	if ( NULL == pclChar )
	{
		return;
	}

	// ����� ����Ʈ ��Ȳ�� �����ִ� ��ȭ���ڸ� ���
	if (pClient->m_pDialog[NBOKBULBOK_RESERVELIST_DLG] == NULL)
	{
		pClient->CreateInterface( NBOKBULBOK_RESERVELIST_DLG );
	}

	((CBokBulBokEventReserveListDlg*)pClient->m_pDialog[NBOKBULBOK_RESERVELIST_DLG])->SetListData( ppWaitList );
}

void CClient_BBBMgr::StageStart(SI32 siPersonID, SI16 siCurrentStage, DWORD dwStartTime)
{
	cltClient* pClient = (cltClient*)pclClient;

	cltCharClient* pclChar = pclClient->pclCM->GetCharClient( 1 );
	if ( NULL == pclChar )
	{
		return;
	}

	// 5�� ī��Ʈ �κ�.
	m_siCurrentStage = siCurrentStage;
	pclChar->siBBBEvent_5SecCountDown = pClient->CurrentClock;
	pclChar->bBBBEvent_5SecCountDownFlag = true;

	// ����� �������� ���� 5�� ī��Ʈ ���۵ɶ� ���� ����
	pClient->siRoundCount = m_siCurrentStage -1;				// ����°������ �־���.

	m_bStageStartFlag = true;
}

void CClient_BBBMgr::StageFail(SI32 siPersonID, DWORD dwEndTime)
{
	cltClient* pClient = (cltClient*)pclClient;

	cltCharClient* pclChar = pclClient->pclCM->GetCharClient( 1 );
	if ( NULL == pclChar )
	{
		return;
	}

	// Lose
	pclChar->siBBBEvent_TotalStageClearResultImageIndex = 4;

	pclChar->siBBBEvent_StageFailCountDown = pClient->CurrentClock;
	pclChar->bBBBEvent_StageFailFlag = true;


	// ���� ǥ�� ������
	pClient->siRoundCount = -1;

	// �������� ���ѽð��� ������
	pClient->bTimeCount = false;
	pClient->siTimeSet	=	0;								// 30��..�ʴ����� �ֽ��ϴ�~
	pClient->dwWriteSetTime	=	0;	// �ð��� ������ �ð�
}

void CClient_BBBMgr::Pop_WarpMapQuestionDlg()
{
	cltClient* pClient = (cltClient*)pclClient;

	cltCharClient* pclChar = pclClient->pclCM->GetCharClient( 1 );
	if ( NULL == pclChar )
	{
		return;
	}

	// ��� ����µ� ���� ���� �ҷ���? ��� ��ȭ���� ���
	if (pClient->m_pDialog[NCOMMONMSG_DLG] == NULL)
	{
		pClient->CreateInterface( NCOMMONMSG_DLG );
	}

	((CNCommonMsgDlg*)pClient->m_pDialog[NCOMMONMSG_DLG])->Set( COMMONDLG_BBB_WARPMAPQUESTION );
	((CNCommonMsgDlg*)pClient->m_pDialog[NCOMMONMSG_DLG])->SetShowTimeSec(10);	// ��� ���� �ð� 10��.
}

void CClient_BBBMgr::Pop_NotEnoughMoneyDlg()
{
	cltClient* pClient = (cltClient*)pclClient;

	cltCharClient* pclChar = pclClient->pclCM->GetCharClient( 1 );
	if ( NULL == pclChar )
	{
		return;
	}

	// ���� ���� �����ϴٰ� ��ȭ���� ���
	TCHAR*	pTitle	= GetTxtFromMgr(1260); // ������ ����
	TCHAR*	pBody	= GetTxtFromMgr(1261); // �������� Ȯ���� �ֽʽÿ�.
	pClient->m_pDialog[NOTIFYMSG_DLG]->SetText(pTitle, pBody);


	// ���� ���� �����ϴٰ� ��ȭ���� ���
	//if (pClient->m_pDialog[NCOMMONMSG_DLG] == NULL)
	//{
	//	pClient->CreateInterface( NCOMMONMSG_DLG );
	//}

	//((CNCommonMsgDlg*)pClient->m_pDialog[NCOMMONMSG_DLG])->Set( COMMONDLG_BBB_NOTENOUGHMONEY );
	//((CNCommonMsgDlg*)pClient->m_pDialog[NCOMMONMSG_DLG])->SetShowTimeSec(10);	// ��� ���� �ð� 10��.
}

void CClient_BBBMgr::StageClear()
{
	cltClient* pClient = (cltClient*)pclClient;

	cltCharClient* pclChar = pclClient->pclCM->GetCharClient( 1 );
	if ( NULL == pclChar )
	{
		return;
	}

	pclChar->siBBBEvent_StageClearCountDown = pClient->CurrentClock;
	pclChar->bBBBEvent_StageClearFlag = true;

	// ���� ǥ�� ������
	pClient->siRoundCount = -1;

	// �������� ���ѽð��� ������
	pClient->bTimeCount = false;
	pClient->siTimeSet	=	0;		// 30��..�ʴ����� �ֽ��ϴ�~
	pClient->dwWriteSetTime	=	0;	// �ð��� ������ �ð�
}

void CClient_BBBMgr::TotalStageClear()
{
	cltClient* pClient = (cltClient*)pclClient;

	cltCharClient* pclChar = pclClient->pclCM->GetCharClient( 1 );
	if( NULL == pclChar)
	{
		return;
	}

	pclChar->siBBBEvent_TotalStageClearCountDown = pClient->CurrentClock;
	pclChar->bBBBEvent_TotalStageClearFlag = true;

	// ���� ǥ�� ������
	pClient->siRoundCount = -1;

	// �������� ���ѽð��� ������
	pClient->bTimeCount = false;
	pClient->siTimeSet	=	0;		// 30��..�ʴ����� �ֽ��ϴ�~
	pClient->dwWriteSetTime	=	0;	// �ð��� ������ �ð�	
}

void CClient_BBBMgr::_Load_BBBGameInfo()
{
	//////////////////////////////////////////////////////////////////////////
	// ���� �ε�
	NDataLoader	dataloader;
	BOOL bLoadFile=FALSE;

	if( pclClient->IsWhereServiceArea( ConstSwitch_TextEncryption ) )
	{
		bLoadFile = dataloader.LoadDataFromCryptFile( TEXT("Data/BBBEvent/BBBEvent_BBBGameInfo.txt") );
	}
	else
	{
		if ( pclClient->IsWhereServiceArea(ConstServiceArea_China) )
		{
			bLoadFile = dataloader.LoadDataFromCryptFile( TEXT("Data/BBBEvent/BBBEvent_BBBGameInfo.txt"));
		}

		else
		{
			bLoadFile = dataloader.LoadDataFromFile( TEXT("Data/BBBEvent/BBBEvent_BBBGameInfo.txt") );
		}	
	}

	if (!bLoadFile)
	{
		MsgBox( TEXT("Not LoadFromFile BBBEvent_BBBGameInfo.txt"),TEXT("Error"));
		return;
	}

	//////////////////////////////////////////////////////////////////////////
	// �о���� ���� �������� �迭 �ʱ�ȭ
	SI32 siStartDelay = 0;				// �������� ���۽� ī��Ʈ ������ (����� ī��Ʈ ����? ���� 5�ʺ��� ī��Ʈ. 3�ʷ� �ٲٷ��� ���Ͽ��� 3����)
	SI32 siLoseDelay = 0;				// Lose ǥ�� ������
	SI32 siWinDelay = 0;				// Win ǥ�� ������
	SI32 siPlayDelay = 0;				// �������� �÷��� �ð�
	//SI32 siTotalWinDelay = 0;			// ��Ż �������� �Ϸ� �� WIN ������
	SI32 siDropRate = 0;				// �������� ������ ����� Ȯ��	(%)

	NDataTypeInfo pDataTypeInfo[] =
	{
		NDATA_INT32,	&siStartDelay,		4,
			NDATA_INT32,	&siLoseDelay,		4,
			NDATA_INT32,	&siWinDelay,		4,
			NDATA_INT32,	&siPlayDelay,		4,
			NDATA_INT32,	&siDropRate,		4,
			//NDATA_INT32,	&siTotalWinDelay,	4,
			0,				0,					0
	};	
	dataloader.RegDataType( pDataTypeInfo );


	//////////////////////////////////////////////////////////////////////////
	SI32 siArrayindex = 0;
	while( !dataloader.IsEndOfData() )
	{
		if ( dataloader.ReadData(true) )
		{
			if ( siArrayindex >= 1 )	break;

			m_siStageStartDelay = (siStartDelay + 1) * 1000;		// start ǥ�ø� ���� 1�ʸ� �����ش�.
			m_siStageLoseDelay = siLoseDelay * 1000;
			m_siStageWinDelay = siWinDelay * 1000;
			//m_siTotalStageWinDelay = siTotalWinDelay;
			m_siStagePlayDelay = siPlayDelay;				// Ŭ���̾�Ʈ�� 1000�� ������ �ʰ� �׳� �� ������ ��� (15�ʸ� 15)
			//m_siItemDropRate = siDropRate * 100;					// Ŭ���̾�Ʈ�� ������ ������� �ʿ�����Ƿ� �о �׳� ������.

			++siArrayindex;
		}
	}
}

void CClient_BBBMgr::Notice_10ClearNotice(SI32 siRewardMoney, TCHAR* pszWinnerName )
{
	cltClient* pClient = (cltClient*)pclClient;
	cltCharClient* pCharClient = (cltCharClient*)pClient->pclCM->GetCharClient( 1 );
	if ( NULL == pCharClient ) return;

	NTCHARString256 strText = GetTxtFromMgr(40068); //�����մϴ�. #name#���� ���Һ� ���ӿ��� ��� ���������� Ŭ�����Ͽ� #money#����� ����� �޾ҽ��ϴ�.
	NTCHARString256 strMoney;
	g_JYLibFunction.SetNumUnit( siRewardMoney, strMoney, 256 );

	strText.Replace( TEXT("#money#"), strMoney );

	NTCHARString256 strName = pszWinnerName;
	strText.Replace( TEXT("#name#"), strName );

	TCHAR* pszTitle = GetTxtFromMgr(865);

	if( pClient->m_pDialog[NRAREITEM_DLG ] == NULL )
	{
		pClient->CreateInterface( NRAREITEM_DLG );
	}
	((CNRareItemDlg*)pClient->m_pDialog[NRAREITEM_DLG ])->Set( NULL, (TCHAR*)strName, pszTitle, (TCHAR*)strText );
}

void CClient_BBBMgr::Check_AlreadyReserved()
{
	// ��Ŷ ���� 
	cltClient* pClient = (cltClient*)pclClient;
	cltCharClient* pCharClient = pClient->pclCM->GetCharClient( 1 );
	if ( NULL == pCharClient ) return;

	cltGameMsgRequest_BBB_AlreadyReserved clinfo( 1 );
	cltMsg clMsg(GAMEMSG_REQUEST_BBB_ALREADYRESERVED, sizeof(clinfo), (BYTE*)&clinfo);
	pCharClient->SendNetMsg((sPacketHeader*)&clMsg);
}

void CClient_BBBMgr::Receive_AlreadyReserved(TCHAR** ppWaitList, bool bResult, GMONEY siTotalMoney )
{
	// ��Ŷ ���� 
	if ( true == bResult )
	{
		if ( NULL == ppWaitList ) return;
		cltClient* pClient = (cltClient*)pclClient;

		cltCharClient* pclChar = pclClient->pclCM->GetCharClient( 1 );
		if ( NULL == pclChar )
		{
			return;
		}

		// ����� ����Ʈ ��Ȳ�� �����ִ� ��ȭ���ڸ� ���
		if (pClient->m_pDialog[NBOKBULBOK_RESERVELIST_DLG] == NULL)
		{
			pClient->CreateInterface( NBOKBULBOK_RESERVELIST_DLG );
		}

		((CBokBulBokEventReserveListDlg*)pClient->m_pDialog[NBOKBULBOK_RESERVELIST_DLG])->SetListData( ppWaitList );
	}
	else
	{
		cltClient* pClient = (cltClient*)pclClient;

		cltCharClient* pclChar = pclClient->pclCM->GetCharClient( 1 );
		if ( NULL == pclChar )
		{
			return;
		}

		if ( NULL == pClient->m_pDialog[NBOKBULBOK_EVENT_DLG] )
		{
			pClient->CreateInterface( NBOKBULBOK_EVENT_DLG );
		}

		((NBokBulBokEventDlg*)pClient->m_pDialog[NBOKBULBOK_EVENT_DLG])->Show_FirstMessageDlg( siTotalMoney );		
	}
}

void CClient_BBBMgr::_Clear_BBBStatus()
{
	cltClient* pClient = (cltClient*)pclClient;
	cltCharClient* pCharClient = pClient->pclCM->GetCharClient( 1 );
	if ( NULL == pCharClient ) return;

	/*pCharClient->bBBBEvent_5SecCountDownFlag = false;
	pCharClient->siBBBEvent_5SecCountDown = 0;

	pCharClient->bBBBEvent_StageFailFlag = false;
	pCharClient->siBBBEvent_StageFailCountDown = 0;

	pCharClient->bBBBEvent_StageClearFlag = false;
	pCharClient->siBBBEvent_StageClearCountDown = 0;

	pCharClient->bBBBEvent_TotalStageClearFlag = false;
	pCharClient->siBBBEvent_TotalStageClearCountDown = 0;

	m_b3secDelay = false;*/

	m_bStageStartFlag = false;

	// ���� ǥ�� ������
	pClient->siRoundCount = -1;

	// �������� ���ѽð��� ������
	pClient->bTimeCount = false;
	pClient->siTimeSet	=	0;								// 30��..�ʴ����� �ֽ��ϴ�~
	pClient->dwWriteSetTime	=	0;	// �ð��� ������ �ð�
}

void CClient_BBBMgr::DrawWinImage_ForMe()
{
	cltClient* pClient = (cltClient*)pclClient;
	cltCharClient* pCharClient = pClient->pclCM->GetCharClient( 1 );
	if ( NULL == pCharClient ) return;

	pCharClient->siBBBEvent_TotalStageClearResultImageIndex = 0;
	m_b3secDelay = true;
	pCharClient->siBBBEvent_TotalStageClearCountDown = pClient->CurrentClock + 1000;

	// ���� ǥ�� ������
	pClient->siRoundCount = -1;

	// �������� ���ѽð��� ������
	pClient->bTimeCount = false;
	pClient->siTimeSet	=	0;		// 30��..�ʴ����� �ֽ��ϴ�~
	pClient->dwWriteSetTime	=	0;	// �ð��� ������ �ð�
}