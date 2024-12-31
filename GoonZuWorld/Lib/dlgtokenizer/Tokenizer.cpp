#include "Tokenizer.h"
#include <string.h>

////////////////////////////////////////////////////////////////////
// Public functions
//
CTokenizer::CTokenizer( char* pstrInput, const char strHeaderDelimiter, const char strDelimiter, const char strEndline )
{
	for(int i=0; i<MAX_CONTROL_PROPERTY_NUM; i++)
		m_pstra[i] = 0;

	m_propertycount = 0;

	Init(pstrInput, strHeaderDelimiter, strDelimiter, strEndline);
}

CTokenizer::~CTokenizer()
{
	for(int i=0; i<MAX_CONTROL_PROPERTY_NUM; i++)
	{
		if(m_pstra[i] != 0)
		{
			delete m_pstra[i];
			m_pstra[i] = 0;
		}
	}
}

void CTokenizer::Init( char* pstrInput, const char strHeaderDelimiter, const char strDelimiter, const char strEndline )
{

	char* pcopy=0;

	int i=0, length = 0;
	int nFound = 0;

	int start_pos = 0;	// �Է� ���� ���ڿ������� ó�� ���� ��ġ
	int header_length = 0; // ��� �κ� ���ڿ� ����

	if(pstrInput == 0)
		return;

	// 0 string terminate ���� ������ ��ü ���� ����
	length = strlen(pstrInput);

	if(length < 1 || pstrInput[length] != '\0')
		return;

	pcopy = new char[length+1];

	strcpy(pcopy, pstrInput);

	// ���� ������ ���� üũ
	if(pcopy[length-1] != strEndline)
	{
		delete pcopy;
		pcopy = 0;
		return;
	}
	
	// ������ ����( ';' ) ����
	length--;

	// �ʱ�ȭ
	for(i=0; i<MAX_CONTROL_PROPERTY_NUM; i++)
	{
		if(m_pstra[i] != 0)
		{
			delete m_pstra[i];
			m_pstra[i] = 0;
		}
	}

	// �ʱ�ȭ �� ������ ���� �ʱ�ȭ
	m_propertycount = 0;

	// ��� Ÿ�� ���� ����
	for(i=0; i<length; i++)
	{
	    if(pcopy[i] == strHeaderDelimiter)
		{
			break;
		}
	}

	if(i == length || i > MAX_HEADER_TYPE_LENGTH - 2)
	{
		delete pcopy;
		return;
	}

	// ���� ��ġ�� ��ü ���̸� �Ѵ��� ���ϱ� ���� ����
	// 0 <= start_pos < length  : ��ȿ ����
	// ���� ��ġ �缳��
	// ������ �ڷ� �̵� : + 1
	start_pos = i + 1;

	header_length = i;

	for(i=0; i< header_length; i++)
		m_headertype[i] = pcopy[i];

	m_headertype[i] = '\0';	

	// �����ڷ� ������ ��
	if(start_pos >= length)
	{
		delete pcopy;
		return;
	}

	for(i=start_pos; i<length; i++)
	{
	    if(pcopy[i] == strDelimiter)
		{
			break;
		}
	}

	if(i == length)
	{
		delete pcopy;
		return;
	}
    
	// ���ڿ������� ��ġ
	// nFound �� : ã�� ������ �迭������ ��ġ
	nFound = i - start_pos;

	bool loop = true;
	while(loop)
	{
		m_pstra[m_propertycount]=0;
		m_pstra[m_propertycount] = new char[nFound+1];
		/*m_pstra[m_propertycount-1] = '\0';*/
		
		// ã�� ����(������)�� ������ ���� ������
		for(i=0; i<nFound; i++)
			(m_pstra[m_propertycount])[i] = pcopy[start_pos + i];

		// 0 string terminator ����
		// ���ӵ� ������(,,,,) �̷� ��� 0 ���ڿ� ����
		(m_pstra[m_propertycount])[i] = '\0';

		m_propertycount++;

		// ���� ��ġ �缳��
		// ������ �ڷ� �̵� : + 1
		start_pos = start_pos + nFound + 1;

		// �����ڷ� ������ ��
		if(start_pos >= length)
		{
			nFound = 0;
			break;
		}
		
		// start_pos�� ���� ��ġ �缳��
		for(i=start_pos; i<length; i++)
		{
			if(pcopy[i] == strDelimiter)
			{
				break;
			}
		}

		// �� �̻� �����ڰ� ���� ��
		if(i == length)
		{
			nFound = length - start_pos;
			break;
		}

		// �������� ��� ��ġ��
		nFound = i - start_pos;
	}
	
	// ������ ������ ���� ���� ����
	m_pstra[m_propertycount]=0;
	m_pstra[m_propertycount] = new char[nFound+1];
	
	// ã�� ����(������)�� ������ ���� ������
	for(i=0; i<nFound; i++)
		(m_pstra[m_propertycount])[i] = pcopy[start_pos + i];

	// 0 string terminator ����
	// ���ӵ� ������(,,,,) �̷� ��� 0 ���ڿ� ����
	(m_pstra[m_propertycount])[i] = '\0';

	m_propertycount++;

}

int CTokenizer::GetSize(  ) const
{
	return m_propertycount;
}

// max_length : �Է� �޾ƿ� pchar �迭�� ��, '\0' ������ ������ ��
bool CTokenizer::GetAt( int nIndex, char* pchar, int max_length) const
{
	int length = 0;
	// �� control enum type�� 0���� �����ϹǷ� nIndex
	if( nIndex < GetSize() )
	{
        length = strlen(m_pstra[nIndex]);

		if(length < max_length)
		{
			strcpy(pchar, m_pstra[nIndex]);
			return true;
		}
		else
		{
			pchar[0] = '\0';
			return false;
		}
	}
	else
	{
		pchar[0] = '\0';
		return false;
	}
}

