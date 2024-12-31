#ifndef _MINISTER_GOONZU_H_
#define _MINISTER_GOONZU_H_

#include "MinisterBase.h"
#include "MinisterMgr.h"

class CMinisterGoonzu : public CMinisterBase
{
public:
	CMinisterGoonzu();
	~CMinisterGoonzu();

	GMONEY	m_iTempFinances; // �ӽ� ����
	GMONEY	m_iTotalFinances; // �� ����

#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, 6>		m_siSetMinisterTime;
#else
	SI32	m_siSetMinisterTime[6] ;
#endif

	// kkm ������ �Ļ긶�������� ���� ���� 2007 / 08 / 15
	// ȣ���� ������ �Ŀ� ��������
	SI16	m_siLiquidationVillageNumber;

	SI16	m_siBonusTime;	// ���� ���� ���ʽ� Ÿ��

	SI16	m_siMakeBonusTime;

	SI16	m_siLastChangedBonusTimeYear;	// ���� ���� ���ʽ� Ÿ���� ��ȯ�� ��
	SI16	m_siLastChangedBonusTimeMonth;	// ���� ���� ���ʽ� Ÿ���� ��ȯ�� ��
	SI16	m_siLastChangedBonusTimeDay;	// ���� ���� ���ʽ� Ÿ���� ��ȯ�� ��


	void AddTempFinances(GMONEY money)
	{
		if ( money < 0 ) return ;
		m_iTempFinances += money ;
	}
	void AddTotalFinances(GMONEY money)
	{
		if ( money < 0 ) return ;
		m_iTotalFinances += money ;
	}

	void RemoveFinances(GMONEY money);

	INT64 GetTempFinances(){return m_iTempFinances;}
	INT64 GetTotalFinances(){return m_iTotalFinances;}

	SI16 GetLiquidationVillageNumber() { return m_siLiquidationVillageNumber; }

	void 	InitializeDB();
	void 	DoMsg_DBMsgResponse_GetMinisterInfo(sPacketHeader* pPacket);

	void 	DoMsg_GameMsgRequest_GetMinisterInfo(SI32 siID);

	void 	DoMsg_GameMsgRequest_SetMinisterInfo(cltMsg* pclMsg, SI32 siID);

	void 	DoMsg_DBMsgResponse_SetMinisterInfo(sPacketHeader* pPacket);

	// server.cpp�� serveraction���� �� ��
	void	DoMsgDBMsgRequest_SetGoonzuFinances(clock_t currentclock) ;
	void	ActionGameServerInfo(clock_t currentclock);

};

#endif