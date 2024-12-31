#include "KingGuri.h"

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

CKingGuriEvent::CKingGuriEvent() : cltEvent()
{
	SI32 i;
	for( i = 0; i < MAX_KINGGURI_NUM; ++i )
	{
		if ( i >= MAX_KINGGURI_NUM )	continue	;	// �迭�� �Ѿ�� ���������� �д´�� �ѱ��.	�ʱ�ȭ�� �� ���ݾ�.
		m_bKilledKingGuri[i] = false;
		m_siKingGuriID[i] = 0;
	}

	FILE* fp = fopen("ServerData\\KingGuri\\KingGuriInfo.txt", "rt");
	if(fp == NULL)
	{
		MessageBox( NULL, "KingGuri Failed", "KingGuri", MB_OK );
		return;
	}

	TCHAR buffer[256] = {'\0'};
	for( i = 0;i< 7;i++ )
	{
		fgets(buffer, 256, fp);
	}// �����Ϳ� ������� �κ��� �о� ���δ�.7�ٱ����� �ǹ� ���� ��ŸƮ��� �� �ǹ� ����

	SI32 count = 0;
	while( fgets( buffer, 256, fp ) != NULL )
	{
		if( _tcscmp( buffer, "<END>") == 0 )	// ���� �߿��� �κ� ���⿡ �����̽��ٳ� ���� ���� ���� ����� �ν� ���մϴ� .
		{
			break;
		}
		if ( count >= MAX_POSITION_NUM )	continue	;	// ���ҽ��� �߸��������� ����ؼ� �ƽ���ŭ �о� ������ ���̻� �迭�� ���� ���� �ʰ� ��Ƽ�� �ؼ� ������ Ŭ���� ��ŵ�ϴ�
		sscanf( buffer, "%s %d %d", m_szAreaName[count], &m_ptPosition[count].x, &m_ptPosition[count].y );
		count++;
	}

	fclose(fp);
}

CKingGuriEvent::~CKingGuriEvent()
{
}

void CKingGuriEvent::Init()
{
	for( SI32 i = 0; i < MAX_KINGGURI_NUM; ++i )
	{
		if ( i >= MAX_KINGGURI_NUM )	continue	;	// �迭�� �Ѿ�� ���������� �д´�� �ѱ��.	�ʱ�ȭ�� �� ���ݾ�.
		m_bKilledKingGuri[i] = false;
		m_siKingGuriID[i] = 0;
	}

	cltEvent::Init();
}

void CKingGuriEvent::Start()
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

void CKingGuriEvent::Action()
{
	if( pclClient->IsCountrySwitch( Switch_KingGuriEvent ) )
	{
		if( false == bEventSwitch )
		{
			cltServer* pclserver = (cltServer*)pclClient;

			//[�߰� : Ȳ���� 2007. 11. 13 �Ϻ��� ��� ������ �̺�Ʈ�� ������ �ߵ�]
			if( (pclClient->siServiceArea == ConstServiceArea_Japan	||
				pclClient->siServiceArea == ConstServiceArea_USA		)
				)
			{
				if(0 == (pclserver->sTime.wMinute%60))
				{
					MakeKingGuri();
					pclserver->pclLog->FileConfigPrint( "KingGuri", "Start" );
				}
			}
			// [����] 2008.01.14 �ѱ��� ����/���� 3,7,11 ���ÿ� �ߵ�(�Ϸ翡 �� 6�� �ߵ�)
			else if ( pclClient->siServiceArea == ConstServiceArea_Korea	||
				pclClient->siServiceArea == ConstServiceArea_English		||
				pclClient->siServiceArea == ConstServiceArea_NHNChina		||
				pclClient->siServiceArea == ConstServiceArea_EUROPE
				)
			{
				if ( ((pclserver->sTime.wHour == 3) || (pclserver->sTime.wHour == 7) || (pclserver->sTime.wHour == 11) 
					|| (pclserver->sTime.wHour == 15) || (pclserver->sTime.wHour == 19) || (pclserver->sTime.wHour == 23))
					&& (pclserver->sTime.wMinute == 0)
					)
				{
					MakeKingGuri();
					pclserver->pclLog->FileConfigPrint( "KingGuri", "Start" );
				}
			}
			else if( pclClient->siServiceArea == ConstServiceArea_China )
			{
				SI32 totalCount = (sizeof( KingGuriEventStartTime ) / sizeof( WORD )) / 2;

				for ( SI32 i = 0 ; i < totalCount ; ++i )
				{
					if( pclserver->sTime.wHour   == KingGuriEventStartTime[i*2]		&&
						pclserver->sTime.wMinute >= KingGuriEventStartTime[i*2+1]	&&
						pclserver->sTime.wMinute <= KingGuriEventStartTime[i*2+1] + 2 )
					{
						MakeKingGuri();
						pclserver->pclLog->FileConfigPrint( "KingGuri", "Start" );
					}
				}
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
					SendTime = 200000; // 3��20�ʸ���.
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

void CKingGuriEvent::End()
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


void CKingGuriEvent::MakeKingGuri()
{
	Start();

	// �ʹ�ȣ �ʱ���.
	m_siAreaIndex[0] = m_siAreaIndex[1] = m_siAreaIndex[2] = -1;

	// ���͸� ��ġ�� ������ ���� ã�´�. 
	SI32 count		  =  0;
	SI32 randValue	  =  0;
	SI32 oldRandValue = -1;
	bool created	  =  false;

	SI32 siSafeCount	=	0	;	// ���� ���� ���� ���� ���࿡ �̵����� �Ȱɸ��� ������ ����


	while( !created )
	{
		randValue = rand() % MAX_POSITION_NUM;

		int i = 0;
		for(	; i < MAX_KINGGURI_NUM; ++i)
		{
			if( randValue == m_siAreaIndex[i])	break;
		}

		if( randValue == oldRandValue || i != MAX_KINGGURI_NUM)	continue;
		if(randValue >= MAX_POSITION_NUM)	continue	;

		oldRandValue = randValue;

		SI32 Kind = 0;
		//[�߰� : Ȳ���� 2007. 11. 13 �Ϻ��� ��� ������ �̺�Ʈ�� ������ �ߵ�]
		if( (pclClient->siServiceArea == ConstServiceArea_Japan		||
			pclClient->siServiceArea == ConstServiceArea_USA		||
			pclClient->siServiceArea == ConstServiceArea_Korea		||
			pclClient->siServiceArea == ConstServiceArea_English	||
			pclClient->siServiceArea == ConstServiceArea_NHNChina	||
			pclClient->siServiceArea == ConstServiceArea_EUROPE
			)
			)
		{
			Kind = pclClient->GetUniqueFromHash(TEXT("KIND_BIGRACCOON"));
		}
		else if( pclClient->siServiceArea == ConstServiceArea_China )
		{
			Kind = pclClient->GetUniqueFromHash(TEXT("KIND_RACCOONCHINA"));
		}

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
				if(count >= MAX_KINGGURI_NUM) continue	;
				m_siKingGuriID[count] = id;
				StringCchCopy( m_szSelectedAreaName[count], 32, m_szAreaName[randValue] );

				//[�߰��� : Ȳ���� 2007. 11. 13 �� �ε��� ��ȣ.]
				m_siAreaIndex[count] = randValue;

				cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[id];

				pclchar->siCharMode = CHARMODE_KINGGURI;
				count++;

				if( count == MAX_KINGGURI_NUM )
					created = true;
			}
		}
		siSafeCount++;
		if( siSafeCount >= 10000)	break	;	// ���� ���� ���� ������ ���� 1������ ���Ƽ� �̰� ���ϸ� ���ѷ����� ���Ҵٰ� ���� �� �׳� ���� ��ȯ�ѳ𿡼� �Ѱ� �̰� ��¥ ���� ���ุ�� ���� �� ���� �ڵ�
	}


	SendInfo( START, dwLeftClock );
}

void CKingGuriEvent::SendInfo( SI32 Type, DWORD LeftTime, TCHAR* UserNmae )
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

void CKingGuriEvent::SetDieKingGuri( bool Flag, SI32 KingGuriID, SI32 UserID )
{
	for( SI32 i = 0; i < MAX_KINGGURI_NUM; ++i )
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

bool CKingGuriEvent::MonsterAllDie(void)
{
	// ���Ͱ� ������ �׾��°� �ƴѰ�?
	bool MonAllDie = true;
	for( SI32 i = 0; i < MAX_KINGGURI_NUM; ++i )
	{
		if(0 != m_siKingGuriID[i])	
		{
			MonAllDie = false;
			break;
		}
	}

	return MonAllDie;
}