//-------------------------------------------------------------------------------------------------
// NkHashMap.h
// �������� ���������
// ������
//-------------------------------------------------------------------------------------------------

#pragma once

#include "NkAlgorithm.h"
#include "NkVector.h"

//=================================================================================================
//
// Hash Functor(�ؽ��� ���� �Լ���)�� Equals Functor(Ű �� �� �Լ���)�� �����ؼ� ����ϼ���
//
// ������� : �Ʒ� �ҽ��� �����Ͽ� ClassName�� Type�� ��ü�Ͽ� ���
//
//=================================================================================================
/*

//-------------------------------------------------------------------------------------------------
// Hash Functor
//-------------------------------------------------------------------------------------------------
class ClassName
{
public:
	inline static unsigned int KeyToHashIndex(const Type& key, unsigned int uiHashSize)
	{
		return key % uiHashSize;
	}
};


//-------------------------------------------------------------------------------------------------
// Equals Functor
//-------------------------------------------------------------------------------------------------
class ClassName
{
public:
	inline static bool Equals(const Type& a, const Type& b)
	{
		return a == b;
	}
};

*/

//=================================================================================================
//
// Key, Data�� �߰�/������ ������ �޸� �Ҵ��̳� ������ �ʿ��� ��쿡��,
// PairDataSetter(������ ����, �Ҹ� �Լ���)�� �����ؼ� ����ϼ���
//
// ���� ��� : �Ʒ� �ҽ��� �����Ͽ� ClassName�� KeyType, DataType�� ��ü�Ͽ� ���
//
//=================================================================================================
/*

class ClassName
{
public:
	static inline void SetData(KeyType& destKey, DataType& destData, const KeyType& srcKey, const DataType& srcData) 
	{
		destKey = srcKey;
		destData = srcData;
	}

	static inline void DeleteData(KeyType& key, DataType& data)
	{
	}
};

*/

//-------------------------------------------------------------------------------------------------
// PairDataSetter ���� ��
//-------------------------------------------------------------------------------------------------
/*

class MyDataSetter
{
public:
	static inline void SetData(char*& destKey, int& destData, char*& srcKey, int& srcData) 
	{
		size_t size = strlen(key) + 1;
		char* pcString = NkAlloc(char, size);
        memcpy(pcString, key, size);
		
		destKey = pcString;
		destData = data;
	}

	static inline void DeleteData(char*& key, int& data) 
	{
		NkFree( key );
	};
};

*/

//-------------------------------------------------------------------------------------------------
// NkHashMapNode
//-------------------------------------------------------------------------------------------------
template <class TKey, class TData>
class NkHashMapNode : public NkMemory
{
public:
	TKey& GetKey() { return m_key; }
	TData& GetData() { return m_data; }

	NkHashMapNode* m_pkNext;
	TKey m_key;
	TData m_data;
};

//-------------------------------------------------------------------------------------------------
// NkHashMap_Iterator
//-------------------------------------------------------------------------------------------------
template <class TKey, class TData>
class NkHashMap_Iterator : public NkMemory
{
public:
	typedef NkHashMapNode<TKey,TData> _Node;
	typedef NkHashMap_Iterator<TKey,TData> _Iter;
	typedef NkVector<_Node*> _HashTable;

	NkHashMap_Iterator() : m_pkNode(0), m_pkHashTable(0), m_uiHashIndex(0) {};
	NkHashMap_Iterator(_Node* pkNode) { m_pkNode = pkNode; }

	_Node& operator*() const { return *m_pkNode; }
	_Node* operator->() const { return m_pkNode; }

	inline void _Next();
	_Iter& operator++() { _Next(); return (*this); }
	_Iter operator++(int) { _Node* pkTemp = m_pkNode; _Next(); return pkTemp; }

	bool operator==(const _Iter& kRight) const { return m_pkNode == kRight.m_pkNode; }
	bool operator!=(const _Iter& kRight) const { return m_pkNode != kRight.m_pkNode; }

	bool IsValid() { return m_pkNode != 0; }
	_Node* GetNodePtr() { return m_pkNode; }
	unsigned int GetHashIndex() { return m_uiHashIndex; }
	
	_Node* m_pkNode;
	_HashTable* m_pkHashTable;
	unsigned int m_uiHashIndex;	
};

//-------------------------------------------------------------------------------------------------
// NkHashMap
//-------------------------------------------------------------------------------------------------
template <class TKey, class TData,
          class THash = NkHashFunctor<TKey>,
		  class TEquals = NkEqualsFunctor<TKey>,
		  class TDataSetter = NkPairDataSetter<TKey, TData> >
class NkHashMap : public NkMemory
{
public:
	typedef NkHashMapNode<TKey,TData>* NodePtr;
	typedef NkHashMap_Iterator<TKey,TData> Iterator;

	NkHashMap(unsigned int uiHashSize = 37);
	~NkHashMap();

	// ũ�� ���� �Լ�
	inline unsigned int GetHashSize() const;
	inline unsigned int GetCount() const;
	inline unsigned int GetAllocedBytes() const;

	// Ư�� �ؽ� �ε����� ��� ���� ���
	inline unsigned int GetNodeCount(unsigned int uiHashIndex) const;
	
	// ��ġ ���� �Լ�
	inline bool GetBegin( Iterator& kIter) const;
	inline bool GetNext( Iterator& kIter) const;

	// ������ �Է� �Լ�
	inline void SetAt(const TKey& key, const TData& data);
	inline void SetAt(const TKey& key, const TData* pData);

	inline void SetData(const Iterator& kIter, const TData& data);
	inline void SetData(const Iterator& kIter, const TData* pData);

	// Ư�� HashIndex�� ������ �߰��ϱ�
	// �����Ͽ� ���:
	//     Find �Լ��� ���� ȣ�� �Ͽ� ��ȯ���� false�� ���(������ Ű�� ���� ���)����
	//     Find �Լ����� ���� Iterator�� ����Ͽ� Insert �Լ��� ȣ���� ��

	inline void Insert( Iterator& kIter, const TKey& key, const TData& data);
	inline void Insert( Iterator& kIter, const TKey& key, const TData* pData);

	// ���� �Լ�
	inline bool Remove(const TKey& key);
	inline bool Remove( Iterator& kIter);
	inline void RemoveAll();

	// ������ ���� �Լ�
	inline bool GetData(const TKey& key,  TData& data) const;
	inline TData* GetDataPtr(const TKey& key) const;

	// �˻� �Լ�
	inline bool Find(const TKey& key,  Iterator& kIter) const;

protected:
	inline NodePtr _NewNode();
	inline void _DeleteNode(NodePtr pkNode);

	unsigned int m_uiHashSize;
	unsigned int m_uiCount;
	
	NkVector<NodePtr>* m_pkHashTable;
};

#include "NkHashMap.inl"
