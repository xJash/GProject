#include "cltSetItem.h"
#include "cltItem.h"
#include "NDataLoader.h"
#include "NFile.h"
#include "NUtil.h"

#include "../../../CommonLogic/CommonLogic.h"

//#include "../../../Client/Client.h"
#include "../../../Server/Server.h"

extern cltCommonLogic* pclClient;

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CSetItemInfo cpp
/////////////////////////////////////////////////////////////////////////////////////////////////////
void CSetItemInfo::Init()
{
	m_siSetItemType = 0;

	for( SI16 i = 0; i < MAX_SETITEM_UNIQUE_NUMBER; ++i )
	{
		m_siSetItemUnique[i] = 0;
	}
}

void CSetItemInfo::SetSetItemInfo( SI16 SetItemType, SI32 SetItemUnique[] )
{
	m_siSetItemType = SetItemType;

	for( SI16 i = 0; i < MAX_SETITEM_UNIQUE_NUMBER; ++i )
	{
		m_siSetItemUnique[i] = SetItemUnique[i];
	}
}

void CSetItemInfo::SetSetItemInfo( CSetItemInfo& SetItemInfo )
{
	m_siSetItemType = SetItemInfo.GetSetItemType();

	for( SI16 i = 0; i < MAX_SETITEM_UNIQUE_NUMBER; ++i )
	{
		m_siSetItemUnique[i] = SetItemInfo.GetSetItemUnique(i);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CSetItemManager cpp
/////////////////////////////////////////////////////////////////////////////////////////////////////
void CSetItemManager::LoadSetItemInfo()
{
	NDataLoader	dataloader;
	BOOL bLoadFile=FALSE;

	TCHAR datfilename[MAX_PATH] = {0,};
	StringCchPrintf(datfilename,  MAX_PATH, TEXT("Item/Data/SetItemInfo.txt") );


	//KHY - 0809 - �ؽ�Ʈ ���ҽ� ��ȣȭ.
	if( pclClient->IsWhereServiceArea( ConstSwitch_TextEncryption ) )
	{
		bLoadFile = dataloader.LoadDataFromCryptFile( datfilename);		
	}
	else
	{
		if ( pclClient->IsWhereServiceArea(ConstServiceArea_China) )
		{
			bLoadFile = dataloader.LoadDataFromCryptFile( datfilename);
		}
		else
		{
			bLoadFile = dataloader.LoadDataFromFile( datfilename);
		}
	}


	if (!bLoadFile)
	{
		MsgBox(TEXT("LoadSetItemInfo()"), TEXT("LoadError:[%s]"), datfilename);
		return;
	}

	SI32  setItemType = 0;
	TCHAR setItemName[128] = { TEXT('\0') };	// ��� �׳� �б⸸ �Ѵ�.
	SI32  setItemUnique[MAX_SETITEM_UNIQUE_NUMBER] = {0,};
	SI16 index = 0;


	NDataTypeInfo pDataTypeInfo[] =
	{
		NDATA_INT32,	&setItemType,			4,		
		NDATA_MBSTRING,	setItemName,		  128,
		NDATA_INT32,	&setItemUnique[0], 		4,
		NDATA_INT32,	&setItemUnique[1], 		4,
		NDATA_INT32,	&setItemUnique[2], 		4,
		NDATA_INT32,	&setItemUnique[3], 		4,
		NDATA_INT32,	&setItemUnique[4], 		4,
		NDATA_INT32,	&setItemUnique[5], 		4,
		NDATA_INT32,	&setItemUnique[6], 		4,
		NDATA_INT32,	&setItemUnique[7], 		4,
		NDATA_INT32,	&setItemUnique[8], 		4,
		NDATA_INT32,	&setItemUnique[9], 		4,
		NDATA_INT32,	&setItemUnique[10], 	4,
		NDATA_INT32,	&setItemUnique[11], 	4,
		NDATA_INT32,	&setItemUnique[12], 	4,
		0,0,0
	};

	SI32 siSetItemNum = 0;	// ��Ʈ �������� ����.
	dataloader.RegDataType( pDataTypeInfo );
	
	bool bFirst = true;

	while( !dataloader.IsEndOfData() ) 
	{
		if( dataloader.ReadData())
		{
			if ( bFirst )
			{
				// ó�� ���ο��� ��Ʈ �������� ������ �ִ�.
				m_pclSetItemInfo = new CSetItemInfo[setItemType];
				siSetItemNum = setItemType;
				bFirst = false;
			}
			else
			{
				if( siSetItemNum <= index )
					MessageBox( NULL, "SetItem Num Difference", "SetItemInfo.txt", 0 );

				CSetItemInfo setItemInfo;
				setItemInfo.SetSetItemInfo( setItemType, setItemUnique );
				m_pclSetItemInfo[index].SetSetItemInfo( setItemInfo );
				index++;
			}
		}
	}
	m_siMaxSetItemNumber = index;
}

bool CSetItemManager::CompareSetItemUnique( SI16 Index, cltItem* pclItemList )
{
	cltServer* pclserver = GetServerClass();

	// �׳� �������� üũ�ؼ� ���Ͻ�Ű��
	if( m_pclSetItemInfo[Index].GetSetItemUnique(PERSONITEM_RING1) == pclItemList[PERSONITEM_RING1].siUnique ||
		m_pclSetItemInfo[Index].GetSetItemUnique(PERSONITEM_RING2) == pclItemList[PERSONITEM_RING2].siUnique ||
		m_pclSetItemInfo[Index].GetSetItemUnique(PERSONITEM_RING1) == 0 ||
		m_pclSetItemInfo[Index].GetSetItemUnique(PERSONITEM_RING2) == 0 )
	{
		for( SI16 i = 0; i < MAX_SETITEM_UNIQUE_NUMBER; ++i )
		{
			// ��Ʈ ������ �������� �ش� �ε����� 0�̸� �ʿ���� �����̱� ������ ������ �̹� üũ�ϴϱ�
			if( 0 == m_pclSetItemInfo[Index].GetSetItemUnique(i) || i == PERSONITEM_RING1 || i == PERSONITEM_RING2 )
				continue;

			if( m_pclSetItemInfo[Index].GetSetItemUnique(i) != pclItemList[i].siUnique )
			{
				return false;
			}

			//KHY - 0723 - �Ⱓ������ �ı� ����.
			//if(pclClient->IsWhereServiceArea( ConstSwitch_DateOverItemNoDestroy) )
			if(pclClient->IsCountrySwitch( Switch_DateOverItemNoDestroy) )
			{
				if(pclItemList[i].IsHaveUseDay() )
				{
					SI32 useableDay = 0;

					BOOL rVal = FALSE;

					if(pclClient->GameMode == GAMEMODE_SERVER)
					{
						rVal = pclserver->GetItemUseAbleDay(&pclItemList[i],&useableDay);
					}
					
					if(rVal == FALSE) 
						return false;
					
					if(useableDay < 0 )
						return false;										
				}
			}
		}
		return true;
	}
	else
		return false;
}

SI16 CSetItemManager::FindSetItemType( cltItem* pclItemList )
{
	for(SI16 i = 0; i < m_siMaxSetItemNumber; i++)
	{
		if( true == CompareSetItemUnique( i, pclItemList) )
		{
			return i + 1;
		}
	}

	return 0;
}

bool CSetItemManager::IsSetItemStep( SI16 _siType )
{
	switch(_siType)
	{
		case VAMPIRE_SETITEM:			// ���� ��Ʈ�� ������ �ִ°ǵ� ����� �ٲ��.
		case XMAS_SETITEM:
		case GIRL_SULBIM_SETITEM:
		case BOY_SULBIM_SETITEM:
		case HALLOWEEN1_SETITEM:
		case HALLOWEEN2_SETITEM:
		case HALLOWEEN3_SETITEM:
		case HALLOWEEN4_SETITEM:
		case FROZEN_SETITEM_STEP:
		case FLAME_SETITEM_STEP:
		case DEMON_SETITEM_STEP:
		case ABEL_SETITEM_STEP:
		case BLACKKNIGHT_SETITEM_STEP:
		case DEVIL_MAN:
		case DEVIL_WOMAN:
			{
				return true;
			}
			break;
	}

	return false;
}

bool CSetItemManager::CompareSetItemUniqueStep( SI16 Index, cltCharCommon* _pclchar, SI16* _psiStep, SI32 _UseSetItem )
{
	*_psiStep = 0;

	cltItem* pclItemList = &_pclchar->pclCI->clCharItem.clItem[0];

	cltServer* pclserver = GetServerClass();
	cltClient* pclclient = GetClientClass();

	SI32 StepCount = 0;
	SI32 returnval = 0;
	bool bIsSameRing = false;

	//  [7/20/2009 ��ȣ] �ҷ����� ó�� �Ǻ���Ʈ�� ���������� �� �𿩾� �ϹǷ� ���� ���� �˻���ƾ�� Ÿ�� �ʰ� �ٷ� 1:1��Ī üũ�մϴ�.
	//	�Ǻ� - �ҷ�����
	if(	Index + 1 == HALLOWEEN1_SETITEM || Index + 1 == HALLOWEEN2_SETITEM || Index + 1 == HALLOWEEN3_SETITEM || Index + 1 == HALLOWEEN4_SETITEM)
	{
		if(	m_pclSetItemInfo[Index].GetSetItemUnique(PERSONITEM_MANTLE) == pclItemList[PERSONITEM_MANTLE].siUnique &&
			m_pclSetItemInfo[Index].GetSetItemUnique(PERSONITEM_HAT)	== pclItemList[PERSONITEM_HAT].siUnique &&
			m_pclSetItemInfo[Index].GetSetItemUnique(PERSONITEM_DRESS)	== pclItemList[PERSONITEM_DRESS].siUnique)
		{
			// ���� 3������ ��� ��ġ�ؾ� �Ǻ� ��Ʈ������ ���� �����մϴ�.
			StepCount = 3;
		}
	}

	// �Ǻ�-����
	else if(Index + 1 == GIRL_SULBIM_SETITEM || Index + 1 == BOY_SULBIM_SETITEM)
	{
		if(	m_pclSetItemInfo[Index].GetSetItemUnique(PERSONITEM_DRESS) == pclItemList[PERSONITEM_DRESS].siUnique &&
			m_pclSetItemInfo[Index].GetSetItemUnique(PERSONITEM_HAT)	== pclItemList[PERSONITEM_HAT].siUnique)
		{
			StepCount = 2;
		}
	}

	// �Ǻ� - ��Ÿ
	else if(Index + 1 == XMAS_SETITEM)
	{
		if(	m_pclSetItemInfo[Index].GetSetItemUnique(PERSONITEM_MANTLE) == pclItemList[PERSONITEM_MANTLE].siUnique &&
			m_pclSetItemInfo[Index].GetSetItemUnique(PERSONITEM_HAT)	== pclItemList[PERSONITEM_HAT].siUnique &&
			m_pclSetItemInfo[Index].GetSetItemUnique(PERSONITEM_DRESS)	== pclItemList[PERSONITEM_DRESS].siUnique)
		{
			// ���� 3������ ��� ��ġ�ؾ� �Ǻ� ��Ʈ������ ���� �����մϴ�.
			StepCount = 3;
		}	
	}

	else
	{
		for( SI16 i = 0; i < MAX_SETITEM_UNIQUE_NUMBER; ++i )
		{
			// ���� ���� �˻�.
			//----------------------------------------------------------------------------------------
			//KHY - 0723 - �Ⱓ������ �ı� ����.
			//if(pclClient->IsWhereServiceArea( ConstSwitch_DateOverItemNoDestroy) )
			if(pclClient->IsCountrySwitch( Switch_DateOverItemNoDestroy) )
			{
				if(pclItemList[i].IsHaveUseDay() )
				{
					SI32 useableDay = 0;

					BOOL rVal = FALSE;

					if(pclClient->GameMode == GAMEMODE_SERVER)
					{
						rVal = pclserver->GetItemUseAbleDay(&pclItemList[i],&useableDay);
					}

					if(rVal == FALSE) 
						return false;

					if(useableDay < 0 )
						return false;										
				}
			}

			// ��Ʈ �����۵� ������ ���Ŀ� ���� �Ұ��� ���� �� �� �ִ�.
			if(pclClient->pclItemManager->CheckCondition(pclItemList[i].siUnique, _pclchar, &returnval) == false ) // - ���� ������ �����ؾ߸� �Ѵ�.
				continue;

			// ��Ʈ ������ �������� �ش� �ε����� 0�̸� �ʿ���� �����̱� ������ ������ �̹� üũ�ϴϱ�
			if( 0 == m_pclSetItemInfo[Index].GetSetItemUnique(i) )
				continue;
			//----------------------------------------------------------------------------------------

			//  [7/21/2009 ��ȣ] ��Ʈ�������� �����̾� ��Ʈ�������� �����, ����, ������ ����ũ 2���� ���Ѵ�.(������ �����ϰ��ִ� �������� �����̾������ ����)
			if(Index + 1 == VAMPIRE_SETITEM)
			{
				if(i == PERSONITEM_NECK)
				{
					if(	m_pclSetItemInfo[Index].GetSetItemUnique(i) == pclItemList[i].siUnique || ITEMUNIQUE(1190) == pclItemList[i].siUnique)
					{
						//  [7/21/2009 ��ȣ] �Ⱓ�� ���� �������� ��Ʈȿ�� ���뿡�� ����.
						SI32 useableDay = 0;
						BOOL rVal = FALSE;

						if(pclClient->GameMode == GAMEMODE_CLIENT)
							rVal = pclclient->GetItemUseAbleDay(&pclItemList[i], &useableDay);
						else if(pclClient->GameMode == GAMEMODE_SERVER)
							rVal = pclserver->GetItemUseAbleDay(&pclItemList[i], &useableDay);

						//  [7/21/2009 ��ȣ] �����ۻ��Ⱓ�� ���� ��쿡�� step ����
						if(useableDay >= 0)
							++StepCount;
					}
				}

				else if(i == PERSONITEM_MANTLE)
				{
					if(	m_pclSetItemInfo[Index].GetSetItemUnique(i) == pclItemList[i].siUnique || ITEMUNIQUE(18520) == pclItemList[i].siUnique)
					{
						//  [7/21/2009 ��ȣ] �Ⱓ�� ���� �������� ��Ʈȿ�� ���뿡�� ����.
						SI32 useableDay = 0;
						BOOL rVal = FALSE;

						if(pclClient->GameMode == GAMEMODE_CLIENT)
							rVal = pclclient->GetItemUseAbleDay(&pclItemList[i], &useableDay);
						else if(pclClient->GameMode == GAMEMODE_SERVER)
							rVal = pclserver->GetItemUseAbleDay(&pclItemList[i], &useableDay);

						//  [7/21/2009 ��ȣ] �����ۻ��Ⱓ�� ���� ��쿡�� step ����
						if(useableDay >= 0)
							++StepCount;
					}
				}

				else if(i == PERSONITEM_RING1 || i == PERSONITEM_RING2)
				{
					if(	m_pclSetItemInfo[Index].GetSetItemUnique(i) == pclItemList[i].siUnique || ITEMUNIQUE(7600) == pclItemList[i].siUnique)
					{
						//  [7/21/2009 ��ȣ] �Ⱓ�� ���� �������� ��Ʈȿ�� ���뿡�� ����.
						SI32 useableDay = 0;
						BOOL rVal = FALSE;

						if(pclClient->GameMode == GAMEMODE_CLIENT)
							rVal = pclclient->GetItemUseAbleDay(&pclItemList[i], &useableDay);
						else if(pclClient->GameMode == GAMEMODE_SERVER)
							rVal = pclserver->GetItemUseAbleDay(&pclItemList[i], &useableDay);

						//  [7/21/2009 ��ȣ] �����ۻ��Ⱓ�� ���� ��쿡�� step ����
						if(useableDay >= 0)
							++StepCount;
					}
				}

				else
				{
					if( m_pclSetItemInfo[Index].GetSetItemUnique(i) == pclItemList[i].siUnique )
					{
						//  [7/21/2009 ��ȣ] �Ⱓ�� ���� �������� ��Ʈȿ�� ���뿡�� ����.
						SI32 useableDay = 0;
						BOOL rVal = FALSE;

						if(pclClient->GameMode == GAMEMODE_CLIENT)
							rVal = pclclient->GetItemUseAbleDay(&pclItemList[i], &useableDay);
						else if(pclClient->GameMode == GAMEMODE_SERVER)
							rVal = pclserver->GetItemUseAbleDay(&pclItemList[i], &useableDay);

						//  [7/21/2009 ��ȣ] �����ۻ��Ⱓ�� ���� ��쿡�� step ����
						if(useableDay >= 0)
							++StepCount;
					}
				}
			}
			
			else
			{
				// ��Ʈ ������ �˻� ++
				if( m_pclSetItemInfo[Index].GetSetItemUnique(i) == pclItemList[i].siUnique )
				{
					//  [7/21/2009 ��ȣ] �Ⱓ�� ���� �������� ��Ʈȿ�� ���뿡�� ����.
					SI32 useableDay = 0;
					BOOL rVal = FALSE;

					if(pclClient->GameMode == GAMEMODE_CLIENT)
						rVal = pclclient->GetItemUseAbleDay(&pclItemList[i], &useableDay);
					else if(pclClient->GameMode == GAMEMODE_SERVER)
						rVal = pclserver->GetItemUseAbleDay(&pclItemList[i], &useableDay);

					//  [7/21/2009 ��ȣ] �����ۻ��Ⱓ�� ���� ��쿡�� step ����
					if(useableDay >= 0)
						++StepCount;
				}
			}

			//	[��ȣ]setitem ������ ��� ���� unique�� ���� �ΰ��� �ߺ� �����Ű�� �ʴ´�. ������ �� ������ �����ϰ�
			//	step�� ������Ű�Ƿ� �̺κп��� üũ�� ���������ش�.

			
			//  [7/21/2009 ��ȣ] ���Ǽ� ������ ��� ������ �����ϰ��ִ� ������ ���Ǽ� �����̳� ����ũ�� �ٸ��Ƿ� �ߺ�üũ���ش�.
			if(Index + 1 == VAMPIRE_SETITEM)
			{
				if(((m_pclSetItemInfo[Index].GetSetItemUnique(i) == pclItemList[PERSONITEM_RING1].siUnique) || (pclItemList[PERSONITEM_RING1].siUnique == ITEMUNIQUE(7600))) &&		
					((m_pclSetItemInfo[Index].GetSetItemUnique(i) == pclItemList[PERSONITEM_RING2].siUnique) || (pclItemList[PERSONITEM_RING2].siUnique == ITEMUNIQUE(7600))))
				{
					bIsSameRing = true;
				}
			}
			else
			{
				if(	(m_pclSetItemInfo[Index].GetSetItemUnique(i) == pclItemList[PERSONITEM_RING1].siUnique) &&		
					(m_pclSetItemInfo[Index].GetSetItemUnique(i) == pclItemList[PERSONITEM_RING2].siUnique)  )
				{
					if(pclItemList[PERSONITEM_RING1].siUnique == pclItemList[PERSONITEM_RING2].siUnique)
						bIsSameRing = true;
				}
			}
		}

		if(bIsSameRing == true)
			StepCount--;
	}

	TWO_STEP <= StepCount ? *_psiStep = StepCount : *_psiStep = 0;
	return TWO_STEP <= StepCount ? true : false;
}

SI16 CSetItemManager::FindSetItemType( cltCharCommon* _pclChar, SI16* _psiStep, SI32 _UseSetItem )
{
	*_psiStep = 0;

	if( USE_SETITEM_5 == _UseSetItem )
	{
		if( 0 >= _pclChar->m_siSetItemType4 ) 
			return 0;
	}	

	if( USE_SETITEM_4 == _UseSetItem )
	{
		if( 0 >= _pclChar->m_siSetItemType3 ) 
			return 0;
	}	

	// ����° ��Ʈ �������� ã�µ� �ι�°�� ã�� ��Ʈ �������� ���ٸ� ã�� �ʴ´�.
	if( USE_SETITEM_3 == _UseSetItem )
	{
		if( 0 >= _pclChar->m_siSetItemType2 ) 
			return 0;
	}	


	// �ι�° ��Ʈ �������� ã�µ� ù��°�� ã�� ��Ʈ �������� ���ٸ� ã�� �ʴ´�.
	if( USE_SETITEM_2 == _UseSetItem )
	{
		if( 0 >= _pclChar->m_siSetItemType ) 
			return 0;
	}


	for( SI16  i = 0; i < m_siMaxSetItemNumber; ++i )
	{
		if( USE_SETITEM_5 == _UseSetItem )
		{
			if( i == _pclChar->m_siSetItemType4 - 1 ) 
				continue;

			if( i == _pclChar->m_siSetItemType3 - 1 ) 
				continue;

			if( i == _pclChar->m_siSetItemType2 - 1 ) 
				continue;

			if( i == _pclChar->m_siSetItemType - 1 ) 
				continue;

			//	[��ȣ] ���� ���� ������ �����Ѵٸ� ���������� ��Ʈ�������� üũ���� �ʾƵ� �ȴ�.
			if(	_pclChar->m_siSetItemType == HALLOWEEN1_SETITEM || 
				_pclChar->m_siSetItemType == HALLOWEEN2_SETITEM ||
				_pclChar->m_siSetItemType == HALLOWEEN3_SETITEM ||
				_pclChar->m_siSetItemType == HALLOWEEN4_SETITEM ||
				_pclChar->m_siSetItemType2 == HALLOWEEN1_SETITEM || 
				_pclChar->m_siSetItemType2 == HALLOWEEN2_SETITEM ||
				_pclChar->m_siSetItemType2 == HALLOWEEN3_SETITEM ||
				_pclChar->m_siSetItemType2 == HALLOWEEN4_SETITEM ||
				_pclChar->m_siSetItemType3 == HALLOWEEN1_SETITEM || 
				_pclChar->m_siSetItemType3 == HALLOWEEN2_SETITEM ||
				_pclChar->m_siSetItemType3 == HALLOWEEN3_SETITEM ||
				_pclChar->m_siSetItemType3 == HALLOWEEN4_SETITEM ||
				_pclChar->m_siSetItemType4 == HALLOWEEN1_SETITEM || 
				_pclChar->m_siSetItemType4 == HALLOWEEN2_SETITEM ||
				_pclChar->m_siSetItemType4 == HALLOWEEN3_SETITEM ||
				_pclChar->m_siSetItemType4 == HALLOWEEN4_SETITEM)
			{
				if(i+1 == HALLOWEEN1_SETITEM || i+1 == HALLOWEEN2_SETITEM || i+1 == HALLOWEEN3_SETITEM || i+1 == HALLOWEEN4_SETITEM) 
					continue;
			}	

			//	[��ȣ] ���� ���� ������ �����Ѵٸ� ���������� ��Ʈ�������� üũ���� �ʾƵ� �ȴ�.
			if(	_pclChar->m_siSetItemType == GIRL_SULBIM_SETITEM || 
				_pclChar->m_siSetItemType == BOY_SULBIM_SETITEM  || 
				_pclChar->m_siSetItemType2 == GIRL_SULBIM_SETITEM || 
				_pclChar->m_siSetItemType2 == BOY_SULBIM_SETITEM  ||
				_pclChar->m_siSetItemType3 == GIRL_SULBIM_SETITEM || 
				_pclChar->m_siSetItemType3 == BOY_SULBIM_SETITEM  ||
				_pclChar->m_siSetItemType4 == GIRL_SULBIM_SETITEM || 
				_pclChar->m_siSetItemType4 == BOY_SULBIM_SETITEM)
			{
				if(i+1 == GIRL_SULBIM_SETITEM || i+1 == BOY_SULBIM_SETITEM) 
					continue;
			}	
		}

		if( USE_SETITEM_4 == _UseSetItem )
		{
			if( i == _pclChar->m_siSetItemType3 - 1 ) 
				continue;

			if( i == _pclChar->m_siSetItemType2 - 1 ) 
				continue;

			if( i == _pclChar->m_siSetItemType - 1 ) 
				continue;

			//	[��ȣ] ���� ���� ������ �����Ѵٸ� ���������� ��Ʈ�������� üũ���� �ʾƵ� �ȴ�.
			if(	_pclChar->m_siSetItemType == HALLOWEEN1_SETITEM || 
				_pclChar->m_siSetItemType == HALLOWEEN2_SETITEM ||
				_pclChar->m_siSetItemType == HALLOWEEN3_SETITEM ||
				_pclChar->m_siSetItemType == HALLOWEEN4_SETITEM ||
				_pclChar->m_siSetItemType2 == HALLOWEEN1_SETITEM || 
				_pclChar->m_siSetItemType2 == HALLOWEEN2_SETITEM ||
				_pclChar->m_siSetItemType2 == HALLOWEEN3_SETITEM ||
				_pclChar->m_siSetItemType2 == HALLOWEEN4_SETITEM ||
				_pclChar->m_siSetItemType3 == HALLOWEEN1_SETITEM || 
				_pclChar->m_siSetItemType3 == HALLOWEEN2_SETITEM ||
				_pclChar->m_siSetItemType3 == HALLOWEEN3_SETITEM ||
				_pclChar->m_siSetItemType3 == HALLOWEEN4_SETITEM)
			{
				if(i+1 == HALLOWEEN1_SETITEM || i+1 == HALLOWEEN2_SETITEM || i+1 == HALLOWEEN3_SETITEM || i+1 == HALLOWEEN4_SETITEM) 
					continue;
			}	

			//	[��ȣ] ���� ���� ������ �����Ѵٸ� ���������� ��Ʈ�������� üũ���� �ʾƵ� �ȴ�.
			if(	_pclChar->m_siSetItemType == GIRL_SULBIM_SETITEM || 
				_pclChar->m_siSetItemType == BOY_SULBIM_SETITEM  || 
				_pclChar->m_siSetItemType2 == GIRL_SULBIM_SETITEM || 
				_pclChar->m_siSetItemType2 == BOY_SULBIM_SETITEM  ||
				_pclChar->m_siSetItemType3 == GIRL_SULBIM_SETITEM || 
				_pclChar->m_siSetItemType3 == BOY_SULBIM_SETITEM)
			{
				if(i+1 == GIRL_SULBIM_SETITEM || i+1 == BOY_SULBIM_SETITEM) 
					continue;
			}	
		}

		if( USE_SETITEM_3 == _UseSetItem )
		{
			if( i == _pclChar->m_siSetItemType2 - 1 ) 
				continue;

			if( i == _pclChar->m_siSetItemType - 1 ) 
				continue;

			//	[��ȣ] ���� ���� ������ �����Ѵٸ� ���������� ��Ʈ�������� üũ���� �ʾƵ� �ȴ�.
			if(	_pclChar->m_siSetItemType == HALLOWEEN1_SETITEM || 
				_pclChar->m_siSetItemType == HALLOWEEN2_SETITEM ||
				_pclChar->m_siSetItemType == HALLOWEEN3_SETITEM ||
				_pclChar->m_siSetItemType == HALLOWEEN4_SETITEM ||
				_pclChar->m_siSetItemType2 == HALLOWEEN1_SETITEM || 
				_pclChar->m_siSetItemType2 == HALLOWEEN2_SETITEM ||
				_pclChar->m_siSetItemType2 == HALLOWEEN3_SETITEM ||
				_pclChar->m_siSetItemType2 == HALLOWEEN4_SETITEM	)
			{
				if(i+1 == HALLOWEEN1_SETITEM || i+1 == HALLOWEEN2_SETITEM || i+1 == HALLOWEEN3_SETITEM || i+1 == HALLOWEEN4_SETITEM) 
					continue;
			}	

			//	[��ȣ] ���� ���� ������ �����Ѵٸ� ���������� ��Ʈ�������� üũ���� �ʾƵ� �ȴ�.
			if(	_pclChar->m_siSetItemType == GIRL_SULBIM_SETITEM || 
				_pclChar->m_siSetItemType == BOY_SULBIM_SETITEM  || 
				_pclChar->m_siSetItemType2 == GIRL_SULBIM_SETITEM || 
				_pclChar->m_siSetItemType2 == BOY_SULBIM_SETITEM)
			{
				if(i+1 == GIRL_SULBIM_SETITEM || i+1 == BOY_SULBIM_SETITEM) 
					continue;
			}	
		}

		// �ι�° ��Ʈ �������� Ȯ���Ҷ��� û��° ��Ʈ �������� �����Ѵ�.
		if( USE_SETITEM_2 == _UseSetItem )
		{
			if( i == _pclChar->m_siSetItemType - 1 ) 
				continue;

			//	[��ȣ] ���� ���� ������ �����Ѵٸ� ���������� ��Ʈ�������� üũ���� �ʾƵ� �ȴ�.
			if(	_pclChar->m_siSetItemType == HALLOWEEN1_SETITEM || 
				_pclChar->m_siSetItemType == HALLOWEEN2_SETITEM ||
				_pclChar->m_siSetItemType == HALLOWEEN3_SETITEM ||
				_pclChar->m_siSetItemType == HALLOWEEN4_SETITEM)
			{
				if(i+1 == HALLOWEEN1_SETITEM || i+1 == HALLOWEEN2_SETITEM || i+1 == HALLOWEEN3_SETITEM || i+1 == HALLOWEEN4_SETITEM) 
					continue;
			}	

			//	[��ȣ] ���� ���� ������ �����Ѵٸ� ���������� ��Ʈ�������� üũ���� �ʾƵ� �ȴ�.
			if(	_pclChar->m_siSetItemType == GIRL_SULBIM_SETITEM || 
				_pclChar->m_siSetItemType == BOY_SULBIM_SETITEM )
			{
				if(i+1 == GIRL_SULBIM_SETITEM || i+1 == BOY_SULBIM_SETITEM) 
					continue;
			}	
		}

		if( true == (IsSetItemStep(i + 1) ? CompareSetItemUniqueStep( i, _pclChar, _psiStep, _UseSetItem) : CompareSetItemUnique( i, &_pclChar->pclCI->clCharItem.clItem[0]) ) )
		{
			return i + 1;
		}
	}

	return 0;
}

