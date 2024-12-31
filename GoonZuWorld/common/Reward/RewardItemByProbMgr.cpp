#include ".\RewardItemByProbMgr.h"

CRewardTypeItemByProbMgr::CRewardTypeItemByProbMgr()
{
	m_uiRewardType = 0;
	m_uiItemCount  = 0;
	m_pVecRewardItem = NULL;
}

CRewardTypeItemByProbMgr::~CRewardTypeItemByProbMgr(void)
{
	Destroy();
}

//	������ ���� - ���� �а� �޸𸮿� ���
BOOL	CRewardTypeItemByProbMgr::Create(UI32 uiRewardType, UI32 uiCount)
{
	m_uiRewardType = 0;
	m_uiItemCount  = 0;
	m_pVecRewardItem = NULL;

	// ��������۸���Ʈ ����
	m_pVecRewardItem = NkNew NkVector<CRewardItemByProb>(uiCount,uiCount);
	
	// ���� Ÿ��
	m_uiRewardType = uiRewardType;

	return TRUE;
}
// ����
BOOL	CRewardTypeItemByProbMgr::Destroy()
{
	if( NULL != m_pVecRewardItem)
	{
		NkDelete m_pVecRewardItem;
		m_pVecRewardItem = NULL;
	}

	return TRUE;
}


// ������ ������ �м��Ѵ�. 
BOOL	CRewardTypeItemByProbMgr::AnalyzeItemInfo(TCHAR* pszData)
{
	TCHAR szTemp;

	// ������ 
	TCHAR szItemName[MAX_PATH];
	SI32 siItemNameIndex = 0;
	bool bItemNameSwitch = false;

	// ������ �ִ��
	TCHAR szItemNum[MAX_PATH];
	SI32 siItemNumIndex	= 0;
	bool bItemNumSwitch = true;

	// ������ �ּҼ�
	TCHAR szItemMinNum[MAX_PATH];
	SI32 siItemMinNumIndex	= 0;
	bool bItemMinNumSwitch = true;

	// ������ Ȯ��
	TCHAR szItemPbt[128];
	SI32 siItemPbtIndex	= 0;
	bool bItemPbtSwitch = false;

	SI32 siTextIndex	= 0;

	bool bUnLimitLoop = true;

	
	while( bUnLimitLoop )
	{
		szTemp = pszData[siTextIndex];
		if(szTemp == '\0')break;

		siTextIndex++;

		// Space�� �����Ѵ�. 
		if( szTemp == ' ')continue;
		if( szTemp == '+')
		{
			bItemNameSwitch	= false;
			bItemNumSwitch	= true;
			bItemMinNumSwitch = true;

			continue;
		}
		if( szTemp == '(')
		{
			szItemName[siItemNameIndex] = '\0';	// �̸��� �������Ѵ�. 
			siItemNameIndex	= 0;

			bItemNameSwitch = true;	// �̸��� ���Դ�. ������ ������Ȯ�� ������. 
			continue;
		}
		if( szTemp == '-')
		{
			bItemMinNumSwitch = false;	// ������ �ּҼ��� ���ϴ� ����̴�. 
		}
		if( szTemp == ':')
		{
			bItemMinNumSwitch = true ;
			bItemNumSwitch = false;	// ������ �ִ���� ���ϴ� ����̴�. 
		}
		if( szTemp == ')')
		{

			szItemMinNum[siItemMinNumIndex] = '\0';	// ������ �ּҼ��� �������Ѵ�. 
			siItemMinNumIndex	= 0;	

			szItemNum[siItemNumIndex] = '\0';		// ������ �ִ���� �������Ѵ�. 
			siItemNumIndex	= 0;	

			szItemPbt[siItemPbtIndex] = '\0';		// ������ Ȯ���� �������Ѵ�. 
			siItemPbtIndex	= 0;

			//-------------------------------------------
			// �̸��� Ȯ���� ��� �������Ƿ� �м��Ѵ�. 
			//-------------------------------------------

			// NULL�̸� �����Ѵ�. 
			if(_tcscmp(szItemName, TEXT("NULL")) == 0)
			{
				return FALSE;
			}

			SI32 siUnique = _tstoi(szItemName);
			SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique(siUnique);
			//if(unique)
			if ( ref > 0 )
			{
				SI32 itempbt	= _tstoi(szItemPbt);

				SI32 itemnum;
				SI32 minnum;

				if(bItemNumSwitch == false )
				{
					itemnum = _tstoi(szItemNum);
			
					if(itemnum <= 0)	itemnum	= 1;

					minnum = _tstoi(szItemMinNum);
					if(minnum <= 0)	minnum	= 1;

					if ( minnum > itemnum )
						minnum = 1 ;
				}
				else
				{
					itemnum = 1;
					minnum = 1;
				}
				
				// ���� ������ ���� �Է�
		
				CRewardItemByProb& clRewardItemByProb = m_pVecRewardItem->GetData(m_uiItemCount);
				clRewardItemByProb.SetMinNum(minnum);
				clRewardItemByProb.SetNum(itemnum);
				clRewardItemByProb.SetProb(itempbt);
				clRewardItemByProb.SetUnique(siUnique);

				++m_uiItemCount;
			}
			else
			{
				MsgBox(TEXT("NotProperItem"), TEXT("text:[%s] itemname:[%s]"), pszData, szItemName);
			}
			continue;
		}

		// �������� �̸��� ���� �������� �ʾ����� �̸��� �Է¹޴´�. 
		if(bItemNameSwitch  == false)
		{
			szItemName[siItemNameIndex ] = szTemp;
			siItemNameIndex ++;
			if(siItemNameIndex  > 100)return false;
		}
		else if(bItemMinNumSwitch  == false)
		{
			// ������ �ּҼ��� ���Ѵ�. 
			if(szTemp != '-')
			{
				szItemMinNum[siItemMinNumIndex] = szTemp;
				siItemMinNumIndex++;
				if(siItemMinNumIndex > 100)return false;
			}
		}
		else if(bItemNumSwitch   == false)
		{
			// ������ �ִ���� ���Ѵ�. 
			if(szTemp != ':')
			{
				szItemNum[siItemNumIndex] = szTemp;
				siItemNumIndex++;
				if(siItemNumIndex > 100)return false;
			}
		}
		else
		{
			szItemPbt[siItemPbtIndex] = szTemp;
			siItemPbtIndex++;
		}

	}
	
	return TRUE;
}
// ������ ����
BOOL	CRewardTypeItemByProbMgr::GetRandItemUnique(UI32* puiUnique,UI32* puiNum)
{
	srand((unsigned)time(NULL));
	UI32 uiRandValue = rand() % MAX_RANDVALUE;


	UI32 uiTemp = 0;
	
	for(UI32 i = 0 ; i < m_uiItemCount; i++)
	{
		CRewardItemByProb& pclRewardItemByProb = m_pVecRewardItem->GetData(i);
		
		// ������ ���� Ȯ�� ��ġ�� ���Ѵ�.
		uiTemp = uiTemp + pclRewardItemByProb.GetProb();

		if(  uiRandValue <= uiTemp)
		{	
			
			if(pclRewardItemByProb.GetNum() != 0)
				*puiNum = (rand() % pclRewardItemByProb.GetNum()) + 1;
			*puiNum = 0;
			*puiUnique = pclRewardItemByProb.GetUnique();

			return TRUE;
		}
	}
	
	return FALSE;
}
UI32	CRewardTypeItemByProbMgr::GetType()
{
	return m_uiRewardType;
}

//========================================================================================================

CRewardItemByProbMgr::CRewardItemByProbMgr()
{

}
CRewardItemByProbMgr::~CRewardItemByProbMgr()
{
	Destroy();
}
// ����
BOOL	CRewardItemByProbMgr::Create()
{	
	for( SI32 siCount = REWARDTYPE::BATTLEROYAL_WINNER ; siCount <= REWARDTYPE::COUNT ; siCount++ )
	{
		CRewardTypeItemByProbMgr pclRewardTypeItemByProbMgr;
		m_pVecRewardItemMgr.PushBack(pclRewardTypeItemByProbMgr);
		if( FALSE == m_pVecRewardItemMgr.GetBackData().Create(  siCount , CRewardTypeItemByProbMgr::INIT_ITEMCOUNT ))
		{
			return FALSE;
		}
	}
		
	// ���� �ε�
	if( FALSE == LoadFileData())
		return FALSE;
	return TRUE;
}
// ����
BOOL	CRewardItemByProbMgr::Destroy()
{
	SI32 siCount = m_pVecRewardItemMgr.GetCount();

	for(SI32 i = 0; i < siCount; i++)
	{
		m_pVecRewardItemMgr.GetData(i).Destroy();
	}

	return TRUE;
}

// ���� ������ �ε�
BOOL	CRewardItemByProbMgr::LoadFileData()
{
	NDataLoader	dataloader;

	const SI32	MAX_TEXT = 1024;

	bool bResult = FALSE;

	// ��ȣȭ ����
	if( pclClient->IsWhereServiceArea(ConstSwitch_TextEncryption))
		bResult = dataloader.LoadDataFromCryptFile(TEXT("Data/RewardTypeItemInfo.txt"));
	else
		bResult = dataloader.LoadDataFromFile(TEXT("Data/RewardTypeItemInfo.txt"));

	if (FALSE == bResult)
		return FALSE;

	SI32	siType = 0;
	TCHAR	szItemDataInfo[MAX_TEXT] = { TEXT('\0') };

	NDataTypeInfo pDataTypeInfo[] =
	{
		NDATA_INT32,	&siType,	4,
		NDATA_MBSTRING,	&szItemDataInfo,	MAX_TEXT,
			0,0,0
	};

	// �����Ͱ� ��� ������ �ѱ�
	dataloader.RegDataType(pDataTypeInfo);

	// ������ �о� ���� 
	while(dataloader.IsEndOfData() != true) 
	{
		if (dataloader.ReadData() == true)	
		{
			CRewardTypeItemByProbMgr& pclRewardTypeItemByProbMgr = m_pVecRewardItemMgr.GetData(siType - 1);
			pclRewardTypeItemByProbMgr.AnalyzeItemInfo(szItemDataInfo);
		}
		else
			break;

	}
	return TRUE;
}

CRewardTypeItemByProbMgr*	CRewardItemByProbMgr::GetRewardTypeItemByProbMgr(UI32 uiRewardType)
{
	if( REWARDTYPE::COUNT < uiRewardType)
	{
		return NULL;
	}
	return (CRewardTypeItemByProbMgr*)&m_pVecRewardItemMgr.GetData(uiRewardType - 1);
}
