//
//
//  @ File Name : CWaitStateForBattleRoyal.h
//  @ Date : 2009-09-25
//  @ Author : �ڱ���
//	@ Desc : ��� ���� Ŭ����
//

#if !defined(_CWAITSTATEFORBATTLEROYAL_H)
#define _CWAITSTATEFORBATTLEROYAL_H

#include "./CBattleRoyalState.h"

class CWaitStateForBattleRoyal : public CBattleRoyalState {
public:
	CWaitStateForBattleRoyal();
	~CWaitStateForBattleRoyal();
	BOOL	Handle();
};

#endif  //_CWAITSTATEFORBATTLEROYAL_H
