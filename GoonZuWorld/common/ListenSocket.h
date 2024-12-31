#ifndef __CLISTENSOCKET__
#define __CLISTENSOCKET__

// Ŭ���̾�Ʈ���� ���ӹ� ����� �ϷḦ ó���ϴ� ���� Ŭ���� 
class CListenSocket
{	
protected:
	HANDLE				m_hCompletionPort;					

private:
	SOCKET				m_socket;						
	WSAEVENT			m_wsaEvent[2];				// ���� ó�� �̺�Ʈ	
	bool				m_bShutdown;				// ���� ���� ���� 				

public:	
	CListenSocket(char *ip, int port);
	virtual	~CListenSocket();

public: 	
	void				Shutdown();						

	bool				associateHandleToIOCompetionPort(HANDLE handle, DWORD key);

	void				connectPoll();
	void				IOCompletionPoll();
	void				processPoll();

protected:	
	//---------------------------------------------------------------------------
	virtual void		occurConnect(SOCKET socket, SOCKADDR_IN *sockAddrIn) = 0;	
	virtual void		occurIOCompletion(DWORD		   completionKey, 
										  DWORD		   numberOfBytesTransferred, 
										  LPOVERLAPPED lpOverlapped) = 0;	
	virtual void		occurProcess()	= 0;

private:
	SOCKADDR_IN			getSockAddrIn(char* ip, int port);
};

#endif