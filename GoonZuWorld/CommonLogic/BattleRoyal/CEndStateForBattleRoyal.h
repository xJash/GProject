//
//
//  @ File Name : CEndStateForBattleRoyal.h
//  @ Date : 2009-09-25
//  @ Author : �ڱ���
//	@ Desc : ���� ���� Ŭ����
//


#if !defined(_CENDSTATEFORBATTLEROYAL_H)
#define _CENDSTATEFORBATTLEROYAL_H

#include "CBattleRoyalState.h"

class CEndStateForBattleRoyal : public CBattleRoyalState {

public:
	CEndStateForBattleRoyal();
	~CEndStateForBattleRoyal();
	BOOL	Handle();
};

#endif  //_CENDSTATEFORBATTLEROYAL_H
