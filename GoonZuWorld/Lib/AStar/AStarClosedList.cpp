#include "AStarClosedList.h"
#include "AStarNode.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAStarClosedList::CAStarClosedList() : CAStarList()
{	
	Initialize();
}

CAStarClosedList::~CAStarClosedList()
{
	Destroy();
}

void CAStarClosedList::Initialize()
{	
	return;
}

void CAStarClosedList::Destroy()
{
	CAStarNode *pTemp;

	while ( pTemp = Pop() )
	{
		delete pTemp;
	}

	return;
}

// �ϳ� ������ ��
CAStarNode *CAStarClosedList::Pop()
{
	CAStarNode *pTemp = GetFirstNode();

	if ( pTemp )
	{
		SetFirstNode( pTemp->GetNextNode() );

		pTemp->SetNextNode( NULL );
	}

	return pTemp;
}