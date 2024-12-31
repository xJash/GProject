#ifndef _MINISTERMGR_H_
#define _MINISTERMGR_H_

enum  
{
	MINISTER_TYPE_START = 1,
	MINISTER_IZO = MINISTER_TYPE_START,	// �����Ǽ� 
	MINISTER_HOZO,						// ȣ�� 
	MINISTER_YEZO,						// ����
	MINISTER_BYUNGZO,					// ���� 
	MINISTER_HYUNGZO,					// ���� 
	MINISTER_GONGZO,					// ���� 
	MINISTER_GOONZU,					// ����
	MINISTER_LAST = MINISTER_GOONZU,
	MINISTER_TOTAL,
};

class CMinisterBase;

class CMinisterMgr
{

public:
#ifdef _SAFE_MEMORY
	NSafeTArray<CMinisterBase*, MINISTER_TOTAL>		m_MinisterBase;
#else
	CMinisterBase	*m_MinisterBase[MINISTER_TOTAL];		// 6���� Pointer 
#endif


	CMinisterMgr();
	~CMinisterMgr();


	void	Initialize();
	void	Destroy();
	CMinisterBase *GetMinister(SI32 siKind);

	//===============================================================================
	// SERVER - DB : Server�� �ʱ� ���ý� DB�κ��� ������ ���´�.
	//===============================================================================
	// DB�� Get�� ��û�Ѵ�.
	void	InitializeDB();			
	// DB���� �Ǽ� ������ ������ ���� Class�� �����Ѵ�.
	void	DoMsg_DBMsgResponse_GetMinisterInfo(SI32 siKind, sPacketHeader* pPacket);
	//===============================================================================

	//===============================================================================
	// CLIENT - SERVER : Client�� ��û�� ���� Server�� ������ ���� 
	//===============================================================================
	// Client���� �Ǽ��� ������ ��û�ϸ� ���� Class�� �ִ� ������ �����Ѵ�.
	void	DoMsg_GameMsgRequest_GetMinisterInfo(SI32 siID, SI32 siKind);
	//===============================================================================

	//===============================================================================
	// CLIENT - SERVER - DB : Client�� Set��û�� DB�� ���� �����ϰ� Client�� �����Ѵ�.
	//===============================================================================
	// Client���� �Ǽ������� ���� �����ϱ⸦ ���ϸ� ���������� DB�� ���� ������ ��û�Ѵ�.
	void	DoMsg_GameMsgRequest_SetMinisterInfo(cltMsg* pclMsg, SI32 siID, SI32 siKind);
	// DB���� ������ ���Ⱑ �Ϸ�Ǹ� Client���� �ٽ� �����Ͽ��ش�.
	void    DoMsg_DBMsgResponse_SetMinisterInfo(SI32 siKind, sPacketHeader* pPacket);
	//===============================================================================
};



#endif