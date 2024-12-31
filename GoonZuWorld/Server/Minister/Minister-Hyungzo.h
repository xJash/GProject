#ifndef _MINISTER_HYUNGZO_H_
#define _MINISTER_HYUNGZO_H_

// by LEEKH 2008-04-03 : ���Ȱ� �ִ� 7�����
#define MAX_HYUNGZO_POLICELIST 7
#define MAX_HYUNGZO_CRIMINALLIST 30

#define	SETCRIMINAL_SUCCESS				1
#define SETCRIMINAL_FAIL_ISGM			2

struct HyungzoPoliceList
{
	TCHAR	szAccountID[32] ;
	TCHAR	szName[MAX_PLAYER_NAME] ;
	SI32	siPersonID ;
	SI32	siLevel ;
};

struct HyungzoCriminalList
{
	TCHAR	szAccountID[32] ;
	TCHAR	szName[MAX_PLAYER_NAME] ;
	TCHAR	szReason[MAX_PRISON_REASON_SIZE];

	SI32	siPersonID ;
	SI32	siTime;
};

class CMinisterHyungzo : public CMinisterBase
{
public:
	SI16	m_siLimitStealNum;
	SI16	m_siSuspectTime;
	SI16	m_siPrisonTime;
	SI16	m_siPrisonerPenalty;

#ifdef _SAFE_MEMORY
	NSafeTArray<HyungzoMember, MAX_PRISON_LIST_NUM>				m_stHyungzoMember;
	NSafeTArray<HyungzoPoliceList, MAX_HYUNGZO_POLICELIST>		m_stHyungzoPoliceList;
	NSafeTArray<HyungzoCriminalList, MAX_HYUNGZO_CRIMINALLIST>	m_stHyungzoCriminalList;
#else
	HyungzoMember		m_stHyungzoMember[MAX_PRISON_LIST_NUM];
	HyungzoPoliceList	m_stHyungzoPoliceList[MAX_HYUNGZO_POLICELIST];
	HyungzoCriminalList	m_stHyungzoCriminalList[MAX_HYUNGZO_CRIMINALLIST];
#endif

	CMinisterHyungzo();
	~CMinisterHyungzo();

	void 	InitializeDB();
	void 	DoMsg_DBMsgResponse_GetMinisterInfo(sPacketHeader* pPacket);

	void 	DoMsg_GameMsgRequest_GetMinisterInfo(SI32 siID);

	void 	DoMsg_GameMsgRequest_SetMinisterInfo(cltMsg* pclMsg, SI32 siID);

	void 	DoMsg_DBMsgResponse_SetMinisterInfo(sPacketHeader* pPacket);

	void	DoMsg_GameMsgRequest_SetHyungPrison(cltMsg* pclMsg,SI32 siID);
	
	// Server&Client
	void	DoMsg_GameMsgRequest_GetPoliceList(cltMsg* pclMsg,SI32 siID);
	void	DoMsg_GameMsgRequest_SetPolice(cltMsg* pclMsg,SI32 siID);

	void	DoMsg_GameMsgRequest_GetCriminalList(cltMsg* pclMsg,SI32 siID);
	void	DoMsg_GameMsgRequest_SetCriminal(cltMsg* pclMsg,SI32 siID);

	// Server&DB
	void	DoMsg_DBMsgResponse_GetPoliceList(sPacketHeader* pPacket); // ���� ��� ��û ����
	void	DoMsg_DBMsgResponse_SetPolice(sPacketHeader* pPacket); // ���� �Ӹ� �� ���� ����

	void	DoMsg_DBMsgResponse_GetCriminalList(sPacketHeader* pPacket); // ����� ��� ��û ����
	void	DoMsg_DBMsgResponse_SetCriminal(sPacketHeader* pPacket); // ����� �Ӹ� �� ���� ����

	bool	IsValidPoliceFromPersonID(SI32 personid);
};

#endif