#ifndef _SERVER_EVENT_INSTANCEMAPINFO_H_
#define _SERVER_EVENT_INSTANCEMAPINFO_H_

#pragma once

#include "../CommonLogic/CommonLogic.h"

//#define SERVER_EVENT_INSTANCE_MAP_START_INDEX 357
#define SERVER_EVENT_INSTANCE_MAP			  4	

class CNInstanceMapInfo
{
public:
	CNInstanceMapInfo();	
	~CNInstanceMapInfo();

	void		Clear(void);
	void		DeleteGate(void);
	void		Action(void);
	
	// �δ� ���� ��.
	void		SetScore(SI64 _siScore);
	SI64 		GetScore(void);
	void		AddScore(SI64 _siAddScore);
		
	// �δ����� ������� Ŭ���� �ܰ�.
	void		SetMapClear(SI16 _Index, bool _bMapClear);
	bool 		GetMapClear(SI16 _Index);
    bool		IsAllMapClear(void);
	void		SetMapStepCount(SI16 _Index, SI16 _siMapStepCount);
	SI16 		GetMapStepCount(SI16 _Index);
	void		AddMapStepCount(SI16 _Index, SI16 _siOpenCount);
	SI16 		GetMapStepCountSum(void);
	
	// �δ��ð�
	void		SetStartTime( DWORD _dwStartTime );
	DWORD		GetStartTime( void );
	
	// ����Ʈ ����
	void		OpenTheGate( void );
	void		CloseTheGate( void );
	void		LeaveLobbyInUser( void );
	
private:

#ifdef _SAFE_MEMORY
	NSafeTArray<bool, SERVER_EVENT_INSTANCE_MAP>		m_bMapClear;
	NSafeTArray<SI16, SERVER_EVENT_INSTANCE_MAP>		m_siMapStepCount;
#else
	bool			m_bMapClear[SERVER_EVENT_INSTANCE_MAP];									// �� �δ����� ����.
	SI16			m_siMapStepCount[SERVER_EVENT_INSTANCE_MAP];							// �δ� ����� ���� ����.(�ܰ�)
#endif
	SI64			m_siScore;																// ���� �� ����� ����.(�Ϸ� ���� ������ ����)

	DWORD			m_dwStartTime;															// �δ� ���۽ð�
	SI32			m_siGateID;																// �δ� �κ�� ����Ʈ ID

};

#endif



