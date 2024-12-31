//-------------------------------------------------------------------------------------------------
// NkMsgQueueThreadTest.cpp
// �������� ���������
// ������
//-------------------------------------------------------------------------------------------------

#include <NkMsgQueue.h>
#include <process.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

enum
{
	MSGTYPE_TESTMSG1 = 1,
	MSGTYPE_TESTMSG2
};

class TestMsg1 : public NkMsg
{
public:
	TestMsg1() { m_usMsgType = MSGTYPE_TESTMSG1; }

	int m_iSerial;
	char m_str[ 2048 ];
};

class TestMsg2 : public NkMsg
{
public:
	TestMsg2() { m_usMsgType = MSGTYPE_TESTMSG2; m_usMsgSize = sizeof(TestMsg2); }

	int m_iSerial;
	int m_iLevel;
	int m_iExp;
};

BOOL g_bThreadRun;

unsigned __stdcall NkMsgQueue_Thread(LPVOID param)
{
	NkMsgQueue* pkMsgQueue = (NkMsgQueue*)param;

	int iSerial = 0;

	while( g_bThreadRun )
	{
		// TestMsg1 ������
		{
			TestMsg1 msg;

			// ���� ���� ���� ���ڿ� ���� 
			int len = (rand() % 11) + 5;
			for( int i = 0; i < len; ++i )
			{
				msg.m_str[ i ] = (char)((rand() % 26) + 'a');
			}
			msg.m_str[ len ] = '\0';
			msg.m_iSerial = iSerial;

			msg.m_usMsgSize = (unsigned short)(sizeof(NkMsg) + len + 5);

			// ť�� �޽��� �ֱ�
			if( pkMsgQueue->PushMsg( &msg ) == true )
				iSerial++;
		}

		// TestMsg2 ������
		{
			TestMsg2 msg;

			msg.m_iLevel = rand() % 100;
			msg.m_iExp = rand() % 1000;

			msg.m_iSerial = iSerial;

			// ť�� �޽��� �ֱ�
			if( pkMsgQueue->PushMsg( &msg ) == true )
				iSerial++;
		}
	}

	return 0;
}

void NkMsgQueueThreadTest()
{
	NkMsgQueue kMsgQueue( 64 * 1024 );

	g_bThreadRun = TRUE;

	// �޽��� �Է� ������ ����
	unsigned int uiThreadID;
	HANDLE hThread = (HANDLE) _beginthreadex( NULL, 0, NkMsgQueue_Thread, (LPVOID)&kMsgQueue, 0, &uiThreadID );
	CloseHandle( hThread );	

	// �޽��� ó�� ���� - Ű�� ������ �����Ѵ�
	NkMsg *pkMsg;
	while( !_kbhit() )
	{	
		pkMsg = kMsgQueue.GetFrontMsg();					// �޽��� ������

		if( pkMsg == NULL ) continue;

		switch( pkMsg->GetMsgType() )						// �޽��� Ÿ�Կ� ���� ó��
		{                                                   // (�޽��� Ÿ�� ������ ���� ���� �Լ� ������ ��� ����)
		case MSGTYPE_TESTMSG1:
			{
				TestMsg1 *pkTestMsg1 = (TestMsg1*)pkMsg;

				printf( "Msg size:%3d, type:%3d, serial:%d, str:%s\n", 
					pkTestMsg1->GetMsgSize(),
					pkTestMsg1->GetMsgType(),
					pkTestMsg1->m_iSerial,
					pkTestMsg1->m_str );
			}
			break;
		case MSGTYPE_TESTMSG2:
			{
				TestMsg2 *pkTestMsg2 = (TestMsg2*)pkMsg;

				printf( "Msg size:%3d, type:%3d, serial:%d, level:%d, exp:%d\n",
					pkTestMsg2->GetMsgSize(),
					pkTestMsg2->GetMsgType(),
					pkTestMsg2->m_iSerial,
					pkTestMsg2->m_iLevel,
					pkTestMsg2->m_iExp
					);
			}
			break;
		}

		kMsgQueue.RemoveFrontMsg();							// �޽��� ����
	}

	InterlockedExchange((LPLONG)&g_bThreadRun, FALSE);

	printf("[���� ����]   NkMsgQueue: FreeSize=%d, MsgCount=%d\n", kMsgQueue.GetFreeSize(), kMsgQueue.GetMsgCount());


	// ���� �޽������� ������, 
	// Queue�� ���� ������� �޽��� ������ Ȯ���غ���. (�ʱ�ȭ ������� ������, ���� �޽��� ������ 0�ΰ�)          
	while( (pkMsg = kMsgQueue.GetFrontMsg()) != 0 )
	{
		kMsgQueue.RemoveFrontMsg();
	}

	printf("[������ �Ϸ�] NkMsgQueue: FreeSize=%d, MsgCount=%d\n", kMsgQueue.GetFreeSize(), kMsgQueue.GetMsgCount());
}