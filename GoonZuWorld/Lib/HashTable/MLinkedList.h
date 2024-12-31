// ============================================================================
// Data Structures For Game Programmers
// Jaycee
// SLinkedList.h
// This is the Single-Linked List class
// ============================================================================
#ifndef _MLINKEDLIST_H_
#define _MLINKEDLIST_H_

#include "HashTable.h"

// -------------------------------------------------------
// Name:        UseFreeList
// Description: This is the Single-linked list node class.
// -------------------------------------------------------
template<class Datatype>
class MLinkedList
{
private:
// ----------------------------------------------------------------
//  Name:           m_Free
//  Description:    ���� ����Ҽ��ִ� Free nodes
// ----------------------------------------------------------------
    DLinkedList<Datatype>	m_Free;

// ----------------------------------------------------------------
//  Name:           m_pData
//  Description:    �̸��Ҵ��� ��� Node�� �迭 Pointer
// ----------------------------------------------------------------

	DListNode<Datatype>*	m_pData;

// ----------------------------------------------------------------
//  Name:           m_siCount
//  Description:    �޸𸮷� �Ҵ��� Node�� Count 
// ----------------------------------------------------------------
    int m_siCount;

// ----------------------------------------------------------------
//  Name:           m_siFreeCount
//  Description:    ���� ���� �Ҵ��Ҽ� �ִ� �����ִ� Node Count
// ----------------------------------------------------------------
	int m_siFreeCount;

// ----------------------------------------------------------------
//  Name:           m_siUsedCount
//  Description:    �̹� �Ҵ��Ͽ� ����ϰ� �ִ� Node Count
// ----------------------------------------------------------------
	int m_siUsedCount;

public:


// ----------------------------------------------------------------
//  Name:           MLinkedList
//  Description:    Node�� �Ҵ��ϰ� �������� �ʱ�ȭ�Ѵ�.
//  Arguments:      count - ���� ������ Node�� ����
//  Return Value:   None.
// ----------------------------------------------------------------
    MLinkedList(int size)
    {
		m_siCount	  = 0;
		m_siFreeCount = 0;
		m_siUsedCount = 0;

		m_pData = new DListNode<Datatype>[size];
		
		if(m_pData)
		{
			m_siCount	  = size;
			m_siFreeCount = size;
			m_siUsedCount = 0;
		}


		Datatype tempdata;
		for(int i= 0; i < m_siCount; ++i)
		{
			m_Free.Append(tempdata, &m_pData[i]);
		}
    }

    
// ----------------------------------------------------------------
//  Name:           ~MLinkedList
//  Description:    �޷θ��� �Ҵ��� Node�� ��� �����Ѵ�.
//  Arguments:      None.
//  Return Value:   None.
// ----------------------------------------------------------------
    ~MLinkedList()
    {
		if(m_pData)	delete [] m_pData;
		m_pData		  = 0;

		m_siCount	  = 0;
		m_siFreeCount = 0;
		m_siUsedCount = 0;
    }

// ----------------------------------------------------------------
//  Name:           Pop
//  Description:    �����ִ� Node�� �ϳ��� �����ش�.
//  Arguments:      None.
//  Return Value:   free Node.
// ----------------------------------------------------------------
    DListNode<Datatype> *Pop()
    {
		DListNode<Datatype> *freenode = NULL;

		freenode = m_Free.RemoveTail();

		if(freenode)
		{
			m_siFreeCount--;
			m_siUsedCount++;
		}
		return freenode;

	}

// ----------------------------------------------------------------
//  Name:           Push
//  Description:    ����ϰ� ������ Node�� �����Ѵ�.
//  Arguments:      freenode .
//  Return Value:   None.
// ----------------------------------------------------------------

	void Push(DListNode<Datatype> *freenode)
	{
		if(!freenode) return;
		Datatype tempdata;
		m_Free.Append(tempdata, freenode);

		m_siFreeCount++;
		m_siUsedCount--;
	}

// ----------------------------------------------------------------
//  Name:           CheckMemoryLeak
//  Description:    ���Ǿ��� Node�� �����ִ� ����� ������ �� ������ ���Ѵ�.
//  Arguments:      freenode .
//  Return Value:   compare count.
// ----------------------------------------------------------------
	bool CheckMemoryLeak()
	{
		if(m_siCount == (m_siFreeCount+m_siUsedCount)) return true;
		return false;
	}


// ----------------------------------------------------------------
//  Name:           Size
//  Description:    �� �޸𸮷� �Ҵ�� Node������ �����ش�.
//  Arguments:      None.
//  Return Value:   size of the list.
// ----------------------------------------------------------------
    int Size()
    {
        return m_siCount;
    }


// ----------------------------------------------------------------
//  Name:           FreeSize
//  Description:    ���� �Ҵ��Ҽ��ִ� Node�� ���� 
//  Arguments:      None.
//  Return Value:   free size of the list.
// ----------------------------------------------------------------
    int FreeSize()
    {
        return m_siFreeCount;
    }


// ----------------------------------------------------------------
//  Name:           UsedSize
//  Description:    �̹� �Ҵ�Ǿ��� Node�� ����
//  Arguments:      None.
//  Return Value:   used size of the list.
// ----------------------------------------------------------------
    int UsedSize()
    {
        return m_siUsedCount;
    }
};

#endif

