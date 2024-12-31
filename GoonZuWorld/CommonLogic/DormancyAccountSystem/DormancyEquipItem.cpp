#include ".\dormancyequipitem.h"


CDormancyEquipItem::CDormancyEquipItem(void)
{
	ZeroMemory(this, sizeof(CDormancyEquipItem));
}
CDormancyEquipItem::~CDormancyEquipItem(void)
{

}

// ���׷��̵� �� Ÿ�� ��� �������� ����ũ�� �����Ѵ�.
BOOL	CDormancyEquipItem::InsertTargetItem(SI32 siTargetUnique, SI32 siUpgradeLevel)
{
	if( 0 > siUpgradeLevel)
		return FALSE;

	if(siUpgradeLevel > MAX_ARRAY_SIZE)
		return FALSE;

#ifdef _DEBUG
	if( 0 != m_TargetItemUniqueArray[siUpgradeLevel])
		MsgBox("Error", "[CDormancyEquipItem]::check DormancyEquipItem.txt(Duplicate UpgradeLevel");
#endif

	m_TargetItemUniqueArray[siUpgradeLevel] = siTargetUnique;
	return TRUE;
}

// ���׷��̵� �� Ÿ�� ��� �������� ����ũ �� ����
SI32	CDormancyEquipItem::GetTargetItemUnique(SI32 siUpgradeLevel)
{
	if( 0 > siUpgradeLevel)
		return 0;

	if(MAX_ARRAY_SIZE <= siUpgradeLevel)
		return 0;

	for( SI32 siIndex = siUpgradeLevel; siIndex > 0 ; siIndex--  )
	{
		if( 0 != m_TargetItemUniqueArray[siIndex] )
			return m_TargetItemUniqueArray[siIndex];	
	}

	return 0;
}

VOID	CDormancyEquipItem::SetBoxUnique(SI32 siBoxUnique)
{
	m_siBoxUnique = siBoxUnique;
}
VOID	CDormancyEquipItem::SetUnique(SI32 siUnique)
{
	m_siUnique = siUnique;
}

const	SI32	CDormancyEquipItem::GetBoxUnique() const
{
	return m_siBoxUnique;
}
const	SI32	CDormancyEquipItem::GetUnique() const
{
	return m_siUnique;
}


//============================================================

CDormancyEquipItemMgr::CDormancyEquipItemMgr(void)
{
	ZeroMemory(this, sizeof(CDormancyEquipItemMgr));
}

CDormancyEquipItemMgr::~CDormancyEquipItemMgr(void)
{
	
}

//	������ ���� - ���� �а� �޸𸮿� ���
BOOL	CDormancyEquipItemMgr::Create()
{
	NDataLoader	dataloader;

	BOOL bResult =FALSE;

	// ��ȣȭ ����
	if( pclClient->IsWhereServiceArea(ConstSwitch_TextEncryption))
		bResult = dataloader.LoadDataFromCryptFile(TEXT("Data/DormancyEquipItem.txt"));
	else
		bResult = dataloader.LoadDataFromFile(TEXT("Data/DormancyEquipItem.txt"));

	if (FALSE == bResult)
		return FALSE;

	SI32	siItemUnique = 0;
	SI32	siUpgradeLevel = 0;
	SI32	siTargetItemUnique = 0;

	NDataTypeInfo pDataTypeInfo[] =
	{
			NDATA_INT32,	&siItemUnique,	4,
			NDATA_INT32,	&siUpgradeLevel,	4,
			NDATA_INT32,	&siTargetItemUnique,	4,
			0,0,0
	};

	// �����Ͱ� ��� ������ �ѱ�
	dataloader.RegDataType(pDataTypeInfo);

	SI32 siCount = -1;

	// ������ �о� ���� 
	while(dataloader.IsEndOfData() != true) 
	{
		if (dataloader.ReadData() == true)	
		{
			// ������ ����Ʈ�� ���� ���� ���� ��츸 �߰�
			if(!IsExist(siItemUnique))
			{
				++siCount;
				if( MAX_ITEM_COUNT <= siCount)
				{
#ifdef _DEBUG
					if(MAX_ITEM_COUNT <= siCount)
						MsgBox("Error", "[CDormancyEquipItemMgr]::check MAX_ITEM_COUNT");
#endif
					break;
				}
				m_ItemArray[siCount].SetUnique(siItemUnique);
				
				// ������ ������ �޸� ���� ������ ���� �ƴ��� �οﰪ �Է�
				SetIsDormancyToItemInfo(siItemUnique);
			}
			m_ItemArray[siCount].InsertTargetItem(siTargetItemUnique,siUpgradeLevel);
		}
		else
			break;

	}
	return TRUE;
}
// ������ ������ �޸� ���� ������ ���� �ƴ��� �οﰪ �Է�
BOOL	CDormancyEquipItemMgr::SetIsDormancyToItemInfo(SI32 siUnique)
{
	cltItemManagerCommon *pclItemManager = pclClient->pclItemManager;
	if( NULL == pclItemManager)
		return FALSE;
	
	cltItemInfo *pclItemInfo = pclItemManager->FindItemInfo(siUnique);
	if( NULL == pclItemInfo)
		return FALSE;
	pclItemInfo->SetDormancy( TRUE );
	
	return TRUE;
}


// �޸� ���� ��� ������ 
CDormancyEquipItem *CDormancyEquipItemMgr::GetDormancyEquipItem(SI32 siUnique)
{
	if( siUnique <= 0)
		return NULL;

	CDormancyEquipItem *pclDormancyEquipItem = NULL;
	for(SI32 i = 0; i< MAX_ITEM_COUNT;i++)
	{
		pclDormancyEquipItem = &m_ItemArray[i];

		if(NULL == pclDormancyEquipItem)
			return NULL;

		if(pclDormancyEquipItem->GetUnique() == siUnique)
		{
			return pclDormancyEquipItem;
		}	
	}

	return NULL;
}

// ������ ����ũ�� ���� �ϴ��� ���� 
BOOL	CDormancyEquipItemMgr::IsExist(SI32 siUnique)
{
	cltItemManagerCommon *pclItemManager = pclClient->pclItemManager;
	if( NULL == pclItemManager)
		return FALSE;

	cltItemInfo *pclItemInfo = pclItemManager->FindItemInfo(siUnique);
	if( NULL == pclItemInfo)
		return FALSE;
	
	return pclItemInfo->IsDormancy();
}