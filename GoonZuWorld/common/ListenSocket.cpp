#include <winsock2.h>
#include <stdio.h>
#include "ListenSocket.h"
//-----------------------------------------------------------------------------------------------------------------------
//	Name : CListenSocket()
//	Desc : �������� ����,�ʱ�ȭ�ϰ� ������ Ŭ���̾�Ʈ�� ������ ����ϴ� ���·� ����� 		  
//-----------------------------------------------------------------------------------------------------------------------
CListenSocket::CListenSocket(char *ip, int port)
{			
	m_bShutdown = FALSE;
		
	// 1. ����� �Ϸ� ��Ʈ ���� 
	if( NULL == (m_hCompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0)))
	{
		printf("CreateIoCompletionPort() fail!\n");
	}				   	

	// 2. Ŭ���̾�Ʈ ���� ��� 
	if(INVALID_SOCKET == (m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)))
	{
		printf("socket() fail!\n");
	}	
	SOCKADDR_IN sockAddr = getSockAddrIn(ip, port);
	if(SOCKET_ERROR   == bind(m_socket, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR_IN)))
	{
		printf("bind() fail!\n");
	}	
	if(SOCKET_ERROR   == listen(m_socket, 50))
	{
		printf("listen() fail!\n");
	}

	// 3. Ŭ���̾�Ʈ ���ӽ� �߻��ϴ� �̺�Ʈ ���� 
	m_wsaEvent[0]	  = WSACreateEvent(); 
	WSAEventSelect(m_socket, m_wsaEvent[0], FD_ACCEPT);			

	// 4. ���� ������ �����ϴ� �̺�Ʈ ���� 
	m_wsaEvent[1]	  = WSACreateEvent(); 

	/*
	linger data;
	data.l_linger = 1000;
	data.l_onoff  = 1;
	
	setsockopt( m_socket, SOL_SOCKET , SO_LINGER, (char*)&data, sizeof(data) );
	*/
}




//-----------------------------------------------------------------------------------------------------------------------
//	Name : ~CAcceptSocket()
//	Desc : 
//-----------------------------------------------------------------------------------------------------------------------
CListenSocket::~CListenSocket()
{
	Shutdown();
		
	// �̺�Ʈ ���� 
	WSACloseEvent(m_wsaEvent[0]);
	WSACloseEvent(m_wsaEvent[1]);	

}




//-----------------------------------------------------------------------------------------------------------------------
//	Name : getSockAddrIn()
//	Desc : ���� IP�� ��Ʈ�� ���� SOCKADDR_IN ����ü ������ ���´� 
//-----------------------------------------------------------------------------------------------------------------------
SOCKADDR_IN CListenSocket::getSockAddrIn(char* ip, int port)
{
	SOCKADDR_IN sockAddrIn;
	memset(&sockAddrIn, 0, sizeof(sockAddrIn));	
	sockAddrIn.sin_family		= AF_INET;
	sockAddrIn.sin_addr.s_addr  = inet_addr(ip);
	sockAddrIn.sin_port			= htons(port);	

	return sockAddrIn;
}




//-----------------------------------------------------------------------------------------------------------------------
//	Name : associateHandleToIOCompetionPort()
//	Desc : ������ ���ο� �ڵ��� IOCP�� ������Ų��
//-----------------------------------------------------------------------------------------------------------------------
bool CListenSocket::associateHandleToIOCompetionPort(HANDLE handle, DWORD key)
{		
	HANDLE completionPort = CreateIoCompletionPort(handle, m_hCompletionPort, key, 0);

	if( completionPort != NULL )	
	{ 	
		m_hCompletionPort = completionPort;
		return TRUE;
	}
	else
	{
		OutputDebugString("CreateIoCompletionPort() fail!\n");							
	}

	return FALSE;
}




//-----------------------------------------------------------------------------------------------------------------------
//	Name : Shutdown()
//	Desc : ������ ó���ϴ� ����, ������� ó���ϴ� ����, ����ó�������� ���� ��Ų�� 
//-----------------------------------------------------------------------------------------------------------------------
void CListenSocket::Shutdown()
{
	if(!m_bShutdown)
	{		
		m_bShutdown = TRUE;
						
		// ���� ���� ���� 		
		SetEvent(m_wsaEvent[1]); 
		
		// ����� �Ϸ� ���� ����
		PostQueuedCompletionStatus(m_hCompletionPort, 0, -1, NULL); 
		
		// ���� �ݱ� 
		closesocket(m_socket);
	}
}




//-----------------------------------------------------------------------------------------------------------------------
//	Name : connectPoll()
//	Desc : Ŭ���̾�Ʈ�κ����� ���� ��û�� ó���Ѵ� 
//-----------------------------------------------------------------------------------------------------------------------
void CListenSocket::connectPoll()
{
	SOCKET		 socket;			
	SOCKADDR_IN  sockAddrIn;		

	int	sockAddrSize = sizeof(sockAddrIn);	
	
	WSANETWORKEVENTS event;				
	while(!m_bShutdown)
	{					
		// �̺�Ʈ ��� 
		DWORD ret = WSAWaitForMultipleEvents(2, m_wsaEvent, FALSE, WSA_INFINITE, FALSE);						
		if(ret == WSA_WAIT_FAILED)
		{ 
			printf("WSAWaitForMultipleEvents() fail!\n");			
			break;
		}			
				
		// ���� �̺�Ʈ �߻� 
		else if(ret == WSA_WAIT_EVENT_0) 
		{
			WSAResetEvent(m_wsaEvent[0]);
			
			WSAEnumNetworkEvents(m_socket, m_wsaEvent[0], &event);
			if ((event.lNetworkEvents & FD_ACCEPT) == FD_ACCEPT)
			{ 								
				if( INVALID_SOCKET == (socket = accept(m_socket, (SOCKADDR*)&sockAddrIn, &sockAddrSize)) )
				{ 			
					if(WSAGetLastError() != WSAEWOULDBLOCK)											 	
					{ 
						printf("accept() fail!\n");
						break;
					}								
				}
				else
				{					
					// ����ó�� 					
					occurConnect(socket, &sockAddrIn);
				}
			}
		}

		// ���� �̺�Ʈ �߻� 
		else
		{
			// ���� ���� 
			WSAResetEvent(m_wsaEvent[1]);			
			break;
		}
	}
}




//-----------------------------------------------------------------------------------------------------------------------
//	Name : IOCompletionPoll()
//	Desc : Ŭ���̾�Ʈ�κ����� ����¿Ϸ� ��û�� ó���Ѵ�   
//-----------------------------------------------------------------------------------------------------------------------
void CListenSocket::IOCompletionPoll()
{
	
	DWORD		  completionKey			   = 0;	
	DWORD		  numberOfBytesTransferred = 0;
	LPOVERLAPPED  lpOverlapped  = NULL;					

	while(!m_bShutdown)
	{				
		if(FALSE == GetQueuedCompletionStatus(m_hCompletionPort, &numberOfBytesTransferred, &completionKey,
											 (LPOVERLAPPED*)&lpOverlapped, INFINITE))
		{ 
			if(lpOverlapped == NULL)
			{
				if(GetLastError()!=ERROR_IO_PENDING)
				{			
					printf("GetQueuedCompletionStatus() fail!\n");
					return; 
				}
			}
		}
		
		// ���� ���� 
		if( completionKey == -1 ) break;

		// ����� �Ϸ� ó��		
		occurIOCompletion(completionKey	, numberOfBytesTransferred, lpOverlapped);
	}	
}




//-----------------------------------------------------------------------------------------------------------------------
//	Name : processPoll()
//	Desc : �� �����ӿ� �ѹ��� ����Ǵ� ����ó�� ���� 
//-----------------------------------------------------------------------------------------------------------------------
void CListenSocket::processPoll()
{
	//while(!m_bShutdown)
	{
		occurProcess();
	}
}




