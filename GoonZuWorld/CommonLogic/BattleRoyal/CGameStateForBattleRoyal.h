//
//
//  @ File Name : CGameStateForBattleRoyal.h
//  @ Date : 2009-09-25
//  @ Author : �ڱ���
//	@ Desc : ���� ���� Ŭ����
//


#if !defined(_CGAMESTATEFORBATTLEROYAL_H)
#define _CGAMESTATEFORBATTLEROYAL_H

#include "CBattleRoyalState.h"

class CGameStateForBattleRoyal : public CBattleRoyalState {
public:
	CGameStateForBattleRoyal();
	~CGameStateForBattleRoyal();
	BOOL	Handle();
};

#endif  //_CGAMESTATEFORBATTLEROYAL_H
