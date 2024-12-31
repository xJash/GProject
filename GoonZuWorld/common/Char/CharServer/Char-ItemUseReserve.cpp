//---------------------------------
// 2004/5/11 ���°�
//---------------------------------

#include "..\Common\CommonHeader.h"
#include "..\..\Server\Server.h"
#include "Char-Server.h"


void cltUseItemReserveInfo::Init()
{
	for(SI32 i = 0;i < MAX_USEITEM_RESERVE_NUM;i++)
	{
		clInfo[i].Init();
	}
}


bool cltUseItemReserveInfo::Push(SI32 unique, SI32 itemnum, SI32 itempos)
{
	SI32 i;
	
	for(i = 0;i < MAX_USEITEM_RESERVE_NUM;i++)
	{
		if(clInfo[i].siUnique == unique && (itempos == -1 || clInfo[i].siItemPos == itempos))
		{
			clInfo[i].siItemNum += itemnum;
			return true;
		}
	}
	
	for(i = 0;i < MAX_USEITEM_RESERVE_NUM;i++)
	{
		if(clInfo[i].siUnique == 0)
		{
			clInfo[i].siUnique	= unique;
			clInfo[i].siItemNum = itemnum;
			clInfo[i].siItemPos = itempos;
			return true;
		}
	}

	return false;
}

// ����Ǿ� �ִ� ���� �ִ°�. 
bool cltUseItemReserveInfo::IsReserved()
{
	SI32 i;
	
	for(i = 0;i < MAX_USEITEM_RESERVE_NUM;i++)
	{
		if(clInfo[i].siUnique)
		{
			return true;
		}
	}

	return false;
}


// ȭ�� �� źȯ ���� Ŭ����
void cltBulletUseReserveInfo::Init()
{
	for(SI32 i = 0;i < MAX_USEITEM_RESERVE_NUM;i++)
	{
		clInfo[i].Init();
	}
}


bool cltBulletUseReserveInfo::Push(SI32 unique, SI32 itemnum, SI32 itempos)
{
	SI32 i;

	for(i = 0;i < MAX_USEITEM_RESERVE_NUM;i++)
	{
		if(clInfo[i].siUnique == unique && clInfo[i].siItemPos == itempos)
		{
			clInfo[i].siItemNum += itemnum;
			return true;
		}
	}

	for(i = 0;i < MAX_USEITEM_RESERVE_NUM;i++)
	{
		if(clInfo[i].siUnique == 0)
		{
			clInfo[i].siUnique	= unique;
			clInfo[i].siItemNum = itemnum;
			clInfo[i].siItemPos = itempos;
			return true;
		}
	}

	return false;
}

// ����Ǿ� �ִ� ���� �ִ°�. 
bool cltBulletUseReserveInfo::IsReserved()
{
	SI32 i;

	for(i = 0;i < MAX_USEITEM_RESERVE_NUM;i++)
	{
		if(clInfo[i].siUnique)
		{
			return true;
		}
	}

	return false;
}

//-----------------------------------------------
// ��ȯ�� ȭ��/�Ѿ� ������ ��� �������
//-----------------------------------------------
cltSummonBulletUseReserveInfo::cltSummonBulletUseReserveInfo()
{
	Init();

}

void cltSummonBulletUseReserveInfo::Init()
{
	for ( SI32 siIndex=0; siIndex<MAX_USEITEM_RESERVE_NUM; siIndex++ )
	{
		m_clInfo[ siIndex ].Init();
	}

}

bool cltSummonBulletUseReserveInfo::Push( SI08 siSummonIndex, SI16 siItemUnique, SI16 siItemNum, SI16 siItemPos )
{
	if ( (0 > siSummonIndex) || (MAX_SUMMON_OWN<=siSummonIndex) )
	{
		return false;
	}

	SI32 siIndex = 0;

	//  ������ ���� �������� ����Ǿ� �ִ��� �˻��ؼ� ������ �װ��� �ִ´�
	for ( siIndex=0; siIndex<MAX_USEITEM_RESERVE_NUM; siIndex++ )
	{
		if ( (siSummonIndex		== m_clInfo[siIndex].m_siSummonIndex)	// ��ȯ�� �ε����˻�
			&& (siItemUnique	== m_clInfo[siIndex].m_siItemUnique)	// ������ ����ũ�˻�
			&& (siItemPos		== m_clInfo[siIndex].m_siItemPos)		// ������ ��ġ�˻�
		)
		{
			m_clInfo[ siIndex ].m_siItemNum += siItemNum;

			return true;
		}

		if ( 0 > m_clInfo[siIndex].m_siSummonIndex )
		{
			break;
		}
	}

	// ���� ����� �������� ���ٸ� ���ο� ���� �߰��Ѵ�
	for ( siIndex=0; siIndex<MAX_USEITEM_RESERVE_NUM; siIndex++ )
	{
		if ( 0 > m_clInfo[siIndex].m_siSummonIndex )
		{
			m_clInfo[ siIndex ].m_siSummonIndex	= siSummonIndex;
			m_clInfo[ siIndex ].m_siItemUnique	= siItemUnique;
			m_clInfo[ siIndex ].m_siItemNum		= siItemNum;
			m_clInfo[ siIndex ].m_siItemPos		= siItemPos;

			return true;
		}
	}

	return false;

}

bool cltSummonBulletUseReserveInfo::IsReserved()
{
	for ( SI32 siIndex=0; siIndex<MAX_USEITEM_RESERVE_NUM; siIndex++ )
	{
		if ( 0 <= m_clInfo[siIndex].m_siSummonIndex )
		{
			return true;
		}
	}

	return false;

}

