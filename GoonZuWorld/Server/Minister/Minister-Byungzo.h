#ifndef _MINISTER_BYUNGZO_H_
#define _MINISTER_BYUNGZO_H_

// by LEEKH 2008-04-03 : ���Ǳ��� ���ְ��� ȸ�� 10ȸ�� ����
#define MAX_SETWARCOUNT	10

class CMinisterByungzo : public CMinisterBase
{
public:
	SI32				m_siPersonID;

	SI32				m_siSetTime;				// ���Ｓ���ð�
	SI32				m_siWarStartTime;			// ������۽ð�
	SI16				m_siSetWarCount;			// ���Ｓ�� Ƚ��
	UI32				m_siBlackArmyNum;			// ���� ���� ���� ��

	SI32				m_siVillageWarTime;	// �����ð� �� 
	
	CMinisterByungzo();
	~CMinisterByungzo();


	void 	InitializeDB();
	void 	DoMsg_DBMsgResponse_GetMinisterInfo(sPacketHeader* pPacket);

	void 	DoMsg_GameMsgRequest_GetMinisterInfo(SI32 siID);

	void 	DoMsg_GameMsgRequest_SetMinisterInfo(cltMsg* pclMsg, SI32 siID);

	void 	DoMsg_DBMsgResponse_SetMinisterInfo(sPacketHeader* pPacket);
	
};

#endif