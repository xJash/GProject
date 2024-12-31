#include ".\CBattleRoyalMgr.h"
#include "./CMabriumBattleRoyal.h"
#include "./CGrandMabriumBattleRoyal.h"
#include "../common/char/CharServer/Char-Server.h"

CBattleRoyalMgr::CBattleRoyalMgr(SI32 siGameMode)
{
	m_pclMabriumBattleRoyal = NULL;
	m_pclGrandMabriumBattleRoyal = NULL;
	m_siGameMode = siGameMode;
	m_bGMOperation = false;
	m_bNextStep = false;
}

CBattleRoyalMgr::~CBattleRoyalMgr(void)
{
	Destroy();
}
// ��Ʋ �ξ� ����
BOOL	CBattleRoyalMgr::Create()
{
	if( NULL != m_pclMabriumBattleRoyal)
		return FALSE;
	if( NULL != m_pclGrandMabriumBattleRoyal)
		return FALSE;

	m_pclMabriumBattleRoyal = new CMabriumBattleRoyal();
	if( NULL == m_pclMabriumBattleRoyal)
		return FALSE;

	m_pclMabriumBattleRoyal->Create();

	m_pclGrandMabriumBattleRoyal = new CGrandMabriumBattleRoyal();
	if( NULL == m_pclGrandMabriumBattleRoyal)
		return FALSE;

	m_pclGrandMabriumBattleRoyal->Create();

	_SYSTEMTIME st;
	GetLocalTime(&st);

	for(SI32 i = 0 ; i <= DAYTOHOURS; i++)
	{
		if( (st.wHour < i) && ((i % EVENTREFRESHTIME ) == 0))
		{
			m_pclMabriumBattleRoyal->SetNextStartTime(i);
			m_pclGrandMabriumBattleRoyal->SetNextStartTime(i);
			break;
		}
	}

	// �� �ð� 55�п� ����
	//m_clEventWait.AddTime(EVENT_1_OCLOCK | EVENT_3_OCLOCK | EVENT_5_OCLOCK | EVENT_7_OCLOCK |
	//	EVENT_9_OCLOCK | EVENT_11_OCLOCK | EVENT_13_OCLOCK | EVENT_15_OCLOCK | EVENT_17_OCLOCK | EVENT_19_OCLOCK | EVENT_21_OCLOCK | EVENT_23_OCLOCK);
	m_clEventWait.AddTime(EVENT_2_OCLOCK | EVENT_5_OCLOCK | EVENT_8_OCLOCK | EVENT_11_OCLOCK |
		EVENT_14_OCLOCK | EVENT_17_OCLOCK | EVENT_20_OCLOCK | EVENT_23_OCLOCK );

	m_clEventWait.Execute( 55,  NULL);

	return TRUE;
}
// ��Ʋ �ξ� ����
void	CBattleRoyalMgr::Destroy()
{
	if( NULL != m_pclMabriumBattleRoyal)
	{
		delete m_pclMabriumBattleRoyal;
		m_pclMabriumBattleRoyal = NULL;
	}

	if( NULL != m_pclGrandMabriumBattleRoyal)
	{
		delete m_pclGrandMabriumBattleRoyal;
		m_pclGrandMabriumBattleRoyal = NULL;
	}

	return;
}
// ������ ���� ����
BOOL	CBattleRoyalMgr::Action()
{
	if( NULL == m_pclMabriumBattleRoyal)
		return FALSE;
	if( NULL == m_pclGrandMabriumBattleRoyal)
		return FALSE;

	if( TRUE != m_pclMabriumBattleRoyal->IsEndState())
	{
		if( m_bNextStep == true)
		{
			m_clMarbriumChangeStateTimer.Init(0);
			m_clMarbriumChangeStateTimer.SetActive(true , GetTickCount());
		}
	}

	if( TRUE != m_pclGrandMabriumBattleRoyal->IsEndState())
	{
		if( m_bNextStep == true)
		{
			m_clGrandMabriumChangeStateTimer.Init(0);
			m_clGrandMabriumChangeStateTimer.SetActive(true , GetTickCount());
		}
	}


	if( TRUE == m_pclMabriumBattleRoyal->IsGamingState() || TRUE == m_pclMabriumBattleRoyal->IsRewardState()
		|| TRUE == m_pclMabriumBattleRoyal->IsEndState())
	{
		m_pclMabriumBattleRoyal->CheckOutGamer();
		m_pclMabriumBattleRoyal->ActionGameMode();
		if(m_pclMabriumBattleRoyal->IsEarlyEnd() == TRUE)
		{
			m_clMarbriumChangeStateTimer.Init(0);
			m_clMarbriumChangeStateTimer.SetActive(true , GetTickCount());
		}
	}

	if( TRUE == m_pclGrandMabriumBattleRoyal->IsGamingState() || TRUE == m_pclGrandMabriumBattleRoyal->IsRewardState()
		|| TRUE == m_pclGrandMabriumBattleRoyal->IsEndState())
	{
		m_pclGrandMabriumBattleRoyal->CheckOutGamer();
		m_pclGrandMabriumBattleRoyal->ActionGameMode();
		if(m_pclGrandMabriumBattleRoyal->IsEarlyEnd() == TRUE)
		{
			m_clGrandMabriumChangeStateTimer.Init(0);
			m_clGrandMabriumChangeStateTimer.SetActive(true , GetTickCount());
		}
	}

	// ��Ʋ�ξ��� ���۵ȴ� ( ��� => ���� => ���� �� => ���� => ����)
	if( TRUE == m_clEventWait.IsTimed() && false == m_bGMOperation )
	{
		// ��� ����
		m_pclMabriumBattleRoyal->Waiting();
		m_pclGrandMabriumBattleRoyal->Waiting();

		// 4�� �� Ÿ�̸�
		m_clMarbriumChangeStateTimer.Init(WAITTIME);
		m_clMarbriumChangeStateTimer.SetActive( true , GetTickCount());

		// 4�� �� Ÿ�̸�
		m_clGrandMabriumChangeStateTimer.Init(WAITTIME);
		m_clGrandMabriumChangeStateTimer.SetActive( true , GetTickCount());
		m_bNextStep = false;
	}
	
	// ��Ʋ �ξ��� �ܰ� ������ ��ȭ
	if( m_clMarbriumChangeStateTimer.IsTimed( GetTickCount(),false) )
	{
		if( m_pclMabriumBattleRoyal->IsWaiteState())
		{
			// ���� ���� (���� ���ɻ���)
			m_pclMabriumBattleRoyal->SetGameTime(GAMETIME/1000);
			m_pclMabriumBattleRoyal->Starting();

			// 1�� �� Ÿ�̸�
			m_clMarbriumChangeStateTimer.Init(STARTTIME);
			m_clMarbriumChangeStateTimer.SetActive( true , GetTickCount());
		}
		else if(m_pclMabriumBattleRoyal->IsStartState())
		{
			// ���� �� ���� 
			m_pclMabriumBattleRoyal->Gaming();

			_SYSTEMTIME st;
			GetLocalTime(&st);

			for(SI32 i = 0 ; i <= DAYTOHOURS; i++)
			{
				if( (st.wHour < i) && ((i % EVENTREFRESHTIME ) == 0))
				{
					m_pclMabriumBattleRoyal->SetNextStartTime(i);
					break;
				}
			}

			// 10�� �� Ÿ�̸�
			m_clMarbriumChangeStateTimer.Init(GAMETIME);
			m_clMarbriumChangeStateTimer.SetActive( true , GetTickCount());
		}
		else if(m_pclMabriumBattleRoyal->IsGamingState())
		{
			// ���� ���� 
			m_pclMabriumBattleRoyal->Rewarding();

			// 5�� �� Ÿ�̸�
			m_clMarbriumChangeStateTimer.Init(REWARDTIME);
			m_clMarbriumChangeStateTimer.SetActive( true , GetTickCount());
		}
		else if(m_pclMabriumBattleRoyal->IsRewardState())
		{
			// ���� �� ���� 
			m_pclMabriumBattleRoyal->Ending();
		}

	}

	// ��Ʋ �ξ��� �ܰ� ������ ��ȭ
	if( m_clGrandMabriumChangeStateTimer.IsTimed( GetTickCount(),false) )
	{
		if( m_pclGrandMabriumBattleRoyal->IsWaiteState())
		{
			// ���� ���� (���� ���ɻ���)
			m_pclGrandMabriumBattleRoyal->Starting();

			// 1�� �� Ÿ�̸�
			m_clGrandMabriumChangeStateTimer.Init(STARTTIME);
			m_clGrandMabriumChangeStateTimer.SetActive( true , GetTickCount());
		}
		else if(m_pclGrandMabriumBattleRoyal->IsStartState())
		{
			// ���� �� ����
			m_pclGrandMabriumBattleRoyal->SetGameTime(GAMETIME/1000);
			m_pclGrandMabriumBattleRoyal->Gaming();

			_SYSTEMTIME st;
			GetLocalTime(&st);

			for(SI32 i = 0 ; i <= DAYTOHOURS; i++)
			{
				if( (st.wHour < i) && ((i % EVENTREFRESHTIME ) == 0))
				{
					m_pclGrandMabriumBattleRoyal->SetNextStartTime(i);
					break;
				}
			}

			// 10�� �� Ÿ�̸�
			m_clGrandMabriumChangeStateTimer.Init(GAMETIME);
			m_clGrandMabriumChangeStateTimer.SetActive( true , GetTickCount());
		}
		else if(m_pclGrandMabriumBattleRoyal->IsGamingState())
		{
			// ���� ���� 
			m_pclGrandMabriumBattleRoyal->Rewarding();

			// 5�� �� Ÿ�̸�
			m_clGrandMabriumChangeStateTimer.Init(REWARDTIME);
			m_clGrandMabriumChangeStateTimer.SetActive( true , GetTickCount());
		}
		else if(m_pclGrandMabriumBattleRoyal->IsRewardState())
		{
			// ���� �� ���� 
			m_pclGrandMabriumBattleRoyal->Ending();
		}
	}

	if( m_pclGrandMabriumBattleRoyal->IsEndState() && m_pclMabriumBattleRoyal->IsEndState())
	{
		m_bGMOperation = false;
	}

	m_bNextStep = false;

	return TRUE;
}

// GM ��ɾ�� ������ ��Ʋ�ξ� ���� ��Ű��,
BOOL CBattleRoyalMgr::OperatorGMBattleRoyal()
{
	if( NULL == m_pclGrandMabriumBattleRoyal )
		return FALSE;
	if( NULL == m_pclMabriumBattleRoyal )
		return FALSE;

	if( true == m_bGMOperation)
		return FALSE;

	if( m_pclGrandMabriumBattleRoyal->IsEndState() && m_pclMabriumBattleRoyal->IsEndState())
	{
		m_bGMOperation = true;

		// ��� ����
		m_pclMabriumBattleRoyal->Waiting();
		m_pclGrandMabriumBattleRoyal->Waiting();

		// 4�� �� Ÿ�̸�
		m_clMarbriumChangeStateTimer.Init(WAITTIME);
		m_clMarbriumChangeStateTimer.SetActive( true , GetTickCount());

		// 4�� �� Ÿ�̸�
		m_clGrandMabriumChangeStateTimer.Init(WAITTIME);
		m_clGrandMabriumChangeStateTimer.SetActive( true , GetTickCount());

		return TRUE;
	}

	return FALSE;
}

// GM ��ɾ�� ��Ʋ�ξ� ���� ��� ���� �ϱ�
BOOL CBattleRoyalMgr::SetGMGameMode(SI32 siMode)
{
	if( NULL == m_pclMabriumBattleRoyal)
		return NULL;
	if( NULL == m_pclGrandMabriumBattleRoyal)
		return NULL;

	if( TRUE == m_pclMabriumBattleRoyal->SetGMGameMode(siMode) && TRUE == m_pclGrandMabriumBattleRoyal->SetGMGameMode(siMode))
	{
		return TRUE;
	}
	return FALSE;
}

// ĳ���Ϳ� �´� ��Ʋ�ξ� ������ ���
CBattleRoyal*	CBattleRoyalMgr::GetBattleRoyal(cltCharServer* pclChar)
{
	if( NULL == pclChar)
		return NULL;
	if( NULL == m_pclMabriumBattleRoyal)
		return NULL;
	if( NULL == m_pclGrandMabriumBattleRoyal)
		return NULL;
	UI32 uiMinLevel = 0;
	UI32 uiMaxLevel = 0;

	UI32 uiCharLevel = pclChar->pclCI->clIP.GetLevel();

	if( FALSE == m_pclMabriumBattleRoyal->GetCanEnterLevel(&uiMinLevel, &uiMaxLevel) )
		return NULL;

	if( (uiMinLevel <= uiCharLevel) && (uiCharLevel<= uiMaxLevel))
		return m_pclMabriumBattleRoyal;

	if( FALSE == m_pclGrandMabriumBattleRoyal->GetCanEnterLevel(&uiMinLevel, &uiMaxLevel) )
		return NULL;

	if( (uiMinLevel <= uiCharLevel) && (uiCharLevel<= uiMaxLevel))
		return m_pclGrandMabriumBattleRoyal;

	return NULL;
}

void	CBattleRoyalMgr::SetNextStep()
{
	m_bNextStep = true;
}