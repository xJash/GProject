// XSyncObject.h
/*!
\file		XSyncObject.h
*/

#ifndef __XSyncObject_Old__
#define __XSyncObject_Old__

#include "XSystemBase.h"
#include <Windows.h>
#include <vector>

/********************************************************************************
	class XSyncObject
********************************************************************************/
/*!
\brief					synchronization objects�� ���� ����� ������ pure virtual class
\remarks				XCriticalSection, XMutex, XSemaphore, XEvent�� XSyncObject�� ��ӹ޾� �����Ǿ� �ִ�.

						- Required header: <XBase/XSystem/XSyncObject.h>

\sa						XCriticalSection, XMutex, XSemaphore, XEvent
*/
class XSYSTEM_API XSyncObject
{
public:
	/*! \brief ȣ���� thread�� XSyncObject�� ownership�� ������� ����Ѵ�. */
	virtual BOOL Lock(DWORD dwMilliseconds = INFINITE) = 0;

	/*! \brief ȣ���� thread�� ������ XSyncObject�� ownership�� releases �Ѵ�. */
	virtual BOOL Unlock() = 0;
};

/********************************************************************************
	class XCriticalSection
********************************************************************************/
/*!
\brief					CRITICAL_SECTION object�� ���� wrapper class

\remarks
						- Required header: <XBase/XSystem/XSyncObject.h>

\sa						XSyncObject, XMutex, XSemaphore, XEvent
*/
class XSYSTEM_API XCriticalSection : public XSyncObject
{
public:
	/*!
	\brief					defualt constructor
	\param dwSpinCount		[in] spin count
	*/
	explicit XCriticalSection(DWORD dwSpinCount = 4000);
	/*! \brief distructor */
	virtual ~XCriticalSection();

	/*! \brief ȣ���� thread�� critical section object�� ownership�� ������� ����Ѵ�. */
	void Enter();

	/*!
	\brief					ȣ���� thread�� critical section object�� ownership�� ������� �õ��Ѵ�.
	
	\return					
							- TRUE: ȣ���� thread�� critical section object�� ownership�� ȹ����.
									Leave �Ǵ� Unlock�� ȣ���Ͽ� ȹ���� ownership�� releases�� �־�� �Ѵ�.
							- FALSE: ȣ���� thread�� critical section object�� ownership�� ȹ������ �� ��
	*/
	BOOL TryEnter();

	/*! \brief ȣ���� thread�� ������ critical section object�� ownership�� releases �Ѵ�. */
	void Leave();

	/*! \brief ���� CRITICAL_SECTION ��ü�� pointer�� ��ȯ�Ѵ�. */
	operator CRITICAL_SECTION*();

	/*! \brief ���� CRITICAL_SECTION ��ü�� ���ڷ� ������ CRITICAL_SECTION object�� attach �Ѵ�. */
	void Attach(CRITICAL_SECTION* p);
	CRITICAL_SECTION Detach();

	/*! \brief Enter()�� ȣ���Ѵ�. */
	virtual BOOL Lock(DWORD dwMilliseconds = INFINITE);
	
	/*! \brief Leave()�� ȣ���Ѵ�. */
	virtual BOOL Unlock();

protected:
	struct Context;
	Context* m_pContext;
};

/********************************************************************************
	class XWaitableObject
********************************************************************************/
/*!
\brief					SYNCHRONIZE �＼�� ������ ������ handle�� ���� ���� ����� ������ class

\remarks
						- Required header: <XBase/XSystem/XSyncObject.h>

\sa						XMutex, XSemaphore, XEvent, XWaitableCollection
*/
class XSYSTEM_API XWaitableObject
{
public:
	/*! \brief defualt constructor */
	XWaitableObject();

	/*! \brief distructor */
	virtual ~XWaitableObject();

	/*! \brief ���� handle�� valid���� �˻��Ѵ�. */
	BOOL IsOpen() const;

	/*! \brief ���� handle�� ��ȯ�Ѵ�. */
	HANDLE GetHandle() const;

	/*! \brief ���� handle�� ��ȯ�Ѵ�. */
	operator HANDLE() const;

	/*! \brief ���� handle�� close �Ѵ�. */
	virtual void Close();

	/*!
	\brief					���� handle�� signaled state�� �ɶ����� ��ٸ���.
	\param dwMilliseconds	[in] Time-out interval, in milliseconds.
	\return					Win32 API�� WaitForSingleObject�� ����
	*/
	DWORD Wait(DWORD dwMilliseconds = INFINITE);

	/*!
	\brief					���� handle�� signaled state�� �ɶ����� ��ٸ���.
	\param bAlertable		[in] If this parameter is TRUE, the function returns when the system queues 
								an I/O completion routine or APC, and the thread runs the routine or function.
								If this parameter is FALSE, the function does not return, 
								and the completion routine or APC function is not executed.
	\param dwMilliseconds	[in] Time-out interval, in milliseconds.
	\return					Win32 API�� WaitForSingleObject�� ����
	*/
	DWORD WaitEx(BOOL bAlertable, DWORD dwMilliseconds = INFINITE);

	/*! \brief ���� handle�� hObject�� attach �Ѵ�. */
	virtual void Attach(HANDLE hObject);

	/*! \brief ���� handle�� detach �Ѵ�. */
	virtual HANDLE Detach();

protected:
	struct Context;
	Context* m_pContext;
};

/********************************************************************************
	class XMutex
********************************************************************************/
/*!
\brief					mutex object�� ���� wrapper class

\remarks
						- Required header: <XBase/XSystem/XSyncObject.h>

\sa						XSyncObject, XWaitableObject, XCriticalSection, XSemaphore, XEvent, XWaitableCollection
*/
class XSYSTEM_API XMutexA : public XWaitableObject, public XSyncObject
{
public:
	/*! \brief defualt constructor */
	XMutexA() {}

	/*! \brief distructor */
	virtual ~XMutexA() {}

	/*! \brief event object ���� */
	BOOL Create(BOOL bInitialOwner = FALSE, const char *pszName = NULL, LPSECURITY_ATTRIBUTES psa = NULL);

	/*! \brief �̹� ������ event object�� open �Ѵ�. */
	BOOL Open(const char *pszName = NULL, DWORD dwDesiredAccess = MUTEX_ALL_ACCESS, BOOL bInheritHandle = FALSE);

	/*! \brief event object�� Releases �Ѵ�. */
	BOOL Release();

	/*! \brief Wait�� ȣ���Ѵ�. */
	virtual BOOL Lock(DWORD dwMilliseconds = INFINITE);

	/*! \brief Release�� ȣ���Ѵ�. */
	virtual BOOL Unlock();
};

class XSYSTEM_API XMutexW : public XWaitableObject, public XSyncObject
{
public:
    /*! \brief defualt constructor */
    XMutexW() {}

    /*! \brief distructor */
    virtual ~XMutexW() {}

    /*! \brief event object ���� */
    BOOL Create(BOOL bInitialOwner = FALSE, const wchar_t *pszName = NULL, LPSECURITY_ATTRIBUTES psa = NULL);

    /*! \brief �̹� ������ event object�� open �Ѵ�. */
    BOOL Open(const wchar_t *pszName = NULL, DWORD dwDesiredAccess = MUTEX_ALL_ACCESS, BOOL bInheritHandle = FALSE);

    /*! \brief event object�� Releases �Ѵ�. */
    BOOL Release();

    /*! \brief Wait�� ȣ���Ѵ�. */
    virtual BOOL Lock(DWORD dwMilliseconds = INFINITE);

    /*! \brief Release�� ȣ���Ѵ�. */
    virtual BOOL Unlock();
};

#if !defined(UNICODE) && !defined(_UNICODE)
    typedef XMutexA XMutex;
#else
    typedef XMutexW XMutex;
#endif

/********************************************************************************
	class XSemaphore
********************************************************************************/
/*!
\brief					semaphore object�� ���� wrapper class

\remarks
						- Required header: <XBase/XSystem/XSyncObject.h>

\sa						XSyncObject, XWaitableObject, XCriticalSection, XMutex, XEvent, XWaitableCollection
*/
class XSYSTEM_API XSemaphoreA : public XWaitableObject, public XSyncObject
{
public:
	/*! \brief defualt constructor */
	XSemaphoreA() {}

	/*! \brief distructor */
	virtual ~XSemaphoreA() {}

	/*! \brief semaphore object ���� */
	BOOL Create(int nInitialCount, int nMaximumCount, const char *pszName = NULL, LPSECURITY_ATTRIBUTES psa = NULL);

	/*! \brief �̹� ������ semaphore object�� open �Ѵ�. */
	BOOL Open(const char *pszName = NULL, DWORD dwDesiredAccess = SEMAPHORE_ALL_ACCESS, BOOL bInheritHandle = FALSE);

	/*! \brief semaphore object�� Releases �Ѵ�. */
	BOOL Release(LONG nReleaseCount, LONG* pnPreviousCount = NULL);

	/*! \brief Wait�� ȣ���Ѵ�. */
	virtual BOOL Lock(DWORD dwMilliseconds = INFINITE);

	/*! \brief Release(1)�� ȣ���Ѵ�. */
	virtual BOOL Unlock();
};

class XSYSTEM_API XSemaphoreW : public XWaitableObject, public XSyncObject
{
public:
    /*! \brief defualt constructor */
    XSemaphoreW() {}

    /*! \brief distructor */
    virtual ~XSemaphoreW() {}

    /*! \brief semaphore object ���� */
    BOOL Create(int nInitialCount, int nMaximumCount, const wchar_t *pszName = NULL, LPSECURITY_ATTRIBUTES psa = NULL);

    /*! \brief �̹� ������ semaphore object�� open �Ѵ�. */
    BOOL Open(const wchar_t *pszName = NULL, DWORD dwDesiredAccess = SEMAPHORE_ALL_ACCESS, BOOL bInheritHandle = FALSE);

    /*! \brief semaphore object�� Releases �Ѵ�. */
    BOOL Release(LONG nReleaseCount, LONG* pnPreviousCount = NULL);

    /*! \brief Wait�� ȣ���Ѵ�. */
    virtual BOOL Lock(DWORD dwMilliseconds = INFINITE);

    /*! \brief Release(1)�� ȣ���Ѵ�. */
    virtual BOOL Unlock();
};

#if !defined(UNICODE) && !defined(_UNICODE)
    typedef XSemaphoreA XSemaphore;
#else
    typedef XSemaphoreW XSemaphore;
#endif

/********************************************************************************
	class XEvent
********************************************************************************/
/*!
\brief					event object�� ���� wrapper class

\remarks
						- Required header: <XBase/XSystem/XSyncObject.h>

\sa						XSyncObject, XWaitableObject, XCriticalSection, XMutex, XSemaphore, XWaitableCollection
*/
class XSYSTEM_API XEventA : public XWaitableObject, public XSyncObject
{
public:
	/*! \brief defualt constructor */
	XEventA() {}

	/*! \brief distructor */
	virtual ~XEventA() {}

	/*! \brief event object ���� */
	BOOL Create(BOOL bManualReset = FALSE, BOOL bInitialState = FALSE, const char *pszName = NULL, LPSECURITY_ATTRIBUTES psa = NULL);

	/*! \brief �̹� ������ event object�� open �Ѵ�. */
	BOOL Open(const char *pszName, DWORD dwDesiredAccess = EVENT_ALL_ACCESS, BOOL bInheritHandle = FALSE);

	/*! \brief event object�� signaled state�� �����. */
	BOOL Set();

	/*! \brief event object�� nonsignaled state�� �����. */
	BOOL Reset();

	/*! \brief event object�� signaled state�� ����� waiting threads�� releases�ϰ� �ٽ� event object�� nonsignaled state�� �����. */
	BOOL Pulse();

	/*! \brief Wait�� ȣ���Ѵ�. */
	virtual BOOL Lock(DWORD dwMilliseconds = INFINITE);

	virtual BOOL Unlock();
};

class XSYSTEM_API XEventW : public XWaitableObject, public XSyncObject
{
public:
    /*! \brief defualt constructor */
    XEventW() {}

    /*! \brief distructor */
    virtual ~XEventW() {}

    /*! \brief event object ���� */
    BOOL Create(BOOL bManualReset = FALSE, BOOL bInitialState = FALSE, const wchar_t *pszName = NULL, LPSECURITY_ATTRIBUTES psa = NULL);

    /*! \brief �̹� ������ event object�� open �Ѵ�. */
    BOOL Open(const wchar_t *pszName, DWORD dwDesiredAccess = EVENT_ALL_ACCESS, BOOL bInheritHandle = FALSE);

    /*! \brief event object�� signaled state�� �����. */
    BOOL Set();

    /*! \brief event object�� nonsignaled state�� �����. */
    BOOL Reset();

    /*! \brief event object�� signaled state�� ����� waiting threads�� releases�ϰ� �ٽ� event object�� nonsignaled state�� �����. */
    BOOL Pulse();

    /*! \brief Wait�� ȣ���Ѵ�. */
    virtual BOOL Lock(DWORD dwMilliseconds = INFINITE);

    virtual BOOL Unlock();
};

#if !defined(UNICODE) && !defined(_UNICODE)
    typedef XEventA XEvent;
#else
    typedef XEventW XEvent;
#endif

/********************************************************************************
    class XRWCriticalSection
********************************************************************************/
class XSYSTEM_API XRWCriticalSection
{
public:
    XRWCriticalSection();
    virtual ~XRWCriticalSection();

    BOOL Create();
    BOOL Destroy();

    BOOL LockReader(IN DWORD dwMilliseconds = INFINITE);
    BOOL UnlockReader();
    BOOL LockWriter(IN DWORD dwMilliseconds = INFINITE);
    BOOL UnlockWriter();

protected:
    struct Context;
    Context *m_pContext;
};

/********************************************************************************
	class XLock
********************************************************************************/
/*!
\brief					�����ڿ� �Ҹ��ڿ��� ���� XSyncObject ��ü�� Lock�� Unlock �Լ��� ���� ȣ���Ѵ�.

\remarks
						- Required header: <XBase/XSystem/XSyncObject.h>

\sa						XSyncObject, XCriticalSection, XMutex, XSemaphore, XEvent
*/
class XSYSTEM_API XLock
{
public:
	/*! \brief constructor */
	explicit XLock(XSyncObject& r, DWORD dwMilliseconds = INFINITE);

	/*! \brief constructor */
	explicit XLock(XSyncObject* p, DWORD dwMilliseconds = INFINITE);

	/*! \brief distructor */
	virtual ~XLock();

	/*! \brief ���� XSyncObject�� Lock �Ѵ�. */
	BOOL Lock(DWORD dwMilliseconds = INFINITE);

	/*! \brief ���� XSyncObject�� Unlock �Ѵ�. */
	BOOL Unlock();

	/*! \brief ���� XSyncObject ��ü�� Lock �������� �˻��Ѵ�. */
	BOOL IsLocked();

	/*! \brief ���� XSyncObject ��ü�� pObj�� attach �Ѵ�. */
	void Attach(XSyncObject* pObj);

	/*! \brief ���� XSyncObject ��ü�� detach �Ѵ�. */
	XSyncObject* Detach();

protected:
	struct Context;
	enum { ContextSize = 12 };
	BYTE m_context[ContextSize];
};

/********************************************************************************
    class XRWLock
********************************************************************************/
class XSYSTEM_API XRWLock
{
public:
    XRWLock(IN XRWCriticalSection* p, IN BOOL bWriter, IN DWORD dwMilliseconds = INFINITE);
    XRWLock(IN XRWCriticalSection& r, IN BOOL bWriter, IN DWORD dwMilliseconds = INFINITE);
    virtual ~XRWLock();

    BOOL Lock(IN DWORD dwMilliseconds = INFINITE);
    BOOL Unlock();
    BOOL IsLocked();

    void Attach(IN XRWCriticalSection* p, IN BOOL bWriter);
    XRWCriticalSection* Detach();

protected:
    struct Context;
    enum { ContextSize = 12 };
    BYTE m_context[ContextSize];
};

/********************************************************************************
	class XWaitableCollection
********************************************************************************/
/*!
\brief					WaitForMultipleObjectsEx ����� ���� wrapper class

\remarks				SYNCHRONIZE �＼�� ������ ������ �ϳ� �̻��� handle�� signaled state�� �ɶ����� ��ٸ���.

						- Required header: <XBase/XSystem/XSyncObject.h>

\sa						XMutex, XSemaphore, XEvent
*/
class XSYSTEM_API XWaitableCollection
{
public:
	/*! \brief default constructor */
	XWaitableCollection();

	/*! \brief distructor */
	virtual ~XWaitableCollection();

	/*! \brief XWaitableCollection ��ü�� Add�� waiting�� handle ���� */
	int GetCount() const;

	/*! \brief waiting�� handle�� �߰��Ѵ�. */
	BOOL Add(HANDLE hObject);

	/*! \brief waiting�� handle�� �����Ѵ�. */
	void Remove(HANDLE hObject);


	/*! \brief Add�� hande�� array�� Win32 API�� WaitForMultipleObjects�� ȣ���Ѵ�. */
	DWORD Wait(BOOL bWaitAll = FALSE, DWORD dwMilliseconds = INFINITE);

	/*! \brief Add�� hande�� array�� Win32 API�� WaitForMultipleObjectsEx�� ȣ���Ѵ�. */
	DWORD WaitEx(BOOL bAlertable = TRUE, BOOL bWaitAll = FALSE, DWORD dwMilliseconds = INFINITE);

	/*! \brief Add�� hande�� array�� Win32 API�� MsgWaitForMultipleObjects�� ȣ���Ѵ�. */
	DWORD MsgWait(DWORD dwWakeMask = QS_ALLINPUT, BOOL bWaitAll = FALSE, DWORD dwMilliseconds = INFINITE);

	/*! \brief Add�� hande�� array�� Win32 API�� MsgWaitForMultipleObjectsEx�� ȣ���Ѵ�. */
	DWORD MsgWaitEx(DWORD dwFlags = 0, DWORD dwWakeMask = QS_ALLINPUT, DWORD dwMilliseconds = INFINITE);

private:
	struct Context;
	Context* m_pContext;
};

#endif //__XSyncObject__
