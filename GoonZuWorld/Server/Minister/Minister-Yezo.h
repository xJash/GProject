#ifndef _MINISTER_YEZO_H_
#define _MINISTER_YEZO_H_

#define MAX_YEZO_ANGELLIST		50

struct YezoAngelList
{
	TCHAR	szAccountID[32] ;
	TCHAR	szName[MAX_PLAYER_NAME] ;
	SI32	siLevel ;
	SI32	siFameLevel ;

	SI32	siPersonID ;
};

class CMinisterYezo: public CMinisterBase
{
public:
	SI32		m_siJapanSwordSolNum;	// �̵��ֱ� ���� ��	KIND_JAPANSWORDSOL
	SI32		m_siJapanGunSolNum;		// ���ѿֱ� ���� ��	KIND_JAPANGUNSOL
	SI32		m_siJapanCommanderNum;	// �ֱ���� ���� �� KIND_JAPANCOMMANDER
	SI32		m_siJapanPorterNum;		// ���ۿֱ� ���� �� KIND_JAPANPORTERSOL

	SI32		m_siWarVillageUnique;		// ���ۿֱ��� �ĵ� ���� ����ũ

#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, MAX_YEZO_ANGELLIST>	m_siAngel;
#else
	SI32		m_siAngel[MAX_YEZO_ANGELLIST];
#endif

#ifdef _SAFE_MEMORY
	NSafeTArray<YezoAngelList, MAX_YEZO_ANGELLIST>	m_stYezoAngelList;
	NSafeTArray<YezoAngelList, MAX_YEZO_ANGELLIST>	m_stYezoAngelApplyerList;
#else
	YezoAngelList	m_stYezoAngelList[MAX_YEZO_ANGELLIST]; // ��ȣõ���
	YezoAngelList	m_stYezoAngelApplyerList[MAX_YEZO_ANGELLIST]; // ��û�ڵ�
#endif

	bool IsValidAngelFromPersonID(SI32 personid);
	bool IsValidAngelFromCharID(SI32 charid);
	bool IsValidAngelFromCharName(const TCHAR * name);

	bool IsValidApplyerFromPersonID(SI32 personid);
	bool IsValidApplyerFromFromCharID(SI32 charid);
	bool IsValidApplyerFromFromCharName(const TCHAR * name);

	SI32 GetAngelNumber();

	CMinisterYezo();
	~CMinisterYezo();


	void 	InitializeDB();
	void 	DoMsg_DBMsgResponse_GetMinisterInfo(sPacketHeader* pPacket);
	
	void 	DoMsg_GameMsgRequest_GetMinisterInfo(SI32 siID);

	void 	DoMsg_GameMsgRequest_SetMinisterInfo(cltMsg* pclMsg, SI32 siID);
	
	void 	DoMsg_DBMsgResponse_SetMinisterInfo(sPacketHeader* pPacket);

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