#pragma once

#ifdef USE_PROMOTOR_FRONT_SERVER

//////////////////////////////////////////////////////////////////////////
// [����] �߱� ���θ���. 
#include "../Promoter/NHNChinaPromoter.h"

	// �������� ���
	#ifdef _DEBUG	
		#pragma comment(lib, "NHNChinaPromoterDllD.lib") 
	#else
		#pragma comment(lib, "NHNChinaPromoterDll.lib") 
	#endif

//#endif
//////////////////////////////////////////////////////////////////////////

#include "itzbase.h"
#include "ITZSession.h"
#include "ITZSendBuffer.h"
class ITZSession;


#include <process.h>
#include "windows.h"
#include "queue"
#include "TCHAR.h"
using namespace std;

#define PROMOTER_THREAD_NUM	 10		// ���θ��Ϳ��� ����ϴ� �������� ����.


//////////////////////////////////////////////////////////////////////////
//
// clPromoterManager ���� ���Ǵ� Ŭ����.
//
//////////////////////////////////////////////////////////////////////////

class clEventInfo
{
public:
	clEventInfo(void)														{ ZeroMemory(this, sizeof(*this));	}
	~clEventInfo(void)														{									}

	void		SetActive( bool _bActive )									{ m_bActive = _bActive;				}
	bool		GetActive( void )											{ return m_bActive;					}

	void		SetEvent(HANDLE _hEvent )									{ m_hEvent = _hEvent;				}
	HANDLE		GetEvent( void )											{ return m_hEvent;					}

private:
	bool		m_bActive;
	HANDLE		m_hEvent;

};

// ���θ��� ���� ��û ���� ����.
class clPromoterInfo
{
public:
	enum{ GET_PROMOTER_INFO_TOTAL, GET_PROMOTER_INFO, GET_PROMOTER_URL };

public:
	clPromoterInfo( void )													{ ZeroMemory(this, sizeof(*this));						}
	clPromoterInfo( SI32	_siID, SI32	_siOperatorType )					{ m_siID = _siID; m_siOperatorType = _siOperatorType;	}
	~clPromoterInfo( void )													{														}

	void		SetOperatorType( SI32 _siOperatorType )						{ m_siOperatorType = _siOperatorType;					}
	SI32		GetOperatorType( void )										{ return m_siOperatorType;								}

	void		SetID( SI32 _siID )											{ m_siID = _siID;										}
	SI32		GetID( void )												{ return m_siID;										}

	void		SetName( TCHAR* _pName )									{ StringCchCopy( m_szCharName, sizeof(m_szCharName), _pName );	}
	TCHAR*		GetName( void )												{ return m_szCharName;									}

	void		SetSession( ITZSession* _pSession )							{ m_pSession = _pSession;								}
	ITZSession*	GetSession( void )											{ return m_pSession;									}

private:
	SI32		m_siOperatorType;
	SI32		m_siID;

	TCHAR		m_szCharName[20];

	ITZSession* m_pSession;
};

// �����忡�� ���޵Ǵ� ����.
class clThreadInfo
{
public:
	enum{ STATE_EXIT = 0, STATE_RUN };

public:
	clThreadInfo(void)														{ ZeroMemory(this, sizeof(*this));				}			

	~clThreadInfo(void)														{												}

	void				Run( void )											{ m_siState = STATE_RUN;						}
	void 				Exit( void )										{ m_siState = STATE_EXIT;						}

	void				SetState( SI32 _siState )							{ m_siState = _siState;							}
	SI32 				GetState( void )									{ return m_siState;								}

	void				SetThreadIndex( SI32 _siThreadIndex )				{ m_siThreadIndex = _siThreadIndex;				}
	SI32 				GetThreadIndex( void )								{ return m_siThreadIndex;						}

public:
	void				SetID( SI32 _siID )									{ m_clPromoterInfo.SetID( _siID );				}
	SI32				GetID( void )										{ return m_clPromoterInfo.GetID();				}

	void				SetName( TCHAR* _pName )							{ m_clPromoterInfo.SetName( _pName );			}
	TCHAR*				GetName( void )										{ return m_clPromoterInfo.GetName();			}

	void				SetOperatorType( SI32 _siOperatorType )				{ m_clPromoterInfo.SetOperatorType( _siOperatorType );	}
	SI32				GetOperatorType( void )								{ return m_clPromoterInfo.GetOperatorType();	}

	void				SetSession( ITZSession* _pSession )					{ m_clPromoterInfo.SetSession( _pSession );	}
	ITZSession*			GetSession( void )									{ return m_clPromoterInfo.GetSession();	}

public:
	void				SetActive( bool _bActive )							{ m_clEventInfo.SetActive( _bActive );			}
	bool				GetActive( void )									{ return m_clEventInfo.GetActive();				}

	void				SetEvent(HANDLE _hEvent )							{ m_clEventInfo.SetEvent( _hEvent );			}
	HANDLE				GetEvent( void )									{ return m_clEventInfo.GetEvent();				}


private:
	SI32					m_siState;
    SI32					m_siThreadIndex;

	clPromoterInfo			m_clPromoterInfo;
	clEventInfo				m_clEventInfo;
};


class clPromoterManager
{
public:
	clPromoterManager(void);
	~clPromoterManager(void);

public:
	void						Action( void );
	void						Push( clPromoterInfo PromoterInfo );
	bool						Pop( void );

	void						Lock( void );
	void						UnLock( void );

	void						ActionThread( SI32 _siThreadIndex );
	clThreadInfo*				GetCreateThreadInfo( void );
		
private:
	CRITICAL_SECTION			m_CS;
	
	clThreadInfo				m_clThreadInfo[PROMOTER_THREAD_NUM];		// ������� �̺�Ʈ �Ѱ���.
			
	std::queue<clPromoterInfo>	m_clPromoterInfoQueue;						// ���θ��� ���� ó���� ��û�� ����Ʈ.
};

#endif