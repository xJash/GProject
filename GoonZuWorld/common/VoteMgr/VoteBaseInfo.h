#ifndef _VOTEBASEINFO_H_
#define _VOTEBASEINFO_H_

#define MAX_CANDIDATURE_NUM				20		// �ִ� ���ĺ��ڼ�

#define MAX_VOTEEXPLAIN_LENGTH			256		// � ��ǥ���� �˸� �ʿ䰡 �����Ƿ�.. �װͿ� ���� ���� ���� text ����

const SI32 Const_MapIndex_PollMap	=	96;		// ���� ��ǥ�� �� �ε���

#if defined(_USA)
	const SI32 Const_CanVote_MinLevel	=	30;		// ��ǥ�� �ϱ����� �ּ� ���� - �̱� ����
#else
	const SI32 Const_CanVote_MinLevel	=	40;		// ��ǥ�� �ϱ����� �ּ� ����
#endif

#endif	// end of _VOTEBASEINFO_H_