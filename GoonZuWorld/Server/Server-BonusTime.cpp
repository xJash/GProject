//---------------------------------
// 2004/11/5 ���°�
//---------------------------------

//----------------------------------
// Common
//----------------------------------
#include "../Common/CommonHeader.h"
#include "Char\CharManager\CharManager.h"

//---------------------------------
// Server
//---------------------------------
#include "../Server/Server.h"

#include "../Server/Minister/Minister-Goonzu.h"

//---------------------------------
// CommonLogic
//---------------------------------
#include "MsgType-System.h"

//---------------------------------
// DBManager
//---------------------------------
#include "../../DBManager/GameDBManager_World/DBMsg-Item.h"


// ���� ���ʽ� Ÿ�� 
void cltServer::MakeBonusTimeAction()
{
	static DWORD dwLastClock = 0;

	TCHAR buffer[256] = TEXT("");
	TCHAR szservicetimetxt[128] = TEXT("");

	bool bevent = false;

	if(bGMBonusTimeSwitch == 0)
	{
		if (GetFrame() % 3600)return ;
	}

	SI16 goonzuMakeBonusTime = -1;

	CMinisterGoonzu *pclministerGoonzu = (CMinisterGoonzu *)pclMinisterMgr->GetMinister(MINISTER_GOONZU);
	if ( pclministerGoonzu && 
		_tcslen(pclministerGoonzu->m_szAccountID) > 0 &&
		_tcslen(pclministerGoonzu->m_szPersonName) > 0 ) 
	{
		goonzuMakeBonusTime = pclministerGoonzu->m_siMakeBonusTime;
	}


	// ���ʽ� �ð�. 
	if (pclClient->siServiceArea == ConstServiceArea_English)
	{
		if( bDoNotAutoBonus == false)
		{
			if( bIsGMBonusTime2 == false && bGMBonusTimeSwitch == 0 )
			{
				if(sTime.wHour == 0|| sTime.wHour == 10 || sTime.wHour == 16 || sTime.wHour == goonzuMakeBonusTime )
				{
					bevent = true;

					if (sTime.wHour == 16)
					{
						StringCchCopy(szservicetimetxt, 128, TEXT("(PST 16:00~17:00)"));
					}
					else if (sTime.wHour == 0)
					{
						StringCchCopy(szservicetimetxt, 128, TEXT("(PST 00:00~01:00)"));
					}
					else if (sTime.wHour == 10)
					{
						StringCchCopy(szservicetimetxt, 128, TEXT("(PST 10:00~11:00)"));
					}
					else if ( sTime.wHour == goonzuMakeBonusTime )
					{
						TCHAR * pText = GetTxtFromMgr(6927);
						StringCchPrintf(szservicetimetxt , 128 , pText , goonzuMakeBonusTime);
					}
				}

				if(bevent)
				{
					if(bBonus2TimeSwitch == false)
					{
						bBonus2TimeSwitch = true;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_MAKE,  bBonus2TimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

					}

					// ��ü �������� �˸� �޽����� ������. 
					TCHAR * pText = GetTxtFromMgr(5384);
					sprintf(buffer,pText);
					SendNoticeMsg(-1, 0, 0, buffer);
					SendNoticeMsg(-1, 0, 0, szservicetimetxt);

				}
				else
				{
					if(bBonus2TimeSwitch == true)
					{
						// ��ü �������� �˸� �޽����� ������. 
						TCHAR * pText = GetTxtFromMgr(5385);
						sprintf(buffer,pText);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, buffer);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, szservicetimetxt);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]

						bBonus2TimeSwitch = false;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_MAKE,  bBonus2TimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

					}
				}

			}
		}
		else
		{
			if( bIsGMBonusTime2 == false && bGMBonusTimeSwitch == 0 )
			{
				if( sTime.wHour == goonzuMakeBonusTime )
				{
					bevent = true;


					TCHAR * pText = GetTxtFromMgr(6927);
					StringCchPrintf(szservicetimetxt , 128 , pText , goonzuMakeBonusTime);

				}

				if(bevent)
				{
					if(bBonus2TimeSwitch == false)
					{
						bBonus2TimeSwitch = true;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_MAKE,  bBonus2TimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

					}

					// ��ü �������� �˸� �޽����� ������. 
					TCHAR * pText = GetTxtFromMgr(5384);
					sprintf(buffer,pText);
					SendNoticeMsg(-1, 0, 0, buffer);
					SendNoticeMsg(-1, 0, 0, szservicetimetxt);

				}
				else
				{
					if(bBonus2TimeSwitch == true)
					{
						// ��ü �������� �˸� �޽����� ������. 
						TCHAR * pText = GetTxtFromMgr(5385);
						sprintf(buffer,pText);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, buffer);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, szservicetimetxt);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]

						bBonus2TimeSwitch = false;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_MAKE,  bBonus2TimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

					}
				}

			}

		}

	}
	else if (pclClient->siServiceArea == ConstServiceArea_USA)
	{
		if( bDoNotAutoBonus == false)
		{
			if( bIsGMBonusTime2 == false && bGMBonusTimeSwitch == 0 )
			{
				if ( sTime.wHour == goonzuMakeBonusTime )
				{
					bevent = true;

					TCHAR * pText = GetTxtFromMgr(6927);
					StringCchPrintf(szservicetimetxt , 128 , pText , goonzuMakeBonusTime);
				}


				if( sTime.wDayOfWeek == 0 )
				{
					SYSTEMTIME	start, end;
					ZeroMemory(&start, sizeof(start));
					ZeroMemory(&end, sizeof(end));

					start.wYear = 2008;		start.wMonth = 7;		start.wDay = 16;
					end.wYear	= 3008;		end.wMonth   = 9;		end.wDay   = 17;	end.wHour = 23;

					// ����� �Ϸ� ���� �̺�Ʈ
					if( TimeInBounds(&sTime, &start, &end) == true)
					{
						// �Ϸ����� �̺�Ʈ.
						bAlldayBonus = true;

						bevent = true;

						TCHAR * pText = GetTxtFromMgr(8414);
						StringCchPrintf(szservicetimetxt , 128 , pText , goonzuMakeBonusTime);
					}
				}


				if(bevent)
				{
					if(bBonus2TimeSwitch == false)
					{
						bBonus2TimeSwitch = true;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_MAKE,  bBonus2TimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);
					}

					// ��ü �������� �˸� �޽����� ������. 
					TCHAR * pText = GetTxtFromMgr(5384);
					sprintf(buffer,pText);
					SendNoticeMsg(-1, 0, 0, buffer);
					SendNoticeMsg(-1, 0, 0, szservicetimetxt);
				}
				else
				{
					// �Ϸ����� �̺�Ʈ.
					bAlldayBonus = false;

					if(bBonus2TimeSwitch == true)
					{
						// ��ü �������� �˸� �޽����� ������. 
						TCHAR * pText = GetTxtFromMgr(5385);
						sprintf(buffer,pText);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, buffer);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, szservicetimetxt);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]

						bBonus2TimeSwitch = false;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_MAKE,  bBonus2TimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);
					}
				}
			}
		}
		else
		{
			if( bIsGMBonusTime2 == false && bGMBonusTimeSwitch == 0 )
			{
				if( sTime.wHour == goonzuMakeBonusTime )
				{
					bevent = true;

					TCHAR * pText = GetTxtFromMgr(6927);
					StringCchPrintf(szservicetimetxt , 128 , pText , goonzuMakeBonusTime);
				}

				
				//[����] �Ͽ����� �Ϸ����� ���� ����ġ ���ʽ� ����.
				if( sTime.wDayOfWeek == 0 )
				{
					SYSTEMTIME	start, end;
					ZeroMemory(&start, sizeof(start));
					ZeroMemory(&end, sizeof(end));

					start.wYear = 2008;		start.wMonth = 7;		start.wDay = 16;
					end.wYear	= 2008;		end.wMonth   = 9;		end.wDay   = 17;	end.wHour = 23;

					// ����� �Ϸ� ���� �̺�Ʈ
					if( TimeInBounds(&sTime, &start, &end) == true)
					{
						// �Ϸ����� �̺�Ʈ.
						bAlldayBonus = true;

						bevent = true;

						TCHAR * pText = GetTxtFromMgr(8414);
						StringCchPrintf(szservicetimetxt , 128 , pText , goonzuMakeBonusTime);
					}
				}

				if(bevent)
				{
					if(bBonus2TimeSwitch == false)
					{
						bBonus2TimeSwitch = true;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_MAKE,  bBonus2TimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);
					}
					
					// ��ü �������� �˸� �޽����� ������. 
					TCHAR * pText = GetTxtFromMgr(5384);
					sprintf(buffer,pText);
					SendNoticeMsg(-1, 0, 0, buffer);
					SendNoticeMsg(-1, 0, 0, szservicetimetxt);

				}
				else
				{
					bAlldayBonus = false;
					
					if(bBonus2TimeSwitch == true)
					{
						// ��ü �������� �˸� �޽����� ������. 
						TCHAR * pText = GetTxtFromMgr(5385);
						sprintf(buffer,pText);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, buffer);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, szservicetimetxt);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]

						bBonus2TimeSwitch = false;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_MAKE,  bBonus2TimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

					}
				}
			}
		}
	}
	else if (pclClient->siServiceArea == ConstServiceArea_Japan)
	{
		if( bDoNotAutoBonus == false)
		{
			if( bIsGMBonusTime2 == false && bGMBonusTimeSwitch == 0 )
			{
				if(sTime.wHour == 15 || sTime.wHour == 22 || sTime.wHour == goonzuMakeBonusTime )
				{
					bevent = true;

					if (sTime.wHour == 15)
					{
						StringCchCopy(szservicetimetxt, 128, TEXT("(15:00~16:00)"));
					}
					else if (sTime.wHour == 22)
					{
						StringCchCopy(szservicetimetxt, 128, TEXT("(22:00~23:00)"));
					}
					else if ( sTime.wHour == goonzuMakeBonusTime )
					{
						TCHAR * pText = GetTxtFromMgr(6927);
						StringCchPrintf(szservicetimetxt , 128 , pText , goonzuMakeBonusTime);
					}
				}

				if(bevent)
				{
					if(bBonus2TimeSwitch == false)
					{
						bBonus2TimeSwitch = true;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_MAKE,  bBonus2TimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

					}

					// ��ü �������� �˸� �޽����� ������. 
					TCHAR * pText = GetTxtFromMgr(5384);
					sprintf(buffer,pText);
					SendNoticeMsg(-1, 0, 0, buffer);
					SendNoticeMsg(-1, 0, 0, szservicetimetxt);

				}
				else
				{
					if(bBonus2TimeSwitch == true)
					{
						// ��ü �������� �˸� �޽����� ������. 
						TCHAR * pText = GetTxtFromMgr(5385);
						sprintf(buffer,pText);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, buffer);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, szservicetimetxt);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]

						bBonus2TimeSwitch = false;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_MAKE,  bBonus2TimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

					}
				}

			}
		}
		else
		{
			if( bIsGMBonusTime2 == false && bGMBonusTimeSwitch == 0 )
			{
				if( sTime.wHour == goonzuMakeBonusTime )
				{
					bevent = true;


					TCHAR * pText = GetTxtFromMgr(6927);
					StringCchPrintf(szservicetimetxt , 128 , pText , goonzuMakeBonusTime);

				}

				if(bevent)
				{
					if(bBonus2TimeSwitch == false)
					{
						bBonus2TimeSwitch = true;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_MAKE,  bBonus2TimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

					}

					// ��ü �������� �˸� �޽����� ������. 
					TCHAR * pText = GetTxtFromMgr(5384);
					sprintf(buffer,pText);
					SendNoticeMsg(-1, 0, 0, buffer);
					SendNoticeMsg(-1, 0, 0, szservicetimetxt);

				}
				else
				{
					if(bBonus2TimeSwitch == true)
					{
						// ��ü �������� �˸� �޽����� ������. 
						TCHAR * pText = GetTxtFromMgr(5385);
						sprintf(buffer,pText);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, buffer);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, szservicetimetxt);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]

						bBonus2TimeSwitch = false;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_MAKE,  bBonus2TimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

					}
				}

			}
		}
	}
	//KHY - 0620 - ����S ���� ����ġ ���ʽ��ð� ����. ������ �̺�Ʈ�ð� �����Ҷ��� �ð����� ������ �س���.
	else if (pclClient->siServiceArea == ConstServiceArea_Korea)
	{
		if( bDoNotAutoBonus == false)
		{
			if( bIsGMBonusTime2 == false && bGMBonusTimeSwitch == 0 )
			{
				// �̺�Ʈ ���� 2007.08.10 - by LEEKH	//KHY -0814 -  20�� ���� �νð�(sTime.wHour >= 20 && sTime.wHour <= 22)
				if ( ((sTime.wHour >= 20 && sTime.wHour < 22) || sTime.wHour == goonzuMakeBonusTime 
					|| pclClient->pclEventTimeManager->InEventTime( TEXT("NewYear_ManufactureBonusTime"), &sTime ))
					// ���� �̺�Ʈ �Ⱓ������ �ٸ� ���ʽ� Ÿ���� �ߵ����� �ʰ� ������ ���� ���ʽ� Ÿ�Ӹ� ����ǵ��� ����
					&& (pclClient->pclEventTimeManager->InEventTime( TEXT("NewYear_AttackBonusTime"), &sTime ) == false)
				)
				//if(sTime.wHour == goonzuMakeBonusTime )
				{
					bevent = true;

					if ( pclClient->pclEventTimeManager->InEventTime( "NewYear_ManufactureBonusTime", &sTime ) == true )
					{
						StringCchCopy(szservicetimetxt, 128, TEXT("(00:00~23:59)"));
					}
					else if (sTime.wHour >= 20 && sTime.wHour < 22)
					{
						StringCchCopy(szservicetimetxt, 128, TEXT("(20:00~22:00)"));
					}
					else if ( sTime.wHour == goonzuMakeBonusTime )
					{
						TCHAR * pText = GetTxtFromMgr(6927);
						StringCchPrintf(szservicetimetxt , 128 , pText , goonzuMakeBonusTime);
					}
				}

				if(bevent)
				{
					if(bBonus2TimeSwitch == false)
					{
						bBonus2TimeSwitch = true;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_MAKE,  bBonus2TimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

					}

					// ��ü �������� �˸� �޽����� ������. 
					TCHAR * pText = GetTxtFromMgr(5384);
					sprintf(buffer,pText);
					SendNoticeMsg(-1, 0, 0, buffer);
					SendNoticeMsg(-1, 0, 0, szservicetimetxt);

				}
				else
				{
					if(bBonus2TimeSwitch == true)
					{
						// ��ü �������� �˸� �޽����� ������. 
						TCHAR * pText = GetTxtFromMgr(5385);
						sprintf(buffer,pText);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, buffer);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, szservicetimetxt);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]

						bBonus2TimeSwitch = false;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_MAKE,  bBonus2TimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

					}
				}

			}
		}
		else
		{
			if( bIsGMBonusTime2 == false && bGMBonusTimeSwitch == 0 )
			{
				if( sTime.wHour == goonzuMakeBonusTime )
				{
					bevent = true;

					TCHAR * pText = GetTxtFromMgr(6927);
					StringCchPrintf(szservicetimetxt , 128 , pText , goonzuMakeBonusTime);

				}

				if(bevent)
				{
					if(bBonus2TimeSwitch == false)
					{
						bBonus2TimeSwitch = true;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_MAKE,  bBonus2TimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

					}

					// ��ü �������� �˸� �޽����� ������. 
					TCHAR * pText = GetTxtFromMgr(5384);
					sprintf(buffer,pText);
					SendNoticeMsg(-1, 0, 0, buffer);
					SendNoticeMsg(-1, 0, 0, szservicetimetxt);

				}
				else
				{
					if(bBonus2TimeSwitch == true)
					{
						// ��ü �������� �˸� �޽����� ������. 
						TCHAR * pText = GetTxtFromMgr(5385);
						sprintf(buffer,pText);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, buffer);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, szservicetimetxt);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]

						bBonus2TimeSwitch = false;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_MAKE,  bBonus2TimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

					}
				}

			}

		}

	}

	// �븸 ���� ����ġ ���ʽ� Ÿ�� �߰� (PCK - 07.12.14)
	else if (pclClient->siServiceArea == ConstServiceArea_Taiwan)
	{
		if( bDoNotAutoBonus == false)
		{
			if( bIsGMBonusTime2 == false && bGMBonusTimeSwitch == 0 )
			{
				// [���� �̺�Ʈ 2008.01.10 - �迵�� �߰� : ���� �̺�Ʈ Ÿ�� ����]
				if ( pclClient->pclEventTimeManager->InEventTime( "NewYear_ManufactureBonusTime", &sTime ) == true )
				{
					bevent = true;

					StringCchCopy(szservicetimetxt, 128, TEXT("(00:00~23:59)"));
				}

				if( sTime.wHour == goonzuMakeBonusTime )
				{
					bevent = true;

					if ( sTime.wHour == goonzuMakeBonusTime )
					{
						TCHAR * pText = GetTxtFromMgr(6927);
						StringCchPrintf(szservicetimetxt , 128 , pText , goonzuMakeBonusTime);
					}
				}

				if(bevent)
				{
					if(bBonus2TimeSwitch == false)
					{
						bBonus2TimeSwitch = true;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_MAKE,  bBonus2TimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

					}

					// ��ü �������� �˸� �޽����� ������. 
					TCHAR * pText = GetTxtFromMgr(5384);
					sprintf(buffer,pText);
					SendNoticeMsg(-1, 0, 0, buffer);
					SendNoticeMsg(-1, 0, 0, szservicetimetxt);

				}
				else
				{
					if(bBonus2TimeSwitch == true)
					{
						// ��ü �������� �˸� �޽����� ������. 
						TCHAR * pText = GetTxtFromMgr(5385);
						sprintf(buffer,pText);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, buffer);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, szservicetimetxt);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]

						bBonus2TimeSwitch = false;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_MAKE,  bBonus2TimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

					}
				}

			}
		}
		else
		{
			if( bIsGMBonusTime2 == false && bGMBonusTimeSwitch == 0 )
			{
				if( sTime.wHour == goonzuMakeBonusTime )
				{
					bevent = true;


					TCHAR * pText = GetTxtFromMgr(6927);
					StringCchPrintf(szservicetimetxt , 128 , pText , goonzuMakeBonusTime);

				}

				if(bevent)
				{
					if(bBonus2TimeSwitch == false)
					{
						bBonus2TimeSwitch = true;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_MAKE,  bBonus2TimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

					}

					// ��ü �������� �˸� �޽����� ������. 
					TCHAR * pText = GetTxtFromMgr(5384);
					sprintf(buffer,pText);
					SendNoticeMsg(-1, 0, 0, buffer);
					SendNoticeMsg(-1, 0, 0, szservicetimetxt);

				}
				else
				{
					if(bBonus2TimeSwitch == true)
					{
						// ��ü �������� �˸� �޽����� ������. 
						TCHAR * pText = GetTxtFromMgr(5385);
						sprintf(buffer,pText);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, buffer);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, szservicetimetxt);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]

						bBonus2TimeSwitch = false;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_MAKE,  bBonus2TimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

					}
				}

			}
		}
	}

	// NHN CHINA ����ġ ���ʽ� Ÿ�� �߰� 
	else if (pclClient->siServiceArea == ConstServiceArea_NHNChina)
	{
		if( bDoNotAutoBonus == false)
		{
			if( bIsGMBonusTime2 == false && bGMBonusTimeSwitch == 0 )
			{
				if(sTime.wHour == 0|| sTime.wHour == 10 || sTime.wHour == 16 || sTime.wHour == goonzuMakeBonusTime )
				{
					bevent = true;

					if (sTime.wHour == 16)
					{
						StringCchCopy(szservicetimetxt, 128, TEXT("(PST 16:00~17:00)"));
					}
					else if (sTime.wHour == 0)
					{
						StringCchCopy(szservicetimetxt, 128, TEXT("(PST 00:00~01:00)"));
					}
					else if (sTime.wHour == 10)
					{
						StringCchCopy(szservicetimetxt, 128, TEXT("(PST 10:00~11:00)"));
					}
					else if ( sTime.wHour == goonzuMakeBonusTime )
					{
						TCHAR * pText = GetTxtFromMgr(6927);
						StringCchPrintf(szservicetimetxt , 128 , pText , goonzuMakeBonusTime);
					}
				}

				if(bevent)
				{
					if(bBonus2TimeSwitch == false)
					{
						bBonus2TimeSwitch = true;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_MAKE,  bBonus2TimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

					}

					// ��ü �������� �˸� �޽����� ������. 
					TCHAR * pText = GetTxtFromMgr(5384);
					sprintf(buffer,pText);
					SendNoticeMsg(-1, 0, 0, buffer);
					SendNoticeMsg(-1, 0, 0, szservicetimetxt);

				}
				else
				{
					if(bBonus2TimeSwitch == true)
					{
						// ��ü �������� �˸� �޽����� ������. 
						TCHAR * pText = GetTxtFromMgr(5385);
						sprintf(buffer,pText);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, buffer);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, szservicetimetxt);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]

						bBonus2TimeSwitch = false;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_MAKE,  bBonus2TimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

					}
				}

			}
		}
		else
		{
			if( bIsGMBonusTime2 == false && bGMBonusTimeSwitch == 0 )
			{
				if( sTime.wHour == goonzuMakeBonusTime )
				{
					bevent = true;


					TCHAR * pText = GetTxtFromMgr(6927);
					StringCchPrintf(szservicetimetxt , 128 , pText , goonzuMakeBonusTime);

				}

				if(bevent)
				{
					if(bBonus2TimeSwitch == false)
					{
						bBonus2TimeSwitch = true;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_MAKE,  bBonus2TimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

					}

					// ��ü �������� �˸� �޽����� ������. 
					TCHAR * pText = GetTxtFromMgr(5384);
					sprintf(buffer,pText);
					SendNoticeMsg(-1, 0, 0, buffer);
					SendNoticeMsg(-1, 0, 0, szservicetimetxt);

				}
				else
				{
					if(bBonus2TimeSwitch == true)
					{
						// ��ü �������� �˸� �޽����� ������. 
						TCHAR * pText = GetTxtFromMgr(5385);
						sprintf(buffer,pText);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, buffer);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, szservicetimetxt);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]

						bBonus2TimeSwitch = false;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_MAKE,  bBonus2TimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

					}
				}

			}

		}

	}
	else if (pclClient->siServiceArea == ConstServiceArea_EUROPE)
	{
		if( bDoNotAutoBonus == false)
		{
			if( bIsGMBonusTime2 == false && bGMBonusTimeSwitch == 0 )
			{
				if(sTime.wHour == 0|| sTime.wHour == 10 || sTime.wHour == 16 || sTime.wHour == goonzuMakeBonusTime )
				{
					bevent = true;

					if (sTime.wHour == 16)
					{
						StringCchCopy(szservicetimetxt, 128, TEXT("(PST 16:00~17:00)"));
					}
					else if (sTime.wHour == 0)
					{
						StringCchCopy(szservicetimetxt, 128, TEXT("(PST 00:00~01:00)"));
					}
					else if (sTime.wHour == 10)
					{
						StringCchCopy(szservicetimetxt, 128, TEXT("(PST 10:00~11:00)"));
					}
					else if ( sTime.wHour == goonzuMakeBonusTime )
					{
						TCHAR * pText = GetTxtFromMgr(6927);
						StringCchPrintf(szservicetimetxt , 128 , pText , goonzuMakeBonusTime);
					}
				}

				if(bevent)
				{
					if(bBonus2TimeSwitch == false)
					{
						bBonus2TimeSwitch = true;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_MAKE,  bBonus2TimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

					}

					// ��ü �������� �˸� �޽����� ������. 
					TCHAR * pText = GetTxtFromMgr(5384);
					sprintf(buffer,pText);
					SendNoticeMsg(-1, 0, 0, buffer);
					SendNoticeMsg(-1, 0, 0, szservicetimetxt);

				}
				else
				{
					if(bBonus2TimeSwitch == true)
					{
						// ��ü �������� �˸� �޽����� ������. 
						TCHAR * pText = GetTxtFromMgr(5385);
						sprintf(buffer,pText);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, buffer);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, szservicetimetxt);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]

						bBonus2TimeSwitch = false;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_MAKE,  bBonus2TimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

					}
				}

			}
		}
		else
		{
			if( bIsGMBonusTime2 == false && bGMBonusTimeSwitch == 0 )
			{
				if( sTime.wHour == goonzuMakeBonusTime )
				{
					bevent = true;


					TCHAR * pText = GetTxtFromMgr(6927);
					StringCchPrintf(szservicetimetxt , 128 , pText , goonzuMakeBonusTime);

				}

				if(bevent)
				{
					if(bBonus2TimeSwitch == false)
					{
						bBonus2TimeSwitch = true;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_MAKE,  bBonus2TimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

					}

					// ��ü �������� �˸� �޽����� ������. 
					TCHAR * pText = GetTxtFromMgr(5384);
					sprintf(buffer,pText);
					SendNoticeMsg(-1, 0, 0, buffer);
					SendNoticeMsg(-1, 0, 0, szservicetimetxt);

				}
				else
				{
					if(bBonus2TimeSwitch == true)
					{
						// ��ü �������� �˸� �޽����� ������. 
						TCHAR * pText = GetTxtFromMgr(5385);
						sprintf(buffer,pText);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, buffer);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, szservicetimetxt);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]

						bBonus2TimeSwitch = false;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_MAKE,  bBonus2TimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

					}
				}

			}

		}

	}

	if (bGMBonusTimeSwitch == 2)
	{
		//���� ����ġ
		if(bBonus2TimeSwitch)
		{
			cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_MAKE,  bBonus2TimeSwitch);
			cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

			/*
			// ��ü �������� �˸� �޽����� ������. 
			if( siGMBonusTime2Percent > 0 )
			{
			TCHAR * pText = GetTxtFromMgr(6972);
			TCHAR szBuffer[256];
			szBuffer[0] = 0;

			StringCchPrintf( szBuffer , 256 , pText , siGMBonusTime2Percent + 100 );

			SendNoticeMsg( -1, 0, 0, szBuffer );

			}
			else
			{
			TCHAR * pText = GetTxtFromMgr(5384);

			SendNoticeMsg( -1, 0, 0, pText );
			}*/

			bIsGMBonusTime2 = true;
		}
		else
		{
			// ��ü �������� �˸� �޽����� ������. 
			TCHAR* pText = GetTxtFromMgr(5385);
			sprintf(buffer,pText);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
			SendNoticeMsg(-1, 0, 0, buffer);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
			SendNoticeMsg(-1, 0, 0, szservicetimetxt);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]

			cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_MAKE,  bBonus2TimeSwitch);
			cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);
			bIsGMBonusTime2 = false;
		}

		bGMBonusTimeSwitch = 0;
	}


	if( bIsGMBonusTime2 ) // GM���ʽ� Ÿ������ �����鿡�� �޽����� �����Ѵ�
	{

		if( siGMBonusTime2Percent > 0 )
		{
			TCHAR * pText = GetTxtFromMgr(6972);
			TCHAR szBuffer[256];
			szBuffer[0] = 0;

			StringCchPrintf( szBuffer , 256 , pText , siGMBonusTime2Percent + 100 );

			SendNoticeMsg( -1, 0, 0, szBuffer );

		}
		else
		{
			TCHAR * pText = GetTxtFromMgr(5384);
			sprintf(buffer,pText);

			SendNoticeMsg( -1, 0, 0, buffer );
		}

	}

	/*
	// ���ʽ� �ð�. 
	if(sTime.wHour == 19)
	{
	bevent = true;
	}

	// ���ֿ��±���Ͽ��� 
	if(bDoubleBonusDaySwitch == true)
	{
	if(sTime.wHour == 20)
	{
	bevent	= true;
	}
	}

	// ���� Ÿ�� ���� Ȯ��. 
	if(bDoubleBonusDaySwitch)
	{
	if ( siServiceArea == ConstServiceArea_Korea )
	strcpy(szservicetimetxt, TEXT("(���� 7��~ 9��)"));
	else if(siServiceArea == ConstServiceArea_China)
	strcpy(szservicetimetxt, TEXT("(PM 7Hour~ 9Hour)"));
	else if(siServiceArea == ConstServiceArea_English)
	strcpy(szservicetimetxt, TEXT("(PM 7Hour~ 9Hour)"));
	}
	else
	{
	if ( siServiceArea == ConstServiceArea_Korea )
	strcpy(szservicetimetxt, TEXT("(���� 7��~ 8��)"));
	else if(siServiceArea == ConstServiceArea_China)
	strcpy(szservicetimetxt, TEXT("(PM 7Hour~ 8Hour)"));
	else if(siServiceArea == ConstServiceArea_English)
	strcpy(szservicetimetxt, TEXT("(PM 7Hour~ 8Hour)"));
	}

	if(bevent)
	{
	if(bBonus2TimeSwitch == false)
	{
	bBonus2TimeSwitch = true;

	cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_MAKE,  bBonus2TimeSwitch);
	cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
	pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

	}

	// ��ü �������� �˸� �޽����� ������. 
	TCHAR * pText = GetTxtFromMgr(5384);
	SendNoticeMsg(-1, 0, 0, pText);
	SendNoticeMsg(-1, 0, 0, szservicetimetxt);

	}
	else
	{
	if(bBonus2TimeSwitch == true)
	{
	// ��ü �������� �˸� �޽����� ������. 
	TCHAR * pText = GetTxtFromMgr(5385);
	SendNoticeMsg(-1, 0, 0, pText);
	SendNoticeMsg(-1, 0, 0, szservicetimetxt);

	bBonus2TimeSwitch = false;

	cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_MAKE,  bBonus2TimeSwitch);
	cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
	pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

	}
	}
	*/	
}


// ���� ���ʽ� Ÿ�� �׼�.
void cltServer::BattleBonusTimeAction()
{
	static DWORD dwLastClock = 0;

	if(bGMBonusTimeSwitch == 0)
	{
		if (GetFrame() % 3600)return ;
	}

	TCHAR buffer[256];
	TCHAR szservicetimetxt[128] = TEXT("");


	bool bevent = false;


	SI16 goonzuBonusTime = -1;

	CMinisterGoonzu *pclministerGoonzu = (CMinisterGoonzu *)pclMinisterMgr->GetMinister(MINISTER_GOONZU);
	if ( pclministerGoonzu && 
		_tcslen(pclministerGoonzu->m_szAccountID) > 0 &&
		_tcslen(pclministerGoonzu->m_szPersonName) > 0 ) 
	{
		goonzuBonusTime = pclministerGoonzu->m_siBonusTime;
	}


	// ���ʽ� �ð�. 
	if (pclClient->siServiceArea == ConstServiceArea_English )
	{
		if( bDoNotAutoBonus == false)
		{

			if ( bIsGMBonusTime == false && bGMBonusTimeSwitch == 0)
			{
				if(sTime.wHour == 9|| sTime.wHour == 15 || sTime.wHour == 23 || sTime.wHour == goonzuBonusTime )
				{
					bevent = true;

					if (sTime.wHour == 15)
					{
						StringCchCopy(szservicetimetxt, 128, TEXT("(PST 15:00~16:00)"));
					}
					else if (sTime.wHour == 23)
					{
						StringCchCopy(szservicetimetxt, 128, TEXT("(PST 23:00~00:00)"));
					}
					else if (sTime.wHour == 9)
					{
						StringCchCopy(szservicetimetxt, 128, TEXT("(PST 09:00~10:00)"));
					}
					else if(sTime.wHour == goonzuBonusTime )
					{
						TCHAR * pText = GetTxtFromMgr(6925);
						StringCchPrintf(szservicetimetxt , 128 , pText , goonzuBonusTime);
					}
				}

				if(bevent)
				{
					if(bBonusTimeSwitch == false)
					{
						bBonusTimeSwitch = true;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_NORMAL,  bBonusTimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

					}

					// ��ü �������� �˸� �޽����� ������. 
					TCHAR* pText = GetTxtFromMgr(3783);
					sprintf(buffer,pText);
					SendNoticeMsg(-1, 0, 0, buffer);
					SendNoticeMsg(-1, 0, 0, szservicetimetxt);


				}
				else
				{
					if(bBonusTimeSwitch == true)
					{
						// ��ü �������� �˸� �޽����� ������. 
						TCHAR* pText = GetTxtFromMgr(3784);
						sprintf(buffer,pText);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, buffer);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, szservicetimetxt);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]

						bBonusTimeSwitch = false;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_NORMAL,  bBonusTimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

					}
				}
			}
		}
		else
		{
			if ( bIsGMBonusTime == false && bGMBonusTimeSwitch == 0)
			{
				if( sTime.wHour == goonzuBonusTime )
				{
					bevent = true;

					TCHAR * pText = GetTxtFromMgr(6925);
					StringCchPrintf(szservicetimetxt , 128 , pText , goonzuBonusTime);

				}

				if(bevent)
				{
					if(bBonusTimeSwitch == false)
					{
						bBonusTimeSwitch = true;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_NORMAL,  bBonusTimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

					}

					// ��ü �������� �˸� �޽����� ������. 
					TCHAR* pText = GetTxtFromMgr(3783);
					sprintf(buffer,pText);
					SendNoticeMsg(-1, 0, 0, buffer);
					SendNoticeMsg(-1, 0, 0, szservicetimetxt);


				}
				else
				{
					if(bBonusTimeSwitch == true)
					{
						// ��ü �������� �˸� �޽����� ������. 
						TCHAR* pText = GetTxtFromMgr(3784);
						sprintf(buffer,pText);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, buffer);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, szservicetimetxt);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]

						bBonusTimeSwitch = false;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_NORMAL,  bBonusTimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

					}
				}
			}
		}
	}
	else if (pclClient->siServiceArea == ConstServiceArea_Japan )
	{
		if( bDoNotAutoBonus == false)
		{

			if ( bIsGMBonusTime == false && bGMBonusTimeSwitch == 0)
			{ 
				if(sTime.wHour == 14|| sTime.wHour == 21 || sTime.wHour == goonzuBonusTime )
				{
					bevent = true;

					if (sTime.wHour == 14)
					{
						StringCchCopy(szservicetimetxt, 128, TEXT("(14:00~15:00)"));
					}
					else if (sTime.wHour == 21)
					{
						StringCchCopy(szservicetimetxt, 128, TEXT("(21:00~22:00)"));
					}
					else if ( sTime.wHour == goonzuBonusTime )
					{
						TCHAR * pText = GetTxtFromMgr(6925);
						StringCchPrintf(szservicetimetxt , 128 , pText , goonzuBonusTime);
					}

				}

				if(bevent)
				{
					if(bBonusTimeSwitch == false)
					{
						bBonusTimeSwitch = true;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_NORMAL,  bBonusTimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

					}

					// ��ü �������� �˸� �޽����� ������. 
					TCHAR* pText = GetTxtFromMgr(3783);
					sprintf(buffer,pText);
					SendNoticeMsg(-1, 0, 0, buffer);
					SendNoticeMsg(-1, 0, 0, szservicetimetxt);


				}
				else
				{
					if(bBonusTimeSwitch == true)
					{
						// ��ü �������� �˸� �޽����� ������. 
						TCHAR* pText = GetTxtFromMgr(3784);
						sprintf(buffer,pText);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, buffer);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, szservicetimetxt);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]


						bBonusTimeSwitch = false;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_NORMAL,  bBonusTimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

					}
				}
			}
		}
		else
		{

			if ( bIsGMBonusTime == false && bGMBonusTimeSwitch == 0)
			{ 
				if( sTime.wHour == goonzuBonusTime )
				{
					bevent = true;

					TCHAR * pText = GetTxtFromMgr(6925);
					StringCchPrintf(szservicetimetxt , 128 , pText , goonzuBonusTime);
				}

				if(bevent)
				{
					if(bBonusTimeSwitch == false)
					{
						bBonusTimeSwitch = true;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_NORMAL,  bBonusTimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

					}

					// ��ü �������� �˸� �޽����� ������. 
					TCHAR* pText = GetTxtFromMgr(3783);
					sprintf(buffer,pText);
					SendNoticeMsg(-1, 0, 0, buffer);
					SendNoticeMsg(-1, 0, 0, szservicetimetxt);


				}
				else
				{
					if(bBonusTimeSwitch == true)
					{
						// ��ü �������� �˸� �޽����� ������. 
						TCHAR* pText = GetTxtFromMgr(3784);
						sprintf(buffer,pText);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, buffer);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, szservicetimetxt);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]


						bBonusTimeSwitch = false;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_NORMAL,  bBonusTimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

					}
				}
			}
		}
	}
	//KHY - 0620 - ����S ���ʽ� �ð� ����.
	else if (pclClient->siServiceArea == ConstServiceArea_Korea )
	{
		if( bDoNotAutoBonus == false)
		{
			if ( bIsGMBonusTime == false && bGMBonusTimeSwitch == 0)
			{ 
				// �̺�Ʈ ���� - 2007-08-10 by LEEKH
				if ( ((sTime.wHour >= 20 && sTime.wHour < 22)||sTime.wHour == goonzuBonusTime 
					|| pclClient->pclEventTimeManager->InEventTime( TEXT("NewYear_AttackBonusTime"), &sTime ))
					// ���� �̺�Ʈ �Ⱓ������ �ٸ� ���ʽ� Ÿ���� �ߵ����� �ʰ� ������ ���� ���ʽ� Ÿ�Ӹ� ����ǵ��� ����
					&& (pclClient->pclEventTimeManager->InEventTime( TEXT("NewYear_ManufactureBonusTime"), &sTime ) == false)
				)
				//if(sTime.wHour == goonzuBonusTime )
				{
					bevent = true;

					if ( pclClient->pclEventTimeManager->InEventTime( TEXT("NewYear_AttackBonusTime"), &sTime ) == true )
					{
						StringCchCopy(szservicetimetxt, 128, TEXT("(00:00~23:59)"));
					}
					else if (sTime.wHour >= 20 && sTime.wHour < 22)
					{
						StringCchCopy(szservicetimetxt, 128, TEXT("(20:00~22:00)"));
					}
					else if ( sTime.wHour == goonzuBonusTime )
					{
						TCHAR * pText = GetTxtFromMgr(6925);
						StringCchPrintf(szservicetimetxt , 128 , pText , goonzuBonusTime);
					}
				}

				if(bevent)
				{
					if(bBonusTimeSwitch == false)
					{
						bBonusTimeSwitch = true;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_NORMAL,  bBonusTimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);
					}

					// ��ü �������� �˸� �޽����� ������. 
					TCHAR* pText = GetTxtFromMgr(3783);
					sprintf(buffer,pText);
					SendNoticeMsg(-1, 0, 0, buffer);
					SendNoticeMsg(-1, 0, 0, szservicetimetxt);
				}
				else
				{
					if(bBonusTimeSwitch == true)
					{
						// ��ü �������� �˸� �޽����� ������.
						TCHAR* pText = GetTxtFromMgr(3784);
						sprintf(buffer,pText);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, buffer);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, szservicetimetxt);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]


						bBonusTimeSwitch = false;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_NORMAL,  bBonusTimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);
					}
				}
			}
		}
		else
		{
			if ( bIsGMBonusTime == false && bGMBonusTimeSwitch == 0)
			{ 
				if( sTime.wHour == goonzuBonusTime )
				{
					bevent = true;

					TCHAR * pText = GetTxtFromMgr(6925);
					StringCchPrintf(szservicetimetxt , 128 , pText , goonzuBonusTime);
				}

				if(bevent)
				{
					if(bBonusTimeSwitch == false)
					{
						bBonusTimeSwitch = true;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_NORMAL,  bBonusTimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

					}

					// ��ü �������� �˸� �޽����� ������. 
					TCHAR* pText = GetTxtFromMgr(3783);
					sprintf(buffer,pText);
					SendNoticeMsg(-1, 0, 0, buffer);
					SendNoticeMsg(-1, 0, 0, szservicetimetxt);
				}
				else
				{
					if(bBonusTimeSwitch == true)
					{
						// ��ü �������� �˸� �޽����� ������. 
						TCHAR* pText = GetTxtFromMgr(3784);
						sprintf(buffer,pText);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, buffer);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, szservicetimetxt);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]


						bBonusTimeSwitch = false;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_NORMAL,  bBonusTimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

					}
				}
			}
		}
	}
	// �̱��� �̺�Ʈ Ÿ��
	else if (pclClient->siServiceArea == ConstServiceArea_USA )
	{
		if( bDoNotAutoBonus == false)
		{
			if ( bIsGMBonusTime == false && bGMBonusTimeSwitch == 0)
			{
				SYSTEMTIME	start, end;
				ZeroMemory(&start, sizeof(start));
				ZeroMemory(&end, sizeof(end));

				start.wYear = 2008;		start.wMonth = 7;		start.wDay = 16;
				end.wYear	= 3008;		end.wMonth   = 9;		end.wDay   = 17;	end.wHour = 23;

				// ����� �Ϸ� ���� �̺�Ʈ
				if( TimeInBounds(&sTime, &start, &end) == true && sTime.wDayOfWeek == 6 )
				{
					bevent = true;

					StringCchCopy(szservicetimetxt, 128, TEXT("(For a day)"));

					// ��ü �������� �˸� �޽����� ������. 
					//[����] �ߺ� 2ȸ ������� �Ʒ����� ����ϹǷ� ����� ����~ => 2008-5-7
					/*
						TCHAR* pText = GetTxtFromMgr(7971);
						sprintf(buffer, pText);
						SendNoticeMsg(-1, 0, 0, buffer);
						SendNoticeMsg(-1, 0, 0, szservicetimetxt);
					*/
				}
				else if ( sTime.wHour == goonzuBonusTime )
				{
					bevent = true;
					bBonusTimeGoonzu = true;
				}

				if(bevent)
				{
					if(bBonusTimeSwitch == false)
					{
						bBonusTimeSwitch = true;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_NORMAL,  bBonusTimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);
					}
					
					if( sTime.wDayOfWeek == 6 )
					{
						// �Ϸ����� �̺�Ʈ.
						bAlldayBonus = true;

						// ��ü �������� �˸� �޽����� ������. 
						TCHAR* pText = GetTxtFromMgr(7971);
						sprintf(buffer,pText);					//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, buffer);		//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
					}
					else if(true == bBonusTimeGoonzu)
					{
						TCHAR * pText = GetTxtFromMgr(6925);
						StringCchPrintf(buffer, 128 , pText , goonzuBonusTime);
						SendNoticeMsg(-1, 0, 0, buffer);
					}
				}
				else
				{
					//if( sTime.wDayOfWeek != 6 )
					//{
					//	// ��ü �������� �˸� �޽����� ������. 
					//	TCHAR* pText = GetTxtFromMgr(7972);
					//	sprintf(buffer,pText);					//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
					//	SendNoticeMsg(-1, 0, 0, buffer);		//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
					//}

					// ���� ���ʽ� Ÿ���ε� ���Ḧ �ϸ� �޽����� ������.
					if(true == bBonusTimeGoonzu)
					{
						// ��ü �������� �˸� �޽����� ������. 
						TCHAR* pText = GetTxtFromMgr(3784);
						sprintf(buffer, pText);				//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, buffer);	//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
					}

					
					if(bBonusTimeSwitch == true)
					{
						// �Ϸ����� �̺�Ʈ.
						bAlldayBonus = false;

						bBonusTimeSwitch = false;
						bBonusTimeGoonzu = false;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_NORMAL,  bBonusTimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

					}
				}
			}
		}
		else
		{
			if ( bIsGMBonusTime == false && bGMBonusTimeSwitch == 0)
			{
				if( sTime.wHour == goonzuBonusTime )
				{
					bevent = true;

					TCHAR * pText = GetTxtFromMgr(6925);
					StringCchPrintf(szservicetimetxt , 128 , pText , goonzuBonusTime);

				}

				if(bevent)
				{
					if(bBonusTimeSwitch == false)
					{
						bBonusTimeSwitch = true;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_NORMAL,  bBonusTimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

					}

					// ��ü �������� �˸� �޽����� ������. 
					TCHAR* pText = GetTxtFromMgr(3783);
					sprintf(buffer,pText);
					SendNoticeMsg(-1, 0, 0, buffer);
					SendNoticeMsg(-1, 0, 0, szservicetimetxt);


				}
				else
				{
					if(bBonusTimeSwitch == true)
					{
						// ��ü �������� �˸� �޽����� ������. 
						TCHAR* pText = GetTxtFromMgr(3784);
						sprintf(buffer,pText);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, buffer);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, szservicetimetxt);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]

						bBonusTimeSwitch = false;
						bBonusTimeGoonzu = false;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_NORMAL,  bBonusTimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

					}
				}
			}
		}
	}
	// �븸 �������ʽ� Ÿ�� �ð� (PCK - 07.12.14)
	else if (pclClient->siServiceArea == ConstServiceArea_Taiwan )
	{
		if( bDoNotAutoBonus == false)
		{

			if ( bIsGMBonusTime == false && bGMBonusTimeSwitch == 0)
			{ 
				// [���� �̺�Ʈ 2008.01.10 - �迵�� �߰� : ���� �̺�Ʈ Ÿ�� ����]
				if ( pclClient->pclEventTimeManager->InEventTime( TEXT("NewYear_AttackBonusTime"), &sTime ) == true )
				{
					bevent = true;

					StringCchCopy(szservicetimetxt, 128, TEXT("(00:00~23:59)"));
				}

				if( sTime.wHour == goonzuBonusTime )
				{
					bevent = true;

					if ( sTime.wHour == goonzuBonusTime )
					{
						TCHAR * pText = GetTxtFromMgr(6925);
						StringCchPrintf(szservicetimetxt , 128 , pText , goonzuBonusTime);
					}
				}

				if(bevent)
				{
					if(bBonusTimeSwitch == false)
					{
						bBonusTimeSwitch = true;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_NORMAL,  bBonusTimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

					}

					// ��ü �������� �˸� �޽����� ������. 
					TCHAR* pText = GetTxtFromMgr(3783);
					sprintf(buffer,pText);
					SendNoticeMsg(-1, 0, 0, buffer);
					SendNoticeMsg(-1, 0, 0, szservicetimetxt);


				}
				else
				{
					if(bBonusTimeSwitch == true)
					{
						// ��ü �������� �˸� �޽����� ������. 
						TCHAR* pText = GetTxtFromMgr(3784);
						sprintf(buffer,pText);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, buffer);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, szservicetimetxt);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]


						bBonusTimeSwitch = false;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_NORMAL,  bBonusTimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

					}
				}
			}
		}
		else
		{

			if ( bIsGMBonusTime == false && bGMBonusTimeSwitch == 0)
			{ 
				if( sTime.wHour == goonzuBonusTime )
				{
					bevent = true;

					TCHAR * pText = GetTxtFromMgr(6925);
					StringCchPrintf(szservicetimetxt , 128 , pText , goonzuBonusTime);
				}

				if(bevent)
				{
					if(bBonusTimeSwitch == false)
					{
						bBonusTimeSwitch = true;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_NORMAL,  bBonusTimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

					}

					// ��ü �������� �˸� �޽����� ������. 
					TCHAR* pText = GetTxtFromMgr(3783);
					sprintf(buffer,pText);
					SendNoticeMsg(-1, 0, 0, buffer);
					SendNoticeMsg(-1, 0, 0, szservicetimetxt);


				}
				else
				{
					if(bBonusTimeSwitch == true)
					{
						// ��ü �������� �˸� �޽����� ������. 
						TCHAR* pText = GetTxtFromMgr(3784);
						sprintf(buffer,pText);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, buffer);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, szservicetimetxt);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]


						bBonusTimeSwitch = false;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_NORMAL,  bBonusTimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

					}
				}
			}
		}
	}

	// NHNCHINA ���� ���ʽ� Ÿ�� �ð�.
	else if (pclClient->siServiceArea == ConstServiceArea_NHNChina )
	{
		if( bDoNotAutoBonus == false)
		{

			if ( bIsGMBonusTime == false && bGMBonusTimeSwitch == 0)
			{
				if(sTime.wHour == 9|| sTime.wHour == 15 || sTime.wHour == 23 || sTime.wHour == goonzuBonusTime )
				{
					bevent = true;

					if (sTime.wHour == 15)
					{
						StringCchCopy(szservicetimetxt, 128, TEXT("(PST 15:00~16:00)"));
					}
					else if (sTime.wHour == 23)
					{
						StringCchCopy(szservicetimetxt, 128, TEXT("(PST 23:00~00:00)"));
					}
					else if (sTime.wHour == 9)
					{
						StringCchCopy(szservicetimetxt, 128, TEXT("(PST 09:00~10:00)"));
					}
					else if(sTime.wHour == goonzuBonusTime )
					{
						TCHAR * pText = GetTxtFromMgr(6925);
						StringCchPrintf(szservicetimetxt , 128 , pText , goonzuBonusTime);
					}
				}

				if(bevent)
				{
					if(bBonusTimeSwitch == false)
					{
						bBonusTimeSwitch = true;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_NORMAL,  bBonusTimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

					}

					// ��ü �������� �˸� �޽����� ������. 
					TCHAR* pText = GetTxtFromMgr(3783);
					sprintf(buffer,pText);
					SendNoticeMsg(-1, 0, 0, buffer);
					SendNoticeMsg(-1, 0, 0, szservicetimetxt);


				}
				else
				{
					if(bBonusTimeSwitch == true)
					{
						// ��ü �������� �˸� �޽����� ������. 
						TCHAR* pText = GetTxtFromMgr(3784);
						sprintf(buffer,pText);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, buffer);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, szservicetimetxt);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]

						bBonusTimeSwitch = false;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_NORMAL,  bBonusTimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

					}
				}
			}
		}
		else
		{
			if ( bIsGMBonusTime == false && bGMBonusTimeSwitch == 0)
			{
				if( sTime.wHour == goonzuBonusTime )
				{
					bevent = true;

					TCHAR * pText = GetTxtFromMgr(6925);
					StringCchPrintf(szservicetimetxt , 128 , pText , goonzuBonusTime);

				}

				if(bevent)
				{
					if(bBonusTimeSwitch == false)
					{
						bBonusTimeSwitch = true;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_NORMAL,  bBonusTimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

					}

					// ��ü �������� �˸� �޽����� ������. 
					TCHAR* pText = GetTxtFromMgr(3783);
					sprintf(buffer,pText);
					SendNoticeMsg(-1, 0, 0, buffer);
					SendNoticeMsg(-1, 0, 0, szservicetimetxt);


				}
				else
				{
					if(bBonusTimeSwitch == true)
					{
						// ��ü �������� �˸� �޽����� ������. 
						TCHAR* pText = GetTxtFromMgr(3784);
						sprintf(buffer,pText);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, buffer);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, szservicetimetxt);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]

						bBonusTimeSwitch = false;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_NORMAL,  bBonusTimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

					}
				}
			}
		}
	}
	else if (pclClient->siServiceArea == ConstServiceArea_EUROPE )
	{
		if( bDoNotAutoBonus == false)
		{

			if ( bIsGMBonusTime == false && bGMBonusTimeSwitch == 0)
			{
				if(sTime.wHour == 9|| sTime.wHour == 15 || sTime.wHour == 23 || sTime.wHour == goonzuBonusTime )
				{
					bevent = true;

					if (sTime.wHour == 15)
					{
						StringCchCopy(szservicetimetxt, 128, TEXT("(PST 15:00~16:00)"));
					}
					else if (sTime.wHour == 23)
					{
						StringCchCopy(szservicetimetxt, 128, TEXT("(PST 23:00~00:00)"));
					}
					else if (sTime.wHour == 9)
					{
						StringCchCopy(szservicetimetxt, 128, TEXT("(PST 09:00~10:00)"));
					}
					else if(sTime.wHour == goonzuBonusTime )
					{
						TCHAR * pText = GetTxtFromMgr(6925);
						StringCchPrintf(szservicetimetxt , 128 , pText , goonzuBonusTime);
					}
				}

				if(bevent)
				{
					if(bBonusTimeSwitch == false)
					{
						bBonusTimeSwitch = true;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_NORMAL,  bBonusTimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

					}

					// ��ü �������� �˸� �޽����� ������. 
					TCHAR* pText = GetTxtFromMgr(3783);
					sprintf(buffer,pText);
					SendNoticeMsg(-1, 0, 0, buffer);
					SendNoticeMsg(-1, 0, 0, szservicetimetxt);


				}
				else
				{
					if(bBonusTimeSwitch == true)
					{
						// ��ü �������� �˸� �޽����� ������. 
						TCHAR* pText = GetTxtFromMgr(3784);
						sprintf(buffer,pText);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, buffer);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, szservicetimetxt);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]

						bBonusTimeSwitch = false;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_NORMAL,  bBonusTimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

					}
				}
			}
		}
		else
		{
			if ( bIsGMBonusTime == false && bGMBonusTimeSwitch == 0)
			{
				if( sTime.wHour == goonzuBonusTime )
				{
					bevent = true;

					TCHAR * pText = GetTxtFromMgr(6925);
					StringCchPrintf(szservicetimetxt , 128 , pText , goonzuBonusTime);

				}

				if(bevent)
				{
					if(bBonusTimeSwitch == false)
					{
						bBonusTimeSwitch = true;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_NORMAL,  bBonusTimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

					}

					// ��ü �������� �˸� �޽����� ������. 
					TCHAR* pText = GetTxtFromMgr(3783);
					sprintf(buffer,pText);
					SendNoticeMsg(-1, 0, 0, buffer);
					SendNoticeMsg(-1, 0, 0, szservicetimetxt);


				}
				else
				{
					if(bBonusTimeSwitch == true)
					{
						// ��ü �������� �˸� �޽����� ������. 
						TCHAR* pText = GetTxtFromMgr(3784);
						sprintf(buffer,pText);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, buffer);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]
						SendNoticeMsg(-1, 0, 0, szservicetimetxt);//%�� ������ �ʵ��� �߰�. [2007.07.05 ����]

						bBonusTimeSwitch = false;

						cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_NORMAL,  bBonusTimeSwitch);
						cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

					}
				}
			}
		}
	}

	if (bGMBonusTimeSwitch == 1)
	{
		if(bBonusTimeSwitch)
		{
			cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_NORMAL,  bBonusTimeSwitch);
			cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);


			// ��ü �������� �˸� �޽����� ������. 
			/*
			if( siGMBonusTimePercent > 0 )
			{
			TCHAR * pText = GetTxtFromMgr(6971);
			TCHAR szBuffer[256];
			szBuffer[0] = 0;

			StringCchPrintf( szBuffer , 256 , pText , siGMBonusTimePercent + 100 );  // 30% �����ϰ�� 130% �� ǥ�����ش�

			SendNoticeMsg( -1, 0, 0, szBuffer );

			}
			else
			{
			TCHAR * pText = GetTxtFromMgr(3783);

			SendNoticeMsg( -1, 0, 0, pText );
			}
			*/

			bIsGMBonusTime = true;
		}
		else
		{
			// ��ü �������� �˸� �޽����� ������. 
			TCHAR* pText = GetTxtFromMgr(3784);
			SendNoticeMsg(-1, 0, 0, pText);
			//SendNoticeMsg(-1, 0, 0, szservicetimetxt);

			cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_NORMAL,  bBonusTimeSwitch);
			cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

			bIsGMBonusTime = false;
		}

		bGMBonusTimeSwitch = 0;
	}


	if( bIsGMBonusTime ) // GM���ʽ� Ÿ������ �����鿡�� �޽����� �����Ѵ�
	{

		if( siGMBonusTimePercent > 0 )
		{
			TCHAR * pText = GetTxtFromMgr(6971);
			TCHAR szBuffer[256];
			szBuffer[0] = 0;

			StringCchPrintf( szBuffer , 256 , pText , siGMBonusTimePercent + 100 );  // 30% �����ϰ�� 130% �� ǥ�����ش�

			SendNoticeMsg( -1, 0, 0, szBuffer );

		}
		else
		{
			TCHAR * pText = GetTxtFromMgr(3783);
			sprintf(buffer, pText);

			SendNoticeMsg( -1, 0, 0, buffer );
		}

	}

	/*
	// ���ʽ� �ð�. 
	if(sTime.wHour == 18 || sTime.wHour == 22 )//|| sTime.wHour == 1)
	{
	bevent = true;
	}

	// ���ֿ��±�����̶� ��̳�����
	if(bDoubleBonusDaySwitch || bSpecailDay8switch )
	{
	if(sTime.wHour == 17 || sTime.wHour == 21 )//|| sTime.wHour == 2 )
	{
	bevent	= true;
	}
	}

	// ���� Ÿ�� ���� Ȯ��. 
	if(bDoubleBonusDaySwitch || bSpecailDay8switch )
	{
	if ( siServiceArea == ConstServiceArea_Korea ) 
	strcpy(szservicetimetxt, TEXT("(���� 5��~ 7��, �� 9�� ~ 11��)"));//, ���� 1�� ~ 3��)");
	else if ( siServiceArea == ConstServiceArea_China)
	strcpy(szservicetimetxt, TEXT("(PM 5Hour~ 7Hour, PM 9Hour ~ 11Hour)"));//, AM 1Hour ~ 3Hour)");
	else if ( siServiceArea == ConstServiceArea_English)
	strcpy(szservicetimetxt, TEXT("(PM 5Hour~ 7Hour, PM 9Hour ~ 11Hour)"));//, AM 1Hour ~ 3Hour)");
	}
	else
	{
	if ( siServiceArea == ConstServiceArea_Korea )
	strcpy(szservicetimetxt, TEXT("(���� 6��~ 7��, �� 10�� ~ 11��)"));//, ���� 1�� ~ 2��)");
	else if( siServiceArea == ConstServiceArea_China)
	strcpy(szservicetimetxt, TEXT("(PM 6Hour~ 7Hour, PM 10Hour ~ 11Hour)"));//, AM 1Hour ~ 2Hour)");
	else if( siServiceArea == ConstServiceArea_English)
	strcpy(szservicetimetxt, TEXT("(PM 6Hour~ 7Hour, PM 10Hour ~ 11Hour)"));//, AM 1Hour ~ 2Hour)");
	}

	if(bevent)
	{
	if(bBonusTimeSwitch == false)
	{
	bBonusTimeSwitch = true;

	cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_NORMAL,  bBonusTimeSwitch);
	cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
	pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

	}

	// ��ü �������� �˸� �޽����� ������. 
	TCHAR* pText = GetTxtFromMgr(3783);
	sprintf(buffer,pText);
	SendNoticeMsg(-1, 0, 0, buffer);
	SendNoticeMsg(-1, 0, 0, szservicetimetxt);


	}
	else
	{
	if(bBonusTimeSwitch == true)
	{
	// ��ü �������� �˸� �޽����� ������. 
	TCHAR* pText = GetTxtFromMgr(3784);
	SendNoticeMsg(-1, 0, 0, pText);
	SendNoticeMsg(-1, 0, 0, szservicetimetxt);

	bBonusTimeSwitch = false;

	cltGameMsgResponse_BonusTime clinfo(BONUSTIMEMODE_NORMAL,  bBonusTimeSwitch);
	cltMsg clMsg(GAMEMSG_RESPONSE_BONUSTIME, 	sizeof(clinfo), (BYTE*)&clinfo);
	pclCM->SendAllPersonMsg((sPacketHeader *)&clMsg);

	}
	}
	*/	
}

//[�߰� : Ȳ���� 2007. 11. 1 ������ �ִ� ������� �ڵ带 �����Ͽ� Ȯ�尡���ϰ� ������]
void cltServer::SpecialQuestAction()
{
	class MagicLamp
	{	
		private:
		public:
			bool	m_bGiveSwitch;			// �ֳ� ����.
			WORD	m_wDay;					// ��.
			WORD	m_wHour;				// ��.
			WORD	m_wMinute;				// ��.
			WORD	m_wSecond;				// ��.
			WORD	m_wUserLevel;			// ���� ���� ����.
		
			MagicLamp(BYTE _Day = -1, BYTE _Hour = -1, BYTE _Minute = -1, BYTE	_Second = -1, BYTE _UserLevel = -1, bool _GiveSwitch = FALSE)
			{
				m_bGiveSwitch = _GiveSwitch;
				m_wDay		  = _Day;
				m_wHour		  = _Hour;
				m_wMinute	  = _Minute;
				m_wSecond	  = _Second;
				m_wUserLevel  = _UserLevel;
			}

			void Set(BYTE _Day, BYTE _Hour, BYTE _Minute,  BYTE	_Second, BYTE _UserLevel, bool _GiveSwitch = TRUE)
			{
				m_bGiveSwitch = _GiveSwitch;
				m_wDay		  = _Day;
				m_wHour		  = _Hour;
				m_wMinute	  = _Minute;
				m_wSecond	  = _Second;
				m_wUserLevel  = _UserLevel;
			}	
	};

	static const SI32   LampSize = 10;
	static MagicLamp	Lamp[LampSize] = {MagicLamp(), };
	
	// �ʱ�ȭ ��¥.
	static WORD	Day = 0;

	static _SYSTEMTIME	giveTime;
	
	DiffTimeSecond( &sTime, &giveTime );
	
	//--------------------------------------------------------------------------------
	// �ش� ���� �ð��� �����ָ� ��������� ���޵˴ϴ�.
	// ������� �ʴ� ����� �ش� ���� �ð��ִ� �κп� return�� �־��ּ���. 
	// �ð��� ������ 10�� ���� �����մϴ�.
	//--------------------------------------------------------------------------------

	if(Day != sTime.wDay)
	{
		Day = sTime.wDay;

		if ( IsWhereServiceArea( ConstServiceArea_China ) )
		{
			Lamp[0].Set(0, 20, 30, 0, 30);
		}
		else if ( IsWhereServiceArea( ConstServiceArea_Korea ) )
		{
			Lamp[0].Set(0, 19, 0, 0, 30);//19�� 30�� �̻� ������� �ش�.[08.01.15]
		}
		else if ( IsWhereServiceArea( ConstServiceArea_NHNChina ) )
		{
			Lamp[0].Set(0, 19, 0, 0, 30);//19�� 30�� �̻� ������� �ش�
		}
		else if ( IsWhereServiceArea( ConstServiceArea_English ) )
		{
			Lamp[0].Set(0,  3, 0, 0, 30);
			Lamp[1].Set(0,  6, 0, 0, 30);
			Lamp[2].Set(0, 15, 0, 0, 30);
			Lamp[3].Set(0, 18, 0, 0, 30);
		}
		else if ( IsWhereServiceArea( ConstServiceArea_USA ) )
		{
			Lamp[0].Set(0,  0, 0, 0, 30);
			Lamp[1].Set(0,  3, 0, 0, 30);
			Lamp[2].Set(0,  6, 0, 0, 30);
			Lamp[3].Set(0,  9, 0, 0, 30);
			Lamp[4].Set(0, 12, 0, 0, 30);
			Lamp[5].Set(0, 15, 0, 0, 30);
			Lamp[6].Set(0, 18, 0, 0, 30);
			Lamp[7].Set(0, 21, 0, 0, 30);
		}
		// �븸 ������� ���� �Ⱓ ���� (�������� 8�ÿ� 20��������)
		else if ( IsWhereServiceArea( ConstServiceArea_Taiwan ) )
		{
			Lamp[0].Set(0,  20, 0, 0, 20);
		}
		// �Ϻ� ���� �ѹ� ���� 6�ÿ� �����Ѵ�
		else if ( IsWhereServiceArea( ConstServiceArea_Japan ) )
		{
			// ���� �̺�Ʈ �ð����� �����ϵ����Ѵ�
			if ( IsCountrySwitch(Switch_Server_Event) && pclEventTimeManager->InEventTime(TEXT("GoonzuDay_Week"), &sTime) )
			{
				Lamp[0].Set(0,  18, 0, 0, 30);
			}

			// ������� �̺�Ʈ �Ⱓ���� 21�ø��ٹ��. ������ �Ʒ�.
			if( pclClient->pclEventTimeManager->InEventTime("MagicLamp_event", &sTime) )
			{
				Lamp[0].Set(0,  21, 0, 0, 30);
			}
		}
		else if ( IsWhereServiceArea( ConstServiceArea_EUROPE ) )
		{
			Lamp[0].Set(0,  6, 0, 0, 30);
			Lamp[1].Set(0, 18, 0, 0, 30);
		}
		else
		{
			return;
		}
	}

	
	static clock_t	sendLampMsgClock = 0;

	for(int i = 0; i < LampSize; ++i)
	{
		if (Lamp[i].m_bGiveSwitch)
		{
			// ���� ������ ���� �ð��� �̺�Ʈ�� �ߵ� ���ϰ�.(�Ϸ� �ѹ�)
			if( sTime.wDay == Lamp[i].m_wDay	) 
			{
				continue;
			}

			giveTime.wHour   = Lamp[i].m_wHour;
			giveTime.wMinute = Lamp[i].m_wMinute;
			giveTime.wSecond = Lamp[i].m_wSecond;

			SI32 diffTime = DiffTimeSecond( &sTime, &giveTime );

			if ( diffTime >= -600 && diffTime < 60 )
			{
				if ( TABS( CurrentClock - sendLampMsgClock) > 1000 * 60*5 ) // 60�ʿ� �ѹ��� ->5�п� �ѹ�.
				{
						TCHAR* pnotice = GetTxtFromMgr( 3787 );
						TCHAR buf[128] = {0,};
						StringCchPrintf( buf, 128, pnotice, TABS(diffTime/60) );
						SendNoticeMsg(-1, 0, 0, buf);
						pnotice = GetTxtFromMgr( 3788 );
						SendNoticeMsg(-1, 0, 0, pnotice);

						sendLampMsgClock = CurrentClock;
				}
			}

			if (sTime.wHour   == Lamp[i].m_wHour	&& 
				sTime.wMinute >= Lamp[i].m_wMinute	&& 	
				sTime.wMinute <= Lamp[i].m_wMinute + 3 )
			{
				// �ð��� �Ǿ������� ���� ��ι��� ���޵��� �ʾҴٸ�, 
				SI16 itemunique = ITEMUNIQUE(13025);
				SI16 sLampNum	= 1; 				// �����ϴ� ���� ����.

				if ( IsWhereServiceArea( ConstServiceArea_Japan ) )
				{
					sLampNum = 1;		// �Ϻ��� 5���� 1���� ����.
				}
					
				pclCM->GiveItem(0, itemunique, sLampNum, GIVEITEM_MODE_MINLEVEL, INPUTITEMPERSON_OPTION_MASTER,0,0, Lamp[i].m_wUserLevel);
				
				// ���ó�¥�� �����Ƿ� ���� ���ǹ��� �����Ѵ�.(������ �ߵ� ����.)
				Lamp[i].m_wDay = sTime.wDay;					

				TCHAR* pnotice = GetTxtFromMgr( 3786 );
				SendNoticeMsg(-1, 0, 0, pnotice);
			}
		}
		else
		{
			break;
		}
	}
}

//KHY - 0115 �߷�Ÿ�ε��� �̺�Ʈ.
void cltServer::ValentineEventGiveItemAction()
{
	class ValentineItemTime
	{	
		private:
		public:
			bool	m_bGiveSwitch;			// �ֳ� ����.
			WORD	m_wDay;					// ��.
			WORD	m_wHour;				// ��.
			WORD	m_wMinute;				// ��.
			WORD	m_wSecond;				// ��.
			WORD	m_wUserLevel;			// ���� ���� ����.
		
			ValentineItemTime(BYTE _Day = 0, BYTE _Hour = 0, BYTE _Minute = 0, BYTE	_Second = 0, BYTE _UserLevel = 0, bool _GiveSwitch = FALSE)
			{
				m_bGiveSwitch = _GiveSwitch;
				m_wDay		  = _Day;
				m_wHour		  = _Hour;
				m_wMinute	  = _Minute;
				m_wSecond	  = _Second;
				m_wUserLevel  = _UserLevel;
			}

			void Set(BYTE _Day, BYTE _Hour, BYTE _Minute,  BYTE	_Second, BYTE _UserLevel, bool _GiveSwitch = TRUE)
			{
				m_bGiveSwitch = _GiveSwitch;
				m_wDay		  = _Day;
				m_wHour		  = _Hour;
				m_wMinute	  = _Minute;
				m_wSecond	  = _Second;
				m_wUserLevel  = _UserLevel;
			}	
	};

	static const SI32   TimeSize = 24;
	static ValentineItemTime	vItem[TimeSize] = {ValentineItemTime(), };
	
	// �ʱ�ȭ ��¥.
	static WORD	Day = 0;

	static _SYSTEMTIME	giveTime;
	
	DiffTimeSecond( &sTime, &giveTime );
	
	//--------------------------------------------------------------------------------
	// �ش� ���� �ð��� �����ָ� �������� ���޵˴ϴ�.
	// ������� �ʴ� ����� �ش� ���� �ð��ִ� �κп� return�� �־��ּ���. 
	// �ð��� ������ 24�� ���� �����մϴ�.
	//  ���ҽ��� ���ǵ� �Ⱓ���� �ߵ��մϴ�.
	//--------------------------------------------------------------------------------
	NDate Today;
	Today.SetDate(sTime.wYear, sTime.wMonth, sTime.wDay );

	if ( Today.GetDateVary() >= clValentineEventStart.GetDateVary() &&
		Today.GetDateVary() <= clValentineEventEnd.GetDateVary() )
	{
		if(Day != sTime.wDay)
		{
			Day = sTime.wDay;

			for(int i = 0; i < TimeSize; ++i)
			{
				vItem[i].Set(0,i, 0, 0, 20); // �Ž� 30���̻� �ش�.
			}
		}
	}
	else
	{
		return;
	}
	
	static clock_t	sendLampMsgClock = 0;

	for(int i = 0; i < TimeSize; ++i)
	{
		if (vItem[i].m_bGiveSwitch)
		{
			// ���� ������ ���� �ð��� �̺�Ʈ�� �ߵ� ���ϰ�.(�Ϸ� �ѹ�)
			if(sTime.wDay == vItem[i].m_wDay) 
			{
				continue;
			}

			giveTime.wHour   = vItem[i].m_wHour;
			giveTime.wMinute = vItem[i].m_wMinute;
			giveTime.wSecond = vItem[i].m_wSecond;

			SI32 diffTime = DiffTimeSecond( &sTime, &giveTime );

			if ( diffTime >= -600 && diffTime < 60 )
			{
				if ( TABS( CurrentClock - sendLampMsgClock) > 1000 * 60 ) // 60�ʿ� �ѹ���
				{
					TCHAR* pnotice = GetTxtFromMgr( 10306 );
					TCHAR buf[128] = {0,};
					StringCchPrintf( buf, 128, pnotice, TABS(diffTime/60) );
					SendNoticeMsg(-1, 0, 0, buf);
					pnotice = GetTxtFromMgr( 10307 );
					SendNoticeMsg(-1, 0, 0, pnotice);

					sendLampMsgClock = CurrentClock;
				}
			}

			if (sTime.wHour   == vItem[i].m_wHour	&& 
				sTime.wMinute >= vItem[i].m_wMinute	&& 	
				sTime.wMinute <= vItem[i].m_wMinute + 3 )
			{
				// �ð��� �Ǿ������� ���� ��������  ���޵��� �ʾҴٸ�, 
				SI16 itemunique = ITEMUNIQUE(13011);  //Tī��
				pclCM->GiveItem(0, itemunique, 1, GIVEITEM_MODE_MINLEVEL, INPUTITEMPERSON_OPTION_MASTER,0,0, vItem[i].m_wUserLevel);
				
				// ���ó�¥�� �����Ƿ� ���� ���ǹ��� �����Ѵ�.(������ �ߵ� ����.)
				vItem[i].m_wDay = sTime.wDay;					

				TCHAR* pnotice = GetTxtFromMgr( 10308 );
				SendNoticeMsg(-1, 0, 0, pnotice);
			}
		}
		else
		{
			break;
		}
	}
}

//KHY - 0218 ȭ��Ʈ���� �̺�Ʈ.
void cltServer::WhiteEventGiveItemAction()
{
	class WhiteItemTime
	{	
		private:
		public:
			bool	m_bGiveSwitch;			// �ֳ� ����.
			WORD	m_wDay;					// ��.
			WORD	m_wHour;				// ��.
			WORD	m_wMinute;				// ��.
			WORD	m_wSecond;				// ��.
			WORD	m_wUserLevel;			// ���� ���� ����.
		
			WhiteItemTime(BYTE _Day = 0, BYTE _Hour = 0, BYTE _Minute = 0, BYTE	_Second = 0, BYTE _UserLevel = 0, bool _GiveSwitch = FALSE)
			{
				m_bGiveSwitch = _GiveSwitch;
				m_wDay		  = _Day;
				m_wHour		  = _Hour;
				m_wMinute	  = _Minute;
				m_wSecond	  = _Second;
				m_wUserLevel  = _UserLevel;
			}

			void Set(BYTE _Day, BYTE _Hour, BYTE _Minute,  BYTE	_Second, BYTE _UserLevel, bool _GiveSwitch = TRUE)
			{
				m_bGiveSwitch = _GiveSwitch;
				m_wDay		  = _Day;
				m_wHour		  = _Hour;
				m_wMinute	  = _Minute;
				m_wSecond	  = _Second;
				m_wUserLevel  = _UserLevel;
			}	
	};

	static const SI32   TimeSize = 24;
	static WhiteItemTime	wItem[TimeSize] = {WhiteItemTime(), };
	
	// �ʱ�ȭ ��¥.
	static WORD	Day = 0;

	static _SYSTEMTIME	giveTime;
	
	DiffTimeSecond( &sTime, &giveTime );
	
	//--------------------------------------------------------------------------------
	// �ش� ���� �ð��� �����ָ� �������� ���޵˴ϴ�.
	// ������� �ʴ� ����� �ش� ���� �ð��ִ� �κп� return�� �־��ּ���. 
	// �ð��� ������ 24�� ���� �����մϴ�.
	//  ���ҽ��� ���ǵ� �Ⱓ���� �ߵ��մϴ�.
	//--------------------------------------------------------------------------------
	NDate Today;
	Today.SetDate(sTime.wYear, sTime.wMonth, sTime.wDay );

	if ( Today.GetDateVary() >= clWhiteEventStart.GetDateVary() &&
		Today.GetDateVary() <= clWhiteEventEnd.GetDateVary() )
	{
		if(Day != sTime.wDay)
		{
			Day = sTime.wDay;

			for(int i = 0; i < TimeSize; ++i)
			{
				wItem[i].Set(0,i, 0, 0, 20); // �Ž� 30���̻� �ش�.
			}
		}
	}
	else
	{
		return;
	}
	
	static clock_t	sendLampMsgClock = 0;

	for(int i = 0; i < TimeSize; ++i)
	{
		if (wItem[i].m_bGiveSwitch)
		{
			// ���� ������ ���� �ð��� �̺�Ʈ�� �ߵ� ���ϰ�.(�Ϸ� �ѹ�)
			if(sTime.wDay == wItem[i].m_wDay) 
			{
				continue;
			}

			giveTime.wHour   = wItem[i].m_wHour;
			giveTime.wMinute = wItem[i].m_wMinute;
			giveTime.wSecond = wItem[i].m_wSecond;

			SI32 diffTime = DiffTimeSecond( &sTime, &giveTime );

			if ( diffTime >= -600 && diffTime < 60 )
			{
				if ( TABS( CurrentClock - sendLampMsgClock) > 1000 * 60 ) // 60�ʿ� �ѹ���
				{
					TCHAR* pnotice = GetTxtFromMgr( 7956 );
					TCHAR buf[128] = {0,};

					StringCchPrintf( buf, 128, pnotice, TABS(diffTime/60) );
					SendNoticeMsg(-1, 0, 0, buf);

					sendLampMsgClock = CurrentClock;
				}
			}

			if (sTime.wHour   == wItem[i].m_wHour	&& 
				sTime.wMinute >= wItem[i].m_wMinute	&& 	
				sTime.wMinute <= wItem[i].m_wMinute + 3 )
			{
				// �ð��� �Ǿ������� ���� ��������  ���޵��� �ʾҴٸ�, 
				SI16 itemunique = ITEMUNIQUE(13020);  //Eī��
				pclCM->GiveItem(0, itemunique, 1, GIVEITEM_MODE_MINLEVEL, INPUTITEMPERSON_OPTION_MASTER,0,0, wItem[i].m_wUserLevel);
				
				// ���ó�¥�� �����Ƿ� ���� ���ǹ��� �����Ѵ�.(������ �ߵ� ����.)
				wItem[i].m_wDay = sTime.wDay;					

				TCHAR* pnotice = GetTxtFromMgr( 10309 );
				SendNoticeMsg(-1, 0, 0, pnotice);
			}
		}
		else
		{
			break;
		}
	}
}

/*
// ��ι� �̺�Ʈ ó��.
void cltServer::SpecialQuestAction()
{
	static WORD giveday_1st		= 0;
	static WORD giveday_2nd		= 0;


	WORD givehour_1st		= 0;
	WORD giveminute_1st		= 0;
	WORD givehour_2nd		= 0;
	WORD giveminute_2nd		= 0;

	bool giveswitch_1st		= false;
	bool giveswitch_2nd		= false;

	if ( IsWhereServiceArea( ConstServiceArea_China ) )
	{
		giveswitch_1st		= true;
		givehour_1st		= 20;
		giveminute_1st		= 30;
	}
	else if ( IsWhereServiceArea( ConstServiceArea_Korea ) )
	{
		giveswitch_1st		= true;
		givehour_1st		= 19;
		giveminute_1st		= 0;
	}
	else if ( IsWhereServiceArea( ConstServiceArea_English ) )
	{
		giveswitch_1st		= true;
		givehour_1st		= 6;
		giveminute_1st		= 0;

		giveswitch_2nd		= true;
		givehour_2nd		= 18;
		giveminute_2nd		= 0;
	}
	else
	{
		return;
	}

	_SYSTEMTIME giveTime;
	static clock_t sendLampMsgClock = 0;

	//----------------------------------------------------------------
	// ��ι� �����ϱ�. 
	//----------------------------------------------------------------
	if ( giveswitch_1st )
	{
		giveTime.wHour = givehour_1st;
		giveTime.wMinute = giveminute_1st;
		giveTime.wSecond = 0;

		SI32 diffTime = DiffTimeSecond( &sTime, &giveTime );
		if ( diffTime >= -600 && diffTime < 60 )
		{
			if ( TABS( CurrentClock - sendLampMsgClock) > 1000 * 60 ) // 60�ʿ� �ѹ���
			{
				TCHAR* pnotice = GetTxtFromMgr( 3787 );
				TCHAR buf[128] = {0,};
				StringCchPrintf( buf, 128, pnotice, TABS(diffTime/60) );
				SendNoticeMsg(-1, 0, 0, buf);
				pnotice = GetTxtFromMgr( 3788 );
				SendNoticeMsg(-1, 0, 0, pnotice);

				sendLampMsgClock = CurrentClock;
			}
		}

		if ( giveday_1st != sTime.wDay && 
			sTime.wHour == givehour_1st && 
			sTime.wMinute >= giveminute_1st && sTime.wMinute <= giveminute_1st + 3 )
		{
			// �ð��� �Ǿ������� ���� ��ι��� ���޵��� �ʾҴٸ�, 
			SI16 itemunique = ITEMUNIQUE(8035);
			pclCM->GiveItem(0, itemunique, 1, GIVEITEM_MODE_MINLEVEL, INPUTITEMPERSON_OPTION_MASTER,0,0,30);
			giveday_1st = sTime.wDay;

			TCHAR* pnotice = GetTxtFromMgr( 3786 );
			SendNoticeMsg(-1, 0, 0, pnotice);
		}
	}

	if ( giveswitch_2nd )
	{
		giveTime.wHour = givehour_1st;
		giveTime.wMinute = giveminute_1st;
		giveTime.wSecond = 0;

		SI32 diffTime = DiffTimeSecond( &sTime, &giveTime );
		if ( diffTime >= -600 && diffTime < 60 )
		{
			if ( TABS( CurrentClock - sendLampMsgClock) > 1000 * 60 ) // 30�ʿ� �ѹ���
			{
				TCHAR* pnotice = GetTxtFromMgr( 3787 );
				TCHAR buf[128] = {0,};
				StringCchPrintf( buf, 128, pnotice, TABS(diffTime/60) );
				SendNoticeMsg(-1, 0, 0, buf);
				pnotice = GetTxtFromMgr( 3788 );
				SendNoticeMsg(-1, 0, 0, pnotice);

				sendLampMsgClock = CurrentClock;
			}
		}

		if ( giveday_2nd != sTime.wDay && 
			sTime.wHour == givehour_2nd && 
			sTime.wMinute >= giveminute_2nd && sTime.wMinute <= giveminute_2nd + 3 )
		{
			// �ð��� �Ǿ������� ���� ��ι��� ���޵��� �ʾҴٸ�, 
			SI16 itemunique = ITEMUNIQUE(8035);
			pclCM->GiveItem(0, itemunique, 1, GIVEITEM_MODE_MINLEVEL, INPUTITEMPERSON_OPTION_MASTER,0,0,30);
			giveday_2nd = sTime.wDay;

			TCHAR* pnotice = GetTxtFromMgr( 3786 );
			SendNoticeMsg(-1, 0, 0, pnotice);
		}
	}
}*/



void cltServer::PCRoomEventAction()
{
	static BOOL bPCRoomGiveItem = FALSE;

	return;

	//if( sTime.wHour == 17 &&
	//	sTime.wMinute >= 30 &&
	//	sTime.wMinute < 35 ) 
	//{

	//	if( bPCRoomGiveItem == TRUE ) return;

	//	//----------------------------------------------------------------
	//	// PC�� �������� ��ι� �����ϱ�. 
	//	//----------------------------------------------------------------		
	//	TCHAR* pText = GetTxtFromMgr(3791);
	//	SendNoticeMsg(-1, 0, 0, pText);

	//	//��ι� 
	//	SI16 itemunique = 8200;
	//	pclCM->GiveItem(0, itemunique, 1, GIVEITEM_MODE_PCROOM, INPUTITEMPERSON_OPTION_MASTER,0);

	//	bPCRoomGiveItem = TRUE;
	//	
	//} else {

	//	bPCRoomGiveItem = FALSE;
	//}
}
