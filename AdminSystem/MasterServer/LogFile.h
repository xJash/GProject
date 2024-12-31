// LogFile.h: interface for the CLogFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGFILE_H__B40F0C60_2692_49EE_98C8_1092AB399924__INCLUDED_)
#define AFX_LOGFILE_H__B40F0C60_2692_49EE_98C8_1092AB399924__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#include <time.h>
#include <stdio.h>

class CLogFile
{
public:
	CLogFile();
	virtual ~CLogFile();

	void Init(); // �����ϱ�
	void Run(); // �����ϱ�
	void Clear(); // ����Ÿ �ʱ�ȭ
	void ReadLogFile(); // �α� ���� �б� - ������ ���� �� ��
	BOOL ReadLogFileEX(int year,int month,int day); // �α� ���� �б� - ��û ��Ŷ�� ���� ��
	void WriteLogFile(); // �α� ���� ���� - �� 5�и���
	BOOL ParallelFile(); // �α� ���� ������ �� ������ ����� �ֳ� ������ ���� �ð��̶� ���ϱ�
	inline void CriTicalWait(){EnterCriticalSection(&m_cs);};
	inline void CriTicalRelease(){LeaveCriticalSection(&m_cs);};

	_SYSTEMTIME			m_sTime; // �ý��� �ð�
	CRITICAL_SECTION	m_cs; // ũ��Ƽ�� ����

	int					m_iServerTotalUseNum[288]; // �� ���� ���� ������ �ð��뺰 ��ģ ��
	int					m_iServer[100][288]; // ������ ���� ������
	int					m_iLastNum; // ���Ͽ��� ����������� ������ȣ
	int					m_iOldMin ; // ���������� ����� �ð��� ��(Minute)

	char				m_chDate[288][24]; // ��������ϸ�ø���� ��ϵ� ���ڿ�

	BOOL				m_bWrite; // ���Ͽ� �ᵵ �Ǵ°� �ȵǴ°�
};

extern CLogFile*	logFile;

#endif // !defined(AFX_LOGFILE_H__B40F0C60_2692_49EE_98C8_1092AB399924__INCLUDED_)
