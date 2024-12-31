//---------------------------------
// 2003/6/12 ���°�
//---------------------------------
#ifndef _CANDIDATE_H
#define _CANDIDATE_H

#include <Directives.h>

#include "..\..\Common\CommonHeader.h"
#include "..\Rank\Rank.h"

#define MAX_CANDIDATE_NUMBER	50		// �ִ� ���ĺ� ���ɼ�. 




//-----------------------------
// ���ĺ��� ������.
//-----------------------------
class cltCandidateManager{
public:

#ifdef _SAFE_MEMORY
	NSafeTArray<cltSimplePerson*, MAX_CANDIDATE_NUMBER>		pclCandidate;
#else
	cltSimplePerson* pclCandidate[MAX_CANDIDATE_NUMBER];
#endif

	cltCandidateManager();
	~cltCandidateManager();

	// �ĺ��� ����Ѵ�. 
	BOOL Set(SI32 index, cltSimplePerson* pclcandidate);
	// �ĺ� ����� ����Ѵ�. 
	BOOL DeletePerson(SI32 personid);

	// ��� �ĺ� ����� ����Ѵ�. 
	BOOL Delete();

	//personid�� �ش��ϴ� �ĺ����� ������ ���´� 
	cltSimplePerson* GetCandidateInfoFromPersonID(SI32 personid, SI32* pindex);

	// ���ĺ����� ���ڸ� �˾Ƴ���. 
	SI32 GetCandidateNum();

	//Ref�� �ش��ϴ� �ĺ����� ������ ���´� 
	cltSimplePerson* GetCandidateInfoFromRef(SI32 ref);


};

//---------------------------------
// ��ܰ� ���õ� �ĺ��� ������. 
//---------------------------------
class cltCityHallCandidateManager{
private:
#ifdef _SAFE_MEMORY
	NSafeTArray<cltCandidateManager*, MAX_RANKTYPE_NUMBER>		pclCandidateManager;
#else
		cltCandidateManager* pclCandidateManager[MAX_RANKTYPE_NUMBER];
#endif

public:


	cltCityHallCandidateManager();
	~cltCityHallCandidateManager();

	// �ĺ��� �����Ѵ�. 
	BOOL SetCandidate(SI32 index, SI32 ranktype, cltSimplePerson* pclcandidate);

	// ��� �ĺ� ����� ����Ѵ�. 
	BOOL Delete();

	// Ư�� Personid�� ��� �ĺ� ��Ͽ���  ����Ѵ�. 
	BOOL DeletePerson(SI32 personid);

	// Ư�� �ź��� �ĺ����� ��� �����Ѵ�.
	BOOL DeleteRank(SI32 ranktype);


	//personid�� �ش��ϴ� �ĺ����� ������ ���´� 
	cltSimplePerson* GetCandidateInfoFromPersonID(SI32 ranktype, SI32 personid, SI32* pindex);

	// Ư�� �ź��� ���ĺ��� ���ڸ� ���´�. 
	SI32 GetCandidateNum(SI32 ranktype);

	//Ref�� �ش��ϴ� �ĺ����� ������ ���´� 
	cltSimplePerson* GetCandidateInfoFromRef(SI32 ranktype, SI32 ref);


};

#endif