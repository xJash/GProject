// XObjectPool.h
/*!
\file		XObjectPool.h
*/

#ifndef __XObjectPool_Old__
#define __XObjectPool_Old__

#include "XSyncObject.h"
#include <vector>
#include <cassert>

#pragma warning(disable:4345)


/********************************************************************************
	class XObjectPool<T>
********************************************************************************/
/*!
	\brief				����� �߻��ϴ� Ư�� object�� ����, �Ҹ� �۾��� ȿ������ ���� pooling ����� �����ϴ� class

	- Required header: <XBase/XSystem/XObjectPool.h>
*/
template <typename T>
class XObjectPool
{
public:
	/*! \brief defualt constructor */
	XObjectPool();

	/*! \brief distructor */
	virtual ~XObjectPool();


	/*!
	\brief					XObjectPool ��ü�� object�� ����� ���ҽ��� �ּ� ������ reserve �Ѵ�.

	\param dwCount			[in] pool�� �̸� ������ object�� ���ҽ� �ּ� ����
							- Default: 0(zero)

	\param dwMaximumFreeObj	[in] �ݳ��� object�� �޸𸮸� �������� �ʰ� pool���� ������ �ִ� ���� 
							- Default: �ִ밪�� ���� �������� �ʴ´�.

	\return					BOOL
							- TRUE: ���� ����
							- FALSE: ���� ����
	*/
	BOOL Reserve(DWORD dwCount);

	/*!
	\brief					XObjectPool ��ü�� ���ҽ��� �����Ѵ�.

	\param					This function has no parameters.

	\return					This function does not return a value.

	\remarks				Clear �Լ��� XObjectPool ��ü�� �ݳ��� object�� ���� ���ҽ����� ������� �Ѵ�.
							��, XObjectPool ��ü�κ��� Alloc �Լ��� �Ҵ��� �� Free �Լ��� ���� �ݳ����� ���� 
							object�� ���ҽ��� ���ؼ��� �������� �ʴ´�.
	*/
	void Clear();


	/*!
	\brief					pool�κ��� object�� �Ҵ��Ѵ�.

	\param					This function has no parameters.

	\return					�Ҵ�� object�� pointer

	\remarks				Alloc �Լ��� ���� object �Ҵ�� object�� defualt constructor�� ȣ��ȴ�.
	*/
	inline T* Alloc();

	/*!
	\brief					�Ҵ��� object�� pool�� �ݳ��Ѵ�.

	\param					�ݳ��� object�� pointer

	\return					This function does not return a value.

	\remarks				Free �Լ��� ���� object �ݳ��� object�� distructor�� ȣ��ȴ�.
	*/
	inline void Free(T* pObject);

protected:
	DWORD m_dwMaximumFreeObj;
	std::vector<void*> m_pool;
	XCriticalSection m_cs;
};


/********************************************************************************
	class XObjectPool<T> Impl
********************************************************************************/
template <typename T>
XObjectPool<T>::XObjectPool()
	: m_dwMaximumFreeObj((DWORD)-1)
{
}

template <typename T>
XObjectPool<T>::~XObjectPool()
{
	Clear();
}

template <typename T>
BOOL XObjectPool<T>::Reserve(DWORD dwCount)
{
	XLock guard(m_cs);
	void* p = NULL;

	Clear();

	m_pool.reserve(dwCount);
	while (m_pool.size() < dwCount)
	{
		p = ::malloc(sizeof(T));
		if (NULL == p)
		{
			Clear();
			return FALSE;
		}
		m_pool.push_back(p);
	}

	return TRUE;
}

template <typename T>
void XObjectPool<T>::Clear()
{
	XLock guard(m_cs);
	void* p = NULL;

	while (!m_pool.empty())
	{
		p = m_pool.back();
		m_pool.pop_back();
		if (NULL != p)
			free(p);
	}
}

template <typename T>
T* XObjectPool<T>::Alloc()
{
	XLock guard(m_cs);
	T* p = NULL;

	if (m_pool.empty())
	{
		p = (T*)malloc(sizeof(T));
	}
	else
	{
		p = (T*)m_pool.back();
		m_pool.pop_back();
	}

	if (NULL != p)
		new (p) T();

	return p;
}

template <typename T>
void XObjectPool<T>::Free(T* p)
{
	if (NULL == p)
		return;

	XLock guard(m_cs);

	p->~T();
	if (((DWORD)-1 == m_dwMaximumFreeObj) || (m_pool.size() < m_dwMaximumFreeObj))
	{
#ifdef _DEBUG
		memset(p, 0xCC, sizeof(T));
#endif
		m_pool.push_back(p);
	}
	else
		free(p);
}


#pragma warning(default:4345)

#endif //__XObjectPool__
