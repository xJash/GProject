//-------------------------------------------------------------------------------------------------
// NkQueue.h
// �������� ���������
// ������
//-------------------------------------------------------------------------------------------------

#pragma once

#include "NkCore.h"

//-------------------------------------------------------------------------------------------------
// NkQueue Iterator
//-------------------------------------------------------------------------------------------------
template <class T>
class NkQueue_Iterator
{
public: 
	typedef NkQueue_Iterator<T> _Iter;

	NkQueue_Iterator() : pT(0) {};

	T& operator*() const { return (T&)*pT; }
	T* operator->() const { return (T*)pT; }

	_Iter& operator++() { ++pT; return (*this); }
	_Iter operator++(int) { T* pTemp = pT; ++pT; return (_Iter)pTemp; }

	_Iter& operator--() { --pT; return (*this); }
	_Iter operator--(int) { T* pTemp = pT; --pT; return (_Iter)pTemp; }

	bool operator==(const _Iter& kRight) const { return pT == kRight.pT; }
	bool operator!=(const _Iter& kRight) const { return pT != kRight.pT; }

	T* pT;
};

//-------------------------------------------------------------------------------------------------
// NkQueue
//-------------------------------------------------------------------------------------------------
template <class T>
class NkQueue : public NkMemory
{
public:
	static const unsigned int GROWSIZE_DOUBLE = (unsigned int)-1;
	static const unsigned int MAXSIZE_DEFAULT = (unsigned int)-1;

	NkQueue(unsigned int uiInitSize = 0, unsigned int uiMaxSize = MAXSIZE_DEFAULT, unsigned int uiGrowSize = GROWSIZE_DOUBLE);
	~NkQueue();

	// ũ�� ���� �Լ�
	inline unsigned int GetCount() const;
	inline unsigned int GetAllocedCount() const;
	inline unsigned int GetAllocedBytes() const;


	// ���� ���� �Լ�
	inline bool IsEmpty() const;
	inline bool IsFull() const;

	// ����
	bool Push(const T& data);			// PushBack

	// ����
	inline void Pop();					// PopFront
	inline bool Pop(T& data);			// PopFront

	void RemoveAll();

	// ������ ���� �Լ�
	inline T& GetData() const;			// GetFrontData
	inline T* GetDataPtr() const;		// GetFrontDataPtr

	inline T& GetData(unsigned int uiIndex) const;			// �ε��� 0 = Front
	inline T* GetDataPtr(unsigned int uiIndex) const;		// �ε��� 0 = Front

	inline T& operator[] (unsigned int uiIndex) const;		// �ε��� 0 = Front

	inline T* getbaseptr() { return m_pBase; }
	inline unsigned int getfrontpos() { return m_uiFrontPos; }
	inline unsigned int getbackpos() { return m_uiBackPos; }

protected:
	inline void _Realloc(unsigned int uiNewSize);

	unsigned int m_uiAllocedSize;
	unsigned int m_uiGrowSize;
	unsigned int m_uiMaxSize;

	unsigned int m_uiCount;
	unsigned int m_uiFrontPos;
	unsigned int m_uiBackPos;

	T* m_pBase;
};

#include "NkQueue.inl"
