#include "ITZCell.h"
#include "ITZWorld.h"
#include "ITZList.h"
#include "ITZPerson.h"
#include "ITZSendBuffer.h"

ITZCell::ITZCell()
{
	m_pWorld = NULL;

	m_pMap = NULL;

	m_ppItem = NULL;

	m_uiItemSlotCount = 0;

	m_uiPlayerCount = 0;
}

ITZCell::~ITZCell()
{

	delete [] m_ppItem;
	m_ppItem = NULL;
}

void ITZCell::CreateCell( ITZWorld< ITZMap > *pWorld, ITZMap *pMap )
{

	m_pWorld = pWorld;

	m_pMap = pMap;

	m_personPtrList.CreateList();

	for( int i = 0; i < 9; ++i ) {
		m_pNearCell[ i ] = NULL;
	}

	m_uiNearCellCount = 0;

	m_uiItemSlotCount = 0;
}

// ���� Person�� �߰��Ѵ� 
void ITZCell::SetPerson( ITZPerson *pPerson )
{
	ITZObjectPtr *pObjPtr = m_personPtrList.push_from( &m_pWorld->m_personPtrList );

	if( pObjPtr == NULL ) {
		return;
	}

	m_pWorld->m_count++;

	pObjPtr->SetObject( (ITZObject *)pPerson );

	pPerson->SetMap( m_pMap );
	pPerson->SetCell( this );
	pPerson->m_siCellPersonIndex = (int)( pObjPtr->m_usIndex );

	// �߰� �Ǵ� ĳ���Ͱ� �÷��̾� ĳ�����̸�, ī��Ʈ�� ������Ų��.
	if( pPerson->GetSession() ) m_uiPlayerCount++;
}

// ������ Person�� �����Ѵ� 
void ITZCell::DelPerson( ITZPerson *pPerson )
{
	if( pPerson->GetCell() == NULL ) return;

	ITZObjectPtr *pObjPtr = m_pWorld->m_personPtrList.get( pPerson->m_siCellPersonIndex );

	if( pObjPtr == NULL ) {
		return;
	}

	m_pWorld->m_count--;

	m_personPtrList.remove_into( pObjPtr, &(m_pWorld->m_personPtrList) );

	pPerson->SetMap( NULL );
	pPerson->SetCell( NULL );
	pPerson->m_siCellPersonIndex = -1;

	// ���� �Ǵ� ĳ���Ͱ� �÷��̾� ĳ�����̸�, ī��Ʈ�� ���ҽ�Ų��.
	if( pPerson->GetSession() ) m_uiPlayerCount--;
}

// ���� ���� �������� ���ÿ����� �ִ� ��� �÷��̾�鿡�� ��Ŷ�� ������ 
void ITZCell::SendPacketNearAll( sPacketHeader *pPacket )
{
	for( UI32 i = 0; i < m_uiNearCellCount; ++i ) {

		m_pNearCell[ i ]->SendPacket( pPacket );
	}
}

void ITZCell::SendPacketNearAll( BYTE *pPacket )
{
	for( UI32 i = 0; i < m_uiNearCellCount; ++i ) {

		m_pNearCell[ i ]->SendPacket( pPacket );
	}
}

void ITZCell::SendPacketNearAllExceptOne( ITZPerson *pExceptedPerson, sPacketHeader *pPacket )
{
	for( UI32 i = 0; i < m_uiNearCellCount; ++i ) 
	{
		m_pNearCell[ i ]->SendPacketExceptOne( pExceptedPerson, pPacket );
	}
}

void ITZCell::SendPacketNearAllExceptOne( ITZPerson *pExceptedPerson, BYTE *pPacket )
{
	for( UI32 i = 0; i < m_uiNearCellCount; ++i ) 
	{
		m_pNearCell[ i ]->SendPacketExceptOne( pExceptedPerson, pPacket );
	}
}


// ���� ���� ��� �÷��̾�鿡�� ��Ŷ�� ������
void ITZCell::SendPacket( sPacketHeader *pPacket )
{
	ITZObjectPtr *pObjPtr;
	ITZPerson *pPerson;
	
	LIST_LOOP( &m_personPtrList, pObjPtr )	
	{

		pPerson = (ITZPerson *)(pObjPtr->GetObject());

		if( pPerson == NULL )continue;
		if( pPerson->GetSession() == NULL )continue;

		pPerson->GetSendBuffer()->Write( (BYTE *)pPacket );
	}
}

void ITZCell::SendPacket( BYTE *pPacket )
{
	ITZObjectPtr *pObjPtr;
	ITZPerson *pPerson;

	LIST_LOOP( &m_personPtrList, pObjPtr )	
	{
		pPerson = (ITZPerson *)(pObjPtr->GetObject());

		if( pPerson == NULL )					continue;
		if( pPerson->GetSession() == NULL )		continue;

		pPerson->GetSendBuffer()->Write( pPacket );
	}
}

void ITZCell::SendPacketExceptOne( ITZPerson *pExceptedPerson, sPacketHeader *pPacket )
{
	ITZObjectPtr *pObjPtr;
	ITZPerson *pPerson;
	
	LIST_LOOP( &m_personPtrList, pObjPtr )	
	{

		pPerson = (ITZPerson *)(pObjPtr->GetObject());

		if( pPerson == NULL )continue;
		if( pPerson->GetSession() == NULL)continue;

		if( pPerson == pExceptedPerson )continue;

		pPerson->GetSendBuffer()->Write( (BYTE *)pPacket );		
	}	
}

void ITZCell::SendPacketExceptOne( ITZPerson* pExceptedPerson, BYTE *pPacket )
{
	ITZObjectPtr *pObjPtr;
	ITZPerson *pPerson;

	LIST_LOOP( &m_personPtrList, pObjPtr )	
	{
		pPerson = (ITZPerson *)(pObjPtr->GetObject());

		if( pPerson == NULL )					continue;
		if( pPerson->GetSession() == NULL)		continue;
		if( pPerson == pExceptedPerson )		continue;

		pPerson->GetSendBuffer()->Write( pPacket );
	}	
}

BOOL ITZCell::IsTherePlayerNearCells()
{
	for( UI32 i = 0; i < m_uiNearCellCount; ++i ) {

		if( m_pNearCell[ i ]->GetPlayerCount() > 0 ) return TRUE;
	}

	return FALSE;
}



