#include "DrawSequenceMgr.h"
#include "DrawSequenceObj.h"
#include "..\..\Common\SMLib\LibList\LibList.h"

CDrawSequenceMgr::CDrawSequenceMgr() : CLibListMgr()
{
	m_pVerticalList = new CLibList();
	
	m_si32VerticalObjNum = 0;

	Initialize();
}

CDrawSequenceMgr::~CDrawSequenceMgr()
{
	Destroy();
}

void CDrawSequenceMgr::Initialize()
{
	return;
}

void CDrawSequenceMgr::Destroy()
{
	if ( m_pVerticalList )
	{
		delete m_pVerticalList;
		m_pVerticalList = NULL;
	}

	return;
}

void CDrawSequenceMgr::CreateMaxEmptyObj( int si32MaxObjNum )
{
	CDrawSequenceObj *pTemp = NULL;

	for ( int i = 0; i < si32MaxObjNum; ++i )
	{
		pTemp = new CDrawSequenceObj();
		PushBackToEmptyList( pTemp );
	}

	return;
}

void CDrawSequenceMgr::Push( SI32 XPos, SI32 YPos, SI32 XSize, SI32 YSize, cltDrawObjData *pclData )
{
	CDrawSequenceObj *pNewObj = ( CDrawSequenceObj * ) PopFrontToEmptyList();

	if ( pNewObj == NULL )
	{
		//MessageBox( NULL, TEXT("���� ����"), TEXT("eTgfj"), MB_OK |MB_TOPMOST);
		return;
	}

	/*
	if ( m_si32VerticalObjNum > 5 )
	{
		return;
	}
	*/

	++m_si32VerticalObjNum;
	

	pNewObj->ObjPtrInitialize();								// �ȿ� ����ִ� �����͵� ������ �ʱ�ȭ
	pNewObj->Initialize();										// �ȿ� ����ִ� �����͵� ������ �ʱ�ȭ
	
	pNewObj->SetData( XPos, YPos, XSize, YSize, pclData );		// �����͵� ���� �ٽ� ����

	if ( m_pVerticalList->GetFirst() == NULL )
	{		
		m_pVerticalList->PushBack( pNewObj );
		return;
	}
	
	CDrawSequenceObj *pVerticalTemp = ( CDrawSequenceObj * ) m_pVerticalList->GetFirst();

	
	bool	bBeforeDraw = false;
	bool	bLaterDraw = false;
	bool	bNotRelativeDraw = false;

	while ( pVerticalTemp )
	{
		switch ( pVerticalTemp->IsDrawingLater( XPos, YPos, XSize, YSize ) )
		{
		case BEFORE_DRAW_SEQUENCE:
			{
				if ( bBeforeDraw )
				{
					break;
				}

				bBeforeDraw = true;

				if ( pVerticalTemp->GetPre() )
				{
					pNewObj->SetNext( pVerticalTemp );
					pNewObj->SetPre( pVerticalTemp->GetPre() );

					pVerticalTemp->GetPre()->SetNext( pNewObj );
					pVerticalTemp->SetPre( pNewObj );
				}
				else
				{
					pNewObj->SetNext( pVerticalTemp );
					pVerticalTemp->SetPre( pNewObj );
					m_pVerticalList->SetFirst( pNewObj );
				}
			}
			break;
		case LATER_DRAW_SEQUENCE:
			{
				bLaterDraw = true;

				if ( bBeforeDraw )				// bBeforeDraw == true �� �� �����, �ڿ��� Ȯ���� ��尡 �ִٴ� ����. ( ��� 3��, new �� �տ� beforedraw ���� �־��� ��ü��, ���� �̳��̶� ��� 3�� ), �׸��� �� �� pVerticalTemp ���� �տ��� ��尡 Ȯ���� ����.
				{
					if( pNewObj->GetPre() )
					{
						CDrawSequenceObj *pTemp1 = pVerticalTemp;
						pVerticalTemp = ( CDrawSequenceObj * )pVerticalTemp->GetNext();

						if ( pTemp1->GetPre() )
						{
							pTemp1->GetPre()->SetNext( pTemp1->GetNext() );
						}
						else
						{
							MessageBox( NULL, TEXT("ErAGDfaG"), TEXT("dsafawefl"), MB_OK |MB_TOPMOST);
						}

						if ( pTemp1->GetNext() )
						{
							pTemp1->GetNext()->SetPre( pTemp1->GetPre() );
						}
						else
						{
							pTemp1->GetPre()->SetNext( NULL );
							m_pVerticalList->SetLast( pTemp1->GetPre() );
						}
						

						pTemp1->SetNext( pNewObj );
						pTemp1->SetPre( pNewObj->GetPre() );

						pNewObj->GetPre()->SetNext( pTemp1 );
						pNewObj->SetPre( pTemp1 );

						continue;
					}
					else
					{
						CDrawSequenceObj *pTemp1 = pVerticalTemp;
						pVerticalTemp = ( CDrawSequenceObj * )pVerticalTemp->GetNext();

						if ( pTemp1->GetPre() )
						{
							pTemp1->GetPre()->SetNext( pTemp1->GetNext() );
						}
						else
						{
							MessageBox( NULL, TEXT("ErAGDfaG"), TEXT("dsafawefl"), MB_OK |MB_TOPMOST);
						}

						if ( pTemp1->GetNext() )
						{
							pTemp1->GetNext()->SetPre( pTemp1->GetPre() );
						}
						else
						{
							pTemp1->GetPre()->SetNext( NULL );
							m_pVerticalList->SetLast( pTemp1->GetPre() );
						}
						

						pTemp1->SetNext( pNewObj );
						pTemp1->SetPre( NULL );

						pNewObj->SetPre( pTemp1 );

						m_pVerticalList->SetFirst( pTemp1 );

						continue;
					}
				}
				else
				{




				}
			}
			break;
		case NOT_RELATIVE_SEQUENCE:
			{
				bNotRelativeDraw = true;
			}
			break;
		}

		pVerticalTemp = ( CDrawSequenceObj * )pVerticalTemp->GetNext();
	}

	if ( ! bBeforeDraw )
	{
		m_pVerticalList->PushBack( pNewObj );
	}

	return;
}

cltDrawObjData *CDrawSequenceMgr::Pop()
{
	if ( m_si32VerticalObjNum == 0 )
	{
		return NULL;
	}

	/*
	if ( si32Size > MAX_DRAW_DATA_SIZE )
	{
		MessageBox( NULL, TEXT("Size Over"), TEXT("error"), MB_OK |MB_TOPMOST);
		return false;
	}
	*/

	CDrawSequenceObj *pTemp = ( CDrawSequenceObj * )m_pVerticalList->PopFront();
	pTemp->ObjPtrInitialize();
	GetEmptyList()->PushBack( pTemp );

	//memcpy( pData, pTemp->GetDrawSequenceData(), si32Size );
	//pTemp->Initialize();

	--m_si32VerticalObjNum;

	return pTemp->GetDrawSequenceData();
}
