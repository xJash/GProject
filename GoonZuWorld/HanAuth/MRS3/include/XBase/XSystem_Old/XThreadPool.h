// XThreadPool.h
/*!
\file		XThreadPool.h

- Required header: <XBase/XSystem/XThreadPool.h>
*/

#ifndef __XThreadPool_Old__
#define __XThreadPool_Old__

#include "XSystemBase.h"
#include <Windows.h>

/*!
\brief					���ο� thread pool�� �����Ѵ�.

\param dwSize			[in] ������ thread ����

\return					������ thread pool�� handle

\sa						XDestroyThreadPool, XGetThreadPoolSize, XQueueWorkItem, XBindCompletionCallback
*/
XSYSTEM_API HANDLE __stdcall XCreateThreadPool(DWORD dwSize);

/*!
\brief					thread pool�� �����Ѵ�.

\param dwSize			[in] ������ thread pool�� handle

\return					���ϰ��� TRUE�̸� �Լ��� ���������� ����Ǿ����� �ǹ��Ѵ�.

\sa						XCreateThreadPool, XGetThreadPoolSize, XQueueWorkItem, XBindCompletionCallback
*/
XSYSTEM_API BOOL __stdcall XDestroyThreadPool(HANDLE hThreadPool);

/*!
\brief					thread pool�� ũ�⸦ ��ȯ�Ѵ�.

\param dwSize			[in] ũ�⸦ ���� thread pool�� handle

\return					�ش� thread pool�� ũ�� (0 �̸��� ��� ����)

\sa						XCreateThreadPool, XDestroyThreadPool, XQueueWorkItem, XBindCompletionCallback
*/
XSYSTEM_API int __stdcall XGetThreadPoolSize(HANDLE hThreadPool);

/*!
\brief					������ ���� function�� thread pool�� queuing �Ѵ�.

\param hThreadPool		[in] function�� ����� thread pool�� handle
\param pFunction		[in] ������ function
\param pParam			[in] pFunction ����� �Բ� ������ ����

\return					���ϰ��� TRUE�̸� thread pool�� ���������� queuing�Ǿ����� �ǹ��Ѵ�.

\sa						XCreateThreadPool, XDestroyThreadPool, XGetThreadPoolSize, XBindCompletionCallback
*/
XSYSTEM_API BOOL __stdcall XQueueWorkItem(HANDLE hThreadPool, LPTHREAD_START_ROUTINE pFunction, PVOID pParam);

/*!
\brief					������ ���� function�� thread pool�� queuing �Ѵ�.

\param hThreadPool		[in] function�� ����� thread pool�� handle
\param pFunction		[in] ������ function
\param dwErrorCode		[in] pFunction ����� �Բ� ������ ù��° ����
\param dwNumberOfBytesTransfered
						[in] pFunction ����� �Բ� ������ �ι�° ����
\param pOverlapped		[in] pFunction ����� �Բ� ������ ����° ����

\return					���ϰ��� TRUE�̸� thread pool�� ���������� queuing�Ǿ����� �ǹ��Ѵ�.

\sa						XCreateThreadPool, XDestroyThreadPool, XGetThreadPoolSize, XBindCompletionCallback
*/
XSYSTEM_API BOOL __stdcall XQueueWorkItem(HANDLE hThreadPool, LPOVERLAPPED_COMPLETION_ROUTINE pFunction, DWORD dwErrorCode, DWORD dwNumberOfBytesTransfered, LPOVERLAPPED pOverlapped);

/*!
\brief					thread pool�� I/O completion port�� file handle�� bind�Ѵ�.

\param hThreadPool		[in] bind�� thread pool�� handle

\param hHandle			[in] bind�� file handle

\param pfnCompletionCallback
						[in] file�� request�� I/O �۾��� �Ϸ�� ��� ȣ��� callback function. \n
						(callback function�� ���� �ڼ��� ������ MSDN�� FileIOCompletionRoutine �׸� ����)

\return					���ϰ��� TRUE�̸� thread pool�� ���������� queuing�Ǿ����� �ǹ��Ѵ�.

\remarks				thread pool�� I/O completion port�� file handle�� bind�Ѵ�.
						bind�� file�� request�� I/O �۾��� �Ϸ�� ��� thread pool�� worker thread�� ���� ��ϵ� 
						callback function�� ȣ��ȴ�.

\sa						XCreateThreadPool, XDestroyThreadPool, XGetThreadPoolSize, XBindCompletionCallback
*/
XSYSTEM_API BOOL __stdcall XBindCompletionCallback(HANDLE hThreadPool, HANDLE hHandle, LPOVERLAPPED_COMPLETION_ROUTINE pfnCompletionCallback);

#endif //__XThreadPool__
