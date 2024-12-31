//-----------------------------------------------------------------------------
// 2005/09/13 이제완
//-----------------------------------------------------------------------------

#ifndef _NLIST_H
#define _NLIST_H

#include "NArray.h"

template< class Type >
class NList;

template< class Type >
class NListPool;

//-----------------------------------------------------------------------------
//
// POOL방식의 리스트이다 
//
// 기본적으로 생성은 NListPool을 통해서 된다.
// 
//  NListPool :     A  <->  B  <->  C  <->  D 
//                  0       1       2       3 (배열인덱스)
//
// 
//
//
//
// 각 노드는 기본적인 리스트 노드로써 전,후 노드의 포인터 뿐만아니라 배열에서의 고유 인덱스를 가진다. 
// 이는 노드를 생성한 
//-----------------------------------------------------------------------------
template< class Type >
class NListNode
{
public:
	friend class NList;
	friend class NListPool;

	NListNode() : m_pListPool(0), m_index(0), m_pPrev(0), m_pNext(0), m_pList(0) {}
	~NListNode() {}

	inline NListPool< Type >*	GetListPool() { return m_pListPool; }
	inline int					GetIndex() { return m_index; }

	inline NListNode< Type >*	GetPrev() { return m_pPrev; }
	inline NListNode< Type >*	GetNext() { return m_pNext; }

	inline NList< Type >*		GetList() { return m_pList; }

	inline Type&				GetData() { return m_data; }
	inline Type*				GetDataPtr() { return &m_data; }

	inline void					Remove() { m_pList->Remove( this ); }

private:
	NListPool< Type >*			m_pListPool;		// 자신을 생성한 리스트 풀
	int							m_index;			// 리스트 풀에서 직접 접근 가능한 자신의 인덱스

	NListNode< Type >*			m_pPrev;			// 이전 노드 포인터
	NListNode< Type >*			m_pNext;			// 다음 노드 포인터

	NList< Type >*				m_pList;			// 현재 자신을 관리하고 있는 리스트

	Type						m_data;
};


//-----------------------------------------------------------------------------
// NListPool
//-----------------------------------------------------------------------------
template< class Type >
class NListPool
{
public:
	friend class NList;

	NListPool( int maxSize ) { CreateListPool( maxSize ); }
	
	NListPool() {}
	~NListPool() {}

	void CreateListPool( int maxSize )
	{
		m_array.CreateArray( maxSize );				// 노드 배열 생성

		NListNode< Type > *pNode;

		for( int i = 0; i < maxSize; ++i )
		{
			pNode = m_array.GetElementPtr( i );		// 배열에서 노드 얻어오기
			
			pNode->m_pListPool = this;				// 자신을 생성한 리스트 풀 설정 (this)
			pNode->m_index = i;						// 리스트 풀에서 배열 인덱스 설정 

			m_list.PushBack( pNode );				// 리스트에 추가
		}
	}

	inline int GetMaxSize()							// 총 노드 개수 얻어오기
	{ 
		return m_array.GetMaxSize(); 
	}

	inline NListNode< Type >& GetNode( int i )		// 특정 인덱스의 노드 얻어오기 (레퍼런스)
	{
		return m_array.GetElement( i );
	}

	inline NListNode< Type >* GetNodePtr( int i )	// 특정 인덱스의 노드 얻어오기 (포인터)
	{ 
		return m_array.GetElementPtr( i ); 
	}

	inline Type& GetData( int i )					// 특정 인덱스의 노드에 있는 데이터 얻어오기 (레퍼런스)
	{ 
		return m_array.GetElement( i ).GetData(); 
	}

	inline Type* GetDataPtr( int i )				// 특정 인덱스의 노드에 있는 데이터 얻어오기 (포인터)
	{ 
		return m_array.GetElement( i ).GetDataPtr(); 
	}

	inline bool IsValidIndex( int i )				// 인덱스 값이 유효한지 여부를 반환
	{
		return ( i >= 0 && i < m_array.GetMaxSize() );
	}

	inline int	GetListNodeNumber( )
	{
		return m_list.m_siCount;
	}
	
private:
	NArray< NListNode< Type > >		m_array;
	NList< Type >					m_list;
	
};

//-----------------------------------------------------------------------------
// NList
//-----------------------------------------------------------------------------
template< class Type >
class NList
{
public:
	friend class NListPool;

	NList();
	NList( NListPool< Type > *pListPool );
	NList( int listPoolSize );

	~NList();

	void		CreateList( NListPool< Type > *pListPool );
	void		CreateList( int listPoolSize );						// self ListPool

	void		Destroy();

	inline NListNode< Type >*	GetFirst() { return m_pFirst; }
	inline NListNode< Type >*	GetLast() { return m_pLast; }

	inline int					GetCount() { return m_siCount; }

	Type*						PushFrontGetData();
	Type*						PushBackGetData();

	Type*						RemoveFrontGetData();
	Type*						RemoveBackGetData();

	NListNode< Type >*			PushFront();
	NListNode< Type >*			PushBack();

	NListNode< Type >*			RemoveFront();
	NListNode< Type >*			RemoveBack();

	NListNode< Type >*			Remove( NListNode< Type > *pNode );

	NListNode< Type >*			Find( Type data );

private:
	NListNode< Type >*			PushFront( NListNode< Type > *pNode );
	NListNode< Type >*			PushBack( NListNode< Type > *pNode );

	NListNode< Type >*			PopFront();
	NListNode< Type >*			PopBack();


private:
	NListPool< Type >*			m_pListPool;

	NListNode< Type >*			m_pFirst;
	NListNode< Type >*			m_pLast;

	int							m_siCount;

	bool						m_bSelfListPool;
};


//-----------------------------------------------------------------------------
// NList
//-----------------------------------------------------------------------------
template< class Type >
NList< Type >::NList()
{
	m_pListPool = NULL;
	
	m_pFirst = NULL;
	m_pLast = NULL;

	m_siCount = 0;

	m_bSelfListPool = FALSE;
}

template< class Type >
NList< Type >::NList( NListPool< Type > *pListPool )
{
	m_pListPool = pListPool;
	
	m_pFirst = NULL;
	m_pLast = NULL;

	m_siCount = 0;	

	m_bSelfListPool = FALSE;
}

template< class Type >
NList< Type >::NList( int listPoolSize )
{
	m_pFirst = NULL;
	m_pLast = NULL;

	m_siCount = 0;	

	m_pListPool = new NListPool< Type >
	m_pListPool->CreateListPool( listPoolSize );

	m_bSelfListPool = TRUE;
}

template< class Type >
NList< Type >::~NList()
{
	Destroy();
}

template< class Type >
void NList< Type >::Destroy()
{
	NListNode< Type > *pNode, *pTemp;

	pNode = m_pFirst;

	while( pNode ) 
	{
		pTemp = pNode;
		pNode = pNode->GetNext();

		Remove( pTemp );
	}

	if( m_bSelfListPool && m_pListPool )
	{
		delete m_pListPool;
	}
	
	m_pListPool = NULL;
	m_bSelfListPool = FALSE;

	m_pFirst = NULL;
	m_pLast = NULL;

	m_siCount = 0;
}

template< class Type >
void NList< Type >::CreateList( NListPool< Type > *pListPool )
{
	Destroy();

	m_pListPool = pListPool;
}

template< class Type >
void NList< Type >::CreateList( int listPoolSize )
{
	Destroy();

	m_pListPool = new NListPool< Type >;
	m_pListPool->CreateListPool( listPoolSize );

	m_bSelfListPool = TRUE;
}


//-----------------------------------------------------------------------------
// 리스트 풀에서 노드를 꺼내와서 리스트 앞에 삽입하고,
// 노드의 데이터 포인터를 반환한다
// 리스트 풀에 가져올 수 있는 노드가 없다면 NULL을 반환한다
//-----------------------------------------------------------------------------
template< class Type >
inline Type* NList< Type >::PushFrontGetData()
{
	NListNode< Type > *pNode;	
	
	pNode = PushFront( m_pListPool->m_list.PopFront() );

	if( pNode ) return &pNode->m_data;

	return NULL;
}

//-----------------------------------------------------------------------------
// 리스트 풀에서 노드를 꺼내와서 리스트 뒤에 삽입하고,
// 노드의 데이터 포인터를 반환한다
// 리스트 풀에 가져올 수 있는 노드가 없다면 NULL을 반환한다
//-----------------------------------------------------------------------------
template< class Type >
inline Type* NList< Type >::PushBackGetData()
{
	NListNode< Type > *pNode;	
	
	pNode = PushBack( m_pListPool->m_list.PopFront() );

	if( pNode ) return &pNode->m_data;

	return NULL;
}

//-----------------------------------------------------------------------------
// 리스트 풀에서 노드를 꺼내와서 리스트 뒤에 삽입하고,
// 노드의 데이터 포인터를 반환한다
// 리스트 풀에 가져올 수 있는 노드가 없다면 NULL을 반환한다
//-----------------------------------------------------------------------------
template< class Type >
inline Type* NList< Type >::RemoveFrontGetData()
{
	NListNode< Type > *pNode;

	pNode = PopFront();

	if( pNode == NULL ) return NULL;

	pNode = pNode->m_pListPool->m_list.PushBack( pNode );

	if( pNode == NULL ) return NULL;
		
	return &pNode->m_data;
}

template< class Type >
inline Type* NList< Type >::RemoveBackGetData()
{
	NListNode< Type > *pNode;

	pNode = PopBack();

	if( pNode == NULL ) return NULL;

	pNode = m_pListPool->m_list.PushBack( pNode );

	if( pNode == NULL ) return NULL;
		
	return &pNode->m_data;
}

//-----------------------------------------------------------------------------
// 리스트 풀에서 노드를 꺼내와서 리스트 뒤에 삽입하고, 노드 포인터를 반환한다
// 리스트 풀에서 가져올 수 있는 노드가 없다면 NULL을 반환한다
//-----------------------------------------------------------------------------
template< class Type >
inline NListNode< Type >* NList< Type >::PushFront()
{
	return PushFront( m_pListPool->m_list.PopFront() );
}

template< class Type >
inline NListNode< Type >* NList< Type >::PushBack()
{
	 return PushBack( m_pListPool->m_list.PopFront() );
}

template< class Type >
inline NListNode< Type >* NList< Type >::RemoveFront()
{
	NListNode< Type > *pNode = PopFront();

	if( pNode == NULL ) return NULL;

	return pNode->m_pListPool->m_list.PushBack( pNode );
}

template< class Type >
inline NListNode< Type >* NList< Type >::RemoveBack()
{	
	NListNode< Type > *pNode = PopBack();

	if( pNode == NULL ) return NULL;

	return pNode->m_pListPool->m_list.PushBack( pNode );
}


//-----------------------------------------------------------------------------
// 리스트에서 주어진 노드를 삭제 한다
// 노드의 소속 리스트 포인터가 this와 같지 않다면 NULL을 반환한다
//-----------------------------------------------------------------------------
template< class Type >
NListNode< Type >* NList< Type >::Remove( NListNode<Type> *pNode )
{
	if( pNode->m_pList == &pNode->m_pListPool->m_list ) return NULL;

	if( pNode->m_pList != this ) return NULL;

	if( pNode == m_pFirst ) {

		m_pFirst = pNode->m_pNext;

	} else {

		pNode->m_pPrev->m_pNext = pNode->m_pNext;
	}

	if( pNode == m_pLast ) {

		m_pLast = pNode->m_pPrev;

	} else {

		pNode->m_pNext->m_pPrev = pNode->m_pPrev;
	}

	m_siCount--;

	pNode->m_pListPool->m_list.PushBack( pNode );

	return pNode;
}

template< class Type >
inline NListNode< Type >* NList< Type >::Find( Type data )
{

	NListNode< Type > *pNode = m_pFirst;

	while( pNode )
	{
		if( pNode->m_data == data ) return pNode;

		pNode = pNode->m_pNext;
	}

	return NULL;
}


//-----------------------------------------------------------------------------
// 리스트 첫번째 노드 앞에 주어진 노드를 삽입한다
// 인수를 반환한다.
//-----------------------------------------------------------------------------
template< class Type >
NListNode< Type >* NList< Type >::PushFront( NListNode< Type > *pNode )
{

	if( pNode == NULL ) return NULL;

	pNode->m_pList = this;

	if( m_siCount == 0 ) {

		pNode->m_pPrev = NULL;
		pNode->m_pNext = NULL;

		m_pFirst = m_pLast = pNode;

	} else {

		pNode->m_pPrev = NULL;
		pNode->m_pNext = m_pFirst;

		m_pFirst->m_pPrev = pNode;
 
		m_pFirst = pNode;

	}

	m_siCount++;

	return pNode;
}

//-----------------------------------------------------------------------------
// 리스트 마지막 노드 뒤에 주어진 노드를 삽입한다
// 인수를 반환한다.
//-----------------------------------------------------------------------------
template< class Type >
NListNode< Type >* NList< Type >::PushBack( NListNode< Type > *pNode )
{

	if( pNode == NULL ) return NULL;

	pNode->m_pList = this;

	if( m_siCount == 0 ) {

		pNode->m_pPrev = NULL;
		pNode->m_pNext = NULL;

		m_pFirst = m_pLast = pNode;

	} else {

		pNode->m_pNext = NULL;
		pNode->m_pPrev = m_pLast;

		m_pLast->m_pNext = pNode;

		m_pLast = pNode;

	}	

	m_siCount++;

	return pNode;
}


//-----------------------------------------------------------------------------
// 리스트에서 첫번째 노드를 꺼낸다
// 노드의 소속 리스트 포인터는 NULL이 된다
// 리스트에 노드가 하나도 없으면 NULL을 반환한다
//-----------------------------------------------------------------------------
template< class Type >
NListNode< Type >* NList< Type >::PopFront()
{
	
	NListNode< Type > *pNode;

	if( m_siCount == 0 ) return NULL;		
	
	m_siCount--;

	pNode = m_pFirst;
	pNode->m_pList = NULL;

	if( m_siCount == 0 ) {
		
		m_pFirst = NULL;
		m_pLast = NULL;

		return pNode;
	}

	m_pFirst = pNode->m_pNext;
	m_pFirst->m_pPrev = NULL;

	

	return pNode;
}

//-----------------------------------------------------------------------------
// 리스트에서 마지막 노드를 꺼낸다
// 노드의 소속 리스트 포인터는 NULL이 된다
// 리스트에 노드가 하나도 없으면 NULL을 반환한다
//-----------------------------------------------------------------------------
template< class Type >
NListNode< Type >* NList< Type >::PopBack()
{

	NListNode< Type > *pNode;

	if( m_siCount == 0 ) return NULL;		

	m_siCount--;

	pNode = m_pLast;

	pNode->m_pList = NULL;

	if( m_siCount == 0 ) {		
		
		m_pFirst = NULL;
		m_pLast = NULL;

		return pNode;
	}

	m_pLast = pNode->m_pPrev;
	m_pLast->m_pNext = NULL;
	
	return pNode;
}


#endif