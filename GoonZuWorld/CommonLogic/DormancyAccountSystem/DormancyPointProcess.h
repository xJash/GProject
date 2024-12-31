#pragma once

#include "../../GoonZuWorld/Common/CommonHeader.h"

class cltCharCommon;

//================================================================================
// �ۼ��� : �ڱ���
// �ۼ��� : 2009.08.2
// Ŭ������ : CDormancyPointProcess
// ���� : �޸� ���� �ý����� ����Ʈ ó�� Ŭ����
//================================================================================

class CDormancyPointProcess
{
//�ɹ� ����
public:
	// ����Ʈ ��� ��� 
	const static SI32 CALCPOINT_RESULT_INCREASEPOINT = 1;
	const static SI32 CALCPOINT_RESULT_INCREASEPLAYTIME = 2;
	const static SI32 CALCPOINT_RESULT_CALCERROR = 3;

private:
	// ����Ʈ ������ ���� ���Ǵ� �ʱ� �ð�
	const static SI32 INIT_TIME = 0; //0�� (���� : ��)

	// ����Ʈ�� ���� �ϴ� �ð�
	const static SI32 POINT_TIME = 60; //1�ð� (���� : ��)

	// ó�� ���� �ð�
	const static SI32 UNIT_TIME = 60000; //1�� (���� : �и�������)

	// ���������� ó�� �� �ð�
	DWORD	m_siLastProcessingTime;

	// ó�� ����
	BOOL	m_bProcessing;

//�ɹ� �޼ҵ�
public:
	CDormancyPointProcess(void);
	virtual ~CDormancyPointProcess(void);

	// ����Ʈ ����
	BOOL	ChangePoint(cltCharCommon *pclChar, SI32 siPoint);

	// ����Ʈ ���
	BOOL	CalcPoint(cltCharCommon *pclChar);

	// ó�� ���� ���� ����
	BOOL	DeterminProcessing(DWORD	siCurrentime);
};
