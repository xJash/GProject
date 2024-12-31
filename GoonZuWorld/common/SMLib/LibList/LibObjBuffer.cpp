#include "LibObjBuffer.h"

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - CLibObjBuffer::CLibObjBuffer( UI32 uiMaxBufferSize )
//	Desc : LibBuffer ������
//	Date : 2003. 11. 14
//	Update : 
//--------------------------------------------------------------------------------------------
CLibObjBuffer::CLibObjBuffer( UI32 uiMaxBufferSize )
{
	m_uiDataSize = 0;

	m_pData = new BYTE[ uiMaxBufferSize ];

	Initialize();
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - CLibObjBuffer::~CLibObjBuffer()
//	Desc : LibBuffer �Ҹ���
//	Date : 2003. 11. 14
//	Update : 
//--------------------------------------------------------------------------------------------
CLibObjBuffer::~CLibObjBuffer()
{
	Destroy();
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CLibObjBuffer::Initialize()
//	Desc : LibBuffer �ʱ�ȭ
//	Date : 2003. 11. 14
//	Update : 
//--------------------------------------------------------------------------------------------
void CLibObjBuffer::Initialize()
{
	if( m_pData )
	{
		memset( m_pData, 0, m_uiDataSize );
		m_uiDataSize = 0;
	}

	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CLibObjBuffer::Initialize()
//	Desc : LibBuffer ����ó��
//	Date : 2003. 11. 14
//	Update : 
//--------------------------------------------------------------------------------------------
void CLibObjBuffer::Destroy()
{
	if ( m_pData )
	{
		delete [] m_pData;
		m_pData = NULL;

		m_uiDataSize = 0;
	}

	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CLibObjBuffer::SetData( BYTE *pData, UI32 ui32DataSize )
//	Desc : LibBuffer �����͸� ���ۿ� ����
//	Date : 2003. 11. 14
//	Update : 
//--------------------------------------------------------------------------------------------
void CLibObjBuffer::SetData( BYTE *pData, UI32 ui32DataSize )
{
	memcpy( m_pData, pData, ui32DataSize );

	m_uiDataSize = ui32DataSize;
	
	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CLibObjBuffer::GetData( BYTE *pData, UI32* pDataSize )
//	Desc : LibBuffer ���۷κ��� �����͸� �о �Ķ���ͷ� �Է��� pData �� �־���
//	Date : 2003. 11. 14
//	Update : 
//--------------------------------------------------------------------------------------------	
void CLibObjBuffer::GetData( BYTE *pData, UI32* pDataSize )
{
#ifdef _DEBUG
	if ( ! IsDataExist() )
	{
		MessageBox( NULL, TEXT("���� �����Ͱ� ���µ�, ������� �մϴ�."), 
			TEXT("void CLibObjBuffer::ReadData( BYTE *pData, SI32 *pDataSize )"), MB_OK|MB_TOPMOST );
		return;
	}
#endif

	memcpy( pData, m_pData, m_uiDataSize );
	*pDataSize = m_uiDataSize;

	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - BYTE *CLibObjBuffer::GetDataPtr()
//	Desc : LibBuffer ������ ������ �����͸� ��ȯ
//					 �����ͷ� ������ ���� ������ ����� ���̸� 
//					 �̰� �ξ� �����Ƿ�..., 
//					 �� ������ ���� �д� ���ȿ��� �����Ͱ� ���� ���ؼ��� �� �ȴٴ� ���̴�.
//	Date : 2003. 11. 14
//	Update : 
//--------------------------------------------------------------------------------------------	
BYTE *CLibObjBuffer::GetDataPtr()
{
#ifdef _DEBUG
	if ( ! IsDataExist() )
	{
		MessageBox( NULL, TEXT("���� �����Ͱ� ���µ�, ������� �մϴ�."), 
			TEXT("void CLibObjBuffer::ReadData( BYTE *pData, SI32 *pDataSize )"), MB_OK|MB_TOPMOST );
		return NULL;
	}
#endif*
	
	return m_pData;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - bool CLibObjBuffer::IsDataExist()
//	Desc : LibBuffer ������ ����� �޾ƿ��� �ͺ��� ������ �ִ��� �����ĸ� üũ�ϴ°� �ֵ� ���̹Ƿ� �����Ͱ� �ִ��ĸ� üũ ( �̰� ������ �� ���� )	
//	Date : 2003. 11. 14
//	Update : 
//--------------------------------------------------------------------------------------------	
bool CLibObjBuffer::IsDataExist()
{
	if ( m_uiDataSize > 0 )
	{
		return true;
	}
	
	return false;	
}