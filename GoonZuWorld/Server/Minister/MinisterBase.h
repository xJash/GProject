#ifndef _MINISTERBASE_H_
#define _MINISTERBASE_H_


struct sPacketHeader;
class cltMsg;

class CMinisterBase
{
public:

	// ������ �̸� , �ڱ�Ұ�
	TCHAR			m_szAccountID[MAX_PLAYER_NAME];		// ����
	TCHAR			m_szPersonName[MAX_PLAYER_NAME];	// PERSON NAME
	TCHAR			m_szGreeting[256];					// �λ縻 

	CMinisterBase();
	virtual ~CMinisterBase() {};

	void			Set(CMinisterBase *pMinister);

	virtual	void 	InitializeDB() {};
	virtual	void 	DoMsg_DBMsgResponse_GetMinisterInfo(sPacketHeader* pPacket) {};

	virtual	void 	DoMsg_GameMsgRequest_GetMinisterInfo(SI32 siID) {};

	virtual	void 	DoMsg_GameMsgRequest_SetMinisterInfo(cltMsg* pclMsg, SI32 siID) {} ;

	virtual	void 	DoMsg_DBMsgResponse_SetMinisterInfo(sPacketHeader* pPacket) {};
						

};

#endif