#include "Obj.h"
#include "LibObjBuffer.h"

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - CObj::CObj( UI32 uiMaxBufferSize )
//	Desc : Obj ������
//		   Obj �� �⺻ ������ �α� ���� ���۰� �ʿ��� ��찡 ���Ƽ� ���⿡�� �⺻ ���۵� �غ��� ��.
//		   ����, �⺻ ���۰� �ʿ���ٸ� �Ķ���� ���� 0���� �θ� ��.
//	Date : 2003. 09. 22
//	Update : 
//--------------------------------------------------------------------------------------------
CObj::CObj( UI32 uiMaxBufferSize )
{
	m_pPre = NULL;
	m_pNext = NULL;

	if ( uiMaxBufferSize == 0 )
	{
		m_pObjBuffer = NULL;
	}
	else
	{
		m_pObjBuffer = new CLibObjBuffer( uiMaxBufferSize );
	}
	
	Initialize();
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - CObj::~CObj()
//	Desc : Obj �Ҹ���
//	Date : 2003. 09. 22
//	Update : 
//--------------------------------------------------------------------------------------------
CObj::~CObj()
{
	Destroy();
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CObj::Initialize()
//	Desc : Obj �ʱ�ȭ ( ������ �ʱ�ȭ �� �����Ͱ� �ִٸ� �����ͱ��� �ʱ�ȭ )
//	Date : 2003. 09. 22
//	Update : 
//--------------------------------------------------------------------------------------------
void CObj::Initialize()
{
	m_pPre = NULL;
	m_pNext = NULL;

	if ( m_pObjBuffer )
	{
		m_pObjBuffer->Initialize();
	}

	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CObj::ObjPtrInitialize()
//	Desc : Obj �ʱ�ȭ ( �����͸� �ʱ�ȭ )
//	Date : 2003. 09. 22
//	Update : 
//--------------------------------------------------------------------------------------------
void CObj::ObjPtrInitialize()
{
	m_pPre= NULL;
	m_pNext = NULL;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CObj::Destroy()
//	Desc : Obj ���� ó��
//	Date : 2003. 09. 22
//	Update : 
//--------------------------------------------------------------------------------------------
void CObj::Destroy()
{
	m_pPre = NULL;
	m_pNext = NULL;

	if ( m_pObjBuffer )
	{
		delete m_pObjBuffer;
		m_pObjBuffer = NULL;
	}

	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - CObj *CObj::GetPre()
//	Desc : ���� Obj ������ ��ȯ
//	Date : 2003. 09. 22
//	Update : 
//--------------------------------------------------------------------------------------------
CObj *CObj::GetPre()
{
	return m_pPre;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CObj::SetPre( CObj *pPre )
//	Desc : ���� Obj ������ ����
//	Date : 2003. 09. 22
//	Update : 
//--------------------------------------------------------------------------------------------
void CObj::SetPre( CObj *pPre )
{
	m_pPre = pPre;
	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - CObj *CObj::GetNext()
//	Desc : ���� Obj ������ ��ȯ
//	Date : 2003. 09. 22
//	Update : 
//--------------------------------------------------------------------------------------------
CObj *CObj::GetNext()
{
	return m_pNext;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CObj::SetNext( CObj *pNext )
//	Desc : ���� Obj ������ ����
//	Date : 2003. 09. 22
//	Update : 
//--------------------------------------------------------------------------------------------
void CObj::SetNext( CObj *pNext )
{
	m_pNext = pNext;
	return;
}


//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CObj::SetData( BYTE *pData, UI32 ui32DataSize )
//	Desc : Obj�� �⺻ �����Ͱ� ����ü�� �Ǿ� ���� ���, �׷� ����ü���� ����Ʈ ������ ���� �� �ְ� �ϱ� ���ؼ�...
//	Date : 2003. 11. 14
//	Update : 
//--------------------------------------------------------------------------------------------
void CObj::SetData( BYTE *pData, UI32 ui32DataSize )
{
	m_pObjBuffer->SetData( pData, ui32DataSize );
	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CObj::GetData( BYTE *pData, UI32 *pDataSize )
//	Desc : Obj�� �⺻ �����͸� �о �����ؼ� �־���.
//	Date : 2003. 11. 14
//	Update : 
//--------------------------------------------------------------------------------------------
void CObj::GetData( BYTE *pData, UI32 *pDataSize )
{
	m_pObjBuffer->GetData( pData, pDataSize );
	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - BYTE* CObj::GetDataPtr()
//	Desc : Obj�� �⺻ �������� �����͸� �Ѱ���.
//		   ����, �����ؾ� ��. ��, �̰��� ���� ������ �ݸ� ������ �ξ� ����.
//		   �� �Լ��� ���ٴ� ����, �� �Լ��� �ҷ��� �Ѱ��� �����͸� ���� ���ȿ��� ���� �����Ͱ� ������� ���� ��쿡�� ��� ���� ��.
//	Date : 2003. 11. 14
//	Update : 
//--------------------------------------------------------------------------------------------
BYTE* CObj::GetDataPtr()
{
	return m_pObjBuffer->GetDataPtr();
}