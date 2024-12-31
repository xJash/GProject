//-----------------------------------------------------------------------------
// 2007/04/16 �̰���
//-----------------------------------------------------------------------------
#ifndef _NUPDATETIMER_H
#define _NUPDATETIMER_H

//-----------------------------------------------------------------------------
// class NUpdateTimer
//-----------------------------------------------------------------------------
class NUpdateTimer
{
private:
	bool			m_bActivated;
	UI64			m_uiStartTime;
	UI64			m_uiTimePeriod;

public:
	NUpdateTimer()
	{
		m_bActivated	= false;

		m_uiStartTime	= 0;
		m_uiTimePeriod	= 0;
	}
	~NUpdateTimer()
	{
	}

	bool IsTimed(UI64 uiCurrentTime, bool bReActiveated = true)
	{
		if(!IsActivated())		{		return false;		}							// ACTIVATED �Ǿ� ���������� �����.

		bool bTimed = false;
		bTimed = uiCurrentTime - m_uiStartTime >= m_uiTimePeriod;

		if(bTimed)	SetActive(bReActiveated, uiCurrentTime);

		return bTimed;
	}

	bool Init(UI64 uiPeriodMS)
	{
		m_bActivated	= FALSE;
		m_uiStartTime	= 0;
		m_uiTimePeriod	= uiPeriodMS;


		return true;
	}

	inline void SetPeriod(UI32 uiPeriodMS)
	{
		m_uiTimePeriod = uiPeriodMS;
	}

	void SetActive(bool bActivate, UI64 uiCurrentTime)
	{
		m_bActivated = bActivate;
		m_uiStartTime= uiCurrentTime;
	}

	bool IsActivated()				{		return m_bActivated;			}

};

#endif

