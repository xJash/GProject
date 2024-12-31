/*
#include "ITZNetLib/itzbase.h"
#include "item/ItemCommon/commonutil.h"
#define MAX_NAME_NUM 21
#define MAX_PASSWORD_NUM 21
#define MAX_SERVER_NAME 20
#define MAX_PERSON_NAME 20
#define MAX_TIME_LENGTH 17
#define MAX_LOGDATA_LENGTH 25
#define MAX_COMMAND_LENGTH 50
#define MAX_LOGTEXT_LENGTH 512

//������ Ŭ���̾�Ʈ���� �޼���
enum UserLogNetworkMsg{
	REQUEST_LOGIN,         //����� ���� ��û
	RESPONSE_LOGIN,        //����� ���� ���� 

	REQUEST_INIT_DATA,     //�ʱ�ȭ ������ ��û
	RESPONSE_INIT_DATA,    //�ʱ�ȭ ������ ����

	REQUEST_LOGDATA,       //�α� ������ ��ȸ ��û
	RESPONSE_LOGDATA,      //�α� ������ ��ȸ ����

	REQUEST_HEARTBEAT,

	REQUEST_LOGOUT,       //�������� ��û
	RESPONSE_LOGOUT,      //�������� ����
};



class cltMsgResponse_Login{
public:
	char szUserID[20+1];
	char szPassword[20+1];

    cltMsgResponse_Login(char* UserID, char* PassWord)
	{
	
		 MStrCpy(szUserID,UserID, MAX_NAME_NUM);
		 MStrCpy(szPassword,PassWord, MAX_PASSWORD_NUM);
			
	}
};

class cltMsgRequest_Login{
public:
	SI32 siResult;

	cltMsgRequest_Login(SI32 Result)
	{
		siResult = Result;
	}
};

class cltMsgRequest_Init_Data{   //�ʱ�ȭ ������ ��û
public:
	cltMsgRequest_Init_Data()
	{
	}
};

class cltMsgResponse_Init_Data{
public:	
	char szServerName[20];

	cltMsgResponse_Init_Data(char* ServerName)
	{
		 MStrCpy(szServerName,ServerName, MAX_SERVER_NAME);
	}
};

class cltMsgRequest_Logdata{
public:
	char szServerName[20];
	char szPersonName[20];
	SI16 siltemUnique;
	SI08 siLogType;
	char szStartTime[17];
	char szEndTime[17];
	cltMsgRequest_Logdata(char* ServerName, char* PersonName, SI16 itemUnique, SI08 LogType,char* StartTime, char* EndTime)
	{
		MStrCpy(szServerName, ServerName, MAX_SERVER_NAME);
		MStrCpy(szPersonName, PersonName, MAX_PERSON_NAME);
		siltemUnique = itemUnique;
		siLogType = LogType;
		MStrCpy(szStartTime, StartTime, MAX_TIME_LENGTH);
		MStrCpy(szEndTime, EndTime,MAX_TIME_LENGTH);

	}

};

class cltMsgResponse_Logdata{
public:
	char szLogData[25];
	char szCommand[50];
	char szPersonName[20];
	char szDstPersonName[20];
	SI16 siItemUnique;
	char szLogText[512];
	cltMsgResponse_Logdata(char* LogData,char* Command, char* PersonName, char* DstPersonName, SI16 ItemUnique, char *LogText )
	{
		MStrCpy(szLogData,LogData,MAX_LOGDATA_LENGTH);
		MStrCpy(szCommand,Command,MAX_COMMAND_LENGTH);
		MStrCpy(szPersonName,PersonName,MAX_PERSON_NAME);
		siItemUnique = ItemUnique;
		MStrCpy(szDstPersonName,DstPersonName,MAX_PERSON_NAME);
		MStrCpy(szLogText,LogText,MAX_LOGTEXT_LENGTH);

	}

};


//-------------------------------------------------------------------
//Ŭ���̾�Ʈ���� ������ ������ �Ϲ����� ���� �޽����� ���� ����. 
//-------------------------------------------------------------------

#define MAX_CLTMSG_DATA_SIZE   10000 //4�� ������� �Ѵ�. 

class cltMsg{
public:
	sPacketHeader clHead;	

	union{
		char    cData[MAX_CLTMSG_DATA_SIZE];				//���� �����Ͱ� ����ִ� ����. 
		SI32	siData32[MAX_CLTMSG_DATA_SIZE/4];
	};


	cltMsg(){};

	cltMsg(UI16 type, SI32 datasize, const char* pdata)
	{
		clHead.usCmd	=	type;

		if(datasize >= MAX_CLTMSG_DATA_SIZE)
		{
			AfxMessageBox("cltMsg1234");
			//MsgBox("cltMsg", "type:%d datasize:%d", type, datasize);
		}
		else
		{
			clHead.usSize	=	sizeof(sPacketHeader) + datasize;

			if(pdata && datasize)
			{
				memcpy(cData, pdata, datasize);
			}
		}
	}

	// 32bit ���� ������ ������. 
	cltMsg(UI16 type, SI32 sidata)
	{
		clHead.usCmd	=	type;
		clHead.usSize	=	sizeof(sPacketHeader) + sizeof(SI32);

		siData32[0] = sidata;
	}

	SI32 GetTotalSize(){return clHead.usSize;}
	SI32 GetDataSize(){return clHead.usSize - sizeof(sPacketHeader);}
};



*/