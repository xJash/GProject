#pragma once

//****************************************************************************** 
// 
// * ���̾�Ʈ ���� ��Ȱ ����.
//
//******************************************************************************

#include "CommonHeader.h"
#include "CommonLogic.h"

class cltGRREHuntMapMonsterInfo;
class cltGRREVillageInfo;
class cltContributionEvent_Common;
class cltContributionInfo;

//==============================================================================
// - ���̾�Ʈ ���� ��Ȱ ���� ����. GiantRaccoonResurrectEvent => GRRE
//==============================================================================
class cltGiantRaccoonResurrectEvent : public cltContributionEvent_Common
{
public:
	enum { POTRACCOON_CONTRIBUTION_ITEM_NUM = 10, };

public:
	cltGiantRaccoonResurrectEvent( void );
	~cltGiantRaccoonResurrectEvent( void );

	bool	FileLoad( void );
	void	Clear( void );
	bool	Init( TCHAR* _pszMap, TCHAR* _pszEventHour, SI32 _siRegenMonsterKind, SI32 siMapRegenMonsterNum, SI32 siMapOnceRegenMonsterNum );
	void	Action( void );

	bool	IsEventActiveTime( void );
	bool	IsInputItem( void );

	void	SetFirstMakeVillage( SI32 _siFirstMakeVillage );
	SI32	GetFirstMakeVillage( void );
	bool	IsFirstMakeVillage( SI32 _siFirstMakeVillage );

private:
	void	CheckNPC( void );
	void	Start( void );											// �̺�Ʈ ����.
	void	End( void );											// �̺�Ʈ ����.
	void	Run( void );											// �̺�Ʈ ����.

	void	MonsterDel( void );										// ���� ����.
	void	InputItemListDel( void );								// ������� ���� ��� �������� �����Ѵ�.			
	void	MonsterRegen( void );									// �� ����Ϳ� ���� ����.
	SI32	GetTotalRegenMonsterCount( void );						// ����Ϳ� ���� �� ������ ��ü ������

	static bool	static_IsMakeNpc( void* _pclGiantRaccoonResurrectEvent, cltCharServer* _pclChar );
	static bool	static_CompleteMakeNpc( void* _pclGiantRaccoonResurrectEvent, cltCharServer* _pclChar );
	static bool	static_IsContribution( void* _pclGiantRaccoonResurrectEvent, cltCharServer* _pclChar );
	
	bool	IsMakeNpc( cltCharServer* _pclChar );
	bool	CompleteMakeNpc( cltCharServer* _pclChar );
	bool	IsContribution( cltCharServer* _pclChar );

private:
	bool							m_bEventActive;					// �̺�Ʈ �ð��ΰ�.
	bool							m_bInputItem;					// ������ ��ΰ� �����Ѱ�.
	SI32							m_siTotalMapNum;				// ���� �� ����.
	SI32							m_siTotalRegenMonsterNum;		// ��ü ���� �� ������ ��.
	DWORD							m_dwMonsterRegenTickCount;		// ���� ���� ƽ ī��Ʈ.
	DWORD							m_dwBeginMonsterRegenTickCount;	// ���� ���� ƽ ī��Ʈ.
	

	cltGRREHuntMapMonsterInfo*		m_pclGRREHuntMapMonsterInfo;	// ���� �� ����.
	cltGRREVillageInfo*				m_pclGRREVillageInfo;			// �̺�Ʈ ���� ���� ����.
	bool							m_bEventHour[24];				// �̺�Ʈ �ð��ΰ�?

	cltContributionInfo*			m_pclContributionInfo;			// �� NpcKind�� ���õ� ��� ����.			

	SI32							m_siNpcID;						// ���� ����ϴ� NPC
};

//==============================================================================
// - ���̾�Ʈ ���� ��Ȱ ���� �� ������ ���� ����.
//==============================================================================
class cltGRREHuntMapMonsterInfo
{
public:
	cltGRREHuntMapMonsterInfo( void );
	~cltGRREHuntMapMonsterInfo( void );

	void	Init( SI32 _siMapIndex, SI32 _siRegenMonsterNum );
	void	Clear( void );
	SI32	GetMapIndex( void );											// �� �ε��� ����.
	void	MonsterDel( void );												// ���� ����.
	void	MonsterRegen( void );											// �ش� �ʿ� ���͸� ���� ��Ų��.
	SI32	GetRegenMonsterCount( void );									// ���� �� ������ ���� ��.
	void	SetRegenMonsterKind( SI32 _siRegenMonsterKind );
	void	SetMapRegenMonsterNum( SI32 _siMapRegenMonsterNum );
	void	SetMapOnceRegenMonsterNum( SI32 _siMapOnceRegenMonsterNum );

private:
	SI32	m_siMapIndex;								// �� �ε���
	SI32*	m_psiMonsterID;								// �ش� �ʿ� ���� �� ������ ID
	SI32	m_siRegenMonsterCount;						// ���� �� ������ ���� ��.

public:	
	static SI32	m_siRegenMonsterKind;					// �����Ǵ� ���� ����. 
	static SI32	m_siMapRegenMonsterNum;					// �ʿ� �����Ǵ� ��ü ������ ��.
	static SI32	m_siMapOnceRegenMonsterNum;				// �ʿ� 1ȸ ���� �� �����Ǵ� ������ ��. 
};

//==============================================================================
// - ���ʷ� ��Ȱž�� �Ǽ��� ����.
//==============================================================================
class cltGRREVillageInfo
{
public:
	cltGRREVillageInfo( void );
	~cltGRREVillageInfo( void );

	void	Clear( void );

	void	SetFirstMakeVillage( SI32 _siFirstMakeVillage );
	SI32	GetFirstMakeVillage( void );
	bool	IsFirstMakeVillage( SI32 _siFirstMakeVillage );

private:
	SI32	m_siFirstMakeVillage;
};
