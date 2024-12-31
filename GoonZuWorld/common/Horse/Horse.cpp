#include <CommonLogic.h>
#include "..\Server\Server.h"

#include "../Util/Util.h"

//----------------------------------------
// Common
//----------------------------------------
#include "Item\ItemCommon\cltItem.h"

#include "Horse.h"

extern cltCommonLogic* pclClient;

bool cltPersonHorseInfo::Add(cltHorse* pclhorse, SI32* pindex)
{
	if(pclhorse == NULL)			return false;

	SI32 index = FindEmptyHorseIndex();
	if(index < 0)return false;

	//clHorse.Set(pclhorse);
	clHorse[index].Set(pclhorse);
	*pindex	= index;
	return true;
}


// ���� �ܿ� �䱸������ ���Ѵ�. 
bool cltPersonHorseInfo::GetNeed(cltHorse* pclhorse, SI32* pneeditemunique, SI32* pneeditemnum)
{
	if(pclhorse == NULL)						return false;
	// �䱸������ ������, 
	if(pclhorse->siNeed != HORSE_NEED_FEED)		return false;
	// ����� �����Ǿ� �ִٸ�, 
	if(pclhorse->siPara2 <= pclhorse->siSupply)	return false;

	*pneeditemunique	= pclhorse->siPara1;
	*pneeditemnum		= pclhorse->siPara2 - pclhorse->siSupply;

	return true;
}


// index�� ���� Ż �� �ִ°�?
bool cltPersonHorseInfo::CanRide(SI32 index, cltDate* pcldate)
{
	if(index < 0)							return false;
	if(index >= MAX_HORSE_PER_PERSON)		return false;

	//if(clHorse.siHorseUnique <= 0)return false;
	if(clHorse[index].siHorseUnique <= 0)	return false;

	return true;
}

// ���� ���� �� �ִ� �ε����� ã�´�. 
SI32 cltPersonHorseInfo::FindEmptyHorseIndex()
{
	
	//if(clHorse.siHorseUnique == 0)return 0;

	//KHY - 1001 - ��µ��� 5���� ���� ����.
	if(pclClient->IsCountrySwitch(Switch_Can5Horse))
	{
		for(SI32 i = 0;i < MAX_HORSE_PER_PERSON;i++)
		{
			if(clHorse[i].siHorseUnique == 0)return i;
		}
	}
	else
	{
		if(clHorse[0].siHorseUnique == 0) //��Ÿ������ ���� �Ѹ�����.
			return 0;
		
	}
	return -1;
}



//-------------------------------------------------------
// �� Ÿ�� 
//-------------------------------------------------------
cltHorseTypeInfo::cltHorseTypeInfo(SI32 unique, TCHAR* pcode, TCHAR* pspecies, SI32 kind, SI32 ServiceArea, bool NotTrade)
{
	siUnique = unique;
	StringCchCopy(szCode, 64, pcode);
	StringCchCopy(szSpecies, 64, pspecies);
	siKind	= kind;

    siServiceArea	= ServiceArea;
	bNotTrade		= NotTrade;
}

cltHorseTypeInfo::~cltHorseTypeInfo()
{
}

//------------------------------------------------------
// Horse������. 
//------------------------------------------------------
cltHorseManager::cltHorseManager()
{
	SI32 i;

	for(i = 0;i < MAX_HORSE_TYPE_INFO;i++)
	{
		pclHorseTypeInfo[i] = NULL;
	}

	TCHAR* pText = GetTxtFromMgr(667);
	AddHorseType( HORSEUNIQUE_BROWN , TEXT("HOR01"), pText,	pclClient->GetUniqueFromHash(TEXT("KIND_HOR01YOUNG")),
				SERVICEAREA_ATB_KOREA | SERVICEAREA_ATB_CHINA | SERVICEAREA_ATB_JAPAN | SERVICEAREA_ATB_ENGLISH | SERVICEAREA_ATB_TAIWAN | SERVICEAREA_ATB_USA | SERVICEAREA_ATB_NHNCHINA | SERVICEAREA_ATB_EUROPE,
				false );		// ������. 

	pText = GetTxtFromMgr(2806);
	AddHorseType( HORSEUNIQUE_BLACK , TEXT("HOR02"), pText,	pclClient->GetUniqueFromHash(TEXT("KIND_HOR02YOUNG")),
				SERVICEAREA_ATB_KOREA | SERVICEAREA_ATB_CHINA | SERVICEAREA_ATB_JAPAN | SERVICEAREA_ATB_ENGLISH | SERVICEAREA_ATB_TAIWAN | SERVICEAREA_ATB_USA | SERVICEAREA_ATB_NHNCHINA | SERVICEAREA_ATB_EUROPE,
				false  );		// �渶. 	

	pText = GetTxtFromMgr(2805);
	AddHorseType( HORSEUNIQUE_WHITE , TEXT("HOR03"), pText,	pclClient->GetUniqueFromHash(TEXT("KIND_HOR03YOUNG")),
				SERVICEAREA_ATB_KOREA | SERVICEAREA_ATB_CHINA | SERVICEAREA_ATB_JAPAN | SERVICEAREA_ATB_ENGLISH | SERVICEAREA_ATB_TAIWAN | SERVICEAREA_ATB_USA | SERVICEAREA_ATB_NHNCHINA | SERVICEAREA_ATB_EUROPE,
				false  );		// �鸶. 
	
	pText = GetTxtFromMgr(2753);
	AddHorseType( HORSEUNIQUE_RED , TEXT("HOR04"), pText,	pclClient->GetUniqueFromHash(TEXT("KIND_HOR04YOUNG")),
				SERVICEAREA_ATB_KOREA | SERVICEAREA_ATB_CHINA | SERVICEAREA_ATB_JAPAN | SERVICEAREA_ATB_ENGLISH | SERVICEAREA_ATB_TAIWAN | SERVICEAREA_ATB_USA | SERVICEAREA_ATB_NHNCHINA | SERVICEAREA_ATB_EUROPE,
				false  );		// ���丶  
	
	pText = GetTxtFromMgr(3370);
	AddHorseType( HORSEUNIQUE_RUDOLF , TEXT("HOR05"), pText,	pclClient->GetUniqueFromHash(TEXT("KIND_HOR05YOUNG")),
				SERVICEAREA_ATB_KOREA | SERVICEAREA_ATB_CHINA | SERVICEAREA_ATB_JAPAN | SERVICEAREA_ATB_ENGLISH | SERVICEAREA_ATB_TAIWAN | SERVICEAREA_ATB_USA | SERVICEAREA_ATB_NHNCHINA | SERVICEAREA_ATB_EUROPE,
				false  );		//  �絹��. 

	//pText = GetTxtFromMgr(5394);
	//AddHorseType( HORSEUNIQUE_TIGER , TEXT("HOR06"), pText,	pclClient->GetUniqueFromHash(TEXT("KIND_HOR06YOUNG")));		// õ����

	pText = GetTxtFromMgr(2791);
	AddHorseType( HORSEUNIQUE_THOUSAND , TEXT("HOR07"), pText,	pclClient->GetUniqueFromHash(TEXT("KIND_HOR07YOUNG")),
				SERVICEAREA_ATB_KOREA | SERVICEAREA_ATB_CHINA | SERVICEAREA_ATB_JAPAN | SERVICEAREA_ATB_ENGLISH | SERVICEAREA_ATB_TAIWAN | SERVICEAREA_ATB_USA | SERVICEAREA_ATB_NHNCHINA | SERVICEAREA_ATB_EUROPE,
				false  );		// õ����

	pText = GetTxtFromMgr(5174);
	AddHorseType( HORSEUNIQUE_STEEL , TEXT("HOR08"), pText,	pclClient->GetUniqueFromHash(TEXT("KIND_HOR08YOUNG")),
				SERVICEAREA_ATB_KOREA | SERVICEAREA_ATB_CHINA | SERVICEAREA_ATB_JAPAN | SERVICEAREA_ATB_ENGLISH | SERVICEAREA_ATB_TAIWAN | SERVICEAREA_ATB_USA | SERVICEAREA_ATB_NHNCHINA | SERVICEAREA_ATB_EUROPE,
				false  );

	pText = GetTxtFromMgr(5622);
	AddHorseType( HORSEUNIQUE_WOLF , TEXT("HOR09"), pText,	pclClient->GetUniqueFromHash(TEXT("KIND_HOR09YOUNG")),
				SERVICEAREA_ATB_KOREA | SERVICEAREA_ATB_CHINA | SERVICEAREA_ATB_JAPAN | SERVICEAREA_ATB_ENGLISH | SERVICEAREA_ATB_TAIWAN | SERVICEAREA_ATB_USA | SERVICEAREA_ATB_NHNCHINA | SERVICEAREA_ATB_EUROPE,
				true  );

	pText = GetTxtFromMgr(2769);
	AddHorseType( HORSEUNIQUE_ZEBRA , TEXT("HOR10"), pText,	pclClient->GetUniqueFromHash(TEXT("KIND_HOR10YOUNG")),
				SERVICEAREA_ATB_KOREA | SERVICEAREA_ATB_CHINA | SERVICEAREA_ATB_JAPAN | SERVICEAREA_ATB_ENGLISH | SERVICEAREA_ATB_TAIWAN | SERVICEAREA_ATB_USA | SERVICEAREA_ATB_NHNCHINA | SERVICEAREA_ATB_EUROPE,
				false  );		// ��踶. 

	pText = GetTxtFromMgr(6418);
	AddHorseType( HORSEUNIQUE_BEAST , TEXT("HOR11"), pText,	pclClient->GetUniqueFromHash(TEXT("KIND_HOR11YOUNG")),
				SERVICEAREA_ATB_KOREA | SERVICEAREA_ATB_CHINA | SERVICEAREA_ATB_JAPAN | SERVICEAREA_ATB_ENGLISH | SERVICEAREA_ATB_TAIWAN | SERVICEAREA_ATB_USA | SERVICEAREA_ATB_NHNCHINA | SERVICEAREA_ATB_EUROPE,
				false  );		// ����ȣ  

	//KHY - 0622 - ����S �ʺ��ڿ�  ������ �߰�.
	pText = GetTxtFromMgr(7505);
	AddHorseType( HORSEUNIQUE_FOAL , TEXT("HOR01"), pText,	pclClient->GetUniqueFromHash(TEXT("KIND_HOR01YOUNG")),
				SERVICEAREA_ATB_KOREA | SERVICEAREA_ATB_CHINA | SERVICEAREA_ATB_JAPAN | SERVICEAREA_ATB_ENGLISH | SERVICEAREA_ATB_TAIWAN | SERVICEAREA_ATB_USA | SERVICEAREA_ATB_NHNCHINA | SERVICEAREA_ATB_EUROPE,
				true  );		// ����

	//KHY - 0911 - ȣ���� �߰�.
	pText = GetTxtFromMgr(5394);
	AddHorseType( HORSEUNIQUE_TIGER , TEXT("HOR06"), pText,	pclClient->GetUniqueFromHash(TEXT("KIND_HOR06YOUNG")),
				SERVICEAREA_ATB_CHINA | SERVICEAREA_ATB_JAPAN | SERVICEAREA_ATB_ENGLISH | SERVICEAREA_ATB_TAIWAN | SERVICEAREA_ATB_USA | SERVICEAREA_ATB_NHNCHINA | SERVICEAREA_ATB_EUROPE,
				true  );		// ȣ����

	//PCK - 08/02/18 - ��Ÿ �߰�.
	pText = GetTxtFromMgr(7936);
	AddHorseType( HORSEUNIQUE_CAMEL, TEXT("HOR12"), pText, pclClient->GetUniqueFromHash(TEXT("KIND_HOR12YOUNG")),
				SERVICEAREA_ATB_CHINA | SERVICEAREA_ATB_JAPAN | SERVICEAREA_ATB_ENGLISH | SERVICEAREA_ATB_TAIWAN | SERVICEAREA_ATB_NHNCHINA | SERVICEAREA_ATB_EUROPE,
				true  );		// ��Ÿ

	// PCK - 08/04/01 - ����S �� �̺�Ʈ ȣ���� �߰�
	pText = GetTxtFromMgr(5394);
	AddHorseType( HORSEUNIQUE_TIGER2 , TEXT("HOR06"), pText,	pclClient->GetUniqueFromHash(TEXT("KIND_HOR06YOUNG")),
				SERVICEAREA_ATB_CHINA | SERVICEAREA_ATB_JAPAN | SERVICEAREA_ATB_ENGLISH | SERVICEAREA_ATB_TAIWAN | SERVICEAREA_ATB_USA | SERVICEAREA_ATB_NHNCHINA | SERVICEAREA_ATB_EUROPE,
				true  );		// ȣ����
	
	// PCK - 08/06/12 - �ڳ��� �߰�
	pText = GetTxtFromMgr(8460);
	AddHorseType( HORSEUNIQUE_ELEPHANT , TEXT("HOR13"), pText,	pclClient->GetUniqueFromHash(TEXT("KIND_HOR13YOUNG")),
		SERVICEAREA_ATB_KOREA | SERVICEAREA_ATB_CHINA | SERVICEAREA_ATB_JAPAN | SERVICEAREA_ATB_ENGLISH | SERVICEAREA_ATB_TAIWAN | SERVICEAREA_ATB_USA | SERVICEAREA_ATB_NHNCHINA | SERVICEAREA_ATB_EUROPE,
		true  );		// �ڳ���

	// PCK - 08/08/14 - ��ȣ �߰�
	pText = GetTxtFromMgr(8752);
	AddHorseType( HORSEUNIQUE_WHITETIGER , TEXT("HOR14"), pText,pclClient->GetUniqueFromHash(TEXT("KIND_HOR14YOUNG")),
		SERVICEAREA_ATB_KOREA | SERVICEAREA_ATB_CHINA | SERVICEAREA_ATB_JAPAN | SERVICEAREA_ATB_ENGLISH | SERVICEAREA_ATB_TAIWAN | SERVICEAREA_ATB_USA | SERVICEAREA_ATB_NHNCHINA | SERVICEAREA_ATB_EUROPE,
		true  );		// ��ȣ

	// PCK - 08/09/02 - ������� �߰�
	pText = GetTxtFromMgr(8795);
	AddHorseType( HORSEUNIQUE_MOTORCYCLE , TEXT("HOR15"), pText,pclClient->GetUniqueFromHash(TEXT("KIND_HOR15YOUNG")),
		SERVICEAREA_ATB_KOREA | SERVICEAREA_ATB_CHINA | SERVICEAREA_ATB_JAPAN | SERVICEAREA_ATB_ENGLISH | SERVICEAREA_ATB_TAIWAN | SERVICEAREA_ATB_USA | SERVICEAREA_ATB_NHNCHINA | SERVICEAREA_ATB_EUROPE,
		true  );		// �������

	// PCK - 08/12/10 - ����ġ �߰� 
	pText = GetTxtFromMgr(2788);
	AddHorseType( HORSEUNIQUE_FIREHATCH , TEXT("HOR16"), pText,pclClient->GetUniqueFromHash(TEXT("KIND_HOR16YOUNG")),
		SERVICEAREA_ATB_KOREA | SERVICEAREA_ATB_CHINA | SERVICEAREA_ATB_JAPAN | SERVICEAREA_ATB_ENGLISH | SERVICEAREA_ATB_TAIWAN | SERVICEAREA_ATB_USA | SERVICEAREA_ATB_NHNCHINA | SERVICEAREA_ATB_EUROPE,
		true  );		// ����ġ

	// �ռ��� - ä��� �鸶 2009-03-17
	pText = GetTxtFromMgr(9897);
	AddHorseType( HORSEUNIQUE_WHITE_TEST , TEXT("HOR03"), pText,pclClient->GetUniqueFromHash(TEXT("KIND_HOR03YOUNG")),
		SERVICEAREA_ATB_KOREA | SERVICEAREA_ATB_CHINA | SERVICEAREA_ATB_JAPAN | SERVICEAREA_ATB_ENGLISH | SERVICEAREA_ATB_TAIWAN | SERVICEAREA_ATB_USA | SERVICEAREA_ATB_NHNCHINA | SERVICEAREA_ATB_EUROPE,
		true  );

	// PCK - 09/07/30 -  ������Ʈ �߰�
	pText = GetTxtFromMgr(30304);
	AddHorseType( HORSEUNIQUE_BAPHOMET , TEXT("HOR17"), pText,pclClient->GetUniqueFromHash(TEXT("KIND_HOR17YOUNG")),
		SERVICEAREA_ATB_KOREA | SERVICEAREA_ATB_CHINA | SERVICEAREA_ATB_JAPAN | SERVICEAREA_ATB_ENGLISH | SERVICEAREA_ATB_TAIWAN | SERVICEAREA_ATB_USA | SERVICEAREA_ATB_NHNCHINA | SERVICEAREA_ATB_EUROPE,
		true  );		// ������Ʈ

	// ���� - 09/08/30 -  ȸ�� ���� �߰�
	pText = GetTxtFromMgr(40047);
	AddHorseType( HORSEUNIQUE_GRAYWOLF , TEXT("HOR09"), pText,pclClient->GetUniqueFromHash(TEXT("KIND_HOR09YOUNG")),
		SERVICEAREA_ATB_KOREA | SERVICEAREA_ATB_CHINA | SERVICEAREA_ATB_JAPAN | SERVICEAREA_ATB_ENGLISH | SERVICEAREA_ATB_TAIWAN | SERVICEAREA_ATB_USA | SERVICEAREA_ATB_NHNCHINA | SERVICEAREA_ATB_EUROPE,
		true  );		// ȸ�� ����

	// ���� - 09/12/31 -  ����� �߰�
	pText = GetTxtFromMgr(14035);
	AddHorseType( HORSEUNIQUE_SASURI , TEXT("HOR18"), pText,pclClient->GetUniqueFromHash(TEXT("KIND_HOR18YOUNG")),
		SERVICEAREA_ATB_KOREA | SERVICEAREA_ATB_CHINA | SERVICEAREA_ATB_JAPAN | SERVICEAREA_ATB_ENGLISH | SERVICEAREA_ATB_TAIWAN | SERVICEAREA_ATB_USA | SERVICEAREA_ATB_NHNCHINA | SERVICEAREA_ATB_EUROPE,
		true  );		// �����

	//pText = GetTxtFromMgr(2769);
	//AddHorseType(5, TEXT("HOR05"), pText,	pclClient->GetUniqueFromHash(TEXT("KIND_HOR05YOUNG")));		// ��踶  
	//pText = GetTxtFromMgr(2781);
	//AddHorseType(6, TEXT("HOR06"), pText,	pclClient->GetUniqueFromHash(TEXT("KIND_HOR06YOUNG")));		// �絹��
	//pText = GetTxtFromMgr(5394);
	//AddHorseType(9, TEXT("HOR09"), pText,	pclClient->GetUniqueFromHash(TEXT("KIND_BEAST01YOUNG")));		// ȣ����

}

cltHorseManager::~cltHorseManager()
{
	SI32 i;

	for(i = 0;i < MAX_HORSE_TYPE_INFO;i++)
	{
		if(pclHorseTypeInfo[i])
		{
			delete pclHorseTypeInfo[i];
			pclHorseTypeInfo[i] = NULL;
		}
	}

}

// ���� Ÿ���� �߰��Ѵ�. 
bool cltHorseManager::AddHorseType(SI32 unique, TCHAR* pcode, TCHAR* pspecies, SI32 kind, SI32 ServiceArea, bool NotTrade)
{
	if(pclHorseTypeInfo[unique])
	{
		MsgBox(TEXT("fd9jfdd"), TEXT("f3fdf:%d"), unique);
		return false;
	}

	pclHorseTypeInfo[unique] = new cltHorseTypeInfo(unique, pcode, pspecies, kind, ServiceArea, NotTrade);

	return true;
}

// ���� ����ũ�� �ٰŷ� ���� �̸��� ���Ѵ�. 
TCHAR* cltHorseManager::GetHorseName(SI32 horseunique)
{
	if(horseunique <= 0)						return NULL;
	if(horseunique >= MAX_HORSE_TYPE_INFO)		return NULL;
	if(pclHorseTypeInfo[horseunique] == NULL)	return NULL;

	return pclHorseTypeInfo[horseunique]->szSpecies;

}

// ���� ���� ������ �ؽ�Ʈ�� ��� �����Ѵ�. 
bool cltHorseManager::GetText(cltHorse* pclhorse, TCHAR* ptext, SI16 txtSize)
{
	if(pclhorse == NULL)return false;
	SI32 unique = pclhorse->siHorseUnique;
	if(unique <= 0)return false;

	TCHAR buffer[256] = TEXT("") ;
	TCHAR buffer2[512] = TEXT("") ;
	if(pclhorse->siSex == ANIMAL_MALE)
	{
		TCHAR* pText = GetTxtFromMgr(596);
		StringCchCopy(buffer, 256, pText);
	}
	else
	{
		TCHAR* pText = GetTxtFromMgr(597);
		StringCchCopy(buffer, 256, pText);
	}

	cltClient* pclclient = (cltClient*)pclClient;
	SI32 datevary = pclclient->clClientDate.GetDateVary();

	SI32 addstatus = 0 ;
	if ( GetAddStatusLimitDateVary(pclhorse) > 0 && pclhorse->siStatusTicketNum > 0 &&
		pclclient->clClientDate.GetDateVary() < GetAddStatusLimitDateVary(pclhorse) )
	{
		addstatus += MAX_HORSE_ADDSTATUS ;
		GetAddStatusLimitDateText(pclhorse,buffer2,512);
	}

	if(pclclient->pclHorseManager->GetLife(pclhorse, datevary) == MAX_UNLIMITEDHORSE_LIFE)
	{
		TCHAR* pText = GetTxtFromMgr(7020);

		StringCchPrintf(ptext, txtSize, pText,
			pclhorse->szName, buffer, pclHorseTypeInfo[unique]->szSpecies,
			pclhorse->GetAge(datevary), 
			//pclclient->pclHorseManager->GetLife(pclhorse, datevary), 
			pclhorse->siMoveSpeed/100.0f,
			pclhorse->siStr/100.0f + addstatus,
			pclhorse->siDex/100.0f + addstatus,
			pclhorse->siMag/100.0f + addstatus,
			pclhorse->siStatusBonus,
			buffer2);
	}
	//KHY - 1111 - ������� �߰�. - �������̰ŷ��� ����(�⸧)�� �ش������ ����.
	else if(pclhorse->siHorseUnique == HORSEUNIQUE_MOTORCYCLE )
	{		
		TCHAR* pText = GetTxtFromMgr(9740);

		StringCchPrintf(ptext, txtSize, pText,
			pclhorse->szName, buffer, pclHorseTypeInfo[unique]->szSpecies,
			pclhorse->GetAge(datevary), 
			pclhorse->siMoveSpeed/100.0f,
			pclhorse->siStr/100.0f + addstatus,
			pclhorse->siDex/100.0f + addstatus,
			pclhorse->siMag/100.0f + addstatus,
			pclhorse->siStatusBonus,
			buffer2);
	}
	else
	{
		TCHAR* pText = GetTxtFromMgr(2897);

		StringCchPrintf(ptext, txtSize, pText,
			pclhorse->szName, buffer, pclHorseTypeInfo[unique]->szSpecies,
			pclhorse->GetAge(datevary), 
			pclclient->pclHorseManager->GetLife(pclhorse, datevary), 
			pclhorse->siMoveSpeed/100.0f,
			pclhorse->siStr/100.0f + addstatus,
			pclhorse->siDex/100.0f + addstatus,
			pclhorse->siMag/100.0f + addstatus,
			pclhorse->siStatusBonus,
			buffer2);
	}

	return true;
}

SI32 cltHorseManager::GetHorseUniqueFromString( TCHAR *szSpecies )
{
	for( int i = 0; i < MAX_HORSE_TYPE_INFO; i++) {

		if( pclHorseTypeInfo[ i ] ) {

			if( _tcscmp( pclHorseTypeInfo[ i ]->szSpecies, szSpecies ) == 0 ) {

				return i;
			}

		}
	}

	return 0;
}

SI32 cltHorseManager::GetFullStr(SI32 unique)
{
	SI32 data;
	switch(unique)
	{
	case HORSEUNIQUE_BROWN:		// ������	
		data = MAX_BROWN_STR;
		break;
	case HORSEUNIQUE_BEAST:
		data = MAX_BEAST_STR;
		break;
	case HORSEUNIQUE_RUDOLF:
		data = MAX_RUDOLF_STR;
		break;
	case HORSEUNIQUE_STEEL:
		data = MAX_STEELHORSE_STR;
		break;
	case HORSEUNIQUE_WOLF:
		data = MAX_WOLF_STR;
		break;	
	//KHY - 0622 - ����S �ʺ��ڿ�  ������ �߰�.
	case HORSEUNIQUE_FOAL:
		data = MAX_FOAL_STR;
		break;
	//KHY - 0911 - ȣ���� �߰�.	
	case HORSEUNIQUE_TIGER:
		data = MAX_TIGER_STR;
		break;
	// PCK - 08/02/18 - ��Ÿ �߰�
	case HORSEUNIQUE_CAMEL:
		data = MAX_CAMEL_STR;
		break;
	// PCK - 08/04/01 - ����S�� �̺�Ʈ ȣ���� �߰�
	case HORSEUNIQUE_TIGER2:
		data = MAX_TIGER2_STR;
		break;
	// PCK - 08/06/12 - �ڳ��� �߰�
	case HORSEUNIQUE_ELEPHANT:
		data = MAX_ELEPHANT_STR;
		break;
	// PCK - 08/08/14 - ��ȣ �߰�
	case HORSEUNIQUE_WHITETIGER:
		data = MAX_WHITETIGER_STR;
		break;
	// PCK - 08/09/02 - ������� �߰�
	case HORSEUNIQUE_MOTORCYCLE:
		data = MAX_MOTORCYCLE_STR;
		break;
	// PCK - 08/12/10 - ����ġ �߰�
	case HORSEUNIQUE_FIREHATCH:
		data = MAX_FIREHATCH_STR;
		break;
	// PCK - 09/07/30 - ������Ʈ �߰�
	case HORSEUNIQUE_BAPHOMET:
		data = MAX_BAPHOMET_STR;
		break;
	// ���� - 09/08/30 - ȸ������ �߰�
	case HORSEUNIQUE_GRAYWOLF:
		data = MAX_GRAYWOLF_STR;
		break;
	// ���� - 09/12/31 - ����� �߰�
	case HORSEUNIQUE_SASURI:
		data = MAX_SASURI_STR;
		break;
	default:
		data = MAX_HORSE_STR;
		break;
	}

	return data;
}

SI32 cltHorseManager::GetFullDex(SI32 unique)
{
	SI32 data;
	switch(unique)
	{
	case HORSEUNIQUE_BROWN:		// ������	
		data = MAX_BROWN_DEX;
		break;
	case HORSEUNIQUE_RUDOLF:
		data = MAX_RUDOLF_DEX;
		break;
	case HORSEUNIQUE_BEAST:
		data = MAX_BEAST_DEX;
		break;
	case HORSEUNIQUE_RED:
		data = MAX_REDHORSE_DEX;
		break;
	case HORSEUNIQUE_WOLF:		// ����
		data = MAX_WOLF_DEX;
		break;
	//KHY - 0622 - ����S �ʺ��ڿ�  ������ �߰�.
	case HORSEUNIQUE_FOAL:
		data = MAX_FOAL_DEX;
		break;
	//KHY - 0911 - ȣ���� �߰�.	
	case HORSEUNIQUE_TIGER:
		data = MAX_TIGER_DEX;
		break;
	// PCK - 08/02/18 - ��Ÿ �߰�
	case HORSEUNIQUE_CAMEL:
		data = MAX_CAMEL_DEX;
		break;
	// PCK - 08/04/01 - ����S�� �̺�Ʈ ȣ���� �߰�
	case HORSEUNIQUE_TIGER2:
		data = MAX_TIGER2_DEX;
		break;
	// PCK - 08/06/12 - �ڳ��� �߰�
	case HORSEUNIQUE_ELEPHANT:
		data = MAX_ELEPHANT_DEX;
		break;
	// PCK - 08/08/14 - ��ȣ �߰�
	case HORSEUNIQUE_WHITETIGER:
		data = MAX_WHITETIGER_DEX;
		break;
	// PCK - 08/09/02 - ������� �߰�
	case HORSEUNIQUE_MOTORCYCLE:
		data = MAX_MOTORCYCLE_DEX;
		break;
	// PCK - 08/12/10 - ����ġ �߰�
	case HORSEUNIQUE_FIREHATCH:
		data = MAX_FIREHATCH_DEX;
		break;
	// PCK - 09/07/30 - ������Ʈ �߰�
	case HORSEUNIQUE_BAPHOMET:
		data = MAX_BAPHOMET_DEX;
		break;
	// ���� - 09/08/30 - ȸ������ �߰�
	case HORSEUNIQUE_GRAYWOLF:
		data = MAX_GRAYWOLF_DEX;
		break;
	// ���� - 09/12/31 - ����� �߰�
	case HORSEUNIQUE_SASURI:
		data = MAX_SASURI_DEX;
		break;
	default:
		data = MAX_HORSE_DEX;
		break;
	}

	return data;
}

SI32 cltHorseManager::GetFullMag(SI32 unique)
{
	SI32 data;
	switch(unique)
	{
	case HORSEUNIQUE_BROWN:		// ������	
		data = MAX_BROWN_MAG;
		break;
	case HORSEUNIQUE_RUDOLF:	// �絹��
		data = MAX_RUDOLF_MAG;
		break;
	case HORSEUNIQUE_BEAST:		// ����ȣ
		data = MAX_BEAST_MAG;
		break;
	case HORSEUNIQUE_WOLF:		// ����
		data = MAX_WOLF_MAG;
		break;
	//KHY - 0622 - ����S �ʺ��ڿ�  ������ �߰�.
	case HORSEUNIQUE_FOAL:
		data = MAX_FOAL_MAG;
		break;	
	//KHY - 0911 - ȣ���� �߰�.
	case HORSEUNIQUE_TIGER:
		data = MAX_TIGER_MAG;
		break;
	// PCK - 08/02/18 - ��Ÿ �߰�
	case HORSEUNIQUE_CAMEL:
		data = MAX_CAMEL_MAG;
		break;
	// PCK - 08/04/01 - ����S�� �̺�Ʈ ȣ���� �߰�
	case HORSEUNIQUE_TIGER2:
		data = MAX_TIGER2_MAG;
		break;
	// PCK - 08/06/12 - �ڳ��� �߰�
	case HORSEUNIQUE_ELEPHANT:
		data = MAX_ELEPHANT_MAG;
		break;
	// PCK - 08/08/14 - ��ȣ �߰�
	case HORSEUNIQUE_WHITETIGER:
		data = MAX_WHITETIGER_MAG;
		break;
	// PCK - 08/09/02 - ������� �߰�
	case HORSEUNIQUE_MOTORCYCLE:
		data = MAX_MOTORCYCLE_MAG;
		break;
	// PCK - 08/12/10 - ����ġ �߰�
	case HORSEUNIQUE_FIREHATCH:
		data = MAX_FIREHATCH_MAG;
		break;
	// PCK - 09/07/30 - ������Ʈ �߰�
	case HORSEUNIQUE_BAPHOMET:
		data = MAX_BAPHOMET_MAG;
		break;
	// ���� - 09/08/30 - ȸ������ �߰�
	case HORSEUNIQUE_GRAYWOLF:
		data = MAX_GRAYWOLF_MAG;
		break;
		// ���� - 09/12/31 - ����� �߰�
	case HORSEUNIQUE_SASURI:
		data = MAX_SASURI_MAG;
		break;
	default:
		data = MAX_HORSE_MAG;
		break;
	}

	return data;
}

SI32 cltHorseManager::GetFullSpeed(SI32 unique)
{
	SI32 data;
	switch(unique)
	{
	case HORSEUNIQUE_BROWN:		// ������	
		data = MAX_BROWN_SPEED;
		break;
	case HORSEUNIQUE_BEAST:
		data = MAX_BEAST_SPEED;
		break;
	case HORSEUNIQUE_WOLF:
	        data = MAX_WOLF_SPEED;
		break;
	//KHY - 0622 - ����S �ʺ��ڿ�  ������ �߰�.
	case HORSEUNIQUE_FOAL:
		data = MAX_FOAL_SPEED;
		break;
	//KHY - 0911 - ȣ���� �߰�.	
	case HORSEUNIQUE_TIGER:
		data = MAX_TIGER_SPEED;
		break;
	// PCK - 08/02/18 - ��Ÿ �߰�
	case HORSEUNIQUE_CAMEL:
		data = MAX_CAMEL_SPEED;
		break;
	// PCK - 08/04/01 - ����S�� �̺�Ʈ ȣ���� �߰�
	case HORSEUNIQUE_TIGER2:
		data = MAX_TIGER2_SPEED;
		break;
	// PCK - 08/06/12 - �ڳ��� �߰�
	case HORSEUNIQUE_ELEPHANT:
		data = MAX_ELEPHANT_SPEED;
		break;
	// PCK - 08/08/14 - ��ȣ �߰�
	case HORSEUNIQUE_WHITETIGER:
		data = MAX_WHITETIGER_SPEED;
		break;
	// PCK - 08/09/02 - ������� �߰�
	case HORSEUNIQUE_MOTORCYCLE:
		data = MAX_MOTORCYCLE_SPEED;
		break;
	// PCK - 08/12/10 - ����ġ �߰�
	case HORSEUNIQUE_FIREHATCH:
		data = MAX_FIREHATCH_SPEED;
		break;
	// PCK - 09/07/30 - ������Ʈ �߰�
	case HORSEUNIQUE_BAPHOMET:
		data = MAX_BAPHOMET_SPEED;
		break;
	// ���� - 09/08/30 - ȸ������ �߰�
	case HORSEUNIQUE_GRAYWOLF:
		data = MAX_GRAYWOLF_SPEED;
		break;
	// ���� - 09/12/31 - ����� �߰�
	case HORSEUNIQUE_SASURI:
		data = MAX_SASURI_SPEED;
		break;
	default:
		data = MAX_HORSE_SPEED;
		break;
	}
	
	return data;
}


SI32 cltHorseManager::GetFullLife(SI32 unique)
{
	SI32 data;
	switch(unique)
	{
	case HORSEUNIQUE_BROWN:		// ������	
		data = MAX_HORSE_LIFE;
		break;
	case HORSEUNIQUE_WOLF:
		data = MAX_UNLIMITEDHORSE_LIFE;
		break;
	//KHY - 0622 - ����S �ʺ��ڿ�  ������ �߰�.
	case HORSEUNIQUE_FOAL:
		data = MAX_FOAL_LIFE;
		break;			
	//KHY - 0911 - ȣ���� �߰�.
	case HORSEUNIQUE_TIGER:
		data = MAX_UNLIMITEDHORSE_LIFE;
		break;
	// PCK - 08/02/18 - ��Ÿ �߰�
	case HORSEUNIQUE_CAMEL:
		data = MAX_UNLIMITEDHORSE_LIFE;
		break;
	// PCK - 08/04/28 - �̺�Ʈ ȣ���� �߰�
	case HORSEUNIQUE_TIGER2:
		data = MAX_TIGER2_LIFE;
		break;
	// PCK - 08/06/12 - �ڳ��� �߰�
	case HORSEUNIQUE_ELEPHANT:
		data = MAX_UNLIMITEDHORSE_LIFE;
		break;
	// PCK - 08/08/14 - ��ȣ �߰�
	case HORSEUNIQUE_WHITETIGER:
		data = MAX_WHITETIGER_LIFE;
		break;
	// PCK - 08/09/02 - ������� �߰�
	case HORSEUNIQUE_MOTORCYCLE:
		data = MAX_UNLIMITEDHORSE_LIFE;
		break;
	// PCK - 08/12/10 - ����ġ �߰�
	case HORSEUNIQUE_FIREHATCH:
		data = MAX_UNLIMITEDHORSE_LIFE;
		break;
	// ü��� �鸶 : �ռ���-2009.03.17
	case HORSEUNIQUE_WHITE_TEST:
		data = MAX_WHITEHORSE_TEST_LIFE;
		break;
	// PCK - 09/07/30 - ������Ʈ �߰�
	case HORSEUNIQUE_BAPHOMET:
		data = MAX_UNLIMITEDHORSE_LIFE;
		break;
	// ���� - 09/08/30 - ȸ������ �߰�
	case HORSEUNIQUE_GRAYWOLF:
		data = MAX_GRAYWOLF_LIFE;
		break;
		// ���� - 09/12/31 - ����� �߰�
	case HORSEUNIQUE_SASURI:
		data = MAX_UNLIMITEDHORSE_LIFE;
		break;
	default:
		data = MAX_SPECIALHORSE_LIFE;
		break;
	}
	
	return data;
}

// ���� ����(��)�� ���Ѵ�. 
SI32 cltHorseManager::GetLife(cltHorse* pclhorse, SI32 curday)
{
	if(pclhorse == NULL)return 0;

	SI32 birthday	= pclhorse->clBirthDate.GetDateVary();
	
	// ���� ����
	if(GetFullLife(pclhorse->siHorseUnique) == MAX_UNLIMITEDHORSE_LIFE)
	{
		return MAX_UNLIMITEDHORSE_LIFE;
	}

	return max(0, GetFullLife(pclhorse->siHorseUnique) - (curday - birthday) - pclhorse->siLife);
}

void cltHorseManager::SetLife(cltHorse* pclhorse, SI32 curday, SI32 life)
{
	if(pclhorse == NULL)return;

	SI32 birthday	= pclhorse->clBirthDate.GetDateVary();
	
	pclhorse->siLife = GetFullLife(pclhorse->siHorseUnique) - curday + birthday - life;
	
	return ;
}



SI32 cltHorseManager::Action(cltServer* pclserver, cltHorse* pclhorse, SI32 skilllevel, SI32 datevary, bool bselfswitch, SI32* prewardamount)
{
	bool bupdateswitch = false;
	if(pclhorse == NULL || pclhorse->siHorseUnique <= 0)return HORSEACTION_NONE;
	
	// ���� ���̸� ���Ѵ�. 
	SI32 siage		= pclhorse->GetAge(datevary);

	// ������ �� �Ǿ��ٸ� ���δ�. 
	SI32 life = pclserver->pclHorseManager->GetLife(pclhorse, datevary);

	//KHY - 1111 - ������� �߰�. - ������̴� ������ ����  ó��.
	if(pclhorse->siHorseUnique != HORSEUNIQUE_MOTORCYCLE)
	{
		if(life <= 0)
		{
			// selfswitch�� false�� ����(â��)���� ��û�� ���̹Ƿ� �� �ʱ�ȭ�� ���� �ʴ´�
			if ( true == bselfswitch )
			{
				pclhorse->Init();
			}
			
			return HORSEACTION_DIE;		// ���ó��. 
		}
	}
	
	// �ɷ���� ���Ͽ� �˻��ϰ� ������Ʈ ���ش�.
	//KHY - 1111 - ������� �߰�. - ������̴� Ż�� ��ȭ�� ��� �Ұ�.
	SI32 siHorseUnique = pclhorse->siHorseUnique	;
	if( siHorseUnique != HORSEUNIQUE_MOTORCYCLE)
	{
		if ( GetAddStatusLimitDateVary(pclhorse) < pclserver->pclTime->clDate.GetDateVary() &&
			 pclhorse->siStatusTicketNum > 0 )
		{
			pclhorse->clAddStatusDate.MakeFullDateFromDateVary(0);
			pclhorse->siStatusTicketNum = 0 ;

			return HORSEATTION_TICKET;
		}
		// �����̾�����
		if ( GetPremiumPArtsDateVary_Slot1(pclhorse) < pclserver->pclTime->clDate.GetDateVary() &&
			pclhorse->GetPremiumUnique_Slot1() > 0 )
		{
			pclhorse->clPremiumPartsDate_Slot1.MakeFullDateFromDateVary(0);
			pclhorse->SetPremiumPartsUnique_Slot1(0);
			pclhorse->AddPremiumPartsNum(-1)	;
			return HORSEATTION_PREMIUMPARTS;
		}
		// �����̾�����
		if ( GetPremiumPArtsDateVary_Slot2(pclhorse) < pclserver->pclTime->clDate.GetDateVary() &&
			pclhorse->GetPremiumUnique_Slot2() > 0 )
		{
			pclhorse->clPremiumPartsDate_Slot2.MakeFullDateFromDateVary(0);
			pclhorse->SetPremiumPartsUnique_Slot2(0);
			pclhorse->AddPremiumPartsNum(-1)	;
			return HORSEATTION_PREMIUMPARTS;
		}
		// �����̾�����
		if ( GetPremiumPArtsDateVary_Slot3(pclhorse) < pclserver->pclTime->clDate.GetDateVary() &&
			pclhorse->GetPremiumUnique_Slot3() > 0 )
		{
			pclhorse->clPremiumPartsDate_Slot3.MakeFullDateFromDateVary(0);
			pclhorse->SetPremiumPartsUnique_Slot3(0);
			pclhorse->AddPremiumPartsNum(-1)	;
			return HORSEATTION_PREMIUMPARTS;
		}
	}
	else if( siHorseUnique == HORSEUNIQUE_MOTORCYCLE)
	{
		// �����̾�����
		if ( GetPremiumPArtsDateVary_Slot1(pclhorse) < pclserver->pclTime->clDate.GetDateVary() &&
			pclhorse->GetPremiumUnique_Slot1() > 0 )
		{
			pclhorse->clPremiumPartsDate_Slot1.MakeFullDateFromDateVary(0);
			pclhorse->SetPremiumPartsUnique_Slot1(0);
			pclhorse->AddPremiumPartsNum(-1)	;
			return HORSEATTION_PREMIUMPARTS;
		}
		// �����̾�����
		if ( GetPremiumPArtsDateVary_Slot2(pclhorse) < pclserver->pclTime->clDate.GetDateVary() &&
			pclhorse->GetPremiumUnique_Slot2() > 0 )
		{
			pclhorse->clPremiumPartsDate_Slot2.MakeFullDateFromDateVary(0);
			pclhorse->SetPremiumPartsUnique_Slot2(0);
			pclhorse->AddPremiumPartsNum(-1)	;
			return HORSEATTION_PREMIUMPARTS;
		}
		// �����̾�����
		if ( GetPremiumPArtsDateVary_Slot3(pclhorse) < pclserver->pclTime->clDate.GetDateVary() &&
			pclhorse->GetPremiumUnique_Slot3() > 0 )
		{
			pclhorse->clPremiumPartsDate_Slot3.MakeFullDateFromDateVary(0);
			pclhorse->SetPremiumPartsUnique_Slot3(0);
			pclhorse->AddPremiumPartsNum(-1)	;
			return HORSEATTION_PREMIUMPARTS;
		}
	}
	
	//-----------------------------------------------
	// ���� ���� �ð� ������ �ʹ� ��� ���� ������ ������. 
	//-----------------------------------------------
	SI32 data = max(10, life);
	SI32 diff = TABS(datevary - pclhorse->siLastUpdateSecond ) / data;
	if(pclhorse->siLastUpdateSecond)
	{
		if(diff > 0)
		{
			diff = min(diff, 100);
			
			switch(rand() % 3)
			{
			case 0:
				pclhorse->siMoveSpeed = max(500, (pclhorse->siMoveSpeed- diff));
				pclhorse->siLastUpdateSecond	= datevary;
				break;
				
			case 1:
				pclhorse->siStr = max(10, (pclhorse->siStr - diff));
				pclhorse->siLastUpdateSecond	= datevary;
				break;
				
			case 2:
				pclhorse->siDex = max(10, (pclhorse->siDex - diff));
				pclhorse->siLastUpdateSecond	= datevary;
				break;
			}
			
			//-----------------------------
			// �䱸������ �ʱ�ȭ�Ѵ�.
			//-----------------------------
			pclhorse->siNeed	= 0;
			pclhorse->siPara1	= 0;
			pclhorse->siPara2	= 0;
			pclhorse->siSupply	= 0;
			pclhorse->siDueTime = 0;
			pclhorse->siRate	= 0;
			
			// ���� �ʱ�ȭ�Ѵ�. 
			pclhorse->siRewardType		= 0;
			pclhorse->siRewardAmount	= 0;

			// ���� ������ ���δ�. 
			// ���̿� ����Ͽ� �پ��� ���� �����Ѵ�. 
			pclhorse->siLife += max(1, diff *  max(1, siage / 2) );
			
			bupdateswitch = true;
		}
	}
	else
	{
		pclhorse->siLastUpdateSecond = datevary;
		bupdateswitch = true;
	}

	
	// ���� �ð��� ���Ѵ�. 
	SI32 curhour = pclserver->pclTime->clDate.GetHourVary();
	
	// �̹� �䱸 ������ �ִ°� ?
	if(pclhorse->siNeed)
	{
		// �䱸���� ����ñⰡ �����°� ?
		if(curhour >= pclhorse->siDueTime)
		{
			SI32 rate = CheckNeed(pclhorse);
			// �����Ѵ�. 
			Reward(pclhorse, rate, bselfswitch, prewardamount);


			// �䱸������ �ʱ�ȭ�Ѵ�.
			pclhorse->siNeed = 0;
			pclhorse->siPara1	= 0;
			pclhorse->siPara2	= 0;
			pclhorse->siSupply	= 0;
			pclhorse->siDueTime = 0;
			pclhorse->siRate	= 0;
			
			// ���� �ʱ�ȭ�Ѵ�. 
			pclhorse->siRewardType		= 0;
			pclhorse->siRewardAmount	= 0;
			
			bupdateswitch = true;
		}
		// ����ñⰡ ���� ������ �ʾҴٸ� ������ �����Ǿ����� Ȯ���Ѵ�.
		else
		{
			// ������ �����Ǿ����� �����Ѵ�.
			SI32 rate = CheckNeed(pclhorse);
			if(rate >= 100)
			{
				// �����Ѵ�. 
				Reward(pclhorse, rate, bselfswitch, prewardamount);

				//-----------------------------
				// �䱸������ �ʱ�ȭ�Ѵ�.
				//-----------------------------
				pclhorse->siNeed = 0;
				pclhorse->siPara1	= 0;
				pclhorse->siPara2	= 0;
				pclhorse->siSupply	= 0;
				pclhorse->siDueTime = 0;
				pclhorse->siRate	= 0;
				
				// ���� �ʱ�ȭ�Ѵ�. 
				pclhorse->siRewardType		= 0;
				pclhorse->siRewardAmount	= 0;

				bupdateswitch = true;
			}
		}
	}
	else
	{
		// ������ �䱸 �ð����� ���� �ð��� �������� ���ο� �䱸�� �����. 
		// ���̿� ���� ���� �䱸 ������ �۾����� �Ѵ�. 
		SI32 datevary	= pclserver->pclTime->clDate.GetDateVary();
		SI32 birthvary	= pclhorse->clBirthDate.GetDateVary();
		SI32 year = TABS(datevary - birthvary) / 360;

	
		SI32 delay = 0;
		if(year > 5)		delay = 60;
		else if(year > 4)	delay = 50;
		else if(year > 3)	delay = 40;
		else if(year > 2)	delay = 30;
		else if(year > 1)	delay = 25;
		else				delay = 17;
		
		// �ڽ��� ���� Ű�ﶧ�� �� ���� �䱸�Ѵ�. 
		if(bselfswitch)
		{
			delay = delay * 7 / 10;		// (70%)
		}
		
		if(TABS(curhour - pclhorse->siLastNeedTime) >= delay)
		{
			if(MakeHorseNeed(pclserver->pclItemManager->clItemStatistic.siNPCPriceRate,  
				skilllevel, 
				pclhorse, 
				curhour + 3, 
				&pclserver->pclTime->clDate) == true)
			{
				pclhorse->siLastNeedTime	= curhour;
				bupdateswitch				= true;
			}
		}
	}
	

	if(bupdateswitch)return HORSEACTION_UPDATE;

	return HORSEACTION_NONE;
}

// �䱸������ �������״��� Ȯ���Ѵ�.
SI32 cltHorseManager::CheckNeed(cltHorse* pclhorse)
{
	if(pclhorse == NULL)			return 0;
	SI32 rate;

	switch(pclhorse->siNeed)
	{
	case HORSE_NEED_FEED:
		// �䱸 ������ �� %�� Ȯ���ߴ��� Ȯ���Ѵ�. 
		if(pclhorse->siPara2 == 0)
		{
			return 0;
		}
		else
		{
			rate = pclhorse->siSupply * 100 / pclhorse->siPara2;
			return min(200, rate);
		}
		break;
	}

	return 0;
}

// ������ �����Ѵ�. 
bool cltHorseManager::Reward(cltHorse* pclhorse, SI32 rate, bool bselfswitch, SI32* prewardamount)
{
	if(pclhorse == NULL)	return false;
	if(rate <= 0)			return false;

	SI32 rewardamount = (pclhorse->siRewardAmount * rate / 100);

	// ���� Ű�� ���� ���, 
	if(bselfswitch)
	{
		rewardamount = rewardamount * 2;
	}

	switch(pclhorse->siRewardType)
	{
	case HORSE_REWARDTYPE_SPEED:
		pclhorse->siMoveSpeed += rewardamount;
		break;

	case HORSE_REWARDTYPE_STR:
		pclhorse->siStr += rewardamount;
		break;
	case HORSE_REWARDTYPE_DEX:
		pclhorse->siDex += rewardamount;
		break;
	case HORSE_REWARDTYPE_MAG:
		pclhorse->siMag += rewardamount;
		break;
	}

	*prewardamount = rewardamount;

	return true;
}

// ���� �䱸������ �����. 
bool cltHorseManager::MakeHorseNeed(SI32 npcpricerate, SI32 skilllevel, cltHorse* pclhorse, SI32 duetime, cltDate* pcldate)
{
	SI32 i;

	if(pclhorse == NULL)			return false;

	//SI32 food[] ={
	//		ITEMUNIQUE(3600), // ��
	//		ITEMUNIQUE(3605), // ��
	//		ITEMUNIQUE(3610), // �̳���. 
	//		ITEMUNIQUE(3615), //ǥ�����.
	//		ITEMUNIQUE(3620), //��� 
	//		ITEMUNIQUE(3625), // ����
	//		ITEMUNIQUE(3630), //����
	//		ITEMUNIQUE(3635), //���� 
	//		ITEMUNIQUE(3640), //����
	//		ITEMUNIQUE(3645), //���
	//		ITEMUNIQUE(3650), // ���� 
	//		ITEMUNIQUE(3655), // ��
	//		ITEMUNIQUE(3660), //���� 
	//		ITEMUNIQUE(3665), //�� 
	//		ITEMUNIQUE(16000), //�ұ� 
	//		ITEMUNIQUE(3685)  //��
	//};

	//SI32 food2[] ={
	//		ITEMUNIQUE(3670), // �߰��
	//		ITEMUNIQUE(3675), // �������
	//		ITEMUNIQUE(3680), // ����
	//		ITEMUNIQUE(16100), // �ؾ�
	//		ITEMUNIQUE(16110), // �ޱ�
	//		ITEMUNIQUE(16120), // �׾�
	//		ITEMUNIQUE(16150), // ���
	//		ITEMUNIQUE(16160), // ����
	//};

	// �䱸������ �ʱ�ȭ�Ѵ�.
	//SI32 data = 0 ;
	SI32 fooduniue	= 0 ;

	//if ( pclhorse->siHorseUnique == HORSEUNIQUE_WOLF )
	switch( pclhorse->siHorseUnique )
	{
	case HORSEUNIQUE_WOLF:
	case HORSEUNIQUE_TIGER: //KHY - 0911 - ȣ���� �߰�.
		{
			fooduniue = GetUniqueWithRandom(HorseFood_Meat_ItemUnique, sizeof(HorseFood_Meat_ItemUnique) / sizeof(SI32));
		}
		break;
	case HORSEUNIQUE_MOTORCYCLE: //KHY - ������� �߰�.
		{
			fooduniue = GetUniqueWithRandom(HorseFood_Mineral_ItemUnique, sizeof(HorseFood_Mineral_ItemUnique) / sizeof(SI32));
		}
		break;
	default:
		{
			fooduniue = GetUniqueWithRandom(HorseFood_Vegetable_ItemUnique, sizeof(HorseFood_Vegetable_ItemUnique) / sizeof(SI32));
			//data = rand() % 16;
			//fooduniue = food[data];
		}
		break;
	}

	// �ش� ��ǰ�� �ü��� ���Ѵ�. 
	cltItemPriceUnit* pclprice = pclClient->pclItemManager->GetCurrentPrice(fooduniue);
	if(pclprice == NULL)return false;
	if(pclprice->siPrice <= 0)return false;

	SI32 foodmoney		= 1500 + (pclhorse->GetAge( pcldate->GetDateVary() ) * 100) ; // ���̰� �������� �� ���� ���̸� �䱸�Ѵ�.
	foodmoney			= (foodmoney * min(100, npcpricerate)) / 100;
	SI32 num			= min(20, max(1, foodmoney / pclprice->siPrice));
	//-------------------------------------
	// ������ ���� ����Ѵ�. 
	//-------------------------------------
	SI32 rewardamount = 0;
	SI32 tempskilllevel = skilllevel;

	if(tempskilllevel > 60)
	{
		rewardamount += max(1, (tempskilllevel-60) / 10+1);
		tempskilllevel = 60;
	}
	if(tempskilllevel > 50)
	{
		rewardamount += max(1, (tempskilllevel-50) / 5);
		tempskilllevel = 50;
	}
	if(tempskilllevel > 40)
	{
		rewardamount += max(1, (tempskilllevel-40) / 4);
		tempskilllevel = 40;
	}
	if(tempskilllevel > 20)
	{
		rewardamount += max(1, (tempskilllevel-20) / 3);
		tempskilllevel = 20;
	}

	rewardamount += max(1, tempskilllevel / 2);

	
	// �̵��ӵ��� ���� ���� ������ ���� �̵� �ӵ��� ���ȴ�.
	bool bspeedswitch = false;
	if(pclhorse->siMoveSpeed < 1000)
	{
		bspeedswitch = true;
	}
	
	SI32 rewardlist[100];
	SI32 rewardlistindex	= 0;

	if(pclhorse->siMoveSpeed < pclClient->pclHorseManager->GetFullSpeed( pclhorse->siHorseUnique ) )
	{
		rewardlist[rewardlistindex] = HORSE_REWARDTYPE_SPEED;
		rewardlistindex++;
	}

	if(bspeedswitch == false && pclhorse->siStr < pclClient->pclHorseManager->GetFullStr( pclhorse->siHorseUnique ))
	{
		for(i = 0;i < 4;i++)
		{
			rewardlist[rewardlistindex] = HORSE_REWARDTYPE_STR;
			rewardlistindex++;
		}
	}

	if(bspeedswitch == false && pclhorse->siDex < pclClient->pclHorseManager->GetFullDex( pclhorse->siHorseUnique ))
	{
		for(i = 0;i < 4;i++)
		{
			rewardlist[rewardlistindex] = HORSE_REWARDTYPE_DEX;
			rewardlistindex++;
		}
	}

	if(bspeedswitch == false && pclhorse->siMag < pclClient->pclHorseManager->GetFullMag( pclhorse->siHorseUnique ))
	{
		for(i = 0;i < 4;i++)
		{
			rewardlist[rewardlistindex] = HORSE_REWARDTYPE_MAG;
			rewardlistindex++;
		}
	}

	if(rewardlistindex)
	{
		pclhorse->siRewardType		= rewardlist[rand() % rewardlistindex];
		pclhorse->siRewardAmount	= rewardamount;
	}
	else
	{
		pclhorse->siRewardType		= 0;
		pclhorse->siRewardAmount	= 0;	
	}

	pclhorse->siRate			= 1;

	pclhorse->siNeed	= HORSE_NEED_FEED;
	pclhorse->siPara1	= fooduniue;	// ���� ���� ����ũ. 
	pclhorse->siPara2	= num + (rand() % num);	// �䱸 ����. 
	pclhorse->siSupply	= 0;				// ���� ��Ȳ�� Ȯ���Ѵ�. 
	
	pclhorse->siDueTime	= duetime;
	
	//-----------------------------
	// ������ �ִ� �޿� 2�谡 �ȴ�. 
	//-----------------------------
	if(pclhorse->siRewardType)
	{
		
		if( pclhorse->GetAge(pcldate->GetDateVary()) > 1 && (pclhorse->clBirthDate.uiMonth == pcldate->uiMonth))
		{
			pclhorse->siRewardAmount	*= 2;
			pclhorse->siRate			=  0;
		}
	}
	
	return true;
}

// ���� �Ա� ���ϴ� ������ ����ũ�� ������ ���´�. 
bool cltHorseManager::GetHorseFoodNeed(cltHorse* pclhorse, SI32* pitemunique, SI32* pitemnum)
{
	if(pclhorse == NULL)					return false;
	if(pclhorse->siNeed != HORSE_NEED_FEED)	return false;


	*pitemunique	= pclhorse->siPara1;
	*pitemnum		= pclhorse->siPara2;

	return  true;
}


// ������ ���̸� �ش�.
bool cltHorseManager::GiveFood(cltHorse* pclhorse, cltItem* pclitem)
{
	if(pclhorse == NULL)return false;
	if(pclhorse->siNeed != HORSE_NEED_FEED)return false;

	// ���ɻ��
	if(pclitem->siUnique == ITEMUNIQUE(3855))
	{
		pclhorse->siSupply = pclhorse->siPara2 * 2;
	} 
	// ������
	else if(pclitem->siUnique == ITEMUNIQUE(3850))
	{		
		pclhorse->siSupply = pclhorse->siPara2;
	}	
	// ���ϴ� �����̸�, 
	else if(pclhorse->siPara1 == pclitem->siUnique)
	{
		// ������ ���̸� �����Ѵ�. 
		pclhorse->siSupply += pclitem->siItemNum;
		pclhorse->siSupply = min(pclhorse->siPara2, pclhorse->siSupply);

	}
	else
	{
		return false;
	}


	// ���̸� ���� ���� �ֱ� �ð��� ������Ʈ �Ѵ�. 
	pclhorse->siLastUpdateSecond	= ((cltServer*)pclClient)->pclTime->clDate.GetDateVary();

	return true;
}


// ���� �䱸 ������ �ؽ�Ʈ�� ���´�. 
bool cltHorseManager::GetNeedText(cltHorse* pclhorse, TCHAR* ptext, SI16 txtSize)
{
	if(pclhorse == NULL)						return false;
	TCHAR buffer[512] = TEXT("") ;
	
	switch(pclhorse->siNeed)
	{
	case HORSE_NEED_FEED:
		{
			// �԰��� �ϴ� ������ �̸��� ���Ѵ�. 
			const TCHAR* pname = pclClient->pclItemManager->GetName(pclhorse->siPara1);
			if(pname == NULL)return false;

			if(pclhorse->siPara2 > pclhorse->siSupply)
			{
				// ������ �ִ� ���̴�.!!
				if(pclhorse->siRate == 0)
				{
					TCHAR* pText = GetTxtFromMgr(3610);
					
					TCHAR num[128]= TEXT(" ") ;					
					StringCchPrintf(num, 128, TEXT("%d"),pclhorse->siPara2 - pclhorse->siSupply);
					Nsprintf(buffer,pText,TEXT("item"),  pname  ,TEXT("num"), num   ,NULL);
					//sprintf(buffer,pText, pname, (pclhorse->siPara2 - pclhorse->siSupply));
				}
				else
				{
					TCHAR* pText = GetTxtFromMgr(3611);
					TCHAR num[128]= TEXT(" ") ;					
					StringCchPrintf(num, 128, TEXT("%d"),pclhorse->siPara2 - pclhorse->siSupply);
					Nsprintf(buffer,pText,TEXT("item"),  pname  ,TEXT("num"), num   ,NULL);
					//sprintf(buffer,pText, pname, (pclhorse->siPara2 - pclhorse->siSupply));
				}
			}
		}
		
		break;
	}

	StringCchCat(ptext, txtSize, buffer);

	return true;
}

// ���� �߰� ������ ���ѳ��ڸ� �ؽ�Ʈ�� ���´�.
void cltHorseManager::GetAddStatusLimitDateText(cltHorse* pclhorse, TCHAR* ptext, SI16 txtSize)
{
	TCHAR buffer[256] = TEXT("") ;
	cltClient* pclclient = (cltClient*)pclClient;

	if ( pclhorse == NULL ) return ;
	if(pclhorse->siHorseUnique <= 0)return ;

	SI32 limitdate = 0 ;
	limitdate = pclhorse->clAddStatusDate.GetDateVary() + MAX_HORSE_ADDSTATUS_LIMITDATE * pclhorse->siStatusTicketNum ;

	if ( pclclient->clClientDate.GetDateVary() > limitdate ) return ;

	cltDate cldate;
	cldate.MakeFullDateFromDateVary( limitdate ) ;
	if ( cldate.GetDateText( buffer ) == FALSE )
	{
		return ;
	}

	NTCHARString256 pText = GetTxtFromMgr(3612);
	pText.Replace(TEXT("#period#"),buffer);
	StringCchPrintf(ptext, txtSize, pText,buffer);
}

void cltHorseManager::GetAddStatusLimitDateText(cltHorse* pclhorse,TCHAR* ptext, SI16 txtSize, SI32 TextMgrIndex)
{
	TCHAR buffer[256] = TEXT("") ;
	cltClient* pclclient = (cltClient*)pclClient;

	if ( pclhorse == NULL ) return ;
	if(pclhorse->siHorseUnique <= 0)return ;

	SI32 limitdate = 0 ;
	limitdate = pclhorse->clAddStatusDate.GetDateVary() + MAX_HORSE_ADDSTATUS_LIMITDATE * pclhorse->siStatusTicketNum ;

	if ( pclclient->clClientDate.GetDateVary() > limitdate ) return ;

	cltDate cldate;
	cldate.MakeFullDateFromDateVary( limitdate ) ;
	if ( cldate.GetDateText( buffer ) == FALSE )
	{
		return ;
	}

	NTCHARString256 pText  = GetTxtFromMgr(TextMgrIndex);
	pText.Replace(TEXT("#period#"),buffer);
	StringCchPrintf(ptext, txtSize, pText,buffer);
}


void cltHorseManager::GetPremiumPartsDateText_Slot1(cltHorse* pclhorse,TCHAR* ptext, SI16 txtSize)
{
	TCHAR buffer[256] = TEXT("") ;
	cltClient* pclclient = (cltClient*)pclClient;

	if ( pclhorse == NULL ) return ;
	if(pclhorse->siHorseUnique <= 0)return ;

	SI32 limitdate = 0 ;
	limitdate = pclhorse->clPremiumPartsDate_Slot1.GetDateVary() + MAX_HORSE_ADDSTATUS_LIMITDATE ;

	if ( pclclient->clClientDate.GetDateVary() > limitdate ) return ;

	cltDate cldate;
	cldate.MakeFullDateFromDateVary( limitdate ) ;
	if ( cldate.GetDateText( buffer ) == FALSE )
	{
		return ;
	}

	NTCHARString256 pText = TEXT("");
	// ���߷�	
	if ( pclhorse->GetPremiumUnique_Slot1() == ITEMUNIQUE(13635 ) 
		|| pclhorse->GetPremiumUnique_Slot1() == ITEMUNIQUE( 13638 )  )
	{
		pText = GetTxtFromMgr(9840);
	}
	// �ٷ°�ȭ
	else if ( pclhorse->GetPremiumUnique_Slot1() == ITEMUNIQUE(13636 ) 
		|| pclhorse->GetPremiumUnique_Slot1() == ITEMUNIQUE( 13639 )  )
	{
		pText = GetTxtFromMgr(9841);
	}
	// ���°�ȭ
	else if ( pclhorse->GetPremiumUnique_Slot1() == ITEMUNIQUE(13637 ) 
		|| pclhorse->GetPremiumUnique_Slot1() == ITEMUNIQUE( 13640 )  )
	{
		pText = GetTxtFromMgr(9842);
	}

	pText.Replace( TEXT("#period#"),buffer );
	memcpy(ptext,pText,sizeof(pText));
}
void cltHorseManager::GetPremiumPartsDateText_Slot2(cltHorse* pclhorse,TCHAR* ptext, SI16 txtSize)
{
	TCHAR buffer[256] = TEXT("") ;
	cltClient* pclclient = (cltClient*)pclClient;

	if ( pclhorse == NULL ) return ;
	if(pclhorse->siHorseUnique <= 0)return ;

	SI32 limitdate = 0 ;
	limitdate = pclhorse->clPremiumPartsDate_Slot2.GetDateVary() + MAX_HORSE_ADDSTATUS_LIMITDATE ;

	if ( pclclient->clClientDate.GetDateVary() > limitdate ) return ;

	cltDate cldate;
	cldate.MakeFullDateFromDateVary( limitdate ) ;
	if ( cldate.GetDateText( buffer ) == FALSE )
	{
		return ;
	}

	NTCHARString256 pText = TEXT("");
	// ���߷�	
	if ( pclhorse->GetPremiumUnique_Slot2() == ITEMUNIQUE(13635 ) 
		|| pclhorse->GetPremiumUnique_Slot2() == ITEMUNIQUE( 13638 )  )
	{
		pText = GetTxtFromMgr(9840);
	}
	// �ٷ°�ȭ
	else if ( pclhorse->GetPremiumUnique_Slot2() == ITEMUNIQUE(13636 ) 
		|| pclhorse->GetPremiumUnique_Slot2() == ITEMUNIQUE( 13639 )  )
	{
		pText = GetTxtFromMgr(9841);
	}
	// ���°�ȭ
	else if ( pclhorse->GetPremiumUnique_Slot2() == ITEMUNIQUE(13637 ) 
		|| pclhorse->GetPremiumUnique_Slot2() == ITEMUNIQUE( 13640 )  )
	{
		pText = GetTxtFromMgr(9842);
	}

	pText.Replace( TEXT("#period#"),buffer );
	memcpy(ptext,pText,sizeof(pText));
}
void cltHorseManager::GetPremiumPartsDateText_Slot3(cltHorse* pclhorse,TCHAR* ptext, SI16 txtSize)
{
	TCHAR buffer[256] = TEXT("") ;
	cltClient* pclclient = (cltClient*)pclClient;

	if ( pclhorse == NULL ) return ;
	if(pclhorse->siHorseUnique <= 0)return ;

	SI32 limitdate = 0 ;
	limitdate = pclhorse->clPremiumPartsDate_Slot3.GetDateVary() + MAX_HORSE_ADDSTATUS_LIMITDATE ;

	if ( pclclient->clClientDate.GetDateVary() > limitdate ) return ;

	cltDate cldate;
	cldate.MakeFullDateFromDateVary( limitdate ) ;
	if ( cldate.GetDateText( buffer ) == FALSE )
	{
		return ;
	}

	NTCHARString256 pText = TEXT("");
	// ���߷�	
	if ( pclhorse->GetPremiumUnique_Slot3() == ITEMUNIQUE(13635 ) 
		|| pclhorse->GetPremiumUnique_Slot3() == ITEMUNIQUE( 13638 )  )
	{
		pText = GetTxtFromMgr(9840);
	}
	// �ٷ°�ȭ
	else if ( pclhorse->GetPremiumUnique_Slot3() == ITEMUNIQUE(13636 ) 
		|| pclhorse->GetPremiumUnique_Slot3() == ITEMUNIQUE( 13639 )  )
	{
		pText = GetTxtFromMgr(9841);
	}
	// ���°�ȭ
	else if ( pclhorse->GetPremiumUnique_Slot3() == ITEMUNIQUE(13637 ) 
		|| pclhorse->GetPremiumUnique_Slot3() == ITEMUNIQUE( 13640 )  )
	{
		pText = GetTxtFromMgr(9842);
	}

	pText.Replace( TEXT("#period#"),buffer );
	memcpy(ptext,pText,sizeof(pText));
}
SI32 cltHorseManager::GetAddStatusLimitDateVary(cltHorse* pclhorse)
{
	if(pclhorse == NULL)		return 0;

	SI32 limitdate = 0 ;
	limitdate = pclhorse->clAddStatusDate.GetDateVary() + MAX_HORSE_ADDSTATUS_LIMITDATE * pclhorse->siStatusTicketNum ;

	return limitdate ;
}
SI32 cltHorseManager::GetPremiumPArtsDateVary_Slot1(cltHorse* pclhorse)
{
	if(pclhorse == NULL)		return 0;

	SI32 limitdate = 0 ;
	limitdate = pclhorse->clPremiumPartsDate_Slot1.GetDateVary() + MAX_HORSE_ADDSTATUS_LIMITDATE * pclhorse->GetPremiumPartsNum_Slot1()	;

	return limitdate ;
}
SI32 cltHorseManager::GetPremiumPArtsDateVary_Slot2(cltHorse* pclhorse)
{
	if(pclhorse == NULL)		return 0;

	SI32 limitdate = 0 ;
	limitdate = pclhorse->clPremiumPartsDate_Slot2.GetDateVary() + MAX_HORSE_ADDSTATUS_LIMITDATE * pclhorse->GetPremiumPartsNum_Slot2()	;

	return limitdate ;
}
SI32 cltHorseManager::GetPremiumPArtsDateVary_Slot3(cltHorse* pclhorse)
{
	if(pclhorse == NULL)		return 0;

	SI32 limitdate = 0 ;
	limitdate = pclhorse->clPremiumPartsDate_Slot3.GetDateVary() + MAX_HORSE_ADDSTATUS_LIMITDATE * pclhorse->GetPremiumPartsNum_Slot3()	;

	return limitdate ;
}

