//-------------------------------------------------------------------------------------------------
// NkRbTreeMapMap.inl
// �������� ���������
// ������
//-------------------------------------------------------------------------------------------------

template <class TKey, class TData, class TComp, class TDataSetter> inline
NkRbTreeMap<TKey,TData,TComp,TDataSetter>::NkRbTreeMap()
: m_uiCount(0)
{
	NIL = NkNew NkRbTreeMapNode<TKey,TData>;

	memset(NIL, 0, sizeof(NkRbTreeMapNode<TKey,TData>));

	m_pkRoot = NIL;
}

template <class TKey, class TData, class TComp, class TDataSetter> inline
NkRbTreeMap<TKey,TData,TComp,TDataSetter>::~NkRbTreeMap()
{
	if( m_pkRoot != NIL )
		_RemoveRecursive(m_pkRoot);

	NkDelete NIL;
}


//-------------------------------------------------------------------------------------------------

template <class TKey, class TData, class TComp, class TDataSetter> inline
unsigned int NkRbTreeMap<TKey,TData,TComp,TDataSetter>::GetCount() const
{
	return m_uiCount;
}

template <class TKey, class TData, class TComp, class TDataSetter> inline
unsigned int NkRbTreeMap<TKey,TData,TComp,TDataSetter>::GetAllocedBytes() const
{
	return sizeof(NkRbTreeMapNode<TKey,TData>) * m_uiCount;
}

template <class TKey, class TData, class TComp, class TDataSetter> inline
unsigned int NkRbTreeMap<TKey,TData,TComp,TDataSetter>::GetMaxDepth() const
{
	NkRbTreeMapNode<TKey,TData>* pkNode = m_pkRoot;
	unsigned int uiDepth = 0;

	while( pkNode != NIL )
	{
		if( !pkNode->m_bRed )
			uiDepth += 1;		
		pkNode = pkNode->m_pkLeft;
	}

	return uiDepth * 2;
}

//-------------------------------------------------------------------------------------------------
template <class TKey, class TData, class TComp, class TDataSetter> inline
bool NkRbTreeMap<TKey,TData,TComp,TDataSetter>::InvalidPos(NkRbTreeMapPos kPos) const
{
	return kPos == NIL || kPos == 0;
}

template <class TKey, class TData, class TComp, class TDataSetter> inline
NkRbTreeMapPos NkRbTreeMap<TKey,TData,TComp,TDataSetter>::GetRootPos() const
{
	return m_pkRoot;
}

template <class TKey, class TData, class TComp, class TDataSetter> inline
NkRbTreeMapPos NkRbTreeMap<TKey,TData,TComp,TDataSetter>::GetParentPos(NkRbTreeMapPos kPos) const
{
	return ((NkRbTreeMap<TKey,TData,TComp,TDataSetter>*)kPos)->m_pkParent;
}

template <class TKey, class TData, class TComp, class TDataSetter> inline
NkRbTreeMapPos NkRbTreeMap<TKey,TData,TComp,TDataSetter>::GetLeftChildPos(NkRbTreeMapPos kPos) const
{
	return ((NkRbTreeMap<TKey,TData,TComp,TDataSetter>*)kPos)->m_pkLeft;
}

template <class TKey, class TData, class TComp, class TDataSetter> inline
NkRbTreeMapPos NkRbTreeMap<TKey,TData,TComp,TDataSetter>::GetRightChildPos(NkRbTreeMapPos kPos) const
{
	return ((NkRbTreeMap<TKey,TData,TComp,TDataSetter>*)kPos)->m_pkRight;
}

template <class TKey, class TData, class TComp, class TDataSetter>
NkRbTreeMapPos NkRbTreeMap<TKey,TData,TComp,TDataSetter>::GetBeginPos() const
{
	if( m_pkRoot == NIL ) return NIL;
	return _FindMin(m_pkRoot);
}

template <class TKey, class TData, class TComp, class TDataSetter>
NkRbTreeMapPos NkRbTreeMap<TKey,TData,TComp,TDataSetter>::GetEndPos() const
{
	if( m_pkRoot == NIL ) return NIL;
	return _FindMax(m_pkRoot);
}

template <class TKey, class TData, class TComp, class TDataSetter>
NkRbTreeMapPos NkRbTreeMap<TKey,TData,TComp,TDataSetter>::GetNextPos(NkRbTreeMapPos kPos) const
{
	return _FindNext((NkRbTreeMapNode<TKey,TData>*)kPos);
}

template <class TKey, class TData, class TComp, class TDataSetter>
NkRbTreeMapPos NkRbTreeMap<TKey,TData,TComp,TDataSetter>::GetPrevPos(NkRbTreeMapPos kPos) const
{
	return _FindPrev((NkRbTreeMapNode<TKey,TData>*)kPos);
}

//-------------------------------------------------------------------------------------------------

template <class TKey, class TData, class TComp, class TDataSetter> inline
bool NkRbTreeMap<TKey,TData,TComp,TDataSetter>::IsRedNode(NkRbTreeMapPos kPos) const
{
	return ((NkRbTreeMapNode<TKey,TData>*)kPos)->m_bRed;
}

template <class TKey, class TData, class TComp, class TDataSetter> inline
TKey& NkRbTreeMap<TKey,TData,TComp,TDataSetter>::GetKey(NkRbTreeMapPos kPos) const
{
	return ((NkRbTreeMapNode<TKey,TData>*)kPos)->m_key;
}

template <class TKey, class TData, class TComp, class TDataSetter> inline
TKey* NkRbTreeMap<TKey,TData,TComp,TDataSetter>::GetKeyPtr(NkRbTreeMapPos kPos) const
{
	return &((NkRbTreeMapNode<TKey,TData>*)kPos)->m_key;
}

template <class TKey, class TData, class TComp, class TDataSetter> inline
TData& NkRbTreeMap<TKey,TData,TComp,TDataSetter>::GetData(NkRbTreeMapPos kPos) const
{
	return ((NkRbTreeMapNode<TKey,TData>*)kPos)->m_data;
}

template <class TKey, class TData, class TComp, class TDataSetter> inline
TData* NkRbTreeMap<TKey,TData,TComp,TDataSetter>::GetDataPtr(NkRbTreeMapPos kPos) const
{
	return &((NkRbTreeMapNode<TKey,TData>*)kPos)->m_data;
}

//-------------------------------------------------------------------------------------------------

template <class TKey, class TData, class TComp, class TDataSetter>
NkRbTreeMapPosVector* NkRbTreeMap<TKey,TData,TComp,TDataSetter>::BuildMapPosVector()
{
	unsigned int uiDepth = GetMaxDepth();

	m_kPosVector.Resize((unsigned int)pow((double)2, (double)uiDepth));
	m_kPosVector.ClearData();

	NkRbTreeMapNode<TKey,TData>* pkNode = m_pkRoot;

	m_kPosVector[0] = pkNode;

	unsigned int uiSizeOfDepth = 1;
	unsigned int uiIndex = 1;
	unsigned int uiBaseIndex = 0;

	for( unsigned int uiCurDepth = 2; uiCurDepth <= uiDepth; ++uiCurDepth )
	{
		for( unsigned int i = 0; i < uiSizeOfDepth; ++i )
		{
			pkNode = (NkRbTreeMapNode<TKey,TData>*)m_kPosVector[uiBaseIndex++];

			if( pkNode == NIL || pkNode == 0 )
			{
				m_kPosVector[uiIndex++] = 0;
				m_kPosVector[uiIndex++] = 0;
			}
			else
			{
				m_kPosVector[uiIndex++] = (NkRbTreeMapPos)pkNode->m_pkLeft;
				m_kPosVector[uiIndex++] = (NkRbTreeMapPos)pkNode->m_pkRight;
			}
		}
		uiSizeOfDepth *= 2;
	}

	return &m_kPosVector;
}

//-------------------------------------------------------------------------------------------------
// Insert
//-------------------------------------------------------------------------------------------------
template <class TKey, class TData, class TComp, class TDataSetter>
bool NkRbTreeMap<TKey,TData,TComp,TDataSetter>::Insert(const TKey& key, const TData& data)
{
	NkRbTreeMapNode<TKey,TData>* pkNewNode = _NewNode();

	TDataSetter::SetData(pkNewNode->m_key, pkNewNode->m_data, key, data);

	pkNewNode->m_pkLeft = NIL;
	pkNewNode->m_pkRight = NIL;

	if( m_uiCount == 0 )
	{
		pkNewNode->m_pkParent = NIL;
		pkNewNode->m_bRed = false;
		m_pkRoot = pkNewNode;
		m_uiCount = 1;
		return true;
	}

	NkRbTreeMapNode<TKey,TData>* pkNode = m_pkRoot;
	NkRbTreeMapNode<TKey,TData>* pkTargetNode = NIL;

	while( pkNode != NIL )
	{
		pkTargetNode = pkNode;

		if( TComp::Equals(key, pkNode->m_key) )
		{
			_DeleteNode(pkNewNode);
			return false;
		}
		else if( TComp::Greater(key, pkNode->m_key) )
			pkNode = pkNode->m_pkRight;
		else
			pkNode = pkNode->m_pkLeft;
			
	}

	if( TComp::Greater(key, pkTargetNode->m_key) )
		pkTargetNode->m_pkRight = pkNewNode;
	else
		pkTargetNode->m_pkLeft = pkNewNode;
		
	pkNewNode->m_pkParent = pkTargetNode;
	pkNewNode->m_bRed = true;

	_InsertFixup(pkNewNode);

	++m_uiCount;

	return true;
}

//-------------------------------------------------------------------------------------------------
// Remove
//-------------------------------------------------------------------------------------------------
template <class TKey, class TData, class TComp, class TDataSetter>
bool NkRbTreeMap<TKey,TData,TComp,TDataSetter>::Remove(const TKey& key)
{

	NkRbTreeMapNode<TKey,TData>* pkNode = _Find(key);

	if( pkNode == NIL )
		return false;

	NkRbTreeMapNode<TKey,TData>* pkTargetNode;
	NkRbTreeMapNode<TKey,TData>* pkChildNode;

	if( pkNode->m_pkLeft == NIL || pkNode->m_pkRight == NIL )
		pkTargetNode = pkNode;
	else
		pkTargetNode = _FindNext(pkNode);

	if( pkTargetNode->m_pkLeft != NIL )
		pkChildNode = pkTargetNode->m_pkLeft;
	else
		pkChildNode = pkTargetNode->m_pkRight;

	pkChildNode->m_pkParent = pkTargetNode->m_pkParent;

	if( pkTargetNode->m_pkParent == NIL )
		m_pkRoot = pkChildNode;
	else if( pkTargetNode == pkTargetNode->m_pkParent->m_pkLeft )
		pkTargetNode->m_pkParent->m_pkLeft = pkChildNode;
	else
		pkTargetNode->m_pkParent->m_pkRight = pkChildNode;

	if( pkTargetNode != pkNode )
	{
		pkNode->m_key = pkTargetNode->m_key;
		pkNode->m_data = pkTargetNode->m_data;
	}

	if( pkTargetNode->m_bRed == false )
		_RemoveFixup(pkChildNode);

	_DeleteNode( pkTargetNode );

	--m_uiCount;

	return true;
}

template <class TKey, class TData, class TComp, class TDataSetter>
void NkRbTreeMap<TKey,TData,TComp,TDataSetter>::RemoveAll()
{
	if( m_pkRoot != NIL )
		_RemoveRecursive(m_pkRoot);
}


//-------------------------------------------------------------------------------------------------
// Find
//-------------------------------------------------------------------------------------------------
template <class TKey, class TData, class TComp, class TDataSetter>
NkRbTreeMapPos NkRbTreeMap<TKey,TData,TComp,TDataSetter>::FindPos(const TKey& key) const
{
	return _Find(key);
}

template <class TKey, class TData, class TComp, class TDataSetter>
bool NkRbTreeMap<TKey,TData,TComp,TDataSetter>::FindData(const TKey& key, TData& OUT data) const
{
	NkRbTreeMapNode<TKey,TData>* pkNode = _Find(key);

	if( pkNode != NIL )
	{
		data = pkNode->m_data;
		return true;
	}

	return false;
}

template <class TKey, class TData, class TComp, class TDataSetter>
TData* NkRbTreeMap<TKey,TData,TComp,TDataSetter>::FindDataPtr(const TKey& key) const
{
	NkRbTreeMapNode<TKey,TData>* pkNode = _Find(key);

	if( pkNode != NIL )
		return &pkNode->m_data;

	return 0;
}


//-------------------------------------------------------------------------------------------------

template <class TKey, class TData, class TComp, class TDataSetter> inline
void NkRbTreeMap<TKey,TData,TComp,TDataSetter>::_InsertFixup(NkRbTreeMapNode<TKey,TData>* pkNode)
{

	// 
	//               g(black)                          g(red)
	//              ����������	                     ���������� 
	//            p(red)   u(red)	  =>         p(black)   u(black) 
	//          ����������		                ���������� 
	//     pkNode(red)  		           pkNode(red)   
	//
	//
	//
	//               g(black)                          g(red)
	//              ����������	                     ���������� 
	//            p(red)   u(black)    =>         p(black)   u(black) 
	//          ����������		                ���������� 
	//     pkNode(red)  		           pkNode(red)   
	//    ����������
	//    a       b
	//


	NkRbTreeMapNode<TKey,TData>* pkParent = pkNode->m_pkParent;
	NkRbTreeMapNode<TKey,TData>* pkGrandParent = pkParent->m_pkParent; 

	NkRbTreeMapNode<TKey,TData>* pkUncleNode;

	// �θ� ��尡 Red�� ��쿡 �ұ����� �߻��ϹǷ�, ���� �۾��� �Ѵ�
	while( pkParent->m_bRed )
	{
		// pkParent�� pkGrandParent�� ���� ����� ���
		if( pkParent == pkGrandParent->m_pkLeft )
		{
			pkUncleNode = pkGrandParent->m_pkRight;

			if( pkUncleNode->m_bRed )
			{
				pkParent->m_bRed = false;
				pkUncleNode->m_bRed = false;
				pkGrandParent->m_bRed = true;

				pkNode = pkGrandParent;
				pkParent = pkNode->m_pkParent;
				pkGrandParent = pkParent->m_pkParent; 
			}
			else 
			{
				if( pkNode == pkParent->m_pkRight )
				{
					pkNode = pkParent;
					_RotateLeft(pkNode);
				}
				pkParent->m_bRed = false;
				pkGrandParent->m_bRed = true;
				_RotateRight(pkGrandParent);
			}
		}
		// pkParent�� pkGrandParent�� ������ ����� ���
		else
		{
			pkUncleNode = pkGrandParent->m_pkLeft;

			if( pkUncleNode->m_bRed )
			{
				pkParent->m_bRed = false;
				pkUncleNode->m_bRed = false;
				pkGrandParent->m_bRed = true;

				pkNode = pkGrandParent;
				pkParent = pkNode->m_pkParent;
				pkGrandParent = pkParent->m_pkParent; 
			}
			else 
			{
				if( pkNode == pkParent->m_pkLeft )
				{
					pkNode = pkParent;
					_RotateRight(pkNode);
				}
				pkParent->m_bRed = false;
				pkGrandParent->m_bRed = true;
				_RotateLeft(pkGrandParent);
			}
		}
	}

	m_pkRoot->m_bRed = false;
}

template <class TKey, class TData, class TComp, class TDataSetter> inline
void NkRbTreeMap<TKey,TData,TComp,TDataSetter>::_RemoveFixup(NkRbTreeMapNode<TKey,TData>* pkNode)
{
	NkRbTreeMapNode<TKey,TData>* pkParent;
	NkRbTreeMapNode<TKey,TData>* pkSibling;

	// ������ ��尡 Root�� �ƴϰ� Black�� ��쿡 �ұ����� �߻��ϹǷ�, ���� �۾��� �Ѵ�
	while( pkNode != m_pkRoot && pkNode->m_bRed == false )
	{
		pkParent = pkNode->m_pkParent;

		if( pkNode == pkParent->m_pkLeft )
		{
			pkSibling = pkParent->m_pkRight;

			if( pkSibling->m_bRed == true )
			{
				pkSibling->m_bRed = false;
				pkParent->m_bRed = true;
				_RotateLeft(pkParent);

				pkParent = pkNode->m_pkParent;
				pkSibling = pkParent->m_pkRight;
			}

			if( pkSibling->m_pkLeft == 0 || pkSibling->m_pkRight == 0 ) 
				break;

			if( pkSibling->m_pkLeft->m_bRed == false && pkSibling->m_pkRight->m_bRed == false )
			{
				pkSibling->m_bRed = true;
				pkNode = pkParent;
			}
			else 
			{
				if( pkSibling->m_pkRight->m_bRed == false )
				{
					pkSibling->m_pkLeft->m_bRed = false;
					pkSibling->m_bRed = true;
					_RotateRight(pkSibling);

					pkParent = pkNode->m_pkParent;
					pkSibling = pkParent->m_pkRight;
				}

				pkSibling->m_bRed = pkParent->m_bRed;
				pkParent->m_bRed = false;
				pkSibling->m_pkRight->m_bRed = false;
				_RotateLeft(pkParent);
				pkNode = m_pkRoot;
			}
		}
		else
		{
			pkSibling = pkParent->m_pkLeft;

			if( pkSibling->m_bRed == true )
			{
				pkSibling->m_bRed = false;
				pkParent->m_bRed = true;
				_RotateRight(pkParent);

				pkParent = pkNode->m_pkParent;
				pkSibling = pkParent->m_pkLeft;
			}

			if( pkSibling->m_pkLeft == 0 || pkSibling->m_pkRight == 0 ) 
				break;

			if( pkSibling->m_pkLeft->m_bRed == false && pkSibling->m_pkRight->m_bRed == false )
			{
				pkSibling->m_bRed = true;
				pkNode = pkParent;
			}
			else 
			{
				if( pkSibling->m_pkLeft->m_bRed == false )
				{
					pkSibling->m_pkRight->m_bRed = false;
					pkSibling->m_bRed = true;
					_RotateLeft(pkSibling);

					pkParent = pkNode->m_pkParent;
					pkSibling = pkParent->m_pkLeft;
				}

				pkSibling->m_bRed = pkParent->m_bRed;
				pkParent->m_bRed = false;
				pkSibling->m_pkLeft->m_bRed = false;
				_RotateRight(pkParent);
				pkNode = m_pkRoot;
			}
		}
	}

	pkNode->m_bRed = false;	
}

template <class TKey, class TData, class TComp, class TDataSetter> inline
NkRbTreeMapNode<TKey,TData>*
NkRbTreeMap<TKey,TData,TComp,TDataSetter>::_FindMin(NkRbTreeMapNode<TKey,TData>* pkNode) const
{
	NkRbTreeMapNode<TKey,TData>* pkTemp = pkNode->m_pkLeft;

	while( pkTemp != NIL )
	{
		pkNode = pkTemp;
		pkTemp = pkTemp->m_pkLeft;
	}

	return pkNode;
}

template <class TKey, class TData, class TComp, class TDataSetter> inline
NkRbTreeMapNode<TKey,TData>*
NkRbTreeMap<TKey,TData,TComp,TDataSetter>::_FindMax(NkRbTreeMapNode<TKey,TData>* pkNode) const
{
	NkRbTreeMapNode<TKey,TData>* pkTemp = pkNode->m_pkRight;

	while( pkTemp != NIL )
	{
		pkNode = pkTemp;
		pkTemp = pkTemp->m_pkRight;
	}

	return pkNode;
}

template <class TKey, class TData, class TComp, class TDataSetter> inline
NkRbTreeMapNode<TKey,TData>*
NkRbTreeMap<TKey,TData,TComp,TDataSetter>::_FindPrev(NkRbTreeMapNode<TKey,TData>* pkNode) const
{
	if( pkNode->m_pkLeft != NIL )
		return _FindMax(pkNode->m_pkLeft);

	NkRbTreeMapNode<TKey,TData>* pkParent = pkNode->m_pkParent;

	while( pkParent != NIL && pkNode == pkParent->m_pkLeft )
	{
		pkNode = pkParent;
		pkParent = pkParent->m_pkParent;
	}

	return pkParent;
}

template <class TKey, class TData, class TComp, class TDataSetter> inline
NkRbTreeMapNode<TKey,TData>*
NkRbTreeMap<TKey,TData,TComp,TDataSetter>::_FindNext(NkRbTreeMapNode<TKey,TData>* pkNode) const
{
	if( pkNode->m_pkRight != NIL )
		return _FindMin(pkNode->m_pkRight);

	NkRbTreeMapNode<TKey,TData>* pkParent = pkNode->m_pkParent;

	while( pkParent != NIL && pkNode == pkParent->m_pkRight )
	{
		pkNode = pkParent;
		pkParent = pkParent->m_pkParent;
	}

	return pkParent;
}

template <class TKey, class TData, class TComp, class TDataSetter> inline
NkRbTreeMapNode<TKey,TData>*
NkRbTreeMap<TKey,TData,TComp,TDataSetter>::_Find(const TKey& key) const
{
	NkRbTreeMapNode<TKey,TData>* pkNode = m_pkRoot;

	while( pkNode != NIL && !TComp::Equals(key, pkNode->m_key) )
	{
		if( TComp::Greater(key, pkNode->m_key) )			
			pkNode = pkNode->m_pkRight;
		else
			pkNode = pkNode->m_pkLeft;
	}

	return pkNode;
}

template <class TKey, class TData, class TComp, class TDataSetter> inline
void NkRbTreeMap<TKey,TData,TComp,TDataSetter>::_RotateLeft(NkRbTreeMapNode<TKey,TData>* pkNode)
{
	NkRbTreeMapNode<TKey,TData>* pkParent = pkNode->m_pkParent;
	NkRbTreeMapNode<TKey,TData>* pkRight = pkNode->m_pkRight;
	NkRbTreeMapNode<TKey,TData>* pkBeta = pkRight->m_pkLeft;

	// �˰��� ����
	//
	//    (pkParent)                              (pkParent)
	//        ��                                      ��
	//        ��(pkNode)           ��        (pkRight)��
	//    ����������             (ȸ��)           ����������
	//    ��      ��(pkRight)             (pkNode)��      ��
	//        ����������                      ����������
	//        ��      ��                      ��      ��


	// ���� ������ �ڽ� ��带 ��� �����Ѵ�
	pkNode->m_pkRight = pkBeta;

	// �Ⱑ NIL�� �ƴϸ�,
	// ���� �θ� ��带 �ط� �����Ѵ�
	if( pkBeta != NIL )
		pkBeta->m_pkParent = pkNode;

	// ���� ���� �ڽ� ��带 �ط� �����Ѵ�
	pkRight->m_pkLeft = pkNode;

	// ���� �θ� ��带 �ٷ� �����Ѵ�
	pkNode->m_pkParent = pkRight;

	if( pkParent == NIL )
	{
		// pkParent�� NIL�̸� �ֻ��� ����̹Ƿ� m_pkRoot�� Y�� �����Ѵ�
		m_pkRoot = pkRight;
	}
	else
	{
		// pkNode�� �θ��� ���� �ڽ� �������, ������ �ڽ� ������� �Ǵ��Ͽ� �ش� ��带 Y�� �����Ѵ�
		if( pkParent->m_pkLeft == pkNode )
			pkParent->m_pkLeft = pkRight;
		else
			pkParent->m_pkRight = pkRight;
	}

	// ���� �θ� ��带 pkParent�� �����Ѵ�.
	pkRight->m_pkParent = pkParent;
}

template <class TKey, class TData, class TComp, class TDataSetter> inline
void NkRbTreeMap<TKey,TData,TComp,TDataSetter>::_RotateRight(NkRbTreeMapNode<TKey,TData>* pkNode)
{
	NkRbTreeMapNode<TKey,TData>* pkParent = pkNode->m_pkParent;
	NkRbTreeMapNode<TKey,TData>* pkLeft = pkNode->m_pkLeft;
	NkRbTreeMapNode<TKey,TData>* pkBeta = pkLeft->m_pkRight;

	// �˰��� ����
	//
	//            (pkParent)                (pkParent)
	//                ��                        ��
	//        (pkNode)��           ��           ��(pkLeft)
	//            ����������     (ȸ��)     ����������
	//    (pkLeft)��      ��                ��      ��(pkNode)
	//        ����������                        ����������
	//        ��      ��                        ��      ��           


	// ���� ���� �ڽ� ��带 ��� �����Ѵ�
	pkNode->m_pkLeft = pkBeta;

	// �Ⱑ NULL�� �ƴϸ�
	// ���� �θ� ��带 �ط� �����Ѵ�
	if( pkBeta != NIL )
		pkBeta->m_pkParent = pkNode;

	// ���� ������ �ڽ� ��带 �ط� �����Ѵ�
	pkLeft->m_pkRight = pkNode;

	// ���� �θ� ��带 �ٷ� �����Ѵ�
	pkNode->m_pkParent = pkLeft;

	if( pkParent == NIL )
	{
		// pkParent�� NIL�̸� �ֻ��� ����̹Ƿ� m_pkRoot�� Y�� �����Ѵ�
		m_pkRoot = pkLeft;
	}
	else
	{
		// pkNode�� �θ��� ���� �ڽ� �������, ������ �ڽ� ������� �Ǵ��Ͽ� �ش� ��带 Y�� �����Ѵ�
		if( pkParent->m_pkLeft == pkNode )
			pkParent->m_pkLeft = pkLeft;
		else
			pkParent->m_pkRight = pkLeft;
	}

	// ���� �θ� ��带 pkParent�� �����Ѵ�.
	pkLeft->m_pkParent = pkParent;
}

template <class TKey, class TData, class TComp, class TDataSetter>
void NkRbTreeMap<TKey,TData,TComp,TDataSetter>::_RemoveRecursive(NkRbTreeMapNode<TKey,TData>* pkNode)
{
	NkRbTreeMapNode<TKey,TData>* pkParent = pkNode->m_pkParent;
	NkRbTreeMapNode<TKey,TData>* pkLeft = pkNode->m_pkLeft;
	NkRbTreeMapNode<TKey,TData>* pkRight = pkNode->m_pkRight;

	if( pkLeft != NIL ) 
		_RemoveRecursive(pkLeft);

	if( pkRight != NIL )
		_RemoveRecursive(pkRight);

	if( pkParent != NIL )
	{
		if( pkParent->m_pkLeft == pkNode )
			pkParent->m_pkLeft = NIL;
		else
			pkParent->m_pkRight = NIL;
	}

	_DeleteNode(pkNode);
}


template <class TKey, class TData, class TComp, class TDataSetter> inline
NkRbTreeMapNode<TKey,TData>* NkRbTreeMap<TKey,TData,TComp,TDataSetter>::_NewNode()
{
	return NkNew NkRbTreeMapNode<TKey,TData>;
}

template <class TKey, class TData, class TComp, class TDataSetter> inline
void NkRbTreeMap<TKey,TData,TComp,TDataSetter>::_DeleteNode( NkRbTreeMapNode<TKey,TData>* pkNode )
{
	TDataSetter::DeleteData(pkNode->m_key, pkNode->m_data);
	NkDelete pkNode;
}
