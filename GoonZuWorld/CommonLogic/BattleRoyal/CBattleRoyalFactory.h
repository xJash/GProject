//
//
//  @ File Name : CBattleRoyalFactory.h
//  @ Date : 2009-09-25
//  @ Author : �ڱ���
//	@ Desc : ��Ʋ�ξ� Factory Ŭ����
//


#if !defined(_CBATTLEROYALFACTORY_H)
#define _CBATTLEROYALFACTORY_H

#include "../CommonLogic.h"
#include "./CBattleRoyal.h"

class CBattleRoyal;

class CBattleRoyalFactory {

public :
	static const SI32 MABRIUM = 1;			// ���긮��
	static const SI32 GRANDMABRIUM = 2;		// �׶����긮��

	static CBattleRoyal*	CreateBattleRoyal(SI32 siKind);					  // ��Ʋ�ξ� ����
	static BOOL				DestroyBattleRoyal(CBattleRoyal* pclBattleRoyal); // ��Ʋ�ξ� ����
};

#endif  //_CBATTLEROYALFACTORY_H
