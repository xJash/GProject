//
//
//  @ File Name : CBattleRoyalGameMode.h
//  @ Date : 2009-09-25
//  @ Author : 박기형
//
//

#if !defined(_CBATTLEROYALGAMEMODE_H)
#define _CBATTLEROYALGAMEMODE_H

#include "../CommonLogic.h"
#include "./CBattleRoyalPersonChangedData.h"
#include "./CBattleRoyalStadium.h"

enum 
{
	BATTLEROYALGAMEMODE_START = 0,
	//==================================================================
	BATTLEROYALGAMEMODE_NORMAL,					// 일반
	BATTLEROYALGAMEMODE_RESTRICTTOUSEHEALITEM,	// "힐링 아이템 사용 제한" 모드			
	BATTLEROYALGAMEMODE_ONEKILL,				// "HP 변경" 모드
	BATTLEROYALGAMEMODE_POWERUPONEUSER,			// "한 유저 파워 업" 모드
	//==================================================================
	BATTLEROYALGAMEMODE_END,
	BATTLEROYALGAMEMODE_COUNT = BATTLEROYALGAMEMODE_END -1
};

class CBattleRoyalGameMode {

public:
	CBattleRoyalGameMode();
	~CBattleRoyalGameMode();
	BOOL	Apply();					// GameMode 적용 시키기
	BOOL	RestrictToUseHealItem();	// "힐링 아이템 사용 제한" 모드
	BOOL	OneKill();					// "OneKill" 모드
	BOOL	PowerupOneUser();			// "한 유저 파워 업" 모드
	BOOL	DetermineMode();			// 모드 결정
	void	SetGamers(NkVector<CBattleRoyalPersonChangedData>& rclPersonChangedData, SI32	siCount
					 , NkVector<SI32>& rclMobData);
	BOOL	ChangeVisibleMode();		// 유저를 보여준다.
	BOOL	ChangeInvisibleMode(cltCharServer* pclChar);		// 유저를 가려준다.
	BOOL	ChangeCharBasicInfo();		// 게임 시 변경이 필요한 기본적인 캐릭터 정보 변경
	BOOL	RestoreCharInfo(cltCharServer* pclChar);		// 게임 종료, 게임 이탈 시 변경된 캐릭터 정보를 되돌려놓는다.
	BOOL	TransformChar();			// 유저를 몹으로 변신
	BOOL	TransformChar(cltCharServer* pclChar);			// 특정 유저를 몹으로 변신
	BOOL	RestoreTrancsformChar(cltCharServer* pclChar);	// 몹으로 변형된 유저를 원래 상태로 
	SI32	GetMode();
	void	SetMode(SI32 siMode);
	void	SetGameTime(SI32 siGameTime);
	BOOL	SetGMGameMode(SI32 siMode);
	BOOL	TakeinHorse(cltCharServer* pclChar);
protected:
	const static int LIMIT_COUNTERCHANGEPOWERUPCHAR = 3;
	SI32 m_siCountChangePowerupChar;
		
	NkVector<CBattleRoyalPersonChangedData>*	m_pclPersonChangedData;	// 변경된 개인 정보 리스트
	NkVector<SI32>*	m_pclMobData;	// 몹 charid
	SI32 m_siPersonDataCount;

	SI32 m_siMode;
	SI32 m_siGameTime;
	SI32 m_siGmGameMode;
	// 몹 kind값
	SI32 m_siKindBlackarmySword;
	SI32 m_siKindBlackarmyRifle;
	SI32 m_siKindBlackarmyKatar;
};

#endif  //_CBATTLEROYALGAMEMODE_H
