// XMemory.h
/*!
\file					XMemory.h

\remarks				XSystem Library���� �����ϴ� Memory Pool�� �Ʒ��� ���� Ư¡�� ������.
						- Memory Pool�� ���������ν� �޸� �Ҵ�, ���� �۾��� ȿ������ ���δ�.
						- Memory Pool�κ��� �Ҵ�� �޸𸮴� XMemory ��ü�� �����ȴ�.
						- XMemory�� reference counting ����� �⺻ �����Ѵ�.
						- XMemory�� ���� ����� shallow copy�� �⺻�����ϸ�, �̸� ���� �޸� �Ҵ� �� ������ overhead�� ���δ�.

- Required header: <XBase/XSystem/XMemory.h>
*/

#ifndef __XMemory_Old__
#define __XMemory_Old__

#include "XSystemBase.h"
#include <Windows.h>

class XMemory;

/*!
\brief					���ο� �޸𸮸� �Ҵ��Ѵ�.

\param dwSize			[in] �Ҵ��� �޸� ũ��

\return					���� �Ҵ�� XMemory ��ü

\sa						XMemory, XMemoryFree, XMemoryRealloc, XMemoryClone, XMemorySize
*/
XSYSTEM_API XMemory __stdcall XMemoryAlloc(DWORD dwSize);

/*!
\brief					�Ҵ�� �޸𸮸� �����Ѵ�.

\param rMem				[in] ������ XMemory ��ü

\return					This function does not return a value.
*/
XSYSTEM_API void __stdcall XMemoryFree(XMemory& rMem);

/*!
\brief					�Ҵ�� �޸��� ũ�⸦ �����Ѵ�.

\param rMem				[in] �޸� ũ�⸦ ������ XMemory ��ü

\param dwNewSize		[in] ����� �޸� ũ��

\return					�޸� ũ�Ⱑ ����� XMemory ��ü
*/
XSYSTEM_API XMemory __stdcall XMemoryRealloc(XMemory& rMem, DWORD dwNewSize);

/*!
\brief					�Ҵ�� �޸𸮸� �����Ѵ�.

\param rMem				[in] ������ �ҽ� XMemory ��ü

\return					����� XMemory ��ü

\remarks				�̶� ����� �ҽ� XMemory ��ü�� �Ҵ�� �޸� ���� ������ ũ���� �޸� ���� 
						Memory Pool�κ��� �Ҵ�ǰ� �޸� ���� ������ ����Ǵ� deep copy�� �ǹ��Ѵ�.
*/
XSYSTEM_API XMemory __stdcall XMemoryClone(XMemory& rMem);

/*!
\brief					�Ҵ�� �޸��� ũ�⸦ ��ȯ�Ѵ�.

\param rMem				[in] �Ҵ�� �޸��� ũ�⸦ ���� XMemory ��ü

\return					�Ҵ�� �޸� ũ��
*/
XSYSTEM_API DWORD __stdcall XMemorySize(XMemory& rMem);


struct MEMORY_BLOCK;
typedef MEMORY_BLOCK* PMEMORY;


/*!
	\brief				Memory Pool���� �Ҵ�� �޸𸮸� �����ϴ� class
	\remarks			XMemoryAlloc �Լ��� �̿��Ͽ� Memory Pool�κ��� �Ҵ�� �޸𸮴� XMemory ��ü�� �����ȴ�. \n
						\n
						XSystem Library���� �����ϴ� Memory Pool�� �Ʒ��� ���� Ư¡�� ������.
						- Memory Pool�� ���������ν� �޸� �Ҵ�, ���� �۾��� ȿ������ ���δ�.
						- Memory Pool�κ��� �Ҵ�� �޸𸮴� XMemory ��ü�� �����ȴ�.
						- XMemory�� reference counting ����� �⺻ �����Ѵ�.
						- XMemory�� ���� ����� shallow copy�� �⺻�����ϸ�, �̸� ���� �޸� �Ҵ� �� ������ overhead�� ���δ�.

	- Required header: <XBase/XSystem/XMemory.h>
*/
class XSYSTEM_API XMemory
{
public:
	/*!
	\brief					defualt constructor

	\remarks				NULL �����͸� ������ XMemory ��ü�� �����Ѵ�.
	*/
	XMemory();

	/*!
	\brief					copy constructor

	\param	rhs				[in] ���� ������ �ҽ� XMemory ��ü

	\remarks				Ư�� XMemory ��ü�� ���� �����Ѵ�. \n
							�̶� ����� �ܼ��� reference count�� ������Ű�� shallow copy�� �ǹ��ϸ�, 
							������ XMemory ��ü�� �ҽ� XMemory ��ü�� ������ �޸� ���� ����Ű�� �ȴ�.
	*/
    XMemory(const XMemory &rhs);

	/*!
	\brief					destructor

	\remarks				XMemory�� �Ҵ�� �޸� ���� ������ ��� XMemoryFree�� ����Ͽ� ���� �۾��� �����Ѵ�.

	\sa						XMemoryFree, XMemoryAlloc
	*/
	~XMemory();

	/*!
	\brief					�Ҵ�� �޸� ���� const void* Ÿ������ ��ȯ�Ѵ�.

	\param					This function has no parameters.

	\return					�Ҵ�� �޸� ���� ���� const void* Ÿ��

	\sa						XMemorySize, XMemoryAlloc, XMemoryFree
	*/
	const void* GetData() const;

	/*!
	\brief					�Ҵ�� �޸� ���� void* Ÿ������ ��ȯ�Ѵ�.

	\param					This function has no parameters.

	\return					�Ҵ�� �޸� ���� ���� void* Ÿ��

	\sa						operator const void*, XMemorySize, XMemoryAlloc, XMemoryFree
	*/
	void* GetData();

	/*!
	\brief					�Ҵ�� �޸��� ũ�⸦ ��ȯ�Ѵ�.

	\param					This function has no parameters.

	\return					�Ҵ�� �޸��� ũ��

	\sa						operator void*, XMemorySize, XMemoryAlloc, XMemoryFree
	*/
	DWORD GetSize() const;

	/*!
	\brief					�޸� ���� �Ҵ���� ���� XMemory ��ü���� �˻��Ѵ�.

	\param					This function has no parameters.

	\return					BOOL
							- TRUE: �޸� ���� �Ҵ���� ���� XMemory ��ü, NULL �����͸� ����Ű�� �ִ�.
							- FALSE: �Ҵ�� �޸𸮸� ������ �ִ� XMemory ��ü

	\sa						XMemoryAlloc, XMemoryFree
	*/
	BOOL IsEmpty() const;


	/*!
	\brief					XMemory ��ü�� ���� assign operator

	\param rMem				[in] assign�� right-hand side�� XMemory ��ü

	\return					assign�� left-hand side�� XMemory ��ü

	\remarks				XMemory ��ü�� ���� assign operator�� right-hand side�� XMemory ��ü�� �޸� ���� 
							left-hand side ��ü�� �޸� ������ �����ϴ� ������ �ǹ��Ѵ�. 
							�̶� ����� �ܼ��� reference count�� ������Ű�� shallow copy�� �ǹ��ϸ�, 
							left-hand side�� XMemory ��ü�� right-hand side�� XMemory ��ü�� ������ �޸� ���� ����Ű�� �ȴ�. \n
							���� assign operator�� ȣ��� ������ left-hand side�� XMemory ��ü�� �̹� �Ҵ�� �޸� ���� 
							������ �ִ� ��� ������ �ִ� �޸� ���� XMemoryFree �Լ��� ������ �� right-hand side�� 
							XMemory ��ü�� �޸� ���� shallow copy �Ѵ�.

	\sa						XMemoryClone, XMemoryAlloc, XMemoryFree
	*/
	XMemory& operator = (const XMemory& rMem);

	/*!
	\brief					������ �޸� ���� ����Ű�� XMemory���� �˻��Ѵ�.

	\param rMem				[in] ���� XMemory ��ü

	\return					BOOL
							- TRUE: ������ �޸� ���� ����Ű�� �ִ�.
							- FALSE: ���� �ٸ� �޸� ���� ����Ű�� �ִ�.

	\sa						operator ==, XMemoryAlloc, XMemoryFree
	*/
	BOOL operator == (const XMemory& rMem) const;

	/*!
	\brief					������ �޸� ���� ����Ű�� XMemory�� �ƴ��� �˻��Ѵ�.

	\param rMem				[in] ���� XMemory ��ü

	\return					BOOL
							- TRUE: ���� �ٸ� �޸� ���� ����Ű�� �ִ�.
							- FALSE: ������ �޸� ���� ����Ű�� �ִ�.

	\sa						operator ==, XMemoryAlloc, XMemoryFree
	*/
	BOOL operator != (const XMemory& rMem) const;


	/*!
	\brief					�Ҵ�� �޸� ���� const void* �ڷ������� access�ϱ� ���� casting operator

	\param					This function has no parameters.

	\return					const void* �ڷ������� casting�� �޸� ��

	\sa						operator void*, XMemoryAlloc, XMemoryFree
	*/
	operator const void*() const;

	/*!
	\brief					�Ҵ�� �޸� ���� void* �ڷ������� access�ϱ� ���� casting operator

	\param					This function has no parameters.

	\return					void* �ڷ������� casting�� �޸� ��

	\sa						operator const void*, XMemoryAlloc, XMemoryFree
	*/
	operator void*();

private:
	explicit XMemory(PMEMORY pMem);

	BOOL Alloc(DWORD dwSize);
	BOOL Realloc(DWORD dwNewSize);
	void Free();
	XMemory Clone();

	inline static PMEMORY InternalAlloc(DWORD dwSize);

	friend XSYSTEM_API XMemory __stdcall XMemoryAlloc(DWORD dwSize);
	friend XSYSTEM_API void __stdcall XMemoryFree(XMemory& rMem);
	friend XSYSTEM_API XMemory __stdcall XMemoryRealloc(XMemory& rMem, DWORD dwNewSize);
	friend XSYSTEM_API XMemory __stdcall XMemoryClone(XMemory& rMem);

private:
	PMEMORY m_pMem;
};

inline BOOL operator == (const void* lhs, const XMemory& rhs)
{
	return (rhs == lhs);
}

#endif //__XMemory__
