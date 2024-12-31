#include "StaticBuffer.h"

StaticBuffer::StaticBuffer(void)
{
	//	��ü ����
	m_Buffer = NULL;

	//	���ۿ��� ���� �ʱ�ȭ
	init();
}

StaticBuffer::~StaticBuffer(void)
{
	if(m_Buffer != NULL)
	{
		free(m_Buffer);
		m_Buffer = NULL;
	}
}
//	��� ���� �ʱ�ȭ
void	StaticBuffer::init()
{
	//	1�� ������ ũ��
	m_Size = 0;
	//	��ü ������ ����
	m_Max_Count = 0;
	//	�Է� ������
	m_In_Index = 0;
	//	��� ������
	m_Out_Index = 0;
	//	��ȯ ��
	m_Cyc_TF = false;
	//	���� ���̵�
	m_Buffer_ID = 0;
}

//	����
BOOL	StaticBuffer::Create(DWORD p_Size, DWORD p_Count)
{
	//	���� ���� ����
	Delete();
	m_Size = p_Size;
	m_Max_Count = p_Count;

	//	���� �Ҵ�
	m_Buffer = (BYTE*) malloc(m_Max_Count * m_Size);
	if( m_Buffer == NULL)
		return false;
	//	���� �ʱ�ȭ	
	//memset(m_Buffer,0, m_Max_Count * m_Size);
	return true;
}
//	����
BOOL	StaticBuffer::Delete()
{
	if(m_Buffer != NULL)
	{
		//	���� �ʱ�ȭ	
		memset(m_Buffer,0, m_Max_Count * m_Size);
	}
	// �ʱ�ȭ
	init();

	return true;
}

//	���ۿ� ������ �Է�
BOOL	StaticBuffer::In_Data_Buffer(BYTE* p_In)
{
	if(p_In == NULL)
		return false;

	return In_Data_Buffer(p_In, m_Size);
}
BOOL	StaticBuffer::In_Data_Buffer(BYTE* p_In,DWORD p_Size, DWORD p_StartPoint)
{
	//	���� Ȯ��
	if(p_In == NULL)
		return false;
	if(p_Size > m_Size) 
		return false;
	if(m_Buffer == NULL)
		return false;

	//	1. cyc, t �Է� >= ��� return false
	if(m_In_Index< m_Max_Count)
	{
		//	2. ������ ����
		memcpy((LPVOID)&(m_Buffer[m_In_Index * m_Size + p_StartPoint]), p_In, p_Size);

		//	3. �Է� �ε��� ����
		++m_In_Index;
		//	4. ��ȯ Ȯ��
		if(	m_In_Index >= m_Max_Count)
		{
			m_Cyc_TF = true;
			m_In_Index = 0;
		}
	}
	else
	{
		//	���� ����
		m_Cyc_TF = false;
		m_In_Index = 0;
		
	}
	return true;
}

//	���ۿ� ������ ���
BOOL	StaticBuffer::Out_Data_Buffer(BYTE * p_Out)
{
	//	���� Ȯ��
	if(p_Out == NULL)
		return false;

	return Out_Data_Buffer(p_Out, m_Size);
}
BOOL	StaticBuffer::Out_Data_Buffer(BYTE * p_Out,DWORD p_Size)
{
	//	���� Ȯ��
	if(p_Out == NULL)
		return false;
	if(p_Size > m_Size) 
		return false;
	if(m_Buffer == NULL)
		return false;

	//	������ ���� ������
	if(m_Cyc_TF)
	{
		// ������ ������ ���
		if(m_Max_Count > m_Out_Index)
		{
			// ���ۿ� ����
			memcpy(p_Out,&m_Buffer[m_Size*m_Out_Index], p_Size);
			m_Out_Index++;
			if(m_Out_Index >= m_Max_Count)
			{
				// ���� �ʱ�ȭ
				m_Cyc_TF = false;
				m_Out_Index = 0;
			}
			return true;
		}
		else
		{
			// ���� �ʱ�ȭ
			m_Cyc_TF = false;
			m_Out_Index = 0;
		}
	}
	else if(m_In_Index > m_Out_Index)
	{
		// ���ۿ� ����
		memcpy(p_Out,&m_Buffer[m_Size*m_Out_Index], p_Size);
		m_Out_Index++;
		if(m_Out_Index >= m_Max_Count)
		{
			m_Out_Index = 0;
		}
		return true;
	}
	return false;
}

//	���� ������ ������ ���
BYTE*	StaticBuffer::ReadData()
{
	if(m_Buffer == NULL)
		return NULL;

	return &m_Buffer[m_Size*m_Out_Index];;
}

// 1�� ���� ������
DWORD	StaticBuffer::GetSize()
{
	return m_Size;
}

//	������ �ִ� ������ ��
DWORD	StaticBuffer::GetExistDataCount()
{
	int rValue = 0;
	if(!m_Cyc_TF)
		rValue = m_In_Index - m_Out_Index;
	else
		rValue = m_Out_Index - m_In_Index;

	return rValue;
}

//	���ۿ� �����ؼ� �����Ϳ� �Է�(DWORD p_StartPoint <= �����ּ�)
BOOL	StaticBuffer::In_Data_Buffer_N(BYTE* p_In, DWORD p_Size, DWORD p_StartPoint)
{
	//	���� Ȯ��
	if(p_In == NULL)
		return false;
	if(p_Size > m_Size) 
		return false;
	if(p_StartPoint > m_Size) 
		return false;
	if(p_Size + p_StartPoint > m_Size)
		return false;
	if(m_Buffer == NULL)
		return false;

	//	2. ������ ����
	memcpy((LPVOID)&(m_Buffer[m_In_Index * m_Size + p_StartPoint]), p_In, p_Size);

	return true;
}
