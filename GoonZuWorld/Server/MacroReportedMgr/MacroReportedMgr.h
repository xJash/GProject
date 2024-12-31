#pragma once

#include <windows.h>
#include <directives.h>

#define	MACROREPORTEDMGR_MAX_MANAGED_USER_NUM		100
#define	MACROREPORTEDMGR_REPORTEDNUM_PERDAY			3				// �Ϸ翡 �� ĳ���Ͱ� �Ű�Ǿ��� �� �ִ� ȸ��

struct	strMacroReportedUser
{
	SI32	siPersondID;			// �Ű�Ǿ��� ĳ������ PersonID
	SI32	siReportedNum;			// �Ű�Ǿ��� ȸ��
};

class cltMacroReportedMgr
{
private:

	strMacroReportedUser	m_stMacroReportedUser[ MACROREPORTEDMGR_MAX_MANAGED_USER_NUM ];	

public:
	cltMacroReportedMgr();
	~cltMacroReportedMgr();

	VOID	Initialize();
	VOID	Free();	
	
	SI32	GetReportedNum( SI32 siPersonID );
		
	/*
	CanUserReport ���ϰ� ����
	1	:	����
	0	:	�Ϲ� ���� ����
	-1	:	�ش� ĳ������ ���� �Ű� ȸ�� �ʰ��� ���� ����
	*/
	SI32	CanUserReport( SI32 siPersonID );
	VOID	OnUserReported( SI32 siPersonID );

	VOID	OnDayChanged();
};
