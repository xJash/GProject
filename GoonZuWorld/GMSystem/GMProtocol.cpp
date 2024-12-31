#include "GMProtocol.h"
#include "GMMsg.h"
#include <atlstr.h>

#include "../Client/Client.h"
#include "../Server/Server.h"
#include "../Server/AuthServer/AuthMsg.h"

#include "../CommonLogic/House/House.h"
#include "../common/skill/Skill-Manager.h"


#include "../Common/Char/CharManager/CharManager.h"
#include "../Common/Char/CharServer/Char-Server.h"

#include "../CommonLogic/CommonLogic.h"
#include "../../Client/ninterface/ncharstatus/NCharPerson.h"
#include "../DBManager/GameDBManager_World/DBMsg-Log.h"

#include "../DBManager/GameDBManager_World/DBMsg-Person.h"

#include "GMProtocol_Updata.h"
#include "GMDefine.h"



extern cltCommonLogic* pclClient;


cGMClient::cGMClient()
{
	ZeroMemory( m_szAccountID, MAX_PLAYER_NAME );
	
	m_siMasterLevel = 0;
}

void cGMClient::SetAccount( TCHAR* pszAccountID, SI32 siMasterLevel )
{
	if ( pszAccountID != NULL )
	{
		StringCchCopy( m_szAccountID, MAX_PLAYER_NAME , pszAccountID );
	}
	
	if ( siMasterLevel >= 0 )
	{
		m_siMasterLevel = siMasterLevel;
	}
}

void cGMClient::Init()
{
	return;
}

void cGMClient::Close()
{
	SetAccount( TEXT(""), 0 );
}




//[�߰� : ��ų ���� ���ڿ� ���. Ȳ���� 2007.10.2]
TCHAR* SkillExplain(cltCharClient* _pclchar, SI32 _SkillUnique);

//[�߰� : ��ȯ�� ���ݷ°� ����. Ȳ���� 2007.9.21]
void SummonAttackAndDeffence(cltParametaBox &clPB, SI32 &totalMinDamage, SI32 &totalMaxDamage, SI32 &totalAC);

GMProtocol::GMProtocol()
{
	m_pSectionData = new GMSectionData( 200 * 1024 );
	m_pGMProtocol_Updata = new CGMProtocol_Updata;

	InitializeCriticalSection( &m_GMcs );
}

GMProtocol::~GMProtocol()
{
	DeleteCriticalSection( &m_GMcs );

	SAFE_DELETE( m_pSectionData );
	SAFE_DELETE( m_pGMProtocol_Updata );
}

void GMProtocol::GMLock()
{
	EnterCriticalSection( &m_GMcs );
}

void GMProtocol::GMUnlock()
{
	LeaveCriticalSection( &m_GMcs );
}

// �ʱ�ȭ
void GMProtocol::Init( UI16 usPort )
{
	m_SF.CreateFactory( GetSessionManager(), Const_Max_Account_Num, 300 * 1000, 300 * 1000 );

	GetNetIOCP()->CreateIOCP( GetSessionManager(), 1 );

	GetListen()->CreateListen( GetSessionManager(), usPort );

	SetFPS( 200 );

//	m_pCurrentSession = NULL;
	m_pCurrentPacket = NULL;
}

// ������Ʈ
void GMProtocol::Update()
{
}

// �޽��� ó�� �Լ�
void GMProtocol::SessionProc( ITZSession *pSession )
{
	if( pSession == NULL )			return;

	//cGMClient* pClient = (cGMClient*)pSession->GetPerson();
	//if ( pClient == NULL )			return;


//	m_pCurrentSession = pSession;
	
	// ���ۿ��� ��Ŷ�� �ϳ� �����´� 
	m_pCurrentPacket = (sPacketHeader *)( pSession->GetRecvBuffer()->GetFirstPacket() );
	if( m_pCurrentPacket == NULL )	return;	// ��Ŷ�� ������ ������

	GMLock();

	// ��Ŷ Ŀ�ǵ忡 ���� ó��
	switch( m_pCurrentPacket->usCmd ) 
	{
	case GMMSG_REQUEST_LOGIN:
		Do_GMMSG_REQUEST_LOGIN(pSession);
		break;

	case GMMSG_REQUEST_PAGE:
		Do_GMMSG_REQUEST_PAGE(pSession);
		break;

	case GMMSG_REQUEST_UPDATEDATA:
		Do_GMMSG_REQUEST_UPDATEDATA(pSession);
		break;

	case GMMSG_REQUEST_GMCOMMAND:
		Do_GMMSG_REQUEST_GMCOMMAND(pSession);
		break;
	}

	GMUnlock();

	pSession->GetRecvBuffer()->RemoveFirstPacket();
}

// ���� ���ǿ� ��Ŷ ������
void GMProtocol::SendPacket( ITZSession* pSession, sPacketHeader* pPacket )
{
	if( pSession  == NULL)										return;
	if( pSession->GetState() != SESSION_STATE_ESTABLISHED )		return;

	pSession->GetSendBuffer()->Write( (BYTE*)pPacket );
}

void GMProtocol::SendPacket( SI32 siCharID, sPacketHeader* pPacket )
{
	cGMClient* pclGMClient = m_SF.GetPerson(siCharID);
	if( pclGMClient == NULL )													return;
	if( pclGMClient->GetSession() != NULL &&
		pclGMClient->GetSession()->GetState() != SESSION_STATE_ESTABLISHED )	return;

	pclGMClient->GetSession()->GetSendBuffer()->Write( (BYTE*)pPacket );
}

// �α���
void GMProtocol::Do_GMMSG_REQUEST_LOGIN(ITZSession* pSession)
{
	// ���� �޽��� ó��
	sGMRequest_Login* pRecvMsg = (sGMRequest_Login*)m_pCurrentPacket;
	if ( pRecvMsg == NULL )			return;

	cltServer* pclserver = (cltServer*)pclClient;
	if ( pclserver == NULL )		return;
	
	sRequest_GMToolAuth clMsg;

	clMsg.packetHeader.usCmd = AUTHMSG_REQUEST_GMTOOLAUTH;
	clMsg.packetHeader.usSize = sizeof(clMsg);

	StringCchCopy(clMsg.userid, MAX_PLAYER_NAME, pRecvMsg->m_szID);
	clMsg.userid[ MAX_PLAYER_NAME - 1 ] = NULL;

	StringCchCopy(clMsg.userpw, MAX_PLAYER_NAME, pRecvMsg->m_szPW);
	clMsg.userpw[ MAX_PLAYER_NAME - 1 ] = NULL;

	clMsg.usCharID = pSession->GetPerson()->GetCharID();

	pclserver->pclFrontAuthProcess->SendMsg( (sPacketHeader*)&clMsg );
}

// ������ ��û
void GMProtocol::Do_GMMSG_REQUEST_PAGE(ITZSession* pSession)
{
	// ���� �޽��� ó��
	sGMRequest_Page* pRecvMsg = (sGMRequest_Page*)m_pCurrentPacket;
	if(pRecvMsg == NULL)					return;

	cltServer* pclserver = (cltServer*)pclClient;
	if(pclserver == NULL)					return;

	char charname[ 20 ];
	memcpy( charname, pRecvMsg->m_szCharName, 20 );
	charname[ 19 ] = NULL;

	char szResult[128] = { '\0', };
	char szReason[128] = { '\0', };

	printf( "�޽��� ���� : GMMSG_REQUEST_PAGE\n" );
	printf( "PageID : %d, CharName : %s\n", pRecvMsg->m_iPageID, charname );

	// ������ ���� �˸�
	sGMResponse_BeginPage beginmsg( pRecvMsg->m_iPageID, pRecvMsg->m_szCharName );
	SendPacket( pSession, (sPacketHeader*)&beginmsg ); 
	printf( "�޽��� ���� : GMMSG_RESPONSE_BEGINPAGE\n" );

	switch(pRecvMsg->m_iPageID)
	{
		case GMMSG_PAGEID_BASICINFO:
			{
				////////////////////////////////////////////////////////////////////////////////////////////////
				//
				//	����������
				//
				////////////////////////////////////////////////////////////////////////////////////////////////
				m_pSectionData->ClearData();
				////////////////////////////////////////////////////////////////////////////////////////////
				//  ������ 
				////////////////////////////////////////////////////////////////////////////////////////////

				_tcscpy(szResult, "Connected");
				_tcscpy(szReason, "Ok");

				m_pSectionData->BeginData( "show_result" );
				{
					m_pSectionData->AddDataStr( "result", szResult );
					m_pSectionData->AddDataStr( "reason", szReason );
				}
				m_pSectionData->EndData( "show_result" );

				m_pSectionData->BeginData( "info" );
				{
					m_pSectionData->AddDataInt( "ver", pclserver->GetVersion());//�ɸ��͸�
				}
				m_pSectionData->EndData( "info" );

				sGMResponse_Section sectionsbasiconfomsg( pRecvMsg->m_iPageID, pRecvMsg->m_szCharName, m_pSectionData );
				SendPacket( pSession, (sPacketHeader*)&sectionsbasiconfomsg ); 
			}
			break;

		case GMMSG_PAGEID_CHARINFO:
			{
				m_pSectionData->ClearData();

				////////////////////////////////////////////////////////////////////////////////////////////
				//  ������ 
				////////////////////////////////////////////////////////////////////////////////////////////
				m_pSectionData->BeginData( "charname_input" );
				{
					m_pSectionData->AddDataStr("charname", "" );
				}
				m_pSectionData->EndData( "charname_input" );

				m_pSectionData->BeginData( "show_result" ); // ���� ���
				{
					m_pSectionData->AddDataStr( "result", "Ready");
					m_pSectionData->AddDataStr( "reason", "...");
				}
				m_pSectionData->EndData( "show_result" );

/*				SI32	siCharID = pclserver->pclCM->GetIDFromName(charname);
				cltCharServer* pclchar = NULL;

				if(pclserver->pclCM->IsValidID(siCharID))
				{
					pclchar = (cltCharServer*)pclserver->pclCM->CR[siCharID];
				}
				if (pclchar == NULL)
				{
					SI32 siClientID = pSession->GetPerson()->GetCharID();
					sDBRequest_BasicInfoByName clMsg( siClientID, charname, GMMSG_PAGEID_CHARINFO );
					pclClient->SendDBMsg(DBSELECT_LETTER, (sPacketHeader *)&clMsg);
				}

				if(pclchar)
				{
					SI32 siPersonID = pclserver->pclCM->GetPersonIDFromName( charname );

					m_pSectionData->ClearData();
					////////////////////////////////////////////////////////////////////////////////////////////
					//  ������ 
					////////////////////////////////////////////////////////////////////////////////////////////
					m_pSectionData->BeginData( "show_result" );
						m_pSectionData->AddDataStr( "result", szResult );
						m_pSectionData->AddDataStr( "reason", szReason );
					m_pSectionData->EndData( "show_result" );


					//-----------------------------------------------------------------------------------------
					// ĳ���� ����
					//-----------------------------------------------------------------------------------------
					////////////////////////////////////////////////////////////////////////////////////////////
					//  �ɸ��� �⺻ ����
					////////////////////////////////////////////////////////////////////////////////////////////
					m_pSectionData->BeginData( "charbasic" );//�⺻����
						m_pSectionData->AddDataInt( "personid", pclserver->pclCM->GetPersonIDFromName( charname ) );
						m_pSectionData->AddDataStr( "name", (TCHAR*)pclchar->GetName());//�ɸ��͸�
						m_pSectionData->AddDataInt( "level", pclchar->pclCI->clIP.GetLevel() );//����
						m_pSectionData->AddDataFormat( "exp", "%d/%d", pclchar->pclCI->clIP.GetCurExp(), GetRequiredExpForLevel(pclchar->pclCI->clIP.GetLevel() + 1) );//����ġ
						m_pSectionData->AddDataFormat( "hp", "%d/%d", pclchar->pclCI->clIP.GetLife(), pclchar->clPB.GetMaxLife() );//hp
						m_pSectionData->AddDataFormat( "mp", "%d/%d", pclchar->pclCI->clIP.GetMana(),pclchar->clPB.GetMaxMana());//mp
						m_pSectionData->AddDataFormat( "fame", "%d/%d", pclchar->pclCI->clIP.siFameExp,  GetRequiredFameExpForLevel(pclchar->pclCI->clIP.siFameLevel + 1) );//�����
						m_pSectionData->AddDataInt( "helth", pclchar->pclCI->clHealthInfo.uiHealthPoint );//�ǰ�
					m_pSectionData->EndData( "charbasic" );                   

					////////////////////////////////////////////////////////////////////////////////////////////
					//  �ڻ� ������Ȳ
					////////////////////////////////////////////////////////////////////////////////////////////
					m_pSectionData->BeginData( "charasset" );
						m_pSectionData->AddDataInt( "money", pclchar->pclCI->clIP.GetMoney() );				// ������
						m_pSectionData->AddDataInt( "bank", pclchar->pclCI->clBank.GetMoney() );			// ����
						m_pSectionData->AddDataInt( "acu", pclchar->pclCI->clWorldMoney.GetWorldMoney() );	// ��ť
					m_pSectionData->EndData( "charasset" );

					// �ڻ� ������Ȳ ���� ����
					m_pSectionData->BeginData( "charasset_modify" );//�ڻ����� ���� ����
						m_pSectionData->AddDataInt( "personid", siPersonID );
					m_pSectionData->EndData( "charasset_modify" );

					////////////////////////////////////////////////////////////////////////////////////////////
					//  �ɸ��� �������ͽ�
					////////////////////////////////////////////////////////////////////////////////////////////
					m_pSectionData->BeginData( "status" );
						m_pSectionData->AddDataInt( "str", pclchar->pclCI->clIP.GetStr() );		// ��
						m_pSectionData->AddDataInt( "agi", pclchar->pclCI->clIP.GetDex() );		// ���߷�
						m_pSectionData->AddDataInt( "wis", pclchar->pclCI->clIP.GetMag() );		// ����
						m_pSectionData->AddDataInt( "vit", pclchar->pclCI->clIP.GetVit() );		// ����Ż
						m_pSectionData->AddDataInt( "dex", pclchar->pclCI->clIP.GetHnd() );		// ������
						m_pSectionData->AddDataInt( "luck", pclchar->pclCI->clIP.GetLuk() );	// ���
						m_pSectionData->AddDataInt( "bonus", pclchar->pclCI->clIP.GetBonus() );	// ���Ⱥ��ʽ�
						m_pSectionData->AddDataInt( "speed", pclchar->clPB.TotalMoveSpeed);		// �̵��ӵ�
					//m_pSectionData->AddDataFormat( "attack", "%d/%d"
					//	,GetTotalMinDamage(pclchar->clPB,pclchar->pclCI->clCharItem.GetEquipSet(EQUIPSET_PERSON),pclchar->ActiveWeapon)
					//	,GetTotalMaxDamage(pclchar->clPB,pclchar->pclCI->clCharItem.GetEquipSet(EQUIPSET_PERSON),pclchar->ActiveWeapon));//���ݷ�
					m_pSectionData->EndData( "status" );

					m_pSectionData->BeginData( "status_modify" );//�⺻���� ���� ����
						m_pSectionData->AddDataInt( "personid", siPersonID );
					m_pSectionData->EndData( "status_modify" );

					////////////////////////////////////////////////////////////////////////////////////////////
					//  �ֽ� ���� 
					////////////////////////////////////////////////////////////////////////////////////////////
					m_pSectionData->BeginData( "stockinfo" );

					for (int nNumber=1; nNumber<=42; nNumber++)
					{
						m_pSectionData->BeginData( "village" );
							m_pSectionData->AddDataInt( "villageunique", nNumber );
							m_pSectionData->AddDataStr( "villagename", pclClient->pclVillageManager->GetName(nNumber) );
							m_pSectionData->AddDataInt( "stocknum", pclchar->pclCI->clStock.clInfo.GetStockAmount(nNumber) );
						m_pSectionData->EndData( "village" );
					}
					m_pSectionData->EndData( "stockinfo" );

					// �ֽ� ���� ����
					m_pSectionData->BeginData( "stock_modify" );
						m_pSectionData->AddDataInt( "personid", siPersonID );
					m_pSectionData->EndData( "stock_modify" );


					////////////////////////////////////////////////////////////////////////////////////////////
					//  ���� ���� 
					////////////////////////////////////////////////////////////////////////////////////////////
					char	szBufName[][64]		= { 
						"ATTACKUP",					// ���ݷ� ��
							"DEFENSEUP",				// ���� ��
							"SPEEDUP",					// �ӵ� ��
							"BUF_MAKEEXPUP",			// ���� ����ġ ��
							"BUF_NOFIRSTATTACK",		// ���� ����
							"SUMMONATACUP",				// ��ȯ�� ���ݷ� ��
							"LOVEPOWER",				// ��� ����
							"FRIENDSHIP",				// ���� ����
							"HINAMOCHI",				// ??
							"SUCCESS_MANUFACTURE",		// ���� ����
							"MOFUMOFU_PERFUME",			// ���ĸ��� �����̾�
							"FOURLEAF",					// ����Ŭ�ι�
							"PREMIUMEXPUP",				// �����̾� ����ġ ��
							"HAPPYBEAN",				// ���� �� ��
							"NOTBONUSTIME_MAKEEXPUP",	// �������ʽ� Ÿ�ӿ� ��ø���� �ʴ´�.
							"ATTACKUP30",				// ������ ������ 30�ϰ�
							"DEFENSEUP30",				// ���� ������ 30�ϰ�
							"SUPEREXPUP",				// ���� EXP UP
							"THANKSGIVING_DAY"			// �߼�������
					};

					SI32	siBufNameCount	= sizeof(szBufName)/sizeof(char)/64;
					stBuf*	pstBuf			= NULL;
					TCHAR*	pText			= GetTxtFromMgr(7599);


					m_pSectionData->BeginData( "BufStatus" );

					for (SI32 siBufType=1; siBufType<siBufNameCount; siBufType++)
					{
						m_pSectionData->BeginData( "buf" );

						// ������ �߰��ߴµ� �̸��� �߰� ���������� ����ؼ� ���� �˻�
						if ( siBufNameCount > (siBufType-1) )
						{
							m_pSectionData->AddDataStr( "bufname",  szBufName[siBufType-1]  );
						}
						else
						{
							m_pSectionData->AddDataStr( "bufname", "Do Not Define Buf Name" );
							m_pSectionData->EndData( "buf" );

							continue;
						}

						m_pSectionData->AddDataInt( "bufnumber", siBufType );

						pstBuf = pclClient->pclCM->CR[siCharID]->pclCI->clBI.clBufInfo.GetBuf( siBufType );

						// �ش� ������ ��� ���̶��
						if( pstBuf != NULL )
						{
							TCHAR		tszTimeBuf[128]	= TEXT("");
							cltDate		cldate;
							SI16		siBufSlot		= -1;


							cldate.MakeFullDateFromDateVary( pstBuf->siOverTime );
							cldate.GetDateText( tszTimeBuf );

							// ���� Ÿ���� ���� ���� ��ȣ ã��
							siBufSlot = pclClient->pclCM->CR[siCharID]->pclCI->clBI.clBufInfo.FindBufSlot( siBufType );

							m_pSectionData->AddDataInt( "bufslot", siBufSlot );
							m_pSectionData->AddDataStr( "bufremain", tszTimeBuf );
						}
						else 
						{
							m_pSectionData->AddDataStr( "bufslot",  "NULL" );
							m_pSectionData->AddDataStr( "bufremain", "Don't Used");
						}

						pstBuf = NULL;

						m_pSectionData->EndData( "buf" );
					}

					//stBuf* pBuf19 = pclClient->pclCM->CR[siCharID]->pclCI->clBI.clBufInfo.GetBuf(BUF_FARMINGNMININGFOREVER);
					//if( pBuf18 != NULL )
					//{
					//	TCHAR timeBuf[512]=TEXT("");
					//	TCHAR warpbuf[2048]=TEXT("");
					//	cltBufInfo clBuf;
					//	clBuf.SetBuf( &pclchar->pclCI->clBI.clBufInfo );
					//	cltDate cldate;
					//	cldate.MakeFullHourFromHourVary(pBuf18->siOverTime);
					//	cldate.GetDateText(timeBuf);
					//	TCHAR* pText = GetTxtFromMgr(7599);
					//	StringCchPrintf(warpbuf, 2048, pText,timeBuf);
					//	m_pSectionData->AddDataStr( "BUF_FARMINGNMININGFOREVER",warpbuf);//������ �ڷ���Ʈ �Ⱓ.,
					//}
					//else {
					//	m_pSectionData->AddDataStr( "BUF_FARMINGNMININGFOREVER","Don't Used");

					//}		
					

					m_pSectionData->EndData( "BufStatus" );

					// ���� ���� ����
					m_pSectionData->BeginData( "buf_modify" );
						m_pSectionData->AddDataInt( "personid", siPersonID );
					m_pSectionData->EndData( "buf_modify" );*/

					sGMResponse_Section sectionsbasiconfomsg( pRecvMsg->m_iPageID, pRecvMsg->m_szCharName, m_pSectionData );
					SendPacket( pSession, (sPacketHeader*)&sectionsbasiconfomsg ); 
			
			}
			break;

		case GMMSG_PAGEID_ANIMAL:
			{
				/////////////////////////////////////////////////////////////////////////////////////////////////
				//
				//Ż��
				//
				////////////////////////////////////////////////////////////////////////////////////////////////

				SI32	siCharID = pclserver->pclCM->GetIDFromName(charname);
				cltCharServer* pclchar = NULL;				
				if(pclserver->pclCM->IsValidID(siCharID))
				{
					pclchar = (cltCharServer*)pclserver->pclCM->CR[siCharID];

				}
				if (pclchar == NULL) {

					SI32 siClientID = pSession->GetPerson()->GetCharID();
					sDBRequest_AnimalByName clMsg( siClientID, charname, GMMSG_PAGEID_ANIMAL );
					pclClient->SendDBMsg(DBSELECT_LETTER, (sPacketHeader *)&clMsg);
				}
				if(pclchar)
				{
					SI32 siPersonID = pclserver->pclCM->GetPersonIDFromName( charname );

					cltClient* pclclient = (cltClient*)pclClient;				
					cltHorse* pHorse1 = pclserver->pclCM->CR[siCharID]->pclCI->clHorseInfo.GetHorse(0);	
					cltHorse* pHorse2 = pclserver->pclCM->CR[siCharID]->pclCI->clHorseInfo.GetHorse(1);	
					cltHorse* pHorse3 = pclserver->pclCM->CR[siCharID]->pclCI->clHorseInfo.GetHorse(2);	
					cltHorse* pHorse4 = pclserver->pclCM->CR[siCharID]->pclCI->clHorseInfo.GetHorse(3);	
					cltHorse* pHorse5 = pclserver->pclCM->CR[siCharID]->pclCI->clHorseInfo.GetHorse(4);	

					////////////////////////////////////////////////////////////////////////////////////////////
					//  ������ 
					////////////////////////////////////////////////////////////////////////////////////////////
					m_pSectionData->ClearData();

					m_pSectionData->BeginData( "show_result" );
						m_pSectionData->AddDataStr( "result", szResult );
						m_pSectionData->AddDataStr( "reason", szReason );
					m_pSectionData->EndData( "show_result" );                   

					if (pHorse1) {
						SI32 datevary = pclserver->pclTime->clDate.GetDateVary();	
						SI32 horseunique = pHorse1->siHorseUnique;
						SI32 lifespan = pclclient->pclHorseManager->GetLife(pHorse1, datevary);
						SI32 HorseBirthYear= pHorse1->clBirthDate.uiYear;
						SI32 HorseBirthMonth= pHorse1->clBirthDate.uiMonth;
						SI32 HorseBirthDay= pHorse1->clBirthDate.uiDay;
						SI32 HorseBirthHour= pHorse1->clBirthDate.uiHour;
						TCHAR* horsetype = pclClient->pclHorseManager->pclHorseTypeInfo[horseunique]->szSpecies;
						SI32 HorseSex = pHorse1->siSex;

						
						m_pSectionData->BeginData( "animalbasic" );
						m_pSectionData->AddDataStr( "animalname",pHorse1->szName);
						if (horseunique == 0) {
							m_pSectionData->AddDataStr( "animaltype","No Horse");
						}
						else{
							m_pSectionData->AddDataStr( "animaltype",horsetype);

						}
						m_pSectionData->AddDataFormat( "animalbirth", "Y:%d M:%d D:%dth H:%d"
							,HorseBirthYear, HorseBirthMonth,HorseBirthDay,HorseBirthHour );
						m_pSectionData->AddDataInt( "anumallifespan",lifespan);                        
						m_pSectionData->AddDataInt( "animalage", pHorse1->GetAge(datevary) );
						if (HorseSex == 1) {m_pSectionData->AddDataStr( "animalgender", "Female" );}
						else{m_pSectionData->AddDataStr( "animalgender", "Male" );}
						m_pSectionData->EndData( "animalbasic" );

						m_pSectionData->BeginData( "anmalstatusinfo" );
						m_pSectionData->AddDatafloat( "animalspeed",pHorse1->siMoveSpeed/100);
						m_pSectionData->AddDatafloat( "animalstr",pHorse1->siStr/100 );
						m_pSectionData->AddDatafloat( "animalagi",pHorse1->siDex/100 );
						m_pSectionData->AddDatafloat( "animalwis",pHorse1->siMag/100 );
						m_pSectionData->AddDatafloat( "animalbonus",pHorse1->siStatusBonus );
						m_pSectionData->EndData( "anmalstatusinfo" );
					}
					if (pHorse2) {
						SI32 datevary = pclserver->pclTime->clDate.GetDateVary();	
						SI32 horseunique = pHorse2->siHorseUnique;
						SI32 lifespan = pclclient->pclHorseManager->GetLife(pHorse2, datevary);
						SI32 HorseBirthYear= pHorse2->clBirthDate.uiYear;
						SI32 HorseBirthMonth= pHorse2->clBirthDate.uiMonth;
						SI32 HorseBirthDay= pHorse2->clBirthDate.uiDay;
						SI32 HorseBirthHour= pHorse2->clBirthDate.uiHour;
						TCHAR* horsetype = pclClient->pclHorseManager->pclHorseTypeInfo[horseunique]->szSpecies;
						SI32 HorseSex = pHorse2->siSex;

						m_pSectionData->BeginData( "animalbasic1" );
						m_pSectionData->AddDataStr( "animalname1",pHorse2->szName);
						if (horseunique == 0) {
							m_pSectionData->AddDataStr( "animaltype1","No Horse");
						}
						else{
							m_pSectionData->AddDataStr( "animaltype1",horsetype);

						}
						m_pSectionData->AddDataFormat( "animalbirth1", "Y:%d M:%d D:%dth H:%d"
							,HorseBirthYear, HorseBirthMonth,HorseBirthDay,HorseBirthHour );
						m_pSectionData->AddDataInt( "anumallifespan1",lifespan);                        
						m_pSectionData->AddDataInt( "animalage1", pHorse2->GetAge(datevary) );
						if (HorseSex == 1) {m_pSectionData->AddDataStr( "animalgender1", "Female" );}
						else{m_pSectionData->AddDataStr( "animalgender1", "Male" );}
						m_pSectionData->EndData( "animalbasic1" );

						m_pSectionData->BeginData( "anmalstatusinfo1" );
						m_pSectionData->AddDatafloat( "animalspeed1",pHorse2->siMoveSpeed/100);
						m_pSectionData->AddDatafloat( "animalstr1",pHorse2->siStr/100 );
						m_pSectionData->AddDatafloat( "animalagi1",pHorse2->siDex/100 );
						m_pSectionData->AddDatafloat( "animalwis1",pHorse2->siMag/100 );
						m_pSectionData->AddDatafloat( "animalbonus1",pHorse2->siStatusBonus );
						m_pSectionData->EndData( "anmalstatusinfo1" );
					}
					if (pHorse3) {
						SI32 datevary = pclserver->pclTime->clDate.GetDateVary();	
						SI32 horseunique = pHorse3->siHorseUnique;
						SI32 lifespan = pclclient->pclHorseManager->GetLife(pHorse3, datevary);
						SI32 HorseBirthYear= pHorse3->clBirthDate.uiYear;
						SI32 HorseBirthMonth= pHorse3->clBirthDate.uiMonth;
						SI32 HorseBirthDay= pHorse3->clBirthDate.uiDay;
						SI32 HorseBirthHour= pHorse3->clBirthDate.uiHour;
						TCHAR* horsetype = pclClient->pclHorseManager->pclHorseTypeInfo[horseunique]->szSpecies;
						SI32 HorseSex = pHorse3->siSex;

						m_pSectionData->BeginData( "animalbasic2" );
						m_pSectionData->AddDataStr( "animalname2",pHorse3->szName);
						if (horseunique == 0) {
							m_pSectionData->AddDataStr( "animaltype2","No Horse");
						}
						else{
							m_pSectionData->AddDataStr( "animaltype2",horsetype);

						}
						m_pSectionData->AddDataFormat( "animalbirth2", "Y:%d M:%d D:%dth H:%d"
							,HorseBirthYear, HorseBirthMonth,HorseBirthDay,HorseBirthHour );
						m_pSectionData->AddDataInt( "anumallifespan2",lifespan);                        
						m_pSectionData->AddDataInt( "animalage2", pHorse3->GetAge(datevary) );
						if (HorseSex == 1) {m_pSectionData->AddDataStr( "animalgender3", "Female" );}
						else{m_pSectionData->AddDataStr( "animalgender2", "Male" );}
						m_pSectionData->EndData( "animalbasic2" );

						m_pSectionData->BeginData( "anmalstatusinfo2" );
						m_pSectionData->AddDatafloat( "animalspeed2",pHorse3->siMoveSpeed/100);
						m_pSectionData->AddDatafloat( "animalstr2",pHorse3->siStr/100 );
						m_pSectionData->AddDatafloat( "animalagi2",pHorse3->siDex/100 );
						m_pSectionData->AddDatafloat( "animalwis2",pHorse3->siMag/100 );
						m_pSectionData->AddDatafloat( "animalbonus2",pHorse3->siStatusBonus );
						m_pSectionData->EndData( "anmalstatusinfo2" );
					}
					if (pHorse4) {
						SI32 datevary = pclserver->pclTime->clDate.GetDateVary();	
						SI32 horseunique = pHorse4->siHorseUnique;
						SI32 lifespan = pclclient->pclHorseManager->GetLife(pHorse4, datevary);
						SI32 HorseBirthYear= pHorse4->clBirthDate.uiYear;
						SI32 HorseBirthMonth= pHorse4->clBirthDate.uiMonth;
						SI32 HorseBirthDay= pHorse4->clBirthDate.uiDay;
						SI32 HorseBirthHour= pHorse4->clBirthDate.uiHour;
						TCHAR* horsetype = pclClient->pclHorseManager->pclHorseTypeInfo[horseunique]->szSpecies;
						SI32 HorseSex = pHorse4->siSex;

						m_pSectionData->BeginData( "animalbasic3" );
						m_pSectionData->AddDataStr( "animalname3",pHorse4->szName);
						if (horseunique == 0) {
							m_pSectionData->AddDataStr( "animaltype3","No Horse");
						}
						else{
							m_pSectionData->AddDataStr( "animaltype3",horsetype);

						}
						m_pSectionData->AddDataFormat( "animalbirth3", "Y:%d M:%d D:%dth H:%d"
							,HorseBirthYear, HorseBirthMonth,HorseBirthDay,HorseBirthHour );
						m_pSectionData->AddDataInt( "anumallifespan3",lifespan);                        
						m_pSectionData->AddDataInt( "animalage3", pHorse4->GetAge(datevary) );
						if (HorseSex == 1) {m_pSectionData->AddDataStr( "animalgender3", "Female" );}
						else{m_pSectionData->AddDataStr( "animalgender3", "Male" );}
						m_pSectionData->EndData( "animalbasic3" );

						m_pSectionData->BeginData( "anmalstatusinfo3" );
						m_pSectionData->AddDatafloat( "animalspeed3",pHorse4->siMoveSpeed/100);
						m_pSectionData->AddDatafloat( "animalstr3",pHorse4->siStr/100 );
						m_pSectionData->AddDatafloat( "animalagi3",pHorse4->siDex/100 );
						m_pSectionData->AddDatafloat( "animalwis3",pHorse4->siMag/100 );
						m_pSectionData->AddDatafloat( "animalbonus3",pHorse4->siStatusBonus );
						m_pSectionData->EndData( "anmalstatusinfo3" );
					}
					if (pHorse5) {
						SI32 datevary = pclserver->pclTime->clDate.GetDateVary();	
						SI32 horseunique = pHorse5->siHorseUnique;
						SI32 lifespan = pclclient->pclHorseManager->GetLife(pHorse5, datevary);
						SI32 HorseBirthYear= pHorse5->clBirthDate.uiYear;
						SI32 HorseBirthMonth= pHorse5->clBirthDate.uiMonth;
						SI32 HorseBirthDay= pHorse5->clBirthDate.uiDay;
						SI32 HorseBirthHour= pHorse5->clBirthDate.uiHour;
						TCHAR* horsetype = pclClient->pclHorseManager->pclHorseTypeInfo[horseunique]->szSpecies;
						SI32 HorseSex = pHorse5->siSex;

						m_pSectionData->BeginData( "animalbasic4" );
						m_pSectionData->AddDataStr( "animalname4",pHorse5->szName);
						if (horseunique == 0) {
							m_pSectionData->AddDataStr( "animaltype4","No Horse");
						}
						else{
							m_pSectionData->AddDataStr( "animaltype4",horsetype);

						}
						m_pSectionData->AddDataFormat( "animalbirth4", "Y:%d M:%d D:%dth H:%d"
							,HorseBirthYear, HorseBirthMonth,HorseBirthDay,HorseBirthHour );
						m_pSectionData->AddDataInt( "anumallifespan4",lifespan);                        
						m_pSectionData->AddDataInt( "animalage4", pHorse5->GetAge(datevary) );
						if (HorseSex == 1) {m_pSectionData->AddDataStr( "animalgender4", "Female" );}
						else{m_pSectionData->AddDataStr( "animalgender4", "Male" );}
						m_pSectionData->EndData( "animalbasic4" );

						m_pSectionData->BeginData( "anmalstatusinfo4" );
						m_pSectionData->AddDatafloat( "animalspeed4",pHorse5->siMoveSpeed/100);
						m_pSectionData->AddDatafloat( "animalstr4",pHorse5->siStr/100 );
						m_pSectionData->AddDatafloat( "animalagi4",pHorse5->siDex/100 );
						m_pSectionData->AddDatafloat( "animalwis4",pHorse5->siMag/100 );
						m_pSectionData->AddDatafloat( "animalbonus4",pHorse5->siStatusBonus );
						m_pSectionData->EndData( "anmalstatusinfo4" );
					}

					// Ż�� �������� ����
					m_pSectionData->BeginData( "animal_add" );
						m_pSectionData->AddDataInt( "personid", siPersonID );
					m_pSectionData->EndData( "animal_add" );

					sGMResponse_Section sectionmsg( pRecvMsg->m_iPageID, pRecvMsg->m_szCharName, m_pSectionData );
					SendPacket( pSession, (sPacketHeader*)&sectionmsg ); 
				}
			}break;



		case GMMSG_PAGEID_INVENTORY	:
			{

				///////////////////////////////////////////////////////////////////////////////////////////////
				//	�κ��丮
				//////////////////////////////////////////////////////////////////////////////////////////////
				SI32	siCharID = pclserver->pclCM->GetIDFromName(charname);

				cltCharServer* pclchar = NULL;


				if(pclserver->pclCM->IsValidID(siCharID))
				{
					pclchar = (cltCharServer*)pclserver->pclCM->CR[siCharID];
				}

				if (pclchar == NULL) {
					SI32 siClientID = pSession->GetPerson()->GetCharID();
					sDBRequest_InventoryByName clMsg( siClientID, charname, GMMSG_PAGEID_INVENTORY );
					pclClient->SendDBMsg(DBSELECT_LETTER, (sPacketHeader *)&clMsg);
				}

				if(pclchar)
				{                
					SI32 siPersonID = pclserver->pclCM->GetPersonIDFromName( charname );

					cltClient *pclclient = ( cltClient * )pclClient;
					
					////////////////////////////////////////////////���� ���� �̸�////////////////////////////////////////////////////////
					TCHAR* pItemName1 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[2].siUnique);
					TCHAR* pItemName2 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[8].siUnique);
					TCHAR* pItemName3
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[0].siUnique);
					TCHAR* pItemName4
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[1].siUnique);
					TCHAR* pItemName5 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[3].siUnique);
					TCHAR* pItemName6 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[4].siUnique);
					TCHAR* pItemName7 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[5].siUnique);
					TCHAR* pItemName8
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[6].siUnique);
					TCHAR* pItemName9 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[7].siUnique);
					TCHAR* pItemName10 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[9].siUnique);
					TCHAR* pItemName11 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[11].siUnique);
					TCHAR* pItemName12 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[12].siUnique);
					TCHAR* pItemName13 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[10].siUnique);
					TCHAR* pItemName14 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[13].siUnique);
					TCHAR* pItemName15 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[14].siUnique);
					//�ɸ����κ��丮
					TCHAR* pInvName1 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[15].siUnique);
					TCHAR* pInvName2 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[16].siUnique);
					TCHAR* pInvName3 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[17].siUnique);
					TCHAR* pInvName4 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[18].siUnique);
					TCHAR* pInvName5 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[19].siUnique);
					TCHAR* pInvName6 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[20].siUnique);
					TCHAR* pInvName7 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[21].siUnique);
					TCHAR* pInvName8 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[22].siUnique);
					TCHAR* pInvName9 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[23].siUnique);
					TCHAR* pInvName10 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[24].siUnique);
					//�ɸ��� �κ��丮 2
					TCHAR* pInvName11 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[25].siUnique);
					TCHAR* pInvName12 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[26].siUnique);
					TCHAR* pInvName13 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[27].siUnique);
					TCHAR* pInvName14 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[28].siUnique);
					TCHAR* pInvName15 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[29].siUnique);
					TCHAR* pInvName16 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[30].siUnique);
					TCHAR* pInvName17 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[31].siUnique);
					TCHAR* pInvName18 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[32].siUnique);
					TCHAR* pInvName19 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[33].siUnique);
					TCHAR* pInvName20 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[34].siUnique);
					//�����κ��丮.
					TCHAR* pInvName21 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[35].siUnique);
					TCHAR* pInvName22
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[36].siUnique);
					TCHAR* pInvName23 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[37].siUnique);
					TCHAR* pInvName24 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[38].siUnique);
					TCHAR* pInvName25 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[39].siUnique);
					TCHAR* pInvName26 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[40].siUnique);
					TCHAR* pInvName27 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[41].siUnique);
					TCHAR* pInvName28 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[42].siUnique);
					TCHAR* pInvName29 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[43].siUnique);
					TCHAR* pInvName30 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[44].siUnique);
					//�����κ��丮2
					TCHAR* pInvName31 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[45].siUnique);
					TCHAR* pInvName32
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[46].siUnique);
					TCHAR* pInvName33 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[47].siUnique);
					TCHAR* pInvName34
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[48].siUnique);
					TCHAR* pInvName35
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[49].siUnique);
					TCHAR* pInvName36 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[50].siUnique);
					TCHAR* pInvName37 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[51].siUnique);
					TCHAR* pInvName38 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[52].siUnique);
					TCHAR* pInvName39 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[53].siUnique);
					TCHAR* pInvName40 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[54].siUnique);
					//����1
					TCHAR* pInvName41 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[55].siUnique);
					TCHAR* pInvName42 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[56].siUnique);
					TCHAR* pInvName43 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[57].siUnique);
					TCHAR* pInvName44 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[58].siUnique);
					TCHAR* pInvName45 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[59].siUnique);
					TCHAR* pInvName46 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[60].siUnique);
					TCHAR* pInvName47 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[61].siUnique);
					TCHAR* pInvName48 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[62].siUnique);
					TCHAR* pInvName49 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[63].siUnique);
					TCHAR* pInvName50 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[64].siUnique);
					TCHAR* pInvName51 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[65].siUnique);
					TCHAR* pInvName52 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[66].siUnique);
					//����2
					TCHAR* pInvName53 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[67].siUnique);
					TCHAR* pInvName54 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[68].siUnique);
					TCHAR* pInvName55 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[69].siUnique);
					TCHAR* pInvName56 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[70].siUnique);
					TCHAR* pInvName57 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[71].siUnique);
					TCHAR* pInvName58 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[72].siUnique);
					TCHAR* pInvName59 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[73].siUnique);
					TCHAR* pInvName60 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[74].siUnique);
					TCHAR* pInvName61 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[75].siUnique);
					TCHAR* pInvName62 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[76].siUnique);
					TCHAR* pInvName63 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[77].siUnique);
					TCHAR* pInvName64 
						= (TCHAR*)pclclient->pclItemManager->GetName(pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[78].siUnique);
					//�ɸ��� ��������
					SI32   villageUnique  = pclClient->pclCM->CR[siCharID]->GetCurrentVillageUnique();
					TCHAR* villageName   = pclClient->pclVillageManager->pclVillageInfo[villageUnique]->szName;

					m_pSectionData->ClearData();
					////////////////////////////////////////////////////////////////////////////////////////////
					//  ������ 
					////////////////////////////////////////////////////////////////////////////////////////////
					m_pSectionData->BeginData( "show_result" );
						m_pSectionData->AddDataStr( "result", szResult );
						m_pSectionData->AddDataStr( "reason", szReason );
					m_pSectionData->EndData( "show_result" );   

					m_pSectionData->BeginData( "charequip" );
					m_pSectionData->AddDataInt( "eWeapon1", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[2].siUnique );
					m_pSectionData->AddDataStr("pItemName1",pItemName1);
					m_pSectionData->AddDataInt( "Itemnum1", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[2].siItemNum);
					m_pSectionData->AddDataInt( "eWeapon2", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[8].siUnique );
					m_pSectionData->AddDataStr("pItemName2",pItemName2);
					m_pSectionData->AddDataInt( "Itemnum2", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[8].siItemNum);
					m_pSectionData->AddDataInt( "eHelmet", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[0].siUnique );
					m_pSectionData->AddDataStr("pItemName3",pItemName3);
					m_pSectionData->AddDataInt( "eArmor", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[1].siUnique );
					m_pSectionData->AddDataStr("pItemName4",pItemName4);
					m_pSectionData->AddDataInt( "eNecklace", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[3].siUnique );
					m_pSectionData->AddDataStr("pItemName5",pItemName5);
					m_pSectionData->AddDataInt( "eRing1", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[4].siUnique );
					m_pSectionData->AddDataStr("pItemName6",pItemName6);
					m_pSectionData->AddDataInt( "eRing2", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[5].siUnique );
					m_pSectionData->AddDataStr("pItemName7",pItemName7);
					m_pSectionData->AddDataInt( "eBelt", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[6].siUnique );
					m_pSectionData->AddDataStr("pItemName8",pItemName8);
					m_pSectionData->AddDataInt( "eShoes", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[7].siUnique );
					m_pSectionData->AddDataStr("pItemName9",pItemName9);
					m_pSectionData->AddDataInt( "eCloak", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[9].siUnique );
					m_pSectionData->AddDataStr("pItemName10",pItemName10);
					m_pSectionData->AddDataInt( "eHat", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[11].siUnique );
					m_pSectionData->AddDataStr("pItemName11",pItemName11);
					m_pSectionData->AddDataInt( "eDress", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[12].siUnique );
					m_pSectionData->AddDataStr("pItemName12",pItemName12);
					m_pSectionData->AddDataInt( "eBag1", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[10].siUnique );
					m_pSectionData->AddDataStr("pItemName13",pItemName13);
					m_pSectionData->AddDataInt( "eBag2", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[13].siUnique );
					m_pSectionData->AddDataStr("pItemName14",pItemName14);
					m_pSectionData->AddDataInt( "eBag3", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[14].siUnique );
					m_pSectionData->AddDataStr("pItemName15",pItemName15);
					m_pSectionData->EndData( "charequip" );

					//�κ��丮
					m_pSectionData->BeginData( "charinventory" );
					m_pSectionData->AddDataInt( "inv1", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[15].siUnique );
					m_pSectionData->AddDataStr("pInvName1",pInvName1);
					m_pSectionData->AddDataInt( "Itemnum15", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[15].siItemNum);
					m_pSectionData->AddDataInt( "inv2", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[16].siUnique );
					m_pSectionData->AddDataStr("pInvName2",pInvName2);
					m_pSectionData->AddDataInt( "Itemnum16", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[16].siItemNum);
					m_pSectionData->AddDataInt( "inv3", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[17].siUnique );
					m_pSectionData->AddDataStr("pInvName3",pInvName3);
					m_pSectionData->AddDataInt( "Itemnum17", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[17].siItemNum);
					m_pSectionData->AddDataInt( "inv4", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[18].siUnique );					
					m_pSectionData->AddDataStr("pInvName4",pInvName4);
					m_pSectionData->AddDataInt( "Itemnum18", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[18].siItemNum);
					m_pSectionData->AddDataInt( "inv5", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[19].siUnique );
					m_pSectionData->AddDataStr("pInvName5",pInvName5);
					m_pSectionData->AddDataInt( "Itemnum19", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[19].siItemNum);
					m_pSectionData->AddDataInt( "inv6", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[20].siUnique );
					m_pSectionData->AddDataStr("pInvName6",pInvName6);
					m_pSectionData->AddDataInt( "Itemnum20", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[20].siItemNum);
					m_pSectionData->AddDataInt( "inv7", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[21].siUnique );
					m_pSectionData->AddDataStr("pInvName7",pInvName7);
					m_pSectionData->AddDataInt( "Itemnum21", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[21].siItemNum);
					m_pSectionData->AddDataInt( "inv8", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[22].siUnique );
					m_pSectionData->AddDataStr("pInvName8",pInvName8);
					m_pSectionData->AddDataInt( "Itemnum22", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[22].siItemNum);
					m_pSectionData->AddDataInt( "inv9", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[23].siUnique );
					m_pSectionData->AddDataStr("pInvName9",pInvName9);
					m_pSectionData->AddDataInt( "Itemnum23", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[23].siItemNum);
					m_pSectionData->AddDataInt( "inv10", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[24].siUnique );					
					m_pSectionData->AddDataStr("pInvName10",pInvName10);
					m_pSectionData->AddDataInt( "Itemnum24", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[24].siItemNum);
					m_pSectionData->EndData( "charinventory" );

					m_pSectionData->BeginData( "charinventory2" );
					m_pSectionData->AddDataInt( "inv11", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[25].siUnique );
					m_pSectionData->AddDataStr("pInvName11",pInvName11);
					m_pSectionData->AddDataInt( "Itemnum25", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[25].siItemNum);
					m_pSectionData->AddDataInt( "inv12", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[26].siUnique );
					m_pSectionData->AddDataStr("pInvName12",pInvName12);
					m_pSectionData->AddDataInt( "Itemnum26", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[26].siItemNum);
					m_pSectionData->AddDataInt( "inv13", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[27].siUnique );
					m_pSectionData->AddDataStr("pInvName13",pInvName13);
					m_pSectionData->AddDataInt( "Itemnum27", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[27].siItemNum);
					m_pSectionData->AddDataInt( "inv14", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[28].siUnique );
					m_pSectionData->AddDataStr("pInvName14",pInvName14);
					m_pSectionData->AddDataInt( "Itemnum28", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[28].siItemNum);
					m_pSectionData->AddDataInt( "inv15", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[29].siUnique );
					m_pSectionData->AddDataStr("pInvName15",pInvName15);
					m_pSectionData->AddDataInt( "Itemnum29", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[29].siItemNum);
					m_pSectionData->AddDataInt( "inv16", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[30].siUnique );
					m_pSectionData->AddDataStr("pInvName16",pInvName16);
					m_pSectionData->AddDataInt( "Itemnum30", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[30].siItemNum);
					m_pSectionData->AddDataInt( "inv17", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[31].siUnique );
					m_pSectionData->AddDataStr("pInvName17",pInvName17);
					m_pSectionData->AddDataInt( "Itemnum31", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[31].siItemNum);
					m_pSectionData->AddDataInt( "inv18", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[32].siUnique );
					m_pSectionData->AddDataStr("pInvName18",pInvName18);
					m_pSectionData->AddDataInt( "Itemnum32", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[32].siItemNum);
					m_pSectionData->AddDataInt( "inv19", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[33].siUnique );
					m_pSectionData->AddDataStr("pInvName19",pInvName19);
					m_pSectionData->AddDataInt( "Itemnum33", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[33].siItemNum);
					m_pSectionData->AddDataInt( "inv20", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[34].siUnique );
					m_pSectionData->AddDataStr("pInvName20",pInvName20);
					m_pSectionData->AddDataInt( "Itemnum34", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[34].siItemNum);
					m_pSectionData->EndData( "charinventory2" );

					m_pSectionData->BeginData( "animalinventory" );
					m_pSectionData->AddDataInt( "inv21", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[35].siUnique );
					m_pSectionData->AddDataStr("pInvName21",pInvName21);
					m_pSectionData->AddDataInt( "Itemnum35", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[35].siItemNum);
					m_pSectionData->AddDataInt( "inv22", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[36].siUnique );
					m_pSectionData->AddDataStr("pInvName22",pInvName22);
					m_pSectionData->AddDataInt( "Itemnum36", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[36].siItemNum);
					m_pSectionData->AddDataInt( "inv23", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[37].siUnique );
					m_pSectionData->AddDataStr("pInvName23",pInvName23);
					m_pSectionData->AddDataInt( "Itemnum37", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[37].siItemNum);
					m_pSectionData->AddDataInt( "inv24", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[38].siUnique );
					m_pSectionData->AddDataStr("pInvName24",pInvName24);
					m_pSectionData->AddDataInt( "Itemnum38", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[38].siItemNum);
					m_pSectionData->AddDataInt( "inv25", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[39].siUnique );
					m_pSectionData->AddDataStr("pInvName25",pInvName25);
					m_pSectionData->AddDataInt( "Itemnum39", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[39].siItemNum);
					m_pSectionData->AddDataInt( "inv26", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[40].siUnique );
					m_pSectionData->AddDataStr("pInvName26",pInvName26);
					m_pSectionData->AddDataInt( "Itemnum40", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[40].siItemNum);
					m_pSectionData->AddDataInt( "inv27", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[41].siUnique );
					m_pSectionData->AddDataStr("pInvName27",pInvName27);
					m_pSectionData->AddDataInt( "Itemnum41", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[41].siItemNum);
					m_pSectionData->AddDataInt( "inv28", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[42].siUnique );
					m_pSectionData->AddDataStr("pInvName28",pInvName28);
					m_pSectionData->AddDataInt( "Itemnum42", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[42].siItemNum);
					m_pSectionData->AddDataInt( "inv29", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[43].siUnique );
					m_pSectionData->AddDataStr("pInvName29",pInvName29);
					m_pSectionData->AddDataInt( "Itemnum43", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[43].siItemNum);
					m_pSectionData->AddDataInt( "inv30", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[44].siUnique );
					m_pSectionData->AddDataStr("pInvName30",pInvName30);
					m_pSectionData->AddDataInt( "Itemnum44", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[44].siItemNum);
					m_pSectionData->EndData( "animalinventory" );

					m_pSectionData->BeginData( "animalinventory2" );
					m_pSectionData->AddDataInt( "inv31", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[45].siUnique );
					m_pSectionData->AddDataStr("pInvName31",pInvName31);
					m_pSectionData->AddDataInt( "Itemnum45", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[45].siItemNum);
					m_pSectionData->AddDataInt( "inv32", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[46].siUnique );
					m_pSectionData->AddDataStr("pInvName32",pInvName32);
					m_pSectionData->AddDataInt( "Itemnum46", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[46].siItemNum);
					m_pSectionData->AddDataInt( "inv33", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[47].siUnique );
					m_pSectionData->AddDataStr("pInvName33",pInvName33);
					m_pSectionData->AddDataInt( "Itemnum47", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[47].siItemNum);
					m_pSectionData->AddDataInt( "inv34", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[48].siUnique );
					m_pSectionData->AddDataStr("pInvName34",pInvName34);
					m_pSectionData->AddDataInt( "Itemnum48", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[48].siItemNum);
					m_pSectionData->AddDataInt( "inv35", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[49].siUnique );
					m_pSectionData->AddDataStr("pInvName35",pInvName35);
					m_pSectionData->AddDataInt( "Itemnum49", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[49].siItemNum);
					m_pSectionData->AddDataInt( "inv36", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[50].siUnique );
					m_pSectionData->AddDataStr("pInvName36",pInvName36);
					m_pSectionData->AddDataInt( "Itemnum50", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[50].siItemNum);
					m_pSectionData->AddDataInt( "inv37", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[51].siUnique );
					m_pSectionData->AddDataStr("pInvName37",pInvName37);
					m_pSectionData->AddDataInt( "Itemnum51", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[51].siItemNum);
					m_pSectionData->AddDataInt( "inv38", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[52].siUnique );
					m_pSectionData->AddDataStr("pInvName38",pInvName38);
					m_pSectionData->AddDataInt( "Itemnum52", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[52].siItemNum);
					m_pSectionData->AddDataInt( "inv39", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[53].siUnique );
					m_pSectionData->AddDataStr("pInvName39",pInvName39);
					m_pSectionData->AddDataInt( "Itemnum53", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[53].siItemNum);
					m_pSectionData->AddDataInt( "inv40", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[54].siUnique );
					m_pSectionData->AddDataStr("pInvName40",pInvName40);
					m_pSectionData->AddDataInt( "Itemnum54", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[54].siItemNum);
					m_pSectionData->EndData( "animalinventory2" );

					m_pSectionData->BeginData( "bag" );
					m_pSectionData->AddDataInt( "inv41", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[55].siUnique );
					m_pSectionData->AddDataStr("pInvName41",pInvName41);
					m_pSectionData->AddDataInt( "Itemnum55", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[55].siItemNum);
					m_pSectionData->AddDataInt( "inv42", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[56].siUnique );
					m_pSectionData->AddDataStr("pInvName42",pInvName42);
					m_pSectionData->AddDataInt( "Itemnum56", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[56].siItemNum);
					m_pSectionData->AddDataInt( "inv43", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[57].siUnique );
					m_pSectionData->AddDataStr("pInvName43",pInvName43);
					m_pSectionData->AddDataInt( "Itemnum57", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[57].siItemNum);
					m_pSectionData->AddDataInt( "inv44", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[58].siUnique );
					m_pSectionData->AddDataStr("pInvName44",pInvName44);
					m_pSectionData->AddDataInt( "Itemnum58", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[58].siItemNum);
					m_pSectionData->AddDataInt( "inv45", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[59].siUnique );
					m_pSectionData->AddDataStr("pInvName45",pInvName45);
					m_pSectionData->AddDataInt( "Itemnum59", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[59].siItemNum);
					m_pSectionData->AddDataInt( "inv46", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[60].siUnique );
					m_pSectionData->AddDataStr("pInvName46",pInvName46);
					m_pSectionData->AddDataInt( "Itemnum06", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[60].siItemNum);
					m_pSectionData->AddDataInt( "inv47", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[61].siUnique );
					m_pSectionData->AddDataStr("pInvName47",pInvName47);
					m_pSectionData->AddDataInt( "Itemnum61", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[61].siItemNum);
					m_pSectionData->AddDataInt( "inv48", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[62].siUnique );
					m_pSectionData->AddDataStr("pInvName48",pInvName48);
					m_pSectionData->AddDataInt( "Itemnum62", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[62].siItemNum);
					m_pSectionData->AddDataInt( "inv49", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[63].siUnique );
					m_pSectionData->AddDataStr("pInvName49",pInvName49);
					m_pSectionData->AddDataInt( "Itemnum63", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[63].siItemNum);
					m_pSectionData->AddDataInt( "inv50", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[64].siUnique );
					m_pSectionData->AddDataStr("pInvName50",pInvName50);
					m_pSectionData->AddDataInt( "Itemnum64", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[64].siItemNum);
					m_pSectionData->AddDataInt( "inv51", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[65].siUnique );
					m_pSectionData->AddDataStr("pInvName51",pInvName51);
					m_pSectionData->AddDataInt( "Itemnum65", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[65].siItemNum);
					m_pSectionData->AddDataInt( "inv52", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[66].siUnique );
					m_pSectionData->AddDataStr("pInvName52",pInvName52);
					m_pSectionData->AddDataInt( "Itemnum66", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[66].siItemNum);
					m_pSectionData->EndData( "bag" );

					m_pSectionData->BeginData( "bag2" );
					m_pSectionData->AddDataInt( "inv53", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[67].siUnique );
					m_pSectionData->AddDataStr("pInvName53",pInvName53);
					m_pSectionData->AddDataInt( "Itemnum67", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[67].siItemNum);
					m_pSectionData->AddDataInt( "inv54", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[68].siUnique );
					m_pSectionData->AddDataStr("pInvName54",pInvName54);
					m_pSectionData->AddDataInt( "Itemnum68", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[68].siItemNum);
					m_pSectionData->AddDataInt( "inv55", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[69].siUnique );
					m_pSectionData->AddDataStr("pInvName55",pInvName55);
					m_pSectionData->AddDataInt( "Itemnum69", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[69].siItemNum);
					m_pSectionData->AddDataInt( "inv56", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[70].siUnique );
					m_pSectionData->AddDataStr("pInvName56",pInvName56);
					m_pSectionData->AddDataInt( "Itemnum70", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[70].siItemNum);
					m_pSectionData->AddDataInt( "inv57", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[71].siUnique );
					m_pSectionData->AddDataStr("pInvName57",pInvName57);
					m_pSectionData->AddDataInt( "Itemnum71", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[71].siItemNum);
					m_pSectionData->AddDataInt( "inv58", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[72].siUnique );
					m_pSectionData->AddDataStr("pInvName58",pInvName58);
					m_pSectionData->AddDataInt( "Itemnum72", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[72].siItemNum);
					m_pSectionData->AddDataInt( "inv59", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[73].siUnique );
					m_pSectionData->AddDataStr("pInvName59",pInvName59);
					m_pSectionData->AddDataInt( "Itemnum73", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[73].siItemNum);
					m_pSectionData->AddDataInt( "inv60", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[74].siUnique );
					m_pSectionData->AddDataStr("pInvName60",pInvName60);
					m_pSectionData->AddDataInt( "Itemnum74", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[74].siItemNum);
					m_pSectionData->AddDataInt( "inv61", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[75].siUnique );
					m_pSectionData->AddDataStr("pInvName61",pInvName61);
					m_pSectionData->AddDataInt( "Itemnum75", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[75].siItemNum);
					m_pSectionData->AddDataInt( "inv62", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[76].siUnique );
					m_pSectionData->AddDataStr("pInvName62",pInvName62);
					m_pSectionData->AddDataInt( "Itemnum76", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[76].siItemNum);
					m_pSectionData->AddDataInt( "inv63", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[77].siUnique );
					m_pSectionData->AddDataStr("pInvName63",pInvName63);
					m_pSectionData->AddDataInt( "Itemnum77", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[77].siItemNum);
					m_pSectionData->AddDataInt( "inv64", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[7].siUnique );
					m_pSectionData->AddDataStr("pInvName76",pInvName64);
					m_pSectionData->AddDataInt( "Itemnum44", pclClient->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[78].siItemNum);
					m_pSectionData->EndData( "bag2" );

					// �κ��丮 �������� ����
					m_pSectionData->BeginData( "item_add" );
						m_pSectionData->AddDataInt( "personid", siPersonID );
					m_pSectionData->EndData( "item_add" );

					sGMResponse_Section sectionmsgtrade( pRecvMsg->m_iPageID, pRecvMsg->m_szCharName, m_pSectionData );
					SendPacket( pSession, (sPacketHeader*)&sectionmsgtrade ); 
					
					
				}
			}break;

			//[�߰� : �ŷ�����. Ȳ���� 2007.9.21] �ϴ�����.
			/*case GMMSG_PAGEID_TRADING:
			{
			SI32	siCharID = pclserver->pclCM->GetIDFromName(charname);
			cltCharServer* pclchar = NULL;

			if(pclserver->pclCM->IsValidID(siCharID))
			{
			pclchar = (cltCharServer*)pclserver->pclCM->CR[siCharID];
			}
			if (pclchar == NULL) {
			return;
			}

			if(pclchar)
			{
			SI32   villageUnique  = pclClient->pclCM->CR[siCharID]->GetCurrentVillageUnique();
			TCHAR* villageName   = pclClient->pclVillageManager->pclVillageInfo[villageUnique]->szName;

			m_pSectionData->ClearData();
			m_pSectionData->BeginData( "market" );
			m_pSectionData->AddDataStr( "village", villageName );
			m_pSectionData->AddDataInt( "Resident_No", 40 );
			m_pSectionData->AddDataStr( "Name", "���ʻ��." );
			m_pSectionData->AddDataInt( "Count",45 );
			m_pSectionData->AddDataInt( "Price", 0 );
			m_pSectionData->EndData( "market" );

			m_pSectionData->BeginData( "stock" );
			m_pSectionData->AddDataStr( "village1", "����" );
			m_pSectionData->AddDataInt( "Resident_No", 40 );
			m_pSectionData->AddDataStr( "village2", "�λ�" );
			m_pSectionData->AddDataInt( "Count", 45 );
			m_pSectionData->AddDataInt( "Price", 0 );
			m_pSectionData->EndData( "stock" );

			m_pSectionData->BeginData( "storge" );
			m_pSectionData->AddDataStr( "village", "�뱸" );
			m_pSectionData->AddDataInt( "Resident_No", 40 );
			m_pSectionData->AddDataStr( "Storge_village", "����" );
			m_pSectionData->AddDataInt( "Storge_No",45 );
			m_pSectionData->AddDataInt( "Price", 0 );
			m_pSectionData->EndData( "storge" );

			m_pSectionData->BeginData( "trade" );
			m_pSectionData->AddDataStr( "Name", "super power!!" );
			m_pSectionData->AddDataInt( "Count", 99 );
			m_pSectionData->AddDataInt( "Price", 789 );
			m_pSectionData->EndData( "trade" );

			sGMResponse_Section sectionmsgtrade( pRecvMsg->m_iPageID, pRecvMsg->m_szCharName, m_pSectionData );
			SendPacket( pSession, (sPacketHeader*)&sectionmsgtrade ); 
			}
			}break;*/
		//[�߰� : ��ȯ�� ���� ���. Ȳ���� 2007.9.21]
		case GMMSG_PAGEID_SUMMON:
			{
				SI32	siCharID = pclserver->pclCM->GetIDFromName(charname);
				cltCharServer* pclchar = NULL;

				if(pclserver->pclCM->IsValidID(siCharID))
				{
					pclchar = (cltCharServer*)pclserver->pclCM->CR[siCharID];
				}
				if (pclchar == NULL)
				{
					SI32 siClientID = pSession->GetPerson()->GetCharID();
					sDBRequest_SummonByName clMsg( siClientID, charname, GMMSG_PAGEID_SUMMON );
					pclClient->SendDBMsg(DBSELECT_LETTER, (sPacketHeader *)&clMsg);
				}

				if(pclchar)
				{		
					SI32 siPersonID = pclserver->pclCM->GetPersonIDFromName( charname );

					SI32 totalMinDamage, totalMaxDamage, totalAC;
					totalMinDamage = totalMaxDamage = totalAC = 0;

					SI32 siSummonIndex1 = 0;
					SI32 siSummonIndex2 = 1;
					SI32 siSummonIndex3 = 2;
					// ù��° ��ȯ��.
					cltSummon* pSummon = pclserver->pclCM->CR[siCharID]->pclCI->clSummonInfo.GetSummon(siSummonIndex1);

					cltParametaBox clPB;	
					//cltKindInfo* pclki = pclClient->pclKindInfoSet->pclKI[pSummon->siKind];
					cltKindInfo* pclki = NULL;
					cltGMCommandKindInfo* pclGMki = NULL;

					if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
					{
						pclki = pclClient->pclKindInfoSet->pclSummonKI[pSummon->siKind];
						pclGMki = pclClient->pclKindInfoSet->pclGMCommandKindInfo[pSummon->siKind];
					}
					else
					{
						pclki = pclClient->pclKindInfoSet->pclKI[pSummon->siKind];
						pclGMki = pclClient->pclKindInfoSet->pclGMCommandKindInfo[pSummon->siKind];
					}

					if(pclki == NULL )
					{
						break;
					}

					if(pclGMki == NULL)
					{
						break;
					}

					bool bmosterhero = false;
					// �����۸����� �Ǹ��ϴ� ��ȯ�����̰� ���Ϳ��� ��ȭ�� ���̶��, 
					if(pclki->bSummonMall && pSummon->siIdentity == 0)	
					{
						bmosterhero = true;
					}


					cltPIPInfo		clipinfo2;
					clipinfo2.Set(&pSummon->clIP);
					clPB.Init(pclClient->pclItemManager, &clipinfo2, NULL, pclki, pclGMki);

					cltItem* pclitemlist = pclserver->pclCM->CR[siCharID]->pclCI->clSummonInfo.GetSummonEquipItemList( siSummonIndex1 );

					SI16 siAttackWearStoneNum	= pSummon->siAttackWearStoneNum;
					SI16 siDefenseWearStoneNum	= pSummon->siDefenseWearStoneNum;

					clPB.Action(NULL, 0, PERSONITEM_WEAPON1, pclitemlist, NULL, NULL, NULL, NULL, siAttackWearStoneNum, siDefenseWearStoneNum, GAMEMODE_CLIENT, true );

					m_pSectionData->ClearData();
					////////////////////////////////////////////////////////////////////////////////////////////
					//  ������ 
					////////////////////////////////////////////////////////////////////////////////////////////
					m_pSectionData->BeginData( "show_result" );
						m_pSectionData->AddDataStr( "result", szResult );
						m_pSectionData->AddDataStr( "reason", szReason );
					m_pSectionData->EndData( "show_result" );   

					m_pSectionData->BeginData( "summoninfo1" );
					m_pSectionData->AddDataStr( "summonname1",		pSummon->szName );
					m_pSectionData->AddDataStr( "summonkind1",		(char*)pclki->GetName());
					m_pSectionData->AddDataFormat( "summonlevel1",	"%d / 100( Ev %d )",	pSummon->clIP.GetLevel(),   pclki->siEvolveLevel);
					m_pSectionData->AddDataFormat( "summonexp1",	"%d / %d",	pSummon->clIP.GetCurExp(),	clPB.GetNextExp());
					m_pSectionData->AddDataFormat( "summonHP1",		"%d / %d",	pSummon->clIP.GetLife(),	clPB.GetMaxLife());
					m_pSectionData->AddDataFormat( "summonMP1",		"%d / %d",	pSummon->clIP.GetMana(),	clPB.GetMaxMana());
					m_pSectionData->EndData( "summoninfo1" );

					m_pSectionData->BeginData( "summonstatus1" );
					m_pSectionData->AddDataInt( "summonstr1",   pSummon->clIP.GetStr());
					m_pSectionData->AddDataInt( "summonagi1",   pSummon->clIP.GetMag());
					m_pSectionData->AddDataInt( "summonwis1",   pSummon->clIP.GetMag());
					m_pSectionData->AddDataInt( "summonvit1",   pSummon->clIP.GetVit());
					m_pSectionData->AddDataInt( "summonbonus1", pSummon->clIP.GetBonus());
					m_pSectionData->EndData( "summonstatus1" );

					// ���ݷ°� ���� ���.
					SummonAttackAndDeffence(clPB, totalMinDamage, totalMaxDamage, totalAC);
					m_pSectionData->BeginData( "summonattackinfo1" );
					m_pSectionData->AddDataFormat( "summonattack1",  "%d - %d",	totalMinDamage, totalMaxDamage);
					m_pSectionData->AddDataInt( "summondefense1", totalAC);
					m_pSectionData->EndData( "summonattackinfo1" );


					// �ι�° ��ȯ��.
					pSummon = pclserver->pclCM->CR[siCharID]->pclCI->clSummonInfo.GetSummon(siSummonIndex2);
					//pclki	= pclClient->pclKindInfoSet->pclKI[pSummon->siKind];
					if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
					{
						pclki = pclClient->pclKindInfoSet->pclSummonKI[pSummon->siKind];
						pclGMki = pclClient->pclKindInfoSet->pclGMCommandKindInfo[pSummon->siKind];
					}
					else
					{
						pclki = pclClient->pclKindInfoSet->pclKI[pSummon->siKind];
						pclGMki = pclClient->pclKindInfoSet->pclGMCommandKindInfo[pSummon->siKind];
					}

					if(pclki == NULL )
					{
						sGMResponse_Section sectionmsg( pRecvMsg->m_iPageID, pRecvMsg->m_szCharName, m_pSectionData );
						SendPacket( pSession, (sPacketHeader*)&sectionmsg ); 
						break;
					}

					bmosterhero = false;
					// �����۸����� �Ǹ��ϴ� ��ȯ�����̰� ���Ϳ��� ��ȭ�� ���̶��, 
					if(pclki->bSummonMall && pSummon->siIdentity == 0)	
					{
						bmosterhero = true;
					}

					clipinfo2.Set(&pSummon->clIP);
					clPB.Init(pclClient->pclItemManager, &clipinfo2, NULL, pclki, pclGMki);

					pclitemlist = pclserver->pclCM->CR[siCharID]->pclCI->clSummonInfo.GetSummonEquipItemList( siSummonIndex2 );

					siAttackWearStoneNum	= pSummon->siAttackWearStoneNum;
					siDefenseWearStoneNum	= pSummon->siDefenseWearStoneNum;

					clPB.Action(NULL, 0, PERSONITEM_WEAPON1, pclitemlist, NULL, NULL, NULL, NULL, siAttackWearStoneNum, siDefenseWearStoneNum, GAMEMODE_CLIENT, true );

					m_pSectionData->BeginData( "summoninfo2" );
					m_pSectionData->AddDataStr( "summonname2",		pSummon->szName );
					m_pSectionData->AddDataStr( "summonkind2",		(char*)pclki->GetName() );
					m_pSectionData->AddDataFormat( "summonlevel2",	"%d / 100( Ev %d )", pSummon->clIP.GetLevel(),   pclki->siEvolveLevel);
					m_pSectionData->AddDataFormat( "summonexp2",	"%d / %d",			 pSummon->clIP.GetCurExp(),  clPB.GetNextExp());
					m_pSectionData->AddDataFormat( "summonHP2",		"%d / %d",			 pSummon->clIP.GetLife(),	 clPB.GetMaxLife());
					m_pSectionData->AddDataFormat( "summonMP2",		"%d / %d",			 pSummon->clIP.GetMana(),	 clPB.GetMaxMana());
					m_pSectionData->EndData( "summoninfo2" );

					m_pSectionData->BeginData( "summonstatus2" );
					m_pSectionData->AddDataInt( "summonstr2",	pSummon->clIP.GetStr());
					m_pSectionData->AddDataInt( "summonagi2",	pSummon->clIP.GetMag());
					m_pSectionData->AddDataInt( "summonwis2",	pSummon->clIP.GetMana());
					m_pSectionData->AddDataInt( "summonvit2",	pSummon->clIP.GetVit());
					m_pSectionData->AddDataInt( "summonbonus2",	pSummon->clIP.GetBonus());
					m_pSectionData->EndData( "summonstatus2" );

					// ���ݷ°� ���� ���.
					SummonAttackAndDeffence(clPB, totalMinDamage, totalMaxDamage, totalAC);
					m_pSectionData->BeginData( "summonattackinfo2" );
					m_pSectionData->AddDataFormat( "summonattack2",  "%d - %d",	totalMinDamage, totalMaxDamage);
					m_pSectionData->AddDataInt( "summondefense2",	totalAC);
					m_pSectionData->EndData( "summonattackinfo2" );

					// ��ȯ�� �������� ����
					m_pSectionData->BeginData( "summon_add" );
						m_pSectionData->AddDataInt( "personid", siPersonID );
					m_pSectionData->EndData( "summon_add" );

					sGMResponse_Section sectionmsg( pRecvMsg->m_iPageID, pRecvMsg->m_szCharName, m_pSectionData );
					SendPacket( pSession, (sPacketHeader*)&sectionmsg ); 
				}
			}break;

		//[�߰� : ��ų ���� ���. Ȳ���� 2007.10.2]
		case GMMSG_PAGEID_SKILLINFO :
			{
				SI32	siCharID = pclserver->pclCM->GetIDFromName(charname);
				cltCharServer* pclchar = NULL;

				if(pclserver->pclCM->IsValidID(siCharID))
				{
					pclchar = (cltCharServer*)pclserver->pclCM->CR[siCharID];
				}
				if (pclchar == NULL) {

					SI32 siClientID = pSession->GetPerson()->GetCharID();
					sDBRequest_SkillByName clMsg( siClientID, charname, GMMSG_PAGEID_SKILLINFO );
					pclClient->SendDBMsg(DBSELECT_LETTER, (sPacketHeader *)&clMsg);
				}
				if(pclchar)
				{
					SI32 siPersonID = pclserver->pclCM->GetPersonIDFromName( charname );

					m_pSectionData->ClearData();
					////////////////////////////////////////////////////////////////////////////////////////////
					//  ������ 
					////////////////////////////////////////////////////////////////////////////////////////////
					m_pSectionData->BeginData( "show_result" );
						m_pSectionData->AddDataStr( "result", szResult );
						m_pSectionData->AddDataStr( "reason", szReason );
					m_pSectionData->EndData( "show_result" );                   

					TCHAR* pSkillExplain = NULL;
										
					TCHAR* strSkill =  "%d / 100";
					//SI32 skilllevel = pclClient->pclCM->CR[id]->pclCI->clCharSkill.GetSkillLevel( m_siCurrentSkillUnique );
					//pclclient->pclSkillManager->GetMaxLevel( m_siCurrentSkillUnique )	   // å �Դ� �� ��ų ����.
					//pclclient->pclSkillManager->GetMaxExpLevel( m_siCurrentSkillUnique ) // �������� ��� �� ��ų ����.
					cltItem* pclitemlist = &pclserver->pclCM->CR[siCharID]->pclCI->clCharItem.clItem[0];

					m_pSectionData->BeginData( "make_equip" );

					m_pSectionData->AddDataFormat( "make_armor", strSkill, pclchar->pclCI->clCharSkill.GetTotalSkillLevel(SKILL_MAKEARMOUR1, 0, 0, pclitemlist));
					pSkillExplain = SkillExplain((cltCharClient*)pclClient->pclCM->CR[siCharID], SKILL_MAKEARMOUR1);				
					m_pSectionData->AddDataStr( "explain1", pSkillExplain );						m_pSectionData->AddDataFormat( "make_helm",	 strSkill, pclchar->pclCI->clCharSkill.GetTotalSkillLevel(SKILL_MAKEHELMET1, 0, 0, pclitemlist));
					pSkillExplain = SkillExplain((cltCharClient*)pclClient->pclCM->CR[siCharID], SKILL_MAKEHELMET1);				
					m_pSectionData->AddDataStr( "explain2", pSkillExplain );

					m_pSectionData->EndData( "make_equip" );


					m_pSectionData->BeginData( "make_weapon");

					m_pSectionData->AddDataFormat( "make_sword",	strSkill, pclchar->pclCI->clCharSkill.GetTotalSkillLevel(SKILL_MAKESWORD1, 0, 0, pclitemlist));
					pSkillExplain = SkillExplain((cltCharClient*)pclClient->pclCM->CR[siCharID], SKILL_MAKESWORD1);				
					m_pSectionData->AddDataStr( "explain3", pSkillExplain );

					m_pSectionData->AddDataFormat( "make_spear",	strSkill, pclchar->pclCI->clCharSkill.GetTotalSkillLevel(SKILL_MAKESPEAR1, 0, 0, pclitemlist));
					pSkillExplain = SkillExplain((cltCharClient*)pclClient->pclCM->CR[siCharID], SKILL_MAKESPEAR1);				
					m_pSectionData->AddDataStr( "explain4", pSkillExplain );

					m_pSectionData->AddDataFormat( "make_axe",		strSkill, pclchar->pclCI->clCharSkill.GetTotalSkillLevel(SKILL_MAKEAXE1, 0, 0, pclitemlist));
					pSkillExplain = SkillExplain((cltCharClient*)pclClient->pclCM->CR[siCharID], SKILL_MAKEAXE1);				
					m_pSectionData->AddDataStr( "explain5", pSkillExplain );

					m_pSectionData->AddDataFormat( "make_cane",	 	strSkill, pclchar->pclCI->clCharSkill.GetTotalSkillLevel(SKILL_MAKESTAFF1, 0, 0, pclitemlist));
					pSkillExplain = SkillExplain((cltCharClient*)pclClient->pclCM->CR[siCharID], SKILL_MAKESTAFF1);				
					m_pSectionData->AddDataStr( "explain6", pSkillExplain );

					m_pSectionData->AddDataFormat( "make_bow" ,	 	strSkill, pclchar->pclCI->clCharSkill.GetTotalSkillLevel(SKILL_MAKEBOW1, 0, 0, pclitemlist));
					pSkillExplain = SkillExplain((cltCharClient*)pclClient->pclCM->CR[siCharID], SKILL_MAKEBOW1);				
					m_pSectionData->AddDataStr( "explain7", pSkillExplain );

					m_pSectionData->AddDataFormat( "make_rifle",	strSkill, pclchar->pclCI->clCharSkill.GetTotalSkillLevel(SKILL_MAKEGUN1, 0, 0, pclitemlist));
					pSkillExplain = SkillExplain((cltCharClient*)pclClient->pclCM->CR[siCharID], SKILL_MAKEGUN1);				
					m_pSectionData->AddDataStr( "explain8", pSkillExplain );

					m_pSectionData->EndData( "make_weapon" );

					m_pSectionData->BeginData( "make_acc" );

					m_pSectionData->AddDataFormat( "make_shoes",	strSkill, pclchar->pclCI->clCharSkill.GetTotalSkillLevel(SKILL_MAKESHOES1, 0, 0, pclitemlist));
					pSkillExplain = SkillExplain((cltCharClient*)pclClient->pclCM->CR[siCharID], SKILL_MAKESHOES1);				
					m_pSectionData->AddDataStr( "explain9", pSkillExplain );

					m_pSectionData->AddDataFormat( "make_belt",	 	strSkill, pclchar->pclCI->clCharSkill.GetTotalSkillLevel(SKILL_MAKEBELT1, 0, 0, pclitemlist));
					pSkillExplain = SkillExplain((cltCharClient*)pclClient->pclCM->CR[siCharID], SKILL_MAKEBELT1);				
					m_pSectionData->AddDataStr( "explain10", pSkillExplain );

					m_pSectionData->EndData( "make_acc" );

					m_pSectionData->BeginData( "make_tool" );

					m_pSectionData->AddDataFormat( "make_iron",	 	strSkill, pclchar->pclCI->clCharSkill.GetTotalSkillLevel(SKILL_MAKEIRON1, 0, 0, pclitemlist));
					pSkillExplain = SkillExplain((cltCharClient*)pclClient->pclCM->CR[siCharID], SKILL_MAKEIRON1);				
					m_pSectionData->AddDataStr( "explain11", pSkillExplain );

					m_pSectionData->AddDataFormat( "make_tool",	 	strSkill, pclchar->pclCI->clCharSkill.GetTotalSkillLevel(SKILL_MAKETOOL1, 0, 0, pclitemlist));
					pSkillExplain = SkillExplain((cltCharClient*)pclClient->pclCM->CR[siCharID], SKILL_MAKETOOL1);				
					m_pSectionData->AddDataStr( "explain12", pSkillExplain );

					m_pSectionData->EndData( "make_tool" );

					m_pSectionData->BeginData( "make_basic" );

					m_pSectionData->AddDataFormat( "make_prescription",	 	strSkill, pclchar->pclCI->clCharSkill.GetTotalSkillLevel(SKILL_CAPTURE, 0, 0, pclitemlist));
					pSkillExplain = SkillExplain((cltCharClient*)pclClient->pclCM->CR[siCharID], SKILL_CAPTURE);				
					m_pSectionData->AddDataStr( "explain13", pSkillExplain );

					m_pSectionData->AddDataFormat( "make_cooking",			strSkill, pclchar->pclCI->clCharSkill.GetTotalSkillLevel(SKILL_MAKEFOOD, 0, 0, pclitemlist));
					pSkillExplain = SkillExplain((cltCharClient*)pclClient->pclCM->CR[siCharID], SKILL_MAKEFOOD);				
					m_pSectionData->AddDataStr( "explain14", pSkillExplain );

					m_pSectionData->AddDataFormat( "make_farming",			strSkill, pclchar->pclCI->clCharSkill.GetTotalSkillLevel(SKILL_FARM, 0, 0, pclitemlist));
					pSkillExplain = SkillExplain((cltCharClient*)pclClient->pclCM->CR[siCharID], SKILL_FARM);				
					m_pSectionData->AddDataStr( "explain15", pSkillExplain );

					m_pSectionData->AddDataFormat( "make_mining",			strSkill, pclchar->pclCI->clCharSkill.GetTotalSkillLevel(SKILL_MINE, 0, 0, pclitemlist));
					pSkillExplain = SkillExplain((cltCharClient*)pclClient->pclCM->CR[siCharID], SKILL_MINE);				
					m_pSectionData->AddDataStr( "explain16", pSkillExplain );

					m_pSectionData->EndData( "make_basic" );

					m_pSectionData->BeginData( "uesage_weapon" );

					m_pSectionData->AddDataFormat( "uesage_sword", 	strSkill, pclchar->pclCI->clCharSkill.GetTotalSkillLevel(SKILL_USESWORD1, 0, 0, pclitemlist));
					pSkillExplain = SkillExplain((cltCharClient*)pclClient->pclCM->CR[siCharID], SKILL_USESWORD1);				
					m_pSectionData->AddDataStr( "explain17", pSkillExplain );

					m_pSectionData->AddDataFormat( "uesage_spear",  strSkill,	pclchar->pclCI->clCharSkill.GetTotalSkillLevel(SKILL_USESPEAR1, 0, 0, pclitemlist));
					pSkillExplain = SkillExplain((cltCharClient*)pclClient->pclCM->CR[siCharID], SKILL_USESPEAR1);				
					m_pSectionData->AddDataStr( "explain18", pSkillExplain );

					m_pSectionData->AddDataFormat( "uesage_axe",	strSkill,	pclchar->pclCI->clCharSkill.GetTotalSkillLevel(SKILL_USEAXE1, 0, 0, pclitemlist));
					pSkillExplain = SkillExplain((cltCharClient*)pclClient->pclCM->CR[siCharID], SKILL_USEAXE1);				
					m_pSectionData->AddDataStr( "explain19", pSkillExplain );

					m_pSectionData->AddDataFormat( "uesage_cane",   strSkill,	pclchar->pclCI->clCharSkill.GetTotalSkillLevel(SKILL_USESTAFF1, 0, 0, pclitemlist));
					pSkillExplain = SkillExplain((cltCharClient*)pclClient->pclCM->CR[siCharID], SKILL_USESTAFF1);				
					m_pSectionData->AddDataStr( "explain20", pSkillExplain );

					m_pSectionData->AddDataFormat( "uesage_bow",	strSkill,	pclchar->pclCI->clCharSkill.GetTotalSkillLevel(SKILL_USEBOW1, 0, 0, pclitemlist));
					pSkillExplain = SkillExplain((cltCharClient*)pclClient->pclCM->CR[siCharID], SKILL_USEBOW1);				
					m_pSectionData->AddDataStr( "explain21", pSkillExplain );

					m_pSectionData->AddDataFormat( "uesage_rifle",  strSkill,	pclchar->pclCI->clCharSkill.GetTotalSkillLevel(SKILL_USEGUN1, 0, 0, pclitemlist));
					pSkillExplain = SkillExplain((cltCharClient*)pclClient->pclCM->CR[siCharID], SKILL_USEGUN1);				
					m_pSectionData->AddDataStr( "explain22", pSkillExplain );

					m_pSectionData->EndData( "uesage_weapon" );

					m_pSectionData->BeginData( "useage_ocean" );

					m_pSectionData->AddDataFormat( "useage_fishing",  	strSkill, pclchar->pclCI->clCharSkill.GetTotalSkillLevel(SKILL_FISH, 0, 0, pclitemlist));
					pSkillExplain = SkillExplain((cltCharClient*)pclClient->pclCM->CR[siCharID], SKILL_FISH);				
					m_pSectionData->AddDataStr( "explain23", pSkillExplain );

					m_pSectionData->EndData( "useage_ocean" );

					m_pSectionData->BeginData( "useage_other" );

					m_pSectionData->AddDataFormat( "summon",		strSkill, pclchar->pclCI->clCharSkill.GetTotalSkillLevel(SKILL_SUMMON, 0, 0, pclitemlist));
					pSkillExplain = SkillExplain((cltCharClient*)pclClient->pclCM->CR[siCharID], SKILL_SUMMON);				
					m_pSectionData->AddDataStr( "explain24", pSkillExplain );

					m_pSectionData->AddDataFormat( "horsetrining",  strSkill, pclchar->pclCI->clCharSkill.GetTotalSkillLevel(SKILL_HORSETRAINING, 0, 0, pclitemlist));
					pSkillExplain = SkillExplain((cltCharClient*)pclClient->pclCM->CR[siCharID], SKILL_HORSETRAINING);				
					m_pSectionData->AddDataStr( "explain25", pSkillExplain );

					m_pSectionData->AddDataFormat( "capture",		strSkill, pclchar->pclCI->clCharSkill.GetTotalSkillLevel(SKILL_CAPTURE, 0, 0, pclitemlist));
					pSkillExplain = SkillExplain((cltCharClient*)pclClient->pclCM->CR[siCharID], SKILL_CAPTURE);				
					m_pSectionData->AddDataStr( "explain26", pSkillExplain );

					m_pSectionData->EndData( "useage_other" );

					// ��ų �������� ����
					m_pSectionData->BeginData( "skill_add" );
						m_pSectionData->AddDataInt( "personid", siPersonID );
					m_pSectionData->EndData( "skill_add" );


					sGMResponse_Section sectionmsg( pRecvMsg->m_iPageID, pRecvMsg->m_szCharName, m_pSectionData );
					SendPacket( pSession, (sPacketHeader*)&sectionmsg ); 
				}
			}
			break;

			//[�߰� : �ε��� ���� ���. Ȳ���� 2007.9.30]
		case GMMSG_PAGEID_REALESTATE :
			{
				SI32	siCharID = pclserver->pclCM->GetIDFromName(charname);
				cltCharServer* pclchar = NULL;

				if(pclserver->pclCM->IsValidID(siCharID))
				{
					pclchar = (cltCharServer*)pclserver->pclCM->CR[siCharID];
				}
				if (pclchar == NULL) {
					SI32 siClientID = pSession->GetPerson()->GetCharID();
					sDBRequest_RealestateByNAme clMsg( siClientID, charname, GMMSG_PAGEID_REALESTATE );
					pclClient->SendDBMsg(DBSELECT_LETTER, (sPacketHeader *)&clMsg);
				}
				if(pclchar)
				{
					SI32 RealEstateCnt = pclchar->pclCI->clRealEstate.GetRealEstateNum();

					// â�� ����.
					SI32 warehouseCnt = 1;

					// ���°� ����.
					SI32 stableCnt = 0;

					char	TableStr[128];
					ZeroMemory(TableStr, sizeof(TableStr));

					char	TempStr[128];
					ZeroMemory(TempStr, sizeof(TempStr));

					char	szDate[1024];
					ZeroMemory(szDate, sizeof(szDate));

					SI32 siPersonID = pclserver->pclCM->GetPersonIDFromName( charname );

					m_pSectionData->ClearData();
					////////////////////////////////////////////////////////////////////////////////////////////
					//  ������ 
					////////////////////////////////////////////////////////////////////////////////////////////
					m_pSectionData->BeginData( "show_result" );
						m_pSectionData->AddDataStr( "result", szResult );
						m_pSectionData->AddDataStr( "reason", szReason );
					m_pSectionData->EndData( "show_result" );



					for(SI32 Cnt = 0; Cnt < RealEstateCnt; ++Cnt)
					{
						// ���� ���� ���.
						SI32  VillageNo	  = pclchar->pclCI->clRealEstate.clRealEstate[Cnt].siVillageUnique;
						SI32  HouseIndex  = pclchar->pclCI->clRealEstate.clRealEstate[Cnt].siIndex;
						char* VillageName = pclClient->pclVillageManager->pclVillageInfo[VillageNo]->szName;

						//------------------------------------------------------------------------------------------------------------------
						TCHAR temp[1024]	= TEXT("");
						TCHAR temp1[1024]	= TEXT("");
						TCHAR buffer1[1024] = TEXT("");
						TCHAR buffer2[1024] = TEXT("");

						SI32 id = 1;
						cltRealEstateUnit* pclinfo = pclClient->pclCM->CR[id]->pclCI->clRealEstate.Find(VillageNo, pclchar->pclCI->clRealEstate.clRealEstate[Cnt].siType, HouseIndex );

						if(pclinfo)
						{
							TCHAR* pText = GetTxtFromMgr(2136);

							StringCchPrintf( temp, 1024, pText, pclinfo->clContract.siRentFee );
							StringCchCopy( buffer1, 1024, temp );

							pText = GetTxtFromMgr(2137);
							StringCchPrintf( temp, 1024, pText, pclinfo->clContract.siRentPeriod );
							StringCchCat( buffer1, 1024, temp );

							if ( pclinfo->clContract.clDate.GetDateText( temp ) == TRUE )
							{
								pText = GetTxtFromMgr(2138);
								StringCchPrintf( temp1, 1024, pText, temp );
								StringCchCat( buffer1, 1024, temp1 );
							}
						}

						cltServer * pclServer = (cltServer*)pclClient;


						memset( buffer2, 0, 1024 );
						TCHAR* pText = GetTxtFromMgr(2136);

						StringCchPrintf( temp, 1024, pText, pclchar->pclCI->clRealEstate.clRealEstate[Cnt].clContract.siRentFee);

						StringCchCopy( buffer2, 1024, temp );
						pText = GetTxtFromMgr(2137);

						StringCchPrintf( temp, 1024, pText, pclchar->pclCI->clRealEstate.clRealEstate[Cnt].clContract.siRentPeriod );

						StringCchCat( buffer2, 1024, temp );
						//------------------------------------------------------------------------------------------------------------------

						// â�� ������.
						cltItem* pItem = &pclClient->pclHouseManager->clClientUnit[HouseIndex].clStorageInfo.clItem[0];

						// ������, ��, ��ȯ���� �����ȿ� �ֳ� Ȯ���Ѵ�.
						cltHouseUnitStorageInfo* pclstg = pclClient->pclHouseManager->GetStgPointer(VillageNo, HouseIndex);

						switch(pclchar->pclCI->clRealEstate.clRealEstate[Cnt].siType)
						{
							// â��.
						case 1:	
							{
								StringCchPrintf(TableStr, sizeof(TableStr), "wherehouseinfo%d", warehouseCnt);

								m_pSectionData->BeginData(TableStr);
								{	
									StringCchPrintf(TempStr, sizeof(TempStr), "village%d", warehouseCnt);
									m_pSectionData->AddDataStr( TempStr, VillageName );

									StringCchPrintf(TempStr, sizeof(TempStr), "rentperiod%d", warehouseCnt);
									m_pSectionData->AddDataStr( TempStr, buffer1 );

									char str[7]   = {'i', 't', 'e', 'm', NULL, NULL, NULL};
									char str2[64] = {NULL, };
									cltItemInfo* ItemInfo = NULL;

									for(SI32 i = 1; i <= MAX_HOUSEUNIT_STORAGE_ITEM_NUMBER; ++i)
									{
										if(pclstg->clItem[i-1].siUnique)
										{
											ItemInfo = pclClient->pclItemManager->FindItemInfo(pclstg->clItem[i-1].siUnique);
											StringCchPrintf(str2, sizeof(str2), "%s(%d)", (char*)ItemInfo->GetName(), pclstg->clItem[i-1].GetItemNum());

											itoa(i, &str[4], 10);
											m_pSectionData->AddDataStr(str, str2); 
										}
									}
								}
								++warehouseCnt;
								m_pSectionData->EndData(TableStr);


								// ���°�.
								m_pSectionData->BeginData( "stableinfo" );

								for(SI32 i = 0; i < MAX_HOUSEUNIT_HORSENUMBER; ++i)
								{
									// ���°��� �ִ�.
									if(pclstg->bCreatedHouseUnitStable[i])
									{
										StringCchPrintf(TableStr, sizeof(TableStr), "village%d", stableCnt);
										m_pSectionData->AddDataStr( TableStr,		VillageName );

										StringCchPrintf(TableStr, sizeof(TableStr), "rentperiod%d", stableCnt);
										m_pSectionData->AddDataStr( TableStr,	buffer1 );

										// �� ����ũ�� �� �̸� ���.
										char* pHorseName = pclClient->pclHorseManager->GetHorseName(pclstg->clHorse[stableCnt].siHorseUnique);
										StringCchPrintf(TableStr, sizeof(TableStr), "horse%d", stableCnt);
										m_pSectionData->AddDataStr( TableStr, pHorseName );

										++stableCnt;
									}
								}
								m_pSectionData->EndData( "stableinfo" );		
							}
							break;

							// ����.
						case 2: 
							{
								m_pSectionData->BeginData( "farminfo" );
								{
									m_pSectionData->AddDataStr( "village",		VillageName );
									m_pSectionData->AddDataStr( "rentperiod",	buffer1 );
								}
								m_pSectionData->EndData( "farminfo" );	
							}
							break;

							// ����.
						case 3:	
							{
								m_pSectionData->BeginData( "mineinfo" );
								{
									m_pSectionData->AddDataStr( "village",		VillageName );
									m_pSectionData->AddDataStr( "rentperiod",	buffer1 );
								}
								m_pSectionData->EndData( "mineinfo" );		
							}
							break;
						}
					}

					// ��ų �������� ����
					m_pSectionData->BeginData( "relestate_add" );
						m_pSectionData->AddDataInt( "personid", siPersonID );
					m_pSectionData->EndData( "relestate_add" );

					sGMResponse_Section sectionmsg( pRecvMsg->m_iPageID, pRecvMsg->m_szCharName, m_pSectionData );
					SendPacket( pSession, (sPacketHeader*)&sectionmsg ); 
				}
			}
			break;
	}

	printf( "�޽��� ���� : GMMSG_RESPONSE_SECTION\n" );
	// ������ ���� �˸�
	sGMResponse_EndPage endmsg( pRecvMsg->m_iPageID );
	SendPacket( pSession, (sPacketHeader*)&endmsg ); 
	printf( "�޽��� ���� : GMMSG_RESPONSE_ENDPAGE\n" );


}

TCHAR* SkillExplain(cltCharClient* _pclchar, SI32 _SkillUnique)
{
	cltCharClient* pclchar = _pclchar;

	static TCHAR Buffer[ 512 ] =  TEXT("");


	SI32 skillexp = 0;
	if(SKILL_USESWORD1 >= 0)
	{
		skillexp   = pclchar->pclCI->clCharSkill.clSkill[_SkillUnique].siSkillExp;
	}

	SI32 explevel	= pclchar->pclCI->clCharSkill.GetSkillExpLevel(_SkillUnique);

	TCHAR* pText = GetTxtFromMgr(675);

	StringCchPrintf( Buffer, 512, pText,
		pclchar->pclCI->clCharSkill.GetSkillLevel(_SkillUnique),
		pclClient->pclSkillManager->GetMaxLevel(_SkillUnique),
		pclClient->pclItemManager->GetUpgradeSkillLevel(&pclchar->pclCI->clCharItem.clItem[0], _SkillUnique,1),
		explevel,
		pclClient->pclSkillManager->GetMaxExpLevel(_SkillUnique),
		skillexp,
		GetRequiredSkillExpForLevel(explevel + 1));

	return Buffer;
}

void SummonAttackAndDeffence(cltParametaBox &clPB, SI32 &totalMinDamage, SI32 &totalMaxDamage, SI32 &totalAC)
{
	//----------------------------------------------------------------------------------------------------------
	// ���ݷ�, ���� ���.

	totalMinDamage = clPB.GetTotalMinDamage();
	totalMaxDamage = clPB.GetTotalMaxDamage();

	// ��ȯ���� �⺻������ ���ݷ� + 10% �� ���ʽ��� �޴´�
	totalMinDamage = totalMinDamage + (SI32)(totalMinDamage * 0.1f);
	totalMaxDamage = totalMaxDamage + (SI32)(totalMaxDamage * 0.1f);

	SI32 summonskill = 0;
	summonskill = pclClient->pclCM->CR[1]->pclCI->clCharSkill.GetTotalSkillLevel( SKILL_SUMMON, 0, 0, &pclClient->pclCM->CR[1]->pclCI->clCharItem.clItem[0], 1 );

	SI32 attackBonusPercent = 0;
	attackBonusPercent = pclClient->GetSummonAttackBonus( summonskill );

	// ��ȯ���� ���� ���ݷ� ���ʽ��� �޴´�.
	if( attackBonusPercent > 0 )
	{
		totalMinDamage = totalMinDamage + totalMinDamage * attackBonusPercent / 100;
		totalMaxDamage = totalMaxDamage + totalMaxDamage * attackBonusPercent / 100;
	}

	SI32 bonusPercent = 0;

	// ������ ���� ���ݷ� ���ʽ��� �޴´�.
	if( pclClient->pclCM->CR[1]->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_SUMMONATACUP) == true )
	{
		bonusPercent = max( bonusPercent, pclClient->pclCM->CR[1]->pclCI->clBI.clBufInfo.GetBufPercent(BUF_SUMMONATACUP) );
	}
	if( pclClient->pclCM->CR[1]->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_LOVEPOWER) == true )
	{
		bonusPercent = max( bonusPercent, 20 );
	}

	totalMinDamage += totalMinDamage * bonusPercent / 100;
	totalMaxDamage += totalMaxDamage * bonusPercent / 100;

	totalAC = clPB.GetTotalAC();

	SI32 defBonusPercent = 0;
	defBonusPercent = pclClient->GetSummonDefBonus( summonskill );

	if( defBonusPercent > 0 )
	{
		totalAC += totalAC * defBonusPercent / 100;
	}

	bonusPercent = 0;
	// ������ ���� ���ݷ� ���ʽ��� �޴´�.
	if( pclClient->pclCM->CR[1]->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_SUMMONATACUP) == true )
	{
		bonusPercent = max( bonusPercent, pclClient->pclCM->CR[1]->pclCI->clBI.clBufInfo.GetBufPercent(BUF_SUMMONATACUP) );
	}
	if( pclClient->pclCM->CR[1]->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_LOVEPOWER) == true )
	{
		bonusPercent = max( bonusPercent, 20 );
	}

	totalAC += totalAC * bonusPercent / 100;
}
void GMProtocol::Do_GMMSG_REQUEST_UPDATEDATA(ITZSession* pSession)
{
	// ���� �޽��� ó��
	sGMRequest_UpdateData* pRecvMsg = (sGMRequest_UpdateData*)m_pCurrentPacket;
	if ( pRecvMsg == NULL )					return;

	cltServer* pclserver = (cltServer*)pclClient;
	if ( pclserver == NULL )				return;
	
	cGMClient* pcGMClient = (cGMClient*)pSession->GetPerson();
	if ( pcGMClient == NULL )				return;

	if ( pcGMClient->GetMasterLevel() < BASIC_GAMEMASTER_LEVEL )	return;

	if ( m_pGMProtocol_Updata == NULL )		return;

	cltCharServer* pclChar = NULL;
	
	char	szCharName[MAX_PLAYER_NAME] = {'\0', };
	SI32	siCharID					= 0; 
	SI32	siPageID					= pRecvMsg->m_iQueryID / 1000;	// � �������ΰ�
	SI32	siButtonID					= pRecvMsg->m_iQueryID % 1000;	// � ��ư�� �����°�
	SI32	siReturnValue				= 0;							// ���� ��� ��
		
	// �ɸ��� �̸��� ���ؼ� ������ �������� �ɸ��� ������ �˻�
/*	strncpy( szCharName, pRecvMsg->m_szCharName, MAX_PLAYER_NAME );
	szCharName[ MAX_PLAYER_NAME-1 ] = NULL;

	siCharID = pclserver->pclCM->GetIDFromName( szCharName );
	
	// ���� �������� �ɸ��Ͷ�� �ɸ��͸� �޾ƿ�
	if ( pclserver->pclCM->IsValidID(siCharID) )
	{
		pclChar = (cltCharServer*)pclserver->pclCM->CR[siCharID];
	}*/

	// �� ���������� �ؾ��� �۾�
	switch ( siPageID ) 
	{
	case 1: // �⺻����
		{
			switch(siButtonID)
			{
			case UPDATA_ID_CHARINFO_REQUEST:
				{
					TCHAR	szInputCharname[64];
					pRecvMsg->GetDataStr( "charname", szInputCharname, sizeof(szInputCharname) );

					SI32 siClientID = pSession->GetPerson()->GetCharID();
					sDBRequest_BasicInfoByName clMsg( siClientID, szInputCharname, GMMSG_PAGEID_CHARINFO );
					pclClient->SendDBMsg(DBSELECT_LETTER, (sPacketHeader *)&clMsg);
				}
				break;
			}
		}
		break;
	}
	


	// �� ���������� �ؾ��� �۾�
/*	switch ( siPageID ) 
	{
		case 1: // �⺻����
			{
				pRecvMsg->m_iPageID = GMMSG_PAGEID_BASICINFO;
				siReturnValue = m_pGMProtocol_Updata->BasicInfoUpdata( pRecvMsg, siButtonID, pclChar );
			}
			break;

		case 2: // ��ų
			{
				pRecvMsg->m_iPageID = GMMSG_PAGEID_SKILLINFO;
			}
			break;

		case 3: // ����ǰ
			{
				pRecvMsg->m_iPageID = GMMSG_PAGEID_INVENTORY;
				siReturnValue = m_pGMProtocol_Updata->InventoryUpdata( pRecvMsg, siButtonID, pclChar );
			}
			break;

		case 4: // �ε���
			{
				pRecvMsg->m_iPageID = GMMSG_PAGEID_REALESTATE;
			}
			break;

		case 5: // ��ȯ��
			{
				pRecvMsg->m_iPageID = GMMSG_PAGEID_SUMMON;
			}
			break;

		case 6: // ����
			{
				pRecvMsg->m_iPageID = GMMSG_PAGEID_ANIMAL;
			}
			break;

		default:
			return;

	}
	WriteGMToolLog( pSession, siReturnValue );
*/
	Return_UpData_Processed_Message( pSession, siReturnValue );

}

void GMProtocol::Return_UpData_Processed_Message(ITZSession* pSession, SI32 siReturnValue)
{
	sGMRequest_UpdateData* pRecvMsg = (sGMRequest_UpdateData*)m_pCurrentPacket;
	if(pRecvMsg == NULL)	return;

	cltServer* pclserver = (cltServer*)pclClient;
	if (pclserver == NULL)	return;

	// �����޽��� ���� (�ӽ÷� ������ ���� ��)
	char szErrorMessage[][256] ={
		/*
		{"���ǵ��� ���� ����� �����Ͽ����ϴ�"}
		,{"�� ����� ������ �� �����ϴ�"}
		,{"�ɸ��Ͱ� �������� �ʽ��ϴ�"}
		,{"�� ��ɾ�� �ɸ��Ͱ� �������϶��� ��밡���մϴ�"}
		,{"�� ��ɾ�� �ɸ��Ͱ� �������� �ƴҶ��� ��밡���մϴ�"}
		,{"�ݾ� ������ �߸��Ǿ����ϴ�"}
		,{"���� ����ũ ������ �߸��Ǿ����ϴ�"}
		,{"�ֽ� �� ������ �߸��Ǿ����ϴ�"}
		,{"���� Ÿ�� ��ȣ�� �߸� �����Ǿ����ϴ�"}
		,{"���� ���� ��ȣ�� �߸� �����Ǿ����ϴ�"}
		,{"���� �ð� ������ �߸� �Ǿ����ϴ�."}
		,{"�ش� �̸��� �������� �������� �ʽ��ϴ�"}
		,{"������ ���� ������ �߸� �Ǿ����ϴ�"}
		,{"�������� ���� �κ��丮 ��ȣ�� �߸� �Ǿ����ϴ�."}
		,{"�ش� �������� ������ �� �����ϴ�"}
		*/
		{"Excuted undefined command."}
		,{"This command is not available."}
		,{"Character does not exist."}
		,{"You can use this command while the character is online."}
		,{"You can use this command while the character is not online."}
		,{"Incorrect amount of money."}
		,{"Town unique setting is incorrect."}
		,{"Number of share setting is incorrect."}
		,{"Effects type number setting is incorrect."}
		,{"Effect slot number setting is incorrect."}
		,{"Effect time setting is incorrect."}
		,{"No item under that name."}
		,{"Number of selected items is incorrect."}
		,{"Inventory number to store items is incorrect."}
		,{"Can not create the following item."}
	};

	// (Ȥ�ø� ����üũ) enum�� ���� �޽����� ���� �ؽ�Ʈ�� ���� ������ �������� �ʴ´�
	SI32 siCheckValue =  sizeof(szErrorMessage)/sizeof(char)/256;

	if ( siCheckValue != UPDATA_ERROR_MSG_END )
	{
		#ifdef _DEBUG
			MessageBox( NULL, "���� �޽��� ������ �߸��Ǿ����ϴ�", "�����޽��� ���� ����", MB_OK );
		#endif
		return;
	}


	// �޽��� ������ �˸�
	sGMResponse_BeginPage beginmsg( pRecvMsg->m_iPageID, pRecvMsg->m_szCharName );
	SendPacket( pSession, (sPacketHeader*)&beginmsg );
	////////////////////////////////////////////////////////////////////////////////////////////////////

	m_pSectionData->ClearData();

	m_pSectionData->BeginData( "show_result" );

	if ( siReturnValue == Const_UpData_Success )
	{
		m_pSectionData->AddDataStr( "result",	"Succeed" );
		m_pSectionData->AddDataStr( "reason",	"A successful operation" );
	}
	else
	{
		m_pSectionData->AddDataStr( "result",	"Failed" );
		m_pSectionData->AddDataStr( "reason",	szErrorMessage[siReturnValue] );
	}

	m_pSectionData->EndData( "show_result" );		

	sGMResponse_Section sectionmsg( pRecvMsg->m_iPageID, pRecvMsg->m_szCharName, m_pSectionData );
	SendPacket( pSession, (sPacketHeader*)&sectionmsg );

	// �޽��� ���Ḧ �˸�
	sGMResponse_EndPage endmsg( pRecvMsg->m_iPageID );
	SendPacket( pSession, (sPacketHeader*)&endmsg ); 
	////////////////////////////////////////////////////////////////////////////////////////////////////

}

void GMProtocol::WriteGMToolLog( ITZSession* pSession, SI32 siReturnValue )
{
	sGMRequest_UpdateData*	pRecvMsg = (sGMRequest_UpdateData*)m_pCurrentPacket;
	if ( pRecvMsg == NULL )		return;

	cltServer*				pclserver = (cltServer*)pclClient;
	if ( pclserver == NULL )	return;

	cGMClient*				pcGMClient = (cGMClient*)pSession->GetPerson();
	if ( pcGMClient == NULL )	return;
	
	
	TCHAR	szFileName[128]	= {'\0', };
	UI16	uiYear			= pclserver->sTime.wYear;
	UI16	uiMonth			= pclserver->sTime.wMonth;
	UI16	uiDay			= pclserver->sTime.wDay;
	FILE	*fp				= NULL;
	

	StringCchPrintf( szFileName, 128, TEXT("Config\\GMToolLog_%04d%02d%02d.log"), uiYear, uiMonth, uiDay );

	fp = _tfopen( szFileName, TEXT("a+") );
	if ( fp == NULL )		return;


	TCHAR	szGMName[MAX_PLAYER_NAME]	= {'\0', };
	TCHAR	szUserName[MAX_PLAYER_NAME]	= {'\0', };
	TCHAR	*pszData					= NULL;
	SI32	siPageID					= pRecvMsg->m_iPageID;
	SI32	siButtonID					= pRecvMsg->m_iQueryID % 1000;
	SI32	siDataSize					= pRecvMsg->m_iDataSize+1;

	
	pszData = new TCHAR[ siDataSize ];
	if ( pszData != NULL )
	{
		ZeroMemory( pszData, siDataSize );

		StringCchCopy( pszData, (siDataSize), pRecvMsg->m_data );
		pszData[ (siDataSize-1) ] = NULL;
	}
	

	StringCchCopy( szGMName, MAX_PLAYER_NAME, pcGMClient->GetID() );
	StringCchCopy( szUserName, MAX_PLAYER_NAME, pRecvMsg->m_szCharName );

	_ftprintf( fp, TEXT("GMName:%s\tPageID:%d\tButtonID:%d\tUserName:%s\tData:%s\tResult:%d\tSuccessValue:%d\n"), szGMName, siPageID, siButtonID, szUserName, pszData, siReturnValue, Const_UpData_Success );

	fclose( fp );

	if ( pszData != NULL )
	{
		delete [] pszData;
	}
}

// �޾ƿ� ���ڿ��� ������ ũ�⸸ŭ �߶� Ŭ��� ��Ŷ ����.
bool GMProtocol::SendInfofromServer( ITZSession* pSession , const char* pszFormat, ...)
{	
	TCHAR szBuf[MAX_INFOLINE_SIZE * 5];

	va_list valist;
	va_start(valist, pszFormat);
	try
	{
		// �ڵ������� ���� �޸� ��������� �����ϱ� ���� try�������� ����.
		StringCchVPrintf(szBuf, sizeof(szBuf), pszFormat, valist);
	}
	catch(...)
	{
	}
	va_end(valist);

	SI32 siStartPos = 0;
	SI32 siStrLen = strlen(szBuf);

	while(siStrLen > siStartPos)
	{
		sGMResponse_InfofromServer sendMsg( &szBuf[siStartPos] );
		SendPacket(pSession, (sPacketHeader*)&sendMsg);

		siStartPos += MAX_INFOLINE_SIZE;
	}

	return false;
}

// Ŭ��κ��� ���� ��Ŷ ó��
void GMProtocol::Do_GMMSG_REQUEST_GMCOMMAND(ITZSession* pSession)
{
	// ���� �޼��� ó��
	sGMRequest_GMCommand* pRecvMsg = (sGMRequest_GMCommand*) m_pCurrentPacket;
	if( pRecvMsg == NULL )				return;

	cltServer* pclserver = (cltServer*)pclClient;
	if ( pclserver == NULL )		return;

	TCHAR szOrder[64] = { '\0', };
	NTCHARString64 kOrder;

	_stscanf(pRecvMsg->m_szGMCommand, "%s", szOrder);	kOrder = szOrder;

	if( kOrder == "user" )
	{
		TCHAR szCharName[64] = { '\0', };

		_stscanf(pRecvMsg->m_szGMCommand, "%s %s", szOrder, szCharName);

		SI32 siClientID = pSession->GetPerson()->GetCharID();
		sDBRequest_BasicInfoByName clMsg( siClientID, szCharName, 0 );
		pclClient->SendDBMsg(DBSELECT_LETTER, (sPacketHeader *)&clMsg);
	}
	else if( kOrder == "charitem" )
	{
	}

	//SendInfofromServer(pSession, pRecvMsg->m_szGMCommand );
}