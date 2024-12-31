//---------------------------------
// 2003/6/12 ���°�
//---------------------------------

#ifndef _RANK_H
#define _RANK_H

#include <Directives.h>
#include ".\..\Common\CommonHeader.h"


//-----------------------------------------
// ��������. 
//-----------------------------------------
class cltRank{
public:
	cltSimpleRank		clRank;			// �ź��� �ּ� ����. 
	cltSimplePerson		clPerson;		// ������� ���� 

public:
	cltRank()
	{
		Init();
	}
	cltRank(cltSimpleRank* pclrank, cltSimplePerson* pclperson)
	{
		clRank.Set(pclrank);
		clPerson.Set(pclperson);
	}

	void Init()
	{
		ZeroMemory(this, sizeof(cltRank));

		clRank.Init();
		clPerson.Init();
	}

	void Set(cltRank* pclrank)
	{
		Set(&pclrank->clRank, &pclrank->clPerson);
	}

	void Set(const cltSimpleRank* pclrank, const cltSimplePerson* pclperson);

	SI32 GetPersonID()const{return clPerson.GetPersonID();}
	SI32 GetRankType()const{return clRank.GetRankType();}

	SI32 GetVillageUnique()const{return clRank.GetVillageUnique();}

	void SetName(const TCHAR* pname){clPerson.SetName(pname);}
	const TCHAR* GetName()const{return clPerson.GetName();}

	const cltSimpleRank* GetRank()const {return &clRank;}
	const cltSimplePerson* GetPerson()const{ return &clPerson;}

	BOOL IsSame(cltSimpleRank* pclrank)const
	{
		return clRank.IsSame(pclrank);
	}
};

//---------------------------------------
// ���� ������. 
//---------------------------------------
class cltRankManager{
private:
	// �� �������� �����ϴ� ����. 
#ifdef _SAFE_MEMORY
	NSafeTArray< NSafeTArray<cltRank, MAX_VILLAGE_NUMBER>, MAX_RANKTYPE_NUMBER>		clRank;
#else
	cltRank clRank[MAX_RANKTYPE_NUMBER][MAX_VILLAGE_NUMBER];		// ����� ���� 
#endif


public:

	cltRankManager();
	~cltRankManager();

	// ������ ���� �ִ��� Ȯ���Ѵ�
	cltRank* GetRankInfo(SI32 personid);
	cltRank* GetRank(SI32 ranktype, SI32 villageunique);


	// �ź��� ���� ����� ����Ѵ�. 
	SI32 SetRank(const cltSimpleRank* pclrank, const cltSimplePerson* pclperson);
	
	// personid�� Ư�� �ź����� Ȯ���Ѵ�. 
	BOOL IsRank(SI32 personid, cltSimpleRank* pclrank);

	// personid�� Ư�� �ź��� �����Ѵ�. 
	BOOL DeleteRank(SI32 personid, cltSimpleRank* pclrank);

};

// �ź��� �̸��� ���´�. 
BOOL GetRankName(cltSimpleRank* pclrank, TCHAR* buffer, SI16 txtSize, UI08 grank = 0 );

//[����] ��ü ���� ���(����, ����...��) => 2008-4-3
bool GetMisterRankName(UI08 grank, TCHAR* buffer, SI16 txtSize);

//[����] ���� ���� ���(����, �ҿ���...��) => 2008-4-3
bool GetVillageRankName(cltSimpleRank* pclrank, TCHAR* buffer, SI16 txtSize);

#endif

