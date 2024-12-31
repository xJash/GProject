//---------------------------------
// 2003/11/19 ���°�
//---------------------------------

#ifndef _DISEASE_H
#define _DISEASE_H

#include <Directives.h>

#define MAX_DISEASE_NUMBER				20		// ������ �ִ� ���� 
#define DISEASE_NAME					32		
#define DISEASE_TYPE					32		// ����Ÿ��


//--------------------------------------
// ���� ����. 
//--------------------------------------
class cltDiseaseInfo
{
public:
	SI32 siUnique;		// ������ ����ũ. 
	SI32 siType;		// ������� ��ȯ�ΰ� ?
	SI32 siLevel;		// clInfo.uiOrg1Disease ��ġ�� �� �̻��� �Ǹ� �� ������ �ɸ��°�?
	SI32 siPenalty;		// �ǰ��� ��ġ�� �ؾ�. (0 ~ 100 : 0�̸� �ƹ��� �ؾ��� ����. ) 

	TCHAR szName[DISEASE_NAME];
	
	TCHAR szDiseaseType[DISEASE_TYPE];

	cltDiseaseInfo(SI32 unique, SI32 type, SI32 level, SI32 penalty, TCHAR* name, TCHAR* DiseaseType );
	~cltDiseaseInfo();
};

//--------------------------------------
// ���� �Ŵ���. 
//-------------------------------------
class cltDiseaseManager{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<cltDiseaseInfo*, MAX_DISEASE_NUMBER>		pclDisease;
#else
	cltDiseaseInfo* pclDisease[MAX_DISEASE_NUMBER];
#endif
	
	cltDiseaseManager();
	~cltDiseaseManager();

	// ���� ������ �߰��Ѵ�.
	bool Add(SI32 unique, SI32 type, SI32 level, SI32 penalty, TCHAR* name, TCHAR* DiseaseType);

	// ������ ������ ã�´�. 
	cltDiseaseInfo* FindDisease(SI32 org, SI32 level);

	// ������ �̸��� ����ũ�� ���Ѵ�.
	SI32 FindUniqueFromName(TCHAR* pname);

	// ������ ����ũ�� �̸��� ���Ѵ�. 
	bool GetNameFromdUnique(SI32 unique, TCHAR* pname, SI16 txtSize);


	// ����Ÿ������ ����ũ�� ���Ѵ�.
	SI32 FindUniqueFromDiseaseType(TCHAR* pDiseaseType);

	// ������ ����ũ�� ����Ÿ���� ���Ѵ�. 
	bool GetDiseaseTypeFromdUnique(SI32 unique, TCHAR* pDiseaseType, SI16 txtSize);

};


#endif
