//---------------------------------
// 2003/11/19 ���°�
//---------------------------------

#include <CommonHeader.h>
#include "Disease.h"
#include "../CommonLogic/TextMgr/TextMgr.h"

//---------------------------------------------------------------
// ���� 
//---------------------------------------------------------------
cltDiseaseManager::cltDiseaseManager()
{
	SI32 i;

	for(i = 0;i < MAX_DISEASE_NUMBER;i++)
	{
		pclDisease[i] = NULL;
	}

	// ����ũ, �������ȯ����, �������ɸ����ִ�����ġ, �ؾ�, �ش������̸�, ����Ÿ��
	TCHAR* pText = GetTxtFromMgr(2824);
	Add(100,	ORG_1, 1,		10,		pText,	"DISEASE_DYSPEPSIA");			// ��ȭ��
	pText = GetTxtFromMgr(2825);
	Add(200,	ORG_1, 10,		15,		pText,	"DISEASE_GASTRITIS");		// ������
	pText = GetTxtFromMgr(2826);
	Add(300,	ORG_1, 20,		30,		pText,	"DISEASE_STOMOCHCANCER");	// �׾���
	
	pText = GetTxtFromMgr(2827);
	Add(400,	ORG_2, 1,		10,		pText,	"DISEASE_HYPERTENSION" );	// �����о�
//	Add(500,	ORG_2, 10,		15,		"���ư�ȭ");
//	Add(600,	ORG_2, 20,		30,		"�索��");
	
	pText = GetTxtFromMgr(2828);
	Add(700,	ORG_3, 1,		10,		pText,	"DISEASE_COLD");				// �����
//	Add(800,	ORG_3, 10,		15,		"���");
//	Add(900,	ORG_3, 20,		30,		"���");

	pText = GetTxtFromMgr(2829);
	Add(1100,	ORG_4, 1,		10,		pText,	"DISEASE_HEADACHE");		// �����
//	Add(1200,	ORG_4, 10,		15,		"����");
//	Add(1300,	ORG_4, 20,		30,		"ġ��");
}

cltDiseaseManager::~cltDiseaseManager()
{
	SI32 i;

	for(i = 0;i < MAX_DISEASE_NUMBER;i++)
	{
		if(pclDisease[i])
		{
			delete pclDisease[i];
			pclDisease[i] = NULL;
		}
		
	}
}

// ���� ������ �߰��Ѵ�. 
bool cltDiseaseManager::Add(SI32 unique, SI32 type, SI32 level, SI32 penalty, TCHAR* name, TCHAR* DiseaseType )
{
	SI32 i;

	for(i = 0;i < MAX_DISEASE_NUMBER;i++)
	{
		if(pclDisease[i] == NULL)
		{
			pclDisease[i] = new cltDiseaseInfo(unique, type, level, penalty, name, DiseaseType );
			return true;
		}
	}

	return false;

}

// ������ ������ ã�´�. (������ �ɸ� ��ġ�� �´���..)
cltDiseaseInfo* cltDiseaseManager::FindDisease(SI32 org, SI32 silevel)
{
	SI32 i;

	cltDiseaseInfo* prtn	= NULL;

	for(i = 0;i < MAX_DISEASE_NUMBER;i++)
	{
		if(pclDisease[i])
		{
			if(pclDisease[i]->siType == org)
			{
				if(silevel >= pclDisease[i]->siLevel)
				{
					prtn = pclDisease[i];
				}
			}
		}
	}

	return prtn;
}


// ������ �̸��� ����ũ�� ���Ѵ�.
SI32 cltDiseaseManager::FindUniqueFromName(TCHAR* pname)
{
	SI32 i;

	for(i = 0;i < MAX_DISEASE_NUMBER;i++)
	{
		if(pclDisease[i])
		{
			if(_tcscmp(pclDisease[i]->szName, pname) == 0)
			{
				return pclDisease[i]->siUnique;
			}
		}
	}

	return 0;
}

// ������ ����ũ�� �̸��� ���Ѵ�. 
bool cltDiseaseManager::GetNameFromdUnique(SI32 unique, TCHAR* pname, SI16 txtSize)
{

	SI32 i;

	for(i = 0;i < MAX_DISEASE_NUMBER;i++)
	{
		if(pclDisease[i]) 
		{
			if(pclDisease[i]->siUnique == unique)
			{
				StringCchCopy(pname, txtSize, pclDisease[i]->szName);
				return true;
			}
		}
	}

	return false;
}

// ����Ÿ������ ����ũ�� ���Ѵ�.
SI32 cltDiseaseManager::FindUniqueFromDiseaseType(TCHAR* pDiseaseType)
{
	SI32 i;

	for(i = 0;i < MAX_DISEASE_NUMBER;i++)
	{
		if(pclDisease[i])
		{
			// Disease ���� ����Ÿ���� ã�� �ش� ����ũ�� ã�´�.
			if(_tcscmp(pclDisease[i]->szDiseaseType, pDiseaseType) == 0)
			{
				return pclDisease[i]->siUnique;
			}
		}
	}

	return 0;
}

// ������ ����ũ�� ����Ÿ���� ���Ѵ�.
bool cltDiseaseManager::GetDiseaseTypeFromdUnique(SI32 unique, TCHAR* pDiseaseType, SI16 txtSize)
{

	SI32 i;

	for(i = 0;i < MAX_DISEASE_NUMBER;i++)
	{
		if(pclDisease[i]) 
		{
			if(pclDisease[i]->siUnique == unique)
			{
				StringCchCopy(pDiseaseType, txtSize, pclDisease[i]->szDiseaseType);
				return true;
			}
		}
	}

	return false;
}

//============================================
// cltDiseaseInfo
//============================================
cltDiseaseInfo::cltDiseaseInfo(SI32 unique, SI32 type, SI32 level, SI32 penalty, TCHAR* name, TCHAR* DiseaseType )
{
	siUnique	=	unique;
	siType		=	type;
	siLevel		=	level;
	siPenalty	=	penalty;

	MStrCpy( szName, name, DISEASE_NAME );
	MStrCpy( szDiseaseType, DiseaseType, DISEASE_TYPE );
}

cltDiseaseInfo::~cltDiseaseInfo()
{}


