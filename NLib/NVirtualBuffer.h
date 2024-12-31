//-----------------------------------------------------------------------------
// 2005/12/21 ������
//-----------------------------------------------------------------------------

#ifndef _NVIRTUALBUFFER_H
#define _NVIRTUALBUFFER_H

#include "NDataTypes.h"

class NVirtualBuffer
{
public:
	NVirtualBuffer();
	~NVirtualBuffer();

	void			CreateVirtualBuffer( DWORD dwMaxSize );
	BYTE*			Alloc( DWORD dwSize );

	BYTE*			GetBasePtr() { return m_pBasePtr; }

	DWORD			m_dwPageSize;					// ������ ũ�� 4096

	BYTE*			m_pBasePtr;						// ���̽� ������
	BYTE*			m_pCurPtr;						// ���� Commit ��ġ

	DWORD			m_dwReservedSize;				// �� ����� ���� ũ��
	DWORD			m_dwCommittedSize;				// Committed �� ���� ũ��

	DWORD			m_dwAllocSize;					// ���� ����ϱ� ���� �Ҵ�� ���� ũ��
	
};


#endif