#include "List.h"
#include "AStarNode.h"

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - CAStarList::CAStarList()
//	Desc : �� �� ��
//	Date : 2003. 07. 02
//	Update : 
//--------------------------------------------------------------------------------------------
CAStarList::CAStarList()
{
	m_pFirst = NULL;
	m_pLast = NULL;

	Initialize();
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - CAStarList::~CAStarList()
//	Desc : �� �� ��
//	Date : 2003. 07. 02
//	Update : 
//--------------------------------------------------------------------------------------------
CAStarList::~CAStarList()
{
	Destroy();
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CAStarList::Initialize()
//	Desc : �� �� ȭ
//	Date : 2003. 07. 02
//	Update : 
//--------------------------------------------------------------------------------------------
void CAStarList::Initialize()
{
	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CAStarList::Destroy()
//	Desc : ���� ó��
//	Date : 2003. 07. 02
//	Update : 
//--------------------------------------------------------------------------------------------
void CAStarList::Destroy()
{
	ListClear();
	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CAStarList::ListClear()
//	Desc : ����Ʈ ���� ���� ���� ����
//	Date : 2003. 07. 02
//	Update : 
//--------------------------------------------------------------------------------------------
void CAStarList::ListClear()
{
	CAStarNode *pTemp1 = m_pFirst;
	CAStarNode *pTemp2 = pTemp1;

	while ( pTemp1 )
	{
		pTemp1 = pTemp1->GetNextNode();
		delete pTemp2;
		pTemp2 = pTemp1;
	}
}

/*
//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CAStarList::AddNode( CAStarNode *pNode )
//	Desc : ����Ʈ�� ��� �߰�
//		   ��� �߰���� ���� �����͸� �߰��Ѵٴ� ����.
//		   ���� ��ü ������ �� �Լ��� ȣ���ϱ� ���� ��ü ���� �� �������� ���� �ڿ� ��� �߰��ϴ� ����
//	Date : 2003. 07. 02
//	Update : 
//--------------------------------------------------------------------------------------------
void CAStarList::AddNode( CAStarNode *pNode )
{
	if ( m_pFirst )
	{
		m_pLast->SetNextNode( pNode );
		m_pLast = pNode;
		m_pLast->SetNextNode( NULL );
	}
	else
	{
		m_pFirst = pNode;
		m_pLast = pNode;
		m_pLast->SetNextNode( NULL );
	}

	return;
}
*/


//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - CAStarNode* CAStarList::IsExist( unsigned int uiTileX, unsigned int uiTileY )
//	Desc : ����Ʈ�� ��尡 �����ϴ� ���� üũ
//	Date : 2003. 07. 02
//	Update : 
//--------------------------------------------------------------------------------------------
CAStarNode* CAStarList::IsExist( int uiTileX, int uiTileY )
{
	CAStarNode *pTemp = m_pFirst;

	while ( pTemp )
	{
		if ( (int)pTemp->GetTileXIndex() == uiTileX && (int)pTemp->GetTileYIndex() == uiTileY )
		{
			return pTemp;
		}
		
		pTemp = pTemp->GetNextNode();
	}

	return NULL;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - CAStarNode *CAStarList::GetFirstNode()
//	Desc : ����Ʈ ���� ���� ����� �����͸� ������.
//	Date : 2003. 07. 03
//	Update : 
//--------------------------------------------------------------------------------------------
CAStarNode *CAStarList::GetFirstNode()
{
	return m_pFirst;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CAStarList::SetFirstNode( CAStarNode * pNode )
//	Desc : ����Ʈ ���� ���� ����� �����͸� ������
//		   �ܹ��� ��ũ�� ����Ʈ�� �Ʒ��� ���� ó���ϴ� �� ���� ���� ��
//	Date : 2003. 07. 03
//	Update : 
//--------------------------------------------------------------------------------------------
void CAStarList::SetFirstNode( CAStarNode * pNode )
{
	if ( pNode == NULL )
	{
		m_pFirst = pNode;
		m_pLast = NULL;
	}
	else
	{
		//pNode->SetNextNode( m_pFirst );		
		//pNode->SetParentNode( NULL );				//9�� 17�� ����
		m_pFirst = pNode;
	}

	return;
}

// ����Ʈ ���� ���� ����� �����͸� ������.
CAStarNode *CAStarList::GetLastNode()
{
	return m_pLast;
}

// ����Ʈ ���� ���� ����� �����͸� ������
void CAStarList::SetLastNode( CAStarNode * pNode )
{
	m_pLast = pNode;
	m_pLast->SetNextNode( NULL );

	return;
}

// ����Ʈ�� ��ü�� �� �� ������...
int CAStarList::GetNodeNum()
{
	CAStarNode *pTemp = m_pFirst;

	int siNum = 0;

	while( pTemp )
	{
		++siNum;
		pTemp = pTemp->GetNextNode();
	}

	return siNum;
}