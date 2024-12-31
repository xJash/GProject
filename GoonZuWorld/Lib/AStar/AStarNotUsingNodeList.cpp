#include "AStarNotUsingNodeList.h"
#include "AStarNode.h"

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - CAStarNotUsingNodeList::CAStarNotUsingNodeList()
//	Desc : �� �� ��
//	Date : 2003. 07. 02
//	Update : 
//--------------------------------------------------------------------------------------------
CAStarNotUsingNodeList::CAStarNotUsingNodeList( int Max_Node_Num )
{	
	m_pFirst = NULL;
	m_pLast = NULL;

	CAStarNode *pTemp = NULL;
	CAStarNode *pTemp1 = m_pFirst;

	for ( int i = 0; i < Max_Node_Num; ++ i )
	{		
		pTemp = new CAStarNode();

		AddNode( pTemp );
	}


	Initialize();
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - CAStarNotUsingNodeList::~CAStarNotUsingNodeList()
//	Desc : �� �� ��
//	Date : 2003. 07. 02
//	Update : 
//--------------------------------------------------------------------------------------------
CAStarNotUsingNodeList::~CAStarNotUsingNodeList()
{
	Destroy();
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CAStarNotUsingNodeList::Initialize()
//	Desc : �� �� ȭ
//	Date : 2003. 07. 02
//	Update : 
//--------------------------------------------------------------------------------------------
void CAStarNotUsingNodeList::Initialize()
{	
	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CList::AddNode( CAStarNode *pNode )
//	Desc : ���� ó��
//	Date : 2003. 07. 02
//	Update : 
//--------------------------------------------------------------------------------------------
void CAStarNotUsingNodeList::Destroy()
{
	CAStarNode *pTemp = GetLastNodeAndMoveLastPtr();

	while( pTemp )
	{
		delete pTemp;
		pTemp = GetLastNodeAndMoveLastPtr();
	}

	m_pFirst = NULL;
	m_pLast = NULL;

	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CAStarNotUsingNodeList::AddNode( CAStarNode *pNode )
//	Desc : ��� �ڿ� �߰�
//	Date : 2003. 07. 02
//	Update : 
//--------------------------------------------------------------------------------------------
void CAStarNotUsingNodeList::AddNode( CAStarNode *pNode )
{
	if ( m_pFirst )
	{
		m_pLast->SetEmptyNext( pNode );
		pNode->SetEmptyPre( m_pLast );
		m_pLast = pNode;
		m_pLast->SetEmptyNext( NULL );
	}
	else
	{
		m_pFirst = pNode;
		m_pLast = pNode;
	}

	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CAStarNotUsingNodeList::DelNode( CAStarNode *pNode )
//	Desc : ��� ��ũ ������
//	Date : 2003. 07. 02
//	Update : 
//--------------------------------------------------------------------------------------------
void CAStarNotUsingNodeList::DelNode( CAStarNode *pNode )
{
	if ( pNode->GetEmptyPre() == NULL )
	{
		m_pFirst = m_pFirst->GetEmptyNext();
	}
	else if ( pNode->GetEmptyNext() == NULL )
	{
		m_pLast = m_pLast->GetEmptyPre();
	}
	else
	{
		pNode->GetEmptyPre()->SetEmptyNext( pNode->GetEmptyNext() );
		pNode->GetEmptyNext()->SetEmptyPre( pNode->GetEmptyPre() );
	}

	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - CAStarNode *CAStarNotUsingNodeList::GetLastNodeAndMoveLastPtr()
//	Desc : �������� �ִ� ��带 ������ �ְ�, ������ ��带 �� ������ �Ű���
//	Date : 2003. 07. 02
//	Update : 
//--------------------------------------------------------------------------------------------
CAStarNode *CAStarNotUsingNodeList::GetLastNodeAndMoveLastPtr()
{
	if ( m_pLast == NULL )
	{
		return NULL;
	}

	CAStarNode *pTemp = m_pLast;
	m_pLast = m_pLast->GetEmptyPre();

	if ( m_pLast )
	{
		m_pLast->SetEmptyNext( NULL );
	}
	else
	{
		m_pFirst = NULL;
	}

	pTemp->Initialize();

	return pTemp;
}

int CAStarNotUsingNodeList::GetNodeNum()
{
	CAStarNode *pTemp = m_pFirst;

	int siNum = 0;

	while( pTemp )
	{
		++siNum;
		pTemp = pTemp->GetEmptyNext();
	}

	return siNum;
}