//-----------------------------------------------------------------------------
// 2005/09/13 ������
//-----------------------------------------------------------------------------

#ifndef _NHASHTABLESTRING_H
#define _NHASHTABLESTRING_H

#include "NList.h"
#include "NHashTable.h"

//-----------------------------------------------------------------------------
// NHashTableString
//
//
//       NArray( ��Ʈ�� ����Ʈ�� �迭 )
// 
//         0(��Ʈ�� ����Ʈ)
//         1       -  A  -  B  -  C(��Ʈ��)
//         2       -  D
//         3       -  E  -  F
//         4
//         .
//         .
//   (arraySize - 1)
//
//
//       NListPool  
//         list    -  G  -  H  -  I  - ...  (��Ʈ���� ��� �ִ� ����Ʈ Ǯ)
//
//-----------------------------------------------------------------------------

template< class DataType >
class NHashTableString
{
public:
	typedef NHashEntry< TCHAR*, DataType >	Entry;
	typedef NList< Entry >					EntryList;

	NHashTableString();
	~NHashTableString();

	void			CreateHashTableString( int arraySize, int maxEntryNumber, int maxStrSize );

	inline int		GetArraySize() { return m_iArraySize; }

	inline int		GetListPoolLeftNode() { return m_listpool.GetListNodeNumber(); }

	inline int		GetHashTableIndex( TCHAR *key ) { return HashFunc( key ) % m_iArraySize; }

	bool			Insert( TCHAR *key, DataType data );
	bool			Remove( TCHAR *key );

	bool			Find( TCHAR *key, DataType &data );
	DataType*		Find( TCHAR *key );


protected:
	unsigned int	HashFunc( TCHAR *key );

	NListPool< Entry >			m_listpool;						// �ؽ� ��Ʈ���� ����Ʈ Ǯ
	NArray< EntryList >			m_array;						// �ؽ� ��Ʈ�� ����Ʈ�� �迭

	NStringArray				m_stringArray;					// ��Ʈ�� ������

	int							m_iArraySize;					// �迭 ������

	int							m_iMaxKeyStrSize;

};

template< class DataType >
NHashTableString< DataType >::NHashTableString()
{
	m_iArraySize = 0;
	m_iMaxKeyStrSize = 0;
}

template< class DataType >
NHashTableString< DataType >::~NHashTableString()
{
}

template< class DataType >
void NHashTableString< DataType >::CreateHashTableString( int arraySize, int maxEntryNumber, int maxStrSize )
{

	m_listpool.CreateListPool( maxEntryNumber );
	m_array.CreateArray( arraySize );

	m_stringArray.CreateStringArray( maxEntryNumber, maxStrSize );

	// ����Ʈ Ǯ�� �ִ� Entry�� char*�� stringArray�� �����͸� �����Ѵ� 
	int i;
	Entry *pEntry;

	for( i = 0; i < maxEntryNumber; ++i )
	{
		pEntry = m_listpool.GetDataPtr( i );
		pEntry->m_key = m_stringArray.GetElement( i );
	}

	// �� list ���� 
	EntryList *pList;

	for( i = 0; i < arraySize; ++i ) 
	{
		pList = m_array.GetElementPtr( i );

		pList->CreateList( &m_listpool );
	}

	m_iArraySize = arraySize;

	m_iMaxKeyStrSize = maxStrSize;
}

template< class DataType >
unsigned int NHashTableString< DataType >::HashFunc( TCHAR *key )
{

	unsigned int hash, i;

	hash = 0;
	i = 1;

	while( *key )
	{
		hash += ( i * (unsigned int)*key );
		++i;
		++key;
	}

	return hash;
}

template< class DataType >
bool NHashTableString< DataType >::Insert( TCHAR *key, DataType data )
{
	if( *key == NULL ) return false;

	int index = GetHashTableIndex( key );

	EntryList* pList = m_array.GetElementPtr( index );

	NListNode< Entry > *pNode;
	Entry *pEntry;

	// ������ Key�� �̹� �ִ��� üũ
	pNode = pList->GetFirst();

	while( pNode )
	{
		if( _tcscmp( pNode->GetDataPtr()->m_key, key ) == 0 ) 
		{
			pNode->GetDataPtr()->m_data = data;
			return true;
		}

		pNode = pNode->GetNext();
	}

	pNode = pList->PushBack();

	if( pNode == NULL ) return false;

	pEntry = pNode->GetDataPtr();

	StringCchCopy( pEntry->m_key, m_iMaxKeyStrSize, key );
	pEntry->m_data = data;

	return true;
}


template< class DataType >
bool NHashTableString< DataType >::Remove( TCHAR *key )
{
	if( *key == NULL ) return false;

	int index = GetHashTableIndex( key );

	EntryList* pList = m_array.GetElementPtr( index );

	NListNode< Entry > *pNode;

	pNode = pList->GetFirst();

	while( pNode )
	{
		if( _tcscmp( pNode->GetDataPtr()->m_key, key ) == 0 ) {

			pList->Remove( pNode );
			return true;
		}

		pNode = pNode->GetNext();
	}

	return false;
}

template< class DataType >
bool NHashTableString< DataType >::Find( TCHAR *key, DataType &data )
{
	if( *key == NULL ) return false;

	int index = GetHashTableIndex( key );

	EntryList* pList = m_array.GetElementPtr( index );

	NListNode< Entry > *pNode;

	pNode = pList->GetFirst();

	while( pNode )
	{
		if( _tcscmp( pNode->GetDataPtr()->m_key, key ) == 0 ) {

			data = pNode->GetDataPtr()->m_data; 

			return true;
		}

		pNode = pNode->GetNext();
	}

	return false;
}

template< class DataType >
DataType* NHashTableString< DataType >::Find( TCHAR *key )
{
	if( *key == NULL ) return NULL;

	int index = GetHashTableIndex( key );

	EntryList* pList = m_array.GetElementPtr( index );

	NListNode< Entry > *pNode;

	pNode = pList->GetFirst();

	while( pNode )
	{

		if( _tcscmp( pNode->GetDataPtr()->m_key, key ) == 0 ) {

			return &pNode->GetDataPtr()->m_data; 
		}

		pNode = pNode->GetNext();
	}

	return NULL;
}

#endif