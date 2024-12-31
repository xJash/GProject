//
//
//  @ File Name : CBattleRoyalClient.h
//  @ Date : 2009-09-25
//  @ Author : �ڱ���
//	@ Desc : ��Ʋ�ξ� ó�� Ŭ����
//


#if !defined(_CBATTLEROYALCLIENT_H)
#define _CBATTLEROYALCLIENT_H

#include "../CommonLogic.h"

#include "./CBattleRoyalGameMode.h"
#include "./CBattleRoyalReward.h"
#include "./CBattleRoyalStadium.h"

class CBattleRoyalGameMode;
class CBattleRoyalReward;
class CBattleRoyalStadium;

class CBattleRoyalClient {

public:
	CBattleRoyalClient();
	virtual ~CBattleRoyalClient();

	BOOL	Create();		// ����
	BOOL	NoticeResult(bool bResult, TCHAR* pszWinnerName, SI32 siMapIndex);	// ��� �˸���
	BOOL	RequestTime();	// �ð� ��û
	BOOL	ShowTime(SI32 siTime);		// �ð� �����ֱ�
	void	SetGameMode(SI32 siMode);
	void	ShowTimerForGamingState(SI32 siTime); 
	void	HideTimerForGamingState(); 
	BOOL	IsTransform(cltCharClient* pclChar);
	void	ShowWarpButton();
protected:
	cltClient* m_pclClient;

	SI32 m_siMode;

	CBattleRoyalGameMode*		m_pclGameMode;	// ���� ���
	CBattleRoyalReward*			m_pclReward;	// ����
	CBattleRoyalStadium*		m_pclStadium;	// �����
};

#endif  //_CBATTLEROYALCLIENT_H