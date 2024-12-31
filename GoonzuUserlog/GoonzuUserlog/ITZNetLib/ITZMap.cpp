#include "ITZMap.h"
#include "ITZWorld.h"
#include "ITZCell.h"
#include "ITZPerson.h"

ITZMap::ITZMap()
{

	m_pWorld = NULL;

	m_pCell = NULL;
	
	m_pItem = NULL;

	m_uiCellCount = 0;

	m_uiRemoveCellCount = 0;
	m_uiNewCellCount = 0;
}

ITZMap::~ITZMap()
{
	delete [] m_pCell;
	delete [] m_pItem;
	
	m_pCell = NULL;
	m_pItem = NULL;
}

void ITZMap::SetWorld( ITZWorld< ITZMap >* pWorld )
{

	m_pWorld = pWorld;
}

void ITZMap::CreateMap( int mapXtile, int mapYtile )
{

	if( mapXtile > mapYtile ) mapYtile = mapXtile;
	if( mapXtile < mapYtile ) mapXtile = mapYtile;

	m_mapXtile = mapXtile;
	m_mapYtile = mapYtile;

	// �� ����/���� ���� ���� ���
	m_mapXcell = ( mapXtile + m_pWorld->m_cellXtile - 1 ) / m_pWorld->m_cellXtile;
	m_mapYcell = ( mapYtile + m_pWorld->m_cellYtile - 1 ) / m_pWorld->m_cellYtile;

	// �� ����
	m_uiCellCount = m_mapXcell * m_mapYcell;

	m_pCell = new ITZCell[ m_uiCellCount ];

	int j, k, x, y, t;

	for( UI32 i = 0; i < m_uiCellCount; ++i ) {

		m_pCell[ i ].CreateCell( m_pWorld, this ); 
		
		// ���� ������ ���� �ʱ�ȭ 
		m_pCell[ i ].m_ppItem = new sItem*[ ( m_pWorld->m_cellXtile + 1 ) * ( m_pWorld->m_cellYtile + 1 ) * 2 ];
		m_pCell[ i ].m_uiItemSlotCount = 0;

		x = i % m_mapXcell;
		y = i / m_mapXcell;

		m_pCell[ i ].m_uiNearCellCount = 0;

		for( j = -1; j < 2; ++j ) {

			for( k = -1; k < 2; ++k ) {

				if( ( x + k ) >= 0 && ( x + k ) < m_mapXcell &&
					( y + j ) >= 0 && ( y + j ) < m_mapYcell ) {

					t = ( y + j ) * m_mapXcell +  x + k;

					m_pCell[ i ].m_pNearCell[  m_pCell[ i ].m_uiNearCellCount  ] = &m_pCell[ t ];

					m_pCell[ i ].m_uiNearCellCount++;
				}

			}

		}

	}


	// ������ ���� ���� �� �ʱ�ȭ
	m_pItem = new sItem[ m_mapXtile * m_mapYtile ];
	
	ITZCell *pCell;
	sItem item;

	for( j = 0; j < m_mapYtile; ++j ) {
		for( k = 0; k < m_mapXtile; ++k ) {

			item.x = k;
			item.y = j;
			item.itemIndex = 0;

			m_pItem[ j * m_mapXtile + k ] = item;

			pCell = GetCell( k, j );
			
			pCell->m_ppItem[ pCell->m_uiItemSlotCount++ ] = &m_pItem[ j * m_mapXtile + k ];
		}
	}

}

int ITZMap::GetCellIndex( int x, int y )
{
	int sx = ( m_mapXtile - y - 1 + x ) / ( m_pWorld->m_cellXtile << 1 );
	int sy = ( x + y ) / ( m_pWorld->m_cellYtile << 1 );

	return m_mapXcell * sy + sx;
}

// �㿡�� x, y Ÿ�� ��ǥ�� �ش��ϴ� ���� ��´�
ITZCell* ITZMap::GetCell( int x, int y )
{
	int sx = ( m_mapXtile - y - 1 + x ) / ( m_pWorld->m_cellXtile << 1 );
	int sy = ( x + y ) / ( m_pWorld->m_cellYtile << 1 );
	int index = m_mapXcell * sy + sx;

	if( index < 0 || index >= m_mapXcell * m_mapYcell ) return NULL;

	return &m_pCell[ index ];
}

void ITZMap::Warp( int x, int y, ITZPerson *pPerson, bool bticketusewarpswitch )
{
	
	ITZCell *pCurrentCell = pPerson->GetCell(); 

	if( pCurrentCell )
	{
		// ���� �޽����� ���� ������ ��´� 
		SetCellList( pCurrentCell, NULL );

		// ���� �޽����� ������
		SendPersonLeaveMsgToOthers( pPerson);

		// ������ ĳ���͸� �����Ѵ� 
		pCurrentCell->DelPerson( pPerson );
	}

	MoveChar( x, y, pPerson, bticketusewarpswitch  );
}

void ITZMap::MoveChar( int x, int y, ITZPerson *pPerson, bool bticketusewarpswitch  )
{

	// �̵� �� ������ x, y ��ǥ�� �ش��ϴ� ���� ���Ѵ� 
	ITZCell *pOldCell = pPerson->GetCell();
	ITZCell *pCurrentCell = GetCell( x, y );

	if( pCurrentCell == NULL ) return;

	if( pOldCell == NULL ) {
		
		// ������ �Ҽӵ� ���� ���� ��� - �̵��� �ƴ϶� ���ڱ� ��Ÿ���� ���..(�α�����������)
		// ���� �߰��� �� ����Ʈ�� ��´�( ó�� ���� ��� �ǹǷ� ���� ���� ���ڴ� NULL�̴� )
		SetCellList( NULL, pCurrentCell );

		// ���� �߰��� ���� �ִ� ĳ���Ϳ� ������ ������ ��´� 
		SendNewOthersInfoToPerson( pPerson );
		SendNewItemsInfoToPerson( pPerson );

		// �ڽ��� ������ �ٸ� ĳ���͵鿡�� �˸��� 
		SendPersonEnterMsgToOthers( pPerson, bticketusewarpswitch );

		// ���� ���� Person�� �����Ѵ� 
		pCurrentCell->SetPerson( pPerson );


	} else {

		if( pOldCell != pCurrentCell ) {
			// ���� �ٲ� ���

			// ������ ĳ���Ͱ� ��ġ�ϰ� �ִ� ���� ���� ���� ���Ͽ�
			// ������ ��, �߰��� ���� ���Ѵ� ( ��� ���� ��� ������ ����.. ���� ȣ�� �ñ��� ��ȿ)
			SetCellList( pOldCell, pCurrentCell );

			// ���� ������ Person�� �����Ѵ�
			pOldCell->DelPerson( pPerson );

			// ������ ���� �ִ� ĳ���͵鿡�� ĳ������ ����(����)�� �˸���
			SendPersonLeaveMsgToOthers( pPerson );

			// ���� �߰��� ���� �ִ� ĳ���Ϳ� ������ ������ ��´� 
			SendNewOthersInfoToPerson( pPerson );
			SendNewItemsInfoToPerson( pPerson );
			
			// ���� �߰��� ���� �ִ� ĳ���͵鿡�� ĳ������ �߰�(����)�� �˸��� 
			SendPersonEnterMsgToOthers( pPerson, bticketusewarpswitch );

			// ���� ���� Person�� �����Ѵ� 
			pCurrentCell->SetPerson( pPerson );
		}

		// ĳ���� �̵� ������ ���ÿ����� �ִ� ĳ���͵鿡�� ������ 
		SendPersonMoveMsgToOthers( pPerson );
	}	

}

void ITZMap::SetCellList( ITZCell *pOldCell, ITZCell *pCurrentCell )
{	

	UI32 i, j;
	
	m_uiRemoveCellCount = 0;
	m_uiNewCellCount = 0;
	
	if( pOldCell == NULL ) {
		// pOldCell�� NULL�̸� ���ο� �� ����Ʈ�� pCurrentCell�� �ֺ� ������ ��� �ִ´�
		
		for( i = 0; i < pCurrentCell->m_uiNearCellCount; ++i ) {
			
			m_pNewCell[ m_uiNewCellCount++ ] = pCurrentCell->m_pNearCell[ i ];
		}
		
	} else if( pCurrentCell == NULL ) {
		// pNewCell�� NULL�̸� ������ �� ����Ʈ�� pOldCell�� �ֺ� ������ ��� �ִ´� 
		
		for( i = 0; i < pOldCell->m_uiNearCellCount; ++i ) {
			
			m_pRemoveCell[ m_uiRemoveCellCount++ ] = pOldCell->m_pNearCell[ i ];
			
		}
		
	} else {
		// ������ �� ����Ʈ�� ���ο� �� ����Ʈ�� ���Ѵ�           

	  	for( i = 0; i < 9; ++i ) {
			
			if( pOldCell->m_pNearCell[ i ] ) {
				// remove cell ��� 
				for( j = 0; j < pCurrentCell->m_uiNearCellCount; ++j ) {
					
					if( pOldCell->m_pNearCell[ i ] == pCurrentCell->m_pNearCell[ j ] ) break;
				}
				
				if( j == pCurrentCell->m_uiNearCellCount ) {
					// remove cell�� �߰� 
					
					m_pRemoveCell[ m_uiRemoveCellCount++ ] = pOldCell->m_pNearCell[ i ];
				}
			}

			
			if( pCurrentCell->m_pNearCell[ i ] ) {
				
				// new cell ��� 	
				for( j = 0; j < pOldCell->m_uiNearCellCount; ++j ) { 

					if( pCurrentCell->m_pNearCell[ i ] == pOldCell->m_pNearCell[ j ] ) break;

				}

				if( j == pOldCell->m_uiNearCellCount ) {
					// new cell�� �߰� 

					m_pNewCell[ m_uiNewCellCount++ ] = pCurrentCell->m_pNearCell[ i ];
				}

			}

		}

	}

}


BOOL ITZMap::AddItem( int x, int y, UI16 itemIndex )
{

	sItem *pItem = &m_pItem[ y * m_mapXtile + x ];

	if( pItem->itemIndex != 0 ) return FALSE;
	
	pItem->itemIndex = itemIndex;

	SendAddItemMsgToOthers( pItem );

	return TRUE;
}


BOOL ITZMap::DelItem( int x, int y, UI16 itemIndex )
{

	sItem *pItem = &m_pItem[ y * m_mapXtile + x ];

	if( pItem->itemIndex == 0 ) return FALSE;
	
	SendDelItemMsgToOthers( pItem );

	pItem->itemIndex = 0;

	return TRUE;
}

