#pragma once

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "ndataTypes.h"
#include "ntimer.h"

const int ROULETTE_X		  = 150;
const int ROULETTE_Y		  = 250;
const int ROULETTE_WIDTH	  = 54;
const int ROULETTE_HEIGHT	  = 54;

struct RouletteTable
{
	bool m_bUserSelect;	// ������ ����
	bool m_bCpuSelect;	// ���Ͱ� ����
	bool m_bResult;		// ����� false :���� true�� ����

	SI16 m_siX;
	SI16 m_siY;

	SI16 m_siValue;		// �귿 ��ȣ

	void Set(bool bUserSelect, bool bCpuSelect, bool bResult, SI16 siX, SI16 siY, SI16 siValue )
	{
		m_bUserSelect = bUserSelect;
		m_bCpuSelect = bCpuSelect;
		m_bResult = bResult;

		m_siX = siX;
		m_siY = siY;
		
		m_siValue = siValue;
	};
};

class CRouletteLogic
{
private:

	RouletteTable	m_stRouletteTable[5][5];

	POINT			m_Mouse;
	SI16			m_siRandomValue[5];		// ���� ��ȣ ������
	SI32			m_siBettingCount;		// ��ι��� �� ��
	bool			m_bStart;

public:

	CRouletteLogic();
	~CRouletteLogic();

	void Init();	
	void StartRoulette();
	void CheckRoulette();			// ���� �귿 üũ
	void StopRoulette();
//	bool CheckLottoRoulette();		// ������� üũ

	bool SetMouseXY(SI32 x, SI32 y);
	void SetRandomValue(SI16 randomvalue[]);
	SI32 GetGourdNumber();


	inline void SetBettingCount(SI32 count)		{ m_siBettingCount = count; }
	inline void SetStart(bool value)			{ m_bStart = value;	}


	inline SI32	GetXPosition(SI32 y, SI32 x)	{ return m_stRouletteTable[y][x].m_siX; }
	inline SI32	GetYPosition(SI32 y, SI32 x)	{ return m_stRouletteTable[y][x].m_siY; }

	// ������ ������ �귿
	inline bool GetUserSelect(SI32 y, SI32 x)	{ return m_stRouletteTable[y][x].m_bUserSelect; }
	// CPU�� ������ �귿
	inline bool GetCpuSelect(SI32 y, SI32 x)	{ return m_stRouletteTable[y][x].m_bCpuSelect; }
	// �ش� �귿 �������� ���
	inline bool GetResult(SI32 y, SI32 x)		{ return m_stRouletteTable[y][x].m_bResult; }	
	// �ش� �귿�� ����
	inline SI32 GetValue(SI32 y, SI32 x)		{ return m_stRouletteTable[y][x].m_siValue; }	
	// ���� ���� 5�� ���
	inline SI16 GetRandom(SI32 index)			{ return m_siRandomValue[index]; }	
	inline SI32 GetBettingCount()				{ return m_siBettingCount; }	
	inline bool GetStart()						{ return m_bStart; }

	
};