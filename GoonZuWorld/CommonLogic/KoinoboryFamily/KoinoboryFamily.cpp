#include "KoinoboryFamily.h"
#include "CommonLogic.h"
#include "Server.h"
#include "Char\CharCommon\Char-Common.h"
#include "Char\CharManager\CharManager.h"
#include "../CommonLogic/Village/Village.h"
#include "../Common/Event/Event.h"

cltKoinoboryFamilyPosition::cltKoinoboryFamilyPosition( void )
{
	ZeroMemory( this, sizeof(cltKoinoboryFamilyPosition) );
}

cltKoinoboryFamilyPosition::~cltKoinoboryFamilyPosition( void )
{

}

void cltKoinoboryFamilyPosition::Init( void )
{
	ZeroMemory( this, sizeof(cltKoinoboryFamilyPosition) );
}

void cltKoinoboryFamilyPosition::SetPosition( void )
{
	SI32			siPosIndex		= 0;
	SI32			siVillageIndex	= 1;

	cltVillageInfo*	pclVillage		= NULL;

	for ( siPosIndex=0; siPosIndex<MAX_KOINOBORYFAMILY_MAKE_POS; siPosIndex++ )
	{
		if ( MAX_VILLAGE_NUMBER <= siVillageIndex )
		{
			break;
		}

		// ���� �������� ��ȿ�� ��ü�� ����´�
		for ( SI32 siIndex=siVillageIndex; siIndex<MAX_VILLAGE_NUMBER; siIndex++)
		{
			pclVillage = pclClient->pclVillageManager->pclVillageInfo[siIndex];
			if ( NULL == pclVillage )
			{
				continue;
			}

			// ���� �ε����� �����ؾ� �ϱ� ������ +1�� �Ѵ�
			siVillageIndex = siIndex+1;
			break;
		}

		// �ѹ��� �˻��غ���
		if ( NULL == pclVillage )
		{
			MsgBox(TEXT("cltKoinoboryFamilyPosition in SetPosition()"),TEXT("VillageInfoReadError"));
			break;
		}

		m_clPos[siPosIndex].SetMapIndex( MAPINDEX_MAINFIELD );
		m_clPos[siPosIndex].SetX( pclVillage->PosX );
		m_clPos[siPosIndex].SetY( pclVillage->PosY );

		// ���� �ε����� �ϴ� ���������� �־�д�
		m_siRandIndex[siPosIndex] = siPosIndex;
	}
}

void cltKoinoboryFamilyPosition::RandomMixUpIndex( void )
{
	SI32 siRandomIndex	= 0;
	SI32 siSwapIndex	= 0;

	for (SI32 siPosIndex=0; siPosIndex<MAX_KOINOBORYFAMILY_MAKE_POS; siPosIndex++ )
	{
		siRandomIndex = rand() % MAX_KOINOBORYFAMILY_MAKE_POS;

		if ( siPosIndex == siRandomIndex )
		{
			continue;
		}

		siSwapIndex						= m_siRandIndex[siPosIndex];
		m_siRandIndex[siPosIndex]		= m_siRandIndex[siRandomIndex];
		m_siRandIndex[siRandomIndex]	= siSwapIndex;
	}
}

cltCharPos* cltKoinoboryFamilyPosition::GetRandomPosition( const SI32 siIndex )
{
	// ������ 42���� ������ �ʿ��Ѱ��� �տ������� 3�����̴� �׷��� ����ü��ִ� ��ȣ�� 0���� 2������ �Ѱ���
	if ( (KOINOBORYFAMILY_KIND_NONE >= siIndex) || (KOINOBORYFAMILY_KIND_MAX <= siIndex) )
	{
		return NULL;
	}

	SI32 siRealIndex = m_siRandIndex[siIndex];
	if ( (0 > siRealIndex) || (MAX_KOINOBORYFAMILY_MAKE_POS <= siRealIndex) )
	{
		return NULL;
	}
	
	return &m_clPos[ siRealIndex ];
}


//------------------------------------------------------------------------------------------------------------------
//
//	cltKoinoboryFamilyManager!!	cltKoinoboryFamilyManager!!	cltKoinoboryFamilyManager!!	cltKoinoboryFamilyManager!!
//
//------------------------------------------------------------------------------------------------------------------
cltKoinoboryFamilyManager::cltKoinoboryFamilyManager()
{
	m_clPos.Init();
	m_clPos.SetPosition();

	ZeroMemory( m_siKonoboryIndex, sizeof(m_siKonoboryIndex) );

	m_siStartHour = -1;
}

cltKoinoboryFamilyManager::~cltKoinoboryFamilyManager()
{

}

void cltKoinoboryFamilyManager::Action()
{
	if ( GAMEMODE_SERVER != pclClient->GameMode )
	{
		return;
	}

	cltServer* pclserver = (cltServer*)pclClient;
	if ( NULL == pclserver )
	{
		return;
	}

	if ( false == pclserver->pclEventTimeManager->InEventTime(TEXT("GoldenWeekEvent"), &pclserver->sTime) )
	{
		return;
	}

	SI16 siNowHour = pclserver->sTime.wHour;

	// ������ �ð��� ������ �̹� ������� �ִٰ� �ص��ȴ�
	if ( m_siStartHour == siNowHour )
	{
		// �����鿡�� ��ġ�� �˷��ش�
		NoticeKoinoboryFamily();
	}
	else
	{
		// ���Ӱ� ���̳뺸���� �����
		MakeKoinoboryFamily();

		// �����鿡�� ��ġ�� �˷��ش�
		NoticeKoinoboryFamily();

		m_siStartHour = siNowHour;
	}
}

void cltKoinoboryFamilyManager::StartEvent()
{
}

void cltKoinoboryFamilyManager::EndEvent()
{
}

void cltKoinoboryFamilyManager::MakeKoinoboryFamily( void )
{
	// ��� ��ġ�� �����ش�
	m_clPos.RandomMixUpIndex();

	// 3���� ����
	for ( SI32 siCount=0; siCount<KOINOBORYFAMILY_KIND_MAX; siCount++ )
	{
		// Ȥ�� �ε����� ���̳뺸���� �����Ѵٸ� �� ���̳뺸���� �����Ѵ�
		if ( 0 < m_siKonoboryIndex[siCount] )
		{
			DeleteKoinobory( siCount );
		}

		CreateKoinobory( siCount );
	}
}

void cltKoinoboryFamilyManager::NoticeKoinoboryFamily( void )
{
	cltServer* pclserver = (cltServer*)pclClient;
	if ( NULL == pclserver )
	{
		return;
	}

	cltCharServer*	pclchar			= NULL;
	SI32			siCharID		= 0;

	SI32			siVillageUnique	= 0;
	TCHAR*			pszVillageName	= NULL;
	
	for ( SI32 siCount=0; siCount<KOINOBORYFAMILY_KIND_MAX; siCount++ )
	{
		siCharID = m_siKonoboryIndex[siCount];
		if ( siCharID <= 0 )
		{
			continue;
		}

		pclchar = pclserver->pclCM->GetCharServer( siCharID );
		if ( NULL == pclchar )
		{
			m_siKonoboryIndex[siCount] = 0;
			continue;
		}

		if ( pclchar->GetKind() != GetKoinoboryKind(siCount) )
		{
			m_siKonoboryIndex[siCount] = 0;
			continue;
		}

		siVillageUnique = pclserver->pclVillageManager->FindNearVillage( pclchar->GetX(), pclchar->GetY() );
		pszVillageName	= pclserver->pclVillageManager->GetName( siVillageUnique );
		if ( NULL == pszVillageName )
		{
			continue;
		}

		TCHAR*	pText			= GetTxtFromMgr( 7038 );
		TCHAR	szBuffer[256]	= TEXT("");

		StringCchPrintf( szBuffer, 256, pText, pszVillageName  );
		
		// ��� �αٿ� �ִ��� ������ ������
		pclserver->SendNoticeMsg( -1, 0, 0, szBuffer );
	}

}

bool cltKoinoboryFamilyManager::CreateKoinobory( const SI32 siIndex )
{
	if ( (KOINOBORYFAMILY_KIND_NONE >= siIndex) || (KOINOBORYFAMILY_KIND_MAX <= siIndex) )
	{
		return false;
	}

	cltServer* pclserver = (cltServer*)pclClient;
	if ( NULL == pclserver )
	{
		return false;
	}

	cltCharPos* pclPos = m_clPos.GetRandomPosition( siIndex );
	if ( NULL == pclPos )
	{
		return false;
	}

	SI32 siKind		= GetKoinoboryKind( siIndex );
	SI32 siMapIndex = pclPos->GetMapIndex();
	SI32 siX		= pclPos->GetX();
	SI32 siY		= pclPos->GetY();

	SI32 siGetX		= 0;
	SI32 siGetY		= 0;

	cltInnerStatusInfo clinnerstatus;
	clinnerstatus.clEnemyType.Set(ENEMYTYPE_ALLPC, 0);

	cltMapCommon* pclMapCommon = pclClient->pclMapManager->pclMapArray[siMapIndex];
	if ( NULL == pclMapCommon )
	{
		return false;
	}

	// Ȥ�� �𸣴� ��� ��������
	for ( SI32 siCount=0; siCount<20; siCount++ )
	{
		if ( false == pclMapCommon->FindEmptyAreaForCharLocate(siKind, siX, siY, 20, &siGetX, &siGetY, true) )
		{
			continue;
		}

		SI32 siID = pclserver->SetNPCChar(siKind, VILLAGE_NONE, NULL, 1, 0, siGetX, siGetY, siMapIndex, NPCITEMMODE_NORMAL, &clinnerstatus );
		if ( pclserver->pclCM->IsValidID(siID) )
		{
			cltCharServer* pclchar = pclserver->pclCM->GetCharServer( siID );
			if ( NULL == pclchar )
			{
				continue;
			}

			pclchar->dwTimerClock		= pclserver->CurrentClock;
			m_siKonoboryIndex[siIndex]	= siID;

			return true;
		}
	}

	return false;
}

bool cltKoinoboryFamilyManager::DeleteKoinobory( const SI32 siIndex )
{
	if ( (KOINOBORYFAMILY_KIND_NONE >= siIndex) || (KOINOBORYFAMILY_KIND_MAX <= siIndex) )
	{
		return false;
	}

	SI32 siCharIndex = m_siKonoboryIndex[siIndex];
	if ( false == pclClient->pclCM->IsValidID(siCharIndex) )
	{
		m_siKonoboryIndex[siIndex] = 0;
		return true;
	}

	cltCharServer* pclchar = pclClient->pclCM->GetCharServer(siCharIndex);
	if ( NULL == pclchar )
	{
		m_siKonoboryIndex[siIndex] = 0;
		return true;
	}

	if ( pclchar->GetKind() != GetKoinoboryKind(siIndex) )
	{
		m_siKonoboryIndex[siIndex] = 0;
		return true;
	}

	pclchar->DeleteInCell();
	if ( TRUE == pclClient->pclCM->DeleteChar(siCharIndex) )
	{
		m_siKonoboryIndex[siIndex] = 0;
		return true;
	}

	return false;

}

SI32 cltKoinoboryFamilyManager::GetKoinoboryKind( const SI32 siIndex )
{
	switch ( siIndex )
	{
	case KOINOBORYFAMILY_KIND_YELLOW:
		{
			return pclClient->GetUniqueFromHash( TEXT("KIND_KOINOBORYYELLOW") );
		}
		break;

	case KOINOBORYFAMILY_KIND_RED:
		{
			return pclClient->GetUniqueFromHash( TEXT("KIND_KOINOBORYRED") );
		}
		break;

	case KOINOBORYFAMILY_KIND_BLUE:
		{
			return pclClient->GetUniqueFromHash( TEXT("KIND_KOINOBORYBLUE")  );
		}
		break;

	}

	return KOINOBORYFAMILY_KIND_NONE;
}

SI32 cltKoinoboryFamilyManager::GetKoinoboryYellowKind()
{
	return pclClient->GetUniqueFromHash( TEXT("KIND_KOINOBORYYELLOW") );
}

SI32 cltKoinoboryFamilyManager::GetKoinoboryRedKind()
{
	return pclClient->GetUniqueFromHash( TEXT("KIND_KOINOBORYRED") );
}

SI32 cltKoinoboryFamilyManager::GetKoinoboryBlueKind()
{
	return pclClient->GetUniqueFromHash( TEXT("KIND_KOINOBORYBLUE")  );
}


/*
void cltKoinoboryFamilyManager::Action()	// 1�п� �ѹ��� ȣ���� �����
{
	//	if (bStartEvent == false)
	//	{
	//		return;
	//	}

	if( m_siLastCreatedTime < 0 )
	{
		m_siLastCreatedTime = ((cltServer*)pclClient)->sTime.wHour;
		return;
	}

	// �̺�Ʈ �ð� üũ�� ����
	SYSTEMTIME	stCur;
	GetLocalTime(&stCur);
	if( pclClient->pclEventTimeManager->InEventTime("GoldenWeekEvent", &stCur) == false )
		return;

	SI32 index = 0;
	SI32 id = 0;
	TCHAR buf[256] = TEXT("");

	bool bAliveYellowKoinobory = false;
	bool bAliveRedKoinobory = false;
	bool bAliveBlueKoinobory = false;

	// 1�п� �ѹ��� ������ ���� �̺�Ʈ�� ���������� �˸���
	// �ѽð��� �ѹ��� ������ üũ�Ѵ�
	if(m_siLastCreatedTime == ((cltServer*)pclClient)->sTime.wHour )
	{ 
		// ���̳뺸�� ������ ����� ���� ��ó���� ������ �ٴϰ��ִٴ� �޽����� �����ְ� ����.
		// ���̳뺸�� ������ ���δ� �׾����� ���� �޽��� ���� �׳� ����
		index = 0;

		while(id = pclClient->pclCM->GetCharOrder(index))
		{
			if ( bAliveYellowKoinobory && bAliveRedKoinobory && bAliveBlueKoinobory )
				break;

			index++;

			if (id > 0 && pclClient->pclCM->IsValidID(id))
			{
				cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[id];

				if ( pclchar->GetKind() == GetKoinoboryYellowKind() )
				{	
					bAliveYellowKoinobory = true;		

					// ���ƴٴϰ� ������ �����鿡�� ����
					TCHAR * pText = GetTxtFromMgr(7038);
					const TCHAR * pMapName = pclClient->pclVillageManager->GetName(pclClient->pclVillageManager->FindNearVillage(pclchar->GetX(), pclchar->GetY()));
					TCHAR szBuffer[256];
					szBuffer[0] = 0;
					if( pText != NULL && pMapName != NULL )
					{
						StringCchPrintf( szBuffer , 256 , pText , pMapName );
						((cltServer*)pclClient)->SendNoticeMsg(-1, 0, 0, szBuffer);
					}
				}
				else if ( pclchar->GetKind() == GetKoinoboryBlueKind() )
				{	
					bAliveBlueKoinobory = true;

					// ���ƴٴϰ� ������ �����鿡�� ����
					TCHAR * pText = GetTxtFromMgr(7038);
					const TCHAR * pMapName = pclClient->pclVillageManager->GetName(pclClient->pclVillageManager->FindNearVillage(pclchar->GetX(), pclchar->GetY()));
					TCHAR szBuffer[256];
					szBuffer[0] = 0;
					if( pText != NULL && pMapName != NULL )
					{
						StringCchPrintf( szBuffer , 256 , pText , pMapName );
						((cltServer*)pclClient)->SendNoticeMsg(-1, 0, 0, szBuffer);
					}
				}
				else if ( pclchar->GetKind() == GetKoinoboryRedKind() )
				{	
					bAliveRedKoinobory = true;

					// ���ƴٴϰ� ������ �����鿡�� ����
					TCHAR * pText = GetTxtFromMgr(7038);
					const TCHAR * pMapName = pclClient->pclVillageManager->GetName(pclClient->pclVillageManager->FindNearVillage(pclchar->GetX(), pclchar->GetY()));
					TCHAR szBuffer[256];
					szBuffer[0] = 0;
					if( pText != NULL && pMapName != NULL )
					{
						StringCchPrintf( szBuffer , 256 , pText , pMapName );
						((cltServer*)pclClient)->SendNoticeMsg(-1, 0, 0, szBuffer);
					}
				}
			}
		}

		return;
	}
	else
	{
		// ���̳뺸�� ������ �׾ �������ٸ� ���� �����Ѵ�.
		index = 0;

		while(id = pclClient->pclCM->GetCharOrder(index))
		{
			if ( bAliveYellowKoinobory && bAliveRedKoinobory && bAliveBlueKoinobory )
				break;

			index++;

			if (id > 0 && pclClient->pclCM->IsValidID(id))
			{
				cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[id];

				if ( pclchar->GetKind() == GetKoinoboryYellowKind() )
				{	
					bAliveYellowKoinobory = true;

					StringCchPrintf(buf, 256, TEXT("Current Yellow Mon x : %d, y : %d"), pclchar->GetX(), pclchar->GetY());
					pclClient->pclLog->FilePrint(TEXT("Config\\KoinoboryFamily.log"), buf);

				}
				else if ( pclchar->GetKind() == GetKoinoboryBlueKind() )
				{	
					bAliveBlueKoinobory = true;

					StringCchPrintf(buf, 256, TEXT("Current Blue Mon x : %d, y : %d"), pclchar->GetX(), pclchar->GetY());
					pclClient->pclLog->FilePrint(TEXT("Config\\KoinoboryFamily.log"), buf);
				}
				else if ( pclchar->GetKind() == GetKoinoboryRedKind() )
				{	
					bAliveRedKoinobory = true;

					StringCchPrintf(buf, 256, TEXT("Current Red Mon x : %d, y : %d"), pclchar->GetX(), pclchar->GetY());
					pclClient->pclLog->FilePrint(TEXT("Config\\KoinoboryFamily.log"), buf);
				}

			}
		}


		SI32 index1 = -1, index2 = -1 , index3 = -1;


		// ���̳뺸������ �������� �ʴ� �༮�� ���� ������ش�
		if ( bAliveYellowKoinobory != true )
		{

			index1 = rand() % MAX_KOINOBORYFAMILY_MAKE_POS;

			cltServer *pclserver = (cltServer*)pclClient;

			cltInnerStatusInfo clinnerstatus;
			clinnerstatus.clEnemyType.Set(ENEMYTYPE_ALLPC, index1);

			SI32 x = 0, y = 0, mapindex = 0;
			mapindex = clPos[index1].siMapIndex;

			pclClient->pclMapManager->pclMapArray[mapindex]->FindEmptyAreaForCharLocate(GetKoinoboryYellowKind(), clPos[index1].siX, clPos[index1].siY, 20, &x, &y, true);

			pclserver->SetNPCChar(GetKoinoboryYellowKind(), VILLAGE_NONE, NULL, 1, 0, x, 
				y, mapindex, NPCITEMMODE_NORMAL, &clinnerstatus );
			StringCchPrintf(buf, 256, TEXT("Gen Yellow x : %d, y : %d"), x, y);
			pclClient->pclLog->FilePrint(TEXT("Config\\KoinoboryFamily.log"), buf);

			// �����Ǿ����� �����鿡�� ����
			TCHAR * pText = GetTxtFromMgr(7037);
			const TCHAR * pMapName = pclClient->pclVillageManager->GetName(pclClient->pclVillageManager->FindNearVillage(x, y));
			TCHAR szBuffer[256];
			szBuffer[0] = 0;
			if( pText != NULL && pMapName != NULL )
			{
				StringCchPrintf( szBuffer , 256 , pText ,pMapName );
				((cltServer*)pclClient)->SendNoticeMsg(-1, 0, 0, szBuffer);
			}
		}

		// ���̳뺸������ �������� �ʴ� �༮�� ���� ������ش�
		if ( bAliveRedKoinobory != true )
		{
			bool bPass = false;
			SI32 cnt = 0;

			while( bPass != true )
			{
				index2 = rand() % MAX_KOINOBORYFAMILY_MAKE_POS;

				if( index2 != index1 )
					bPass = true;

				if( cnt++ > 1000000)
					return;

			}

			cltServer *pclserver = (cltServer*)pclClient;

			cltInnerStatusInfo clinnerstatus;
			clinnerstatus.clEnemyType.Set(ENEMYTYPE_ALLPC, index2);

			SI32 x = 0, y = 0, mapindex = 0;
			mapindex = clPos[index2].siMapIndex;

			pclClient->pclMapManager->pclMapArray[mapindex]->FindEmptyAreaForCharLocate(GetKoinoboryRedKind(), clPos[index2].siX, clPos[index2].siY, 20, &x, &y, true);

			pclserver->SetNPCChar(GetKoinoboryRedKind(), VILLAGE_NONE, NULL, 1, 0, x, 
				y, mapindex, NPCITEMMODE_NORMAL, &clinnerstatus );
			StringCchPrintf(buf, 256, TEXT("Gen Red x : %d, y : %d"), x, y);
			pclClient->pclLog->FilePrint(TEXT("Config\\KoinoboryFamily.log"), buf);

			// �����Ǿ����� �����鿡�� ����
			TCHAR * pText = GetTxtFromMgr(7037);
			const TCHAR * pMapName = pclClient->pclVillageManager->GetName(pclClient->pclVillageManager->FindNearVillage(x, y));
			TCHAR szBuffer[256];
			szBuffer[0] = 0;
			if( pText != NULL && pMapName != NULL )
			{
				StringCchPrintf( szBuffer , 256 , pText  , pMapName );
				((cltServer*)pclClient)->SendNoticeMsg(-1, 0, 0, szBuffer);
			}
		}

		// ���̳뺸������ �������� �ʴ� �༮�� ���� ������ش�
		if ( bAliveBlueKoinobory != true )
		{
			bool bPass = false;     
			SI32 cnt = 0;

			while( bPass != true )
			{
				index3 = rand() % MAX_KOINOBORYFAMILY_MAKE_POS;

				if( index3 != index1 && index3 != index2 )
					bPass = true;

				if( cnt++ > 1000000)
					return;

			}

			cltServer *pclserver = (cltServer*)pclClient;

			cltInnerStatusInfo clinnerstatus;
			clinnerstatus.clEnemyType.Set(ENEMYTYPE_ALLPC, index3);

			SI32 x = 0, y = 0, mapindex = 0;
			mapindex = clPos[index3].siMapIndex;

			pclClient->pclMapManager->pclMapArray[mapindex]->FindEmptyAreaForCharLocate(GetKoinoboryBlueKind(), clPos[index3].siX, clPos[index3].siY, 20, &x, &y, true);

			pclserver->SetNPCChar(GetKoinoboryBlueKind(), VILLAGE_NONE, NULL, 1, 0, x, 
				y, mapindex, NPCITEMMODE_NORMAL, &clinnerstatus );
			StringCchPrintf(buf, 256, TEXT("Gen Blue x : %d, y : %d"), x, y);
			pclClient->pclLog->FilePrint(TEXT("Config\\KoinoboryFamily.log"), buf);

			// �����Ǿ����� �����鿡�� ����
			TCHAR * pText = GetTxtFromMgr(7037);
			const TCHAR * pMapName = pclClient->pclVillageManager->GetName(pclClient->pclVillageManager->FindNearVillage(x, y));
			TCHAR szBuffer[256];
			szBuffer[0] = 0;
			if( pText != NULL && pMapName != NULL )
			{
				StringCchPrintf( szBuffer , 256 , pText , pMapName );
				((cltServer*)pclClient)->SendNoticeMsg(-1, 0, 0, szBuffer);
			}
		}

		m_siLastCreatedTime = ((cltServer*)pclClient)->sTime.wHour;
	}
}

void cltKoinoboryFamilyManager::StartEvent()
{
	//	if (bStartEvent)
	//	{
	//		EndEvent();
	//	}

	SI32 index1 = 0 , index2 = 0, index3 = 0;
	bool bPass = false;
	SI32 cnt = 0;

	index1 = rand() % MAX_KOINOBORYFAMILY_MAKE_POS;

	while (!bPass)
	{
		index2 = rand() % MAX_KOINOBORYFAMILY_MAKE_POS;

		if (index1 != index2)
			bPass = true;

		if(cnt++ > 1000000) return;		

	}

	bPass = false;
	cnt = 0;

	while (!bPass)
	{
		index3 = rand() % MAX_KOINOBORYFAMILY_MAKE_POS;

		if (index1 != index3 && index2 != index3)
			bPass = true;

		if(cnt++ > 1000000) return;	
	}

	cltServer *pclserver = (cltServer*)pclClient;

	cltInnerStatusInfo clinnerstatus;
	clinnerstatus.clEnemyType.Set(ENEMYTYPE_ALLPC, index1);

	SI32 x = 0, y = 0, mapindex = 0;

	mapindex = clPos[index1].siMapIndex;

	pclClient->pclMapManager->pclMapArray[mapindex]->FindEmptyAreaForCharLocate(GetKoinoboryYellowKind(), clPos[index1].siX, clPos[index1].siY, 20, &x, &y, true);

	pclserver->SetNPCChar(GetKoinoboryYellowKind(), VILLAGE_NONE, NULL, 1, 0, x, 
		y, mapindex, NPCITEMMODE_NORMAL, &clinnerstatus );

	x = 0; 
	y = 0;
	mapindex = clPos[index2].siMapIndex;

	cltInnerStatusInfo clinnerstatus2;
	clinnerstatus2.clEnemyType.Set(ENEMYTYPE_ALLPC, index2);

	pclClient->pclMapManager->pclMapArray[mapindex]->FindEmptyAreaForCharLocate(GetKoinoboryRedKind(), clPos[index2].siX, clPos[index2].siY, 20, &x, &y, true);

	pclserver->SetNPCChar(GetKoinoboryRedKind(), VILLAGE_NONE, NULL, 1, 0, x, 
		y, mapindex, NPCITEMMODE_NORMAL, &clinnerstatus2 );

	x = 0; 
	y = 0;
	mapindex = clPos[index3].siMapIndex;

	cltInnerStatusInfo clinnerstatus3;
	clinnerstatus3.clEnemyType.Set(ENEMYTYPE_ALLPC, index3);

	pclClient->pclMapManager->pclMapArray[mapindex]->FindEmptyAreaForCharLocate(GetKoinoboryBlueKind(), clPos[index3].siX, clPos[index3].siY, 20, &x, &y, true);

	pclserver->SetNPCChar(GetKoinoboryBlueKind(), VILLAGE_NONE, NULL, 1, 0, x, 
		y, mapindex, NPCITEMMODE_NORMAL, &clinnerstatus3 );

	//	bStartEvent = true;

}

void cltKoinoboryFamilyManager::EndEvent()
{
	SI32 index = 0;
	SI32 id;
	while(id = pclClient->pclCM->GetCharOrder(index))
	{
		index++;

		if (id > 0 && pclClient->pclCM->IsValidID(id))
		{
			cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[id];

			if (pclchar->GetKind() == GetKoinoboryBlueKind() 
				|| pclchar->GetKind() == GetKoinoboryRedKind()
				|| pclchar->GetKind() == GetKoinoboryYellowKind())
			{
				// �� �������� ������ �����Ѵ�. 
				pclClient->pclCM->CR[id]->DeleteInCell();
				if(pclClient->pclCM->DeleteChar( id ) == TRUE)
				{
					index--;
				}
			}

		}

	}

	//	bStartEvent = false;

}
*/