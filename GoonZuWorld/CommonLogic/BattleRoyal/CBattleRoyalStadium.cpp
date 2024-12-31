#include "./CBattleRoyalStadium.h"
#include "../MsgType.h"
#include "../../Server/Server.h"
#include "../../Client/Client.h"
#include "../common/Char/CharManager/CharManager.h"
#include "../msg/MsgType-BattleRoyal.h"

CBattleRoyalStadium::CBattleRoyalStadium()
{
	m_pclCommon = pclClient;

	// ������� ���� ���� �ִ���?
	m_bOpenGame = false;

	m_siMobCount = 0;
	m_pclWinner = NULL;
	m_siKindBlackarmySword = 0;
	m_siKindBlackarmyRifle = 0;
	m_siKindBlackarmyKatar = 0;
}

CBattleRoyalStadium::~CBattleRoyalStadium()
{

}

BOOL	CBattleRoyalStadium::Init()
{
	if( NULL == m_pclCommon)
		return FALSE;

	// ������� ���� �ִ� �ּ� ���� ����
	m_uiCanEnterMinLevel = m_pclCommon->pclMapManager->GetMinLevel(m_siMapIndex);
	m_uiCanEnterMaxLevel = m_pclCommon->pclMapManager->GetMaxLevel(m_siMapIndex);
	
	return TRUE;
}

// ����� �Ա��� ����.
void	CBattleRoyalStadium::OpenGate()
{
	// ������� ���� ���� �ִ���?
	m_bOpenGame = true;
}
// ����� �Ա��� �ݴ´�.
void	CBattleRoyalStadium::CloseGate()
{
	// ������� ���� ���� �ִ���?
	m_bOpenGame = false;
}

// ������ ����
BOOL	CBattleRoyalStadium::DeleteGamer(SI32 siPersonID)
{	return TRUE;
}




// ���� ���� �ּ� ����
UI32	CBattleRoyalStadium::GetCanEnterMinLevel()
{
	return m_uiCanEnterMinLevel;
}
// ���� ���� �ִ� ����
UI32	CBattleRoyalStadium::GetCanEnterMaxLevel()
{
	return m_uiCanEnterMaxLevel;
}
// ����� �Ա��� ���� �ִ���?
BOOL	CBattleRoyalStadium::IsOpenedGate()
{
	return m_bOpenGame;
}

SI32	CBattleRoyalStadium::GetMapIndex()
{
	return m_siMapIndex;
}

cltCharCommon* CBattleRoyalStadium::GetWinner()
{
	return m_pclWinner;
}

//====================================================================================================================================
CBattleRoyalStadiumServer::CBattleRoyalStadiumServer()
{
	m_pclServer = (cltServer*)pclClient;
	m_siGamerCount = 0;
	m_siBeforeGamerCount = 0;
	m_siGamingUserCount = 0;

}

CBattleRoyalStadiumServer::~CBattleRoyalStadiumServer()
{

}


BOOL	CBattleRoyalStadiumServer::Init()
{
	if( NULL == m_pclCommon)
		return FALSE;

	// ������� ���� �ִ� �ּ� ���� ����
	m_uiCanEnterMinLevel = m_pclCommon->pclMapManager->GetMinLevel(m_siMapIndex);
	m_uiCanEnterMaxLevel = m_pclCommon->pclMapManager->GetMaxLevel(m_siMapIndex);

	m_MobCharIDArray.Resize(MAX_UNIT_COUNT,MAX_UNIT_COUNT);
	m_BeforeGamerArray.Resize(MAX_GAMER_COUNT,MAX_GAMER_COUNT);
	m_GamerArray.Resize(MAX_GAMER_COUNT,MAX_GAMER_COUNT);

	return TRUE;
}

// ������� ������ �˸���.
BOOL	CBattleRoyalStadiumServer::Notice(TCHAR* pszContentText)
{
	if( NULL ==  pszContentText )
		return FALSE;

	TCHAR* pszTitleText = GetTxtFromMgr(5482); 
	if( NULL ==  pszTitleText )
		return FALSE;

	cltGameMsgResponse_Notice clNotice(pszTitleText, pszContentText,true);
	cltMsg clMsg(	GAMEMSG_RESPONSE_NOTICE, clNotice.siDataSize, (BYTE*)&clNotice);

	m_pclServer->pclCM->SendAllPersonMsg((sPacketHeader*)&clMsg);	

	return TRUE;
}

// ��⿡ ������ ����Ʈ�� �����Ѵ�.
BOOL	CBattleRoyalStadiumServer::SaveGamerList()
{
	// 1. �� ���� ��� �ʱ�ȭ
	m_BeforeGamerArray.ClearData();
	// 2. ���۵� ��Ʋ�ξ⿡ ������ ���� ��� ����
	cltCharServer* pclCharServer = NULL;

	for (SI32 siID = 0; siID < MAX_PERSON_NUMBER; siID++)
	{
		if( m_siGamerCount >= MAX_GAMER_COUNT)
			break;

		pclCharServer = m_pclServer->pclCM->GetCharServer(siID);
		if( NULL == pclCharServer)
			continue;

		if(m_siMapIndex == pclCharServer->pclCI->clBI.GetMapIndex())
		{
			CBattleRoyalPersonChangedData& pclGamer = m_GamerArray.GetData(m_siGamerCount);

			pclGamer.SetPersonID( pclCharServer->pclCI->GetPersonID()) ;
			++m_siGamerCount;
		}
	}
	
	// 3. ���� ��Ʋ�ξ⿡�� ���۵� ��Ʋ�ξ⿡ ������ ������ �ź� �ϱ� ���� �뵵�� ��� ����

	// ��Ʋ �ξ⿡ ������ ���� ��� ����
	m_siBeforeGamerCount = m_siGamerCount;
	m_siGamingUserCount =  m_siGamerCount;

	for( SI32 i = 0 ; i < m_siBeforeGamerCount; i++)
	{
		CBattleRoyalPersonChangedData& pclGamer =  m_GamerArray.GetData(i);
		m_BeforeGamerArray[i] = pclGamer.GetPersonID();

		pclCharServer = m_pclServer->pclCM->GetCharServer(i);
	}

	// �α� -  ����, ĳ���� ��, ���� 
	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		m_pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_BATTLEROYAL, LOGCOMMAND_INDEX_BATTLEROYAL_GAMERCOUNT,
			0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
			0, m_siGamerCount, 0, 0, 0, 0, NULL, NULL);
	}

	return TRUE;
}

// ������ ����
BOOL	CBattleRoyalStadiumServer::DeleteGamer(SI32 siPersonID)
{
	if(m_siGamerCount <= 0)
		return FALSE;
	
	for(SI32 i = 0; i < MAX_GAMER_COUNT; i++)
	{
		CBattleRoyalPersonChangedData& pclGamer =  m_GamerArray.GetData(i);

		if( pclGamer.GetPersonID() == siPersonID)
		{
			pclGamer.SetPersonID(0);
			--m_siGamingUserCount;
			return TRUE;
		}
	}
	
	return FALSE;
}
// ���� �����Ѵ�.
BOOL	CBattleRoyalStadiumServer::RemoveMob()
{
	if( NULL == m_pclServer)
		return FALSE;


	cltCharServer * pclChar = NULL;
	for(SI32 i = 0; i < MAX_UNIT_COUNT; i++)
	{
		pclChar =m_pclServer->pclCM->GetCharServer(m_MobCharIDArray.GetData(i));

		if(NULL == pclChar)
			continue;
	
		pclChar->SetLife(0);
	}

	return TRUE;
}

// ���� �����Ѵ�.
BOOL	CBattleRoyalStadiumServer::CreateMob()
{
	if( NULL == m_pclServer)
		return FALSE;

	const SI32 MOBNUMCUTLINE = 15;
	const SI32 POS_BASIC_X = 6;
	const SI32 POS_BASIC_Y = 6;
	const SI32 POS_EXTENSION_LEFT_X = 10;
	const SI32 POS_EXTENSION_LEFT_Y = 26;
	const SI32 POS_EXTENSION_RIGHT_X = 26;
	const SI32 POS_EXTENSION_RIGHT_Y = 10;
	const SI32 POS_BASIC_WIDTH = 20;
	const SI32 POS_BASIC_HEIGHT = 20;
	const SI32 POS_EXTENSION_LEFT_WIDTH = 15;
	const SI32 POS_EXTENSION_LEFT_HEIGHT = 5;
	const SI32 POS_EXTENSION_RIGHT_WIDTH = 5;
	const SI32 POS_EXTENSION_RIGHT_HEIGHT = 16;

	const SI32 ROOMCOUNT = 1;
	const SI32 MOBKINDCOUNT = 3;

	const SI32 NOTEXISTPOSCOUNT = 30;
	
	// ������ �� ����
	m_MobCharIDArray.ClearData();
	SI32 siX		=	0;		// X��ǥ
	SI32 siY		=	0;		// Y��ǥ
	SI32 siMakeCount=	0;		// ���� ���� ����
	SI32 siEnergy	=	10000;
	SI32 siLevel	=	10;
	SI32 siMobCountInRoom = 0;	// �븶�� ���Ե� ���� ��

	SI32 siBasicPosX = 0;
	SI32 siBasicPosY = 0;
	SI32 siMobKind = 0;
	SI32 siMobNumInExtensionRoom = 1;
	m_siMobCount = MAX_UNIT_COUNT - m_siGamerCount;

	if( m_siMobCount > MOBNUMCUTLINE)
	{
		siMobNumInExtensionRoom = 2;
	}

	SI32 siNoExistArrayIndex = 0;
	cltPos clNoExistPos[NOTEXISTPOSCOUNT];
	clNoExistPos[siNoExistArrayIndex++].Set(12,18);
	clNoExistPos[siNoExistArrayIndex++].Set(12,19);
	clNoExistPos[siNoExistArrayIndex++].Set(12,20);
	clNoExistPos[siNoExistArrayIndex++].Set(13,19);
    clNoExistPos[siNoExistArrayIndex++].Set(6,6);
	clNoExistPos[siNoExistArrayIndex++].Set(6,7);
	clNoExistPos[siNoExistArrayIndex++].Set(6,8);
	clNoExistPos[siNoExistArrayIndex++].Set(7,6);
	clNoExistPos[siNoExistArrayIndex++].Set(8,6);

	cltInnerStatusInfo clinnerstatus;
	clinnerstatus.clEnemyType.Set(  ENEMYTYPE_ALLPC, 0);
	cltIdentity clIdentity;
	clIdentity.MakeBattleRoyalMob( IDENTITY_BATTLEROYAL_MONSTER );

	srand( (unsigned)time( NULL ) );

	SI32 siDiv = 0;
	SI32 siMobID = 0;
	SI32 siTmpX = 0;
	SI32 siTmpY = 0;
	SI32 siHeightRange = 0;
	bool bRelocation = false;
	for (siMakeCount; siMakeCount < m_siMobCount; siMakeCount++ )
	{
		siTmpX = 0;
		siTmpY = 0;
		siHeightRange = 0;
		siMobID = 0;
		bRelocation = false;

		if( siMobNumInExtensionRoom > siMakeCount)
		{
			siTmpX = rand() % POS_EXTENSION_LEFT_WIDTH;
			siX = siTmpX + POS_EXTENSION_LEFT_X;

			siTmpY = rand() % POS_EXTENSION_LEFT_HEIGHT;
			siY = siTmpY + POS_EXTENSION_LEFT_Y;
		}
		else if ( siMobNumInExtensionRoom * 2 > siMakeCount && siMakeCount >= siMobNumInExtensionRoom)
		{
			siTmpX = rand() % POS_EXTENSION_RIGHT_WIDTH;
			siX = siTmpX + POS_EXTENSION_RIGHT_X;

			siTmpY = rand() % POS_EXTENSION_RIGHT_HEIGHT;
			siY = siTmpY + POS_EXTENSION_RIGHT_Y;
		}
		else
		{
			siTmpX = rand() % POS_BASIC_WIDTH;
			siX = siTmpX + POS_BASIC_X;

			siTmpY = rand() % POS_BASIC_HEIGHT;
			siY = siTmpY + POS_BASIC_Y;

			for (SI32 i = 0 ; i < NOTEXISTPOSCOUNT ; i++)
			{
				if( clNoExistPos[i].siX == 0)
					break;

				if ( clNoExistPos[i].siX == siTmpX && clNoExistPos[i].siY == siTmpY)
				{
					bRelocation = true;
				}
			}

			if ( true == bRelocation ) 
			{
				--siMakeCount;
				continue;
			}
			
			if ( siNoExistArrayIndex < NOTEXISTPOSCOUNT)
				clNoExistPos[siNoExistArrayIndex++].Set(siTmpX,siTmpY);
		}

		// ���� ����
		if( m_uiCanEnterMaxLevel >= m_uiCanEnterMinLevel)
			siLevel = (rand() % ( m_uiCanEnterMaxLevel -  m_uiCanEnterMinLevel)) + m_uiCanEnterMinLevel;
		else
			siLevel = m_uiCanEnterMinLevel;

		// �� ���� ����
		switch(rand() %MOBKINDCOUNT)
		{
		case 0:
			{	
				siMobKind = m_siKindBlackarmySword;
				break;
			}
		case 1:
			{
				siMobKind = m_siKindBlackarmyRifle;
				break;
			}
		case 2:
			{
				siMobKind = m_siKindBlackarmyKatar;
				break;
			}
		default:
			{
				siMobKind = m_siKindBlackarmySword;
				break;
			}
		}

		cltMapCommon* pclMap = m_pclServer->pclMapManager->GetMapPointer( m_siMapIndex )	;	// ��������
		if(pclMap != NULL)
		{
			// ������ �� ���� �Է�
			// �� ���� ����
			siMobID = m_pclServer->SetNPCChar( siMobKind, 
				VILLAGE_NONE, 
				&clIdentity, 
				siLevel, 
				0, 
				siX, 
				siY, 
				m_siMapIndex, 
				NPCITEMMODE_NONE, 
				&clinnerstatus );
			m_MobCharIDArray[siMakeCount] = siMobID;
		}
	}
	return TRUE;
}

// ����� �˸���.
BOOL	CBattleRoyalStadiumServer::NoticeResult()
{
	bool bresult = false;
	const TCHAR* pszCharName = NULL;

	if( NULL != m_pclWinner)
	{	
		bresult = true;
		pszCharName = m_pclWinner->GetName();
	}
	
	cltGameMsgResponse_BattleRoyalNoticeResult clNotice(pszCharName, bresult, m_siMapIndex);
	
	cltMsg clMassage(GAMEMSG_RESPONSE_BATTLEROYAL_NOTICERESULT, sizeof( clNotice ), (BYTE*)&clNotice );
	m_pclServer->pclCM->SendAllPersonMsg((sPacketHeader*)&clMassage);
	
	return TRUE;
}

// �����ڸ� ����忡�� �����Ų��.
BOOL	CBattleRoyalStadiumServer::BanGamer()
{
	// ����忡 �ִ� ����ڸ� ���縮���� ���� ��Ų��.
	cltCharServer* pclCharServer = NULL;
	for (SI32 id = 0; id < MAX_PERSON_NUMBER; id++)
	{
		pclCharServer = pclClient->pclCM->GetCharServer(id);
		if( NULL == pclCharServer)
			continue;

		if(  m_siMapIndex == pclCharServer->GetMapIndex() && pclCharServer->siKilledMode != KILLEDMODE_BATTLEROYAL)
		{
			SI32		siWarpX = 502;
			SI32		siWarpY = 258;
			cltWarpInfo clWarp(1, MAPINDEX_MAINFIELD, false, false, siWarpX, siWarpY, -1, -1);

			pclCharServer->SetWarpInfo( &clWarp, 1024 );
			pclCharServer->Warp();
		}
	}
	return TRUE;
}

// ��⿡ �������� ���� ���� �����ش�.
UI32	CBattleRoyalStadiumServer::GetWaitGamerNum()
{
	cltCharServer* pclCharServer = NULL;
	UI32	uiCount = 0;
	for (SI32 siID = 0; siID < MAX_PERSON_NUMBER; siID++)
	{
		pclCharServer = m_pclServer->pclCM->GetCharServer(siID);
		if( NULL == pclCharServer)
			continue;

		if(m_siMapIndex == pclCharServer->pclCI->clBI.GetMapIndex())
		{
			++uiCount;
		}
	}

	return uiCount;
}

// ������ ��⿡ ���� �߾�����?
BOOL	CBattleRoyalStadiumServer::WasJoinedLastGame(SI32 siPersonID)
{
	for(SI32 i = 0 ; i < MAX_GAMER_COUNT; i++)
	{
		if( siPersonID == m_BeforeGamerArray.GetData(i))
		{
			return TRUE;
		}
	}
	return FALSE;
}
// ������ ���� �Ѱ�ġ�ΰ�?
BOOL	CBattleRoyalStadiumServer::IsLimitedGamerNum()
{
	if( GetGamerNum() >= MAX_GAMER_COUNT)
	{
		return TRUE;
	}

	return FALSE;
}
// ��⿡ ������ ���� ��
UI32	CBattleRoyalStadiumServer::GetGamerNum()
{
	return m_siGamerCount;
}
// ��⿡ ������ ���� ���� ��
UI32	CBattleRoyalStadiumServer::GetGamingGamerNum()
{
	return m_siGamingUserCount;
}
NkVector<CBattleRoyalPersonChangedData>& CBattleRoyalStadiumServer::GetPersonChangedData()
{
	return m_GamerArray;
}
NkVector<SI32>& CBattleRoyalStadiumServer::GetMobData()
{
	return m_MobCharIDArray;
}

// ������ �ʱ�ȭ
void	CBattleRoyalStadiumServer::InitData()
{
	m_GamerArray.ClearData();
	m_MobCharIDArray.ClearData();
	m_siGamerCount = 0;
	m_siGamingUserCount = 0;
	m_pclWinner = NULL;
	m_siMobCount = 0;
}

void	CBattleRoyalStadiumServer::ProcessLogoutCharByIndex(SI32 siIndex)
{
	if( (siIndex < 0) || (MAX_GAMER_COUNT <= siIndex))
		return ;
	if( NULL == m_pclServer)
		return ;

	CBattleRoyalPersonChangedData& pclPersonData =  m_GamerArray.GetData(siIndex);

	if( pclPersonData.GetPersonID() <= 0)
		return;

	SI32 siCharID =  m_pclServer->pclCM->GetIDFromPersonID(pclPersonData.GetPersonID());
	cltCharServer* pclChar = m_pclServer->pclCM->GetCharServer(siCharID) ;

	if( NULL == pclChar)
	{
		DeleteGamer(pclPersonData.GetPersonID());
	}
	else
	{
		if( pclChar->pclCI->GetPersonID() != pclPersonData.GetPersonID())
		{
			DeleteGamer(pclPersonData.GetPersonID());
		}
	}
}

cltCharServer*	CBattleRoyalStadiumServer::GetGamingCharByIndex(SI32 siIndex)
{
	if( (siIndex < 0) || (MAX_GAMER_COUNT <= siIndex))
		return NULL;
	if( NULL == m_pclServer)
		return NULL;

	CBattleRoyalPersonChangedData& pclPersonData = m_GamerArray.GetData(siIndex);
	
	SI32 siCharID =  m_pclServer->pclCM->GetIDFromPersonID(pclPersonData.GetPersonID());
	return m_pclServer->pclCM->GetCharServer(siCharID);
}

// ����� ó���Ѵ�. (����� �ִ� ��� TRUE ó�� ������ ��� FALSE�� ��ȯ�Ѵ�.)
BOOL	CBattleRoyalStadiumServer::ProcessResult()
{
	m_pclWinner = NULL;

	SI32 siRemainedCharCount = 0 ;

	if( m_siGamingUserCount >= 1)
	{
		cltCharServer* pclChar = NULL;
		SI32 siCharID = 0;
		
		for(SI32 i = 0 ; i < MAX_GAMER_COUNT; i++)
		{
			CBattleRoyalPersonChangedData& pclPersonData =  m_GamerArray.GetData(i);
			
			siCharID =  m_pclServer->pclCM->GetIDFromPersonID(pclPersonData.GetPersonID());
			pclChar = m_pclServer->pclCM->GetCharServer(siCharID);
			if(NULL == pclChar)
				continue;

			if((pclChar->GetMapIndex() == m_siMapIndex) && pclChar->siKilledMode != KILLEDMODE_BATTLEROYAL)
			{
				m_pclWinner = pclChar;
				++siRemainedCharCount;
			}
		}
	}
	
	if( siRemainedCharCount > 1)
		m_pclWinner = NULL;


	if( (m_siMobCount > 0) )
		m_pclWinner = NULL;

	return TRUE;
}
// ��⿡ �����ϴ� ���� ��
UI32	CBattleRoyalStadiumServer::GetMobNum()
{
	return m_siMobCount;
}
// �� ����
void	CBattleRoyalStadiumServer::DieMob()
{
	--m_siMobCount;
}

//====================================================================================================================================
CBattleRoyalStadiumClient::CBattleRoyalStadiumClient()
{
	m_pclClient = (cltClient*)pclClient;
}

CBattleRoyalStadiumClient::~CBattleRoyalStadiumClient()
{

}

// ������ ����
BOOL	CBattleRoyalStadiumClient::DeleteGamer(SI32 siPersonID)
{
	return TRUE;
}
// ����� �˸���.
BOOL	CBattleRoyalStadiumClient::NoticeResult()
{
	

	return TRUE;
}
