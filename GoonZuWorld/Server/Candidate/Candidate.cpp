//---------------------------------
// 2003/6/12 ���°�
//---------------------------------

#include "Candidate.h"

cltCandidateManager::cltCandidateManager()
{
	SI32 i;

	for(i = 0;i < MAX_CANDIDATE_NUMBER;i++)
	{
		pclCandidate[i] = NULL;
	}


	for(i = 0;i < MAX_CANDIDATE_NUMBER;i++)
	{
		pclCandidate[i] = new cltSimplePerson();
	}

}

cltCandidateManager::~cltCandidateManager()
{
	SI32 i;

	for(i = 0;i < MAX_CANDIDATE_NUMBER;i++)
	{
		if(pclCandidate[i])
		{
			delete pclCandidate[i];
			pclCandidate[i] = NULL;
		}
	}
}

// �ĺ��� ����Ѵ�. 
BOOL cltCandidateManager::Set(SI32 index, cltSimplePerson* pclcandidate)
{
	pclCandidate[index]->Set(pclcandidate);
	return TRUE;
}

// �ĺ� ����� ����Ѵ�. 
BOOL cltCandidateManager::DeletePerson(SI32 personid)
{
	SI32 i;

	if(personid == 0)return FALSE;

	// ������ �̹� ��ϵǾ� �ִ��� Ȯ���Ѵ�. 
	for(i = 0; i < MAX_CANDIDATE_NUMBER;i++)
	{
		if(pclCandidate[i]->GetPersonID() == personid)
		{
			pclCandidate[i]->Init();
			return TRUE;
		}
	}

	return TRUE;
}

// �ĺ� ����� ��� ����Ѵ�. 
BOOL cltCandidateManager::Delete()
{
	SI32 i;

	// ������ �̹� ��ϵǾ� �ִ��� Ȯ���Ѵ�. 
	for(i = 0; i < MAX_CANDIDATE_NUMBER;i++)
	{
		if(pclCandidate[i]->GetPersonID())
		{
			pclCandidate[i]->Init();
		}
	}

	return TRUE;
}

//personid�� �ش��ϴ� �ĺ����� ������ ���´� 
cltSimplePerson* cltCandidateManager::GetCandidateInfoFromPersonID(SI32 personid, SI32* pindex)
{
	SI32 i;

	if(personid == 0)return NULL;

	for(i = 0; i < MAX_CANDIDATE_NUMBER;i++)
	{
		if(pclCandidate[i] && pclCandidate[i]->GetPersonID() == personid)
		{
			*pindex = i;
			return pclCandidate[i];
		}
	}

	return NULL;

}

// ���ĺ����� ���ڸ� �˾Ƴ���. 
SI32 cltCandidateManager::GetCandidateNum()
{
	SI32 i;
	SI32 num = 0;

	for(i = 0; i < MAX_CANDIDATE_NUMBER;i++)
	{
		if(pclCandidate[i]->GetPersonID())
		{
			num++;
		}
	}

	return num;

}


//Ref�� �ش��ϴ� �ĺ����� ������ ���´� 
cltSimplePerson* cltCandidateManager::GetCandidateInfoFromRef(SI32 ref)
{
	return pclCandidate[ref];
}


//---------------------------------
// ��ܰ� ���õ� �ĺ��� ������. 
//---------------------------------
cltCityHallCandidateManager::cltCityHallCandidateManager()
{
	SI32 i;

	for(i = 0;i < MAX_RANKTYPE_NUMBER;i++)
	{
		pclCandidateManager[i] = new cltCandidateManager();
	}
}

cltCityHallCandidateManager::~cltCityHallCandidateManager()
{
	SI32 i;

	for(i = 0;i < MAX_RANKTYPE_NUMBER;i++)
	{
		if(pclCandidateManager[i])
		{
			delete pclCandidateManager[i];
			pclCandidateManager[i] = NULL;
		}
	}

}

// �ĺ��� �����Ѵ�. 
BOOL cltCityHallCandidateManager::SetCandidate(SI32 index, SI32 ranktype, cltSimplePerson* pclcandidate)
{
	if(ranktype ==0)return FALSE;
	if(pclcandidate == NULL)return FALSE;

	pclCandidateManager[ranktype]->pclCandidate[index]->Set(pclcandidate);
	return TRUE;
}



// ��� �ĺ� ����� ����Ѵ�. 
BOOL cltCityHallCandidateManager::Delete()
{
	SI32 i;

	for(i = 0;i < MAX_RANKTYPE_NUMBER;i++)
	{
		if(pclCandidateManager[i])
		{
			pclCandidateManager[i]->Delete();
		}
	}

	return TRUE;
}

// Ư�� Personid�� ��� �ĺ� ��Ͽ���  ����Ѵ�. 
BOOL cltCityHallCandidateManager::DeletePerson(SI32 personid)
{
	SI32 i;

	for(i = 0;i < MAX_RANKTYPE_NUMBER;i++)
	{
		if(pclCandidateManager[i])
		{
			pclCandidateManager[i]->DeletePerson(personid);
		}
	}

	return TRUE;
}

// Ư�� �ź��� �ĺ����� ��� �����Ѵ�.
BOOL cltCityHallCandidateManager::DeleteRank(SI32 ranktype)
{
	if(pclCandidateManager[ranktype])
	{
		pclCandidateManager[ranktype]->Delete();
		return TRUE;
	}

	return FALSE;
}


//personid�� �ش��ϴ� �ĺ����� ������ ���´� 
cltSimplePerson* cltCityHallCandidateManager::GetCandidateInfoFromPersonID(SI32 ranktype, SI32 personid, SI32* pindex)
{
	if(pclCandidateManager[ranktype] == NULL)return NULL;

	return pclCandidateManager[ranktype]->GetCandidateInfoFromPersonID(personid, pindex);

}

// Ư�� �ź��� ���ĺ��� ���ڸ� ���´�. 
SI32 cltCityHallCandidateManager::GetCandidateNum(SI32 ranktype)
{
	return pclCandidateManager[ranktype]->GetCandidateNum();
}

//Ref�� �ش��ϴ� �ĺ����� ������ ���´� 
cltSimplePerson* cltCityHallCandidateManager::GetCandidateInfoFromRef(SI32 ranktype, SI32 ref)
{
	return pclCandidateManager[ranktype]->GetCandidateInfoFromRef(ref);
}
