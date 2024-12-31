#pragma once

#include "../CommonLogic/CommonLogic.h"

//================================================================================
// �ۼ��� : �ڱ���
// �ۼ��� : 2009.08.12
// Ŭ������ : CDormancyInfo
// ���� : �޸� ���� �ý��� ���� ĳ���Ͱ� ������ �־�� �� ����
//================================================================================
class CDormancyInfo
{
	// �ɹ� ����
public:

private:
	_SYSTEMTIME  m_StartedDate;				// �޸� ������ �� ��¥
	SI32	m_siDormancyPoint;				// �޸� ����Ʈ
	SI32	m_siRemainedDormancyPlayTime;	// �޸� ����Ʈ�� �ޱ� ���� �ʿ��� �޸� �÷��� �ð�
	BOOL	m_bDormancyState;				// �޸� ���� ���� ����
	BOOL	m_bGiveDormancyEquipItem;		// �޸� ���� ���� �������� ���� �޾Ҵ���?

	// �ɹ� �޼ҵ�
public:
	// ������
	CDormancyInfo();
	// �Ҹ���
	virtual ~CDormancyInfo(void);

	VOID	Set( CDormancyInfo	*pclDormancyInfo );

	VOID	IncreasePoint();
	VOID	CalcPoint(SI32 siPoint);
	VOID	IncreasePlayTime();

	VOID	SetDormancyPoint(SI32 siDormancyPoint);
	VOID	SetRemainedDormancyPlayTime(SI32 siRemainedDormancyPlayTime);
	VOID	SetDormancyState(BOOL bDormancyState);
	VOID	SetGiveDormancyEquipItem(BOOL bGiveDormancyEquipItem);

	SI32	GetDormancyPoint();
	SI32	GetRemainedDormancyPlayTime();
	BOOL	GetDormancyState();
	BOOL	GetGiveDormancyEquipItem();

	SI32*	GetDormancyPointPointer();
	SI32*	GetRemainedDormancyPlayTimePointer();
	BOOL*	GetDormancyStatePointer();
	BOOL*	GetGiveDormancyEquipItemPointer();
	_SYSTEMTIME* GetStartedDate();
	
};