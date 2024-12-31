#include ".\bbbeventmap.h"

#include "../../NLib/NUtil.h"

#include "../Server/Server.h"
#include "../Char/CharManager/CharManager.h"

#include "../CommonLogic/CommonLogic.h"
#include "../CommonLogic/MsgType.h"
#include "../CommonLogic/Msg/MsgType-BokBulBok.h"
#include "../CommonLogic/MsgRval-Define.h"

#include "../../DBManager/GameDBManager_World/DBMsg-PVP_League.h"
#include "../../DBManager/GameDBManager_World/DBMsg-Item.h"
#include "../../DBManager/GameDBManager_World/DBMsg-Person.h"






CBBBEventMap::CBBBEventMap(SI16 siMapNumber)
{
	m_siMapNumber = siMapNumber;
	m_siStageStartDelay		= 6000;
	m_siStageLoseDelay		= 5000;
	m_siStageWinDelay		= 5000;
	m_siStagePlayDelay		= 15000;
	m_siTotalStageWinDelay  = 5000;
	m_siItemDropRate		= 1000;
	m_bTemporaryOccupied	= false;
	m_dwTemporaryOccupyCancelTime = 0;

	ZeroMemory( m_aItemUnique, sizeof(SI32) * MAX_ITEMKIND_NUM );
	ZeroMemory( m_aMapPosition, sizeof(SI32) * MAX_EVENTMAP_NUM );
	ZeroMemory( m_aMonsterKind, sizeof(SI32) * MAX_GENMOBKIND_NUM );
	ZeroMemory( m_aStageInfo, sizeof(SI32) * MAX_BBBSTAGE_NUM );


	//////////////////////////////////////////////////////////////////////////
	_ClearMonster();
	_ClearThisMap();

	//////////////////////////////////////////////////////////////////////////
	// ���ҽ� ���� �ε�
	if ( pclClient->IsCountrySwitch(Switch_BokBulBok) == true )
	{
		_Load_BBBGameInfo();
		_Load_DropItemKind();
		_Load_EventMapCenterPosition();
		_Load_GenMobKind();
		_Load_StageMobInfo();
	}
}

CBBBEventMap::~CBBBEventMap(void)
{
}


//////////////////////////////////////////////////////////////////////////
bool CBBBEventMap::IsAvailable()
{
	return (m_bOccupied)? false: true;
}

void CBBBEventMap::EnterUser(SI32 siUserID, TCHAR* pszUserName)
{
	cltServer* pclServer = (cltServer*)pclClient;
	cltCharServer* pclChar = pclServer->pclCM->GetCharServer( siUserID );
	if ( NULL == pclChar )
	{
		_ClearMonster();
		_ClearThisMap();
		return;
	}

	// ĳ���Ͱ� ���� ������ ������ �ִ��� üũ
	GMONEY gMyMoney = pclChar->pclCI->clIP.GetMoney();

	SI32 siNPCRate = pclClient->pclItemManager->clItemStatistic.siNPCPriceRate;
	GMONEY siEntranceFee = siNPCRate * 10;

	if ( gMyMoney >= siEntranceFee )
	{
		//	��������ϰ� ���� �˸���.
		sDBRequest_ChangeMoney clMsg(pclChar->GetID(), pclChar->pclCI->GetPersonID(), CHANGE_MONEY_REASON_BOKBULBOK_ENTRANCE_FEE, -siEntranceFee);
		pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

		pclServer->m_pServer_BBBMgr->SetEntranceFee( siEntranceFee );


		// ���Һ��α�
		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// ���Һ� ���� ������� ������ �ݾ� �α׷� ����.
			pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_BOKBULBOK, LOGCOMMAND_INDEX_BOKBULBOK_PAID, 
				0, pclChar,NULL ,0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
				siEntranceFee, 0, 0, 0, 0, NULL, NULL);	// para1 : ������
		}


		// ������ �������� �� ��ŸƮ
		m_bOccupied = true;
		m_siCurrentStage = 1;
		m_siUserID = siUserID;
		MStrCpy( m_szUserName, pszUserName, sizeof(TCHAR) * MAX_PLAYER_NAME );

		// ���� ��ŸƮ
		GameStart();
	}
	else						// ������ ������ �����Ϸ��� �������� �� ���ٰ� ��Ŷ ������ ���� �ٽ� ������� �����
	{
		// ��Ŷ ������
		cltGameMsgResponse_BBB_NotEnoughMoney clinfo( m_siUserID );
		cltMsg clMsg( GAMEMSG_RESPONSE_BBB_NOTENOUGHMONEY, sizeof(clinfo), (BYTE*)&clinfo);
		pclChar->SendNetMsg((sPacketHeader*)&clMsg);

		// ��� ����
		_ClearMonster();
		_ClearThisMap();
		return;
	}


}

void CBBBEventMap::LeaveUser()
{
	cltServer* pclServer = (cltServer*)pclClient;

	// �ϴ� ������ ���� ��Ų��.
	cltCharServer* pclChar = pclServer->pclCM->GetCharServer( m_siUserID );
	if ( pclChar != NULL )
	{
		cltWarpInfo clWarpInfo(1, 0, true, false, 100, 174, -1, -1);
		clWarpInfo.uiMapIndex = PLAY_MAP_INDEX;

		pclChar->SetWarpInfo(&clWarpInfo, 2200);	// �ش� ��ġ�� ���� �Ѵ� .
		pclChar->Warp()	;
	}

	_ClearMonster();
	_ClearThisMap();
}

//////////////////////////////////////////////////////////////////////////
SI32 CBBBEventMap::GetUserID()
{
	return m_siUserID;
}

void CBBBEventMap::SetUserID(SI32 siUserID)
{
	m_siUserID = siUserID;
}

void CBBBEventMap::SetUserName(TCHAR* pszUserName)
{
	MStrCpy( m_szUserName, pszUserName, sizeof(TCHAR) * MAX_PLAYER_NAME );
}

TCHAR* CBBBEventMap::GetUserName()
{
	return m_szUserName;
}

void CBBBEventMap::SetCurrentStage(SI16 siCurrentStage)
{
	m_siCurrentStage = siCurrentStage;
}

SI16 CBBBEventMap::GetCurrentStage()
{
	return m_siCurrentStage;
}


//////////////////////////////////////////////////////////////////////////
void CBBBEventMap::GameStart()
{
	_WarpUserToMap( m_siMapNumber );
	m_bNeedCreateMonster = true;
	_StartCount();
}

void CBBBEventMap::GameFail()
{
	if ( true == m_bNeedClearMap )	// �������� ���� �÷��װ� �̹� �����Ǿ� �ִ�.
	{
		return;
	}
	m_bStageStartFlag = false;
	m_dwStageStartTime = 0;

	cltServer* pclServer = (cltServer*)pclClient;

	cltCharServer* pclChar = pclServer->pclCM->GetCharServer( m_siUserID );

	if(NULL == pclServer->m_pServer_BBBMgr)
		return;

	// ���Һ��α�
	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// ���Һ� ����
		pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_BOKBULBOK, LOGCOMMAND_INDEX_BOKBULBOK_CLEAR_FAIL, 
			0, pclChar, NULL ,0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
			m_siCurrentStage, pclServer->m_pServer_BBBMgr->m_siTotalRewardPrice, 0, 0, 0, NULL, NULL);	// para1 : ���� �ܰ� para2 : �����ݾ�
	}


	if ( NULL == pclChar )
	{
		_ClearMonster();
		_ClearThisMap();
		return;
	}

	DWORD dwStageEndTime = pclServer->CurrentClock;

	// ���� ��Ŷ�� Ŭ��� ������
	cltGameMsgResponse_BBB_StageFail clinfo( m_siUserID, dwStageEndTime );
	cltMsg clMsg( GAMEMSG_RESPONSE_BBB_STAGEFAIL, sizeof(clinfo), (BYTE*)&clinfo);
	pclChar->SendNetMsg((sPacketHeader*)&clMsg);

	// �ʿ� �����ִ� ���� Ŭ���� �ϰ�
	_ClearMonster();

	// 5�ʵ� �ʵ�� �����϶�� ����
	m_bNeedClearMap = true;
	m_bStageEndFlag = false;
	m_dwStageEndTime = pclServer->CurrentClock;
}

void CBBBEventMap::GameClear()
{
	if ( true == m_bNeedClearMap )	// �������� ���� �÷��װ� �̹� �����Ǿ� �ִ�.
	{
		return;
	}

	// �ϴ� �� �����
	_ClearMonster();
	m_bStageEndFlag = true;		// �������� Ŭ���� �÷��׸� true�� ����

	// ��� �������� Ŭ����
	if ( 10 == m_siCurrentStage )
	{
		_ClearReward();
	}
	else
	{
		_NextStage();
	}
}

void CBBBEventMap::_WarpUserToMap(SI16 siMapNumber)
{
	cltServer* pServer = (cltServer*)pclClient;

	cltWarpInfo clWarpInfo(1, 0, true, false, m_aMapPosition[siMapNumber].posX, m_aMapPosition[siMapNumber].posY, -1, -1);
	clWarpInfo.uiMapIndex = PLAY_MAP_INDEX;

	//SI32 siCharId = pServer->pclCM->GetIDFromPersonID( m_siUserID ) ;

	cltCharServer* pclchar = (cltCharServer*)pServer->pclCM->GetCharServer( m_siUserID );
	if (pclchar == NULL )
	{
		// ���� ������ ���ٴ°Ŵϱ� �ش� �ʿ� �������ִ� ���� ������ �ʱ�ȭ �ϰ� ������ ���� ����ٰ� �뺸
		_ClearMonster();
		_ClearThisMap();
		return;
	}

	pclchar->SetWarpInfo(&clWarpInfo, 2200);	// �ش� ��ġ�� ���� �Ѵ� .
	pclchar->Warp();
}

void CBBBEventMap::_CreateMonster(SI16 siStageNumber)
{
	cltServer* pServer = (cltServer*)pclClient;

	SI32 siMonsterKind	=	0	;	// �̾Ƴ� ���� ī�ε�
	SI32 siX	=	0	;	// ���� ������ X��ǥ
	SI32 siY	=	0	;	// ���� ������ Y��ǥ
	SI32 siMapIndex		=	PLAY_MAP_INDEX	;	// ����߸� ���ε���
	SI32 silevel		=	0	;	// ���� ����
	SI32 siMakeCount	=	0	;	// ���� ����  ����
	SI32 siEnergy		=	10000;
	SI32 siLevel		=	10	;

	//////////////////////////////////////////////////////////////////////////
	SI16 siGenMobIndex = rand() % 4;

	//////////////////////////////////////////////////////////////////////////
	_SetupCurrentStageMonsterInfo();

	//////////////////////////////////////////////////////////////////////////
	for (siMakeCount; siMakeCount < MAX_MONSTER_COUNT; siMakeCount++ )
	{
		//////////////////////////////////////////////////////////////////////////	�����ϰ� ��ǥ ����
		siX = m_aMapPosition[m_siMapNumber].posX;
		siY = m_aMapPosition[m_siMapNumber].posY;
		siX = siX + rand() % 4 * ((rand()%2)? -1 : 1);
		siY = siY + rand() % 4 * ((rand()%2)? -1 : 1);

		//////////////////////////////////////////////////////////////////////////

		siMonsterKind = m_aMonsterKind[siGenMobIndex];

		cltMapCommon* pclmap = pServer->pclMapManager->GetMapPointer( siMapIndex )	;	// ��������
		if(pclmap != NULL)
		{
			cltInnerStatusInfo clinnerstatus;
			clinnerstatus.clEnemyType.Set(ENEMYTYPE_ALLPC, 0);

			// �� Ÿ�Ժ��� ���� identity�� �����Ѵ�.
			SI16 siMonsterIdentity = IDENTITY_BOKBULBOK_EVENTMONSTER;

			switch ( m_aStageMobInfo[siMakeCount] )
			{
			case MONSTER_TYPE_NORMAL:
				siMonsterIdentity = IDENTITY_BOKBULBOK_EVENTMONSTER;
				break;
			case MONSTER_TYPE_ONEKILL:
				siMonsterIdentity = IDENTITY_BOKBULBOK_ONEKILLMONSTER;
				break;
			case MONSTER_TYPE_KEY:
				siMonsterIdentity = IDENTITY_BOKBULBOK_KEYMONSTER;
				break;
			case MONSTER_TYPE_ITEM:
				siMonsterIdentity = IDENTITY_BOKBULBOK_ITEMMONSTER;
				break;
			default:
				siMonsterIdentity = IDENTITY_BOKBULBOK_EVENTMONSTER;
			}

			cltIdentity clIdentity;
			clIdentity.MakeBBBEventMonster( siMonsterIdentity );

			siEnergy = ( m_aStageMobInfo[siMakeCount] == MONSTER_TYPE_ONEKILL )? 2000000 : 1 ;

			SI32 id = pServer->SetNPCChar( siMonsterKind, 
				VILLAGE_NONE, 
				&clIdentity, 
				siLevel, 
				siEnergy, 
				siX, 
				siY, 
				siMapIndex, 
				NPCITEMMODE_NONE, 
				&clinnerstatus );

			cltCharServer* pCharServer = pServer->pclCM->GetCharServer( id );

			if ( NULL != pCharServer )
			{
				m_aGenMosterUnique[siMakeCount] = id;
				SI16 itemUniqueIndex = rand() % 4;
				pCharServer->pclKI->siAggressive = 0;

				if ( MONSTER_TYPE_ONEKILL == m_aStageMobInfo[siMakeCount] )	// ���� ��ų ��
				{
					//SI32 attacktype, SI32 range, SI32 mindamage, SI32 maxdamage, SI32 ac
					pCharServer->pclKI->clDefaultWeaponInfo.Set( ATTACKTYPE_HAND, 5, 1, 1, 1 );
					pCharServer->bOneKill = true;
				}
				else
				{
#ifdef _DEBUG
					if ( MONSTER_TYPE_KEY == m_aStageMobInfo[siMakeCount] )	// Ű��
					{
						pCharServer->clIdentity.siIdentity;
						pCharServer->SetName( "KEYMOB" );
					}					
#endif
					pCharServer->pclKI->clDefaultWeaponInfo.Set( ATTACKTYPE_HAND, 1, 1, 1, 1 );
				}

				if ( MONSTER_TYPE_ITEM == m_aStageMobInfo[siMakeCount] )	// ���� ��
				{
					cltItem item( m_aItemUnique[itemUniqueIndex] );
					pCharServer->AddItemToInventory( &item );
					pCharServer->pclKI->clItemPbtSet.Add( m_aItemUnique[itemUniqueIndex], m_siItemDropRate, 1, 1 );
#ifdef _DEBUG
					pCharServer->SetName( "ITEMMOB" );
#endif
				}
			}
		}
	}
}

void CBBBEventMap::_StartCount()
{
	cltServer* pServer = (cltServer*)pclClient;

	cltCharServer* pclChar = pServer->pclCM->GetCharServer( m_siUserID );
	if ( NULL == pclChar )
	{
		_ClearMonster();
		_ClearThisMap();
		return;
	}

	m_bStageStartFlag = true;
	m_dwStageStartTime = pServer->CurrentClock;// + 5000;		// ��ŸƮ ���� 5�ʵ� �����̹Ƿ� 5�ʸ� ���ؼ� ���� �ð����� �����ص�.

	// Ŭ�� ���� ������ �˸��� ��Ŷ ���� (5�� ī��Ʈ �����ϰ� �ٷ� ����)
	cltGameMsgResponse_BBB_StageStart clinfo( m_siUserID, m_siCurrentStage, m_dwStageStartTime ); // 10�ܰ� ���� �����ϱ� ���� �������� ������ ���� ����.
	cltMsg clMsg( GAMEMSG_RESPONSE_BBB_STAGESTART, sizeof(clinfo), (BYTE*)&clinfo);
	pclChar->SendNetMsg((sPacketHeader*)&clMsg);
}

void CBBBEventMap::_StartStage(SI16 siStageNumber)
{
}

bool CBBBEventMap::_EndStage()
{
	return true;
}

void CBBBEventMap::_ClearThisMap()
{
	if ( false == m_bOccupied ) return;

	m_bTemporaryOccupied = false;
	m_dwTemporaryOccupyCancelTime = 0;
	m_bOccupied = false;
	m_siUserID = 0;
	m_siCurrentStage = 0;
	ZeroMemory( m_szUserName, sizeof(TCHAR) * MAX_PLAYER_NAME );
	m_dwStageStartTime = 0;
	m_bStageStartFlag = false;
	m_dwStageEndTime = 0;
	m_bStageEndFlag = false;
	m_bNeedClearMap = false;
	m_bNeedCreateMonster = false;
	ZeroMemory( m_aStageMobInfo, sizeof(SI16) * MAX_MONSTER_COUNT );
	ZeroMemory( m_aGenMosterUnique, sizeof(SI32) * MAX_MONSTER_COUNT );
}

void CBBBEventMap::_SetupCurrentStageMonsterInfo()
{
	ZeroMemory( m_aStageMobInfo, sizeof(SI16) * 10 );
	ZeroMemory( m_aGenMosterUnique, sizeof(SI16) * 10 );

	for ( int i = 0; i < MAX_MONSTER_COUNT; ++i )
	{
		m_aStageMobInfo[i] = MONSTER_TYPE_NORMAL;		// �Ϲݸ�
		
		//m_aStageMobInfo[i] = MONSTER_TYPE_KEY;		// Ű��
		//m_aStageMobInfo[i] = MONSTER_TYPE_ITEM;       // �����۸�
		//m_aStageMobInfo[i] = MONSTER_TYPE_ONEKILL;    // �����۸�
	}

	_SetKeyMob();
	_SetOneKillMob();
	_SetItemMob();
}

void CBBBEventMap::_SetKeyMob()
{
	for ( int i = 0; i < m_aStageInfo[m_siCurrentStage-1].siKeyMobCount; ++i )
	{
		int k = 0;
		while( 1000 > k )
		{
			SI16 keyMobIndex = rand() % MAX_MONSTER_COUNT;
			if ( 0 == m_aStageMobInfo[keyMobIndex] )
			{
				m_aStageMobInfo[keyMobIndex] = MONSTER_TYPE_KEY;		// Ű��
				break;
			}
			++k;
		}
	}
}

void CBBBEventMap::_SetOneKillMob()
{
	for ( int i = 0; i < m_aStageInfo[m_siCurrentStage-1].siOneKillMobCount; ++i )
	{
		int k = 0;
		while( 1000 > k )
		{
			SI16 keyMobIndex = rand() % MAX_MONSTER_COUNT;
			if ( 0 == m_aStageMobInfo[keyMobIndex] )
			{
				m_aStageMobInfo[keyMobIndex] = MONSTER_TYPE_ONEKILL;		// ��ų��
				break;
			}
			++k;
		}
	}
}

void CBBBEventMap::_SetItemMob()
{
	for ( int i = 0; i < m_aStageInfo[m_siCurrentStage-1].siItemMobCount; ++i )
	{
		int k = 0;
		while( 1000 > k )
		{
			SI16 keyMobIndex = rand() % MAX_MONSTER_COUNT;
			if ( 0 == m_aStageMobInfo[keyMobIndex] )
			{
				m_aStageMobInfo[keyMobIndex] = MONSTER_TYPE_ITEM;		// �����۸�
				break;
			}
			++k;
		}
	}
}

void CBBBEventMap::DoTimeTask()
{
	cltServer* pServer = (cltServer*)pclClient;

	// ĳ���Ͱ� �ִ� ��ġ�� �̺�Ʈ �������� ���� �´��� üũ. �ƴҰ�쿣 ������� �����.
	cltCharServer* pclchar = (cltCharServer*)pServer->pclCM->GetCharServer( m_siUserID );

	if ( NULL == pclchar )
	{
		_ClearMonster();
		_ClearThisMap();
	}

	if ( false == m_bTemporaryOccupied )
	{
		//if ( NULL == pclchar )
		//{
		//	_ClearMonster();
		//	_ClearThisMap();
		//}
		if ( true == m_bOccupied )
		{
			if ( NULL != pclchar )
			{
				if ( PLAY_MAP_INDEX == pclchar->GetMapIndex() )
				{
					cltMapCommon* pclmap = pServer->pclMapManager->GetMapPointer( PLAY_MAP_INDEX );
					if ( NULL != pclmap )
					{
						SI32 siColl = pclmap->CalcCollInfo( pclchar->GetX(), pclchar->GetY());
						if( 0 == (siColl & BLOCK_EVENT2 || siColl & BLOCK_EVENT3 || siColl & BLOCK_EVENT5 || siColl & BLOCK_EVENT6) )		// 2, 3, 5, 6�� �̺�Ʈ Ÿ���� ��� ���� ������
						{
							_ClearMonster();
							_ClearThisMap();
							//return;
						}
					}
					else						// �̺�Ʈ �� ��ü�� ����.
					{
						_ClearMonster();
						_ClearThisMap();
						//return;
					}
				}
				else							// ������ �̺�Ʈ �ʿ� ����.
				{
					_ClearMonster();
					_ClearThisMap();
					//return;
				}
			}
			else								// ���� �̿����� ������ ����.
			{
				_ClearMonster();
				_ClearThisMap();
				return;
			}
		}
	}
	else
	{
		if ( NULL != pclchar )
		{
			if ( m_dwTemporaryOccupyCancelTime < pServer->CurrentClock )
			{
				CancelTemporaryReserve(0);	// 0�� �ǹ� ���� ����
			}
		}
		else
		{
			_ClearMonster();
			_ClearThisMap();
			return;
		}
	}

	if ( true == m_bNeedClearMap )
	{
		if ( false == m_bStageEndFlag )		// ���������� ������ �������� (Ŭ���� ���� ��������)
		{
			if ( m_dwStageEndTime + m_siStageLoseDelay < pServer->CurrentClock )
			{
				m_bNeedClearMap = false;

				// ĳ���͸� npc ��ó�� ����
				cltWarpInfo clWarpInfo(1, 0, true, false, 100, 174, -1, -1);
				clWarpInfo.uiMapIndex = PLAY_MAP_INDEX;

				if (pclchar == NULL )
				{
					_ClearMonster();
					_ClearThisMap();
					return;
				}

				pclchar->SetWarpInfo(&clWarpInfo, 2200);	// �ش� ��ġ�� ���� �Ѵ� .
				pclchar->Warp();

				_ClearMonster();
				_ClearThisMap();
			}
		}
		else		// ���������� ���������� �������� ���� ���������� �Ѿ
		{
			if ( m_dwStageEndTime + m_siStageWinDelay < pServer->CurrentClock )
			{
				m_bNeedClearMap = false;
				m_bStageEndFlag = false;
				m_bNeedCreateMonster = true;
				_StartCount();
			}
		}

	}

	if ( true == m_bStageStartFlag )
	{
		if ( true == m_bNeedCreateMonster )
		{
			if ( m_dwStageStartTime + m_siStageStartDelay < pServer->CurrentClock )
			{
				m_bNeedCreateMonster = false;
				m_bStageEndFlag = false;
				_CreateMonster( m_siCurrentStage );
			}
		}		

		if ( m_dwStageStartTime + m_siStagePlayDelay + m_siStageStartDelay < pServer->CurrentClock )
		{
			GameFail();
		}
	}
}

void CBBBEventMap::_ClearMonster()
{
	// �ʵ忡 ���� ����
	cltServer* pclserver = (cltServer*)pclClient;
	if ( false == m_bOccupied ) return;

	for ( SI32 siIndex = 0; siIndex <MAX_MONSTER_COUNT; siIndex++ ) 
	{
		SI32 siMonsterID = m_aGenMosterUnique[siIndex];

		// ���̵� ������ 0�� ä�� ����Ʈ�ּ� ����� .
		m_aGenMosterUnique[siIndex] = 0 ;
		cltCharServer* pclMonster = pclClient->pclCM->GetCharServer( siMonsterID );
		if ( pclMonster != NULL ) 
		{
			if( IDENTITY_BOKBULBOK_EVENTMONSTER == pclMonster->clIdentity.siIdentity
				|| IDENTITY_BOKBULBOK_ITEMMONSTER == pclMonster->clIdentity.siIdentity
				|| IDENTITY_BOKBULBOK_KEYMONSTER == pclMonster->clIdentity.siIdentity
				|| IDENTITY_BOKBULBOK_ONEKILLMONSTER == pclMonster->clIdentity.siIdentity )
			{
				SI32 siMapindex = pclMonster->GetMapIndex();

				if( siMapindex == PLAY_MAP_INDEX )// �ش� ���ε����� �ְ� 
				{
					cltMapCommon* pclmap = pclClient->pclMapManager->GetMapPointer(siMapindex);

					if(pclmap != NULL)
					{
						SI32 siColl = pclmap->CalcCollInfo( pclMonster->GetX(), pclMonster->GetY())	;
						if( siColl & BLOCK_EVENT2 || siColl & BLOCK_EVENT3
							|| siColl & BLOCK_EVENT5 || siColl & BLOCK_EVENT6 )	// 2, 3, 5, 6�� �̺�Ʈ Ÿ���� ��� ������.
						{
							pclMonster->SetLife(0);
							pclMonster->DeleteInCell();
						}
					}
				}
			}
		}
	}
}

void CBBBEventMap::_NextStage()
{
	cltServer* pServer = (cltServer*)pclClient;

	cltCharServer* pclChar = pServer->pclCM->GetCharServer( m_siUserID );
	if ( NULL == pclChar )
	{
		_ClearMonster();
		_ClearThisMap();
		return;
	}

	if ( 0 < m_siCurrentStage && 10 > m_siCurrentStage )
	{
		m_siCurrentStage++;

		// 8�������� ����
		if ( 8 <= m_siCurrentStage )
		{
			_Notice_8_StageUser();
		}

		m_bNeedClearMap = true;
		m_bStageEndFlag = true;
		m_dwStageEndTime = pServer->CurrentClock;

		// Ŭ���̾�Ʈ�� �¸� �̹��� �����ֶ�� ��Ŷ �����°� �߰�
		cltGameMsgResponse_BBB_StageClear clinfo( m_siUserID );
		cltMsg clMsg( GAMEMSG_RESPONSE_BBB_STAGECLEAR, sizeof(clinfo), (BYTE*)&clinfo);
		pclChar->SendNetMsg((sPacketHeader*)&clMsg);
	}
}

void CBBBEventMap::_ClearReward()
{
	cltServer* pServer = (cltServer*)pclClient;

	cltCharServer* pclCharServer = pServer->pclCM->GetCharServer( m_siUserID );
	if( pclCharServer != NULL )
	{
		SI32 siMapindex = pclCharServer->GetMapIndex();
		if( siMapindex == PLAY_MAP_INDEX )
		{
			cltMapCommon* pclmap = pclClient->pclMapManager->GetMapPointer(siMapindex);
			if(pclmap != NULL)
			{
				SI32 siColl = pclmap->CalcCollInfo( pclCharServer->GetX(), pclCharServer->GetY())	;
				if( siColl & BLOCK_EVENT2 || siColl & BLOCK_EVENT3
					|| siColl & BLOCK_EVENT5 || siColl & BLOCK_EVENT6 )
				{
					// ĳ���Ϳ��� ���� �ְ� ������� ���� â ���
					GMONEY siRewardMoney = pServer->m_pServer_BBBMgr->GetRewardMoney();

					sDBRequest_ChangeMoney clMsg(pclCharServer->GetID(), pclCharServer->pclCI->GetPersonID(), CHANGE_MONEY_REASON_BOKBULBOK_REWARD, siRewardMoney);
					pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
					pServer->SendServerResponseCharMsg2( 0, SRVAL_RETURN_BOKBULBOK_CLEAR_REWARD, SI64ToString(siRewardMoney), NULL, NULL, pclCharServer->GetCharUnique() ); // ����

					cltGameMsgResponse_BBB_10ClearNotice clinfo( m_siUserID, siRewardMoney, (TCHAR*)pclCharServer->GetName() );
					cltMsg clMsg2(GAMEMSG_RESPONSE_BBB_10CLEARNOTICE, sizeof(clinfo), (BYTE*)&clinfo);
			
					// ����s �ϰ�쿣 �̺�Ʈ �ʿ��� �ѷ��ش�
					if( true == pclClient->IsWhereServiceArea( ConstServiceArea_Korea ) )
					{
						pServer->pclCM->SendAllPersonInMapMsg( (sPacketHeader*)&clMsg2, pclCharServer->GetMapIndex() );
					}
					else
					{
						pServer->pclCM->SendAllPersonMsg((sPacketHeader*)&clMsg2);
					}

					// ���� �� �ٱ����� ������Ŵ
					cltWarpInfo clWarpInfo(1, 0, true, false, 100, 174, -1, -1);
					clWarpInfo.uiMapIndex = PLAY_MAP_INDEX;
					pclCharServer->SetWarpInfo(&clWarpInfo, 2200);	// �ش� ��ġ�� ���� �Ѵ� .
					pclCharServer->Warp();

					_ClearMonster();
					_ClearThisMap();


					// ���Һ��α�
					if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
					{
						// ���Һ� ���� �����ܰ� Ŭ���� �� �޴� ��� �α� ����.
						pServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_BOKBULBOK, LOGCOMMAND_INDEX_BOKBULBOK_REWARD_MONEY, 
							0, pclCharServer,NULL ,0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
							siRewardMoney, 0, 0, 0, 0, NULL, NULL);	// para1 : ���
					}


				}
			}
		}
	}
}

void CBBBEventMap::SetTemporaryReserve(SI32 siUserID)
{
	cltServer* pclServer = (cltServer*)pclClient;
	cltCharServer* pclChar = pclServer->pclCM->GetCharServer( siUserID );
	if ( NULL == pclChar )
	{
		_ClearMonster();
		_ClearThisMap();
		return;
	}

	const TCHAR* pszCharName = pclChar->GetName();

	m_dwTemporaryOccupyCancelTime = pclServer->CurrentClock + 13 * 1000;		// 13�� (��Ŷ �ְ� �޴� ������ ����)
	m_bTemporaryOccupied = true;
	m_bOccupied = true;
	m_siCurrentStage = 1;
	m_siUserID = siUserID;	
	MStrCpy( m_szUserName, pszCharName, sizeof(TCHAR) * MAX_PLAYER_NAME );
}

void CBBBEventMap::ActiveTemporaryReserve(SI32 siUserID)
{
	// �ӽÿ��� ��Ȳ�� �����ش�. 
	m_bTemporaryOccupied = false;
	m_dwTemporaryOccupyCancelTime = 0;

	if ( m_siUserID == siUserID )
	{
		cltServer* pclServer = (cltServer*)pclClient;
		cltCharServer* pclChar = pclServer->pclCM->GetCharServer( siUserID );
		if ( NULL != pclChar)
		{
			//////////////////////////////////////////////////////////////////////////
			// ĳ���Ͱ� ���� ������ ������ �ִ��� üũ
			GMONEY gMyMoney = pclChar->pclCI->clIP.GetMoney();

			SI32 siNPCRate = pclClient->pclItemManager->clItemStatistic.siNPCPriceRate;
			GMONEY siEntranceFee = siNPCRate * 10;

			if ( gMyMoney >= siEntranceFee )
			{
				//	��������ϰ� ���� �˸���.
				sDBRequest_ChangeMoney clMsg(pclChar->GetID(), pclChar->pclCI->GetPersonID(), CHANGE_MONEY_REASON_BOKBULBOK_ENTRANCE_FEE, -siEntranceFee);
				pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

				pclServer->m_pServer_BBBMgr->SetEntranceFee( siEntranceFee );


				// ���Һ��α�
				if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
				{
					// ���Һ� ���� ������ �α� ����.
					pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_BOKBULBOK, LOGCOMMAND_INDEX_BOKBULBOK_PAID, 
						0, pclChar,NULL ,0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
						siEntranceFee, 0, 0, 0, 0, NULL, NULL);	// para1 : ������
				}


				// ������ �������� �� ��ŸƮ
				GameStart();
				return;
			}
			else						// ������ ������ �����Ϸ��� �������� �� ���ٰ� ��Ŷ ������ ���� �ٽ� ������� �����
			{
				// ��Ŷ ������
				cltGameMsgResponse_BBB_NotEnoughMoney clinfo( m_siUserID );
				cltMsg clMsg( GAMEMSG_RESPONSE_BBB_NOTENOUGHMONEY, sizeof(clinfo), (BYTE*)&clinfo);
				pclChar->SendNetMsg((sPacketHeader*)&clMsg);

				// ��� ����
				_ClearMonster();
				_ClearThisMap();
				return;
			}			
		}
	}

	_ClearMonster();
	_ClearThisMap();
}

void CBBBEventMap::CancelTemporaryReserve(SI32 siUserID)
{
	m_bTemporaryOccupied = false;
	m_dwTemporaryOccupyCancelTime = 0;
	_ClearMonster();
	_ClearThisMap();
}

void CBBBEventMap::_Load_DropItemKind()
{
	// ���� ���� : �ִ� ��� ������ ������ ���� (���� 4����)

	//////////////////////////////////////////////////////////////////////////
	// ���� �ε�
	NDataLoader	dataloader;
	BOOL bLoadFile=FALSE;

	if( pclClient->IsWhereServiceArea( ConstSwitch_TextEncryption ) )
	{
		bLoadFile = dataloader.LoadDataFromCryptFile( TEXT("Data/BBBEvent/BBBEvent_DropItemKind.txt") );
	}
	else
	{
		if ( pclClient->IsWhereServiceArea(ConstServiceArea_China) )
		{
			bLoadFile = dataloader.LoadDataFromCryptFile( TEXT("Data/BBBEvent/BBBEvent_DropItemKind.txt"));
		}
		
		else
		{
			bLoadFile = dataloader.LoadDataFromFile( TEXT("Data/BBBEvent/BBBEvent_DropItemKind.txt") );
		}	
	}

	if (!bLoadFile)
	{
		MsgBox( TEXT("Not LoadFromFile BBBEvent_DropItemKind.txt"),TEXT("Error"));
		return;
	}


	//////////////////////////////////////////////////////////////////////////
	// �о���� ���� �������� �迭 �ʱ�ȭ
	SI32 siDropItemKind = 0;					// ��� ������ ����ũ

	NDataTypeInfo pDataTypeInfo[] =
	{
		NDATA_INT32,	&siDropItemKind,	4,
			0,				0,					0
	};	
	dataloader.RegDataType( pDataTypeInfo );


	//////////////////////////////////////////////////////////////////////////
	SI32 siArrayindex = 0 ;
	while( !dataloader.IsEndOfData() )
	{
		if ( dataloader.ReadData(true) )
		{
			if ( siArrayindex >= MAX_ITEMKIND_NUM )	break;
			if( siDropItemKind <= 0 )	continue;

			m_aItemUnique[siArrayindex] = siDropItemKind;
			++siArrayindex;
		}
	}
}

void CBBBEventMap::_Load_EventMapCenterPosition()
{
	// ���� ���� : �ִ� �̺�Ʈ ���� ������ ���� ���� (���� 4��)
	//////////////////////////////////////////////////////////////////////////
	// ���� �ε�
	NDataLoader	dataloader;
	BOOL bLoadFile=FALSE;

	if( pclClient->IsWhereServiceArea( ConstSwitch_TextEncryption ) )
	{
		bLoadFile = dataloader.LoadDataFromCryptFile( TEXT("Data/BBBEvent/BBBEvent_EventMapCenterPosition.txt") );
	}
	else
	{
		if ( pclClient->IsWhereServiceArea(ConstServiceArea_China) )
		{
			bLoadFile = dataloader.LoadDataFromCryptFile( TEXT("Data/BBBEvent/BBBEvent_EventMapCenterPosition.txt"));
		}

		else
		{
			bLoadFile = dataloader.LoadDataFromFile( TEXT("Data/BBBEvent/BBBEvent_EventMapCenterPosition.txt") );
		}
		
	}

	if (!bLoadFile)
	{
		MsgBox( TEXT("Not LoadFromFile BBBEvent_EventMapCenterPosition.txt"),TEXT("Error"));
		return;
	}


	//////////////////////////////////////////////////////////////////////////
	// �о���� ���� �������� �迭 �ʱ�ȭ
	SI32 siMapIndex = 0;					// �� �ε���
	SI32 siPosX = 0;						// x ��ǥ
	SI32 siPosY = 0;						// y ��ǥ

	NDataTypeInfo pDataTypeInfo[] =
	{
		NDATA_INT32,	&siMapIndex,	4,
			NDATA_INT32,	&siPosX,		4,
			NDATA_INT32,	&siPosY,		4,
			0,				0,				0
	};	
	dataloader.RegDataType( pDataTypeInfo );


	//////////////////////////////////////////////////////////////////////////
	SI32 siArrayindex = 0;
	while( !dataloader.IsEndOfData() )
	{
		if ( dataloader.ReadData(true) )
		{
			if ( siArrayindex >= MAX_EVENTMAP_NUM )	break;
			if( 0 > siMapIndex || MAX_EVENTMAP_NUM <= siMapIndex ) continue;

			m_aMapPosition[siMapIndex].posX = siPosX;
			m_aMapPosition[siMapIndex].posY = siPosY;

			++siArrayindex;
		}
	}
}

void CBBBEventMap::_Load_GenMobKind()
{
	// ���� ���� : ���� ������ �� ������ �� ���� (��������, ��������, �����䳢 ���)
	//////////////////////////////////////////////////////////////////////////
	// ���� �ε�
	NDataLoader	dataloader;
	BOOL bLoadFile=FALSE;

	if( pclClient->IsWhereServiceArea( ConstSwitch_TextEncryption ) )
	{
		bLoadFile = dataloader.LoadDataFromCryptFile( TEXT("Data/BBBEvent/BBBEvent_GenMonsterKind.txt") );
	}
	else
	{
		if ( pclClient->IsWhereServiceArea(ConstServiceArea_China) )
		{
			bLoadFile = dataloader.LoadDataFromCryptFile( TEXT("Data/BBBEvent/BBBEvent_GenMonsterKind.txt"));
		}

		else
		{
			bLoadFile = dataloader.LoadDataFromFile( TEXT("Data/BBBEvent/BBBEvent_GenMonsterKind.txt") );
		}	
	}

	if (!bLoadFile)
	{
		MsgBox( TEXT("Not LoadFromFile BBBEvent_GenMonsterKind.txt"),TEXT("Error"));
		return;
	}


	//////////////////////////////////////////////////////////////////////////
	// �о���� ���� �������� �迭 �ʱ�ȭ
	TCHAR szGenMobKind[64] = TEXT("");					// �� �� ī�ε�

	NDataTypeInfo pDataTypeInfo[] =
	{
		NDATA_MBSTRING,		&szGenMobKind,		64,
			0,					0,					0
	};	
	dataloader.RegDataType( pDataTypeInfo );


	//////////////////////////////////////////////////////////////////////////
	SI32 siArrayindex = 0;
	while( !dataloader.IsEndOfData() )
	{
		if ( dataloader.ReadData(true) )
		{
			if ( siArrayindex >= MAX_GENMOBKIND_NUM )	break;

			SI32 siMonsterUnique =	pclClient->GetUniqueFromHash( szGenMobKind );
			if ( 0 >= siMonsterUnique ) continue;

			m_aMonsterKind[siArrayindex] = siMonsterUnique;

			++siArrayindex;
		}
	}
}

void CBBBEventMap::_Load_StageMobInfo()
{
	// ���� ���� : �� Ÿ���� ���� (������, ��ų��, Ű�� ��)
	//////////////////////////////////////////////////////////////////////////
	// ���� �ε�
	NDataLoader	dataloader;
	BOOL bLoadFile=FALSE;

	if( pclClient->IsWhereServiceArea( ConstSwitch_TextEncryption ) )
	{
		bLoadFile = dataloader.LoadDataFromCryptFile( TEXT("Data/BBBEvent/BBBEvent_StageMobInfo.txt") );
	}
	else
	{
		if ( pclClient->IsWhereServiceArea(ConstServiceArea_China) )
		{
			bLoadFile = dataloader.LoadDataFromCryptFile( TEXT("Data/BBBEvent/BBBEvent_StageMobInfo.txt"));
		}

		else
		{
			bLoadFile = dataloader.LoadDataFromFile( TEXT("Data/BBBEvent/BBBEvent_StageMobInfo.txt") );
		}
	}

	if (!bLoadFile)
	{
		MsgBox( TEXT("Not LoadFromFile BBBEvent_StageMobInfo.txt"),TEXT("Error"));
		return;
	}

	//////////////////////////////////////////////////////////////////////////
	// �о���� ���� �������� �迭 �ʱ�ȭ
	SI32 siStageNumber = 0;			// �������� ��ȣ
	SI32 siOneKill = 0;				// ��ų���� ��
	SI32 siKey = 0;					// Ű�� ��
	SI32 siItem = 0;				// ������ ��

	NDataTypeInfo pDataTypeInfo[] =
	{
		NDATA_INT32,	&siStageNumber,		4,
		NDATA_INT32,	&siOneKill,			4,
			NDATA_INT32,	&siKey,				4,
			NDATA_INT32,	&siItem,			4,
			0,				0,					0
	};	
	dataloader.RegDataType( pDataTypeInfo );


	//////////////////////////////////////////////////////////////////////////
	SI32 siArrayindex = 0;
	while( !dataloader.IsEndOfData() )
	{
		if ( dataloader.ReadData(true) )
		{
			if ( siArrayindex >= MAX_BBBSTAGE_NUM )	break;

			m_aStageInfo[siArrayindex].siOneKillMobCount = siOneKill;
			m_aStageInfo[siArrayindex].siKeyMobCount = siKey;
			m_aStageInfo[siArrayindex].siItemMobCount = siItem;

			++siArrayindex;
		}
	}
}

void CBBBEventMap::_Load_BBBGameInfo()
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
	//SI32 siTotalWinDelay = 0;			// ������������ �Ϸ��� �ߴ� Win ������
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
			m_siStagePlayDelay = siPlayDelay * 1000;
			m_siItemDropRate = siDropRate * 100;
			//m_siTotalStageWinDelay = siTotalWinDelay * 1000;

			++siArrayindex;
		}
	}
}

void CBBBEventMap::_Notice_8_StageUser()
{
	cltServer* pServer = (cltServer*)pclClient;

	// ���� 1
	TCHAR* pHeadTag = GetTxtFromMgr(5482); 

	NTCHARString256 strMapNumber;
	NTCHARString256 strUserName( m_szUserName );
	NTCHARString256 strStageNumber;
	NTCHARString256 pContents( GetTxtFromMgr(40067) );

	//(INT64 num , TCHAR * dest , SI16 destsize, TCHAR * add )
	g_JYLibFunction.SetNumUnit( (m_siMapNumber+1), strMapNumber, 2 );
	g_JYLibFunction.SetNumUnit( (m_siCurrentStage), strStageNumber, 2 );

	pContents.Replace( "#num#", strMapNumber );
	pContents.Replace( "#name#", strUserName );
	pContents.Replace( "#stage#", strStageNumber );

	cltGameMsgResponse_Notice clNotice( pHeadTag, pContents, true);
	cltMsg clMsg( GAMEMSG_RESPONSE_NOTICE, clNotice.siDataSize, (BYTE*)&clNotice );
	pServer->pclCM->SendAllPersonInMapMsg( (sPacketHeader*)&clMsg, MAPINDEX_FESTIVAL);

	// ���� 2
	TCHAR* pHeadTag2 = GetTxtFromMgr(5482); 
	NTCHARString256 pContents2( GetTxtFromMgr(40093) );

	cltGameMsgResponse_Notice clNotice2( pHeadTag2, pContents2, true);
	cltMsg clMsg2( GAMEMSG_RESPONSE_NOTICE, clNotice2.siDataSize, (BYTE*)&clNotice2 );
	pServer->pclCM->SendAllPersonInMapMsg( (sPacketHeader*)&clMsg2, MAPINDEX_FESTIVAL);
}