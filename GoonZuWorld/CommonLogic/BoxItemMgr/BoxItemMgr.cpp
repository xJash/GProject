
#include "BoxItemMgr.h"

extern cltCommonLogic* pclClient;

/************************************************************************************************************************
* Ŭ���� �̸� : CBoxItemUnit
* ���� : ���� �����ۿ� �� ���� ������ ������
************************************************************************************************************************/
CBoxItemUnit::CBoxItemUnit( void )
	: m_uiItemUnique(0)
	, m_uiMinNum(0)
	, m_uiMaxNum(0)
	, m_uiItemUseDate(0)
	, m_uiProbability(0)
	, m_uiCanNotice(0)
{
	
}

CBoxItemUnit::CBoxItemUnit( UI16 uiItemUnique, UI16 uiMinNum, UI16 uiMaxNum, UI16 uiItemUseDate, UI16 uiProbability, UI16 uiCanNotice )
	: m_uiItemUnique(uiItemUnique)
	, m_uiMinNum(uiMinNum)
	, m_uiMaxNum(uiMaxNum)
	, m_uiItemUseDate(uiItemUseDate)
	, m_uiProbability(uiProbability)
	, m_uiCanNotice(uiCanNotice)
{

}

CBoxItemUnit::CBoxItemUnit( const CBoxItemUnit* pclBoxItemUnit )
{
	if ( pclBoxItemUnit )
	{
		memcpy( this, pclBoxItemUnit, sizeof(CBoxItemUnit) );
	}
}

CBoxItemUnit::~CBoxItemUnit( void )
{

}

void CBoxItemUnit::Init( void )
{
	ZeroMemory( this, sizeof(CBoxItemUnit) );
}

void CBoxItemUnit::SetBoxItemUnit( UI16 uiItemUnique, UI16 uiMinNum, UI16 uiMaxNum, UI16 uiItemUseDate, UI16 uiProbability, UI16 uiCanNotice )
{
	m_uiItemUnique	= uiItemUnique;
	m_uiMinNum		= uiMinNum;
	m_uiMaxNum		= uiMaxNum;
	m_uiItemUseDate	= uiItemUseDate;
	m_uiProbability	= uiProbability;
	m_uiCanNotice	= uiCanNotice;
}

void CBoxItemUnit::SetBoxItemUnit( const CBoxItemUnit* pclBoxItemUnit )
{
	if ( pclBoxItemUnit )
	{
		memcpy( this, pclBoxItemUnit, sizeof(CBoxItemUnit) );
	}
}

UI16 CBoxItemUnit::GetItemNum( void ) const
{
	// min > max ���(�� ���� ���ҽ��� �߸��Ȱ��̶�� ����)
	// min == max ���
	// min < max ���
	// ���� ������ ��Ȳ�� ����ؾ� �Ѵ�

	if ( m_uiMinNum < m_uiMaxNum )
	{
		UI16 uiRange		= m_uiMaxNum - m_uiMinNum;
		UI16 uiReturnValue	= (rand() % uiRange) + m_uiMinNum;

		return uiReturnValue;
	}
	else if ( m_uiMinNum == m_uiMaxNum )
	{
		return m_uiMinNum; // min�̳� max ���� ����� �����ص� ��
	}

	return 0;
}

/************************************************************************************************************************
* Ŭ���� �̸� : CBoxItemSet
* ���� : �ϳ��� ���� �������� ���� Ŭ����
************************************************************************************************************************/
CBoxItemSet::CBoxItemSet( void )
	: m_uiBoxItemUnique(0)
	, m_uiBoxItemType(0)
	, m_pclVecBoxItemUnit(NULL)
{
}

CBoxItemSet::CBoxItemSet( UI16 uiBoxItemUnique, UI16 uiBoxItemType, NkVec_BoxItemUnit* pclVecBoxItemUnit/* =NULL  */)
	: m_uiBoxItemUnique(uiBoxItemUnique)
	, m_uiBoxItemType(uiBoxItemType)
	, m_pclVecBoxItemUnit(pclVecBoxItemUnit)
{
}

CBoxItemSet::CBoxItemSet( const CBoxItemSet& rclBoxItemSet )
	: m_uiBoxItemUnique(rclBoxItemSet.m_uiBoxItemUnique)
	, m_uiBoxItemType(rclBoxItemSet.m_uiBoxItemType)
	, m_pclVecBoxItemUnit(rclBoxItemSet.m_pclVecBoxItemUnit)
{

}

CBoxItemSet::~CBoxItemSet( void )
{
	ClearBoxItemUnit();

	if ( m_pclVecBoxItemUnit )
	{
		// ����
		NkDelete m_pclVecBoxItemUnit;
		m_pclVecBoxItemUnit = NULL;
	}
}

/************************************************************************************************************************
* �Լ��� : Init
* ��  �� : �ʱ�ȭ
* ��  �� :
* ���ϰ� : 
************************************************************************************************************************/
void CBoxItemSet::Init( void )
{
	m_uiBoxItemUnique	= 0;
	m_uiBoxItemType		= 0;

	ClearBoxItemUnit();
}

/************************************************************************************************************************
* �Լ��� : ClearBoxItemUnit
* ��  �� : ������ ����� ��� �޸𸮸� �����Ѵ�
* ��  �� :
* ���ϰ� : 
************************************************************************************************************************/
void CBoxItemSet::ClearBoxItemUnit( void )
{
	if ( m_pclVecBoxItemUnit )
	{
		// ���ο� �ִ� �����͸� ���� �����Ѵ�
		UI32 uiMaxCount = m_pclVecBoxItemUnit->GetCount();
		for ( UI32 uiIndex=0; uiIndex<uiMaxCount; uiIndex++ )
		{
			delete m_pclVecBoxItemUnit->GetData(uiIndex);
		}
	}
}

/************************************************************************************************************************
* �Լ��� : GetRandItem
* ��  �� : ������ ��� �߿��� ���������� ����ü�� �����ϰ� �ϳ� �����´�
* ��  �� :
* ���ϰ� : �����ϰ� �������� CBoxItemUnit������
************************************************************************************************************************/
CBoxItemUnit* CBoxItemSet::GetRandItem( void )
{
	if ( NULL == m_pclVecBoxItemUnit )
	{
		return NULL;
	}

	SI32 siGetItemRandValue		= rand() % Const_Max_BoxItemMgr_Probability;
	SI32 siNowValue				= 0;
	SI32 siProbility			= 0;

	UI32 uiMaxCount				= m_pclVecBoxItemUnit->GetCount();
	for ( UI32 uiIndex=0; uiIndex<uiMaxCount; uiIndex++ )
	{
		siProbility = m_pclVecBoxItemUnit->GetData(uiIndex)->GetProbability();

		if ( (siNowValue <= siGetItemRandValue) && (siGetItemRandValue < siNowValue+siProbility) )
		{
			return m_pclVecBoxItemUnit->GetData(uiIndex);
		}

		siNowValue += siProbility;
	}

	return NULL;
}

/************************************************************************************************************************
* �Լ��� : LoadBoxItemSet
* ��  �� : ���� ������ ���ҽ��� �о�´�
*			���������� ����
* ��  �� :	TCHAR* szFileName	- �о�� ���ҽ� ���� �̸� ("ServerData/Box/'����ũ'.txt" �� ������)
* ���ϰ� : ���������� ���ҽ��� �о�Դٸ� TRUE
************************************************************************************************************************/
BOOL CBoxItemSet::LoadBoxItemSet( TCHAR* const szFileName )
{
	NDataLoader	dataloader;
	BOOL		bLoadFile	= FALSE;

	if( pclClient->IsWhereServiceArea( ConstSwitch_TextEncryption ) )
	{
		bLoadFile = dataloader.LoadDataFromCryptFile( szFileName );		
	}
	else
	{
		bLoadFile = dataloader.LoadDataFromFile( szFileName );
	}

	if (!bLoadFile)
	{
		MsgBox(TEXT("Error"), TEXT("LoadError:[%s]"), szFileName);
		return FALSE;
	}

	if ( NULL == m_pclVecBoxItemUnit )
	{
		m_pclVecBoxItemUnit = NkNew NkVec_BoxItemUnit;
	}

	SI32 siItemUnique	= 0;
	SI32 siMinNum		= 0;
	SI32 siMaxNum		= 0;
	SI32 siUseDate		= 0;
	SI32 siProbability	= 0;
	SI32 siCanNotice	= 0;

	//Ȯ�� ����
	SI32 siTotalProb	= 0; // ������ ���ھȿ� �� ��ǰ�� Ȯ�� ����Const_Max_BoxItemMgr_Probability �̾�� �Ѵ�

	NDataTypeInfo pDataTypeInfo[] =
	{
		NDATA_INT32,	&siItemUnique,	4,
		NDATA_INT32,	&siMinNum,		4,
		NDATA_INT32,	&siMaxNum,		4,
		NDATA_INT32,	&siUseDate,		4,
		NDATA_INT32,	&siProbability,	4,
		NDATA_INT32,	&siCanNotice,	4,
		0,0,0
	};

	dataloader.RegDataType( pDataTypeInfo );

	while( !dataloader.IsEndOfData() )
	{
		if( dataloader.ReadData())
		{
			CBoxItemUnit* pclBoxItemUnit = new CBoxItemUnit( siItemUnique, siMinNum, siMaxNum, siUseDate, siProbability, siCanNotice );

			m_pclVecBoxItemUnit->PushBack( pclBoxItemUnit );

			// Ȯ�� Ȯ�ο�
			siTotalProb += siProbability;
		}
	}

	// ���̻� ���� ���� ����
	m_pclVecBoxItemUnit->Resize();

	if ( Const_Max_BoxItemMgr_Probability != siTotalProb )
	{
		MsgBox(TEXT("Error"), TEXT("Probility Over Max[%d]/Now[%d], File[%s]"), Const_Max_BoxItemMgr_Probability, siTotalProb, szFileName);
		return FALSE;
	}

	return TRUE;
}

/************************************************************************************************************************
* �Լ��� : GetInItemList
* ��  �� : �ȿ� ����ִ� �������� ����Ʈ�� ���´�
* ��  �� :	SI32* psiInBoxItemList	- ������ ����Ʈ�� ������ �迭
*			UI32 uiListCount		- ������ ����Ʈ�� ������ �迭�� ����
* ���ϰ� : ������ ����Ʈ�� ������ ����
************************************************************************************************************************/
UI32 CBoxItemSet::GetInItemList( OUT SI32* psiInBoxItemList, IN const UI32 uiListCount )
{
	if ( (NULL == psiInBoxItemList) || (0 == uiListCount) )
	{
		return 0;
	}

	if ( NULL == m_pclVecBoxItemUnit )
	{
		return 0;
	}

	UI32 uiMaxCount	= min(m_pclVecBoxItemUnit->GetCount(), uiListCount);

	for ( UI32 uiIndex=0; uiIndex<uiMaxCount; uiIndex++ )
	{
		psiInBoxItemList[uiIndex] = m_pclVecBoxItemUnit->GetData(uiIndex)->GetItemUnique();
	}

	return uiMaxCount;
}

/************************************************************************************************************************
* �Լ��� : IsItemCanNotice
* ��  �� : �μ��� ���� �������� ��� ��ǰ���� �˻�
* ��  �� :	SI32 siInItemUnique		- ���� ������ �ȿ� ����ִ� ������ ����ũ
* ���ϰ� : ��� ��ǰ�� �´ٸ� TRUE
************************************************************************************************************************/
BOOL CBoxItemSet::IsItemCanNotice( const SI32 siInItemUnique )
{
	if ( NULL == m_pclVecBoxItemUnit )
	{
		return FALSE;
	}

	UI32 uiMaxCount	= m_pclVecBoxItemUnit->GetCount();
	for ( UI32 uiIndex=0; uiIndex<uiMaxCount; uiIndex++ )
	{
		if ( m_pclVecBoxItemUnit->GetData(uiIndex)->GetItemUnique() == siInItemUnique )
		{
			return DATA_TO_TYPE_BOOL( m_pclVecBoxItemUnit->GetData(uiIndex)->GetCanNotice() );
		}
	}

	return FALSE;
}

/************************************************************************************************************************
* Ŭ���� �̸� : CBoxItemMgr
* ���� : ��� ���� �������� ������
************************************************************************************************************************/
CBoxItemMgr::CBoxItemMgr( void )
{

}

CBoxItemMgr::~CBoxItemMgr( void )
{

}

/************************************************************************************************************************
* �Լ��� : LoadBoxItemInfo
* ��  �� : ���� �������� �⺻�� �Ǵ� ���� ���ҽ��� �о�´�
* ��  �� :
* ���ϰ� : ���������� ���ҽ��� �о�Դٸ� TRUE
************************************************************************************************************************/
BOOL CBoxItemMgr::LoadBoxItemInfo( void )
{
	NDataLoader	dataloader;
	BOOL		bLoadFile	= FALSE;
	TCHAR*		szFileName	= TEXT("Data/BoxInfo.txt");

	if( pclClient->IsWhereServiceArea( ConstSwitch_TextEncryption ) )
	{
		bLoadFile = dataloader.LoadDataFromCryptFile( szFileName );		
	}
	else
	{
		bLoadFile = dataloader.LoadDataFromFile( szFileName );
	}

	if (!bLoadFile)
	{
		MsgBox(TEXT("Error"), TEXT("LoadError:[%s]"), szFileName);
		return FALSE;
	}

	SI32 siItemUnique	= 0;
	SI32 siItemMode		= 0;

	NDataTypeInfo pDataTypeInfo[] =
	{
		NDATA_INT32,	&siItemUnique,	4,
		NDATA_INT32,	&siItemMode,	4,
		0,0,0
	};

	dataloader.RegDataType( pDataTypeInfo );

	while( !dataloader.IsEndOfData() )
	{
		if( dataloader.ReadData())
		{
			CBoxItemSet clBoxItemSet( siItemUnique, siItemMode );

			m_clMapBoxItemSet.Insert( siItemUnique, clBoxItemSet );
		}
	}

	return TRUE;
}

/************************************************************************************************************************
* �Լ��� : LoadAllBoxItemSet
* ��  �� : ��� ���� ����ũ ���ҽ��� �о�´�
*			���������� ����
* ��  �� :
* ���ϰ� :
************************************************************************************************************************/
void CBoxItemMgr::LoadAllBoxItemSet( void )
{
	TCHAR			szFileName[MAX_PATH]	= {0,};
	SI32			siItemUnique			= 0;

	UI32			uiMaxCount				= m_clMapBoxItemSet.GetCount();

	NkRbTreeMapPos	kPos					= m_clMapBoxItemSet.GetBeginPos();

	for ( UI32 uiCount=0; uiCount<uiMaxCount; uiCount++ )
	{
		siItemUnique = m_clMapBoxItemSet.GetKey( kPos );
		if ( 0 < siItemUnique )
		{
			StringCchPrintf( szFileName, MAX_PATH, TEXT("ServerData/Box/%d.txt"), siItemUnique );

			m_clMapBoxItemSet.GetData( kPos ).LoadBoxItemSet( szFileName );
		}

		// ���� ������
		kPos = m_clMapBoxItemSet.GetNextPos( kPos );
	}
	/*
	for ( NkRbTreeMapPos kPos=m_clMapBoxItemSet.GetBeginPos(); kPos!=m_clMapBoxItemSet.GetEndPos(); kPos=m_clMapBoxItemSet.GetNextPos(kPos) )
	{
		siItemUnique = m_clMapBoxItemSet.GetKey( kPos );
		if ( 0 < siItemUnique )
		{
			StringCchPrintf( szFileName, MAX_PATH, TEXT("ServerData/Box/%d.txt"), siItemUnique );

			m_clMapBoxItemSet.GetData( kPos ).LoadBoxItemSet( szFileName );
		}
	}
	*/

}

/************************************************************************************************************************
* �Լ��� : GetRandItemFromUnique
* ��  �� : Ư�� ���� �����۾ȿ� ����ִ� ���������� ����ü�� �����ϰ� �ϳ� �����´�
* ��  �� :	SI32 siBoxItemUnique	- ���� ������ ����ũ
* ���ϰ� : �����ϰ� �������� CBoxItemUnit������
************************************************************************************************************************/
CBoxItemUnit* CBoxItemMgr::GetRandItemFromUnique( const SI32 siBoxItemUnique )
{
	CBoxItemSet* pclBoxItemSet = m_clMapBoxItemSet.FindDataPtr(siBoxItemUnique);

	if ( NULL == pclBoxItemSet )
	{
		return NULL;
	}

	return pclBoxItemSet->GetRandItem();
}

/************************************************************************************************************************
* �Լ��� : IsSameBoxItemType
* ��  �� : Ư�� ���� �������� Ÿ���� �μ��� ���� Ÿ���� �´��� �˻�
* ��  �� :	SI32 siBoxItemUnique	- ���� ������ ����ũ
*			SI32 siBoxItemType		- �˻��ϰ��� �ϴ� Ÿ��
* ���ϰ� : �ش� Ÿ���� ���� �������� �´ٸ� TRUE
************************************************************************************************************************/
BOOL CBoxItemMgr::IsSameBoxItemType( const SI32 siBoxItemUnique, const SI32 siBoxItemType )
{
	// ���� ����ũ Ȯ��
	CBoxItemSet* pclBoxItemSet = m_clMapBoxItemSet.FindDataPtr(siBoxItemUnique);
	if ( NULL == pclBoxItemSet )
	{
		return FALSE;
	}

	// ���Ȯ��
	if ( pclBoxItemSet->GetBoxITemType() != siBoxItemType )
	{
		return FALSE;
	}

	return TRUE;
}
/************************************************************************************************************************
* �Լ��� : GetInBoxItemList
* ��  �� : Ư�� ���� ������ �ȿ��� ������ �������� ����Ʈ�� ���´�
* ��  �� :	SI32 siBoxItemUnique	- ���� ������ ����ũ
*			SI32* psiInBoxItemList	- ������ ����Ʈ�� ������ �迭
*			UI32 uiListCount		- ������ ����Ʈ�� ������ �迭�� ����
* ���ϰ� : ������ ����Ʈ�� ������ ����
************************************************************************************************************************/
UI32 CBoxItemMgr::GetInBoxItemList( IN const SI32 siBoxItemUnique, OUT SI32* psiInBoxItemList, IN const UI32 uiListCount )
{
	CBoxItemSet* pclBoxItemSet = m_clMapBoxItemSet.FindDataPtr(siBoxItemUnique);
	if ( NULL == pclBoxItemSet )
	{
		return 0;
	}

	return pclBoxItemSet->GetInItemList( psiInBoxItemList, uiListCount );
}

/************************************************************************************************************************
* �Լ��� : IsInBoxItemCanNotice
* ��  �� : Ư�� ���� ������ �ȿ��� ������ �������� ��� ��ǰ������ �˻��Ѵ�
* ��  �� :	SI32 siBoxItemUnique	- ���� ������ ����ũ
*			SI32 siInItemUnique		- ���� ������ �ȿ� ����ִ� ������ ����ũ
* ���ϰ� : ��ڹ�ǰ�ϰ�� TRUE
************************************************************************************************************************/
BOOL CBoxItemMgr::IsInBoxItemCanNotice( const SI32 siBoxItemUnique, const SI32 siInItemUnique )
{
	CBoxItemSet* pclBoxItemSet = m_clMapBoxItemSet.FindDataPtr(siBoxItemUnique);
	if ( NULL == pclBoxItemSet )
	{
		return FALSE;
	}

	return pclBoxItemSet->IsItemCanNotice( siInItemUnique );
}
