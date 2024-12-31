// ============================================================================
// Data Structures For Game Programmers
// Ron Penton
// HashTable.h
// This file holds the Linekd Hash Table implementation.
// ============================================================================

 
#ifndef _HASHTABLE_INTINT_H_
#define _HASHTABLE_INTINT_H_

#include "HashTable.h"

// ============================================================================
//  Classes
// ============================================================================

class HashInt
{
public:
	int m_Data1;

public:
	// constructor
	HashInt()
	{
        m_Data1 = 0;
	}
	// constructor
    HashInt( int Data1)
    {
        m_Data1 = Data1;
    }

	void GetHashDat( int &Data1)
	{
        Data1 = m_Data1;
	}

    // = operator
    void operator= ( HashInt& Right )
    {
		m_Data1 = Right.m_Data1;
    }

    // == operator
    bool operator== ( HashInt& Right )
    {
		if(m_Data1 != Right.m_Data1) return false;
		return true;
    }
};

// ============================================================================
//  Classes
// ============================================================================

class HashIntInt
{

public:
// ----------------------------------------------------------------
//  Name:           m_Table
//  Description:    Hash Table
// ----------------------------------------------------------------
	HashTable< HashInt, HashInt > *m_Table;
	
	
public:
// ----------------------------------------------------------------
//  Name:           HashIntInt
//  Description:    Int�� Key(Unique�ϴ�)�� �ϰ� Data�� �����Ҽ� �ִ� HashTable�� �����Ѵ�.
//  Arguments:      siArraySize -  The size of the table
//                  siEntrySize -  ������ ������ �ִ� Entry�� ������ �����Ѵ�.
//  Return Value:   None
// ----------------------------------------------------------------
	HashIntInt(int siArraySize, int siEntrySize)
	{
		m_Table = new HashTable< HashInt, HashInt >(siArraySize, siEntrySize, IntHashKeyFunc);
	}
// ----------------------------------------------------------------
//  Name:           ~HashIntInt
//  Description:    ������ HashTable�� �����Ѵ�.
//  Arguments:      None
//  Return Value:   None
// ----------------------------------------------------------------
	~HashIntInt()
	{
		if(m_Table)		delete m_Table;
	}

// ----------------------------------------------------------------
//  Name:           String Hasher
//  Description:    �־��� Int�� �׳� Hash Key�� ����Ѵ�.
//  Arguments:      None
//  Return Value:   None
// ----------------------------------------------------------------
	static unsigned long int IntHashKeyFunc( HashInt IntKey )
	{
		return IntKey.m_Data1;
	}
// ----------------------------------------------------------------
//  Name:           Insert
//  Description:    String�� Key������ int Data1, Data2�� �����Ѵ�.
//  Arguments:      Key     - Key�� ����� Int
//					siData1 - ù��° Data
//  Return Value:   HashTable�� �߰� �������� 
//               	(������ ���� ���� �����ϰų� �߰����н� false)
// ----------------------------------------------------------------

	bool Insert(int Key, int siData1)
	{
		if(Find(Key, siData1) == true) 	{	Remove(Key);	} 
		
		HashInt Data(siData1);
		return m_Table->Insert(Key, Data);
	}
	
// ----------------------------------------------------------------
//  Name:           Remove
//  Description:    �ش� Key�� ������ Entry�� ����
//  Arguments:      Key     - Key�� ����� Int
//  Return Value:   HashTable������ ���� ��������
//               	(������ ���� ���� �������� ������ false)
// ----------------------------------------------------------------
	bool Remove(int Key)
	{
		return m_Table->Remove(Key);
	}
	
// ----------------------------------------------------------------
//  Name:           Find
//  Description:    �ش� Key�� ������ Entry�� ����
//  Arguments:      Key		- Key�� ����� ���ڿ� 
//					siData1 - ù��° Data
//  Return Value:   HashTable������ �˻� ��������
//               	(������ ���� ���� �������� ������ false)
// ----------------------------------------------------------------
	bool Find(int Key, int& Data1)
	{
		HashInt HashKey(Key);
		
		// hash entry �� �����Ѵ�.
		HashEntry< HashInt, HashInt >* entry;
		
		// �ش� Key������ Data�� �˻��Ѵ�.
		entry = m_Table->Find( HashKey );
		
		if( entry != 0 )
		{
			HashInt Data(entry->m_Data);

			// ���� ���� Data�� �����Ѵ�.
			Data.GetHashDat(Data1);
			return true;
		}

		return false;
	}

	

};

#endif