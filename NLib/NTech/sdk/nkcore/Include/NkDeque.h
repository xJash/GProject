//-------------------------------------------------------------------------------------------------
// NkDeque.h
// �������� ���������
// ������
//-------------------------------------------------------------------------------------------------

#pragma once

#include "NkCore.h"

template <class T>
class NkDeque : public NkMemory
{
public:
	static const unsigned int GROWSIZE_DOUBLE = (unsigned int)-1;
	static const unsigned int MAXSIZE_DEFAULT = (unsigned int)-1;

	NkDeque(unsigned int uiInitSize = 0, unsigned int uiMaxSize = MAXSIZE_DEFAULT, unsigned int uiGrowSize = GROWSIZE_DOUBLE);
	~NkDeque();

	// ũ�� ���� �Լ�
	inline unsigned int GetCount() const;
	inline unsigned int GetAllocedCount() const;
	inline unsigned int GetAllocedBytes() const;

	// ���� ���� �Լ�
	inline bool IsEmpty() const;
	inline bool IsFull() const;

	// ����
	bool PushFront(const T& data);
	bool PushBack(const T& data);

	// ����
	inline void PopFront();
	inline void PopBack();

	inline bool PopFront(T& data);
	inline bool PopBack(T& data);

	void RemoveAll();

	// ������ ���� �Լ�
	inline T& GetFrontData() const;
	inline T& GetBackData() const;

	inline T* GetFrontDataPtr() const;
	inline T* GetBackDataPtr() const;

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

	unsigned int m_uiFrontPos;
	unsigned int m_uiBackPos;

	unsigned int m_uiCount;

	T* m_pBase;
};

#include "NkDeque.inl"
