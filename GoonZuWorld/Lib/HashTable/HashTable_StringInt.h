// ============================================================================
// Data Structures For Game Programmers
// Ron Penton
// HashTable.h
// This file holds the Linekd Hash Table implementation.
// ============================================================================

 
#ifndef _HASHTABLE_STRINGINT_H_
#define _HASHTABLE_STRINGINT_H_

#include "HashTable.h"

// ============================================================================
//  Classes
// ============================================================================
class HashString
{
public:
    TCHAR m_String[64];

    // empty constructor
    HashString() 
    {
        
		_tcscpy( m_String, TEXT("") );    
    }

    // copy-string constructor
    HashString( TCHAR* pString )
    {
/*		if(pString == NULL)
		{
			SI32 b = 0;
		}
		if(lstrlen(pString) >= 64)
		{
			SI32 a = 0;
		}
		*/
        _tcscpy( m_String, pString );
    }

    // == operator
    bool operator== ( HashString& Right )
    {
        return !_tcscmp( m_String, Right.m_String);
    }
};

// ============================================================================
//  Classes
// ============================================================================

class HashData
{
public:
	int m_Data1;
	int m_Data2;
	
public:
	// constructor
	HashData()
	{
        m_Data1 = 0;
		m_Data2 = 0;
	}
	// constructor
    HashData( int Data1, int Data2)
    {
        m_Data1 = Data1;
		m_Data2 = Data2;
    }

	void GetHashDat( int &Data1, int &Data2)
	{
        Data1 = m_Data1;
		Data2 = m_Data2;
	}

    // = operator
    void operator= ( HashData& Right )
    {
		m_Data1 = Right.m_Data1;
		m_Data2 = Right.m_Data2;
    }

    // == operator
    bool operator== ( HashData& Right )
    {
		if(m_Data1 != Right.m_Data1 || m_Data2 != Right.m_Data2 ) return false;
		return true;
    }
};

// ============================================================================
//  Classes
// ============================================================================

class HashStringInt
{

public:
// ----------------------------------------------------------------
//  Name:           m_Table
//  Description:    Hash Table
// ----------------------------------------------------------------
	HashTable< HashString, HashData > *m_Table;
	
	
public:
// ----------------------------------------------------------------
//  Name:           HashStringInt
//  Description:    String�� Key�� �ϰ� Data�� �����Ҽ� �ִ� HashTable�� �����Ѵ�.
//  Arguments:      siArraySize -  The size of the table
//                  siEntrySize -  ������ ������ �ִ� Entry�� ������ �����Ѵ�.
//  Return Value:   None
// ----------------------------------------------------------------
	HashStringInt(int siArraySize, int siEntrySize)
	{
		m_Table = new HashTable< HashString, HashData >(siArraySize, siEntrySize, StringHashKeyFunc);
	}
// ----------------------------------------------------------------
//  Name:           ~HashStringInt
//  Description:    ������ HashTable�� �����Ѵ�.
//  Arguments:      None
//  Return Value:   None
// ----------------------------------------------------------------
	~HashStringInt()
	{
		if(m_Table)		delete m_Table;
	}

// ----------------------------------------------------------------
//  Name:           String Hasher
//  Description:    �־��� String���κ��� Hash ������ ����Ѵ�.
//  Arguments:      None
//  Return Value:   None
// ----------------------------------------------------------------
	static unsigned long int StringHashKeyFunc( HashString String )
	{
		unsigned long int hash = 0;
		int i;
		int length = _tcslen( String.m_String );
		for( i = 0; i < length; i++ )
		{
			hash += ( (i + 1) * (int)String.m_String[i] );
		}
		return hash;
	}
// ----------------------------------------------------------------
//  Name:           Insert
//  Description:    String�� Key������ int Data1, Data2�� �����Ѵ�.
//  Arguments:      pString - Key�� ����� ���ڿ� 
//					siData1 - ù��° Data
//					siData2 - �ι�° Data
//  Return Value:   HashTable�� �߰� �������� 
//               	(������ ���� ���� �����ϰų� �߰����н� false)
// ----------------------------------------------------------------

	bool Insert(TCHAR *pString, int siData1, int siData2)
	{
		if(Find(pString, siData1, siData2, 10) == true)	{	Remove(pString);	}
		
		HashData Data(siData1, siData2);
		return m_Table->Insert(pString, Data);
	}
	
// ----------------------------------------------------------------
//  Name:           Remove
//  Description:    �ش� Key�� ������ Entry�� ����
//  Arguments:      pString - Key�� ����� ���ڿ� 
//  Return Value:   HashTable������ ���� ��������
//               	(������ ���� ���� �������� ������ false)
// ----------------------------------------------------------------
	bool Remove(TCHAR *pString)
	{
		return m_Table->Remove(pString);
	}
	
// ----------------------------------------------------------------
//  Name:           Find
//  Description:    �ش� Key�� ������ Entry�� ����
//  Arguments:      pString - Key�� ����� ���ڿ� 
//					siData1 - ù��° Data
//					siData2 - �ι�° Data
//  Return Value:   HashTable������ �˻� ��������
//               	(������ ���� ���� �������� ������ false)
// ----------------------------------------------------------------
	bool Find(TCHAR *pString, int& Data1, int& Data2, SI32 unique)
	{
		if(pString == (TCHAR*)0xcdcdcdcd)
		{
			SI32 a = 0;
		}

		// String �� �����Ѵ�.
		HashString str( pString );
		
		// hash entry �� �����Ѵ�.
		HashEntry< HashString, HashData >* entry;
		
		// �ش� Key������ Data�� �˻��Ѵ�.
		entry = m_Table->Find( str );
		
		if( entry != 0 )
		{
			HashData Data(entry->m_Data);

			// ���� ���� Data�� �����Ѵ�.
			Data.GetHashDat(Data1, Data2);
			return true;
		}

		return false;
	}

	

};

#endif