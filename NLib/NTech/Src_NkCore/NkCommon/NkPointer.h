//-------------------------------------------------------------------------------------------------
// NkPointer.h
// �������� ���������
// ������
//-------------------------------------------------------------------------------------------------

#pragma once

#include "NkMemory.h"

//-------------------------------------------------------------------------------------------------
// ���� ������
// ���� �ܺο��� �������� ���� �����͸� ��������� ����ϱ� ���� ���ø�
//-------------------------------------------------------------------------------------------------
template <class T>
class NkRefPtr
{
public:
	inline NkRefPtr(T* pObject = (T*)0) { m_pObject = pObject; }

	inline operator T*() const { return m_pObject; }
	inline T& operator*() const { return *m_pObject; }
	inline T* operator->() const { return m_pObject; }

	inline NkRefPtr& operator=(T* pObject) { m_pObject = pObject; return *this; }

	inline bool operator==(const T* pObject) const { return m_pObject == pObject; }
	inline bool operator!=(const T* pObject) const { return m_pObject != pObject; }

	inline bool IsValid() { return (m_pObject) ? true : false; }

protected:
	T* m_pObject;
};

//-------------------------------------------------------------------------------------------------
// �ڵ� ��ü ������ ���ø�
// ��ü�� �Ҹ��� �ڵ����� �������ش� 
//-------------------------------------------------------------------------------------------------
template <class T> 
class NkAutoPtr : public NkMemory
{
public:
	inline NkAutoPtr(T* pObject = (T*)0) { m_pObject = pObject; }
	inline ~NkAutoPtr() { if( m_pObject ) NkDelete m_pObject; m_pObject = 0; }

	inline operator T*() const { return m_pObject; }
	inline T& operator*() const { return *m_pObject; }
	inline T* operator->() const { return m_pObject; }

	inline NkAutoPtr& operator=(T* pObject);

	inline bool operator==(const T* pObject) const { return m_pObject == pObject; }
	inline bool operator!=(const T* pObject) const { return m_pObject != pObject; }

	inline bool IsValid() { return (m_pObject) ? true : false; }

	void Delete();

protected:
	T* m_pObject;
};


template <class T>
inline NkAutoPtr<T>& NkAutoPtr<T>::operator=(T* pObject)
{
	if( m_pObject != pObject )
	{
		if( m_pObject ) NkDelete m_pObject;
		m_pObject = pObject;
	}
	return *this;
}

template <class T>
inline void NkAutoPtr<T>::Delete()
{
	if( m_pObject ) NkDelete m_pObject;
	m_pObject = 0;
}


//-------------------------------------------------------------------------------------------------
// �ڵ� �迭 ������ ���ø�
// �迭 �޸� �Ҹ��� �ڵ����� �������ش� 
//-------------------------------------------------------------------------------------------------
template <class T> 
class NkArrayPtr : public NkMemory
{
public:
	inline NkArrayPtr(T* pObject = (T*)0) { m_pObject = pObject; }
	inline ~NkArrayPtr() { if( m_pObject ) NkDelete [] m_pObject; m_pObject = 0; }

	inline operator T*() const { return m_pObject; }
	inline T& operator*() const { return *m_pObject; }
	inline T* operator->() const { return m_pObject; }

	inline NkArrayPtr& operator=(T* pObject);

	inline bool operator==(const T* pObject) const { return m_pObject == pObject; }
	inline bool operator!=(const T* pObject) const { return m_pObject != pObject; }

	inline bool IsValid() { return m_pObject; }

	void Delete();

protected:
	T* m_pObject;
};

template <class T>
inline NkArrayPtr<T>& NkArrayPtr<T>::operator=(T* pObject)
{
	if( m_pObject != pObject )
	{
		if( m_pObject ) NkDelete [] m_pObject;
		m_pObject = pObject;
	}
	return *this;
}

template <class T>
inline void NkArrayPtr<T>::Delete()
{
	if( m_pObject ) NkDelete [] m_pObject;
	m_pObject = 0;
}

//-------------------------------------------------------------------------------------------------
// ���۷��� ������Ʈ ���ø�
// ����Ʈ �����͸� ����ϱ� ����, ��ü�� ī���� ������ ���� �ϱ� ���ؼ� ����Ѵ�
//-------------------------------------------------------------------------------------------------
class NkRefObject : public NkMemory
{
public:
	NkRefObject() : m_uiRefCount(0) {};
	virtual ~NkRefObject() {};

	inline void IncRefCount() { ++m_uiRefCount; }
	inline void DecRefCount() { if( --m_uiRefCount == 0 ) NkDelete this; }

	inline unsigned int GetRefCount() const { return m_uiRefCount; }

private:
	unsigned int m_uiRefCount;
};

//-------------------------------------------------------------------------------------------------
// ����Ʈ ������ ���ø�
// ��ü�� ���۷��� ī������ ������ ������, ���۷��� ī��Ʈ�� 0�̵� ��쿡 �ڵ����� �Ҹ��Ų��
//-------------------------------------------------------------------------------------------------
template <class T>
class NkSmartPtr : public NkMemory
{
public:
	inline NkSmartPtr(T* pObject = (T*)0);
	inline explicit NkSmartPtr(const NkSmartPtr& ptr);
	inline ~NkSmartPtr();

	inline operator T*() const { return m_pObject; }
	inline T& operator*() const { return *m_pObject; }
	inline T* operator->() const { return m_pObject; }

	inline NkSmartPtr& operator=(const NkSmartPtr& ptr);
	inline NkSmartPtr& operator=(T* pObject);

	inline bool operator==(const T* pObject) const { return m_pObject == pObject; }
	inline bool operator!=(const T* pObject) const { return m_pObject != pObject; }
	inline bool operator==(const NkSmartPtr& ptr) const { return m_pObject == ptr.m_pObject; }
	inline bool operator!=(const NkSmartPtr& ptr) const { return m_pObject != ptr.m_pObject; }

protected:
	T* m_pObject;
};

template <class T> inline
NkSmartPtr<T>::NkSmartPtr(T* pObject)
{
	m_pObject = pObject;
	if( m_pObject ) m_pObject->IncRefCount();
}

template <class T> inline
NkSmartPtr<T>::NkSmartPtr(const NkSmartPtr& ptr)
{
	m_pObject = ptr.m_pObject;
	if( m_pObject ) m_pObject->IncRefCount();
}

template <class T> inline
NkSmartPtr<T>::~NkSmartPtr()
{
	if( m_pObject ) m_pObject->DecRefCount();
}

template <class T> inline
NkSmartPtr<T>& NkSmartPtr<T>::operator=(T* pObject)
{
	if (m_pObject != pObject)
	{
		if( m_pObject ) m_pObject->DecRefCount();
		m_pObject = pObject;
		if( m_pObject ) m_pObject->IncRefCount();
	}
	return *this;
}

template <class T> inline
NkSmartPtr<T>& NkSmartPtr<T>::operator=(const NkSmartPtr& ptr)
{
	if( m_pObject != ptr.m_pObject )
	{
		if( m_pObject ) m_pObject->DecRefCount();
		m_pObject = ptr.m_pObject;
		if( m_pObject ) m_pObject->IncRefCount();
	}
	return *this;
}
