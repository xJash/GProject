#include "IDNumTable.h"

unsigned int MyHashFunc_1( int key )
{
	return key;
}

cltIDNumTable::cltIDNumTable()
{
	m_hashtable.CreateHashTable( 4000, 10000, MyHashFunc_1 );
}

cltIDNumTable::~cltIDNumTable()
{

}


bool cltIDNumTable::AddIDNum( int idnum, int charid )
{
	int cid = 0;

	// �̹� �ؽ� ���̺� ��� �Ǿ� ������ ����,,
	if( m_hashtable.Find( idnum, &cid ) ) {
		
		if( cid == charid ) return false;

		m_hashtable.Remove( idnum );

	}

	m_hashtable.Insert( idnum, charid );

	return true;
}

bool cltIDNumTable::DelIDNum( int idnum )
{
	return m_hashtable.Remove( idnum );
}

int cltIDNumTable::GetCharIDFromIDNum( int idnum )
{
	int cid = 0;

	if( m_hashtable.Find( idnum, &cid ) == true ) return cid;

	return -1;
}

