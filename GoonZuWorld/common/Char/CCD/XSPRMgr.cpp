#include "XSPRMgr.h"
#include "XSPRObj.h"
#include "..\..\SMLib\LibList\LibList.h"

#include "..\..\Client\Client.h"
extern cltCommonLogic* pclClient;

#define	MAX_LOADED_FILE_NUM		1000		// �ߺ� �̹��� �����ص� �� ȭ�鿡 ������ 300���̸� 800 �� ���� ��ƾ� ��
											// �켱��, ���� �ʹ��̶� ����� �����Ƿ�...

/*
CXSPRMgr	g_XSPRMgr;

CXSPRMgr::CXSPRMgr() : CLibListMgr()
{
	CreateEmptyObj( MAX_LOADED_FILE_NUM );
	Initialize();
}

CXSPRMgr::~CXSPRMgr()
{
	Destroy();
}

void CXSPRMgr::Initialize()
{
	return;
}

void CXSPRMgr::Destroy()
{
	return;
}

void CXSPRMgr::CreateEmptyObj( SI32 siMaxEmptyObj )
{
	CXSPRObj *pTemp = NULL;

	for ( int i = 0; i < siMaxEmptyObj; ++i )
	{
		pTemp = new CXSPRObj();		
		PushBackToEmptyList( pTemp );
	}

	return;
}

char CXSPRMgr::LoadXSPR( TCHAR *strFileName, SI16 CharacterKind, char cPart, short ssActionIndex )
{

	CXSPRObj* pTemp = IsSameFileExist( strFileName, CharacterKind, cPart, ssActionIndex );

	if ( pTemp == NULL )
	{
		pTemp = ( CXSPRObj * )PopFrontToEmptyListAndPushFrontToExistList();

		if ( pTemp )
		{
			if ( ! pTemp->LoadXSPR( strFileName, CharacterKind, cPart, ssActionIndex ) )
			{
				PopFrontToExistListAndPushBackToEmptyList();
				return LOAD_FAIL;
			}
		}
		else
		{
			return LOAD_FAIL;
		}

		return SUCCESS;
	}

	return FILE_EXIST;
}

void CXSPRMgr::LoadSimilarXSPR( TCHAR *strFileName, SI16 CharacterKind, char cPart, short ssActionIndex )
{
	if ( ssActionIndex > SPCU )			// �� ź ���
	{
		return;
		
		//if ( strFileName[14]== 'H' && strFileName[15]== 'O' )
		//{
			//strncpy( &strFileName[ 14 ], TEXT("HOR01"), 5 );
		//}
		//else if ( strFileName[14]== 'M' && strFileName[15]== 'T' )
		//{
			//strncpy( &strFileName[ 14 ], TEXT("MTL01"), 5 );
		//}
		//else if ( strFileName[14]== 'E' && strFileName[15]== 'Q' )
		//{
			//strncpy( &strFileName[ 14 ], TEXT("EQU01"), 5 );
		//}
		//else
		//{
			// �Ѽ� ����( 1HSR ) �� �Ǽ����� ���������� ���� �ڵ� ��� ��.
		//	if ( ssActionIndex > HSR1 && ssActionIndex < HITR )
		//	{
				// ���� �ڵ尡 �־�� ��. �Ǽտ� ���� ������ ����.
		//	}
		//	else
		//	{
				//strncpy( &strFileName[ 14 ], TEXT("KOR01"), 5 );
		//	}
		//}
	}
	else								// �� Ÿ�� ���� ���
	{		
		if ( ssActionIndex < HITU )
		{
			// 1HSU �� 2HSU �� 1HSU ������ ���� ����.
			strncpy( &strFileName[ 25 ], TEXT("1HSU"), 4 );
		}

		return;
		
		//if ( strFileName[14]== 'M' && strFileName[15]== 'T' )
		//{
			//strncpy( &strFileName[ 14 ], TEXT("MTL01"), 5 );
		//}
		//else if ( strFileName[14]== 'E' && strFileName[15]== 'Q' )
		//{
			//strncpy( &strFileName[ 14 ], TEXT("EQU01"), 5 );
		//}
		//else
		//{
			// �Ѽ� ����( 1HSU ) �� �Ǽ����� ���������� ���� �ڵ� ��� ��.
		//	if ( ssActionIndex > HSU1 && ssActionIndex < HITU )
		//	{				
		//	}
		//	else
		//	{
				//strncpy( &strFileName[ 14 ], TEXT("KOR01"), 5 );
		//	}
		//}
	}

	return;
}


CXSPRObj* CXSPRMgr::IsSameFileExist( TCHAR *strFileName, SI16 CharacterKind, char cPart, short ssActionIndex )
{

	CXSPRObj *pTemp = (CXSPRObj *)GetExistList()->GetFirst();

	while( pTemp )
	{
		if ( pTemp->IsSameFile( strFileName, CharacterKind, cPart, ssActionIndex ) )
		{
			return pTemp;
		}

		pTemp = (CXSPRObj *)pTemp->GetNext();
	}

	return NULL;
}

cltTSpr* CXSPRMgr::PutSprT( SI16 CharacterKind, char cPart, short ssActionIndex, TCHAR *strFileName, int siPosX, int siPosY, int siWidth, int siHeight, int siStartPos )
{
	CXSPRObj *pTempExistObj = IsSameFileExist( strFileName, CharacterKind, cPart, ssActionIndex );

	if ( pTempExistObj == NULL )
	{
		pTempExistObj = ( CXSPRObj * )PopFrontToEmptyListAndPushFrontToExistList();

		if ( pTempExistObj )
		{
			if ( ! pTempExistObj->LoadXSPR( strFileName, CharacterKind, cPart, ssActionIndex ) )
			{
				PopFrontToExistListAndPushBackToEmptyList();
				return NULL;
			}
		}
		else
		{
			LoadSimilarXSPR( strFileName, CharacterKind, cPart, ssActionIndex );

			pTempExistObj = IsSameFileExist( strFileName, CharacterKind, cPart, ssActionIndex );
			
			if ( pTempExistObj == NULL )
			{
				pTempExistObj = (CXSPRObj *)GetExistList()->PopBack();
				GetExistList()->PushFront( pTempExistObj );
				
				if ( ! pTempExistObj->LoadXSPR( strFileName, CharacterKind, cPart, ssActionIndex ) )
				{
					PopFrontToExistListAndPushBackToEmptyList();
					return NULL;
				}
			}			
		}
	}
	
	return pTempExistObj->PutSprT( siPosX, siPosY, siWidth, siHeight, siStartPos );
	

	// ���� ������� ���ϵ��� �޸𸮸� Ȯ���ϱ� ���ؼ�...
	//UI32 temp1;
	//GetLoadedImageDataSize( &temp1 );
	

	//return SUCCESS;
}

cltTSpr* CXSPRMgr::PutSprRT( SI16 CharacterKind, char cPart, short ssActionIndex, char *strFileName, int siPosX, int siPosY, int siWidth, int siHeight, int siStartPos )
{	
	CXSPRObj *pTempExistObj = IsSameFileExist( strFileName, CharacterKind, cPart, ssActionIndex );

	if ( pTempExistObj == NULL )
	{
		pTempExistObj = ( CXSPRObj * )PopFrontToEmptyListAndPushFrontToExistList();

		if ( pTempExistObj )
		{
			if ( ! pTempExistObj->LoadXSPR( strFileName, CharacterKind, cPart, ssActionIndex ) )
			{
				PopFrontToExistListAndPushBackToEmptyList();
				return NULL;
			}
		}
		else
		{
			LoadSimilarXSPR( strFileName, CharacterKind, cPart, ssActionIndex );

			pTempExistObj = IsSameFileExist( strFileName, CharacterKind, cPart, ssActionIndex );
			
			if ( pTempExistObj == NULL )
			{
				pTempExistObj = (CXSPRObj *)GetExistList()->PopBack();
				GetExistList()->PushFront( pTempExistObj );
				
				if ( ! pTempExistObj->LoadXSPR( strFileName, CharacterKind, cPart, ssActionIndex ) )
				{
					PopFrontToExistListAndPushBackToEmptyList();
					return NULL;
				}
			}
		}
	}

	return pTempExistObj->PutSprRT( siPosX, siPosY, siWidth, siHeight, siStartPos );	
}

cltTSpr* CXSPRMgr::PutSprScreenT( SI16 CharacterKind, char cPart, short ssActionIndex, char *strFileName, int siPosX, int siPosY, int siWidth, int siHeight, int siStartPos )
{
	CXSPRObj *pTempExistObj = IsSameFileExist( strFileName, CharacterKind, cPart, ssActionIndex );

	if ( pTempExistObj == NULL )
	{
		pTempExistObj = ( CXSPRObj * )PopFrontToEmptyListAndPushFrontToExistList();

		if ( pTempExistObj )
		{
			if ( ! pTempExistObj->LoadXSPR( strFileName, CharacterKind, cPart, ssActionIndex ) )
			{
				PopFrontToExistListAndPushBackToEmptyList();
				return NULL;
			}
		}
		else
		{
			LoadSimilarXSPR( strFileName, CharacterKind, cPart, ssActionIndex );

			pTempExistObj = IsSameFileExist( strFileName, CharacterKind, cPart, ssActionIndex );

			if ( pTempExistObj == NULL )
			{
				pTempExistObj = (CXSPRObj *)GetExistList()->PopBack();
				GetExistList()->PushFront( pTempExistObj );

				if ( ! pTempExistObj->LoadXSPR( strFileName, CharacterKind, cPart, ssActionIndex ) )
				{
					PopFrontToExistListAndPushBackToEmptyList();
					return NULL;
				}
			}			
		}
	}

	return pTempExistObj->PutSprScreenT( siPosX, siPosY, siWidth, siHeight, siStartPos );


	// ���� ������� ���ϵ��� �޸𸮸� Ȯ���ϱ� ���ؼ�...
	//UI32 temp1;
	//GetLoadedImageDataSize( &temp1 );


	//return SUCCESS;
}

cltTSpr* CXSPRMgr::PutSprScreenRT( SI16 CharacterKind, char cPart, short ssActionIndex, char *strFileName, int siPosX, int siPosY, int siWidth, int siHeight, int siStartPos )
{	
	CXSPRObj *pTempExistObj = IsSameFileExist( strFileName, CharacterKind, cPart, ssActionIndex );

	if ( pTempExistObj == NULL )
	{
		pTempExistObj = ( CXSPRObj * )PopFrontToEmptyListAndPushFrontToExistList();

		if ( pTempExistObj )
		{
			if ( ! pTempExistObj->LoadXSPR( strFileName, CharacterKind, cPart, ssActionIndex ) )
			{
				PopFrontToExistListAndPushBackToEmptyList();
				return NULL;
			}
		}
		else
		{
			LoadSimilarXSPR( strFileName, CharacterKind, cPart, ssActionIndex );

			pTempExistObj = IsSameFileExist( strFileName, CharacterKind, cPart, ssActionIndex );

			if ( pTempExistObj == NULL )
			{
				pTempExistObj = (CXSPRObj *)GetExistList()->PopBack();
				GetExistList()->PushFront( pTempExistObj );

				if ( ! pTempExistObj->LoadXSPR( strFileName, CharacterKind, cPart, ssActionIndex ) )
				{
					PopFrontToExistListAndPushBackToEmptyList();
					return NULL;
				}
			}
		}
	}

	return pTempExistObj->PutSprScreenRT( siPosX, siPosY, siWidth, siHeight, siStartPos );	
}

int CXSPRMgr::GetLoadedImageDataSize( unsigned int *pFileSize )
{
	int siCount = 0;
	*pFileSize = 0;

	CXSPRObj *pTemp = (CXSPRObj *)GetExistList()->GetFirst();

	while( pTemp )
	{
		*pFileSize += pTemp->GetImageFileSize();
		pTemp = (CXSPRObj *)pTemp->GetNext();
		++siCount;
	}

	return siCount;
}

int CXSPRMgr::GetLoadedImageNum()
{
	return GetExistList()->GetObjNum();
}

void CXSPRMgr::Action()
{
	UI32 CurrentFrame = pclClient->GetFrame();

	CXSPRObj *pTemp = (CXSPRObj *)GetExistList()->GetFirst();
	CXSPRObj *pTemp1 = NULL;

	while( pTemp )
	{	
		if ( pTemp->Action( CurrentFrame ) )
		{
			pTemp1 = (CXSPRObj *)pTemp->GetNext();

			GetExistList()->Pop( pTemp );
			GetEmptyList()->PushBack( pTemp );
			pTemp->Initialize();
			
			pTemp = pTemp1;
		}
		else
		{
			pTemp = (CXSPRObj *)pTemp->GetNext();
		}
	}

	return;
}
*/


CXSPRMgr	g_XSPRMgr;

typedef pair< tstring, CXSPRObj* > XSPRPair;


CXSPRMgr::CXSPRMgr()
{	
	CreateEmptyObj( MAX_LOADED_FILE_NUM );
	Initialize();
}

CXSPRMgr::~CXSPRMgr()
{	
	m_XSPRMap.clear();
	Destroy();
}

void CXSPRMgr::Initialize()
{
	return;
}

void CXSPRMgr::Destroy()
{
	return;
}

void CXSPRMgr::CreateEmptyObj( SI32 siMaxEmptyObj )
{
	CXSPRObj *pTemp = NULL;

	for ( int i = 0; i < siMaxEmptyObj; ++i )
	{
		pTemp = new CXSPRObj();		
		PushBackToEmptyList( pTemp );
	}

	return;
}

char CXSPRMgr::LoadXSPR( TCHAR *strFileName, SI16 CharacterKind, char cPart, short ssActionIndex )
{
	CXSPRObj* pTemp = IsSameFileExist( strFileName );

	if ( pTemp == NULL )
	{
		pTemp = ( CXSPRObj * )PopFrontToEmptyListAndPushFrontToExistList();

		if ( pTemp )
		{
			if ( ! pTemp->LoadXSPR( strFileName ) )
			{
				PopFrontToExistListAndPushBackToEmptyList();
				return LOAD_FAIL;
			}
		}
		else
		{
			return LOAD_FAIL;
		}

		m_XSPRMap.insert( XSPRPair( strFileName, pTemp ) );

		return SUCCESS;
	}

	return FILE_EXIST;
}

void CXSPRMgr::LoadSimilarXSPR( TCHAR *strFileName, short ssActionIndex )
{
	if ( ssActionIndex > SPCU )			// �� ź ���
	{
		return;
	}
	else								// �� Ÿ�� ���� ���
	{		
		if ( ssActionIndex < HITU )
		{
			// 1HSU �� 2HSU �� 1HSU ������ ���� ����.
			_tcsncpy( &strFileName[ 25 ], TEXT("1HSU"), 4 );
		}

		return;
	}

	return;
}


CXSPRObj* CXSPRMgr::IsSameFileExist( const TCHAR *strFileName )
{
	if  ( strFileName == NULL || _tcslen( strFileName ) < 1 )
	{
		return NULL;
	}

	map< tstring, CXSPRObj * >::iterator itr;
	itr = m_XSPRMap.find( strFileName );

	if ( itr != m_XSPRMap.end() )
	{
		CXSPRObj *pXSPRObj = itr->second;
		return pXSPRObj;
	}

	return NULL;
}


TSpr* CXSPRMgr::PutSprT( short ssActionIndex, TCHAR *strFileName, int siPosX, int siPosY, int siWidth, int siHeight, int siStartPos )
{
	CXSPRObj *pTempExistObj = IsSameFileExist( strFileName );

	if ( pTempExistObj == NULL )
	{
		pTempExistObj = ( CXSPRObj * )PopFrontToEmptyListAndPushFrontToExistList();

		if ( pTempExistObj )
		{
			if ( ! pTempExistObj->LoadXSPR( strFileName ) )
			{
				PopFrontToExistListAndPushBackToEmptyList();
				return NULL;
			}

			m_XSPRMap.insert( XSPRPair( strFileName, pTempExistObj ) );
		}
		else
		{
			LoadSimilarXSPR( strFileName, ssActionIndex );

			pTempExistObj = IsSameFileExist( strFileName );

			if ( pTempExistObj == NULL )
			{
				pTempExistObj = (CXSPRObj *)GetExistList()->PopBack();
				GetExistList()->PushFront( pTempExistObj );

				if ( ! pTempExistObj->LoadXSPR( strFileName ) )
				{
					PopFrontToExistListAndPushBackToEmptyList();
					return NULL;
				}

				m_XSPRMap.insert( XSPRPair( strFileName, pTempExistObj ) );
			}			
		}		
	}

	return pTempExistObj->PutSprT( siPosX, siPosY, siWidth, siHeight, siStartPos );
}


TSpr* CXSPRMgr::PutSprRT( short ssActionIndex, TCHAR *strFileName, int siPosX, int siPosY, int siWidth, int siHeight, int siStartPos )
{	
	CXSPRObj *pTempExistObj = IsSameFileExist( strFileName );

	if ( pTempExistObj == NULL )
	{
		pTempExistObj = ( CXSPRObj * )PopFrontToEmptyListAndPushFrontToExistList();

		if ( pTempExistObj )
		{
			if ( ! pTempExistObj->LoadXSPR( strFileName ) )
			{
				PopFrontToExistListAndPushBackToEmptyList();
				return NULL;
			}

			m_XSPRMap.insert( XSPRPair( strFileName, pTempExistObj ) );
		}
		else
		{
			LoadSimilarXSPR( strFileName, ssActionIndex );

			pTempExistObj = IsSameFileExist( strFileName );

			if ( pTempExistObj == NULL )
			{
				pTempExistObj = (CXSPRObj *)GetExistList()->PopBack();
				GetExistList()->PushFront( pTempExistObj );

				if ( ! pTempExistObj->LoadXSPR( strFileName ) )
				{
					PopFrontToExistListAndPushBackToEmptyList();
					return NULL;
				}

				m_XSPRMap.insert( XSPRPair( strFileName, pTempExistObj ) );
			}
		}
	}

	return pTempExistObj->PutSprRT( siPosX, siPosY, siWidth, siHeight, siStartPos );	
}

TSpr* CXSPRMgr::PutSprScreenT( short ssActionIndex, TCHAR *strFileName, int siPosX, int siPosY, int siWidth, int siHeight, int siStartPos )
{
	CXSPRObj *pTempExistObj = IsSameFileExist( strFileName );

	if ( pTempExistObj == NULL )
	{
		pTempExistObj = ( CXSPRObj * )PopFrontToEmptyListAndPushFrontToExistList();

		if ( pTempExistObj )
		{
			if ( ! pTempExistObj->LoadXSPR( strFileName ) )
			{
				PopFrontToExistListAndPushBackToEmptyList();
				return NULL;
			}

			m_XSPRMap.insert( XSPRPair( strFileName, pTempExistObj ) );
		}
		else
		{
			LoadSimilarXSPR( strFileName, ssActionIndex );

			pTempExistObj = IsSameFileExist( strFileName );

			if ( pTempExistObj == NULL )
			{
				pTempExistObj = (CXSPRObj *)GetExistList()->PopBack();
				GetExistList()->PushFront( pTempExistObj );

				if ( ! pTempExistObj->LoadXSPR( strFileName ) )
				{
					PopFrontToExistListAndPushBackToEmptyList();
					return NULL;
				}

				m_XSPRMap.insert( XSPRPair( strFileName, pTempExistObj ) );
			}			
		}
	}

	return pTempExistObj->PutSprScreenT( siPosX, siPosY, siWidth, siHeight, siStartPos );
}

TSpr* CXSPRMgr::PutSprScreenRT( short ssActionIndex, TCHAR *strFileName, int siPosX, int siPosY, int siWidth, int siHeight, int siStartPos )
{	
	CXSPRObj *pTempExistObj = IsSameFileExist( strFileName );

	if ( pTempExistObj == NULL )
	{
		pTempExistObj = ( CXSPRObj * )PopFrontToEmptyListAndPushFrontToExistList();

		if ( pTempExistObj )
		{
			if ( ! pTempExistObj->LoadXSPR( strFileName ) )
			{
				PopFrontToExistListAndPushBackToEmptyList();
				return NULL;
			}

			m_XSPRMap.insert( XSPRPair( strFileName, pTempExistObj ) );
		}
		else
		{
			LoadSimilarXSPR( strFileName, ssActionIndex );

			pTempExistObj = IsSameFileExist( strFileName );

			if ( pTempExistObj == NULL )
			{
				pTempExistObj = (CXSPRObj *)GetExistList()->PopBack();
				GetExistList()->PushFront( pTempExistObj );

				if ( ! pTempExistObj->LoadXSPR( strFileName ) )
				{
					PopFrontToExistListAndPushBackToEmptyList();
					return NULL;
				}

				m_XSPRMap.insert( XSPRPair( strFileName, pTempExistObj ) );
			}
		}
	}

	return pTempExistObj->PutSprScreenRT( siPosX, siPosY, siWidth, siHeight, siStartPos );	
}

int CXSPRMgr::GetLoadedImageDataSize( unsigned int *pFileSize )
{
	int siCount = 0;
	*pFileSize = 0;

	CXSPRObj *pTemp = (CXSPRObj *)GetExistList()->GetFirst();

	while( pTemp )
	{
		*pFileSize += pTemp->GetImageFileSize();
		pTemp = (CXSPRObj *)pTemp->GetNext();
		++siCount;
	}

	return siCount;
}

int CXSPRMgr::GetLoadedImageNum()
{
	return GetExistList()->GetObjNum();
}

void CXSPRMgr::Action()
{
	UI32 CurrentFrame = pclClient->GetFrame();
	
	CXSPRObj *pTemp = (CXSPRObj *)GetExistList()->GetFirst();
	CXSPRObj *pTemp1 = NULL;

	map< tstring, CXSPRObj *>::iterator itr;

	while( pTemp )
	{	
		if ( pTemp->Action( CurrentFrame ) )
		{
			pTemp1 = (CXSPRObj *)pTemp->GetNext();
			
			itr = m_XSPRMap.find( pTemp->GetFileName() );
			if ( itr != m_XSPRMap.end() )
			{
				GetExistList()->Pop( pTemp );
				GetEmptyList()->PushBack( pTemp );
				pTemp->Initialize();
				
				m_XSPRMap.erase( itr );
			}
#ifdef _DEBUG
			else
			{
				MsgBox( pTemp->GetFileName(), TEXT("CCD No File Error") );
			}
#endif

			pTemp = pTemp1;
		}
		else
		{
			pTemp = (CXSPRObj *)pTemp->GetNext();
		}
	}

	return;
}