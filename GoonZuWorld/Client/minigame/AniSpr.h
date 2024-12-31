#ifndef _ANI_SPR_
#define _ANI_SPR_

#include "../Lib/Graphic/graphic.h"
#include "../lib/ngraphics/graphics.h"

#include "ndataTypes.h"
#include "ntimer.h"
#include "TSpr.h"

class CAniSpr
{
public:
	TSpr		m_pSpr;

	SI32		m_MaxFrame;		// ������ ����
	SI32		m_NowFrame;		// ���� ������
	
	UI32		m_DelayTime;	// ���� �ð�
	UI32		m_LastTime;		

public:
	CAniSpr();
	~CAniSpr();

	void	SetAniData(SI32 delay);
	void	ResetFrame();
	void	Release();								// ���� 
	int		AniProc();								// ������ ����
	int		AniProcEnd();
	
	BOOL	LoadSpr(TCHAR* pName, SI32 delay);
	void	DrawAniSpr(SI32 x, SI32 y, SI32 imagenum =0);
	void	DrawAniSprT(SI32 x, SI32 y, SI32 imagenum =0);
};

#endif