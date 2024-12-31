#pragma once

//****************************************************************************** 
// 
// * ��� ���� �̺�Ʈ���� �� �̰��� ��ӹް� �Ѵ�.
//
// * ��ο� �⺻�� ��� �������� ����, ��� �޴� ������  �ִ��, ��θ� �޴� NPC�� ī�ε带 �⺻������ ������.
//
//******************************************************************************

#include "CommonHeader.h"
#include "CommonLogic.h"

#define CONTRIBUTION_ITEM_NUM	  6	// ��� �������� �ִ� ����.
#define CONTRIBUTION_INFO_NUM	100	// ��� ���� ���� �ִ� ����.

class cltContributionInfo
{
public:
	SI32	m_siNPCKind;
	SI32	m_siMakeNPCKind;
	SI32	m_siItemUnique[CONTRIBUTION_ITEM_NUM];	// ��ΰ� ������ �������� ����ũ.
	SI16	m_siItemNum[CONTRIBUTION_ITEM_NUM];		// ��ΰ� ������ �������� ��.
	bool	m_bMyVillage;							// �� �������� ��ο� NPC(������) ����Ⱑ �����ϳ�.
};


class cltContributionEvent_Common
{
public:
	cltContributionEvent_Common( void );
	~cltContributionEvent_Common( void );

	bool					FileLoad( void );
	void					Clear( void );
	cltContributionInfo*	FindContributionInfo( SI32 siNPCKind );
	SI32					GetMakeNPC( SI32 siNPCKind );									// �ش� NPC�� ����� �ִ� NPC�� ����.

	bool					Insert( SI32 _siNPCKind, 
									void* _pClass, 
									bool (*_pMakeNpcFunc)( void* _pClass, cltCharServer* _pclChar ), 
									bool (*_pCompleteMakeNpcFunc)( void* _pClass, cltCharServer* _pclChar ), 
									bool (*_pContributionFunc)( void* _pClass, cltCharServer* _pclChar ) );

	bool					IsMakeNpc( SI32 _siNPCKind, cltCharServer* _pclChar );									// npc�� ���鶧 ���� ���� Ȯ�ο� �Լ� ���.
	bool					CompleteMakeNpc( SI32 _siNPCKind, cltCharServer* _pclChar );							// npc�� ������� �� ���ϴ� �ൿ �Լ�.
	bool					IsContribution( SI32 _siNPCKind, cltCharServer* _pclChar );								// ��ν� ��� ���� ���θ� Ȯ�ο� ���.	
	void					ContributionItemListDelete( SI32 m_siVillageUnique, SI32 m_siNPCKind );					// ����� �������� �����Ѵ�.
	
private:
	static bool					m_bCreate;
	static cltContributionInfo* m_pclContributionInfo[CONTRIBUTION_INFO_NUM];

	static void*				m_pClass[MAX_KIND_NUMBER];										// �� Ŭ����. 
	static bool					(*m_pMakeNpcFunc[MAX_KIND_NUMBER])( void* _pClass, cltCharServer* _pclChar );			// npc�� ����°� �������� �˻��� �Լ��� ���. (�ǹ� �ϼ� �� Ȯ��)
	static bool					(*m_pCompleteMakeNpcFunc[MAX_KIND_NUMBER])( void* _pClass, cltCharServer* _pclChar );	// npc�� ����µ� �����ϸ� ȣ��� �Լ��� ���. (�ǹ� �ϼ� ��)
	static bool					(*m_pContributionFunc[MAX_KIND_NUMBER])( void* _pClass, cltCharServer* _pclChar );		// ��ΰ� �������� �˻��� �Լ��� ���.
};

