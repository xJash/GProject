//---------------------------------
// 2004/10/6 ���°�
//---------------------------------
#ifndef _STATISTICS_H
#define _STATISTICS_H

#include <Directives.h>

//---------------------------------
// Common
//---------------------------------
#include "..\..\Common\CommonHeader.h"
#include "..\..\Common\Quest\Quest.h"

//-------------------------------
// ���� ���� ��� 
//-------------------------------
class cltStatistics{
public:

	//-------------------------------
	// �α��� ����� �� 
	//-------------------------------
	SI32 siLoginNumber;

	//-------------------------------
	// ä�� �� 
	//-------------------------------
	SI32 siChatNumber;

	//-------------------------------
	// ������ �̿��ڼ�. 
	//-------------------------------
	SI32 siHuntUserNumber;

	//-------------------------------
	// �Ϲ� ���� �̿��ڼ�. 
	//-------------------------------
	SI32 siDungeonUserNumber;
	//-------------------------------
	// �ν��Ͻ� ���� �̿��ڼ�
	//-------------------------------
	SI32 siInstanceDungeonUserNumber;

	//-------------------------------
	// ���� ���� �̿� Ƚ��. 
	//-------------------------------
	SI32 siMasterInfoUseNumber;

	//-------------------------------
	// ���� ������ ����� ���. 
	//-------------------------------
	SI32 siAbnormalQuitUserNumber;
	SI32 siNormalQuitUserNumber;

	//------------------------------
	// �ֽ� �ŷ��� ��� 
	//------------------------------
	SI32 siStockTradeNumber;

	//------------------------------
	// Ŭ���̾�Ʈ���� �޽��� ���� ��� 
	//----------------------------------
	SI32 siReceiveFromClientMsgNumber;
	SI32 siSendToClientMsgNumber;

	//---------------------------------
	// DB���� �޽��� ���� ���. 
	//--------------------------------
	SI32 siReceiveFromDBMsgNumber;
	SI32 siSendToDBMsgNumber;

	//-------------------------------
	// ���� ��� 
	//-------------------------------
	GMONEY siMakeMoney;		
	//--------------------------------
	// �̺�Ʈ ��� 
	//--------------------------------
	// �Ұ��縮 ��� �̺�Ʈ Ƚ�� 
	SI32 siHuntingEventNumber;

	// ���� �̺�Ʈ Ƚ�� 
	SI32 siGoguEventNumber;

	// ��ȭ�� �̺�Ʈ Ƚ��
	SI32 siKanghwadoEventNumber;

	//-------------------------------
	// ��ȣõ�� 
	//-------------------------------
	SI32 siAngelNumber;

	//-------------------------------
	// ���� 50�̻� ��õ�μ�. 
	//-------------------------------
	SI32 siRecommenderNumber;

	//-------------------------------
	// ����� �ൿ ��� 
	//-------------------------------
	SI32 siFishUserNumber;
	SI32 siFarmUserNumber;
	SI32 siMineUserNumber;
	SI32 siSummonNumber;

	//------------------------------
	// ���� ��� ���. 
	//------------------------------
	SI32 siScrollSummonNumber;
	// ���� �̿� ���� �Ǽ� ��� 
	SI32 siScrollTuneNumber;

	//-----------------------------
	// SBS ���� �� ��� 
	//-----------------------------
	SI32 siCurSBSUserNum;				// ���� SBS����. 

	//-----------------------------
	// ��� ��ǰ ��� 
	//-----------------------------
	SI32 siBigItemNum;

	//-----------------------------
	// ��ι� ����Ʈ �Ϸ�  ��� 
	//-----------------------------
	SI32 siSpecialQuestDoneNum;

	//------------------------------
	// System�� �������ִ� �� 
	//------------------------------
	GMONEY siSystemBuyMoney;
	SI32 siSystemBuyNum;

	//------------------------------
	// �� ���� �� 
	//-----------------------------
	SI32 siSystemBuyHorseNum;
	GMONEY siSystemBuyHorseMoney;

	//-----------------------------
	// ������ �ŷ��� 
	//-----------------------------
	SI32 siTradeMerchantNum;
	GMONEY siTradeMerchantMoney;
	GMONEY siTradeTax;

	//-----------------------------
	// �Ű� �ŷ��� 
	//-----------------------------
	SI32 siRealEstateTradeNum;
	GMONEY siRealEstateTradeMoney;


	//-----------------------------
	// �𺴰� ����Ʈ ���� ��� 
	//-----------------------------
	SI32 siDailyQuestAcceptNum;
	SI32 siDailyQuestClearNum;

	//-----------------------------
	// �纹�� ��� 
	//-----------------------------
	SI32 siHorseMarketTradeNumber;
	GMONEY siHorseMarketTradeMoney;

	//-----------------------------
	// �忹�� ��� 
	//-----------------------------
	SI32 siSummonMarketTradeNumber;
	GMONEY siSummonMarketTradeMoney;


	//-----------------------------
	// ������� 
	//----------------------------
	SI32 siTotalHouseNumber;
	SI32 siRentHouseNumber;
	SI32 siRecallHouseNumber;


	//-----------------------------
	// ���ڽ� ���
	//----------------------------
	SI32 siFeastUseNumber;
	GMONEY siFeastUseMoney;


	//-----------------------------
	// ����� ��� ���� ��� 
	//-----------------------------
	SI32 siFameLevel10Num;
	SI32 siFameLevel20Num;
	SI32 siFameLevel30Num;
	SI32 siFameLevel40Num;

	//-----------------------------
	// ����Ʈ ��� 
	//-----------------------------
	SI32 siQuestClear[MAX_QUEST_TYPE][2]; // 


	//-----------------------------
	// ���� ���� ��������
	//-----------------------------
	GMONEY siForeignMerchantBuyGameItemMoney;
	GMONEY siForeignMerchantBuyCashItemMoney;

	//-----------------------------
	// �� Ǯ���� Ƚ�� 
	//-----------------------------
	SI32 siReleaseHorse;

	cltStatistics()
	{
		Init();
	}

	~cltStatistics()
	{

	}

	void Init()
	{
		ZeroMemory(this, sizeof(cltStatistics));
	}

	// �߱��� �����
	SI32 siChineseUserCount;

	// �ڽ��� ��� �����͸� ���Ͽ� ����.
	void Write(TCHAR * pszFileName ,_SYSTEMTIME sTime, cltQuestManager* pclQuestManager);

	// ���ڷ� ���� Ŭ������ ���� �ڽ��� ���� ���Ѵ�.
	void Add( cltStatistics * pclAddStatistics );	

	// �߱��� ����� ���
	void WriteChineseUser( TCHAR * pszFileName , _SYSTEMTIME sTime );	
};

class cltStatisticsManager
{
	SI32 siLastWriteenDay;
	SI32 siLastWriteenWeek;
	
	bool bIsBackUpDateLoaded;

public:
	cltStatistics	clDailyStatistics;
	cltStatistics	clWeeklyStatistcs;

	// ���� �ֱ⸶�� ��� ������ ������Ʈ�Ѵ�.
	void WriteAction(_SYSTEMTIME sTime, cltQuestManager* pclQuestManager);

	// ���� �з��� ��踦 ���Ͽ� ����Ѵ�. 
	void WriteDaily(_SYSTEMTIME sTime, cltQuestManager* pclQuestManager);

	// ���� ������ �з��� ��踦 ���Ͽ� ����Ѵ�.
	void WriteWeekly(_SYSTEMTIME sTime, cltQuestManager* pclQuestManager);

	void WriteDailyBackUp(TCHAR * pszFileName ,_SYSTEMTIME sTime);

	void ReadDailyBackUp(TCHAR * pszFileName , _SYSTEMTIME sTime);

	void WriteWeeklyBackUp(TCHAR * pszFileName ,_SYSTEMTIME sTime);

	void ReadWeeklyBackUp(TCHAR * pszFileName , _SYSTEMTIME sTime);

	// [��] �ü�Ȯ�� 2008-07-18
	void ReadMarketConditions(_SYSTEMTIME sTime);

	cltStatisticsManager()
	{
	}
	~cltStatisticsManager()
	{
	}

	void Init();

};


#endif