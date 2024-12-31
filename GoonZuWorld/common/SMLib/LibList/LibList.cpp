#include "LibList.h"
#include "Obj.h"

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - CLibList::CLibList()
//	Desc : List ���̺귯�� ������
//	Date : 2003. 09. 22
//	Update : 
//--------------------------------------------------------------------------------------------
CLibList::CLibList()
{
	m_pFirst = NULL;
	m_pLast = NULL;

	m_si32ObjNum = 0;

	InitializeCriticalSection( &m_LibListCrit );

	Initialize();
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - CLibList::~CLibList()
//	Desc : List ���̺귯�� �Ҹ���
//	Date : 2003. 09. 22
//	Update : 
//--------------------------------------------------------------------------------------------
CLibList::~CLibList()
{
	Destroy();
	DeleteCriticalSection( &m_LibListCrit );
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CLibList::Initialize()
//	Desc : List ���̺귯�� �ʱ�ȭ
//	Date : 2003. 09. 22
//	Update : 
//--------------------------------------------------------------------------------------------
void CLibList::Initialize()
{
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CLibList::Destroy()
//	Desc : List ���̺귯�� ����ó��
//	Date : 2003. 09. 22
//	Update : 
//--------------------------------------------------------------------------------------------
void CLibList::Destroy()
{
	CObj *pTemp = NULL;

	while( m_pFirst )
	{
		pTemp = m_pFirst;
		m_pFirst = m_pFirst->GetNext();
		
		delete pTemp;
		pTemp = NULL;
	}

	m_pFirst = NULL;
	m_pLast = NULL;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CLibList::Create( int	si32MakeNodeNum )
//	Desc : List ��� ����( �⺻������ Max���� ��带 �����ϵ��� �ϰ� �ϱ� ���ؼ�. - EmptyList, ExistList �ΰ��� �ִµ�, ��� ��带 EmptyList�� �ΰ� �ϱ� ���ؼ��� )
//		   ���� CObj�� ��� ���� �ʿ� ����, CObj�� ���۸����ε� ����� �����ϴٸ�, �׳� CObj ��ü�� �����ؼ� ����ϸ� �� ���ϹǷ�...
//		   si32BufferSize �� CObj�� ���� ũ���̴�.
//	Date : 2003. 11. 20
//	Update : 
//--------------------------------------------------------------------------------------------
void CLibList::Create( int si32MakeNodeNum, int si32BufferSize )
{
	CObj *pTemp = NULL;

	for ( int i = 0; i < si32MakeNodeNum; ++i )
	{
		pTemp = new CObj( si32BufferSize );
		PushBack( pTemp );
	}
	
	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CLibList::Lock()
//	Desc : List �ڷ� ó�� �ϱ� ���� Lock �ɱ�
//	Date : 2003. 09. 22
//	Update : 
//--------------------------------------------------------------------------------------------
void CLibList::Lock()
{
	EnterCriticalSection( &m_LibListCrit );
	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CLibList::UnLock()
//	Desc : List �ڷ� ó�� �Ŀ� UnLock �ϱ�
//	Date : 2003. 09. 22
//	Update : 
//--------------------------------------------------------------------------------------------
void CLibList::UnLock()
{
	LeaveCriticalSection( &m_LibListCrit );
	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CLibList::PushFront( CObj *pObj )
//	Desc : List �տ� �߰�
//	Date : 2003. 09. 22
//	Update : 
//--------------------------------------------------------------------------------------------
void CLibList::PushFront( CObj *pObj )
{
	pObj->ObjPtrInitialize();

	if ( m_pFirst )
	{
		m_pFirst->SetPre( pObj );
		pObj->SetNext( m_pFirst );
		m_pFirst = pObj;
	}
	else
	{
		m_pFirst = pObj;
		m_pLast = pObj;
	}

	++m_si32ObjNum;

	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CLibList::PushBack( CObj *pObj )
//	Desc : List �ڿ� �߰�
//	Date : 2003. 09. 22
//	Update : 
//--------------------------------------------------------------------------------------------
void CLibList::PushBack( CObj *pObj )
{
	pObj->ObjPtrInitialize();

	if ( m_pFirst )
	{
		m_pLast->SetNext( pObj );
		pObj->SetPre( m_pLast );
		m_pLast = pObj;
	}
	else
	{
		m_pFirst = pObj;
		m_pLast = pObj;
	}

	++m_si32ObjNum;

	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CLibList::PushIndex( int si32Index, CObj *pObj )
//	Desc : List si32Index��°�� �߰� ( �ణ�� �׽�Ʈ�� �ʿ��� )
//	Date : 2003. 09. 22
//	Update : 
//--------------------------------------------------------------------------------------------
void CLibList::PushIndex( int si32Index, CObj *pObj )
{
#ifdef _DEBUG
	if ( si32Index > m_si32ObjNum )
	{
		MessageBox( NULL, TEXT("adfhlh3"), TEXT("23ui5y"), MB_OK|MB_TOPMOST );
		return;
	}
#endif

	if ( si32Index == 0 || si32Index == m_si32ObjNum )
	{
		if ( si32Index == 0 )
		{
			PushFront( pObj );
		}
		else
		{
			PushBack( pObj );
		}
	}
	else
	{
		CObj *pTemp = m_pFirst;

		for ( int i = 0; i < si32Index - 1; ++i )
		{
			pTemp = pTemp->GetNext();
		}

		pObj->SetNext( pTemp->GetNext() );
		pObj->SetPre( pTemp );

		pTemp->GetNext()->SetPre( pObj );
		pTemp->SetNext( pObj );
	}
	
	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - CObj *CLibList::PopFront()
//	Desc : List �տ��� ���� ( ���� �Ŀ� ó���� ��� �� )
//	Date : 2003. 09. 22
//	Update : 
//--------------------------------------------------------------------------------------------
CObj *CLibList::PopFront()
{
	if ( m_pFirst )
	{
		CObj *pTemp = m_pFirst;

		if ( m_pFirst->GetNext() )
		{
			m_pFirst->GetNext()->SetPre( NULL );
			m_pFirst = m_pFirst->GetNext();
		}
		else
		{
			m_pFirst = NULL;
			m_pLast = NULL;
		}

		--m_si32ObjNum;

		pTemp->ObjPtrInitialize();
		return pTemp;
	}
	else
	{
		return NULL;
	}
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - CObj *CLibList::PopBack()
//	Desc : List �ڿ��� ���� ( ���� �Ŀ� ó���� ��� �� )
//	Date : 2003. 09. 22
//	Update : 
//--------------------------------------------------------------------------------------------
CObj *CLibList::PopBack()
{
	if ( m_pFirst )
	{
		CObj *pTemp = m_pLast;

		if ( m_pLast->GetPre() )
		{
			m_pLast->GetPre()->SetNext( NULL );
			m_pLast = m_pLast->GetPre();
		}
		else
		{
			m_pFirst = NULL;
			m_pLast = NULL;
		}

		--m_si32ObjNum;

		pTemp->ObjPtrInitialize();
		return pTemp;
	}
	else
	{
		return NULL;
	}
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CLibList::Pop( CObj *pObj )
//	Desc : Ư�� ���( �Ķ���ͷ� �Է��� CObj *pObj) �� ����Ʈ���� ����
//		   �Ķ���� ���� ���� ����̱� ������ ���� ���� ������ ��ü ������ �� �ʿ� ����... �翬�� ��������...
//	Date : 2003. 10. 01
//	Update : 
//--------------------------------------------------------------------------------------------
void CLibList::Pop( CObj *pObj )
{
	/*

#ifdef _DEBUG
	if ( m_si32ObjNum == 0 )
	{
		MessageBox( NULL, TEXT("Pop �Ұ� ���µ�... �����������"), TEXT("Pop �Ұ� ����."), MB_OK|MB_TOPMOST );
		return;
	}
#endif

	// �Ŀ� ����ȭ ��ų������ �� �κ��� �ּ��� ���� ���Ѽ� �� ���� �ӵ��� ����� ��
	if ( m_si32ObjNum == 1 )
	{
		m_pFirst = NULL;
		m_pLast = NULL;

		--m_si32ObjNum;
		pObj->ObjPtrInitialize();

		return;
	}
	*/

	if ( pObj->GetPre() )
	{
		pObj->GetPre()->SetNext( pObj->GetNext() );
	}
	else				// pObj �� m_pFirst �� �������...
	{
		if ( pObj->GetNext() )
		{
			m_pFirst = pObj->GetNext();
			m_pFirst->SetPre( NULL );
		}
		else
		{
			m_pFirst = NULL;
			m_pLast = NULL;
		}
	}

	if ( pObj->GetNext() )
	{
		pObj->GetNext()->SetPre( pObj->GetPre() );
	}
	else				// pObj �� m_pLast �� �������...
	{
		if ( pObj->GetPre() )
		{
			m_pLast = pObj->GetPre();
			m_pLast->SetNext( NULL );
		}
		else
		{
			m_pFirst = NULL;
			m_pLast = NULL;
		}
	}

	--m_si32ObjNum;

	pObj->ObjPtrInitialize();

	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - int CLibList::GetObjNum()
//	Desc : List �� �ִ� ��ü�� ���ڸ� ������ ��
//	Date : 2003. 09. 22
//	Update : 
//--------------------------------------------------------------------------------------------
int CLibList::GetObjNum()
{
	return m_si32ObjNum;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - CObj *CLibList::GetFirst()
//	Desc : List �� �ִ� �� ó���� ��带 ��������
//	Date : 2003. 09. 22
//	Update : 
//--------------------------------------------------------------------------------------------
CObj *CLibList::GetFirst()
{
	return m_pFirst;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - CObj *CLibList::GetLast()
//	Desc : List �� �ִ� �� ���� ��带 ��������
//	Date : 2003. 09. 22
//	Update : 
//--------------------------------------------------------------------------------------------
CObj *CLibList::GetLast()
{
	return m_pLast;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CLibList::SetFirst( CObj	*pObj )
//	Desc : List ���� ���� ��� ���� ( ���� ������ ����� �κе��� �� �Լ� ȣ�� ���� ó�� �Ǿ�� ��. ��� �ű�ٴ��� �ϴ� �� )
//	Date : 2003. 09. 22
//	Update : 
//--------------------------------------------------------------------------------------------
void CLibList::SetFirst( CObj	*pObj )
{
	m_pFirst = pObj;
	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CLibList::SetFirst( CObj	*pObj )
//	Desc : List ���� ���� ��� ���� ( ���� ������ ����� �κе��� �� �Լ� ȣ�� ���� ó�� �Ǿ�� ��. ��� �ű�ٴ��� �ϴ� �� )
//	Date : 2003. 09. 22
//	Update : 
//--------------------------------------------------------------------------------------------
void CLibList::SetLast( CObj	*pObj )
{
	m_pLast = pObj;
	return;
}
