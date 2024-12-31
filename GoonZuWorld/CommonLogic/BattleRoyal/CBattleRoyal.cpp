#include ".\CBattleRoyal.h"
#include "../../Server/Server.h"

CBattleRoyal::CBattleRoyal(void)
{
	m_pclState = &m_clEndState;
	m_pclGameMode = NULL;
	m_pclReward = NULL;
	m_pclStadium = NULL;
	m_siNextStartTime = 0;
}

CBattleRoyal::~CBattleRoyal(void)
{
	if( NULL != m_pclState )
	{
		m_pclState = NULL;
	}

	if( NULL != m_pclGameMode )
	{
		delete m_pclGameMode;
		m_pclGameMode = NULL;
	}

	if( NULL != m_pclReward )
	{
		delete m_pclReward;
		m_pclReward = NULL;
	}

	if( NULL != m_pclStadium )
	{
		delete m_pclStadium;
		m_pclStadium = NULL;
	}
}
// ��� ���·�
BOOL	CBattleRoyal::Waiting()
{
	m_pclState = &m_clWaitState;
	
	return Action();
}
// ���� ���·�
BOOL	CBattleRoyal::Gaming()
{
	m_pclState = &m_clGameState;
	
	return Action();
}
// ���� ���·�
BOOL	CBattleRoyal::Ending()
{
	m_pclState = &m_clEndState;
	
	return Action();
}
// ���� ���·�
BOOL	CBattleRoyal::Rewarding()
{
	m_pclState = &m_clRewardState;
	
	return Action();
}
// ���� ���·�
BOOL	CBattleRoyal::Starting()
{
	m_pclState = &m_clStartState;
	
	return Action();
}
// ����������
BOOL	CBattleRoyal::IsWaiteState()
{
	if( m_pclState == &m_clWaitState )
		return TRUE;
	return FALSE;
}
// ���ӻ�������
BOOL	CBattleRoyal::IsGamingState()
{
	if( m_pclState == &m_clGameState )
		return TRUE;
	return FALSE;
}
// �����������
BOOL	CBattleRoyal::IsEndState()
{
	if( m_pclState == &m_clEndState )
		return TRUE;
	return FALSE;
}
// �����������
BOOL	CBattleRoyal::IsRewardState()
{
	if( m_pclState == &m_clRewardState )
		return TRUE;
	return FALSE;
}
// ���ۻ�������
BOOL	CBattleRoyal::IsStartState()
{
	if( m_pclState == &m_clStartState )
		return TRUE;
	return FALSE;
}



// �ൿ
BOOL	CBattleRoyal::Action()
{
	if( NULL == m_pclState)
		return FALSE;
	if( NULL == m_pclGameMode)
		return FALSE;
	if( NULL == m_pclReward)
		return FALSE;
	if( NULL == m_pclStadium)
		return FALSE;

	BOOL bValue = m_pclState->Handle();
	return bValue;
}

void	CBattleRoyal::InitState()	// ���� ��ü �ʱ�ȭ
{
	m_clWaitState.Init(m_pclGameMode, m_pclReward, m_pclStadium);
	m_clGameState.Init(m_pclGameMode, m_pclReward, m_pclStadium);
	m_clEndState.Init(m_pclGameMode, m_pclReward, m_pclStadium);
	m_clRewardState.Init(m_pclGameMode, m_pclReward, m_pclStadium);
	m_clStartState.Init(m_pclGameMode, m_pclReward, m_pclStadium);
}
// ���� ���� ����
BOOL	CBattleRoyal::GetCanEnterLevel(UI32* uiMinLevel, UI32* uiMaxLevel)
{
	if( NULL == uiMinLevel)
		return FALSE;
	if( NULL == uiMaxLevel)
		return FALSE;
	if( NULL == m_pclStadium)
		return FALSE;

	*uiMinLevel = m_pclStadium->GetCanEnterMinLevel();
	*uiMaxLevel = m_pclStadium->GetCanEnterMaxLevel();

	return TRUE;
}
// ���� ��������  
BOOL	CBattleRoyal::CanEnter(cltCharServer* pclChar)
{
	if( NULL == pclChar)
		return FALSE;
	if( NULL == m_pclGameMode)
		return FALSE;
	if( NULL == m_pclReward)
		return FALSE;
	if( NULL == m_pclStadium)
		return FALSE;

	SI32 siPersonID = pclChar->pclCI->GetPersonID();

	//1. ����� ���� ������ ��
	if (FALSE == m_pclStadium->IsOpenedGate())
		return BATTLEROYAL_ENTERERROR_ISOPENED;
	//2. �� ��⿡ ���� ����
	if (TRUE == m_pclStadium->WasJoinedLastGame(siPersonID))
		return BATTLEROYAL_ENTERERROR_WASJOINED;
	//3. ���� �� �� ��� ���� �Ұ�
	if ( pclChar->siPersonalMakeItemType > 0)
		return BATTLERPYAL_ENTERERROR_ISMAKING;
	//4. ��ȯ�� ��ȯ ����
	if ( pclChar->siChildCharUnique > 0)
		return BATTLERPYAL_ENTERERROR_TAKEDOUTSUMMON;
	//5. ��ȣ���� ��ȯ ����
	if ( pclChar->siMySoulGuardUnique > 0)
		return BATTLERPYAL_ENTERERROR_TAKEDOUTSUMMON;
	//6. ������ ���� �Ѱ�ġ ����?
	if ( m_pclStadium->GetWaitGamerNum() >= CBattleRoyalStadiumServer::MAX_GAMER_COUNT)
		return BATTLERPYAL_ENTERERROR_FULLEDGAMER;
	//7. ��Ƽ ������
	if ( pclChar->siPartyIndex > 0 )
	{
		return BATTLERPYAL_ENTERERROR_JOINPARTY;
	}
	// ���� �� �� �ִٸ�

	//1. ĳ���͸� ���̵� ���� �ٲ۴�.
	m_pclGameMode->ChangeInvisibleMode(pclChar);

	return TRUE;
}

// ����� ������ �̵�
void	CBattleRoyal::WarpFrontOfStadium(cltCharServer* pclChar)
{
	if( NULL == pclChar)
		return;

	// ���� ������ ��
	SI32	siWarpX = 503;
	SI32	siWarpY = 257;

	cltWarpInfo clWarpPollMap(1, MAPINDEX_MAINFIELD, true, false, siWarpX, siWarpY, -1, -1);

	pclChar->SetWarpInfo( &clWarpPollMap, 905 );
	pclChar->Warp();
}

// ��Ʋ�ξ� �߿� ������ ���� ������� �������� �ش�.(100% Ȯ�� �ƴ�)
BOOL	CBattleRoyal::GiveItemToKiller(cltCharServer* pclChar)
{
	if( NULL == m_pclReward)
		return FALSE;

	if( NULL == pclChar)
		return FALSE;

	if( FALSE == m_pclReward->GiveRewardToKillingUser(pclChar))
		return FALSE;

	return TRUE;
}

// �� �ε���
SI32	CBattleRoyal::GetStadiumMapIndex()
{
	if( NULL == m_pclStadium)
		return FALSE;

	return m_pclStadium->GetMapIndex();
}
// ������� �������� ���������� üũ
BOOL	CBattleRoyal::CheckOutGamer()
{
	if( NULL == m_pclStadium)
		return FALSE;
	if( NULL == m_pclGameMode)
		return FALSE;

	cltCharServer* pclChar = NULL;
	for(SI32 i = 0 ; i < CBattleRoyalStadiumServer::MAX_GAMER_COUNT; i++)
	{
		m_pclStadium->ProcessLogoutCharByIndex(i);
		pclChar = m_pclStadium->GetGamingCharByIndex(i);
		if( NULL == pclChar)
			continue;

		if(m_pclStadium->GetMapIndex() != pclChar->GetMapIndex())
		{
			RestorChar(pclChar);

			//pclChar->SetUpdateSwitch(UPDATE_BASICINFO, true, 0 );
			cltMsg clMassage(GAMEMSG_RESPONSE_BATTLEROYAL_ENDGAME, 0, NULL );
			pclChar->SendNetMsg((sPacketHeader*)&clMassage);
			m_pclStadium->DeleteGamer(pclChar->pclCI->GetPersonID());
		}

		if( pclChar->siKilledMode == KILLEDMODE_BATTLEROYAL && pclChar->siCharMode == CHARMODE_BATTLEROYAL)
		{
			RestorChar(pclChar);

			//pclChar->SetUpdateSwitch(UPDATE_BASICINFO, true, 0 );
			cltMsg clMassage(GAMEMSG_RESPONSE_BATTLEROYAL_ENDGAME, 0, NULL );
			pclChar->SendNetMsg((sPacketHeader*)&clMassage);
		}

	}

	return TRUE;
}
// ���� ���� Ȯ��
BOOL	CBattleRoyal::IsEarlyEnd()
{
	if( NULL == m_pclStadium)
		return FALSE;

	if( m_pclStadium->GetGamingGamerNum() > 1)
	{
		return FALSE;
	}
	
	if( m_pclStadium->GetGamingGamerNum() == 1)
	{
		if( m_pclStadium->GetMobNum() <= 0)
			return TRUE;
		return FALSE;
	}

	return TRUE;
}

BOOL	CBattleRoyal::DieMob()
{	
	if( NULL == m_pclStadium)
		return FALSE;

	m_pclStadium->DieMob();
	return TRUE;
}

void	CBattleRoyal::SetNextStartTime(SI32 siNextStartTime)
{
	m_siNextStartTime = siNextStartTime;
}
SI32	CBattleRoyal::GetNextStartRemainedTime()
{
	_SYSTEMTIME st;
	GetLocalTime(&st);

	const SI32 HOURTOMINUTE = 60;

	SI32 siEndMinute = m_siNextStartTime * HOURTOMINUTE;
	SI32 siStartMinute = (st.wHour * HOURTOMINUTE) + st.wMinute;

	return siEndMinute - siStartMinute;
}
// ������������ ��� �� �� �ִ� ��
BOOL	CBattleRoyal::CanUseHealItem()
{
	if( NULL == m_pclGameMode)
		return TRUE;

	if(m_pclGameMode->GetMode() == BATTLEROYALGAMEMODE_RESTRICTTOUSEHEALITEM)
		return FALSE;

	return TRUE;
}
// ���� �÷��� �ð� ����
BOOL	CBattleRoyal::SetGameTime(SI32 siTime)
{
	if( NULL == m_pclGameMode)
		return FALSE;

	m_pclGameMode->SetGameTime(siTime);

	return TRUE;
}
BOOL	CBattleRoyal::IsExistStadium(cltCharServer* pclChar)
{
	if( NULL == pclChar)
		return FALSE;

	if( pclChar->GetMapIndex() == m_pclStadium->GetMapIndex())
	{
		return TRUE;
	}

	return FALSE;
}
BOOL	CBattleRoyal::ActionGameMode()
{
	if( NULL == m_pclGameMode)
		return FALSE;

	if( BATTLEROYALGAMEMODE_POWERUPONEUSER == m_pclGameMode->GetMode())
	{
		m_pclGameMode->PowerupOneUser();	
	}

	return TRUE;
}

BOOL	CBattleRoyal::SetGMGameMode(SI32 siMode)
{
	if( NULL == m_pclGameMode)
		return FALSE;
		
	return m_pclGameMode->SetGMGameMode(siMode);
}

// ����忡 �� �� ������ ���� �ִٸ� ������ �� �ֱ�
BOOL	CBattleRoyal::TakeinHorse(cltCharServer* pclChar)
{
	if ( NULL == pclChar)
		return FALSE;
	if( NULL == m_pclGameMode)
		return FALSE;

	m_pclGameMode->TakeinHorse(pclChar);

	return TRUE;
}
// ����忡 ���ͼ� ���� ���� ������ �����·� ������.
BOOL	CBattleRoyal::RestorChar(cltCharServer* pclChar)
{
	if ( NULL == pclChar)
		return FALSE;
	if( NULL == m_pclGameMode)
		return FALSE;

	m_pclGameMode->RestoreCharInfo(pclChar);
	m_pclGameMode->RestoreTrancsformChar(pclChar);

	return TRUE;
}
// ������ ������ ���� ��Ų��.
BOOL	CBattleRoyal::TransformChar(cltCharServer* pclChar)
{
	if( NULL == pclChar)
		return FALSE;
	if( NULL == m_pclGameMode)
		return FALSE;
	
	if( FALSE ==  m_pclGameMode->TransformChar(pclChar))
		return FALSE;
	
	return TRUE;
}