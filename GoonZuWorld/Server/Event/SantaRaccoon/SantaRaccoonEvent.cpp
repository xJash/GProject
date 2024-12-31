#include "SantaRaccoonEvent.h"

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

CSantaRaccoon::CSantaRaccoon() : cltEvent()
{
	SI32 i;
	for( i = 0; i < MAX_SANTARACCOON_NUM; ++i )
	{
		if ( i >= MAX_SANTARACCOON_NUM )	continue	;	// 배열이 넘어서면 다음데이터 읽는대로 넘긴다.	초기화는 다 했잖아.
		m_bKilledSantaRaccoon[i] = false;
		m_siSantaRaccoonID[i] = 0;
	}

	// 대왕구리댁과 같은 곳에서 출현하므로 좌표정보는 구리댁 것을 이용한다.
	FILE* fp = fopen("ServerData\\KingGuri\\KingGuriInfo.txt", "rt");
	if(fp == NULL)
	{
		MessageBox( NULL, "SantaRaccoon Failed", "SantaRaccoon", MB_OK );
		return;
	}

	TCHAR buffer[256] = {'\0'};
	for( i = 0;i< 7;i++ )
	{
		fgets(buffer, 256, fp);
	}

	SI32 count = 0;
	while( fgets( buffer, 256, fp ) != NULL )
	{
		if( _tcscmp( buffer, "<END>") == 0 )
		{
			break;
		}
		if ( count >= MAX_SANTARACCOON_POSITION_NUM )	continue	;	// 리소스가 잘못들어갔을때를 대비해서 맥스만큼 읽어 댔으면 더이상 배열에 집어 넣지 않고 컨티뉴 해서 파일을 클로즈 시킵니다
		sscanf( buffer, "%s %d %d", m_szAreaName[count], &m_ptPosition[count].x, &m_ptPosition[count].y );
		count++;
	}

	fclose(fp);
}

CSantaRaccoon::~CSantaRaccoon()
{
}

void CSantaRaccoon::Init()
{
	for( SI32 i = 0; i < MAX_SANTARACCOON_NUM; ++i )
	{
		m_bKilledSantaRaccoon[i] = false;
		m_siSantaRaccoonID[i] = 0;
	}

	cltEvent::Init();
}

void CSantaRaccoon::Start()
{
	Init();

	bEventSwitch = true;

	dwLeftClock = 1000 * 60 * 50; 

	dwStartClock = pclClient->CurrentClock;
	dwLastInfoClock = pclClient->CurrentClock;
}	

void CSantaRaccoon::Action()						
{
	if( false == bEventSwitch )
	{
		cltServer* pclserver = (cltServer*)pclClient;

		if(0 == (pclserver->sTime.wMinute%60))
		{
			MakeSantaRaccoon();
			pclserver->pclLog->FileConfigPrint( "SantaRaccoon.txt", "Start" );
		}
	}
	else
	{
		if( pclClient->CurrentClock - dwStartClock > dwLeftClock )
		{
			End();
		}
		//[추가 : 황진성 2007. 11. 29 산타라쿤 몬스터가 다 죽었으면 이벤트 종료.]
		else if(true == MonsterAllDie())
		{
			End();
		}
		else
		{
			DWORD SendTime = 1000 * 60 * 3; //3분 20초

			// 전체유저에게 메세지 전송
			if( pclClient->CurrentClock - dwLastInfoClock > SendTime )
			{
				DWORD leftClock = dwLeftClock - ( pclClient->CurrentClock - dwStartClock ); 
				SendInfo( ACTION, leftClock );
				dwLastInfoClock = pclClient->CurrentClock;
			}
		}
	}
}

void CSantaRaccoon::End()
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

			if( pclchar->siCharMode == CHARMODE_SANTARACCOON )	
			{
				// 셀 내에서의 정보를 삭제한다. 
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


void CSantaRaccoon::MakeSantaRaccoon()
{
	Start();

	// 몬스터를 배치할 적절한 곳을 찾는다. 
	SI32 count = 0;
	SI32 randValue = 0;
	SI32 oldRandValue = -1;
	bool created = false;
	while( !created )
	{
	 	randValue = rand() % MAX_SANTARACCOON_POSITION_NUM;
		if( randValue == oldRandValue )
			continue;

		oldRandValue = randValue;

		SI32 Kind = pclClient->GetUniqueFromHash(TEXT("KIND_SANTARACCOON_ZIQ"));
		
		SI32 tempX = m_ptPosition[randValue].x; 
		SI32 tempY = m_ptPosition[randValue].y;

		SI32 x, y;
		if( pclClient->pclMapManager->pclMapArray[0]->FindEmptyAreaForCharLocate(Kind, tempX, tempY, 10, &x, &y, true) == true )
		{

			cltInnerStatusInfo clinnerstatus;
			clinnerstatus.clEnemyType.Set(ENEMYTYPE_ALLPC, 0);

			cltServer* pclserver = (cltServer*)pclClient;

			SI32 id = pclserver->SetNPCChar(Kind, VILLAGE_NONE, NULL, 1, 0, x, y, 0, NPCITEMMODE_NORMAL, &clinnerstatus );
			if(id)
			{
				m_siSantaRaccoonID[count] = id;
				if ( count >= MAX_SANTARACCOON_NUM)	continue	;
				StringCchCopy( m_szSelectedAreaName[count], 32, m_szAreaName[randValue] );

				//[추가 : 황진성 2007. 11. 29 맵 인덱스 번호.]
				m_siAreaIndex[count] = randValue;

				cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[id];

				pclchar->siCharMode = CHARMODE_SANTARACCOON;
				count++;

				if( count == MAX_SANTARACCOON_NUM )
					created = true;
			}
		}
	}


	SendInfo( START, dwLeftClock );
}

void CSantaRaccoon::SendInfo( SI32 Type, DWORD LeftTime, TCHAR* UserNmae )
{
	cltGameMsgResponse_SantaRaccoonInfo clSantaRaccoonInfo( Type, LeftTime, m_szSelectedAreaName, UserNmae, &m_ptPosition[0], &m_siAreaIndex[0]);
	cltMsg clMsg( GAMEMSG_RESPONSE_SANTARACCOONINFO, sizeof(clSantaRaccoonInfo), (BYTE*)&clSantaRaccoonInfo );

	SI32 index = 0;
	SI32 id = 0;
	while(id = pclClient->pclCM->GetCharOrder(index))
	{
		index++;

		// 사용자인 컴에게만 전달한다. 
		if( true == pclClient->pclCM->CR[id]->IsValidConnection() )
		{
			pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		}
	}
}

void CSantaRaccoon::SetDieSantaRaccoon( bool Flag, SI32 SantaRaccoonID, SI32 UserID )
{
	for( SI32 i = 0; i < MAX_SANTARACCOON_NUM; ++i )
	{
		if( m_siSantaRaccoonID[i] == SantaRaccoonID )
		{
			if( false == m_bKilledSantaRaccoon[i] )
			{
				m_bKilledSantaRaccoon[i] = Flag;

				//[추가 : 황진성 2007. 11. 13. 산타라쿤이 죽어서 해당 아이디 제거와 맵이름.]
				m_siSantaRaccoonID[i]	 = 0;
				ZeroMemory(m_szSelectedAreaName[i], sizeof(m_szSelectedAreaName[i]));

				if( true == pclClient->pclCM->IsValidID(UserID) )		
				{
					TCHAR* userName = (TCHAR*)pclClient->pclCM->CR[UserID]->GetName();
					SendInfo( DIE, 0, userName );
				}
			}
		}
	}

	// 몬스터가 모두 죽었으면 이벤트 종료.
	if(true == MonsterAllDie())
	{
		SendInfo( END, 0 );
	}
	// 몬스터가 살아 있으면 몬스터의 위치를 다시 공지.
	else
	{
		//[추가중 : 황진성 2007. 11. 13 산타라쿤이 죽어서 위치를 공지함.]
		DWORD leftClock = dwLeftClock - ( pclClient->CurrentClock - dwStartClock ); 
		SendInfo( ACTION, leftClock );
		dwLastInfoClock = pclClient->CurrentClock;
	}
}

bool CSantaRaccoon::MonsterAllDie(void)
{
	// 몬스터가 모조리 죽었는가 아닌가?
	bool MonAllDie = true;
	for( SI32 i = 0; i < MAX_SANTARACCOON_NUM; ++i )
	{
		if(0 != m_siSantaRaccoonID[i])	
		{
			MonAllDie = false;
			break;
		}
	}

	return MonAllDie;
}