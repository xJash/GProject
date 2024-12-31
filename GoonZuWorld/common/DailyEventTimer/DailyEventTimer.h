#pragma once

#include "../CommonLogic/CommonLogic.h"

#define EVENT_0_OCLOCK				0x00000001
#define EVENT_1_OCLOCK				0x00000002		
#define EVENT_2_OCLOCK				0x00000004		
#define EVENT_3_OCLOCK				0x00000008		
#define EVENT_4_OCLOCK				0x00000010  	
#define EVENT_5_OCLOCK				0x00000020  	
#define EVENT_6_OCLOCK				0x00000040		
#define EVENT_7_OCLOCK				0x00000080		
#define EVENT_8_OCLOCK				0x00000100		
#define EVENT_9_OCLOCK				0x00000200		
#define EVENT_10_OCLOCK				0x00000400		
#define EVENT_11_OCLOCK				0x00000800		
#define EVENT_12_OCLOCK				0x00001000		
#define EVENT_13_OCLOCK				0x00002000		
#define EVENT_14_OCLOCK				0x00004000		
#define EVENT_15_OCLOCK				0x00008000		
#define EVENT_16_OCLOCK				0x00010000		
#define EVENT_17_OCLOCK				0x00020000		
#define EVENT_18_OCLOCK				0x00040000		
#define EVENT_19_OCLOCK				0x00080000		
#define EVENT_20_OCLOCK				0x00100000		
#define EVENT_21_OCLOCK				0x00200000		
#define EVENT_22_OCLOCK				0x00400000		
#define EVENT_23_OCLOCK				0x00800000	

//================================================================================
// �ۼ��� : �ڱ���
// �ۼ��� : 2009.09.29
// Ŭ������ : CDailyEventTimer
// ���� : ���� �Ͼ�� �̺�Ʈ,
//		  �Էµ� Ư�� �ð� �� ������ �д����� ���� �Ǵ� Ÿ�̸�
//================================================================================
class CDailyEventTimer
{	 
	// �ɹ� �޼ҵ�
public:
	CDailyEventTimer();
	~CDailyEventTimer();

	// �̺�Ʈ �߻� �ð� �� �Է�
	void	AddTime(UI32 uiHour);
	// Ÿ�̸� �۵�
	BOOL	Execute(SI32	siMinute, BOOL (*pCallBackFunc)());
	// Ÿ�̸� ����
	void	Stop();

	// ������ ������ ����
	BOOL	IsTimed();

protected:
	// 32��Ʈ
	const static SI32 BITSIZE = 32;
	//	ó�� �Լ� ������
	BOOL (*pFuncProcess)();
	
	//	�۵� ����
	BOOL	m_bOperation;
	//	��
	SI32	m_siMinute;

	//  �̺�Ʈ �߻� �ð� ���� ������
	UI32	m_uiTime;
	
	//  ���� �ð� �� �ߺ� ���� ����
	SI32	m_siDuplExecCheck;
};

