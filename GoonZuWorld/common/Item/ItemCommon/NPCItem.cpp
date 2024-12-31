//---------------------------------
// 2003/8/19 ���°�
//---------------------------------

#include "NPCItem.h"

//--------------------------------
// Common
//--------------------------------
#include "Char\KindInfo\KindInfo.h"
#include "CommonLogic.h"

extern cltCommonLogic* pclClient;

bool AddNPCItemData(SI32* pclNPCSellList, SI32 siListSize, SI32 siItemUnique, SI32 siPrice)
{
	SI32 i = 0;
	SI32 siEmptyPos = -1;

	for( i = 0; i<siListSize; i++)
	{
		if(pclNPCSellList[i] == -1)
		{
			siEmptyPos = i;
			break;
		}
	}

	if(siEmptyPos < 0)	return false;
	if(siEmptyPos+1 >= siListSize ) return false;

	pclNPCSellList[siEmptyPos] = siItemUnique;
	siEmptyPos++;
	pclNPCSellList[siEmptyPos] = siPrice;

	return true;
}

cltNPCItemInfo::cltNPCItemInfo(cltItemManagerCommon* pclitemmanager)
{
	siCurNPCMerchantNumber = 0;

	SI32 i = 0;

	pclNPCItemInfo_KIND_WAITINGWOMAN		=	new SI32[MAX_NPC_SELLLIST];	
	pclNPCItemInfo_KIND_INVESTMENT			=	new SI32[MAX_NPC_SELLLIST];	
	pclNPCItemInfo_KIND_MAGICALRACCOON_NPC	=	new SI32[MAX_NPC_SELLLIST];
	pclNPCItemInfo_KIND_ANNIVERSARY			=	new SI32[MAX_NPC_SELLLIST];
	pclNPCItemInfo_KIND_SNACKBAR1			=	new SI32[MAX_NPC_SELLLIST];
	pclNPCItemInfo_KIND_SNACKBAR2			=	new SI32[MAX_NPC_SELLLIST];
	pclNPCItemInfo_KIND_SNACKBAR3			=	new SI32[MAX_NPC_SELLLIST];
	pclNPCItemInfo_KIND_SNACKBAR4			=	new SI32[MAX_NPC_SELLLIST];
	m_psiNPCItemInfo_KIND_CHOCOLATE			=	new SI32[MAX_NPC_SELLLIST];
	m_psiNPCItemInfo_KIND_GIFTRACCOON		=	new SI32[MAX_NPC_SELLLIST];

	for(i=0; i<MAX_NPC_SELLLIST; i++)		pclNPCItemInfo_KIND_WAITINGWOMAN[i] = -1;
	for(i=0; i<MAX_NPC_SELLLIST; i++)		pclNPCItemInfo_KIND_INVESTMENT[i] = -1;
	for(i=0; i<MAX_NPC_SELLLIST; i++)		pclNPCItemInfo_KIND_MAGICALRACCOON_NPC[i] = -1;
	for(i=0; i<MAX_NPC_SELLLIST; i++)		pclNPCItemInfo_KIND_ANNIVERSARY[i] = -1;
	for(i=0; i<MAX_NPC_SELLLIST; i++)		pclNPCItemInfo_KIND_SNACKBAR1[i] = -1;
	for(i=0; i<MAX_NPC_SELLLIST; i++)		pclNPCItemInfo_KIND_SNACKBAR2[i] = -1;
	for(i=0; i<MAX_NPC_SELLLIST; i++)		pclNPCItemInfo_KIND_SNACKBAR3[i] = -1;
	for(i=0; i<MAX_NPC_SELLLIST; i++)		pclNPCItemInfo_KIND_SNACKBAR4[i] = -1;
	for(i=0; i<MAX_NPC_SELLLIST; i++)		m_psiNPCItemInfo_KIND_CHOCOLATE[i] = -1;
	for(i=0; i<MAX_NPC_SELLLIST; i++)		m_psiNPCItemInfo_KIND_GIFTRACCOON[i] = -1;

	pclItemManager = pclitemmanager;
	if(pclitemmanager == NULL)
	{
		MsgBox(TEXT("fd9jf"), TEXT("ds9j1"));
	}

	NDataLoader	dataloader;
	BOOL bLoadFile = FALSE;

	if(pclClient->IsWhereServiceArea(ConstSwitch_TextEncryption))
	{
		bLoadFile = dataloader.LoadDataFromCryptFile(TEXT("Data/NPCSellList.txt"));
	}
	else
	{
		bLoadFile = dataloader.LoadDataFromFile(TEXT("Data/NPCSellList.txt"));
	}

	if(!bLoadFile)
	{
		MsgBox(TEXT("ERROR"), TEXT("Not Found NPCSellList.txt"));
	}

	TCHAR	szNPCKind[128] = TEXT("");
	SI32	siItemUnique   = 0;
	SI32	siPrice        = 0;

	// NPCSellList ����
	NDataTypeInfo pNPCSellList[] =
	{
		NDATA_MBSTRING,	szNPCKind,		128,
		NDATA_INT32,	&siItemUnique,	4,
		NDATA_INT32,	&siPrice,		4,
			0,0,0
	};

	dataloader.RegDataType(pNPCSellList);

	while(!dataloader.IsEndOfData())
	{
		if(dataloader.ReadData())
		{
			if(pclClient->GetUniqueFromHash(szNPCKind) == pclClient->GetUniqueFromHash(TEXT("KIND_WAITINGWOMAN")))
			{
				AddNPCItemData(pclNPCItemInfo_KIND_WAITINGWOMAN, MAX_NPC_SELLLIST, siItemUnique, siPrice);
			}
			else if(pclClient->GetUniqueFromHash(szNPCKind) == pclClient->GetUniqueFromHash(TEXT("KIND_INVESTMENT")))
			{
				AddNPCItemData(pclNPCItemInfo_KIND_INVESTMENT, MAX_NPC_SELLLIST, siItemUnique, siPrice);
			}
			else if(pclClient->GetUniqueFromHash(szNPCKind) == pclClient->GetUniqueFromHash(TEXT("KIND_MAGICALRACCOON_NPC")))
			{
				AddNPCItemData(pclNPCItemInfo_KIND_MAGICALRACCOON_NPC, MAX_NPC_SELLLIST, siItemUnique, siPrice);
			}
			else if(pclClient->GetUniqueFromHash(szNPCKind) == pclClient->GetUniqueFromHash(TEXT("KIND_ANNIVERSARY")))
			{
				AddNPCItemData(pclNPCItemInfo_KIND_ANNIVERSARY, MAX_NPC_SELLLIST, siItemUnique, siPrice);
			}
			else if(pclClient->GetUniqueFromHash(szNPCKind) == pclClient->GetUniqueFromHash(TEXT("KIND_SNACKBAR1")))
			{
				AddNPCItemData(pclNPCItemInfo_KIND_SNACKBAR1, MAX_NPC_SELLLIST, siItemUnique, siPrice);
			}
			else if(pclClient->GetUniqueFromHash(szNPCKind) == pclClient->GetUniqueFromHash(TEXT("KIND_SNACKBAR2")))
			{
				AddNPCItemData(pclNPCItemInfo_KIND_SNACKBAR2, MAX_NPC_SELLLIST, siItemUnique, siPrice);
			}
			else if(pclClient->GetUniqueFromHash(szNPCKind) == pclClient->GetUniqueFromHash(TEXT("KIND_SNACKBAR3")))
			{
				AddNPCItemData(pclNPCItemInfo_KIND_SNACKBAR3, MAX_NPC_SELLLIST, siItemUnique, siPrice);
			}
			else if(pclClient->GetUniqueFromHash(szNPCKind) == pclClient->GetUniqueFromHash(TEXT("KIND_SNACKBAR4")))
			{
				AddNPCItemData(pclNPCItemInfo_KIND_SNACKBAR4, MAX_NPC_SELLLIST, siItemUnique, siPrice);
			}
			else if(pclClient->GetUniqueFromHash(szNPCKind) == pclClient->GetUniqueFromHash(TEXT("KIND_CHOCOLATE")))
			{
				AddNPCItemData(m_psiNPCItemInfo_KIND_CHOCOLATE, MAX_NPC_SELLLIST, siItemUnique, siPrice);
			}
			else if(pclClient->GetUniqueFromHash(szNPCKind) == pclClient->GetUniqueFromHash(TEXT("KIND_GIFTRACCOON")))
			{
				AddNPCItemData(m_psiNPCItemInfo_KIND_GIFTRACCOON, MAX_NPC_SELLLIST, siItemUnique, siPrice);
			}
		}
	}

	Add(pclClient->GetUniqueFromHash(TEXT("KIND_WAITINGWOMAN")),		pclNPCItemInfo_KIND_WAITINGWOMAN);
	Add(pclClient->GetUniqueFromHash(TEXT("KIND_INVESTMENT")),			pclNPCItemInfo_KIND_INVESTMENT);
	Add(pclClient->GetUniqueFromHash(TEXT("KIND_MAGICALRACCOON_NPC")),	pclNPCItemInfo_KIND_MAGICALRACCOON_NPC);
	Add(pclClient->GetUniqueFromHash(TEXT("KIND_ANNIVERSARY")),			pclNPCItemInfo_KIND_ANNIVERSARY);
	Add(pclClient->GetUniqueFromHash(TEXT("KIND_SNACKBAR1")),			pclNPCItemInfo_KIND_SNACKBAR1);
	Add(pclClient->GetUniqueFromHash(TEXT("KIND_SNACKBAR2")),			pclNPCItemInfo_KIND_SNACKBAR2);
	Add(pclClient->GetUniqueFromHash(TEXT("KIND_SNACKBAR3")),			pclNPCItemInfo_KIND_SNACKBAR3);
	Add(pclClient->GetUniqueFromHash(TEXT("KIND_SNACKBAR4")),			pclNPCItemInfo_KIND_SNACKBAR4);
	Add(pclClient->GetUniqueFromHash(TEXT("KIND_CHOCOLATE")),			m_psiNPCItemInfo_KIND_CHOCOLATE);
	Add(pclClient->GetUniqueFromHash(TEXT("KIND_GIFTRACCOON")),			m_psiNPCItemInfo_KIND_GIFTRACCOON);
}

cltNPCItemInfo::~cltNPCItemInfo()
{
	if(pclNPCItemInfo_KIND_WAITINGWOMAN)		delete[]	pclNPCItemInfo_KIND_WAITINGWOMAN;
	if(pclNPCItemInfo_KIND_INVESTMENT)			delete[]	pclNPCItemInfo_KIND_INVESTMENT;
	if(pclNPCItemInfo_KIND_MAGICALRACCOON_NPC)	delete[]	pclNPCItemInfo_KIND_MAGICALRACCOON_NPC;
	if(pclNPCItemInfo_KIND_ANNIVERSARY)			delete[]	pclNPCItemInfo_KIND_ANNIVERSARY;
	if(pclNPCItemInfo_KIND_SNACKBAR1)			delete[]	pclNPCItemInfo_KIND_SNACKBAR1;
	if(pclNPCItemInfo_KIND_SNACKBAR2)			delete[]	pclNPCItemInfo_KIND_SNACKBAR2;
	if(pclNPCItemInfo_KIND_SNACKBAR3)			delete[]	pclNPCItemInfo_KIND_SNACKBAR3;
	if(pclNPCItemInfo_KIND_SNACKBAR4)			delete[]	pclNPCItemInfo_KIND_SNACKBAR4;
	if(m_psiNPCItemInfo_KIND_CHOCOLATE)			delete[]	m_psiNPCItemInfo_KIND_CHOCOLATE;
	if(m_psiNPCItemInfo_KIND_GIFTRACCOON)		delete[]	m_psiNPCItemInfo_KIND_GIFTRACCOON;
	
}

void cltNPCItemInfo::Create(SI32 npcpricerate)
{
	if(npcpricerate <= 0)return ;

	SetNPCItemInfo(npcpricerate);
}

//KHY - 20090527 - NPCrate ���� �߰��� �ٲ� ���, ������ ������ �ٽ� �����ϱ� ���ؼ�.��
void cltNPCItemInfo::SetNPCItemInfo(SI32 npcpricerate)
{

	for(SI32 i = 0;i < siCurNPCMerchantNumber;i++)
	{
		SI32 index = 0;
		while(clNPCMerchantInfo[i].psiNPCItemInfo[index*2] > 0)
		{
			// [����] ������ ������� �ִ´�
			SI32 siItemUnique	= clNPCMerchantInfo[i].psiNPCItemInfo[index*2];
			UI08 uiDateUseDay	= 0;

			// ���Ⱓ �޾ƿ���
			if ( 0 < siItemUnique )
			{
				SI32 siRef = pclItemManager->FindItemRefFromUnique( siItemUnique );
				if ( 0 < siRef )
				{
					uiDateUseDay = pclItemManager->pclItemInfo[ siRef ]->clItem.uiDateUseDay;
				}
			}

			SI16	brareswitch = 0;
			cltItem	clItem;

			if(pclItemManager->MakeRandItemUnique(siItemUnique, &clItem, 0, 0, &brareswitch, 0, 0, 0, 0, 0, uiDateUseDay) )
			{
				if(clItem.siUnique)
				{
					clNPCMerchantInfo[i].clItemInfo[index].clItem.Set(&clItem);
					GMONEY siTempMoney = clNPCMerchantInfo[i].psiNPCItemInfo[index*2+1]; // �����÷ο찡 ���� ���� 

					// [����] USA ������ �Ǹ� ������ �ٸ���
					if ( pclClient->IsWhereServiceArea(ConstServiceArea_USA) 
						&& (pclClient->GetUniqueFromHash(TEXT("KIND_ANNIVERSARY")) == clNPCMerchantInfo[i].siNPCKind)
					)
					{
						clNPCMerchantInfo[i].clItemInfo[index].siPrice	=  ((GMONEY)npcpricerate) * 35000;
					}
					else
					{
						clNPCMerchantInfo[i].clItemInfo[index].siPrice	=  siTempMoney * npcpricerate / 100;
					}
				}
			}
			
			index++;
		}
	}
	
}

void cltNPCItemInfo::Add(SI32 npckind, SI32* pnpcinfo)
{
	if(siCurNPCMerchantNumber >=  MAX_NPC_MERCHANT_NUMBER)
	{
		MsgBox(TEXT("fd38fd"), TEXT("fdf3dff"));
		return ;
	}

	clNPCMerchantInfo[siCurNPCMerchantNumber].siNPCKind						= npckind;
	clNPCMerchantInfo[siCurNPCMerchantNumber].psiNPCItemInfo				= pnpcinfo;
	siCurNPCMerchantNumber++;
}

//npckind�� �ٰŷ� ������ �����͸� ���Ѵ�.
cltNPCMerchantInfo* cltNPCItemInfo::GetMerchantInfo(SI32 npckind)
{
	SI32 ref = -1;
	for(SI32 i = 0;i < siCurNPCMerchantNumber;i++)
	{
		if(clNPCMerchantInfo[i].siNPCKind == npckind)
		{
			ref = i;
			break;
		}
	}
	if(ref < 0)return NULL;

	return &clNPCMerchantInfo[ref];

}

GMONEY cltNPCItemInfo::GetPrice(SI32 npckind, SI32 unique)
{

	// NPCkind�� �ٰŷ� ������ �����͸� ���Ѵ�. 
	cltNPCMerchantInfo* pinfo = GetMerchantInfo(npckind);
	if(pinfo == NULL)return 0;


	SI32 index = 0;
	
	while(pinfo->psiNPCItemInfo[index*2] > 0)
	{
		if(pinfo->psiNPCItemInfo[index*2] == unique)
		{
			return pinfo->psiNPCItemInfo[index*2 + 1];
		}

		index++;
	}

	return 0;

}

GMONEY cltNPCItemInfo::GetRealPrice(SI32 npckind, SI32 unique)
{
	// NPCkind�� �ٰŷ� ������ �����͸� ���Ѵ�. 
	cltNPCMerchantInfo* pinfo = GetMerchantInfo(npckind);
	if(pinfo == NULL)return 0;

	SI32 index = 0;

	while(pinfo->psiNPCItemInfo[index*2] > 0)
	{
		if(pinfo->psiNPCItemInfo[index*2] == unique)
		{
			return pinfo->clItemInfo[index].siPrice;
		}

		index++;
	}

	return 0;

}
