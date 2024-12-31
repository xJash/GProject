//
//
//  @ File Name : CBattleRoyalStadium.h
//  @ Date : 2009-09-25
//  @ Author : �ڱ���
//
//
#if !defined(_CBATTLEROYALSTADIUM_H)
#define _CBATTLEROYALSTADIUM_H

#include "../CommonLogic.h"
#include "./CBattleRoyalPersonChangedData.h"

class cltCommonLogic;
class cltServer;
class cltClient;

class CBattleRoyalStadium {

public:
	CBattleRoyalStadium();
	virtual ~CBattleRoyalStadium();
	
	virtual BOOL	Init();			// ������ �ʱ�ȭ
	BOOL	IsOpenedGate();	// ����� �Ա��� ���� �ִ���?
	virtual void	OpenGate();		// ����� �Ա��� ����.
	void	CloseGate();	// ����� �Ա��� �ݴ´�.
	BOOL	NoticeResult();	// ����� �˸���.
	virtual BOOL DeleteGamer(SI32 siPersonID);
	// ���� ���� �ּ� ����
	UI32	GetCanEnterMinLevel();
	// ���� ���� �ִ� ����
	UI32	GetCanEnterMaxLevel();

	SI32	GetMapIndex();

	cltCharCommon* GetWinner();
	// �ִ� ���� ��
	const static SI32 MAX_UNIT_COUNT = 30;	
protected:
	
	// ���� ���� ������
	cltCommonLogic*	m_pclCommon;

	// �� �ε���
	SI32	m_siMapIndex;
	// �� �ִ� ��
	SI32	m_siMobCount;

	// ������� ���� ���� �ִ���?
	bool	m_bOpenGame;

	// ����� ����
	cltCharCommon* m_pclWinner;

	// ���� ���� �ּ� ����
	UI32	m_uiCanEnterMinLevel;
	// ���� ���� �ִ� ����
	UI32	m_uiCanEnterMaxLevel;
	// ���� ����
	SI32	m_siKindBlackarmySword;
	SI32	m_siKindBlackarmyRifle;
	SI32	m_siKindBlackarmyKatar;

};

class CBattleRoyalStadiumServer : public CBattleRoyalStadium {

public:
	CBattleRoyalStadiumServer();
	virtual ~CBattleRoyalStadiumServer();

	// �ִ� ������ ��
	const static SI32 MAX_GAMER_COUNT = 20;	

	BOOL	Init();
	void	InitData();			// ������ �ʱ�ȭ
	BOOL	IsLimitedGamerNum();// ������ ���� �Ѱ�ġ�ΰ�?
	UI32	GetWaitGamerNum();	// ��⿡ ��� ���� ���� ���� �����ش�.
	virtual BOOL	NoticeWait() = 0;	// ��Ʋ�ξ� ��⸦ �˸���.
	virtual BOOL	NoticeOpen() = 0;	// ������� ������ �˸���.
	BOOL	SaveGamerList();// ��⿡ ������ ����Ʈ�� �����Ѵ�.
	BOOL	CreateMob();	// ���� �����Ѵ�.
	BOOL	RemoveMob();	// ���� �����Ѵ�.
	BOOL	BanGamer();		// �����ڸ� ����忡�� �����Ų��.
	BOOL	NoticeResult();	// ����� �˸���.
	BOOL	WasJoinedLastGame(SI32 m_siPersonId); // ������ ��⿡ ���� �߾�����?
	UI32	GetGamerNum();	// ��⿡ ������ ���� ��
	UI32	GetGamingGamerNum();	// ��⿡ ������ ���� ���� ��
	UI32	GetMobNum();	// ��⿡ �����ϴ� ���� ��
	BOOL	ProcessResult();// ����� ó���Ѵ�.
	void	DieMob();		// �� ����
	BOOL	DeleteGamer(SI32 siPersonID);
	void	ProcessLogoutCharByIndex(SI32 siIndex);

	NkVector<CBattleRoyalPersonChangedData>& GetPersonChangedData();
	NkVector<SI32>& GetMobData();

	cltCharServer*	GetGamingCharByIndex(SI32 siIndex);
	
	virtual void OpenGate() = 0;
protected:
	// �� ĳ���� ID
	NkVector<SI32>	m_MobCharIDArray;
	// �� ��� ������ �迭
	NkVector<SI32>	m_BeforeGamerArray;
	// ������ �迭
	NkVector<CBattleRoyalPersonChangedData>	m_GamerArray;

	// ���� ���� ������
	cltServer*	m_pclServer;
	
	// �� ��� ������ ��
	SI32	m_siBeforeGamerCount;
	
	// ������ ��
	SI32	m_siGamerCount;
	// �������� ���ڰ� ��
	SI32	m_siGamingUserCount;

	BOOL	Notice(TCHAR* pszContentText);		// �����ϱ�
};

class CBattleRoyalStadiumClient : public CBattleRoyalStadium{

public:
	CBattleRoyalStadiumClient();
	virtual ~CBattleRoyalStadiumClient();
	BOOL	DeleteGamer(SI32 siPersonID);	// ������ ����
	BOOL	NoticeResult();	// ����� �˸���.
protected:
	// Ŭ���̾�Ʈ ���� ������
	cltClient*	m_pclClient;
};


#endif  //_CBATTLEROYALSTADIUM_H
