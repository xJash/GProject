//
//
//  @ File Name : CStartStateForBattleRoyal.h
//  @ Date : 2009-09-25
//  @ Author : �ڱ���
//	@ Desc : ���� ���� Ŭ����
//


#if !defined(_CSTARTSTATEFORBATTLEROYAL_H)
#define _CSTARTSTATEFORBATTLEROYAL_H

#include "CBattleRoyalState.h"

class CStartStateForBattleRoyal : public CBattleRoyalState {
public:
	CStartStateForBattleRoyal();
	~CStartStateForBattleRoyal();
	BOOL	Handle();
};

#endif  //_CSTARTSTATEFORBATTLEROYAL_H
