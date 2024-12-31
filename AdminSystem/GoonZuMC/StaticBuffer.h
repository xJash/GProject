#pragma once

//===============================================================
// ������ : �ڱ���
// ���� :  ���� ���� Ŭ����
//		   ���� ������ ��� ����
//===============================================================

#include <windows.h>

class StaticBuffer
{
//	���� ����
protected:
	//	��ü ����
	BYTE*	m_Buffer;
	//	1�� ������ ũ��
	DWORD	m_Size;
	//	��ü ������ ����
	DWORD	m_Max_Count;
	
	//	�Է� ������
	DWORD	m_In_Index;
	//	��� ������
	DWORD	m_Out_Index;
	//	��ȯ ��
	bool	m_Cyc_TF;

//	���� �޼ҵ�
protected:
	//	��� ���� �ʱ�ȭ
	void	init();

public:
	//	���� ���̵�
	DWORD	m_Buffer_ID;

public:
	StaticBuffer(void);
	~StaticBuffer(void);
	
	//	����
	BOOL	Create(DWORD p_Size, DWORD p_Count);
	//	����
	BOOL	Delete();

	//	���ۿ� ������ �Է�
	BOOL	In_Data_Buffer(BYTE* p_In);
	BOOL	In_Data_Buffer(BYTE* p_In,DWORD p_Size, DWORD p_StartPoint = 0);
	//	���ۿ� �����ؼ� �����Ϳ� �Է�(DWORD p_StartPoint <= �����ּ�)
	BOOL	In_Data_Buffer_N(BYTE* p_In, DWORD p_Size, DWORD p_StartPoint);

	//	���ۿ� ������ ���
	BOOL	Out_Data_Buffer(BYTE * p_Out);
	BOOL	Out_Data_Buffer(BYTE * p_Out,DWORD p_Size);

	//	���� ������ ������ ���
	BYTE*	ReadData();

	// 1�� ���� ������
	DWORD	GetSize();

	//	������ �ִ� ������ ��
	DWORD	GetExistDataCount();
};