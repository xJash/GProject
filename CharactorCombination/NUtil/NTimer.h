#ifndef _NTIMER_H
#define _NTIMER_H

#include <windows.h>
#include "ndatatypes.h"

class NTimer
{
public:
	NTimer();
	~NTimer();

	enum TIMER_STATE
	{
		OFF = 0,
		ON,
		HOLD,
	};

	void	Start();
	void	Stop();
	void	Suspend();
	void	Resume();	

	REAL32	GetCurrentTime();					// ���� �ð��� ��´� 
	REAL32	GetElapsedTime();					// Start���� �Ͻ� ������ �ð��� ������ ��� �ð��� ��´� 
	REAL32	GetSuspendTime();					// Start���� �Ͻ� ������ �ð��� ��´� 

private:
	static BOOL		m_bTimerInitialized;
	static LONGLONG	m_llQPFTicksPerSec;

    LONGLONG		m_llStartTime;				// ���� �ð� 
	LONGLONG		m_llStopTime;				// ����/�Ͻ����� �ð� 
	LONGLONG		m_llSuspendTime;			// �Ͻ������� �ð� 

	TIMER_STATE		m_state;					// ���� 
};

#endif
