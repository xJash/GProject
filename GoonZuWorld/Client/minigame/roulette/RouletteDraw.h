#pragma once

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "../Lib/Graphic/graphic.h"
#include "../lib/ngraphics/graphics.h"

#include "ndataTypes.h"
#include "ntimer.h"
#include "../Client/MiniGame/AniSpr.h"

class CRouletteDraw
{
private:

	
	TSpr			m_sprNumber;		// ������
	TSpr			m_sprNumber2;		// �ڼ� ǥ��
	TSpr			m_sprCpuSelect;
	TSpr			m_sprDot;			// ����ڿ�

	CAniSpr			m_aniBird;
	CAniSpr			m_aniRoll;			// ���ư��� ���
	

public:

	CRouletteDraw();
	~CRouletteDraw();

	bool LoadImage();
	void FreeImage();

	void DrawRouletteBack(SI32 x, SI32 y, SI32 imagenum =0); // ����� �׸���
	void DrawNumber(SI32 x, SI32 y, SI32 imagenum = 0);
	void DrawNumber2(SI32 x, SI32 y, SI32 imagenum = 0);
	void DrawCpuSelect(SI32 x, SI32 y, SI32 imagenum = 0);
	void DrawUserSelect(SI32 x, SI32 y);
	void DrawBird(SI32 x, SI32 y);
	void DrawRoll(SI32 x, SI32 y, SI32 delay);
};