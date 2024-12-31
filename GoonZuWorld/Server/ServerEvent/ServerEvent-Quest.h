/*

*/
#pragma once

#include "Directives.h"
#include "CommonLogic.h"


// �� ���� ����Ʈ�� ���� ���� �� �ִ� ���ڼ�
const SI32 Const_ServerEvent_Max_QuestCharacter		= 15;
const SI32 Const_ServerEvent_MulNum					= 2;
// �� ����Ʈ ������ ��
const SI32 Const_ServerEvent_Max_QuestData			= 50;

const SI32 Const_ServerEvent_RewardItemGetMinLevel	= 20;

enum SERVEREVENT_MESSAGETYPE
{
	SERVEREVENT_MESSAGETYPE_NONE	= 0,	// �̷�Ÿ���� ����,

	SERVEREVENT_MESSAGETYPE_QUEST_FAIL,		// �ð��� �ٵǾ��µ��� ����Ʈ�� �������� ���� �����ߴ�
	SERVEREVENT_MESSAGETYPE_GETCHAR,		// ���ڸ� �޴´�(����Ʈ ������ ����)
	SERVEREVENT_MESSAGETYPE_CHAR_FAIL,		// ���� �ޱ⸦ �����ߴ�.(����Ʈ�� ���������� ���ڸ� ���� ����)
	SERVEREVENT_MESSAGETYPE_QUEST_ALLCLEAR,	// ��� ����Ʈ�� Ŭ���� �ߴ�.
	
	/*------------------------------------------------------------------------------
	//
	//	���ο� �޽��� Ÿ���� �� ���� �߰��� �ּ���
	//
	------------------------------------------------------------------------------*/
	SERVEREVENT_MESSAGETYPE_END
};

enum SERVEREVENT_TYPE
{
	SERVEREVENT_TYPE_NONE = 0,			// �̷�Ÿ���� ����

	SERVEREVENT_TYPE_HUNTLEVEL,			// 01 Ư�� ������ ���� ���(Condition1=�� ��������, Condition2=�� ��������)
	SERVEREVENT_TYPE_HUNTKIND,			// 02 Ư�� KIND ���� ���(Condition1=ATB, Condition2=Kind)
	SERVEREVENT_TYPE_HUNTBOSS,			// 03 Ư�� ���� KIND ���� ���(Condition1=Kind)
	
	SERVEREVENT_TYPE_QUESTCLEAR,		// 04 ����Ʈ Ŭ����(Condition1=Quest Type)
	
	SERVEREVENT_TYPE_USEITEM,			// 05 ������ ����ϱ�(Condition1=Item Type, Condition2=Item Unique)
	
	SERVEREVENT_TYPE_MAKELEVELITEM,		// 06 Ư�� ������ ������ ����(Condition1=�� ��������, Condition2=�� ��������)
	SERVEREVENT_TYPE_MAKERAREITEM,		// 07 �ű� ������ �̻� �����ϱ�
	
	SERVEREVENT_TYPE_INSTANCEMAPCLEAR,	// 08 �δ� Ŭ����(Condition1=�ν��Ͻ� �� Ÿ��)
	
	SERVEREVENT_TYPE_FISH,				// 09 �����ؼ� ������ ���
	SERVEREVENT_TYPE_FARM,				// 10 ����ؼ�	������ ���
	SERVEREVENT_TYPE_MINE,				// 11 ä���ؼ� ������ ���
	
	SERVEREVENT_TYPE_SKILLUP,			// 12 �ƹ� ��ų����Ʈ �ø���

	SERVEREVENT_TYPE_BLACKWARCLEAR,		// 13 ���Ǳ��� �¸��ϱ�

	SERVEREVENT_TYPE_RESIDENTVILLAGE,	// 14 ���� �ֹ����� �����ϱ�(Condition1=���� �ε���)
	
	SERVEREVENT_TYPE_OPEN_GVG,			// 15 ������� �����ؾ� �Ѵ�
	
	SERVEREVENT_TYPE_COUNTUSER_INMAP,	// 16 Ư�� �� �ε����� ������ ����̻� �־���Ѵ�

	SERVEREVENT_TYPE_LEVELUP,			// 17 �������ϱ�(Condition1=�� �����̻� �÷����Ѵ�)


	/*------------------------------------------------------------------------------
	//
	//	���ο� ���� �̺�Ʈ Ÿ���� �� ���� �߰��� �ּ���
	//
	------------------------------------------------------------------------------*/
	SERVEREVENT_TYPE_END
};

class CNServerEvent_QuestData
{
protected:
	SI32	m_siEventType;			// ���� �̺�Ʈ Ÿ��

	SI32	m_siCondition1;			// Ŭ���� �ϱ� ���� �ʿ��� ���� 1
	SI32	m_siCondition2;			// Ŭ���� �ϱ� ���� �ʿ��� ���� 2
	
	SI32	m_siNeedClearAmount;	// Ŭ���� �ϱ� ���� �ʿ��� ����
	
	SI32	m_siRewardItemUnique;	// Ŭ����� ����Ǵ� ������(����ũ)
	SI32	m_siRewardItemAmount;	// ����Ǵ� ������ ����

	SI32	m_siLimitMinute;		// ���ѽð�

public:
	CNServerEvent_QuestData( void );
	CNServerEvent_QuestData( CNServerEvent_QuestData* pclSEQuestData );

	~CNServerEvent_QuestData();

public:
	void	Init( void );
	// �������̽� �Լ�
public:
	bool	SetServerEvent_QuestData( 
		SI32	siEventType,		// ���� �̺�Ʈ ����Ʈ Ÿ��
		
		SI32	siCondition1,		// ����1(����Ʈ�� ����(�ο�)�ϱ� ���� ����)
		SI32	siCondition2,		// ����2(���������� �˻� ������ �ȴ�)

		SI32	siNeedClearAmount,	// ����Ʈ�� Ŭ���� �ϱ� ���� �ʿ��� Ƚ��

		SI32	siRewardItemUnique,	// ���� ������
		SI32	siRewardItemAmount,	// ���� ������ ����
	
		SI32	siLimitMinute		// ���� �ð�(��)
	);

	bool	SetServerEvent_QuestData( CNServerEvent_QuestData* pclSEQuestData );


	SI32	GetEventType( void ) const						{ return m_siEventType; } 
	void	SetEventType( SI32 siEventType );

	SI32	GetCondition1( void ) const						{ return m_siCondition1; }
	void	SetCondition1( SI32 siCondition1 )				{ m_siCondition1 = siCondition1; }

	SI32	GetCondition2( void ) const						{ return m_siCondition2; }
	void	SetCondition2( SI32 siCondition2 )				{ m_siCondition2 = siCondition2; }

	SI32	GetNeedClearAmount( void )	const				{ return m_siNeedClearAmount; }
	void	SetNeedClearAmount( SI32 siNeedClearAmount )	{ m_siNeedClearAmount = siNeedClearAmount; }

	SI32	GetRewardItemUnique( void )	const				{ return m_siRewardItemUnique; }
	void	SetRewardItemUnique( SI32 siRewardItemUnique )	{ m_siRewardItemUnique = siRewardItemUnique; }

	SI32	GetRewardItemAmount( void )	const				{ return m_siRewardItemAmount; }
	void	SetRewardItemAmount( SI32 siRewardItemAmount )	{ m_siRewardItemAmount = siRewardItemAmount; }

	SI32	GetLimitMinute( void ) const					{ return m_siLimitMinute; }
	void	SetLimitMinute( SI32 siLimitMinute )			{ m_siLimitMinute = siLimitMinute; }
	SI32	DecLimitMinute( SI32 siDecMinute );

};

/**************************************************************************************************************************/
/*------------------------------------------------------------------------------------------------------------------------*/
/*                                                    ��輱 �Դϴ�                                                       */
/*------------------------------------------------------------------------------------------------------------------------*/
/**************************************************************************************************************************/

class CNServerEvent_QuestData_Manager
{
public:
enum SEQD_MANAGER_VARIABLE
{
	SMV_FORHUNTKIND_MAXMAPNUM = 50,
	SMV_FORHUNTKIND_MAXNPCNUM = 30,
};
protected:
#ifdef _SAFE_MEMORY
	NSafeTArray<CNServerEvent_QuestData*, Const_ServerEvent_Max_QuestData>		m_pcltSEQuestData;
#else
	// �����̺�Ʈ�� ��ϵ� Ŭ����
	CNServerEvent_QuestData*	m_pcltSEQuestData[Const_ServerEvent_Max_QuestData];
#endif
	// ���� ���� �̺�Ʈ�� ��ϵ� ��
	SI32						m_siServerEventDataCount;


public:
	CNServerEvent_QuestData_Manager( void );
	~CNServerEvent_QuestData_Manager();

	void	Init( void );


public:
	bool	LoadQuestDataFile( SI16 siServerUnique );

	SI32	EventTypeStringToInteger( IN TCHAR* pszEventTypeString );
	bool	ConditionToInteger( IN SI32 siEventType, IN TCHAR* pszCondition1, IN TCHAR* pszCondition2, OUT SI32 &rsiCondition1, OUT SI32 &rsiCondition2 );
	bool	GetRandQuestData( OUT CNServerEvent_QuestData* pclSEQuestData, IN SI32 siSelectIndex=-1 );
	SI32	GetIndexFromType( SI32 siEventType, SI32 siStartPos=0 );
	
protected:
	bool	AddServerEvent_QuestData( 
		SI32	siEventType,

		SI32	siCondition1,
		SI32	siCondition2,

		SI32	siNeedClearAmount,

		SI32	siRewardItemUnique,
		SI32	siRewardItemAmount,

		SI32	siLimitMinute
		);

	bool	AddServerEvent_QuestData( IN CNServerEvent_QuestData* pclSEQuestData );

	void	ShowMessageBox( TCHAR* pszEventType, SI32 siCondition1=0, SI32 siCondition2=0 );

	SI32	LoadHuntParentMapIndex( SI32 psiMapIndex[] );
	SI32	FindHuntChildMapIndex( IN SI32 siParentMapIndex ,OUT SI32 psiMapIndex[] );
	SI32	RandHuntMonsterKind( SI32 siMapIndex, SI32 siATB=0 );

	SI32	GetRandMonsterKindForHuntKind( SI32 siATB=0 );
	SI32	GetRandItemUinqueForUseItem( SI32 siItemType );
	SI32	GetRandMapIndexForUserCount( void );
	
};

/**************************************************************************************************************************/
/*------------------------------------------------------------------------------------------------------------------------*/
/*                                                    ��輱 �Դϴ�                                                       */
/*------------------------------------------------------------------------------------------------------------------------*/
/**************************************************************************************************************************/

enum SERVEREVENT_QUEST_PACKETTYPE
{
	SERVEREVENT_QUEST_PACKETTYPE_NONE			= 0,// �̷� Ÿ���� ����

	// Ŭ���̾�Ʈ��
	SERVEREVENT_QUEST_PACKETTYPE_QUESTSTART,		// ����Ʈ�� ���۵Ǿ���
	SERVEREVENT_QUEST_PACKETTYPE_RUNINFO,			// ����Ʈ ���� ����
	SERVEREVENT_QUEST_PACKETTYPE_GETCHAR,			// ����Ʈ�� Ŭ���� �ؼ� ���ڸ� �ϳ� �޾Ҵ�
	SERVEREVENT_QUEST_PACKETTYPE_QUEST_FAIL,		// ����Ʈ�� �����ߴ�
	SERVEREVENT_QUEST_PACKETTYPE_CHAR_FAIL,			// ����Ʈ�� Ŭ���� ������ ���ڸ� ���� ���ߴ�
	SERVEREVENT_QUEST_PACKETTYPE_ALLCLEAR,			// ��� ����Ʈ�� Ŭ���� �ߴ�

	// DB��
	SERVEREVENT_QUEST_PACKETTYPE_GET_QUESTINFO,		// ����Ʈ ���� ��û
	SERVEREVENT_QUEST_PACKETTYPE_SET_QUESTINFO,		// ����Ʈ ���� ����

	SERVEREVENT_QUEST_PACKETTYPE_END			
};

class CNServerEvent_Quest
{
protected:
	CNServerEvent_QuestData			m_clSEQuestData;
	CNServerEvent_QuestData_Manager	m_clSEQD_Manager;

#ifdef _SAFE_MEMORY
	NSafeTArray<bool, Const_ServerEvent_Max_QuestCharacter>									m_bCharacter;
#else
	// ���и� ������ ����
	bool							m_bCharacter[ Const_ServerEvent_Max_QuestCharacter ];
#endif
	SI16							m_siInFailCharacter[ Const_ServerEvent_Max_QuestCharacter * Const_ServerEvent_MulNum ];

	SI16							m_siCharacterLimit;			// ������ ���� ����
	SI16							m_siFailAddCharacterLimit;	// ���и� ������ ���� ����

	SI16							m_siCharacterIndex;			// ���� m_bInFailCharacter �����ؾ��ϴ� �ε���

	SI32							m_siNowAmount;				// �󸶸�ŭ�� ����Ʈ ������ ����°�?

	DWORD							m_dwServerEventQuestColck;


public:
	CNServerEvent_Quest( void );
	~CNServerEvent_Quest();

public:
	void						Action( void );

	bool						LoadQuestData( SI16 siServerUnique );

	void						Init( void );
	void						InitCharacter( void );

	void						IncServerEventQuestCondition( SI32 siEventType, SI32 siCondition, SI32 siAmount );

	bool						IsClearServerEventQuest( void );
	bool						ServerEventQuestClearProcess( SI32 siEventType=0 );
	bool						AllClearServerEventQuest( void );
	
	void						MakeNewServerEventQuest( SI32 siEventType=0 );

	CNServerEvent_QuestData*	GetServerEnent_QuestData( void )	{ return &m_clSEQuestData; }
	
	SI16						GetCharacterLimit( void )			{ return m_siCharacterLimit; }
	void						SetCharacterLimit( SI16 siCharacterLimit );

	SI32						GetNowAmount( void )				{ return m_siNowAmount; }
	void						SetNowAmount( SI32 siNowAmount );

	SI16						GetCharacterIndex( void )			{ return m_siCharacterIndex; }
	void						SetCharacterIndex( SI16 siCharacterIndex );

	bool*						GetCharacter( void )				{ return &m_bCharacter[0]; }
	void						SetCharacter( bool bCharacter[] );

	SI16*						GetInFailCharacter( void )			{ return &m_siInFailCharacter[0]; }
	void						SetInFailCharacter( SI16 siInFailCharacter[] );

	DWORD						GetServerEventQuestColck( void )	{ return m_dwServerEventQuestColck; }
	void						SetServerEventQuestColck( DWORD dwServerEventQuestColck );

	void						StartServerEventQuest( void );
	void						SendMessageToDB( SI32 siPacketType );
	
	// ��� ��ɾ� serverquestclear �� ���� ���� ����Ʈ Ŭ���� �� �Լ�
	void						QuestClearForGM( void );

protected:
	void						MakeCharacter( void );
	void						RewardCharacter( void );

	void						IncAmount( SI32 siAmount );
	void						RewardItem( SI32 siItemUnique, SI32 siItemAmount );

	void						SendMessageToClient( SI32 siPacketType, SI32 siPara1=0, SI32 siPara2=0 );
	

};