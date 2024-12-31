#include ".\dormancypointProcess.h"
#include "DormancyInfo.h"
#include "../common/char/CharCommon/Char-Common.h"

CDormancyPointProcess::CDormancyPointProcess(void)
{
	// ���������� ó�� �� �ð�
	m_siLastProcessingTime = 0;

	// ó�� ����
	m_bProcessing = FALSE;
}

CDormancyPointProcess::~CDormancyPointProcess(void)
{
}

// ����Ʈ ���
SI32	CDormancyPointProcess::CalcPoint(cltCharCommon *pclChar)
{
	if( NULL == pclChar)
		return CALCPOINT_RESULT_CALCERROR;
	if( NULL == pclChar->pclCI)
		return CALCPOINT_RESULT_CALCERROR;
	if( FALSE == m_bProcessing)
		return CALCPOINT_RESULT_CALCERROR;

	// �޸� ���� 
	CDormancyInfo &rclDormancyInfo = pclChar->pclCI->clDormancyInfo;

	// �÷��� �ð� ���� (1�� ����)
	rclDormancyInfo.IncreasePlayTime();

	// ����Ʈ ���� �ϴ� �ð��� �÷��� �Ͽ��ٸ�
	if( POINT_TIME <= rclDormancyInfo.GetRemainedDormancyPlayTime() )
	{
		// �÷��� �ð� �ʱ�ȭ
		rclDormancyInfo.SetRemainedDormancyPlayTime( INIT_TIME );
		return CALCPOINT_RESULT_INCREASEPOINT;
	}
	
	return CALCPOINT_RESULT_INCREASEPLAYTIME;
}

// ó�� ���� ���� ����
BOOL	CDormancyPointProcess::DeterminProcessing(DWORD	siCurrentime)
{
	if( m_siLastProcessingTime > siCurrentime)
	{
		m_siLastProcessingTime = 0;
	}

	if( (siCurrentime - m_siLastProcessingTime) >= UNIT_TIME)
	{
		m_bProcessing = TRUE;
		m_siLastProcessingTime = siCurrentime;
	}
	else
	{
		m_bProcessing = FALSE;
		return FALSE;
	}
	return TRUE;
}

// ����Ʈ ����
BOOL	CDormancyPointProcess::ChangePoint(cltCharCommon *pclChar, SI32 siPoint)
{
	if( NULL == pclChar)
		return FALSE;
	if( NULL == pclChar->pclCI)
		return FALSE;

	// �޸� ���� 
	CDormancyInfo &pclDormancyInfo = pclChar->pclCI->clDormancyInfo;

	pclDormancyInfo.CalcPoint(siPoint);

	return TRUE;
}