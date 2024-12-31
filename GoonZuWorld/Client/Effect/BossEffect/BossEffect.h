#ifndef _BOSSEFFECT_H_
#define _BOSSEFFECT_H_

#include <Directives.h>
#include <time.h>

#include "..\..\..\Common\SMLib\LibList\Obj.h"
#include "TSpr.h"

class	CBossEffect
{
public:
	CBossEffect( TSpr *pBigBossEffectTSPR, TSpr *pSmallBossEffectTSPR );
	~CBossEffect();

	void		Set( SI32 BossType );
	bool		Action();	// ���ϰ��� true �̸�, ���� ����Ʈ �� �����ٴ� ���� ����.
	void		Draw( SI32 si32CenterXPos, SI32	si32CenterYPos );	

	bool		GetBossEffectStatus();	

private:
	TSpr		*m_pBigBossEffectTSPR;
	TSpr		*m_pSmallBossEffectTSPR;


	SI32		m_siBossType;

	SI32		m_siBigBossSprImageNum;
	SI32		m_siSmallBossSprImageNum;
	SI32		m_siCurrentFrame;
	SI32		m_siBigBossMaxFrameNum;
	SI32		m_siSmallBossMaxFrameNum;

	SI32		m_siDelayFrame;

	bool		m_bBossEffectStatus;

	clock_t		m_delayClock;
};

#endif