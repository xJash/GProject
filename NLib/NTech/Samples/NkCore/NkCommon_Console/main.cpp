//-------------------------------------------------------------------------------------------------
// main.cpp
// �������� ���������
// ������
//-------------------------------------------------------------------------------------------------

#include <NkCore.h>

#include <stdio.h>
#include <conio.h>

#include "display_helper.h"

struct SampleFunction
{
	char m_chKey;
	char* m_pcFunctionName;
	void (*pFunc)();
};


//-------------------------------------------------------------------------------------------------
// ���⿡ �Լ� ���� �߰� �� ��ϸ� �ϸ� ��.
//-------------------------------------------------------------------------------------------------

void NkCharsSample();
void NkStringSample();
void NkVectorSample();
void NkListSample();
void NkStackSample();
void NkQueueSample();
void NkDequeSample();
void NkHashMapSample();
void NkMsgQueueSample();
void NkMsgQueueThreadTest();
void NkRbTreeMapSample();

void MemoryLeak();

SampleFunction sample[] =
{
	{ '1', "����(NkVector) ����", NkVectorSample },
	{ '2', "����Ʈ(NkList) ����", NkListSample },
	{ '3', "����(NkStack) ����", NkStackSample },
	{ '4', "ť(NkQueue) ����", NkQueueSample },
	{ '5', "��ũ(NkDeque) ����", NkDequeSample },
	{ '6', "�ؽ���(NkHashMap) ����", NkHashMapSample },
	{ '7', "�޽���ť(NkMsgQueue) ������ ���� ����", NkMsgQueueThreadTest },
	{ '8', "�������� ���� ���ڿ�(NkChars) ����", NkCharsSample },
	{ '9', "�� ���ڿ�(NkStrings) ����", NkStringSample },
	{ 'a', "�����Ʈ��(NkRbTreeMap) ����", NkRbTreeMapSample },
	{ '!', "�޸� �� �߻�", MemoryLeak },

	{ 0, "", 0 }

};

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

void disp_menu()
{
	CDispHelper::Get().Printf("-------------------------------------------------------------------------------\n");
	CDispHelper::Get().Printf("NkCommon Samples\n");
	CDispHelper::Get().Printf("-------------------------------------------------------------------------------\n");

	for( int i = 0; sample[i].m_chKey != 0; ++i )
	{
		if( 'a' <= sample[i].m_chKey && sample[i].m_chKey <= 'z' )
			sample[i].m_chKey -= ('a'-'A');

		CDispHelper::Get().Printf("[%c] %s\n", sample[i].m_chKey, sample[i].m_pcFunctionName);
	}

	CDispHelper::Get().Printf("\n[ESC] Exit\n");
}

void main()
{
	//-------------------------------------------------------------------------
	// NkCore ��ŸƮ
	// NkCommon ���̺귯���� �̿��ϱ� ���ؼ��� 
	// ���ø����̼� ���۽� NkCore::Startup() ���� �ʼ� 
	//-------------------------------------------------------------------------
	NkCore::Startup();

	CDispHelper::Init();

	CDispHelper::Get().CreateConsole("NkCommon ����", 1024);

	//-------------------------------------------------------------------------
	// �޴� ���
	//-------------------------------------------------------------------------
	disp_menu();

	//-------------------------------------------------------------------------
	// �Է� ó��
	//-------------------------------------------------------------------------
	char key;
	while( (key = (char)_getch()) != 27 )
	{
		if( 'a' <= key && key <= 'z' )
			key -= ('a'-'A');

		for( int i = 0; sample[i].m_chKey != 0; ++i )
		{
			if( key == sample[i].m_chKey )
			{
				CDispHelper::Get().Printf("\n\n");
				CDispHelper::Get().Printf("-------------------------------------------------------------------------------\n");
				CDispHelper::Get().Printf("%s\n", sample[i].m_pcFunctionName);
				CDispHelper::Get().Printf("-------------------------------------------------------------------------------\n");

				sample[i].pFunc();
				CDispHelper::Get().Printf("\n\n");
				disp_menu();
			}
		}
	}
	//-------------------------------------------------------------------------

	CDispHelper::Get().CloseConsole();

	CDispHelper::Shutdown();

	//-------------------------------------------------------------------------
	// NkCore ����. ���ø����̼� ����� NkCore::Shutdown()���� �ݵ�� ����
	//-------------------------------------------------------------------------
	NkCore::Shutdown();
}
