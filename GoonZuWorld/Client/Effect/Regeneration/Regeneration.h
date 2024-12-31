#ifndef _REGENERATION_H_
#define _REGENERATION_H_

#include <Directives.h>
#include <time.h>

#include "..\..\..\Common\SMLib\LibList\Obj.h"
#include "TSpr.h"

class	CRegeneration
{
public:
	CRegeneration( TSpr *pRegenerationTSPR );
	~CRegeneration();

	void		Set();
	bool		Action();	// ���ϰ��� true �̸�, ���� ����Ʈ �� �����ٴ� ���� ����.
	
	void		DrawBottom( SI32 si32CenterXPos, SI32	si32CenterYPos );
	void		DrawCenter( SI32 si32CenterXPos, SI32	si32CenterYPos );

	bool		GetRegenerationStatus();		// true = ���� ����

private:
	TSpr		*m_pRegenerationTSPR;

	SI32		m_siSprImageNum;
	SI32		m_siCurrentFrame;
	SI32		m_siMaxFrameNum;

	SI32		m_siDelayFrame;

	bool		m_bRegenerationStatus;

	clock_t		m_delayClock;

};

#endif