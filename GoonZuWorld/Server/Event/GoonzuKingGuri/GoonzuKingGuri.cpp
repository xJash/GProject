#include "GoonzuKingGuri.h"

#include "../CommonLogic/CommonLogic.h"
#include "../Server/Server.h"

//-----------------------------------------
// Common
//-----------------------------------------
#include "../Common/Char/KindInfo/KindInfo.h"
#include "../Common/Order/Order.h"
#include "Char/CharManager/CharManager.h"

#include "MsgType-System.h"

#include "../../Client/Music/Music.h"

#include "../../../DBManager/GameDBManager_World/DBMsg-Item.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-System.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-Person.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-Village.h"

#include <MsgType-Person.h>

extern cltCommonLogic* pclClient;

CGoonzuKingGuriEvent::CGoonzuKingGuriEvent() : cltEvent()
{
	SI32 i;
	for( i = 0; i < MAX_GOONZU_KINGGURI_NUM; ++i )
	{
		if ( i >= MAX_GOONZU_KINGGURI_NUM )	continue	;	// �迭�� �Ѿ�� ���������� �д´�� �ѱ��.	�ʱ�ȭ�� �� ���ݾ�.
		m_bKilledKingGuri[i] = false;
		m_siKingGuriID[i] = 0;
	}
	for ( SI32 siSlot = 0 ; siSlot < MAX_SELECTRFIELD_NUM_GOONZURACCOONEVENT; siSlot++) 
	{
		GoonzuRaccoonEventData[siSlot].init()	;
	}
	// �ð� �ʱ�ȭ 
	LsatsetTime.wYear	=	2009	;
	LsatsetTime.wMonth	=	10	;
	LsatsetTime.wDay	=	1	;
	LsatsetTime.wHour	=	1	;
	LsatsetTime.wSecond	=	0	;
	LsatsetTime.wMinute	=	0	;
	LsatsetTime.wMilliseconds	=	0	;
	LsatsetTime.wDayOfWeek	=	0	;

	for ( SI32 siSlot = 0 ; siSlot < MAX_GOONZU_KINGGURI_NUM; siSlot++) 
	{
		StringCchCopy( m_szSelectedAreaName[siSlot], 32, TEXT("") );
	}	
}

CGoonzuKingGuriEvent::~CGoonzuKingGuriEvent()
{
}

void CGoonzuKingGuriEvent::Init()
{
	for( SI32 i = 0; i < MAX_GOONZU_KINGGURI_NUM; ++i )
	{
		if ( i >= MAX_GOONZU_KINGGURI_NUM )	continue	;	// �迭�� �Ѿ�� ���������� �д´�� �ѱ��.	�ʱ�ȭ�� �� ���ݾ�.
		m_bKilledKingGuri[i] = false;
		m_siKingGuriID[i] = 0;
	}

	cltEvent::Init();
}

void CGoonzuKingGuriEvent::Start()
{
	Init();

	bEventSwitch = true;
#ifdef _DEBUG
	dwLeftClock = 1000 * 60 * 50; 
#else
	dwLeftClock = 1000 * 60 * 50; 
#endif	
	dwStartClock = pclClient->CurrentClock;
	dwLastInfoClock = pclClient->CurrentClock;

	//[�߰� : Ȳ���� 2007. 11. 13 �Ϻ��� ��� ������ �̺�Ʈ�� 50 �е���.]
	if( pclClient->siServiceArea == ConstServiceArea_Japan )
	{
#ifdef _DEBUG
		dwLeftClock = 1000 * 60 * 10; 
#else
		dwLeftClock = 1000 * 60 * 50; 
#endif
	}
}

void CGoonzuKingGuriEvent::Action()
{
	if( pclClient->IsCountrySwitch( Switch_RaccoonEvent_Change_Goonzu ) )
	{
		if( false == bEventSwitch )
		{
			cltServer* pclserver = (cltServer*)pclClient;
			if(0 == (pclserver->sTime.wMinute%60))
			{
				MakeKingGuri();	// ���ÿ� �ѹ��� ������ 
				pclserver->pclLog->FileConfigPrint( "GoonzuKingGuri", "Start" );
			}
		}
		else
		{
			if( pclClient->CurrentClock - dwStartClock > dwLeftClock )
			{
				End();
			}
			//[�߰� : Ȳ���� 2007. 11. 14 ��� ������ ���Ͱ� �� �׾����� �̺�Ʈ ����.]
			else if(true == MonsterAllDie())
			{
				End();
			}
			else
			{
				SI32 SendTime = 20 * 1000; //15�� ����

				//[�߰� : Ȳ���� 2007. 11. 13 �Ϻ��� ��� ������ ���� �޽��� ����.]
				if( pclClient->siServiceArea == ConstServiceArea_Japan ||
					pclClient->siServiceArea == ConstServiceArea_USA   ||
					pclClient->siServiceArea == ConstServiceArea_NHNChina	||
					pclClient->siServiceArea == ConstServiceArea_Korea	)
				{
					//SendTime = 200000; // 3��20�ʸ���.

					SendTime = 60 * 5 * 1000	;	// 5�и���
				}

				// ��ü�������� �޼��� ����
				if( pclClient->CurrentClock - dwLastInfoClock > (DWORD)SendTime )
				{
					DWORD leftClock = dwLeftClock - ( pclClient->CurrentClock - dwStartClock ); 
					SendInfo( ACTION, leftClock );
					dwLastInfoClock = pclClient->CurrentClock;
				}
			}
		}
	}
}

void CGoonzuKingGuriEvent::End()
{
	bEventSwitch = false;

	SI32 index = 0;
	SI32 id = 0;
	while( id = pclClient->pclCM->GetCharOrder(index) )
	{
		index++;

		cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[id];

		if( NULL != pclchar)
		{
			if( pclClient->pclCM->IsValidID(id) == false )		
				continue;

			if( pclchar->siCharMode == CHARMODE_KINGGURI )	
			{
				// �� �������� ������ �����Ѵ�. 
				pclClient->pclCM->CR[id]->DeleteInCell();
				if( pclClient->pclCM->DeleteChar( id ) == TRUE )
				{
					index--;
				}
			}
		}
	}

	SendInfo( END, 0 );

	Init();
}


void CGoonzuKingGuriEvent::MakeKingGuri()
{
	cltServer* pclserver = (cltServer*)pclClient;

	SI32 siMakeRaccoonCount	=	0	;
	// �ʹ�ȣ �ʱ���.
	m_siAreaIndex[0] = m_siAreaIndex[1] = m_siAreaIndex[2] = -1;

	// �ش� �ð��� �Ǹ� �´� �ð��� ã�Ƽ� ������
	for (SI32 siMakeRaccoon = 0 ; siMakeRaccoon < MAX_SELECTRFIELD_NUM_GOONZURACCOONEVENT; siMakeRaccoon++ )	// Ÿ�Ӻ��� �˻� �Ѵ� 
	{
		if( siMakeRaccoon >= MAX_SELECTRFIELD_NUM_GOONZURACCOONEVENT)	return	;
		// �ð��� �³� �˻� �ؼ� ��� ��Ų�� 
		SI32 siTime = GoonzuRaccoonEventData[siMakeRaccoon].GetTime()	;	// ���� �ð�
		if (siTime < 0 || siTime > MAX_HOUR_GOONZURACCOONEVENT )	return	;
		if(pclserver->sTime.wHour == (WORD)siTime && pclserver->sTime.wMinute %60 == 0 && pclserver->sTime.wSecond == 0)
		{
			// �ش� �ð��� ������ 
			SI32 sIMakeRaccoonNUM = GoonzuRaccoonEventData[siMakeRaccoon].GetMonsterNum()	; // �������� ���� ����
			// 0 ������ ����� ���� 
			if(sIMakeRaccoonNUM <= 0 || sIMakeRaccoonNUM > MAX_MONSTER_NUM_GOONZURACCOONEVENT )	return	;
			// ���������� ��ǥ �� ���� ���Ѵ� .
			if(GoonzuRaccoonEventData[siMakeRaccoon].GetRocX(0) <= 0 &&GoonzuRaccoonEventData[siMakeRaccoon].GetRocY(0) <= 0)	return	;
			Start();
			for (SI32 siMakeRaccoon_Map = 0 ; siMakeRaccoon_Map < MAX_GOONZU_KINGGURI_NUM; siMakeRaccoon_Map++)	// �ʺ��� ������ �ϴϱ�
			{// ������ ��ŭ �����				
				siMakeRaccoonCount++	;
				if ( siMakeRaccoonCount > sIMakeRaccoonNUM )	break	;	// ���� ���路 ����
				if(siMakeRaccoon_Map >= MAX_SELECTRFIELD_NUM_GOONZURACCOONEVENT )	break	;
				SI32 siMakeMapIndex = MAPINDEX_MAINFIELD;	// ���� �ʵ�� ���θʿ��� �ش� ��ǥ�� ���� 

				SI32 Kind = 0;
				if( (pclClient->siServiceArea == ConstServiceArea_Japan		||				pclClient->siServiceArea == ConstServiceArea_USA		||
					pclClient->siServiceArea == ConstServiceArea_Korea		||				pclClient->siServiceArea == ConstServiceArea_English	||
					pclClient->siServiceArea == ConstServiceArea_NHNChina	||				pclClient->siServiceArea == ConstServiceArea_EUROPE)	)
				{
					Kind = pclClient->GetUniqueFromHash(TEXT("KIND_BIGRACCOON"));
				}
				else if( pclClient->siServiceArea == ConstServiceArea_China )
				{
					Kind = pclClient->GetUniqueFromHash(TEXT("KIND_RACCOONCHINA"));
				}
				//----------------------------------------------------------------------------
				// ����Ʈ ��ǥ - �⺻ ��ǥ���� ������ ��ġ�� ã�´�.
				//----------------------------------------------------------------------------				
				SI32 tempX = GoonzuRaccoonEventData[siMakeRaccoon].GetRocX(siMakeRaccoon_Map)	;
				SI32 tempY = GoonzuRaccoonEventData[siMakeRaccoon].GetRocY(siMakeRaccoon_Map)	;
				if ( tempX <= 0 || tempY <= 0 )	continue	;	//��ǥ�� �������̸� �ǳʶڴ�.
				SI32 UseX	=	0	;
				SI32 UseY	=	0	;
				//----------------------------------------------------------------------------
				if( pclClient->pclMapManager->pclMapArray[siMakeMapIndex]->FindEmptyAreaForCharLocate(Kind, tempX, tempY, 10, &UseX, &UseY, true) == true )
				{
					if ( UseX <= 0 || UseY <= 0 )	continue	;	//��ǥ�� �������̸� �ǳʶڴ�.

					cltInnerStatusInfo clinnerstatus;
					clinnerstatus.clEnemyType.Set(ENEMYTYPE_ALLPC, 0);

					cltServer* pclserver = (cltServer*)pclClient;

					SI32 id = pclserver->SetNPCChar(Kind, VILLAGE_NONE, NULL, 1, 0, UseX, UseY, 0, NPCITEMMODE_NORMAL, &clinnerstatus );
					if(id)
					{
						m_siKingGuriID[siMakeRaccoon_Map] = id;	// ���� ������ ���̵� ���� 
						SI32 simapindex = GoonzuRaccoonEventData[siMakeRaccoon].GetRocIndex(siMakeRaccoon_Map)	;
						TCHAR* pMapname = GetTxtFromMgr(simapindex)	;
						if ( pMapname != NULL ) 
						{
							StringCchCopy( m_szSelectedAreaName[siMakeRaccoon_Map], 32, pMapname );	// ���̸� ���� 
						}
						m_siAreaIndex[siMakeRaccoon_Map] = siMakeMapIndex;	// ���ε��� ����
						// �ش� ��ǥ ���� 
						m_ptPosition[siMakeRaccoon_Map].x	=	UseX	;
						m_ptPosition[siMakeRaccoon_Map].y	=	UseY	;	

						cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[id];

						pclchar->siCharMode = CHARMODE_KINGGURI;

					}

				}
			}
			SendInfo( START, dwLeftClock );// ����� ���縸ŭ �˸���
		}
	}
	
}

void CGoonzuKingGuriEvent::SendInfo( SI32 Type, DWORD LeftTime, TCHAR* UserNmae )
{
	cltGameMsgResponse_KingGuriInfo clKingGuriInfo( Type, LeftTime, m_szSelectedAreaName, UserNmae, &m_ptPosition[0], &m_siAreaIndex[0]);
	cltMsg clMsg( GAMEMSG_RESPONSE_KINGGURIINFO, sizeof(clKingGuriInfo), (BYTE*)&clKingGuriInfo );

	SI32 index = 0;
	SI32 id = 0;
	while(id = pclClient->pclCM->GetCharOrder(index))
	{
		index++;

		// ������� �Ŀ��Ը� �����Ѵ�. 
		if( true == pclClient->pclCM->CR[id]->IsValidConnection() )
		{
			pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		}
	}
}

void CGoonzuKingGuriEvent::SetDieKingGuri( bool Flag, SI32 KingGuriID, SI32 UserID )
{
	for( SI32 i = 0; i < MAX_GOONZU_KINGGURI_NUM; ++i )
	{
		if( m_siKingGuriID[i] == KingGuriID )
		{
			if( false == m_bKilledKingGuri[i] )
			{
				m_bKilledKingGuri[i] = Flag;

				//[�߰� : Ȳ���� 2007. 11. 13. ��� �������� �׾ �ش� ���̵� ���ſ� ���̸�.]
				m_siKingGuriID[i]	 = 0;
				ZeroMemory(m_szSelectedAreaName[i], sizeof(m_szSelectedAreaName[i]));

				if( true == pclClient->pclCM->IsValidID(UserID) )		
				{
					TCHAR* userName = (TCHAR*)pclClient->pclCM->CR[UserID]->GetName();
					SendInfo( DIE_KINGGURI, 0, userName );
				}
			}
		}
	}

	// ���Ͱ� ��� �׾����� �̺�Ʈ ����.
	if(true == MonsterAllDie())
	{
		SendInfo( END, 0 );
	}
	// ���Ͱ� ��� ������ ������ ��ġ�� �ٽ� ����.
	else
	{
		//[�߰��� : Ȳ���� 2007. 11. 13 ��� �������� �׾ ��ġ�� ������.]
		DWORD leftClock = dwLeftClock - ( pclClient->CurrentClock - dwStartClock ); 
		SendInfo( ACTION, leftClock );
		dwLastInfoClock = pclClient->CurrentClock;
	}
}

bool CGoonzuKingGuriEvent::MonsterAllDie(void)
{
	// ���Ͱ� ������ �׾��°� �ƴѰ�?
	bool MonAllDie = true;
	for( SI32 i = 0; i < MAX_GOONZU_KINGGURI_NUM; ++i )
	{
		if(0 != m_siKingGuriID[i])	
		{
			MonAllDie = false;
			break;
		}
	}

	return MonAllDie;
}
SI32 CGoonzuKingGuriEvent::ChekData(cGoonzuRaccoonEventData* GoonzuRaccoonEventData)
{
	cltServer* pclserver = (cltServer*)pclClient;

	// 24�ð��� ������ �ʾҴ�.
	if(1 > DiffDate(&pclserver->sTime, &LsatsetTime))
	{
		return GOONZU_KINGGURI_NOTOVERTIME	;
	}
	SI32 siTime_1 =	GoonzuRaccoonEventData[GOONZU_KINGGURI_FIRSTTIME].GetTime()	;	//  �ð� 1
	SI32 siTime_2 =	GoonzuRaccoonEventData[GOONZU_KINGGURI_SECONDTIME].GetTime()	;	//	�ð� 2
	SI32 siTime_3 =	GoonzuRaccoonEventData[GOONZU_KINGGURI_THIRDTTIME].GetTime()	;	//	�ð� 3

	SI32 Mapindex_1	=	GoonzuRaccoonEventData[GOONZU_KINGGURI_FIRSTTIME].GetRocIndex(GOONZU_KINGGURI_FIRSTMAP);	// ù��°�� Ȯ�� �ϸ� �ȴ� -> ���̸��� �޾� �´� 
	SI32 Mapindex_2	=	GoonzuRaccoonEventData[GOONZU_KINGGURI_SECONDTIME].GetRocIndex(GOONZU_KINGGURI_FIRSTMAP);
	SI32 Mapindex_3	=	GoonzuRaccoonEventData[GOONZU_KINGGURI_THIRDTTIME].GetRocIndex(GOONZU_KINGGURI_FIRSTMAP);

	// �ּ��� ��Ÿ�Ӿ��� ������ �Ǿ��ִ°�
	if( Mapindex_1 <= 0  || Mapindex_2<= 0 ||Mapindex_3 <= 0 )
	{
		return GOONZU_KINGGURI_NOTENOUGHDATA	;
	}

	// ���� �ð��� �ֳ� üũ 
	if ( siTime_1 == siTime_2 || siTime_1 == siTime_3|| siTime_2 == siTime_3 ) 
	{
		return GOONZU_KINGGURI_SAMETIME	;
	}
	// ���� ��Ҹ� �����߳� üũ
	for ( SI32 siIndex = 0 ; siIndex < MAX_SELECTRFIELD_NUM_GOONZURACCOONEVENT; siIndex++ ) 
	{
		SI32 siMapindex_Slot1 = 0 ;
		SI32 siMapindex_Slot2 = 0 ;
		SI32 siMapindex_Slot3 = 0 ; 

		siMapindex_Slot1 = GoonzuRaccoonEventData[siIndex].GetRocIndex(GOONZU_KINGGURI_FIRSTMAP)	;
		siMapindex_Slot2 = GoonzuRaccoonEventData[siIndex].GetRocIndex(GOONZU_KINGGURI_SECONDMAP)	;
		siMapindex_Slot3 = GoonzuRaccoonEventData[siIndex].GetRocIndex(GOONZU_KINGGURI_THIRDTMAP)	;

		if(siMapindex_Slot1 != 0 && siMapindex_Slot2 != 0 && siMapindex_Slot3 != 0 )	// ��� 0�� �ƴҶ�
		{
			if (siMapindex_Slot1 == siMapindex_Slot2) 
			{
				return GOONZU_KINGGURI_SAMETIME	;
			}
			else if(siMapindex_Slot1 == siMapindex_Slot3)
			{
				return GOONZU_KINGGURI_SAMETIME	;
			}
			else if(siMapindex_Slot2 == siMapindex_Slot3)
			{
				return GOONZU_KINGGURI_SAMETIME	;
			}

		}
		else if( siMapindex_Slot1 != 0 && siMapindex_Slot2 != 0 )
		{
			if (siMapindex_Slot1 == siMapindex_Slot2) 
			{
				return GOONZU_KINGGURI_SAMETIME	;
			}

		}
	}


	// ��� �� ������ ��ŭ ������ ��ġ�� �����Ͽ��°� Ȯ��
	for (  SI32 Time_MonsterNumber = 0 ; Time_MonsterNumber < MAX_SELECTRFIELD_NUM_GOONZURACCOONEVENT; Time_MonsterNumber++) 
	{
		if(Time_MonsterNumber >= MAX_SELECTRFIELD_NUM_GOONZURACCOONEVENT)	continue	;
		if(Time_MonsterNumber < 0)	continue	;
		SI32 siMakeMonsterNumber = GoonzuRaccoonEventData[Time_MonsterNumber].m_siMakeMonsterNum	;
		switch( siMakeMonsterNumber ) 
		{
		case 1:
			{
				SI32 siMapindex = GoonzuRaccoonEventData[Time_MonsterNumber].GetRocIndex(GOONZU_KINGGURI_FIRSTMAP)	;
				SI32 siRocX = GoonzuRaccoonEventData[Time_MonsterNumber].GetRocX(GOONZU_KINGGURI_FIRSTMAP)	;
				SI32 siRocY = GoonzuRaccoonEventData[Time_MonsterNumber].GetRocY(GOONZU_KINGGURI_FIRSTMAP)	;
				if ( siMapindex <= 0 ) return	GOONZU_KINGGURI_NOTENOUGHDATA	;
				if ( siRocX <= 0 ) return	GOONZU_KINGGURI_NOTENOUGHDATA	;
				if ( siRocY <= 0 ) return	GOONZU_KINGGURI_NOTENOUGHDATA	;
				if (false == IsCorrectRoc( siMapindex ,siRocX, siRocY ) )
				{
					return	GOONZU_KINGGURI_NOTENOUGHDATA	;
				}

			}
			break;
		case 2:
			{
				for ( SI32 siindex = 0 ; siindex < siMakeMonsterNumber; siindex++) 
				{
					SI32 siMapindex = GoonzuRaccoonEventData[Time_MonsterNumber].GetRocIndex(siindex)	;
					SI32 siRocX = GoonzuRaccoonEventData[Time_MonsterNumber].GetRocX(siindex)	;
					SI32 siRocY = GoonzuRaccoonEventData[Time_MonsterNumber].GetRocY(siindex)	;
					if ( siMapindex <= 0 ) return	GOONZU_KINGGURI_NOTENOUGHDATA	;
					if ( siRocX <= 0 ) return	GOONZU_KINGGURI_NOTENOUGHDATA	;
					if ( siRocY <= 0 ) return	GOONZU_KINGGURI_NOTENOUGHDATA	;
					if (false == IsCorrectRoc( siMapindex ,siRocX, siRocY ) )
					{
						return	GOONZU_KINGGURI_NOTENOUGHDATA	;
					}
				}
				
			}
			break;
		case 3:
			{
				for ( SI32 siindex = 0 ; siindex < siMakeMonsterNumber; siindex++) 
				{
					SI32 siMapindex = GoonzuRaccoonEventData[Time_MonsterNumber].GetRocIndex(siindex)	;
					SI32 siRocX = GoonzuRaccoonEventData[Time_MonsterNumber].GetRocX(siindex)	;
					SI32 siRocY = GoonzuRaccoonEventData[Time_MonsterNumber].GetRocY(siindex)	;
					if ( siMapindex <= 0 ) return	GOONZU_KINGGURI_NOTENOUGHDATA	;
					if ( siRocX <= 0 ) return	GOONZU_KINGGURI_NOTENOUGHDATA	;
					if ( siRocY <= 0 ) return	GOONZU_KINGGURI_NOTENOUGHDATA	;
					if (false == IsCorrectRoc( siMapindex ,siRocX, siRocY ) )
					{
						return	GOONZU_KINGGURI_NOTENOUGHDATA	;
					}
				}
			}
			break;
		default:
			{
				return	GOONZU_KINGGURI_NOTENOUGHDATA	;
			}
		}
	}



	return GOONZU_KINGGURI_CORRECTDATA	;
}

void CGoonzuKingGuriEvent::LoadData()
{
	NDataLoader	dataloader;
	BOOL bLoadFile=FALSE;

	ZeroMemory(GoonzuRaccoonRocData,sizeof(GoonzuRaccoonRocData))	;
	//KHY - 0810 - �ؽ�Ʈ ���ҽ� ��ȣȭ.
	if( pclClient->IsWhereServiceArea( ConstSwitch_TextEncryption ) )
	{
		bLoadFile = dataloader.LoadDataFromCryptFile( TEXT("Data/KingGuriInfo.txt") );
	}
	else
	{
		bLoadFile = dataloader.LoadDataFromFile( TEXT("Data/KingGuriInfo.txt") );
	}

	if (!bLoadFile)
	{
		MsgBox( TEXT("Not LoadFromFile KingGuriInfo.txt"),TEXT("Error"));
		return;
	}

	SI32 TextNum	=	0	;	// �ؽ�Ʈ �Ŵ��� ��ȣ
	SI32 RocX	=	0	;
	SI32 RocY	=	0	;
	SI32 siCount	=	0	;

	NDataTypeInfo pDataTypeInfo[] =
	{
		NDATA_INT32,	&TextNum,	4,
			NDATA_INT32,	&RocX,	4,
			NDATA_INT32,	&RocY,	4,
			0,0,0
	};

	dataloader.RegDataType( pDataTypeInfo );

	while( !dataloader.IsEndOfData() ) {

		if( dataloader.ReadData() ) 
		{
			if(siCount >= MAX_DATA_MAP_NUM)	break	;
			if(TextNum <= 0)	continue	;
			GoonzuRaccoonRocData[siCount].SetRoc(TextNum,RocX,RocY)	;	// ���� ��ǥ�� ���� 
			siCount++;
		}
	}
}
bool CGoonzuKingGuriEvent::IsCorrectRoc( SI32 siMapname , SI32 X , SI32 y )
{
	if( siMapname <= 0 )	return	false ;
	if( X <= 0 )	return	false ;
	if( y <= 0 )	return	false ;
	for ( SI32 index = 0 ; index < MAX_DATA_MAP_NUM; index++) 
	{
		if(GoonzuRaccoonRocData[index].GetMapIndex() == siMapname && 
			GoonzuRaccoonRocData[index].GetX() == X && 
			GoonzuRaccoonRocData[index].GetY() == y)
		{
			return true	;
		}

	}

	return false	;
	
}