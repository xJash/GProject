#ifndef _MASTERPROCESS_H
#define _MASTERPROCESS_H

#include "stdafx.h"

#include "GoonZuMC.h"

#include "ITZSessionFactory.h"
#include "ITZSessionManager.h"
#include "ITZNetOverlapped.h"
#include "ITZPerson.h"

class cMaster;

class MasterProcess
{
public:
	MasterProcess();
	~MasterProcess();

public:
	void				Init( char *szIP, UI16 usPort );
	
	void				SetIP( char *szIP );

	void				SetIDPW( char *szID, char *szPW );

	void				SetConnect( BOOL b );

	ITZSession*			GetSession() { return m_pMasterSession; };
	cMaster*			GetMaster() { return (cMaster *)m_pMasterSession->GetPerson(); };
	
	void				Run();

	void				lock() { EnterCriticalSection( &m_cs ); };
	void				unlock() { LeaveCriticalSection( &m_cs ); };


public:
	ITZSessionFactory< cMaster >	m_sf;
	ITZSessionManager				m_sm;
	ITZNetOverlapped				m_overlapped;
	
	ITZSession*						m_pMasterSession;

	char							m_szIP[ 16 ];
	UI16							m_usPort;

	CRITICAL_SECTION				m_cs;

	char							m_szID[ 20 ];
	char							m_szPW[ 20 ];

	BOOL							m_bConnecting;			// ���� �õ����ΰ� 
	
	BOOL							m_bSendLogin;			// �α��� ��û�� ���³�
	BOOL							m_bLoginOK;				// �α��ο� �����Ͽ���
	BOOL							m_bLoginFailed;			// �α��� ���� 

	BOOL							m_bSendReqInit;			// �ʱ�ȭ ���� ��û�� ���³�
	BOOL							m_bInitOK;				// �ʱ�ȭ�� �Ϸ�Ǿ���

};


class cMaster : public ITZPerson
{
public:
	cMaster() {};
	~cMaster() {};

	virtual void Init() { printf( "Client NewConnect\n" );

						  MasterProcess *pMasterProcess = ((CGoonZuMCApp *)AfxGetApp())->m_pMasterProcess;		

						  pMasterProcess->lock();

						  pMasterProcess->m_bConnecting = FALSE;
						  
						  pMasterProcess->m_bSendLogin = FALSE;
						  pMasterProcess->m_bLoginOK = FALSE;
						  
						  pMasterProcess->m_bSendReqInit = FALSE;
						  pMasterProcess->m_bInitOK = FALSE;

						  pMasterProcess->unlock();

	};


	virtual void Close() { printf( "Client Disconnected\n" ); 

						  MasterProcess *pMasterProcess = ((CGoonZuMCApp *)AfxGetApp())->m_pMasterProcess;		

						  pMasterProcess->lock();	

//						  if( m_bLoginOK == TRUE )
//							  SendMessage( AfxGetMainWnd()->m_hWnd, WM_USER + 101, 0, 0 );
	
						  pMasterProcess->m_bConnecting = FALSE;
						  
						  pMasterProcess->m_bSendLogin = FALSE;
						  pMasterProcess->m_bLoginOK = FALSE;
						  
						  pMasterProcess->m_bSendReqInit = FALSE;
						  pMasterProcess->m_bInitOK = FALSE;

						  pMasterProcess->unlock();

	};

};

#endif
