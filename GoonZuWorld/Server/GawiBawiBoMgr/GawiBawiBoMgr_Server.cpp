#include "GawiBawiBoMgr_Server.h"
#include "Char/CharManager/CharManager.h"
#include "../CommonLogic/CommonLogic.h"
#include "../Lib/dxutil.h"
#include "../Client/Client.h"

extern cltCommonLogic* pclClient;

CGawiBawiBoMgr_Server::CGawiBawiBoMgr_Server()
{
	m_siStatus = 0;	
	ZeroMemory(m_siWInPercentage, sizeof(m_siWInPercentage));

	m_bAlwaysWin = false;
	m_siLimitWin = 0;
}


CGawiBawiBoMgr_Server::~CGawiBawiBoMgr_Server()
{
	
}


bool CGawiBawiBoMgr_Server::Initialize()			//	�Ŵ��� �ʱ�ȭ
{
	bool bResult = false;

	//	�Ŵ��� �ʱ�ȭ �۾�.. ���Ϸε� ���
	bResult = LoadGawiBawiBoFiles();

	return bResult;
}

bool CGawiBawiBoMgr_Server::LoadGawiBawiBoFiles()
{
	NDataLoader	dataloader;

	bool bResult = false;

	if( pclClient->IsWhereServiceArea(ConstSwitch_TextEncryption))
		bResult = dataloader.LoadDataFromCryptFile(TEXT("Data/SRPInfo.txt"));
	else
		bResult = dataloader.LoadDataFromFile(TEXT("Data/SRPInfo.txt"));

	if (bResult == false)
		return false;

	TCHAR	szName[MAX_PATH] = TEXT("");
	SI32	siValue = 0;

	NDataTypeInfo pDataTypeInfo[] =
	{
		NDATA_MBSTRING,	szName,		MAX_PATH,
		NDATA_INT32,	&siValue,	4,
		0,0,0
	};

	dataloader.RegDataType(pDataTypeInfo);

	SI16 siCount = 1;

	while(dataloader.IsEndOfData() != true) 
	{
		if (dataloader.ReadData() == true)	
		{
			if(siCount <= 4)		//	������������ 2�� �ε��������� �·� ������
				m_siWInPercentage[siCount] = siValue;
			else				//	������������ 3���ε��� ���ʹ� ��������Ʈ ������ (��������Ʈ�� ����ī��Ʈ�� ��ȹ�� �� �þ�� �����Ƿ� ���ͷ�)
			{
				m_vecStraightWins.push_back(siValue);	
				m_siLimitWin++;
			}
			siCount++;
		}
		else
			return true;
	}
	return false;	
}

void CGawiBawiBoMgr_Server::Action()
{

}


GMONEY	CGawiBawiBoMgr_Server::GetChargedMoney()	//	������ �ݾ��� ����
{
	GMONEY siMoney = 0;

	siMoney	= (pclClient->pclItemManager->clItemStatistic.siNPCPriceRate) * 200;	//	 ����� �ü� * 200

	return siMoney;
}

//	���� ����
SI08 CGawiBawiBoMgr_Server::GetCalculateResult()
{
	SI32 siRand = rand() % 100;
	
	if(siRand < m_siWInPercentage[GAWIBAWIBO_RESULT_ABUSE_WIN]) // NPC ���������� ������ �¸�
		return GAWIBAWIBO_RESULT_ABUSE_WIN;
	
	else if(siRand < m_siWInPercentage[GAWIBAWIBO_RESULT_WIN])
		return GAWIBAWIBO_RESULT_WIN;
	
	else if(siRand < m_siWInPercentage[GAWIBAWIBO_RESULT_WIN] + m_siWInPercentage[GAWIBAWIBO_RESULT_DRAW])
		return GAWIBAWIBO_RESULT_DRAW;
	
	else
		return GAWIBAWIBO_RESULT_LOSE;
}


// �Ѿ�� ���ڰ��� ���¼�. �ش� ���½� ���� ���ִ� �����ݾ���  ���Ѵ�.
GMONEY CGawiBawiBoMgr_Server::GetCalculateCumulativeMoney(SI08 siStraightWins)						//	�����ݾ� ���
{
	//	���������� �Ѿ�� ī��Ʈ ���ڸ��� �������� ���´������� ���ؾ� �Ѵ�.
	GMONEY siMoneyCumulativeMoney = 0;

	//	siCount ������ ������ ���� �ݾ��� ����
	
	if(IsValidCount(siStraightWins) == false)
	{
		assert(0);
		return 0;
	}

	SI32	siNpcrate	= pclClient->pclItemManager->clItemStatistic.siNPCPriceRate;
	GMONEY	siUnitMoney	= siNpcrate * 200;	//	 ����� �ü� * 10			

	//	 siIndex�� �ʱⰪ�� 1�� ������ ������ ���ҽ��󿡼� 1���� index �� 1�̴�.
	//for(SI08 siIndex = 1; siIndex <= siStraightWins; siIndex++)
	//{
	//if(siIndex == 1)	// ���� �����ݾ��� ���� ���.
	//	siMoneyCumulativeMoney = (siUnitMoney * m_vecStraightWins.at(siIndex)) / 100;	
	//else
	//	siMoneyCumulativeMoney = (siMoneyCumulativeMoney * m_vecStraightWins.at(siIndex)) / 100;

	// �����ݾ� ���� ����
	//}

	siMoneyCumulativeMoney = (siUnitMoney * m_vecStraightWins.at(siStraightWins)) / 100;	

	return siMoneyCumulativeMoney;
}

SI08 CGawiBawiBoMgr_Server::IsValidCount(SI08 siCount)
{
	if(siCount <= 0 || siCount > (SI08)m_vecStraightWins.size())
		return GAWIBAWIBO_RESULT_VALIDCOUNT_INVALID;
	else if(siCount == (SI08)(m_vecStraightWins.size()-1))
		return GAWIBAWIBO_RESULT_VALIDCOUNT_MAXWIN;
	else
        return GAWIBAWIBO_RESULT_VALIDCOUNT_VALID;
}

void CGawiBawiBoMgr_Server::SetLimitWin(SI32 siLimitWin)
{
	if((size_t)siLimitWin >= m_vecStraightWins.size()-1)
		m_siLimitWin = m_vecStraightWins.size()-1;
	else
		m_siLimitWin = siLimitWin;
}
