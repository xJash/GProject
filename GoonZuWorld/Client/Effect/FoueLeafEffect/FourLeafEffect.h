#ifndef _FOURLEAFEFFECT_H_
#define _FOURLEAFEFFECT_H_

#include <Directives.h>
#include <time.h>

#include "..\..\..\Common\SMLib\LibList\Obj.h"
#include "TSpr.h"

class	CFourLeafEffect
{
public:
	CFourLeafEffect( TSpr *pHeartEffect );
	~CFourLeafEffect();

	void		Action( bool bFourLeafEffect );	// ����Ʈ�� �׷��� ���� ������ ���ڷ� ����
	void		Draw( SI32 si32CenterXPos, SI32	si32CenterYPos );	

private:
	TSpr		*m_pFourLeafEffectTSPR;

	SI32		m_siFourLeafSprImageNum;

	SI32		m_siDelayFrame;

	SI32		m_siCurrentFrame;

	clock_t		m_FourLeafClock;

	bool		m_bFourLeafEffect;
};

#endif