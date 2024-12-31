// ============================================================================
// DLinkedList.h
//
// This is the Doubly-Linked List class
// ============================================================================
#ifndef _DLINKEDLIST_H_
#define _DLINKEDLIST_H_




// forward declarations 
template<class Datatype> class DListNode;
template<class Datatype> class DLinkedList;
template<class Datatype> class DListIterator;



// -------------------------------------------------------
// Name:        DListNode
// Description: This is the Doubly-linked list node class.
// -------------------------------------------------------
template<class Datatype>
class DListNode
{
public:

// ----------------------------------------------------------------
//  Name:           m_Data
//  Description:    �� Node�� ���� �ִ� Data
// ----------------------------------------------------------------
    Datatype m_Data;

// ----------------------------------------------------------------
//  Name:           m_Next
//  Description:    List���� �� Node�� ����Ű�� Next Node
// ----------------------------------------------------------------
    DListNode<Datatype>* m_Next;

// ----------------------------------------------------------------
//  Name:           m_Previous
//  Description:    List���� �� Node�� ����Ű�� Previous Node
// ----------------------------------------------------------------
    DListNode<Datatype>* m_Previous;

public:

// ----------------------------------------------------------------
//  Name:           DeLink
//  Description:    �� ��带 List���� Link�� ���� �յڸ� �����Ѵ�.
//  Arguments:      None.
//  Return Value:   None.
// ----------------------------------------------------------------
    void Delink()
    {
		// Previous Node�� �ִٸ�, Previous Node�� Next Node�� ����Ű���� �Ѵ�.
        if( m_Previous != 0 )
            m_Previous->m_Next = m_Next;

		// Next Node�� �ִٸ�, Next Node�� Previous Node�� ����Ű���� �Ѵ�.
        if( m_Next != 0 )
            m_Next->m_Previous = m_Previous;
    }


// ----------------------------------------------------------------
//  Name:           InsertAfter
//  Description:    ������ Node �ٷεڿ� ���ο� Node�� �߰��Ѵ�.
//  Arguments:      Data	 - ���ο� Node�� ����Ǿ��� Data
//				    pNewNode - ���� ������ Node Pointer
//  Return Value:   None.
// ----------------------------------------------------------------
    bool InsertAfter( Datatype Data, DListNode<Datatype> *pNewNode )
    {
		if(!pNewNode) return false;

		// New Node�� Data�� �����Ѵ�.
        pNewNode->m_Data	= Data;

        // New Node�� ���ο� Pointer�� �����Ѵ�.
        pNewNode->m_Next    = m_Next;
        pNewNode->m_Previous= this;

		// �� Node ������ Node �� �����Ѵٸ� New Node�� ����Ű�����Ѵ�.
        if( m_Next != 0 )
            m_Next->m_Previous = pNewNode;

        // �� Node�� ������ New Node�� ����Ű���� �Ѵ�.
        m_Next = pNewNode;
		return true;
    }


// ----------------------------------------------------------------
//  Name:           InsertBefore
//  Description:    ������ Node�տ� ���ο� Node�� �߰��Ѵ�.
//  Arguments:      Data	 - ���ο� Node�� ����Ǿ��� Data
//				    pNewNode - ���� ������ Node Pointer
//  Return Value:   None.
// ----------------------------------------------------------------
    bool InsertBefore( Datatype Data, DListNode<Datatype>* pNewNode )
    {
        if(!pNewNode) return false;

		// New Node�� Data�� �����Ѵ�.
        pNewNode->m_Data	= Data;

        // New Node�� ���ο� Pointer�� �����Ѵ�.
        pNewNode->m_Next     = this;
        pNewNode->m_Previous = m_Previous;

		// �� Node �տ� Node �� �����Ѵٸ� New Node�� ����Ű�����Ѵ�.
        if( m_Previous != 0 )
            m_Previous->m_Next = pNewNode;

		// �� Node�� Previous�� New Node�� ����Ű���� �Ѵ�.
        m_Previous = pNewNode;

		return true;
    }


};


// -------------------------------------------------------
// Name:        DLinkedList
// Description: This is the Doubly-linked list container.
// -------------------------------------------------------
template<class Datatype>
class DLinkedList
{
public:
// ----------------------------------------------------------------
//  Name:           m_Head
//  Description:    The first node in the list
// ----------------------------------------------------------------
    DListNode<Datatype>* m_Head;

// ----------------------------------------------------------------
//  Name:           m_Tail
//  Description:    The last node in the list
// ----------------------------------------------------------------
    DListNode<Datatype>* m_Tail;

// ----------------------------------------------------------------
//  Name:           m_siCount
//  Description:    The number of nodes in the list
// ----------------------------------------------------------------
    int m_siCount;

public:

// ----------------------------------------------------------------
//  Name:           DLinkedList
//  Description:    Constructor; creates an empty list
//  Arguments:      None.
//  Return Value:   None.
// ----------------------------------------------------------------
    DLinkedList()
    {
        m_Head		= 0;
        m_Tail		= 0;
        m_siCount	= 0;
    }

    
// ----------------------------------------------------------------
//  Name:           DLinkedList
//  Description:    Destructor; destroys every node
//  Arguments:      None.
//  Return Value:   None.
// ----------------------------------------------------------------
    ~DLinkedList()
    {
        m_Head		= 0;
        m_Tail		= 0;
        m_siCount	= 0;
    }


// ----------------------------------------------------------------
//  Name:           Append
//  Description:    List�� �ǵڿ� ���ο� Node�� �߰��Ѵ�.
//  Arguments:      Data	 - �߰��� Data
//					pNewNode - ���� ������ Node Pointer
//  Return Value:   None.
// ----------------------------------------------------------------
    bool Append( Datatype Data, DListNode<Datatype>* pNewNode)
    {
		if(!pNewNode) return false;

        // List�� ����ִ� �����̹Ƿ� Head Node�� NULL �϶� 
        if( m_Head == 0 )
        {
            // ���ο� Head Node�� �����Ѵ�.
            m_Head	= m_Tail	= pNewNode;
            m_Head->m_Data		= Data;
            m_Head->m_Next		= 0;
            m_Head->m_Previous	= 0;
        }
        else
        {
			// Tail �ڿ� ���ο� Node�� �߰��ϰ� Tail�� �缳���Ѵ�.
            m_Tail->InsertAfter( Data, pNewNode );
            m_Tail = m_Tail->m_Next;
        }
		// Count�� �ϳ� ������Ų��.
        m_siCount++;
		return true;
    }


// ----------------------------------------------------------------
//  Name:           Prepend
//  Description:    List�� �Ǿտ� ���ο� Node�� �߰��Ѵ�.
//  Arguments:      Data	 - �߰��� Data
//					pNewNode - ���� ������ Node Pointer
//  Return Value:   None.
// ----------------------------------------------------------------
    bool Prepend( Datatype Data, DListNode<Datatype> *pNewNode )
    {
		if(!pNewNode) return false;

        // List�� ����ִ� �����̹Ƿ� Head Node�� NULL �϶� 
        if( m_Head == 0 )
        {
            // ���ο� Head Node�� �����Ѵ�.
            m_Head	= m_Tail	= pNewNode;
            m_Head->m_Data		= Data;
            m_Head->m_Next		= 0;
            m_Head->m_Previous	= 0;
        }
        else
        {
			// Head�տ� ���ο� Node�� �߰��ϰ� Head�� �缳���Ѵ�.
            m_Head->InsertBefore( Data, pNewNode );
            m_Head = m_Head->m_Previous;
        }
		// Count�� �ϳ� ������Ų��.
        m_siCount++;
		return true;
    }


// ----------------------------------------------------------------
//  Name:           RemoveHead
//  Description:    List�� Head Node�� �����Ѵ�.
//  Arguments:      pRemovedNode - ���ŵ� Node
//  Return Value:   None.
// ----------------------------------------------------------------
    DListNode<Datatype> *RemoveHead()
    {
		DListNode<Datatype>* pRemovedNode = 0;
        DListNode<Datatype>* node = 0;

        if( m_Head != 0 )
        {
			// Head�� Next Node�� �ӽ÷� �����Ѵ�.
            node = m_Head->m_Next;

			// Head�� �����ϰ� node�� Head�� �����Ѵ�.
			pRemovedNode = m_Head;	//  delete m_Head;
            m_Head		 = node;

			// ���ο� Head�� NULL �̶��, Tail �� NULL�� ����
			// �׷�ġ ������, ���ο� Head�� Previous Node�� NULL�� �����Ѵ�.
            if( m_Head == 0 )
                m_Tail = 0;
            else
                m_Head->m_Previous = 0;

			// Count�� �ϳ� ���δ�.
            m_siCount--;

			return pRemovedNode;
        }
		return NULL;
    }


// ----------------------------------------------------------------
//  Name:           RemoveTail
//  Description:    List�� Tail Node�� �����Ѵ�.
//  Arguments:      pRemovedNode - ���ŵ� Node.
//  Return Value:   None.
// ----------------------------------------------------------------
    DListNode<Datatype>* RemoveTail()
    {
		DListNode<Datatype>* pRemovedNode = 0;
        DListNode<Datatype>* node = 0;

        if( m_Tail != 0 )
        {
            // Tail�� Previous Node�� �ӽ÷� �����Ѵ�.
            node = m_Tail->m_Previous;

			// Tail�� �����ϰ� node�� Tail Node�� �����Ѵ�.
            pRemovedNode = m_Tail; //delete m_Tail;
            m_Tail		 = node;

			// ���ο� Tail�� NULL �̶��, Head Node�� NULL�� �����Ѵ�.
			// �׷�ġ ������, ���ο� Tail�� Next Node�� NULL�� �����Ѵ�.
            if( m_Tail == 0 )
                m_Head = 0;
            else
                m_Tail->m_Next = 0;

			// Count�� �ϳ� ���δ�.
            m_siCount--;

			return pRemovedNode;
        }
		return NULL;
    }



// ----------------------------------------------------------------
//  Name:           InsertAfter
//  Description:    iterator �ٷ� �ڿ� Data�� �߰��ϰų� 
//	                iterator�� invalid �ϸ� List�� �ǵڿ� �߰��Ѵ�.
//  Arguments:      Iterator - �ڿ� Insert�� Iterator
//					Data	 - ���ο� Node�� ����Ǿ��� Data
//					pNewNode - ���� ������ Node Pointer
//  Return Value:   None.
// ----------------------------------------------------------------
    bool InsertAfter( DListIterator<Datatype>& Iterator, Datatype Data, DListNode<Datatype> *pNewNode)
    {
        if( Iterator.m_Node != 0 )
        {
            // Iterator �ڿ� Data�� �߰��Ѵ�.
            Iterator.m_Node->InsertAfter( Data, pNewNode);

			// Iterator�� Tail�̶�� Tail�� ���� �����Ѵ�.
            if( Iterator.m_Node == m_Tail )
                m_Tail = m_Tail->m_Next;

            // Count�� �ϳ� ������Ų��.
            m_siCount++;
			return true;
        }
        else
        {
            return Append( Data );
        }

		return false;
    }


// ----------------------------------------------------------------
//  Name:           InsertBefore
//  Description:    iterator �ٷ� �տ� Data�� �߰��ϰų� 
//	                iterator�� invalid �ϸ� List�� �Ǿտ� �߰��Ѵ�.
//  Arguments:      Iterator - �տ� Insert�� Iterator
//					Data	 - ���ο� Node�� ����Ǿ��� Data
//					pNewNode - ���� ������ Node Pointer
//  Return Value:   None.
// ----------------------------------------------------------------
    bool InsertBefore( DListIterator<Datatype>& Iterator, Datatype Data, DListNode<Datatype> *pNewNode )
    {
        if( Iterator.m_Node != 0 )
        {
            // Iterator �տ� Data�� �߰��Ѵ�.
            Iterator.m_Node->InsertBefore( Data, pNewNode );

			// Iterator�� Head��� Head�� ���� �����Ѵ�.
            if( Iterator.m_Node == m_Head )
                m_Head = m_Head->m_Previous;

            // Count�� �ϳ� ������Ų��.
            m_siCount++;
			return true;
        }
        else
        {
            return Prepend( Data );
        }
		return false;
    }


// ----------------------------------------------------------------
//  Name:           Remove
//  Description:    Iterator�� ����Ű�� Node�� �����ϰ�. 
//					Next Node�� Interator Pointer�� �����Ѵ�.	
//  Arguments:      Iterator     - ������ Iterator
//					pRemovedNode - ���ŵ� Node
//  Return Value:   None.
// ----------------------------------------------------------------
    DListNode<Datatype>* Remove( DListIterator<Datatype>& Iterator)
    {
        // temporary node pointer.
		DListNode<Datatype>* pRemovedNode =0;
        DListNode<Datatype>* node =0;

        // Iterator�� invalid��� ���ư���.
        if( Iterator.m_Node == 0 )	return NULL;

        // ������ Node�� �ӽú����� �����Ѵ�.
        node = Iterator.m_Node;

		// ������ Node�� Head �ų� Tail �̶�� 
		// Head�� Tail�� �����̳� ���� Node�� �������Ѵ�.
        if( node == m_Head )
        {
            m_Head = m_Head->m_Next;
        }
        else if( node == m_Tail )
        {
            m_Tail = m_Tail->m_Previous;
        }

		// Iterator�� ������ Valid Node�� �ű��.
        Iterator.Forth();

        // ������ Node�� Delink��Ų��.
        node->Delink();

		pRemovedNode = node;// delete node;

		// Head�� NULL�̶�� Tail�� NULL�� �����.
        if( m_Head == 0 )
            m_Tail = 0;
        
        m_siCount--;

		return pRemovedNode;
    }



// ----------------------------------------------------------------
//  Name:           GetIterator
//  Description:    Iterator�� List�� �Ǿ��� ����Ű���� �ϰ� ���´�.
//  Arguments:      None.
//  Return Value:   List�� �Ǿ��� ����Ű�� Iterator
// ----------------------------------------------------------------
    DListIterator<Datatype> GetIterator()
    {
        return DListIterator<Datatype>( this, m_Head );
    }


// ----------------------------------------------------------------
//  Name:           Size
//  Description:    List�� ������ Count�� ���´�.
//  Arguments:      None.
//  Return Value:   List�� ũ��
// ----------------------------------------------------------------
    int Size()
    {
        return m_siCount;
    }


// ----------------------------------------------------------------
//  Name:           SaveToDisk
//  Description:    Linked List�� Disk�� �����Ѵ�.
//  Arguments:      pFileName	- ������ �����̸� 
//  Return Value:   true, if successful
// ----------------------------------------------------------------
    bool SaveToDisk( char* pFileName )
    {
        FILE* fpOutFile = 0;
        DListNode<Datatype>* itr = m_Head;

        // ������ ����.
        fpOutFile = _tfopen( pFileName, TEXT("wb") );

        // ������ ���µ� �����ߴٸ� ���ư���.
        if( fpOutFile == 0 )
            return false;

        // ���� List�� Size�� �����Ѵ�.
        fwrite( &m_siCount, sizeof( int ), 1, fpOutFile );

        // Loop�� ���鼭 List�� �����Ѵ�.
        while( itr != 0 )
        {
            fwrite( &(itr->m_Data), sizeof( Datatype ), 1, fpOutFile );
            itr = itr->m_Next;
        }
		// ������ �ݴ´�.
        fclose( fpOutFile );

        return true;
    }


// ----------------------------------------------------------------
//  Name:           ReadFromDisk
//  Description:    Reads a linked list from a file.
//  Arguments:      p_filename: the name of the file to read from
//  Return Value:   true if successful.
// ----------------------------------------------------------------
    bool ReadFromDisk( char* pFileName )
    {
        FILE* fpInFile = 0;
        Datatype buffer;
        int count = 0;

        // ������ ����.
        fpInFile = _tfopen( pFileName, TEXT("rb") );

        // ������ ���µ� �����ߴٸ� ���ư���.
        if( fpInFile == 0 )
            return false;

        // ���� List�� Size�� �о�´�.
        fread( &count, sizeof( int ), 1, fpInFile );

		// Loop�� ���鼭 Data�� �о�´�.
        while( count != 0 )
        {
            fread( &buffer, sizeof( Datatype ), 1, fpInFile );
            Append( buffer );
            count--;
        }

		// ������ �ݴ´�.
        fclose( fpInFile );

        return true;
    }

};




// -------------------------------------------------------
// Name:        DListIterator
// Description: This is the basic linked list iterator class.
// -------------------------------------------------------
template<class Datatype>
class DListIterator
{
public:

// ----------------------------------------------------------------
//  Name:           m_Node
//  Description:    ������ Node�� ����Ű�� Pointer
// ----------------------------------------------------------------
    DListNode<Datatype>* m_Node;


// ----------------------------------------------------------------
//  Name:           m_List
//  Description:    ������ List�� ����Ű�� Pointer
// ----------------------------------------------------------------
    DLinkedList<Datatype>* m_List;
public:


// ----------------------------------------------------------------
//  Name:           DListIterator
//  Description:    Constructor  - ������ List�� Node�� Interator�� �����Ѵ�. , creates an iterator that points
//  Arguments:      pList	- Iterator�� ���� List�� Pointer 
//                  pNode	- ������ Node�� ����Ű�� Pointer 
//  Return Value:   None.
// ----------------------------------------------------------------
    DListIterator( DLinkedList<Datatype>* pList = 0, DListNode<Datatype>* pNode = 0 )
    {
        m_List = pList;
        m_Node = pNode;
    }


// ----------------------------------------------------------------
//  Name:           Start
//  Description:    Iterator�� List�� �Ǿ� Node�� �����Ѵ�.
//  Arguments:      None.
//  Return Value:   None.
// ----------------------------------------------------------------
    void Start()
    {
        if( m_List != 0 )	m_Node = m_List->m_Head;
    }

// ----------------------------------------------------------------
//  Name:           End
//  Description:    Iterator�� List�� �ǵ� Node�� �����Ѵ�.
//  Arguments:      None.
//  Return Value:   None.
// ----------------------------------------------------------------
    void End()
    {
        if( m_List != 0 )	m_Node = m_List->m_Tail;
    }


// ----------------------------------------------------------------
//  Name:           Forth
//  Description:    Iterator�� ���� Node�� �̵���Ų��.
//  Arguments:      None.
//  Return Value:   None.
// ----------------------------------------------------------------
    void Forth()
    {
        if( m_Node != 0 )	m_Node = m_Node->m_Next;
    }


// ----------------------------------------------------------------
//  Name:           Back
//  Description:    Iterator�� �� Node�� �̵���Ų��.
//  Arguments:      None.
//  Return Value:   None.
// ----------------------------------------------------------------
    void Back()
    {
        if( m_Node != 0 )	m_Node = m_Node->m_Previous;
    }


// ----------------------------------------------------------------
//  Name:           Item
//  Description:    Iterator�� ����Ű�� Item�� ���´�.
//  Arguments:      None.
//  Return Value:   Node�� �ִ� Data�� ���´�.
// ----------------------------------------------------------------
    Datatype& Item()
    {
        return m_Node->m_Data;
    }


// ----------------------------------------------------------------
//  Name:           Valid
//  Description:    Node�� valid���� �˻��Ѵ�.
//  Arguments:      None.
//  Return Value:   valid �ϸ� true�� �����ش�.
// ----------------------------------------------------------------
    bool Valid()
    {
        return (m_Node != 0);
    }


// ----------------------------------------------------------------
//  Name:           operator==
//  Description:    2���� Iterator�� ���� Node�� ����Ű���� �˻��Ѵ�.
//  Arguments:      None.
//  Return Value:   ���� Node��� true�� �����ش�.
// ----------------------------------------------------------------
    bool operator==( DListIterator<Datatype>& p_rhs )
    {
        if( m_Node == p_rhs.m_Node && m_List == p_rhs.m_List )
        {
            return true;
        }
        return false;
    }

};



#endif
