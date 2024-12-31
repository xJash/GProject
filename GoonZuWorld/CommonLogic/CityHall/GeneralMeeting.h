#ifndef _GENERALMEETING_H
#define _GENERALMEETING_H

#include "CommonHeader.h"

class cltGeneralMeetingVoter
{
public:
	cltGeneralMeetingVoter();
	~cltGeneralMeetingVoter();

	void			Init();
	void			Set( cltGeneralMeetingVoter* pclVoter );

public:
	SI32			siPersonID;											// ��ǥ�� personid
	TCHAR			szPersonName[ MAX_PLAYER_NAME ];					// ��ǥ�� �̸� 
	SI32			siStockAmount;										// ���� �ֽ� ��
	SI32			siVoteType;											// ��ǥ ����  1: ����,  2: �ݴ�
	SI32			siParticipate;										// ���� ����  0: ���ǻ�,  1: ����,  2:��������
};


class cltGeneralMeetingInfo
{
public:
	cltGeneralMeetingInfo();
	~cltGeneralMeetingInfo();

	void			Init();

	void			SetVoter( cltGeneralMeetingVoter voter[] );

	BOOL			IsVoter( SI32 personid );
	BOOL			IsAleadyVote( SI32 personid );
	BOOL			Vote( SI32 personid, SI32 votetype );
	
	SI32			GetTotalAgree();
	SI32			GetTotalOpposition();
	SI32			GetTotalNotParticipate();//�ݴ��ο� ��Ż ����[2007.07.10 ����]

	SI32			GetResult();

	//void			Action( SI32 _siVillageUnique );

public:
	SI32			siVillageUnique;
	SI32			siMatterType;										
	SI32			siPersonID;											// ������ personid
	SI32			siTotalStock;										// ���� �� �ֽ� �� 
	cltDate			clStartDate;										// ������ȸ ������

	cltDate			clCloseDate;										// ������ȸ ��������

	SI32			siCandidatePersonID;								// ����� �ĺ��� personid
	TCHAR			szCandidateName[ MAX_PLAYER_NAME ];					// ����� �ĺ��� �̸�

	SI32			siAcceptCandidate;									// ���ε��� ���� 

#ifdef _SAFE_MEMORY
	NSafeTArray<cltGeneralMeetingVoter, 100>	clVoter;
#else
	cltGeneralMeetingVoter	clVoter[ 100 ];								// ��ǥ�� ����
#endif
};


#endif