//
//
//  @ File Name : CAbstractState.h
//  @ Date : 2009-09-28
//  @ Author : �ڱ���
//	@ Desc : �߻� ���� Ŭ����
//


#if !defined(_CABSTRACTSTATE_H)
#define _CABSTRACTSTATE_H

#include "../CommonLogic.h"

class CAbstractState {
	virtual BOOL	Handle() = 0;
};

#endif  //_CABSTRACTSTATE_H
