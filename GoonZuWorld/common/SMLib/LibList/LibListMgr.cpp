#include "LibListMgr.h"
#include "LibList.h"
#include "Obj.h"

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - CLibListMgr::CLibListMgr( bool bCircleLinkedListMode )
//	Desc : List Manager ���̺귯�� ������
//		   bCircleLinkedListMode �� ��尡 �� á����, ���ο� ��带 �߰��϶�� �ϸ� ���� ó���� ��� ��带 �ʱ�ȭ �ϰ�, �� ��带 ���� ������ ���ġ ��Ŵ...
//		   ���� ���ϸ� emptylist �� ��尡 ������, existlist �� ���� ó���� �Էµ� ��带 �ʱ�ȭ �� ������, �� ���� existlist ���� ���� ���� ������...
//		   �������� ������ �����ؾ���....
//		   �׷��� default ������ false �� �� ������
//		   bCircleLinkedListMode �� false �� �� ��쿡�� m_bCircleLinkedListMode �� �ʿ� ���� ������, �ű⿡ ����� if ���� ��� �����ؼ� �� ���� �ӵ��� ����� �� �ְ� �ȴ�.
//	Date : 2003. 09. 22
//	Update : 
//--------------------------------------------------------------------------------------------
CLibListMgr::CLibListMgr( bool bCircleLinkedListMode )
{
	m_pExistList = new CLibList();
	m_pEmptyList = new CLibList();

	m_bCircleLinkedListMode = bCircleLinkedListMode;

	InitializeCriticalSection( &m_LibListMgrCrit );

	Initialize();
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - CLibListMgr::~CLibListMgr()
//	Desc : List Manager ���̺귯�� �Ҹ���
//	Date : 2003. 09. 22
//	Update : 
//--------------------------------------------------------------------------------------------
CLibListMgr::~CLibListMgr()
{
	Destroy();

	DeleteCriticalSection( &m_LibListMgrCrit );
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CLibListMgr::Initialize()
//	Desc : List Manager ���̺귯�� �ʱ�ȭ
//	Date : 2003. 09. 22
//	Update : 
//--------------------------------------------------------------------------------------------
void CLibListMgr::Initialize()
{
	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CLibListMgr::Destroy()
//	Desc : List Manager ���̺귯�� ���� ó��
//	Date : 2003. 09. 22
//	Update : 
//--------------------------------------------------------------------------------------------
void CLibListMgr::Destroy()
{
	if ( m_pExistList )
	{
		delete	m_pExistList;
		m_pExistList = NULL;
	}

	if ( m_pEmptyList )
	{
		delete m_pEmptyList;
		m_pEmptyList = NULL;
	}

	return;
}


//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CLibListMgr::CreateMaxEmptyObj( int si32MaxObjNum, int si32BufferSize )
//	Desc : Empty List �� �ִ� ������ �����ؼ� �־��ֱ� ���ؼ�
//		   ���� CObj�� ��� ���� �ʿ� ����, CObj�� ���۸����ε� ����� �����ϴٸ�, �׳� CObj ��ü�� �����ؼ� ����ϸ� �� ���ϹǷ�...
//		   ������ ���� �� CObj ��� ���� �ʿ䰡 ���� ��쿡�� ����ؾ� �Ѵٴ� ���̴�.
//		   �ι�° �Ķ���ʹ� CObj �� ���� ũ���̴�.
//	Date : 2003. 11. 20
//	Update : 
//--------------------------------------------------------------------------------------------
void CLibListMgr::CreateMaxEmptyObj( int si32MaxObjNum, int si32BufferSize )
{
	m_pEmptyList->Create( si32MaxObjNum, si32BufferSize );
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CLibListMgr::Clear()
//	Desc : Exist ����Ʈ�� �ִ°� ���� Empty ����Ʈ �� �־���.
//	Date : 2004. 5. 27
//	Update : 
//--------------------------------------------------------------------------------------------
void CLibListMgr::Clear()
{
	Lock();

	bool unlimitloop = true;
	while ( unlimitloop )
	{
		CObj *pTemp = m_pExistList->PopFront();
		if ( pTemp == NULL )
		{
			break;
		}

		m_pEmptyList->PushBack( pTemp );
	}

	UnLock();
	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CLibListMgr::Lock()
//	Desc : List Manager Lock
//	Date : 2003. 09. 22
//	Update : 
//--------------------------------------------------------------------------------------------
void CLibListMgr::Lock()
{
	EnterCriticalSection( &m_LibListMgrCrit );
	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CLibListMgr::UnLock()
//	Desc : List Manager UnLock
//	Date : 2003. 09. 22
//	Update : 
//--------------------------------------------------------------------------------------------
void CLibListMgr::UnLock()
{
	LeaveCriticalSection( &m_LibListMgrCrit );
	return;
}

void CLibListMgr::PushFrontToExistList( CObj *pObj )
{
	Lock();
	m_pExistList->PushFront( pObj );
	UnLock();
	return;
}

void CLibListMgr::PushBackToExistList( CObj *pObj )
{
	Lock();
	m_pExistList->PushBack( pObj );
	UnLock();
	return;
}

void CLibListMgr::PushFrontToEmptyList( CObj *pObj )
{
	Lock();
	m_pEmptyList->PushFront( pObj );
	UnLock();
	return;
}

void CLibListMgr::PushBackToEmptyList( CObj *pObj )
{
	Lock();
	m_pEmptyList->PushBack( pObj );
	UnLock();
	return;
}


CObj *CLibListMgr::PopFrontToExistList()
{
	return m_pExistList->PopFront();
}

CObj *CLibListMgr::PopBackToExistList()
{
	return m_pExistList->PopBack();
}

CObj *CLibListMgr::PopFrontToEmptyList()
{
	return m_pEmptyList->PopFront();
}

CObj *CLibListMgr::PopBackToEmptyList()
{
	return m_pEmptyList->PopBack();
}


//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - CObj *CLibListMgr::PopFrontToExistListAndPushFrontToEmptyList()
//	Desc : Exist ����Ʈ�� �տ��� �����ͼ� Empty ����Ʈ �տ� �־���
//	Date : 2003. 09. 22
//	Update : 
//--------------------------------------------------------------------------------------------
CObj *CLibListMgr::PopFrontToExistListAndPushFrontToEmptyList()
{
	Lock();
	CObj *pTemp = m_pExistList->PopFront();

	if ( pTemp == NULL )
	{
		if ( m_bCircleLinkedListMode )
		{
			pTemp = m_pEmptyList->PopBack();
#ifdef _DEBUG
			if ( pTemp == NULL )
			{
				MessageBox( NULL, TEXT("��ü ���� Ȯ��"), TEXT("��ü ���� Ȯ��"), MB_OK|MB_TOPMOST );
			}
#endif
			m_pEmptyList->PushFront( pTemp );
			UnLock();
			return pTemp;
		}

		UnLock();
		return NULL;
	}

	m_pEmptyList->PushFront( pTemp );
	UnLock();
	return pTemp;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - CObj *CLibListMgr::PopFrontToExistListAndPushBackToEmptyList()
//	Desc : Exist ����Ʈ�� �տ��� �����ͼ� Empty ����Ʈ �ڿ� �־���
//	Date : 2003. 09. 22
//	Update : 
//--------------------------------------------------------------------------------------------
CObj *CLibListMgr::PopFrontToExistListAndPushBackToEmptyList()
{
	Lock();
	CObj *pTemp = m_pExistList->PopFront();

	if ( pTemp == NULL )
	{
		if ( m_bCircleLinkedListMode )
		{
			pTemp = m_pEmptyList->PopFront();
#ifdef _DEBUG
			if ( pTemp == NULL )
			{
				MessageBox( NULL, TEXT("��ü ���� Ȯ��"), TEXT("��ü ���� Ȯ��"), MB_OK|MB_TOPMOST );
			}
#endif
			m_pEmptyList->PushBack( pTemp );
			UnLock();
			return pTemp;
		}

		UnLock();
		return NULL;
	}

	m_pEmptyList->PushBack( pTemp );
	UnLock();
	return pTemp;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - CObj *CLibListMgr::PopBackToExistListAndPushFrontToEmptyList()
//	Desc : Exist ����Ʈ�� �ڿ��� �����ͼ� Empty ����Ʈ �տ� �־���
//	Date : 2003. 09. 22
//	Update : 
//--------------------------------------------------------------------------------------------
CObj *CLibListMgr::PopBackToExistListAndPushFrontToEmptyList()
{
	Lock();
	CObj *pTemp = m_pExistList->PopBack();

	if ( pTemp == NULL )
	{
		if ( m_bCircleLinkedListMode )
		{
			pTemp = m_pEmptyList->PopBack();
#ifdef _DEBUG
			if ( pTemp == NULL )
			{
				MessageBox( NULL, TEXT("��ü ���� Ȯ��"), TEXT("��ü ���� Ȯ��"), MB_OK|MB_TOPMOST );
			}
#endif
			m_pEmptyList->PushFront( pTemp );
			UnLock();
			return pTemp;
		}

		UnLock();
		return NULL;
	}


	m_pEmptyList->PushFront( pTemp );
	UnLock();
	return pTemp;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - CObj *CLibListMgr::PopBackToExistListAndPushBackToEmptyList()
//	Desc : Exist ����Ʈ�� �ڿ��� �����ͼ� Empty ����Ʈ �ڿ� �־���
//	Date : 2003. 09. 22
//	Update : 
//--------------------------------------------------------------------------------------------
CObj *CLibListMgr::PopBackToExistListAndPushBackToEmptyList()
{
	Lock();
	CObj *pTemp = m_pExistList->PopBack();

	if ( pTemp == NULL )
	{
		if ( m_bCircleLinkedListMode )
		{
			pTemp = m_pEmptyList->PopFront();
#ifdef _DEBUG
			if ( pTemp == NULL )
			{
				MessageBox( NULL, TEXT("��ü ���� Ȯ��"), TEXT("��ü ���� Ȯ��"), MB_OK|MB_TOPMOST );
			}
#endif
			m_pEmptyList->PushBack( pTemp );
			UnLock();
			return pTemp;
		}

		UnLock();
		return NULL;
	}

	m_pEmptyList->PushBack( pTemp );
	UnLock();
	return pTemp;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - CObj *CLibListMgr::PopFrontToEmptyListAndPushFrontToExistList()
//	Desc : Empty ����Ʈ�� �տ��� �����ͼ� Exist ����Ʈ �տ� �־���
//	Date : 2003. 09. 22
//	Update : 
//--------------------------------------------------------------------------------------------
CObj *CLibListMgr::PopFrontToEmptyListAndPushFrontToExistList()
{
	Lock();
	CObj *pTemp = m_pEmptyList->PopFront();

	if ( pTemp == NULL )
	{
		if ( m_bCircleLinkedListMode )
		{
			pTemp = m_pExistList->PopBack();
#ifdef _DEBUG
			if ( pTemp == NULL )
			{
				MessageBox( NULL, TEXT("��ü ���� Ȯ��"), TEXT("��ü ���� Ȯ��"), MB_OK|MB_TOPMOST );
			}
#endif
			m_pExistList->PushFront( pTemp );
			UnLock();
			return pTemp;
		}

		UnLock();
		return NULL;
	}

	m_pExistList->PushFront( pTemp );
	UnLock();
	return pTemp;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - CObj *CLibListMgr::PopFrontToEmptyListAndPushBackToExistList()
//	Desc : Empty ����Ʈ�� �տ��� �����ͼ� Exist ����Ʈ �ڿ� �־���
//	Date : 2003. 09. 22
//	Update : 
//--------------------------------------------------------------------------------------------
CObj *CLibListMgr::PopFrontToEmptyListAndPushBackToExistList()
{
	Lock();
	CObj *pTemp = m_pEmptyList->PopFront();

	if ( pTemp == NULL )
	{
		if ( m_bCircleLinkedListMode )
		{
			pTemp = m_pExistList->PopFront();
#ifdef _DEBUG
			if ( pTemp == NULL )
			{
				MessageBox( NULL, TEXT("��ü ���� Ȯ��"), TEXT("��ü ���� Ȯ��"), MB_OK|MB_TOPMOST );
			}
#endif
			m_pExistList->PushBack( pTemp );
			UnLock();
			return pTemp;
		}

		UnLock();
		return NULL;
	}

	m_pExistList->PushBack( pTemp );
	UnLock();
	return pTemp;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - CObj *CLibListMgr::PopBackToEmptyListAndPushFrontToExistList()
//	Desc : Empty ����Ʈ�� �ڿ��� �����ͼ� Exist ����Ʈ �տ� �־���
//	Date : 2003. 09. 22
//	Update : 
//--------------------------------------------------------------------------------------------
CObj *CLibListMgr::PopBackToEmptyListAndPushFrontToExistList()
{
	Lock();
	CObj *pTemp = m_pEmptyList->PopBack();

	if ( pTemp == NULL )
	{
		if ( m_bCircleLinkedListMode )
		{
			pTemp = m_pExistList->PopBack();
#ifdef _DEBUG
			if ( pTemp == NULL )
			{
				MessageBox( NULL, TEXT("��ü ���� Ȯ��"), TEXT("��ü ���� Ȯ��"), MB_OK|MB_TOPMOST );
			}
#endif
			m_pExistList->PushFront( pTemp );
			UnLock();
			return pTemp;
		}
		
		UnLock();
		return NULL;
	}

	m_pExistList->PushFront( pTemp );
	UnLock();
	return pTemp;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - CObj *CLibListMgr::PopBackToEmptyListAndPushBackToExistList()
//	Desc : Empty ����Ʈ�� �ڿ��� �����ͼ� Exist ����Ʈ �ڿ� �־���
//	Date : 2003. 09. 22
//	Update : 
//--------------------------------------------------------------------------------------------
CObj *CLibListMgr::PopBackToEmptyListAndPushBackToExistList()
{
	Lock();
	CObj *pTemp = m_pEmptyList->PopBack();

	if ( pTemp == NULL )
	{
		if ( m_bCircleLinkedListMode )
		{
			pTemp = m_pExistList->PopFront();
#ifdef _DEBUG
			if ( pTemp == NULL )
			{
				MessageBox( NULL, TEXT("��ü ���� Ȯ��"), TEXT("��ü ���� Ȯ��"), MB_OK|MB_TOPMOST );
			}
#endif
			m_pExistList->PushBack( pTemp );
			UnLock();
			return pTemp;
		}

		UnLock();
		return NULL;
	}

	m_pExistList->PushBack( pTemp );
	UnLock();
	return pTemp;
}

int	CLibListMgr::GetExistListObjNum()
{
	return m_pExistList->GetObjNum();
}

int CLibListMgr::GetEmptyListObjNum()
{
	return m_pEmptyList->GetObjNum();
}

CLibList *CLibListMgr::GetExistList()
{
	return m_pExistList;
}

CLibList *CLibListMgr::GetEmptyList()
{
	return m_pEmptyList;
}