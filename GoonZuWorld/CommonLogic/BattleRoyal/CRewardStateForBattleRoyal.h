//
//
//  @ File Name : CRewardStateForBattleRoyal.h
//  @ Date : 2009-09-25
//  @ Author : �ڱ���
//	@ Desc : ���� ���� Ŭ����
//


#if !defined(_CREWARDSTATEFORBATTLEROYAL_H)
#define _CREWARDSTATEFORBATTLEROYAL_H

#include "CBattleRoyalState.h"

class CRewardStateForBattleRoyal : public CBattleRoyalState {
public:
	CRewardStateForBattleRoyal();
	~CRewardStateForBattleRoyal();
	BOOL	Handle();
};

#endif  //_CREWARDSTATEFORBATTLEROYAL_H
