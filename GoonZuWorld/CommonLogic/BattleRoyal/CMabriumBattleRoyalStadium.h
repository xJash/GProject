//
//
//  @ File Name : CMabriumBattleRoyalStadium.h
//  @ Date : 2009-09-25
//  @ Author : �ڱ���
//
//


#if !defined(_CMABRIUMBATTLEROYALSTADIUM_H)
#define _CMABRIUMBATTLEROYALSTADIUM_H

#include "CBattleRoyalStadium.h"

class CMabriumBattleRoyalStadiumServer : public CBattleRoyalStadiumServer{
public:
	CMabriumBattleRoyalStadiumServer();
	~CMabriumBattleRoyalStadiumServer();
	virtual BOOL	NoticeWait();	// ��Ʋ�ξ� ��⸦ �˸���.
	virtual BOOL	NoticeOpen();	// ������� ������ �˸���.
	virtual void	OpenGate();
};

class CMabriumBattleRoyalStadiumClient : public CBattleRoyalStadiumClient{
public:
	CMabriumBattleRoyalStadiumClient();
	~CMabriumBattleRoyalStadiumClient();
};

#endif  //_CMABRIUMBATTLEROYALSTADIUM_H
