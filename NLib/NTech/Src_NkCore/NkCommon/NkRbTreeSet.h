//-------------------------------------------------------------------------------------------------
// NkRbTreeSet.h
// �������� ���������
// ������
//-------------------------------------------------------------------------------------------------

#pragma once

#include "NkMemory.h"
#include "NkVector.h"

typedef void* NkRbTreeSetPos;

template <class T>
class NkRbTreeSetNode : public NkMemory
{
public:
	T* GetDataPtr() { return &m_data; }
	T& GetData() { return m_data; }

	bool IsRedNode() { return m_bRed; }

	NkRbTreeSetNode* m_pkParent;
	NkRbTreeSetNode* m_pkLeft;
	NkRbTreeSetNode* m_pkRight;

	T m_data;

	bool m_bRed;
};

class NkRbTreeSetPosVector : public  NkVector<NkRbTreeSetPos>
{
public:
	NkRbTreeSetPosVector(){};
};


template <class T, class TComp = NkCompareFunctor<T> >
class NkRbTreeSet : public NkMemory
{
public:
	NkRbTreeSet();
	~NkRbTreeSet();

	// ũ�� ���� �Լ�
	inline unsigned int GetCount() const;
	inline unsigned int GetAllocedBytes() const;
	inline unsigned int GetMaxDepth() const;

	// ��ġ ���� �Լ�
	inline bool InvalidPos(NkRbTreeSetPos kPos) const;

	inline NkRbTreeSetPos GetRootPos() const;
	inline NkRbTreeSetPos GetParentPos(NkRbTreeSetPos kPos) const;
	inline NkRbTreeSetPos GetLeftChildPos(NkRbTreeSetPos kPos) const;
	inline NkRbTreeSetPos GetRightChildPos(NkRbTreeSetPos kPos) const;

	NkRbTreeSetPos GetBeginPos() const;
	NkRbTreeSetPos GetEndPos() const;
	NkRbTreeSetPos GetNextPos(NkRbTreeSetPos kPos) const;
	NkRbTreeSetPos GetPrevPos(NkRbTreeSetPos kPos) const;

	NkRbTreeSetPosVector* BuildMapPosVector();

	// ������ ���� �Լ�
	inline bool IsRedNode(NkRbTreeSetPos kPos) const;

	inline T& GetData(NkRbTreeSetPos kPos) const;
	inline T* GetDataPtr(NkRbTreeSetPos kPos) const;

	// ���� (�̹� ������ Key�� �����ϴ� ��� false��ȯ)
	bool Insert(const T& data);

	// ����
	bool Remove(const T& data);
	void RemoveAll();

	// �˻�
	NkRbTreeSetPos FindPos(const T& data) const;
	bool FindData(const T& data) const;

protected:
	inline NkRbTreeSetNode<T>* _FindMin(NkRbTreeSetNode<T>* pkNode) const;
	inline NkRbTreeSetNode<T>* _FindMax(NkRbTreeSetNode<T>* pkNode) const;
	inline NkRbTreeSetNode<T>* _FindPrev(NkRbTreeSetNode<T>* pkNode) const;
	inline NkRbTreeSetNode<T>* _FindNext(NkRbTreeSetNode<T>* pkNode) const;
	inline NkRbTreeSetNode<T>* _Find(const T& data) const;

	inline void _InsertFixup(NkRbTreeSetNode<T>* pkNode);
	inline void _RemoveFixup(NkRbTreeSetNode<T>* pkNode);

	inline void _RotateLeft(NkRbTreeSetNode<T>* pkNode);
	inline void _RotateRight(NkRbTreeSetNode<T>* pkNode);

	void _RemoveRecursive(NkRbTreeSetNode<T>* pkNode);

	NkRbTreeSetNode<T>* _NewNode();
	void _DeleteNode(NkRbTreeSetNode<T>* pkNode);

	NkRbTreeSetNode<T>* NIL;
	NkRbTreeSetNode<T>* m_pkRoot;

	unsigned int m_uiCount;

	NkRbTreeSetPosVector m_kPosVector;
};

#include "NkRbTreeSet.inl"