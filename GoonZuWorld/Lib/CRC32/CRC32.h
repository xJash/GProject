#pragma once

#include "NDataTypes.h"

class CCRC32
{

enum{
	XOR_VALUE				= 0xFFFFFFFFL,	//���� ��Ʈ(�̰� ��� ~�����ڸ� �ᵵ ����)
	POLYNOMIAL				= 0xEDB88320L,	//�ִ��� �ߺ����� ���� ������
	MAX_READ_BUFFER_SIZE	= 65536,		//�ִ� �б� ���� ������
	MAX_CRC_TABLE_NUM		= 256,			//�ִ� CRC ���̺� ��	
	ERROR_RETURN_VALUE		= 0				//������ ���ϵǴ� ��
};


// �ɹ� ���� ����
protected:
	//�ӵ���� �� �޸� ����(��ü�� �޶� ���̺��� �������� �̿���)�� �������� static���� ���̺� �� ����
	const static unsigned long m_ulCRCTable[MAX_CRC_TABLE_NUM]; 

// ��� �Լ� ����
public:
	CCRC32(void);
	// ���� ������
	CCRC32( const CCRC32& inDuplicate );
	~CCRC32(void);

	unsigned long CalculateCRCCode( TCHAR* ptstrFileName, unsigned long *pGetSize=NULL );
	unsigned long CalculateCRCCode( FILE* pFile, unsigned long *pGetSize=NULL );
		
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
class CCRC32List : public CCRC32
{
// ��� ���� ����
protected:
	TCHAR			m_tszFileName[MAX_PATH];	// ���� �̸�
	unsigned long	m_ulCRC32Code;				// CRC32 �ڵ�
	unsigned long	m_ulFileSize;				// ���� ������


// ��� �Լ� ����
public:
	CCRC32List();
	CCRC32List( const TCHAR* ptsFileName );
	// ���� ������
	CCRC32List( const CCRC32List& inDuplicate );

	~CCRC32List() {};

public:
	BOOL SetList( const TCHAR* ptsFileName );	// ���� �̸��� ������ ��� ��� ������ ��Ʈ�Ѵ�.

	const TCHAR* GetFileName(void) const { return m_tszFileName; }
	unsigned long GetCRC32Code(void) const { return m_ulCRC32Code; }
	unsigned long GetFileSize(void) const { return m_ulFileSize; }

public:
	SI08 Compare( const CCRC32List& inCompare);


};


///////////////////////////////////////////////////////////////////////////////////////////////////////
class CCRC32Controller
{
// ��� ���� ����
protected:
	CCRC32List*		m_pCRC32List; // ���� �Ҵ��� ���� ����
	unsigned int	m_uiElements; // ���� CCRC32List�� ����


// ��� �Լ� ����
public:
	CCRC32Controller();
	~CCRC32Controller();

public:
	BOOL Set( const TCHAR* ptsFileNames, const UI08 uiElements );
	CCRC32List* GetCRC32List( const UI08 uiElement );

public:
	BOOL ListCompare( const CCRC32List* pCRC32List, const UI08 uiElements );

};
