//
//
//  @ File Name : CBattleRoyalReward.h
//  @ Date : 2009-09-25
//  @ Author : �ڱ���
//
//
#if !defined(_CBATTLEROYALREWARD_H)
#define _CBATTLEROYALREWARD_H

#include "../CommonLogic.h"

class CBattleRoyalReward {

public :
	CBattleRoyalReward();
	~CBattleRoyalReward();
	BOOL	Create();										// ����
	BOOL	GiveRewardToWinner(cltCharCommon* pclChar);		// ����ڿ��� �����ϱ�
	BOOL	GiveRewardToKillingUser(cltCharCommon* pclChar);// ������ ������ ���� �������� �����ϱ� 

protected :
	BOOL	GiveReward( UI32 uiCharID, UI32 uiItemUnique, UI32 uiItemNum, SI32 siInputMode);

	CRewardTypeItemByProbMgr* m_pclRewardItemToWinner;		// ��� ���� ������ �Ŵ���
	CRewardTypeItemByProbMgr* m_pclRewardToKillingUser;		// ���� ���� ���� ������ �Ŵ���

};

#endif  //_CBATTLEROYALREWARD_H
