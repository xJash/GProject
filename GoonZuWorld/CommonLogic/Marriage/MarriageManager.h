#pragma once 

#include <Directives.h>
#include "../../Common/CommonHeader.h"
#include "../../common/Family/Marriage.h"

#include "../NLib/NUpdateTimer.h"

#include "WeddingManager.h"

#define MARRIAGE_WEDDING_CREATE_NPC_X				14
#define MARRIAGE_WEDDING_CREATE_NPC_Y				10

#define MARRIAGE_WEDDING_COMEIN_CONGRATULATOR_X		10
#define MARRIAGE_WEDDING_COMEIN_CONGRATULATOR_Y		16

#define MARRIAGE_WEDDING_COMEIN_MARRIAGE_PERSON_X	15
#define MARRIAGE_WEDDING_COMEIN_MARRIAGE_PERSON_Y	24

enum MARRIAGE_ABILITY_TYPE
{
	MARRIAGE_ABILITY_TYPE_NONE	= 0,

	MARRIAGE_ABILITY_TYPE_ATTACK,	// ���ݷ� +
	MARRIAGE_ABILITY_TYPE_DEFENSE,	// ���� +
	MARRIAGE_ABILITY_TYPE_LIFE,		// ����� +
	MARRIAGE_ABILITY_TYPE_EXP,		// ����ġ %

	MARRIAGE_ABILITY_TYPE_MAX
};

enum MARRIAGE_EFFECT_TYPE
{
	MARRIAGE_EFFECT_TYPE_NONE = 0,	// ����

	MARRIAGE_EFFECT_TYPE_SMALL,		// ����
	MARRIAGE_EFFECT_TYPE_MEDIUM,	// �߰�
	MARRIAGE_EFFECT_TYPE_LARGE,		// ū��

	MARRIAGE_EFFECT_TYPE_MAX
};

enum MARRIAGE_WEDDING_MESSAGE
{
	MARRIAGE_WEDDING_MESSAGE_05 = 0x0001,
	MARRIAGE_WEDDING_MESSAGE_15 = 0x0002,
	MARRIAGE_WEDDING_MESSAGE_25 = 0x0004,

	MARRIAGE_WEDDING_MESSAGE_35 = 0x0008,
	MARRIAGE_WEDDING_MESSAGE_45 = 0x0010,
	MARRIAGE_WEDDING_MESSAGE_55 = 0x0020,
};

enum MARRIAGE_WEDDING_STATUS
{
	MARRIAGE_WEDDING_STATUS_NONE = 0,


	MARRIAGE_WEDDING_STATUS_READY,					// ���� �غ�
	MARRIAGE_WEDDING_STATUS_START,					// ���� ����

	MARRIAGE_WEDDING_STATUS_COMEIN_WAIT,			// �θ��⸦ ��ٸ�

	MARRIAGE_WEDDING_STATUS_MATE1_COMEIN,			// �����1 ����
	MARRIAGE_WEDDING_STATUS_MATE1_COMEIN_WAIT,		// �����1 �����ϱ⸦ ��ٸ�

	MARRIAGE_WEDDING_STATUS_MATE2_COMEIN,			// �����2 ����
	MARRIAGE_WEDDING_STATUS_MATE2_COMEIN_WAIT,		// �����2 �����ϱ⸦ ��ٸ�

	MARRIAGE_WEDDING_STATUS_MATE1_QUESTION,			// �����1���� ����
	MARRIAGE_WEDDING_STATUS_MATE1_QUESTION_WAIT,	// �����1�� �亯�� ��ٸ�

	MARRIAGE_WEDDING_STATUS_MATE2_QUESTION,			// �����2���� ����
	MARRIAGE_WEDDING_STATUS_MATE2_QUESTION_WAIT,	// �����2�� �亯�� ��ٸ�

	MARRIAGE_WEDDING_STATUS_WEDDING_END,			// ��ȥ�� ����

	MARRIAGE_WEDDING_STATUS_GIVEITEM_QUESTION,		// ȭ�� ������ ���� ����
	MARRIAGE_WEDDING_STATUS_GIVEITEM_WAIT,			// ȭ�� ������ ���� �亯 ��ٸ�
	MARRIAGE_WEDDING_STATUS_GIVEITEM,				// ȭ�� ������ ����

	MARRIAGE_WEDDING_STATUS_END_READY,				// �� �غ�
	MARRIAGE_WEDDING_STATUS_END,					// ��

	MARRIAGE_WEDDING_STATUS_MAX
};

enum MARRIAGE_WEDDING_CHAT_MESSAGE
{
	MARRIAGE_WEDDING_CHAT_MESSAGE_NONE = 0,

	MARRIAGE_WEDDING_CHAT_MESSAGE_READY1,			// �غ�
	MARRIAGE_WEDDING_CHAT_MESSAGE_READY2,			// �غ�
	MARRIAGE_WEDDING_CHAT_MESSAGE_READY3,			// �غ�
	MARRIAGE_WEDDING_CHAT_MESSAGE_SAY1,				// �ַʻ�
	MARRIAGE_WEDDING_CHAT_MESSAGE_SAY2,				// �ַʻ�
	MARRIAGE_WEDDING_CHAT_MESSAGE_SAY3,				// �ַʻ�
	MARRIAGE_WEDDING_CHAT_MESSAGE_SAY4,				// �ַʻ�
	MARRIAGE_WEDDING_CHAT_MESSAGE_COMEIN,			// �����ض�
	MARRIAGE_WEDDING_CHAT_MESSAGE_QUESTION1,		// �Ŷ�,�źο��� ����
	MARRIAGE_WEDDING_CHAT_MESSAGE_QUESTION2,		// �Ŷ�,�źο��� ����
	MARRIAGE_WEDDING_CHAT_MESSAGE_QUESTION3,		// �Ŷ�,�źο��� ����
	MARRIAGE_WEDDING_CHAT_MESSAGE_QUESTION4,		// �Ŷ�,�źο��� ����
	MARRIAGE_WEDDING_CHAT_MESSAGE_END,				// ��ȥ ����

};

// MarriageAbilityItem
class cltMarriageAbilityItem
{
private:
	SI32 m_siAbilityType;	// �ɷ�ġ Ÿ��
	SI32 m_siAbilityValue;	// �ɷ�ġ ��ġ

	SI32 m_siEffectType;	// �������� ����Ʈ Ÿ��

public:
	cltMarriageAbilityItem() : m_siAbilityType(0), m_siAbilityValue(0), m_siEffectType(0) 
	{
	}

	~cltMarriageAbilityItem()
	{
	}

	void Init( void )
	{
		ZeroMemory( this, sizeof(cltMarriageAbilityItem) );
	}

	void Set( cltMarriageAbilityItem* pclMarriageAbilityItem )
	{
		
	}

	void Set( SI32 siAbilityType, SI32 siAbilityValue, SI32 siEffectType )
	{
		m_siAbilityType		= siAbilityType;	
		m_siAbilityValue	= siAbilityValue;	

		m_siEffectType		= siEffectType;	
	}

// Utility Function
public:
	SI32 GetAbilityType( void )					{	return m_siAbilityType;				}
	void SetAbilityType( SI32 siAbilityType )	{	m_siAbilityType = siAbilityType;	}

	SI32 GetAbilityValue( void )				{	return m_siAbilityValue;			}
	void SetAbilityValue( SI32 siAbilityValue )	{	m_siAbilityValue = siAbilityValue;	}

	SI32 GetEffectType( void )					{	return m_siEffectType;				}
	void SetEffectType( SI32 siEffectType )		{	m_siEffectType = siEffectType;		}

	BOOL IsEmpty( void )
	{
		if ( 0 < m_siAbilityType )	return FALSE;
		if ( 0 < m_siAbilityValue )	return FALSE;
		if ( 0 < m_siEffectType	)	return FALSE;
		
		return TRUE;
	}

};

class cltMarriageAbilityManager
{
private:
	cltMarriageAbilityItem*		m_pclMarriageAbilityItem;

public:
	cltMarriageAbilityManager( void );
	~cltMarriageAbilityManager( );

// For Resource Function
public:
	BOOL LoadMarriageAbilityInfo( void );
private:
	SI32 ConvertAbilityTypeFromText( TCHAR* pszAbilityTypeText );
	SI32 ConvertEffectTypeFromText( TCHAR* pszEffectTypeText );

	void AddMarriageAbilityItem( SI32 siLoveLevel, SI32 siAbilityType, SI32 siAbilityValue, SI32 siEffectType );

// Utility Function
public:
	SI32 GetTotalAbilityValue( SI32 siAbilityType, SI32 siLoveLevel );
	SI32 GetEffectType( SI32 siLoveLevel );
}; 


class cltMarriageManager
{
private:
	cltMarriageAbilityManager	m_clAbilityMgr;

	NUpdateTimer				m_UpdateTimerWeddingAction;

private:
	SI32						m_siWeddingMessage;			// ���� �޽��� ����
	SI32						m_siWeddingStatus;			// ���� �����Ȳ ����

	SI32						m_siOfficiatorID;			// �ַ� NPC CharID

	SI32						m_siWeddintProgressCount;	// ���� ����� �ʿ��� ī��Ʈ

public:
	cltWeddingReserveList		m_clWeddingList;

public:
	cltMarriageManager( void );
	~cltMarriageManager();

	void Init( void );
	void InitForWeddingVariable( void );

	void ActionForWedding( void );

public:
	SI32 GetTotalAttackAbilityValue( SI32 siLoveLevel ); 
	SI32 GetTotalDefenseAbilityValue( SI32 siLoveLevel );
	SI32 GetTotalLifeAbilityValue( SI32 siLoveLevel );
	SI32 GetTotalExpAbilityValue( SI32 siLoveLevel );

	// ������ ���� ����Ʈ Ÿ���� �����´�
	SI32 GetEffectTypeFromLoveLevel( SI32 siLoveLevel );

public:
	// ���� ���� ���¸� �޾ƿ´�
	SI32 GetWeddingStatus( void )	{	return m_siWeddingStatus;	};

	// �������� �ڸ��� �ִ´�
	void PushWeddingMessage( TCHAR* pszName1, TCHAR* pszName2, bool bFuture=false, SI16 siHour=0 );
	// ���� �޽��� ���°� Toogle�Ǿ��ִ� �� �˻�
	BOOL IsWeddingMessage( SI32 siWeddingMessage );
	BOOL CheckAndSetForProgressMessage( SI16 siMinute );
	BOOL CheckAndSetForFutureMessage( SI16 siMinute );

public:
	// ���������� ���İ��� ���μ����� ������ �Լ�
	void WeddingProcess( cltWeddingReserveUnit* pclUnit );
	// �����忡 ��ȥ���� �ø� �� ĳ���Ͱ� �ִ��� �˻�
	BOOL IsInHearMapWeddingPersons( IN SI32 siMate1_PersonID, IN SI32 siMate2_PersonID, OUT SI32* psiMate1CharUnique, OUT SI32* psiMate2CharUnique );
	// ��ȥ���� �ø� �� ĳ���͸� ���������� �ҷ��´�
	BOOL ComeInMarriagePersons( SI32 siMate1_PersonID, SI32 siMate2_PersonID );
	// �۽����̵� ���ĸ� Ư����ġ�� �ִ��� �˻�
	BOOL IsComeInMarriagePerson( SI32 siPersonID );
	// �ַ� NPC����
	BOOL CreateOfficiatorNPC( void );	// �ַ� NPC����
	void DeleteOfficiatorNPC( void );	// �ַ� NPC����
	// �����忡 �ִ� ��� ĳ���� �鿡�� ä�� �޽����� ������
	void SendWeddingChatMessage( SI32 siMessageMode, TCHAR* pszName1=NULL, TCHAR* pszName2=NULL );
	// ���� ���� ���¸� �����Ѵ�
	void ChangeWeddingStatus( SI32 siChangeWeddingStatus );
	// �����忡 �ִ� ��� ������� ��������
	void OutInHearMapAllPerson( void );
	// �źο��� ȭ���� ���������� �����
	BOOL QuestionDropWeddingFlower( SI32 siMate1_PersonID, SI32 siMate2_PersonID );
	// �ϰ� Ȥ�� ��ȥ���� �ø� ������� ȭ�� �������� �ش�
	void GiveWeddingFlowerItem( SI32 siMate1_PersonID, SI32 siMate2_PersonID );
	
};
