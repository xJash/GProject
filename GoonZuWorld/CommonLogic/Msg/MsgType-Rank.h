//---------------------------------
// 2004/5/20 ���°�
//---------------------------------
#ifndef _MSGTYPERANK_H
#define _MSGTYPERANK_H

//------------------------------------------------------
// �ĺ��� ������ Ŭ���̾�Ʈ�� �뺸. 
//------------------------------------------------------
class cltGameMsgResponse_CandidateList{
public:
	SI32			siIndex;				// �� cltCandidate�����Ͱ� ��� ���Կ� ���� �ϴ°�?
	cltSimpleRank	clRank;				// ���ĺ��� �ź��� ����. 

	cltSimplePerson clPerson;

	cltGameMsgResponse_CandidateList()
	{
		siIndex	= 0;
		clRank.Init();
	}

	cltGameMsgResponse_CandidateList(SI32 index, cltSimpleRank* pclrank, cltSimplePerson* pclperson)
	{
		siIndex	= index;
		clRank.Set(pclrank);
		clPerson.Set(pclperson);
	}
};



#endif
