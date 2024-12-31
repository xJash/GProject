#include ".\dormancybox.h"

CDormancyBox::CDormancyBox(void)
{
	ZeroMemory(this, sizeof(CDormancyBox));
}

CDormancyBox::~CDormancyBox(void)
{

}

// ���ڿ� ��� �������� �ִ´�.  
BOOL	CDormancyBox::InsertItem(CDormancyEquipItem *pclDormancyEquipItem)
{
	if(m_siItemCount >= MAX_ITEM_COUNT)
		return FALSE;

	m_ItemArray[m_siItemCount] = pclDormancyEquipItem;

	++m_siItemCount;

	return TRUE;
}

// ���ڿ� ��� �ִ� ������ ��
SI32	CDormancyBox::GetItemCount() const
{
	return m_siItemCount;
}

VOID	CDormancyBox::SetUnique(SI32 siUnique)
{
	m_siUnique = siUnique;
}
SI32	CDormancyBox::GetUnique() const
{
	return m_siUnique;
}

// �ε����� ��� �������� ��´�.
CDormancyEquipItem*	CDormancyBox::GetEquipItem(SI32 siIndex)
{
	if( 0 > siIndex)
		return NULL;
	if(siIndex >= MAX_ITEM_COUNT)
		return NULL;

	return m_ItemArray[siIndex];
}

//================================================================================================================

CDormancyBoxMgr::CDormancyBoxMgr(CDormancyEquipItemMgr *pclDormancyEquipItemMgr)
{
	m_pclDormancyEquipItemMgr = pclDormancyEquipItemMgr;

	m_siCount = 0;
}

CDormancyBoxMgr::CDormancyBoxMgr(void)
{
	
}

CDormancyBoxMgr::~CDormancyBoxMgr(void)
{
	
}

//	������ ���� - ���� �а� �޸𸮿� ���
BOOL	CDormancyBoxMgr::Create()
{
	NDataLoader	dataloader;

	bool bResult =FALSE;

	// ��ȣȭ ����
	if( pclClient->IsWhereServiceArea(ConstSwitch_TextEncryption))
		bResult = dataloader.LoadDataFromCryptFile(TEXT("Data/SelectBox.txt"));
	else
		bResult = dataloader.LoadDataFromFile(TEXT("Data/SelectBox.txt"));

	if (FALSE == bResult)
		return FALSE;

	if( NULL == m_pclDormancyEquipItemMgr )
		return FALSE;

	SI32	siBoxKind = 0;
	SI32	siItemUnique = 0;
	SI32	siBoxUnique = 0;

	NDataTypeInfo pDataTypeInfo[] =
	{
		NDATA_INT32,	&siBoxKind,	4,
		NDATA_INT32,	&siItemUnique,	4,
		NDATA_INT32,	&siBoxUnique,	4,
		0,0,0
	};

	// �����Ͱ� ��� ������ �ѱ�
	dataloader.RegDataType(pDataTypeInfo);

	m_siCount = -1;
	CDormancyEquipItem* pTempDormancyEquipItem = NULL;
	
	// ������ �о� ���� 
	while(dataloader.IsEndOfData() != true) 
	{
		if (dataloader.ReadData() == true)	
		{
			// ���� ���� ����Ʈ�� ���� ���� ���� ��츸 �߰�
			if(!IsExist(siBoxUnique))
			{
				++m_siCount;
				if( MAX_ITEM_COUNT <= m_siCount)
				{
#ifdef _DEBUG
					MsgBox("Error", "[CDormancyBoxMgr]::check MAX_ITEM_COUNT");
#endif
				break;
				}

				m_ItemArray[m_siCount].SetUnique(siBoxUnique);
			}

			// ���� ��� ������
			pTempDormancyEquipItem = m_pclDormancyEquipItemMgr->GetDormancyEquipItem(siItemUnique);

			pTempDormancyEquipItem->SetBoxUnique(siBoxUnique);

			// ���� ��� �������� ���� ���ڿ� �ִ´�.
			m_ItemArray[m_siCount].InsertItem(pTempDormancyEquipItem);
		}
		else
			break;

	}
	return TRUE;
}
// ������ ����ũ�� ���� ���ڰ� ���� �ϴ��� ���� 
BOOL	CDormancyBoxMgr::IsExist(SI32 siUnique)
{
	if( NULL != GetDormancyBox(siUnique))
		return TRUE;
	
	return FALSE;
}

// �޸� ���� ���� ����
CDormancyBox *CDormancyBoxMgr::GetDormancyBox(SI32 siUnique)
{
	if( siUnique <= 0)
		return NULL;

	CDormancyBox *pclDormancyBox = NULL;
	for(SI32 i = 0; i< MAX_ITEM_COUNT;i++)
	{
		pclDormancyBox = &m_ItemArray[i];

		if(NULL == pclDormancyBox)
			return NULL;

		if(pclDormancyBox->GetUnique() == siUnique)
		{
			return pclDormancyBox;
		}	
	}
	return NULL;
}

// �޸� ���� ���� ���� (�Ŵ����� �ε�����)
CDormancyBox *CDormancyBoxMgr::GetDormancyBoxByIndex(SI32 siIndex)
{
	if( 0 > siIndex)
		return NULL;

	if( siIndex >= MAX_ITEM_COUNT)
		return NULL;

	return &m_ItemArray[siIndex];
}

// �ڽ� ��
SI32	CDormancyBoxMgr::GetCount()
{
	return m_siCount + 1;
}
