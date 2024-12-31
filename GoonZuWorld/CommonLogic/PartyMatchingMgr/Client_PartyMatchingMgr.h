// ��Ƽ��Ī
#ifndef _CLIENT_PARTYMATCHING_MANAGER_H_
#define _CLIENT_PARTYMATCHING_MANAGER_H_

#include "../../Common/CommonHeader.h"
#include "Info_PartyMatching.h"
#include "../../CommonLogic/Msg/MsgType-PartyMatching.h"






//////////////////////////////////////////////////////////////////////////
// Ŭ���̾�Ʈ ��Ƽ ��Ī �Ŵ���
//////////////////////////////////////////////////////////////////////////


class CClient_PartyMatchingMgr
{
public:
	CClient_PartyMatchingMgr();
	~CClient_PartyMatchingMgr();

public:
	NkVector<CInfo_PartyMatching>	m_PartyList;

public:
	SI32 m_siSelectedCategory;
	SI32 m_siSelectedMission;



	//-------------------------------------------------------------
	// ���� npc Ŭ�������� ���̴� â ó�� ��
	//-------------------------------------------------------------
public:
	void Click_PartyMatchingNPC();		
	void Click_DestroyDlgButton();
	void Click_CategoryButton(SI16 siIndex);



	//-------------------------------------------------------------
	// ������ ����Ʈ ����Ʈ ��ư Ŭ�������� ���̰� �� â ó����
	//-------------------------------------------------------------
public:
	void Click_PartyEnterRequestButton(SI16 siSelectedIndex);
	void Click_WhisperButton(SI16 siSelectedIndex);

	void Click_PartyMakeButton(SI16 siTmpCate);

	

	//-------------------------------------------------------------
	// ��Ƽ��Ī ���� �����ϱ� �������� ���̰� �� â ó����
	//-------------------------------------------------------------
public:
	void Click_PartyMakeButton2();					// ��ư Ŭ���� ��ȭ������ �� ��Ʈ�ѷκ��� ��Ƽ��Ī ��Ͽ� �ʿ��� �������� �о� �����ϸ� ������ ������ �����ϵ��� �Ѵ�.



	// �Ϲ� �������̽�
public:
	bool Get_Info_PartyMemberInfo(CInfo_PartyMatching& rInfo);

	void Set_Category(SI32 siCategory);
	void Set_Mission(SI32 siMission);
	SI32 Get_Category();
	SI32 Get_Mission();

	void Action();

	CInfo_PartyMatching* Get_PartyMatchingInfo(SI16 siSelectedIndex);
	SI32 AlreadyExist(SI32 siMyCharUnique);

	// ��ȭ���ڰ� �ƴ� �Ϲݾ׼ǿ� ���� �������̽��� (�ַ� ������ ���� ����� ��Ŷ�� ���� ó���� �ָ� �̷�)
public:
	// request ( Ŭ�� -> ���� )
	void MsgProcess_Request_CreatePartyMatching(CInfo_PartyMatching& rInfo);
	void MsgProcess_Request_JoinPartyMatching(SI16 siSelectedIndex);
	void MsgProcess_Request_PartyMatchingList(SI16 siCategory);

	// response ( ���� -> Ŭ�� )
	void MsgProcess_Response_PartyMatchingLevel(SI32 siCharID, cltGameResponse_PartyMatchingLevel* pInfo);
	void MsgProcess_Response_PartyMatchingCreate(SI32 siCharID, bool bResult);
	void MsgProcess_Response_PartyMatchingJoin();
};

#endif				//_CLIENT_PARTYMATCHING_MANAGER_H_