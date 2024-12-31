//
//
//  @ File Name : CBattleRoyalMgr.h
//  @ Date : 2009-09-25
//  @ Author : �ڱ���
//	@ Desc : ��Ʋ �ξ� �Ŵ��� Ŭ����
//

#if !defined(_CBATTLEROYALMGR_H)
#define _CBATTLEROYALMGR_H

#include "../CommonLogic.h"
#include "./CBattleRoyal.h"

class CBattleRoyal;
class CDailyEventTimer;
class NUpdateTimer;

class CBattleRoyalMgr {
public:
	CBattleRoyalMgr(SI32 siGameMode = GAMEMODE_CLIENT);
	~CBattleRoyalMgr();

	BOOL	Create();  // ��Ʋ �ξ� ����
	void	Destroy(); // ��Ʋ �ξ� ����
	BOOL	Action();  // ������ ���� ����

	// ĳ���Ϳ� �´� ��Ʋ�ξ� ������ ���
	CBattleRoyal*	GetBattleRoyal(cltCharServer* pclChar);
	// GM ��ɾ�� ������ ��Ʋ�ξ� ���� ��Ű��,
	BOOL			OperatorGMBattleRoyal();
	// GM ��ɾ�� ��Ʋ�ξ� ���� ��� ���� �ϱ�
	BOOL			SetGMGameMode(SI32 siMode);
	// ���� �ܰ�� �ѱ��
	void			SetNextStep();
private:
	static const SI32 WAITTIME = 1000 * 60 * 4;
	static const SI32 STARTTIME = 1000 * 60 * 1;
	/*static const SI32 WAITTIME = 1000 ;
	static const SI32 STARTTIME = 1000 * 60 * 5 - 1000;*/
	static const SI32 GAMETIME = 1000 * 60 * 10;
	static const SI32 REWARDTIME = 1000 * 60 * 1;
	static const SI32 DAYTOHOURS = 24;
	static const SI32 EVENTREFRESHTIME = 3;

	// ��� �÷���
	SI32	m_siGameMode;

	CBattleRoyal*		m_pclMabriumBattleRoyal;		// ���긮�� ��Ʋ �ξ�
	CBattleRoyal*		m_pclGrandMabriumBattleRoyal;	// �׶����긮�� ��Ʋ �ξ�

	CDailyEventTimer	m_clEventWait;			// ���� ��� ���� Ÿ�̸�
	NUpdateTimer		m_clMarbriumChangeStateTimer;		// ���긮�� ���� ��ȯ Ÿ�̸�
	NUpdateTimer		m_clGrandMabriumChangeStateTimer;	// �׶����긮�� ���� ��ȯ Ÿ�̸�

	bool				m_bGMOperation;
	bool				m_bNextStep;
};

#endif  //_CBATTLEROYALMGR_H
