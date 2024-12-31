#ifndef _MINISTER_HOZO_H_
#define _MINISTER_HOZO_H_

#include "MinisterBase.h"

#define UNIT_HOZO_SETMONEY			100000

#define MAX_HOZO_FIXATIONMONEY		10
//cyj ���ΰ� �����Ǳ� ������ �ű����� ������ 0���� ���� /[����] �ٽ� ���
#define MIN_HOZO_FIXATIONMONEY		1
//#define MIN_HOZO_FIXATIONMONEY	0

#define MAX_HOZO_PRIZEMONEY			50
#define MIN_HOZO_PRIZEMONEY			1

#define MAX_HOZO_CHANGEDNAME_LIST	100

#define MAX_HOZO_ANGELLIST			50

// [����] �ʺ��� ���� : ���ֹ��� ����
const SI32 Const_Min_Hozo_Dividend_Money = 1;
const SI32 Const_Max_Hozo_Dividend_Money = 3;

struct ChangedNameChar
{
	SI32	siDate;

	TCHAR	szOldName[MAX_PLAYER_NAME];
	TCHAR	szNewName[MAX_PLAYER_NAME];
};

struct HozoAngelList
{
	TCHAR	szAccountID[32] ;
	TCHAR	szName[MAX_PLAYER_NAME] ;
	SI32	siLevel ;
	SI32	siFameLevel ;

	SI32	siPersonID ;
};

class CMinisterHozo : public CMinisterBase
{
public:
	SI32	m_siResidentNum;	// �ֹ��� ��
	SI32	m_siMaxShop;		// ������ �� ������

	SI32	m_siTotalCharNum;	// �� �鼺��
	SI32	m_siCalcTime;		// �� �鼺�� ����� �ð�
	
	GMONEY	m_siPrizeMoney;		// ��õ�ο��� �־�� �� ����� ( ���� 10�� )
	SI32	m_siPrizeSetTime;	// ����� ���� �ð�
	GMONEY	m_siFixationMoney;

	GMONEY	m_siTutorialVillageDivideend;	// [����]�ʺ��� ���� ���ֹ���

#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, MAX_HOZO_ANGELLIST>		m_siAngel;
#else
	SI32	m_siAngel[MAX_HOZO_ANGELLIST];
#endif

#ifdef _SAFE_MEMORY
	NSafeTArray<HozoAngelList, MAX_HOZO_ANGELLIST>		m_stHozoAngelList;
	NSafeTArray<HozoAngelList, MAX_HOZO_ANGELLIST>		m_stHozoAngelApplyerList;
#else
	HozoAngelList	m_stHozoAngelList[MAX_HOZO_ANGELLIST]; // ��ȣõ���
	HozoAngelList	m_stHozoAngelApplyerList[MAX_HOZO_ANGELLIST]; // ��û�ڵ�
#endif
	SI32	m_siNewCharNum;

	// �Ļ� ���� ����
	SI16	m_siBankruptcyVillageNumber;
	SI32	m_siSetBankruptcyVillageDate;

	GMONEY	GetPrizeMoney()				{ return m_siPrizeMoney * UNIT_HOZO_SETMONEY; }
	GMONEY	GetFizationMoney()			{ return m_siFixationMoney * UNIT_HOZO_SETMONEY; }
	GMONEY	GetBeginnerVillageMoney()	{ return m_siTutorialVillageDivideend * UNIT_HOZO_SETMONEY; }
	
	SI32	GetMaxShopNum(){return m_siMaxShop;}
	
	bool IsValidAngelFromPersonID(SI32 personid);
	bool IsValidAngelFromCharID(SI32 charid);
	bool IsValidAngelFromCharName(const TCHAR * name);

	bool IsValidApplyerFromPersonID(SI32 personid);
	bool IsValidApplyerFromFromCharID(SI32 charid);
	bool IsValidApplyerFromFromCharName(const TCHAR * name);

	SI32 GetAngelNumber();
	
	CMinisterHozo();
	~CMinisterHozo();

	void 	InitializeDB();
	void 	DoMsg_DBMsgResponse_GetMinisterInfo(sPacketHeader* pPacket);

	void 	DoMsg_GameMsgRequest_GetMinisterInfo(SI32 siID);

	void 	DoMsg_GameMsgRequest_SetMinisterInfo(cltMsg* pclMsg, SI32 siID);

	void 	DoMsg_DBMsgResponse_SetMinisterInfo(sPacketHeader* pPacket);

	void	DoMsg_DBMsgResponse_GetDailyNewChar(sPacketHeader* pPacket);

	// Server&Client
	void	DoMsg_GameMsgRequest_GetAngelApplyerList(cltMsg* pclMsg, SI32 siID); // ��ȣõ�� ��û�� ��� ��û
	void	DoMsg_GameMsgRequest_GetAngelList(cltMsg* pclMsg, SI32 siID); // ��ȣõ�� ��� ��û 

	void	DoMsg_GameMsgRequest_SetAngelApplyer(cltMsg* pclMsg, SI32 siID); // ��ȣõ�� ��� ��û
	void	DoMsg_GameMsgRequest_SetAngel(cltMsg* pclMsg, SI32 siID); // ��ȣõ�� �Ӹ� �� ����

	// Server&DB
	void	DoMsg_DBMsgResponse_GetAngelApplyerList(sPacketHeader* pPacket); // ��ȣõ�� ��û�� ��� ��û ����
	void	DoMsg_DBMsgResponse_GetAngelList(sPacketHeader* pPacket); // ��ȣõ�� ��� ��û ����

	void	DoMsg_DBMsgResponse_SetAngelApplyer(sPacketHeader* pPacket); // ��ȣõ�� ��� ��û ����
	void	DoMsg_DBMsgResponse_SetAngel(sPacketHeader* pPacket); // ��ȣõ�� �Ӹ� �� ���� ����



};

#endif