//---------------------------------
// 2008/05/21 �̰���
//---------------------------------
#ifndef _MONEYSTATISTICS_H
#define _MONEYSTATISTICS_H

#include "../../../Lib/Directives.h"
#include "../../NLib/NTCHARString.h"
#include "../../NLib/NUpdateTimer.h"
#include "../../../Lib/Directives.h"

class cltMoneyStatistics
{
protected:
	NTCHARString<32>*	m_pColumnNames;
	SI64*				m_Row;	
	NTCHARString<32>	m_kFileName;
	SI32				m_siColumnCount;

	NUpdateTimer		m_kUpdateTimer_Action;

public:
	cltMoneyStatistics()
	{
		m_pColumnNames	= NULL;
		m_Row			= NULL;
		m_siColumnCount = 0;
	}

	~cltMoneyStatistics()
	{
		if(m_pColumnNames)		delete [] m_pColumnNames;
		if(m_Row)				delete [] m_Row;
	}

public:
	virtual void Add(SI32 siColumn, SI64 siValue) = 0;

	void Action();

protected:
	virtual void Init(SI32 siColumnCount) = 0;

	bool ReadStatistics();
	bool WriteStatistics();

	bool CreateFile();
	bool ChangeExistFileName();

	int CheckColumn();
};


//------------------------------------------------------------------------------------------------------
// ADDMONEYSTATISTIC
//------------------------------------------------------------------------------------------------------
enum ADDMONEYSTATISTIC_COLUMN
{
	ADDMONEY_STATISTIC_DATE,
	//==========================================

	ADDMONEY_STATISTIC_DAILYQUEST,
	ADDMONEY_STATISTIC_LEVEL20,
	ADDMONEY_STATISTIC_ANKALANSTOCK30,
	ADDMONEY_STATISTIC_SKILLMONEY,
	ADDMONEY_STATISTIC_EVENT,
	ADDMONEY_STATISTIC_FATHER,	
	ADDMONEY_STATISTIC_SPECIALQUEST,
	ADDMONEY_STATISTIC_QUEST,
	ADDMONEY_STATISTIC_SELLNPC,
	ADDMONEY_STATISTIC_SYSTEMREWARD,
	ADDMONEY_STATISTIC_MONTHMONEY,
	ADDMONEY_STATISTIC_NPCBUYITEM,

	ADDMONEY_STATISTIC_DIVIDEND,
	ADDMONEY_STATISTIC_GUILDDUNGEON,

	//==========================================
	ADDMONEY_STATISTIC_TOTAL
};

class cltAddMoneyStatistics : public cltMoneyStatistics
{
protected:
	void Init(SI32 siColumnCount);

public:
	cltAddMoneyStatistics()
	{
		Init(ADDMONEY_STATISTIC_TOTAL);
	}

	~cltAddMoneyStatistics()
	{
	}

	void Add(SI32 siColumn, SI64 siValue)
	{
		if( siValue < 0 )		return;
		if( siColumn <= ADDMONEY_STATISTIC_DATE || siColumn >= ADDMONEY_STATISTIC_TOTAL )	return;

		m_Row[siColumn] += siValue;
	}

protected:
};

//------------------------------------------------------------------------------------------------------
// DELMONEYSTATISTIC
//------------------------------------------------------------------------------------------------------
enum DELMONEYSTATISTIC_COLUMN
{
	DELMONEY_STATISTIC_DATE,
	//==========================================

	DELMONEY_SERVICECHARGE,			// ������ - �ǹ��� ���� ��
	DELMONEY_TAX,					// ���� - ������� ��
	DELMONEY_DONATE,				// ��α�
	DELMONEY_SAVEHOUSE,				// Ŭ��� ��ǰ ������
	DELMONEY_DEATHPANELTY,			// ��� �г�Ƽ
	DELMONEY_MARKETSERVICECHARGE,	// ���� ��� ������
	DELMONEY_WARP,					// ���� ���
	DELMONEY_ENTEREVENT,			// �̺�Ʈ ������
	DELMONEY_BUYNPC,				// NPC ���� ����
	DELMONEY_POSTOFFICE,			// ��ü�� �̿��
	DELMONEY_STOCK,					// �ֽı��Ժ�
	DELMONEY_GUILDCREATE,			// ��� ������ (����)
	DELMONEY_BANK_FEE,				// ���� (����)
	DELMONEY_BANK_SERVICECHARGE,	// ������ (����)
	DELMONEY_BUFF_ROULETTE,			// [����] �����귿�� �̿��� ���.
	DELMONEY_MARKETCONDITIONS,		// [��] �ü�Ȯ��.
	DELMONEY_CHAR_ROULETTE,			// [����] ���ŷ귿�� �̿��� ���.
	DELMONEY_NEWYEAREVENT_ROULETTE,	// [���] �ų��̺�Ʈ ��귿�� �̿��� ���.
	DELMONEY_BALANCECURRENCY,		// [��ȣ] ��ȭ�� ��� ��å

	//==========================================
	DELMONEY_STATISTIC_TOTAL
};

class cltDelMoneyStatistics : public cltMoneyStatistics
{
protected:
	void Init(SI32 siColumnCount);

public:
	cltDelMoneyStatistics()
	{
		Init(DELMONEY_STATISTIC_TOTAL);
	}

	~cltDelMoneyStatistics()
	{
	}

	void Add(SI32 siColumn, SI64 siValue)
	{
		//if( siValue < 0 )		return;
		if( siColumn <= DELMONEY_STATISTIC_DATE || siColumn >= DELMONEY_STATISTIC_TOTAL )	return;

		m_Row[siColumn] += TABS(siValue);
	}

	void Del(SI32 siColumn, SI64 siValue)
	{
		if( siValue < 0 )		return;
		if( siColumn <= DELMONEY_STATISTIC_DATE || siColumn >= DELMONEY_STATISTIC_TOTAL )	return;

		m_Row[siColumn] -= siValue;
	}

protected:
};

#endif
