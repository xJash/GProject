#ifndef _HEARTEFFECT_H_
#define _HEARTEFFECT_H_

#include <Directives.h>
#include <time.h>

#include "..\..\..\Common\SMLib\LibList\Obj.h"
#include "TSpr.h"

class	CHeartEffect
{
public:
	CHeartEffect( TSpr *pHeartEffect );
	~CHeartEffect();

	void		Action( bool bHeartEffect );	// ��Ʈ����Ʈ�� �׷��� ���� ������ ���ڷ� ����
	void		Draw( SI32 si32CenterXPos, SI32	si32CenterYPos );	

private:
	TSpr		*m_pHeartEffectTSPR;

	SI32		m_siHeartSprImageNum;

	SI32		m_siDelayFrame;
	
	SI32		m_siCurrentFrame;
	
	clock_t		m_HeartClock;

	bool		m_bHeartEffect;
};

#endif