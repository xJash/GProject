//
//
//  @ File Name : CGrandMabriumBattleRoyalStadium.h
//  @ Date : 2009-09-25
//  @ Author : �ڱ���
//
//


#if !defined(_CGRANDMABRIUMBATTLEROYALSTADIUM_H)
#define _CGRANDMABRIUMBATTLEROYALSTADIUM_H

#include "CBattleRoyalStadium.h"

class CGrandMabriumBattleRoyalStadiumServer : public CBattleRoyalStadiumServer{
public:
	CGrandMabriumBattleRoyalStadiumServer();
	~CGrandMabriumBattleRoyalStadiumServer();
	virtual BOOL	NoticeWait();	// ��Ʋ�ξ� ��⸦ �˸���.
	virtual BOOL	NoticeOpen();	// ������� ������ �˸���.
	virtual void	OpenGate();
};

class CGrandMabriumBattleRoyalStadiumClient : public CBattleRoyalStadiumClient{
public:
	CGrandMabriumBattleRoyalStadiumClient();
	~CGrandMabriumBattleRoyalStadiumClient();
};

#endif  //_CGRANDMABRIUMBATTLEROYALSTADIUM_H
