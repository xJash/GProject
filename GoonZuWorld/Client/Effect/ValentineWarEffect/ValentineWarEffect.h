#ifndef _VALENTINEWAREFFECT_H_
#define _VALENTINEWAREFFECT_H_

#include <Directives.h>
#include <time.h>

#include "..\..\..\Common\SMLib\LibList\Obj.h"
#include "TSpr.h"

class	CValentineWarEffect
{
public:
	CValentineWarEffect( TSpr *pHeartEffect );
	~CValentineWarEffect();

	void		Action( SI32 siCouple );	// 이펙트를 그려야 할지 말지를 인자로 받음
	void		Draw( SI32 si32CenterXPos, SI32	si32CenterYPos );	

private:
	TSpr		*m_pValentineWarEffectTSPR;

	SI32		m_siValentineWarSprImageNum;

	SI32		m_siDelayFrame;

	SI32		m_siCurrentFrame;

	clock_t		m_ValentineWarClock;

	SI32		siCouple;
};

#endif