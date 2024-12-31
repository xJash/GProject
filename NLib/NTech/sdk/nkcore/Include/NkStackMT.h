//-------------------------------------------------------------------------------------------------
// NkStackMT.h
// �������� ���������
// ������
//-------------------------------------------------------------------------------------------------

#pragma once

#include "NkCore.h"

template <class T>
class NkStackMT : public NkMemory
{
public:
	static const unsigned int GROWSIZE_DOUBLE = (unsigned int)-1;
	static const unsigned int MAXSIZE_DEFAULT = (unsigned int)-1;

	NkStackMT(unsigned int uiInitSize = 1, unsigned int uiMaxSize = MAXSIZE_DEFAULT, unsigned int uiGrowSize = GROWSIZE_DOUBLE);
	~NkStackMT();

	inline unsigned int GetCount() const;
	inline unsigned int GetAllocedCount() const;
	inline unsigned int GetAllocedBytes() const;

	inline bool IsEmpty();
	inline bool IsFull();

	inline void RemoveAll();

	bool Push(const T& data);
	inline bool Pop(T& data);
	inline void Pop();

	void Realloc(unsigned int uiNewSize = 0, unsigned int uiGrowSize = GROWSIZE_DOUBLE, unsigned int uiMaxSize = MAXSIZE_DEFAULT);

	inline T* getbaseptr() { return m_pBase; }

protected:
	inline void _Realloc(unsigned int uiNewSize);

	unsigned int m_uiAllocedSize;
	unsigned int m_uiGrowSize;
	unsigned int m_uiMaxSize;

	unsigned int m_uiCount;

	T* m_pBase;

	CRITICAL_SECTION m_cs;
};

#include "NkStackMT.inl"
