//---------------------------------
// 2004/10/6 ���°�
//---------------------------------

#include "Statistics.h"
#include "../CommonLogic/CommonLogic.h"
#include "../../../NLib/NUtil.h"

extern cltCommonLogic* pclClient;

// ��踦 ���Ͽ� ����Ѵ�. 

void cltStatistics::Write(TCHAR * pszFileName ,_SYSTEMTIME sTime, cltQuestManager* pclQuestManager)
{

	SI32 i;
	TCHAR buffer[256];

	//StringCchPrintf(buffer,256,TEXT("Config/Server_%02d%02d%02d.txt"),sTime.wYear , sTime.wMonth , sTime.wDay);


	FILE *fp = _tfopen( pszFileName , TEXT("wt") );

	if ( fp == NULL )
	{
		return;
	}

	TCHAR *pText = GetTxtFromMgr(5783);

	// ���� �ð��� ���Ѵ�. 
	StringCchPrintf(buffer, 256, pText, 
		sTime.wMonth, sTime.wDay, sTime.wHour, sTime.wMinute, sTime.wSecond);

	pText = GetTxtFromMgr(5784);
	_ftprintf( fp, pText,		buffer);

	pText = GetTxtFromMgr(5785);
	_ftprintf( fp, pText,		siLoginNumber);
	pText = GetTxtFromMgr(5785);
	_ftprintf( fp, pText,		siLoginNumber);
	pText = GetTxtFromMgr(5786);
	_ftprintf( fp, pText,			siChatNumber);

	pText = GetTxtFromMgr(5787);
	_ftprintf( fp, pText,		siHuntUserNumber);
	pText = GetTxtFromMgr(5788);
	_ftprintf( fp, pText,	siDungeonUserNumber);
	pText = GetTxtFromMgr(5789);
	_ftprintf( fp, pText,siInstanceDungeonUserNumber);

	pText = GetTxtFromMgr(5790);
	_ftprintf( fp, pText,	siMasterInfoUseNumber);


	pText = GetTxtFromMgr(5791);
	_ftprintf( fp, pText,	siNormalQuitUserNumber);
	pText = GetTxtFromMgr(5792);
	_ftprintf( fp, pText,	siAbnormalQuitUserNumber);

	pText = GetTxtFromMgr(5793);
	_ftprintf( fp, pText,	siStockTradeNumber);


	pText = GetTxtFromMgr(5794);
	_ftprintf( fp, pText,	siReceiveFromClientMsgNumber);
	pText = GetTxtFromMgr(5795);
	_ftprintf( fp, pText,	siSendToClientMsgNumber);

	pText = GetTxtFromMgr(5796);
	_ftprintf( fp, pText,	siReceiveFromDBMsgNumber);
	pText = GetTxtFromMgr(5797);
	_ftprintf( fp, pText,	siSendToDBMsgNumber);

	pText = GetTxtFromMgr(5798);
	_ftprintf( fp, pText,	siMakeMoney);

	pText = GetTxtFromMgr(5799);
	_ftprintf( fp, pText,	siHuntingEventNumber);
	pText = GetTxtFromMgr(5800);
	_ftprintf( fp, pText,	siGoguEventNumber);
	pText = GetTxtFromMgr(5801);
	_ftprintf( fp, pText,	siKanghwadoEventNumber);

	pText = GetTxtFromMgr(5802);
	_ftprintf( fp, pText,	siAngelNumber);


	pText = GetTxtFromMgr(5803);
	_ftprintf( fp, pText,	siRecommenderNumber);

	pText = GetTxtFromMgr(5804);
	_ftprintf( fp, pText,	siFishUserNumber, siFarmUserNumber, siMineUserNumber );

	pText = GetTxtFromMgr(5805);
	_ftprintf( fp, pText,	siScrollTuneNumber, siScrollSummonNumber);

	pText = GetTxtFromMgr(5806);
	_ftprintf( fp, pText,		siBigItemNum);

	pText = GetTxtFromMgr(5807);
	_ftprintf( fp, pText,		siSpecialQuestDoneNum);


	pText = GetTxtFromMgr(5808);
	_ftprintf( fp, pText,	siSystemBuyMoney);
	pText = GetTxtFromMgr(5809);
	_ftprintf( fp, pText,		siSystemBuyNum);

	pText = GetTxtFromMgr(5810);
	_ftprintf( fp, pText,	siSystemBuyHorseNum, siSystemBuyHorseMoney);

	pText = GetTxtFromMgr(5811);
	_ftprintf( fp, pText,
		siTradeMerchantNum, siTradeMerchantMoney,siTradeTax);

	pText = GetTxtFromMgr(5812);
	_ftprintf( fp, pText,		siDailyQuestClearNum, siDailyQuestAcceptNum);

	pText = GetTxtFromMgr(5813);
	_ftprintf( fp, pText,		
		siTotalHouseNumber, siRentHouseNumber, siRecallHouseNumber);

	pText = GetTxtFromMgr(5814);
	_ftprintf( fp, pText,		
		siHorseMarketTradeNumber, siHorseMarketTradeMoney);

	pText = GetTxtFromMgr(5815);
	_ftprintf( fp, pText,		
		siSummonMarketTradeNumber, siSummonMarketTradeMoney);

	pText = GetTxtFromMgr(5816);
	_ftprintf( fp, pText,		
		siRealEstateTradeNum, siRealEstateTradeMoney);

	pText = GetTxtFromMgr(5817);
	_ftprintf( fp, pText,
		siFeastUseNumber, siFeastUseMoney );

	pText = GetTxtFromMgr(5818);
	_ftprintf( fp, pText,		siFameLevel10Num);
	pText = GetTxtFromMgr(5819);
	_ftprintf( fp, pText,		siFameLevel20Num);
	pText = GetTxtFromMgr(5820);
	_ftprintf( fp, pText,		siFameLevel30Num);
	pText = GetTxtFromMgr(5821);
	_ftprintf( fp, pText,		siFameLevel40Num);






	for(i = 0;i < MAX_QUEST_TYPE;i++)
	{
		SI32 rate = 0;
		if(siQuestClear[i][0])
		{
			rate = siQuestClear[i][0] * 100 / (siQuestClear[i][0] + siQuestClear[i][1]);
		}

		TCHAR* pquesttypename = pclQuestManager->GetQuestTypeName(i);
		if(pquesttypename)
		{
			pText = GetTxtFromMgr(5822);
			_ftprintf( fp, pText,	
				pquesttypename, siQuestClear[i][0], siQuestClear[i][1], rate, '%');

		}

	}

	pText = GetTxtFromMgr(5823);
	_ftprintf( fp, pText, siForeignMerchantBuyGameItemMoney );
	pText = GetTxtFromMgr(5824);
	_ftprintf( fp, pText, siForeignMerchantBuyCashItemMoney );

	pText = GetTxtFromMgr(6137);
	_ftprintf( fp, pText, siReleaseHorse );

	fclose( fp );
}


void cltStatistics::WriteChineseUser( TCHAR * pszFileName , _SYSTEMTIME sTime )
{
	//	SI32 i;
	//	TCHAR buffer[256];

	FILE *fp = _tfopen( TEXT("Config/ChineseUserCount.log"), TEXT("a") );

	if ( fp == NULL )
	{
		return;
	}

	_ftprintf( fp, TEXT("[%d-%d-%d]%d:%d\t"), sTime.wYear, sTime.wMonth, sTime.wDay, sTime.wHour, sTime.wMinute );
	TCHAR* pText = GetTxtFromMgr(6361);
	_ftprintf( fp, pText, siChineseUserCount );

	fclose( fp );
}


void cltStatistics::Add( cltStatistics * pclAddStatistics )
{

	siChineseUserCount += pclAddStatistics->siChineseUserCount;

	siLoginNumber += pclAddStatistics->siLoginNumber;

	siChatNumber += pclAddStatistics->siChatNumber;

	siHuntUserNumber += pclAddStatistics->siHuntUserNumber;

	siDungeonUserNumber += pclAddStatistics->siDungeonUserNumber;

	siInstanceDungeonUserNumber += pclAddStatistics->siInstanceDungeonUserNumber;

	siMasterInfoUseNumber += pclAddStatistics->siMasterInfoUseNumber;

	siAbnormalQuitUserNumber += pclAddStatistics->siAbnormalQuitUserNumber;
	siNormalQuitUserNumber += pclAddStatistics->siNormalQuitUserNumber;

	siStockTradeNumber += pclAddStatistics->siStockTradeNumber;

	siReceiveFromClientMsgNumber += pclAddStatistics->siReceiveFromClientMsgNumber;
	siSendToClientMsgNumber += pclAddStatistics->siSendToClientMsgNumber;

	siReceiveFromDBMsgNumber += pclAddStatistics->siReceiveFromDBMsgNumber;
	siSendToDBMsgNumber += pclAddStatistics->siSendToDBMsgNumber;

	siMakeMoney += pclAddStatistics->siMakeMoney;		

	siHuntingEventNumber += pclAddStatistics->siHuntingEventNumber;

	siGoguEventNumber += pclAddStatistics->siGoguEventNumber;

	siKanghwadoEventNumber += pclAddStatistics->siKanghwadoEventNumber;

	siAngelNumber += pclAddStatistics->siAngelNumber;

	siRecommenderNumber += pclAddStatistics->siRecommenderNumber;

	siFishUserNumber += pclAddStatistics->siFishUserNumber;
	siFarmUserNumber += pclAddStatistics->siFarmUserNumber;
	siMineUserNumber += pclAddStatistics->siMineUserNumber;
	siSummonNumber += pclAddStatistics->siSummonNumber;

	siScrollSummonNumber += pclAddStatistics->siScrollSummonNumber;

	siScrollTuneNumber += pclAddStatistics->siScrollTuneNumber;

	siCurSBSUserNum += pclAddStatistics->siCurSBSUserNum;				// 

	siBigItemNum += pclAddStatistics->siBigItemNum;

	siSpecialQuestDoneNum += pclAddStatistics->siSpecialQuestDoneNum;

	siSystemBuyMoney += pclAddStatistics->siSystemBuyMoney;
	siSystemBuyNum += pclAddStatistics->siSystemBuyNum;

	siSystemBuyHorseNum += pclAddStatistics->siSystemBuyHorseNum;
	siSystemBuyHorseMoney += pclAddStatistics->siSystemBuyHorseMoney;

	siTradeMerchantNum += pclAddStatistics->siTradeMerchantNum;
	siTradeMerchantMoney += pclAddStatistics->siTradeMerchantMoney;
	siTradeTax += pclAddStatistics->siTradeTax;

	siRealEstateTradeNum += pclAddStatistics->siRealEstateTradeNum;
	siRealEstateTradeMoney += pclAddStatistics->siRealEstateTradeMoney;

	siDailyQuestAcceptNum += pclAddStatistics->siDailyQuestAcceptNum;
	siDailyQuestClearNum += pclAddStatistics->siDailyQuestClearNum;

	siHorseMarketTradeNumber += pclAddStatistics->siHorseMarketTradeNumber;
	siHorseMarketTradeMoney += pclAddStatistics->siHorseMarketTradeMoney;

	siSummonMarketTradeNumber += pclAddStatistics->siSummonMarketTradeNumber;
	siSummonMarketTradeMoney += pclAddStatistics->siSummonMarketTradeMoney;

	siTotalHouseNumber += pclAddStatistics->siTotalHouseNumber;
	siRentHouseNumber += pclAddStatistics->siRentHouseNumber;
	siRecallHouseNumber += pclAddStatistics->siRecallHouseNumber;

	siFeastUseNumber += pclAddStatistics->siFeastUseNumber;
	siFeastUseMoney += pclAddStatistics->siFeastUseMoney;

	siFameLevel10Num += pclAddStatistics->siFameLevel10Num;
	siFameLevel20Num += pclAddStatistics->siFameLevel20Num;
	siFameLevel30Num += pclAddStatistics->siFameLevel30Num;
	siFameLevel40Num += pclAddStatistics->siFameLevel40Num;


	SI32 siQuestClear[MAX_QUEST_TYPE][2]; 

	for( SI32 i = 0 ; i < MAX_QUEST_TYPE ; i ++)
	{
		siQuestClear[ i ][ 0 ] += pclAddStatistics->siQuestClear[ i ][ 0 ];
		siQuestClear[ i ][ 1 ] += pclAddStatistics->siQuestClear[ i ][ 1 ];
	}

	siForeignMerchantBuyGameItemMoney += pclAddStatistics->siForeignMerchantBuyGameItemMoney;
	siForeignMerchantBuyCashItemMoney += pclAddStatistics->siForeignMerchantBuyCashItemMoney;

	siReleaseHorse += pclAddStatistics->siReleaseHorse;

}


void cltStatisticsManager::WriteAction(_SYSTEMTIME sTime, cltQuestManager* pclQuestManager)
{
	// ���� �������� ����
	TCHAR fileNameBuffer[256];
	fileNameBuffer[0] = 0;


	// ������ ������ ���� ����� �����͸� �о� �´�
	if( bIsBackUpDateLoaded == false)
	{
		ReadDailyBackUp(TEXT("Config\\Server_bakup.bak"), sTime);
		ReadWeeklyBackUp(TEXT("Config\\WeeklyServer_backup.bak"), sTime);

		// [��] �ü�Ȯ�� 2008-07-18
		if(pclClient->IsCountrySwitch(Switch_MarketConditions))
		{
			ReadMarketConditions(sTime);
		}
				
		bIsBackUpDateLoaded = true;
		siLastWriteenDay = sTime.wDay;
	}


	// ��¥�� �ٲ�� �ϴ��� ��� �����͸� �ʱ�ȭ ���ش�.
	if( siLastWriteenDay != sTime.wDay )
	{
		// [��] �ü�Ȯ�� 2008-07-18  - ��ġ�� �� �� �����غ���.
		if(pclClient->IsCountrySwitch(Switch_MarketConditions))
		{
			ReadMarketConditions(sTime);
		}

		// �ϴ��� �����͸� �ʱ�ȭ ���ֱ� ���� �ִ��� �����Ϳ� �����ش�.
		clWeeklyStatistcs.Add( &clDailyStatistics );

		clDailyStatistics.Init();


		// ���ֿ������� �Ǹ� �ִ��� ��� �����͸� ���Ͽ� ��� �� �ʱ�ȭ ���ش�.
		if( sTime.wDayOfWeek == 1 )
		{
			StringCchPrintf(fileNameBuffer,256,TEXT("Config\\WeeklyServer_%04d%02d%02d.log"),sTime.wYear , sTime.wMonth , sTime.wDay );
			clWeeklyStatistcs.Write( fileNameBuffer , sTime , pclQuestManager );			
			clWeeklyStatistcs.Init();

		}		
		siLastWriteenDay = sTime.wDay;
		
		// �ִ��� �����͸� ������Ͽ� ����.
		StringCchPrintf(fileNameBuffer,256,TEXT("Config\\WeeklyServer_backup.bak"));
		WriteWeeklyBackUp( fileNameBuffer , sTime );
	}

	StringCchPrintf( fileNameBuffer , 256 , TEXT("Config\\Server_%04d%02d%02d.log"), sTime.wYear , sTime.wMonth , sTime.wDay );

	clDailyStatistics.Write( fileNameBuffer , sTime , pclQuestManager );

	StringCchPrintf( fileNameBuffer , 256 , TEXT("Config\\Server_bakup.bak") );

	WriteDailyBackUp( fileNameBuffer , sTime );	
}




void cltStatisticsManager::WriteDailyBackUp(TCHAR * pszFileName , _SYSTEMTIME sTime)
{
	FILE *fp = _tfopen( pszFileName , TEXT("wb") );

	if ( fp == NULL )
	{
		return;
	}

	stServerBackUpFileHeader clBackUpFileHeader;
	StringCchPrintf(clBackUpFileHeader.szDesc, 32 , TEXT("Statistics%04d%02d%02d"), sTime.wYear , sTime.wMonth , sTime.wDay );
	clBackUpFileHeader.siVersion = SERVER_BACKUPFILE_HEADER_VERSION;

	fwrite(&clBackUpFileHeader , sizeof(stServerBackUpFileHeader) , 1 , fp);
	fwrite(&clDailyStatistics , sizeof(cltStatistics) , 1 , fp);
	
	fclose( fp );
}

void cltStatisticsManager::ReadDailyBackUp(TCHAR * pszFileName , _SYSTEMTIME sTime)
{

	TCHAR buffer[256];

	FILE *fp = _tfopen( pszFileName , TEXT("rb") );

	if ( fp == NULL )
	{
		return;
	}

	clDailyStatistics.Init();
	stServerBackUpFileHeader clBackUpFileHeader;
	memset(&clBackUpFileHeader,0,sizeof(stServerBackUpFileHeader));

	fread( &clBackUpFileHeader , sizeof(stServerBackUpFileHeader) , 1 , fp);
	
	clBackUpFileHeader.szDesc[31] = 0;	// Insert Null
	
	// ���ó�¥�� ���ڿ��� ����� ��������� ��

	StringCchPrintf(buffer, 256 , TEXT("Statistics%04d%02d%02d"), sTime.wYear , sTime.wMonth , sTime.wDay );

	// ������ ����� �������� �ʴ��� ���� �ʴ´�.
	if( _tcscmp( clBackUpFileHeader.szDesc , buffer ) != 0 ) return;
			
	// ���� ������ �ٸ��� ���� �ʴ´�
	if( clBackUpFileHeader.siVersion != SERVER_BACKUPFILE_HEADER_VERSION ) return;

	fread( &clDailyStatistics , sizeof(cltStatistics) , 1 , fp );

	fclose( fp );
}

void cltStatisticsManager::WriteWeeklyBackUp(TCHAR * pszFileName ,_SYSTEMTIME sTime)
{
	FILE *fp = _tfopen( pszFileName , TEXT("wb") );

	if ( fp == NULL )
	{
		return;
	}

	stServerBackUpFileHeader clBackUpFileHeader;
	StringCchPrintf(clBackUpFileHeader.szDesc, 32 , TEXT("Statistics%04d%02d%02d"), sTime.wYear , sTime.wMonth , sTime.wDay );
	clBackUpFileHeader.siVersion = SERVER_BACKUPFILE_HEADER_VERSION;

	fwrite(&clBackUpFileHeader , sizeof(stServerBackUpFileHeader) , 1 , fp);
	fwrite(&clWeeklyStatistcs , sizeof(cltStatistics) , 1 , fp);

	fclose( fp );
}

void cltStatisticsManager::ReadWeeklyBackUp(TCHAR * pszFileName , _SYSTEMTIME sTime)
{
	TCHAR buffer[256];

	FILE *fp = _tfopen( pszFileName , TEXT("rb") );

	if ( fp == NULL )
	{
		return;
	}

	clDailyStatistics.Init();
	stServerBackUpFileHeader clBackUpFileHeader;
	memset(&clBackUpFileHeader,0,sizeof(stServerBackUpFileHeader));

	fread( &clBackUpFileHeader , sizeof(stServerBackUpFileHeader) , 1 , fp);

	clBackUpFileHeader.szDesc[31] = 0;	// Insert Null

	// ���ó�¥�� ���ڿ��� ����� ��������� ��

	StringCchPrintf(buffer, 256 , TEXT("Statistics%04d%02d%02d"), sTime.wYear , sTime.wMonth , sTime.wDay );

	// ������ ����� �������� �ʴ��� ���� �ʴ´�.
	if( _tcscmp( clBackUpFileHeader.szDesc , buffer ) != 0 ) return;

	// ���� ������ �ٸ��� ���� �ʴ´�
	if( clBackUpFileHeader.siVersion != SERVER_BACKUPFILE_HEADER_VERSION ) return;

	fread( &clWeeklyStatistcs, sizeof(cltStatistics) , 1 , fp );

	fclose( fp );
}

void cltStatisticsManager::ReadMarketConditions(_SYSTEMTIME sTime)
{

	TCHAR		fileNameBuffer[256]; // ���� ���ϸ�.
	FILE *fp = NULL;

	_SYSTEMTIME yTime; // ���ų�¥�� ����ϱ����� ����.		
	ZeroMemory( &yTime,sizeof(_SYSTEMTIME));

	SI16 openLimite = 0; 

	for(SI16 i = 0;i < 9 ; i++) //������ġ �����͸� ����Ѵ�. - �Ϸ簡 �� �ʿ��ϴ�.
	{
		if(openLimite >= 15) break; // ���������� 15���� �˻��Ѵ�. (���ѹݺ�����)

		TimeSubDate(&sTime, (i+1+openLimite) ,&yTime);

		StringCchPrintf( fileNameBuffer , 256 , TEXT("Config\\Item_%04d%02d%02d.log") , yTime.wYear , yTime.wMonth , yTime.wDay );
			
		fp = _tfopen( fileNameBuffer , TEXT("rb") );

		if ( fp == NULL )
		{
			if(openLimite < 15)
			{
				i--;  // ��·�� 7���� ����� �Ѵ�.
				openLimite ++; // ���ѹݺ�����.
			}
			else
				break;

			continue;
		}
		else
		{
			//������ ����.
			TCHAR buffer[1024] = { TEXT('\0') };
			TCHAR tempbuffer[128] = { TEXT('\0') };

			SI32 imsi[10] = {'0',};

			//���� �ʿ�������.
			SI32 itemUnique = 0; 
			GMONEY siPrice = 0; 
			
			_fgetts(buffer, 1024, fp);

			if(pclClient->pclItemManager->clMarketConditions[i] == NULL)
				pclClient->pclItemManager->clMarketConditions[i] = new clItemMarketConditions;

			memcpy( &(pclClient->pclItemManager->clMarketConditions[i]->sTimeMarketConditions) , &yTime , sizeof(_SYSTEMTIME) );

			while( _fgetts(buffer, 1024, fp) != NULL )
			{
				HQDivideByTab(buffer,"%d	%s	%d	%d	%d	%d	%d	%d	%d	%d	%d	%d	%I64d",
					&itemUnique,tempbuffer,&imsi[0],&imsi[1],&imsi[2],&imsi[3],&imsi[4],&imsi[5],&imsi[6],&imsi[7],&imsi[8],&imsi[9],
					&siPrice);

				if( _tcslen(tempbuffer) >= 50 )
				{
					OutputDebugString(tempbuffer);
				}

				if( itemUnique <= 0 && itemUnique >= MAX_ITEM_UNIQUE )		continue;

				if(pclClient->pclItemManager->clMarketConditions[i]->pclMarketConditionsB[itemUnique] == NULL)
					pclClient->pclItemManager->clMarketConditions[i]->pclMarketConditionsB[itemUnique] = new clMarketConditionsBasic;

				pclClient->pclItemManager->clMarketConditions[i]->pclMarketConditionsB[itemUnique]->siItemUnique = (SI16)itemUnique;
				pclClient->pclItemManager->clMarketConditions[i]->pclMarketConditionsB[itemUnique]->siItemMarketConditions = siPrice;
			}
			
			fclose( fp );
		}
	}
}

void cltStatisticsManager::Init()
{
	siLastWriteenDay = 0;
	siLastWriteenWeek = 0;
	clDailyStatistics.Init();
	clWeeklyStatistcs.Init();
	bIsBackUpDateLoaded = false;
}
