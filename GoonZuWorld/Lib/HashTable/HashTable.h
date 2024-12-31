// ============================================================================
// Data Structures For Game Programmers
// Ron Penton
// HashTable.h
// This file holds the Linekd Hash Table implementation.
// ============================================================================

 
#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include "Array.h"
#include "DLinkedList.h"
#include "MLinkedList.h"


// -------------------------------------------------------
// Name:        HashEntry
// Description: Hash Table Entry Class
//              Key�� Data�� ������ �����Ѵ�.
// -------------------------------------------------------
template< class KeyType, class DataType>
class HashEntry
{
public:
    KeyType		m_Key;
    DataType	m_Data;
};



// -------------------------------------------------------
// Name:        HashTable
// Description: Hashtable Class.
// -------------------------------------------------------
template< class KeyType, class DataType>
class HashTable
{

	// typedef the entry class 
    typedef HashEntry<KeyType, DataType> Entry;

public:    
// ----------------------------------------------------------------
//  Name:           m_ArraySize
//  Description:    table�� ũ�� 
// ----------------------------------------------------------------
    int m_siArraySize;

// ----------------------------------------------------------------
//  Name:           m_EntrySize
//  Description:    Entry Node�� ũ�� 
// ----------------------------------------------------------------
    int m_siEntrySize;

// ----------------------------------------------------------------
//  Name:           m_TableEntryCount
//  Description:    Table�� �����ִ� Entry�� Count
// ----------------------------------------------------------------
    int m_siTableEntryCount;

// ----------------------------------------------------------------
//  Name:           m_ArrayTable
//  Description:    Entry�� Linked List�� �����ִ� ArrayTable
// ----------------------------------------------------------------
    Array< DLinkedList< Entry > >		m_ArrayTable;

// ----------------------------------------------------------------
//  Name:           m_EntryList
//  Description:    ���� Entry Node�� �޸𸮸� �����ϴ� Table
// ----------------------------------------------------------------
	MLinkedList< Entry >				m_EntryList;

// ----------------------------------------------------------------
//  Name:           m_HashFunc
//  Description:    Hash function Pointer
// ----------------------------------------------------------------
    unsigned long int (*m_HashFunc)(KeyType);


public:

// ----------------------------------------------------------------
//  Name:           HashTable
//  Description:    HashTable�� �����ϱ����� �ʱ�ȭ�� �����Ѵ�.
//  Arguments:      ArraySize - Table Array�� ũ��
//                  EntrySize - Node�� ũ��
//                  HashFunc  - Hashing Function.
//  Return Value:   None
// ----------------------------------------------------------------
    HashTable( int ArraySize, int EntrySize, unsigned long int (*HashFunc)(KeyType) )
        : m_ArrayTable( ArraySize ) , m_EntryList(EntrySize)
    {
        // set the size, hash function, and count.
        m_siArraySize		= ArraySize;
        m_HashFunc			= HashFunc;
		m_siEntrySize		= EntrySize;
        m_siTableEntryCount	= 0;

    }

// ----------------------------------------------------------------
//  Name:           HashTableIndex
//  Description:    Key������ ArrayTable index�� ���´�. 
//  Arguments:      Key  - key
//  Return Value:   Table Index
// ----------------------------------------------------------------
	inline int HashTableIndex(KeyType Key)
	{
		return m_HashFunc( Key ) % m_siArraySize;
	}
	

// ----------------------------------------------------------------
//  Name:           Insert
//  Description:    Table�� Key�� Data�� ������ �߰��Ѵ�.
//  Arguments:      Key  - the key
//                  Data - Key�� �ΰ��Ǵ� Data
//  Return Value:   None
// ----------------------------------------------------------------
    bool Insert( KeyType Key, DataType Data)
    {
        // Entry �� �����ϰ� ���� �����Ѵ�.
        Entry entry;
        entry.m_Key		= Key;
        entry.m_Data	= Data;

		// Key���� Hash Value�� ���� �̸� Table�� ũ��� 
		// �������� ����Ͽ� Table index�� ���Ѵ�.
		int index = HashTableIndex(Key);		

		// �ش� Index�� Entry�� �����Ѵ�.
        bool bsuccess = m_ArrayTable[index].Append( entry , m_EntryList.Pop());
		if(bsuccess)	m_siTableEntryCount++;

		return bsuccess;
    }

// ----------------------------------------------------------------
//  Name:           Find
//  Description:    Table���� Key������ Entry�� �˻��Ѵ�.
//  Arguments:      Key - �˻��� ���� Key
//  Return Value:   Entry Pointer�� �����ش�.
// ----------------------------------------------------------------
    Entry* Find( KeyType Key )
    {
		// Key�� ����Ͽ� Table index�� ���´�.
        int index = HashTableIndex(Key);		

        // Iterator�� ����Ͽ� List�� Head�� ���´�.
        DListIterator<Entry> itr = m_ArrayTable[index].GetIterator();

        // �� Item�� Valid���� �˻��Ͽ� ���ϴ� Key�� ã���� �˻��Ѵ�.
        while( itr.Valid() )
        {
			// ���ϴ� key�� ã������ �ش� Entry�� Pointer�� �����ش�.
            if( itr.Item().m_Key == Key )	return &(itr.Item());
            itr.Forth();
        }

		// ã�����ϸ� NULL�� �����ش�.
        return 0;
    }

 
// ----------------------------------------------------------------
//  Name:           Remove
//  Description:    Key �� ����Ͽ� �ش� Entry�� �����Ѵ�.
//  Arguments:      Key - key
//  Return Value:   ���ſ� �����ϸ� true
// ----------------------------------------------------------------
    bool Remove( KeyType Key )
    {
		// Key�� �ش� Index�� ����Ѵ�.
        int index = HashTableIndex(Key);	

		// Iterator�� ����Ͽ� List�� Head�� ���´�.
        DListIterator<Entry> itr = m_ArrayTable[index].GetIterator();

        // �� Item�� Valid���� �˻��Ͽ� ���ϴ� Key�� ã���� �˻��Ѵ�.
        while( itr.Valid() )
        {
            // ���ϴ� key�� ã������ �ش� Entry�� �����ϰ� �޸𸮸� �����ش�.
            if( itr.Item().m_Key == Key )
            {
				m_EntryList.Push(m_ArrayTable[index].Remove(itr));
                m_siTableEntryCount--;
                return true;
            }
            itr.Forth();
        }

        // ã�����ϸ� NULL�� �����ش�.
        return false;
    }


// ----------------------------------------------------------------
//  Name:           Count
//  Description:    Table�� �Ҵ�Ǿ��� ���ǰ� �ִ� Entry������ ���´�.
//  Arguments:      None
//  Return Value:   Table�� �Ҵ�Ǿ��ִ� Entry����
// ----------------------------------------------------------------
    int Count()
    {
        return m_siTableEntryCount;
    }

};


#endif

