//////////////////////////////////////////////////////////////////////////
//
// �̸� : ���� ���ϱ� �̺�Ʈ 
// ������ : �ռ���
// ���� : ������� �̺�Ʈ�� ������ �Ŵ���
//		 ���� ����Ʈ�� ���� �����ϰ�, �ɸ��͵��� ���� ��Ű�µ��� ���� �Ѵ�
//	//Switch_10MonthEvent_RacoonDodge
//	
//
//////////////////////////////////////////////////////////////////////////
#ifndef _RACOONDODGEEVENT_H_
#define _RACOONDODGEEVENT_H_

#include "../common/CommonHeader.h"
#include "../NLib/NUpdateTimer.h"	//5�� ���������� ���

#define MAX_RESERVER_NUM				40			// �ִ� ���డ�� �� ����
#define EVENT_START_NUM					5			// �̺�Ʈ���� ���� ���� 
#define MAX_RESERVER_SHOW_NUM			20			// �ִ� ������ ������ ����
#define MAX_EVENTPLACE					2			// �ִ� �̺�Ʈ ����
#define MAX_EVENT_MONSTER_CREATE_ROC	10			// �ִ� �̺�Ʈ ���� ���� ��ǥ 
#define MAX_MONSTER_ROC					20			// ������ ���� ��ǥ �Ѱ���
#define	MAX_STAGE_NUM					2			// �ִ� �ʰ���
#define	MAX_MONSTER_NUM					10			// �ִ� ��ϰ����� ����	10����
#define	ROUND_TIME_LMIT					30000		// �Ѷ��� �ð� 30��
#define	MAKEMOSTER_TERM					3000		// �Ѷ��� �ð� 3��

#define MAX_AGGRESSIVE					7
#define MAX_MOVESPEED					20

#define  MAX_PLAY_LEVEL					10			// �÷��� �ϴ� �� ����

#define MAKE_MONSTER_NUM_1	1
#define MAKE_MONSTER_NUM_10	10

#define PLAY_MAP_INDEX					97
#define PLAY_MAP_INDEX_INDODEVENT		97

#define MAX_MAKE_MONSTER_NUM			600		// �ִ� ������ ���� �Ѽ�
#define REWARDPOINT						20		// ���� ���� ���� ���� �� 20��
#define MAX_ROOF_NUM					100		// ���� ����� ������ �Ѱ�ġ

#define CAN_PLAY_RACOONDODGEEVENT_LMIT	5	// ���� �̺�Ʈ �ּ� ���� �ο�
#define CAN_PLAY_RACOONDODGEEVENT_2STAGE	10	// ���� �̺�Ʈ 2 �������� ���� �ο�

// ���� ���������ʵ�
enum
{
	RACOONDODGEEVENT_STAGE_FIELD_1ST = 0 ,	// ù��° ��������
	RACOONDODGEEVENT_STAGE_FILED_2ND,	
};

enum // �̺�Ʈ �ܰ�
{
	EVENTSTEP_WAIT = 0 ,				// �̺�Ʈ ��� �ð�.
	EVENTSTEP_MAKE_PLAYUSERLIST ,		// ��û�ڵ��߿� �̺�Ʈ�� ������ ����� ����Ʈ�� �����
	EVENTSTEP_REQUEST_PLAY_EVENT_NOW ,	// ������ ��û�ڵ鿡�� ���� ���θ� ���´�
	EVENTSTEP_WAIT_ANSWER ,				// ������ ����� ��ٸ��� �����ϴ� �ð� 10�ʰ��� ��� �ð�.
	EVENTSTEP_GAMESTART ,				// ������ ���� �Ѵ�.
	EVENTSTEP_PLAY,						// �̺�Ʈ�� ���� �÷��� ���� ���� �̴�. ���ο��� ������ ���� �ϸ鼭 ������ ���� �ǰ� �ִ�.
	EVENTSTEP_WAITTIME,					// �̺�Ʈ�� ���� �÷��� ���� ���� �̴�. ���ο��� ������ ���� �ϸ鼭 ������ ���� �ǰ� �ִ�.
	EVENTSTEP_GAMEEND ,					// ������ �ð��� ������ �����ؼ� ���� �Ǵ���, ������ ������ ���� ��Ų��.
};

enum // �̺�Ʈ ���� 
{
	EVENTLEVEL_WAIT = 0 ,
	EVENTLEVEL_LV1,
	EVENTLEVEL_LV2,
	EVENTLEVEL_LV3,
	EVENTLEVEL_LV4,
	EVENTLEVEL_LV5,
	EVENTLEVEL_LV6,
	EVENTLEVEL_LV7,
	EVENTLEVEL_LV8,
	EVENTLEVEL_LV9,
	EVENTLEVEL_LV10,
	EVENTLEVEL_CLEAR
};

enum
{
	RACOONDODGEEVENT_STAGE_NONE	=	0,	// ���������� ������ ���� �ο� ����  
	RACOONDODGEEVENT_STAGE_ONE,			// 1���� ������ 
	RACOONDODGEEVENT_STAGE_TWO,			// 2���� ������ 

};

// ���иż��� value
enum
{
	EVENT_RESERVATION_FALE_NOT_EMPTY	=	0,	// ���ڸ��� ����.
};

class ReserveData
{
public:
	ReserveData()							;
	~ReserveData()							;
	void init()								;

	SI32 GetCharPersonID( )					;
	TCHAR* GetCharName( )					;

	void SetCharPersonID(SI32 siPersonID )	;
	void SetCharName(TCHAR *charname )		;

	void SetChar(SI32 siPersonID,TCHAR *charname )
	{
		SetCharPersonID(siPersonID)	;
		SetCharName(charname )		;
	};
private:
	SI32	PersonID	;
	TCHAR	m_szCharName[MAX_PLAYER_NAME] ;	// �ڽ� �̸�
};


class cltRocData	// ��ǥ�� ����ϰ� ���� Ŭ����
{
public:
	cltRocData(){		ZeroMemory(this,sizeof(cltRocData))	;	};
	~cltRocData(){};
	SI32 GetRocX(){		return X	;	}	;
	SI32 GetRocY(){		return Y	;	}	;
	SI32 GetRocStage(){	return Stage;	}	;

	void SetRocX( SI32 siX ){	X	=	siX;	}	;
	void SetRocY( SI32 siY ){	Y	=	siY;	}	;
	void SetRocStage( SI32 siStage ){	Stage	=	siStage;	}	;
	void SetRoc( SI32 siX , SI32 siY,SI32 siStage )
	{	
		X = siX ; 
		Y = siY; 
		Stage = siStage;
	};
private:
	SI32 Stage	;
	SI32 X	;
	SI32 Y	;
};

class cltRocDataArray
{
public:
	cltRocDataArray()
	{
		ZeroMemory(this, sizeof(cltRocDataArray));
	};
	~cltRocDataArray(){};
	void SetRoc( SI32 siStageIndex, SI32 siX , SI32 siY)
	{
		for ( SI32 i = 0; i < MAX_MONSTER_ROC; i++) 
		{
			if (pclRocData!=NULL &&  0 == pclRocData[i].GetRocStage() )
			{

				pclRocData[i].SetRoc( siX, siY,siStageIndex)	;
				break;
			}
		}
	};
	//void SetRocX( SI32 siIndex, SI32 siX)
	//{
	//	if(siIndex < MAX_MONSTER_ROC)
	//	{
	//		pclRocData[siIndex].SetRocX( siX)	;
	//	}
	//};
	//void SetRocY( SI32 siIndex, SI32 siY)
	//{
	//	if(siIndex < MAX_MONSTER_ROC)
	//	{
	//		pclRocData[siIndex].SetRocY(siY)	;
	//	}
	//};
	//void SetStage( SI32 siIndex, SI32 siStage)
	//{
	//	if(siIndex < MAX_MONSTER_ROC)
	//	{
	//		pclRocData[siIndex].SetRocStage(siStage)	;
	//	}
	//};
	SI32 GetRocX( SI32 siIndex)
	{
		if(siIndex >= MAX_MONSTER_ROC)	return -1	;
		return pclRocData[siIndex].GetRocX()	;

	};
	SI32 GetRocY( SI32 siIndex)
	{
		if(siIndex >= MAX_MONSTER_ROC)	return -1	;
		return pclRocData[siIndex].GetRocY()	;
	};
	SI32 GetStage( SI32 siIndex)
	{
		if(siIndex >= MAX_MONSTER_ROC)	return -1	;
		return pclRocData[siIndex].GetRocStage()	;
	};
	
private:
	cltRocData	pclRocData[MAX_MONSTER_ROC]	;

};
class cltMonsterSetData
{
public:
	cltMonsterSetData(){		ZeroMemory(this,sizeof(cltMonsterSetData))	;	};
	~cltMonsterSetData(){};

	void SetData(SI32 EventLevel, SI32 AGV_Value, SI32 AGV_AddValue, SI32 MoveSpeed_Value, SI32 MoveSpeed_AddValue )
	{
		siEventLevel	=	EventLevel ;			// �̺�Ʈ ����
		siAGV_Value		=	AGV_Value ;				// ���� ��׷��ú� min, Max ����
		siAGV_AddValue	=	AGV_AddValue ;			// ���� ��׷��ú� �߰� ������		
		siMoveSpeed_Value		=	MoveSpeed_Value ;		// ���� ��׷��ú� min, Max ����
		siMoveSpeed_AddValue	=	MoveSpeed_AddValue ;	// ���� ��׷��ú� �߰� ������

	};
	SI32 GetAGV_Value(){return  siAGV_Value;}	;
	SI32 GetAGV_AddValue(){return  siAGV_AddValue;}	;
	SI32 GetMoveSpeed_Value(){return  siMoveSpeed_Value;}	;
	SI32 GetMoveSpeed_AddValue(){return  siMoveSpeed_AddValue;}	;
	SI32 GetSiGameLevel(){return  siEventLevel;}	;
private:
	SI32 siEventLevel	;	// �̺�Ʈ ����

	SI32 siAGV_Value	;	// ���� ��׷��ú� min, Max ����
	SI32 siAGV_AddValue	;	// ���� ��׷��ú� �߰� ������

	SI32 siMoveSpeed_Value	;	// ���� ��׷��ú� min, Max ����
	SI32 siMoveSpeed_AddValue	;	// ���� ��׷��ú� �߰� ������
};
class CRacoonDodgeEventMgr
{
public:
	CRacoonDodgeEventMgr()	;	// ������
	~CRacoonDodgeEventMgr() ;	// �Ҹ���

	void init(void)		;									// ���� �ʱ�ȭ
	void Action(void)	;									// ���� ������ �׼� �Լ�
	void MakeSelectPersonList(void)	;						// ������ ������� �̾Ƴ��� ����Ʈ�� ����� �� ����Ʈ�� ���ฮ��Ʈ�ʹ� �ٸ���.
	bool AddReserveList(SI32 siPersonID )	;				// ����Ʈ�� �߰� �Ѵ�.
	void SendMessage_Request_PlayEvent(void)	;			// ������� ���� ����Ʈ���� �� ���� �Ұų��� �޼����� ������.
	
	SI32 FindEmptyPosiotion(void)	;						// ����Ʈ�� �󽽷��� ã�´�.
	void Select_Participated_PersonID( SI32 siPersonID);	// ������ ����� ���� ó��.
	SI32 FindPersonID_InList( SI32 siInputPersonID) ;		// ����Ʈ���� �ش� ����� ã�Ƽ� �ε����� ���� �Ѵ�.
	bool SetEventChar( SI32 siPersonID)	;					// �̺�Ʈ�ɸ��Ͷ�� ���� �Ѵ�.	
	void WarpGameSpace(SI32 siPersonID )	;					// �ش� �ɸ��͸� ���� �Ѵ�
	void SendReserveList(SI32 siPersonID )	;					// ���������� Ŭ���̾�Ʈ�� �����ش�

	SI32 GetStep(  void )	;									// �Ŵ����� ���� ������ ������ �´�
	SI32 GetLevel(  void )	;									// ����ǰ� �ִ� ������ ���� ������������ �´�
	void ChangeStep( SI32 siStep )	;							// �Ŵ����� ���� ������ ���� �Ѵ�.
	void ChangeLevel( SI32 siLevel )	;						// ����ǰ� �ִ� ������ ������ ���� �Ѵ�.

	void SetMonster( SI32 siMake_Monster_Num, SI32 siStageindex)	;	// ���͸� �ش� ������ ��ŭ �ѷ��ش�
	SI32 CheckPlayStageNum()	;										// 2���� �ʵ忡�� ��� ������ �������� �ƴ��� Ȯ���Ѵ� .

	bool CanReserveList(SI32 siPersonID)	;							// �����Ҽ� �ִ��� Ȯ��
	void SetAggressiveNMoveSpeed( SI32 siCharID )	;					// ���� ���Ǿ��� ���꽺�ǵ�� ��׷��ú� ���� 
	
	void Count5Second(void)	;								// 5�� ī��Ʈ �ϵ��� �޼����� ������ ������ �̺�Ʈ�� ���۾�����
	void Count30Second(void)	;							// �̺�Ʈ ���� �ϸ鼭 30�� ī��Ʈ �ϵ��� �޼����� ������
	void RoundSet(void)	;									//  ����ǥ�� �Ѵ�.

	bool CanPlayEvent(void)	;								// �̺�Ʈ�� ���� �ɼ� �ִ��� Ȯ�� �Ѵ� .
	void KillEventMonster(void)	;							// �̺�Ʈ ���͸� �� ���δ�.
	//void RememberEventMonster(SI32 siID)	;				// ���� �̺�Ʈ ���� ���̵� ����Ѵ� 200�� ���� 
	void RewardMoney(void)	;								// ���� 10 �޼� ���� �ش� 

	void SetRoundTime(SI32 siSecond)	;					// ���� �ð� ���� �ʴ����� �Է¹޴´�.

	void ClearData()	;									// ���尡 ������ �Ŵ��� ���¸� �ʱ�ȭ�Ѵ�. �׷��� ���ฮ��Ʈ�� �������. 
	SI32 CountReservePersonNum();

	//---------------------------------------------------------------------------------------------------------------------------
	// ���ҽ� �ε� �ϴ� �͵�
	//---------------------------------------------------------------------------------------------------------------------------
	void LoadRocFile();				// ��ǥ�� ������������ �о� ���δ�.
	void LoadMonsterKindFile();		// ���� ī�ε带 ������������ �о� ���δ�.
	void LoadMonsterInfoSetFile();	// ������ ������ ���� ���� ��׷��ú� ���� ���꽺�ǵ带������ �´�.

	//---------------------------------------------------------------------------------------------------------------------------


private:
	SI32 siGameStep			;		// ���� ���� ����
	SI32 siGameLevel		;		// ���� ���� ���� 

	SI32 siInEventGroundNum	;		// �̺�Ʈ �׶��忡 �ִ� ��� 5�� �Ѿ�� 2�� �׶���� ������.
	bool bLeadData			;

	SI32 siCheckFieldNum	;
	SI32 siMonsterKindNum	;
	bool bCheck_1stMakeMonster	;	// ó�� 10���� ���͸� ���������


	DWORD dwCount_3Second	;		// �� �ܰ躰�� 10�ʴ� �ѹ� ���͸� ��� ���� ���� �ð� ����
	DWORD dwCount_30Second	;		// ���� �ܰ�� �Ѿ� ���� ���� 30�� �ð� ����
	DWORD dwRoundTime		;		// �Ѷ��� �ð� 
	DWORD siWaitTime5Second	;

	SI32 siMakeMonster_Num	;		// ���� ���� ����
	
#ifdef _SAFE_MEMORY
	NSafeTArray<ReserveData, MAX_RESERVER_NUM> pclReserveList;						// ���ฮ��Ʈ
	NSafeTArray<ReserveData, EVENT_START_NUM*MAX_EVENTPLACE> pclSelectPersonList;	// ���� ����Ʈ
	NSafeTArray<cltRocDataArray, MAX_STAGE_NUM > pclRocList;						// ����ǥ ����Ʈ �� 1���� �׾ȿ��� 2���� ���������� �ִ�	
	NSafeTArray<cltMonsterSetData, MAX_PLAY_LEVEL > pclMonsterInfo_Level;			// �� ���� ������ ��Ʈ ��׷��ú� ���꽺�ǵ� �� 

	NSafeTArray<SI32, MAX_MONSTER_NUM > pclMonsterUnique;							// ����ϴ� ���� ����ũ ����
	NSafeTArray<SI32, MAX_MAKE_MONSTER_NUM > MakeMonsterArray;						// ���߿� ���͸� ���� �ϱ� ���� ���� id�������صд� �ִ� 200�� ���� �����Ѵ�.
	
#else
	ReserveData			pclReserveList[MAX_RESERVER_NUM]	;				// ���ฮ��Ʈ
	ReserveData			pclSelectPersonList[EVENT_START_NUM*2]	;			// ���õ� ���ฮ��Ʈ
	cltRocDataArray		pclRocList[MAX_STAGE_NUM]	;						// ���ฮ��Ʈ	
	cltMonsterSetData	pclMonsterInfo_Level[MAX_PLAY_LEVEL]	;			// ���� ������ ���� ���� ������ aggressive , movespeed
	
	SI32				pclMonsterUnique[MAX_MONSTER_NUM]	;				// ����ϴ� ���� ����ũ ���� 
	SI32				MakeMonsterArray[MAX_MAKE_MONSTER_NUM]	;			// ���߿� ���͸� ���� �ϱ� ���� ���� id�������صд� �ִ� 200�� ���� �����Ѵ�.
#endif

};
#endif
