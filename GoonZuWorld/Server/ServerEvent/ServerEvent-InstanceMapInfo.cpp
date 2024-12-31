#include <CommonLogic.h>

#include "ServerEvent-InstanceMapInfo.h"

#include "../CommonLogic/MsgType-System.h"
#include "../CommonLogic/MsgRval-Define.h"
#include "../common/CommonHeader.h"
#include "../common/Char/CharManager/CharManager.h"
#include "../common/Map/MapManager/MapManager.h"

CNInstanceMapInfo::CNInstanceMapInfo()									
{
	ZeroMemory(this, sizeof(*this));
}

CNInstanceMapInfo::~CNInstanceMapInfo()								
{

}

void CNInstanceMapInfo::Clear(void)
{
	SI32 siGateID =	m_siGateID;

	ZeroMemory(this, sizeof(*this));

	m_siGateID = siGateID;
}

void CNInstanceMapInfo::DeleteGate(void)
{
	cltServer* pclserver = (cltServer*)pclClient;
	if( NULL == pclserver )	return;
	
	// �ش� ���̵��� �ɸ��Ͱ� ���ٸ� ����
	cltCharServer* pclGateChar = pclClient->pclCM->GetCharServer( m_siGateID );
	if ( pclGateChar == NULL )	return;

	// �ش� ���̵��� �ɸ��͸� �޾ƿ����� ����Ʈ�� �ƴ϶�� ����
	if ( pclGateChar->GetKind() != pclClient->GetUniqueFromHash("KIND_SERVERGATE") )	return;

	// �ش� ����Ʈ�� �����ϰ�
	pclGateChar->DeleteInCell();

	// ������ �Ϸ�Ǿ����� ����Ʈ ���̵� �ٽ� �ʱ�ȭ��Ŵ
	if( TRUE == pclserver->pclCM->DeleteChar(m_siGateID) )
	{
		m_siGateID = 0;
	}
}

void CNInstanceMapInfo::SetScore(SI64 _siScore)
{
	m_siScore = _siScore;
}

SI64 CNInstanceMapInfo::GetScore(void)
{
	return m_siScore;
}

void CNInstanceMapInfo::AddScore(SI64 _siAddScore)
{
	m_siScore += _siAddScore;
}

void CNInstanceMapInfo::SetMapClear(SI16 _Index, bool _bMapClear)
{
	if(false == SAFE_ARRAY_CHECK(_Index, m_bMapClear))
		return;

	m_bMapClear[_Index] = _bMapClear;
}
bool CNInstanceMapInfo::GetMapClear(SI16 _Index)
{
	if(false == SAFE_ARRAY_CHECK(_Index, m_bMapClear))
		return false;

	return m_bMapClear[_Index];
}
bool CNInstanceMapInfo::IsAllMapClear(void)
{
	if( true == m_bMapClear[0] &&
		true == m_bMapClear[1] &&
		true == m_bMapClear[2] &&
		true == m_bMapClear[3]	)
		return true;

	return false;
}


void CNInstanceMapInfo::SetMapStepCount(SI16 _Index, SI16 _siMapStepCount)
{
	if(false == SAFE_ARRAY_CHECK(_Index, m_siMapStepCount))
		return;
	
	m_siMapStepCount[_Index] = _siMapStepCount;
}

SI16 CNInstanceMapInfo::GetMapStepCount(SI16 _Index)
{
	if(false == SAFE_ARRAY_CHECK(_Index, m_siMapStepCount))
		return -1;

	return m_siMapStepCount[_Index];
}

void CNInstanceMapInfo::AddMapStepCount(SI16 _Index, SI16 _siMapStepCount)
{
	if(false == SAFE_ARRAY_CHECK(_Index, m_siMapStepCount))
		return;

	m_siMapStepCount[_Index] += _siMapStepCount;
}

SI16 CNInstanceMapInfo::GetMapStepCountSum(void)
{
	SI16 SumCount = 0;
	for(SI32 Count = 0; Count < SERVER_EVENT_INSTANCE_MAP; ++Count)
	{
		SumCount += m_siMapStepCount[Count];
	}

	return SumCount;
}

void CNInstanceMapInfo::SetStartTime( DWORD _dwStartTime )
{
	if ( 0 > _dwStartTime )
	{
		return;
	}

	m_dwStartTime = _dwStartTime;
}

DWORD CNInstanceMapInfo::GetStartTime( void )
{
	return m_dwStartTime;
}

void CNInstanceMapInfo::OpenTheGate( void )
{
	cltServer* pclserver = (cltServer*)pclClient;
	if( NULL == pclserver )
	{
		return;
	}
	
	// �̹� ����Ʈ�� �������� �ʱ� ������ ����
	if ( 0 < m_siGateID ) 
	{
		pclserver->pclServerEventManager->SetServerEventState( SERVER_EVENT_STATE_GOING_INDUN );
		return;
	}

	// ����Ʈ ������ KIND
	SI32 siGateKind	= pclClient->GetUniqueFromHash("KIND_SERVERGATE");	
	// ����Ʈ�� X,Y��ǥ
	SI32 siX		= 288;
	SI32 siY		= 334;

	// ����Ʈ ����
	m_siGateID = pclserver->SetNPCChar(siGateKind, VILLAGE_NONE, NULL, 1, 0, siX, siY, 0, NPCITEMMODE_NONE, NULL );

	// ����Ʈ�� ���� �Ǿ��ٴ� �޽����� ����
	if ( m_siGateID	> 0 )
	{
		// ����Ʈ ���� �ð��� �����Ѵ�
		SetStartTime( pclClient->CurrentClock );

		// �������� ���
		cltServerResponseValue clreturn( 0, SRVAL_NOTICE_OPENTHE_SERVEREVENTGATE, 0, 0 );
		// Ŭ���̾�Ʈ�� ������ ������. 
		cltMsg clRtnMsg(GAMEMSG_RESPONSE_SERVERRTN, sizeof(cltServerResponseValue), (BYTE*)&clreturn);

		pclClient->pclCM->SendAllPersonMsg( (sPacketHeader*)&clRtnMsg );

		pclserver->pclServerEventManager->SetServerEventState( SERVER_EVENT_STATE_GOING_INDUN );
	}

}

void CNInstanceMapInfo::CloseTheGate( void )
{
	cltServer* pclserver = (cltServer*)pclClient;
	if( NULL == pclserver )
	{
		return;
	}

	// ����Ʈ�� �������� �ʱ⶧���� ����
	if ( 0 >= m_siGateID )
	{
		pclserver->pclServerEventManager->SetServerEventState( SERVER_EVENT_STATE_START_QUEST );
		return;
	}

	// ����Ʈ ������ KIND
	SI32 siGateKind	= pclClient->GetUniqueFromHash("KIND_SERVERGATE");	

	// ����Ʈ�� �����ɶ� �޾ƿ� ���̵�� ������ �����Ѵ�
	if ( pclserver->pclCM->IsValidID(m_siGateID) == false )
	{
		return;
	}

	// �ش� ���̵��� �ɸ��Ͱ� ���ٸ� ����
	cltCharServer* pclGateChar = (cltCharServer*)pclClient->pclCM->CR[m_siGateID];
	if ( pclGateChar == NULL )
	{
		return;
	}

	// �ش� ���̵��� �ɸ��͸� �޾ƿ����� ����Ʈ�� �ƴ϶�� ����
	if ( pclGateChar->GetKind() != siGateKind )
	{
		return;
	}

	// �ش� ����Ʈ�� �����ϰ�
	pclGateChar->DeleteInCell();

	// ������ �Ϸ�Ǿ����� ����Ʈ ���̵� �ٽ� �ʱ�ȭ��Ŵ
	if ( pclserver->pclCM->DeleteChar(m_siGateID) == TRUE )
	{
		m_siGateID = 0;
		SetStartTime( 0 );

		// �������� ���
		cltServerResponseValue clreturn( 0, SRVAL_NOTICE_CLOSETHE_SERVEREVENTGATE, 0, 0 );
		// Ŭ���̾�Ʈ�� ������ ������. 
		cltMsg clRtnMsg(GAMEMSG_RESPONSE_SERVERRTN, sizeof(cltServerResponseValue), (BYTE*)&clreturn);

		pclClient->pclCM->SendAllPersonMsg( (sPacketHeader*)&clRtnMsg );

		pclserver->pclServerEventManager->SetServerEventState( SERVER_EVENT_STATE_START_QUEST );
	}

}

void CNInstanceMapInfo::Action()
{
	// 60��(1��)�� �ȳ����� ����
	if ( TABS(pclClient->CurrentClock - m_dwStartTime) < 60000 )
	{
		return;
	}

	if( TABS(m_dwStartTime - pclClient->CurrentClock) > (INSTANCEMAP_SERVEREVENT_MAX_TIME+60000) )
	{
		cltServer* pclserver = (cltServer*)pclClient;
		if ( NULL == pclserver )
		{
			return;
		}

		pclserver->pclServerEventManager->ManagerExcute( SERVER_EVENT_COMMANDTYPE_INDUN_END );
	}

}

void CNInstanceMapInfo::LeaveLobbyInUser( void )
{
	cltServer* pclserver = (cltServer*)pclClient;
	if( pclserver == NULL )
	{
		return;
	}

	SI32 siMapIndex = MAPINDEX_SERVEREVENT_LOBBY;

	// �ʿ� �ִ� ĳ���͸� �� ������ �̵���Ų��.
	SI32 index = 0;
	SI32 id;

	while(id = pclClient->pclCM->GetCharOrder(index))
	{
		index++;

		if( !IsPC(id) )
		{
			continue;	// ����
		}

		cltCharServer* pclchar = (cltCharServer* )pclClient->pclCM->CR[id];
		if ( NULL == pclchar )
		{
			continue;
		}

		
		if(		pclchar->GetMapIndex() != siMapIndex 
			&&	INSTANCEMAP_TYPE_SERVER != pclClient->pclMapManager->GetInstanceMapType( pclchar->GetMapIndex()) )
		{
			continue;	// �δ��� ����.
		}

		SI32 x = 0 , y = 0;
		cltWarpInfo clWarpInfo(1, 0, false, true, x, y, -1, -1);

		
		if ( pclClient->pclMapManager->pclGateManager->FindMainFieldPos( MAPINDEX_PALACE, &x, &y ) == false )
		{
			continue;
		}

		clWarpInfo.uiMapIndex	= MAPINDEX_PALACE; //������ ���� �� ���´�.
		clWarpInfo.uiX			= x+2;
		clWarpInfo.uiY			= y+2;

		// �����ֵ��� �츰��
		if (pclClient->pclCM->IsAlive(id) == FALSE)
		{
			pclchar->siKilledMode = 0;
		}
		// ���縮�� ������ �̵� ��Ų��.
		else
		{
			// ������ �ִ� ������ ������
			SI32 siVillageMapIndex	= pclchar->pclCI->clBI.siHomeVillage;

			if ( 0 < siVillageMapIndex )
			{
				SI32 siMapTypeUnique	= pclserver->pclMapManager->pclMapArray[ siVillageMapIndex ]->siMapUnique;
				UI32 uiX				= (UI32)pclserver->pclMapManager->pclMapTypeManager->pclMapTypeInfo[ siMapTypeUnique ]->siCenterX;
				UI32 uiY				= (UI32)pclserver->pclMapManager->pclMapTypeManager->pclMapTypeInfo[ siMapTypeUnique ]->siCenterY;

				clWarpInfo.uiMapIndex	= (UI32)siVillageMapIndex;
				clWarpInfo.uiX			= uiX;
				clWarpInfo.uiY			= uiY;
			}

			pclchar->SetWarpInfo(&clWarpInfo, 3000);
			pclchar->Warp();
		}
	} // while(id = pclClient->pclCM->GetCharOrder(index)) ����
}